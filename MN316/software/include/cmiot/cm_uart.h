/**
 * @file        cm_uart.h
 * @brief       UART驱动接口
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By tw
 * @date        2021/05/18
 *  
 * @defgroup uart uart
 * @ingroup PI
 * @{
 */

#ifndef __CM_UART_H__
#define __CM_UART_H__


/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include "cm_gpio.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/** 波特率 */
#define    CM_UART_BAUDRATE_2400       (2400U)
#define    CM_UART_BAUDRATE_4800       (4800U)
#define    CM_UART_BAUDRATE_9600       (9600U)
#define    CM_UART_BAUDRATE_19200      (19200U)
#define    CM_UART_BAUDRATE_38400      (38400U)
#define    CM_UART_BAUDRATE_57600      (57600U)
#define    CM_UART_BAUDRATE_115200     (115200U)


/****************************************************************************
 * Public Types
 ****************************************************************************/

/**
 *  @brief
 */
/**  UART 通道，一共3个通道 */
typedef enum
{
    CM_UART_DEV_0,  /*!< UART外设0 */
    CM_UART_DEV_1,  /*!< UART外设1 */
    CM_UART_DEV_2,  /*!< UART外设2 */   
    CM_UART_DEV_NUM /*!< 可用UART个数 */
} cm_uart_dev_e;

/** 数据位 */
typedef enum
{
    CM_UART_BYTE_SIZE_8,
    CM_UART_BYTE_SIZE_7,
    CM_UART_BYTE_SIZE_6, 
} cm_uart_byte_size_e;

/** 停止位 */
typedef enum
{
    CM_UART_STOP_BIT_ONE, /*!< UART 1个停止位 */
	CM_UART_STOP_BIT_ONE_HALF, /*!< UART 1.5个停止位 (仅UART1支持)*/
    CM_UART_STOP_BIT_TWO /*!< UART 2个停止位 */
} cm_uart_stop_bit_e;


/** 奇偶校验 */
typedef enum
{
    CM_UART_PARITY_NONE,/*!< UART 无校验 */
    CM_UART_PARITY_ODD, /*!< UART 奇校验 */
    CM_UART_PARITY_EVEN, /*!< UART 偶校验 */
    CM_UART_PARITY_MARK, /*!< UART 一校验 */    
    CM_UART_PARITY_SPACE, /*!< UART 零校验 */
} cm_uart_parity_e;


/** 流控制 */
typedef enum
{
    CM_UART_FLOW_CTRL_NONE,
    CM_UART_FLOW_CTRL_HW,
    CM_UART_FLOW_CTRL_SW
} cm_uart_flow_ctrl_e;

/** UART配置*/
typedef struct
{
    cm_uart_byte_size_e  byte_size;/*!< 数据位 */
    cm_uart_parity_e  parity;/*!< 奇偶校验  */
    cm_uart_stop_bit_e  stop_bit;/*!< 停止位  */
	cm_uart_flow_ctrl_e flow_ctrl;      /*!< 流控制，枚举*/
	int  baudrate;/*!< 波特率 */
} cm_uart_cfg_t;

/** 事件类型 */
typedef enum
{    
	CM_UART_EVENT_TYPE_RX_ARRIVED,  /*!< 接收到新的数据*/ 
}cm_uart_event_type_e;

/** 事件 */
typedef struct
{    
	cm_uart_event_type_e event_type; /*!< 事件类型，数据可读/写完成/错误等*/        
	void *event_param;               /*!< 事件参数*/    
	void *event_entry;               /*!< 事件执行入口*/
} cm_uart_event_t;

/****************************************************************************
 * Public Data
 ****************************************************************************/


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief 串口打开
 *
 * @param [in] dev 串口设备号
 * @param [in] cfg 串口配置
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details UART0、UART2只支持无校验,其他类型设置无效。
 */
int32_t cm_uart_open(cm_uart_dev_e dev, cm_uart_cfg_t *cfg);


/**
 * @brief 串口关闭
 *
 * @param [in] dev 串口设备号
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_uart_close(cm_uart_dev_e dev);


/**
 * @brief 串口写数据
 *
 * @param [in] dev 串口设备号
 * @param [in] data 待发送数据首地址
 * @param [in] len 待发送数据长度
 * @param [in] timeout 最大超时等待时间（单位ms）,值为0xFFFFFFFF时表示一直阻塞
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_uart_write(cm_uart_dev_e dev, const void *data, uint32_t len, uint32_t timeout);


/**
 * @brief 串口读数据
 *
 * @param [in] dev 串口设备号
 * @param [in] len 读取数据长度
 * @param [in] timeout 最大超时等待时间（单位ms）,值为0xFFFFFFFF时表示一直阻塞
 * @param [out] data 读取数据缓存首地址，需分配内存
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_uart_read(cm_uart_dev_e dev, void *data, uint32_t len, uint32_t timeout);


/**
 * @brief 注册指定ID UART的接收回调函数
 *
 * @param [in] dev 串口设备号
 * @param [in] event 回调函数
 * 
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details 中断服务程序及内部调用接口，必须使用编译器参数加载至内存中运行！！！ 
 */
int32_t cm_uart_register_event(cm_uart_dev_e dev, void *event);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_UART_H__ */

/** @}*/
