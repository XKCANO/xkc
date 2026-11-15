/**
 *  @file    cm_onenet.h
 *  @brief   OpenCPU onenet接口
 *  @copyright copyright ? 2020 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2020/11/03
 */


#ifndef __CM_ONENET_H__
#define __CM_ONENET_H__

enum {
    CM_NBIOT_SUCCESS                = 0x00,
    CM_NBIOT_SYNTAX_ERROR           = 0x62,         //语法，句法错误
    CM_NBIOT_MEMORY_ERROR           = 0X04,         //内存错误或无此资源
    CM_NBIOT_IN_PROGRESS            = 0x63,         //操作不被允许
    CM_NBIOT_PROGRESS_ERROR         = 0X06,         //操作不支持,notify时：无observe权限或未被订阅
    CM_NBIOT_FLOW_CONTROL           = 0x64,         //Uplink Busy
    CM_NBIOT_NOT_REGISTERED         = 0x5A,         //设备未注册
    CM_NBIOT_REGISTEREDORING        = 0x5B,         //设备注册中或已注册
    CM_NBIOT_RESOURE_FAIL           = 0x5C,         //资源操作错误，申请dev时已存在，其他操作资源不存在
    CM_NBIOT_TOKEN_MISSING          = 0x5D,
    CM_NBIOT_NO_OBSERVE             = 0x5E,
    CM_NBIOT_MSG_OUT                = 0x60,
    CM_NBIOT_MSG_BUSY               = 0x61,
};//错误码定义

//操作结果返回码
#define CM_RESULT_000_ERROR                 0
#define CM_RESULT_205_CONTENT               1
#define CM_RESULT_204_CHANGED               2
#define CM_RESULT_400_BADREQUEST            11
#define CM_RESULT_401_UNAUTHORIZED          12
#define CM_RESULT_404_NOTFOUND              13
#define CM_RESULT_405_METHODNOTALLOWED      14
#define CM_RESULT_406_NOTACCEPTABLE         15
#define CM_RESULT_231_CONTINUE              16
#define CM_RESULT_408_REQUESTINCOMPLTETE    17
#define CM_RESULT_413_REQUESTTOOLARGE       18
#define CM_RESULT_415_FORMATUNSUPPORTED     19

//状态事件上报类型
#define CM_CIS_EVENT_BASE               0x00
#define CM_CIS_EVENT_BOOTSTRAP_START    (CM_CIS_EVENT_BASE + 1)
#define CM_CIS_EVENT_BOOTSTRAP_SUCCESS  (CM_CIS_EVENT_BASE + 2)
#define CM_CIS_EVENT_BOOTSTRAP_FAILED   (CM_CIS_EVENT_BASE + 3)
#define CM_CIS_EVENT_CONNECT_SUCCESS    (CM_CIS_EVENT_BASE + 4)
#define CM_CIS_EVENT_CONNECT_FAILED     (CM_CIS_EVENT_BASE + 5)
#define CM_CIS_EVENT_REG_SUCCESS        (CM_CIS_EVENT_BASE + 6)
#define CM_CIS_EVENT_REG_FAILED         (CM_CIS_EVENT_BASE + 7)
#define CM_CIS_EVENT_REG_TIMEOUT        (CM_CIS_EVENT_BASE + 8)
#define CM_CIS_EVENT_LIFETIME_TIMEOUT   (CM_CIS_EVENT_BASE + 9)
#define CM_CIS_EVENT_STATUS_HALT        (CM_CIS_EVENT_BASE + 10)
#define CM_CIS_EVENT_UPDATE_SUCCESS     (CM_CIS_EVENT_BASE + 11)
#define CM_CIS_EVENT_UPDATE_FAILED      (CM_CIS_EVENT_BASE + 12)
#define CM_CIS_EVENT_UPDATE_TIMEOUT     (CM_CIS_EVENT_BASE + 13)
#define CM_CIS_EVENT_UNREG_DONE         (CM_CIS_EVENT_BASE + 15)
#define CM_CIS_EVENT_UNREG_FAILED       (CM_CIS_EVENT_BASE + 16)
#define CM_CIS_EVENT_RESPONSE_FAILED    (CM_CIS_EVENT_BASE + 20)
#define CM_CIS_EVENT_RESPONSE_SUCCESS   (CM_CIS_EVENT_BASE + 21)
#define CM_CIS_EVENT_NOTIFY_FAILED      (CM_CIS_EVENT_BASE + 25)
#define CM_CIS_EVENT_NOTIFY_SUCCESS     (CM_CIS_EVENT_BASE + 26)

#define CM_CIS_EVENT_NO_DEVICE          (CM_CIS_EVENT_BASE + 31)
#define CM_CIS_EVENT_DTLS_NAT           (CM_CIS_EVENT_BASE + 32)

//OneNET FOTA相关事件上报类型
#define CM_CIS_EVENT_FIRMWARE_DOWNLOADING (CM_CIS_EVENT_BASE + 40)         //设备进入下载升级包状态
#define CM_CIS_EVENT_FIRMWARE_DOWNLOAD_FAILED (CM_CIS_EVENT_BASE + 41)     //设备下载升级包失败
#define CM_CIS_EVENT_FIRMWARE_DOWNLOADED (CM_CIS_EVENT_BASE + 42)          //设备下载升级包完成
#define CM_CIS_EVENT_FIRMWARE_UPDATING (CM_CIS_EVENT_BASE + 43)            //设备进入升级状态
#define CM_CIS_EVENT_FIRMWARE_UPDATE_SUCCESS (CM_CIS_EVENT_BASE + 44)      //设备升级成功
#define CM_CIS_EVENT_FIRMWARE_UPDATE_FAILED (CM_CIS_EVENT_BASE + 45)       //设备升级失败
#define CM_CIS_EVENT_FIRMWARE_UPDATE_OVER (CM_CIS_EVENT_BASE + 46)         //设备升级完成
#define CM_CIS_EVENT_FIRMWARE_DOWNLOAD_DISCONNECT (CM_CIS_EVENT_BASE + 47) //设备下载中断
#define CM_CIS_EVENT_FIRMWARE_TRIGGER (CM_CIS_EVENT_BASE + 50)             //设备触发升级流程
#define CM_CIS_EVENT_FIRMWARE_DOWNLOADING_PROGRESS (CM_CIS_EVENT_BASE + 51)//fota下载进度

/**
 * @defgroup ONENET onenet
 * 模组的OneNET功能函数接口，对接平台为中移物联网OneNET平台
 * @ingroup CC
 *@{
 */

/**
 *  @brief OneNET FOTA通知事件（未连接平台前，连接平台后该注册的函数失效）
 *  
 *  @param [out] mid 操作消息的ID
 *
 *  @return None
 *  
 */
typedef void (*cm_onenet_fota_event_cb_t)(int event);

/**
 *  @brief 状态事件上报回调函数，需用户实现
 *  
 *  @param [out] event 状态事件类型，参照状态事件类型定义
 *
 *  @return 无
 *  
 */
typedef void (*cot_event_cb_t)(int event);

/**
 *  @brief notify上报响应回调函数，需用户实现
 *  
 *  @param [out] ack_id notify的
 *
 *  @return 无
 *  
 */
typedef void (*cot_notify_cb_t)  (int ack_id);

/**
 *  @brief 平台read操作回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] objid 被操作的object ID
 *  @param [out] insid 被操作的instance ID
 *  @param [out] resid 被操作的resource ID
 *
 *  @return 无
 *  
 */
typedef void (*cot_read_cb_t)(int mid, int objid, int insid, int resid);

/**
 *  @brief 平台write操作回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] objid 被操作的object ID
 *  @param [out] insid 被操作的instance ID
 *  @param [out] resid 被操作的resource ID
 *  @param [out] type  写资源的类型，如该资源未曾被notify或read，皆作opaque类型处理
 *  @param [out] flag  多条写指令上报时消息标识 1、第一条消息； 2、中间消息； 0、最后一条消息
 *  @param [out] len   数据长度
 *  @param [out] data 被写入的数据
 *
 *  @return 无
 *  
 */
typedef void (*cot_write_cb_t)(int mid, int objid, int insid, int resid, int type, int flag, int len, char *data);

/**
 *  @brief 平台excute操作回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] objid 被操作的object ID
 *  @param [out] insid 被操作的instance ID
 *  @param [out] resid 被操作的resource ID
 *  @param [out] len   数据长度
 *  @param [out] data 执行的参数
 *
 *  @return 无
 *  
 */
typedef void (*cot_execute_cb_t)(int mid, int objid, int insid, int resid, int len, char *data);

 /**
 *  @brief 平台observe操作回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] observe 订阅标志 1：订阅；0：取消订阅 
 *  @param [out] objid 被操作的object ID
 *  @param [out] insid 被操作的instance ID
 *  @param [out] resid 被操作的resource ID
 *
 *  @return 无
 *  
 */
typedef void (*cot_observe_cb_t)(int mid, int observe, int objid, int insid, int resid);
 
/**
 *  @brief 平台设置策略参数请求回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] objid 被操作的object ID
 *  @param [out] insid 被操作的instance ID
 *  @param [out] resid 被操作的resource ID
 *  @param [out] len   数据长度
 *  @param [out] parameter   策略参数，格式如:pmin=xxx; pmax=xxx; gt=xxx; lt=xxx; stp=xxx\n
 *					pmin: int类型，上传数据的最小时间间隔\n
 *					pmax: int类型，上传数据的最大时间间隔\n
 *					gt:   double类型，当数据大于该值上传\n
 *					lt:   double类型，当数据小于该值上传\n
 *					stp:  double类型，当两个数据点相差大于或者等于该值上传
 *
 *  @return 无
 *  
 */
typedef void (*cot_params_cb_t)(int mid, int objid, int insid, int resid, int len, char *parameter);

/**
 *  @brief 平台discover操作回调函数，需用户实现
 *  
 *  @param [out] mid 操作消息的ID
 *  @param [out] objid 被操作的object ID
 *
 *  @return 无
 *  
 */
typedef void (*cot_discover_cb_t)(int mid, int objid);


/** OneNET事件回调*/
typedef struct cm_cot_cb
{
    cot_read_cb_t       onRead;         /*!< 读回调，平台下发Read请求时触发*/
    cot_write_cb_t      onWrite;        /*!< 写回调，平台下发Write请求时触发*/
    cot_execute_cb_t    onExec;         /*!< 执行回调，平台下发Exec请求时触发*/
	cot_observe_cb_t    onObserve;      /*!< 订阅回调，平台下发订阅请求时触发*/
	cot_params_cb_t     onParams;       /*!< 策略参数回调，平台下发策略时触发*/
    cot_event_cb_t      onEvent;        /*!< 事件状态通知*/
    cot_notify_cb_t     onNotify;       /*!< Notify通知*/
	cot_discover_cb_t   onDiscover;     /*!< 平台下发Discover请求时触发*/
}cm_cot_cb_t;


/**
 *  @brief 初始化OneNET任务，在使用OneNET相关函数之前调用
 *
 *  @return 无
 *
 */
void cm_onenet_init(void);


/**
 *  @brief 创建cot设备，当前只允许创建一个设备
 *  
 *  @param [in]  ip      需注册的OneNET平台服务器IP
 *  @param [in]  is_bs   是否bootstrap服务器
 *  @param [in]  cot_cb  需注册的回调函数
 *
 *  @return 0: 创建成功，创建成功后\n
 *         >0: 创建失败，错误码参照错误码定义
 *  
 */
int cm_onenet_create(char *ip, int is_bs, cm_cot_cb_t *cot_cb);


/**
 *  @brief 创建cot设备，当前只允许创建一个设备
 *  
 *  @param [in]  ip         需注册的OneNET平台服务器IP
 *  @param [in]  is_bs      是否bootstrap服务器
 *  @param [in]  cot_cb     需注册的回调函数
 *  @param [in]  auth_code  注册服务器认证参数，不设值时平台无认证参数设置为NULL
 *
 *  @return 0: 创建成功，创建成功后\n
 *         >0: 创建失败，错误码参照错误码定义
 *  
 */
int cm_onenet_create_ex(char *ip, int is_bs, cm_cot_cb_t *cot_cb,char *auth_code);


/**
 *  @brief 创建cot设备，当前只允许创建一个设备
 *  
 *  @param [in]  ip         需注册的OneNET平台服务器IP
 *  @param [in]  is_bs      是否bootstrap服务器
 *  @param [in]  cot_cb     需注册的回调函数
 *  @param [in]  auth_code  注册服务器认证参数，不设值时平台无认证参数设置为NULL
 *  @param [in]  psk        共享密匙
 *
 *  @return 0: 创建成功，创建成功后\n
 *         >0: 创建失败，错误码参照错误码定义
 *  
 */
int cm_onenet_create_dtls(char *ip, int is_bs, cm_cot_cb_t *cot_cb,char *auth_code,char *psk);


/**
 *  @brief 注销设备与OneNET连接 或 清理OneNET设备
 *  
 *  @param [in]  level  2 注销与OneNET连接，清除resource数据\n
 *                      4 关闭与OneNET连接，清除所有resource、instance、object数据
 *
 *  @return 0: 操作成功\n
 *             若有注销OneNET平台操作，cot_event_cb_t将被回调\n
 *         >0: 操作失败，错误码参照错误码定义
 *  
 */
int cm_onenet_close(int level);


/**
 *  @brief 添加一个object
 *  
 *  @param [in]  objid     object id,本次需添加的object，如3200
 *  @param [in]  inscount  设置该object对象的instance个数，若设置本次添加的object有5个实例，则inscount为5
 *  @param [in]  bitmap    实例位图，字符串格式，每一个字符表示为一个实例，其中1表示可用，0表示不可用。\n
 *                         例如当前添加的object有5个实例，其中，0,3可用，则实例位图为10010
 *  @param [in]  attcount  属性个数，当前版本暂不使用，置0即可
 *  @param [in]  actcount  操作个数，当前版本暂不使用，置0即可
 *
 *  @return 0: 添加成功\n
 *         >0: 添加失败，错误码参照错误码定义
 *  
 */
int cm_onenet_add_obj(int objid, int inscount, unsigned char* bitmap, int attcount, int actcount);


/**
 *  @brief 删除一个object，同时将删除相关的所有instance和resource数据
 *  
 *  @param [in]  objid     object id,本次需删除的object，如3200
 *
 *  @return 0: 删除成功\n
 *         >0: 删除失败，错误码参照错误码定义
 *  
 */
int cm_onenet_del_obj(int objid);


/**
 *  @brief 向平台发起注册请求
 *  
 *  @param [in]  timeout   本次注册的超时时长，单位为s，超时后将关闭当前操作，并上报。不可为0
 *  @param [in]  lifetime  本次注册成功后生命周期，单位为s。\n
 *                         生命周期超时后如未及时UPDATE将注销当前连接，并上报
 *
 *  @return 0: 操作发起成功，操作是否成功依据模组cot_event_cb_t回调结果\n
 *         >0: 操作发起失败，错误码参照错误码定义
 *  
 */
int cm_onenet_open(unsigned int timeout, unsigned int lifetime);


/**
 *  @brief 向平台发起更新生命周期或当前object请求
 *  
 *  @param [in]  lifetime  更新的lifetime值，单位为s，如果小于10则表示使用默认的lifetime值，86400s
 *  @param [in]  flag      是否需要同时更新注册的Object对象\n
 *                         0:不更新     1:更新
 *
 *  @return 0: 操作发起成功，操作是否成功依据模组cot_event_cb_t回调结果\n
 *         >0: 操作发起失败，错误码参照错误码定义
 *  
 */
int cm_onenet_update(unsigned int lifetime, int flag);


/**
 *  @brief 向平台发起查询是否在注册状态
 *  
 *
 *  @return 0: 向平台发起查询成功，操作是否成功需等待模组cot_event_cb_t回调结果\n
 *         >0: 向平台发起查询失败，错误码参照错误码定义\n
 *        600: 设备未注册
 *
 */
int cm_onenet_is_open(void);


/**
 *  @brief 声明指定object的资源列表
 *  
 *  @param [in]  objid   需discover操作的对象ID
 *  @param [in]  len     data的长度
 *  @param [in]  data    object的resource要求，多个resource之间使用分号";"隔开"1101;1102;1103"
 *
 *  @return 0: 操作成功\n
 *         >0: 操作失败，错误码参照错误码定义
 *
 */
int cm_onenet_discover(int objid, int len, char *data);


/**
 *  @brief 向平台上报指定resource数据的变化
 *  
 *  @param [in]  objid   object id,本次需上报数据的对象ID，如3200
 *  @param [in]  insid   instance id，本次需上报数据的实例ID
 *  @param [in]  resid   resource id，本次需上报数据的资源ID
 *  @param [in]  type    发送的数据类型，不透明类型为十六进制字符串直接上报\n
 *                       1      2       3       4       5\n
 *                       string opaque  integer float   bool\n
 *                       字符串 不透明  整形    浮点型  布尔型
 *  @param [in]  value   发送的数据
 *  @param [in]  flag    消息标识 0:该Notify消息暂不上报 1:上报未上报的Notify消息(同一instance下)
 *  @param [in]  ack_id  指定该消息是否以响应形式上报  -1:非响应模式  >=0:响应模式\n
 *                       如果为响应模式，该条Notify消息成功时将被cot_notify_cb_t回调\n
 *                       该ack_id应该为不同的值
 *  @param [in]  mode    是否使用RAI功能，当前暂不提供该功能
 *
 *  @return 0: 操作成功\n
 *         >0: 操作失败，错误码参照错误码定义
 *
 */
int cm_onenet_notify(int objid, int insid, int resid, int type, char *value, int flag, int ack_id, int mode);


/**
 *  @brief cot_read_cb被回调后，回复平台读取到的资源的值
 *  
 *  @param [in]  mid     收到的+MIPLREAD的消息携带的mid。
 *  @param [in]  objid   object id,本次需回复数据的对象ID，如3200
 *  @param [in]  insid   instance id，本次需回复数据的实例ID
 *  @param [in]  resid   resource id，本次需回复数据的资源ID
 *  @param [in]  type    回复的数据类型，不透明类型为十六进制字符串直接上报\n
 *                       1      2       3       4       5\n
 *                       string opaque  integer float   bool\n
 *                       字符串 不透明  整形    浮点型  布尔型
 *  @param [in]  value   回复的数据
 *  @param [in]  flag    消息标识 0:该read回复暂不回复 1:回复未回复的read消息(同一instance下)
 *
 *  @return 0: 操作成功\n
 *         >0: 操作失败，错误码参照错误码定义
 *
 */
int cm_onenet_read(int mid, int objid, int insid, int resid, int type, char *value, int flag);


/**
 *  @brief 以下回调函数被回调后，回复平台操作结果\n
 *          cot_write_cb\n
 *          cot_execute_cb\n
 *          cot_observe_cb\n
 *          cot_parameter_cb
 *  
 *  @param [in]  mid          收到的操作消息携带的mid
 *  @param [in]  result       操作结果返回码
 *  @param [in]  is_observe   是否是MIPLOBSERVE操作
 *
 *  @return 0: 操作成功\n
 *         >0: 操作失败，错误码参照错误码定义
 *
 */
int cm_onenet_result(int mid, int result, int is_observe);

/**
 *  @brief 未连接平台前，用户注册OneNET FOTA通知事件（连接平台后，cm_onenet_create()被调用后，该注册的函数被cm_onenet_create()注册的函数替换）
 *  
 *  @param [in] cb 回调函数
 *  @return None
 *
 */
void cm_onenet_event_register(cm_onenet_fota_event_cb_t cb) ;

/** @} */ 

#endif

