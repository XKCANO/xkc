/**
 *  @file    cm_demo_onenet.c
 *  @brief   OpenCPU ONENET相关测试例程
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by WangPeng
 *  @date 2021/10/15
 */

 

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include "cm_onenet.h"
#include "cm_sys.h"
//#include "cm_fota.h"
#include "cm_demo_common.h"
#include "stdio.h"
#include "string.h"
#include "cm_os.h"
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Data
 ****************************************************************************/
 static const char user_ver[] = "V1.0.0";
 
/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int is_ref = 0;//是否注册


/**
 *  \brief FOTA版本号获取，版本号仅支持数字、字母、‘.’、‘_’，长度≤16字节
 *  
 *  \param [out] version 版本号
 *  \return None
 *  
 *  \details 此函数原型在静态库中为弱引用，用户在进行fota升级时定义为强引用，并自行添加版本号
 */
void cm_fota_get_version(char version[])
{
    if(version == NULL)
    {
        return;
    }

    memcpy(version, user_ver, sizeof(user_ver));
}

/**
 *  \brief 状态事件上报
 *  
 *  \param [in] event 事件
 *  \return None
 *  
 *  \details More details
 */
static void cot_event_cb(int event)
{
    cm_demo_printf("event:%d\n",event);
    switch(event)
    {
        case CM_CIS_EVENT_REG_SUCCESS: 
        {
            is_ref = 1;
            cm_demo_printf("onenet register ok\n");
        }
        break;
        case CM_CIS_EVENT_REG_FAILED:
        {
            is_ref = 0;
            cm_demo_printf("onenet register fail\n");
        }
        break;
        case CM_CIS_EVENT_UNREG_DONE:
        {
            is_ref = 0;
            cm_demo_printf("onenet unregister done\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_DOWNLOADING:
        {
            cm_demo_printf("onenet fota downloading\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_DOWNLOADED:
        {
            cm_demo_printf("onenet fota downloaded\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_UPDATING:
        {
            cm_demo_printf("onenet fota updating\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_UPDATE_SUCCESS:
        {
        	/* 系统在开机时通知该事件，该时刻uart不能保证初始化完成，故demo从log口打印该消息 */
            cm_log_printf(0, "onenet fota update success\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_UPDATE_FAILED:
        {
        	/* 系统在开机时通知该事件，该时刻uart不能保证初始化完成，故demo从log口打印该消息 */
            cm_log_printf(0, "onenet fota update fail\n");
        }
        break;
        case CM_CIS_EVENT_FIRMWARE_UPDATE_OVER:
        {
            cm_demo_printf("onenet fota update over\n");
        }
        break;
        default:
        break;
    }
    
}

/**
 *  @brief 用户注册OneNET FOTA通知事件（未连接平台前，连接平台后该注册的函数失效）
 *  
 *  @return None
 *  
 *  @details 此函数由用户实现,切勿更改函数声明
 */
void user_onenet_event_register(void)
{
    cm_onenet_event_register(cot_event_cb);
}

/**
 *  \brief notify上报回调函数
 *  
 *  \param [in] ack_id notify的ack_id
 *  \return None
 *  
 *  \details 用户自行实现
 */
static void cot_notify_cb(int ack_id)
{
    //TODO
    cm_demo_printf("ack_id:%d\n",ack_id);
}


/**
 *  \brief 平台read操作正确回调函数，需用户实现
 *
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \param [in] insid 被操作的instance ID
 *  \param [in] resid 被操作的resource ID
 *  \return None
 *
 */
static void cot_read_cb(int mid, int objid, int insid, int resid)
{
    //TODO
    //...
    (void)objid;
    (void)insid;
    (void)resid;
    //根据传入的objid_insid_resid决定需上传的数据
    cm_demo_printf("mid:%d objid:%d insid:%d resid:%d\n",mid, objid, insid, resid);

    if (3 == objid && 0 == insid && 9 == resid)
    {
        //OneNET FOTA平台在发起下载升级包和发起升级指令前会获取设备电量信息，此为反馈平台当前电量为100%
        cm_onenet_read(mid, objid, insid, resid, 3, "100", 1);//返回表示该操作结果数据,示例资源类型为int型
    }
    else
    {
        cm_onenet_read(mid, objid, insid, resid, 3, "10", 1);//返回表示该操作结果数据,示例资源类型为int型
    }
}


/**
 *  \brief 平台write操作回调函数，需用户实现
 *  
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \param [in] insid 被操作的instance ID
 *  \param [in] resid 被操作的resource ID
 *  \param [in] type 写资源的类型，如该资源未曾被notify或read，皆作opaque类型处理
 *  \param [in] flag 多条写指令上报时消息标识 1、第一条消息； 2、中间消息； 0、最后一条消息
 *  \param [in] len 数据长度
 *  \param [in] data 被写入的数据
 *  \return None
 *  
 *  \details More details
 */
static void cot_write_cb(int mid, int objid, int insid, int resid, int type, int flag, int len, char *data)
{
    //TODO
    //...
    (void)objid;
    (void)insid;
    (void)resid;
    (void)resid;
    (void)type;
    (void)flag;
    (void)len;
    (void)data;
    cm_demo_printf("objid:%d insid:%d resid:%d type:%d flag:%d len:%d data:%s\n",objid,insid,resid,type,flag,len,data);
    cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
}


/**
 *  \brief 平台excute操作回调函数，需用户实现
 *  
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \param [in] insid 被操作的instance ID
 *  \param [in] resid 被操作的resource ID
 *  \param [in] len 数据长度
 *  \param [in] data 被写入的数据
 *  \return None
 *  
 *  \details More details
 */
static void cot_execute_cb(int mid, int objid, int insid, int resid, int len, char *data)
{
    //TODO
    //...
    (void)objid;
    (void)insid;
    (void)resid;
    (void)len;
    (void)data;
    cm_demo_printf("mid:%d objid:%d insid:%d resid:%d len:%d len:%s\n",mid, objid, insid, resid, len, data);
    cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
}


/**
 *  \brief 平台discover操作回调函数，需用户实现
 *  
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \return None
 *  
 *  \details More details
 */
static void cot_discover_cb(int mid, int objid)
{
    //TODO
    //...
    cm_demo_printf("discover mid:%d objid:%d \n", mid, objid);
    if(objid == 3303)
    {
        cm_onenet_discover(mid, 9, "5700;5601");//返回将用到的资源列表
    }
    else if(objid == 3306)
    {
        cm_onenet_discover(mid, 9, "5852;5853");//返回将用到的资源列表
    }
}


/**
 *  \brief 平台observe操作回调函数，需用户实现
 *  
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \param [in] insid 被操作的instance ID
 *  \param [in] resid 被操作的resource ID
 *  \return None
 *  
 *  \details More details
 */
static void cot_observe_cb(int mid, int observe, int objid, int insid, int resid)
{
    //TODO
    //...
    cm_demo_printf("%d_%d_%d: %d\n", objid, insid, resid, observe);
    cm_onenet_result(mid, CM_RESULT_205_CONTENT, 1);//操作正确完成返回204
}


/**
 *  \brief 平台设置策略参数请求回调函数，需用户实现
 *  
 *  \param [in] mid 操作消息的ID
 *  \param [in] objid 被操作的object ID
 *  \param [in] insid 被操作的instance ID
 *  \param [in] resid 被操作的resource ID
 *  \param [in] len 数据长度
 *  \param [in] parameter 策略参数，格式如:pmin=xxx; pmax=xxx; gt=xxx; lt=xxx; stp=xxx
 *              pmin: int类型，上传数据的最小时间间隔
 *              pmax: int类型，上传数据的最大时间间隔
 *              gt: double类型，当数据大于该值上传
 *              lt: double类型，当数据小于该值上传
 *              stp:double类型，当两个数据点相差大于或者等于该值上传
 *  \return None
 *  
 *  \details More details
 */
static void cot_parameter_cb(int mid,int objid, int insid, int resid, int len, char *parameter)
{
    //TODO
    //...
    (void)objid;
    (void)insid;
    (void)resid;
    (void)len;
    (void)parameter;
    cm_onenet_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
}


/**
 *  
 *  查看OneNET FOTA版本号                                    CM:ONENET:VERSION
 *  登陆OneNET平台                                          CM:ONENET:CHECKIN
 *  登出OneNET平台                                          CM:ONENET:CHECKOUT
 *
 *  OneNET中含有FOTA功能（使用OneNET LWM2M FOTA，非OneNET HTTP FOTA）
 *  CMIOT不同型号模组OpenCPU SDK提供的OneNET FOTA存在差异（本部分为OneNET LWM2M FOTA），在平台网页端的操作不同，详见OneNET官网
 *  基于20211022 OneNET平台网页，网页端使用OneNET LWM2M FOTA功能操作的路径为“OneNET官网-NB IoT物联网套件-用户创建的产品-OTA升级-FOTA升级”
 *  平台网页完成OneNET LWM2M FOTA配置和任务下发后，模组端连接至平台后会接收到平台端的差分包下载和升级指令，底层会自动进行FOTA升级并将FOTA状态通知上层应用
 *  FOTA升级过程中平台会下发指令获取模组端当前电量，参见本Demo中cot_read_cb()接口实现
 *
 *  推荐使用OneNET LWM2M FOTA，该模块将持续支持与维护
 */
void cm_test_onenet(unsigned char **cmd, int len)
{
    char operation[20] = {0};
    sprintf(operation, "%s", cmd[2]);

    if (0 == strcmp(operation, "VERSION"))
    {
        char version[30] = {0};

        cm_fota_get_version(version);//打印当前版本号
        cm_demo_printf("current ver:%s\n", version);
    }
    else if (0 == strcmp(operation, "CHECKIN"))
    {
        cm_cot_cb_t callback;
        callback.onRead = (cot_read_cb_t)cot_read_cb;
        callback.onWrite = (cot_write_cb_t)cot_write_cb;
        callback.onExec = (cot_execute_cb_t)cot_execute_cb;
        callback.onObserve = (cot_observe_cb_t)cot_observe_cb;
        callback.onParams = (cot_params_cb_t)cot_parameter_cb;
        callback.onEvent = (cot_event_cb_t)cot_event_cb;
        callback.onNotify = (cot_notify_cb_t)cot_notify_cb;
        callback.onDiscover = (cot_discover_cb_t)cot_discover_cb;
        
        cm_onenet_init();//初始化任务

        /* 常用连接示例如下 */
        //cm_onenet_create("183.230.40.39:5683", 1, &callback);//创建设备
        //cm_onenet_create("2409:8060:8ea:601::1864", 0, &callback);//创建设备
        //cm_onenet_create("[2409:8060:8ea:601::1864]:5683", 0, &callback);//创建设备
        //cm_onenet_create("nbiotbt.heclouds.com", 1, &callback);//创建设备
        //cm_onenet_create("nbiotbt.heclouds.com:5683", 1, &callback);//创建设备
        cm_onenet_create("183.230.40.39", 1, &callback);//创建设备
        
        cm_onenet_add_obj(3303, 1, (unsigned char*)"1", 0, 0);
        cm_onenet_add_obj(3306, 1, (unsigned char*)"1", 0, 0);
        cm_onenet_discover(3303, 9, "5700;5601");
        cm_onenet_discover(3306, 9, "5852;5853");
        cm_onenet_open(30, 3000);
        cm_demo_printf("open onenet\n");

        while(!is_ref)
        {
            osDelay(100);//休眠
        }
        
        osDelay(5000);//休眠
        cm_onenet_notify(3303, 0, 5700, 4, "20.8", 1, 1, 0);
        cm_onenet_notify(3306, 0, 5853, 1, "test", 1, 2, 0);
        osDelay(500);//休眠
        cm_demo_printf("onenet notify ok\n");
        osDelay(1000);
    }
    else if (0 == strcmp(operation, "CHECKOUT"))
    {
        cm_onenet_close(2);//注销连接
        cm_onenet_del_obj(3303);//释放obj订阅的资源
        cm_onenet_del_obj(3306);
        cm_onenet_close(4);//清理设备
        cm_demo_printf("close onenet\n");
    }
}