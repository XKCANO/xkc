/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_755LHA_MAC.H
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
 * 	 RAM: 32bytes
 *   Name: FE_MAC_TypeDef mac
 *
 * History :
 * 	2024-6-26: 初版发布
 *
 */

#ifndef __FE_755LHA_MAC_H
#define __FE_755LHA_MAC_H

#include "stdint.h"

#define  FE_FIRE_ALARM_CMD  0x22
#define  FE_STOP_ALARM_CMD  0x33
#define  FE_TEST_CMD        0xAA
#define  FE_HUSH_CMD        0xBB
#define  FE_FIND_CMD        0xCC

/*
 * @details: 回调函数
 */
typedef void (*FE_MAC_CALLBACK)(uint32_t cmd);

/*
 * @brief MAC主体运行函数
 *
 * @param[in]: 无
 *
 * @return: 无
 *
 * @details 需要放在主函数main()中
 * 
 */
void fe_755lha_mac_process_run(void);

/*
 * @brief 查询MAC状态
 *
 * @param [in]: 无
 *
 * @return:
 *   =0:空闲
 *   !=0:忙
 *
 * @details
 */
uint32_t fe_get_755lha_mac_state(void);

/*
 * @brief 接收指令
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
uint32_t fe_755lha_mac_receive_data(void);

/*
 * @brief 发送指令
 *
 * @param [in] cmd: 指令
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *
 */
uint32_t fe_755lha_mac_send_data(uint32_t cmd);

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
uint32_t fe_755lha_mac_quit(void);

/*
 * @brief 设置MAC回调函数
 *
 * @param [in] cb: 回调函数
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *  
 *  
 */
uint32_t fe_set_755lha_mac_callback(FE_MAC_CALLBACK cb);

#endif

