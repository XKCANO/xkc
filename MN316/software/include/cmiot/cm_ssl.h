/**
 * @file        cm_ssl.h
 * @brief       SSL通用API接口
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By YeXiangji
 * @date        2021/8/5
 *
 * @defgroup ssl ssl
 * @ingroup NP
 * @{
 */

#ifndef _CM_SSL_H_
#define _CM_SSL_H_

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/** SSL配置类型 */
typedef enum
{
    CM_SSL_PARAM_VERIFY,           /*!< 设置验证方式, 参数(value): 类型uint8_t, 值为验证方式类型，0无身份验证，1单向验证， 2双向验证. */
	CM_SSL_PARAM_NEGOTIME,         /*!< 设置超时时间, 参数(value): 类型uint16_t, 值为超时时间 */
    CM_SSL_PARAM_CA_CERT,          /*!< 设置CA证书, 参数(value): 类型char*, 值为CA证书字符串指针. */
    CM_SSL_PARAM_CLI_CERT,         /*!< 设置客户端证书, 参数(value): 类型char*, 值为客户端证书字符串指针. */
    CM_SSL_PARAM_CLI_KEY,          /*!< 设置客户端密钥, 参数(value): 类型char*, 值为客户端密钥. */
} cm_ssl_param_type_e;

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
 * @brief 配置SSL参数
 *
 * @param [in] ssl_id   	ssl通道号
 * @param [in] type 		SSL配置项类型
 * @param [in] value 		SSL配置项参数
 *
 * @return 
 *   = 0  - 成功 \n
 *   = -1  - 参数错误
 *	 = -2  - 该通道正在使用
 * @details 设置SSL配置参数
 */
int32_t cm_ssl_setopt(int32_t ssl_id,cm_ssl_param_type_e type,void * value);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_SSL_H__ */

/** @}*/
