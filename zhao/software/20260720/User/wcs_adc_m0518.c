#include "wcs_adc_m0518.h"
#include "WCS_M0518_DEF.h"

ADC0_typedef adc0;


/**
 * @brief       ADC IRQ
 * @param       None
 * @return      None
 * @details     The ADC default IRQ, declared in startup_M0518.s.
 */
void ADC_IRQHandler(void)
{
  ADC->ADSR = ADC_ADSR_CMPF0_Msk;
  adc0.value[adc0.idx++] = ADC->ADDR[0];

  system_data.signal |= ADC0_UPDATE_SIGNAL_FLAG_MSK;
  system_data.masking |= SYSTEM_MESSAGE_FLAG_MSK;
}

/**
  * @brief      Open ADC CH0
  * @param[in]  null
  * @return     None
  * @details    HIRC -> 22.1184Mhz
  */
void Open_Adc_Ch0(void)
{
  //GPIO -> ADC0
  SYS->GPA_MFP |= 0x0001;
  //DIV = (1+1) -> 11.0592Mhz
  CLK->CLKDIV |= 0x10000;
  //clock enable
  CLK->APBCLK |= CLK_APBCLK_ADC_EN_Msk;
  
  ADC->ADCR = ADC_ADCR_ADMD_Msk + ADC_ADCR_ADEN_Msk;
  ADC->ADCHER = ADC_ADCMPR_CMPEN_Msk;
  //compare data: 500
  ADC->ADCMPR[0] = (500 << 16) + (2 << 8) + 0x07;
  ADC->ADSR = ADC_ADSR_CMPF0_Msk + ADC_ADSR_ADF_Msk;
  NVIC_EnableIRQ(ADC_IRQn);

  ADC->ADCR |= ADC_ADCR_ADST_Msk;
}

/**
  * @brief      Close Timer0 Capture
  * @param[in]  null
  * @return     None
  * @details
  */
void Close_Adc_Ch0(void)
{
  NVIC_DisableIRQ(ADC_IRQn);
 
  ADC->ADCR &= ~(ADC_ADCR_ADST_Msk + ADC_ADCR_ADEN_Msk);

  //GPIO -> ADC0
  SYS->GPA_MFP &= ~0x0001;
  //clock enable
  CLK->APBCLK &= ~CLK_APBCLK_ADC_EN_Msk;
}



