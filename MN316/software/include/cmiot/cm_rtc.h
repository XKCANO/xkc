/**
 * @file        cm_rtc.h
 * @brief       RTC管理
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By ljw
 * @date        2021/05/28
 *
 * @defgroup rtc rtc
 * @ingroup SYS
 * @{
 */

#ifndef __CM_RTC_H__
#define __CM_RTC_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <time.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/

/** RTC定时器ID枚举 */
typedef enum{
    CM_RTC_TIMER_ID_0 = 0,
    CM_RTC_TIMER_ID_1,	
    CM_RTC_TIMER_ID_2,
    CM_RTC_TIMER_ID_3,	    
    CM_RTC_TIMER_ID_END,
}cm_rtc_timer_id_e;

/**
 * @brief RTC定时器回调函数指针
 *
 * @param [in] arg 入参
 *
 * @return 空
 *
 * @details 创建定时器时传入
 */
typedef void (*cm_rtc_timer_cb)(void * arg);

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
 * @brief 获取UTC时间戳
 *
 * @return 
 *   > 0   - 成功 \n
 *   <= 0  - 失败, 返回值为错误码
 *  
 * @details 网络附着获取为当前网络时间，否则默认时间从2000-1-1开始.，精确到秒
 */
time_t cm_rtc_get_time(void);

/**
 * @brief 获取UTC时间, 北京时区，tm结构
 *  
 * @param [in] time 时间结构体
 *
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details 网络附着获取为当前网络时间，否则默认时间从2000-1-1开始.
 */
int32_t cm_rtc_get_time_tm(struct tm* time);

/**
 * @brief 设置UTC时间, 北京时区，tm结构
 *  
 * @param [in] time 时间结构体
 *
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *
 * @details tm结构,年/月/日，时：分：秒
 */
int32_t cm_rtc_set_time_tm(struct tm* time);

/**
 * @brief 启动rtc定时器
 *  
 * @param [in] timer_id 定时器id
 * @param [in] timeout 定时时间，单位秒
 * @param [in] cb 定时器回调函数
 * @param [in] data 用户参数
 *
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details rtc定时器可唤醒模组睡眠
 */
int32_t cm_rtc_timer_start(cm_rtc_timer_id_e timer_id, uint32_t timeout, cm_rtc_timer_cb cb, void *data);

/**
 * @brief 停止rtc定时器
 *  
 * @param [in] timer_id 定时器id
 *
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *
 * @details rtc定时器可唤醒模组睡眠
 */
int32_t cm_rtc_timer_stop(cm_rtc_timer_id_e timer_id);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_RTC_H__ */

/** @}*/
