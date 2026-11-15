#ifndef __M0518_DEF_H__
#define __M0518_DEF_H__


#include "M0518.h"
#include "wcs_timer_m0518.h"

/* --------------------------------------------------------------------------- */
//beta version
#define   _BETA_VERSION   0
/* --------------------------------------------------------------------------- */
//GPIO
//PB2 -> DEBUG
#define DEBUG_PIN 0x0004
#define DEBUG_KEY (PB->PIN & DEBUG_PIN)

//PA13 -> KEY1
#define KEY1_PIN 0x2000
#define KEY1_KEY (PA->PIN & KEY1_PIN)

//PA14 -> KEY2
#define KEY2_PIN 0x4000
#define KEY2_KEY (PA->PIN & KEY2_PIN)

//PA15 -> KEY3
#define KEY3_PIN 0x8000
#define KEY3_KEY (PA->PIN & KEY3_PIN)

//PC0 -> LEDH
#define LEDH_PIN 0x0001
#define LEDH_ON  PC->DOUT &= ~LEDH_PIN
#define LEDH_OFF PC->DOUT |= LEDH_PIN


/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
//timer
#define  KEY1_SCAN_TIMER       timer.t[0]
#define  KEY2_SCAN_TIMER       timer.t[1]
#define  KEY3_SCAN_TIMER       timer.t[2]
#define  TIMER1_CAPTURE_TIMER  timer.t[3]
#define  ADC_CAPTURE_TIMER     timer.t[4]


/* --------------------------------------------------------------------------- */

typedef struct
{
  uint16_t masking;
  uint16_t state;
  uint16_t signal;
  uint16_t resource;
  
  uint8_t red_value;
  uint8_t led_value;
  uint16_t reserve;
  
}SYSTEM_DATA_TYPEDEF;
extern SYSTEM_DATA_TYPEDEF system_data;

/* --------------------------------------------------------------------------- */
//masking
#define  SYSTEM_INIT_FLAG_POS  0
#define  SYSTEM_INIT_FLAG_MSK  (1 << SYSTEM_INIT_FLAG_POS)

#define  SYSTEM_DEBUG_FLAG_POS  1
#define  SYSTEM_DEBUG_FLAG_MSK  (1 << SYSTEM_DEBUG_FLAG_POS)

#define  SYSTEM_MESSAGE_FLAG_POS  2
#define  SYSTEM_MESSAGE_FLAG_MSK  (1 << SYSTEM_MESSAGE_FLAG_POS)

#define  TIMER0_INIT_FLAG_POS  3
#define  TIMER0_INIT_FLAG_MSK  (1 << TIMER0_INIT_FLAG_POS)

#define  TIMER0_TIF_FLAG_POS  4
#define  TIMER0_TIF_FLAG_MSK  (1 << TIMER0_TIF_FLAG_POS)

#define  SYSTEM_AUTO_MODE_FLAG_POS  5
#define  SYSTEM_AUTO_MODE_FLAG_MSK  (1 << SYSTEM_AUTO_MODE_FLAG_POS)


/* --------------------------------------------------------------------------- */
//state
#define  TIMER0_UPDATE_STATE_FLAG_POS  0
#define  TIMER0_UPDATE_STATE_FLAG_MSK  (1 << TIMER0_UPDATE_STATE_FLAG_POS)

/* --------------------------------------------------------------------------- */
//signal
#define  UPDATE_LED_SIGNAL_FLAG_POS  0
#define  UPDATE_LED_SIGNAL_FLAG_MSK  (1 << UPDATE_LED_SIGNAL_FLAG_POS)

#define  UPDATE_RED_SIGNAL_FLAG_POS  1
#define  UPDATE_RED_SIGNAL_FLAG_MSK  (1 << UPDATE_RED_SIGNAL_FLAG_POS)

#define  TIMER0_UPDATE_SIGNAL_FLAG_POS  2
#define  TIMER0_UPDATE_SIGNAL_FLAG_MSK  (1 << TIMER0_UPDATE_SIGNAL_FLAG_POS)

#define  ADC0_UPDATE_SIGNAL_FLAG_POS  3
#define  ADC0_UPDATE_SIGNAL_FLAG_MSK  (1 << ADC0_UPDATE_SIGNAL_FLAG_POS)








#endif



