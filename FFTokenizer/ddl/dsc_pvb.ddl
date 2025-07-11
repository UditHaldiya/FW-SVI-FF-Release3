/*
** @(#)dsc_pvb.ddl  0.92 2007-06-25
**
** FF Standard Discrete Positioner Valve Basic Device Access
** Filename: dsc_pvb.ddl
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
**  QLQ Revision 0.8    970812
**  DAD Revision 0.9beta 1999-03-04
**      new rev numering system for dev revb and dd rev
**  FI  Revision 0.91  20051109
**      fixed view(s) per AR#766
**  FI  Revision 0.92  20070625
**      updated per DPS x.x positioner specification
**  FI  Revision 1.2 20071113
**      updated per DPS 3.0.1 positioner specification
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
** Standard Discrete Positioner Valve Basic Device Access(Output)
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DISC_POS_BASIC,
DEVICE_REVISION __DISC_POS_BASIC_beta_dev_rev,
DD_REVISION     __DISC_POS_BASIC_beta_dd_rev

/*
**********************************************************************
** Discrete Positioner Valve Access to Basic Device
** Definition of standard discrete positioner valve access
**********************************************************************
*/
BLOCK   __discrete_pv_basic
{
    CHARACTERISTICS __dpvb_character ;
    LABEL           [dpv_basic_block] ;
    HELP            [dpv_basic_block_help] ;
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
        TRANSDUCER_TYPE_VER,        __transducer_type_ver;
        XD_ERROR,                   __xd_error ;
        COLLECTION_DIRECTORY,       __collection_directory ;
        FINAL_VALUE_D,              __final_value_d ;
        FINAL_POSITION_VALUE_D,     __final_position_value_d ;
        WORKING_POS_D,              __working_pos_d ;
        WORKING_SP_D,               __working_sp_d ;
        XD_FSTATE_VAL_D,            __xd_fstate_val_d ;
        XD_FSTATE_OPT,              __xd_fstate_opt ;
        CYCLE_CNTR,                 __cycle_cntr ;
        SIGNAL_ACTION,              __signal_action ;
        READBACK_SELECT,            __readback_select ;
        XD_COMMAND,                 __xd_command ;
        XD_COMMAND_STATE,           __xd_command_state ;
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
        VIEW_1, __dpvb_view_1 ;
        VIEW_2, __dpvb_view_2 ;
        VIEW_3, __dpvb_view_3 ;
        VIEW_4, __dpvb_view_4 ;
    }
    /* UNIT_ITEMS { NONE }  */
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_dpvb
    	,upload_wanted_dpvb
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __dpvb_character
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
VARIABLE_LIST   __dpvb_view_1
{
    LABEL       [dpvb_view_1] ;
    HELP        [dpvb_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_MODE_BLK,                PARAM.MODE_BLK ;
        VL_BLOCK_ERR,               PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE,         PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_XD_ERROR,                PARAM.XD_ERROR ;
        VL_FINAL_VALUE_D,           PARAM.FINAL_VALUE_D ;
        VL_FINAL_POSITION_VALUE_D,  PARAM.FINAL_POSITION_VALUE_D ;
        VL_WORKING_POS_D,           PARAM.WORKING_POS_D ;
        VL_WORKING_SP_D,            PARAM.WORKING_SP_D ;
    }
}

VARIABLE_LIST   __dpvb_view_2
{
    LABEL       [dpvb_view_2] ;
    HELP        [dpvb_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,               PARAM.ST_REV ;
        VL_TRANSDUCER_TYPE,      PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,  PARAM.TRANSDUCER_TYPE_VER ;
        VL_XD_FSTATE_VAL_D,      PARAM.XD_FSTATE_VAL_D ;
        VL_XD_FSTATE_OPT,        PARAM.XD_FSTATE_OPT ;
        VL_READBACK_SELECT,      PARAM.READBACK_SELECT ;
    }
}

VARIABLE_LIST   __dpvb_view_3
{
    LABEL       [dpvb_view_3] ;
    HELP        [dpvb_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_MODE_BLK,                PARAM.MODE_BLK ;
        VL_BLOCK_ERR,               PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE,         PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_XD_ERROR,                PARAM.XD_ERROR ;
        VL_FINAL_VALUE_D,           PARAM.FINAL_VALUE_D ;
        VL_FINAL_POSITION_VALUE_D,  PARAM.FINAL_POSITION_VALUE_D ;
        VL_WORKING_POS_D,           PARAM.WORKING_POS_D ;
        VL_WORKING_SP_D,            PARAM.WORKING_SP_D ;
        VL_CYCLE_CNTR,              PARAM.CYCLE_CNTR ;
        VL_XD_COMMAND,              PARAM.XD_COMMAND ;
        VL_XD_COMMAND_STATE,        PARAM.XD_COMMAND_STATE ;
    }
}

VARIABLE_LIST   __dpvb_view_4
{
    LABEL       [dpvb_view_4] ;
    HELP        [dpvb_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,               PARAM.ST_REV ;
        VL_STRATEGY,             PARAM.STRATEGY ;
        VL_ALERT_KEY,            PARAM.ALERT_KEY ;
        VL_TRANSDUCER_TYPE,      PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,  PARAM.TRANSDUCER_TYPE_VER ;
        VL_SIGNAL_ACTION,        PARAM.SIGNAL_ACTION ;
        VL_ACT_FAIL_ACTION,      PARAM.ACT_FAIL_ACTION ;
        VL_ACT_MAN_ID,           PARAM.ACT_MAN_ID ;
        VL_ACT_MODEL_NUM,        PARAM.ACT_MODEL_NUM ;
        VL_ST_REV_01,            PARAM.ST_REV ;
        VL_ACT_SN,               PARAM.ACT_SN ;
        VL_VALVE_MAN_ID,         PARAM.VALVE_MAN_ID ;
        VL_VALVE_MODEL_NUM,      PARAM.VALVE_MODEL_NUM ;
        VL_VALVE_SN,             PARAM.VALVE_SN ;
        VL_ST_REV_02,            PARAM.ST_REV ;
        VL_VALVE_TYPE,           PARAM.VALVE_TYPE ;
        VL_XD_CAL_LOC,           PARAM.XD_CAL_LOC ;
        VL_XD_CAL_DATE,          PARAM.XD_CAL_DATE ;
        VL_XD_CAL_WHO,           PARAM.XD_CAL_WHO ;
    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/* NONE */
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
COLLECTION no_download_dpvb
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_dpvb
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
