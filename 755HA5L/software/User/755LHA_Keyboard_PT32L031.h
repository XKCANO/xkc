#ifndef __755LHA_KEYBOARD_PT32L031_H
#define __755LHA_KEYBOARD_PT32L031_H


#include "pt32x031.h"
#include "755LHA_DEF.h"


/* --------------------------------------------------------------------------- */
#define KEYBOARD_SCANNING_TIME_1 5
#define KEYBOARD_SCANNING_TIME_2 50

/* --------------------------------------------------------------------------- */
typedef struct
{
	unsigned char count;
	unsigned char count1;
	
	unsigned char step;
	unsigned char mode;
		
}KEY_Event_Typedef;
extern KEY_Event_Typedef check_fre;

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

/* --------------------------------------------------------------------------- */
void keyfrequency_check(void);
void scankey2_process_run(void);
void scankey3_process_run(void);
void key3_down_event(void);
void key3_08s_event(void);
void key3_10s_event(void);
void key3_up_event(void);

/* --------------------------------------------------------------------------- */
#endif
