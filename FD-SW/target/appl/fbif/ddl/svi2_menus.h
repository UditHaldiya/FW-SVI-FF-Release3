#ifndef TB_MENU_2013_01_29_13_13_36_GE_300010777
#define TB_MENU_2013_01_29_13_13_36_GE_300010777
#define TS_MENU "Time-stamp: <2013-11-25 09:49:34 GE-300010777>"

#ifndef NOMENUS
#include "aggregwraps.h"
#include "svi_tb.h"

/*---------------------------------------------/
** All parameters
/---------------------------------------------*/

/*---------------------------------------------/
** Defines the help string for labels and helps
/---------------------------------------------*/

#define LBL_MN_DEVICE                                   "|en|Device"
#define LBL_MN_DIAG                                     "|en|Diagnostic"
#define LBL_MN_PV                                       "|en|Process Variables"

#define LBL_CONFIGURE_SETUP                             "|en|Configure Setup"
#define LBL_BASIC_SETUP                                 "|en|Basic Setup"
#define LBL_ADVANCED_SETUP                              "|en|Advanced Setup"
#define LBL_CALIBRATION                                 "|en|Calibration"
#define LBL_MAINTENANCE                                 "|en|Maintenance"

#define LBL_STATUS                                      "|en|Status"
#define LBL_ERRORS                                      "|en|Errors"
#define LBL_ALERTS                                      "|en|Alerts"
#define LBL_ALARMS                                      "|en|Alarms"

#define LBL_OVERVIEW                                    "|en|Overview"
#define LBL_TRENDS                                      "|en|Trends"
#define LBL_GAUDGES                                     "|en|Sensors"

#define LBL_MN_CONF                                     "|en|Device"
#define LBL_MN_DS                                       "|en|Diagnostic"

#define LBL_MN_CONF_POSITIONS                           "|en|Positions"
#define LBL_MN_CONF_ACTUATOR                            "|en|Actuator"
#define LBL_MN_CONF_ALERT                               "|en|Alert"
#define LBL_MN_CONF_BLOCK                               "|en|Block"
#define LBL_MN_CONF_CALIBRATION                         "|en|Calibration"
#define LBL_MN_CONF_CHARACTERIZATION                    "|en|Characterization"
#define LBL_MN_CONF_CTRTUNE                             "|en|Ctrtune"
#define LBL_MN_CONF_EXTREMES                            "|en|Extremes"
#define LBL_MN_CONF_FSTATE                              "|en|Fstate"
#define LBL_MN_CONF_IDENT                               "|en|Ident"
#define LBL_MN_CONF_INFORMATION                         "|en|Information"
#define LBL_MN_CONF_LCD                                 "|en|LCD"
#define LBL_MN_CONF_LOCAL                               "|en|Local"
#define LBL_MN_CONF_MAINT                               "|en|Maintenance"
#define LBL_MN_CONF_OTHER                               "|en|Other"
#define LBL_MN_CONF_PROCESS_CONTROL                     "|en|Process Control"
#define LBL_MN_CONF_READBACK                            "|en|Readback"
#define LBL_MN_CONF_SENSOR                              "|en|Sensor"
#define LBL_MN_CONF_SETPOINT                            "|en|Setpoint"
#define LBL_MN_CONF_SWITCHS                             "|en|Switchs"
#define LBL_MN_CONF_TRAVEL                              "|en|Travel"
#define LBL_MN_CONF_VALVE                               "|en|Valve"
#define LBL_MN_CONF_CUT_OFF                             "|en|Cut Off"
#define LBL_MN_CONF_LIMITS                              "|en|Limits"
#define LBL_MN_CONF_RANGE                               "|en|Range"
#define LBL_MN_DS_MODE                                  "|en|Mode"
#define LBL_MN_DS_BLOCK_ERR                             "|en|Block Err"
#define LBL_MN_DS_BLOCK_ERR_UPDATE_EVT                  "|en|Block Err Update Evt"
#define LBL_MN_DS_BLOCK_ALM                             "|en|Block Alm"
#define LBL_MN_DS_ACTUATOR_PRESSURE                     "|en|Actuator Pressure"
#define LBL_MN_DS_ALERTS                                "|en|Alerts"
#define LBL_MN_DS_FF_AP                                 "|en|FF AP"
#define LBL_MN_DS_BLOCK                                 "|en|Block"
#define LBL_MN_DS_BLOCK_ALARM                           "|en|Block Alarm"
#define LBL_MN_DS_METHODS                               "|en|Methods"
#define LBL_MN_DS_PRESSURE                              "|en|Pressure"
#define LBL_MN_DS_STATUS                                "|en|Status"
#define LBL_MN_DS_XD_ERROR                              "|en|Xd Error"
#define LBL_MN_DS_ALERT                                 "|en|Alert"
#define LBL_MN_PV_FINAL_VALUE                           "|en|Final Value"
#define LBL_MN_PV_FINAL_POSITION_VALUE                  "|en|Final Position Value"
#define LBL_MN_PV_DISCRETE                              "|en|Discrete"
#define LBL_MN_PV_FSC                                   "|en|Fsc"
#define LBL_MN_PV_PRESSURE                              "|en|Pressure"
#define LBL_MN_PV_PROCESS_CONTROL                       "|en|Process Control"
#define LBL_MN_PV_SETPOINT                              "|en|Setpoint"
#define LBL_MN_PV_SWITCHS                               "|en|Switchs"
#define LBL_MN_PV_TEMP                                  "|en|Temp"
#define LBL_MN_CONF_ALERT_ACT                           "|en|Alert Act"
#define LBL_MN_CONF_ALERT_COUNTS                        "|en|Alert Counts"
#define LBL_MN_CONF_ALERT_IP_DRIVE_CURRENT              "|en|Alert Ip Drive Current"
#define LBL_MN_CONF_ALERT_PRESSURE                      "|en|Alert Pressure"
#define LBL_MN_CONF_ALERT_SETPOINT                      "|en|Alert Setpoint"
#define LBL_MN_CONF_ALERT_TEMP                          "|en|Alert Temp"
#define LBL_MN_CONF_ALERT_NEAR_CLOSED                   "|en|Alert Near Closed"
#define LBL_MN_CONF_ALERT_POSITION                      "|en|Alert Position"
#define LBL_MN_CONF_ALERT_TRAVEL_ACCUMLATION            "|en|Alert Travel Accumlation"
#define LBL_MN_CONF_CALIBRATION_FINDSTOP                "|en|Findstop"
#define LBL_MN_CONF_CALIBRATION_AUTOTUNE                "|en|Autotune"
#define LBL_MN_CONF_CALIBRATION_METHOD                  "|en|Method"
#define LBL_MN_CONF_CALIBRATION_RESET_PRESSURE          "|en|Reset Pressure"
#define LBL_MN_CONF_CALIBRATION_TRAVEL                  "|en|Travel"
#define LBL_MN_CONF_CALIBRATION_INFO                    "|en|Info"
#define LBL_MN_CONF_CTRTUNE_ACTIVE                      "|en|Ctrtune Active"
#define LBL_MN_CONF_CTRTUNE_CUSTOM                      "|en|Ctrtune Custom"
#define LBL_MN_CONF_CTRTUNE_BACKUP                      "|en|Ctrtune Backup"
#define LBL_MN_CONF_EXTREMES_POSITION_EXTREMES          "|en|Extremes Position Extremes"
#define LBL_MN_CONF_EXTREMES_PRESSURE_EXTREMES          "|en|Extremes Pressure Extremes"
#define LBL_MN_CONF_EXTREMES_TEMPERATURE_EXTREMES       "|en|Extremes Temperature Extremes"
#define LBL_MN_CONF_EXTREMES_IP_CURRENT_EXTREMES        "|en|Extremes Ip Current Extremes"
#define LBL_MN_CONF_FSTATE_XD_FSTATE                    "|en|Fstate Xd Fstate"
#define LBL_MN_CONF_MAINT_CYCLE_COUNTER_A_ALERT         "|en|Cycle Counter A Alert"
#define LBL_MN_CONF_MAINT_CYCLE_COUNTER_B_ALERT         "|en|Cycle Counter B Alert"
#define LBL_MN_CONF_MAINT_CYCLE_COUNTER_TREND           "|en|Cycle Counter Trend"
#define LBL_MN_CONF_MAINT_POSITION_ERROR_TREND          "|en|Position Error Trend"
#define LBL_MN_CONF_MAINT_ALERT_LOG                     "|en|Alert Log"
#define LBL_MN_CONF_MAINT_WORKING_TIMES                 "|en|Working Times"
#define LBL_MN_CONF_MAINT_WORKING_TIME_ALERT            "|en|Working Time Alert"
#define LBL_MN_CONF_MAINT_FACTORY_USE                   "|en|Factory Use"
#define LBL_MN_CONF_MAINT_ERR_HISTOGRAM                 "|en|Err Histogram"
#define LBL_MN_CONF_MAINT_HISTOGRAM                     "|en|Histogram"
#define LBL_MN_CONF_MAINT_TRAVEL_ACCUMULATION_TREND     "|en|Travel Accumulation Trend"
#define LBL_MN_CONF_OTHER_BOOSTER                       "|en|Other Booster"
#define LBL_MN_CONF_OTHER_ACCESSORY                     "|en|Other Accessory"
#define LBL_MN_CONF_SENSOR_PRESSURE                     "|en|Sensor Pressure"
#define LBL_MN_CONF_VALVE_IDENTIFICATION                "|en|Valve Identification"
#define LBL_MN_CONF_VALVE_SERVICE                       "|en|Valve Service"
#define LBL_MN_CONF_VALVE_BODY                          "|en|Valve Body"
#define LBL_MN_DS_ACTUATOR_PRESSURE_A                   "|en|Actuator Pressure A"
#define LBL_MN_DS_ACTUATOR_PRESSURE_B                   "|en|Actuator Pressure B"
#define LBL_MN_DS_ALERT_IP_DRIVE_CURRENT                "|en|Alert Ip Drive Current"
#define LBL_MN_DS_ALERT_PRESSURE                        "|en|Alert Pressure"
#define LBL_MN_DS_ALERT_SETPOINT                        "|en|Alert Setpoint"
#define LBL_MN_DS_ALERT_TEMP                            "|en|Alert Temp"
#define LBL_MN_DS_ALERT_NEAR_CLOSED                     "|en|Alert Near Closed"
#define LBL_MN_DS_PRESSURE_ATMOSPHERIC                  "|en|Pressure Atmospheric"
#define LBL_MN_DS_PRESSURE_PILOT                        "|en|Pressure Pilot"
#define LBL_MN_DS_STATUS_IP_DRIVE                       "|en|Status Ip Drive"
#define LBL_MN_PV_ACTUATOR_SUPPLY                       "|en|Actuator Supply"
#define LBL_MN_PV_ACTUATOR_AB                           "|en|Actuator Ab"
#define LBL_MN_CONF_ALERT_DEVIATION_ALERT               "|en|Deviation Alert"
#define LBL_MN_CONF_ALERT_IP_DRIVE_CURRENT_HI           "|en|Ip Drive Current Hi"
#define LBL_MN_CONF_ALERT_IP_DRIVE_CURRENT_LO           "|en|Ip Drive Current Lo"
#define LBL_MN_CONF_ALERT_PRESSURE_HI                   "|en|Pressure Hi"
#define LBL_MN_CONF_ALERT_PRESSURE_LO                   "|en|Pressure Lo"
#define LBL_MN_CONF_ALERT_PRESSURE_LOLO                 "|en|Pressure Lolo"
#define LBL_MN_CONF_ALERT_TEMP_HI                       "|en|Temp Hi"
#define LBL_MN_CONF_ALERT_TEMP_LO                       "|en|Temp Lo"
#define LBL_MN_CONF_ALERT_POSITION_HI                   "|en|Position Hi"
#define LBL_MN_CONF_ALERT_POSITION_HIHI                 "|en|Position Hihi"
#define LBL_MN_CONF_ALERT_POSITION_LO                   "|en|Position Lo"
#define LBL_MN_CONF_ALERT_POSITION_LOLO                 "|en|Position Lolo"
#define LBL_MN_CONF_ALERT_TRAVEL_ACCUMLATION_A          "|en|Travel Accumlation A"
#define LBL_MN_CONF_ALERT_TRAVEL_ACCUMLATION_B          "|en|Travel Accumlation B"
#define LBL_MN_CONF_CALIBRATION_INFO_TRAVEL             "|en|Calibration Info Travel"
#define LBL_MN_CONF_CALIBRATION_INFO_PRESSURE           "|en|Calibration Info Pressure"
#define LBL_MN_DS_ALERT_PRESSURE_LO                     "|en|Alert Pressure Lo"
#define LBL_MN_DS_ALERT_PRESSURE_LOLO                   "|en|Alert Pressure Lolo"
#define LBL_MN_DATA_COLLECTION_CONFIG					"|en|Data Collection Configuration" /**************************************************/
#define LBL_MN_DATA_COLLECTION_TRIGGER                  "|en|Data Collection Trigger"       /**************************************************/

/*============================/
 * MENUS for Tranceducer Block
 /============================*/

/*----------/
** Top level
/----------*/

MENU Menu_Top_ptb
{
    LABEL "|en|Top";
    ITEMS
    {
        hdevice_ptb
        hdiagnostic_ptb
        hprocess_variables_ptb
        TB_METHOD_LIST
    }
}

MENU hdevice_ptb
{
    LABEL "|en|Device Setup";
    /* STYLE MENU; */
    ITEMS
    {
        mnu_startup
        mnu_tb_process
        mnu_config
        mnu_calibrate
        mnu_identification
        /*mnu_tb_exconfig*/
    }
}
MENU hdiagnostic_ptb
{
    LABEL "|en|Status/Diagnostics";
    /* STYLE MENU; */
    ITEMS
    {
        grp_blockerror
        mnu_devicestatusfaults
        mnu_sensormeasurements
        mnu_historian
        mnu_trend
    }
}

MENU hprocess_variables_ptb
{
    LABEL "|en|Process Variables";
    /* STYLE MENU; */
    ITEMS
    {
        mnu_ao_control
        mnu_do_control
        mnu_sensor_state
    }
}

/*-------/
** Device
/-------*/
#ifdef DD4
#define STYLE(m)
#else
#define STYLE(m) STYLE m;
#endif

MENU device_root_menu_ptb
{
    LABEL "|en|Device Setup";
    STYLE(MENU)
    ITEMS
    {
        mnu_startup
        mnu_tb_process
        mnu_config
        mnu_calibrate
        mnu_identification
        /*mnu_tb_exconfig*/
    }
}

/*------------/
** Diagnaostic
/------------*/

MENU diagnostic_root_menu_ptb
{
    LABEL "|en|Status/Diagnostics";
    STYLE(MENU)
    ITEMS
    {
        mnu_devicestatusfaults
        mnu_sensormeasurements
        mnu_historian
		mnu_strokevalve
        mnu_trend
#ifndef DD4
		mnu_pst
#endif
    }
}

/*---/
** PV
/---*/

MENU  mnu_block_mode
{
    LABEL "|en|Block Mode";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.MODE_BLK.ACTUAL
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.TARGET
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.PERMITTED
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.NORMAL
    }
}

MENU process_variables_root_menu_ptb
{
    LABEL "|en|Process Variables";
    STYLE(MENU)
    ITEMS
    {
        mnu_ao_control
        mnu_do_control
        mnu_sensor_state
    }
}

#ifdef DD4
MENU mnu_sensor_state
{
    LABEL "|en|Sensors State";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_final_value
        mnu_finalposition_value
        mnu_workingpos_value
        mnu_workingsp_value
			mnu_supply_pressure
			mnu_actuator_a_pressure
			mnu_actuator_b_pressure
			mnu_pilot_pressure
			mnu_atmospheric_pressure
    }
}
#else
MENU mnu_sensor_state
{
    LABEL "|en|Sensors State";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_final_value_trend
        EDD(ROWBREAK)
        mnu_pressure_gauge
		EDD(COLUMNBREAK)
        EDD(COLUMNBREAK)
        mnu_act_press_gauge
		EDD(ROWBREAK)
		PARAM.ANALOG_INPUT.STATUS
		EDD(COLUMNBREAK)
		PARAM.ANALOG_INPUT.VALUE
			EDD(ROWBREAK)
			mnu_pressure
			mnu_temperature_group
			mnu_current_group
    }
}
#endif

MENU mnu_do_discretecontrol
{
    LABEL "|en|Discrete Control";
    STYLE(GROUP)
    ITEMS
    {
		grp_final_value
        EDD(COLUMNBREAK)
		grp_final_value_dint
        EDD(ROWBREAK)
		grp_final_position_value
        EDD(COLUMNBREAK)
		grp_final_position_value_dint
    }
}

MENU grp_final_value
{
	LABEL "|en|Final Value";
	STYLE(GROUP)
	ITEMS
	{

		PARAM.FINAL_VALUE_D.STATUS
		PARAM.FINAL_VALUE_D.VALUE
	}
}
MENU grp_final_value_dint
{
	LABEL "|en|Final Value DINT";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_VALUE_DINT.STATUS
		PARAM.FINAL_VALUE_DINT.VALUE
	}
}
MENU grp_final_position_value
{
	LABEL "|en|Final Position Value";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_POSITION_VALUE_D.STATUS
		PARAM.FINAL_POSITION_VALUE_D.VALUE
	}
}
MENU grp_final_position_value_dint
{
	LABEL "|en|Final Position Value - DINT";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_POSITION_VALUE_DINT.STATUS
		PARAM.FINAL_POSITION_VALUE_DINT.VALUE
	}
}


MENU mnu_di_switches
{
    LABEL "|en|Discrete Input";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.DISCRETE_INPUT.STATUS
        PARAM.DISCRETE_INPUT.VALUE

    }
}

MENU mnu_do1_switches
{
    LABEL "|en|Discrete output 1 State";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.DISCRETE_OUTPUT_1_STATE.STATUS
        PARAM.DISCRETE_OUTPUT_1_STATE.VALUE

    }
}

MENU mnu_do2_switches
{
    LABEL "|en|Discrete output 2 State";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.DISCRETE_OUTPUT_2_STATE.STATUS
        PARAM.DISCRETE_OUTPUT_2_STATE.VALUE

	}
}

MENU mnu_do_switches
{
    LABEL "|en|Switches";
    STYLE(GROUP)
    ITEMS
    {
		mnu_di_switches
        EDD(COLUMNBREAK)
		mnu_do1_switches
        EDD(COLUMNBREAK)
		mnu_do2_switches
    }
}

MENU mnu_do_failedstate
{
    LABEL "|en|Failed State";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FAILED_STATE.FF
        EDD(COLUMNBREAK)
        PARAM.FAILED_STATE.APP
        EDD(COLUMNBREAK)
        PARAM.FAILED_STATE.PROPAGATE_MODE
    }
}

MENU mnu_do_control
{
    LABEL "|en|Discrete Control";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_do_discretecontrol
		EDD(ROWBREAK)
        mnu_do_switches
    }
}

#ifndef DD4
AXIS y_axis_position
{
    LABEL   "Position(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}

AXIS y_axis_final_value
{
    LABEL "|en|Final Value(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}
/***********************************************************************************************************************************/
AXIS y_axis_analog_input
{
    LABEL "|en|Analog Input(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}
/***********************************************************************************************************************************/
AXIS y_axis_final_pos
{
    LABEL "|en|Final Position Value(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}
AXIS y_axis_working_sp
{
    LABEL "|en|Working SP(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}
AXIS y_axis_working_pos
{
    LABEL "|en|Working Position Value(%)";
    MIN_VALUE   PARAM.FINAL_VALUE_RANGE.EU_0;
    MAX_VALUE   PARAM.FINAL_VALUE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1342];
}

AXIS y_axis_pressure
{
    LABEL   "Pressure";
    MIN_VALUE   PARAM.PRESSURE_RANGE.EU_0;
    MAX_VALUE   PARAM.PRESSURE_RANGE.EU_100;
    CONSTANT_UNIT [unit_code_1133];
}
AXIS y_axis_actuator_press
{
	LABEL   "Actuator Pressure";
	MIN_VALUE   -100;
	MAX_VALUE   100;
	CONSTANT_UNIT[unit_code_1133];
}
AXIS y_axis_temperature
{
    LABEL   "Pressure";
    MIN_VALUE   -40;
    MAX_VALUE   100;
    CONSTANT_UNIT [unit_code_1001];
}
#endif

#ifdef DD4
#else
SOURCE src_final_value
{
    LABEL   "|en|Final Value";
    MEMBERS
    {
        SRC_FINAL_VALUE,    PARAM.FINAL_VALUE.VALUE;
    }
    LINE_COLOR 0x1f78b4;
    Y_AXIS y_axis_final_value;
}
#endif

#ifdef DD4
#else
SOURCE src_final_pos_value
{
    LABEL   "|en|Final Pos Value";
    MEMBERS
    {
        SRC_FINAL_POS_VALUE, PARAM.FINAL_POSITION_VALUE.VALUE;
    }
    LINE_COLOR 0x33a02c;
    Y_AXIS y_axis_final_pos;
}
#endif
/********************************************************************************************************************************************/
#ifdef DD4
#else
SOURCE src_analog_input
{
    LABEL   "|en|Analog Input";
    MEMBERS
    {
        SRC_ANALOG_INPUT, PARAM.ANALOG_INPUT.VALUE;
    }
    LINE_COLOR 0x000000;
    Y_AXIS y_axis_analog_input;
}
#endif

/***********************************************************************************************************************************************/
#ifdef DD4
#else
SOURCE src_working_sp
{
    LABEL   "|en|Working SP";
    MEMBERS
    {
        SRC_WORKING_SP,    PARAM.WORKING_SP.VALUE;
    }
    LINE_COLOR 0xe31a1c;
    Y_AXIS y_axis_working_sp;
}
#endif

#ifdef DD4
#else
SOURCE src_working_pos
{
    LABEL   "|en|Working Pos";
    MEMBERS
    {
        SRC_WORKING_POS,    PARAM.WORKING_POS.VALUE;
    }
    LINE_COLOR 0xff7f00;
    Y_AXIS y_axis_working_pos;
}
#endif

#ifdef DD4
#else
SOURCE src_supply_press
{
    LABEL   "|en|Supply_press";
    MEMBERS
    {
        SRC_SUPPLY_PRESS,    PARAM.SUPPLY_PRESSURE.VALUE;
    }
    LINE_COLOR 0x1f78b4;
}
#endif

#ifdef DD4
#else
SOURCE src_actuators_a_press
{
    LABEL   "|en|Act. A Press";
    MEMBERS
    {
        SRC_ACTUATOR_A_PRESS,    PARAM.ACTUATOR_A_PRESSURE.VALUE;
    }
    LINE_COLOR 0x6a3d9a;
	Y_AXIS y_axis_actuator_press;
}

#endif

#ifdef DD4
#else
SOURCE src_actuators_b_press
{
    LABEL   "|en|Act. B Press";
    MEMBERS
    {
        SRC_ACTUATOR_B_PRESS,    PARAM.ACTUATOR_B_PRESSURE.VALUE;
    }
    LINE_COLOR 0x6a3d9a;
}
#endif

#ifndef DD4
CHART mnu_final_value_trend
{
    LABEL       "|en|Working SP/Working Pos";
    CYCLE_TIME  1000*2;
    LENGTH      1000*60*6;
    HEIGHT      LARGE;
    WIDTH       LARGE;
    TYPE        STRIP;
    MEMBERS
    {
        /*STRIP1, src_final_value;
        STRIP2, src_final_pos_value;*/
        STRIP3, src_working_sp;
        STRIP4, src_working_pos;
		STRIP5, src_analog_input;         /*******************************************************************************************************/
    }
}

CHART mnu_pressure_gauge
{
    LABEL       "|en|Supply press";
    CYCLE_TIME  1000*2;
    LENGTH      1000*60*6;
    HEIGHT      SMALL;
    WIDTH       SMALL;
    TYPE        GAUGE;
    MEMBERS
    {
        STRIP1, src_supply_press;
    }
}

CHART mnu_act_press_gauge
{
    LABEL "|en|Actuator a pressure";
    CYCLE_TIME  1000*2;
    LENGTH      1000*60*6;
    HEIGHT      SMALL;
    WIDTH       SMALL;
    TYPE        GAUGE;
    MEMBERS
    {
        STRIP1, src_actuators_a_press;
        STRIP2, src_actuators_b_press;
    }
}
#endif

MENU mnu_final_value
{
    LABEL "|en|Final Value";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FINAL_VALUE.STATUS
        EDD(COLUMNBREAK)
        PARAM.FINAL_VALUE.VALUE
        EDD(ROWBREAK)
    }
}
MENU mnu_finalposition_value
{
    LABEL "|en|Final Position Value";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FINAL_POSITION_VALUE.STATUS
        EDD(COLUMNBREAK)
        PARAM.FINAL_POSITION_VALUE.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_workingsp_value
{
    LABEL "|en|Characterized Setpoint";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.WORKING_SP.STATUS
        EDD(COLUMNBREAK)
        PARAM.WORKING_SP.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_workingpos_value
{
    LABEL "|en|Characterized Position";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.WORKING_POS.STATUS
        EDD(COLUMNBREAK)
        PARAM.WORKING_POS.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_setpoint_value
{
    LABEL "|en|Setpoint";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.SETPOINT.STATUS
        EDD(COLUMNBREAK)
        PARAM.SETPOINT.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_position_value
{
    LABEL "|en|Actual Position";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.ACTUAL_POSITION.STATUS
        EDD(COLUMNBREAK)
        PARAM.ACTUAL_POSITION.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_position_group
{
    LABEL "|en|Position";
    STYLE(GROUP)
    ITEMS
    {
		mnu_final_value
        mnu_finalposition_value
        mnu_workingsp_value
        mnu_workingpos_value
        mnu_setpoint_value
        mnu_position_value
    }
}

MENU mnu_supply_pressure
{
    LABEL "|en|Supply Pressure";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.SUPPLY_PRESSURE.STATUS
        EDD(COLUMNBREAK)
        PARAM.SUPPLY_PRESSURE.VALUE
    }
}

MENU mnu_actuator_a_pressure
{
    LABEL "|en|Actuator A Pressure";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.ACTUATOR_A_PRESSURE.STATUS
			EDD(COLUMNBREAK)
        PARAM.ACTUATOR_A_PRESSURE.VALUE
    }
}

MENU mnu_actuator_b_pressure
{
    LABEL "|en|Actuator B Pressure";
    STYLE(GROUP)
#ifndef DD4
    VALIDITY
        IF( SVI2_DBL_ACT == PARAM.ACTUATOR_3.ACT_STYLE )
        { TRUE; }
        ELSE
        { FALSE; }
#endif
    ITEMS
    {
        PARAM.ACTUATOR_B_PRESSURE.STATUS
        EDD(COLUMNBREAK)
        PARAM.ACTUATOR_B_PRESSURE.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_atmospheric_pressure
{
    LABEL "|en|Atmospheric Pressure";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.ATMOSPHERIC_PRESSURE.STATUS
        EDD(COLUMNBREAK)
        PARAM.ATMOSPHERIC_PRESSURE.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_pilot_pressure
{
    LABEL "|en|Pilot Pressure";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.PILOT_PRESSURE.STATUS
        EDD(COLUMNBREAK)
        PARAM.PILOT_PRESSURE.VALUE
        EDD(ROWBREAK)
    }
}
MENU mnu_current_group
{
    LABEL "|en|I/P";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.IP_DRIVE_CURRENT.STATUS
        EDD(COLUMNBREAK)
        PARAM.IP_DRIVE_CURRENT.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_temperature_group
{
    LABEL "|en|Temperature";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.TEMPERATURE.STATUS
        EDD(COLUMNBREAK)
        PARAM.TEMPERATURE.VALUE
        EDD(ROWBREAK)
    }
}

MENU mnu_ao_control
{
    LABEL "|en|AO Control";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_tbmode_mode
        mnu_position_group
		mnu_supply_pressure
		mnu_actuator_a_pressure
		mnu_actuator_b_pressure
		mnu_pilot_pressure
		mnu_atmospheric_pressure
        mnu_current_group
        mnu_temperature_group
    }
}

MENU mnu_calibrate
{
    LABEL "|en|Calibration";
    STYLE(WINDOW)
    ITEMS
    {
		mnu_data_collection
    }
}

MENU mnu_identification
{
    LABEL "|en|Identification";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_actuator
        mnu_valve_info
        mnu_valve_body
		mnu_advanced_valve_configuration
    }
}

MENU mnu_cal_positions
{
    LABEL "|en|Valve Position";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.SUPPLY_PRESSURE.STATUS
        PARAM.SUPPLY_PRESSURE.VALUE
        EDD(COLUMNBREAK)
        PARAM.ACTUATOR_A_PRESSURE.STATUS
        PARAM.ACTUATOR_A_PRESSURE.VALUE
        EDD(COLUMNBREAK)
        PARAM.ACTUATOR_B_PRESSURE.STATUS
        PARAM.ACTUATOR_B_PRESSURE.VALUE
        EDD(ROWBREAK)
        PARAM.RAW_POSITION
        PARAM.OPEN_STOP_ADJUSTMENT
        EDD(COLUMNBREAK)
        PARAM.ACTUAL_POSITION.STATUS
        PARAM.ACTUAL_POSITION.VALUE
        EDD(COLUMNBREAK)
		WHOLE_PARAM__TRAVEL
    }
}

MENU mnu_strokevalve
{
    LABEL "|en|Valve Travel";
    STYLE(PAGE)
    ITEMS
    {
        mnu_cal_positions
        EDD(ROWBREAK)
		mnu_check_procss
    }
}

MENU mnu_check_procss
{
    LABEL "|en|Check Process";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.CHECK_PROCESS.PROCESS_ID
        PARAM.CHECK_PROCESS.PERCENT_COMPLETE
    }
}

MENU mnu_mode_row
{
    LABEL "|en|RB Block Mode";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.MODE_BLK.TARGET
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.ACTUAL
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.PERMITTED
		EDD(COLUMNBREAK)
		PARAM.MODE_BLK.NORMAL
    }
}

MENU  mnu_tbmode_mode
{
    LABEL "|en|Block Mode";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.MODE_BLK.TARGET
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.ACTUAL
        EDD(ROWBREAK)
    }
}

MENU mnu_tuningdata
{
    LABEL "|en|Position control settings";
	STYLE(GROUP)
    ITEMS
    {
        PARAM.ACTIVATE_CONTROL_SET
        EDD(ROWBREAK)
			grp_active_control_set
        EDD(COLUMNBREAK)
        PARAM.CUSTOM_CONTROL_SET.P
        PARAM.CUSTOM_CONTROL_SET.I
        PARAM.CUSTOM_CONTROL_SET.D
        PARAM.CUSTOM_CONTROL_SET.PADJ
        PARAM.CUSTOM_CONTROL_SET.BETA
        PARAM.CUSTOM_CONTROL_SET.POSCOMP
        PARAM.CUSTOM_CONTROL_SET.DEADZONE
        PARAM.CUSTOM_CONTROL_SET.NONLIN
    }
}
MENU mnu_characterization
{
    LABEL "|en|Characterization";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.CHAR_SELECTION.TYPE_1 /*_svi2*/
        EDD(COLUMNBREAK)
        PARAM.CHAR_SELECTION.NUMBER_OF_POINTS_1 /*_svi2*/
        EDD(COLUMNBREAK)
        /*mnu_characterPoints*/
    }
}

/**
MENU mnu_characterization_page
{
    LABEL "|en|Characterization";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.CHAR_SELECTION.TYPE_1 //_svi2
        EDD(COLUMNBREAK)
        PARAM.CHAR_SELECTION.NUMBER_OF_POINTS_1 //_svi2
        EDD(COLUMNBREAK)
        mnu_characterPoints
    }
}

MENU mnu_characterPoints
{
    LABEL "|en|Characterization Points";
    STYLE(GROUP)
    ITEMS
    {
        mnu_custom_char_points
        EDD(ROWBREAK)
        mnu_current_char_points

        PARAM.CUSTOM_CHAR_POINTS
        EDD(ROWBREAK)
        PARAM.CURRENT_CHAR_POINTS
    }
}
**/
MENU mnu_travelrange
{
    LABEL "|en|Travel";
    STYLE(GROUP)
    ITEMS
    {
		WHOLE_PARAM__TRAVEL
        EDD(COLUMNBREAK)
        PARAM.OPEN_STOP_ADJUSTMENT
    }
}

MENU mnu_startup
{
    LABEL "|en|Startup";
	STYLE(PAGE) /*ADDED style*/
    ITEMS
    {
		ptb_character.BLOCK_TAG
		EDD(ROWBREAK)
		mnu_tbmode_mode
			EDD(ROWBREAK)
		PARAM.ACTUATOR_3.ACT_FAIL_ACTION_1
		EDD(COLUMNBREAK)
        PARAM.ACTUATOR_3.ACT_STYLE
		EDD(COLUMNBREAK)
		PARAM.ACCESSORY.REMOTE_SENSOR
		/*METHODs*/
		EDD(ROWBREAK)
        do_find_stops
        EDD(COLUMNBREAK)
        do_manual_hi_low_stops
        EDD(COLUMNBREAK)
        do_autotune
		EDD(ROWBREAK)
        mnu_travelrange
		EDD(ROWBREAK)
        mnu_tuningdata
		EDD(ROWBREAK)
        mnu_characterization
    }
}

MENU grp_tb_updateevent
{
    LABEL "|en|Update Event";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.UPDATE_EVT.UNACKNOWLEDGED
        PARAM.UPDATE_EVT.UPDATE_STATE
        PARAM.UPDATE_EVT.TIME_STAMP
        PARAM.UPDATE_EVT.STATIC_REVISION
        PARAM.UPDATE_EVT.RELATIVE_INDEX
    }
}

MENU grp_tb_blockalarm
{
    LABEL "|en|Block Alarm";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.BLOCK_ALM.UNACKNOWLEDGED
        PARAM.BLOCK_ALM.ALARM_STATE
        PARAM.BLOCK_ALM.TIME_STAMP
        PARAM.BLOCK_ALM.SUB_CODE
        PARAM.BLOCK_ALM.VALUE
    }
}

MENU mnu_tb_process
{
    LABEL "|en|Application";
	STYLE(PAGE) /*ADDED style*/
    ITEMS
    {
		ptb_character.BLOCK_TAG
        mnu_block_mode
        PARAM.TAG_DESC
			EDD(COLUMNBREAK)
        PARAM.STRATEGY
			EDD(COLUMNBREAK)
        PARAM.ALERT_KEY
			EDD(ROWBREAK)
        grp_tb_updateevent
		EDD(COLUMNBREAK)
        grp_tb_blockalarm
        PARAM.TRANSDUCER_DIRECTORY
		 }
}

MENU grp_blockerror
{
    LABEL "|en|Block Error";
    STYLE(PAGE)
    ITEMS
    {
		PARAM.XD_ERROR_POS
			EDD(COLUMNBREAK)
		PARAM.XD_ERROR_PRESSURE
			EDD(COLUMNBREAK)
		PARAM.XD_ERROR_TEMPERATURE
			EDD(ROWBREAK)
        PARAM.BLOCK_ERR
		EDD(COLUMNBREAK)
		PARAM.BLOCK_ERR_DESC_1
    }
}
MENU mnu_devicestatusfaults
{
    LABEL "|en|Status/Faults";
    STYLE(WINDOW)
    ITEMS
    {
		PARAM.APP_MODE
		EDD(ROWBREAK)
		clear_current_fault
			EDD(COLUMNBREAK)
		clear_all_fault
			EDD(COLUMNBREAK)
		change_app_mode
		EDD(ROWBREAK)
		mnu_currentfaultlist
        EDD(COLUMNBREAK)
        mnu_historyfaultlist
    }
}

MENU mnu_currentfaultlist
{
    LABEL "|en|Current Faults";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_0_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_1_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_2_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_3_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_4_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_5_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_7_C
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_8_C
    }
}

MENU mnu_historyfaultlist
{
    LABEL "|en|History Faults";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_0_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_1_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_2_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_3_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_4_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_5_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_7_H
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_8_H
    }
}

MENU mnu_positionhistogram
{
    LABEL "|en|Position Histogram";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.POSITION_HISTOGRAM.TOTAL_TIME
        PARAM.POSITION_HISTOGRAM.POS_5_PERCENT_CLOSED
        PARAM.POSITION_HISTOGRAM.POS_10_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_20_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_30_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_40_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_50_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_60_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_70_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_80_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_90_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_95_PERCENT
        PARAM.POSITION_HISTOGRAM.POS_95_PERCENT_OPEN
    }
}

MENU mnu_positionErrorhistogram
{
    LABEL "|en|Position Error Histogram";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.POSITION_ERROR_HISTOGRAM.POS_5_PERCENT_CLOSED
        PARAM.POSITION_ERROR_HISTOGRAM.POS_10_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_20_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_30_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_40_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_50_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_60_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_70_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_80_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_90_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_95_PERCENT
        PARAM.POSITION_ERROR_HISTOGRAM.POS_95_PERCENT_OPEN
    }
}

MENU mnu_nearclosedalert
{
    LABEL "|en|Near Closed Alert";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__NEAR_CLOSED_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.NEAR_CLOSE_ALERT_ST
#endif
    }
}

MENU mnu_positionerrortrend
{
    LABEL "|en|Position Error Trend";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.POSITION_ERROR_TREND.CURRENTLY_COLLECTED
        PARAM.POSITION_ERROR_TREND.TODAY
        PARAM.POSITION_ERROR_TREND.LAST_DAY
        PARAM.POSITION_ERROR_TREND.PREVIOUS_DAY
        PARAM.POSITION_ERROR_TREND.THREE_DAYS_AGO
        PARAM.POSITION_ERROR_TREND.CURRENT_WEEK
        PARAM.POSITION_ERROR_TREND.LAST_WEEK
        PARAM.POSITION_ERROR_TREND.PREVIOUS_WEEK
        PARAM.POSITION_ERROR_TREND.THREE_WEEKS_AGO
        PARAM.POSITION_ERROR_TREND.CURRENT_MONTH
        PARAM.POSITION_ERROR_TREND.LAST_MONTH
        PARAM.POSITION_ERROR_TREND.PREVIOUS_MONTH
        PARAM.POSITION_ERROR_TREND.THREE_MONTHS_AGO
        PARAM.POSITION_ERROR_TREND.CURRENT_12_MONTHS
        PARAM.POSITION_ERROR_TREND.LAST_12_MONTHS
        PARAM.POSITION_ERROR_TREND.PREVIOUS_12_MONTHS
        PARAM.POSITION_ERROR_TREND.THREE_YEARS_AGO
    }
}

MENU mnu_historian_position
{
    LABEL "|en|Position Histogram";
    STYLE(PAGE)
    ITEMS
    {
        mnu_positionhistogram
        EDD(COLUMNBREAK)
        mnu_positionErrorhistogram
        EDD(COLUMNBREAK)
        mnu_nearclosedalert
        EDD(COLUMNBREAK)
        mnu_positionerrortrend
    }
}

MENU mnu_travelalertA
{
    LABEL "|en|Travel Alert A";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__TRAVEL_ACCUMULATION_A_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.TRAVEL_ACCUMULATION_A_ALERT_ST
#endif
    }
}

MENU mnu_travelalertB
{
    LABEL "|en|Travel Alert B";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__TRAVEL_ACCUMULATION_B_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.TRAVEL_ACCUMULATION_B_ALERT_ST
#endif
    }
}

MENU mnu_travel_accumulation
{
    LABEL "|en|Travel Accumulation";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.TRAVEL_ACCUMULATION_TREND.CURRENTLY_COLLECTED
        PARAM.TRAVEL_ACCUMULATION_TREND.TODAY
        PARAM.TRAVEL_ACCUMULATION_TREND.LAST_DAY
        PARAM.TRAVEL_ACCUMULATION_TREND.PREVIOUS_DAY
        PARAM.TRAVEL_ACCUMULATION_TREND.THREE_DAYS_AGO
        PARAM.TRAVEL_ACCUMULATION_TREND.CURRENT_WEEK
        PARAM.TRAVEL_ACCUMULATION_TREND.LAST_WEEK
        PARAM.TRAVEL_ACCUMULATION_TREND.PREVIOUS_WEEK
        PARAM.TRAVEL_ACCUMULATION_TREND.THREE_WEEKS_AGO
        PARAM.TRAVEL_ACCUMULATION_TREND.CURRENT_MONTH
        PARAM.TRAVEL_ACCUMULATION_TREND.LAST_MONTH
        PARAM.TRAVEL_ACCUMULATION_TREND.PREVIOUS_MONTH
        PARAM.TRAVEL_ACCUMULATION_TREND.THREE_MONTHS_AGO
        PARAM.TRAVEL_ACCUMULATION_TREND.CURRENT_12_MONTHS
        PARAM.TRAVEL_ACCUMULATION_TREND.LAST_12_MONTHS
        PARAM.TRAVEL_ACCUMULATION_TREND.PREVIOUS_12_MONTHS
        PARAM.TRAVEL_ACCUMULATION_TREND.THREE_YEARS_AGO
    }
}

MENU mnu_cyclealertA
{
    LABEL "|en|Counter Alert A";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__CYCLE_COUNTER_A_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.CYCLE_COUNTER_A_ALERT_ST
#endif
    }
}

MENU mnu_cyclealertB
{
    LABEL "|en|Counter Alert B";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__CYCLE_COUNTER_B_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.CYCLE_COUNTER_B_ALERT_ST
#endif
    }
}

MENU mnu_cycle_counter
{
    LABEL "|en|Cycle Counter";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.CYCLE_COUNTER_TREND.CURRENTLY_COLLECTED
        PARAM.CYCLE_COUNTER_TREND.TODAY
        PARAM.CYCLE_COUNTER_TREND.LAST_DAY
        PARAM.CYCLE_COUNTER_TREND.PREVIOUS_DAY
        PARAM.CYCLE_COUNTER_TREND.THREE_DAYS_AGO
        PARAM.CYCLE_COUNTER_TREND.CURRENT_WEEK
        PARAM.CYCLE_COUNTER_TREND.LAST_WEEK
        PARAM.CYCLE_COUNTER_TREND.PREVIOUS_WEEK
        PARAM.CYCLE_COUNTER_TREND.THREE_WEEKS_AGO
        PARAM.CYCLE_COUNTER_TREND.CURRENT_MONTH
        PARAM.CYCLE_COUNTER_TREND.LAST_MONTH
        PARAM.CYCLE_COUNTER_TREND.PREVIOUS_MONTH
        PARAM.CYCLE_COUNTER_TREND.THREE_MONTHS_AGO
        PARAM.CYCLE_COUNTER_TREND.CURRENT_12_MONTHS
        PARAM.CYCLE_COUNTER_TREND.LAST_12_MONTHS
        PARAM.CYCLE_COUNTER_TREND.PREVIOUS_12_MONTHS
        PARAM.CYCLE_COUNTER_TREND.THREE_YEARS_AGO
    }
}

MENU mnu_historian
{
    LABEL "|en|Position Histogram";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_historian_position
    }
}

MENU mnu_trend
{
    LABEL "|en|Trend";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_travel_accumulation
		EDD(COLUMNBREAK)
        mnu_cycle_counter
    }
}
MENU grp_OnOff_SP_from_DO_Block
{
	LABEL "|en| On/Off SP from DO Block ";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_VALUE_D.STATUS
		EDD(COLUMNBREAK)
		PARAM.FINAL_VALUE_D.VALUE
	}
}
MENU grp_discrete_SP_from_Block
{
	LABEL "|en| Discrete SP from DO Block";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_VALUE_DINT.STATUS
			EDD(COLUMNBREAK)
		PARAM.FINAL_VALUE_DINT.VALUE
	}
}

/*MENU grp_hardwarealert
{
	LABEL "|en|Hardware Alert";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.ALERT_STATE.SENSOR_FAILURE_ALERT_ST
		PARAM.ALERT_STATE.PROCESSOR_ALERT_ST
		PARAM.ALERT_STATE.VALVE_CONTROL_ALERT_ST
		PARAM.ALERT_STATE.COMMISSIONING_ALERT_ST
		PARAM.ALERT_STATE.AIR_SUPPLY_ALERT_ST
		PARAM.ALERT_STATE.SUPPORTING_HARDWARE_ALERT_ST

		PARAM.ALERT_COUNTERS.SENSOR_FAILURE_ALERT_CNT
		PARAM.ALERT_COUNTERS.PROCESSOR_ALERT_CNT
		PARAM.ALERT_COUNTERS.VALVE_CONTROL_ALERT_CNT
		PARAM.ALERT_COUNTERS.COMMISSIONING_ALERT_CNT
		PARAM.ALERT_COUNTERS.AIR_SUPPLY_ALERT_CNT
		PARAM.ALERT_COUNTERS.SUPPORTING_HARDWARE_ALERT_CNT
	}
}*/

MENU grp_pressurealert
{
    LABEL "|en|Pressure Alert";
    STYLE(GROUP)
    ITEMS
    {
		mnu_pilot_pressure
		mnu_atmospheric_pressure
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_LOLO_ALERT_ST
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_LO_ALERT_ST
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_HI_ALERT_ST
			EDD(COLUMNBREAK)
        PARAM.ALERT_COUNTERS.SUPPLY_PRESSURE_LOLO_ALERT_CNT
        PARAM.ALERT_COUNTERS.SUPPLY_PRESSURE_LO_ALERT_CNT
		PARAM.ALERT_COUNTERS.SUPPLY_PRESSURE_HI_ALERT_CNT
    }
}
MENU grp_temperaturealert
{
	LABEL "|en|Temperature Alert";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.ALERT_COUNTERS.TEMPERATURE_LO_ALERT_CNT
		PARAM.ALERT_COUNTERS.TEMPERATURE_HI_ALERT_CNT
		EDD(COLUMNBREAK)
		PARAM.ALERT_STATE.TEMPERATURE_LO_ALERT_ST
		PARAM.ALERT_STATE.TEMPERATURE_HI_ALERT_ST
	}
}

MENU grp_alertlog
{
    LABEL "|en|Alert log";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.ALERT_LOG.ALERT_COMMAND
        PARAM.ALERT_LOG.ALERT_TIME
        PARAM.ALERT_LOG.ALERT_DATA
	}
}
MENU mnu_position
{
	LABEL "|en|Position";
	STYLE(GROUP)
	ITEMS
	{
		mnu_finalposition_value
		mnu_final_value
		grp_OnOff_SP_from_DO_Block
		grp_discrete_SP_from_Block
		mnu_workingsp_value
		mnu_workingpos_value
	}
}
MENU mnu_pressure
{
	LABEL "|en|Pressure";
	STYLE(GROUP)
	ITEMS
	{
		mnu_supply_pressure
		mnu_actuator_a_pressure
		mnu_actuator_b_pressure
	}
}
MENU mnu_mode_blk_grp
{
	LABEL "|en| Mode Block";
	STYLE(GROUP)
	ITEMS {
		block_mode_auto
		EDD(COLUMNBREAK)
		block_mode_manual
			EDD(COLUMNBREAK)
		block_mode_outOfService

	}
}
MENU mnu_current_mode
{
	LABEL "|en|Current Mode";
	STYLE(GROUP)
	ITEMS {
		PARAM.MODE_BLK.ACTUAL
		mnu_mode_blk_grp
	}
}

MENU mnu_sensormeasurements
{
	LABEL "|en|Device State";
	STYLE(WINDOW)
	ITEMS
	{
		grp_blockerror
		mnu_failed_state
		page_pos_alerts
		mnu_fDiagactive
	}
}
MENU mnu_failed_state
{
	LABEL "|en|Failed State";
	STYLE(PAGE)
	ITEMS
	{
		mnu_do_failedstate
		EDD(ROWBREAK)
		mnu_fstate_status
	}
}
/*MENU mnu_pos_state
{
	LABEL "|en|Positioner State";
	STYLE(PAGE)
	ITEMS
	{
		mnu_position
		mnu_pressure
		mnu_temperature_group
		mnu_current_group
		EDD(COLUMNBREAK)
		EDD(COLUMNBREAK)
		grp_pressurealert
		grp_temperaturealert
		grp_alertaction
	}
}*/

MENU page_pos_alerts
{
	LABEL "|en|Position Alerts";
	STYLE(PAGE)
	ITEMS
	{

		#if 0
				img_dev_alert
		#endif
				pic_dev_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.DEVIATION_ALERT_CNT
				EDD(ROWBREAK)
				pic_poshihi_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.POSITION_HIHI_ALERT_CNT
				EDD(ROWBREAK)
				pic_poshi_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.POSITION_HI_ALERT_CNT
				EDD(ROWBREAK)
				pic_poslo_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.POSITION_LO_ALERT_CNT
				EDD(ROWBREAK)
				pic_poslolo_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.POSITION_LOLO_ALERT_CNT
				EDD(ROWBREAK)
				pic_setpoint_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.SETPOINT_TIMEOUT_ALERT_CNT
				EDD(ROWBREAK)
				pic_nearclose_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.NEAR_CLOSE_ALERT_CNT
				EDD(ROWBREAK)
				pic_travelA_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.TRAVEL_ACCUMULATION_A_ALERT_CNT
				EDD(ROWBREAK)
				pic_travelB_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.TRAVEL_ACCUMULATION_B_ALERT_CNT
				EDD(ROWBREAK)
				pic_cycleA_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.CYCLE_COUNTER_A_ALERT_CNT
				EDD(ROWBREAK)
				pic_cycleB_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.CYCLE_COUNTER_B_ALERT_CNT
				EDD(ROWBREAK)
				pic_wroktime_alert
				EDD(COLUMNBREAK)
				PARAM.ALERT_COUNTERS.WORKING_TIME_ALERT_CNT

		}
}
MENU grp_diagnostic_config
{
	LABEL "|en|Diagnostic Configuration";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.DIAGNOSTIC_CONFIGURATION.START_POSITION
        PARAM.DIAGNOSTIC_CONFIGURATION.END_POSITION
        PARAM.DIAGNOSTIC_CONFIGURATION.SET_POINT_RATE
        PARAM.DIAGNOSTIC_CONFIGURATION.SAMPLING_TIME
        PARAM.DIAGNOSTIC_CONFIGURATION.DIRECTION
        PARAM.DIAGNOSTIC_CONFIGURATION.OPTION
	}
}

MENU mnu_pidinfo
{
    LABEL "|en|Valve Tuning Data";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.ACTIVATE_CONTROL_SET
        EDD(ROWBREAK)
			mnu_active_control
        EDD(COLUMNBREAK)
        PARAM.CUSTOM_CONTROL_SET.P
        PARAM.CUSTOM_CONTROL_SET.I
        PARAM.CUSTOM_CONTROL_SET.D
        PARAM.CUSTOM_CONTROL_SET.PADJ
        PARAM.CUSTOM_CONTROL_SET.BETA
        PARAM.CUSTOM_CONTROL_SET.POSCOMP
        PARAM.CUSTOM_CONTROL_SET.DEADZONE
        PARAM.CUSTOM_CONTROL_SET.NONLIN
    }
}
MENU mnu_active_control
{
	LABEL "|en| Activate Control Set";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.ACTIVE_CONTROL_SET.SELECTOR
        PARAM.ACTIVE_CONTROL_SET.P
        PARAM.ACTIVE_CONTROL_SET.I
        PARAM.ACTIVE_CONTROL_SET.D
        PARAM.ACTIVE_CONTROL_SET.PADJ
        PARAM.ACTIVE_CONTROL_SET.BETA
        PARAM.ACTIVE_CONTROL_SET.POSCOMP
        PARAM.ACTIVE_CONTROL_SET.DEADZONE
        PARAM.ACTIVE_CONTROL_SET.NONLIN
}
}
MENU mnu_position_lo_alert
{
	LABEL "|en|Position LO ALert";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__POSITION_LO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.POSITION_LO_ALERT_ST
#endif
	}
}
MENU mnu_position_hi_alert
{
	LABEL "|en|Position HI ALert";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__POSITION_HI_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.POSITION_HI_ALERT_ST
#endif
	}
}
MENU mnu_position_lolo_alert
{
    LABEL "|en|Position LOLO Alert";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__POSITION_LOLO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.POSITION_LOLO_ALERT_ST
#endif
	}
}
MENU mnu_position_hihi_alert
{
	LABEL "|en|Position HIHI Alert";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__POSITION_HIHI_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.POSITION_HIHI_ALERT_ST
#endif
	}
}
MENU mnu_supply_pressure_hilo_alert
{
    LABEL "|en|Supply Pressure Alerts";
	STYLE(GROUP)
    ITEMS
    {
		PARAM.SUPPLY_PRESSURE.VALUE
			EDD(ROWBREAK)
		PARAM.ALERT_ACTION.SUPPLY_PRESSURE_LOLO_ALERT_ACT
		mnu_supply_pressure_lolo_alert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.SUPPLY_PRESSURE_LO_ALERT_ACT
		mnu_supply_pressure_lo_alert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.SUPPLY_PRESSURE_HI_ALERT_ACT
		mnu_supply_pressure_hi_alert
    }
}
MENU mnu_supply_pressure_lolo_alert
{
	LABEL "|en|Supply pressure LOLO alerts";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__SUPPLY_PRESSURE_LOLO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_LOLO_ALERT_ST
#endif
	}
}MENU mnu_supply_pressure_lo_alert
{
	LABEL "|en|Supply pressure LO alerts";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__SUPPLY_PRESSURE_LO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_LO_ALERT_ST
#endif
	}
}
MENU mnu_supply_pressure_hi_alert
{
	LABEL "|en|Supply pressure HI alerts";
	STYLE(GROUP)
	ITEMS
	{
        WHOLE_PARAM__SUPPLY_PRESSURE_HI_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.SUPPLY_PRESSURE_HI_ALERT_ST
#endif
	}
}
MENU mnu_temperature_alerts
{
    LABEL "|en|Temperature LO - HI Alerts";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.TEMPERATURE.VALUE
        EDD(ROWBREAK)
        WHOLE_PARAM__TEMPERATURE_LO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.TEMPERATURE_LO_ALERT_ST
#endif
        EDD(COLUMNBREAK)
        WHOLE_PARAM__TEMPERATURE_HI_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.TEMPERATURE_HI_ALERT_ST
#endif
    }
}

MENU mnu_ip_current_alert
{
    LABEL "|en|IP Current Alerts";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.IP_DRIVE_CURRENT.VALUE
		EDD(ROWBREAK)
        mnu_ip_current_alert_lo
        EDD(COLUMNBREAK)
        mnu_ip_current_alert_hi
    }
}

MENU mnu_ip_current_alert_lo
{
    LABEL "|en|Ip Driver Current Lo Alert";
	STYLE(GROUP)
    ITEMS
    {
		WHOLE_PARAM__IP_DRIVE_CURRENT_LO_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.IP_DRIVE_CURRENT_ALERT_LO_ST
#endif
    }
}

MENU mnu_ip_current_alert_hi
{
    LABEL "|en|Ip Driver Current Hi Alert";
	STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__IP_DRIVE_CURRENT_HI_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.IP_DRIVE_CURRENT_ALERT_HI_ST
#endif
    }
}


MENU mnu_discrete_switch_configure
{
    LABEL "|en|Discrete Switch";
    STYLE(GROUP)
    ITEMS
    {
		grp_discrete_switch_1
        EDD(COLUMNBREAK)
		grp_discrete_switch_2
    }
}
MENU grp_discrete_switch_1
{
	LABEL "|en|Discrete Switch Configuration 1";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.DISCRETE_SWITCH_1_CONF.DIRECTION
		PARAM.DISCRETE_SWITCH_1_CONF.FUNCTION
	}
}
MENU grp_discrete_switch_2
{
	LABEL "|en|Discrete Switch Configuration 2";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.DISCRETE_SWITCH_2_CONF.DIRECTION
		PARAM.DISCRETE_SWITCH_2_CONF.FUNCTION
	}
}
MENU mnu_config_position
{
    LABEL "|en|Position";
    STYLE(WINDOW)
    ITEMS
    {
        mnu_position_configuration
        mnu_positionlimits
        mnu_positioncontrol
        mnu_positionalerts
    }
}

MENU mnu_position_configuration
{
    LABEL "|en|Primary";
    STYLE(PAGE)
    ITEMS
    {
		mnu_finalposition_value
        grp_failedstate
        EDD(ROWBREAK)
        grp_setpointsource
		EDD(ROWBREAK)
		mnu_discrete_switch_configure
    }
}

MENU mnu_positionlimits
{
    LABEL "|en|Limits";
    STYLE(PAGE)
    ITEMS
    {

		PARAM.POSITION_LIMITS.LIMITS_PROTECTED
		EDD(ROWBREAK)
        grp_positionlimits_HI
		EDD(ROWBREAK)
		grp_positionlimits_LO
		EDD(ROWBREAK)
		grp_positionlimits
    }
}

MENU mnu_positioncontrol
{
    LABEL "|en|Control Set";
    STYLE(PAGE)
    ITEMS
    {
		PARAM.ACTIVATE_CONTROL_SET
		EDD(ROWBREAK)
		grp_active_control_set
		EDD(COLUMNBREAK)
        grp_customcontrolset
		EDD(COLUMNBREAK)
		grp_backup_control_set

    }
}
MENU grp_active_control_set
{
	LABEL "|en|Current Settings";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.ACTIVE_CONTROL_SET.SELECTOR
		PARAM.ACTIVE_CONTROL_SET.P
        PARAM.ACTIVE_CONTROL_SET.I
        PARAM.ACTIVE_CONTROL_SET.D
        PARAM.ACTIVE_CONTROL_SET.PADJ
        PARAM.ACTIVE_CONTROL_SET.BETA
        PARAM.ACTIVE_CONTROL_SET.POSCOMP
        PARAM.ACTIVE_CONTROL_SET.DEADZONE
        PARAM.ACTIVE_CONTROL_SET.NONLIN
	}
}
MENU grp_backup_control_set
{
	LABEL "|en|Backup Control Set";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.BACKUP_CONTROL_SET.SELECTOR
		PARAM.BACKUP_CONTROL_SET.P
		PARAM.BACKUP_CONTROL_SET.I
		PARAM.BACKUP_CONTROL_SET.D
		PARAM.BACKUP_CONTROL_SET.PADJ
		PARAM.BACKUP_CONTROL_SET.BETA
		PARAM.BACKUP_CONTROL_SET.POSCOMP
		PARAM.BACKUP_CONTROL_SET.DEADZONE
		PARAM.BACKUP_CONTROL_SET.NONLIN
	}
}
MENU mnu_positionalerts
{
    LABEL "|en|Alerts";
    STYLE(PAGE)
    ITEMS
    {
		PARAM.WORKING_POS.VALUE
			EDD(ROWBREAK)
		PARAM.ALERT_ACTION.POSITION_LOLO_ALERT_ACT
		mnu_position_lolo_alert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.POSITION_LO_ALERT_ACT
		mnu_position_lo_alert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.POSITION_HI_ALERT_ACT
        mnu_position_hi_alert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.POSITION_HIHI_ALERT_ACT
        mnu_position_hihi_alert
			EDD(ROWBREAK)
		PARAM.ALERT_ACTION.DEVIATION_ALERT_ACT
	    grp_deviationalert
			EDD(COLUMNBREAK)
        PARAM.ALERT_ACTION.NEAR_CLOSE_ALERT_ACT
		mnu_nearclosedalert
			EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.SETPOINT_TIMEOUT_ALERT_ACT
		grp_setpointtimealert
			EDD(COLUMNBREAK)
		grp_position_extremes
    }
}

MENU mnu_travelalerts
{
    LABEL "|en|Travel Alarms";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.ALERT_ACTION.TRAVEL_ACCUMULATION_A_ALERT_ACT
		mnu_travelalertA
        EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.TRAVEL_ACCUMULATION_B_ALERT_ACT
        mnu_travelalertB
        EDD(ROWBREAK)
		PARAM.ALERT_ACTION.CYCLE_COUNTER_A_ALERT_ACT
        mnu_cyclealertA
        EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.CYCLE_COUNTER_B_ALERT_ACT
        mnu_cyclealertB
    }
}

MENU grp_deviationalert
{
    LABEL "|en|Deviation Alert";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__DEVIATION_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.DEVIATION_ALERT_ST
#endif
    }
}

MENU grp_setpointtimealert
{
    LABEL "|en|Setpoint Timeout Alert";
    STYLE(GROUP)
    ITEMS
    {
        WHOLE_PARAM__SETPOINT_TIMEOUT_ALERT
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_EXCLUDE)
		PARAM.ALERT_STATE.SETPOINT_TIMEOUT_ALERT_ST
#endif
    }
}

MENU grp_customcontrolset
{
    LABEL "|en|Custom Control Set";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.CUSTOM_CONTROL_SET.P
        PARAM.CUSTOM_CONTROL_SET.I
        PARAM.CUSTOM_CONTROL_SET.D
        PARAM.CUSTOM_CONTROL_SET.PADJ
        PARAM.CUSTOM_CONTROL_SET.BETA
        PARAM.CUSTOM_CONTROL_SET.POSCOMP
        PARAM.CUSTOM_CONTROL_SET.DEADZONE
        PARAM.CUSTOM_CONTROL_SET.NONLIN
    }
}
MENU grp_positionlimits
{
    LABEL "|en|Setpoint Rate Limits";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.POSITION_LIMITS.LIMIT_RATE
		PARAM.POSITION_LIMITS.ENABLE_RATE_HI
        PARAM.POSITION_LIMITS.ENABLE_RATE_LO
    }
}
MENU grp_limits_LO
{
	LABEL "|en|Limit";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.POSITION_LIMITS.ENABLE_LO
		EDD(COLUMNBREAK)
		PARAM.POSITION_LIMITS.LIMIT_LO
	}
}
MENU grp_positionlimits_LO
{
	LABEL "|en|LOW Position - Either Range OR Cut-Off may be enabled";
	STYLE(GROUP)
	ITEMS
	{
		grp_limits_LO
		EDD(ROWBREAK)
		grp_positioncutoff_lo
	}
}
MENU grp_limits_HI
{
	LABEL "|en|Limit";
	STYLE(GROUP)
	ITEMS
	{
	PARAM.POSITION_LIMITS.ENABLE_HI
	EDD(COLUMNBREAK)
	PARAM.POSITION_LIMITS.LIMIT_HI
	}
}
MENU grp_positionlimits_HI
{
	LABEL "|en|HIGH Position-Either Range OR Cut-Off may be enabled";
	STYLE(GROUP)
	ITEMS
	{
		grp_limits_HI
		EDD(ROWBREAK)
		grp_positioncutoff_hi
	}
}
MENU grp_positioncutoff_hi
{
    LABEL "|en|Cut-Off";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FINAL_VALUE_CUTOFF_HI.ENABLE
		EDD(COLUMNBREAK)
        PARAM.FINAL_VALUE_CUTOFF_HI.CUTOFF_POINT_HI
    }
}

MENU grp_positioncutoff_lo
{
	LABEL "|en|Cut-Off ";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FINAL_VALUE_CUTOFF_LO.ENABLE
		EDD(COLUMNBREAK)
		PARAM.FINAL_VALUE_CUTOFF_LO.CUTOFF_POINT_LO
	}
}

MENU grp_failedstate
{
    LABEL "|en|Fault State";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.XD_FSTATE.CONFIGURATION
        PARAM.XD_FSTATE.XD_FSTATE_OPT_1 /*XD Fault State Option*/
        EDD(COLUMNBREAK)
        PARAM.XD_FSTATE.FSTATE_VALUE_1   /*FSTATE Value*/
        PARAM.XD_FSTATE.FSTATE_TIME_1    /*FSTATE Time*/
    }
}
MENU mnu_fstate_status
{
	LABEL "|en| TB FSTATE Status";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.TB_FSTATE_STATUS.DO_USR_REQ
		PARAM.TB_FSTATE_STATUS.FINAL_VALUE_REQ
		PARAM.TB_FSTATE_STATUS.TIME_TO_FSTATE
	}
}
/************************************************************************************************************************************************/
MENU grp_setpointsource
{
    LABEL "|en|Setpoint Source";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.SETPOINT_SOURCE
        EDD(COLUMNBREAK)
        PARAM.READBACK_SELECT
        EDD(ROWBREAK)
    }
}

MENU mnu_config_pressure
{
    LABEL "|en|Pressure";
    STYLE(WINDOW)
    ITEMS
    {
		mnu_supply_pressure
			mnu_actuator_a_pressure
			mnu_actuator_b_pressure
			mnu_pilot_pressure
			mnu_atmospheric_pressure
        grp_pressurerange
			EDD(ROWBREAK)
        mnu_supply_pressure_hilo_alert
			grp_pressure_extremes
    }
}

MENU grp_pressurerange
{
    LABEL "|en|Pressure Range";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.PRESSURE_RANGE.EU_0
        PARAM.PRESSURE_RANGE.EU_100
        EDD(COLUMNBREAK)
        PARAM.PRESSURE_RANGE.UNITS_INDEX
        PARAM.PRESSURE_RANGE.DECIMAL
        EDD(ROWBREAK)
    }
}

MENU mnu_config_temperature
{
    LABEL "|en|Temperature";
    STYLE(WINDOW)
    ITEMS
    {
		mnu_temperature_group
		EDD(ROWBREAK)
		PARAM.ALERT_ACTION.TEMPERATURE_LO_ALERT_ACT
		EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.TEMPERATURE_HI_ALERT_ACT
		EDD(ROWBREAK)
        mnu_temperature_alerts
		EDD(ROWBREAK)
		grp_temperature_extremes
    }
}

MENU mnu_config_current
{
    LABEL "|en|IP Current";
    STYLE(WINDOW)
    ITEMS
    {
		mnu_current_group
		EDD(ROWBREAK)
		PARAM.ALERT_ACTION.IP_DRIVE_CURRENT_ALERT_LO_ACT
		EDD(COLUMNBREAK)
		PARAM.ALERT_ACTION.IP_DRIVE_CURRENT_ALERT_HI_ACT
		EDD(ROWBREAK)
        mnu_ip_current_alert
		EDD(ROWBREAK)
		grp_ip_current_extremes
			PARAM.ALERT_COUNTERS.IP_DRIVE_CURRENT_ALERT_LO_CNT
			PARAM.ALERT_STATE.IP_DRIVE_CURRENT_ALERT_LO_ST
			EDD(COLUMNBREAK)
			PARAM.ALERT_STATE.IP_DRIVE_CURRENT_ALERT_HI_ST
			PARAM.ALERT_COUNTERS.IP_DRIVE_CURRENT_ALERT_HI_CNT
    }
}
MENU grp_alertaction
{
    LABEL "|en|Alert Action";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.ALERT_ACTION.BLOCK_ERR_MAP
        PARAM.ALERT_ACTION.WORKING_TIME_ALERT_ACT
        PARAM.ALERT_ACTION.SENSOR_FAILURE_ALERT_ACT
        PARAM.ALERT_ACTION.PROCESSOR_ALERT_ACT
		EDD(COLUMNBREAK)
        PARAM.ALERT_ACTION.VALVE_CONTROL_ALERT_ACT
        PARAM.ALERT_ACTION.COMMISSIONING_ALERT_ACT
        PARAM.ALERT_ACTION.AIR_SUPPLY_ALERT_ACT
        PARAM.ALERT_ACTION.SUPPORTING_HARDWARE_ALERT_ACT
    }
}
MENU mnu_config_lcddisplay
{
    LABEL "|en|LCD Display";
    STYLE(WINDOW)
    ITEMS
    {
        PARAM.UI_LANGUAGE
        PARAM.UI_CUSTOM_CONFIGURATION.CUSTOM_1_CONFIGURATION
        PARAM.UI_CUSTOM_CONFIGURATION.CUSTOM_2_CONFIGURATION
			EDD(ROWBREAK)
			grp_ui_access_conntrol
    }
}
MENU grp_ui_access_conntrol
{
	LABEL "|en| UI Access Control";
	STYLE(GROUP)
	ITEMS {
		PARAM.UI_ACCESS_CONTROL.LOCK_LEVEL
		PARAM.UI_ACCESS_CONTROL.PASSWORD_ENABLED
		/*PARAM.UI_ACCESS_CONTROL.PASSWORD*/
	}
}
MENU mnu_advanced_valve_configuration
{
	LABEL "|en|Advanced Configuration";
	STYLE(PAGE)
	ITEMS
	{
		grp_booster
		EDD(ROWBREAK)
		grp_accessory
		EDD(ROWBREAK)
		PARAM.ADVANCED
	}
}
MENU grp_booster
{
	LABEL "|en|Booster";
	STYLE(GROUP)
	ITEMS {
		PARAM.BOOSTER.MANUFACTURER_INFO
		PARAM.BOOSTER.MODEL
		PARAM.BOOSTER.QTY
	}
}
MENU grp_accessory
{
	LABEL "|en|Accessory";
	STYLE(GROUP)
	ITEMS {
		PARAM.ACCESSORY.SOLENOID
		PARAM.ACCESSORY.REMOTE_SENSOR
	}
}
MENU mnu_actuator
{
    LABEL "|en|Actuator";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.ACTUATOR_INFO.DESCRIPTOR
		PARAM.ACTUATOR_INFO.MESSAGE
		PARAM.ACTUATOR_INFO.DATE_INFO
		PARAM.ACTUATOR_INFO.SPEC_SHEET
        EDD(COLUMNBREAK)
			PARAM.ACTUATOR_1.ACT_MAN_ID_1
			PARAM.ACTUATOR_1.ACT_MODEL_NUM_1
			PARAM.ACTUATOR_1.ACT_SN_1
		EDD(COLUMNBREAK)
			PARAM.ACTUATOR_2.ACT_TYPE_STRING
			PARAM.ACTUATOR_2.ACT_SIZE
			PARAM.ACTUATOR_2.ACT_ROTARY_MOMENT_ARM
			PARAM.ACTUATOR_2.ACT_EFFECTIVE_AREA
			PARAM.ACTUATOR_3.SHUTOFF_DP
			PARAM.ACTUATOR_3.HAND_WHEEL
			PARAM.ACTUATOR_3.ACT_STYLE
			EDD(COLUMNBREAK)
			PARAM.ACTUATOR_3.ACT_FAIL_ACTION_1
			PARAM.ACTUATOR_3.RELAY_TYPE
			PARAM.ACTUATOR_3.SUPPLY_PRS_MAX
			PARAM.ACTUATOR_3.PRS_CONTROL_HI
			PARAM.ACTUATOR_3.PRS_CONTROL_LO
    }
}
MENU mnu_valve_info
{
    LABEL "|en|Valve ID";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.VALVE_INFO.SAME_AS_ACTUATOR
			PARAM.VALVE_INFO.DESCRIPTOR
			PARAM.VALVE_INFO.MESSAGE
			PARAM.VALVE_INFO.DATE_INFO
			PARAM.VALVE_INFO.SPEC_SHEET
        EDD(COLUMNBREAK)
			PARAM.VALVE_IDENTIFICATION.VALVE_MAN_ID_1
			PARAM.VALVE_IDENTIFICATION.VALVE_MODEL_NUM_1
			PARAM.VALVE_IDENTIFICATION.VALVE_SN_1
        EDD(COLUMNBREAK)
			PARAM.VALVE_SERVICE.SERVICE_1
			PARAM.VALVE_SERVICE.PID_NO
    }
}

MENU mnu_valve_body
{
    LABEL "|en|Valve Body";
    STYLE(GROUP)
    ITEMS
    {
		PARAM.VALVE_BODY_1.VALVE_TYPE_1
			PARAM.VALVE_BODY_1.VALVE_TYPE_1
			PARAM.VALVE_BODY_1.BODY_SIZE
			PARAM.VALVE_BODY_1.PACKING
			PARAM.VALVE_BODY_1.PLUG_TYPE
			PARAM.VALVE_BODY_1.SEAT_RING_TYPE
		EDD(COLUMNBREAK)
			PARAM.VALVE_BODY_2.CHARACTERISTIC
			PARAM.VALVE_BODY_2.LEAKAGE_CLASS
        EDD(COLUMNBREAK)
			PARAM.VALVE_BODY_3.FLOW_ACTION
			PARAM.VALVE_BODY_3.RATED_ADJ_CV
    }
}
MENU grp_position_extremes
{
	 LABEL "|en|Position Extremes";
STYLE(GROUP)
ITEMS
{
		PARAM.POSITION_EXTREMES.FINAL_VALUE_MAX
		PARAM.POSITION_EXTREMES.FINAL_VALUE_MIN
		PARAM.POSITION_EXTREMES.FINAL_POS_VALUE_MAX
		PARAM.POSITION_EXTREMES.FINAL_POS_VALUE_MIN
		PARAM.POSITION_EXTREMES.WORKING_SP_MAX
		PARAM.POSITION_EXTREMES.WORKING_SP_MIN
		PARAM.POSITION_EXTREMES.WORKING_POS_MAX
		PARAM.POSITION_EXTREMES.WORKING_POS_MIN
}
}
MENU grp_pressure_extremes
{
	 LABEL "|en|Pressure Extremes";
STYLE(GROUP)
ITEMS
{
		PARAM.PRESSURE_EXTREMES.SUPPLY_PRESSURE_MIN
		PARAM.PRESSURE_EXTREMES.ACTUATOR_A_MIN
		PARAM.PRESSURE_EXTREMES.ACTUATOR_B_MIN
		PARAM.PRESSURE_EXTREMES.PILOT_MIN
			EDD(COLUMNBREAK)
		PARAM.PRESSURE_EXTREMES.SUPPLY_PRESSURE_MAX
		PARAM.PRESSURE_EXTREMES.ACTUATOR_A_MAX
		PARAM.PRESSURE_EXTREMES.ACTUATOR_B_MAX
		PARAM.PRESSURE_EXTREMES.PILOT_MAX
}
}

MENU grp_temperature_extremes
{
	 LABEL "|en|Temperature Extremes";
STYLE(GROUP)
ITEMS
{
	WHOLE_PARAM__TEMPERATURE_EXTREMES
}
}

MENU grp_ip_current_extremes
{
	 LABEL "|en|IP Current Extremes";
STYLE(GROUP)
ITEMS
{
	PARAM.IP_CURRENT_EXTREMES.IP_CURRENT_MIN
	EDD(COLUMNBREAK)
	PARAM.IP_CURRENT_EXTREMES.IP_CURRENT_MAX
}
}

MENU mnu_tb_exconfig_page
{
    LABEL "|en|Extended Configuration";
    STYLE(PAGE)
    ITEMS
    {
        grp_tb_blockalarm

        mnu_write_alm

		mnu_grant_deny


    }
}

MENU mnu_config
{
    LABEL "|en|Configuration";
    STYLE(MENU)
    ITEMS
    {
        mnu_config_position
        mnu_config_pressure
        mnu_config_temperature
        mnu_config_current
		mnu_travelalerts
		mnu_do_control
        mnu_config_lcddisplay
    }
}

/*=========================/
 * MENUS for Resource Block
 /=========================*/

/*-------------/
** Status menus
/-------------*/

MENU process_variables_root_menu_rb
{
    LABEL "|en|Process Variable";
    ITEMS
    {
       mnu_identification_in_process_variable
       mnu_features
    }
}


MENU mnu_identification_in_process_variable
{
    LABEL "|en|Identification";
    STYLE(PAGE)
    ITEMS
    {
         __res_2_character.BLOCK_TAG
        EDD(ROWBREAK)

        PARAM.MANUFAC_ID
        EDD(COLUMNBREAK)
        PARAM.DEV_TYPE
        EDD(COLUMNBREAK)
        PARAM.DEV_REV
        EDD(ROWBREAK)

        PARAM.DD_RESOURCE
        EDD(COLUMNBREAK)
        PARAM.DD_REV
        EDD(COLUMNBREAK)
        PARAM.ITK_VER
        EDD(ROWBREAK)


        PARAM.SOFTWARE_REV
        EDD(COLUMNBREAK)
        PARAM.HARDWARE_REV
        EDD(COLUMNBREAK)
        PARAM.COMPATIBILITY_REV
        EDD(ROWBREAK)

        PARAM.TAG_DESC
        EDD(COLUMNBREAK)
        PARAM.SOFTWARE_REV_FF
        EDD(COLUMNBREAK)
        PARAM.SOFTWARE_REV_APP
    }
}


/*-------------/
** Device menus
/-------------*/
MENU mnu_fDiagactive
{
LABEL "|en|FD Active Alerts";
STYLE(PAGE)
ITEMS
{
	   __fd_fail_active
		EDD(COLUMNBREAK)
		__fd_offspec_active
		EDD(COLUMNBREAK)
		__fd_maint_active
		EDD(COLUMNBREAK)
		__fd_check_active
		EDD(COLUMNBREAK)
}
}
MENU diagnostic_root_menu_rb
{
    LABEL "|en|Device Diagnostic";
    ITEMS
    {
        mnu_process_in_device_diagnostic
        mnu_alarms_in_device_diagnostic
		mnu_fDiagactive
    }
}

MENU mnu_process_in_device_diagnostic
{
    LABEL "|en|Process";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.MODE_BLK.TARGET
        EDD(COLUMNBREAK)
        PARAM.MODE_BLK.ACTUAL
        EDD(COLUMNBREAK)
        EDD(ROWBREAK)

        PARAM.BLOCK_ERR
        EDD(COLUMNBREAK)
        PARAM.FAULT_STATE
        EDD(COLUMNBREAK)
        PARAM.RS_STATE
		PARAM.BLOCK_ERR_DESC_1 /*from R2*/
    }
}

MENU mnu_alarms_in_device_diagnostic
{
    LABEL "|en|Alarms";
    STYLE(PAGE)
    ITEMS
    {
        mnu_update_evt
        EDD(COLUMNBREAK)

        mnu_block_alm
        EDD(ROWBREAK)
        mnu_write_alm
        EDD(COLUMNBREAK)
        mnu_maint_alm
        EDD(COLUMNBREAK)
        mnu_offspec_alm
        EDD(ROWBREAK)
		mnu_fail_alm
        EDD(COLUMNBREAK)
        mnu_alarm_sum
    }
}

MENU mnu_features
{
    LABEL "|en|Features";
    STYLE(PAGE)
    ITEMS
    {
        /*PARAM.FEATURES*/
        PARAM.FEATURE_SEL
    }
}

/*
MENU mnu_cycles
{
    LABEL "|en|Cycles";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.CYCLE_TYPE
        EDD(COLUMNBREAK)
        PARAM.CYCLE_SEL
        EDD(ROWBREAK)
    }
}

*/

/*
MENU mnu_notify
{
    LABEL "|en|Alerts Notify Setting";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.MAX_NOTIFY
        PARAM.LIM_NOTIFY
    }
}

*/

/*
MENU mnu_communication_setting
{
    LABEL "|en|Communication Setting";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.SHED_RCAS
        PARAM.SHED_ROUT
        PARAM.CONFIRM_TIME
    }
}

*/


/*
MENU mnu_lock
{
    LABEL "|en|Write Lock";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.WRITE_LOCK
        PARAM.WRITE_PRI
    }
}

*/

/*
MENU mnu_alarm
{
    LABEL "|en|Alarm";
    STYLE(PAGE)
    ITEMS
    {
        mnu_update_evt
        EDD(COLUMNBREAK)
        mnu_block_alm
        EDD(COLUMNBREAK)
        mnu_write_alm
        EDD(ROWBREAK)
        mnu_alarm_sum
        EDD(COLUMNBREAK)
        PARAM.ACK_OPTION

    }
}
*/

MENU mnu_grant_deny
{
    LABEL "|en|Grant Deny";
	STYLE(GROUP)
    ITEMS
    {
        PARAM.GRANT_DENY.GRANT
        PARAM.GRANT_DENY.DENY
    }
}

MENU mnu_fail_alm
{
	LABEL "|en|Failed Alm";
	STYLE(GROUP)
	ITEMS
	{
		PARAM.FD_FAIL_ALM.UNACKNOWLEDGED,
		PARAM.FD_FAIL_ALM.ALARM_STATE,
		PARAM.FD_FAIL_ALM.TIME_STAMP,
		PARAM.FD_FAIL_ALM.SUB_CODE,
		PARAM.FD_FAIL_ALM.VALUE
	}
}


MENU mnu_write_alm
{
    LABEL "|en|Write Alarm";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.WRITE_ALM.UNACKNOWLEDGED,
        PARAM.WRITE_ALM.ALARM_STATE,
        PARAM.WRITE_ALM.TIME_STAMP,
        PARAM.WRITE_ALM.SUB_CODE,
		PARAM.WRITE_ALM.VALUE
    }
}

MENU mnu_maint_alm
{
    LABEL "|en|Maintenance Alm";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FD_MAINT_ALM.UNACKNOWLEDGED,
        PARAM.FD_MAINT_ALM.ALARM_STATE,
        PARAM.FD_MAINT_ALM.TIME_STAMP,
        PARAM.FD_MAINT_ALM.SUB_CODE,
        PARAM.FD_MAINT_ALM.VALUE
    }
}

MENU mnu_offspec_alm
{
    LABEL "|en|Off-spec Alm";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.FD_OFFSPEC_ALM.UNACKNOWLEDGED,
        PARAM.FD_OFFSPEC_ALM.ALARM_STATE,
        PARAM.FD_OFFSPEC_ALM.TIME_STAMP,
        PARAM.FD_OFFSPEC_ALM.SUB_CODE,
        PARAM.FD_OFFSPEC_ALM.VALUE
    }
}

MENU mnu_alarm_sum
{
    LABEL "|en|Alarm Sum";
    STYLE(GROUP)
    ITEMS
    {
         PARAM.ALARM_SUM.CURRENT,
         PARAM.ALARM_SUM.UNACKNOWLEDGED,
         PARAM.ALARM_SUM.UNREPORTED,
         PARAM.ALARM_SUM.DISABLED
    }
}


MENU mnu_block_alm
{
    LABEL "|en|Block Alarm";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.BLOCK_ALM.UNACKNOWLEDGED,
        PARAM.BLOCK_ALM.ALARM_STATE,
        PARAM.BLOCK_ALM.TIME_STAMP,
        PARAM.BLOCK_ALM.SUB_CODE,
        PARAM.BLOCK_ALM.VALUE
    }
}



MENU mnu_update_evt
{
    LABEL "|en|Update Evt";
    STYLE(GROUP)
    ITEMS
    {
        PARAM.UPDATE_EVT.UNACKNOWLEDGED,
        PARAM.UPDATE_EVT.UPDATE_STATE,
        PARAM.UPDATE_EVT.TIME_STAMP,
        PARAM.UPDATE_EVT.STATIC_REVISION,
        PARAM.UPDATE_EVT.RELATIVE_INDEX
    }
}

/*------------/
** Setup menus
/------------*/

MENU mnu_process_in_device_setup
{
    LABEL "|en|Process";
    STYLE(PAGE)
    ITEMS
    {
       mnu_mode_row
       EDD(ROWBREAK)

       PARAM.STRATEGY
	   EDD(COLUMNBREAK)
       PARAM.ALERT_KEY
       EDD(COLUMNBREAK)

       PARAM.SHED_RCAS
       EDD(COLUMNBREAK)
       PARAM.SHED_ROUT
       EDD(ROWBREAK)

       PARAM.FAULT_STATE
       EDD(COLUMNBREAK)
       PARAM.CLR_FSTATE
       EDD(COLUMNBREAK)
       PARAM.SET_FSTATE
       EDD(ROWBREAK)


       mnu_update_evt
    }
}

MENU mnu_hardware
{
    LABEL "|en|Hardware";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.HARD_TYPES
        EDD(COLUMNBREAK)
        PARAM.MEMORY_SIZE
        EDD(COLUMNBREAK)
        PARAM.FREE_TIME
        EDD(ROWBREAK)

        PARAM.FREE_SPACE
        EDD(COLUMNBREAK)
        PARAM.MIN_CYCLE_T
        EDD(COLUMNBREAK)
        PARAM.NV_CYCLE_T
        EDD(ROWBREAK)

        PARAM.RESTART
        EDD(COLUMNBREAK)
        PARAM.WRITE_LOCK
    }
}

MENU mnu_alarm_in_device_setup
{
    LABEL "|en|Alarms";
    STYLE(PAGE)
    ITEMS
    {
        PARAM.WRITE_PRI
        EDD(COLUMNBREAK)
        PARAM.CONFIRM_TIME
        EDD(COLUMNBREAK)
        PARAM.MAX_NOTIFY
        EDD(ROWBREAK)

        PARAM.LIM_NOTIFY
        EDD(COLUMNBREAK)
        PARAM.ACK_OPTION
        EDD(ROWBREAK)

        mnu_block_alm
        EDD(COLUMNBREAK)

		grp_blockerror
		EDD(COLUMNBREAK)

        mnu_write_alm
        EDD(COLUMNBREAK)
        mnu_alarm_sum
    }
}

MENU mnu_identification_in_device_setup
{
    LABEL "|en|Identification";
    STYLE(PAGE)
    ITEMS
    {
        __res_2_character.BLOCK_TAG
        EDD(COLUMNBREAK)

        PARAM.MANUFAC_ID
        EDD(COLUMNBREAK)
        PARAM.DEV_TYPE
        EDD(COLUMNBREAK)
        PARAM.DEV_REV
        EDD(ROWBREAK)

        PARAM.DD_REV
        EDD(COLUMNBREAK)
        PARAM.ITK_VER
        EDD(COLUMNBREAK)
        PARAM.SOFTWARE_REV
        EDD(ROWBREAK)

        PARAM.HARDWARE_REV
        EDD(COLUMNBREAK)
        PARAM.TAG_DESC
        EDD(COLUMNBREAK)
        PARAM.SOFTWARE_REV_FF
        EDD(ROWBREAK)
        PARAM.SOFTWARE_REV_APP
    }
}

MENU mnu_options
{
    LABEL "|en|Options";
    STYLE(PAGE)
    ITEMS
    {
         PARAM.GRANT_DENY.GRANT
         EDD(COLUMNBREAK)
         PARAM.GRANT_DENY.DENY
         EDD(COLUMNBREAK)
         PARAM.COMPATIBILITY_REV
		 PARAM.DD_RESOURCE
		 EDD(COLUMNBREAK)
		 PARAM.FEATURE_SEL
         /*PARAM.FEATURES*/ /*from R2*/
         EDD(ROWBREAK)
         PARAM.CYCLE_SEL
         EDD(COLUMNBREAK)
         PARAM.CYCLE_TYPE
    }
}

MENU mnu_fDiagmap
{
LABEL "|en|FD Alert Map";
STYLE(PAGE)
ITEMS
{
	    __fd_fail_map
		EDD(COLUMNBREAK)
		__fd_offspec_map
		EDD(COLUMNBREAK)
		__fd_maint_map
		EDD(COLUMNBREAK)
		__fd_check_map
		EDD(ROWBREAK)
	    FD_FAIL_MAP_default
		/*EDD(COLUMNBREAK)
		FD_OFFSPEC_MAP_default
		EDD(COLUMNBREAK)
		FD_MAINT_MAP_default
		EDD(COLUMNBREAK)
		FD_CHECK_MAP_default
		EDD(COLUMNBREAK)*/
}
}

MENU mnu_fDiagmask
{
	LABEL "|en|FD Alert Mask";
STYLE(PAGE)
ITEMS
{
	    __fd_fail_mask
		EDD(COLUMNBREAK)
		__fd_offspec_mask
		EDD(COLUMNBREAK)
		__fd_maint_mask
		EDD(COLUMNBREAK)
		__fd_check_mask
		EDD(COLUMNBREAK)
}
}

MENU mnu_fDiagAlertpriorities
{
LABEL "|en|FD Alert Priorities";
STYLE(PAGE)
ITEMS
{
	    __fd_fail_pri
		EDD(COLUMNBREAK)
		__fd_offspec_pri
		EDD(COLUMNBREAK)
		__fd_maint_pri
		EDD(COLUMNBREAK)
		__fd_check_pri
		EDD(ROWBREAK)
		FD_FAIL_pri_default
		EDD(COLUMNBREAK)
		/*FD_OFFSPEC_pri_default
		EDD(COLUMNBREAK)
		FD_MAINT_pri_default
		EDD(COLUMNBREAK)*/



}
}
/********************************************************************************************************************************************************************/
/*MENU mnu_data_collection_config0
{
	LABEL "|en|Data Collection Configuration 0";
	STYLE(GROUP)
#ifndef DD4
    VALIDITY
        IF(PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTSELECTOR == 0)
        { TRUE; }
        ELSE
        { FALSE; }
#endif
	ITEMS {mnu_data_collection_config}
}

MENU mnu_data_collection_config1
{
	LABEL "|en|Data Collection Configuration 1";
	STYLE(GROUP)
#ifndef DD4
    VALIDITY
        IF(PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTSELECTOR == 1)
        { TRUE; }
        ELSE
        { FALSE; }
#endif
	ITEMS {mnu_data_collection_config}
}

MENU mnu_data_collection_config
{
	LABEL "|en|Our Friday fun";
	/*STYLE(GROUP)*/
/*	ITEMS
{
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTSELECTOR
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTBASE
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTSKIPCOUNT
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTBITMAP
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTMAXSAMPLES
	PARAM.DATA_COLLECTION_CONFIG.DATACOLLECTMAXPRESAMPLES
   }

}
	*/
MENU mnu_data_collection_trig
{
	LABEL "|en|Data Collection Trigger";
	STYLE(GROUP)
	ITEMS
{
    WHOLE_PARAM__DATA_COLLECTION_TRIGGER
#if 0
	PARAM.DATA_COLLECTION_TRIGGER.TRIGGER_ON_DEMAND
	PARAM.DATA_COLLECTION_TRIGGER.TRIGGER_BY_DI_SWITCH
	PARAM.DATA_COLLECTION_TRIGGER.TRIGGER_BY_AI_INPUT
	PARAM.DATA_COLLECTION_TRIGGER.AI_TRIGGER_INPUT_THRESHOLD
#endif
 }
}
/******************************************************************************************************************/
#ifndef DD4
MENU mnu_pst
{
	LABEL "|en|PST-Partial Stroke Test";
	STYLE(WINDOW)
	ITEMS
	{
	mnu_pst_trigger
	EDD(ROWBREAK)
	mnu_pst_config
	}
}

MENU mnu_pst_trigger
{
	LABEL "|en|Partial Stroke Test (PST) Trigger";
STYLE(GROUP)

	ITEMS
{
	PARAM.PST_TRIGGER.PST_TRIGGER_ON_DEMAND
	PARAM.PST_TRIGGER.PST_TRIGGER_BY_DI_SWITCH
	EDD(COLUMNBREAK)
	PARAM.PST_TRIGGER.PST_TRIGGER_BY_AI_INPUT
	PARAM.PST_TRIGGER.PST_AI_TRIGGER_INPUT_THRESHOLD
	}
}
MENU mnu_pst_config
{
	LABEL "|en|Partial Stroke Test (PST) Configuration";
	STYLE(GROUP)
	ITEMS
{
	pst_graph_image
	check_process_btn
	grp_shape_configuration
	EDD(COLUMNBREAK)
	grp_pst_cancellation
	EDD(ROWBREAK)
	PARAM.PST_CONFIG.PST_DATAMAP
		EDD(COLUMNBREAK)
	PARAM.PST_CONFIG.PST_FREEZE_OPTIONS

 }
}
MENU grp_shape_configuration
{
	LABEL "|en|PST Shape Configuration";
	STYLE(GROUP)
	ITEMS
{
	PARAM.PST_CONFIG.PST_PATTERN
	PARAM.PST_CONFIG.PST_TRAVEL
	PARAM.PST_CONFIG.PST_SETPOINT_RATE
	PARAM.PST_CONFIG.PST_PAUSE
	PARAM.PST_CONFIG.PST_LEADTIME
 }
}
MENU grp_pst_cancellation
{
	LABEL "|en|PST Configuration";
	STYLE(GROUP)
	ITEMS
{
	PARAM.PST_CONFIG.SETPOINT_CHANGE_THRESHOLD
	PARAM.PST_CONFIG.PILOT_THRESHOLD
	PARAM.PST_CONFIG.ACTUATOR_THRESHOLD
	PARAM.PST_CONFIG.STROKE_TIMEOUT_OVERRIDE
	PARAM.PST_CONFIG.PST_MAXTIME
	PARAM.PST_CONFIG.PST_SKIP_COUNT
 }
}
#endif
/**********************************************************************************************************************************/
MENU mnu_data_collection
{
	LABEL "|en|Data Collection";
	STYLE(PAGE)
	ITEMS
{
	grp_data_collection_perm
	EDD(COLUMNBREAK)
		grp_data_collection_temp
		EDD(COLUMNBREAK)
	mnu_data_collection_trig
}
}
MENU grp_data_collection_perm
{
	LABEL "|en|Permanent Data Configuration";
STYLE(GROUP)
ITEMS
{
	PARAM.DATA_CONFIG_PERM.DATACOLLECTBASE
		PARAM.DATA_CONFIG_PERM.DATACOLLECTSKIPCOUNT
		PARAM.DATA_CONFIG_PERM.DATACOLLECTBITMAP
		PARAM.DATA_CONFIG_PERM.DATACOLLECTMAXSAMPLES
		PARAM.DATA_CONFIG_PERM.DATACOLLECTMAXPRESAMPLES
}
}
MENU grp_data_collection_temp
{
	LABEL "|en|Temporary Data Configuration";
STYLE(GROUP)
ITEMS
{

	PARAM.DATA_CONFIG_TEMP.DATACOLLECTBASE
		PARAM.DATA_CONFIG_TEMP.DATACOLLECTSKIPCOUNT
		PARAM.DATA_CONFIG_TEMP.DATACOLLECTBITMAP
		PARAM.DATA_CONFIG_TEMP.DATACOLLECTMAXSAMPLES
}
}
MENU mnu_fDiag
{
	LABEL "|en|FD Alert Configuration";
  STYLE(PAGE)
  ITEMS
{
	/*mnu_fDiagactive*/
	mnu_fDiagmap
	mnu_fDiagmask
	mnu_fDiagAlertpriorities
}
}
MENU device_root_menu_rb
{
    LABEL "|en|Device Setup";
    ITEMS
    {
        mnu_process_in_device_setup
        mnu_identification_in_device_setup
        mnu_hardware
        mnu_alarm_in_device_setup
        mnu_options
		mnu_tb_exconfig_page
		mnu_fDiag
    }
}

/*----------/
** Top menus
/----------*/

MENU Menu_Top_rb
{
    LABEL   "|en|Menu Top";
    ITEMS
    {
		device_root_menu_rb
        diagnostic_root_menu_rb
		process_variables_root_menu_rb
    }
}

/*=========================/
 * Others
 /=========================*/
#if 1 /*!!!NOT!!! for Open*/

MENU Menu_Top_ptb_bar
{
    LABEL   "|en|Menu Bar for PTB";
    ITEMS
    {
        diagnostic_root_menu_ptb
        process_variables_root_menu_ptb
        device_root_menu_ptb
    }
}

MENU mnu_rb_0
{
    LABEL "|en|Top 0";
    ITEMS
    {
        Menu_Top_rb
    }
}

MENU mnu_PTB_0
{
    LABEL "|en|Top 0";
    ITEMS
    {
        /*mnu_other_useless*/
        Menu_Top_ptb_bar
    }
}

#if 0
MENU mnu_other_useless
{
    LABEL "|en|independent_items";
    {
        src_actuators_a_press
        src_actuators_b_press
        src_final_pos_value
		src_analog_input /******************************************************************************************************/
        src_final_value
        src_supply_press
        src_working_pos
        src_working_sp
        y_axis_final_pos
        y_axis_final_value
		y_axis_analog_input /***************************************************************************************************/
        y_axis_position
        y_axis_pressure
        y_axis_temperature
        y_axis_working_pos
        y_axis_working_sp
    }
}
#endif


#endif
#endif  /*NOMENUS*/
#endif  /* TB_MENU_2013_01_29_13_13_36_GE_300010777 */

