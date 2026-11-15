#include "wcs_timer_m0518.h"
#include "WCS_M0518_DEF.h"


Timer_typedef timer;
Timer0_typedef timer0;


/**
  * @brief      Set Systemtick Timer
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz
  */
void Open_System_Timer(void)
{
	SysTick->LOAD = 22118;
	SysTick->VAL = 22118;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief      Check Systemtick Interrupt flag
  * @param[in]  null
  * @return     None
  * @details    
  */
void Check_Sytem_Timer(void)
{
	uint32_t i;
  
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
	{
		i = 0;
		do{
			timer.t[i]++;
			i++;
		}while(i < TIMER_SIZE);
	}
}

/**
  * @brief      Close Systemtick Timer
  * @param[in]  null
  * @return     None
  * @details    
  */
void Close_System_Timer(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief       Timer0 IRQ
 * @param       None
 * @return      None
 * @details     The Timer0 default IRQ, declared in startup_M0518.s.
 */
void TMR0_IRQHandler(void)
{
  if(TIMER0->TEXISR & TIMER_TEXISR_TEXIF_Msk)
  {
    TIMER0->TEXISR = TIMER_TEXISR_TEXIF_Msk;
    TIMER0->TCSR |= TIMER_TCSR_IE_Msk;
    
    timer0.capture_value[0] = TIMER0->TCAP;
    timer0.cont = 0;
    
    system_data.signal |= TIMER0_UPDATE_SIGNAL_FLAG_MSK;
    system_data.state |= TIMER0_UPDATE_STATE_FLAG_MSK;
    system_data.masking |= SYSTEM_MESSAGE_FLAG_MSK;
  }
  
  if(TIMER0->TISR & TIMER_TISR_TIF_Msk)
  {
    TIMER0->TISR = TIMER_TISR_TIF_Msk;
    
    if(system_data.state & TIMER0_UPDATE_STATE_FLAG_MSK)
    {
      timer0.cont++;
    }
  }
}

/**
  * @brief      Open Timer0 Capture
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz -> 758ms
  */
void Open_Timer0(void)
{
  SYS->GPB_MFP |= 0x80008000;
  SYS->ALT_MFP |= 0x1000000;
  
  //clock enable
  CLK->APBCLK |= CLK_APBCLK_TMR0_EN_Msk;
  
  TIMER0->TCSR = TIMER_TCSR_MODE_Msk;
  TIMER0->TCMPR = 0xFFFFFF;
  TIMER0->TEXCON = 0x68;
  TIMER0->TEXISR = TIMER_TEXISR_TEXIF_Msk;
  TIMER0->TISR = TIMER_TISR_TIF_Msk;
  
  NVIC_EnableIRQ(TMR0_IRQn);
  
  TIMER0->TCSR |= TIMER_TCSR_CEN_Msk;
}

/**
  * @brief      Close Timer0 Capture
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz
  */
void Close_Timer0(void)
{
  NVIC_DisableIRQ(TMR0_IRQn);
  
  TIMER0->TCSR &= ~TIMER_TCSR_CEN_Msk;
  
  SYS->GPB_MFP &= ~0x80008000;
  SYS->ALT_MFP &= ~0x1000000;

  //clock disable
  CLK->APBCLK &= ~CLK_APBCLK_TMR0_EN_Msk;
}

/**
 * @brief       Pwm0 IRQ
 * @param       None
 * @return      None
 * @details     The Pwm0 default IRQ, declared in startup_M0518.s.
 */
void PWM0_IRQHandler(void)
{
  if(PWM0->INTSTS0 & PWM_INTSTS0_CMPDIF0_Msk)
  {
    PWM0->INTSTS0 = PWM_INTSTS0_CMPDIF0_Msk;
  }
}

/**
  * @brief      Open PWM0 CH0
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz
  */
void Open_Pwm0_Ch0(void)
{
  //clock enable
  CLK->APBCLK1 |= 0x20000;

  PWM0->CTL0 = PWM_CTL0_CTRLD0_Msk;
  PWM0->CTL1 = 0x02;
  //22.1184M / 8 = 2764.8khz
  PWM0->CLKPSC0_1 = 7;
  //2764800/(2*200) = 6912
  PWM0->PERIOD[0] = 6912;
  PWM0->CMPDAT[0] = 3456;
  PWM0->CNT[0] = 0x10000;
  
  PWM0->WGCTL0 |= 0x0001;
  PWM0->WGCTL1 |= 0x30001;
  PWM0->INTEN0 |= PWM_INTEN0_CMPDIEN0_Msk;
  
  PWM0->CNTEN |= 0x01;
  
  NVIC_EnableIRQ(PWM0_IRQn);
}

/**
  * @brief      Close PWM0 CH0
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz
  */
void Close_Pwm0_Ch0(void)
{
  PWM0->CNTEN &= ~0x01;
  PWM0->CNT[0] = 0x10000;
  
  CLK->APBCLK1 &= ~0x20000;
}










