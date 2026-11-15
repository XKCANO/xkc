#include "wcs_windows_m0518.h"
#include "WCS_M0518_DEF.h"



/**
  * @brief    Display Led Management
  * @param[in] data(0-9)
  * @return
  * succeed: 0
  * error: 0xFF
  * @details
  */
void Display_Led_Management(uint8_t mode)
{
  if(mode == 0)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN + LEDF_PIN);
    PD->DOUT |= LEDG_PIN;
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN + LEDE_PIN);
  }
  else if(mode == 1)
  {
    PD->DOUT |= LEDA_PIN + LEDF_PIN + LEDG_PIN;
    PD->DOUT &= ~LEDB_PIN;
    PC->DOUT |= LEDD_PIN + LEDE_PIN;
    PC->DOUT &= ~LEDC_PIN;
  }
  else if(mode == 2)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN + LEDG_PIN);
    PD->DOUT |= LEDF_PIN;
    PC->DOUT &= ~(LEDD_PIN + LEDE_PIN);
    PC->DOUT |= LEDC_PIN;
  }
  else if(mode == 3)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN + LEDG_PIN);
    PD->DOUT |= LEDF_PIN;
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN);
    PC->DOUT |= LEDE_PIN;
  }
  else if(mode == 4)
  {
    PD->DOUT &= ~(LEDB_PIN + LEDF_PIN + LEDG_PIN);
    PD->DOUT |= LEDA_PIN;
    PC->DOUT &= ~LEDC_PIN;
    PC->DOUT |= LEDD_PIN + LEDE_PIN;
  }
  else if(mode == 5)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDF_PIN + LEDG_PIN);
    PD->DOUT |= LEDB_PIN;
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN);
    PC->DOUT |= LEDE_PIN;
    
  }
  else if(mode == 6)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDF_PIN + LEDG_PIN);
    PD->DOUT |= LEDB_PIN;
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN + LEDE_PIN);
  }
  else if(mode == 7)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN);
    PD->DOUT |= LEDF_PIN + LEDG_PIN;
    PC->DOUT &= ~LEDC_PIN;
    PC->DOUT |= LEDD_PIN + LEDE_PIN;
  }
  else if(mode == 8)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN + LEDF_PIN + LEDG_PIN);
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN + LEDE_PIN);
  }
  else if(mode == 9)
  {
    PD->DOUT &= ~(LEDA_PIN + LEDB_PIN + LEDF_PIN + LEDG_PIN);
    PC->DOUT &= ~(LEDC_PIN + LEDD_PIN);
    PC->DOUT |= LEDE_PIN;
  }
}

/**
  * @brief    Display Red Management
  * @param[in] data(0-8)
  * @return     None
  * @details
  */
void Display_Red_Management(uint8_t mode)
{
  if(mode == 0)
  {
    PB->DOUT |= RED1_PIN + RED2_PIN + RED9_PIN + RED10_PIN;
    PF->DOUT |= RED3_PIN + RED4_PIN;
    PA->DOUT |= RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN;
  }
  if(mode == 1)
  {
    PB->DOUT &= ~RED1_PIN;
    PB->DOUT |= RED2_PIN + RED9_PIN + RED10_PIN;
    PF->DOUT |= RED3_PIN + RED4_PIN;
    PA->DOUT |= RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN;
  }
  else if(mode == 2)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT |= RED3_PIN + RED4_PIN;
    PA->DOUT |= RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN;
  }
  else if(mode == 3)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~RED3_PIN;
    PF->DOUT |= RED4_PIN;
    PA->DOUT |= RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN;
  }
  else if(mode == 4)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT |= RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN;
  }
  else if(mode == 5)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~RED5_PIN;
    PA->DOUT |= RED6_PIN + RED7_PIN + RED8_PIN;
  }
  else if(mode == 6)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~(RED5_PIN + RED6_PIN);
    PA->DOUT |= RED7_PIN + RED8_PIN;
  }
  else if(mode == 7)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~(RED5_PIN + RED6_PIN + RED7_PIN);
    PA->DOUT |= RED8_PIN;
  }
  else if(mode == 8)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN);
    PB->DOUT |= RED9_PIN + RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~(RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN);
  }
  else if(mode == 9)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN + RED9_PIN);
    PB->DOUT |= RED10_PIN;
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~(RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN);
  }
  else if(mode == 10)
  {
    PB->DOUT &= ~(RED1_PIN + RED2_PIN + RED9_PIN + RED10_PIN);
    PF->DOUT &= ~(RED3_PIN + RED4_PIN);
    PA->DOUT &= ~(RED5_PIN + RED6_PIN + RED7_PIN + RED8_PIN);
  }
}




