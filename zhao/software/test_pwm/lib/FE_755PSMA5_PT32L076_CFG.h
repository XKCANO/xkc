/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_755PSMA5_PT32L031_CFG.H
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
 *   公共函数库
 *
 * History :
 * 	2025-1-4: 初版发布
 *
 */
#ifndef __FE_755PSMA5_PT32L076_CFG_H
#define __FE_755PSMA5_PT32L076_CFG_H

#include "stdint.h"

/*
 * @brief 初始化GPIO
 *
 * @param [in]:无
 *
 * @return:无
 * 
 * @details
 * 
 */
void fe_initializing_gpio(void);

/*
 * @brief 初始化RAM
 *
 * @param [in]:无
 *
 * @return:无
 * 
 * @details
 */
void fe_clear_ram(void);

/*
 * @brief 计算RTC-8秒的计时值
 *
* @param [in] s: step变量
 *
 * @return: 无
 * 
 * @details 计算依据以RTC分频系数31为基准，以Timer2为基准计时
 * 由于使用中断，因此计算期间不能使用其它中断
 * 计算时间约500ms
 */
void fe_calculate_sleep_8s(unsigned char *s);

/*
 * @brief 获得RTC-8秒的计时值
 *
 * @param [in] 无
 *
 * @return: 计时值
 * 
 * @details
 * LSI: 25~38KHz (31.5KHz)
 * -40~+85: +/-10%
 */
uint32_t fe_get_sleep_8s(void);

#endif

