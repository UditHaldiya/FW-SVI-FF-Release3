/*
** @(#)xdcr_parm.ddl 0.93beta 2006-08-08
**
** FF common definitions
** Filename: xducer_parm.ddl
** Spec revision:   FF-900    FS 1.0  DDL spec
**                  FF-94-891 PS 1.2  FBP spec part 2
**                  FF-903    PS 2.0  TBP spec
**		    FF-902    FS 1.0  TBT spec
** Date of last change: 2006-08-08
** Description: This file contains common data variables and records
** used for block parameter records
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
**
** (c) Fieldbus Foundation(TM) (1994-2006)
**
*/

/*
** HISTORY:
**  QLQ Revision 0.8  04SEP1997
**  DAD Revision 0.9beta 1999-03-04
**      added dev rev and dd rev system
**  SBM Revision 0.91beta 2002-06-09
**              changed __UNITS_CODES to __UNITS_CODES1 and __UNITS_CODES2 due to bug in Tokenizer 4.2
**  FI  Revision 0.92beta 2005-11-09
**      changed __final_position_value, __final_value,__final_value_d according to AR#618
**      changed __final_value_cuttoff_hi and _lo to __final_value_cutoff_hi and _lo according to AR#1026
**  ED  Revision 0.93beta 2006-08-08
** 	Added parameters introduced in two sensor device
** MS   ARs 2006, 2055 -- 2008.10.07
** MS   ARs 2997, 2998, 3450, 3079, 3656, 3992 -- 2009.06.15
** MS   ARs 3438, 4521, 5157, 5158, 5159, 5160, 5161, 5162, 5163, 5164 -- 2010.06.29
** MS   ARs 5668 -- 2011.04.25
**
*/

#include "com_tbls.h"
/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __STD_XDCR_PARM,
DEVICE_REVISION __STD_XDCR_PARM_beta_dev_rev,
DD_REVISION     __STD_XDCR_PARM_beta_dd_rev

 /*
**********************************************************************
** The following variables make up the Transducer Block Parameters as
** defined by the Transducer Block specification (FF902)
**********************************************************************
*/

/*
**********************************************************************
__status_contained_srv
%TXT%   variable    __status_contained_srv enumerated       0x8002174B
%IMP%   VARIABLE    __status_contained_srv
**********************************************************************
*/
VARIABLE    __status_contained_srv
{
    LABEL           [status_label] ;
    HELP            [status_contained_help] ;
    CLASS           CONTAINED & SERVICE;
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
__float_contained_srv
%TXT%   variable    __float_contained_srv   float         0x8002174C
%IMP%   VARIABLE    __float_contained_srv
**********************************************************************
*/

VARIABLE    __float_contained_srv
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__discrete_contained_srv
%TXT%   variable    __discrete_contained_srv  enumerated     0x8002174D
%IMP%   VARIABLE    __discrete_contained_srv
**********************************************************************
*/
VARIABLE    __discrete_contained_srv
{
    LABEL           [discrete_contained] ;
    HELP            [discrete_contained_help] ;
    CLASS           CONTAINED & SERVICE;
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
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__eu_100_srv
%TXT%   variable    __eu_100_srv              float	0x8002174E
%IMP%   VARIABLE    __eu_100_srv
**********************************************************************
*/
VARIABLE    __eu_100_srv
{
    LABEL           [eu_100] ;
    HELP            [eu_100_help] ;
    CLASS           CONTAINED & SERVICE;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__eu_0_srv
%TXT%   variable    __eu_0_srv	float	0x8002174F
%IMP%   VARIABLE    __eu_0_srv
**********************************************************************
*/
VARIABLE    __eu_0_srv
{
    LABEL           [eu_0] ;
    HELP            [eu_0_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__units_index_srv
%TXT%   variable    __units_index_srv	enumerated	0x80021750
%IMP%   VARIABLE    __units_index_srv
**********************************************************************
*/
VARIABLE    __units_index_srv
{
    LABEL           [units_index] ;
    HELP            [units_index_help] ;
    CLASS           CONTAINED & SERVICE;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__decimal_srv
%TXT%   variable    __decimal_srv	integer		0x80021751
%IMP%   VARIABLE    __decimal_srv
**********************************************************************
*/
VARIABLE    __decimal_srv
{
    LABEL           [decimal] ;
    HELP            [decimal_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__act_fail_action                       FF-903-1.9,  4.6
%SYM%   member      ACT_FAIL_ACTION       parameter         0xC0010330
%SYM%   member      VL_ACT_FAIL_ACTION    variable-list     0xC0010331
%TXT%   variable    __act_fail_action     enumerated        0x80020330
%IMP%   VARIABLE    __act_fail_action
**********************************************************************
*/
VARIABLE    __act_fail_action
{
    LABEL           [act_fail_action_label] ;
    HELP            [act_fail_action_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 1,   [self_close_label],      [self_close_help]       },
        { 2,   [self_open_label],       [self_open_help]        },
        { 3,   [hold_last_val_label],   [hold_last_val_help]    },
        { 4,   [max_val_label],         [max_val_help]          },
        { 5,   [min_val_label],         [min_val_help]          },
        { 255, [indeterm_label],        [indeterm_help]         }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__act_man_id
%SYM%   member      ACT_MAN_ID       parameter        0xC0010332
%SYM%   member      VL_ACT_MAN_ID    variable-list    0xC0010333
%TXT%   variable    __act_man_id     enumerated       0x80020332
%IMP%   VARIABLE    __act_man_id
**********************************************************************
*/
VARIABLE    __act_man_id
{
    LABEL           [act_man_id_label] ;
    HELP            [act_man_id_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/**********************************************************************
__act_model_num
%SYM%   member      ACT_MODEL_NUM         parameter        0xC0010334
%SYM%   member      VL_ACT_MODEL_NUM      variable-list    0xC0010335
%TXT%   variable    __act_model_num       visible          0x80020334
%IMP%   VARIABLE    __act_model_num
**********************************************************************
*/
VARIABLE    __act_model_num
{
    LABEL           [act_model_num_label] ;
    HELP            [act_model_num_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__act_sn
%SYM%   member      ACT_SN         parameter           0xC0010336
%SYM%   member      VL_ACT_SN      variable-list       0xC0010337
%TXT%   variable    __act_sn       visible             0x80020336
%IMP%   VARIABLE    __act_sn
**********************************************************************
*/
VARIABLE    __act_sn
{
    LABEL           [act_sn_label] ;
    HELP            [act_sn_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            VISIBLE (32);
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_min_span
%SYM%   member      CAL_MIN_SPAN        parameter          0xC0010342
%SYM%   member      VL_CAL_MIN_SPAN     variable-list      0xC0010343
%TXT%   variable    __cal_min_span      float              0x80020342
%IMP%   VARIABLE    __cal_min_span
**********************************************************************
*/
VARIABLE    __cal_min_span
{
    LABEL           [cal_min_span_label] ;
    HELP            [cal_min_span_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_hi
%SYM%   member      CAL_POINT_HI        parameter         0xC0010344
%SYM%   member      VL_CAL_POINT_HI     variable-list     0xC0010345
%TXT%   variable    __cal_point_hi      float             0x80020344
%IMP%   VARIABLE    __cal_point_hi
**********************************************************************
*/
VARIABLE    __cal_point_hi
{
    LABEL           [cal_point_hi_label] ;
    HELP            [cal_point_hi_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_lo
%SYM%   member      CAL_POINT_LO        parameter         0xC0010346
%SYM%   member      VL_CAL_POINT_LO     variable-list     0xC0010347
%TXT%   variable    __cal_point_lo      float             0x80020346
%IMP%   VARIABLE    __cal_point_lo
**********************************************************************
*/
VARIABLE    __cal_point_lo
{
    LABEL           [cal_point_lo_label] ;
    HELP            [cal_point_lo_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_propagation_vel
%SYM%   member     CAL_PROPAGATION_VEL      parameter      0xC0010348
%SYM%   member     VL_CAL_PROPAGATION_VEL   variable-list  0xC0010349
%TXT%   variable   __cal_propagation_vel    float          0x80020348
%IMP%   VARIABLE   __cal_propagation_vel
**********************************************************************
*/
VARIABLE    __cal_propagation_vel
{
    LABEL           [cal_propagation_vel_label] ;
    HELP            [cal_propagation_vel_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_unit
%SYM%   member      CAL_UNIT        parameter           0xC0010350
%SYM%   member      VL_CAL_UNIT     variable-list       0xC0010351
%TXT%   variable    __cal_unit      enumerated          0x80020350
%IMP%   VARIABLE    __cal_unit
**********************************************************************
*/
VARIABLE    __cal_unit
{
    LABEL           [cal_unit_label] ;
    HELP            [cal_unit_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__channel_map_entry
%SYM%   member      CHANNEL_MAP_ENTRY      parameter   0xC0010353
%TXT%   variable    __channel_map_entry    unsigned    0x80020353
%IMP%   VARIABLE    __channel_map_entry
**********************************************************************
*/
VARIABLE  __channel_map_entry
  {
     LABEL           [blk_char] ;
     HELP            [blk_char_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            UNSIGNED_INTEGER (2) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__channel_map
%SYM%   member          CHANNEL_MAP          parameter   0xC0010352
%TXT%   array           __channel_map                    0x80020352
%IMP%   ARRAY           __channel_map
%IMP%     VARIABLE        __channel_map_entry
%IMP%     VARIABLE        __array_indicie
**********************************************************************
*/
ARRAY  __channel_map
  {
     LABEL    [channel_map_label] ;
     HELP     [channel_map_help] ;
     TYPE     __channel_map_entry ;
/*   {
        __array_indicie
     }  */
     NUMBER_OF_ELEMENTS 1;
  }

 /*
**********************************************************************
__collection_directory
%SYM%   member      COLLECTION_DIRECTORY      parameter   0xC0010356
%TXT%   array       __collection_directory                0x80020356
%IMP%   ARRAY       __collection_directory
%IMP%     VARIABLE    __collection_directory_entry
**********************************************************************
*/
ARRAY  __collection_directory
  {
     LABEL    [collection_directory_label] ;
     HELP     [collection_directory_help] ;
     TYPE     __collection_directory_entry;
     NUMBER_OF_ELEMENTS 1;
  }

/*
**********************************************************************
__collection_directory_entry
%SYM%   member     COLLECTION_DIRECTORY_ENTRY    parameter 0xC0010357
%TXT%   variable   __collection_directory_entry  unsigned  0x80020357
%IMP%   VARIABLE   __collection_directory_entry
**********************************************************************
*/
VARIABLE  __collection_directory_entry
  {
     LABEL           [blk_char] ;
     HELP            [blk_char_help] ;
     CLASS           CONTAINED ;
     TYPE            UNSIGNED_INTEGER (4) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__final_position_value           (DS-65)
%SYM%   member     FINAL_POSITION_VALUE      parameter      0xC0010362
%SYM%   member     VL_FINAL_POSITION_VALUE   variable-list  0xC0010363
%TXT%   record     __final_position_value                   0x80020362
%IMP%   RECORD     __final_position_value
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __final_position_value
{
    LABEL           [final_position_value_label] ;
    HELP            [final_position_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __float_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__final_value           (DS-65)
%SYM%   member      FINAL_VALUE        parameter        0xC0010364
%SYM%   member      VL_FINAL_VALUE     variable-list    0xC0010365
%TXT%   record      __final_value                       0x80020364
%IMP%   RECORD      __final_value
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __final_value
{
    LABEL           [final_value_label] ;
    HELP            [final_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_srv ;
        VALUE,   __float_contained_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

 /*
**********************************************************************
__final_value_cutoff_hi
%SYM%   member     FINAL_VALUE_CUTOFF_HI     parameter     0xC0010430
%SYM%   member     VL_FINAL_VALUE_CUTOFF_HI  variable-list 0xC0010431
%TXT%   variable   __final_value_cutoff_hi   float         0x80020430
%IMP%   VARIABLE   __final_value_cutoff_hi
**********************************************************************
*/
VARIABLE    __final_value_cutoff_hi
{
    LABEL           [final_value_cutoff_hi_label] ;
    HELP            [final_value_cutoff_hi_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__final_value_cutoff_lo
%SYM%   member     FINAL_VALUE_CUTOFF_LO     parameter     0xC0010432
%SYM%   member     VL_FINAL_VALUE_CUTOFF_LO  variable-list 0xC0010433
%TXT%   variable   __final_value_cutoff_lo   float         0x80020432
%IMP%   VARIABLE   __final_value_cutoff_lo
**********************************************************************
*/
VARIABLE    __final_value_cutoff_lo
{
    LABEL           [final_value_cutoff_lo_label] ;
    HELP            [final_value_cutoff_lo_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__final_value_d            (DS-66)
%SYM%   member      FINAL_VALUE_D       parameter         0xC0010366
%SYM%   member      VL_FINAL_VALUE_D    variable-list     0xC0010367
%TXT%   record      __final_value_d                       0x80020366
%IMP%   RECORD      __final_value_d
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __discrete_input
**********************************************************************
*/
RECORD      __final_value_d
{
    LABEL           [final_value_d_label] ;
    HELP            [final_value_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_srv ;
        VALUE,   __discrete_contained_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__final_value_range        (DS-68)
%SYM%   member      FINAL_VALUE_RANGE       parameter       0xC0010368
%SYM%   member      VL_FINAL_VALUE_RANGE    variable-list   0xC0010369
%TXT%   record      __final_value_range                     0x80020368
%IMP%   RECORD      __final_value_range
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __final_value_range
{
    LABEL           [final_value_range_label] ;
    HELP            [final_value_range_help] ;
    MEMBERS
    {
        EU_100,      __eu_100_srv ;
        EU_0,        __eu_0_srv ;
        UNITS_INDEX,  __units_index_srv ;
        DECIMAL,     __decimal_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__level_offset
%SYM%   member      LEVEL_OFFSET        parameter          0xC0010370
%SYM%   member      VL_LEVEL_OFFSET     variable-list      0xC0010371
%TXT%   variable    __level_offset      float              0x80020370
%IMP%   VARIABLE    __level_offset
**********************************************************************
*/
VARIABLE    __level_offset
{
    LABEL           [level_offset_label] ;
    HELP            [level_offset_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__lin_type                                  FF-903 PS1.9  Sec4.4
%SYM%   member      LIN_TYPE           parameter          0xC0010372
%SYM%   member      VL_LIN_TYPE        variable-list      0xC0010373
%TXT%   variable    __lin_type         enumerated         0x80020372
%IMP%   VARIABLE    __lin_type
**********************************************************************
*/
VARIABLE    __lin_type
{
    LABEL           [lin_type_label] ;
    HELP            [lin_type_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 1,   [lin_in_label],              [lin_in_help]           },
        { 2,   [lin_out_label],             [lin_out_help]          },
        { 3,   [sqr_root_label],            [sqr_root_help]         },
        { 4,   [sqr_root_thrd_pwr_label],   [sqr_root_thrd_pwr_help]},
        { 5,   [sqr_root_fif_pwr_label],    [sqr_root_fif_pwr_help] },
        { 255, [other],                     [other_help]            }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__module_sn
%SYM%   member      MODULE_SN         parameter           0xC0010374
%SYM%   member      VL_MODULE_SN      variable-list       0xC0010375
%TXT%   variable    __module_sn       unsigned            0x80020374
%IMP%   VARIABLE    __module_sn
**********************************************************************
*/
VARIABLE    __module_sn
{
    LABEL           [module_sn_label] ;
    HELP            [module_sn_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE(32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value             (DS-65)
%SYM%   member      PRIMARY_VALUE        parameter        0xC0010376
%SYM%   member      VL_PRIMARY_VALUE     variable-list    0xC0010377
%TXT%   record      __primary_value                       0x80020376
%IMP%   RECORD      __primary_value
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __float_contained
**********************************************************************
*/
RECORD      __primary_value
{
    LABEL           [primary_value_label] ;
    HELP            [primary_value_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_range       (DS-68)
%SYM%   member     PRIMARY_VALUE_RANGE      parameter      0xC0010378
%SYM%   member     VL_PRIMARY_VALUE_RANGE   variable-list  0xC0010379
%TXT%   record     __primary_value_range                   0x80020378
%IMP%   RECORD     __primary_value_range
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __primary_value_range
{
    LABEL           [primary_value_range_label] ;
    HELP            [primary_value_range_help] ;
    MEMBERS
    {
        EU_100,      __eu_100_srv ;
        EU_0,        __eu_0_srv ;
        UNITS_INDEX,  __units_index_srv ;
        DECIMAL,     __decimal_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_type
%SYM%   member      PRIMARY_VALUE_TYPE      parameter      0xC0010380
%SYM%   member      VL_PRIMARY_VALUE_TYPE   variable-list  0xC0010381
%TXT%   variable    __primary_value_type    enumerated     0x80020380
%IMP%   VARIABLE    __primary_value_type
**********************************************************************
*/
VARIABLE    __primary_value_type
{
    LABEL           [primary_value_type_label] ;
    HELP            [primary_value_type_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __PRIMARY_VALUE_TYPES
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__secondary_value             (DS-65)
%SYM%   member      SECONDARY_VALUE       parameter       0xC0010382
%SYM%   member      VL_SECONDARY_VALUE    variable-list   0xC0010383
%TXT%   record      __secondary_value                     0x80020382
%IMP%   RECORD      __secondary_value
%IMP%       VARIABLE    __status_output
%IMP%       VARIABLE    __float_output
**********************************************************************
*/
RECORD      __secondary_value
{
    LABEL           [secondary_value_label] ;
    HELP            [secondary_value_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__secondary_value_unit
%SYM%   member     SECONDARY_VALUE_UNIT      parameter      0xC0010384
%SYM%   member     VL_SECONDARY_VALUE_UNIT   variable-list  0xC0010385
%TXT%   variable   __secondary_value_unit    enumerated       0x80020384
%IMP%   VARIABLE   __secondary_value_unit
**********************************************************************
*/
VARIABLE    __secondary_value_unit
{
    LABEL           [secondary_value_unit_label] ;
    HELP            [secondary_value_unit_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_date
%SYM%   member      SENSOR_CAL_DATE       parameter        0xC0010386
%SYM%   member      VL_SENSOR_CAL_DATE    variable-list    0xC0010387
%TXT%   variable    __sensor_cal_date     date_and_time    0x80020386
%IMP%   VARIABLE    __sensor_cal_date
**********************************************************************
 */
VARIABLE    __sensor_cal_date
{
    LABEL           [sensor_cal_date_label] ;
    HELP            [sensor_cal_date_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_loc
%SYM%   member      SENSOR_CAL_LOC       parameter        0xC0010388
%SYM%   member      VL_SENSOR_CAL_LOC    variable-list    0xC0010389
%TXT%   variable    __sensor_cal_loc     visible          0x80020388
%IMP%   VARIABLE    __sensor_cal_loc
**********************************************************************
*/
VARIABLE   __sensor_cal_loc
  {
     LABEL           [sensor_cal_loc_label] ;
     HELP            [sensor_cal_loc_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__sensor_cal_method
%SYM%   member      SENSOR_CAL_METHOD       parameter       0xC0010390
%SYM%   member      VL_SENSOR_CAL_METHOD    variable-list   0xC0010391
%TXT%   variable    __sensor_cal_method     enumerated      0x80020390
%IMP%   VARIABLE    __sensor_cal_method
**********************************************************************
*/
VARIABLE    __sensor_cal_method
{
    LABEL           [sensor_cal_method_label] ;
    HELP            [sensor_cal_method_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        { 100,  [volume_label],             [volume_help]           },
        { 101,  [static_wght_label],        [static_wght_label]     },
        { 102,  [dync_wght_label],          [dync_wght_label]       },
        { 103,  [fac_trim_std_cal_label],   [fac_trim_std_cal_help] },
        { 104,  [user_trim_std_cal_label],  [user_trim_std_cal_help]},
        { 105,  [fac_trim_sp_cal_label],    [fac_trim_sp_cal_help]  },
        { 106,  [user_trim_sp_cal_label],   [user_trim_sp_cal_help] },
        { 255,  [other],                    [other_help]            }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_who
%SYM%   member      SENSOR_CAL_WHO        parameter        0xC0010434
%SYM%   member      VL_SENSOR_CAL_WHO     variable-list    0xC0010435
%TXT%   variable    __sensor_cal_who      visible          0x80020434
%IMP%   VARIABLE    __sensor_cal_who
**********************************************************************
*/
VARIABLE    __sensor_cal_who
  {
     LABEL           [sensor_cal_who_label] ;
     HELP            [sensor_cal_who_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

 /*
**********************************************************************
__sensor_connection
%SYM%   member      SENSOR_CONNECTION       parameter       0xC0010392
%SYM%   member      VL_SENSOR_CONNECTION    variable-list   0xC0010393
%TXT%   variable    __sensor_connection     enumerated      0x80020392
%IMP%   VARIABLE    __sensor_connection
**********************************************************************
*/
VARIABLE    __sensor_connection
{
    LABEL           [sensor_connection_label] ;
    HELP            [sensor_connection_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        { 2,  [two_wires],      [two_wires_help] },
        { 3,  [three_wires],    [three_wires_help] },
        { 4,  [four_wires],     [four_wires_help] }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_fill_fluid
%SYM%   member      SENSOR_FILL_FLUID      parameter       0xC0010394
%SYM%   member      VL_SENSOR_FILL_FLUID   variable-list   0xC0010395
%TXT%   variable    __sensor_fill_fluid    enumerated        0x80020394
%IMP%   VARIABLE    __sensor_fill_fluid
**********************************************************************
*/
VARIABLE    __sensor_fill_fluid
{
    LABEL           [sensor_fill_fluid_label] ;
    HELP            [sensor_fill_fluid_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED(2)
    {
        _UNDEFINED_VALUE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_isolator_mtl
%SYM%   member      SENSOR_ISOLATOR_MTL      parameter      0xC0010396
%SYM%   member      VL_SENSOR_ISOLATOR_MTL   variable-list  0xC0010397
%TXT%   variable    __sensor_isolator_mtl    enumerated       0x80020396
%IMP%   VARIABLE    __sensor_isolator_mtl
**********************************************************************
*/
VARIABLE    __sensor_isolator_mtl
{
    LABEL           [sensor_isolator_mtl_label] ;
    HELP            [sensor_isolator_mtl_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED(2)
    {
        _UNDEFINED_VALUE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_offset
%SYM%   member      SENSOR_OFFSET        parameter         0xC0010436
%SYM%   member      VL_SENSOR_OFFSET     variable-list     0xC0010437
%TXT%   variable    __sensor_offset      float             0x80020436
%IMP%   VARIABLE    __sensor_offset
**********************************************************************
*/
VARIABLE    __sensor_offset
{
    LABEL           [sensor_offset_label] ;
    HELP            [sensor_offset_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_range        (DS-68)
%SYM%   member      SENSOR_RANGE      parameter       0xC0010398
%SYM%   member      VL_SENSOR_RANGE   variable-list   0xC0010399
%TXT%   record      __sensor_range                    0x80020398
%IMP%   RECORD      __sensor_range
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __sensor_range
{
    LABEL           [sensor_range_label] ;
    HELP            [sensor_range_help] ;
    MEMBERS
    {
        EU_100,      __eu_100_srv ;
        EU_0,        __eu_0_srv ;
        UNITS_INDEX,  __units_index_srv ;
        DECIMAL,     __decimal_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_sn
%SYM%   member      SENSOR_SN         parameter           0xC0010400
%SYM%   member      VL_SENSOR_SN      variable-list       0xC0010401
%TXT%   variable    __sensor_sn       visible             0x80020400
%IMP%   VARIABLE    __sensor_sn
**********************************************************************
*/
VARIABLE    __sensor_sn
{
    LABEL           [sensor_sn_label] ;
    HELP            [sensor_sn_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_type                           FF-903 PS1.9 Sec4.3
%SYM%   member      SENSOR_TYPE        parameter         0xC0010406
%SYM%   member      VL_SENSOR_TYPE     variable-list     0xC0010407
%TXT%   variable    __sensor_type      enumerated        0x80020406
%IMP%   VARIABLE    __sensor_type
**********************************************************************
*/
VARIABLE    __sensor_type
{
    LABEL           [sensor_type_label] ;
    HELP            [sensor_type_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __SENSOR_TYPES
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__servo_gain
%SYM%   member      SERVO_GAIN      parameter           0xC0010408
%SYM%   member      VL_SERVO_GAIN   variable-list       0xC0010409
%TXT%   variable    __servo_gain    float               0x80020408
%IMP%   VARIABLE    __servo_gain
**********************************************************************
*/
VARIABLE    __servo_gain
  {
     LABEL           [servo_gain_label] ;
     HELP            [servo_gain_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            FLOAT ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__servo_rate
%SYM%   member      SERVO_RATE      parameter           0xC0010410
%SYM%   member      VL_SERVO_RATE   variable-list       0xC0010411
%TXT%   variable    __servo_rate    float               0x80020410
%IMP%   VARIABLE    __servo_rate
**********************************************************************
*/
VARIABLE    __servo_rate
  {
     LABEL           [servo_rate_label] ;
     HELP            [servo_rate_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            FLOAT ;
     CONSTANT_UNIT   [sec] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__servo_reset
%SYM%   member      SERVO_RESET      parameter           0xC0010412
%SYM%   member      VL_SERVO_RESET   variable-list       0xC0010413
%TXT%   variable    __servo_reset    float               0x80020412
%IMP%   VARIABLE    __servo_reset
**********************************************************************
*/
VARIABLE    __servo_reset
  {
     LABEL           [servo_reset_label] ;
     HELP            [servo_reset_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            FLOAT ;
     CONSTANT_UNIT   [sec] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__transducer_directory
%SYM%   member      TRANSDUCER_DIRECTORY      parameter   0xC0010414
%TXT%   array      __transducer_directory                 0x80020414
%IMP%   ARRAY      __transducer_directory
%IMP%     VARIABLE    __transducer_directory_entry
**********************************************************************
*/
ARRAY  __transducer_directory
  {
     LABEL    [transducer_directory_label] ;
     HELP     [transducer_directory_help] ;
     TYPE     __transducer_directory_entry;
     NUMBER_OF_ELEMENTS 1;
  }

/*
**********************************************************************
__transducer_directory_entry
%SYM%   member     TRANSDUCER_DIRECTORY_ENTRY    parameter 0xC0010415
%TXT%   variable   __transducer_directory_entry  unsigned  0x80020415
%IMP%   VARIABLE   __transducer_directory_entry
**********************************************************************
*/
VARIABLE  __transducer_directory_entry
  {
     LABEL           [blk_char] ;
     HELP            [blk_char_help] ;
     CLASS           CONTAINED ;
     TYPE            UNSIGNED_INTEGER (2) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ ;
     /* RESPONSE_CODES  xxx ; */
  }


/*
**********************************************************************
__transducer_type   FF-903 PS 1.9 Sec.4.2
%SYM%   member      TRANSDUCER_TYPE      parameter       0xC0010354
%SYM%   member      VL_TRANSDUCER_TYPE   variable-list   0xC0010355
%TXT%   variable    __transducer_type    enumerated      0x80020354
%IMP%   VARIABLE    __transducer_type
**********************************************************************
*/
VARIABLE    __transducer_type
{
    LABEL           [transducer_type_label] ;
    HELP            [transducer_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __TRANSDUCER_TYPES
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__transducer_type_ver   
%SYM%   member      TRANSDUCER_TYPE_VER      parameter       0xC001
%SYM%   member      VL_TRANSDUCER_TYPE_VER   variable-list   0xC001
%TXT%   variable    __transducer_type_ver    unsigned        0x8002
%IMP%   VARIABLE    __transducer_type_ver
**********************************************************************
*/
VARIABLE    __transducer_type_ver
{
    LABEL           [transducer_type_ver_label] ;
    HELP            [transducer_type_ver_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_opts   
%SYM%   member      XD_OPTS      parameter       0x
%SYM%   member      VL_XD_OPTS   variable-list   0x
%TXT%   variable    __xd_opts    bit-enumerated  0x80021752
%IMP%   VARIABLE    __xd_opts
**********************************************************************
*/
VARIABLE    __xd_opts
{
    LABEL           [transducer_opts_label] ;
    HELP            [transducer_opts_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            BIT_ENUMERATED (4)
    {
    	{ 0x0001,  [xd_opts_bad_in_man],    [xd_opts_bad_in_man_help] },
    	{ 0x0002,  [xd_opts_unc_in_man],    [xd_opts_unc_in_man_help] }
    }
    HANDLING	READ  & WRITE ;
}


/*
**********************************************************************
__travel_accum   
%SYM%   member      TRAVEL_ACCUM      parameter       0xC001
%SYM%   member      VL_TRAVEL_ACCUM   variable-list   0xC001
%TXT%   variable    __travel_accum    float           0x8002
%IMP%   VARIABLE    __travel_accum
**********************************************************************
*/
VARIABLE    __travel_accum
{
    LABEL           [travel_accum_label] ;
    HELP            [travel_accum_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__valve_man_id
%SYM%   member      VALVE_MAN_ID        parameter         0xC0010416
%SYM%   member      VL_VALVE_MAN_ID     variable-list     0xC0010417
%TXT%   variable    __valve_man_id      enumerated        0x80020416
%IMP%   VARIABLE    __valve_man_id
**********************************************************************
*/
VARIABLE    __valve_man_id
  {
     LABEL           [valve_man_id_label] ;
     HELP            [valve_man_id_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE;
     /* RESPONSE_CODES  xxx ; */
  }


/*
**********************************************************************
__valve_model_num
%SYM%   member      VALVE_MODEL_NUM       parameter       0xC0010418
%SYM%   member      VL_VALVE_MODEL_NUM    variable-list   0xC0010419
%TXT%   variable    __valve_model_num     visible         0x80020418
%IMP%   VARIABLE    __valve_model_num
**********************************************************************
*/
VARIABLE    __valve_model_num
  {
     LABEL           [valve_model_num_label] ;
     HELP            [valve_model_num_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE;
     /* RESPONSE_CODES  xxx ; */
  }


/*
**********************************************************************
__valve_sn
%SYM%   member      VALVE_SN         parameter         0xC0010420
%SYM%   member      VL_VALVE_SN      variable-list     0xC0010421
%TXT%   variable    __valve_sn       visible           0x80020420
%IMP%   VARIABLE    __valve_sn
**********************************************************************
*/
VARIABLE    __valve_sn
  {
     LABEL           [valve_sn_label] ;
     HELP            [valve_sn_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__valve_type
%SYM%   member      VALVE_TYPE          parameter         0xC0010438
%SYM%   member      VL_VALVE_TYPE       variable-list     0xC0010439
%TXT%   variable    __valve_type        enumerated        0x80020438
%IMP%   VARIABLE    __valve_type
**********************************************************************
*/
VARIABLE    __valve_type
{
    LABEL           [valve_type_label] ;
    HELP            [valve_type_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 1,  [linear_label],    [linear_help] },
        { 2,  [rotary_label],    [rotary_help] },
        {255, [other],           [other_help]  }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__velocity_unit
%SYM%   member      VELOCITY_UNIT      parameter         0xC0010426
%SYM%   member      VL_VELOCITY_UNIT   variable-list     0xC0010427
%TXT%   variable    __velocity_unit    enumerated        0x80020426
%IMP%   VARIABLE    __velocity_unit
**********************************************************************
*/
VARIABLE    __velocity_unit
{
    LABEL           [velocity_unit_label] ;
    HELP            [velocity_unit_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
    /*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_cal_loc
%SYM%   member      XD_CAL_LOC         parameter         0xC0010440
%SYM%   member      VL_XD_CAL_LOC      variable-list     0xC0010441
%TXT%   variable    __xd_cal_loc       visible          0x80020440
%IMP%   VARIABLE    __xd_cal_loc
**********************************************************************
*/
VARIABLE    __xd_cal_loc
  {
     LABEL           [xd_cal_loc_label] ;
     HELP            [xd_cal_loc_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__xd_cal_date
%SYM%   member       XD_CAL_DATE        parameter        0xC0010442
%SYM%   member       VL_XD_CAL_DATE     variable-list    0xC0010443
%TXT%   variable     __xd_cal_date      date_and_time    0x80020442
%IMP%   VARIABLE     __xd_cal_date
**********************************************************************
 */
VARIABLE    __xd_cal_date
{
    LABEL           [xd_cal_date_label] ;
    HELP            [xd_cal_date_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

 /*
**********************************************************************
__xd_cal_who
%SYM%   member      XD_CAL_WHO         parameter         0xC0010444
%SYM%   member      VL_XD_CAL_WHO      variable-list     0xC0010445
%TXT%   variable    __xd_cal_who       visible          0x80020444
%IMP%   VARIABLE    __xd_cal_who
**********************************************************************
*/
VARIABLE    __xd_cal_who
  {
     LABEL           [xd_cal_who_label] ;
     HELP            [xd_cal_who_help] ;
     CLASS           CONTAINED & SERVICE ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__xd_error      FF-903 Pt.2   Sec 3.1 & Sec 4.8
%SYM%   member     XD_ERROR         parameter        0xC0010428
%SYM%   member     VL_XD_ERROR      variable-list    0xC0010429
%TXT%   variable   __xd_error       enumerated       0x80020428
%IMP%   VARIABLE   __xd_error
**********************************************************************
*/
VARIABLE    __xd_error
  {
     LABEL           [xd_error_label] ;
     HELP            [xd_error_help] ;
     CLASS           CONTAINED ;
     TYPE            ENUMERATED (1)
     {
        { 16, [unspec_err_label],       [unspec_err_help]     },
        { 17, [gen_err_label],          [gen_err_help]        },
        { 18, [cal_err_label],          [cal_err_help]        },
        { 19, [config_err_label],       [config_err_help]     },
        { 20, [elec_fail_label],        [elec_fail_help]      },
        { 21, [mech_fail_label],        [mech_fail_help]      },
        { 22, [io_fail_label],          [io_fail_help]        },
        { 23, [data_integ_err_label],   [data_integ_err_help] },
        { 24, [software_err_label],     [software_err_label]  },
        { 25, [algorithm_err_label],    [algorithm_err_label] }
    }
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ ;
     /* RESPONSE_CODES  xxx ; */
  }


/*
**********************************************************************
__cal_min_span_1
%SYM%   member      CAL_MIN_SPAN_1      parameter          0xC0010446
%SYM%   member      VL_CAL_MIN_SPAN_1   variable-list      0xC0010447
%TXT%   variable    __cal_min_span_1    float              0x80020446
%IMP%   VARIABLE    __cal_min_span_1
**********************************************************************
*/
VARIABLE    __cal_min_span_1
{
    LABEL           [cal_min_span_1_label] ;
    HELP            [cal_min_span_1_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_hi_1
%SYM%   member      CAL_POINT_HI_1        parameter         0xC0010448
%SYM%   member      VL_CAL_POINT_HI_1     variable-list     0xC0010449
%TXT%   variable    __cal_point_hi_1      float             0x80020448
%IMP%   VARIABLE    __cal_point_hi_1
**********************************************************************
*/
VARIABLE    __cal_point_hi_1
{
    LABEL           [cal_point_hi_1_label] ;
    HELP            [cal_point_hi_1_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_lo_1
%SYM%   member      CAL_POINT_LO_1        parameter         0xC001044A
%SYM%   member      VL_CAL_POINT_LO_1     variable-list     0xC001044B
%TXT%   variable    __cal_point_lo_1      float             0x8002044A
%IMP%   VARIABLE    __cal_point_lo_1
**********************************************************************
*/
VARIABLE    __cal_point_lo_1
{
    LABEL           [cal_point_lo_1_label] ;
    HELP            [cal_point_lo_1_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_unit_1
%SYM%   member      CAL_UNIT_1        parameter           0xC001044C
%SYM%   member      VL_CAL_UNIT_1     variable-list       0xC001044D
%TXT%   variable    __cal_unit_1      enumerated          0x8002044C
%IMP%   VARIABLE    __cal_unit_1
**********************************************************************
*/
VARIABLE    __cal_unit_1
{
    LABEL           [cal_unit_1_label] ;
    HELP            [cal_unit_1_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
		__UNITS_CODES2
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_1             (DS-65)
%SYM%   member      PRIMARY_VALUE_1        parameter        0xC001044E
%SYM%   member      VL_PRIMARY_VALUE_1     variable-list    0xC001044F
%TXT%   record      __primary_value_1                       0x8002044E
%IMP%   RECORD      __primary_value_1
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __float_contained
**********************************************************************
*/
RECORD      __primary_value_1
{
    LABEL           [primary_value_1_label] ;
    HELP            [primary_value_1_help] ;
    MEMBERS
    {
        STATUS,     __status_contained ;
        VALUE,      __float_contained ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_range_1       (DS-68)
%SYM%   member     PRIMARY_VALUE_RANGE_1      parameter      0xC0010450
%SYM%   member     VL_PRIMARY_VALUE_RANGE_1   variable-list  0xC0010451
%TXT%   record     __primary_value_range_1                   0x80020450
%IMP%   RECORD     __primary_value_range_1
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __primary_value_range_1
{
    LABEL           [primary_value_range_1_label] ;
    HELP            [primary_value_range_1_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_type_1
%SYM%   member      PRIMARY_VALUE_TYPE_1      parameter      0xC0010452
%SYM%   member      VL_PRIMARY_VALUE_TYPE_1   variable-list  0xC0010453
%TXT%   variable    __primary_value_type_1    enumerated     0x80020452
%IMP%   VARIABLE    __primary_value_type_1
**********************************************************************
*/
VARIABLE    __primary_value_type_1
{
    LABEL           [primary_value_type_1_label] ;
    HELP            [primary_value_type_1_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __PRIMARY_VALUE_TYPES
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__sensor_cal_date_1
%SYM%   member      SENSOR_CAL_DATE_1       parameter        0xC0010454
%SYM%   member      VL_SENSOR_CAL_DATE_1    variable-list    0xC0010455
%TXT%   variable    __sensor_cal_date_1     date_and_time    0x80020454
%IMP%   VARIABLE    __sensor_cal_date_1
**********************************************************************
 */
VARIABLE    __sensor_cal_date_1
{
    LABEL           [sensor_cal_date_1_label] ;
    HELP            [sensor_cal_date_1_help] ;
    CLASS           CONTAINED ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_loc_1
%SYM%   member      SENSOR_CAL_LOC_1       parameter        0xC0010456
%SYM%   member      VL_SENSOR_CAL_LOC_1    variable-list    0xC0010457
%TXT%   variable    __sensor_cal_loc_1     visible          0x80020456
%IMP%   VARIABLE    __sensor_cal_loc_1
**********************************************************************
*/
VARIABLE   __sensor_cal_loc_1
  {
     LABEL           [sensor_cal_loc_1_label] ;
     HELP            [sensor_cal_loc_1_help] ;
     CLASS           CONTAINED ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__sensor_cal_method_1
%SYM%   member      SENSOR_CAL_METHOD_1       parameter       0xC0010458
%SYM%   member      VL_SENSOR_CAL_METHOD_1    variable-list   0xC0010459
%TXT%   variable    __sensor_cal_method_1     enumerated      0x80020458
%IMP%   VARIABLE    __sensor_cal_method_1
**********************************************************************
*/
VARIABLE    __sensor_cal_method_1
{
    LABEL           [sensor_cal_method_1_label] ;
    HELP            [sensor_cal_method_1_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 100,  [volume_label],             [volume_help]           },
        { 101,  [static_wght_label],        [static_wght_label]     },
        { 102,  [dync_wght_label],          [dync_wght_label]       },
        { 103,  [fac_trim_std_cal_label],   [fac_trim_std_cal_help] },
        { 104,  [user_trim_std_cal_label],  [user_trim_std_cal_help]},
        { 105,  [fac_trim_sp_cal_label],    [fac_trim_sp_cal_help]  },
        { 106,  [user_trim_sp_cal_label],   [user_trim_sp_cal_help] },
        { 255,  [other],                    [other_help]            }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_who_1
%SYM%   member      SENSOR_CAL_WHO_1        parameter        0xC001045A
%SYM%   member      VL_SENSOR_CAL_WHO_1     variable-list    0xC001045B
%TXT%   variable    __sensor_cal_who_1      visible          0x8002045A
%IMP%   VARIABLE    __sensor_cal_who_1
**********************************************************************
*/
VARIABLE    __sensor_cal_who_1
  {
     LABEL           [sensor_cal_who_1_label] ;
     HELP            [sensor_cal_who_1_help] ;
     CLASS           CONTAINED ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

 /*
**********************************************************************
__sensor_connection_1
%SYM%   member      SENSOR_CONNECTION_1       parameter       0xC001045C
%SYM%   member      VL_SENSOR_CONNECTION_1    variable-list   0xC001045D
%TXT%   variable    __sensor_connection_1     enumerated      0x8002045C
%IMP%   VARIABLE    __sensor_connection_1
**********************************************************************
*/
VARIABLE    __sensor_connection_1
{
    LABEL           [sensor_connection_1_label] ;
    HELP            [sensor_connection_1_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 2,  [two_wires],      [two_wires_help] },
        { 3,  [three_wires],    [three_wires_help] },
        { 4,  [four_wires],     [four_wires_help] }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__sensor_range_1        (DS-68)
%SYM%   member      SENSOR_RANGE_1      parameter       0xC001045E
%SYM%   member      VL_SENSOR_RANGE_1   variable-list   0xC001045F
%TXT%   record      __sensor_range_1                    0x8002045E
%IMP%   RECORD      __sensor_range_1
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __sensor_range_1
{
    LABEL           [sensor_range_1_label] ;
    HELP            [sensor_range_1_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_sn_1
%SYM%   member      SENSOR_SN_1         parameter           0xC0010460
%SYM%   member      VL_SENSOR_SN_1      variable-list       0xC0010461
%TXT%   variable    __sensor_sn_1       visible             0x80020460
%IMP%   VARIABLE    __sensor_sn_1
**********************************************************************
*/
VARIABLE    __sensor_sn_1
{
    LABEL           [sensor_sn_1_label] ;
    HELP            [sensor_sn_1_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_type_1                           FF-903 PS1.9 Sec4.3
%SYM%   member      SENSOR_TYPE_1        parameter         0xC0010462
%SYM%   member      VL_SENSOR_TYPE_1     variable-list     0xC0010463
%TXT%   variable    __sensor_type_1      enumerated        0x80020462
%IMP%   VARIABLE    __sensor_type_1
**********************************************************************
*/
VARIABLE    __sensor_type_1
{
    LABEL           [sensor_type_1_label] ;
    HELP            [sensor_type_1_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __SENSOR_TYPES
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__cal_min_span_2
%SYM%   member      CAL_MIN_SPAN_2      parameter          0xC0010464
%SYM%   member      VL_CAL_MIN_SPAN_2   variable-list      0xC0010465
%TXT%   variable    __cal_min_span_2    float              0x80020464
%IMP%   VARIABLE    __cal_min_span_2
**********************************************************************
*/
VARIABLE    __cal_min_span_2
{
    LABEL           [cal_min_span_2_label] ;
    HELP            [cal_min_span_2_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_hi_2
%SYM%   member      CAL_POINT_HI_2        parameter         0xC0010466
%SYM%   member      VL_CAL_POINT_HI_2     variable-list     0xC0010467
%TXT%   variable    __cal_point_hi_2      float             0x80020466
%IMP%   VARIABLE    __cal_point_hi_2
**********************************************************************
*/
VARIABLE    __cal_point_hi_2
{
    LABEL           [cal_point_hi_2_label] ;
    HELP            [cal_point_hi_2_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_point_lo_2
%SYM%   member      CAL_POINT_LO_2        parameter         0xC0010468
%SYM%   member      VL_CAL_POINT_LO_2     variable-list     0xC0010469
%TXT%   variable    __cal_point_lo_2      float             0x80020468
%IMP%   VARIABLE    __cal_point_lo_2
**********************************************************************
*/
VARIABLE    __cal_point_lo_2
{
    LABEL           [cal_point_lo_2_label] ;
    HELP            [cal_point_lo_2_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_unit_2
%SYM%   member      CAL_UNIT_2        parameter           0xC001046A
%SYM%   member      VL_CAL_UNIT_2     variable-list       0xC001046B
%TXT%   variable    __cal_unit_2      enumerated          0x8002046A
%IMP%   VARIABLE    __cal_unit_2
**********************************************************************
*/
VARIABLE    __cal_unit_2
{
    LABEL           [cal_unit_2_label] ;
    HELP            [cal_unit_2_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
		__UNITS_CODES2
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_2             (DS-65)
%SYM%   member      PRIMARY_VALUE_2        parameter        0xC001046C
%SYM%   member      VL_PRIMARY_VALUE_2     variable-list    0xC001046D
%TXT%   record      __primary_value_2                       0x8002046C
%IMP%   RECORD      __primary_value_2
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __float_contained
**********************************************************************
*/
RECORD      __primary_value_2
{
    LABEL           [primary_value_2_label] ;
    HELP            [primary_value_2_help] ;
    MEMBERS
    {
        STATUS,     __status_contained ;
        VALUE,      __float_contained ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_range_2       (DS-68)
%SYM%   member     PRIMARY_VALUE_RANGE_2      parameter      0xC001046E
%SYM%   member     VL_PRIMARY_VALUE_RANGE_2   variable-list  0xC001046F
%TXT%   record     __primary_value_range_2                   0x8002046E
%IMP%   RECORD     __primary_value_range_2
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __primary_value_range_2
{
    LABEL           [primary_value_range_2_label] ;
    HELP            [primary_value_range_2_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_type_2
%SYM%   member      PRIMARY_VALUE_TYPE_2      parameter      0xC0010470
%SYM%   member      VL_PRIMARY_VALUE_TYPE_2   variable-list  0xC0010471
%TXT%   variable    __primary_value_type_2    enumerated     0x80020470
%IMP%   VARIABLE    __primary_value_type_2
**********************************************************************
*/
VARIABLE    __primary_value_type_2
{
    LABEL           [primary_value_type_2_label] ;
    HELP            [primary_value_type_2_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __PRIMARY_VALUE_TYPES
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__sensor_cal_date_2
%SYM%   member      SENSOR_CAL_DATE_2       parameter        0xC0010472
%SYM%   member      VL_SENSOR_CAL_DATE_2    variable-list    0xC0010473
%TXT%   variable    __sensor_cal_date_2     date_and_time    0x80020472
%IMP%   VARIABLE    __sensor_cal_date_2
**********************************************************************
 */
VARIABLE    __sensor_cal_date_2
{
    LABEL           [sensor_cal_date_2_label] ;
    HELP            [sensor_cal_date_2_help] ;
    CLASS           CONTAINED ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_loc_2
%SYM%   member      SENSOR_CAL_LOC_2       parameter        0xC0010474
%SYM%   member      VL_SENSOR_CAL_LOC_2    variable-list    0xC0010475
%TXT%   variable    __sensor_cal_loc_2     visible          0x80020474
%IMP%   VARIABLE    __sensor_cal_loc_2
**********************************************************************
*/
VARIABLE   __sensor_cal_loc_2
  {
     LABEL           [sensor_cal_loc_2_label] ;
     HELP            [sensor_cal_loc_2_help] ;
     CLASS           CONTAINED ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

/*
**********************************************************************
__sensor_cal_method_2
%SYM%   member      SENSOR_CAL_METHOD_2       parameter       0xC0010476
%SYM%   member      VL_SENSOR_CAL_METHOD_2    variable-list   0xC0010477
%TXT%   variable    __sensor_cal_method_2     enumerated      0x80020476
%IMP%   VARIABLE    __sensor_cal_method_2
**********************************************************************
*/
VARIABLE    __sensor_cal_method_2
{
    LABEL           [sensor_cal_method_2_label] ;
    HELP            [sensor_cal_method_2_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 100,  [volume_label],             [volume_help]           },
        { 101,  [static_wght_label],        [static_wght_label]     },
        { 102,  [dync_wght_label],          [dync_wght_label]       },
        { 103,  [fac_trim_std_cal_label],   [fac_trim_std_cal_help] },
        { 104,  [user_trim_std_cal_label],  [user_trim_std_cal_help]},
        { 105,  [fac_trim_sp_cal_label],    [fac_trim_sp_cal_help]  },
        { 106,  [user_trim_sp_cal_label],   [user_trim_sp_cal_help] },
        { 255,  [other],                    [other_help]            }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_cal_who_2
%SYM%   member      SENSOR_CAL_WHO_2        parameter        0xC0010478
%SYM%   member      VL_SENSOR_CAL_WHO_2     variable-list    0xC0010479
%TXT%   variable    __sensor_cal_who_2      visible          0x80020478
%IMP%   VARIABLE    __sensor_cal_who_2
**********************************************************************
*/
VARIABLE    __sensor_cal_who_2
  {
     LABEL           [sensor_cal_who_2_label] ;
     HELP            [sensor_cal_who_2_help] ;
     CLASS           CONTAINED ;
     TYPE            VISIBLE (32) ;
     CONSTANT_UNIT   [blank] ;
     HANDLING        READ & WRITE ;
     /* RESPONSE_CODES  xxx ; */
  }

 /*
**********************************************************************
__sensor_connection_2
%SYM%   member      SENSOR_CONNECTION_2       parameter       0xC001047A
%SYM%   member      VL_SENSOR_CONNECTION_2    variable-list   0xC001047B
%TXT%   variable    __sensor_connection_2     enumerated      0x8002047A
%IMP%   VARIABLE    __sensor_connection_2
**********************************************************************
*/
VARIABLE    __sensor_connection_2
{
    LABEL           [sensor_connection_2_label] ;
    HELP            [sensor_connection_2_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 2,  [two_wires],      [two_wires_help] },
        { 3,  [three_wires],    [three_wires_help] },
        { 4,  [four_wires],     [four_wires_help] }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__sensor_range_2        (DS-68)
%SYM%   member      SENSOR_RANGE_2      parameter       0xC001047C
%SYM%   member      VL_SENSOR_RANGE_2   variable-list   0xC001037D
%TXT%   record      __sensor_range_2                    0x8002037C
%IMP%   RECORD      __sensor_range_2
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __sensor_range_2
{
    LABEL           [sensor_range_2_label] ;
    HELP            [sensor_range_2_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_sn_2
%SYM%   member      SENSOR_SN_2         parameter           0xC001047E
%SYM%   member      VL_SENSOR_SN_2      variable-list       0xC001047F
%TXT%   variable    __sensor_sn_2       visible             0x8002047E
%IMP%   VARIABLE    __sensor_sn_2
**********************************************************************
*/
VARIABLE    __sensor_sn_2
{
    LABEL           [sensor_sn_2_label] ;
    HELP            [sensor_sn_2_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sensor_type_2                           FF-903 PS1.9 Sec4.3
%SYM%   member      SENSOR_TYPE_2        parameter         0xC0010480
%SYM%   member      VL_SENSOR_TYPE_2     variable-list     0xC0010481
%TXT%   variable    __sensor_type_2      enumerated        0x80020480
%IMP%   VARIABLE    __sensor_type_2
**********************************************************************
*/
VARIABLE    __sensor_type_2
{
    LABEL           [sensor_type_2_label] ;
    HELP            [sensor_type_2_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __SENSOR_TYPES
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*** FLOW TRANSDUCER BLOCK FF-908 ***/

/*
**********************************************************************
__damping_constant
%SYM%   member      DAMPING_CONSTANT        parameter         0xC00105F0
%SYM%   member      VL_DAMPING_CONSTANT     variable-list     0x
%TXT%   variable    __damping_constant      float             0x800205F0
%IMP%   VARIABLE    __damping_constant
**********************************************************************
*/
VARIABLE    __damping_constant
{
    LABEL           [damping_constant_label] ;
    HELP            [damping_constant_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/**********************************************************************
__temperature_value           (DS-65)
%SYM%   member     TEMPERATURE_VALUE      parameter      0xC00105F1
%SYM%   member     VL_TEMPERATURE_VALUE   variable-list  0x
%TXT%   record     __temperature_value                   0x800205F1
%IMP%   RECORD     __temperature_value
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __temperature_value
{
    LABEL           [temperature_value_label] ;
    HELP            [temperature_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__temperature_value_range        (DS-68)
%SYM%   member      TEMPERATURE_VALUE_RANGE       parameter       0xC00105F2
%SYM%   member      VL_TEMPERATURE_VALUE_RANGE    variable-list   0x
%TXT%   record      __temperature_value_range                     0x800205F2
%IMP%   RECORD      __temperature_value_range
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __temperature_value_range
{
    LABEL           [temperature_value_range_label] ;
    HELP            [temperature_value_range_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX,  __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__flow_direction                       FF-903-1.9,  4.6
%SYM%   member      ACT_FLOW_DIRECTION   parameter         0xC00105F3
%SYM%   member      VL_FLOW_DIRECTION    variable-list     0x
%TXT%   variable    __flow_direction     enumerated        0x800205F3
%IMP%   VARIABLE    __flow_direction
**********************************************************************
*/
VARIABLE    __flow_direction
{
    LABEL           [flow_direction_label] ;
    HELP            [flow_direction_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [forward_label],      [forward_help]       },
        { 1,   [reverse_label],      [reverse_help]       },
        { 255, [indeterm_label],     [indeterm_help]      }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__zero_point
%SYM%   member      ZERO_POINT        parameter         0xC00105F4
%SYM%   member      VL_ZERO_POINT     variable-list     0x
%TXT%   variable    __zero_point      float             0x800205F4
%IMP%   VARIABLE    __zero_point
**********************************************************************
*/
VARIABLE    __zero_point
{
    LABEL           [zero_point_label] ;
    HELP            [zero_point_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__set_zero_point                       FF-903-1.9,  4.6
%SYM%   member      SET_ZERO_POINT       parameter         0xC00105F5
%SYM%   member      VL_SET_ZERO_POINT    variable-list     0x
%TXT%   variable    __set_zero_point     enumerated        0x800205F5
%IMP%   VARIABLE    __set_zero_point
**********************************************************************
*/
VARIABLE    __set_zero_point
{
    LABEL           [set_zero_point_label] ;
    HELP            [set_zero_point_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [not_activated_label],   [not_activated_help]       },
        { 1,   [activated_label],       [activated_help]        },
        { 2,   [reserved_label],        [reserved_help]    },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [reserved_label],        [reserved_help]    },
        { 9,   [reserved_label],        [reserved_help]    },
        { 255, [indeterm_label],        [indeterm_help]         }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__primary_value_low_cut_off
%SYM%   member     PRIMARY_VALUE_LOW_CUT_OFF     parameter     0xC00105F6
%SYM%   member     VL_PRIMARY_VALUE_LOW_CUT_OFF  variable-list 0x
%TXT%   variable   __primary_value_cutoff_lo   float         0x800205F6
%IMP%   VARIABLE   __primary_value_cutoff_lo
**********************************************************************
*/
VARIABLE    __primary_value_low_cut_off
{
    LABEL           [primary_value_low_cut_off_label] ;
    HELP            [primary_value_low_cut_off_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__secondary_value_low_cut_off
%SYM%   member     SECONDARY_VALUE_LOW_CUT_OFF     parameter     0xC00105F7
%SYM%   member     VL_SECONDARY_VALUE_LOW_CUT_OFF  variable-list 0x
%TXT%   variable   __secondary_value_low_cut_off   float         0x800205F7
%IMP%   VARIABLE   __secondary_value_low_cut_off
**********************************************************************
*/
VARIABLE    __secondary_value_low_cut_off
{
    LABEL           [secondary_value_low_cut_off_label] ;
    HELP            [secondary_value_low_cut_off_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__density_constant
%SYM%   member      DENSITY_CONSTANT        parameter         0xC00105F8
%SYM%   member      VL_DENSITY_CONSTANT     variable-list     0x
%TXT%   variable    __density_constant      float             0x800205F8
%IMP%   VARIABLE    __density_constant
**********************************************************************
*/
VARIABLE    __density_constant
{
    LABEL           [density_constant_label] ;
    HELP            [density_constant_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__density_constant_units
%SYM%   member     DENSITY_CONSTANT_UNITS      parameter      0xC00105F9
%SYM%   member     VL_DENSITY_CONSTANT_UNITS   variable-list  0x
%TXT%   variable   __density_constant_units    enumerated     0x800205F9
%IMP%   VARIABLE   __density_constant_units
**********************************************************************
*/
VARIABLE    __density_constant_units
{
    LABEL           [density_constant_units_label] ;
    HELP            [density_constant_units_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__viscosity_constant
%SYM%   member      VISCOSITY_CONSTANT        parameter         0xC00105FA
%SYM%   member      VL_VISCOSITY_CONSTANT     variable-list     0x
%TXT%   variable    __viscosity_constant      float             0x800205FA
%IMP%   VARIABLE    __viscosity_constant
**********************************************************************
*/
VARIABLE    __viscosity_constant
{
    LABEL           [viscosity_constant_label] ;
    HELP            [viscosity_constant_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__viscosity_constant_units
%SYM%   member     VISCOSITY_CONSTANT_UNITS      parameter      0xC00105FB
%SYM%   member     VL_VISCOSITY_CONSTANT_UNITS   variable-list  0x
%TXT%   variable   __viscosity_constant_units    enumerated     0x800205FB
%IMP%   VARIABLE   __viscosity_constant_units
**********************************************************************
*/
VARIABLE    __viscosity_constant_units
{
    LABEL           [viscosity_constant_units_label] ;
    HELP            [viscosity_constant_units_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__tube_diameter_constant
%SYM%   member      TUBE_DIAMETER_CONSTANT        parameter         0xC00105FC
%SYM%   member      VL_TUBE_DIAMETER_CONSTANT     variable-list     0x
%TXT%   variable    __tube_diameter_constant      float             0x800205FC
%IMP%   VARIABLE    __tube_diameter_constant
**********************************************************************
*/
VARIABLE    __tube_diameter_constant
{
    LABEL           [tube_diameter_constant_label] ;
    HELP            [tube_diameter_constant_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__tube_diameter_units
%SYM%   member     TUBE_DIAMETER_UNITS      parameter      0xC00105FD
%SYM%   member     VL_TUBE_DIAMETER_UNITS   variable-list  0x
%TXT%   variable   __tube_diameter_units    enumerated     0x800205FD
%IMP%   VARIABLE   __tube_diameter_units
**********************************************************************
*/
VARIABLE    __tube_diameter_units
{
    LABEL           [tube_diameter_units_label] ;
    HELP            [tube_diameter_units_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__magmeter_coil_frequency
%SYM%   member      MAGMETER_COIL_FREQUENCY        parameter         0xC00105FE
%SYM%   member      VL_MAGMETER_COIL_FREQUENCY     variable-list     0x
%TXT%   variable    __magmeter_coil_frequency      float             0x800205FE
%IMP%   VARIABLE    __magmeter_coil_frequency
**********************************************************************
*/
VARIABLE    __magmeter_coil_frequency
{
    LABEL           [magmeter_coil_frequency_label] ;
    HELP            [magmeter_coil_frequency_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [Hz] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vortex_shedding_frequency
%SYM%   member      VORTEX_SHEDDING_FREQUENCY        parameter         0xC00105FF
%SYM%   member      VL_VORTEX_SHEDDING_FREQUENCY     variable-list     0x
%TXT%   variable    __vortex_shedding_frequency      float             0x800205FF
%IMP%   VARIABLE    __vortex_shedding_frequency
**********************************************************************
*/
VARIABLE    __vortex_shedding_frequency
{
    LABEL           [vortex_shedding_frequency_label] ;
    HELP            [vortex_shedding_frequency_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [Hz] ;    
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sound_velocity
%SYM%   member      SOUND_VELOCITY        parameter         0xC0010600
%SYM%   member      VL_SOUND_VELOCITY     variable-list     0x
%TXT%   variable    __sound_velocity      float             0x80020600
%IMP%   VARIABLE    __sound_velocity
**********************************************************************
*/
VARIABLE    __sound_velocity
{
    LABEL           [sound_velocity_label] ;
    HELP            [sound_velocity_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sound_velocity_units
%SYM%   member     SOUND_VELOCITY_UNITS      parameter      0xC0010601
%SYM%   member     VL_SOUND_VELOCITY_UNITS   variable-list  0x
%TXT%   variable   __sound_velocity_units    enumerated     0x80020601
%IMP%   VARIABLE   __sound_velocity_units
**********************************************************************
*/
VARIABLE    __sound_velocity_units
{
    LABEL           [sound_velocity_units_label] ;
    HELP            [sound_velocity_units_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*** END FLOW ***/

/*** Totalizer Parameters FF-908 ***/

/*
FAIL_SAFE_OPTION 
BATCH_CONTROL
TOTALIZER_MODE 
TOTALIZER_OPTION 
TOTALIZER_SELECT
*/

/*** END TOTALIZER ***/

/*** Positioner Transducer FF-906 ***/

/*
**********************************************************************
__closed_pos_deadband
%SYM%   member      CLOSED_POS_DEADBAND        parameter         0xC0010531
%SYM%   member      VL_CLOSED_POS_DEADBAND     variable-list     0x
%TXT%   variable    __closed_pos_deadband      float             0x80020531
%IMP%   VARIABLE    __closed_pos_deadband
**********************************************************************
*/
VARIABLE    __closed_pos_deadband
{
    LABEL           [closed_pos_deadband_label] ;
    HELP            [closed_pos_deadband_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__characterization
%SYM%   member      CHARACTERIZATION         parameter           0xC0010530
%SYM%   member      VL_CHARACTERIZATION      variable-list       0x
%TXT%   variable    __characterization       enumerated          0x80020530
%IMP%   VARIABLE    __characterization
**********************************************************************
*/
VARIABLE    __characterization
{
    LABEL           [characterization_label] ;
    HELP            [characterization_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [linear_label],          [linear_help]       },
        { 1,   [percent_label],         [percent_help]        },
        { 2,   [quick_opening_label],   [quick_opening_help]    },
        { 3,   [custom_label],          [custom_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__closed_pos_shift
%SYM%   member      CLOSED_POS_SHIFT        parameter         0xC0010532
%SYM%   member      VL_CLOSED_POS_SHIFT     variable-list     0x
%TXT%   variable    __closed_pos_shift      float             0x80020532
%IMP%   VARIABLE    __closed_pos_shift
**********************************************************************
*/
VARIABLE    __closed_pos_shift
{
    LABEL           [closed_pos_shift_label] ;
    HELP            [closed_pos_shift_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cycle_cntr_deadband
%SYM%   member      CYCLE_CNTR_DEADBAND        parameter         0xC0010534
%SYM%   member      VL_CYCLE_CNTR_DEADBAND     variable-list     0x
%TXT%   variable    __cycle_cntr_deadband      float             0x80020534
%IMP%   VARIABLE    __cycle_cntr_deadband
**********************************************************************
*/
VARIABLE    __cycle_cntr_deadband
{
    LABEL           [cycle_cntr_deadband_label] ;
    HELP            [cycle_cntr_deadband_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cycle_cntr
%SYM%   member      CYCLE_CNTR         parameter           0xC0010533
%SYM%   member      VL_CYCLE_CNTR      variable-list       0x
%TXT%   variable    __cycle_cntr       unsigned            0x80020533
%IMP%   VARIABLE    __cycle_cntr
**********************************************************************
*/
VARIABLE    __cycle_cntr
{
    LABEL           [cycle_cntr_label] ;
    HELP            [cycle_cntr_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cycle_cntr_lim
%SYM%   member      CYCLE_CNTR_LIM         parameter           0xC0010535
%SYM%   member      VL_CYCLE_CNTR_LIM      variable-list       0x
%TXT%   variable    __cycle_cntr_lim       unsigned            0x80020535
%IMP%   VARIABLE    __cycle_cntr_lim
**********************************************************************
*/
VARIABLE    __cycle_cntr_lim
{
    LABEL           [cycle_cntr_lim_label] ;
    HELP            [cycle_cntr_lim_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__deviation_deadband
%SYM%   member      DEVIATION_DEADBAND        parameter         0xC0010536
%SYM%   member      VL_DEVIATION_DEADBAND     variable-list     0x
%TXT%   variable    __deviation_deadband      float             0x80020536
%IMP%   VARIABLE    __deviation_deadband
**********************************************************************
*/
VARIABLE    __deviation_deadband
{
    LABEL           [deviation_deadband_label] ;
    HELP            [deviation_deadband_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__deviation_time
%SYM%   member      DEVIATION_TIME        parameter         0xC0010537
%SYM%   member      VL_DEVIATION_TIME     variable-list     0x
%TXT%   variable    __deviation_time      float             0x80020537
%IMP%   VARIABLE    __deviation_time
**********************************************************************
*/
VARIABLE    __deviation_time
{
    LABEL           [deviation_time_label] ;
    HELP            [deviation_time_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__deviation_value
%SYM%   member      DEVIATION_VALUE        parameter         0xC0010538
%SYM%   member      VL_DEVIATION_VALUE     variable-list     0x
%TXT%   variable    __deviation_value      float             0x80020538
%IMP%   VARIABLE    __deviation_value
**********************************************************************
*/
VARIABLE    __deviation_value
{
    LABEL           [deviation_value_label] ;
    HELP            [deviation_value_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__friction_units
%SYM%   member      FRICTION_UNITS         parameter           0xC0010539
%SYM%   member      VL_FRICTION_UNITS      variable-list       0x
%TXT%   variable    __friction_units       enumerated          0x80020539
%IMP%   VARIABLE    __friction_units
**********************************************************************
*/
VARIABLE    __friction_units
{
    LABEL           [friction_units_label] ;
    HELP            [friction_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__friction
%SYM%   member      FRICTION        parameter         0xC001053A
%SYM%   member      VL_FRICTION     variable-list     0x
%TXT%   variable    __friction      float             0x8002053A
%IMP%   VARIABLE    __friction
**********************************************************************
*/
VARIABLE    __friction
{
    LABEL           [friction_label] ;
    HELP            [friction_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__fst_breakout_timeout
%SYM%   member      FST_BREAKOUT_TIMEOUT        parameter         0xC001173E
%SYM%   member      VL_FST_BREAKOUT_TIMEOUT     variable-list     0xC001173F
%TXT%   variable    __fst_breakout_timeout      float             0x800204E7
%IMP%   VARIABLE    __fst_breakout_timeout
**********************************************************************
*/
VARIABLE    __fst_breakout_timeout
{
    LABEL           [fst_breakout_timeout_label] ;
    HELP            [fst_breakout_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fst_breakout_time
%SYM%   member      FST_BREAKOUT_TIME        parameter         0xC001053B
%SYM%   member      VL_FST_BREAKOUT_TIME     variable-list     0x
%TXT%   variable    __fst_breakout_time      float             0x8002053B
%IMP%   VARIABLE    __fst_breakout_time
**********************************************************************
*/
VARIABLE    __fst_breakout_time
{
    LABEL           [fst_breakout_time_label] ;
    HELP            [fst_breakout_time_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__fst_ramp_rate
%SYM%   member      FST_RAMP_RATE        parameter         0xC001053C
%SYM%   member      VL_FST_RAMP_RATE     variable-list     0x
%TXT%   variable    __fst_ramp_rate      float             0x8002053C
%IMP%   VARIABLE    __fst_ramp_rate
**********************************************************************
*/
VARIABLE    __fst_ramp_rate
{
    LABEL           [fst_ramp_rate_label] ;
    HELP            [fst_ramp_rate_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent_per_sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__fst_strk_trav_timeout
%SYM%   member      FST_STRK_TRAV_TIMEOUT        parameter         0xC0011740
%SYM%   member      VL_FST_STRK_TRAV_TIMEOUT     variable-list     0xC0011741
%TXT%   variable    __fst_strk_trav_timeout      float             0x8002053D
%IMP%   VARIABLE    __fst_strk_trav_timeout
**********************************************************************
*/
VARIABLE    __fst_strk_trav_timeout
{
    LABEL           [fst_strk_trav_timeout_label] ;
    HELP            [fst_strk_trav_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__fst_completion_timeout
%SYM%   member      FST_COMPLETION_TIMEOUT        parameter         0xC0011742
%SYM%   member      VL_FST_COMPLETION_TIMEOUT     variable-list     0xC0011743
%TXT%   variable    __fst_completion_timeout      float             0x8002053E
%IMP%   VARIABLE    __fst_completion_timeout
**********************************************************************
*/
VARIABLE    __fst_completion_timeout
{
    LABEL           [fst_completion_timeout_label] ;
    HELP            [fst_completion_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__hysterisis
%SYM%   member      HYSTERISIS        parameter         0xC001053F
%SYM%   member      VL_HYSTERISIS     variable-list     0x
%TXT%   variable    __hysterisis      float             0x8002053F
%IMP%   VARIABLE    __hysterisis
**********************************************************************
*/
VARIABLE    __hysterisis
{
    LABEL           [hysterisis_label] ;
    HELP            [hysterisis_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__internal_temp_units
%SYM%   member      INTERNAL_TEMP_UNITS         parameter           0xC0010540
%SYM%   member      VL_INTERNAL_TEMP_UNITS      variable-list       0x
%TXT%   variable    __internal_temp_units       enumerated          0x80020540
%IMP%   VARIABLE    __internal_temp_units
**********************************************************************
*/
VARIABLE    __internal_temp_units
{
    LABEL           [internal_temp_units_label] ;
    HELP            [internal_temp_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__internal_temp
%SYM%   member      INTERNAL_TEMP        parameter         0xC001056D
%SYM%   member      VL_INTERNAL_TEMP     variable-list     0x
%TXT%   variable    __internal_temp      float             0x8002056D
%IMP%   VARIABLE    __internal_temp
**********************************************************************
*/
VARIABLE    __internal_temp
{
    LABEL           [internal_temp_label] ;
    HELP            [internal_temp_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stroke_time_close_lim
%SYM%   member      STROKE_TIME_CLOSE_LIM        parameter         0xC0010541
%SYM%   member      VL_STROKE_TIME_CLOSE_LIM     variable-list     0xC0011746
%TXT%   variable    __stroke_time_close_lim      float             0xC0011747
%IMP%   VARIABLE    __stroke_time_close_lim
**********************************************************************
*/
VARIABLE    __stroke_time_close_lim
{
    LABEL           [stroke_time_close_lim_label] ;
    HELP            [stroke_time_close_lim_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__stroke_time_open_lim
%SYM%   member      STROKE_TIME_OPEN_LIM        parameter         0xC0011748
%SYM%   member      VL_STROKE_TIME_OPEN_LIM     variable-list     0xC0011749
%TXT%   variable    __stroke_time_open_lim      float             0x800204E9
%IMP%   VARIABLE    __stroke_time_open_lim
**********************************************************************
*/
VARIABLE    __stroke_time_open_lim
{
    LABEL           [stroke_time_open_lim_label] ;
    HELP            [stroke_time_open_lim_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__internal_temp_min
%SYM%   member      INTERNAL_TEMP_MIN        parameter         0xC001174C
%SYM%   member      VL_INTERNAL_TEMP_MIN     variable-list     0xC001174C
%TXT%   variable    __internal_temp_min      float             0x800204EA
%IMP%   VARIABLE    __internal_temp_min
**********************************************************************
*/
VARIABLE    __internal_temp_min
{
    LABEL           [internal_temp_min_label] ;
    HELP            [internal_temp_min_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__internal_temp_max
%SYM%   member      INTERNAL_TEMP_MAX        parameter         0xC001174E
%SYM%   member      VL_INTERNAL_TEMP_MAX     variable-list     0xC001174F
%TXT%   variable    __internal_temp_max      float             0x800204BE
%IMP%   VARIABLE    __internal_temp_max
**********************************************************************
*/
VARIABLE    __internal_temp_max
{
    LABEL           [internal_temp_max_label] ;
    HELP            [internal_temp_max_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__pressure_port_a
%SYM%   member      PRESSURE_PORT_A        parameter         0xC0010548
%SYM%   member      VL_PRESSURE_PORT_A     variable-list     0x
%TXT%   variable    __pressure_port_a      float             0x80020548
%IMP%   VARIABLE    __pressure_port_a
**********************************************************************
*/
VARIABLE    __pressure_port_a
{
    LABEL           [pressure_port_a_label] ;
    HELP            [pressure_port_a_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__pressure_port_b
%SYM%   member      PRESSURE_PORT_B        parameter         0xC0010549
%SYM%   member      VL_PRESSURE_PORT_B     variable-list     0x
%TXT%   variable    __pressure_port_b      float             0x80020549
%IMP%   VARIABLE    __pressure_port_b
**********************************************************************
*/
VARIABLE    __pressure_port_b
{
    LABEL           [pressure_port_b_label] ;
    HELP            [pressure_port_b_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__pos_alert_hi
%SYM%   member      POS_ALERT_HI        parameter         0xC0010543
%SYM%   member      VL_POS_ALERT_HI     variable-list     0x
%TXT%   variable    __pos_alert_hi      float             0x80020543
%IMP%   VARIABLE    __pos_alert_hi
**********************************************************************
*/
VARIABLE    __pos_alert_hi
{
    LABEL           [pos_alert_hi_label] ;
    HELP            [pos_alert_hi_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;  
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__pos_alert_lo
%SYM%   member      POS_ALERT_LO        parameter         0xC0010544
%SYM%   member      VL_POS_ALERT_LO     variable-list     0x
%TXT%   variable    __pos_alert_hi      float             0x80020544
%IMP%   VARIABLE    __pos_alert_hi
**********************************************************************
*/
VARIABLE    __pos_alert_lo
{
    LABEL           [pos_alert_lo_label] ;
    HELP            [pos_alert_lo_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__pos_deadband
%SYM%   member      POS_DEADBAND        parameter         0xC0010545
%SYM%   member      VL_POS_DEADBAND     variable-list     0x
%TXT%   variable    __pos_deadband      float             0x80020545
%IMP%   VARIABLE    __pos_deadband
**********************************************************************
*/
VARIABLE    __pos_deadband
{
    LABEL           [pos_deadband_label] ;
    HELP            [pos_deadband_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pos_features
%SYM%   member      POS_FEATURES         parameter           0xC0011726
%SYM%   member      VL_POS_FEATURES      variable-list       0xC0011727
%TXT%   variable    __pos_features       bit-enumerated      0x80021744
%IMP%   VARIABLE    __pos_features
**********************************************************************
*/
VARIABLE    __pos_features
{
    LABEL           [pos_features_label] ;
    HELP            [pos_features_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,	[pos_features_0],	[pos_features_0_help] },
        { 0x0002,	[pos_features_1],	[pos_features_1_help] },
        { 0x0004,	[pos_features_2],	[pos_features_2_help] },
        { 0x0008,	[pos_features_3],	[pos_features_3_help] },
        { 0x0010,	[pos_features_4],	[pos_features_4_help] },
        { 0x0020,	[pos_features_5],	[pos_features_5_help] },
        { 0x0040,	[pos_features_6],	[pos_features_6_help] },
        { 0x0080,	[pos_features_7],	[pos_features_7_help] },
        { 0x0100,	[pos_features_8],	[pos_features_8_help] },
        { 0x0200,	[pos_features_9],	[pos_features_9_help] },
        { 0x0400,	[pos_features_10],	[pos_features_10_help] },
        { 0x0800,	[pos_features_11],	[pos_features_11_help] }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_breakout_time
%SYM%   member      PST_BREAKOUT_TIME        parameter         0xC001054A
%SYM%   member      VL_PST_BREAKOUT_TIME     variable-list     0x
%TXT%   variable    __pst_breakout_time      float             0x8002054A
%IMP%   VARIABLE    __pst_breakout_time
**********************************************************************
*/
VARIABLE    __pst_breakout_time
{
    LABEL           [pst_breakout_time_label] ;
    HELP            [pst_breakout_time_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_breakout_timeout
%SYM%   member      PST_BREAKOUT_TIMEOUT        parameter         0xC0011736
%SYM%   member      VL_PST_BREAKOUT_TIMEOUT     variable-list     0xC0011737
%TXT%   variable    __pst_breakout_timeout      float             0x8002054A
%IMP%   VARIABLE    __pst_breakout_timeout
**********************************************************************
*/
VARIABLE    __pst_breakout_timeout
{
    LABEL           [pst_breakout_timeout_label] ;
    HELP            [pst_breakout_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_initial_start_time
%SYM%   member      PST_INITIAL_START_TIME       parameter        0xC001054B
%SYM%   member      VL_PST_INITIAL_START_TIME    variable-list    0x
%TXT%   variable    __pst_initial_start_time     date_and_time    0x8002054B
%IMP%   VARIABLE    __pst_initial_start_time
**********************************************************************
 */
VARIABLE    __pst_initial_start_time
{
    LABEL           [pst_initial_start_time_label] ;
    HELP            [pst_initial_start_time_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_interval
%SYM%   member      PST_INTERVAL        parameter         0xC001054C
%SYM%   member      VL_PST_INTERVAL     variable-list     0x
%TXT%   variable    __pst_interval      float             0x8002054C
%IMP%   VARIABLE    __pst_interval
**********************************************************************
*/
VARIABLE    __pst_interval
{
    LABEL           [pst_interval_label] ;
    HELP            [pst_interval_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_options
%SYM%   member      PST_OPTIONS        parameter         0xC001056A
%SYM%   member      VL_PST_OPTIONS     variable-list     0x
%TXT%   variable    __pst_options      enumerated        0x8002056A
%IMP%   VARIABLE    __pst_options
**********************************************************************
*/
VARIABLE    __pst_options
{
    LABEL           [pst_options_label] ;
    HELP            [pst_options_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        { 0,   [freeze_analog_label],   [freeze_analog_help]       },
        { 1,   [freeze_discrete_label], [freeze_discrete_help]        },
        { 2,   [reserved_label],        [reserved_help]    },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],        [mfg_specific_help]    },
        { 9,   [mfg_specific_label],        [mfg_specific_help]    },
        { 10,  [mfg_specific_label],        [mfg_specific_help]    },
        { 11,  [mfg_specific_label],        [mfg_specific_help]    },
        { 12,  [mfg_specific_label],        [mfg_specific_help]    },
        { 13,  [mfg_specific_label],        [mfg_specific_help]    },
        { 14,  [mfg_specific_label],        [mfg_specific_help]    },
        { 15,  [mfg_specific_label],        [mfg_specific_help]    },
        { 255, [indeterm_label],        [indeterm_help]         }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_ramp_rate
%SYM%   member      PST_RAMP_RATE        parameter         0xC001054D
%SYM%   member      VL_PST_RAMP_RATE     variable-list     0x
%TXT%   variable    __pst_ramp_rate      float             0x8002054D
%IMP%   VARIABLE    __pst_ramp_rate
**********************************************************************
*/
VARIABLE    __pst_ramp_rate
{
    LABEL           [pst_ramp_rate_label] ;
    HELP            [pst_ramp_rate_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent_per_sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_strk_trav
%SYM%   member      PST_STRK_TRAV        parameter         0xC0011738
%SYM%   member      VL_PST_STRE_TRAV     variable-list     0xC0011739
%TXT%   variable    __pst_strk_trav      float             0x8002054E
%IMP%   VARIABLE    __pst_strk_trav
**********************************************************************
*/
VARIABLE    __pst_strk_trav
{
    LABEL           [pst_strk_trav_label] ;
    HELP            [pst_strk_trav_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_strk_trav_timeout
%SYM%   member      PST_STRK_TRAV_TIMEOUT        parameter         0xC001173A
%SYM%   member      VL_PST_STRK_TRAV_TIMEOUT     variable-list     0xC001173B
%TXT%   variable    __pst_strk_trav_timeout      float             0x8002054F
%IMP%   VARIABLE    __pst_strk_trav_timeout
**********************************************************************
*/
VARIABLE    __pst_strk_trav_timeout
{
    LABEL           [pst_strk_trav_timeout_label] ;
    HELP            [pst_strk_trav_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_completion_timeout
%SYM%   member      PST_COMPLETION_TIMEOUT        parameter         0xC001173C
%SYM%   member      VL_PST_COMPLETION_TIMEOUT     variable-list     0xC001173D
%TXT%   variable    __pst_completion_timeout      float             0x80020550
%IMP%   VARIABLE    __pst_completion_timeout
**********************************************************************
*/
VARIABLE    __pst_completion_timeout
{
    LABEL           [pst_completion_timeout_label] ;
    HELP            [pst_completion_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__rated_travel
%SYM%   member      RATED_TRAVEL        parameter         0xC0010551
%SYM%   member      VL_RATED_TRAVEL     variable-list     0x
%TXT%   variable    __rated_travel      float             0x80020551
%IMP%   VARIABLE    __rated_travel
**********************************************************************
*/
VARIABLE    __rated_travel
{
    LABEL           [rated_travel_label] ;
    HELP            [rated_travel_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__stop_hi
%SYM%   member      STOP_HI        parameter         0xC0010554
%SYM%   member      VL_STOP_HI     variable-list     0x
%TXT%   variable    __stop_hi      float             0x80020554
%IMP%   VARIABLE    __stop_hi
**********************************************************************
*/
VARIABLE    __stop_hi
{
    LABEL           [stop_hi_label] ;
    HELP            [stop_hi_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__stop_lo
%SYM%   member      STOP_LO        parameter         0xC0010555
%SYM%   member      VL_STOP_LO     variable-list     0x
%TXT%   variable    __stop_lo      float             0x80020555
%IMP%   VARIABLE    __stop_lo
**********************************************************************
*/
VARIABLE    __stop_lo
{
    LABEL           [stop_lo_label] ;
    HELP            [stop_lo_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stroke_time_closed
%SYM%   member      STROKE_TIME_CLOSED        parameter         0xC0010556
%SYM%   member      VL_STROKE_TIME_CLOSED     variable-list     0x
%TXT%   variable    __stroke_time_closed      float             0x80020556
%IMP%   VARIABLE    __stroke_time_closed
**********************************************************************
*/
VARIABLE    __stroke_time_closed
{
    LABEL           [stroke_time_closed_label] ;
    HELP            [stroke_time_closed_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stroke_time_open
%SYM%   member      STROKE_TIME_OPEN        parameter         0xC0010557
%SYM%   member      VL_STROKE_TIME_OPEN     variable-list     0x
%TXT%   variable    __stroke_time_open      float             0x80020557
%IMP%   VARIABLE    __stroke_time_open
**********************************************************************
*/
VARIABLE    __stroke_time_open
{
    LABEL           [stroke_time_open_label] ;
    HELP            [stroke_time_open_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pressure_supply
%SYM%   member      PRESSURE _SUPPLY        parameter         0xC0010547
%SYM%   member      VL_PRESSURE _SUPPLY     variable-list     0x
%TXT%   variable    __pressure_supply       float             0x80020547
%IMP%   VARIABLE    __pressure_supply
**********************************************************************
*/
VARIABLE    __pressure_supply
{
    LABEL           [pressure_supply_label] ;
    HELP            [pressure_supply_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__torque_units
%SYM%   member      TORQUE_UNITS         parameter           0xC0010558
%SYM%   member      VL_TORQUE_UNITS      variable-list       0x
%TXT%   variable    __torque_units       enumerated          0x80020558
%IMP%   VARIABLE    __torque_units
**********************************************************************
*/
VARIABLE    __torque_units
{
    LABEL           [torque_units_label] ;
    HELP            [torque_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__torque
%SYM%   member      TORQUE        parameter         0xC0010559
%SYM%   member      VL_TORQUE     variable-list     0x
%TXT%   variable    __torque      float             0x80020559
%IMP%   VARIABLE    __torque
**********************************************************************
*/
VARIABLE    __torque
{
    LABEL           [torque_label] ;
    HELP            [torque_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__travel_accum_deadband
%SYM%   member      TRAVEL_ACCUM_DEADBAND        parameter         0xC001055A
%SYM%   member      VL_TRAVEL_ACCUM_DEADBAND     variable-list     0x
%TXT%   variable    __travel_accum_deadband      float             0x8002055A
%IMP%   VARIABLE    __travel_accum_deadband
**********************************************************************
*/
VARIABLE    __travel_accum_deadband
{
    LABEL           [travel_accum_deadband_label] ;
    HELP            [travel_accum_deadband_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__travel_accum_lim
%SYM%   member      TRAVEL_ACCUM_LIM        parameter         0xC001055C
%SYM%   member      VL_TRAVEL_ACCUM_LIM     variable-list     0x
%TXT%   variable    __travel_accum_lim      float             0x8002055C
%IMP%   VARIABLE    __travel_accum_lim
**********************************************************************
*/
VARIABLE    __travel_accum_lim
{
    LABEL           [travel_accum_lim_label] ;
    HELP            [travel_accum_lim_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__travel_units
%SYM%   member     TRAVEL_UNITS      parameter      0xC001055D
%SYM%   member     VL_TRAVEL_UNITS   variable-list  0x
%TXT%   variable   __travel_units    enumerated     0x8002055D
%IMP%   VARIABLE   __travel_units
**********************************************************************
*/
VARIABLE    __travel_units
{
    LABEL           [travel_units_label] ;
    HELP            [travel_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__travel_accum_units
%SYM%   member     TRAVEL_ACCUM_UNITS      parameter      0xC001174A
%SYM%   member     VL_TRAVEL_ACCUM_UNITS   variable-list  0xC001174B
%TXT%   variable   __travel_accum_units    enumerated     0x80021735
%IMP%   VARIABLE   __travel_accum_units
**********************************************************************
*/
VARIABLE    __travel_accum_units
{
    LABEL           [travel_accum_units_label] ;
    HELP            [travel_accum_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
                __UNITS_CODES2
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__trip_timeout
%SYM%   member      TRIP_TIMEOUT        parameter         0xC001055E
%SYM%   member      VL_TRIP_TIMEOUT     variable-list     0x
%TXT%   variable    __trip_timeout      float             0x8002055E
%IMP%   VARIABLE    __trip_timeout
**********************************************************************
*/
VARIABLE    __trip_timeout
{
    LABEL           [trip_timeout_label] ;
    HELP            [trip_timeout_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vst_command
%SYM%   member      VST_COMMAND         parameter           0xC001055F
%SYM%   member      VL_VST_COMMAND      variable-list       0x
%TXT%   variable    __vst_command       enumerated          0x8002055F
%IMP%   VARIABLE    __vst_command
**********************************************************************
*/
VARIABLE    __vst_command
{
    LABEL           [vst_command_label] ;
    HELP            [vst_command_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1) 
    {
        { 0,   [uninitialized],   [uninitialized_help]       },
        { 1,   [execute_vst_ref_label], [execute_vst_ref_exceeded_help]        },
        { 2,   [execute_vst_cur_exceeded_label], [execute_vst_cur_help]    },
        { 3,   [abort_stroke_test_label],  [abort_stroke_test_help]    },
        { 4,   [reset_vst_label],        [reset_vst_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_detailed_result
%SYM%   member      PST_DETAILED_RESULT        record          0xC001056B
%TXT%   variable    __pst_detailed_result      enumerated      0x8002056B
%IMP%   VARIABLE    __pst_detailed_result
**********************************************************************
*/

VARIABLE    __pst_detailed_result
{
    LABEL           [pst_detailed_result_label] ;
    HELP            [pst_detailed_result_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        { 0,   [test_cmd_rejected_label],   [test_cmd_rejected_help]       },
        { 1,   [time_limit_exceeded_label], [time_limit_exceeded_help]        },
        { 2,   [pres_limit_exceeded_label], [pres_limit_exceeded_help]    },
        { 3,   [friction_limit_exceeded_label],  [friction_limit_exceeded_help]    },
        { 4,   [pst_travel_limit_exceeded_label],        [pst_travel_limit_exceeded_help]    },
        { 5,   [overridden_label],        [overridden_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 255, [indeterm_label],        [indeterm_help]         }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fst_detailed_result
%SYM%   member      FST_DETAILED_RESULT        record          0xC001056B
%TXT%   variable    __fst_detailed_result      enumerated      0x8002056B
%IMP%   VARIABLE    __fst_detailed_result
**********************************************************************
*/

VARIABLE    __fst_detailed_result
{
    LABEL           [fst_detailed_result_label] ;
    HELP            [fst_detailed_result_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        { 0,   [test_cmd_rejected_label],   [test_cmd_rejected_help]       },
        { 1,   [time_limit_exceeded_label], [time_limit_exceeded_help]        },
        { 2,   [pres_limit_exceeded_label], [pres_limit_exceeded_help]    },
        { 3,   [friction_limit_exceeded_label],  [friction_limit_exceeded_help]    },
        { 4,   [pst_travel_limit_exceeded_label],        [pst_travel_limit_exceeded_help]    },
        { 5,   [overridden_label],        [overridden_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 255, [indeterm_label],        [indeterm_help]         }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vst_mode
%SYM%   member      VST_MODE         parameter           0xC0010560
%SYM%   member      VL_VST_MODE      variable-list       0x
%TXT%   variable    __vst_mode       unsigned            0x80020560
%IMP%   VARIABLE    __vst_mode
**********************************************************************
*/
VARIABLE    __vst_mode
{
    LABEL           [vst_mode_label] ;
    HELP            [vst_mode_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1) 
    {
        { 0,   [disabled],              [disabled_help]      },
        { 1,   [PST_for_ESD_label],     [PST_for_ESD_help]   },
        { 2,   [FST_for_ESD_label],     [FST_for_ESD_help]   },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pst_pause
%SYM%   member      PST_PAUSE        parameter         0xC0010561
%SYM%   member      VL_PST_PAUSE     variable-list     0x
%TXT%   variable    __pst_pause      float             0x80020561
%IMP%   VARIABLE    __pst_pause
**********************************************************************
*/
VARIABLE    __pst_pause
{
    LABEL           [pst_pause_label] ;
    HELP            [pst_pause_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fst_pause
%SYM%   member      FST_PAUSE        parameter         0xC001
%SYM%   member      VL_FST_PAUSE     variable-list     0x
%TXT%   variable    __fst_pause      float             0x8002
%IMP%   VARIABLE    __fst_pause
**********************************************************************
*/
VARIABLE    __fst_pause
{
    LABEL           [fst_pause_label] ;
    HELP            [fst_pause_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;    
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vst_result
%SYM%   member      XD_VST_RESULT        parameter      0xC0010562
%SYM%   member      VL_VST_RESULT     variable-list     0x
%TXT%   variable    __vst_result      enumerated        0x80020562
%IMP%   VARIABLE    __vst_result
**********************************************************************
*/
VARIABLE    __vst_result
{
    LABEL           [vst_result_label] ;
    HELP            [vst_result_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            ENUMERATED (1) 
    {
        { 0,   [no_initial_results_label],        [no_initial_results_help]      },
        { 1,   [last_vst_successful_label],     [last_vst_successful_help]   },
        { 2,   [last_vst_failed_label],     [last_vst_failed_help]   }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__working_pos           (DS-65)
%SYM%   member     WORKING_POS      parameter      0xC0010563
%SYM%   member     VL_WORKING_POS   variable-list  0x
%TXT%   record     __working_pos                   0x80020563
%IMP%   RECORD     __working_pos
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __working_pos
{
    LABEL           [working_pos_label] ;
    HELP            [working_pos_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__readback_select
%SYM%   member      READBACK_SELECT         parameter           0xC0010552
%SYM%   member      VL_READBACK_SELECT      variable-list       0x
%TXT%   variable    __readback_select       enumerated          0x80020552
%IMP%   VARIABLE    __readback_select
**********************************************************************
*/
VARIABLE    __readback_select
{
    LABEL           [readback_select_label] ;
    HELP            [readback_select_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
{
        { 0,   [final_position_value_label],   [final_position_value_help]       },
        { 1,   [working_pos_label],       [working_pos_help]        }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__working_pos_d            (DS-66)
%SYM%   member      WORKING_POS_D       parameter         0xC00105B0
%SYM%   member      VL_WORKING_POS_D    variable-list     0x
%TXT%   record      __working_pos_d                       0x800205B0
%IMP%   RECORD      __working_pos_d 
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __discrete_input
**********************************************************************
*/
RECORD      __working_pos_d 
{
    LABEL           [working_pos_d_label] ;
    HELP            [working_pos_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__working_sp_d            (DS-66)
%SYM%   member      WORKING_SP_D       parameter         0xC00105B1
%SYM%   member      VL_WORKING_SP_D    variable-list     0x
%TXT%   record      __working_sp_d                       0x800205B1
%IMP%   RECORD      __working_sp_d
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __discrete_input
**********************************************************************
*/
RECORD      __working_sp_d
{
    LABEL           [working_sp_d_label] ;
    HELP            [working_sp_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_srv ;
        VALUE,   __discrete_contained_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__working_sp           (DS-65)
%SYM%   member     WORKING_SP      parameter      0xC0010564
%SYM%   member     VL_WORKING_SP   variable-list  0x
%TXT%   record     __working_sp                   0x80020564
%IMP%   RECORD     __working_sp
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __working_sp
{
    LABEL           [working_sp_label] ;
    HELP            [working_sp_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_srv ;
        VALUE,   __float_contained_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__xd_command
%SYM%   member      XD_COMMAND         parameter           0xC0010565
%SYM%   member      VL_XD_COMMAND      variable-list       0x
%TXT%   variable    __xd_command       enumerated          0x80020565
%IMP%   VARIABLE    __xd_command
**********************************************************************
*/
VARIABLE    __xd_command
{
    LABEL           [xd_command_label] ;
    HELP            [xd_command_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2) 
    {
        { 0,   [normal_operation_label],        [normal_operation_help]      },
        { 1,   [reserved_label],        [reserved_help]    },
        { 2,   [reserved_label],        [reserved_help]    },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    },
        { 256,   [mfg_specific_label],    [mfg_specific_help]    },
        { 257,   [mfg_specific_label],    [mfg_specific_help]    },
        { 258,   [mfg_specific_label],    [mfg_specific_help]    },
        { 259,   [mfg_specific_label],    [mfg_specific_help]    },
        { 260,   [mfg_specific_label],    [mfg_specific_help]    },
        { 261,   [mfg_specific_label],    [mfg_specific_help]    },
        { 262,   [mfg_specific_label],    [mfg_specific_help]    },
        { 263,   [mfg_specific_label],    [mfg_specific_help]    },
        { 264,   [mfg_specific_label],    [mfg_specific_help]    },
        { 265,   [mfg_specific_label],    [mfg_specific_help]    },
        { 266,   [mfg_specific_label],    [mfg_specific_help]    },
        { 267,   [mfg_specific_label],    [mfg_specific_help]    },
        { 268,   [mfg_specific_label],    [mfg_specific_help]    },
        { 269,   [mfg_specific_label],    [mfg_specific_help]    },
        { 270,   [mfg_specific_label],    [mfg_specific_help]    },
        { 271,   [mfg_specific_label],    [mfg_specific_help]    },
        { 272,   [mfg_specific_label],    [mfg_specific_help]    },
        { 273,   [mfg_specific_label],    [mfg_specific_help]    },
        { 274,   [mfg_specific_label],    [mfg_specific_help]    },
        { 275,   [mfg_specific_label],    [mfg_specific_help]    },
        { 276,   [mfg_specific_label],    [mfg_specific_help]    },
        { 277,   [mfg_specific_label],    [mfg_specific_help]    },
        { 278,   [mfg_specific_label],    [mfg_specific_help]    },
        { 279,   [mfg_specific_label],    [mfg_specific_help]    },
        { 280,   [mfg_specific_label],    [mfg_specific_help]    },
        { 281,   [mfg_specific_label],    [mfg_specific_help]    },
        { 282,   [mfg_specific_label],    [mfg_specific_help]    },
        { 283,   [mfg_specific_label],    [mfg_specific_help]    },
        { 284,   [mfg_specific_label],    [mfg_specific_help]    },
        { 285,   [mfg_specific_label],    [mfg_specific_help]    },
        { 286,   [mfg_specific_label],    [mfg_specific_help]    },
        { 287,   [mfg_specific_label],    [mfg_specific_help]    },
        { 288,   [mfg_specific_label],    [mfg_specific_help]    },
        { 289,   [mfg_specific_label],    [mfg_specific_help]    },
        { 290,   [mfg_specific_label],    [mfg_specific_help]    },
        { 291,   [mfg_specific_label],    [mfg_specific_help]    },
        { 292,   [mfg_specific_label],    [mfg_specific_help]    },
        { 293,   [mfg_specific_label],    [mfg_specific_help]    },
        { 294,   [mfg_specific_label],    [mfg_specific_help]    },
        { 295,   [mfg_specific_label],    [mfg_specific_help]    },
        { 296,   [mfg_specific_label],    [mfg_specific_help]    },
        { 297,   [mfg_specific_label],    [mfg_specific_help]    },
        { 298,   [mfg_specific_label],    [mfg_specific_help]    },
        { 299,   [mfg_specific_label],    [mfg_specific_help]    },       
        { 300,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 301,   [mfg_specific_label],    [mfg_specific_help]    },
        { 302,   [mfg_specific_label],    [mfg_specific_help]    },
        { 303,   [mfg_specific_label],    [mfg_specific_help]    },
        { 304,   [mfg_specific_label],    [mfg_specific_help]    },
        { 305,   [mfg_specific_label],    [mfg_specific_help]    },
        { 306,   [mfg_specific_label],    [mfg_specific_help]    },
        { 307,   [mfg_specific_label],    [mfg_specific_help]    },
        { 308,   [mfg_specific_label],    [mfg_specific_help]    },
        { 309,   [mfg_specific_label],    [mfg_specific_help]    },
        { 310,   [mfg_specific_label],    [mfg_specific_help]    },
        { 311,   [mfg_specific_label],    [mfg_specific_help]    },
        { 312,   [mfg_specific_label],    [mfg_specific_help]    },
        { 313,   [mfg_specific_label],    [mfg_specific_help]    },
        { 314,   [mfg_specific_label],    [mfg_specific_help]    },
        { 315,   [mfg_specific_label],    [mfg_specific_help]    },
        { 316,   [mfg_specific_label],    [mfg_specific_help]    },
        { 317,   [mfg_specific_label],    [mfg_specific_help]    },
        { 318,   [mfg_specific_label],    [mfg_specific_help]    },
        { 319,   [mfg_specific_label],    [mfg_specific_help]    },
        { 320,   [mfg_specific_label],    [mfg_specific_help]    },
        { 321,   [mfg_specific_label],    [mfg_specific_help]    },
        { 322,   [mfg_specific_label],    [mfg_specific_help]    },
        { 323,   [mfg_specific_label],    [mfg_specific_help]    },
        { 324,   [mfg_specific_label],    [mfg_specific_help]    },
        { 325,   [mfg_specific_label],    [mfg_specific_help]    },
        { 326,   [mfg_specific_label],    [mfg_specific_help]    },
        { 327,   [mfg_specific_label],    [mfg_specific_help]    },
        { 328,   [mfg_specific_label],    [mfg_specific_help]    },
        { 329,   [mfg_specific_label],    [mfg_specific_help]    },
        { 330,   [mfg_specific_label],    [mfg_specific_help]    },
        { 331,   [mfg_specific_label],    [mfg_specific_help]    },
        { 332,   [mfg_specific_label],    [mfg_specific_help]    },
        { 333,   [mfg_specific_label],    [mfg_specific_help]    },
        { 334,   [mfg_specific_label],    [mfg_specific_help]    },
        { 335,   [mfg_specific_label],    [mfg_specific_help]    },
        { 336,   [mfg_specific_label],    [mfg_specific_help]    },
        { 337,   [mfg_specific_label],    [mfg_specific_help]    },
        { 338,   [mfg_specific_label],    [mfg_specific_help]    },
        { 339,   [mfg_specific_label],    [mfg_specific_help]    },
        { 340,   [mfg_specific_label],    [mfg_specific_help]    },
        { 341,   [mfg_specific_label],    [mfg_specific_help]    },
        { 342,   [mfg_specific_label],    [mfg_specific_help]    },
        { 343,   [mfg_specific_label],    [mfg_specific_help]    },
        { 344,   [mfg_specific_label],    [mfg_specific_help]    },
        { 345,   [mfg_specific_label],    [mfg_specific_help]    },
        { 346,   [mfg_specific_label],    [mfg_specific_help]    },
        { 347,   [mfg_specific_label],    [mfg_specific_help]    },
        { 348,   [mfg_specific_label],    [mfg_specific_help]    },
        { 349,   [mfg_specific_label],    [mfg_specific_help]    },
        { 350,   [mfg_specific_label],    [mfg_specific_help]    },
        { 351,   [mfg_specific_label],    [mfg_specific_help]    },
        { 352,   [mfg_specific_label],    [mfg_specific_help]    },
        { 353,   [mfg_specific_label],    [mfg_specific_help]    },
        { 354,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 355,   [mfg_specific_label],    [mfg_specific_help]    },
        { 356,   [mfg_specific_label],    [mfg_specific_help]    },
        { 357,   [mfg_specific_label],    [mfg_specific_help]    },
        { 358,   [mfg_specific_label],    [mfg_specific_help]    },
        { 359,   [mfg_specific_label],    [mfg_specific_help]    },
        { 360,   [mfg_specific_label],    [mfg_specific_help]    },
        { 361,   [mfg_specific_label],    [mfg_specific_help]    },
        { 362,   [mfg_specific_label],    [mfg_specific_help]    },
        { 363,   [mfg_specific_label],    [mfg_specific_help]    },
        { 364,   [mfg_specific_label],    [mfg_specific_help]    },
        { 365,   [mfg_specific_label],    [mfg_specific_help]    },
        { 366,   [mfg_specific_label],    [mfg_specific_help]    },
        { 367,   [mfg_specific_label],    [mfg_specific_help]    },
        { 368,   [mfg_specific_label],    [mfg_specific_help]    },
        { 369,   [mfg_specific_label],    [mfg_specific_help]    },
        { 370,   [mfg_specific_label],    [mfg_specific_help]    },
        { 371,   [mfg_specific_label],    [mfg_specific_help]    },
        { 372,   [mfg_specific_label],    [mfg_specific_help]    },
        { 373,   [mfg_specific_label],    [mfg_specific_help]    },
        { 374,   [mfg_specific_label],    [mfg_specific_help]    },
        { 375,   [mfg_specific_label],    [mfg_specific_help]    },
        { 376,   [mfg_specific_label],    [mfg_specific_help]    },
        { 377,   [mfg_specific_label],    [mfg_specific_help]    },
        { 378,   [mfg_specific_label],    [mfg_specific_help]    },
        { 379,   [mfg_specific_label],    [mfg_specific_help]    },
        { 380,   [mfg_specific_label],    [mfg_specific_help]    },
        { 381,   [mfg_specific_label],    [mfg_specific_help]    },
        { 382,   [mfg_specific_label],    [mfg_specific_help]    },
        { 383,   [mfg_specific_label],    [mfg_specific_help]    },
        { 384,   [mfg_specific_label],    [mfg_specific_help]    },
        { 385,   [mfg_specific_label],    [mfg_specific_help]    },
        { 386,   [mfg_specific_label],    [mfg_specific_help]    },
        { 387,   [mfg_specific_label],    [mfg_specific_help]    },
        { 388,   [mfg_specific_label],    [mfg_specific_help]    },
        { 389,   [mfg_specific_label],    [mfg_specific_help]    },
        { 390,   [mfg_specific_label],    [mfg_specific_help]    },
        { 391,   [mfg_specific_label],    [mfg_specific_help]    },
        { 392,   [mfg_specific_label],    [mfg_specific_help]    },
        { 393,   [mfg_specific_label],    [mfg_specific_help]    },
        { 394,   [mfg_specific_label],    [mfg_specific_help]    },
        { 395,   [mfg_specific_label],    [mfg_specific_help]    },
        { 396,   [mfg_specific_label],    [mfg_specific_help]    },
        { 397,   [mfg_specific_label],    [mfg_specific_help]    },
        { 398,   [mfg_specific_label],    [mfg_specific_help]    },
        { 399,   [mfg_specific_label],    [mfg_specific_help]    },
        { 400,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 401,   [mfg_specific_label],    [mfg_specific_help]    },
        { 402,   [mfg_specific_label],    [mfg_specific_help]    },
        { 403,   [mfg_specific_label],    [mfg_specific_help]    },
        { 404,   [mfg_specific_label],    [mfg_specific_help]    },
        { 405,   [mfg_specific_label],    [mfg_specific_help]    },
        { 406,   [mfg_specific_label],    [mfg_specific_help]    },
        { 407,   [mfg_specific_label],    [mfg_specific_help]    },
        { 408,   [mfg_specific_label],    [mfg_specific_help]    },
        { 409,   [mfg_specific_label],    [mfg_specific_help]    },
        { 410,   [mfg_specific_label],    [mfg_specific_help]    },
        { 411,   [mfg_specific_label],    [mfg_specific_help]    },
        { 412,   [mfg_specific_label],    [mfg_specific_help]    },
        { 413,   [mfg_specific_label],    [mfg_specific_help]    },
        { 414,   [mfg_specific_label],    [mfg_specific_help]    },
        { 415,   [mfg_specific_label],    [mfg_specific_help]    },
        { 416,   [mfg_specific_label],    [mfg_specific_help]    },
        { 417,   [mfg_specific_label],    [mfg_specific_help]    },
        { 418,   [mfg_specific_label],    [mfg_specific_help]    },
        { 419,   [mfg_specific_label],    [mfg_specific_help]    },
        { 420,   [mfg_specific_label],    [mfg_specific_help]    },
        { 421,   [mfg_specific_label],    [mfg_specific_help]    },
        { 422,   [mfg_specific_label],    [mfg_specific_help]    },
        { 423,   [mfg_specific_label],    [mfg_specific_help]    },
        { 424,   [mfg_specific_label],    [mfg_specific_help]    },
        { 425,   [mfg_specific_label],    [mfg_specific_help]    },
        { 426,   [mfg_specific_label],    [mfg_specific_help]    },
        { 427,   [mfg_specific_label],    [mfg_specific_help]    },
        { 428,   [mfg_specific_label],    [mfg_specific_help]    },
        { 429,   [mfg_specific_label],    [mfg_specific_help]    },
        { 430,   [mfg_specific_label],    [mfg_specific_help]    },
        { 431,   [mfg_specific_label],    [mfg_specific_help]    },
        { 432,   [mfg_specific_label],    [mfg_specific_help]    },
        { 433,   [mfg_specific_label],    [mfg_specific_help]    },
        { 434,   [mfg_specific_label],    [mfg_specific_help]    },
        { 435,   [mfg_specific_label],    [mfg_specific_help]    },
        { 436,   [mfg_specific_label],    [mfg_specific_help]    },
        { 437,   [mfg_specific_label],    [mfg_specific_help]    },
        { 438,   [mfg_specific_label],    [mfg_specific_help]    },
        { 439,   [mfg_specific_label],    [mfg_specific_help]    },
        { 440,   [mfg_specific_label],    [mfg_specific_help]    },
        { 441,   [mfg_specific_label],    [mfg_specific_help]    },
        { 442,   [mfg_specific_label],    [mfg_specific_help]    },
        { 443,   [mfg_specific_label],    [mfg_specific_help]    },
        { 444,   [mfg_specific_label],    [mfg_specific_help]    },
        { 445,   [mfg_specific_label],    [mfg_specific_help]    },
        { 446,   [mfg_specific_label],    [mfg_specific_help]    },
        { 447,   [mfg_specific_label],    [mfg_specific_help]    },
        { 448,   [mfg_specific_label],    [mfg_specific_help]    },
        { 449,   [mfg_specific_label],    [mfg_specific_help]    },
        { 450,   [mfg_specific_label],    [mfg_specific_help]    },
        { 451,   [mfg_specific_label],    [mfg_specific_help]    },
        { 452,   [mfg_specific_label],    [mfg_specific_help]    },
        { 453,   [mfg_specific_label],    [mfg_specific_help]    },
        { 454,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 455,   [mfg_specific_label],    [mfg_specific_help]    },
        { 456,   [mfg_specific_label],    [mfg_specific_help]    },
        { 457,   [mfg_specific_label],    [mfg_specific_help]    },
        { 458,   [mfg_specific_label],    [mfg_specific_help]    },
        { 459,   [mfg_specific_label],    [mfg_specific_help]    },
        { 460,   [mfg_specific_label],    [mfg_specific_help]    },
        { 461,   [mfg_specific_label],    [mfg_specific_help]    },
        { 462,   [mfg_specific_label],    [mfg_specific_help]    },
        { 463,   [mfg_specific_label],    [mfg_specific_help]    },
        { 464,   [mfg_specific_label],    [mfg_specific_help]    },
        { 465,   [mfg_specific_label],    [mfg_specific_help]    },
        { 466,   [mfg_specific_label],    [mfg_specific_help]    },
        { 467,   [mfg_specific_label],    [mfg_specific_help]    },
        { 468,   [mfg_specific_label],    [mfg_specific_help]    },
        { 469,   [mfg_specific_label],    [mfg_specific_help]    },
        { 470,   [mfg_specific_label],    [mfg_specific_help]    },
        { 471,   [mfg_specific_label],    [mfg_specific_help]    },
        { 472,   [mfg_specific_label],    [mfg_specific_help]    },
        { 473,   [mfg_specific_label],    [mfg_specific_help]    },
        { 474,   [mfg_specific_label],    [mfg_specific_help]    },
        { 475,   [mfg_specific_label],    [mfg_specific_help]    },
        { 476,   [mfg_specific_label],    [mfg_specific_help]    },
        { 477,   [mfg_specific_label],    [mfg_specific_help]    },
        { 478,   [mfg_specific_label],    [mfg_specific_help]    },
        { 479,   [mfg_specific_label],    [mfg_specific_help]    },
        { 480,   [mfg_specific_label],    [mfg_specific_help]    },
        { 481,   [mfg_specific_label],    [mfg_specific_help]    },
        { 482,   [mfg_specific_label],    [mfg_specific_help]    },
        { 483,   [mfg_specific_label],    [mfg_specific_help]    },
        { 484,   [mfg_specific_label],    [mfg_specific_help]    },
        { 485,   [mfg_specific_label],    [mfg_specific_help]    },
        { 486,   [mfg_specific_label],    [mfg_specific_help]    },
        { 487,   [mfg_specific_label],    [mfg_specific_help]    },
        { 488,   [mfg_specific_label],    [mfg_specific_help]    },
        { 489,   [mfg_specific_label],    [mfg_specific_help]    },
        { 490,   [mfg_specific_label],    [mfg_specific_help]    },
        { 491,   [mfg_specific_label],    [mfg_specific_help]    },
        { 492,   [mfg_specific_label],    [mfg_specific_help]    },
        { 493,   [mfg_specific_label],    [mfg_specific_help]    },
        { 494,   [mfg_specific_label],    [mfg_specific_help]    },
        { 495,   [mfg_specific_label],    [mfg_specific_help]    },
        { 496,   [mfg_specific_label],    [mfg_specific_help]    },
        { 497,   [mfg_specific_label],    [mfg_specific_help]    },
        { 498,   [mfg_specific_label],    [mfg_specific_help]    },
        { 499,   [mfg_specific_label],    [mfg_specific_help]    }        
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_command_flags
%SYM%   member      XD_COMMAND_FLAGS        parameter         0xC001056C
%SYM%   member      VL_XD_COMMAND_FLAGS     variable-list     0x
%TXT%   variable    __xd_command_flags      bit-string        0x8002056C
%IMP%   VARIABLE    __xd_command_flags
**********************************************************************
*/
VARIABLE    __xd_command_flags
{
    LABEL           [xd_command_flags_label] ;
    HELP            [xd_command_flags_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2) 
    {
        { 0,   [no_procedure_label],        [no_procedure_help]      },
        { 1,   [reserved_label],        [reserved_help]    },
        { 2,   [reserved_label],        [reserved_help]    },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_command_state
%SYM%   member      XD_COMMAND_STATE         parameter           0xC0010566
%SYM%   member      VL_XD_COMMAND_STATE      variable-list       0x
%TXT%   variable    __xd_command_state       enumerated          0x80020566
%IMP%   VARIABLE    __xd_command_state
**********************************************************************
*/
VARIABLE    __xd_command_state
{
    LABEL           [xd_command_state_label] ;
    HELP            [xd_command_state_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2) 
{
        { 0,   [normal_operation_label],        [normal_operation_help]      },
        { 1,   [reserved_label],        [reserved_help]    },
        { 2,   [reserved_label],        [reserved_help]    },
        { 3,   [reserved_label],        [reserved_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    },
        { 256,   [mfg_specific_label],    [mfg_specific_help]    },
        { 257,   [mfg_specific_label],    [mfg_specific_help]    },
        { 258,   [mfg_specific_label],    [mfg_specific_help]    },
        { 259,   [mfg_specific_label],    [mfg_specific_help]    },
        { 260,   [mfg_specific_label],    [mfg_specific_help]    },
        { 261,   [mfg_specific_label],    [mfg_specific_help]    },
        { 262,   [mfg_specific_label],    [mfg_specific_help]    },
        { 263,   [mfg_specific_label],    [mfg_specific_help]    },
        { 264,   [mfg_specific_label],    [mfg_specific_help]    },
        { 265,   [mfg_specific_label],    [mfg_specific_help]    },
        { 266,   [mfg_specific_label],    [mfg_specific_help]    },
        { 267,   [mfg_specific_label],    [mfg_specific_help]    },
        { 268,   [mfg_specific_label],    [mfg_specific_help]    },
        { 269,   [mfg_specific_label],    [mfg_specific_help]    },
        { 270,   [mfg_specific_label],    [mfg_specific_help]    },
        { 271,   [mfg_specific_label],    [mfg_specific_help]    },
        { 272,   [mfg_specific_label],    [mfg_specific_help]    },
        { 273,   [mfg_specific_label],    [mfg_specific_help]    },
        { 274,   [mfg_specific_label],    [mfg_specific_help]    },
        { 275,   [mfg_specific_label],    [mfg_specific_help]    },
        { 276,   [mfg_specific_label],    [mfg_specific_help]    },
        { 277,   [mfg_specific_label],    [mfg_specific_help]    },
        { 278,   [mfg_specific_label],    [mfg_specific_help]    },
        { 279,   [mfg_specific_label],    [mfg_specific_help]    },
        { 280,   [mfg_specific_label],    [mfg_specific_help]    },
        { 281,   [mfg_specific_label],    [mfg_specific_help]    },
        { 282,   [mfg_specific_label],    [mfg_specific_help]    },
        { 283,   [mfg_specific_label],    [mfg_specific_help]    },
        { 284,   [mfg_specific_label],    [mfg_specific_help]    },
        { 285,   [mfg_specific_label],    [mfg_specific_help]    },
        { 286,   [mfg_specific_label],    [mfg_specific_help]    },
        { 287,   [mfg_specific_label],    [mfg_specific_help]    },
        { 288,   [mfg_specific_label],    [mfg_specific_help]    },
        { 289,   [mfg_specific_label],    [mfg_specific_help]    },
        { 290,   [mfg_specific_label],    [mfg_specific_help]    },
        { 291,   [mfg_specific_label],    [mfg_specific_help]    },
        { 292,   [mfg_specific_label],    [mfg_specific_help]    },
        { 293,   [mfg_specific_label],    [mfg_specific_help]    },
        { 294,   [mfg_specific_label],    [mfg_specific_help]    },
        { 295,   [mfg_specific_label],    [mfg_specific_help]    },
        { 296,   [mfg_specific_label],    [mfg_specific_help]    },
        { 297,   [mfg_specific_label],    [mfg_specific_help]    },
        { 298,   [mfg_specific_label],    [mfg_specific_help]    },
        { 299,   [mfg_specific_label],    [mfg_specific_help]    },       
        { 300,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 301,   [mfg_specific_label],    [mfg_specific_help]    },
        { 302,   [mfg_specific_label],    [mfg_specific_help]    },
        { 303,   [mfg_specific_label],    [mfg_specific_help]    },
        { 304,   [mfg_specific_label],    [mfg_specific_help]    },
        { 305,   [mfg_specific_label],    [mfg_specific_help]    },
        { 306,   [mfg_specific_label],    [mfg_specific_help]    },
        { 307,   [mfg_specific_label],    [mfg_specific_help]    },
        { 308,   [mfg_specific_label],    [mfg_specific_help]    },
        { 309,   [mfg_specific_label],    [mfg_specific_help]    },
        { 310,   [mfg_specific_label],    [mfg_specific_help]    },
        { 311,   [mfg_specific_label],    [mfg_specific_help]    },
        { 312,   [mfg_specific_label],    [mfg_specific_help]    },
        { 313,   [mfg_specific_label],    [mfg_specific_help]    },
        { 314,   [mfg_specific_label],    [mfg_specific_help]    },
        { 315,   [mfg_specific_label],    [mfg_specific_help]    },
        { 316,   [mfg_specific_label],    [mfg_specific_help]    },
        { 317,   [mfg_specific_label],    [mfg_specific_help]    },
        { 318,   [mfg_specific_label],    [mfg_specific_help]    },
        { 319,   [mfg_specific_label],    [mfg_specific_help]    },
        { 320,   [mfg_specific_label],    [mfg_specific_help]    },
        { 321,   [mfg_specific_label],    [mfg_specific_help]    },
        { 322,   [mfg_specific_label],    [mfg_specific_help]    },
        { 323,   [mfg_specific_label],    [mfg_specific_help]    },
        { 324,   [mfg_specific_label],    [mfg_specific_help]    },
        { 325,   [mfg_specific_label],    [mfg_specific_help]    },
        { 326,   [mfg_specific_label],    [mfg_specific_help]    },
        { 327,   [mfg_specific_label],    [mfg_specific_help]    },
        { 328,   [mfg_specific_label],    [mfg_specific_help]    },
        { 329,   [mfg_specific_label],    [mfg_specific_help]    },
        { 330,   [mfg_specific_label],    [mfg_specific_help]    },
        { 331,   [mfg_specific_label],    [mfg_specific_help]    },
        { 332,   [mfg_specific_label],    [mfg_specific_help]    },
        { 333,   [mfg_specific_label],    [mfg_specific_help]    },
        { 334,   [mfg_specific_label],    [mfg_specific_help]    },
        { 335,   [mfg_specific_label],    [mfg_specific_help]    },
        { 336,   [mfg_specific_label],    [mfg_specific_help]    },
        { 337,   [mfg_specific_label],    [mfg_specific_help]    },
        { 338,   [mfg_specific_label],    [mfg_specific_help]    },
        { 339,   [mfg_specific_label],    [mfg_specific_help]    },
        { 340,   [mfg_specific_label],    [mfg_specific_help]    },
        { 341,   [mfg_specific_label],    [mfg_specific_help]    },
        { 342,   [mfg_specific_label],    [mfg_specific_help]    },
        { 343,   [mfg_specific_label],    [mfg_specific_help]    },
        { 344,   [mfg_specific_label],    [mfg_specific_help]    },
        { 345,   [mfg_specific_label],    [mfg_specific_help]    },
        { 346,   [mfg_specific_label],    [mfg_specific_help]    },
        { 347,   [mfg_specific_label],    [mfg_specific_help]    },
        { 348,   [mfg_specific_label],    [mfg_specific_help]    },
        { 349,   [mfg_specific_label],    [mfg_specific_help]    },
        { 350,   [mfg_specific_label],    [mfg_specific_help]    },
        { 351,   [mfg_specific_label],    [mfg_specific_help]    },
        { 352,   [mfg_specific_label],    [mfg_specific_help]    },
        { 353,   [mfg_specific_label],    [mfg_specific_help]    },
        { 354,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 355,   [mfg_specific_label],    [mfg_specific_help]    },
        { 356,   [mfg_specific_label],    [mfg_specific_help]    },
        { 357,   [mfg_specific_label],    [mfg_specific_help]    },
        { 358,   [mfg_specific_label],    [mfg_specific_help]    },
        { 359,   [mfg_specific_label],    [mfg_specific_help]    },
        { 360,   [mfg_specific_label],    [mfg_specific_help]    },
        { 361,   [mfg_specific_label],    [mfg_specific_help]    },
        { 362,   [mfg_specific_label],    [mfg_specific_help]    },
        { 363,   [mfg_specific_label],    [mfg_specific_help]    },
        { 364,   [mfg_specific_label],    [mfg_specific_help]    },
        { 365,   [mfg_specific_label],    [mfg_specific_help]    },
        { 366,   [mfg_specific_label],    [mfg_specific_help]    },
        { 367,   [mfg_specific_label],    [mfg_specific_help]    },
        { 368,   [mfg_specific_label],    [mfg_specific_help]    },
        { 369,   [mfg_specific_label],    [mfg_specific_help]    },
        { 370,   [mfg_specific_label],    [mfg_specific_help]    },
        { 371,   [mfg_specific_label],    [mfg_specific_help]    },
        { 372,   [mfg_specific_label],    [mfg_specific_help]    },
        { 373,   [mfg_specific_label],    [mfg_specific_help]    },
        { 374,   [mfg_specific_label],    [mfg_specific_help]    },
        { 375,   [mfg_specific_label],    [mfg_specific_help]    },
        { 376,   [mfg_specific_label],    [mfg_specific_help]    },
        { 377,   [mfg_specific_label],    [mfg_specific_help]    },
        { 378,   [mfg_specific_label],    [mfg_specific_help]    },
        { 379,   [mfg_specific_label],    [mfg_specific_help]    },
        { 380,   [mfg_specific_label],    [mfg_specific_help]    },
        { 381,   [mfg_specific_label],    [mfg_specific_help]    },
        { 382,   [mfg_specific_label],    [mfg_specific_help]    },
        { 383,   [mfg_specific_label],    [mfg_specific_help]    },
        { 384,   [mfg_specific_label],    [mfg_specific_help]    },
        { 385,   [mfg_specific_label],    [mfg_specific_help]    },
        { 386,   [mfg_specific_label],    [mfg_specific_help]    },
        { 387,   [mfg_specific_label],    [mfg_specific_help]    },
        { 388,   [mfg_specific_label],    [mfg_specific_help]    },
        { 389,   [mfg_specific_label],    [mfg_specific_help]    },
        { 390,   [mfg_specific_label],    [mfg_specific_help]    },
        { 391,   [mfg_specific_label],    [mfg_specific_help]    },
        { 392,   [mfg_specific_label],    [mfg_specific_help]    },
        { 393,   [mfg_specific_label],    [mfg_specific_help]    },
        { 394,   [mfg_specific_label],    [mfg_specific_help]    },
        { 395,   [mfg_specific_label],    [mfg_specific_help]    },
        { 396,   [mfg_specific_label],    [mfg_specific_help]    },
        { 397,   [mfg_specific_label],    [mfg_specific_help]    },
        { 398,   [mfg_specific_label],    [mfg_specific_help]    },
        { 399,   [mfg_specific_label],    [mfg_specific_help]    },
        { 400,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 401,   [mfg_specific_label],    [mfg_specific_help]    },
        { 402,   [mfg_specific_label],    [mfg_specific_help]    },
        { 403,   [mfg_specific_label],    [mfg_specific_help]    },
        { 404,   [mfg_specific_label],    [mfg_specific_help]    },
        { 405,   [mfg_specific_label],    [mfg_specific_help]    },
        { 406,   [mfg_specific_label],    [mfg_specific_help]    },
        { 407,   [mfg_specific_label],    [mfg_specific_help]    },
        { 408,   [mfg_specific_label],    [mfg_specific_help]    },
        { 409,   [mfg_specific_label],    [mfg_specific_help]    },
        { 410,   [mfg_specific_label],    [mfg_specific_help]    },
        { 411,   [mfg_specific_label],    [mfg_specific_help]    },
        { 412,   [mfg_specific_label],    [mfg_specific_help]    },
        { 413,   [mfg_specific_label],    [mfg_specific_help]    },
        { 414,   [mfg_specific_label],    [mfg_specific_help]    },
        { 415,   [mfg_specific_label],    [mfg_specific_help]    },
        { 416,   [mfg_specific_label],    [mfg_specific_help]    },
        { 417,   [mfg_specific_label],    [mfg_specific_help]    },
        { 418,   [mfg_specific_label],    [mfg_specific_help]    },
        { 419,   [mfg_specific_label],    [mfg_specific_help]    },
        { 420,   [mfg_specific_label],    [mfg_specific_help]    },
        { 421,   [mfg_specific_label],    [mfg_specific_help]    },
        { 422,   [mfg_specific_label],    [mfg_specific_help]    },
        { 423,   [mfg_specific_label],    [mfg_specific_help]    },
        { 424,   [mfg_specific_label],    [mfg_specific_help]    },
        { 425,   [mfg_specific_label],    [mfg_specific_help]    },
        { 426,   [mfg_specific_label],    [mfg_specific_help]    },
        { 427,   [mfg_specific_label],    [mfg_specific_help]    },
        { 428,   [mfg_specific_label],    [mfg_specific_help]    },
        { 429,   [mfg_specific_label],    [mfg_specific_help]    },
        { 430,   [mfg_specific_label],    [mfg_specific_help]    },
        { 431,   [mfg_specific_label],    [mfg_specific_help]    },
        { 432,   [mfg_specific_label],    [mfg_specific_help]    },
        { 433,   [mfg_specific_label],    [mfg_specific_help]    },
        { 434,   [mfg_specific_label],    [mfg_specific_help]    },
        { 435,   [mfg_specific_label],    [mfg_specific_help]    },
        { 436,   [mfg_specific_label],    [mfg_specific_help]    },
        { 437,   [mfg_specific_label],    [mfg_specific_help]    },
        { 438,   [mfg_specific_label],    [mfg_specific_help]    },
        { 439,   [mfg_specific_label],    [mfg_specific_help]    },
        { 440,   [mfg_specific_label],    [mfg_specific_help]    },
        { 441,   [mfg_specific_label],    [mfg_specific_help]    },
        { 442,   [mfg_specific_label],    [mfg_specific_help]    },
        { 443,   [mfg_specific_label],    [mfg_specific_help]    },
        { 444,   [mfg_specific_label],    [mfg_specific_help]    },
        { 445,   [mfg_specific_label],    [mfg_specific_help]    },
        { 446,   [mfg_specific_label],    [mfg_specific_help]    },
        { 447,   [mfg_specific_label],    [mfg_specific_help]    },
        { 448,   [mfg_specific_label],    [mfg_specific_help]    },
        { 449,   [mfg_specific_label],    [mfg_specific_help]    },
        { 450,   [mfg_specific_label],    [mfg_specific_help]    },
        { 451,   [mfg_specific_label],    [mfg_specific_help]    },
        { 452,   [mfg_specific_label],    [mfg_specific_help]    },
        { 453,   [mfg_specific_label],    [mfg_specific_help]    },
        { 454,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 455,   [mfg_specific_label],    [mfg_specific_help]    },
        { 456,   [mfg_specific_label],    [mfg_specific_help]    },
        { 457,   [mfg_specific_label],    [mfg_specific_help]    },
        { 458,   [mfg_specific_label],    [mfg_specific_help]    },
        { 459,   [mfg_specific_label],    [mfg_specific_help]    },
        { 460,   [mfg_specific_label],    [mfg_specific_help]    },
        { 461,   [mfg_specific_label],    [mfg_specific_help]    },
        { 462,   [mfg_specific_label],    [mfg_specific_help]    },
        { 463,   [mfg_specific_label],    [mfg_specific_help]    },
        { 464,   [mfg_specific_label],    [mfg_specific_help]    },
        { 465,   [mfg_specific_label],    [mfg_specific_help]    },
        { 466,   [mfg_specific_label],    [mfg_specific_help]    },
        { 467,   [mfg_specific_label],    [mfg_specific_help]    },
        { 468,   [mfg_specific_label],    [mfg_specific_help]    },
        { 469,   [mfg_specific_label],    [mfg_specific_help]    },
        { 470,   [mfg_specific_label],    [mfg_specific_help]    },
        { 471,   [mfg_specific_label],    [mfg_specific_help]    },
        { 472,   [mfg_specific_label],    [mfg_specific_help]    },
        { 473,   [mfg_specific_label],    [mfg_specific_help]    },
        { 474,   [mfg_specific_label],    [mfg_specific_help]    },
        { 475,   [mfg_specific_label],    [mfg_specific_help]    },
        { 476,   [mfg_specific_label],    [mfg_specific_help]    },
        { 477,   [mfg_specific_label],    [mfg_specific_help]    },
        { 478,   [mfg_specific_label],    [mfg_specific_help]    },
        { 479,   [mfg_specific_label],    [mfg_specific_help]    },
        { 480,   [mfg_specific_label],    [mfg_specific_help]    },
        { 481,   [mfg_specific_label],    [mfg_specific_help]    },
        { 482,   [mfg_specific_label],    [mfg_specific_help]    },
        { 483,   [mfg_specific_label],    [mfg_specific_help]    },
        { 484,   [mfg_specific_label],    [mfg_specific_help]    },
        { 485,   [mfg_specific_label],    [mfg_specific_help]    },
        { 486,   [mfg_specific_label],    [mfg_specific_help]    },
        { 487,   [mfg_specific_label],    [mfg_specific_help]    },
        { 488,   [mfg_specific_label],    [mfg_specific_help]    },
        { 489,   [mfg_specific_label],    [mfg_specific_help]    },
        { 490,   [mfg_specific_label],    [mfg_specific_help]    },
        { 491,   [mfg_specific_label],    [mfg_specific_help]    },
        { 492,   [mfg_specific_label],    [mfg_specific_help]    },
        { 493,   [mfg_specific_label],    [mfg_specific_help]    },
        { 494,   [mfg_specific_label],    [mfg_specific_help]    },
        { 495,   [mfg_specific_label],    [mfg_specific_help]    },
        { 496,   [mfg_specific_label],    [mfg_specific_help]    },
        { 497,   [mfg_specific_label],    [mfg_specific_help]    },
        { 498,   [mfg_specific_label],    [mfg_specific_help]    },
        { 499,   [mfg_specific_label],    [mfg_specific_help]    }        
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_fstate_opt
%SYM%   member      XD_FSTATE_OPT         parameter           0xC0010567
%SYM%   member      VL_XD_FSTATE_OPT      variable-list       0x
%TXT%   variable    __xd_fstate_opt       unsigned            0x80020567
%IMP%   VARIABLE    __xd_fstate_opt
**********************************************************************
*/
VARIABLE    __xd_fstate_opt
{
    LABEL           [xd_fstate_opt_label] ;
    HELP            [xd_fstate_opt_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1) 
{
        { 0,   [hold_last_value_label],        [hold_last_value_help]      },
        { 1,   [fail_closed_label],        [fail_closed_help]    },
        { 2,   [fail_open_label],        [fail_open_help]    },
        { 3,   [xd_fstate_val_label],   [xd_fstate_val_help]    },
        { 4,   [reserved_label],        [reserved_help]    },
        { 5,   [reserved_label],        [reserved_help]    },
        { 6,   [reserved_label],        [reserved_help]    },
        { 7,   [reserved_label],        [reserved_help]    },
        { 8,   [mfg_specific_label],    [mfg_specific_help]    },
        { 9,   [mfg_specific_label],    [mfg_specific_help]    },
        { 10,   [mfg_specific_label],    [mfg_specific_help]    },
        { 11,   [mfg_specific_label],    [mfg_specific_help]    },
        { 12,   [mfg_specific_label],    [mfg_specific_help]    },
        { 13,   [mfg_specific_label],    [mfg_specific_help]    },
        { 14,   [mfg_specific_label],    [mfg_specific_help]    },
        { 15,   [mfg_specific_label],    [mfg_specific_help]    },
        { 16,   [mfg_specific_label],    [mfg_specific_help]    },
        { 17,   [mfg_specific_label],    [mfg_specific_help]    },
        { 18,   [mfg_specific_label],    [mfg_specific_help]    },
        { 19,   [mfg_specific_label],    [mfg_specific_help]    },
        { 20,   [mfg_specific_label],    [mfg_specific_help]    },
        { 21,   [mfg_specific_label],    [mfg_specific_help]    },
        { 22,   [mfg_specific_label],    [mfg_specific_help]    },
        { 23,   [mfg_specific_label],    [mfg_specific_help]    },
        { 24,   [mfg_specific_label],    [mfg_specific_help]    },
        { 25,   [mfg_specific_label],    [mfg_specific_help]    },
        { 26,   [mfg_specific_label],    [mfg_specific_help]    },
        { 27,   [mfg_specific_label],    [mfg_specific_help]    },
        { 28,   [mfg_specific_label],    [mfg_specific_help]    },
        { 29,   [mfg_specific_label],    [mfg_specific_help]    },
        { 30,   [mfg_specific_label],    [mfg_specific_help]    },
        { 31,   [mfg_specific_label],    [mfg_specific_help]    },
        { 32,   [mfg_specific_label],    [mfg_specific_help]    },
        { 33,   [mfg_specific_label],    [mfg_specific_help]    },
        { 34,   [mfg_specific_label],    [mfg_specific_help]    },
        { 35,   [mfg_specific_label],    [mfg_specific_help]    },
        { 36,   [mfg_specific_label],    [mfg_specific_help]    },
        { 37,   [mfg_specific_label],    [mfg_specific_help]    },
        { 38,   [mfg_specific_label],    [mfg_specific_help]    },
        { 39,   [mfg_specific_label],    [mfg_specific_help]    },
        { 40,   [mfg_specific_label],    [mfg_specific_help]    },
        { 41,   [mfg_specific_label],    [mfg_specific_help]    },
        { 42,   [mfg_specific_label],    [mfg_specific_help]    },
        { 43,   [mfg_specific_label],    [mfg_specific_help]    },
        { 44,   [mfg_specific_label],    [mfg_specific_help]    },
        { 45,   [mfg_specific_label],    [mfg_specific_help]    },
        { 46,   [mfg_specific_label],    [mfg_specific_help]    },
        { 47,   [mfg_specific_label],    [mfg_specific_help]    },
        { 48,   [mfg_specific_label],    [mfg_specific_help]    },
        { 49,   [mfg_specific_label],    [mfg_specific_help]    },
        { 50,   [mfg_specific_label],    [mfg_specific_help]    },
        { 51,   [mfg_specific_label],    [mfg_specific_help]    },
        { 52,   [mfg_specific_label],    [mfg_specific_help]    },
        { 53,   [mfg_specific_label],    [mfg_specific_help]    },
        { 54,   [mfg_specific_label],    [mfg_specific_help]    },
        { 55,   [mfg_specific_label],    [mfg_specific_help]    },
        { 56,   [mfg_specific_label],    [mfg_specific_help]    },
        { 57,   [mfg_specific_label],    [mfg_specific_help]    },
        { 58,   [mfg_specific_label],    [mfg_specific_help]    },
        { 59,   [mfg_specific_label],    [mfg_specific_help]    },
        { 60,   [mfg_specific_label],    [mfg_specific_help]    },
        { 61,   [mfg_specific_label],    [mfg_specific_help]    },
        { 62,   [mfg_specific_label],    [mfg_specific_help]    },
        { 63,   [mfg_specific_label],    [mfg_specific_help]    },
        { 64,   [mfg_specific_label],    [mfg_specific_help]    },
        { 65,   [mfg_specific_label],    [mfg_specific_help]    },
        { 66,   [mfg_specific_label],    [mfg_specific_help]    },
        { 67,   [mfg_specific_label],    [mfg_specific_help]    },
        { 68,   [mfg_specific_label],    [mfg_specific_help]    },
        { 69,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 70,   [mfg_specific_label],    [mfg_specific_help]    },
        { 71,   [mfg_specific_label],    [mfg_specific_help]    },
        { 72,   [mfg_specific_label],    [mfg_specific_help]    },
        { 73,   [mfg_specific_label],    [mfg_specific_help]    },
        { 74,   [mfg_specific_label],    [mfg_specific_help]    },
        { 75,   [mfg_specific_label],    [mfg_specific_help]    },
        { 76,   [mfg_specific_label],    [mfg_specific_help]    },
        { 77,   [mfg_specific_label],    [mfg_specific_help]    },
        { 78,   [mfg_specific_label],    [mfg_specific_help]    },
        { 79,   [mfg_specific_label],    [mfg_specific_help]    },
        { 80,   [mfg_specific_label],    [mfg_specific_help]    },
        { 81,   [mfg_specific_label],    [mfg_specific_help]    },
        { 82,   [mfg_specific_label],    [mfg_specific_help]    },
        { 83,   [mfg_specific_label],    [mfg_specific_help]    },
        { 84,   [mfg_specific_label],    [mfg_specific_help]    },
        { 85,   [mfg_specific_label],    [mfg_specific_help]    },
        { 86,   [mfg_specific_label],    [mfg_specific_help]    },
        { 87,   [mfg_specific_label],    [mfg_specific_help]    },
        { 88,   [mfg_specific_label],    [mfg_specific_help]    },
        { 89,   [mfg_specific_label],    [mfg_specific_help]    },
        { 90,   [mfg_specific_label],    [mfg_specific_help]    },
        { 91,   [mfg_specific_label],    [mfg_specific_help]    },
        { 92,   [mfg_specific_label],    [mfg_specific_help]    },
        { 93,   [mfg_specific_label],    [mfg_specific_help]    },
        { 94,   [mfg_specific_label],    [mfg_specific_help]    },
        { 95,   [mfg_specific_label],    [mfg_specific_help]    },
        { 96,   [mfg_specific_label],    [mfg_specific_help]    },
        { 97,   [mfg_specific_label],    [mfg_specific_help]    },
        { 98,   [mfg_specific_label],    [mfg_specific_help]    },
        { 99,   [mfg_specific_label],    [mfg_specific_help]    },
        { 100,   [mfg_specific_label],    [mfg_specific_help]    },
        { 101,   [mfg_specific_label],    [mfg_specific_help]    },
        { 102,   [mfg_specific_label],    [mfg_specific_help]    },
        { 103,   [mfg_specific_label],    [mfg_specific_help]    },
        { 104,   [mfg_specific_label],    [mfg_specific_help]    },
        { 105,   [mfg_specific_label],    [mfg_specific_help]    },
        { 106,   [mfg_specific_label],    [mfg_specific_help]    },
        { 107,   [mfg_specific_label],    [mfg_specific_help]    },
        { 108,   [mfg_specific_label],    [mfg_specific_help]    },
        { 109,   [mfg_specific_label],    [mfg_specific_help]    },
        { 110,   [mfg_specific_label],    [mfg_specific_help]    },
        { 111,   [mfg_specific_label],    [mfg_specific_help]    },
        { 112,   [mfg_specific_label],    [mfg_specific_help]    },
        { 113,   [mfg_specific_label],    [mfg_specific_help]    },
        { 114,   [mfg_specific_label],    [mfg_specific_help]    },
        { 115,   [mfg_specific_label],    [mfg_specific_help]    },
        { 116,   [mfg_specific_label],    [mfg_specific_help]    },
        { 117,   [mfg_specific_label],    [mfg_specific_help]    },
        { 118,   [mfg_specific_label],    [mfg_specific_help]    },
        { 119,   [mfg_specific_label],    [mfg_specific_help]    },
        { 120,   [mfg_specific_label],    [mfg_specific_help]    },
        { 121,   [mfg_specific_label],    [mfg_specific_help]    },
        { 122,   [mfg_specific_label],    [mfg_specific_help]    },
        { 123,   [mfg_specific_label],    [mfg_specific_help]    },
        { 124,   [mfg_specific_label],    [mfg_specific_help]    },
        { 125,   [mfg_specific_label],    [mfg_specific_help]    },
        { 126,   [mfg_specific_label],    [mfg_specific_help]    },
        { 127,   [mfg_specific_label],    [mfg_specific_help]    },
        { 128,   [mfg_specific_label],    [mfg_specific_help]    },
        { 129,   [mfg_specific_label],    [mfg_specific_help]    },
        { 130,   [mfg_specific_label],    [mfg_specific_help]    },
        { 131,   [mfg_specific_label],    [mfg_specific_help]    },
        { 132,   [mfg_specific_label],    [mfg_specific_help]    },
        { 133,   [mfg_specific_label],    [mfg_specific_help]    },
        { 134,   [mfg_specific_label],    [mfg_specific_help]    },
        { 135,   [mfg_specific_label],    [mfg_specific_help]    },
        { 136,   [mfg_specific_label],    [mfg_specific_help]    },
        { 137,   [mfg_specific_label],    [mfg_specific_help]    },
        { 138,   [mfg_specific_label],    [mfg_specific_help]    },
        { 139,   [mfg_specific_label],    [mfg_specific_help]    },
        { 140,   [mfg_specific_label],    [mfg_specific_help]    },
        { 141,   [mfg_specific_label],    [mfg_specific_help]    },
        { 142,   [mfg_specific_label],    [mfg_specific_help]    },
        { 143,   [mfg_specific_label],    [mfg_specific_help]    },
        { 144,   [mfg_specific_label],    [mfg_specific_help]    },
        { 145,   [mfg_specific_label],    [mfg_specific_help]    },
        { 146,   [mfg_specific_label],    [mfg_specific_help]    },
        { 147,   [mfg_specific_label],    [mfg_specific_help]    },
        { 148,   [mfg_specific_label],    [mfg_specific_help]    },
        { 149,   [mfg_specific_label],    [mfg_specific_help]    },
        { 150,   [mfg_specific_label],    [mfg_specific_help]    },
        { 151,   [mfg_specific_label],    [mfg_specific_help]    },
        { 152,   [mfg_specific_label],    [mfg_specific_help]    },
        { 153,   [mfg_specific_label],    [mfg_specific_help]    },
        { 154,   [mfg_specific_label],    [mfg_specific_help]    },
        { 155,   [mfg_specific_label],    [mfg_specific_help]    },
        { 156,   [mfg_specific_label],    [mfg_specific_help]    },
        { 157,   [mfg_specific_label],    [mfg_specific_help]    },
        { 158,   [mfg_specific_label],    [mfg_specific_help]    },
        { 159,   [mfg_specific_label],    [mfg_specific_help]    },
        { 160,   [mfg_specific_label],    [mfg_specific_help]    },
        { 161,   [mfg_specific_label],    [mfg_specific_help]    },
        { 162,   [mfg_specific_label],    [mfg_specific_help]    },
        { 163,   [mfg_specific_label],    [mfg_specific_help]    },
        { 164,   [mfg_specific_label],    [mfg_specific_help]    },
        { 165,   [mfg_specific_label],    [mfg_specific_help]    },
        { 166,   [mfg_specific_label],    [mfg_specific_help]    },
        { 167,   [mfg_specific_label],    [mfg_specific_help]    },
        { 168,   [mfg_specific_label],    [mfg_specific_help]    },
        { 169,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 170,   [mfg_specific_label],    [mfg_specific_help]    },
        { 171,   [mfg_specific_label],    [mfg_specific_help]    },
        { 172,   [mfg_specific_label],    [mfg_specific_help]    },
        { 173,   [mfg_specific_label],    [mfg_specific_help]    },
        { 174,   [mfg_specific_label],    [mfg_specific_help]    },
        { 175,   [mfg_specific_label],    [mfg_specific_help]    },
        { 176,   [mfg_specific_label],    [mfg_specific_help]    },
        { 177,   [mfg_specific_label],    [mfg_specific_help]    },
        { 178,   [mfg_specific_label],    [mfg_specific_help]    },
        { 179,   [mfg_specific_label],    [mfg_specific_help]    },
        { 180,   [mfg_specific_label],    [mfg_specific_help]    },
        { 181,   [mfg_specific_label],    [mfg_specific_help]    },
        { 182,   [mfg_specific_label],    [mfg_specific_help]    },
        { 183,   [mfg_specific_label],    [mfg_specific_help]    },
        { 184,   [mfg_specific_label],    [mfg_specific_help]    },
        { 185,   [mfg_specific_label],    [mfg_specific_help]    },
        { 186,   [mfg_specific_label],    [mfg_specific_help]    },
        { 187,   [mfg_specific_label],    [mfg_specific_help]    },
        { 188,   [mfg_specific_label],    [mfg_specific_help]    },
        { 189,   [mfg_specific_label],    [mfg_specific_help]    },
        { 190,   [mfg_specific_label],    [mfg_specific_help]    },
        { 191,   [mfg_specific_label],    [mfg_specific_help]    },
        { 192,   [mfg_specific_label],    [mfg_specific_help]    },
        { 193,   [mfg_specific_label],    [mfg_specific_help]    },
        { 194,   [mfg_specific_label],    [mfg_specific_help]    },
        { 195,   [mfg_specific_label],    [mfg_specific_help]    },
        { 196,   [mfg_specific_label],    [mfg_specific_help]    },
        { 197,   [mfg_specific_label],    [mfg_specific_help]    },
        { 198,   [mfg_specific_label],    [mfg_specific_help]    },
        { 199,   [mfg_specific_label],    [mfg_specific_help]    },
        { 200,   [mfg_specific_label],    [mfg_specific_help]    },  
        { 201,   [mfg_specific_label],    [mfg_specific_help]    },
        { 202,   [mfg_specific_label],    [mfg_specific_help]    },
        { 203,   [mfg_specific_label],    [mfg_specific_help]    },
        { 204,   [mfg_specific_label],    [mfg_specific_help]    },
        { 205,   [mfg_specific_label],    [mfg_specific_help]    },
        { 206,   [mfg_specific_label],    [mfg_specific_help]    },
        { 207,   [mfg_specific_label],    [mfg_specific_help]    },
        { 208,   [mfg_specific_label],    [mfg_specific_help]    },
        { 209,   [mfg_specific_label],    [mfg_specific_help]    },
        { 210,   [mfg_specific_label],    [mfg_specific_help]    },
        { 211,   [mfg_specific_label],    [mfg_specific_help]    },
        { 212,   [mfg_specific_label],    [mfg_specific_help]    },
        { 213,   [mfg_specific_label],    [mfg_specific_help]    },
        { 214,   [mfg_specific_label],    [mfg_specific_help]    },
        { 215,   [mfg_specific_label],    [mfg_specific_help]    },
        { 216,   [mfg_specific_label],    [mfg_specific_help]    },
        { 217,   [mfg_specific_label],    [mfg_specific_help]    },
        { 218,   [mfg_specific_label],    [mfg_specific_help]    },
        { 219,   [mfg_specific_label],    [mfg_specific_help]    },
        { 220,   [mfg_specific_label],    [mfg_specific_help]    },
        { 221,   [mfg_specific_label],    [mfg_specific_help]    },
        { 222,   [mfg_specific_label],    [mfg_specific_help]    },
        { 223,   [mfg_specific_label],    [mfg_specific_help]    },
        { 224,   [mfg_specific_label],    [mfg_specific_help]    },
        { 225,   [mfg_specific_label],    [mfg_specific_help]    },
        { 226,   [mfg_specific_label],    [mfg_specific_help]    },
        { 227,   [mfg_specific_label],    [mfg_specific_help]    },
        { 228,   [mfg_specific_label],    [mfg_specific_help]    },
        { 229,   [mfg_specific_label],    [mfg_specific_help]    },
        { 230,   [mfg_specific_label],    [mfg_specific_help]    },
        { 231,   [mfg_specific_label],    [mfg_specific_help]    },
        { 232,   [mfg_specific_label],    [mfg_specific_help]    },
        { 233,   [mfg_specific_label],    [mfg_specific_help]    },
        { 234,   [mfg_specific_label],    [mfg_specific_help]    },
        { 235,   [mfg_specific_label],    [mfg_specific_help]    },
        { 236,   [mfg_specific_label],    [mfg_specific_help]    },
        { 237,   [mfg_specific_label],    [mfg_specific_help]    },
        { 238,   [mfg_specific_label],    [mfg_specific_help]    },
        { 239,   [mfg_specific_label],    [mfg_specific_help]    },
        { 240,   [mfg_specific_label],    [mfg_specific_help]    },
        { 241,   [mfg_specific_label],    [mfg_specific_help]    },
        { 242,   [mfg_specific_label],    [mfg_specific_help]    },
        { 243,   [mfg_specific_label],    [mfg_specific_help]    },
        { 244,   [mfg_specific_label],    [mfg_specific_help]    },
        { 245,   [mfg_specific_label],    [mfg_specific_help]    },
        { 246,   [mfg_specific_label],    [mfg_specific_help]    },
        { 247,   [mfg_specific_label],    [mfg_specific_help]    },
        { 248,   [mfg_specific_label],    [mfg_specific_help]    },
        { 249,   [mfg_specific_label],    [mfg_specific_help]    },
        { 250,   [mfg_specific_label],    [mfg_specific_help]    },
        { 251,   [mfg_specific_label],    [mfg_specific_help]    },
        { 252,   [mfg_specific_label],    [mfg_specific_help]    },
        { 253,   [mfg_specific_label],    [mfg_specific_help]    },
        { 254,   [mfg_specific_label],    [mfg_specific_help]    },        
        { 255,   [mfg_specific_label],    [mfg_specific_help]    }        
    }    
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_fstate_val
%SYM%   member      XD_FSTATE_VAL        parameter         0xC0010568
%SYM%   member      VL_XD_FSTATE_VAL     variable-list     0x
%TXT%   variable    __xd_fstate_val      float             0x80020568
%IMP%   VARIABLE    __xd_fstate_val
**********************************************************************
*/
VARIABLE    __xd_fstate_val
{
    LABEL           [xd_fstate_val_label] ;
    HELP            [xd_fstate_val_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_fstate_val_d
%SYM%   member      XD_FSTATE_VAL_D         parameter           0xC00105B2
%SYM%   member      VL_XD_FSTATE_VAL_D      variable-list       0x
%TXT%   variable    __xd_fstate_val_d       unsigned            0x800205B2
%IMP%   VARIABLE    __xd_fstate_val_D
**********************************************************************
*/
VARIABLE    __xd_fstate_val_d
{
    LABEL           [xd_fstate_val_d_label] ;
    HELP            [xd_fstate_val_d_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*** END POSITIONER ***/


/*** Definitions for TABLE STRUCTURE ***/

/*
**********************************************************************
__scaling_factor
%SYM%   member      SCALING_FACTOR         parameter           0xC0010374
%SYM%   member      VL_SCALING_FACTOR      variable-list       0x
%TXT%   variable    __scaling_factor       unsigned            0x80020374
%IMP%   VARIABLE    __scaling_factor
**********************************************************************
*/
VARIABLE    __scaling_factor
{
    LABEL           [scaling_factor_label] ;
    HELP            [scaling_factor_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__num_points_supported
%SYM%   member      NUM_POINTS_SUPPORTED         parameter           0xC00104D6
%SYM%   member      VL_NUM_POINTS_SUPPORTED      variable-list       0x
%TXT%   variable    __num_points_supported       unsigned            0x800204D5
%IMP%   VARIABLE    __num_points_supported
**********************************************************************
*/
VARIABLE    __num_points_supported
{
    LABEL           [num_points_supported_label] ;
    HELP            [num_points_supported_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__min_num_points
%SYM%   member      MIN_NUM_POINTS         parameter           0xC00104D7
%SYM%   member      VL_MIN_NUM_POINTS      variable-list       0x
%TXT%   variable    __min_num_points       unsigned            0x80021738
%IMP%   VARIABLE    __min_num_points
**********************************************************************
*/
VARIABLE    __min_num_points
{
    LABEL           [min_num_points_label] ;
    HELP            [min_num_points_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__max_num_points
%SYM%   member      MAX_NUM_POINTS         parameter           0xC00104D8
%SYM%   member      VL_MAX_NUM_POINTS      variable-list       0x
%TXT%   variable    __max_num_points       unsigned            0x80021739
%IMP%   VARIABLE    __max_num_points
**********************************************************************
*/
VARIABLE    __max_num_points
{
    LABEL           [max_num_points_label] ;
    HELP            [max_num_points_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__table_element_data_type
%SYM%   member      TABLE_ELEMENT_DATA_TYPE         parameter	0xC00104D9
0xC0010
%SYM%   member      VL_TABLE_ELEMENT_DATA_TYPE      variable-list       0x
%TXT%   variable    __table_element_data_type       unsigned	0x80021740
0x80020
%IMP%   VARIABLE    __table_element_data_type
**********************************************************************
*/
VARIABLE    __table_element_data_type
{
    LABEL           [table_element_data_type_label] ;
    HELP            [table_element_data_type_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__custom_curve_description			DS-180        
%SYM%   member      CUSTOM_CURVE_DESCRIPTION         parameter          0xC0011732
%SYM%   member      VL_CUSTOM_CURVE_DESCRIPTION      variable-list      0xC0011732
%TXT%   record      __custom_curve_description                		0x80021741
%IMP%   RECORD      custom_curve_description
%IMP%       VARIABLE    __min_num_points
%IMP%       VARIABLE    __max_num_points
%IMP%       VARIABLE    __table_element_data_type
**********************************************************************
*/
RECORD      __custom_curve_description
{
    LABEL           [custom_curve_description] ;
    HELP            [custom_curve_description_help] ;
    MEMBERS
    {
        MIN_NUM_POINTS,      __min_num_points ;
        MAX_NUM_POINTS,      __max_num_points ;
        TABLE_ELEMENT_DATA_TYPE,   __table_element_data_type ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__x1_value_f
**********************************************************************
*/
VARIABLE    __x1_value_f
{
    LABEL           [x1_value_f_label] ;
    HELP            [x1_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x2_value_f
**********************************************************************
*/
VARIABLE    __x2_value_f
{
    LABEL           [x2_value_f_label] ;
    HELP            [x2_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x3_value_f
**********************************************************************
*/
VARIABLE    __x3_value_f
{
    LABEL           [x3_value_f_label] ;
    HELP            [x3_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x4_value_f
**********************************************************************
*/
VARIABLE    __x4_value_f
{
    LABEL           [x4_value_f_label] ;
    HELP            [x4_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x5_value_f
**********************************************************************
*/
VARIABLE    __x5_value_f
{
    LABEL           [x5_value_f_label] ;
    HELP            [x5_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x6_value_f
**********************************************************************
*/
VARIABLE    __x6_value_f
{
    LABEL           [x6_value_f_label] ;
    HELP            [x6_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x7_value_f
**********************************************************************
*/
VARIABLE    __x7_value_f
{
    LABEL           [x7_value_f_label] ;
    HELP            [x7_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x8_value_f
**********************************************************************
*/
VARIABLE    __x8_value_f
{
    LABEL           [x8_value_f_label] ;
    HELP            [x8_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x9_value_f
**********************************************************************
*/
VARIABLE    __x9_value_f
{
    LABEL           [x9_value_f_label] ;
    HELP            [x9_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x10_value_f
**********************************************************************
*/
VARIABLE    __x10_value_f
{
    LABEL           [x10_value_f_label] ;
    HELP            [x10_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x11_value_f
**********************************************************************
*/
VARIABLE    __x11_value_f
{
    LABEL           [x11_value_f_label] ;
    HELP            [x11_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x12_value_f
**********************************************************************
*/
VARIABLE    __x12_value_f
{
    LABEL           [x12_value_f_label] ;
    HELP            [x12_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x13_value_f
**********************************************************************
*/
VARIABLE    __x13_value_f
{
    LABEL           [x13_value_f_label] ;
    HELP            [x13_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x14_value_f
**********************************************************************
*/
VARIABLE    __x14_value_f
{
    LABEL           [x14_value_f_label] ;
    HELP            [x14_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y1_value_f
**********************************************************************
*/
VARIABLE    __y1_value_f
{
    LABEL           [y1_value_f_label] ;
    HELP            [y1_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y2_value_f
**********************************************************************
*/
VARIABLE    __y2_value_f
{
    LABEL           [y2_value_f_label] ;
    HELP            [y2_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y3_value_f
**********************************************************************
*/
VARIABLE    __y3_value_f
{
    LABEL           [y3_value_f_label] ;
    HELP            [y3_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y4_value_f
**********************************************************************
*/
VARIABLE    __y4_value_f
{
    LABEL           [y4_value_f_label] ;
    HELP            [y4_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y5_value_f
**********************************************************************
*/
VARIABLE    __y5_value_f
{
    LABEL           [y5_value_f_label] ;
    HELP            [y5_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y6_value_f
**********************************************************************
*/
VARIABLE    __y6_value_f
{
    LABEL           [y6_value_f_label] ;
    HELP            [y6_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y7_value_f
**********************************************************************
*/
VARIABLE    __y7_value_f
{
    LABEL           [y7_value_f_label] ;
    HELP            [y7_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y8_value_f
**********************************************************************
*/
VARIABLE    __y8_value_f
{
    LABEL           [y8_value_f_label] ;
    HELP            [y8_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y9_value_f
**********************************************************************
*/
VARIABLE    __y9_value_f
{
    LABEL           [y9_value_f_label] ;
    HELP            [y9_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y10_value_f
**********************************************************************
*/
VARIABLE    __y10_value_f
{
    LABEL           [y10_value_f_label] ;
    HELP            [y10_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y11_value_f
**********************************************************************
*/
VARIABLE    __y11_value_f
{
    LABEL           [y11_value_f_label] ;
    HELP            [y11_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y12_value_f
**********************************************************************
*/
VARIABLE    __y12_value_f
{
    LABEL           [y12_value_f_label] ;
    HELP            [y12_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y13_value_f
**********************************************************************
*/
VARIABLE    __y13_value_f
{
    LABEL           [y13_value_f_label] ;
    HELP            [y13_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y14_value_f
**********************************************************************
*/
VARIABLE    __y14_value_f
{
    LABEL           [y14_value_f_label] ;
    HELP            [y14_value_f_help] ;
    TYPE            FLOAT ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__custom_curve_xy_float                                    DS-182
%SYM%   member      CUSTOM_CURVE_XY_FLOAT         parameter          0xC0011734
%SYM%   member      VL_CUSTOM_CURVE_XY_FLOAT      variable-list      0xC0011735
%TXT%   record      __custom_curve_xy_float                0x80021742
%IMP%   RECORD      custom_curve_xy_float
%IMP%       VARIABLE    __num_points_supported		   
%IMP%       VARIABLE       __x_value_f (14)
%IMP%       VARIABLE       __y_value_f (14)
**********************************************************************
*/

RECORD      __custom_curve_xy_float    
{
    LABEL           [custom_curve_xy_float] ;
    HELP            [custom_curve_xy_float_help] ;
    MEMBERS
    {
        NUM_POINTS_SUPPORTED,       __num_points_supported ;
        X1_VALUE_F,                 __x1_value_f ;
        X2_VALUE_F,                 __x2_value_f ;
        X3_VALUE_F,                 __x3_value_f ;
        X4_VALUE_F,                 __x4_value_f ;
        X5_VALUE_F,                 __x5_value_f ;
        X6_VALUE_F,                 __x6_value_f ;
        X7_VALUE_F,                 __x7_value_f ;
        X8_VALUE_F,                 __x8_value_f ;
        X9_VALUE_F,                 __x9_value_f ;
        X10_VALUE_F,                __x10_value_f ;
        X11_VALUE_F,                __x11_value_f ;
        X12_VALUE_F,                __x12_value_f ;
        X13_VALUE_F,                __x13_value_f ;
        X14_VALUE_F,                __x14_value_f ;
        Y1_VALUE_F,                 __y1_value_f ;
        Y2_VALUE_F,                 __y2_value_f ;
        Y3_VALUE_F,                 __y3_value_f ;
        Y4_VALUE_F,                 __y4_value_f ;
        Y5_VALUE_F,                 __y5_value_f ;
        Y6_VALUE_F,                 __y6_value_f ;
        Y7_VALUE_F,                 __y7_value_f ;
        Y8_VALUE_F,                 __y8_value_f ;
        Y9_VALUE_F,                 __y9_value_f ;
        Y10_VALUE_F,                __y10_value_f ;
        Y11_VALUE_F,                __y11_value_f ;
        Y12_VALUE_F,                __y12_value_f ;
        Y13_VALUE_F,                __y13_value_f ;
        Y14_VALUE_F,                __y14_value_f ;
    }
}


/*
**********************************************************************
__x1_value_u
**********************************************************************
*/
VARIABLE    __x1_value_u
{
    LABEL           [x1_value_u_label] ;
    HELP            [x1_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x2_value_u
**********************************************************************
*/
VARIABLE    __x2_value_u
{
    LABEL           [x2_value_u_label] ;
    HELP            [x2_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x3_value_u
**********************************************************************
*/
VARIABLE    __x3_value_u
{
    LABEL           [x3_value_u_label] ;
    HELP            [x3_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x4_value_u
**********************************************************************
*/
VARIABLE    __x4_value_u
{
    LABEL           [x4_value_u_label] ;
    HELP            [x4_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x5_value_u
**********************************************************************
*/
VARIABLE    __x5_value_u
{
    LABEL           [x5_value_u_label] ;
    HELP            [x5_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x6_value_u
**********************************************************************
*/
VARIABLE    __x6_value_u
{
    LABEL           [x6_value_u_label] ;
    HELP            [x6_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x7_value_u
**********************************************************************
*/
VARIABLE    __x7_value_u
{
    LABEL           [x7_value_u_label] ;
    HELP            [x7_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x8_value_u
**********************************************************************
*/
VARIABLE    __x8_value_u
{
    LABEL           [x8_value_u_label] ;
    HELP            [x8_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x9_value_u
**********************************************************************
*/
VARIABLE    __x9_value_u
{
    LABEL           [x9_value_u_label] ;
    HELP            [x9_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x10_value_u
**********************************************************************
*/
VARIABLE    __x10_value_u
{
    LABEL           [x10_value_u_label] ;
    HELP            [x10_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x11_value_u
**********************************************************************
*/
VARIABLE    __x11_value_u
{
    LABEL           [x11_value_u_label] ;
    HELP            [x11_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x12_value_u
**********************************************************************
*/
VARIABLE    __x12_value_u
{
    LABEL           [x12_value_u_label] ;
    HELP            [x12_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x13_value_u
**********************************************************************
*/
VARIABLE    __x13_value_u
{
    LABEL           [x13_value_u_label] ;
    HELP            [x13_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x14_value_u
**********************************************************************
*/
VARIABLE    __x14_value_u
{
    LABEL           [x14_value_u_label] ;
    HELP            [x14_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x15_value_u
**********************************************************************
*/
VARIABLE    __x15_value_u
{
    LABEL           [x15_value_u_label] ;
    HELP            [x15_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x16_value_u
**********************************************************************
*/
VARIABLE    __x16_value_u
{
    LABEL           [x16_value_u_label] ;
    HELP            [x16_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x17_value_u
**********************************************************************
*/
VARIABLE    __x17_value_u
{
    LABEL           [x17_value_u_label] ;
    HELP            [x17_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x18_value_u
**********************************************************************
*/
VARIABLE    __x18_value_u
{
    LABEL           [x18_value_u_label] ;
    HELP            [x18_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x19_value_u
**********************************************************************
*/
VARIABLE    __x19_value_u
{
    LABEL           [x19_value_u_label] ;
    HELP            [x19_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x20_value_u
**********************************************************************
*/
VARIABLE    __x20_value_u
{
    LABEL           [x20_value_u_label] ;
    HELP            [x20_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x21_value_u
**********************************************************************
*/
VARIABLE    __x21_value_u
{
    LABEL           [x21_value_u_label] ;
    HELP            [x21_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x22_value_u
**********************************************************************
*/
VARIABLE    __x22_value_u
{
    LABEL           [x22_value_u_label] ;
    HELP            [x22_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x23_value_u
**********************************************************************
*/
VARIABLE    __x23_value_u
{
    LABEL           [x23_value_u_label] ;
    HELP            [x23_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x24_value_u
**********************************************************************
*/
VARIABLE    __x24_value_u
{
    LABEL           [x24_value_u_label] ;
    HELP            [x24_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x25_value_u
**********************************************************************
*/
VARIABLE    __x25_value_u
{
    LABEL           [x25_value_u_label] ;
    HELP            [x25_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x26_value_u
**********************************************************************
*/
VARIABLE    __x26_value_u
{
    LABEL           [x26_value_u_label] ;
    HELP            [x26_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x27_value_u
**********************************************************************
*/
VARIABLE    __x27_value_u
{
    LABEL           [x27_value_u_label] ;
    HELP            [x27_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x28_value_u
**********************************************************************
*/
VARIABLE    __x28_value_u
{
    LABEL           [x28_value_u_label] ;
    HELP            [x28_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__x29_value_u
**********************************************************************
*/
VARIABLE    __x29_value_u
{
    LABEL           [x29_value_u_label] ;
    HELP            [x29_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y1_value_u
**********************************************************************
*/
VARIABLE    __y1_value_u
{
    LABEL           [y1_value_u_label] ;
    HELP            [y1_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y2_value_u
**********************************************************************
*/
VARIABLE    __y2_value_u
{
    LABEL           [y2_value_u_label] ;
    HELP            [y2_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y3_value_u
**********************************************************************
*/
VARIABLE    __y3_value_u
{
    LABEL           [y3_value_u_label] ;
    HELP            [y3_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y4_value_u
**********************************************************************
*/
VARIABLE    __y4_value_u
{
    LABEL           [y4_value_u_label] ;
    HELP            [y4_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y5_value_u
**********************************************************************
*/
VARIABLE    __y5_value_u
{
    LABEL           [y5_value_u_label] ;
    HELP            [y5_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y6_value_u
**********************************************************************
*/
VARIABLE    __y6_value_u
{
    LABEL           [y6_value_u_label] ;
    HELP            [y6_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y7_value_u
**********************************************************************
*/
VARIABLE    __y7_value_u
{
    LABEL           [y7_value_u_label] ;
    HELP            [y7_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y8_value_u
**********************************************************************
*/
VARIABLE    __y8_value_u
{
    LABEL           [y8_value_u_label] ;
    HELP            [y8_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y9_value_u
**********************************************************************
*/
VARIABLE    __y9_value_u
{
    LABEL           [y9_value_u_label] ;
    HELP            [y9_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y10_value_u
**********************************************************************
*/
VARIABLE    __y10_value_u
{
    LABEL           [y10_value_u_label] ;
    HELP            [y10_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y11_value_u
**********************************************************************
*/
VARIABLE    __y11_value_u
{
    LABEL           [y11_value_u_label] ;
    HELP            [y11_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y12_value_u
**********************************************************************
*/
VARIABLE    __y12_value_u
{
    LABEL           [y12_value_u_label] ;
    HELP            [y12_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y13_value_u
**********************************************************************
*/
VARIABLE    __y13_value_u
{
    LABEL           [y13_value_u_label] ;
    HELP            [y13_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y14_value_u
**********************************************************************
*/
VARIABLE    __y14_value_u
{
    LABEL           [y14_value_u_label] ;
    HELP            [y14_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y15_value_u
**********************************************************************
*/
VARIABLE    __y15_value_u
{
    LABEL           [y15_value_u_label] ;
    HELP            [y15_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y16_value_u
**********************************************************************
*/
VARIABLE    __y16_value_u
{
    LABEL           [y16_value_u_label] ;
    HELP            [y16_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y17_value_u
**********************************************************************
*/
VARIABLE    __y17_value_u
{
    LABEL           [y17_value_u_label] ;
    HELP            [y17_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y18_value_u
**********************************************************************
*/
VARIABLE    __y18_value_u
{
    LABEL           [y18_value_u_label] ;
    HELP            [y18_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y19_value_u
**********************************************************************
*/
VARIABLE    __y19_value_u
{
    LABEL           [y19_value_u_label] ;
    HELP            [y19_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y20_value_u
**********************************************************************
*/
VARIABLE    __y20_value_u
{
    LABEL           [y20_value_u_label] ;
    HELP            [y20_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y21_value_u
**********************************************************************
*/
VARIABLE    __y21_value_u
{
    LABEL           [y21_value_u_label] ;
    HELP            [y21_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y22_value_u
**********************************************************************
*/
VARIABLE    __y22_value_u
{
    LABEL           [y22_value_u_label] ;
    HELP            [y22_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y23_value_u
**********************************************************************
*/
VARIABLE    __y23_value_u
{
    LABEL           [y23_value_u_label] ;
    HELP            [y23_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y24_value_u
**********************************************************************
*/
VARIABLE    __y24_value_u
{
    LABEL           [y24_value_u_label] ;
    HELP            [y24_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y25_value_u
**********************************************************************
*/
VARIABLE    __y25_value_u
{
    LABEL           [y25_value_u_label] ;
    HELP            [y25_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y26_value_u
**********************************************************************
*/
VARIABLE    __y26_value_u
{
    LABEL           [y26_value_u_label] ;
    HELP            [y26_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y27_value_u
**********************************************************************
*/
VARIABLE    __y27_value_u
{
    LABEL           [y27_value_u_label] ;
    HELP            [y27_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y28_value_u
**********************************************************************
*/
VARIABLE    __y28_value_u
{
    LABEL           [y28_value_u_label] ;
    HELP            [y28_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__y29_value_u
**********************************************************************
*/
VARIABLE    __y29_value_u
{
    LABEL           [y29_value_u_label] ;
    HELP            [y29_value_u_help] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED & SERVICE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__custom_curve_xy                                DS-181
%TXT%   record      __custom_curve_xy            0x80021743
%IMP%   RECORD      custom_curve_xy
%IMP%       VARIABLE    __num_points_supported
%IMP%       VARIABLE       __x_value_u (29)
%IMP%       VARIABLE       __y_value_u (29)
%IMP%       VARIABLE      __scaling_factor
**********************************************************************
*/


RECORD      __custom_curve_xy
{
    LABEL           [custom_curve_xy] ;
    HELP            [custom_curve_xy_help] ;
    MEMBERS
    {
        NUM_POINTS_SUPPORTED,       __num_points_supported ;
        X1_VALUE_U,                 __x1_value_u ;
        X2_VALUE_U,                 __x2_value_u ;
        X3_VALUE_U,                 __x3_value_u ;
        X4_VALUE_U,                 __x4_value_u ;
        X5_VALUE_U,                 __x5_value_u ;
        X6_VALUE_U,                 __x6_value_u ;
        X7_VALUE_U,                 __x7_value_u ;
        X8_VALUE_U,                 __x8_value_u ;
        X9_VALUE_U,                 __x9_value_u ;
        X10_VALUE_U,                __x10_value_u ;
        X11_VALUE_U,                __x11_value_u ;
        X12_VALUE_U,                __x12_value_u ;
        X13_VALUE_U,                __x13_value_u ;
        X14_VALUE_U,                __x14_value_u ;
        X15_VALUE_U,                __x15_value_u ;
        X16_VALUE_U,                __x16_value_u ;
        X17_VALUE_U,                __x17_value_u ;
        X18_VALUE_U,                __x18_value_u ;
        X19_VALUE_U,                __x19_value_u ;
        X20_VALUE_U,                __x20_value_u ;
        X21_VALUE_U,                __x21_value_u ;
        X22_VALUE_U,                __x22_value_u ;
        X23_VALUE_U,                __x23_value_u ;
        X24_VALUE_U,                __x24_value_u ;
        X25_VALUE_U,                __x25_value_u ;
        X26_VALUE_U,                __x26_value_u ;
        X27_VALUE_U,                __x27_value_u ;
        X28_VALUE_U,                __x28_value_u ;
        X29_VALUE_U,                __x29_value_u ;
        Y1_VALUE_U,                 __y1_value_u ;
        Y2_VALUE_U,                 __y2_value_u ;
        Y3_VALUE_U,                 __y3_value_u ;
        Y4_VALUE_U,                 __y4_value_u ;
        Y5_VALUE_U,                 __y5_value_u ;
        Y6_VALUE_U,                 __y6_value_u ;
        Y7_VALUE_U,                 __y7_value_u ;
        Y8_VALUE_U,                 __y8_value_u ;
        Y9_VALUE_U,                 __y9_value_u ;
        Y10_VALUE_U,                __y10_value_u ;
        Y11_VALUE_U,                __y11_value_u ;
        Y12_VALUE_U,                __y12_value_u ;
        Y13_VALUE_U,                __y13_value_u ;
        Y14_VALUE_U,                __y14_value_u ;
        Y15_VALUE_U,                __y15_value_u ;
        Y16_VALUE_U,                __y16_value_u ;
        Y17_VALUE_U,                __y17_value_u ;
        Y18_VALUE_U,                __y18_value_u ;
        Y19_VALUE_U,                __y19_value_u ;
        Y20_VALUE_U,                __y20_value_u ;
        Y21_VALUE_U,                __y21_value_u ;
        Y22_VALUE_U,                __y22_value_u ;
        Y23_VALUE_U,                __y23_value_u ;
        Y24_VALUE_U,                __y24_value_u ;
        Y25_VALUE_U,                __y25_value_u ;
        Y26_VALUE_U,                __y26_value_u ;
        Y27_VALUE_U,                __y27_value_u ;
        Y28_VALUE_U,                __y28_value_u ;
        Y29_VALUE_U,                __y29_value_u ;
        SCALING_FACTOR_TB,          __scaling_factor ;
    }
}


/*** END Definitions for TABLE STRUCTURE ***/

/*
**********************************************************************
__secondary_value_range        (DS-68)
%SYM%   member	SECONDARY_VALUE_RANGE		parameter	0xC001177A      
%SYM%   member	VL_SECONDARY_VALUE_RANGE	variable-list	0xC001177B
%TXT%   record      __secondary_value_range                    0x80020338
%IMP%   RECORD      __secondary_value_range
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __secondary_value_range
{
    LABEL           [secondary_value_range_label] ;
    HELP            [secondary_value_range_help] ;
    MEMBERS
    {
        EU_100,      __eu_100_srv ;
        EU_0,        __eu_0_srv ;
        UNITS_INDEX,  __units_index_srv ;
        DECIMAL,     __decimal_srv ;
    }
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__secondary_value_type
%SYM%   member      SECONDARY_VALUE_TYPE      parameter      0xC0010380
%SYM%   member      VL_SECONDARY_VALUE_TYPE   variable-list  0xC0010381
%TXT%   variable    __secondary_value_type    enumerated     0x80020380
%IMP%   VARIABLE    __secondary_value_type
**********************************************************************
*/
VARIABLE    __secondary_value_type
{
    LABEL           [secondary_value_type_label] ;
    HELP            [secondary_value_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        { 100,  [mass_flow_label],          [mass_flow_help] },
        { 101,  [volume_flow_label],        [volume_flow_help] },
        { 102,  [avg_mass_flow_label],      [avg_mass_flow_help] },
        { 103,  [avg_volume_flow_label],    [avg_volume_flow_help] },
        { 104,  [process_temp_label],       [process_temp_help] },
        { 105,  [non_process_temp_label],   [non_process_temp_help] },
        { 106,  [diff_temp_label],          [diff_temp_help] },
        { 107,  [diff_press_label],         [diff_press_help]},
        { 108,  [gauge_press_label],        [gauge_press_help] },
        { 109,  [absolute_press_label],     [absolute_press_help] },
        { 255,  [other],                    [other_help] }
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__signal_action
%SYM%   member      SIGNAL_ACTION         parameter           0xC0010374
%SYM%   member      VL_SIGNAL_ACTION      variable-list       0x
%TXT%   variable    __signal_action       enumerated          0x80020374
%IMP%   VARIABLE    __signal_action
**********************************************************************
*/
VARIABLE    __signal_action
{
    LABEL           [signal_action_label] ;
    HELP            [signal_action_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1) 
    {
        { 0,  [increase_to_open_label],         [increase_to_open_help] },
        { 1,  [increase_to_close_label],        [increase_to_close_help] }
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__final_position_value_d            (DS-66)
%SYM%   member      FINAL_POSITION_VALUE_D       parameter         0xC0010366
%SYM%   member      VL_FINAL_POSITION_VALUE_D    variable-list     0xC0010367
%TXT%   record      __final_position_value_d                       0x80020366
%IMP%   RECORD      __final_position_value_d
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __discrete_input
**********************************************************************
*/
RECORD      __final_position_value_d
{
    LABEL           [final_position_value_d_label] ;
    HELP            [final_position_value_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __discrete_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stop_hi_pos
%SYM%   member      STOP_HI_POS           parameter           0xC0011728
%SYM%   member      VL_STOP_HI_POS        variable-list       0xC0011729
%TXT%   variable    __stop_hi_pos         float               0x80021745
%IMP%   VARIABLE    __stop_hi_pos
**********************************************************************
*/
VARIABLE    __stop_hi_pos
{
    LABEL           [stop_hi_pos_label] ;
    HELP            [stop_hi_pos_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [unit_code_1342] ; /* % */
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stop_lo_pos
%SYM%   member      STOP_LO_POS           parameter           0xC001172A
%SYM%   member      VL_STOP_LO_POS        variable-list       0xC001172B
%TXT%   variable    __stop_lo_pos         float               0x80021746
%IMP%   VARIABLE    __stop_lo_pos
**********************************************************************
*/
VARIABLE    __stop_lo_pos
{
    LABEL           [stop_lo_pos_label] ;
    HELP            [stop_lo_pos_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [unit_code_1342] ; /* % */
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__xd_oos_opt
%SYM%   member      XD_OOS_OPT           parameter           0xC001172C
%SYM%   member      VL_XD_OOS_OPT        variable-list       0xC001172D
%TXT%   variable    __xd_oos_opt         enumerated          0x80021747
%IMP%   VARIABLE    __xd_oos_opt
**********************************************************************
*/
VARIABLE    __xd_oos_opt
{
    LABEL           [xd_oos_opt_label] ;
    HELP            [xd_oos_opt_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (1)
    {
        { 0,  [xd_oos_opt_0],	[xd_oos_opt_0_help] },
        { 1,  [xd_oos_opt_1],	[xd_oos_opt_1_help] },
        { 2,  [xd_oos_opt_2],	[xd_oos_opt_2_help] },
        { 3,  [xd_oos_opt_3],	[xd_oos_opt_3_help] }
    }
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [blank] ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vst_pause
%SYM%   member      VST_PAUSE             parameter           0xC001172E
%SYM%   member      VL_VST_PAUSE          variable-list       0xC001172F
%TXT%   variable    __vst_pause        	  float               0x80021748
%IMP%   VARIABLE    __vst_pause
**********************************************************************
*/
VARIABLE    __vst_pause
{
    LABEL           [vst_pause_label] ;
    HELP            [vst_pause_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [unit_code_1054] ; /* s */
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__vst_detailed_result
%SYM%   member      VST_DETAILED_RESULT         parameter           0xC0011730
%SYM%   member      VL_VST_DETAILED_RESULT      variable-list       0xC0011731
%TXT%   variable    __vst_detailed_result       bit-enumerated      0x80021749
%IMP%   VARIABLE    __vst_detailed_result
**********************************************************************
*/
VARIABLE    __vst_detailed_result
{
    LABEL           [vst_dtld_rslt_label] ;
    HELP            [vst_dtld_rslt_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,	[vst_dtld_rslt_0],	[vst_dtld_rslt_0_help] },
        { 0x0002,	[vst_dtld_rslt_1],	[vst_dtld_rslt_1_help] },
        { 0x0004,	[vst_dtld_rslt_2],	[vst_dtld_rslt_2_help] },
        { 0x0008,	[vst_dtld_rslt_3],	[vst_dtld_rslt_3_help] },
        { 0x0010,	[vst_dtld_rslt_4],	[vst_dtld_rslt_4_help] },
        { 0x0020,	[vst_dtld_rslt_5],	[vst_dtld_rslt_5_help] }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pressure_units
%SYM%   member      PRESSURE_UNITS          parameter           0xC0011744
%SYM%   member      VL_PRESSURE_UNITS       variable-list       0xC0011745
%TXT%   variable    __pressure_units        enumerated          0x800204EB
%IMP%   VARIABLE    __pressure_units
**********************************************************************
*/
VARIABLE    __pressure_units
{
    LABEL           [pressure_units_label] ;
    HELP            [pressure_units_help] ;
    CLASS           CONTAINED & SERVICE ;
    TYPE            ENUMERATED (2)
    {
        __UNITS_CODES1
        __UNITS_CODES2
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_value           (DS-65)
%SYM%   member     CAL_VALUE       parameter      0xC0011778
%SYM%   member     VL_WCAL_VALUE   variable-list  0xC0011779
%TXT%   record     __cal_value                    0x8002174A
%IMP%   RECORD     __cal_value
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __cal_value
{
    LABEL           [cal_value_label] ;
    HELP            [cal_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_value_1           (DS-65)
%SYM%   member     CAL_VALUE_1       parameter      0xC001177E
%SYM%   member     VL_CAL_VALUE_1   variable-list  0xC0011780
%TXT%   record     __cal_value_1                    0x80021753
%IMP%   RECORD     __cal_value_1
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __cal_value_1
{
    LABEL           [cal_value_1_label] ;
    HELP            [cal_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__cal_value_2           (DS-65)
%SYM%   member     CAL_VALUE_2       parameter      0xC001177F
%SYM%   member     VL_CAL_VALUE_2   variable-list  0xC0011781
%TXT%   record     __cal_value_2                    0x80021754
%IMP%   RECORD     __cal_value_2
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __cal_value_2
{
    LABEL           [cal_value_1_label] ;
    HELP            [cal_value_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__block_err_desc_1_flow   
%SYM%   member     BLOCK_ERR_DESC_1       parameter      0xC0011782
%SYM%   member     VL_BLOCK_ERR_DESC_1   variable-list  0xC0011783
%TXT%   variable     __block_err_desc_1_flow   bit-enumerated  0x80021755
%IMP%   VARIABLE     __block_err_desc_1_flow
**********************************************************************
*/
VARIABLE    __block_err_desc_1_flow
{
    LABEL           [block_err_desc];
    HELP            [block_err_desc_help];
    CLASS           CONTAINED & DIAGNOSTIC;
    TYPE            BIT_ENUMERATED (4)
    {
        {0x00000001,"Manufacturer specific configuration errors.",[no_help_available]}
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
