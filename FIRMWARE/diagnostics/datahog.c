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

static ErrorCode_t datahog_SetX(const DatahogConf_t *src, DatahogConfId_t confid)
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
        u16_least num_presamples = DatahogConf[HogConfPerm].num_presamples * numvars;
        const DatahogState_t state =
        {
            .skipsleft = 0,
            .num_presamples = (u16)num_presamples,
            .presamples_left = (u16)num_presamples,
            .numvars = (u8)numvars, //max 16=CHAR_BIT*sizeof(datamask)
            .status = DatahogIdle,
            .procId = process_GetProcId(), //NOTE: relies on early init of process data
            .DatahogConfId = confid,
            .CheckWord = 0, //don't care
        };
        Struct_Copy(DatahogState_t, &DatahogState, &state);

        //Now, retrigger presampling
        if(confid == HogConfPerm)
        {
            buffer_InitializeXDiagnosticBuffer(DIAGBUF_AUX);
        }
    }
    return err;
}

/** \brief Set function (Set temporary)
*/
ErrorCode_t datahog_Set(const DatahogConf_t *src)
{
    return datahog_SetX(src, HogConfTemporary);
}

/** \brief Set function (persistent/permanent)

The act of writing retriggers presampling
*/
ErrorCode_t datahog_SetPerm(const DatahogConf_t *src)
{
    ErrorCode_t err = datahog_SetX(src, HogConfPerm); //NULL for default is OK
    if(err == ERR_OK)
    {
        if(!oswrap_IsOSRunning())
        {
            //Init temporary configuration to something sensible
            Struct_Copy(DatahogConf_t, &DatahogConf[HogConfTemporary], &DatahogConf[HogConfPerm]);
        }
        err = ram2nvramAtomic(NVRAMID_DatahogConf);
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
        DatahogStatus_t status = DatahogState.status;
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
                    if(allowed)
                    {
                        datahog_InitDeviationFilters();
                    }
                }
                if(allowed)
                {
                    if(op == DatahogForceStart)
                    {
                        op = DatahogStart;
                    }
                    storeMemberInt(&DatahogState, status, op);
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

static hogresult_t datahog_Sample(DatahogState_t *state, const DatahogConf_t *conf, bool_t (*sample_func)(diag_t val))
{
    hogresult_t hogresult = hog_skipped; //indicator of buffer overflow
    u16 skipsleft = state->skipsleft;
    if(skipsleft != 0U)
    {
        --skipsleft;
        SafeStoreInt(state, skipsleft, skipsleft);
    }
    else
    {
        //Restart counting
        SafeStoreInt(state, skipsleft, conf->skip_count);
        hogresult = hog_ok;
        u16_least mask = 1U;
        //And collect data
        for(size_t i=0; i<MIN(NELEM(DatahogTable), sizeof(conf->datamask)*CHAR_BIT); i++)
        {
            if((mask & conf->datamask) != 0U)
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
    bool_t done_with_presamples = (DatahogState.presamples_left == 0U);
    if(!done_with_presamples)
    {
        //Do the copying one sample at a time
        (void)buffer_GetDataFromXDiagnosticBuffer(DIAGBUF_AUX, 1*DatahogState.numvars, &pbuf[samples_collected*DatahogState.numvars + EXTDIAG_HEADERSZ]);

        u16 presamples_left = DatahogState.presamples_left - 1U;
        SafeStoreInt(&DatahogState, presamples_left, presamples_left);

        //Populate the DIAGBUF_DEFAULT buffer's counters (which will enable reading it)
        pbuf[BUFFERPLACE_NUMPRESAMPLES]++;
        pbuf[BUFFERPLACE_NUMSAMPLES]++; //that many are ready to read already
    }

    hogresult_t hogresult = datahog_Sample(&DatahogState, &DatahogConf[DatahogState.DatahogConfId], linear_sample);

    if(hogresult == hog_ok)
    {
        samples_collected++;
        //Increment counter in the header
        if(pbuf[BUFFERPLACE_NUMPRESAMPLES] == DatahogConf[DatahogState.DatahogConfId].num_presamples)
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
        SafeStoreInt(&DatahogState, status, (u8)DatahogCompleted);
    }
}


/** \brief Simple high-speed collector of various data per bitmask

If used at all:
    MUST be called from cycle task
    MAY be called from control task
*/
void datahog_Collect(void)
{
    if(oswrap_IsContext(TASKID_CYCLE))
    {
        Struct_Test(DatahogState_t, &DatahogState);
    }
    //Presample
    if(oswrap_IsContext(DatahogConf[HogConfPerm].taskid))
    {
        (void)datahog_Sample(&DatahogState, &DatahogConf[HogConfPerm], circular_sample);
    }
    if(!oswrap_IsContext(DatahogConf[DatahogState.DatahogConfId].taskid))
    {
        return; //Not the right context
    }

    bool_t runok = datahog_TestProcess();
    if(!runok)
    {
        if(DatahogState.status != DatahogIdle)
        {
            SafeStoreInt(&DatahogState, status, (u8)DatahogInterrupted);
        }
        return;
    }

    switch(DatahogState.status)
    {
        case DatahogStart:
        {
            //We create the header and presamples here
            DatahogStatus_t s = DatahogCollecting;

            (void)FillDiagHeader(&DatahogConf[DatahogState.DatahogConfId], &DatahogState);

            /*Pull data from the presample buffer piecemeal - we can't afford copying
            the whole presample buffer.

            We need to pull at least numvars (see below) at a time,
            or we'll have DIAGBUF_AUX buffer overrun
            */
            bufindex_t num_presamples = 0;
            if(DatahogState.DatahogConfId == HogConfPerm)
            {
                MN_ENTER_CRITICAL();
                    num_presamples = buffer_KeepAtMost(DIAGBUF_AUX, DatahogState.num_presamples);
                    size_t prefilled = num_presamples + EXTDIAG_HEADERSZ;
                    if(prefilled >= DIAGNOSTIC_BUFFER_SIZE/2U)
                    {
                        //presamples can't be more than half buffer)
                        num_presamples = 0;
                        s = DatahogInterrupted;
                    }
                    else
                    {
                        bufindex_t startpos=0;
                        bufindex_t endpos=num_presamples+EXTDIAG_HEADERSZ;
                        buffer_SelectRange(DIAGBUF_DEFAULT, &startpos, &endpos);
                    }
                MN_EXIT_CRITICAL();
            }

            SafeStoreInt(&DatahogState, num_presamples, num_presamples);
            SafeStoreInt(&DatahogState, presamples_left, num_presamples);
            SafeStoreInt(&DatahogState, status, (u8)s);
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
