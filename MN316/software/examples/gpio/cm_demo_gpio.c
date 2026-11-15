/**
 * @file        cm_demo_gpio.c
 * @brief       OpenCPU gpio测试例程
 * @copyright   Copyright ? 2021 China Mobile IOT. All rights reserved.
 */
 

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include "string.h"
#include "cm_common.h"
#include "cm_os.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define CM_DEMO_GPIO_LOG     CM_DEMO_LOG


#define CM_DEMO_INPUT_GPIO      CM_GPIO_NUM_6  //可设置，选择需要进行输入功能测试的引脚
#define CM_DEMO_OUTPUT_GPIO     CM_GPIO_NUM_2  //可设置，选择需要进行输出功能测试的引脚
#define CM_DEMO_INTERRUPT_GPIO  CM_GPIO_NUM_7  //可设置，选择需要进行中断功能测试的引脚
/****************************************************************************
 * Private Types
 ****************************************************************************/


 
/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Data
 ****************************************************************************/
static osSemaphoreId_t s_cm_gpio_int_sem = NULL;
static uint32_t s_cm_gpio_inter_times = 0;


/****************************************************************************
 * Private Functions
 ****************************************************************************/

/**
 *  \brief GPIO中断处理函数
 * 
 *  \details 中断处理函数以及内部调用接口必须在声明阶段使用编译器参数置于.ramtext段！！！切勿执行复杂耗时操作。
 */
static void gpio_irq_handle(cm_gpio_num_e gpio_num) __RAM_FUNC;
int32_t cm_gpio_interrupt_disable(cm_gpio_num_e gpio_num) __RAM_FUNC;



/**
 *  @brief gpio中断服务函数
 *  
 *  @param [in] gpio_num 产生中断的PIN脚
 *  
 *  @return 
 *  @details More details
 */
static void gpio_irq_handle(cm_gpio_num_e gpio_num)
{
    (void)gpio_num;
    /*用户填充*/
    s_cm_gpio_inter_times++;
	cm_gpio_interrupt_disable(CM_DEMO_INTERRUPT_GPIO);
    if(s_cm_gpio_int_sem) osSemaphoreRelease(s_cm_gpio_int_sem);
    return;
}


/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * @brief 读取GPIO电平示例
 * @return  
 *
 * @details More details
 */
void cm_demo_gpio_input(void)
{
    int32_t ret;
	cm_gpio_cfg_t gpio_cfg =
	{
		.mode = CM_GPIO_MODE_INPUT, //输入模式
		.pull = CM_GPIO_PULL_UP, //上拉，根据所选引脚配置
	};
	cm_gpio_level_e level = CM_GPIO_LEVEL_LOW;

	CM_DEMO_GPIO_LOG("cm_demo_gpio_input start!!\n");

	ret = cm_gpio_init(CM_DEMO_INPUT_GPIO, &gpio_cfg);
	if(ret != RET_SUCCESS)
	{
		CM_DEMO_GPIO_LOG("cm_demo_gpio_input cm_gpio_init err :%d\n", ret);
		return;
	}

    cm_gpio_get_level(CM_DEMO_INPUT_GPIO,&level);
    CM_DEMO_GPIO_LOG("GPIO%d read Value:%d!!\n",CM_DEMO_INPUT_GPIO,level);
    osDelay(1000);  
    cm_gpio_deinit(CM_DEMO_INPUT_GPIO);
	CM_DEMO_GPIO_LOG("cm_demo_gpio_input end!!\n");
	return;
}


/**
 * @brief GPIO输出电平示例
 * @return  
 *
 * @details More details
 */
void cm_demo_gpio_output(void)
{
    int32_t ret;

	cm_gpio_cfg_t gpio_cfg =
	{
		.mode = CM_GPIO_MODE_OUTPUT_PP, //输出模式
		.pull = CM_GPIO_PULL_UP, //上拉，根据所选引脚配置
	};

	CM_DEMO_GPIO_LOG("cm_demo_gpio_output start!!\n");

	ret = cm_gpio_init(CM_DEMO_OUTPUT_GPIO, &gpio_cfg);

	if(ret != RET_SUCCESS)
	{
		CM_DEMO_GPIO_LOG("cm_demo_gpio_output cm_gpio_init err :%d\n", ret);
		return;
	}
	cm_gpio_set_level(CM_DEMO_OUTPUT_GPIO, CM_GPIO_LEVEL_HIGH);
    osDelay(1000);  
	cm_gpio_set_level(CM_DEMO_OUTPUT_GPIO, CM_GPIO_LEVEL_LOW);
    osDelay(1000);  
    cm_gpio_deinit(CM_DEMO_OUTPUT_GPIO);

	CM_DEMO_GPIO_LOG("cm_demo_gpio_output end!!\n");
	return;
}


/**
 * @brief GPIO中断示例
 * @return  
 *
 * @details 同一时刻只支持一个GPIO的中断功能。
 */
void cm_demo_gpio_interrupt(void)
{
    int32_t ret;

	cm_gpio_cfg_t gpio_cfg =
	{
		.mode = CM_GPIO_MODE_IT_RISING_FALLING, // 双边沿触发中断模式	
		.pull = CM_GPIO_PULL_UP, //上拉
	};

	CM_DEMO_GPIO_LOG("cm_demo_gpio_interrupt start!!\n");
	//创建信号量
	s_cm_gpio_int_sem = osSemaphoreNew(0xFFFF, 0,NULL);
    cm_assert(s_cm_gpio_int_sem != NULL);

	ret = cm_gpio_init(CM_DEMO_INTERRUPT_GPIO, &gpio_cfg);
	if(ret != RET_SUCCESS)
	{
		CM_DEMO_GPIO_LOG("cm_demo_gpio_interrupt cm_gpio_init err :%d\n", ret);
		return;
	}	
    cm_gpio_interrupt_register(CM_DEMO_INTERRUPT_GPIO,gpio_irq_handle);//中断注册函数
    cm_gpio_interrupt_enable(CM_DEMO_INTERRUPT_GPIO,CM_GPIO_IT_EDGE_BOTH);

    //等待获取信号量，释放线程控制权
    if(osOK == osSemaphoreAcquire(s_cm_gpio_int_sem, osWaitForever))
    {
        //打印中断次数
        CM_DEMO_GPIO_LOG("hal_gpio_interrupt times:%d\n", s_cm_gpio_inter_times);
    }
    cm_gpio_deinit(CM_DEMO_INTERRUPT_GPIO);
    //删除信号量
    osSemaphoreDelete(s_cm_gpio_int_sem);
    s_cm_gpio_int_sem = NULL;

	CM_DEMO_GPIO_LOG("cm_demo_gpio_interrupt end!!\n");

	return;
}

/**
 * @brief GPIO功能示例
 * @return  
 *
 * @details More details
 */

int cm_test_gpio(unsigned char **cmd, int len)
{

	CM_DEMO_GPIO_LOG("cm_demo_gpio start!!\n");
    cm_demo_gpio_input();
    cm_demo_gpio_output();
    cm_demo_gpio_interrupt();
	CM_DEMO_GPIO_LOG("cm_demo_gpio end!!\n");
	return 0;
}



