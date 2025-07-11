/*
** @(#)rio_h1_block.ddl      0.9   2009-08-07
**
** FF Standard H1 Module Transducer Block
** Filename: rio_h1_block.ddl
** Spec revision:   FF-901 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.2  Transducer Block Common Structures
**                  FF-912 FS 1.0  Field Diagnostics Profile
**                  FF-915 DPS 2.2 Transducer Block for HSE RIO Module
**                  
** Date of last change: 2009-11-30
** Description:
**    Standard H1 Module Transducer Block
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
** TAB   Revision 0.1  20090807
** TAB   Revision 0.2  20091130
**       Updated for FF-915 DPS rev 2.2
** TAB   Revision 0.3  20100618
**       Updated for FF-915 DPS rev 2.3
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Standard H1 Module Transducer Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_H1_BLOCK,
DEVICE_REVISION __RIO_H1_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_H1_BLOCK_rel_dd_rev

/*
**********************************************************************
** Block definition
**********************************************************************
*/
BLOCK    __rio_h1_xdcr_block
{
         CHARACTERISTICS       __rio_h1_xdcr_character ;
         LABEL                 [rio_h1_xdcr_block] ;
         HELP                  [rio_h1_xdcr_block_help] ;
         PARAMETERS
         {
            ST_REV,                    __st_rev ;
            TAG_DESC,                  __tag_desc ;
            STRATEGY,                  __strategy ;
            ALERT_KEY,                 __alert_key ;
            MODE_BLK,                  __mode_blk ;
            BLOCK_ERR,                 __block_err ;
            UPDATE_EVT,                __update_evt ;
            BLOCK_ALM,                 __block_alm ;
            ACK_OPTION,                __ack_option ;
            TRANSDUCER_DIRECTORY,      __transducer_directory ;
            TRANSDUCER_TYPE,           __transducer_type ;
            TRANSDUCER_TYPE_VER,       __transducer_type_ver ;
            XD_ERROR,                  __xd_error ;
            COLLECTION_DIRECTORY,      __collection_directory ;
            MANUFAC_ID,                __manufac_id ;
            DEV_TYPE,                  __dev_type ;
            DEV_REV,                   __dev_rev ;
            DD_REV,                    __dd_rev ;
            H1_VFD_ID_1,               __h1_vfd_id_1 ;
            H1_VFD_ID_2,               __h1_vfd_id_2 ;
         }


         PARAMETER_LISTS
         {
            VIEW_1, __rio_h1_xdcr_view_1 ;
            VIEW_2, __rio_h1_xdcr_view_2 ;
            VIEW_3, __rio_h1_xdcr_view_3 ;
            VIEW_4, __rio_h1_xdcr_view_4 ;
         }

	#ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_rio_h1_xdcr
		,upload_wanted_rio_h1_xdcr
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __rio_h1_xdcr_character
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

VARIABLE_LIST     __rio_h1_xdcr_view_1
{
      LABEL       [rio_h1_xdcr_view_1] ;
      HELP        [rio_h1_xdcr_view_1_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
         VL_H1_VFD_ID_1,            PARAM.H1_VFD_ID_1 ;
         VL_H1_VFD_ID_2,            PARAM.H1_VFD_ID_2 ;
      }
}

VARIABLE_LIST     __rio_h1_xdcr_view_2
{
      LABEL       [rio_h1_xdcr_view_2] ;
      HELP        [rio_h1_xdcr_view_2_help] ;
      MEMBERS
      {
         VL_ST_REV,                    PARAM.ST_REV ;
         VL_TRANSDUCER_TYPE,           PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,       PARAM.TRANSDUCER_TYPE_VER ;
      }
}

VARIABLE_LIST   __rio_h1_xdcr_view_3
{
      LABEL           [rio_h1_xdcr_view_3] ;
      HELP            [rio_h1_xdcr_view_3_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
      }
}

VARIABLE_LIST     __rio_h1_xdcr_view_4
{
      LABEL       [rio_h1_xdcr_view_4] ;
      HELP        [rio_h1_xdcr_view_4_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_STRATEGY,               PARAM.STRATEGY ;
         VL_ALERT_KEY,              PARAM.ALERT_KEY ;
         VL_ACK_OPTION,             PARAM.ACK_OPTION ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,    PARAM.TRANSDUCER_TYPE_VER ;
         VL_MANUFAC_ID,             PARAM.MANUFAC_ID ;
         VL_DEV_TYPE,               PARAM.DEV_TYPE ;
         VL_DEV_REV,                PARAM.DEV_REV ;
         VL_DD_REV,                 PARAM.DD_REV ;
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
COLLECTION no_download_rio_h1_xdcr
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_rio_h1_xdcr
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
