/*
** @(#)mao16_block.ddl     1.0 2009-06-16
**
** FF standard Multiple Analog Output Function Block
** Filename: mao16_block.ddl
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
** Multiple Analog Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_MAO16_BLOCK,
DEVICE_REVISION __RIO_MAO16_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_MAO16_BLOCK_rel_dd_rev
/*
**********************************************************************
** Multiple Analog Output
** Definition of a multiple analog output block
**********************************************************************
*/
BLOCK   __multiple_analog_output_16_block
{
        CHARACTERISTICS __mao16_character ;
        LABEL                              [mao16_block] ;
        HELP                               [mao16_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
				FORCE_ENB_16,			__force_enb_16 ;
				CHANNEL_TAG_16,			__channel_tag_16 ;
				SPM_16,					__spm_16 ;
				CAS_INM_16,				__cas_inm_16 ;
				OUTM_16,				__outm_16 ;
				MAP_MM_16,				__map_mm_16 ;
				MO_FSTATE_OPTS_16,		__mo_fstate_opts_16 ;
				MO_POWERUP_OPTS_16,		__mo_powerup_opts_16 ;
				FSTATE_TIME,			__fstate_time ;
				FSTATE_VAL_16,			__fstate_val_16 ;
				FSTATE_ST_16,			__fstate_st_16 ;
				BKCAL_OUTM_16,			__bkcal_outm_16 ;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __mao16_view_1 ;
                VIEW_2, __mao16_view_2 ;
                VIEW_3, __mao16_view_3 ;
                VIEW_4, __mao16_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_mao16
		,upload_wanted_mao16
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __mao16_character
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
VARIABLE_LIST   __mao16_view_1
{
        LABEL           [mao16_view_1] ;
        HELP            [mao16_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_FORCE_ENB_16, PARAM.FORCE_ENB_16 ;
				VL_SPM_16,		PARAM.SPM_16 ;
				VL_CAS_INM_16,		PARAM.CAS_INM_16 ;
				VL_OUTM_16,		PARAM.OUTM_16 ;
				VL_MAP_MM_16,	PARAM.MAP_MM_16 ;
				VL_FSTATE_ST_16,	PARAM.FSTATE_ST_16 ;
        }
}

VARIABLE_LIST   __mao16_view_2
{
        LABEL           [mao16_view_2] ;
        HELP            [mao16_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
				VL_FORCE_ENB_16,		PARAM.FORCE_ENB_16 ;
        }
}

VARIABLE_LIST   __mao16_view_3
{
        LABEL           [mao16_view_3] ;
        HELP            [mao16_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_FORCE_ENB_16, PARAM.FORCE_ENB_16 ;
				VL_SPM_16,		PARAM.SPM_16 ;
				VL_CAS_INM_16,		PARAM.CAS_INM_16 ;
				VL_OUTM_16,		PARAM.OUTM_16 ;
				VL_MAP_MM_16,	PARAM.MAP_MM_16 ;
				VL_FSTATE_ST_16,	PARAM.FSTATE_ST_16 ;
				VL_BKCAL_OUTM_16,	PARAM.BKCAL_OUTM_16 ;
        }
}

VARIABLE_LIST   __mao16_view_4
{
        LABEL           [mao16_view_4] ;
        HELP            [mao16_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
				VL_FORCE_ENB_16,		PARAM.FORCE_ENB_16 ;
				VL_MO_FSTATE_OPTS_16,	PARAM.MO_FSTATE_OPTS_16 ;
				VL_MO_POWERUP_OPTS_16,	PARAM.MO_POWERUP_OPTS_16 ;
				VL_FSTATE_TIME,	PARAM.FSTATE_TIME ;
				VL_FSTATE_VAL_16,	PARAM.FSTATE_VAL_16 ;
        }
}

/*
**********************************************************************
** no_download & upload_wanted collections
**********************************************************************
*/
#ifdef UD_LISTS
COLLECTION no_download_mao16
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_mao16
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
