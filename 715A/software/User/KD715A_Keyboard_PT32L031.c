#include "KD715A_Keyboard_PT32L031.h"


KEY_TYPEDEF key;

/************************************************************************
** @brief  按键外部中断
** @param  Void
** @note
** @retval None
************************************************************************/
void PA_Handler(void)
{
	//PA6 -> KY2 -> MUTE
	if(CMSDK_PA->INTSTATUS & MUTE_PIN)
	{
		CMSDK_PA->INTCLEAR |= MUTE_PIN;
		if(key.flag == 0)
		{
			MUTE_TIMER += 50;
		  key.flag = MUTE_PIN;
		}
	}
	//PA7 -> KY3 -> TEST
	else if(CMSDK_PA->INTSTATUS & TEST_PIN)
	{
		CMSDK_PA->INTCLEAR |= TEST_PIN;
		if(key.flag == 0)
		{
			TEST_TIMER += 50;
		  key.flag = TEST_PIN;
		}
	}
	else
	{
		CMSDK_PA->INTCLEAR |= 0xFFFF;
	}
}

/************************************************************************
** @brief  ScanTestKeyProcess 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void scan_key_process(unsigned char *v)
{
  key.value = v;
	
	if((*(key.value) & 0x01) != 0)
	{
		if(!TEST_KEY) //按下
		{
			if((*(key.value) & 0x08) != 0)
			{
				*(key.value) = 0x40;
			}
			else
			{
				*(key.value) |= 0x08;
			}
		}
		else
		{
			*(key.value) &= ~0x08;
		}
	}
	else
	{
		if(TEST_KEY) //非按下
		{
			if((*(key.value) & 0x08) != 0)
			{
				*(key.value) = 0x81;
			}
			else
			{
				*(key.value) |= 0x08;
			}
		}
		else
		{
			*(key.value) &= ~0x08;
		}
  }
}

/************************************************************************
** @brief  TestKeyDownEvent 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void key_downevent(unsigned char *v)
{
	key.value = v;
	
	KEY_LONG_TIMER = 0;
	
	*(key.value) = 0x20;
	
	if(key.flag == TEST_PIN)
	{
		keylong_event();
	}
}

/************************************************************************
** @brief  TestKeyUpEvent 	
** @param  void
** @note 	 
** @retval no
************************************************************************/
void key_upevent(unsigned char *v)
{
	key.value = v;
	
	system_data.masking |= MESSAGE_FLAG_MSK;

	if(key.flag == TEST_PIN)
	{
		if(system_data.signal & DEVICE_TEST_FLAG_MSK)
		{
			system_data.signal &= ~DEVICE_TEST_FLAG_MSK;
		}
	}
  else if(key.flag == MUTE_PIN)
	{
		if(KEY_LONG_TIMER < 300)
		{
			KEY_LONG_TIMER = 0;
			keyshort_event();
		}
	}
	
	*(key.value) = 0x01;
	key.flag = 0;
}

/************************************************************************
** @brief  短按事件 -> 静音
** @param  Void
** @note   
** @retval None
************************************************************************/
void keyshort_event(void)
{
	if(key.flag == MUTE_PIN)
	{
		if(system_data.state & ALARM_FLAG_MSK)
		{
			system_data.signal |= DEVICE_HUSH_FLAG_MSK;
		}
	}
}

/************************************************************************
** @brief  长按事件 -> 测试
** @param  Void
** @note   
** @retval None
************************************************************************/
void keylong_event(void)
{
	system_data.masking |= MESSAGE_FLAG_MSK;
	
	if((system_data.state & (SENSOR_FAULT_FLAG_MSK + ALARM_FLAG_MSK)) == 0)
	{
		system_data.signal |= DEVICE_TEST_FLAG_MSK;//本地测试
	}
}






