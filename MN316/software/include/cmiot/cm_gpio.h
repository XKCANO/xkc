/**
 * @file        cm_gpio.h
 * @brief       GPIO驱动接口
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By tw
 * @date        2021/05/18
 *  
 * @defgroup gpio gpio
 * @ingroup PI
 * @{
 */

#ifndef __CM_GPIO_H__
#define __CM_GPIO_H__


/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "cm_common.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/

/*  GPIO引脚号*/  
typedef enum {
	CM_GPIO_NUM_0 = 0,
	CM_GPIO_NUM_1,
	CM_GPIO_NUM_2,
	CM_GPIO_NUM_3,
	CM_GPIO_NUM_4,
	CM_GPIO_NUM_5,
	CM_GPIO_NUM_6,
	CM_GPIO_NUM_7,
	CM_GPIO_NUM_8,
	CM_GPIO_NUM_9,
	CM_GPIO_NUM_10,
	CM_GPIO_NUM_11,
	CM_GPIO_NUM_12,
	CM_GPIO_NUM_13,
	CM_GPIO_NUM_14,
	CM_GPIO_NUM_15,
	CM_GPIO_NUM_16,
    CM_GPIO_NUM_MAX
} cm_gpio_num_e;


/* GPIO上拉下拉状态 */
typedef enum {
    CM_GPIO_PULL_NONE,/*!< 无上下拉  */
    CM_GPIO_PULL_DOWN,/*!< 下拉  */
    CM_GPIO_PULL_UP,/*!< 上拉     */
} cm_gpio_pull_e;

/** I/O方向 */
typedef enum{
    CM_GPIO_DIRECTION_INPUT, /*!< 普通GPIO输入模式		*/
    CM_GPIO_DIRECTION_OUTPUT, /*!< 普通GPIO输出模式		*/
    CM_GPIO_DIRECTION_INPUT_OUTPUT, /*!< 输入输出模式		*/
    CM_GPIO_DIRECTION_HIGH_IMPEDANCE, /*!< 功能模式，高阻抗	*/
} cm_gpio_direction_e;


/** 边沿+电平触发 */
typedef enum
{      
    CM_GPIO_IT_EDGE_FALLING,    
    CM_GPIO_IT_EDGE_BOTH,    
    CM_GPIO_IT_LEVEL_HIGH,    
 } cm_gpio_interrupt_e;

/* GPIO工作模式 */
typedef enum 
{
//输入模式
    CM_GPIO_MODE_INPUT,/*!< 普通GPIO输入模式		*/
    CM_GPIO_MODE_INOUT,/*!< 输入输出模式	*/
//输出模式
    CM_GPIO_MODE_OUTPUT_PP,/*!< 推挽输出模式	*/
//中断模式
    CM_GPIO_MODE_IT_FALLING,/*!< 下降沿外部中断模式	*/
    CM_GPIO_MODE_IT_RISING_FALLING,/*!< 双边沿触发中断模式	*/
    CM_GPIO_MODE_IT_HIGH_LEVEL,/*!< 高电平外部中断模式	*/
    CM_GPIO_MODE_NUM/*!<可用 工作模式数量*/
} cm_gpio_mode_e;

/**  GPIO工输出电平 */
typedef enum{
    CM_GPIO_LEVEL_LOW, /*!< GPIO 低电平状态 */
    CM_GPIO_LEVEL_HIGH, /*!< GPIO 高电平状态 */
} cm_gpio_level_e;

/** 命令码 */
typedef enum
{
    CM_GPIO_CMD_SET_PULL,/*!< 上下拉设置命令码*/
    CM_GPIO_CMD_SET_LEVEL,/*!< 驱动能力设置命令码*/
    CM_GPIO_CMD_SET_DIRECTION,/*!< 输入输出设置命令码*/
} cm_gpio_cmd_e;


/** 配置 */
typedef struct{
    cm_gpio_mode_e mode; /*!< GPIO工作模式 */
	cm_gpio_direction_e direction;/*!< I/O方向 */
    cm_gpio_pull_e pull; /*!< GPIO上下拉模式 */
} cm_gpio_cfg_t;


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


/**
 *  @brief 初始化GPIO
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  @param [in] cfg 配置
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details （1）GPIO0、5、14默认状态为输入下拉；
 *           （2）GPIO0、5、14仅支持下拉，其他GPIO仅支持上拉；
 * 
 */
int32_t cm_gpio_init(cm_gpio_num_e gpio_num, cm_gpio_cfg_t *cfg);


/**
 *  @brief 去初始化
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_gpio_deinit(cm_gpio_num_e gpio_num);


/**
 * @brief 配置GPIO输出电平
 *
 *	\param [in] gpio_num   待操作的PIN脚
 *	\param [in] level 输出电平
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_gpio_set_level(cm_gpio_num_e gpio_num, cm_gpio_level_e level);
	

/**
 * @brief 读取GPIO输入电平
 *
 * @param [in] gpio_num   待操作的PIN脚
 * @param [out] level 输入电平
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_gpio_get_level(cm_gpio_num_e gpio_num, cm_gpio_level_e *level);


/**
 *  @brief 设置上/下拉
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  @param [in] type 上下拉配置
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_gpio_set_pull(cm_gpio_num_e gpio_num, cm_gpio_pull_e type);


/**
 * @brief I/O方向模式配置
 *
 * @param [in]  gpio_num 引脚号
 * @param [in]  dir 输入/输出/高阻态
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details More details
 */
int32_t cm_gpio_set_direction(cm_gpio_num_e gpio_num, cm_gpio_direction_e dir);


/**
 *  @brief 注册中断回调函数
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  @param [in] interrupt_cb 中断回调函数
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details 中断服务程序及内部调用接口，必须使用编译器参数加载至内存中运行！！！ 
 */
int32_t cm_gpio_interrupt_register(cm_gpio_num_e gpio_num, void *interrupt_cb);
	

/**
 *  @brief 使能中断
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  @param [in] intr_mode 中断触发方式
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_gpio_interrupt_enable(cm_gpio_num_e gpio_num,cm_gpio_interrupt_e intr_mode);


/**
 *  @brief 失能中断
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details More details
 */
int32_t cm_gpio_interrupt_disable(cm_gpio_num_e gpio_num);


/**
 *  @brief GPIO控制
 *  
 *  @param [in] gpio_num GPIO引脚ID
 *  @param [in] cmd 命令码
 *  @param [in] arg 命令
 *  
 *  @return 
 *    = 0 - 成功 
 *    < 0 - 失败, 返回值为错误码
 *  
 *  @details 根据不同的cmd值（命令码），arg参数类型须对应配置。\n
 *  cmd = \ref GPIO_CMD_SET_PULL, arg传入\ref cm_gpio_pull_e *               \n
 *  cmd = \ref GPIO_CMD_SET_LEVEL, arg传入\ref cm_gpio_level_e *             \n
 *  cmd = \ref GPIO_CMD_SET_DIRECTION, arg传入\ref cm_gpio_direction_e *     \n
 */
int32_t cm_gpio_ioctl(cm_gpio_num_e gpio_num, int32_t cmd, void *arg);

#undef EXTERN
#ifdef __cplusplus
}
#endif


#endif /* __CM_GPIO_H__ */

/** @}*/