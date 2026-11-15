#include "755PSMA5L_System_PT32L076.h"



/**********************************************************************
  * @brief  Clear_SRAM .
  * @param  None
  * @retval None
  *********************************************************************/
void clear_sram(void)
{
	unsigned int i, l;
	l = __get_MSP();
	l = (l & 0x00007FFF) / 4;
	i = 0;
	do{
		((unsigned int *)SRAM_BASE)[i] = 0;
		i++;
	}while(i < l);
}

/**********************************************************************
  * @brief  This Function Of The System Clock .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_clock_init(void)
{
	unsigned int LSI_TRIM = 0;
	unsigned int tmpreg = 0;
	
	//HCLK: 16M
	//PCLK: 16M
	RCC->HSICR |= RCC_HSICR_EN;
	RCC->CFGR &= ~(RCC_CFGR_SCW + RCC_CFGR_HPRE + RCC_CFGR_SCWK + RCC_CFGR_SCDS + RCC_CFGR_PPRE);
	RCC->CFGR |= 0x10;
	
	//校准内部低速时钟
	LSI_TRIM = (*((u32 volatile *)(0x4001F03C))>>24);
	tmpreg = RCC->LSICR;
	tmpreg &= ~(RCC_LSICR_CFS|0xFF0000);
	tmpreg |= (LSI_TRIM<<16|0xBF00);
	RCC->LSICR = tmpreg;
	
	//38.4k
  RCC->LSICR &= ~RCC_LSICR_CFS;
	RCC->LSICR |= RCC_LSICR_EN;
	
	RCC->RSR |= 0x6D7B;
}


/**********************************************************************
  * @brief  This Function Of The System GPIO .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_gpio_init(void)
{
	//PA 0100 0000 0110 0011
	//   |||| |||| |||| |||+--> I22
	//   |||| |||| |||| ||+---> I23
	//   |||| |||| |||| |+----> HTS
	//   |||| |||| |||| +-----> VOP
	//
	//   |||| |||| |||+-------> SKS
	//   |||| |||| ||+--------> RED
	//   |||| |||| |+---------> RED1
	//   |||| |||| +----------> KY3
	//
	//   |||| |||+------------> NC
	//   |||| ||+-------------> KY4
	//   |||| |+--------------> BOOST_POWER
	//   |||| +---------------> HB
	//
	//   |||+-----------------> HS
	//   ||+------------------> SWDIO
	//   |+-------------------> SWCLK/TX1
	//   +--------------------> RX1

	//输入使能
	GPIOA->OEC |= (1 << 7) + 
							  (1 << 9) + 
							  (1 << 15);
	//输出使能
	GPIOA->OES |= (1 << 0) + (1 << 1) + (1 << 2) + (1 << 3) + 
	              (1 << 4) + (1 << 5) + (1 << 6) +
							  (1 << 8) + (1 << 10) + (1 << 11) + 
							  (1 << 12);
								
#if _BETA_VERSION
	 //数字复用失能
	AFIOA->AFC |= 0x9FFF;
	//输出复位
	GPIOA->BRR |= 0x1D1C;
	//输出置位
	GPIOA->BSR |= 0x4063;
#else
	//数字复用失能
	AFIOA->AFC |= 0xFFFF;
	//输出使能
	GPIOA->OES |= (1 << 13) + (1 << 14);
	//输出复位
	GPIOA->BRR |= 0x3D1C;
	//输出置位
	GPIOA->BSR |= 0x4063;
#endif
	//开漏失能
	GPIOA->ODC |= 0xFFFF;
	//开漏使能
	GPIOA->ODS |= 0x0003;
	//上拉失能
	GPIOA->PUC |= 0xFFFF;
	//下拉失能
	GPIOA->PDC |= 0xFFFF;
	//施密特触发使能
	GPIOA->CSS |= 0xFFFF;
	//中断失能
	EXTIA->IEC |= 0xFFFF;
  //模拟失能
	AFIOA->ANAC |= 0xFFFF;
	

  //PB 0000 0010 0000 0100
	//   |||| |||| |||| |||+--> BL_EN
	//   |||| |||| |||| ||+---> BTS
	//   |||| |||| |||| |+----> PB2(STM32)
	//   |||| |||| |||| +-----> IO_PIN
	//
	//   |||| |||| |||+-------> KY1(常态输入,睡眠输出)
	//   |||| |||| ||+--------> KY2(输入)
	//   |||| |||| |+---------> I_OUT(输出)
	//   |||| |||| +----------> NC
	//
	//   |||| |||+------------> IR1
	//   |||| ||+-------------> I11(开漏输出)
	//   |||| |+--------------> NC
	//   |||| +---------------> NC
	//
	//   |||+-----------------> NC
	//   ||+------------------> NC
	//   |+-------------------> NC
	//   +--------------------> NC


	//输入使能
	GPIOB->OEC |= (1 << 3) + (1 << 4) + (1 << 5);
	//输出使能
	GPIOB->OES |= (1 << 0) + (1 << 1) + (1 << 2) +
	              (1 << 6) + (1 << 7) +
							  (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + 
							  (1 << 12) + (1 << 13) + (1 << 14) + (1 << 15);
	//输出复位
	GPIOB->BRR |= 0xFDC7;
	//输出置位
	GPIOB->BSR |= 0x0200;
	//开漏失能
	GPIOB->ODC |= 0xFFFF;
	//开漏使能
	GPIOB->ODS |= 0x0200;
	//上拉失能
	GPIOB->PUC |= 0xFFFF;
	//下拉失能
	GPIOB->PDC |= 0xFFFF;
	//施密特触发使能
	GPIOB->CSS |= 0xFFFF;
	//中断失能
	EXTIB->IEC |= 0xFFFF;
	//模拟失能
	AFIOB->ANAC |= 0xFFFF;
	//数字复用失能
	AFIOB->AFC |= 0xFFFF;
	
	
	//PC 1000 0000 0000 0000
	//   |||| |||| |||| |||+--> NC
	//   |||| |||| |||| ||+---> NC
	//   |||| |||| |||| |+----> NC
	//   |||| |||| |||| +-----> NC
	//
	//   |||| |||| |||+-------> NC
	//   |||| |||| ||+--------> NC
	//   |||| |||| |+---------> NC
	//   |||| |||| +----------> NC
	//
	//   |||| |||+------------> NC
	//   |||| ||+-------------> NC
	//   |||| |+--------------> NC
	//   |||| +---------------> NC
	//
	//   |||+-----------------> NC
	//   ||+------------------> I12(开漏输出)
	//   |+-------------------> I13(开漏输出)
	//   +--------------------> BOOT(输出)
	
	//输入使能
	GPIOC->OEC |= 0;
	//输出使能
	GPIOC->OES |= 0xFFFF;
	//输出复位
	GPIOC->BRR |= 0x9FFF;
	//输出置位
	GPIOC->BSR |= 0x6000;
	//开漏失能
	GPIOC->ODC |= 0xFFFF;
	//开漏使能
	GPIOC->ODS |= 0x6000;
	//上拉失能
	GPIOC->PUC |= 0xFFFF;
	//下拉失能
	GPIOC->PDC |= 0xFFFF;
	//施密特触发使能
	GPIOC->CSS |= 0xFFFF;
	//中断失能
	EXTIC->IEC |= 0xFFFF;
	//模拟失能
	AFIOC->ANAC |= 0xFFFF;
	//数字复用失能
	AFIOC->AFC |= 0xFFFF;


	//PF 0000 0000 0000 0011
	//   |||| |||| |||| |||+--> IR2(输出)
	//   |||| |||| |||| ||+---> I21(开漏输出)
	//   |||| |||| |||| |+----> NC
	//   |||| |||| |||| +-----> NC
	//
	//   |||| |||| |||+-------> NC
	//   |||| |||| ||+--------> NC
	//   |||| |||| |+---------> GND
	//   |||| |||| +----------> VCC
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
	GPIOF->OEC |= 0x00C0;
	//输出使能
	GPIOF->OES |= 0xFF3F;
	//输出复位
	GPIOF->BRR |= 0xFF3D;
	//输出置位
	GPIOF->BSR |= 0x0002;
	//开漏失能
	GPIOF->ODC |= 0xFFFF;
	//开漏使能
	GPIOF->ODS |= 0x0002;
	//上拉失能
	GPIOF->PUC |= 0xFFFF;
	//下拉失能
	GPIOF->PDC |= 0xFFFF;
	//施密特触发使能
	GPIOF->CSS |= 0xFFFF;
	//中断失能
	EXTIF->IEC |= 0xFFFF;
	//模拟失能
	AFIOF->ANAC |= 0xFFFF;
	//数字复用失能
	AFIOF->AFC |= 0xFFFF;
}

/**
* @brief 对指定数组修改值
* @param d：目的地址 num：值，l：长度
* @retval None
*/
void mem_data_add(unsigned int* d, unsigned short num, unsigned char l)
{
	for (unsigned int i = 0; i < l; i++) 
	{
		d[i] += num;
	}
}

/**********************************************************************
  * @brief  DeepSleep Function
  * @param  None
  * @retval None
  *********************************************************************/
void goto_deepsleep(void)
{
	close_swdg();
  TIM5->CR1 &= ~TIM_CR1_EN;
	fe_kill_system_tick_timer();

  //KY1 -> PB4 输出0
	GPIOB->OES |= LOCAL_PIN;
	GPIOB->PUC |= LOCAL_PIN;
	GPIOB->BRR |= LOCAL_PIN;
  
  if(key4.value != 0)
  {
    //KY4 -> PA9
    EXTIA->ITDS |= AC_PIN;
    EXTIA->IES |= AC_PIN;
  }
  
	//KY3 -> PA7
	EXTIA->ITDS |= TEST_PIN;
	EXTIA->IES |= TEST_PIN;
  EXTIA->IF |= 0xFFFF;
	
	//IO_PIN -> PB3
  //KY2 -> PB5
	EXTIB->ITDS |= IO_PIN + EXT_PIN;
	EXTIB->IES |= IO_PIN + EXT_PIN;
	EXTIB->IF |= 0xFFFF;
  
  if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{
		if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
		{
			TIM4->ARR = 8084;
		}
		else
		{
			TIM4->ARR = 2021;
		}
	}
	else if(system_data.state & DEVICE_8S_MODE)
	{
		TIM4->ARR = 8084;
	}
	else
	{
		TIM4->ARR = 10150;
	}
  //38.4k -2% - +3%
	//38.4 / (37+1) = 1.011 kHz
	TIM4->PSC = 37;
  TIM4->SR |= TIM_SR_ARF;
	TIM4->CR2 = TIM_CR2_ARI;
	TIM4->CR1 |= TIM_CR1_EN;
	while((TIM4->CR1 & TIM_CR1_EN) == 0){__NOP();}
	
	NVIC_EnableIRQ(EXTIA_IRQn);
	NVIC_EnableIRQ(EXTIB_IRQn);
  NVIC_EnableIRQ(TIM4_IRQn);
	
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
	__NOP();
	__WFI();
	__NOP();
  
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	
  NVIC_DisableIRQ(TIM4_IRQn);
  NVIC_DisableIRQ(EXTIA_IRQn);
	NVIC_DisableIRQ(EXTIB_IRQn);

  TIM4->CR1 &= ~TIM_CR1_EN;
  while((TIM4->CR1 & TIM_CR1_EN) == TIM_CR1_EN){__NOP();}
  
	//KY3 -> PA7
  //KY4 -> PA9
	EXTIA->IEC |= TEST_PIN + AC_PIN;

	//IO_PIN -> PB3
  //KY2 -> PB5
	EXTIB->IEC |= IO_PIN + EXT_PIN;

	//KY1 -> PB4 输入上拉 
	GPIOB->OEC |= LOCAL_PIN;
	GPIOB->PUS |= LOCAL_PIN;
	
  fe_set_system_tick_timer();
	TIM5->CR1 |= TIM_CR1_EN;
	open_swdg();

  if(system_data.masking & SYSTEM_INTERRUPT_FLAG_MSK)
  {
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
			{
				mem_data_add(&timer5.t[8],8000,8);//2s
			}
			else
			{
				mem_data_add(&timer5.t[8],2000,8);//10s
			}
		}
    else if(system_data.state & DEVICE_8S_MODE)
    {
      mem_data_add(&timer5.t[8],8000,8);//8s
    }
    else
    {
      mem_data_add(&timer5.t[8],10000,8);//10s
    }
		
    message_execution();
		
    system_data.masking &= ~SYSTEM_INTERRUPT_FLAG_MSK;
  }
}


/*---------------------------------------------------------------------------------------------------------*/


