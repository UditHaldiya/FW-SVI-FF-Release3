/*
** @(#)adv_parm.ddl    1.0 Thu May 23 10:21:53 2002

**
** FF standard advanced parameter definitions
** Filename: adv_parm.ddl
** Spec revision:       FF-900 FS 1.0 DDL spec
**                      FF-892 FS 1.5 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
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
** DBG   Revision 1.0  20020523
** FI    Revision 1.1  20051109
**       added __disable_input
**       fixed __disable_1,__disable_2,__disable_3,__disable_4 per AR#1783
**       fixed __input_opts per AR#1564
**       fixed __lock_val per AR#1567
**       added __discrete_input_op_select
**       fixed __op_select,__pre_out,__pre_out_1,__pre_out_2,__pre_out_alm per AR#1783
**       fixed __permissive_d
**       added __discrete_input_reset_confirm
**       fixed __reset_confirm,__rev_flow1,__rev_flow2 per AR#1783
**       added __discrete_input_rev_flow
** TAB   added __failure_opts, __preset_in, __totalizer_opts, __xd_range for flow totalizer
** MS   ARs 1992, 2692 -- 2008.10.07
** MS   ARs 2345, 3036, 3641, 2227, 4184 -- 2009.06.15
** MS   ARs 3438, 4233, 4234, 4274, 4437, 5178 -- 2010.06.29
*/
/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "com_tbls.h"


/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __ADV_PARAM,
DEVICE_REVISION __ADV_PARAM_rel_dev_rev,
DD_REVISION     __ADV_PARAM_rel_dd_rev


/*
**********************************************************************
__reset_in_value
**********************************************************************
*/
VARIABLE    __reset_in_value
{
    LABEL           [value_label] ;
    HELP            [value_label] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
       {0, [reset_in_val_0]	},
       {1, [reset_in_val_1]	},
       {2, [reset_in_val_2]	}
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__status_input_r_nd
**********************************************************************
*/
VARIABLE    __status_input_r_nd
{
    LABEL           [status_label] ;
    HELP            [status_input_help] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__status_input_r
**********************************************************************
*/
VARIABLE    __status_input_r
{
    LABEL           [status_label] ;
    HELP            [status_input_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__status_output_r_nd
**********************************************************************
*/
VARIABLE    __status_output_r_nd
{
    LABEL           [status_label] ;
    HELP            [status_output_help] ;
    CLASS           OUTPUT;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__discrete_output_r_nd
**********************************************************************
*/
VARIABLE    __discrete_output_r_nd
{
    LABEL           [discrete_output_label] ;
    HELP            [discrete_output_help] ;
    CLASS           OUTPUT;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_0,
        _DISCRETE_VALUE_1,
        _DISCRETE_VALUE_2,
        _DISCRETE_VALUE_3,
        _DISCRETE_VALUE_4,
        _DISCRETE_VALUE_5,
        _DISCRETE_VALUE_6,
        _DISCRETE_VALUE_7,
        _DISCRETE_VALUE_8,
        _DISCRETE_VALUE_9,
        _DISCRETE_VALUE_10,
        _DISCRETE_VALUE_11,
        _DISCRETE_VALUE_12,
        _DISCRETE_VALUE_13,
        _DISCRETE_VALUE_14,
        _DISCRETE_VALUE_15,
        _DISCRETE_VALUE_16
    }
    HANDLING        READ ;
}

/*
**********************************************************************
__discrete_output
**********************************************************************
*/
VARIABLE    __discrete_output
{
    LABEL           [discrete_output_label] ;
    HELP            [discrete_output_help] ;
    CLASS           OUTPUT & DYNAMIC;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_0,
        _DISCRETE_VALUE_1,
        _DISCRETE_VALUE_2,
        _DISCRETE_VALUE_3,
        _DISCRETE_VALUE_4,
        _DISCRETE_VALUE_5,
        _DISCRETE_VALUE_6,
        _DISCRETE_VALUE_7,
        _DISCRETE_VALUE_8,
        _DISCRETE_VALUE_9,
        _DISCRETE_VALUE_10,
        _DISCRETE_VALUE_11,
        _DISCRETE_VALUE_12,
        _DISCRETE_VALUE_13,
        _DISCRETE_VALUE_14,
        _DISCRETE_VALUE_15,
        _DISCRETE_VALUE_16
    }
    HANDLING        READ & WRITE;
}

/*
**********************************************************************
__float_input_r_nd
**********************************************************************
*/
VARIABLE    __float_input_r_nd
{
    LABEL           [value_label] ;
    HELP            [float_input_help] ;
    CLASS           INPUT ;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__float_input_r
**********************************************************************
*/
VARIABLE    __float_input_r
{
    LABEL           [value_label] ;
    HELP            [float_input_help] ;
    CLASS           INPUT & DYNAMIC;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__disable_input
**********************************************************************
*/
VARIABLE    __disable_input
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
        _DISABLE_VALUE_0,
        _DISABLE_VALUE_1
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__accept_alm
**********************************************************************
*/
RECORD      __accept_alm
{
    LABEL           [accept_alm_label] ;
    HELP            [accept_alm_help] ;
    MEMBERS    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __alm_value ;
    }
}

/*
**********************************************************************
__accept_d
**********************************************************************
*/
VARIABLE    __accept_d
{
    LABEL           [accept_d_label] ;
    HELP            [accept_d_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1) 
    {
        __FF_ACCEPT_D_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__accept_pri
**********************************************************************
*/
VARIABLE    __accept_pri
{
    LABEL           [accept_pri_label] ;
    HELP            [accept_pri_help] ;
    CLASS           CONTAINED & ALARM;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__alm_rate_dn
**********************************************************************
*/
VARIABLE    __alm_rate_dn
{
    LABEL           [alm_rate_dn_label] ;
    HELP            [alm_rate_dn_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__alm_rate_up
**********************************************************************
*/
VARIABLE    __alm_rate_up
{
    LABEL           [alm_rate_up_label] ;
    HELP            [alm_rate_up_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__arith_type
**********************************************************************
*/
VARIABLE    __arith_type
{
    LABEL           [arith_type_label] ;
    HELP            [arith_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_ARITH_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__auto_cycle
**********************************************************************
*/
VARIABLE    __auto_cycle
{
    LABEL           [auto_cycle_label] ;
    HELP            [auto_cycle_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_AUTO_CYCLE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__bias_in_1
**********************************************************************
*/
VARIABLE    __bias_in_1
{
    LABEL           [bias_in_1_label] ;
    HELP            [bias_in_1_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__bias_in_2
**********************************************************************
*/
VARIABLE    __bias_in_2
{
    LABEL           [bias_in_2_label] ;
    HELP            [bias_in_2_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__bias_in_3
**********************************************************************
*/
VARIABLE    __bias_in_3
{
    LABEL           [bias_in_3_label] ;
    HELP            [bias_in_3_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__binary_cl
**********************************************************************
*/
RECORD      __binary_cl
{
    LABEL           [binary_cl_label] ;
    HELP            [binary_cl_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__binary_op
**********************************************************************
*/
RECORD      __binary_op
{
    LABEL           [binary_op_label] ;
    HELP            [binary_op_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__bkcal_in_1
**********************************************************************
*/
RECORD      __bkcal_in_1
{
    LABEL           [bkcal_in_1_label] ;
    HELP            [bkcal_in_1_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__bkcal_in_2
**********************************************************************
*/
RECORD      __bkcal_in_2
{
    LABEL           [bkcal_in_2_label] ;
    HELP            [bkcal_in_2_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__bkcal_in_d
**********************************************************************
*/
RECORD      __bkcal_in_d
{
    LABEL           [bkcal_in_d_label] ;
    HELP            [bkcal_in_d_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__calc_errs
**********************************************************************
*/
VARIABLE    __calc_errs
{
    LABEL           [calc_errs_label] ;
    HELP            [calc_errs_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2) 
    {
        __FF_CALC_ERRS_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__cfm_act1_time
**********************************************************************
*/
VARIABLE    __cfm_act1_time
{
    LABEL           [cfm_act1_time_label] ;
    HELP            [cfm_act1_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__cfm_act2_time
**********************************************************************
*/
VARIABLE    __cfm_act2_time
{
    LABEL           [cfm_act2_time_label] ;
    HELP            [cfm_act2_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__cfm_pass_time
**********************************************************************
*/
VARIABLE    __cfm_pass_time
{
    LABEL           [cfm_pass_time_label] ;
    HELP            [cfm_pass_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__checkback
**********************************************************************
*/
VARIABLE    __checkback
{
    LABEL           [checkback_label] ;
    HELP            [checkback_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2) 
    {
        __FF_CHECKBACK_ENUMS
    }
    HANDLING        READ;
}

/*
**********************************************************************
__clock_per
**********************************************************************
*/
VARIABLE    __clock_per
{
    LABEL           [clock_per_label] ;
    HELP            [clock_per_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__comb_type
**********************************************************************
*/
VARIABLE    __comb_type
{
    LABEL           [comb_type_label] ;
    HELP            [comb_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_COMB_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__comp_hi_lim
**********************************************************************
*/
VARIABLE    __comp_hi_lim
{
    LABEL           [comp_hi_lim_label] ;
    HELP            [comp_hi_lim_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__comp_lo_lim
**********************************************************************
*/
VARIABLE    __comp_lo_lim
{
    LABEL           [comp_lo_lim_label] ;
    HELP            [comp_lo_lim_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__cond_time
**********************************************************************
*/
VARIABLE    __cond_time
{
    LABEL           [cond_time_label] ;
    HELP            [cond_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__cond_type
**********************************************************************
*/
VARIABLE    __cond_type
{
    LABEL           [cond_type_label] ;
    HELP            [cond_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_COND_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__crack_time
**********************************************************************
*/
VARIABLE    __crack_time
{
    LABEL           [crack_time_label] ;
    HELP            [crack_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__crack_timer
**********************************************************************
*/
VARIABLE    __crack_timer
{
    LABEL           [crack_timer_label] ;
    HELP            [crack_timer_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ;
}

/*
**********************************************************************
__curve_x
**********************************************************************
*/
VARIABLE    __curve_x_elem
{
    LABEL           [curve_x_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __curve_x
{
    LABEL               [curve_x_label] ;
    HELP                [curve_x_help] ;
    TYPE                __curve_x_elem ;
    NUMBER_OF_ELEMENTS  21 ;
}

/*
**********************************************************************
__curve_y
**********************************************************************
*/
VARIABLE    __curve_y_elem
{
    LABEL           [curve_y_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __curve_y
{
    LABEL               [curve_y_label] ;
    HELP                [curve_y_help] ;
    TYPE                __curve_y_elem ;
    NUMBER_OF_ELEMENTS  21 ;
}

/*
**********************************************************************
__dc_state
**********************************************************************
*/
VARIABLE    __dc_state
{
    LABEL           [dc_state_label] ;
    HELP            [dc_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_DC_STATE_ENUMS
    }
    HANDLING        READ;
}

/*
**********************************************************************
__dead_band
**********************************************************************
*/
VARIABLE    __dead_band
{
    LABEL           [dead_band_label] ;
    HELP            [dead_band_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__dead_time
**********************************************************************
*/
RECORD      __dead_time
{
    LABEL           [dead_time_label] ;
    HELP            [dead_time_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__delay_time
**********************************************************************
*/
VARIABLE    __delay_time
{
    LABEL           [delay_time_label] ;
    HELP            [delay_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__delay_timer
**********************************************************************
*/
VARIABLE    __delay_timer
{
    LABEL           [delay_timer_label] ;
    HELP            [delay_timer_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ;
}

/*
**********************************************************************
__device_opts
**********************************************************************
*/
VARIABLE    __device_opts
{
    LABEL           [device_opts_label] ;
    HELP            [device_opts_help] ;
    CLASS           CONTAINED;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__disable_1
**********************************************************************
*/
RECORD      __disable_1
{
    LABEL           [disable_1_label] ;
    HELP            [disable_1_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __disable_input ;
    }
}

/*
**********************************************************************
__disable_2
**********************************************************************
*/
RECORD      __disable_2
{
    LABEL           [disable_2_label] ;
    HELP            [disable_2_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __disable_input ;
    }
}

/*
**********************************************************************
__disable_3
**********************************************************************
*/
RECORD      __disable_3
{
    LABEL           [disable_3_label] ;
    HELP            [disable_3_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __disable_input ;
    }
}

/*
**********************************************************************
__disable_4
**********************************************************************
*/
RECORD      __disable_4
{
    LABEL           [disable_4_label] ;
    HELP            [disable_4_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __disable_input ;
    }
}

/*
**********************************************************************
__disc_cond
**********************************************************************
*/
VARIABLE    __disc_cond
{
    LABEL           [disc_cond_label] ;
    HELP            [disc_cond_help] ;
    CLASS           CONTAINED & ALARM;
    TYPE            ENUMERATED (1) 
    {
        __FF_DISC_COND_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__en_close
**********************************************************************
*/
RECORD      __en_close
{
    LABEL           [en_close_label] ;
    HELP            [en_close_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__en_open
**********************************************************************
*/
RECORD      __en_open
{
    LABEL           [en_open_label] ;
    HELP            [en_open_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__err_latch
**********************************************************************
*/
VARIABLE    __err_latch
{
    LABEL           [err_latch_label] ;
    HELP            [err_latch_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_ERR_LATCH_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__expand_dn
**********************************************************************
*/
VARIABLE    __expand_dn
{
    LABEL           [expand_dn_label] ;
    HELP            [expand_dn_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ;
}

/*
**********************************************************************
__expand_up
**********************************************************************
*/
VARIABLE    __expand_up
{
    LABEL           [expand_up_label] ;
    HELP            [expand_up_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ;
}

/*
**********************************************************************
__fail
**********************************************************************
*/
VARIABLE    __fail
{
    LABEL           [fail_label] ;
    HELP            [fail_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2) 
    {
        __FF_FAIL_ENUMS
    }
    HANDLING        READ;
}

/*
**********************************************************************
__fail_alm
**********************************************************************
*/
RECORD      __fail_alm
{
    LABEL           [fail_alm_label] ;
    HELP            [fail_alm_help] ;
    MEMBERS    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __alm_value ;
    }
}

/*
**********************************************************************
__fail_pri
**********************************************************************
*/
VARIABLE    __fail_pri
{
    LABEL           [fail_pri_label] ;
    HELP            [fail_pri_help] ;
    CLASS           CONTAINED & ALARM;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__failure_opts
**********************************************************************
*/
VARIABLE    __failure_opts
{
    LABEL           [failure_opts_label] ;
    HELP            [failure_opts_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1)
    {
        { 0,    [failure_opt_run],         [failure_opt_run_help]           },
        { 1,    [failure_opt_hold],        [failure_opt_hold_help]          },
        { 2,    [failure_opt_last_val],    [failure_opt_last_val_help]      }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__follow
**********************************************************************
*/
RECORD      __follow
{
    LABEL           [follow_label] ;
    HELP            [follow_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__fsafe_time
**********************************************************************
*/
VARIABLE    __fsafe_time
{
    LABEL           [fsafe_time_label] ;
    HELP            [fsafe_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__fsafe_val
**********************************************************************
*/
VARIABLE    __fsafe_val
{
    LABEL           [fsafe_val_label] ;
    HELP            [fsafe_val_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__fsafe_val_d
**********************************************************************
*/
VARIABLE    __fsafe_val_d
{
    LABEL           [fsafe_val_d_label] ;
    HELP            [fsafe_val_d_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__gain_in_1
**********************************************************************
*/
VARIABLE    __gain_in_1
{
    LABEL           [gain_in_1_label] ;
    HELP            [gain_in_1_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__gain_in_2
**********************************************************************
*/
VARIABLE    __gain_in_2
{
    LABEL           [gain_in_2_label] ;
    HELP            [gain_in_2_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__gain_in_3
**********************************************************************
*/
VARIABLE    __gain_in_3
{
    LABEL           [gain_in_3_label] ;
    HELP            [gain_in_3_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__good_lim
**********************************************************************
*/
VARIABLE    __good_lim
{
    LABEL           [good_lim_label] ;
    HELP            [good_lim_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__hi_bias
**********************************************************************
*/
VARIABLE    __hi_bias
{
    LABEL           [hi_bias_label] ;
    HELP            [hi_bias_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__hi_gain
**********************************************************************
*/
VARIABLE    __hi_gain
{
    LABEL           [hi_gain_label] ;
    HELP            [hi_gain_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__hi_hi_bias
**********************************************************************
*/
VARIABLE    __hi_hi_bias
{
    LABEL           [hi_hi_bias_label] ;
    HELP            [hi_hi_bias_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__hi_hi_limx
**********************************************************************
*/
VARIABLE    __hi_hi_limx
{
    LABEL           [hi_hi_limx_label] ;
    HELP            [hi_hi_limx_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__hi_limx
**********************************************************************
*/
VARIABLE    __hi_limx
{
    LABEL           [hi_limx_label] ;
    HELP            [hi_limx_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__hysteresis
**********************************************************************
*/
VARIABLE    __hysteresis
{
    LABEL           [hysteresis_label] ;
    HELP            [hysteresis_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__hystval
**********************************************************************
*/
VARIABLE    __hystval
{
    LABEL           [hystval_label] ;
    HELP            [hystval_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__ignore
**********************************************************************
*/
VARIABLE    __ignore
{
    LABEL           [ignore_label] ;
    HELP            [ignore_help] ;
    CLASS           CONTAINED;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__ignore_alm
**********************************************************************
*/
RECORD      __ignore_alm
{
    LABEL           [ignore_alm_label] ;
    HELP            [ignore_alm_help] ;
    MEMBERS    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __alm_value ;
    }
}

/*
**********************************************************************
__ignore_pri
**********************************************************************
*/
VARIABLE    __ignore_pri
{
    LABEL           [ignore_pri_label] ;
    HELP            [ignore_pri_help] ;
    CLASS           CONTAINED & ALARM;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__ignore_time
**********************************************************************
*/
VARIABLE    __ignore_time
{
    LABEL           [ignore_time_label] ;
    HELP            [ignore_time_help] ;
    CLASS           CONTAINED & ALARM;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__in_array
**********************************************************************
*/
VARIABLE    __in_array_elem
{
    LABEL           [in_array_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __in_array
{
    LABEL               [in_array_label] ;
    HELP                [in_array_help] ;
    TYPE                __in_array_elem ;
    NUMBER_OF_ELEMENTS  4 ;
}

/*
**********************************************************************
__in_d
**********************************************************************
*/
RECORD      __in_d
{
    LABEL           [in_d_label] ;
    HELP            [in_d_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d9
**********************************************************************
*/
RECORD      __in_d9
{
    LABEL           [in_d9_label] ;
    HELP            [in_d9_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d10
**********************************************************************
*/
RECORD      __in_d10
{
    LABEL           [in_d10_label] ;
    HELP            [in_d10_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d11
**********************************************************************
*/
RECORD      __in_d11
{
    LABEL           [in_d11_label] ;
    HELP            [in_d11_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d12
**********************************************************************
*/
RECORD      __in_d12
{
    LABEL           [in_d12_label] ;
    HELP            [in_d12_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d13
**********************************************************************
*/
RECORD      __in_d13
{
    LABEL           [in_d13_label] ;
    HELP            [in_d13_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d14
**********************************************************************
*/
RECORD      __in_d14
{
    LABEL           [in_d14_label] ;
    HELP            [in_d14_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d15
**********************************************************************
*/
RECORD      __in_d15
{
    LABEL           [in_d15_label] ;
    HELP            [in_d15_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_d16
**********************************************************************
*/
RECORD      __in_d16
{
    LABEL           [in_d16_label] ;
    HELP            [in_d16_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
}

/*
**********************************************************************
__in_lo
**********************************************************************
*/
RECORD      __in_lo
{
    LABEL           [in_lo_label] ;
    HELP            [in_lo_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__init_val_1
**********************************************************************
*/
RECORD      __init_val_1
{
    LABEL           [init_val_1_label] ;
    HELP            [init_val_1_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__init_val_2
**********************************************************************
*/
RECORD      __init_val_2
{
    LABEL           [init_val_2_label] ;
    HELP            [init_val_2_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__init_val_3
**********************************************************************
*/
RECORD      __init_val_3
{
    LABEL           [init_val_3_label] ;
    HELP            [init_val_3_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__init_val_4
**********************************************************************
*/
RECORD      __init_val_4
{
    LABEL           [init_val_4_label] ;
    HELP            [init_val_4_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__init_val_d1
**********************************************************************
*/
RECORD      __init_val_d1
{
    LABEL           [init_val_d1_label] ;
    HELP            [init_val_d1_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__init_val_d2
**********************************************************************
*/
RECORD      __init_val_d2
{
    LABEL           [init_val_d2_label] ;
    HELP            [init_val_d2_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__init_val_d3
**********************************************************************
*/
RECORD      __init_val_d3
{
    LABEL           [init_val_d3_label] ;
    HELP            [init_val_d3_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__init_val_d4
**********************************************************************
*/
RECORD      __init_val_d4
{
    LABEL           [init_val_d4_label] ;
    HELP            [init_val_d4_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__input_opts
**********************************************************************
*/
VARIABLE    __input_opts
{
    LABEL           [input_opts_label] ;
    HELP            [input_opts_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2)
    {
          __FF_INPUT_OPTS_ENUMS
    }
    
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__inst_err_no
**********************************************************************
*/
VARIABLE    __inst_err_no
{
    LABEL           [inst_err_no_label] ;
    HELP            [inst_err_no_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__inst_ex_lim
**********************************************************************
*/
VARIABLE    __inst_ex_lim
{
    LABEL           [inst_ex_lim_label] ;
    HELP            [inst_ex_lim_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__inst_list1
**********************************************************************
*/
VARIABLE    __inst_list1_elem
{
    LABEL           [inst_list1_elem_label] ;
    TYPE            BITSTRING (32) ;
    CLASS           CONTAINED ;
}

ARRAY    __inst_list1
{
    LABEL               [inst_list1_label] ;
    HELP                [inst_list1_help] ;
    TYPE                __inst_list1_elem ;
    NUMBER_OF_ELEMENTS  50 ;
}

/*
**********************************************************************
__integ_opts
**********************************************************************
*/
VARIABLE    __integ_opts
{
    LABEL           [integ_opts_label] ;
    HELP            [integ_opts_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2) 
    {
        __FF_INTEG_OPTS_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__integ_type
**********************************************************************
*/
VARIABLE    __integ_type
{
    LABEL           [integ_type_label] ;
    HELP            [integ_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_INTEG_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__interlock_d
**********************************************************************
*/
RECORD      __interlock_d
{
    LABEL           [interlock_d_label] ;
    HELP            [interlock_d_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__invert_opts
**********************************************************************
*/
VARIABLE    __invert_opts
{
    LABEL           [invert_opts_label] ;
    HELP            [invert_opts_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2) 
    {
        __FF_INVERT_OPTS_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_1
**********************************************************************
*/
RECORD      __iv_1
{
    LABEL           [iv_1_label] ;
    HELP            [iv_1_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__iv_2
**********************************************************************
*/
RECORD      __iv_2
{
    LABEL           [iv_2_label] ;
    HELP            [iv_2_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__iv_3
**********************************************************************
*/
RECORD      __iv_3
{
    LABEL           [iv_3_label] ;
    HELP            [iv_3_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__iv_4
**********************************************************************
*/
RECORD      __iv_4
{
    LABEL           [iv_4_label] ;
    HELP            [iv_4_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__iv_d1
**********************************************************************
*/
RECORD      __iv_d1
{
    LABEL           [iv_d1_label] ;
    HELP            [iv_d1_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__iv_d2
**********************************************************************
*/
RECORD      __iv_d2
{
    LABEL           [iv_d2_label] ;
    HELP            [iv_d2_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__iv_d3
**********************************************************************
*/
RECORD      __iv_d3
{
    LABEL           [iv_d3_label] ;
    HELP            [iv_d3_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__iv_d4
**********************************************************************
*/
RECORD      __iv_d4
{
    LABEL           [iv_d4_label] ;
    HELP            [iv_d4_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__iv_desc_1
**********************************************************************
*/
VARIABLE    __iv_desc_1
{
    LABEL           [iv_desc_1_label] ;
    HELP            [iv_desc_1_help] ;
    CLASS           CONTAINED;
    TYPE            VISIBLE (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_desc_2
**********************************************************************
*/
VARIABLE    __iv_desc_2
{
    LABEL           [iv_desc_2_label] ;
    HELP            [iv_desc_2_help] ;
    CLASS           CONTAINED;
    TYPE            VISIBLE (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_desc_3
**********************************************************************
*/
VARIABLE    __iv_desc_3
{
    LABEL           [iv_desc_3_label] ;
    HELP            [iv_desc_3_help] ;
    CLASS           CONTAINED;
    TYPE            VISIBLE (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_desc_4
**********************************************************************
*/
VARIABLE    __iv_desc_4
{
    LABEL           [iv_desc_4_label] ;
    HELP            [iv_desc_4_help] ;
    CLASS           CONTAINED;
    TYPE            VISIBLE (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_scale_1
**********************************************************************
*/
RECORD      __iv_scale_1
{
    LABEL           [iv_scale_1_label] ;
    HELP            [iv_scale_1_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__iv_scale_2
**********************************************************************
*/
RECORD      __iv_scale_2
{
    LABEL           [iv_scale_2_label] ;
    HELP            [iv_scale_2_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__iv_scale_3
**********************************************************************
*/
RECORD      __iv_scale_3
{
    LABEL           [iv_scale_3_label] ;
    HELP            [iv_scale_3_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__iv_scale_4
**********************************************************************
*/
RECORD      __iv_scale_4
{
    LABEL           [iv_scale_4_label] ;
    HELP            [iv_scale_4_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__iv_state_1
**********************************************************************
*/
VARIABLE    __iv_state_1
{
    LABEL           [iv_state_1_label] ;
    HELP            [iv_state_1_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_state_2
**********************************************************************
*/
VARIABLE    __iv_state_2
{
    LABEL           [iv_state_2_label] ;
    HELP            [iv_state_2_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_state_3
**********************************************************************
*/
VARIABLE    __iv_state_3
{
    LABEL           [iv_state_3_label] ;
    HELP            [iv_state_3_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__iv_state_4
**********************************************************************
*/
VARIABLE    __iv_state_4
{
    LABEL           [iv_state_4_label] ;
    HELP            [iv_state_4_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__jog_time
**********************************************************************
*/
VARIABLE    __jog_time
{
    LABEL           [jog_time_label] ;
    HELP            [jog_time_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lag_time
**********************************************************************
*/
VARIABLE    __lag_time
{
    LABEL           [lag_time_label] ;
    HELP            [lag_time_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lead_time
**********************************************************************
*/
VARIABLE    __lead_time
{
    LABEL           [lead_time_label] ;
    HELP            [lead_time_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lo_bias
**********************************************************************
*/
VARIABLE    __lo_bias
{
    LABEL           [lo_bias_label] ;
    HELP            [lo_bias_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lo_gain
**********************************************************************
*/
VARIABLE    __lo_gain
{
    LABEL           [lo_gain_label] ;
    HELP            [lo_gain_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lo_limx
**********************************************************************
*/
VARIABLE    __lo_limx
{
    LABEL           [lo_limx_label] ;
    HELP            [lo_limx_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__lo_lo_bias
**********************************************************************
*/
VARIABLE    __lo_lo_bias
{
    LABEL           [lo_lo_bias_label] ;
    HELP            [lo_lo_bias_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__lo_lo_limx
**********************************************************************
*/
VARIABLE    __lo_lo_limx
{
    LABEL           [lo_lo_limx_label] ;
    HELP            [lo_lo_limx_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ ;
}

/*
**********************************************************************
__lockval
**********************************************************************
*/
VARIABLE    __lockval
{
    LABEL           [lockval_label] ;
    HELP            [lockval_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        _UNINITIALIZED_VALUE,
        __FF_LOCKVAL_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__min_good
**********************************************************************
*/
VARIABLE    __min_good
{
    LABEL           [min_good_label] ;
    HELP            [min_good_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__n_reset
**********************************************************************
*/
VARIABLE    __n_reset
{
    LABEL           [n_reset_label] ;
    HELP            [n_reset_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__n_start
**********************************************************************
*/
VARIABLE    __n_start
{
    LABEL           [n_start_label] ;
    HELP            [n_start_help] ;
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__op_cmd_cxo
**********************************************************************
*/
VARIABLE    __op_cmd_cxo
{
    LABEL           [op_cmd_cxo_label] ;
    HELP            [op_cmd_cxo_help] ;
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2) 
    {
        __FF_OP_CMD_CXO_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__op_cmd_int
**********************************************************************
*/
VARIABLE    __op_cmd_int
{
    LABEL           [op_cmd_int_label] ;
    HELP            [op_cmd_int_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1) 
    {
        __FF_OP_CMD_INT_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__op_cmd_spg
**********************************************************************
*/
VARIABLE    __op_cmd_spg
{
    LABEL           [op_cmd_spg_label] ;
    HELP            [op_cmd_spg_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1) 
    {
        __FF_OP_CMD_SPG_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__discrete_input_op_select
**********************************************************************
*/
VARIABLE    __discrete_input_op_select
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_0,
        _DISCRETE_VALUE_1,
        _DISCRETE_VALUE_2,
        _DISCRETE_VALUE_3,
        _DISCRETE_VALUE_4
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_input_op
**********************************************************************
*/
VARIABLE    __status_input_op
{
    LABEL           [status_label] ;
    HELP            [status_input_help] ;
    CLASS           INPUT & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__op_select
**********************************************************************
*/
RECORD      __op_select
{
    LABEL           [op_select_label] ;
    HELP            [op_select_help] ;
    MEMBERS    {
        STATUS,  __status_input_op ;
        VALUE,   __discrete_input_op_select ;
    }
}

/*
**********************************************************************
__out_1_range
**********************************************************************
*/
RECORD      __out_1_range
{
    LABEL           [out_1_range_label] ;
    HELP            [out_1_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__out_1_state
**********************************************************************
*/
VARIABLE    __out_1_state
{
    LABEL           [out_1_state_label] ;
    HELP            [out_1_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2) 
    {
        __FF_OUT_1_STATE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_1_units
**********************************************************************
*/
VARIABLE    __out_1_units
{
    LABEL           [out_1_units_label] ;
    HELP            [out_1_units_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
        __UNITS_CODES2
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_2_range
**********************************************************************
*/
RECORD      __out_2_range
{
    LABEL           [out_2_range_label] ;
    HELP            [out_2_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__out_2_state
**********************************************************************
*/
VARIABLE    __out_2_state
{
    LABEL           [out_2_state_label] ;
    HELP            [out_2_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2) 
    {
        __FF_OUT_2_STATE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_2_units
**********************************************************************
*/
VARIABLE    __out_2_units
{
    LABEL           [out_2_units_label] ;
    HELP            [out_2_units_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
        __UNITS_CODES2
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_3_state
**********************************************************************
*/
VARIABLE    __out_3_state
{
    LABEL           [out_3_state_label] ;
    HELP            [out_3_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2) 
    {
        __FF_OUT_3_STATE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_4_state
**********************************************************************
*/
VARIABLE    __out_4_state
{
    LABEL           [out_4_state_label] ;
    HELP            [out_4_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2) 
    {
        __FF_OUT_4_STATE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_accum
**********************************************************************
*/
RECORD      __out_accum
{
    LABEL           [out_accum_label] ;
    HELP            [out_accum_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__out_alm
**********************************************************************
*/
RECORD      __out_alm
{
    LABEL           [out_alm_label] ;
    HELP            [out_alm_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__out_alm_sum
**********************************************************************
*/
VARIABLE    __out_alm_sum
{
    LABEL           [out_alm_sum_label] ;
    HELP            [out_alm_sum_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_OUT_ALM_SUM_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__out_array
**********************************************************************
*/
VARIABLE    __out_array_elem
{
    LABEL           [out_array_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __out_array
{
    LABEL               [out_array_label] ;
    HELP                [out_array_help] ;
    TYPE                __out_array_elem ;
    NUMBER_OF_ELEMENTS  4 ;
}

/*
**********************************************************************
__out_exp
**********************************************************************
*/
RECORD      __out_exp
{
    LABEL           [out_exp_label] ;
    HELP            [out_exp_help] ;
    MEMBERS    {
        STATUS,  __status_output_r_nd ;
        VALUE,   __float_output_nd ;
    }
}

/*
**********************************************************************
__out_ptrip
**********************************************************************
*/
RECORD      __out_ptrip
{
    LABEL           [out_ptrip_label] ;
    HELP            [out_ptrip_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __on_off_output_nd ;
    }
}

/*
**********************************************************************
__out_range
**********************************************************************
*/
RECORD      __out_range
{
    LABEL           [out_range_label] ;
    HELP            [out_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__out_rem
**********************************************************************
*/
RECORD      __out_rem
{
    LABEL           [out_rem_label] ;
    HELP            [out_rem_help] ;
    MEMBERS    {
        STATUS,  __status_output_r_nd ;
        VALUE,   __float_output_nd ;
    }
}

/*
**********************************************************************
__out_trip
**********************************************************************
*/
RECORD      __out_trip
{
    LABEL           [out_trip_label] ;
    HELP            [out_trip_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __on_off_output_nd ;
    }
}

/*
**********************************************************************
__outage_lim
**********************************************************************
*/
VARIABLE    __outage_lim
{
    LABEL           [outage_lim_label] ;
    HELP            [outage_lim_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__pause
**********************************************************************
*/
RECORD      __pause
{
    LABEL           [pause_label] ;
    HELP            [pause_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__pause_cause
**********************************************************************
*/
VARIABLE    __pause_cause
{
    LABEL           [pause_cause_label] ;
    HELP            [pause_cause_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_PAUSE_CAUSE_ENUMS
    }
    HANDLING        READ;
}

/*
**********************************************************************
__pct_incl
**********************************************************************
*/
VARIABLE    __pct_incl
{
    LABEL           [pct_incl_label] ;
    HELP            [pct_incl_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ;
}

/*
**********************************************************************
__permissive_d
**********************************************************************
*/
RECORD      __permissive_d
{
    LABEL           [permissive_d_label] ;
    HELP            [permissive_d_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __on_off_output_nd ;
    }
}

/*
**********************************************************************
__pre_out
**********************************************************************
*/
RECORD      __pre_out
{
    LABEL           [pre_out_label] ;
    HELP            [pre_out_help] ;
    MEMBERS    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
}

/*
**********************************************************************
__pre_out_1
**********************************************************************
*/
RECORD      __pre_out_1
{
    LABEL           [pre_out_1_label] ;
    HELP            [pre_out_1_help] ;
    MEMBERS    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
}

/*
**********************************************************************
__pre_out_2
**********************************************************************
*/
RECORD      __pre_out_2
{
    LABEL           [pre_out_2_label] ;
    HELP            [pre_out_2_help] ;
    MEMBERS    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
}

/*
**********************************************************************
__pre_out_alm
**********************************************************************
*/
RECORD      __pre_out_alm
{
    LABEL           [pre_out_alm_label] ;
    HELP            [pre_out_alm_help] ;
    MEMBERS    {
        STATUS,  __status_contained_r ;
        VALUE,   __on_off_contained_r ;
    }
}

/*
**********************************************************************
__pre_out_d
**********************************************************************
*/
RECORD      __pre_out_d
{
    LABEL           [pre_out_d_label] ;
    HELP            [pre_out_d_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__pre_out_d1
**********************************************************************
*/
RECORD      __pre_out_d1
{
    LABEL           [pre_out_d1_label] ;
    HELP            [pre_out_d1_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__pre_out_d2
**********************************************************************
*/
RECORD      __pre_out_d2
{
    LABEL           [pre_out_d2_label] ;
    HELP            [pre_out_d2_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__pre_out_d3
**********************************************************************
*/
RECORD      __pre_out_d3
{
    LABEL           [pre_out_d3_label] ;
    HELP            [pre_out_d3_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__pre_out_d4
**********************************************************************
*/
RECORD      __pre_out_d4
{
    LABEL           [pre_out_d4_label] ;
    HELP            [pre_out_d4_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__preset_in 
**********************************************************************
*/
RECORD      __preset_in
{
    LABEL           [preset_in_label] ;
    HELP            [preset_in_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__pre_trip
**********************************************************************
*/
VARIABLE    __pre_trip
{
    LABEL           [pre_trip_label] ;
    HELP            [pre_trip_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__prop_lims
**********************************************************************
*/
VARIABLE    __prop_lims
{
    LABEL           [prop_lims_label] ;
    HELP            [prop_lims_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_PROP_LIMS_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__psp
**********************************************************************
*/
RECORD      __psp
{
    LABEL           [psp_label] ;
    HELP            [psp_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
}

/*
**********************************************************************
__pulse_dur
**********************************************************************
*/
VARIABLE    __pulse_dur
{
    LABEL           [pulse_dur_label] ;
    HELP            [pulse_dur_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__pulse_val
**********************************************************************
*/
VARIABLE    __pulse_val
{
    LABEL           [pulse_val_label] ;
    HELP            [pulse_val_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__pulse_val1
**********************************************************************
*/
VARIABLE    __pulse_val1
{
    LABEL           [pulse_val1_label] ;
    HELP            [pulse_val1_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__pulse_val2
**********************************************************************
*/
VARIABLE    __pulse_val2
{
    LABEL           [pulse_val2_label] ;
    HELP            [pulse_val2_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__quies_opt
**********************************************************************
*/
VARIABLE    __quies_opt
{
    LABEL           [quies_opt_label] ;
    HELP            [quies_opt_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_QUIES_OPT_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__range_hi
**********************************************************************
*/
VARIABLE    __range_hi
{
    LABEL           [range_hi_label] ;
    HELP            [range_hi_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__range_lo
**********************************************************************
*/
VARIABLE    __range_lo
{
    LABEL           [range_lo_label] ;
    HELP            [range_lo_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__discrete_input_reset_confirm
**********************************************************************
*/
VARIABLE    __discrete_input_reset_confirm
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_0,
        _DISCRETE_VALUE_CONFIRM
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reset_confirm
**********************************************************************
*/
RECORD      __reset_confirm
{
    LABEL           [reset_confirm_label] ;
    HELP            [reset_confirm_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_reset_confirm ;
    }
}

/*
**********************************************************************
__reset_d
**********************************************************************
*/
VARIABLE    __reset_d
{
    LABEL           [reset_d_label] ;
    HELP            [reset_d_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_RESET_D_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__reset_in
**********************************************************************
*/
RECORD      __reset_in
{
    LABEL           [reset_in_label] ;
    HELP            [reset_in_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
     	VALUE,   __reset_in_value ;
    }
}

/*
**********************************************************************
__restart_time
**********************************************************************
*/
VARIABLE    __restart_time
{
    LABEL           [restart_time_label] ;
    HELP            [restart_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__discrete_input_rev_flow
**********************************************************************
*/
VARIABLE    __discrete_input_rev_flow
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_FORWARD,
        _DISCRETE_VALUE_REVERSE
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__rev_flow1
**********************************************************************
*/
RECORD      __rev_flow1
{
    LABEL           [rev_flow1_label] ;
    HELP            [rev_flow1_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_rev_flow ;
    }
}

/*
**********************************************************************
__rev_flow2
**********************************************************************
*/
RECORD      __rev_flow2
{
    LABEL           [rev_flow2_label] ;
    HELP            [rev_flow2_help] ;
    MEMBERS    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_rev_flow ;
    }
}

/*
**********************************************************************
__rtotal
**********************************************************************
*/
VARIABLE    __rtotal
{
    LABEL           [rtotal_label] ;
    HELP            [rtotal_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__safeguard_cl
**********************************************************************
*/
RECORD      __safeguard_cl
{
    LABEL           [safeguard_cl_label] ;
    HELP            [safeguard_cl_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__safeguard_op
**********************************************************************
*/
RECORD      __safeguard_op
{
    LABEL           [safeguard_op_label] ;
    HELP            [safeguard_op_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__select_type
**********************************************************************
*/
VARIABLE    __select_type
{
    LABEL           [select_type_label] ;
    HELP            [select_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_SELECT_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__selected
**********************************************************************
*/
RECORD      __selected
{
    LABEL           [selected_label] ;
    HELP            [selected_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__shutdown_d
**********************************************************************
*/
RECORD      __shutdown_d
{
    LABEL           [shutdown_d_label] ;
    HELP            [shutdown_d_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__simulate_p
**********************************************************************
*/
RECORD      __simulate_p
{
    LABEL           [simulate_p_label] ;
    HELP            [simulate_p_help] ;
    MEMBERS    {
        SIMULATE_STATUS,     __simulate_status ;
        SIMULATE_VALUE,      __simulate_value ;
        TRANSDUCER_STATUS,   __transducer_status ;
        TRANSDUCER_VALUE,    __transducer_value ;
        ENABLE_DISABLE,      __enable_disable ;
    }
}

/*
**********************************************************************
__spg_state
**********************************************************************
*/
VARIABLE    __spg_state
{
    LABEL           [spg_state_label] ;
    HELP            [spg_state_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_SPG_STATE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__srtotal
**********************************************************************
*/
VARIABLE    __srtotal
{
    LABEL           [srtotal_label] ;
    HELP            [srtotal_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ;
}

/*
**********************************************************************
__ssp
**********************************************************************
*/
VARIABLE    __ssp
{
    LABEL           [ssp_label] ;
    HELP            [ssp_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ;
}

/*
**********************************************************************
__start
**********************************************************************
*/
RECORD      __start
{
    LABEL           [start_label] ;
    HELP            [start_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__start_type
**********************************************************************
*/
VARIABLE    __start_type
{
    LABEL           [start_type_label] ;
    HELP            [start_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_START_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__start_val
**********************************************************************
*/
VARIABLE    __start_val_elem
{
    LABEL           [start_val_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __start_val
{
    LABEL               [start_val_label] ;
    HELP                [start_val_help] ;
    TYPE                __start_val_elem ;
    NUMBER_OF_ELEMENTS  11 ;
}

/*
**********************************************************************
__step_posn
**********************************************************************
*/
RECORD      __step_posn
{
    LABEL           [step_posn_label] ;
    HELP            [step_posn_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
}

/*
**********************************************************************
__stotal
**********************************************************************
*/
VARIABLE    __stotal
{
    LABEL           [stotal_label] ;
    HELP            [stotal_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ;
}

/*
**********************************************************************
__swap_2
**********************************************************************
*/
VARIABLE    __swap_2
{
    LABEL           [swap_2_label] ;
    HELP            [swap_2_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_SWAP_2_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__temp_1
**********************************************************************
*/
RECORD      __temp_1
{
    LABEL           [temp_1_label] ;
    HELP            [temp_1_help] ;
    MEMBERS    {
        STATUS,  __status_input_r ;
        VALUE,   __float_input_r ;
    }
}

/*
**********************************************************************
__temp_2
**********************************************************************
*/
RECORD      __temp_2
{
    LABEL           [temp_2_label] ;
    HELP            [temp_2_help] ;
    MEMBERS    {
        STATUS,  __status_input_r ;
        VALUE,   __float_input_r ;
    }
}

/*
**********************************************************************
__temp_3
**********************************************************************
*/
RECORD      __temp_3
{
    LABEL           [temp_3_label] ;
    HELP            [temp_3_help] ;
    MEMBERS    {
        STATUS,  __status_input_r ;
        VALUE,   __float_input_r ;
    }
}

/*
**********************************************************************
__temp_4
**********************************************************************
*/
RECORD      __temp_4
{
    LABEL           [temp_4_label] ;
    HELP            [temp_4_help] ;
    MEMBERS    {
        STATUS,  __status_input_r ;
        VALUE,   __float_input_r ;
    }
}

/*
**********************************************************************
__temp_d1
**********************************************************************
*/
RECORD      __temp_d1
{
    LABEL           [temp_d1_label] ;
    HELP            [temp_d1_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d2
**********************************************************************
*/
RECORD      __temp_d2
{
    LABEL           [temp_d2_label] ;
    HELP            [temp_d2_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d3
**********************************************************************
*/
RECORD      __temp_d3
{
    LABEL           [temp_d3_label] ;
    HELP            [temp_d3_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d4
**********************************************************************
*/
RECORD      __temp_d4
{
    LABEL           [temp_d4_label] ;
    HELP            [temp_d4_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d5
**********************************************************************
*/
RECORD      __temp_d5
{
    LABEL           [temp_d5_label] ;
    HELP            [temp_d5_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d6
**********************************************************************
*/
RECORD      __temp_d6
{
    LABEL           [temp_d6_label] ;
    HELP            [temp_d6_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d7
**********************************************************************
*/
RECORD      __temp_d7
{
    LABEL           [temp_d7_label] ;
    HELP            [temp_d7_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__temp_d8
**********************************************************************
*/
RECORD      __temp_d8
{
    LABEL           [temp_d8_label] ;
    HELP            [temp_d8_help] ;
    MEMBERS    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
}

/*
**********************************************************************
__time_duration
**********************************************************************
*/
VARIABLE    __time_duration_elem
{
    LABEL           [time_duration_elem_label] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED ;
}

ARRAY    __time_duration
{
    LABEL               [time_duration_label] ;
    HELP                [time_duration_help] ;
    TYPE                __time_duration_elem ;
    NUMBER_OF_ELEMENTS  10 ;
}

/*
**********************************************************************
__time_posn
**********************************************************************
*/
RECORD      __time_posn
{
    LABEL           [time_posn_label] ;
    HELP            [time_posn_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
}

/*
**********************************************************************
__time_posn_t
**********************************************************************
*/
RECORD      __time_posn_t
{
    LABEL           [time_posn_t_label] ;
    HELP            [time_posn_t_help] ;
    MEMBERS    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
}

/*
**********************************************************************
__time_unit1
**********************************************************************
*/
VARIABLE    __time_unit1
{
    LABEL           [time_unit1_label] ;
    HELP            [time_unit1_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_TIME_UNIT1_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__time_unit2
**********************************************************************
*/
VARIABLE    __time_unit2
{
    LABEL           [time_unit2_label] ;
    HELP            [time_unit2_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_TIME_UNIT2_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__time_units
**********************************************************************
*/
VARIABLE    __time_units
{
    LABEL           [time_units_label] ;
    HELP            [time_units_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_TIME_UNITS_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__timer_sp
**********************************************************************
*/
VARIABLE    __timer_sp
{
    LABEL           [timer_sp_label] ;
    HELP            [timer_sp_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__timer_type
**********************************************************************
*/
VARIABLE    __timer_type
{
    LABEL           [timer_type_label] ;
    HELP            [timer_type_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (1) 
    {
        __FF_TIMER_TYPE_ENUMS
    }
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__total_sp
**********************************************************************
*/
VARIABLE    __total_sp
{
    LABEL           [total_sp_label] ;
    HELP            [total_sp_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__totalizer_opts
**********************************************************************
*/
VARIABLE    __totalizer_opts
{
    LABEL           [totalizer_opts_label] ;
    HELP            [totalizer_opts_help] ;
    CLASS           CONTAINED;
    TYPE            ENUMERATED (2)
    {
        { 0,    [totalizer_opt_balanced],     [totalizer_opt_balanced_help]    },
        { 1,    [totalizer_opt_absolute],     [totalizer_opt_absolute_help]    },
        { 2,    [totalizer_opt_only_pos],     [totalizer_opt_only_pos_help]    },
        { 3,    [totalizer_opt_only_neg],     [totalizer_opt_only_neg_help]    },
        { 4,    [totalizer_opt_hold],         [totalizer_opt_hold_help]        }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__travel_time
**********************************************************************
*/
VARIABLE    __travel_time
{
    LABEL           [travel_time_label] ;
    HELP            [travel_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__travel_timer
**********************************************************************
*/
VARIABLE    __travel_timer
{
    LABEL           [travel_timer_label] ;
    HELP            [travel_timer_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ;
}

/*
**********************************************************************
__trip_time
**********************************************************************
*/
VARIABLE    __trip_time
{
    LABEL           [trip_time_label] ;
    HELP            [trip_time_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__uncert_lim
**********************************************************************
*/
VARIABLE    __uncert_lim
{
    LABEL           [uncert_lim_label] ;
    HELP            [uncert_lim_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__unit_conv
**********************************************************************
*/
VARIABLE    __unit_conv
{
    LABEL           [unit_conv_label] ;
    HELP            [unit_conv_help] ;
    CLASS           CONTAINED;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__xd_range
**********************************************************************
*/
RECORD      __xd_range
{
    LABEL           [xd_range_label] ;
    HELP            [xd_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__x_range
**********************************************************************
*/
RECORD      __x_range
{
    LABEL           [x_range_label] ;
    HELP            [x_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

/*
**********************************************************************
__y_range
**********************************************************************
*/
RECORD      __y_range
{
    LABEL           [y_range_label] ;
    HELP            [y_range_help] ;
    MEMBERS    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
}

