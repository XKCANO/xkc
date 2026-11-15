#include "755LHA_System_PT32L031.h"


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
 
	//PCLK:24 / 8 = 3MHz
	__NOP();
	CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	__NOP();
	CMSDK_SYSCON->SYSCLK &= ~(SYSCON_SYSCLK_WAKE_DELAY + SYSCON_SYSCLK_FDFAIL_DETECTEN + SYSCON_SYSCLK_EOSFAIL_DETECTEN + 
	                          SYSCON_SYSCLK_PCLKDIV + SYSCON_SYSCLK_HCLKDIV + SYSCON_SYSCLK_FDCLKSEL + SYSCON_SYSCLK_SYSCLKSEL);
	CMSDK_SYSCON->SYSCLK |= (SYSCON_SYSCLK_RECOVER_SEL + SYSCON_SYSCLK_PCLKDIV_8DIV + SYSCON_SYSCLK_HCLKDIV_1DIV);
  
	//PVD失能
	CMSDK_ANAMIX->VDD_LVD_CON &= ~ANAMIX_VDDLVDCTRL_EN;
	
	
	NVIC->ICER[0] |= 0x100000;
}

/**********************************************************************
  * @brief  This Function Of The System GPIO .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_gpio_init(void)
{
	//PA 1000 0110 0000 1100
	//   |||| |||| |||| |||+--> BL_EN(输出)
	//   |||| |||| |||| ||+---> BTS(输出)
	//   |||| |||| |||| |+----> KY3(输入)
	//   |||| |||| |||| +-----> RED1(输出)
	//
	//   |||| |||| |||+-------> NC(输出)
	//   |||| |||| ||+--------> DBG
	//   |||| |||| |+---------> HTS(输出)
	//   |||| |||| +----------> VOP(输出)
	//
	//   |||| |||+------------> KY1(常态输入,睡眠输出)
	//   |||| ||+-------------> TX1(输出)
	//   |||| |+--------------> RX1(输入)
	//   |||| +---------------> HS(输出)
	//
	//   |||+-----------------> HB(输出)
	//   ||+------------------> SWDIO
	//   |+-------------------> SWCLK
	//   +--------------------> CS(输出)

	//输出锁存
	CMSDK_PA->DATAOUT = 0xC20C;
	//输入使能
	CMSDK_PA->OUTENABLECLR |= (1 << 2) + (1 << 8) + (1 << 10);
	//输出使能
	CMSDK_PA->OUTENABLESET |= (1 << 0) + (1 << 1) +(1 << 3) + 
	                          (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7) + 
													  (1 << 9) + (1 << 11) + 
													  (1 << 12) + (1 << 15);
#if _BETA_VERSION
  //数字复用失能
	CMSDK_PA->ALTFUNCCLR |= 0x9FFF;
#else
	//数字复用失能
	CMSDK_PA->ALTFUNCCLR |= 0xFFFF;
	//输出使能
	CMSDK_PA->OUTENABLESET |= (1 << 13) + (1 << 14);
	//输出复位
//	CMSDK_PA->DATAOUT &= ~0x6000;
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

  //PB 0000 0000 1111 1000
	//   |||| |||| |||| |||+--> I_OUT(输出)
	//   |||| |||| |||| ||+---> KY2(输入)
	//   |||| |||| |||| |+----> IO_PIN(输入)
	//   |||| |||| |||| +-----> SCK
	//
	//   |||| |||| |||+-------> MISO
	//   |||| |||| ||+--------> MOSI
	//   |||| |||| |+---------> RED
	//   |||| |||| +----------> YLW
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

	//输出锁存
	CMSDK_PB->DATAOUT = 0x00F8;
	//输入使能
	CMSDK_PB->OUTENABLECLR |= (1 << 1) + (1 << 2) + (1 << 4);
	//输出使能
  CMSDK_PB->OUTENABLESET |= (1 << 0) + (1 << 3) + 
                            (1 << 5) + (1 << 6) + (1 << 7) +	
	                          (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + 
													  (1 << 12) + (1 << 13) + (1 << 14) + (1 << 15);

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
	
	
	//PF 0000 0000 0000 0000
	//                    |+--> KY4(输入)
	//                    +---> BOOST_PWR
	
	//输出锁存
	CMSDK_PF->DATAOUT = 0;
	//输入使能
	CMSDK_PF->OUTENABLECLR |= (1 << 0);
	//输出使能
  CMSDK_PF->OUTENABLESET |= 0xFFFE;
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

#if _BETA_VERSION
/************************************************************************
  * @brief  System Init
  * @param  None
  * @retval None
************************************************************************/
void eeprom_data_cfg(void)
{
	eeprom_data.marking = 0;//配置EEPROM
	eeprom_data.network_address = 0x01;//主机分配网络编号
	eeprom_data.address = 0x01;
	
	eeprom_data.id[0] = 0x33;//生产ID
	eeprom_data.id[1] = 0x00;
	eeprom_data.id[2] = 0x72;
	eeprom_data.id[3] = 0xF6;
	
	eeprom_data.network_id[0] = 0x50;//配网时的同步码
	eeprom_data.network_id[1] = 0x00;
	eeprom_data.network_id[2] = 0xA0;
	eeprom_data.network_id[3] = 0x00;
  
	eeprom_data.low_voltage = 154;
	eeprom_data.end_voltage = 128;
}
#endif

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
      if(GENERAL_TIMER >= 990)
      {
        RED1_LED_ON;
        fe_755LHA_read_eeprom_data(&eeprom_data);
        fe_set_755lha_mac_callback(mac_callback);
        fe_set_uart_callback(uart_callback);
        start.step++;
      }
			break;
		case 1:
			if(GENERAL_TIMER >= 1000)
      {
        RED1_LED_OFF;
        if(TEST_KEY == 0)
        {
          if(EXT_KEY == 0)
          {
						fe_uart_open(1);
            system_data.masking |= DEBUG_FLAG_MSK;
            system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
            start.step = 0;
            start.mode = _idle;
          }
          else
          {
            release.mode = _exe;
            start.step = 7;
          }
        }
        else
        {
          if(eeprom_data.marking & 0x01)
          {
            system_data.masking |= ON_NET_FLAG_MSK;
          }
          start.step++;
        }
      }
			break;
			
		case 2:
#if _BETA_VERSION
      eeprom_data_cfg();
      start.step = 10;
#else
      start.step++;
#endif
			break;
			
		case 3:
      start.step++;
		  fe_calculate_sleep_8s(&start.step);
			break;
      
    case 4:
      break;
    
		case 5:
			timer3.timer4_T8s = fe_get_sleep_8s();
      HEAT_TIMER = 8000;
      BATTERY_TIMER = 48000;
      system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
      start.step = 0;
      start.mode = _idle;
			break;
    
		case 7:
			if(release.mode == _idle)
			{
				start.step = 3;
			}
			break;

#if _BETA_VERSION
    case 10:
			if(fe_755LHA_write_eeprom_data(&eeprom_data) == 0)
			{
				start.step++;
			}
			break;
		case 11:
			if(fe_get_eeprom_state() == 0)
			{
        start.step++;
			}
			break;
		case 12:
			if(fe_755LHA_read_eeprom_data(&eeprom_data) == 0)
			{
				start.step = 3;
			}
			break;
#endif

	}
}

/**********************************************************************
  * @brief  指定数组的指定位置增加指定的值
  * @param  None
  * @retval None
  *********************************************************************/
void mem_data_add(unsigned int* d, unsigned short num, unsigned char l)
{
	for (unsigned short i = 0; i < l; i++) 
	{
		d[i] += num;
	}
}

/**********************************************************************
  * @brief  This Function Of The DeepSleep .
  * @param  None
  * @retval None
  *********************************************************************/
void goto_deepsleep(void)
{
//	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC12 + GPIO_AFC_AFC11;
	fe_kill_system_tick_timer();
	kill_timer3();
	close_swdg();
	
	//KY1 local  --> PA8
	CMSDK_PA->OUTENABLESET |= NETWORK_PIN;
	CMSDK_PA->PULLUPCLR |= NETWORK_PIN;
	
	//KY3 --> PA2
	CMSDK_PA->INTTYPESET |= TEST_PIN;
	CMSDK_PA->INTTYPESET1 |= TEST_PIN;
	CMSDK_PA->INTPOLCLR |= TEST_PIN;
	CMSDK_PA->INTENSET |= TEST_PIN;
	CMSDK_PA->INTCLEAR |= TEST_PIN;
	
	//KY2 --> PB1
	CMSDK_PB->INTTYPESET |= EXT_PIN;
	CMSDK_PB->INTTYPESET1 |= EXT_PIN;
	CMSDK_PB->INTPOLCLR |= EXT_PIN;
	CMSDK_PB->INTENSET |= EXT_PIN;
	CMSDK_PB->INTCLEAR |= EXT_PIN;

	if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{
		if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
		{
			TIM4->MR0 = timer3.timer4_T8s;
		}
		else
		{
			TIM4->MR0 = (timer3.timer4_T8s >> 2);
		}
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
	while((TIM4->TCR & TIM_TCR_EN) == 0){ __NOP();}
	
	NVIC_EnableIRQ(PA_IRQn);
	NVIC_EnableIRQ(PB_IRQn);
	NVIC_EnableIRQ(TIMER4_IRQn);
	
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__NOP();
	__WFI();
	__NOP();
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	
	NVIC_DisableIRQ(TIMER4_IRQn);
	NVIC_DisableIRQ(PA_IRQn);
	NVIC_DisableIRQ(PB_IRQn);
	
	TIM4->TCR &= ~TIM_TCR_EN;
	while((TIM4->TCR & TIM_TCR_EN) != 0){ __NOP();}

	CMSDK_PA->INTENCLR |= TEST_PIN;//KY3  --> PA2
	CMSDK_PB->INTENCLR |= EXT_PIN;//KY2 --> PB1
	
	CMSDK_PA->OUTENABLECLR |= NETWORK_PIN;//KY1 local -> PA8
	CMSDK_PA->PULLUPSET |= NETWORK_PIN;//上拉使能
	
	fe_set_system_tick_timer();
	set_timer3();
	open_swdg();
  
	if(system_data.masking & SYSTEM_INTERRUPT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
		  {
			  mem_data_add(&timer3.t[11],8000,8);
			}
			else
			{
				mem_data_add(&timer3.t[11],2000,8);
			}
		}
		else
		{
			mem_data_add(&timer3.t[11],8000,8);
		}
		
		message_execution();
		
		system_data.masking &= ~SYSTEM_INTERRUPT_FLAG_MSK;
	}
}

/*---------------------------------------------------------------------------------------------------------*/


