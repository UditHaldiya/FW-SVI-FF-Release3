/* Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_coinstrum.h
    \brief MN code instrumentation. Critical section profilng version

    CPU: Any (profiler instrumentation)

    OWNER: AK

    \ingroup OSWrap
*/
#ifndef MN_COINSTRUM_H_
#define MN_COINSTRUM_H_
#include <tmbase_proj.h> //for CORE_FREQ

typedef uint32_t ccount_t;

#define DWT_CYCCNT HARDWARE(volatile ccount_t *, 0xE0001004U)
#define DWT_CONTROL HARDWARE(volatile uint32_t *, 0xE0001000U)
#define DEMCR HARDWARE(volatile uint32_t *, 0xE000EDFCU)

MN_INLINE void instrum_EnableCycleCount(void)
{
    // enable the use DWT
    *DEMCR |= 0x01000000U;

    // Reset cycle counter
    *DWT_CYCCNT = 0U;

    // enable cycle counter
    *DWT_CONTROL |= 1U ;
}

//lint -emacro(453, instrum_GetHighResolutionTimer) //don't care about volatile access in it
#define instrum_GetHighResolutionTimer() (*DWT_CYCCNT)

#define ASSERT_DISPLAY_TIME (5*CORE_FREQ) //5 seconds display at the most

#define MN_ENTER_CRITICAL_HOOK(psw) \
    ccount_t stamp = instrum_GetHighResolutionTimer();


#define MN_EXIT_CRITICAL_HOOK(psw) \
    if(((psw) & CPU_NO_INTERRUPTS) != CPU_NO_INTERRUPTS) \
    { \
        ccount_t captured_count = instrum_GetHighResolutionTimer(); \
        stamp = captured_count - stamp; \
        if(stamp > CritSectStat.maxlen) \
        { \
            CritSectStat.maxlen = stamp; \
            CritSectStat.addr = mn_getPC(); \
        } \
    }

//lint -esym(526, mn_getPC) An assembler routine returning its LR in R0
LINT_PURE(mn_getPC)
extern u32 mn_getPC(void);

typedef struct CritSectStat_t
{
    ccount_t maxlen; //max length of a critical section so far
    uintptr_t addr; //address of the end of the longest critical section
} Atomic_ CritSectStat_t;

//lint -estring(453,CritSectStat) OK to modify it in an otherwise pure function
//lint -estring(752,CritSectStat) OK not to reference locally
extern CritSectStat_t CritSectStat; //critical sections profiler

extern u32 profiler_extra_task_load;
extern u8 profiler_task_id;


//lint -estring(453,instrum_GetHighResolutionTimer) OK to read timer in an otherwise pure function

#endif //MN_COINSTRUM_H_
/* This line marks the end of the source */
