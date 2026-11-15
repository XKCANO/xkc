/**
 * @file        cm_mem.h
 * @brief       内存管理
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 * @author      By ljw
 * @date        2021/05/28
 *
 * @defgroup mem mem
 * @ingroup SYS
 * @{
 */

#ifndef __CM_MEM_H__
#define __CM_MEM_H__

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

/** heap状态 */
typedef struct
{
    uint32_t total_size;            /*!<总量大小 */
    uint32_t allocated;             /*!<目前已分配大小 */
    uint32_t free;                  /*!<剩余可分配大小 */
    uint32_t max_continuity_free;   /*!<剩余可分配最大连续块大小 */
    uint32_t allocated_peak;        /*!<历史分配峰值 */
    uint32_t allocated_times;       /*!<历史分配次数 */
    uint32_t free_times;            /*!<历史释放次数 */
} cm_heap_stats_t;

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
 * @brief 获取目前系统heap状态
 *  
 * @param [out] stats heap状态
 *
 * @return 
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *
 * @details More details
 */
int32_t cm_mem_get_heap_stats(cm_heap_stats_t *stats);

/**
 * @brief 申请内存
 *  
 * @param [in] size 申请长度
 *
 * @return 返回内存地址
 *  
 * @details More details
 */
void *cm_malloc(size_t size);

/**
 * @brief 释放内存
 *  
 * @param [in] buf 待释放内存
 *
 * @return 空
 *  
 * @details More details
 */ 
void cm_free(void *ptr);



#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_MEM_H__ */

/** @}*/
