/******************************************************************************
* @file    PT32x076_type.h
* @author  应用开发团队
* @version V1.1.0
* @date    2022/9/1
* @brief    This file contains all the functions prototypes for the TYPE firmware library.
*
******************************************************************************
* @attention
*
*
*****************************************************************************/

#ifndef PT32x076_Type_H
#define PT32x076_Type_H

#ifdef __cplusplus
extern "C" {
#endif


#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <rt_misc.h>


/** @addtogroup Exported_types **/
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef const int32_t sc32; 	/*!< Read Only	*/
typedef const int16_t sc16;	/*!< Read Only	*/
typedef const int8_t  sc8;		/*!< Read Only  	*/

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t  vs8;

typedef __I int32_t vsc32;	/*!< Read Only	*/
typedef __I int16_t vsc16;	/*!< Read Only 	*/
typedef __I int8_t  vsc8;		/*!< Read Only	*/

typedef unsigned long long  u64;
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;	/*!< Read Only	*/
typedef unsigned short const uc16;	/*!< Read Only	*/
typedef unsigned char  const uc8;	/*!< Read Only	*/

typedef __IO uint32_t  vu32;
typedef __IO uint16_t  vu16;
typedef __IO uint8_t   vu8;

typedef __I uint32_t vuc32;	/*!< Read Only	*/
typedef __I uint16_t vuc16;	/*!< Read Only	*/
typedef __I uint8_t  vuc8;		/*!< Read Only	*/

#define UNUSED(x)  (void)(x)

#endif



