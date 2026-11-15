#ifndef __MESSAGE_BOX_H
#define __MESSAGE_BOX_H
/*--------------------------------------------------*/
typedef enum {
  POWER_ON = 0,  
  PIN_RESET,  //1    
  SOFT_RESET,  //2    
  UTC_WAKEUP,  //3
  EXTPIN_WAKEUP, //4
  WDT_RESET, //5   
  UNKNOWN_ON, //6   
}SYS_START_STAT;
/*--------------------------------------------------*/
typedef struct
{
  uint32_t psm;
  uint32_t wake;
  uint32_t flag;
  uint32_t status;
  void *handle;
}SYSTEM_TypeDef;
/*--------------------------------------------------*/
typedef struct
{
  void *t;
  //uint32_t message;
  //void *p;
  //uint32_t param;
}TIMER_TypeDef;
/*--------------------------------------------------*/
typedef struct
{
  unsigned char packet_id;
  unsigned char type;
  unsigned char status;
  unsigned char unit;
  unsigned char voltage;
  unsigned char temperature;
  unsigned char density;
  unsigned char reserved;
}DETECTOR_TypeDef;
/*--------------------------------------------------*/
void OpenCPU_Message_Box_Task_Main(void* arg);
/* --------------------------------------------------------------------------- */
#endif

