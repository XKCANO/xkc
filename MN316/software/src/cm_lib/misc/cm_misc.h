/**
 * @file         cm_misc.h
 * @brief        杂项功能函数
 * @copyright    Copyright © 2021 China Mobile IOT. All rights reserved.
 * @author       By WK,XGL
 * @date         2021/08/31
 *
 * @defgroup misc misc
 * @ingroup PI
 * @{
 */

#ifndef __CM_MISC_H__
#define __CM_MISC_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/
typedef struct cm_tm {
    int tm_sec; /* 秒 – 取值区间为[0,59] */   
    int tm_min; /* 分 - 取值区间为[0,59] */
    int tm_hour; /* 时 - 取值区间为[0,23] */
    int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
    int tm_mon; /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
    int tm_year; /* 年份，其值等于实际年份减去1900 */
}cm_tm_t;


/****************************************************************************
 * Public Data
 ****************************************************************************/


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/**
 * @brief 将bcd码转为字符串
 *
 * @param [in]  pcu8Bcd    BCD码指针
 * @param [in]  u32BcdLen  BCD码长度
 * @param [out] pchStrBuf  存储转换后字符串的缓冲区指针
 * @param [in]  u32BufLen  传入的缓冲区长度
 *
 * @return  
 *   转换后的字符串长度
 *
 * @details 
 */
uint32_t cm_misc_bcd_to_str(const uint8_t* pcu8Bcd, uint32_t u32BcdLen, 
	char* pchStrBuf, uint32_t u32BufLen);
/**
 * @brief 将字符串转为BCD码
 *
 * @param [in]  pcchStr   字符串指针
 * @param [in]  u32StrLen 字符串长度
 * @param [out] pu8BcdBuf 存储转换后BCD码的缓冲区指针
 * @param [in]  u32BufLen 传入的缓冲区长度
 *
 * @return  
 *   转换后的BCD码长度
 *
 * @details 
 */	
uint32_t cm_misc_bcd_from_str(const char* pcchStr, uint32_t u32StrLen, 
	uint8_t* pu8BcdBuf, uint32_t u32BufLen);
/**
 * @brief 将BCD码转为16进制数
 *
 * @param [in]  BCD  BCD码
 *
 * @return  
 *   转换后的16进制值
 *
 * @details 
 */		
uint8_t cm_misc_bcd_to_hex(uint8_t BCD);

/**
 * @brief 将16进制数改为BCD码
 *
 * @param [in]  BCD  BCD码
 *
 * @return  
 *   转换后的16进制值
 *
 * @details 
 */
uint8_t cm_misc_hex_to_bcd(uint8_t HEX);
/**
 * @brief 计算CRC8
 *
 * @param [in]  pcu8Data   要进行CRC8计算的数据指针
 * @param [in]  u32Len     要进行CRC8计算的数据长度
 *
 * @return  
 *   CRC8值
 *
 * @details 生成多项式为G(x)=x^8+x^2+x+1,msb
 */	
uint8_t cm_misc_crc8(const uint8_t* pcu8Data, uint32_t u32Len);

/**
 * @brief 计算CRC16
 *
 * @param [in]  pcu8Data   要进行CRC16计算的数据指针
 * @param [in]  u32Len     要进行CRC16计算的数据长度
 *
 * @return  
 *   CRC16值
 *
 * @details 生成多项式为G(x)=x^16+x^15+x^2+1  ,msb
 */	
uint16_t cm_misc_crc16(const uint8_t* pcu8Data, uint32_t u32Len);

/**
 * @brief 计算CRC32
 *
 * @param [in]  pcu8Data   要进行CRC32计算的数据指针
 * @param [in]  u32Len     要进行CRC32计算的数据长度
 *
 * @return  
 *   CRC32值
 *
 * @details 生成多项式为G(x)=X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X+1  ,msb
 */	
uint32_t cm_misc_crc32(const uint8_t* pcu8Data, uint32_t u32Len);

/**
 * @brief 字符串参数解析
 *
 * @param [in]  resp_line   待解析的字符串
 * @param [in]  resp_expr   用于匹配参数的格式化字符串
 * @param [out] ...         用于接收解析结果的参数
 *
 * @return  
 *	 >= 0  - 解析成功的参数个数
 *   < 0   - 失败
 * @details 
 */	
int32_t cm_misc_str_parse(const char *resp_line, const char *resp_expr, ...);
#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_MISC_H__ */

/** @}*/

