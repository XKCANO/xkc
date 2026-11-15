/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_semaphore.h
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
 * 	
 *
 * History :
 * 	2024-12-27: 初版发布
 *
 */
#ifndef __FE_SEMAPHORE_H
#define __FE_SEMAPHORE_H

#include "stdint.h"

/*
 * @brief 查询信号标
 *
 * @param [in] : 
 *
 * @return:
 *    =0:空闲
 *    =1:占用
 *
 * @details: 非占用
 *   b8: BOOST_HOLD
 *   b9: RF_HOLD
 *  b10: BUZZER_HOLD
 */
uint32_t fe_get_semaphore_state(void);

/*
 * @brief 设置信号标
 *
 * @param [in] f: 位号
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 *    有效位号:8-32
 */
uint32_t fe_set_semaphore(uint32_t f);

/*
 * @brief 清除信号标
 *
 * @param [in] f: 位号
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 *    有效位号:8-32
 */
uint32_t fe_clear_semaphore(uint32_t f);

#endif
