/*
** @(#)os_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Output Splitter block
** Filename: os_block.ddl
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
** Output Splitter block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __OUTPUT_SPLITTER,
DEVICE_REVISION __OUTPUT_SPLITTER_rel_dev_rev,
DD_REVISION     __OUTPUT_SPLITTER_rel_dd_rev
/*
**********************************************************************
** Output Splitter
** Definition of Output Splitter Block
**********************************************************************
*/
BLOCK   __output_splitter
{
        CHARACTERISTICS __os_character ;
        LABEL                              [output_splitter_block] ;
        HELP                               [output_splitter_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            SP,                         __sp ;
            OUT_1,                      __out_1 ;
            OUT_2,                      __out_2 ;
            OUT_1_RANGE,                __out_1_range ;
            OUT_2_RANGE,                __out_2_range ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_os ;
            #endif
            CAS_IN,                     __cas_in ;
            BKCAL_OUT,                  __bkcal_out ;
            IN_ARRAY,                   __in_array ;
            OUT_ARRAY,                  __out_array ;
            LOCKVAL,                    __lockval ;
            BKCAL_IN_1,                 __bkcal_in_1 ;
            BKCAL_IN_2,                 __bkcal_in_2 ;
            BAL_TIME,                   __bal_time ;
            HYSTVAL,                    __hystval ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __os_view_1 ;
            VIEW_2, __os_view_2 ;
            VIEW_3, __os_view_3 ;
            VIEW_4, __os_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_os_out_1,
            __unit_os_out_2
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_os
		,upload_wanted_os
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __os_character
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
VARIABLE_LIST   __os_view_1
{
        LABEL           [os_view_1] ;
        HELP            [os_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_SP,                           PARAM.SP ;
            VL_OUT_1,                        PARAM.OUT_1 ;
            VL_OUT_2,                        PARAM.OUT_2 ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
        }
}

VARIABLE_LIST   __os_view_2
{
        LABEL           [os_view_2] ;
        HELP            [os_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_1_RANGE,                  PARAM.OUT_1_RANGE ;
            VL_OUT_2_RANGE,                  PARAM.OUT_2_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __os_view_3
{
        LABEL           [os_view_3] ;
        HELP            [os_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_SP,                           PARAM.SP ;
            VL_OUT_1,                        PARAM.OUT_1 ;
            VL_OUT_2,                        PARAM.OUT_2 ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
            VL_BKCAL_OUT,                    PARAM.BKCAL_OUT ;
            VL_BKCAL_IN_1,                   PARAM.BKCAL_IN_1 ;
            VL_BKCAL_IN_2,                   PARAM.BKCAL_IN_2 ;
        }
}

VARIABLE_LIST   __os_view_4
{
        LABEL           [os_view_4] ;
        HELP            [os_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_IN_ARRAY,                     PARAM.IN_ARRAY ;
            VL_OUT_ARRAY,                    PARAM.OUT_ARRAY ;
            VL_LOCKVAL,                      PARAM.LOCKVAL ;
            VL_BAL_TIME,                     PARAM.BAL_TIME ;
            VL_HYSTVAL,                      PARAM.HYSTVAL ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_os_out_1 {
    PARAM.OUT_1_RANGE.UNITS_INDEX : PARAM.OUT_1.VALUE
}
UNIT __unit_os_out_2 {
    PARAM.OUT_2_RANGE.UNITS_INDEX : PARAM.OUT_2.VALUE
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
COLLECTION no_download_os
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_os
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
