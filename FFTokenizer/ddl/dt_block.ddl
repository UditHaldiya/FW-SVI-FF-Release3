/*
** @(#)dt_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Deadtime block
** Filename: dt_block.ddl
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
** Deadtime block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DEADTIME,
DEVICE_REVISION __DEADTIME_rel_dev_rev,
DD_REVISION     __DEADTIME_rel_dd_rev
/*
**********************************************************************
** Deadtime
** Definition of Deadtime Block
**********************************************************************
*/
BLOCK   __deadtime
{
        CHARACTERISTICS __dt_character ;
        LABEL                              [deadtime_block] ;
        HELP                               [deadtime_block_help] ;
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
            STATUS_OPTS,                __status_opts_dt ;
            #endif
            IN,                         __in ;
            FOLLOW,                     __follow ;
            DEAD_TIME,                  __dead_time ;
            BAL_TIME,                   __bal_time ;
            OUTAGE_LIM,                 __outage_lim ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __dt_view_1 ;
            VIEW_2, __dt_view_2 ;
            VIEW_3, __dt_view_3 ;
            VIEW_4, __dt_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_dt_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_dt
		,upload_wanted_dt
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __dt_character
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
VARIABLE_LIST   __dt_view_1
{
        LABEL           [dt_view_1] ;
        HELP            [dt_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN,                           PARAM.IN ;
            VL_FOLLOW,                       PARAM.FOLLOW ;
            VL_DEAD_TIME,                    PARAM.DEAD_TIME ;
        }
}

VARIABLE_LIST   __dt_view_2
{
        LABEL           [dt_view_2] ;
        HELP            [dt_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __dt_view_3
{
        LABEL           [dt_view_3] ;
        HELP            [dt_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN,                           PARAM.IN ;
            VL_FOLLOW,                       PARAM.FOLLOW ;
            VL_DEAD_TIME,                    PARAM.DEAD_TIME ;
        }
}

VARIABLE_LIST   __dt_view_4
{
        LABEL           [dt_view_4] ;
        HELP            [dt_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_BAL_TIME,                     PARAM.BAL_TIME ;
            VL_OUTAGE_LIM,                   PARAM.OUTAGE_LIM ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_dt_out {
    PARAM.OUT_RANGE.UNITS_INDEX : PARAM.OUT.VALUE
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
COLLECTION no_download_dt
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_dt
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
