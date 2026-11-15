#ifndef __ADC_PT32L031_H
#define __ADC_PT32L031_H

#include "stdint.h"

/*
 * @brief ADC初始化
 *
 * @param [in] s：被调用函数主体的step
 *
 * @return: 无
 *
 * @details
 */
void fe_adc_init(unsigned char *step);

/*
 * @brief ADC关闭
 *
 * @param [in]：无
 *
 * @return: 无
 *
 * @details
 */
void fe_adc_kill(void);

/*
 * @brief 打开通道1
 *
 * @param [in] d:数据返回指定地址
 *
 * @return:无
 *
 * @details 单次转换
 */
void fe_adc_open_scm_in1(unsigned short *d);

/*
 * @brief 打开通道12
 *
 * @param [in] d:数据返回指定地址
 *
 * @return:无
 *
 * @details 单次转换，内部参考电压
 */
void fe_adc_open_scm_in12(unsigned short *d);

/*
 * @brief ADC Value Calculate
 *
 * @param [in] d:ADC数据
 *
 * @return:
 *
 * @details 单次转换，内部参考电压
 */
uint32_t CalculateActualVoltage(uint32_t data);

#endif

