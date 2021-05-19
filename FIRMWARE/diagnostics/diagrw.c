/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file diagrw.c
    \brief valve diagnostic signature read/write

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#include "mnwrap.h"
#include "diagrw.h"
#include "diagnostics.h"
#include "process.h"
#include "bufferhandler.h"

#include "logfile.h"
#include "logfileids.h"
#include "nvram.h"
#include "hart.h" //for device id

typedef struct diagReadWrite_t
{
    u8 SignatureType;
    u8 SignatureAssignment;
    u8 BufferId;
    u8 FileId;
} diagReadWrite_t;

static diagReadWrite_t diagrw; //! Interface to process

/** \brief A helper
*/
static ErrorCode_t diag_SetWriteReq(u8 SignatureType, u8 SignatureAssignment)
{
    ErrorCode_t err = ERR_OK;
    if(!((SignatureType == DIAGRW_EXT_SIGNATURE) || (SignatureType == DIAGRW_PST)))
    {
        err = ERR_INVALID_PARAMETER;
    }

    if(!((SignatureAssignment==DIAGRW_CURRENT) || (SignatureAssignment==DIAGRW_BASELINE) || (SignatureAssignment==DIAGRW_USER)))
    {
        err = ERR_INVALID_PARAMETER;
    }
    if(err == ERR_OK)
    {
        diagrw.SignatureType = SignatureType;
        diagrw.SignatureAssignment = SignatureAssignment;
    }
    return err;
}

//Since file ids are generated, need translation
static const u8 fileids[] =
{
    [DIAGRW_USER] = DIAGSIGN_USER_LOGFILE_ID,
    [DIAGRW_CURRENT] = DIAGSIGN_CURRENT_LOGFILE_ID,
    [DIAGRW_BASELINE] = DIAGSIGN_BASELINE_LOGFILE_ID,
    [DIAGRW_PST] = PST_LOGFILE_ID,
};

static const diag_t diagids[] =
{
    [DIAGRW_USER] = DIAG_EXT_ACT,
    [DIAGRW_CURRENT] = DIAG_EXT_ACT,
    [DIAGRW_BASELINE] = DIAG_EXT_ACT,
    [DIAGRW_PST] = DIAG_PST,
};
/** \brief Prepares data for writing default buffer to a log file in a process context
\param SignatureType - curently, only DIAGRW_EXT_SIGNATURE or PST
\param SignatureAssignment - one of DIAG{PST, SIGN_{USER,CURRENT,BASELINE}}_LOGFILE_ID
\return an error code
*/
ErrorCode_t diag_PrepareSignatureWrite(u8 SignatureType, u8 SignatureAssignment)
{
    ErrorCode_t err = diag_SetWriteReq(SignatureType, SignatureAssignment);
    if(err == ERR_OK)
    {
        if(buffer_GetEntriesInXDiagnosticBuffer(DIAGBUF_DEFAULT) <= EXTDIAG_HEADERSZ)
        {
            //No data
            err = ERR_DIAG_TYPE_NOT_AVAILABLE;
        }
    }

    if(err == ERR_OK)
    {
        //Check that the default buffer has a signature
        const diag_t *p = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT); //guaranteed non-NULL
        if(p[0] != diagids[SignatureType])
        {
            //Wrong signature
            err = ERR_DIAG_TYPE_NOT_AVAILABLE;
        }
    }

    if(err == ERR_OK)
    {
        diagrw.FileId = LOGF_FULL_ID(fileids[SignatureAssignment], 0U);
        diagrw.BufferId = DIAGBUF_DEFAULT;
    }
    return err;
}

/** \brief Interface to glue layer to launch a process of writing default buffer to a log file
\param SignatureType - curently, only DIAGRW_EXT_SIGNATURE or PST
\param SignatureAssignment - one of DIAG{PST, SIGN_{USER,CURRENT,BASELINE}}_LOGFILE_ID
\return an error code
*/
ErrorCode_t diag_LaunchSignatureWrite(u8 SignatureType, u8 SignatureAssignment)
{
    ErrorCode_t err = ERR_OK;

    /* Before we do anything, check that there *is* something to write.
       Then, write unconditionally.
    */
    if(!process_IsGuardingDiagBuffer()) //Do we have the buffer intact?
    {
        err = ERR_INVALID_PARAMETER;
    }
    if(err == ERR_OK)
    {
        //Does the buffer header say it is a signature? And other checks
        err = diag_PrepareSignatureWrite(SignatureType, SignatureAssignment);
    }

    if(err == ERR_OK)
    {
        process_ForceProcessCommand(PROC_WRITE_BUFFER);
    }
    return err;
}


/** \brief Interface to glue layer to launch a process of reading a buffer from a log file
\param SignatureType - curently, only DIAGRW_EXT_SIGNATURE
\param SignatureAssignment - one of DIAGSIGN_{USER,CURRENT,BASELINE}_LOGFILE_ID
\param FileVersion - age of the file
\param BufferId - buffer to read into
\return an error code
*/
ErrorCode_t diag_LaunchSignatureRead(u8 SignatureType, u8 SignatureAssignment, u8 FileVersion, u8 BufferId)
{
    ErrorCode_t err = diag_SetWriteReq(SignatureType, SignatureAssignment);
    if(err != ERR_OK)
    {
        return err;
    }

    if(FileVersion > LOGF_MAX_AGE)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(BufferId > NUM_DIAG_BUFFERS)
    {
        return ERR_INVALID_PARAMETER;
    }

    u8 fullid = LOGF_FULL_ID(fileids[SignatureAssignment], FileVersion);
    if(!logf_Exist(fullid))
    {
        return ERR_HART_NO_DATA_AVAILABLE;
    }

    diagrw.FileId = fullid;
    diagrw.BufferId = BufferId;

    err = process_SetProcessCommand(PROC_READ_BUFFER);

    return err;
}

//------------ Actual process section -------------------

/** \brief Process of writing a buffer to a log file
\return a process completion code
*/
procresult_t diag_WriteBuffer(s16 *procdetails)
{
    return diag_WriteBufferEx(procdetails, UINT16_MAX);
}

procresult_t diag_WriteBufferEx(s16 *procdetails, s16_least maxlen)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    u16 len;
    s16_least i, iend;
    ErrorCode_t err;
    MN_FRAM_ACQUIRE();
        err = logf_Open(diagrw.FileId, LOG_WRITE, NULL);
    MN_FRAM_RELEASE();

    const diag_t* data;
    data = buffer_GetXDiagnosticBuffer(diagrw.BufferId);

    if(data != NULL) //skip saving data from a non-existent buffer
    {
        iend = buffer_GetEntriesInXDiagnosticBuffer(diagrw.BufferId)/2; //we write in pairs
        iend = MIN(iend, maxlen); //limit the size of a write
        for(i=0; i<iend; i++)
        {
            if(err == ERR_OK)
            {
                if(process_WaitForTime(1U)) //let periodic services (mopup and WD) run
                {
                    err = ERR_PROCESS_START; //AK: a kludgy reuse of an error code
                    procresult = PROCRESULT_CANCELED;
                }
            }
            if(err == ERR_OK)
            {
                MN_FRAM_ACQUIRE();
                    len = sizeof(*data)*2U; //data in pairs
                    err = logf_Write(&data[i*2], &len, diagrw.FileId);
                MN_FRAM_RELEASE();
            }
            if(err != ERR_OK)
            {
                break;
            }
        }
    }

    //close the file
    MN_FRAM_ACQUIRE();
        ErrorCode_t err1 = logf_Close(diagrw.FileId, (err != ERR_OK));
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
        procresult = PROCRESULT_OK;
    }
    return procresult;
}

/** \brief Process of reading a buffer from a log file
\return a process completion code
*/
procresult_t diag_ReadBuffer(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    u16 len;
    ErrorCode_t err;
    MN_FRAM_ACQUIRE();
        err = logf_Open(diagrw.FileId, LOG_READ, &len);
    MN_FRAM_RELEASE();

    buffer_InitializeXDiagnosticBuffer(diagrw.BufferId);

    u16 rlen = 0;
    do
    {
        if(err == ERR_OK)
        {
            if(process_WaitForTime(1U)) //let periodic services (mopup and WD) run
            {
                err = ERR_PROCESS_START; //AK: a kludgy reuse of an error code
                procresult = PROCRESULT_CANCELED;
            }
        }
        if(err == ERR_OK)
        {
            dsample_t data;
            rlen = sizeof(data); //data in pairs
            MN_FRAM_ACQUIRE();
                err = logf_Read(&data, &rlen, diagrw.FileId);
            MN_FRAM_RELEASE();
            if(rlen != 0)
            {
                bool_t b = buffer_AddXDiagnosticData2(diagrw.BufferId, data.data1, data.data2);
                if(b)
                {
                    //buffer overflow - should not happen
                    err = ERR_DIAG_TYPE_NOT_AVAILABLE;
                }
            }
        }
        if(err != ERR_OK)
        {
            break;
        }
    } while(rlen != 0);

    //close the file
    MN_FRAM_ACQUIRE();
        (void)logf_Close(diagrw.FileId, false);
    MN_FRAM_RELEASE();
    if(err == ERR_OK)
    {
        procresult = PROCRESULT_OK;
    }
    else
    {
        //discard any reads
        buffer_InitializeXDiagnosticBuffer(diagrw.BufferId);
    }
    return procresult;
}

//Utilities
static diag_t buf_use_count = 0;

/** \brief A quickie util to populate the buffer header
\param header - the header to copy
\param numentries - number of elements in the header
*/
void diag_WriteBufferHeader(const diag_t header[], size_t numentries)
{
    size_t i;
    diag_t *p = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);

    //Stick in device id at the end of the header;
    //If the content is too long, it may overwrite the id
    CONST_ASSERT((DEVID_SIZE*sizeof(*p)) >= HART_ID_LENGTH);
    CONST_ASSERT(DEVID_SIZE < DIAGRW_HEADERSZ);
    diag_t *devid = p + (DIAGRW_HEADERSZ - DEVID_SIZE);
    mn_memset(devid, 0, DEVID_SIZE*sizeof(*devid));
    
    //An afterthought to stick the high halword of sampling interval
    devid[0] = p[2]; 
    p[2] = EXTDIAG_HEADERSZ;
    
    devid[1] = buf_use_count++;
    MN_ENTER_CRITICAL();
        mn_memcpy(&devid[2], hart_GetHartData()->device_id, HART_ID_LENGTH);
    MN_EXIT_CRITICAL();

    for(i=0; i < numentries; i++)
    {
        p[i] = header[i];
    }
    for(; i < (DIAGRW_HEADERSZ - DEVID_SIZE); i++)
    {
        p[i] = DIAGRW_HEADER_FILLER; //just fill the space with a pleasing filler
    }
}

/* This line marks the end of the source */
