#include "KD715A_Heat_PT32L031.h"
#include "FE_semaphore.h"
#include "FE_755LHA_UART_PT32L031.h"

#define     ADC_UPPER_LIMIT     3966  //125℃
#define     ADC_LOWER_LIMIT     290   //-25℃

HEAT_TypeDef Heat;

/************************************************************************
  * @brief  获取基准温度
  * @param  None
  * @return: no
************************************************************************/
void GeneratingBaseData(void)
{
	FE_CURVE_AVERAGE_TypeDef t;
	uint32_t u;
	
	fe_get_curve_average(&t, Heat.t_data, CAL_BASE_TIME);
	
	u = fe_subtractive(t.average, Heat.base_data);
	
	if(u > 0x8000)
	{
		Heat.base_data = t.average;
	}
	else if(t.u <= 256)
	{
		Heat.base_data = t.average;
	}
	else
	{
		fe_get_curve_average(&t, Heat.t_data, T_DATA_SIZE);
		
		if(t.u <= 384)
		{
			Heat.base_data = t.average;
		}
	}
}

/************************************************************************
  * @brief  Check Is 20k
  * @param  None
  * @return: 
  *  不符合: 0
  *    符合: 1
************************************************************************/
uint32_t CheckIs20K(void)
{
	if(Heat.counter >= 8)
	{
		if(Heat.rate >= 960) //7.5 * 128 = 960
		{
			if(Heat.t_minute[0] >= 960 && Heat.t_minute[1] >= 960) //7.5 * 128 = 960
			{
				return 0xFFFFFFFF;
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
  *    符合: 1
************************************************************************/
uint32_t CheckIs10K(void)
{
	uint32_t u;
	
	if(Heat.counter >= 18) 
	{
		if(Heat.rate >= 576) //4.5 * 128 = 576
		{
			u = fe_subtractive(Heat.t_data[0], Heat.base_data);
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
  *    符合: 1
************************************************************************/
uint32_t CheckIs5K(void)
{
	uint32_t u;
	
	if(Heat.counter >= 40)
	{
		if(Heat.rate >= 320) //2.5 * 128 = 320
		{
			u = fe_subtractive(Heat.t_data[0], Heat.base_data);
			
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
  *    符合: 1
************************************************************************/
uint32_t CheckIs3K(void)
{
	uint32_t u;
	
	if(Heat.counter >= 60)
	{
		if(Heat.rate >= 166) //1.3 * 128 = 166 需要线下测试，根据实际来定
		{
			u = fe_subtractive(Heat.t_data[0], Heat.base_data);
			
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
  *    符合: 1
************************************************************************/
uint32_t CheckIs1K(void)
{
	uint32_t t;
	
	//45 * 128 = 5760
	t = fe_get_minimum(Heat.t_data, 8);
	
	if(Heat.t_data[0] >= 6400) //50 * 128 = 6400
	{
		if(Heat.t_average_128 >= 64) //0.5 * 128 = 64
		{
			if(t > 5760)
			{
				return 0xFFFFFFFF;
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
  *    符合: 1
************************************************************************/
uint32_t CheckIs02K(void)
{
	uint32_t t;
	
	if(Heat.t_data[0] >= 6784) //53 * 128 = 6784
	{
		t = fe_get_minimum(Heat.t_data, 16);
		
		if(t > 6400) //50 * 128 = 6400
		{
			return 0xFFFFFFFF;
		}
	}
	return 0;
}

/************************************************************************
  * @brief  Check Is Safe
  * @param  None
  * @return: no
************************************************************************/
void CheckIsSafe(void)
{
	uint32_t t,k;
	
	t = fe_get_maximum(Heat.t_data, 16);
	k = fe_subtractive(Heat.stop_data,  t);
	
	if(t < 6272) //49 * 128 = 6272
	{
		if(k < 0x8000)
		{
			ALARM_TIMER = 0;
			
			system_data.signal &= ~DEVICE_ALARM_FLAG_MSK;
			system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
}

/************************************************************************
  * @brief  uart out
  * @param  None
  * @return: no
************************************************************************/
void IssueOutputData(void)
{
	unsigned char buffer[15];
	
	Heat.step = 0;
	Heat.mode = _idle;

	if(eeprom_data.marking & 0x80)
	{
		mem_data_copy(buffer, (unsigned char *)(&Heat.ntc_data), 10);
		buffer[10] = (unsigned char)Heat.t_data[0];
		buffer[11] = (unsigned char)(Heat.t_data[0] >> 8);
		buffer[12] = (unsigned char)Heat.t_minute[0];
		buffer[13] = (unsigned char)(Heat.t_minute[0] >> 8);
		buffer[14] = bat.data[0];
		fe_uart_write(buffer, 15);
	}
}

/************************************************************************
  * @brief  Fire Alarm
  * @param  None
  * @return: no
************************************************************************/
void FireAlarm(void)
{
	unsigned int i;
	
	i = fe_subtractive(Heat.t_data[0],Heat.base_data);
	i *= 77;
	i /= 128;
	
	i += Heat.base_data;
	Heat.stop_data = (unsigned short)i;
	
	system_data.signal |= DEVICE_ALARM_FLAG_MSK;
	system_data.masking |= MESSAGE_FLAG_MSK;
	
	IssueOutputData();
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
void fe_heat_process_run(void)
{
	switch(Heat.step)
	{
		case 0:
			if(fe_get_semaphore_state() == 0)
			{
				fe_set_semaphore(11);
				Heat.step++;
			}
			break;
			
		case 1:
			fe_adc_init(&Heat.step);
			HTS_IN_ON;
			HTS_ANA_ON;
			VH_ON;
			HEAT_TIMER = 0;
			Heat.step++;
			break;
		
		case 2:
			if(HEAT_TIMER > 1) //2ms
			{
				Heat.step++;
				fe_adc_open_scm_in1(&Heat.ntc_data);
			}
			break;
		
		case 3:
			break;
		
		case 4:
			VH_OFF;
			HTS_ANA_OFF;
			HTS_IN_OFF;
			fe_clear_semaphore(11);
			Heat.step++;
			break;
		
		case 5:
		  if((system_data.signal & DEVICE_SENSOR_FAULT_FLAG_MSK) == 0)
			{
				if(Heat.ntc_data > ADC_UPPER_LIMIT || Heat.ntc_data < ADC_LOWER_LIMIT)
				{
					Heat.fault_time++;
					if(Heat.fault_time >= 30)
					{
						Heat.normal_time = 0;
						system_data.signal |= DEVICE_SENSOR_FAULT_FLAG_MSK;
						system_data.masking |= MESSAGE_FLAG_MSK;
					}
					IssueOutputData();
				}
				else
				{
					Heat.fault_time = 0;
					fe_data_move_to_right(Heat.t_data, T_DATA_SIZE);
			    Heat.step++;
				}
			}
			else
			{
				if(Heat.ntc_data < ADC_UPPER_LIMIT && Heat.ntc_data > ADC_LOWER_LIMIT)
				{
					Heat.normal_time++;
					if(Heat.normal_time >= 3)
					{
						Heat.normal_time = 0;
						system_data.signal &= ~DEVICE_SENSOR_FAULT_FLAG_MSK;//退出传感器故障
			      system_data.masking |= MESSAGE_FLAG_MSK + HEAT_INITIALIZE_FLAG_MSK;
					}
				}
				IssueOutputData();
			}
			break;
		
		case 6:
			Heat.t_data[0] = fe_calculate_external_16b_temperature(Heat.ntc_data);
			if((system_data.masking & HEAT_INITIALIZE_FLAG_MSK) != 0)
			{
				Heat.normal_time++;
				if(Heat.normal_time < 8)
				{
					IssueOutputData();
				}
				else
				{
					Heat.step++;
				}
			}
			else
			{
				Heat.step++;
			}
			break;
			
		case 7:
			fe_data_move_to_right(Heat.t_minute, U_DATA_SIZE);
			if(fe_comparision(Heat.t_data[0], Heat.t_data[11]) == fe_math_greater)
			{
				Heat.t_minute[0] = fe_subtractive(Heat.t_data[0], Heat.t_data[11]);
			}
			else
			{
				Heat.t_minute[0] = 0;
			}
			Heat.rate = fe_get_2b_filter(Heat.rate, Heat.t_minute[0]);
			Heat.step++;
			break;
		
		case 8:
			if((system_data.masking & HEAT_INITIALIZE_FLAG_MSK) != 0)
			{
				if(Heat.normal_time < CAL_BASE_TIME)
				{
					Heat.base_data = Heat.t_data[0];
					IssueOutputData();
				}
				else
				{
					system_data.masking &= ~HEAT_INITIALIZE_FLAG_MSK;
					GeneratingBaseData();
					Heat.step++;
				}
			}
			else
			{
				GeneratingBaseData();
				Heat.step++;
			}
			break;
					
		case 9:
			if(Heat.t_minute[0] > 51) //0.4 * 128 = 51                                                         
			{
				Heat.counter++;
			}
			else
			{
				Heat.counter = 0;
			}
			Heat.t_average_128 = fe_get_average(Heat.t_minute, U_DATA_SIZE);
			Heat.step++;
			break;
			
		case 10:
			if((system_data.signal & DEVICE_ALARM_FLAG_MSK) != 0)
			{
				CheckIsSafe();
				IssueOutputData();
			}
			else
			{
				Heat.step++;
			}
			break;
		case 11:
			if(CheckIs20K())
			{
				FireAlarm();
			}
			else
			{
				if(CheckIs10K())
				{
					FireAlarm();
				}
				else
				{
					Heat.step++;
				}
			}
			break;
		case 12:
			if(CheckIs5K())
			{
				FireAlarm();
			}
			else
			{
				if(CheckIs3K())
				{
					FireAlarm();
				}
				else
				{
					Heat.step++;
				}
			}
			break;
		case 13:
			if(CheckIs1K())
			{
				FireAlarm();
			}
			else
			{
				if(CheckIs02K())
				{
					FireAlarm();
				}
				else
				{
					IssueOutputData();
				}
			}
			break;			
  }
}

/*---------------------------------------------------------------------------------------------------------*/
