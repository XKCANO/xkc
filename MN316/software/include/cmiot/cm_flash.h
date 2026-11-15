/**
 * @file        cm_flash.h
 * @brief       FLASH驱动接口实现
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By tw
 * @date        2021/05/18
 *  
 * @defgroup flash flash
 * @ingroup PI
 * @{
 */


#ifndef __CM_FLASH_H__
#define __CM_FLASH_H__


/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>



/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/
/** flash信息 */
typedef struct
{
    uint32_t block_amount;/*!< 块（最小可擦除单元）总数（用户空间中的flash块总数） */
    uint32_t block_size;/*!< 单个块（最小可擦除单元）的大小 */
} cm_flash_info_t;

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
 *  @brief 获取flash信息
 *
 *  @param [out] flash_info   flash信息
 *
 *  @return 
 *   =  0 - 成功 \n
 *   = -1 - 失败
 *
 *  @details More details
 */
int32_t cm_flash_info(cm_flash_info_t *flash_info);

/**
 *  @brief flash写数据
 *  
 *  @param [in] addr 写数据地址（相对地址）
 *  @param [in] buf  写数据指针
 *  @param [in] size 写数据长度（写入数据长度不可超出flash空间，超出时接口不执行写入操作返回-1）
 *
 *  @return 
 *   >=  0 - 实际写入长度 \n
 *   =  -1 - 失败
 *  
 *  @details 写入范围0-0x10000共计64KB, 不需擦除，可直接写入
 */
int32_t cm_flash_write(uint32_t addr, const void *buf, uint32_t size);

/**
 *  @brief flash读数据
 *  
 *  @param [in]  addr 读数据地址（相对地址）
 *  @param [out] buf  读数据指针
 *  @param [in]  size 读数据长度（读数据长度若超出flash空间，仅读取flash空间范围内的数据）
 *
 *  @return 
 *   >= 0 - 读数据长度 \n
 *   = -1 - 失败
 *  
 *  @details 范围0-0x10000共计64KB,
 */
int32_t cm_flash_read(uint32_t addr, void *buf, uint32_t size);

/**
 *  @brief flash擦除（擦除从block开始的count块flash空间）
 *  
 *  @param [in] block 擦除的块（最小可擦除单元）序号
 *  @param [in] count 擦除的块（最小可擦除单元）数量
 *
 *  @return 
 *   =  0 - 成功 \n
 *   = -1 - 失败
 *  
 *  @details 块（最小可擦除单元）总数n由cm_flash_info()接口获取，块序号范围为1~n（块总数）
 */
int32_t cm_flash_erase(uint32_t block, uint32_t count);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_FLASH_H__ */

/** @}*/