/*
**
*/
#ifndef __FLASH_API_H
#define __FLASH_API_H
/* ====================================================== */
/**
** XY1100
** 我们提供了40K flash供用户使用，地址从0到40K。
** 块(最小可擦除单元)总数(用户空间中的flash块总数):16
** 单个块(最小可擦除单元)的大小:4096(1 0000 0000 0000)
** 20KB: 0x0000 0000 - 0x0000 5000
** 40KB: 0x0000 0000 - 0x0000 A000
*/
#define EEPROM_PAGE0_BASE  ((unsigned long)0x00000000)
#define EEPROM_PAGE0_BLOCK 1
#define	EEPROM_PAGE1_BASE	((unsigned long)0x00005000)
#define EEPROM_PAGE1_BLOCK 5
/* ====================================================== */
#define  EEPROM_INITIALIZE_FLAG  0x55AA55AA
/* ====================================================== */
#define  IMEI_SIZE  20
#define  ICCID_SIZE  24
#define  IMSI_SIZE  20
#define  HOST_IP_SIZE  20
/* ====================================================== */
typedef struct
{
  uint32_t masking;
  
  uint32_t no;
  uint32_t service_provider;
  
  unsigned char IMEI[IMEI_SIZE];
  unsigned char ICCID[ICCID_SIZE];
  unsigned char IMSI[IMSI_SIZE];
  
  unsigned short year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
  unsigned char reserved[2];
/*--------------------------------------------------------*/
  uint32_t time_stamp;  //格林威治时间1970年01月01日00时00分00秒
/*--------------------------------------------------------*/
  uint32_t status;
  uint32_t event_id;
  uint32_t obj_heartbeat_time;
  uint32_t heartbeat_time;
  uint32_t reboot_counter;
  uint32_t update_counter;
  uint32_t notify_counter;
/*--------------------------------------------------------*/
  uint32_t day_counter;
/*--------------------------------------------------------*/
  unsigned int crc16;
  unsigned int initialize_flag;
}SYSTEM_DATA_TypeDef;
/* ====================================================== */
#define SYSTEM_DATA_SIZE sizeof(SYSTEM_DATA_TypeDef)
/* ====================================================== */
#define EEPROM_DATA ((SYSTEM_DATA_TypeDef *)EEPROM_PAGE0_BASE)
#define EEPROM_DATA_BACKUP ((SYSTEM_DATA_TypeDef *)EEPROM_PAGE1_BASE)
/* ====================================================== */
uint32_t CalculateCRC_CCITT(unsigned char *p, uint32_t n);
/* ====================================================== */
void ReadSystemData(void);
void WriteSystemData(void);
void SaveSystemData(void);
int Get_Service_Provider(void);
/* ====================================================== */
#endif

