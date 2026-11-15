/**
 *  \file    cm_demo_ctwing.c
 *  \brief   CTWing使用示例
 *  \copyright copyright ? 2021 China Mobile IOT. All rights reserved.
 *  \author by ZXW
 *  \date 2021/02/02
 */


#include <stdio.h>
#include <string.h>
#include "cm_demo_common.h"
#include "cm_ctwing.h"
#include "cm_fota.h"

static bool s_ctw_subscrible_flag = false;

/**
 *  \brief FOTA状态回调
 *  
 *  \param [in] state FOTA状态
 *  \return None
 *  
 *  \details \ref cm_ctw_fota_cb
 */
static void test_ctw_fota_cb(const cm_ctw_fota_state_t* state)
{
    if(state == NULL)
    {
        return;
    }

    switch(state->state)
    {
        case CM_CTW_FOTA_IDLE://空闲态
        {
            cm_demo_printf("+CTWFOTA:%d,%d\n", state->state, state->n1);
        }
        break;
        case CM_CTW_FOTA_DOWNLOADING://下载中
        {
            cm_demo_printf("+CTWFOTA:%d,%d,%d\n", state->state, state->n1, state->n2);
        }
        break;
        case CM_CTW_FOTA_DOWNLOADED://下载完成
        {
            cm_demo_printf("+CTWFOTA:%d\n", state->state);
        }
        break;
        case CM_CTW_FOTA_UPDATING://升级中
        {
            cm_demo_printf("+CTWFOTA:%d\n", state->state);
        }
        break;
        case CM_CTW_FOTA_UPDATED://升级完成
        {
            cm_demo_printf("+CTWFOTA:%d,%d\n", state->state, state->n1);
        }
        break;
        default:
        break;
    }
}


/**
 *  \brief 发送数据回调
 *  
 *  \param [in] mid 发送数据的消息ID
 *  \return None
 *  
 *  \details \ref cm_ctw_send_cb  当前版本中未实现
 */
static void test_ctw_send_cb(int mid)
{
    cm_demo_printf("+CTWSEND:%d\n", mid);
}


/**
 *  \brief 接收数据回调
 *  
 *  \param [in] data 接收数据
 *  \param [in] len 数据长度
 *  \return None
 *  
 *  \details \ref cm_ctw_recv_cb
 */
static void test_ctw_recv_cb(char* data, int len)
{
    if(data == NULL || len <= 0)
    {
        return;
    }

    char* recv_data = (char*)cm_malloc(len + 1);

    memcpy(recv_data, data, len);
    recv_data[len] = '\0';
    cm_demo_printf("+CTWRECV:%d,%s\n", len, recv_data);

    cm_free(recv_data);
}


/**
 *  \brief 事件回调
 *  
 *  \param [in] event 事件
 *  \param [in] mid 消息ID，仅当event为发送数据事件时有效
 *  \return None
 *  
 *  \details \ref cm_ctw_event_cb
 */
static void test_ctw_event_cb(int event, int mid)
{
    if(event == CM_CTW_DATA_SEND_OK || event == CM_CTW_DATA_SEND_TIMEOUT)
    {
        cm_demo_printf("+CTWEVT:%d,%d\n", event, mid);
    }
    else
    {
        cm_demo_printf("+CTWEVT:%d\n", event);
    }

    if(event == CM_CTW_DATA_SUBSCRIBLE)//注册成功
    {
        s_ctw_subscrible_flag = true;
    }
    else if(event == CM_CTW_RECOVERY_OK)//深睡眠唤醒后恢复状态
    {
        int ret = cm_ctw_update();//更新注册
        if(ret)
        {
            cm_demo_printf("ctw update err,%d\n", ret);
        }
    }
    else if(event == CM_CTW_DEREG)
    {
        s_ctw_subscrible_flag = false;
    }
}


/**
 *  \brief 空口回传回调
 *  
 *  \param [in] seq 空口回传序列号
 *  \param [in] state 发送状态
 *  \return None
 *  
 *  \details 当send数据携带空口回传标志时，将会在发送成功或失败时触发此回调
 */
static void test_ctw_sequence_cb(unsigned char seq, unsigned char state)
{
    cm_demo_printf("+CTWSEQ:%d,%d\n", seq, state);
}

/**
 *  \brief CTWing使用示例
 *  
 *  \return None
 *  
 *  \details 仅供参考
 */
 
static int test_ctw_create(void* arg){
    char* server_ip = "221.229.214.202";
    int server_port = 5683;
    int ret = cm_ctw_create(server_ip, server_port);
    if(ret != 0)
    {
        cm_demo_printf("ctw create err,%d\n", ret);
        goto ctw_exit;
    }
    return 0;
ctw_exit:
    cm_ctw_delete();
    return -1;
}

static int test_ctw_open(void* arg)
{
    (void)arg;

    /*判断CTWing是否已注册*/
    if(s_ctw_subscrible_flag == true)
    {
        cm_demo_printf("ctw already open\n");//CTWing已经注册至平台
        return 0;
    }
    
    char value[64] = {0};
    if(cm_fota_get_version)
    {
        cm_fota_get_version(value);
        cm_demo_printf("ctw fota ver:%s\n", value);
    }
    
    cm_ctw_cb_t ctw_cb = {0};
    
    int wait_time = 0;

    /*设置回调函数*/
    ctw_cb.send_cb = test_ctw_send_cb;  
    ctw_cb.recv_cb = test_ctw_recv_cb;
    ctw_cb.evt_cb = test_ctw_event_cb;
    ctw_cb.fota_cb = test_ctw_fota_cb;
    ctw_cb.seq_cb = test_ctw_sequence_cb;

    /*注册至服务器*/
    
    int ret = cm_ctw_open(86400, &ctw_cb);

    if(ret != 0)
    {
        cm_demo_printf("ctw open err,%d\n", ret);
        goto ctw_exit;
    }

    while(wait_time < 30)//接收到CM_CTW_DATA_SUBSCRIBLE才表示成功注册并订阅
    {
        if(s_ctw_subscrible_flag == true)
        {
            break;
        }
        osDelay(1000);
        wait_time++;
    }

    if(wait_time >= 30)
    {
        cm_demo_printf("ctw subscrible err\n");
        goto ctw_exit;
    }

    return 0;

ctw_exit:
    cm_ctw_delete();
    return -1;
}


static int test_ctw_send1(void* arg)
{
    (void)arg;

    char test_data[] = "foo foo foo foo";
    int ret = cm_ctw_send(test_data, strlen(test_data));

    if(ret != 0)
    {
        cm_demo_printf("ctw send err,%d\n", ret);
    }

    return ret;
}

static int test_ctw_send2(void* arg)
{
    (void)arg;

    char test_data[] = "bar bar bar bar";
    int ret = cm_ctw_send_ex(test_data, strlen(test_data), CM_CTW_COAP_TYPE_NON, CM_CTW_RAI_1, 123);

    if(ret != 0)
    {
        cm_demo_printf("ctw send err,%d\n", ret);
    }

    return ret;
}

static int test_ctw_update(void* arg)
{
    (void)arg;

    int ret = cm_ctw_update();
    if(ret != 0)
    {
        cm_demo_printf("ctw update err,%d\n", ret);
    }

    return ret;
}

static int test_ctw_close(void* arg)
{
    (void)arg;

    int ret = cm_ctw_close();
    if(ret != 0)
    {
        cm_demo_printf("ctw close err,%d\n", ret);
    }

    return ret;
}

static int test_ctw_delete(void* arg)
{
    (void)arg;

    int ret = cm_ctw_delete();
    if(ret != 0)
    {
        cm_demo_printf("ctw delete err,%d\n", ret);
    }

    return ret;
}

static void test_ctw_fota_query(void)
{
    cm_ctw_fota_state_t state = {0};

    int ret = cm_ctw_fota_query_state(&state);

    if(ret != 0)
    {
        cm_demo_printf("ctw fota state err,%d\n", ret);
        return;
    }

    switch(state.state)
    {
        case CM_CTW_FOTA_IDLE://空闲态
        {
            cm_demo_printf("+FOTA:%d,%d\n", state.state, state.n1);
        }
        break;
        case CM_CTW_FOTA_DOWNLOADING://下载中
        {
            cm_demo_printf("+FOTA:%d,%d,%d\n", state.state, state.n1, state.n2);
        }
        break;
        case CM_CTW_FOTA_DOWNLOADED://下载完成
        {
            cm_demo_printf("+FOTA:%d\n", state.state);
        }
        break;
        case CM_CTW_FOTA_UPDATING://升级中
        {
            cm_demo_printf("+FOTA:%d\n", state.state);
        }
        break;
        case CM_CTW_FOTA_UPDATED://升级完成
        {
            cm_demo_printf("+FOTA:%d,%d\n", state.state, state.n1);
        }
        break;
        default:
        break;
    }
}


void cm_test_ctwing(unsigned char **cmd, int len)
{
	int func = atoi((const char *)cmd[2]);
	switch(func)
	{
	    case 0:
            test_ctw_create(0);
            break;
		case 1:
			test_ctw_open(0);
			break;
		case 2:
			test_ctw_send1(0);
			break;
		case 3:
			test_ctw_send2(0);
			break;
		case 4:
			test_ctw_update(0);
			break;
		case 5:
			test_ctw_close(0);
			break;
        case 6:
			test_ctw_delete(0);
			break;
        case 7:
            test_ctw_fota_query();
            break;
		default:
			cm_demo_printf("no func\n");
			break;
	}
}
