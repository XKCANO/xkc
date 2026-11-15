#ifndef __KD715A_TIMER_PT32L0_H
#define __KD715A_TIMER_PT32L0_H
/* --------------------------------------------------------------------------- */
#include "stdint.h"
#include "KD715A_DEF.h"

/* --------------------------------------------------------------------------- */
#define 	TIMER3_SIZE		15

/* --------------------------------------------------------------------------- */
#define   WDG_WriteAccess_Enable     ((uint32_t)0x1ACCE551)
#define   WDG_WriteAccess_Disable    ((uint32_t)0x00000000)
/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t t[TIMER3_SIZE];
}TIMER3_TypeDef;
extern TIMER3_TypeDef Timer3;
/* --------------------------------------------------------------------------- */
void set_timer3(void);
void check_timer3(void);
void kill_timer3(void);
/* --------------------------------------------------------------------------- */
void open_timer4(void);
void close_timer4(void);
/* --------------------------------------------------------------------------- */
void set_alarm(unsigned char flag);
void open_buzzer(void);
void close_buzzer(void);
void del_alarm(void);
/* --------------------------------------------------------------------------- */
void open_iwdg(void);
void feed_iwdg(void);
void close_iwdg(void);
/* --------------------------------------------------------------------------- */
void open_swdg(void);
void feed_swdg(void);
void close_swdg(void);
/* --------------------------------------------------------------------------- */
void system_irq_proc_run(void);
/* --------------------------------------------------------------------------- */
extern uint16_t timer4_T8s;


#endif
