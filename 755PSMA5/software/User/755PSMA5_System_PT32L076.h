#ifndef __755LPSMA5_SYSTEM_PT32L076_H
#define __755LPSMA5_SYSTEM_PT32L076_H


#include "755PSMA5_Windows_PT32L076.h"
#include "FE_SMOKE_TIMER_PT32L076.h"
#include "FE_755PSMA5_SMOKE_PT32L076.h"
#include "FE_755PSMA5_BATTERY_PT32L076.h"
#include "755PSMA5_Keyboard_PT32L076.h"
#include "755PSMA5_Windows_PT32L076.h"


/* --------------------------------------------------------------------------- */
void clear_sram(void);
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);

/* --------------------------------------------------------------------------- */
#endif


