/**
 *  @file    cm_ota.h
 *  @brief   通用ota接口
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/7/2
 *  @date 2021/7/8 by zxw，规范OTA接口
 */


#ifndef __CM_OTA_H__
#define __CM_OTA_H__


/** @defgroup OTA ota
 * 差分升级接口
 * @ingroup SYS
 * @{
 * */


/**
 *  @brief 通用OTA升级初始化
 *  
 *  @return 
 *   =  0 - 成功 \n
 *   <  0 - 失败
 *  
 */
int32_t cm_ota_init(void);

/**
 *  @brief 查询用于升级的文件系统或flash空间大小
 *  
 *  @return 
 *   >= 0 - 空间大小 \n
 *   <  0 - 失败
 *  
 */
int32_t cm_ota_get_capacity(void);

/**
 *  @brief 通用OTA升级，保存升级包至文件系统或flash
 *  
 *  @param [in] buffer  下载固件包数据
 *  @param [in] size    下载固件包长度
 *  @return 
 *   =  0 - 成功 \n
 *   <  0 - 失败
 *  
 *  @details 用户自行维护偏移量，保证数据写入正确
 */
int32_t cm_ota_firmware_write(char* buffer, int size);

/**
 *  @brief 查询已写入文件系统或flash中的升级包大小
 *  
 *  @return 
 *   >=  0 - 已写入文件系统或flash中的升级包大小 \n
 *   <   0 - 失败
 *  
 */
int32_t cm_ota_get_written_size(void);

/**
 *  @brief 擦除已写入文件系统或flash中的升级包
 *  
 *  @return 
 *   =  0 - 成功 \n
 *   <  0 - 失败
 *  
 */
int32_t cm_ota_firmware_erase(void);

/**
 *  @brief 触发升级
 *  
 *  @return 
 *   =  0 - 成功 \n
 *   <  0 - 失败
 *  
 *  @details 须在写入升级包操作后执行
 */
int32_t cm_ota_upgrade(void);


/*
流程：
step1: cm_ota_init();
step2: cm_ota_firmware_write();
step3: cm_ota_upgrade();
*/


/** @} end of group DRV_FOTA */

#endif
