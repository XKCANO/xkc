/*
 * Copyright (c) 2019, Future Eagle Technology
 * File name : FE_755LHA_CFG.H
 * Version : 0.1
 * 32bit MCU : PT32L031
 * Cortex : Cortex-M0
 *
 * Compiler : 
 *   Keil ARM 5.18 Compiler
 *
 * Pack:
 *   PAI-IC.PT32X031_DFP.1.0.6
 *
 * Author : 
 *   Tang
 *
 * Description : 
 *   755LHA 宏定义头文件
 *
 * History :
 * 	2024-6-4: 初版发布
 *
 */
#ifndef __FE_755LHA_CFG_H
#define __FE_755LHA_CFG_H
/* --------------------------------------------------------------------------- */
#define GPIO_MODER_MODE         		((uint32_t)0x00000003U)
#define GPIO_MODER_MODE_0        		((uint32_t)0x00000001U)
#define GPIO_MODER_MODE_1        		((uint32_t)0x00000002U)
#define GPIO_MODER_INPUT_MODE				((uint32_t)0x00000000U)	//Input mode
#define GPIO_MODER_OUTPUT_MODE			((uint32_t)0x00000001U)	//General purpose output mode
#define	GPIO_MODER_ALTERNATE_MODE		((uint32_t)0x00000002U)	//Alternate function mode
#define	GPIO_MODER_ANALOG_MODE			((uint32_t)0x00000003U)	//Analog mode (reset state)
/* --------------------------------------------------------------------------- */
#define	GPIO_OSPEEDER_OSPEED_VLS		((uint32_t)0x00000000U)	//Very low speed
#define GPIO_OSPEEDER_OSPEED_LS			((uint32_t)0x00000001U)	//Low speed
#define	GPIO_OSPEEDER_OSPEED_MS			((uint32_t)0x00000002U)	//Medium speed
#define	GPIO_OSPEEDER_OSPEED_HS			((uint32_t)0x00000003U)	//High speed
/* --------------------------------------------------------------------------- */
#define GPIO_PUPDR_PUPD_MODE  ((uint32_t)0x00000003U)
#define	GPIO_PUPDR_PUPD_NO		((uint32_t)0x00000000U)	//No pull-up, pull-down
#define GPIO_PUPDR_PUPD_PU		((uint32_t)0x00000001U)	//Pull-up
#define	GPIO_PUPDR_PUPD_PD		((uint32_t)0x00000002U)	//Pull-down
/* --------------------------------------------------------------------------- */
#define	GPIO_PIN0			0
#define	GPIO_PIN1			1
#define	GPIO_PIN2			2
#define	GPIO_PIN3			3
#define	GPIO_PIN4			4
#define	GPIO_PIN5			5
#define	GPIO_PIN6			6
#define	GPIO_PIN7			7
#define	GPIO_PIN8			8
#define	GPIO_PIN9			9
#define	GPIO_PIN10		10
#define	GPIO_PIN11		11
#define	GPIO_PIN12		12
#define	GPIO_PIN13		13
#define	GPIO_PIN14		14
#define	GPIO_PIN15		15
/* --------------------------------------------------------------------------- */
#define GPIO_AF_0            ((uint8_t)0x01)
#define GPIO_AF_1            ((uint8_t)0x02)
#define GPIO_AF_2            ((uint8_t)0x03)
#define GPIO_AF_3            ((uint8_t)0x04)
#define GPIO_AF_4            ((uint8_t)0x05)
#define GPIO_AF_5            ((uint8_t)0x06)
#define GPIO_AF_6            ((uint8_t)0x06) 
/* --------------------------------------------------------------------------- */
/*
!< Uncomment the following line if you need to relocate your vector Table in Internal SRAM. 
*/
//#define VECT_TAB_SRAM
/*
!< Vector Table base offset field. This value must be a multiple of 0x200. 
*/
#define VECT_TAB_OFFSET  0x00 
/* --------------------------------------------------------------------------- */
#endif
