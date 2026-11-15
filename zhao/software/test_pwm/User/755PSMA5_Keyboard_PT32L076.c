#include "755PSMA5_Keyboard_PT32L076.h"

MULTIPLE_KEY_Tytedef key2;

SIMPLE_KEY_Tytedef key3;
SIMPLE_KEY_Tytedef key4;
SIMPLE_KEY_Tytedef key5;

/************************************************************************
** @brief  按键外部中断 
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
  
  if(system_data.masking & TIMER1_OPEN_FLAG_MSK)
  {
    system_data.masking |= TIMER1_UPDATE_FLAG_MSK;
    
    if(timer5.mr0 >= 4)
    {
      timer5.mr0 = timer5.mr0 /2;
    } 
  }
  else
  {
    open_buzzer();
    system_data.masking |= TIMER1_OPEN_FLAG_MSK;
  }
}

void key3_08s_event(void)
{
	key3.value &= ~0x20;
 
  close_buzzer();
  
  system_data.masking &= ~TIMER1_OPEN_FLAG_MSK;
}

void key3_10s_event(void)
{
	key3.value &= ~0x40;
}

void key3_up_event(void)
{
	key3.value &= ~0x80;
}



