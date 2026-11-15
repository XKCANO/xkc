#include "KD715A_Message_PT32L031.h"


/**********************************************************************
  * @brief  Message MSK
  * @param  None
  * @retval None
  *********************************************************************/
void messageproc(void)
{
	system_data.masking &= ~MESSAGE_FLAG_MSK;

	if(system_data.masking & SYSTEM_INITIALIZE_FLAG_MSK)
	{
		if(start.mode == _idle)
		{
			start.mode = _exe;
		}
	}
	else
	{
		if((system_data.state & HUSH_FLAG_MSK) == 0)
		{
			if(system_data.state & ALARM_FLAG_MSK)
			{
				if(system_data.signal & DEVICE_HUSH_FLAG_MSK)
			  {
					ALARM_TIMER += 60000;
					remove_alarm();
					system_data.state |= HUSH_FLAG_MSK;
				}
				else
				{
					if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
					{
						remove_alarm();
						system_data.state &= ~ALARM_FLAG_MSK;
					}
					else
					{
						if(alarm_init(FIRE_MODE) == 0)
						{
							system_data.state |= ALARM_FLAG_MSK;
						}
					}
				}
			}
			else
			{
				if(system_data.signal & DEVICE_ALARM_FLAG_MSK)
				{
					if(alarm_init(FIRE_MODE) == 0)
					{
						system_data.state |= ALARM_FLAG_MSK;
					}
				}
			}
		}
		else
		{
			if((system_data.signal & DEVICE_HUSH_FLAG_MSK) == 0)
			{
				system_data.state &= ~HUSH_FLAG_MSK;
				
				if(system_data.signal & DEVICE_ALARM_FLAG_MSK)
				{
					if(alarm_init(FIRE_MODE) == 0)
					{
						system_data.state |= ALARM_FLAG_MSK;
					}
				}
			}
		}
		
		
		if((system_data.state & TEST_FLAG_MSK) == 0)
		{
			if(system_data.signal & DEVICE_TEST_FLAG_MSK)
			{
				if(alarm_init(FIRE_MODE) == 0)
				{
					system_data.state |= TEST_FLAG_MSK;
				}
			}
		}
		else
		{
			if((system_data.signal & DEVICE_TEST_FLAG_MSK) == 0)
			{
				remove_alarm();
				system_data.state &= ~TEST_FLAG_MSK;
			}
		}
		
		if((system_data.state & SENSOR_FAULT_FLAG_MSK) == 0)
		{
			if(system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK)
			{
				ALARM_TIMER += 60000;
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
		
		if((system_data.state & LOW_BATTERY_FLAG_MSK) == 0)
		{
			if(system_data.signal & DEVICE_LOW_BATTERY_FLAG_MSK)
			{
				ALARM_TIMER += 60000;
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
		
  }	
}

void message_execution(void)
{
	if(system_data.state == 0)
	{
		if(ALARM_TIMER >= 60000)
		{
			if(alarm_init(ONE_LOW_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
	}
	else if(system_data.state & HUSH_FLAG_MSK)
	{
		if(ALARM_TIMER >= 60000)
		{
			if(alarm_init(ONE_LOW_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
		if(HUSH_TIMER > 600000)
		{
			HUSH_TIMER = 0;
			system_data.signal &= ~DEVICE_HUSH_FLAG_MSK;
		}
	}
	else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
	{
		if(ALARM_TIMER >= 60000)
		{
			if(alarm_init(TWO_MED_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
	}
	else if(system_data.state & LOW_BATTERY_FLAG_MSK)
	{
		if(ALARM_TIMER >= 60000)
		{
			if(alarm_init(ONE_MED_MODE) == 0)
			{
				ALARM_TIMER = 0;
			}
		}
	}
	
}

