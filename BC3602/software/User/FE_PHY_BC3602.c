/*
**
*/
#include "FE_PHY_BC3602.h"
#include <stdio.h>
#include "PT32x031.h"
#include "FE_HEAT_CFG.h"
#include "FE_IO.h"
#include "FE_MATH.h"
#include "BC3602reg.h"
#include "FE_SPI_PT32L031.h"
/* --------------------------------------------------------------------------- */
/* BC3602 Common & Bank 0 register */
enum 
{
   CFG1 = 0x00,           
   RC1,               
   IRQ1,                
   IRQ2,             
   IRQ3,            
   IO1 = 0x06,      
   IO2,             
   IO3,            
   FIFO1,             
   FIFO2,               
   PKT1,           
   PKT2,    
   PKT3,    
   PKT4,    
   PKT5,  
   PKT6,
   PKT7,
   PKT8,
   PKT9,
   MOD1 = 0x14,   
   MOD2,
   MOD3,
   DM1 = 0x17,
   DM2,
   DM3,
   DM4,
   DM5,
	 DM6,
	 DM7,
   DM8 = 0x1E,
   OM = 0x20,
   SX1 = 0x22,   
   SX2,   
   SX3,   
   SX4,   
   STA1,
   RSSI2 = 0x28,
   RSSI3,
   RSSI4,
   ATR1,
   ATR2,
   ATR3,
   ATR4,
   ATR5,
   ATR6,
   ATR7,
   ATR8,
	 ATR9,
	 ATR10,
	 ATR11,
   XO1 = 0x3C,
   XO2,
   XO3,
   TX2
};

/* BC3602 Bank 1 register */
enum 
{
   AGC2 = 0x21,
   AGC3,
   AGC4,
   AGC5,
   AGC6,
   AGC7,
   FCF1 = 0x2C,
   FCF2,
   FCF3,
   FCF4,
   FCF5,
   FCF6,
   FCF7,
   FCF8,
   FCF9,
   FCF10,
   FCF11,
   FCF12,
   FCF13,
   FCF14,
   FCF15,
   FCF16,
   FCF17,
   FCF18,
   FCF19,   
};

/* BC3602 Bank 2 register */
enum
{
	RSV0 = 0x21,
	RSV1 = 0x26,
	RSV2,
	RSV3,
	RSV4,
	RSV5 = 0x2D,
	RSV6,
	RSV7,
	RSV8 = 0x30,
	RSV9,
	RSV10 = 0x34,
	RSV11 = 0x3A,
};

/****************** Bit definition for IRQ_STATUS_REGS register  ***********************/
#define  FIFOLTIF  ((unsigned char)0x20)
/****************** Bit definition for OPERATION_CTL_REGS register  ********************/
#define  ACAL_EN  ((unsigned char)0x08)
/* --------------------------------------------------------------------------- */
/*
 *Deviation:  19.042969K
 *Datarate:   38.383484KBaud
 *Modulation: GFSK
 *RF:         868.082855MHz
 *Channel:    199.951172KHz
 *RX:         101.562500KHz
 */
/*
 *Deviation:         19.042969K
 *Datarate:          38.383484KBaud
 *Modulation:        GFSK
 *RF:                433.082733MHz
 *Channel Bandwidth: 199.951172KHz
 *RX:                101.562500KHz
 */
/*
dBm:0,   5,   10,  13
  { 0x06,0x08,0x0B,0x0F } //315
  { 0x04,0x06,0x09,0x0D } //433
  { 0x04,0x06,0x09,0x0D } //470         
  { 0x06,0x08,0x0B,0x0E } //868      
  { 0x06,0x08,0x0B,0x0E } //915
 */
const unsigned char PA_Power_Table[] =
{
	0x04,0x06,0x09,0x0D
};

const unsigned char Public_Register[][2] = 
{
	{CFG1,0x40},
  {IRQ1,0x09},{IRQ2,0x00},//{IRQ2,0x04},
  {IO1,0x41},{IO2,0x00},{IO3,0xBF},
  {FIFO1,0x00},{FIFO2,0x01},
  {PKT1,0x07}, //preanble:8 bytes
	
	//TRAILER_EN:0
	//WHTFMT:0 -->P(X)=X7+X6+X5+X4+1
	//       1 -->P(X)=X7+X4+1(PN7)
	//SYNCLEN:01(4 bytes of sync_word)
	//RXPMLEN:10(2 bytes of preamble)
  {PKT2,0x16}, 
	
  {PKT3,0x00},//MCH_EN:0(manchester); CRC_EN:0; CRCFMT:0(CCITT)
  {PKT4,0x7F},//WHT_EN:0
  {PKT7,0x38},//DLY_RXS:7-->100us
	
  {MOD1,0x31}, //data rate 10.204KHz = 16M/32/49
  {MOD2,0x60},{MOD3,0x66}, //199.951KHz = 16M * 1638(0x666) / 131072
  //DMCLK = 800KHz
  {DM1,0x09},{DM2,0xC9},{DM3,0x8D},{DM4,0x08},{DM5,0x06},{DM6,0x40},{DM7,0x66},{DM8,0x0A},//CFO:100KHz
	
	//D_N = 433.4216/16 = 27.08885 = 27(0x1B)
	//D_K = 0.08885 * 1048576 = 93165(0x016BED)	
	//{SX1,0x1B}, {SX2,0xED}, {SX3,0x6B}, {SX4,0x01},
	
	//D_N = 433.42/16 = 27.08875 = 27(0x1B)
	//D_K = 0.08875 * 1048576 = 93061(0x016B85)
	//{SX1,0x1B}, {SX2,0x85}, {SX3,0x6B}, {SX4,0x01},
	
	//D_N = 433.418/16 = 27.088625 = 27(0x1B)
	//D_K = 0.088625 * 1048576 = 92930(0x016B02)
	{SX1,0x1B}, {SX2,0x02}, {SX3,0x6B}, {SX4,0x01},
	{ATR1,0x0},
  {XO1,0x0C},
  {XO2,0x03},
	{TX2,0x09}
};

const unsigned char Bank1_Register[][2] = 
{
	{AGC2,0x40},{AGC3,0x24},{AGC4,0x11},{AGC5,0x0},{AGC7,0x30},
  {FCF1,0x16},
  {FCF2,0x14},{FCF3,0x00}, //frequency deviation:5KHz
  {FCF4,0x00},{FCF5,0x00},
	{FCF6,0x00},{FCF7,0x00},
  {FCF8,0x10},{FCF9,0x03},
	{FCF10,0x00},{FCF11,0x00},
  {FCF12,0x00},{FCF13,0x00},
	{FCF14,0x00},{FCF15,0x00},
  {FCF16,0x00},{FCF17,0x00},
	{FCF18,0x00},{FCF19,0x00}
};

const unsigned char Bank2_Register[][2] =
{  
	{RSV0,0x8F},{RSV1,0x03},{RSV2,0x88},{RSV3,0xAA},{RSV4,0x80},{RSV5,0x16},
	{RSV6,0x64},{RSV7,0x44},{RSV8,0x00},{RSV9,0x64},{RSV10,0xBC},{RSV11,0x94}
}; 

//const unsigned char Public_Register[][2] = 
//{
//	{CFG1,0x40},
//	{IRQ1,0x01},{IRQ2,0x04},
//	{IO1,0x41},{IO2,0x00},{IO3,0xBF},
//	{FIFO1,0x00},{FIFO2,0x01},
//	{PKT1,0x03}, //preanble:4bytes
//	
//	//TRAILER_EN:0
//	//syncword:4bytes
//	{PKT2,0x06}, 
//	
//	{PKT3,0x20},//MCH_EN:0(manchester); CRC_EN:1; CRCFMT:0(CCITT)
//	{PKT4,0x36},
//	{PKT7,0x38},//DLY_RXS:7-->100us
//	
//	{MOD1,0x31}, //data rate 10.204KHz = 16M/32/49
//	{MOD2,0x60},{MOD3,0x66}, //RX filter bandwidth 199.951KHz = 16M * 1638(0x666) / 131072
//	//DMCLK = 800KHz
//	{DM1,0x09},{DM2,0xC9},{DM3,0xE6},{DM4,0x48},{DM5,0x1A},{DM8,0x1A},
//	
//	//D_N = 433.42/16 = 27.08875 = 27(0x1B)
//	//D_K = 0.08875 * 1048576 = 93061(0x016B85)
//	{SX1,0x1B}, {SX2,0x85}, {SX3,0x6B}, {SX4,0x01},
//	{ATR1,0x0},
//	{XO1,0x1B}, //12pF
//	{XO2,0x03},
//	{TX2,0x09}
//};

//const unsigned char Bank1_Register[][2] = 
//{
//	{AGC2,0x40},{AGC3,0x24},{AGC4,0x11},{AGC5,0x0},{AGC7,0x30},
//	{FCF1,0x16},
//	{FCF2,0xA4},{FCF3,0x00}, //frequency deviation:40KHz
//	{FCF4,0x00},{FCF5,0x00},
//	{FCF6,0x00},{FCF7,0x00},
//	{FCF8,0x10},{FCF9,0x03},
//	{FCF10,0x00},{FCF11,0x00},
//	{FCF12,0x00},{FCF13,0x00},
//	{FCF14,0x00},{FCF15,0x00},
//	{FCF16,0x00},{FCF17,0x00},
//	{FCF18,0x00},{FCF19,0x00}
//};
/* --------------------------------------------------------------------------- */
#define  fe_phy_idle  0x0
#define  fe_phy_tx_mode  0x3
#define  fe_phy_rx_mode  0x5
#define  fe_phy_end  0x10
/* --------------------------------------------------------------------------- */
//masking
#define  BC3602_INITIAL_FLAG_POS  0
#define  BC3602_INITIAL_FLAG_MSK  (1UL << BC3602_INITIAL_FLAG_POS)

#define  DEEP_SLEEP_FLAG_POS  1
#define  DEEP_SLEEP_FLAG_MSK  (1UL << DEEP_SLEEP_FLAG_POS)

#define  PREAMBLE_TX_FLAG_POS  2
#define  PREAMBLE_TX_FLAG_MSK  (1UL << PREAMBLE_TX_FLAG_POS)

//#define  INFINITE_FIFO_MODE_POS  2
//#define  INFINITE_FIFO_MODE_MSK  (1UL << INFINITE_FIFO_MODE_POS)

//#define  PAYLOAD_LENGTH_ENABLE_POS  3
//#define  PAYLOAD_LENGTH_ENABLE_MSK  (1UL << PAYLOAD_LENGTH_ENABLE_POS)

#define  RX_EVENT_UPDATE_FLAG_POS  4
#define  RX_EVENT_UPDATE_FLAG_MSK  (1UL << RX_EVENT_UPDATE_FLAG_POS)

/* --------------------------------------------------------------------------- */
#define  PHY_TIMER  Timer.t[1]
/* --------------------------------------------------------------------------- */
#define  PHY_TX_END_STEP  17
#define  PHY_RX_END_STEP  18
/* --------------------------------------------------------------------------- */
#define  PHY_RSSI_DETECT_TIME  5
/* --------------------------------------------------------------------------- */
#define  SYNC_WORD_SIZE  4
#define  PHY_DATA_SIZE  32
#define  PHY_BUFFER_SIZE  36
/* --------------------------------------------------------------------------- */
typedef struct
{
	FE_PHY_CALLBACK cb;
	
	uint32_t work_time;
	uint32_t idle_time;
	uint32_t t;
	
	unsigned char masking;
	unsigned char pos;
	
	unsigned char rssi;
//	unsigned char carry_rssi;
	unsigned char sync_rssi;
	
	unsigned char sync_word[SYNC_WORD_SIZE];
	unsigned char data[PHY_DATA_SIZE];
  unsigned char buffer[PHY_BUFFER_SIZE];

	unsigned char preamble_length;
	unsigned char length;
//	unsigned char channel;
	unsigned char pa_power;

	unsigned char initial_step;
	unsigned char wake_step;
	unsigned char sleep_step;
	
  unsigned char step;
  unsigned char mode;
}FE_PHY_TypeDef;
/* --------------------------------------------------------------------------- */
FE_PHY_TypeDef phy;
/* --------------------------------------------------------------------------- */

/*
 * @brief 
 */
void bc3602_configure_process_run(void)
{
	switch(phy.initial_step)
	{
		case 0:
			phy.buffer[0] = LIGHT_SLEEP_CMD;
		  phy.initial_step++;
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.initial_step++;
			}
			break;
		case 2:
			if(fe_get_spi_state() == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + Public_Register[phy.pos][0];
				phy.buffer[1] = Public_Register[phy.pos][1];
				phy.initial_step++;
			}
			break;
		case 3:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.pos++;
			  if(phy.pos < 32)
			  {
				  phy.initial_step--;
			  }
			  else
			  {
				  phy.buffer[0] = REGS_BANK_CMD + REGS_BANK1;
				  phy.initial_step++;
				}
			}
			break;
		case 4:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.pos = 0;
				phy.initial_step++;
			}
			break;
		case 5:
			if(fe_get_spi_state() == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + Bank1_Register[phy.pos][0];
				phy.buffer[1] = Bank1_Register[phy.pos][1];
				phy.initial_step++;
			}
			break;
		case 6:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.pos++;
				if(phy.pos < 24)
			  {
				  phy.initial_step--;
			  }
			  else
			  {
				  phy.buffer[0] = REGS_BANK_CMD + REGS_BANK2;
				  phy.initial_step++;
				}
			}
			break;
		case 7:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.pos = 0;
				phy.initial_step++;
			}
			break;
		case 8:
			if(fe_get_spi_state() == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + Bank2_Register[phy.pos][0];
				phy.buffer[1] = Bank2_Register[phy.pos][1];
				phy.initial_step++;
			}
			break;
		case 9:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.pos++;
				if(phy.pos < 12)
			  {
				  phy.initial_step--;
			  }
			  else
			  {
					phy.initial_step++;
				}
			}
			break;
		case 10:
			if(fe_get_spi_state() == 0)
			{
				phy.initial_step = 0;
				phy.idle_time = 0;
				phy.masking |= BC3602_INITIAL_FLAG_MSK;
			}
			break;
	}
}

/*
 * @brief 
 */
void phy_wake_up_process_run(void)
{
	switch(phy.wake_step)
	{
		case 0:
			if((phy.masking & BC3602_INITIAL_FLAG_MSK) != 0)
			{
			  phy.masking &= ~DEEP_SLEEP_FLAG_MSK;
				phy.sleep_step = 0;
			  phy.buffer[0] = LIGHT_SLEEP_CMD;
		    phy.wake_step++;
			}
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
			  phy.buffer[0] = REGS_BANK_CMD;
		    phy.wake_step++;
			}
			break;
		case 2:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + OPERATION_CTL_REGS;
			  phy.buffer[1] = 0x28;
				phy.wake_step++;
			}
			break;
		case 3:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = READ_REGS_CMD + OPERATION_CTL_REGS;
				phy.wake_step++;
			}
			break;
		case 4:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.wake_step++;
			}
			break;
		case 5:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 2);
				if((phy.buffer[1] & ACAL_EN) == 0)
				{
					phy.wake_step = 0;
					phy.mode &= 0xFE;
				}
				else
				{
					phy.buffer[0] = READ_REGS_CMD + OPERATION_CTL_REGS;
					phy.wake_step--;
				}
			}
			break;
	}
}

/*
 * @brief 
 */
void phy_deep_sleep_process_run(void)
{
	switch(phy.sleep_step)
	{
		case 0:
			if((phy.masking & BC3602_INITIAL_FLAG_MSK) != 0)
			{
			  if(phy.mode == fe_phy_idle)
			  {
					if(PHY_TIMER >= phy.idle_time)
					{
					  phy.buffer[0] = DEEP_SLEEP_CMD;
		        phy.sleep_step++;
					}
			  }
		  }
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.sleep_step++;
			}
			break;
		case 2:
			if(fe_enter_spi_sleep() == 0)
			{
			  phy.sleep_step = 0;
				phy.masking |= DEEP_SLEEP_FLAG_MSK;
			}
			break;
	}
}

/*
 * @brief
 */
void get_tx_data(void)
{
	uint32_t i;
	i = 0;
	do{
		phy.data[i] = 0xAA;
		i++;
	}while(i < PHY_DATA_SIZE);
}

/*
 * @brief
 */
void phy_transmitter_process_run(void)
{
	switch(phy.step)
	{
		case 0:
			if((phy.mode & 0x1) == 0)
			{
//				mem_data_copy(phy.sync_word, Rom.network_id, 4);
				get_tx_data();
				
			  phy.buffer[0] = WRITE_REGS_CMD + FIFO2_CTL_REGS;
				phy.buffer[1] = 0x0F;
				phy.step++;
			}
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + TX_POWER_CTL_REGS;
				phy.buffer[1] = PA_Power_Table[PA_H13DBM];
				phy.step++;
			}
			break;
		case 2:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + PREAMBLE_LENG_REGS;
				phy.buffer[1] = 255;
				phy.step++;
			}
			break;
		case 3:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = WRITE_SYNCWORD_CMD;
		    mem_data_copy(&phy.buffer[1], phy.sync_word, 4);
		    phy.step++;
			}
			break;
		case 4:
			if(fe_spi_write(phy.buffer, 5) == 0)
			{
				phy.buffer[0] = REST_TX_POS_CMD;
				phy.step++;
			}
			break;
		case 5:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = WRITE_FIFO_CMD;
			  mem_data_copy(&phy.buffer[1], phy.data, 32);
			  phy.step++;
			}
			break;
		case 6:
			if(fe_spi_write(phy.buffer, 33) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + IRQ_STATUS_REGS;
				phy.buffer[1] = 0;
				phy.step++;
			}
			break;
		case 7:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = TX_MODE_CMD;
				PHY_TIMER = 0;
			  phy.step++;
			}
			break;
		case 8:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = READ_REGS_CMD + MODE_STATUS_REGS;
				phy.step++;
			}
			break;
		case 9:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step++;
			}
			break;
		case 10:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 2);
				if((phy.buffer[1] & 0x7) == _STA_TX_MODE_)
				{
					phy.step++;
				}
				else
				{
					if(PHY_TIMER < 5)
					{
						phy.buffer[0] = READ_REGS_CMD + MODE_STATUS_REGS;
				    phy.step--;
					}
					else
					{
						phy.buffer[0] = LIGHT_SLEEP_CMD;
						phy.step = PHY_TX_END_STEP - 1;
					}
				}
			}
			break;
		case 11:
			phy.buffer[0] = READ_REGS_CMD + IRQ_STATUS_REGS;
			phy.step++;
		  break;
		case 12:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step++;
			}
			break;
		case 13:
			if(fe_get_spi_state() == 0)
			{
				if((phy.mode & fe_phy_end) != 0)
				{
					phy.buffer[0] = LIGHT_SLEEP_CMD;
		      phy.step = PHY_TX_END_STEP - 1;
				}
				else
				{
					fe_spi_read(phy.buffer, 2);
					if((phy.buffer[1] & _TX_RX_MEG_IRQ_) != 0)
					{
						CMSDK_PA->DATAOUT &= ~0x08;
						phy.buffer[0] = WRITE_FIFO_CMD;
						mem_data_copy(&phy.buffer[1], phy.data, 32);
						phy.step++;
					}
					else
					{
						phy.step -= 2;
					}
				}
		  }
			break;
		case 14:
			if(fe_spi_write(phy.buffer, 33) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + IRQ_STATUS_REGS;
				phy.buffer[1] = 0;
				phy.step++;
			}
			break;
    case 15:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				CMSDK_PA->DATAOUT |= 0x08;
				phy.step -= 4;
			}
      break;
		case 16:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.step++;
			}
			break;
		case 17:
			if(fe_get_spi_state() == 0)
			{
			  phy.step = 0;
				PHY_TIMER = 0; //sleep_time
				phy.idle_time = 10;
		    phy.mode &= 0xED;
			}
			break;
	}
}

/*
 * @brief 
 */
void phy_receiver_process_run(void)
{
	switch(phy.step)
	{
		case 0:
			if((phy.mode & 0x1) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + GIO34_CTL_REGS;
			  phy.buffer[1] = 0x04;
		    phy.step++;
			}
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + FIFO2_CTL_REGS;
				phy.buffer[1] = 0x0F;
				phy.step++;
			}
			break;
		case 2:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = WRITE_SYNCWORD_CMD;
		    mem_data_copy(&phy.buffer[1], phy.sync_word, 4);
		    phy.step++;
			}
			break;
		case 3:
			if(fe_spi_write(phy.buffer, 5) == 0)
			{
				phy.buffer[0] = REST_RX_POS_CMD;
				phy.step++;
			}
			break;
		case 4:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = WRITE_REGS_CMD + IRQ_STATUS_REGS;
				phy.buffer[1] = 0;
				phy.step++;
			}
			break;
		case 5:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.buffer[0] = RX_MODE_CMD;
				PHY_TIMER = 0;
			  phy.step++;
			}
			break;
		case 6:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = READ_REGS_CMD + MODE_STATUS_REGS;
				phy.step++;
			}
			break;
		case 7:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step++;
			}
			break;
		case 8:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 2);
				if((phy.buffer[1] & 0x7) == _STA_RX_MODE_)
				{
					PHY_TIMER = 0;
					phy.t = PHY_RSSI_DETECT_TIME;
					phy.step++;
				}
				else
				{
					if(PHY_TIMER < 5)
					{
						phy.buffer[0] = READ_REGS_CMD + MODE_STATUS_REGS;
				    phy.step--;
					}
					else
					{
						phy.buffer[0] = LIGHT_SLEEP_CMD;
						phy.step = PHY_RX_END_STEP - 1;
					}
				}
			}
			break;
		case 9:
			if((phy.mode & fe_phy_end) != 0)
			{
				phy.buffer[0] = LIGHT_SLEEP_CMD;
				phy.step = PHY_RX_END_STEP - 1;
			}
			else
			{
				if(PHY_TIMER >= phy.t)
				{
					phy.t += PHY_RSSI_DETECT_TIME;
					phy.buffer[0] = READ_REGS_CMD + RSSI_VALUE_REGS;
					phy.step++;
				}
			}
			break;
		case 10:
			if(fe_spi_write(phy.buffer, 3) == 0)
			{
				phy.step++;
			}
			break;
		case 11:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 3);
				phy.rssi = phy.buffer[1];
				phy.sync_rssi = phy.buffer[2];
				
			  phy.buffer[0] = READ_REGS_CMD + IRQ_STATUS_REGS;
		    phy.step++;
			}
		  break;
		case 12:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step++;
			}
			break;
		case 13:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 2);
				if((phy.buffer[1] & _TX_RX_MEG_IRQ_) != 0)
				{
					CMSDK_PB->DATAOUT &= ~0x80;
					phy.buffer[0] = READ_FIFO_CMD;
					phy.step++;
				}
				else
				{
					phy.step -= 4;
				}
		  }
			break;
		case 14:
			if(fe_spi_write(phy.buffer, 33) == 0)
			{
				phy.step++;
			}
			break;
		case 15:
			if(fe_get_spi_state() == 0)
			{
				CMSDK_PB->DATAOUT |= 0x80;
				phy.buffer[0] = WRITE_REGS_CMD + IRQ_STATUS_REGS;
				phy.buffer[1] = 0;
				phy.step++;
			}
			break;
		case 16:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step -= 7;
			}
			break;
		case 17:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.step++;
			}
			break;
		case 18:
			if(fe_get_spi_state() == 0)
			{
			  phy.step = 0;
				PHY_TIMER = 0; //sleep_time
				phy.idle_time = 10;
		    phy.mode &= 0xEB;
			}
			break;
	}
}

/*
 * @brief 
 */
void phy_moniting_process_run(void)
{
	switch(phy.step)
	{
		case 0:
			if((phy.masking & BC3602_INITIAL_FLAG_MSK) != 0)
			{
			  phy.masking &= ~DEEP_SLEEP_FLAG_MSK;
				phy.sleep_step = 0;
			  phy.buffer[0] = LIGHT_SLEEP_CMD;
		    phy.step++;
			}
			break;
		case 1:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.buffer[0] = RX_MODE_CMD;
			  phy.step++;
			}
			break;
		case 2:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
			  phy.buffer[0] = REGS_BANK_CMD;
		    phy.step++;
			}
			break;
		case 3:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
				phy.step++;
			}
			break;
		case 4:
			if(fe_get_spi_state() == 0)
			{
				PHY_TIMER = 0;
				phy.step++;
			}
			break;
		case 5:
			if(PHY_TIMER >= PHY_RSSI_DETECT_TIME)
			{
				phy.buffer[0] = READ_REGS_CMD + RSSI_VALUE_REGS;
				phy.step++;
			}
			break;
		case 6:
			if(fe_spi_write(phy.buffer, 2) == 0)
			{
				phy.step++;
			}
			break;
		case 7:
			if(fe_get_spi_state() == 0)
			{
				fe_spi_read(phy.buffer, 2);
				phy.rssi = phy.buffer[1];
				phy.buffer[0] = LIGHT_SLEEP_CMD;
		    phy.step++;
			}
		  break;
		case 8:
			if(fe_spi_write(phy.buffer, 1) == 0)
			{
		    phy.step++;
			}
			break;
		case 9:
			if(fe_get_spi_state() == 0)
			{
			  phy.step = 0;
				PHY_TIMER = 0; //sleep_time
		    phy.mode &= 0xE7;
			}
			break;
	}
}

/*
 * @brief PHY主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 * 
 */
void fe_phy_process_run(void)
{
	if((phy.masking & BC3602_INITIAL_FLAG_MSK) == 0)
	{
		bc3602_configure_process_run();
	}
	
	if(phy.mode & 0x01)
	{
		phy_wake_up_process_run();
	}
	
	if(phy.mode & 0x02)
	{
		phy_transmitter_process_run();
	}
	
	if(phy.mode & 0x04)
	{
		phy_receiver_process_run();
	}
	
	if(phy.mode & 0x08)
	{
		phy_moniting_process_run();
	}
	
	if((phy.masking & DEEP_SLEEP_FLAG_MSK) == 0)
	{
		phy_deep_sleep_process_run();
	}
}

/*
 * @brief 查询PHY状态
 *
 * @param [in]:无
 *
 * @return:
 *   =0:空闲
 *   =1:深度睡眠
 *   =0xFFFFFFFF:忙
 *
 * @details
 *
 */
uint32_t fe_get_phy_state(void)
{
	if((phy.masking & BC3602_INITIAL_FLAG_MSK) == 0)
	{
		return 0xFFFFFFFF;
	}
	else if((phy.masking & DEEP_SLEEP_FLAG_MSK) != 0)
	{
		return 1;
	}
	else if(phy.mode == fe_phy_idle)
	{
		return 0;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

/*
 * @brief 获取RSSI
 *
 * @param [in] 无
 *
 * @return: rssi
 *    
 *
 * @details
 */
uint32_t fe_get_rssi(uint32_t _mode)
{
	if(_mode == 0)
	{
	  return (uint32_t)phy.rssi;
	}
	else
	{
		return (uint32_t)phy.sync_rssi;
	}
}

/*
 * @brief 获取接收到的数据
 *
 * @param [in] p: 数据首地址
 * @param [in] l: 数据长度
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details
 */
//uint32_t fe_get_phy_data(unsigned char *p, uint32_t l)
//{
//	if(l > PHY_DATA_SIZE)
//	{
//		return 0;
//	}
//	if((phy.masking & RX_EVENT_UPDATE_FLAG_MSK) != 0)
//	{
//		phy.masking &= ~RX_EVENT_UPDATE_FLAG_MSK;
//		mem_data_copy(p, phy.data, l);
//		return l;
//	}
//	else
//	{
//		return 0;
//	}
//}

/*
 * @brief 设置工作参数
 *
 * @param [in] tx_mode : 数据帧模式; 0:正常模式
 * @param [in] tx_power: 发射功率
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details
 */
uint32_t fe_set_phy_tx_parameter(uint32_t tx_mode, uint32_t tx_power)
{
	if(phy.mode == fe_phy_idle)
	{
		switch(tx_mode)
		{
			case 0:
				phy.preamble_length = 7;
			  phy.masking &= ~PREAMBLE_TX_FLAG_MSK;
				break;
			case 1:
				phy.preamble_length = 63;
			  phy.masking &= ~PREAMBLE_TX_FLAG_MSK;
				break;
			case 2:
				phy.preamble_length = 255;
			  phy.masking &= ~PREAMBLE_TX_FLAG_MSK;
				break;
			case 3:
				phy.preamble_length = 255;
			  phy.masking |= PREAMBLE_TX_FLAG_MSK;
				break;
		}

		if(tx_power < 4)
		{
			phy.pa_power = PA_Power_Table[tx_power];
		}
    else
		{
			phy.pa_power = PA_Power_Table[0];
		}
		return 0;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

/*
 * @brief 设置工作参数（同步字节和回调函数）
 *
 * @param [in] sw: 同步字节
 * @param [in] cb: 同步字节
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details 同步字节长度默认4个字节
 *
 */
uint32_t fe_set_phy_parameter(unsigned char *sw, FE_PHY_CALLBACK cb)
{
	if(phy.mode == fe_phy_idle)
	{
		mem_data_copy(phy.sync_word, sw, 4);
		if(cb != 0)
		{
			phy.cb = cb;
		}
		return 0;
	}
	else
		return 0xFFFFFFFF;
}

/*
 * @brief 设置同步字节
 *
 * @param [in] s: 数据首地址
 *
 * @return:
 *    =0:成功
 *   !=0:失败
 *
 * @details 同步字节长度默认4个字节
 *
 */
//uint32_t fe_set_phy_sync_word(unsigned char *s)
//{
//	if(phy.mode == fe_phy_idle)
//	{
//		mem_data_copy(phy.sync_word, s, 4);
//		return 0;
//	}
//	else
//		return 0xFFFFFFFF;
//}

/*
 * @brief RF发射数据
 *
 * @param [in] data: 待发送数据首地址
 * @param [in] len: 待发送数据长度
 * @param [in] tx_time: 发射时间
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区最大长度20
 *
 */
uint32_t fe_phy_send_data(void)
{
	if((phy.masking & BC3602_INITIAL_FLAG_MSK) == 0)
	{
		return 0xFFFFFFFF;
	}
	else
	{
	  if(phy.mode == fe_phy_idle)
	  {
			if((phy.masking & DEEP_SLEEP_FLAG_MSK) != 0)
			{
				phy.mode = fe_phy_tx_mode;
			}
			else
			{
				if(phy.sleep_step == 0)
				{
				  phy.mode |= 0x2;
				}
				else
				{
					phy.mode = fe_phy_tx_mode;
				}
			}
		  return 0;
	  }
	  else
		{
		  return 0xFFFFFFFF;
		}
  }
}

/*
 * @brief RF发射数据
 *
 * @param [in] len: 接收发送数据长度
 * @param [in] rx_time: 接收等待时间
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区最大长度20
 *
 */
uint32_t fe_phy_receive_data(void)
{
	if((phy.masking & BC3602_INITIAL_FLAG_MSK) == 0)
	{
		return 0xFFFFFFFF;
	}
	else
	{
	  if(phy.mode == fe_phy_idle)
	  {
			if((phy.masking & DEEP_SLEEP_FLAG_MSK) != 0)
			{
		    phy.mode = fe_phy_rx_mode;
			}
			else
			{
				if(phy.sleep_step == 0)
				{
				  phy.mode |= 0x04;
				}
				else
				{
					phy.mode = fe_phy_rx_mode;
				}
			}
		  return 0;
	  }
	  else
		{
		  return 0xFFFFFFFF;
		}
  }
}

/*
 * @brief RF监听数据
 *
 * @param [in] idle_time: 空闲等待时间
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *
 */
uint32_t fe_phy_moniting_data(uint32_t idle_time)
{
	if((phy.masking & BC3602_INITIAL_FLAG_MSK) == 0)
	{
		return 0xFFFFFFFF;
	}
	else
	{
	  if(phy.mode == fe_phy_idle)
	  {
			phy.idle_time = idle_time;
			phy.mode = 0x8;
		  return 0;
	  }
	  else
		{
		  return 0xFFFFFFFF;
		}
  }
}

/*
 * @brief 退出
 *
 * @param [in]: 无
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *
 */
uint32_t fe_phy_quit(void)
{
	if(phy.mode != fe_phy_idle)
	{
		phy.mode |= fe_phy_end;
	}
	return 0;
}

/*
 * @brief 设置PHY回调函数
 *
 * @param [in] cb: 回调函数
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 *  
 *  
 */
//uint32_t fe_set_phy_callback(FE_PHY_CALLBACK cb)
//{
//	if(cb != 0)
//	{
//		phy.cb = cb;
//		return 0;
//	}
//	else
//		return 0xFFFFFFFF;
//}

