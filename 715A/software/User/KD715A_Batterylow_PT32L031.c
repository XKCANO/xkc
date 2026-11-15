#include "KD715A_Batterylow_PT32L031.h"


#define  LOW_BATTER    154


Battery_typedef bat;


void array_right(unsigned char *arr, unsigned char l) 
{
	for(unsigned char i = l - 1; i > 0; i--)
	{
		arr[i] = arr[i-1];
	}
}


void CheckIsLowbattery(void)
{
	if(bat.data[2] <= LOW_BATTER)
	{
		if(bat.data[1] <= LOW_BATTER)
		{
			if(bat.data[0] <= LOW_BATTER)
			{
				system_data.signal |= DEVICE_LOW_BATTERY_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
}

void CheckVoltageIsOk(void)
{
	if(bat.data[2] > LOW_BATTER)
	{
		if(bat.data[1] > LOW_BATTER)
		{
			if(bat.data[0] > LOW_BATTER)
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
			BL_ON;
			BATTERY_TIMER = 0;
			bat.step++;
			break;
		
		case 2:
			if(BATTERY_TIMER > 1)
			{
				bat.step++;
				fe_adc_open_scm_in12(&bat.v_vref);
			}
			break;
		
		case 3:
			break;
		
		case 4:
			BL_OFF;
		  fe_clear_semaphore(11);
			bat.step++;
			break;
		
		case 5:
			array_right(bat.data, BATTERY_DATA_SIZE);
		  bat.v_data = (4096 / bat.v_vref) * 64;
		  bat.data[0] = (unsigned char)bat.v_data;
		  bat.step++;
			break;
		
		case 6:
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
					bat.step = 0;
					bat.mode = _idle;
				}
			}
			else
			{
				bat.step++;
			}
			break;
			
		case 7:
      if((system_data.state & LOW_BATTERY_FLAG_MSK) != 0)
			{
			  CheckVoltageIsOk();
			}
			else
			{
				CheckIsLowbattery();
			}
			bat.step = 0;
			bat.mode = _idle;
			break;		
	}
}
