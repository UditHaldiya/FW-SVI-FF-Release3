/*
** @(#)spid_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Step Output PID block
** Filename: spid_block.ddl
** Spec revision:       FF-900 FS 5.0 DDL spec
**                      FF-892 FS 1.7 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
** Date of last change: 2006-05-16
** Description:
**
**
** DISCLAIMER OF WARRANTIES
**
** THIS DOCUMENT IS PROVIDED ON AN "AS IS" BASIS AND MAY BE SUBJECT TO FUTURE
** ADDITIONS, MODIFICATIONS, OR CORRECTIONS DEPENDING ON THE RESULTS OF FIELD
** TRIAL TESTING.  THE FIELDBUS FOUNDATION(TM) HEREBY DISCLAIMS ALL WARRANTIES
** OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING ANY WARRANTY OF MERCHANTABILITY
** OR FITNESS FOR A PARTICULAR PURPOSE, FOR THIS DOCUMENT.  IN NO EVENT WILL
** THE FIELDBUS FOUNDATION(TM) BE RESPONSIBLE FOR ANY LOSS OR DAMAGE ARISING
** OUT OF OR RESULTING FROM ANY DEFECT, ERROR OR OMISSION IN THIS DOCUMENT OR
** FROM ANYONE'S USE OF OR RELIANCE ON THIS DOCUMENT.
** DISCLAIMER OF WARRANTIES
**
** (c) Fieldbus Foundation(TM) (1994-2006)
**
*/

/*
** HISTORY:
** DBG   Revision 1.0  20020523
** FI    Revision 1.1  20051109
**       added block specific status options per AR#708
**       added block specific control options per AR#708
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
**       added block specific io options per AR#708
** MS	 modified unit relations to resolve to correct attribute per AR#1991
** MS	 made changes per AR2351 using LIB2 macro def during tok 2007-07-17
** MS   ARs 2901 -- 2008.10.07
*/
/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Step Output PID block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __STEP_OUTPUT_PID,
DEVICE_REVISION __STEP_OUTPUT_PID_beta_dev_rev,
DD_REVISION     __STEP_OUTPUT_PID_beta_dd_rev
/*
**********************************************************************
** Step Output PID
** Definition of Step Output PID Block
**********************************************************************
*/
BLOCK   __step_output_pid
{
        CHARACTERISTICS __spid_character ;
        LABEL                              [step_output_pid_block] ;
        HELP                               [step_output_pid_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV,                         __pv ;
            SP,                         __sp ;
            OUT_D,                      __out_d ;
            PV_SCALE,                   __pv_scale ;
            XD_STATE,                   __xd_state ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            CONTROL_OPTS,               __control_opts ;
            STATUS_OPTS,                __status_opts ;
            #else
            CONTROL_OPTS,               __control_opts_spid ;
            STATUS_OPTS,                __status_opts_spid ;
            #endif
            IN,                         __in ;
            PV_FTIME,                   __pv_ftime ;
            JOG_TIME,                   __jog_time ;
            CAS_IN,                     __cas_in ;
            SP_RATE_DN,                 __sp_rate_dn ;
            SP_RATE_UP,                 __sp_rate_up ;
            SP_HI_LIM,                  __sp_hi_lim ;
            SP_LO_LIM,                  __sp_lo_lim ;
            GAIN,                       __gain ;
            RESET,                      __reset ;
            BAL_TIME,                   __bal_time ;
            RATE,                       __rate ;
            #ifdef LIB2
            IO_OPTS,                    __io_opts ;
            #else
            IO_OPTS,                    __io_opts_spid ;
            #endif
            CHANNEL,                    __channel ;
            FSAFE_TIME,                 __fsafe_time ;
            FSAFE_VAL_D,                __fsafe_val_d ;
            BKCAL_OUT,                  __bkcal_out ;
            RCAS_IN,                    __rcas_in ;
            SHED_OPT,                   __shed_opt ;
            RCAS_OUT,                   __rcas_out ;
            TRAVEL_TIME,                __travel_time ;
            PULSE_DUR,                  __pulse_dur ;
            DEAD_BAND,                  __dead_band ;
            HYSTERESIS,                 __hysteresis ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            ACK_OPTION,                 __ack_option ;
            #else
            ALARM_SUM,                  __alarm_sum_spid ;
            ACK_OPTION,                 __ack_option_spid ;
            #endif
            ALARM_HYS,                  __alarm_hys ;
            HI_HI_PRI,                  __hi_hi_pri ;
            HI_HI_LIM,                  __hi_hi_lim ;
            HI_PRI,                     __hi_pri ;
            HI_LIM,                     __hi_lim ;
            LO_PRI,                     __lo_pri ;
            LO_LIM,                     __lo_lim ;
            LO_LO_PRI,                  __lo_lo_pri ;
            LO_LO_LIM,                  __lo_lo_lim ;
            DV_HI_PRI,                  __dv_hi_pri ;
            DV_HI_LIM,                  __dv_hi_lim ;
            DV_LO_PRI,                  __dv_lo_pri ;
            DV_LO_LIM,                  __dv_lo_lim ;
            HI_HI_ALM,                  __hi_hi_alm ;
            HI_ALM,                     __hi_alm ;
            LO_ALM,                     __lo_alm ;
            LO_LO_ALM,                  __lo_lo_alm ;
            DV_HI_ALM,                  __dv_hi_alm ;
            DV_LO_ALM,                  __dv_lo_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __spid_view_1 ;
            VIEW_2, __spid_view_2 ;
            VIEW_3, __spid_view_3 ;
            VIEW_4, __spid_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_spid_pv
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_spid
		,upload_wanted_spid
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __spid_character
{
    LABEL           [blk_char] ;
    HELP            [blk_char_help] ;
    MEMBERS
    {
        BLOCK_TAG,          __block_tag ;
        DD_MEMBER,          __dd_member ;
        DD_ITEM,            __dd_item ;
        DD_REVIS,           __dd_revis ;
        PROFILE,            __profile ;
        PROFILE_REVISION,   __profile_revision ;
        EXECUTION_TIME,     __execution_time ;
        EXECUTION_PERIOD,   __execution_period ;
        NUM_OF_PARAMS,      __num_of_params ;
        NEXT_FB_TO_EXECUTE, __next_fb_to_execute ;
        #ifdef HSE
        VIEWS_INDEX,        __views_index32 ;
        #else
        VIEWS_INDEX,        __views_index ;
        #endif
        NUMBER_VIEW_3,      __number_view_3 ;
        NUMBER_VIEW_4,      __number_view_4 ;
    }
}

/*
**********************************************************************
** Variable lists
**********************************************************************
*/
VARIABLE_LIST   __spid_view_1
{
        LABEL           [spid_view_1] ;
        HELP            [spid_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_SP,                           PARAM.SP ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __spid_view_2
{
        LABEL           [spid_view_2] ;
        HELP            [spid_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_PV_SCALE,                     PARAM.PV_SCALE ;
            VL_XD_STATE,                     PARAM.XD_STATE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_SP_HI_LIM,                    PARAM.SP_HI_LIM ;
            VL_SP_LO_LIM,                    PARAM.SP_LO_LIM ;
        }
}

VARIABLE_LIST   __spid_view_3
{
        LABEL           [spid_view_3] ;
        HELP            [spid_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_SP,                           PARAM.SP ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_IN,                           PARAM.IN ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
            VL_BKCAL_OUT,                    PARAM.BKCAL_OUT ;
            VL_RCAS_IN,                      PARAM.RCAS_IN ;
            VL_RCAS_OUT,                     PARAM.RCAS_OUT ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __spid_view_4
{
        LABEL           [spid_view_4] ;
        HELP            [spid_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_CONTROL_OPTS,                 PARAM.CONTROL_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_PV_FTIME,                     PARAM.PV_FTIME ;
            VL_JOG_TIME,                     PARAM.JOG_TIME ;
            VL_SP_RATE_DN,                   PARAM.SP_RATE_DN ;
            VL_SP_RATE_UP,                   PARAM.SP_RATE_UP ;
            VL_GAIN,                         PARAM.GAIN ;
            VL_RESET,                        PARAM.RESET ;
            VL_BAL_TIME,                     PARAM.BAL_TIME ;
            VL_RATE,                         PARAM.RATE ;
            VL_IO_OPTS,                      PARAM.IO_OPTS ;
            VL_CHANNEL,                      PARAM.CHANNEL ;
            VL_FSAFE_TIME,                   PARAM.FSAFE_TIME ;
            VL_FSAFE_VAL_D,                  PARAM.FSAFE_VAL_D ;
            VL_SHED_OPT,                     PARAM.SHED_OPT ;
            VL_TRAVEL_TIME,                  PARAM.TRAVEL_TIME ;
            VL_PULSE_DUR,                    PARAM.PULSE_DUR ;
            VL_DEAD_BAND,                    PARAM.DEAD_BAND ;
            VL_HYSTERESIS,                   PARAM.HYSTERESIS ;
            VL_ACK_OPTION,                   PARAM.ACK_OPTION ;
            VL_ALARM_HYS,                    PARAM.ALARM_HYS ;
            VL_HI_HI_PRI,                    PARAM.HI_HI_PRI ;
            VL_HI_HI_LIM,                    PARAM.HI_HI_LIM ;
            VL_HI_PRI,                       PARAM.HI_PRI ;
            VL_HI_LIM,                       PARAM.HI_LIM ;
            VL_LO_PRI,                       PARAM.LO_PRI ;
            VL_LO_LIM,                       PARAM.LO_LIM ;
            VL_LO_LO_PRI,                    PARAM.LO_LO_PRI ;
            VL_LO_LO_LIM,                    PARAM.LO_LO_LIM ;
            VL_DV_HI_PRI,                    PARAM.DV_HI_PRI ;
            VL_DV_HI_LIM,                    PARAM.DV_HI_LIM ;
            VL_DV_LO_PRI,                    PARAM.DV_LO_PRI ;
            VL_DV_LO_LIM,                    PARAM.DV_LO_LIM ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_spid_pv {
    PARAM.PV_SCALE.UNITS_INDEX : PARAM.PV.VALUE
}

/*
**********************************************************************
** Refresh relations
**********************************************************************
*/

/*
**********************************************************************
** Response codes
**********************************************************************
*/

/*
**********************************************************************
** Write as one relations
**********************************************************************
*/

/*
**********************************************************************
** Edit displays
**********************************************************************
*/

/*
**********************************************************************
** no_download & upload_wanted collections
**********************************************************************
*/
#ifdef UD_LISTS
COLLECTION no_download_spid
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_spid
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
