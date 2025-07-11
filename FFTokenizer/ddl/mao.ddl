/*
** @(#)mao_block.ddl 1.0 2002-06-09
**
** FF standard Multiple Analog Output block
** Filename: mao_block.ddl
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
** Multiple Analog Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __MAO,
DEVICE_REVISION __MAO_rel_dev_rev,
DD_REVISION     __MAO_rel_dd_rev


BLOCK   __mao_block
{
   CHARACTERISTICS      __mao_character ;
   LABEL                [mao_block] ;
   HELP                 [mao_block_help] ;
   PARAMETERS
   {
      ST_REV,           __st_rev ;
      TAG_DESC,         __tag_desc ;
      STRATEGY,         __strategy ;
      ALERT_KEY,        __alert_key ;
      MODE_BLK,         __mode_blk ;
      BLOCK_ERR,        __block_err ;
      CHANNEL,          __channel;
      IN_1,                __in_1;
      IN_2,                __in_2;
      IN_3,                __in_3;
      IN_4,                __in_4;
      IN_5,                __in_5;
      IN_6,                __in_6;
      IN_7,                __in_7;
      IN_8,                __in_8;
      MO_OPTS,          __mo_opts;
      FSTATE_TIME,      __fstate_time;
      FSTATE_VAL1,      __fstate_val1;
      FSTATE_VAL2,      __fstate_val2;
      FSTATE_VAL3,      __fstate_val3;
      FSTATE_VAL4,      __fstate_val4;
      FSTATE_VAL5,      __fstate_val5;
      FSTATE_VAL6,      __fstate_val6;
      FSTATE_VAL7,      __fstate_val7;
      FSTATE_VAL8,      __fstate_val8;
      FSTATE_STATUS,     __fstate_status;
      UPDATE_EVT,       __update_evt ;
      BLOCK_ALM,        __block_alm ;
   }

   PARAMETER_LISTS
   {
      VIEW_1,   __mao_view_1 ;
      VIEW_2,   __mao_view_2 ;
      VIEW_3,   __mao_view_3 ;
      VIEW_4,   __mao_view_4 ;
   }
   
   #ifdef UD_LISTS
   COLLECTION_ITEMS
   {
   	no_download_mao
   	,upload_wanted_mao
   }
   #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __mao_character
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

VARIABLE_LIST     __mao_view_1
{
   LABEL          [mao_view_1_label] ;
   HELP           [mao_view_1_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_IN_1,          PARAM.IN_1 ;
      VL_IN_2,          PARAM.IN_2 ;
      VL_IN_3,          PARAM.IN_3 ;
      VL_IN_4,          PARAM.IN_4 ;
      VL_IN_5,          PARAM.IN_5 ;
      VL_IN_6,          PARAM.IN_6 ;
      VL_IN_7,          PARAM.IN_7 ;
      VL_IN_8,          PARAM.IN_8 ;
      VL_FSTATE_STATUS,  PARAM.FSTATE_STATUS;
   }
}

VARIABLE_LIST     __mao_view_2
{
   LABEL          [mao_view_2_label] ;
   HELP           [mao_view_2_help] ;
   MEMBERS
   {
      VL_ST_REV,      PARAM.ST_REV ;
   }
}

VARIABLE_LIST     __mao_view_3
{
   LABEL          [mao_view_3_label] ;
   HELP           [mao_view_3_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_IN_1,          PARAM.IN_1 ;
      VL_IN_2,          PARAM.IN_2 ;
      VL_IN_3,          PARAM.IN_3 ;
      VL_IN_4,          PARAM.IN_4 ;
      VL_IN_5,          PARAM.IN_5 ;
      VL_IN_6,          PARAM.IN_6 ;
      VL_IN_7,          PARAM.IN_7 ;
      VL_IN_8,          PARAM.IN_8 ;
      VL_FSTATE_STATUS,  PARAM.FSTATE_STATUS;
   }
}

VARIABLE_LIST     __mao_view_4
{
   LABEL          [mao_view_4_label] ;
   HELP           [mao_view_4_help] ;
   MEMBERS
   {
      VL_ST_REV,           PARAM.ST_REV ;
      VL_STRATEGY,         PARAM.STRATEGY ;
      VL_ALERT_KEY,        PARAM.ALERT_KEY ;
      VL_CHANNEL,          PARAM.CHANNEL ;
      VL_MO_OPTS,          PARAM.MO_OPTS;
      VL_FSTATE_TIME,      PARAM.FSTATE_TIME;
      VL_FSTATE_VAL1,      PARAM.FSTATE_VAL1;
      VL_FSTATE_VAL2,      PARAM.FSTATE_VAL2;
      VL_FSTATE_VAL3,      PARAM.FSTATE_VAL3;
      VL_FSTATE_VAL4,      PARAM.FSTATE_VAL4;
      VL_FSTATE_VAL5,      PARAM.FSTATE_VAL5;
      VL_FSTATE_VAL6,      PARAM.FSTATE_VAL6;
      VL_FSTATE_VAL7,      PARAM.FSTATE_VAL7;
      VL_FSTATE_VAL8,      PARAM.FSTATE_VAL8;
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
COLLECTION no_download_mao
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_mao
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
