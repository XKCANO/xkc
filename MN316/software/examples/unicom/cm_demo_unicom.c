/**
 *  @file    cm_demo_unicom.c
 *  @brief   OpenCPU UNICOM相关测试例程
 *  @copyright copyright © 2022 China Mobile IOT. All rights reserved.
 *  @author by shimingrui
 *  @date 2022/05/19
 */

 

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include "cm_unicom.h"
#include "cm_sys.h"
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

 
/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int is_ref = 0;//是否注册

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
            cm_demo_printf("unicom register ok\n");
        }
        break;
        case CM_CIS_EVENT_REG_FAILED:
        {
            is_ref = 0;
            cm_demo_printf("unicom register fail\n");
        }
        break;
        case CM_CIS_EVENT_UNREG_DONE:
        {
            is_ref = 0;
            cm_demo_printf("unicom unregister done\n");
        }
        break;

        default:
        break;
    }
    
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

    if (3200 == objid && 0 == insid && 5503 == resid)
    {
        cm_unicom_read(mid, objid, insid, resid, 3, "100", 1);//返回表示该操作结果数据,示例资源类型为int型
    }
    else
    {
        cm_unicom_read(mid, objid, insid, resid, 3, "10", 1);//返回表示该操作结果数据,示例资源类型为int型
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
    cm_unicom_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
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
    cm_unicom_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
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
    if(objid == 3200)
    {
        cm_unicom_discover(mid, 9, "5501;5504");//返回将用到的资源列表
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
    cm_unicom_result(mid, CM_RESULT_205_CONTENT, 1);//操作正确完成返回205
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
    cm_unicom_result(mid, CM_RESULT_204_CHANGED, 0);//操作正确完成返回204
}


/**
 *  
 *  登陆unicom平台                                          CM:UNICOM:CHECKIN
 *  登出unicom平台                                          CM:UNICOM:CHECKOUT
 *  更新保活                                                CM:UNICOM:UPDATE
 *
 */
void cm_test_unicom(unsigned char **cmd, int len)
{
    char operation[20] = {0};
    sprintf(operation, "%s", cmd[2]);

    if (0 == strcmp(operation, "CHECKIN"))
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
        

        /* 常用连接示例如下，若地址发生变化，请自行查找正确地址 */
        //cm_unicom_create("dmp-coap.cuiot.cn:5683", 0, &callback);//创建设备
        //cm_unicom_create("153.35.119.75", 0, &callback);//创建设备
        //cm_unicom_create("2408:873D:2810:C:1::8", 0, &callback);//创建设备
        //cm_unicom_create("[2408:873D:2810:C:1::8]:5683", 0, &callback);//创建设备
        if(!(cm_unicom_create("153.35.119.75:5683", 0, &callback)))//创建设备
        {
            cm_unicom_init();//初始化任务
        }else{
            cm_demo_printf("unicom err\n");
            return;
        }
        
        cm_unicom_add_obj(3200, 1, (unsigned char*)"1", 0, 0);
        cm_unicom_discover(3200, 4, "5503");
        cm_unicom_open(30, 3000);
        cm_demo_printf("open unicom\n");

        while(!is_ref)
        {
            osDelay(100);//休眠
        }
        
        osDelay(5000);//休眠
        cm_unicom_notify(3200, 0, 5503, 3, "50", 1, 1, 0);
        osDelay(500);//休眠
        cm_demo_printf("unicom notify ok\n");
        osDelay(1000);
    }
    else if (0 == strcmp(operation, "CHECKOUT"))
    {
        cm_unicom_close(2);//注销连接
        cm_unicom_del_obj(3200);//释放obj订阅的资源
        cm_unicom_close(4);//清理设备
        cm_demo_printf("close unicom\n");
    }
    else if (0 == strcmp(operation, "UPDATE"))
    {
        cm_unicom_update(3000, 0);
    }
}