/*
Copyright 2009-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_actuator_3.c
    \brief Implementation of API for parameter ACTUATOR_3

    NOTE: Air action is only maintained be Read/Write handlers; do not use in internal code!

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <ptb.h>
#include <osif.h>

//MN FIRMWARE headers second
#include "hartdef.h"
#include "bufutils.h"
#include "crc.h"

//Glue headers last
#include "mnhart2ff.h"
#include "mn_actuator_3.h"

#include "pressure_range.h"
#include "hmsndrcv5.h"
#include "ptbcustomsubx.h"


static const Act3Min_t Act3Min_default =
{
    .shutoff_dp = 0,
    .hand_wheel = 0,
    .relay_type = 1,
    .supply_prs_max = 35.0F,
    .prs_control_hi = 15.0F,
    .prs_control_lo = 2.988F, //!< All pressures in psi; values stolen from GW (where they are in KPa)
    .CheckWord = 0, //don't care
};

static Act3Min_t Act3Min;

ErrorCode_t act3min_Set(const Act3Min_t *src)
{
    if(src == NULL)
    {
        src = &Act3Min_default;
    }
    STRUCT_GET(src, &Act3Min);
    return ram2nvramAtomic(NVRAMID_Act3Min);
}

const Act3Min_t *act3min_Get(Act3Min_t *dst)
{
    return STRUCT_TESTGET(&Act3Min, dst);
}

/** \brief read actuator_3 parameter
    \param p_block_instance - pointer to function block
    \param snd_buf -  send buffer
    \param rcv_buf -  receive buffer
    return FF error
*/
fferr_t ReadActuator3(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    Req_ReadAirAction_t* req = snd_buf;
    Rsp_ReadAirAction_t* rsp = rcv_buf;
    Req_ReadPneumaticParameters_t* req_167 = snd_buf;
    Rsp_ReadPneumaticParameters_t* rsp_167 = rcv_buf;

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    fferr_t fferr = hmsndrcv5_ReadAirAction(req, rsp);

    if(fferr == E_OK)
    {
        u8 ap_air_action = util_GetU8(rsp->AirAction[0]);
        if (HAirToClose == ap_air_action)
        {
            //act fail action vlaue is 2
            p_PTB->actuator_3.act_fail_action = ACTUATOR_ATC;
        }
        else // (ATO == ap_air_action)
        {
            //act fail action vlaue is 1
            p_PTB->actuator_3.act_fail_action = ACTUATOR_ATO;
        }
        fferr = hmsndrcv5_ReadPneumaticParameters(req_167, rsp_167);
    }


    if(fferr == E_OK)
    {
        PneumaticParameters_t* p_pp = (PneumaticParameters_t*)rsp_167->PneumaticParameters[0];
        u8 single_flag = util_GetU8(p_pp->SingleActingFlag[0]);
        if(SAFSingleActing == single_flag)
        {
            p_PTB->actuator_3.style = SINGLE_ACTING;
        }
        else
        {
            p_PTB->actuator_3.style = DOUBLE_ACTING;
        }

        //Now, populate the remaining fields
        const Act3Min_t *p = act3min_Get(NULL); //Mostly to test
        p_PTB->actuator_3.shutoff_dp = p->shutoff_dp;
        p_PTB->actuator_3.hand_wheel = p->hand_wheel;
        p_PTB->actuator_3.relay_type = p->relay_type;
        u16 units = p_PTB->pressure_range.units;
        p_PTB->actuator_3.supply_prs_max = ffpres_Internal2Eng(p->supply_prs_max, units);
        p_PTB->actuator_3.prs_control_hi = ffpres_Internal2Eng(p->prs_control_hi, units);
        p_PTB->actuator_3.prs_control_lo = ffpres_Internal2Eng(p->prs_control_lo, units);
    }
    return fferr;
}

static fferr_t WriteAirAction(const T_FBIF_PTB *p_PTB, u8 ff_air_action, void* snd_buf, void* rcv_buf)
{
    fferr_t fferr = E_OK;
    Req_WriteAirAction_t* req = snd_buf;
    Rsp_WriteAirAction_t* rsp = rcv_buf;
    u8 ap_air_action = 0;
    if(MODE_OS != p_PTB->mode_blk.target)
    {
        fferr = E_FB_WRONG_MODE;
    }
    else
    {
        if (ACTUATOR_ATC == ff_air_action)
        {
            //act fail action vlaue should be 0
            ap_air_action = HAirToClose;
        }
        else if (ACTUATOR_ATO == ff_air_action)
        {
            //act fail action vlaue is 1
            ap_air_action = HAirToOpen;
        }
        else
        {
            fferr = E_FB_PARA_LIMIT;
        }
    }
    if(fferr == E_OK)
    {
        util_PutU8(req->AirAction[0], ap_air_action);
        fferr = hmsndrcv5_WriteAirAction(req, rsp);
    }
    return fferr;
}

/** \brief write actuator_3 parameter
    \param p_block_instance - pointer to function block
    \param p_write - a pointer to write stream
    \param snd_buf - send buffer
    \param rcv_buf - receive buffer
    \return FF error
*/
fferr_t WriteActuator3(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA *p_write, void* snd_buf, void* rcv_buf)
{
    fferr_t fferr = E_OK;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    Act3Min_t a3;
    (void)act3min_Get(&a3);
    switch(p_write->subindex)
    {
        case 0:
        {
            _ACTUATOR_3* p_actuator_3 = (_ACTUATOR_3*)(void*)p_write->source;
            a3.shutoff_dp = p_actuator_3->shutoff_dp;
            a3.hand_wheel = p_actuator_3->hand_wheel;
            a3.relay_type = p_actuator_3->relay_type;

            u16 units = p_PTB->pressure_range.units;
            a3.prs_control_hi = ffpres_Eng2Internal(p_actuator_3->prs_control_hi, units);
            a3.prs_control_lo = ffpres_Eng2Internal(p_actuator_3->prs_control_lo, units);

            fferr = WriteAirAction(p_PTB, p_actuator_3->act_fail_action, snd_buf, rcv_buf);
            break;
        }
        case PTB_SUBX_ACTUATOR_3___act_fail_action:
        {
            const u8 *ff_air_action = p_write->source;
            fferr = WriteAirAction(p_PTB, *ff_air_action, snd_buf, rcv_buf);
            break;
        }
        case PTB_SUBX_ACTUATOR_3___shutoff_dp:
        {
            const USIGN16 *shutoff_dp = (const void *)p_write->source;
            a3.shutoff_dp = *shutoff_dp;
            break;
        }
        case PTB_SUBX_ACTUATOR_3___hand_wheel:
        {
            const USIGN8 *hand_wheel = p_write->source;
            a3.hand_wheel = *hand_wheel;
            break;
        }
        case PTB_SUBX_ACTUATOR_3___style:
            break; //not writable
        case PTB_SUBX_ACTUATOR_3___relay_type:
        {
            const USIGN8 *relay_type = p_write->source;
            a3.relay_type = *relay_type;
            break;
        }
        case PTB_SUBX_ACTUATOR_3___supply_prs_max:
        {
            const FLOAT *supply_prs_max = (const void *)p_write->source;
            a3.supply_prs_max = ffpres_Eng2Internal(*supply_prs_max, p_PTB->pressure_range.units);
            break;
        }
        case PTB_SUBX_ACTUATOR_3___prs_control_hi:
        {
            const FLOAT *prs_control_hi = (const void *)p_write->source;
            a3.prs_control_hi = ffpres_Eng2Internal(*prs_control_hi, p_PTB->pressure_range.units);
            break;
        }
        case PTB_SUBX_ACTUATOR_3___prs_control_lo:
        {
            const FLOAT *prs_control_lo = (const void *)p_write->source;
            a3.prs_control_lo = ffpres_Eng2Internal(*prs_control_lo, p_PTB->pressure_range.units);
            break;
        }
        default:
            fferr = E_FB_PARA_CHECK;
            break;
    }

    if(fferr == E_OK)
    {
        if((p_write->subindex == PTB_SUBX_ACTUATOR_3___style) || (p_write->subindex == PTB_SUBX_ACTUATOR_3___act_fail_action))
        {
            //Nothing to save
        }
        else
        {
            ErrorCode_t err = act3min_Set(&a3);
            if(err == ERR_OK)
            {
                //Need to manually increment ST_REV since we don't let Softing write in. Check the uses (in appl_ptb.c)!!!
                fferr = fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ACTUATOR_3);
            }
            else
            {
                //Simplistic but it is the only error we currently have
                fferr = E_FB_TEMP_ERROR;
            }
        }
    }
    return fferr;
}  //lint !e818 const-ness may be confusing to reader since the pointed-to object is modified indirectly

/* This line marks the end of the source */
