/*
** @(#)dc_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Device Control block
** Filename: dc_block.ddl
** Spec revision:       FF-900 FS 1.0 DDL spec
**                      FF-892 FS 1.5 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
** Date of last change: 2005-11-09
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
** (c) Fieldbus Foundation(TM) (1994-2005)
**
*/

/*
** HISTORY:
** DBG   Revision 1.0  20020523
** FI    Revision 1.1  20051109
**       added block specific status options per AR#708
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
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
** Device Control block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DEVICE_CONTROL,
DEVICE_REVISION __DEVICE_CONTROL_rel_dev_rev,
DD_REVISION     __DEVICE_CONTROL_rel_dd_rev
/*
**********************************************************************
** Device Control
** Definition of Device Control Block
**********************************************************************
*/
BLOCK   __device_control
{
        CHARACTERISTICS __dc_character ;
        LABEL                              [device_control_block] ;
        HELP                               [device_control_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV_D,                       __pv_d ;
            SP_D,                       __sp_d ;
            OUT_D,                      __out_d ;
            OUT_STATE,                  __out_state ;
            GRANT_DENY,                 __grant_deny ;
            DEVICE_OPTS,                __device_opts ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_dc ;
            #endif
            IN_D,                       __in_d ;
            #ifdef LIB2
            ACK_OPTION,                 __ack_option ;
            #else
            ACK_OPTION,                 __ack_option_dc ;
            #endif
            FAIL_PRI,                   __fail_pri ;
            ACCEPT_PRI,                 __accept_pri ;
            IGNORE_PRI,                 __ignore_pri ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            FAIL_ALM,                   __fail_alm ;
            ACCEPT_ALM,                 __accept_alm ;
            IGNORE_ALM,                 __ignore_alm ;
            SHUTDOWN_D,                 __shutdown_d ;
            INTERLOCK_D,                __interlock_d ;
            PERMISSIVE_D,               __permissive_d ;
            RESET_D,                    __reset_d ;
            ACCEPT_D,                   __accept_d ;
            DC_STATE,                   __dc_state ;
            TRAVEL_TIMER,               __travel_timer ;
            CFM_PASS_TIME,              __cfm_pass_time ;
            CFM_ACT1_TIME,              __cfm_act1_time ;
            TRIP_TIME,                  __trip_time ;
            IGNORE,                     __ignore ;
            FAIL,                       __fail ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            #else
            ALARM_SUM,                  __alarm_sum_dc ;
            #endif
            BKCAL_IN_D,                 __bkcal_in_d ;
            TRK_IN_D,                   __trk_in_d ;
            CAS_IN_D,                   __cas_in_d ;
            BKCAL_OUT_D,                __bkcal_out_d ;
            RCAS_IN_D,                  __rcas_in_d ;
            RCAS_OUT_D,                 __rcas_out_d ;
            SHED_OPT,                   __shed_opt ;
            CRACK_TIMER,                __crack_timer ;
            DELAY_TIMER,                __delay_timer ;
            CFM_ACT2_TIME,              __cfm_act2_time ;
            CRACK_TIME,                 __crack_time ;
            DELAY_TIME,                 __delay_time ;
            RESTART_TIME,               __restart_time ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __dc_view_1 ;
            VIEW_2, __dc_view_2 ;
            VIEW_3, __dc_view_3 ;
            VIEW_4, __dc_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_dc
		,upload_wanted_dc
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __dc_character
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
VARIABLE_LIST   __dc_view_1
{
        LABEL           [dc_view_1] ;
        HELP            [dc_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_SP_D,                         PARAM.SP_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_SHUTDOWN_D,                   PARAM.SHUTDOWN_D ;
            VL_INTERLOCK_D,                  PARAM.INTERLOCK_D ;
            VL_PERMISSIVE_D,                 PARAM.PERMISSIVE_D ;
            VL_RESET_D,                      PARAM.RESET_D ;
            VL_ACCEPT_D,                     PARAM.ACCEPT_D ;
            VL_DC_STATE,                     PARAM.DC_STATE ;
            VL_IGNORE,                       PARAM.IGNORE ;
            VL_FAIL,                         PARAM.FAIL ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
            VL_TRK_IN_D,                     PARAM.TRK_IN_D ;
            VL_CAS_IN_D,                     PARAM.CAS_IN_D ;
        }
}

VARIABLE_LIST   __dc_view_2
{
        LABEL           [dc_view_2] ;
        HELP            [dc_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_STATE,                    PARAM.OUT_STATE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __dc_view_3
{
        LABEL           [dc_view_3] ;
        HELP            [dc_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_SP_D,                         PARAM.SP_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_IN_D,                         PARAM.IN_D ;
            VL_SHUTDOWN_D,                   PARAM.SHUTDOWN_D ;
            VL_INTERLOCK_D,                  PARAM.INTERLOCK_D ;
            VL_PERMISSIVE_D,                 PARAM.PERMISSIVE_D ;
            VL_RESET_D,                      PARAM.RESET_D ;
            VL_ACCEPT_D,                     PARAM.ACCEPT_D ;
            VL_DC_STATE,                     PARAM.DC_STATE ;
            VL_TRAVEL_TIMER,                 PARAM.TRAVEL_TIMER ;
            VL_IGNORE,                       PARAM.IGNORE ;
            VL_FAIL,                         PARAM.FAIL ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
            VL_BKCAL_IN_D,                   PARAM.BKCAL_IN_D ;
            VL_TRK_IN_D,                     PARAM.TRK_IN_D ;
            VL_CAS_IN_D,                     PARAM.CAS_IN_D ;
            VL_BKCAL_OUT_D,                  PARAM.BKCAL_OUT_D ;
            VL_RCAS_IN_D,                    PARAM.RCAS_IN_D ;
            VL_RCAS_OUT_D,                   PARAM.RCAS_OUT_D ;
            VL_CRACK_TIMER,                  PARAM.CRACK_TIMER ;
            VL_DELAY_TIMER,                  PARAM.DELAY_TIMER ;
        }
}

VARIABLE_LIST   __dc_view_4
{
        LABEL           [dc_view_4] ;
        HELP            [dc_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_DEVICE_OPTS,                  PARAM.DEVICE_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_ACK_OPTION,                   PARAM.ACK_OPTION ;
            VL_FAIL_PRI,                     PARAM.FAIL_PRI ;
            VL_ACCEPT_PRI,                   PARAM.ACCEPT_PRI ;
            VL_IGNORE_PRI,                   PARAM.IGNORE_PRI ;
            VL_CFM_PASS_TIME,                PARAM.CFM_PASS_TIME ;
            VL_CFM_ACT1_TIME,                PARAM.CFM_ACT1_TIME ;
            VL_TRIP_TIME,                    PARAM.TRIP_TIME ;
            VL_SHED_OPT,                     PARAM.SHED_OPT ;
            VL_CFM_ACT2_TIME,                PARAM.CFM_ACT2_TIME ;
            VL_CRACK_TIME,                   PARAM.CRACK_TIME ;
            VL_DELAY_TIME,                   PARAM.DELAY_TIME ;
            VL_RESTART_TIME,                 PARAM.RESTART_TIME ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/

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
COLLECTION no_download_dc
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_dc
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
