#include "755LHA_RF_PT32L031.h"

typedef_pair pair;

/************************************************************************
** @brief  mac 回调函数 	
** @param  数组p,	 
** @retval no
************************************************************************/
void phy_callback(unsigned char *p, uint32_t l)
{
	if(l == 0x12)
	{
		if(p[0] == 0x0F) //配网包、自己作为主机
		{
			if(p[5] == 0xAA)
			{
				if(p[14] != 0xFF)
				{
					mem_data_copy(&pair.data[1], &p[1], 4);				
					pair.flag |= SLAVE_RESPONSE_FLAG_MSK;
				}
			}
			
			if(p[5] == 0xBB)//主机回码校验、自己作为从机
			{
				if(p[1] == eeprom_data.id[0])
				{
					if(p[2] == eeprom_data.id[1])
					{
						if(p[3] == eeprom_data.id[2])
						{
							if(p[4] == eeprom_data.id[3])
							{
								eeprom_data.network_id[0] = p[9];//同步码 -> 主机的ID
								eeprom_data.network_id[1] = p[8];
								eeprom_data.network_id[2] = p[7];
								eeprom_data.network_id[3] = p[6];
								eeprom_data.network_address = (p[10] << 8)+ p[11];
								pair.flag |= MASTER_RESPONSE_FLAG_MSK;
							}
						}
					}
				}
			}
		}
	}
}

/************************************************************************
** @brief  phy 回调函数 	
** @param  cmd	 
** @retval no
************************************************************************/
void mac_callback(uint32_t cmd)
{
	if(cmd == NET_TEST_ALARM)
	{
		NET_ALARM_TIMER = 0;
		system_data.signal |= DEVICE_NETWORK_TEST_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if(cmd == NET_FIND_ALARM)
	{
		if(system_data.state & ALARM_FLAG_MSK)
		{
			set_wire_connect(CLOSE_ALL);
			set_wireless_connect(NET_CLOSE_ALARM);
		}
		else
		{
			if(system_data.state & NETWORK_ALARM_FLAG_MSK)
			{
				system_data.signal &= ~DEVICE_NETWORK_ALARM_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
			if(system_data.masking & RECENT_ALARM_FLAG_MSK)
			{
				system_data.signal |= DEVICE_FIND_ALARM_FLAG_MSK;
				system_data.masking |= MESSAGE_FLAG_MSK;
			}
		}
	}
	else if(cmd == NET_FIRE_ALARM)
	{
		if((system_data.state & ALARM_FLAG_MSK) == 0)
		{
			NET_ALARM_TIMER = 0;
		  system_data.signal |= DEVICE_NETWORK_ALARM_FLAG_MSK;
		  system_data.masking |= MESSAGE_FLAG_MSK;
		}
	}
	else if(cmd == NET_CLOSE_ALARM)
	{
		system_data.signal &= ~DEVICE_NETWORK_ALARM_FLAG_MSK;
		system_data.masking |= MESSAGE_FLAG_MSK;
	}
	else if(cmd == NET_HUSH_ALARM)
	{
		system_data.masking |= MESSAGE_FLAG_MSK;
		
		if(system_data.state & NETWORK_ALARM_FLAG_MSK)
		{
			system_data.signal &= ~DEVICE_NETWORK_ALARM_FLAG_MSK;
		}
		else
		{
			system_data.signal |= DEVICE_HUSH_FLAG_MSK;
		}
	}
}

/************************************************************************
** @brief  发送数据整理	
** @param  	 
** @retval no
************************************************************************/
void explain_command(unsigned char state)
{
	pair.data[0] = 0x0F;//长度
	
	switch(state)
	{
		case NETWORK_APPLY:
		  mem_data_copy(&pair.data[1], &eeprom_data.id[0], 4);
			pair.data[5] = 0xAA;
			
			for(unsigned char i = 6;i < 14; i++)
			{
				pair.data[i] = 0;
			}
			
			pair.data[14] = 0x10;
			pair.data[15] = 0x10;
		break;
			
		case MASTER_ACK:
			//主机回复数据包
			pair.data[5] = 0xBB;
			pair.data[6] = eeprom_data.id[3];//主机sn 低位在前
			pair.data[7] = eeprom_data.id[2];
			pair.data[8] = eeprom_data.id[1];
			pair.data[9] = eeprom_data.id[0];

			//E2中的数据初始值 1
		  eeprom_data.network_address++;
		  pair.data[10] = eeprom_data.network_address >> 8;//网络编号高位
			pair.data[11] += eeprom_data.network_address & 0xFF;

			pair.data[12] = 0x0A;
			pair.data[13] = 0x12;
			pair.data[14] = 0x34;
			pair.data[15] = 0x78;
			break;
		
		case SLAVE_ACK:
		  mem_data_copy(&pair.data[1], &eeprom_data.id[0], 4);
			
			pair.data[5] = 0xAA;
			
			for(unsigned char i = 6;i < 16; i++)
			{
				pair.data[i] = 0xFF;
			}
			break;
	}
}

/************************************************************************
** @brief  RF配网	
** @param  	 
** @retval no
************************************************************************/
void rf_pairing_process_run(void)
{
	switch(pair.step)
	{
		case 0:
			pair.syncword[0] = 0x50;
			pair.syncword[1] = 0x00;
			pair.syncword[2] = 0xA0;
			pair.syncword[3] = 0x00;
		  pair.tx_mode = 0;
		  pair.count = 0;
		  pair.tx_power = PA_H10DBM;
		  explain_command(NETWORK_APPLY);
			pair.step++;
			break;
		case 1:
		  if(fe_set_phy_parameter(pair.syncword, phy_callback) == 0)
			{
				if(fe_set_755lha_mac_callback(mac_callback) == 0)
				{
					pair.step++;
				}				
			}
			break;
	  case 2:
			if(fe_set_phy_tx_parameter(pair.tx_mode, pair.tx_power) == 0)
			{
				pair.step++;
			}
			break;
		case 3:
			if(fe_phy_send_data(pair.data,16,30,10) == 0)
			{
				pair.step++;
			}
			break;
		case 4:
			if(fe_phy_receive_data(16,600,10) == 0)
			{
				pair.step++;
			}
			break;
		case 5:
			if(fe_get_phy_state() != 0xFFFFFFFF)
			{
				pair.count++;
				if(pair.flag & MASTER_RESPONSE_FLAG_MSK)//有主机已回复 进入从机模式
				{
					pair.flag &= ~MASTER_RESPONSE_FLAG_MSK;
					explain_command(SLAVE_ACK);
					pair.count = 0;
					pair.step++;
				}
				else
				{
					if(pair.count <= 2)
					{
						pair.step = 3;
					}
					else
					{
						pair.count = 0;
						eeprom_data.network_address = 0x01;
						pair.step = 11;
					}
				}
			}
			break;
		case 6:
			if(fe_phy_send_data(pair.data,16,30,10) == 0)
			{
				pair.count++;
				if(pair.count >= 3)
				{
					pair.count = 0;
					eeprom_data.marking |= 0x01;//配网位
					system_data.masking &= ~DECEIVE_MASTER_FLAG_MSK;//从机
					system_data.masking |= ON_NET_FLAG_MSK + MESSAGE_FLAG_MSK;
					pair.step += 3;
				}
				else
				{
					RF_TIMER = 0;
					pair.step++;
				}
				
			}
			break;
		case 7:
			if(RF_TIMER > 99)
			{
				pair.step--;
			}
			break;
			
		case 9:
			fe_755LHA_write_eeprom_data(&eeprom_data);
		  alarm_cfg(NET_WORK_SECCESS);
		  system_data.masking &= ~RF_PAIRINGF_FLAG_MSK;
			pair.count = 0;
			pair.step = 0;
			pair.mode = _idle;
			break;
		
		
		case 11:
			if(fe_phy_receive_data(16,30000,10) == 0)//没有主机回复 进入主机模式
			{
				RED1_LED_ON;
				pair.step++;
			}
			break;
		case 12:
			if(fe_get_phy_state() != 0xFFFFFFFF)
			{
				if(pair.flag & SLAVE_RESPONSE_FLAG_MSK)
				{
					pair.flag &= ~SLAVE_RESPONSE_FLAG_MSK;
					explain_command(MASTER_ACK);
					pair.step++;
				}
				else
				{
					if(pair.flag & SLAVE_PAIRING_SUCCEED_FLAG_MSK)
					{
						fe_755LHA_write_eeprom_data(&eeprom_data);
						pair.flag &= ~SLAVE_PAIRING_SUCCEED_FLAG_MSK;
						system_data.masking |= DECEIVE_MASTER_FLAG_MSK + ON_NET_FLAG_MSK + MESSAGE_FLAG_MSK;
					}
					RED1_LED_OFF;
					system_data.masking &= ~RF_PAIRINGF_FLAG_MSK;
					pair.count = 0;
					pair.step = 0;
					pair.mode = _idle;
				}
			}
			break;
		case 13:
			if(fe_phy_send_data(pair.data,16,30,10) == 0)
			{
				eeprom_data.marking |= 0x01;
				eeprom_data.address = 0x01;
				eeprom_data.network_id[0] = eeprom_data.id[0];//同步码 -> 主机的ID
			  eeprom_data.network_id[1] = eeprom_data.id[1];
			  eeprom_data.network_id[2] = eeprom_data.id[2];
			  eeprom_data.network_id[3] = eeprom_data.id[3];
				pair.flag |= SLAVE_PAIRING_SUCCEED_FLAG_MSK;
				system_data.masking |= ON_NET_FLAG_MSK;
				pair.step++;
			}
			break;
		case 14:
			if(fe_get_phy_state() != 0xFFFFFFFF)
			{
				RED1_LED_OFF;
				alarm_cfg(NET_WORK_SECCESS);
				pair.step++;
			}
			break;
		case 15:
			if(red_led.mode == _idle)
			{
				pair.step = 11;
			}
			break;
			
		case 20:
			if(fe_phy_quit() == 0)
			{
				RED1_LED_OFF;
				if(pair.flag & SLAVE_PAIRING_SUCCEED_FLAG_MSK)
				{
					pair.flag &= ~SLAVE_PAIRING_SUCCEED_FLAG_MSK;
					fe_755LHA_write_eeprom_data(&eeprom_data);
					system_data.masking |= ON_NET_FLAG_MSK + MESSAGE_FLAG_MSK;
				}
				system_data.masking &= ~RF_PAIRINGF_FLAG_MSK;
				pair.count = 0;
	      pair.step = 0;
	      pair.mode = _idle;
			}
			break;
	}
}


