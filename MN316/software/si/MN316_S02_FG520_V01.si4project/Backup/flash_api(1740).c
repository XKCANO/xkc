/*
**
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "macro_definition.h"
#include "flash_api.h"

#include "cm_os.h"
#include "cm_flash.h"

#include "uart_api.h"
/*----------------------------------------------------------------------------------------------------*/
const unsigned short CRC_CCITT_TABLE[16] =
{
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};
/*----------------------------------------------------------------------------------------------------*/
SYSTEM_DATA_TypeDef system_data;
/*----------------------------------------------------------------------------------------------------*/
/*
** Calculate CRC CCITT
*/
uint32_t CalculateCRC_CCITT(unsigned char *p, uint32_t n)
{
	unsigned int m, sum = 0;
	
	while(n--)
	{
		m = (uint32_t)(*p >> 4) & 0x0000000F;
		m = ((sum >> 12) & 0x0000000F) ^ m;
		sum = (sum << 4) ^ CRC_CCITT_TABLE [m];
		
		m = ((sum >> 12) & 0x0000000F) ^ (uint32_t)(*p & 0x0000000F);
		sum = (sum << 4) ^ CRC_CCITT_TABLE [m];
		
		p++;
	};
	
	return (sum & 0x0000FFFF);
}
/*----------------------------------------------------------------------------------------------------*/
/*
** Reset Default Factory
*/
void ResetDefaultFactory(void)
{
  system_data.masking = 0;
  system_data.no = 0;
  system_data.status = 0;
  system_data.event_id = 128;
  system_data.obj_heartbeat_time = T3412_20H_VALUE;
  system_data.reboot_counter =
  system_data.update_counter =
  system_data.notify_counter = 0;
  system_data.day_counter = 256;
}
/*----------------------------------------------------------------------------------------------------*/
/*
** Read System Data
*/
void ReadSystemData(void)
{
  unsigned int i,s;
  SYSTEM_DATA_TypeDef system_data_backup;

  i = 3;
  do{
  	//读取EEPROM_PAGE0_BASE地址的数据，存储到system_data.masking（结构体首地址）的地址中，读取长度为结构体system_data的大小
  	if(cm_flash_read((uint32_t)EEPROM_DATA, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) == SYSTEM_DATA_SIZE)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  if(i == 0)//读取三次都失败则打印
    opencpu_printf("\nRead EEPROM page0 failed!");
#endif
  i = 3;
  do{
  	//读取EEPROM_PAGE1_BASE地址的数据，存储到system_data_backup.masking（结构体首地址）的地址中，读取长度为结构体system_data_backup的大小
  	if(cm_flash_read((uint32_t)EEPROM_DATA_BACKUP, (unsigned char *)&system_data_backup.masking, SYSTEM_DATA_SIZE) == SYSTEM_DATA_SIZE)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  if(i == 0)//读取三次都失败则打印
    opencpu_printf("\nRead EEPROM page1 failed!");
#endif
  //检查system_data初始化，若已经初始化则对结构体数据进行CRC校验，否则检查system_data_backup初始化
  if(system_data.initialize_flag == EEPROM_INITIALIZE_FLAG)
  {
    s = CalculateCRC_CCITT((unsigned char *)&system_data.masking, (SYSTEM_DATA_SIZE - 8));
	//再判断是否等于存储的CRC检验数据且不为0
  	if(s != 0 && s == system_data.crc16)
  	{
  	  //若等于再判断是否不等于备份的CRC检验数据
  	  if(system_data.crc16 != system_data_backup.crc16)
  	  {
  	    //若不等于则擦除EEPROM中EEPROM_PAGE1_BLOCK中的数据，并判断是否擦除成功
        if(cm_flash_erase(EEPROM_PAGE1_BLOCK, 1) != 0)
        {
          opencpu_printf("\nErase EEPROM page1 failed!");
        }
		//并将system_data.masking 写入 EEPROM的EEPROM_PAGE1_BASE中，并判断是否写入成功
        if(cm_flash_write((uint32_t)EEPROM_DATA_BACKUP, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) != SYSTEM_DATA_SIZE)
        {
          opencpu_printf("\nWrite EEPROM page1 failed!");
        }
  	  }
  	}
	//若system_data存储的CRC检验数据0或者实际CRC检验数据不等于存储的CRC检验数据则判断system_data_backup初始化
	else
  	{
  	  if(system_data_backup.initialize_flag == EEPROM_INITIALIZE_FLAG)
      {
        //system_data_backup已经初始化则对system_data_backup数据进行CRC校验
        s = CalculateCRC_CCITT((unsigned char *)&system_data_backup.masking, (SYSTEM_DATA_SIZE - 8));
		//判断system_data_backup CRC检验数据是否为0，且判断是否等于system_data_backup存储的CRC数据
		if(s != 0 && s == system_data_backup.crc16)
    	{
    	  //若判断system_data_backup数据正常则将system_data_backup的数据复制到system_data中
    	  memcpy((unsigned char *)&system_data.masking, (unsigned char *)&system_data_backup.masking, SYSTEM_DATA_SIZE);
          //擦除EEPROM中EEPROM_PAGE1_BLOCK中的数据，并判断是否擦除成功
		  if(cm_flash_erase(EEPROM_PAGE0_BLOCK, 1) != 0)
          {
            opencpu_printf("\nErase EEPROM page0 failed!");
          }
		  //将system_data.masking 写入 EEPROM的EEPROM_PAGE1_BASE中，并判断是否写入成功
          if(cm_flash_write((uint32_t)EEPROM_DATA, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) != SYSTEM_DATA_SIZE)
          {
            opencpu_printf("\nWrite EEPROM page0 failed!");
          }
    	}
		//system_data_backup CRC检验数据为0或者system_data_backup CRC检验数据不等于system_data_backup CRC存储的数据则恢复默认设置
    	{
    	  ResetDefaultFactory();
    	}
      }
	  //system_data_backup没有初始化，则恢复默认设置
  	  else
  	  {
  	    ResetDefaultFactory();
  	  }
	}
  }

  //system_data没有初始化，则检查system_data_backup初始化
  else
  {
  	if(system_data_backup.initialize_flag == EEPROM_INITIALIZE_FLAG)
    {
      //system_data_backup已经初始化则对system_data_backup数据进行CRC校验
      s = CalculateCRC_CCITT((unsigned char *)&system_data_backup.masking, (SYSTEM_DATA_SIZE - 8));
  	  if(s != 0 && s == system_data_backup.crc16)
  	  {
  	    //如果system_data_backup CRC校验数据不为0且等于system_data_backup存储的CRC数据，则将system_data_backup的数据复制到system_data中
  		memcpy((unsigned char *)&system_data.masking, (unsigned char *)&system_data_backup.masking, SYSTEM_DATA_SIZE);
        //擦除EEPROM中EEPROM_PAGE1_BLOCK中的数据，并判断是否擦除成功
		if(cm_flash_erase(EEPROM_PAGE0_BLOCK, 1) != 0)
        {
          opencpu_printf("\nErase EEPROM page0 failed!");
        }
		//将system_data.masking 写入 EEPROM的EEPROM_PAGE1_BASE中，并判断是否写入成功
        if(cm_flash_write((uint32_t)EEPROM_DATA, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) != SYSTEM_DATA_SIZE)
        {
          opencpu_printf("\nWrite EEPROM page0 failed!");
        }
  	  }
	  //如果system_data_backup CRC校验数据为0或者不等于system_data_backup存储的CRC数据，则将恢复默认设置
  	  else
  	  {
  		  ResetDefaultFactory();
  	  }
    }
	//如果system_data_backup没有初始化，则将恢复默认设置
  	else
  	{
  	  ResetDefaultFactory();
  	}
  }
}

/*----------------------------------------------------------------------------------------------------*/
/*
** Write System Data
*/
void WriteSystemData(void)
{
  int i;

  i = 3;
  do{
  	if(cm_flash_erase(EEPROM_PAGE0_BLOCK, 1) == 0)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  if(i == 0)
    opencpu_printf("\nErase EEPROM page0 failed!");
#endif
  i = 3;
  do{
  	if(cm_flash_write((uint32_t)EEPROM_DATA, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) == SYSTEM_DATA_SIZE)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  if(i == 0)
  	opencpu_printf("\nWrite EEPROM page0 failed!");
#endif
  i = 3;
  do{
  	if(cm_flash_erase(EEPROM_PAGE1_BLOCK, 1) == 0)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE  
  if(i == 0)
    opencpu_printf("\nErase EEPROM page1 failed!");
#endif  
  i = 3;
  do{
  	if(cm_flash_write((uint32_t)EEPROM_DATA_BACKUP, (unsigned char *)&system_data.masking, SYSTEM_DATA_SIZE) == SYSTEM_DATA_SIZE)
	  break;
	osDelay(1000);
  }while(--i);
#ifdef _OPENCPU_DEBUG_OUTPUT_MODE
  if(i == 0)
    opencpu_printf("\nWrite EEPROM page1 failed!");
#endif
}  

/*----------------------------------------------------------------------------------------------------*/
/*
** Save System Data
*/
void SaveSystemData(void)
{
  unsigned int i;
  i = CalculateCRC_CCITT((unsigned char *)&system_data.masking, (SYSTEM_DATA_SIZE - 8));
  if(system_data.initialize_flag != EEPROM_INITIALIZE_FLAG || i != system_data.crc16)
  {
    system_data.crc16 = i;
    system_data.initialize_flag = EEPROM_INITIALIZE_FLAG;
	WriteSystemData();
  }  
}
/*
** Get Service Provider
** 描   述: 获得移动服务商
** 返回值:
          1:中国移动 CMCC
          2:中国电信 CTCC
          3:中国联通 CUCC
*/
int Get_Service_Provider(void)
{
  unsigned char icc_id[8];
  
  memcpy(icc_id, system_data.ICCID, 6);
  icc_id[6] = '\0';
  
  if(strcmp(icc_id, "898600") == 0)
    return CMCC;

  if(strcmp(icc_id, "898602") == 0)
    return CMCC;

  if(strcmp(icc_id, "898604") == 0)
    return CMCC;

  if(strcmp(icc_id, "898607") == 0)
    return CMCC;

  if(strcmp(icc_id, "898608") == 0)
    return CMCC;

  if(strcmp(icc_id, "898601") == 0)
    return CUCC;
  
  if(strcmp(icc_id, "898606") == 0)
    return CUCC;
  
  if(strcmp(icc_id, "898609") == 0)
    return CUCC;
    
  if(strcmp(icc_id, "898603") == 0)
    return CTCC;
  
  if(strcmp(icc_id, "898611") == 0)
    return CTCC;
    
  return 0;
}
/*----------------------------------------------------------------------------------------------------*/


