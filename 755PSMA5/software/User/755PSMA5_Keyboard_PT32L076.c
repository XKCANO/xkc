#include "755PSMA5_Keyboard_PT32L076.h"

MULTIPLE_KEY_Tytedef key2;
MULTIPLE_KEY_Tytedef key3;

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
	if(EXTIA->IF & TEST_PIN)
	{
		//KY3 -> PA7
		EXTIA->IF |= TEST_PIN;
		KEY3_TIMER += 50;
		system_data.masking |= TEST_HOLD_FLAG_MSK;
	}
	else if(EXTIA->IF & AC_PIN)
	{
		//KY4 -> PA10
		EXTIA->IF |= AC_PIN;
		system_data.masking |= AC_CHECK_FLAG_MSK;
	}
  else
	{
		EXTIA->IF |= 0xFFFF;
	}
}

void EXTIB_Handler(void)
{
	if(EXTIB->IF & IO_PIN)
	{
		//IO_PIN -> PB3
		EXTIB->IF |= IO_PIN;
		system_data.masking |= RIN_CHECK_FLAG_MSK;
	}
	else if(EXTIB->IF & EXT_PIN)
	{
		//KY2 -> PB5
		EXTIB->IF |= EXT_PIN;
		system_data.masking |= EXT_CHECK_FLAG_MSK;
	}
	else
	{
		EXTIB->IF |= 0xFFFF;
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
  if(key3.value == 0x01)
	{
		if(TEST_KEY)
		{
			key3.value = 0x01;
			key3.hold_t = 0;
			system_data.masking &= ~TEST_HOLD_FLAG_MSK;
		}
		else
		{
			key3.hold_t++;
			
			if(key3.hold_t >= 2)
			{
				key3.hold_t = 0;
				key3.value = 0x02;
			}
		}
	}
	else if(key3.value == 0x02)
	{
    if(TEST_KEY)
		{
			key3.hold_t = 0;
		  key3.value = 0x04;
		}
		else
		{
			key3.hold_t++;
			
			if(key3.hold_t >= 16)
			{
				key3.hold_t = 0;
				key3.value = 0x10;
			}
		}
	}
	else if(key3.value == 0x04)
	{
		if(TEST_KEY)
		{
			key3.value = 0x08;
		}
		else
		{
			key3.value = 0x02;
		}
	}
  else if(key3.value == 0x20)
	{
		if(TEST_KEY)
		{
			key3.value = 0x40;
		}
	}
	else if(key3.value == 0x40)
	{
		if(TEST_KEY)
		{
			key3.value = 0x80;
		}
	}
}

/************************************************************************
** @brief  TestKeyDownEvent 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void key3_shortevent(void)
{
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
		system_data.masking &= ~TEST_HOLD_FLAG_MSK;
		
		if((system_data.state & KEY3_NO_RESPONSE1) == 0)
		{
			if(system_data.state & ALARM_FLAG_MSK)
			{
				system_data.signal |= DEVICE_HUSH_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & (SNOOZE_FAULT_FLAG_MSK + SNOOZE_LOW_FLAG_MSK))
			{
				if(system_data.state & ALARM_MEMORY_FLAG_MSK)
				{
					system_data.signal |= DEVICE_SNOOZE_MEMORY_FLAG_MSK;
					system_data.masking |= MESSAGE_FLAG_MSK;
				}
			}
			else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
			{
				system_data.signal |= DEVICE_SNOOZE_FAULT_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
				
				if(system_data.state & LOW_BATTERY_FLAG_MSK)
				{
					if(system_data.state & ALARM_MEMORY_FLAG_MSK)
					{
						system_data.signal |= DEVICE_SNOOZE_LOW_FLAG_MSK + DEVICE_SNOOZE_MEMORY_FLAG_MSK;
					}
				}
			}
			else if(system_data.state & LOW_BATTERY_FLAG_MSK)
			{
				system_data.signal |= DEVICE_SNOOZE_LOW_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & ALARM_MEMORY_FLAG_MSK)
			{
				system_data.signal |= DEVICE_SNOOZE_MEMORY_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state == 0)
			{
				system_data.signal |= DEVICE_SHORT_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
  }

	key3.value = 0x01;
}

void key3_longevent(void)
{
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
		if((system_data.state & KEY3_NO_RESPONSE) == 0)
		{
			if(system_data.state & HUSH_FLAG_MSK)
			{
				system_data.signal |= DEVICE_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & DEVICE_ALARM_FLAG_MSK)
			{
				system_data.signal |= DEVICE_HUSH_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & SNOOZE_FAULT_FLAG_MSK)
			{
				if(system_data.state & ALARM_MEMORY_FLAG_MSK)
				{
					system_data.signal |= SNOOZE_MEMORY_FLAG_MSK;
					system_data.masking |= MESSAGE_FLAG_MSK;
				}
			}
			else if(system_data.state & SNOOZE_LOW_FLAG_MSK)
			{
				system_data.signal |= DEVICE_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
			{
				system_data.signal |= DEVICE_SNOOZE_FAULT_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state & (LOW_BATTERY_FLAG_MSK + ALARM_MEMORY_FLAG_MSK + SNOOZE_MEMORY_FLAG_MSK))
			{
				system_data.signal |= DEVICE_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			else if(system_data.state == 0)
			{
				system_data.signal |= DEVICE_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
	
	key3.value = 0x20;
}

void key3_upevent(void)
{
	if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
	{
		if(system_data.signal & DEVICE_TEST_FLAG_MSK)
		{
			system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
		}
		
		system_data.masking &= ~TEST_HOLD_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}

	key3.value = 0x01;
}

/************************************************************************
** @brief  É¨Ãè»¥ÁªÊäÈë×´Ì¬
** @param  Void
** @note   
** @retval None
************************************************************************/
void scankey2_process_run(void)
{
	if(key2.value)
	{
		if(EXT_KEY)
		{
			key2.h_time++;
		}
		else
		{
			key2.l_time++;
		}
		
		if((key2.h_time + key2.l_time) >= 400)
		{
			if(key2.l_time >= 400 && key2.h_time == 0)
			{
				key2.value = 0;
				
				if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
				{
					if((system_data.state & KEY2_NO_RESPONSE) == 0)
					{
						system_data.signal |= DEVICE_EXTERNAL_ALARM_FLAG_MSK;
						system_data.masking |= MESSAGE_FLAG_MSK;
					}
				}
			}
			else if(key2.h_time >= 100 && key2.l_time >= 200)
			{
				key2.value = 0;
				
				if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
				{
					if((system_data.state & KEY2_NO_RESPONSE) == 0)
					{
						system_data.signal |= DEVICE_EXTERNAL_ERROR_FLAG_MSK;
						system_data.masking |= MESSAGE_FLAG_MSK;
					}
				}
		  }
			
		  key2.h_time = 0;
		  key2.l_time = 0;
			system_data.masking &= ~EXT_CHECK_FLAG_MSK;
	  }
	}
	else
	{
		if(EXT_KEY)
		{
			key2.h_time++;
			
			if(key2.h_time >= 4)
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
}

/************************************************************************
** @brief  AC ¼ì²â
** @param  Void
************************************************************************/
void scankey4_process_run(void)
{
	if(key4.value)
	{
		if(AC_KEY)
		{
			key4.h_time++;
		}
		else
		{
			key4.l_time++;
		}
		
		if((key4.h_time + key4.l_time) >= 8)
		{
			if(key4.l_time >= 2)
			{
				key4.value = 0;
				fe_set_main_power_source();
			}
			key4.h_time = 0;
			key4.l_time = 0;
			system_data.masking &= ~AC_CHECK_FLAG_MSK;
		}
	}
	else
	{
    if(AC_KEY)
		{
			key4.h_time++;
			if(key4.h_time >= 4)
			{
				key4.value = 0x01;
				key4.h_time = 0;
				key4.l_time = 0;
				fe_set_backup_power_source();
			}
		}
		else
		{
			key4.h_time = 0;
		}
	}
}

/************************************************************************
** @brief  Realy ±¨¾¯¼ì²â
** @param  Void
************************************************************************/
void scankey5_process_run(void)
{
	if(key5.value)
	{
		if(IO_KEY)
		{
			key5.h_time++;
		}
		else
		{
			key5.h_time = 0;
		}
		
		if(key5.h_time >= 200)
		{
			key5.value = 0;
			key5.h_time = 0;
			key5.l_time = 0;
			
			if((system_data.state & KEY5_NO_RESPONSE) == 0)
			{
				if((system_data.masking & IO_OUTPUT_FLAG_MSK) == 0)
				{
					system_data.signal |= DEVICE_RELAYIN_ALARM_FLAG_MSK;
					system_data.masking &= ~RIN_CHECK_FLAG_MSK;
					system_data.masking |= MESSAGE_FLAG_MSK;
				}
			}
		}
	}
	else
	{
		if(IO_KEY)
		{
			key5.l_time = 0;
		}
		else
		{
			key5.l_time++;
		}
		
		if(key5.l_time >= 200)
		{
			key5.value = 0x01;
			key5.h_time = 0;
			key5.l_time = 0;
			
			system_data.signal &= ~DEVICE_RELAYIN_ALARM_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
}




