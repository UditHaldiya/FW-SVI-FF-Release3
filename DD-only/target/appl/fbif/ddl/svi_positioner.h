/* ===========================================================================

FILE_NAME          svi_positioner.h



FUNCTIONAL_MODULE_DESCRIPTION

  This file contains definitions for the DD of the SVI Positioner application.

=========================================================================== */

/*------------------------------------------------------------/
** Definitions Strings for LABLE and HELPS for SVI2 AP FF
/------------------------------------------------------------*/

#define   dct_ack_opt_0                                 \
    "|en|Disc Alm Auto Ack"                             \

#define   dct_ack_opt_0_help                            \
    "|en|Discrete alarm auto acknowledge enabled"       \

#define   dct_ack_opt_1                                 \
    "|en|HiHi Alm Auto Ack"                             \

#define   dct_ack_opt_1_help                            \
    "|en|HiHi alarm auto acknowledge enabled"           \

#define   dct_ack_opt_2                                 \
    "|en|Hi Alm Auto Ack"                               \

#define   dct_ack_opt_2_help                            \
    "|en|Hi alarm auto acknowledge enabled"             \

#define   dct_ack_opt_3                                 \
    "|en|LoLo Alm Auto Ack"                             \

#define   dct_ack_opt_3_help                            \
    "|en|LoLo alarm auto acknowledge enabled"           \

#define   dct_ack_opt_4                                 \
    "|en|Lo Alm Auto Ack"                               \

#define   dct_ack_opt_4_help                            \
    "|en|Lo alarm auto acknowledge enabled"             \

#define   dct_ack_opt_5                                 \
    "|en|Deviation Hi Alm Auto Ack"                            \

#define   dct_ack_opt_5_help                            \
    "|en|Deviation high alarm auto acknowledge enabled" \

#define   dct_ack_opt_6                                 \
    "|en|Deviation Lo Alm Auto Ack"                            \

#define   dct_ack_opt_6_help                            \
    "|en|Deviation low alarm auto acknowledge enabled"  \

#define   dct_ack_opt_7                                 \
    "|en|Blk Alm Auto Ack"                              \

#define   dct_ack_opt_7_help                            \
    "|en|Block alarm auto acknowledge enabled"          \

#define   dct_ack_opt_8                                 \
    "|en|Fail Alm Auto Ack"                             \

#define   dct_ack_opt_8_help                            \
    "|en|Fail alarm auto acknowledge enabled"           \

#define   dct_ack_opt_9                                 \
    "|en|Off Spec Alm Auto Ack"                         \

#define   dct_ack_opt_9_help                            \
    "|en|Off spec alarm auto acknowledge enabled"       \

#define   dct_ack_opt_10                                \
    "|en|Maint Alm Auto Ack"                            \

#define   dct_ack_opt_10_help                           \
    "|en|Maintenance alarm auto acknowledge enabled"    \

#define   dct_ack_opt_11                                \
    "|en|Check Alm Auto Ack"                            \

#define   dct_ack_opt_11_help                           \
    "|en|Check alarm auto acknowledge enabled"          \

#define _FF_ACK_OPT_0  { _DISCRETE_ALARM,          dct_ack_opt_0,    dct_ack_opt_0_help }
#define _FF_ACK_OPT_1  { _HIGH_HIGH_ALARM,         dct_ack_opt_1,    dct_ack_opt_1_help }
#define _FF_ACK_OPT_2  { _HIGH_ALARM,              dct_ack_opt_2,    dct_ack_opt_2_help }
#define _FF_ACK_OPT_3  { _LOW_LOW_ALARM,           dct_ack_opt_3,    dct_ack_opt_3_help }
#define _FF_ACK_OPT_4  { _LOW_ALARM,               dct_ack_opt_4,    dct_ack_opt_4_help }
#define _FF_ACK_OPT_5  { _DEVIATION_HIGH_ALARM,    dct_ack_opt_5,    dct_ack_opt_5_help }
#define _FF_ACK_OPT_6  { _DEVIATION_LOW_ALARM,     dct_ack_opt_6,    dct_ack_opt_6_help }
#define _FF_ACK_OPT_7  { _BLOCK_ALARM,             dct_ack_opt_7,    dct_ack_opt_7_help }
#define _FF_ACK_OPT_8  { _FAIL_ALARM,              dct_ack_opt_8,    dct_ack_opt_8_help }
#define _FF_ACK_OPT_9  { _OFF_SPEC_ALARM,          dct_ack_opt_9,    dct_ack_opt_9_help }
#define _FF_ACK_OPT_10 { _MAINTENANCE_ALARM,       dct_ack_opt_10,   dct_ack_opt_10_help }
#define _FF_ACK_OPT_11 { _CHECK_ALARM,             dct_ack_opt_11,   dct_ack_opt_11_help }

/*------------------------------------------------------------/
** Addtional parameter definitions for PID SVi2 AP FF
/------------------------------------------------------------*/

#define HLP_ALGORITHM                                                                   \
  "|en|Used PID algorithm"                                                              \

#define LBL_ALGORITHM                                                                   \
  "|en|Algorithm"                                                                       \

#define LBL_IDEAL    "|en|Ideal"
#define LBL_SERIAL   "|en|Serial"
#define LBL_PARALLEL "|en|Parallel"
#define LBL_I_PD     "|en|I-PD"
#define LBL_IP_D     "|en|IP-D"

#define ENUM_ALGORITHM              \
  { 0, LBL_IDEAL, LBL_IDEAL},       \
  { 1, LBL_SERIAL, LBL_SERIAL},     \
  { 2, LBL_PARALLEL, LBL_PARALLEL}, \
  { 3, LBL_I_PD, LBL_I_PD},         \
  { 4, LBL_IP_D, LBL_IP_D}          \

#define HLP_TFPD                                                                    \
  "|en|Time constant filtering the Proportional-Derivative component"                                                               \

#define LBL_TFPD                                                                    \
  "|en|PD Filter Time constant"           \

#define HLP_TFPID                                                                   \
  "|en|Time constant of the single exponential filter of all PID components"                                                              \

#define LBL_TFPID                                                                   \
  "|en|PID Filter Time constant"           \


/*------------------------------------------------------------/
** Channels Definitions for SVi2 AP FF
/------------------------------------------------------------*/



/*------------------------------------------------------------/
** Others from Softing
/------------------------------------------------------------*/

/*
**********************************************************************
**********************************************************************
resource block
**********************************************************************
**********************************************************************
*/

#define FEATURES_RES2 { 0x0002,  [feature_report],       [feature_report_help]                     }, \
                      { 0x0004,  [feature_faultstate],   [feature_faultstate_help]                 }, \
                      { 0x0008,  [feature_soft_write],   [feature_soft_write_help]                 }, \
                      { 0x0010,  [feature_hard_write],   [feature_hard_write_help]                 }, \
                      { 0x0020,  [feature_out_readback], [feature_out_readback_help]               }, \
                      { 0x0400,  "|en|Mbit Alarm",       "|en|Multi-bit Alarm supported"           }

/*
**********************************************************************
**********************************************************************
function blocks
**********************************************************************
**********************************************************************
*/



#define ACK_OPTIONS_AI     { 0x0002,  "|en|HiHi Alm Auto Ack Enabled",  "|en|HiHi alarm automatically acknowledged enabled"  }, \
                           { 0x0004,  "|en|Hi Alm Auto Ack Enabled",    "|en|Hi alarm automatically acknowledged enabled"    }, \
                           { 0x0008,  "|en|LoLo Alm Auto Ack Enabled",  "|en|LoLo alarm automatically acknowledged enabled"  }, \
                           { 0x0010,  "|en|Lo Alm Auto Ack Enabled",    "|en|Lo alarm automatically acknowledged enabled"    }, \
                           { 0x0080,  "|en|Block Alm Auto Ack Enabled", "|en|Block alarm automatically acknowledged enabled" }

#define ACK_OPTIONS_DI     { 0x0001,  "|en|Disc Alm Auto Ack Enabled",     "|en|Discrete alarm automatically acknowledged enabled" }, \
                           { 0x0080,  "|en|Block Alm Auto Ack Enabled",    "|en|Block alarm automatically acknowledged enabled"    }

#define ACK_OPTIONS_PID    { 0x0002,  "|en|HiHi Alm Auto Ack Enabled",     "|en|HiHi alarm automatically acknowledged enabled"         }, \
                           { 0x0004,  "|en|Hi Alm Auto Ack Enabled",       "|en|Hi alarm automatically acknowledged enabled"           }, \
                           { 0x0008,  "|en|LoLo Alm Auto Ack Enabled",     "|en|LoLo alarm automatically acknowledged enabled"         }, \
                           { 0x0010,  "|en|Lo Alm Auto Ack Enabled",       "|en|Lo alarm automatically acknowledged enabled"           }, \
                           { 0x0020,  "|en|DevHi Alm Auto Ack Enabled",    "|en|Deviation Hi alarm automatically acknowledged enabled" }, \
                           { 0x0040,  "|en|DevLo Alm Auto Ack Enabled",    "|en|Deviation Lo alarm automatically acknowledged enabled" }, \
                           { 0x0080,  "|en|Block Alm Auto Ack Enabled",    "|en|Block alarm automatically acknowledged enabled"        }

#define STATUS_OPTIONS_PID { 0x0001, [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         }, \
                           { 0x0002, [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     }, \
                           { 0x0004, [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     }, \
                           { 0x0020, [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         }, \
                           { 0x0200, [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }, \
                           { 0x0400, "|en|Target to Man if BAD TRK_IN_D", "|en|Target to Man if BAD TRK_IN_D"  }, \
                           { 0x0800, "|en|IFS if BAD TRK_IN_D",           "|en|IFS if BAD TRK_IN_D"            }



#define LBL_ISFB    "|en|IS"
#define HLP_ISFB    "|en| The signal selector block provides selection of" \
                    "up to four inputs and generates an output based on the" \
                    "configured action."

#define LBL_ARFB    "|en|AR"
#define HLP_ARFB    "|en|The Arithmetic Function Block The AR block is" \
                    "intended for use in calculating measurements from" \
                    "combinations of signals from sensors."

#define LBL_MAI "|en|Multiple Analog Input"
      /* standard.dct: "mai Block", NI configurator displays capitals only => "B" */


/*
**********************************************************************
input selector block
**********************************************************************
*/
#define LBL_ISEL_DISABLE_VALUE         "|en|Value"
#define HLP_ISEL_DISABLE_VALUE         [blank]

#define ENUM_ISEL_DISABLE_USE          {0 ,"|en|Use",[blank]}
#define ENUM_ISEL_DISABLE_DISABLE      {1 ,"|en|Disable",[blank]}

#define ENUM_SELECT_TYPE_UNITIALIZED   {0 ,"|en|Uninitalized",[blank]}
#define ENUM_SELECT_TYPE_FIRST_GOOD    {1 ,"|en|First good",[blank]}
#define ENUM_SELECT_TYPE_MINIMUM       {2 ,"|en|Minimum",[blank]}
#define ENUM_SELECT_TYPE_MAXIMUM       {3 ,"|en|Maximum",[blank]}
#define ENUM_SELECT_TYPE_MIDDLE        {4 ,"|en|Middle",[blank]}
#define ENUM_SELECT_TYPE_AVERAGE       {5 ,"|en|Average",[blank]}

#define LBL_OP_SELECT_VALUE            "|en|Value"
#define HLP_OP_SELECT_VALUE            [blank]

#define LBL_SELECTED_VALUE             "|en|Value"
#define HLP_SELECTED_VALUE             [blank]

#define ENUM_OP_SELECT_0               {0 ,"|en|No selection", [blank] }
#define ENUM_OP_SELECT_1               {1 ,"|en|IN_1 selected", [blank] }
#define ENUM_OP_SELECT_2               {2 ,"|en|IN_2 selected", [blank] }
#define ENUM_OP_SELECT_3               {3 ,"|en|IN_3 selected", [blank] }
#define ENUM_OP_SELECT_4               {4 ,"|en|IN_4 selected", [blank] }


/*
**********************************************************************
Output Splitter Function Block
**********************************************************************
*/
#define LBL_OSFB  "|en|OS"
#define HLP_OSFB  "|en|The output splitter block provides the capability to" \
                  " drive two control outputs from a single input. Each output" \
                  " is a linear function of some portion of the input."


#define STATUS_OPTIONS_OS    { 0x0002, [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     }, \
                             { 0x0200, [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }


/*
**********************************************************************
arithmetic block
**********************************************************************
*/
#define ENUM_ARITH_TYPE_UNITIALIZED       {0 ,"|en|Uninitalized",[blank]}
#define ENUM_ARITH_TYPE_FLOW_COMP_LIN     {1 ,"|en|Flow compensation, linear",[blank]}
#define ENUM_ARITH_TYPE_FLOW_COMP_SQR     {2 ,"|en|Flow compensation, square root",[blank]}
#define ENUM_ARITH_TYPE_FLOW_COMP_APPROX  {3 ,"|en|Flow compensation, approximate",[blank]}
#define ENUM_ARITH_TYPE_BTU_FLOW          {4 ,"|en|BTU flow",[blank]}
#define ENUM_ARITH_TYPE_MULT_DIV          {5 ,"|en|Traditional Multiply Divide",[blank]}
#define ENUM_ARITH_TYPE_AVERAGE           {6 ,"|en|Average",[blank]}
#define ENUM_ARITH_TYPE_TRADIT_SUM        {7 ,"|en|Traditional Summer",[blank]}
#define ENUM_ARITH_TYPE_POLYNOM           {8 ,"|en|Fourth order polynomial",[blank]}
#define ENUM_ARITH_TYPE_HTG_COMP          {9 ,"|en|Simple HTG compensated level",[blank]}
#define ENUM_ARITH_TYPE_POLYNOM_2         {10 ,"|en|Fourth order polynomial 2",[blank]}

#define ENUM_AR_INPUT_OPT_IN_USE_UNCERT    { 0x0001 ,"|en|IN Use uncertain",[blank]}
#define ENUM_AR_INPUT_OPT_IN_LO_USE_UNCERT { 0x0002 ,"|en|IN_LO Use uncertain",[blank]}
#define ENUM_AR_INPUT_OPT_IN_1_USE_UNCERT  { 0x0004 ,"|en|IN_1 Use uncertain",[blank]}
#define ENUM_AR_INPUT_OPT_IN_1_USE_BAD     { 0x0008 ,"|en|IN_1 Use bad",[blank]}
#define ENUM_AR_INPUT_OPT_IN_2_USE_UNCERT  { 0x0010 ,"|en|IN_2 Use uncertain",[blank]}
#define ENUM_AR_INPUT_OPT_IN_2_USE_BAD     { 0x0020 ,"|en|IN_2 Use bad",[blank]}
#define ENUM_AR_INPUT_OPT_IN_3_USE_UNCERT  { 0x0040 ,"|en|IN_3 Use uncertain",[blank]}
#define ENUM_AR_INPUT_OPT_IN_3_USE_BAD     { 0x0080 ,"|en|IN_3 Use bad",[blank]}


/*
**********************************************************************
**********************************************************************
transducer blocks
**********************************************************************
**********************************************************************
*/

/*
**********************************************************************
AI_transducer_block
**********************************************************************
*/

#define LBL_POSITIONER_TRANSDUCER_BLOCK   "|en|Positioner Transducer Block"
#define HLP_POSITIONER_TRANSDUCER_BLOCK   [blank]

/*
****** aitb_character ******
*/
#define LBL_PTB_CHARACTER   "|en|ptb_character"
#define HLP_PTB_CHARACTER   [blank]

/*
****** pv_unit ******
*/
#define LBL_PV_UNIT   "|en|PV Unit"
#define HLP_PV_UNIT   "|en|Unit of the primary value as delivered by the HART device"

/*
****** sv_unit ******
*/
#define LBL_SV_UNIT   "|en|SV Unit"
#define HLP_SV_UNIT   "|en|Unit of the secondary value as delivered by the HART device"

/*
****** hart_man_id ******
*/
#define LBL_HART_MAN_ID   "|en|HART Manufacturer ID"
#define HLP_HART_MAN_ID   "|en|Manufacturer-ID of the HART device"

/*
****** hart_dev_type ******
*/
#define LBL_HART_DEV_TYPE   "|en|HART Device Type"
#define HLP_HART_DEV_TYPE   "|en|Device-Type of the HART device"

/*
****** hart_dev_id ******
*/
#define LBL_HART_DEV_ID   "|en|HART Device ID"
#define HLP_HART_DEV_ID   "|en|Device-ID of the HART device"

/*
****** hart_dev_rev ******
*/
#define LBL_HART_DEV_REV   "|en|HART Device Revision"
#define HLP_HART_DEV_REV   "|en|Device-Revision of the HART device"

/*
****** hart_sw_rev ******
*/
#define LBL_HART_SW_REV   "|en|HART SW Revision"
#define HLP_HART_SW_REV   "|en|Software-Revision of the HART device"

/*
****** hart_hw_rev ******
*/
#define LBL_HART_HW_REV   "|en|HART HW Revision"
#define HLP_HART_HW_REV   "|en|Hardware-Revision of the HART device"

/*
****** hart_tag ******
*/
#define LBL_HART_TAG   "|en|HART Tag"
#define HLP_HART_TAG   "|en|Local tag of the HART device as read by CMD#13"

/*
****** hart_descr ******
*/
#define LBL_HART_DESCR   "|en|HART Description"
#define HLP_HART_DESCR   "|en|Local description of the HART device as read by CMD#13"

#if 0
/*
****** hart_date ******
*/
#define LBL_HART_DATE   "|en|HART Date"
#define HLP_HART_DATE   "|en|Date information of the HART device as read by CMD#13"
#endif

/*
****** day ******
*/
#define LBL_DAY   "|en|Day"
#define HLP_DAY   "|en|Date: day of month in HART format"

/*
****** month ******
*/
#define LBL_MONTH   "|en|Month"
#define HLP_MONTH   "|en|Date: month in HART format"

/*
****** year ******
*/
#define LBL_YEAR   "|en|Year"
#define HLP_YEAR   "|en|Date: year in HART format starting at 1900"

/*
****** ramp_value ******
*/
#define LBL_RAMP_VALUE   "|en|Ramp Value"
#define HLP_RAMP_VALUE   [blank]

/*
****** ramp_rate ******
*/
#define LBL_RAMP_RATE   "|en|Ramp Rate"
#define HLP_RAMP_RATE   [blank]

/*
****** ramp_min ******
*/
#define LBL_RAMP_MIN   "|en|Ramp Min"
#define HLP_RAMP_MIN   [blank]

/*
****** ramp_max ******
*/
#define LBL_RAMP_MAX   "|en|Ramp Max"
#define HLP_RAMP_MAX   [blank]

/*
****** rect_value ******
*/
#define LBL_RECT_VALUE   "|en|Rect Value"
#define HLP_RECT_VALUE   [blank]

/*
****** rect_period ******
*/
#define LBL_RECT_PERIOD   "|en|Rect Period"
#define HLP_RECT_PERIOD   [blank]

/*
****** rect_min ******
*/
#define LBL_RECT_MIN   "|en|Rect min"
#define HLP_RECT_MIN   [blank]

/*
****** rect_max ******
*/
#define LBL_RECT_MAX   "|en|Rect max"
#define HLP_RECT_MAX   [blank]

/*
****** const_value ******
*/
#define LBL_CONST_VALUE   "|en|Constant Value"
#define HLP_CONST_VALUE   [blank]

/*
****** comm_state ******
*/
#define LBL_COMM_STATE "|en|Communication State"
#define HLP_COMM_STATE [blank]


/*
**********************************************************************
VIEWs
**********************************************************************
*/

#define LBL_VIEW_1_LIST  "|en|View 1"
#define LBL_VIEW_2_LIST  "|en|View 2"
#define LBL_VIEW_3_LIST  "|en|View 3"
#define LBL_VIEW_4_LIST  "|en|View 4"

/*
****** ptb_view_1 ******
*/
#define LBL_PTB_VIEW_1   "|en|ptb_view_1"
#define HLP_PTB_VIEW_1   "|en|"

/*
****** ptb_view_2 ******
*/
#define LBL_PTB_VIEW_2   "|en|ptb_view_2"
#define HLP_PTB_VIEW_2   "|en|"

/*
****** ptb_view_3 ******
*/
#define LBL_PTB_VIEW_3   "|en|ptb_view_3"
#define HLP_PTB_VIEW_3   "|en|"

/*
****** ptb_view_4 ******
*/
#define LBL_PTB_VIEW_4   "|en|ptb_view_4"
#define HLP_PTB_VIEW_4   "|en|"


/*
****** New defines ******
*/

