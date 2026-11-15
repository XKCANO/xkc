/*
**
*/
#ifndef __FE_HEAT_CFG_H
#define __FE_HEAT_CFG_H
/* -------------------------------------------------------------------------- */
#include "stdint.h"
/* -------------------------------------------------------------------------- */
#define  fe_idle  0
#define  fe_exe   1
/* -------------------------------------------------------------------------- */
#define  fe_normal	 10000
#define	 fe_success	 10000
#define	 fe_failed	 10001
#define	 fe_error		 10002
/* -------------------------------------------------------------------------- */

/******************************************************************************/
/*                                                                            */
/*                           GPIO                                             */
/*                                                                            */
/******************************************************************************/
#define	GPIO_PIN0			0
#define	GPIO_PIN1			1
#define	GPIO_PIN2			2
#define	GPIO_PIN3			3
#define	GPIO_PIN4			4
#define	GPIO_PIN5			5
#define	GPIO_PIN6			6
#define	GPIO_PIN7			7
#define	GPIO_PIN8			8
#define	GPIO_PIN9			9
#define	GPIO_PIN10		10
#define	GPIO_PIN11		11
#define	GPIO_PIN12		12
#define	GPIO_PIN13		13
#define	GPIO_PIN14		14
#define	GPIO_PIN15		15

/****************** Bit definition for GPIO_AFS register  ********************/
#define   GPIO_AFS_FUN0                 ((uint32_t)0x00000000)
#define   GPIO_AFS_FUN1                 ((uint32_t)0x00000001)
#define   GPIO_AFS_FUN2                 ((uint32_t)0x00000002)
#define   GPIO_AFS_FUN3                 ((uint32_t)0x00000003)
#define   GPIO_AFS_FUN4                 ((uint32_t)0x00000004)
#define   GPIO_AFS_FUN5                 ((uint32_t)0x00000005)
#define   GPIO_AFS_FUN6                 ((uint32_t)0x00000006)
#define   GPIO_AFS_FUN7                 ((uint32_t)0x00000007)
/* ========================================================================== */

/******************************************************************************/
/*                                                                            */
/*                           Advanced Timer (TIM)                             */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for TIM_CCMR1 register  *******************/
#define 	TIM_CCMR1_CC1S_OUTPUT					((uint32_t)0x00000000U)
#define 	TIM_CCMR1_OC1M_PWM_MODE1      ((uint32_t)0x00000060U)
#define 	TIM_CCMR1_OC1M_PWM_MODE2      ((uint32_t)0x00000070U)
#define 	TIM_CCMR1_CC2S_OUTPUT					((uint32_t)0x00000000U)
#define 	TIM_CCMR1_OC2M_PWM_MODE1      ((uint32_t)0x00006000U)
#define 	TIM_CCMR1_OC2M_PWM_MODE2      ((uint32_t)0x00007000U)

/*******************  Bit definition for TIM_CR1 register  ********************/
#define 	TIM_CR1_CMS_EDGE_MODE					((uint32_t)0x00000000U)
#define 	TIM_CR1_CMS_CENTER_MODE1			((uint32_t)0x00000020U)
#define 	TIM_CR1_CMS_CENTER_MODE2			((uint32_t)0x00000040U)
#define 	TIM_CR1_CMS_CENTER_MODE3			((uint32_t)0x00000060U)
/* --------------------------------------------------------------------------- */
#define 	TIMER_SIZE		4
/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t t[TIMER_SIZE];
	uint32_t sleep_8s;
	unsigned char *s;
}FE_TIMER_TypeDef;
/* --------------------------------------------------------------------------- */
extern FE_TIMER_TypeDef Timer;
/* --------------------------------------------------------------------------- */


/******************************************************************************/
/*                                                                            */
/*                           EEPROM                                           */
/*                                                                            */
/******************************************************************************/



/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/

/* --------------------------------------------------------------------------- */


/******************************************************************************/
/*                                                                            */
/*           Universal Asynchronous Receiver Transmitter (UART)      				  */
/*                                                                            */
/******************************************************************************/
//TX1 --> PA9
//#define TX1_PIN_INPUT_MODE (GPIOA->MODER &= ~(GPIO_MODER_MODE << GPIO_PIN9))
//#define TX1_PIN_OUTPUT_MODE (GPIOA->MODER |= (GPIO_MODER_OUTPUT_MODE << GPIO_PIN9))
//#define TX1_PIN_UART_MODE (GPIOA->MODER |= (GPIO_MODER_ALTERNATE_MODE << GPIO_PIN9))
//RX1 --> PA10
//#define RX1_PIN_INPUT_MODE (GPIOA->MODER &= ~(GPIO_MODER_MODE << GPIO_PIN10))
//#define RX1_PIN_OUTPUT_MODE (GPIOA->MODER |= (GPIO_MODER_OUTPUT_MODE << GPIO_PIN10))
//#define RX1_PIN_UART_MODE (GPIOA->MODER |= (GPIO_MODER_ALTERNATE_MODE << GPIO_PIN10))
/* --------------------------------------------------------------------------- */
/******************  Bit definition for UART_CR register  *******************/
#define  UART_CR_MODE_D8BITS              ((uint32_t)0x00000001)
#define  UART_CR_MODE_D7BITS_P1BIT        ((uint32_t)0x00000003)
#define  UART_CR_MODE_D9BITS              ((uint32_t)0x00000004)
#define  UART_CR_MODE_D8BITS_W1BIT        ((uint32_t)0x00000005)
#define  UART_CR_MODE_D8BITS_P1BIT        ((uint32_t)0x00000007)
#define  UART_CR_STOP_0_5BIT              ((uint32_t)0x00000000)
#define  UART_CR_STOP_1BIT                ((uint32_t)0x00000008)
#define  UART_CR_STOP_1_5BIT              ((uint32_t)0x00000010)
#define  UART_CR_STOP_2BITS               ((uint32_t)0x00000018)
/* --------------------------------------------------------------------------- */
#include "FE_755LHA_UART_PT32L031.h"
//masking
#define  UART_DEBUG_FLAG_POS    7
#define  UART_DEBUG_FLAG_MSK    (1UL << UART_DEBUG_FLAG_POS)
//cmd
#define  OUTPUT_SYSTEM_STATE_CMD  0x01
#define  OUTPUT_SMOKE_DATA_CMD    0x02
#define  OUTPUT_HEAT_DATA_CMD     0x04
#define  WAITING_IN_DATA_CMD      0x10
/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char cmd;
	unsigned char step;
	unsigned char mode;
	unsigned char masking;
  FE_UART_CALLBACK cb;
}FE_UART_TypeDef;
/* -------------------------------------------------------------------------- */
extern FE_UART_TypeDef uart;
/* -------------------------------------------------------------------------- */


/******************************************************************************/
/*                                                                            */
/*                           SPI                                              */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*                           PHY                                              */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*                           MAC                                              */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/*                           SEMAPHORE                                        */
/*                                                                            */
/******************************************************************************/


#endif


