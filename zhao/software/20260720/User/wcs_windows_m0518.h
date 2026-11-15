#ifndef __WCS_WINDOWS_M0518_H__
#define __WCS_WINDOWS_M0518_H__


#include "M0518.h"

//PB8 -> RED1
#define RED1_PIN 0x0100
#define RED1_ON  PB->DOUT &= ~RED1_PIN
#define RED1_OFF PB->DOUT |= RED1_PIN

//PB12 -> RED2
#define RED2_PIN 0x1000
#define RED2_ON  PB->DOUT &= ~RED2_PIN
#define RED2_OFF PB->DOUT |= RED2_PIN

//PF5 -> RED3
#define RED3_PIN 0x0020
#define RED3_ON  PF->DOUT &= ~RED3_PIN
#define RED3_OFF PF->DOUT |= RED3_PIN

//PF4 -> RED4
#define RED4_PIN 0x0010
#define RED4_ON  PF->DOUT &= ~RED4_PIN
#define RED4_OFF PF->DOUT |= RED4_PIN

//PA11 -> RED5
#define RED5_PIN 0x0800
#define RED5_ON  PA->DOUT &= ~RED5_PIN
#define RED5_OFF PA->DOUT |= RED5_PIN

//PA10 -> RED6
#define RED6_PIN 0x0400
#define RED6_ON  PA->DOUT &= ~RED6_PIN
#define RED6_OFF PA->DOUT |= RED6_PIN

//PA9 -> RED7
#define RED7_PIN 0x0200
#define RED7_ON  PA->DOUT &= ~RED7_PIN
#define RED7_OFF PA->DOUT |= RED7_PIN

//PA8 -> RED8
#define RED8_PIN 0x0100
#define RED8_ON  PA->DOUT &= ~RED8_PIN
#define RED8_OFF PA->DOUT |= RED8_PIN

//PB4 -> RED9
#define RED9_PIN 0x0010
#define RED9_ON  PB->DOUT &= ~RED9_PIN
#define RED9_OFF PB->DOUT |= RED9_PIN

//PB5 -> RED10
#define RED10_PIN 0x0020
#define RED10_ON  PB->DOUT &= ~RED10_PIN
#define RED10_OFF PB->DOUT |= RED10_PIN


//PD7 -> LEDA
#define LEDA_PIN 0x0080
#define LEDA_ON  PD->DOUT &= ~LEDA_PIN
#define LEDA_OFF PD->DOUT |= LEDA_PIN

//PD6 -> LEDB
#define LEDB_PIN 0x0040
#define LEDB_ON  PD->DOUT &= ~LEDB_PIN
#define LEDB_OFF PD->DOUT |= LEDB_PIN

//PC1 -> LEDC
#define LEDC_PIN 0x0002
#define LEDC_ON  PC->DOUT &= ~LEDC_PIN
#define LEDC_OFF PC->DOUT |= LEDC_PIN

//PC2 -> LEDD
#define LEDD_PIN 0x0004
#define LEDD_ON  PC->DOUT &= ~LEDD_PIN
#define LEDD_OFF PC->DOUT |= LEDD_PIN

//PC3 -> LEDE
#define LEDE_PIN 0x0008
#define LEDE_ON  PC->DOUT &= ~LEDE_PIN
#define LEDE_OFF PC->DOUT |= LEDE_PIN

//PD15 -> LEDF
#define LEDF_PIN 0x8000
#define LEDF_ON  PD->DOUT &= ~LEDF_PIN
#define LEDF_OFF PD->DOUT |= LEDF_PIN

//PD14 -> LEDG
#define LEDG_PIN 0x4000
#define LEDG_ON  PD->DOUT &= ~LEDG_PIN
#define LEDG_OFF PD->DOUT |= LEDG_PIN



void Display_Led_Management(uint8_t mode);
void Display_Red_Management(uint8_t mode);



#endif



