#include "FE_755LHA_UART_PT32L031.h"
#include <stdio.h>
#include "PT32x031.h"
#include "FE_HEAT_CFG.h"
#include "FE_IO.h"
#include "FE_math.h"
/* --------------------------------------------------------------------------- */
#define  fe_uart_idle    0x00
#define  fe_uart_exe     0x01
#define  fe_uart_busy		 0x10
#define  fe_uart_end		 0x20
#define  fe_uart_err		 0x40
#define  fe_uart_finish  0x80
/* --------------------------------------------------------------------------- */
#define _SYN0 0x55
#define _SYN1 0xAA
/* --------------------------------------------------------------------------- */
//Frame Control
#define _SETUP 0xB4
#define _OUT   0x87
#define _IN    0x96
#define _DATA0 0xC3
#define _DATA1 0xD2
#define _SOF   0xA5
#define _ACK   0x4B
#define _NAK   0x5A
/* --------------------------------------------------------------------------- */
#define READ_EEPROM_CMD 0x60

#define READ_PRODUCT_CODE 0x11
#define READ_VERSION 0x12
#define READ_DAY_TIME 0x13

#define READ_25C_SMOKE_PARAMETER 0x14
#define READ_SMOKE_DENSITY_PARAMETER 0x15
#define READ_RADIANT_INTENSITY 0x16
#define READ_TEMPERATURE_PARAMETER 0x17
#define READ_BATTERY_PARAMETER 0x18

//#define READ_LINEARITY 0x19
#define READ_TEMPERATURE_PARAMETER_2 0x19

#define READ_PARTICLE_DIAMETER 0x1A
#define READ_PARTICLE_VARIANCE 0x1B

#define READ_PRODUCT_DATE 0x1C
/* --------------------------------------------------------------------------- */
#define GET_UID  0x21
#define GET_KEY  0x22
#define GET_DATA 0x23
/* --------------------------------------------------------------------------- */
#define WRITE_EEPROM_CMD 0x90

#define WRITE_PRODUCT_CODE             0x31
#define WRITE_VERSION                  0x32
#define WRITE_DAY_TIME                 0x33

#define WRITE_25C_SMOKE_PARAMETER      0x34
#define WRITE_SMOKE_DENSITY_PARAMETER  0x35
#define WRITE_RADIANT_INTENSITY        0x36
#define WRITE_TEMPERATURE_PARAMETER    0x37
#define WRITE_BATTERY_PARAMETER        0x38

//#define WRITE_LINEARITY 0x39
#define WRITE_TEMPERATURE_PARAMETER_2  0x39

#define WRITE_PARTICLE_DIAMETER        0x3A
#define WRITE_PARTICLE_VARIANCE        0x3B

#define WRITE_PRODUCT_DATE             0x3C
/* --------------------------------------------------------------------------- */
#define SETUP_SAMPLING_FLAG 0x41
#define CLEAR_SAMPLING_FLAG 0x42
#define OPEN_BUZZER  0x43
#define ENTER_DEEP_SLEEP  0x44
/* --------------------------------------------------------------------------- */
//#define SET_AT_CLOSE       0x50
//#define SET_BAUDRATE_9600  0x51
#define SET_LED_COLOR        0x52
#define GET_STATE            0x53
#define IN_DATA              0x54
#define SET_T3412            0x55
/* --------------------------------------------------------------------------- */
//Sci.mode
#define SCI_RX_CMD fe_uart_exe
#define SCI_TX_CMD fe_uart_exe
//uart.mode
//#define BAUDRATE_115200_CMD 0x02
//#define OUTPUT_DATA_CMD 0x04
//#define AT_ATCLOSE_CMD 0x08
//#define DEBUG_MODE_CMD 0x10
//uart.step
#define UART_QUEUE_STEP 2
#define UART_TX_STEP 5
/* --------------------------------------------------------------------------- */
//marking
#define  SCI_TIMER_COUNTING_FLAG_POS  0
#define  SCI_TIMER_COUNTING_FLAG_MSK  (1UL << SCI_TIMER_COUNTING_FLAG_POS)

#define  SOF_FLAG_POS  2
#define  SOF_FLAG_MSK  (1UL << SOF_FLAG_POS)

#define  UART_EVENT_UPDATE_FLAG_POS  3
#define  UART_EVENT_UPDATE_FLAG_MSK  (1UL << UART_EVENT_UPDATE_FLAG_POS)

//#define  SCI_TRANSMITTING_FLAG_POS  1
//#define  SCI_TRANSMITTING_FLAG_MSK  (1UL << SCI_TRANSMITTING_FLAG_POS)

//#define  SCI_RECEIVED_FLAG_POS  3
//#define  SCI_RECEIVED_FLAG_MSK  (1UL << SCI_RECEIVED_FLAG_POS)
/* --------------------------------------------------------------------------- */
#define SCI_TIMER Timer.t[0] //1ms
/* --------------------------------------------------------------------------- */
#define SCI_RX_BUFFER_SIZE 38
#define SCI_TX_BUFFER_SIZE 42
/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char rx_buffer[SCI_RX_BUFFER_SIZE];
	unsigned char tx_buffer[SCI_TX_BUFFER_SIZE];
//80
	unsigned short no;
	
	unsigned char rx_cmd;
	unsigned char rx_len;
	
	unsigned char reserved[2];

	unsigned char rx_pos;
	unsigned char rx_mode;
	
	unsigned char tx_total;
	unsigned char tx_pos;

	unsigned char tx_step;
	unsigned char tx_mode;
//12
}FE_SCI_TypeDef;
/* --------------------------------------------------------------------------- */
FE_SCI_TypeDef Sci;
/* --------------------------------------------------------------------------- */
FE_UART_TypeDef uart;
/* --------------------------------------------------------------------------- */
/*
** UART Initinalize
** PCLK: 24MHz
** Baud Rate: 9600
*/
void OpenUART(void)
{
	//TX --> PA14
	//RX --> PA15
//CMSDK_PA->ALTFUNCSET1 |= (GPIO_AFS_FUN3 << 28) + (GPIO_AFS_FUN3 << 24);
	//TX --> PA9
	//RX --> PA10
	CMSDK_PA->ALTFUNCSET1 |= (GPIO_AFS_FUN4 << 8) + (GPIO_AFS_FUN4 << 4);
	
	//24000000 / 16 / 156 = 9615
	UART1->BRR = 156;
	UART1->CR = UART_CR_STOP_1BIT + UART_CR_MODE_D8BITS;
	__NOP();
	UART1->CR |= UART_CR_RXEN + UART_CR_BRUN;
}
/*
** Close UART
*/
void CloseUART(void)
{
	UART1->TRR = 0;
	UART1->RRR = 0;
	UART1->SR |= 0x70;
	UART1->CR = 0;
	
//	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC15 + GPIO_AFC_AFC14;
	//TX --> PA9
	//RX --> PA10
	CMSDK_PA->ALTFUNCCLR |= GPIO_AFC_AFC10 + GPIO_AFC_AFC9;
}
/*
** Run SCI Receiving Process
*/
void RunSciReceivingProc(void)
{
	if(UART1->SR & UART_ISR_OVERR)
	{
		UART1->SR |= 0x70;
		UART1->RRR = 0;
		return;
	}
	
	if(UART1->SR & UART_ISR_RXNE)
  {
		if(Sci.rx_mode & fe_uart_finish)
		{
			Sci.rx_buffer[0] = UART1->BR;
			return;
		}
		
    Sci.rx_buffer[Sci.rx_pos] = UART1->BR;
		Sci.rx_pos++;
		
		if(Sci.rx_pos > 0)
	  {
		  if(Sci.rx_buffer[0] == _SYN0)
		  {
				if((uart.masking & SCI_TIMER_COUNTING_FLAG_MSK) == 0)
				{
					SCI_TIMER = 0;
					uart.masking |= SCI_TIMER_COUNTING_FLAG_MSK;
				}
			  if(Sci.rx_pos > 1)
			  {
				  if(Sci.rx_buffer[1] == _SYN1)
				  {
						if(Sci.rx_pos > 2)
						{
							if(Sci.rx_buffer[2] <= SCI_RX_BUFFER_SIZE)
							{
							  if(Sci.rx_pos >= Sci.rx_buffer[2])
							  {
					        if(fe_calculate_crc(Sci.rx_buffer, Sci.rx_buffer[2]) == 0)
						      {
							      Sci.rx_mode |= fe_uart_finish;
							      Sci.rx_pos = 0;
							      uart.masking &= ~SCI_TIMER_COUNTING_FLAG_MSK;
									}
							  }
						  }
							else
							{
								Sci.rx_pos = 0;
								uart.masking &= ~SCI_TIMER_COUNTING_FLAG_MSK;
							}
					  }
				  }
				  else
				  {
					  Sci.rx_pos = 0;
				  }
			  }
		  }
		  else
		  {
				if(Sci.rx_buffer[0] == _SOF)
			  {
					uart.masking |= SOF_FLAG_MSK;
			  }
			  Sci.rx_pos = 0;
		  }
	  }
  }
	
	if((uart.masking & SCI_TIMER_COUNTING_FLAG_MSK) != 0)
	{
		if(SCI_TIMER >= 500)
		{
		  Sci.rx_pos = 0;
		  uart.masking &= ~SCI_TIMER_COUNTING_FLAG_MSK;
		}
	}
}
/*
** Run SCI Transmitting Process
*/
void RunSciTransmittingProc(void)
{
	uint32_t i;
	switch(Sci.tx_step)
	{
		case 0:
			Sci.tx_buffer[0] = _SYN0;
		  Sci.tx_buffer[1] = _SYN1;
			Sci.tx_buffer[2] = Sci.tx_total + 2;
			i = fe_calculate_crc(Sci.tx_buffer, Sci.tx_total);
		  Sci.tx_buffer[Sci.tx_total] = (unsigned char)(i >> 8);
		  Sci.tx_total++;
		  Sci.tx_buffer[Sci.tx_total] = (unsigned char)i;
		  Sci.tx_total++;
		  Sci.tx_pos = 0;
		  Sci.tx_step++;
      break;
		
		case 1:
			if(UART1->SR & UART_ISR_TXE)
			{
				UART1->BR = Sci.tx_buffer[Sci.tx_pos];
				Sci.tx_step++;
			}
			break;
			
		case 2:
			Sci.tx_pos++;
			if(Sci.tx_pos < Sci.tx_total)
			{
			  Sci.tx_step--;
			}
			else
			{
				Sci.tx_step++;
			}
			break;
			
		case 3:
			if(UART1->SR & UART_ISR_TXEND)
			{
				Sci.tx_step = 0;
				Sci.tx_mode = fe_uart_finish;
			}
			break;
	}
}
/*
**
*/
void explain_token_packet(void)
{
	
}

/*
** Get Out Data
*/
void get_out_data(void)
{
	Sci.tx_buffer[3] = _DATA0;
	Sci.tx_buffer[4] = (unsigned char)Sci.no;
	Sci.tx_buffer[5] = (unsigned char)(Sci.no >> 8);
  Sci.no++;
	Sci.tx_mode = SCI_TX_CMD;
}

/*
** Run UART Server Task
*/
void RunUartServerTask(void)
{
	switch(uart.step)
	{
		case 0:
		  OpenUART();
		  uart.step++;
			break;
			
		case 1:
			Sci.rx_mode = SCI_RX_CMD;
			Sci.rx_pos = 0;
		  uart.step++;
			break;
		
		case UART_QUEUE_STEP:
			if((uart.mode & fe_uart_end) != 0)
			{
				Sci.rx_mode = fe_uart_idle;
				Sci.tx_mode = fe_uart_idle;
				Sci.tx_step = 0;
				uart.mode = fe_uart_idle;
				uart.step = 0;
				CloseUART();
			}
			else
			{
				uart.step++;
			}
			if(uart.masking & UART_EVENT_UPDATE_FLAG_MSK)
			{
				uart.masking &= ~UART_EVENT_UPDATE_FLAG_MSK;
				if(uart.cb != 0)
				{
					uart.cb(Sci.rx_cmd, Sci.rx_len);
				}
			}
			break;
			
		case 3:
		  if(uart.cmd & OUTPUT_HEAT_DATA_CMD)
			{
				uart.cmd &= ~OUTPUT_HEAT_DATA_CMD;
				get_out_data();
				uart.step = UART_TX_STEP;
				if((uart.masking & UART_DEBUG_FLAG_MSK) == 0)
				{
				  uart.mode |= fe_uart_end;
				}
			}
			else
			{
				uart.step++;
			}
			break;
			
    case 4:
			uart.step = UART_QUEUE_STEP;
			if(Sci.rx_mode & fe_uart_finish)
			{
				Sci.rx_mode &= ~fe_uart_finish;
        explain_token_packet();
			}
			break;
			
		case UART_TX_STEP:
			if(Sci.tx_mode & fe_uart_finish)
			{
				Sci.tx_mode = fe_uart_idle;
				uart.step = UART_QUEUE_STEP;
			}
			break;
	}
}
/* --------------------------------------------------------------------------- */
/*
 * @brief UART主体运行函数
 *
 * @param[in]:无
 *
 * @return:无
 *
 * @details 需要放在主函数main()中
 */
void fe_uart_process_run(void)
{
	if(Sci.rx_mode & fe_uart_exe)
	{
		RunSciReceivingProc();
	}
	
	if(Sci.tx_mode & fe_uart_exe)
	{
		RunSciTransmittingProc();
	}
	
	if(uart.mode & fe_uart_exe)
	{
		RunUartServerTask();
	}
}

/*
 * @brief 串口打开
 *
 * @param[in] mode:
 *    =0:normal mode
 *    =1:debug mode
 *
 * @return:
 *    =0:success
 *    !=0:failure
 *
 * @details
 */
uint32_t fe_uart_open(uint32_t mode)
{
	if(mode != 0)
	{
		uart.masking |= UART_DEBUG_FLAG_MSK;
	}
	
	if(uart.mode == fe_uart_idle)
	{
	  uart.mode = fe_uart_exe;
	  return 0;
	}
	else
	{
		return 1;
	}
}

/*
 * @brief 串口关闭
 *
 * @param[in]:无
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 */
//uint32_t fe_uart_close(void)
//{
//	if(uart.mode != fe_uart_idle)
//	{
//		uart.mode |= fe_uart_end;
//		return 0;
//	}
//	else
//		return 1;
//}

/*
 * @brief 查询UART状态
 *
 * @param [in] l:接收数据长度
 *
 * @return:
 *   =0:串口关闭
 *   =1:串口忙
 *
 * @details 进入DeepSleep前，要确保串口空闲状态
 */
uint32_t fe_get_uart_state(void)
{
	if(uart.mode == fe_uart_idle)
		return 0;
	else
		return 1;
}

/*
 * @brief 串口写数据
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
uint32_t fe_uart_write(unsigned char *data, uint32_t len)
{
	if(uart.cmd == 0)
	{
	  mem_data_copy(&Sci.tx_buffer[6], data, len);
	  Sci.tx_total = len + 6;
		uart.cmd |= OUTPUT_HEAT_DATA_CMD;
		if(uart.mode == fe_uart_idle)
		{
			uart.mode = fe_uart_exe;
		}
	  return 0;
	}
	else 
		return 1;
}

/*
 * @brief 串口读数据
 *
 * @param [in] data 数据缓存首地址
 *
 * @return:
 *   >0:数据长度
 *   =0:失败
 *
 * @details 数据缓冲区长度56
 */
//uint32_t fe_uart_read(unsigned char *data)
//{
//	uint32_t i;
//	if((uart.masking & SCI_RECEIVED_FLAG_MSK) != 0)
//	{
//		uart.masking &= ~SCI_RECEIVED_FLAG_MSK;
//		i = Sci.rx_buffer[2] - 8;
//		mem_data_copy(data, &Sci.tx_buffer[6], i);
//		return i;
//	}
//	else
//		return 0;
//}
/*
 * @brief 串口接收回调函数
 *
 * @param [in] event 回调函数
 *
 * @return:
 *   =0:success
 *   !=0:failure
 *
 * @details
 */
//uint32_t fe_uart_register_event(FE_UART_RX_CALLBACK event)
//{
//	uart.event = event;
//	return 0;
//}
/* --------------------------------------------------------------------------- */
