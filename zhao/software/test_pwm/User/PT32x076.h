/********************************************************************************
  * @file    PT32x076.h
  * @author  应用开发团队
  * @version V1.1.0
  * @date    2023/10/20
  * @brief   This file contains all the functions prototypes for interrupt number,MCU registers and bits
	*
  * @attention
  *
  * 当前的固件仅供指导, 目的是向客户提供有关其产品的编码信息,以节省他们的时间。
  * 对于因此类固件的内容/或客户使用其中包含的编码信息而引起的任何索赔, * Pai-IC 不对任何直接，间接或继发的损害负责。
  *
  * (C) 版权所有 Pai-IC Microelectronics
  *******************************************************************************/

#ifndef PT32x076_H
#define PT32x076_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__CC_ARM)
#pragma anon_unions
#endif

#define __CM0_REV			0 					/*!< Core Revision r0p0	*/
#define __MPU_PRESENT		0 				/*!< S038x do not provide MPU	*/
#define __NVIC_PRIO_BITS	2 			/*!< S038x uses 2 Bits for the Priority Levels  */
#define __Vendor_SysTickConfig	0 /*!< Set to 1 if different SysTick Config is used  */
#define _PT32x076								/*!< MCU Type*/

/**
 * @brief S038x Interrupt Number Definition
 */
typedef enum IRQn
{
	/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
	NMI_IRQn        = -14,	/*!< 2 Non Maskable Interrupt*/
	HardFault_IRQn	= -13,	/*!< 3 Cortex-M0 Hard Fault Interrupt*/
	SVCall_IRQn		  = -5,			/*!< 11 Cortex-M0 SV Call Interrupt	*/
	PendSV_IRQn	    = -2,		/*!< 14 Cortex-M0 Pend SV Interrupt	*/
	SysTick_IRQn	  = -1,			/*!< 15 Cortex-M0 System Tick Interrupt*/

	/****** MCU Specific Interrupt Numbers *******************************************************/
	PVD_IRQn 	    =  0 ,  		/* PVD         Interrupt  */
	CMP0_IRQn 	  =  1 ,  		/* CMP0        Interrupt  */
	AES_IRQn 	    =  2 ,  		/* AES         Interrupt  */
	IFMC_IRQn    	=  3 ,  		/* IFMC        Interrupt  */
	DMA_IRQn    	=  4 ,  		/* DMA         Interrupt  */
	EXTIA_IRQn    =  5 ,  		/* PA          Interrupt  */
	EXTIB_IRQn    =  6 , 			/* PB          Interrupt  */
	EXTIC_IRQn    =  7 ,			/* PC          Interrupt  */
	EXTIF_IRQn    =  8 ,			/* PF          Interrupt  */
	LPTIM_IRQn    =  9 ,			/* LPTIM       Interrupt  */           
	UART2_IRQn	  =  10,  		/* UART2       Interrupt 	*/
	UART3_IRQn	  =  11, 	  	/* UART3       Interrupt 	*/
	ADC_IRQn      =  12,  		/* ADC         Interrupt 	*/
	TIM1_IRQn     =  13,  		/* TIM1        Interrupt 	*/
	TIM5_IRQn     =  14,  		/* TIM5        Interrupt 	*/
	TIM4_IRQn     =  15,  		/* TIM4        Interrupt 	*/
	TIM3_IRQn     =  16,  		/* TIM3        Interrupt 	*/
	TIM2_IRQn     =  17, 	  	/* TIM2        Interrupt 	*/
	ALU_IRQn      =  18, 		 	/* ALU         Interrupt 	*/
	LPUART1_IRQn  =  19, 		 	/* LPUART1_IRQnInterrupt 	*/
	LPUART0_IRQn  =  20,  		/* LPUART0_IRQnInterrupt 	*/
	CMP_IRQn      =  21,  		/* CMP         Interrupt 	*/
	TIM8_IRQn     =  22,  		/* TIM8        Interrupt 	*/
	I2C0_IRQn     =  23,  		/* I2C0        Interrupt 	*/
	I2C1_IRQn     =  24,  		/* I2C1        Interrupt 	*/
	SPI0_IRQn     =  25,  		/* SPI0        Interrupt 	*/
	SPI1_IRQn     =  26,  		/* SPI1        Interrupt 	*/
	UART0_IRQn    =  27,  		/* UART0       Interrupt 	*/
	UART1_IRQn    =  28,  		/* UART1       Interrupt 	*/
	RTC_IRQn      =  29, 	  	/* RTC         Interrupt 	*/
	TIM6_IRQn     =  30,  		/* TIM6        Interrupt 	*/
	TIM7_IRQn     =  31,  		/* TIM7        Interrupt 	*/
} IRQn_Type;


#include "core_cm0.h"
#include "PT32x076_Type.h"
#include <stdint.h>


/** @addtogroup Exported_types
  * @{
  */
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, RemapStatus, ProtectStatus, BitAction;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/** @defgroup ID_TypeDef
* @{
*/

typedef struct
{
	__I  u32  UDID;     /*!< Offset: 0x000 User Define Identifier Register 					(R) */
	u32  RESERVED0[2]; 	/*!< Offset: 0x004 Reserved 										   							*/
  u32  RESERVED1;			/*!< Offset: 0x008 Reserved 										   							*/
	__I  u32  UID1;   	/*!< Offset: 0x010 Unique Product Identification Register 1 (R) */
	__I  u32  UID2;   	/*!< Offset: 0x014 Unique Product Identification Register 2 (R) */
	__I  u32  UID3;   	/*!< Offset: 0x018 Unique Product Identification Register 3 (R) */
	__I  u32  CID;      /*!< Offset: 0x01C Chip Configration Identifier Register 		(R) */
} ID_TypeDef;

/** @defgroup GPIO_TypeDef
* @{
*/
typedef struct
{
	__IO u32  DR;        	/*!< Offset: 0x000 DATA Register 														 (R/W) */
	u32  RESERVED1;       /*!< Offset: 0x004 Reserved 																			 */
	__IO u32  OES;				/*!< Offset: 0x008 Output Enable Set Register  							 (R/W) */
	__O  u32  OEC; 				/*!< Offset: 0x00C Output Enable Clear Register  						   (W) */
	u32  RESERVED2[12];		/*!< Offset: 0x010 Reserved 																			 */
	__IO u32  PUS;				/*!< Offset: 0x040 Pull Up Set Register  										 (R/W) */
	__O  u32  PUC;				/*!< Offset: 0x044 Pull Up Clear Register  									   (W) */
	__IO u32  PDS;				/*!< Offset: 0x048 Pull Down Set Register  									 (R/W) */
	__O  u32  PDC;				/*!< Offset: 0x04C Pull Down Clear Register  								   (W) */
	__IO u32  ODS;				/*!< Offset: 0x050 Open Drain Set Register  								 (R/W) */
	__O  u32  ODC;				/*!< Offset: 0x054 Open Drain Clear Register  							   (W) */
	u32  RESERVED3[2];    /*!< Offset: 0x058 Reserved 																			 */
	u32  RESERVED4[4];		/*!< Offset: 0x060 Reserved 																			 */
	__IO u32  CSS;				/*!< Offset: 0x070 Sthmidt set Register 										 (R/W) */
	__O  u32  CSC;				/*!< Offset: 0x074 Sthmidt Clear Register 									   (W) */
	__IO u32  BSR;				/*!< Offset: 0x078 Port Bit Set Register  							     (R/W) */
	__IO u32  BRR;				/*!< Offset: 0x07C Port Bit Reset Register  							   (R/W) */
} GPIO_TypeDef;

/** @defgroup AFIO_TypeDef
* @{
*/
typedef struct
{
	__IO u32  AFS[2];	      /*!< Offset: 0x000 Alternate Function Set Register0/1 	(R/W) */
	__O  u32  AFC;    	    /*!< Offset: 0x008 Alternate Function Clear Register0  	  (W) */
	u32 RESERVED0[15];	    /*!< Offset: 0x00C Reserved 																	*/
	__IO u32  ANAS;					/*!< Offset: 0x048 Analog function Set Register  				(R/W) */
	__O  u32  ANAC;					/*!< Offset: 0x04C Analog function Clear Register  			  (W) */
} AFIO_TypeDef;

/** @defgroup EXTI_TypeDef
* @{
*/
typedef struct
{
	__IO u32  IES;     	/*!< Offset: 0x000 Interrupt Enable Set Register  	 (R/W) */
	__O  u32  IEC;    	/*!< Offset: 0x004 Interrupt Enable Clear Register     (W) */
	__IO u32  ITS;      /*!< Offset: 0x008 Interrupt Type Set Register0  		 (R/W) */
	__O  u32  ITC;      /*!< Offset: 0x00C Interrupt Type Clear Register0      (W) */
	__IO u32  ITDS;	    /*!< Offset: 0x010 Interrupt Type Set Register1  		 (R/W) */
	__O  u32  ITDC;	    /*!< Offset: 0x014 Interrupt Type Clear Register1  	   (W) */
	__IO u32  PTS;      /*!< Offset: 0x018 Interrupt Polarity Set Register   (R/W) */
	__O  u32  PTC;   	  /*!< Offset: 0x01C Interrupt Polarity Clear Register 	 (W) */
	__IO u32  IF;	      /*!< Offset: 0x020 Interrupt Status Register  			 (R/W) */
} EXTI_TypeDef;

/** @defgroup TIM_TypeDef
* @{
*/
typedef struct
{
	__IO u32 SR;        /*!< Offset: 0x00  TIM Interrupt status Register   					  (R/W) */
	__IO u32 CR1;       /*!< Offset: 0x04  TIM Control Register 1            				  (R/W) */
	__IO u32 MSCR;      /*!< Offset: 0x08  TIM Master And Slave Mode Control Register (R/W) */
	__IO u32 ITARR;     /*!< Offset: 0x0C  TIM Interrupt Auto Reload Register     		(R/W) */
	__I  u32 ITCNT;     /*!< Offset: 0x10  TIM Interrupt Counter Register 					  (R)   */
	__IO u32 PSC;       /*!< Offset: 0x14  TIM Prescale Register           					  (R/W) */
	u32 RESERVED0;    	/*!< Offset: 0x18  Reserved 																	  		*/
	__IO u32 CNT;       /*!< Offset: 0x1C  TIM Counter Register      								  (R)   */
	__IO u32 CR2;       /*!< Offset: 0x20  TIM Control Register 2      							  (R/W) */
	__IO u32 ARR;       /*!< Offset: 0x24  TIM Auto Reload Register       						(R/W) */
	__IO u32 OCR[4];    /*!< Offset: 0x28-0x34  TIM Output Compare Register 1-4       (R/W) */
	__IO u32 CAPR1;     /*!< Offset: 0x38  TIM Capture Configuration Register 1    	  (R/W) */
	__IO u32 CAPR2;     /*!< Offset: 0x3C  TIM Capture Configuration Register 2   	  (R/W) */
	__I  u32 ICR[4];    /*!< Offset: 0x40-0x4C  TIM Input Capture Register 1-4     		(R)   */
	__IO u32 OCMR;      /*!< Offset: 0x50  TIM Output Compare Mode Register     	  	(R/W) */
	__IO u32 BDTR;      /*!< Offset: 0x54  TIM Break And Dead Time Register         	(R/W) */
	__IO u32 CR3;       /*!< Offset: 0x58  TIM Control Register 3            				  (R/W) */
	__IO u32 TDCR;      /*!< Offset: 0x5C  TIM Trigger DMA Control Register        	  (R/W) */
	__IO u32 TACR;      /*!< Offset: 0x60  TIM Trigger ADC Control Register        	  (R/W) */
	__IO u32 BKICR;     /*!< Offset: 0x64  TIM Break Input Control Register        	  (R/W) */
}TIM_TypeDef;


/** @defgroup IWDG_TypeDef
* @{
*/
typedef struct
{
	__IO u32 RLR;   		/*!< Offset: 0x000  IWDG Reload register	 (R/W) */
	__IO u32 CNT; 			/*!< Offset: 0x004  IWDG COUNT register	 	 (R/W) */
	__IO u32 CR;    		/*!< Offset: 0x008  IWDG Control register  (R/W) */
	__O  u32 KR;  			/*!< Offset: 0x00C  IWDG Key register	 	     (W) */
	__I  u32 SR;   			/*!< Offset: 0x010  IWDG Status register	 (R)   */
	u32 RESERVED0[251]; /*!< Offset: 0x014  Reserved 									   */
	__IO u32 LOCK;    	/*!< Offset: 0x400  IWDG Lock register	 	 (R/W) */
} IWDG_TypeDef;

/** @defgroup UART_TypeDef
* @{
*/
typedef struct
{
	__IO u32 DR;     	 /*!< Offset: 0x000  UART Buffer Register 				   								(R/W) */
	__IO u32 CR;		 	 /*!< Offset: 0x004  UART Control Register				   								(R/W) */
	__IO u32 BRR;      /*!< Offset: 0x008  UART Baud Rate Register			   								(R/W) */
	__IO u32 IE;    	 /*!< Offset: 0x00C  UART Interrupt Enable Register  								(R/W) */
	__IO u32 SR;     	 /*!< Offset: 0x010  UART Status Register						 								(R/W) */
	u32 RESERVED0;	   /*!< Offset: 0x014  Reserved 														 	 							*/
	__IO u32 TO;   		 /*!< Offset: 0x018  UART Time Out Register  			   								(R/W) */
	__IO u32 TXFR;     /*!< Offset: 0x01C  UART TX Buffer Reset Register     								(W) */
	__IO u32 RXFR;     /*!< Offset: 0x020  UART RX Buffer Reset Register     								(W) */
	u32 RESERVED1;		 /*!< Offset: 0x024  Reserved 														 	 							*/
	__IO u32 IMCR;		 /*!< Offset: 0x028  UART Infrared Modulation Control Register 			(R/W) */
	__IO u32 IMDCR;		 /*!< Offset: 0x02C  UART Infrared Modulation Duty Control Register (R/W) */
	__IO u32 AR;		   /*!< Offset: 0x030  Address Register                               (R/W) */	
} UART_TypeDef;

/** @defgroup SPI_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR1;       /*!< Offset: 0x000  SPI Control Register1 				   (R/W) */
	__IO u32 CR2;       /*!< Offset: 0x004  SPI Control Register2 				   (R/W) */
	__IO u32 DR;        /*!< Offset: 0x008  SPI Data Register 				   	   (R/W) */
	__I  u32 SR1;       /*!< Offset: 0x00C  SPI Status Register1 				     (R)   */
	__IO u32 BR; 	   	  /*!< Offset: 0x010  SPI Clock Prescaler Register 	   (R/W) */
	__IO u32 IE;        /*!< Offset: 0x014  SPI Interrupt Enable Register  	 (R/W) */
	__I  u32 SR2;       /*!< Offset: 0x018  SPI Status Register2 				   	 (R)   */
	u32 RESERVED0;	    /*!< Offset: 0x01C  Reserved 														 	 */
	__O  u32 IC;        /*!< Offset: 0x020  SPI Interrupt Flag Clear Register  (W) */
	__IO u32 DCR;       /*!< Offset: 0x024  SPI DMA Control Register 				 (R/W) */
	__IO u32 CSS;       /*!< Offset: 0x028  SPI Chip-Select Control Register (R/W) */
	__O  u32 TXFR;      /*!< Offset: 0x02C  SPI Transmit FIFO Reset Register   (W) */
	__O  u32 RXFR;      /*!< Offset: 0x030  SPI Receive FIFO Reset Register    (W) */
} SPI_TypeDef;

/** @defgroup I2C_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;		    /*!< Offset: 0x000 	I2C Control Register  	 		(R/W) */
	__I  u32 SR; 		    /*!< Offset: 0x004 	I2C Status Register  		 		(R)   */
	__IO u32 DR;  	 	  /*!< Offset: 0x008 	I2C Data Register  		 	 		(R/W) */
	__IO u32 OAR;	 			/*!< Offset: 0x00C 	I2C Own Address Register 		(R/W) */
	u32 RESERVED0;      /*!< Offset: 0x010  Reserved 												  */
	u32 RESERVED1;      /*!< Offset: 0x014  Reserved												  */
	__IO u32 CCR; 		 	/*!< Offset: 0x018 	I2C Clear Controll Register (R/W) */
} I2C_TypeDef;


/** @defgroup ADC_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR1;       /*!< Offset: 0x000  ADC Control Register1 									(R/W) */
	__IO u32 CR2;       /*!< Offset: 0x004  ADC Control Register2 									(R/W) */
	__I  u32 SR;    		/*!< Offset: 0x008  ADC Status Register  										(R)   */
	__I  u32 DR;    		/*!< Offset: 0x00C 	ADC data Register 											(R)   */
	u32 RESERVED0;	    /*!< Offset: 0x010  Reserved 														 	 				*/
	__IO u32 SCHR[4];		/*!< Offset: 0x014 	ADC Scan Channe1 Configuration Register (R/W) */
	__IO u32 BGCR;      /*!< Offset: 0x024  BG2v0 Control register                        */
	u32 RESERVED1[6];		/*!< Offset: 0x028  Reserved 														 	 				*/
	__I  u32 SCHDR[20];	/*!< Offset: 0x040 - 0x08C ADC Scan Channel x Data Register (R)   */
} ADC_TypeDef;

/** @defgroup CMP_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR1;       /*!< Offset: 0x000  CMP Control Register1  				 (R/W) */
	u32 RESERVED0[2];   /*!< Offset: 0x004  Reserved 														 */
	__IO u32 IE;        /*!< Offset: 0x00C  CMP Interrupt Enable Register  (R/W) */
	__IO u32 SR;        /*!< Offset: 0x010  CMP Status Register 					 (R/W) */
	__IO u32 CR2;       /*!< Offset: 0x014  CMP Control Register2   			 (R/W) */
} CMP_TypeDef;

/** @defgroup OPA_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR1;      /*!< Offset: 0x000  OPA Control Register  (R/W) */
	__IO u32 CR2;	     /*!< Offset: 0x004  OPA Control Register  (R/W) */
} OPA_TypeDef;

/** @defgroup LDAC_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;       /*!< Offset: 0x000  LDAC Control Register  (R/W) */
} LDAC_TypeDef;

/** @defgroup CRC_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;       /*!< Offset: 0x000  CRC Control Register     (R/W) */
	__IO u32 SEED;     /*!< Offset: 0x004  CRC Seed Register   		  (R/W) */
	__IO u32 POLY;     /*!< Offset: 0x008  CRC polynomial Register  (R/W) */
	__O  u32 DIN;      /*!< Offset: 0x00C  CRC Data INPUT Register    (W) */
	__I  u32 DOUT;     /*!< Offset: 0x010  CRC Data INPUT Register  (R)   */
} CRC_TypeDef;

/** @defgroup PWR_TypeDef
* @{
*/
typedef struct
{
	__IO u32 PVDR;				 /*!< Offset: 0x000   PWR Power Voltage Detect Control Register (R/W) */
} PWR_TypeDef;

/** @defgroup RCC_TypeDef
* @{
*/

typedef struct
{
	__IO u32 HSECR1;  		/*!< Offset: 0x000 	 RCC HSE Control Register1 							(R/W) */
	__IO u32 HSECR2;  		/*!< Offset: 0x004 	 RCC HSE Control Register2 							(R/W) */
	__IO u32 HSICR;				/*!< Offset: 0x008 	 RCC HSI Control Register  							(R/W) */
	__IO u32 LSICR;				/*!< Offset: 0x00C 	 RCC LSI Control Register  							(R/W) */
	u32 RESERVED0[3];  		/*!< Offset: 0x010   Reserved 																		*/
	__IO u32 MCOR;      	/*!< Offset: 0x01C 	 RCC MCO Control Register  							(R/W) */
	u32 RESERVED1[4];  		/*!< Offset: 0x020   Reserved 																		*/
	__IO u32 LSECR;				/*!< Offset: 0x030 	 LSE Control Register             			(R/W) */
	__IO u32 PLLCFGR1;		/*!< Offset: 0x034 	 PLL Configuration Register1   	    		(R/W) */
	__IO u32 PLLCFGR2;		/*!< Offset: 0x038 	 PLL Configuration Register2      			(R/W) */
	u32 RESERVED2[30194];	/*!< Offset: 0x03C   Reserved 																		*/
	__IO u32 CFGR;				/*!< Offset: 0x4001F00C RCC Clock Configuration Register 			  (R/W) */
	__IO u32 RSR;					/*!< Offset: 0x4001F010 RCC Reset State Register  							(R/W) */
	__O  u32 ASRCR;				/*!< Offset: 0x4001F014 RCC Advanced Software Control Register  (W) */
	__IO u32 RCR;					/*!< Offset: 0x4001F018 RCC Reset Control Register              (R/W) */
} RCC_TypeDef;

/** @defgroup IFMC_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR; 						/*!< Offset: 0x000   	IFMC Control Register 					(R/W) */
	__IO u32 SR;   					/*!< Offset: 0x004   	IFMC Status Register 		 				(R/W) */
	__IO u32 IE;  					/*!< Offset: 0x008   	IFMC Interrupt Enable Register  (R/W) */
	__IO u32 AR;    				/*!< Offset: 0x00C   	IFMC Address Register 					(R/W) */
	__IO u32 DR;  					/*!< Offset: 0x010   	IFMC Data Register   	 					(R/W) */
	u32  RESERVED0[5];	  	/*!< Offset: 0x014   	Reserved 															*/
	__IO u32 PSC;  					/*!< Offset: 0x028    IFMC Prescaler Register  				(R/W) */
	u32  RESERVED1[31733]; 	/*!< Offset: 0x02C    Reserved 								 							*/
	__IO u32 BSR;  					/*!< Offset: 0x1F000  BOOT Status Register  					(R/W) */
	__IO u32 IAPAR;  				/*!< Offset: 0x1F004  IAP Adress Register  						(R/W) */
	u32  RESERVED2[5];		  /*!< Offset: 0x1F008  Reserved 									 						*/
	__IO u32 IVTSAR;        /*!< Offset: 0x1F01C  inteerupt vectortable move to sram address register   (R/W) */
	u32  RESERVED3;					/*!< Offset: 0x1F020  Reserved 									 						*/
	__IO u32 RPSR;  				/*!< Offset: 0x1F024  Read Protection Status Register (R/W) */
} IFMC_TypeDef;

/** @defgroup DMA_Channel_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CSBAR;     	/*!< Offset: 0x000  DMA CHx Source Base Address Register              (R/W) */
	__IO u32 CDBAR;       /*!< Offset: 0x004  DMA CHx Destination Dase Address Register         (R/W) */
	__IO u32 CNDTR;       /*!< Offset: 0x008  DMA CHx Number of Data to Transfer Register       (R/W) */
	__IO u32 CCR;         /*!< Offset: 0x00C  DMA CHx Control Register                          (R/W) */
	__IO u32 CCSAR;       /*!< Offset: 0x010  DMA CHx Current Data Source Address Register      (R/W) */
	__IO u32 CCDAR;       /*!< Offset: 0x014  DMA CHx Current Data Destination Address Register (R/W) */
	__IO u32 CCNTR;       /*!< Offset: 0x018  DMA CHx Residue Cnt Register                      (R/W) */
} DMA_Channel_TypeDef;

/** @defgroup DMA_TypeDef
* @{
*/
typedef struct
{
	__IO u32 IER;         /*!< Offset: 0x0C0  DMA Interrupt Enable Register         (R/W) */
	__O  u32 ICR;         /*!< Offset: 0x0C4  DMA Flag Clear Register               	(W) */
	__I  u32 SR;          /*!< Offset: 0x0C8  DMA Status Register                   (R) 	*/
	__IO u32 CHAPCR[2];   /*!< Offset: 0x0CC  DMA Relevance Peripheral Register     (R/W) */
} DMA_TypeDef;

/** @defgroup BEEP_TypeDef
* @{
*/
typedef struct
{
	__IO u32 HCR;  					/*!< Offset: 0x000   BEEP High Sink Control Register  (R/W) */
	u32  RESERVED1[1015];		/*!< Offset: 0x004   Reserved 													*/
	__IO u32 CR;    				/*!< Offset: 0xFE0   BEEP Control Register        (R/W) */
} BEEP_TypeDef;

/** @defgroup ALU_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;  					/*!< Offset: 0x000  ALU Control Register            (R/W) */
	__IO u32 IE;  					/*!< Offset: 0x004  ALU Interrupt Enable Register   (R/W) */
	__IO u32 SR;    				/*!< Offset: 0x008  ALU Status Register             (R/W) */
	__IO u32 OPDXR;    			/*!< Offset: 0x00C  ALU Operand X Register          (R/W) */
	__IO u32 OPDYR;    			/*!< Offset: 0x010  ALU Operand Y Register          (R/W) */
	__IO u32 OPDZR;    			/*!< Offset: 0x014  ALU Operand Z Register          (R/W) */
	u32  RESERVED0;		      /*!< Offset: 0x018  Reserved 													    */
	__I  u32 DHR;    				/*!< Offset: 0x01C  ALU Data High 32-bit Register   (R)   */
	__I  u32 DLR;    				/*!< Offset: 0x020  ALU Data Low 32-bit Register    (R)   */
	u32  RESERVED1[4];		  /*!< Offset: 0x024  Reserved 													    */
	__I  u32 DRR;    				/*!< Offset: 0x034  ALU Division Remainder Register (R)   */
} ALU_TypeDef;

/** @defgroup LCD_TypeDef
* @{
*/

typedef struct
{
	__IO u32 CR;            /*!< Offset: 0x000  LCD Control Register   							 (R/W) */
	__IO u32 GCR;   		    /*!< Offset: 0x004  LCD Gray SET Register  							 (R/W) */
	__IO u32 PSC;  		      /*!< Offset: 0x008  LCD Prescaler Register  						 (R/W) */
	__IO u32 BTCR;          /*!< Offset: 0x00C  LCD Blink Time Control Register   	 (R/W) */
	__IO u32 BON;         	/*!< Offset: 0x010  LCD Blink On Control Register      	 (R/W) */
	__IO u32 PCR1;          /*!< Offset: 0x014  LCD Port Control Register 1      		 (R/W) */
	__IO u32 PCR2;        	/*!< Offset: 0x018  LCD Port Control Register 2      		 (R/W) */
	__IO u32 PDCR1;       	/*!< Offset: 0x01C  LCD Port Driver Control Register 1   (R/W) */
	__IO u32 PDCR2;         /*!< Offset: 0x020  LCD Port Driver Control Register 2   (R/W) */
	__IO u32 PDTR;	        /*!< Offset: 0x024  LCD Page Display Time Register       (R/W) */
	__IO u32 SDPR;     	    /*!< Offset: 0x028  LCD Scroll Display Page Register     (R/W) */
	__IO u32 PNR;        	  /*!< Offset: 0x02C  LCD Page Number Register             (R/W) */
	u32  RESERVED1[244];		/*!< Offset: 0x024  Reserved 	  	                             */
	__IO u32 LCD_PxLy[16 * 11];
} LCD_TypeDef;

/** @defgroup RTC_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;            /*!< Offset: 0x000  RTC Control Register   							(R/W) */
	__I  u32 SR1;   		    /*!< Offset: 0x004  RTC Status Register 1  							(R)   */
	__IO u32 LOCK;  		    /*!< Offset: 0x008  RTC Lock Register  							    (R/W) */
	__IO u32 CSEC;          /*!< Offset: 0x00C  RTC Clock Second Register   				(R/W) */
	__IO u32 CMIN;         	/*!< Offset: 0x010  RTC Clock Minute Register      			(R/W) */
	__IO u32 CHOUR;         /*!< Offset: 0x014  RTC Clock Hour Register     				(R/W) */
	__IO u32 CDAY;        	/*!< Offset: 0x018  RTC Clock Day Register   						(R/W) */
	__IO u32 CWEEK;       	/*!< Offset: 0x01C  RTC Clock Week Register   					(R/W) */
	__IO u32 CMON;         	/*!< Offset: 0x020  RTC Clock Month Register   					(R/W) */
	__IO u32 CYEAR;	        /*!< Offset: 0x024  RTC Clock Year Register       			(R/W) */
	__IO u32 IE;     	    	/*!< Offset: 0x028  RTC Interrupt Enable Register     	(R/W) */
	__IO u32 SR2;        	  /*!< Offset: 0x02C  RTC Status Register 2             	(R/W) */
	__IO u32 ASEC;        	/*!< Offset: 0x030  RTC Alarm Second Register           (R/W) */
	__IO u32 AMIN;        	/*!< Offset: 0x034  RTC Alarm Minute Register           (R/W) */
	__IO u32 AHOUR;        	/*!< Offset: 0x038  RTC Alarm Hour Register             (R/W) */
	__IO u32 AWEEK;        	/*!< Offset: 0x03C  RTC Alarm Week Register          	  (R/W) */
	__IO u32 TRIM;        	/*!< Offset: 0x040  RTC Trim Value Register          	  (R/W) */
} RTC_TypeDef;

/** @defgroup WWDG_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR1;    		/*!< Offset: 0x000  WWDG Control register                   (R/W) */
	__IO u32 CFGR;  		/*!< Offset: 0x004  WWDG Configuration register	 	          (R/W) */
	__IO u32 SR;   			/*!< Offset: 0x008  WWDG Status register	                  (R/W) */
	__IO u32 CR2 ;    	/*!< Offset: 0x00C  WWDG Control register	 	                (R/W) */
}WWDG_TypeDef;

/** @defgroup AES_TypeDef
* @{
*/
typedef struct
{
	__IO u32 CR;  					/*!<Offset: 0x00 AES control register 	                        (R/W)  */
	__I  u32 SR;    				/*!<Offset: 0x04 AES status register 	                          (R) 	 */
	 u32 RESERVED0[2];	    /*!<Offset: 0x08-0x0C                                           (R/W)  */
	__IO u32 KR[8];    			/*!<Offset: 0x10-0x2C AES encryption key configuration register (R/W)  */
	__IO u32 IVR[4];    		/*!<Offset: 0x30-0x3C AES initial vector configuration register (R/W)  */
	__IO u32 DINR[4];    		/*!<Offset: 0x40-0x4C AES input data register 	                (R/W)  */	
	 u32 RESERVED1[4];      /*!<Offset: 0x50-0x5C  	              												  (R/W)  */	
	__I  u32 DOUTR[4];    	/*!<Offset: 0x60-0x6C AES output data register 	                (R)   	*/	
} AES_TypeDef;

/*Peripheral and SRAM base address */
#define SRAM_BASE             (0x20000000)
#define FLASH_BASE            (0x00000000)

#define APB_BASE              (0x40000000)
#define AHB_BASE              (0x48000000)

/* AHB peripherals */
#define GPIOA_BASE        (AHB_BASE + 0x00000000)
#define GPIOB_BASE        (AHB_BASE + 0x00001000)
#define GPIOC_BASE        (AHB_BASE + 0x00002000)
#define GPIOF_BASE        (AHB_BASE + 0x00005000)

#define EXTIA_BASE				(AHB_BASE + 0x0000001C)
#define EXTIB_BASE				(AHB_BASE + 0x0000101C)
#define EXTIC_BASE				(AHB_BASE + 0x0000201C)
#define EXTIF_BASE				(AHB_BASE + 0x0000501C)

#define AFIOA_BASE				(AHB_BASE + 0x00000010)
#define AFIOB_BASE				(AHB_BASE + 0x00001010)
#define AFIOC_BASE				(AHB_BASE + 0x00002010)
#define AFIOF_BASE				(AHB_BASE + 0x00005010)

/* APB peripherals */
#define IFMC_BASE    	    (APB_BASE + 0x00000000)
#define CMP0_BASE	        (APB_BASE + 0x00000800)
#define CMP1_BASE	        (APB_BASE + 0x00000C00)
#define TIM2_BASE       	(APB_BASE + 0x00001000)
#define TIM3_BASE       	(APB_BASE + 0x00001400)
#define PWR_BASE        	(APB_BASE + 0x00001800)
#define RCC_BASE     	    (APB_BASE + 0x00001808)
#define BEEP_BASE         (APB_BASE + 0x00001820)
#define OPA_BASE	        (APB_BASE + 0x00001828)
#define LDAC_BASE	      	(APB_BASE + 0x00001830)
#define TIM4_BASE        	(APB_BASE + 0x00001C00)
#define WWDG_BASE        	(APB_BASE + 0x00002000)
#define CMP2_BASE	        (APB_BASE + 0x00002C00)
#define IWDG_BASE       	(APB_BASE + 0x00003000)
#define SPI1_BASE        	(APB_BASE + 0x00003800)
#define CRC_BASE         	(APB_BASE + 0x00003C00)
#define LPUART0_BASE   	  (APB_BASE + 0x00004000)
#define UART0_BASE    	  (APB_BASE + 0x00004400)
#define ALU_BASE    	  	(APB_BASE + 0x00004800)
#define LPUART1_BASE   	 	(APB_BASE + 0x00004C00)
#define I2C0_BASE         (APB_BASE + 0x00005400)
#define I2C1_BASE         (APB_BASE + 0x00005800)
#define UART2_BASE   	  	(APB_BASE + 0x00005C00)
#define UART3_BASE   	  	(APB_BASE + 0x00006000)
#define TIM8_BASE        	(APB_BASE + 0x00006400)
#define CMP3_BASE	        (APB_BASE + 0x00006800)
#define TIM10_BASE        (APB_BASE + 0x00006C00)
#define DMA_Channel0_BASE (APB_BASE + 0x0000F000)
#define DMA_Channel1_BASE (APB_BASE + 0x0000F020)
#define DMA_Channel2_BASE (APB_BASE + 0x0000F040)
#define DMA_Channel3_BASE (APB_BASE + 0x0000F060)
#define DMA_Channel4_BASE (APB_BASE + 0x0000F080)
#define DMA_Channel5_BASE (APB_BASE + 0x0000F0A0)
#define DMA_BASE         	(APB_BASE + 0x0000F0C0)
#define ADC_BASE          (APB_BASE + 0x00012400)
#define TIM1_BASE        	(APB_BASE + 0x00012C00)
#define SPI0_BASE         (APB_BASE + 0x00013000)
#define AES_BASE          (APB_BASE + 0x00013400)
#define UART1_BASE   	  	(APB_BASE + 0x00013800)
#define RTC_BASE   	  		(APB_BASE + 0x00013C00)
#define TIM5_BASE        	(APB_BASE + 0x00014400)
#define TIM6_BASE        	(APB_BASE + 0x00014800)
#define TIM7_BASE        	(APB_BASE + 0x00014C00)
#define LCD_BASE   		  	(APB_BASE + 0x00015000)
#define ID_BASE		        (APB_BASE + 0x0001F020)

/*Peripheral declaration */
#define PWR		((PWR_TypeDef  	   *) PWR_BASE )
#define RCC		((RCC_TypeDef   	 *) RCC_BASE )
#define ID		((ID_TypeDef       *) ID_BASE )

#define GPIOA	((GPIO_TypeDef     *) GPIOA_BASE )
#define GPIOB	((GPIO_TypeDef     *) GPIOB_BASE )
#define GPIOC	((GPIO_TypeDef     *) GPIOC_BASE )
#define GPIOF	((GPIO_TypeDef     *) GPIOF_BASE )

#define AFIOA	((AFIO_TypeDef     *) AFIOA_BASE )
#define AFIOB	((AFIO_TypeDef     *) AFIOB_BASE )
#define AFIOC	((AFIO_TypeDef     *) AFIOC_BASE )
#define AFIOF	((AFIO_TypeDef     *) AFIOF_BASE )

#define EXTIA	((EXTI_TypeDef     *) EXTIA_BASE )
#define EXTIB	((EXTI_TypeDef     *) EXTIB_BASE )
#define EXTIC	((EXTI_TypeDef     *) EXTIC_BASE )
#define EXTIF	((EXTI_TypeDef     *) EXTIF_BASE )

#define UART0 ((UART_TypeDef     *) UART0_BASE )
#define UART1 ((UART_TypeDef     *) UART1_BASE )
#define UART2 ((UART_TypeDef     *) UART2_BASE )
#define UART3 ((UART_TypeDef     *) UART3_BASE )
#define LPUART0 ((UART_TypeDef   *) LPUART0_BASE )
#define LPUART1 ((UART_TypeDef   *) LPUART1_BASE )

#define IFMC	((IFMC_TypeDef     *) IFMC_BASE )
#define ADC   ((ADC_TypeDef      *) ADC_BASE )
#define I2C0	((I2C_TypeDef      *) I2C0_BASE )
#define I2C1	((I2C_TypeDef      *) I2C1_BASE )
#define SPI0  ((SPI_TypeDef      *) SPI0_BASE )
#define SPI1	((SPI_TypeDef      *) SPI1_BASE )
#define CMP0	((CMP_TypeDef   	 *) CMP0_BASE )
#define CMP1	((CMP_TypeDef   	 *) CMP1_BASE )
#define CMP2	((CMP_TypeDef   	 *) CMP2_BASE )
#define CMP3	((CMP_TypeDef   	 *) CMP3_BASE )
#define OPA		((OPA_TypeDef   	 *) OPA_BASE )
#define LDAC	((LDAC_TypeDef   	 *) LDAC_BASE )
#define TIM1	((TIM_TypeDef      *) TIM1_BASE )
#define TIM2	((TIM_TypeDef      *) TIM2_BASE )
#define TIM3	((TIM_TypeDef      *) TIM3_BASE )
#define TIM4	((TIM_TypeDef      *) TIM4_BASE )
#define TIM5	((TIM_TypeDef      *) TIM5_BASE )
#define TIM6	((TIM_TypeDef      *)	TIM6_BASE )
#define TIM7	((TIM_TypeDef      *) TIM7_BASE )
#define TIM8	((TIM_TypeDef      *) TIM8_BASE )
#define LPTIM	((TIM_TypeDef      *) TIM10_BASE )
#define CRC		((CRC_TypeDef      *) CRC_BASE )
#define IWDG	((IWDG_TypeDef     *) IWDG_BASE )
#define WWDG	((WWDG_TypeDef     *) WWDG_BASE )
#define BEEP  ((BEEP_TypeDef     *) BEEP_BASE )
#define DMA_Channel0  ((DMA_Channel_TypeDef      *) DMA_Channel0_BASE )
#define DMA_Channel1  ((DMA_Channel_TypeDef      *) DMA_Channel1_BASE )
#define DMA_Channel2  ((DMA_Channel_TypeDef      *) DMA_Channel2_BASE )
#define DMA_Channel3  ((DMA_Channel_TypeDef      *) DMA_Channel3_BASE )
#define DMA_Channel4  ((DMA_Channel_TypeDef      *) DMA_Channel4_BASE )
#define DMA_Channel5  ((DMA_Channel_TypeDef      *) DMA_Channel5_BASE )
#define DMA   ((DMA_TypeDef      *) DMA_BASE )
#define LCD   ((LCD_TypeDef      *) LCD_BASE)
#define RTC   ((RTC_TypeDef      *) RTC_BASE)
#define ALU   ((ALU_TypeDef      *) ALU_BASE)
#define AES   ((AES_TypeDef      *) AES_BASE)

/******************** Peripheral Registers Bits Definition ***********************/
/******************************************************************************/
/*                                                                            */
/*                       Reset And Clock Control（RCC）                   	  */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RCC_HSECR1 register  ******************/
#define  RCC_HSECR1_EN            		 ((u32)0x00000001)        /*!< HSE enable */
#define  RCC_HSECR1_AAC              	 ((u32)0x00000002)        /*!< Automatic amplitude control */
#define  RCC_HSECR1_ECEN             	 ((u32)0x00000004)        /*!< External clock enable */
#define  RCC_HSECR1_HSEFR            	 ((u32)0x00000010)        /*!< HSE frequency range */
#define  RCC_HSECR1_LPF              	 ((u32)0x00000300)        /*!< Low pass filter */
#define  RCC_HSECR1_LPFB             	 ((u32)0x00000400)        /*!< Low pass filter bypass */
#define  RCC_HSECR1_RDY           		 ((u32)0x80000000)        /*!< HSE ready flag */

/********************  Bits definition for RCC_HSECR2 register  ******************/
#define  RCC_HSECR2_CAD              	 ((u32)0x00000007)        /*!< Current adjust */
#define  RCC_HSECR2_FDR              	 ((u32)0x00000300)        /*!< Feedback resistance selection */

/********************  Bits definition for RCC_HSI register  ******************/
#define  RCC_HSICR_EN             	   ((u32)0x00000001)        /*!< HSI enable */

/********************  Bits definition for RCC_LSICR register  ******************/
#define  RCC_LSICR_EN             	   ((u32)0x00000001)        /*!< LSI enable */
#define  RCC_LSICR_CFS             	   ((u32)0x00000002)        /*!< LSI clock frequency selection */

/********************  Bits definition for RCC_MCOR register  ******************/
#define  RCC_MCOR_COPRE              	 ((u32)0x00000007)        /*!< Clock output prescale */
#define  RCC_MCOR_COSRC                ((u32)0x00000070)        /*!< Clock output source */

/********************  Bits definition for RCC_LSECR register  ******************/
#define  RCC_LSECR_EN                  ((u32)0x00000001)        /*!< LSE enable */
#define  RCC_LSECR_ECEN                ((u32)0x00000002)        /*!< External clock enable */
#define  RCC_LSECR_RDY                 ((u32)0x00000004)        /*!< Ready flag */
#define  RCC_LSECR_LPF                 ((u32)0x00000300)        /*!< Low pass filter */
#define  RCC_LSECR_LPFB                ((u32)0x00000400)        /*!< Low pass filter bypass */

/********************  Bits definition for RCC_PLLCFGR1 register  ******************/
#define  RCC_PLLCFGR1_EN               ((u32)0x00000001)        /*!< PLL enable */
#define  RCC_PLLCFGR1_SRC              ((u32)0x00000002)        /*!< PLL entry clock source */
#define  RCC_PLLCFGR1_LPFB             ((u32)0x00000004)        /*!< Low pass filter bypass */
#define  RCC_PLLCFGR1_MUL              ((u32)0x000001F0)        /*!< PLL multiplication factor */
#define  RCC_PLLCFGR1_DIV              ((u32)0x00007000)        /*!< PLL division factor */
#define  RCC_PLLCFGR1_RDY              ((u32)0x80000000)        /*!< Ready flag */

/********************  Bits definition for RCC_PLLCFGR2 register  ******************/
#define  RCC_PLLCFGR2_LPF              ((u32)0x00000030)        /*!< Low pass filter */
#define  RCC_PLLCFGR2_DELAY            ((u32)0x00000040)        /*!< Delay */

/********************  Bits definition for RCC_CFGR register  ******************/
#define  RCC_CFGR_SCW                  ((u32)0x00000003)        /*!< System clock switch */
#define  RCC_CFGR_HPRE                 ((u32)0x000001F0)        /*!< HCLK prescaler */
#define  RCC_CFGR_HSEDE                ((u32)0x00001000)        /*!< PLL fail detecting enable */
#define  RCC_CFGR_FWUS                 ((u32)0x00010000)        /*!< Flash wakeup selection */
#define  RCC_CFGR_SCWK                 ((u32)0x00100000)        /*!< System clock after wakeup */
#define  RCC_CFGR_SCDS                 ((u32)0x00600000)        /*!< System clock before deepsleep */
#define  RCC_CFGR_PPRE                 ((u32)0x1F000000)        /*!< PCLK prescaler */

/********************  Bits definition for RCC_RSR register  ******************/
#define  RCC_RSR_SFR                   ((u32)0x00000001)        /*!< Software reset */
#define  RCC_RSR_IWDG                  ((u32)0x00000002)        /*!< IWDG reset */
#define  RCC_RSR_CPU                   ((u32)0x00000008)        /*!< CPU reset */
#define  RCC_RSR_HSE                   ((u32)0x00000010)        /*!< HSE fail reset */
#define  RCC_RSR_PLL                   ((u32)0x00000020)        /*!< PLL fail reset */
#define  RCC_RSR_POR                   ((u32)0x00000040)        /*!< Power reset */
#define  RCC_RSR_PVD                   ((u32)0x00000100)        /*!< PVD low voltage reset */
#define  RCC_RSR_PIN                   ((u32)0x00000400)        /*!< Pin reset */
#define  RCC_RSR_CWR                   ((u32)0x00000800)        /*!< Configuration word reset */
#define  RCC_RSR_RTC                   ((u32)0x00002000)        /*!< RTC reset */
#define  RCC_RSR_WWDG                  ((u32)0x00004000)        /*!< WWDG reset */

/********************  Bits definition for RCC_ASRCR register  ******************/
#define  RCC_ASRCR_KEY                 ((u32)0x0000FFFF)        /*!< Key */

/********************  Bits definition for RCC_RCR register  ******************/
#define  RCC_RCR_PDRE                  ((u32)0x00000100)        /*!< PVD low voltage reset enable */

/******************************************************************************/
/*                                                                            */
/*                            Power Control (PWR)                   	        */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for PWR_PVDR register  ******************/
#define  PWR_PVDR_PVDE                 ((u32)0x00000001)    		/*!< Power voltage detection enable */
#define  PWR_PVDR_PLS                  ((u32)0x000001FE)    		/*!< Power level selection */

/******************************************************************************/
/*                                                                            */
/*               Alternate Function Input/Output Ports (AFIO)                 */
/*                                                                            */
/******************************************************************************/
/****************** Bit definition for AFIO_AFS0 register  ********************/
#define  AFIO_AFS0_IO0            ((u32)0x0000000F)              /*!<Port x pin 0 digtal alternate function  */
#define  AFIO_AFS0_IO1            ((u32)0x000000F0)              /*!<Port x pin 1 digtal alternate function  */
#define  AFIO_AFS0_IO2            ((u32)0x00000F00)              /*!<Port x pin 2 digtal alternate function  */
#define  AFIO_AFS0_IO3            ((u32)0x0000F000)              /*!<Port x pin 3 digtal alternate function  */
#define  AFIO_AFS0_IO4            ((u32)0x000F0000)              /*!<Port x pin 4 digtal alternate function  */
#define  AFIO_AFS0_IO5            ((u32)0x00F00000)              /*!<Port x pin 5 digtal alternate function  */
#define  AFIO_AFS0_IO6            ((u32)0x0F000000)              /*!<Port x pin 6 digtal alternate function  */
#define  AFIO_AFS0_IO7            ((u32)0xF0000000)              /*!<Port x pin 7 digtal alternate function  */

/****************** Bit definition for AFIO_AFS1 register  ********************/
#define  AFIO_AFS1_IO8             ((u32)0x0000000F)             /*!<Port x pin 8 digtal alternate function  */
#define  AFIO_AFS1_IO9             ((u32)0x000000F0)             /*!<Port x pin 9 digtal alternate function  */
#define  AFIO_AFS1_IO10            ((u32)0x00000F00)             /*!<Port x pin 10 digtal alternate function  */
#define  AFIO_AFS1_IO11            ((u32)0x0000F000)             /*!<Port x pin 11 digtal alternate function  */
#define  AFIO_AFS1_IO12            ((u32)0x000F0000)             /*!<Port x pin 12 digtal alternate function  */
#define  AFIO_AFS1_IO13            ((u32)0x00F00000)             /*!<Port x pin 13 digtal alternate function  */
#define  AFIO_AFS1_IO14            ((u32)0x0F000000)             /*!<Port x pin 14 digtal alternate function  */
#define  AFIO_AFS1_IO15            ((u32)0xF0000000)             /*!<Port x pin 15 digtal alternate function  */

/******************************************************************************/
/*                                                                            */
/*                   On-chip Flash Memory Controller (IFMC)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IFMC_CR register  ******************/
#define  IFMC_CR_STAR                   ((u32)0x00000001)        /*!< Start generation */
#define  IFMC_CR_CMD                    ((u32)0x00000006)        /*!< IFMC operation command */
#define  IFMC_CR_WAIT                   ((u32)0x000000E0)        /*!< Instruction fetch wait cycle */
#define  IFMC_CR_MODE                   ((u32)0x00000100)        /*!< IFMC operation mode */
#define  IFMC_CR_AINC                   ((u32)0x00002000)        /*!< Address auto increment control */
#define  IFMC_CR_KEY                    ((u32)0xFFFF0000)        /*!< IFMC key */

/*******************  Bit definition for IFMC_SR register  ******************/
#define  IFMC_SR_WC                     ((u32)0x00000001)        /*!< Write operation complete */
#define  IFMC_SR_PEC                    ((u32)0x00000002)        /*!< Page erase operation complete */
#define  IFMC_SR_CEC                    ((u32)0x00000004)        /*!< Chip erase operation complete */
#define  IFMC_SR_BSY                    ((u32)0x00000008)        /*!< Operation busy */
#define  IFMC_SR_CERR                   ((u32)0x00000010)        /*!< Operation command error */
#define  IFMC_SR_KERR                   ((u32)0x00000020)        /*!< Key error */
#define  IFMC_SR_AERR                   ((u32)0x00000040)        /*!< Address error */

/*******************  Bit definition for IFMC_IE register  ******************/
#define  IFMC_IE_WCIE                   ((u32)0x00000001)        /*!< Write operation complete interrupt enable */
#define  IFMC_IE_PECIE                  ((u32)0x00000002)        /*!< Page erase operation complete interrupt enable */
#define  IFMC_IE_CECIE                  ((u32)0x00000004)        /*!< Chip erase operation complete interrupt enable */
#define  IFMC_IE_CERIE                  ((u32)0x00000010)        /*!< Operation command error interrupt enable */
#define  IFMC_IE_KERIE                  ((u32)0x00000020)        /*!< Key error interrupt enable */
#define  IFMC_IE_AERIE                  ((u32)0x00000040)        /*!< Address error interrupt enable */

/*******************  Bit definition for IFMC_AR register  *******************/
#define  IFMC_AR_AR                     ((u32)0x0000FFFC)        /*!< IFMC words addr */

/*******************  Bit definition for IFMC_DR register  *******************/
#define  IFMC_DR_DR                     ((u32)0xFFFFFFFF)        /*!< IFMC data */

/*******************  Bit definition for IFMC_PSC  register  *******************/
#define  IFMC_PSC_PSC                   ((u32)0x000000FF)        /*!< Prescaler value */

/********************  Bits definition for IFMC_BSR register  ******************/
#define  IFMC_BSR_IAPF                  ((u32)0x00000002)        /*!< IAP Enable Flag */
#define  IFMC_BSR_IVTSC                 ((u32)0x00000004)        /*!< IVTS Enable Ctronl */

/********************  Bits definition for IFMC_IAPAR register  ******************/
#define  IFMC_IAPAR_AR                  ((u32)0xFFFFFFFF)        /*!< IAP address */

/********************  Bits definition for IFMC_IVTSAR register  ******************/
#define  IFMC_IVTSAR_SAR                ((u32)0xFFFFFFFF)        /*!< IVTS Address */

/********************  Bits definition for IFMC_RPT register  ******************/
#define  IFMC_RPSR_PSR                  ((u32)0x00000001)        /*!< Data protection status */

/******************************************************************************/
/*                                                                            */
/*           Universal Asynchronous Receiver Transmitter (UART)      				  */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for UART_DR register  *******************/
#define  UART_DR_DR                       ((u32)0x000001FF)            /*!< UART data */

/******************  Bit definition for UART_CR register  *******************/
#define  UART_CR_WP                       ((u32)0x00000007)        /*!< Word length and parity config */
#define  UART_CR_STOP                     ((u32)0x00000018)        /*!< Stop bit length */
#define  UART_CR_PS                       ((u32)0x00000020)        /*!< parity mode */
#define  UART_CR_LPB                      ((u32)0x00000040)        /*!< loopback mode */
#define  UART_CR_EN                       ((u32)0x00000080)        /*!< UART enable */
#define  UART_CR_RE                       ((u32)0x00000100)        /*!< Receiver enable */
#define  LPUART_CR_CLKS                   ((u32)0x00000E00)        /*!< UART Clock source selection */
#define  UART_CR_DMAE                     ((u32)0x00001000)        /*!< DMA mode enable */
#define  UART_CR_DMATC                    ((u32)0x00006000)        /*!< DMA trigger control */
#define  UART_CR_RXP                      ((u32)0x00010000)        /*!< Receiver polarity control */
#define  UART_CR_TXP                      ((u32)0x00020000)        /*!< Transmitter polarity control */
#define  UART_CR_SLME                     ((u32)0x00100000)        /*!< single-line mode enable */
#define  UART_CR_SLDS                     ((u32)0x00200000)        /*!< single-line direction setting */
#define  UART_CR_MMWU                     ((u32)0x01000000)        /*!< mute mode wakeup method */
#define  UART_CR_MME                      ((u32)0x02000000)        /*!< mute mode wakeup enable */
#define  UART_CR_LPWU                     ((u32)0x04000000)        /*!< Low power mode wakeup method */
#define  LPUART_CR_BSY                    ((u32)0x80000000)        /*!< register busy */

/******************  Bit definition for UART_BRR register  *******************/
#define  UART_BRR_BR                      ((u32)0x0000FFFF)        /*!< Baud rate control  */
#define  LPUART_BRR_SR                    ((u32)0x00030000)        /*!< Sample rate control */

/******************  Bit definition for UART_IE register  *******************/
#define  UART_IE_RXNEI                    ((u32)0x00000001)        /*!< Receive FIFO not empty interrupt enable */
#define  UART_IE_RXHFI                    ((u32)0x00000002)        /*!< Receive FIFO half full interrupt enable */
#define  UART_IE_RXFI                     ((u32)0x00000004)        /*!< Receive FIFO full interrupt enable */
#define  UART_IE_RXCOTI                   ((u32)0x00000008)        /*!< Receive FIFO clear overtime interrupt enable */
#define  UART_IE_IDLEI                    ((u32)0x00000010)        /*!< Idle overtime interrupt enable */
#define  UART_IE_PEI                      ((u32)0x00000020)        /*!< parity error interrupt enable */
#define  UART_IE_FEI                      ((u32)0x00000040)        /*!< frame error interrupt enable */
#define  UART_IE_OVRI                     ((u32)0x00000080)        /*!< Receive FIFO overflow interrupt enable */
#define  UART_IE_TXEI                     ((u32)0x00000100)        /*!< Transmit FIFO empty interrupt enable */
#define  UART_IE_TXHEI                    ((u32)0x00000200)        /*!< Transmit FIFO half empty interrupt enable */
#define  UART_IE_TXFI                     ((u32)0x00000400)        /*!< Transmit FIFO full interrupt enable */
#define  UART_IE_TXOI                     ((u32)0x00000800)        /*!< Transmit end interrupt enable */
#define  UART_IE_LPWUI                    ((u32)0x00002000)        /*!< Low power wakeup interrupt enable */

/******************  Bit definition for UART_SR register  *******************/
#define  UART_SR_RXNE                     ((u32)0x00000001)        /*!< Receive FIFO not empty flag */
#define  UART_SR_RXHF                     ((u32)0x00000002)        /*!< Receive FIFO half full flag */
#define  UART_SR_RXF                      ((u32)0x00000004)        /*!< Receive FIFO full flag */
#define  UART_SR_RXCOT                    ((u32)0x00000008)        /*!< Receive FIFO clear overtime flag */
#define  UART_SR_IDLE                     ((u32)0x00000010)        /*!< Idle overtime interrupt enable */
#define  UART_SR_PE                       ((u32)0x00000020)        /*!< parity error flag */
#define  UART_SR_FE                       ((u32)0x00000040)        /*!< frame error flag */
#define  UART_SR_OVR                      ((u32)0x00000080)        /*!< Receive FIFO overflow flag */
#define  UART_SR_TXE                      ((u32)0x00000100)        /*!< Transmit FIFO empty flag */
#define  UART_SR_TXHE                     ((u32)0x00000200)        /*!< Transmit FIFO half empty flag */
#define  UART_SR_TXF                      ((u32)0x00000400)        /*!< Transmit FIFO full flag */
#define  UART_SR_TXO                      ((u32)0x00000800)        /*!< Transmit end flag */
#define  UART_SR_MMF                      ((u32)0x00001000)        /*!< Mute mode flag */
#define  UART_SR_LPWU                     ((u32)0x00002000)        /*!< Low power wakeup flag */

/******************  Bit definition for UART_TO_TO register  *******************/
#define  UART_TO_TO                       ((u32)0x000000FF)        /*!< timeout*/
#define  LPUART_TO_BSY                    ((u32)0x80000000)        /*!< register busy*/

/******************  Bit definition for UART_TXFR register  *******************/
#define  UART_TXFR_TXFR                   ((u32)0xFFFFFFFF)        /*!< Transmit FIFO reset */
#define  LPUART_TXFR_BSY                  ((u32)0x80000000)        /*!< register busy*/

/******************  Bit definition for UART_RXFR register  *******************/
#define  UART_RXFR_RXFR                   ((u32)0xFFFFFFFF)        /*!< Receive FIFO reset */
#define  LPUART_RXFR_BSY                  ((u32)0x80000000)        /*!< register busy*/

/******************  Bit definition for UART_IMCR register  *******************/
#define  UART_IMCR_IRE                    ((u32)0x00000001)        /*!< Infrared enable */
#define  UART_IMCR_IRPN                   ((u32)0x00000002)        /*!< Infrared polarity control */
#define  UART_IMCR_IRBD                   ((u32)0x00000030)        /*!< Infrared baud rate */

/******************  Bit definition for UART_IMDCR register  *******************/
#define  UART_IMDCR_DUTY               	  ((u32)0x00000FFF)        /*!< Infrared duty cycle */

/******************  Bit definition for UART_AR register  *******************/
#define  UART_AR_AR               	      ((u32)0x000000FF)        /*!< ADDress Register */

/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for ADC_CR1 register  ******************/
#define  ADC_CR1_EN                               ((u32)0x00000001)         /*!< ADC enable */
#define  ADC_CR1_MODE                             ((u32)0x00000002)         /*!< ADC mode */
#define  ADC_CR1_TRIGS                            ((u32)0x0000000C)         /*!< ADC trigger source selection */
#define  ADC_CR1_TIMS                             ((u32)0x000000F0)         /*!< ADC timer trigger source selection */
#define  ADC_CR1_ADVRPS                           ((u32)0x00000300)         /*!< ADC voltage reference positive selection */
#define  ADC_CR1_EOCIE                            ((u32)0x00000400)         /*!< ADC end of conversion interrupt enable */
#define  ADC_CR1_ALIGN                            ((u32)0x00000800)         /*!< ADC ALIGN */
#define  ADC_CR1_SOC                              ((u32)0x00001000)         /*!< ADC start on control */
#define  ADC_CR1_INNS                             ((u32)0x00002000)         /*!< ADC Input negative selection */
#define  ADC_CR1_SCANE                            ((u32)0x00004000)         /*!< ADC scan enable */
#define  ADC_CR1_EOSIE                            ((u32)0x00008000)         /*!< ADC end of scan interrupt enable */
#define  ADC_CR1_CHS                              ((u32)0x001F0000)         /*!< ADC channel selection */
#define  ADC_CR1_BGS                              ((u32)0x00200000)         /*!< ADC bg voltage selection */
#define  ADC_CR1_AVGE                             ((u32)0x02000000)         /*!< ADC Average enable */
#define  ADC_CR1_DMAE                             ((u32)0x10000000)         /*!< ADC DMA enable */
#define  ADC_CR1_EXTS                             ((u32)0x20000000)         /*!< ADC external trigger source selection */

/********************  Bits definition for ADC_CR2 register  ******************/
#define  ADC_CR2_RDTC                             ((u32)0x000000FF)         /*!< ADC ready time control */
#define  ADC_CR2_SMP                              ((u32)0x0000FF00)         /*!< ADC sample time */
#define  ADC_CR2_PSC                              ((u32)0x00FF0000)         /*!< ADC prescaler */
#define  ADC_CR2_AVGT                             ((u32)0x07000000)         /*!< Average times */
#define  ADC_CR2_DFD                              ((u32)0x10000000)         /*!< Delete first data */

/********************  Bits definition for ADC_SR register  ******************/
#define  ADC_SR_RDY                               ((u32)0x00000001)         /*!< ADC ready */
#define  ADC_SR_EOC                               ((u32)0x00000002)         /*!< ADC end of conversion */
#define  ADC_SR_EOS                               ((u32)0x00000004)         /*!< ADC end of scan */

/********************  Bits definition for ADC_DR register  ******************/
#define  ADC_DR_DATA                              ((u32)0x0000FFFF)         /*!< ADC data */

/********************  Bits definition for ADC_SCHR1 register  ******************/
#define  ADC_SCHR1_CH0                            ((u32)0x0000001F)         /*!< ADC scan channel 0 selection */
#define  ADC_SCHR1_CH1                            ((u32)0x000003E0)         /*!< ADC scan channel 1 selection */
#define  ADC_SCHR1_CH2                            ((u32)0x00007C00)         /*!< ADC scan channel 2 selection */
#define  ADC_SCHR1_CH3                            ((u32)0x000F8000)         /*!< ADC scan channel 3 selection */
#define  ADC_SCHR1_CH4                            ((u32)0x01F00000)         /*!< ADC scan channel 4 selection */
#define  ADC_SCHR1_CH5                            ((u32)0x3E000000)         /*!< ADC scan channel 5 selection */

/********************  Bits definition for ADC_SCHR2 register  ******************/
#define  ADC_SCHR2_CH6                            ((u32)0x0000001F)         /*!< ADC scan channel 6 selection */
#define  ADC_SCHR2_CH7                            ((u32)0x000003E0)         /*!< ADC scan channel 7 selection */
#define  ADC_SCHR2_CH8                            ((u32)0x00007C00)         /*!< ADC scan channel 8 selection */
#define  ADC_SCHR2_CH9                            ((u32)0x000F8000)         /*!< ADC scan channel 9 selection */
#define  ADC_SCHR2_CH10                           ((u32)0x01F00000)         /*!< ADC scan channel 10 selection */
#define  ADC_SCHR2_CH11                           ((u32)0x3E000000)         /*!< ADC scan channel 11 selection */

/********************  Bits definition for ADC_SCHR3 register  ******************/
#define  ADC_SCHR3_CH12                           ((u32)0x0000001F)         /*!< ADC scan channel 12 selection */
#define  ADC_SCHR3_CH13                           ((u32)0x000003E0)         /*!< ADC scan channel 13 selection */
#define  ADC_SCHR3_CH14                           ((u32)0x00007C00)         /*!< ADC scan channel 14 selection */
#define  ADC_SCHR3_CH15                           ((u32)0x000F8000)         /*!< ADC scan channel 15 selection */
#define  ADC_SCHR3_CH16                           ((u32)0x01F00000)         /*!< ADC scan channel 16 selection */
#define  ADC_SCHR3_CH17                           ((u32)0x3E000000)         /*!< ADC scan channel 17 selection */

/********************  Bits definition for ADC_SCHR4 register  ******************/
#define  ADC_SCHR4_CH18                           ((u32)0x0000001F)         /*!< ADC scan channel 18 selection */
#define  ADC_SCHR4_CH19                           ((u32)0x000003E0)         /*!< ADC scan channel 19 selection */
#define  ADC_SCHR4_SCNT                           ((u32)0x001F0000)         /*!< ADC scan channel number configuration */

/********************  Bits definition for ADC_BGCR register  ******************/
#define  ADC_BGCR_BGE                             ((u32)0x00001000)         /*!< ADC scan channel 18 selection */
#define  ADC_BGCR_BGOE                            ((u32)0x00002000)        	/*!< ADC scan channel 18 selection */
#define  ADC_BGCR_TRIM                            ((u32)0x003F0000)         /*!< Trim value */
#define  ADC_BGCR_KEY                             ((u32)0xFF000000)         /*!< ADC scan channel 18 selection */

/********************  Bits definition for ADC_SCHDRx register  ******************/
#define  ADC_SCHDRx_DATA                          ((u32)0x0000FFFF)         /*!< ADC scan channel x data */

/******************************************************************************/
/*                                                                            */
/*                   Inter-integrated Circuit Interface (I2C)                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CR register  *******************/
#define  I2C_CR_ACK                         ((u32)0x00000004)        /*!< Acknowledge enable */
#define  I2C_CR_SI                          ((u32)0x00000008)        /*!< I2C status flag */
#define  I2C_CR_STOP                        ((u32)0x00000010)        /*!< Stop generation */
#define  I2C_CR_STAR                        ((u32)0x00000020)        /*!< Start generation */
#define  I2C_CR_EN                          ((u32)0x00000040)        /*!< I2C enable */
#define  I2C_CR_HCT                         ((u32)0x0000FF00)        /*!< High level detection coefficient of time) */
#define  I2C_CR_PSC                         ((u32)0x03FF0000)        /*!< Prescaler */

/*******************  Bit definition for I2C_SR register  *******************/
#define  I2C_SR_SR                          ((u32)0x000000F8)      	 /*!< I2C bus status */

/*******************  Bit definition for I2C_DR register  *******************/
#define  I2C_DR_DR                          ((u32)0x000000FF)        /*!< I2C data */

/*******************  Bit definition for I2C_OAR register  *******************/
#define  I2C_OAR_BC													((u32)0x00000001)        /*!< Broadcast response control */
#define  I2C_OAR_ADDR                       ((u32)0x000000FE)        /*!< I2C addr */

/*******************  Bit definition for I2C_CCR register  *******************/
#define  I2C_CCR_ACK                        ((u32)0x00000004)        /*!< Clear Acknowledge control) */
#define  I2C_CCR_SI                         ((u32)0x00000008)        /*!< Clear I2C interrupt flag */
#define  I2C_CCR_STOP                       ((u32)0x00000010)        /*!< Clear stop generation */
#define  I2C_CCR_STAR                       ((u32)0x00000020)        /*!< Clear start generation */
#define  I2C_CCR_EN                         ((u32)0x00000040)        /*!< I2C disable */
#define  I2C_CCR_HCT                        ((u32)0x0000FF00)        /*!< Clear high level detection time */
#define  I2C_CCR_PSC                        ((u32)0x03FF0000)        /*!< Clear prescaler */

/******************************************************************************/
/*                                                                            */
/*                     Serial Peripheral Interface (SPI)                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define  SPI_CR1_DFF                        ((u32)0x0000000F)         /* Data frame format */
#define  SPI_CR1_CPOL		                		((u32)0x00000040)         /* Clock Polarity */
#define  SPI_CR1_CPHA		                		((u32)0x00000080)         /* Clock Phase */
#define  SPI_CR1_PSC                        ((u32)0x0000FF00)         /* Prescaler */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define  SPI_CR2_LBM				                ((u32)0x00000001)         /* Loopback Mode */
#define  SPI_CR2_EN				                  ((u32)0x00000002)         /* SPI Enable*/
#define  SPI_CR2_MSM			                  ((u32)0x00000004)         /* Master-slave mode */
#define  SPI_CR2_SOD			                  ((u32)0x00000008)         /* SPI slave output disable */

/********************  Bit definition for SPI_DR register  ********************/
#define  SPI_DR_DR                          ((u32)0xFFFF)             /* Data Register */

/********************  Bit definition for SPI_SR1 register  ********************/
#define  SPI_SR1_TXE                        ((u32)0x00000001)         /* Transmit FIFO is empty */
#define  SPI_SR1_TNF                        ((u32)0x00000002)        	/* Transmit FIFO is not full */
#define  SPI_SR1_RXNE                       ((u32)0x00000004)         /* Receive FIFO is not empty */
#define  SPI_SR1_RXF                        ((u32)0x00000008)         /* Receive FIFO is Full */
#define  SPI_SR1_BSY                        ((u32)0x00000010)         /* Busy flag */
#define  SPI_SR1_RXFS                       ((u32)0x00000F00)         /* Rx FIFO size */
#define  SPI_SR1_TXFS                       ((u32)0x0000F000)         /* Tx FIFO size */

/********************  Bit definition for SPI_BR register  ********************/
#define  SPI_BR_BR                          ((u32)0x000000FF)         /* Prescaler factor */

/********************  Bit definition for SPI_IE register  ********************/
#define  SPI_IE_OVRE                        ((u32)0x00000001)         /* Receive FIFO overflow interrupt enable */
#define  SPI_IE_OTE                         ((u32)0x00000002)         /* Receive FIFO over time interrupt enable */
#define  SPI_IE_RXHE                        ((u32)0x00000004)         /* Receive FIFO half full interrupt enable */
#define  SPI_IE_TXHE                        ((u32)0x00000008)         /* Transmit FIFO more than half interrupt enable */

/********************  Bit definition for SPI_SR2 register  ********************/
#define  SPI_SR2_OVR                        ((u32)0x00000001)         /* Receive FIFO overflow error flag */
#define  SPI_SR2_OT                         ((u32)0x00000002)         /* Receive FIFO overtime error flag */
#define  SPI_SR2_RXH                        ((u32)0x00000004)         /* Receive FIFO half full flag */
#define  SPI_SR2_TXH                        ((u32)0x00000008)         /* Transmit FIFO more than half flag */

/********************  Bit definition for SPI_IC register  ********************/
#define  SPI_IC_OVR                       	((u32)0x00000001)         /* Clear receive FIFO overflow error flag */
#define  SPI_IC_OT                          ((u32)0x00000002)         /* Clear receive FIFO overtime error flag */

/*******************  Bit definition for SPI_DCR register  ********************/
#define  SPI_DCR_RXDMAE				       				((u32)0x00000001)         /* Rx DMA request enable */
#define  SPI_DCR_TXDMAE				        			((u32)0x00000002)         /* Tx DMA request enable */
#define  SPI_DCR_DMATC			            		((u32)0x00000004)         /* DMA transfer trigger condition */

/********************  Bit definition for SPI_CSS register  ********************/
#define  SPI_CSS_CSS												((u32)0x00000004)         /* CSS control selection */
#define  SPI_CSS_SWCS			    							((u32)0x00000008)         /* Software control CSS */

/********************  Bit definition for SPI_TXFR register  ********************/
#define  SPI_TXFR_TXFR											((u32)0xFFFFFFFF)         /* Transmit FIFO reset  */

/********************  Bit definition for SPI_RXFR register  ********************/
#define  SPI_RXFR_RXFR											((u32)0xFFFFFFFF)         /* Receive FIFO reset  */

/******************************************************************************/
/*                                                                            */
/*                            Comparators (CMP)                						  	*/
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                            Comparators (CMP)                						  	*/
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CMP_CR1 register  ********************/
#define  CMP_CR1_EN                   ((u32)0x00000001)         /*!< Comparator enable */
#define  CMP_CR1_CRS                  ((u32)0x00000002)         /*!< Comparator result */
#define  CMP_CR1_CNS                  ((u32)0x0000000C) 				/*!< Comparator negative intput selection */
#define  CMP_CR1_DFC                  ((u32)0x00000070)         /*!< Digital filter configuration */
#define  CMP_CR1_CPMS                 ((u32)0x00000080)        	/*!< Comparator power mode selection */
#define  CMP_CR1_OPC                  ((u32)0x00000100)        	/*!< Comparator output polarity control */
#define  CMP_CR1_CPS                  ((u32)0x00007000)        	/*!< Comparator positive input selection */
#define  CMP_CR1_SYNC                 ((u32)0x00010000)					/*!< Comparator output synchronization control */
#define  CMP_CR1_PPC                  ((u32)0x00020000)					/*!< Comparator output PWM polarity control */
#define  CMP_CR1_PWMS                 ((u32)0x00F00000)					/*!< Comparator output PWM selection */

/********************  Bit definition for CMP_IE register  ********************/
#define  CMP_IE_COF                   ((u32)0x00000001)         /*!< Comparator output falling edge interrupt enable */
#define  CMP_IE_COR                   ((u32)0x00000002)         /*!< Comparator output rising edge interrupt enable */
#define  CMP_IE_COFW                  ((u32)0x00000004)         /*!< Comparator output falling edge wake up interrupt enable */
#define  CMP_IE_CORW                  ((u32)0x00000008)         /*!< Comparator output rising edge wake up interrupt enable */

/********************  Bit definition for CMP_SR register  ********************/
#define  CMP_SR_COF                   ((u32)0x00000001)         /*!< Comparator output falling edge flag */
#define  CMP_SR_COR                   ((u32)0x00000002)         /*!< Comparator output rising edge flag */
#define  CMP_SR_COFW                  ((u32)0x00000004)         /*!< Comparator output falling edge wake up flag */
#define  CMP_SR_CORW                  ((u32)0x00000008)         /*!< Comparator output rising edge wake up flag */

/********************  Bit definition for CMP_CR2 register  ********************/
#define  CMP_CR2_DELAY	              ((u32)0x000007FF)         /*!< Comparator Initialization delay time */

/******************************************************************************/
/*                                                                            */
/*                    Digital to Analog Converters (LDAC)                			*/
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for LDAC_CR register  *******************/
#define  LDAC_CR_DATA								  ((u32)0x0000007F)				  /*!< LDAC data */
#define  LDAC_CR_EN									  ((u32)0x00000100)				  /*!< LDAC enable */
#define  LDAC_CR_OE									  ((u32)0x00000200)				  /*!< LDAC output enable */ 

/******************************************************************************/
/*                                                                            */
/*                      Operational Amplifiers (OPA)                	        */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for OPA_CR1 register  *******************/
#define  OPA_CR1_TRIM0									((u32)0x0000007F)       /*!< Trim value */
#define  OPA_CR1_TRIM1									((u32)0x00007F00)       /*!< Trim value */
#define  OPA_CR1_TRIM2									((u32)0x007F0000)       /*!< Trim value */
#define  OPA_CR1_TRIM3									((u32)0x7F000000)       /*!< Trim value */


/*******************  Bit definition for OPA_CR2 register  *******************/
#define  OPA_CR2_OPA0E									((u32)0x00000001)       /*!< Opamp0 enable */
#define  OPA_CR2_OPA1E									((u32)0x00000002)       /*!< Opamp1 enable */
#define  OPA_CR2_OPA2E									((u32)0x00000004)       /*!< Opamp2 enable */
#define  OPA_CR2_OPA3E									((u32)0x00000008)       /*!< Opamp3 enable */
#define  OPA_CR2_TM0E                   ((u32)0x00000100)       /*!< Opamp0 trim mode enable */
#define  OPA_CR2_TM1E                   ((u32)0x00000200)       /*!< Opamp1 trim mode enable */
#define  OPA_CR2_TM2E                   ((u32)0x00000400)       /*!< Opamp2 trim mode enable */
#define  OPA_CR2_TM3E                   ((u32)0x00000800)       /*!< Opamp3 trim mode enable */
#define  OPA_CR2_KEY                    ((u32)0x00FF0000)       /*!< Opamp3 trim mode enable */

/******************************************************************************/
/*                                                                            */
/*                           Advanced Timer (TIM)                             */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_SR register  *******************/
#define  TIM_SR_ARF                      ((u32)0x00000001)       	   /*!< auto reload flag */
#define  TIM_SR_OC1F                     ((u32)0x00000002)      		 /*!< output compare 1 flag */
#define  TIM_SR_OC2F                     ((u32)0x00000004)      		 /*!< output compare 2 flag */
#define  TIM_SR_OC3F                     ((u32)0x00000008)      		 /*!< output compare 3 flag */
#define  TIM_SR_OC4F                     ((u32)0x00000010)      		 /*!< output compare 4 flag */
#define  TIM_SR_IC1R                     ((u32)0x00000020)       		 /*!< input capture 1 rising edge flag */
#define  TIM_SR_IC1F                     ((u32)0x00000040)      		 /*!< input capture 1 falling edge flag */
#define  TIM_SR_IC2R                     ((u32)0x00000080)       		 /*!< input capture 2 rising edge flag */
#define  TIM_SR_IC2F                     ((u32)0x00000100)       		 /*!< input capture 2 falling edge flag */
#define  TIM_SR_IC3R                     ((u32)0x00000200)      		 /*!< input capture 3 rising edge flag */
#define  TIM_SR_IC3F                     ((u32)0x00000400)       		 /*!< input capture 3 falling edge flag */
#define  TIM_SR_IC4R                     ((u32)0x00000800)       		 /*!< input capture 4 rising edge flag */
#define  TIM_SR_IC4F                     ((u32)0x00001000)       		 /*!< input capture 4 falling edge flag */
#define  TIM_SR_BIF                      ((u32)0x00002000)       		 /*!< Break input flag */
#define  TIM_SR_TIF                      ((u32)0x00004000)       		 /*!< Trigger input flag */
#define  TIM_SR_UF                       ((u32)0x00008000)       		 /*!< update flag */
#define  TIM_SR_COMF                     ((u32)0x00010000)       	   /*!< Com event flag */
#define  LPTIM_SR_ARRUF                  ((u32)0x00010000)           /*!< ARR update completed flag      */
#define  LPTIM_SR_OCR1UF                 ((u32)0x00020000)           /*!< OCR1 update completed flag      */
#define  LPTIM_SR_DOWN                   ((u32)0x00040000)           /*!< Counter diredtion change up to down      */
#define  LPTIM_SR_UP                     ((u32)0x00080000)           /*!< Counter diredtion change down to up      */
#define  LPTIM_SR_BSY                    ((u32)0x80000000)           /*!< Register busy      */

/*******************  Bit definition for TIM_CR1 register  *******************/
#define  TIM_CR1_EN                      ((u32)0x00000001)       		 /*!< Counter enable */
#define  TIM_CR1_UG                      ((u32)0x00000002)       		 /*!< Update generation */
#define  TIM_CR1_CLKS                    ((u32)0x00000004)       		 /*!< TIM internal clock source selection */
#define  TIM_CR1_SAMPSC                  ((u32)0x00000070)       		 /*!< Sampling clock division */
#define  TIM_CR1_DBGE                    ((u32)0x00000100)       		 /*!< TIM debug */
#define  TIM_CR1_DIR                     ((u32)0x00000200)       		 /*!< Direction */
#define  TIM_CR1_CMS                     ((u32)0x00000400)       		 /*!< Center-aligned mode selection */
#define  TIM_CR1_CPC                     ((u32)0x00000800)       		 /*!< Compare preloaded control */
#define  TIM_CR1_BSY                     ((u32)0x00008000)       		 /*!< LPTIM &TIM4 Control regsister busy */
#define  LPTIM_CR1_CLKS                  ((u32)0x00070000)           /*!< LPTIM internal clock source selection*/

/*******************  Bit definition for TIM_MSCR register  *******************/
#define  TIM_MSCR_TIS                    ((u32)0x0000000F)           /*!< Trigger input selection */
#define  TIM_MSCR_SMS                    ((u32)0x00000070)           /*!< Slave mode selection */
#define  TIM_MSCR_TIE                    ((u32)0x00000080)           /*!< Trigger interrupt enable */
#define  TIM_MSCR_ETF                    ((u32)0x00000700)           /*!< External trigger filter */
#define  TIM_MSCR_ETPSC                  ((u32)0x00003000)           /*!< External trigger prescaler */
#define  TIM_MSCR_ECE                    ((u32)0x00004000)           /*!< External clock enable */
#define  TIM_MSCR_ETP                    ((u32)0x00008000)           /*!< External trigger polarity */
#define  TIM_MSCR_TOS                    ((u32)0x000F0000)           /*!< Trigger output selection */
#define  TIM_MSCR_SYNC                   ((u32)0x00100000)           /*!< TIM synchronization enable */
#define  LPTIM_MSCR_STE                  ((u32)0x01000000)           /*!< Single trigger enable */
#define  LPTIM_MSCR_TIMOUTE              ((u32)0x02000000)           /*!< Timeout enable */
#define  LPTIM_MSCR_TPS                  ((u32)0x0C000000)           /*!< Trigger polarity selection */
#define  LPTIM_MSCR_SWTC                 ((u32)0x10000000)           /*!< Software trigger control */

/*******************  Bit definition for TIM_ITARR register  *******************/
#define  TIM_ITARR_ITARR                 ((u32)0x0000000F)           /*!< TIM interrupt auto reload */

/*******************  Bit definition for TIM_ITCNT register  *******************/
#define  TIM_ITCNT_ITCNT                 ((u32)0x0000000F)           /*!< TIM interrupt counter value */

/*******************  Bit definition for TIM_PSC register  *******************/
#define  TIM_PSC_PSC                     ((u32)0x0000FFFF)           /*!< Prescaler value */

/*******************  Bit definition for TIM_CNT register  *******************/
#define  TIM_CNT_CNT                     ((u32)0x0000FFFF)           /*!< Counter value */

/*******************  Bit definition for TIM_CR2 register  *******************/
#define  TIM_CR2_ARI                     ((u32)0x000000001)       	 /*!< Auto reload interrupt enable */
#define  TIM_CR2_OC1I                    ((u32)0x000000002)       	 /*!< output compare 1 interrupt enable */
#define  TIM_CR2_OC2I                    ((u32)0x000000004)       	 /*!< output compare 2 interrupt enable */
#define  TIM_CR2_OC3I                    ((u32)0x000000008)       	 /*!< output compare 3 interrupt enable */
#define  TIM_CR2_OC4I                    ((u32)0x000000010)       	 /*!< output compare 4 interrupt enable */
#define  TIM_CR2_OPM                     ((u32)0x000000020)       	 /*!< One-pulse mode */
#define  TIM_CR2_UIE                     ((u32)0x000000040)       	 /*!< update interrupt enable */
#define  TIM_CR2_COMIE                   ((u32)0x000000080)       	 /*!< Com interrupt enable */
#define  LPTIM_CR2_ARRUIE                ((u32)0x000010000)   			 /*!< ARR update completed interrupt enable */
#define  LPTIM_CR2_OCR1UIE               ((u32)0x000020000)   			 /*!< OCR1 update completed interrupt enable */
#define  LPTIM_CR2_DOWNIE                ((u32)0x000040000)   			 /*!< Counter direction change to down interrupt enable */
#define  LPTIM_CR2_UPIE                  ((u32)0x000080000)   			 /*!< Counter direction change to up interrupt enable */

/*******************  Bit definition for TIM_ARR register  *******************/
#define  TIM_ARR_ARR                     ((u32)0x0000FFFF)           /*!< Auto reload value */

/*******************  Bit definition for TIM_OCR1 register  *******************/
#define  TIM_OCR1_OCR                    ((u32)0x0000FFFF)           /*!< output compare 1 value */

/*******************  Bit definition for TIM_OCR2 register  *******************/
#define  TIM_OCR2_OCR                    ((u32)0x0000FFFF)           /*!< output compare 2 value */

/*******************  Bit definition for TIM_OCR3 register  *******************/
#define  TIM_OCR3_OCR                    ((u32)0x0000FFFF)           /*!< output compare 3 value */

/*******************  Bit definition for TIM_OCR4 register  *******************/
#define  TIM_OCR4_OCR                    ((u32)0x0000FFFF)           /*!< output compare 4 value */

/*******************  Bit definition for TIM_CAPR1 register  *******************/
#define  TIM_CAPR1_IC1R                  ((u32)0x00000001)       /*!< input capture 1 rising capture enable */
#define  TIM_CAPR1_IC1F                  ((u32)0x00000002)       /*!< input capture 1 falling capture enable */
#define  TIM_CAPR1_IC1RC                 ((u32)0x00000004)       /*!< input capture 1 capture reset counter enable */
#define  TIM_CAPR1_IC1I                  ((u32)0x00000008)       /*!< input capture 1 interrupt enable */
#define  TIM_CAPR1_IC2R                  ((u32)0x00000010)       /*!< input capture 2 rising capture enable */
#define  TIM_CAPR1_IC2F                  ((u32)0x00000020)       /*!< input capture 2 falling capture enable */
#define  TIM_CAPR1_IC2RC                 ((u32)0x00000040)       /*!< input capture 2 capture reset counter enable */
#define  TIM_CAPR1_IC2I                  ((u32)0x00000080)       /*!< input capture 2 interrupt enable */
#define  TIM_CAPR1_IC3R                  ((u32)0x00000100)       /*!< input capture 3 rising capture enable */
#define  TIM_CAPR1_IC3F                  ((u32)0x00000200)       /*!< input capture 3 falling capture enable */
#define  TIM_CAPR1_IC3RC                 ((u32)0x00000400)       /*!< input capture 3 capture reset counter enable */
#define  TIM_CAPR1_IC3I                  ((u32)0x00000800)       /*!< input capture 3 interrupt enable */
#define  TIM_CAPR1_IC4R                  ((u32)0x00001000)       /*!< input capture 4 rising capture enable */
#define  TIM_CAPR1_IC4F                  ((u32)0x00002000)       /*!< input capture 4 falling capture enable */
#define  TIM_CAPR1_IC4RC                 ((u32)0x00004000)       /*!< input capture 4 capture reset counter enable */
#define  TIM_CAPR1_IC4I                  ((u32)0x00008000)       /*!< input capture 4 interrupt enable */
#define  TIM_CAPR1_IC1S                  ((u32)0x00070000)       /*!< input capture 1 source selection */
#define  TIM_CAPR1_ICS1S                 ((u32)0x00080000)       /*!< ICS1 selection */
#define  TIM_CAPR1_IC2S                  ((u32)0x00700000)       /*!< input capture 2 source selection */
#define  TIM_CAPR1_IC3S                  ((u32)0x07000000)       /*!< input capture 3 source selection */
#define  TIM_CAPR1_IC4S                  ((u32)0x70000000)       /*!< input capture 4 source selection */

/*******************  Bit definition for TIM_CAPR2 register  *******************/
#define  TIM_CAPR2_IC1FR                 ((u32)0x00000007)       /*!< Input capture 1 filter */
#define  TIM_CAPR2_IC1PSC                ((u32)0x00000030)       /*!< Input capture 1 prescaler */
#define  TIM_CAPR2_IC2FR                 ((u32)0x00000700)       /*!< Input capture 2 filter */
#define  TIM_CAPR2_IC2PSC                ((u32)0x00003000)       /*!< Input capture 2 prescaler */
#define  TIM_CAPR2_IC3FR                 ((u32)0x00070000)       /*!< Input capture 3 filter */
#define  TIM_CAPR2_IC3PSC                ((u32)0x00300000)       /*!< Input capture 3 prescaler */
#define  TIM_CAPR2_IC4FR                 ((u32)0x07000000)       /*!< Input capture 4 filter */
#define  TIM_CAPR2_IC4PSC                ((u32)0x30000000)       /*!< Input capture 4 prescaler */

/*******************  Bit definition for TIM_ICR1 register  *******************/
#define  TIM_ICR1_ICR                    ((u32)0x0000FFFF)       /*!< input capture 1 value */

/*******************  Bit definition for TIM_ICR2 register  *******************/
#define  TIM_ICR2_ICR                    ((u32)0x0000FFFF)       /*!< input capture 2 value */

/*******************  Bit definition for TIM_ICR3 register  *******************/
#define  TIM_ICR3_ICR                    ((u32)0x0000FFFF)       /*!< input capture 3 value */

/*******************  Bit definition for TIM_ICR4 register  *******************/
#define  TIM_ICR4_ICR                    ((u32)0x0000FFFF)       /*!< input capture 4 value */

/*******************  Bit definition for TIM_OCMR register  *******************/
#define  TIM_OCMR_OC1M                   ((u32)0x00000007)       /*!< output compare 1 mode */
#define  TIM_OCMR_OC1CE                  ((u32)0x00000008)       /*!< output compare 1 clear enable */
#define  TIM_OCMR_OC2M                   ((u32)0x00000070)       /*!< output compare 2 mode */
#define  TIM_OCMR_OC2CE                  ((u32)0x00000080)       /*!< output compare 2 clear enable */
#define  TIM_OCMR_OC3M                   ((u32)0x00000700)       /*!< output compare 3 mode */
#define  TIM_OCMR_OC3CE                  ((u32)0x00000800)       /*!< output compare 3 clear enable */
#define  TIM_OCMR_OC4M                   ((u32)0x00007000)       /*!< output compare 4 mode */
#define  TIM_OCMR_OC4CE                  ((u32)0x00008000)       /*!< output compare 4 clear enable */
#define  TIM_OCMR_OIS1              		 ((u32)0x00010000)       /*!< Output Idle state 1 */
#define  TIM_OCMR_OIS2                 	 ((u32)0x00020000)       /*!< Output Idle state 2 */
#define  TIM_OCMR_OIS3                 	 ((u32)0x00040000)       /*!< Output Idle state 3 */
#define  TIM_OCMR_OIS4                   ((u32)0x00080000)       /*!< Output Idle state 4 */
#define  TIM_OCMR_OIS1N           			 ((u32)0x00100000)       /*!< Output Idle state 1 complementary */
#define  TIM_OCMR_OIS2N             		 ((u32)0x00200000)       /*!< Output Idle state 2 complementary */
#define  TIM_OCMR_OIS3N             		 ((u32)0x00400000)       /*!< Output Idle state 3 complementary */
#define  TIM_OCMR_OIS4N             		 ((u32)0x00800000)       /*!< Output Idle state 4 complementary */
#define  TIM_OCMR_OC1NE             		 ((u32)0x01000000)       /*!< Compare output 1 complementary output enable */
#define  TIM_OCMR_OC2NE              		 ((u32)0x02000000)       /*!< Compare output 2 complementary output enable */
#define  TIM_OCMR_OC3NE                  ((u32)0x04000000)       /*!< Compare output 3 complementary output enable */
#define  TIM_OCMR_OC4NE              		 ((u32)0x08000000)       /*!< Compare output 4 complementary output enable */
#define  TIM_OCMR_OC1E             		   ((u32)0x10000000)       /*!< Compare output 1 output enable */
#define  TIM_OCMR_OC2E              		 ((u32)0x20000000)       /*!< Compare output 2 output enable */
#define  TIM_OCMR_OC3E               		 ((u32)0x40000000)       /*!< Compare output 3 output enable */
#define  TIM_OCMR_OC4E              		 ((u32)0x80000000)       /*!< Compare output 4 output enable */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DT                     ((u32)0x00000FFF)       /*!< Dead-time value */
#define  TIM_BDTR_BKE                    ((u32)0x00010000)       /*!< Break enable */
#define  TIM_BDTR_BKP                    ((u32)0x00020000)       /*!< Break polarity */
#define  TIM_BDTR_BKI                    ((u32)0x00040000)       /*!< Break interrupt enable */
#define  TIM_BDTR_BKSC                   ((u32)0x00080000)       /*!< Break software control enable */
#define  TIM_BDTR_BKIC                   ((u32)0x01000000)       /*!< break input control */

/*******************  Bit definition for TIM_CR3 register  *******************/
#define  TIM_CR3_CC1P                    ((u32)0x00000001)       /*!< Capture/Compare 1 output polarity */
#define  TIM_CR3_C1NP                    ((u32)0x00000002)       /*!< Compare 1 complementary output polarity */
#define  TIM_CR3_CC2P                    ((u32)0x00000010)       /*!< Capture/Compare 2 output polarity */
#define  TIM_CR3_C2NP                    ((u32)0x00000020)       /*!< Compare 2 complementary output polarity */
#define  TIM_CR3_CC3P                    ((u32)0x00000100)       /*!< Capture/Compare 3 output polarity */
#define  TIM_CR3_C3NP                    ((u32)0x00000200)       /*!< Compare 3 complementary output polarity */
#define  TIM_CR3_CC4P                    ((u32)0x00001000)       /*!< Capture/Compare 4 output polarity */
#define  TIM_CR3_C4NP                    ((u32)0x00002000)       /*!< Compare 4 complementary output polarity */

#define  LPTIM_CR3_CC1P                  ((u32)0x00000001)       /*!< Capture/Compare 1 output polarity */
#define  LPTIM_CR3_C2P                   ((u32)0x00000010)       /*!< Capture 2 output polarity */
/*******************  Bit definition for TIM_TDCR register  *******************/
#define  TIM_TDCR_ARDE                   ((u32)0x00000001)       /*!< auto reload DMA request enable */
#define  TIM_TDCR_OC1DE                  ((u32)0x00000002)       /*!< output compare 1 DMA request enable */
#define  TIM_TDCR_OC2DE                  ((u32)0x00000004)       /*!< output compare 2 DMA request enable */
#define  TIM_TDCR_OC3DE                  ((u32)0x00000008)       /*!< output compare 3 DMA request enable */
#define  TIM_TDCR_OC4DE                  ((u32)0x00000010)     	 /*!< output compare 4 DMA request enable */
#define  TIM_TDCR_IC1RDE                 ((u32)0x00000020)       /*!< input capture 1 rising edge DMA request enable */
#define  TIM_TDCR_IC1FDE                 ((u32)0x00000040)     	 /*!< input capture 1 falling edge DMA request enable */
#define  TIM_TDCR_IC2RDE                 ((u32)0x00000080)     	 /*!< input capture 2 rising edge DMA request enable */
#define  TIM_TDCR_IC2FDE                 ((u32)0x00000100)     	 /*!< input capture 2 falling edge DMA request enable */
#define  TIM_TDCR_IC3RDE                 ((u32)0x00000200)     	 /*!< input capture 3 rising edge DMA request enable */
#define  TIM_TDCR_IC3FDE                 ((u32)0x00000400)     	 /*!< input capture 3 falling edge DMA request enable */
#define  TIM_TDCR_IC4RDE                 ((u32)0x00000800)     	 /*!< input capture 4 rising edge DMA request enable */
#define  TIM_TDCR_IC4FDE                 ((u32)0x00001000)     	 /*!< input capture 4 falling edge DMA request enable */
#define  TIM_TDCR_TDE                    ((u32)0x00004000)     	 /*!< trigger DMA request enable */
#define  TIM_TDCR_UDE                    ((u32)0x00008000)     	 /*!< update DMA request enable */
#define  TIM_TDCR_COMDE                  ((u32)0x00010000)     	 /*!< Com event DMA request enable */

/*******************  Bit definition for TIM_TACR register  *******************/
#define  TIM_TACR_OC1UE                  ((u32)0x00000001)       /*!< OC1U trigger ADC enable */
#define  TIM_TACR_OC1DE                  ((u32)0x00000002)       /*!< OC1D trigger ADC enable */
#define  TIM_TACR_OC2UE                  ((u32)0x00000004)       /*!< OC2U trigger ADC enable */
#define  TIM_TACR_OC2DE                  ((u32)0x00000008)       /*!< OC2D trigger ADC enable */
#define  TIM_TACR_OC3UE                  ((u32)0x00000010)       /*!< OC3U trigger ADC enable */
#define  TIM_TACR_OC3DE                  ((u32)0x00000020)       /*!< OC3D trigger ADC enable */
#define  TIM_TACR_OC4UE                  ((u32)0x00000040)       /*!< OC4U trigger ADC enable */
#define  TIM_TACR_OC4DE                  ((u32)0x00000080)       /*!< OC4D trigger ADC enable */
#define  TIM_TACR_UOAE                   ((u32)0x00000100)       /*!< UpOVF trigger ADC enable */
#define  TIM_TACR_DOAE                   ((u32)0x00000200)       /*!< DownOVF trigger ADC enable */
#define  TIM_TACR_TAE                    ((u32)0x00000400)       /*!< TEV trigger ADC enable */
#define  TIM_TACR_IC1RAE                 ((u32)0x00010000)       /*!< IC1R trigger ADC enable */
#define  TIM_TACR_IC1FAE                 ((u32)0x00020000)       /*!< IC1F trigger ADC enable */
#define  TIM_TACR_IC2RAE                 ((u32)0x00040000)       /*!< IC2R trigger ADC enable */
#define  TIM_TACR_IC2FAE                 ((u32)0x00080000)       /*!< IC2F trigger ADC enable */
#define  TIM_TACR_IC3RAE                 ((u32)0x00100000)       /*!< IC3R trigger ADC enable */
#define  TIM_TACR_IC3FAE                 ((u32)0x00200000)       /*!< IC3F trigger ADC enable */
#define  TIM_TACR_IC4RAE                 ((u32)0x00400000)       /*!< IC4R trigger ADC enable */
#define  TIM_TACR_IC4FAE                 ((u32)0x00800000)       /*!< IC4F trigger ADC enable */
/*******************  Bit definition for TIM_BKICR register  *******************/
#define  TIM_BKICR_BKINE                 ((u32)0x00000001)       /*!< BKIN Break input enable */
#define  TIM_BKICR_PVDE                  ((u32)0x00000010)       /*!< PVD Break input enable */
#define  TIM_BKICR_SWE                   ((u32)0x00000020)       /*!< SW Break input enable */
#define  TIM_BKICR_CMP0E                 ((u32)0x00000100)       /*!< CMP0 Break input enable */
#define  TIM_BKICR_CMP1E                 ((u32)0x00000200)       /*!< CMP1 Break input enable */
#define  TIM_BKICR_CMP2E                 ((u32)0x00000400)       /*!< CMP2 Break input enable */
#define  TIM_BKICR_CMP3E                 ((u32)0x00000800)       /*!< CMP3 Break input enable */

/******************************************************************************/
/*                                                                            */
/*                     Cyclic Redundancy Check (CRC)                          */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_CR register  *******************/
#define  CRC_CR_EN                           ((u32)0x00000001)        		/*!< CRC Enable */
#define  CRC_CR_CRS                          ((u32)0x00000002)        		/*!< CRC reset control */
#define  CRC_CR_CIS                          ((u32)0x00000004)        		/*!< CRC input select */
#define  CRC_CR_CISN                         ((u32)0x00000008)        		/*!< CRC input bit sequence reversal */
#define  CRC_CR_CBN                          ((u32)0x00000010)        		/*!< CRC input byte sequence reversal */
#define  CRC_CR_COSN                         ((u32)0x00000020)       		  /*!< CRC output bit sequence reversal */

/*******************  Bit definition for CRC_SEED register  *******************/
#define  CRC_SEED_SEED                       ((u32)0x0000FFFF)        		/*!< CRC SEED */

/*******************  Bit definition for CRC_POLY register  *******************/
#define  CRC_PLOY_PLOY                       ((u32)0x0000FFFF)        		/*!< CRC POLY */

/*******************  Bit definition for CRC_DIN register  *******************/
#define  CRC_DIN_DIN                         ((u32)0x0000FFFF)       		  /*!< CRC data input */

/*******************  Bit definition for CRC_DOUT register  *******************/
#define  CRC_DOUT_DOUT                       ((u32)0x0000FFFF)        		/*!< CRC data output data output */

/******************************************************************************/
/*                                                                            */
/*                        Independent WatchDog (IWDG)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WDG_RLR register  *******************/
#define  IWDG_RLR_RL                         ((u32)0xFFFFFFFF)        /*!< Reload value */

/*******************  Bit definition for WDG_Count register  *******************/
#define  IWDG_CNT_CNT                        ((u32)0xFFFFFFFF)        /*!< Counter value */

/*******************  Bit definition for WDG_CR register  *******************/
#define  IWDG_CR_EN                          ((u32)0x00000001)        /*!< Enable */
#define  IWDG_CR_RSTE                        ((u32)0x00000002)       	/*!< Reset enable */
#define  IWDG_CR_DBGE                        ((u32)0x00000004)       	/*!< IWDG debug Control */
#define  IWDG_CR_CLKS                        ((u32)0x00000008)       	/*!< IWDG clock source selection */

/*******************  Bit definition for WDG_KR register  *******************/
#define  IWDG_KR_KEY                         ((u32)0xFFFFFFFF)       	/*!< key value */

/*******************  Bit definition for WDG_SR register  *******************/
#define  IWDG_SR_HDF                         ((u32)0x00000001)       	/*!< hungry dog flag */

/*******************  Bit definition for WDG_KR register  ********************/
#define  IWDG_LOCK_KEY                       ((u32)0xFFFFFFFF)        /*!< lock key */
#define  IWDG_LOCK_LOCK                      ((u32)0x00000001)        /*!< lock status */

/******************************************************************************/
/*                                                                            */
/*                                   BEEP                                 		*/
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for BEEP_CR register  ********************/
#define  BEEP_CR_EN                          ((u32)0x00000001)       	 /*!< BEEP enable */
#define  BEEP_CR_CLKS                        ((u32)0x00000002)       	 /*!< BEEP clock source selection */
#define  BEEP_CR_DIV                         ((u32)0x0000FF00)       	 /*!< BEEP Clock divider */

/*******************  Bit definition for BEEP_HCR register ********************/
#define  BEEP_HCR_BEEPE                      ((u32)0x00000001)				 /*!< BEEP1 High sink enable */

/******************************************************************************/
/*                                                                            */
/*                       Direct Memory Access (DMA)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DMA_CxSBAR register  ********************/
#define  DMA_CxSBAR_SBA                     ((u32)0xFFFFFFFF)           /*!< DMA source base address */
/*******************  Bit definition for DMA_CxDBAR register  ********************/
#define  DMA_CxDBAR_DBA                     ((u32)0xFFFFFFFF)           /*!< DMA destination base address */
/*******************  Bit definition for DMA_CxNDTR register  ********************/
#define  DMA_CxNDTR_NDT                     ((u32)0x0000FFFF)           /*!< Number of data to transfer */
/*******************  Bit definition for DMA_CxCR register  ********************/
#define  DMA_CCR_EN                         ((u32)0x00000001)           /*!< DMA channel enable */
#define  DMA_CCR_SINC                       ((u32)0x00000002)          	/*!< Source address increment control */
#define  DMA_CCR_DINC                       ((u32)0x00000004)           /*!< Destination address increment control */
#define  DMA_CCR_SSIZE                      ((u32)0x00000018)           /*!< Source data size  */
#define  DMA_CCR_BURST                      ((u32)0x00000060)           /*!< Burst transfer configuration */
#define  DMA_CCR_DSIZE                      ((u32)0x00000180)           /*!< Destination data size */
#define  DMA_CCR_CPC                        ((u32)0x00000600)           /*!< Channel priority config */
#define  DMA_CCR_DIR                        ((u32)0x00003800)           /*!< Direction */
#define  DMA_CCR_CIRC                       ((u32)0x00004000)           /*!< Circular mode */
/*******************  Bit definition for DMA_CxCSAR register  ********************/
#define  DMA_CxCSAR_CSA                     ((u32)0xFFFFFFFF)           /*!< DMA current source address */
/*******************  Bit definition for DMA_CxCDAR register  ********************/
#define  DMA_CxCDAR_CDA                     ((u32)0xFFFFFFFF)           /*!< DMA current destination address */
/*******************  Bit definition for DMA_CxCNTR register  ********************/
#define  DMA_CxCNTR_CNT                     ((u32)0x0000FFFF)           /*!< DMA Counter value */
/*******************  Bit definition for DMA_IER register  ********************/
#define  DMA_IER_TC0E                       ((u32)0x00000001)           /*!< DMA channel 0 transfer complete interrupt enable */
#define  DMA_IER_TC1E                       ((u32)0x00000002)           /*!< DMA channel 1 transfer complete interrupt enable */
#define  DMA_IER_TC2E                       ((u32)0x00000004)           /*!< DMA channel 2 transfer complete interrupt enable */
#define  DMA_IER_TC3E                       ((u32)0x00000008)           /*!< DMA channel 3 transfer complete interrupt enable */
#define  DMA_IER_TC4E                       ((u32)0x00000010)           /*!< DMA channel 4 transfer complete interrupt enable */
#define  DMA_IER_TC5E                       ((u32)0x00000020)           /*!< DMA channel 5 transfer complete interrupt enable */
#define  DMA_IER_TE0E                       ((u32)0x00000100)           /*!< DMA channel 0 transfer error interrupt enable */
#define  DMA_IER_TE1E                       ((u32)0x00000200)           /*!< DMA channel 1 transfer error interrupt enable */
#define  DMA_IER_TE2E                       ((u32)0x00000400)           /*!< DMA channel 2 transfer error interrupt enable */
#define  DMA_IER_TE3E                       ((u32)0x00000800)           /*!< DMA channel 3 transfer error interrupt enable */
#define  DMA_IER_TE4E                       ((u32)0x00001000)           /*!< DMA channel 4 transfer error interrupt enable */
#define  DMA_IER_TE5E                       ((u32)0x00002000)           /*!< DMA channel 5 transfer error interrupt enable */
#define  DMA_IER_TH0E                       ((u32)0x00010000)           /*!< DMA channel 0 transfer over half interrupt enable */
#define  DMA_IER_TH1E                       ((u32)0x00020000)           /*!< DMA channel 1 transfer over half interrupt enable */
#define  DMA_IER_TH2E                       ((u32)0x00040000)           /*!< DMA channel 2 transfer over half interrupt enable */
#define  DMA_IER_TH3E                       ((u32)0x00080000)           /*!< DMA channel 3 transfer over half interrupt enable */
#define  DMA_IER_TH4E                       ((u32)0x00100000)           /*!< DMA channel 4 transfer over half interrupt enable */
#define  DMA_IER_TH5E                       ((u32)0x00200000)           /*!< DMA channel 5 transfer over half interrupt enable */

/*******************  Bit definition for DMA_ICR register  ********************/
#define  DMA_ICR_C0TCF                      ((u32)0x00000001)           /*!< DMA channel 0 clear transfer complete interrupt flag */
#define  DMA_ICR_C1TCF                      ((u32)0x00000002)           /*!< DMA channel 1 clear transfer complete interrupt flag */
#define  DMA_ICR_C2TCF                      ((u32)0x00000004)           /*!< DMA channel 2 clear transfer complete interrupt flag */
#define  DMA_ICR_C3TCF                      ((u32)0x00000008)           /*!< DMA channel 3 clear transfer complete interrupt flag */
#define  DMA_ICR_C4TCF                      ((u32)0x00000010)           /*!< DMA channel 4 clear transfer complete interrupt flag */
#define  DMA_ICR_C5TCF                      ((u32)0x00000020)           /*!< DMA channel 5 clear transfer complete interrupt flag */
#define  DMA_ICR_C0TEF                      ((u32)0x00000100)           /*!< DMA channel 0 clear transfer error interrupt flag */
#define  DMA_ICR_C1TEF                      ((u32)0x00000200)           /*!< DMA channel 1 clear transfer error interrupt flag */
#define  DMA_ICR_C2TEF                      ((u32)0x00000400)           /*!< DMA channel 2 clear transfer error interrupt flag */
#define  DMA_ICR_C3TEF                      ((u32)0x00000800)           /*!< DMA channel 3 clear transfer error interrupt flag */
#define  DMA_ICR_C4TEF                      ((u32)0x00001000)           /*!< DMA channel 4 clear transfer error interrupt flag */
#define  DMA_ICR_C5TEF                      ((u32)0x00002000)           /*!< DMA channel 5 clear transfer error interrupt flag */
#define  DMA_ICR_C0THF                      ((u32)0x00010000)           /*!< DMA channel 0 clear transfer over half interrupt flag */
#define  DMA_ICR_C1THF                      ((u32)0x00020000)           /*!< DMA channel 1 clear transfer over half interrupt flag */
#define  DMA_ICR_C2THF                      ((u32)0x00040000)           /*!< DMA channel 2 clear transfer over half interrupt flag */
#define  DMA_ICR_C3THF                      ((u32)0x00080000)           /*!< DMA channel 3 clear transfer over half interrupt flag */
#define  DMA_ICR_C4THF                      ((u32)0x00100000)           /*!< DMA channel 4 clear transfer over half interrupt flag */
#define  DMA_ICR_C5THF                      ((u32)0x00200000)           /*!< DMA channel 5 clear transfer over half interrupt flag */

/*******************  Bit definition for DMA_SR register  ********************/
#define  DMA_SR_TC0F                        ((u32)0x00000001)           /*!< DMA channel 0 transfer complete interrupt flag */
#define  DMA_SR_TC1F                        ((u32)0x00000002)           /*!< DMA channel 1 transfer complete interrupt flag */
#define  DMA_SR_TC2F                        ((u32)0x00000004)           /*!< DMA channel 2 transfer complete interrupt flag */
#define  DMA_SR_TC3F                        ((u32)0x00000008)           /*!< DMA channel 3 transfer complete interrupt flag */
#define  DMA_SR_TC4F                        ((u32)0x00000010)           /*!< DMA channel 4 transfer complete interrupt flag */
#define  DMA_SR_TC5F                        ((u32)0x00000020)           /*!< DMA channel 5 transfer complete interrupt flag */
#define  DMA_SR_TE0F                        ((u32)0x00000100)           /*!< DMA channel 0 transfer error interrupt flag */
#define  DMA_SR_TE1F                        ((u32)0x00000200)           /*!< DMA channel 1 transfer error interrupt flag */
#define  DMA_SR_TE2F                        ((u32)0x00000400)           /*!< DMA channel 2 transfer error interrupt flag */
#define  DMA_SR_TE3F                        ((u32)0x00000800)           /*!< DMA channel 3 transfer error interrupt flag */
#define  DMA_SR_TE4F                        ((u32)0x00001000)           /*!< DMA channel 4 transfer error interrupt flag */
#define  DMA_SR_TE5F                        ((u32)0x00002000)           /*!< DMA channel 5 transfer error interrupt flag */
#define  DMA_SR_TH0F                        ((u32)0x00010000)           /*!< DMA channel 0 transfer over half flag */
#define  DMA_SR_TH1F                        ((u32)0x00020000)           /*!< DMA channel 1 transfer over half flag */
#define  DMA_SR_TH2F                        ((u32)0x00040000)           /*!< DMA channel 2 transfer over half flag */
#define  DMA_SR_TH3F                        ((u32)0x00080000)           /*!< DMA channel 3 transfer over half flag */
#define  DMA_SR_TH4F                        ((u32)0x00100000)           /*!< DMA channel 4 transfer over half flag */
#define  DMA_SR_TH5F                        ((u32)0x00200000)           /*!< DMA channel 5 transfer over half flag */
#define  DMA_SR_CEF                         ((u32)0x80000000)           /*!< DMA channel configuration error interrupt flag */

/*******************  Bit definition for DMA_CHAPCR1 register  ********************/
#define  DMA_CHAPCR1_CH0SEL                 ((u32)0x0000003F)           /*!< DMA channel 0 peripheral selection */
#define  DMA_CHAPCR1_CH1SEL                 ((u32)0x00003F00)           /*!< DMA channel 1 peripheral selection */
#define  DMA_CHAPCR1_CH2SEL                 ((u32)0x003F0000)           /*!< DMA channel 2 peripheral selection */
#define  DMA_CHAPCR1_CH3SEL                 ((u32)0x3F000000)           /*!< DMA channel 3 peripheral selection */

/*******************  Bit definition for DMA_CHAPCR2 register  ********************/
#define  DMA_CHAPCR2_CH4SEL                 ((u32)0x0000003F)          	/*!< DMA channel 4 peripheral selection */
#define  DMA_CHAPCR2_CH5SEL                 ((u32)0x00003F00)          	/*!< DMA channel 5 peripheral selection */

/******************************************************************************/
/*                                                                            */
/*                       Arithmetic Logic Unit (ALU)                          */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for ALU_CR register  ********************/
#define  ALU_CR_MODE                        ((u32)0x00000007)           /*!< Operation mode selection */
#define  ALU_CR_START                       ((u32)0x00000008)           /*!< Start calculation */
#define  ALU_CR_QFMT                        ((u32)0x000001F0)           /*!< Q format data type */
#define  ALU_CR_SIGN                        ((u32)0x00002000)           /*!< Operand sign bit enable */

/*******************  Bit definition for ALU_IE register  ********************/
#define  ALU_IE_DIE                         ((u32)0x00000001)           /*!< Operation done interrupt enable */
#define  ALU_IE_ERRIE                       ((u32)0x00000002)           /*!< Operation error interrupt enable */

/*******************  Bit definition for ALU_SR register  ********************/
#define  ALU_SR_DONE                        ((u32)0x00000001)           /*!< Operation done flag */
#define  ALU_SR_ERR                         ((u32)0x00000002)          	/*!< Operation error flag */
#define  ALU_SR_BSY                         ((u32)0x00000004)          	/*!< Operation busy flag */

/*******************  Bit definition for ALU_OPDXR register  ********************/
#define  ALU_OPDXR_OPDX                     ((u32)0xFFFFFFFF)           /*!< Operand X */

/*******************  Bit definition for ALU_OPDYR register  ********************/
#define  ALU_OPDYR_OPDY                     ((u32)0xFFFFFFFF)           /*!< Operand Y */

/*******************  Bit definition for ALU_OPDZR register  ********************/
#define  ALU_OPDZR_OPDZ                     ((u32)0x0000FFFF)           /*!< Operand Z */

/*******************  Bit definition for ALU_DHR register  ********************/
#define  ALU_DHR_DATAH                      ((u32)0xFFFFFFFF)           /*!< Data high 32-bit */

/*******************  Bit definition for ALU_DLR register  ********************/
#define  ALU_DLR_DATAL                      ((u32)0xFFFFFFFF)           /*!< Data low 32-bit */

/*******************  Bit definition for ALU_DRR register  ********************/
#define  ALU_DRR_ROD                        ((u32)0x0000FFFF)           /*!< Remainder of division */

/******************************************************************************/
/*                                                                            */
/*                       Liquid Crystal Display (LCD)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for LCD_CR register  ********************/
#define  LCD_CR_EN											  	((u32)0x00000001)         /*!< LCD enable */
#define  LCD_CR_BSY   											((u32)0x00000002)					/*!< Register busy */
#define  LCD_CR_DUTY  											((u32)0x0000000C)					/*!< LCD duty cycle */
#define  LCD_CR_WAVE  											((u32)0x00000010)					/*!< waveform control */
#define  LCD_CR_CLKS  											((u32)0x00000040)					/*!< Clock selection */
#define  LCD_CR_DU	  											((u32)0x00000080)					/*!< Display data update */
#define  LCD_CR_SCM	  											((u32)0x00000600)					/*!< Screen Control mode */
#define  LCD_CR_PDM   											((u32)0x00003000)					/*!< Page display mode */
#define  LCD_CR_RSEL  											((u32)0x00008000)					/*!< Total resistance selection */
#define  LCD_CR_TYPE  											((u32)0x00030000)					/*!< LCD drive voltage type */

/*******************  Bit definition for LCD_GCR register  *******************/
#define  LCD_GCR_EN	  											((u32)0x00000001)					/*!< Grayscale Control Enable */
#define  LCD_GCR_GDR  											((u32)0x0000000E)					/*!< Grayscale adjustment control */

/*******************  Bit definition for LCD_PSC register  *******************/
#define  LCD_PSC_PSC   											((u32)0x0000001F)					/*!< Prescaler */

/*******************  Bit definition for LCD_BTCR register  ******************/
#define  LCD_BTCR_BT  											((u32)0x000000FF)					/*!< Blink Time */

/*******************  Bit definition for LCD_BON register  *******************/
#define  LCD_BON_ON   											((u32)0x000000FF)					/*!< Blinking Lighting Time */

/*******************  Bit definition for LCD_PCR1 register  *******************/
#define  LCD_PCR1_PE   											((u32)0xFFFFFFFF)					/*!< LCDx pin enable */

/*******************  Bit definition for LCD_PCR2 register  *******************/
#define  LCD_PCR2_PE   											((u32)0x00000FFF)					/*!< LCDx pin enable */

/*******************  Bit definition for LCD_PDCR1 register  *******************/
#define  LCD_PDCR1_PDC 											((u32)0xFFFFFFFF)					/*!< LCDx pin driver control */

/*******************  Bit definition for LCD_PDCR2 register  *******************/
#define  LCD_PDCR2_PDC 											((u32)0x00000FFF)					/*!< LCDx pin driver control */

/*******************  Bit definition for LCD_PDTR register  *******************/
#define  LCD_PDTR_PDT 											((u32)0x000000FF)					/*!< Page display time */

/*******************  Bit definition for LCD_SDPR register  *******************/
#define  LCD_SDPR_SDP 											((u32)0x0000000F)					/*!< Scroll display max page */

/*******************  Bit definition for LCD_PNR register  *******************/
#define  LCD_PNR_PN	  											((u32)0x0000000F)					/*!< Page Number */

/*******************  Bit definition for LCD_PxLy register  *******************/
#define  LCD_PxLy_COMn   										((u32)0x000000FF)					/*!< LCDx mermory */

/******************************************************************************/
/*                                                                            */
/*                        Real-Time Clock (RTC)                               */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for RTC_CR register  ********************/
#define  RTC_CR_EN													((u32)0x00000001)       /*!< RTC enable */
#define  RTC_CR_TF													((u32)0x00000002)       /*!< Time format */
#define  RTC_CR_CLKS	 											((u32)0x00000004)       /*!< Clock selection */
#define  RTC_CR_TBOE												((u32)0x00000008)       /*!< Time beacon output enable */
#define  RTC_CR_TME													((u32)0x00000010)       /*!< Trim mode enable */
#define  RTC_CR_BSY													((u32)0x00008000)       /*!< Register busy */
#define  RTC_CR_PIINR												((u32)0xFFFF0000)       /*!< Periodic Interrupt Interval */

/*******************  Bit definition for RTC_SR1 register  ********************/
#define  RTC_SR1_BSY												((u32)0x00000001)       /*!< RTC busy */

/*******************  Bit definition for RTC_LOCK register  ********************/
#define  RTC_LOCK_LOCK											((u32)0x00000001)       /*!< Lock status */
#define  RTC_LOCK_BSY												((u32)0x00000002)       /*!< Register busy */
#define  RTC_LOCK_KEY											  ((u32)0xFFFFFFFF)       /*!< Lock key */

/*******************  Bit definition for RTC_CSEC register  ********************/
#define  RTC_CSEC_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CSEC_TENS											((u32)0x00000070)       /*!< Tens */
#define  RTC_CSEC_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CMIN register  ********************/
#define  RTC_CMIN_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CMIN_TENS											((u32)0x00000030)       /*!< Tens */
#define  RTC_CMIN_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CHOUR register  *******************/
#define  RTC_CHOUR_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CHOUR_TENS											((u32)0x00000030)       /*!< Tens */
#define  RTC_CHOUR_PM 											((u32)0x00000100)       /*!< P.M flag */
#define  RTC_CHOUR_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CDAY register  ********************/
#define  RTC_CDAY_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CDAY_TENS											((u32)0x00000030)       /*!< Tens */
#define  RTC_CDAY_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CWEEK register  *******************/
#define  RTC_CWEEK_DIGS											((u32)0x00000007)       /*!< Digits */
#define  RTC_CWEEK_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CMON register  ********************/
#define  RTC_CMON_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CMON_TENS											((u32)0x00000010)       /*!< Tens */
#define  RTC_CMON_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_CYEAR register  *******************/
#define  RTC_CYAER_DIGS											((u32)0x0000000F)       /*!< Digits */
#define  RTC_CYEAR_TENS											((u32)0x000000F0)       /*!< Tens */
#define  RTC_CYEAR_HUND											((u32)0x00000F00)       /*!< Hundreds */
#define  RTC_CYEAR_THOU											((u32)0x0000F000)       /*!< Thousands */
#define  RTC_CYEAR_BSY 										  ((u32)0x00010000)       /*!< Register busy */

/*******************  Bit definition for RTC_IE register  ********************/
#define  RTC_IE_CHSECE											((u32)0x00000001)  						/*!< Calendar half-seconds interrupt enable */
#define  RTC_IE_CSECE											  ((u32)0x00000002)  						/*!< Calendar seconds interrupt enable */
#define  RTC_IE_CMINE										  	((u32)0x00000004)  						/*!< Calendar mins interrupt enable */
#define  RTC_IE_CHOURE											((u32)0x00000008)  						/*!< Calendar hours interrupt enable */
#define  RTC_IE_CDAYE										  	((u32)0x00000010)  						/*!< Calendar days interrupt enable */
#define  RTC_IE_CMONE     									((u32)0x00000020)  						/*!< Calendar months interrupt enable */
#define  RTC_IE_ALME     										((u32)0x00000040)  						/*!< Alarm interrupt enable */
#define  RTC_IE_PEDE     										((u32)0x00000080)  						/*!< Periodic interrupt enable */

/*******************  Bit definition for RTC_SR2 register  ********************/
#define  RTC_SR2_CHSEC											((u32)0x00000001)  						/*!< Calendar half-seconds update flag */
#define  RTC_SR2_CSEC											  ((u32)0x00000002)  						/*!< Calendar seconds update flag */
#define  RTC_SR2_CMIN										  	((u32)0x00000004)  						/*!< Calendar mins update flag */
#define  RTC_SR2_CHOUR											((u32)0x00000008)  						/*!< Calendar hours update flag */
#define  RTC_SR2_CDAY		  									((u32)0x00000010)  						/*!< Calendar days update flag */
#define  RTC_SR2_CMON		  									((u32)0x00000020)  						/*!< Calendar months update flag */
#define  RTC_SR2_ALM     										((u32)0x00000040)  						/*!< Alarm flag */
#define  RTC_SR2_PED     										((u32)0x00000080)  						/*!< Periodic update flag */

/*******************  Bit definition for RTC_ASEC register  ********************/
#define  RTC_ASEC_DIGS  										((u32)0x0000000F)  						/*!< Digits */
#define  RTC_ASEC_TENS  										((u32)0x00000070)  						/*!< Tens */

/*******************  Bit definition for RTC_AMIN register  ********************/
#define  RTC_AMIN_DIGS  										((u32)0x0000000F)  						/*!< Digits */
#define  RTC_AMIN_TENS  										((u32)0x00000070)  						/*!< Tens */

/*******************  Bit definition for RTC_AHOUR register  *******************/
#define  RTC_AHOUR_DIGS  										((u32)0x0000000F)  				   	/*!< Digits */
#define  RTC_AHOUR_TENS  										((u32)0x00000030)  				  	/*!< Tens */
#define  RTC_AHOUR_PM  											((u32)0x00000100)  				  	/*!< P.M flag */

/*******************  Bit definition for RTC_AWEEK register  *******************/
#define  RTC_AWEEK_WEEK  										((u32)0x000000FE)  						/*!< Week */

/*******************  Bit definition for RTC_TRIM register  ********************/
#define  RTC_TRIM_TRIM  										((u32)0x000001FF)  					  /*!< Trim Value */

/******************************************************************************/
/*                                                                            */
/*                        Window watch dog(WWDG)                              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WWDG_CR1 register  *******************/
#define WWDG_CR1_CNT                        ((u32)0x0000007F)       /*!< WWDG Counter value  */ 
#define WWDG_CR1_RSTE                       ((u32)0x00000080)       /*!< WWDG reset enable */ 

/*******************  Bit definition for WWDG_CFGR register *******************/
#define WWDG_CFGR_W                         ((u32)0x0000007F)       /*!< WWDG window value */ 
#define WWDG_CFGR_DBGE                      ((u32)0x00000100)       /*!< WWDG debug pending */ 
#define WWDG_CFGR_EWIE                      ((u32)0x00000200)       /*!< WWDG early wakeup interrupt enable */ 
#define WWDG_CFGR_PSC                       ((u32)0x00007000)       /*!< WWDG prescaler value  */ 

/*******************  Bit definition for WWDG_SR register *******************/
#define WWDG_SR_EWIF                        ((u32)0x00000001)       /*!< WWDG early wakeup interrupt flag */

/*******************  Bit definition for WWDG_CR2 register *******************/
#define WWDG_CR2_EN                         ((u32)0x00000001)       /*!< WWDG enable */
#define WWDG_CR2_KEY                        ((u32)0xFFFF0000)       /*!< WWDG Key value  */

/******************************************************************************/
/*                                                                            */
/*                      AES Registers                                         */
/*                                                                            */
/******************************************************************************/

/*******************  Bits definition for AES_CR register  *******************/
#define AES_CR_START                             ((u32)0x00000001)         /*!< Start computation                      */
#define AES_CR_MODE                              ((u32)0x00000002)         /*!< AES operating mode                     */
#define AES_CR_EM                          	     ((u32)0x00000004)         /*!< AES encryption method                  */
#define AES_CR_KSIZE                      		   ((u32)0x00000018)         /*!< Key size selection                     */
#define AES_CR_KEE                     	    		 ((u32)0x00000080)         /*!< Key expansion enable                   */
#define AES_CR_CCIE                     	    	 ((u32)0x00000100)         /*!< Computation completed interrupt enable */

/*******************   Bits definition for AES_SR register  ******************/ 
#define AES_SR_CCF                               ((u32)0x00000001)         /*!< Computation completed flag             */

/********************  Bits definition for AES_KR register  ******************/
#define AES_KRx_KEY                              ((u32)0xFFFFFFFF)         /*!< Key Register                           */

/********************  Bits definition for AES_IVR register  ******************/
#define AES_IVRx_IVI                             ((u32)0xFFFFFFFF)         /*!< Initialization Vector Register         */

/********************  Bits definition for AES_DINR register  ******************/
#define AES_DINRx_DIN                            ((u32)0xFFFFFFFF)         /*!< Data Input Register                    */

/********************  Bits definition for AES_DOUTR register  ******************/
#define AES_DOUTRx_DOUT                          ((u32)0xFFFFFFFF)         /*!< Data Output Register                    */

#ifdef USE_STDPERIPH_DRIVER
#endif


#ifdef __cplusplus
}
#endif

#endif

