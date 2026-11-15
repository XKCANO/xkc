/**
 * @file    cm_demo_sys.c
 * @brief   OpenCPU SYS相关使用示例
 * @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "cm_demo_common.h"

/**
 * @brief SYS测试
 *  
 * @return 成功返回0，失败返回-1
 *  
 * @details
 */
int cm_test_sys_sim_mem(unsigned char **cmd, int len)
{

    int  cpin = -1;
    char imei[CM_IMEI_LEN] = {0};
    char imsi[CM_IMSI_LEN] = {0};
    char iccid[CM_ICCID_LEN] = {0};
    char sn[CM_SN_LEN] = {0};
    char cm_ver[CM_VER_LEN] = {0};
    char base_ver[CM_VER_LEN] = {0};
    cm_storage_stats_t storage_states = {0};
    cm_heap_stats_t heap_states = {0};

    cpin = cm_sim_get_cpin();
    cm_sys_get_imei(imei);
    cm_sim_get_imsi(imsi);
    cm_sim_get_iccid(iccid);
    cm_sys_get_sn(sn);
    cm_sys_get_cm_ver(cm_ver, sizeof(cm_ver));
    cm_sys_get_base_ver(base_ver, sizeof(base_ver));
    cm_sys_get_storage_stats(&storage_states);
    cm_mem_get_heap_stats(&heap_states);

    cm_demo_printf("CPIN: %d\n", cpin);
    cm_demo_printf("IMEI: %s\n", imei);
    cm_demo_printf("IMSI: %s\n", imsi);
    cm_demo_printf("ICCID: %s\n", iccid);
    cm_demo_printf("SN: %s\n", sn);
    cm_demo_printf("CM_VER: %s\n", cm_ver);
    cm_demo_printf("BASE_VER: %s\n", base_ver);

    cm_demo_printf("storage ---\n");
    cm_demo_printf("flash_total_size: %d\n", storage_states.flash_total_size);
    cm_demo_printf("flash_allocated: %d\n", storage_states.flash_allocated);
    cm_demo_printf("flash_remain: %d\n", storage_states.flash_remain);
    cm_demo_printf("ram_total_size: %d\n", storage_states.ram_total_size);
    cm_demo_printf("ram_allocated: %d\n", storage_states.ram_allocated);
    cm_demo_printf("ram_remain: %d\n", storage_states.ram_remain);
    cm_demo_printf("data_used: %d\n", storage_states.data_used);
    cm_demo_printf("text_used: %d\n", storage_states.text_used);
    cm_demo_printf("bss_used: %d\n", storage_states.bss_used);

    cm_demo_printf("heap ---\n");
    cm_demo_printf("total_size: %d\n", heap_states.total_size);
    cm_demo_printf("allocated: %d\n", heap_states.allocated);
    cm_demo_printf("free: %d\n", heap_states.free);
    cm_demo_printf("max_continuity_free: %d\n", heap_states.max_continuity_free);
    cm_demo_printf("allocated_peak: %d\n", heap_states.allocated_peak);
    cm_demo_printf("allocated_times: %d\n", heap_states.allocated_times);
    cm_demo_printf("free_times: %d\n", heap_states.free_times);

    char *malloc_test = cm_malloc(5);
    cm_free(malloc_test);

    return 0;
}


