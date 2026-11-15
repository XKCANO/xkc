/**
 * @file        cm_pm.h
 * @brief       PM接口
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By ljw
 * @date        2021/05/28
 *
 * @defgroup pm pm
 * @ingroup PM
 * @{
 */

#ifndef __CM_PM_H__
#define __CM_PM_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/

/** 上电原因 */
typedef enum
{
    CM_PM_POWER_ON = 0,     /*!<正常上电 */
    CM_PM_PIN_RESET,        /*!<PIN按键复位 */
    CM_PM_SOFT_RESET,       /*!<软件复位 */
    CM_PM_UTC_WAKEUP,       /*!<UTC超时唤醒 */
    CM_PM_EXTPIN_WAKEUP,    /*!<WAKEUP-PIN唤醒 */
    CM_PM_WDT_RESET,        /*!<硬件看门狗复位 */
    CM_PM_UNKNOWN_ON,       /*!<未知，一般为硬件错误 */
}cm_pm_power_on_reason_e;

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
 * @brief 获取上电原因
 * 
 * @return 
 *   >= 0  - 上电原因代码，请参考cm_pm_power_on_reason_e类型定义 
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details More details
 */
cm_pm_power_on_reason_e cm_pm_get_power_on_reason(void);

/**
 * @brief 设置模组电源模式
 *  
 * @param [in] pm_mode 模组电源模式代码，0:关闭standby模式 1:开启standby模式
 *  
 * @return 
 *   = 0  - 成功 
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details 开启standby模式后，若条件成立会进入到浅睡眠模式，推荐使用深睡眠模式。请参考模组电源管理文档
 */
int32_t cm_pm_set_mode(int32_t pm_mode);

/**
 * @brief 获取模组电源模式
 *  
 * @param [out] pm_mode 模组电源模式代码，0:关闭standby模式 1:开启standby模式
 *
 * @return
 *  = 0  - 成功 
 *  < 0  - 失败, 返回值为错误码
 *  
 * @details More details
 */
int32_t cm_pm_get_mode(int32_t *pm_mode);

/**
 * @brief 上锁深睡眠模式
 *  
 * @return 空
 *  
 * @details 执行后，模组将无法进入深睡眠状态
 */
void cm_pm_work_lock(void);

/**
 * @brief 解锁深睡眠模式
 *  
 * @return 空
 *  
 * @details 执行后，模组将允许进入深睡眠状态，推荐该睡眠模式。
 */
void cm_pm_work_unlock(void);

/**
 * @brief 模组重启
 * 
 * @param [in] type 重启类型代码，预留接口
 * 
 * @return 空
 *  
 * @details 目前仅支持soft reboot
 */
void cm_pm_reboot(uint8_t type);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_PM_H__ */

/** @}*/

