#include "755LHA_Message_PT32L031.h"


/************************************************************************
** @brief  ¶Ì°´¼ì²â
** @param  Void
** @note   
** @retval None
************************************************************************/
void key3_short_check(void)
{
	if(system_data.state & ALARM_FLAG_MSK)
	{
	  system_data.signal |= DEVICE_HUSH_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if((system_data.state & SNOOZE_LOW_FLAG_MSK) && (system_data.state & ALARM_MEMORY_FLAG_MSK))
	{
		system_data.signal |= DEVICE_SNOOZE_MEMORY_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if((system_data.state & KEY_NO_RESPONSE1) == 0)
	{
		if(system_data.state & SENSOR_FAULT_FLAG_MSK)
		{
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
	}
}

/************************************************************************
** @brief  ³¤°´¼ì²â
** @param  Void
** @note   
** @retval None
************************************************************************/
void key3_08s_check(void)
{
	if(system_data.state & HUSH_FLAG_MSK)
	{
		system_data.signal |= DEVICE_TEST_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if(system_data.state & ALARM_FLAG_MSK)
	{
	  system_data.signal |= DEVICE_HUSH_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if((system_data.state & SNOOZE_LOW_FLAG_MSK) && (system_data.state & ALARM_MEMORY_FLAG_MSK))
	{
		system_data.signal |= DEVICE_TEST_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if((system_data.state & KEY_NO_RESPONSE2) == 0)
	{
		if(system_data.state & SENSOR_FAULT_FLAG_MSK)
		{
			system_data.signal |= DEVICE_SNOOZE_FAULT_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
		else if(system_data.state & (LOW_BATTERY_FLAG_MSK + SNOOZE_LOW_FLAG_MSK + SNOOZE_MEMORY_FLAG_MSK + ALARM_MEMORY_FLAG_MSK))
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
  * @brief  Message MSK
  * @param  None
  * @retval None
  *********************************************************************/
void	message_proc(void)
{
	system_data.masking &= ~MESSAGE_FLAG_MSK;

	if((system_data.state & HUSH_FLAG_MSK) == 0)
	{
		if(system_data.signal & DEVICE_HUSH_FLAG_MSK)
		{
			alarm_cfg(HUSH_MODE);
			set_wireless_connect(NET_CLOSE_ALARM);
			HUSH_TIMER = 0;
			system_data.state |= HUSH_FLAG_MSK;
			system_data.masking |= HUSH_HOLD_FLAG_MSK;
		}
	}
	else
	{
		if((system_data.signal & DEVICE_HUSH_FLAG_MSK) == 0)
		{
			remove_alarm();
			
			system_data.state &= ~(HUSH_FLAG_MSK + ALARM_FLAG_MSK + EXTERNAL_ALARM_FLAG_MSK);
			system_data.masking &= ~HUSH_HOLD_FLAG_MSK;
			
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
			{
				if((system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK) == 0)
				{
					key2.h_time = 0;
				  key2.l_time = 0;
					system_data.masking |= EXT_CHECK_FLAG_MSK;
				}
			}
		}
	}
	
	if((system_data.state & NETWORK_ALARM_FLAG_MSK) == 0) 
  {
		if(system_data.signal & DEVICE_NETWORK_ALARM_FLAG_MSK)
		{
			alarm_cfg(NET_ALARM_MODE);
		
			if(NETWORK_KEY != 0)
			{
				set_wire_connect(I_IO_OUT);
			}
			else
			{
				set_wire_connect(I_OUT);
			}
			system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
			system_data.state &= ~TEST_FLAG_MSK;
			system_data.state |= NETWORK_ALARM_FLAG_MSK;
		}
  }
  else
  {
    if((system_data.signal & DEVICE_NETWORK_ALARM_FLAG_MSK) == 0)
    {
      remove_alarm();
			system_data.state &= ~(NETWORK_ALARM_FLAG_MSK + EXTERNAL_ALARM_FLAG_MSK);
			
			if((system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK) == 0)
			{
				key2.h_time = 0;
				key2.l_time = 0;
				system_data.masking |= EXT_CHECK_FLAG_MSK;
			}
    }
  }	
	
	if((system_data.state & NETWORK_TEST_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_NETWORK_TEST_FLAG_MSK)
    {
			alarm_cfg(NET_ALARM_MODE);
			
			if(NETWORK_KEY != 0)
			{
				set_wire_connect(I_IO_OUT);
			}
			else
			{
				set_wire_connect(I_OUT);
			}
			system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
			system_data.state &= ~TEST_FLAG_MSK;
			system_data.state |= NETWORK_TEST_FLAG_MSK;
			system_data.masking &= ~RECENT_ALARM_FLAG_MSK;
    }
  }
  else
  {
    if((system_data.signal & DEVICE_NETWORK_TEST_FLAG_MSK) == 0)
    {
      remove_alarm();
      system_data.state &= ~(NETWORK_TEST_FLAG_MSK + EXTERNAL_ALARM_FLAG_MSK);
			
			if((system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK) == 0)
			{
				key2.h_time = 0;
				key2.l_time = 0;
				system_data.masking |= EXT_CHECK_FLAG_MSK;
			}
    }
  }

	if((system_data.state & EXTERNAL_ALARM_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_EXTERNAL_ALARM_FLAG_MSK)
    {
		 	if((system_data.state & (NETWORK_TEST_FLAG_MSK + NETWORK_ALARM_FLAG_MSK + HUSH_FLAG_MSK)) == 0)
      {
        alarm_cfg(NET_ALARM_MODE);
				
        if(NETWORK_KEY != 0)
        {
          set_wire_connect(IO_OUT);
          set_wireless_connect(NET_FIRE_ALARM);
        }
				system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
			  system_data.state &= ~TEST_FLAG_MSK;
        system_data.masking &= ~RECENT_ALARM_FLAG_MSK;
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
			
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
			{
				if(NETWORK_KEY != 0)
				{
					set_wireless_connect(NET_CLOSE_ALARM);
				}
			}
    }
  }
	
	if((system_data.state & ALARM_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_ALARM_FLAG_MSK)
    {
			if((system_data.state & (EXTERNAL_ALARM_FLAG_MSK + NETWORK_ALARM_FLAG_MSK + NETWORK_TEST_FLAG_MSK + HUSH_FLAG_MSK)) == 0)
			{
				alarm_cfg(FIRE_MODE);
				set_wire_connect(I_IO_OUT);
			  set_wireless_connect(NET_FIRE_ALARM);
				
				system_data.signal &= ~(DEVICE_TEST_FLAG_MSK + DEVICE_ALARM_MEMORY_FLAG_MSK);
				system_data.state &= ~(TEST_FLAG_MSK + ALARM_MEMORY_FLAG_MSK);
				system_data.masking |= RECENT_ALARM_FLAG_MSK;
				system_data.state |= ALARM_FLAG_MSK;
			}
		}
  }
	else
	{
		if((system_data.signal & DEVICE_ALARM_FLAG_MSK) == 0)
		{
			remove_alarm();
			set_wireless_connect(NET_CLOSE_ALARM);
			
			system_data.signal &= ~DEVICE_HUSH_FLAG_MSK;
			system_data.state &= ~(ALARM_FLAG_MSK + HUSH_FLAG_MSK + ALARM_MEMORY_FLAG_MSK);
			system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
			system_data.masking &= ~HUSH_HOLD_FLAG_MSK;

			key2.h_time = 0;
			key2.l_time = 0;
			system_data.masking |= EXT_CHECK_FLAG_MSK;
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
      fe_phy_quit();
      remove_alarm();
      if(system_data.state & HUSH_FLAG_MSK)
      {
        alarm_cfg(HUSH_MODE);
      }
      system_data.state &= ~TEST_FLAG_MSK;
    }
  }

  if((system_data.state & EXTERNAL_ERROR_FLAG_MSK) == 0) 
  {
    if(system_data.signal & DEVICE_EXTERNAL_ERROR_FLAG_MSK)
    {
      alarm_cfg(EXT_ERROR);
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
  
  if((system_data.state & FIND_ALARM_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_FIND_ALARM_FLAG_MSK)
    {
      alarm_cfg(FIRE_MODE);
      NET_ALARM_TIMER = 0;
      system_data.state |= FIND_ALARM_FLAG_MSK;
    }
  }
  else
  {
    if((system_data.signal & DEVICE_FIND_ALARM_FLAG_MSK) == 0)
    {
      remove_alarm();
      system_data.state &= ~FIND_ALARM_FLAG_MSK;
    }
  }
	
  //´«¸ÐÆ÷¹ÊÕÏ
  if((system_data.state & SENSOR_FAULT_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK)
    {
      ALARM_TIMER = 40000;
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
  
  //´«¸ÐÆ÷¹ÊÕÏÃâ´òÈÅ
  if((system_data.state & SNOOZE_FAULT_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_SNOOZE_FAULT_FLAG_MSK)
    {
      if((system_data.state & (~SENSOR_FAULT_FLAG_MSK)) != 0)
      {
        ALARM_TIMER = 0;
        FU_DND_TIMER = 0;
        system_data.state |= SNOOZE_FAULT_FLAG_MSK;
      }
      else
      {
        alarm_cfg(BUZZER_ONCE);
        ALARM_TIMER = 0;
        FU_DND_TIMER = 0;
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
  
  //µÍµçÑ¹
  if((system_data.state & LOW_BATTERY_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_LOW_BATTERY_FLAG_MSK)
    {
      ALARM_TIMER = 40000;
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
  
  //µÍµçÑ¹Ãâ´òÈÅ
  if((system_data.state & SNOOZE_LOW_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_SNOOZE_LOW_FLAG_MSK)
    {
      ALARM_TIMER = 0;
      LB_DND_TIMER = 0;
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
  
  //±¨¾¯¼ÇÒä
  if((system_data.state & ALARM_MEMORY_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_ALARM_MEMORY_FLAG_MSK)
    {
      ALARM_TIMER = 0;
      ALARM_M_TIMER = 0;
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
  
  //±¨¾¯¼ÇÒäÃâ´òÈÅ
  if((system_data.state & SNOOZE_MEMORY_FLAG_MSK) == 0)
  {
    if(system_data.signal & DEVICE_SNOOZE_MEMORY_FLAG_MSK)
    {
      ALARM_TIMER = 0;
      MEM_DND_TIMER = 0;
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

  
  if(system_data.masking & KEY3_08S_FLAG_MSK)
  {
    key3_08s_check();
    system_data.masking &= ~KEY3_08S_FLAG_MSK;
  }
  
  if(system_data.masking & KEY3_10S_FLAG_MSK)
  {
    if(system_data.state & TEST_FLAG_MSK)
    {
      set_wire_connect(I_IO_OUT);
      set_wireless_connect(NET_TEST_ALARM);
    }
    system_data.masking &= ~KEY3_10S_FLAG_MSK;
  }
  
  if(system_data.masking & KEY3_UP_FLAG_MSK)
  {
    if(system_data.masking & KEY3_DOWN_FLAG_MSK)
    {
			if((system_data.state & 
				(ALARM_FLAG_MSK + EXTERNAL_ALARM_FLAG_MSK + NETWORK_ALARM_FLAG_MSK + NETWORK_TEST_FLAG_MSK + EXTERNAL_ERROR_FLAG_MSK + FIND_ALARM_FLAG_MSK)) == 0)
			{
				check_fre.count++;
				if(check_fre.count == 1)
				{
					GENERAL_TIMER = 0;
					check_fre.mode = _exe;
				}
			}

      key3_short_check();
      system_data.masking &= ~KEY3_DOWN_FLAG_MSK;
    }
    else
    {
      if(system_data.state & TEST_FLAG_MSK)
      {
        system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
        system_data.masking |= MESSAGE_FLAG_MSK;
      }
      check_fre.count = 0;
    }
    ALARM_TIMER = 0;
    system_data.masking &= ~KEY3_UP_FLAG_MSK;
  }
}


/**********************************************************************
  * @brief  Message execution
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
			alarm_cfg(REDLED_ONCE_LOW);
		}
	}
	else if(system_data.state & SNOOZE_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
			{
				if(ALARM_TIMER >= 40000)
				{
					ALARM_TIMER = 0;
					alarm_cfg(REDLED_ONCE_LOW);
				}
			}
			else
			{
				if(ALARM_TIMER >= 2000)
				{
					ALARM_TIMER = 0;
					alarm_cfg(REDLED_ONCE_MED);
				}
			}
		}
		
		if(ALARM_TIMER1 >= 24000)
		{
			ALARM_TIMER1 = 0;
		  alarm_cfg(YELLOWLED_TWICE_LOW);
		}
		
		if(FU_DND_TIMER >= 36000000)
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
				if(ALARM_TIMER1 >= 40000)
				{
					ALARM_TIMER1 = 0;
					alarm_cfg(REDLED_ONCE_LOW);
				}
			}
			else 
			{
				if(ALARM_TIMER1 >= 2000)
				{
					ALARM_TIMER1 = 0;
					alarm_cfg(REDLED_ONCE_MED);
				}
			}
		}
		if(ALARM_TIMER >= 24000) 
		{
			ALARM_TIMER = 0;
			alarm_cfg(YELLOWLED_ONCE_LOW);
		}
		if((LB_DND_TIMER >= 36000000))
		{
			system_data.signal &= ~DEVICE_SNOOZE_LOW_FLAG_MSK;
      system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
	else if(system_data.state & SNOOZE_MEMORY_FLAG_MSK)
	{
		if(system_data.state & SENSOR_FAULT_FLAG_MSK)
		{
			if(ALARM_TIMER1 >= 40000)
			{
				ALARM_TIMER1 = 0;
				alarm_cfg(YELLOWLED_TWICE_LOW);
			}
		}
		else if(system_data.state & LOW_BATTERY_FLAG_MSK)
		{
			if(ALARM_TIMER1 >= 40000)
			{
				ALARM_TIMER1 = 0;
				alarm_cfg(YELLOWLED_ONCE_LOW);
			}
		}
		if(ALARM_TIMER >= 40000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(REDLED_ONCE_LOW);
		}
		if(MEM_DND_TIMER >= 36000000)
		{
			system_data.signal &= ~DEVICE_SNOOZE_MEMORY_FLAG_MSK;
      system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
	else if(system_data.state & SENSOR_FAULT_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER1 >= 2000)
			{
				ALARM_TIMER1 = 0;
				alarm_cfg(REDLED_ONCE_MED);
			}
		}
		if(ALARM_TIMER >= 40000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(SENSOR_FAULT_MODE);
		}
	}
	else if(system_data.state & LOW_BATTERY_FLAG_MSK)
	{
		if(system_data.state & ALARM_MEMORY_FLAG_MSK)
		{
			if(ALARM_TIMER1 >= 2000)
			{
				ALARM_TIMER1 = 0;
				alarm_cfg(REDLED_ONCE_MED);
			}
		}
		if(ALARM_TIMER >= 40000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(LOW_BAT_MODE);
		}
	}
	else if(system_data.state & ALARM_MEMORY_FLAG_MSK)
	{ 
		if(ALARM_TIMER >= 2000)
		{
			ALARM_TIMER = 0;
			alarm_cfg(REDLED_ONCE_MED);
		}
		if(ALARM_M_TIMER >= 259200000)
		{
			system_data.signal &= ~DEVICE_ALARM_MEMORY_FLAG_MSK;
      system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
}
 



