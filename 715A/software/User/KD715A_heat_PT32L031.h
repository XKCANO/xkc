#ifndef __KD715A_HEAT_PT32L031_H
#define __KD715A_HEAT_PT32L031_H
/* ====================================================== */
#include "stdint.h"
#include "KD715A_DEF.h"
#include "FE_IO.h"
#include "FE_MATH.h"
#include "ADC_PT32L031.h"
#include "KD715A_Timer_PT32L031.h"
#include "KD715A_Batterylow_PT32L031.h"
/* ====================================================== */

/* ====================================================== */

/* ====================================================== */
#define T_DATA_SIZE  512
#define U_DATA_SIZE  128
/* ====================================================== */
#define CAL_BASE_TIME 64
/* ====================================================== */
typedef struct
{
	unsigned char step;
	unsigned char mode;

	unsigned char normal_time;
	unsigned char fault_time;
	
	unsigned short ntc_data;
	unsigned short base_data; //Temperature Base
	
	unsigned short counter;
  unsigned short rate;
	unsigned short t_average_128;
	unsigned short stop_data;
	
	unsigned short t_data[T_DATA_SIZE]; //Temperature
	unsigned short t_minute[U_DATA_SIZE]; //Increment
}HEAT_TypeDef;
/* ====================================================== */
extern HEAT_TypeDef Heat;
/* ====================================================== */

/*
 * @brief HEAT主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_heat_process_run(void);
/* ====================================================== */
#endif

