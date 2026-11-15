/**
 *  @file    cm_demo_common.h
 *  @brief   OpenCPU示例头文件
 *  @copyright copyright ? 2021 China Mobile IOT. All rights reserved.
 *  @author by ZXW
 *  @date 2021/06/11
 */


#ifndef __CM_DEMO_COMMONH__
#define __CM_DEMO_COMMON_H__


#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "cm_mem.h"
#include "cm_pm.h"
#include "cm_sys.h"
#include "cm_sim.h"
#include "cm_modem.h"
#include "cm_rtc.h"
#include "cm_os.h"


int cm_test_adc(unsigned char **cmd, int len);
int cm_test_modem_get(unsigned char **cmd, int len);
int cm_test_modem_set(unsigned char **cmd, int len);
int cm_test_sys_sim_mem(unsigned char **cmd, int len);
int cm_test_i2c(unsigned char **cmd, int len);
int cm_test_spi(unsigned char **cmd, int len);
int cm_test_gpio(unsigned char **cmd, int len);
int cm_test_flash(unsigned char **cmd, int len);
int cm_test_dns(unsigned char **cmd, int len);
int cm_test_tcp(unsigned char **cmd, int len);
int cm_test_udp(unsigned char **cmd, int len);
void cm_test_onenet(unsigned char **cmd, int len);
void cm_test_onenet_fota(unsigned char **cmd, int len);
int cm_test_os(unsigned char **cmd, int len);
int cm_test_rtc_timer(unsigned char **cmd, int len);
int cm_test_soft_timer(unsigned char **cmd, int len);
void cm_test_ctwing(unsigned char **cmd, int len);
void cm_test_asocket_cmd(unsigned char **cmd, int len);
int cm_test_uart(unsigned char **cmd, int len);
void cm_test_ota(unsigned char **cmd, int len);
void cm_test_http(unsigned char **cmd, int len);
void cm_test_mqtt(unsigned char **cmd,int len);

int open_uart(int devno);
void cm_demo_printf(const char* fmt, ...);
int test_asocket_init(void);
void cm_test_pwm(unsigned char **cmd, int len);
void cm_test_reboot(unsigned char **cmd, int len);
void cm_test_sleep(unsigned char **cmd, int len);
void cm_test_pm_mode(unsigned char **cmd, int len);
void cm_test_unicom(unsigned char **cmd, int len);

#endif
