/*
** @(#)ft_block.ddl    1.0 2011-04-25

**
** FF standard Flow Totalizer block
** Filename: ft_block.ddl
** Spec revision:       FF-892 FS 1.10 FBAP spec part 3
**                      
** Date of last change: 2011-04-25
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
** (c) Fieldbus Foundation(TM) (2008)
**
*/

/*
** HISTORY:
** FI    Revision 1.0  20080616
** MS   ARs 2901 -- 2008.10.07
** MS   ARs 4200, 4201, 4205 -- 2009.06.15
** MS   ARs 4658 -- 2010.07.14

*/
/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Flow Totalizer block
**********************************************************************
*/
MANUFACTURER      __FF,
DEVICE_TYPE       __FLOW_TOTALIZER,
DEVICE_REVISION   __FLOW_TOTALIZER_rel_dev_rev,
DD_REVISION       __FLOW_TOTALIZER_rel_dd_rev
/*
**********************************************************************
** Integrator
** Definition of Flow Totalizer Block
**********************************************************************
*/
BLOCK   __flow_totalizer
{
   CHARACTERISTICS   __ft_character ;
   LABEL             [flow_totalizer_block] ;
   HELP              [flow_totalizer_block_help] ;
   PARAMETERS
   {
      ST_REV,                    __st_rev ;
      TAG_DESC,                  __tag_desc ;
      STRATEGY,                  __strategy ;
      ALERT_KEY,                 __alert_key ;
      MODE_BLK,                  __mode_blk ;
      BLOCK_ERR,                 __block_err ;
      TOTAL_SP,                  __total_sp ;
      PV,                        __pv;
      OUT,                       __out ;
      SIMULATE,                  __simulate_float ;
      XD_RANGE,                  __xd_range;
      OUT_RANGE,                 __out_range ;
      GRANT_DENY,                __grant_deny ;
      TOTALIZER_OPTS,            __totalizer_opts ;
      FAILURE_OPTS,              __failure_opts ;
      #ifdef LIB2
      IO_OPTS,                   __io_opts ;
      STATUS_OPTS,               __status_opts ;
      #else
      IO_OPTS,                   __io_opts_ai ;
      STATUS_OPTS,               __status_opts_tot ;
      #endif
      CHANNEL,                   __channel ;
      RESET_IN,                  __reset_in ;
      PRESET_IN,                 __preset_in ;
      OUT_TRIP,                  __out_trip ;
      OUT_PTRIP,                 __out_ptrip ;
      PRE_TRIP,                  __pre_trip ;
      UPDATE_EVT,                __update_evt ;
      BLOCK_ALM,                 __block_alm ;
      ALARM_SUM,                 __alarm_sum_ft ;
      ACK_OPTION,                __ack_option_ft ;
      ALARM_HYS,                 __alarm_hys ;
      HI_PRI,                    __hi_pri ;
      HI_LIM,                    __hi_lim ;
      LO_PRI,                    __lo_pri ;
      LO_LIM,                    __lo_lim ;
      HI_ALM,                    __hi_alm ;
      LO_ALM,                    __lo_alm ;
      BLOCK_ERR_DESC_1,           __block_err_desc_1_tot ;
   }
   
   PARAMETER_LISTS
   {
      VIEW_1, __ft_view_1 ;
      VIEW_2, __ft_view_2 ;
      VIEW_3, __ft_view_3 ;
      VIEW_4, __ft_view_4 ;
   }
   
   UNIT_ITEMS
   {
      __unit_ft_xd,
      __unit_ft_out
   }
   
   #ifdef UD_LISTS
   COLLECTION_ITEMS
   {
   	no_download_ft
   	,upload_wanted_ft
   }
   #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ft_character
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
VARIABLE_LIST   __ft_view_1
{
   LABEL           [ft_view_1] ;
   HELP            [ft_view_1_help] ;
   MEMBERS
   {
      VL_ST_REV,                 PARAM.ST_REV ;
      VL_MODE_BLK,               PARAM.MODE_BLK ;
      VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
      VL_TOTAL_SP,               PARAM.TOTAL_SP ;
      VL_PV,                     PARAM.PV ;
      VL_OUT,                    PARAM.OUT ;
      VL_RESET_IN,               PARAM.RESET_IN ;
      VL_PRESET_IN,              PARAM.PRESET_IN ;
      VL_OUT_TRIP,		 PARAM.OUT_TRIP;
      VL_OUT_PTRIP,		 PARAM.OUT_PTRIP;
      VL_ALARM_SUM,              PARAM.ALARM_SUM ;
      VL_BLOCK_ERR_DESC_1, PARAM.BLOCK_ERR_DESC_1 ;
   }
}

VARIABLE_LIST   __ft_view_2
{
   LABEL           [ft_view_2] ;
   HELP            [ft_view_2_help] ;
   MEMBERS
   {
      VL_ST_REV,                 PARAM.ST_REV ;
      VL_XD_RANGE,               PARAM.XD_RANGE ;
      VL_OUT_RANGE,              PARAM.OUT_RANGE ;
      VL_GRANT_DENY,             PARAM.GRANT_DENY ;
   }
}

VARIABLE_LIST   __ft_view_3
{
   LABEL           [ft_view_3] ;
   HELP            [ft_view_3_help] ;
   MEMBERS
   {
      VL_ST_REV,                 PARAM.ST_REV ;
      VL_MODE_BLK,               PARAM.MODE_BLK ;
      VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
      VL_TOTAL_SP,               PARAM.TOTAL_SP ;
      VL_PV,                     PARAM.PV ;
      VL_OUT,                    PARAM.OUT ;
      VL_RESET_IN,               PARAM.RESET_IN ;
      VL_PRESET_IN,              PARAM.PRESET_IN ;
      VL_OUT_TRIP,		 PARAM.OUT_TRIP;
      VL_OUT_PTRIP,		 PARAM.OUT_PTRIP;
      VL_ALARM_SUM,              PARAM.ALARM_SUM ;
      VL_BLOCK_ERR_DESC_1, PARAM.BLOCK_ERR_DESC_1 ;
   }
}

VARIABLE_LIST   __ft_view_4
{
   LABEL           [ft_view_4] ;
   HELP            [ft_view_4_help] ;
   MEMBERS
   {
      VL_ST_REV,                 PARAM.ST_REV ;
      VL_STRATEGY,               PARAM.STRATEGY ;
      VL_ALERT_KEY,              PARAM.ALERT_KEY ;
      VL_TOTALIZER_OPTS,         PARAM.TOTALIZER_OPTS ;
      VL_FAILURE_OPTS,           PARAM.FAILURE_OPTS ;
      VL_IO_OPTS,                PARAM.IO_OPTS ;
      VL_STATUS_OPTS,            PARAM.STATUS_OPTS ; 
      VL_CHANNEL,                PARAM.CHANNEL ;
      VL_PRE_TRIP,               PARAM.PRE_TRIP ;
      VL_ACK_OPTION,             PARAM.ACK_OPTION ;
      VL_ALARM_HYS,              PARAM.ALARM_HYS ;
      VL_HI_PRI,                 PARAM.HI_PRI ;
      VL_HI_LIM,                 PARAM.HI_LIM ;
      VL_LO_PRI,                 PARAM.LO_PRI ;
      VL_LO_LIM,                 PARAM.LO_LIM ;
   }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT  __unit_ft_xd
{
   PARAM.XD_RANGE.UNITS_INDEX : PARAM.SIMULATE.TRANSDUCER_VALUE,
   PARAM.SIMULATE.SIMULATE_VALUE,
   PARAM.XD_RANGE.EU_100,
   PARAM.XD_RANGE.EU_0
}
           
UNIT  __unit_ft_out
{
   PARAM.OUT_RANGE.UNITS_INDEX : PARAM.TOTAL_SP,
   PARAM.PV.VALUE,
   PARAM.OUT.VALUE,
   PARAM.OUT_SCALE.EU_100,
   PARAM.OUT_SCALE.EU_0,
   PARAM.PRESET_IN.VALUE,
   PARAM.PRE_TRIP,
   PARAM.HI_LIM,
   PARAM.LO_LIM,
   PARAM.HI_ALM.VALUE,
   PARAM.LO_ALM.VALUE
}

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
COLLECTION no_download_ft
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ft
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
