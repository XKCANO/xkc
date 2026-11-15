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
#include "PT32x076.h"
#include "755PSMA5_Timer_PT32L076.h"
#include "755PSMA5_System_PT32L076.h"

/* =========================================================================== */
TIMER_TypeDef timer5;
/* =========================================================================== */

/**
* @brief TIM1中断服务函数
* @param None
* @retval None
*/
void TIM1_Handler(void)
{
	if(TIM1->SR & TIM_SR_ARF)
	{
		if(system_data.masking & TIMER1_UPDATE_FLAG_MSK)
		{
			if(timer5.mr0 <= MAX_TIMER_US)
			{
				timer5.mr0 += 2;
				if(system_data.masking & LOW_SOUND_FLAG_MSK)
				{
					TIM1->ARR = timer5.mr0 * 2;
	        TIM1->OCR[3] = timer5.mr0;
				}
				else
				{
					TIM1->ARR = timer5.mr0;
	        TIM1->OCR[3] = timer5.mr0 / 2;
				}
			}
			system_data.masking &= ~TIMER1_UPDATE_FLAG_MSK;
		}
		TIM1->SR |= TIM_SR_ARF;
	}
}

/**
* @brief 设置定时器1
* @param flag
*  0: low
*  1: high
* @retval None
*/
void set_timer1(void)
{
	//PA11 PA12
	AFIOA->AFS[1] = (0x05 << 12) + (0x05 << 16);
	
	// 16M / (15 + 1) = 1M
	TIM1->PSC = 15;
	
  TIM1->ARR = timer5.mr0;
	TIM1->OCR[3] = timer5.mr0 / 2;

	TIM1->OCMR = 0x001000;
	
	//死区时间 8us
	TIM1->BDTR = 255;
	TIM1->CR1 = TIM_CR1_DIR;
	TIM1->CR2 |= TIM_CR2_ARI;
	
	NVIC_EnableIRQ(TIM1_IRQn);
}

/**
* @brief 恢复默认设置
* @param None
* @retval None
*/
void close_timer1(void)
{
	NVIC_DisableIRQ(TIM1_IRQn);
	
	TIM1->CR1 &= ~TIM_CR1_EN;
	
	__NOP();
	__NOP();
	
	TIM1->PSC = 0;
	TIM1->ARR = 0;
	TIM1->OCR[3] = 0;
	TIM1->OCMR = 0;
	TIM1->CR1 = 0;
	TIM1->CR2 = 0;
	
	//PA11 PA12
	AFIOA->AFC |= HB_PIN + HS_PIN;
	GPIOA->OES |= HB_PIN + HS_PIN;
	GPIOA->BRR |= HB_PIN + HS_PIN;
}

/**
* @brief 设置定时器2，1ms发生一次中断
* @param None
* @retval None
*/
void settimer5(void)
{
	TIM5->PSC = 0;//16M
	TIM5->CNT = 0;
	TIM5->CR2 = 0;
	TIM5->ARR = 16000;//1ms
	
	__NOP();
	__NOP();
	__NOP();
	
	TIM5->SR |= TIM_SR_ARF;//清除中断标志位
	TIM5->CR1 = TIM_CR1_EN;//开启定时器
}

/**
* @brief 检查定时器5是否发生中断
* @param None
* @retval None
*/
void checktimer5(void)
{
	unsigned char i;
	
	if(TIM5->SR & TIM_SR_ARF)
	{
		i = 0;
		do
		{
			timer5.t[i]++;
			i++;
		}
		while(i < TIMER_SIZE);
		
		TIM5->SR |= TIM_SR_ARF;
	}
}

/**
* @brief 关闭定时器5
* @param None
* @retval None
*/
void closetimer5(void)
{
	TIM5->CR1 = 0;//关闭定时器
	
	__NOP();
	__NOP();
	__NOP();
	
	TIM5->PSC = 0;
	TIM5->CNT = 0;
	TIM5->CR2 = 0;
	TIM5->ARR = 0;
	
	TIM5->SR |= 0xE063;//清除所有标志位
}

/**
* @brief 设置低功耗定时器Timer4 38.4k
* @param None
* @retval None
*/
void settimer4(void)
{
  if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{
		TIM4->ARR = 2021;
	}
	else
	{
		TIM4->ARR = 8084;
	}

	TIM4->PSC = 37;
	TIM4->CR2 = 0x01;

	TIM4->CR1 |= 0x01;
	while((TIM4->CR1 & 0x1) == 0){__NOP();}
	
	NVIC_EnableIRQ(TIM4_IRQn);
}

/**
* @brief 关闭低功耗定时器
* @param None
* @retval None
*/
void closetimer4(void)
{
	while(TIM4->CR1 & 0x8000){__NOP();}
	
	TIM4->CR1 &= ~0x107;
	TIM4->ARR = 0;
	TIM4->PSC = 0;
	TIM4->CR2 = 0;
	
	NVIC_DisableIRQ(TIM4_IRQn);
}

/**
* @brief LPTIM中断服务函数
* @param None
* @retval None
*/
void TIM4_Handler(void)
{
	TIM4->SR |= TIM_SR_ARF;
	system_data.masking |= SYSTEM_INTERRUPT_FLAG_MSK;
}

/*
** Open Independent watchdog
** 32KHz  20s
*/
void open_iwdg(void)
{
	IWDG->LOCK = WDG_LockKey_Unlock;
	IWDG->RLR = 768000;
	IWDG->KR = 1;
	IWDG->CR |= IWDG_CR_RSTE + IWDG_CR_EN;
	IWDG->LOCK = WDG_LockKey_Lock;
}

/*
** Feed Independent watchdog
*/
void feed_iwdg(void)
{
  IWDG->LOCK = WDG_LockKey_Unlock;
	IWDG->RLR = 768000;
	IWDG->KR = 1;
	IWDG->LOCK = WDG_LockKey_Lock;
}

/*
** Close Independent watchdog
*/
void close_iwdg(void)
{
	IWDG->LOCK = WDG_LockKey_Unlock;
	IWDG->RLR = 768000;
	IWDG->CNT = 0xFFFFFFFF;
	IWDG->CR &= ~(IWDG_CR_EN + IWDG_CR_RSTE + IWDG_CR_DBGE + IWDG_CR_CLKS);
	IWDG->LOCK = WDG_LockKey_Lock;
}

/*
** Open System Watchdog
** 16000000 / 2048 / 16 = 488.28Hz
** 100ms
*/
void open_swdg(void)
{
	WWDG->CFGR = 0x407F;
	
	//100ms * 488.28 = 48.828
  //49+64 = 113
	WWDG->CR1 |= 113;
	
	__NOP();
	__NOP();
	
	WWDG->CR1 |= WWDG_CR1_RSTE;
	WWDG->CR2 = WWDG_CR2_EN + WWDG_CR2_KEYVALUE;
}

/*
** Feed System watchdog
*/
void feed_swdg(void)
{
	WWDG->CR1 |= 113;
}

/*
** Close System watchdog
*/
void close_swdg(void)
{
	WWDG->CR1 |= 113;
	WWDG->CR2 = WWDG_CR2_KEYVALUE;
}




/*---------------------------------------------------------------------------------------------------------*/



