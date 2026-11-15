#include "wcs_message_m0518.h"
#include "WCS_M0518_DEF.h"



/****
  * @brief 数组右移，最后一个数据被丢弃
	*
	* @param[in]: 数组地址
	* @param[in]: 数组长度
	*
	* @return:无
*****/
void array_right_uint32_t(unsigned int *arr, unsigned short l) 
{
	for(unsigned short i = l - 1; i > 0; i--)
	{
		arr[i] = arr[i-1];
	}
}

/****
  * @brief 数组右移，最后一个数据被丢弃
	*
	* @param[in]: 数组地址
	* @param[in]: 数组长度
	*
	* @return:无
*****/
void array_right_uint16_t(unsigned short *arr, unsigned short l) 
{
	for(unsigned short i = l - 1; i > 0; i--)
	{
		arr[i] = arr[i-1];
	}
}
  

/****
  * @brief 数组值清空
	*
	* @param[in]: 数组地址
	* @param[in]: 数组长度
	*
	* @return:无
*****/
void array_clear(unsigned int *arr, unsigned short l) 
{
	for(unsigned short i = l - 1; i > 0; i--)
	{
		arr[i] = 0;
	}
}

/**
  * @brief  test key up event.
  * @param  None
  * @retval None
  */
void System_Message_Process(void)
{
  system_data.masking &= ~SYSTEM_MESSAGE_FLAG_MSK;
  
  if(system_data.signal & UPDATE_LED_SIGNAL_FLAG_MSK)
  {
    Display_Led_Management(system_data.led_value);
    system_data.signal &= ~UPDATE_LED_SIGNAL_FLAG_MSK;
  }
  
  if(system_data.signal & UPDATE_RED_SIGNAL_FLAG_MSK)
  {
    Display_Red_Management(system_data.led_value);
    system_data.signal &= ~UPDATE_RED_SIGNAL_FLAG_MSK;
  }
  
  if(system_data.signal & TIMER0_UPDATE_SIGNAL_FLAG_MSK)
  {
    system_data.signal &= ~TIMER0_UPDATE_SIGNAL_FLAG_MSK;

    if(system_data.masking & TIMER0_INIT_FLAG_MSK)
    {
      system_data.masking &= ~TIMER0_INIT_FLAG_MSK;
    }
    else
    {
      if(timer0.capture_value[0] >= timer0.capture_value[1])
      {
        timer0.period_value[0] = timer0.capture_value[0] - timer0.capture_value[1];
      }
      else
      {
        timer0.period_value[0] = 0x1000000 - timer0.capture_value[1] + timer0.capture_value[0];
      }
      
      array_right_uint32_t(timer0.period_value,128);
    }
    
    array_right_uint32_t(timer0.capture_value,2);
  }
  
  if(system_data.signal & ADC0_UPDATE_SIGNAL_FLAG_MSK)
  {
    ADC->ADCMPR[0] &= ~0x07;
    
    while(adc0.idx <= 63)
    {
      while((ADC->ADSR & ADC_ADSR_ADF_Msk) == 0);
      adc0.value[adc0.idx++] = ADC->ADDR[0];
    }
    
    adc0.idx = 0;
    ADC->ADCMPR[0] |= 0x07;
    ADC->ADCR |= ADC_ADCR_ADST_Msk;
    
    system_data.signal &= ~ADC0_UPDATE_SIGNAL_FLAG_MSK;
  }
  
  
}

