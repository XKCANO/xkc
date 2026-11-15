#ifndef __MACRO_DEFINITION_H
#define __MACRO_DEFINITION_H
/*---------------------------------------------------------------------*/
typedef void* TaskHandle_t;
//typedef int int32_t;
typedef unsigned short uint16_t;
//typedef unsigned int uint32_t;
//typedef unsigned int bool;
/*---------------------------------------------------------------------*/
#define _OPENCPU_DEBUG_OUTPUT_MODE
#define _KINGDUN_OUTPUT_MODE
/*---------------------------------------------------------------------*/
#define WAKING_FLAG  0x55AA55AA
/*---------------------------------------------------------------------*/
#define _success 10000
#define _failed  10001
#define	_error   10002
/*---------------------------------------------------------------------*/
#define  NETWORK_STATUS_OVERTIME  -3
#define  NETWORK_STATUS_INVALID_PARAM  -2
#define  NETWORK_STATUS_FAILED  -1
#define  NETWORK_STATUS_SUCCESS  0
/*---------------------------------------------------------------------*/
//SYSTEM_DATA MASKING
#define  SYSTEM_REBOOT_FLAG_POS  0
#define  SYSTEM_REBOOT_FLAG_MSK  (1UL << SYSTEM_REBOOT_FLAG_POS)

#define  SIM_INITIALIZE_FLAG_POS  1
#define  SIM_INITIALIZE_FLAG_MSK  (1UL << SIM_INITIALIZE_FLAG_POS)

#define  TIME_UPDATE_SUCCESS_FLAG_POS  2
#define  TIME_UPDATE_SUCCESS_FLAG_MSK  (1UL << TIME_UPDATE_SUCCESS_FLAG_POS)

#define  CONNECT_PLATFORM_SUCCESS_FLAG_POS  3
#define  CONNECT_PLATFORM_SUCCESS_FLAG_MSK  (1UL << CONNECT_PLATFORM_SUCCESS_FLAG_POS)

#define  FIRST_T3412_UPDATE_FLAG_POS  4
#define  FIRST_T3412_UPDATE_FLAG_MSK  (1UL << FIRST_T3412_UPDATE_FLAG_POS)

#define  REBOOT_REPEAT_FLAG_POS  8
#define  REBOOT_REPEAT_FLAG_MSK  (1UL << REBOOT_REPEAT_FLAG_POS)

#define  UPDATE_REPEAT_FLAG_POS  9
#define  UPDATE_REPEAT_FLAG_MSK  (1UL << UPDATE_REPEAT_FLAG_POS)

#define  NOTIFY_REPEAT_FLAG_POS  10
#define  NOTIFY_REPEAT_FLAG_MSK  (1UL << NOTIFY_REPEAT_FLAG_POS)

#define  SYSTEM_WAKEUP_INTERRUPT_FLAG_POS  15
#define  SYSTEM_WAKEUP_INTERRUPT_FLAG_MSK  (1UL << SYSTEM_WAKEUP_INTERRUPT_FLAG_POS)

//SYSTEM FLAG
#define  POWER_ON_FLAG_POS  0
#define  POWER_ON_FLAG_MSK  (1UL << POWER_ON_FLAG_POS)

#define  INTERRUPT_WAKEUP_IN_FLAG_POS  1
#define  INTERRUPT_WAKEUP_IN_FLAG_MSK  (1UL << INTERRUPT_WAKEUP_IN_FLAG_POS)

#define  PSM_WAKEUP_IN_FLAG_POS  2
#define  PSM_WAKEUP_IN_FLAG_MSK  (1UL << PSM_WAKEUP_IN_FLAG_POS)

#define  LOCAL_TIME_UPDATE_SUCCESS_FLAG_POS  9
#define  LOCAL_TIME_UPDATE_SUCCESS_FLAG_MSK  (1UL << LOCAL_TIME_UPDATE_SUCCESS_FLAG_POS)

#define  HEARTBEAT_TIME_UPDATE_FLAG_POS  10
#define  HEARTBEAT_TIME_UPDATE_FLAG_MSK  (1UL << HEARTBEAT_TIME_UPDATE_FLAG_POS)

#define  FIRST_SYSTEM_POWER_ON_FLAG_POS  11
#define  FIRST_SYSTEM_POWER_ON_FLAG_MSK  (1UL << FIRST_SYSTEM_POWER_ON_FLAG_POS)

#define  PLATFORM_UPDATE_LIFE_TIME_FLAG_POS  13
#define  PLATFORM_UPDATE_LIFE_TIME_FLAG_MSK  (1UL << PLATFORM_UPDATE_LIFE_TIME_FLAG_POS)

#define  PLATFORM_REPLY_FLAG_POS  15
#define  PLATFORM_REPLY_FLAG_MSK  (1UL << PLATFORM_REPLY_FLAG_POS)

//SYSTEM STATUS BIT0~4
#define  ACTIVE_FLAG_POS  0
#define  ACTIVE_FLAG_MSK  (1UL << ACTIVE_FLAG_POS)

#define  FAULT_FLAG_POS  1
#define  FAULT_FLAG_MSK  (1UL << FAULT_FLAG_POS)

#define  PSM_ERROR_FLAG_POS  2
#define  PSM_ERROR_FLAG_MSK  (1UL	<< PSM_ERROR_FLAG_POS)

#define  LOW_BATTERY_FLAG_POS  3
#define  LOW_BATTERY_FLAG_MSK  (1UL << LOW_BATTERY_FLAG_POS)

//SYSTEM STATUS BIT5~7 --> PACKET ID
#define SETUP_PACKET_ID 0
#define OUT_PACKET_ID 1
#define IN_PACKET_ID 2
#define SOF_PACKET_ID 3
#define ACK_PACKET_ID 4
#define NAK_PACKET_ID 5

//SYSTEM DATA STATUS
#define  ALARM_EVENT_FLAG_POS  0
#define  ALARM_EVENT_FLAG_MSK  (1UL << ALARM_EVENT_FLAG_POS)

#define  TEST_EVENT_FLAG_POS  1
#define  TEST_EVENT_FLAG_MSK  (1UL << TEST_EVENT_FLAG_POS)

#define  REMOVE_EVENT_FLAG_POS  2
#define  REMOVE_EVENT_FLAG_MSK  (1UL << REMOVE_EVENT_FLAG_POS)

#define  BATTERY_LOW_FAULT_EVENT_FLAG_POS  4
#define  BATTERY_LOW_FAULT_EVENT_FLAG_MSK  (1UL << BATTERY_LOW_FAULT_EVENT_FLAG_POS)

#define  SENSOR_TROUBLE_FAULT_EVENT_FLAG_POS  5
#define  SENSOR_TROUBLE_FAULT_EVENT_FLAG_MSK  (1UL << SENSOR_TROUBLE_FAULT_EVENT_FLAG_POS)

//DETECTOR STATUS
#define  DETECTOR_ALERT_FLAG_POS  0
#define  DETECTOR_ALERT_FLAG_MSK  (1UL << DETECTOR_ALERT_FLAG_POS)

#define  DETECTOR_HUSH_FLAG_POS  1
#define  DETECTOR_HUSH_FLAG_MSK  (1UL << DETECTOR_HUSH_FLAG_POS)

#define  DETECTOR_TEST_FLAG_POS  2
#define  DETECTOR_TEST_FLAG_MSK  (1UL << DETECTOR_TEST_FLAG_POS)

#define  DETECTOR_LOW_BATTERY_FLAG_POS  3
#define  DETECTOR_LOW_BATTERY_FLAG_MSK  (1UL << DETECTOR_LOW_BATTERY_FLAG_POS)

#define  DETECTOR_SENSOR_TROUBLE_FLAG_POS   4
#define  DETECTOR_SENSOR_TROUBLE_FLAG_MSK   (1UL << DETECTOR_SENSOR_TROUBLE_FLAG_POS)

#define  DETECTOR_SENSOR_DUST_FLAG_POS  5
#define  DETECTOR_SENSOR_DUST_FLAG_MSK  (1UL << DETECTOR_SENSOR_DUST_FLAG_POS)

#define  DETECTOR_EEPROM_TROUBLE_FLAG_POS  6
#define  DETECTOR_EEPROM_TROUBLE_FLAG_MSK  (1UL << DETECTOR_EEPROM_TROUBLE_FLAG_POS)

#define  DETECTOR_REMOVE_FLAG_POS  7
#define  DETECTOR_REMOVE_FLAG_MSK  (1UL << DETECTOR_REMOVE_FLAG_POS)
/*---------------------------------------------------------------------*/
// PACKET ID
#define  EVENT_PACKET_ID  0x01
#define  RESET_PACKET_ID  0x04
#define  HEARTBEAT_PACKET_ID  0x08
/*---------------------------------------------------------------------*/
// Code
#define  SMOKE_DETECTOR_CODE  0x01
#define  FG520_NB  0x20
/*---------------------------------------------------------------------*/
#define  HEARTBEAT_EVENT_ID    0
#define  ALARM_OCCUR_EVENT_ID  1
#define  ALARM_RESET_EVENT_ID  2
#define  TEST_OCCUR_EVENT_ID   3
#define  TEST_RESET_EVENT_ID   4
#define  REMOVE_OCCUR_EVENT_ID  5
#define  REMOVE_RESET_EVENT_ID  6
#define  BATTERY_LOW_OCCUR_EVENT_ID     7
#define  SENSOR_TROUBLE_OCCUR_EVENT_ID  8
#define  SENSOR_DUST_OCCUR_EVENT_ID     9
#define  EEPROM_TROUBLE_OCCUR_EVENT_ID  10
#define  FAULT_RESET_EVENT_ID     11
#define  REGISTER_OCCUR_EVENT_ID  12
#define  REPLY_OCCUR_EVENT_ID     13
/*---------------------------------------------------------------------*/
// Protocol v01
#define  PROTOCOL_VERSION  0x03
#define  DEVICE_CLASS  0x01
#define  DEVICE_TYPE  SMOKE_DETECTOR_CODE
#define  DEVICE_MODEL  FG520_NB

#define  HEART_EVENT_ID  0x01
#define  ALARM_EVENT_ID  0x02
#define  TEST_EVENT_ID   0x03
#define  REMOVE_EVENT_ID  0x04
#define  FAULT_EVENT_ID   0x05
#define  REGISTER_EVENT_ID  0x08
#define  REPLY_EVENT_ID     0x09

#define  OCCUR_ID  0x01
#define  RESET_ID  0x80

#define  BATTERY_LOW_ID  0x01
#define  SENSOR_TROUBLE_ID  0x02
#define  SENSOR_DUST_ID     0x03
#define  EEPROM_TROUBLE_ID  0x04

#define  UNIT_VALUE  0x10
#define  DATA_SIZE 13

#define  PLATFORM_SETUP_CMD  0x12
#define  PLATFORM_SETUP_HEARTBEAT_TIME  0X13
/*---------------------------------------------------------------------*/
//SYSTEM CMD
#define  EXT_ALARM_CMD_FLAG_POS  0
#define  EXT_ALARM_CMD_FLAG_MSK  (1UL << EXT_ALARM_CMD_FLAG_POS)

#define  EXT_HUSH_CMD_FLAG_POS  1
#define  EXT_HUSH_CMD_FLAG_MSK  (1UL << EXT_HUSH_CMD_FLAG_POS)

#define  EXT_TEST_CMD_FLAG_POS  2
#define  EXT_TEST_CMD_FLAG_MSK  (1UL << EXT_TEST_CMD_FLAG_POS)
/*---------------------------------------------------------------------*/
#define  T3412_1H_VALUE  0x21
#define  T3412_2H_VALUE  0x22
#define  T3412_4H_VALUE  0x24
#define  T3412_18H_VALUE  0x32
#define  T3412_20H_VALUE  0x34
#define  T3412_22H_VALUE  0x36
#define  T3412_24H_VALUE  0x38
/*---------------------------------------------------------------------*/
//#define  HEARTBEAT_TIME_VALUE  22
/*---------------------------------------------------------------------*/
#define  CMCC  1
#define  CTCC  2
#define  CUCC  3
/*---------------------------------------------------------------------*/
#endif


