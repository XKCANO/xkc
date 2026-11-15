/**
 *  @file    cm_demo_ota.c
 *  @brief   OpenCPU OTA相关测试例程
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by WangPeng
 *  @date 2021/9/18
 */


#include "cm_os.h"
#include "cm_ota.h"
#include "cm_demo_common.h"
#include "cm_uart.h"

#define OTA_UART  CM_UART_DEV_1
#define cm_printf cm_demo_printf
#define MAX_DIFF_SIZE           (10 * 1024)             //存放升级包的缓存区大小

static char ota_diff_buf[MAX_DIFF_SIZE] = {0};          //升级包缓存
static bool ota_uart_init_flag = false;
static int total_len = 0;

/**
 *  @brief OTA串口1接收中断回调函数，将串口接收到的数据置于ota_diff_buf中
 * 
 *  @details 此函数必须在声明阶段使用编译器参数置于.ramtext段！！！
 */
static void user_ota_callback(char *rcv_data, uint32_t len) __RAM_FUNC;

/**
 *  @brief OTA串口1接收中断回调函数，将串口接收到的数据置于ota_diff_buf中
 */
static void user_ota_callback(char *rcv_data, uint32_t len)
{
    memcpy (ota_diff_buf + total_len, rcv_data, len);       
    total_len += len;
}

/**
 * @brief  串口初始化
 *
 * @return  成功返回0，失败返回-1
 *
 * @details More details
 */
int open_ota_uart(void)
{
    if (ota_uart_init_flag)
    {
        CM_LOG("OTA_UART has been initialized\n"); 
        return 0;
    }
    
    cm_uart_cfg_t uart_config = {CM_UART_BYTE_SIZE_8 , CM_UART_PARITY_NONE, CM_UART_STOP_BIT_ONE,CM_UART_FLOW_CTRL_NONE,CM_UART_BAUDRATE_9600};   

    if(0 == cm_uart_open(OTA_UART, &uart_config))
    {
        CM_LOG("OTA_UART open ok\n");   
        cm_uart_event_t uart_event ={ CM_UART_EVENT_TYPE_RX_ARRIVED,NULL,NULL};
        uart_event.event_entry = (void *)user_ota_callback;
        cm_uart_register_event(OTA_UART, &uart_event);
        ota_uart_init_flag = true;
    }
    else
    {
        CM_LOG("OTA_UART open fail\n");
        ota_uart_init_flag = false;
        return -1;
    }

    return 0;
}

void test_firmware_download()
{
    if (0 == open_ota_uart())
    {
        total_len = 0;
        memset(ota_diff_buf, 0, MAX_DIFF_SIZE);
        cm_ota_init();
        cm_printf("[OTA] OTA_UART init success, please send package through OTA_UART\n");
    }
    else
    {
        cm_printf("[OTA] OTA_UART init fail\n");
    }
}

void test_firmware_write()
{
    int ret = -1;
    cm_printf("total_len %d\r\n", total_len);
    cm_printf("cm_ota_get_capacity() %d\r\n", cm_ota_get_capacity());
    
    for (int i = 0; i < total_len; i+= 512)
    {
        if ((i + 512) > total_len)
        {
            ret = cm_ota_firmware_write(&ota_diff_buf[i], (total_len - i));
        }
        else
        {
            ret = cm_ota_firmware_write(&ota_diff_buf[i], 512);
        }

        if (-1 == ret)
        {
            cm_printf("cm_ota_firmware_write() error\n");
        }
    }
}

/**
 *  OTA功能调试建议使用方式
 *  DEMO为使用UART1下载升级包，若使用本DEMO，用户需从UART1中传入升级包
 *  查看模组中已写入升级包大小                                       CM:OTA:SIZE
 *  UART1传输升级包                                          CM:OTA:DOWNLOAD
 *  传输完成后写入至模组中                                         CM:OTA:WRITE
 *  差分包传入错误时删除差分包                                       CM:OTA:DELETE
 *  升级（升级成功会重启模组）                                       CM:OTA:UPGRADE
 *
 *  正常流程如下
 *  1.执行 CM:OTA:DOWNLOAD 初始化UART1
 *  2.用户从UART1中传入升级包数据
 *  3.执行 CM:OTA:WRITE 将升级包数据写入flash中
 *  4.执行 CM:OTA:UPGRADE 升级
 */
void cm_test_ota(unsigned char **cmd, int len)
{
    unsigned char operation[20] = {0};
    sprintf(operation, "%s", cmd[2]);

    if (0 == strcmp(operation, "DOWNLOAD"))
    {
        /* 该部分代码为初始化UART1，升级包数据需用户操作从UART1中传入，传入的数据会置于ota_diff_buf中 */
        cm_printf("[OTA] firmware download\n");
        test_firmware_download();
    }
    else if (0 == strcmp(operation, "WRITE"))
    {
        /* 将ota_diff_buf（用户从UART1中传入）中的数据保存至flash */
        cm_printf("[OTA] firmware write\n");
        test_firmware_write();
    }
    else if (0 == strcmp(operation, "SIZE"))
    {
        cm_printf("[OTA] firmware file size is %d\n", cm_ota_get_written_size());
    }
    else if (0 == strcmp(operation, "DELETE"))
    {
        memset(ota_diff_buf, 0, MAX_DIFF_SIZE);
        total_len = 0;
        cm_printf("[OTA] firmware delete\n");
        cm_ota_firmware_erase();
    }
    else if (0 == strcmp(operation, "UPGRADE"))
    {
        cm_printf("[OTA] firmware upgrade: %d\n", cm_ota_upgrade());
    }
    else
    {
        cm_printf("[OTA] Illegal operation\n"); 
    }
}
