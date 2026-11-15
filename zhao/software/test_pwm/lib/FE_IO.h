/*
**
*/
#ifndef __FE_IO_H
#define __FE_IO_H

#include "stdint.h"

typedef void (*GO_TO_TypeDef)(void);
typedef void (*FLASH_ERASE_PAGE_TypeDef)(uint32_t addr);
typedef void (*FLASH_WRITE_PAGE_TypeDef)(uint32_t d, uint32_t s, uint32_t l);

uint32_t malloc_ram(uint32_t fp);

void mem_data_copy(unsigned char *d, unsigned char *s, uint32_t l);
void mem_word_copy(uint32_t *d, uint32_t *s, uint32_t l);
void mem_word_clear(uint32_t *p, uint32_t l);
void mem_byte_clear(unsigned char *p, uint32_t l);

#endif

