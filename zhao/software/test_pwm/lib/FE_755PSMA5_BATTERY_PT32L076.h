/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_755PSMA5_BATTERY_PT32L076.H
 * Version : 0.1
 * 32bit MCU : PT32L076
 * Cortex : Cortex-M0
 *
 * Compiler : 
 *   Keil ARM 5.18 Compiler
 *
 * Pack:
 *   PAI-IC.PT32x076_DFP.1.1.0
 *
 * Author : 
 *
 *
 * Description : 
 *   RAM: 16bytes
 *   Name: FE_BATTERY_TypeDef Battery
 *
 * History :
 * 	2025-1-4: 初版发布
 *
 */
#ifndef __FE_755PSMA5_BATTERY_PT32L076_H
#define __FE_755PSMA5_BATTERY_PT32L076_H

#include "stdint.h"

/*
 * @brief 回调函数
 *
 * @param [in] param: 
 *    b0: ready
 *    b4: low battery
 *    b5: end battery
 *
 * @details: 
 */
typedef void (*FE_BATTERY_CALLBACK)(uint32_t param);

/*
 * @brief BATTERY主体运行函数
 *
 * @param[in]: 无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_battery_process_run(void);

/*
 * @brief 设置BATTERY回调函数
 *
 * @param [in] p: callback
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_set_battery_callback(FE_BATTERY_CALLBACK cb);

/*
 * @brief 启动BATTERY
 *
 * @param [in] mode: 
 *    =0:normal mode
 *    =1:debug mode
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_start_up_battery_process(uint32_t mode);

/*
 * @brief 查询Battery状态
 *
 * @param [in]:
 *
 * @return:
 *    =0:空闲
 *    =1:忙
 *
 * @details
 */
uint32_t fe_get_battery_state(void);

#endif




