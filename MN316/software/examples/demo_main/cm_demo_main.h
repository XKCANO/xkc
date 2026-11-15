/**
 *  @file    cm_demo_main.h
 *  @brief   OpenCPU使用示例
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/03
 */


#ifndef __CM_DEMO_MAIN_H__
#define __CM_DEMO_MAIN_H__

#define CM_UNUSED(n) do{(void)n;}while(0)


/** 消息队列定义*/
typedef struct{
    char* cmd_str;
    void* param;
} cm_user_msg_t;

/**命令结构体*/
typedef struct cm_cmd {
    unsigned char * cmdstr;
    void (* cmdfunc)(unsigned char **,int);
} cm_cmd_t;
/**
 *  \brief 串口命令结构体
 */
typedef struct 
{
    int cmd_execute;  //命令执行标志，1未被执行，0执行完成
    unsigned char * buf[20]; //最多接受20个参数
    int len;//参数个数
}cm_uart_cmd_recv_t;
/**
 *  \brief 写队列
 *  
 *  \param [in] msg 队列指针
 *  \return 成功返回0，失败返回-1
 *  
 *  \details 使用指针传递方式
 */
int cm_user_queue_send(cm_user_msg_t* msg);


/**
 *  \brief OpenCPU版本程序入口
 *  
 *  \return 空
 *  
 *  \details 仅用于创建OC线程,请勿修改此函数名
 */
void cm_opencpu_entry(void);

#endif
