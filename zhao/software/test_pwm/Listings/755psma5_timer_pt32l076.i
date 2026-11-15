#line 1 "User\\755PSMA5_Timer_PT32L076.c"
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



 

#line 2 "User\\755PSMA5_Timer_PT32L076.c"
#line 1 "User\\PT32x076.h"













 









#pragma anon_unions










 
typedef enum IRQn
{
	 
	NMI_IRQn        = -14,	 
	HardFault_IRQn	= -13,	 
	SVCall_IRQn		  = -5,			 
	PendSV_IRQn	    = -2,		 
	SysTick_IRQn	  = -1,			 

	 
	PVD_IRQn 	    =  0 ,  		 
	CMP0_IRQn 	  =  1 ,  		 
	AES_IRQn 	    =  2 ,  		 
	IFMC_IRQn    	=  3 ,  		 
	DMA_IRQn    	=  4 ,  		 
	EXTIA_IRQn    =  5 ,  		 
	EXTIB_IRQn    =  6 , 			 
	EXTIC_IRQn    =  7 ,			 
	EXTIF_IRQn    =  8 ,			 
	LPTIM_IRQn    =  9 ,			            
	UART2_IRQn	  =  10,  		 
	UART3_IRQn	  =  11, 	  	 
	ADC_IRQn      =  12,  		 
	TIM1_IRQn     =  13,  		 
	TIM5_IRQn     =  14,  		 
	TIM4_IRQn     =  15,  		 
	TIM3_IRQn     =  16,  		 
	TIM2_IRQn     =  17, 	  	 
	ALU_IRQn      =  18, 		 	 
	LPUART1_IRQn  =  19, 		 	 
	LPUART0_IRQn  =  20,  		 
	CMP_IRQn      =  21,  		 
	TIM8_IRQn     =  22,  		 
	I2C0_IRQn     =  23,  		 
	I2C1_IRQn     =  24,  		 
	SPI0_IRQn     =  25,  		 
	SPI1_IRQn     =  26,  		 
	UART0_IRQn    =  27,  		 
	UART1_IRQn    =  28,  		 
	RTC_IRQn      =  29, 	  	 
	TIM6_IRQn     =  30,  		 
	TIM7_IRQn     =  31,  		 
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
 




 
















 









 













   
   

 




 
#line 107 ".\\CMSIS\\cmsis_armcc.h"

 



 





 
 






 
 





 
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


#line 342 ".\\CMSIS\\cmsis_armcc.h"






 
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








 



#line 732 ".\\CMSIS\\cmsis_armcc.h"







 
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




   


 



 

#line 866 ".\\CMSIS\\cmsis_armcc.h"
 


#line 35 ".\\CMSIS\\cmsis_compiler.h"




 
#line 268 ".\\CMSIS\\cmsis_compiler.h"




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
        uint32_t RESERVED1[31U];
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
  uint32_t vectors = 0x0U;
  (* (int *) (vectors + ((int32_t)IRQn + 16) * 4)) = vector;
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t vectors = 0x0U;
  return (uint32_t)(* (int *) (vectors + ((int32_t)IRQn + 16) * 4));
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



 










#line 82 "User\\PT32x076.h"
#line 1 "User\\PT32x076_Type.h"











 









#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"




 





 












 






   









 






#line 61 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 75 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   




 















 
#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











 





extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_dcmp4(double  , double  );
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_fcmp4(float  , float  );
    




 

extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassifyf(float  );
extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassify(double  );
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
    


 

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
     
     








#line 230 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   
  typedef float float_t;
  typedef double double_t;
#line 251 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"



extern const int math_errhandling;
#line 261 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

extern __declspec(__nothrow) double acos(double  );
    
    
    
extern __declspec(__nothrow) double asin(double  );
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double atan(double  );
    
    

extern __declspec(__nothrow) double atan2(double  , double  );
    
    
    
    

extern __declspec(__nothrow) double cos(double  );
    
    
    
    
extern __declspec(__nothrow) double sin(double  );
    
    
    
    

extern void __use_accurate_range_reduction(void);
    
    

extern __declspec(__nothrow) double tan(double  );
    
    
    
    

extern __declspec(__nothrow) double cosh(double  );
    
    
    
    
extern __declspec(__nothrow) double sinh(double  );
    
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double tanh(double  );
    
    

extern __declspec(__nothrow) double exp(double  );
    
    
    
    
    

extern __declspec(__nothrow) double frexp(double  , int *  ) __attribute__((__nonnull__(2)));
    
    
    
    
    
    

extern __declspec(__nothrow) double ldexp(double  , int  );
    
    
    
    
extern __declspec(__nothrow) double log(double  );
    
    
    
    
    
extern __declspec(__nothrow) double log10(double  );
    
    
    
extern __declspec(__nothrow) double modf(double  , double *  ) __attribute__((__nonnull__(2)));
    
    
    
    

extern __declspec(__nothrow) double pow(double  , double  );
    
    
    
    
    
    
extern __declspec(__nothrow) double sqrt(double  );
    
    
    




    inline double _sqrt(double __x) { return sqrt(__x); }




    inline float _sqrtf(float __x) { return (float)sqrt(__x); }

    



 

extern __declspec(__nothrow) __attribute__((const)) double ceil(double  );
    
    
extern __declspec(__nothrow) __attribute__((const)) double fabs(double  );
    
    

extern __declspec(__nothrow) __attribute__((const)) double floor(double  );
    
    

extern __declspec(__nothrow) double fmod(double  , double  );
    
    
    
    
    

    









 



extern __declspec(__nothrow) double acosh(double  );
    

 
extern __declspec(__nothrow) double asinh(double  );
    

 
extern __declspec(__nothrow) double atanh(double  );
    

 
extern __declspec(__nothrow) double cbrt(double  );
    

 
inline __declspec(__nothrow) __attribute__((const)) double copysign(double __x, double __y)
    

 
{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
inline __declspec(__nothrow) __attribute__((const)) float copysignf(float __x, float __y)
    

 
{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __declspec(__nothrow) double erf(double  );
    

 
extern __declspec(__nothrow) double erfc(double  );
    

 
extern __declspec(__nothrow) double expm1(double  );
    

 



    

 






#line 479 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"


extern __declspec(__nothrow) double hypot(double  , double  );
    




 
extern __declspec(__nothrow) int ilogb(double  );
    

 
extern __declspec(__nothrow) int ilogbf(float  );
    

 
extern __declspec(__nothrow) int ilogbl(long double  );
    

 







    

 





    



 





    



 





    

 





    



 





    



 





    



 





    

 





    

 





    


 

extern __declspec(__nothrow) double lgamma (double  );
    


 
extern __declspec(__nothrow) double log1p(double  );
    

 
extern __declspec(__nothrow) double logb(double  );
    

 
extern __declspec(__nothrow) float logbf(float  );
    

 
extern __declspec(__nothrow) long double logbl(long double  );
    

 
extern __declspec(__nothrow) double nextafter(double  , double  );
    


 
extern __declspec(__nothrow) float nextafterf(float  , float  );
    


 
extern __declspec(__nothrow) long double nextafterl(long double  , long double  );
    


 
extern __declspec(__nothrow) double nexttoward(double  , long double  );
    


 
extern __declspec(__nothrow) float nexttowardf(float  , long double  );
    


 
extern __declspec(__nothrow) long double nexttowardl(long double  , long double  );
    


 
extern __declspec(__nothrow) double remainder(double  , double  );
    

 
extern __declspec(__nothrow) __attribute__((const)) double rint(double  );
    

 
extern __declspec(__nothrow) double scalbln(double  , long int  );
    

 
extern __declspec(__nothrow) float scalblnf(float  , long int  );
    

 
extern __declspec(__nothrow) long double scalblnl(long double  , long int  );
    

 
extern __declspec(__nothrow) double scalbn(double  , int  );
    

 
extern __declspec(__nothrow) float scalbnf(float  , int  );
    

 
extern __declspec(__nothrow) long double scalbnl(long double  , int  );
    

 




    

 



 
extern __declspec(__nothrow) __attribute__((const)) float _fabsf(float);  
inline __declspec(__nothrow) __attribute__((const)) float fabsf(float __f) { return _fabsf(__f); }
extern __declspec(__nothrow) float sinf(float  );
extern __declspec(__nothrow) float cosf(float  );
extern __declspec(__nothrow) float tanf(float  );
extern __declspec(__nothrow) float acosf(float  );
extern __declspec(__nothrow) float asinf(float  );
extern __declspec(__nothrow) float atanf(float  );
extern __declspec(__nothrow) float atan2f(float  , float  );
extern __declspec(__nothrow) float sinhf(float  );
extern __declspec(__nothrow) float coshf(float  );
extern __declspec(__nothrow) float tanhf(float  );
extern __declspec(__nothrow) float expf(float  );
extern __declspec(__nothrow) float logf(float  );
extern __declspec(__nothrow) float log10f(float  );
extern __declspec(__nothrow) float powf(float  , float  );
extern __declspec(__nothrow) float sqrtf(float  );
extern __declspec(__nothrow) float ldexpf(float  , int  );
extern __declspec(__nothrow) float frexpf(float  , int *  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) __attribute__((const)) float ceilf(float  );
extern __declspec(__nothrow) __attribute__((const)) float floorf(float  );
extern __declspec(__nothrow) float fmodf(float  , float  );
extern __declspec(__nothrow) float modff(float  , float *  ) __attribute__((__nonnull__(2)));

 
 













 
__declspec(__nothrow) long double acosl(long double );
__declspec(__nothrow) long double asinl(long double );
__declspec(__nothrow) long double atanl(long double );
__declspec(__nothrow) long double atan2l(long double , long double );
__declspec(__nothrow) long double ceill(long double );
__declspec(__nothrow) long double cosl(long double );
__declspec(__nothrow) long double coshl(long double );
__declspec(__nothrow) long double expl(long double );
__declspec(__nothrow) long double fabsl(long double );
__declspec(__nothrow) long double floorl(long double );
__declspec(__nothrow) long double fmodl(long double , long double );
__declspec(__nothrow) long double frexpl(long double , int* ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double ldexpl(long double , int );
__declspec(__nothrow) long double logl(long double );
__declspec(__nothrow) long double log10l(long double );
__declspec(__nothrow) long double modfl(long double  , long double *  ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double powl(long double , long double );
__declspec(__nothrow) long double sinl(long double );
__declspec(__nothrow) long double sinhl(long double );
__declspec(__nothrow) long double sqrtl(long double );
__declspec(__nothrow) long double tanl(long double );
__declspec(__nothrow) long double tanhl(long double );





 
extern __declspec(__nothrow) float acoshf(float  );
__declspec(__nothrow) long double acoshl(long double );
extern __declspec(__nothrow) float asinhf(float  );
__declspec(__nothrow) long double asinhl(long double );
extern __declspec(__nothrow) float atanhf(float  );
__declspec(__nothrow) long double atanhl(long double );
__declspec(__nothrow) long double copysignl(long double , long double );
extern __declspec(__nothrow) float cbrtf(float  );
__declspec(__nothrow) long double cbrtl(long double );
extern __declspec(__nothrow) float erff(float  );
__declspec(__nothrow) long double erfl(long double );
extern __declspec(__nothrow) float erfcf(float  );
__declspec(__nothrow) long double erfcl(long double );
extern __declspec(__nothrow) float expm1f(float  );
__declspec(__nothrow) long double expm1l(long double );
extern __declspec(__nothrow) float log1pf(float  );
__declspec(__nothrow) long double log1pl(long double );
extern __declspec(__nothrow) float hypotf(float  , float  );
__declspec(__nothrow) long double hypotl(long double , long double );
extern __declspec(__nothrow) float lgammaf(float  );
__declspec(__nothrow) long double lgammal(long double );
extern __declspec(__nothrow) float remainderf(float  , float  );
__declspec(__nothrow) long double remainderl(long double , long double );
extern __declspec(__nothrow) float rintf(float  );
__declspec(__nothrow) long double rintl(long double );






 
extern __declspec(__nothrow) double exp2(double  );  
extern __declspec(__nothrow) float exp2f(float  );
__declspec(__nothrow) long double exp2l(long double );
extern __declspec(__nothrow) double fdim(double  , double  );
extern __declspec(__nothrow) float fdimf(float  , float  );
__declspec(__nothrow) long double fdiml(long double , long double );
#line 803 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) double fma(double  , double  , double  );
extern __declspec(__nothrow) float fmaf(float  , float  , float  );

inline __declspec(__nothrow) long double fmal(long double __x, long double __y, long double __z)     { return (long double)fma((double)__x, (double)__y, (double)__z); }


extern __declspec(__nothrow) __attribute__((const)) double fmax(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fmaxf(float  , float  );
__declspec(__nothrow) long double fmaxl(long double , long double );
extern __declspec(__nothrow) __attribute__((const)) double fmin(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fminf(float  , float  );
__declspec(__nothrow) long double fminl(long double , long double );
extern __declspec(__nothrow) double log2(double  );  
extern __declspec(__nothrow) float log2f(float  );
__declspec(__nothrow) long double log2l(long double );
extern __declspec(__nothrow) long lrint(double  );
extern __declspec(__nothrow) long lrintf(float  );

inline __declspec(__nothrow) long lrintl(long double __x)     { return lrint((double)__x); }


extern __declspec(__nothrow) long long llrint(double  );
extern __declspec(__nothrow) long long llrintf(float  );

inline __declspec(__nothrow) long long llrintl(long double __x)     { return llrint((double)__x); }


extern __declspec(__nothrow) long lround(double  );
extern __declspec(__nothrow) long lroundf(float  );

inline __declspec(__nothrow) long lroundl(long double __x)     { return lround((double)__x); }


extern __declspec(__nothrow) long long llround(double  );
extern __declspec(__nothrow) long long llroundf(float  );

inline __declspec(__nothrow) long long llroundl(long double __x)     { return llround((double)__x); }


extern __declspec(__nothrow) __attribute__((const)) double nan(const char * );
extern __declspec(__nothrow) __attribute__((const)) float nanf(const char * );

inline __declspec(__nothrow) __attribute__((const)) long double nanl(const char *__t)     { return (long double)nan(__t); }
#line 856 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) __attribute__((const)) double nearbyint(double  );
extern __declspec(__nothrow) __attribute__((const)) float nearbyintf(float  );
__declspec(__nothrow) long double nearbyintl(long double );
extern  double remquo(double  , double  , int * );
extern  float remquof(float  , float  , int * );

inline long double remquol(long double __x, long double __y, int *__q)     { return (long double)remquo((double)__x, (double)__y, __q); }


extern __declspec(__nothrow) __attribute__((const)) double round(double  );
extern __declspec(__nothrow) __attribute__((const)) float roundf(float  );
__declspec(__nothrow) long double roundl(long double );
extern __declspec(__nothrow) double tgamma(double  );  
extern __declspec(__nothrow) float tgammaf(float  );
__declspec(__nothrow) long double tgammal(long double );
extern __declspec(__nothrow) __attribute__((const)) double trunc(double  );
extern __declspec(__nothrow) __attribute__((const)) float truncf(float  );
__declspec(__nothrow) long double truncl(long double );






#line 896 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 1087 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











#line 1317 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"





 
#line 23 "User\\PT32x076_Type.h"
#line 24 "User\\PT32x076_Type.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
 
 
 




 
 



 






   














  


 








#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


  



    typedef unsigned int size_t;    
#line 70 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"






    



    typedef unsigned short wchar_t;  
#line 91 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { long long quot, rem; } lldiv_t;
    


#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   



 

   




 
#line 131 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) long long atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) long long strtoll(const char * __restrict  ,
                                  char ** __restrict  , int  )
                          __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned long long strtoull(const char * __restrict  ,
                                            char ** __restrict  , int  )
                                   __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 436 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 524 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 553 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) long long llabs(long long  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(long long  , long long  );
   











 
#line 634 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 892 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"





 
#line 25 "User\\PT32x076_Type.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\rt_misc.h"







 









#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"
 






 

 
 
 





 





#line 34 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"




  typedef signed int ptrdiff_t;



  



    typedef unsigned int size_t;    
#line 57 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



   



      typedef unsigned short wchar_t;  
#line 82 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



    




   




  typedef long double max_align_t;









#line 114 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



 

#line 19 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\rt_misc.h"
#line 20 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\rt_misc.h"




 
extern void _getenv_init(void);




 
extern void _clock_init(void);





 

extern void *__user_libspace(void);










 
struct __argc_argv {




    int argc;




    char **argv;
    void *r2;
    void *r3;
};
extern __value_in_regs struct __argc_argv
__rt_lib_init(unsigned  , unsigned  );









 
__value_in_regs struct __argc_argv __ARM_get_argv(void * );




 
extern void __rt_lib_shutdown(void);






 
extern void __rt_exit(int  );    













 
struct __initial_stackheap {
    unsigned heap_base;                 
    unsigned stack_base;                
    unsigned heap_limit;                
    unsigned stack_limit;               
};
extern __value_in_regs struct __initial_stackheap
__user_initial_stackheap(unsigned  , unsigned  ,
                         unsigned  , unsigned  );




 
struct __heap_extent {
    uintptr_t base;
    size_t range;
};
extern __value_in_regs struct __heap_extent
__user_heap_extent(uintptr_t  , size_t  );










 
struct __stack_slop {
    unsigned always, cleanup;
};
extern __value_in_regs struct __stack_slop
__user_stack_slop(unsigned  , unsigned  );








 
extern size_t __user_heap_extend(int  ,
                                 void **  ,
                                 size_t  );






 
int __raise(int  , intptr_t  );






 
int __default_signal_handler(int  , intptr_t  );





 
void __rt_raise(int  , intptr_t  );







#line 26 "User\\PT32x076_Type.h"


 
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef const int32_t sc32; 	 
typedef const int16_t sc16;	 
typedef const int8_t  sc8;		 

typedef volatile int32_t vs32;
typedef volatile int16_t vs16;
typedef volatile int8_t  vs8;

typedef volatile const int32_t vsc32;	 
typedef volatile const int16_t vsc16;	 
typedef volatile const int8_t  vsc8;		 

typedef unsigned long long  u64;
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;	 
typedef unsigned short const uc16;	 
typedef unsigned char  const uc8;	 

typedef volatile uint32_t  vu32;
typedef volatile uint16_t  vu16;
typedef volatile uint8_t   vu8;

typedef volatile const uint32_t vuc32;	 
typedef volatile const uint16_t vuc16;	 
typedef volatile const uint8_t  vuc8;		 







#line 83 "User\\PT32x076.h"
#line 84 "User\\PT32x076.h"




 
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, RemapStatus, ProtectStatus, BitAction;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;




 

typedef struct
{
	volatile const  u32  UDID;      
	u32  RESERVED0[2]; 	 
  u32  RESERVED1;			 
	volatile const  u32  UID1;   	 
	volatile const  u32  UID2;   	 
	volatile const  u32  UID3;   	 
	volatile const  u32  CID;       
} ID_TypeDef;



 
typedef struct
{
	volatile u32  DR;        	 
	u32  RESERVED1;        
	volatile u32  OES;				 
	volatile  u32  OEC; 				 
	u32  RESERVED2[12];		 
	volatile u32  PUS;				 
	volatile  u32  PUC;				 
	volatile u32  PDS;				 
	volatile  u32  PDC;				 
	volatile u32  ODS;				 
	volatile  u32  ODC;				 
	u32  RESERVED3[2];     
	u32  RESERVED4[4];		 
	volatile u32  CSS;				 
	volatile  u32  CSC;				 
	volatile u32  BSR;				 
	volatile u32  BRR;				 
} GPIO_TypeDef;



 
typedef struct
{
	volatile u32  AFS[2];	       
	volatile  u32  AFC;    	     
	u32 RESERVED0[15];	     
	volatile u32  ANAS;					 
	volatile  u32  ANAC;					 
} AFIO_TypeDef;



 
typedef struct
{
	volatile u32  IES;     	 
	volatile  u32  IEC;    	 
	volatile u32  ITS;       
	volatile  u32  ITC;       
	volatile u32  ITDS;	     
	volatile  u32  ITDC;	     
	volatile u32  PTS;       
	volatile  u32  PTC;   	   
	volatile u32  IF;	       
} EXTI_TypeDef;



 
typedef struct
{
	volatile u32 SR;         
	volatile u32 CR1;        
	volatile u32 MSCR;       
	volatile u32 ITARR;      
	volatile const  u32 ITCNT;      
	volatile u32 PSC;        
	u32 RESERVED0;    	 
	volatile u32 CNT;        
	volatile u32 CR2;        
	volatile u32 ARR;        
	volatile u32 OCR[4];     
	volatile u32 CAPR1;      
	volatile u32 CAPR2;      
	volatile const  u32 ICR[4];     
	volatile u32 OCMR;       
	volatile u32 BDTR;       
	volatile u32 CR3;        
	volatile u32 TDCR;       
	volatile u32 TACR;       
	volatile u32 BKICR;      
}TIM_TypeDef;




 
typedef struct
{
	volatile u32 RLR;   		 
	volatile u32 CNT; 			 
	volatile u32 CR;    		 
	volatile  u32 KR;  			 
	volatile const  u32 SR;   			 
	u32 RESERVED0[251];  
	volatile u32 LOCK;    	 
} IWDG_TypeDef;



 
typedef struct
{
	volatile u32 DR;     	  
	volatile u32 CR;		 	  
	volatile u32 BRR;       
	volatile u32 IE;    	  
	volatile u32 SR;     	  
	u32 RESERVED0;	    
	volatile u32 TO;   		  
	volatile u32 TXFR;      
	volatile u32 RXFR;      
	u32 RESERVED1;		  
	volatile u32 IMCR;		  
	volatile u32 IMDCR;		  
	volatile u32 AR;		    	
} UART_TypeDef;



 
typedef struct
{
	volatile u32 CR1;        
	volatile u32 CR2;        
	volatile u32 DR;         
	volatile const  u32 SR1;        
	volatile u32 BR; 	   	   
	volatile u32 IE;         
	volatile const  u32 SR2;        
	u32 RESERVED0;	     
	volatile  u32 IC;         
	volatile u32 DCR;        
	volatile u32 CSS;        
	volatile  u32 TXFR;       
	volatile  u32 RXFR;       
} SPI_TypeDef;



 
typedef struct
{
	volatile u32 CR;		     
	volatile const  u32 SR; 		     
	volatile u32 DR;  	 	   
	volatile u32 OAR;	 			 
	u32 RESERVED0;       
	u32 RESERVED1;       
	volatile u32 CCR; 		 	 
} I2C_TypeDef;




 
typedef struct
{
	volatile u32 CR1;        
	volatile u32 CR2;        
	volatile const  u32 SR;    		 
	volatile const  u32 DR;    		 
	u32 RESERVED0;	     
	volatile u32 SCHR[4];		 
	volatile u32 BGCR;       
	u32 RESERVED1[6];		 
	volatile const  u32 SCHDR[20];	 
} ADC_TypeDef;



 
typedef struct
{
	volatile u32 CR1;        
	u32 RESERVED0[2];    
	volatile u32 IE;         
	volatile u32 SR;         
	volatile u32 CR2;        
} CMP_TypeDef;



 
typedef struct
{
	volatile u32 CR1;       
	volatile u32 CR2;	      
} OPA_TypeDef;



 
typedef struct
{
	volatile u32 CR;        
} LDAC_TypeDef;



 
typedef struct
{
	volatile u32 CR;        
	volatile u32 SEED;      
	volatile u32 POLY;      
	volatile  u32 DIN;       
	volatile const  u32 DOUT;      
} CRC_TypeDef;



 
typedef struct
{
	volatile u32 PVDR;				  
} PWR_TypeDef;



 

typedef struct
{
	volatile u32 HSECR1;  		 
	volatile u32 HSECR2;  		 
	volatile u32 HSICR;				 
	volatile u32 LSICR;				 
	u32 RESERVED0[3];  		 
	volatile u32 MCOR;      	 
	u32 RESERVED1[4];  		 
	volatile u32 LSECR;				 
	volatile u32 PLLCFGR1;		 
	volatile u32 PLLCFGR2;		 
	u32 RESERVED2[30194];	 
	volatile u32 CFGR;				 
	volatile u32 RSR;					 
	volatile  u32 ASRCR;				 
	volatile u32 RCR;					 
} RCC_TypeDef;



 
typedef struct
{
	volatile u32 CR; 						 
	volatile u32 SR;   					 
	volatile u32 IE;  					 
	volatile u32 AR;    				 
	volatile u32 DR;  					 
	u32  RESERVED0[5];	  	 
	volatile u32 PSC;  					 
	u32  RESERVED1[31733]; 	 
	volatile u32 BSR;  					 
	volatile u32 IAPAR;  				 
	u32  RESERVED2[5];		   
	volatile u32 IVTSAR;         
	u32  RESERVED3;					 
	volatile u32 RPSR;  				 
} IFMC_TypeDef;



 
typedef struct
{
	volatile u32 CSBAR;     	 
	volatile u32 CDBAR;        
	volatile u32 CNDTR;        
	volatile u32 CCR;          
	volatile u32 CCSAR;        
	volatile u32 CCDAR;        
	volatile u32 CCNTR;        
} DMA_Channel_TypeDef;



 
typedef struct
{
	volatile u32 IER;          
	volatile  u32 ICR;          
	volatile const  u32 SR;           
	volatile u32 CHAPCR[2];    
} DMA_TypeDef;



 
typedef struct
{
	volatile u32 HCR;  					 
	u32  RESERVED1[1015];		 
	volatile u32 CR;    				 
} BEEP_TypeDef;



 
typedef struct
{
	volatile u32 CR;  					 
	volatile u32 IE;  					 
	volatile u32 SR;    				 
	volatile u32 OPDXR;    			 
	volatile u32 OPDYR;    			 
	volatile u32 OPDZR;    			 
	u32  RESERVED0;		       
	volatile const  u32 DHR;    				 
	volatile const  u32 DLR;    				 
	u32  RESERVED1[4];		   
	volatile const  u32 DRR;    				 
} ALU_TypeDef;



 

typedef struct
{
	volatile u32 CR;             
	volatile u32 GCR;   		     
	volatile u32 PSC;  		       
	volatile u32 BTCR;           
	volatile u32 BON;         	 
	volatile u32 PCR1;           
	volatile u32 PCR2;        	 
	volatile u32 PDCR1;       	 
	volatile u32 PDCR2;          
	volatile u32 PDTR;	         
	volatile u32 SDPR;     	     
	volatile u32 PNR;        	   
	u32  RESERVED1[244];		 
	volatile u32 LCD_PxLy[16 * 11];
} LCD_TypeDef;



 
typedef struct
{
	volatile u32 CR;             
	volatile const  u32 SR1;   		     
	volatile u32 LOCK;  		     
	volatile u32 CSEC;           
	volatile u32 CMIN;         	 
	volatile u32 CHOUR;          
	volatile u32 CDAY;        	 
	volatile u32 CWEEK;       	 
	volatile u32 CMON;         	 
	volatile u32 CYEAR;	         
	volatile u32 IE;     	    	 
	volatile u32 SR2;        	   
	volatile u32 ASEC;        	 
	volatile u32 AMIN;        	 
	volatile u32 AHOUR;        	 
	volatile u32 AWEEK;        	 
	volatile u32 TRIM;        	 
} RTC_TypeDef;



 
typedef struct
{
	volatile u32 CR1;    		 
	volatile u32 CFGR;  		 
	volatile u32 SR;   			 
	volatile u32 CR2 ;    	 
}WWDG_TypeDef;



 
typedef struct
{
	volatile u32 CR;  					 
	volatile const  u32 SR;    				 
	 u32 RESERVED0[2];	     
	volatile u32 KR[8];    			 
	volatile u32 IVR[4];    		 
	volatile u32 DINR[4];    		 	
	 u32 RESERVED1[4];       	
	volatile const  u32 DOUTR[4];    	 	
} AES_TypeDef;

 






 















 
#line 560 "User\\PT32x076.h"

 



















#line 587 "User\\PT32x076.h"

#line 624 "User\\PT32x076.h"

 
 
 
 
 
 
 
#line 639 "User\\PT32x076.h"

 



 


 



 



 






 
#line 669 "User\\PT32x076.h"

 



 
#line 682 "User\\PT32x076.h"

 
#line 695 "User\\PT32x076.h"

 


 


 
 
 
 
 
 



 
 
 
 
 
 
#line 725 "User\\PT32x076.h"

 
#line 735 "User\\PT32x076.h"

 
 
 
 
 
 
#line 748 "User\\PT32x076.h"

 
#line 757 "User\\PT32x076.h"

 
#line 765 "User\\PT32x076.h"

 


 


 


 



 


 


 


 
 
 
 
 
 


 
#line 814 "User\\PT32x076.h"

 



 
#line 833 "User\\PT32x076.h"

 
#line 849 "User\\PT32x076.h"

 



 



 



 




 


 


 
 
 
 
 
 
#line 895 "User\\PT32x076.h"

 






 




 


 
#line 918 "User\\PT32x076.h"

 
#line 926 "User\\PT32x076.h"

 
#line 934 "User\\PT32x076.h"

 




 





 


 
 
 
 
 
 
#line 962 "User\\PT32x076.h"

 


 


 



 
#line 981 "User\\PT32x076.h"

 
 
 
 
 
 





 





 


 
#line 1010 "User\\PT32x076.h"

 


 





 





 



 




 



 


 


 
 
 
 
 
 
 
 
 
 
 
#line 1066 "User\\PT32x076.h"

 





 





 


 
 
 
 
 
 




 
 
 
 
 
 






 
#line 1114 "User\\PT32x076.h"

 
 
 
 
 
 
#line 1143 "User\\PT32x076.h"

 
#line 1155 "User\\PT32x076.h"

 
#line 1170 "User\\PT32x076.h"

 


 


 


 


 
#line 1196 "User\\PT32x076.h"

 


 


 


 


 


 
#line 1234 "User\\PT32x076.h"

 
#line 1244 "User\\PT32x076.h"

 


 


 


 


 
#line 1282 "User\\PT32x076.h"

 
#line 1290 "User\\PT32x076.h"

 
#line 1300 "User\\PT32x076.h"



 
#line 1320 "User\\PT32x076.h"

 
#line 1341 "User\\PT32x076.h"
 
#line 1349 "User\\PT32x076.h"

 
 
 
 
 
 
#line 1362 "User\\PT32x076.h"

 


 


 


 


 
 
 
 
 
 


 


 





 


 


 



 
 
 
 
 
 




 


 
 
 
 
 
 

 

 

 
#line 1436 "User\\PT32x076.h"
 

 

 

 
#line 1461 "User\\PT32x076.h"

 
#line 1481 "User\\PT32x076.h"

 
#line 1502 "User\\PT32x076.h"

 





 



 
 
 
 
 
 





 



 




 


 


 


 


 


 


 
 
 
 
 
 
#line 1567 "User\\PT32x076.h"

 



 


 


 


 


 


 


 


 


 


 


 


 
 
 
 
 
 
#line 1618 "User\\PT32x076.h"

 


 




 




 




 





 




 



 




 






 
#line 1673 "User\\PT32x076.h"

 
#line 1683 "User\\PT32x076.h"

 



 



 




 


 


 
 
 
 
 
 



 





 


 



 
 
 
 
 

 
#line 1738 "User\\PT32x076.h"

  


 


 


 


 












#line 3 "User\\755PSMA5_Timer_PT32L076.c"
#line 1 "User\\755PSMA5_Timer_PT32L076.h"




#line 6 "User\\755PSMA5_Timer_PT32L076.h"
#line 1 "User\\755PSMA5_DEF.h"



#line 5 "User\\755PSMA5_DEF.h"
#line 6 "User\\755PSMA5_DEF.h"
#line 1 "User\\755PSMA5_Timer_PT32L076.h"
#line 7 "User\\755PSMA5_DEF.h"

 
#line 15 "User\\755PSMA5_DEF.h"
 



 








































 








































 























































 
































#line 196 "User\\755PSMA5_DEF.h"














 






 

#line 228 "User\\755PSMA5_DEF.h"

#line 237 "User\\755PSMA5_DEF.h"

 






 
typedef struct
{
  uint32_t state;
	uint32_t masking;
	uint32_t signal;
}SYSTEM_DATA_typedef;

extern SYSTEM_DATA_typedef system_data;

 


#line 7 "User\\755PSMA5_Timer_PT32L076.h"
#line 1 ".\\lib\\FE_IO.h"


 



#line 8 ".\\lib\\FE_IO.h"

typedef void (*GO_TO_TypeDef)(void);
typedef void (*FLASH_ERASE_PAGE_TypeDef)(uint32_t addr);
typedef void (*FLASH_WRITE_PAGE_TypeDef)(uint32_t d, uint32_t s, uint32_t l);

uint32_t malloc_ram(uint32_t fp);

void mem_data_copy(unsigned char *d, unsigned char *s, uint32_t l);
void mem_word_copy(uint32_t *d, uint32_t *s, uint32_t l);
void mem_word_clear(uint32_t *p, uint32_t l);
void mem_byte_clear(unsigned char *p, uint32_t l);



#line 8 "User\\755PSMA5_Timer_PT32L076.h"


 








 
typedef struct
{
	uint32_t t[18];
	uint32_t mr0;
}TIMER_TypeDef;
extern TIMER_TypeDef timer5;

 
void close_timer1(void);

 
void settimer5(void);
void checktimer5(void);
void closetimer5(void);

 
void open_iwdg(void);
void feed_iwdg(void);
void close_iwdg(void);

 
void open_swdg(void);
void feed_swdg(void);
void close_swdg(void);
void close_wdog(void);

 
#line 4 "User\\755PSMA5_Timer_PT32L076.c"
#line 1 "User\\755PSMA5_System_PT32L076.h"




#line 1 "User\\755PSMA5_Windows_PT32L076.h"




#line 6 "User\\755PSMA5_Windows_PT32L076.h"
#line 7 "User\\755PSMA5_Windows_PT32L076.h"
#line 1 ".\\lib\\FE_755PSMA5_UART_PT32L076.h"

























 




#line 32 ".\\lib\\FE_755PSMA5_UART_PT32L076.h"









 
typedef void (*FE_UART_CALLBACK)(uint32_t p, uint32_t l);









 
void fe_uart_process_run(void);













 
uint32_t fe_uart_open(uint32_t mode);











 












 
uint32_t fe_get_uart_state(void);












 












 













 
uint32_t fe_set_uart_callback(FE_UART_CALLBACK cb);




#line 8 "User\\755PSMA5_Windows_PT32L076.h"


 
enum
{
	TEST_MODE,
	FIRE_MODE,
	EXTERNAL_MODE,
	EXT_ERROR_MODE,
	
	ONE_LOW_MODE,
	TWO_LOW_MODE,
	
	ONE_MED_MODE,

	LOW_BAT_MODE,
	SENSOR_FAULT_MODE,
	HUSH_MODE,
};

 
enum
{
	CLOSE_ALL = 0,
	I_OUT,
	IO_OUT,
	I_IO_OUT,
};
 
typedef struct
{
	unsigned char mode;
	unsigned char step;
	unsigned char counter;
	unsigned char offset;
	
}Alarm_typedef;

extern Alarm_typedef led;
extern Alarm_typedef buzzer;
extern Alarm_typedef update;

 
void alarm_cfg(uint8_t mode);
void remove_alarm(void);
void led_lighten(void);
void buzzer_sound(void);
void update_timer1(void);
void set_connect(unsigned char flag);
void open_buzzer(void);
void close_buzzer(void);
 
void smoke_callback(uint32_t state);
void battery_callback(uint32_t state);
void uart_callback(uint32_t p, uint32_t l);

 
#line 6 "User\\755PSMA5_System_PT32L076.h"
#line 1 ".\\lib\\FE_SMOKE_TIMER_PT32L076.h"






















 











 
void fe_set_system_tick_timer(void);









 
void fe_check_system_tick_timer(void);









 
void fe_kill_system_tick_timer(void);

#line 7 "User\\755PSMA5_System_PT32L076.h"
#line 1 ".\\lib\\FE_755PSMA5_SMOKE_PT32L076.h"























 



#line 29 ".\\lib\\FE_755PSMA5_SMOKE_PT32L076.h"













 
typedef void (*FE_SMOKE_CALLBACK)(uint32_t param);









 
void fe_smoke_process_run(void);











 
uint32_t fe_set_smoke_callback(FE_SMOKE_CALLBACK cb);














 
uint32_t fe_start_up_smoke_process(uint32_t mode);











 
uint32_t fe_start_up_smoke_sampling(void);











 
uint32_t fe_stop_smoke_sampling(void);











 
uint32_t fe_set_main_power_source(void);











 
uint32_t fe_set_backup_power_source(void);











 
uint32_t fe_get_smoke_state(void);



#line 8 "User\\755PSMA5_System_PT32L076.h"
#line 1 ".\\lib\\FE_755PSMA5_BATTERY_PT32L076.h"























 



#line 29 ".\\lib\\FE_755PSMA5_BATTERY_PT32L076.h"










 
typedef void (*FE_BATTERY_CALLBACK)(uint32_t param);









 
void fe_battery_process_run(void);











 
uint32_t fe_set_battery_callback(FE_BATTERY_CALLBACK cb);













 
uint32_t fe_start_up_battery_process(uint32_t mode);











 
uint32_t fe_get_battery_state(void);






#line 9 "User\\755PSMA5_System_PT32L076.h"
#line 1 "User\\755PSMA5_Keyboard_PT32L076.h"



#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 5 "User\\755PSMA5_Keyboard_PT32L076.h"
#line 6 "User\\755PSMA5_Keyboard_PT32L076.h"
#line 7 "User\\755PSMA5_Keyboard_PT32L076.h"
#line 1 "User\\755PSMA5_System_PT32L076.h"
#line 22 "User\\755PSMA5_System_PT32L076.h"


#line 8 "User\\755PSMA5_Keyboard_PT32L076.h"
#line 9 "User\\755PSMA5_Keyboard_PT32L076.h"

 



 
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

 
void PA_Handler(void);

void scankey2_process_run(void);
void scankey3_process_run(void);
void scankey4_process_run(void);
void scankey5_process_run(void);

void key3_down_event(void);
void key3_08s_event(void);
void key3_10s_event(void);
void key3_up_event(void);

 
#line 10 "User\\755PSMA5_System_PT32L076.h"
#line 11 "User\\755PSMA5_System_PT32L076.h"
#line 1 "User\\755PSMA5_Message_PT32L076.h"




#line 6 "User\\755PSMA5_Message_PT32L076.h"
#line 7 "User\\755PSMA5_Message_PT32L076.h"


 
void message_proc(void);
void message_execution(void);

 











#line 12 "User\\755PSMA5_System_PT32L076.h"


 
void clear_sram(void);
void sys_clock_init(void);
void sys_gpio_init(void);
void goto_deepsleep(void);

 



#line 5 "User\\755PSMA5_Timer_PT32L076.c"
#line 1 ".\\lib\\FE_semaphore.h"






















 



#line 28 ".\\lib\\FE_semaphore.h"














 
uint32_t fe_get_semaphore_state(void);












 
uint32_t fe_set_semaphore(uint32_t f);












 
uint32_t fe_clear_semaphore(uint32_t f);

#line 6 "User\\755PSMA5_Timer_PT32L076.c"

TIMER_TypeDef timer5;






 
void TIM1_Handler(void)
{
	uint32_t i;
	i = ((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->SR;
	((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->SR |= i;
	
	if((system_data.masking & (1UL << 16)) != 0)
	{
		system_data.masking &= ~(1UL << 16);
		close_timer1();
	}
	else
	{
		if((system_data.masking & (1UL << 7)) != 0)
		{
			system_data.masking &= ~(1UL << 7);
			
			((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->ARR = i = timer5.mr0;
			((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->OCR[3] = i >> 1;
		}
	}
}





 
void TIM4_Handler(void)
{
	uint32_t i;
	i = ((TIM_TypeDef *) ((0x40000000) + 0x00001C00) )->SR;
	((TIM_TypeDef *) ((0x40000000) + 0x00001C00) )->SR |= i;
	
	system_data.masking |= (1UL << 1);
}





 
void close_timer1(void)
{
	
	((AFIO_TypeDef *) ((0x48000000) + 0x00000010) )->AFC |= 0x0800 + 0x1000;
	((GPIO_TypeDef *) ((0x48000000) + 0x00000000) )->OES |= 0x0800 + 0x1000;
	((GPIO_TypeDef *) ((0x48000000) + 0x00000000) )->BRR |= 0x0800 + 0x1000;
	
	__NVIC_DisableIRQ(TIM1_IRQn);
	
	((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->CR1 = 0;
	((TIM_TypeDef *) ((0x40000000) + 0x00012C00) )->OCMR = 0;
}






 
void settimer5(void)
{
	
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->PSC = 0;
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->CNT = 0;
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->CR2 = 0;
  ((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->ARR = 16000;
  
	__nop();
	__nop();
	__nop();
  
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->SR |= ((u32)0x00000001);
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->CR1 |= ((u32)0x00000001);
}





 
void checktimer5(void)
{
	unsigned char i;
	
	if((((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->SR & ((u32)0x00000001)) != 0)
	{
    ((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->SR |= ((u32)0x00000001);
		i = 0;
		do
    {
			timer5.t[i]++;
      i++;
		}
    while(i < 18);
	}
}





 
void closetimer5(void)
{
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->CR1 = 0;
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->CR2 = 0;
	((TIM_TypeDef *) ((0x40000000) + 0x00014400) )->SR |= ((u32)0x00000001);
}




 
void open_iwdg(void)
{
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x1ACCE551);
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->RLR = 768000;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->KR = 1;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->CR |= ((u32)0x00000002) + ((u32)0x00000001);
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x00000000);
}



 
void feed_iwdg(void)
{
  ((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x1ACCE551);
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->RLR = 768000;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->KR = 1;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x00000000);
}



 
void close_iwdg(void)
{
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x1ACCE551);
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->KR = 1;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->CR = ~(((u32)0x00000001) + ((u32)0x00000002) + ((u32)0x00000004) + ((u32)0x00000008));
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x00000000);
}





 
void open_swdg(void)
{
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CFGR = 0x407F;
	
	
  
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR1 |= 113;
	
	__nop();
	__nop();
	
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR1 |= ((u32)0x00000080);
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR2 = ((u32)0x00000001) + ((u32)0xACBD0000);
}



 
void feed_swdg(void)
{
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR1 |= 113;
}



 
void close_swdg(void)
{
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR1 |= 113;
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR2 = ((u32)0xACBD0000);
}



 
void close_wdog(void)
{
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR1 |= 113;
	((WWDG_TypeDef *) ((0x40000000) + 0x00002000) )->CR2 = ((u32)0xACBD0000);
	
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x1ACCE551);
  ((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->KR = 1;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->CR = 0;
	((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->LOCK = ((u32)0x00000000);
  
  while((((IWDG_TypeDef *) ((0x40000000) + 0x00003000) )->CR & ((u32)0x00000001)) == ((u32)0x00000001)){__nop();}
}


 



