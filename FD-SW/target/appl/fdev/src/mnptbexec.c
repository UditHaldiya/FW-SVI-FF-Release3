/**
    \file mntbexec.c
    \brief Some application-level TB executiuon stuff coded by MN

*/
#include <softing_base.h>
#include <ptb.h>
#include <dofb.h>
#include "mndoswff.h"
#include "mn_fstate.h"
#include "ptbcustomsubx.h"
#include "pressure_range.h"
#include "appl_alert.h"
#define MN_READBACK_SELECT_FINALPOS    0
#define MN_READBACK_SELECT_WORKINGPOS  1

typedef void TbChannelFunc_t(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val);

/** \brief A hacky helper to elicit IMAN in an upsteam FB (AO or DO)
*/
static void tb_FixupStatus(const T_FBIF_PTB *p_PTB, FLOAT_S *p_process_val)
{
    if((p_PTB->mode_blk.actual & (MODE_MAN|MODE_LO)) != 0U)
    {
        p_process_val->status = (p_process_val->status & ~SUB_STATUS_MASK) | MN_SUB_COMMON_MAN_LO;
    }
}

/* TFS:16709,16710 traced to a Softing bug in AO FB where AO's first GOOD OUT is grabbed
from last written value in MAN. (If target mode is AUTO, AO FB silently starts
in MAN which is a bug in its own right)
A kludgy workaround is to ignore a few first runs of FB application
We may want to revert this when/if Softing provides a fix
*/
#define IGNORE_COUNT 3

static void tb_PositionSp(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    static u8 ignore_count = IGNORE_COUNT;
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    FLOAT_S                   local_final_value = *p_process_val;
    T_FBS_WRITE_PARAM_LOCAL   p_write_loc;

#if 0
    // if PTB is in OOS: FINAL_VALUE status must be OOS regardless of upstream status
    //                   FINAL_VALUE value shall not change
    if ( p_PTB->mode_blk.actual == MODE_OS )
    {
        local_final_value.status = SQ_BAD | SUB_OUT_OF_SERVICE;
    }
#endif

    if(ignore_count > 0)
    {
        --ignore_count;
        local_final_value.status = SQ_UNCERTAIN | SUB_INITIAL_VALUE;
    }

#if 0 //doesn't quite work; see a hack in ffbl_ao.c instead
    if((p_PTB->mode_blk.target & MODE_AUTO)!= 0U)
    {
        if(local_final_value.status == (SQ_UNCERTAIN|SUB_LUV)) //That's what Softing sends; FRAGILE!
        {
            local_final_value.status = SQ_GOOD;
        }
    }
#endif
    //write local_final_value to FINAL_VALUE in PTB block
    if (p_PTB->mode_blk.actual != MODE_MAN)
    {
        p_write_loc.subindex = 0;
        p_write_loc.length   = sizeof(FLOAT_S);
        p_write_loc.rel_idx = REL_IDX_PTB_FINAL_VALUE;
        p_write_loc.source   = (USIGN8*) (&local_final_value);
        p_write_loc.startup_sync = FALSE;
        (void)mn_fbs_write_param_loc( p_block_instance, &p_write_loc );
    }

    /* write AOFB readback parameter */
    switch (p_PTB->readback_select)
    {
        case MN_READBACK_SELECT_FINALPOS :        // Spec: 0 - Final Position
            *p_process_val = p_PTB->final_position_value;
            break;
        case MN_READBACK_SELECT_WORKINGPOS :      // Spec: 1 - Working Position
            *p_process_val = p_PTB->working_pos;
            break;
        default :                                 // Error!
            break;
    }

    if(p_PTB->mode_blk.actual != MODE_AUTO)
    {
        ignore_count = IGNORE_COUNT;
    }

    tb_FixupStatus(p_PTB, p_process_val);
} //lint !e818 all helper functions must have the same prototype


static void tb_IntSp(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    static u8 ignore_count = IGNORE_COUNT;
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    DISCRETE_S                local_final_value_dint = *(DISCRETE_S *)(void *)p_process_val;
    T_FBS_WRITE_PARAM_LOCAL   p_write_loc;

#if 0
    // if PTB is in OOS: FINAL_VALUE_DINT status must be OOS regardless of upstream status
    //                   FINAL_VALUE_DINT value shall not change
    if ( p_PTB->mode_blk.actual == MODE_OS )
    {
        local_final_value_dint.status = SQ_BAD | SUB_OUT_OF_SERVICE;
    }
#endif

    if(ignore_count > 0)
    {
        --ignore_count;
        local_final_value_dint.status = SQ_UNCERTAIN | SUB_INITIAL_VALUE;
    }

#if 0
    // only if PTB is in AUTO mode FINAL_VALUE_DINT should reflect SP_D from upstream
    if ( p_PTB->mode_blk.actual == MODE_AUTO )
    {
        local_final_value_dint.status = ((DISCRETE_S *)(void *)p_process_val)->status;
    }

    //write local_final_value_dint to FINAL_VALUE_DINT in PTB block
    if ( (p_PTB->mode_blk.actual == MODE_AUTO) || (p_PTB->mode_blk.actual == MODE_OS) )
#endif
    if ( (p_PTB->mode_blk.actual != MODE_MAN) )
    {
        p_write_loc.subindex = 0;
        p_write_loc.length   = sizeof(DISCRETE_S);
        p_write_loc.rel_idx = REL_IDX_PTB_FINAL_VALUE_DINT;
        p_write_loc.source   = (USIGN8*) (&local_final_value_dint);
        p_write_loc.startup_sync = FALSE;
        (void)mn_fbs_write_param_loc( p_block_instance, &p_write_loc );
    }

    /* write DOFBInt readback parameter */
    *(DISCRETE_S *)(void *)p_process_val = p_PTB->final_position_value_dint;

    if(p_PTB->mode_blk.actual != MODE_AUTO)
    {
        ignore_count = IGNORE_COUNT;
    }

    tb_FixupStatus(p_PTB, p_process_val);
} //lint !e818 all helper functions must have the same prototype


static void tb_BoolSp(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    static u8 ignore_count = IGNORE_COUNT;
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    T_FBS_WRITE_PARAM_LOCAL   p_write_loc;
    DISCRETE_S                local_final_value_d = *(DISCRETE_S *)(void *)p_process_val;

#if 0
    // if PTB is in OOS: FINAL_VALUE_D status must be OOS regardless of upstream status
    //                   FINAL_VALUE_D value shall not change
    if ( p_PTB->mode_blk.actual == MODE_OS )
    {
        local_final_value_d.status = SQ_BAD | SUB_OUT_OF_SERVICE;
    }
#endif

    if(ignore_count > 0)
    {
        --ignore_count;
        local_final_value_d.status = SQ_UNCERTAIN | SUB_INITIAL_VALUE;
    }

#if 0
    // only if PTB is in AUTO mode FINAL_VALUE_DINT should reflect SP_D from upstream
    if ( p_PTB->mode_blk.actual == MODE_AUTO )
    {
        local_final_value_d.status = ((DISCRETE_S *)(void *)p_process_val)->status;
    }

    //write local_final_value_d to FINAL_VALUE_D in PTB block
    if ( (p_PTB->mode_blk.actual == MODE_AUTO) || (p_PTB->mode_blk.actual == MODE_OS) )
#endif
    if ( (p_PTB->mode_blk.actual != MODE_MAN) )
    {
        //cast value from <float> to <u8> so that we can compare integer to integer
        local_final_value_d.value = ((DISCRETE_S *)(void *)p_process_val)->value;
        if ( local_final_value_d.value != 0 )
        {
            local_final_value_d.value = 1;
        }
        p_write_loc.subindex = 0;
        p_write_loc.length   = sizeof(DISCRETE_S);
        p_write_loc.rel_idx = REL_IDX_PTB_FINAL_VALUE_D;
        p_write_loc.source   = (USIGN8*) (&local_final_value_d);
        p_write_loc.startup_sync = FALSE;
        (void)mn_fbs_write_param_loc( p_block_instance, &p_write_loc );
    }

    /* write DOFBBool readback parameter */
    *(DISCRETE_S *)(void *)p_process_val = p_PTB->final_position_value_d;

    if(p_PTB->mode_blk.actual != MODE_AUTO)
    {
        ignore_count = IGNORE_COUNT;
    }

    tb_FixupStatus(p_PTB, p_process_val);
} //lint !e818 all helper functions must have the same prototype

/** \brief A simple helper to retrieve DO FB channel configuration
\param fbid - a DO FB block id (ID_DOFB_1 or ID_DOFB_2)
\return the block's channel
*/
static u16 dofb_GetChannel(u8 fbid)
{
    const T_FBIF_BLOCK_INSTANCE *p_DOFB_instance = fbs_get_block_inst(fbid);
    T_FBIF_DOFB *p_DOFB = p_DOFB_instance->p_block_desc->p_block;
    return p_DOFB->channel;
}

/** \brief A guard patrol for a DO FB to remove its fstate request if
the channel no longer matches.
\param fbid - a DO FB block id (ID_DOFB_1 or ID_DOFB_2)
*/
static void dofb_FstatePatrol(u8 fbid)
{
    if(dofb_GetChannel(fbid) != CH_DO_FAULT)
    {
        fstate_ForceFstate(fbid, false);
    }
}

/** \brief Application-specific guard of external fstate requests.
May change with changes in channels and FB nomenclature
*/
void tb_FstatePatrol(void)
{
    dofb_FstatePatrol(ID_DOFB_1);
    dofb_FstatePatrol(ID_DOFB_2);
}

static void tb_ForceFstate(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    static u8 ignore_count = IGNORE_COUNT;
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    DISCRETE_S pfstate = *(DISCRETE_S *)(void *)p_process_val;

    if(ignore_count > 0)
    {
        --ignore_count;
        pfstate.status = SQ_UNCERTAIN | SUB_INITIAL_VALUE;
    }

    if(p_PTB->mode_blk.actual == MODE_AUTO) //So that we don't accidentally chop off fingers of a local guy
    {
        if((pfstate.status & SQ_GOOD) == SQ_GOOD)
        {
            //Who's calling?
            u8 fbid = ID_DOFB_1;
            if(dofb_GetChannel(fbid) != CH_DO_FAULT)
            {
                //must be DO 2 then
                fbid = ID_DOFB_2;
            }
            //NOTE: This doesn't scale well but who cares now?

            fstate_ForceFstate(fbid, pfstate.value != 0);
        }
        else
        {
            //don't do anything
        }
    }

    /* DO NOT write readback parameter: it is unchanged */

    if(p_PTB->mode_blk.actual != MODE_AUTO)
    {
        ignore_count = IGNORE_COUNT;
    }

} //lint !e818 all helper functions must have the same prototype


//*****  Helper functions for ANALOG INPUT block *****
static void tb_SupplyPressure(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write supply_pressure value and status to AIFB channel */
    p_process_val->value = ffpres_ReadPressureEngByIndex(pres_supply);
    p_process_val->status = p_PTB->supply_pressure.status;
} //lint !e818 all helper functions must have the same prototype

static void tb_Act1Pressure(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write actuator_a_pressure value and status to AIFB channel */
    p_process_val->status = p_PTB->actuator_a_pressure.status;
    p_process_val->value = ffpres_ReadPressureEngByIndex(pres_act_a);
} //lint !e818 all helper functions must have the same prototype

static void tb_Act2Pressure(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write actuator_b_pressure value and status to AIFB channel */
    p_process_val->status = p_PTB->actuator_b_pressure.status;
    p_process_val->value = ffpres_ReadPressureEngByIndex(pres_act_b);
} //lint !e818 all helper functions must have the same prototype

static void tb_PilotPressure(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write pilot_pressure value and status to AIFB channel */
    p_process_val->status = p_PTB->pilot_pressure.status;
    p_process_val->value = ffpres_ReadPressureEngByIndex(pres_pilot);
} //lint !e818 all helper functions must have the same prototype

static void tb_IPcurrent(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write ip_current value and status to AIFB channel */
    *p_process_val = p_PTB->ip_drive_current;
} //lint !e818 all helper functions must have the same prototype

static void tb_Temperature(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write temperature value and status to AIFB channel */
    *p_process_val = p_PTB->temperature;
} //lint !e818 all helper functions must have the same prototype

static void tb_FinalValue(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write final_value value and status to AIFB channel */
    *p_process_val = p_PTB->final_value;
} //lint !e818 all helper functions must have the same prototype

static void tb_FinalPosValue(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write final_position_value value and status to AIFB channel */
    *p_process_val = p_PTB->final_position_value;
} //lint !e818 all helper functions must have the same prototype

static void tb_WorkingSP(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write working_sp value and status to AIFB channel */
    *p_process_val = p_PTB->working_sp;
} //lint !e818 all helper functions must have the same prototype

static void tb_WorkingPos(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    /* write working_pos value and status to AIFB channel */
    *p_process_val = p_PTB->working_pos;
} //lint !e818 all helper functions must have the same prototype


//*****  Helper functions for DISCRETE INPUT block *****
static void tb_Switch1(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    DISCRETE_S *p = (DISCRETE_S *)(void *)p_process_val;
    /* write discrete_output_1 value and status to DIFB channel */
    p->status = p_PTB->discrete_output_1_state.status;
    p->value = p_PTB->discrete_output_1_state.value;
} //lint !e818 all helper functions must have the same prototype

static void tb_Switch2(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    DISCRETE_S *p = (DISCRETE_S *)(void *)p_process_val;
    /* write discrete_output_2 value and status to DIFB channel */
    p->status = p_PTB->discrete_output_2_state.status;
    p->value = p_PTB->discrete_output_2_state.value;
} //lint !e818 all helper functions must have the same prototype

static void tb_DiscreteInput(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    DISCRETE_S *p = (DISCRETE_S *)(void *)p_process_val;
    /* write discrete_input value and status to DIFB channel */
    p->status = p_PTB->discrete_input.status;
    p->value = p_PTB->discrete_input.value;
} //lint !e818 all helper functions must have the same prototype

static void tb_AnalogInput(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    FLOAT_S *p = p_process_val;
    /* write analog_input value and status to AI FB channel */
#ifdef REL_IDX_PTB_ANALOG_INPUT
    p->status = p_PTB->analog_input.status;
    p->value = p_PTB->analog_input.value;
#else
    UNUSED_OK(p_PTB);
    UNUSED_OK(p);
#endif
} //lint !e818 all helper functions must have the same prototype

static void tb_MAIchannels(T_FBIF_BLOCK_INSTANCE *p_block_instance, FLOAT_S *p_process_val)
{
    T_FBIF_PTB *p_PTB         = p_block_instance->p_block_desc->p_block;
    FLOAT_S *p = p_process_val;
    // write 8 channels AI values and statuses to MAI block
    p[0].value = ffpres_ReadPressureEngByIndex(pres_supply);
    p[0].status = p_PTB->supply_pressure.status;

    p[1].value = ffpres_ReadPressureEngByIndex(pres_act_a);
    p[1].status = p_PTB->actuator_a_pressure.status;

    p[2].value = ffpres_ReadPressureEngByIndex(pres_act_b);
    p[2].status = p_PTB->actuator_b_pressure.status;

    p[3].value = ffpres_ReadPressureEngByIndex(pres_pilot);
    p[3].status = p_PTB->pilot_pressure.status;

    p[4] = p_PTB->ip_drive_current;
    p[5] = p_PTB->temperature;
    p[6] = p_PTB->working_sp;
    p[7] = p_PTB->working_pos;
} //lint !e818 all helper functions must have the same prototype


static TbChannelFunc_t * const TbChannelFunc[] =
{
    [CH_AI_NOT_CONFIGURED] = NULL,
    [CH_AO_POSITION] = tb_PositionSp,
    [CH_DO_POSITION_OPEN_CLOSE] = tb_BoolSp,
    [CH_DO_POSITION_DISCRETE_POSITION] = tb_IntSp,
    [CH_DO_DISCRETE_SWITCH_1] = tb_DOsw1,
    [CH_DO_DISCRETE_SWITCH_2] = tb_DOsw2,
    [CH_DO_FAULT] = tb_ForceFstate,
    [CH_AI_SUPPLY_PRESSURE] = tb_SupplyPressure,
    [CH_AI_ACTUATOR_PRESSURE_1] = tb_Act1Pressure,
    [CH_AI_ACTUATOR_PRESSURE_2] = tb_Act2Pressure,
    [CH_AI_IP_CURRENT] = tb_IPcurrent,
    [CH_AI_PILOT_PRESSURE] = tb_PilotPressure,
    [CH_AI_TEMPERATURE] = tb_Temperature,
    [CH_AI_FINAL_VALUE] = tb_FinalValue,
    [CH_AI_FINAL_POSITION_VALUE] = tb_FinalPosValue,
    [CH_AI_WORKING_SP] = tb_WorkingSP,
    [CH_AI_WORKING_POSITION] = tb_WorkingPos,
    [CH_AI_ANALOG_INPUT] = tb_AnalogInput,
    [CH_DI_DISCRETE_INPUT] = tb_DiscreteInput,
    [CH_DI_STATE_OF_SW1] = tb_Switch1,
    [CH_DI_STATE_OF_SW2] = tb_Switch2,
    [CH_MAI_CHANNEL1] = tb_MAIchannels,
};

/**
\brief A TB callback called separately with each channel number
It must dispatch prosessing ASAP.
Individual channel functions should be fast, too, and do what their channel dictates

  This function is called by the execution function of a AI function block.
  It has to provide a analog input value.

\param  p_block_instance  Pointer to the transducer block to be executed
\param  p_exec_tb         Pointer to a process data description block.
The relevant components of the process data description block are:

    channel             Channel number

    p_process_value     Pointer to the process value (type FLOAT_S *)

    p_xd_scale          Pointer to the XD_SCALE parameter of the AI block
*/
void Execute_PTB(T_FBIF_BLOCK_INSTANCE *p_block_instance, T_FBIF_PROCESS_DATA *p_exec_tb)
{
    FLOAT_S *p_process_val = p_exec_tb->p_process_value;

    u16 channel = p_exec_tb->channel;
    if((channel >= NELEM(TbChannelFunc)) || (TbChannelFunc[channel] == NULL))
    {
        //Softing's default action
        p_process_val->value  = 0.0F;
        p_process_val->status = SQ_BAD | SUB_CONFIGURATION_ERROR;
    }
    else
    {
        TbChannelFunc[channel](p_block_instance, p_process_val);

        ff_fstate_Execute_fromFB(p_block_instance, channel);
        ff_AlertSPTimeout_Execute_fromFB(p_block_instance, channel);
    }
} //lint !e818 Softing prototype - can't change (automatically generated)



/* This line marks the end of the source */
