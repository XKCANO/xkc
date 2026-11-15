#ifndef __755LHA_RF_PT32L031_H
#define __755LHA_RF_PT32L031_H


#include "pt32x031.h"
#include "FE_IO.h"
#include "755LHA_DEF.h"
#include "FE_755LHA_MAC.h"
#include "FE_PHY_BC3602.h"
#include "FE_SPI_PT32L031.h"
#include "755LHA_Release_PT32L031.h"

/* --------------------------------------------------------------------------- */
enum
{
	NETWORK_APPLY = 0,
	MASTER_ACK,
	SLAVE_ACK,
};

/* --------------------------------------------------------------------------- */
//flag
#define  MASTER_RESPONSE_FLAG_POS  0
#define  MASTER_RESPONSE_FLAG_MSK  (1UL << MASTER_RESPONSE_FLAG_POS)

#define  SLAVE_RESPONSE_FLAG_POS  1
#define  SLAVE_RESPONSE_FLAG_MSK  (1UL << SLAVE_RESPONSE_FLAG_POS)

#define  SLAVE_PAIRING_SUCCEED_FLAG_POS  2
#define  SLAVE_PAIRING_SUCCEED_FLAG_MSK  (1UL << SLAVE_PAIRING_SUCCEED_FLAG_POS)

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char data[16];
	
	unsigned char syncword[4];
	
	unsigned char tx_mode;
	unsigned char tx_power;
	unsigned char step;
	unsigned char mode;
	
	unsigned char count;
	unsigned char flag;
	unsigned char cmd;
	unsigned char reserve;
}typedef_pair;
extern typedef_pair pair;

/* --------------------------------------------------------------------------- */
void rf_pairing_process_run(void);
void mac_callback(uint32_t cmd);
void PhyCallback(unsigned char *p, uint32_t l);

/* --------------------------------------------------------------------------- */
#endif

