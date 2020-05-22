/*
** @(#)mdi_block.ddl 1.0 2002-06-09
**
** FF standard Multiple Discrete Input block
** Filename: mdi_block.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.3 FBAP spec part 1
**                  FF-891 FS 1.3 FBAP spec part 2
**                  FF-893 FS 1.0 FBAP spec part 4
** Date of last change: 2002-06-09
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
**  TAB Revision draft   1998-11-02
**  DAD Revision 0.9beta 1999-03-04
**  SBM Revision 1.0     2002-06-09
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
** Multiple Discrete Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __MDI,
DEVICE_REVISION __MDI_rel_dev_rev,
DD_REVISION     __MDI_rel_dd_rev


BLOCK   __mdi_block
{
   CHARACTERISTICS      __mdi_character ;
   LABEL                [mdi_block] ;
   HELP                 [mdi_block_help] ;
   PARAMETERS
   {
      ST_REV,           __st_rev ;
      TAG_DESC,         __tag_desc ;
      STRATEGY,         __strategy ;
      ALERT_KEY,        __alert_key ;
      MODE_BLK,         __mode_blk ;
      BLOCK_ERR,        __block_err ;
      CHANNEL,          __channel;
      OUT_D1,           __out_d1;
      OUT_D2,           __out_d2;
      OUT_D3,           __out_d3;
      OUT_D4,           __out_d4;
      OUT_D5,           __out_d5;
      OUT_D6,           __out_d6;
      OUT_D7,           __out_d7;
      OUT_D8,           __out_d8;
      UPDATE_EVT,       __update_evt ;
      BLOCK_ALM,        __block_alm ;
   }

   PARAMETER_LISTS
   {
      VIEW_1,   __mdi_view_1 ;
      VIEW_2,   __mdi_view_2 ;
      VIEW_3,   __mdi_view_3 ;
      VIEW_4,   __mdi_view_4 ;
   }
   
   #ifdef UD_LISTS
   COLLECTION_ITEMS
   {
   	no_download_mdi
   	,upload_wanted_mdi
   }
   #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __mdi_character
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

VARIABLE_LIST     __mdi_view_1
{
   LABEL       [mdi_view_1_label] ;
   HELP        [mdi_view_1_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_OUT_D1,        PARAM.OUT_D1 ;
      VL_OUT_D2,        PARAM.OUT_D2 ;
      VL_OUT_D3,        PARAM.OUT_D3 ;
      VL_OUT_D4,        PARAM.OUT_D4 ;
      VL_OUT_D5,        PARAM.OUT_D5 ;
      VL_OUT_D6,        PARAM.OUT_D6 ;
      VL_OUT_D7,        PARAM.OUT_D7 ;
      VL_OUT_D8,        PARAM.OUT_D8 ;
   }
}

VARIABLE_LIST     __mdi_view_2
{
   LABEL       [mdi_view_2_label] ;
   HELP        [mdi_view_2_help] ;
   MEMBERS
   {
      VL_ST_REV,      PARAM.ST_REV ;
   }
}

VARIABLE_LIST     __mdi_view_3
{
   LABEL       [mdi_view_3_label] ;
   HELP        [mdi_view_3_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_OUT_D1,        PARAM.OUT_D1 ;
      VL_OUT_D2,        PARAM.OUT_D2 ;
      VL_OUT_D3,        PARAM.OUT_D3 ;
      VL_OUT_D4,        PARAM.OUT_D4 ;
      VL_OUT_D5,        PARAM.OUT_D5 ;
      VL_OUT_D6,        PARAM.OUT_D6 ;
      VL_OUT_D7,        PARAM.OUT_D7 ;
      VL_OUT_D8,        PARAM.OUT_D8 ;
   }
}

VARIABLE_LIST     __mdi_view_4
{
   LABEL       [mdi_view_4_label] ;
   HELP        [mdi_view_4_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_STRATEGY,      PARAM.STRATEGY ;
      VL_ALERT_KEY,     PARAM.ALERT_KEY ;
      VL_CHANNEL,       PARAM.CHANNEL ;
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
COLLECTION no_download_mdi
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_mdi
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
