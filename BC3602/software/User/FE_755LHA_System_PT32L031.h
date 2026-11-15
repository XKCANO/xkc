/*
* Copyright (c) 2008, XingLan Technology
* File name : NUC1xx_System_api.H
* Version: 0.6
* 32bit MCU : NUC1xx
* Cortex: Cortex-M0
* Compiler: 
*   Keil ARM 4.11 Compiler
*   IAR  ARM 5.40 Compiler
*
* Author : Tom (pengfengboy@163.com)
*
* Description : 
* 	1:initialize the system clock module
* 	2:initialize the GPIO module
*
* History :
* 	02/18/2011 : adds the SetSystem function.
*
*/
#ifndef __FE_755LHA_SYSTEM_PT32L031_H
#define __FE_755LHA_SYSTEM_PT32L031_H

#include "FE_755LHA_CFG.h"

/* --------------------------------------------------------------------------- */
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);
void spi_enable_cfg(unsigned char mode);
/* --------------------------------------------------------------------------- */
#endif
