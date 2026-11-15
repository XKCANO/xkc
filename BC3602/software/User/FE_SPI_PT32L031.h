/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_SPI_PT32L031.H
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
 * 	SPI通信公共函数
 *
 * History :
 * 	2024-6-15: 初版发布
 *
 */

#ifndef __FE_SPI_PT32L031_H
#define __FE_SPI_PT32L031_H

#include "stdint.h"

/*
 * @brief SPI主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 * 数据缓存长度20 bytes
 */
void fe_spi_process_run(void);

/*
 * @brief 查询SPI状态
 *
* @param [in] :无
 *
 * @return:
 *   =0:SPI空闲
 *   =1:SPI忙
 *
 * @details 进入DeepSleep前，要确保串口空闲状态
 */
uint32_t fe_get_spi_state(void);

/*
 * @brief SPI写数据
 *
 * @param [in] data 待发送数据首地址
 * @param [in] len 待发送数据长度
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区长度20
 */
uint32_t fe_spi_write(unsigned char *data, uint32_t len);

/*
 * @brief SPI读数据
 *
* @param [in] data: 数据缓存首地址
* @param [in] len: 待发送数据长度
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区长度20
 */
uint32_t fe_spi_read(unsigned char *data, uint32_t len);

/*
 * @brief 关闭SPI
 *
 * @param [in] :无
 *
 * @return:
 *   =0:SPI关闭
 *   =1:SPI忙
 *
 * @details 进入DeepSleep前，要确保SPI关闭状态
 */
uint32_t fe_enter_spi_sleep(void);

#endif

