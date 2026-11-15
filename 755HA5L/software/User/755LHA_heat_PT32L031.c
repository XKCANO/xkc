#include "755LHA_Heat_PT32L031.h"
#include "FE_semaphore.h"
#include "FE_755LHA_UART_PT32L031.h"

#define     ADC_UPPER_LIMIT     3966  //125℃
#define     ADC_LOWER_LIMIT     290   //-25℃

HEAT_TypeDef heat;

/************************************************************************
  * @brief  获取基准温度
  * @param  None
  * @return: no
************************************************************************/
void generating_basedata(void)
{
	FE_CURVE_AVERAGE_TypeDef t;
	uint32_t u;
	
	fe_get_curve_average(&t, heat.t_data, CAL_BASE_TIME);
	
	u = fe_subtractive(t.average, heat.base_data);
	
	if(u > 0x8000)
	{
		heat.base_data = t.average;
	}
	else if(t.u <= 256) //2.0 * 128 = 256
	{
		if(t.average <= 5376 || t.average > 0x8000) //42.0 * 128 = 5376
		{
      heat.base_data = t.average;
		}
		else if(u <= 192) //1.5 * 128 = 192
		{
			heat.base_data = t.average;
		}
    else
    {
      fe_get_curve_average(&t, heat.t_data, T_DATA_SIZE);
		  if(t.u <= 768) //6.0 * 128 = 768
		  {
			  heat.base_data = t.average;
		  }
    }
	}
	else
	{
		fe_get_curve_average(&t, heat.t_data, T_DATA_SIZE);
		if(t.u <= 768) //6.0 * 128 = 768
		{
			heat.base_data = t.average;
		}
	}
}

/************************************************************************
  * @brief  Check Is 20k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is20k(void)
{
  if(fe_real_comparision(heat.base_data, 5888) == fe_math_less) //46 * 128 = 5888
  {
		if(heat.counter >= 11)
		{
			if(heat.rate >= 832) //6.5 * 128 = 832
			{
				if(heat.t_minute[0] >= 960 && heat.t_minute[1] >= 960) //7.5 * 128 = 960
				{
					return 0xFFFFFFFF;
				}
			}
		}
  }
  return  0;
}

/************************************************************************
  * @brief  Check Is 10k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is10k(void)
{
	uint32_t u;
	
	if(heat.counter >= 18) 
	{
		if(heat.rate >= 576) //4.5 * 128 = 576
		{
			u = fe_subtractive(heat.t_data[0], heat.base_data);
			
			if(u > 1280) //10 * 128 = 1280
			{
			  return 0xFFFFFFFF;
			}
		}
	}
	return  0;
}

/************************************************************************
  * @brief  Check Is 5k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is5k(void)
{
	uint32_t u;
	
	if(heat.counter >= 40)
	{
		if(heat.rate >= 396) //3.1 * 128 = 396
		{
			u = fe_subtractive(heat.t_data[0], heat.base_data);
			
			if(u >= 1280) //10 * 128 = 1280
			{
			  return 0xFFFFFFFF;
			}
		}
	}
	return  0;
}

/************************************************************************
  * @brief  Check Is 3k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is3k(void)
{
	uint32_t u;
	
	if(heat.counter >= 76)
	{
		if(heat.rate >= 205) //1.6 * 128 = 205
		{
			u = fe_subtractive(heat.t_data[0], heat.base_data);
			
			if(u >= 1280) //10 * 128 = 1280
			{
			  return 0xFFFFFFFF;
			}
		}
	}
	return  0;
}

/************************************************************************
  * @brief  Check Is 1k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is1k(void)
{
  uint32_t t;
  
	if(fe_real_comparision(heat.base_data, 5888) == fe_math_less) //46 * 128 = 5888
	{
		if(heat.t_data[0] >= 6656)//52 * 128 = 6656
		{
			if(heat.t_average_128 >= 64)//0.5 * 128 = 64
			{
				t = fe_get_real_minimum(heat.t_data, 8);
				
				if(t > 6272 && t < 0x8000) // 49 * 128 = 6272
				{
					return 0xFFFFFFFF;
				}
			}
		}
  }
	return 0;
}

/************************************************************************
  * @brief  Check Is 0.2k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 0xFFFFFFFF
************************************************************************/
uint32_t check_is02k(void)
{
	uint32_t t,u;
  
	if(heat.t_data[0] >= 7040) //55 * 128 = 7040
	{
		t = fe_get_real_minimum(heat.t_data, 16);
		if(t > 6656 && t < 0x8000) //52 * 128 = 6656
		{
		  return 0xFFFFFFFF;
		}
		else
		{
			if(fe_real_comparision(heat.base_data, 5888) == fe_math_greater) //46 * 128 = 5888
		  {
				t = 0;
				do{
					u = fe_subtractive(heat.t_data[t], heat.base_data);
					t++;
				}while(u > 256 && u < 0x8000); //2.0 * 128 = 256
				
				if(t >= 10 && heat.rate >= 960) //7.5 * 128 = 960
				{
					return 0xFFFFFFFF;
				}
		  }
	  }
	}
	return 0;
}

/************************************************************************
  * @brief  Check Is Safe
  * @param  None
  * @return: no
************************************************************************/
void check_issafe(void)
{
	uint32_t t;
		
	t = fe_get_real_maximum(heat.t_data, 16);
	
	if(t < 6272) //49 * 128 = 6272
	{
		if(fe_real_comparision(t, heat.stop_data) == fe_math_less)
		{
			ALARM_TIMER = 0;
			ALARM_M_TIMER = 0;//多次报警，报警记忆计时以最近一次的报警为准
			
			system_data.signal &= ~DEVICE_ALARM_FLAG_MSK;
			system_data.signal |= DEVICE_ALARM_MEMORY_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
}

/************************************************************************
  * @brief  data treating
  * @param  None
  * @return: no
************************************************************************/
void data_treating(void)
{
	unsigned char buffer[15];
	
	mem_data_copy(buffer, (unsigned char *)(&heat.ntc_data), 10);
	buffer[10] = (unsigned char)heat.t_data[0];
	buffer[11] = (unsigned char)(heat.t_data[0] >> 8);
	buffer[12] = (unsigned char)heat.t_minute[0];
	buffer[13] = (unsigned char)(heat.t_minute[0] >> 8);
	buffer[14] = bat.data[0];
	fe_uart_write(buffer, 15);
}

/************************************************************************
  * @brief  uart out
  * @param  None
  * @return: no
************************************************************************/
void issue_outputdata(void)
{
	heat.step = 0;
	heat.mode = _idle;

	if(eeprom_data.marking & 0x80)
	{
		data_treating();
	}
}

/************************************************************************
  * @brief  Fire Alarm
  * @param  None
  * @return: no
************************************************************************/
void fire_alarm(void)
{
	uint32_t i;
	
	i = fe_subtractive(heat.t_data[0], heat.base_data);
	i *= 77;
	i /= 128;
	i = i + heat.base_data;
	heat.stop_data = (unsigned short)i;
	
	system_data.signal |= DEVICE_ALARM_FLAG_MSK;
	system_data.masking |= MESSAGE_FLAG_MSK;

	issue_outputdata();
}

/*
 * @brief HEAT主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void heat_process_run(void)
{
	switch(heat.step)
	{
		case 0:
			if((fe_get_semaphore_state() & 0x400) == 0)
			{
				fe_set_semaphore(11);
				heat.step++;
			}
			break;
			
		case 1:
			fe_adc_init(&heat.step);
			HTS_IN_ON;
			HTS_ANA_ON;
			VH_ON;
			HEAT_TIMER = 0;
			heat.step++;
			break;
		
		case 2:
			if(HEAT_TIMER > 1) //2ms
			{
				heat.step++;
				fe_adc_open_scm_in6(&heat.ntc_data);//HTS -> PA6
			}
			break;
		
		case 3:
			break;
		
		case 4:
			VH_OFF;
			HTS_ANA_OFF;
			HTS_IN_OFF;
			fe_clear_semaphore(11);
			heat.step++;
			break;
		
		case 5:
		  if((system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK) == 0)
			{
				if(heat.ntc_data > ADC_UPPER_LIMIT || heat.ntc_data < ADC_LOWER_LIMIT)
				{
					heat.fault_time++;
					if(heat.fault_time >= 30)
					{
						heat.normal_time = 0;
						system_data.signal |= DEVICE_SENSOR_FAULT_FLAG_MSK;
						system_data.masking |= MESSAGE_FLAG_MSK;
					}
					issue_outputdata();
				}
				else
				{
					heat.fault_time = 0;
					fe_data_move_to_right(heat.t_data, T_DATA_SIZE);
			    heat.step++;
				}
			}
			else
			{
				if(heat.ntc_data < ADC_UPPER_LIMIT && heat.ntc_data > ADC_LOWER_LIMIT)
				{
					heat.normal_time++;
					if(heat.normal_time >= 3)
					{
						heat.normal_time = 0;
						system_data.signal &= ~DEVICE_SENSOR_FAULT_FLAG_MSK;//退出传感器故障
			      system_data.masking |= MESSAGE_FLAG_MSK + HEAT_INITIALIZE_FLAG_MSK;
					}
				}
				issue_outputdata();
			}
			break;
		
		case 6:
			heat.t_data[0] = fe_calculate_external_16b_temperature(heat.ntc_data);
			if((system_data.masking & HEAT_INITIALIZE_FLAG_MSK) != 0)
			{
				heat.normal_time++;
				if(heat.normal_time < 8)
				{
					issue_outputdata();
				}
				else
				{
					heat.step++;
				}
			}
			else
			{
				heat.step++;
			}
			break;
			
		case 7:
			fe_data_move_to_right(heat.t_minute, U_DATA_SIZE);
			if(fe_real_comparision(heat.t_data[0], heat.t_data[7]) == fe_math_greater)
			{
				heat.t_minute[0] = fe_subtractive(heat.t_data[0], heat.t_data[7]);
			}
			else
			{
				heat.t_minute[0] = 0;
			}
			heat.rate = fe_get_2b_filter(heat.rate, heat.t_minute[0]);
			heat.step++;
			break;
		
		case 8:
			if((system_data.masking & HEAT_INITIALIZE_FLAG_MSK) != 0)
			{
				if(heat.normal_time < CAL_BASE_TIME)
				{
					heat.base_data = heat.t_data[0];
					issue_outputdata();
				}
				else
				{
					system_data.masking &= ~HEAT_INITIALIZE_FLAG_MSK;
					generating_basedata();
					heat.step++;
				}
			}
			else
			{
				generating_basedata();
				heat.step++;
			}
			break;
					
		case 9:
			if(heat.t_minute[0] > 51) //0.4 * 128 = 51
			{
				heat.counter++;
			}
			else
			{
				heat.counter = 0;
			}
			heat.t_average_128 = fe_get_average(heat.t_minute, U_DATA_SIZE);
			heat.step++;
			break;
			
		case 10:
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) != 0)
			{
				check_issafe();
				issue_outputdata();
			}
			else
			{
				heat.step++;
			}
			break;
		case 11:
			if(check_is20k())
			{
				fire_alarm();
			}
			else
			{
				if(check_is10k())
				{
					fire_alarm();
				}
				else
				{
					heat.step++;
				}
			}
			break;
		case 12:
			if(check_is5k())
			{
				fire_alarm();
			}
			else
			{
				if(check_is3k())
				{
					fire_alarm();
				}
				else
				{
					heat.step++;
				}
			}
			break;
		case 13:
			if(check_is1k())
			{
				fire_alarm();
			}
			else
			{
				if(check_is02k())
				{
					fire_alarm();
				}
				else
				{
					issue_outputdata();
				}
			}
			break;			
  }
}

/*---------------------------------------------------------------------------------------------------------*/
