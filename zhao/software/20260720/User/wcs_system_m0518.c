#include "wcs_system_m0518.h"

/**
  * @brief      Clear System SRAM
  * @param[in]  null
  * @return     None
  * @details    SRAM 16K:0x2000 0000 -0x2000 3FFF
  */
void Clear_Sram(void)
{
  unsigned int i, l;
	l = __get_MSP();
	l = (l & 0x00003FFF) / 4;
	i = 0;
	do{
		((unsigned int *)SRAM_BASE)[i] = 0;
		i++;
	}while(i < l);
}

/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  *
  */
void Sys_Unlockreg(void)
{
  while(SYS->REGWRPROT != SYS_REGWRPROT_REGPROTDIS_Msk)
  {
    SYS->REGWRPROT = 0x59;
    SYS->REGWRPROT = 0x16;
    SYS->REGWRPROT = 0x88;
  }
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
void Sys_Lockreg(void)
{
  SYS->REGWRPROT = 0;
}

/**
  * @brief      Set System Clock
  * @param[in]  null
  * @return     None
  * @details
  */
void System_Clock_Init(void)
{
  //Unlock register
  Sys_Unlockreg();
  
  //Enable HIRC
  CLK->PWRCON |= CLK_PWRCON_IRC22M_EN_Msk;
  while((CLK->CLKSTATUS & CLK_CLKSTATUS_IRC22M_STB_Msk) != CLK_CLKSTATUS_IRC22M_STB_Msk);
  //HCLK = 22.1184M
  CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_Msk;
  //DIV = 1
  CLK->CLKDIV &= ~0x000F;
  //ADC TIM0->HCLK
  CLK->CLKSEL1 |= 0x0280;
  //PWM0->PCLK
  CLK->CLKSEL3 |= 0x10000;

  //Systick ->hclk
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  
  //lock register
  Sys_Lockreg();
}

/**
  * @brief      Set System gpio
  * @param[in]  null
  * @return     None
  * @details
  */
void System_Gpio_Init(void)
{
  //PA 1110 1111 1000 0000
  //   |||| |||| |||| |||+-->ADC0
  //   |||| |||| |||| ||+--->NC
  //   |||| |||| |||| |+---->NC
  //   |||| |||| |||| +----->NC
  //
  //   |||| |||| |||+ ------>NC
  //   |||| |||| ||+- ------>NC
  //   |||| |||| |+-- ------>NC
  //   |||| |||| +--- ------>+5V
  //
  //   |||| |||+ ---- ------>RED8
  //   |||| ||+- ---- ------>RED7
  //   |||| |+-- ---- ------>RED6
  //   |||| +--- ---- ------>RED5
  //
  //   |||+ ---- ---- ------>PWM_OUT
  //   ||+- ---- ---- ------>KEY1
  //   |+-- ---- ---- ------>KEY2
  //   +--- ---- ---- ------>KEY3
  
  // I/O
  PA->PMD = 0x1551554;
  // OFF
  PA->OFFD = 0x00010000;
  //OUT_DATA
  PA->DOUT = 0x0F00;
  //DE bounce
  PA->DBEN = 0xE000;               
  
  //ADC0 PWM0_CH0
  //SYS->GPA_MFP |= 0x1001;
  
  
  //PB 0001 0001 0011 0010
  //   |||| |||| |||| |||+-->UART0_RX
  //   |||| |||| |||| ||+--->UART0_TX
  //   |||| |||| |||| |+---->DEBUG
  //   |||| |||| |||| +----->NC
  //
  //   |||| |||| |||+ ------>RED9
  //   |||| |||| ||+- ------>RED10
  //   |||| |||| |+-- ------>NC
  //   |||| |||| +--- ------>NC
  //
  //   |||| |||+ ---- ------>RED1
  //   |||| ||+- ---- ------>NC
  //   |||| |+-- ---- ------>NC
  //   |||| +--- ---- ------>NC
  //
  //   |||+ ---- ---- ------>RED2
  //   ||+- ---- ---- ------>NC
  //   |+-- ---- ---- ------>NC
  //   +--- ---- ---- ------>PWM_IN
  
  // I/O
  PB->PMD = 0x15555544;
  // OFF
  PB->OFFD = 0;
  //OUT
  PB->DOUT = 0x1132;
  //DE bounce
  PB->DBEN = 0x0004;
  
//  //UART
//  SYS->GPB_MFP |= 0x0003;
  
  
  //PC 0000 0000 0000 0000
  //   |||| |||| |||| |||+-->LED_H
  //   |||| |||| |||| ||+--->LED_C
  //   |||| |||| |||| |+---->LED_D
  //   |||| |||| |||| +----->LED_E
  //
  //   |||| |||| |||+ ------>NULL
  //   |||| |||| ||+- ------>NULL
  //   |||| |||| |+-- ------>NC
  //   |||| |||| +--- ------>NC
  //
  //   |||| |||+ ---- ------>NC
  //   |||| ||+- ---- ------>NC
  //   |||| |+-- ---- ------>NC
  //   |||| +--- ---- ------>NC
  //
  //   |||+ ---- ---- ------>NULL
  //   ||+- ---- ---- ------>NULL
  //   |+-- ---- ---- ------>NC
  //   +--- ---- ---- ------>NC
  
  // I/O
  PC->PMD = 0x55555555;
  // OFF
  PC->OFFD = 0;
  //OUT
  PC->DOUT = 0x000F;
  //DE bounce
  PC->DBEN = 0;
  
  
  //PD 0000 0000 0000 0000
  //   |||| |||| |||| |||+-->NULL
  //   |||| |||| |||| ||+--->NULL
  //   |||| |||| |||| |+---->NULL
  //   |||| |||| |||| +----->NULL
  //
  //   |||| |||| |||+ ------>NULL
  //   |||| |||| ||+- ------>NULL
  //   |||| |||| |+-- ------>LED_B
  //   |||| |||| +--- ------>LED_A
  //
  //   |||| |||+ ---- ------>NULL
  //   |||| ||+- ---- ------>NULL
  //   |||| |+-- ---- ------>NULL
  //   |||| +--- ---- ------>NULL
  //
  //   |||+ ---- ---- ------>NULL
  //   ||+- ---- ---- ------>NULL
  //   |+-- ---- ---- ------>LED_G
  //   +--- ---- ---- ------>LED_F
  
  // I/O
  PD->PMD = 0x55555555;
  // OFF
  PD->OFFD = 0;
  //OUT
  PD->DOUT = 0xC0C0;
  //DE bounce
  PD->DBEN = 0;
  
  //PF 0000 0000 0000 0000
  //   |||| |||| |||| |||+-->NC
  //   |||| |||| |||| ||+--->NC
  //   |||| |||| |||| |+---->NULL
  //   |||| |||| |||| +----->NULL
  //
  //   |||| |||| |||+ ------>RED4
  //   |||| |||| ||+- ------>RED3
  //   |||| |||| |+-- ------>ICE_CLK
  //   |||| |||| +--- ------>ICE_DAT
  //
  //   |||| |||+ ---- ------>NC
  //   |||| ||+- ---- ------>NULL
  //   |||| |+-- ---- ------>NULL
  //   |||| +--- ---- ------>NULL
  //
  //   |||+ ---- ---- ------>NULL
  //   ||+- ---- ---- ------>NULL
  //   |+-- ---- ---- ------>NULL
  //   +--- ---- ---- ------>NULL

  // I/O
  PF->PMD |= 0x55550555;
  // OFF
  PF->OFFD |= 0x00300000;
  //OUT
  PF->DOUT |= 0x0030;
  //DE bounce
  PF->DBEN &= ~0xFF3F;
}














