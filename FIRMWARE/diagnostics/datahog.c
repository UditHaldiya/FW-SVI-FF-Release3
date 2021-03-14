/*
Copyright 2014-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file datahog.c
    \brief Implementation of high-speed data collection

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#include "mnwrap.h"
#include "datahog.h"
#include "diagnostics.h"
#include "timebase.h"
#include "mnassert.h"
#include "diagrw.h"
#include "oswrap.h"
#include "digitalsp.h"
#include "ipcdefs.h"

#ifdef DATAHOG_POSITION
#include "position.h"
#endif

#if defined(DATAHOG_MAINPRESSURE) || defined(DATAHOG_PILOTPRESSURE) || defined(DATAHOG_SUPPLYPRESSURE) || defined(DATAHOG_PRESSUREB)
#include "pressures.h"
#endif

#ifdef DATAHOG_IPCURRENT
#include "ipcurr.h"
#endif

#ifdef DATAHOG_SETPOINT
#include "devicemode.h"
#include "ctllimits.h"
#endif

#ifdef DATAHOG_AI_INPUT
#include "inpv.h"
#endif

typedef s16 DatahogFunc_t(void);

//--------------------- Shims --------------------------
#ifdef DATAHOG_SETPOINT
static s16 getsp(void)
{
    s32 sp;
    s16 ret;
    ctlmode_t ctlmode = mode_GetEffectiveControlMode(&sp);
    if((ctlmode == CONTROL_OFF) || (sp == SETPOINT_INVALID))
    {
        ret = INT16_MIN; //indication of invalid value
    }
    else
    {
        ret = (s16)sp;
    }
    return ret;
}
#endif //DATAHOG_SETPOINT

#ifdef DATAHOG_PILOTPRESSURE
static s16 getpilotpres(void)
{
    return pres_GetPressureData()->Pressures[PRESSURE_PILOT_INDEX];
}
#endif

#ifdef DATAHOG_SUPPLYPRESSURE
static s16 getsupplypres(void)
{
    return pres_GetPressureData()->Pressures[PRESSURE_SUPPLY_INDEX];
}
#endif

#ifdef DATAHOG_PRESSUREB
static s16 getpresb(void)
{
    return pres_GetPressureData()->Pressures[PRESSURE_ACT2_INDEX];
}
#endif

#ifdef DATAHOG_IPCURRENT
static s16 getipcirr(void)
{
    return (s16)ipcurr_GetCompensatedIpCurrent();
}
#endif
//-------------------- end shims ---------------------------

static  DatahogFunc_t *const DatahogTable[] =
{
#ifdef DATAHOG_POSITION
    [DATAHOG_POSITION] = vpos_GetScaledPosition,
#endif
#ifdef DATAHOG_MAINPRESSURE
    [DATAHOG_MAINPRESSURE] = pres_GetMainPressure,
#endif
#ifdef DATAHOG_PILOTPRESSURE
    [DATAHOG_PILOTPRESSURE] = getpilotpres,
#endif
#ifdef DATAHOG_SUPPLYPRESSURE
    [DATAHOG_SUPPLYPRESSURE] = getsupplypres,
#endif
#ifdef DATAHOG_PRESSUREB
    [DATAHOG_PRESSUREB] = getpresb,
#endif
#ifdef DATAHOG_SETPOINT
    [DATAHOG_SETPOINT] = getsp,
#endif
#ifdef DATAHOG_IPCURRENT
    [DATAHOG_IPCURRENT] = getipcirr,
#endif
#ifdef DATAHOG_AI_INPUT
    [DATAHOG_AI_INPUT] = inpv_GetPV,
#endif
};

static DatahogConf_t DatahogConf[HogConfsCount];
static DatahogState_t DatahogState;

/** \brief Get Datahog state function
*/
const DatahogState_t *datahog_GetState(DatahogState_t *dst)
{
    return STRUCT_TESTGET(&DatahogState, dst);
}


static const DatahogConf_t DatahogConf_default =
{
    .datamask = 1U,
    .taskid = TASKID_CYCLE,
    .skip_count = 0,
    .CheckWord = 0U, //don't care
};


/** \brief Get function (persistent/permanent)
*/
const DatahogConf_t *datahog_GetPerm(DatahogConf_t *dst)
{
    return STRUCT_TESTGET(&DatahogConf[HogConfPerm], dst);
}


#define HOG_MAX_VARS_AT_CONTROL 4U //! max number of variables to sample in control context
/** \brief Get function ( Get temporary)
*/
const DatahogConf_t *datahog_Get(DatahogConf_t *dst)
{
    return STRUCT_TESTGET(&DatahogConf[HogConfTemporary], dst);
}

/** \brief Tests data collection bitmap against the collection table
\param datamask - requested data collection bitmap
\return number of channels to collect (0 indicates an error
*/
u8_least datahog_TestDataMap(u16 datamask)
{
    u16_least mask = 1U;
    u8_least numvars = 0U;
    for(size_t i=0; i<sizeof(datamask)*CHAR_BIT; i++)
    {
        if((mask & datamask) != 0U)
        {
            //Collection requested
            if((i >= NELEM(DatahogTable)) || (DatahogTable[i] == NULL))
            {
                numvars = 0;
                break;
            }
            numvars++;
        }
        mask <<= 1;
    }
    return numvars;
}

static ErrorCode_t datahog_SetX(const DatahogConf_t *src, DatahogConfId_t confid, DatahogStatus_t status)
{
    if(src == NULL)
    {
        src = &DatahogConf_default;
    }

    if((src->num_presamples != 0) && (confid == HogConfTemporary))
    {
        return ERR_INVALID_PARAMETER;
    }

    //Check that all data requests have valid collection functions
    ErrorCode_t err = ERR_OK;
    u8_least numvars = datahog_TestDataMap(src->datamask);

    if(numvars == 0U)
    {
        err = ERR_NOT_SUPPORTED;
    }
    else if((src->num_presamples * numvars) >= DIAGNOSTIC_BUFFER_SIZE_AUX)
    {
        err = ERR_INVALID_PARAMETER; //ERR_HART_PARAM_TOO_SMALL;
    }
    else if(src->taskid == TASKID_CONTROL)
    {
        if(numvars > HOG_MAX_VARS_AT_CONTROL)
        {
            err = ERR_INVALID_PARAMETER; //ERR_HART_PARAM_TOO_BIG;
        }
        //else OK
    }
    else if(src->taskid == TASKID_CYCLE)
    {
        //OK
    }
    else
    {
        err = ERR_INVALID_PARAMETER;
    }

    if(err == ERR_OK)
    {
        Struct_Copy(DatahogConf_t, &DatahogConf[confid], src);

        //Modify the state per new configuration
        MN_ENTER_CRITICAL();
            storeMemberInt(&DatahogState, skipsleft[confid], 0U); //ready to sample
            storeMemberInt(&DatahogState, numvars[confid], numvars); //precomputed # of vars in a tuple
            if(status != DatahogUnchanged)
            {
                storeMemberInt(&DatahogState, status[confid], status); //repair the status as requested
            }
            if(confid == HogConfPerm)
            {
                //Change in configuration causes restart of presampling
                storeMemberInt(&DatahogState, num_presamples, 0U);
                storeMemberInt(&DatahogState, presamples_left, 0U);
            }
        MN_EXIT_CRITICAL();

    }
    return err;
}

/** \brief Set function (Set temporary)
*/
ErrorCode_t datahog_Set(const DatahogConf_t *src)
{
    DatahogStatus_t s = DatahogUnchanged;
    if(DatahogState.DatahogConfId == HogConfTemporary)
    {
        //Changing current configuration
        s = DatahogStop;
    }
    return datahog_SetX(src, HogConfTemporary, s);
}

/** \brief Set function (persistent/permanent)

The act of writing restarts presampling
*/
ErrorCode_t datahog_SetPerm(const DatahogConf_t *src)
{
    DatahogStatus_t s = DatahogUnchanged;
    if(!oswrap_IsOSRunning())
    {
        //Initialization
        STRUCT_CLOSE(DatahogConf_t, &DatahogState); //All zeros are fine: review! datahog_SetX will fix it
        s = DatahogIdle;
    }
    else
    {
        if(DatahogState.DatahogConfId == HogConfPerm)
        {
            //Changing current configuration
            s = DatahogStop;
        }
    }
    ErrorCode_t err = datahog_SetX(src, HogConfPerm, s); //NULL for default is OK
    if(err == ERR_OK)
    {
        if(!oswrap_IsOSRunning())
        {
            //Init temporary configuration to something sensible
            DatahogConf_t c = DatahogConf[HogConfPerm];
            c.num_presamples = 0U;
            err = datahog_Set(&c);
            MN_DBG_ASSERT(err == ERR_OK); //can't fail if perm. is OK and num_presamples cleared
        }
        err = ram2nvramAtomic(NVRAMID_DatahogConf);

        //Now, retrigger presampling
        buffer_InitializeXDiagnosticBuffer(DIAGBUF_AUX);

    }
    return err;
}

#define SafeStoreInt(structptr, member, value) \
    MN_ENTER_CRITICAL(); \
    storeMemberInt((structptr), member, (value)); \
    MN_EXIT_CRITICAL()


/** \brief A wrapper for automatically triggered data collection
\param op - command to data collection
\param confid - permanent or temporary
\return an error code
*/
ErrorCode_t datahog_ControlAuto(DatahogStatus_t op, DatahogConfId_t confid)
{
    ErrorCode_t err;
    u8 tbmode = digsp_GetExternalMode();
    if((tbmode != IPC_MODE_AUTO) && (op != DatahogStop))
    {
        err = ERR_CNFG_PROTECTED_LIMITS; //map to HART_ACCESS_RESTRICTED
    }
    else
    {
        err = datahog_Control(op, confid);
    }
    return err;
}

ErrorCode_t datahog_Control(DatahogStatus_t op, DatahogConfId_t confid)
{
    ErrorCode_t err = ERR_OK;
    MN_ENTER_CRITICAL();
        DatahogStatus_t status = DatahogState.status[confid];
        if(
           ((status != DatahogCollecting) /*&& (status != DatahogCompleted)*/ && (status != DatahogStart))
           || (op == DatahogStop)
               )
        {
            if(confid < HogConfsCount)
            {
                bool_t allowed = true;
                if(op == DatahogStart)
                {
                    allowed = (process_GetResourceFlags() & PROCINIT_CLAIMDIAGBUFFER) == 0U; //don't step on a running process
                }
                if(op == DatahogStop)
                {
                    //We stop only the running data collection, so we must fix the confid and ignore what's requested
                    confid = DatahogState.DatahogConfId;
                    allowed = (DatahogState.status[confid] == DatahogCollecting); //Stop only if running
                }
                if(allowed)
                {
                    if(op == DatahogForceStart)
                    {
                        op = DatahogStart;
                    }
                    if(op == DatahogStart)
                    {
                        ProcId_t id = process_GetProcId(); //On whose behalf to collect data
                        storeMemberInt(&DatahogState, procId, id);

                        DatahogConfId_t other = HogConfPerm;
                        if(DatahogState.DatahogConfId == HogConfPerm)
                        {
                            other = HogConfTemporary;
                        }
                        storeMemberInt(&DatahogState, status[other], DatahogIdle);
                        datahog_InitDeviationFilters();
                    }
                    storeMemberInt(&DatahogState, status[confid], op);
                    storeMemberInt(&DatahogState, DatahogConfId, confid);
                }
            }
            else
            {
                err = ERR_INVALID_PARAMETER;
            }
        }
        else
        {
            err = ERR_DP_DEVICE_BUSY; //shameless hijack of error code
        }
    MN_EXIT_CRITICAL();
    return err;
}


#define DIAG_DATAHOG_VERSION 0

#define BUFFERPLACE_HEADERSIZE 2
#define BUFFERPLACE_NUMSAMPLES 3
#define BUFFERPLACE_NUMPRESAMPLES 6
#define BUFFERPLACE_PROCESSID 7

/**
\return pointer beyond header
*/
static diag_t *FillDiagHeader(const DatahogConf_t *conf, const DatahogState_t *state)
{
    u32 interval = (conf->skip_count+1) * CTRL_TASK_DIVIDER; //Sampling interval in 5 ms ticks
    if(conf->taskid == TASKID_CYCLE)
    {
         interval *= CYCLE_TASK_DIVIDER;
    }
    //Populate the buffer header
    const diag_t ExtDiag_Header[] =
    {
        [0] = DIAG_DATAHOG, //test type
        [1] = DIAG_DATAHOG_VERSION, //version
        [BUFFERPLACE_HEADERSIZE] = EXTDIAG_HEADERSZ, //header size in diag_t entries
        [BUFFERPLACE_NUMSAMPLES] = 0, // #of samples collected
        [4] = (diag_t)conf->datamask,
        [5] = (diag_t)MIN(INT16_MAX, interval), //Sampling interval in 5 ms ticks
        [BUFFERPLACE_NUMPRESAMPLES] = (diag_t)state->num_presamples,
        [BUFFERPLACE_PROCESSID] = (diag_t)state->procId,
    };

    buffer_InitializeXDiagnosticBuffer(DIAGBUF_DEFAULT);

    DIAGRW_WriteBufferHEADER(ExtDiag_Header);
    u16 buf_init_entries = EXTDIAG_HEADERSZ;
    buffer_SelectRange(DIAGBUF_DEFAULT, NULL, &buf_init_entries); //OK, had to to initialize
    return buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT) + EXTDIAG_HEADERSZ;
}

static bool_t linear_sample(diag_t val)
{
    return buffer_AddXDiagnosticData1(DIAGBUF_DEFAULT, val);
}
static bool_t circular_sample(diag_t val)
{
    buffer_AddXDiagnosticDataCircular(DIAGBUF_AUX, val);
    return false;
}

typedef enum hogresult_t
{
    hog_ok,
    hog_skipped,
    hog_overflow
} hogresult_t;

/** \brief Collect a sample tuple into a diagnostic buffer.
\param sample_func - a pointer to a sampling function which determines the buffer itself
\return the result of sampling
*/
static hogresult_t datahog_Sample(DatahogConfId_t confid, bool_t (*sample_func)(diag_t val))
{
    hogresult_t hogresult = hog_skipped; //indicator of buffer overflow
    u16 skipsleft = DatahogState.skipsleft[confid];
    if(skipsleft != 0U)
    {
        --skipsleft;
        SafeStoreInt(&DatahogState, skipsleft[confid], skipsleft);
    }
    else
    {
        //Restart counting
        SafeStoreInt(&DatahogState, skipsleft[confid], DatahogConf[confid].skip_count);
        hogresult = hog_ok;
        u16_least mask = 1U;
        //And collect data
        for(size_t i=0; i<MIN(NELEM(DatahogTable), sizeof(DatahogConf[0].datamask)*CHAR_BIT); i++)
        {
            if((mask & DatahogConf[confid].datamask) != 0U)
            {
                //Collection requested
                s16 val = DatahogTable[i]();
                bool_t bovfl = sample_func(val);
                if(bovfl) //buffer full?
                {
                    hogresult = hog_overflow;
                    break;
                }
            }
            mask <<= 1;
        }
    }
    return hogresult;
}

/** \brief Check if we can (continue to) collect data in the buffer.

The condition is that the process is the same that started the collection
or doesn't need the diagnostic buffer.
\return true iff collection is compatible with the running process
*/
static bool_t datahog_TestProcess(void)
{
    //MISRA-style || :)
    bool_t ret = (process_GetProcId() == DatahogState.procId);
    if(!ret)
    {
        ret = ((process_GetResourceFlags() & PROCINIT_CLAIMDIAGBUFFER) == 0);
    }
    return ret;
}

static diag_t samples_collected;

static void collect(void)
{
    diag_t *pbuf = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);
    bool_t done_with_presamples = (DatahogState.presamples_left == 0U) || (DatahogState.DatahogConfId != HogConfPerm);
    if(!done_with_presamples)
    {
        //Do the copying one sample tuple at a time
        (void)buffer_GetDataFromXDiagnosticBuffer(DIAGBUF_AUX, 1*DatahogState.numvars[HogConfPerm],
                                                  &pbuf[samples_collected*DatahogState.numvars[HogConfPerm] + EXTDIAG_HEADERSZ]);

        u16 presamples_left = DatahogState.presamples_left - 1U;
        SafeStoreInt(&DatahogState, presamples_left, presamples_left);

        //Populate the DIAGBUF_DEFAULT buffer's counters (which will enable reading it)
        pbuf[BUFFERPLACE_NUMPRESAMPLES]++;
        pbuf[BUFFERPLACE_NUMSAMPLES]++; //that many are ready to read already
    }

    hogresult_t hogresult = datahog_Sample(DatahogState.DatahogConfId, linear_sample);

    if(hogresult == hog_ok)
    {
        samples_collected++;
        //Increment counter in the header
        if(pbuf[BUFFERPLACE_NUMPRESAMPLES] == DatahogState.num_presamples)
        {
            //Copying presamples complete
            pbuf[BUFFERPLACE_NUMSAMPLES] = samples_collected;
        }
    }
    if(done_with_presamples &&
       ((hogresult == hog_overflow) ||
        ((DatahogConf[DatahogState.DatahogConfId].maxsamples != 0)
                 && (pbuf[BUFFERPLACE_NUMSAMPLES] >= DatahogConf[DatahogState.DatahogConfId].maxsamples)))
           )
    {
        SafeStoreInt(&DatahogState, status[DatahogState.DatahogConfId], (u8)DatahogCompleted);
    }
}


/** \brief Simple high-speed collector of various data per bitmask

If used at all:
    MUST be called from cycle task
    MAY be called from control task
*/
void datahog_Collect(void)
{
    //Data integrity
    if(oswrap_IsContext(TASKID_CYCLE))
    {
        Struct_Test(DatahogState_t, &DatahogState);
    }
    //Presample
    if(oswrap_IsContext(DatahogConf[HogConfPerm].taskid))
    {
        /* A possible optimization is to skip presampling if
        the permanent-config collection is already running
        */
        hogresult_t hr = datahog_Sample(HogConfPerm, circular_sample);
        if(hr == hog_ok)
        {
            if(DatahogState.status[HogConfPerm] != DatahogCollecting)
            {
                //count the number of presamples collected
                MN_ENTER_CRITICAL();
                    u16 num_presamples = DatahogState.num_presamples;
                    if(num_presamples < DatahogConf[HogConfPerm].num_presamples)
                    {
                        num_presamples++;
                        storeMemberInt(&DatahogState, num_presamples, num_presamples);
                        storeMemberInt(&DatahogState, presamples_left, num_presamples);
                    }
                MN_EXIT_CRITICAL();
            }
        }
    }

    //Now, the active collection
    DatahogConfId_t confid = DatahogState.DatahogConfId;
    if(!oswrap_IsContext(DatahogConf[confid].taskid))
    {
        return; //Not the right context
    }

    bool_t runok = datahog_TestProcess();
    if(!runok)
    {
        //Cancel all data collection
        for(confid=0; confid<HogConfsCount; confid++)
        {
            DatahogStatus_t status = DatahogState.status[confid];
            if(status != DatahogIdle)
            {
                if(status == DatahogCollecting)
                {
                    status = DatahogInterrupted;
                }
                else
                {
                    status = DatahogIdle;
                }
                SafeStoreInt(&DatahogState, status[confid], (u8)status);
            }
        }
        return;
    }

    switch(DatahogState.status[confid])
    {
        case DatahogStart:
        {
            //We create the header and presamples here
            DatahogStatus_t s = DatahogCollecting;

            //NOTE: DatahogState.DatahogConfId is set by datahog_Control()
            const DatahogConf_t *pconf = &DatahogConf[confid];

            //u16_least num_presamples = 0U;
            /*Pull data from the presample buffer piecemeal - we can't afford copying
            the whole presample buffer.

            We need to pull at least numvars (see below) at a time,
            or we'll have DIAGBUF_AUX buffer overrun
            */
            if(confid == HogConfPerm)
            {
                MN_ENTER_CRITICAL();
                    u16 presamples_debt = (u16)(DatahogState.num_presamples * DatahogState.numvars[HogConfPerm]); //Number of diag_t items to retrieve
                    presamples_debt = buffer_KeepAtMost(DIAGBUF_AUX, presamples_debt);
                    size_t prefilled = presamples_debt + EXTDIAG_HEADERSZ;
                    if(prefilled >= DIAGNOSTIC_BUFFER_SIZE/2U)
                    {
                        //presamples can't be more than half buffer)
                        presamples_debt = 0;
                        s = DatahogInterrupted;
                    }

                    bufindex_t startpos=0;
                    bufindex_t endpos=presamples_debt + EXTDIAG_HEADERSZ;
                    buffer_SelectRange(DIAGBUF_DEFAULT, &startpos, &endpos); //reserve space for copying presamples
                    //num_presamples = presamples_debt/DatahogState.numvars[HogConfPerm];
                MN_EXIT_CRITICAL();
            }
            //SafeStoreInt(&DatahogState, num_presamples, num_presamples); //redundant?

            ErrorCode_t err = datahog_SetX(pconf, confid, DatahogCollecting);
            if(err != ERR_OK)
            {
                //Don't know how to collect
                s = DatahogIdle;
            }
            SafeStoreInt(&DatahogState, status[confid], (u8)s); //Done with status

            //Now, we are all set to write the buffer header
            (void)FillDiagHeader(pconf, &DatahogState);

            samples_collected = 0;
            if(s == DatahogCollecting)
            {
                collect();
            }
            break;
        }
        case DatahogCollecting:
        {
            collect();
            break;
        }
        case DatahogCompleted:
        case DatahogStop:
        case DatahogIdle:
        default:
        {
            break; //nothing to do
        }
    }
}

/* This line marks the end of the source */
