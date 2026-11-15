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
#ifndef __FE_755LHA_PT32L031_CFG_H
#define __FE_755LHA_PT32L031_CFG_H

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


#endif

