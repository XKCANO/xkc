#ifndef __755LPSMA5_WINDOWS_PT32L076_H
#define __755LPSMA5_WINDOWS_PT32L076_H


#include "PT32x076.h"
#include "755PSMA5_DEF.h"
#include "FE_755PSMA5_UART_PT32L076.h"


/* --------------------------------------------------------------------------- */
enum
{
	TEST_MODE,//测试模式
	FIRE_MODE,//火灾报警模式
	EXTERNAL_MODE,//有线互联报警模式/Relay 互联报警模式
	EXT_ERROR_MODE,//有线互联错误报警模式
	
	ONE_LOW_MODE,//低亮度闪一次
	TWO_LOW_MODE,//低亮度闪两次
	
	ONE_MED_MODE,//中亮度闪一次

	LOW_BAT_MODE,
	SENSOR_FAULT_MODE,
	HUSH_MODE,
};

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned char counter;
	unsigned char offset;
	
}Alarm_typedef;

extern Alarm_typedef led;
extern Alarm_typedef buzzer;
extern Alarm_typedef update;

/* --------------------------------------------------------------------------- */
void alarm_cfg(uint8_t mode);
void remove_alarm(void);
void led_lighten(void);
void buzzer_sound(void);
void update_timer1(void);
void set_connect(unsigned char flag);

/* --------------------------------------------------------------------------- */
void smoke_callback(uint32_t state);
void battery_callback(uint32_t state);
void uart_callback(uint32_t p, uint32_t l);

/* --------------------------------------------------------------------------- */
#endif
