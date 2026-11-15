#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stdarg.h"
#include "macro_definition.h"
#include "uart_api.h"

#include "cm_uart.h"  //#include <cm_drv_uart.h>

#include "msg_box.h"
#include "flash_api.h"
#include "Network_api.h"
/*------------------------------------------------------------------------------------------------*/
extern SYSTEM_DATA_TypeDef system_data;
extern SYSTEM_TypeDef System;
extern DETECTOR_TypeDef smoke_data;
extern NETWORK_TypeDef network_data;
UART_TypeDef uart;
/*------------------------------------------------------------------------------------------------*/
/*
** Issue Set UART Baudrate
*/
void IssueSetBaudrate(void)
{
  int i;
  unsigned char buffer[8];
  
  buffer[0] = _SYN0;
  buffer[1] = _SYN1;
  buffer[2] = 8;
  buffer[3] = SET_UART_BAUDRATE;
  //9600 = 0x2580;
	buffer[4] = 0x80;
	buffer[5] = 0x25;
	i = CalculateCRC_CCITT(buffer, 6);
	buffer[6] = (unsigned char)(i >> 8);
	buffer[7] = (unsigned char)i;
	uart1_send_data(buffer, 8);

	uart.cmd = SET_UART_BAUDRATE;
	uart.message = 0;	
	uart.pos = 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Issue Set LED Color
*/
void IssueSetLED_Color(uint32_t color)
{
  int i;
  unsigned char buffer[7];
  
  buffer[0] = _SYN0;
  buffer[1] = _SYN1;
  buffer[2] = 7;
  buffer[3] = SET_LED_COLOR;
  buffer[4] = (unsigned char)color;
  i = CalculateCRC_CCITT(buffer, 5);
  buffer[5] = (unsigned char)(i >> 8);
  buffer[6] = (unsigned char)i;
  uart1_send_data(buffer, 7);

  uart.cmd = SET_LED_COLOR; 
  uart.message = 0;
  uart.pos = 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Issue Get Status
*/
void IssueGetStatus(void)
{
  int i;
  unsigned char buffer[6];
  
  buffer[0] = _SYN0;
  buffer[1] = _SYN1;
  buffer[2] = 6;
  buffer[3] = GET_STATE;
  i = CalculateCRC_CCITT(buffer, 4);
  buffer[4] = (unsigned char)(i >> 8);
  buffer[5] = (unsigned char)i;
  uart1_send_data(buffer, 6);
  
  uart.cmd = GET_STATE;
  uart.message = 0;
  uart.pos = 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Issue In Data Packet
*/
void IssueInDataPacket(void)
{
  int i;
  unsigned char buffer[14];
  
  buffer[0] = _SYN0;
  buffer[1] = _SYN1;
  buffer[2] = 7;
  buffer[3] = IN_DATA;
  buffer[4] = (unsigned char)network_data.platform_data;
  //memcpy((buffer + 4), (unsigned char *)&smoke_data, sizeof(DETECTOR_TypeDef));
  i = CalculateCRC_CCITT(buffer, 5);
  buffer[5] = (unsigned char)(i >> 8);
  buffer[6] = (unsigned char)i;
  uart1_send_data(buffer, 7);
  
  uart.cmd = IN_DATA;
  uart.message = 0;
  uart.pos = 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Issue Set T3412
*/
void IssueSetT3412(void)
{
  int i;
  unsigned char buffer[7];
  
  buffer[0] = _SYN0;
  buffer[1] = _SYN1;
  buffer[2] = 7;
  buffer[3] = SET_T3412;
  buffer[4] = (unsigned char)system_data.heartbeat_time;
  
  i = CalculateCRC_CCITT(buffer, 5);
  buffer[5] = (unsigned char)(i >> 8);
  buffer[6] = (unsigned char)i;
  uart1_send_data(buffer, 7);
  
  uart.cmd = SET_T3412;
  uart.message = 0;
  uart.pos = 0;
}
/* --------------------------------------------------------------------------- */
/*
** Issue SOF
*/
void IssueSOF(void)
{
/*
  int i;
  uart.buffer[0] = _SYN0;
  uart.buffer[1] = _SYN1;
  uart.buffer[2] = 6;
  uart.buffer[3] = _SOF;
  i = CalculateCRC_CCITT(uart.buffer, 4);
  uart.buffer[4] = (unsigned char)(i >> 8);
  uart.buffer[5] = (unsigned char)i;
  uart1_send_data(uart.buffer, 6);
*/
  unsigned char buffer = _SOF;
  uart1_send_data(&buffer, 1);
}
/* --------------------------------------------------------------------------- */
/*
** Explain Received Data Packet
*/
void ExplainDataPacket(void)
{
  switch(uart.buffer[3])
  {
  case SET_LED_COLOR:
    System.status |= ACTIVE_FLAG_MSK;
    break;
  case GET_STATE:
	  memcpy((unsigned char *)&smoke_data, (uart.buffer + 4), sizeof(DETECTOR_TypeDef));
	  System.status |= ACTIVE_FLAG_MSK;
	  break;
	case IN_DATA:
	  System.status |= ACTIVE_FLAG_MSK;
	  break;
	case SET_T3412:
	  System.status |= ACTIVE_FLAG_MSK;
	  break;
  }
  
  if(uart.buffer[3] == uart.cmd)
  {
    uart.message = _success;
  }
}
/* --------------------------------------------------------------------------- */
/*
** UART1 Printf String
*/
void uart1_printf_string(const char *str, ...)
{
  int l;
  va_list args;
  unsigned char s[512]; //This needs to be large enough to store the string TODO Change magic number
 	
  if((str == NULL) || (strlen(str) == 0))
  {
    return;
  }
  
  va_start (args, str);
  l = (unsigned int)vsprintf((char*)s, str, args);
  va_end (args);

  cm_uart_write(UART1, s, l, 5000);
}

/*
** UART1 Send Data
*/
void uart1_send_data(unsigned char *p, unsigned int l)
{
  if(p == NULL || l == 0) return;
  cm_uart_write(UART1, p, l, UART_TIME_OUT);
}
/*
** UART1 Callback
*/
void uart1_callback(char *rcv_data, int len)
{
  int l;  

  l = uart.pos + len;

  if(l > UART1_BUFFER_SIZE)
  {
    l = UART1_BUFFER_SIZE - uart.pos;
  }
  else
  {
    l = len;
  }

  memcpy((uart.buffer + uart.pos), rcv_data, l);
  uart.pos = uart.pos + (unsigned int)l;
  
  if(uart.pos > 0)
  {
    if(uart.buffer[0] == _SYN0)
	{
	  if(uart.pos > 1)
	  {
	    if(uart.buffer[1] == _SYN1)
		{
		  if(uart.pos > 2)
		  {
            if(uart.buffer[2] <= UART1_BUFFER_SIZE)
            {
              if(uart.pos >= uart.buffer[2])
			  {
	            if(CalculateCRC_CCITT(uart.buffer, uart.buffer[2]) == 0)
				{
				  ExplainDataPacket();
				  uart.pos = 0;
				}
			  }
			}
			else
			{
			  uart.pos = 0;
		    }
		  }
		}
		else
		{
		  uart.pos = 0;
		}
	  }
    }
	else
	{
	  uart.pos = 0;
	}
  }
}
/*
** Open UART1
*/
int open_uart1(void)
{
  cm_uart_cfg_t cfg = {CM_UART_BYTE_SIZE_8,
                       CM_UART_PARITY_NONE,
                       CM_UART_STOP_BIT_ONE,
                       CM_UART_FLOW_CTRL_NONE,
                       CM_UART_BAUDRATE_9600};
  
  cm_uart_event_t event = {CM_UART_EVENT_TYPE_RX_ARRIVED,
  	                       NULL,
  	                       NULL};
  event.event_entry = (void *)uart1_callback;
  uart.pos = 0;
  
  if(cm_uart_open(UART1, &cfg) == 0)
  {
    return cm_uart_register_event(UART1, &event);
  }
  else
  	return -1;
}
/*
** Close UART1
*/
void close_uart1(void)
{
  cm_uart_close(UART1);
}
/* --------------------------------------------------------------------------- */
/*
** UART0 Printf String
*/
void uart0_printf_string (const char *str, ...)
{
  int l;
  static unsigned char s[512]; //This needs to be large enough to store the string TODO Change magic number
  

  if((str == NULL) || (strlen(str) == 0))
  {
    return;
  }
  
  va_list args;
  va_start(args, str);
  l = (unsigned int)vsnprintf((char *)s, 512, str, args);
  va_end(args);
  
  cm_uart_write(UART0, s, l, 5000);
}
/*
** UART0 Send Data
*/
void uart0_send_data(unsigned char *p, unsigned int l)
{
  if(p == NULL || l == 0) return;
  cm_uart_write(UART0, p, l, UART_TIME_OUT);
}
/*
** UART0 Send Data
*/
void uart0_callback(char *rcv_data, int len)
{
  unsigned char buffer[UART0_RX_BUFFER_SIZE];

  if(len > 0 && len <= UART0_RX_BUFFER_SIZE)
  {
    memcpy(buffer, rcv_data, len);
	cm_uart_write(UART0, buffer, len, UART_TIME_OUT);
  }
}
/*
** Open UART0
*/
int open_uart0(void)
{
  cm_uart_cfg_t cfg = {CM_UART_BYTE_SIZE_8,
                       CM_UART_PARITY_NONE,
                       CM_UART_STOP_BIT_ONE,
                       CM_UART_FLOW_CTRL_NONE,
                       CM_UART_BAUDRATE_9600};
  
  cm_uart_event_t event = {CM_UART_EVENT_TYPE_RX_ARRIVED,
						   NULL,
						   NULL};
  event.event_entry = (void *)uart0_callback;

  if(cm_uart_open(UART0, &cfg) == 0)
  {
    return cm_uart_register_event(UART0, &event);
  }
  else
  	return -1;
}
/*
** Close UART0
*/
void close_uart0(void)
{
  cm_uart_close(UART0);
}
/* --------------------------------------------------------------------------- */

