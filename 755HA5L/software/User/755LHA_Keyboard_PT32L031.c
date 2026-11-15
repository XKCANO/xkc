#include "755LHA_Keyboard_PT32L031.h"

KEY_Event_Typedef check_fre;
MULTIPLE_KEY_Tytedef key2;
SIMPLE_KEY_Tytedef key3;

/************************************************************************
** @brief  按键外部中断
** @param  Void
** @note
** @retval None
************************************************************************/
void PA_Handler(void)
{
	uint32_t i;
	i = CMSDK_PA->INTSTATUS;
	CMSDK_PA->INTCLEAR |= i;
	
	if(i & TEST_PIN)
	{
		//KY3 -> PA2
	  KEY3_TIMER += 50;
	}
}

void PB_Handler(void)
{
	uint32_t i;
	i = CMSDK_PB->INTSTATUS;
	CMSDK_PB->INTCLEAR |= i;
	
	if(i & EXT_PIN)
	{
		//KY2 -> PB1
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
** @brief  按键次数检测
** @param  Void
** @note   
** @retval None
************************************************************************/
void keyfrequency_check(void)
{
	switch(check_fre.step)
	{
		case 0:
			if(GENERAL_TIMER < 2000)
			{
				if(check_fre.count > 2)
				{
					check_fre.step++;
				}
			}
			else
			{
				GENERAL_TIMER = 0;
				check_fre.count = 0;
			  check_fre.step = 0;
			  check_fre.mode = _idle;
			}
			break;
		case 1:
			if((system_data.masking & RF_PAIRINGF_FLAG_MSK) == 0)
			{
				fe_phy_quit();
				pair.step = 0;
				pair.mode = _exe;
				system_data.masking |= RF_PAIRINGF_FLAG_MSK;
			}
			else
			{
				pair.step = 20;
				pair.mode = _exe;
			}
			GENERAL_TIMER = 0;
			check_fre.count = 0;
			check_fre.step = 0;
			check_fre.mode = _idle;
			break;
	}
}

/************************************************************************
** @brief  扫描互联输入状态
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
				system_data.masking &= ~EXT_CHECK_FLAG_MSK;
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
