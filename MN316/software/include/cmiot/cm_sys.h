/**
 * @file        cm_sys.h
 * @brief       系统管理
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By ljw
 * @date        2021/05/28
 *
 * @defgroup sys sys
 * @ingroup SYS
 * @{
 */

#ifndef __CM_SYS_H__
#define __CM_SYS_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifndef __RAM_FUNC 
#define __RAM_FUNC __attribute__((section(".ramtext")))
#endif

#define CM_IMEI_LEN      16 /*!< IMEI存储长度 */
#define CM_SN_LEN        32 /*!< SN存储长度 */
#define CM_VER_LEN       64 /*!< 版本号存储长度 */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/** storage状态 */
typedef struct{
    uint32_t flash_total_size;      /*!<flash总量大小 */
    uint32_t flash_allocated;       /*!<flash目前已分配大小 */
    uint32_t flash_remain;          /*!<flash剩余可分配大小 */
    uint32_t ram_total_size;        /*!<ram总量大小 */
    uint32_t ram_allocated;         /*!<ram目前已分配大小 */
    uint32_t ram_remain;            /*!<ram剩余可分配大小 */
    uint32_t data_used;             /*!<DATA已分配大小 */
    uint32_t text_used;             /*!<TEXT已分配大小 */
    uint32_t bss_used;              /*!<BSS已分配大小 */
} cm_storage_stats_t;

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
 * @brief 获取模组IMEI
 * 
 * @param [out] imei IMEI，长度16字节
 * 
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details More details
 */
int32_t cm_sys_get_imei(char *imei); 

/**
 * @brief 获取模组SN
 * 
 * @param [out] sn SN，长度32字节
 * 
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details More details
 */
int32_t cm_sys_get_sn(char *sn); 

/**
 * @brief 获取SDK版本号
 * 
 * @param [out] ver 版本号
 * @param [in] len 版本号长度，单位字节
 * 
 * @return 
 *   >= 0  - 获取到的版本号长度，单位字节 \n
 *   < 0  - 失败, 返回值为错误码
 *  
 * @details More details
 */
int32_t cm_sys_get_cm_ver(char *ver, uint32_t len);

/**
 * @brief 获取SDK基线版本号
 * 
 * @param [out] ver 基线版本号
 * @param [in] len 基线版本号长度，单位字节
 * 
 * @return 
 *   >= 0  - 获取到的版本号长度，单位字节 \n
 *   < 0  - 失败, 返回值为错误码
 * 
 * @details More details
 */
int32_t cm_sys_get_base_ver(char *ver, uint32_t len);

/**
 * @brief 获取目前系统storage状态
 *  
 * @param [out] stats storage状态
 * 
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *
 * @details More details
 */
int32_t cm_sys_get_storage_stats(cm_storage_stats_t *stats);

/**
 * @brief 切换至AT模式
 * 
 * @return 空
 * 
 * @details 执行后将会重启进入AT模式。注意：此AT模式不能用于项目开发，仅提供生产调试
 */
void cm_sys_open_at(void);

/**
 * @brief 打印log信息
 *  
 * @param [in] log_level log等级
 * @param [in] fmt 格式化字符串
 * @param [in] ... 格式化字符串参数
 * 
 * @return 空
 * 
 * @details More details
 */
void cm_log_printf(uint8_t log_level, const char *fmt, ...);

/**
 * @brief 断言
 *  
 * @param [in] a a为false时产生断言
 * @return 空
 *  
 * @details 在接入LOG工具的情况下，将会自动保存断言时刻系统的dump文件
 */
void cm_assert(bool a);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_SYS_H__ */

/** @}*/
