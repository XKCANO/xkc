#include <stdio.h>
#include "PT32x031.h"
#include "ADC_PT32L031.h"
/* --------------------------------------------------------------------------- */
#define ADC_CR_CLKDIV_0DIV  ((uint32_t)0x00000000)
#define ADC_CR_CLKDIV_2DIV  ((uint32_t)0x00000100)
#define ADC_CR_CLKDIV_4DIV  ((uint32_t)0x00000200)
#define ADC_CR_CLKDIV_8DIV  ((uint32_t)0x00000300)
/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned short *p;
	unsigned char *s;
}ADC1_TypeDef;
/* --------------------------------------------------------------------------- */
ADC1_TypeDef adc;
/* --------------------------------------------------------------------------- */

/*
 * @brief ADC初始化
 *
 * @param [in] s：被调用函数主体的step
 *
 * @return: 无
 *
 * @details
 * ADC Initial
 * PCLK: 24MHz
 * TRSTN >= 1us
 */
void fe_adc_init(unsigned char *s)
{
	adc.s = s;
	ADC->TRSTN = 48; //2us
}

/*
 * @brief ADC关闭
 *
 * @param [in]：无
 *
 * @return: 无
 *
 * @details
 */
void fe_adc_kill(void)
{
	NVIC_DisableIRQ(ADC_IRQn);
  ADC->CR &= ~ADC_CR_ADEN;
	ADC->CR = 0x000F0000;
}

/*
 * @brief 打开通道1
 *
 * @param [in] d:数据返回指定地址
 *
 * @return:无
 *
 * @details 单次转换
 */
void fe_adc_open_scm_in1(unsigned short *d)
{
	adc.p = d;
	
	//IN1 --> PA1
	ADC->CR = ADC_CR_CHSEL_1 + ADC_CR_EOCIE + ADC_CR_HSSMP;
	
	ADC->SR |= ADC_SR_EOC;
	NVIC_EnableIRQ(ADC_IRQn);
	
	ADC->CR |= ADC_CR_ADEN;
	while((ADC->SR & ADC_SR_ADRDY) == 0);
	
	ADC->CR |= ADC_CR_ADSTART;
}

/*
 * @brief 打开通道12
 *
 * @param [in] d:数据返回指定地址
 *
 * @return:无
 *
 * @details 单次转换，内部参考电压
 * IN12 --> BANDGAP --> 1.0V
 */
void fe_adc_open_scm_in12(unsigned short *d)
{
	adc.p = d;
	
	//IN12 --> BANDGAP --> 1.0V
	ADC->CR = ADC_CR_CHSEL_12 + ADC_CR_EOCIE + ADC_CR_HSSMP;// + ADC_CR_ADCAL;
	
	ADC->SR |= ADC_SR_EOC;
	NVIC_EnableIRQ(ADC_IRQn);
	
	ADC->CR |= ADC_CR_ADEN;
	while((ADC->SR & ADC_SR_ADRDY) == 0);
	
	ADC->CR |= ADC_CR_ADSTART;
}

/*
** ADC interrupt callback
*/
void ADC_Handler(void)
{
	ADC->SR |= ADC_SR_EOC;
	
	NVIC_DisableIRQ(ADC_IRQn);
	
	*(adc.p) = ADC->DR;
	
  ADC->CR &= ~ADC_CR_ADEN;
	
	*(adc.s) += 1;
	
	ADC->CR = 0x000F0000;
}

/*
** ADC Value Calculate
*/
uint32_t CalculateActualVoltage(uint32_t data)
{
	uint32_t i;
	// 4096 / data * 64
	i = 262144 / data;
	return i;	
}


/*---------------------------------------------------------------------------------------------------------*/







