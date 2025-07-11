/*
** @(#)mbo64_block.ddl     1.0 2009-06-16
**
** FF standard Multiple Binary Output Function Block
** Filename: mbo64_block.ddl
** Spec revision:       FF-900 FS 1.0  DDL spec
**                FF-890 FS 1.0 FBAP spec part 1
**                FF-891 FS 1.0 FBAP spec part 2
**				  FF-633 DPS 2.0
** Date of last change: 2009-06-16
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
** DBG   Revision 0.9  20090616
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Multiple Binary Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_MBO64_BLOCK,
DEVICE_REVISION __RIO_MBO64_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_MBO64_BLOCK_rel_dd_rev
/*
**********************************************************************
** Multiple Binary Output
** Definition of a multiple binary output block
**********************************************************************
*/
BLOCK   __multiple_binary_output_64_block
{
        CHARACTERISTICS __mbo64_character ;
        LABEL                              [mbo64_block] ;
        HELP                               [mbo64_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
				FORCE_ENB_B64,			__force_enb_b64 ;
				CHANNEL_TAG_64A,		__channel_tag_64a;
				CHANNEL_TAG_64B,		__channel_tag_64b;
				SPM_B64,				__spm_b64;
				CAS_INM_B64,			__cas_inm_b64;
				OUTM_B64,				__outm_b64 ;
				MAP_MM_64,				__map_mm_64;
				MO_FSTATE_OPTS_64,		__mo_fstate_opts_64;
				MO_POWERUP_OPTS_64,		__mo_powerup_opts_64;
				FSTATE_TIME,			__fstate_time;
				FSTATE_VAL_B64,			__fstate_val_b64;
				FSTATE_ST_64,			__fstate_st_64;
				BKCAL_OUTM_B64,			__bkcal_outm_b64;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __mbo64_view_1 ;
                VIEW_2, __mbo64_view_2 ;
                VIEW_3, __mbo64_view_3 ;
                VIEW_4, __mbo64_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_mbo64
		,upload_wanted_mbo64
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __mbo64_character
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
VARIABLE_LIST   __mbo64_view_1
{
        LABEL           [mbo64_view_1] ;
        HELP            [mbo64_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_SPM_B64,		PARAM.SPM_B64;
				VL_CAS_INM_B64,	PARAM.CAS_INM_B64;
				VL_MAP_MM_64,	PARAM.MAP_MM_64;
				VL_FSTATE_ST_64,	PARAM.FSTATE_ST_64;
        }
}

VARIABLE_LIST   __mbo64_view_2
{
        LABEL           [mbo64_view_2] ;
        HELP            [mbo64_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
				VL_FORCE_ENB_B64,		PARAM.FORCE_ENB_B64 ;
        }
}

VARIABLE_LIST   __mbo64_view_3
{
        LABEL           [mbo64_view_3] ;
        HELP            [mbo64_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_SPM_B64,		PARAM.SPM_B64;
				VL_CAS_INM_B64,	PARAM.CAS_INM_B64;
				VL_OUTM_B64,	PARAM.OUTM_B64;
				VL_MAP_MM_64,	PARAM.MAP_MM_64;
				VL_FSTATE_ST_64,	PARAM.FSTATE_ST_64;
				VL_BKCAL_OUTM_B64,	PARAM.BKCAL_OUTM_B64;
        }
}

VARIABLE_LIST   __mbo64_view_4
{
        LABEL           [mbo64_view_4] ;
        HELP            [mbo64_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
				VL_FORCE_ENB_B64,		PARAM.FORCE_ENB_B64 ;
				VL_MO_FSTATE_OPTS_64,	PARAM.MO_FSTATE_OPTS_64;
				VL_MO_POWERUP_OPTS_64,	PARAM.MO_POWERUP_OPTS_64;
				VL_FSTATE_TIME,	PARAM.FSTATE_TIME;
				VL_FSTATE_VAL_B64, PARAM.FSTATE_VAL_B64;
        }
}

/*
**********************************************************************
** no_download & upload_wanted collections
**********************************************************************
*/
#ifdef UD_LISTS
COLLECTION no_download_mbo64
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_mbo64
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
