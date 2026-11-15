#ifndef __755LHA_DEF_H
#define __755LHA_DEF_H

#include "stdint.h"
#include "755LHA_RF_PT32L031.h"
#include "755LHA_Timer_PT32L031.h"

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
#define   _BETA_VERSION   0

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

#define			SNOOZE_LOW_FLAG_POS              4 
#define			SNOOZE_LOW_FLAG_MSK             (1UL << SNOOZE_LOW_FLAG_POS)

#define			EXTERNAL_ALARM_FLAG_POS          5
#define			EXTERNAL_ALARM_FLAG_MSK         (1UL << EXTERNAL_ALARM_FLAG_POS) 

#define			NETWORK_ALARM_FLAG_POS           6
#define			NETWORK_ALARM_FLAG_MSK          (1UL << NETWORK_ALARM_FLAG_POS)

#define			NETWORK_TEST_FLAG_POS            7
#define			NETWORK_TEST_FLAG_MSK           (1UL << NETWORK_TEST_FLAG_POS)

#define			SENSOR_FAULT_FLAG_POS            8
#define			SENSOR_FAULT_FLAG_MSK           (1UL << SENSOR_FAULT_FLAG_POS)

#define			SNOOZE_FAULT_FLAG_POS            9
#define			SNOOZE_FAULT_FLAG_MSK           (1UL << SNOOZE_FAULT_FLAG_POS)

#define			ALARM_MEMORY_FLAG_POS            10
#define			ALARM_MEMORY_FLAG_MSK           (1UL << ALARM_MEMORY_FLAG_POS)

#define			SNOOZE_MEMORY_FLAG_POS           11
#define			SNOOZE_MEMORY_FLAG_MSK          (1UL << SNOOZE_MEMORY_FLAG_POS)

#define			EXTERNAL_ERROR_FLAG_POS          12
#define			EXTERNAL_ERROR_FLAG_MSK         (1UL << EXTERNAL_ERROR_FLAG_POS)

#define			FIND_ALARM_FLAG_POS              13
#define			FIND_ALARM_FLAG_MSK             (1UL << FIND_ALARM_FLAG_POS)

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

#define			DEVICE_SNOOZE_LOW_FLAG_POS       4 
#define			DEVICE_SNOOZE_LOW_FLAG_MSK      (1UL << DEVICE_SNOOZE_LOW_FLAG_POS)

#define			DEVICE_EXTERNAL_ALARM_FLAG_POS   5
#define			DEVICE_EXTERNAL_ALARM_FLAG_MSK  (1UL << DEVICE_EXTERNAL_ALARM_FLAG_POS)

#define			DEVICE_NETWORK_ALARM_FLAG_POS    6
#define			DEVICE_NETWORK_ALARM_FLAG_MSK   (1UL << DEVICE_NETWORK_ALARM_FLAG_POS)

#define			DEVICE_NETWORK_TEST_FLAG_POS     7
#define			DEVICE_NETWORK_TEST_FLAG_MSK    (1UL << DEVICE_NETWORK_TEST_FLAG_POS)

#define			DEVICE_SENSOR_FAULT_FLAG_POS     8
#define			DEVICE_SENSOR_FAULT_FLAG_MSK    (1UL << DEVICE_SENSOR_FAULT_FLAG_POS)

#define			DEVICE_SNOOZE_FAULT_FLAG_POS     9
#define			DEVICE_SNOOZE_FAULT_FLAG_MSK    (1UL << DEVICE_SNOOZE_FAULT_FLAG_POS)

#define			DEVICE_ALARM_MEMORY_FLAG_POS     10
#define			DEVICE_ALARM_MEMORY_FLAG_MSK    (1UL << DEVICE_ALARM_MEMORY_FLAG_POS)

#define			DEVICE_SNOOZE_MEMORY_FLAG_POS    11
#define			DEVICE_SNOOZE_MEMORY_FLAG_MSK   (1UL << DEVICE_SNOOZE_MEMORY_FLAG_POS)

#define			DEVICE_EXTERNAL_ERROR_FLAG_POS   12
#define			DEVICE_EXTERNAL_ERROR_FLAG_MSK  (1UL << DEVICE_EXTERNAL_ERROR_FLAG_POS)

#define			DEVICE_FIND_ALARM_FLAG_POS       13
#define			DEVICE_FIND_ALARM_FLAG_MSK      (1UL << DEVICE_FIND_ALARM_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM MASKING
#define			SYSTEM_INITIALIZE_FLAG_POS       0
#define			SYSTEM_INITIALIZE_FLAG_MSK      (1UL	<< SYSTEM_INITIALIZE_FLAG_POS)

#define			HEAT_INITIALIZE_FLAG_POS         1
#define			HEAT_INITIALIZE_FLAG_MSK        (1UL	<< HEAT_INITIALIZE_FLAG_POS)

#define			BAT_INITIALIZE_FLAG_POS          2
#define			BAT_INITIALIZE_FLAG_MSK         (1UL << BAT_INITIALIZE_FLAG_POS)

#define			MESSAGE_FLAG_POS                 3
#define			MESSAGE_FLAG_MSK                (1UL << MESSAGE_FLAG_POS)

#define			EXT_CHECK_FLAG_POS               4
#define			EXT_CHECK_FLAG_MSK              (1UL << EXT_CHECK_FLAG_POS)

#define			RF_SEND_FLAG_POS                 5
#define			RF_SEND_FLAG_MSK                (1UL << RF_SEND_FLAG_POS)

#define			ON_NET_FLAG_POS                  6
#define			ON_NET_FLAG_MSK                 (1UL << ON_NET_FLAG_POS)

#define			RECENT_ALARM_FLAG_POS            7
#define			RECENT_ALARM_FLAG_MSK           (1UL << RECENT_ALARM_FLAG_POS)

#define			DEBUG_FLAG_POS                   8
#define			DEBUG_FLAG_MSK                  (1UL << DEBUG_FLAG_POS)

#define			RF_PAIRINGF_FLAG_POS             9
#define			RF_PAIRINGF_FLAG_MSK            (1UL << RF_PAIRINGF_FLAG_POS)

#define			TIMER1_UPDATE_FLAG_POS           10
#define			TIMER1_UPDATE_FLAG_MSK          (1UL << TIMER1_UPDATE_FLAG_POS)

#define			LOW_SOUND_FLAG_POS               11
#define			LOW_SOUND_FLAG_MSK              (1UL << LOW_SOUND_FLAG_POS)

#define			DECEIVE_MASTER_FLAG_POS          12
#define			DECEIVE_MASTER_FLAG_MSK         (1UL << DECEIVE_MASTER_FLAG_POS)

#define     SYSTEM_INTERRUPT_FLAG_POS        13
#define     SYSTEM_INTERRUPT_FLAG_MSK       (1UL << SYSTEM_INTERRUPT_FLAG_POS)

#define     KEY2_OUT_FLAG_POS                14
#define     KEY2_OUT_FLAG_MSK               (1UL << KEY2_OUT_FLAG_POS)

#define     KEY5_OUT_FLAG_POS                15
#define     KEY5_OUT_FLAG_MSK               (1UL << KEY5_OUT_FLAG_POS)

#define     KEY3_DOWN_FLAG_POS               16
#define     KEY3_DOWN_FLAG_MSK              (1UL << KEY3_DOWN_FLAG_POS)

#define     KEY3_08S_FLAG_POS                17
#define     KEY3_08S_FLAG_MSK               (1UL << KEY3_08S_FLAG_POS)

#define     KEY3_10S_FLAG_POS                18
#define     KEY3_10S_FLAG_MSK               (1UL << KEY3_10S_FLAG_POS)

#define     KEY3_UP_FLAG_POS                 19
#define     KEY3_UP_FLAG_MSK                (1UL << KEY3_UP_FLAG_POS)

#define     RF_CHECK_FLAG_POS                20
#define     RF_CHECK_FLAG_MSK               (1UL << RF_CHECK_FLAG_POS)

#define     KEY2_PENDING_FLAG_POS            21
#define     KEY2_PENDING_FLAG_MSK           (1UL << KEY2_PENDING_FLAG_POS)

#define     TIMER1_CLOSE_FLAG_POS            22
#define     TIMER1_CLOSE_FLAG_MSK           (1UL << TIMER1_CLOSE_FLAG_POS)

#define     OPEN_BOOST_FLAG_POS              23
#define     OPEN_BOOST_FLAG_MSK             (1UL << OPEN_BOOST_FLAG_POS)

#define     CLOSE_BOOST_FLAG_POS             24
#define     CLOSE_BOOST_FLAG_MSK            (1UL << CLOSE_BOOST_FLAG_POS)

#define     HUSH_HOLD_FLAG_POS               25
#define     HUSH_HOLD_FLAG_MSK              (1UL << HUSH_HOLD_FLAG_POS)

#define     BOOST_HOLD_UP_FLAG_POS           26
#define     BOOST_HOLD_UP_FLAG_MSK          (1UL << BOOST_HOLD_UP_FLAG_POS)

#define     BATTERY_SAMPLING_FLAG_POS        27
#define     BATTERY_SAMPLING_FLAG_MSK       (1UL << BATTERY_SAMPLING_FLAG_POS)


/* --------------------------------------------------------------------------- */
//PWM 频率
#define     MIN_TIMER_US            289                                        
#define     MAX_TIMER_US            302
#define     LOW_TIMER_US            275

/* --------------------------------------------------------------------------- */
//timer3
#define     KEY_TIMER 		            timer3.t[0]
#define     KEY3_TIMER 				        timer3.t[1]
#define     TIMER1_TIMER 		          timer3.t[2]
#define     GENERAL_TIMER       	    timer3.t[3]
#define     YELLOW_LED_TIMER          timer3.t[4]
#define     RED_LED_TIMER             timer3.t[5]
#define     BUZZER_TIMER              timer3.t[6]
#define     RF_TIMER 		              timer3.t[7]
#define     NET_ALARM_TIMER		        timer3.t[8]
#define     RELEASE_TIMER 		        timer3.t[9]
#define     HUSH_TIMER 		            timer3.t[10]

#define	    HEAT_TIMER                timer3.t[11]
#define     BATTERY_TIMER 		        timer3.t[12]
#define     ALARM_TIMER               timer3.t[13]
#define     ALARM_TIMER1              timer3.t[14]
#define     LB_DND_TIMER              timer3.t[15]
#define     FU_DND_TIMER              timer3.t[16]
#define     ALARM_M_TIMER             timer3.t[17]
#define     MEM_DND_TIMER             timer3.t[18]

/* --------------------------------------------------------------------------- */
//rf send cmd
#define     SEND_CMD		            pair.cmd

/* --------------------------------------------------------------------------- */
// BL_EN --> PA0
#define     BL_PIN                  0x0001
#define     BL_ON                   CMSDK_PA->DATAOUT |= BL_PIN
#define     BL_OFF                  CMSDK_PA->DATAOUT &= ~BL_PIN

// BTS --> PA1
#define     BTS_IN_ON		            CMSDK_PA->OUTENABLECLR |= (1 << 1)
#define     BTS_IN_OFF	            CMSDK_PA->OUTENABLESET |= (1 << 1)
#define     BTS_ANA_ON              CMSDK_PA->ANASET |= (1 << 1)
#define     BTS_ANA_OFF             CMSDK_PA->ANACLR |= (1 << 1)

//PA2 -> KY3 -> 按键
#define     TEST_PIN		            0x0004
#define     TEST_KEY		           (CMSDK_PA->DATA & TEST_PIN)

//PA3 -> RED1
#define     RED1_PIN		            0x0008
#define     RED1_LED_ON             CMSDK_PA->DATAOUT &= ~RED1_PIN
#define     RED1_LED_OFF            CMSDK_PA->DATAOUT |= RED1_PIN

//PA6 -> HTS
#define     HTS_PIN                 0x0040
#define     HTS_IN_ON		            CMSDK_PA->OUTENABLECLR |= HTS_PIN
#define     HTS_IN_OFF	            CMSDK_PA->OUTENABLESET |= HTS_PIN
#define     HTS_ANA_ON              CMSDK_PA->ANASET |= HTS_PIN
#define     HTS_ANA_OFF             CMSDK_PA->ANACLR |= HTS_PIN

//PA7 -> VOP
#define     VH_PIN                  0x0080
#define     VH_ON                   CMSDK_PA->DATAOUT |= VH_PIN
#define     VH_OFF                  CMSDK_PA->DATAOUT &= ~VH_PIN

//PA8 -> local
#define     NETWORK_PIN		          0x0100
#define     NETWORK_KEY		         (CMSDK_PA->DATA & NETWORK_PIN)

//PB0 -> I_OUT
#define     IOUT_PIN		            0x0001
#define     IOUT_ON                 CMSDK_PB->DATAOUT |= IOUT_PIN
#define     IOUT_OFF                CMSDK_PB->DATAOUT &= ~IOUT_PIN

//PB1 -> KY2 -> 有线互联
#define     EXT_PIN		              0x0002
#define     EXT_KEY		             (CMSDK_PB->DATA & EXT_PIN)

//PB2 -> IO_PIN
#define     IO_PIN		              0x0004
#define     IO_PIN_IN               CMSDK_PB->OUTENABLECLR |= IO_PIN
#define     IO_PIN_OUT              CMSDK_PB->OUTENABLESET |= IO_PIN
#define     IO_PIN_ON               CMSDK_PB->DATAOUT |= IO_PIN
#define     IO_PIN_OFF              CMSDK_PB->DATAOUT &= ~IO_PIN

//PB6 -> RED
#define     RED_PIN		              0x0040
#define     RED_LED_ON              CMSDK_PB->DATAOUT &= ~RED_PIN
#define     RED_LED_OFF             CMSDK_PB->DATAOUT |= RED_PIN

//PB7 -> 黄灯
#define     YELLOW_PIN		          0x0080
#define     YELLOW_LED_ON           CMSDK_PB->DATAOUT &= ~YELLOW_PIN
#define     YELLOW_LED_OFF          CMSDK_PB->DATAOUT |= YELLOW_PIN

////PF0 -> KY4 -> AC_KEY
//#define     AC_PIN		              0x0001
//#define     AC_KEY		             (CMSDK_PF->DATA & AC_PIN)

//PF1 -> BOOST
#define     BOOST_PIN		            0x0002
#define     BOOST_ON                CMSDK_PF->DATAOUT |= BOOST_PIN
#define     BOOST_OFF               CMSDK_PF->DATAOUT &= ~BOOST_PIN

/* --------------------------------------------------------------------------- */
//短按失效
#define    KEY_NO_RESPONSE1         (EXTERNAL_ALARM_FLAG_MSK + NETWORK_ALARM_FLAG_MSK + NETWORK_TEST_FLAG_MSK + HUSH_FLAG_MSK + ALARM_FLAG_MSK + \
                                     SNOOZE_LOW_FLAG_MSK + SNOOZE_MEMORY_FLAG_MSK + FIND_ALARM_FLAG_MSK)
//长按失效
#define    KEY_NO_RESPONSE2         (EXTERNAL_ALARM_FLAG_MSK + NETWORK_ALARM_FLAG_MSK + NETWORK_TEST_FLAG_MSK + SNOOZE_FAULT_FLAG_MSK + FIND_ALARM_FLAG_MSK)

/* --------------------------------------------------------------------------- */
typedef struct
{
  uint32_t state;
	uint32_t masking;
	uint32_t signal;
}SYSTEM_DATA_typedef;
extern SYSTEM_DATA_typedef system_data;

/* --------------------------------------------------------------------------- */
#endif

