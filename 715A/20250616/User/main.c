/***********************************************************************
**
** 								Include
**
***********************************************************************/
#include "FE_MATH.h"
#include "FE_TIMER_PT32L031.h"
#include "FE_755LHA_Uart_PT32L031.h"

#include <stdio.h>
#include "pt32x031.h"
#include "KD715A_DEF.h"
#include "KD715A_System_PT32L031.h"
#include "KD715A_heat_PT32L031.h"
#include "KD715A_Message_PT32L031.h"
#include "KD715A_Batterylow_PT32L031.h"


SYSTEM_DATA_typedef system_data;
FE_755LHA_EEPROM_TypeDef eeprom_data;

/***********************************************************************
**
**															Main
**
***********************************************************************/


int main(void)
{
	fe_clear_ram();

	sys_clock_init();
	
	sys_gpio_init();
	
	open_iwdg();
	
	open_swdg();
		
	fe_read_eeprom_data();
	
	system_data.masking |= (SYSTEM_INITIALIZE_FLAG_MSK + HEAT_INITIALIZE_FLAG_MSK + BAT_INITIALIZE_FLAG_MSK + MESSAGE_FLAG_MSK);
	
	key.test_value = 0x01;
	key.mute_value = 0x01;
	
	fe_set_system_tick_timer();
	
	set_timer3();
	
	while(1)
	{	
/************************************************************************
 * @brief System Inition Function
 * 
************************************************************************/	
		if(start.mode & _exe)
		{
			system_start_proc_run();
		}
		
/************************************************************************
 * @brief normal mode
 * 
************************************************************************/		
	  if((system_data.masking & (SYSTEM_INITIALIZE_FLAG_MSK + DEBUG_FLAG_MSK)) == 0)
		{
			if(TEST_TIMER > 49)
			{
				TEST_TIMER = 0;
				
				scan_key_process(&key.test_value);
				
				if((key.test_value & 0x40) != 0)
				{
					key_downevent(&key.test_value);
				}
				if((key.test_value & 0x80) != 0)
				{
					key_upevent(&key.test_value);
				}
			}
			
			if(MUTE_TIMER > 49)
			{
				MUTE_TIMER = 0;
				
				scan_key_process(&key.mute_value);
				
				if((key.mute_value & 0x40) != 0)
				{
					key_downevent(&key.mute_value);
				}
				
				if((key.mute_value & 0x80) != 0)
				{
					key_upevent(&key.mute_value);
				}
			}

			if(HEAT_TIMER >= 8000)
			{
				HEAT_TIMER = 0;
				feed_iwdg();
   			Heat.mode = _exe;
			}

			if(Heat.mode & _exe)
			{
				fe_heat_process_run();
			}

			if(BATTERY_TIMER >= 48000)
			{
				BATTERY_TIMER = 0;
				bat.mode = _exe;
			}
			
			if(bat.mode & _exe)
			{
				measure_battery();
			}
		}
		
/************************************************************************
 * @brief Message Check Function
 *
************************************************************************/
		if(led.mode & _exe)
		{
			led_lighten();
		}
			
		if(buzzer.mode & _exe)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		{
			buzzer_sound();
		}
		
		if(update.mode & _exe)
		{
			update_timer1();
		}
/************************************************************************
 * @brief Message Check Function
 *
************************************************************************/		
    if(system_data.masking & MESSAGE_FLAG_MSK)
	  {
			messageproc();
	  }
		
/************************************************************************
 * @brief Message Exe Function
 *
************************************************************************/
		if((system_data.masking & DEBUG_FLAG_MSK) == 0)
		{
			message_execution();
		}
		
/************************************************************************
 * @brief DeepSleep Exe Function
 *
************************************************************************/
		if(key.mute_value == key.test_value == 0x1)
		{
			if(fe_get_eeprom_state() == 0)
			{
				if(fe_get_uart_state() == 0)
				{
					if(DEEPSLEEP == _idle)
					{
						goto_deepsleep();
					}
				}
			}
		}
			
/************************************************************************
 * @brief   系统lib执行函数
 *  
************************************************************************/
		fe_uart_process_run();
		fe_eeprom_process_run();
		
    feed_swdg();
		
		fe_check_system_tick_timer();
		check_timer3();
	}
}


/* --------------------------------------------------------------------*/


