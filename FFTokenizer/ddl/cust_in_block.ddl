/*
** @(#)cust_in_block.ddl      1.0	2009-06-15
**
** FF Custom Input Block
** Filename: cust_in_block.ddl
** Spec revision:   FF-900 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  
** Date of last change: 2009-06-15
** Description:
** 	"Skeleton" block definition as per FF-890 Input Function
**	Block Formal Model.  Block definition can be imported and
**	application specific parameters can be added through redefinitions.
**	The following parameters are required and should be added (specific
**	to application):
**		Process Variable
**		Primary Output
**		Simulate Parameter
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Custom Input Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __CUSTOM_INPUT_BLOCK,
DEVICE_REVISION __CUSTOM_INPUT_BLOCK_rel_dev_rev,
DD_REVISION     __CUSTOM_INPUT_BLOCK_rel_dd_rev

/*
**********************************************************************
** "Skeleton" block definition
**********************************************************************
*/
BLOCK   __custom_in_block
{
        CHARACTERISTICS		__custom_in_character ;
        LABEL                   [custom_in_block] ;
        HELP                    [custom_in_block_help] ;
        PARAMETERS
        {
                ST_REV,				__st_rev ;
                TAG_DESC,                       __tag_desc ;
                STRATEGY,			__strategy ;
                ALERT_KEY,			__alert_key ;
                MODE_BLK,			__mode_blk ;
                BLOCK_ERR,			__block_err ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __custom_in_view_1 ;
                VIEW_2, __custom_in_view_2 ;
                VIEW_3, __custom_in_view_3 ;
                VIEW_4, __custom_in_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_custom_in
		,upload_wanted_custom_in
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __custom_in_character
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
VARIABLE_LIST   __custom_in_view_1
{
        LABEL           [custom_in_view_1] ;
        HELP            [custom_in_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,         	PARAM.ST_REV ;
                VL_MODE_BLK,            PARAM.MODE_BLK ;
                VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
        }
}

VARIABLE_LIST   __custom_in_view_2
{
        LABEL           [custom_in_view_2] ;
        HELP            [custom_in_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,     		PARAM.ST_REV ;
        }
}

VARIABLE_LIST   __custom_in_view_3
{
        LABEL           [custom_in_view_3] ;
        HELP            [custom_in_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,            PARAM.MODE_BLK ;
                VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
        }
}

VARIABLE_LIST   __custom_in_view_4
{
        LABEL           [custom_in_view_4] ;
        HELP            [custom_in_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,		PARAM.ST_REV ;
		VL_STRATEGY,		PARAM.STRATEGY ;
		VL_ALERT_KEY,		PARAM.ALERT_KEY ;
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
COLLECTION no_download_custom_in
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_custom_in
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
