#ifndef __KD715A_KEYBOARD_PT32L031_H
#define __KD715A_KEYBOARD_PT32L031_H

#include "pt32x031.h"
#include "KD715A_DEF.h"


typedef struct
{
	unsigned char test_value;
	unsigned char mute_value;
	unsigned char flag;
	unsigned char *value;
	
}KEY_TYPEDEF;
extern KEY_TYPEDEF key;



void PA_Handler(void);
void scan_key_process(unsigned char *v);
void key_upevent(unsigned char *v);
void key_downevent(unsigned char *v);
void keyshort_event(void);
void keylong_event(void);


extern KEY_TYPEDEF key;


#endif
