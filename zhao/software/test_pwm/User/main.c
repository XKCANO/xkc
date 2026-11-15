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
	
	key2.value = 
	key3.value = 
	key4.value = 1;
	
	system_data.masking |= SYSTEM_INITIALIZE_FLAG_MSK;
  
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
				GENERAL_TIMER++;
				RED_LED_ON;
			}
			if(GENERAL_TIMER > 1000)
			{
				RED_LED_OFF;
				system_data.masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
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
    
		if(system_data.masking & MESSAGE_FLAG_MSK)
	  {
			message_proc();
	  }

    feed_iwdg();
		feed_swdg();
		checktimer5();
	}
}

/* --------------------------------------------------------------------------- */





