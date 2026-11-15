#ifndef __WCS_KEYBOARD_M0518_H__
#define __WCS_KEYBOARD_M0518_H__


#include "wcs_adc_m0518.h"
#include "wcs_timer_m0518.h"


typedef struct
{
	unsigned char value1;
	unsigned char value2;
  unsigned char value3;
	unsigned char reserve;
  
}KEY_TYPEDEF;
extern KEY_TYPEDEF key;


void Scan_Key_Process(unsigned short module,unsigned char *value);

void Key1_Downevent(void);
void Key1_Upevent(void);
void Key2_Downevent(void);
void Key2_Upevent(void);
void Key3_Downevent(void);
void Key3_Upevent(void);

#endif


