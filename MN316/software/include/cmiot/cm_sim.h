/**
 * @file        cm_sim.h
 * @brief       SIM接口
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By ljw
 * @date        2021/05/28
 *
 * @defgroup sim sim
 * @ingroup PHONE
 * @{
 */

#ifndef __CM_SIM_H__
#define __CM_SIM_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define CM_IMSI_LEN       16 /** IMSI存储长度 */
#define CM_ICCID_LEN      21 /** ICCID存储长度 */

/****************************************************************************
 * Public Types
 ****************************************************************************/


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
 * @brief 获取SIM卡状态
 * 
 * @return 
 *   >= 0  - SIM卡状态码，0:READY, 1:SIM PIN, 2:SIM PUK \n
 *   < 0   - 失败, 返回值为错误码 
 *  
 * @details More details
 */
int32_t cm_sim_get_cpin(void);

/**
 * @brief 获取IMSI
 * 
 * @param [out] imsi IMSI，长度16字节
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 * 
 * @details More details
 */
int32_t cm_sim_get_imsi(char* imsi);

/**
 * @brief 获取ICCID
 * 
 * @param [out] iccid ICCID，长度21字节
 * 
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 * 
 * @details More details
 */
int32_t cm_sim_get_iccid(char* iccid);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_SIM_H__ */

/** @}*/
