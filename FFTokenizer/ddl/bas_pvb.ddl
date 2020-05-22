/*
** @(#)bas_pvb.ddl  0.93 06/25/2007
**
** FF Standard Basic Positioner Valve Basic Device Access
** Filename: bas_pvb.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.0  FBAP spec part 1
**                  FF-891 FS 1.0  FBAP spec part 2
**                  FF-906 PS 2.1  Positioner TB spec
** Date of last change: 2007-06-25
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
** (c) Fieldbus Foundation(TM) (1994-2007)
**
*/

/*
** HISTORY:
**  QLQ Revision 0.9    970812
**  DAD Revision 0.91beta  1999-03-04
**  FI  Revision 0.92   20051109
**      fixed view(s) per AR#766
**  FI  Revision 0.93  20070625
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
** Standard Basic Positioner Valve Basic Device Access(Output)
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __BASIC_POS_BASIC,
DEVICE_REVISION __BASIC_POS_BASIC_beta_dev_rev,
DD_REVISION     __BASIC_POS_BASIC_beta_dd_rev

/*
**********************************************************************
** Basic Positioner Valve Access to Basic Device
** Definition of standard basic positioner valve access
**********************************************************************
*/
BLOCK   __basic_pv_basic
{
    CHARACTERISTICS __bpvb_character ;
    LABEL           [bpv_basic_block] ;
    HELP            [bpv_basic_block_help] ;
    PARAMETERS
    {
        ST_REV,                 __st_rev ;
        TAG_DESC,               __tag_desc ;
        STRATEGY,               __strategy ;
        ALERT_KEY,              __alert_key ;
        MODE_BLK,               __mode_blk ;
        BLOCK_ERR,              __block_err ;
        UPDATE_EVT,             __update_evt ;
        BLOCK_ALM,              __block_alm ;
        TRANSDUCER_DIRECTORY,       __transducer_directory ;
        TRANSDUCER_TYPE,            __transducer_type ;
        XD_ERROR,                   __xd_error ;
        COLLECTION_DIRECTORY,       __collection_directory ;
        FINAL_VALUE,                __final_value ;
        FINAL_VALUE_RANGE,          __final_value_range ;
        FINAL_VALUE_CUTOFF_HI,      __final_value_cutoff_hi ;
        FINAL_VALUE_CUTOFF_LO,      __final_value_cutoff_lo ;
        FINAL_POSITION_VALUE,       __final_position_value ;       
        ACT_FAIL_ACTION,            __act_fail_action ;
        ACT_MAN_ID,                 __act_man_id ;
        ACT_MODEL_NUM,              __act_model_num ;
        ACT_SN,                     __act_sn ;
        VALVE_MAN_ID,               __valve_man_id ;
        VALVE_MODEL_NUM,            __valve_model_num ;
        VALVE_SN,                   __valve_sn ;
        VALVE_TYPE,                 __valve_type ;
        XD_CAL_LOC,                 __xd_cal_loc ;
        XD_CAL_DATE,                __xd_cal_date ;
        XD_CAL_WHO,                 __xd_cal_who ;      
    }
    PARAMETER_LISTS
    {
        VIEW_1, __bpvb_view_1 ;
        VIEW_2, __bpvb_view_2 ;
        VIEW_3, __bpvb_view_3 ;
        VIEW_4, __bpvb_view_4 ;
    }
    UNIT_ITEMS
    {
        __unit_bpvb_fvr
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_bpvb
    	,upload_wanted_bpvb
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __bpvb_character
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
VARIABLE_LIST   __bpvb_view_1
{
    LABEL       [bpvb_view_1] ;
    HELP        [bpvb_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_MODE_BLK,        PARAM.MODE_BLK ;
        VL_BLOCK_ERR,       PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE, PARAM.TRANSDUCER_TYPE ;
        VL_XD_ERROR,        PARAM.XD_ERROR ;
        VL_FINAL_VALUE,     PARAM.FINAL_VALUE ;
        VL_FINAL_POSITION_VALUE,     PARAM.FINAL_POSITION_VALUE ;        
    }
}

VARIABLE_LIST   __bpvb_view_2
{
    LABEL       [bpvb_view_2] ;
    HELP        [bpvb_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,              PARAM.ST_REV ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_FINAL_VALUE_RANGE,   PARAM.FINAL_VALUE_RANGE ;
    }
}

VARIABLE_LIST   __bpvb_view_3
{
    LABEL       [bpvb_view_3] ;
    HELP        [bpvb_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_MODE_BLK,        PARAM.MODE_BLK ;
        VL_BLOCK_ERR,       PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE, PARAM.TRANSDUCER_TYPE ;
        VL_XD_ERROR,        PARAM.XD_ERROR ;
        VL_FINAL_VALUE,     PARAM.FINAL_VALUE ;
        VL_FINAL_POSITION_VALUE,     PARAM.FINAL_POSITION_VALUE ;                    
    }
}

VARIABLE_LIST   __bpvb_view_4
{
    LABEL       [bpvb_view_4] ;
    HELP        [bpvb_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_STRATEGY,        PARAM.STRATEGY ;
        VL_ALERT_KEY,       PARAM.ALERT_KEY ;
        VL_TRANSDUCER_TYPE, PARAM.TRANSDUCER_TYPE ;
        VL_FINAL_VALUE_CUTOFF_HI,      PARAM.FINAL_VALUE_CUTOFF_HI ;
        VL_FINAL_VALUE_CUTOFF_LO,      PARAM.FINAL_VALUE_CUTOFF_HI ;        
        VL_ACT_FAIL_ACTION, PARAM.ACT_FAIL_ACTION ;
        VL_ACT_MAN_ID,      PARAM.ACT_MAN_ID ;
        VL_ACT_MODEL_NUM,   PARAM.ACT_MODEL_NUM ;
        VL_ACT_SN,          PARAM.ACT_SN ;
        VL_ST_REV_01,       PARAM.ST_REV ;
        VL_VALVE_MAN_ID,    PARAM.VALVE_MAN_ID ;
        VL_VALVE_MODEL_NUM, PARAM.VALVE_MODEL_NUM ;
        VL_VALVE_SN,        PARAM.VALVE_SN ;
        VL_VALVE_TYPE,      PARAM.VALVE_TYPE ;
        VL_ST_REV_02,       PARAM.ST_REV ;
        VL_XD_CAL_LOC,      PARAM.XD_CAL_LOC ;
        VL_XD_CAL_DATE,     PARAM.XD_CAL_DATE ;
        VL_XD_CAL_WHO,      PARAM.XD_CAL_WHO ;
    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_bpvb_fvr
{
    PARAM.FINAL_VALUE_RANGE.UNITS_INDEX:
        PARAM.FINAL_VALUE.VALUE,
        PARAM.FINAL_VALUE_RANGE.EU_100,
        PARAM.FINAL_VALUE_RANGE.EU_0
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
COLLECTION no_download_bpvb
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_bpvb
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
