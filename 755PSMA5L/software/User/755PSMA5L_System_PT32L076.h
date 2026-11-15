#ifndef __755LPSMA5_SYSTEM_PT32L076_H
#define __755LPSMA5_SYSTEM_PT32L076_H


#include "755PSMA5L_DEF.h"
#include "755PSMA5L_Windows_PT32L076.h"
#include "755PSMA5L_Keyboard_PT32L076.h"
#include "FE_SMOKE_TIMER_PT32L076.h"
#include "FE_755PSMA5L_BATTERY_PT32L076.h"
#include "FE_755PSMA5L_SMOKE_PT32L076.h"
#include "FE_755PSMA5L_UART_PT32L076.h"
#include "755PSMA5L_Message_PT32L076.h"


/* --------------------------------------------------------------------------- */
void clear_sram(void);
void system_init_process_run(void);
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);

/* --------------------------------------------------------------------------- */
#endif


