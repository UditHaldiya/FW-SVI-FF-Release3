/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_facotry_defaults.c
    \brief implement the parameter failed_state read

    CPU: Any

    OWNER: Victoria
    $Date: 04/27/13 14:19p $
*/

//Softing headers first
#include <softing_base.h>
#include <ptb.h>
#include <RTOS.h>

#include "hw_if.h"
#include "hartdef.h"
#include "mnhart2ff.h"
#include "bufutils.h"
#include "mn_factory_defaults.h"
#include "mn_fstate.h"
#include "nvffext.h"
#include "fbif_dcl.h"
#include "mn_advanced.h"
#include "appl_ptb.h"

#include "logfile.h"
#include "logfproc.h"
#include "logfileids.h"

#include "facdefaults.h"
#include "hmsndrcv5.h"

#include "ff2nvram.h"
#include "nvmempriv.h"
#include "mnassert.h"
#include "syncpatches.h"
#include "appl_alert.h"

#define SAVE_AP_DELAY_TIME_MS    100u //more or less arbitrary

/** \brief Wait for completion of a process in APP
\param snd_buf - working send buffer scratchpad
\param rcv_buf - working receive buffer scratchpad
\return error code (in comm. to APP)
*/
static fferr_t osif_WaitAppProcess(void)
{
    taskid_t taskid = osif_get_current_task_id();
    fferr_t fferr;
    do
    {
        //Wait until the APP process completes
        osif_TickleWatchdog(taskid);
        OS_Delay(SAVE_AP_DELAY_TIME_MS);
        fferr = mn_HART_acyc_cmd(251, snd_buf, 0, rcv_buf);
        Rsp_CheckProcess_t *rsp = (void *)((u8 *)rcv_buf + 2);
        u8 procid = util_GetU8(rsp->ProcessId[0]);
        if(procid == 0)
        {
            //Completed!
            break;
        }
    } while(fferr == E_OK);
    return fferr;
}

/** \brief Wait for completion of a process in FFP
*/
static void osif_WaitFfpProcess(void)
{
    taskid_t taskid = osif_get_current_task_id();
    do
    {
        syswd_TickleWatchdog(taskid);
        OS_Delay(SAVE_AP_DELAY_TIME_MS);
    } while(process_GetProcId() != PROC_NONE);
}



/** \brief reset the APP by hart command 42
   \return FF error
*/
fferr_t ffres_restart_APP(void)
{
    Req_Reset_t *req = (void *)snd_buf;
    Rsp_Reset_t *rsp = (void *)rcv_buf;
    return hmsndrcv5_Reset(req, rsp);
}

/** \brief Reinitializes NVMEM of which there is no finer control.
Relies on that corrupting StartupVersionNumber will do the right thing
*/
fferr_t ffres_ReinitNvmem(void)
{
    fferr_t fferr = E_FB_TEMP_ERROR;
    ErrorCode_t err = nvram_SetSignature(0U, 0U); //Corrupt signature on vol. 0
    if(err == ERR_OK)
    {
        fferr = ffres_restart_APP();
    }
    if(fferr == E_OK)
    {
        Reset_CPU();
    }
    return fferr;
}


/** \brief When the restart parameter choose the "HIDDEN", we need to
    save the TB block parameters to eep blk3. Then we need to send a
    hart command to save the current APP parameter also.
   \param snd_buf - send buffer
   \param      rcv_buf:  receive buffer
   \return        FF error
*/
fferr_t ffres_restart_hidden(void)
{
    T_EEP_RESULT  eep_result=EEP_OK;

    Req_SetFailedState_t* req = (void *)snd_buf;
    Rsp_SetFailedState_t* rsp = (void *)rcv_buf;
    // set the APP mode to Failed sstate
    fferr_t fferr = hmsndrcv5_SetFailedState(req, rsp);

    if (fferr == E_OK)
    {
        //send hart command 190,130 to save current APP parameters.
        Req_SaveNvmemAsFactoryDefault_t *req1 = (void *)snd_buf;
        Rsp_SaveNvmemAsFactoryDefault_t *rsp1 = (void *)rcv_buf;
        fferr = hmsndrcv5_SaveNvmemAsFactoryDefault(req1, rsp1);
    }
    if (fferr == E_OK)
    {
        //Save the image in log files
        process_ForceProcessCommand(PROC_FILE_NVMEM);

        //For the time being, ignore any errors - until we use synchronous interface in the process routine
        UNUSED_OK(eep_result);
#if 0
        if (eep_result != EEP_OK)
        {
            fferr = E_FB_EEP_NO_WRITE;
        }
#endif
        //Wait for local process completion
        osif_WaitFfpProcess();
    }

    if(fferr == E_OK)
    {
        //Wait until the APP process completes
        fferr = osif_WaitAppProcess();
    }

    //Clear failsafe (unconditionally)
    Req_ClearFailedState_t *req2 = (void *)snd_buf;
    Rsp_ClearFailedState_t *rsp2 = (void *)rcv_buf;
    fferr_t fferr1 = hmsndrcv5_ClearFailedState(req2, rsp2);

    //but report an error, if any
    if(fferr == E_OK)
    {
        fferr = fferr1;
    }

    return fferr;
}

/** \brief When the restart parameter choose the "RESTART_FACTORY_DEFAULTS",
    we need to restore the TB block parameters from eep blk3. Then we need
    to send a hart command to restore the APP parameter using the saving datas.
   \param in:
        snd_buf:  send buffer
        rcv_buf:  receive buffer
   \return:
        FF error
*/
fferr_t ffres_restart_factory_defaults(void)
{
    fferr_t fferr;
    fferr_t fferr_app;

    T_FBIF_BLOCK_INSTANCE * p_block_instance = fbs_get_block_inst(ID_PTB_1);
    T_FBIF_PTB *    p_PTB = p_block_instance->p_block_desc->p_block;

    Req_WriteSettings_t* req = (void *)&snd_buf[0];

    //check if the mode is OOS both in TB.target and TB.actual.
    if (p_PTB->mode_blk.target != MODE_OS || p_PTB->mode_blk.actual != MODE_OS)
    {
        return E_FB_WRONG_MODE;
    }

    if(!logf_Exist(NVMBACKUP_LOGFILE_ID))
    {
        return E_FB_PARA_LIMIT; //We didn't save the defaults
    }

    u16 st_rev = p_PTB->st_rev; //save it for repiring afterwards

    //Restore all volumes, designated entries only
    ErrorCode_t err = nvmem_LaunchFactoryRestore(0xFFU, NVMFLAG_RESTORED, NVMFLAG_RESTORED, 0);

    if(err == ERR_OK)
    {
        fferr = E_OK;
        //While we are restoring FFP data, start restoring APP data
        //send hart command 155 to set the APP mode to Failsafe.
        util_PutU8(req->SubCmdNum[0], 6);
        fferr_app = mn_HART_acyc_cmd(155, snd_buf, HC155_REQ_LENGTH +
                MN_OFFSETOF(Req_SetFailedState_t, endmark), rcv_buf);

        if (fferr_app == E_OK) //We are on a roll!
        {
            //send a hart command to resotre current APP parameters.hart cmd 190,129
            Req_RestoreFactoryDefaultNvmem_t* req_129 = (void*)((u8*)snd_buf + HC190_REQ_LENGTH);
            util_PutU8(req->SubCmdNum[0], 129);
            util_PutU8(req_129->NvmemDefaultsMaskFlags[0], NVMFLAG_RESTORED);
            util_PutU8(req_129->NvmemDefaultsMatchFlags[0], NVMFLAG_RESTORED);
            util_PutU8(req_129->NvmemDefaultsTestOnly[0], 0);
            util_PutU8(req_129->NvmemVolumeId[0], 0xFFU); //All volumes

            fferr_app = mn_HART_acyc_cmd(190, snd_buf, HC190_REQ_LENGTH +
                MN_OFFSETOF(Req_RestoreFactoryDefaultNvmem_t, endmark), rcv_buf);
        }

        //save the tb block static/nv data to NV
        if (fferr_app == E_OK)
        {
            fferr_app = osif_WaitAppProcess();
        }

        //In a change from R2 (and R1), we leave APP in failsafe intentionally,
        //But we do clear the faults
        //We won't change the mode though. Just clear faults.
        util_PutU8(snd_buf, 1); //Include history since we are starting fresh
        (void)mn_HART_acyc_cmd(138, snd_buf, HC138_REQ_LENGTH, rcv_buf);

        osif_WaitFfpProcess(); //wait for the "restore" process to complete

        //Indicate the level of success in the new st_rev

        (void)fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?

        if(fferr_app == E_OK)
        {
            (void)fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?
            (void)fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?
        }

        p_PTB->st_rev = st_rev;
        nvramId_t nvid = eepmap[EEP_FBL_BLK1+ID_PTB_1].nvid;
        (void)ram2nvramAtomic(nvid); //no means of handling error here

    }
    else
    {
        fferr = E_FB_WRONG_MODE; //Could not start restore process!
        fferr_app = E_FB_WRONG_MODE; //Did not not start restore process!
    }

    /* re-check of the alert related parameters used to be here.
    Now, alerts wrapper monitors "Advanced" on the go
    */

    // Reset APP and FFP together.
    if((fferr_app == E_OK) || (fferr == E_OK))
    {
        (void)ffres_restart_APP(); //no means to handle
        /* EXPLANATION: We are going to reset FFP if fferr == E_OK, as below.
        So if we don't reset APP as well, it will time out waiting for setpoint.
        Thus, oh well, we'll reset it too, even if it failed to restore factory
        settings.
        */

        if (fferr == E_OK)
        {
            Reset_CPU();
        }
    }

    return fferr;
}

// ----------- here is the addition of restoring to FW defaults ----------

/** \brief Check and start restoring FW defaults
\return FF error
*/
fferr_t nvmem_FFP_PreRestoreFirmwareDefaults(void)
{
    fferr_t fferr = E_FB_TEMP_ERROR;
    //0. Check if we have a process running
    if(process_CheckProcess())
    {
        //done
    }
    else
    {
        //1. Run APP restore
        Req_RestoreFirmwareDefaultNvmem_t *req = (void *)snd_buf;
        //These are unused but must be filled
        util_PutU8(req->NvmemDefaultsMaskFlags[0], 0);
        util_PutU8(req->NvmemDefaultsMatchFlags[0], 0);
        util_PutU8(req->NvmemDefaultsTestOnly[0], 0);
        util_PutU8(req->NvmemVolumeId[0], 0);
        Rsp_RestoreFirmwareDefaultNvmem_t *rsp = (void *)rcv_buf;
        fferr = hmsndrcv5_RestoreFirmwareDefaultNvmem(req,  rsp);
    }
    if(fferr != E_OK)
    {
        fferr = E_FB_TEMP_ERROR;
    }
    return fferr;
}

/** \brief  restoring FW defaults
\return a process completion code
*/
void nvmem_FFP_RestoreFirmwareDefaults(void)
{
    //Remaining Steps:
    //2. Restore TB parameters damaged by Softing restore
    u8 *dst = ((u8 *)&ptb_1);
    const void *p; //for sanity check
    size_t relid;
    nvramId_fast_t id;
    for(relid=1; relid<ff2nvram_map_size; relid++)
    {
        id = ff2nvram_map[relid].nvramid;
        if(id != 0)
        {
            //We took it over from Softing, so we need to repair the image
            if((nvram_map[id].flags & NVMFLAG_RESTORED) == 0U)
            { //Can't accept restore if not restorable
                p = nvmem_GetItemById(dst + ptb_param_dir[relid].par_offset, id); //lint !e960 pointer arith (17.1)
                MN_DBG_ASSERT(p != NULL);
            }
        }
    }
    //2.1 Special case: ADVANCED is not handled in a standard way, and code refactoring is postponed
    p = nvmem_GetItemById(dst + ptb_param_dir[REL_IDX_PTB_ADVANCED].par_offset, NVRAMID_AdvancedParam); //lint !e960 pointer arith (17.1)
    MN_DBG_ASSERT(p != NULL);
    UNUSED_OK(p); //for release build
    //2.2 Special case: Travel Alerts;
    alert_RestartTravelAlert();
    //2.3 Special case: Cycle Alerts;
    alert_RestartCyclelAlert();

    //3. Restore the restorable TB params
    process_ForceProcessCommand(PROC_RESTORE_FW_NVMEM);

    //4. Contrary to Softing advice, we'll wait here for local process to complete before responding
    /* That's because there are unexplained comm. errors
    */
    do
    {
        OS_Delay(50);
    } while(process_CheckProcess());
}

procresult_t proc_FFP_RestoreFirmwareDefaults(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_FAILED;

    ErrorCode_t err = ERR_OK;
    for(nvramId_fast_t id=1; id<NVRAM_ENTRIES; id++)
    {
        if((nvram_map[id].flags & NVMFLAG_RESTORED) != 0U)
        {
            ErrorCode_t err1 = nvmem_SetItemById(NULL, id);
            if(err1 == ERR_OK)
            {
                err1 = ram2nvramAtomic(id);
            }
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

/*This is the last line of this file*/

