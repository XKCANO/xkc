/**
 * @file         cm_cyclequeue.h
 * @brief        杂项功能函数
 * @copyright    Copyright © 2021 China Mobile IOT. All rights reserved.
 * @author       By WK,XGL
 * @date         2021/08/31
 *
 * @defgroup cyclequeue cyclequeue
 * @ingroup PI
 * @{
 */

#ifndef __CM_CYCLEQUEUE_H__
#define __CM_CYCLEQUEUE_H__

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

/**cycle queue 对象*/
typedef struct {
	uint8_t *pu8Buf; 		/*!< 队列缓冲区*/
	uint32_t u32Capacity;   /*!< 队列容量(字节)*/
	uint32_t u32Head; 		/*!< 队列头部索引*/
	uint32_t u32Tail; 		/*!<队列尾部索引*/
	uint32_t u32Len; 		/*!< 当前数据长度*/
} cm_cyclequeue_t;

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
 * @brief 创建cycle queue
 *
 * @param [in]  ptCycleQueue    cm_cyclequeue_t结构体指针
 * @param [in]   pu8Buf          数据buffer指针  		   
 * @param [in]   u32BufLen       数据buffer长度，必须为2^n,由用户保证
 *
 * @return  
 *   空
 *
 * @details 数据buffer由调用者自行分配，避免动态内存申请
 */
void cm_cyclequeue_create(cm_cyclequeue_t* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen);
/**
 * @brief 释放cycle queue
 *
 * @param [in]  ptCycleQueue   cm_cyclequeue_t结构体指针
 *
 * @return  
 *   空
 *
 * @details 
 */
void cm_cyclequeue_release(cm_cyclequeue_t* ptCycleQueue);

/**
 * @brief 清空cycle queue
 *
 * @param [in]  ptCycleQueue   cm_cyclequeue_t结构体指针
 *
 * @return  
 *   空
 *
 * @details 
 */
void cm_cyclequeue_clean(cm_cyclequeue_t* ptCycleQueue);
/**
 * @brief 插入数据到cycle queue头部
 *
 * @param [in] ptCycleQueue    cm_cyclequeue_t结构体指针
 * @param [in]  pcu8Data       待插入的数据
 * @param [in]  u32DataLen     待插入的数据长度(字节数)
 *
 * @return  
 *   实际插入的长度
 *
 * @details 
 */
uint32_t cm_cyclequeue_insert(cm_cyclequeue_t* ptCycleQueue, const uint8_t* pcu8Data, uint32_t u32DataLen);

/**
 * @brief 从cycle queue尾部读出数据, 已读数据将会从队列删除
 *
 * @param [in] ptCycleQueue    cm_cyclequeue_t结构体指针
 * @param [out]  pu8Buf        用于存放读出数据的缓冲区
 * @param [in]  u32BufLen      待插入的数据长度(字节数)
 * @param [in]  pu32RemainLen  待插入的数据长度(字节数)
 *
 * @return  
 *   实际读取的字节数
 *
 * @details 
 */
uint32_t cm_cyclequeue_delete(cm_cyclequeue_t* ptCycleQueue, uint8_t* pu8Buf, uint32_t u32BufLen, uint32_t* pu32RemainLen);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_CYCLEQUEUE_H__ */

/** @}*/

