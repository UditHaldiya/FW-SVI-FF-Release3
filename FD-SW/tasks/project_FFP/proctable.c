/*
Copyright 2005-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file proctable.c
    \brief Project-specific tables defining the actions of process.c.

    CPU: Any

    OWNER: AK

    \ingroup Process
*/
//#include "projectdef.h"
#include "mnwrap.h"
#include "oswrap.h"
#include "errcodes.h"
//#include "devicemode.h"
#include "nvram.h"
#include "procshims.h"
#include "selftest.h"
//#include "diagnostics.h"
//#include "datahog.h"

#include "logfproc.h"
#include "clonenvram.h"

#include "mn_fwdl.h"
#include "process.h"
#include "faultpublic.h"
#include "procpriv.h"

//#include "uistartnodes.h"
#include "hartfunc.h" //for HC_WRITE_COMMAND and such

#include "timer.h"
//#include "poscharact.h"
//#include "doswitch.h"
#include "nvffext.h"

#include "logfproc.h"
#include "facdefaults.h"
#include "ptbif.h"

// trick to use hartfunc.h in AP build
CONST_ASSERT (HC_WRITE_COMMAND != 0u);

/* \brief An empty function to make an empty process non-NULL
*/
static procresult_t DummyProc(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    return PROCRESULT_OK;
}

/** Array of definitions of "long processes" indexed by project-independent
"process ids".
If an entry is not explicitly iniitialized, it happens to have a NULL function pointer,
and no function will be run at a request with an uninitialized entry.
*/
const proctable_t proctable[] =
{
    {
        .id = PROC_NONE,
        .procf = nvram_PageTest_SHIM,
        .flags = {.throughflags=0xFFU, .initflags = 0U}, //everything whatsoever is allowed
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#if 0 //until we get to cloning/translation
    {
        .id = PROC_EMPTY_WRAPPER,
        .procf = nvram_DummyProcess,
        .flags = {.throughflags=0xffU, .initflags = 0U}, //everything is allowed
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#endif //0
    {
        .id = PROC_HART_SUB132_INIT_WITHCAL,
        .procf = hart_procRamCommitWithCal_SHIM,
        .flags = {.throughflags=0U, .initflags = 0U},
        .action =
        { //absolutely stealth
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#if 0 //new nvram
    {
        .id = PROC_HART_RAM_COMMIT,
        .procf = hart_procRamCommit,
        .flags = {.throughflags=0U, .initflags = 0U},
        .action =
        { //absolutely stealth
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#endif //OLD_NVRAM

    {
        .id = PROC_CANCEL_PROC,
        .procf = DummyProc, //we need a non-NULL placeholder for a process
        .flags = {.throughflags=HC_WRITE_COMMAND, .initflags = 0U},
        .action =
        { //absolutely stealth
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] = //dummy: cannot be canceled
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] = //dummy: cannot fail
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#if 1 //future, perhaps: (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE) //TODO: This is a kludgy conditional!
    {
        .id = PROC_CLONE_NVMEM,
        .procf = nvmem_Clone,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NVM_WRITE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
    {
        .id = PROC_UPLOAD_NVMEM,
        .procf = nvmem_PrepareUpload,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NVM_WRITE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
    {
        .id = PROC_DOWNLOAD_NVMEM,
        .procf = nvmem_WriteImageProc,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NVM_WRITE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST
#endif //FEATURE_CPU
    {
        .id = PROC_FILE_NVMEM,
        .procf = nvmem_SaveAsFactoryDefaults,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NV_BK_RESTORE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
    {
        .id = PROC_RESTORE_FILED_NVMEM,
        .procf = nvmem_RestoreFactoryDefaults,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NV_BK_RESTORE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
    {
        .id = PROC_RESTORE_FW_NVMEM,
        .procf = proc_FFP_RestoreFirmwareDefaults,
        .flags = {.throughflags=0U, .initflags = 0U},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NV_BK_RESTORE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NV_BK_RESTORE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
    {
        .id = PROC_WRITE_LOGFILE,
        .procf = logf_WriteDeferred,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
    {
        .id = PROC_FWDL,
        .procf = fwdl_ProcEnvelope,
        .flags = {.throughflags=0U, .initflags = PROCINIT_CLAIMDIAGBUFFER},
        .action =
        {
            [PROCRESULT_OK] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_CANCELED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
            [PROCRESULT_FAILED] =
            {
                .event = FAULT_NONE,
                .UIplace = -1,
                .termflags = PROCTERMFLAG_NOCTLMODE,
            },
        }
    },
};

const u8 proctable_size = NELEM(proctable); //!< exported size of proctable

/** Array of function pointers (to mop-up - deferred action - functions).
process.c services one function at a time in cyclical order.
*/
MopupFunc_t * const mopuplist[] =
{
    //error_Mopup, //deferred fault storage save (NVRAM save)
    //mode_Mopup,
    selftest_FlashCrcMon,
    nvmem_Mopup,
    logf_WriteMopup,
    syswd_Mopup,
    nvmem_Mopup,
    logf_WriteMopup,
    nvmem_Mopup,
    logf_WriteMopup, //several times to make it a bit faster
    facdef_Mopup,

    //timer_IntegrityCheck,
    //error_TestData,
};

const u8 mopuplist_size = NELEM(mopuplist); //!< exported size of mopuplist

/* This line marks the end of the source */
