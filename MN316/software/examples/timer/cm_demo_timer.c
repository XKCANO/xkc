/**
 *  @file    cm_demo_timer.c
 *  @brief   OpenCPU定时器相关测试例程
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/22
 */


#include "cm_os.h"
#include "cm_demo_common.h"

#define TEST_SOFT_TIMER_NAME    "soft-timer"
#define TEST_RTC_TIMER_ID       CM_RTC_TIMER_ID_0

static void* s_timer_id = NULL;


/**
 *  \brief 软件定时器回调函数
 *  
 *  \param [in] arg 用户参数
 *  \return None
 *  
 *  \details More details
 */
static void soft_timer_callback(void* arg)
{
    (void)arg;

    cm_demo_printf("SOFT-TIMER TIMEOUT\n");
}


/**
 *  \brief RTC定时器回调函数
 *  
 *  \param [in] arg 用户参数
 *  \return None
 *  
 *  \details More details
 */
static void rtc_timer_callback(void* arg)
{
    (void)arg;

    cm_demo_printf("RTC-TIMER TIMEOUT\n");
}


/**
 *  \brief 软件定时器
 *  
 *  \return 成功返回0，失败返回-1
 *  
 *  \details More details
 */
int cm_test_soft_timer(unsigned char **cmd, int len)
{

    if(s_timer_id == NULL)
    {
        osTimerAttr_t timer_attr = {.name = "demo_timer"};
        s_timer_id = osTimerNew(soft_timer_callback, osTimerOnce, NULL, &timer_attr);
    }

    if(s_timer_id == NULL)
    {
        cm_log_printf(0, "soft-timer create fail\n");
        return -1;
    }

    osTimerStart(s_timer_id, 5000);
    cm_demo_printf("soft-timer start\n");
    return 0;
}


/**
 *  \brief RTC定时器
 *  
 *  \return 成功返回0，失败返回-1
 *  
 *  \details More details
 */
int cm_test_rtc_timer(unsigned char **cmd, int len)
{

    cm_rtc_timer_start(TEST_RTC_TIMER_ID, 120, rtc_timer_callback, NULL);
    cm_demo_printf("rtc-timer start\n");
    //cm_pm_work_unlock();//深睡眠测试
    return 0;
}

