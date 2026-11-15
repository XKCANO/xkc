#ifndef __KD715A_SYSTEM_PT32L031_H
#define __KD715A_SYSTEM_PT32L031_H

#include "pt32x031.h"

#include "FE_MATH.h"
#include "FE_TIMER_PT32L031.h"
#include "FE_755LHA_PT32L031_CFG.h"
#include "FE_755LHA_Uart_PT32L031.h"

#include "KD715A_Windows_PT32L031.h"
#include "KD715A_Keyboard_PT32L031.h"


/* --------------------------------------------------------------------------- */
typedef struct
{
  unsigned char step;
	unsigned char mode;
}START_TYPEDEF;
extern START_TYPEDEF start;
/* --------------------------------------------------------------------------- */
void system_start_proc_run(void);
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);
/* --------------------------------------------------------------------------- */
#endif
