#include "755PSMA5_Message_PT32L076.h"


void messageproc(void)
{
	system_data.masking &= ~MESSAGE_FLAG_MSK;

	//火灾报警
	if((system_data.state & ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_ALARM_FLAG_MSK)
		{
			if(alarm_cfg(FIRE_MODE) == 0)
			{
				set_connect(3);
				system_data.state |= ALARM_FLAG_MSK;
				system_data.masking |= LATEST_ALARM_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.state & HUSH_FLAG_MSK) == 0)
		{
			if(system_data.signal & DEVICE_HUSH_FLAG_MSK)
			{
				alarm_del();
				ALARM_TIMER = 0;
				HUSH_TIMER = 0;
				system_data.state |= HUSH_FLAG_MSK;
			}
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
			{
				alarm_del();
				system_data.state &= ~ALARM_FLAG_MSK;
				system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
			}
		}
		else
		{
			if((system_data.signal & DEVICE_HUSH_FLAG_MSK) == 0)
			{
				system_data.state &= ~(HUSH_FLAG_MSK + ALARM_FLAG_MSK);
				system_data.masking |= MESSAGE_FLAG_MSK;
				system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
			}
		}
	}

	//长按测试
	if((system_data.state & TEST_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_TEST_FLAG_MSK)
		{
			if(alarm_cfg(TEST_MODE) == 0)
			{
				system_data.state |= TEST_FLAG_MSK;
				system_data.masking |= IO_OUTPUT_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_TEST_FLAG_MSK) == 0)
		{
			alarm_del();
			system_data.state &= ~TEST_FLAG_MSK;
		}
	}
	
	//短按测试
	if((system_data.state & SHORT_TEST_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SHORT_TEST_FLAG_MSK)
		{
			if(alarm_cfg(TEST_MODE) == 0)
			{
				system_data.state |= SHORT_TEST_FLAG_MSK;
				system_data.masking |= IO_OUTPUT_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SHORT_TEST_FLAG_MSK) == 0)
		{
			alarm_del();
			system_data.state &= ~SHORT_TEST_FLAG_MSK;
		}
	}
	
	//报警记忆
	if((system_data.state & ALARM_MEMORY_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_ALARM_MEMORY_FLAG_MSK)
		{
			ALARM_TIMER = 0;
			ALARM_MEMORY_TIMER = 0;
			system_data.state |= ALARM_MEMORY_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_ALARM_MEMORY_FLAG_MSK) == 0)
		{
			system_data.state &= ~ALARM_MEMORY_FLAG_MSK;
		}
	}
	
	//有线互联火灾报警
	if((system_data.state & EXTERNAL_ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK)
		{
			if(alarm_cfg(EXTERNAL_MODE) == 0)
			{
				if(LOCAL_KEY)
				{
					set_connect(2);
				}
				system_data.masking |= IO_OUTPUT_FLAG_MSK;
				system_data.state |= EXTERNAL_ALARM_FLAG_MSK;
				system_data.masking &= ~LATEST_ALARM_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK) == 0)
		{
			alarm_del();
			system_data.state &= ~EXTERNAL_ALARM_FLAG_MSK;
		}
	}
	
	//有线互联错误
	if((system_data.state & EXTERNAL_ERROR_FLAG_MSK) == 0) 
	{
		if(system_data.signal & DEVICE_EXTERNAL_ERROR_FLAG_MSK)
		{
			if(alarm_cfg(EXT_ERROR_MODE) == 0)
			{
				system_data.state |= EXTERNAL_ERROR_FLAG_MSK;
				system_data.masking |= IO_OUTPUT_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_EXTERNAL_ERROR_FLAG_MSK) == 0)
		{
			alarm_del();
			system_data.state &= ~EXTERNAL_ERROR_FLAG_MSK;
		}
	}

	//base互联火灾报警
	if((system_data.state & RELAYIN_ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_RELAYIN_ALARM_FLAG_MSK)
		{
			if(alarm_cfg(EXTERNAL_MODE) == 0)
			{
				set_connect(1);
				system_data.state |= RELAYIN_ALARM_FLAG_MSK;
				system_data.masking &= ~LATEST_ALARM_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_RELAYIN_ALARM_FLAG_MSK) == 0)
		{
			alarm_del();
			system_data.state &= ~RELAYIN_ALARM_FLAG_MSK;
		}
	}
	
	//传感器故障免打扰
	if((system_data.state & SNOOZE_FAULT_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SNOOZE_FAULT_FLAG_MSK)
		{
			if((system_data.state & (~SENSOR_FAULT_FLAG_MSK)) != 0)
			{
				ALARM_TIMER = 0;
				SNOOZE_FAULT_TIMER = 0;
				system_data.state |= SNOOZE_FAULT_FLAG_MSK;
			}
			else
			{
				if(alarm_cfg(LOW_BAT_MODE) == 0)
				{
					ALARM_TIMER = 0;
					SNOOZE_FAULT_TIMER = 0;
					system_data.state |= SNOOZE_FAULT_FLAG_MSK;
				}
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SNOOZE_FAULT_FLAG_MSK) == 0)
		{
			system_data.state &= ~SNOOZE_FAULT_FLAG_MSK;
		}
	}
	
	//低电压免打扰
	if((system_data.state & SNOOZE_LOW_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SNOOZE_LOW_FLAG_MSK)
		{
			ALARM_TIMER = 0;
			SNOOZE_LOW_TIMER = 0;
			system_data.state |= SNOOZE_LOW_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SNOOZE_LOW_FLAG_MSK) == 0)
		{
			system_data.state &= ~SNOOZE_LOW_FLAG_MSK;
		}
	}
	
	//报警记忆免打扰
	if((system_data.state & SNOOZE_MEMORY_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SNOOZE_MEMORY_FLAG_MSK)
		{
			ALARM_TIMER = 0;
			SNOOZE_MEMORY_TIMER = 0;
			system_data.state |= SNOOZE_MEMORY_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SNOOZE_MEMORY_FLAG_MSK) == 0)
		{
			system_data.state &= ~SNOOZE_MEMORY_FLAG_MSK;
		}
	}
	
	//传感器故障
	if((system_data.state & SENSOR_FAULT_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK)
		{
			ALARM_TIMER = 40000;
			system_data.state |= SENSOR_FAULT_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK) == 0)
		{
			system_data.state &= ~SENSOR_FAULT_FLAG_MSK;
		}
	}

	//低电压
	if((system_data.state & LOW_BATTERY_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_LOW_BATTERY_FLAG_MSK)
		{
			ALARM_TIMER = 40000;
			system_data.state |= LOW_BATTERY_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_LOW_BATTERY_FLAG_MSK) == 0)
		{
			system_data.state &= ~LOW_BATTERY_FLAG_MSK;
		}
	}
	
	//报警记忆
	if((system_data.state & ALARM_MEMORY_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_ALARM_MEMORY_FLAG_MSK)
		{
			ALARM_TIMER = 0;
			ALARM_MEMORY_TIMER = 0;
			system_data.state |= ALARM_MEMORY_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_ALARM_MEMORY_FLAG_MSK) == 0)
		{
			system_data.state &= ~ALARM_MEMORY_FLAG_MSK;
		}
	}
		
}

void message_execution(void)
{
	if(system_data.state == 0)
	{
		if(ALARM_TIMER >= 40000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(ONE_LOW_MODE);
		}
	}
	else if(system_data.state & LED_NULLIFY)
	{
		ALARM_TIMER = 0;
		ALARM_TIMER1 = 0;
	}
	else if(system_data.state & TEST_FLAG_MSK)
	{
		if(TEST_TIMER > 9499)
		{
			TEST_TIMER = 10000;
			set_connect(3);
		}
		ALARM_TIMER = 0;
		ALARM_TIMER1 = 0;
	}
	else if(system_data.state & HUSH_FLAG_MSK)
	{
		if(ALARM_TIMER >= 8000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(ONE_MED_MODE);
		}
		if(HUSH_TIMER >= 600000)
		{
			ALARM_TIMER = 0;
			HUSH_TIMER = 0;
			ALARM_MEMORY_TIMER = 0;
			system_data.signal &= ~DEVICE_HUSH_FLAG_MSK;
		}
	}
	else if(system_data.state & ALARM_FLAG_MSK)
	{
		ALARM_TIMER = 0;
		ALARM_TIMER1 = 0;
	}
	else if(system_data.state & SNOOZE_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
			{
				if(ALARM_TIMER >= 24000)
				{
					if(alarm_cfg(TWO_LOW_MODE) == 0)
					{
						ALARM_TIMER = 0;
					}
				}
			}
			else
			{
				if(ALARM_TIMER >= 2000)
				{
					if(alarm_cfg(ONE_MED_MODE) == 0)
					{
						ALARM_TIMER = 0;
					}
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 24000)
			{
				if(alarm_cfg(TWO_LOW_MODE) == 0)
				{
					ALARM_TIMER = 0;
				}
			}
		}
		if(SNOOZE_FAULT_TIMER >= 36000000)
		{
			ALARM_TIMER = 0;
			SNOOZE_FAULT_TIMER = 0;
			system_data.signal &= ~DEVICE_SNOOZE_FAULT_FLAG_MSK;
		}
	}
	else if(system_data.state & SNOOZE_LOW_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
			{
				if(ALARM_TIMER >= 24000)
				{
					if(alarm_cfg(ONE_LOW_MODE) == 0)
					{
						ALARM_TIMER = 0;
					}
				}
			}
			else
			{
				if(ALARM_TIMER >= 2000)
				{
					if(alarm_cfg(ONE_MED_MODE) == 0)
					{
						ALARM_TIMER = 0;
					}
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 24000)
			{
				if(alarm_cfg(ONE_LOW_MODE) == 0)
				{
					ALARM_TIMER = 0;
				}
			}
		}
		if((SNOOZE_LOW_TIMER >= 36000000))
		{
			ALARM_TIMER = 0;
			SNOOZE_LOW_TIMER = 0;
			system_data.signal &= ~DEVICE_SNOOZE_LOW_FLAG_MSK;
		}
	}
	else if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
	{
		if(ALARM_TIMER >= 40000)
		{
			if(alarm_cfg(ONE_LOW_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
		if(SNOOZE_MEMORY_TIMER >= 36000000)
		{
			ALARM_TIMER = 0;
			SNOOZE_MEMORY_TIMER = 0;
			system_data.signal &= ~DEVICE_SNOOZE_MEMORY_FLAG_MSK;
		}
	}
	else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER >= 2000)
			{
				if(ALARM_TIMER1 >= 40000)
				{
					if(alarm_cfg(SENSOR_FAULT_MODE) == 0)
					{
						ALARM_TIMER = 0;
						ALARM_TIMER1 = 0;
					}
				}
				else
				{
					if(alarm_cfg(ONE_MED_MODE) == 0)
					{
						ALARM_TIMER = 0;
					}
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 40000)
			{
				if(alarm_cfg(SENSOR_FAULT_MODE) == 0)
				{
					ALARM_TIMER = 0;
				}
			}
		}
	}
	else if(system_data.state & LOW_BATTERY_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER >= 2000)
			{
				if(alarm_cfg(ONE_MED_MODE) == 0)
				{
					ALARM_TIMER = 0;
				}
			}
			if(ALARM_TIMER1 >= 40000)
			{
				if(alarm_cfg(ONE_SOUND_MODE) == 0)
				{
					ALARM_TIMER1 = 0;
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 40000)
			{
				if(alarm_cfg(LOW_BAT_MODE) == 0)
				{
					ALARM_TIMER = 0;
				}
			}
		}
	}
	else if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{
		if(ALARM_TIMER >= 2000)
		{
			if(alarm_cfg(ONE_MED_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
		if(ALARM_MEMORY_TIMER >= 259200000)
		{
			ALARM_MEMORY_TIMER = 0;
			ALARM_TIMER = 0;
			system_data.signal &= ~(DEVICE_ALARM_MEMORY_FLAG_MSK + SNOOZE_MEMORY_FLAG_MSK);
		}
	}
}





