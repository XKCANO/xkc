#ifndef __755LHA_RELEASE_PT32L031_H
#define __755LHA_RELEASE_PT32L031_H

#include "755LHA_Windows_PT32L031.h"
#include "755LHA_RF_PT32L031.h"
#include "FE_755LHA_EEPROM_PT32L031.h"

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char step;
	unsigned char mode;
	unsigned char count;
	unsigned char reserve;
}Release_typedef;
extern Release_typedef release;

extern FE_755LHA_EEPROM_TypeDef eeprom_data;

/* --------------------------------------------------------------------------- */
void write_eepromdata(void);
void release_network(void);

/* --------------------------------------------------------------------------- */
#endif






