#include <stdio.h>
#include "pt32x031.h"
#include "755LHA_Timer_PT32L031.h"
#include "755LHA_Keyboard_PT32L031.h"
#include "FE_semaphore.h"


/* =========================================================================== */
TIMER3_TypeDef timer3;

/* 
** Set Timer3
** PCLK: 24MHz
*/
void set_timer3(void)
{
	//CLK: 3M / (0 + 1) = 3MHz
	TIM3->PR = 0;
	TIM3->MCR = TIM_MCR_MR0R;
	TIM3->MR0 = 3000;
	
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
** Check Timer3
*/
void check_timer3(void)
{
	unsigned char i;
	
	if(TIM3->ISR & TIM_ISR_OV)
	{
		i = 0;
		do
		{
			timer3.t[i]++;
			i++;
		}
		while(i < TIMER3_SIZE);
		
		TIM3->ISR |= TIM_ISR_OV;
	}
}

/*
** close Timer3
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

/*
** Timer1 handler
*/
void TIMER1_Handler(void)
{
  uint32_t i;
	i = PWM1->ISR;
	PWM1->ISR |= i;
  
  if((system_data.masking & TIMER1_CLOSE_FLAG_MSK) != 0)
	{
		CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC12 + GPIO_AFC_AFC11;
		NVIC_DisableIRQ(TIMER1_IRQn);
		PWM1->TCR = 0;
		__NOP();
		PWM1->CMR = 0;
		PWM1->MCR = 0;
		system_data.masking &= ~TIMER1_CLOSE_FLAG_MSK;
		fe_clear_semaphore(10);
  }
  else
  {
    if(system_data.masking & TIMER1_UPDATE_FLAG_MSK)
		{
			i = update.value;
			PWM1->MR0 = i / 2;
			PWM1->MR4 = i / 4;
      system_data.masking &= ~TIMER1_UPDATE_FLAG_MSK;
		}
  }
}

/*
** close Timer1
*/
//void close_timer1(void)
//{
//	PWM1->TCR = 0;
//	__NOP();
//	__NOP();
//	__NOP();
//	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC12 + GPIO_AFC_AFC11;
////	CMSDK_PA->OUTENABLESET |=(1 << 11) + (1 << 12);
////	CMSDK_PA->DATAOUT &= ~((1 << 11) | (1 << 12));
//	NVIC_DisableIRQ(TIMER1_IRQn);
//	PWM1->CMR = 0;
////	PWM1->ISR |= 0x1F;
//	PWM1->MCR = 0;
//	system_data.masking &= ~TIMER1_CLOSE_FLAG_MSK;
//	fe_clear_semaphore(10);
//}

/*
** Open Timer4 (LpTimer)
** LSI: 25 ~ 38KHz --> 31.5KHz
** -40 ~ +85: +/-10%
*/
void open_timer4(void)
{
  if(system_data.state & ALARM_MEMORY_FLAG_MSK)//报警记忆
	{
		TIM4->MR0 = (timer3.timer4_T8s >> 2);
	}
	else
	{
	  TIM4->MR0 = timer3.timer4_T8s;
	}
	
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
	
	system_data.masking |= SYSTEM_INTERRUPT_FLAG_MSK + RF_CHECK_FLAG_MSK;
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
	SWDG->RLR = 300000; //100ms
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

/*
** close wdog
*/
void close_wdog(void)
{
  IWDG->KR = WDG_WriteAccess_Enable;
	IWDG->RLR = 640000;
	IWDG->FWDG = 0xFFFFFFFF;
	IWDG->CR &= ~(WDG_CR_RSTE + WDG_CR_INTE + WDG_CR_DBGE);
	IWDG->KR = WDG_WriteAccess_Disable;
  
  __NOP();
  __NOP();
  
  SWDG->KR = WDG_WriteAccess_Enable;
	SWDG->CR &= ~(WDG_CR_RSTE + WDG_CR_INTE + WDG_CR_DBGE);
	SWDG->KR = WDG_WriteAccess_Disable;
}


/*---------------------------------------------------------------------------------------------------------*/

