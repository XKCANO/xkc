#include "755PSMA5_Message_PT32L076.h"


/**********************************************************************
  * @brief  短按处理
  * @param  None
  * @retval None
  *********************************************************************/
void key3_short_check(void)
{
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
      if(system_data.state & LOW_BATTERY_FLAG_MSK)
      {
        if(system_data.state & ALARM_MEMORY_FLAG_MSK)
        {
          system_data.signal |= DEVICE_SNOOZE_LOW_FLAG_MSK + DEVICE_SNOOZE_MEMORY_FLAG_MSK;
        }
      }
      
      system_data.signal |= DEVICE_SNOOZE_FAULT_FLAG_MSK;
      system_data.masking |= MESSAGE_FLAG_MSK;
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

/**********************************************************************
  * @brief  长按处理
  * @param  None
  * @retval None
  *********************************************************************/
void key3_08s_check(void)
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

/**********************************************************************
  * @brief  消息处理
  * @param  None
  * @retval None
  *********************************************************************/
void message_proc(void)
{
	system_data.masking &= ~MESSAGE_FLAG_MSK;

	if((system_data.state & ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_ALARM_FLAG_MSK)
		{
			alarm_cfg(FIRE_MODE);
			set_connect(3);
			system_data.state |= ALARM_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.state & HUSH_FLAG_MSK) == 0)
		{
			if(system_data.signal & DEVICE_HUSH_FLAG_MSK)
			{
				alarm_cfg(HUSH_MODE);
				set_connect(0);
				ALARM_TIMER = 0;
				system_data.state |= HUSH_FLAG_MSK;
			}
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
			{
				remove_alarm();
				system_data.state &= ~ALARM_FLAG_MSK;
				system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
			}
		}
		else
		{
			if((system_data.signal & DEVICE_HUSH_FLAG_MSK) == 0)
			{
				system_data.state &= ~(HUSH_FLAG_MSK + ALARM_FLAG_MSK);
				system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
	
	if((system_data.state & TEST_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_TEST_FLAG_MSK)
		{
			alarm_cfg(TEST_MODE);
			system_data.state |= TEST_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_TEST_FLAG_MSK) == 0)
		{
			remove_alarm();
			if(system_data.state & HUSH_FLAG_MSK)
			{
				alarm_cfg(HUSH_MODE);
			}
			system_data.state &= ~TEST_FLAG_MSK;
		}
	}
	
	if((system_data.state & SHORT_TEST_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SHORT_TEST_FLAG_MSK)
		{
			alarm_cfg(TEST_MODE);
			system_data.state |= SHORT_TEST_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_SHORT_TEST_FLAG_MSK) == 0)
		{
			remove_alarm();
			system_data.state &= ~SHORT_TEST_FLAG_MSK;
		}
	}

	if((system_data.state & EXTERNAL_ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK)
		{
			if((system_data.state & (EXTERNAL_ERROR_FLAG_MSK + HUSH_FLAG_MSK)) == 0)
			{
				alarm_cfg(EXTERNAL_MODE);
				if(LOCAL_KEY)
				{
					set_connect(2);
				}
				system_data.signal &= ~(DEVICE_SHORT_TEST_FLAG_MSK + DEVICE_TEST_FLAG_MSK);
				system_data.state &= ~(SHORT_TEST_FLAG_MSK + TEST_FLAG_MSK);
				system_data.state |= EXTERNAL_ALARM_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK) == 0)
		{
			remove_alarm();
			system_data.state &= ~EXTERNAL_ALARM_FLAG_MSK;
			system_data.masking |= RIN_CHECK_FLAG_MSK;
		}
	}
	
	if((system_data.state & RELAYIN_ALARM_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_RELAYIN_ALARM_FLAG_MSK)
		{
			if((system_data.state & (EXTERNAL_ERROR_FLAG_MSK + HUSH_FLAG_MSK)) == 0)
			{
				alarm_cfg(EXTERNAL_MODE);
				set_connect(1);
				system_data.signal &= ~(DEVICE_SHORT_TEST_FLAG_MSK + DEVICE_TEST_FLAG_MSK);
				system_data.state &= ~(SHORT_TEST_FLAG_MSK + TEST_FLAG_MSK);
				system_data.state |= RELAYIN_ALARM_FLAG_MSK;
			}
		}
	}
	else
	{
		if((system_data.signal & DEVICE_RELAYIN_ALARM_FLAG_MSK) == 0)
		{
			remove_alarm();
			system_data.state &= ~RELAYIN_ALARM_FLAG_MSK;
			system_data.masking |= EXT_CHECK_FLAG_MSK;
		}
	}
	
	if((system_data.state & EXTERNAL_ERROR_FLAG_MSK) == 0) 
	{
		if(system_data.signal & DEVICE_EXTERNAL_ERROR_FLAG_MSK)
		{
			alarm_cfg(EXT_ERROR_MODE);
			system_data.state |= EXTERNAL_ERROR_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_EXTERNAL_ERROR_FLAG_MSK) == 0)
		{
			remove_alarm();
			system_data.state &= ~EXTERNAL_ERROR_FLAG_MSK;
		}
	}
	
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
				alarm_cfg(LOW_BAT_MODE);
				ALARM_TIMER = 0;
				SNOOZE_FAULT_TIMER = 0;
				system_data.state |= SNOOZE_FAULT_FLAG_MSK;
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
	
	if((system_data.state & SENSOR_FAULT_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK)
		{
			ALARM_TIMER1 = 40000;
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
			ALARM_TIMER1 = 40000;
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
	
	if(system_data.masking & KEY3_08S_FLAG_MSK)
	{
		key3_08s_check();
		system_data.masking &= ~KEY3_08S_FLAG_MSK;
	}
	
	if(system_data.masking & KEY3_10S_FLAG_MSK)
	{
		if(system_data.state & TEST_FLAG_MSK)
		{
			set_connect(3);
		}
		system_data.masking &= ~KEY3_10S_FLAG_MSK;
	}
	
	if(system_data.masking & KEY3_UP_FLAG_MSK)
	{
		if(system_data.masking & KEY3_DOWN_FLAG_MSK)
		{
			system_data.masking &= ~KEY3_DOWN_FLAG_MSK;
			key3_short_check();
		}
		else
		{
			if(system_data.state & TEST_FLAG_MSK)
			{
				system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
		system_data.masking &= ~KEY3_UP_FLAG_MSK;
	}
}

/**********************************************************************
  * @brief  唤醒检测
  * @param  None
  * @retval None
  *********************************************************************/
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
	else if(system_data.state & SNOOZE_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
			{
				if(ALARM_TIMER >= 24000)
				{
					ALARM_TIMER = 0;
					alarm_cfg(TWO_LOW_MODE);
				}
			}
			else
			{
				if(ALARM_TIMER >= 2000)
				{
					ALARM_TIMER = 0;
					alarm_cfg(ONE_MED_MODE);
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 24000)
			{
				ALARM_TIMER = 0;
				alarm_cfg(TWO_LOW_MODE);
			}
		}
		if(SNOOZE_FAULT_TIMER >= 36000000)
		{
			system_data.signal &= ~DEVICE_SNOOZE_FAULT_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
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
					ALARM_TIMER = 0;
					alarm_cfg(ONE_LOW_MODE);
				}
			}
			else
			{
				if(ALARM_TIMER >= 2000)
				{
					ALARM_TIMER = 0;
					alarm_cfg(ONE_MED_MODE);
				}
			}
		}
		else
		{
			if(ALARM_TIMER >= 24000)
			{
				ALARM_TIMER = 0;
				alarm_cfg(ONE_LOW_MODE);
			}
		}
		if((SNOOZE_LOW_TIMER >= 36000000))
		{
			system_data.signal &= ~DEVICE_SNOOZE_LOW_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
	else if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
	{
		if(ALARM_TIMER >= 40000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(ONE_LOW_MODE);
		}
		if(SNOOZE_MEMORY_TIMER >= 36000000)
		{
			system_data.signal &= ~DEVICE_SNOOZE_MEMORY_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
	else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER >= 2000)
			{
				ALARM_TIMER = 0;
				alarm_cfg(ONE_MED_MODE);
			}
		}
		if(ALARM_TIMER1 >= 40000)
		{
			ALARM_TIMER1 = 0;
			alarm_cfg(SENSOR_FAULT_MODE);
		}
	}
	else if(system_data.state & LOW_BATTERY_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER >= 2000)
			{
				ALARM_TIMER = 0;
				alarm_cfg(ONE_MED_MODE);
			}
		}
		if(ALARM_TIMER1 >= 40000)
		{
			ALARM_TIMER1 = 0;
			alarm_cfg(LOW_BAT_MODE);
		}
	}
	else if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{
		if(ALARM_TIMER >= 2000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(ONE_MED_MODE);
		}
		if(ALARM_MEMORY_TIMER >= 259200000)
		{
			system_data.signal &= ~DEVICE_ALARM_MEMORY_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
}


/* --------------------------------------------------------------------------- */



