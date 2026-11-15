/*
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ----------------------------------------------------------------------
 *
 * $Date:        10. January 2017
 * $Revision:    V2.1.0
 *
 * Project:      CMSIS-RTOS2 API
 * Title:        cmsis_os2.h header file
 *
 * Version 2.1.0
 *    Support for critical and uncritical sections (nesting safe):
 *    - updated: osKernelLock, osKernelUnlock
 *    - added: osKernelRestoreLock
 *    Updated Thread and Event Flags:
 *    - changed flags parameter and return type from int32_t to uint32_t
 * Version 2.0.0
 *    Initial Release
 *---------------------------------------------------------------------------*/


#ifndef __CMSIS_DEF_H__
#define __CMSIS_DEF_H__

#include <stdint.h>
#include <stddef.h>


//  ==== Enumerations, structures, defines ====

#ifdef CMIOT_OPENCPU_SUPPORT
#include "osal_type.h"
#else

/// Version information.
typedef struct {
  uint32_t                       api;   ///< API version (major.minor.rev: mmnnnrrrr dec).
  uint32_t                    kernel;   ///< Kernel version (major.minor.rev: mmnnnrrrr dec).
} osVersion_t;

/// Kernel state.
typedef enum {
  osKernelInactive        =  0,         ///< Inactive.
  osKernelReady           =  1,         ///< Ready.
  osKernelRunning         =  2,         ///< Running.
  osKernelLocked          =  3,         ///< Locked.
  osKernelSuspended       =  4,         ///< Suspended.
  osKernelError           = -1,         ///< Error.
  osKernelReserved        = 0x7FFFFFFFU ///< Prevents enum down-size compiler optimization.
} osKernelState_t;

/// Thread state.
typedef enum {
  osThreadInactive        =  0,         ///< Inactive.
  osThreadReady           =  1,         ///< Ready.
  osThreadRunning         =  2,         ///< Running.
  osThreadBlocked         =  3,         ///< Blocked.
  osThreadTerminated      =  4,         ///< Terminated.
  osThreadError           = -1,         ///< Error.
  osThreadReserved        = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osThreadState_t;

/// Priority values.
typedef enum {
    osPriorityNone          = 0,          ///< No priority (not initialized).
  osPriorityIdle          = 1,          ///< Reserved for Idle thread.
  osPriorityLow           = 4,          ///< Priority: low
  osPriorityLow1          = 4+1,        ///< Priority: low + 1
  osPriorityLow2          = 4+2,        ///< Priority: low + 2
  osPriorityLow3          = 4+3,        ///< Priority: low + 3
  osPriorityBelowNormal   = 8,          ///< Priority: below normal
  osPriorityBelowNormal1  = 8+1,        ///< Priority: below normal + 1
  osPriorityBelowNormal2  = 8+2,        ///< Priority: below normal + 2
  osPriorityBelowNormal3  = 8+3,        ///< Priority: below normal + 3
  osPriorityNormal        = 12,         ///< Priority: normal
  osPriorityNormal1       = 12+1,       ///< Priority: normal + 1
  osPriorityNormal2       = 12+2,       ///< Priority: normal + 2
  osPriorityNormal3       = 12+3,       ///< Priority: normal + 3
  osPriorityAboveNormal   = 16,         ///< Priority: above normal
  osPriorityAboveNormal1  = 16+1,       ///< Priority: above normal + 1
  osPriorityAboveNormal2  = 16+2,       ///< Priority: above normal + 2
  osPriorityAboveNormal3  = 16+3,       ///< Priority: above normal + 3
  osPriorityHigh          = 20,         ///< Priority: high
  osPriorityHigh1         = 20+1,       ///< Priority: high + 1
  osPriorityHigh2         = 20+2,       ///< Priority: high + 2
  osPriorityHigh3         = 20+3,       ///< Priority: high + 3
  osPriorityRealtime      = 24,         ///< Priority: realtime
  osPriorityRealtime1     = 24+1,       ///< Priority: realtime + 1
  osPriorityRealtime2     = 24+2,       ///< Priority: realtime + 2
  osPriorityRealtime3     = 24+3,       ///< Priority: realtime + 3
  osPriorityISR           = 31,         ///< Reserved for ISR deferred thread.
  osPriorityError         = -1,         ///< System cannot determine priority or illegal priority.
  osPriorityReserved      = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osPriority_t;

/// Entry point of a thread.
typedef void (*osThreadFunc_t) (void *argument);

/// Entry point of a timer call back function.
typedef void (*osTimerFunc_t) (void *argument);

/// Timer type.
typedef enum {
  osTimerOnce               = 0,          ///< One-shot timer.
  osTimerPeriodic           = 1           ///< Repeating timer.
} osTimerType_t;

/// Timeout value.
#define osWaitForever         0xFFFFFFFFU ///< Wait forever timeout value.0xffffffffUL
#define osNoWait                0x0U
/// Flags options.
#define osFlagsWaitAny        0x00000000U ///< Wait for any flag (default).
#define osFlagsWaitAll        0x00000001U ///< Wait for all flags.
#define osFlagsNoClear        0x00000002U ///< Do not clear flags which have been specified to wait for.

/// Flags errors (returned by osThreadFlagsXxxx and osEventFlagsXxxx).
#define osFlagsError          0x80000000U ///< Error indicator.
#define osFlagsErrorUnknown   0xFFFFFFFFU ///< osError (-1).
#define osFlagsErrorTimeout   0xFFFFFFFEU ///< osErrorTimeout (-2).
#define osFlagsErrorResource  0xFFFFFFFDU ///< osErrorResource (-3).
#define osFlagsErrorParameter 0xFFFFFFFCU ///< osErrorParameter (-4).
#define osFlagsErrorISR       0xFFFFFFFAU ///< osErrorISR (-6).

/// Thread attributes (attr_bits in \ref osThreadAttr_t).
#define osThreadDetached      0x00000000U ///< Thread created in detached state (default)
#define osThreadJoinable      0x00000001U ///< Thread created in joinable state

/// Mutex attributes (attr_bits in \ref osMutexAttr_t).
#define osMutexRecursive      0x00000001U ///< Recursive mutex.
#define osMutexPrioInherit    0x00000002U ///< Priority inherit protocol.
#define osMutexRobust         0x00000008U ///< Robust mutex.

/// Status code values returned by CMSIS-RTOS functions.
typedef enum {
  osOK                      =  0,         ///< Operation completed successfully.
  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
  osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
  osErrorResource           = -3,         ///< Resource not available.
  osErrorParameter          = -4,         ///< Parameter error.
  osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
  osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osStatus_t;


/// \details Thread ID identifies the thread.
typedef void *osThreadId_t;

/// \details Timer ID identifies the timer.
typedef void *osTimerId_t;

/// \details Event Flags ID identifies the event flags.
typedef void *osEventFlagsId_t;

/// \details Mutex ID identifies the mutex.
typedef void *osMutexId_t;

/// \details Semaphore ID identifies the semaphore.
typedef void *osSemaphoreId_t;

/// \details Memory Pool ID identifies the memory pool.
typedef void *osMemoryPoolId_t;

/// \details Message Queue ID identifies the message queue.
typedef void *osMessageQueueId_t;

// [ADD] By wangk
/// Attributes structure for event flags.
typedef struct {
  const char                   *name;   ///< name of the event flags
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osEventFlagsAttr_t;
#endif

#ifndef TZ_MODULEID_T
#define TZ_MODULEID_T
/// \details Data type that identifies secure software modules called by a process.
typedef uint32_t TZ_ModuleId_t;
#endif


/// Attributes structure for thread.
typedef struct {
  const char                   *name;   ///< name of the thread
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                   *stack_mem;    ///< memory for stack
  uint32_t                stack_size;   ///< size of stack
  osPriority_t              priority;   ///< initial thread priority (default: osPriorityNormal)
  TZ_ModuleId_t            tz_module;   ///< TrustZone module identifier
  uint32_t                  reserved;   ///< reserved (must be 0)
} osThreadAttr_t;

/// Attributes structure for timer.
typedef struct {
  const char                   *name;   ///< name of the timer
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osTimerAttr_t;

/// Attributes structure for mutex.
typedef struct {
  const char                   *name;   ///< name of the mutex
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osMutexAttr_t;

/// Attributes structure for semaphore.
typedef struct {
  const char                   *name;   ///< name of the semaphore
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osSemaphoreAttr_t;

/// Attributes structure for memory pool.
typedef struct {
  const char                   *name;   ///< name of the memory pool
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                      *mp_mem;    ///< memory for data storage
  uint32_t                   mp_size;   ///< size of provided memory for data storage
} osMemoryPoolAttr_t;

/// Attributes structure for message queue.
typedef struct {
  const char                   *name;   ///< name of the message queue
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
  void                      *mq_mem;    ///< memory for data storage
  uint32_t                   mq_size;   ///< size of provided memory for data storage
} osMessageQueueAttr_t;


#endif  // CMSIS_OS2_H_
