/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_MATH.H
 * Version : 0.1
 * 32bit MCU : 
 * Cortex : Cortex-M0
 *
 * Compiler : 
 *   Keil ARM 5.18 Compiler
 *
 * Pack:
 *
 *
 * Author : 
 *   Tang
 *
 * Description : 
 *   公共函数库
 *
 * History :
 * 	2024-5-27: 初版发布1.0.0
 *  2025-1-4 : 1.0.1
 */
#ifndef __FE_MATH_H
#define __FE_MATH_H

#include "stdint.h"

#define  fe_math_less    0xFFFFFFFF
#define  fe_math_equal   0
#define  fe_math_greater 1

/*
 * @brief
 */
typedef struct
{
	uint32_t average;
	uint32_t max;
	uint32_t min;
	uint32_t u;
}FE_CURVE_AVERAGE_TypeDef;

/*
 * @brief
 */
typedef struct
{
	uint16_t t_max;
	uint16_t y_max;
	uint16_t t_min;
	uint16_t y_min;
	uint16_t y_u;
}FE_CURVE_AMPLITUDE_TypeDef;

/*
 * @brief 数据白化
 *
 * @param [in] p 数据缓存首地址
 * @param [in] l 数据长度
 *
 *
 * @return: 无
 * 
 * @details
 */
void fe_data_whitening_pn7(unsigned char *p, uint32_t l);

/*
 * @brief CRC校验
 *
 * @param [in] p 数据缓存首地址
 * @param [in] l 数据长度
 *
 *
 * @return: 校验值
 * 
 * @details
 *   CRC-CCITT = X16+X12+X5+1(0x11021)
 *
 */
uint32_t fe_calculate_crc(unsigned char *p, unsigned char l);

/*
 * @brief CRC校验
 *
 * @param [in] p 数据缓存首地址
 * @param [in] l 数据长度
 *
 *
 * @return: 校验值
 * 
 * @details
 *   CRC16 = X16+X15+X5+1(0x18021)
 *
 */
uint32_t fe_calculate_crc16(unsigned char *p, unsigned char l);

/*
 * @brief 修改AD值
 *
 * @param [in] data: 当前值
 * @param [in] vref: 当前参考电压值
 *
 * @return: 修正后的AD值
 *
 * @details
 */
uint32_t fe_correcting_ad_data(uint32_t data, uint32_t vref);



/*
 * @brief 获取平均值
 *
 * @param [in] p：数据缓存首地址
 * @param [in] l：数据长度
 *
 * @return: 平均值
 *
 * @details
 */
uint32_t fe_get_average(uint16_t *p, uint32_t l);

/*
 * @brief 获取最大值
 *
 * @param [in] p：数据缓存首地址
 * @param [in] l：数据长度
 *
 * @return: 最大值
 *
 * @details
 */
uint32_t fe_get_maximum(uint16_t *p, uint32_t l);

/*
 * @brief 获取最小值
 *
 * @param [in] p：数据缓存首地址
 * @param [in] l：数据长度
 *
 * @return: 最小值
 *
 * @details
 */
uint32_t fe_get_minimum(uint16_t *p, uint32_t l);

/*
 * @brief 获取最大增幅值
 *
 * @param [in] p：数据缓存首地址
 * @param [in] l：数据长度
 *
 * @return: 增幅值
 *
 * @details: 
 * 最大值-最小值
 */
uint32_t fe_get_increment(uint16_t *p, uint32_t l);

/*
 * @brief 一维浮点数组左移
 *
 * @param [in] p 数据缓存首地址
 * @param [in] n 数据长度
 *
 * @return: 无
 * 
 * @details
 *   浮点数
 */
void fe_float_data_move_to_left(float *p, uint32_t l);

/*
 * @brief 一维浮点数组右移
 *
 * @param [in] p 数据缓存首地址
 * @param [in] n 数据长度
 *
 * @return: 无
 * 
 * @details
 *   浮点数
 */
void fe_float_data_move_to_right(float *p, uint32_t l);
	
/*
 * @brief 一维数组左移
 *
 * @param [in] p 数据缓存首地址
 * @param [in] n 数据长度
 *
 * @return: 无
 * 
 * @details 
 */
void fe_data_move_to_left(uint16_t *p, uint32_t l);

/*
 * @brief 一维数组右移
 *
 * @param [in] p 数据缓存首地址
 * @param [in] n 数据长度
 *
 * @return: 无
 * 
 * @details 
 */
void fe_data_move_to_right(uint16_t *p, uint32_t l);

/*
 * @brief Byte一维数组左移
 *
 * @param [in] p 数据缓存首地址
 * @param [in] n 数据长度
 *
 * @return: 无
 * 
 * @details:
 */
void fe_byte_data_move_to_left(unsigned char *p, uint32_t l);



#endif

