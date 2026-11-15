#include "FE_755LHA_System_PT32L031.h"
#include "PT32X031.h"
 

/* =========================================================================== */

/* =========================================================================== */

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
	CMSDK_SYSCON->SYSCLK &= ~(SYSCON_SYSCLK_WAKE_DELAY + SYSCON_SYSCLK_FDFAIL_DETECTEN + SYSCON_SYSCLK_EOSFAIL_DETECTEN + SYSCON_SYSCLK_PCLKDIV + SYSCON_SYSCLK_HCLKDIV + SYSCON_SYSCLK_FDCLKSEL + SYSCON_SYSCLK_SYSCLKSEL);
	CMSDK_SYSCON->SYSCLK |= (SYSCON_SYSCLK_RECOVER_SEL + SYSCON_SYSCLK_PCLKDIV_1DIV + SYSCON_SYSCLK_HCLKDIV_1DIV);
}
/* =========================================================================== */
// 
/* =========================================================================== */


/**********************************************************************
  * @brief  This Function Of The System GPIO .
  * @param  None
  * @retval None
  *********************************************************************/
void sys_gpio_init(void)
{
	//PA 0000 0110 0000 1000
	//   |||| |||| |||| |||+--> BL_EN(输出)
	//   |||| |||| |||| ||+---> BTS(输出)
	//   |||| |||| |||| |+----> KY3(输入)
	//   |||| |||| |||| +-----> RDE1(输出)
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
	//   +--------------------> CS // 输入

	//输出锁存
	CMSDK_PA->DATAOUT = 0x060C;
	//输入使能
	CMSDK_PA->OUTENABLECLR |= (1 << 2) + (1 << 8) + (1 << 10) + (1 << 15);
	//输出使能
	CMSDK_PA->OUTENABLESET |= (1 << 0) + (1 << 1) +(1 << 3) + 
	                          (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7) + 
													  (1 << 9) + (1 << 11) + 
													  (1 << 12);
  //数字复用失能
	CMSDK_PA->ALTFUNCCLR |= 0x9FFF;
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

  //PB 0000 0000 1011 1000
	//   |||| |||| |||| |||+--> I_OUT(输出)
	//   |||| |||| |||| ||+---> KY2(输入)
	//   |||| |||| |||| |+----> IO_PIN(输入)
	//   |||| |||| |||| +-----> SCK   // 输入上拉
	//
	//   |||| |||| |||+-------> MISO
	//   |||| |||| ||+--------> MOSI  //输入
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
	CMSDK_PB->DATAOUT = 0x00B0;
	//输入使能
	CMSDK_PB->OUTENABLECLR |= (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
	//输出使能
  CMSDK_PB->OUTENABLESET |= (1 << 0) +  
                            (1 << 6) + (1 << 7) +	
	                          (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + 
													  (1 << 12) + (1 << 13) + (1 << 14) + (1 << 15);	

	//复用失能
	CMSDK_PB->ALTFUNCCLR |= 0xFFFF;
	//开漏失能
	CMSDK_PB->ODRCLR |= 0xFFFF;
	//上拉失能
	CMSDK_PB->PULLUPCLR |= 0xFFFF;
	//上拉使能
	CMSDK_PB->PULLDOWNSET |= 0x0008;
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

/* sck 配置
*
*/
void spi_enable_cfg(unsigned char mode)
{
	if(mode == 0)
	{
		//CS
    //下拉失能
	  CMSDK_PA->PULLDOWNCLR |= 0x8000;
		//输出
		CMSDK_PA->DATAOUT |= 0x80B8;
		//输出使能
		CMSDK_PA->OUTENABLESET |= 0x8000;
		
		//SCK 、MOSI
		//输出锁存
		CMSDK_PB->DATAOUT |= 0x00B8;
		//输出
		CMSDK_PB->OUTENABLESET |= 0x0028;
		//上拉失能
		CMSDK_PB->PULLUPCLR |= 0x0028;
	}
	else
	{
		//CS
		//输入
		CMSDK_PA->OUTENABLECLR |= 0x8000;
		//上拉失能
		CMSDK_PA->PULLUPCLR |= 0x8000;
    //下拉使能
	  CMSDK_PA->PULLDOWNSET |= 0x8000;
		
		//SCK 、MOSI
		//输入
		CMSDK_PB->OUTENABLECLR |= 0x0028;
	}
}






/*---------------------------------------------------------------------------------------------------------*/


