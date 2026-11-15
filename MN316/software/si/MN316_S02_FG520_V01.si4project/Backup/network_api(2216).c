#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "macro_definition.h"
#include "network_api.h"

#include "cm_os.h"
#include "cm_rtc.h"
#include "cm_modem.h"
#include "sockets.h"
#include "cm_onenet.h"
#include "cm_ctwing.h"

#include "msg_box.h"
#include "flash_api.h"
#include "uart_api.h"

/*----------------------------------------------------------------------------------------------------*/
extern SYSTEM_TypeDef System;
extern SYSTEM_DATA_TypeDef system_data;
extern DETECTOR_TypeDef smoke_data;
extern UART_TypeDef uart;
NETWORK_TypeDef network_data;
/*----------------------------------------------------------------------------------------------------*/
/*
** Get heartbeat time
*/
int GetHeartbeatTime(unsigned int tau)
{
  int i,j;
  i = (tau >> 5) & 0x7;
  j = tau & 0x1F;
  switch(i)
  {
  case 0:
    return (j / 6);
    //break;
  case 1:
    return j;
    //break;
  case 2:
    return (j * 10);
    //break;
  case 3:
    return (j / 1800);
    //break;
  case 4:
    return (j / 120);
    //break;
  case 5:
    return (j / 60);
    //break;
  case 6:
    return (j * 320);
    //break;
  case 7:
  default:
    return 0;
    //break;
  }
}
/*
** Check PSM parameter
*/
void CheckPSM(void)
{
  int i,j;
  i = GetHeartbeatTime(network_data.periodic_tau);
  j = GetHeartbeatTime(system_data.obj_heartbeat_time);
  if(i < j)
  {
    System.status |= PSM_ERROR_FLAG_MSK;
  }
  else
  {
    System.status &= ~PSM_ERROR_FLAG_MSK;
  }
}
/*
** modify heartbeat time
*/
int ModifyHeartbeatTime(void)
{
  int i,t;

  if((System.flag & FIRST_SYSTEM_POWER_ON_FLAG_MSK) != 0)
  {
    return -1;
  }

  if((System.flag & HEARTBEAT_TIME_UPDATE_FLAG_MSK) != 0)
  {
    return 0;
  }

  if((system_data.masking & FIRST_T3412_UPDATE_FLAG_MSK) != 0)
  {
    if(smoke_data.packet_id == RESET_PACKET_ID || smoke_data.packet_id == HEARTBEAT_PACKET_ID)
    {
      system_data.masking &= ~FIRST_T3412_UPDATE_FLAG_MSK;
      system_data.heartbeat_time = system_data.obj_heartbeat_time;
      return 0;
    }
  }
  
  //if(system_data.packet_id == HEARTBEAT_PACKET_ID && smoke_data.packet_id == HEARTBEAT_PACKET_ID)
  if(system_data.event_id == HEARTBEAT_EVENT_ID && network_data.event_id == HEARTBEAT_EVENT_ID)
  {

    if((System.flag & LOCAL_TIME_UPDATE_SUCCESS_FLAG_MSK) == 0 ||
       (system_data.masking & TIME_UPDATE_SUCCESS_FLAG_MSK) == 0)
    {
      return -1;
    }

    t = GetHeartbeatTime(system_data.obj_heartbeat_time);
    
    i = 0;
    if(system_data.year == network_data.year && system_data.month == network_data.month)
    {
      i = (network_data.day - system_data.day) * 24 + network_data.hour - system_data.hour;
      i = i - t;
    }
    
    if(i == 0)
    {
      return -1;
    }
    else
    {
      t = t - i;
      if(t > 31)
      {
        t = 31;
      }
      if(t < 10)
      {
        t = 10;
      }
      t = t + (MULTIPLE_1_HOUR << 5);
      system_data.heartbeat_time = (uint32_t)t;

      return 0;
    }
  }

  return -1;
}
/*----------------------------------------------------------------------------------------------------*/
int CalculateRSSI(int rssi)
{
  return (rssi * 2 - 113);
}
/*----------------------------------------------------------------------------------------------------
void get_network_csq(void)
{
  int rssi,lqi;
  opencpu_csq(&rssi, &lqi);
  rssi = CalculateRSSI(rssi);
  if(network_data.RSSI == 0)
  {
    network_data.RSSI = rssi;
  }
  else
  {
    network_data.RSSI += rssi;
    network_data.RSSI /= 2;
  }
  network_data.LQI = lqi;
}*/
/*----------------------------------------------------------------------------------------------------*/
/*
**
*/
int CharToInteger(char *s, int *p)
{
  int n = 0;
  int i = 0;
  
  while(s[i] >= '0' && s[i] <= '9')  
  {  
    n = 10 * n + (s[i] - '0');
    i++;
  } 
  *p = i;
  return n;
}
/*
**
*/
int CharHexToInteger(char *s)
{
  int n = 0;
  int i = 0;

  while(1)
  {
    if(s[i] >= '0' && s[i] <= '9')
    {
      n = n * 16 + (s[i] - '0');
    }
    else if(s[i] >= 'a' && s[i] <= 'f')
    {
      n = n * 16 + (s[i] - 'a') + 10;
    }
    else if(s[i] >= 'A' && s[i] <= 'F')
    {
      n = n * 16 + (s[i] - 'A') + 10;
    }
    else
    {
      break;
    }
    i++;
  }
  
  return n;
}
/*
** opencpu get EPS network status
*/
int opencpu_get_cereg(void)
{
  int i;
  cm_cereg_state_t eps;  //cm_cereg_stats_t eps;

  i = 30;
  do{
  	eps.state = 0;
  	cm_modem_get_cereg_state(&eps);  //cm_ril_get_cereg(&eps);
  	if(eps.state == 1)
	  break;
	else
	  osDelay(1000);
  }while(--i);

  if(i == 0)
  	return -1;

  network_data.cell_id = eps.ci;
  network_data.active_time = eps.active_time;
  network_data.periodic_tau = eps.periodic_tau;
  
  return 0;
}
/*
** opencpu get cell info
*/
int opencpu_get_cell_info(void)
{
  int i;
  cm_cell_info_t cell;

  i = 3;
  do{
  	if(cm_modem_get_cell_info(&cell, 3) > 0)  //if(cm_ril_get_cell_info(&cell) == 0)
      break;
	else
      osDelay(1000);
  }while(--i);

  if(i == 0)
  	return -1;
  if(cell.primary_cell == 0)
  	return -1;

  network_data.sc_pci = cell.pci;
  
  network_data.sc_rsrp = cell.rsrp;
  if(cell.rsrp > 0x8000)
    network_data.sc_rsrp -= 65536;

  network_data.sc_rsrq = cell.rsrq;
  if(cell.rsrq > 0x8000)
  	network_data.sc_rsrq -= 65536;
    
  network_data.sc_rssi = cell.rssi;
  if(cell.rssi > 0x8000)
  	network_data.sc_rssi -= 65536;
  
  network_data.sc_snr = cell.snr;

  return 0;
}
/*
** opencpu get PSM status
*/
int opencpu_get_psm(void)
{
  int i;
  //cm_cpsms_info_t psm;
  cm_psm_cfg_t psm;
  
  i = 3;
  do{
  	if(cm_modem_get_psm_cfg(&psm) == 0)  //if(cm_ril_get_cpsms(&psm) == 0)
      break;
	else
      osDelay(1000);
  }while(--i);

  if(i == 0)
  	return -1;
  if(psm.mode != 1)
  	return -1;

  network_data.active_time = psm.active_time;
  network_data.periodic_tau = psm.periodic_tau;
  
  return 0;
}
/*
** opencpu get EDRX status
*/
int opencpu_get_edrx(void)
{
  int i;
  //char type, edrx_value, paging_time_window;
  cm_edrx_cfg_get_t edrx;
  
  i = 3;
  do{
  	if(cm_modem_get_edrx_cfg(&edrx) == 0)  //if(cm_ril_get_edrxs(&type, &edrx_value, &paging_time_window) == 0)
      break;
	else
      osDelay(1000);
  }while(--i);

  if(i == 0)
  	return -1;

  network_data.act_type = edrx.act_type;
  return 0;
}
/*
** opencpu get time
*/
int opencpu_get_time(void)
{
  int i;
  struct tm t = {0};
  //struct xy_wall_clock wc;
  
  //cm_sys_set_time_by_ntp();
  //xy_rtc_get_time(&wc);
  i = 3;
  do{
  	if(cm_rtc_get_time_tm(&t) == 0)  //if(cm_sys_get_time_tm(&t) == 0)
	  break;
	else
	  osDelay(1000);
  }while(--i);

  if(i == 0)
  	return -1;
  
  network_data.year = t.tm_year;
  network_data.month = t.tm_mon;
  network_data.day = t.tm_mday;
  network_data.hour = t.tm_hour;
  network_data.minute = t.tm_min;
  
  return 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
** Generate Detector Hex Data Packet
*/
int GenerateDetectorHexDataPacket(unsigned char *p)
{
  int i;
  
  memcpy(p, (unsigned char *)&system_data.no, 19);
  memcpy((p + 19), (unsigned char *)&system_data.IMSI, 15);
  p[34] = (char)network_data.rssi;
  i = OUT_PACKET_ID;
  i = ((i << 5) & 0x000000E0) | (System.status & 0x0000001F);
  p[35] = (unsigned char)i;
  p[36] = 8;
  memcpy((p + 37), (unsigned char *)&smoke_data, 8);

  return 45;
}
/*------------------------------------------------------------------------------------------------*/
int ExplainPacketFromServer(unsigned char *p, uint32_t l)
{
  if(l == 45)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/*------------------------------------------------------------------------------------------------*/
/*
** UDP TX task
*/
void opencpu_udp_tx_task(void *arg)
{
  int i,l;
  unsigned char *p;
  unsigned char buffer[128];

  buffer[0] = (unsigned char)system_data.no;
  l = 1;
  //l = GenerateDetectorHexDataPacket(buffer);
  p = buffer;
  
  while(l > 0)
  {
    i = send(network_data.socket, p, l, 0);
    p = p + i;
	l = l - i;
  }
  
  network_data.message = _success;
  osThreadExit();
}
/*------------------------------------------------------------------------------------------------*/
/*
** UDP RX task
*/
void opencpu_udp_rx_task(void *arg)
{
  int l;
  unsigned char buffer[128];
  
  struct sockaddr_in from;
  socklen_t fromlen = sizeof(struct sockaddr_in);

  l = recvfrom(network_data.socket, buffer, 45, MSG_TRUNC, (struct sockaddr*)&from, &fromlen);
  //l = recvfrom(network_data.socket, buffer, 45, MSG_TRUNC | MSG_DONTWAIT, (struct sockaddr*)&from, &fromlen);

  if(l > 0)
  {
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nRX:");
    opencpu_printf_data(buffer, l);
#endif
    //ExplainPacketFromServer(buffer, l);
  }
  
  network_data.message = _success;
  osThreadExit();
}
/*------------------------------------------------------------------------------------------------*/
/*
** Connect Server with UDP
*/
int ConnectServerWithUDP(int mode)
{
  int i;
  TaskHandle_t Tx_handle;
  osThreadAttr_t tx_attr;
   
  struct in_addr remote_addr;
  uint16_t remote_port;
  
  struct sockaddr_in host_address;
 
  if(system_data.service_provider == CMCC)
  {
    inet_aton("183.230.40.39", &remote_addr);
    remote_port = 80;
  }
  else
  {
    inet_aton("221.229.214.202", &remote_addr);
    remote_port = 80;
  }

  network_data.socket = socket(AF_INET, SOCK_DGRAM, 0);
  if(network_data.socket == -1)
  {
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nGreate udp sorket failed!");
#endif
	return -1;
  }
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  else
  {
    opencpu_printf("\r\nGreate udp sorket success!");
  }
#endif
  
  memset(&host_address, 0, sizeof(host_address));
  host_address.sin_family = AF_INET;
  host_address.sin_addr.s_addr = remote_addr.s_addr;  
  host_address.sin_port = htons(remote_port); 
   
  if(connect(network_data.socket, (struct sockaddr *)&host_address, sizeof(struct sockaddr)) != 0)
  {
    close(network_data.socket);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nUDP conneting failed!");
#endif
    return -1;
  }
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  else
  {
    opencpu_printf("\r\nUDP connecting success!");
  }
#endif
  network_data.message = 0;

  Tx_handle = NULL;
  tx_attr.name = "udp_tx_task";
  tx_attr.priority = osPriorityNormal;
  tx_attr.stack_size = 1024;
  Tx_handle = osThreadNew(opencpu_udp_tx_task, NULL, (const osThreadAttr_t*)&tx_attr);
  if(Tx_handle == NULL)
  {
    close(network_data.socket);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nGreate udp tx task failed!");
#endif
    return -1;
  }
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  else
  {
    opencpu_printf("\r\nGreate udp tx task success!");
  }
#endif

  i = 100;
  do{
    osDelay(100);
	if(network_data.message != 0)
		break;
  }while(--i);

  if(network_data.message != _success)
  {
	osThreadTerminate(Tx_handle);
    close(network_data.socket);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nUDP send data failed!");
#endif
    return -1;
  }
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  else
  {
    opencpu_printf("\r\n%d\r\nUDP send data success!",(100-i));
  }
#endif

  close(network_data.socket);
  return 0;
}
/*------------------------------------------------------------------------------------------------*/
/*
**
*/
int SignedIntegerPrintf(char *p, uint32_t n)
{
  char h,s[16];
  int i,l;

  l = 0;
  if((n & 0x80000000) != 0)
  {
    n = (~n) + 1;
    p[0] = '-';
    l++;
  }

  i = 0;
  do{
    h = (char)(n % 10);
    h = h + '0';
    s[i] = h;
    i++;
    n = n / 10;
  }while(n > 0);

  do{
    i--;
    p[l] = s[i];
    l++;
  }while(i > 0);
  
  return l;
}
/*
**
*/
void IntegerPrintf(char *p, uint32_t n, uint32_t l)
{
  char h;
  do{
    h = (char)(n % 10);
    h = h + '0';
    p[l - 1] = h;
    
    n = n / 10;
    l--;
  }while(l > 0);
}
/*
** Integer to Char
*/
void IntegerPrintf_Hex(char *p, uint32_t n, uint32_t l)
{
  char h;
  do{
    h = (char)(n & 0x0000000F);
    if(h > 9)
    {
      h = (h - 10) + 'A';
    }
    else
    {
      h = h + '0';
    }
    p[l - 1] = h;
    
    n = n >> 4;
    l--;
  }while(l > 0);
}
/*
** get detector event id
*/
int GetDetectorEventID(void)
{
  if((System.flag & FIRST_SYSTEM_POWER_ON_FLAG_MSK) != 0)
    return REGISTER_OCCUR_EVENT_ID;
    
  if(smoke_data.packet_id == EVENT_PACKET_ID)
  {
    if((smoke_data.status & DETECTOR_ALERT_FLAG_MSK) != 0)
    {
      system_data.status |= ALARM_EVENT_FLAG_MSK;
      return ALARM_OCCUR_EVENT_ID;
    }
    if((smoke_data.status & DETECTOR_TEST_FLAG_MSK) != 0)
    {
      system_data.status |= TEST_EVENT_FLAG_MSK;
      return TEST_OCCUR_EVENT_ID;
    }
    if((smoke_data.status & DETECTOR_REMOVE_FLAG_MSK) != 0)
    {
      system_data.status |= REMOVE_EVENT_FLAG_MSK;
      return REMOVE_OCCUR_EVENT_ID;
    }
    if((smoke_data.status & DETECTOR_LOW_BATTERY_FLAG_MSK) != 0)
    {
      system_data.status |= BATTERY_LOW_FAULT_EVENT_FLAG_MSK;
      return BATTERY_LOW_OCCUR_EVENT_ID;
    }
    if((smoke_data.status & DETECTOR_SENSOR_TROUBLE_FLAG_MSK) != 0)
    {
      system_data.status |= SENSOR_TROUBLE_FAULT_EVENT_FLAG_MSK;
      return SENSOR_TROUBLE_OCCUR_EVENT_ID;
    }
  }

  if(smoke_data.packet_id == RESET_PACKET_ID || smoke_data.packet_id == HEARTBEAT_PACKET_ID)
  {
    if((system_data.status & ALARM_EVENT_FLAG_MSK) != 0)
    {
      if((smoke_data.status & DETECTOR_ALERT_FLAG_MSK) == 0)
      {
        system_data.status &= ~ALARM_EVENT_FLAG_MSK;
        return ALARM_RESET_EVENT_ID;
      }
    }
    if((system_data.status & TEST_EVENT_FLAG_MSK) != 0)
    {
      if((smoke_data.status & DETECTOR_TEST_FLAG_MSK) == 0)
      {
        system_data.status &= ~TEST_EVENT_FLAG_MSK;
        return TEST_RESET_EVENT_ID;
      }
    }
    if((system_data.status & REMOVE_EVENT_FLAG_MSK) != 0)
    {
      if((smoke_data.status & DETECTOR_REMOVE_FLAG_MSK) == 0)
      {
        system_data.status &= ~REMOVE_EVENT_FLAG_MSK;
        return REMOVE_RESET_EVENT_ID;
      }
    }
    if((system_data.status & BATTERY_LOW_FAULT_EVENT_FLAG_MSK) != 0)
    {
      if((smoke_data.status & DETECTOR_LOW_BATTERY_FLAG_MSK) == 0)
      {
        system_data.status &= ~BATTERY_LOW_FAULT_EVENT_FLAG_MSK;
        return FAULT_RESET_EVENT_ID;
      }
    }
    if((system_data.status & SENSOR_TROUBLE_FAULT_EVENT_FLAG_MSK) != 0)
    {
      if((smoke_data.status & DETECTOR_SENSOR_TROUBLE_FLAG_MSK) == 0)
      {
        system_data.status &= ~SENSOR_TROUBLE_FAULT_EVENT_FLAG_MSK;
        return FAULT_RESET_EVENT_ID;
      }
    }
    if(smoke_data.packet_id == HEARTBEAT_PACKET_ID)
    {
      return HEARTBEAT_EVENT_ID;
    }
  }
  
  return -1;
}
/*
** get uplink detector data
*/
int GetUplinkDetectorData(char *p, uint32_t event_id)
{
  IntegerPrintf_Hex(p, PROTOCOL_VERSION, 2);
  IntegerPrintf_Hex((p + 2), DEVICE_CLASS, 2);
  IntegerPrintf_Hex((p + 4), DEVICE_TYPE, 2);
  IntegerPrintf_Hex((p + 6), DEVICE_MODEL, 2);

  switch(event_id)
  {
  case HEARTBEAT_EVENT_ID:
    IntegerPrintf_Hex((p + 8), HEART_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), smoke_data.status, 2);
    break;
  case ALARM_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), ALARM_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), OCCUR_ID, 2);
    break;
  case ALARM_RESET_EVENT_ID:
    IntegerPrintf_Hex((p + 8), ALARM_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), RESET_ID, 2);
    break;
  case TEST_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), TEST_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), OCCUR_ID, 2);
    break;
  case TEST_RESET_EVENT_ID:
    IntegerPrintf_Hex((p + 8), TEST_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), RESET_ID, 2);
    break;
  case REMOVE_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), REMOVE_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), OCCUR_ID, 2);
    break;
  case REMOVE_RESET_EVENT_ID:
    IntegerPrintf_Hex((p + 8), REMOVE_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), RESET_ID, 2);
    break;
  case BATTERY_LOW_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), FAULT_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), BATTERY_LOW_ID, 2);
    break;
  case SENSOR_TROUBLE_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), FAULT_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), SENSOR_TROUBLE_ID, 2);
    break;
  case SENSOR_DUST_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), FAULT_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), SENSOR_DUST_ID, 2);
    break;
  case EEPROM_TROUBLE_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), FAULT_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), EEPROM_TROUBLE_ID, 2);
    break;
  case FAULT_RESET_EVENT_ID:
    IntegerPrintf_Hex((p + 8), FAULT_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), RESET_ID, 2);
    break;
  case REGISTER_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), REGISTER_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), OCCUR_ID, 2);
    break;
  case REPLY_OCCUR_EVENT_ID:
    IntegerPrintf_Hex((p + 8), REPLY_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), network_data.platform_cmd_id, 2);
    break;
  default:
    IntegerPrintf_Hex((p + 8), HEART_EVENT_ID, 2);
    IntegerPrintf_Hex((p + 10), smoke_data.status, 2);
  }
  
  IntegerPrintf_Hex((p + 12), smoke_data.unit, 2);
  IntegerPrintf_Hex((p + 14), smoke_data.voltage, 2);
  IntegerPrintf_Hex((p + 16), smoke_data.temperature, 2);
  IntegerPrintf_Hex((p + 18), smoke_data.density, 2);
  IntegerPrintf_Hex((p + 20), (System.status & 0xFE), 2);
  IntegerPrintf_Hex((p + 22), smoke_data.voltage, 2);
  IntegerPrintf_Hex((p + 24), network_data.rssi, 2);
  
  return 26;
}
/*
** Generate Json Data Packet
*/
int GenerateJsonDataPacket(char *p)
{
  int i;

  memcpy(p, "{\"NO\":\"", 7);
  i = SignedIntegerPrintf((p + 7), system_data.no);
  i += 7;
  
  memcpy((p + i), "\",\"IMEI\":\"", 10);
  i += 10;
  memcpy((p + i), (char *)&system_data.IMEI, 15);
  i += 15;
  
  memcpy((p + i), "\",\"IMSI\":\"", 10);
  i += 10;
  memcpy((p + i), (char *)&system_data.IMSI, 15);
  i += 15;

  memcpy((p + i), "\",\"ICCID\":\"", 11);
  i += 11;
  memcpy((p + i), (char *)&system_data.ICCID, 20);
  i += 20;
  
  memcpy((p + i), "\",\"SIZE\":", 9);
  i += 9;
  IntegerPrintf((p + i), DATA_SIZE, 2);
  i += 2;
  
  memcpy((p + i), ",\"DATA\":\"", 9);
  i += 9;
  i += GetUplinkDetectorData((p + i), network_data.event_id);

  memcpy((p + i), "\",\"TAU\":\"", 9);
  i += 9;
  IntegerPrintf_Hex((p + i), network_data.active_time, 2);
  i += 2;
  IntegerPrintf_Hex((p + i), network_data.periodic_tau, 2);
  i += 2;
  p[i++] = '\"';

  memcpy((p + i), ",\"PCI\":\"", 8);
  i += 8;
  i += SignedIntegerPrintf((p + i), network_data.sc_pci);
    
  memcpy((p + i), "\",\"SNR\":", 8);
  i += 8;
  i += SignedIntegerPrintf((p + i), network_data.sc_snr);

  memcpy((p + i), ",\"ECL\":", 7);
  i += 7;
  i += SignedIntegerPrintf((p + i), network_data.sc_ecl);
  
  memcpy((p + i), ",\"NC\":", 6);
  i += 6;
  i += SignedIntegerPrintf((p + i), network_data.nc_num);

  memcpy((p + i), ",\"cell_ID\":\"", 12);
  i += 12;
  i += SignedIntegerPrintf((p + i), network_data.cell_id);
  
  memcpy((p + i), "\",\"SINR\":", 9);
  i += 9;
  i += SignedIntegerPrintf((p + i), network_data.nc_sinr);

  p[i++] = '}';
  p[i] = '\0';
  
  return i;
}
/*
** {"NO":0,"IMEI":"864481050677084","SIZE":5,"DATA":"0112020000"}
** 3030303138363434383130353036373730383430313132303230303030
** 紧凑型二进制: 00018644810506770840112020000
** 0 1 2 3|4 5 6 7 8 9 10 11 12 13 14 15 16 17 18|19 20 21 22 23 24 25 26 27 28
** 0 0 0 0|8 6 4 4 8 1 0  5  0  6  7  7  0  8  4 |0  1  1  2  0  2  0  0  0  0
*/
int ExplainPacketFormPlatform(char *p, uint32_t l)
{
  int i;
  char imei[20];
  char buffer[16];
  
  if(l != 29)
    return -1;

  memcpy(imei, (p + 4), 15);
  imei[15] = '\0';

  if(strcmp(imei, system_data.IMEI) == 0)
  {
    memcpy(buffer, (p + 19), 2);
    buffer[2] = '\0';
    network_data.platform_version = CharHexToInteger(buffer);

    if(network_data.platform_version == 0x01)
    {
      memcpy(buffer, p, 4);
      buffer[4] = '\0';
      network_data.platform_no = CharHexToInteger(buffer);
  
      memcpy(buffer, (p + 23), 2);
      buffer[2] = '\0';
      network_data.platform_data = CharHexToInteger(buffer);
      
      memcpy(buffer, (p + 21), 2);
      buffer[2] = '\0';
      network_data.platform_cmd_id = CharHexToInteger(buffer);

      return 0;
    }
  }  
  return -1;
}
/*------------------------------------------------------------------------------------------------*/
/*
** OneNET call back
*/
void onenet_read_callback(int mid, int objid, int insid, int resid)
{
  char buffer[256];
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nread_callback:%d,%d,%d,%d",mid,objid,insid,resid);
#endif
  if((objid == OBJECT_ID) && (resid == RESOURCE_ID) && (network_data.event_id >= 0))
  {
    GenerateJsonDataPacket(buffer);
    cm_onenet_read(mid, objid, insid, resid, 1, buffer, 1);//返回表示该操作结果数据,示例资源类型为string型
    network_data.onenet_masking |= ONENET_READ_SUCCESS_FLAG_MSK;
  }
  else
  {
    cm_onenet_result(mid, CM_RESULT_400_BADREQUEST, 0);//返回表示该操作结果错误
  }
}

/*
**{"NO":1,"IMEI":"864481050677084","SIZE":5,"DATA":"0113360000"}
** 00018611320494292430113360000
*/
void onenet_write_callback(int mid, int objid, int insid, int resid, int type, int flag, int len, char *data)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nwrite_callback:%d,%d,%d,%d,%d,%d,%d\r\n",mid,objid,insid,resid,type,flag,len);
  opencpu_printf_data(data, len);
#endif
  if(ExplainPacketFormPlatform(data, len) == 0)
  {
    opencpu_printf("\r\nno:%d,ver:%d,cmd:0x%x,data:0x%x", network_data.platform_no, 
                   network_data.platform_version, network_data.platform_cmd_id, network_data.platform_data);
  }
  if((objid == OBJECT_ID) && (resid == RESOURCE_ID))
  {
    cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
    network_data.onenet_masking |= ONENET_WRITE_SUCCESS_FLAG_MSK;
  }
  else
  {
    cm_onenet_result(mid, CM_RESULT_400_BADREQUEST, 0);//返回表示该操作结果错误
  }
}

void onenet_execute_callback(int mid, int objid, int insid, int resid, int len, char *data)
{
  cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nexecute_callback:%d,%d,%d,%d,%d\r\n",mid,objid,insid,resid,len);
  opencpu_printf_data(data,len);
#endif
}

/*
** observe_callback:51769,1,3200,0,-1
** observe_callback:24367,1,3200,0,-1
** observe_callback:46236,1,3200,0,-1
** observe_callback:8258,1,3200,0,-1
*/
void onenet_observe_callback(int mid, int observe, int objid, int insid, int resid)
{
  cm_onenet_result(mid, CM_RESULT_205_CONTENT, 1);//操作正确完成返回205
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nobserve_callback:%d,%d,%d,%d,%d",mid,observe,objid,insid,resid);
#endif
  network_data.onenet_masking |= ONENET_OBSERVE_SUCCESS_FLAG_MSK;
}

void onenet_parameter_callback(int mid,int objid, int insid, int resid, int len, char *parameter)
{
  cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nparameter_callback:%d,%d,%d,%d,%d\r\n",mid,objid,insid,resid,len);
  opencpu_printf_data(parameter,len);
#endif
}

void onenet_event_callback(int event)
{
	switch(event)
	{
    case CM_CIS_EVENT_BOOTSTRAP_START:
      opencpu_printf("\r\nonenet bootstrap start!");
      break;
    case CM_CIS_EVENT_BOOTSTRAP_SUCCESS:
      opencpu_printf("\r\nonenet bootstrap success!");
      break;
    case CM_CIS_EVENT_BOOTSTRAP_FAILED:
      opencpu_printf("\r\nonenet bootstrap failed!");
      break;
	case CM_CIS_EVENT_CONNECT_SUCCESS:
      opencpu_printf("\r\nconnect onenet success!");
	  break;
	case CM_CIS_EVENT_CONNECT_FAILED:
	  opencpu_printf("\r\nconnect onenet failded!");
	  break;
	case CM_CIS_EVENT_REG_SUCCESS: 
      opencpu_printf("\r\nonenet register success!");
	  network_data.onenet_masking |= ONENET_REGISTER_SUCCESS_FLAG_MSK;
	  break;
	case CM_CIS_EVENT_REG_FAILED:
	  opencpu_printf("\r\nonenet register failed!");
	  break;
	case CM_CIS_EVENT_REG_TIMEOUT:
	  opencpu_printf("\r\nonenet register timeout!");
	  break;
	case CM_CIS_EVENT_LIFETIME_TIMEOUT:
	  opencpu_printf("\r\nonenet lifetime timeout!");
	  break;
	case CM_CIS_EVENT_STATUS_HALT:
	  opencpu_printf("\r\nonenet status halt!");
	  break;
    case CM_CIS_EVENT_UPDATE_SUCCESS:
	  opencpu_printf("\r\nonenet update success!");
	  network_data.onenet_masking |= ONENET_UPDATE_SUCCESS_FLAG_MSK;
	  break;
	case CM_CIS_EVENT_UPDATE_FAILED:
	  opencpu_printf("\r\nonenet update failed!");
	  break;
	case CM_CIS_EVENT_UPDATE_TIMEOUT:
	  opencpu_printf("\r\nonenet update timeout!");
	  break;
	case CM_CIS_EVENT_UNREG_DONE:
      opencpu_printf("\r\nonenet unregister done!");
	  network_data.onenet_masking |= ONENET_UNREGISTER_DONE_FLAG_MSK;
	  break;
	case CM_CIS_EVENT_RESPONSE_FAILED:
	  opencpu_printf("\r\nonenet response failed!");
	  break;
	case CM_CIS_EVENT_RESPONSE_SUCCESS:
	  opencpu_printf("\r\nonenet response success!");
	  break;
	case CM_CIS_EVENT_NOTIFY_FAILED:
	  opencpu_printf("\r\nonenet notify failed!");
	  break;
	case CM_CIS_EVENT_NOTIFY_SUCCESS:
	  opencpu_printf("\r\nonenet notify success!");
	  break;
	//case CM_CIS_EVENT_FIRMWARE_TRIGGER:
	  //opencpu_printf("\nonenet firmware trigger!");
	  //break;
	default:
      opencpu_printf("\r\nevent_callback:%d",event);
      break;
	}
}

void onenet_notify_callback(int ack_id)
{
  if(ack_id == system_data.no)
  {
    network_data.onenet_masking |= ONENET_NOTIFY_ACK_SUCCESS_FLAG_MSK;
  }
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\nnotify_callback:%d",ack_id);
#endif
}

void onenet_discover_callback(int mid, int objid)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\ndiscover_callback:%d,%d",mid,objid);
#endif
  network_data.onenet_masking |= ONENET_DISCOVER_SUCCESS_FLAG_MSK;
}

/*
** OneNET connecting
** nbiotbt.heclouds.com <-> 183.230.40.39
*/
int onenet_connecting(void)
{
  int i;
  
  cm_cot_cb_t cb;
  cb.onRead = onenet_read_callback;
  cb.onWrite = onenet_write_callback;
  cb.onExec = onenet_execute_callback;
  cb.onObserve = onenet_observe_callback;
  cb.onParams = onenet_parameter_callback;
  cb.onEvent = onenet_event_callback;
  cb.onNotify = onenet_notify_callback;
  cb.onDiscover = onenet_discover_callback;

  //network_data.onenet_masking = 0;
  
  cm_onenet_init(); //初始化任务
  cm_onenet_create("183.230.40.39", 1, &cb); //创建设备
  cm_onenet_add_obj(OBJECT_ID, 1, "1", 0, 0);
  cm_onenet_discover(OBJECT_ID, 4, RESOURCE_ID_VALUE); //返回将用到的资源列表

  if(cm_onenet_open(30, ONENET_LIFETIME) != 0)
  {
	cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nOneNET open failed!");
#endif
   return -1;
  }

  i = 0;
  do{
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_onenet_close(2);
      cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nOneNET register failed!");
#endif
      return -1;
    }
  }while((network_data.onenet_masking & (ONENET_REGISTER_SUCCESS_FLAG_MSK + ONENET_OBSERVE_SUCCESS_FLAG_MSK + ONENET_DISCOVER_SUCCESS_FLAG_MSK)) != 
         (ONENET_REGISTER_SUCCESS_FLAG_MSK + ONENET_OBSERVE_SUCCESS_FLAG_MSK + ONENET_DISCOVER_SUCCESS_FLAG_MSK));

#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nOneNET connect success!",i);
#endif

  return 0;
}

/*
** OneNET updateing
*/
int onenet_updating(void)
{
  int i;

  if(cm_onenet_update(ONENET_LIFETIME, 1) != 0)
  {
    cm_onenet_close(2);
	cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nOneNET update() failed!");
#endif
 	return -1;
  }

  i = 0;
  do
  {
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_onenet_close(2);
	  cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nOneNET update failed!");
#endif
 	    return -1;
    }
  }while((network_data.onenet_masking & ONENET_UPDATE_SUCCESS_FLAG_MSK) == 0);
  
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nOneNET update success!", i);
#endif
  return 0;
}

/*
** OneNET notifying
*/
int onenet_notifying(void)
{
  int i;
  char buffer[256];
  
  i = GenerateJsonDataPacket(buffer);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\n%s",i,buffer);
#endif
  //network_data.onenet_masking = 0;

  if(cm_onenet_notify(OBJECT_ID, INSTANCE_ID, RESOURCE_ID, 1, buffer, 1, system_data.no, 0) != 0)
  {
    cm_onenet_close(2);
	cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nOneNET send failed!");
#endif
 	return -1;  
  }

  i = 0;
  do
  {
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_onenet_close(2);
	  cm_onenet_del_obj(OBJECT_ID);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nOneNET notify failed!");
#endif
 	  return -1;
    }
  }while((network_data.onenet_masking & ONENET_NOTIFY_ACK_SUCCESS_FLAG_MSK) == 0);
  
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nOneNET notify success!",i);
#endif

  return 0;
}
/*
** Connect OneNET
** nbiotbt.heclouds.com <-> 183.230.40.39
*/
void ConnectOneNET(void)
{
  int i,j;
  
  if((system_data.masking & CONNECT_PLATFORM_SUCCESS_FLAG_MSK) == 0)
  {
    if(onenet_connecting() == 0)
    {
      system_data.masking |= CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
	  
      if((system_data.masking & REBOOT_REPEAT_FLAG_MSK) != 0)
      {
        system_data.masking &= ~REBOOT_REPEAT_FLAG_MSK;
      }
      else
      {
        if((System.flag & POWER_ON_FLAG_MSK) != 0)
        {
          System.flag |= FIRST_SYSTEM_POWER_ON_FLAG_MSK;
        }
      }
    }
    else
    {
      system_data.masking |= SYSTEM_REBOOT_FLAG_MSK;
      
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
      
      if((system_data.masking & REBOOT_REPEAT_FLAG_MSK) == 0)
      {
        system_data.masking |= REBOOT_REPEAT_FLAG_MSK;
        system_data.reboot_counter = 0;
        system_data.heartbeat_time = T3412_1H_VALUE;
      }
      else
      {
        system_data.reboot_counter++;
        if(system_data.reboot_counter >= 2)
        {
          system_data.heartbeat_time = T3412_24H_VALUE;
        }
        else
        {
          system_data.heartbeat_time = T3412_2H_VALUE;
        }
      }
      return;
    }
  }

    if(onenet_updating() == 0)
    {
      if((system_data.masking & UPDATE_REPEAT_FLAG_MSK) != 0)
      {
        system_data.masking &= ~UPDATE_REPEAT_FLAG_MSK;
        System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
        system_data.heartbeat_time = system_data.obj_heartbeat_time;
      }
    }
    else
    {
      system_data.masking &= ~CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
    
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;

      if((system_data.masking & UPDATE_REPEAT_FLAG_MSK) == 0)
      {
        system_data.masking |= UPDATE_REPEAT_FLAG_MSK;
        system_data.update_counter = 0;
        system_data.heartbeat_time = T3412_2H_VALUE;
      }
      else
      {
        system_data.update_counter++;
        if(system_data.update_counter >= 2)
        {
          system_data.heartbeat_time = T3412_24H_VALUE;
        }
        else
        {
          system_data.heartbeat_time = T3412_4H_VALUE;
        }
      }
      return;
    }
  //}

  if(opencpu_get_cell_info() == 0)
  {
    //system_data.masking |= NETWORK_STATE_UPDATE_SUCCESS_FLAG_MSK;
    opencpu_printf("\r\nPCI:%d,RSRP:%d,RSRQ:%d,RSSI:%d,SNR:%d",
                    network_data.sc_pci, network_data.sc_rsrp, network_data.sc_rsrq, network_data.sc_rssi, network_data.sc_snr);
  }
  else
  {
    network_data.sc_rsrp = network_data.sc_rsrq = network_data.sc_rssi = network_data.sc_snr = 0;
    opencpu_printf("\r\nGet cell info faild!");
  }
  network_data.sc_ecl = network_data.nc_num = 0;
  //network_data.cell_ID[0] = '\0';
  //network_data.cell_id_length = 0;
  
  network_data.event_id = GetDetectorEventID();
  if(network_data.event_id < 0)
  {
    return;
  }

  if(onenet_notifying() == 0)
  {
    if((system_data.masking & NOTIFY_REPEAT_FLAG_MSK) != 0)
    {
      system_data.masking &= ~NOTIFY_REPEAT_FLAG_MSK;
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
      system_data.heartbeat_time = system_data.obj_heartbeat_time;
    }
    system_data.no++;
  }
  else
  {
    system_data.masking &= ~CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
    
    System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
    
    if((system_data.masking & NOTIFY_REPEAT_FLAG_MSK) == 0)
    {
      system_data.masking |= NOTIFY_REPEAT_FLAG_MSK;
      system_data.notify_counter = 0;
      system_data.heartbeat_time = T3412_2H_VALUE;
    }
    else
    {
      system_data.notify_counter++;
      if(system_data.notify_counter >= 2)
      {
        system_data.heartbeat_time = T3412_24H_VALUE;
      }
      else
      {
        system_data.heartbeat_time = T3412_4H_VALUE;
      }
    }
    return;
  }
  
  if((System.flag & FIRST_SYSTEM_POWER_ON_FLAG_MSK) != 0 || (system_data.status & (ALARM_EVENT_FLAG_MSK + TEST_EVENT_FLAG_MSK)) != 0)
  {
    for(i=0; i<300; i++)
    {
      osDelay(100);
      if(network_data.platform_cmd_id == PLATFORM_SETUP_CMD)
      {
		j = 10;
        do{
          IssueInDataPacket();
          osDelay(200);
		  if(uart.message == _success)
		  	break;
        }while(--j);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
        opencpu_printf("\r\n%d\r\nplatform cmd be sent!", 10-j);
#endif
        System.flag |= PLATFORM_REPLY_FLAG_MSK;
        network_data.event_id = REPLY_OCCUR_EVENT_ID;
        break;
      }
      
      if(network_data.platform_cmd_id == PLATFORM_SETUP_HEARTBEAT_TIME)
      {
        system_data.masking |= FIRST_T3412_UPDATE_FLAG_MSK;
        system_data.obj_heartbeat_time = network_data.platform_data;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
        opencpu_printf("\r\nplatform set heartbeat time success!");
#endif
        System.flag |= PLATFORM_REPLY_FLAG_MSK;
        network_data.event_id = REPLY_OCCUR_EVENT_ID;
        break;
      }
    } 
    
    if((System.flag & PLATFORM_REPLY_FLAG_MSK) != 0)
    {
      if(onenet_notifying() == 0)
      {
        system_data.no++;
      }
    }
  }
}
/*------------------------------------------------------------------------------------------------*/
/*
** AEP call back
*/
void aep_send_callback(int mid)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\naep send callback:%d", mid);
#endif
}
void aep_receiver_callback(char* data, int len)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\naep recv callback:%d", len);
  data[len] = '\0';
  opencpu_printf("\r\n%s",data);
#endif
	
  if(ExplainPacketFormPlatform(data, len) == 0)
  {
	opencpu_printf("\r\nno:%d,ver:%d,cmd:0x%x,data:0x%x", network_data.platform_no, 
				   network_data.platform_version, network_data.platform_cmd_id, network_data.platform_data);
  }
}
void aep_event_callback(int event, int mid)
{
  switch(event)
  {
  case CM_CTW_REG_OK:
    network_data.aep_masking |= AEP_REGISTER_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep register success!");
#endif
    break;
  case CM_CTW_REG_FAIL:
    //network_data.aep_masking &= ~AEP_REGISTER_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep register failed!");
#endif
    break;

  case CM_CTW_REG_UPDATED:
    network_data.aep_masking |= AEP_UPDATE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep update success!");
#endif
    break;
  case CM_CTW_REG_UPDAT_FAIL:
    //network_data.aep_masking &= ~AEP_UPDATE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep update failed!");
#endif
    break;

  case CM_CTW_DEREG:
	network_data.aep_masking |= AEP_DEREGISTER_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
	opencpu_printf("\r\naep deregister success!");
#endif
	break;
  case CM_CTW_DEREG_FAIL:
	//network_data.aep_masking &= ~AEP_DEREGISTER_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
	opencpu_printf("\r\naep deregister failed!");
#endif
	break;

  case CM_CTW_DATA_SUBSCRIBLE:
    network_data.aep_masking |= AEP_OBSERVE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep observe success!");
#endif
    break;
  case CM_CTW_DATA_UNSUBSCRIBLE:
    //network_data.aep_masking &= ~AEP_OBSERVE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep observe failed!");
#endif
    break; 

  case CM_CTW_DATA_SEND_OK:
    network_data.aep_masking |= AEP_NOTIFY_ACK_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nmid:%d,aep notify ack success!", mid);
#endif
    break;
  case CM_CTW_DATA_SEND_TIMEOUT:
    //network_data.aep_masking &= ~AEP_NOTIFY_ACK_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nmid:%d,aep notify ack failed!", mid);
#endif
    break;

  case CM_CTW_DTLS_HANDLE_OK:
    //network_data.aep_masking |= AEP_HANDSHAKE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep dtls success!");
#endif
    break;
  case CM_CTW_DTLS_HANDLE_FAIL:
    //network_data.aep_masking &= ~AEP_HANDSHAKE_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep dtls failed!");
#endif
    break;

  case CM_CTW_RECOVERY_OK:
    network_data.aep_masking |= AEP_STATE_RECOVERY_SUCCESS_FLAG_MSK;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\naep recovery success!");
#endif
    break;
  }
}
void aep_sequence_callback(unsigned char seq, unsigned char state)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\naep sequence callback:%d,%d", seq, state);
#endif
}
void aep_fota_callback(const cm_ctw_fota_state_t* state)
{
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\naep fota callback:%d", state->state);
#endif
}
/*
** Connect AEP
** www.ctwing.cn <-> 221.229.214.202 5683
*/
int aep_connecting(void)
{

  int i;
  
  cm_ctw_cb_t ctw_cb;
  int host_port = 5683;  

  if(cm_ctw_create(AEP_HOST_IP, host_port) != 0)
  {
    cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
	opencpu_printf("\r\nAEP create failed!");
#endif
	return -1;
  }

  ctw_cb.send_cb = aep_send_callback;
  ctw_cb.recv_cb = aep_receiver_callback;
  ctw_cb.evt_cb = aep_event_callback;
  ctw_cb.seq_cb = aep_sequence_callback;
  ctw_cb.fota_cb = aep_fota_callback;

  if(cm_ctw_open(AEP_LIFETIME, &ctw_cb) != 0)
  {
    cm_ctw_close();
    cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nAEP open failed!");
#endif
    return -1;
  }
  
  i = 0;
  do{
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_ctw_close();
      cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nAEP register failed!");
#endif
      return -1;
    }
  }while((network_data.aep_masking & (AEP_REGISTER_SUCCESS_FLAG_MSK + AEP_OBSERVE_SUCCESS_FLAG_MSK)) != 
         (AEP_REGISTER_SUCCESS_FLAG_MSK + AEP_OBSERVE_SUCCESS_FLAG_MSK));

#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nAEP connect success!",i);
#endif

  return 0;
}
/*
** aep updating
*/
int aep_updating(void)
{
  int i;
  
  //network_data.aep_masking = 0;

  i = cm_ctw_update();
  if(i != 0)
  {
    cm_ctw_close();
    cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nAEP update(%d) failed!",i);
#endif
    return -1;
  }

  i = 0;
  do
  {
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_ctw_close();
      cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nAEP update failed!");
#endif
 	    return -1;
    }
  }while((network_data.aep_masking & AEP_UPDATE_SUCCESS_FLAG_MSK) == 0);

#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nAEP update success!",i);
#endif
  return 0;
}
/*
** aep notifying
*/
int aep_notifying()
{
  int i,l;
  char buffer[256];

  //network_data.aep_masking = 0;

  l = GenerateJsonDataPacket(buffer);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\n%s",l,buffer);
#endif

  network_data.seq = system_data.no & 0x000000FF;
  if(network_data.seq == 0)
  {
    network_data.seq += 128;
  }
  //network_data.seq = 0;
  opencpu_printf("\r\nseq:%d",network_data.seq);

  if(cm_ctw_send_ex(buffer, l, CM_CTW_COAP_TYPE_CON, CM_CTW_RAI_0, (unsigned char)network_data.seq) != 0)
  {
    cm_ctw_close();
    cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
    opencpu_printf("\r\nAEP send failed!");
#endif
    return -1;
  }
    
  i = 0;
  do
  {
    osDelay(100);
    i++;
    if(i >= 300)
    {
      cm_ctw_close();
      cm_ctw_delete();
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      opencpu_printf("\r\nAEP notify failed!");
#endif
 	    return -1;
    }
  }while((network_data.aep_masking & AEP_NOTIFY_ACK_SUCCESS_FLAG_MSK) == 0);
  
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  opencpu_printf("\r\n%d\r\nAEP notify success!",i);
#endif

  return 0;
}
/*
** Connect AEP
** www.ctwing.cn <-> 221.229.214.202 5683
*/
void ConnectCTWing(void)
{
  int i,j;
  
  if((system_data.masking & CONNECT_PLATFORM_SUCCESS_FLAG_MSK) == 0)
  {
    if(aep_connecting() == 0)
    {
      system_data.masking |= CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
      //System.flag |= PLATFORM_UPDATE_LIFE_TIME_FLAG_MSK;
      
      if((system_data.masking & REBOOT_REPEAT_FLAG_MSK) != 0)
      {
        system_data.masking &= ~REBOOT_REPEAT_FLAG_MSK;
      }
      else
      {
        if((System.flag & POWER_ON_FLAG_MSK) != 0)
        {
          System.flag |= FIRST_SYSTEM_POWER_ON_FLAG_MSK;
        }
      }
    }
    else
    {
      system_data.masking |= SYSTEM_REBOOT_FLAG_MSK;
      
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
      
      if((system_data.masking & REBOOT_REPEAT_FLAG_MSK) == 0)
      {
        system_data.masking |= REBOOT_REPEAT_FLAG_MSK;
        system_data.reboot_counter = 0;
        system_data.heartbeat_time = T3412_1H_VALUE;
      }
      else
      {
        system_data.reboot_counter++;
        if(system_data.reboot_counter >= 2)
        {
          system_data.heartbeat_time = T3412_24H_VALUE;
        }
        else
        {
          system_data.heartbeat_time = T3412_2H_VALUE;
        }
      }
      return;
    }
  }

  //if((System.flag & PLATFORM_UPDATE_LIFE_TIME_FLAG_MSK) == 0)
  //{
    //System.flag |= PLATFORM_UPDATE_LIFE_TIME_FLAG_MSK;
  if(aep_updating() == 0)
  {
    if((system_data.masking & UPDATE_REPEAT_FLAG_MSK) != 0)
    {
      system_data.masking &= ~UPDATE_REPEAT_FLAG_MSK;
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
      system_data.heartbeat_time = system_data.obj_heartbeat_time;
    }
  }
  else
  {
    system_data.masking &= ~CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
  
    System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
    if((system_data.masking & UPDATE_REPEAT_FLAG_MSK) == 0)
    {
      system_data.masking |= UPDATE_REPEAT_FLAG_MSK;
      system_data.update_counter = 0;
      system_data.heartbeat_time = T3412_2H_VALUE;
    }
    else
    {
      system_data.update_counter++;
      if(system_data.update_counter >= 2)
      {
        system_data.heartbeat_time = T3412_24H_VALUE;
      }
      else
      {
        system_data.heartbeat_time = T3412_4H_VALUE;
      }
    }
    return;
  }
  //}
  
  if(opencpu_get_cell_info() == 0)
  {
    //system_data.masking |= NETWORK_STATE_UPDATE_SUCCESS_FLAG_MSK;
    opencpu_printf("\r\nPCI:%d,RSRP:%d,RSRQ:%d,RSSI:%d,SNR:%d",
                    network_data.sc_pci, network_data.sc_rsrp, network_data.sc_rsrq, network_data.sc_rssi, network_data.sc_snr);
  }
  else
  {
    network_data.sc_rsrp = network_data.sc_rsrq = network_data.sc_rssi = network_data.sc_snr = 0;
    opencpu_printf("\r\nGet cell info faild!");
  }
  network_data.sc_ecl = network_data.nc_num = 0;

  network_data.event_id = GetDetectorEventID();
  if(network_data.event_id < 0)
  {
    return;
  }

  if(aep_notifying() == 0)
  {
    if((system_data.masking & NOTIFY_REPEAT_FLAG_MSK) != 0)
    {
      system_data.masking &= ~NOTIFY_REPEAT_FLAG_MSK;
      System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
      system_data.heartbeat_time = system_data.obj_heartbeat_time;
    }
    system_data.no++;
  }
  else
  {
    system_data.masking &= ~CONNECT_PLATFORM_SUCCESS_FLAG_MSK;
    
    System.flag |= HEARTBEAT_TIME_UPDATE_FLAG_MSK;
    
    if((system_data.masking & NOTIFY_REPEAT_FLAG_MSK) == 0)
    {
      system_data.masking |= NOTIFY_REPEAT_FLAG_MSK;
      system_data.notify_counter = 0;
      system_data.heartbeat_time = T3412_2H_VALUE;
    }
    else
    {
      system_data.notify_counter++;
      if(system_data.notify_counter >= 2)
      {
        system_data.heartbeat_time = T3412_24H_VALUE;
      }
      else
      {
        system_data.heartbeat_time = T3412_4H_VALUE;
      }
    }
    return;
  }

  if((System.flag & FIRST_SYSTEM_POWER_ON_FLAG_MSK) != 0 || (system_data.status & (ALARM_EVENT_FLAG_MSK + TEST_EVENT_FLAG_MSK)) != 0)
  {
    for(i=0; i<300; i++)
    {
      osDelay(100);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
      //opencpu_printf("%d;", i);
#endif	  
      if(network_data.platform_cmd_id == PLATFORM_SETUP_CMD)
      {
        j = 10;
        do{
          IssueInDataPacket();
          osDelay(200);
		  if(uart.message == _success)
		  	break;
        }while(--j);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
        opencpu_printf("\r\n%d\r\nplatform cmd be sent!", 10-j);
#endif
        System.flag |= PLATFORM_REPLY_FLAG_MSK;
        network_data.event_id = REPLY_OCCUR_EVENT_ID;
        break;
      }
      
      if(network_data.platform_cmd_id == PLATFORM_SETUP_HEARTBEAT_TIME)
      {
        system_data.masking |= FIRST_T3412_UPDATE_FLAG_MSK;
        system_data.obj_heartbeat_time = network_data.platform_data;
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
        opencpu_printf("\r\nplatform set heartbeat time success!");
#endif
        System.flag |= PLATFORM_REPLY_FLAG_MSK;
        network_data.event_id = REPLY_OCCUR_EVENT_ID;
        break;
      }
    } 
    
    if((System.flag & PLATFORM_REPLY_FLAG_MSK) != 0)
    {
      if(aep_notifying() == 0)
      {
        system_data.no++;
      }
    }
  }
}
/*------------------------------------------------------------------------------------------------*/

