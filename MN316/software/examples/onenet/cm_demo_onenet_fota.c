/**
 *  @file    cm_demo_onenet_fota.c
 *  @brief   OpenCPU OneNET FOTA使用示例
 *  @copyright copyright © 2020 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2020/11/19
 */


#include <stdio.h>
#include <string.h>
#include "cm_onenet_fota.h"
#include "cm_demo_common.h"


static const char user_ver[] = "V1.0.0";


/**
 *  \brief （OneNET HTTP）FOTA回调函数，FOTA状态变化时触发
 *  
 *  \param [in] state 参考cm_onenet_fota.h中回调函数说明
 *  \return None
 *  
 *  \details More details
 */
static void onenet_fota_cb(char* state)
{
    cm_demo_printf("%s\n", state);
}


/**
 *  \brief （OneNET HTTP）FOTA版本号获取，版本号仅支持数字、字母、‘.’、‘_’，长度≤16字节
 *  
 *  \param [out] version 版本号
 *  \return None
 *  
 *  \details 此函数原型在静态库中为弱引用，用户在进行fota升级时定义为强引用，并自行添加版本号
 */
void cm_gota_get_version(char version[])
{
    if(version == NULL)
    {
        return;
    }

    memcpy(version, user_ver, sizeof(user_ver));
}


/**
 *  \brief 设置（OneNET HTTP）FOTA升级状态回调函数
 *  
 *  \details More details
 *
 */
void test_onenet_fota_init(void)
{
    cm_gota_set_cb(onenet_fota_cb);
}


/**
 *  启动（OneNET HTTP）FOTA升级任务                                          CM:GOTA
 * 
 *  本方式下使用OneNET HTTP FOTA，非OneNET LWM2M FOTA，该方式下的FOTA升级操作由模组端触发
 *  CMIOT不同型号模组OpenCPU SDK提供的OneNET FOTA存在差异（本部分为OneNET HTTP FOTA），在平台网页端的操作不同，详见OneNET官网
 *  基于20211108 OneNET平台网页，网页端使用OneNET HTTP FOTA功能操作的路径为“OneNET官网-远程升级OTA-FOTA升级”。注意，使用FOTA功能前应先在OneNET HTTP协议接入中添加产品和设备信息。
 *
 *  保留（OneNET HTTP）FOTA功能出于兼容性考虑，后续将不再升级和维护。对于新增OneNET FOTA功能开发需求的用户建议使用（OneNET LWM2M）FOTA，参考cm_demo_onenet.c
 */
void cm_test_onenet_fota(unsigned char **cmd, int len)
{
    
    char version[30] = {0};

    cm_gota_get_version(version);//打印当前版本号
    cm_demo_printf("current ver:%s\n", version);

    cm_gota_configure("466713", "06JnF0s5Pkcj7q4KSs9JrrU6lrpMOjVlQO4jr0G7rXo=");//升级参数配置

    cm_gota_start();//启动升级
}

