#ifndef __IOT_API_H
#define __IOT_API_H
/*--------------------------------------------------*/
/*
Public Data Network --- PDN
*/
#include "macro_definition.h"
/*--------------------------------------------------*/
//typedef unsigned int bool;
/*--------------------------------------------------*/
struct xy_wall_clock
{
  uint32_t tm_sec;  /* Seconds (0-59) */
  uint32_t tm_min;  /* Minutes (0-59) */
  uint32_t tm_hour; /* Hours (0-23) */
  uint32_t tm_mday; /* Day of the month (1-31) */
  uint32_t tm_mon;  /* Month (0-11) */
  uint32_t tm_year; /* Years */
  uint32_t tm_wday; /* Day of the week (0-6),always ignore */
  uint32_t tm_yday; /* Day of the year (0-365),always ignore */
};
/*--------------------------------------------------*/
/*
struct tm {
  int tm_sec;  //0-59
  int tm_min;  //0-59
  int tm_hour; //0-23
  int tm_mday; //1-31
  int tm_mon;  //月份(0代表一月):0-11
  int tm_year; //年份,其值从1900开始
  int tm_wday; //星期-取值区间为【0,6】,0代表星期天,1代表星期一 //不可用
  int tm_yday; //从每年的1月1日开始的天数:0-365,其中0代表1月1日 //不可用
  int tm_isdst;//夏令时标识符,实行夏令时的时候,tm_isdst为正 //不可用
};
*/
/*--------------------------------------------------*/
#define SERVER_DOMAIN_NAME "tomboy2020.vicp.net"
#define SERVER_IP "103.46.128.41"
#define SERVER_PORT 31269
/*--------------------------------------------------*/
#define SERVER_2_DOMAIN_NAME "nbiotbt.heclouds.com"
#define SERVER_2_IP "183.230.40.39"
#define SERVER_2_PORT 5683
/*--------------------------------------------------*/
#define SERVER_3_DOMAIN_NAME "www.baidu.com"
#define SERVER_3_PORT 80
/*--------------------------------------------------*/
#define AEP_HOST_IP "221.229.214.202"
#define AEP_HOST_PORT "5683"
#define AEP_AUTO_RECEIVE_MODE 0
#define AEP_MANUAL_RECEIVE_MODE 1
#define AEP_LIFETIME 86400
//#define AEP_LIFETIME 115200 //32*3600=115200
/*--------------------------------------------------*/
#define OBJECT_ID 3200
#define INSTANCE_ID 0
#define RESOURCE_ID 5750
#define RESOURCE_ID_VALUE "5750"
#define ONENET_LIFETIME 111600 //31*3600=111600
/*--------------------------------------------------*/
#define RSSI_MIN_VALUE -110
/*--------------------------------------------------*/
#define T3324_8_BIT_VALUE "00000000"
#define T3324_HEX_VALUE  0x0
#define T3412_8_BIT_VALUE "00111000"
#define T3412_HEX_VALUE  0x38
/*--------------------------------------------------*/
#define MULTIPLE_10_MINUTES 0
#define MULTIPLE_1_HOUR 1
/*--------------------------------------------------*/
#define EDRX_4_BIT_VALUE "0010"
#define NB_S1_MODE_VALUE 5
#define DISABLE_EDRX_MODE_VALUE 0
/*--------------------------------------------------*/
#define NETWORK_DATA_BUFFER_SIZE 32
#define APN_SIZE 20
#define IP_SIZE 20
#define EDRX_SIZE 8
/*--------------------------------------------------*/
//ONENET_MASKING
#define ONENET_REGISTER_SUCCESS_FLAG_POS 0
#define ONENET_REGISTER_SUCCESS_FLAG_MSK (1UL << ONENET_REGISTER_SUCCESS_FLAG_POS)

#define ONENET_UNREGISTER_DONE_FLAG_POS 1
#define ONENET_UNREGISTER_DONE_FLAG_MSK (1UL << ONENET_UNREGISTER_DONE_FLAG_POS)

#define ONENET_OBSERVE_SUCCESS_FLAG_POS 2
#define ONENET_OBSERVE_SUCCESS_FLAG_MSK (1UL << ONENET_OBSERVE_SUCCESS_FLAG_POS)

#define ONENET_DISCOVER_SUCCESS_FLAG_POS 3
#define ONENET_DISCOVER_SUCCESS_FLAG_MSK (1UL << ONENET_DISCOVER_SUCCESS_FLAG_POS)

#define ONENET_NOTIFY_ACK_SUCCESS_FLAG_POS 4
#define ONENET_NOTIFY_ACK_SUCCESS_FLAG_MSK (1UL << ONENET_NOTIFY_ACK_SUCCESS_FLAG_POS)

#define ONENET_READ_SUCCESS_FLAG_POS 5
#define ONENET_READ_SUCCESS_FLAG_MSK (1UL << ONENET_READ_SUCCESS_FLAG_POS)

#define ONENET_WRITE_SUCCESS_FLAG_POS 6
#define ONENET_WRITE_SUCCESS_FLAG_MSK (1UL << ONENET_WRITE_SUCCESS_FLAG_POS)

#define ONENET_UPDATE_SUCCESS_FLAG_POS 7
#define ONENET_UPDATE_SUCCESS_FLAG_MSK (1UL << ONENET_UPDATE_SUCCESS_FLAG_POS)
/*--------------------------------------------------*/
//AEP_MASKING
#define AEP_REGISTER_SUCCESS_FLAG_POS 0
#define AEP_REGISTER_SUCCESS_FLAG_MSK (1UL << AEP_REGISTER_SUCCESS_FLAG_POS)

#define AEP_UPDATE_SUCCESS_FLAG_POS 1
#define AEP_UPDATE_SUCCESS_FLAG_MSK (1UL << AEP_UPDATE_SUCCESS_FLAG_POS)

#define AEP_OBSERVE_SUCCESS_FLAG_POS 2
#define AEP_OBSERVE_SUCCESS_FLAG_MSK (1UL << AEP_OBSERVE_SUCCESS_FLAG_POS)

#define AEP_NOTIFY_ACK_SUCCESS_FLAG_POS 3
#define AEP_NOTIFY_ACK_SUCCESS_FLAG_MSK (1UL << AEP_NOTIFY_ACK_SUCCESS_FLAG_POS)

#define AEP_HANDSHAKE_SUCCESS_FLAG_POS 4
#define AEP_HANDSHAKE_SUCCESS_FLAG_MSK (1UL << AEP_HANDSHAKE_SUCCESS_FLAG_POS)

#define AEP_DEREGISTER_SUCCESS_FLAG_POS 5
#define AEP_DEREGISTER_SUCCESS_FLAG_MSK (1UL << AEP_DEREGISTER_SUCCESS_FLAG_POS)

#define AEP_LWM2M_SESSION_ABNORMAL_FLAG_POS 7
#define AEP_LWM2M_SESSION_ABNORMAL_FLAG_MSK (1UL << AEP_LWM2M_SESSION_ABNORMAL_FLAG_POS)

#define AEP_READ_SUCCESS_FLAG_POS 8
#define AEP_READ_SUCCESS_FLAG_MSK (1UL << AEP_READ_SUCCESS_FLAG_POS)

#define AEP_WRITE_SUCCESS_FLAG_POS 9
#define AEP_WRITE_SUCCESS_FLAG_MSK (1UL << AEP_WRITE_SUCCESS_FLAG_POS)

#define AEP_NOTIFY_SEQ_ACK_SUCCESS_FLAG_POS 10
#define AEP_NOTIFY_SEQ_ACK_SUCCESS_FLAG_MSK (1UL << AEP_NOTIFY_SEQ_ACK_SUCCESS_FLAG_POS)

#define AEP_NOTIFY_MID_ACK_SUCCESS_FLAG_POS 11
#define AEP_NOTIFY_MID_ACK_SUCCESS_FLAG_MSK (1UL << AEP_NOTIFY_MID_ACK_SUCCESS_FLAG_POS)

#define AEP_STATE_RECOVERY_SUCCESS_FLAG_POS 16
#define AEP_STATE_RECOVERY_SUCCESS_FLAG_MSK (1UL << AEP_STATE_RECOVERY_SUCCESS_FLAG_POS)
/*--------------------------------------------------*/
typedef struct
{
  unsigned int message;
  
  unsigned int length;
  unsigned char buffer[NETWORK_DATA_BUFFER_SIZE];
  
  //uint32_t cid; /**< Defines the PDP(Packet Data Protocol) context.  */
  //unsigned char apn[APN_SIZE]; /**APN(Access Point Name): A logical name to select the GGSN or the external packet data network. */
  //unsigned char local_ip[IP_SIZE];

  //int cell_id_length;
  //unsigned char cell_ID[10];
  uint32_t cell_id;
  int32_t sc_pci;
  int32_t sc_rsrp;
  int32_t sc_rsrq;
  int32_t sc_rssi;
  int32_t sc_snr;
  int32_t sc_ecl;
  
  int32_t nc_num;
  int32_t nc_pci;
  int32_t nc_rsrp;
  int32_t nc_rsrq;
  int32_t nc_rssi;
  int32_t nc_sinr;

  int32_t act_type;
/*
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  //unsigned char requested_eDRX_value[EDRX_SIZE];
  unsigned char provided_eDRX_value[EDRX_SIZE];
  unsigned char paging_time_window_value[EDRX_SIZE];
#endif
*/
  uint32_t active_time;
  uint32_t periodic_tau;

  char rssi;
  char lqi;

  int socket;
  uint32_t onenet_masking;
  uint32_t aep_masking;
  uint32_t seq;

  int event_id;
  
  unsigned int platform_no;
  unsigned int platform_version;
  unsigned int platform_cmd_id;
  unsigned int platform_data;

  //unsigned int no;
  //unsigned char imei[20];
  //unsigned char imsi[20];
  
  uint32_t time_stamp;
  
  unsigned short year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
  unsigned char reserved[2];
}NETWORK_TypeDef;
/*--------------------------------------------------*/
void CheckPSM(void);
int ModifyHeartbeatTime(void);


int opencpu_get_cereg(void);
int opencpu_get_cell_info(void);
int opencpu_get_psm(void);
int opencpu_get_edrx(void);
int opencpu_get_time(void);

int ConnectServerWithUDP(int mode);
void ConnectOneNET(void);
void ConnectCTWing(void);
/*--------------------------------------------------*/
#endif

