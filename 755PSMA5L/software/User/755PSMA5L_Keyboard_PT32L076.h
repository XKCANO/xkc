#ifndef __755LPSMA5_KEYBOARD_PT32L076_H
#define __755LPSMA5_KEYBOARD_PT32L076_H


#include "PT32x076.h"
#include "755PSMA5L_Timer_PT32L076.h"
#include "755PSMA5L_System_PT32L076.h"
#include "FE_755PSMA5L_SMOKE_PT32L076.h"


/* --------------------------------------------------------------------------- */
#define KEYBOARD_SCANNING_TIME_1 5
#define KEYBOARD_SCANNING_TIME_2 50

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char value;
	unsigned char hold_t;
	unsigned short reserve;
	
	unsigned short h_time;
	unsigned short l_time;

}MULTIPLE_KEY_Tytedef;
extern MULTIPLE_KEY_Tytedef key2;

typedef struct
{
	unsigned char value;
	unsigned char h_time;
	unsigned char l_time;
  unsigned char reserve;
	
}SIMPLE_KEY_Tytedef;
extern SIMPLE_KEY_Tytedef key3;
extern SIMPLE_KEY_Tytedef key4;
extern SIMPLE_KEY_Tytedef key5;

/* --------------------------------------------------------------------------- */
void PA_Handler(void);

void scankey2_process_run(void);
void scankey3_process_run(void);
void scankey4_process_run(void);
void scankey5_process_run(void);

void key3_down_event(void);
void key3_08s_event(void);
void key3_10s_event(void);
void key3_up_event(void);

/* --------------------------------------------------------------------------- */
#endif
