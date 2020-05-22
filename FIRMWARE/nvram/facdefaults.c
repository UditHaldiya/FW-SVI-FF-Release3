/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvrw.c
    \brief valve diagnostic signature read/write

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#define NEED_NVMEM_END
#include "mnwrap.h"
#include "mnassert.h"
#include <nvramtypes.h>
#include "facdefaults.h"
#include "process.h"
#include "fram.h"
#include "faultpublic.h"

#include "logfile.h"
#include "logfileids.h"
//#include "nvram.h"
#include "nvmempriv.h"
#include MEMMAP_H_
#include "nvramtable.h"
#include "bufferhandler.h"
#include "dimensions.h"

typedef struct nvReadWrite_t
{
    u8 volid;
    u8 mask_flags;
    u8 match_flags;
    u8 test_only;
} nvReadWrite_t;

static nvReadWrite_t nvrw; //! Interface to process

/** \brief A helper
\param volid - a bitmask of volumes to read
\param mask_flags - a bitmask of flags in NV map to match
\param match_flags - a bitmask to check against
*/
static void nv_SetReq(u8 volid, u8 mask_flags, u8 match_flags)
{
    nvrw.volid = volid;
    nvrw.mask_flags = mask_flags;
    nvrw.match_flags = match_flags;
}


/** \brief Interface to glue layer to launch a process of saving factory defaults to a log file
\param volid - what NVMEM volume to save
\return an error code
*/
ErrorCode_t nvmem_LaunchFactorySave(void)
{
    return process_SetProcessCommand(PROC_FILE_NVMEM);
}

/** \brief Interface to glue layer to launch a process of reading NVMEM from a log file
\param volid - bitmap of what NVMEM volumes to restore
\param mask_flags - curently, only DIAGRW_EXT_SIGNATURE
\param match_flags - the test is (nvram_map[nvramid].flags & mask_flags) == match_flags
\return an error code
*/
ErrorCode_t nvmem_LaunchFactoryRestore(u8 volid, u8 mask_flags, u8 match_flags, u8 test_only)
{
    nv_SetReq(volid, mask_flags, match_flags);

    nvrw.test_only = test_only;
    u8 fullid = LOGF_FULL_ID(NVMBACKUP_LOGFILE_ID, 0U);

    ErrorCode_t err;
    if(!logf_Exist(fullid))
    {
        err = ERR_OK;
    }
    else
    {
        err = process_SetProcessCommand(PROC_RESTORE_FILED_NVMEM);
    }
    return err;
}

//------------ Actual process section -------------------

//Redundant-ish definitions for the first cut
//lint -emacro({826}, CRC_ADDR)  area too small:  The checksum is the two bytes beyond (dst + len)
#define CRC_ADDR(addr, len) ((u16 *)((u8*)(addr) + (len)))
#define NVM_H_MAXSIZE ((NVM_MAXSIZE+(sizeof(u16)-1U))/sizeof(u16)) //size in halfwords

CONST_ASSERT(NVM_H_MAXSIZE < (1U<<DIAG_BUFFER_LOGSIZE));

/** \brief Process of writing a buffer to a log file
\return a process completion code
*/
static procresult_t nvmem_SaveAsFactoryDefaults_Naked(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    u16 *nvbuf = (u16 *)buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);

    const u8 fullid = LOGF_FULL_ID(NVMBACKUP_LOGFILE_ID, 0U);
    u16 len;
    ErrorCode_t err;
    MN_FRAM_ACQUIRE();
        err = logf_Open(fullid, LOG_WRITE, NULL);
    MN_FRAM_RELEASE();

    error_SetFault(FAULT_FACTORYWRITE); //disable "normal" NVMEM writes

    nvramId_fast_t id;
    for(id=0; id<NVRAM_ENTRIES; id++)
    {
        if(err != ERR_OK)
        {
            break;
        }

        len = nvram_map[id].length;  //for CRC field
        const u16 *pCheckWord = CRC_ADDR(nvbuf, len);
        MN_FRAM_ACQUIRE();
            err = nvmem_ReadVol((void *)nvbuf,
                               (nvram_map[id].offset + nvmem_GetVolumeBase(nvram_map[id].volid)),
                               len + sizeof(u16),
                               nvram_map[id].volid);
        MN_FRAM_RELEASE();

        if(err == ERR_OK)
        {
            u16 crc = hCrc16(CRC_SEED, nvbuf, len/2U); //length is in halfwords
            if(crc != *pCheckWord)
            {
                err = ERR_NVMEM_CRC;
            }
        }

        if(err == ERR_OK)
        {
            if(process_WaitForTimeExt(1U, CANCELPROC_MODE) != 0) //let periodic services (mopup and WD) run
            {
                err = ERR_PROCESS_START; //AK: a kludgy reuse of an error code
                procresult = PROCRESULT_CANCELED;
            }
        }
        if(err == ERR_OK)
        {
            len = nvram_map[id].length + sizeof(u16);
            MN_FRAM_ACQUIRE();
                err = logf_Write(nvbuf, &len, fullid);
            MN_FRAM_RELEASE();
        }
        if(err == ERR_OK) //wait again
        {
            if(process_WaitForTimeExt(1U, CANCELPROC_MODE) != 0) //let periodic services (mopup and WD) run
            {
                err = ERR_PROCESS_START; //AK: a kludgy reuse of an error code
                procresult = PROCRESULT_CANCELED;
            }
        }
    }

    //close the file
    MN_FRAM_ACQUIRE();
        //re-enable "normal" NVMEM writes; this would also allow to close the file
        error_ClearFault_Private(FAULT_FACTORYWRITE);

        ErrorCode_t err1 = logf_Close(fullid, (err != ERR_OK));
        if(err == ERR_OK)
        {
            err = err1;
            /* Explanation:
            If ERR_OK before closing the file, there still may be an error closing.
            Otherwise, we close with discard, and (though technically this doesn't
            ever fail) we don't care.
            */
        }
    MN_FRAM_RELEASE();

    if(err == ERR_OK)
    {
        FactoryDefaultState_t fds;
        (void)facdef_GetState(&fds);
        fds.first_time = false;
        err = facdef_SetState(&fds);
    }

    if(err == ERR_OK)
    {
        procresult = PROCRESULT_OK;
    }
    return procresult;
}

/** \brief Process of writing a buffer to a log file.

Aborts processing if there is NVMEM fault.
\return a process completion code
*/
procresult_t nvmem_SaveAsFactoryDefaults(s16 *procdetails)
{
    procresult_t procresult = PROCRESULT_FAILED;
    if(!error_IsFault(FAULT_NVM_CHECKSUM0))
    {
        procresult = nvmem_SaveAsFactoryDefaults_Naked(procdetails);
    }
    return procresult;
}

/** \brief Process of restoring from a log file
\return a process completion code
*/
procresult_t nvmem_RestoreFactoryDefaults(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    u16 *nvbuf = (u16 *)buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);

    const u8 fullid = LOGF_FULL_ID(NVMBACKUP_LOGFILE_ID, 0U);
    u16 len;
    ErrorCode_t err;
    MN_FRAM_ACQUIRE();
        err = logf_Open(fullid, LOG_READ, &len);
    MN_FRAM_RELEASE();

    error_SetFault(FAULT_FACTORYWRITE); //disable "normal" NVMEM writes

    nvramId_fast_t id;
    for(id=0; id<NVRAM_ENTRIES; id++)
    {
        if(err != ERR_OK)
        {
            break;
        }
        len = nvram_map[id].length;  //for CRC field
        const u16 *pCheckWord = CRC_ADDR(nvbuf, len);
        len += sizeof(u16);
        MN_FRAM_ACQUIRE();
            err = logf_Read(nvbuf, &len, fullid);
        MN_FRAM_RELEASE();

        //This critical process can't be canceled
        (void)process_WaitForTime(1U); //let periodic services (mopup and WD) run

        if(err == ERR_OK)
        {
            u16 crc = hCrc16(CRC_SEED, nvbuf, nvram_map[id].length/2U); //length is in halfwords
            if(crc != *pCheckWord)
            {
                err = ERR_NVMEM_CRC;
            }
        }

        if( (nvrw.test_only == 0)
           && (((1U<<nvram_map[id].volid) & nvrw.volid) != 0U)
           && ((nvram_map[id].flags & nvrw.mask_flags) == nvrw.match_flags)
           && (id != NVRAMID_logdata) //this one may be temporarily: the right place is flags
               )
        {
            if(err == ERR_OK)
            {
                MN_FRAM_ACQUIRE();
                    err = nvmem_WriteVol((void *)nvbuf,
                                       (nvram_map[id].offset + nvmem_GetVolumeBase(nvram_map[id].volid)),
                                       nvram_map[id].length + sizeof(u16),
                                       nvram_map[id].volid);
                MN_FRAM_RELEASE();
            }

            //This critical process can't be canceled
            (void)process_WaitForTime(1U); //let periodic services (mopup and WD) run
        }
    }

    //close the file
    MN_FRAM_ACQUIRE();
        (void)logf_Close(fullid, false);
    MN_FRAM_RELEASE();

    error_ClearFault_Private(FAULT_FACTORYWRITE); //re-enable "normal" NVMEM writes

    if(err == ERR_OK)
    {
#if 0 //AK: I disagree with motivation of it but who am I to disagree?
        /* Set stops fault even though we don't restore calibrations
        */
        error_SetFault(FAULT_FIND_STOPS_FAILED);
        //Since we are expecting reset, make sure it got written
        error_Mopup();
#endif
        procresult = PROCRESULT_OK;
    }

    //Post-processing cleanup

    //This is N/A anymore: we enabled it already to save a fault (see above)
    /* *DO NOT* re-enable "normal" NVMEM writes:
    The restored NVMEM may not be compatible with restored content.
    Reset is required to activate the restored content.
    */

    error_ClearFault(FAULT_FACTORYMODE);

    return procresult;
}

// ----------- here is the addition of restoring to FW defaults ----------

/** \brief Process of restoring FW defaults
\return a process completion code
*/
procresult_t nvmem_RestoreFirmwareDefaults(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    ErrorCode_t err = ERR_OK;

    nvramId_fast_t id;
    for(id=0; id<NVRAM_ENTRIES; id++)
    {
        if((nvram_map[id].flags & NVMFLAG_RESTORED) != 0U)
        {
            ErrorCode_t err1 = nvmem_SetItemById(NULL, id);
            if(err == ERR_OK)
            {
                err = err1; //capture first error
            }
            //This critical process can't be canceled
            (void)process_WaitForTime(1U); //let periodic services (mopup and WD) run
        }
    }

    if(err == ERR_OK)
    {
        procresult = PROCRESULT_OK;
    }

    return procresult;
}


/* This line marks the end of the source */
