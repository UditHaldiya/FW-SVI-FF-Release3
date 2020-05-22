/*
** @(#)press_cb.ddl 0.9beta 1999-03-04
**
** FF Standard Pressure with Calibration for Basic Device Access
** Filename: pres_cb.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.0  FBAP spec part 1
**                  FF-891 FS 1.0  FBAP spec part 2
**                  FF-903 PS 2.0  TB spec part 2
** Date of last change: 2005-11-09
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
**  QLQ Revision 0.8    970820
**  DAD Revision 0.9beta 1999-03-04
**      added new numbering system for dev rev and dd rev
**  TAB Revision 1.0    20051109
**      changed device revision and dd revision to release revisions
**      fixed views according to ARs 766 and 620
**      fixed unit relations according to AR#1748
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
** Pressure with Calibration for Basic Device Access(Input)
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __PRESS_BASIC,
DEVICE_REVISION __PRESS_BASIC_rel_dev_rev,
DD_REVISION     __PRESS_BASIC_rel_dd_rev

/*
**********************************************************************
** Pressure with Calibration for Basic Device
** Definition of standard pressure with calibration access
**********************************************************************
*/
BLOCK   __pressure_cal_basic
{
    CHARACTERISTICS __pcb_character ;
    LABEL                  [pressure_basic_block] ;
    HELP                   [pressure_basic_block_help] ;
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
        PRIMARY_VALUE_TYPE,         __primary_value_type ;
        PRIMARY_VALUE,              __primary_value ;
        PRIMARY_VALUE_RANGE,        __primary_value_range ;
        CAL_POINT_HI,               __cal_point_hi ;
        CAL_POINT_LO,               __cal_point_lo ;
        CAL_MIN_SPAN,               __cal_min_span ;
        CAL_UNIT,                   __cal_unit ;
        SENSOR_TYPE,                __sensor_type ;
        SENSOR_RANGE,               __sensor_range ;
        SENSOR_SN,                  __sensor_sn ;
        SENSOR_CAL_METHOD,          __sensor_cal_method ;
        SENSOR_CAL_LOC,             __sensor_cal_loc ;
        SENSOR_CAL_DATE,            __sensor_cal_date ;
        SENSOR_CAL_WHO,             __sensor_cal_who ;
        SENSOR_ISOLATOR_MTL,        __sensor_isolator_mtl ;
        SENSOR_FILL_FLUID,          __sensor_fill_fluid ;
        SECONDARY_VALUE,            __secondary_value ;
        SECONDARY_VALUE_UNIT,       __secondary_value_unit ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __pcb_view_1 ;
        VIEW_2, __pcb_view_2 ;
        VIEW_3, __pcb_view_3 ;
        VIEW_4, __pcb_view_4 ;
    }
    UNIT_ITEMS
    {
        __unit_pcb_cal_unit,
        __unit_pcb_sensor_range,
        __unit_pcb_primary_val_unit,
        __unit_pcb_second_val_unit
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_pcb
    	,upload_wanted_pcb
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __pcb_character
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
VARIABLE_LIST   __pcb_view_1
{
    LABEL       [pcb_view_1] ;
    HELP        [pcb_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_MODE_BLK,        PARAM.MODE_BLK ;
        VL_BLOCK_ERR,       PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE, PARAM.TRANSDUCER_TYPE ;
        VL_XD_ERROR,        PARAM.XD_ERROR ;
        VL_PRIMARY_VALUE,   PARAM.PRIMARY_VALUE ;
        VL_SECONDARY_VALUE, PARAM.SECONDARY_VALUE ;
    }
}

VARIABLE_LIST   __pcb_view_2
{
    LABEL       [pcb_view_2] ;
    HELP        [pcb_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_TRANSDUCER_TYPE,         PARAM.TRANSDUCER_TYPE ;
        VL_PRIMARY_VALUE_TYPE,      PARAM.PRIMARY_VALUE_TYPE ;
        VL_CAL_POINT_HI,            PARAM.CAL_POINT_HI ;
        VL_CAL_POINT_LO,            PARAM.CAL_POINT_LO ;
        VL_SECONDARY_VALUE_UNIT,    PARAM.SECONDARY_VALUE_UNIT ;
    }
}

VARIABLE_LIST   __pcb_view_3
{
    LABEL       [pcb_view_3] ;
    HELP        [pcb_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,              PARAM.ST_REV ;
        VL_MODE_BLK,            PARAM.MODE_BLK ;
        VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_XD_ERROR,            PARAM.XD_ERROR ;
        VL_PRIMARY_VALUE,       PARAM.PRIMARY_VALUE ;
        VL_SECONDARY_VALUE,     PARAM.SECONDARY_VALUE ;
    }
}

VARIABLE_LIST   __pcb_view_4
{
    LABEL       [pcb_view_4] ;
    HELP        [pcb_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_STRATEGY,                PARAM.STRATEGY ;
        VL_ALERT_KEY,               PARAM.ALERT_KEY ;
        VL_TRANSDUCER_TYPE,         PARAM.TRANSDUCER_TYPE ;
        VL_PRIMARY_VALUE_RANGE,     PARAM.PRIMARY_VALUE_RANGE ;
        VL_CAL_MIN_SPAN,            PARAM.CAL_MIN_SPAN ;
        VL_CAL_UNIT,                PARAM.CAL_UNIT ;
        VL_SENSOR_TYPE,             PARAM.SENSOR_TYPE ;
        VL_SENSOR_RANGE,            PARAM.SENSOR_RANGE ;
        VL_SENSOR_ISOLATOR_MTL,     PARAM.SENSOR_ISOLATOR_MTL ;
        VL_SENSOR_FILL_FLUID,       PARAM.SENSOR_FILL_FLUID ;        
        VL_ST_REV_01,               PARAM.ST_REV;        
        VL_SENSOR_SN,               PARAM.SENSOR_SN ;
        VL_SENSOR_CAL_METHOD,       PARAM.SENSOR_CAL_METHOD ;
        VL_SENSOR_CAL_LOC,          PARAM.SENSOR_CAL_LOC ;
        VL_SENSOR_CAL_DATE,         PARAM.SENSOR_CAL_DATE ;
        VL_SENSOR_CAL_WHO,          PARAM.SENSOR_CAL_WHO ;


    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_pcb_cal_unit
{
    PARAM.CAL_UNIT :
        PARAM.CAL_MIN_SPAN,
        PARAM.CAL_POINT_HI,
        PARAM.CAL_POINT_LO
}
UNIT    __unit_pcb_sensor_range
{
        PARAM.SENSOR_RANGE.UNITS_INDEX :
        PARAM.SENSOR_RANGE.EU_100,
        PARAM.SENSOR_RANGE.EU_0
}
UNIT    __unit_pcb_primary_val_unit
{
     PARAM.PRIMARY_VALUE_RANGE.UNITS_INDEX :
        PARAM.PRIMARY_VALUE_RANGE.EU_100,
        PARAM.PRIMARY_VALUE_RANGE.EU_0,
        PARAM.PRIMARY_VALUE.VALUE
}
UNIT    __unit_pcb_second_val_unit
{
     PARAM.SECONDARY_VALUE_UNIT :
        PARAM.SECONDARY_VALUE.VALUE
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
COLLECTION no_download_pcb
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_pcb
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
