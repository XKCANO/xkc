/*********************************************************
*  @file    cm_misc_bcd.c
*  @brief   BCD码处理工具函数
*  Copyright (c) 2021 China Mobile IOT.
*  All rights reserved.
*  created by WK,XGL 2021/08/30
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

uint32_t cm_misc_bcd_to_str(const uint8_t* pcu8Bcd, uint32_t u32BcdLen, 
	char* pchStrBuf, uint32_t u32BufLen)
{
	uint32_t j = 0;
	uint32_t i = 0;
	if (u32BufLen >= (2 * u32BcdLen + 1))
	{ // 缓冲区空间足够存储? (每字节BCD编码将转换成两字节字符数据,再加上末尾的字符串结束符)
		for (; i < u32BcdLen; ++i)
		{
			// get the high 4 bits
			uint8_t u8Tmp = (pcu8Bcd[i] & 0xF0) >> 4;

			// A -- F
			if(u8Tmp >= 0x0A)
			{
				pchStrBuf[j++] = (u8Tmp - 0x0A) + 'A';
			}
			else // 0 -- 9
			{

				pchStrBuf[j++] = u8Tmp + '0';
			}

			// get the low 4 bits
			u8Tmp = pcu8Bcd[i] & 0x0F;

			// A -- F
			if (u8Tmp >= 0x0A)
			{
				pchStrBuf[j++] = (u8Tmp - 0x0A) + 'A';
			}
			else // 0 -- 9
			{
				pchStrBuf[j++] = u8Tmp + '0';
			}
		}
		pchStrBuf[j] = '\0';
		return j;
	}
	return 0;
}
uint32_t cm_misc_bcd_from_str(const char* pcchStr, uint32_t u32StrLen, 
	uint8_t* pu8BcdBuf, uint32_t u32BufLen)
{
	uint32_t u32BcdLen = ((u32StrLen + 1) / 2);
	uint32_t j = 0;
	uint32_t i = 0;
	if (u32BufLen >= u32BcdLen)
	{ // 缓冲区空间足够存储?
		if (u32StrLen % 2)
		{ // 处理奇数字节数据的特殊情况
			uint8_t u8Char = pcchStr[j++];
			// set the high 4 bits
			pu8BcdBuf[i] = 0xF0;
			// set the low 4 bits
			if(u8Char >= '0' && u8Char <= '9')
			{
				pu8BcdBuf[i] |= (uint8_t)(u8Char - '0');
			}
			else if ((u8Char >= 'A') && (u8Char <= 'F'))
			{
				pu8BcdBuf[i] |= (uint8_t)((u8Char - 'A') + 0x0A);
			}
			else if ((u8Char >= 'a') && (u8Char <= 'f'))
			{
				pu8BcdBuf[i] |= (uint8_t)((u8Char - 'a') + 0x0A);
			}
			else
			{
				return 0;
			}
			i++;
		}

		for (; i < u32BcdLen; ++i)
		{
			// set the high 4 bits
			uint8_t u8Char = pcchStr[j++];
			if(u8Char >= '0' && u8Char <= '9')
			{
				pu8BcdBuf[i] = (uint8_t)((u8Char - '0') << 4);
			}
			else if ((u8Char >= 'A') && (u8Char <= 'F'))
			{
				pu8BcdBuf[i] = (uint8_t)(((u8Char - 'A') + 0x0A) << 4);
			}
			else if ((u8Char >= 'a') && (u8Char <= 'f'))
			{
				pu8BcdBuf[i] = (uint8_t)(((u8Char - 'a') + 0x0A) << 4);
			}
			else
			{
				return 0;
			}

			// set the low 4 bits
			u8Char = pcchStr[j++];
			if(u8Char >= '0' && u8Char <= '9')
			{
				pu8BcdBuf[i] |= (uint8_t)(u8Char - '0');
			}
			else if ((u8Char >= 'A') && (u8Char <= 'F'))
			{
				pu8BcdBuf[i] |= (uint8_t)((u8Char - 'A') + 0x0A);
			}
			else if ((u8Char >= 'a') && (u8Char <= 'f'))
			{
				pu8BcdBuf[i] |= (uint8_t)((u8Char - 'a') + 0x0A);
			}
			else
			{
				return 0;
			}
		}
		return u32BcdLen;
	}
	return 0;
}

uint8_t cm_misc_bcd_to_hex(uint8_t BCD)
{	
	uint8_t tempData;
	
	tempData = (BCD >> 4) * 10 + (BCD & 0x0F);
	return (tempData);
}
uint8_t cm_misc_hex_to_bcd(uint8_t HEX)
{
	uint8_t tempData;
	
	tempData = ((HEX / 10) << 0x04) + (HEX % 10);
	return (tempData);
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif


//End of cm_misc_bcd.c
