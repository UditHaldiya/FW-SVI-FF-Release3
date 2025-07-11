/*
** @(#)is_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Input Selector block
** Filename: is_block.ddl
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
** Input Selector block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __INPUT_SELECTOR,
DEVICE_REVISION __INPUT_SELECTOR_rel_dev_rev,
DD_REVISION     __INPUT_SELECTOR_rel_dd_rev
/*
**********************************************************************
** Input Selector
** Definition of Input Selector Block
**********************************************************************
*/
BLOCK   __input_selector
{
        CHARACTERISTICS __is_character ;
        LABEL                              [input_selector_block] ;
        HELP                               [input_selector_block_help] ;
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
            STATUS_OPTS,                __status_opts_is ;
            #endif
            IN_1,                       __in_1 ;
            IN_2,                       __in_2 ;
            IN_3,                       __in_3 ;
            IN_4,                       __in_4 ;
            DISABLE_1,                  __disable_1 ;
            DISABLE_2,                  __disable_2 ;
            DISABLE_3,                  __disable_3 ;
            DISABLE_4,                  __disable_4 ;
            SELECT_TYPE,                __select_type ;
            MIN_GOOD,                   __min_good ;
            SELECTED,                   __selected ;
            OP_SELECT,                  __op_select ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __is_view_1 ;
            VIEW_2, __is_view_2 ;
            VIEW_3, __is_view_3 ;
            VIEW_4, __is_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_is_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_is
		,upload_wanted_is
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __is_character
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
VARIABLE_LIST   __is_view_1
{
        LABEL           [is_view_1] ;
        HELP            [is_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_IN_3,                         PARAM.IN_3 ;
            VL_IN_4,                         PARAM.IN_4 ;
            VL_DISABLE_1,                    PARAM.DISABLE_1 ;
            VL_DISABLE_2,                    PARAM.DISABLE_2 ;
            VL_DISABLE_3,                    PARAM.DISABLE_3 ;
            VL_DISABLE_4,                    PARAM.DISABLE_4 ;
            VL_SELECTED,                     PARAM.SELECTED ;
            VL_OP_SELECT,                    PARAM.OP_SELECT ;
        }
}

VARIABLE_LIST   __is_view_2
{
        LABEL           [is_view_2] ;
        HELP            [is_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __is_view_3
{
        LABEL           [is_view_3] ;
        HELP            [is_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_IN_3,                         PARAM.IN_3 ;
            VL_IN_4,                         PARAM.IN_4 ;
            VL_DISABLE_1,                    PARAM.DISABLE_1 ;
            VL_DISABLE_2,                    PARAM.DISABLE_2 ;
            VL_DISABLE_3,                    PARAM.DISABLE_3 ;
            VL_DISABLE_4,                    PARAM.DISABLE_4 ;
            VL_SELECTED,                     PARAM.SELECTED ;
            VL_OP_SELECT,                    PARAM.OP_SELECT ;
        }
}

VARIABLE_LIST   __is_view_4
{
        LABEL           [is_view_4] ;
        HELP            [is_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_SELECT_TYPE,                  PARAM.SELECT_TYPE ;
            VL_MIN_GOOD,                     PARAM.MIN_GOOD ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_is_out {
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
COLLECTION no_download_is
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_is
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
