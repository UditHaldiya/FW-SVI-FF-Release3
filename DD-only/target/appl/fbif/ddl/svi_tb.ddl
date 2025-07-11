#define TS_TB_DD "Time-stamp: <2013-11-27 12:58:42 GE-300010777>"
/*
#+LINK: SVIFFDocs file:c:/Users/300010777/Desktop/FF Design Documents/
  Web Document:
  http://libraries.ge.com/download?fileid=439958398101&entity_id=24543915101&sid=101
  Loc. Document: [[SVIFFDocs:FF_Parameter_Mapping_TB_131031.xlsx][FF_Parameter_Mapping_TB.xlsx]]
*/

/*
 * Variable & Record Definitios for transducer block
 */
#include "builtins.h"

/*=====================================================================/
* define bits orders ( reversed for svi2 FF) (from svi_faults.h)
/=====================================================================*/
#define FBIT0 0x80
#define FBIT1 0x40
#define FBIT2 0x20
#define FBIT3 0x10
#define FBIT4 0x08
#define FBIT5 0x04
#define FBIT6 0x02
#define FBIT7 0x01

#include "stopsmethods.h"

/* Conditional cached and history alert values */
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)
#define AlertCachedVal ALERT, alert;
#else
#define AlertCachedVal
#endif

#if TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE)
#define AlertHistoryVal HISTORIC_ALERT, historic_alert;
#else
#define AlertHistoryVal
#endif

#define AlertExtras AlertCachedVal AlertHistoryVal
#include "svi_tb.h"
#include "faultdef_ff.h"
#include "svi_images.h"
#include "svi2_menus.h"


/*-----------------------------------/
** Defines all menus for TB_MENU_LIST
/-----------------------------------*/


/*-----------------------------/
** define the various relations
/-----------------------------*/

/* UNIT pv_unit_relation */
/* { */
/*     PARAM.FINAL_VALUE_RANGE.UNITS_INDEX: */
/*     PARAM.FINAL_VALUE.VALUE, */
/*     PARAM.FINAL_POSITION_VALUE.VALUE */
/* } */

UNIT pressure_unit_relation
{
  PARAM.PRESSURE_RANGE.UNITS_INDEX:
    PARAM.PRESSURE_RANGE.EU_100,
    PARAM.PRESSURE_RANGE.EU_0,
    PARAM.SUPPLY_PRESSURE.VALUE,
    PARAM.ACTUATOR_A_PRESSURE.VALUE,
    PARAM.ACTUATOR_B_PRESSURE.VALUE,
    PARAM.PILOT_PRESSURE.VALUE,
    PARAM.ATMOSPHERIC_PRESSURE.VALUE,
    PARAM.SUPPLY_PRESSURE_HI_ALERT.ALERT_POINT,
    PARAM.SUPPLY_PRESSURE_HI_ALERT.DEADBAND,
    PARAM.SUPPLY_PRESSURE_LOLO_ALERT.ALERT_POINT,
    PARAM.SUPPLY_PRESSURE_LOLO_ALERT.DEADBAND,
    PARAM.SUPPLY_PRESSURE_LO_ALERT.ALERT_POINT,
    PARAM.SUPPLY_PRESSURE_LO_ALERT.DEADBAND,
    PARAM.PRESSURE_EXTREMES.SUPPLY_PRESSURE_MAX,
    PARAM.PRESSURE_EXTREMES.SUPPLY_PRESSURE_MIN,
    PARAM.PRESSURE_EXTREMES.ACTUATOR_A_MAX,
    PARAM.PRESSURE_EXTREMES.ACTUATOR_A_MIN,
    PARAM.PRESSURE_EXTREMES.ACTUATOR_B_MAX,
    PARAM.PRESSURE_EXTREMES.ACTUATOR_B_MIN,
    PARAM.PRESSURE_EXTREMES.PILOT_MAX,
    PARAM.PRESSURE_EXTREMES.PILOT_MIN,
    PARAM.ACTUATOR_3.SUPPLY_PRS_MAX,
    PARAM.ACTUATOR_3.PRS_CONTROL_HI,
    PARAM.ACTUATOR_3.PRS_CONTROL_LO
}

UNIT working_sp_unit_relation
{
    PARAM.TRAVEL.UNITS_INDEX:
      PARAM.WORKING_SP.VALUE,
      PARAM.WORKING_POS.VALUE
}

UNIT travel_unit_relation
{
    PARAM.TRAVEL.UNITS_INDEX:
        PARAM.TRAVEL_ACCUMULATION_A_ALERT.TRAVEL_ACCUMULATION,
        PARAM.TRAVEL_ACCUMULATION_A_ALERT.INT_ALERT_POINT,
        PARAM.TRAVEL_ACCUMULATION_A_ALERT.DEADBAND_AB,
        PARAM.TRAVEL_ACCUMULATION_B_ALERT.TRAVEL_ACCUMULATION,
        PARAM.TRAVEL_ACCUMULATION_B_ALERT.INT_ALERT_POINT,
        PARAM.TRAVEL_ACCUMULATION_B_ALERT.DEADBAND_AB,
        PARAM.CYCLE_COUNTER_A_ALERT.CYCLE_COUNTER,
        PARAM.CYCLE_COUNTER_A_ALERT.INT_ALERT_POINT,
        PARAM.CYCLE_COUNTER_A_ALERT.DEADBAND_AB,
        PARAM.CYCLE_COUNTER_B_ALERT.CYCLE_COUNTER,
        PARAM.CYCLE_COUNTER_B_ALERT.INT_ALERT_POINT,
        PARAM.CYCLE_COUNTER_B_ALERT.DEADBAND_AB
}

/*---------------------------/
** Variables for common usage
/---------------------------*/


VARIABLE int_2_element
{
    LABEL           "|en|integer(2) element" ;
    CLASS           CONTAINED;
    TYPE            INTEGER (2) ;
}

VARIABLE int_element
{
    LABEL "|en|int element";
    CLASS CONTAINED;
    TYPE INTEGER;
}

int_2_element_r LIKE VARIABLE int_2_element
{
    REDEFINE  HANDLING READ;
}

METHOD scale_to_percent
{
    LABEL "scaled to percent";
    CLASS INPUT;
    DEFINITION
    {
        long percent;
        get_signed(&percent);
        percent = percent * 100 / 16384;
        put_signed(percent);
    }
}

METHOD scale_to_counts
{
    LABEL "scaled to counts";
    CLASS OUTPUT;
    DEFINITION
    {
        long counts;
        get_signed(&counts);
        counts = counts * 16384 / 100;
        put_signed(counts);
    }
}

#if 0
int_2_element_scaled LIKE  VARIABLE int_2_element
{

    REDEFINE PRE_WRITE_ACTIONS
    {
        scale_to_counts
    }
    REDEFINE POST_READ_ACTIONS
    {
        scale_to_percent
    }
}

int_2_element_scaled_r LIKE  VARIABLE int_2_element
{
    REDEFINE POST_READ_ACTIONS
    {
        scale_to_percent
    }
    REDEFINE HANDLING READ;
}

VARIABLE int_2_element_d
{
    LABEL           "|en|integer(2) with dynamic" ;
    CLASS           CONTAINED & DYNAMIC;
    TYPE            INTEGER (2) ;
}
#endif

VARIABLE uint_element
{
    LABEL           "|en|unsigned integer element" ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (1) ;
}

uint_element_r LIKE VARIABLE uint_element
{
    REDEFINE  HANDLING READ;
}

#if 0
VARIABLE uint_element_d
{
    LABEL           "|en|unsigned integer element" ;
    CLASS           CONTAINED & DYNAMIC;
    TYPE            UNSIGNED_INTEGER (1) ;
}
#endif

VARIABLE uint_2_element
{
    LABEL           "|en|unsigned integer element" ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
}

#if 0
uint_2_element_r LIKE VARIABLE uint_2_element
{
    REDEFINE  HANDLING READ;
}

uint_2_element_rd LIKE VARIABLE uint_2_element_d
{
    REDEFINE  HANDLING READ;
}
#endif

VARIABLE uint_2_element_d
{
    LABEL           "|en|unsigned integer element" ;
    CLASS           CONTAINED & DYNAMIC;
    TYPE            UNSIGNED_INTEGER (2) ;
}

#if 0
VARIABLE uint_4_element_r
{
    LABEL           "|en|unsigned integer(4) element" ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}
#endif

VARIABLE uint_4_element_nd
{
    LABEL           "|en|unsigned integer(4) element" ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
}

#if 0
VARIABLE uint_4_element_r_nd
{
    LABEL           "|en|unsigned integer(4) element" ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}
#endif

/* RECORD _position_alert */
/* { */
/*     LABEL LBL_POSITION_ALERT; */
/*     HELP  HLP5(HLP_POSITION_ALERT); */
/*     MEMBERS */
/*     { */
/*         POSITION,                           _position; */
/*         ALERT_POINT,                        _alert_point; */
/*         DEADBAND,                           _deadband; */
/*         ALERT,                              alert; */
/*         HISTORIC_ALERT,                     historic_alert; */
/*         ENABLE,                             enable; */
/*     } */
/* } */

VARIABLE _position
{
    LABEL LBL_POSITION;
    HELP  HLP5(HLP_POSITION);
    CLASS CONTAINED & DYNAMIC;
    TYPE FLOAT ;
    CONSTANT_UNIT [unit_code_1342];
    HANDLING READ;
}
VARIABLE _alert_point
{
    LABEL LBL_ALERT_POINT;
    HELP  HLP5(HLP_ALERT_POINT);
    CLASS CONTAINED;
    TYPE FLOAT ;
    CONSTANT_UNIT [unit_code_1342];

}
VARIABLE _deadband
{
    LABEL LBL_DEADBAND;
    HELP  HLP5(HLP_DEADBAND);
    CLASS CONTAINED;
    TYPE FLOAT ;
    CONSTANT_UNIT [unit_code_1342];

}


VARIABLE _direction
{
    LABEL "|en|Direction";
    HELP  HLP5(HLP_DIRECTION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_DIRECTION
    }
}

VARIABLE _function
{
    LABEL "|en|Function";
    HELP  HLP5(HLP_FUNCTION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_FUNCTION
    }
}


#if 0
			VARIABLE pos_percent_r
			{
			    LABEL LBL_POS_5_PERCENT_CLOSED;
			    HELP  HLP5(HLP_POS_5_PERCENT_CLOSED);
			    CLASS CONTAINED;
			    TYPE  FLOAT
			    {
			        DISPLAY_FORMAT "6.3f";
			    }
			    HANDLING READ;
			}

			pos_5_percent_closed_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_5_PERCENT_CLOSED;
			    REDEFINE HELP  HLP5(HLP_POS_5_PERCENT_CLOSED);
			}

			pos_10_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_10_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_10_PERCENT);
			}
			pos_20_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_20_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_20_PERCENT);
			}
			pos_30_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_30_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_30_PERCENT);
			}
			pos_40_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_40_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_40_PERCENT);
			}
			pos_50_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_50_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_50_PERCENT);
			}
			pos_60_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_60_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_60_PERCENT);
			}
			pos_70_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_70_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_70_PERCENT);
			}
			pos_80_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_80_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_80_PERCENT);
			}
			pos_90_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_90_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_90_PERCENT);
			}
			pos_95_percent_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_95_PERCENT;
			    REDEFINE HELP  HLP5(HLP_POS_95_PERCENT);
			}
			pos_95_percent_open_r LIKE VARIABLE pos_percent_r
			{
			    REDEFINE LABEL LBL_POS_95_PERCENT_OPEN;
			    REDEFINE HELP  HLP5(HLP_POS_95_PERCENT_OPEN);
			}
#endif


VARIABLE p
{
    LABEL LBL_P;
    HELP  HLP5(HLP_P);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MAX_VALUE 5000;
    }
    /*VALIDITY  NA  ;*/
}
VARIABLE i
{
    LABEL LBL_I;
    HELP  HLP5(HLP_I);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MAX_VALUE 1000;
    }
    /*VALIDITY  NA  ;*/
}
VARIABLE d
{
    LABEL LBL_D;
    HELP  HLP5(HLP_D);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MAX_VALUE 200;
    }
    /*VALIDITY  NA  ;*/
}
VARIABLE padj
{
    LABEL LBL_PADJ;
    HELP  HLP5(HLP_PADJ);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MIN_VALUE -3000;
        MAX_VALUE 3000;
    }

    /*VALIDITY  NA  ;*/
}
VARIABLE beta
{
    LABEL LBL_BETA;
    HELP  HLP5(HLP_BETA);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MIN_VALUE -9;
        MAX_VALUE 9;
    }

    /*VALIDITY  NA  ;*/
}
VARIABLE poscomp
{
    LABEL LBL_POSCOMP;
    HELP  HLP5(HLP_POSCOMP);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MIN_VALUE 2;
        MAX_VALUE 20;
    }

    /*VALIDITY  NA  ;*/
}
VARIABLE deadzone
{
    LABEL LBL_DEADZONE;
    HELP  HLP5(HLP_DEADZONE);
    CLASS CONTAINED;
    TYPE INTEGER (2)
    {
        MAX_VALUE 821;
    }

    /*VALIDITY  NA  ;*/
}
VARIABLE nonlin
{
    LABEL LBL_NONLIN;
    HELP  HLP5(HLP_NONLIN);
    CLASS CONTAINED;
    TYPE INTEGER (2)
	DATA_LIMITS(0, 20)
    /*VALIDITY  NA  ;*/
}

p_r LIKE VARIABLE p
{
    REDEFINE HANDLING READ;
}
i_r LIKE VARIABLE i
{
    REDEFINE HANDLING READ;
}
d_r LIKE VARIABLE d
{
    REDEFINE HANDLING READ;
}
padj_r LIKE VARIABLE padj
{
    REDEFINE HANDLING READ;
}
beta_r LIKE VARIABLE beta
{
    REDEFINE HANDLING READ;
}
poscomp_r LIKE VARIABLE poscomp
{
    REDEFINE HANDLING READ;
}
deadzone_r LIKE VARIABLE deadzone
{
    REDEFINE HANDLING READ;
}
nonlin_r LIKE VARIABLE nonlin
{
    REDEFINE HANDLING READ;
}

VARIABLE propagate_mode
{
    LABEL LBL_PROPAGATE_MODE;
    HELP  HLP5(HLP_PROPAGATE_MODE);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_PROPAGATE_MODE
    }
}

VARIABLE final_value_f
{
    LABEL           [value_label] ;
    HELP            HLP5(HLP_FINAL_VALUE);
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT;
    HANDLING
    IF ((PARAM.MODE_BLK.ACTUAL|PARAM.MODE_BLK.TARGET) & _AUTOMATIC ) {
        READ;
    }
    ELSE {
        READ & WRITE ;
    }
    CONSTANT_UNIT [unit_code_1342];
    /* DATA_LIMITS(-25,125) */
}

/* Unused
final_value_s LIKE VARIABLE __status_contained_srv
{
    REDEFINE HANDLING
    IF ((PARAM.MODE_BLK.ACTUAL|PARAM.MODE_BLK.TARGET) & _AUTOMATIC ) {
        READ;
    }
    ELSE {
        READ & WRITE ;
    }
}
*/

#if 0
float_position_r LIKE VARIABLE __float_contained_r
{
    REDEFINE CONSTANT_UNIT [unit_code_1342];
    REDEFINE LABEL LBL_POSITION;
	REDEFINE HANDLING READ;
}
#endif

float_value_r LIKE VARIABLE __float_contained_r
{
    REDEFINE LABEL LBL_VALUE_D;
	REDEFINE HANDLING READ;
}


VARIABLE _ip_drive_current_deadband
{
    LABEL LBL_DEADBAND;
    HELP  HLP5(HLP_DEADBAND);
    CLASS CONTAINED;
    TYPE  FLOAT
	DATA_LIMITS(0, 20)
    CONSTANT_UNIT [unit_code_1342];

}

VARIABLE _alert_command
{
    LABEL LBL_ALERT_COMMAND;
    HELP  HLP5(HLP_ALERT_COMMAND);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ALERT_LOG_COMMAND
    }
}

VARIABLE _alert_data_r
{
    LABEL LBL_ALERT_DATA;
    HELP  HLP5(HLP_ALERT_DATA);
    CLASS CONTAINED;
    TYPE  UNSIGNED_INTEGER (4) ;
    HANDLING READ;
}

temp_value_with_unit LIKE VARIABLE __float_contained_r
{
	REDEFINE LABEL "|en|Temperature Value";
    REDEFINE CONSTANT_UNIT [unit_code_1001];

}

VARIABLE discrete_input_value
{
    LABEL LBL_VALUE_D;
    HELP  HLP5(HLP_DISCRETE_INPUT);
    CLASS CONTAINED & DYNAMIC;
    TYPE  ENUMERATED (1)
    {
        ENUM_DISCRETE_STATE
    }
    HANDLING READ;
}

VARIABLE aggressiveness
{
    LABEL LBL_AGGRESSIVENESS;
    HELP  HLP5(HLP_AGGRESSIVENESS);
    CLASS CONTAINED;
    TYPE  INTEGER
    {
        MIN_VALUE -9;
        MAX_VALUE 9;
    }
}

tune_flags LIKE VARIABLE uint_element
{
    REDEFINE LABEL LBL_TUNE_FLAGS;
    REDEFINE HELP  HLP5(HLP_TUNE_FLAGS);
}

VARIABLE completion
{
    LABEL LBL_COMPLETION;
    HELP  HLP5(HLP_COMPLETION);
    CLASS CONTAINED & DYNAMIC;
    TYPE ENUMERATED (2)
    {
        ENUM_COMPLETION
    }
}

VARIABLE character_type
{
    LABEL LBL_CHARACTER_TYPE;
    HELP  HLP5(HLP_CHARACTER_TYPE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_TYPE
    }
    /*VALIDITY  "Man/OOS"    ;*/
}

VARIABLE char_sel_number_of_points_r
{
    LABEL LBL_CHAR_SEL_NUMBER_OF_POINTS;
    HELP  HLP5(HLP_CHAR_SEL_NUMBER_OF_POINTS);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
    /*VALIDITY  "Man/OOS"    ;*/
    HANDLING READ;
}

VARIABLE act_style
{
    LABEL LBL_ACT_STYLE;
    HELP  HLP5(HLP_ACT_STYLE);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ACTUATOR_TYPE
    }
    HANDLING READ;
}

VARIABLE point_closed
{
    LABEL LBL_POINT_CLOSED;
    HELP  HLP5(HLP_POINT_CLOSED);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-49,100)
}

VARIABLE float_nd_with_max_min
{
    LABEL "|en|Position";
    HELP  "|en|Position value";
    CLASS CONTAINED;
    TYPE  FLOAT
    DATA_LIMITS(0.1, -200)
}


VARIABLE xd_fs_configuration
{
    LABEL LBL_XD_FS_CONFIGURATION;
    HELP  HLP5(HLP_XD_FS_CONFIGURATION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_XD_FS_CONFIGURATION
    }
}

_eu_100_r LIKE VARIABLE __eu_100
{
    REDEFINE  HANDLING READ;
}
_eu_0_r LIKE VARIABLE __eu_0
{
    REDEFINE  HANDLING READ;
}

VARIABLE _enable_disable
{
    LABEL LBL_ENABLE;
    HELP  HLP5(HLP_ENABLE);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ENABLE_DISABLE
    }
    /* HANDLING READ; */
}

VARIABLE _discrete_value_nd
{
    LABEL LBL_VALUE_D;
    HELP  HLP5(HLP_VALUE_D);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1)
    DATA_LIMITS(0,1)
}

VARIABLE _discrete_state_r
{
    LABEL LBL_VALUE_D;
    HELP HLP5(HLP_VALUE_D);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_DISCRETE_STATE
    }
	HANDLING READ;
}

VARIABLE _discrete_value
{
    LABEL LBL_VALUE_D;
    HELP  HLP5(HLP_VALUE_D);
    CLASS CONTAINED & DYNAMIC;
    TYPE UNSIGNED_INTEGER (1)
    DATA_LIMITS(0,1)
}

_discrete_value_int_nd LIKE VARIABLE _discrete_value_nd
{
    REDEFINE HELP  HLP5(HLP_VALUE_DINT);
    REDEFINE_DATA_LIMITS(UNSIGNED_INTEGER, 0, 100)
}

_discrete_value_int_nd_r LIKE VARIABLE _discrete_value_nd
{
    REDEFINE HELP  HLP5(HLP_VALUE_DINT);
    REDEFINE_DATA_LIMITS(UNSIGNED_INTEGER, 0, 100)
    REDEFINE HANDLING READ;

}

/* xd_fstate_opt LIKE VARIABLE __xd_fstate_opt /\* bug 15845 *\/ */
/* { */
/*     REDEFINE HANDLING READ & WRITE; */
/* } */

VARIABLE xd_fstate_opt
{
    LABEL [xd_fstate_opt_label] ;
    HELP [xd_fstate_opt_help] ;
    CLASS CONTAINED & SERVICE ;
    TYPE ENUMERATED (1)
    {
        { 0, [hold_last_value_label],[hold_last_value_help] },
        { 1, [fail_closed_label], [fail_closed_help] },
        { 2, [fail_open_label], [fail_open_help] },
        { 3, [xd_fstate_val_label], [xd_fstate_val_help] }
    }
    HANDLING READ & WRITE;
}


VARIABLE trvl_accmltn_alert_point
{
    LABEL           "|en|Alert Point" ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~/
*** local var definitions
/~~~~~~~~~~~~~~~~~~~~~~~~*/


/* Add more variable for travel trend and cycle counter alert*/
VARIABLE _currently_collected
{
    LABEL           "|en|Currently Collected";
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _today
{
    LABEL           LBL_168_TODAY;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _last_day
{
    LABEL           LBL_169_LAST_DAY;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _previous_day
{
    LABEL           LBL_170_PREVIOUS_DAY;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _three_days_ago
{
    LABEL           LBL_171_THREE_DAYS_AGO;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _current_week
{
    LABEL           LBL_172_CURRENT_WEEK;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _last_week
{
    LABEL           LBL_173_LAST_WEEK;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _previous_week
{
    LABEL           LBL_174_PREVIOUS_WEEK;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _three_weeks_ago
{
    LABEL           LBL_175_THREE_WEEKS_AGO;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _current_month
{
    LABEL           LBL_176_CURRENT_MONTH;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _last_month
{
    LABEL           LBL_177_LAST_MONTH;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _previous_month
{
    LABEL           LBL_178_PREVIOUS_MONTH;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _three_months_ago
{
    LABEL           LBL_179_THREE_MONTHS_AGO;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _current_12_months
{
    LABEL           LBL_180_CURRENT_12_MONTHS;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _last_12_months
{
    LABEL           LBL_181_LAST_12_MONTHS;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _previous_12_months
{
    LABEL           LBL_182_PREVIOUS_12_MONTHS;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE _three_years_ago
{
    LABEL           LBL_183_THREE_YEARS_AGO;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
}

VARIABLE    _float_currently_collected
{
    LABEL           "|en|Currently Collected";
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_today
{
    LABEL           LBL_168_TODAY;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_last_day
{
    LABEL           LBL_169_LAST_DAY;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_previous_day
{
    LABEL           LBL_170_PREVIOUS_DAY;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_three_days_ago
{
    LABEL           LBL_171_THREE_DAYS_AGO;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_current_week
{
    LABEL           LBL_172_CURRENT_WEEK;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_last_week
{
    LABEL           LBL_173_LAST_WEEK;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_previous_week
{
    LABEL           LBL_174_PREVIOUS_WEEK;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_three_weeks_ago
{
    LABEL           LBL_175_THREE_WEEKS_AGO;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_current_month
{
    LABEL           LBL_176_CURRENT_MONTH;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_last_month
{
    LABEL           LBL_177_LAST_MONTH;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_previous_month
{
    LABEL           LBL_178_PREVIOUS_MONTH;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_three_months_ago
{
    LABEL           LBL_179_THREE_MONTHS_AGO;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_current_12_months
{
    LABEL           LBL_180_CURRENT_12_MONTHS;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_last_12_months
{
    LABEL           LBL_181_LAST_12_MONTHS;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_previous_12_months
{
    LABEL           LBL_182_PREVIOUS_12_MONTHS;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

VARIABLE _float_three_years_ago
{
    LABEL           LBL_183_THREE_YEARS_AGO;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*----------------------------/
** Records definition for SVI2
/----------------------------*/

RECORD final_value
{
    LABEL LBL_045_FINAL_VALUE;
    HELP HLP5(HLP_045_FINAL_VALUE);
    MEMBERS
    {
        STATUS,                                  __status_contained_srv;
        /*VALUE,                                   __float_contained_nd;*/ /*_047_value;*/
        VALUE,                                   final_value_f;
    }
}
RECORD final_value_range
{
    LABEL LBL_048_FINAL_VALUE_RANGE;
    HELP HLP5(HLP_048_FINAL_VALUE_RANGE);
    MEMBERS
    {
        EU_100,                                  _eu_100_r;
        EU_0,                                    _eu_0_r;
        UNITS_INDEX,                             _units_index_percent_r;
        DECIMAL,                                 _decimal_2_r;
    }
}
RECORD position_limits
{
    LABEL LBL_053_POSITION_LIMITS;
    HELP HLP5(HLP_053_POSITION_LIMITS);
    MEMBERS
    {
        LIMITS_PROTECTED,                        _limits_protected;
        ENABLE_HI,                               _enable_hi;
        ENABLE_LO,                               _enable_lo;
        LIMIT_HI,                                _limit_hi;
        LIMIT_LO,                                _limit_lo;
        ENABLE_RATE_HI,                          _enable_rate_hi;
        ENABLE_RATE_LO,                          _enable_rate_lo;
        LIMIT_RATE,                              _limit_rate;
    }
}
RECORD final_value_cutoff_hi
{
    LABEL LBL_062_FINAL_VALUE_CUTOFF_HI;
    HELP HLP5(HLP_062_FINAL_VALUE_CUTOFF_HI);
    MEMBERS
    {
        ENABLE,                                  _enable_disable;
        CUTOFF_POINT_HI,                         cutoff_point_hi;
    }
}
RECORD final_value_cutoff_lo
{
    LABEL LBL_065_FINAL_VALUE_CUTOFF_LO;
    HELP HLP5(HLP_065_FINAL_VALUE_CUTOFF_LO);
    MEMBERS
    {
        ENABLE,                                  _enable_disable;
        CUTOFF_POINT_LO,                         cutoff_point_lo;
    }
}
RECORD final_position_value
{
    LABEL LBL_068_FINAL_POSITION_VALUE;
    HELP HLP5(HLP_068_FINAL_POSITION_VALUE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   position;
    }
}
RECORD active_control_set
{
    LABEL LBL_072_ACTIVE_CONTROL_SET;
    HELP HLP5(HLP_072_ACTIVE_CONTROL_SET);
    MEMBERS
    {
        SELECTOR,                                _selector_r;
        P,                                       p_r;
        I,                                       i_r;
        D,                                       d_r;
        PADJ,                                    padj_r;
        BETA,                                    beta_r;
        POSCOMP,                                 poscomp_r;
        DEADZONE,                                deadzone_r;
        NONLIN,                                  nonlin_r;
    }
}
RECORD custom_control_set
{
    LABEL LBL_081_CUSTOM_CONTROL_SET;
    HELP HLP5(HLP_081_CUSTOM_CONTROL_SET);
    MEMBERS
    {
        P,                                       p;
        I,                                       i;
        D,                                       d;
        PADJ,                                    padj;
        BETA,                                    beta;
        POSCOMP,                                 poscomp;
        DEADZONE,                                deadzone;
        NONLIN,                                  nonlin;
    }
}
RECORD backup_control_set
{
    LABEL LBL_090_BACKUP_CONTROL_SET;
    HELP HLP5(HLP_090_BACKUP_CONTROL_SET);
    MEMBERS
    {
        SELECTOR,                                _uint_selector_r;
        P,                                       p_r;
        I,                                       i_r;
        D,                                       d_r;
        PADJ,                                    padj_r;
        BETA,                                    beta_r;
        POSCOMP,                                 poscomp_r;
        DEADZONE,                                deadzone_r;
        NONLIN,                                  nonlin_r;
    }
}
RECORD travel_calibration
{
    LABEL LBL_100_TRAVEL_CALIBRATION;
    HELP HLP5(HLP_100_TRAVEL_CALIBRATION);
    MEMBERS
    {
        CAL_LOCATION,                            _cal_location;
        CAL_DATE,                                _cal_date;
        CAL_WHO,                                 _cal_who;
        CAL_STOP_HI_POS,                        _stop_hi_pos;
        CAL_STOP_LO_POS,                        _stop_lo_pos;
        CAL_TYPE,                                _cal_type;
        LAST_RESULT,                             _last_result_r_enum;
    }
}
RECORD working_sp
{
    LABEL LBL_111_WORKING_SP;
    HELP HLP5(HLP_111_WORKING_SP);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   float_value_r;
    }
}
RECORD working_pos
{
    LABEL LBL_114_WORKING_POS;
    HELP HLP5(HLP_114_WORKING_POS);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   float_value_r;
    }
}


RECORD travel_accumulation_trend
{
    LABEL LBL_167_TRAVEL_ACCUMULATION_TREND;
    HELP HLP5(HLP_167_TRAVEL_ACCUMULATION_TREND);
    MEMBERS
    {
        CURRENTLY_COLLECTED,                     _currently_collected;
        TODAY,                                   _today;
        LAST_DAY,                                _last_day;
        PREVIOUS_DAY,                            _previous_day;
        THREE_DAYS_AGO,                          _three_days_ago;
        CURRENT_WEEK,                            _current_week;
        LAST_WEEK,                               _last_week;
        PREVIOUS_WEEK,                           _previous_week;
        THREE_WEEKS_AGO,                         _three_weeks_ago;
        CURRENT_MONTH,                           _current_month;
        LAST_MONTH,                              _last_month;
        PREVIOUS_MONTH,                          _previous_month;
        THREE_MONTHS_AGO,                        _three_months_ago;
        CURRENT_12_MONTHS,                       _current_12_months;
        LAST_12_MONTHS,                          _last_12_months;
        PREVIOUS_12_MONTHS,                      _previous_12_months;
        THREE_YEARS_AGO,                         _three_years_ago;
        /*TOTAL_SVI2,                              uint_4_element_r_nd;*/ /*_184_total;*/
    }
}


RECORD cycle_counter_trend
{
    LABEL LBL_199_CYCLE_COUNTER_TREND;
    HELP HLP5(HLP_199_CYCLE_COUNTER_TREND);
    MEMBERS
    {
        CURRENTLY_COLLECTED,                     _currently_collected;
        TODAY,                                   _today;
        LAST_DAY,                                _last_day;
        PREVIOUS_DAY,                            _previous_day;
        THREE_DAYS_AGO,                          _three_days_ago;
        CURRENT_WEEK,                            _current_week;
        LAST_WEEK,                               _last_week;
        PREVIOUS_WEEK,                           _previous_week;
        THREE_WEEKS_AGO,                         _three_weeks_ago;
        CURRENT_MONTH,                           _current_month;
        LAST_MONTH,                              _last_month;
        PREVIOUS_MONTH,                          _previous_month;
        THREE_MONTHS_AGO,                        _three_months_ago;
        CURRENT_12_MONTHS,                       _current_12_months;
        LAST_12_MONTHS,                          _last_12_months;
        PREVIOUS_12_MONTHS,                      _previous_12_months;
        THREE_YEARS_AGO,                         _three_years_ago;
    }
}
RECORD position_error_trend
{
    LABEL LBL_217_POSITION_ERROR_TREND;
    HELP HLP5(HLP_217_POSITION_ERROR_TREND);
    MEMBERS
    {
        CURRENTLY_COLLECTED,                     _float_currently_collected;
        TODAY,                                   _float_today;
        LAST_DAY,                                _float_last_day;
        PREVIOUS_DAY,                            _float_previous_day;
        THREE_DAYS_AGO,                          _float_three_days_ago;
        CURRENT_WEEK,                            _float_current_week;
        LAST_WEEK,                               _float_last_week;
        PREVIOUS_WEEK,                           _float_previous_week;
        THREE_WEEKS_AGO,                         _float_three_weeks_ago;
        CURRENT_MONTH,                           _float_current_month;
        LAST_MONTH,                              _float_last_month;
        PREVIOUS_MONTH,                          _float_previous_month;
        THREE_MONTHS_AGO,                        _float_three_months_ago;
        CURRENT_12_MONTHS,                       _float_current_12_months;
        LAST_12_MONTHS,                          _float_last_12_months;
        PREVIOUS_12_MONTHS,                      _float_previous_12_months;
        THREE_YEARS_AGO,                         _float_three_years_ago;
        /*TOTAL are removed in version 26/10*/
    }
}
#if 0
			RECORD position_histogram
			{
			    LABEL LBL_235_POSITION_HISTOGRAM;
			    HELP HLP5(HLP_235_POSITION_HISTOGRAM);
			    MEMBERS
			    {
			        TOTAL_TIME,                              position_history_total_time;
			        POS_5_PERCENT_CLOSED,                    pos_5_percent_closed_r;
			        POS_10_PERCENT,                          pos_10_percent_r;
			        POS_20_PERCENT,                          pos_20_percent_r;
			        POS_30_PERCENT,                          pos_30_percent_r;
			        POS_40_PERCENT,                          pos_40_percent_r;
			        POS_50_PERCENT,                          pos_50_percent_r;
			        POS_60_PERCENT,                          pos_60_percent_r;
			        POS_70_PERCENT,                          pos_70_percent_r;
			        POS_80_PERCENT,                          pos_80_percent_r;
			        POS_90_PERCENT,                          pos_90_percent_r;
			        POS_95_PERCENT,                          pos_95_percent_r;
			        POS_95_PERCENT_OPEN,                     pos_95_percent_open_r;
			    }
			}
#endif

RECORD near_closed_alert
{
    LABEL LBL_249_NEAR_CLOSED_ALERT;
    HELP HLP5(HLP_249_NEAR_CLOSED_ALERT);
    MEMBERS
    {
        POSITION_CLOSED,                            point_closed;
        NEAR_CLOSED,                             _near_closed;
        ALERT_POINT,                             _alert_point_time;
        AlertExtras
#if 0
#ifndef NOUPDATES
        HISTORIC_ALERT,                          historic_alert;
#else
        HISTORIC_ALERT,                          _historic_alert_for_near_closed_alert; /* see 18272 & mail */
#endif /*NOUPDATES*/
#endif
       ENABLE,                                  enable;
    }
}
#if 0
			RECORD position_error_histogram
			{
			    LABEL LBL_255_POSITION_ERROR_HISTOGRAM;
			    HELP HLP5(HLP_255_POSITION_ERROR_HISTOGRAM);
			    MEMBERS
			    {
			        POS_5_PERCENT_CLOSED,                pos_5_percent_closed_r;
			        POS_10_PERCENT,                          pos_10_percent_r;
			        POS_20_PERCENT,                          pos_20_percent_r;
			        POS_30_PERCENT,                          pos_30_percent_r;
			        POS_40_PERCENT,                          pos_40_percent_r;
			        POS_50_PERCENT,                          pos_50_percent_r;
			        POS_60_PERCENT,                          pos_60_percent_r;
			        POS_70_PERCENT,                          pos_70_percent_r;
			        POS_80_PERCENT,                          pos_80_percent_r;
			        POS_90_PERCENT,                          pos_90_percent_r;
			        POS_95_PERCENT,                          pos_95_percent_r;
			        POS_95_PERCENT_OPEN,                     pos_95_percent_open_r;
			    }
			}

			RECORD setpoint_timeout_alert
			{
			    LABEL LBL_268_SETPOINT_TIMEOUT_ALERT;
			    HELP HLP5(HLP_268_SETPOINT_TIMEOUT_ALERT);
			    MEMBERS
			    {
			        TIME_SINCE_UPDATE,                       time_since_update;
			        ALERT_POINT,                             setpoint_alert_point;
			        SETPOINT_MAX_TIME, setpoint_max_time;
			        AlertExtras
			        ENABLE,                                  enable;
			    }
			}
#endif

RECORD xd_fstate
{
    LABEL LBL_275_XD_FSTATE;
    HELP HLP5(HLP_275_XD_FSTATE);
    MEMBERS
    {
        CONFIGURATION,                           xd_fs_configuration;
        XD_FSTATE_OPT_1, /*_svi2*/                      xd_fstate_opt;
        FSTATE_VALUE_1, /*_svi2*/                       _fstate_value;
        FSTATE_TIME_1, /*_svi2*/                        _fstate_time;
    }
}
RECORD char_selection
{
    LABEL LBL_280_CHAR_SELECTION;
    HELP HLP5(HLP_280_CHAR_SELECTION);
    MEMBERS
    {
        TYPE_1, /*_svi2*/                               character_type;
        NUMBER_OF_POINTS_1, /*_svi2*/                   char_sel_number_of_points_r;
    }
}
RECORD custom_char
{
    LABEL LBL_284_CUSTOM_CHAR;
    HELP HLP5(HLP_284_CUSTOM_CHAR);
    MEMBERS
    {
        ACTION,                                  _action;
        NUMBER_OF_POINTS_1, /*_svi2*/                   _number_of_points_custom_char;
    }
}
RECORD supply_pressure
{
    LABEL LBL_291_SUPPLY_PRESSURE;
    HELP HLP5(HLP_291_SUPPLY_PRESSURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r; /*see bug:12555*/
        VALUE,                                   __float_contained_r;
    }
}
RECORD pressure_range
{
    LABEL LBL_294_PRESSURE_RANGE;
    HELP HLP5(HLP_294_PRESSURE_RANGE);
    MEMBERS
    {
        EU_100,                                  _eu_100_r;
        EU_0,                                    _eu_0_r;
        UNITS_INDEX,                             _units_index_press;
        DECIMAL,                                 _decimal_3;
    }
}
RECORD supply_pressure_hi_alert
{
    LABEL LBL_299_SUPPLY_PRESSURE_HI_ALERT;
    HELP HLP5(HLP_299_SUPPLY_PRESSURE_HI_ALERT);
    MEMBERS
    {
        CURR_VALUE,                                __float_contained_r;
        ALERT_POINT,                             _alert_point_press_hi;
        DEADBAND,                                _deadband_press;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD supply_pressure_lo_alert
{
    LABEL LBL_306_SUPPLY_PRESSURE_LO_ALERT;
    HELP HLP5(HLP_306_SUPPLY_PRESSURE_LO_ALERT);
    MEMBERS
    {
        CURR_VALUE,                                __float_contained_r;
        ALERT_POINT,                             _alert_point_press_lo;
        DEADBAND,                                _deadband_press;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD supply_pressure_lolo_alert
{
    LABEL LBL_313_SUPPLY_PRESSURE_LOLO_ALERT;
    HELP HLP5(HLP_313_SUPPLY_PRESSURE_LOLO_ALERT);
    MEMBERS
    {
        CURR_VALUE,                                __float_contained_r;
        ALERT_POINT,                             _alert_point_press_lo;
        DEADBAND,                                _deadband_press;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD actuator_a_pressure
{
    LABEL LBL_320_ACTUATOR_A_PRESSURE;
    HELP HLP5(HLP_320_ACTUATOR_A_PRESSURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   __float_contained_r;
    }
}
RECORD actuator_b_pressure
{
    LABEL LBL_323_ACTUATOR_B_PRESSURE;
    HELP HLP5(HLP_323_ACTUATOR_B_PRESSURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   __float_contained_r;
    }
    /*VALIDITY FALSE;*/
}
RECORD atmospheric_pressure
{
    LABEL LBL_326_ATMOSPHERIC_PRESSURE;
    HELP HLP5(HLP_326_ATMOSPHERIC_PRESSURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   __float_contained_r;
    }
}
RECORD pilot_pressure
{
    LABEL LBL_329_PILOT_PRESSURE;
    HELP HLP5(HLP_329_PILOT_PRESSURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   __float_contained_r;
    }
}

RECORD temperature
{
    LABEL LBL_341_TEMPERATURE;
    HELP HLP5(HLP_341_TEMPERATURE);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   temp_value_with_unit;
    }
}
RECORD temperature_hi_alert
{
    LABEL LBL_344_TEMPERATURE_HI_ALERT;
    HELP HLP5(HLP_344_TEMPERATURE_HI_ALERT);
    MEMBERS
    {
        CURR_VALUE,                         temp_value_with_unit;
        ALERT_POINT,                             _alert_point_temp_hi;
        DEADBAND,                                _deadband_temp;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD temperature_lo_alert
{
    LABEL LBL_351_TEMPERATURE_LO_ALERT;
    HELP HLP5(HLP_351_TEMPERATURE_LO_ALERT);
    MEMBERS
    {
        CURR_VALUE,                         temp_value_with_unit;
        ALERT_POINT,                             _alert_point_temp_lo;
        DEADBAND,                                _deadband_temp;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD ip_drive_current
{
    LABEL LBL_358_IP_DRIVE_CURRENT;
    HELP HLP5(HLP_358_IP_DRIVE_CURRENT);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _value_ip_r;
    }
}
RECORD ip_drive_current_hi_alert
{
    LABEL LBL_361_IP_DRIVE_CURRENT_HI_ALERT;
    HELP HLP5(HLP_361_IP_DRIVE_CURRENT_HI_ALERT);
    MEMBERS
    {
        CURRENT,                                 _current;
        ALERT_POINT,                             _alert_point_ip_current_hi;
        DEADBAND,                                _ip_drive_current_deadband;
        DURATION_TIME,                           _time_float;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD ip_drive_current_lo_alert
{
    LABEL LBL_368_IP_DRIVE_CURRENT_LO_ALERT;
    HELP HLP5(HLP_368_IP_DRIVE_CURRENT_LO_ALERT);
    MEMBERS
    {
        CURRENT,                                 _current;
        ALERT_POINT,                             _alert_point_current_lo;
        DEADBAND,                                _ip_drive_current_deadband;
        DURATION_TIME,                               _time_float;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD autotune
{
    LABEL LBL_376_AUTOTUNE;
    HELP HLP5(HLP_376_AUTOTUNE);
    MEMBERS
    {
        SUPPLY_PRESS,                            __float_contained_nd;
        AGGRESSIVENESS,                          aggressiveness;
        TUNE_FLAGS,                              tune_flags;
        COMPLETION,                              completion;
    }
}
/* RECORD autotune_state */
/* { */
/*     LABEL LBL_380_AUTOTUNE_STATE; */
/*     HELP HLP5(HLP_380_AUTOTUNE_STATE); */
/*     MEMBERS */
/*     { */
/*         START_SVI2,                              _381_start; */
/*         RESULT,                                  _383_result; */
/*     } */
/* } */
/* RECORD travel_calibration */
/* { */
/*     LABEL LBL_384_TRAVEL_CALIBRATION; */
/*     HELP HLP5(HLP_384_TRAVEL_CALIBRATION); */
/*     MEMBERS */
/*     { */
/*         START_SVI2,                              _385_start; */
/*         RESULT,                                  _386_result; */
/*     } */
/* } */
RECORD check_process
{
    LABEL LBL_387_CHECK_PROCESS;
    HELP HLP5(HLP_387_CHECK_PROCESS);
    MEMBERS
    {
        PROCESS_ID,                              _process_id_r;
        PERCENT_COMPLETE,                        _percent_complete_r;
    }
}
RECORD ui_custom_configuration
{
    LABEL LBL_390_UI_CUSTOM_CONFIGURATION;
    HELP HLP5(HLP_390_UI_CUSTOM_CONFIGURATION);
    MEMBERS
    {
        CUSTOM_1_CONFIGURATION,                  custom_1_configuration;
        CUSTOM_2_CONFIGURATION,                  custom_2_configuration;
    }
}
RECORD failed_state
{
    LABEL LBL_393_FAILED_STATE;
    HELP HLP5(HLP_393_FAILED_STATE);
    MEMBERS
    {
        FF,                                      _ff_r;
        APP,                                     _app_r;
        PROPAGATE_MODE,                          propagate_mode;
    }
}
RECORD final_value_d
{
    LABEL LBL_396_FINAL_VALUE_D;
    HELP HLP5(HLP_396_FINAL_VALUE_D);
    MEMBERS
    {
        STATUS,                                  __status_contained;
        VALUE,                                   _discrete_value_nd;
    }
}
RECORD final_position_value_d
{
    LABEL LBL_399_FINAL_POSITION_VALUE_D;
    HELP HLP5(HLP_399_FINAL_POSITION_VALUE_D);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _discrete_value_int_nd_r;
    }
}
RECORD final_value_dint
{
    LABEL LBL_402_FINAL_VALUE_DINT;
    HELP HLP5(HLP_402_FINAL_VALUE_DINT);
    MEMBERS
    {
        STATUS,                                  __status_contained;
        VALUE,                                   _discrete_value_int_nd;
    }
}
RECORD final_position_value_dint
{
    LABEL LBL_405_FINAL_POSITION_VALUE_DINT;
    HELP HLP5(HLP_405_FINAL_POSITION_VALUE_DINT);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _discrete_value_int_nd_r;
    }
}
RECORD fsc_set_d
{
    LABEL LBL_408_FSC_SET_D;
    HELP HLP5(HLP_408_FSC_SET_D);
    MEMBERS
    {
        STATUS,                                  __status_contained;
        VALUE,                                   _discrete_value;
    }
}
RECORD fsc_actual_d
{
    LABEL LBL_411_FSC_ACTUAL_D;
    HELP HLP5(HLP_411_FSC_ACTUAL_D);
    MEMBERS
    {
        STATUS,                                  __status_contained;
        VALUE,                                   _discrete_value;
    }
}
RECORD discrete_output_1_state
{
    LABEL LBL_414_DISCRETE_OUTPUT_1;
    HELP HLP5(HLP_414_DISCRETE_OUTPUT_1);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _discrete_state_r;
    }
}
RECORD discrete_output_2_state
{
    LABEL LBL_417_DISCRETE_OUTPUT_2;
    HELP HLP5(HLP_417_DISCRETE_OUTPUT_2);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _discrete_state_r;
    }
}

RECORD discrete_input
{
    LABEL LBL_DISCRETE_INPUT;
    HELP  HLP5(HLP_DISCRETE_INPUT);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   discrete_input_value;
    }
}

RECORD discrete_switch_1_conf
{
    LABEL LBL_426_DISCRETE_SWITCH_1_CONF;
    HELP HLP5(HLP_426_DISCRETE_SWITCH_1_CONF);
    MEMBERS
    {
        DIRECTION,                               _direction;
        FUNCTION,                                _function;
    }
}
RECORD discrete_switch_2_conf
{
    LABEL LBL_429_DISCRETE_SWITCH_2_CONF;
    HELP HLP5(HLP_429_DISCRETE_SWITCH_2_CONF);
    MEMBERS
    {
        DIRECTION,                               _direction;
        FUNCTION,                                _function;
    }
}
RECORD setpoint
{
    LABEL LBL_442_SETPOINT;
    HELP HLP5(HLP_442_SETPOINT);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _value_open_close_r;
    }
}

/* RECORD manual_setpoint */
/* { */
/*     LABEL LBL_MANUAL_SETPOINT; */
/*     HELP HLP5(HLP_MANUAL_SETPOINT); */
/*     MEMBERS */
/*     { */
/*         STATUS,                                  __status_contained_r; */
/*         VALUE,                                   __float_contained_r; */
/*     } */
/*     } */
/* } */

RECORD actual_position
{
    LABEL LBL_445_ACTUAL_POSITION;
    HELP HLP5(HLP_445_ACTUAL_POSITION);
    MEMBERS
    {
        STATUS,                                  __status_contained_r;
        VALUE,                                   _value_open_close_r;
    }
}

RECORD alert_log
{
    LABEL LBL_ALERT_LOG;
    HELP HLP5(HLP_ALERT_LOG);
    MEMBERS
    {
        ALERT_COMMAND,         _alert_command;
        ALERT_TIME,      __time_stamp;
        ALERT_DATA,      _alert_data_r;
    }
}

#if 0
                RECORD working_times
                {
                    LABEL LBL_531_WORKING_TIMES;
                    HELP HLP5(HLP_531_WORKING_TIMES);
                    MEMBERS
                    {
                        SINCE_RESET,                             _since_reset;
                        TOTAL_TIME,                              _total_time_r;
                    }
                }
#endif

RECORD working_time_alert
{
    LABEL LBL_535_WORKING_TIME_ALERT;
    HELP HLP5(HLP_535_WORKING_TIME_ALERT);
    MEMBERS
    {
        ALERT_TOTAL_TIME,                        _alert_total_time_r; /*Bug #17523;*/
        ALERT_POINT,                             trvl_accmltn_alert_point;
        AlertExtras
        ENABLE,                                  enable;
    }
}
RECORD actuator_1
{
    LABEL LBL_543_ACTUATOR_1;
    HELP HLP5(HLP_543_ACTUATOR_1);
    MEMBERS
    {
        ACT_MAN_ID_1, /*_svi2*/                         _act_man_id;
        ACT_MODEL_NUM_1, /*_svi2*/                      _act_model_num;
        ACT_SN_1, /*_svi2*/                             _act_sn;
    }
}
RECORD actuator_2
{
    LABEL LBL_548_ACTUATOR_2;
    HELP HLP5(HLP_548_ACTUATOR_2);
    MEMBERS
    {
        ACT_TYPE_STRING,                                _act_type;
        ACT_SIZE,                                _act_size;
        ACT_ROTARY_MOMENT_ARM,                   _act_rotary_moment_arm;
        ACT_EFFECTIVE_AREA,                      _act_effective_area;
    }
}
RECORD actuator_3
{
    LABEL LBL_553_ACTUATOR_3;
    HELP HLP5(HLP_553_ACTUATOR_3);
    MEMBERS
    {
        SHUTOFF_DP,                              _shutoff_dp;
        HAND_WHEEL,                              _hand_wheel;
        ACT_STYLE,                               act_style;
        ACT_FAIL_ACTION_1, /*_svi2*/                  _act_fail_action;
        /* SENSOR_INCREASE,                         _558_sensor_increase; */
        RELAY_TYPE,                              _relay_type;
        SUPPLY_PRS_MAX,                          _supply_pres_max;
        PRS_CONTROL_HI,                          _prs_control_hi;
        PRS_CONTROL_LO,                          _prs_control_lo;

    }
}
RECORD actuator_info
{
    LABEL LBL_563_ACTUATOR_INFO;
    HELP HLP5(HLP_563_ACTUATOR_INFO);
    MEMBERS
    {
        DESCRIPTOR,                              _descriptor;
        MESSAGE,                                 _message;
        DATE_INFO,                               _date;
        SPEC_SHEET,                              _spec_sheet;
    }
}
RECORD valve_identification
{
    LABEL LBL_568_VALVE_IDENTIFICATION;
    HELP HLP5(HLP_568_VALVE_IDENTIFICATION);
    MEMBERS
    {
        VALVE_MAN_ID_1, /*_svi2*/                       _valve_man_id;
        VALVE_MODEL_NUM_1, /*_svi2*/                    _valve_model_num;
        VALVE_SN_1, /*_svi2*/                           _valve_sn;
    }
}
RECORD valve_service
{
    LABEL LBL_572_VALVE_SERVICE;
    HELP HLP5(HLP_572_VALVE_SERVICE);
    MEMBERS
    {
        SERVICE_1, /*_svi2*/                            _service;
        PID_NO,                                  _pid_no;
    }
}
RECORD valve_body_1
{
    LABEL LBL_575_VALVE_BODY_1;
    HELP HLP5(HLP_575_VALVE_BODY_1);
    MEMBERS
    {
        VALVE_TYPE_1, /*_svi2*/                         _valve_type;
        BODY_SIZE,                               _body_size;
        PACKING,                                 _packing;
        PLUG_TYPE,                               _plug_type;
        SEAT_RING_TYPE,                          _seat_ring_type;
    }
}
RECORD valve_body_2
{
    LABEL LBL_581_VALVE_BODY_2;
    HELP HLP5(HLP_581_VALVE_BODY_2);
    MEMBERS
    {
        CHARACTERISTIC,                          _characteristic;
        LEAKAGE_CLASS,                           _leakage_class;
    }
}

RECORD valve_body_3
{
    LABEL LBL_584_VALVE_BODY_3;
    HELP HLP5(HLP_584_VALVE_BODY_3);
    MEMBERS
    {
        FLOW_ACTION,                             _flow_action;
        RATED_ADJ_CV,                            _rated_adj_cv;
    }
}
RECORD valve_info
{
    LABEL LBL_587_VALVE_INFO;
    HELP HLP5(HLP_587_VALVE_INFO);
    MEMBERS
    {
        SAME_AS_ACTUATOR,                        _same_as_actuator;
        DESCRIPTOR,                              _descriptor;
        MESSAGE,                                 _message;
        DATE_INFO,                               _date;
        SPEC_SHEET,                              _spec_sheet;
    }
}
RECORD booster
{
    LABEL LBL_593_BOOSTER;
    HELP HLP5(HLP_593_BOOSTER);
    MEMBERS
    {
        MANUFACTURER_INFO,                       _manufacturer;
        MODEL,                                   _model;
        QTY,                                     _qty;
    }
}

#if 0
RECORD accessory
{
    LABEL LBL_597_ACCESSORY;
    HELP HLP5(HLP_597_ACCESSORY);
    MEMBERS
    {
        SOLENOID,                                _solenoid;
        REMOTE_SENSOR,                           _remote_sensor;
    }
}
#endif

RECORD position_extremes
{
    LABEL LBL_599_POSITION_EXTREMES;
    HELP HLP5(HLP_599_POSITION_EXTREMES);
    MEMBERS
    {
        FINAL_VALUE_MAX,                         _final_value_max;
        FINAL_VALUE_MIN,                         _final_value_min;
        FINAL_POS_VALUE_MAX,                     _final_pos_value_max;
        FINAL_POS_VALUE_MIN,                     _final_pos_value_min;
        WORKING_SP_MAX,                          _working_sp_max;
        WORKING_SP_MIN,                          _working_sp_min;
        WORKING_POS_MAX,                         _working_pos_max;
        WORKING_POS_MIN,                         _working_pos_min;
    }
}
RECORD pressure_extremes
{
    LABEL LBL_608_PRESSURE_EXTREMES;
    HELP HLP5(HLP_608_PRESSURE_EXTREMES);
    MEMBERS
    {
        SUPPLY_PRESSURE_MAX,                     _supply_pressure_max;
        SUPPLY_PRESSURE_MIN,                     _supply_pressure_min;
        ACTUATOR_A_MAX,                          _actuator_a_max;
        ACTUATOR_A_MIN,                          _actuator_a_min;
        ACTUATOR_B_MAX,                          _actuator_b_max;
        ACTUATOR_B_MIN,                          _actuator_b_min;
        PILOT_MAX,                               _pilot_max;
        PILOT_MIN,                               _pilot_min;
    }
}
RECORD ip_current_extremes
{
    LABEL LBL_620_IP_CURRENT_EXTREMES;
    HELP HLP5(HLP_620_IP_CURRENT_EXTREMES);
    MEMBERS
    {
        IP_CURRENT_MAX,                          _ip_current_max;
        IP_CURRENT_MIN,                          _ip_current_min;
    }
}

RECORD diagnostic_configuration
{
    LABEL LBL_DIAGNOSTIC_CONFIGURATION;
    HELP HLP5(HLP_DIAGNOSTIC_CONFIGURATION);
    MEMBERS
    {
        START_POSITION,          start_position;
        END_POSITION,            end_position;
        /* NUMBER_OF_POINTS_SVI2,   number_of_points; */
        SET_POINT_RATE,          set_point_rate;
        SAMPLING_TIME,           sampling_time;
        DIRECTION,               diag_direction;
        /* INCREMENT,               increment; */
        OPTION,       diag_option;
        /* DIAG_TIME,               diag_time; */
    }
}

/*-------------------------------------------/
** The variables for SVI2 AP FF in the Record
/-------------------------------------------*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~/
*** variables are refined.
/~~~~~~~~~~~~~~~~~~~~~~~~~*/
#if 0
#include "V_Ds.h"
#endif

VARIABLE  _act_effective_area
{
    LABEL LBL_ACT_EFFECTIVE_AREA;
    HELP  HLP5(HLP_ACT_EFFECTIVE_AREA);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
}
VARIABLE  _act_fail_action
{
    LABEL LBL_ACT_FAIL_ACTION;
    HELP  HLP5(HLP_ACT_FAIL_ACTION);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ACT_FAIL_ACTION
    }
}
VARIABLE  _act_man_id
{
    LABEL LBL_ACT_MAN_ID;
    HELP  HLP5(HLP_ACT_MAN_ID);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _act_model_num
{
    LABEL LBL_ACT_MODEL_NUM;
    HELP  HLP5(HLP_ACT_MODEL_NUM);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _act_rotary_moment_arm
{
    LABEL LBL_ACT_ROTARY_MOMENT_ARM;
    HELP  HLP5(HLP_ACT_ROTARY_MOMENT_ARM);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _act_size
{
    LABEL LBL_ACT_SIZE;
    HELP  HLP5(HLP_ACT_SIZE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _act_sn
{
    LABEL LBL_ACT_SN;
    HELP  HLP5(HLP_ACT_SN);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _act_type
{
    LABEL LBL_ACT_TYPE;
    HELP  HLP5(HLP_ACT_TYPE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _action
{
    LABEL LBL_ACTION;
    HELP  HLP5(HLP_ACTION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_CUSTOM_CHAR_ACTION
    }
}
VARIABLE  _actuator_a_max
{
    LABEL LBL_ACTUATOR_A_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _actuator_a_min
{
    LABEL LBL_ACTUATOR_A_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _actuator_b_max
{
    LABEL LBL_ACTUATOR_B_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _actuator_b_min
{
    LABEL LBL_ACTUATOR_B_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}

VARIABLE  _alert_point_current_lo
{
    LABEL LBL_ALERT_POINT_CURRENT_LO;
    HELP  HLP5(HLP_ALERT_POINT_CURRENT_LO);
    CLASS CONTAINED;
    TYPE  FLOAT
	DATA_LIMITS(-20,120)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _alert_point_press_hi
{
    LABEL LBL_ALERT_POINT_PRESS_HI;
    HELP  HLP5(HLP_ALERT_POINT_PRESS_HI);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(0,1035)
}

VARIABLE  _alert_point_press_lo
{
    LABEL LBL_ALERT_POINT_PRESS_LO;
    HELP  HLP5(HLP_ALERT_POINT_PRESS_LO);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(0,1035)
}
VARIABLE  _alert_point_temp_hi
{
    LABEL LBL_ALERT_POINT_TEMP_HI;
    HELP  HLP5(HLP_ALERT_POINT_TEMP_HI);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-45,85)
    CONSTANT_UNIT [unit_code_1001];
}
VARIABLE  _alert_point_ip_current_hi
{
    LABEL LBL_ALERT_POINT_TEMP_HI;
    HELP  HLP5(HLP_ALERT_POINT_TEMP_HI);
    CLASS CONTAINED;
    TYPE  FLOAT
	DATA_LIMITS(-20,120)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _alert_point_temp_lo
{
    LABEL LBL_ALERT_POINT_TEMP_LO;
    HELP  HLP5(HLP_ALERT_POINT_TEMP_LO);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-45,85)
    CONSTANT_UNIT [unit_code_1001];
}
VARIABLE  _alert_point_time
{
    LABEL LBL_ALERT_POINT_TIME;
    HELP  HLP5(HLP_ALERT_POINT_TIME);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (4);

    CONSTANT_UNIT [unit_code_1059];

}
VARIABLE  _app_r
{
    LABEL LBL_APP;
    HELP  HLP5(HLP_APP);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
    HANDLING READ; /*spec. V15*/
}
VARIABLE  _body_size
{
    LABEL LBL_BODY_SIZE;
    HELP  HLP5(HLP_BODY_SIZE);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
}
VARIABLE  _cal_date
{
    LABEL LBL_CAL_DATE;
    HELP  HLP5(HLP_CAL_DATE);
    CLASS CONTAINED;
    TYPE DATE_AND_TIME;
}
VARIABLE  _cal_location
{
    LABEL LBL_CAL_LOCATION;
    HELP  HLP5(HLP_CAL_LOCATION);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _cal_type
{
    LABEL LBL_CAL_TYPE;
    HELP  HLP5(HLP_CAL_TYPE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_CAL_TYPE
    }
}
VARIABLE  _cal_who
{
    LABEL LBL_CAL_WHO;
    HELP  HLP5(HLP_CAL_WHO);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _characteristic
{
    LABEL LBL_CHARACTERISTIC;
    HELP  HLP5(HLP_CHARACTERISTIC);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _current
{
    LABEL LBL_CURRENT;
    HELP  HLP5(HLP_CURRENT);
    CLASS CONTAINED & DYNAMIC;
    TYPE  FLOAT ;
    CONSTANT_UNIT [unit_code_1342];
    HANDLING READ;
}
VARIABLE  _date
{
    LABEL LBL_DATE;
    HELP  HLP5(HLP_DATE);
    CLASS CONTAINED;
    TYPE VISIBLE (8);
}
VARIABLE  _deadband_press
{
    LABEL LBL_DEADBAND_PRESS;
    HELP  HLP5(HLP_DEADBAND_PRESS);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(0,20)
    /* DATA_LIMITS(0,2) */
}
VARIABLE  _deadband_temp
{
    LABEL LBL_DEADBAND_TEMP;
    HELP  HLP5(HLP_DEADBAND_TEMP);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(0,2)
    CONSTANT_UNIT [unit_code_1001];
}
VARIABLE  _decimal_2_r
{
    LABEL LBL_DECIMAL_2;
    HELP  HLP5(HLP_DECIMAL_2);
    CLASS CONTAINED;
    TYPE INTEGER (1);
    HANDLING READ;
}
VARIABLE  _decimal_3
{
    LABEL LBL_DECIMAL_3;
    CLASS CONTAINED;
	TYPE INTEGER (1)
    {
        MIN_VALUE 3;
        MAX_VALUE 3;
    }
}
VARIABLE  _descriptor
{
    LABEL LBL_DESCRIPTOR;
    HELP  HLP5(HLP_DESCRIPTOR);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _enable_hi
{
    LABEL LBL_ENABLE_HI;
    HELP  HLP5(HLP_ENABLE_HI);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ENABLE_DISABLE
    }
    /* HANDLING READ; */
}
VARIABLE  _enable_lo
{
    LABEL LBL_ENABLE_LO;
    HELP  HLP5(HLP_ENABLE_LO);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ENABLE_DISABLE
    }
    /* HANDLING READ; */
}
VARIABLE  _enable_rate_hi
{
    LABEL LBL_ENABLE_RATE_HI;
    HELP  HLP5(HLP_ENABLE_RATE_HI);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ENABLE_DISABLE
    }
    /* HANDLING READ; */
}
VARIABLE  _enable_rate_lo
{
    LABEL LBL_ENABLE_RATE_LO;
    HELP  HLP5(HLP_ENABLE_RATE_LO);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ENABLE_DISABLE
    }
    /* HANDLING READ; */
}
VARIABLE  _ff_r
{
    LABEL LBL_FF;
    HELP  HLP5(HLP_FF);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
    HANDLING READ;
}
VARIABLE  _final_pos_value_max
{
    LABEL LBL_FINAL_POS_VALUE_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _final_pos_value_min
{
    LABEL LBL_FINAL_POS_VALUE_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _final_value_max
{
    LABEL LBL_FINAL_VALUE_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _final_value_min
{
    LABEL LBL_FINAL_VALUE_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _flow_action
{
    LABEL LBL_FLOW_ACTION;
    HELP  HLP5(HLP_FLOW_ACTION);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _hand_wheel
{
    LABEL LBL_HAND_WHEEL;
    HELP  HLP5(HLP_HAND_WHEEL);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
}
VARIABLE  _ip_current_max
{
    LABEL LBL_IP_CURRENT_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-25,150)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _ip_current_min
{
    LABEL LBL_IP_CURRENT_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-25,150)
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _last_result_r_enum
{
    LABEL LBL_LAST_RESULT;
    HELP  HLP5(HLP_LAST_RESULT);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_LAST_RESULT
    }
    HANDLING READ;
}
VARIABLE  _last_result_r
{
    LABEL LBL_LAST_RESULT;
    HELP  HLP5(HLP_LAST_RESULT);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
    HANDLING READ;
}
VARIABLE  _leakage_class
{
    LABEL LBL_LEAKAGE_CLASS;
    HELP  HLP5(HLP_LEAKAGE_CLASS);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _limit_hi
{
    LABEL LBL_LIMIT_HI;
    HELP  HLP5(HLP_LIMIT_HI);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(10,110)
    /* HANDLING READ; */
}
VARIABLE  _limit_lo
{
    LABEL LBL_LIMIT_LO;
    HELP  HLP5(HLP_LIMIT_LO);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-10,50)
    /* HANDLING READ; */
}
VARIABLE  _limit_rate
{
    LABEL LBL_LIMIT_RATE;
    HELP  HLP5(HLP_LIMIT_RATE);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(0.49,100.1)
    /* HANDLING READ; */
}
VARIABLE  _limits_protected
{
    LABEL LBL_LIMITS_PROTECTED;
    HELP  HLP5(HLP_LIMITS_PROTECTED);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
}
VARIABLE  _manufacturer
{
    LABEL LBL_MANUFACTURER;
    HELP  HLP5(HLP_MANUFACTURER);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _message
{
    LABEL LBL_MESSAGE;
    HELP  HLP5(HLP_MESSAGE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _model
{
    LABEL LBL_MODEL;
    HELP  HLP5(HLP_MODEL);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
#if 0 /*check data limits before deleting*/
			VARIABLE  _near_close_alert
			{
			    LABEL LBL_NEAR_CLOSE_ALERT;
			    HELP  HLP5(HLP_NEAR_CLOSE_ALERT);
			    CLASS CONTAINED & DYNAMIC;
			    TYPE UNSIGNED_INTEGER (2)
			    DATA_LIMITS(0,0x7D0)
			}
#endif
VARIABLE  _near_closed
{
    LABEL LBL_NEAR_CLOSED;
    HELP  HLP5(HLP_NEAR_CLOSED);
    CLASS CONTAINED & DYNAMIC;
    TYPE UNSIGNED_INTEGER (4);
    CONSTANT_UNIT [unit_code_1059];

}
VARIABLE  _number_of_points_custom_char
{
    LABEL LBL_NUMBER_OF_POINTS_CUSTOM_CHAR;
    HELP  HLP5(HLP_NUMBER_OF_POINTS_CUSTOM_CHAR);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1)
    DATA_LIMITS(0,19)
}
VARIABLE  _packing
{
    LABEL LBL_PACKING;
    HELP  HLP5(HLP_PACKING);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _percent_complete_r
{
    LABEL LBL_PERCENT_COMPLETE;
    HELP  HLP5(HLP_PERCENT_COMPLETE);
    CLASS CONTAINED & DYNAMIC;
    TYPE UNSIGNED_INTEGER (4);
    HANDLING READ;
}
VARIABLE  _pid_no
{
    LABEL LBL_PID_NO;
    HELP  HLP5(HLP_PID_NO);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (1);
}
VARIABLE  _pilot_max
{
    LABEL LBL_PILOT_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _pilot_min
{
    LABEL LBL_PILOT_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _plug_type
{
    LABEL LBL_PLUG_TYPE;
    HELP  HLP5(HLP_PLUG_TYPE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _process_id_r
{
    LABEL LBL_PROCESS_ID;
    HELP  HLP5(HLP_PROCESS_ID);
    CLASS CONTAINED & DYNAMIC;
    TYPE  ENUMERATED (1)
    {
        ENUM_PROCESS_ID
    }
    HANDLING READ;
}
VARIABLE  _qty
{
    LABEL LBL_QTY;
    HELP  HLP5(HLP_QTY);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _rated_adj_cv
{
    LABEL LBL_RATED_ADJ_CV;
    HELP  HLP5(HLP_RATED_ADJ_CV);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _relay_type
{
    LABEL LBL_RELAY_TYPE;
    HELP  HLP5(HLP_RELAY_TYPE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_RELAY_TYPE
    }
}
VARIABLE  _same_as_actuator
{
    LABEL LBL_SAME_AS_ACTUATOR;
    HELP  HLP5(HLP_SAME_AS_ACTUATOR);
    CLASS CONTAINED;
    TYPE  ENUMERATED (1)
    {
        ENUM_ALERT_STATE
    }
}
VARIABLE  _seat_ring_type
{
    LABEL LBL_SEAT_RING_TYPE;
    HELP  HLP5(HLP_SEAT_RING_TYPE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _selector_r
{
    LABEL LBL_SELECTOR;
    HELP  HLP5(HLP_SELECTOR);
    CLASS CONTAINED;
    TYPE INTEGER (2);
    HANDLING READ;
}

VARIABLE  _uint_selector_r
{
    LABEL LBL_SELECTOR;
    HELP  HLP5(HLP_SELECTOR);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
    HANDLING READ;
}


VARIABLE  _service
{
    LABEL LBL_SERVICE;
    HELP  HLP5(HLP_SERVICE);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _shutoff_dp
{
    LABEL LBL_SHUTOFF_DP;
    HELP  HLP5(HLP_SHUTOFF_DP);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
}

#if 0
                VARIABLE  _since_reset
                {
                    LABEL LBL_SINCE_RESET;
                    HELP  HLP5(HLP_SINCE_RESET);
                    CLASS CONTAINED & DYNAMIC;
                    TYPE UNSIGNED_INTEGER (4);
                    CONSTANT_UNIT [unit_code_1059];
                }
#endif

#if 0
VARIABLE  _solenoid
{
    LABEL LBL_SOLENOID;
    HELP  HLP5(HLP_SOLENOID);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}

VARIABLE  _remote_sensor
{
    LABEL LBL_REMOTE_SENSOR;
    HELP  HLP5(HLP_REMOTE_SENSOR);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_REMOTE_SENSOR
    }
}
#endif

VARIABLE  _spec_sheet
{
    LABEL LBL_SPEC_SHEET;
    HELP  HLP5(HLP_SPEC_SHEET);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _stop_hi_pos
{
    LABEL LBL_STOP_HI_POS;
    HELP  HLP5(HLP_STOP_HI_POS);
    CLASS CONTAINED;
    TYPE INTEGER (4);
    /* HANDLING IF ( PARAM.TRAVEL_CALIBRATION.CAL_TYPE == 43 ) { READ & WRITE;} */
    /*     ELSE { READ; } */
}
VARIABLE  _stop_lo_pos
{
    LABEL LBL_STOP_LO_POS;
    HELP  HLP5(HLP_STOP_LO_POS);
    CLASS CONTAINED;
    TYPE INTEGER (4);
    /* HANDLING IF ( PARAM.TRAVEL_CALIBRATION.CAL_TYPE == 43 ) { READ & WRITE;} */
    /*     ELSE { READ; } */

}
VARIABLE  _supply_pressure_max
{
    LABEL LBL_SUPPLY_PRESSURE_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
VARIABLE  _supply_pressure_min
{
    LABEL LBL_SUPPLY_PRESSURE_MIN;
    HELP  HLP5(HLP_VALUE_MIN);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS_FOR_PRESS_UNITS(-25,1050)
}
#if 0
VARIABLE  _time_uint_4
{
    LABEL LBL_TIME;
    HELP  HLP5(HLP_TIME);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (4)
    DATA_LIMITS(0,3600)
    CONSTANT_UNIT [unit_code_1054];
}
#endif
VARIABLE  _time_float
{
    LABEL LBL_TIME;
    HELP  HLP5(HLP_TIME);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(1,60)
    CONSTANT_UNIT [unit_code_1054];
}

#if 0
VARIABLE  _total_time_r
{
    LABEL LBL_TOTAL_TIME;
    HELP  HLP5(HLP_TOTAL_TIME);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (4);
    HANDLING READ;
    CONSTANT_UNIT [unit_code_1059];
}
#endif

_alert_total_time_r LIKE VARIABLE total_time_r
{
    REDEFINE LABEL LBL_ALERT_TOTAL_TIME;
    REDEFINE HELP  HLP5(HLP_ALERT_TOTAL_TIME);
}

VARIABLE  _units_index_percent_r
{
    LABEL LBL_UNITS_INDEX_PERCENT;
    HELP  HLP5(HLP_UNITS_INDEX_PERCENT);
    CLASS CONTAINED;
    TYPE ENUMERATED (2)
    {
        ENUM_UNITS_INDEX_1342
    }
    HANDLING READ;
}
VARIABLE  _units_index_press
{
    LABEL LBL_UNITS_INDEX_PRESS;
    HELP  HLP5(HLP_UNITS_INDEX_PRESS);
    CLASS CONTAINED;
    TYPE ENUMERATED (2)
    {
        ENUM_UNITS_INDEX_PRESS
    }
}

VARIABLE  _value_ip_r
{
    LABEL LBL_VALUE_IP;
    HELP  HLP5(HLP_VALUE_IP);
    CLASS CONTAINED & DYNAMIC;
    TYPE FLOAT;
    HANDLING READ;
    CONSTANT_UNIT [unit_code_1342];
}
VARIABLE  _value_open_close_r
{
    LABEL LBL_VALUE_OPEN_CLOSE;
    HELP  HLP5(HLP_VALUE_OPEN_CLOSE);
    CLASS CONTAINED & DYNAMIC;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    HANDLING        READ ;
}
VARIABLE  _valve_man_id
{
    LABEL LBL_VALVE_MAN_ID;
    HELP  HLP5(HLP_VALVE_MAN_ID);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _valve_model_num
{
    LABEL LBL_VALVE_MODEL_NUM;
    HELP  HLP5(HLP_VALVE_MODEL_NUM);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _valve_sn
{
    LABEL LBL_VALVE_SN;
    HELP  HLP5(HLP_VALVE_SN);
    CLASS CONTAINED;
    TYPE VISIBLE (32);
}
VARIABLE  _valve_type
{
    LABEL LBL_VALVE_TYPE;
    HELP  HLP5(HLP_VALVE_TYPE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_VALVE_TYPE
    }
}
VARIABLE _working_pos_max
{
    LABEL LBL_WORKING_POS_MAX;
    HELP  HLP5(HLP_VALUE_MAX);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(-50,199)
    CONSTANT_UNIT [unit_code_1342];
}
#if 0
			VARIABLE  _working_pos_min
			{
			    LABEL LBL_WORKING_POS_MIN;
			    HELP  HLP5(HLP_VALUE_MIN);
			    CLASS CONTAINED;
			    TYPE FLOAT
			    DATA_LIMITS(-50,199)
			    CONSTANT_UNIT [unit_code_1342];
			}
			VARIABLE  _working_sp_max
			{
			    LABEL LBL_WORKING_SP_MAX;
			    HELP  HLP5(HLP_VALUE_MAX);
			    CLASS CONTAINED;
			    TYPE FLOAT
			    DATA_LIMITS(-50,199)
			    CONSTANT_UNIT [unit_code_1342];
			}
			VARIABLE  _working_sp_min
			{
			    LABEL LBL_WORKING_SP_MIN;
			    HELP  HLP5(HLP_VALUE_MIN);
			    CLASS CONTAINED;
			    TYPE FLOAT
			    DATA_LIMITS(-50,199)
			    CONSTANT_UNIT [unit_code_1342];
			}
#else
_working_pos_min LIKE VARIABLE _working_pos_max
{
    REDEFINE LABEL LBL_WORKING_POS_MIN;
    REDEFINE HELP  HLP5(HLP_VALUE_MIN);
}
_working_sp_max LIKE VARIABLE _working_pos_max
{
    REDEFINE LABEL LBL_WORKING_SP_MAX;
}
_working_sp_min LIKE VARIABLE _working_pos_max
{
    REDEFINE LABEL LBL_WORKING_SP_MIN;
    REDEFINE HELP  HLP5(HLP_VALUE_MIN);
}
#endif


cutoff_point_hi LIKE VARIABLE float_nd_with_max_min
{
	REDEFINE LABEL "|en|Threshold Point,%";
    REDEFINE HELP HLP5(HLP_FLOAT_VALUE);
    REDEFINE_DATA_LIMITS(FLOAT, 80,101)
}

cutoff_point_lo LIKE VARIABLE float_nd_with_max_min
{
	REDEFINE LABEL "|en|Threshold Point,%";
    REDEFINE HELP HLP5(HLP_FLOAT_VALUE);
    REDEFINE_DATA_LIMITS(FLOAT, -1,20)
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
*** variables needed to be refined
/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

VARIABLE raw_position
{
    LABEL LBL_RAW_POSITION;
    HELP  HLP5(HLP_RAW_POSITION);
    CLASS CONTAINED & DYNAMIC;
    TYPE  INTEGER (4);
    HANDLING READ;
}

VARIABLE position_transducer_type
{
    LABEL LBL_043_POSITION_TRANSDUCER_TYPE;
    HELP  HLP5(HLP_043_POSITION_TRANSDUCER_TYPE);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
    HANDLING READ;
}

VARIABLE activate_control_set
{
    LABEL LBL_071_ACTIVATE_CONTROL_SET;
    HELP  HLP5(HLP_071_ACTIVATE_CONTROL_SET);
    CLASS CONTAINED & DYNAMIC;
    TYPE ENUMERATED (1)
    {
        ENUM_ACTIVATE_CONTROL_SET
    }
}

ARRAY current_char_points
{
    LABEL LBL_CURRENT_CHAR_POINTS;
    HELP  HLP5(HLP_CURRENT_CHAR_POINTS);
    TYPE int_2_element_r;
    NUMBER_OF_ELEMENTS NBRS_CHAR_ARRAY;
}
ARRAY custom_char_points
{
    LABEL LBL_287_CUSTOM_CHAR_POINTS;
    HELP HLP5(HLP_287_CUSTOM_CHAR_POINTS);
    TYPE int_2_element;
    NUMBER_OF_ELEMENTS NBRS_CHAR_ARRAY;
}
ARRAY advanced
{
    LABEL LBL_ADVANCED;
    HELP HLP5(HLP_ADVANCED);
    TYPE uint_4_element_nd;
    NUMBER_OF_ELEMENTS 14;
}

VARIABLE transducer_type
{
    LABEL LBL_289_TRANSDUCER_TYPE;
    HELP  HLP5(HLP_289_TRANSDUCER_TYPE);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
    HANDLING READ;
}
VARIABLE temp_transducer_type
{
    LABEL LBL_339_TEMP_TRANSDUCER_TYPE;
    HELP  HLP5(HLP_339_TEMP_TRANSDUCER_TYPE);
    CLASS CONTAINED;
    TYPE UNSIGNED_INTEGER (2);
    HANDLING READ;
}

start_position LIKE VARIABLE __float_contained_nd
{
    REDEFINE LABEL LBL_START_POSITION;
    REDEFINE HELP  HLP5(HLP_START_POSITION);
}

end_position LIKE VARIABLE __float_contained_nd
{
    REDEFINE LABEL LBL_END_POSITION;
    REDEFINE HELP  HLP5(HLP_END_POSITION);
}

set_point_rate LIKE VARIABLE __float_contained_nd
{
    REDEFINE LABEL LBL_SET_POINT_RATE;
    REDEFINE HELP  HLP5(HLP_SET_POINT_RATE);
    REDEFINE CONSTANT_UNIT [unit_code_1713];
}
sampling_time LIKE VARIABLE uint_2_element
{
    REDEFINE LABEL LBL_SAMPLING_TIME;
    REDEFINE HELP  HLP5(HLP_SAMPLING_TIME);
    REDEFINE CONSTANT_UNIT [unit_code_1054];
}

VARIABLE diag_direction
{
    LABEL "|en|Direction";
    HELP  HLP5(HLP_DIAG_DIRECTION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_DIAG_DIRECTION
    }
}

VARIABLE diag_option
{
    LABEL "|en|Diagnostic Option";
    HELP  HLP5(HLP_DIAG_OPTION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_DIAG_OPTION
    }
}

ARRAY diagnostic_data
{
    LABEL LBL_DIAGNOSTIC_DATA;
    HELP HLP5(HLP_DIAGNOSTIC_DATA);
    TYPE uint_2_element_d;
    NUMBER_OF_ELEMENTS 27;
}

VARIABLE custom_1_configuration
{
    LABEL LBL_CUSTOM_1_CONFIGURATION;
    HELP  HLP5(HLP_CUSTOM_CONFIGURATION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_UI_CUSTOM_CONFIGURATION
    }

}
VARIABLE custom_2_configuration
{
    LABEL LBL_CUSTOM_2_CONFIGURATION;
    HELP  HLP5(HLP_CUSTOM_CONFIGURATION);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_UI_CUSTOM_CONFIGURATION
    }
}
VARIABLE ui_language
{
    LABEL LBL_436_UI_LANGUAGE;
    HELP  HLP5(HLP_436_UI_LANGUAGE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_UI_LANGUAGE
    }
}
VARIABLE app_mode
{
    LABEL LBL_437_APP_MODE;
    HELP  HLP5(HLP_437_APP_MODE);
    CLASS CONTAINED & DYNAMIC;
    TYPE ENUMERATED (1)
    {
        ENUM_APP_MODE
    }
}
RECORD complete_status
{
    LABEL LBL_438_COMPLETE_STATUS;
    HELP HLP5(HLP_438_COMPLETE_STATUS);
    MEMBERS
    {
        DEVICE_STATUS;
    }
}
VARIABLE clear_status
{
    LABEL LBL_439_CLEAR_STATUS;
    HELP  HLP5(HLP_439_CLEAR_STATUS);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_CLEAR_STATUS
    }
}
VARIABLE open_stop_adjustment
{
    LABEL LBL_440_OPEN_STOP_ADJUSTMENT;
    HELP  HLP5(HLP_440_OPEN_STOP_ADJUSTMENT);
    CLASS CONTAINED;
    TYPE FLOAT
    DATA_LIMITS(60.00,100.00)
}
VARIABLE setpoint_source
{
    LABEL LBL_441_SETPOINT_SOURCE;
    HELP  HLP5(HLP_441_SETPOINT_SOURCE);
    CLASS CONTAINED;
    TYPE ENUMERATED (1)
    {
        ENUM_SETPOINT_SOURCE
    }
}

_fstate_value LIKE VARIABLE float_nd_with_max_min
{
    REDEFINE LABEL LBL_FSTATE_VALUE;
    REDEFINE_DATA_LIMITS(FLOAT, -50, 160)
}

VARIABLE _fstate_time
{
    LABEL LBL_FSTATE_TIME;
    HELP  HLP5(HLP_279_FSTATE_TIME);
    CLASS CONTAINED;
    TYPE  FLOAT
	{
		MIN_VALUE 1.0;
		MAX_VALUE 100000.0; /* #15873 */
	}
}

_supply_pres_max LIKE VARIABLE float_nd_with_max_min
{
    REDEFINE LABEL LBL_560_SUPPLY_PRS_MAX;
    REDEFINE HELP  HLP5(HLP_560_SUPPLY_PRS_MAX);
	REDEFINE_DATA_LIMITS(FLOAT, 0, 241.3)
}
_prs_control_hi LIKE VARIABLE float_nd_with_max_min
{
    REDEFINE LABEL LBL_561_PRS_CONTROL_HI;
    REDEFINE HELP  HLP5(HLP_561_PRS_CONTROL_HI);
	REDEFINE_DATA_LIMITS(FLOAT, 0, 103.4)
}
_prs_control_lo  LIKE VARIABLE float_nd_with_max_min
{
    REDEFINE LABEL LBL_562_PRS_CONTROL_LO;
    REDEFINE HELP  HLP5(HLP_562_PRS_CONTROL_LO);
	REDEFINE_DATA_LIMITS(FLOAT, 0, 20.6)
}

/*--------------------------------------/
** Defines all method for TB_METHOD_LIST
/--------------------------------------*/
#if 0
METHOD do_test_wr_limits
{
    LABEL "|en|Test write Limits";
    HELP HLP5("|en|Enable/Disable Position Limits");
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
        unsigned long old_value, new_value;
        int           ivalue;
        int           sel;
        float         flt_buf;
        long          chk_cnt;

        unsigned long us8_hi;
        unsigned long us8_lo;

        /* check mode, if OOS or MAN? */

        id = ITEM_ID(PARAM.POSITION_LIMITS);
        mb = 0;
        status=read_value(id,mb);

        mb = MEMBER_ID(ENABLE_HI);
        status = put_unsigned_value(id, mb, 1);
        mb = MEMBER_ID(ENABLE_LO);
        status = put_unsigned_value(id, mb, 1);
        status = select_from_menu("|en|Select the way to send data:\n", dummy, dummy, 0, \
                                  "|en|send by record;" \
                                  "send by member\n", &ivalue);
        switch (ivalue){
        case 1:
            mb = 0;
            status = send_value(id, mb);
            break;
        case 2:
            mb = MEMBER_ID(ENABLE_HI);
            status = send_value(id, mb);
            mb = MEMBER_ID(ENABLE_LO);
            status = send_value(id, mb);
            break;
        }
        mb = 0;
        status = read_value(id, mb);
        METHOD_FINISHED_MACRO
   }
}
#endif

METHOD do_autotune
{
    LABEL "|en|Auto Tune";
    HELP HLP5("|en|Run the auto tune");
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

				unsigned long parid;
				unsigned long memid;
        unsigned long  old_value, new_value;
        int            ivalue;
        int            ival;
        int            sel;
        long           chk_cnt;
        int step;
        step = 0;

        CHECK_DEVICE_IN_MAN;
        if(status == BLTIN_SUCCESS) {
            step = 1;
            CHECK_DEVICE_IN_PROCESS;
        }

        /* check PID slots */
#define CTLPARAMSET_AUTOTUNE 0
#define CTLPARAMSET_COPY_ACTIVE_TO_CUSTOM 11
        if(status == BLTIN_SUCCESS) {
            step = 2;
            id = ITEM_ID(PARAM.ACTIVE_CONTROL_SET);
            READ_PARAM(id, MEMBER_ID(SELECTOR), "ACTIVE_CONTROL_SET.SELECTOR");
			if(status == BLTIN_SUCCESS) {
				step = 3;
				parid = id;
				memid = MEMBER_ID(SELECTOR);
				status = get_signed_value(parid, memid, &ival);
			}
        }
        if(status == BLTIN_SUCCESS) {
            step = 4;
            if ( ival != CTLPARAMSET_AUTOTUNE )
            {
                get_acknowledgement("|en|NOTE: Device currently does not support auto tune.\n"
                                          "Auto tune operation is allowed only for " \
                                          "active control set 0.\n\n"          \
                                          "Click Next to change to control set 0 or Abort the method now.\n", \
                                          dummy,dummy,0);
                /* switch to custom control set */
                id = ITEM_ID(PARAM.ACTIVATE_CONTROL_SET);
                put_unsigned_value(id, 0, CTLPARAMSET_COPY_ACTIVE_TO_CUSTOM);
                status = SEND_PARAM(id, 0, "ACTIVE_CONTROL_SET");
				if(status == BLTIN_SUCCESS) {
					step = 5;
					put_unsigned_value(id, 0, CTLPARAMSET_AUTOTUNE);
					status = SEND_PARAM(id, 0, "ACTIVE_CONTROL_SET");
				}
            }
        }

        /* check for the limits were set and be protected */
        if(status == BLTIN_SUCCESS) {
            step = 6;
            READ_PARAM(ITEM_ID(PARAM.POSITION_LIMITS), MEMBER_ID(LIMITS_PROTECTED),"POSITION_LIMITS.LIMITS_PROTECTED");
        }

        if(status == BLTIN_SUCCESS) {
            step = 8;
            status = get_unsigned_value(ITEM_ID(PARAM.POSITION_LIMITS), MEMBER_ID(LIMITS_PROTECTED), &us8_buf);
        }
        if(status == BLTIN_SUCCESS) {
            step = 9;
            if ( us8_buf != 0 )
            {

                select_from_menu("|en|The device is in protected mode. \n" \
                                          "disable the protected mode to continue auto tune?", dummy,dummy,0, \
                                          "Yes;No(Abort)", &ivalue);
                if (ivalue != 1 ) {

                    METHOD_ABORT_MACRO;

                }
                else {
                    step = 10;
                    status = put_unsigned_value(ITEM_ID(PARAM.POSITION_LIMITS), MEMBER_ID(LIMITS_PROTECTED), DISABLE);
                    if(status == BLTIN_SUCCESS) {
                        SEND_PARAM(ITEM_ID(PARAM.POSITION_LIMITS), MEMBER_ID(LIMITS_PROTECTED), "POSITION_LIMITS.LIMITS_PROTECTED");
                    }
                }
            }
        }

        /* Input the auto tune parameters */
        if(status == BLTIN_SUCCESS) {
            step = 11;
            ids[0] = ITEM_ID(PARAM.PRESSURE_RANGE);
            mbs[0]=MEMBER_ID(UNITS_INDEX);
            ids[1]=ITEM_ID(PARAM.AUTOTUNE);
            status = read_value(ITEM_ID(PARAM.AUTOTUNE), MEMBER_ID(SUPPLY_PRESS));
        }
        if(status == BLTIN_SUCCESS) {
            status = read_value(ids[0], mbs[0]);
        }
        if(status == BLTIN_SUCCESS) {
            step = 12;
            get_acknowledgement("|en|The fallback supply"
                                " pressure should be at least 5PSI(34.5kPa) above"
                                " the spring range.\nPlease verify the spring range"
                                " and cancel the procedure to adjust the supply"
                                " pressure if necessary.", ids, mbs, 1);
            select_from_menu("|en|Do you want to change auto tune parameters. \n", dummy,dummy,0,
                                  "Yes;No", &ivalue);
            if ( ivalue == 1 )
            {
                status = edit_device_value("|en|Fallback Supply Pressure, %{0}:", ids, mbs, 1, ids[1], MEMBER_ID(SUPPLY_PRESS));
                if(status == BLTIN_SUCCESS) {
                    step = 13;
                    mbs[1]=MEMBER_ID(AGGRESSIVENESS);

                    status = get_signed_value(ids[1], mbs[1], &ivalue);
                    do {
                        if(status == BLTIN_SUCCESS) {
                            step = 14;
                            status = edit_device_value("|en|Agressiveness(%[d]{ivalue})[-9, +9]:", dummy, dummy, 0, ids[1], mbs[1]);
                        }
                        if(status == BLTIN_SUCCESS) {
                            step = 15;
                            status = get_signed_value(ids[1], mbs[1], &sel);
                        }
                        if(status != BLTIN_SUCCESS) {
                            break;
                        }
                    } while (sel < -9 || sel > 9);
                }
				if(status == BLTIN_SUCCESS) {
					step = 1601;
					status = SEND_PARAM(ITEM_ID(PARAM.AUTOTUNE), MEMBER_ID(SUPPLY_PRESS), "PARAM.AUTOTUNE.SUPPLY_PRESS");
					status = SEND_PARAM(ITEM_ID(PARAM.AUTOTUNE), MEMBER_ID(AGGRESSIVENESS), "PARAM.AUTOTUNE.AGGRESSIVENESS");				
				}
            }
        }

        /* Start the process */
        if(status == BLTIN_SUCCESS) {
            step = 17;
            select_from_menu("|en|This procedure will take a few minutes to complete.\n" \
                                  "Elapsed time will be updated periodically.\n\n" \
                                  "Proceed?\n", \
                                  dummy, dummy, 0, "Yes;No(Abort)", &ivalue);
            if ( ivalue == 2 ) {
                METHOD_ABORT_MACRO;
            }

            /* start to Auto Tune */
            id = ITEM_ID(PARAM.AUTOTUNE);
            mb = MEMBER_ID(COMPLETION);
            put_unsigned_value(id, mb, AUTOTUNE_START);
            status = SEND_PARAM(ITEM_ID(PARAM.AUTOTUNE), MEMBER_ID(COMPLETION), "AUTOTUNE.COMPLETION");
            
        }

        if(status == BLTIN_SUCCESS) {
            step = 18;
            status = add_abort_method(ITEM_ID(cancel_process));
        }

#define REFRESH_RATE 3
        if(status == BLTIN_SUCCESS) {
			chk_cnt = 0;
			do {

				delayfor( REFRESH_RATE, "|en|The auto tune is running(%[d]{chk_cnt} seconds)...\n"
					"NOTE: If it runs for too long, e.g. longer than 600 s,"
					"you may want to abort the process." , dummy, dummy, 0);

				/* check the status for find stops in the device status*/
				id = ITEM_ID(PARAM.AUTOTUNE);
				mb = MEMBER_ID(COMPLETION);
				if(status == BLTIN_SUCCESS) {
					step = 19;
					READ_PARAM(id, mb, "AUTOTUNE.COMPLETION");
				}
				if(status == BLTIN_SUCCESS) {
					step = 20;
					status = get_unsigned_value(id, mb, &us8_buf);
				}
				if(status != BLTIN_SUCCESS) {
					break;
				}
				chk_cnt += REFRESH_RATE;
			} while ( us8_buf == AUTOTUNE_START || us8_buf == AUTOTUNE_RUNNING );
		}
		
        remove_all_abort_methods();

        if(status == BLTIN_SUCCESS) {
            step = 21;
            /* Waiting for COMPLETE_STATUS to update */
            delayfor( 5, "|en|Waiting for status update...", dummy, dummy, 0);
            /* report auto tune success/failed */
            id = ITEM_ID(PARAM.COMPLETE_STATUS);
            mb = MEMBER_ID(CURRENT_STATUS_1_C);
            READ_PARAM(id, mb, "COMPLETE_STATUS.CURRENT_STATUS_1_C");
        }
        if(status == BLTIN_SUCCESS) {
            step = 22;
            status = get_unsigned_value(id, mb, &us8_buf);

            if ( (us8_buf & FBIT2 ) != 0 ) {
                /* display the reason of failed tuning.*/
                id = ITEM_ID(PARAM.AUTOTUNE);
                mb = MEMBER_ID(COMPLETION);
                status = get_unsigned_value(id, mb, &us8_buf);
                if ( us8_buf > 30 ) {
                    maxlen = 255;
                    status = get_status_string(id, mb, us8_buf, str_buf, maxlen);
                    get_acknowledgement("|en|Auto tune failed due to \"%{str_buf}\".", dummy,dummy,0);
                }
                else
                {
                    get_acknowledgement("|en|Auto tune failed.", dummy,dummy,0);
                }
            }
            else {
                /* read the auto tune parameters */
                get_acknowledgement("|en|Auto tune finished.", dummy, dummy, 0);
            }
        }
        else {
			if(status == BLTIN_FAIL_COMM_ERROR)
			{
				get_acknowledgement("|en|Failed to start procedure\nVerify Write Lock state in Resource Block.", dummy,dummy,0);
                mb = get_comm_error();
				if(mb!=0) {
					display_comm_error(mb);
				}
            }
            else {
                display_builtin_error(status);
				get_acknowledgement("|en|Method failed in step %{step}: status %{status}.\n", dummy, dummy, 0);
            }

        }
    }
}

METHOD cancel_process
{
	LABEL "|en|Cancel Process";
	HELP HLP5("|en|The method aborts any running process.");
	CLASS OUTPUT;
	DEFINITION
	{
	COMMON_LOCAL_VARS;
	SEND_DIAG_COMMAND(DIAG_CANCEL_TEST);
	}
}

METHOD check_process_btn
{
    LABEL "|en|Start PST";
	HELP HLP5("|en|To start PST, ensure TB is in Manual mode.\n"
         "The method checks if another process is running and whether the device already contains a data set.");
    CLASS INPUT;
    DEFINITION
    {
		COMMON_LOCAL_VARS;
		SEND_DIAG_COMMAND(DIAG_PST_START);
    }
}

METHOD change_app_mode
{
    LABEL "|en|Change App Mode";
    HELP  "|en|Restore the app mode to Normal.";
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        int            ivalue;

        maxlen = 256;
        id = ITEM_ID(PARAM.APP_MODE);
        mb = 0;

        status = read_value(id, mb);
        if(status == BLTIN_SUCCESS) {
            status = get_unsigned_value(id, mb, &us8_buf);
        }
        if(status == BLTIN_SUCCESS) {
            status = get_status_string(id, mb, us8_buf, str_buf, maxlen);
        }
        if(status != BLTIN_SUCCESS) {
            get_acknowledgement("|en|Unexpected error occurred. Please try again.\n\n", dummy, dummy, 0);
        }
        else if ( us8_buf == CHANGE_NORMAL ) {
            get_acknowledgement("|en|Positioner is already under system control.\n"
            "The method is only applicable for LO mode of Transducer Block.\n\n", dummy, dummy, 0);
        }
        else {
            status = select_from_menu("|en| "
            "CAUTION!\nThere may be local personnel working with the valve.\n"
            "Make sure it is safe to switch the positioner to normal control.\n\n"
            "APP_MODE" " = %{str_buf}.\n" "Do you want to proceed?" "\n",
                                    dummy, dummy, 0, "|en|Yes;No(Skip)", &ivalue);
            get_acknowledgement("|en|\n", dummy, dummy, 0);
            if ( ivalue == 1 ) {

                status = put_unsigned_value(id, mb, CHANGE_NORMAL);
                SEND_PARAM(id, mb, "APP_MODE");

                READ_PARAM(id, mb, "APP_MODE");
                status = get_unsigned_value(id, 0, &us8_buf);
                status = get_status_string(id, 0, us8_buf, str_buf, maxlen);
                status = get_acknowledgement("|en| ""APP_MODE" " = %{str_buf}.\n",
                                             dummy, dummy, 0);
            }
            else {
                get_acknowledgement("|en|No changes made.\n\n", dummy, dummy, 0);
            }
        }

    }
}

METHOD  clear_current_fault
{
    LABEL "|en|Clear Current Fault";
    HELP HLP5("|en|Clear current status and faults.");
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        id = ITEM_ID(PARAM.CLEAR_STATUS);
        mb = 0;

        status = put_unsigned_value(id, mb, CLEAR_CURRENT_STATUS);
        SEND_PARAM(id, mb, "CLEAR_STATUS:CURRENT");
        get_acknowledgement("|en|\nCurrent faults was cleared.", dummy,dummy, 0);

    }
}

METHOD  clear_all_fault
{
    LABEL "|en|Clear All Faults";
    HELP HLP5("|en|Clear all status and faults.");
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        id = ITEM_ID(PARAM.CLEAR_STATUS);
        mb = 0;

        status = put_unsigned_value(id, mb, CLEAR_ALL_STATUS);
        SEND_PARAM(id, mb, "CLEAR_STATUS:ALL");
        get_acknowledgement("|en|\n Current and historic faults was cleared.", dummy,dummy, 0);

    }
}

METHOD clear_travel_trend
{
    LABEL "|en|Clear Travel Trend";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_TREND_TRAVEL);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_TREND_TRAVEL");

		ids[17] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[17] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[17], mbs[17],"TRAVEL_ACCUMULATION_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"TRAVEL_ACCUMULATION_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"TRAVEL_ACCUMULATION_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"TRAVEL_ACCUMULATION_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"TRAVEL_ACCUMULATION_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"TRAVEL_ACCUMULATION_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"TRAVEL_ACCUMULATION_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"TRAVEL_ACCUMULATION_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"TRAVEL_ACCUMULATION_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"TRAVEL_ACCUMULATION_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"TRAVEL_ACCUMULATION_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"TRAVEL_ACCUMULATION_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"TRAVEL_ACCUMULATION_TREND.THREE_YEARS_AGO");

        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
								   }
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_travel_trend
{
	LABEL "|en|Refresh Travel Trend";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

		ids[0] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[0] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.TRAVEL_ACCUMULATION_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[0], mbs[0],"TRAVEL_ACCUMULATION_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"TRAVEL_ACCUMULATION_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"TRAVEL_ACCUMULATION_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"TRAVEL_ACCUMULATION_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"TRAVEL_ACCUMULATION_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"TRAVEL_ACCUMULATION_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"TRAVEL_ACCUMULATION_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"TRAVEL_ACCUMULATION_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"TRAVEL_ACCUMULATION_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"TRAVEL_ACCUMULATION_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"TRAVEL_ACCUMULATION_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"TRAVEL_ACCUMULATION_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"TRAVEL_ACCUMULATION_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"TRAVEL_ACCUMULATION_TREND.THREE_YEARS_AGO");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}

METHOD clear_cycle_counter
{
	LABEL "|en|Clear Cycle Counter";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_TREND_CYCLE_COUNT);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_TREND_CYCLE_COUNTER");

		ids[17] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[17] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[17], mbs[17],"CYCLE_COUNTER_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"CYCLE_COUNTER_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"CYCLE_COUNTER_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"CYCLE_COUNTER_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"CYCLE_COUNTER_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"CYCLE_COUNTER_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"CYCLE_COUNTER_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"CYCLE_COUNTER_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"CYCLE_COUNTER_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"CYCLE_COUNTER_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"CYCLE_COUNTER_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"CYCLE_COUNTER_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"CYCLE_COUNTER_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"CYCLE_COUNTER_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"CYCLE_COUNTER_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"CYCLE_COUNTER_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"CYCLE_COUNTER_TREND.THREE_YEARS_AGO");

        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
        }
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_cycle_counter
{
	LABEL "|en|Refresh Cycle Counter";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

		ids[0] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[0] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.CYCLE_COUNTER_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[0], mbs[0],"CYCLE_COUNTER_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"CYCLE_COUNTER_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"CYCLE_COUNTER_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"CYCLE_COUNTER_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"CYCLE_COUNTER_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"CYCLE_COUNTER_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"CYCLE_COUNTER_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"CYCLE_COUNTER_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"CYCLE_COUNTER_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"CYCLE_COUNTER_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"CYCLE_COUNTER_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"CYCLE_COUNTER_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"CYCLE_COUNTER_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"CYCLE_COUNTER_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"CYCLE_COUNTER_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"CYCLE_COUNTER_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"CYCLE_COUNTER_TREND.THREE_YEARS_AGO");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}

METHOD clear_position_error_trend
{
	LABEL "|en|Clear Position Error Trend";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_TREND_POS_ERROR);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_TREND_POSITION_ERROR");

		ids[17] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[17] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[17], mbs[17],"POSITION_ERROR_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"POSITION_ERROR_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"POSITION_ERROR_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"POSITION_ERROR_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"POSITION_ERROR_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"POSITION_ERROR_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"POSITION_ERROR_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"POSITION_ERROR_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"POSITION_ERROR_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"POSITION_ERROR_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"POSITION_ERROR_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"POSITION_ERROR_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"POSITION_ERROR_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"POSITION_ERROR_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"POSITION_ERROR_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"POSITION_ERROR_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"POSITION_ERROR_TREND.THREE_YEARS_AGO");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_position_error_trend
{
	LABEL "|en|Refresh Position Error Trend";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

		ids[0] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[0] = MEMBER_ID(CURRENTLY_COLLECTED);

		ids[1] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[1] = MEMBER_ID(TODAY);

		ids[2] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[2] = MEMBER_ID(LAST_DAY);

		ids[3] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[3] = MEMBER_ID(PREVIOUS_DAY);

		ids[4] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[4] = MEMBER_ID(THREE_DAYS_AGO);

		ids[5] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[5] = MEMBER_ID(CURRENT_WEEK);

		ids[6] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[6] = MEMBER_ID(LAST_WEEK);

		ids[7] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[7] = MEMBER_ID(PREVIOUS_WEEK);

		ids[8] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[8] = MEMBER_ID(THREE_WEEKS_AGO);

		ids[9] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[9] = MEMBER_ID(CURRENT_MONTH);

		ids[10] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[10] = MEMBER_ID(LAST_MONTH);

		ids[11] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[11] = MEMBER_ID(PREVIOUS_MONTH);

		ids[12] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[12] = MEMBER_ID(THREE_MONTHS_AGO);

		ids[13] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[13] = MEMBER_ID(CURRENT_12_MONTHS);

		ids[14] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[14] = MEMBER_ID(LAST_12_MONTHS);

		ids[15] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[15] = MEMBER_ID(PREVIOUS_12_MONTHS);

		ids[16] = ITEM_ID(PARAM.POSITION_ERROR_TREND);
		mbs[16] = MEMBER_ID(THREE_YEARS_AGO);
			
		READ_PARAM(ids[0], mbs[0],"POSITION_ERROR_TREND.CURRENTLY_COLLECTED");
		READ_PARAM(ids[1], mbs[1],"POSITION_ERROR_TREND.TODAY");
		READ_PARAM(ids[2], mbs[2],"POSITION_ERROR_TREND.LAST_DAY");
		READ_PARAM(ids[3], mbs[3],"POSITION_ERROR_TREND.PREVIOUS_DAY");
		READ_PARAM(ids[4], mbs[4],"POSITION_ERROR_TREND.THREE_DAYS_AGO");
		READ_PARAM(ids[5], mbs[5],"POSITION_ERROR_TREND.CURRENT_WEEK");
		READ_PARAM(ids[6], mbs[6],"POSITION_ERROR_TREND.LAST_WEEK");
		READ_PARAM(ids[7], mbs[7],"POSITION_ERROR_TREND.PREVIOUS_WEEK");
		READ_PARAM(ids[8], mbs[8],"POSITION_ERROR_TREND.THREE_WEEKS_AGO");
		READ_PARAM(ids[9], mbs[9],"POSITION_ERROR_TREND.CURRENT_MONTH");
		READ_PARAM(ids[10], mbs[10],"POSITION_ERROR_TREND.LAST_MONTH");
		READ_PARAM(ids[11], mbs[11],"POSITION_ERROR_TREND.PREVIOUS_MONTH");
		READ_PARAM(ids[12], mbs[12],"POSITION_ERROR_TREND.THREE_MONTHS_AGO");
		READ_PARAM(ids[13], mbs[13],"POSITION_ERROR_TREND.CURRENT_12_MONTHS");
		READ_PARAM(ids[14], mbs[14],"POSITION_ERROR_TREND.LAST_12_MONTHS");
		READ_PARAM(ids[15], mbs[15],"POSITION_ERROR_TREND.PREVIOUS_12_MONTHS");
		READ_PARAM(ids[16], mbs[16],"POSITION_ERROR_TREND.THREE_YEARS_AGO");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}

METHOD clear_position_histogram
{
	LABEL "|en|Clear Position Histogram";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_POSITION_HISTOGRAM);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_POSITION_HISTOGRAM");

		ids[13] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[13] = MEMBER_ID(TOTAL_TIME);

		ids[1] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[1] = MEMBER_ID(POS_5_PERCENT_CLOSED);

		ids[2] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[2] = MEMBER_ID(POS_10_PERCENT);

		ids[3] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[3] = MEMBER_ID(POS_20_PERCENT);

		ids[4] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[4] = MEMBER_ID(POS_30_PERCENT);

		ids[5] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[5] = MEMBER_ID(POS_40_PERCENT);

		ids[6] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[6] = MEMBER_ID(POS_50_PERCENT);

		ids[7] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[7] = MEMBER_ID(POS_60_PERCENT);

		ids[8] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[8] = MEMBER_ID(POS_70_PERCENT);

		ids[9] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[9] = MEMBER_ID(POS_80_PERCENT);

		ids[10] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[10] = MEMBER_ID(POS_90_PERCENT);

		ids[11] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[11] = MEMBER_ID(POS_95_PERCENT);

		ids[12] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[12] = MEMBER_ID(POS_95_PERCENT_OPEN);
		
		READ_PARAM(ids[13], mbs[13],"POSITION_HISTOGRAM.TOTAL_TIME");
		READ_PARAM(ids[1], mbs[1],"POSITION_HISTOGRAM.POS_5_PERCENT_CLOSED");
		READ_PARAM(ids[2], mbs[2],"POSITION_HISTOGRAM.POS_10_PERCENT");
		READ_PARAM(ids[3], mbs[3],"POSITION_HISTOGRAM.POS_20_PERCENT");
		READ_PARAM(ids[4], mbs[4],"POSITION_HISTOGRAM.POS_30_PERCENT");
		READ_PARAM(ids[5], mbs[5],"POSITION_HISTOGRAM.POS_40_PERCENT");
		READ_PARAM(ids[6], mbs[6],"POSITION_HISTOGRAM.POS_50_PERCENT");
		READ_PARAM(ids[7], mbs[7],"POSITION_HISTOGRAM.POS_60_PERCENT");
		READ_PARAM(ids[8], mbs[8],"POSITION_HISTOGRAM.POS_70_PERCENT");
		READ_PARAM(ids[9], mbs[9],"POSITION_HISTOGRAM.POS_80_PERCENT");
		READ_PARAM(ids[10], mbs[10],"POSITION_HISTOGRAM.POS_90_PERCENT");
		READ_PARAM(ids[11], mbs[11],"POSITION_HISTOGRAM.POS_95_PERCENT");
		READ_PARAM(ids[12], mbs[12],"POSITION_HISTOGRAM.POS_95_PERCENT_OPEN");		

        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
        }
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_position_histogram
{
	LABEL "|en|Refresh Position Histogram";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		ids[0] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[0] = MEMBER_ID(TOTAL_TIME);

		ids[1] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[1] = MEMBER_ID(POS_5_PERCENT_CLOSED);

		ids[2] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[2] = MEMBER_ID(POS_10_PERCENT);

		ids[3] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[3] = MEMBER_ID(POS_20_PERCENT);

		ids[4] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[4] = MEMBER_ID(POS_30_PERCENT);

		ids[5] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[5] = MEMBER_ID(POS_40_PERCENT);

		ids[6] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[6] = MEMBER_ID(POS_50_PERCENT);

		ids[7] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[7] = MEMBER_ID(POS_60_PERCENT);

		ids[8] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[8] = MEMBER_ID(POS_70_PERCENT);

		ids[9] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[9] = MEMBER_ID(POS_80_PERCENT);

		ids[10] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[10] = MEMBER_ID(POS_90_PERCENT);

		ids[11] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[11] = MEMBER_ID(POS_95_PERCENT);

		ids[12] = ITEM_ID(PARAM.POSITION_HISTOGRAM);
		mbs[12] = MEMBER_ID(POS_95_PERCENT_OPEN);
		
		READ_PARAM(ids[0], mbs[0],"POSITION_HISTOGRAM.TOTAL_TIME");
		READ_PARAM(ids[1], mbs[1],"POSITION_HISTOGRAM.POS_5_PERCENT_CLOSED");
		READ_PARAM(ids[2], mbs[2],"POSITION_HISTOGRAM.POS_10_PERCENT");
		READ_PARAM(ids[3], mbs[3],"POSITION_HISTOGRAM.POS_20_PERCENT");
		READ_PARAM(ids[4], mbs[4],"POSITION_HISTOGRAM.POS_30_PERCENT");
		READ_PARAM(ids[5], mbs[5],"POSITION_HISTOGRAM.POS_40_PERCENT");
		READ_PARAM(ids[6], mbs[6],"POSITION_HISTOGRAM.POS_50_PERCENT");
		READ_PARAM(ids[7], mbs[7],"POSITION_HISTOGRAM.POS_60_PERCENT");
		READ_PARAM(ids[8], mbs[8],"POSITION_HISTOGRAM.POS_70_PERCENT");
		READ_PARAM(ids[9], mbs[9],"POSITION_HISTOGRAM.POS_80_PERCENT");
		READ_PARAM(ids[10], mbs[10],"POSITION_HISTOGRAM.POS_90_PERCENT");
		READ_PARAM(ids[11], mbs[11],"POSITION_HISTOGRAM.POS_95_PERCENT");
		READ_PARAM(ids[12], mbs[12],"POSITION_HISTOGRAM.POS_95_PERCENT_OPEN");		
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}

METHOD clear_position_error_histogram
{
	LABEL "|en|Clear Position Err. Histogram";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_POS_ERROR_HISTOGRAM);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_POSITION_ERROR_HISTOGRAM");

		ids[1] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[1] = MEMBER_ID(POS_5_PERCENT_CLOSED);

		ids[2] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[2] = MEMBER_ID(POS_10_PERCENT);

		ids[3] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[3] = MEMBER_ID(POS_20_PERCENT);

		ids[4] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[4] = MEMBER_ID(POS_30_PERCENT);

		ids[5] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[5] = MEMBER_ID(POS_40_PERCENT);

		ids[6] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[6] = MEMBER_ID(POS_50_PERCENT);

		ids[7] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[7] = MEMBER_ID(POS_60_PERCENT);

		ids[8] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[8] = MEMBER_ID(POS_70_PERCENT);

		ids[9] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[9] = MEMBER_ID(POS_80_PERCENT);

		ids[10] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[10] = MEMBER_ID(POS_90_PERCENT);

		ids[11] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[11] = MEMBER_ID(POS_95_PERCENT);

		ids[12] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[12] = MEMBER_ID(POS_95_PERCENT_OPEN);
			
		READ_PARAM(ids[1], mbs[1],"POSITION_ERROR_HISTOGRAM.POS_5_PERCENT_CLOSED");
		READ_PARAM(ids[2], mbs[2],"POSITION_ERROR_HISTOGRAM.POS_10_PERCENT");
		READ_PARAM(ids[3], mbs[3],"POSITION_ERROR_HISTOGRAM.POS_20_PERCENT");
		READ_PARAM(ids[4], mbs[4],"POSITION_ERROR_HISTOGRAM.POS_30_PERCENT");
		READ_PARAM(ids[5], mbs[5],"POSITION_ERROR_HISTOGRAM.POS_40_PERCENT");
		READ_PARAM(ids[6], mbs[6],"POSITION_ERROR_HISTOGRAM.POS_50_PERCENT");
		READ_PARAM(ids[7], mbs[7],"POSITION_ERROR_HISTOGRAM.POS_60_PERCENT");
		READ_PARAM(ids[8], mbs[8],"POSITION_ERROR_HISTOGRAM.POS_70_PERCENT");
		READ_PARAM(ids[9], mbs[9],"POSITION_ERROR_HISTOGRAM.POS_80_PERCENT");
		READ_PARAM(ids[10], mbs[10],"POSITION_ERROR_HISTOGRAM.POS_90_PERCENT");
		READ_PARAM(ids[11], mbs[11],"POSITION_ERROR_HISTOGRAM.POS_95_PERCENT");
		READ_PARAM(ids[12], mbs[12],"POSITION_ERROR_HISTOGRAM.POS_95_PERCENT_OPEN");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
								   }
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_position_error_histogram
{
	LABEL "|en|Refresh Position Err. Histogram";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
        
		ids[1] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[1] = MEMBER_ID(POS_5_PERCENT_CLOSED);

		ids[2] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[2] = MEMBER_ID(POS_10_PERCENT);

		ids[3] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[3] = MEMBER_ID(POS_20_PERCENT);

		ids[4] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[4] = MEMBER_ID(POS_30_PERCENT);

		ids[5] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[5] = MEMBER_ID(POS_40_PERCENT);

		ids[6] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[6] = MEMBER_ID(POS_50_PERCENT);

		ids[7] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[7] = MEMBER_ID(POS_60_PERCENT);

		ids[8] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[8] = MEMBER_ID(POS_70_PERCENT);

		ids[9] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[9] = MEMBER_ID(POS_80_PERCENT);

		ids[10] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[10] = MEMBER_ID(POS_90_PERCENT);

		ids[11] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[11] = MEMBER_ID(POS_95_PERCENT);

		ids[12] = ITEM_ID(PARAM.POSITION_ERROR_HISTOGRAM);
		mbs[12] = MEMBER_ID(POS_95_PERCENT_OPEN);

		READ_PARAM(ids[1], mbs[1],"POSITION_ERROR_HISTOGRAM.POS_5_PERCENT_CLOSED");
		READ_PARAM(ids[2], mbs[2],"POSITION_ERROR_HISTOGRAM.POS_10_PERCENT");
		READ_PARAM(ids[3], mbs[3],"POSITION_ERROR_HISTOGRAM.POS_20_PERCENT");
		READ_PARAM(ids[4], mbs[4],"POSITION_ERROR_HISTOGRAM.POS_30_PERCENT");
		READ_PARAM(ids[5], mbs[5],"POSITION_ERROR_HISTOGRAM.POS_40_PERCENT");
		READ_PARAM(ids[6], mbs[6],"POSITION_ERROR_HISTOGRAM.POS_50_PERCENT");
		READ_PARAM(ids[7], mbs[7],"POSITION_ERROR_HISTOGRAM.POS_60_PERCENT");
		READ_PARAM(ids[8], mbs[8],"POSITION_ERROR_HISTOGRAM.POS_70_PERCENT");
		READ_PARAM(ids[9], mbs[9],"POSITION_ERROR_HISTOGRAM.POS_80_PERCENT");
		READ_PARAM(ids[10], mbs[10],"POSITION_ERROR_HISTOGRAM.POS_90_PERCENT");
		READ_PARAM(ids[11], mbs[11],"POSITION_ERROR_HISTOGRAM.POS_95_PERCENT");
		READ_PARAM(ids[12], mbs[12],"POSITION_ERROR_HISTOGRAM.POS_95_PERCENT_OPEN");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}

METHOD clear_working_times
{
	LABEL "|en|Clear Working Times";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;
		unsigned long value;

		ids[0] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);
		mbs[0] = 0;

		status = put_unsigned_value(ids[0], mbs[0], DIAG_CLEAR_WORKING_TIMES);
		SEND_PARAM(ids[0], mbs[0], "DIAG_CLEAR_WORKING_TIMES");

		ids[1] = ITEM_ID(PARAM.WORKING_TIMES);
		mbs[1] = MEMBER_ID(SINCE_RESET);

		ids[2] = ITEM_ID(PARAM.WORKING_TIMES);
		mbs[2] = MEMBER_ID(TOTAL_TIME);
		
		READ_PARAM(ids[1], mbs[1],"WORKING_TIMES.SINCE_RESET");
		READ_PARAM(ids[2], mbs[2],"WORKING_TIMES.TOTAL_TIME");

        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Done", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Failed", dummy,dummy, 0);
        }
	}
}

METHOD refresh_working_times
{
	LABEL "|en|Update Working Times";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

		ids[0] = ITEM_ID(PARAM.WORKING_TIMES);
		mbs[0] = MEMBER_ID(SINCE_RESET);

		ids[1] = ITEM_ID(PARAM.WORKING_TIMES);
		mbs[1] = MEMBER_ID(TOTAL_TIME);
		
		READ_PARAM(ids[0], mbs[0],"WORKING_TIMES.SINCE_RESET");
		READ_PARAM(ids[1], mbs[1],"WORKING_TIMES.TOTAL_TIME");
		
        if(status == BLTIN_SUCCESS){
			get_acknowledgement("|en|Refresh succeeded.", dummy,dummy, 0);
		}
        else {
            get_acknowledgement("|en|Refresh failed.", dummy,dummy, 0);
        }
	}
}