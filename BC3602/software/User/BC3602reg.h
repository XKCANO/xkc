
#ifndef _BC3602_REG_H_
#define _BC3602_REG_H_
												
/* BC3602 strobe command */
#define WRITE_REGS_CMD				0x40  /* Register write command */
#define READ_REGS_CMD					0xC0  /* Register read command */
#define REGS_BANK_CMD      		0x20  /* Set Register Bank command */
#define WRITE_SYNCWORD_CMD  	0x10  /* Write Sync-Word command */
#define READ_SYNCWORD_CMD   	0x90  /* Read Sync-Word command */
#define WRITE_FIFO_CMD      	0x11  /* Write TX FIFO command */
#define READ_FIFO_CMD       	0x91  /* Read RX FIFO command */
#define READ_ID_CMD     	  	0x9F  /* Read Chip ID command */					//3602 only
#define SOFT_RESET_CMD      	0x08  /* Software reset command */
#define REST_TX_POS_CMD     	0x09  /* TX FIFO address pointer reset command */
#define REST_RX_POS_CMD     	0x89  /* RX FIFO address pointer reset command */
#define DEEP_SLEEP_CMD      	0x0A  /* Enter Deep Sleep mode */
#define IDLE_MODE_CMD       	0x0B  /* Enter Idle mode */
#define LIGHT_SLEEP_CMD     	0x0C  /* Enter Light Sleep mode */
#define STANDBY_MODE_CMD    	0x0D  /* Enter Standby mode */
#define TX_MODE_CMD         	0x0E  /* Enter TX mode */
#define RX_MODE_CMD         	0x8E  /* Enter RX mode */
#define REGSADDR_MASK       	0x3F

/* BC3602 register bank */
enum 
{
   REGS_BANK0 = 0,                  /* register bank 0 */
   REGS_BANK1,                      /* register bank 1 */
   REGS_BANK2,                      /* register bank 2 */
   REGS_BANK3                       /* register bank 3 */
};

/* BC3602 Common & Bank 0 register */
enum 
{
   CONFIG_REGS = 0x00,           /* Configuration Control Register */
   CLOCK_CTL_REGS,               /* Reset/Clock Control Register */
   IRQ_CTL_REGS,                 /* Interrupt Control Register */
   IRQ_ENABLE_REGS,              /* Interrupt enable register */
   IRQ_STATUS_REGS,              /* interrupt status register */
   GIO12_CTL_REGS = 0x06,       /* GPIO 1/2 control register */
   GIO34_CTL_REGS,              /* GPIO 3/4 control register */
   GPIO_PULL_UP_REGS,            /* SPI/GPIO pull high control register */
   TX_FIFO_SA_REGS,              /* TX FIFO start address register */
   FIFO2_CTL_REGS,               /* Packet mode FIFO control regster */
   PREAMBLE_LENG_REGS,           /* Packet preamble length register */
   PACKET_CTL2_REGS,
   PACKET_CTL3_REGS,
   PACKET_CTL4_REGS,
   TX_DATA_LENG_REGS,
   RX_DATA_LENG_REGS,
   TRX_MODE_DELAY_REGS,
   HEADER_ADDR0_REGS,
   HEADER_ADDR1_REGS,
   MODULATOR_CTL1_REGS = 0x14,   
   MODULATOR_CTL2_REGS,
   MODULATOR_CTL3_REGS,
   DEMOULATOR_CTL1_REGS = 0x17,
   DEMOULATOR_CTL2_REGS,
   DEMOULATOR_CTL3_REGS,
   DEMOULATOR_CTL4_REGS,
   DEMOULATOR_CTL5_REGS,
   DEMOULATOR_CTL8_REGS = 0x1E,
   OPERATION_CTL_REGS = 0x20,
   FRACTIONAL_N_DN_REGS = 0x22,   
   FRACTIONAL_N_DKL_REGS,   
   FRACTIONAL_N_DKM_REGS,   
   FRACTIONAL_N_DKH_REGS,   
   MODE_STATUS_REGS,
   RSSI_CTL_REGS = 0x28,
   RSSI_VALUE_REGS,
   RSSI_VALUE_ID_REGS,
   ATR_CONTROL_REGS,
   ATR_CYCLE_L_REGS,
   ATR_CYCLE_H_REGS,
   ATR_ACTIVE_REGS,
   ATR_EACTIVE_L_REGS,
   ATR_EACTIVE_H_REGS,
   ARK_CONTROL_REGS,
   ARK_ACTIVE_REGS,
	 ATRCT_L_REGS,
	 ATRCT_H_REGS,
	 ATR_ACTIVE_H_REGS,
   XO_CAP_CTL_REGS = 0x3C,
   XO_SEL_CTL_REGS,
   LIRC_CTL_REGS,
   TX_POWER_CTL_REGS
};

/* BC3602 Bank 1 register */
enum 
{
   AGC_CTL1_REGS = 0x20,
   AGC_CTL2_REGS,
   AGC_CTL3_REGS,
   AGC_CTL4_REGS,
   AGC_CTL5_REGS,
   AGC_CTL6_REGS,
   AGC_CTL7_REGS,
   FILTER_CTL1_REGS = 0x2C,
   FILTER_CTL2_REGS,
   FILTER_CTL3_REGS,
   FILTER_CTL4_REGS,
   FILTER_CTL5_REGS,
   FILTER_CTL6_REGS,
   FILTER_CTL7_REGS,
   FILTER_CTL8_REGS,
   FILTER_CTL9_REGS,
   FILTER_CTL10_REGS,
   FILTER_CTL11_REGS,
   FILTER_CTL12_REGS,
   FILTER_CTL13_REGS,
   FILTER_CTL14_REGS,
   FILTER_CTL15_REGS,
   FILTER_CTL16_REGS,
   FILTER_CTL17_REGS,
   FILTER_CTL18_REGS,
   FILTER_CTL19_REGS,   
};

/* BC3602 Bank 2 register */
enum
{
	GAIN_CTL_REGS = 0x21,
	RX2_CTL_REGS = 0x2F,
};

/* IRQ1 */
enum
{
	_b_RX_FF_OV_,
	_b_RX_TO_,
};

#define	_RX_FF_OV_			(0x01 << _b_RX_FF_OV_)
#define	_RX_TO_				  (0x01 << _b_RX_TO_)

/* IRQ2 */

#define TXCMPIE_EN 		0x01				//TX Complete IRQ Enable
#define RXCMPIE_EN 		0x02				//RX Complete IRQ Enable
#define CALCMPIE_EN 	0x04				//Calibration Complete IRQ Enable
#define RXDETIE_EN 		0x08				//RX Event Detected IRQ Enable
#define RXERRIE_EN 		0x10				//RX Error IRQ Enable
#define FIFOLTIE_EN 	0x20				//FIFO Low Threshold IRQ Enable
#define ATRCTIE_EN		0x40				//ATR Cycle Timer IRQ Enable
#define ARKTFIE_EN		0x80				//ARK TX Failure IRQ Enable

/* IRQ3 */
enum
{
	_b_TX_COMPLETE_IRQ_ = 0,
	_b_RX_COMPLETE_IRQ_,
	_b_CALIBRATION_COMPLETE_,
	_b_RX_CRY_PRMBL_SYNC_IRQ_,
	_b_RX_FAIL_IRQ_,
	_b_TX_RX_MEG_IRQ_,
	_b_WTX_WAKEUP_IRQ_,
	_b_ARK_TX_FAIL_IRQ_,
};

#define	_TX_COMPLETE_IRQ_				  (0x01	<< _b_TX_COMPLETE_IRQ_)
#define	_RX_COMPLETE_IRQ_				  (0x01	<< _b_RX_COMPLETE_IRQ_)
#define	_CALIBRATION_COMPLETE_		(0x01	<< _b_CALIBRATION_COMPLETE_)
#define	_RX_CRY_PRMBL_SYNC_IRQ_		(0x01	<< _b_RX_CRY_PRMBL_SYNC_IRQ_)
#define	_RX_FAIL_IRQ_							(0x01	<< _b_RX_FAIL_IRQ_)
#define	_TX_RX_MEG_IRQ_						(0x01	<< _b_TX_RX_MEG_IRQ_)
#define	_WTX_WAKEUP_IRQ_					(0x01	<< _b_WTX_WAKEUP_IRQ_)
#define	_ARK_TX_FAIL_IRQ_					(0x01	<< _b_ARK_TX_FAIL_IRQ_)


/* GIO function */
enum 
{
   INPUT_MODE = 0,         /* GPIO input mode */
   SPI_SDO_FUN,            /* SPI SDO function */
   DIRECT_TRXD,            /* Direct mode TX/RD data input/output */
   DIRECT_TXD,             /* Direct mode TX data input */
   DIRECT_RXD,             /* Direct mode RX data output */
   INT_REQUEST,            /* Interrupt request output */
   LOSC_INPUT,             /* LOSC input */
   TBCLK_OUTPUT = 8,       /* Direct mode TX bit clock output */
   RBCLK_OUTPUT,           /* Direct mode RX bit clock output */
   FCLK_OUTPUT,            /* Frequency clock output */
   LOSC_OUTPUT,            /* LOSC output */
   EPA_CTLO,               /* External PA control output */
   ELNA_CTLO,              /* External LNA control output */
   DIRECT_TRBCLK           /* Direct mode Tx/Rx bit clock output */
};

/* STA1 */
enum
{
	_STA_SLEEP_MODE_ = 0,
	_STA_IDLE_MODE_,
	_STA_LIGHT_SLEEP_MODE_,
	_STA_STANDBY_MODE_,
	_STA_TX_MODE_,
	_STA_RX_MODE_,
	_STA_VCO_MODE_,
};	

/* ATR1 */
enum
{
	_ATR_WTX_ = 0,
	_ATR_WRX_,
	_ATR_WTM_
};

/* OM */
enum
{
	_OM_RX_ = 0,
	_OM_TX_
};
#endif	/* _BC3602_REG_H_ */
