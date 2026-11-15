#include <stdio.h>
#include "PT32x076.h"
#include "755PSMA5L_Timer_PT32L076.h"
#include "755PSMA5L_System_PT32L076.h"


TIMER_TypeDef timer5;


/**
* @brief TIM1中断服务函数
* @param None
* @retval None
*/
void TIM1_Handler(void)
{
	uint32_t i;
	i = TIM1->SR;
	TIM1->SR |= i;

	if((system_data.masking & TIMER1_CLOSE_FLAG_MSK) != 0)
	{
		system_data.masking &= ~TIMER1_CLOSE_FLAG_MSK;
		close_timer1();
	}
	else
	{
		if((system_data.masking & TIMER1_UPDATE_FLAG_MSK) != 0)
		{
			system_data.masking &= ~TIMER1_UPDATE_FLAG_MSK;

		  TIM1->ARR = i = timer5.mr0;
		  TIM1->OCR[3] = timer5.mr0 >> 1;
		}
	}
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

/**
* @brief 恢复默认设置
* @param None
* @retval None
*/
void close_timer1(void)
{
	//PA11 PA12
	AFIOA->AFC |= HB_PIN + HS_PIN;
	GPIOA->OES |= HB_PIN + HS_PIN;
	GPIOA->BRR |= HB_PIN + HS_PIN;
	
	NVIC_DisableIRQ(TIM1_IRQn);
	
	TIM1->CR1 = 0;
	TIM1->OCMR = 0;
}

/**
* @brief 设置定时器5，1ms发生一次中断
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
	
	TIM5->SR |= TIM_SR_ARF;
	TIM5->CR1 = TIM_CR1_EN;
}

/**
* @brief 检查定时器5是否发生中断
* @param None
* @retval None
*/
void checktimer5(void)
{
	unsigned char i;
	
	if((TIM5->SR & TIM_SR_ARF) != 0)
	{
    TIM5->SR |= TIM_SR_ARF;
		i = 0;
		do
		{
			timer5.t[i]++;
			i++;
		}
		while(i < TIMER_SIZE);
	}
}

/**
* @brief 关闭定时器5
* @param None
* @retval None
*/
void closetimer5(void)
{
	TIM5->CR1 = 0;
	TIM5->CR2 = 0;
	
	TIM5->SR |= TIM_SR_ARF;
}

/*
** Open Independent watchdog
** 38.4KHz  20s
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
	IWDG->CR &= ~(IWDG_CR_EN + IWDG_CR_RSTE + IWDG_CR_DBGE + IWDG_CR_CLKS);
	IWDG->LOCK = WDG_LockKey_Lock;
}

/*
** Open System Watchdog
**  
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

/*
** close wdog
*/
void close_wdog(void)
{
	WWDG->CR1 |= 113;
	WWDG->CR2 = WWDG_CR2_KEYVALUE;
	
	IWDG->LOCK = WDG_LockKey_Unlock;
  IWDG->KR = 1;
	IWDG->CR = 0;
	IWDG->LOCK = WDG_LockKey_Lock;
  
  while((IWDG->CR & WDG_CR_ENABLE) == WDG_CR_ENABLE){__NOP();}
}



/*---------------------------------------------------------------------------------------------------------*/

