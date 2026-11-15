/**
 *  @file    custom_main.h
 *  @brief   OpenCPU用户业务
 *  @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/04
 */


#ifndef __CUSTOM_MAIN_H__
#define __CUSTOM_MAIN_H__


#define CM_UNUSED(n) do{(void)n;}while(0)


/**
 *  \brief OpenCPU版本程序入口
 *  
 *  \return 空
 *  
 *  \details 仅用于创建OC线程,请勿修改此函数名
 */
void cm_opencpu_entry(void);

 
#endif
