#ifndef __755LHA_WINDOWS_PT32L031_H
#define __755LHA_WINDOWS_PT32L031_H


#include "pt32x031.h"
#include "755LHA_DEF.h"
#include "FE_755LHA_Uart_PT32L031.h"


/****************** Bit definition for GPIO_AFS1 register  ********************/
#define   GPIO_AFS_FUN0                 ((uint32_t)0x00000000)
#define   GPIO_AFS_FUN1                 ((uint32_t)0x00000001)
#define   GPIO_AFS_FUN2                 ((uint32_t)0x00000002)
#define   GPIO_AFS_FUN3                 ((uint32_t)0x00000003)
#define   GPIO_AFS_FUN4                 ((uint32_t)0x00000004)
#define   GPIO_AFS_FUN5                 ((uint32_t)0x00000005)
#define   GPIO_AFS_FUN6                 ((uint32_t)0x00000006)
#define   GPIO_AFS_FUN7                 ((uint32_t)0x00000007)
/*******************  Bit definition for PWM_CMR register  *******************/ 
#define   PWM_CMR_MC4_MODE1             ((uint32_t)0x00001000)
#define   PWM_CMR_MC4_MODE2             ((uint32_t)0x00002000)
#define   PWM_CMR_MC4_MODE3             ((uint32_t)0x00003000)
/* --------------------------------------------------------------------------- */
#define   NET_FIRE_ALARM   0x22
#define   NET_CLOSE_ALARM  0x33
#define   NET_TEST_ALARM   0xAA
#define   NET_HUSH_ALARM   0xBB
#define   NET_FIND_ALARM   0xCC

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned char counter;
	unsigned char offset;
}Alarm_typedef;
extern Alarm_typedef buzzer;
extern Alarm_typedef red_led;
extern Alarm_typedef yel_led;

typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned short value;
}typedef_common;
extern typedef_common update;

/* --------------------------------------------------------------------------- */
enum
{
	TEST_MODE = 0,
	FIRE_MODE,
	REDLED_ONCE_LOW,
	REDLED_ONCE_MED,
	YELLOWLED_ONCE_LOW,
	YELLOWLED_TWICE_LOW,
	LOW_BAT_MODE,
	SENSOR_FAULT_MODE,
	NET_ALARM_MODE,
	BUZZER_ONCE,
	EXT_ERROR,
	NET_WORK_SECCESS,
	HUSH_MODE,
};

/* --------------------------------------------------------------------------- */
enum
{
	CLOSE_ALL = 0,
	I_OUT,
	IO_OUT,
	I_IO_OUT,
};


/* --------------------------------------------------------------------------- */
void remove_alarm(void);
void alarm_cfg(unsigned char mode);
void buzzer_sound(void);
void red_led_lighten(void);
void yellow_led_lighten(void);
void set_wire_connect(unsigned char flag);
void set_wireless_connect(unsigned char cmd);
void update_timer1(void);
void uart_callback(uint32_t p, uint32_t l);

/* --------------------------------------------------------------------------- */
#endif

