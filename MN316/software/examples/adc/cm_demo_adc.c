/**
 * @file        cm_demo_adc.c
 * @brief       OpenCPU adc测试例程
 * @copyright   Copyright © 2021 China Mobile IOT. All rights reserved.
 */
 

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include "cm_adc.h"
#include "cm_os.h"
#include "cm_common.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define CM_DEMO_ADC_LOG     CM_DEMO_LOG


/****************************************************************************
 * Private Types
 ****************************************************************************/


 
/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Data
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * @brief  adc接口函数测试示例
 *
 * @return  void
 *
 * @details More details
 */
 int cm_test_adc(unsigned char **cmd, int len)
{

	uint32_t voltage;
	int32_t ret;
	CM_DEMO_ADC_LOG("adc test start!!\n");

	ret = cm_adc_vbat_read(&voltage);
	if(ret != RET_SUCCESS)
	{
		CM_DEMO_ADC_LOG("adc vbate read err,ret=%d\n", ret);
		return -1;
	}
	CM_DEMO_ADC_LOG("adc vbate read:%ld(mv)!!\n",voltage);


	cm_adc_open(CM_ADC_0);
	//测试ADC0
	ret = cm_adc_read(CM_ADC_0,&voltage);
	cm_adc_close(CM_ADC_0);
	if(ret != RET_SUCCESS)
	{
		CM_DEMO_ADC_LOG("adcCM_ADC_0 read err,ret=0x%08x\n", ret);
		return -1;
	}
	CM_DEMO_ADC_LOG("adc CM_ADC_0 read:%ld(mv)!!\n",voltage);

	CM_DEMO_ADC_LOG("adc test end!!\n");
	return 0;

}
