/*
** @(#)dal_block.ddl    1.0 Thu May 23 10:21:53 2002

**
** FF standard Discrete Alarm block
** Filename: dal_block.ddl
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
** Discrete Alarm block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DISCRETE_ALARM,
DEVICE_REVISION __DISCRETE_ALARM_beta_dev_rev,
DD_REVISION     __DISCRETE_ALARM_beta_dd_rev
/*
**********************************************************************
** Discrete Alarm
** Definition of Discrete Alarm Block
**********************************************************************
*/
BLOCK   __discrete_alarm
{
        CHARACTERISTICS __dal_character ;
        LABEL                              [discrete_alarm_block] ;
        HELP                               [discrete_alarm_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV_D,                       __pv_d ;
            OUT_D,                      __out_d ;
            OUT_STATE,                  __out_state ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_dal ;
            #endif
            IN_D1,                      __in_d1 ;
            IN_D2,                      __in_d2 ;
            IN_D3,                      __in_d3 ;
            IN_D4,                      __in_d4 ;
            INVERT_OPTS,                __invert_opts ;
            COMB_TYPE,                  __comb_type ;
            COND_TYPE,                  __cond_type ;
            COND_TIME,                  __cond_time ;
            PRE_OUT_D,                  __pre_out_d ;
            OUT_ALM,                    __out_alm ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            ACK_OPTION,                 __ack_option ;
            #else
	    	ALARM_SUM,                  __alarm_sum_dal ;
            ACK_OPTION,                 __ack_option_dal ;
            #endif
            ALARM_HYS,                  __alarm_hys ;
            DISC_PRI,                   __disc_pri ;
            DISC_COND,                  __disc_cond ;
            DISC_ALM,                   __disc_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __dal_view_1 ;
            VIEW_2, __dal_view_2 ;
            VIEW_3, __dal_view_3 ;
            VIEW_4, __dal_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_dal
		,upload_wanted_dal
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __dal_character
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
VARIABLE_LIST   __dal_view_1
{
        LABEL           [dal_view_1] ;
        HELP            [dal_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D,                    PARAM.PRE_OUT_D ;
            VL_OUT_ALM,                      PARAM.OUT_ALM ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __dal_view_2
{
        LABEL           [dal_view_2] ;
        HELP            [dal_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_STATE,                    PARAM.OUT_STATE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __dal_view_3
{
        LABEL           [dal_view_3] ;
        HELP            [dal_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D,                    PARAM.PRE_OUT_D ;
            VL_OUT_ALM,                      PARAM.OUT_ALM ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __dal_view_4
{
        LABEL           [dal_view_4] ;
        HELP            [dal_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_INVERT_OPTS,                  PARAM.INVERT_OPTS ;
            VL_COMB_TYPE,                    PARAM.COMB_TYPE ;
            VL_COND_TYPE,                    PARAM.COND_TYPE ;
            VL_COND_TIME,                    PARAM.COND_TIME ;
            VL_ACK_OPTION,                   PARAM.ACK_OPTION ;
            VL_ALARM_HYS,                    PARAM.ALARM_HYS ;
            VL_DISC_PRI,                     PARAM.DISC_PRI ;
            VL_DISC_COND,                    PARAM.DISC_COND ;
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
COLLECTION no_download_dal
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_dal
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
