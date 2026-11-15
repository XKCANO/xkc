#include "755LHA_Batterylow_PT32L031.h"


Battery_typedef bat;


void array_right(unsigned char *arr, unsigned char l) 
{
	for(unsigned char i = l - 1; i > 0; i--)
	{
		arr[i] = arr[i-1];
	}
}


void check_islowbattery(void)
{
	if(bat.data[2] <= RomLowVoltage)
	{
		if(bat.data[1] <= RomLowVoltage)
		{
			if(bat.data[0] <= RomLowVoltage)
			{
				system_data.signal |= DEVICE_LOW_BATTERY_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
}

void check_isok(void)
{
	if(bat.data[2] > RomLowVoltage)
	{
		if(bat.data[1] > RomLowVoltage)
		{
			if(bat.data[0] > RomLowVoltage)
			{
				system_data.signal &= ~DEVICE_LOW_BATTERY_FLAG_MSK;//退出低电压模式
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
}


void measure_battery(void)
{
  switch(bat.step)
	{
	  case 0:
			if(fe_get_semaphore_state() == 0)
			{
				fe_set_semaphore(11);
				bat.step++;
			}
			break;
		case 1:
			fe_adc_init(&bat.step);
			BTS_IN_ON;
			BTS_ANA_ON;
			BL_ON;
			BATTERY_TIMER = 0;
			bat.step++;
			break;
		
		case 2:
			if(BATTERY_TIMER > 1)
			{
				bat.step++;
				fe_adc_open_scm_in1(&bat.v_data);//BTS->PA1
			}
			break;
		
		case 3:
			break;
		
		case 4:
			bat.step++;
			fe_adc_open_scm_in12(&bat.v_vref);
			break;
		
		case 5:
			break;
		
		case 6:
			BL_OFF;
			BTS_ANA_OFF;
			BTS_IN_OFF;
		  fe_clear_semaphore(11);
			bat.step++;
			break;
		
		case 7:
			array_right(bat.data, BATTERY_DATA_SIZE);
		  bat.v_data = (bat.v_data *2.0 / bat.v_vref) * 64;
		  bat.data[0] = (unsigned char)bat.v_data;
		  bat.step++;
			break;
		
		case 8:
			if(system_data.masking & BAT_INITIALIZE_FLAG_MSK)
			{
				bat.count++;
				if(bat.count > 2)
				{
					bat.count = 0;
					system_data.masking &= ~BAT_INITIALIZE_FLAG_MSK;
					bat.step++;
				}
				else
				{
					if(system_data.masking & BATTERY_SAMPLING_FLAG_MSK)
			    {
				    data_treating();
			    }
					bat.step = 0;
					bat.mode = _idle;
				}
			}
			else
			{
				bat.step++;
			}
			break;
		case 9:
      if((system_data.state & LOW_BATTERY_FLAG_MSK) != 0)
			{
			  check_isok();
			}
			else
			{
				check_islowbattery();
			}
			bat.step++;
			break;
		case 10:
			if(system_data.masking & BATTERY_SAMPLING_FLAG_MSK)
			{
				data_treating();
			}
			bat.step = 0;
			bat.mode = _idle;
      break;			
	}
}
