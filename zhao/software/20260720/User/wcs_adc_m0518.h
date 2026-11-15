#ifndef __WCS_ADC_M0518_H__
#define __WCS_ADC_M0518_H__


#include "M0518.h"


#define ADC0_SIZE 64


typedef struct
{
  uint16_t value[ADC0_SIZE];
  uint16_t idx;
}ADC0_typedef;
extern ADC0_typedef adc0;

void Open_Adc_Ch0(void);
void Close_Adc_Ch0(void);

#endif



