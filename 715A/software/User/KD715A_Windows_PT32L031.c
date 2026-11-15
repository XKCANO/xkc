#include "KD715A_Windows_PT32L031.h"
#include "FE_semaphore.h"


Alarm_typedef led;
Alarm_typedef buzzer;
typedef_common update;


void UartCallBack(uint32_t p, uint32_t l)
{
	if( p == OPEN_BUZZER)
	{
		set_alarm(1);
		buzzer.step = 5;
		buzzer.mode = _exe;
	}
}

void set_update_timer1(unsigned char state)
{
	update.step = 0;
	update.value = MIN_TIMER_US;
	
	if(system_data.masking & LOW_SOUND_FLAG_MSK)
	{
		PWM1->MR0 = update.value * 2;
	  PWM1->MR4 = update.value;
	}
	else
	{
		PWM1->MR0 = update.value;
	  PWM1->MR4 = update.value/2;
	}
	
	if(state == 1)
	{
		update.mode = _exe;
	}
	else if(state == 0)
	{
	  update.mode = _idle;
	}
}


/**
* @brief 关闭灯指示
* @retval None
**/
void led_close(void)
{
	led.step = 0;
	led.counter = 0;
	led.counter1 = 0;
	led.mode = _idle;
	
	RED_LED_OFF;
}

/**
* @brief 关闭声音指示
* @retval None
**/
void buzzer_close(void)
{
	system_data.masking &= ~LOW_SOUND_FLAG_MSK;
	
	fe_clear_semaphore(11);
	
	del_alarm();
	
	buzzer.step = 0;
	buzzer.counter = 0;
	buzzer.counter1 = 0;
	buzzer.mode = _idle;
	
	set_update_timer1(0);
}



/**
* @brief 关闭声光指示
* @retval None
**/
void remove_alarm(void)
{
  led_close();
	
	buzzer_close();
	
	system_data.resource &= ~(LED_FLAG_MSK + BUZZER_FLAG_MSK);
}

/**
* @brief 设置声光指示
* @retval None
**/
unsigned char alarm_init(unsigned char mode)
{
  unsigned char state = 1;
	
	switch(mode)
	{
		case ONE_LOW_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 2;
				LED_TIMER = 100;
				led.step = 7;
				led.mode = _exe;
				state = 0;
			}
			break;
			
		case ONE_MED_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 10;
				LED_TIMER = 100;
				led.step = 7;
				led.mode = _exe;
				state = 0;
			}
			break;
			
		case TWO_MED_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 10;
				led.step = 5;
				led.mode = _exe;
				state = 0;
			}
			break;
			
		case FIRE_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.counter = 0;
				led.step = 0;
				led.mode = _exe;
				state = 0;
			}
			break;
	}
	
	if(state == 1)
	{
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	
	return state;
}

/************************************************************************
  * @brief  LED  
	*  
*************************************************************************/
void led_lighten(void)
{
	switch(led.step)
	{
		//本地温感报警/测试报警    红灯1s闪烁一次（声光同步）
		case 0:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
		    RED_LED_ON;
				system_data.resource |= LED_FLAG_MSK;
			  LED_TIMER = 0;
				led.counter++;
				led.step++;
			}
			break;
		case 1:
			if(LED_TIMER > 499)
			{
				RED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 2:
			if(LED_TIMER > 999)
			{
				if(led.counter > 2)
				{
					led.counter = 0;
				  led.step++;
				}
				else
				{
					led.step -= 2;
				}
			}
			break;
		case 3:
			if(LED_TIMER > 1999)
			{
				led.step -= 3;
			}
			break;

			
		case 5:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				RED_LED_ON;
				system_data.resource |= LED_FLAG_MSK;
			  LED_TIMER = 0;
			  led.step++;
			}
			break;
		case 6:
			if(LED_TIMER > (led.offset - 1))
			{
				RED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step = 0;
				led.mode = _idle;
			}
			break;
	}
}




void buzzer_sound(void)
{
	switch(buzzer.step)
	{
		//测试报警 前6声低后面高
		case 0:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				if(fe_get_semaphore_state() == 0)
			  {
					fe_set_semaphore(11);
					open_buzzer();
					set_update_timer1(1);
					system_data.resource |= BUZZER_FLAG_MSK;
					BUZZER_TIMER = 0;
					buzzer.counter++;
					buzzer.step++;
				}
			}
			break;
		case 1:
			if(BUZZER_TIMER > 499)
			{
				close_buzzer();
				fe_clear_semaphore(11);
				set_update_timer1(0);
				system_data.resource &= ~BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
		case 2:
			if(BUZZER_TIMER > 999)
			{
        if(buzzer.counter > 2)
				{
					buzzer.counter = 0;
				  buzzer.step++;
				}
				else
				{
					buzzer.step = 0;
				}
			}
			break;
		case 3:
			if(BUZZER_TIMER > 1999)
			{
        buzzer.counter1++;
				if(system_data.state & TEST_FLAG_MSK)
				{
					if(buzzer.counter1 == 2)
					{
						del_alarm();
						__NOP();
						__NOP();
						set_alarm(1);
						BST_ON;
						buzzer.counter1 = 0;
						buzzer.counter = 0;
						system_data.masking &= ~LOW_SOUND_FLAG_MSK;
					}
				}
				
				buzzer.step = 0;
			}
			break;
			
			
		//响两下
		case 5:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				if(fe_get_semaphore_state() == 0)
			  {
					fe_set_semaphore(11);
					BST_ON;
					open_buzzer();
					system_data.resource |= BUZZER_FLAG_MSK;
					BUZZER_TIMER = 0;
					buzzer.step++;
				}
			}
			break;
		case 6: 
			if(BUZZER_TIMER > 9)
			{
			  close_buzzer();
				fe_clear_semaphore(11);
				system_data.resource &= ~BUZZER_FLAG_MSK;
        buzzer.step++;
			}
			break;
		case 7:
			if(BUZZER_TIMER > 109)
			{
				if((system_data.resource & BUZZER_FLAG_MSK) == 0)
				{
					if(fe_get_semaphore_state() == 0)
					{
						fe_set_semaphore(11);
						BST_ON;
						open_buzzer();
						BUZZER_TIMER = 110;
						system_data.resource |= BUZZER_FLAG_MSK;
						buzzer.step++;
					}
				}
			}
			break;
		case 8:
			if(BUZZER_TIMER > 119)
			{
				BST_OFF;
				del_alarm();
				fe_clear_semaphore(11);
				system_data.resource &= ~BUZZER_FLAG_MSK;
				buzzer.step = 0;
				buzzer.mode = _idle;
			}
			break;
	}
}


void update_timer1(void)
{
	switch(update.step)
	{
		case 0:
			TIMER1_TIMER = 0;
		  update.step++;
			break;
		case 1:
			if(TIMER1_TIMER > 99)
			{
				TIMER1_TIMER = 0;
				system_data.masking |= TIMER1_UPDATE_FLAG_MSK;
				update.step--;
			}
			break;
	}
}




