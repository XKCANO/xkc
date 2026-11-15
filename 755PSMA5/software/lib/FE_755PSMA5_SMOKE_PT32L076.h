/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_755PSMA5_SMOKE_PT32L076.H
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
 * 	 2024-12-31: 初版发布
 *
 */
#ifndef __FE_755PSMA5_SMOKE_PT32L076_H
#define __FE_755PSMA5_SMOKE_PT32L076_H

#include "stdint.h"

/*
 * @details: 回调函数
 */
typedef void (*FE_SMOKE_CALLBACK)(uint32_t param);

/*
 * @brief SMOKE主体运行函数
 *
 * @param[in]: 无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_smoke_process_run(void);

/*
 * @brief 设置SMOKE回调函数
 *
 * @param [in] p: callback
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_set_smoke_callback(FE_SMOKE_CALLBACK cb);

/*
 * @brief 启动SMOKE
 *
 * @param [in] mode: 
 *    =0:normal mode
 *    =1:initial mode
 *    =2:debug mode
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_start_up_smoke_process(uint32_t mode);

/*
 * @brief 启动实时采样
 *
 * @param [in] : 无
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_start_up_smoke_sampling(void);

/*
 * @brief 停止实时采样
 *
 * @param [in] : 无
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_stop_smoke_sampling(void);

/*
 * @brief 设置主电源供电
 *
 * @param [in] : 无
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_set_main_power_source(void);

/*
 * @brief 设置备用电源供电
 *
 * @param [in] : 无
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_set_backup_power_source(void);

/*
 * @brief 查询SMOKE状态
 *
 * @param [in] state: 
 *    b0: initializing
 *    b1: debugging
 *    b2: acting
 *    b3: alarming
 *    b6: chamber trouble
 *    b7: chamber dust
 *
 * @return:
 *    =0:空闲
 *    =1:忙
 *
 * @details
 */
uint32_t fe_get_smoke_state(void);

#endif

