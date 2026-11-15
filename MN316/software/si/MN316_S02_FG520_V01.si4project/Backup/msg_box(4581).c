/*
**
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "macro_definition.h"

#include "cm_os.h"  //#include "cmsis_def.h" //#include "cmsis_os2.h"
#include "cm_sys.h"
#include "cm_pm.h"
#include "cm_sim.h"
#include "cm_modem.h"
#include "xy_sys.h"
#include "xy_ps.h"
#include "custom_main.h"

#include "msg_box.h"
#include "flash_api.h"
#include "uart_api.h"
#include "network_api.h"
/*------------------------------------------------------------------------------------------------*/
extern UART_TypeDef uart;
extern NETWORK_TypeDef network_data;
extern SYSTEM_DATA_TypeDef system_data;
SYSTEM_TypeDef System;
DETECTOR_TypeDef smoke_data;
TIMER_TypeDef msg_time;
/*------------------------------------------------------------------------------------------------*/
/**
 *  \brief 获取默认启动方式
 *  
 *  \return 0:默认以AT启动，需手动切换至OC; \n
 *        非0:默认以OC模式启动，不支持切换
 *  
 *  \details 此接口由用户实现。不实现此接口时，默认以AT启动，需手动切换至OC模式
*/
int cm_sys_get_run_mode(void)
{
  return 1;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Save Local Time
*/
void SaveLocalTime(void)
{
  if(smoke_data.packet_id == RESET_PACKET_ID || smoke_data.packet_id == HEARTBEAT_PACKET_ID)
  {
    if((System.flag & LOCAL_TIME_UPDATE_SUCCESS_FLAG_MSK) != 0)
    {
      memcpy((unsigned char *)&system_data.year, (unsigned char *)&network_data.year, 6);
	  //system_data.time_stamp = network_data.time_stamp;
      system_data.masking |= TIME_UPDATE_SUCCESS_FLAG_MSK;
    }
    else
    {
      system_data.masking &= ~TIME_UPDATE_SUCCESS_FLAG_MSK;
    }
  }
  else
  {
    system_data.masking &= ~TIME_UPDATE_SUCCESS_FLAG_MSK;
  }
}
/*------------------------------------------------------------------------------------------------*/
/*
** Waking Interrupt Callback
*/
/*
void cm_wakeup_callback(void)
{
  System.wake = WAKING_FLAG;
}
*/
/*------------------------------------------------------------------------------------------------*/
/*
** Timer Callback
*/
void vTimerCallback(void *arg)
{
  int i;

  osTimerDelete(msg_time.t);

  osThreadTerminate(System.handle);

  opencpu_printf("\r\ntimer overflow!"); 
  
  if((system_data.masking & SIM_INITIALIZE_FLAG_MSK) == 0)
  {
    opencpu_printf("\r\nSIM card error!");
  }
  else
  {
    opencpu_printf("\r\nAntenna connection error!");
  }
  
  opencpu_printf("\r\npower off...");
  osDelay(100);
  
  if((System.flag & POWER_ON_FLAG_MSK) != 0)
  {
    i = 10;
    do{
      IssueSetLED_Color(0);
	  osDelay(200);
      if(uart.message == _success)
	  	break;
    }while(--i);
	
	if(i == 0)
	  opencpu_printf("\r\nSet Red LED failed!");
	else
      opencpu_printf("\r\n%d\r\nSet Red LED finished!",i);
  }

  osDelay(1000);
  
  xy_fast_power_off(0);
}
/*------------------------------------------------------------------------------------------------*/
/*
** OpenCPU Message Box Task Main
*/
void OpenCPU_Message_Box_Task_Main(void* arg)
{
  int i,j,k;

  CM_UNUSED(arg);
  
  cm_pm_work_lock();
  cm_pm_set_mode(0);

  ReadSystemData();

  msg_time.t = osTimerNew(vTimerCallback, osTimerOnce, NULL, NULL);

  System.flag = System.psm = 0;
  network_data.onenet_masking = 0;
  network_data.aep_masking = 0;
  network_data.platform_cmd_id = 0;

  System.wake = cm_pm_get_power_on_reason();
  if(System.wake == CM_PM_SOFT_RESET)
  {
    if((system_data.masking & SYSTEM_WAKEUP_INTERRUPT_FLAG_MSK) != 0)
    {
      system_data.masking &= ~SYSTEM_WAKEUP_INTERRUPT_FLAG_MSK;
      System.flag |= INTERRUPT_WAKEUP_IN_FLAG_MSK;
    }
    else
    {
      System.flag |= POWER_ON_FLAG_MSK;
      system_data.masking &= ~(SYSTEM_REBOOT_FLAG_MSK + SIM_INITIALIZE_FLAG_MSK + TIME_UPDATE_SUCCESS_FLAG_MSK + CONNECT_PLATFORM_SUCCESS_FLAG_MSK);
      system_data.masking |= FIRST_T3412_UPDATE_FLAG_MSK;
    }
  }
  else if(System.wake == CM_PM_UTC_WAKEUP)
  {
    System.flag |= PSM_WAKEUP_IN_FLAG_MSK;
  }
  else if(System.wake == CM_PM_EXTPIN_WAKEUP)
  {
    System.flag |= INTERRUPT_WAKEUP_IN_FLAG_MSK;
  }
  else
  {
    System.flag |= POWER_ON_FLAG_MSK;
    system_data.masking &= ~(SYSTEM_REBOOT_FLAG_MSK + SIM_INITIALIZE_FLAG_MSK + TIME_UPDATE_SUCCESS_FLAG_MSK + CONNECT_PLATFORM_SUCCESS_FLAG_MSK);
    system_data.masking |= FIRST_T3412_UPDATE_FLAG_MSK;
  }
/*----------------------------------------------------
** UART Initialize
*/
  close_uart0();
  open_uart0();
  close_uart1();
  open_uart1();
  
/*----------------------------------------------------
** reboot
*/
  if((system_data.masking & SYSTEM_REBOOT_FLAG_MSK) != 0)
  {
    system_data.masking &= ~SYSTEM_REBOOT_FLAG_MSK;
    if((System.flag & INTERRUPT_WAKEUP_IN_FLAG_MSK) != 0)
    {
      system_data.masking |= SYSTEM_WAKEUP_INTERRUPT_FLAG_MSK;
    }
	
    SaveSystemData();
    osTimerDelete(msg_time.t);
	
    opencpu_printf("\r\nreboot...\r\n");
	osDelay(1000);
	
	//cm_sys_reboot();
	xy_reboot();
	
    osThreadExit();
    return;
  }
#ifdef _KINGDUN_OUTPUT_MODE
  opencpu_printf("\r\nVer:H-01-0094-V1\r\n");
#endif  
  //opencpu_printf("\nThread:0x%x,Time:0x%x",System.handle,msg_time.t);
  opencpu_printf("\r\npsm:%d, wakeup:%d, flag:0x%02x",System.psm,System.wake,System.flag);

/*----------------------------------------------------
** Get Detector Status
*/
  if((System.flag & INTERRUPT_WAKEUP_IN_FLAG_MSK) != 0)
  {
    i = 10;
	do{
	  IssueGetStatus();
	  osDelay(200);
	  if(uart.message == _success)
	  	break;
	}while(--i);

	if(i == 0)
	{
	  smoke_data.packet_id = 0;
	}
	else
	{
	  opencpu_printf("\r\nPacket_ID:0x%x", smoke_data.packet_id);
	  opencpu_printf("\r\nType:0x%x", smoke_data.type);
	  opencpu_printf("\r\nState:0x%x", smoke_data.status);
	  opencpu_printf("\r\nUnit:0x%x", smoke_data.unit);
	  opencpu_printf("\r\nBattery voltage:%d", smoke_data.voltage);
	  opencpu_printf("\r\nTemperature:%d", smoke_data.temperature);
	  opencpu_printf("\r\nSmoke density:%d", smoke_data.density);
	  opencpu_printf("\r\nres:0x%x", smoke_data.reserved);
	  opencpu_printf("\r\n%d", 10-i);
	}
  }
  else
  {
    smoke_data.packet_id = 0;
  }
  
/*----------------------------------------------------
** SIM Card Initialize
** time:10s
*/
  if((System.flag & POWER_ON_FLAG_MSK) != 0 ||
	 (system_data.masking & SIM_INITIALIZE_FLAG_MSK) == 0)
  {
    memset(system_data.IMEI, 0, IMEI_SIZE);
	memset(system_data.ICCID, 0, ICCID_SIZE);
	memset(system_data.IMSI, 0, IMSI_SIZE);
	
	cm_sys_get_imei(system_data.IMEI);  //cm_ril_get_imei(system_data.IMEI);
  
	osTimerStart(msg_time.t, 10000);
	while(cm_sim_get_iccid(system_data.ICCID) != 0)  //while(cm_ril_get_iccid(system_data.ICCID) != 0)
	{
	  osDelay(1000);
	}
	while(cm_sim_get_imsi(system_data.IMSI) != 0)  //while(cm_ril_get_imsi(system_data.IMSI) != 0)
	{
	  osDelay(1000);
	}
	osTimerStop(msg_time.t);
  
	system_data.service_provider = Get_Service_Provider();
	
  	system_data.masking |= SIM_INITIALIZE_FLAG_MSK; 	
  }
  opencpu_printf("\r\nIMEI:%s\r\n", system_data.IMEI);
  opencpu_printf("ICCID:%s\r\n", system_data.ICCID);
#ifdef _KINGDUN_OUTPUT_MODE
  opencpu_printf("SIMSN:%s\r\n", system_data.ICCID);
#endif
  opencpu_printf("IMSI:%s\r\n", system_data.IMSI);

/*----------------------------------------------------
** NETWORK registration
** time:60s/30s
*/
  if((System.flag & POWER_ON_FLAG_MSK) != 0)
  {
    osTimerStart(msg_time.t, 60000);
  }
  else
  {
    osTimerStart(msg_time.t, 30000);
  }
  i = 0;
  while(1)
  {
	if(cm_modem_get_pdp_state(0) > 0)
	{
	  break;
	}
    osDelay(1000);
	i++;
  };
  osTimerStop(msg_time.t);
  //System.flag |= NETWORK_REGISTER_SUCCESS_FLAG_MSK;
  opencpu_printf("\r\n%d\r\nNetwork register success!", i);

/*----------------------------------------------------
** Get RSSI/LQI
*/
  i = 30;
  do{
    cm_modem_get_csq(&network_data.rssi, &network_data.lqi);
    if(network_data.rssi != 99)
	  break;
    else
	  osDelay(1000);
  }while(--i);

  if(i == 0)
  {
    network_data.rssi =
	network_data.lqi = 0;
	opencpu_printf("\r\nGet RSSI failed!");
  }
  else
  {
    opencpu_printf("\r\n%d\r\nRSSI:%d,LQI:%d", (30-i), network_data.rssi, network_data.lqi);
  }

/*----------------------------------------------------*/
#ifdef _KINGDUN_OUTPUT_MODE
  opencpu_printf("\r\nCSQ:%d\r\n", network_data.rssi);
#endif
/*----------------------------------------------------
** Get EPS network status
*/
  if(opencpu_get_cereg() == 0)
  {
    CheckPSM();
    opencpu_printf("\r\nT3324:0x%02x,T3412:0x%02x", network_data.active_time, network_data.periodic_tau);
  }
  else
  {
    network_data.cell_id =
    network_data.active_time =
    network_data.periodic_tau = 0;
    opencpu_printf("\r\nGet EPS status failed!");
  }

/*----------------------------------------------------
** Get eDRX parameter
*/
  if(opencpu_get_edrx() == 0)
  {
    //System.flag |= EDRX_UPDATE_SUCCESS_FLAG_MSK;
    opencpu_printf("\r\neDRX act_type:%d", network_data.act_type);
  }
  else
  {
    opencpu_printf("\r\nGet eDRX failed!");
  }
 
/*----------------------------------------------------
** Get Local Time
*/
  if(opencpu_get_time() == 0)
  {
    System.flag |= LOCAL_TIME_UPDATE_SUCCESS_FLAG_MSK;
	opencpu_printf("\r\nlocal time:%d-%d-%d %d:%d", network_data.year, network_data.month, network_data.day, network_data.hour, network_data.minute);
    //opencpu_printf("\ntime stamp:%d",network_data.time_stamp);
  }
  else
  {
    opencpu_printf("\r\nGet local time failed!");
  }
/*----------------------------------------------------
** Set LED color
*/
  if((System.flag & POWER_ON_FLAG_MSK) != 0)
  {	 
    i = 10;
	do{
	  IssueSetLED_Color(1);
	  osDelay(200);
	  if(uart.message == _success)
	  	break;
	}while(--i);
  
	if(i == 0)
	{
	  opencpu_printf("\r\nSet Green LED failed!");
	}
	else
	{
	  opencpu_printf("\r\n%d\r\nSet Green LED finished!", 10-i);
	}
  }

/*----------------------------------------------------
** Connect Platform
*/
  if(system_data.service_provider == CMCC)
  {
    ConnectOneNET();
  }
  else
  {
  	if(system_data.service_provider == CTCC)
    {
	  ConnectCTWing();
    }
  }
  osDelay(1000);

/*----------------------------------------------------
** Connect Server
*/
  //if((System.flag & POWER_ON_FLAG_MSK) == 0)
  //{
  //ConnectServerWithUDP(1);
  //}
  i = xy_send_rai();
  opencpu_printf("\r\nset rai return:%d", i);

/*----------------------------------------------------
** Set Detector T3412
*/
  if(ModifyHeartbeatTime() == 0)
  {
    i = 10;
    do{
	  IssueSetT3412();
	  osDelay(200);
	  if(uart.message == _success)
	  	break;
    }while(--i);

    if(i == 0)
    {
	  opencpu_printf("\r\nSet T3412 failed!");
    }
    else
    {
	  opencpu_printf("\r\n%d\r\nSet T3412(0x%x) finished!", (10-i), system_data.heartbeat_time);
    }
  }
  system_data.event_id = network_data.event_id;

/*----------------------------------------------------*/
  SaveLocalTime();
  
  SaveSystemData();
  opencpu_printf("\r\nWrite flash finished!\r\n");
  
  osTimerDelete(msg_time.t);

  cm_pm_set_mode(1);
  cm_pm_work_unlock();
/*----------------------------------------------------*/
  i = 0;
  while(1)
  {
	IssueSOF();
	opencpu_printf("%d;", ++i);
	osDelay(1000);
  }
  osThreadExit();
}
/*----------------------------------------------------------------------------------------------------*/

