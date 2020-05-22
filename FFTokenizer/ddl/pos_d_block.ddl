/*
** @(#)pos_d_block.ddl      1.0	2009-06-15
**
** FF Standard Advanced Discrete Positioner Transducer Block
** Filename: pos_d_block.ddl
** Spec revision:   FF-900 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.1  Transducer Block Common Structures
**                  FF-906 FS 1.0  Positioner Transducer Block
**                  
** Date of last change: 2009-06-15
** Description:
** 	Standard Advanced Discrete Positioner Basic Device
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
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Standard Advanced Discrete Positioner Transducer Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __POS_DISCRETE,
DEVICE_REVISION __POS_DISCRETE_rel_dev_rev,
DD_REVISION     __POS_DISCRETE_rel_dd_rev

/*
**********************************************************************
** Block definition
**********************************************************************
*/
BLOCK   __pos_d_xdcr_block
{
        CHARACTERISTICS		__pos_d_xdcr_character ;
        LABEL                   [pos_d_xdcr_block] ;
        HELP                    [pos_d_xdcr_block_help] ;
        PARAMETERS
        {
                ST_REV,		__st_rev ;
		TAG_DESC,		__tag_desc ;
		STRATEGY,		__strategy ;
		ALERT_KEY,		__alert_key ;
		MODE_BLK,		__mode_blk ;
		BLOCK_ERR,		__block_err ;
		UPDATE_EVT,		__update_evt ;
		BLOCK_ALM,		__block_alm ;
		TRANSDUCER_DIRECTORY,		__transducer_directory ;
		TRANSDUCER_TYPE,		__transducer_type ;
		TRANSDUCER_TYPE_VER,		__transducer_type_ver ;
		XD_ERROR,		__xd_error ;
		COLLECTION_DIRECTORY,		__collection_directory ;
		FINAL_VALUE_D,		__final_value_d ;
		FINAL_POSITION_VALUE_D,		__final_position_value_d ;
		WORKING_POS_D,		__working_pos_d ;
		WORKING_SP_D,		__working_sp_d ;
		XD_FSTATE_VAL_D,		__xd_fstate_val_d ;
		XD_FSTATE_OPT,		__xd_fstate_opt ;
		CYCLE_CNTR,		__cycle_cntr ;
		SIGNAL_ACTION,		__signal_action ;
		READBACK_SELECT,		__readback_select ;
		XD_COMMAND,		__xd_command ;
		XD_COMMAND_STATE,		__xd_command_state ;
		ACT_FAIL_ACTION,		__act_fail_action ;
		ACT_MAN_ID,		__act_man_id ;
		ACT_MODEL_NUM,		__act_model_num ;
		ACT_SN,		__act_sn ;
		VALVE_MAN_ID,		__valve_man_id ;
		VALVE_MODEL_NUM,		__valve_model_num ;
		VALVE_SN,		__valve_sn ;
		VALVE_TYPE,		__valve_type ;
		XD_CAL_LOC,		__xd_cal_loc ;
		XD_CAL_DATE,		__xd_cal_date ;
		XD_CAL_WHO,		__xd_cal_who ;
		XD_OOS_OPT,		__xd_oos_opt ;
		POS_FEATURES,		__pos_features ;
	}
        PARAMETER_LISTS
        {
                VIEW_1, __pos_d_xdcr_view_1 ;
                VIEW_2, __pos_d_xdcr_view_2 ;
                VIEW_3, __pos_d_xdcr_view_3 ;
                VIEW_4, __pos_d_xdcr_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_pos_d_xdcr
		,upload_wanted_pos_d_xdcr
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __pos_d_xdcr_character
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
VARIABLE_LIST   __pos_d_xdcr_view_1
{
        LABEL           [pos_d_xdcr_view_1] ;
        HELP            [pos_d_xdcr_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,		PARAM.ST_REV ;
		VL_MODE_BLK,		PARAM.MODE_BLK ;
		VL_BLOCK_ERR,		PARAM.BLOCK_ERR ;
		VL_TRANSDUCER_TYPE,		PARAM.TRANSDUCER_TYPE ;
		VL_TRANSDUCER_TYPE_VER,		PARAM.TRANSDUCER_TYPE_VER ;
		VL_XD_ERROR,		PARAM.XD_ERROR ;
		VL_FINAL_VALUE_D,		PARAM.FINAL_VALUE_D ;
		VL_FINAL_POSITION_VALUE_D,		PARAM.FINAL_POSITION_VALUE_D ;
		VL_WORKING_POS_D,		PARAM.WORKING_POS_D ;
		VL_WORKING_SP_D,		PARAM.WORKING_SP_D ;
	}
}

VARIABLE_LIST   __pos_d_xdcr_view_2
{
        LABEL           [pos_d_xdcr_view_2] ;
        HELP            [pos_d_xdcr_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,		PARAM.ST_REV ;
		VL_TRANSDUCER_TYPE,		PARAM.TRANSDUCER_TYPE ;
		VL_TRANSDUCER_TYPE_VER,		PARAM.TRANSDUCER_TYPE_VER ;
		VL_XD_FSTATE_VAL_D,		PARAM.XD_FSTATE_VAL_D ;
		VL_XD_FSTATE_OPT,		PARAM.XD_FSTATE_OPT ;
		VL_READBACK_SELECT,		PARAM.READBACK_SELECT ;
		VL_XD_OOS_OPT,		PARAM.XD_OOS_OPT ;
		VL_POS_FEATURES,		PARAM.POS_FEATURES ;
	}
}

VARIABLE_LIST   __pos_d_xdcr_view_3
{
        LABEL           [pos_d_xdcr_view_3] ;
        HELP            [pos_d_xdcr_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,		PARAM.ST_REV ;
		VL_MODE_BLK,		PARAM.MODE_BLK ;
		VL_BLOCK_ERR,		PARAM.BLOCK_ERR ;
		VL_TRANSDUCER_TYPE,		PARAM.TRANSDUCER_TYPE ;
		VL_TRANSDUCER_TYPE_VER,		PARAM.TRANSDUCER_TYPE_VER ;
		VL_XD_ERROR,		PARAM.XD_ERROR ;
		VL_FINAL_VALUE_D,		PARAM.FINAL_VALUE_D ;
		VL_FINAL_POSITION_VALUE_D,		PARAM.FINAL_POSITION_VALUE_D ;
		VL_WORKING_POS_D,		PARAM.WORKING_POS_D ;
		VL_WORKING_SP_D,		PARAM.WORKING_SP_D ;
		VL_CYCLE_CNTR,		PARAM.CYCLE_CNTR ;
		VL_XD_COMMAND,		PARAM.XD_COMMAND ;
		VL_XD_COMMAND_STATE,		PARAM.XD_COMMAND_STATE ;
	}
}

VARIABLE_LIST   __pos_d_xdcr_view_4
{
        LABEL           [pos_d_xdcr_view_4] ;
        HELP            [pos_d_xdcr_view_4_help] ;
        MEMBERS
        {
                /* View 4_1 */
                VL_ST_REV,		PARAM.ST_REV ;
		VL_STRATEGY,		PARAM.STRATEGY ;
		VL_ALERT_KEY,		PARAM.ALERT_KEY ;
		VL_TRANSDUCER_TYPE,		PARAM.TRANSDUCER_TYPE ;
		VL_TRANSDUCER_TYPE_VER,		PARAM.TRANSDUCER_TYPE_VER ;
		VL_SIGNAL_ACTION,		PARAM.SIGNAL_ACTION ;
		VL_ACT_FAIL_ACTION,		PARAM.ACT_FAIL_ACTION ;
		VL_ACT_MAN_ID,		PARAM.ACT_MAN_ID ;
		VL_ACT_MODEL_NUM,		PARAM.ACT_MODEL_NUM ;
		
                /* View 4_2 */
        	VL_ST_REV_01,                   PARAM.ST_REV ;
                VL_ACT_SN,		PARAM.ACT_SN ;
		VL_VALVE_MAN_ID,		PARAM.VALVE_MAN_ID ;
		VL_VALVE_MODEL_NUM,		PARAM.VALVE_MODEL_NUM ;
		VL_VALVE_SN,		PARAM.VALVE_SN ;
		
                /* View 4_3 */
        	VL_ST_REV_02,                   PARAM.ST_REV ;
                VL_VALVE_TYPE,		PARAM.VALVE_TYPE ;
		VL_XD_CAL_LOC,		PARAM.XD_CAL_LOC ;
		VL_XD_CAL_DATE,		PARAM.XD_CAL_DATE ;
		VL_XD_CAL_WHO,		PARAM.XD_CAL_WHO ;
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
COLLECTION no_download_pos_d_xdcr
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_pos_d_xdcr
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
