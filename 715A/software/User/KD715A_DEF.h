/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : 
 * Version : 0.1
 * 32bit MCU : PT32L031
 * Cortex : Cortex-M0
 *
 * Compiler : 
 *   Keil ARM 5.18 Compiler
 *
 * Pack:
 *   PAI-IC.PT32X031_DFP.1.0.6
 *
 * Author : 
 *  
 *
 * Description : 
 *   
 *
 * History :
 * 	
 *
 */
#ifndef __755LHA_DEF_H
#define __755LHA_DEF_H

#include "stdint.h"
#include "KD715A_Timer_PT32L031.h"
#include "FE_755LHA_EEPROM_PT32L031.h"

/* --------------------------------------------------------------------------- */
//state
#define			_idle				0x00
#define			_exe				0x01
#define			_busy				0x10
#define			_end				0x20
#define			_err				0x40
#define			_finish			0x80
/* --------------------------------------------------------------------------- */
//beta version
#define   _BETA_VERSION   1

/* --------------------------------------------------------------------------- */
//SYSTEM STATUS
#define			ALARM_FLAG_POS                   0
#define			ALARM_FLAG_MSK  						    (1UL << ALARM_FLAG_POS)

#define			HUSH_FLAG_POS                    1
#define			HUSH_FLAG_MSK                   (1UL << HUSH_FLAG_POS)

#define			TEST_FLAG_POS                    2
#define			TEST_FLAG_MSK                   (1UL << TEST_FLAG_POS)

#define			LOW_BATTERY_FLAG_POS             3
#define			LOW_BATTERY_FLAG_MSK            (1UL << LOW_BATTERY_FLAG_POS)

#define			SENSOR_FAULT_FLAG_POS            4
#define			SENSOR_FAULT_FLAG_MSK           (1UL << SENSOR_FAULT_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM SIGNAL
#define			DEVICE_ALARM_FLAG_POS            0
#define			DEVICE_ALARM_FLAG_MSK           (1UL << DEVICE_ALARM_FLAG_POS)

#define			DEVICE_HUSH_FLAG_POS             1
#define			DEVICE_HUSH_FLAG_MSK            (1UL << DEVICE_HUSH_FLAG_POS)

#define			DEVICE_TEST_FLAG_POS             2
#define			DEVICE_TEST_FLAG_MSK            (1UL << DEVICE_TEST_FLAG_POS)

#define			DEVICE_LOW_BATTERY_FLAG_POS      3
#define			DEVICE_LOW_BATTERY_FLAG_MSK     (1UL << DEVICE_LOW_BATTERY_FLAG_POS)

#define			DEVICE_SENSOR_FAULT_FLAG_POS     4
#define			DEVICE_SENSOR_FAULT_FLAG_MSK    (1UL << DEVICE_SENSOR_FAULT_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM MASKING
#define			SYSTEM_INITIALIZE_FLAG_POS       0
#define			SYSTEM_INITIALIZE_FLAG_MSK      (1UL	<< SYSTEM_INITIALIZE_FLAG_POS)

#define			HEAT_INITIALIZE_FLAG_POS         1
#define			HEAT_INITIALIZE_FLAG_MSK        (1UL	<< HEAT_INITIALIZE_FLAG_POS)

#define			MESSAGE_FLAG_POS                 2
#define			MESSAGE_FLAG_MSK                (1UL << MESSAGE_FLAG_POS)

#define			BAT_INITIALIZE_FLAG_POS          3
#define			BAT_INITIALIZE_FLAG_MSK         (1UL << BAT_INITIALIZE_FLAG_POS)

#define			DEBUG_FLAG_POS                   4
#define			DEBUG_FLAG_MSK                  (1UL << DEBUG_FLAG_POS)

#define			TIMER1_UPDATE_FLAG_POS           5
#define			TIMER1_UPDATE_FLAG_MSK          (1UL << TIMER1_UPDATE_FLAG_POS)

#define			LOW_SOUND_FLAG_POS               6
#define			LOW_SOUND_FLAG_MSK              (1UL << LOW_SOUND_FLAG_POS)

#define			TIMER3_UPDATE_FLAG_POS           7
#define			TIMER3_UPDATE_FLAG_MSK          (1UL << TIMER3_UPDATE_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM RESOURCE
#define			LED_FLAG_POS                     0
#define			LED_FLAG_MSK                    (1ul << LED_FLAG_POS)

#define			BUZZER_FLAG_POS                  1
#define			BUZZER_FLAG_MSK                 (1ul << BUZZER_FLAG_POS)

/* --------------------------------------------------------------------------- */
//timer3
#define     TEST_TIMER 				        Timer3.t[0]
#define     MUTE_TIMER       	        Timer3.t[1]
#define     GENERAL_TIMER       	    Timer3.t[2]
#define     KEY_LONG_TIMER 			      Timer3.t[3]
#define     YELLOW_LED_TIMER          Timer3.t[4]
#define     LED_TIMER                 Timer3.t[5]
#define     BUZZER_TIMER              Timer3.t[6]
#define     TIMER1_TIMER 		          Timer3.t[7]



#define	    HEAT_TIMER                Timer3.t[10]
#define     BATTERY_TIMER 		        Timer3.t[11]
#define     ALARM_TIMER               Timer3.t[12]
#define     HUSH_TIMER                Timer3.t[13]

/* --------------------------------------------------------------------------- */
//PA0 -> VOP
#define     VH_PIN                  0x0001
#define     VH_ON                   CMSDK_PA->DATAOUT |= VH_PIN
#define     VH_OFF                  CMSDK_PA->DATAOUT &= ~VH_PIN

//PA1 -> HTS
#define     HTS_PIN                 0x0002
#define     HTS_IN_ON		            CMSDK_PA->OUTENABLECLR |= HTS_PIN
#define     HTS_IN_OFF	            CMSDK_PA->OUTENABLESET |= HTS_PIN
#define     HTS_ANA_ON              CMSDK_PA->ANASET |= HTS_PIN
#define     HTS_ANA_OFF             CMSDK_PA->ANACLR |= HTS_PIN

//PA2 -> BOOST
#define     BST_PIN		              0x0004
#define     BST_ON                  CMSDK_PA->DATAOUT |= BST_PIN
#define     BST_OFF                 CMSDK_PA->DATAOUT &= ~BST_PIN

//PA5 -> KY1 -> DEBUG按键
#define     DEBUG_PIN		            0x0020
#define     DEBUG_KEY		           (CMSDK_PA->DATA & DEBUG_PIN)

//PA6 -> KY2 -> MUTE按键
#define     MUTE_PIN		            0x0040
#define     MUTE_KEY		           (CMSDK_PA->DATA & MUTE_PIN)

//PA7 -> KY3 -> TEST按键
#define     TEST_PIN		            0x0060
#define     TEST_KEY		           (CMSDK_PA->DATA & TEST_PIN)

//PA8 -> RED
#define     RED_PIN		              0x0100
#define     RED_LED_ON              CMSDK_PA->DATAOUT &= ~RED_PIN
#define     RED_LED_OFF             CMSDK_PA->DATAOUT |= RED_PIN

//PF0 -> BL_PIN
#define     BL_PIN		              0x0001
#define     BL_ON                   CMSDK_PF->DATAOUT &= ~BL_PIN
#define     BL_OFF                  CMSDK_PF->DATAOUT |= BL_PIN

/* --------------------------------------------------------------------------- */
//PWM 频率
#define     MIN_TIMER_US            284
#define     MAX_TIMER_US            294

/* --------------------------------------------------------------------------- */
//深度睡眠
#define     DEEPSLEEP                 (Heat.mode + bat.mode + buzzer.mode + led.mode + update.mode + start.mode)

/* --------------------------------------------------------------------------- */
typedef struct
{
  uint32_t state;
	uint32_t masking;
	uint32_t signal;
	uint32_t resource;
	
}SYSTEM_DATA_typedef;

extern SYSTEM_DATA_typedef system_data;
extern FE_755LHA_EEPROM_TypeDef eeprom_data;



#endif

