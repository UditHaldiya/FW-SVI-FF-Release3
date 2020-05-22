/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ctrl_param_set.c
    \brief functions about parameter ACTIVATE_CONTROL_SET, ACTIVATE_CONTROL_SET, CUSTOM_CONTROL_SET and BACKUP_CONTROL_SET

    CPU: Any

    OWNER: EJ

*/
#include <softing_base.h>
#include <ptb.h>
//end incantaion

//MN FIRMWARE headers second
#include "hartdef.h"
#include "bufutils.h"
#include "crc.h"

//Glue headers last
#include "mnhart2ff.h"
#include "selftune.h"
#include "ctrl_param_set.h"
#include "hmsndrcv5.h"

#define MODULE_ID   (COMP_FAPP + MOD_APPL_TRN)

#define NONLIN_HIGH_LIMIT       ((s16)BOOST_HIGH_LIMIT)
#define NONLIN_LOW_LIMIT        (0) //because defined as signed in PTB params
//-----------------------------------------------------------------------------------------

/* \brief execution codes for Write_handler_PTB(), when change on REL_IDX_PTB_CUSTOM_CONTROL_SET
    param in:
        p_block_instance:   pointer to the FF block
        p_write:            ponter to the write parameters
        snd_buf:            pointer to memory, which is for send of HART
        rcv_buf:            pointer to memory, which is for receive of hart
    param out:

    return:
        OK if succeeds
        ERROR if fails
*/
static fferr_t ctrl_param_WriteCustomCtrlSet(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    fferr_t                         fferr;
    Req_WriteControlParameters_t    *req = snd_buf;
    ControlParams_t                 *pCtrlParams = (void*)req->ControlParams[0];
    T_FBIF_PTB                      *p_PTB = p_block_instance->p_block_desc->p_block;

    util_PutU8(req->PIDDataSelector[0], 0);
    util_PutS16(pCtrlParams->PIDDataP[0], p_PTB->custom_control_set.component_0);
    util_PutS16(pCtrlParams->PIDDataI[0], p_PTB->custom_control_set.component_1);
    util_PutS16(pCtrlParams->PIDDataD[0], p_PTB->custom_control_set.component_2);
    util_PutS16(pCtrlParams->PIDDataPADJ[0], p_PTB->custom_control_set.component_3);
    util_PutS16(pCtrlParams->PIDDataBETA[0], p_PTB->custom_control_set.component_4);
    util_PutS16(pCtrlParams->PIDDataPOS_COMP[0], p_PTB->custom_control_set.component_5);
    util_PutS16(pCtrlParams->PIDDataDEADZONE[0], p_PTB->custom_control_set.component_6);
    util_PutS16(pCtrlParams->PIDDataNONLIN1[0], p_PTB->custom_control_set.component_7);

    fferr = mn_HART_acyc_cmd(173, snd_buf, HC173_REQ_LENGTH, rcv_buf);

    return fferr;
}

static fferr_t ctrl_param_WriteSelector(u8 selector, void* snd_buf, void* rcv_buf)
{
    Req_WriteSettings_t* req = snd_buf;
    Req_WriteControlParametersSelector_t* req_216 = (void*)((u8*)snd_buf + HC171_REQ_LENGTH);
    util_PutU8(req->SubCmdNum[0], 216);
    util_PutU8(req_216->PIDDataSelector[0], selector);
    fferr_t fferr = mn_HART_acyc_cmd(171, snd_buf, HC171_REQ_LENGTH + MN_OFFSETOF(Req_WriteControlParametersSelector_t, endmark), rcv_buf);
    return fferr;
}

/* async hart command 171, 216 to write slector for control param set */
static fferr_t ctrl_param_WriteActivateCtrlSet(const _BACKUP_CONTROL_SET *ctlset, void* snd_buf, void* rcv_buf)
{
    fferr_t fferr = E_OK;
    
    u8 selector = (u8)ctlset->selector;

    //If selector is 0 (custom), write the whole thing, otherwise, only the selector
    if(selector == 0)
    {
        Req_WriteControlParameters_t    *req = snd_buf;
        Rsp_WriteControlParameters_t    *rsp = snd_buf;
        ControlParams_t                 *pCtrlParams = (void*)req->ControlParams[0];
        util_PutU8(req->PIDDataSelector[0], 0);
        util_PutS16(pCtrlParams->PIDDataP[0], ctlset->p);
        util_PutS16(pCtrlParams->PIDDataI[0], ctlset->i);
        util_PutS16(pCtrlParams->PIDDataD[0], ctlset->d);
        util_PutS16(pCtrlParams->PIDDataPADJ[0], ctlset->padj);
        util_PutS16(pCtrlParams->PIDDataBETA[0], ctlset->beta);
        util_PutS16(pCtrlParams->PIDDataPOS_COMP[0], ctlset->poscomp);
        util_PutS16(pCtrlParams->PIDDataDEADZONE[0], ctlset->deadzone);
        util_PutS16(pCtrlParams->PIDDataNONLIN1[0], ctlset->nonlin);
        fferr = hmsndrcv5_WriteControlParameters(req, rsp);
    }
    
    if(fferr == E_OK)
    {
        fferr = ctrl_param_WriteSelector(selector, snd_buf, rcv_buf);
    }
    return fferr;
}

/* \brief Since backup control set is changed by itself, not by user
            so the storage is not handled by Write_handler_PTB()
            and we need to do it manually
    param in:
        p_PTB: pointer to the objects of transducer block
    return:
        void
*/
static USIGN16 ctrl_param__WriteBackup(T_FBIF_BLOCK_INSTANCE * p_block_instance)
{
    T_FBS_WRITE_PARAM_LOCAL write_loc;
    T_FBIF_PTB *  p_PTB = p_block_instance->p_block_desc->p_block;

    write_loc.rel_idx = REL_IDX_PTB_BACKUP_CONTROL_SET;
    // Store out parameter in non-volatile RAM ----------------------
    write_loc.subindex      = 0;
    write_loc.length        = sizeof(p_PTB->backup_control_set);
    write_loc.source        = (USIGN8 *)&p_PTB->backup_control_set;
    write_loc.startup_sync = FALSE;

    return mn_fbs_write_param_loc (p_block_instance, &write_loc);
}


/* \brief execution codes for Read_handler_PTB(), when retrive REL_IDX_PTB_ACTIVE_CONTROL_SET, REL_IDX_PTB_CUSTOM_CONTROL_SET
    param in:
        p_block_instance:   pointer to the FF block
        rel_idx:            the index value of the parameter to be read
        snd_buf:            pointer to memory, which is for send of HART
        rcv_buf:            pointer to memory, which is for receive of hart
    param out:

    return:
        OK if succeeds
        ERROR if fails
*/
fferr_t ctrl_param_ReadWorkingSet(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* from, void* to)
{

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    _ACTIVE_CONTROL_SET *pCtrlSet = &p_PTB->active_control_set;

    Req_ReadControlParametersSelector_t* req = from;
    Rsp_ReadControlParametersSelector_t* rsp = to;
    fferr_t fferr = hmsndrcv5_ReadControlParametersSelector(req, rsp);
    if(fferr == E_OK)
    {
        s16 selector = util_GetU8(rsp->PIDDataSelector[0]);
        Rsp_ReadCurrentControlParametersSet_t* rsp1 = to;
        const ControlParams_t *pCtlSet = (const void *)(rsp1->ControlParams[0]);
        fferr = hmsndrcv5_ReadCurrentControlParametersSet(from, rsp1);

        if(fferr == E_OK)
        {
            pCtrlSet->component_0 = selector;
            pCtrlSet->component_1 = util_GetS16(pCtlSet->PIDDataP[0]);
            pCtrlSet->component_2 = util_GetS16(pCtlSet->PIDDataI[0]);
            pCtrlSet->component_3 = util_GetS16(pCtlSet->PIDDataD[0]);
            pCtrlSet->component_4 = util_GetS16(pCtlSet->PIDDataPADJ[0]);
            pCtrlSet->component_5 = util_GetS16(pCtlSet->PIDDataBETA[0]);
            pCtrlSet->component_6 = util_GetS16(pCtlSet->PIDDataPOS_COMP[0]);
            pCtrlSet->component_7 = util_GetS16(pCtlSet->PIDDataDEADZONE[0]);
            pCtrlSet->component_8 = util_GetS16(pCtlSet->PIDDataNONLIN1[0]);
        }
    }

    return fferr;
}

/* \brief execution codes for Write_handler_PTB(), when change on REL_IDX_PTB_ACTIVATE_CONTROL_SET
    param in:
        p_block_instance:   pointer to the FF block
        p_write:            ponter to the write parameters
        snd_buf:            pointer to memory, which is for send of HART
        rcv_buf:            pointer to memory, which is for receive of hart
    param out:

    return:
        OK if succeeds
        ERROR if fails
*/
fferr_t ctrl_param_WriteActivate(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA *p_write, void* snd_buf, void* rcv_buf)
{
    fferr_t     fferr = E_OK;
    T_FBIF_PTB  *p_PTB = p_block_instance->p_block_desc->p_block;

    u8* p_selector = p_write->source;

    switch(*p_selector)
    {
        case ACTIVATE_CUSTOM_CONTROL_SET:
        case ACTIVATE_CONTROL_SET_1:
        case ACTIVATE_CONTROL_SET_2:
        case ACTIVATE_CONTROL_SET_3:
        case ACTIVATE_CONTROL_SET_4:
        case ACTIVATE_CONTROL_SET_5:
        case ACTIVATE_CONTROL_SET_6:
        case ACTIVATE_CONTROL_SET_7:
        {
            if(ACTIVATE_CUSTOM_CONTROL_SET == *p_selector)
            {
                fferr = ctrl_param_WriteCustomCtrlSet(p_block_instance, snd_buf, rcv_buf);
            }
            if(E_OK == fferr)
            {
                fferr = ctrl_param_WriteSelector(*p_selector, snd_buf, rcv_buf);
                if (E_OK == fferr)
                {
                    mn_memcpy((void*)&p_PTB->backup_control_set,
                    &(p_PTB->active_control_set),
                    sizeof(p_PTB->backup_control_set));
                    fferr = ctrl_param__WriteBackup(p_block_instance);
                }
            }
            break;
        }
        case RESTORE_CONTROL_SET:
        {
            fferr = ctrl_param_WriteActivateCtrlSet(&p_PTB->backup_control_set, snd_buf, rcv_buf);
            break;
        }
        case MAKE_ACTIVE_CONTROL_AS_CUSTOM_CONTROL:
        {
            //First, make sure we populated Active Control Set!
            fferr = ctrl_param_ReadWorkingSet(p_block_instance, snd_buf, rcv_buf);
            if(fferr == E_OK)
            {
                struct buckets_t
                {
                    INT16           selector;
                    _CONTROL_SET    controlset;
                } *p = (void*)&p_PTB->active_control_set;
                //Assert my assumptions:
                //1. (No) padding
                CONST_ASSERT(sizeof(*p) == sizeof(p_PTB->active_control_set));
                //2. Alignment
                CONST_ASSERT(sizeof(p->controlset) == sizeof(p_PTB->custom_control_set) );
                UNUSED_OK(p->selector);

                _CONTROL_SET* pData = (_CONTROL_SET*)&p->controlset;
                mn_memcpy(&(p_PTB->custom_control_set), (void*)pData, sizeof(_CONTROL_SET));
                //fferr = ctrl_param_WriteCustomCtrlSet(p_block_instance, snd_buf, rcv_buf);
            }
            break;
        }
        case DO_NOTHING:
        {
            break;
        }
        default:
        {
            fferr = E_ERROR;
            break;
        }
    }

    *p_selector = DO_NOTHING;
    return fferr;
}


/* \brief Routine called by Read_handler_PTB() to populate pPTB with Autotune parameters.
          Called when Read Handler is called with the index REL_IDX_PTB_AUTOTUNE.
    param in:
        p_block_instance:   pointer to the FF block
        snd_buf:            pointer to a buffer sent to HART
    param out:
        rcv_buf:            pointer to a buffer received from HART
    return:
        error code: OK if succeeds, ERROR if fails
*/
fferr_t ctrl_param_ReadAutotuneParam(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    fferr_t fferr;
    Req_ReadSettings_t* req = snd_buf;

    Rsp_ReadTuningParameters_t* rsp_189 = (void*)((u8*)rcv_buf + MN_OFFSETOF(Rsp_ReadSettings_t, endmark) + 2);
    AutotuneParams_t* pTuneParams = (void*)rsp_189->AutotuneParams[0];

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    _AUTOTUNE* pAutotuneParams = &p_PTB->autotune;

    util_PutU8(req->SubCmdNum[0], 189);
    fferr = mn_HART_acyc_cmd(170, snd_buf, MN_OFFSETOF(Req_ReadTuningParameters_t, endmark) + MN_OFFSETOF(Req_ReadSettings_t, endmark), rcv_buf);

    if(fferr == E_OK)
    {
        pAutotuneParams->component_0 = util_GetFloat(pTuneParams->DefaultSupplyPressure[0]);
        pAutotuneParams->component_1 = (s8)util_GetU8(pTuneParams->TuneAggressiveness[0]);
        pAutotuneParams->component_2 = util_GetU8(pTuneParams->TuneFlags[0]);
        pAutotuneParams->component_3 = util_GetU16(rsp_189->TuneCompletionCode[0]);
    }

    return fferr;
} // ----- end of ctrl_param_ReadAutotuneParam() -----

/** \brief Write Autotune params and start Autotune (combo)
*/
#define SUBCMDLENGTH    1u
fferr_t ctrl_param_Autotune(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    fferr_t fferr;
    u16     TuneCompletion;
    u8      buffLen;

    const T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    const _AUTOTUNE *pAutotuneParams = &p_PTB->autotune;
    AutotuneParams_t* pTuneParams189 = snd_buf;
    Req_WriteSettings_t* req = snd_buf; //pointer to the start of the buffer to put subcommand
    //pointer to the rest of the send buffer
    AutotuneParams_t* pTuneParams171 = (void*)((u8*)snd_buf + SUBCMDLENGTH);

    //AK: This is the original passage from Sergey. Not sure what it is for
    if ( p_PTB->mode_blk.target != MODE_MAN )
    {
        return E_FB_WRONG_MODE;
    }

    TuneCompletion = pAutotuneParams->component_3; //Completion sub-parameter of Autotune

    switch (TuneCompletion)
    {
        case AUTOTUNE_CANCEL:   //cancel process
            buffLen = 0u;
            fferr = mn_HART_acyc_cmd(253, snd_buf, buffLen, rcv_buf);
            break;

        case AUTOTUNE_START:    //start autotune
            util_PutFloat(pTuneParams189->DefaultSupplyPressure[0], pAutotuneParams->component_0);
            util_PutU8(pTuneParams189->TuneAggressiveness[0], (u8)pAutotuneParams->component_1);
            util_PutU8(pTuneParams189->TuneFlags[0], pAutotuneParams->component_2);
            fferr = mn_HART_acyc_cmd(189, snd_buf, sizeof(AutotuneParams_t), rcv_buf);
            break;

        default:  //write parameters only without starting autotune
            util_PutU8(req->SubCmdNum[0], 189); //write subcommand
            //write the rest of the buffer
            util_PutFloat(pTuneParams171->DefaultSupplyPressure[0], pAutotuneParams->component_0);
            util_PutU8(pTuneParams171->TuneAggressiveness[0], (u8)pAutotuneParams->component_1);
            util_PutU8(pTuneParams171->TuneFlags[0], pAutotuneParams->component_2);
            fferr = mn_HART_acyc_cmd(171, snd_buf, sizeof(AutotuneParams_t) + SUBCMDLENGTH, rcv_buf);
            break;
    }
    return fferr;
} // ----- end of ctrl_param_AutotuneParam() -----

/* \brief Routine called by Write_handler_PTB() when users write CUSTOM_CONTROL_SET
    param in:
        p_write:   pointer to the write block
    return:
        error code: OK if succeeds, ERROR if fails
*/
fferr_t ctrl_param_WriteCustom(const T_FBIF_WRITE_DATA *p_write)
{
    fferr_t fferr = E_OK;

    switch (p_write->subindex)
    {
        case 0:
        {
            _CONTROL_SET* p_controlset = (_CONTROL_SET*)(void*)p_write->source;
            if(
                ((u16)p_controlset->component_0 > P_HIGH_LIMIT) ||
                ((u16)p_controlset->component_1 > I_HIGH_LIMIT) ||
                ((u16)p_controlset->component_2 > D_HIGH_LIMIT) ||
                (p_controlset->component_3 < PADJ_LOW_LIMIT)  ||
                (p_controlset->component_3 > PADJ_HIGH_LIMIT) ||
                (p_controlset->component_4 < BETA_LOW_LIMIT)  ||
                (p_controlset->component_4 > BETA_HIGH_LIMIT) ||
                (p_controlset->component_5 < PCOMP_LOW_LIMIT)  ||
                (p_controlset->component_5 > PCOMP_HIGH_LIMIT) ||
                ((u16)p_controlset->component_6 > DEADZONE_HIGH_LIMIT) ||
                (p_controlset->component_7 > NONLIN_HIGH_LIMIT) ||
                (p_controlset->component_7 < NONLIN_LOW_LIMIT)
               )
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 1:
        {
            u16* p_P = (u16*)(void*)p_write->source;
            if(*p_P > P_HIGH_LIMIT)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 2:
        {
            u16* p_I = (u16*)(void*)p_write->source;
            if(*p_I > I_HIGH_LIMIT)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 3:
        {
            u16* p_D = (u16*)(void*)p_write->source;
            if(*p_D > D_HIGH_LIMIT)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 4:
        {
            s16* p_Padj = (s16*)(void*)p_write->source;
            if((*p_Padj < PADJ_LOW_LIMIT) || (*p_Padj > PADJ_HIGH_LIMIT))
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 5:
        {
            s16* p_beta = (s16*)(void*)p_write->source;
            if((*p_beta < BETA_LOW_LIMIT) || (*p_beta > BETA_HIGH_LIMIT))
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 6:
        {
            s16* p_posComp = (s16*)(void*)p_write->source;
            if((*p_posComp < PCOMP_LOW_LIMIT) || (*p_posComp > PCOMP_HIGH_LIMIT))
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 7:
        {
            u16* p_deadZone = (u16*)(void*)p_write->source;
            if(*p_deadZone > DEADZONE_HIGH_LIMIT)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 8:
        {
            s16* p_nonLin = (s16*)(void*)p_write->source;
            if((*p_nonLin > NONLIN_HIGH_LIMIT) || (*p_nonLin < NONLIN_LOW_LIMIT))
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        default:
        {
            fferr = E_FB_PARA_CHECK;
            break;
        }
    }

    return fferr;
}

/* This line marks the end of the source */
