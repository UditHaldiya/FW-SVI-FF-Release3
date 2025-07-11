#include <base.h>
#include "sysio.h"
#include "posctlmode.h"
#include "process.h"
#if 0
    #include "faultpublic.h"
#endif
#include "timer.h"
#include "power.h"
#include "reset.h"
#include "mnassert.h"
#include "uartconfig.h"
#include <hw_if.h>
#include <stm32f10x.h>

void sysio_ShowCrash(const void *message, s32 line)
{
    UNUSED_OK(message);
    UNUSED_OK(line);
#if UART_IPC_PANIC_OPTION == OPTION_ON
    MN_ENTER_CRITICAL();

        HART_Init();

        //Send a break to APP; the best we can do.
        USART2->CR1 |= USART_CR1_UE|USART_CR1_TE; //In case we killed it before for any reason
        USART2->CR2 |= USART_CR2_LINEN;
        USART2->CR1 |= USART_CR1_SBK;
        /* Since we are, normally, going to reset now,
        we need to be sure that the whole BREAK went through.
        We do this in a hacky-ish way by sending a character and waiting for
        it to be sent
        */
        while((USART2->CR1 & USART_CR1_SBK) != 0)
        {
            ;
        }

        /* Don't even think of removing this!
        Otherwise, BREAK might not be able to get through.
        Just timing, folks
        */
        USART2->DR = 0x55U; //just something
        while((USART2->SR & USART_SR_TC) == 0)
        {
            ;
        }

        USART2->CR1 &= ~USART_CR1_UE; //In case we return
        USART2->CR1 &= ~(USART_CR1_PS); //paranoia
        USART2->CR2 &= ~USART_CR2_LINEN;
    MN_EXIT_CRITICAL();
#endif //UART_IPC_PANIC_OPTION == OPTION_ON
}

static MN_NO_INIT u16 wsSignature;
static bool_t isWarmstart = false;

#define WARM_SIGNATURE (0x5a5a)

void reset_Warmstart(void)
{
    MN_ENTER_CRITICAL();
        wsSignature = WARM_SIGNATURE;
        HardReset_CPU();
    MN_EXIT_CRITICAL();
}

/** \brief Report warmstart state
\return true iff warm start
*/
bool_t reset_IsWarmstart(void)
{
    return isWarmstart;
}

void  reset_OnReset(void)
{
    if (wsSignature == WARM_SIGNATURE)
    {
        isWarmstart = true;
        wsSignature = 0;
    }
}

#define FFP_TICKS_IN_APP_TICKS (5U)
/** \brief Return the current value of the 5 ms tick counter

  \return the current tick counter LSW.
*/
tick_t timer_GetTicks(void)
{
    return osif_get_time_in_ms()/FFP_TICKS_IN_APP_TICKS;
}

#define TICKS_APP_WRAPAROUND ((u32)((UINT32_MAX+1ULL)/FFP_TICKS_IN_APP_TICKS))
tick_t timer_GetTicksSince(tick_t basetime)
{
	tick_t current_time = timer_GetTicks(); //read current time *AFTER* basetime is established
    /*time diff in FFP wraps around not at (UINT32_MAX+1) but at (UINT32_MAX+1)/FFP_TICKS_IN_APP_TICKS
    Let's account for this in a hard way
    */
    if(current_time < basetime)
    {
        //wraparound occurred
        current_time += TICKS_APP_WRAPAROUND;
    }
	tick_t diff = current_time - basetime; //assignment guarantees correct modulo operation
	return diff;
}

void timer_WaitTicks(tick_t ticks)
{
    OS_Delay(5*(s32)ticks);
}

/**
  \brief This function is hijacked to disable writes to NVMEM while translation
of NVMEM image is in progress. The reason is that "non-precious" logical volume 1
in FFP is shared between old and new firmware images and the running old image
may corrupt the new image being written.

[Original purpose:
This function checks to see if the power is currently
above the operating threshold. return - true if there is enough power
]

\return true iff the translation process is NOT running
*/
bool_t power_IsOK(void)
{
    return process_GetProcId() != PROC_CLONE_NVMEM;
}


#if 0
//A required stub
void bios_WritePwm(u16 value)
{
    UNUSED_OK(value);
}

void error_SetFault(faultcode_fast_t ErrorCode)
{
    UNUSED_OK(ErrorCode);
}

u32 timer_EstimateFunctionLength(void (*func)(void))
{
    u32   startime = 0xffffffu;         // 8.38 seconds @ 2 Mhz; 4.34 s @4MHz
    u32   TempReload;

    TempReload      = SysTick->LOAD;    // Store he reload value

    SysTick->LOAD   = startime;         // set reload register
    SysTick->VAL    = startime;         // Load the SysTick Counter Value
    func();                             // call routine
    startime       -= SysTick->VAL;     // elapsed time
    SysTick->LOAD   = TempReload;       // Restore reload register
    SysTick->VAL    = 0u;               // Load the SysTick Counter Value
    return startime/2U; //for FFP, account for twice the clock speed without changing idle.c and customizing the headers. Fix it next release!
}
#endif

ctlmode_t mode_GetIntendedControlMode(s32 *sp)
{
    if(sp != NULL)
    {
        *sp = 0; //doesn't matter
    }
    return CONTROL_OFF;
}

void mode_SetControlMode(ctlmode_t ctlmode, s32 setpoint)
{
    UNUSED_OK(ctlmode);
    UNUSED_OK(setpoint);
}

// end of file
