/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_SMOKE_EEPROM_PT32L076.H
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
 *   RAM: 212bytes
 *   Name: EEPROM_DATA_TypeDef Rom
 *         FE_EEPROM_TypeDef Eeprom
 *
 * History :
 * 	2024-12-26: 初版发布
 *
 */
#ifndef __FE_SMOKE_EEPROM_PT32L076_H
#define __FE_SMOKE_EEPROM_PT32L076_H
/* ====================================================== */
#include "stdint.h"
/* ====================================================== */

/*
 * @brief EEPROM主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中的while内
 */
void fe_eeprom_process_run(void);

/*
 * @brief 查询EEPROM状态
 *
 * @param [in]:无
 *
 * @return:
 *   =0 : 空闲
 *   !=1: 忙
 *
 * @details 进入DeepSleep前，要确保EEPROM空闲状态
 */
uint32_t fe_get_eeprom_state(void);

/*
 * @brief 读EEPROM数据
 *
 * @param [in]:
 *
 * @return:
 * 
 * @details 需要放在主函数main()中，上电执行一次
 */
void fe_smoke_read_eeprom_data(void);

/*
 * @brief 写EEPROM数据
 *
 * @param [in]:
 *
 * @return:
 *   =0:success
 *   !=0:failure
 * 
 * @details 在启动写EEPROM时，FLASH会被锁定，因此需空闲时方可调用
 */
//uint32_t fe_smoke_write_eeprom_data(void);

/* --------------------------------------------------------------------------- */
#endif

