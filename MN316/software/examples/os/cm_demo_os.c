/**
 *  @file    cm_demo_os.c
 *  @brief   OpenCPU操作系统使用示例
 *  @copyright copyright ? 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/22
 */


#include "cm_os.h"
#include "cm_demo_common.h"


static osMessageQueueId_t s_test_queue = NULL;
static osMutexId_t s_test_mutex = NULL;
static osSemaphoreId_t s_test_seamp1 = NULL;
static osSemaphoreId_t s_test_seamp2 = NULL;
static osTimerId_t s_test_timer = NULL;
static unsigned int s_test_num = 0;

typedef struct{
    int msg_type;
    void* msg_data;
} test_msg_t;


/**
 *  \brief 软件定时器回调函数
 * 
 *  \details
 */
static void test_timer_callback(void* arg)
{
    (void)arg;
    test_msg_t msg = {0};

    msg.msg_type = s_test_num++;

    if(s_test_queue != NULL)//向队列发送数据
    {
        osDelay(100);
        osMessageQueuePut(s_test_queue, &msg, 0, osNoWait);
    }

    if(s_test_seamp1 != NULL)//释放信号量
    {
        osDelay(100);
        osSemaphoreRelease(s_test_seamp1);
        cm_demo_printf("s_test_seamp1 release\n");
    }

    if(s_test_seamp2 != NULL)//释放信号量
    {
        osDelay(100);
        osSemaphoreRelease(s_test_seamp2);
        cm_demo_printf("s_test_seamp2 release\n");
    }
}


/**
 *  \brief 线程1，用于队列测试
 * 
 *  \details
 */
static void test_task_1(void *arg)
{
    (void)arg;
    cm_demo_printf("test tsk1 start\n");

    test_msg_t msg = {0};

    while(1)
    {
        if(osMessageQueueGet(s_test_queue, &msg, NULL, osWaitForever) == osOK)//永久阻塞，直至队列不为空
        {
            cm_demo_printf("msg->type:%d\n", msg.msg_type);
        }
    }

    osThreadExit();//删除线程
}


/**
 *  \brief 线程2，用于互斥锁和信号量测试
 * 
 *  \details
 */
static void test_task_2(void *arg)
{
    (void)arg;
    cm_demo_printf("test tsk2 start\n");

    while(1)
    {
        osSemaphoreAcquire(s_test_seamp1, osWaitForever);//获取信号量，永久阻塞，直至信号量被释放

        cm_demo_printf("s_test_seamp1 acquire\n");

        osMutexAcquire(s_test_mutex, osWaitForever);//加锁，永久阻塞

        cm_demo_printf("tsk2 mutex-acquire\n");

        osMutexRelease(s_test_mutex);//释放锁
    }

    osThreadExit();//删除线程
}


/**
 *  \brief 线程2，用于互斥锁和信号量测试
 * 
 *  \details
 */
static void test_task_3(void *arg)
{
    (void)arg;
    cm_demo_printf("test tsk3 start\n");

    while(1)
    {
        osSemaphoreAcquire(s_test_seamp2, osWaitForever);//获取信号量，永久阻塞，直至信号量被释放

        cm_demo_printf("s_test_seamp2 acquire\n");

        osMutexAcquire(s_test_mutex, osWaitForever);//加锁，永久阻塞

        cm_demo_printf("tsk3 mutex-acquire\n");

        osMutexRelease(s_test_mutex);//释放锁
    }

    osThreadExit();//删除线程
}


/**
 *  \brief 操作系统使用示例
 * 
 *  \details
 */
int cm_test_os(unsigned char **cmd, int len)
{

    if(s_test_queue == NULL)//创建队列
    {
        s_test_queue = osMessageQueueNew(10, sizeof(test_msg_t), NULL);
        cm_assert(s_test_queue != NULL);
    }

    if(s_test_mutex == NULL)//创建互斥锁
    {
        s_test_mutex = osMutexNew(NULL);
        cm_assert(s_test_mutex != NULL);
    }

    if(s_test_seamp1 == NULL)//创建信号量
    {
        s_test_seamp1 = osSemaphoreNew(1, 0, NULL);
        cm_assert(s_test_seamp1 != NULL);
    }

    if(s_test_seamp2 == NULL)//创建信号量
    {
        s_test_seamp2 = osSemaphoreNew(1, 0, NULL);
        cm_assert(s_test_seamp2 != NULL);
    }

    /* 用户线程优先级范围osPriorityNormal -> osPriorityNormal5*/
    osThreadAttr_t attr1 = {
        .name = "TEST-TSK1",
        .priority = osPriorityNormal1,
        .stack_size = 512,
    };
    osThreadAttr_t attr2 = {
        .name = "TEST-TSK2",
        .priority = osPriorityNormal1,
        .stack_size = 512
    };
    osThreadAttr_t attr3 = {
        .name = "TEST-TSK3",
        .priority = osPriorityNormal1,
        .stack_size = 512
    };

    osThreadNew(test_task_1, NULL, (const osThreadAttr_t*)&attr1);//创建线程
    osDelay(100);
    osThreadNew(test_task_2, NULL, (const osThreadAttr_t*)&attr2);
    osDelay(100);
    osThreadNew(test_task_3, NULL, (const osThreadAttr_t*)&attr3);

    if(s_test_timer == NULL)
    {
        osTimerAttr_t timer_attr = {.name = "test_timer"};
        s_test_timer = osTimerNew(test_timer_callback, osTimerPeriodic, NULL, &timer_attr);//创建定时器，周期性运行
    }

    osTimerStart(s_test_timer, 5000);//启动定时器
    return 0;
}
