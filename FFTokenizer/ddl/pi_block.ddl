/*
** @(#)pi_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Pulse Input block
** Filename: pi_block.ddl
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
** Pulse Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __PULSE_INPUT,
DEVICE_REVISION __PULSE_INPUT_beta_dev_rev,
DD_REVISION     __PULSE_INPUT_beta_dd_rev
/*
**********************************************************************
** Pulse Input
** Definition of Pulse Input Block
**********************************************************************
*/
BLOCK   __pulse_input
{
        CHARACTERISTICS __pi_character ;
        LABEL                              [pulse_input_block] ;
        HELP                               [pulse_input_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV,                         __pv ;
            OUT,                        __out ;
            OUT_ACCUM,                  __out_accum ;
            SIMULATE_P,                 __simulate_p ;
            PULSE_VAL,                  __pulse_val ;
            TIME_UNITS,                 __time_units ;
            OUT_SCALE,                  __out_scale ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            IO_OPTS,                    __io_opts ;
            STATUS_OPTS,                __status_opts ;
            #else
            IO_OPTS,                    __io_opts_pi ;
            STATUS_OPTS,                __status_opts_pi ;
            #endif
            CHANNEL,                    __channel ;
            PV_FTIME,                   __pv_ftime ;
            FIELD_VAL,                  __field_val ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            ACK_OPTION,                 __ack_option ;
            #else
            ALARM_SUM,                  __alarm_sum_pi ;
            ACK_OPTION,                 __ack_option_pi ;
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
            HI_HI_ALM,                  __hi_hi_alm ;
            HI_ALM,                     __hi_alm ;
            LO_ALM,                     __lo_alm ;
            LO_LO_ALM,                  __lo_lo_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __pi_view_1 ;
            VIEW_2, __pi_view_2 ;
            VIEW_3, __pi_view_3 ;
            VIEW_4, __pi_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_pi_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_pi
		,upload_wanted_pi
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __pi_character
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
VARIABLE_LIST   __pi_view_1
{
        LABEL           [pi_view_1] ;
        HELP            [pi_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_OUT_ACCUM,                    PARAM.OUT_ACCUM ;
            VL_FIELD_VAL,                    PARAM.FIELD_VAL ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __pi_view_2
{
        LABEL           [pi_view_2] ;
        HELP            [pi_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_SCALE,                    PARAM.OUT_SCALE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __pi_view_3
{
        LABEL           [pi_view_3] ;
        HELP            [pi_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_OUT_ACCUM,                    PARAM.OUT_ACCUM ;
            VL_FIELD_VAL,                    PARAM.FIELD_VAL ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __pi_view_4
{
        LABEL           [pi_view_4] ;
        HELP            [pi_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_PULSE_VAL,                    PARAM.PULSE_VAL ;
            VL_TIME_UNITS,                   PARAM.TIME_UNITS ;
            VL_IO_OPTS,                      PARAM.IO_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_CHANNEL,                      PARAM.CHANNEL ;
            VL_PV_FTIME,                     PARAM.PV_FTIME ;
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
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_pi_out {
    PARAM.OUT_SCALE.UNITS_INDEX : PARAM.OUT.VALUE,
            PARAM.OUT_ACCUM.VALUE
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
COLLECTION no_download_pi
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_pi
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
