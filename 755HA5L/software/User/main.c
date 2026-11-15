/***********************************************************************
**
** 								Include
**
***********************************************************************/
#include <stdio.h>
#include "pt32x031.h"
#include "755LHA_DEF.h"
#include "FE_MATH.h"
#include "FE_TIMER_PT32L031.h"
#include "FE_755LHA_Uart_PT32L031.h"

#include "755LHA_RF_PT32L031.h"
#include "755LHA_System_PT32L031.h"
#include "755LHA_heat_PT32L031.h"
#include "755LHA_Message_PT32L031.h"
#include "755LHA_Batterylow_PT32L031.h"

SYSTEM_DATA_typedef system_data;

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
  
	fe_set_system_tick_timer();
	
	set_timer3();
  
	key2.value = 
	key3.value = 1;
  
  system_data.masking |= (SYSTEM_INITIALIZE_FLAG_MSK + HEAT_INITIALIZE_FLAG_MSK + BAT_INITIALIZE_FLAG_MSK);
	
	while(1)
	{
/************************************************************************
 * @brief System Inition Function
 * 
************************************************************************/	
		if(system_data.masking & SYSTEM_INITIALIZE_FLAG_MSK)
		{
			system_start_proc_run();
		}

    if(KEY_TIMER >= KEYBOARD_SCANNING_TIME_1) 
    {
      KEY_TIMER = 0;
			
      if((system_data.masking & KEY2_OUT_FLAG_MSK) == 0)
			{
        scankey2_process_run();
      }
    }
		
    if(KEY3_TIMER >= KEYBOARD_SCANNING_TIME_2)
    {
      KEY3_TIMER = 0;
      
      scankey3_process_run();

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

    if(check_fre.mode & _exe)
    {
      keyfrequency_check();
    }
    
    if(HEAT_TIMER >= 8000)
    {
      HEAT_TIMER = 0;
      feed_iwdg();
      heat.mode = _exe;
    }
		
    if(heat.mode & _exe)
    {
      heat_process_run();
    }

    if(pair.mode & _exe)
    {
      rf_pairing_process_run();
    }

		if(system_data.masking & DEBUG_FLAG_MSK)
		{
			if(system_data.masking & BATTERY_SAMPLING_FLAG_MSK)
			{
				if(BATTERY_TIMER >= 1000)
				{
					BATTERY_TIMER = 0;
					bat.mode = _exe;
				}
			}
		}
		else
		{
			if(BATTERY_TIMER >= 48000)
			{
				BATTERY_TIMER = 0;
				bat.mode = _exe;
			}
		}
    
    if(bat.mode & _exe)
    {
      measure_battery();
    }

		if(red_led.mode & _exe)
		{
			red_led_lighten();
		}
		
		if(yel_led.mode & _exe)
		{
			yellow_led_lighten();
		}
			
		if(buzzer.mode & _exe)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		{
			buzzer_sound();
      
      if(update.mode & _exe)
      {
        update_timer1();
      }
		}
		
		if(release.mode & _exe)
		{
			release_network();
		}

    if(system_data.state & FIND_ALARM_FLAG_MSK)
    {
      if(NET_ALARM_TIMER > 7999)
      {
        system_data.signal &= ~DEVICE_FIND_ALARM_FLAG_MSK;
        system_data.masking |= MESSAGE_FLAG_MSK;
      }
    }
    
		if(system_data.state & (NETWORK_ALARM_FLAG_MSK + NETWORK_TEST_FLAG_MSK))
		{
			if(NET_ALARM_TIMER > 24999)
			{
				system_data.signal &= ~(DEVICE_NETWORK_ALARM_FLAG_MSK + DEVICE_NETWORK_TEST_FLAG_MSK);
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
    
    if(system_data.state & HUSH_FLAG_MSK)
    {
      if(HUSH_TIMER >= 600000)
      {
        system_data.signal &= ~DEVICE_HUSH_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
      }
    }
		
		if(system_data.masking & OPEN_BOOST_FLAG_MSK)
		{
			if(system_data.masking & BOOST_HOLD_UP_FLAG_MSK)
			{
				system_data.masking &= ~OPEN_BOOST_FLAG_MSK;
			}
			else
			{
				if((fe_get_semaphore_state() & 0x1FF) == 0)
				{
					BOOST_ON;
					fe_set_semaphore(8);
					system_data.masking &= ~OPEN_BOOST_FLAG_MSK;
					system_data.masking |= BOOST_HOLD_UP_FLAG_MSK;
				}
			}
		}
		
		if(system_data.masking & CLOSE_BOOST_FLAG_MSK)
		{
			if((fe_get_semaphore_state() & 0x100) == 0)
			{
				system_data.masking &= ~(CLOSE_BOOST_FLAG_MSK + BOOST_HOLD_UP_FLAG_MSK);
			}
			else
			{
				BOOST_OFF;
			  fe_clear_semaphore(8);
			  system_data.masking &= ~(CLOSE_BOOST_FLAG_MSK + BOOST_HOLD_UP_FLAG_MSK);
			}
		}
		
		if(system_data.masking & RF_SEND_FLAG_MSK)
		{
			if(fe_755lha_mac_send_data(SEND_CMD) == 0)
			{
				system_data.masking &= ~RF_SEND_FLAG_MSK;
			}
		}
		
		if(system_data.masking & RF_CHECK_FLAG_MSK)
    {
      if(system_data.masking & ON_NET_FLAG_MSK)
      {
        if(fe_755lha_mac_receive_data() == 0)
        {
          system_data.masking &= ~RF_CHECK_FLAG_MSK;
        }
      }
      else
      {
        system_data.masking &= ~RF_CHECK_FLAG_MSK;
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
		fe_755lha_mac_process_run();
		fe_phy_process_run();
		fe_spi_process_run();
		fe_uart_process_run();
		fe_eeprom_process_run();
   
/************************************************************************
 * @brief DeepSleep Function
 *
************************************************************************/
	  if((system_data.masking & 
			(SYSTEM_INITIALIZE_FLAG_MSK + EXT_CHECK_FLAG_MSK + RF_SEND_FLAG_MSK + DEBUG_FLAG_MSK + \
       RF_CHECK_FLAG_MSK + OPEN_BOOST_FLAG_MSK + CLOSE_BOOST_FLAG_MSK + TIMER1_CLOSE_FLAG_MSK + HUSH_HOLD_FLAG_MSK + MESSAGE_FLAG_MSK)) == 0)
		{
			if(fe_get_eeprom_state() == 0)
			{
				if(fe_get_uart_state() == 0)
				{
					if(fe_get_755lha_mac_state() == 0)
					{
						if(fe_get_phy_state() != 0xFFFFFFFF)
						{
							if(fe_get_spi_state() == 0)
							{
								if(heat.mode == _idle && check_fre.mode == _idle && bat.mode == _idle && 
									 buzzer.mode == _idle && yel_led.mode == _idle && red_led.mode == _idle &&
								   pair.mode == _idle && key3.value == 0x1 && key2.value == 0x1)
								{
									goto_deepsleep();
								}
							}
						}
					}
				}
			}
	  }
/************************************************************************
 * @brief   系统lib执行函数
 *  
************************************************************************/
    feed_swdg();
		fe_check_system_tick_timer();
		check_timer3();
	}
}


/* --------------------------------------------------------------------*/


