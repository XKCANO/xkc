/**
 * @file        cm_common.h
 * @brief       opencpu 通用头文件
 * @copyright   Copyright © 2021 China Mobile IOT. All rights reserved.
 * @author      By tw
 * @date        2021/05/18
 */


#ifndef __CM_COMMON_H__
#define __CM_COMMON_H__


/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cm_gpio.h"
#include "cm_sys.h"



/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef FALSE
#define FALSE (0U)
#endif

#ifndef TRUE
#define TRUE (1U)
#endif
extern void cm_demo_printf(const char *str, ...);

#define LOG_LEVEL  0
#define CM_LOG(fmt, args...) cm_log_printf(LOG_LEVEL, fmt, ##args)

#define CM_DEMO_LOG(fmt, args...) cm_demo_printf(fmt, ##args) 
/****************************************************************************
 * Public Types
 ****************************************************************************/
typedef enum{
	RET_BUSY = -2,
	RET_ERROR =-1,
	RET_SUCCESS = 0
}CM_RET_E;


/****************************************************************************
 * Public Data
 ****************************************************************************/


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif










#undef EXTERN
#ifdef __cplusplus
}
#endif

/** @}*/
/** @}*/

#endif /* __CM_COMMON_H__ */



