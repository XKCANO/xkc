/*
**
*/
#include "FE_IO.h"
#include <stdio.h>
#include "cmsis_armcc.h"



/*
** data copy
*/
void mem_data_copy(unsigned char *d, unsigned char *s, uint32_t l)
{
	uint32_t i = 0;
	do{
		d[i] = s[i];
		i++;
	}while(i < l);
}

/*
** word copy
*/
void mem_word_copy(uint32_t *d, uint32_t *s, uint32_t l)
{
	uint32_t i = 0;
	do{
		d[i] = s[i];
		i++;
	}while(i < l);
}

/*
**
*/
void mem_word_clear(uint32_t *p, uint32_t l)
{
	uint32_t i = 0;
	do{
		p[i] = 0;
		i++;
	}while(i < l);
}

/*
**
*/
void mem_byte_clear(unsigned char *p, uint32_t l)
{
	uint32_t i = 0;
	do{
		p[i] = 0;
		i++;
	}while(i < l);
}


