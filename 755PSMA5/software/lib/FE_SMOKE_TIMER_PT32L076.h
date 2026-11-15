/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_TIMER_PT32L076.H
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
 * 	2024-12-24: 初版发布
 *
 */
#ifndef __FE_TIMER_PT32L076_H
#define __FE_TIMER_PT32L076_H

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
