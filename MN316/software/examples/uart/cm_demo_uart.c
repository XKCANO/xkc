/**
 *  @file    cm_demo_uart.c
 *  @brief   OpenCPU串口测试例程
 *  @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 */


 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include "cm_uart.h"
#include "cm_demo_common.h"
#include "cm_demo_main.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define CM_DEMO_UART_LOG  CM_DEMO_LOG

#define UART_RX_BUF_SIZE   256
#define CM_TEST_UART_DEV   CM_UART_DEV_0 //可修改测试uart口
/****************************************************************************
 * Private Types
 ****************************************************************************/
typedef struct{
    const char* cmd_str;
    int cmd_type;
} uart_test_tbl_t;


/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/


/****************************************************************************
 * Private Data
 ****************************************************************************/
static void* g_opencpu_recv_tsk_handle = NULL;
static void* g_uart_sem = NULL;
static volatile uint8_t uart0_rx_buf[UART_RX_BUF_SIZE+1] = {0};
static volatile uint32_t uart0_rx_size = 0;
static volatile uint8_t uart1_rx_buf[UART_RX_BUF_SIZE] = {0};
static volatile uint32_t uart1_rx_size = 0;
static volatile uint8_t uart2_rx_buf[UART_RX_BUF_SIZE] = {0};
static volatile uint32_t uart2_rx_size = 0;
extern osEventFlagsId_t cmd_task_flag;
cm_uart_cmd_recv_t gstUartCmdRecv = {0}; //串口命令缓冲区
/****************************************************************************
 * Private Functions
 ****************************************************************************/
static int  __cm_cmd_engine(unsigned char * prefix,unsigned char * uart_buf,int* uart_buf_len,unsigned char **cmd_buf,int *cmd_len)
{
    unsigned char *p1,*p2,*p3,*temp1,*temp2;
    uart_buf[*uart_buf_len] = 0;//结尾
    p1 = strstr(uart_buf,prefix);
    if(p1 == 0)
    {
        *uart_buf_len = 0;
        return -1;
    }
    p2 = strstr(p1,"\r\n");
    if(p2 == 0)
    {
        *uart_buf_len = 0;
        return -1;
    }
    *cmd_len = 0;
    p3 = strchr(p1,':');
    if(p3 == 0)
    {
        *uart_buf_len = 0;
        return -1;
    }
    cmd_buf[(*cmd_len)++] = cm_malloc(p3-p1+1+1);
    memset(cmd_buf[*cmd_len-1],0,p3-p1+1);
    if(cmd_buf[*cmd_len -1] <= 0)
    {
        *uart_buf_len = 0;
        return -1;
    }
    memcpy(cmd_buf[*cmd_len-1],p1,(int)(p3-p1));
    temp1= p3;
    while(1)
    {
        if(*cmd_len >= 20)
        {
            *uart_buf_len = 0;
            for(int j = 0;j< *cmd_len;j++)
            {
                free(cmd_buf[j]);
            }
            return -1;
        }
        temp2 = strchr(temp1+1,':');
        if(temp2 == 0)
            break;        
        if((temp2-temp1) < 1)
        {
             for(int j = 0;j< *cmd_len;j++)
            {
                free(cmd_buf[j]);
            }
            *uart_buf_len = 0;
            return -1;
        }
        cmd_buf[(*cmd_len)++] =cm_malloc(temp2-temp1+1);
        if(cmd_buf[*cmd_len -1] <= 0)
        {
             for(int j = 0;j< *cmd_len;j++)
            {
                free(cmd_buf[j]);
            }
            *uart_buf_len = 0;
            return -1;
        }
        memset(cmd_buf[*cmd_len-1],0,temp2-temp1);
        memcpy(cmd_buf[*cmd_len-1],temp1+1,temp2-temp1-1);
        temp1 = temp2;            
    }
    if((p2-temp1-1) < 1)
    {
         for(int j = 0;j< *cmd_len;j++)
        {
            free(cmd_buf[j]);
        }
        *uart_buf_len = 0;
        return -1;
    }
    
    cmd_buf[(*cmd_len)++] = cm_malloc(p2-temp1+1);
    memset(cmd_buf[*cmd_len-1],0,p2-temp1);
    memcpy(cmd_buf[*cmd_len-1],temp1+1,p2-1-temp1);
    *uart_buf_len = 0;
    return 0;
}

/**
 *  \brief 串口0接收中断回调函数
 * 
 *  \details 中断处理函数以及内部调用接口必须在声明阶段使用编译器参数置于.ramtext段！！！
 */
static void user_uart0_callback(char *rcv_data, uint32_t len) __RAM_FUNC;

/**
 *  \brief 串口1接收中断回调函数
 * 
 *  \details 中断处理函数以及内部调用接口必须在声明阶段使用编译器参数置于.ramtext段！！！
 */
static void user_uart1_callback(char *rcv_data, uint32_t len) __RAM_FUNC;

/**
 *  \brief 串口2接收中断回调函数
 * 
 *  \details 中断处理函数以及内部调用接口必须在声明阶段使用编译器参数置于.ramtext段！！！
 */
static void user_uart2_callback(char *rcv_data, uint32_t len) __RAM_FUNC;

void cm_demo_printf(const char *str, ...) __RAM_FUNC;

/**
 *  \brief 串口0接收中断回调函数
 * 
 *  \details 此函数只作为串口接收，请勿添加大量代码。
 */
static void user_uart0_callback(char *rcv_data, uint32_t len)
{
    if (uart0_rx_size < UART_RX_BUF_SIZE)
    {
        len = (UART_RX_BUF_SIZE - uart0_rx_size) > len ? len : (UART_RX_BUF_SIZE - uart0_rx_size);
        memcpy((void*)&uart0_rx_buf[uart0_rx_size], (void*)rcv_data, len);
        uart0_rx_size += len;
    }

    if (g_uart_sem != NULL && (uart0_rx_buf[uart0_rx_size - 2] == '\r' || uart0_rx_buf[uart0_rx_size - 2] == '\n' || uart0_rx_buf[uart0_rx_size - 1] == '\r' || uart0_rx_buf[uart0_rx_size - 1] == '\n' || (uart0_rx_size >= UART_RX_BUF_SIZE)))
    {
		
		//处理收到数据事件
        if(gstUartCmdRecv.cmd_execute==0)
		{
			gstUartCmdRecv.cmd_execute ++;
			osSemaphoreRelease(g_uart_sem);
		}
        else
		{
			memset((void*)uart0_rx_buf, 0, sizeof(uart0_rx_buf));
			uart0_rx_size = 0;
			cm_demo_printf("Uart busy\n");
		}
    }
}


/**
 *  \brief 串口1接收中断回调函数
 * 
 *  \details 此函数只作为串口接收，请勿添加大量代码。
 */
static void user_uart1_callback(char *rcv_data, uint32_t len)
{
    if (uart1_rx_size < UART_RX_BUF_SIZE)
    {
        len = (UART_RX_BUF_SIZE - uart1_rx_size) > len ? len : (UART_RX_BUF_SIZE - uart1_rx_size);
        memcpy((void*)&uart1_rx_buf[uart1_rx_size], (void*)rcv_data, len);
        uart1_rx_size += len;
    }

    if (g_uart_sem != NULL)
    {
        osSemaphoreRelease(g_uart_sem);
    }
}


/**
 *  \brief 串口2接收中断回调函数
 * 
 *  \details 此函数只作为串口接收，请勿添加大量代码。
 */
static void user_uart2_callback(char *rcv_data, uint32_t len)
{
    if (uart2_rx_size < UART_RX_BUF_SIZE)
    {
        len = (UART_RX_BUF_SIZE - uart2_rx_size) > len ? len : (UART_RX_BUF_SIZE - uart2_rx_size);
        memcpy((void*)&uart2_rx_buf[uart2_rx_size], (void*)rcv_data, len);
        uart2_rx_size += len;
    }

    if (g_uart_sem != NULL )
    {
        osSemaphoreRelease(g_uart_sem);
    }
}


/**
 *  \brief 串口接收数据处理函数
 * 
 *  \details
 */
static void uart_recv_task_loop(void * arg)
{
    (void)arg;
    cm_user_msg_t user_msg = {0};
	cm_uart_cmd_recv_t* pstUartCmdRecv = &gstUartCmdRecv;
    CM_DEMO_UART_LOG("uart recv task start\r\n");

    while (1)
    {
        if (g_uart_sem != NULL)
        {
            osSemaphoreAcquire(g_uart_sem, osWaitForever);//阻塞
        }
    
        if (uart1_rx_size != 0)
        {
            cm_uart_write(CM_UART_DEV_1, (const void*)uart1_rx_buf, uart1_rx_size, 500);
            CM_LOG("uart1 recv and write ok, recv len %d,data:%s\r\n", uart1_rx_size, uart1_rx_buf);
            memset((void*)uart1_rx_buf, 0, sizeof(uart1_rx_buf));
			uart1_rx_size = 0;
        }
        else if (uart0_rx_size != 0)
        {/*
            CM_LOG("uart0 recv and write ok, recv len %d,data:%s\r\n", uart0_rx_size, uart0_rx_buf);

            user_msg.cmd_str = (char*)cm_malloc(uart0_rx_size + 1);
            user_msg.param = NULL;

            memcpy(user_msg.cmd_str, (void*)uart0_rx_buf, uart0_rx_size);
            user_msg.cmd_str[uart0_rx_size] = '\0';
            cm_user_queue_send(&user_msg);//向队列发送数据
            memset((void*)uart0_rx_buf, 0, sizeof(uart0_rx_buf));
			uart0_rx_size = 0;*/
			 if(pstUartCmdRecv->cmd_execute != 0)
        {             
            //OC指令参数的格式是否正确
            char *trai_colon_pz = NULL;
            
            trai_colon_pz = strrchr((const char *)uart0_rx_buf, ':');
            
            if((trai_colon_pz != NULL)&&((*(trai_colon_pz+1) == '\0') || (*(trai_colon_pz+1) == '\r') ||(*(trai_colon_pz+1) == '\n')))
            {
                cm_demo_printf("formate error\n");
                memset((void*)uart0_rx_buf, 0, sizeof(uart0_rx_buf));
				uart0_rx_size = 0;
                pstUartCmdRecv->cmd_execute = 0;
                continue;
            }
            
            //解析命令，如果未检测到正确的命令格式，则丢弃本次数据
            if(__cm_cmd_engine("CM",(unsigned char *)uart0_rx_buf,(int *)&uart0_rx_size,pstUartCmdRecv->buf,&pstUartCmdRecv->len) == -1)
            {
                cm_demo_printf("CM CMD error\n");
                memset((void*)uart0_rx_buf, 0, sizeof(uart0_rx_buf));
				uart0_rx_size = 0;
                pstUartCmdRecv->cmd_execute = 0;
            }
            else
            {
                //清空数据缓冲，并提示主任务开始执行命令
                memset((void*)uart0_rx_buf, 0, sizeof(uart0_rx_buf));
				uart0_rx_size = 0;
                osEventFlagsSet(cmd_task_flag, 0x00000001U);  
            }
        }
			
        }
        else if (uart2_rx_size != 0)
        {
            cm_uart_write(CM_UART_DEV_2, (const void*)uart2_rx_buf, uart2_rx_size, 500);
            CM_LOG("uart2 recv and write ok, recv len %d,data:%s\r\n", uart2_rx_size, uart2_rx_buf);
            memset((void*)uart2_rx_buf, 0, sizeof(uart2_rx_buf));
			uart2_rx_size = 0;
        }
    }
    
    osThreadExit();
}


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/**
 *  \brief 串口打印
 * 
 *  \details
 */
void cm_demo_printf(const char *str, ...)
{
    uint8_t s[256]  = {0};
    uint32_t str_len = 0;

    memset(s, 0, sizeof(s));

    if ((str == NULL) || (strlen(str) == 0))
    {
        return;
    }
    
    va_list args;
    va_start(args, str);
    str_len = (uint32_t)vsnprintf((char *)s, 256, str, args);
    va_end(args);

    cm_uart_write(CM_TEST_UART_DEV, (char *)s, str_len, 2000);
}


/**
 * @brief  串口初始化
 *
 * @return  成功返回0，失败返回-1
 *
 * @details More details
 */
int open_uart(int devno)
{
    cm_uart_cfg_t uart_config[CM_UART_DEV_NUM] = {
            {CM_UART_BYTE_SIZE_8 , CM_UART_PARITY_NONE, CM_UART_STOP_BIT_ONE,CM_UART_FLOW_CTRL_NONE,CM_UART_BAUDRATE_9600},
            {CM_UART_BYTE_SIZE_8 , CM_UART_PARITY_NONE, CM_UART_STOP_BIT_ONE,CM_UART_FLOW_CTRL_NONE,CM_UART_BAUDRATE_9600},
            {CM_UART_BYTE_SIZE_8 , CM_UART_PARITY_NONE, CM_UART_STOP_BIT_ONE,CM_UART_FLOW_CTRL_NONE,CM_UART_BAUDRATE_9600}
        };
	cm_uart_event_t uart_event ={ CM_UART_EVENT_TYPE_RX_ARRIVED,NULL,NULL};

	
    if(g_uart_sem == NULL)
    {
        g_uart_sem = osSemaphoreNew(1, 0, NULL);
        cm_assert(g_uart_sem != NULL);
    }

    if(devno == CM_UART_DEV_0)
    {
        if(0 == cm_uart_open(CM_UART_DEV_0, &uart_config[0]))
        {
            CM_LOG("uart0 open ok\n");    
			uart_event.event_entry = (void *)user_uart0_callback;
            cm_uart_register_event(CM_UART_DEV_0, &uart_event);
        }
        else
        {
            CM_LOG("uart0 open fail\n");
            return -1;
        }
    }
    else if(devno == CM_UART_DEV_1)
    {
        if(0 == cm_uart_open(CM_UART_DEV_1, &uart_config[1]))
        {
            CM_LOG("uart1 open ok\n");   
			uart_event.event_entry = (void *)user_uart1_callback;
            cm_uart_register_event(CM_UART_DEV_1, &uart_event);
        }
        else
        {
            CM_LOG("uart1 open fail\n");
            return -1;
        }
    }
    else if(devno == CM_UART_DEV_2)
    {
        if(0 == cm_uart_open(CM_UART_DEV_2, &uart_config[2]))
        {
            CM_LOG("uart2 open ok\n");   
			uart_event.event_entry = (void *)user_uart2_callback;
            cm_uart_register_event(CM_UART_DEV_2, &uart_event);
        }
        else
        {
            CM_LOG("uart2 open fail\n");
            return -1;
        }
    }

    if(g_opencpu_recv_tsk_handle == NULL)
    {
        osThreadAttr_t attr = {
                .name = "OpenCPU-UART-DEMO",
                .priority = osPriorityNormal2,
                .stack_size = 1024,
            };
        
       g_opencpu_recv_tsk_handle = osThreadNew(uart_recv_task_loop, NULL, (const osThreadAttr_t *)&attr);
    }

    return 0;
}


/**
 * \brief UART1、UART2收发测试
 *
 */
int cm_test_uart(unsigned char **cmd, int len)
{
	int uart_num = atoi(cmd[2]);

    if(uart_num == 1) open_uart(1);
    else if(uart_num == 2)open_uart(2);
	else return -1;

    return 0;
}