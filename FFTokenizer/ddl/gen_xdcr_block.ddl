/*
** @(#)gen_xdcr_block.ddl 1.0 2007-11-21
**
** FF Resource Block for Programable Resource
** Filename: prog_resblock.ddl
** Spec revision:   	FF-900 FS 5.0  DDL spec
**			FF-901 FS 1.0  DD interop spec
**			FF-902 FS 1.0  Transducer Block Common Structures
** Date of last change: 2007-11-21
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
** (c) Fieldbus Foundation(TM) (1999-2007)
**
*/

/*
** HISTORY:
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
** Programable Resource Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __GEN_XDCR_BLOCK,
DEVICE_REVISION __GEN_XDCR_BLOCK_beta_dev_rev,
DD_REVISION     __GEN_XDCR_BLOCK_beta_dd_rev

/*
**********************************************************************
** Generic Transducer Block Definition
**********************************************************************
*/
BLOCK      __generic_xdcr_block
{
    CHARACTERISTICS     __generic_xdcr_character ;
    LABEL               [gen_xdcr_blk] ;
    HELP                [gen_xdcr_blk_help] ;
    PARAMETERS
    {
        ST_REV,			__st_rev ;
	TAG_DESC,		__tag_desc ;
	STRATEGY,		__strategy ;
	ALERT_KEY,		__alert_key ;
	MODE_BLK,		__mode_blk ;
	BLOCK_ERR,		__block_err ;
	UPDATE_EVT,		__update_evt ;
	BLOCK_ALM,		__block_alm ;
	TRANSDUCER_DIRECTORY,	__transducer_directory ;
	TRANSDUCER_TYPE,	__transducer_type ;
	XD_ERROR,		__xd_error ;
        COLLECTION_DIRECTORY,	__collection_directory ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __generic_xdcr_view_1 ;
        VIEW_2, __generic_xdcr_view_2 ;
        VIEW_3, __generic_xdcr_view_3 ;
        VIEW_4, __generic_xdcr_view_4 ;
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_gen_xdcr
    	,upload_wanted_gen_xdcr
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __generic_xdcr_character
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
VARIABLE_LIST   __generic_xdcr_view_1
{
    LABEL       [gen_xdcr_view_1] ;
    HELP        [gen_xdcr_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,              PARAM.ST_REV ;
	VL_MODE_BLK,            PARAM.MODE_BLK ;
	VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
	VL_XD_ERROR,            PARAM.XD_ERROR ;
    }
}

VARIABLE_LIST   __generic_xdcr_view_2
{
    LABEL       [gen_xdcr_view_2] ;
    HELP        [gen_xdcr_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,              PARAM.ST_REV ;
	VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
     }
}

VARIABLE_LIST   __generic_xdcr_view_3
{
    LABEL       [gen_xdcr_view_3] ;
    HELP        [gen_xdcr_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,              PARAM.ST_REV ;
	VL_MODE_BLK,            PARAM.MODE_BLK ;
	VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
	VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
	VL_XD_ERROR,            PARAM.XD_ERROR ;
    }
}

VARIABLE_LIST   __generic_xdcr_view_4
{
    LABEL       [gen_xdcr_view_4] ;
    HELP        [gen_xdcr_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
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
COLLECTION no_download_gen_xdcr
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_gen_xdcr
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
