#include "755PSMA5_Windows_PT32L076.h"

Alarm_typedef led;
Alarm_typedef buzzer;
Alarm_typedef alarm;
Alarm_typedef update;

/*
 * smoke 回调函数
 */
void smoke_callback(uint32_t state)
{
	system_data.masking |= MESSAGE_FLAG_MSK;
	
	if(state & 0xC0)
	{
		system_data.signal |= DEVICE_SENSOR_FAULT_FLAG_MSK;
	}
	else
	{
		system_data.signal &= ~DEVICE_SENSOR_FAULT_FLAG_MSK;
	}
	
	if(state & 0x08)
	{
		system_data.signal |= DEVICE_ALARM_FLAG_MSK;
	}
	else
	{
		system_data.signal &= ~DEVICE_ALARM_FLAG_MSK;
	}
}

/*
 * battery 回调函数
 */
void battery_callback(uint32_t state)
{
	system_data.masking |= MESSAGE_FLAG_MSK;
	
	if(state & 0x10)
	{
		system_data.signal |= DEVICE_LOW_BATTERY_FLAG_MSK;
	}
	else
	{
		system_data.signal &= ~DEVICE_LOW_BATTERY_FLAG_MSK;
	}
}

/*
 * uart 回调函数
 */
void uart_callback(uint32_t p, uint32_t l)
{
	if( p == OPEN_BUZZER)
	{
		set_alarm(1);
		buzzer.step = 4;
		buzzer.mode = _exe;
	}
}

/*
 * 短按检测
 */
void check_short_test(void)
{
	if(system_data.state & SHORT_TEST_FLAG_MSK)
	{
	  system_data.signal &= ~DEVICE_SHORT_TEST_FLAG_MSK;
	  system_data.masking |= MESSAGE_FLAG_MSK;
	}
}

/*
 * 设置更新模式
 */
void set_update_timer1(unsigned char state)
{
	update.step = 0;
	
	timer5.mr0 = MIN_TIMER_US;
	
	if(system_data.masking & LOW_SOUND_FLAG_MSK)
	{
		TIM1->ARR = timer5.mr0 * 2;
		TIM1->OCR[3] = timer5.mr0;
	}
	else
	{
		TIM1->ARR = timer5.mr0;
		TIM1->OCR[3] = timer5.mr0 / 2;
	}

	if(state == 0)
	{
		update.mode = _idle;
	}
	else if(state == 1)
	{
		update.mode = _exe;
	}
}

/*
 * 报警声光指示配置函数
 */
unsigned char alarm_cfg(uint8_t mode)
{
	alarm.mode = 0x01;
	
	switch(mode)
	{
		//测试报警，声光T3时刻，有渐响
		case TEST_MODE:
			if((system_data.resource & (BUZZER_FLAG_MSK + LED_FLAG_MSK)) == 0)
			{
				led.step = 0;
			  led.mode = _exe;
		    set_alarm(0);
		    buzzer.step = 0;
		    buzzer.mode = _exe;
				alarm.mode = 0;
				system_data.masking |= LOW_SOUND_FLAG_MSK;
			}
			break;
		
    //火灾报警，声光T3时刻，无渐响
		case FIRE_MODE:
			if((system_data.resource & (BUZZER_FLAG_MSK + LED_FLAG_MSK)) == 0)
			{
				set_alarm(1);
				led.step = 0;
				led.mode = _exe;
				buzzer.step = 4;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//互联报警，蜂鸣器 T3时序
		case EXTERNAL_MODE:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				set_alarm(1);
				buzzer.step = 4;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//互联错误 红灯中亮度 0.2s亮 0.8s灭
		case EXT_ERROR_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.step = 12;
				led.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//低亮度闪一次 -> 2ms (待机、低压免打扰)
		case ONE_LOW_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 2;
				LED_TIMER = 110;
				led.step = 9;
				led.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//低亮度闪两次(失效故障免打扰)
		case TWO_LOW_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 2;
				led.step = 7;
				led.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//中亮度闪一次 -> 10ms (报警记忆、低压、静音)
		case ONE_MED_MODE:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				led.offset = 10;
				LED_TIMER = 110;
				led.step = 9;
				led.mode = _exe;
				alarm.mode = 0;
			}
			break;
		
		//哔叫一声 （低压、进入失效故障免打扰）
		case ONE_SOUND_MODE:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				set_alarm(1);
				BUZZER_TIMER = 110;
				buzzer.step = 13;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
			
		//中等亮度闪一下，叫一声
		case LOW_BAT_MODE:
			if((system_data.resource & (LED_FLAG_MSK + BUZZER_FLAG_MSK)) == 0)
			{
				set_alarm(1);
				LED_TIMER = 110;
				BUZZER_TIMER = 110;
				led.offset = 10;
				led.step = 9;
				led.mode = _exe;
				buzzer.step = 13;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
			
    //中亮度闪两次、哔叫两声（传感器失效故障）
		case SENSOR_FAULT_MODE:
			if((system_data.resource & (LED_FLAG_MSK + BUZZER_FLAG_MSK)) == 0)
			{
				set_alarm(1);
				led.offset = 10;
				led.step = 7;
				led.mode = _exe;
				buzzer.step = 11;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
			
		case FIND_ALARM_MODE:
			if((system_data.resource & (LED_FLAG_MSK + BUZZER_FLAG_MSK)) == 0)
			{
				led.step = 0;
				led.mode = _exe;
				set_alarm(1);
				buzzer.step = 4;
				buzzer.mode = _exe;
				alarm.mode = 0;
			}
			break;
	}
	
	if(alarm.mode != 0)
	{
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	
	return alarm.mode;
}

void de_led(void)
{
	RED_LED_OFF;
	HRED_LED_OFF;
	
	led.offset = 0;
	led.counter = 0;
	led.counter1 = 0;
	led.step = 0;
	led.mode = _idle;
}

void de_buzzer(void)
{
	system_data.masking &= ~LOW_SOUND_FLAG_MSK;
	
	de_alarm();
	
	buzzer.offset = 0;
	buzzer.counter = 0;
	buzzer.counter1 = 0;
	buzzer.step = 0;
  buzzer.mode = _idle;
	
	set_update_timer1(0);
}

/**
* @brief 设置互联状态
* @param flag
* 0: close
* 1: wire
* 2: base
* 3: wire and base
* @retval None
*/
void set_connect(unsigned char flag)
{
	switch(flag)
	{
		case 0:
		  IOUT_OFF;
	    IO_PIN_L;
		  IO_PIN_IN;
		  system_data.masking &= ~IO_OUTPUT_FLAG_MSK;
			break;
		
		case 1:
			IOUT_ON;
		
			break;
		
		case 2:
			IO_PIN_OUT;
	    IO_PIN_H;
		  system_data.masking |= IO_OUTPUT_FLAG_MSK;
			break;
		
		case 3:
			IO_PIN_OUT;
		  IOUT_ON;
	    IO_PIN_H;
		  system_data.masking |= IO_OUTPUT_FLAG_MSK;
			break;
		
		default:
		  IOUT_OFF;
      IO_PIN_L;
		  IO_PIN_IN;
		  system_data.masking &= ~IO_OUTPUT_FLAG_MSK;
	}
}


void alarm_del(void)
{
	de_led();
	
	de_buzzer();

	set_connect(0);
	
	system_data.resource &= ~(BUZZER_FLAG_MSK + LED_FLAG_MSK);
}


void led_lighten(void)
{
	switch(led.step)
	{
		//测试报警、火灾报警
		case 0:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				HRED_LED_ON;
				LED_TIMER = 0;
				system_data.resource |= LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 1:
			if(LED_TIMER > 499)
			{
				if(led.counter > 1)
				{
					check_short_test();
				}
				HRED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 2:
			if(LED_TIMER > 999)
			{
				led.counter++;
				if(led.counter > 2)
				{
					led.counter = 0;
					led.step++;
				}
				else
          led.step -= 2;
			}
			break;
		case 3:
			if(LED_TIMER > 1999)
			{
				led.step -= 3;
			}
			break;
		
		
		//闪2次
		case 7:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				RED_LED_ON;
				LED_TIMER = 0;
				system_data.resource |= LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 8:
			if(LED_TIMER > (led.offset - 1))
			{
				RED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step++;
			}
			break;
			
	 //闪1次
	 case 9:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				if(LED_TIMER > 109)
				{
					RED_LED_ON;
					LED_TIMER = 110;
					system_data.resource |= LED_FLAG_MSK;
					led.step++;
				}
			}
			break;
		case 10:
			if(LED_TIMER > (109 + led.offset))
			{
				RED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step = 0;
				led.mode = _idle;
			}
			break;
			
    //互联错误
		case 12:
			if((system_data.resource & LED_FLAG_MSK) == 0)
			{
				HRED_LED_ON;
				LED_TIMER = 0;
				system_data.resource |= LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 13:
			if(LED_TIMER > 19)
			{
				HRED_LED_OFF;
				system_data.resource &= ~LED_FLAG_MSK;
				led.step++;
			}
			break;
		case 14:
			if(LED_TIMER > 329)
			{
				led.step -= 2;
			}
			break;
	}
}


void buzzer_sound(void)
{
	switch(buzzer.step)
	{
		//T3时刻，低声音
		case 0:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{ 
				set_update_timer1(1);
				open_buzzer(0);
				BUZZER_TIMER = 0;
				system_data.resource |= BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
		case 1:
			if(BUZZER_TIMER > 499)
			{
				set_update_timer1(0);
				close_buzzer();
				system_data.resource &= ~BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
		case 2:  
			if(BUZZER_TIMER > 999)
			{
				buzzer.counter++;
        if(buzzer.counter > 2)
				{
					buzzer.counter = 0;
				  buzzer.step++;
				}
				else
          buzzer.step -= 2;
			}
			break;
		case 3:
			if(BUZZER_TIMER > 1999)
			{
				buzzer.counter1++;
				if(buzzer.counter1 < 2)
				{
					buzzer.step -= 3;
				}
				else
				{
					system_data.masking &= ~LOW_SOUND_FLAG_MSK;
					de_alarm();
					__NOP();
					__NOP();
					set_alarm(1);
					buzzer.counter = 0;
					buzzer.counter1 = 0;
					buzzer.step++;
				}
			}
			break;
			
			
	  //T3时序，大声音
		case 4:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				set_update_timer1(1);
				open_buzzer(1);
				BUZZER_TIMER = 0;
				system_data.resource |= BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
		case 5:
			if(BUZZER_TIMER > 499)
			{
				set_update_timer1(0);
				close_buzzer();
				system_data.resource &= ~BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
		case 6:  
			if(BUZZER_TIMER > 999)
			{
				buzzer.counter++;
        if(buzzer.counter > 2)
				{
					buzzer.counter = 0;
				  buzzer.step++;
				}
				else
				{
					 buzzer.step -= 2;
				}
			}
			break;
		case 7:
			if(BUZZER_TIMER > 1999)
			{
				buzzer.step -= 3;
			}
			break;

			
		//哔叫两声 每次10ms
		case 11:
			if((system_data.resource & BUZZER_FLAG_MSK) == 0)
			{
				open_buzzer(1);
				BUZZER_TIMER = 0;
				system_data.resource |= BUZZER_FLAG_MSK;
				buzzer.step++;
			}
			break;
    case 12:
			if(BUZZER_TIMER > 9)
			{
				close_buzzer();
				system_data.resource &= ~BUZZER_FLAG_MSK;
				buzzer.step++;
			}
      break;
			
		//哔叫两声 每次10ms 间隔100ms
		case 13:
			if(BUZZER_TIMER > 109)
			{
				if((system_data.resource & BUZZER_FLAG_MSK) == 0)
				{
					open_buzzer(1);
					BUZZER_TIMER = 110;
					system_data.resource |= BUZZER_FLAG_MSK;
					buzzer.step++;
				}
			}
      break;
    case 14:
			if(BUZZER_TIMER > 119)
			{
				de_alarm();
				system_data.resource &= ~BUZZER_FLAG_MSK;
        buzzer.step = 0;
				buzzer.mode = _idle;
			}
      break;
	}
}

/*
*  设置TIM1的PWM扫频
*/
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



