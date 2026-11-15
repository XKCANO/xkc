/**
 *  @file    custom_main.c
 *  @brief   OpenCPU用户业务
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/04
 */


#include "stdlib.h"
#include "stdio.h"
#include "cm_os.h"
#include "cm_uart.h"
#include "custom_main.h"

#include "msg_box.h"


extern SYSTEM_TypeDef System;


/**
 *  \brief OpenCPU用户程序入口
 *  
 *  \return None
 *  
 *  \details 用户业务循环
 

static void custom_task_loop(void* arg)
{
    CM_UNUSED(arg);
	
	//OpenCPU_Message_Box_Task_Main();

    char* test_str = "hello world\n";

    cm_uart_cfg_t uart_config = {CM_UART_BYTE_SIZE_8 , CM_UART_PARITY_NONE, CM_UART_STOP_BIT_ONE,CM_UART_FLOW_CTRL_NONE,CM_UART_BAUDRATE_9600};

    cm_uart_open(CM_UART_DEV_0, &uart_config);
    cm_uart_write(CM_UART_DEV_0, test_str, strlen(test_str), 500);
    osDelay(1000);
    cm_uart_close(CM_UART_DEV_0);

    osThreadExit();
}
*/

/**
 *  \brief OpenCPU版本程序入口
 *  
 *  \return 空
 *  
 *  \details 仅用于创建OC线程,请勿修改此函数名
 */
void cm_opencpu_entry(void)
{
    /* 用户线程优先级范围osPriorityNormal -> osPriorityNormal5 */
    osThreadAttr_t attr = {
        .name = "OpenCPU-CUSTOM",
        .priority = osPriorityNormal2,
        .stack_size = 1024,//WORD,size = 1024*4
    };

    //osThreadNew(custom_task_loop, NULL, (const osThreadAttr_t *)&attr);
	System.handle = osThreadNew(OpenCPU_Message_Box_Task_Main, NULL, (const osThreadAttr_t *)&attr);
}

