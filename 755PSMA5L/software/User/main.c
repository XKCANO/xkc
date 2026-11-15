/***********************************************************************
**
** 								Include
**
***********************************************************************/
#include "755PSMA5L_DEF.h"
#include "755PSMA5L_System_PT32L076.h"
#include "755PSMA5L_Timer_PT32L076.h"
#include "755PSMA5L_Windows_PT32L076.h"
#include "755PSMA5L_Keyboard_PT32L076.h"
#include "755PSMA5L_Message_PT32L076.h"

#include "FE_SMOKE_EEPROM_PT32L076.h"
#include "FE_755PSMA5L_UART_PT32L076.h"


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

	key2.value = 
	key3.value = 
	key4.value = 1;
	
	system_data.masking |= SYSTEM_INITIALIZE_FLAG_MSK;

  fe_set_system_tick_timer();
  settimer5();

	while(1)
	{
/************************************************************************
  * @brief System  Initalize
	* 
*************************************************************************/				
    if(system_data.masking & SYSTEM_INITIALIZE_FLAG_MSK)
    {
      if(GENERAL_TIMER == 990)
      {
        RED_LED_ON;
        fe_set_smoke_callback(smoke_callback);
				fe_set_battery_callback(battery_callback);
				fe_set_uart_callback(uart_callback);
      }
      
      if(GENERAL_TIMER == 1000)
      {
        RED_LED_OFF;
        if((TEST_KEY == 0) && (EXT_KEY == 0))
				{
          fe_start_up_smoke_process(2);
          fe_start_up_battery_process(1);
          system_data.masking |= DEBUG_FLAG_MSK;
          system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
				}
				else
				{
					IO_PIN_IN;
          fe_start_up_smoke_process(1);
          fe_start_up_battery_process(0);
          system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
				}
      }
    }

/************************************************************************
  * @brief standby
	* 
*************************************************************************/
    if(KEY_TIMER >= KEYBOARD_SCANNING_TIME_1)
    {
      KEY_TIMER = 0;
			
      if((system_data.masking & KEY2_OUT_FLAG_MSK) == 0)
			{
        scankey2_process_run();
			}
			
      scankey4_process_run();
    }
    
    if(KEY3_TIMER >= KEYBOARD_SCANNING_TIME_2)
		{
			KEY3_TIMER = 0;
			
			scankey3_process_run();
			
			if((system_data.masking & KEY5_OUT_FLAG_MSK) == 0)
			{
			  scankey5_process_run();
			}
			
			if(key3.value & 0x10)
			{
				key3_down_event();
		  }
			
			if(key3.value & 0x20)
			{
        key3_08s_event();
			}
			
			if(key3.value & 0x40)
			{
				key3_10s_event();
			}
			
			if(key3.value & 0x80)
			{
				key3_up_event();
			}
		}

		if(led.mode & _exe)
		{
			led_lighten();
		}
		
		if(buzzer.mode & _exe)
		{
		  buzzer_sound();
      
			if(update.mode & _exe)
			{
				update_timer1();
			}
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
		
		if(system_data.masking & OPEN_BOOST_FLAG_MSK)
		{
			if((fe_get_semaphore_state() & 0x1FF) == 0)
			{
				BOOST_ON;
				fe_set_semaphore(8);
				system_data.masking &= ~OPEN_BOOST_FLAG_MSK;
			}
		}
		
		if(system_data.masking & CLOSE_BOOST_FLAG_MSK)
		{
			if(fe_get_smoke_state() == 0)
			{
				BOOST_OFF;
				fe_clear_semaphore(8);
				system_data.masking &= ~CLOSE_BOOST_FLAG_MSK;
			}
		}
		
		if(system_data.state & HUSH_FLAG_MSK)
    {
      if(ALARM_TIMER >= 600000)       
      {
        system_data.signal &= ~DEVICE_HUSH_FLAG_MSK;
        system_data.masking |= MESSAGE_FLAG_MSK;
      }
    }
		
		if(system_data.masking & MESSAGE_FLAG_MSK)
	  {
			message_proc();
	  }
		
/************************************************************************
  * @brief  lib
	* 
*************************************************************************/
		fe_smoke_process_run();
		fe_battery_process_run();
		fe_uart_process_run();
		fe_eeprom_process_run();
		
/************************************************************************
  * @brief deepsleep
	* 
*************************************************************************/
	  if((system_data.masking & 
			 (SYSTEM_INITIALIZE_FLAG_MSK + AC_CHECK_FLAG_MSK + RIN_CHECK_FLAG_MSK + EXT_CHECK_FLAG_MSK +
		    DEBUG_FLAG_MSK + OPEN_BOOST_FLAG_MSK + CLOSE_BOOST_FLAG_MSK + MESSAGE_FLAG_MSK)) == 0)
		{
			if(fe_get_uart_state() == 0)
			{
				if(fe_get_battery_state() == 0)
				{
					if(fe_get_smoke_state() == 0)
					{
						if(led.mode == _idle && buzzer.mode == _idle &&
							 key2.value == 0x1 && key3.value == 0x1 && key5.value == 0)
						{
							goto_deepsleep();
						}
					}
				}
			}
    }
/************************************************************************
  * @brief timer
	* 1ms
*************************************************************************/	
		feed_iwdg();
		feed_swdg();
		checktimer5();
    fe_check_system_tick_timer();
	}                                                              
}


/* --------------------------------------------------------------------------- */





