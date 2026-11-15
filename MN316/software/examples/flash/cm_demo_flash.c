/**
 * @file        cm_demo_flash.c
 * @brief       OpenCPU flash接口测试例程
 * @copyright   Copyright @2021 China Mobile IOT. All rights reserved.
 */

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include "cm_flash.h"
#include "cm_common.h"
#include "cm_os.h"
#include "cm_mem.h"



/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define CM_DEMO_FLASH_LOG     CM_DEMO_LOG


/****************************************************************************
 * Private Types
 ****************************************************************************/


 
/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Data
 ****************************************************************************/
 
 
/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * @brief  Flash读写擦除示例
 *
 * @return  void
 *
 * @details More details
 */
int cm_test_flash(unsigned char **cmd, int len)
{

    char test_str[] = "Hello world!";
    uint32_t test_len = sizeof(test_str);
    
    char* read_str = (char*)cm_malloc(test_len);
    memset(read_str, 0, test_len);

	CM_DEMO_FLASH_LOG("flash test start!!\n");
    //数据写入
    int32_t ret =  cm_flash_write(0, test_str, test_len);
    osDelay(100);
    CM_DEMO_FLASH_LOG("w_ret:%d\n", ret);

    //数据读出
    ret = cm_flash_read(0,(void * )read_str,test_len);
    osDelay(100);
    CM_DEMO_FLASH_LOG("r_ret:%d\n", ret);

    CM_DEMO_FLASH_LOG("read_str:%s\n", read_str);

    cm_free(read_str);

    ret = cm_flash_erase(1,1);
	if(ret != RET_SUCCESS)
	{
		CM_DEMO_FLASH_LOG("cm_flash_erase err %08x\n", (uint32_t)ret);
		return -1;
	}

	CM_DEMO_FLASH_LOG("flash test end!!\n");

    return 0;
}



