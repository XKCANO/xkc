#include "KD715A_System_PT32L031.h"


START_TYPEDEF start;


/**********************************************************************
  * @brief  This Function Of The System Clock .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_clock_init(void)
{
	CMSDK_SYSCON->RSTINFO |= CMSDK_SYSCON->RSTINFO;
	//HCLK:24MHz
	//PCLK:24 / 1 = 24MHz
	__NOP();
	CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	__NOP();
	CMSDK_SYSCON->SYSCLK &= ~(SYSCON_SYSCLK_WAKE_DELAY + SYSCON_SYSCLK_FDFAIL_DETECTEN + SYSCON_SYSCLK_EOSFAIL_DETECTEN + 
	                          SYSCON_SYSCLK_PCLKDIV + SYSCON_SYSCLK_HCLKDIV + SYSCON_SYSCLK_FDCLKSEL + SYSCON_SYSCLK_SYSCLKSEL);
	CMSDK_SYSCON->SYSCLK |= (SYSCON_SYSCLK_RECOVER_SEL + SYSCON_SYSCLK_PCLKDIV_1DIV + SYSCON_SYSCLK_HCLKDIV_1DIV);
}

/**********************************************************************
  * @brief  This Function Of The System GPIO .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_gpio_init(void)
{
	//PA 0000 0111 1110 0000
	//   |||| |||| |||| |||+--> VOP
	//   |||| |||| |||| ||+---> HTS
	//   |||| |||| |||| |+----> BST
	//   |||| |||| |||| +-----> NC
	//
	//   |||| |||| |||+-------> NC
	//   |||| |||| ||+--------> KY1
	//   |||| |||| |+---------> KY2 MUTE
	//   |||| |||| +----------> KY3 TEST
	//
	//   |||| |||+------------> RED
	//   |||| ||+-------------> TX1
	//   |||| |+--------------> RX1
	//   |||| +---------------> HS
	//
	//   |||+-----------------> HB
	//   ||+------------------> SWDIO
	//   |+-------------------> SWCLK
	//   +--------------------> CS

	//输入使能
	CMSDK_PA->OUTENABLECLR |= (1 << 5) + (1 << 6) + (1 << 7) + (1 << 10);
	//输出使能
	CMSDK_PA->OUTENABLESET |= (1 << 0) + (1 << 1) + (1 << 2) + (1 << 3) + 
	                          (1 << 4) + 
													  (1 << 8) + (1 << 9) + (1 << 11) + 
													  (1 << 12) + (1 << 15);
	//输出锁存
	CMSDK_PA->DATAOUT |= 0x0700;
	
#if _BETA_VERSION
  //数字复用失能
	CMSDK_PA->ALTFUNCCLR |= 0x9FFF;
#else
	//数字复用失能
	CMSDK_PA->ALTFUNCCLR |= 0xFFFF;
	//输出使能
	CMSDK_PA->OUTENABLESET |= (1 << 13) + (1 << 14);
	//输出复位
	CMSDK_PA->DATAOUT &= ~0x6000;
#endif
	//开漏失能
	CMSDK_PA->ODRCLR |= 0xFFFF;
	//上拉失能
	CMSDK_PA->PULLUPCLR |= 0xFFFF;
	//下拉失能
	CMSDK_PA->PULLDOWNCLR |= 0xFFFF;
	//中断失能
	CMSDK_PA->INTENCLR |= 0xFFFF;
	//模拟失能
	CMSDK_PA->ANACLR |= 0xFFFF;


  //PB 0000 0000 1000 0000
	//   |||| |||| |||| |||+--> NC
	//   |||| |||| |||| ||+---> NC
	//   |||| |||| |||| |+----> NC
	//   |||| |||| |||| +-----> SCK
	//
	//   |||| |||| |||+-------> MISO
	//   |||| |||| ||+--------> MOSI
	//   |||| |||| |+---------> FCSB
	//   |||| |||| +----------> NC
	//
	//   |||| |||+------------> NC
	//   |||| ||+-------------> NC
	//   |||| |+--------------> NC
	//   |||| +---------------> NC
	//
	//   |||+-----------------> NC
	//   ||+------------------> NC
	//   |+-------------------> NC
	//   +--------------------> NC

	//输入使能
	CMSDK_PB->OUTENABLECLR = 0;
	//输出使能
  CMSDK_PB->OUTENABLESET |= 0xFFFF;
	//输出锁存
	CMSDK_PB->DATAOUT = 0;
	//复用失能
	CMSDK_PB->ALTFUNCCLR |= 0xFFFF;
	//开漏失能
	CMSDK_PB->ODRCLR |= 0xFFFF;
	//上拉失能
	CMSDK_PB->PULLUPCLR |= 0xFFFF;
	//下拉失能
	CMSDK_PB->PULLDOWNCLR |= 0xFFFF;
	//中断失能
	CMSDK_PB->INTENCLR |= 0xFFFF;
	//模拟失能
	CMSDK_PB->ANACLR |= 0xFFFF;
	
	
	//PF 0000 0000 0000 0001
	//                    |+--> BL
	//                    +---> NC
	
	//输入使能
	CMSDK_PF->OUTENABLECLR = 0;
	//输出使能
  CMSDK_PF->OUTENABLESET |= 0xFFFF;
	//输出锁存
	CMSDK_PF->DATAOUT |= 0x0001;
	//复用失能
	CMSDK_PF->ALTFUNCCLR |= 0xFFFF;
	//开漏失能(推挽使能)
	CMSDK_PF->ODRCLR |= 0xFFFF;
	//上拉失能
  CMSDK_PF->PULLUPCLR |= 0xFFFF;
	//下拉失能
	CMSDK_PF->PULLDOWNCLR |= 0xFFFF;
	//中断失能
  CMSDK_PF->INTENCLR |= 0xFFFF;
	//模拟失能
	CMSDK_PF->ANACLR |= 0xFFFF;
}

/************************************************************************
  * @brief  System Init
  * @param  None
  * @retval None
************************************************************************/
void system_start_proc_run(void)
{
	switch(start.step)
	{
		case 0:
      #if _BETA_VERSION
		  RED_LED_ON;
      #endif
			GENERAL_TIMER = 0;
		  start.step++;
			break;
		case 1:
			if(GENERAL_TIMER > 999)
			{
				fe_755LHA_read_eeprom_data(&eeprom_data);
				fe_set_uart_callback(UartCallBack);
				start.step++;
			}
			break;
		case 2:
			if(TEST_KEY == 0)
			{
				if(DEBUG_KEY == 0)
				{
					close_iwdg();
					RED_LED_ON;
					fe_uart_open(1);
					system_data.masking |= DEBUG_FLAG_MSK;
					start.step = 12;
				}
			}
			else
			{
				start.step++;
			}
			break;
		case 3:
			start.step++;
		  fe_calculate_sleep_8s(&start.step);
			break;
		
		case 4:
			break;
		
		case 5:
			timer4_T8s = fe_get_sleep_8s();
		  timer4_T8s = timer4_T8s / 1.6;
			start.step++;
			break;
		
		case 6:
			alarm_init(ONE_MED_MODE);
		  start.step++;
			break;
		case 7:
			if(led.mode == _idle)
			{
				update.value = MIN_TIMER_US;
				TEST_TIMER += 50;
				HEAT_TIMER = 8000;
				BATTERY_TIMER = 48000;
				system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
				start.step = 0;
				start.mode = _idle;
			}
			break;
			
	 case 12:
			if(GENERAL_TIMER > 2999)
			{
				RED_LED_OFF;
				start.step = 6;
			}
			break;	
	}
}

/**********************************************************************
  * @brief  This Function Of The DeepSleep .
  * @param  None
  * @retval None
  *********************************************************************/
void goto_deepsleep(void)
{
	fe_kill_system_tick_timer();
	kill_timer3();
	close_swdg();
	
	//KY3 --> PA7
	CMSDK_PA->INTTYPESET |= TEST_PIN;
	CMSDK_PA->INTTYPESET1 |= TEST_PIN;
	CMSDK_PA->INTPOLCLR |= TEST_PIN;
	CMSDK_PA->INTENSET |= TEST_PIN;
	CMSDK_PA->INTCLEAR |= TEST_PIN;
	
	NVIC_EnableIRQ(PA_IRQn);
	
	while((TIM4->TCR & TIM_TCR_EN) != 0){ __NOP();}
	open_timer4();

	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__NOP();
	__WFI();
	__NOP();
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	
	NVIC_DisableIRQ(PA_IRQn);
	
  close_timer4();
	
	//KY3  --> PA2
	CMSDK_PA->INTENCLR |= TEST_PIN;
	
	while((TIM4->TCR & TIM_TCR_EN) != 0){ __NOP();}
	
	fe_set_system_tick_timer();
	set_timer3();
	
	__NOP();
	__NOP();
	
	if(system_data.masking & TIMER3_UPDATE_FLAG_MSK)
	{
		system_irq_proc_run();
		system_data.masking &= ~TIMER3_UPDATE_FLAG_MSK;
	}
	
	open_swdg();
}

/*---------------------------------------------------------------------------------------------------------*/


