/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_TIMER_PT32L031.H
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
 *   公共函数库
 *   RAM: 24bytes
 *   Name: FE_TIMER_TypeDef Timer
 *
 * History :
 * 	2024-6-12: 初版发布
 *
 */
#ifndef __FE_TIMER_PT32L031_H
#define __FE_TIMER_PT32L031_H

/*
 * @brief 启动
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_set_system_tick_timer(void);

/*
 * @brief 检查
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_check_system_tick_timer(void);

/*
 * @brief 终止
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_kill_system_tick_timer(void);

#endif
