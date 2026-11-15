/**
 * @file        cm_demo_pm.c
 * @brief       OpenCPU PM测试例程
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 */
 

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include "cm_demo_common.h"
#include "cm_demo_main.h"
#include "cm_common.h"
#include "cm_os.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Private Types
 ****************************************************************************/


 
/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Data
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/
 void cm_test_reboot(unsigned char **cmd, int len)
{
    CM_UNUSED(len);
    cm_demo_printf("cm_test_reboot start...\n");
    osDelay(1000);
    cm_pm_reboot(0);
 }

 void cm_test_sleep(unsigned char **cmd, int len)
 {
     cm_demo_printf("cm_test_sleep start...\n");
     CM_UNUSED(len);
	 
     if(strstr((const char*)cmd[2],"0"))//不允许进入深度睡眠
     {
         cm_demo_printf("cm_pm_work_lock\n");
         cm_pm_work_lock();
     }
     else if(strstr((const char*)cmd[2],"1"))//允许进入深度睡眠
     {
        cm_demo_printf("cm_pm_work_unlock\n");
        cm_pm_work_unlock();
     }
}

void cm_test_pm_mode(unsigned char **cmd, int len)
{
    int32_t pm_mode;
	cm_demo_printf("cm_test_pm_mode start...\n");
    CM_UNUSED(len);
    if(strstr((const char*)cmd[2],"0"))//关闭standby模式
    {
        cm_pm_set_mode(0);
        cm_pm_get_mode(&pm_mode);
        cm_demo_printf("pm_mode=0x%02x\n",pm_mode);
    }
    else if(strstr((const char*)cmd[2],"1"))//开启standby模式(不推荐开启)。
    {
        cm_pm_set_mode(1);
        cm_pm_get_mode(&pm_mode);
        cm_demo_printf("pm_mode=0x%02x\n",pm_mode);
    }
    else
    {
        cm_demo_printf("CMD param error\n");
    }
}


