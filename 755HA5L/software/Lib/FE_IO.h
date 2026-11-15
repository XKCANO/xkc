/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_IO.H
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
 * Description : 公共函数库
 *
 * History :
 * 	2025-3-28: 初版发布
 *
 */
#ifndef __FE_IO_H
#define __FE_IO_H

#include "stdint.h"

/*
 * @brief 函数声明
 */
typedef void (*GO_TO_TypeDef)(void);
typedef void (*FLASH_ERASE_PAGE_TypeDef)(uint32_t addr);
typedef void (*FLASH_WRITE_PAGE_TypeDef)(uint32_t d, uint32_t s, uint32_t l);

/*
 * @brief 动态申请RAM
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
uint32_t malloc_ram(uint32_t fp);

/*
 * @brief Byte数组复制
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
void mem_data_copy(unsigned char *d, unsigned char *s, uint32_t l);

/*
 * @brief Word数组复制
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
void mem_word_copy(uint32_t *d, uint32_t *s, uint32_t l);

/*
 * @brief Word数组清零
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
void mem_word_clear(uint32_t *p, uint32_t l);

/*
 * @brief Byte数组清零
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
void mem_byte_clear(unsigned char *p, uint32_t l);

/*
 * @brief Byte数组初始化设定
 *
 * @param[in]:
 *
 * @return:
 *
 * @details 
 */
void mem_byte_set(unsigned char *p, unsigned char d, uint32_t l);

#endif

