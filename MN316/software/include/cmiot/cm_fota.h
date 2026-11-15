/**
 *  @file    cm_fota.h
 *  @brief   远程升级fota接口
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by WangPeng
 *  @date 2021/10/20
 */


#ifndef __CM_FOTA_H__
#define __CM_FOTA_H__


/** @defgroup FOTA fota
 * 差分升级接口
 * @ingroup SYS
 * @{
 * */

/**
 *  @brief 获取（OneNET LWM2M/CTWing）FOTA版本号，长度16字符以内，仅支持数字、字母、‘.’、‘_’
 *  
 *  @param [out] version 版本号
 *  @return None
 *  
 *  @details 此函数由用户实现,切勿更改函数声明，将用户版本号拷贝至version内存中，版本号设置必须与OneNET/CTWing平台一致
 */
void cm_fota_get_version(char version[]) __attribute__((weak)) ;


/**
 *  @brief 未连接平台前，用户注册（OneNET LWM2M）FOTA通知事件（连接平台后，cm_onenet_create()被调用后，该注册的函数被cm_onenet_create()注册的函数替换）
 *         FOTA完成后模组会重启，重启后会将FOTA升级成功或失败的状态通知至应用，此操作在驻网之前即会完成，应用层析若需接收相关事件通知，需在此接口中调用cm_onenet_event_register()完成回调函数注册
 *         在OpenCPU入口函数cm_opencpu_entry()返回后  ，系统即会调用  user_onenet_event_register()接口
 *  
 *  @return None
 *  
 *  @details 此函数由用户实现,切勿更改函数声明
 */
void user_onenet_event_register(void) __attribute__((weak)) ;


/** @} end of group DRV_FOTA */

#endif
