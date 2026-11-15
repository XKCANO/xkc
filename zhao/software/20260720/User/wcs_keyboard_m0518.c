#include "wcs_keyboard_m0518.h"
#include "WCS_M0518_DEF.h"


KEY_TYPEDEF key;


/**
  * @brief  scan key.
  * @param  
	  key: key1,key2,key3
		key:value
  * @retval None
  */
void Scan_Key_Process(unsigned short module,unsigned char *value)
{
  if((*value & 0x01) != 0)
	{
		if(module == 0)
		{
			if((*value & 0x08) != 0)
			{
				*value = 0x10;
			}
			else
			{
				*value |= 0x08;
			}
		}
		else
		{
			*value &= ~0x08;
		}
	}
	else
	{
		if(module != 0) 
		{
			if((*value & 0x08) != 0)
			{
				*value = 0x21;
			}
			else
			{
				*value |= 0x08;
			}
		}
		else
		{
			*value &= ~0x08;
		}
  }
}

/**
  * @brief  test key down event.
  * @param  None
  * @retval None
  */
void Key1_Downevent(void)
{
  key.value1 &= ~0x10;
  
  if(system_data.led_value < 9)
  {
    system_data.led_value++;
    system_data.signal |= UPDATE_LED_SIGNAL_FLAG_MSK + UPDATE_RED_SIGNAL_FLAG_MSK;
    system_data.masking |= SYSTEM_MESSAGE_FLAG_MSK;
  }
}

/**
  * @brief  test key up event.
  * @param  None
  * @retval None
  */
void Key1_Upevent(void) 
{ 
  key.value1 &= ~0x20;
}

/**
  * @brief  learn key down event.
  * @param  None
  * @retval None
  */
void Key2_Downevent(void)
{
	key.value2 &= ~0x10;
  
  if(system_data.led_value > 0 && system_data.led_value <= 9)
  {
    system_data.led_value--;
    system_data.signal |= UPDATE_LED_SIGNAL_FLAG_MSK + UPDATE_RED_SIGNAL_FLAG_MSK;
    system_data.masking |= SYSTEM_MESSAGE_FLAG_MSK;
  }
}

/**
  * @brief  learn key up event.
  * @param  None
  * @retval None
  */
void Key2_Upevent(void) 
{
	key.value2 &= ~0x20;
}

/**
  * @brief  learn key down event.
  * @param  None
  * @retval None
  */
void Key3_Downevent(void)
{
	key.value3 &= ~0x10;
  
  PC->DOUT ^= LEDH_PIN;
  
  system_data.masking ^= SYSTEM_AUTO_MODE_FLAG_MSK;
  
  if(system_data.masking & SYSTEM_AUTO_MODE_FLAG_MSK)
  {
    Open_Timer0();
    Close_Adc_Ch0();
  }
  else
  {
    Close_Timer0();
    Open_Adc_Ch0();
  }
}

/**
  * @brief  learn key up event.
  * @param  None
  * @retval None
  */
void Key3_Upevent(void) 
{
	key.value3 &= ~0x20;
}









