#include <stdio.h>
#include "pt32x031.h"
#include "KD715A_Timer_PT32L031.h"
#include "KD715A_Keyboard_PT32L031.h"
#include "KD715A_Windows_PT32L031.h"

/* =========================================================================== */
TIMER3_TypeDef Timer3;

uint16_t timer4_T8s = 0;

/* =========================================================================== */

/* 
** Set Timer3
** PCLK: 24MHz
*/
void set_timer3(void)
{
	//CLK: 24M / (0 + 1) = 24MHz
	TIM3->PR = 0;
	TIM3->MCR = TIM_MCR_MR0R;
	TIM3->MR0 = 24000;
	
  TIM3->TCR = 0;
	
	__NOP();
	__NOP();
	__NOP();
	
	//清除中断标志位
	TIM3->ISR |= 0x1;
	//启动定时器
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
		i = 0;
		do
		{
			Timer3.t[i]++;
			i++;
		}
		while(i < TIMER3_SIZE);
		TIM3->ISR |= TIM_ISR_OV;
	}
}

/*
** 关闭定时器3
*/
void kill_timer3(void)
{
	TIM3->TCR = 0;
	
	__NOP();
	__NOP();
	__NOP();
	
	TIM3->ISR |= TIM_ISR_OV;
	TIM3->MCR = 0;
}


void TIMER1_Handler(void)
{
  if(PWM1->ISR & PWM_ISR_MR0)
	{
		if(system_data.masking & TIMER1_UPDATE_FLAG_MSK)
		{
			if(update.value <= MAX_TIMER_US)
			{
				update.value += 1;
				if(system_data.masking & LOW_SOUND_FLAG_MSK)
				{
					PWM1->MR0 = update.value * 2;
					PWM1->MR4 = update.value;
				}
				else
				{
					PWM1->MR0 = update.value;
					PWM1->MR4 = update.value/2;
				}
			}
			system_data.masking &= ~TIMER1_UPDATE_FLAG_MSK;
		}
		PWM1->ISR |= PWM_ISR_MR0;
	}
}

/*
** Open Timer1
** output PWM on CH4
** PCLK: 24MHz
** PA11 --> HB --> FUN1 --> TIM1_CH4
** PA12 --> HS --> FUN1 --> TIM1_CH4N
*/
void set_alarm(unsigned char flag)
{
	CMSDK_PA->ALTFUNCSET1 |= (0x02 << 16) + (0x02 << 12);
	
	PWM1->TCR &= ~PWM_TCR_EN;
	
	__NOP();
	__NOP();
	
	//1M -> 1us = 1
	PWM1->PR = 23;
	PWM1->DT = 192;
	PWM1->MCR = 0x41;
	PWM1->CMR = 0;
	PWM1->CCR = 0;
	PWM1->INT_RPT = 0;
	
	//3.49khz = 1/3.49k = 286us
	
	if(flag == 0)
	{
		PWM1->MR0 = update.value * 2;
	  PWM1->MR4 = update.value;
	}
	else
	{
		//理论：3.49khz = 286us = 286
		//实测：3.49khz 约为 284
		PWM1->MR0 = update.value;
	  PWM1->MR4 = update.value/2;
	}

	NVIC_EnableIRQ(TIMER1_IRQn);
	
	PWM1->CMR = (0x02 << 12) + (0 << 3);
}

/*
** 打开蜂鸣器
*/
void open_buzzer(void)
{
	PWM1->CMR |= PWM_CMR_PWM4n_EN;
  PWM1->TCR |= PWM_TCR_EN;
}

/*
** 关闭蜂鸣器
*/
void close_buzzer(void)
{
	PWM1->TCR &= ~PWM_TCR_EN;
	PWM1->CMR &= ~PWM_CMR_PWM4n_EN;
}

void del_alarm(void)
{
	NVIC_DisableIRQ(TIMER1_IRQn);
	
	PWM1->TCR = 0;
	
	__NOP();
	__NOP();
	
	PWM1->CMR = 0;
	PWM1->ISR |= 0x1F;
	PWM1->MCR = 0;
	
	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC12 + GPIO_AFC_AFC11;
	CMSDK_PA->OUTENABLESET |=(1 << 11) + (1 << 12);
	CMSDK_PA->DATAOUT &= ~0x1800;
}

/*
** Open Timer4 (LpTimer)
** LSI: 25 ~ 38KHz --> 31.5KHz
** -40 ~ +85: +/-10%
*/
void open_timer4(void)
{
	TIM4->MR0 = timer4_T8s;
	
	TIM4->PR = 30;
	
	TIM4->MCR = TIM_MCR_MR0R + TIM_MCR_MR0I;
	TIM4->TCR |= TIM_TCR_UPDATE;
	TIM4->ISR |= TIM_ISR_OV;
	TIM4->TCR |= TIM_TCR_EN;

  while((TIM4->TCR & TIM_TCR_EN) == 0)
  {
	  __NOP();
	}
	
	NVIC_EnableIRQ(TIMER4_IRQn);
}

/*
** Close Timer4
*/
void close_timer4(void)
{
	NVIC_DisableIRQ(TIMER4_IRQn);
	
	TIM4->TCR = 0;
	
	__NOP();
	__NOP();
	
	TIM4->MCR = 0;
	TIM4->ISR |= TIM_ISR_OV;
}

/*
** TIMER4_Handler
** 
*/
void TIMER4_Handler(void)
{
	TIM4->TCR = 0;
	
	__NOP();
	__NOP();
	
	TIM4->MCR = 0;
	TIM4->ISR |= TIM_ISR_OV;
	
	system_data.masking |= TIMER3_UPDATE_FLAG_MSK;
}

/*
** 向指定的数组增加特定值的值
*/
void mem_data_add(unsigned int* d, unsigned short num, unsigned int l)
{
	for (unsigned int i = 0; i < l; i++) 
	{
		d[i] += num;
	}
}

/*
** timer4 唤醒时timer3需要增加相应的值
*/
void system_irq_proc_run(void)
{
	mem_data_add(&Timer3.t[10],8000,5);
}

/*
** Open Independent watchdog
*/
void open_iwdg(void)
{
	IWDG->KR = WDG_WriteAccess_Enable;
	IWDG->RLR = 640000; //20s
	IWDG->FWDG = 0xFFFFFFFF;
	IWDG->CR |= WDG_CR_RSTE + WDG_CR_INTE;
	IWDG->KR = WDG_WriteAccess_Disable;
}

/*
** Feed Independent watchdog
*/
void feed_iwdg(void)
{
	IWDG->KR = WDG_WriteAccess_Enable;
	IWDG->FWDG = 0xFFFFFFFF;
	IWDG->KR = WDG_WriteAccess_Disable;
}

/*
** Close Independent watchdog
*/
void close_iwdg(void)
{
	IWDG->KR = WDG_WriteAccess_Enable;
	IWDG->RLR = 640000; //20s
	IWDG->FWDG = 0xFFFFFFFF;
	IWDG->CR &= ~(WDG_CR_RSTE + WDG_CR_INTE + WDG_CR_DBGE);
	IWDG->KR = WDG_WriteAccess_Disable;
}

/*
** Open System Watchdog
** 100ms
*/
void open_swdg(void)
{
	SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->RLR = 2400000; //100ms
	SWDG->FWDG = 0xFFFFFFFF;
	SWDG->CR |= WDG_CR_RSTE + WDG_CR_INTE;
	SWDG->KR = WDG_WriteAccess_Disable;
}

/*
** Feed System watchdog
*/
void feed_swdg(void)
{
	SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->FWDG = 0xFFFFFFFF;
	SWDG->KR = WDG_WriteAccess_Disable;
}

/*
** Feed System watchdog
*/
void close_swdg(void)
{
	SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->CR &= ~(WDG_CR_RSTE + WDG_CR_INTE + WDG_CR_DBGE);
	SWDG->KR = WDG_WriteAccess_Disable;
}


/*---------------------------------------------------------------------------------------------------------*/

