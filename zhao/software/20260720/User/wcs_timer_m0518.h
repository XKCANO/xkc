#ifndef __WCS_TIMER_M0518_H__
#define __WCS_TIMER_M0518_H__


#include "M0518.h"

#define TIMER_SIZE 20

typedef struct
{
  uint32_t t[TIMER_SIZE];
}Timer_typedef;
extern Timer_typedef timer;


typedef struct
{
  uint32_t capture_value[2];
  uint32_t period_value[128];
  uint16_t idx;
  uint16_t cont;

}Timer0_typedef;
extern Timer0_typedef timer0;


void Open_System_Timer(void);
void Check_Sytem_Timer(void);
void Close_System_Timer(void);
void Open_Timer0(void);
void Close_Timer0(void);



#endif



