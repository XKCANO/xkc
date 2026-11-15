/**
 * @file        cm_adc.h
 * @brief       ADC设备接口
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 * @author      By tw
 * @date        2021/03/18
 *  
 * @defgroup adc adc
 * @ingroup PI
 * @{
 */

#ifndef __CM_ADC_H__
#define __CM_ADC_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/****************************************************************************
 * Public Types
 ****************************************************************************/

/**
 *  @brief ADC 通道，一共1个通道
 */
typedef enum
{
    CM_ADC_0 = 0,   /*!< ADC0 */ 
    CM_ADC_NUM, /*!< ADC设备个数 */
} cm_adc_dev_e;


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
 * @brief 开启ADC设备
 *
 * @param [in] dev ADC设备ID
 *
 * @return  
 *   = 0  - 成功 \n
 *   < 0  - 失败, 返回值为错误码
 *
 * @details 使ADC设备进入工作状态(开启ADC设备电源和时钟等)
 */
int32_t cm_adc_open(cm_adc_dev_e dev);

/**
 * @brief 关闭ADC设备
 *
 * @param [in] dev ADC设备ID
 *
 * @details 使ADC设备进入关闭状态(关闭ADC设备电源和时钟等)
 */
void cm_adc_close(cm_adc_dev_e dev);


/**
 * @brief 读取ADC电压
 *
 * @param [in]  dev ADC设备ID
 * @param [out] voltage 电压值, 单位: mv
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details 通过ADC设备读取测量电压值
 */
int32_t cm_adc_read(cm_adc_dev_e dev, int32_t *voltage);


/**
 * @brief 读取VBAT电压
 *
 * @param [out] voltage 电压值, 单位: mv
 *
 * @return  
 *   = 0  - 成功.
 *   < 0  - 失败, 返回值为错误码.
 *
 * @details 通过ADC通道读取VBAT(电池)电压值，使用时会占用ADC通道，ADC开启时无法使用
 */
int32_t cm_adc_vbat_read(uint32_t *voltage);



#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __CM_ADC_H__ */


/** @}*/
