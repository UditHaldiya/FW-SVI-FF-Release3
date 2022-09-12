#ifndef STMCOMMON_H_
#define STMCOMMON_H_

#include "tmbase_proj.h"
#define TICKS_PER_SEC   LCL_TICKS_PER_SEC        // system tick == 5 ms

#ifdef __STDC__         // so can include in assembly language
#include "errcodes.h"   // to map error codes returned by functions
#include "timebase.h"   // to map error codes returned by functions
#include "stm_periph.h"
#include "cm3core.h"

//lint -esym(526,PendSV_Handler)  PendSV_Handler is in os_cpu_a.s79
extern MN_IRQ void  PendSV_Handler(void);

//lint -esym(526,__iar_program_start)  __iar_program_start is in cmain.s (library)
extern MN_IRQ void __iar_program_start(void);
//lint -esym(526,jmpstart)  jmpstart is in os_cpu_a_M3.s79
//lint -esym(757,jmpstart)  not referenced - may or may not be used (a weak reset method)
extern void jmpstart(u32 addr);

// NVIC API
MN_DECLARE_API_FUNC(scb_DoHardReset)
extern void scb_DoHardReset(void);

// RCC API
//extern void SystemInit (void);
extern void rcc_enable_HSI(void);
extern void rcc_disable_HSI(void);


MN_DECLARE_API_FUNC(__low_level_init) //__low_level_init is calledfrom cmain.s (library)
extern s32 __low_level_init(void);

MN_DECLARE_API_FUNC(startWD) // startWD is not used
extern void startWD(void);
//extern volatile u16 * tmr_GetTM2(void);


#if USE_INTERNAL_WATCHDOG == OPTION_ON
extern void rcc_DisableTimer5(void);
extern bool_t rcc_WDTimeout(void);
extern u32 tmr_GetLSIFreq(void);
#endif

// flash API                // the flash programming API is in mn_flash.h
extern void flash_SetACR(void);

// HART / UART API
MN_DECLARE_API_FUNC(UART2_IRQHandler,UART3_IRQHandler,UART4_IRQHandler,uart_Send)
enum {UART_1, UART_2, UART_3, UART_4, UART_5};
extern void uart_Send(u32 uartNo, u16_least length, const u8 *buff);
extern MN_IRQ void UART1_IRQHandler(void);
extern MN_IRQ void UART2_IRQHandler(void);
extern MN_IRQ void UART3_IRQHandler(void);
extern MN_IRQ void UART4_IRQHandler(void);
extern bool_t uart_ProcessUART_DMA_Chars(u8 uartNo, void (*prochar)(u8 c, u8 uartNo, u8_least hart_channel));
extern void uart_init(u8_least uartNo);



#endif // __STDC__

#endif // STMCOMMON_H_

// end of source
