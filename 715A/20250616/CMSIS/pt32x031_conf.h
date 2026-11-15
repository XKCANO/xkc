/**
  ******************************************************************************
  * @file    pt32x031.h
  * @author  应用开发团队
  * @version V1.0.0
  * @date    2020/04/28
  * @brief   
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *          
  *
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PT32x031_CONF_H
#define __PT32x031_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Comment the line below to disable peripheral header file inclusion */
#include "pt32x031_adc.h"
#include "pt32x031_ana.h"
#include "pt32x031_beep.h"
#include "pt32x031_flash.h"
#include "pt32x031_gpio.h"
#include "pt32x031_cmp_opa.h"
#include "pt32x031_pwr.h"
#include "pt32x031_spi.h"
#include "pt32x031_syscfg.h"
#include "pt32x031_tim.h"
#include "pt32x031_pwm.h"
#include "pt32x031_uart.h"
#include "pt32x031_wdg.h"
#include "pt32x031_led.h"
#include "pt32x031_misc.h"
#include "pt32x031_sys.h"
#include "pt32x031_serial.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
//#define USE_FULL_ASSERT    1 

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __PT32x031_CONF_H */

/************************ (C) COPYRIGHT PENGPAI Microelectronics *****END OF FILE****/
