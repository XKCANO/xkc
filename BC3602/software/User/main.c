#include "pt32x031.h"
#include "FE_755LHA_CFG.h"
#include "FE_755LHA_System_PT32L031.h"
#include "FE_755LHA_Timer_PT32L031.h"

#include "FE_755LHA_PT32L031_CFG.h"
#include "FE_TIMER_PT32L031.h"
//#include "FE_755LHA_EEPROM_PT32L031.h"
#include "FE_SPI_PT32L031.h"
#include "FE_PHY_BC3602.h"
#include "FE_755LHA_UART_PT32L031.h"

uint8_t buffer[4];
uint32_t step;

uint32_t system_masking = 0;

#define			SYSTEM_INITIALIZE_FLAG_POS       0
#define			SYSTEM_INITIALIZE_FLAG_MSK      (1UL	<< SYSTEM_INITIALIZE_FLAG_POS)

#define			SYSTEM_TEST_MODE_FLAG_POS        1
#define			SYSTEM_TEST_MODE_FLAG_MSK       (1UL	<< SYSTEM_TEST_MODE_FLAG_POS)

//PB3 -> SCK 
#define     SCK_PIN		            0x0008
#define     SCK_KEY		           (CMSDK_PB->DATA & SCK_PIN)

//PB7 -> 黄灯
#define     YELLOW_PIN		          0x0080
#define     YELLOW_LED_ON           CMSDK_PB->DATAOUT &= ~YELLOW_PIN
#define     YELLOW_LED_OFF          CMSDK_PB->DATAOUT |= YELLOW_PIN

//PA7 -> VOP
#define     VH_PIN                  0x0080
#define     VH_ON                   CMSDK_PA->DATAOUT |= VH_PIN
#define     VH_OFF                  CMSDK_PA->DATAOUT &= ~VH_PIN

//PA6 -> HTS
#define     HTS_PIN                 0x0040
#define     HTS_IN_ON		            CMSDK_PA->OUTENABLECLR |= HTS_PIN
#define     HTS_IN_OFF	            CMSDK_PA->OUTENABLESET |= HTS_PIN
#define     HTS_ANA_ON              CMSDK_PA->ANASET |= HTS_PIN
#define     HTS_ANA_OFF             CMSDK_PA->ANACLR |= HTS_PIN

// BL_EN --> PA0
#define     BL_PIN                  0x0001
#define     BL_ON                   CMSDK_PA->DATAOUT |= BL_PIN
#define     BL_OFF                  CMSDK_PA->DATAOUT &= ~BL_PIN

// BTS --> PA1
#define     BTS_IN_ON		            CMSDK_PA->OUTENABLECLR |= (1 << 1)
#define     BTS_IN_OFF	            CMSDK_PA->OUTENABLESET |= (1 << 1)
#define     BTS_ANA_ON              CMSDK_PA->ANASET |= (1 << 1)
#define     BTS_ANA_OFF             CMSDK_PA->ANACLR |= (1 << 1)


/*
** Main
*/
int main(void)
{
	fe_clear_ram();
	sys_clock_init();
	sys_gpio_init();
	
	fe_set_system_tick_timer();
	
	set_timer3();
	
	system_masking |= SYSTEM_INITIALIZE_FLAG_MSK;
	
	while(1)
	{
		if(system_masking & SYSTEM_INITIALIZE_FLAG_MSK)
		{
			if(Timer3.t[1] >= 100)
			{
				if(SCK_KEY)
				{
					spi_enable_cfg(0);
					
					system_masking &= ~SYSTEM_INITIALIZE_FLAG_MSK;
				}
				else
				{
          CMSDK_PB->DATAOUT |= 0x40;
          
          //上拉失能
	        CMSDK_PA->PULLUPCLR |= 0xFFFF;
          //下拉失能
	        CMSDK_PA->PULLDOWNCLR |= 0xFFFF;
          //上拉失能
	        CMSDK_PB->PULLUPCLR |= 0xFFFF;
          //下拉失能
	        CMSDK_PB->PULLDOWNCLR |= 0xFFFF;
          
          SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
          __NOP();
          __WFI();
          __NOP();
				}
			}
		}
		else
		{
			switch(step)
			{
				case 0:
					if(Timer3.t[0] >= 1000)
					{
						CMSDK_PB->DATAOUT |= 0x40;
						step++;
					}
					break;
				case 1:
					if(fe_phy_send_data() == 0)
					{
						step++;
					}
					break;
				case 2:
					if((CMSDK_PA->DATA & 0x04) == 0)
					{
						CMSDK_PB->DATAOUT &= ~0x40;
						step++;
					}
					break;
				case 3:
					if((CMSDK_PA->DATA & 0x04) != 0)
					{
						CMSDK_PB->DATAOUT |= 0x40;
						step++;
					}
					break;
				case 4:
					if(fe_phy_quit() == 0)
					{
						step++;
					}
					break;
				case 5:
					if(fe_phy_receive_data() == 0)
					{
						Timer3.t[0] = 0;
						step++;
					}
					break;
				case 6:
					if((CMSDK_PA->DATA & 0x04) == 0)
					{
						CMSDK_PB->DATAOUT &= ~0x40;
						step++;
					}
					else
					{
						if(Timer3.t[0] >= 19)
						{
							spi_enable_cfg(1);
							step++;
						}
					}
					break;
				case 7:
					if((CMSDK_PA->DATA & 0x04) == 0)
					{
						step++;
					}
					break;
				case 8:
					if((CMSDK_PA->DATA & 0x04) != 0)
					{
						CMSDK_PB->DATAOUT |= 0x40;
						step++;
					}
					break;
				case 9:
					if(fe_phy_quit() == 0)
					{
						Timer3.t[0] = 0;
						step = 12;
					}
					break;
					
				case 12:
					if(Timer3.t[0] >= 100)
					{
						step = 1;
						spi_enable_cfg(0);
					}
					break; 
			}
      
      fe_phy_process_run();

		  fe_spi_process_run();

		  fe_uart_process_run(); 
		}
		
		fe_check_system_tick_timer();
		check_timer3();
	}
}

/* --------------------------------------------------------------------------- */


