/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_EEPROM_PT32L031.H
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
 * 	 RAM: 80bytes
 *   Name: EEPROM_DATA_TypeDef Rom
 *         FE_EEPROM_TypeDef Eeprom
 *
 * History :
 * 	 2024-5-25: 初版发布
 *
 */
#ifndef __FE_755LHA_EEPROM_PT32L031_H
#define __FE_755LHA_EEPROM_PT32L031_H
/* ====================================================== */
#include "stdint.h"
/* ====================================================== */
/*
 * @brief EEPROM 数据结构
 */
typedef struct
{
	unsigned char id[4];
	unsigned char reserved_0;
	unsigned char marking;
	unsigned char low_voltage;
	unsigned char end_voltage;
	unsigned char network_id[4];
	unsigned short network_address;//网络地址
	unsigned short address;//本机地址
}FE_755LHA_EEPROM_TypeDef;

/*
 * @brief EEPROM主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_eeprom_process_run(void);

/*
 * @brief 读EEPROM数据
 *
 * @param [in]:
 *
 * @return:
 * 
 * @details 需要放在主函数main()中，上电执行一次
 */
void fe_read_eeprom_data(void);

/*
 * @brief 查询EEPROM状态
 *
 * @param [in]:无
 *
 * @return:
 *   =0:EEPROM写入完成
 *   =1:EEPROM写入中
 *
 * @details 进入DeepSleep前，要确保EEPROM空闲状态
 */
uint32_t fe_get_eeprom_state(void);

/*
 * @brief 读EEPROM数据
 *
 * @param [in]:详见FE_755LHA_EEPROM_TypeDef结构
 *
 * @return:
 *   =0:success
 *   !=0:failure
 * 
 * @details 
 */
uint32_t fe_755LHA_read_eeprom_data(FE_755LHA_EEPROM_TypeDef *p);

/*
 * @brief 写EEPROM数据
 *
 * @param [in]:详见FE_755LHA_EEPROM_TypeDef结构
 *
 * @return:
 *   =0:success
 *   !=0:failure
 * 
 * @details 在启动写EEPROM时，FLASH会被锁定，因此需空闲时方可调用
 */
uint32_t fe_755LHA_write_eeprom_data(FE_755LHA_EEPROM_TypeDef *p);

/* --------------------------------------------------------------------------- */
#endif

