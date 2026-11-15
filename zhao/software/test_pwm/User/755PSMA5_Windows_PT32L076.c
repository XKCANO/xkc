#include "755PSMA5_Windows_PT32L076.h"
#include "FE_semaphore.h"

#define   OPEN_BUZZER   0x43
#define   ENTER_SLEEP   0x44


Alarm_typedef led;
Alarm_typedef buzzer;
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

#define  LOW_BATTERY_755PSMA5_FLAG_POS  4
#define  LOW_BATTERY_755PSMA5_FLAG_MSK  (1UL << LOW_BATTERY_755PSMA5_FLAG_POS)

#define  END_BATTERY_755PSMA5_FLAG_POS  5
#define  END_BATTERY_755PSMA5_FLAG_MSK  (1UL << END_BATTERY_755PSMA5_FLAG_POS)
/*
 * battery 回调函数
 */
void battery_callback(uint32_t state)
{
	if(state & LOW_BATTERY_755PSMA5_FLAG_MSK)
	{
		system_data.signal |= DEVICE_LOW_BATTERY_FLAG_MSK;
	}
	else
	{
		system_data.signal &= ~DEVICE_LOW_BATTERY_FLAG_MSK;
	}
	system_data.masking |= MESSAGE_FLAG_MSK;
}

/*
 * uart 回调函数
 */
void uart_callback(uint32_t p, uint32_t l)
{
	if(p == OPEN_BUZZER)
	{
    if(buzzer.mode == _idle)
    {
      led.counter = 0;
      led.step = 0;
      led.mode = _exe;
			buzzer.counter = 0;
		  buzzer.step = 5;
		  buzzer.mode = _exe;
    }
	}
	
	if(p == ENTER_SLEEP)
  {
    close_wdog();
    
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	
	  __NOP();
	  __WFI();
	  __NOP();
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

/**
* @brief 设置声音大小
* @param flag
*  0: low
*  1: high
* @retval None
* PCLK:16MHz
*/
void open_buzzer(void)
{
	system_data.masking &= ~(TIMER1_CLOSE_FLAG_MSK + TIMER1_UPDATE_FLAG_MSK);
	
	//16M / (1599 + 1) = 10k
	TIM1->PSC = 1599;
	TIM1->CR1 = TIM_CR1_DIR;//TIM_CR1_CMS
	TIM1->CR2 |= TIM_CR2_ARI;//TIM_CR2_OC4I
		
  
  timer5.mr0 = MIN_TIMER_US;
  TIM1->ARR = timer5.mr0;
  TIM1->OCR[3] = timer5.mr0 >> 1;
  TIM1->OCMR = TIM_OCMR_OC4E + 0x00001000;

	TIM1->CR1 |= TIM_CR1_UG;
	
	//死区时间 45us * 16 = 320
	TIM1->BDTR = 0;
	
	TIM1->SR |= 0xFF;
	TIM1->CR1 |= TIM_CR1_EN;
	NVIC_EnableIRQ(TIM1_IRQn);
	
	//PA11 PA12
  AFIOA->AFS[1] = (0x05 << 12);
	
//  update.step = 0;
//	update.mode = _exe;
}

/**
* @brief 关闭声音
* @param None
* @retval None
*/
void close_buzzer(void)
{
	update.step = 0;
	update.mode = _idle;
	
	system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
}

/**
* @brief 移除报警指示
* @param None
* @retval None
*/
void remove_alarm(void)
{
	set_connect(CLOSE_ALL);
	
	close_timer1();
	
	HRED_LED_OFF;
	
	led.mode =
	buzzer.mode = 
	update.mode = _idle;
	
	system_data.masking &= ~LOW_SOUND_FLAG_MSK;
	system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
}

/*
 * 报警声光指示配置函数
 */
void alarm_cfg(uint8_t mode)
{
	switch(mode)
	{
		//测试报警，声光T3时刻，有渐响
		case TEST_MODE:
			led.counter = 0;
			led.step = 0;
			led.mode = _exe;
		  buzzer.offset = 0;
		  buzzer.counter = 0;
			buzzer.step = 0;
			buzzer.mode = _exe;
			system_data.masking |= LOW_SOUND_FLAG_MSK;
			break;
		
    //火灾报警，声光T3时刻，无渐响
		case FIRE_MODE:
			led.counter = 0;
			led.step = 0;
			led.mode = _exe;
		  buzzer.counter = 0;
			buzzer.step = 5;
			buzzer.mode = _exe;
      system_data.masking &= ~LOW_SOUND_FLAG_MSK;
			break;
		
		//互联报警，蜂鸣器 T3时序
		case EXTERNAL_MODE:
			HRED_LED_OFF;
      led.mode = _idle;
		  buzzer.counter = 0;
			buzzer.step = 5;
			buzzer.mode = _exe;
			break;
		
		//互联错误 红灯中亮度 0.2s亮 0.8s灭
		case EXT_ERROR_MODE:
			led.step = 14;
			led.mode = _exe;
		  buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
			break;
		
		//低亮度闪一次 -> 2ms
		case ONE_LOW_MODE:
			HRED_LED_OFF;
			led.offset = 2;
			LED_TIMER = 110;
			led.step = 11;
			led.mode = _exe;
		  buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
			break;
		
		//低亮度闪两次
		case TWO_LOW_MODE:
			HRED_LED_OFF;
			led.offset = 2;
			led.step = 8;
			led.mode = _exe;
		  buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
			break;
		
		//中亮度闪一次 -> 10ms
		case ONE_MED_MODE:
			HRED_LED_OFF;
			led.offset = 10;
			LED_TIMER = 110;
			led.step = 11;
			led.mode = _exe;
		  buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
			break;

		//中等亮度闪一下，叫一声
		case LOW_BAT_MODE:
			HRED_LED_OFF;
			LED_TIMER = 110;
			BUZZER_TIMER = 110;
			led.offset = 10;
			led.step = 11;
			led.mode = _exe;
			buzzer.step = 12;
			buzzer.mode = _exe;
			break;
			
    //中亮度闪两次、哔叫两声
		case SENSOR_FAULT_MODE:
			HRED_LED_OFF;
			led.offset = 10;
			led.step = 8;
			led.mode = _exe;
			buzzer.step = 9;
			buzzer.mode = _exe;
			break;
		
		case HUSH_MODE:
			HRED_LED_OFF;
			led.step = 4;
		  led.mode = _exe;
      buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
			break;
	}
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
		case CLOSE_ALL:
		  IOUT_OFF;
		  IO_PIN_L;
		  IO_PIN_IN;
      system_data.masking &= ~(KEY5_OUT_FLAG_MSK + KEY2_OUT_FLAG_MSK);
			break;
		
		case I_OUT:
			IO_PIN_L;
		  IO_PIN_IN;
		  IOUT_ON;
      system_data.masking &= ~KEY5_OUT_FLAG_MSK;
  		system_data.masking |= KEY2_OUT_FLAG_MSK;
			break;
		
		case IO_OUT:
			IOUT_OFF;
			IO_PIN_OUT; 
	    IO_PIN_H;
		  system_data.masking &= ~KEY2_OUT_FLAG_MSK;
      system_data.masking |= KEY5_OUT_FLAG_MSK;
			break;
		
		case I_IO_OUT:
			IO_PIN_OUT;
		  IOUT_ON;
	    IO_PIN_H;
      system_data.masking |= KEY5_OUT_FLAG_MSK + KEY2_OUT_FLAG_MSK;
			break;
	}
}

/**
* @brief 设置led的状态
* @param null
* @retval null
*/
void led_lighten(void)
{
	switch(led.step)
	{
		case 0:
			HRED_LED_ON;
			LED_TIMER = 0;
			led.step++;
			break;
		case 1:
			if(LED_TIMER > 499)
			{
				HRED_LED_OFF;
				led.step++;
			}
			break;
		case 2:
			if(LED_TIMER > 999)
			{
				if(led.counter < 2)
				{
					led.counter++;
					led.step -= 2;
				}
				else
				{
					if(LED_TIMER > 1999)
					{
						led.counter = 0;
						led.step -= 2;
					}
				}
			}
			break;
		
		case 4:
			RED_LED_ON;
			LED_TIMER = 0;
			led.step++;
			break;
		case 5:
			if(LED_TIMER >= 10)
			{
				RED_LED_OFF;
				LED_TIMER = 0;
				led.step++;
			}
			break;	
		case 6:
			if(LED_TIMER >= 8000)
			{
				led.step -= 2;
			}
			break;
			
		case 8:
			RED_LED_ON;
			LED_TIMER = 0;
			led.step++;
			break;
		case 9:
			if(LED_TIMER > (led.offset - 1))
			{
				RED_LED_OFF;
				led.step += 2;
			}
			break;
			
	 case 11:
			if(LED_TIMER > 109)
			{
				RED_LED_ON;
				led.step++;
			}
			break;
		case 12:
			if(LED_TIMER > (109 + led.offset))
			{
				RED_LED_OFF;
				led.step = 0;
				led.mode = _idle;
			}
			break;
			
		case 14:
			HRED_LED_ON;
			LED_TIMER = 0;
			led.step++;
			break;
		case 15:
			if(LED_TIMER > 19)
			{
				HRED_LED_OFF;
				led.step++;
			}
			break;
		case 16:
			if(LED_TIMER > 329)
			{
				led.step -= 2;
			}
			break;
	}
}

/**
* @brief 设置声音的状态
* @param null
* @retval null
*/
void buzzer_sound(void)
{
	switch(buzzer.step)
	{
		case 0:
      open_buzzer();
      BUZZER_TIMER = 0;
      buzzer.step++;
			break;
		case 1:
			if(BUZZER_TIMER > 499)
			{
				close_buzzer();
				buzzer.step++;
			}
			break;
		case 2:  
			if(BUZZER_TIMER > 999)
			{
				if(buzzer.counter < 2)
				{
					buzzer.counter++;
					buzzer.step -= 2;
				}
				else
				{
					if(BUZZER_TIMER > 1999)
					{
						buzzer.counter = 0;
						buzzer.step -= 2;
					}
				}   
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
			if(TIMER1_TIMER > 49)
			{
				TIMER1_TIMER = 0;
				if((system_data.masking & LOW_SOUND_FLAG_MSK) == 0)
			  {
				  timer5.mr0 += 1;
					system_data.masking |= TIMER1_UPDATE_FLAG_MSK;
				}
				update.step--;
			}
			break;
	}
}



