/*
* Copyright (c) 2008, XingLan Technology
* File name : NUC1xx_Timer_api.H
* Version: 0.6
* 32bit MCU : NUC1xx
* Cortex: Cortex-M0
* Compiler: 
*   Keil ARM 4.11 Compiler
*   IAR  ARM 5.40 Compiler
*
* Author : Tom (pengfengboy@163.com)
*
* Description : 
* 	1:initialize the timer module
*
* History :
* 	02/18/2011 : adds the SetTimer0 function.
*
*/
#ifndef __FE_755LHA_TIMER_PT32L0_H
#define __FE_755LHA_TIMER_PT32L0_H
/* --------------------------------------------------------------------------- */
#include "stdint.h"
//#include "Macro_definition.h"
/* --------------------------------------------------------------------------- */
#define 	TIMER3_SIZE		4
#define   COUNTER_SIZE  5
/* --------------------------------------------------------------------------- */
/******************  Bit definition for TIM_CCMR1 register  *******************/
#define 	TIM_CCMR1_CC1S_OUTPUT					((uint32_t)0x00000000U)
#define 	TIM_CCMR1_OC1M_PWM_MODE1      ((uint32_t)0x00000060U)
#define 	TIM_CCMR1_OC1M_PWM_MODE2      ((uint32_t)0x00000070U)
#define 	TIM_CCMR1_CC2S_OUTPUT					((uint32_t)0x00000000U)
#define 	TIM_CCMR1_OC2M_PWM_MODE1      ((uint32_t)0x00006000U)
#define 	TIM_CCMR1_OC2M_PWM_MODE2      ((uint32_t)0x00007000U)
/* --------------------------------------------------------------------------- */
/*******************  Bit definition for TIM_CR1 register  ********************/
#define 	TIM_CR1_CMS_EDGE_MODE					((uint32_t)0x00000000U)
#define 	TIM_CR1_CMS_CENTER_MODE1			((uint32_t)0x00000020U)
#define 	TIM_CR1_CMS_CENTER_MODE2			((uint32_t)0x00000040U)
#define 	TIM_CR1_CMS_CENTER_MODE3			((uint32_t)0x00000060U)
/* --------------------------------------------------------------------------- */
/*******************  Bit definition for PWM_CMR register  *******************/ 
#define   PWM_CMR_MC4_MODE1             ((uint32_t)0x00001000)
#define   PWM_CMR_MC4_MODE2             ((uint32_t)0x00002000)
#define   PWM_CMR_MC4_MODE3             ((uint32_t)0x00003000)
/* --------------------------------------------------------------------------- */
#define WDG_WriteAccess_Enable     ((uint32_t)0x1ACCE551)
#define WDG_WriteAccess_Disable    ((uint32_t)0x00000000)
/* --------------------------------------------------------------------------- */


/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t t[TIMER3_SIZE];
	uint32_t T8s;
	unsigned short period;
	unsigned char step;
	unsigned char mode;
}TIMER3_TypeDef;
/* --------------------------------------------------------------------------- */
extern TIMER3_TypeDef Timer3;
/* --------------------------------------------------------------------------- */


/* --------------------------------------------------------------------------- */
typedef struct
{
	uint32_t data[4];
}RANDOM_TypeDef;
/* --------------------------------------------------------------------------- */
extern RANDOM_TypeDef Random;
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
void SetTimer2_ET(uint32_t t);
void KillTimer2_ET(void);
/* --------------------------------------------------------------------------- */
void set_timer3(void);
void check_timer3(void);
void kill_timer3(void);
/* --------------------------------------------------------------------------- */
void OpenTimer1_CH4_PWM(void);
void CloseTimer1(void);
/* --------------------------------------------------------------------------- */
void open_timer4(void);
void close_timer4(void);
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
void OpenSystemWatchdog(void);
void FeedSystemWatchdog(void);
void CloseSystemWatchdog(void);
/* --------------------------------------------------------------------------- */


typedef struct
{
	unsigned char mode;
	unsigned char idx;
  unsigned char counter[COUNTER_SIZE];
}SystemCounter;

extern SystemCounter system_count;

void system_counter(void);

void fe_755LHA_calculate_internal_32k(void);

#endif
