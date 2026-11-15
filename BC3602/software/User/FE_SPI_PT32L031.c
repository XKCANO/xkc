/*
**
*/
#include "FE_SPI_PT32L031.h"
#include <stdio.h>
#include "PT32x031.h"
#include "FE_HEAT_CFG.h"
#include "FE_IO.h"
/* --------------------------------------------------------------------------- */
#define  fe_spi_idle  0x00
#define  fe_spi_exe   0x01
#define  fe_spi_end   0x10
/* --------------------------------------------------------------------------- */
//masking
#define  SPI_IDLE_FLAG_POS  0
#define  SPI_IDLE_FLAG_MSK  (1UL << SPI_IDLE_FLAG_POS)
/* --------------------------------------------------------------------------- */
#define  SPI_BUFFER_SIZE  36
/* --------------------------------------------------------------------------- */
typedef struct
{
  unsigned char buffer[SPI_BUFFER_SIZE];
	unsigned char pos;
  unsigned char length;
	unsigned char masking;
  unsigned char step;
  unsigned char mode;
}FE_SPI_TypeDef;
/* --------------------------------------------------------------------------- */
FE_SPI_TypeDef spi;
/* --------------------------------------------------------------------------- */
/*
** SPI Initinalize
** PCLK: 24MHz
** Baud Rate: 125K
*/
void spi_open(void)
{
	//50K = 24M / (10 * (1+47))
	//125K = 14M / (6 * (1+31))
	//200K = 24M / (4 * (1+29)) = 24M / (40 * (1+2))
	SPI1->CPSR = 6;
	SPI1->CR0 = 31 * 256; 
//	SPI1->CR0 = (31 * 256 + SPI_CR0_DSS_8B);
	
	SPI1->CSCR = SPI_CSCR_SWCS + SPI_CSCR_SWSEL;
	
	SPI1->IE = 0;
	
	SPI1->ICR |= (SPI_ICR_RFNETO + SPI_ICR_RFOVF);
	
	SPI1->CR1 = SPI_CR1_SPIEN;
	
	//PA15 --> CS
	CMSDK_PA->ALTFUNCSET1 |= (GPIO_AFS_FUN2 << 28);
	//PB3 --> SCK
	//PB4 --> MISO
	//PB5 --> MOSI
	CMSDK_PB->ALTFUNCSET |= (GPIO_AFS_FUN2 << 20) + (GPIO_AFS_FUN2 << 16) + (GPIO_AFS_FUN2 << 12);
	
//	SPI1->CSCR &= ~SPI_CSCR_SWCS;
}

void spi_close(void)
{
//	SPI1->CSCR |= SPI_CSCR_SWCS;
	
	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC15;
	CMSDK_PB->ALTFUNCCLR |= GPIO_AFC_AFC5 + GPIO_AFC_AFC4 + GPIO_AFC_AFC3;
	
	SPI1->CR1 = 0;
	SPI1->CR0 = 0;
}

void spi_run(void)
{
	uint32_t i;

	switch(spi.step)
	{
	case 0:
		SPI1->ICR |= (SPI_ICR_RFNETO + SPI_ICR_RFOVF);
		SPI1->CSCR &= ~SPI_CSCR_SWCS;
	  spi.pos = 0;
	  spi.step++;
	  //break;
	case 1:
		if((SPI1->SR & SPI_SR_TFE) != 0)
		{
			SPI1->CR0 &= ~SPI_CR0_DSS;
			i = spi.length - spi.pos;
			if(i == 1)
			{
				SPI1->CR0 |= SPI_CR0_DSS_8B;
				i = spi.buffer[spi.pos];
			}
			else
			{
				SPI1->CR0 |= SPI_CR0_DSS_16B;
				i = (spi.buffer[spi.pos] << 8) + spi.buffer[spi.pos + 1];
			}
			SPI1->DR = i;
//			SPI1->DR = spi.buffer[spi.pos];
			spi.step++;
		}
		break;
	case 2:
		if((SPI1->SR & SPI_SR_RFNE) != 0)
		{
			i = SPI1->DR;
			if((SPI1->CR0 & SPI_CR0_DSS) == SPI_CR0_DSS_8B)
			{
				spi.buffer[spi.pos] = (unsigned char)i;
			}
			else
			{
			  spi.buffer[spi.pos + 1] = (unsigned char)i;
			  spi.buffer[spi.pos] = (unsigned char)(i >> 8);
			}
//			spi.buffer[spi.pos] = SPI1->DR;
			spi.step++;
		}
		break;
	case 3:
		spi.pos += 2;
//	  spi.pos++;
		if(spi.pos >= spi.length)
		{
			SPI1->CSCR |= SPI_CSCR_SWCS;
			spi.step = 0;
			spi.mode = fe_spi_idle;
		}
		else
		{
			spi.step -= 2;
		}			
		break;
  }
}
/*
 * @brief SPI主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 * 数据缓存长度16 bytes
 */
void fe_spi_process_run(void)
{
	if(spi.mode & 0x01)
	{
		spi_open();
		spi.masking |= SPI_IDLE_FLAG_MSK;
		spi.mode &= 0xFE;
	}
		
	if(spi.mode & 0x02)
	{
		spi_run();
	}
}
//void fe_spi_process_run(void)
//{
//	if((spi.mode & fe_spi_exe) != 0)
//	{
//		switch(spi.step)
//	  {
//		case 0:
//			spi_open();
//		  spi.pos = 0;
//		  spi.step++;
//			break;
//		case 1:
//			if((SPI1->SR & SPI_SR_TFE) != 0)
//			{
//				SPI1->DR = spi.buffer[spi.pos];
//				spi.step++;
//			}
//			break;
//		case 2:
//			if((SPI1->SR & SPI_SR_RFNE) != 0)
//			{
//				spi.buffer[spi.pos] = SPI1->DR;
//				spi.step++;
//			}
//			break;
//		case 3:
//			spi.pos++;
//		  if(spi.pos >= spi.length)
//			{
//				spi_close();
//		    spi.step = 0;
//		    spi.mode = fe_spi_idle;
//			}
//			else
//			{
//				spi.step -= 2;
//			}			
//			break;
//		case 4:
//			spi_close();
//		  spi.step = 0;
//		  spi.mode = fe_spi_idle;
//			break;
//	  }
//	}
//}

/*
 * @brief 查询SPI状态
 *
 * @param [in] :无
 *
 * @return:
 *   =0:SPI空闲
 *   =1:SPI忙
 *
 * @details 
 */
uint32_t fe_get_spi_state(void)
{
	if(spi.mode == fe_spi_idle)
	  return 0;
	else
		return 1;
}

/*
 * @brief SPI写数据
 *
 * @param [in] data 待发送数据首地址
 * @param [in] len 待发送数据长度
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区长度56
 */
uint32_t fe_spi_write(unsigned char *data, uint32_t len)
{
	if(spi.mode == fe_spi_idle)
	{
	  mem_data_copy(spi.buffer, data, len);
		spi.length = len;
//		spi.mode = fe_spi_exe;
		if(spi.masking == 0)
		{
			spi.mode = 0x3;
		}
		else
		{
			spi.mode = 0x2;
		}
	  return 0;
	}
	else 
		return 1;
}

/*
 * @brief SPI读数据
 *
* @param [in] data: 数据缓存首地址
* @param [in] len: 待发送数据长度
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details 数据缓冲区长度56
 */
uint32_t fe_spi_read(unsigned char *data, uint32_t len)
{
	if(spi.mode == fe_spi_idle)
	{
		mem_data_copy(data, spi.buffer, len);
		return 0;
	}
	else
		return 1;
}

/*
 * @brief 关闭SPI
 *
 * @param [in] :无
 *
 * @return:
 *   =0:SPI关闭
 *   =1:SPI忙
 *
 * @details 进入DeepSleep前，要确保SPI关闭状态
 */
uint32_t fe_enter_spi_sleep(void)
{
	if(spi.masking == 0)
	{
		return 0;
	}
	
	if(spi.mode == fe_spi_idle)
	{
		spi_close();
		spi.masking = 0;
		return 0;
	}
	else
	{
		return 1;
	}
}

