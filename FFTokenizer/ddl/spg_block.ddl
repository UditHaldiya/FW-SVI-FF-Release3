/*
** @(#)spg_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Setpoint Ramp Generator block
** Filename: spg_block.ddl
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
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
** MS	 commented out UNIT_ITEMS ref. & def. per AR#1991
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
** Setpoint Ramp Generator block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __SETPOINT_RAMP_GENERATOR,
DEVICE_REVISION __SETPOINT_RAMP_GENERATOR_rel_dev_rev,
DD_REVISION     __SETPOINT_RAMP_GENERATOR_rel_dd_rev
/*
**********************************************************************
** Setpoint Ramp Generator
** Definition of Setpoint Ramp Generator Block
**********************************************************************
*/
BLOCK   __setpoint_ramp_generator
{
        CHARACTERISTICS __spg_character ;
        LABEL                              [setpoint_ramp_generator_block] ;
        HELP                               [setpoint_ramp_generator_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            OUT,                        __out ;
            OUT_RANGE,                  __out_range ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_spg ;
            #endif
            START_VAL,                  __start_val ;
            TIME_DURATION,              __time_duration ;
            TIME_UNITS,                 __time_units ;
            BKCAL_IN,                   __bkcal_in ;
            START,                      __start ;
            START_TYPE,                 __start_type ;
            PAUSE,                      __pause ;
            PAUSE_CAUSE,                __pause_cause ;
            AUTO_CYCLE,                 __auto_cycle ;
            STEP_POSN,                  __step_posn ;
            TIME_POSN,                  __time_posn ;
            TIME_POSN_T,                __time_posn_t ;
            OP_CMD_SPG,                 __op_cmd_spg ;
            SPG_STATE,                  __spg_state ;
            PRE_OUT,                    __pre_out ;
            RESET_IN,                   __reset_in ;
            BAL_TIME,                   __bal_time ;
            OUTAGE_LIM,                 __outage_lim ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            ACK_OPTION,                 __ack_option ;
            #else
            ALARM_SUM,                  __alarm_sum_spg ;
            ACK_OPTION,                 __ack_option_spg ;
            #endif
            ALARM_HYS,                  __alarm_hys ;
            DV_HI_PRI,                  __dv_hi_pri ;
            DV_HI_LIM,                  __dv_hi_lim ;
            DV_LO_PRI,                  __dv_lo_pri ;
            DV_LO_LIM,                  __dv_lo_lim ;
            DV_HI_ALM,                  __dv_hi_alm ;
            DV_LO_ALM,                  __dv_lo_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __spg_view_1 ;
            VIEW_2, __spg_view_2 ;
            VIEW_3, __spg_view_3 ;
            VIEW_4, __spg_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_spg_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_spg
		,upload_wanted_spg
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __spg_character
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
VARIABLE_LIST   __spg_view_1
{
        LABEL           [spg_view_1] ;
        HELP            [spg_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_START,                        PARAM.START ;
            VL_PAUSE,                        PARAM.PAUSE ;
            VL_PAUSE_CAUSE,                  PARAM.PAUSE_CAUSE ;
            VL_STEP_POSN,                    PARAM.STEP_POSN ;
            VL_TIME_POSN,                    PARAM.TIME_POSN ;
            VL_TIME_POSN_T,                  PARAM.TIME_POSN_T ;
            VL_OP_CMD_SPG,                   PARAM.OP_CMD_SPG ;
            VL_SPG_STATE,                    PARAM.SPG_STATE ;
            VL_PRE_OUT,                      PARAM.PRE_OUT ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __spg_view_2
{
        LABEL           [spg_view_2] ;
        HELP            [spg_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_START_VAL,                    PARAM.START_VAL ;
            VL_TIME_DURATION,                PARAM.TIME_DURATION ;
            VL_AUTO_CYCLE,                   PARAM.AUTO_CYCLE ;
        }
}

VARIABLE_LIST   __spg_view_3
{
        LABEL           [spg_view_3] ;
        HELP            [spg_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_BKCAL_IN,                     PARAM.BKCAL_IN ;
            VL_START,                        PARAM.START ;
            VL_PAUSE,                        PARAM.PAUSE ;
            VL_PAUSE_CAUSE,                  PARAM.PAUSE_CAUSE ;
            VL_STEP_POSN,                    PARAM.STEP_POSN ;
            VL_TIME_POSN,                    PARAM.TIME_POSN ;
            VL_TIME_POSN_T,                  PARAM.TIME_POSN_T ;
            VL_OP_CMD_SPG,                   PARAM.OP_CMD_SPG ;
            VL_SPG_STATE,                    PARAM.SPG_STATE ;
            VL_PRE_OUT,                      PARAM.PRE_OUT ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __spg_view_4
{
        LABEL           [spg_view_4] ;
        HELP            [spg_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_TIME_UNITS,                   PARAM.TIME_UNITS ;
            VL_START_TYPE,                   PARAM.START_TYPE ;
            VL_BAL_TIME,                     PARAM.BAL_TIME ;
            VL_OUTAGE_LIM,                   PARAM.OUTAGE_LIM ;
            VL_ACK_OPTION,                   PARAM.ACK_OPTION ;
            VL_ALARM_HYS,                    PARAM.ALARM_HYS ;
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
UNIT __unit_spg_out {
    PARAM.OUT_RANGE.UNITS_INDEX : PARAM.OUT.VALUE,
            PARAM.START_VAL,
            PARAM.PAUSE.VALUE,
            PARAM.PRE_OUT.VALUE
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
COLLECTION no_download_spg
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_spg
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
