/*
** @(#)ai_block.ddl     1.1 1999-03-04
**
** FF standard Analog Input block
** Filename: ai_block.ddl
** Spec revision:       FF-900 FS 1.0  DDL spec
**                FF-890 FS 1.0 FBAP spec part 1
**                FF-891 FS 1.0 FBAP spec part 2
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
** JPH   Revision 0.9  19950515
** TAB   Revision 1.0  19961015
** DAD   Revision 1.1  1999-03-04
**         set new rel numbering system for dev rev and dd rev
** FI    Revision 1.2  20051109
**         added block specific status options per AR#708
**         added block specific io options per AR#708
**         added block specific alarm summary per AR#697
**         added block specific ack option per AR#1349
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
** Analog Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __AI_BLOCK,
DEVICE_REVISION __AI_BLOCK_rel_dev_rev,
DD_REVISION     __AI_BLOCK_rel_dd_rev
/*
**********************************************************************
** Analog Input
** Definition of an analog input block
**********************************************************************
*/
BLOCK   __analog_input_block
{
        CHARACTERISTICS __ai_character ;
        LABEL                              [analog_input_block] ;
        HELP                               [analog_input_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
                PV,                     __pv ;
                OUT,                    __out ;
                SIMULATE,               __simulate_float ;
                XD_SCALE,               __xd_scale ;
                OUT_SCALE,              __out_scale ;
                GRANT_DENY,             __grant_deny ;
                #ifdef LIB2
                IO_OPTS,                __io_opts ;
                STATUS_OPTS,    	__status_opts ;
                #else
                IO_OPTS,                __io_opts_ai ;
                STATUS_OPTS,    	__status_opts_ai ;
                #endif
                CHANNEL,                __channel ;
                L_TYPE,                 __l_type ;
                LOW_CUT,                __low_cut ;
                PV_FTIME,               __pv_ftime ;
                FIELD_VAL,              __field_val ;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
                #ifdef LIB2
                ALARM_SUM,              __alarm_sum ;
                ACK_OPTION,             __ack_option ;
                #else
                ALARM_SUM,              __alarm_sum_ai ;
                ACK_OPTION,             __ack_option_ai ;
                #endif
                ALARM_HYS,              __alarm_hys ;
                HI_HI_PRI,              __hi_hi_pri ;
                HI_HI_LIM,              __hi_hi_lim ;
                HI_PRI,                 __hi_pri ;
                HI_LIM,                 __hi_lim ;
                LO_PRI,                 __lo_pri ;
                LO_LIM,                 __lo_lim ;
                LO_LO_PRI,              __lo_lo_pri ;
                LO_LO_LIM,              __lo_lo_lim ;
                HI_HI_ALM,              __hi_hi_alm ;
                HI_ALM,                 __hi_alm ;
                LO_ALM,                 __lo_alm ;
                LO_LO_ALM,              __lo_lo_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __ai_view_1 ;
                VIEW_2, __ai_view_2 ;
                VIEW_3, __ai_view_3 ;
                VIEW_4, __ai_view_4 ;
        }
        UNIT_ITEMS
        {
                __unit_ai_xd,
                __unit_ai_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_ai
		,upload_wanted_ai
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ai_character
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
VARIABLE_LIST   __ai_view_1
{
        LABEL           [ai_view_1] ;
        HELP            [ai_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,                  PARAM.PV ;
                VL_OUT,                 PARAM.OUT ;
                VL_FIELD_VAL,   PARAM.FIELD_VAL ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __ai_view_2
{
        LABEL           [ai_view_2] ;
        HELP            [ai_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_XD_SCALE,    PARAM.XD_SCALE ;
                VL_OUT_SCALE,   PARAM.OUT_SCALE ;
                VL_GRANT_DENY,  PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __ai_view_3
{
        LABEL           [ai_view_3] ;
        HELP            [ai_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,                  PARAM.PV ;
                VL_OUT,                 PARAM.OUT ;
                VL_FIELD_VAL,   PARAM.FIELD_VAL ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __ai_view_4
{
        LABEL           [ai_view_4] ;
        HELP            [ai_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
                VL_IO_OPTS,             PARAM.IO_OPTS ;
                VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
                VL_CHANNEL,             PARAM.CHANNEL ;
                VL_L_TYPE,              PARAM.L_TYPE ;
                VL_LOW_CUT,             PARAM.LOW_CUT ;
                VL_PV_FTIME,    PARAM.PV_FTIME ;
                VL_ACK_OPTION,  PARAM.ACK_OPTION ;
                VL_ALARM_HYS,   PARAM.ALARM_HYS ;
                VL_HI_HI_PRI,   PARAM.HI_HI_PRI ;
                VL_HI_HI_LIM,   PARAM.HI_HI_LIM ;
                VL_HI_PRI,              PARAM.HI_PRI ;
                VL_HI_LIM,              PARAM.HI_LIM ;
                VL_LO_PRI,              PARAM.LO_PRI ;
                VL_LO_LIM,              PARAM.LO_LIM ;
                VL_LO_LO_PRI,   PARAM.LO_LO_PRI ;
                VL_LO_LO_LIM,   PARAM.LO_LO_LIM ;
        }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/*
** NOTE:
** In the implementation of the AI Block, PV and OUT always
** have identical scaling.  OUT_SCALE provides scaling for
** PV.
*/
UNIT    __unit_ai_xd
{
        PARAM.XD_SCALE.UNITS_INDEX :
           PARAM.SIMULATE.TRANSDUCER_VALUE,
           PARAM.SIMULATE.SIMULATE_VALUE
                PARAM.XD_SCALE.EU_100,
                PARAM.XD_SCALE.EU_0
}
UNIT    __unit_ai_out
{
        PARAM.OUT_SCALE.UNITS_INDEX :
                PARAM.OUT.VALUE,
                PARAM.OUT_SCALE.EU_100,
                PARAM.OUT_SCALE.EU_0,
                PARAM.LOW_CUT
                PARAM.PV.VALUE,
                PARAM.HI_HI_LIM,
                PARAM.HI_LIM,
                PARAM.LO_LIM,
                PARAM.LO_LO_LIM,
                PARAM.HI_HI_ALM.VALUE,
                PARAM.HI_ALM.VALUE,
                PARAM.LO_ALM.VALUE,
                PARAM.LO_LO_ALM.VALUE
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
COLLECTION no_download_ai
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ai
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
