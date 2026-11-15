/**
 *  @file    cm_demo_main.c
 *  @brief   OpenCPU使用示例
 *  @copyright copyright ? 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/03
 */


#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "cm_demo_common.h"
#include "cm_demo_main.h"

osEventFlagsId_t cmd_task_flag;
extern cm_uart_cmd_recv_t gstUartCmdRecv;


static osMessageQueueId_t s_cm_user_queue = NULL;

cm_cmd_t cmd_vector[] = {
    {"SYS",       (void *)cm_test_sys_sim_mem},
    {"MODEMG",    (void *)cm_test_modem_get},
    {"MODEMS",    (void *)cm_test_modem_set},
    {"UART",      (void *)cm_test_uart},
    {"I2C",       (void *)cm_test_i2c},
    {"SPI",       (void *)cm_test_spi},
    {"GPIO",      (void *)cm_test_gpio},
    {"PWM",       (void *)cm_test_pwm},
    {"ADC",       (void *)cm_test_adc},
    {"FLASH",     (void *)cm_test_flash},
    {"TCP",       (void *)cm_test_tcp},
    {"UDP",       (void *)cm_test_udp},
    {"DNS",       (void *)cm_test_dns},
    {"CTWING",    (void *)cm_test_ctwing},
    {"ONENET",    (void *)cm_test_onenet},//集成OneNET LWM2M FOTA功能，注意与OneNET HTTP FOTA不一致
    {"UNICOM",    (void *)cm_test_unicom},//联通雁飞格物平台
    {"GOTA",      (void *)cm_test_onenet_fota},//OneNET HTTP FOTA，注意与OneNET LWM2M FOTA不一致
    {"OS",        (void *)cm_test_os},
    {"RTC",       (void *)cm_test_rtc_timer},
    {"TIMER",     (void *)cm_test_soft_timer},
    {"ASOCKET",   (void *)cm_test_asocket_cmd},
    {"OTA",       (void *)cm_test_ota}, //CM:OTA:DOWNLOAD
                                //CM:OTA:WRITE
                                //CM:OTA:SIZE
                                //CM:OTA:UPGRADE
                                //CM:OTA:DELETE
	{"HTTP",      (void *)cm_test_http},
	{"MQTT",      (void *)cm_test_mqtt},
    {"REBOOT",    (void *)cm_test_reboot},//CM:REBOOT	
    {"PM_MODE",   (void *)cm_test_pm_mode},//CM:PM_MODE    
    {"SLEEP",     (void *)cm_test_sleep},//CM:SLEEP  
    {"OPENAT",    (void *)cm_sys_open_at},//CM:OPENAT  
};

extern void test_onenet_fota_init(void);


/**
 *  \brief 比对指定长度的字符串是否相等，不区分大小写
 *  
 *  \param [in] str1 字符串1
 *  \param [in] str2 字符串2
 *  \return 成功返回0，失败返回-1
 *  
 *  \details
 */
static int str_casecmp(char* str1, char* str2, int len)
{
    if(str1 == NULL || str2 == NULL || len <= 0)
    {
        return -1;
    }

    int ch1 = 0;
    int ch2 = 0;

    do
    {
        if((ch1 = *str1++) >= 'a' && ch1 <= 'z')
        {
            ch1 -= 'a' - 'A';
        }

        if((ch2 = *str2++) >= 'a' && ch2 <= 'z')
        {
            ch2 -= 'a' - 'A';
        }
    }while(ch1 && ch1 == ch2 && --len);

    return ch1 - ch2;
}


/**
 *  \brief OpenCPU示例程序入口
 *  
 *  \return None
 *  
 *  \details 示例业务循环
 */
static void cm_demo_task(void* arg)
{
    CM_UNUSED(arg);
    char tempbuf[64] = {0};
    char version[64] = {0};
    int net_retry_time = 60;
    int i = 0;
	cm_uart_cmd_recv_t *pUartCmdRecv_t = &gstUartCmdRecv;
        
    cm_pm_work_lock();
    cm_pm_set_mode(0);
    test_onenet_fota_init();
    open_uart(0);
	osDelay(200);
    cm_demo_printf("OpenCPU task start,boot reason:%d\n", cm_pm_get_power_on_reason());
    cm_sys_get_cm_ver(version, sizeof(version));
    cm_demo_printf("Current Version:%s\n", version);
    
    if(cm_sim_get_cpin()<0)
    {
        cm_demo_printf("sim not ready\n");
    }
    else
    {
		if(cm_sim_get_imsi(tempbuf) == 0)
		{
			cm_demo_printf("IMSI:%s\n",tempbuf);
		}
		else
		{
			cm_demo_printf("IMSI ERROR\n");
		}
		memset(tempbuf,0,64);
		if(cm_sim_get_iccid(tempbuf) == 0)
		{
			cm_demo_printf("ICCID:%s\n",tempbuf);
		}
		else
		{
			cm_demo_printf("ICCID ERROR\n");
		}
		memset(tempbuf,0,64);
		
        cm_demo_printf("sim ready\n");
        cm_demo_printf("Waiting for network connection...\n");
        while(net_retry_time--)//等待驻网
        {
            if(cm_modem_get_pdp_state(0) > 0)
            {
                break;
            }

            osDelay(1000);
        }

        if(net_retry_time <= 0)
        {
            cm_demo_printf("Network is not connected\n");
        }
        else
        {
            cm_demo_printf("Network is connected\n");
        }
    }
    
	osDelay(10);
    struct tm cur_time = {0};
    cm_rtc_get_time_tm(&cur_time);
    cm_demo_printf("Current time:%04d-%02d-%02d %02d:%02d:%02d\n", 
        cur_time.tm_year,
        cur_time.tm_mon,
        cur_time.tm_mday,
        cur_time.tm_hour,
        cur_time.tm_min,
        cur_time.tm_sec);
    if(cm_sys_get_imei(tempbuf) == 0)
    {
        cm_demo_printf("IMEI:%s\n",tempbuf);
    }
    else
    {
        cm_demo_printf("IMEI ERROR\n");
    }

    test_asocket_init();

    while(1)
    {
        cm_demo_printf("\nplease input cmds:\n");
        pUartCmdRecv_t->cmd_execute = 0;
        osEventFlagsWait(cmd_task_flag, 0x00000001U, osFlagsWaitAny, osWaitForever);
		if ((pUartCmdRecv_t->len < 2))
        {
            cm_demo_printf("CMD NOT DEFINE\n");
        }
        else
        {
            for (i = 0; i <(int)( (sizeof(cmd_vector) / sizeof(cm_cmd_t))); i++)
            {
                if (NULL == pUartCmdRecv_t->buf[1])
                {
                    break;
                }
                if (strcmp(pUartCmdRecv_t->buf[1], cmd_vector[i].cmdstr) == 0)
                {
                    (*(cmd_vector[i].cmdfunc))(pUartCmdRecv_t->buf, pUartCmdRecv_t->len);
                    cm_demo_printf("OK\n");
                    break;
                }
            }
            if (i >= (int)((sizeof(cmd_vector) / sizeof(cm_cmd_t))))
            {
                cm_demo_printf("CMD NOT DEFINE\n");
            }
        }
        for (i = 0; i < pUartCmdRecv_t->len; i++)
        {
            if (NULL != pUartCmdRecv_t->buf[i])
            {
                cm_free(pUartCmdRecv_t->buf[i]);
                pUartCmdRecv_t->buf[i] = NULL;
            }
        }
    }

    cm_demo_printf("OpenCPU task exit\n");
    osThreadExit();
}


/**
 *  \brief OpenCPU版本程序入口
 *  
 *  \return 空
 *  
 *  \details 仅用于创建OC线程,请勿修改此函数名
 */
void cm_opencpu_entry(void)
{
	cmd_task_flag = osEventFlagsNew(0);
    osThreadAttr_t attr = {
        .name = "OpenCPU-DEMO",
        .priority = osPriorityNormal2,
        .stack_size = 1024,//WORD,size = 1024*4
    };

    osThreadNew(cm_demo_task, NULL, (const osThreadAttr_t *)&attr);
	
}


