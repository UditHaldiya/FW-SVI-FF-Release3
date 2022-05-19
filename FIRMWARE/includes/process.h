/*
Copyright 2004-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file process.h
    \brief MNCB Public interface of the Process task module.

    CPU: Any

    OWNER: AK

    \ingroup Process
*/
#ifndef PROCESS_H_
#define PROCESS_H_
//#include "timebase.h" //tick_t
#include "errcodes.h"
#include "syswd.h"
//Defines

//FUTURE lint -strong(AiJeX, ProcId_t)
typedef u8 ProcId_t; //!< a type for (long) process id to run in the process task context

#define ENUM_WITH_MAXVAL(type, ...) enum {__VA_ARGS__ CAT(type,_MAXVAL)}

ENUM_WITH_MAXVAL( PROC,
    PROC_NONE, //0,
    PROC_FIND_STOPS, //1,
    PROC_FINDSTOPS_NORMAL, //2,
    PROC_OPENSTOPADJ_NORMAL, //3,   //TFS:4288
    PROC_AUTOTUNE, //4,
    PROC_AUTOTUNE_NORMAL, //5,
    PROC_STD_ACT_SIGNATURE, //6,
    PROC_EXT_ACT_SIGNATURE, //7,
    PROC_STEP_TEST, //8,
    PROC_HART_42_RESET, //9,
    PROC_HART_RAM_COMMIT, //10,
    PROC_HART_SUB132_INIT_NOCAL, //11, //<! deprecated
    PROC_HART_SUB132_INIT_WITHCAL, //12,
    PROC_HART_235_SAVECAL, //13, //<! deprecated
    PROC_BUMPLESS, //14,
    PROC_DIAG_RAMP_TEST, //15,
    PROC_DIAG_PARTIAL_STROKE_TEST, //16,
    PROC_SHUTDOWN_MONITOR, //17,
    PROC_PROOF_TEST, //18,
    PROC_ESD_CONT_DIAGS, //19,
    PROC_ESD_TB_DIAG, //20,
    PROC_IP_STEP_CAL, //21,
    PROC_AOSWEEP, //22, //!< DLT-style output sweep, also reused for FW download
    PROC_TEST_PROCESS, //23, //!< Local UI (SVi1000 style) test
    PROC_READ_BUFFER, //24, //!< Load saved diagnostics
    PROC_WRITE_BUFFER, //25, //!< Save diagnostic curve
    PROC_FILE_NVMEM, //26,  //!< A process to store "factory defaults"
    PROC_RESTORE_FILED_NVMEM, //27, //!< A process to restore "factory defaults"
    PROC_CLONE_NVMEM, //28, //!< A process to clone NVMEM to the opposite "bank" (for firmware download if supported)
    PROC_CANCEL_PROC, //29, //!< simply cancels the existing process, if any
    PROC_UPLOAD_NVMEM, //30, //!< Upload NVMEM into diagnostic buffer
    PROC_DOWNLOAD_NVMEM, //31, //!< Write NVMEM image from diagnostic buffer to NVMEM
    PROC_WRITE_LOGFILE, //32, //!< deferred write of a log file
    PROC_EMPTY_WRAPPER, //33, //!< just to make sure a process is running
    PROC_RESTORE_FW_NVMEM, //34,  //!< A process to store "firmware defaults"
);

/** Process return codes */
typedef enum procresult_t
{
    PROCRESULT_OK,
    PROCRESULT_CANCELED,
    PROCRESULT_FAILED
} procresult_t;


//A collection of required interfaces to be provided by individual modules
//extern procresult_t nvram_PageTest(s16 *procdetails);

typedef struct procflags_t
{
    u8 throughflags; //!< what's allowed via HART while the process is running
    u8 initflags; //!< what's to be done before the process start
    //u8 reserved[2]; //!< for the future: we have an alignment waste anyway
} procflags_t;
#define PROCINIT_CLAIMDIAGBUFFER 0x01U //!an initflag to init and use the diagnostic buffer 0
#define PROCINIT_CLAIMCTLMODE 0x02U //!an initflag to restore control mode on exit
#define PROCINIT_INHERITDIAGBUFFER 0x04U //!an initflag to suppress init of claimed diag buffer
#define PROCINIT_IGNOREBUFFERGUARD 0x08U //!an initflag to allow forced process if the same process id guards the buffer
#define PROCINIT_HONORWRITELOCK 0x10U //!an initflag to prohibit process when write lock is activated

//-----------------------------------------------------------------------
MN_DECLARE_API_FUNC(process_Exec) //A process might want to call another process; this is the way which may or may not be used
extern procresult_t process_Exec(ProcId_t procId);
extern u8 process_GetProcessFlags(void);
MN_DECLARE_API_FUNC(process_GetResourceFlags) //this is the way which may or may not be used
extern u8 process_GetResourceFlags(void);
extern u8 process_GetProcessTermFlags(procresult_t Action);

//Bitmap reasons for proc cancellation
#define CANCELPROC_UIPUSHBUTTON 0x01U
#define CANCELPROC_MODE         0x02U
#define CANCELPROC_POWERMARGIN  0x04U
#define CANCELPROC_INTERNALREQ  0x08U
#define CANCELPROC_MONITOR      0x10U //! Go together with CANCELPROC_INTERNALREQ
#define CANCELPROC_ABORT        0x20U //! Go together with CANCELPROC_INTERNALREQ

//Functions
extern bool_t process_WaitForTime(tick_t nDelay);
extern u8_least process_WaitForTimeExt(tick_t nDelay, u8_least brk_mask); //returns bitmap of requests

#define process_CheckProcess() (process_GetProcId() != PROC_NONE)
//lint -sem(process_GetProcId, pure)
extern ProcId_t process_GetProcId(void);

extern u8 process_CheckProcessProgress(void);
extern void process_SetProcessProgress(u8 Progress);
extern void	process_CancelProcess(void); //deprecated
extern bool_t process_IsGuardingDiagBuffer(void);

typedef enum ProcSource_t
{
    ProcSourceDefault, //0 for backward compatibility; HART or internal
    ProcSourceUI, //1 for backward compatibility
    ProcSourceMonitor, //!< Set by internal monitor
    ProcSourceAbort, //!< Set by internal abort monitor
} ProcSource_t;

extern void process_CancelProcessEx(ProcId_t proc, ProcSource_t src);
extern ErrorCode_t process_SetProcessCommandEx(ProcId_t proc, ProcSource_t source);
/** \deprecated
*/
MN_INLINE ErrorCode_t process_SetProcessCommand(ProcId_t proc)
{
    return process_SetProcessCommandEx(proc, ProcSourceDefault);
}
extern void  process_ForceProcessCommandEx(ProcId_t ProcessCommand, ProcSource_t source);
/** \deprecated
*/
MN_INLINE void process_ForceProcessCommand(ProcId_t proc)
{
    process_ForceProcessCommandEx(proc, ProcSourceDefault);
}

#if 1
/** \brief Backward compatibility,
*/
MN_INLINE void process_SetWatchdogFlag(taskid_t  taskid)
{
    syswd_TickleWatchdog(taskid);
}
#endif

extern void process_InitData(void);

extern void process_SetRequestorFlag(u16 flag);

extern tick_t process_SampleAndClearOverhead(void);

extern void process_ProcessTaskLoop(void);

//-------------- Required project-specific interfaces ------------------

/** \brief Returns application-specific process cancellation bitmap.
May execute arbitrary (but not long) application code, e.g. UI
\return process cancellation bitmap (a bitwise OR of CANCELPROC_... constants)
*/
extern u8_least process_CheckSpecific(void);

/** \brief Notifies interested parties, e.g. UI, that a process
that started without ProcSourceUI flag has ended
*/
extern void process_NotifyEnd(void);

/** \brief Notifies interested parties, e.g. UI, that a process
that started with ProcSourceUI flag has ended
*/
extern void process_NotifyEndUI(s8 uiplace, s16 procdetails);

/** \brief Performs final cleanup after a process exits (including the buffer
guard part, if any). Example: Sync control mode and setpoint with deferred input,
or any such cleanup.
\param ProcId - Id of the exiting process
*/
extern void process_EndHook(ProcId_t ProcId);

#endif //PROCESS_H_

/* This line marks the end of the source */
