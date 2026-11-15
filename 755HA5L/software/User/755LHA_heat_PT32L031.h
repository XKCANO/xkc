#ifndef __755LHA_HEAT_PT32L031_H
#define __755LHA_HEAT_PT32L031_H


#include "stdint.h"
#include "755LHA_DEF.h"
#include "FE_MATH.h"
#include "ADC_PT32L031.h"
#include "755LHA_Timer_PT32L031.h"
#include "755LHA_Batterylow_PT32L031.h"

/* --------------------------------------------------------------------------- */
#define T_DATA_SIZE  512
#define U_DATA_SIZE  128
#define CAL_BASE_TIME 64

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char step;
	unsigned char mode;

	unsigned char normal_time;
	unsigned char fault_time;
	
	unsigned short ntc_data;
	unsigned short base_data; //Temperature Base 实际为符号数
	
	unsigned short counter;
  unsigned short rate;
	unsigned short t_average_128;
	unsigned short stop_data;
	
	unsigned short t_data[T_DATA_SIZE]; //Temperature 实际为符号数
	unsigned short t_minute[U_DATA_SIZE]; //Increment
}HEAT_TypeDef;
extern HEAT_TypeDef heat;

/* --------------------------------------------------------------------------- */
void heat_process_run(void);
void data_treating(void);
/* --------------------------------------------------------------------------- */
#endif

