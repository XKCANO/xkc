;  File Name        : startup_PT32x076.s
;  Version          : V1.1.0
;  Date             : 2023/10/20
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/
;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;//   <o> Stack Size (in Bytes, must 8 byte aligned) <0-16384:8>
Stack_Size          EQU     4096

                    AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem           SPACE   Stack_Size
__initial_sp

;//   <o>  Heap Size (in Bytes) <0-16384:8>
Heap_Size           EQU     0

                    AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem            SPACE   Heap_Size
__heap_limit

                    PRESERVE8
                    THUMB

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                    AREA    RESET, CODE, READONLY
                    EXPORT  __Vectors

__Vectors           DCD  __initial_sp                       ; Top address of Stack
                    DCD  Reset_Handler                      ; Reset Handler
                    DCD  NMI_Handler                        ; NMI Handler
                    DCD  HardFault_Handler                  ; Hard Fault Handler
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved						
                    DCD  SVC_Handler            			; SVC Handler
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  PendSV_Handler                     ; PendSV Handler
                    DCD  SysTick_Handler                    ; SysTick Handler

                    ; External Interrupt Handler
                    DCD  PVD_Handler						;  16+ 0:  PVD_Handler
                    DCD  CMP0_Handler   				    ;  16+ 1:  CMP0_Handler
                    DCD  AES_Handler						;  16+ 2:  AES_Handler
                    DCD  IFMC_Handler						;  16+ 3:  IFMC_Handler
                    DCD  DMA_Handler           				;  16+ 4:  DMA_Handler
                    DCD  EXTIA_Handler			     		;  16+ 5:  EXTIA_Handler
                    DCD  EXTIB_Handler						;  16+ 6:  EXTIB_Handler
                    DCD  EXTIC_Handler						;  16+ 7:  EXTIC_Handler
                    DCD  EXTIF_Handler						;  16+ 8:  EXTID_Handler
                    DCD  LPTIM_Handler						;  16+ 9:  LPTIM_Handler
                    DCD  UART2_Handler						;  16+ 10: UART2_Handler
                    DCD  UART3_Handler					    ;  16+ 11: UART3_Handler
                    DCD  ADC_Handler			            ;  16+ 12: ADC_Handler
                    DCD  TIM1_Handler		                ;  16+ 13: TIM1_Handler
                    DCD  TIM5_Handler		                ;  16+ 14: TIM5_Handler
                    DCD  TIM4_Handler		                ;  16+ 15: TIM4_Handler
                    DCD  TIM3_Handler                       ;  16+ 16: TIM3_Handler
                    DCD  TIM2_Handler		                ;  16+ 17: TIM2_Handler
                    DCD  ALU_Handler           			   	;  16+ 18: ALU_Handler
                    DCD  LPUART1_Handler           			;  16+ 19: LPUART1_Handler
                    DCD  LPUART0_Handler		            ;  16+ 20: LPUART0_Handler
                    DCD  CMP_Handler						;  16+ 21: CMP_Handler
				    DCD  TIM8_Handler                       ;  16+ 22: TIM8_Handler
                    DCD  I2C0_Handler						;  16+ 23: I2C0_Handler
                    DCD  I2C1_Handler          				;  16+ 24: I2C1_Handler
                    DCD  SPI0_Handler						;  16+ 25: SPI0_Handler
                    DCD  SPI1_Handler						;  16+ 26: SPI1_Handler		
                    DCD  UART0_Handler						;  16+ 27: UART0_Handler					
                    DCD  UART1_Handler						;  16+ 28: UART1_Handler
                    DCD  RTC_Handler						;  16+ 29: RTC_Handler	
                    DCD  TIM6_Handler                       ;  16+ 30: TIM6_Handler
                    DCD  TIM7_Handler                       ;  16+ 31: TIM7_Handler
						

; Reset handler routine
Reset_Handler       PROC
                    EXPORT  Reset_Handler                   [WEAK]
                    IMPORT  __main
                    ;IMPORT  SystemInit
					;LDR     R0, =SystemInit
                    ;BLX     R0
                    LDR     R0, =__main
                    BX      R0
                    ENDP

; Dummy Exception Handlers
NMI_Handler         PROC
                    EXPORT  NMI_Handler                     [WEAK]
                    B       .
                    ENDP

HardFault_Handler   PROC
                    EXPORT  HardFault_Handler               [WEAK]
                    B       .
                    ENDP

SVC_Handler         PROC
                    EXPORT  SVC_Handler                     [WEAK]
                    B       .
                    ENDP

PendSV_Handler      PROC
                    EXPORT  PendSV_Handler                  [WEAK]
                    B       .
                    ENDP

SysTick_Handler     PROC
                    EXPORT  SysTick_Handler                 [WEAK]
                    B       .
                    ENDP


Default_Handler     PROC
                    EXPORT  PVD_Handler                    	[WEAK]
                    EXPORT  CMP0_Handler                    [WEAK]
                    EXPORT  AES_Handler                    	[WEAK]
					EXPORT  IFMC_Handler                    [WEAK]
					EXPORT  DMA_Handler                     [WEAK]
                    EXPORT  EXTIA_Handler                   [WEAK]
                    EXPORT  EXTIB_Handler                   [WEAK]
                    EXPORT  EXTIC_Handler                   [WEAK]
                    EXPORT  EXTIF_Handler                   [WEAK]
                    EXPORT  LPTIM_Handler                   [WEAK]						
                    EXPORT  UART2_Handler                   [WEAK]
                    EXPORT  UART3_Handler	                [WEAK]					
                    EXPORT  ADC_Handler	                    [WEAK]
                    EXPORT  TIM1_Handler                    [WEAK]
                    EXPORT  TIM5_Handler                    [WEAK]						
                    EXPORT  TIM4_Handler                    [WEAK]
                    EXPORT  TIM3_Handler                    [WEAK]
                    EXPORT  TIM2_Handler                    [WEAK]
                    EXPORT  ALU_Handler                     [WEAK]
					EXPORT  LPUART1_Handler                 [WEAK]
					EXPORT  LPUART0_Handler                 [WEAK]					
					EXPORT  CMP_Handler                   	[WEAK]
					EXPORT  TIM8_Handler                   	[WEAK]
                    EXPORT  I2C0_Handler                    [WEAK]
					EXPORT  I2C1_Handler                    [WEAK]
                    EXPORT  SPI0_Handler                    [WEAK]
                    EXPORT  SPI1_Handler                    [WEAK]
                    EXPORT  UART0_Handler                   [WEAK]
					EXPORT  UART1_Handler                   [WEAK]
				    EXPORT  RTC_Handler                     [WEAK]
                    EXPORT  TIM6_Handler                    [WEAK]
                    EXPORT  TIM7_Handler                    [WEAK]



PVD_Handler
CMP0_Handler
AES_Handler
IFMC_Handler
DMA_Handler
EXTIA_Handler
EXTIB_Handler
EXTIC_Handler
EXTIF_Handler
LPTIM_Handler
UART2_Handler
UART3_Handler
ADC_Handler
TIM1_Handler
TIM5_Handler
TIM4_Handler
TIM3_Handler
TIM2_Handler
ALU_Handler
LPUART1_Handler
LPUART0_Handler
CMP_Handler
TIM8_Handler
I2C0_Handler
I2C1_Handler
SPI0_Handler
SPI1_Handler
UART0_Handler
UART1_Handler
RTC_Handler
TIM6_Handler
TIM7_Handler


                    B       .
                    ENDP

                    ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                    IF      :DEF:__MICROLIB

                    EXPORT  __initial_sp
                    EXPORT  __heap_base
                    EXPORT  __heap_limit

                    ELSE

                    IMPORT  __use_two_region_memory
                    EXPORT  __user_initial_stackheap
__user_initial_stackheap

                    LDR     R0, =  Heap_Mem
                    LDR     R1, = (Stack_Mem + Stack_Size)
                    LDR     R2, = (Heap_Mem + Heap_Size)
                    LDR     R3, = Stack_Mem
                    BX      LR

                    ALIGN

                    ENDIF

                    END
