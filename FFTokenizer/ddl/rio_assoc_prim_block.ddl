/*
** @(#)rio_assoc_prim_block.ddl     1.0 2009-06-22
**
** FF standard Remote IO Primary Association Transducer Block
** Filename: rio_assoc_prim_block.ddl
** Spec revision:       FF-900 FS 1.0  DDL spec
**                FF-890 FS 1.0 FBAP spec part 1
**                FF-891 FS 1.0 FBAP spec part 2
**				  FF-061 DPS 2.0
** Date of last change: 2009-06-22
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
** FD   Revision 0.9  20090622
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Rio Primary Association Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_ASSOC_PRIMARY_BLOCK,
DEVICE_REVISION __RIO_ASSOC_PRIMARY_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_ASSOC_PRIMARY_BLOCK_rel_dd_rev
/*
**********************************************************************
** Association Block (Primary)
** Skeleton of the Primary Association Transducer Block
**********************************************************************
*/
BLOCK   __primary_association_block
{
        CHARACTERISTICS __pab_character ;
        LABEL                              [pab_block] ;
        HELP                               [pab_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
				UPDATE_EVT,				__update_evt ;
				BLOCK_ALM,				__block_alm ;
				NUM_POSNS,				__num_posns ;
				MAX_NUM_POSNS,			__max_num_posns ;
				ELEM_MISMAT_NUM,		__elem_mismat_num ;
				ELEM_MISMAT_BS_1,		__elem_mismat_bs_1 ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __pab_view_1 ;
                VIEW_2, __pab_view_2 ;
                VIEW_3, __pab_view_3 ;
                VIEW_4, __pab_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_pab
		,upload_wanted_pab
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __pab_character
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
VARIABLE_LIST   __pab_view_1
{
        LABEL           [pab_view_1] ;
        HELP            [pab_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_NUM_POSNS,   PARAM.NUM_POSNS ;
				VL_MAX_NUM_POSNS,   PARAM.MAX_NUM_POSNS ;
				VL_ELEM_MISMAT_BS_1, PARAM.ELEM_MISMAT_BS_1 ;
        }
}

VARIABLE_LIST   __pab_view_2
{
        LABEL           [pab_view_2] ;
        HELP            [pab_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
        }
}

VARIABLE_LIST   __pab_view_3
{
        LABEL           [pab_view_3] ;
        HELP            [pab_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
				VL_NUM_POSNS,   PARAM.NUM_POSNS ;
				VL_MAX_NUM_POSNS,   PARAM.MAX_NUM_POSNS ;
				VL_ELEM_MISMAT_BS_1, PARAM.ELEM_MISMAT_BS_1 ;
        }
}

VARIABLE_LIST   __pab_view_4
{
        LABEL           [pab_view_4] ;
        HELP            [pab_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
				VL_ELEM_MISMAT_NUM, PARAM.ELEM_MISMAT_NUM ;
        }
}

/*
**********************************************************************
** no_download & upload_wanted collections
**********************************************************************
*/
#ifdef UD_LISTS
COLLECTION no_download_pab
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_pab
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
