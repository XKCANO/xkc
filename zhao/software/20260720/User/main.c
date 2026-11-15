#include <stdio.h>
#include "M0518.h"
#include "WCS_M0518_DEF.h"
#include "wcs_system_m0518.h"
#include "wcs_timer_m0518.h"
#include "wcs_keyboard_m0518.h"
#include "wcs_windows_m0518.h"
#include "wcs_message_m0518.h"
#include "wcs_adc_m0518.h"




/* --------------------------------------------------------------------------- */
SYSTEM_DATA_TYPEDEF system_data;
/* --------------------------------------------------------------------------- */



int main(void)
{
  Clear_Sram();
  
  System_Clock_Init();
  
  System_Gpio_Init();
  
  system_data.masking |= SYSTEM_INIT_FLAG_MSK + TIMER0_INIT_FLAG_MSK;
  
  key.value1 = key.value2 = key.value3 = 0x01;
  
  Display_Led_Management(8);
  Display_Red_Management(10);
  
  Open_System_Timer();
  
  while(1)
  {
    if(system_data.masking & SYSTEM_INIT_FLAG_MSK)
    {
      if(KEY1_SCAN_TIMER > 199)
      {
        if(DEBUG_KEY && KEY1_KEY)
        {
          system_data.masking |= SYSTEM_DEBUG_FLAG_MSK;
        }
        else
        {
          Open_Timer0();
          Open_Adc_Ch0();
        }
        
        Display_Led_Management(0);
        Display_Red_Management(0);
        
        system_data.masking &= ~SYSTEM_INIT_FLAG_MSK;
      }
    }
    else
    {
      if(KEY1_SCAN_TIMER >= 18)
      {
        KEY1_SCAN_TIMER = 0;
        
        Scan_Key_Process(KEY1_KEY,&key.value1);

        if((key.value1 & 0x10) != 0)
        {
          Key1_Downevent();
        }
        
        if((key.value1 & 0x20) != 0)
        {
          Key1_Upevent();
        }
      }
      
      if(KEY2_SCAN_TIMER >= 20)
      {
        KEY2_SCAN_TIMER = 0;
        
        Scan_Key_Process(KEY2_KEY,&key.value2);
        
        if((key.value2 & 0x10) != 0)
        {
          Key2_Downevent();
        }
        
        if((key.value2 & 0x20) != 0)
        {
          Key2_Upevent();
        }
      }
      
      if(KEY3_SCAN_TIMER >= 22)
      {
        KEY3_SCAN_TIMER = 0;
        
        Scan_Key_Process(KEY3_KEY,&key.value3);
        
        if((key.value3 & 0x10) != 0)
        {
          Key3_Downevent();
        }
        
        if((key.value3 & 0x20) != 0)
        {
          Key3_Upevent();
        }
      }
      
      if(system_data.state & TIMER0_UPDATE_STATE_FLAG_MSK)
      {
        if(timer0.cont > 1)//twice
        {
          timer0.cont = 0;
          TIMER0->TCSR &= ~TIMER_TCSR_IE_Msk;
          timer0.capture_value[0] = timer0.capture_value[1] = 0;
          system_data.state &= ~TIMER0_UPDATE_STATE_FLAG_MSK;
          system_data.masking |= TIMER0_INIT_FLAG_MSK;
        }
      }
      
      if(system_data.masking & SYSTEM_MESSAGE_FLAG_MSK)
      {
        System_Message_Process();
      }

    }
    
    
    Check_Sytem_Timer();
  }
 
}
