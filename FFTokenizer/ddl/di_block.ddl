/*
** @(#)di_block.ddl     1.1 1999-03-04
**
** FF standard Discrete Input block
** Filename: di_block.ddl
** Spec revision:       FF-900 FS 5.0  DDL spec
**                FF-890 FS 1.7 FBAP spec part 1
**                FF-891 FS 1.7 FBAP spec part 2
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
** JPH   Revision 0.9  19950515
** TAB   Revision 1.0  19961015
** DAD   Revision 1.1  1999-03-04
**       added new number system for dev rev and dd rev
** FI    Revision 1.2  20051109
**       added block specific status options per AR#708
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
**       added block specific io options per AR#708
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
** Discrete Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DI_BLOCK,
DEVICE_REVISION __DI_BLOCK_rel_dev_rev,
DD_REVISION     __DI_BLOCK_rel_dd_rev

/*
**********************************************************************
** Discrete Input
** Definition of a discrete input block
**********************************************************************
*/
BLOCK   __discrete_input_block
{
        CHARACTERISTICS     __di_character ;
        LABEL                           [discrete_input_block] ;
        HELP                            [discrete_input_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
                PV_D,                   __pv_d ;
                OUT_D,                  __out_d ;
                SIMULATE_D,             __simulate_discrete ;
                XD_STATE,               __xd_state ;
                OUT_STATE,              __out_state ;
                GRANT_DENY,             __grant_deny ;
                #ifdef LIB2
                IO_OPTS,                __io_opts ;
                STATUS_OPTS,    	__status_opts ;
                #else
                IO_OPTS,                __io_opts_di ;
                STATUS_OPTS,    	__status_opts_di ;
                #endif
                CHANNEL,                __channel ;
                PV_FTIME,               __pv_ftime ;
                FIELD_VAL_D,    	__field_val_d ;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
                #ifdef LIB2
                ALARM_SUM,              __alarm_sum ;
                ACK_OPTION,             __ack_option ;
                #else
                ALARM_SUM,              __alarm_sum_di ;
                ACK_OPTION,             __ack_option_di ;
                #endif
                DISC_PRI,               __disc_pri ;
                DISC_LIM,               __disc_lim ;
                DISC_ALM,               __disc_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __di_view_1 ;
                VIEW_2, __di_view_2 ;
                VIEW_3, __di_view_3 ;
                VIEW_4, __di_view_4 ;
        }
        /*UNIT_ITEMS
        {
                __unit_di_xd,
                __unit_di_out
        }*/
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_di
		,upload_wanted_di
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __di_character
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
VARIABLE_LIST   __di_view_1
{
        LABEL           [di_view_1] ;
        HELP            [di_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV_D,                   PARAM.PV_D ;
                VL_OUT_D,               PARAM.OUT_D ;
                VL_FIELD_VAL_D, PARAM.FIELD_VAL_D ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __di_view_2
{
        LABEL           [di_view_2] ;
        HELP            [di_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_XD_STATE,    PARAM.XD_STATE ;
                VL_OUT_STATE,   PARAM.OUT_STATE ;
                VL_GRANT_DENY,  PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __di_view_3
{
        LABEL           [di_view_3] ;
        HELP            [di_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV_D,                   PARAM.PV_D ;
                VL_OUT_D,               PARAM.OUT_D ;
                VL_FIELD_VAL_D, PARAM.FIELD_VAL_D ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __di_view_4
{
        LABEL           [di_view_4] ;
        HELP            [di_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
                VL_IO_OPTS,             PARAM.IO_OPTS ;
                VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
                VL_CHANNEL,             PARAM.CHANNEL ;
                VL_PV_FTIME,    PARAM.PV_FTIME ;
                VL_ACK_OPTION,  PARAM.ACK_OPTION ;
                VL_DISC_PRI,    PARAM.DISC_PRI ;
                VL_DISC_LIM,    PARAM.DISC_LIM ;
        }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/*UNIT    __unit_di_out
{
        PARAM.OUT_STATE:
                PARAM.PV_D.VALUE,
                PARAM.DISC_LIM,
                PARAM.DISC_ALM.VALUE,
                PARAM.OUT_D.VALUE
}

UNIT    __unit_di_xd
{
        PARAM.XD_STATE:
                PARAM.SIMULATE_D.TRANSDUCER_VALUE,
                PARAM.SIMULATE_D.SIMULATE_VALUE
}*/
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
COLLECTION no_download_di
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_di
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
