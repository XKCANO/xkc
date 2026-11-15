/***********************************************************************
**
** 								Include
**
***********************************************************************/
#include "755PSMA5_DEF.h"
#include "755PSMA5_System_PT32L076.h"
#include "755PSMA5_Timer_PT32L076.h"
#include "755PSMA5_Windows_PT32L076.h"
#include "755PSMA5_Keyboard_PT32L076.h"
#include "755PSMA5_Message_PT32L076.h"

#include "FE_755PSMA5_SMOKE_PT32L076.h"
#include "FE_SMOKE_TIMER_PT32L076.h"
#include "FE_SMOKE_EEPROM_PT32L076.h"
#include "FE_755PSMA5_UART_PT32L076.h"
#include "FE_755PSMA5_BATTERY_PT32L076.h"

SYSTEM_DATA_typedef system_data;


/***********************************************************************
**
**															Main
**
***********************************************************************/

int main(void)
{
	clear_sram();
	
	sys_clock_init();
	
	sys_gpio_init();

	open_iwdg();
	
	open_swdg();
	
  fe_smoke_read_eeprom_data();
	
	settimer5();
	
	fe_set_system_tick_timer();
	
	key2.value = _exe;
	key3.value = _exe;
	key4.value = _exe;
	key5.value = _exe;
	timer5.mr0 = MIN_TIMER_US;
	
	system_data.masking |= SYSTEM_INITIALIZE_FLAG_MSK;
	
	while(1)
	{
		
/************************************************************************
  * @brief System  Initalize Function
	* 
*************************************************************************/		
		if(system_data.masking & SYSTEM_INITIALIZE_FLAG_MSK)
		{
			if(SYSINIT_TIMER > 990)
			{
				if((system_data.resource & LED_FLAG_MSK) == 0)
				{
					RED_LED_ON;
					system_data.resource |= LED_FLAG_MSK;
					fe_set_smoke_callback(smoke_callback);
				  fe_set_battery_callback(battery_callback);
				  fe_set_uart_callback(uart_callback);
				}
				
				if(SYSINIT_TIMER > 999)
				{
					RED_LED_OFF;
					system_data.resource &= ~LED_FLAG_MSK;

					if(TEST_KEY == 0)
					{
						if(EXT_KEY == 0)
						{
							close_iwdg();
						  close_swdg();
							RED_LED_ON;
							system_data.masking |= DEBUG_FLAG_MSK;
							fe_start_up_smoke_process(2);
						  fe_start_up_battery_process(1);
						}
					}
					else
					{
						IO_PIN_IN;
						fe_start_up_smoke_process(1);
					  fe_start_up_battery_process(0);
					}
					
					system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
				}
			}
		}
		
/************************************************************************
  * @brief Key Function
	* 
*************************************************************************/			
		if(KEY3_TIMER > 49)
		{
			KEY3_TIMER = 0;
			
			scankey3_process_run();
			
			if(key3.value & 0x08)
			{
				key3_shortevent();
			}
			
			if(key3.value & 0x10)
			{
				key3_longevent();
			}
			
			if(key3.value & 0x80)
			{
				key3_upevent();
			}
		}
		
		if(AC_TIMER > 4)
		{
			AC_TIMER = 0;
			scankey2_process_run();
			scankey4_process_run();
			scankey5_process_run();
		}
		
		if(SMOKE_TIMER >= 8000)
		{
			SMOKE_TIMER = 0;
			fe_start_up_smoke_process(0);
		}
		
		if(BATTERY_TIMER >= 48000)
		{
			BATTERY_TIMER = 0;
			fe_start_up_battery_process(0);
		}
		
/************************************************************************
  * @brief Alarm Function
	* 
*************************************************************************/			
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
*************************************************************************/	
	  if(system_data.masking & MESSAGE_FLAG_MSK)
	  {
			messageproc();
	  }
		
/************************************************************************
 * @brief Message Exe Function
 *
*************************************************************************/
		message_execution();
    
/************************************************************************
  * @brief  lib Function
	* 
*************************************************************************/		
	  fe_smoke_process_run();
		fe_battery_process_run();
		fe_uart_process_run();
		fe_eeprom_process_run();
		
/************************************************************************
  * @brief DeepSleep Function
	* 
*************************************************************************/		
    if((system_data.masking & DEVICE_PENDING_MODE) == 0)
		{
			if(fe_get_uart_state() == 0)
			{
				if(fe_get_battery_state() == 0)
				{
					if(fe_get_smoke_state() == 0)
					{
						if(DEEPSLEEP == _idle)
						{
							goto_deepsleep();
						}
					}
				}
			}
	  }

/************************************************************************
  * @brief  Check Timer3 Function
	* 定时器检查时钟 1ms 1拍 
*************************************************************************/	
    feed_iwdg();
		feed_swdg();
		checktimer5();
		fe_check_system_tick_timer();
		
	}
}

/* --------------------------------------------------------------------------- */





