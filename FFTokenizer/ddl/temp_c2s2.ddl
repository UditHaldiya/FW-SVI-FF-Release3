/*
** @(#)temp_c2s2.ddl	1.0	2011-04-22
**
** Standard Temperature with Calibration Two Sensor Device Access 2
** Filename: temp_c2s2.ddl
** Spec revision:   FF-904 FS 2.0
**
** Date of last change: 2011-04-22
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
** (c) Fieldbus Foundation(TM) (1994-2011)
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
** Standard Temperature with Calibration Two Sensor Device Access(Input)
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __TEMPERATURE_BASIC_2_SENSOR2,
DEVICE_REVISION __TEMPERATURE_BASIC_2_SENSOR2_rel_dev_rev,
DD_REVISION     __TEMPERATURE_BASIC_2_SENSOR2_rel_dd_rev

/*
**********************************************************************
** Standard Temperature with Calibration Two Sensor Device
** Definition of standard temperature with calibration two sensor device access
**********************************************************************
*/
BLOCK   __temperature_cal_basic_2_sensor2
{
    CHARACTERISTICS         __tc2s2_character ;
    LABEL                  [temperature_basic_2_sensor_block2] ;
    HELP                   [temperature_basic_2_sensor_help] ;
    PARAMETERS
    {
        ST_REV,                     __st_rev ;
        TAG_DESC,                   __tag_desc ;
        STRATEGY,                   __strategy ;
        ALERT_KEY,                  __alert_key ;
        MODE_BLK,                   __mode_blk ;
        BLOCK_ERR,                  __block_err ;
        UPDATE_EVT,                 __update_evt ;
        BLOCK_ALM,                  __block_alm ;
        TRANSDUCER_DIRECTORY,       __transducer_directory ;
        TRANSDUCER_TYPE,            __transducer_type ;
        TRANSDUCER_TYPE_VER,        __transducer_type_ver ;
        XD_ERROR,                   __xd_error ;
        COLLECTION_DIRECTORY,       __collection_directory ;
        PRIMARY_VALUE_TYPE_1,       __primary_value_type_1 ;
        PRIMARY_VALUE_1,            __primary_value_1 ;
        PRIMARY_VALUE_RANGE_1,      __primary_value_range_1 ;
        CAL_POINT_HI_1,             __cal_point_hi_1 ;
        CAL_POINT_LO_1,             __cal_point_lo_1 ;
        CAL_MIN_SPAN_1,             __cal_min_span_1 ;
        CAL_VALUE_1,                  __cal_value_1 ;
        CAL_UNIT_1,                 __cal_unit_1 ;
        XD_OPTS,                    __xd_opts ;
        SENSOR_TYPE_1,              __sensor_type_1 ;
        SENSOR_RANGE_1,             __sensor_range_1 ;
        SENSOR_SN_1,                __sensor_sn_1 ;
        SENSOR_CAL_METHOD_1,        __sensor_cal_method_1 ;
        SENSOR_CAL_LOC_1,           __sensor_cal_loc_1 ;
        SENSOR_CAL_DATE_1,          __sensor_cal_date_1 ;
        SENSOR_CAL_WHO_1,           __sensor_cal_who_1 ;
        SENSOR_CONNECTION_1,        __sensor_connection_1;
        PRIMARY_VALUE_TYPE_2,       __primary_value_type_2 ;
        PRIMARY_VALUE_2,            __primary_value_2 ;
        PRIMARY_VALUE_RANGE_2,      __primary_value_range_2 ;
        CAL_POINT_HI_2,             __cal_point_hi_2 ;
        CAL_POINT_LO_2,             __cal_point_lo_2 ;
        CAL_MIN_SPAN_2,             __cal_min_span_2 ;
        CAL_VALUE_2,                  __cal_value_2 ;
        CAL_UNIT_2,                 __cal_unit_2 ;
        SENSOR_TYPE_2,              __sensor_type_2 ;
        SENSOR_RANGE_2,             __sensor_range_2 ;
        SENSOR_SN_2,                __sensor_sn_2 ;
        SENSOR_CAL_METHOD_2,        __sensor_cal_method_2 ;
        SENSOR_CAL_LOC_2,           __sensor_cal_loc_2 ;
        SENSOR_CAL_DATE_2,          __sensor_cal_date_2 ;
        SENSOR_CAL_WHO_2,           __sensor_cal_who_2 ;
        SENSOR_CONNECTION_2,        __sensor_connection_2;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __tc2s2_view_1 ;
        VIEW_2, __tc2s2_view_2 ;
        VIEW_3, __tc2s2_view_3 ;
        VIEW_4, __tc2s2_view_4 ;
    }
    UNIT_ITEMS
    {
        __unit_tc2s2_cal_unit_1,
        __unit_tc2s2_sensor_range_1,
        __unit_tc2s2_primary_val_1,
        __unit_tc2s2_cal_unit_2,
        __unit_tc2s2_sensor_range_2,
        __unit_tc2s2_primary_val_2
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_tc2s2
    	,upload_wanted_tc2s2
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __tc2s2_character
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
VARIABLE_LIST   __tc2s2_view_1
{
    LABEL       [tc2s_view_1] ;
    HELP        [tc2s_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_MODE_BLK,                PARAM.MODE_BLK ;
        VL_BLOCK_ERR,               PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_XD_ERROR,                PARAM.XD_ERROR ;
        VL_PRIMARY_VALUE_1,         PARAM.PRIMARY_VALUE_1 ;
        VL_CAL_VALUE_1,           PARAM.CAL_VALUE_1;
        VL_PRIMARY_VALUE_2,         PARAM.PRIMARY_VALUE_2 ;
        VL_CAL_VALUE_2,           PARAM.CAL_VALUE_2;
    }
}

VARIABLE_LIST   __tc2s2_view_2
{
    LABEL       [tc2s_view_2] ;
    HELP        [tc2s_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_PRIMARY_VALUE_TYPE_1,    PARAM.PRIMARY_VALUE_TYPE_1 ;
        VL_CAL_POINT_HI_1,          PARAM.CAL_POINT_HI_1 ;
        VL_CAL_POINT_LO_1,          PARAM.CAL_POINT_LO_1 ;
        VL_XD_OPTS,               PARAM.XD_OPTS ;
        VL_PRIMARY_VALUE_TYPE_2,    PARAM.PRIMARY_VALUE_TYPE_2 ;
        VL_CAL_POINT_HI_2,          PARAM.CAL_POINT_HI_2 ;
        VL_CAL_POINT_LO_2,          PARAM.CAL_POINT_LO_2 ;
    }
}

VARIABLE_LIST   __tc2s2_view_3
{
    LABEL       [tc2s_view_3] ;
    HELP        [tc2s_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_MODE_BLK,                PARAM.MODE_BLK ;
        VL_BLOCK_ERR,               PARAM.BLOCK_ERR ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_XD_ERROR,                PARAM.XD_ERROR ;
        VL_PRIMARY_VALUE_1,         PARAM.PRIMARY_VALUE_1 ;
        VL_CAL_VALUE_1,           PARAM.CAL_VALUE_1;
        VL_PRIMARY_VALUE_2,         PARAM.PRIMARY_VALUE_2 ;
        VL_CAL_VALUE_2,           PARAM.CAL_VALUE_2;
    }
}

VARIABLE_LIST   __tc2s2_view_4
{
    LABEL       [tc2s_view_4] ;
    HELP        [tc2s_view_4_help] ;
    MEMBERS
    {
        /* View 4_1 */
        VL_ST_REV,                  PARAM.ST_REV ;
        VL_STRATEGY,                PARAM.STRATEGY ;
        VL_ALERT_KEY,               PARAM.ALERT_KEY ;
        VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE ;
        VL_TRANSDUCER_TYPE_VER,     PARAM.TRANSDUCER_TYPE_VER ;
        VL_PRIMARY_VALUE_RANGE_1,   PARAM.PRIMARY_VALUE_RANGE_1 ;
        VL_CAL_MIN_SPAN_1,          PARAM.CAL_MIN_SPAN_1 ;
        VL_CAL_UNIT_1,              PARAM.CAL_UNIT_1 ;
        VL_SENSOR_TYPE_1,           PARAM.SENSOR_TYPE_1 ;
        VL_SENSOR_RANGE_1,          PARAM.SENSOR_RANGE_1 ;
        VL_SENSOR_SN_1,             PARAM.SENSOR_SN_1 ;
        VL_SENSOR_CAL_METHOD_1,     PARAM.SENSOR_CAL_METHOD_1 ;                

        /* View 4_2 */
        VL_ST_REV_01,               PARAM.ST_REV ;
        VL_SENSOR_CAL_LOC_1,        PARAM.SENSOR_CAL_LOC_1 ;
	VL_SENSOR_CAL_DATE_1,       PARAM.SENSOR_CAL_DATE_1 ;
        VL_SENSOR_CAL_WHO_1,        PARAM.SENSOR_CAL_WHO_1 ;
        VL_SENSOR_CONNECTION_1,	    PARAM.SENSOR_CONNECTION_1 ;
        VL_PRIMARY_VALUE_RANGE_2,   PARAM.PRIMARY_VALUE_RANGE_2 ;
	VL_CAL_MIN_SPAN_2,          PARAM.CAL_MIN_SPAN_2 ;
	VL_CAL_UNIT_2,              PARAM.CAL_UNIT_2 ;
        VL_SENSOR_TYPE_2,           PARAM.SENSOR_TYPE_2 ;
        
        /* View 4_3 */
        VL_ST_REV_02,               PARAM.ST_REV ;
        VL_SENSOR_RANGE_2,          PARAM.SENSOR_RANGE_2 ;
	VL_SENSOR_SN_2,             PARAM.SENSOR_SN_2 ;
        VL_SENSOR_CAL_METHOD_2,     PARAM.SENSOR_CAL_METHOD_2 ;
	VL_SENSOR_CAL_LOC_2,        PARAM.SENSOR_CAL_LOC_2 ;
	VL_SENSOR_CAL_DATE_2,       PARAM.SENSOR_CAL_DATE_2;
        
        /* View 4_4 */
        VL_ST_REV_03,               PARAM.ST_REV ;
        VL_SENSOR_CAL_WHO_2,        PARAM.SENSOR_CAL_WHO_2 ;
	VL_SENSOR_CONNECTION_2,	    PARAM.SENSOR_CONNECTION_2 ;
     }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_tc2s2_cal_unit_1
{
    PARAM.CAL_UNIT_1 :
    PARAM.CAL_MIN_SPAN_1,
    PARAM.CAL_POINT_HI_1,
    PARAM.CAL_POINT_LO_1
}
UNIT    __unit_tc2s2_sensor_range_1
{
    PARAM.SENSOR_RANGE_1.UNITS_INDEX :
    PARAM.SENSOR_RANGE_1.EU_100,
    PARAM.SENSOR_RANGE_1.EU_0
}
UNIT    __unit_tc2s2_primary_val_1
{
    PARAM.PRIMARY_VALUE_RANGE_1.UNITS_INDEX :
    PARAM.PRIMARY_VALUE_RANGE_1.EU_100,
    PARAM.PRIMARY_VALUE_RANGE_1.EU_0,
    PARAM.PRIMARY_VALUE_1.VALUE
}

UNIT    __unit_tc2s2_cal_unit_2
{
    PARAM.CAL_UNIT_2 :
    PARAM.CAL_MIN_SPAN_2,
    PARAM.CAL_POINT_HI_2,
    PARAM.CAL_POINT_LO_2
}
UNIT    __unit_tc2s2_sensor_range_2
{
    PARAM.SENSOR_RANGE_2.UNITS_INDEX :
    PARAM.SENSOR_RANGE_2.EU_100,
    PARAM.SENSOR_RANGE_2.EU_0
}
UNIT    __unit_tc2s2_primary_val_2
{
    PARAM.PRIMARY_VALUE_RANGE_2.UNITS_INDEX :
    PARAM.PRIMARY_VALUE_RANGE_2.EU_100,
    PARAM.PRIMARY_VALUE_RANGE_2.EU_0,
    PARAM.PRIMARY_VALUE_2.VALUE
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
COLLECTION no_download_tc2s2
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_tc2s2
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
