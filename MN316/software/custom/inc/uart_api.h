#ifndef __UART_API_H
#define __UART_API_H
/* --------------------------------------------------------------------------- */
#define _SYN0 0x55
#define _SYN1 0xAA
/* --------------------------------------------------------------------------- */
//Frame Control
#define _SETUP 0xB4
#define _OUT 0x87
#define _IN 0x96
#define _DATA0 0xC3
#define _DATA1 0xD2
#define _SOF 0xA5
#define _ACK 0x4B
#define _NAK 0x5A
/* --------------------------------------------------------------------------- */
#define SET_UART_BAUDRATE 0x51
#define SET_LED_COLOR 0x52
#define GET_STATE 0x53
#define IN_DATA 0x54
#define SET_T3412 0x55
/* --------------------------------------------------------------------------- */
//#define STATE_BYTE_LENGHT 5
#define UART0 CM_UART_DEV_1  //UART_BUS_1
#define UART0_BUFFER_SIZE  128
#define UART0_TX_BUFFER_SIZE  128
#define UART0_RX_BUFFER_SIZE  128

#define UART1 CM_UART_DEV_2  //UART_BUS_2
#define UART1_BUFFER_SIZE  128
#define UART1_TX_BUFFER_SIZE  128
#define UART1_RX_BUFFER_SIZE  128
/* --------------------------------------------------------------------------- */
#define opencpu_printf uart0_printf_string
#define opencpu_printf_data uart0_send_data
/* --------------------------------------------------------------------------- */
#define UART_TIME_OUT 500
/* --------------------------------------------------------------------------- */
typedef struct
{
  unsigned char buffer[UART1_BUFFER_SIZE];
  unsigned int pos;
  unsigned int message;
  
  unsigned char cmd;
  //unsigned char rsp_cmd;
}UART_TypeDef;
/* --------------------------------------------------------------------------- */
int open_uart0(void);
void close_uart0(void);
void uart0_callback(char *rcv_data, int len);
void uart0_send_data(unsigned char *p, unsigned int l);
void uart0_printf_string(const char *str, ...);
/* --------------------------------------------------------------------------- */
int open_uart1(void);
void close_uart1(void);
void uart1_send_data(unsigned char *p, unsigned int l);
/* --------------------------------------------------------------------------- */
void IssueSetBaudrate(void);
void IssueSetLED_Color(uint32_t color);
void IssueGetStatus(void);
void IssueInDataPacket(void);
void IssueSetT3412(void);
void IssueSOF(void);
//void ExplainDataPacket(void);
/* --------------------------------------------------------------------------- */
#endif

