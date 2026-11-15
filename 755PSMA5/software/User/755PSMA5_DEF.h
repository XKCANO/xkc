#ifndef __FE_755LPSMA5_DEF_H
#define __FE_755LPSMA5_DEF_H

#include "stdint.h"
#include "PT32x076.h"
#include "755PSMA5_Timer_PT32L076.h"

/* --------------------------------------------------------------------------- */
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
#define     ALARM_FLAG_POS  0
#define     ALARM_FLAG_MSK  (1UL << ALARM_FLAG_POS)

#define     HUSH_FLAG_POS  1
#define     HUSH_FLAG_MSK  (1UL << HUSH_FLAG_POS)

#define     TEST_FLAG_POS  2
#define     TEST_FLAG_MSK  (1UL << TEST_FLAG_POS)

#define     LOW_BATTERY_FLAG_POS  3
#define     LOW_BATTERY_FLAG_MSK  (1UL << LOW_BATTERY_FLAG_POS)

#define     SNOOZE_LOW_FLAG_POS  4
#define     SNOOZE_LOW_FLAG_MSK  (1UL << SNOOZE_LOW_FLAG_POS)

#define     ALARM_MEMORY_FLAG_POS  5
#define     ALARM_MEMORY_FLAG_MSK  (1UL << ALARM_MEMORY_FLAG_POS)

#define     SNOOZE_MEMORY_FLAG_POS  6
#define     SNOOZE_MEMORY_FLAG_MSK  (1UL << SNOOZE_MEMORY_FLAG_POS)

#define     SENSOR_FAULT_FLAG_POS  7
#define     SENSOR_FAULT_FLAG_MSK  (1UL << SENSOR_FAULT_FLAG_POS)

#define     SNOOZE_FAULT_FLAG_POS  8
#define     SNOOZE_FAULT_FLAG_MSK  (1UL << SNOOZE_FAULT_FLAG_POS)

#define     EXTERNAL_ALARM_FLAG_POS  9
#define     EXTERNAL_ALARM_FLAG_MSK  (1UL << EXTERNAL_ALARM_FLAG_POS)

#define     EXTERNAL_ERROR_FLAG_POS  10
#define     EXTERNAL_ERROR_FLAG_MSK  (1UL << EXTERNAL_ERROR_FLAG_POS)

#define     RELAYIN_ALARM_FLAG_POS  11
#define     RELAYIN_ALARM_FLAG_MSK  (1UL << RELAYIN_ALARM_FLAG_POS)

#define     SHORT_TEST_FLAG_POS  12
#define     SHORT_TEST_FLAG_MSK  (1UL << SHORT_TEST_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM SIGNAL
#define     DEVICE_ALARM_FLAG_POS  0
#define     DEVICE_ALARM_FLAG_MSK  (1UL << DEVICE_ALARM_FLAG_POS)

#define     DEVICE_HUSH_FLAG_POS  1
#define     DEVICE_HUSH_FLAG_MSK  (1UL << DEVICE_HUSH_FLAG_POS)

#define     DEVICE_TEST_FLAG_POS  2
#define     DEVICE_TEST_FLAG_MSK  (1UL << DEVICE_TEST_FLAG_POS)

#define     DEVICE_LOW_BATTERY_FLAG_POS  3
#define     DEVICE_LOW_BATTERY_FLAG_MSK  (1UL << DEVICE_LOW_BATTERY_FLAG_POS)

#define     DEVICE_SNOOZE_LOW_FLAG_POS  4
#define     DEVICE_SNOOZE_LOW_FLAG_MSK  (1UL << DEVICE_SNOOZE_LOW_FLAG_POS)

#define     DEVICE_ALARM_MEMORY_FLAG_POS  5
#define     DEVICE_ALARM_MEMORY_FLAG_MSK  (1UL << DEVICE_ALARM_MEMORY_FLAG_POS)

#define     DEVICE_SNOOZE_MEMORY_FLAG_POS  6
#define     DEVICE_SNOOZE_MEMORY_FLAG_MSK  (1UL << DEVICE_SNOOZE_MEMORY_FLAG_POS)

#define     DEVICE_SENSOR_FAULT_FLAG_POS  7
#define     DEVICE_SENSOR_FAULT_FLAG_MSK  (1UL << DEVICE_SENSOR_FAULT_FLAG_POS)

#define     DEVICE_SNOOZE_FAULT_FLAG_POS  8
#define     DEVICE_SNOOZE_FAULT_FLAG_MSK  (1UL << DEVICE_SNOOZE_FAULT_FLAG_POS)

#define     DEVICE_EXTERNAL_ALARM_FLAG_POS  9
#define     DEVICE_EXTERNAL_ALARM_FLAG_MSK  (1UL << DEVICE_EXTERNAL_ALARM_FLAG_POS)

#define     DEVICE_EXTERNAL_ERROR_FLAG_POS  10
#define     DEVICE_EXTERNAL_ERROR_FLAG_MSK  (1UL << DEVICE_EXTERNAL_ERROR_FLAG_POS)

#define     DEVICE_RELAYIN_ALARM_FLAG_POS  11
#define     DEVICE_RELAYIN_ALARM_FLAG_MSK  (1UL << DEVICE_RELAYIN_ALARM_FLAG_POS)

#define     DEVICE_SHORT_TEST_FLAG_POS  12
#define     DEVICE_SHORT_TEST_FLAG_MSK  (1UL << DEVICE_SHORT_TEST_FLAG_POS)

/* --------------------------------------------------------------------------- */
//SYSTEM MASKING
#define     SYSTEM_INITIALIZE_FLAG_POS  0
#define     SYSTEM_INITIALIZE_FLAG_MSK  (1UL	<< SYSTEM_INITIALIZE_FLAG_POS)

#define     SYSTEM_INTERRUPT_FLAG_POS  1
#define     SYSTEM_INTERRUPT_FLAG_MSK  (1UL << SYSTEM_INTERRUPT_FLAG_POS)

#define     MESSAGE_FLAG_POS  2
#define     MESSAGE_FLAG_MSK  (1UL << MESSAGE_FLAG_POS)

#define     AC_CHECK_FLAG_POS  3
#define     AC_CHECK_FLAG_MSK  (1UL << AC_CHECK_FLAG_POS)

#define     EXT_CHECK_FLAG_POS  4
#define     EXT_CHECK_FLAG_MSK  (1UL << EXT_CHECK_FLAG_POS)

#define     RIN_CHECK_FLAG_POS  5
#define     RIN_CHECK_FLAG_MSK  (1UL << RIN_CHECK_FLAG_POS)

#define     DEBUG_FLAG_POS  6
#define     DEBUG_FLAG_MSK  (1UL << DEBUG_FLAG_POS)

#define     TIMER1_UPDATE_FLAG_POS  7
#define     TIMER1_UPDATE_FLAG_MSK  (1UL << TIMER1_UPDATE_FLAG_POS)

#define     LOW_SOUND_FLAG_POS  8
#define     LOW_SOUND_FLAG_MSK  (1UL << LOW_SOUND_FLAG_POS)

#define     KEY3_DOWN_FLAG_POS  9
#define     KEY3_DOWN_FLAG_MSK  (1UL << KEY3_DOWN_FLAG_POS)

#define     KEY3_08S_FLAG_POS  10
#define     KEY3_08S_FLAG_MSK  (1UL << KEY3_08S_FLAG_POS)

#define     KEY3_10S_FLAG_POS  11
#define     KEY3_10S_FLAG_MSK  (1UL << KEY3_10S_FLAG_POS)

#define     KEY3_UP_FLAG_POS  12
#define     KEY3_UP_FLAG_MSK  (1UL << KEY3_UP_FLAG_POS)

#define     KEY5_OUTPUT_FLAG_POS  13
#define     KEY5_OUTPUT_FLAG_MSK  (1UL << KEY5_OUTPUT_FLAG_POS)

#define     KEY2_OUT_FLAG_POS  14
#define     KEY2_OUT_FLAG_MSK  (1UL << KEY2_OUT_FLAG_POS)

#define     KEY2_PENDING_FLAG_POS  15
#define     KEY2_PENDING_FLAG_MSK  (1UL << KEY2_PENDING_FLAG_POS)

#define     TIMER1_CLOSE_FLAG_POS    16
#define     TIMER1_CLOSE_FLAG_MSK   (1UL << TIMER1_CLOSE_FLAG_POS)

/* --------------------------------------------------------------------------- */
//RED  -> PA5
#define     RED_PIN         0x0020
#define     RED_LED_ON      GPIOA->BRR |= RED_PIN
#define     RED_LED_OFF     GPIOA->BSR |= RED_PIN

//RED1 -> PA6
#define     RED1_PIN        0x0040
#define     RED1_LED_ON     GPIOA->BRR |= RED1_PIN
#define     RED1_LED_OFF    GPIOA->BSR |= RED1_PIN

#define     HRED_LED_ON     GPIOA->BRR |= RED_PIN + RED1_PIN
#define     HRED_LED_OFF    GPIOA->BSR |= RED_PIN + RED1_PIN

//KY3  -> PA7
#define     TEST_PIN        0x0080
#define     TEST_KEY       (GPIOA->DR & TEST_PIN)

//KY4 -> PA10
#define     AC_PIN          0x0400
#define     AC_KEY         (GPIOA->DR & AC_PIN)

//HB -> PA11
#define     HB_PIN          0x0800

//HS -> PA12
#define     HS_PIN          0x1000

//TX1 -> PA14
#define     TX1_PIN         0x4000
#define     TX1_OUT_L       GPIOA->BRR |= TX1_PIN

//IO_PIN -> PB3
#define     IO_PIN          0x0008
#define     IO_KEY         (GPIOB->DR & IO_PIN)
#define     IO_PIN_IN       GPIOB->OEC |= IO_PIN
#define     IO_PIN_OUT      GPIOB->OES |= IO_PIN
#define     IO_PIN_H        GPIOB->BSR |= IO_PIN
#define     IO_PIN_L        GPIOB->BRR |= IO_PIN

//LOCAL_KEY KY1 -> PB4
#define     LOCAL_PIN       0x0010
#define     LOCAL_KEY      (GPIOB->DR & LOCAL_PIN)

//KY2 -> PB5
#define     EXT_PIN         0x0020
#define     EXT_KEY        (GPIOB->DR & EXT_PIN)

//I_OUT --> PB6
#define     IOUT_PIN        0x0040
#define     IOUT_ON         GPIOB->BSR |= IOUT_PIN
#define     IOUT_OFF        GPIOB->BRR |= IOUT_PIN

/* --------------------------------------------------------------------------- */
//timer1
#define     MIN_TIMER_US        295
#define     MAX_TIMER_US        305

#define     LOW_TIMER_US        270 // 1/ 270 = 3.7kHz

/* --------------------------------------------------------------------------- */
//timer5
#define     KEY3_TIMER 				       timer5.t[0]
#define     KEY_TIMER 		           timer5.t[1]
#define     TIMER1_TIMER 		         timer5.t[2]
#define     GENERAL_TIMER 				   timer5.t[3]
#define     LED_TIMER 				       timer5.t[4]
#define     BUZZER_TIMER 				     timer5.t[5]
#define     EXT_TIMER 				       timer5.t[6]
#define     RIN_TIMER 				       timer5.t[7]

#define     SMOKE_TIMER 				     timer5.t[8]
#define     ALARM_TIMER 				     timer5.t[9]
#define     ALARM_TIMER1 				     timer5.t[10]
#define     BATTERY_TIMER 				   timer5.t[11]
#define     SNOOZE_FAULT_TIMER       timer5.t[12]
#define     SNOOZE_LOW_TIMER         timer5.t[13]
#define     SNOOZE_MEMORY_TIMER      timer5.t[14]
#define     ALARM_MEMORY_TIMER       timer5.t[15]

/* --------------------------------------------------------------------------- */
//按键长按失效
#define     KEY3_NO_RESPONSE       (EXTERNAL_ALARM_FLAG_MSK + RELAYIN_ALARM_FLAG_MSK + EXTERNAL_ERROR_FLAG_MSK + SHORT_TEST_FLAG_MSK)

//按键短按失效
#define     KEY3_NO_RESPONSE1      (EXTERNAL_ALARM_FLAG_MSK + RELAYIN_ALARM_FLAG_MSK + EXTERNAL_ERROR_FLAG_MSK + HUSH_FLAG_MSK + SNOOZE_MEMORY_FLAG_MSK)


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

