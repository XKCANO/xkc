#ifndef __KD715A_BATTERYLOW_PT32L031_H
#define __KD715A_BATTERYLOW_PT32L031_H


#include "pt32x031.h"
#include "FE_MATH.h"
#include "KD715A_DEF.h"
#include "ADC_PT32L031.h"
#include "FE_semaphore.h"


#define  BATTERY_DATA_SIZE     3
#define  RomLowVoltage         2.6


typedef struct
{
	unsigned char step;
  unsigned char mode;
	unsigned char count;
	unsigned char data[BATTERY_DATA_SIZE];
	
	unsigned short v_data;
	unsigned short v_vref;
}Battery_typedef;


void measure_battery(void);
void CheckIsLowbattery(void);
void CheckVoltageIsOk(void);
void array_right(unsigned char *arr, unsigned char l);

extern Battery_typedef bat;

#endif

