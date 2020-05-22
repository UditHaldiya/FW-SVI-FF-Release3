/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file logfproc.c
    \brief Implementation of log files write as a helper for mopup services of process task.

    CPU: Any

    OWNER: AK

    \ingroup logfile
*/
#include "mnwrap.h"
#include MEMMAP_H_
#define NEED_NVMEM_END //expose hidden stuff
#include "logfile.h"
#include "logfileids.h"
#include "logfsupport.h"
#include "logfdata.h"
#include "logfproc.h"
#include "nvram.h"
#include "bufferhandler.h"
#include "dimensions.h"

#include <keywords.h>
#include <osif.h>

typedef struct AllLogfWrites_t
{
    const u8 *ptr[LOGF_NUMFILES]; //!< Array of data pointers presumed persistent
    u16 len[LOGF_NUMFILES]; //!< Array of lengths (0 means no request)
    u8 curr; //!< Log file id currently being written out
    u16 CheckWord;
} AllLogfWrites_t; //Type of write requests for "background" log files

static AllLogfWrites_t AllLogfWrites =
{
    .ptr = ALL_ZEROES,
    .len = ALL_ZEROES,
    .curr = 0,
    .CheckWord = CRC_SEED,
};

/** \brief Submits logfile for write.
\param logId - one of the predefined log file ids
\param data - a pointer to data to write. The content shall not move elsewhere
\param len - length of data to write
\return an error code
*/
ErrorCode_t logf_SubmitWrite(u8 logId, const void *data, u16 len)
{
    ErrorCode_t err = ERR_OK;
    if(logId >= NELEM(AllLogfWrites.ptr))
    {
        err = ERR_LOGF_INVALID;
    }
    else if(data == NULL)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else if((len > LOGF_MAX_SIZE_REQUIRED) || (len == 0))
    {
        err = ERR_LOGF_LENGTH;
    }
    else
    {
        MN_ENTER_CRITICAL();
            if(AllLogfWrites.len[logId] == 0)
            {
                storeMemberPtr(&AllLogfWrites, ptr[logId], (const u8 *)data); //cast needed to satisfy safeguards in storeMemberPtr
                storeMemberInt(&AllLogfWrites, len[logId], len);
            }
            else
            {
                if(AllLogfWrites.ptr[logId] != data)
                {
                    //Unexpected collision
                    err = ERR_NOT_SUPPORTED;
                }
            }
        MN_EXIT_CRITICAL();
    }
    return err;
}

/** \brief A helper to advance to the next file to write
\param curr - current log id
*/
static void nextlogf(u8 curr)
{
    //move to next
    ++curr;
    if(curr == NELEM(AllLogfWrites.len))
    {
        curr = 0;
    }
    MN_ENTER_CRITICAL();
        storeMemberInt(&AllLogfWrites, curr, curr);
    MN_EXIT_CRITICAL();
}

#define LOGF_MOPUP_CHUNK 80 //number taken from thin air

/** \brief The process mopup routine to write out delayed-write log files
*/
void logf_WriteMopup(void)
{
    Struct_Test(AllLogfWrites_t, &AllLogfWrites);

    u8 curr = AllLogfWrites.curr;
    if(AllLogfWrites.len[curr] == 0)  //criterion of nothing to write
    {
        if(process_GetProcId() != PROC_WRITE_LOGFILE)
        {
            //we are not writing it
            nextlogf(curr);
        }
    }
    else
    {
        ErrorCode_t err = process_SetProcessCommand(PROC_WRITE_LOGFILE);
        MN_DBG_ASSERT(err != ERR_INVALID_PARAMETER); //sanity check
        UNUSED_OK(err); //for Release build
        /* EXPLANAITION: If a process is running, we'll wait until next time
        */
    }
}

procresult_t logf_WriteDeferred(s16 *procdetails)
{
    ErrorCode_t err; //        ERR_OK;
    UNUSED_OK(procdetails);
    u8 curr = AllLogfWrites.curr;
    u16 len = AllLogfWrites.len[curr]; //file length to write
    u16 len_saved = len;
    if(len != 0) //not really needed if we got here
    {
        //yes; prepare the write
        MN_NVMEM_LOCK(8U); //small number to read the file header
            err = logf_Open(curr, LOG_WRITE, &len);
        MN_NVMEM_UNLOCK();
        CONST_ASSERT(LOGF_MAX_SIZE_REQUIRED < ((1U<<DIAG_BUFFER_LOGSIZE)/2U)); //[LOGF_MAX_SIZE_REQUIRED] bytes needed
        u8 *logfbuf = (void *)buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT); //! to hold the image of a log file
        osif_disable_all_tasks();
        mn_memcpy(logfbuf, AllLogfWrites.ptr[curr], len);
        (void)process_WaitForTime(1U);

        //mark the file written (preliminarily)
        storeMemberInt(&AllLogfWrites, len[curr], 0);
        osif_enable_all_tasks();

        //Write the file
        bool_t cancel;
        u16 offset = 0;
        do
        {
            u16 chunk = MIN(LOGF_MOPUP_CHUNK, len);
            MN_DBG_ASSERT(chunk != 0);
            MN_NVMEM_LOCK(len);
                err = logf_Write(logfbuf + offset, &chunk, curr);
            MN_NVMEM_UNLOCK();
            cancel = process_WaitForTime(1U) || (err != ERR_OK);
            if(cancel)
            {
                break;
            }
            offset += chunk;
            len -= chunk;
        } while (len != 0);

        MN_NVMEM_LOCK(len);
            err = logf_Close(curr, !cancel);
        MN_NVMEM_UNLOCK();

        if(cancel || (err!=ERR_OK))
        {
            //failed for some reason; restore the request
            MN_ENTER_CRITICAL();
                if(AllLogfWrites.len[curr] == 0) //no new request
                {
                    storeMemberInt(&AllLogfWrites, len[curr], len_saved);
                }
            MN_EXIT_CRITICAL();
        }

        //We gave this file a fair shot; advance to next. Come back here on around trip.
        nextlogf(curr);
    }
    return PROCRESULT_OK;
}

/* This line marks the end of the source */
