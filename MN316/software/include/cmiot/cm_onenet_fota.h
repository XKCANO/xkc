/**
 *  @file    cm_onenet_fota.h
 *  @brief   OpenCPU onenet FOTA接口
 *  @copyright copyright © 2020 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2020/11/18
 *  @details 保留（OneNET HTTP）FOTA功能出于兼容性考虑，后续将不再升级和维护。对于新增OneNET FOTA功能开发需求的用户建议使用（OneNET LWM2M）FOTA，参考cm_demo_onenet.c
 */


#ifndef __CM_ONENET_FOTA_H__
#define __CM_ONENET_FOTA_H__

/** @defgroup OneNET_FOTA onenet fota
 * OneNET FOTA接口(基于HTTP)
 * @ingroup CC
 * @{
 * */


typedef enum{
    CM_GOTA_NO_ERR = 0,
    CM_GOTA_ERR_INOUT = -1,         /*!< 非法输入输出 */
    CM_GOTA_ERR_STATE = -2,	        /*!< 当前状态执行错误 */
    CM_GOTA_ERR_MEMERY = -3,        /*!< 内存操作错误 */
    CM_GOTA_ERR_NET = -4,  	        /*!< 网络错误 */
    CM_GOTA_ERR_SYSTEM = -5,	    /*!< 系统操作错误 */
}cm_gota_err_e;


/** （OneNET HTTP）Fota升级状态
 *
 * current_step相关说明 \n
 * 1-100 下载百分比 \n
 * 0   FOTA初始化完成 \n
 * 101 FOTA下载并校验完成 \n
 * 102 FOTA升级设备空间不足 \n
 * 103 FOTA操作flash异常，平台显示内存溢出 \n
 * 104 任务流程超时，网络异常或用户未及时响应请求可导致 \n
 * 105 下载时因电量不足而终止 \n
 * 107 任务与平台交互异常，平台显示未知异常 \n
 * 200 开始升级 \n
 * 201 FOTA升级成功 \n
 * 202 升级请求因电量不足而终止 \n
 * 203 FOTA升级时内存错误 \n
 * 204 FOTA升级时版本错误 \n
 * 205 FOTA校验失败 \n
 * 206 设备与平台交互异常，平台显示未知异常 \n
 * 207 固件验签错误，平台显示达到最大重试次数 \n
 * 208 设备无法申请升级，平台显示设备升级过期 \n
 */
typedef struct{
    int total_size;             /*!< 升级包总长度*/
    int current_size;           /*!< 当前接收到的升级包长度*/
    int current_step;           /*!< 下载进度，百分比*/
}cm_gota_state_t;


/**
 *  @brief （OneNET HTTP）FOTA升级状态回调函数，在升级状态变化时触发调用，请勿长时间阻塞
 *  
 *  @param [in] state 当前升级状态
 *  @return None
 *  
 *  @details 升级状态为字符串格式，包含5种类型: \n
 *  1、+MFOTATASK:<res>[,<power>,<total>] \n
 *      res=0   任务获取成功 \n
 *      res=1   鉴权失败(当设备不存在时) \n
 *      res=2   请求参数错误 \n
 *      res=7   OneNET内部错误 \n
 *      res=8   检测失败，任务存在，但manuf或者model不一致 \n
 *      res=9   检测失败，任务存在，但version不一致 \n
 *      res=11  设备不存在对应的升级任务 \n
 *      res=27  版本号格式错误 \n
 *      power:电量百分比，1-100 \n
 *      total:升级包长度 \n
 *  2、+MFOTAIND:<res> \n
 *      res说明参考cm_gota_state_t结构体中的current_step>100部分说明 \n
 *  3、+MFOTADL:<res>,<current>,<total> \n
 *      res:下载进度1-100 \n
 *      current:已下载固件包长度 \n
 *      total:总固件包长度 \n
 *  4、+MFOTADATA:<res> \n
 *      res=1   未找到有效文件包 \n
 *      res=2   获取文件包大小与目标文件包大小不一致 \n
 *      res=3   获取文件包任务身份失效 \n
 *      res=4   获取文件包失败 \n
 *      res=5   请求参数错误 \n
 *      res=6   NB基站限制 \n
 *  5、+MFOTAEND:<res> \n
 *      res=0  删除FOTA任务 \n
 *      res=1  暂停任务 \n
 */
typedef void(*cm_gota_cb)(char* state);


/**
 *  @brief 配置产品ID和秘钥
 *  
 *  @param [in] pid 产品ID
 *  @param [in] pkey 安全鉴权秘钥access_key
 *  @return 见cm_gota_err_e枚举
 *  
 *  @details 不支持ipv6单栈下使用该接口
 */
int cm_gota_configure(char* pid, char* pkey);


/**
 *  @brief 启动（OneNET HTTP）FOTA升级任务
 *  
 *  @return 见cm_gota_err_e枚举
 *  
 *  @details 不支持ipv6单栈下使用该接口；保留（OneNET HTTP）FOTA功能出于兼容性考虑，后续将不再升级和维护。对于新增OneNET FOTA功能开发需求的用户建议使用（OneNET LWM2M）FOTA，参考cm_demo_onenet.c
 */
int cm_gota_start(void);


/**
 *  @brief 停止（OneNET HTTP）FOTA升级任务
 *  
 *  @return 见cm_gota_err_e枚举
 *  
 *  @details 不支持ipv6单栈下使用该接口
 */
int cm_gota_stop(void);


/**
 *  @brief 设置（OneNET HTTP）FOTA升级回调，在FOTA升级状态变化时将会触发回调函数执行
 *  
 *  @param [in] cb 回调函数
 *  @return 见cm_gota_err_e枚举
 *  
 *  @details 请在FOTA升级启动前设置，暂不支持ipv6单栈下使用该接口
 */
void cm_gota_set_cb(cm_gota_cb cb);


/**
 *  @brief 获取（OneNET HTTP）FOTA升级状态
 *  
 *  @param [out] state 升级状态
 *  @return 见cm_gota_err_e枚举
 *  
 *  @details 不支持ipv6单栈下使用该接口
 */
int cm_gota_get_state(cm_gota_state_t* state);


/**
 *  @brief 获取（OneNET HTTP）FOTA版本号，长度16字符以内，仅支持数字、字母、‘.’、‘_’
 *  
 *  @param [out] version 版本号
 *  @return None
 *  
 *  @details 此函数由用户实现,切勿更改函数声明，将用户版本号拷贝至version内存中，版本号设置必须与OneNET平台一致
 */
void cm_gota_get_version(char version[]) __attribute__((weak)) ;


/** @} end of group OneNET_FOTA*/

#endif

