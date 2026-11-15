/**
 * @file        cm_etimer.h
 * @brief       etimer模块接口定义
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By wangk
 * @date        2021/08/31
 *
 * @defgroup etimer etimer
 * @ingroup SYS
 * @{
 */

#ifndef __CM_ETIMER_H__
#define __CM_ETIMER_H__

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

/** etimer对象 */
typedef struct _cm_etimer cm_etimer_t;

/** etimer管理器对象 */
typedef struct
{
    cm_etimer_t *list_head; /*!< 所管理的timer链表表头 */
} cm_etimer_manager_t;

/**
  Event Loop回调函数类型
  @param timer          [in] 定时器对象
  @param cb_param       [in] 回调函数用户参数
*/
typedef void (*cm_etimer_cb)(cm_etimer_t *timer, void *cb_param);

/** etimer对象定义 */
struct _cm_etimer
{
    uint32_t start_time;   /*!< timer启动时间(ms) */
    uint32_t interval;     /*!< timer超时间隔时间(ms) */
    cm_etimer_cb timer_cb; /*!< timer回调函数 */
    void *cb_param;        /*!< 回调函数参数 */

    // 所属管理器
    cm_etimer_manager_t *manager;

    // timer链表链接指针
    struct _cm_etimer *next;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/**
 * @brief 初始化定时器管理器
 *
 * @param [in] manager     timer管理器
 *
 * @return  
 *   = 0 - 成功 \n
 *   < 0 - 失败
 *
 * @details 
 */
int32_t cm_etimer_manager_init(cm_etimer_manager_t *manager);

/**
 * @brief 初始化定时器
 *
 * @param [in] timer    要初始化的timer对象
 * @param [in] timer_cb 定时器回调函数
 * @param [in] cb_param 回调函数用户参数
 *
 * @return  
 *   = 0 - 成功 \n
 *   < 0 - 失败
 *
 * @details 
 */
int32_t cm_etimer_init(cm_etimer_t *timer, cm_etimer_cb timer_cb, void *cb_param);

/**
 * @brief 启动或重启定时器
 *
 * @param [in] manager     timer所属管理器
 * @param [in] timer       要启动的timer对象
 * @param [in] millisec    超时时间(ms)
 *
 * @return  
 *   = 0 - 成功 \n
 *   < 0 - 失败
 *
 * @details
 *   如果timer已启动将会按照新的参数重新启动 \n
 *   timer超时后将会自动停止, 如果需要周期触发则需要再次调用start重新启动
 */
int32_t cm_etimer_start(cm_etimer_manager_t *manager, cm_etimer_t *timer, uint32_t millisec);

/**
 * @brief 停止定时器
 *
 * @param [in] timer    要停止的timer对象
 *
 * @return  
 *   = 1 - timer已经是停止状态 \n
 *   = 0 - 成功停止 \n
 *   < 0 - 失败
 *
 * @details 
 */
int32_t cm_etimer_stop(cm_etimer_t *timer);

/**
 * @brief 获取当前所有定时器距离下一次超时还需等待的时间(ms)
 *
 * @param [in] manager     timer管理器
 *
 * @details 如果当前定时器队列为空,将返回0xFFFFFFFF
 */
uint32_t cm_etimer_get_wait_time(const cm_etimer_manager_t *manager);

/**
 * @brief 运行所有timer
 *
 * @param [in] manager     timer管理器
 *
 * @details 在某个执行环境(例如: eloop)中被反复调用, 检查所有定时器是否超时并调用回调函数
 */
void cm_etimer_run(cm_etimer_manager_t *manager);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_ETIMER_H__ */

/** @}*/
