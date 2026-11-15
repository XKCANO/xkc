#line 1 "User\\main.c"




 
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 7 "User\\main.c"
#line 1 "User\\pt32x031.h"










































 



 



 
    








#pragma anon_unions




 
  


 






 
   




 
  


 




 





 	
typedef enum IRQn
{
 
  NonMaskableInt_IRQn     = -14,        
  HardFault_IRQn          = -13,       
  SVCall_IRQn             = -5,        
  PendSV_IRQn             = -2,        
  SysTick_IRQn            = -1,        


 
	SWDG_IRQn                =  0 ,      
	CLK_FAIL_IRQn           =  1 ,       
	FLASH_IRQn              =  3 ,       
	PA_IRQn                 =  5 ,       
	PB_IRQn                 =  6 ,       
	PF_IRQn                 =  7 ,       
	
	Comparator0_IRQn        =  9 ,       
	Comparator1_IRQn        =  10,       
	ADC_IRQn                =  12,       
	TIMER1_IRQn             =  13,        
	TIMER0_IRQn             =  14,       
	TIMER4_IRQn             =  15,       
	TIMER3_IRQn             =  16,       
	TIMER2_IRQn             =  17,       
	LED_IRQn                =  18,       
	PVD_IRQn                =  20,       
	LVD_IRQn                =  21,       
	I2C0_IRQn               =  23,       
	I2C1_IRQn               =  24,       
	SPI0_IRQn               =  25,       
	SPI1_IRQn               =  26,       
	UART0_IRQn              =  27,       
	UART1_IRQn              =  28,       

} IRQn_Type;



 


#line 1 ".\\CMSIS\\core_cm0.h"
 




 
















 










#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 35 ".\\CMSIS\\core_cm0.h"

















 




 



 

#line 1 ".\\CMSIS\\cmsis_version.h"
 




 
















 










 
#line 64 ".\\CMSIS\\core_cm0.h"
 
 









 







#line 114 ".\\CMSIS\\core_cm0.h"

#line 1 ".\\CMSIS\\cmsis_compiler.h"
 




 
















 




#line 29 ".\\CMSIS\\cmsis_compiler.h"



 
#line 1 ".\\CMSIS\\cmsis_armcc.h"
 




 
















 









 













   
   


 
#line 103 ".\\CMSIS\\cmsis_armcc.h"

 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}


#line 338 ".\\CMSIS\\cmsis_armcc.h"






 
static __inline uint32_t __get_FPSCR(void)
{





   return(0U);

}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{





  (void)fpscr;

}


 


 



 




 






 







 






 








 










 










 






                  





 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 




__attribute__((always_inline)) static __inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  uint32_t s = (4U   * 8U) - 1U;  

  result = value;                       
  for (value >>= 1U; value != 0U; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                         
  return result;
}








 



#line 728 ".\\CMSIS\\cmsis_armcc.h"







 
__attribute__((always_inline)) static __inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}







 
__attribute__((always_inline)) static __inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}




   


 



 

#line 862 ".\\CMSIS\\cmsis_armcc.h"
 


#line 35 ".\\CMSIS\\cmsis_compiler.h"




 
#line 263 ".\\CMSIS\\cmsis_compiler.h"




#line 116 ".\\CMSIS\\core_cm0.h"

















 
#line 150 ".\\CMSIS\\core_cm0.h"

 






 
#line 166 ".\\CMSIS\\core_cm0.h"

 




 










 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:28;               
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:15;               
    uint32_t T:1;                         
    uint32_t _reserved1:3;                
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t _reserved0:1;                
    uint32_t SPSEL:1;                     
    uint32_t _reserved1:30;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 



 







 



 
typedef struct
{
  volatile uint32_t ISER[1U];                
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];                
        uint32_t RSERVED1[31U];
  volatile uint32_t ISPR[1U];                
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];                
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];                  
}  NVIC_Type;

 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
        uint32_t RESERVED0;
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
        uint32_t RESERVED1;
  volatile uint32_t SHP[2U];                 
  volatile uint32_t SHCSR;                   
} SCB_Type;

 















 



























 















 









 






 



 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 








 
 







 






 







 


 







 

 










 









 


 



 





 

#line 583 ".\\CMSIS\\core_cm0.h"
 





#line 598 ".\\CMSIS\\core_cm0.h"




 





 
 












 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
  else
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2)) ? (uint32_t)(2) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(2)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2)) ? (uint32_t)(2) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(2)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}











 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)0x0U;
  vectors[(int32_t)IRQn + 16] = vector;
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)0x0U;
  return vectors[(int32_t)IRQn + 16];
}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 


 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
    return 0U;            
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 










#line 143 "User\\pt32x031.h"
#line 1 ".\\CMSIS\\system_pt32x031.h"

























 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 









 



 
  
extern void SystemInit(void);


 









 
  


   
 
#line 144 "User\\pt32x031.h"
#line 145 "User\\pt32x031.h"



   

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, RemapStatus, ProtectStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;



#line 162 "User\\pt32x031.h"





typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef enum {FALSE = 0, TRUE = !FALSE} bool;



    



 




 



 
typedef struct
{
  volatile uint32_t  REMAP;                 
  volatile uint32_t  RESERVED0;             
  volatile uint32_t  RESERVED1;             
  volatile uint32_t  SYSCLK;	               
  volatile uint32_t  RSTINFO;               
  volatile uint32_t  RETRIMING;             
  volatile uint32_t  RSTENCTRL;             
       uint32_t  RESERVED2;
  volatile uint32_t  CUSTOMER_ID_INFO;      
  volatile uint32_t  FLASH_PROTECT;         
       uint32_t  RESERVED3;
  volatile uint32_t  AGENT_ID_INFO;         
  volatile uint32_t  UID_INFO1;             
  volatile uint32_t  UID_INFO2;             
  volatile uint32_t  UID_INFO3;             
  volatile uint32_t  CID_INFO;              
       uint32_t  RESERVED4[996];
  volatile uint32_t  PID0;                  
  volatile uint32_t  PID1;                  
  volatile uint32_t  PID2;                  
  volatile uint32_t  PID3;                  
  volatile uint32_t  PID4;                  
  volatile uint32_t  PID5;                  
  volatile uint32_t  PID6;                  
  volatile uint32_t  PID7;                  
  volatile uint32_t  CID0;                  
  volatile uint32_t  CID1;                  
  volatile uint32_t  CID2;                  
  volatile uint32_t  CID3;                  
} CMSDK_SYSCON_TypeDef;



 

typedef struct 
{
  volatile uint32_t VDD_LVD_CON;        	  
  volatile uint32_t LDO_LVD_CON;            
  volatile uint32_t EOSC_CON1;        	    
  volatile uint32_t EOSC_CON2;         	    
  volatile uint32_t IOSC_24M_CON;      	    
  volatile uint32_t IOSC_32K_CON;       	  
  volatile uint32_t FD_CON;       	        
  volatile uint32_t DEGLITCH_CON;       	  
  volatile uint32_t HSINK_CON;       	      
  volatile uint32_t MCO_DIV_CON;       	    
}  CMSDK_ANAMIX_TypeDef;



 

typedef struct
{
  volatile uint32_t  DATA;            	    
  volatile uint32_t  DATAOUT;         	    
  volatile uint32_t  OUTENABLESET;    	    
  volatile uint32_t  OUTENABLECLR;    	    
  volatile uint32_t  ALTFUNCSET;      	    
  volatile uint32_t  ALTFUNCCLR;      	    
  volatile uint32_t  INTENSET;        	    
  volatile uint32_t  INTENCLR;        	    
  volatile uint32_t  INTTYPESET;      	    
  volatile uint32_t  INTTYPECLR;      	    
  volatile uint32_t  INTTYPESET1;           
  volatile uint32_t  INTTYPECLR1;           
  volatile uint32_t  INTPOLSET;       	    
  volatile uint32_t  INTPOLCLR;       	    
  union
  {
      volatile const uint32_t  INTSTATUS;   	      
      volatile uint32_t  INTCLEAR;    	      
  };
volatile uint32_t  PULLUPSET;		            
volatile uint32_t  PULLUPCLR;		            
volatile uint32_t  PULLDOWNSET;	            
volatile uint32_t  PULLDOWNCLR; 	          
volatile uint32_t  ODRSET;		              
volatile uint32_t  ODRCLR;		              
volatile uint32_t  ANASET;		              
volatile uint32_t  ANACLR;		              
volatile uint32_t  ALTFUNCSET1;      	      
volatile uint32_t  RESERVED1[232];
volatile uint32_t  LB_MASKED[256];    	    
volatile uint32_t  UB_MASKED[256];    	    
} CMSDK_GPIO_TypeDef;




 

typedef struct
{
	volatile uint32_t  CSR;                                   
	volatile uint32_t  RVR;                                
	volatile uint32_t  CVR;                                
}CMSDK_SYSTICK_TypeDef;




 
typedef struct
{
  volatile uint32_t BR;                     
  volatile uint32_t CR;                     
  volatile uint32_t BRR;                    
  volatile uint32_t IER;                    
  volatile uint32_t SR;                     
  volatile uint32_t GTR;                    
  volatile uint32_t TOR;                    
  volatile uint32_t TRR;                    
  volatile uint32_t RRR;                    
  volatile uint8_t  ISO7816_CR;             
  volatile uint32_t IR_CR;                  
  volatile uint32_t IRTX_PWMC;              
} CMSDK_UART_TypeDef;



 
typedef struct
{
  volatile uint32_t ACR;                    
  volatile uint32_t ISR;         	          
  volatile uint32_t IER;    	              
  volatile uint32_t AR;    	                
  volatile uint32_t DR;                     
       uint32_t  RESERVED[5];
  volatile uint32_t DIV;        	          
                                      
} CMSDK_FLASH_TypeDef;	




 
typedef struct
{
  volatile uint32_t CR;                     
  volatile uint32_t TRSTN;         	        
  volatile uint32_t SR;    	                
  volatile uint32_t DR;    	                
                                      
} CMSDK_ADC_TypeDef;	



 

typedef struct
{
  volatile uint32_t CSR;        
  volatile const  uint32_t SR;         
  volatile uint32_t DR;         	
  volatile uint32_t OAR;        
	volatile uint32_t RESERVED[2];
  volatile uint32_t CCR;        	
	
} CMSDK_I2C_TypeDef;



 
  
typedef struct
{
  volatile uint32_t CR0;        
  volatile uint32_t CR1;        
  volatile uint32_t DR;         
  volatile uint32_t SR;         	
  volatile uint32_t CPSR;       
  volatile uint32_t IE;         	
  volatile uint32_t RIS;        	
  volatile uint32_t EIS;        		
  volatile uint32_t ICR;        		
  volatile uint32_t RESERVED0;  
  volatile uint32_t CSCR;       	
	
} CMSDK_SPI_TypeDef;




 
  
typedef struct
{
  volatile uint32_t CR;         
  volatile uint32_t CPSR;       
  volatile uint32_t TR;         	
  volatile uint32_t DR0;        
  volatile uint32_t DR1;        	
  volatile uint32_t DR2;        
  volatile uint32_t DR3;        	
  volatile uint32_t EIS;        		
	
} CMSDK_LED_TypeDef;



 
  
typedef struct
{
  volatile uint32_t CR1;        
  volatile uint32_t CR2;        
  volatile uint32_t DAC;        
  volatile uint32_t IE;         	
  volatile uint32_t EIS;        
  volatile uint32_t INITDELAY;  	
	
} CMSDK_CMPOPA_TypeDef;




 
typedef struct
{
  volatile uint32_t ISR;            			  
  volatile uint32_t TCR;            			  
  volatile uint32_t INT_RPT;            	  
  volatile uint32_t INT_RPTC;            	  
  volatile uint32_t PR;            		  	  
  volatile uint32_t PC;             			  
  volatile uint32_t TC;             			  
  volatile uint32_t MCR;            			  
  volatile uint32_t MR0;            			  
  volatile uint32_t MR1;            			  	
  volatile uint32_t MR2;            			  
  volatile uint32_t MR3;            		    
  volatile uint32_t MR4;             			  
  volatile uint32_t CCR;             			  
  volatile uint32_t CR1;            			  
  volatile uint32_t CR2;            			  
  volatile uint32_t CR3;            			  
  volatile uint32_t CR4;            			  	
  volatile uint32_t CMR;            			  
  volatile uint32_t DT;             		    	
} CMSDK_PWM_TypeDef;



 
typedef struct
{
  volatile uint32_t ISR;            			  
  volatile uint32_t TCR;            			  
  volatile uint32_t PR;            		  	  
  volatile uint32_t PC;             			  
  volatile uint32_t TC;             			  
  volatile uint32_t MCR;            			  
  volatile uint32_t MR0;            			  
} CMSDK_TIM_TypeDef;




 
typedef struct
{                                                                              
  volatile uint32_t CR;                
  volatile uint32_t SDR;               	
  volatile uint32_t POLY;              
  volatile uint32_t DIN;               
  volatile uint32_t DOUT;              
	
} CMSDK_CRC_TypeDef;




 
typedef struct
{
  volatile uint32_t RLR;    
  volatile const  uint32_t COUNT;  
  volatile uint32_t CR;     
  volatile uint32_t FWDG;   
  volatile uint32_t RIS;    
  volatile uint32_t EIS;    
	volatile uint32_t RESERVED0[250];        
  volatile uint32_t KR;     		
		
} CMSDK_WDG_TypeDef;



 
typedef struct
{
  volatile uint32_t CR;     
		
} CMSDK_BEEP_TypeDef;


 







 




 
#line 524 "User\\pt32x031.h"




 



   
	
#line 559 "User\\pt32x031.h"



 



 
  
  

 
    
 
 
 
 
 
 
 
 
 


 


 
#line 616 "User\\pt32x031.h"

 
#line 628 "User\\pt32x031.h"

 



 
#line 640 "User\\pt32x031.h"

 


 


 


 


 


 


 





 



 


 


 


 


 


 


 


 
 
 
 
 
 
#line 706 "User\\pt32x031.h"

 
 





 
 
#line 728 "User\\pt32x031.h"

 
 
#line 754 "User\\pt32x031.h"

 
 


 

 


 

 


 
 
#line 796 "User\\pt32x031.h"

 
 





 
#line 811 "User\\pt32x031.h"

 
 
 
 
 
 
 
#line 835 "User\\pt32x031.h"

 
#line 853 "User\\pt32x031.h"

 
#line 871 "User\\pt32x031.h"

 
#line 889 "User\\pt32x031.h"

 
#line 899 "User\\pt32x031.h"

 
#line 909 "User\\pt32x031.h"



 
#line 929 "User\\pt32x031.h"


                                        
#line 948 "User\\pt32x031.h"
                                                                                                                            
                                        
#line 966 "User\\pt32x031.h"

                                            
#line 984 "User\\pt32x031.h"
                                                                                                                           
                                            
#line 1002 "User\\pt32x031.h"

                                          
#line 1020 "User\\pt32x031.h"
                                                                                                                          
                                          
#line 1038 "User\\pt32x031.h"

                                          
#line 1056 "User\\pt32x031.h"
                                                                                                                       
                                          
#line 1074 "User\\pt32x031.h"

                                          
#line 1092 "User\\pt32x031.h"

                                          
#line 1110 "User\\pt32x031.h"
                                                                                                                       
                                          
#line 1128 "User\\pt32x031.h"

                                            
#line 1146 "User\\pt32x031.h"
                                                                                                                           
                                            
#line 1164 "User\\pt32x031.h"

                                               
#line 1182 "User\\pt32x031.h"
                                                                                                                             
                                              
#line 1200 "User\\pt32x031.h"

                                              
#line 1218 "User\\pt32x031.h"
                                                                                                                             
                                              
#line 1236 "User\\pt32x031.h"

                                           
#line 1254 "User\\pt32x031.h"
                                                                                                                           
                                           
#line 1272 "User\\pt32x031.h"


 
 
 
 
 

 
#line 1290 "User\\pt32x031.h"

 
																																								






 
																																								






 

 


 


 


 
 
 
 
 
 


 
#line 1337 "User\\pt32x031.h"

 






 
#line 1358 "User\\pt32x031.h"


 
#line 1373 "User\\pt32x031.h"

 


 


 


 


 




 







 


 
 
 
 
 
 
 
 
 
#line 1428 "User\\pt32x031.h"

#line 1443 "User\\pt32x031.h"

 


 



 


 
 
 
 
 

 
#line 1469 "User\\pt32x031.h"

 


 



 
#line 1488 "User\\pt32x031.h"


 
 
 
 
 
 
#line 1517 "User\\pt32x031.h"
 





 


 






 


 





 





 





 



 



 
 
 
 
 
 
#line 1575 "User\\pt32x031.h"

 


 


 


 


 


 



 



 
 
 
 
 
 
#line 1621 "User\\pt32x031.h"

 


 


 





 





 


 
 
 
 
 

   


   



   


   


   


   






   




 
 
 
 
 

   
#line 1698 "User\\pt32x031.h"

   




   


   


   


   


   


   
#line 1728 "User\\pt32x031.h"

   


   


   


   


   


   
#line 1761 "User\\pt32x031.h"

   



  



   



   



   
#line 1794 "User\\pt32x031.h"

   


 
 
 
 
 

   
#line 1811 "User\\pt32x031.h"

   


   


   


   


 
 
 
 
 

   


 
 
 
 
 
 


  


   




   


 



   


 
 
 
 
 







 
	







 


 
  








 

  

 
  

 

 
#line 8 "User\\main.c"
#line 1 "User\\755LHA_DEF.h"



#line 5 "User\\755LHA_DEF.h"
#line 1 "User\\755LHA_RF_PT32L031.h"




#line 6 "User\\755LHA_RF_PT32L031.h"
#line 1 ".\\Lib\\FE_IO.h"





















 



#line 27 ".\\Lib\\FE_IO.h"



 
typedef void (*GO_TO_TypeDef)(void);
typedef void (*FLASH_ERASE_PAGE_TypeDef)(uint32_t addr);
typedef void (*FLASH_WRITE_PAGE_TypeDef)(uint32_t d, uint32_t s, uint32_t l);









 
uint32_t malloc_ram(uint32_t fp);









 
void mem_data_copy(unsigned char *d, unsigned char *s, uint32_t l);









 
void mem_word_copy(uint32_t *d, uint32_t *s, uint32_t l);









 
void mem_word_clear(uint32_t *p, uint32_t l);









 
void mem_byte_clear(unsigned char *p, uint32_t l);









 
void mem_byte_set(unsigned char *p, unsigned char d, uint32_t l);



#line 7 "User\\755LHA_RF_PT32L031.h"
#line 1 "User\\755LHA_DEF.h"
#line 318 "User\\755LHA_DEF.h"

#line 8 "User\\755LHA_RF_PT32L031.h"
#line 1 ".\\Lib\\FE_755LHA_MAC.h"























 




#line 30 ".\\Lib\\FE_755LHA_MAC.h"









 
typedef void (*FE_MAC_CALLBACK)(uint32_t cmd);










 
void fe_755lha_mac_process_run(void);











 
uint32_t fe_get_755lha_mac_state(void);












 
uint32_t fe_755lha_mac_receive_data(void);












 
uint32_t fe_755lha_mac_send_data(uint32_t cmd);












 
uint32_t fe_755lha_mac_quit(void);













 
uint32_t fe_set_755lha_mac_callback(FE_MAC_CALLBACK cb);



#line 9 "User\\755LHA_RF_PT32L031.h"
#line 1 ".\\Lib\\FE_PHY_BC3602.h"























 




#line 30 ".\\Lib\\FE_PHY_BC3602.h"








 
typedef void (*FE_PHY_CALLBACK)(unsigned char *p, uint32_t l);










 
void fe_phy_process_run(void);












 
uint32_t fe_get_phy_state(void);










 
uint32_t fe_get_rssi(uint32_t _mode);












 
uint32_t fe_set_phy_tx_parameter(uint32_t tx_mode, uint32_t tx_power);













 
uint32_t fe_set_phy_parameter(unsigned char *sw, FE_PHY_CALLBACK cb);















 
uint32_t fe_phy_send_data(unsigned char *data, uint32_t len, uint32_t tx_time, uint32_t idle_time);














 
uint32_t fe_phy_receive_data(uint32_t len, uint32_t rx_time, uint32_t idle_time);












 
uint32_t fe_phy_pluse_send_data(unsigned char *data);












 
uint32_t fe_phy_moniting_data(uint32_t idle_time);












 
uint32_t fe_phy_quit(void);



#line 10 "User\\755LHA_RF_PT32L031.h"
#line 1 ".\\Lib\\FE_SPI_PT32L031.h"
























 




#line 31 ".\\Lib\\FE_SPI_PT32L031.h"










 
void fe_spi_process_run(void);











 
uint32_t fe_get_spi_state(void);












 
uint32_t fe_spi_write(unsigned char *data, uint32_t len);












 
uint32_t fe_spi_read(unsigned char *data, uint32_t len);











 
uint32_t fe_enter_spi_sleep(void);



#line 11 "User\\755LHA_RF_PT32L031.h"
#line 1 "User\\755LHA_Release_PT32L031.h"



#line 1 "User\\755LHA_Windows_PT32L031.h"




#line 6 "User\\755LHA_Windows_PT32L031.h"
#line 7 "User\\755LHA_Windows_PT32L031.h"
#line 1 ".\\Lib\\FE_755LHA_Uart_PT32L031.h"

























 




#line 32 ".\\Lib\\FE_755LHA_Uart_PT32L031.h"








 
typedef void (*FE_UART_CALLBACK)(uint32_t p, uint32_t l);









 
void fe_uart_process_run(void);













 
uint32_t fe_uart_open(uint32_t mode);











 
uint32_t fe_get_uart_state(void);












 
uint32_t fe_uart_write(unsigned char *data, uint32_t len);












 
uint32_t fe_set_uart_callback(FE_UART_CALLBACK cb);



#line 8 "User\\755LHA_Windows_PT32L031.h"


 
#line 19 "User\\755LHA_Windows_PT32L031.h"
  



 






 
typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned char counter;
	unsigned char offset;
}Alarm_typedef;
extern Alarm_typedef buzzer;
extern Alarm_typedef red_led;
extern Alarm_typedef yel_led;

typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned short value;
}typedef_common;
extern typedef_common update;

 
enum
{
	TEST_MODE = 0,
	FIRE_MODE,
	REDLED_ONCE_LOW,
	REDLED_ONCE_MED,
	YELLOWLED_ONCE_LOW,
	YELLOWLED_TWICE_LOW,
	LOW_BAT_MODE,
	SENSOR_FAULT_MODE,
	NET_ALARM_MODE,
	BUZZER_ONCE,
	EXT_ERROR,
	NET_WORK_SECCESS,
	HUSH_MODE,
};

 
enum
{
	CLOSE_ALL = 0,
	I_OUT,
	IO_OUT,
	I_IO_OUT,
};


 
void remove_alarm(void);
void alarm_cfg(unsigned char mode);
void buzzer_sound(void);
void red_led_lighten(void);
void yellow_led_lighten(void);
void set_wire_connect(unsigned char flag);
void set_wireless_connect(unsigned char cmd);
void update_timer1(void);
void uart_callback(uint32_t p, uint32_t l);

 


#line 5 "User\\755LHA_Release_PT32L031.h"
#line 1 "User\\755LHA_RF_PT32L031.h"
#line 58 "User\\755LHA_RF_PT32L031.h"

#line 6 "User\\755LHA_Release_PT32L031.h"
#line 1 ".\\Lib\\FE_755LHA_EEPROM_PT32L031.h"
























 


 
#line 30 ".\\Lib\\FE_755LHA_EEPROM_PT32L031.h"
 


 
typedef struct
{
	unsigned char id[4];
	unsigned char reserved_0;
	unsigned char marking;
	unsigned char low_voltage;
	unsigned char end_voltage;
	unsigned char network_id[4];
	unsigned short network_address;
	unsigned short address;
}FE_755LHA_EEPROM_TypeDef;









 
void fe_eeprom_process_run(void);









 
void fe_read_eeprom_data(void);











 
uint32_t fe_get_eeprom_state(void);











 
uint32_t fe_755LHA_read_eeprom_data(FE_755LHA_EEPROM_TypeDef *p);











 
uint32_t fe_755LHA_write_eeprom_data(FE_755LHA_EEPROM_TypeDef *p);

 


#line 7 "User\\755LHA_Release_PT32L031.h"

 
typedef struct
{
	unsigned char step;
	unsigned char mode;
	unsigned char count;
	unsigned char reserve;
}Release_typedef;
extern Release_typedef release;

extern FE_755LHA_EEPROM_TypeDef eeprom_data;

 
void write_eepromdata(void);
void release_network(void);

 







#line 12 "User\\755LHA_RF_PT32L031.h"

 
enum
{
	NETWORK_APPLY = 0,
	MASTER_ACK,
	SLAVE_ACK,
};

 










 
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

 
void rf_pairing_process_run(void);
void mac_callback(uint32_t cmd);
void PhyCallback(unsigned char *p, uint32_t l);

 


#line 6 "User\\755LHA_DEF.h"
#line 1 "User\\755LHA_Timer_PT32L031.h"




#line 6 "User\\755LHA_Timer_PT32L031.h"
#line 7 "User\\755LHA_Timer_PT32L031.h"

 


 



 
typedef struct
{
	uint32_t t[20];
	uint32_t timer4_T8s;
}TIMER3_TypeDef;
extern TIMER3_TypeDef timer3;

 
void set_timer3(void);
void check_timer3(void);
void kill_timer3(void);

void open_timer4(void);

void set_timer1(void);
void open_buzzer(void);
void close_buzzer(void);
void close_timer1(void);

void open_iwdg(void);
void feed_iwdg(void);
void close_iwdg(void);

void open_swdg(void);
void feed_swdg(void);
void close_swdg(void);
void close_wdog(void);
  
 
#line 7 "User\\755LHA_DEF.h"

 

#line 16 "User\\755LHA_DEF.h"
 



 











































 











































 






















































































 





 

#line 214 "User\\755LHA_DEF.h"

#line 223 "User\\755LHA_DEF.h"

 



 







































































 






 
typedef struct
{
  uint32_t state;
	uint32_t masking;
	uint32_t signal;
}SYSTEM_DATA_typedef;
extern SYSTEM_DATA_typedef system_data;

 


#line 9 "User\\main.c"
#line 1 ".\\Lib\\FE_MATH.h"






















 



#line 28 ".\\Lib\\FE_MATH.h"







 
typedef struct
{
	uint32_t average;
	uint32_t max;
	uint32_t min;
	uint32_t u;
}FE_CURVE_AVERAGE_TypeDef;



 
typedef struct
{
	uint16_t t_max;
	uint16_t y_max;
	uint16_t t_min;
	uint16_t y_min;
	uint16_t y_u;
}FE_CURVE_AMPLITUDE_TypeDef;











 
void fe_data_whitening_pn7(unsigned char *p, uint32_t l);













 
uint32_t fe_calculate_crc(unsigned char *p, unsigned char l);













 
uint32_t fe_calculate_crc16(unsigned char *p, unsigned char l);










 
uint32_t fe_correcting_ad_data(uint32_t data, uint32_t vref);










 
uint32_t fe_get_2b_filter(uint32_t f, uint32_t data);










 
uint32_t fe_get_5b_filter(uint32_t f, uint32_t data);










 
uint32_t fe_get_average(uint16_t *p, uint32_t l);










 
uint32_t fe_get_maximum(uint16_t *p, uint32_t l);










 
uint32_t fe_get_minimum(uint16_t *p, uint32_t l);











 
uint32_t fe_get_increment(uint16_t *p, uint32_t l);










 
uint32_t fe_get_real_average(uint16_t *p, uint32_t l);










 
uint32_t fe_get_real_maximum(uint16_t *p, uint32_t l);










 
uint32_t fe_get_real_minimum(uint16_t *p, uint32_t l);











 
uint32_t fe_get_real_increment(uint16_t *p, uint32_t l);











 
void fe_float_data_move_to_left(float *p, uint32_t l);











 
void fe_float_data_move_to_right(float *p, uint32_t l);
	









 
void fe_data_move_to_left(uint16_t *p, uint32_t l);










 
void fe_data_move_to_right(uint16_t *p, uint32_t l);










 
void fe_byte_data_move_to_left(unsigned char *p, uint32_t l);













 
uint32_t fe_real_comparision(uint32_t t1, uint32_t t2);













 
uint32_t fe_char_real_comparision(unsigned char t1, unsigned char t2);










 
uint32_t fe_subtractive(uint32_t t1, uint32_t t2);










 
uint32_t fe_char_real_subtractive(unsigned char t1, unsigned char t2);











 
void fe_get_curve_average(FE_CURVE_AVERAGE_TypeDef *p, uint16_t *pd, uint32_t l);











 
void fe_get_curve_amplitude(FE_CURVE_AMPLITUDE_TypeDef *p, uint16_t *pd, uint32_t l);









 
uint32_t fe_calculate_external_16b_temperature(uint32_t data);









 
uint32_t fe_calculate_external_8b_temperature(uint32_t data);



#line 10 "User\\main.c"
#line 1 ".\\Lib\\FE_TIMER_PT32L031.h"
























 











 
void fe_set_system_tick_timer(void);









 
void fe_check_system_tick_timer(void);









 
void fe_kill_system_tick_timer(void);

#line 11 "User\\main.c"
#line 12 "User\\main.c"

#line 14 "User\\main.c"
#line 1 "User\\755LHA_System_PT32L031.h"



#line 5 "User\\755LHA_System_PT32L031.h"
#line 6 "User\\755LHA_System_PT32L031.h"
#line 1 ".\\Lib\\FE_755LHA_PT32L031_CFG.h"






















 



#line 28 ".\\Lib\\FE_755LHA_PT32L031_CFG.h"










 
void fe_initializing_gpio(void);









 
void fe_clear_ram(void);











 
void fe_calculate_sleep_8s(unsigned char *s);











 
uint32_t fe_get_sleep_8s(void);



#line 7 "User\\755LHA_System_PT32L031.h"
#line 8 "User\\755LHA_System_PT32L031.h"

#line 10 "User\\755LHA_System_PT32L031.h"
#line 11 "User\\755LHA_System_PT32L031.h"
#line 12 "User\\755LHA_System_PT32L031.h"
#line 1 "User\\755LHA_Keyboard_PT32L031.h"




#line 6 "User\\755LHA_Keyboard_PT32L031.h"
#line 7 "User\\755LHA_Keyboard_PT32L031.h"


 



 
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

 
void keyfrequency_check(void);
void scankey2_process_run(void);
void scankey3_process_run(void);
void key3_down_event(void);
void key3_08s_event(void);
void key3_10s_event(void);
void key3_up_event(void);

 
#line 13 "User\\755LHA_System_PT32L031.h"
#line 1 "User\\755LHA_Message_PT32L031.h"




#line 6 "User\\755LHA_Message_PT32L031.h"
#line 1 "User\\755LHA_System_PT32L031.h"
#line 7 "User\\755LHA_Message_PT32L031.h"
#line 8 "User\\755LHA_Message_PT32L031.h"
#line 9 "User\\755LHA_Message_PT32L031.h"


void message_proc(void);
void message_execution(void);












#line 14 "User\\755LHA_System_PT32L031.h"

 
typedef struct
{
  unsigned char step;
	unsigned char mode;
}START_TYPEDEF;
extern START_TYPEDEF start;

 
void system_start_proc_run(void);
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);

 
#line 15 "User\\main.c"
#line 1 "User\\755LHA_heat_PT32L031.h"




#line 6 "User\\755LHA_heat_PT32L031.h"
#line 7 "User\\755LHA_heat_PT32L031.h"
#line 8 "User\\755LHA_heat_PT32L031.h"
#line 1 "User\\ADC_PT32L031.h"



#line 5 "User\\ADC_PT32L031.h"









 
void fe_adc_init(unsigned char *step);









 
void fe_adc_kill(void);









 
void fe_adc_open_scm_in1(unsigned short *d);









 
void fe_adc_open_scm_in3(unsigned short *d);









 
void fe_adc_open_scm_in6(unsigned short *d);








 
void fe_adc_open_scm_in12(unsigned short *d);









 
uint32_t CalculateActualVoltage(uint32_t data);



#line 9 "User\\755LHA_heat_PT32L031.h"
#line 10 "User\\755LHA_heat_PT32L031.h"
#line 1 "User\\755LHA_Batterylow_PT32L031.h"




#line 6 "User\\755LHA_Batterylow_PT32L031.h"
#line 7 "User\\755LHA_Batterylow_PT32L031.h"
#line 8 "User\\755LHA_Batterylow_PT32L031.h"
#line 9 "User\\755LHA_Batterylow_PT32L031.h"
#line 1 ".\\Lib\\FE_semaphore.h"























 



#line 29 ".\\Lib\\FE_semaphore.h"
















 
uint32_t fe_get_semaphore_state(void);












 
uint32_t fe_set_semaphore(uint32_t f);












 
uint32_t fe_clear_semaphore(uint32_t f);

#line 10 "User\\755LHA_Batterylow_PT32L031.h"
#line 1 "User\\755LHA_Heat_PT32L031.h"
#line 44 "User\\755LHA_Heat_PT32L031.h"

#line 11 "User\\755LHA_Batterylow_PT32L031.h"


 



 
typedef struct
{
	unsigned char step;
  unsigned char mode;
	unsigned char count;
	unsigned char data[3];
	
	unsigned short v_data;
	unsigned short v_vref;
}Battery_typedef;
extern Battery_typedef bat;

 
void measure_battery(void);
void CheckIsLowbattery(void);
void CheckVoltageIsOk(void);
void array_right(unsigned char *arr, unsigned char l);

 


#line 11 "User\\755LHA_heat_PT32L031.h"

 




 
typedef struct
{
	unsigned char step;
	unsigned char mode;

	unsigned char normal_time;
	unsigned char fault_time;
	
	unsigned short ntc_data;
	unsigned short base_data; 
	
	unsigned short counter;
  unsigned short rate;
	unsigned short t_average_128;
	unsigned short stop_data;
	
	unsigned short t_data[512]; 
	unsigned short t_minute[128]; 
}HEAT_TypeDef;
extern HEAT_TypeDef heat;

 
void heat_process_run(void);
void data_treating(void);
 


#line 16 "User\\main.c"
#line 17 "User\\main.c"
#line 18 "User\\main.c"

SYSTEM_DATA_typedef system_data;





 

int main(void)
{
	fe_clear_ram();

	sys_clock_init();

	sys_gpio_init();

	open_iwdg();

	open_swdg();

	fe_read_eeprom_data();
  
	fe_set_system_tick_timer();
	
	set_timer3();
  
	key2.value = 
	key3.value = 1;
  
  system_data.masking |= ((1UL << 0) + (1UL << 1) + (1UL << 2));
	
	while(1)
	{



 	
		if(system_data.masking & (1UL << 0))
		{
			system_start_proc_run();
		}

    if(timer3 . t[0] >= 5) 
    {
      timer3 . t[0] = 0;
			
      if((system_data.masking & (1UL << 14)) == 0)
			{
        scankey2_process_run();
      }
    }
		
    if(timer3 . t[1] >= 50)
    {
      timer3 . t[1] = 0;
      
      scankey3_process_run();

			if(key3.value & 0x10)
			{
				key3_down_event();
		  }
			
			if(key3.value & 0x20)
			{
        key3_08s_event();
			}
			
			if(key3.value & 0x40)
			{
				key3_10s_event();
			}
	 		
			if(key3.value & 0x80)
			{
				key3_up_event();
			}
    }

    if(check_fre.mode & 0x01)
    {
      keyfrequency_check();
    }
    
    if(timer3 . t[11] >= 8000)
    {
      timer3 . t[11] = 0;
      feed_iwdg();
      heat.mode = 0x01;
    }
		
    if(heat.mode & 0x01)
    {
      heat_process_run();
    }

    if(pair.mode & 0x01)
    {
      rf_pairing_process_run();
    }

		if(system_data.masking & (1UL << 8))
		{
			if(system_data.masking & (1UL << 27))
			{
				if(timer3 . t[12] >= 1000)
				{
					timer3 . t[12] = 0;
					bat.mode = 0x01;
				}
			}
		}
		else
		{
			if(timer3 . t[12] >= 48000)
			{
				timer3 . t[12] = 0;
				bat.mode = 0x01;
			}
		}
    
    if(bat.mode & 0x01)
    {
      measure_battery();
    }

		if(red_led.mode & 0x01)
		{
			red_led_lighten();
		}
		
		if(yel_led.mode & 0x01)
		{
			yellow_led_lighten();
		}
			
		if(buzzer.mode & 0x01)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		{
			buzzer_sound();
      
      if(update.mode & 0x01)
      {
        update_timer1();
      }
		}
		
		if(release.mode & 0x01)
		{
			release_network();
		}

    if(system_data.state & (1UL << 13))
    {
      if(timer3 . t[8] > 7999)
      {
        system_data.signal &= ~(1UL << 13);
        system_data.masking |= (1UL << 3);
      }
    }
    
		if(system_data.state & ((1UL << 6) + (1UL << 7)))
		{
			if(timer3 . t[8] > 24999)
			{
				system_data.signal &= ~((1UL << 6) + (1UL << 7));
				system_data.masking |= (1UL << 3);
			}
		}
    
    if(system_data.state & (1UL << 1))
    {
      if(timer3 . t[10] >= 600000)
      {
        system_data.signal &= ~(1UL << 1);
				system_data.masking |= (1UL << 3);
      }
    }
		
		if(system_data.masking & (1UL << 23))
		{
			if(system_data.masking & (1UL << 26))
			{
				system_data.masking &= ~(1UL << 23);
			}
			else
			{
				if((fe_get_semaphore_state() & 0x1FF) == 0)
				{
					((CMSDK_GPIO_TypeDef *) ((0x48000000) + 0x00002000) )->DATAOUT |= 0x0002;
					fe_set_semaphore(8);
					system_data.masking &= ~(1UL << 23);
					system_data.masking |= (1UL << 26);
				}
			}
		}
		
		if(system_data.masking & (1UL << 24))
		{
			if((fe_get_semaphore_state() & 0x100) == 0)
			{
				system_data.masking &= ~((1UL << 24) + (1UL << 26));
			}
			else
			{
				((CMSDK_GPIO_TypeDef *) ((0x48000000) + 0x00002000) )->DATAOUT &= ~0x0002;
			  fe_clear_semaphore(8);
			  system_data.masking &= ~((1UL << 24) + (1UL << 26));
			}
		}
		
		if(system_data.masking & (1UL << 5))
		{
			if(fe_755lha_mac_send_data(pair . cmd) == 0)
			{
				system_data.masking &= ~(1UL << 5);
			}
		}
		
		if(system_data.masking & (1UL << 20))
    {
      if(system_data.masking & (1UL << 6))
      {
        if(fe_755lha_mac_receive_data() == 0)
        {
          system_data.masking &= ~(1UL << 20);
        }
      }
      else
      {
        system_data.masking &= ~(1UL << 20);
      }
    }

		if(system_data.masking & (1UL << 3))
	  {
			message_proc();
	  }
		



 			
		fe_755lha_mac_process_run();
		fe_phy_process_run();
		fe_spi_process_run();
		fe_uart_process_run();
		fe_eeprom_process_run();
   



 
	  if((system_data.masking & 
			((1UL << 0) + (1UL << 4) + (1UL << 5) + (1UL << 8) +        (1UL << 20) + (1UL << 23) + (1UL << 24) + (1UL << 22) + (1UL << 25) + (1UL << 3))) == 0)

		{
			if(fe_get_eeprom_state() == 0)
			{
				if(fe_get_uart_state() == 0)
				{
					if(fe_get_755lha_mac_state() == 0)
					{
						if(fe_get_phy_state() != 0xFFFFFFFF)
						{
							if(fe_get_spi_state() == 0)
							{
								if(heat.mode == 0x00 && check_fre.mode == 0x00 && bat.mode == 0x00 && 
									 buzzer.mode == 0x00 && yel_led.mode == 0x00 && red_led.mode == 0x00 && 
								   pair.mode == 0x00 && key3.value == 0x1 && key2.value == 0x1)
								{
									goto_deepsleep();
								}
							}
						}
					}
				}
			}
	  }



 
    feed_swdg();
		fe_check_system_tick_timer();
		check_timer3();
	}
}


 


