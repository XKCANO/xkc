/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_UART_PT32L031.H
 * Version : 0.1
 * 32bit MCU : PT32L031
 * Cortex : Cortex-M0
 *
 * Compiler : 
 *   Keil ARM 5.18 Compiler
 *
 * Pack:
 *   PAI-IC.PT32X031_DFP.1.0.6
 *
 * Author : 
 *   Tang
 *
 * Description : 
 * 	串口打印输出公共接口函数库
 *
 * History :
 * 	2024-4-11: 初版发布
 *
 */

#ifndef __FE_755LHA_USART_PT32L031_H
#define __FE_755LHA_USART_PT32L031_H

#include "stdint.h"

/*
 * @details: 回调函数
 */
typedef void (*FE_UART_CALLBACK)(uint32_t p, uint32_t l);

/*
 * @brief UART主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_uart_process_run(void);

/*
 * @brief 串口打开
 *
 * @param[in] mode:
 *    =0:normal mode
 *    =1:debug mode
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_uart_open(uint32_t mode);

/*
 * @brief 串口关闭
 *
 * @param[in]:无
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 */
//uint32_t fe_uart_close(void);

/*
 * @brief 查询UART状态
 *
 * @param [in] l:接收数据长度
 *
 * @return:
 *   =0:串口关闭
 *   =1:串口忙
 *
 * @details 进入DeepSleep前，要确保串口空闲状态
 */
uint32_t fe_get_uart_state(void);

/*
 * @brief 串口写数据
 *
 * @param [in] data 待发送数据首地址
 * @param [in] len 待发送数据长度
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区长度56
 */
uint32_t fe_uart_write(unsigned char *data, uint32_t len);

/*
 * @brief 串口读数据
 *
 * @param [in] data 数据缓存首地址
 *
 * @return:
 *   >0:数据长度
 *   =0:失败
 *
 * @details 数据缓冲区长度56
 */
uint32_t fe_uart_read(unsigned char *data);

/*
 * @brief 串口接收回调函数
 *
 * @param [in] event 回调函数
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 */
//uint32_t fe_uart_register_event(FE_UART_RX_CALLBACK event);

/*
 * @brief 设置串口回调函数
 *
 * @param [in] cb: 回调函数
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *   OPEN_BUZZER: 0x43
 *   ENTER_DEEP_SLEEP: 0x44
 */
//uint32_t fe_set_uart_callback(FE_UART_CALLBACK cb);

#endif

