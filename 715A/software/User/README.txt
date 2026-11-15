/* --------------------------------------------------------------------------- */
 *
 *
 * Author : 
 *   xu
 *
 * History : 2024-7-2
 *
 *
/* --------------------------------------------------------------------------- */

1.这里主要分析一下报警记忆，会修改低功耗定时器，间接的影响到很多功能

受影响功能：待机40s，热感8s，故障报警40s，静音10min和红灯8s，电池电压48s

开启报警记忆：
a.低功耗定时器定时唤醒由8s更改为2s -> timer_factor = 4
b.待机40s功能取消
c.热感还是8s，HEAT_TIMER1 += 2000;
d.故障报警40s，FAULT_TIMER += 2000;
e.静音10min，HUSH_TIMER += 2000;
f.电池电压48s，BATTERY_TIMER1 += 2000;


//故障状态下的定时器
		if(LOWBATTERY_TIMER_40S >= 40000)
		{
			LOWBATTERY_TIMER_40S = 0;
			alarm_init(SENSOR_ERROR_MODE);
		}
		
		//故障免打扰状态下连个定时器
		if(FAULT_DND_TIMER > 24000)
		{
			FAULT_DND_TIMER = 0;
			alarm_init(LOWBATTERY_DND_MODE);
		}
		if(FAULT_DND_TIMER1 > 120000) // 10h -> 2min
		{
			system_data.masking &= ~FAULT_DND_FLAG_MSK; //故障免打扰解除 10h
		}
		
		//低电压模式下的定时器
		if(LOWBATTERY_TIMER_40S >= 40000)
		{
			LOWBATTERY_TIMER_40S = 0;
			alarm_init(SENSOR_ERROR_MODE);
		}
		//低电压免打扰模式下的定时器 -> 没有退出时间
		if(LOWBATTERY_NDN_TIMER1 > 24000)
		{
			LOWBATTERY_NDN_TIMER1 = 0;
			alarm_init(LOWBATTERY_DND_MODE);
		}
		
		//报警记忆模式下的定时器
		if(STANDBY_TIMER >= 2000)
		{
			STANDBY_TIMER = 0;
			alarm_init(STANDBY_MODE);
		}
		if(ALARM_MEMORY_TIMER > 259200000)//72h
		{
			if(system_data.masking & ALARM_MEMORY_FLAG_MSK)
			{
				system_data.masking &= ~ALARM_MEMORY_FLAG_MSK;
			}
		}
		
		//报警记忆免打扰模式下的定时器
		if(LOWBATTERY_TIMER_40S >= 40000)
		{
			LOWBATTERY_TIMER_40S = 0;
			alarm_init(SENSOR_ERROR_MODE);
		}
		if(MEMORY_NDN_TIMER >= 120000) //10h -> 2min
		{
			system_data.masking &= ~MEMORY_DND_FLAG_MSK;
		}
		
		//静音模式下的定时器
		if(HUSH_TIMER1 >= 8000)
	  {
			HUSH_TIMER1 = 0;
      alarm_init(STANDBY_MODE);
	  }
		
		//正常待机模式下的定时器
		if(STANDBY_TIMER >= 40000)
		{
			STANDBY_TIMER = 0;
			alarm_init(STANDBY_MODE);
		}






if(system_data.state & LOWBAT_FLAG_MSK)
			{
			  if(ALARM_TIMER1 > 40000) //40s
        {
          ALARM_TIMER1 = 0;
          alarm_init(REDLED_TWICE_SOUND);
        }
			}
			else
			{
				if(ALARM_TIMER1 > 40000) //40s
				{
					ALARM_TIMER1 = 0;
					alarm_init(YELLOWLED_TWICE_SOUND);
				}
				if(FU_DND_TIMER > 36000000) //10h
				{
					ALARM_TIMER1 = 0;
					FU_DND_TIMER = 0;
					system_data.signal &= FAULT_DND_FLAG_MSK; //故障免打扰解除 10h
				}
			}













