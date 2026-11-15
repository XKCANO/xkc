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
 *  RAM: 100bytes
 *  Name: FE_SCI_TypeDef Sci
 *        FE_UART_TypeDef uart
 *
 * History :
 * 	2024-4-11: 初版发布
 *
 */

#ifndef __FE_755LHA_USART_PT32L031_H
#define __FE_755LHA_USART_PT32L031_H

#include "stdint.h"

#define SETUP_SAMPLING_FLAG 0x41
#define CLEAR_SAMPLING_FLAG 0x42
#define OPEN_BUZZER         0x43
#define ENTER_DEEP_SLEEP    0x44

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
 *   !=0:failure
 *
 * @details
 */
uint32_t fe_uart_open(uint32_t mode);

/*
 * @brief 查询UART状态
 *
 * @param [in] l:接收数据长度
 *
 * @return:
 *   =0:串口关闭
 *  !=0:串口忙
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
 *  !=0:failure
 *
 * @details 数据缓冲区长度40
 */
uint32_t fe_uart_write(unsigned char *data, uint32_t len);

/*
 * @brief 设置串口回调函数
 *
 * @param [in] cb: 回调函数
 *
 * @return:
 *   =0:success
 *  !=0:failure
 *
 * @details
 *
 */
uint32_t fe_set_uart_callback(FE_UART_CALLBACK cb);

#endif

