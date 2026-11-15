#include "755LHA_Windows_PT32L031.h"
#include "FE_semaphore.h"

Alarm_typedef yel_led;
Alarm_typedef red_led;
Alarm_typedef buzzer;
typedef_common update;


/**
* @brief 设置串口回调函数
* @param flag
* @retval None
*/
void uart_callback(uint32_t p, uint32_t l)
{
	if(p == SETUP_SAMPLING_FLAG)
	{
		if((system_data.masking & DEBUG_FLAG_MSK) != 0)
		{
			BATTERY_TIMER += 1000;
			system_data.masking |= BATTERY_SAMPLING_FLAG_MSK;
		}
	}
	
	if(p == CLEAR_SAMPLING_FLAG)
	{
		system_data.masking &= ~BATTERY_SAMPLING_FLAG_MSK;
	}
	
	if( p == OPEN_BUZZER)
	{
    if(buzzer.mode == _idle)
    {
      red_led.counter = 0;
      red_led.step = 0;
      red_led.mode = _exe;
      buzzer.counter = 0;
		  buzzer.step = 5;
		  buzzer.mode = _exe;
    }
	}
  
  if(p == ENTER_DEEP_SLEEP)
  {
    close_wdog(); 
    
    VH_OFF;
		HTS_ANA_OFF;
		HTS_IN_OFF;
    
    BL_OFF;
		BTS_ANA_OFF;
		BTS_IN_OFF;
    
		__NOP();
		
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
		
	  __NOP();
	  __WFI();
	  __NOP();
  }
  
}

/**
* @brief 打开蜂鸣器
** output PWM on CH4
** PCLK: 3MHz
**   PR: 2
**  CLK: 1MHz = PCLK / (PR + 1)
**   DT: 150
** Dead Time: 50us = DT / PCLK
** PA11 --> HB --> FUN1 --> TIM1_CH4
** PA12 --> HS --> FUN1 --> TIM1_CH4N
*/
void open_buzzer(void)
{
	uint32_t i;
	fe_set_semaphore(10);
  system_data.masking &= ~(TIMER1_CLOSE_FLAG_MSK + TIMER1_UPDATE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK);
  
	PWM1->PR = 2;
	PWM1->DT = 150;
	PWM1->TCR = 0;
	__NOP();
	PWM1->MCR = 0;
	PWM1->CMR = 0;
	PWM1->CCR = 0;
	PWM1->INT_RPT = 0;

  if(system_data.masking & LOW_SOUND_FLAG_MSK)
	{
    i = update.value = LOW_TIMER_US;
  }
  else
  {
    i = update.value = MIN_TIMER_US;
  }
	PWM1->MR0 = i / 2;
	PWM1->MR4 = i / 4;
	PWM1->MCR |= PWM_MCR_DIR_RV + PWM_MCR_MR0I;
	PWM1->CMR |= PWM_CMR_PWM4n_EN + PWM_CMR_MC4_MODE2;

  PWM1->TCR |= PWM_TCR_EN;
	i = PWM1->ISR;
	PWM1->ISR |= i;
  NVIC_EnableIRQ(TIMER1_IRQn);
  
	if(system_data.masking & LOW_SOUND_FLAG_MSK)
	{
	  CMSDK_PA->ALTFUNCSET1 |= (GPIO_AFS_FUN2 << 12);
	}
	else
	{
		CMSDK_PA->ALTFUNCSET1 |= (GPIO_AFS_FUN2 << 16) + (GPIO_AFS_FUN2 << 12);
	}
	
	update.step = 0;
	update.mode = _exe;
	system_data.masking |= OPEN_BOOST_FLAG_MSK;
}


/**
* @brief 关闭蜂鸣器
* @param flag
* @retval None
*/
void close_buzzer(void)
{
	fe_clear_semaphore(10);
	
	update.step = 0;
	update.mode = _idle;

	if((system_data.masking & (KEY2_OUT_FLAG_MSK + KEY5_OUT_FLAG_MSK)) == 0)
	{
		system_data.masking |= CLOSE_BOOST_FLAG_MSK;
	}

  system_data.masking |= TIMER1_CLOSE_FLAG_MSK;
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
void set_wire_connect(unsigned char flag)
{
	switch(flag)
	{
		case CLOSE_ALL:
			IO_PIN_OFF;
		  IO_PIN_IN;
	    IOUT_OFF;
      system_data.masking &= ~(KEY2_OUT_FLAG_MSK + KEY5_OUT_FLAG_MSK);
 		  break;
		
		case I_OUT:
			IO_PIN_OFF;
		  IO_PIN_IN;
		  IOUT_ON;
		  system_data.masking &= ~KEY5_OUT_FLAG_MSK;
		  system_data.masking |= KEY2_OUT_FLAG_MSK;
			break;
		
		case IO_OUT:
			IOUT_OFF;
		  IO_PIN_OUT;
			IO_PIN_ON;
		  system_data.masking &= ~KEY2_OUT_FLAG_MSK;
		  system_data.masking |= KEY5_OUT_FLAG_MSK;
			break;
		
		case I_IO_OUT:
		  IO_PIN_OUT;
			IO_PIN_ON;
	    IOUT_ON;
      system_data.masking |= KEY2_OUT_FLAG_MSK + KEY5_OUT_FLAG_MSK;
			break;
	}
}

/**
* @brief 设置无线发送
* @param flag
* @retval None
*/
void set_wireless_connect(unsigned char cmd)
{
	if(system_data.masking & ON_NET_FLAG_MSK)
	{
		SEND_CMD = cmd;
		system_data.masking |= RF_SEND_FLAG_MSK;
	}
}

/**
* @brief 关闭声光指示
* @retval None
**/
void remove_alarm(void)
{
	fe_clear_semaphore(10);
	
  set_wire_connect(CLOSE_ALL);
  
  RED_LED_OFF;
	RED1_LED_OFF;
	YELLOW_LED_OFF;
  
	red_led.mode = _idle;
	yel_led.mode = _idle;
	buzzer.mode = _idle;
  update.mode = _idle;
  
	system_data.masking &= ~LOW_SOUND_FLAG_MSK;
	system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
}

/**
* @brief 设置声光指示
* @retval None
**/
void alarm_cfg(unsigned char mode)
{
	switch(mode)
	{
		case TEST_MODE:
			YELLOW_LED_OFF;
		  red_led.counter = 0;
		  red_led.offset = 0;
		  red_led.step = 0;
			red_led.mode = _exe;
		  buzzer.counter = 0;
		  buzzer.offset = 0;
			buzzer.step = 0;
			buzzer.mode = _exe;
      yel_led.mode = _idle;
			system_data.masking |= LOW_SOUND_FLAG_MSK;
			break;

		case FIRE_MODE:
			YELLOW_LED_OFF;
		  red_led.counter = 0;
		  red_led.offset = 0;
			red_led.step = 0;
			red_led.mode = _exe;
		  buzzer.counter = 0;
		  buzzer.offset = 0;
			buzzer.step = 5;
			buzzer.mode = _exe;
      yel_led.mode = _idle;
		  system_data.masking &= ~LOW_SOUND_FLAG_MSK;
			break;
			
		case REDLED_ONCE_LOW:
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
			red_led.offset = 2;
			red_led.step = 16;
			red_led.mode = _exe;
      buzzer.mode = 
      yel_led.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
		
		case REDLED_ONCE_MED:
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
			red_led.offset = 10;
			red_led.step = 16;
			red_led.mode = _exe;
      buzzer.mode = 
      yel_led.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
		  break;
		
		case YELLOWLED_ONCE_LOW:
			RED_LED_OFF;
	    RED1_LED_OFF;
			YELLOW_LED_TIMER = 110;
			yel_led.offset = 2;
			yel_led.step = 3;
			yel_led.mode = _exe;
      red_led.mode =
      buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
		
		case YELLOWLED_TWICE_LOW:
			RED_LED_OFF;
	    RED1_LED_OFF;
			yel_led.offset = 2;
			yel_led.step = 0;
			yel_led.mode = _exe;
      red_led.mode =
      buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
			
		case LOW_BAT_MODE:
			RED_LED_OFF;
	    RED1_LED_OFF;
			YELLOW_LED_TIMER = 110;
			yel_led.offset = 10;
			yel_led.step = 3;
			yel_led.mode = _exe;
			BUZZER_TIMER = 110;
			buzzer.step = 11;
			buzzer.mode = _exe;
      red_led.mode = _idle;
			break;
		
		case SENSOR_FAULT_MODE:
			RED_LED_OFF;
	    RED1_LED_OFF;
      yel_led.offset = 10;
			yel_led.step = 0;
			yel_led.mode = _exe;
			buzzer.step = 9;
			buzzer.mode = _exe;
      red_led.mode = _idle;
			break;
			
		case NET_ALARM_MODE:
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
		  buzzer.counter = 0;
		  buzzer.offset = 0;
			buzzer.step = 5;
			buzzer.mode = _exe;
      yel_led.mode = 
      red_led.mode = _idle;
			break;
		
		case BUZZER_ONCE:
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
			BUZZER_TIMER = 110;
			buzzer.step = 11;
			buzzer.mode = _exe;
      yel_led.mode = 
      red_led.mode = _idle;
			break;
			
		case EXT_ERROR:
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
			red_led.step = 8;
			red_led.mode = _exe;
      yel_led.mode =
      buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
		
		case NET_WORK_SECCESS:
			red_led.step = 12;
			red_led.mode = _exe;
      yel_led.mode =
      buzzer.mode = _idle;
		  system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
			
		case	HUSH_MODE:
			
			YELLOW_LED_OFF;
			RED_LED_OFF;
	    RED1_LED_OFF;
			red_led.step = 4;
			red_led.mode = _exe;
      yel_led.mode =
      buzzer.mode = _idle;
      system_data.masking |= TIMER1_CLOSE_FLAG_MSK + CLOSE_BOOST_FLAG_MSK;
			break;
	}
}

/************************************************************************
  * @brief  LED  
	*  
*************************************************************************/
void red_led_lighten(void)
{
	switch(red_led.step)
	{
		case 0:
			RED_LED_ON;
			RED1_LED_ON;
			RED_LED_TIMER = 0;
			red_led.step++;
			break;
		case 1:
			if(RED_LED_TIMER > 499)
			{
				RED_LED_OFF;
				RED1_LED_OFF;
				red_led.step++;
			}
			break;
		case 2:
			if(RED_LED_TIMER > 999)
			{
				if(red_led.counter < 2)
				{
					red_led.counter++;
					red_led.step -= 2;
				}
				else
				{
					if(RED_LED_TIMER > 1999)
					{
						red_led.counter = 0;
						red_led.step -= 2;
					}
				}
			}
			break;
		
    case 4:
			RED1_LED_ON;
		  RED_LED_TIMER = 0;
		  red_led.step++;
			break;
		case 5:
			if(RED_LED_TIMER > 9)
			{
				RED1_LED_OFF;
				RED_LED_TIMER = 0;
				red_led.step++;
			}
			break;
		case 6:
			if(RED_LED_TIMER >= 8000)
			{
				red_led.step -= 2;
			}
			break;
			
			
    //互联错误
		case 8:
			RED_LED_ON;
			RED1_LED_ON;
			RED_LED_TIMER = 0;
			red_led.step++;
			break;
		case 9:
			if(RED_LED_TIMER > 19)
			{
				RED_LED_OFF;
				RED1_LED_OFF;
				red_led.step++;
			}
			break;
		case 10:
			if(RED_LED_TIMER > 329)
			{
				red_led.step -= 2;
			}
			break;
		
		//配网时序灯 1s闪烁一次
		case 12:
			RED1_LED_ON;
			RED_LED_TIMER = 0;
			red_led.step++;
			break;
		case 13:
			if(RED_LED_TIMER > 499)
			{
				RED1_LED_OFF;
				red_led.step++;
			}
			break;
		case 14:
			if(RED_LED_TIMER > 999)
			{
				if(red_led.counter < 2)
				{
					red_led.counter++;
					red_led.step -= 2;
				}
				else
				{
					if(system_data.masking & DECEIVE_MASTER_FLAG_MSK)
					{
						RF_TIMER = 0;
						RED1_LED_ON;
					}
					red_led.counter = 0;
					red_led.step = 0;
					red_led.mode = _idle;
				}
			}
			break;
		
		//呼吸灯
		case 16:
			RED1_LED_ON;
			RED_LED_TIMER = 0;
			red_led.step++;
			break;
		case 17:
			if(RED_LED_TIMER > (red_led.offset - 1))
			{
				RED1_LED_OFF;
				red_led.step = 0;
				red_led.mode = _idle;
			}
			break;
	}
}


void yellow_led_lighten(void)
{
	switch(yel_led.step)
	{
		//黄灯闪烁两次
		case 0:
			YELLOW_LED_ON;
			YELLOW_LED_TIMER = 0;
			yel_led.step++;
			break;
		case 1:
			if(YELLOW_LED_TIMER > (yel_led.offset - 1))
			{
			  YELLOW_LED_OFF;
		    yel_led.step += 2;
			}
			break;
			
		case 3:
			if(YELLOW_LED_TIMER > 109)
			{
				YELLOW_LED_ON;
				YELLOW_LED_TIMER = 110;
				yel_led.step++;
			}
			break;
		case 4:
			if(YELLOW_LED_TIMER > (yel_led.offset + 109))
			{
			  YELLOW_LED_OFF;
				yel_led.offset = 0;
		    yel_led.step = 0;
				yel_led.mode = _idle;
			}
			break;
	}
}


void buzzer_sound(void)
{
	switch(buzzer.step)
	{
		case 0:
			if((fe_get_semaphore_state() & 0x800) == 0)
			{
				open_buzzer();
			  BUZZER_TIMER = 0;
			  buzzer.counter++;
			  buzzer.step++;
			}
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
		case 3:
			if(BUZZER_TIMER > 1999)
			{
        buzzer.offset++;
				if(buzzer.offset < 2)
				{
					buzzer.step -= 3;
				}
				else
				{
					system_data.masking &= ~LOW_SOUND_FLAG_MSK;
					buzzer.offset = 0;
				  buzzer.counter = 0;
					buzzer.step += 2;
				}
			}
			break;
			
		case 5:
			if((fe_get_semaphore_state() & 0x800) == 0)
			{
				open_buzzer();
				BUZZER_TIMER = 0;
				buzzer.step++;
			}
			break;
		case 6:
			if(BUZZER_TIMER > 499)
			{
				close_buzzer();
				buzzer.step++;
			}
			break;
		case 7:
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

		//响两下
		case 9:
			if((fe_get_semaphore_state() & 0x800) == 0)
			{
				open_buzzer();
				BUZZER_TIMER = 0;
				buzzer.step++;
			}
			break;
		case 10: 
			if(BUZZER_TIMER > 9)
			{
			  close_buzzer();
        buzzer.step++;
			}
			break;
			
		case 11:
			if(BUZZER_TIMER > 109)
			{
				if((fe_get_semaphore_state() & 0x800) == 0)
			  {
					open_buzzer();
					BUZZER_TIMER = 110;
					buzzer.step++;
				}
			}
			break;
		case 12:
			if(BUZZER_TIMER > 119)
			{ 
				close_buzzer();
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
		  if(system_data.masking & LOW_SOUND_FLAG_MSK)
			{
				update.step += 3;
			}
			else
			{
				update.step++;
			}
			break;
		case 1:
			if(TIMER1_TIMER > 249)
			{
				TIMER1_TIMER = 0;
        update.value++;
				system_data.masking |= TIMER1_UPDATE_FLAG_MSK;
				update.step--;
			}
			break;
			
		case 3:
			if(TIMER1_TIMER > 299)
			{
				TIMER1_TIMER = 0;
        update.value++;
				system_data.masking |= TIMER1_UPDATE_FLAG_MSK;
				update.step -= 3;
			}
			break;
	}
}




