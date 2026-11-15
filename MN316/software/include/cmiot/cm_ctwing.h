/**
 *  @file    cm_ctwing.h
 *  @brief   CTWing接口
 *  @copyright copyright © 2022 China Mobile IOT. All rights reserved.
 *  @author by ZXW/SMR
 *  @date 2022/01/18
 */


/** @defgroup CTWing ctwing
 * CTWing接口
 * @ingroup CC
 * @{
 * */
 
#ifndef __CM_CTWING_H__
#define __CM_CTWING_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum{
    CM_CTW_RET_OK = 0,                  //成功
    CM_CTW_RET_INVALID_PARAM = -1,         
    CM_CTW_RET_ERR_STATE = -2,          //fota过程中不能close或delete
    CM_CTW_RET_NOT_RUNNING = -3,
    CM_CTW_RET_ALREADY_OPEN = -4,
    CM_CTW_RET_OPEN_FAIL = -5,
    CM_CTW_RET_LIFETIME_EXPIRED = -6,
    CM_CTW_RET_SERVER_EMPTY = -7,
    CM_CTW_RET_NET_DOWN = -8,
    CM_CTW_RET_SEND_ERR = -9,
    CM_CTW_RET_CREATE_FAIL = -10,
    CM_CTW_RET_ERR_PLAT = -11,          //ctwing平台与onenet平台互斥，使用onenet时需保证ctwing已被delete，反之亦然
}cm_ctw_err_type_e;

typedef enum{
    CM_CTW_COAP_TYPE_NON = 0,       /*!< 不需要服务器回复ACK */
    CM_CTW_COAP_TYPE_CON,       /*!< 需要服务器返回ACK */
}cm_ctw_coap_ack_type_e;

typedef enum{
    CM_CTW_RAI_0 = 0,           /*!< 基站协商释放，一般为20秒 */
    CM_CTW_RAI_1,           /*!< 发送之后立即释放 */
    CM_CTW_RAI_2,           /*!< 发送数据并收到数据后立即释放 */
}cm_ctw_rai_type_e;

typedef enum{
    CM_CTW_REG_OK = 1,              /*!< 注册成功       */
    CM_CTW_REG_FAIL,                /*!< 注册失败       */
    CM_CTW_REG_UPDATED,             /*!< 更新注册成功   */
    CM_CTW_REG_UPDAT_FAIL,          /*!< 更新注册失败   */
    CM_CTW_DEREG,                   /*!< 注销成功       */
    CM_CTW_DEREG_FAIL,              /*!< 注销失败       */
    CM_CTW_DATA_SUBSCRIBLE,         /*!< 订阅成功       */
    CM_CTW_DATA_UNSUBSCRIBLE,       /*!< 订阅失败       */
    CM_CTW_DATA_SEND_OK,            /*!< CON 模式下，接收到 ACK，数据发送成功       */
    CM_CTW_DATA_SEND_TIMEOUT,       /*!< CON 模式下，超时未收到 ACK，数据发送失败  */
    CM_CTW_DTLS_HANDLE_OK,          /*!< DTLS 握手成功，暂不支持                     */
    CM_CTW_DTLS_HANDLE_FAIL,        /*!< DTLS 握手失败，暂不支持                     */
	CM_CTW_RECOVERY_OK,             /*!< 深睡眠唤醒后， 状态恢复成功                     */
}cm_ctw_evt_type_e;

typedef enum{
    CM_CTW_FOTA_IDLE = 0,           /*!< 设备空闲或等待平台下发配置  */
    CM_CTW_FOTA_DOWNLOADING,        /*!< 设备正在下载升级包          */
    CM_CTW_FOTA_DOWNLOADED,         /*!< 下载完成                    */
    CM_CTW_FOTA_UPDATING,           /*!< 开始升级                    */
    CM_CTW_FOTA_UPDATED,            /*!< 设备升级完成                */
}cm_ctw_fota_state_e;

typedef struct{
    short send_retry_times;        /*!< 重传次数，有效值<1-3>次，设置为0表示不需要重传，缺省配置为3 */
    short send_retry_interval;     /*!< 重传间隔，<4-8>秒，每次重传间隔在上一次基础上加倍，缺省配置为4.例：设置值为4，则第1次重传间隔4秒，第2次8秒，第3次16秒。若重传次数配置为0，则本参数用作发送超时时间 */
    short recv_filter_time;        /*!< 接收包重复过滤，有效值<10-30>秒，当recv_fileter_time秒内接收到mid相同的数据包，则丢弃后一包数据不做处理；设置为0表示不需要过滤，缺省配置为0 */
    uint8_t cloud_update_switch;   /*!< 是否开启云保活。有效值<0-1>，1为开启，0为不开启，默认不开启。开启后保活时间超时将不上报注销事件，超时后可使用update重新注册，不需要再次open */
}cm_ctw_cfg_t;

typedef struct{
    char state;     /*!< FOTA状态，\ref cm_ctw_fota_state_e */
    int n1;         /*!< 当state=0时，n1表示fota状态                          \n
                            n1=0，空闲状态                                   \n
                            n1=1，FOTA 状态订阅完成，等待配置 URI 下载信息   \n
                            n1=2，初始化完成，开始下载                       \n
                         当state=1时，n1表示升级包总长度                      \n
                         当state=4时，n1表示升级结果                          \n
                            n1=1，升级成功                                   \n
                            n1=2，升级包超过限制                             \n
                            n1=3，内存不足                                   \n
                            n1=4，下载过程中连接中断                         \n
                            n1=5，升级包校验失败                             \n
                            n1=6，升级包类型错误                             \n
                            n1=7，无效 URI                                   \n
                            n1=8，升级失败                                   \n
                            n1=9，协议不支持                                 \n
                         state为其他值，n1无效 */
    int n2;         /*!< 仅当state=1时，n2表示当前累计下载升级包的长度；state为其他值，n2无效 */
}cm_ctw_fota_state_t;

/* ctwing 注册状态 */
typedef enum{
    CM_CTW_REG_STATE_IDLE = 0,        /*!< 空闲   */
    CM_CTW_REG_STATE_LOGINING,        /*!< 注册中 */
    CM_CTW_REG_STATE_LOGINOK,         /*!< 注册成功 */
    CM_CTW_REG_STATE_DEREG,           /*!< 注销中 */
}cm_ctw_reg_state_e;

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

/****************************************************************************/

/**
 *  @brief 发送回调 
 *  
 *  @param [in] mid 消息ID
 *  @return None
 *  
 *  @details 执行send操作后将会触发返回当前发送消息的ID
 */
typedef void (* cm_ctw_send_cb)(int mid);

/**
 *  @brief 接收回调
 *  
 *  @param [in] data 消息内容
 *  @param [in] len 消息长度，len <= 1000字节
 *  @return None
 *  
 *  @details 服务器下发数据后将会触发此回调函数
 */
typedef void (* cm_ctw_recv_cb)(char* data, int len);

/**
 *  @brief 事件回调
 *  
 *  @param [in] event 事件类型，\ref cm_ctw_evt_type_e
 *  @param [in] mid 消息ID，仅当event=9或10时，mid表示发送数据的mid；event为其他值，mid无效
 *  @return None
 *  
 *  @details
 */
typedef void (* cm_ctw_event_cb)(int event, int mid);

/**
 *  @brief 空口回传回调
 *  
 *  @param [in] seq 空口回传序列号，1-255
 *  @param [in] state 发送状态，0：发送成功，其他：发送失败
 *  @return None
 *  
 *  @details 当send数据携带空口回传标志时，将会在发送成功或失败时触发此回调
 */
typedef void (* cm_ctw_sequence_cb)(unsigned char seq, unsigned char state);

/**
 *  @brief FOTA状态回调
 *  
 *  @param [in] state 当前fota状态，\ref cm_ctw_fota_state_t
 *  @return None
 *  
 *  @details 当平台端开始FOTA升级时触发此回调
 */
typedef void (* cm_ctw_fota_cb)(const cm_ctw_fota_state_t* state);

typedef struct{
    cm_ctw_send_cb send_cb;         /*!< 发送回调 */
    cm_ctw_recv_cb recv_cb;         /*!< 接收回调 */
    cm_ctw_event_cb evt_cb;         /*!< 事件回调 */
    cm_ctw_sequence_cb seq_cb;      /*!< 空口回传回调 */
    cm_ctw_fota_cb fota_cb;         /*!< FOTA回调 */
}cm_ctw_cb_t;

/**
 *  @brief 创建
 *  
 *  @param [in] ip 服务器IP地址，不支持域名
 *  @param [in] port 服务器端口
 *  @return 成功返回0，失败返回负值
 *  
 *  @details More details
 */
int cm_ctw_create(char* ip, int port);

/**
 *  @brief 删除
 *  
 *  @return 成功返回0，失败返回负值
 *  
 *  @details More details
 */
int cm_ctw_delete(void);

/**
 *  @brief 配置
 *  
 *  @param [in] cfg 配置信息
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 只能在open之前使用
 */
int cm_ctw_cfg(const cm_ctw_cfg_t* cfg);

/**
 *  @brief 注册至平台
 *  
 *  @param [in] leftime 保活时间，300-86400秒
 *  @param [in] cb 回调函数配置
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 请在回调函数中处理对应的异步信息. 
 */
int cm_ctw_open(int lifetime, cm_ctw_cb_t* cb);

/**
 *  @brief 注销
 *  
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 请在回调函数中处理对应的异步信息
 */
int cm_ctw_close(void);

/**
 *  @brief 更新注册
 *  
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 请在回调函数中处理对应的异步信息，更新注册将按照open传入的leftime重新保活
 */
int cm_ctw_update(void);


/**
 *  @brief 标准发送
 *  
 *  @param [in] data 待发送数据
 *  @param [in] len 数据长度，len <= 1000字节
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 标准发送接口：CON模式，不携带空口回传标识，接收到下行包后立即释放RRC
 */
int cm_ctw_send(const char* data, int len);

/**
 *  @brief 自定义发送
 *  
 *  @param [in] data 待发送数据
 *  @param [in] len 数据长度，len <= 1000字节
 *  @param [in] con 消息类型
 *  @param [in] rai RRC释放方式
 *  @param [in] seq 空口回传序列号，有效值1-255，0表示不携带此标识
 *  @return 成功返回0，失败返回负值
 *  
 *  @details 在回调函数中处理对应的异步信息
 */
int cm_ctw_send_ex(const char* data, int len, cm_ctw_coap_ack_type_e con, cm_ctw_rai_type_e rai, unsigned char seq);

/**
 *  @brief 查询FOTA升级状态
 *  
 *  @param [out] state 升级状态
 *  @return 成功返回0，失败返回负值
 *  
 *  @details More details
 */
int cm_ctw_fota_query_state(cm_ctw_fota_state_t* state);

/**
 *  @brief 查询注册状态
 *  
 *  @return 成功返回注册状态cm_ctw_reg_state_e，失败返回负值
 *  
 *  @details More details
 */
int cm_ctw_get_reg_state(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_CTWING_H__ */

/** @}*/
