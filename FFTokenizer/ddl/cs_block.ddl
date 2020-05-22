/*
** @(#)cs_block.ddl     1.1 1999-03-04
**
** FF standard Control Selector block
** Filename: cs_block.ddl
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
**       added new rev numbering system for dev rev and dd rev
** FI    Revision 1.2  20051109
**       added block specific status options per AR#708
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
** Control Selector block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __CS_BLOCK,
DEVICE_REVISION __CS_BLOCK_rel_dev_rev,
DD_REVISION     __CS_BLOCK_rel_dd_rev
/*
**********************************************************************
** Control Selector
** Definition of a control selector block
**********************************************************************
*/
BLOCK   __control_selector_block
{
        CHARACTERISTICS     __cs_character ;
        LABEL                           [control_selector_block] ;
        HELP                            [control_selector_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
                OUT,                    __out ;
                OUT_SCALE,              __out_scale ;
                GRANT_DENY,             __grant_deny ;
                #ifdef LIB2
                STATUS_OPTS,    	__status_opts ;
                #else
                STATUS_OPTS,    	__status_opts_cs ;
                #endif
                SEL_1,                  __sel_1 ;
                SEL_2,                  __sel_2 ;
                SEL_3,                  __sel_3 ;
                SEL_TYPE,               __sel_type ;
                BKCAL_IN,               __bkcal_in ;
                OUT_HI_LIM,             __out_hi_lim ;
                OUT_LO_LIM,             __out_lo_lim ;
                BKCAL_SEL_1,    	__bkcal_sel_1 ;
                BKCAL_SEL_2,    	__bkcal_sel_2 ;
                BKCAL_SEL_3,    	__bkcal_sel_3 ;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __cs_view_1 ;
                VIEW_2, __cs_view_2 ;
                VIEW_3, __cs_view_3 ;
                VIEW_4, __cs_view_4 ;
        }
        UNIT_ITEMS
        {
                __unit_cs_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_cs
		,upload_wanted_cs
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __cs_character
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
VARIABLE_LIST   __cs_view_1
{
        LABEL           [cs_view_1] ;
        HELP            [cs_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_OUT,                 PARAM.OUT ;
                VL_SEL_1,               PARAM.SEL_1 ;
                VL_SEL_2,               PARAM.SEL_2 ;
                VL_SEL_3,               PARAM.SEL_3 ;
        }
}

VARIABLE_LIST   __cs_view_2
{
        LABEL           [cs_view_2] ;
        HELP            [cs_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_OUT_SCALE,   PARAM.OUT_SCALE ;
                VL_GRANT_DENY,  PARAM.GRANT_DENY ;
                VL_OUT_HI_LIM,  PARAM.OUT_HI_LIM ;
                VL_OUT_LO_LIM,  PARAM.OUT_LO_LIM ;
        }
}

VARIABLE_LIST   __cs_view_3
{
        LABEL           [cs_view_3] ;
        HELP            [cs_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_OUT,                 PARAM.OUT ;
                VL_SEL_1,               PARAM.SEL_1 ;
                VL_SEL_2,               PARAM.SEL_2 ;
                VL_SEL_3,               PARAM.SEL_3 ;
                VL_BKCAL_IN,    PARAM.BKCAL_IN ;
                VL_BKCAL_SEL_1, PARAM.BKCAL_SEL_1 ;
                VL_BKCAL_SEL_2, PARAM.BKCAL_SEL_2 ;
                VL_BKCAL_SEL_3, PARAM.BKCAL_SEL_3 ;
        }
}

VARIABLE_LIST   __cs_view_4
{
        LABEL           [cs_view_4] ;
        HELP            [cs_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
                VL_SEL_TYPE,    PARAM.SEL_TYPE ;
        }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_cs_out
{
        PARAM.OUT_SCALE.UNITS_INDEX :
                PARAM.OUT.VALUE,
                PARAM.OUT_SCALE.EU_100,
                PARAM.OUT_SCALE.EU_0,
                PARAM.SEL_1.VALUE,
                PARAM.SEL_2.VALUE,
                PARAM.SEL_3.VALUE,
                PARAM.BKCAL_IN.VALUE,
                PARAM.OUT_HI_LIM,
                PARAM.OUT_LO_LIM,
                PARAM.BKCAL_SEL_1.VALUE,
                PARAM.BKCAL_SEL_2.VALUE,
                PARAM.BKCAL_SEL_3.VALUE
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
COLLECTION no_download_cs
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_cs
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
