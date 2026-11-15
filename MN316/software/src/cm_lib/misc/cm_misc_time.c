/*********************************************************
*  @file    cm_misc_crc.c
*  @brief   CRC工具函数
*  Copyright (c) 2021 China Mobile IOT.
*  All rights reserved.
*  created by XGL 2021/08/30
********************************************************/

/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"
#include "cm_misc.h"

/*----------------------------------------------------------------------------*
**                             Debugging Flag                                 *
**----------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/
#define SECOND_OF_DAY (24*60*60)
static const char DayOfMon[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/

void cm_sec_to_date(long lSec, cm_tm_t *tTime)
{
  unsigned short i,j,iDay;
  unsigned long lDay;
 
  lDay = lSec / SECOND_OF_DAY;    
  lSec = lSec % SECOND_OF_DAY;
 
  i = 1970;
  while(lDay > 365)
  {
   if(((i%4==0)&&(i%100!=0)) || (i%400==0)) 
    lDay -= 366;
   else
    lDay -= 365;
   i++;
  }
  if((lDay == 365) && !(((i%4==0)&&(i%100!=0)) || (i%400==0))) 
  {
   lDay -= 365;
   i++;
  }
  tTime->tm_year = i;   
  for(j=0;j<12;j++)   
  {
   if((j==1) && (((i%4==0)&&(i%100!=0)) || (i%400==0)))
    iDay = 29;
   else
    iDay = DayOfMon[j];
   if(lDay >= iDay) lDay -= iDay;
   else break;
  }
  tTime->tm_mon = j+1;
  tTime->tm_mday = lDay+1;
  tTime->tm_hour = ((lSec / 3600))%24;//这里注意，世界时间已经加上北京时间差8，
  tTime->tm_min = (lSec % 3600) / 60;
  tTime->tm_sec = (lSec % 3600) % 60;
}

long cm_date_to_sec(cm_tm_t *date_time)
{
	unsigned short iYear, iMon, iDay, iHour, iMin, iSec;
  iYear = date_time->tm_year;
  iMon = date_time->tm_mon;
  iDay = date_time->tm_mday;
  iHour = date_time->tm_hour;
  iMin = date_time->tm_min;
  iSec = date_time->tm_sec;
 
  unsigned short i, Cyear=0;
  unsigned long CountDay=0;
 
  for(i=1970; i<iYear; i++)   
  {
    if(((i%4==0) && (i%100!=0)) || (i%400==0)) Cyear++;
  }
  CountDay = Cyear * 366 + (iYear-1970-Cyear) * 365;
  for(i=1; i<iMon; i++)
  {
    if((i==2) && (((iYear%4==0)&&(iYear%100!=0)) || (iYear%400==0)))
      CountDay += 29;
    else
      CountDay += DayOfMon[i-1];
  }
  CountDay += (iDay-1);
 
  CountDay = CountDay*SECOND_OF_DAY + (unsigned long)iHour*3600 + (unsigned long)iMin*60 + iSec;
  return CountDay;
}

uint8_t cm_time_to_weekday(cm_tm_t *t)
{
  uint32_t u32WeekDay = 0;
  uint32_t u32Year = t->tm_year;
  uint8_t u8Month = t->tm_mon;
  uint8_t u8Day = t->tm_mday;
  if(u8Month < 3U)
  {
    /*D = { [(23 x month) / 9] + day + 4 + year + [(year - 1) / 4] - [(year - 1) / 100] + [(year - 1) / 400] } mod 7*/
    u32WeekDay = (((23U * u8Month) / 9U) + u8Day + 4U + u32Year + ((u32Year - 1U) / 4U) - ((u32Year - 1U) / 100U) + ((u32Year - 1U) / 400U)) % 7U;
  }
  else
  {
    /*D = { [(23 x month) / 9] + day + 4 + year + [year / 4] - [year / 100] + [year / 400] - 2 } mod 7*/
    u32WeekDay = (((23U * u8Month) / 9U) + u8Day + 4U + u32Year + (u32Year / 4U) - (u32Year / 100U) + (u32Year / 400U) - 2U ) % 7U;
  }

	if (0U == u32WeekDay)
	{
		u32WeekDay = 7U;
	}
	
  return (uint8_t)u32WeekDay;
}
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif


//End of cm_misc_crc.c
