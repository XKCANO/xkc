/**
 * @file        cm_pwm.h
 * @brief       PWM接口
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By ZHANGXW
 * @date        2021/03/09
 *
 * @defgroup pwm pwm
 * @ingroup PI
 * @{
 */

#ifndef __CM_PWM_H__
#define __CM_PWM_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/** 设备ID */
typedef enum{
    CM_PWM_DEV_0,              /*!< 设备1*/
    CM_PWM_DEV_NUM
} cm_pwm_dev_e;

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

/**
 *  @brief 打开PWM设备
 *  
 *  @param [in] dev PWM设备ID
 *  @param [in] frequency 频率HZ
 *  @param [in] duty 占空比，千分比，‰
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_pwm_open(cm_pwm_dev_e dev, int32_t frequency, int32_t duty);

/**
 *  @brief 关闭PWM设备
 *  
 *  @param [in] dev PWM设备ID
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_pwm_close(cm_pwm_dev_e dev);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_PWM_H__ */

/** @}*/
