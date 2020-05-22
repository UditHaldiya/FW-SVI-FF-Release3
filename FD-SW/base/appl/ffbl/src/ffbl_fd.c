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

FILE_NAME          ffbl_bas.c



FUNCTIONAL_MODULE_DESCRIPTION

=========================================================================== */
  #include "keywords.h"
  #define  MODULE_ID      (COMP_FFBL + MOD_FBLKFD)

INCLUDES
  #include "base.h"
  #include "osif.h"
  #include "except.h"
  #include "vfd.h"
  #include "fbif_idx.h"
  #include "fbap.h"
  #include "ffbl_int.h"
  #include "fbs_api.h"
  #include "ffbl_api.h"
  #include "ffbl_res.h"
  #include <fbif_dcl.h>

/* Possible AK_CONSTIZE values are:
0 - revert to original Softing version
1 - (intended) constant version
2 - (debug) combined version to inspect that the following values are identical:
ffbl_fd_map and ffbl_fd_map_c
ffbl_fd_active and ffbl_fd_active_c
ffbl_fd_mask and ffbl_fd_mask_c
ffbl_fd_alm and ffbl_fd_alm_c
ffbl_fd_pri and ffbl_fd_pri_c
ffbl_fd_start_idx and ffbl_fd_start_idx_c
*/
#define AK_CONSTIZE 1

#if AK_CONSTIZE==2
#include "mnassert.h"
#endif
#include "crc.h"

LOCAL_DEFINES


#define NO_OF_FD_ALARMS   4
#define FD_FAIL           0
#define FD_OFFSPEC        1
#define FD_MAINT          2
#define FD_CHECK          3

#define FFBL_FD_SIM_RECOMMENDED_ACT   1

LOCAL_TYPEDEFS

FUNCTION_DECLARATIONS

FUNCTION LOCAL VOID ffbl_fd_update_fd_alarm
  (
    IN USIGN16        fd_idx,
    IN USIGN32        field_diagnostic_value
  );

IMPORT_DATA

EXPORT_DATA

#include "da_ffbl.h"                             /* DATA SEGMENT DEFINITION */

#if AK_CONSTIZE!=1
static NO_INIT T_FD_PARAM *               p_fd;
STATIC NO_INIT  USIGN32 *           ffbl_fd_map   [NO_OF_FD_ALARMS];
STATIC NO_INIT  USIGN32 *           ffbl_fd_active[NO_OF_FD_ALARMS];
STATIC NO_INIT  USIGN32 *           ffbl_fd_mask  [NO_OF_FD_ALARMS];
STATIC NO_INIT  ALARM_FD_DIAG *     ffbl_fd_alm   [NO_OF_FD_ALARMS];
STATIC NO_INIT  USIGN8 *            ffbl_fd_pri   [NO_OF_FD_ALARMS];
STATIC NO_INIT  USIGN16             ffbl_fd_start_idx;
#endif

#include "da_def.h"                              /* DEFAULT DATA SEGMENT */

LOCAL_DATA


typedef struct FdAlarmSrc_t
{
    USIGN16  ffbl_fd_alarm_source[32];
    u16 CheckWord;
} FdAlarmSrc_t;

typedef struct FdAlarmBits_t
{
    USIGN32 ffbl_fd_alarm_bits[NO_OF_FD_ALARMS];
    u16 CheckWord;
} FdAlarmBits_t;

//AK: Rely on zero-init
static FdAlarmSrc_t FdAlarmSrc = {.CheckWord = CRC_SEED};
static FdAlarmBits_t FdAlarmBits = {.CheckWord = CRC_SEED};

#if AK_CONSTIZE!=0
static const USIGN16 ffbl_fd_start_idx_c = REL_IDX_RESB_FD_VER;

static USIGN32 *const ffbl_fd_map_c[NO_OF_FD_ALARMS] =
{
    [FD_FAIL] = &resb_1.fd_fail_map,
    [FD_OFFSPEC] = &resb_1.fd_offspec_map,
    [FD_MAINT] = &resb_1.fd_maint_map,
    [FD_CHECK] = &resb_1.fd_check_map,
};

static USIGN32 *const ffbl_fd_active_c[NO_OF_FD_ALARMS] =
{
    [FD_FAIL] = &resb_1.fd_fail_active,
    [FD_OFFSPEC] = &resb_1.fd_offspec_active,
    [FD_MAINT] = &resb_1.fd_maint_active,
    [FD_CHECK] = &resb_1.fd_check_active,
};

static USIGN32 *const ffbl_fd_mask_c[NO_OF_FD_ALARMS] =
{
    [FD_FAIL] = &resb_1.fd_fail_mask,
    [FD_OFFSPEC] = &resb_1.fd_offspec_mask,
    [FD_MAINT] = &resb_1.fd_maint_mask,
    [FD_CHECK] = &resb_1.fd_check_mask,
};

static ALARM_FD_DIAG *const ffbl_fd_alm_c[NO_OF_FD_ALARMS] =
{
    [FD_FAIL] = &resb_1.fd_fail_alm,
    [FD_OFFSPEC] = &resb_1.fd_offspec_alm,
    [FD_MAINT] = &resb_1.fd_maint_alm,
    [FD_CHECK] = &resb_1.fd_check_alm,
};

static USIGN8 *const ffbl_fd_pri_c[NO_OF_FD_ALARMS] =
{
    [FD_FAIL] = &resb_1.fd_fail_pri,
    [FD_OFFSPEC] = &resb_1.fd_offspec_pri,
    [FD_MAINT] = &resb_1.fd_maint_pri,
    [FD_CHECK] = &resb_1.fd_check_pri,
};
#endif //AK_CONSTIZE
#if AK_CONSTIZE==1
#define ffbl_fd_start_idx ffbl_fd_start_idx_c
#define ffbl_fd_map ffbl_fd_map_c
#define ffbl_fd_active ffbl_fd_active_c
#define ffbl_fd_mask ffbl_fd_mask_c
#define ffbl_fd_alm ffbl_fd_alm_c
#define ffbl_fd_pri ffbl_fd_pri_c
#endif //AK_CONSTIZE


/****************************************************************************/

FUNCTION PUBLIC VOID ffbl_fd_start
  (
    IN const T_FBIF_BLOCK_DESCR    * p_block_desc
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  Start routine field diagnostics module

PARAMETERS
  p_block_desc  Pointer to the object descriptions of the resource block

RETURN
  none

----------------------------------------------------------------------------*/
{
    osif_disable_all_tasks();
        memset (FdAlarmBits.ffbl_fd_alarm_bits,0x00,sizeof(FdAlarmBits.ffbl_fd_alarm_bits));
        STRUCT_CLOSE(FdAlarmBits_t, &FdAlarmBits);
        memset (FdAlarmSrc.ffbl_fd_alarm_source,0x00,sizeof(FdAlarmSrc.ffbl_fd_alarm_source));
        STRUCT_CLOSE(FdAlarmSrc_t, &FdAlarmSrc);
        CONST_ASSERT(sizeof(FdAlarmSrc.ffbl_fd_alarm_source) == 32*sizeof(USIGN16));
    osif_enable_all_tasks();

#if AK_CONSTIZE == 1
/* Nothing to be initialized because of static initialization
*/
    UNUSED_OK(p_block_desc);
#endif
#if AK_CONSTIZE != 1
LOCAL_VARIABLES
  USIGN16                       i;
  const T_BLK_OBJ_DESC *        p_obj_desc;

FUNCTION_BODY

  for (i = REL_IDX_RESB_FD_VER; i < p_block_desc->no_of_param; i++)
  {
    p_obj_desc = p_block_desc->list_of_obj_desc[i];

    if (p_obj_desc->r_var_obj_descr.obj_code      == RECORD_OBJECT    &&
        p_obj_desc->r_var_obj_descr.index_of_type == DS_ALARM_FD_DIAG    )
    {
      break;
    }
  }
    const T_FBIF_PARAM_DESCR *    p_param_desc;
    osif_disable_all_tasks();


    if (i >= p_block_desc->no_of_param)
    {
        /* The resource block has got no FD alarm parameter ------------------- */
        p_fd = NULL;
    }
    else
    {
        /* The resource block has an FD alarm parameter ------------------------- */
        ffbl_fd_start_idx = i - FD_PAR_FAIL_ALM;

        p_param_desc = &p_block_desc->param_dir[ffbl_fd_start_idx];

        _ASSERT(p_param_desc != NULL);

        /* Initialize the pointer to the field diagnostic structure */
        p_fd = (T_FD_PARAM *) ( ((USIGN32) p_block_desc->p_block) + p_param_desc->par_offset);

        ffbl_fd_map[FD_FAIL]        = &p_fd->fd_fail_map;
        ffbl_fd_map[FD_OFFSPEC]     = &p_fd->fd_offspec_map;
        ffbl_fd_map[FD_MAINT]       = &p_fd->fd_maint_map;
        ffbl_fd_map[FD_CHECK]       = &p_fd->fd_check_map;

        ffbl_fd_active[FD_FAIL]     = &p_fd->fd_fail_active;
        ffbl_fd_active[FD_OFFSPEC]  = &p_fd->fd_offspec_active;
        ffbl_fd_active[FD_MAINT]    = &p_fd->fd_maint_active;
        ffbl_fd_active[FD_CHECK]    = &p_fd->fd_check_active;

        ffbl_fd_mask[FD_FAIL]       = &p_fd->fd_fail_mask;
        ffbl_fd_mask[FD_OFFSPEC]    = &p_fd->fd_offspec_mask;
        ffbl_fd_mask[FD_MAINT]      = &p_fd->fd_maint_mask;
        ffbl_fd_mask[FD_CHECK]      = &p_fd->fd_check_mask;

        ffbl_fd_alm[FD_FAIL]        = &p_fd->fd_fail_alm;
        ffbl_fd_alm[FD_OFFSPEC]     = &p_fd->fd_offspec_alm;
        ffbl_fd_alm[FD_MAINT]       = &p_fd->fd_maint_alm;
        ffbl_fd_alm[FD_CHECK]       = &p_fd->fd_check_alm;

        ffbl_fd_pri[FD_FAIL]        = &p_fd->fd_fail_pri;
        ffbl_fd_pri[FD_OFFSPEC]     = &p_fd->fd_offspec_pri;
        ffbl_fd_pri[FD_MAINT]       = &p_fd->fd_maint_pri;
        ffbl_fd_pri[FD_CHECK]       = &p_fd->fd_check_pri;
    }
    osif_enable_all_tasks();
#if AK_CONSTIZE==2
    MN_ASSERT(ffbl_fd_start_idx == ffbl_fd_start_idx_c);
    for(USIGN32 n=0; n<NO_OF_FD_ALARMS; n++)
    {
        MN_ASSERT(ffbl_fd_map[n] == ffbl_fd_map_c[n]);
        MN_ASSERT(ffbl_fd_active[n] == ffbl_fd_active_c[n]);
        MN_ASSERT(ffbl_fd_mask[n] == ffbl_fd_mask_c[n]);
        MN_ASSERT(ffbl_fd_alm[n] == ffbl_fd_alm_c[n]);
        MN_ASSERT(ffbl_fd_pri[n] == ffbl_fd_pri_c[n]);
    }
#endif //AK_CONSTIZE==2
#endif //AK_CONSTIZE!=1
}






FUNCTION GLOBAL VOID ffbl_load_fdiag_sources
  (
    IN USIGN16 const *   fdiag_sources
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  Field diagnostics alerts have got an element ‘Source Block Index’.
  ‘Source Block Index’ is the OD start index of the block that triggered the
  alert; it is zero if the alert does not relate to a certain block.

  This function allows the application to provide an array of 32 ‘Source Block
  Indexes’ for 32 field diagnostics conditions. The first element of the array
  relates to field diagnostics condition 0; the last element of the array
  relates to field diagnostics condition 31.

  The application must not call this function before fbs_start() has been
  executed.

  The Restart-with-defaults command reset the internal FFBL array of ‘Source
  Block Indexes’ to zero. After Restart-with-defaults the application has to
  re-load an array with 32 ‘Source Block Indexes’.

  The application is allowed to call this function more than one time. The FFBL
  component will always work with a copy of the newest array.

  The call of this function is optional. If the application does not call this
  function the FFBL component will use zero as ‘Source Block Index’ for all
  field diagnostics conditions.

PARAMETERS
  fdiag_sources   Pointer to an array of 32 ‘Source Block Indexes’.
                  The FFBL component works with an internal copy of the ‘Source
                  Block Index’ array. When this function returns the calling
                  function may free the buffer where fdiag_sources points to.
RETURN
  None

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    osif_disable_all_tasks();
    Struct_Test(FdAlarmSrc_t, &FdAlarmSrc);
    memcpy (FdAlarmSrc.ffbl_fd_alarm_source, fdiag_sources, sizeof(FdAlarmSrc.ffbl_fd_alarm_source));
    CONST_ASSERT(32*sizeof(USIGN16) == sizeof(FdAlarmSrc.ffbl_fd_alarm_source)); //sanity check; can be removed
    STRUCT_CLOSE(FdAlarmSrc_t, &FdAlarmSrc);
    osif_enable_all_tasks();

  return ;
}







FUNCTION PUBLIC VOID ffbl_fd_reset_simulate (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function resets the Field Diagnostics simulation.

PARAMETERS


RETURN

  none

----------------------------------------------------------------------------*/
{
#if AK_CONSTIZE==1
    resb_1.fd_simulate.enable = SIMULATION_DISABLED;
#endif
#if AK_CONSTIZE==0
LOCAL_VARIABLES

FUNCTION_BODY

  if (p_fd != NULL)
  {
    p_fd->fd_simulate.enable = SIMULATION_DISABLED;
  }

  return;
#endif
}


#if AK_CONSTIZE==1
#define PFD (&resb_1)
#else
#define PFD (p_fd)
#endif


/*lint -esym(457, resb_1) -esym(458, resb_1)
Atomicity of FB data is a battle of the future
*/

FUNCTION PUBLIC VOID ffbl_fd_background (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION


PARAMETERS


RETURN

  none

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8    i;
  BOOL      simulation_active;
  USIGN32   field_diagnostic_value;
  USIGN32   recomm_act_bitstring;

FUNCTION_BODY

#if AK_CONSTIZE==0
  /* Check if the resource block has got FD parameters -------------------- */
  if (p_fd == NULL)
  {
    return;
  }
#endif

  _ASSERT (ffbl_call_fdev_funct.a_of_fd_get_diag_value != NULL);
  _ASSERT (ffbl_call_fdev_funct.a_of_fd_get_recomm_act != NULL);

  /*Fix of TTP947
    FF-912: 2.11 "Field Diagnostic conditions are not evaluated if the target mode of the Resource block is Out-of-Service."*/
  if (p_resource->mode_blk.target != MODE_OS)
  {
      PFD->fd_simulate.diagnostic_value = ffbl_call_fdev_funct.a_of_fd_get_diag_value();

    if (PFD->fd_simulate.enable == SIMULATION_ENABLED)
    {
      field_diagnostic_value = PFD->fd_simulate.diagnostic_simulate_value;

      simulation_active = TRUE;
    }
    else
    {
      field_diagnostic_value = PFD->fd_simulate.diagnostic_value;
      PFD->fd_simulate.diagnostic_simulate_value = field_diagnostic_value;

      simulation_active = FALSE;
    }

    /* Update recommended action -------------------------------------------- */
    MN_ENTER_CRITICAL();
        recomm_act_bitstring  = *ffbl_fd_map[0] | *ffbl_fd_map[1] |
                            *ffbl_fd_map[2] | *ffbl_fd_map[3];
    MN_EXIT_CRITICAL();

    recomm_act_bitstring &=  field_diagnostic_value;

    PFD->fd_recommen_act = ffbl_call_fdev_funct.a_of_fd_get_recomm_act
                                (recomm_act_bitstring,simulation_active);
  }
  else /* FF-912: 2.11 "... Therefore the FD_SIMULATE Values have to be 0 if the resource block is OOS".*/
  {
    PFD->fd_simulate.diagnostic_value = 0;
    PFD->fd_simulate.diagnostic_simulate_value = 0;
    field_diagnostic_value = 0;
  }


  for (i = 0; i < NO_OF_FD_ALARMS; i++)
  {
    ffbl_fd_update_fd_alarm (i, field_diagnostic_value);
  }

  return;
}


/*lint -esym(458, ffbl_fd_update_fd_alarm)
Lint (as of 9.00h) gets it all wrong with FdAlarmBits and FdAlarmSrc.
Thread safety of this function must be reviewed manually
*/
FUNCTION LOCAL VOID ffbl_fd_update_fd_alarm
  (
    IN USIGN16        fd_idx,
    IN USIGN32        field_diagnostic_value
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

PARAMETERS

RETURN

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  INT16                 i;
  USIGN32               current_alarm_bits;
  USIGN32               alarm_occur_bits;
  USIGN32               alarm_clear_bits;
  T_FBS_ALERT_NOTIFY    alert_desc;
FUNCTION_BODY

    Struct_Test(FdAlarmBits_t, &FdAlarmBits);
    Struct_Test(FdAlarmSrc_t, &FdAlarmSrc);
  osif_disable_all_tasks();

    /* AK NOTE:
    *ffbl_fd_active[fd_idx]
    ffbl_fd_alm[fd_idx]->...
    are actually in RB and can't be protected
    with a checksum until we take on all function blocks wholesale
    */
  /* Calculate the currently active alarms -------------------------------- */
  *ffbl_fd_active[fd_idx]  = field_diagnostic_value & *ffbl_fd_map[fd_idx];

  /* Calculate the currently active and enabled alarms -------------------- */
  current_alarm_bits = *ffbl_fd_active[fd_idx] & ~(*ffbl_fd_mask[fd_idx]);

  /* Check if the FD alarm is enabled ------------------------------------- */
  USIGN32 almask = FdAlarmBits.ffbl_fd_alarm_bits[fd_idx];
  if (!(p_resource->alarm_sum.disable & (ALARM_SUM_FD_FAIL >> fd_idx)))
  {
    alarm_occur_bits =  current_alarm_bits & ~almask;
    alarm_clear_bits = ~current_alarm_bits & almask;

    if ((p_resource->ack_option & (ALARM_SUM_FD_FAIL >> fd_idx))) /* Auto ack. enabled */
    {
      if (ffbl_fd_alm[fd_idx]->unack == ALARM_UNACKED)
      {
        ffbl_fd_alm[fd_idx]->unack = ALARM_ACKED;
      }
    }
  }
  else /* FD alarm is disabled -------------------------------------------- */
  {
    alarm_occur_bits = 0x00000000UL;
    alarm_clear_bits = FdAlarmBits.ffbl_fd_alarm_bits[fd_idx];

    if (ffbl_fd_alm[fd_idx]->state)
    {
      ffbl_fd_alm[fd_idx]->unack = ALARM_ACKED;
    }
  }

  /* Clear all alarms if the resource block is out-of-service ------------- */
  /* Fix of TTP947 - FF-912: "2.11 ... All alarms are cleared when the target mode is Out-of-Service." */
  if ( (p_resource->mode_blk.actual == MODE_OS) || (p_resource->mode_blk.target == MODE_OS) )
  {
    alarm_occur_bits = 0x00000000UL;
    alarm_clear_bits = FdAlarmBits.ffbl_fd_alarm_bits[fd_idx];

    current_alarm_bits = 0x00000000UL;
  }

  storeMemberInt(&FdAlarmBits, ffbl_fd_alarm_bits[fd_idx], current_alarm_bits);


  osif_enable_all_tasks();


  if (!alarm_occur_bits && !alarm_clear_bits)
  {
    return;
  }

  alert_desc.block_id    = 0; /* ID of resource block */
  alert_desc.rel_idx     = ffbl_fd_start_idx + FD_PAR_FAIL_ALM + fd_idx;
  alert_desc.priority    = *(ffbl_fd_pri[fd_idx]);

  /* Encode alarm subcode ------------------------------------------------- */
  alert_desc.data.fld.subcode = 0x00000000UL;

  for (i = 0; i < 32; i++)
  {
    if (current_alarm_bits & (0x80000000UL >> i))
    {
      alert_desc.data.fld.subcode  |= (0x00000001UL << i);
    }
  }

  /* Send alert description with alarm clear */
  if (alarm_clear_bits)
  {
    USIGN32 single_clear_bit;

    alert_desc.action = ALARM_CLEAR;

    for (i = 31; i >= 0; i--)
    {
      single_clear_bit = (alarm_clear_bits & (0x80000000 >> i));

      if (single_clear_bit)
      {
        alert_desc.data.fld.mbit_mask = single_clear_bit;
        alert_desc.data.fld.value     = i;
        alert_desc.data.fld.alarm_src = FdAlarmSrc.ffbl_fd_alarm_source[i];

        fbs_alert_notify(&alert_desc);
      }
    }
  }

  if (alarm_occur_bits)
  {
    USIGN32 single_active_bit;

    alert_desc.action = ALARM_ACTIVE;

    for (i = 31; i >= 0; i--)
    {
      single_active_bit = (alarm_occur_bits & (0x80000000 >> i));

      if (single_active_bit)
      {
        alert_desc.data.fld.mbit_mask = single_active_bit;
        alert_desc.data.fld.value     = i;
        alert_desc.data.fld.alarm_src = FdAlarmSrc.ffbl_fd_alarm_source[i];

        fbs_alert_notify(&alert_desc);
      }
    }
  }

  return;
}





FUNCTION PUBLIC USIGN16 ffbl_fd_pre_write_check
  (
    IN T_FBIF_WRITE_DATA *        p_write
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

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

  switch (p_write->rel_idx - ffbl_fd_start_idx)
  {
    case FD_PAR_FAIL_PRI:
    case FD_PAR_OFFSPEC_PRI:
    case FD_PAR_MAINT_PRI:
    case FD_PAR_CHECK_PRI:
    {
      if (*source > WRITE_PRI_MAX)
      {
        result = E_FB_PARA_LIMIT;
      }

      break;
    }

    case FD_PAR_FAIL_ALM:
    {
      result = ffbl_check_unack_flag (&PFD->fd_fail_alm.unack, source, subindex);

      break;
    }

    case FD_PAR_OFFSPEC_ALM:
    {
      result = ffbl_check_unack_flag (&PFD->fd_offspec_alm.unack, source, subindex);

      break;
    }

    case FD_PAR_MAINT_ALM:
    {
      result = ffbl_check_unack_flag (&PFD->fd_maint_alm.unack, source, subindex);

      break;
    }

    case FD_PAR_CHECK_ALM:
    {
      result = ffbl_check_unack_flag (&PFD->fd_check_alm.unack, source, subindex);

      break;
    }

    case FD_PAR_SIMULATE:
    {
      USIGN8 enable_flag;

      if      (subindex == 0) enable_flag = ((SIMULATE_FD *)source)->enable;
      else if (subindex == 3) enable_flag = *source;
      else                    break;

      if (ffbl_bas_check_sim_param (enable_flag) == E_FB_PARA_CHECK)
        return (E_FB_PARA_CHECK);

      break;
    }

    default:
    {
      ;
    }
  }

  return result;
}






FUNCTION PUBLIC VOID ffbl_fd_update_alarm_sum
  (
    INOUT ALARM_SUMMARY *  p_alarm_sum
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8    i;
  USIGN16   fd_current;
  USIGN16   fd_unrep;
  USIGN16   fd_unack;

FUNCTION_BODY

  fd_current = 0;
  fd_unrep   = 0;
  fd_unack   = 0;

  osif_disable_all_tasks();

  for (i = 0; i < NO_OF_FD_ALARMS; i++)
  {
    if (FdAlarmBits.ffbl_fd_alarm_bits[i])
    {
      fd_current |= (ALARM_SUM_FD_FAIL >> i);
    }

    if (_ALARM_NOT_REPORTED(ffbl_fd_alm[i]->state))
    {
      fd_unrep |= (ALARM_SUM_FD_FAIL >> i);
    }

    if (_ALARM_NOT_ACKNOWLEDGED(ffbl_fd_alm[i]->unack))
    {
      fd_unack |= (ALARM_SUM_FD_FAIL >> i);
    }
  }

  p_alarm_sum->current  |= fd_current;
  p_alarm_sum->unrep    |= fd_unrep;
  p_alarm_sum->unack    |= fd_unack;

  osif_enable_all_tasks();

  return;
}
