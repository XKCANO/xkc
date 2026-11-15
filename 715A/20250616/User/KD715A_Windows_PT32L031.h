#ifndef __KD715A_WINDOWS_PT32L031_H
#define __KD715A_WINDOWS_PT32L031_H


#include "pt32x031.h"
#include "KD715A_DEF.h"
#include "FE_755LHA_Uart_PT32L031.h"

typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned char counter;
	unsigned char counter1;//报警次数控制
	
	unsigned char offset;
	unsigned char reserve;
	unsigned short reserve1;
	
}Alarm_typedef;


typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned short value;
}typedef_common;

enum
{
	ONE_LOW_MODE = 0,//2ms
	ONE_MED_MODE,//10ms
	TWO_MED_MODE,//10ms
	FIRE_MODE,//测试
};

unsigned char alarm_init(unsigned char mode);
void led_lighten(void);




void remove_alarm(void);

void buzzer_sound(void);
void update_timer1(void);
void set_update_timer1(unsigned char state);
void UartCallBack(uint32_t p, uint32_t l);

extern Alarm_typedef buzzer;
extern Alarm_typedef led;
extern typedef_common update;


#endif

