#include "755LHA_Release_PT32L031.h"


FE_755LHA_EEPROM_TypeDef eeprom_data;
Release_typedef release;

//eeprom_data.marking
//bit7£ºOUTPUT
//bit6£ºNC
//bit5£ºNC
//bit4£ºNC
//bit3£ºNC
//bit2£ºNC
//bit1£ºNC
//bit0£ºÍøÂçÅäÖÃÎ»


/*
 * @brief Çå³ýRFÅäÍøÐÅÏ¢
 *
 */
void release_network(void)
{
	switch(release.step)
	{
		case 0:
			RED1_LED_ON;
		  RELEASE_TIMER = 0;
			release.step++;
			break;
		case 1:
			if(RELEASE_TIMER > 2999)
			{
				RED1_LED_OFF;
				RELEASE_TIMER = 0;
				release.step++;
			}
			else
			{
				if(TEST_KEY != 0)
				{
					RED1_LED_OFF;
					release.step = 0;
					release.mode = _idle;
				}
			}
			break;
		case 2:
			if(RELEASE_TIMER > 49)
			{
				if(TEST_KEY != 0)
				{
					release.step++;
				}
			}
			break;
		case 3:
			RED1_LED_ON;
			RELEASE_TIMER = 0;
			release.step++;
			break;
		case 4:
			if(RELEASE_TIMER > 49)
			{
				if(TEST_KEY == 0)
				{
					RELEASE_TIMER = 0;
					release.step++;
				}
				else
				{
					if(RELEASE_TIMER > 2999)
					{
						RED1_LED_OFF;
						release.step = 0;
						release.mode = _idle;
					}
				}
			}
			break;
		case 5:
			if(RELEASE_TIMER > 49)
			{
				if(TEST_KEY != 0)
				{
					RELEASE_TIMER = 0;
					release.step++;
				}
			}
			break;
		case 6:
			eeprom_data.network_id[0] = eeprom_data.id[0];
			eeprom_data.network_id[1] = eeprom_data.id[1];
			eeprom_data.network_id[2] = eeprom_data.id[2];
			eeprom_data.network_id[3] = eeprom_data.id[3];
		  eeprom_data.marking &= ~0x01;
		  fe_755LHA_write_eeprom_data(&eeprom_data);
		  system_data.masking &= ~ON_NET_FLAG_MSK;
		  release.step++;
			break;
		case 7:
			RED1_LED_ON;
		  RELEASE_TIMER = 0;
		  release.count++;
		  release.step++;
			break;
		case 8:
			if(RELEASE_TIMER > 99)
			{
				RED1_LED_OFF;
				release.step++;
			}
			break;
		case 9:
			if(RELEASE_TIMER > 199)
			{
				if(release.count > 25)
				{
					release.count = 0;
			    release.step = 0;
			    release.mode = _idle;
				}
				else
				{
					release.step -= 2;
				}
			}
			break;
	}
}



