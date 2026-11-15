#include "FE_755LHA_PT32L031_CFG.h"
#include "FE_HEAT_CFG.h"
#include "PT32X031.h"

/*
 * @brief 初始化GPIO
 *
 * @param [in]:无
 *
 * @return:无
 * 
 * @details
 * 
 */
void fe_initializing_gpio(void)
{
}

/*
 * @brief 初始化RAM
 *
 * @param [in]:无
 *
 * @return:无
 * 
 * @details
 * SRAM 4KB:  0x20000000 - 0x20000FFF 
 * SRAM 16KB: 0x20000000 - 0x20003FFF 
 */
void fe_clear_ram(void)
{
	uint32_t i, l;
	l = __get_MSP();
	l = (l & 0x00003FFF) / 4;
	i = 0;
	do{
		((uint32_t *)CMSDK_SRAM_BASE)[i] = 0;
		i++;
	}while(i < l);
}




