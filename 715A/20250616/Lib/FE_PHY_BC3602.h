/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_PHY_BC3602.H
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
 *   RAM: 92bytes
 *   Name: FE_PHY_TypeDef phy
 *
 * History :
 * 	2024-6-15: 初版发布
 *
 */

#ifndef __FE_PHY_BC3602_H
#define __FE_PHY_BC3602_H

#include "stdint.h"

#define  PA_H0DBM   0    // 0dBm
#define  PA_H5DBM   1    // +5dBm
#define  PA_H10DBM  2    // +10dBm
#define  PA_H13DBM  3    // +13dBm

/*
 * @details: 回调函数
 */
typedef void (*FE_PHY_CALLBACK)(unsigned char *p, uint32_t l);

/*
 * @brief PHY主体运行函数
 *
 * @param[in]: 无
 *
 * @return: 无
 *
 * @details 需要放在主函数main()中
 * 
 */
void fe_phy_process_run(void);

/*
 * @brief 查询PHY状态
 *
 * @param [in]:无
 *
 * @return:
 *   =0: 空闲
 *   =1: 深度睡眠
 *   =0xFFFFFFFF: 忙
 *
 * @details
 */
uint32_t fe_get_phy_state(void);

/*
 * @brief 获取RSSI
 *
 * @param [in] mode: 0
 *
 * @return: rssi
 *    
 *
 * @details
 */
uint32_t fe_get_rssi(uint32_t _mode);

/*
 * @brief 设置发射工作参数
 *
 * @param [in] tx_mode : 0
 * @param [in] tx_power: 发射功率
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details
 */
uint32_t fe_set_phy_tx_parameter(uint32_t tx_mode, uint32_t tx_power);

/*
 * @brief 设置工作参数（同步字节和回调函数）
 *
 * @param [in] sw: 同步字节
 * @param [in] cb: 回调函数
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details 同步字节长度默认4个字节
 *
 */
uint32_t fe_set_phy_parameter(unsigned char *sw, FE_PHY_CALLBACK cb);

/*
 * @brief RF发射数据
 *
 * @param [in] data: 待发送数据首地址
 * @param [in] len: 待发送数据长度
 * @param [in] tx_time: 发射时间
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区最大长度20
 *
 */
uint32_t fe_phy_send_data(unsigned char *data, uint32_t len, uint32_t tx_time, uint32_t idle_time);

/*
 * @brief RF接收数据
 *
 * @param [in] len: 接收发送数据长度
 * @param [in] rx_time: 接收等待时间
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区最大长度20
 *
 */
uint32_t fe_phy_receive_data(uint32_t len, uint32_t rx_time, uint32_t idle_time);

/*
 * @brief RF发射数据
 *
 * @param [in] data: 待发送数据首地址
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 广播指令, 发送数据长度6
 *
 */
uint32_t fe_phy_pluse_send_data(unsigned char *data);

/*
 * @brief RF监听数据
 *
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *
 */
uint32_t fe_phy_moniting_data(uint32_t idle_time);

/*
 * @brief 退出
 *
 * @param [in]: 无
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *
 */
uint32_t fe_phy_quit(void);

#endif

