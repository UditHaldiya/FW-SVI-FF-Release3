/*
** @(#)ahi_block.ddl    1.0 Thu May 23 10:21:53 2002

**
** FF standard Analog Human Interface block
** Filename: ahi_block.ddl
** Spec revision:       FF-900 FS 1.0 DDL spec
**                      FF-892 FS 1.5 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
** Date of last change: 2002-05-23
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
** Analog Human Interface block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __ANALOG_HUMAN_INTERFACE,
DEVICE_REVISION __ANALOG_HUMAN_INTERFACE_beta_dev_rev,
DD_REVISION     __ANALOG_HUMAN_INTERFACE_beta_dd_rev
/*
**********************************************************************
** Analog Human Interface
** Definition of Analog Human Interface Block
**********************************************************************
*/
BLOCK   __analog_human_interface
{
        CHARACTERISTICS __ahi_character ;
        LABEL                              [analog_human_interface_block] ;
        HELP                               [analog_human_interface_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            GRANT_DENY,                 __grant_deny ;
            IV_1,                       __iv_1 ;
            IV_2,                       __iv_2 ;
            IV_3,                       __iv_3 ;
            IV_4,                       __iv_4 ;
            IV_SCALE_1,                 __iv_scale_1 ;
            IV_SCALE_2,                 __iv_scale_2 ;
            IV_SCALE_3,                 __iv_scale_3 ;
            IV_SCALE_4,                 __iv_scale_4 ;
            INIT_VAL_1,                 __init_val_1 ;
            INIT_VAL_2,                 __init_val_2 ;
            INIT_VAL_3,                 __init_val_3 ;
            INIT_VAL_4,                 __init_val_4 ;
            IV_DESC_1,                  __iv_desc_1 ;
            IV_DESC_2,                  __iv_desc_2 ;
            IV_DESC_3,                  __iv_desc_3 ;
            IV_DESC_4,                  __iv_desc_4 ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __ahi_view_1 ;
            VIEW_2, __ahi_view_2 ;
            VIEW_3, __ahi_view_3 ;
            VIEW_4, __ahi_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_ahi
		,upload_wanted_ahi
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ahi_character
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
VARIABLE_LIST   __ahi_view_1
{
        LABEL           [ahi_view_1] ;
        HELP            [ahi_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_IV_1,                         PARAM.IV_1 ;
            VL_IV_2,                         PARAM.IV_2 ;
            VL_IV_3,                         PARAM.IV_3 ;
            VL_IV_4,                         PARAM.IV_4 ;
        }
}

VARIABLE_LIST   __ahi_view_2
{
        LABEL           [ahi_view_2] ;
        HELP            [ahi_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_IV_SCALE_1,                   PARAM.IV_SCALE_1 ;
            VL_IV_SCALE_2,                   PARAM.IV_SCALE_2 ;
            VL_IV_SCALE_3,                   PARAM.IV_SCALE_3 ;
            VL_IV_SCALE_4,                   PARAM.IV_SCALE_4 ;
        }
}

VARIABLE_LIST   __ahi_view_3
{
        LABEL           [ahi_view_3] ;
        HELP            [ahi_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_IV_1,                         PARAM.IV_1 ;
            VL_IV_2,                         PARAM.IV_2 ;
            VL_IV_3,                         PARAM.IV_3 ;
            VL_IV_4,                         PARAM.IV_4 ;
        }
}

VARIABLE_LIST   __ahi_view_4
{
        LABEL           [ahi_view_4] ;
        HELP            [ahi_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_INIT_VAL_1,                   PARAM.INIT_VAL_1 ;
            VL_INIT_VAL_2,                   PARAM.INIT_VAL_2 ;
            VL_INIT_VAL_3,                   PARAM.INIT_VAL_3 ;
            VL_INIT_VAL_4,                   PARAM.INIT_VAL_4 ;
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
COLLECTION no_download_ahi
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ahi
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
