/*
The ultra-low-power STM32L031x4/6 devices include three general-purpose timers, 
one low- power timer (LPTM), two watchdog timers and the SysTick timer.
1, General-purpose timers (TIM2, TIM21 and TIM22)
2, Low-power Timer (LPTIM)
3, SysTick timer
   < This timer is dedicated to the OS, but could also be used as a standard downcounter.
   It is based on a 24-bit downcounter with autoreload capability and a programmable clock source.
   It features a maskable system interrupt generation when the counter reaches '0'. >
4, Independent watchdog (IWDG)
5, Window watchdog (WWDG)
   < The window watchdog is based on a 7-bit downcounter that can be set as free-running. 
	 It can be used as a watchdog to reset the device when a problem occurs. It is clocked from the main clock. 
	 It has an early warning interrupt capability and the counter can be frozen in debug mode.>
*/
#include <stdio.h>
#include "PT32X031.h"
#include "FE_755LHA_Timer_PT32L031.h"
//#include "FE_755LHA_System_PT32L031.h"
//#include "pt32x031_gpio.h"

/* =========================================================================== */
TIMER3_TypeDef Timer3;
SystemCounter system_count;
/* =========================================================================== */

/* 
** Set Timer3
** PCLK: 24MHz
*/
void set_timer3(void)
{
	TIM3->PR = 23;
	TIM3->MCR = TIM_MCR_DIR + TIM_MCR_MR0R + TIM_MCR_MR0I;
	TIM3->MR0 = 1000;
	
  TIM3->TCR |= TIM_TCR_UPDATE;
	__NOP();
	__NOP();
	__NOP();
	
	TIM3->ISR |= TIM_ISR_OV;
	TIM3->TCR |= TIM_TCR_EN;
}
/*
** Check System Tick Timer
*/
void check_timer3(void)
{
	unsigned char i;
	
	if(TIM3->ISR & TIM_ISR_OV)
	{
		TIM3->ISR |= TIM_ISR_OV;
//		CMSDK_PB->DATAOUT ^= 0x40;
		i = 0;
		do{
			Timer3.t[i]++;
			i++;
		}while(i < TIMER3_SIZE);
	}
}

void kill_timer3(void)
{
	TIM3->ISR |= TIM_ISR_OV;
	TIM3->TCR = 0;
	TIM3->MCR = 0;
}
/*
** Open Timer1
** output PWM on CH4
** PCLK: 24MHz
** PA11 --> HB --> FUN1 --> TIM1_CH4
** PA12 --> HS --> FUN1 --> TIM1_CH4N
*/
void OpenTimer1_CH4_PWM(void)
{
	//CMSDK_PA->ALTFUNCSET1 |= (GPIO_AF_1 << 16) + (GPIO_AF_1 << 12);

	PWM1->PR = 24-1;
	PWM1->DT = 50;
	PWM1->TCR = 0;
	PWM1->MCR = 0;
	PWM1->CMR = 0;
	PWM1->CCR = 0;
	PWM1->INT_RPT = 0;
	PWM1->MR0 = 294 - 1;
	PWM1->MR4 = 147;
	//PWM1->CMR = (COMPAER_MODE2 << 12) + (PWM_IDLE_LOW << 3);
	PWM1->CMR |= PWM_CMR_PWM4n_EN;
	PWM1->TCR |= PWM_TCR_EN;
}
/*
** Close Timer1
*/
void CloseTimer1(void)
{
	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC12 + GPIO_AFC_AFC11;

	PWM1->TCR = 0;
	PWM1->CMR = 0;
	PWM1->ISR |= PWM_ISR_MR4 + PWM_ISR_MR3 + PWM_ISR_MR2 + PWM_ISR_MR1 + PWM_ISR_MR0;
	PWM1->MCR = 0;
}

/*
** Open Timer4 (LpTimer)
** LSI: 25 ~ 38KHz --> 31.5KHz
** -40 ~ +85: +/-10%
*/
void open_timer4(void)
{
	TIM4->PR = 31;
	TIM4->MCR |= 0x3;
	
	//8s -> 8000->9.1s  //1. 8s->7032
	//8s -> 7032->8.73s //2. 7.98s->6444  8.03s->6484
	TIM4->MR0 = 6444;  

	TIM4->TCR |= TIM_TCR_UPDATE;
	
	__NOP();
	__NOP();
	__NOP();
	
	TIM4->ISR |= TIM_ISR_OV;
	TIM4->TCR |= TIM_TCR_EN;
	
	NVIC_EnableIRQ(TIMER4_IRQn);
}

/*
** Close Timer4
*/
void close_timer4(void)
{
	TIM4->ISR = TIM_ISR_OV;
	TIM4->TCR = 0;
	TIM4->MCR &= ~0x2;
	TIM4->MR0 = 0;
	
	__NOP();
	__NOP();
	__NOP();
	
}

/*
** Open System Window Watchdog
** PCLK: 24MHz
*/
void OpenSystemWatchdog(void)
{
	SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->RLR = 2400000;  //100ms
	SWDG->FWDG = 0xFFFFFFFF;
	SWDG->CR |= WDG_CR_RSTE;
  SWDG->CR |= WDG_CR_INTE;
	SWDG->KR = WDG_WriteAccess_Disable;
}
/*
** Feed System watchdog
*/
void FeedSystemWatchdog(void)
{
	SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->FWDG = 0xFFFFFFFF;
	SWDG->KR = WDG_WriteAccess_Disable;
}

void system_counter(void)
{
	/*
	system_count.idx = 0;
	
	do
	{
		system_count.counter[system_count.idx]++;
		system_count.idx++;
	}
	while(system_count.idx < COUNTER_SIZE);
	
	system_count.mode = _idle;
	*/
}








/*---------------------------------------------------------------------------------------------------------*/

