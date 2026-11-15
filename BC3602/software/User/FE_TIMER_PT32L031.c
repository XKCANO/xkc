#include "FE_TIMER_PT32L031.h"
#include "FE_HEAT_CFG.h"
#include "PT32X031.h"

/* =========================================================================== */
FE_TIMER_TypeDef Timer;
/* =========================================================================== */

/*
System Tick Timer is a 24-bit downcounter.
HCLK: 24MHz
*/
void fe_set_system_tick_timer(void)
{
	SysTick->LOAD = 24000; //1ms
	SysTick->VAL = 24000;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}
/*
** Check System Tick Timer
*/
void fe_check_system_tick_timer(void)
{
	uint32_t i;
	if((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0)
	{
		i = 0;
		do{
			Timer.t[i]++;
			i++;
		}while(i < TIMER_SIZE);
	}
}
/*
** Kill System Tick Timer
*/
void fe_kill_system_tick_timer(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
/* 
** Set Timer2 External Trigger
** PCLK: 24MHz
*/
void fe_set_timer2_et(uint32_t t)
{	
	//CLK: 24M / (23 + 1) = 1MHz
	TIM2->PR = 23;
	TIM2->MCR = TIM_MCR_DIR + TIM_MCR_MR0S;
	TIM2->MR0 = t;

  TIM2->TCR |= TIM_TCR_UPDATE;
	__NOP();
	__NOP();
	__NOP();
	TIM2->ISR |= TIM_ISR_OV;
	TIM2->TCR |= TIM_TCR_EN;
}
/*
** Kill Timer2 External Trigger
*/
void fe_kill_timer2_et(void)
{
	TIM2->ISR |= TIM_ISR_OV;
	TIM2->TCR = 0;
	TIM2->MCR = 0;
}

/*---------------------------------------------------------------------------------------------------------*/

