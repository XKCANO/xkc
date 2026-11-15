/**
 *  @file    cm_os.h
 *  @brief   OpenCPU CMSIS2操作系统定义
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW,XGL
 *  @date 2021/06/04
 */


#ifndef __CM_OS_H__
#define __CM_OS_H__

#include "stdint.h"
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




typedef uint32_t TZ_ModuleId_t;



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


/// Attributes structure for event flags.
typedef struct {
  const char                   *name;   ///< name of the event flags
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osEventFlagsAttr_t;


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

/**
 * @defgroup RTOS rtos
 * CMSIS2.0操作系统
 * @ingroup OS
 *@{
 */

#define osThreadNew                CM_osThreadNew
#define osTimerNew                 CM_osTimerNew
#define osSemaphoreNew             CM_osSemaphoreNew
#define osMessageQueueNew          CM_osMessageQueueNew
#define osTimerNew                 CM_osTimerNew
#define osTimerGetName             CM_osTimerGetName
#define osTimerStart               CM_osTimerStart
#define osTimerStop                CM_osTimerStop
#define osTimerIsRunning           CM_osTimerIsRunning
#define osTimerDelete              CM_osTimerDelete

osThreadId_t CM_osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);
osSemaphoreId_t CM_osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);
osMessageQueueId_t CM_osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);
osTimerId_t CM_osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);
const char * CM_osTimerGetName (osTimerId_t timer_id) ;
osStatus_t CM_osTimerStart (osTimerId_t timer_id, uint32_t ticks);
osStatus_t CM_osTimerStop (osTimerId_t timer_id);
uint32_t CM_osTimerIsRunning (osTimerId_t timer_id);
osStatus_t CM_osTimerDelete (osTimerId_t timer_id);
/**
 * @brief Get the RTOS kernel tick count.
 *
 * @return RTOS kernel current tick count.
 */
uint32_t osKernelGetTickCount (void);

/**
 * @brief Get the RTOS kernel tick frequency.
 *
 * @return frequency of the kernel tick in hertz, i.e. kernel ticks per second.
 */
uint32_t osKernelGetTickFreq (void);



/**
 * @brief Get name of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.	
 *
 * @return name as null-terminated string.
 */ 
const char *osThreadGetName (osThreadId_t thread_id);

/**
 * @brief Return the thread ID of the current running thread.
 *
 * @return thread ID for reference by other functions or NULL in case of error.
 */
osThreadId_t osThreadGetId (void);

/**
 * @brief Get current thread state of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return current thread state of the specified thread.
 */
osThreadState_t osThreadGetState (osThreadId_t thread_id);

/**
 * @brief Get stack size of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return stack size in bytes.
 */
uint32_t osThreadGetStackSize (osThreadId_t thread_id);

/**
 * @brief Get available stack space of a thread based on stack watermark recording during execution.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return remaining stack space in bytes.
 */
uint32_t osThreadGetStackSpace (osThreadId_t thread_id);

/**
 * @brief Change priority of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 * @param[in]     priority      new priority value for the thread function.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);

/**
 * @brief Get current priority of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return current priority value of the specified thread.
 */
osPriority_t osThreadGetPriority (osThreadId_t thread_id);

/**
 * @brief Pass control to next thread that is in state \b READY.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osThreadYield (void);

/**
 * @brief Suspend execution of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osThreadSuspend (osThreadId_t thread_id);

/**
 * @brief Resume execution of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osThreadResume (osThreadId_t thread_id);

 
/** Terminate execution of current running thread. */
void osThreadExit (void);

/**
 * @brief Terminate execution of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osThreadTerminate (osThreadId_t thread_id);

/**
 * @brief Get number of active threads.
 *
 * @return number of active threads.
 */
uint32_t osThreadGetCount (void);

/**
 * @brief Enumerate active threads.
 *
 * @param[out]    thread_array  pointer to array for retrieving thread IDs.
 * @param[in]     array_items   maximum number of items in array for retrieving thread IDs.
 *
 * @return status code that indicates the execution status of the function.
 */
uint32_t osThreadEnumerate (osThreadId_t *thread_array, uint32_t array_items);

/**
 * @brief Set the specified Thread Flags of a thread.
 *
 * @param[in]     thread_id     thread ID obtained by @ref osThreadNew or @ref osThreadGetId.
 * @param[in]     flags         specifies the flags of the thread that shall be set.
 *
 * @return thread flags after setting or error code if highest bit set.
 */
uint32_t osThreadFlagsSet (osThreadId_t thread_id, uint32_t flags);

/**
 * @brief Clear the specified Thread Flags of current running thread.
 *
 * @param[in]     flags         specifies the flags of the thread that shall be cleared.
 *
 * @return thread flags before clearing or error code if highest bit set.
 */
uint32_t osThreadFlagsClear (uint32_t flags);

/**
 * @brief Get the current Thread Flags of current running thread.
 *
 * @return current thread flags.
 */
uint32_t osThreadFlagsGet (void);

/**
 * @brief Wait for one or more Thread Flags of the current running thread to become signaled.
 *
 * @param[in]     flags         specifies the flags to wait for.
 * @param[in]     options       specifies flags options (osFlagsXxxx).
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return thread flags before clearing or error code if highest bit set.
 */
uint32_t osThreadFlagsWait (uint32_t flags, uint32_t options, uint32_t timeout);

/**
 * @brief Wait for Timeout (Time Delay).
 *
 * @param[in]     ticks         @ref CMSIS_RTOS_TimeOutValue "time ticks" value
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osDelay (uint32_t ticks);

/**
 * @brief Wait until specified time.
 *
 * @param[in]     ticks         absolute time in ticks
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osDelayUntil (uint32_t ticks);


/**
 * @brief Get name of a timer.
 *
 * @param[in]     timer_id      timer ID obtained by @ref osTimerNew.
 *
 * @return name as null-terminated string.
 */
const char *osTimerGetName (osTimerId_t timer_id);

/**
 * @brief Start or restart a timer.
 *
 * @param[in]     timer_id      timer ID obtained by @ref osTimerNew.
 * @param[in]     ticks         @ref CMSIS_RTOS_TimeOutValue "time ticks" value of the timer.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);

/**
 * @brief Stop a timer.
 *
 * @param[in]     timer_id      timer ID obtained by @ref osTimerNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osTimerStop (osTimerId_t timer_id);

/**
 * @brief Check if a timer is running.
 *
 * @param[in]      timer_id      timer ID obtained by @ref osTimerNew.
 *
 * @return
 *   = 0 -  not running \n
 *   = 1 -  running
 */
uint32_t osTimerIsRunning (osTimerId_t timer_id);

/**
 * @brief Delete a timer.
 *
 * @param[in]     timer_id      timer ID obtained by @ref osTimerNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osTimerDelete (osTimerId_t timer_id);

/**
 * @brief Create and Initialize an Event Flags object.
 *
 * @param[in]     attr          event flags attributes; NULL: default values.
 *
 * @return event flags ID for reference by other functions or NULL in case of error.
 */
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);


/**
 * @brief Set the specified Event Flags.
 *
 * @param[in]     ef_id         event flags ID obtained by @ref osEventFlagsNew.
 * @param[in]     flags         specifies the flags that shall be set.
 *
 * @return event flags after setting or error code if highest bit set.
 */
uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);

/**
 * @brief Clear the specified Event Flags.
 *
 * @param[in]     ef_id         event flags ID obtained by @ref osEventFlagsNew.
 * @param[in]     flags         specifies the flags that shall be cleared.
 *
 * @return event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);

/**
 * @brief Get the current Event Flags.
 *
 * @param[in]     ef_id         event flags ID obtained by @ref osEventFlagsNew.
 *
 * @return current event flags.
 */
uint32_t osEventFlagsGet (osEventFlagsId_t ef_id);

/**
 * @brief Wait for one or more Event Flags to become signaled.
 *
 * @param[in]     ef_id         event flags ID obtained by @ref osEventFlagsNew.
 * @param[in]     flags         specifies the flags to wait for.
 * @param[in]     options       specifies flags options (osFlagsXxxx).
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return event flags before clearing or error code if highest bit set.
 */
uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);

/**
 * @brief Delete an Event Flags object.
 *
 * @param[in]      ef_id         event flags ID obtained by @ref osEventFlagsNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);

/**
 * @brief Create and Initialize a Mutex object.
 *
 * @param[in]      attr          mutex attributes; NULL: default values.
 *
 * @return mutex ID for reference by other functions or NULL in case of error.
 */
osMutexId_t osMutexNew (const osMutexAttr_t *attr);


/**
 * @brief Acquire a Mutex or timeout if it is locked.
 *
 * @param[in]     mutex_id      mutex ID obtained by @ref osMutexNew.
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);

/**
 * @brief Release a Mutex that was acquired by @ref osMutexAcquire.
 *
 * @param[in]     mutex_id      mutex ID obtained by @ref osMutexNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMutexRelease (osMutexId_t mutex_id);

/**
 * @brief Get Thread which owns a Mutex object.
 *
 * @param[in]     mutex_id      mutex ID obtained by @ref osMutexNew.
 *
 * @return thread ID of owner thread or NULL when mutex was not acquired.
 */
osThreadId_t osMutexGetOwner (osMutexId_t mutex_id);

/**
 * @brief Delete a Mutex object.
 *
 * @param[in]     mutex_id      mutex ID obtained by @ref osMutexNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMutexDelete (osMutexId_t mutex_id);


/**
 * @brief Acquire a Semaphore token or timeout if no tokens are available.
 *
 * @param[in]     semaphore_id  semaphore ID obtained by @ref osSemaphoreNew.
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);

/**
 * @brief Release a Semaphore token up to the initial maximum count.
 *
 * @param[in]     semaphore_id  semaphore ID obtained by @ref osSemaphoreNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);

/**
 * @brief Get current Semaphore token count.
 *
 * @param[in]     semaphore_id  semaphore ID obtained by @ref osSemaphoreNew.
 *
 * @return number of tokens available.
 */
uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);

/**
 * @brief Delete a Semaphore object.
 *
 * @param[in]     semaphore_id  semaphore ID obtained by @ref osSemaphoreNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);




/**
 * @brief Put a Message into a Queue or timeout if Queue is full.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 * @param[in]     msg_ptr       pointer to buffer with message to put into a queue.
 * @param[in]     msg_prio      message priority.
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);

/**
 * @brief Get a Message from a Queue or timeout if Queue is empty.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 * @param[out]    msg_ptr       pointer to buffer for message to get from a queue.
 * @param[out]    msg_prio      pointer to buffer for message priority or NULL.
 * @param[in]     timeout       @ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);

/**
 * @brief Get maximum number of messages in a Message Queue.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return maximum number of messages.
 */
uint32_t osMessageQueueGetCapacity (osMessageQueueId_t mq_id);

/**
 * @brief Get maximum message size in a Message Queue.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return maximum message size in bytes.
 */
uint32_t osMessageQueueGetMsgSize (osMessageQueueId_t mq_id);

/**
 * @brief Get number of queued messages in a Message Queue.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return number of queued messages.
 */
uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);

/**
 * @brief Get number of available slots for messages in a Message Queue.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return number of available slots for messages.
 */
uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);

/**
 * @brief Reset a Message Queue to initial empty state.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueReset (osMessageQueueId_t mq_id);

/**
 * @brief Delete a Message Queue object.
 *
 * @param[in]     mq_id         message queue ID obtained by @ref osMessageQueueNew.
 *
 * @return status code that indicates the execution status of the function.
 */
osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);
/** @} end of group RTOS*/

#endif

