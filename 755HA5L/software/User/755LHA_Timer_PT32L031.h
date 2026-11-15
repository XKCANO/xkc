#ifndef __755LHA_TIMER_PT32L0_H
#define __755LHA_TIMER_PT32L0_H


#include "stdint.h"
#include "755LHA_DEF.h"

/* --------------------------------------------------------------------------- */
#define 	TIMER3_SIZE		20

/* --------------------------------------------------------------------------- */
#define   WDG_WriteAccess_Enable     ((uint32_t)0x1ACCE551)
#define   WDG_WriteAccess_Disable    ((uint32_t)0x00000000)

/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t t[TIMER3_SIZE];
	uint32_t timer4_T8s;
}TIMER3_TypeDef;
extern TIMER3_TypeDef timer3;

/* --------------------------------------------------------------------------- */
void set_timer3(void);
void check_timer3(void);
void kill_timer3(void);

void open_timer4(void);

void set_timer1(void);
void open_buzzer(void);
void close_buzzer(void);
void close_timer1(void);

void open_iwdg(void);
void feed_iwdg(void);
void close_iwdg(void);

void open_swdg(void);
void feed_swdg(void);
void close_swdg(void);
void close_wdog(void);
  
/* --------------------------------------------------------------------------- */
#endif
