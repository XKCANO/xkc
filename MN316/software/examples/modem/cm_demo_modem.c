/**
 * @file    cm_demo_modem.c
 * @brief   OpenCPU MODEM相关使用示例
 * @copyright copyright © 2021 China Mobile IOT. All rights reserved.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "cm_demo_common.h"

/**
 *  @brief PSM状态回调函数
 *  
 *  @param [in] state PSM状态 0:进入PSM 1:退出PSM
 *  
 *  @return 
 *  @details More details
 */
static void __cm_demo_get_psm_state(char state)
{
    cm_demo_printf("psm_state: %d\n", state);
}


/**
 * @brief MODEM get测试
 *  
 * @return 成功返回0，失败返回-1
 *  
 * @details
 */
int cm_test_modem_get(unsigned char **cmd, int len)
{

    int cfun = -1;
    int pdp_state = -1;
    int cscon = -1;
    
    char cgmm[CM_CGMM_LEN] = {0};
    char cgmi[CM_CGMI_LEN] = {0};
    char rssi = 0;
    char ber = 0;

    cm_cops_info_t cops_info = {0};
    cm_cereg_state_t cereg_state = {0};
    cm_radio_info_t radio_info = {0};
    cm_cell_info_t cell_info[3] = {0};
    cm_edrx_cfg_get_t edrx_cfg_get = {0};
    cm_psm_cfg_t psm_cfg = {0};

    cfun = cm_modem_get_cfun();
    pdp_state = cm_modem_get_pdp_state(0);
    cscon = cm_modem_get_cscon();
    
    cm_modem_get_cgmm(cgmm);
    cm_modem_get_cgmi(cgmi);
    cm_modem_get_cops(&cops_info);
    cm_modem_get_csq(&rssi, &ber);
    cm_modem_get_cereg_state(&cereg_state);
    cm_modem_get_radio_info(&radio_info);
    cm_modem_get_cell_info(cell_info, 3);
    cm_modem_get_edrx_cfg(&edrx_cfg_get);
    cm_modem_get_psm_cfg(&psm_cfg);

    cm_demo_printf("cfun: %d\n", cfun);
    cm_demo_printf("pdp: %d\n", pdp_state);
    cm_demo_printf("cscon: %d\n", cscon);
    cm_demo_printf("CGMM: %s\n", cgmm);
    cm_demo_printf("CGMI: %s\n", cgmi);
    cm_demo_printf("mode: %d\n", cops_info.mode);
    cm_demo_printf("format: %d\n", cops_info.format);
    cm_demo_printf("oper: %s\n", cops_info.oper);
    cm_demo_printf("act: %d\n", cops_info.act);
    cm_demo_printf("rssi: %d\n", rssi);
    cm_demo_printf("ber: %d\n", ber);

    cm_demo_printf("cereg ---\n");
    cm_demo_printf("n: %d\n", cereg_state.n);
    cm_demo_printf("state: %d\n", cereg_state.state);
    cm_demo_printf("lac: %d\n", cereg_state.lac);
    cm_demo_printf("ci: %d\n", cereg_state.ci);
    cm_demo_printf("act: %d\n", cereg_state.act);
    cm_demo_printf("rac: %d\n", cereg_state.rac);
    cm_demo_printf("cause_type: %d\n", cereg_state.cause_type);
    cm_demo_printf("reject_cause: %d\n", cereg_state.reject_cause);
    cm_demo_printf("active_time: %d\n", cereg_state.active_time);
    cm_demo_printf("periodic_tau: %d\n", cereg_state.periodic_tau);

    cm_demo_printf("radio ---\n");
    cm_demo_printf("rsrp: %d\n", radio_info.rsrp);
    cm_demo_printf("rsrq: %d\n", radio_info.rsrq);
    cm_demo_printf("rssi: %d\n", radio_info.rssi);
    cm_demo_printf("rxlev: %d\n", radio_info.rxlev);
    cm_demo_printf("tx_power: %d\n", radio_info.tx_power);
    cm_demo_printf("tx_time: %d\n", radio_info.tx_time);
    cm_demo_printf("rx_time: %d\n", radio_info.rx_time);
    cm_demo_printf("last_cellid: %d\n", radio_info.last_cellid);
    cm_demo_printf("last_ecl: %d\n", radio_info.last_ecl);
    cm_demo_printf("last_snr: %d\n", radio_info.last_snr);
    cm_demo_printf("last_earfcn: %d\n", radio_info.last_earfcn);
    cm_demo_printf("last_pci: %d\n", radio_info.last_pci);

    cm_demo_printf("cell ---\n");
    cm_demo_printf("primary_cell: %d\n", cell_info[0].primary_cell); 
    cm_demo_printf("earfcn: %d\n", cell_info[0].earfcn); 
    cm_demo_printf("pci: %d\n", cell_info[0].pci); 
    cm_demo_printf("rsrp: %d\n", cell_info[0].rsrp); 
    cm_demo_printf("rsrq: %d\n", cell_info[0].rsrq); 
    cm_demo_printf("rssi: %d\n", cell_info[0].rssi); 
    cm_demo_printf("snr: %d\n", cell_info[0].snr); 

    cm_demo_printf("edrx ---\n");
    cm_demo_printf("act_type: %d\n", edrx_cfg_get.act_type); 
    cm_demo_printf("edrx_value: %d\n", edrx_cfg_get.edrx_value); 
    cm_demo_printf("paging_time_window: %d\n", edrx_cfg_get.paging_time_window); 

    cm_demo_printf("psm ---\n");
    cm_demo_printf("mode: %d\n", psm_cfg.mode); 
    cm_demo_printf("periodic_tau: %d\n", psm_cfg.periodic_tau); 
    cm_demo_printf("active_time: %d\n", psm_cfg.active_time); 

    return 0;
}


/**
 * @brief MODEM set测试
 *  
 * @return 成功返回0，失败返回-1
 *  
 * @details
 */
int cm_test_modem_set(unsigned char **cmd, int len)
{

    static int flag = 0;
    cm_edrx_cfg_set_t edrx_cfg_set = {0};
    cm_psm_cfg_t psm_cfg = {0};
    int ret;

	ret = cm_modem_set_cfun(0);
	cm_demo_printf("set cfun=1 ret: %d\n", ret);	
	ret = cm_modem_clear_storge_earfcn();
	cm_demo_printf("clear storge earfcn ret: %d\n", ret); 	
	ret = cm_modem_set_cfun(1);
	cm_demo_printf("set cfun=0 ret: %d\n", ret);
	ret = cm_modem_psm_state_open();
	cm_demo_printf("cm_modem_psm_state_open ret: %d\n", ret);
	cm_modem_psm_state_register(__cm_demo_get_psm_state);

    if(flag == 1)
    {
        edrx_cfg_set.mode = 1;
        edrx_cfg_set.act_type = 5;
        edrx_cfg_set.edrx_value = 5;
        edrx_cfg_set.paging_time_window = 7;
        cm_modem_set_edrx_cfg(&edrx_cfg_set);

        psm_cfg.mode = 1;
        psm_cfg.periodic_tau = 129;
        psm_cfg.active_time = 7;
        cm_modem_set_psm_cfg(&psm_cfg);

        flag = 0;
    }
    else
    {
        edrx_cfg_set.mode = 0;
        edrx_cfg_set.act_type = 5;
        edrx_cfg_set.edrx_value = 12;
        edrx_cfg_set.paging_time_window = 8;
        cm_modem_set_edrx_cfg(&edrx_cfg_set);

        psm_cfg.mode = 0;
        psm_cfg.periodic_tau = 55;
        psm_cfg.active_time = 22;
        cm_modem_set_psm_cfg(&psm_cfg);

       flag = 1;
    }

    cm_demo_printf("test modem set done.\n");

    return 0;
}

