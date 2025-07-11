/*****************************************************************************
*                                                                            *
*                     SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                          *
*                                D-85540 Haar                                *
*                        Phone: ++49-89-4 56 56-0                            *
*                          Fax: ++49-89-4 56 56-3 99                         *
*                                                                            *
*                            SOFTING CONFIDENTIAL                            *
*                                                                            *
*                     Copyright (C) SOFTING IA GmbH 2013                     *
*                             All Rights Reserved                            *
*                                                                            *
* NOTICE: All information contained herein is, and remains the property of   *
*   SOFTING Industrial Automation GmbH and its suppliers, if any. The intel- *
*   lectual and technical concepts contained herein are proprietary to       *
*   SOFTING Industrial Automation GmbH and its suppliers and may be covered  *
*   by German and Foreign Patents, patents in process, and are protected by  *
*   trade secret or copyright law. Dissemination of this information or      *
*   reproduction of this material is strictly forbidden unless prior         *
*   written permission is obtained from SOFTING Industrial Automation GmbH.  *
******************************************************************************
******************************************************************************
*                                                                            *
* PROJECT_NAME             Softing FF/PA FD 2.42.A                           *
*                                                                            *
* VERSION                  FF - 2.42.A                                       *
*                          PA - 2.42.A                                       *
*                                                                            *
* DATE                     14. Aug. 2013                                     *
*                                                                            *
*****************************************************************************/


/* ===========================================================================

FILE_NAME          ffbl_res.c



FUNCTIONAL_MODULE_DESCRIPTION

=========================================================================== */
#include "keywords.h"
#define  MODULE_ID      (COMP_FFBL + MOD_FBLKRES)

INCLUDES

  #include "base.h"
  #include "osif.h"
  #include "hw_if.h"
  #include "version.h"
  #include "vfd.h"
  #include "fbs_api.h"
  #include "ffbl_int.h"
  #include "ffbl_res.h"

  #include "except.h"
  #include "hm_api.h"
#include "mnassert.h"
#include "ptbcustomsubx.h"  //for automatically generated artifacts
#include <fbif_dcl.h>
#include <fbif_idx.h>
#include "mnerrorif.h"
#include "faultpublic.h"
#include "ff2nvram.h"

LOCAL_DEFINES

/* What MN doesn't touch or what shouldn't be cleared.
Check definitions in fbap.h and what RB may natively report, in
FF 890 4.4.3.6 Block Error Parameter Formal Model
*/
#define BLK_ERR_SOFTING_SET_RB (BLK_ERR_LINK_CONFIG_ERR|BLK_ERR_BLOCK_CONFIG_ERR|BLK_ERR_LINK_CONFIG_ERR)
/* This is the mask of block errors that pushes RB to OOS.
Gleaned from the original implementation. Excluding BLK_ERR_DEV_FAULT_STATE_SET for now.
*/
#define FAILSAFE_BLOCK_ERR (BLK_ERR_MEMORY_FAILURE|BLK_ERR_LOST_STATIC_DATA)

LOCAL_TYPEDEFS

FUNCTION_DECLARATIONS
  FUNCTION LOCAL VOID Update_alarm_sum_RESB (VOID);

/* AK: It is unacceptable that a static duration variable remains
unprotected in RAM forever.
This is also very sensitive to the order of initialization.
MN_ASSERT in Start_RSB() asserts the correction of this initialization
now to be placed in ROM.
*/
//T_FBIF_BLOCK_INSTANCE T_FBIF_RESB vs T_RESOURCE
#if 1
T_FBIF_RESB *const p_resource = &resb_1;
static const T_FBIF_BLOCK_DESCR *const p_resb_desc = &fbif_block_descr[0];
#else
#include "da_ffbl.h"                             /* DATA SEGMENT DEFINITION */
  NO_INIT T_RESOURCE *                      p_resource;
  STATIC NO_INIT  const T_FBIF_BLOCK_DESCR * p_resb_desc;
#endif

LOCAL_DATA
#include "da_ffbl.h"                             /* DATA SEGMENT DEFINITION */
//AK: OK to have it so because it is self-repairing
static USIGN16                    ffbl_res_old_block_alarm_bits = 0U;
#include "da_def.h"                              /* DEFAULT DATA SEGMENT */


/****************************************************************************/

FUNCTION PUBLIC VOID Start_RESB
  (
    IN T_FBIF_BLOCK_INSTANCE *    p_block_instance
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

#if 0 //See explanation at definitions of those variables
  p_resb_desc   = p_block_instance->p_block_desc;
  p_resource    = p_resb_desc->p_block;
#else
  MN_ASSERT((fbif_block_descr[0].p_block == &resb_1) && (p_block_instance->p_block_desc == p_resb_desc));
#endif

  /* Initialize resource internal data ------------------------------------ */
  //AK: Can't rely on C init: Start_RESB may run more than once
  ffbl_res_old_block_alarm_bits = 0;

  /* Disable update events ------------------------------------------------ */
  ffbl_disable_update_events (&p_resource->update_evt);

#ifdef USE_FIELD_DIAGNOSTICS /* -------------------------------------------- */
  ffbl_fd_start (p_resb_desc);
#endif /* USE_FIELD_DIAGNOSTICS */

  if (p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP)
  {
    // if (hw_write_protection () )
    if (hw_write_protection () || Remote_WP_Jumper())
    {
      p_resource->write_lock = WRITE_LOCKED;
    }
  }

  return;
}






FUNCTION PUBLIC USIGN16 Read_handler_RESB
  (
    IN T_FBIF_BLOCK_INSTANCE *     p_block_instance,
    IN T_FBIF_READ_DATA *          p_read
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Return  E_OK    or a neg. return code defined in fbap.h
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  _UNREF_PARAM (p_block_instance);

 /* Check and/or update parameter to be read ----------------------------- */
  switch (p_read->rel_idx)
  {
    case RES_PAR_RS_STATE:
    {
      /* Update resource state -------------------------------------------- */

      if (p_resource->mode_blk.actual == MODE_OS)
      {
        p_resource->rs_state = RS_STATE_STANDBY;
      }
      else
      {
        if (fbs_links_online ())
          p_resource->rs_state = RS_STATE_ON_LINE;
        else
          p_resource->rs_state = RS_STATE_ON_LINE_LNKING;
      }

      break;
    }

    case RES_PAR_NV_CYCLE_T:
    {
      break;
    }

    case RES_PAR_ALARM_SUM:
    {
      Update_alarm_sum_RESB ();

      break;
    }
  }

  return E_OK;
}







FUNCTION PUBLIC USIGN16 Write_handler_RESB
  (
    IN T_FBIF_BLOCK_INSTANCE *    p_block_instance,
    IN T_FBIF_WRITE_DATA *        p_write
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Return  E_OK    or a neg. return code defined in fbap.h
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8    subindex;
  USIGN8 *  source;
  USIGN16   result;

FUNCTION_BODY

  subindex  = p_write->subindex;
  source    = p_write->source;
  result    = E_OK;

  switch (p_write->rel_idx)
  {
    case RES_PAR_ALERT_KEY:
    {
      if (*source == 0) return (E_FB_PARA_LIMIT);

      break;
    }

    case RES_PAR_MODE_BLK:
    {
      result = ffbl_check_mode (&p_resource->mode_blk,
                          subindex, source, MODE_RES_VALID);
      break;
    }

    case RES_PAR_GRANT_DENY:
    {
      ffbl_bas_write_grant_deny (subindex,source,&p_resource->grant_deny);

      break;
    }

    case RES_PAR_RESTART:
    {
      break;
    }

    case RES_PAR_FEATURE_SEL:
    {
      *((USIGN16 *)source) &= p_resource->features; /* Clear all unsupp bits */

      /* FAILURE --> HW Write Lock Jumper could be in place before according feature_sel bit will be enabled */
      #if 0
      if (*((USIGN16 *)source) & RES_FEAT_HARD_WRITE_LOCK_SUPP)
      {
        /* Feature 'hard write lock' shall be enabled --------------------- */

        // if (hw_write_protection ())
        if (hw_write_protection () || Remote_WP_Jumper())
        {
          /* Do not allow to enable the feature 'hard write lock'
             when the physical hard write lock is enabled ----------------- */

          return (E_FB_WRITE_LOCK);
        }
      }
      #endif
      break;
    }

    case RES_PAR_CYCLE_SEL:
    {
      *((USIGN16 *)source) &= p_resource->cycle_type; /* Clear all unsupp bits */

      break;
    }

    case RES_PAR_SET_FSTATE:
    {
      if (*source == SET_FAULT_STATE_OFF)
      {
        ;  /* do nothing */
      }
      else if ((*source == SET_FAULT_STATE_SET)                  &&
               (p_resource->feature_sel & RES_FEAT_FAULT_STATE_SUPP)   )
      {
        p_resource->fault_state = FAULT_STATE_ACTIVE; /* Set fault state */
        *source = SET_FAULT_STATE_OFF;             /* Reset parameter */
      }
      else
      {
        return (E_FB_PARA_CHECK);
      }

      break;
    }

    case RES_PAR_CLR_FSTATE:
    {
      if (*source == CLR_FAULT_STATE_OFF)
      {
        ;  /* do nothing */
      }
      else if (*source == CLR_FAULT_STATE_CLEAR)
      {
        p_resource->fault_state = FAULT_STATE_CLEAR; /* Clear fault state */
        *source = CLR_FAULT_STATE_OFF;            /* Reset parameter */
      }
      else
      {
        return (E_FB_PARA_CHECK);
      }

      break;
    }

    case RES_PAR_LIM_NOTIFY:
    {
      if (*source > p_resource->max_notify) return (E_FB_PARA_LIMIT);

      break;
    }

    case RES_PAR_CONFIRM_TIME:
    {
      if (*((USIGN32 *)source) == 0) break;

      if (*((USIGN32 *)source) < p_resource->min_cycle_t) return (E_FB_PARA_LIMIT);

      break;
    }

    case RES_PAR_WRITE_LOCK:
    {
      if (p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP)
      {
        /* If hard write lock is enabled, writes to write-lock are not allowed */

        return (E_FB_PARA_CHECK);
      }

      if (!(p_resource->feature_sel & RES_FEAT_SOFT_WRITE_LOCK_SUPP))
      {
        /* If soft write lock is not enabled, writes to write-lock are not allowed */

        return (E_FB_PARA_CHECK);
      }

      if (!((*source == WRITE_LOCKED) || (*source == WRITE_UNLOCKED)))
      {
        return (E_FB_PARA_CHECK);
      }

      break;
    }

    case RES_PAR_UPDATE_EVT:
    {
      result = ffbl_check_unack_flag (&p_resource->update_evt.unack, source, subindex);

      break;
    }

    case RES_PAR_BLOCK_ALM:
    {
      result = ffbl_check_unack_flag (&p_resource->block_alm.unack, source, subindex);

      break;
    }

    case RES_PAR_WRITE_PRI:
    {
      if (*source > WRITE_PRI_MAX) return (E_FB_PARA_LIMIT);

      break;
    }

    case RES_PAR_WRITE_ALM:
    {
      result = ffbl_check_unack_flag (&p_resource->write_alm.unack,
                                                   source, subindex);
      break;
    }

    default:
    {
     #ifdef USE_FIELD_DIAGNOSTICS /* --------------------------------------- */
     result = ffbl_fd_pre_write_check (p_write);
     #endif /* USE_FIELD_DIAGNOSTICS */
    }

  }


  if (result == E_OK)
  {
    result = fbs_write_param (p_block_instance,p_write);
  }


  if (result != E_OK) return (result);


  if (p_write->rel_idx == RES_PAR_RESTART)
  {
    p_resource->restart = RS_RESTART_RUN;
  }
  #ifdef USE_FIELD_DIAGNOSTICS
  else if (p_write->rel_idx == (FD_PAR_SIMULATE + RES_PAR_ITK_VER + 1))
  {
    ffbl_fd_background ();
  }
  #endif
  else if (p_write->rel_idx == RES_PAR_TEST_RW)
  {
    if (p_resource->test_rw.value7 == 85540)
    {
      memset (p_resource->test_rw.value9,0x20,sizeof(p_resource->test_rw.value9));
      memcpy (p_resource->test_rw.value9,PRJ_LABEL,strlen(PRJ_LABEL));
    }
  }

  return (result);
}







FUNCTION GLOBAL VOID Background_RESB
   (
     T_FBIF_BLOCK_INSTANCE *    p_block_instance
   )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

PARAMETERS:
  p_block_instance  Pointer to the transducer block to be executed

RETURN_VALUES:
  none
----------------------------------------------------------------------------*/
{
    USIGN16   alarm_bits;

    /* Update write protection of the resource ------------------------------ */
    USIGN8 wlock = WRITE_UNLOCKED;
    if( (p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP) != 0)
    {
        //HW jumper is in charge
        if(hw_write_protection () || Remote_WP_Jumper())
        {
            wlock = WRITE_LOCKED;
        }
    }
    else if( (p_resource->feature_sel & RES_FEAT_SOFT_WRITE_LOCK_SUPP) != 0)
    {
        //leave unchanged
        wlock = p_resource->write_lock;
    }
    else
    {
        //leave unlocked
    }
    p_resource->write_lock = wlock;


    //Fix-up fault_state
    const T_FBIF_BLOCK_INSTANCE *p_block_instance1 = fbs_get_block_inst(ID_PTB_1);
    T_FBIF_PTB *p_PTB = p_block_instance1->p_block_desc->p_block;
    //if FailState propagate flag is set -- set RB actual (was:target) mode to OOS (propagate FailState)
    bool_t force_oos = false;
    if( ( (p_PTB->failed_state.propagate_mode & PROPAGATE_FAILED_STATE_TO_RB ) != 0 )
       && (0 != p_PTB->failed_state.app) )
    {
        force_oos = true;

        p_resource->fault_state = FAULT_STATE_ACTIVE; /* Set fault state */
    }


    // Collect new block_err bits, and do incidental chores along the way
    u16 BlockErr = p_resource->block_err & BLK_ERR_SOFTING_SET_RB; //filter out what we don't touch

    if(p_resource->fault_state == FAULT_STATE_ACTIVE) //propagated or written
    {
        BlockErr  |= BLK_ERR_DEV_FAULT_STATE_SET; /* Set BLOCK_ERR bit */
    }

    /* 1. Update simulate state of the resource -------------------------------- */
    if (  (hw_get_simulate_enable_jumper() == TRUE)
      ||(Lui_Simulation() != FALSE) )
    {
        BlockErr |= BLK_ERR_SIMULATE_ACTIVE;
    }
#ifdef USE_FIELD_DIAGNOSTICS /* -------------------------------------------- */
    else
    {
        if( (p_resource->block_err & BLK_ERR_SIMULATE_ACTIVE) != 0)
        {
            ffbl_fd_reset_simulate ();
        }
    }
#endif /* USE_FIELD_DIAGNOSTICS */

    //2. Various and sundry self-diagnostics
    if(error_IsFault(FAULT_FW_CHECKSUM)) //In FFP!
    {
        BlockErr |= BLK_ERR_MEMORY_FAILURE;
    }
    if(error_IsFault(FAULT_TMOUT_FLASH_TEST)) //In FFP
    {
        BlockErr |= BLK_ERR_DEV_NEEDS_MAINT_NOW;
    }
    if (error_IsFault(FAULT_NVM_WRITE) || error_IsFault(FAULT_NVM_TEST))
    {
        BlockErr |= BLK_ERR_LOST_STATIC_DATA;
    }

    //3. Any errors mapped from TB
    BlockErr |= MnAlert_GetAlertsEtc(NULL)->rb_block_err;
    p_resource->block_err = BlockErr;

    USIGN8 actual = p_resource->mode_blk.actual;

    /* Update actual mode of the resource block ----------------------------- */
    if( ((BlockErr & (FAILSAFE_BLOCK_ERR)) != 0) || ((p_resource->mode_blk.target & MODE_OS) != 0) || force_oos)
    {
        BlockErr |= BLK_ERR_OUT_OF_SERVICE;
        p_resource->block_err = BlockErr; //for fear of any interference

        //In this case we jam mode_blk.actual to MODE_OS
        if (actual != MODE_OS)
        {
            //i.e. we were in AUTO and transitioning to OOS)
            ffbl_disable_update_events (&p_resource->update_evt);
        }
        p_resource->mode_blk.actual = MODE_OS;
    }
    else
    {
        p_resource->mode_blk.actual = p_resource->mode_blk.target;
        if( (p_resource->mode_blk.actual == MODE_AUTO) && (actual != MODE_AUTO) )
        {
            ffbl_enable_update_events (
              p_resb_desc->block_id,
              p_resb_desc->idx_upd_evt,
              &p_resource->update_evt,
              p_resource->st_rev
            );
        }
    }

    if (p_resource->block_err & BLK_ERR_OUT_OF_SERVICE)
    {
        alarm_bits = BLK_ERR_OUT_OF_SERVICE;
    }
    else
    {
        alarm_bits = p_resource->block_err;
    }


//lint -estring(457,ffbl_res_old_block_alarm_bits) Review carefully since it is fragile;
//for now I made the underlying ffbl_update_block_alarm() handle ffbl_res_old_block_alarm_bits atomically
  /* Update resource block alarm ------------------------------------------ */
  ffbl_bas_update_extended_block_alarm
  (
    p_block_instance->p_block_desc, &p_resource->block_alm,
    p_resource->alarm_sum.disable, p_resource->ack_option,
    alarm_bits, &ffbl_res_old_block_alarm_bits
  );

#ifdef USE_FIELD_DIAGNOSTICS /* -------------------------------------------- */
  /* Fix of TTP#947 */
  ffbl_fd_background ();
#endif /* USE_FIELD_DIAGNOSTICS */

  if (p_resource->write_alm.current == ALARM_CLEAR)
  {
    if (p_resource->write_lock == WRITE_UNLOCKED)
    {
      if (!(p_resource->alarm_sum.disable & ALARM_SUM_DISC))
      {
        if ((p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP) ||
            (p_resource->feature_sel & RES_FEAT_SOFT_WRITE_LOCK_SUPP)    )
        {
          if (p_resource->write_pri)
          {
            T_FBS_ALERT_NOTIFY  resb_alert_notify;

            resb_alert_notify.action              = ALARM_ACTIVE;
            resb_alert_notify.block_id            = 0; /* block id for resource block is fix */
            resb_alert_notify.rel_idx             = RES_PAR_WRITE_ALM;
            resb_alert_notify.priority            = p_resource->write_pri;
            resb_alert_notify.data.dsc.subcode    = 0;
            resb_alert_notify.data.dsc.value      = WRITE_UNLOCKED;
            resb_alert_notify.data.dsc.mbit_mask  = 0;

            fbs_alert_notify (&resb_alert_notify);

            if (p_resource->ack_option & ALARM_SUM_DISC)      /* Auto ack. enabled */
                 p_resource->write_alm.unack = ALARM_ACKED;
            else p_resource->write_alm.unack = ALARM_UNACKED;
          }
        }
      }
    }
  }

  else if (p_resource->write_alm.current == ALARM_ACTIVE)
  {
    BOOL clear_write_alm = FALSE;

    if (p_resource->write_lock == WRITE_LOCKED)
    {
      clear_write_alm = TRUE;
    }

    if (p_resource->alarm_sum.disable & ALARM_SUM_DISC)
    {
      clear_write_alm = TRUE;
    }

    if (p_resource->write_pri == 0)
    {
      clear_write_alm = TRUE;
    }

    if ((!(p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP)) &&
        (!(p_resource->feature_sel & RES_FEAT_SOFT_WRITE_LOCK_SUPP))    )
    {
      clear_write_alm = TRUE;
    }

    if (clear_write_alm)
    {
      T_FBS_ALERT_NOTIFY  resb_alert_notify;

      resb_alert_notify.action              = ALARM_CLEAR;
      resb_alert_notify.block_id            = 0; /* block id for resource block is fix */
      resb_alert_notify.rel_idx             = RES_PAR_WRITE_ALM;
      resb_alert_notify.priority            = p_resource->write_pri;
      resb_alert_notify.data.dsc.subcode    = 0;
      resb_alert_notify.data.dsc.mbit_mask  = 0;

      if (p_resource->write_lock == WRITE_LOCKED)
      {
        resb_alert_notify.data.dsc.value      = WRITE_LOCKED;
      }
      else
      {
        resb_alert_notify.data.dsc.value      = 0;
      }


      fbs_alert_notify (&resb_alert_notify);
    }
  }

  return;
}


FUNCTION LOCAL VOID Update_alarm_sum_RESB (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

----------------------------------------------------------------------------*/
{
    /* Update the 'current' bitfield ---------------------------------------- */
    p_resource->alarm_sum.current = 0;

    //Combine native and mapped block errors


    if (p_resource->block_err!=0)
    {
        p_resource->alarm_sum.current |= ALARM_SUM_BLOCK;
    }
    if (p_resource->write_alm.current == ALARM_ACTIVE)
    {
        p_resource->alarm_sum.current |= ALARM_SUM_DISC;
    }

    /* Update the 'unrep' bitfield ------------------------------------------ */
    p_resource->alarm_sum.unrep = 0;

    if (_ALARM_NOT_REPORTED(p_resource->block_alm.state))
    {
        p_resource->alarm_sum.unrep |= ALARM_SUM_BLOCK;
    }
    if (_ALARM_NOT_REPORTED(p_resource->write_alm.state))
    {
        p_resource->alarm_sum.unrep |= ALARM_SUM_DISC;
    }

    /* Update the 'unack' bitfield ------------------------------------------ */
    p_resource->alarm_sum.unack = 0;

    if (_ALARM_NOT_ACKNOWLEDGED(p_resource->block_alm.unack))
    {
        p_resource->alarm_sum.unack |= ALARM_SUM_BLOCK;
    }
    if (_ALARM_NOT_ACKNOWLEDGED(p_resource->write_alm.unack))
    {
        p_resource->alarm_sum.unack |= ALARM_SUM_DISC;
    }

#ifdef USE_FIELD_DIAGNOSTICS
    ffbl_fd_update_alarm_sum (&p_resource->alarm_sum);
#endif /* USE_FIELD_DIAGNOSTICS */

    p_resource->alarm_sum.current &= ~p_resource->alarm_sum.disable;
    p_resource->alarm_sum.unrep   &= ~p_resource->alarm_sum.disable;
    p_resource->alarm_sum.unack   &= ~p_resource->alarm_sum.disable;

  return;
}





FUNCTION GLOBAL VOID ffbl_provide_resb_data_to_fdc
  (
    OUT USIGN32 *   p_manufac_id,
    OUT USIGN16 *   p_dev_type,
    OUT USIGN32 *   p_min_cycle_t
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by Field Device Communication stack in the device
  startup phase.

  It provides some resource block parameters.

PARAMETERS
  p_manufac_id      Pointer to the parameter MAX_NOTIFY
  p_dev_type        Pointer to the parameter DEV_TYPE
  p_min_cycle_t     Pointer to the parameter MIN_CYCLE_T

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  _ASSERT (p_resource != NULL);

  *p_manufac_id   = p_resource->manufac_id;
  *p_dev_type     = p_resource->dev_type;
  *p_min_cycle_t  = p_resource->min_cycle_t;

  return;
}






FUNCTION GLOBAL VOID ffbl_provide_resb_data_to_fbs
  (
    OUT USIGN8 * *   pp_max_notify,
    OUT USIGN8 * *   pp_lim_notify,
    OUT USIGN32 * *  pp_confirm_time,
    OUT USIGN16 * *  pp_feature_sel
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by FB shell in the device startup phase.

  It provides pointers to some resource block parameters.

PARAMETERS
  pp_max_notify     Pointer to pointer to the parameter MAX_NOTIFY
  pp_lim_notify     Pointer to pointer to the parameter LIM_NOTIFY
  pp_confirm_time   Pointer to pointer to the parameter CONFIRM_TIME
  pp_feature_sel    Pointer to pointer to the parameter FEATURE_SEL

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  _ASSERT (p_resource != NULL);

  *pp_max_notify   = &p_resource->max_notify;
  *pp_lim_notify   = &p_resource->lim_notify;
  *pp_confirm_time = &p_resource->confirm_time;
  *pp_feature_sel  = &p_resource->feature_sel;

  return;
}






FUNCTION GLOBAL USIGN16 ffbl_check_write_lock
  (
    IN USIGN16 index
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by FB shell when a parameter has to be written.

PARAMETERS
  index             Index of the parameter to be written

RETURN_VALUES
  E_OK              Parameter is writeable
  E_FB_WRITE_LOCK   Parameter is not writeable
----------------------------------------------------------------------------*/
{
    USIGN16 ret = E_OK;

    /* AK: First, if it is a TB custom parameter, delegate the decision
    to Write_Handler_PTB() because of non-GW storage
    */
    u32 rel_index = index - fbif_block_descr[ID_PTB_1].start_index;
    /* EXPLANATION: It's a very large number if index is before PTB
    */
    if((rel_index < fbif_block_descr[ID_PTB_1].no_of_param) && (rel_index >= TB_CUSTOM_FIRST_REL_INDEX))
    {
        //We are in TB range.
        //Already set: ret = E_OK;
    }
    else
    {
        if (p_resource->write_lock == WRITE_LOCKED)
        {
            if (p_resource->feature_sel & RES_FEAT_HARD_WRITE_LOCK_SUPP)
            {
              ret = (E_FB_WRITE_LOCK);
            }

            else
            {
                if (index != (p_resb_desc->start_index + RES_PAR_WRITE_LOCK))
                {
                    ret = (E_FB_WRITE_LOCK);
                }
            }
        }
    }
    return ret;
}

