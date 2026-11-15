#ifndef __755PSMA5L_TIMER_PT32L0_H
#define __755PSMA5L_TIMER_PT32L0_H


#include "stdint.h"
#include "755PSMA5L_DEF.h"


/* --------------------------------------------------------------------------- */
#define   WDG_CR_ENABLE             ((u32)0x00000001)
#define   WDG_LockKey_Unlock        ((u32)0x1ACCE551)
#define   WDG_LockKey_Lock          ((u32)0x00000000)
#define   WWDG_CR2_KEYVALUE         ((u32)0xACBD0000)

#define 	TIMER_SIZE		17

/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t t[TIMER_SIZE];
	uint32_t mr0;
}TIMER_TypeDef;
extern TIMER_TypeDef timer5;

/* --------------------------------------------------------------------------- */
void set_timer1(void);
void close_timer1(void);

/* --------------------------------------------------------------------------- */
void settimer5(void);
void checktimer5(void);
void closetimer5(void);

/* --------------------------------------------------------------------------- */
void open_iwdg(void);
void feed_iwdg(void);
void close_iwdg(void);

/* --------------------------------------------------------------------------- */
void open_swdg(void);
void feed_swdg(void);
void close_swdg(void);
void close_wdog(void);

/* --------------------------------------------------------------------------- */
#endif
