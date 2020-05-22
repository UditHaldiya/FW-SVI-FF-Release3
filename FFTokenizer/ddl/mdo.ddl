/*
** @(#)mdo_block.ddl 1.0 2002-06-09
**
** FF standard Multiple Discrete Output block
** Filename: mdo_block.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.3 FBAP spec part 1
**                  FF-891 FS 1.3 FBAP spec part 2
**                  FF-893 DPS1.0 FBAP spec part 4
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
**  SBM Revision 1.0	 2002-06-09
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
** Multiple Discrete Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __MDO,
DEVICE_REVISION __MDO_rel_dev_rev,
DD_REVISION     __MDO_rel_dd_rev


BLOCK   __mdo_block
{
   CHARACTERISTICS      __mdo_character ;
   LABEL                [mdo_block] ;
   HELP                 [mdo_block_help] ;
   PARAMETERS
   {
      ST_REV,           __st_rev ;
      TAG_DESC,         __tag_desc ;
      STRATEGY,         __strategy ;
      ALERT_KEY,        __alert_key ;
      MODE_BLK,         __mode_blk ;
      BLOCK_ERR,        __block_err ;
      CHANNEL,          __channel;
      IN_D1,            __in_d1;
      IN_D2,            __in_d2;
      IN_D3,            __in_d3;
      IN_D4,            __in_d4;
      IN_D5,            __in_d5;
      IN_D6,            __in_d6;
      IN_D7,            __in_d7;
      IN_D8,            __in_d8;
      MO_OPTS,          __mo_opts;
      FSTATE_TIME,      __fstate_time;
      FSTATE_VAL_D1,    __fstate_val_d1;
      FSTATE_VAL_D2,    __fstate_val_d2;
      FSTATE_VAL_D3,    __fstate_val_d3;
      FSTATE_VAL_D4,    __fstate_val_d4;
      FSTATE_VAL_D5,    __fstate_val_d5;
      FSTATE_VAL_D6,    __fstate_val_d6;
      FSTATE_VAL_D7,    __fstate_val_d7;
      FSTATE_VAL_D8,    __fstate_val_d8;
      FSTATE_STATUS,     __fstate_status;
      UPDATE_EVT,       __update_evt ;
      BLOCK_ALM,        __block_alm ;
   }

   PARAMETER_LISTS
   {
      VIEW_1,   __mdo_view_1 ;
      VIEW_2,   __mdo_view_2 ;
      VIEW_3,   __mdo_view_3 ;
      VIEW_4,   __mdo_view_4 ;
   }
   
   #ifdef UD_LISTS
   COLLECTION_ITEMS
   {
   	no_download_mdo
   	,upload_wanted_mdo
   }
   #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __mdo_character
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
*/VARIABLE_LIST     __mdo_view_1
{
   LABEL          [mdo_view_1_label] ;
   HELP           [mdo_view_1_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_IN_D1,         PARAM.IN_D1 ;
      VL_IN_D2,         PARAM.IN_D2 ;
      VL_IN_D3,         PARAM.IN_D3 ;
      VL_IN_D4,         PARAM.IN_D4 ;
      VL_IN_D5,         PARAM.IN_D5 ;
      VL_IN_D6,         PARAM.IN_D6 ;
      VL_IN_D7,         PARAM.IN_D7 ;
      VL_IN_D8,         PARAM.IN_D8 ;
      VL_FSTATE_STATUS,  PARAM.FSTATE_STATUS;
   }
}

VARIABLE_LIST     __mdo_view_2
{
   LABEL          [mdo_view_2_label] ;
   HELP           [mdo_view_2_help] ;
   MEMBERS
   {
      VL_ST_REV,      PARAM.ST_REV ;
   }
}

VARIABLE_LIST     __mdo_view_3
{
   LABEL          [mdo_view_3_label] ;
   HELP           [mdo_view_3_help] ;
   MEMBERS
   {
      VL_ST_REV,        PARAM.ST_REV ;
      VL_MODE_BLK,      PARAM.MODE_BLK ;
      VL_BLOCK_ERR,     PARAM.BLOCK_ERR ;
      VL_IN_D1,         PARAM.IN_D1 ;
      VL_IN_D2,         PARAM.IN_D2 ;
      VL_IN_D3,         PARAM.IN_D3 ;
      VL_IN_D4,         PARAM.IN_D4 ;
      VL_IN_D5,         PARAM.IN_D5 ;
      VL_IN_D6,         PARAM.IN_D6 ;
      VL_IN_D7,         PARAM.IN_D7 ;
      VL_IN_D8,         PARAM.IN_D8 ;
      VL_FSTATE_STATUS,  PARAM.FSTATE_STATUS;
   }
}

VARIABLE_LIST     __mdo_view_4
{
   LABEL          [mdo_view_4_label] ;
   HELP           [mdo_view_4_help] ;
   MEMBERS
   {
      VL_ST_REV,           PARAM.ST_REV ;
      VL_STRATEGY,         PARAM.STRATEGY ;
      VL_ALERT_KEY,        PARAM.ALERT_KEY ;
      VL_CHANNEL,          PARAM.CHANNEL ;
      VL_MO_OPTS,          PARAM.MO_OPTS;
      VL_FSTATE_TIME,      PARAM.FSTATE_TIME;
      VL_FSTATE_VAL_D1,    PARAM.FSTATE_VAL_D1;
      VL_FSTATE_VAL_D2,    PARAM.FSTATE_VAL_D2;
      VL_FSTATE_VAL_D3,    PARAM.FSTATE_VAL_D3;
      VL_FSTATE_VAL_D4,    PARAM.FSTATE_VAL_D4;
      VL_FSTATE_VAL_D5,    PARAM.FSTATE_VAL_D5;
      VL_FSTATE_VAL_D6,    PARAM.FSTATE_VAL_D6;
      VL_FSTATE_VAL_D7,    PARAM.FSTATE_VAL_D7;
      VL_FSTATE_VAL_D8,    PARAM.FSTATE_VAL_D8;
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
COLLECTION no_download_mdo
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_mdo
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
