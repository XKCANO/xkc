#include "755PSMA5L_Keyboard_PT32L076.h"

MULTIPLE_KEY_Tytedef key2;

SIMPLE_KEY_Tytedef key3;
SIMPLE_KEY_Tytedef key4;
SIMPLE_KEY_Tytedef key5;

/************************************************************************
** @brief  °´¼üÍâ²¿ÖÐ¶Ï  
** @param  Void
** @note   
** @retval None
************************************************************************/
void EXTIA_Handler(void)
{
	uint32_t i;
	
	i = EXTIA->IF;
	EXTIA->IF |= i;
	
	if(i & TEST_PIN)
	{
    //KY3 -> PA7
		KEY3_TIMER += 50;
	}
	if(i & AC_PIN)
	{
		//KY4 -> PA10
		key4.h_time = 0;
		key4.l_time = 0;
    system_data.masking |= AC_CHECK_FLAG_MSK;
	}
}

void EXTIB_Handler(void)
{
	uint32_t i;
	
	i = EXTIB->IF;
	EXTIB->IF |= i;
	
	if(i & IO_PIN)
	{
		//IO_PIN -> PB3
		key5.h_time = 0;
    KEY3_TIMER += 50;
		system_data.masking |= RIN_CHECK_FLAG_MSK;
	}
	if(i & EXT_PIN)
	{
		//KY2 -> PB5
		key2.h_time = 0;
		key2.l_time = 0;
		system_data.masking |= EXT_CHECK_FLAG_MSK;
	}
}

/************************************************************************
** @brief  ScanTestKeyProcess 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void scankey3_process_run(void)
{
	if((key3.value & 0x01) != 0)
	{
		if(TEST_KEY == 0)
		{
			if((key3.value & 0x08) != 0)
			{
				key3.value = 0x10;
				key3.l_time = 0;
			}
			else
			{
				key3.value |= 0x08;
			}
		}
		else
		{
			key3.value &= ~0x08;
		}
	}
	else
	{
		if(TEST_KEY != 0)
		{
			if((key3.value & 0x08) != 0)
			{
				key3.value = 0x81;
			}
			else
			{
				key3.value |= 0x08;
			}
		}
		else
		{
			if(key3.l_time < 255)
			{
			  key3.l_time++;
			}
			if(key3.l_time == 16)
			{
				key3.value |= 0x20;
			}
			else if(key3.l_time == 200)
			{
				key3.value |= 0x40;
			}
			key3.value &= ~0x08;
		}
	}
}

/************************************************************************
** @brief  Key3 Event 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void key3_down_event(void)
{
	key3.value &= ~0x10;
	
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
	  system_data.masking |= KEY3_DOWN_FLAG_MSK;
	}
}

void key3_08s_event(void)
{
	key3.value &= ~0x20;
	
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
		system_data.masking &= ~KEY3_DOWN_FLAG_MSK;
		system_data.masking |= KEY3_08S_FLAG_MSK + MESSAGE_FLAG_MSK;
	}
}

void key3_10s_event(void)
{
	key3.value &= ~0x40;
	
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
	  system_data.masking |= KEY3_10S_FLAG_MSK + MESSAGE_FLAG_MSK;
	}
}

void key3_up_event(void)
{
	key3.value &= ~0x80;
	
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
	  system_data.masking |= KEY3_UP_FLAG_MSK + MESSAGE_FLAG_MSK;
	}
}

/************************************************************************
** @brief  É¨Ãè»¥ÁªÊäÈë×´Ì¬
** @param  Void
** @note   
** @retval None
************************************************************************/
void scankey2_process_run(void)
{
	if(key2.value == 0)  
	{
		if(EXT_KEY != 0)
		{
			key2.h_time++;
			if(key2.h_time >= 8)
			{
				key2.value = 0x01;
				key2.h_time = 0;
				key2.l_time = 0;
				
				system_data.signal &= ~(DEVICE_EXTERNAL_ERROR_FLAG_MSK + DEVICE_EXTERNAL_ALARM_FLAG_MSK);
				system_data.masking |= MESSAGE_FLAG_MSK;
			}		
		}
		else
		{
			key2.h_time = 0;
		}
	}
	else
	{
		if((system_data.masking & EXT_CHECK_FLAG_MSK) == 0)
		{
			if(EXT_KEY == 0)
			{
				key2.h_time = 0;
				key2.l_time = 0;
				system_data.masking |= EXT_CHECK_FLAG_MSK;
			}
		}
		else
		{
			if(EXT_KEY != 0)
			{
				key2.h_time++;
			}
			else
			{
				key2.l_time++;
			}
			if((system_data.masking & KEY2_PENDING_FLAG_MSK) == 0)
			{
				if((key2.h_time + key2.l_time) >= 20)
				{
					if(key2.h_time >= 6 && key2.l_time >= 6)
					{
						key2.value = 0;
						key2.h_time = 0;
						system_data.masking &= ~EXT_CHECK_FLAG_MSK;

						if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
						{
							system_data.signal |= DEVICE_EXTERNAL_ERROR_FLAG_MSK;
							system_data.masking |= MESSAGE_FLAG_MSK;
						}
					}
					else if(key2.h_time == 0)
					{
						system_data.masking |= KEY2_PENDING_FLAG_MSK;
					}
					else
					{
						key2.h_time = 0;
						key2.l_time = 0;
						system_data.masking &= ~EXT_CHECK_FLAG_MSK;
					}
				}
			}
			else
			{
				if((key2.h_time + key2.l_time) >= 400)
				{
					if(key2.l_time >= 400)
					{
						key2.value = 0;

						if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
						{
							system_data.signal |= DEVICE_EXTERNAL_ALARM_FLAG_MSK;
							system_data.masking |= MESSAGE_FLAG_MSK;
						}
					}
					key2.h_time = 0;
					key2.l_time = 0;
					system_data.masking &= ~(KEY2_PENDING_FLAG_MSK + EXT_CHECK_FLAG_MSK);
				}
			}
	  }
  }
}

/************************************************************************
** @brief  AC ¼ì²â
** @param  Void
************************************************************************/
void scankey4_process_run(void)
{
	if(key4.value == 0)
	{
		if(AC_KEY == 0)
		{
			key4.l_time++;
			if(key4.l_time == 1)
			{
				system_data.masking |= AC_CHECK_FLAG_MSK;
			}
			if(key4.l_time >= 8)
			{
				key4.value = 0x01;
				key4.l_time = 0;
				key4.l_time = 0;
				system_data.masking &= ~AC_CHECK_FLAG_MSK;
				fe_set_backup_power_source();
			}
		}
		else
		{
			key4.l_time = 0;
			system_data.masking &= ~AC_CHECK_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.masking & AC_CHECK_FLAG_MSK) == 0)
		{
			if(AC_KEY != 0)
			{
				key4.h_time = 0;
				key4.l_time = 0;
				system_data.masking |= AC_CHECK_FLAG_MSK;
			}
		}
		else
		{
			if(AC_KEY != 0)
			{
				key4.h_time++;
			}
			else
			{
				key4.l_time++;
			}
			if((key4.h_time + key4.l_time) >= 12)
			{
				if(key4.h_time >= 4)
				{
					key4.value = 0;
					fe_set_main_power_source();
				}
				key4.h_time = 0;
				key4.l_time = 0;
				system_data.masking &= ~AC_CHECK_FLAG_MSK;
			}
		}
	}
}

/************************************************************************
** @brief  Realy ±¨¾¯¼ì²â
** @param  Void
************************************************************************/
void scankey5_process_run(void)
{
	if(key5.value == 0)
	{
		if(IO_KEY != 0)
		{
			key5.h_time++;
			
			if(key5.h_time >= 20)
			{
				key5.value = 0x01;
				key5.h_time = 0;
				system_data.masking &= ~RIN_CHECK_FLAG_MSK;
				if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
				{
					system_data.signal |= DEVICE_RELAYIN_ALARM_FLAG_MSK;
					system_data.masking |= MESSAGE_FLAG_MSK;
				}
			}
		}
		else
		{
			key5.h_time = 0;
			system_data.masking &= ~RIN_CHECK_FLAG_MSK;
		}
	}
	else
	{
		if(IO_KEY == 0)
		{
			key5.h_time++;
			if(key5.h_time >= 2)
			{
				key5.value = 0;
				key5.h_time = 0;
				if((system_data.signal & DEVICE_RELAYIN_ALARM_FLAG_MSK) != 0)
				{
					system_data.signal &= ~DEVICE_RELAYIN_ALARM_FLAG_MSK;
					system_data.masking |= MESSAGE_FLAG_MSK;
				}
			}
		}
		else
		{
			key5.h_time = 0;
		}
	}
}


