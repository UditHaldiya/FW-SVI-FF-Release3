/*
** @(#)std_parm.ddl 1.7 2002-06-09
**
** FF common definitions
** Filename: std_parm.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.2 FBAP spec part 1
**                  FF-891 FS 1.2 FBAP spec part 2
** Date of last change: 2005-11-09
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
** (c) Fieldbus Foundation(TM) (1994-2005)
**
*/

/*
** HISTORY:
**  JPH Revision 0.9  19960430
**  TAB Revision 1.0  19961015
**  DAD Revision 1.1  12MAY97
**      Corrected __control_opts, __io_opts, __status_opts to FF-891-1.2
**      Added Units Codes to __units_index.
**  QLQ Revision 1.2  06NOV97
**      AR#212: Changed all fail-safe to fault-state.
**      AR#219: Added parameter __on_off_input_nd.
**      AR#222: Added enumeration member "low_cutoff" in IO_OPTS.
**      AR#217: Added ALARM or TUNE class to all applicable parameters
**                see FBAP Pt.2 Parameter Table 5.2
**      AR#245: Corrected all parameters with type DS-71 to show value type as a float.
**  QLQ Revision 1.3  19NOV97
**      Change __manufac_id from unsigned to enumerated with __FF_MFR_INDEX in Com_tbls.h
**      Change UNITS_CODES to reference from Com_tbls.h
**  DAD Revision 1.4  1999-03-04
**      added new system for dev rev and dd rev
**  DAD Revision 1.5  1999-06-10
**      added symbols for VIEW_3_2 thru 17, View_4_2 thru 17.
**      SBM Revision 1.6  1999-12-01
**              added definitions for new resource block parameters __itk_ver
**  SBM Revision 1.7  2002-06-09
**              reset __manufac_id to unsigned.  Manufacturers can redefine parameter to add their registered name
**              changed units on __itk_ver to [blank]
**      changed __UNITS_CODES to __UNITS_CODES1 and __UNITS_CODES2 due to bug in Tokenizer 4.2
**  FI  Revision 1.8  2005-11-09
**      changed several variables to class OPERATE according to AR#1262
**      changed several variables to class ALARM according to AR#1262
**      changed several variables to class TUNE according to AR#1262
**      fixed enumerations for __on_off_input_nd
**      added __on_off_contained_r and __on_off_output_nd for FBAP Part 3 blocks
**      fixed __unacknowledged according to AR#657
**      changed __channel to enumerated
**      fixed constant unit for __confirm_time,__min_cycle_t,__nv_cycle_t,__shed_rcas,__shed_rout according to AR#667
**      fixed __control_opts according to AR#705
**      changed __dev_type to enumerated
**      added bypass to __feature_sel and __features according to AR#703
**      fixed __io_opts according to AR#222
**      changed __manufac_id to enumerated
**      fixed __status_opts according to ARs 706 and 1299
**      changed __trk_in_d according to AR 219
**      added block specific status opts,control opts,io opts,current summary,
**        unacked summary, unreported summary,disabled summary,ack option, and
**        alarm summary according to AR#708
**      added variables for resource block 3
**  MS	added/updated items for programmable resource; AR2668 16-Nov-07
**  TAB added __ack_option_ft, __alarm_sum_ft for flow totalizer
** MS   ARs 2123, 2126, 2128, 2197, 2883, 2901 -- 2008.10.07
** MS   ARs 3999, 4000, 4116, 2227, 3102, 3225, 3236, 3438, 4143, 4209 -- 2009.06.15
** MS   ARs 4815, 3438, 5095, 4228, 4461, 4487, 4624, 4658, 5291 -- 2010.06.14
** MS   ARs 5632 -- 2011.04.13
*/

#include "com_tbls.h"
/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __STD_PARM,
DEVICE_REVISION __STD_PARM_rel_dev_rev,
DD_REVISION     __STD_PARM_rel_dd_rev

/*
**********************************************************************
** Block Data Structure (DS-64)
** The following variables make up a block record (DS-64) as defined
** by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__block_tag
%SYM%   member      BLOCK_TAG           record              0xC0010001
%TXT%   variable    __block_tag         visible             0x80020001
%IMP%   VARIABLE    __block_tag
**********************************************************************
*/
VARIABLE    __block_tag
{
    LABEL           [block_tag] ;
    HELP            [block_tag_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dd_member
%SYM%   member      DD_MEMBER           record              0xC0010002
%TXT%   variable    __dd_member         unsigned            0x80020002
%IMP%   VARIABLE    __dd_member
**********************************************************************
*/
VARIABLE    __dd_member
{
    LABEL           [dd_member] ;
    HELP            [dd_member_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dd_item
%SYM%   member      DD_ITEM             record              0xC0010003
%TXT%   variable    __dd_item           unsigned            0x80020003
%IMP%   VARIABLE    __dd_item
**********************************************************************
*/
VARIABLE    __dd_item
{
    LABEL           [dd_item] ;
    HELP            [dd_item_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dd_revis
%SYM%   member      DD_REVIS            record              0xC0010004
%TXT%   variable    __dd_revis          unsigned            0x80020004
%IMP%   VARIABLE    __dd_revis
**********************************************************************
*/
VARIABLE    __dd_revis
{
    LABEL           [dd_revis] ;
    HELP            [dd_revis_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__profile
%SYM%   member      PROFILE             record              0xC0010005
%TXT%   variable    __profile           unsigned            0x80020005
%IMP%   VARIABLE    __profile
**********************************************************************
*/
VARIABLE    __profile
{
    LABEL           [profile] ;
    HELP            [profile_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__profile_revision
%SYM%   member      PROFILE_REVISION    record              0xC0010006
%TXT%   variable    __profile_revision  unsigned            0x80020006
%IMP%   VARIABLE    __profile_revision
**********************************************************************
*/
VARIABLE    __profile_revision
{
    LABEL           [profile_revision] ;
    HELP            [profile_revision_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__execution_time
%SYM%   member      EXECUTION_TIME      record              0xC0010007
%TXT%   variable    __execution_time    unsigned            0x80020007
%IMP%   VARIABLE    __execution_time
**********************************************************************
*/
VARIABLE    __execution_time
{
    LABEL           [execution_time] ;
    HELP            [execution_time_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__execution_period
%SYM%   member      EXECUTION_PERIOD    record              0xC0010008
%TXT%   variable    __execution_period  unsigned            0x80020008
%IMP%   VARIABLE    __execution_period
**********************************************************************
*/
VARIABLE    __execution_period
{
    LABEL           [execution_period] ;
    HELP            [execution_period_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__num_of_params
%SYM%   member      NUM_OF_PARAMS       record              0xC0010009
%TXT%   variable    __num_of_params     unsigned            0x80020009
%IMP%   VARIABLE    __num_of_params
**********************************************************************
*/
VARIABLE    __num_of_params
{
    LABEL           [num_of_params] ;
    HELP            [num_of_params_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__next_fb_to_execute
%SYM%   member      NEXT_FB_TO_EXECUTE  record              0xC001000A
%TXT%   variable    __next_fb_to_execute    unsigned        0x8002000A
%IMP%   VARIABLE    __next_fb_to_execute
**********************************************************************
*/
VARIABLE    __next_fb_to_execute
{
    LABEL           [next_fb_to_execute] ;
    HELP            [next_fb_to_execute_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__views_index
%SYM%   member      VIEWS_INDEX         record              0xC001000B
%TXT%   variable    __views_index       unsigned            0x8002000B
%IMP%   VARIABLE    __views_index
**********************************************************************
*/
VARIABLE    __views_index
{
    LABEL           [views_index] ;
    HELP            [views_index_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__views_index32
%SYM%   member      VIEWS_INDEX         record              0xC001000B
%TXT%   variable    __views_index32       unsigned            0x80020B55
%IMP%   VARIABLE    __views_index32
**********************************************************************
*/
VARIABLE    __views_index32
{
    LABEL           [views_index] ;
    HELP            [views_index_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__number_view_3
%SYM%   member      NUMBER_VIEW_3       record              0xC001000C
%TXT%   variable    __number_view_3     unsigned            0x8002000C
%IMP%   VARIABLE    __number_view_3
**********************************************************************
*/
VARIABLE    __number_view_3
{
    LABEL           [number_view_3] ;
    HELP            [number_view_3_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__number_view_4
%SYM%   member      NUMBER_VIEW_4       record              0xC001000D
%TXT%   variable    __number_view_4     unsigned            0x8002000D
%IMP%   VARIABLE    __number_view_4
**********************************************************************
*/
VARIABLE    __number_view_4
{
    LABEL           [number_view_4] ;
    HELP            [number_view_4_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__blk_char
%TXT%   record      __blk_char                              0x8002000E
%IMP%   RECORD      __blk_char
%IMP%       VARIABLE    __block_tag
%IMP%       VARIABLE    __dd_member
%IMP%       VARIABLE    __dd_item
%IMP%       VARIABLE    __dd_revis
%IMP%       VARIABLE    __profile
%IMP%       VARIABLE    __profile_revision
%IMP%       VARIABLE    __execution_time
%IMP%       VARIABLE    __execution_period
%IMP%       VARIABLE    __num_of_params
%IMP%       VARIABLE    __next_fb_to_execute
%IMP%       VARIABLE    __views_index
%IMP%       VARIABLE    __number_view_3
%IMP%       VARIABLE    __number_view_4
**********************************************************************
*/
RECORD      __blk_char
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
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** For all the value and status types there is a set naming convention.
** If the variable is a readable, writeable and dynamic then just
** the name alone will be used, i.e. __status_input. If the variable
** is read-only it will have _r appended and if it is not dynamic
** it will have _nd appended.
**********************************************************************
*/
/*
**********************************************************************
** Value & Status Floating Point Data Structure (DS-65)
** The following variables make up a value & status record (DS-65) as
** defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__status_input_nd
%SYM%   member      STATUS              record              0xC001000F
%SYM%   member      SIMULATE_STATUS     record              0xC0010010
%SYM%   member      FIELD_STATUS        record              0xC0010011
%TXT%   variable    __status_input_nd   enumerated          0x800201AA
%IMP%   VARIABLE    __status_input_nd
**********************************************************************
*/
VARIABLE    __status_input_nd
{
    LABEL           [status_label] ;
    HELP            [status_input_help] ;
    CLASS           INPUT ;
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
__status_input
%SYM%   member      STATUS              record              0xC001000F
%SYM%   member      SIMULATE_STATUS     record              0xC0010010
%SYM%   member      FIELD_STATUS        record              0xC0010011
%TXT%   variable    __status_input      enumerated          0x8002000F
%IMP%   VARIABLE    __status_input
**********************************************************************
*/
VARIABLE    __status_input
{
    LABEL           [status_label] ;
    HELP            [status_input_help] ;
    CLASS           INPUT & DYNAMIC ;
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
__status_output
%SYM%   member      STATUS              record              0xC001000F
%TXT%   variable    __status_output     enumerated          0x80020010
%IMP%   VARIABLE    __status_output
**********************************************************************
*/
VARIABLE    __status_output
{
    LABEL           [status_label] ;
    HELP            [status_output_help] ;
    CLASS           OUTPUT & DYNAMIC;
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
__status_output_r
%SYM%   member      STATUS              record              0xC001000F
%TXT%   variable    __status_output_r   enumerated          0x800201AC
%IMP%   VARIABLE    __status_output_r
**********************************************************************
*/
VARIABLE    __status_output_r
{
    LABEL           [status_label] ;
    HELP            [status_output_help] ;
    CLASS           OUTPUT & DYNAMIC;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_output_nd
%SYM%   member      STATUS              record              0xC001000F
%TXT%   variable    __status_output_nd  enumerated          0x800201A5
%IMP%   VARIABLE    __status_output_nd
**********************************************************************
*/
VARIABLE    __status_output_nd
{
    LABEL           [status_label] ;
    HELP            [status_output_help] ;
    CLASS           OUTPUT & OPERATE ;
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
__status_contained_r
%SYM%   member      STATUS                record           0xC001000F
%TXT%   variable    __status_contained_r  enumerated       0x80020011
%IMP%   VARIABLE    __status_contained_r
**********************************************************************
*/
VARIABLE    __status_contained_r
{
    LABEL           [status_label] ;
    HELP            [status_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_contained
%SYM%   member      STATUS                record           0xC001000F
%TXT%   variable    __status_contained    enumerated       0x800201A4
%IMP%   VARIABLE    __status_contained
**********************************************************************
*/
VARIABLE    __status_contained
{
    LABEL           [status_label] ;
    HELP            [status_contained_help] ;
    CLASS           CONTAINED & DYNAMIC;
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
__status_contained_nd
%SYM%   member      STATUS                record           0xC001000F
%TXT%   variable    __status_contained_nd enumerated       0x80020
%IMP%   VARIABLE    __status_contained_nd
**********************************************************************
*/
VARIABLE    __status_contained_nd
{
    LABEL           [status_label] ;
    HELP            [status_contained_help] ;
    CLASS           CONTAINED & OPERATE;
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
__float_input_nd
%SYM%   member      VALUE                   record              0xC0010012
%SYM%   member      SIMULATE_VALUE          record              0xC0010013
%SYM%   member      TRANSDUCER_VALUE        record              0xC0010014
%TXT%   variable    __float_input_nd        float               0x80020012
%IMP%   VARIABLE    __float_input_nd
**********************************************************************
*/
VARIABLE    __float_input_nd
{
    LABEL           [value_label] ;
    HELP            [float_input_help] ;
    CLASS           INPUT ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_input
%SYM%   member      VALUE                   record         0xC0010012
%SYM%   member      SIMULATE_VALUE          record         0xC0010013
%SYM%   member      TRANSDUCER_VALUE        record         0xC0010014
%TXT%   variable    __float_input           float          0x800201A9
%IMP%   VARIABLE    __float_input
**********************************************************************
*/
VARIABLE    __float_input
{
    LABEL           [value_label] ;
    HELP            [float_input_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_output_r
%SYM%   member      VALUE                    record       0xC0010012
%TXT%   variable    __float_output_r         float        0x80020013
%IMP%   VARIABLE    __float_output_r
**********************************************************************
*/
VARIABLE    __float_output_r
{
    LABEL           [value_label] ;
    HELP            [float_output_help] ;
    CLASS           OUTPUT & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_output_nd
%SYM%   member      VALUE                    record       0xC0010012
%TXT%   variable    __float_output_nd        float        0x80020
%IMP%   VARIABLE    __float_output_nd
**********************************************************************
*/
VARIABLE    __float_output_nd
{
    LABEL           [value_label] ;
    HELP            [float_output_help] ;
    CLASS           OUTPUT & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_bkcal_sel
%SYM%   member      VALUE                    record       0xC0010012
%TXT%   variable    __float_bkcal_sel        float        0x800201A6
%IMP%   VARIABLE    __float_bkcal_sel
**********************************************************************
*/
VARIABLE    __float_bkcal_sel
{
    LABEL           [value_label] ;
    HELP            [float_output_help] ;
    CLASS           OUTPUT & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_contained_nd
%SYM%   member      VALUE                  record        0xC0010012
%TXT%   variable    __float_contained_nd   float         0x80020014
%IMP%   VARIABLE    __float_contained_nd
**********************************************************************
*/
VARIABLE    __float_contained_nd
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_contained
%SYM%   member      VALUE                  record        0xC0010012
%TXT%   variable    __float_contained      float         0x800201AE
%IMP%   VARIABLE    __float_contained
**********************************************************************
*/
VARIABLE    __float_contained
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_c_r_pct
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __float_c_r_pct     float               0x800201A3
%IMP%   VARIABLE    __float_c_r_pct
**********************************************************************
*/
VARIABLE    __float_c_r_pct
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_contained_r
%SYM%   member      VALUE                   record       0xC0010012
%TXT%   variable    __float_contained_r     float        0x80020197
%IMP%   VARIABLE    __float_contained_r
**********************************************************************
*/
VARIABLE    __float_contained_r
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__field_val_r
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __field_val_r       float               0x8002019A
%IMP%   VARIABLE    __field_val_r
**********************************************************************
*/
VARIABLE    __field_val_r
{
    LABEL           [value_label] ;
    HELP            [float_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ ;
    CONSTANT_UNIT [percent] ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Value & Status Discrete Data Structure (DS-66)
** The following variables make up a value & status record (DS-66) as
** defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__discrete_input
%SYM%   member      VALUE                      record       0xC0010012
%SYM%   member      SIMULATE_VALUE             record       0xC0010013
%SYM%   member      TRANSDUCER_VALUE           record       0xC0010014
%TXT%   variable    __discrete_input           enumerated   0x80020015
%IMP%   VARIABLE    __discrete_input
**********************************************************************
*/
VARIABLE    __discrete_input
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT & DYNAMIC ;
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
__on_off_input_nd
%SYM%   member      VALUE                      record       0xC0010012
%SYM%   member      SIMULATE_VALUE             record       0xC0010013
%SYM%   member      TRANSDUCER_VALUE           record       0xC0010014
%TXT%   variable    __on_off_input_nd          enumerated   0x800201B0
%IMP%   VARIABLE    __on_off_input_nd
**********************************************************************
*/
VARIABLE    __on_off_input_nd
{
    LABEL           [value_label] ;
    HELP            [on_off_input_help] ;
    CLASS           INPUT ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_OFF,
        _DISCRETE_VALUE_ON
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__discrete_input_nd
%SYM%   member      VALUE                      record       0xC0010012
%SYM%   member      SIMULATE_VALUE             record       0xC0010013
%SYM%   member      TRANSDUCER_VALUE           record       0xC0010014
%TXT%   variable    __discrete_input_nd        enumerated   0x800201A8
%IMP%   VARIABLE    __discrete_input_nd
**********************************************************************
*/
VARIABLE    __discrete_input_nd
{
    LABEL           [value_label] ;
    HELP            [discrete_input_help] ;
    CLASS           INPUT ;
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
__discrete_output_r
%SYM%   member      VALUE                    record           0xC0010012
%TXT%   variable    __discrete_output_r      enumerated       0x80020016
%IMP%   VARIABLE    __discrete_output_r
**********************************************************************
*/
VARIABLE    __discrete_output_r
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
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__discrete_output_nd
%SYM%   member      VALUE                    record         0xC0010012
%TXT%   variable    __discrete_output_nd     enumerated     0x800201AD
%IMP%   VARIABLE    __discrete_output_nd
**********************************************************************
*/
VARIABLE    __discrete_output_nd
{
    LABEL           [discrete_output_label] ;
    HELP            [discrete_output_help] ;
    CLASS           OUTPUT & OPERATE ;
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
__discrete_contained
%SYM%   member      VALUE                  record        0xC0010012
%TXT%   variable    __discrete_contained  enumerated     0x80020017
%IMP%   VARIABLE    __discrete_contained
**********************************************************************
*/
VARIABLE    __discrete_contained
{
    LABEL           [discrete_contained] ;
    HELP            [discrete_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
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
__discrete_contained_nd
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __discrete_contained_nd  enumerated     0x800201AB
%IMP%   VARIABLE    __discrete_contained_nd
**********************************************************************
*/
VARIABLE    __discrete_contained_nd
{
    LABEL           [discrete_contained] ;
    HELP            [discrete_contained_help] ;
    CLASS           CONTAINED & OPERATE;
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
__discrete_contained_r
%SYM%   member      VALUE                   record         0xC0010012
%TXT%   variable    __discrete_contained_r  enumerated     0x80020198
%IMP%   VARIABLE    __discrete_contained_r
**********************************************************************
*/
VARIABLE    __discrete_contained_r
{
    LABEL           [discrete_contained] ;
    HELP            [discrete_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
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
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__on_off_contained_r
**********************************************************************
*/
VARIABLE    __on_off_contained_r
{
    LABEL           [value_label] ;
    HELP            [discrete_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_OFF,
        _DISCRETE_VALUE_ON
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__on_off_output_nd
**********************************************************************
*/
VARIABLE    __on_off_output_nd
{
    LABEL           [value_label] ;
    HELP            [discrete_output_help] ;
    CLASS           OUTPUT & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        _DISCRETE_VALUE_OFF,
        _DISCRETE_VALUE_ON
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
** Value & Status Bitstring Data Structure (DS-67)
** The following variables make up a value & status record (DS-67) as
** defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__bitstring_input
%SYM%   member      VALUE               record              0xC0010012
%SYM%   member      SIMULATE_VALUE      record              0xC0010013
%SYM%   member      TRANSDUCER_VALUE    record              0xC0010014
%TXT%   variable    __bitstring_input   bit-string          0x80020018
%IMP%   VARIABLE    __bitstring_input
**********************************************************************
*/
VARIABLE    __bitstring_input
{
    LABEL           [bitstring_input] ;
    HELP            [bitstring_input_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            BITSTRING (8) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bitstring_output
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __bitstring_output  bit-string          0x80020019
%IMP%   VARIABLE    __bitstring_output
**********************************************************************
*/
VARIABLE    __bitstring_output
{
    LABEL           [bitstring_output] ;
    HELP            [bitstring_output_help] ;
    CLASS           OUTPUT & DYNAMIC ;
    TYPE            BITSTRING (8) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bitstring_contained_rw
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __bitstring_contained_rw bit-string     0x8002001A
%IMP%   VARIABLE    __bitstring_contained_rw
**********************************************************************
*/
VARIABLE    __bitstring_contained_rw
{
    LABEL           [bitstring_contained] ;
    HELP            [bitstring_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bitstring_contained_r
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __bitstring_contained_r  bit-string     0x80020199
%IMP%   VARIABLE    __bitstring_contained_r
**********************************************************************
*/
VARIABLE    __bitstring_contained_r
{
    LABEL           [bitstring_contained] ;
    HELP            [bitstring_contained_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (8) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Scaling Data Structure (DS-68)
** The following variables make up a scaling record (DS-68) as
** defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__eu_0
%SYM%   member      EU_0                record              0xC001001C
%TXT%   variable    __eu_0              float               0x8002001C
%IMP%   VARIABLE    __eu_0
**********************************************************************
*/
VARIABLE    __eu_0
{
    LABEL           [eu_0] ;
    HELP            [eu_0_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__eu_100
%SYM%   member      EU_100                record              0xC001001C
%TXT%   variable    __eu_100              float               0x8002001B
%IMP%   VARIABLE    __eu_100
**********************************************************************
*/
VARIABLE    __eu_100
{
    LABEL           [eu_100] ;
    HELP            [eu_100_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__units_index
%SYM%   member      UNITS_INDEX         record              0xC001001D
%TXT%   variable    __units_index       enumerated          0x8002001D
%IMP%   VARIABLE    __units_index
**********************************************************************
*/
VARIABLE    __units_index
{
    LABEL           [units_index] ;
    HELP            [units_index_help] ;
    CLASS           CONTAINED ;
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
__decimal,
%SYM%   member      DECIMAL             record              0xC001001E
%TXT%   variable    __decimal           integer             0x8002001E
%IMP%   VARIABLE    __decimal
**********************************************************************
*/
VARIABLE    __decimal
{
    LABEL           [decimal] ;
    HELP            [decimal_help] ;
    CLASS           CONTAINED ;
    TYPE            INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Mode Data Structure (DS-69)
** The following variables make up a mode record (DS-69) as
** defined by the Function Block specification FF-890-1.2,  4.4.3.5
**********************************************************************
*/
/*
**********************************************************************
__target_mode
%SYM%   member      TARGET              record              0xC001001F
%TXT%   variable    __target_mode       bit-enumerated      0x8002001F
%IMP%   VARIABLE    __target_mode
**********************************************************************
*/
VARIABLE    __target_mode
{
    LABEL           [target_mode] ;
    HELP            [target_mode_help] ;
    CLASS           CONTAINED & OPERATE;
    TYPE            BIT_ENUMERATED (1)
    {
        _MODE_REMOTE_OUTPUT,
        _MODE_REMOTE_CASCADE,
        _MODE_CASCADE,
        _MODE_AUTOMATIC,
        _MODE_MANUAL,
        /*_MODE_LOCKED, AR4487*/
        /*_MODE_INITIALIZATION, AR4487*/
        _MODE_OUT_OF_SERVICE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__actual_mode
%SYM%   member      ACTUAL              record              0xC0010020
%TXT%   variable    __actual_mode       bit-enumerated      0x80020020
%IMP%   VARIABLE    __actual_mode
**********************************************************************
*/
VARIABLE    __actual_mode
{
    LABEL           [actual_mode] ;
    HELP            [actual_mode_help] ;
    CLASS           CONTAINED & DYNAMIC & OPERATE ;
    TYPE            BIT_ENUMERATED (1)
    {
        _MODE_REMOTE_OUTPUT,
        _MODE_REMOTE_CASCADE,
        _MODE_CASCADE,
        _MODE_AUTOMATIC,
        _MODE_MANUAL,
        _MODE_LOCKED,
        _MODE_INITIALIZATION,
        _MODE_OUT_OF_SERVICE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__permitted_mode
%SYM%   member      PERMITTED           record              0xC00101A4
%TXT%   variable    __permitted_mode    bit-enumerated      0x80020195
%IMP%   VARIABLE    __permitted_mode
**********************************************************************
*/
VARIABLE    __permitted_mode
{
    LABEL           [permitted_mode] ;
    HELP            [permitted_mode_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            BIT_ENUMERATED (1)
    {
        _PERMITTED_REMOTE_OUTPUT,
        _PERMITTED_REMOTE_CASCADE,
        _PERMITTED_CASCADE,
        _PERMITTED_AUTOMATIC,
        _PERMITTED_MANUAL,
        _PERMITTED_LOCKED,
        _PERMITTED_INITIALIZATION,
        _PERMITTED_OUT_OF_SERVICE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__normal_mode
%SYM%   member      NORMAL              record              0xC0010021
%TXT%   variable    __normal_mode       bit-enumerated      0x80020021
%IMP%   VARIABLE    __normal_mode
**********************************************************************
*/
VARIABLE    __normal_mode
{
    LABEL           [normal_mode] ;
    HELP            [normal_mode_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            BIT_ENUMERATED (1)
    {
        _MODE_REMOTE_OUTPUT,
        _MODE_REMOTE_CASCADE,
        _MODE_CASCADE,
        _MODE_AUTOMATIC,
        _MODE_MANUAL,
        _MODE_LOCKED,
        _MODE_INITIALIZATION,
        _MODE_OUT_OF_SERVICE
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__mode
%TXT%   record      __mode                                  0x80020022
%IMP%   RECORD      mode
%IMP%       VARIABLE    __target_mode
%IMP%       VARIABLE    __actual_mode
%IMP%       VARIABLE    __permitted_mode
%IMP%       VARIABLE    __normal_mode
**********************************************************************
*/
RECORD      __mode
{
    LABEL           [mode] ;
    HELP            [mode_help] ;
    MEMBERS
    {
        TARGET,      __target_mode ;
        ACTUAL,      __actual_mode ;
        PERMITTED,   __permitted_mode ;
        NORMAL,      __normal_mode ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Access Permissions Data Structure (DS-70)
** The following variables make up an Access Permissions record (DS-70)
** as defined by the Function Block specification FF-890-1.2,  4.4.3.16
**********************************************************************
*/
/*
**********************************************************************
__grant
%SYM%   member      GRANT               record              0xC0010023
%TXT%   variable    __grant             bit-enumerated      0x80020023
%IMP%   VARIABLE    __grant
**********************************************************************
*/
VARIABLE    __grant
{
    LABEL           [grant] ;
    HELP            [grant_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (1)
    {
        { 0x01,  [grant_program],     [grant_program_help] },
        { 0x02,  [grant_tune],        [grant_tune_help] },
        { 0x04,  [grant_alarm],       [grant_alarm_help] },
        { 0x08,  [grant_local],       [grant_local_help] },
        { 0x10,  [grant_operate],     [grant_operate_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__deny
%SYM%   member      DENY                record              0xC0010024
%TXT%   variable    __deny              bit-enumerated      0x80020024
%IMP%   VARIABLE    __deny
**********************************************************************
*/
VARIABLE    __deny
{
    LABEL           [deny] ;
    HELP            [deny_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (1)
    {
        { 0x01,  [deny_program],     [deny_program_help] },
        { 0x02,  [deny_tune],        [deny_tune_help] },
        { 0x04,  [deny_alarm],       [deny_alarm_help] },
        { 0x08,  [deny_local],       [deny_local_help] },
        { 0x10,  [deny_operate],     [deny_operate_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__access
%TXT%   record      __access                                0x80020025
%IMP%   RECORD      __access
%IMP%       VARIABLE    __grant
%IMP%       VARIABLE    __deny
**********************************************************************
*/
RECORD      __access
{
    LABEL           [access] ;
    HELP            [access_help] ;
    MEMBERS
    {
        GRANT,   __grant ;
        DENY,    __deny ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Alarm float Data Structure (DS-71)
** The following variables make up an Alarm float record (DS-71)
** as defined by the Function Block specification FF-890-1.2,  4.4.3.13
**********************************************************************
*/
/*
**********************************************************************
__unacknowledged
%SYM%   member      UNACKNOWLEDGED      record              0xC0010026
%TXT%   variable    __unacknowledged    enumerated          0x80020026
%IMP%   VARIABLE    __unacknowledged
**********************************************************************
*/
VARIABLE    __unacknowledged
{
    LABEL           [unacknowledged] ;
    HELP            [unacknowledged_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        _ALARM_EVENT_ACKED,
        _ALARM_EVENT_UNACKED
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacknowledged_evt
%SYM%   member      UNACKNOWLEDGED        record              0xC0010026
%TXT%   variable    __unacknowledged_evt  enumerated          0x80
%IMP%   VARIABLE    __unacknowledged_evt
**********************************************************************
*/
VARIABLE    __unacknowledged_evt
{
    LABEL           [unacknowledged] ;
    HELP            [unacknowledged_evt_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        _ALARM_EVENT_ACKED,
        _ALARM_EVENT_UNACKED
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_state       FF-890-1.2,  4.4.3.14
%SYM%   member      ALARM_STATE         record              0xC0010027
%TXT%   variable    __alarm_state       enumerated          0x80020027
%IMP%   VARIABLE    __alarm_state
**********************************************************************
*/
VARIABLE    __alarm_state
{
    LABEL           [alarm_state] ;
    HELP            [alarm_state_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        _ALARM_STATE_1,
        _ALARM_STATE_2,
        _ALARM_STATE_3,
        _ALARM_STATE_4
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__time_stamp
%SYM%   member      TIME_STAMP          record              0xC0010028
%TXT%   variable    __time_stamp        time_value          0x80020028
%IMP%   VARIABLE    __time_stamp
**********************************************************************
*/
VARIABLE    __time_stamp
{
    LABEL           [time_stamp] ;
    HELP            [time_stamp_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            TIME_VALUE;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sub_code              FF-890-1.2,  4.4.3.12
%SYM%   member      SUB_CODE            record              0xC0010029
%TXT%   variable    __sub_code          enumerated          0x80020029
%IMP%   VARIABLE    __sub_code
**********************************************************************
*/
VARIABLE    __sub_code
{
    LABEL           [sub_code] ;
    HELP            [sub_code_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            ENUMERATED (2)
    {
        { 0x0000,  [subcode_other],           [subcode_other_help] },
        { 0x0001,  [subcode_block_config],    [subcode_block_config_help] },
        { 0x0002,  [subcode_link_config],     [subcode_link_config_help] },
        { 0x0003,  [subcode_simulation],      [subcode_simulation_help] },
        { 0x0004,  [subcode_override],        [subcode_override_help] },
        { 0x0005,  [subcode_fault_state],     [subcode_fault_state_help] },
        { 0x0006,  [subcode_maint_soon],      [subcode_maint_soon_help] },
        { 0x0007,  [subcode_input_fail],      [subcode_input_fail_help] },
        { 0x0008,  [subcode_output_fail],     [subcode_output_fail_help] },
        { 0x0009,  [subcode_mem_fail],        [subcode_mem_fail_help] },
        { 0x000A,  [subcode_lost_static],     [subcode_lost_static_help] },
        { 0x000B,  [subcode_lost_nv],         [subcode_lost_nv_help] },
        { 0x000C,  [subcode_readback_fail],   [subcode_readback_fail_help] },
        { 0x000D,  [subcode_maint_now],       [subcode_maint_now_help] },
        { 0x000E,  [subcode_power_up],        [subcode_power_up_help] },
        { 0x000F,  [subcode_out_of_service],  [subcode_out_of_service_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__float_value
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __float_value       float               0x8002002A
%IMP%   VARIABLE    __float_value
**********************************************************************
*/
VARIABLE    __float_value
{
    LABEL           [float_value] ;
    HELP            [float_value_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_float
%TXT%   record      __alarm_float                           0x8002002B
%IMP%   RECORD      __alarm_float
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __alarm_float
{
    LABEL           [alarm_float] ;
    HELP            [alarm_float_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Alarm discrete Data Structure (DS-72)
** The following variables make up an Alarm discrete record (DS-72)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__discrete_value
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __discrete_value    enumerated          0x8002002C
%IMP%   VARIABLE    __discrete_value
**********************************************************************
*/
VARIABLE    __discrete_value
{
    LABEL           [discrete_value] ;
    HELP            [discrete_value_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM;
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
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_discrete
%TXT%   record      __alarm_discrete                        0x8002002D
%IMP%   RECORD      __alarm_discrete
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __alarm_discrete
{
    LABEL           [alarm_discrete] ;
    HELP            [alarm_discrete_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __discrete_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Event update Data Structure (DS-73)
** The following variables make up an Event update record (DS-73)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__update_state
%SYM%   member      UPDATE_STATE        record              0xC00101A5
%TXT%   variable    __update_state      enumerated          0x80020196
%IMP%   VARIABLE    __update_state
**********************************************************************
*/
VARIABLE    __update_state
{
    LABEL           [update_state] ;
    HELP            [update_state_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [update_reported],       [update_reported_help] },
        { 0x02,  [update_not_reported],   [update_not_reported_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__static_revision
%SYM%   member      STATIC_REVISION     record              0xC001002E
%TXT%   variable    __static_revision   unsigned            0x8002002E
%IMP%   VARIABLE    __static_revision
**********************************************************************
*/
VARIABLE    __static_revision
{
    LABEL           [static_revision] ;
    HELP            [static_revision_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (2);
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__relative_index
%SYM%   member      RELATIVE_INDEX      record              0xC001002F
%TXT%   variable    __relative_index    unsigned            0x8002002F
%IMP%   VARIABLE    __relative_index
**********************************************************************
*/
VARIABLE    __relative_index
{
    LABEL           [relative_index] ;
    HELP            [relative_index_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (2);
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Alarm summary Data Structure (DS-74)
** The following variables make up an Alarm summary record (DS-74)
** as defined by the Function Block specification  FF-890-1.2,  4.4.3.11
** Also see comtbls.h
**********************************************************************
*/
/*
**********************************************************************
__current_summary
%SYM%   member      CURRENT             record              0xC0010031
%TXT%   variable    __current_summary   bit-enumerated      0x80020031
%IMP%   VARIABLE    __current_summary
**********************************************************************
*/
VARIABLE    __current_summary
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_0,
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7,
        _CURR_SUMM_8,
        _CURR_SUMM_9,
        _CURR_SUMM_10,
        _CURR_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary
%SYM%   member      UNACKNOWLEDGED      record              0xC0010026
%TXT%   variable    __unacked_summary   bit-enumerated      0x80020032
%IMP%   VARIABLE    __unacked_summary
**********************************************************************
*/
VARIABLE    __unacked_summary
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_0,
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10,
        _UNACK_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary
%SYM%   member      UNREPORTED          record              0xC0010033
%TXT%   variable    __unreported_summary  bit-enumerated    0x80020033
%IMP%   VARIABLE    __unreported_summary
**********************************************************************
*/
VARIABLE    __unreported_summary
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_0,
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10,
        _UNREP_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary
%SYM%   member      DISABLED            record              0xC00101A6
%TXT%   variable    __disabled_summary  bit-enumerated      0x80020034
%IMP%   VARIABLE    __disabled_summary
**********************************************************************
*/
VARIABLE    __disabled_summary
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_0,
        _DISAB_SUMM_1,
        _DISAB_SUMM_2,
        _DISAB_SUMM_3,
        _DISAB_SUMM_4,
        _DISAB_SUMM_5,
        _DISAB_SUMM_6,
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10,
        _DISAB_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_sum
%TXT%   record      __alarm_sum                             0x80020035
%SYM%   member      ALARM_SUM           parameter           0xC0010094
%SYM%   member      VL_ALARM_SUM        variable-list       0xC0010095
%IMP%   RECORD      __alarm_sum
%IMP%       VARIABLE    __current_summary
%IMP%       VARIABLE    __unacked_summary
%IMP%       VARIABLE    __unreported_summary
%IMP%       VARIABLE    __disabled_summary
**********************************************************************
*/
RECORD      __alarm_sum
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary ;
        UNACKNOWLEDGED,      __unacked_summary ;
        UNREPORTED,          __unreported_summary ;
        DISABLED,            __disabled_summary ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Simulate - float Data Structure (DS-82)
** The following variables make up a Simulate - float record (DS-82)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__enable_disable
%SYM%   member      ENABLE_DISABLE      record              0xC0010076
%TXT%   variable    __enable_disable    enumerated          0x80020076
%IMP%   VARIABLE    __enable_disable
**********************************************************************
*/
VARIABLE    __enable_disable
{
    LABEL           [enable_disable_label] ;
    HELP            [enable_disable_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [simulate_disabled],   [simulate_disabled_help] },
        { 0x02,    [simulate_active],     [simulate_active_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__simulate_status
%SYM%   member      STATUS              record              0xC001000F
%TXT%   variable    __simulate_status   enumerated          0x8002019A
%IMP%   VARIABLE    __simulate_status
**********************************************************************
*/
VARIABLE    __simulate_status
{
    LABEL           [simulate_status_label] ;
    HELP            [simulate_status_help] ;
    CLASS           CONTAINED & DYNAMIC ;
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
__simulate_value
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __simulate_value    float               0x8002019B
%IMP%   VARIABLE    __simulate_value
**********************************************************************
*/
VARIABLE    __simulate_value
{
    LABEL           [simulate_value_label] ;
    HELP            [simulate_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__simulate_d_value
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __simulate_d_value  enumerated          0x8002019F
%IMP%   VARIABLE    __simulate_d_value
**********************************************************************
*/
VARIABLE    __simulate_d_value
{
    LABEL           [simulate_d_value_label] ;
    HELP            [simulate_d_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
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
__transducer_d_value
%SYM%   member      VALUE                 record              0xC0010012
%TXT%   variable    __transducer_d_value  enumerated          0x800201A0
%IMP%   VARIABLE    __transducer_d_value
**********************************************************************
*/
VARIABLE    __transducer_d_value
{
    LABEL           [transducer_d_value_label] ;
    HELP            [transducer_d_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
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
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__transducer_status
%SYM%   member      STATUS              record              0xC001000F
%TXT%   variable    __transducer_status enumerated          0x8002019C
%IMP%   VARIABLE    __transducer_status
**********************************************************************
*/
VARIABLE    __transducer_status
{
    LABEL           [transducer_status_label] ;
    HELP            [transducer_status_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        __FF_STATUS_VALUES
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__transducer_value
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __transducer_value  float               0x8002019D
%IMP%   VARIABLE    __transducer_value
**********************************************************************
*/
VARIABLE    __transducer_value
{
    LABEL           [transducer_value_label] ;
    HELP            [transducer_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    HANDLING        READ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__simulate_float
%TXT%   record      __simulate_float                        0x80020077
%IMP%   RECORD      __simulate_float
%IMP%       VARIABLE    __simulate_status
%IMP%       VARIABLE    __simulate_value
%IMP%       VARIABLE    __transucer_status
%IMP%       VARIABLE    __transducer_value
**********************************************************************
*/
RECORD      __simulate_float
{
    LABEL           [simulate_label] ;
    HELP            [simulate_float_help] ;
    MEMBERS
    {
        SIMULATE_STATUS,     __simulate_status ;
        SIMULATE_VALUE,      __simulate_value ;
        TRANSDUCER_STATUS,   __transducer_status ;
        TRANSDUCER_VALUE,    __transducer_value ;
        ENABLE_DISABLE,      __enable_disable ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Simulate - discrete Data Structure (DS-83)
** The following variables make up a Simulate - discrete record (DS-83)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__simulate_discrete
%TXT%   record      __simulate_discrete                     0x80020078
%IMP%   RECORD      __simulate_discrete
%IMP%       VARIABLE    __simulate_status
%IMP%       VARIABLE    __simulate_d_value
%IMP%       VARIABLE    __transducer_status
%IMP%       VARIABLE    __transducer_d_value
%IMP%       VARIABLE    __enable_disable
**********************************************************************
*/
RECORD      __simulate_discrete
{
    LABEL           [simulate_D_label] ;
    HELP            [simulate_discrete_help] ;
    MEMBERS
    {
        SIMULATE_STATUS,     __simulate_status ;
        SIMULATE_VALUE,      __simulate_d_value ;
        TRANSDUCER_STATUS,   __transducer_status ;
        TRANSDUCER_VALUE,    __transducer_d_value ;
        ENABLE_DISABLE,      __enable_disable ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Simulate - bitstring Data Structure (DS-84)
** The following variables make up a Simulate - bitstring record (DS-84)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__simulate_bitstring
%TXT%   record      __simulate_bitstring                    0x80020079
%IMP%   RECORD      __simulate_bitstring
%IMP%       VARIABLE    __simulate_status
%IMP%       VARIABLE    __bitstring_contained_r
%IMP%       VARIABLE    __bitstring_contained_rw
%IMP%       VARIABLE    __enable_disable
**********************************************************************
*/
RECORD      __simulate_bitstring
{
    LABEL           [simulate_bitstring] ;
    HELP            [simulate_bitstring_help] ;
    MEMBERS
    {
        SIMULATE_STATUS,     __simulate_status ;
        SIMULATE_VALUE,      __bitstring_contained_rw ;
        TRANSDUCER_STATUS,   __transducer_status ;
        TRANSDUCER_VALUE,    __bitstring_contained_r ;
        ENABLE_DISABLE,      __enable_disable ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Test read / write Data Structure (DS-85)
** The following variables make up a test read / write record (DS-85)
** as defined by the Function Block specification
**********************************************************************
*/
/*
**********************************************************************
__test_boolean
%SYM%   member      VALUE_1             record              0xC001007A
%TXT%   variable    __test_boolean      boolean             0x8002007A
%IMP%   VARIABLE    __test_boolean
**********************************************************************
*/
VARIABLE    __test_boolean
{
    LABEL           [test_boolean] ;
    HELP            [test_boolean_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BOOLEAN ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_integer8
%SYM%   member      VALUE_2             record              0xC001007B
%TXT%   variable    __test_integer8     integer             0x8002007B
%IMP%   VARIABLE    __test_integer8
**********************************************************************
*/
VARIABLE    __test_integer8
{
    LABEL           [test_integer8] ;
    HELP            [test_integer8_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_integer16
%SYM%   member      VALUE_3             record              0xC001007C
%TXT%   variable    __test_integer16    integer             0x8002007C
%IMP%   VARIABLE    __test_integer16
**********************************************************************
*/
VARIABLE    __test_integer16
{
    LABEL           [test_integer16] ;
    HELP            [test_integer16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_integer32
%SYM%   member      VALUE_4             record              0xC001007D
%TXT%   variable    __test_integer32    integer             0x8002007D
%IMP%   VARIABLE    __test_integer32
**********************************************************************
*/
VARIABLE    __test_integer32
{
    LABEL           [test_integer32] ;
    HELP            [test_integer32_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_unsigned8
%SYM%   member      VALUE_5             record              0xC001007E
%TXT%   variable    __test_unsigned8    unsigned            0x8002007E
%IMP%   VARIABLE    __test_unsigned8
**********************************************************************
*/
VARIABLE    __test_unsigned8
{
    LABEL           [test_unsigned8] ;
    HELP            [test_unsigned8_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_unsigned16
%SYM%   member      VALUE_6             record              0xC001007F
%TXT%   variable    __test_unsigned16   unsigned            0x8002007F
%IMP%   VARIABLE    __test_unsigned16
**********************************************************************
*/
VARIABLE    __test_unsigned16
{
    LABEL           [test_unsigned16] ;
    HELP            [test_unsigned16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_unsigned32
%SYM%   member      VALUE_7             record              0xC0010080
%TXT%   variable    __test_unsigned32   unsigned            0x80020080
%IMP%   VARIABLE    __test_unsigned32
**********************************************************************
*/
VARIABLE    __test_unsigned32
{
    LABEL           [test_unsigned32] ;
    HELP            [test_unsigned32_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_float
%SYM%   member      VALUE_8             record              0xC0010081
%TXT%   variable    __test_float        float               0x80020081
%IMP%   VARIABLE    __test_float
**********************************************************************
*/
VARIABLE    __test_float
{
    LABEL           [test_float] ;
    HELP            [test_float_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_visible_string
%SYM%   member      VALUE_9             record              0xC0010082
%TXT%   variable    __test_visible_string   visible         0x80020082
%IMP%   VARIABLE    __test_visible_string
**********************************************************************
*/
VARIABLE    __test_visible_string
{
    LABEL           [test_visible_string] ;
    HELP            [test_visible_string_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_octet_string
%SYM%   member      VALUE_10            record              0xC0010083
%TXT%   variable    __test_octet_string octet               0x80020083
%IMP%   VARIABLE    __test_octet_string
**********************************************************************
*/
VARIABLE    __test_octet_string
{
    LABEL           [test_octet_string] ;
    HELP            [test_octet_string_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            OCTET (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_date
%SYM%   member      VALUE_11            record              0xC0010084
%TXT%   variable    __test_date         date/time           0x80020084
%IMP%   VARIABLE    __test_date
**********************************************************************
*/
VARIABLE    __test_date
{
    LABEL           [test_date] ;
    HELP            [test_date_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            DATE_AND_TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_time
%SYM%   member      VALUE_12            record              0xC0010085
%TXT%   variable    __test_time         time                0x80020085
%IMP%   VARIABLE    __test_time
**********************************************************************
*/
VARIABLE    __test_time
{
    LABEL           [test_time] ;
    HELP            [test_time_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            TIME ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_time_diff
%SYM%   member      VALUE_13            record              0xC0010086
%TXT%   variable    __test_time_diff    duration            0x80020086
%IMP%   VARIABLE    __test_time_diff
**********************************************************************
*/
VARIABLE    __test_time_diff
{
    LABEL           [test_time_diff] ;
    HELP            [test_time_diff_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            DURATION ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_bitstring
%SYM%   member      VALUE_14            record              0xC0010087
%TXT%   variable    __test_bitstring    bit-string          0x80020087
%IMP%   VARIABLE    __test_bitstring
**********************************************************************
*/
VARIABLE    __test_bitstring
{
    LABEL           [test_bitstring] ;
    HELP            [test_bitstring_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_dll_time
%SYM%   member      VALUE_15            record              0xC0010088
%TXT%   variable    __test_dll_time     time_value          0x80020088
%IMP%   VARIABLE    __test_dll_time
**********************************************************************
*/
VARIABLE    __test_dll_time
{
    LABEL           [test_dll_time] ;
    HELP            [test_dll_time_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            TIME_VALUE ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_read_write
%TXT%   record      __test_read_write                       0x80020089
%SYM%   member      TEST_RW             parameter           0xC0010089
%IMP%   RECORD      __test_read_write
%IMP%       VARIABLE    __test_boolean
%IMP%       VARIABLE    __test_integer8
%IMP%       VARIABLE    __test_integer16
%IMP%       VARIABLE    __test_integer32
%IMP%       VARIABLE    __test_unsigned8
%IMP%       VARIABLE    __test_unsigned16
%IMP%       VARIABLE    __test_unsigned32
%IMP%       VARIABLE    __test_float
%IMP%       VARIABLE    __test_visible_string
%IMP%       VARIABLE    __test_octet_string
%IMP%       VARIABLE    __test_date
%IMP%       VARIABLE    __test_time
%IMP%       VARIABLE    __test_time_diff
%IMP%       VARIABLE    __test_bitstring
%IMP%       VARIABLE    __test_dll_time
**********************************************************************
*/
RECORD      __test_read_write
{
    LABEL           [test_read_write_label] ;
    HELP            [test_read_write_help] ;
    MEMBERS
    {
        VALUE_1,     __test_boolean ;
        VALUE_2,     __test_integer8 ;
        VALUE_3,     __test_integer16 ;
        VALUE_4,     __test_integer32 ;
        VALUE_5,     __test_unsigned8 ;
        VALUE_6,     __test_unsigned16 ;
        VALUE_7,     __test_unsigned32 ;
        VALUE_8,     __test_float ;
        VALUE_9,     __test_visible_string ;
        VALUE_10,    __test_octet_string ;
        VALUE_11,    __test_date ;
        VALUE_12,    __test_time ;
        VALUE_13,    __test_time_diff ;
        VALUE_14,    __test_bitstring ;
        VALUE_15,    __test_dll_time ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
** Standard function block variable / parameter definitions
**********************************************************************
*/
/*
**********************************************************************
__ack_option
%SYM%   member      ACK_OPTION          parameter           0xC0010090
%SYM%   member      VL_ACK_OPTION       variable-list       0xC0010091
%TXT%   variable    __ack_option        bit-enumerated      0x80020090
%IMP%   VARIABLE    __ack_option
**********************************************************************
*/
VARIABLE    __ack_option
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_0,
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_hys
%SYM%   member      ALARM_HYS           parameter           0xC0010092
%SYM%   member      VL_ALARM_HYS        variable-list       0xC0010093
%TXT%   variable    __alarm_hys         float               0x80020092
%IMP%   VARIABLE    __alarm_hys
**********************************************************************
*/
VARIABLE    __alarm_hys
{
    LABEL           [alarm_hys_label] ;
    HELP            [alarm_hys_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
        MAX_VALUE   50.0 ;
    }
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alarm_sum       (DS-74)
%SYM%   member      ALARM_SUM           parameter           0xC0010094
%SYM%   member      VL_ALARM_SUM        variable-list       0xC0010095
%TXT%   record      __alarm_sum                             0x80020035
%IMP%   RECORD      __alarm_sum
%IMP%       VARIABLE    __current_summary
%IMP%       VARIABLE    __unacked_summary
%IMP%       VARIABLE    __unreported_summary
%IMP%       VARIABLE    __disabled_summary
**********************************************************************
*/
/*
**********************************************************************
__alert_key
%SYM%   member      KEY                 record              0xC0010037
%SYM%   member      ALERT_KEY           parameter           0xC0010096
%SYM%   member      VL_ALERT_KEY        variable-list       0xC0010097
%TXT%   variable    __alert_key         unsigned            0x80020037
%IMP%   VARIABLE    __alert_key
**********************************************************************
*/
VARIABLE    __alert_key
{
    LABEL           [alert_key_label] ;
    HELP            [alert_key_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MIN_VALUE       1;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bal_time
%SYM%   member      BAL_TIME            parameter           0xC0010098
%SYM%   member      VL_BAL_TIME         variable-list       0xC0010099
%TXT%   variable    __bal_time          float               0x80020098
%IMP%   VARIABLE    __bal_time
**********************************************************************
*/
VARIABLE    __bal_time
{
    LABEL           [bal_time_label] ;
    HELP            [bal_time_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bias
%SYM%   member      BIAS                parameter           0xC001009A
%SYM%   member      VL_BIAS             variable-list       0xC001009B
%TXT%   variable    __bias              float               0x8002009A
%IMP%   VARIABLE    __bias
**********************************************************************
*/
VARIABLE    __bias
{
    LABEL           [bias_label] ;
    HELP            [bias_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_hys
%SYM%   member      BKCAL_HYS           parameter           0xC001009C
%SYM%   member      VL_BKCAL_HYS        variable-list       0xC001009D
%TXT%   variable    __bkcal_hys         float               0x8002009C
%IMP%   VARIABLE    __bkcal_hys
**********************************************************************
*/
VARIABLE    __bkcal_hys
{
    LABEL           [bkcal_hys_label] ;
    HELP            [bkcal_hys_help] ;
    CLASS           CONTAINED & TUNE;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
        MAX_VALUE   50.0 ;
    }
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_in        (DS-65)
%SYM%   member      BKCAL_IN            parameter           0xC001009E
%SYM%   member      VL_BKCAL_IN         variable-list       0xC001009F
%TXT%   record      __bkcal_in                              0x8002009E
%IMP%   RECORD      __bkcal_in
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __bkcal_in
{
    LABEL           [bkcal_in_label] ;
    HELP            [bkcal_in_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_out       (DS-65)
%SYM%   member      BKCAL_OUT           parameter           0xC00100A0
%SYM%   member      VL_BKCAL_OUT        variable-list       0xC00100A1
%TXT%   record      __bkcal_out                             0x800200A0
%IMP%   RECORD      __bkcal_out
%IMP%       VARIABLE    __status_output_r
%IMP%       VARIABLE    __float_output_r
**********************************************************************
*/
RECORD      __bkcal_out
{
    LABEL           [bkcal_out_label] ;
    HELP            [bkcal_out_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __float_output_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_out_d     (DS-66)
%SYM%   member      BKCAL_OUT_D         parameter           0xC00100A2
%SYM%   member      VL_BKCAL_OUT_D      variable-list       0xC00100A3
%TXT%   record      __bkcal_out_d                           0x800200A2
%IMP%   RECORD      __bkcal_out_d
%IMP%       VARIABLE    __status_output_r
%IMP%       VARIABLE    __discrete_output_r_nd
**********************************************************************
*/
RECORD      __bkcal_out_d
{
    LABEL           [bkcal_out_d_label] ;
    HELP            [bkcal_out_d_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_sel_1     (DS-65)
%SYM%   member      BKCAL_SEL_1         parameter           0xC00100A4
%SYM%   member      VL_BKCAL_SEL_1      variable-list       0xC00100A5
%TXT%   record      __bkcal_sel_1                           0x800200A4
%IMP%   RECORD      __bkcal_sel_1
%IMP%       VARIABLE    __status_output
%IMP%       VARIABLE    __float_bkcal_sel
**********************************************************************
*/
RECORD      __bkcal_sel_1
{
    LABEL           [bkcal_sel_1_label] ;
    HELP            [bkcal_sel_1_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __float_bkcal_sel ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_sel_2     (DS-65)
%SYM%   member      BKCAL_SEL_2         parameter           0xC00100A6
%SYM%   member      VL_BKCAL_SEL_2      variable-list       0xC00100A7
%TXT%   record      __bkcal_sel_2                           0x800200A6
%IMP%   RECORD      __bkcal_sel_2
%IMP%       VARIABLE    __status_output
%IMP%       VARIABLE    __float_bkcal_sel
**********************************************************************
*/
RECORD      __bkcal_sel_2
{
    LABEL           [bkcal_sel_2_label] ;
    HELP            [bkcal_sel_2_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __float_bkcal_sel ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bkcal_sel_3     (DS-65)
%SYM%   member      BKCAL_SEL_3         parameter           0xC00100A8
%SYM%   member      VL_BKCAL_SEL_3      variable-list       0xC00100A9
%TXT%   record      __bkcal_sel_3                           0x800200A8
%IMP%   RECORD      __bkcal_sel_3
%IMP%       VARIABLE    __status_output
%IMP%       VARIABLE    __float_bkcal_sel
**********************************************************************
*/
RECORD      __bkcal_sel_3
{
    LABEL           [bkcal_sel_3_label] ;
    HELP            [bkcal_sel_3_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __float_bkcal_sel ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__alm_value
%SYM%   member      VALUE                record              0xC0010012
%TXT%   variable    __alm_value         enumerated          0x800201A2
%IMP%   VARIABLE    __alm_value
**********************************************************************
*/
VARIABLE    __alm_value
{
    LABEL           [value_label] ;
    HELP            [alm_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (1) ;
/*    CONSTANT_UNIT   [blank] ; */
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__block_alm       (DS-72)
%SYM%   member      BLOCK_ALM           parameter           0xC00100AA
%SYM%   member      VL_BLOCK_ALM        variable-list       0xC00100AB
%TXT%   record      __block_alm                             0x800200AA
%IMP%   RECORD      __block_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __alm_value
**********************************************************************
*/
RECORD      __block_alm
{
    LABEL           [block_alm_label] ;
    HELP            [block_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __alm_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__block_err             FF-890-1.2,  4.4.3.6
%SYM%   member      BLOCK_ERR           parameter           0xC00100AC
%SYM%   member      VL_BLOCK_ERR        variable-list       0xC00100AD
%TXT%   variable    __block_err         bit-enumerated      0x800200AC
%IMP%   VARIABLE    __block_err
**********************************************************************
*/
VARIABLE    __block_err
{
    LABEL           [block_err_label] ;
    HELP            [block_err_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,  [subcode_other],           [subcode_other_help] },
        { 0x0002,  [subcode_block_config],    [subcode_block_config_help] },
        { 0x0004,  [subcode_link_config],     [subcode_link_config_help] },
        { 0x0008,  [subcode_simulation],      [subcode_simulation_help] },
        { 0x0010,  [subcode_override],        [subcode_override_help] },
        { 0x0020,  [subcode_fault_state],     [subcode_fault_state_help] },
        { 0x0040,  [subcode_maint_soon],      [subcode_maint_soon_help] },
        { 0x0080,  [subcode_input_fail],      [subcode_input_fail_help] },
        { 0x0100,  [subcode_output_fail],     [subcode_output_fail_help] },
        { 0x0200,  [subcode_mem_fail],        [subcode_mem_fail_help] },
        { 0x0400,  [subcode_lost_static],     [subcode_lost_static_help] },
        { 0x0800,  [subcode_lost_nv],         [subcode_lost_nv_help] },
        { 0x1000,  [subcode_readback_fail],   [subcode_readback_fail_help] },
        { 0x2000,  [subcode_maint_now],       [subcode_maint_now_help] },
        { 0x4000,  [subcode_power_up],        [subcode_power_up_help] },
        { 0x8000,  [subcode_out_of_service],  [subcode_out_of_service_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__bypass
%SYM%   member      BYPASS              parameter           0xC00100AE
%SYM%   member      VL_BYPASS           variable-list       0xC00100AF
%TXT%   variable    __bypass            enumerated          0x800200AE
%IMP%   VARIABLE    __bypass
**********************************************************************
*/
VARIABLE    __bypass
{
    LABEL           [bypass_label] ;
    HELP            [bypass_help] ;
    CLASS           CONTAINED & OPERATE;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [off],    [bypass_off_help] },
        { 0x02,    [on],     [bypass_on_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__cas_in      (DS-65)
%SYM%   member      CAS_IN              parameter           0xC00100B0
%SYM%   member      VL_CAS_IN           variable-list       0xC00100B1
%TXT%   record      __cas_in                                0x800200B0
%IMP%   RECORD      __cas_in
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __float_input
**********************************************************************
*/
RECORD      __cas_in
{
    LABEL           [cas_in_label] ;
    HELP            [cas_in_help] ;
    MEMBERS
    {
        STATUS,  __status_input ;
        VALUE,   __float_input ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__cas_in_d    (DS-66)
%SYM%   member      CAS_IN_D            parameter           0xC00100B2
%SYM%   member      VL_CAS_IN_D         variable-list       0xC00100B3
%TXT%   record      __cas_in_d                              0x800200B2
%IMP%   RECORD      __cas_in_d
%IMP%       VARIABLE    __status_input
%IMP%       VARIABLE    __discrete_input
**********************************************************************
*/
RECORD      __cas_in_d
{
    LABEL           [cas_in_d_label] ;
    HELP            [cas_in_d_help] ;
    MEMBERS
    {
        STATUS,  __status_input ;
        VALUE,   __discrete_input ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__channel
%SYM%   member      CHANNEL             parameter           0xC00100B4
%SYM%   member      VL_CHANNEL          variable-list       0xC00100B5
%TXT%   variable    __channel           unsigned            0x800200B4
%IMP%   VARIABLE    __channel
**********************************************************************
*/
VARIABLE    __channel
{
    LABEL           [channel_label] ;
    HELP            [channel_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        _CHANNEL_0,
        _CHANNEL_1,
        _CHANNEL_2
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__clr_fstate
%SYM%   member      CLR_FSTATE           parameter           0xC00100B6
%SYM%   member      VL_CLR_FSTATE        variable-list       0xC00100B7
%TXT%   variable    __clr_fstate         enumerated          0x800200B6
%IMP%   VARIABLE    __clr_fstate
**********************************************************************
*/
VARIABLE    __clr_fstate
{
    LABEL           [clr_fstate_label] ;
    HELP            [clr_fstate_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [off],               [clear_faultstate_off_help] },
        { 0x02,  [clear_faultstate],    [clear_faultstate_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__confirm_time
%SYM%   member      CONFIRM_TIME        parameter           0xC00100B8
%SYM%   member      VL_CONFIRM_TIME     variable-list       0xC00100B9
%TXT%   variable    __confirm_time      unsigned            0x800200B8
%IMP%   VARIABLE    __confirm_time
**********************************************************************
*/
VARIABLE    __confirm_time
{
    LABEL           [confirm_time_label] ;
    HELP            [confirm_time_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__control_opts          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts      bit-enumerated      0x800200BA
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_CONTROL_OPTS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__cycle_sel          FF-891-1.2,  5.4.1
%SYM%   member      CYCLE_SEL           parameter           0xC00100BC
%SYM%   member      VL_CYCLE_SEL        variable-list       0xC00100BD
%TXT%   variable    __cycle_sel         bit-enumerated      0x800200BC
%IMP%   VARIABLE    __cycle_sel
**********************************************************************
*/
VARIABLE    __cycle_sel
{
    LABEL           [cycle_sel_label] ;
    HELP            [cycle_sel_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,  [block_scheduled],     [block_scheduled_help] },
        { 0x0002,  [block_completion],    [block_completion_help] },
        { 0x0004,  [block_manufacturer],  [block_manufacturer_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__cycle_type          FF-891-1.2,  5.4.1
%SYM%   member      CYCLE_TYPE          parameter           0xC00100BE
%SYM%   member      VL_CYCLE_TYPE       variable-list       0xC00100BF
%TXT%   variable    __cycle_type        bit-enumerated      0x800200BE
%IMP%   VARIABLE    __cycle_type
**********************************************************************
*/
VARIABLE    __cycle_type
{
    LABEL           [cycle_type_label] ;
    HELP            [cycle_type_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,  [block_scheduled],     [block_scheduled_help] },
        { 0x0002,  [block_completion],    [block_completion_help] },
        { 0x0004,  [block_manufacturer],  [block_manufacturer_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dd_resource
%SYM%   member      DD_RESOURCE         parameter           0xC00100C0
%SYM%   member      VL_DD_RESOURCE      variable-list       0xC00100C1
%TXT%   variable    __dd_resource       visible             0x800200C0
%IMP%   VARIABLE    __dd_resource
**********************************************************************
*/
VARIABLE    __dd_resource
{
    LABEL           [dd_resource_label] ;
    HELP            [dd_resource_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dd_rev
%SYM%   member      DD_REV              parameter           0xC00100C2
%SYM%   member      VL_DD_REV           variable-list       0xC00100C3
%TXT%   variable    __dd_rev            unsigned            0x800200C2
%IMP%   VARIABLE    __dd_rev
**********************************************************************
*/
VARIABLE    __dd_rev
{
    LABEL           [dd_rev_label] ;
    HELP            [dd_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dev_rev
%SYM%   member      DEV_REV             parameter           0xC00100C4
%SYM%   member      VL_DEV_REV          variable-list       0xC00100C5
%TXT%   variable    __dev_rev           unsigned            0x800200C4
%IMP%   VARIABLE    __dev_rev
**********************************************************************
*/
VARIABLE    __dev_rev
{
    LABEL           [dev_rev_label] ;
    HELP            [dev_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dev_type
%SYM%   member      DEV_TYPE            parameter           0xC00100C6
%SYM%   member      VL_DEV_TYPE         variable-list       0xC00100C7
%TXT%   variable    __dev_type          unsigned            0x800200C6
%IMP%   VARIABLE    __dev_type
**********************************************************************
*/
VARIABLE    __dev_type
{
    LABEL           [dev_type_label] ;
    HELP            [dev_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
    	{ 0,	[undefined],	[blank] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disc_alm        (DS-72)
%SYM%   member      DISC_ALM            parameter           0xC00100C8
%SYM%   member      VL_DISC_ALM         variable-list       0xC00100C9
%TXT%   record      __disc_alm                              0x800200C8
%IMP%   RECORD      __disc_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __disc_alm
{
    LABEL           [disc_alm_label] ;
    HELP            [disc_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __discrete_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disc_lim
%SYM%   member      DISC_LIM            parameter           0xC00100CA
%SYM%   member      VL_DISC_LIM         variable-list       0xC00100CB
%TXT%   variable    __disc_lim          unsigned            0x800200CA
%IMP%   VARIABLE    __disc_lim
**********************************************************************
*/
VARIABLE    __disc_lim
{
    LABEL           [disc_lim_label] ;
    HELP            [disc_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disc_pri
%SYM%   member      DISC_PRI            parameter           0xC00100CC
%SYM%   member      VL_DISC_PRI         variable-list       0xC00100CD
%TXT%   variable    __disc_pri          unsigned            0x800200CC
%IMP%   VARIABLE    __disc_pri
**********************************************************************
*/
VARIABLE    __disc_pri
{
    LABEL           [disc_pri_label] ;
    HELP            [disc_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_hi_alm       (DS-71)
%SYM%   member      DV_HI_ALM           parameter           0xC00100CE
%SYM%   member      VL_DV_HI_ALM        variable-list       0xC00100CF
%TXT%   record      __dv_hi_alm                             0x800200CE
%IMP%   RECORD      __dv_hi_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __dv_hi_alm
{
    LABEL           [dv_hi_alm_label] ;
    HELP            [dv_hi_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_hi_lim
%SYM%   member      DV_HI_LIM           parameter           0xC00100D0
%SYM%   member      VL_DV_HI_LIM        variable-list       0xC00100D1
%TXT%   variable    __dv_hi_lim         float               0x800200D0
%IMP%   VARIABLE    __dv_hi_lim
**********************************************************************
*/
VARIABLE    __dv_hi_lim
{
    LABEL           [dv_hi_lim_label] ;
    HELP            [dv_hi_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_hi_pri
%SYM%   member      DV_HI_PRI           parameter           0xC00100D2
%SYM%   member      VL_DV_HI_PRI        variable-list       0xC00100D3
%TXT%   variable    __dv_hi_pri         unsigned            0x800200D2
%IMP%   VARIABLE    __dv_hi_pri
**********************************************************************
*/
VARIABLE    __dv_hi_pri
{
    LABEL           [dv_hi_pri_label] ;
    HELP            [dv_hi_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_lo_alm       (DS-71)
%SYM%   member      DV_LO_ALM           parameter           0xC00100D4
%SYM%   member      VL_DV_LO_ALM        variable-list       0xC00100D5
%TXT%   record      __dv_lo_alm                             0x800200D4
%IMP%   RECORD      __dv_lo_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __dv_lo_alm
{
    LABEL           [dv_lo_alm_label] ;
    HELP            [dv_lo_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_lo_lim
%SYM%   member      DV_LO_LIM           parameter           0xC00100D6
%SYM%   member      VL_DV_LO_LIM        variable-list       0xC00100D7
%TXT%   variable    __dv_lo_lim         float               0x800200D6
%IMP%   VARIABLE    __dv_lo_lim
**********************************************************************
*/
VARIABLE    __dv_lo_lim
{
    LABEL           [dv_lo_lim_label] ;
    HELP            [dv_lo_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__dv_lo_pri
%SYM%   member      DV_LO_PRI           parameter           0xC00100D8
%SYM%   member      VL_DV_LO_PRI        variable-list       0xC00100D9
%TXT%   variable    __dv_lo_pri         unsigned            0x800200D8
%IMP%   VARIABLE    __dv_lo_pri
**********************************************************************
*/
VARIABLE    __dv_lo_pri
{
    LABEL           [dv_lo_pri_label] ;
    HELP            [dv_lo_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__fault_state
%SYM%   member      FAULT_state          parameter          0xC00100DA
%SYM%   member      VL_FAULT_state       variable-list      0xC00100DB
%TXT%   variable    __fault_state        enumerated         0x800200DA
%IMP%   VARIABLE    __fault_state
**********************************************************************
*/
VARIABLE    __fault_state
{
    LABEL           [fault_state_label] ;
    HELP            [fault_state_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [clear_faultstate],    [clear_faultstate_off_help] },
        { 0x02,  [active],              [active_faultstate_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__feature_sel          FF-891-1.2,  5.4.1
%SYM%   member      FEATURE_SEL         parameter           0xC00100DC
%SYM%   member      VL_FEATURE_SEL      variable-list       0xC00100DD
%TXT%   variable    __feature_sel       bit-enumerated      0x800200DC
%IMP%   VARIABLE    __feature_sel
**********************************************************************
*/
VARIABLE    __feature_sel
{
    LABEL           [feature_sel_label] ;
    HELP            [feature_sel_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_FEATURES_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__features          FF-891-1.2,  5.4.1
%SYM%   member      FEATURES            parameter           0xC00100DE
%SYM%   member      VL_FEATURES         variable-list       0xC00100DF
%TXT%   variable    __features          bit-enumerated      0x800200DE
%IMP%   VARIABLE    __features
**********************************************************************
*/
VARIABLE    __features
{
    LABEL           [features_label] ;
    HELP            [features_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_FEATURES_ENUMS    
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__ff_gain
%SYM%   member      FF_GAIN             parameter           0xC00100E0
%SYM%   member      VL_FF_GAIN          variable-list       0xC00100E1
%TXT%   variable    __ff_gain           float               0x800200E0
%IMP%   VARIABLE    __ff_gain
**********************************************************************
*/
VARIABLE    __ff_gain
{
    LABEL           [ff_gain_label] ;
    HELP            [ff_gain_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__ff_scale        (DS-68)
%SYM%   member      FF_SCALE            parameter           0xC00100E2
%SYM%   member      VL_FF_SCALE         variable-list       0xC00100E3
%TXT%   record      __ff_scale                              0x800200E2
%IMP%   RECORD      __ff_scale
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __ff_scale
{
    LABEL           [ff_scale_label] ;
    HELP            [ff_scale_help] ;
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
__ff_val          (DS-65)
%SYM%   member      FF_VAL              parameter           0xC00100E4
%SYM%   member      VL_FF_VAL           variable-list       0xC00100E5
%TXT%   record      __ff_val                                0x800200E4
%IMP%   RECORD      __ff_val
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __ff_val
{
    LABEL           [ff_val_label] ;
    HELP            [ff_val_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__field_val       (DS-65)
%SYM%   member      FIELD_VAL           parameter           0xC00100E6
%SYM%   member      VL_FIELD_VAL        variable-list       0xC00100E7
%TXT%   record      __field_val                             0x800200E6
%IMP%   RECORD      __field_val
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __field_val_r
**********************************************************************
*/
RECORD      __field_val
{
    LABEL           [field_val_label] ;
    HELP            [field_val_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __field_val_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__field_val_d     (DS-66)
%SYM%   member      FIELD_VAL_D         parameter           0xC00100E8
%SYM%   member      VL_FIELD_VAL_D      variable-list       0xC00100E9
%TXT%   record      __field_val_d                           0x800200E8
%IMP%   RECORD      __field_val_d
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __discrete_contained_r
**********************************************************************
*/
RECORD      __field_val_d
{
    LABEL           [field_val_d_label] ;
    HELP            [field_val_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__free_space
%SYM%   member      FREE_SPACE          parameter           0xC00100EA
%SYM%   member      VL_FREE_SPACE       variable-list       0xC00100EB
%TXT%   variable    __free_space        float               0x800200EA
%IMP%   VARIABLE    __free_space
**********************************************************************
*/
VARIABLE    __free_space
{
    LABEL           [free_space_label] ;
    HELP            [free_space_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
        MAX_VALUE   100.0 ;
    }
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__free_time
%SYM%   member      FREE_TIME           parameter           0xC00100EC
%SYM%   member      VL_FREE_TIME        variable-list       0xC00100ED
%TXT%   variable    __free_time         float               0x800200EC
%IMP%   VARIABLE    __free_time
**********************************************************************
*/
VARIABLE    __free_time
{
    LABEL           [free_time_label] ;
    HELP            [free_time_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
        MAX_VALUE   100.0 ;
    }
    CONSTANT_UNIT   [percent] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__fstate_time
%SYM%   member      FSTATE_TIME          parameter           0xC00100EE
%SYM%   member      VL_FSTATE_TIME       variable-list       0xC00100EF
%TXT%   variable    __fstate_time        float               0x800200EE
%IMP%   VARIABLE    __fstate_time
**********************************************************************
*/
VARIABLE    __fstate_time
{
    LABEL           [fstate_time_label] ;
    HELP            [fstate_time_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__fstate_val
%SYM%   member      FSTATE_VAL        parameter           0xC00100F0
%SYM%   member      VL_FSTATE_VAL     variable-list       0xC00100F1
%TXT%   variable    __fstate_val      float               0x800200F0
%IMP%   VARIABLE    __fstate_val
**********************************************************************
*/
VARIABLE    __fstate_val
{
    LABEL           [fstate_val_label] ;
    HELP            [fstate_val_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__fstate_val_d
%SYM%   member      FSTATE_VAL_D         parameter           0xC00100F2
%SYM%   member      VL_FSTATE_VAL_D      variable-list       0xC00100F3
%TXT%   variable    __fstate_val_d       unsigned            0x800200F2
%IMP%   VARIABLE    __fstate_val_d
**********************************************************************
*/
VARIABLE    __fstate_val_d
{
    LABEL           [fstate_val_d_label] ;
    HELP            [fstate_val_d_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__gain
%SYM%   member      GAIN                parameter           0xC00100F4
%SYM%   member      VL_GAIN             variable-list       0xC00100F5
%TXT%   variable    __gain              float               0x800200F4
%IMP%   VARIABLE    __gain
**********************************************************************
*/
VARIABLE    __gain
{
    LABEL           [gain_label] ;
    HELP            [gain_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__grant_deny
%SYM%   member      GRANT_DENY          parameter           0xC00100F6
%SYM%   member      VL_GRANT_DENY       variable-list       0xC00100F7
%TXT%   record      __grant_deny                            0x800200F6
%IMP%   RECORD      __grant_deny
%IMP%       VARIABLE    __grant
%IMP%       VARIABLE    __deny
**********************************************************************
*/
RECORD      __grant_deny
{
    LABEL           [grant_deny_label] ;
    HELP            [grant_deny_help] ;
    MEMBERS
    {
        GRANT,   __grant ;
        DENY,    __deny ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hard_types          FF-891-1.2,  5.4.1
%SYM%   member      HARD_TYPES          parameter           0xC00100F8
%SYM%   member      VL_HARD_TYPES       variable-list       0xC00100F9
%TXT%   variable    __hard_types        bit-enumerated      0x800200F8
%IMP%   VARIABLE    __hard_types
**********************************************************************
*/
VARIABLE    __hard_types
{
    LABEL           [hard_types_label] ;
    HELP            [hard_types_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,  [hardware_scalar_input],       [hardware_scalar_input_help] },
        { 0x0002,  [hardware_scalar_output],      [hardware_scalar_output_help] },
        { 0x0004,  [hardware_discrete_input],     [hardware_discrete_input_help] },
        { 0x0008,  [hardware_discrete_output],    [hardware_discrete_output_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_alm      (DS-71)
%SYM%   member      HI_ALM              parameter           0xC00100FA
%SYM%   member      VL_HI_ALM           variable-list       0xC00100FB
%TXT%   record      __hi_alm                                0x800200FA
%IMP%   RECORD      __hi_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __hi_alm
{
    LABEL           [hi_alm_label] ;
    HELP            [hi_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_hi_alm       (DS-71)
%SYM%   member      HI_HI_ALM           parameter           0xC00100FC
%SYM%   member      VL_HI_HI_ALM        variable-list       0xC00100FD
%TXT%   record      __hi_hi_alm                             0x800200FC
%IMP%   RECORD      __hi_hi_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __hi_hi_alm
{
    LABEL           [hi_hi_alm_label] ;
    HELP            [hi_hi_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_hi_lim
%SYM%   member      HI_HI_LIM           parameter           0xC00100FE
%SYM%   member      VL_HI_HI_LIM        variable-list       0xC00100FF
%TXT%   variable    __hi_hi_lim         float               0x800200FE
%IMP%   VARIABLE    __hi_hi_lim
**********************************************************************
*/
VARIABLE    __hi_hi_lim
{
    LABEL           [hi_hi_lim_label] ;
    HELP            [hi_hi_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_hi_pri
%SYM%   member      HI_HI_PRI           parameter           0xC0010100
%SYM%   member      VL_HI_HI_PRI        variable-list       0xC0010101
%TXT%   variable    __hi_hi_pri         unsigned            0x80020100
%IMP%   VARIABLE    __hi_hi_pri
**********************************************************************
*/
VARIABLE    __hi_hi_pri
{
    LABEL           [hi_hi_pri_label] ;
    HELP            [hi_hi_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_lim
%SYM%   member      HI_LIM              parameter           0xC0010102
%SYM%   member      VL_HI_LIM           variable-list       0xC0010103
%TXT%   variable    __hi_lim            float               0x80020102
%IMP%   VARIABLE    __hi_lim
**********************************************************************
*/
VARIABLE    __hi_lim
{
    LABEL           [hi_lim_label] ;
    HELP            [hi_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__hi_pri
%SYM%   member      HI_PRI              parameter           0xC0010104
%SYM%   member      VL_HI_PRI           variable-list       0xC0010105
%TXT%   variable    __hi_pri            unsigned            0x80020104
%IMP%   VARIABLE    __hi_pri
**********************************************************************
*/
VARIABLE    __hi_pri
{
    LABEL           [hi_pri_label] ;
    HELP            [hi_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__io_opts          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts           bit-enumerated      0x80020106
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
           __FF_IO_OPTS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__in              (DS-65)
%SYM%   member      IN                  parameter           0xC0010108
%SYM%   member      VL_IN               variable-list       0xC0010109
%TXT%   record      __in                                    0x80020108
%IMP%   RECORD      __in
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __in
{
    LABEL           [in_label] ;
    HELP            [in_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__in_1            (DS-65)
%SYM%   member      IN_1                parameter           0xC001010A
%SYM%   member      VL_IN_1             variable-list       0xC001010B
%TXT%   record      __in_1                                  0x8002010A
%IMP%   RECORD      __in_1
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __in_1
{
    LABEL           [in_1_label] ;
    HELP            [in_1_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__l_type
%SYM%   member      L_TYPE              parameter           0xC001010C
%SYM%   member      VL_L_TYPE           variable-list       0xC001010D
%TXT%   variable    __l_type            enumerated          0x8002010C
%IMP%   VARIABLE    __l_type
**********************************************************************
*/
VARIABLE    __l_type
{
    LABEL           [l_type_label] ;
    HELP            [l_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [direct],                [direct_help] },
        { 0x02,  [indirect],              [indirect_help] },
        { 0x03,  [indirect_square_root],  [indirect_square_root_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lim_notify
%SYM%   member      LIM_NOTIFY          parameter           0xC001010E
%SYM%   member      VL_LIM_NOTIFY       variable-list       0xC001010F
%TXT%   variable    __lim_notify        unsigned            0x8002010E
%IMP%   VARIABLE    __lim_notify
**********************************************************************
*/
VARIABLE    __lim_notify
{
    LABEL           [lim_notify_label] ;
    HELP            [lim_notify_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE       PARAM.MAX_NOTIFY ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__low_cut
%SYM%   member      LOW_CUT             parameter           0xC0010110
%SYM%   member      VL_LOW_CUT          variable-list       0xC0010111
%TXT%   variable    __low_cut           float               0x80020110
%IMP%   VARIABLE    __low_cut
**********************************************************************
*/
VARIABLE    __low_cut
{
    LABEL           [low_cut_label] ;
    HELP            [low_cut_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT
    {
        MIN_VALUE       0.0 ;
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_alm          (DS-71)
%SYM%   member      LO_ALM              parameter           0xC0010112
%SYM%   member      VL_LO_ALM           variable-list       0xC0010113
%TXT%   record      __lo_alm                                0x80020112
%IMP%   RECORD      __lo_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __lo_alm
{
    LABEL           [lo_alm_label] ;
    HELP            [lo_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_lim
%SYM%   member      LO_LIM              parameter           0xC0010114
%SYM%   member      VL_LO_LIM           variable-list       0xC0010115
%TXT%   variable    __lo_lim            float               0x80020114
%IMP%   VARIABLE    __lo_lim
**********************************************************************
*/
VARIABLE    __lo_lim
{
    LABEL           [lo_lim_label] ;
    HELP            [lo_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_pri
%SYM%   member      LO_PRI              parameter           0xC0010116
%SYM%   member      VL_LO_PRI           variable-list       0xC0010117
%TXT%   variable    __lo_pri            unsigned            0x80020116
%IMP%   VARIABLE    __lo_pri
**********************************************************************
*/
VARIABLE    __lo_pri
{
    LABEL           [lo_pri_label] ;
    HELP            [lo_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_lo_alm       (DS-71)
%SYM%   member      LO_LO_ALM           parameter           0xC0010118
%SYM%   member      VL_LO_LO_ALM        variable-list       0xC0010119
%TXT%   record      __lo_lo_alm                             0x80020118
%IMP%   RECORD      __lo_lo_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __float_value
**********************************************************************
*/
RECORD      __lo_lo_alm
{
    LABEL           [lo_lo_alm_label] ;
    HELP            [lo_lo_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_lo_lim
%SYM%   member      LO_LO_LIM           parameter           0xC001011A
%SYM%   member      VL_LO_LO_LIM        variable-list       0xC001011B
%TXT%   variable    __lo_lo_lim         float               0x8002011A
%IMP%   VARIABLE    __lo_lo_lim
**********************************************************************
*/
VARIABLE    __lo_lo_lim
{
    LABEL           [lo_lo_lim_label] ;
    HELP            [lo_lo_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__lo_lo_pri
%SYM%   member      LO_LO_PRI           parameter           0xC001011C
%SYM%   member      VL_LO_LO_PRI        variable-list       0xC001011D
%TXT%   variable    __lo_lo_pri         unsigned            0x8002011C
%IMP%   VARIABLE    __lo_lo_pri
**********************************************************************
*/
VARIABLE    __lo_lo_pri
{
    LABEL           [lo_lo_pri_label] ;
    HELP            [lo_lo_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__manufac_id
%SYM%   member      MANUFAC_ID          parameter           0xC001011E
%SYM%   member      VL_MANUFAC_ID       variable-list       0xC001011F
%TXT%   variable    __manufac_id        enumerated          0x8002011E
%IMP%   VARIABLE    __manufac_id
**********************************************************************
*/
VARIABLE    __manufac_id
{
    LABEL           [manufac_id_label] ;
    HELP            [manufac_id_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (4)
    {
            __FF_MFR_INDEX
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__max_notify
%SYM%   member      MAX_NOTIFY          parameter           0xC0010120
%SYM%   member      VL_MAX_NOTIFY       variable-list       0xC0010121
%TXT%   variable    __max_notify        unsigned            0x80020120
%IMP%   VARIABLE    __max_notify
**********************************************************************
*/
VARIABLE    __max_notify
{
    LABEL           [max_notify_label] ;
    HELP            [max_notify_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__memory_size
%SYM%   member      MEMORY_SIZE         parameter           0xC0010122
%SYM%   member      VL_MEMORY_SIZE      variable-list       0xC0010123
%TXT%   variable    __memory_size       unsigned            0x80020122
%IMP%   VARIABLE    __memory_size
**********************************************************************
*/
VARIABLE    __memory_size
{
    LABEL           [memory_size_label] ;
    HELP            [memory_size_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [kilobytes] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__min_cycle_t
%SYM%   member      MIN_CYCLE_T         parameter           0xC0010124
%SYM%   member      VL_MIN_CYCLE_T      variable-list       0xC0010125
%TXT%   variable    __min_cycle_t       unsigned            0x80020124
%IMP%   VARIABLE    __min_cycle_t
**********************************************************************
*/
VARIABLE    __min_cycle_t
{
    LABEL           [min_cycle_t_label] ;
    HELP            [min_cycle_t_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__mode_blk        (DS-69)
%SYM%   member      MODE_BLK            parameter           0xC0010126
%SYM%   member      VL_MODE_BLK         variable-list       0xC0010127
%TXT%   record      __mode_blk                              0x80020126
%IMP%   RECORD      __mode_blk
%IMP%       VARIABLE    __target_mode
%IMP%       VARIABLE    __actual_mode
%IMP%       VARIABLE    __permitted_mode
%IMP%       VARIABLE    __normal_mode
**********************************************************************
*/
RECORD      __mode_blk
{
    LABEL           [mode_blk_label] ;
    HELP            [mode_blk_help] ;
    MEMBERS
    {
        TARGET,       __target_mode ;
        ACTUAL,       __actual_mode ;
        PERMITTED,    __permitted_mode ;
        NORMAL,       __normal_mode ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__nv_cycle_t
%SYM%   member      NV_CYCLE_T          parameter           0xC0010128
%SYM%   member      VL_NV_CYCLE_T       variable-list       0xC0010129
%TXT%   variable    __nv_cycle_t        unsigned            0x80020128
%IMP%   VARIABLE    __nv_cycle_t
**********************************************************************
*/
VARIABLE    __nv_cycle_t
{
    LABEL           [nv_cycle_t_label] ;
    HELP            [nv_cycle_t_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__out             (DS-65)
%SYM%   member      OUT                 parameter           0xC001012A
%SYM%   member      VL_OUT              variable-list       0xC001012B
%TXT%   record      __out                                   0x8002012A
%IMP%   RECORD      __out
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out
{
    LABEL           [out_label] ;
    HELP            [out_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__out_d           (DS-66)
%SYM%   member      OUT_D               parameter           0xC001012C
%SYM%   member      VL_OUT_D            variable-list       0xC001012D
%TXT%   record      __out_d                                 0x8002012C
%IMP%   RECORD      __out_d
%IMP%       VARIABLE    __status_output
%IMP%       VARIABLE    __discrete_output
**********************************************************************
*/
RECORD      __out_d
{
    LABEL           [out_d_label] ;
    HELP            [out_d_help] ;
    MEMBERS
    {
        STATUS,  __status_output_r ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__out_hi_lim
%SYM%   member      OUT_HI_LIM          parameter           0xC001012E
%SYM%   member      VL_OUT_HI_LIM       variable-list       0xC001012F
%TXT%   variable    __out_hi_lim        float               0x8002012E
%IMP%   VARIABLE    __out_hi_lim
**********************************************************************
*/
VARIABLE    __out_hi_lim
{
    LABEL           [out_hi_lim_label] ;
    HELP            [out_hi_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__out_lo_lim
%SYM%   member      OUT_LO_LIM          parameter           0xC0010130
%SYM%   member      VL_OUT_LO_LIM       variable-list       0xC0010131
%TXT%   variable    __out_lo_lim        float               0x80020130
%IMP%   VARIABLE    __out_lo_lim
**********************************************************************
*/
VARIABLE    __out_lo_lim
{
    LABEL           [out_lo_lim_label] ;
    HELP            [out_lo_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__out_scale       (DS-68)
%SYM%   member      OUT_SCALE           parameter           0xC0010132
%SYM%   member      VL_OUT_SCALE        variable-list       0xC0010133
%TXT%   record      __out_scale                             0x80020132
%IMP%   RECORD      __out_scale
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __out_scale
{
    LABEL           [out_scale_label] ;
    HELP            [out_scale_help] ;
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
__out_state
%SYM%   member      OUT_STATE           parameter           0xC0010134
%SYM%   member      VL_OUT_STATE        variable-list       0xC0010135
%TXT%   variable    __out_state         unsigned            0x80020134
%IMP%   VARIABLE    __out_state
**********************************************************************
*/
VARIABLE    __out_state
{
    LABEL           [out_state_label] ;
    HELP            [out_state_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__pv              (DS-65)
%SYM%   member      PV                  parameter           0xC0010136
%SYM%   member      VL_PV               variable-list       0xC0010137
%TXT%   record      __pv                                    0x80020136
%IMP%   RECORD      __pv
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __float_contained_r
**********************************************************************
*/
RECORD      __pv
{
    LABEL           [pv_label] ;
    HELP            [pv_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__pv_d            (DS-66)
%SYM%   member      PV_D                parameter           0xC0010138
%SYM%   member      VL_PV_D             variable-list       0xC0010139
%TXT%   record      __pv_d                                  0x80020138
%IMP%   RECORD      __pv_d
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __discrete_contained_r
**********************************************************************
*/
RECORD      __pv_d
{
    LABEL           [pv_d_label] ;
    HELP            [pv_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__pv_ftime
%SYM%   member      PV_FTIME            parameter           0xC001013A
%SYM%   member      VL_PV_FTIME         variable-list       0xC001013B
%TXT%   variable    __pv_ftime          float               0x8002013A
%IMP%   VARIABLE    __pv_ftime
**********************************************************************
*/
VARIABLE    __pv_ftime
{
    LABEL           [pv_ftime_label] ;
    HELP            [pv_ftime_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__pv_scale        (DS-68)
%SYM%   member      PV_SCALE            parameter           0xC001013C
%SYM%   member      VL_PV_SCALE         variable-list       0xC001013D
%TXT%   record      __pv_scale                              0x8002013C
%IMP%   RECORD      __pv_scale
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __pv_scale
{
    LABEL           [pv_scale_label] ;
    HELP            [pv_scale_help] ;
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
__pv_state
%SYM%   member      PV_STATE            parameter           0xC001013E
%SYM%   member      VL_PV_STATE         variable-list       0xC001013F
%TXT%   variable    __pv_state          unsigned            0x8002013E
%IMP%   VARIABLE    __pv_state
**********************************************************************
*/
VARIABLE    __pv_state
{
    LABEL           [pv_state_label] ;
    HELP            [pv_state_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__ra_ftime
%SYM%   member      RA_FTIME            parameter           0xC0010140
%SYM%   member      VL_RA_FTIME         variable-list       0xC0010141
%TXT%   variable    __ra_ftime          float               0x80020140
%IMP%   VARIABLE    __ra_ftime
**********************************************************************
*/
VARIABLE    __ra_ftime
{
    LABEL           [ra_ftime_label] ;
    HELP            [ra_ftime_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rate
%SYM%   member      RATE                parameter           0xC0010142
%SYM%   member      VL_RATE             variable-list       0xC0010143
%TXT%   variable    __rate              float               0x80020142
%IMP%   VARIABLE    __rate
**********************************************************************
*/
VARIABLE    __rate
{
    LABEL           [rate_label] ;
    HELP            [rate_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rcas_in             (DS-65)
%SYM%   member      RCAS_IN             parameter           0xC0010144
%SYM%   member      VL_RCAS_IN          variable-list       0xC0010145
%TXT%   record      __rcas_in                               0x80020144
%IMP%   RECORD      __rcas_in
%IMP%       VARIABLE    __status_contained_nd
%IMP%       VARIABLE    __float_contained_nd
**********************************************************************
*/
RECORD      __rcas_in
{
    LABEL           [rcas_in_label] ;
    HELP            [rcas_in_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __float_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rcas_in_d           (DS-66)
%SYM%   member      RCAS_IN_D           parameter           0xC0010146
%SYM%   member      VL_RCAS_IN_D        variable-list       0xC0010147
%TXT%   record      __rcas_in_d                             0x80020146
%IMP%   RECORD      __rcas_in_d
%IMP%       VARIABLE    __status_contained_nd
%IMP%       VARIABLE    __discrete_contained_r
**********************************************************************
*/
RECORD      __rcas_in_d
{
    LABEL           [rcas_in_d_label] ;
    HELP            [rcas_in_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_nd ;
        VALUE,   __discrete_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rcas_out                (DS-65)
%SYM%   member      RCAS_OUT            parameter           0xC0010148
%SYM%   member      VL_RCAS_OUT         variable-list       0xC0010149
%TXT%   record      __rcas_out                              0x80020148
%IMP%   RECORD      __rcas_out
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __float_contained_r
**********************************************************************
*/
RECORD      __rcas_out
{
    LABEL           [rcas_out_label] ;
    HELP            [rcas_out_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rcas_out_d          (DS-66)
%SYM%   member      RCAS_OUT_D          parameter           0xC001014A
%SYM%   member      VL_RCAS_OUT_D       variable-list       0xC001014B
%TXT%   record      __rcas_out_d                            0x8002014A
%IMP%   RECORD      __rcas_out_d
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __discrete_contained_r
**********************************************************************
*/
RECORD      __rcas_out_d
{
    LABEL           [rcas_out_d_label] ;
    HELP            [rcas_out_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__readback                (DS-65)
%SYM%   member      READBACK            parameter           0xC001014C
%SYM%   member      VL_READBACK         variable-list       0xC001014D
%TXT%   record      __readback                              0x8002014C
%IMP%   RECORD      __readback
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __float_contained_r
**********************************************************************
*/
RECORD      __readback
{
    LABEL           [readback_label] ;
    HELP            [readback_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__readback_d          (DS-66)
%SYM%   member      READBACK_D          parameter           0xC001014E
%SYM%   member      VL_READBACK_D       variable-list       0xC001014F
%TXT%   record      __readback_d                            0x8002014E
%IMP%   RECORD      __readback_d
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __discrete_contained_r
**********************************************************************
*/
RECORD      __readback_d
{
    LABEL           [readback_d_label] ;
    HELP            [readback_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__reset
%SYM%   member      RESET               parameter           0xC0010150
%SYM%   member      VL_RESET            variable-list       0xC0010151
%TXT%   variable    __reset             float               0x80020150
%IMP%   VARIABLE    __reset
**********************************************************************
*/
VARIABLE    __reset
{
    LABEL           [reset_label] ;
    HELP            [reset_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__restart
%SYM%   member      RESTART             parameter           0xC0010152
%SYM%   member      VL_RESTART          variable-list       0xC0010153
%TXT%   variable    __restart           enumerated          0x80020152
%IMP%   VARIABLE    __restart
**********************************************************************
*/
VARIABLE    __restart
{
    LABEL           [restart_label] ;
    HELP            [restart_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [restart_run],         [restart_run_help] },
        { 0x02,    [restart_resource],    [restart_resource_help] },
        { 0x03,    [restart_defaults],    [restart_defaults_help] },
        { 0x04,    [restart_processor],   [restart_processor_help] }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rout_in             (DS-65)
%SYM%   member      ROUT_IN             parameter           0xC0010154
%SYM%   member      VL_ROUT_IN          variable-list       0xC0010155
%TXT%   record      __rout_in                               0x80020154
%IMP%   RECORD      __rout_in
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __float_contained
**********************************************************************
*/
RECORD      __rout_in
{
    LABEL           [rout_in_label] ;
    HELP            [rout_in_help] ;
    MEMBERS
    {
        STATUS,  __status_contained ;
        VALUE,   __float_contained ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rout_out                (DS-65)
%SYM%   member      ROUT_OUT            parameter           0xC0010156
%SYM%   member      VL_ROUT_OUT         variable-list       0xC0010157
%TXT%   record      __rout_out                              0x80020156
%IMP%   RECORD      __rout_out
%IMP%       VARIABLE    __status_contained_r
%IMP%       VARIABLE    __float_contained_r
**********************************************************************
*/
RECORD      __rout_out
{
    LABEL           [rout_out_label] ;
    HELP            [rout_out_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__rs_state
%SYM%   member      RS_STATE            parameter           0xC0010158
%SYM%   member      VL_RS_STATE         variable-list       0xC0010159
%TXT%   variable    __rs_state          enumerated          0x80020158
%IMP%   VARIABLE    __rs_state
**********************************************************************
*/
VARIABLE    __rs_state
{
    LABEL           [rs_state_label] ;
    HELP            [rs_state_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [state_restart],       [state_restart_help] },
        { 0x02,    [state_init],          [state_init_help] },
        { 0x03,    [state_linking],       [state_linking_help] },
        { 0x04,    [state_online],        [state_online_help] },
        { 0x05,    [state_standby],       [state_standby_help] },
        { 0x06,    [state_failure],       [state_failure_help] }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sel_1           (DS-65)
%SYM%   member      SEL_1               parameter           0xC001015A
%SYM%   member      VL_SEL_1            variable-list       0xC001015B
%TXT%   record      __sel_1                                 0x8002015A
%IMP%   RECORD      __sel_1
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __sel_1
{
    LABEL           [sel_1_label] ;
    HELP            [sel_1_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sel_2           (DS-65)
%SYM%   member      SEL_2               parameter           0xC001015C
%SYM%   member      VL_SEL_2            variable-list       0xC001015D
%TXT%   record      __sel_2                                 0x8002015C
%IMP%   RECORD      __sel_2
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __sel_2
{
    LABEL           [sel_2_label] ;
    HELP            [sel_2_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sel_3           (DS-65)
%SYM%   member      SEL_3               parameter           0xC001015E
%SYM%   member      VL_SEL_3            variable-list       0xC001015F
%TXT%   record      __sel_3                                 0x8002015E
%IMP%   RECORD      __sel_3
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __sel_3
{
    LABEL           [sel_3_label] ;
    HELP            [sel_3_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sel_type
%SYM%   member      SEL_TYPE            parameter           0xC0010160
%SYM%   member      VL_SEL_TYPE         variable-list       0xC0010161
%TXT%   variable    __sel_type          enumerated          0x80020160
%IMP%   VARIABLE    __sel_type
**********************************************************************
*/
VARIABLE    __sel_type
{
    LABEL           [sel_type_label] ;
    HELP            [sel_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [select_high],     [select_high_help] },
        { 0x02,    [select_low],      [select_low_help] },
        { 0x03,    [select_middle],   [select_middle_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__set_fstate
%SYM%   member      SET_FSTATE           parameter           0xC0010162
%SYM%   member      VL_SET_FSTATE        variable-list       0xC0010163
%TXT%   variable    __set_fstate         enumerated          0x80020162
%IMP%   VARIABLE    __set_fstate
**********************************************************************
*/
VARIABLE    __set_fstate
{
    LABEL           [set_fstate_label] ;
    HELP            [set_fstate_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [faultstate_off],  [faultstate_off_help] },
        { 0x02,  [faultstate_set],  [faultstate_set_help] }

    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__shed_opt
%SYM%   member      SHED_OPT            parameter           0xC0010164
%SYM%   member      VL_SHED_OPT         variable-list       0xC0010165
%TXT%   variable    __shed_opt          enumerated          0x80020164
%IMP%   VARIABLE    __shed_opt
**********************************************************************
*/
VARIABLE    __shed_opt
{
    LABEL           [shed_opt_label] ;
    HELP            [shed_opt_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,  [shed_normal_normal],    [shed_normal_normal_help] },
        { 0x02,  [shed_normal_no],        [shed_normal_no_help] },
        { 0x03,  [shed_auto_normal],      [shed_auto_normal_help] },
        { 0x04,  [shed_auto_no],          [shed_auto_no_help] },
        { 0x05,  [shed_man_normal],       [shed_man_normal_help] },
        { 0x06,  [shed_man_no],           [shed_man_no_help] },
        { 0x07,  [shed_retained_normal],  [shed_retained_normal_help] },
        { 0x08,  [shed_retained_no],      [shed_retained_no_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__shed_rcas
%SYM%   member      SHED_RCAS           parameter           0xC0010166
%SYM%   member      VL_SHED_RCAS        variable-list       0xC0010167
%TXT%   variable    __shed_rcas         unsigned            0x80020166
%IMP%   VARIABLE    __shed_rcas
**********************************************************************
*/
VARIABLE    __shed_rcas
{
    LABEL           [shed_rcas_label] ;
    HELP            [shed_rcas_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__shed_rout
%SYM%   member      SHED_ROUT           parameter           0xC0010168
%SYM%   member      VL_SHED_ROUT        variable-list       0xC0010169
%TXT%   variable    __shed_rout         unsigned            0x80020168
%IMP%   VARIABLE    __shed_rout
**********************************************************************
*/
VARIABLE    __shed_rout
{
    LABEL           [shed_rout_label] ;
    HELP            [shed_rout_help] ;
    CLASS           CONTAINED & TUNE ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__simulate        (DS-82)
%SYM%   member      SIMULATE            parameter           0xC001016A
%SYM%   member      VL_SIMULTATE        variable-list       0xC001016B
%IMP%   RECORD      __simulate_float
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __float_contained_r
%IMP%       VARIABLE    __float_contained_rw
%IMP%       VARIABLE    __enable_disable
**********************************************************************
*/
/*
**********************************************************************
__simulate_d      (DS-83)
%SYM%   member      SIMULATE_D          parameter           0xC001016C
%SYM%   member      VL_SIMULATE_D       variable-list       0xC001016D
%IMP%   RECORD      __simulate_discrete
%IMP%       VARIABLE    __status_contained
%IMP%       VARIABLE    __discrete_contained_r
%IMP%       VARIABLE    __discrete_contained
%IMP%       VARIABLE    __enable_disable
**********************************************************************
*/
/*
**********************************************************************
__sp                      (DS-65)
%SYM%   member      SP                  parameter           0xC001016E
%SYM%   member      VL_SP               variable-list       0xC001016F
%TXT%   record      __sp                                    0x8002016E
%IMP%   RECORD      __sp
%IMP%       VARIABLE    __status_contained_nd
%IMP%       VARIABLE    __float_contained_nd
**********************************************************************
*/
RECORD      __sp
{
    LABEL           [sp_label] ;
    HELP            [sp_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __float_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sp_d                (DS-66)
%SYM%   member      SP_D                parameter           0xC0010170
%SYM%   member      VL_SP_D             variable-list       0xC0010171
%TXT%   record      __sp_d                                  0x80020170
%IMP%   RECORD      __sp_d
%IMP%       VARIABLE    __status_contained_nd
%IMP%       VARIABLE    __discrete_contained_nd
**********************************************************************
*/
RECORD      __sp_d
{
    LABEL           [sp_d_label] ;
    HELP            [sp_d_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sp_hi_lim
%SYM%   member      SP_HI_LIM           parameter           0xC0010172
%SYM%   member      VL_SP_HI_LIM        variable-list       0xC0010173
%TXT%   variable    __sp_hi_lim         float               0x80020172
%IMP%   VARIABLE    __sp_hi_lim
**********************************************************************
*/
VARIABLE    __sp_hi_lim
{
    LABEL           [sp_hi_lim_label] ;
    HELP            [sp_hi_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sp_lo_lim
%SYM%   member      SP_LO_LIM           parameter           0xC0010174
%SYM%   member      VL_SP_LO_LIM        variable-list       0xC0010175
%TXT%   variable    __sp_lo_lim         float               0x80020174
%IMP%   VARIABLE    __sp_lo_lim
**********************************************************************
*/
VARIABLE    __sp_lo_lim
{
    LABEL           [sp_lo_lim_label] ;
    HELP            [sp_lo_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sp_rate_dn
%SYM%   member      SP_RATE_DN          parameter           0xC0010176
%SYM%   member      VL_SP_RATE_DN       variable-list       0xC0010177
%TXT%   variable    __sp_rate_dn        float               0x80020176
%IMP%   VARIABLE    __sp_rate_dn
**********************************************************************
*/
VARIABLE    __sp_rate_dn
{
    LABEL           [sp_rate_dn_label] ;
    HELP            [sp_rate_dn_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [pv_per_sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__sp_rate_up
%SYM%   member      SP_RATE_UP          parameter           0xC0010178
%SYM%   member      VL_SP_RATE_UP       variable-list       0xC0010179
%TXT%   variable    __sp_rate_up        float               0x80020178
%IMP%   VARIABLE    __sp_rate_up
**********************************************************************
*/
VARIABLE    __sp_rate_up
{
    LABEL           [sp_rate_up_label] ;
    HELP            [sp_rate_up_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT
    {
        MIN_VALUE   0.0 ;
    }
    CONSTANT_UNIT   [pv_per_sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__st_rev
%SYM%   member      ST_REV              parameter           0xC001017A
%SYM%   member      VL_ST_REV           variable-list       0xC001017B
%TXT%   variable    __st_rev            unsigned            0x8002017A
%IMP%   VARIABLE    __st_rev
**********************************************************************
*/
VARIABLE    __st_rev
{
    LABEL           [st_rev_label] ;
    HELP            [st_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts       bit-enumerated      0x8002017C
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__strategy
%SYM%   member      STRATEGY            parameter           0xC001017E
%SYM%   member      VL_STRATEGY         variable-list       0xC001017F
%TXT%   variable    __strategy          unsigned            0x8002017E
%IMP%   VARIABLE    __strategy
**********************************************************************
*/
VARIABLE    __strategy
{
    LABEL           [strategy_label] ;
    HELP            [strategy_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__tag_desc
%SYM%   member      TAG_DESC            parameter           0xC0010180
%SYM%   member      VL_TAG_DESC         variable-list       0xC0010181
%TXT%   variable    __tag_desc          octet               0x80020180
%IMP%   VARIABLE    __tag_desc
**********************************************************************
*/
VARIABLE    __tag_desc
{
    LABEL           [tag_desc_label] ;
    HELP            [tag_desc_help] ;
    CLASS           CONTAINED ;
    TYPE            OCTET (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__test_rw         (DS-85)
%SYM%   member      TEST_RW             parameter           0xC0010182
%SYM%   member      VL_TEST_RW          variable-list       0xC0010183
%IMP%   RECORD      __test_read_write
%IMP%       VARIABLE    __test_boolean
%IMP%       VARIABLE    __test_integer8
%IMP%       VARIABLE    __test_integer16
%IMP%       VARIABLE    __test_integer32
%IMP%       VARIABLE    __test_unsigned8
%IMP%       VARIABLE    __test_unsigned16
%IMP%       VARIABLE    __test_unsigned32
%IMP%       VARIABLE    __test_float
%IMP%       VARIABLE    __test_visible_string
%IMP%       VARIABLE    __test_octet_string
%IMP%       VARIABLE    __test_date
%IMP%       VARIABLE    __test_time
%IMP%       VARIABLE    __test_time_diff
%IMP%       VARIABLE    __test_bitstring
%IMP%       VARIABLE    __test_dll_time
**********************************************************************
*/
/*
**********************************************************************
__trk_in_d            (DS-66)
%SYM%   member      TRK_IN_D            parameter           0xC0010184
%SYM%   member      VL_TRK_IN_D         variable-list       0xC0010185
%TXT%   record      __trk_in_d                              0x80020184
%IMP%   RECORD      __trk_in_d
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __discrete_input_nd
**********************************************************************
*/
RECORD      __trk_in_d
{
    LABEL           [trk_in_d_label] ;
    HELP            [trk_in_d_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __on_off_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__trk_scale       (DS-68)
%SYM%   member      TRK_SCALE           parameter           0xC0010186
%SYM%   member      VL_TRK_SCALE        variable-list       0xC0010187
%TXT%   record      __trk_scale                             0x80020186
%IMP%   RECORD      __trk_scale
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __trk_scale
{
    LABEL           [trk_scale_label] ;
    HELP            [trk_scale_help] ;
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
__trk_val     (DS-65)
%SYM%   member      TRK_VAL             parameter           0xC0010188
%SYM%   member      VL_TRK_VAL          variable-list       0xC0010189
%TXT%   record      __trk_val                               0x80020188
%IMP%   RECORD      __trk_val
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
**********************************************************************
*/
RECORD      __trk_val
{
    LABEL           [trk_val_label] ;
    HELP            [trk_val_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__update_evt          (DS-73)
%SYM%   member      UPDATE_EVT          parameter           0xC001018A
%SYM%   member      VL_UPDATE_EVT       variable-list       0xC001018B
%IMP%   RECORD      __update_evt			    0x80020030
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __update_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __static_revision
%IMP%       VARIABLE    __relative_index
**********************************************************************
*/
RECORD      __update_evt
{
    LABEL           [event_update_label] ;
    HELP            [event_update_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,      __unacknowledged_evt ;
        UPDATE_STATE,        __update_state ;
        TIME_STAMP,          __time_stamp ;
        STATIC_REVISION,     __static_revision ;
        RELATIVE_INDEX,      __relative_index ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__write_alm       (DS-72)
%SYM%   member      WRITE_ALM           parameter           0xC001018C
%SYM%   member      VL_WRITE_ALM        variable-list       0xC001018D
%TXT%   record      __write_alm                             0x8002018C
%IMP%   RECORD      __write_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __write_alm
{
    LABEL           [write_alm_label] ;
    HELP            [write_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __discrete_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__write_lock
%SYM%   member      WRITE_LOCK          parameter           0xC001018E
%SYM%   member      VL_WRITE_LOCK       variable-list       0xC001018F
%TXT%   variable    __write_lock        enumerated          0x8002018E
%IMP%   VARIABLE    __write_lock
**********************************************************************
*/
VARIABLE    __write_lock
{
    LABEL           [write_lock_label] ;
    HELP            [write_lock_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            ENUMERATED (1)
    {
        _UNINITIALIZED_VALUE,
        { 0x01,    [write_not_locked],    [write_not_locked_help] },
        { 0x02,    [write_locked],        [write_locked_help] }
    }
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__write_pri
%SYM%   member      WRITE_PRI           parameter           0xC0010190
%SYM%   member      VL_WRITE_PRI        variable-list       0xC0010191
%TXT%   variable    __write_pri         unsigned            0x80020190
%IMP%   VARIABLE    __write_pri
**********************************************************************
*/
VARIABLE    __write_pri
{
    LABEL           [write_pri_label] ;
    HELP            [write_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__xd_scale        (DS-68)
%SYM%   member      XD_SCALE            parameter           0xC0010192
%SYM%   member      VL_XD_SCALE         variable-list       0xC0010193
%TXT%   record      __xd_scale                              0x80020192
%IMP%   RECORD      __xd_scale
%IMP%       VARIABLE    __eu_100
%IMP%       VARIABLE    __eu_0
%IMP%       VARIABLE    __units_index
%IMP%       VARIABLE    __decimal
**********************************************************************
*/
RECORD      __xd_scale
{
    LABEL           [xd_scale_label] ;
    HELP            [xd_scale_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,    __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__xd_state
%SYM%   member      XD_STATE            parameter           0xC0010194
%SYM%   member      VL_XD_STATE         variable-list       0xC0010195
%TXT%   variable    __xd_state          unsigned            0x80020194
%IMP%   VARIABLE    __xd_state
**********************************************************************
*/
VARIABLE    __xd_state
{
    LABEL           [xd_state_label] ;
    HELP            [xd_state_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__status_opts_aal          FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_aal       bit-enumerated      0x800201B2
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_aal
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
            __FF_STATUS_OPTS_AAL_ENUMS /*AR4815 in com_tbls.h*/
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_ai           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_ai       bit-enumerated      0x800201B3
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_ai
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
      __FF_STATUS_OPTS_AI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_ao           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_ao       bit-enumerated      0x800201B4
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_ao
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_AO_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_bg           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_bg       bit-enumerated      0x800201B5
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_bg
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
       __FF_STATUS_OPTS_BG_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_cs           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_cs       bit-enumerated      0x800201BA
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_cs
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
       __FF_STATUS_OPTS_CS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_os           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_os       bit-enumerated      0x800201C5
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_os
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
           __FF_STATUS_OPTS_OS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_ml           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_ml       bit-enumerated      0x800201C4
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_ml
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
      __FF_STATUS_OPTS_ML_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_pd           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_pd       bit-enumerated      0x800201C6
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_pd
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_PD_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_dc           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_dc       bit-enumerated      0x800201BC
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_dc
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
             __FF_STATUS_OPTS_DC_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_di           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_di       bit-enumerated      0x800201BD
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_di
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_DI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_do           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_do       bit-enumerated      0x800201BE
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_do
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
       __FF_STATUS_OPTS_DO_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_dt           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_dt       bit-enumerated      0x800201BF
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_dt
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_DT_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_pid           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_pid       bit-enumerated      0x800201C7
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_pid
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_PID_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_mio           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_mio       bit-enumerated      0x800201C3
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_mio
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_MIO_ENUMS  
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_ra           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_ra       bit-enumerated      0x800201C8
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_ra
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_RA_ENUMS

    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_spg           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_spg       bit-enumerated      0x800201C9
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_spg
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
          __FF_STATUS_OPTS_SPG_ENUMS

    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_tmr           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_tmr       bit-enumerated      0x800201CB
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_tmr
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
      __FF_STATUS_OPTS_TMR_ENUMS /*AR4815 in com_tbls.h*/

    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_ll           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_ll       bit-enumerated      0x8002017C
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_ll
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_LL_ENUMS

    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_is           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_is       bit-enumerated      0x800201C0
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_is
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_IS_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_it           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_it       bit-enumerated      0x800201C1
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_it
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
    __FF_STATUS_OPTS_IT_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_tot           FF-908
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_tot       bit-enumerated  0x80020F19
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_tot 
{ 
    LABEL           [status_opts_label] ; 
    HELP            [status_opts_help] ; 
    CLASS           CONTAINED ; 
    TYPE            BIT_ENUMERATED (2) 
    { 
        __FF_STATUS_OPTS_TOT_ENUMS 
    } 
    CONSTANT_UNIT   [blank] ; 
    HANDLING        READ & WRITE ; 
/*  RESPONSE_CODES  xxx ; */ 
} 

/*
**********************************************************************
__status_opts_calca           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_calca       bit-enumerated      0x800201B6
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_calca
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_CALCA_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_calcd           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_calcd       bit-enumerated      0x800201B7
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_calcd
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_STATUS_OPTS_CALCD_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__status_opts_cao           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_cao       bit-enumerated      0x800201B8
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_cao
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_CAO_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_cdo           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_cdo       bit-enumerated      0x800201B9
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_cdo
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_STATUS_OPTS_CDO_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_dal           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_dal       bit-enumerated      0x800201BB
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_dal
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
       __FF_STATUS_OPTS_DAL_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_spid           FF-891-1.2,  5.4.2.3
%SYM%   member      STATUS_OPTS         parameter           0xC001017C
%SYM%   member      VL_STATUS_OPTS      variable-list       0xC001017D
%TXT%   variable    __status_opts_spid       bit-enumerated      0x800201CA
%IMP%   VARIABLE    __status_opts
**********************************************************************
*/
VARIABLE    __status_opts_spid
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
           __FF_STATUS_OPTS_SPID_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_pi 
**********************************************************************
*/
VARIABLE    __status_opts_pi
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
           __FF_STATUS_OPTS_PI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_ml          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_ml      bit-enumerated      0x800201CC
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_ml
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_CONTROL_OPTS_ML_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_bg          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_bg      bit-enumerated      0x800201CD
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_bg
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_CONTROL_OPTS_BG_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_pd          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_pd      bit-enumerated      0x800201CE
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_pd
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_CONTROL_OPTS_PD_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_pid          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_pid      bit-enumerated      0x800201CF
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_pid
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_CONTROL_OPTS_PID_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_ra          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_ra      bit-enumerated      0x800202DA
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_ra
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_CONTROL_OPTS_RA_ENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__control_opts_spid          FF-891-1.2,  5.4.2.2
%SYM%   member      CONTROL_OPTS        parameter           0xC00100BA
%SYM%   member      VL_CONTROL_OPTS     variable-list       0xC00100BB
%TXT%   variable    __control_opts_spid      bit-enumerated      0x800201D1
%IMP%   VARIABLE    __control_opts
**********************************************************************
*/
VARIABLE    __control_opts_spid
{
    LABEL           [control_opts_label] ;
    HELP            [control_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,    [bypass_enable],         [bypass_enable_help] },
        { 0x0002,    [sp_pv_track_man],       [sp_pv_track_man_help] },
        { 0x0004,    [sp_pv_track_rout],      [sp_pv_track_rout_help] },
        { 0x0008,    [sp_pv_track_lo],        [sp_pv_track_lo_help] },
        { 0x0010,    [sp_track_retain],       [sp_track_retain_help] },
        { 0x0020,    [direct_acting],         [direct_acting_help] },
        { 0x0080,    [track_enable],          [track_enable_help] },
        { 0x0100,    [track_in_man],          [track_in_man_help] },
        { 0x0200,    [pv_for_bkcal_out],      [pv_for_bkcal_out_help] },
        { 0x0400,    [act_on_ir],             [act_on_ir_help] },
        { 0x0800,    [bkcalout_with_in1],     [bkcalout_with_in1_help] },
        { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] },
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }


    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_ai          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_ai           bit-enumerated      0x800201D2
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_ai
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_IO_OPTS_AI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_ao          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_ao           bit-enumerated      0x800201D3
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_ao
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_cao          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_cao           bit-enumerated      0x800201D4
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_cao
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,   [io_invert],              [io_invert_help] },
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },
/****** { 0x0004,   [io_reserved],            [io_reserved_help] },        ******/
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] },
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] }
/****** { 0x0800,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x1000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x2000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x4000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x8000,   [io_reserved],            [io_reserved_help] },        ******/
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_cdo          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_cdo           bit-enumerated      0x800201D5
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_cdo
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,   [io_invert],              [io_invert_help] },
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] }
/****** { 0x0004,   [io_reserved],            [io_reserved_help] },        ******/
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] }
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] }
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] }
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] }
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] }
/****** { 0x0800,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x1000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x2000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x4000,   [io_reserved],            [io_reserved_help] },        ******/
/****** { 0x8000,   [io_reserved],            [io_reserved_help] },        ******/
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_di          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_di           bit-enumerated      0x800201D6
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_di
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_IO_OPTS_DI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_do          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_do           bit-enumerated      0x800201D7
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_do
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
         __FF_IO_OPTS_DO_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_pi          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_pi           bit-enumerated      0x800201D8
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_pi
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        __FF_IO_OPTS_PI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_opts_spid          FF-891-1.2,  5.4.2.1
%SYM%   member      IO_OPTS             parameter           0xC0010106
%SYM%   member      VL_IO_OPTS          variable-list       0xC0010107
%TXT%   variable    __io_opts_spid           bit-enumerated      0x800201D9
%IMP%   VARIABLE    __io_opts
**********************************************************************
*/
VARIABLE    __io_opts_spid
{
    LABEL           [io_opts_label] ;
    HELP            [io_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
           __FF_IO_OPTS_SPID_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_aal
**********************************************************************
*/
VARIABLE    __ack_option_aal
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_aal
**********************************************************************
*/
VARIABLE    __current_summary_aal
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_aal
**********************************************************************
*/
VARIABLE    __unacked_summary_aal
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_aal
**********************************************************************
*/
VARIABLE    __unreported_summary_aal
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_aal
**********************************************************************
*/
VARIABLE    __disabled_summary_aal
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_1,
        _DISAB_SUMM_2,
        _DISAB_SUMM_3,
        _DISAB_SUMM_4,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_ai
**********************************************************************
*/
VARIABLE    __ack_option_ai
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_ai
**********************************************************************
*/
VARIABLE    __current_summary_ai
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_ai
**********************************************************************
*/
VARIABLE    __unacked_summary_ai
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_ai
**********************************************************************
*/
VARIABLE    __unreported_summary_ai
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_ai
**********************************************************************
*/
VARIABLE    __disabled_summary_ai
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_1,
        _DISAB_SUMM_2,
        _DISAB_SUMM_3,
        _DISAB_SUMM_4,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_dal
**********************************************************************
*/
VARIABLE    __ack_option_dal
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_0,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_dal
**********************************************************************
*/
VARIABLE    __current_summary_dal
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_0,
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7,
        _CURR_SUMM_8,
	_CURR_SUMM_9,
	_CURR_SUMM_10,
        _CURR_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_dal
**********************************************************************
*/
VARIABLE    __unacked_summary_dal
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_0,
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10,
        _UNACK_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_dal
**********************************************************************
*/
VARIABLE    __unreported_summary_dal
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_0,
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10,
        _UNREP_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_dal
**********************************************************************
*/
VARIABLE    __disabled_summary_dal
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_0,
        _DISAB_SUMM_5,
        _DISAB_SUMM_6,
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10,
        _DISAB_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_dc
**********************************************************************
*/
VARIABLE    __ack_option_dc
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__current_summary_dc
**********************************************************************
*/
VARIABLE    __current_summary_dc
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_7,
        _CURR_SUMM_8,
        _CURR_SUMM_9,
        _CURR_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_dc
**********************************************************************
*/
VARIABLE    __unacked_summary_dc
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_dc
**********************************************************************
*/
VARIABLE    __unreported_summary_dc
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_dc
**********************************************************************
*/
VARIABLE    __disabled_summary_dc
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_di
**********************************************************************
*/
VARIABLE    __ack_option_di
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_0,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_di
**********************************************************************
*/
VARIABLE    __current_summary_di
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_0,
        _CURR_SUMM_7,
        _CURR_SUMM_8,
	_CURR_SUMM_9,
	_CURR_SUMM_10,
        _CURR_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_di
**********************************************************************
*/
VARIABLE    __unacked_summary_di
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_0,
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10,
        _UNACK_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_di
**********************************************************************
*/
VARIABLE    __unreported_summary_di
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_0,
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10,
        _UNREP_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_di
**********************************************************************
*/
VARIABLE    __disabled_summary_di
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_0,
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10,
        _DISAB_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_ft
**********************************************************************
*/
VARIABLE    __ack_option_ft
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_2,
	_ACK_OPT_4,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_ft
**********************************************************************
*/
VARIABLE    __current_summary_ft
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_2,
        _CURR_SUMM_4,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_ft
**********************************************************************
*/
VARIABLE    __unacked_summary_ft
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_2,
        _UNACK_SUMM_4,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_ft
**********************************************************************
*/
VARIABLE    __unreported_summary_ft
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_2,
        _UNREP_SUMM_4,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_ft
**********************************************************************
*/
VARIABLE    __disabled_summary_ft
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_2,
        _DISAB_SUMM_4,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_ml
**********************************************************************
*/
VARIABLE    __ack_option_ml
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_ml
**********************************************************************
*/
VARIABLE    __current_summary_ml
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_ml
**********************************************************************
*/
VARIABLE    __unacked_summary_ml
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_ml
**********************************************************************
*/
VARIABLE    __unreported_summary_ml
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_ml
**********************************************************************
*/
VARIABLE    __disabled_summary_ml
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_1,
        _DISAB_SUMM_2,
        _DISAB_SUMM_3,
        _DISAB_SUMM_4,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_pd
**********************************************************************
*/
VARIABLE    __ack_option_pd
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_pd
**********************************************************************
*/
VARIABLE    __current_summary_pd
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_pd
**********************************************************************
*/
VARIABLE    __unacked_summary_pd
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_pd
**********************************************************************
*/
VARIABLE    __unreported_summary_pd
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_pd
**********************************************************************
*/
VARIABLE    __disabled_summary_pd
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_pi
**********************************************************************
*/
VARIABLE    __ack_option_pi
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
     _DISAB_SUMM_7,
     _DISAB_SUMM_8,
     _DISAB_SUMM_9,
     _DISAB_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_pi
**********************************************************************
*/
VARIABLE    __current_summary_pi
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_7,
        _CURR_SUMM_8,
        _CURR_SUMM_9,
        _CURR_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_pi
**********************************************************************
*/
VARIABLE    __unacked_summary_pi
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_pi
**********************************************************************
*/
VARIABLE    __unreported_summary_pi
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_pi
**********************************************************************
*/
VARIABLE    __disabled_summary_pi
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_pid
**********************************************************************
*/
VARIABLE    __ack_option_pid
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_pid
**********************************************************************
*/
VARIABLE    __current_summary_pid
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_pid
**********************************************************************
*/
VARIABLE    __unacked_summary_pid
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_pid
**********************************************************************
*/
VARIABLE    __unreported_summary_pid
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_pid
**********************************************************************
*/
VARIABLE    __disabled_summary_pid
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_1,
        _DISAB_SUMM_2,
        _DISAB_SUMM_3,
        _DISAB_SUMM_4,
        _DISAB_SUMM_5,
        _DISAB_SUMM_6,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_ra
**********************************************************************
*/
VARIABLE    __ack_option_ra
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_1,
	_ACK_OPT_2,
	_ACK_OPT_3,
	_ACK_OPT_4,
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_ra
**********************************************************************
*/
VARIABLE    __current_summary_ra
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_1,
        _CURR_SUMM_2,
        _CURR_SUMM_3,
        _CURR_SUMM_4,
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_ra
**********************************************************************
*/
VARIABLE    __unacked_summary_ra
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_1,
        _UNACK_SUMM_2,
        _UNACK_SUMM_3,
        _UNACK_SUMM_4,
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_ra
**********************************************************************
*/
VARIABLE    __unreported_summary_ra
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_1,
        _UNREP_SUMM_2,
        _UNREP_SUMM_3,
        _UNREP_SUMM_4,
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_ra
**********************************************************************
*/
VARIABLE    __disabled_summary_ra
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
     _DISAB_SUMM_1,
     _DISAB_SUMM_2,
     _DISAB_SUMM_3,
     _DISAB_SUMM_4,
     _DISAB_SUMM_5,
     _DISAB_SUMM_6,
     _DISAB_SUMM_7
   }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_res
**********************************************************************
*/
VARIABLE    __ack_option_res
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_0,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_res
**********************************************************************
*/
VARIABLE    __current_summary_res
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_0,
        _CURR_SUMM_7,
        _CURR_SUMM_8,
	_CURR_SUMM_9,
	_CURR_SUMM_10,
        _CURR_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_res
**********************************************************************
*/
VARIABLE    __unacked_summary_res
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_0,
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10,
        _UNACK_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_res
**********************************************************************
*/
VARIABLE    __unreported_summary_res
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_0,
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10,
        _UNREP_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_res
**********************************************************************
*/
VARIABLE    __disabled_summary_res
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_0,
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10,
        _DISAB_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_res2
**********************************************************************
*/
VARIABLE    __ack_option_res2
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_0,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_res2
**********************************************************************
*/
VARIABLE    __current_summary_res2
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_0,
        _CURR_SUMM_7,
        _CURR_SUMM_8,
	_CURR_SUMM_9,
	_CURR_SUMM_10,
        _CURR_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_res2
**********************************************************************
*/
VARIABLE    __unacked_summary_res2
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_0,
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10,
        _UNACK_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_res2
**********************************************************************
*/
VARIABLE    __unreported_summary_res2
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_0,
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10,
        _UNREP_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_res2
**********************************************************************
*/
VARIABLE    __disabled_summary_res2
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_0,
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10,
        _DISAB_SUMM_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_spg
**********************************************************************
*/
VARIABLE    __ack_option_spg
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_5,
	_ACK_OPT_6,
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_spg
**********************************************************************
*/
VARIABLE    __current_summary_spg
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_5,
        _CURR_SUMM_6,
        _CURR_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_spg
**********************************************************************
*/
VARIABLE    __unacked_summary_spg
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_5,
        _UNACK_SUMM_6,
        _UNACK_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_spg
**********************************************************************
*/
VARIABLE    __unreported_summary_spg
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_5,
        _UNREP_SUMM_6,
        _UNREP_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_spg
**********************************************************************
*/
VARIABLE    __disabled_summary_spg
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_5,
        _DISAB_SUMM_6,
        _DISAB_SUMM_7
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ack_option_spid
**********************************************************************
*/
VARIABLE    __ack_option_spid
{
    LABEL           [ack_option_label] ;
    HELP            [ack_option_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
	_ACK_OPT_7,
	_ACK_OPT_8,
	_ACK_OPT_9,
	_ACK_OPT_10,
	_ACK_OPT_11
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__current_summary_spid
**********************************************************************
*/
VARIABLE    __current_summary_spid
{
    LABEL           [current_summary_label] ;
    HELP            [current_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _CURR_SUMM_7,
        _CURR_SUMM_8,
        _CURR_SUMM_9,
        _CURR_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unacked_summary_spid
**********************************************************************
*/
VARIABLE    __unacked_summary_spid
{
    LABEL           [unacked_summary_label] ;
    HELP            [unacked_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNACK_SUMM_7,
        _UNACK_SUMM_8,
        _UNACK_SUMM_9,
        _UNACK_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__unreported_summary_spid
**********************************************************************
*/
VARIABLE    __unreported_summary_spid
{
    LABEL           [unreported_summary_label] ;
    HELP            [unreported_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _UNREP_SUMM_7,
        _UNREP_SUMM_8,
        _UNREP_SUMM_9,
        _UNREP_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__disabled_summary_spid
**********************************************************************
*/
VARIABLE    __disabled_summary_spid
{
    LABEL           [disabled_summary_label] ;
    HELP            [disabled_summary_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (2)
    {
        _DISAB_SUMM_7,
        _DISAB_SUMM_8,
        _DISAB_SUMM_9,
        _DISAB_SUMM_10
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_aal
**********************************************************************
*/
RECORD      __alarm_sum_aal
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_aal ;
        UNACKNOWLEDGED,      __unacked_summary_aal ;
        UNREPORTED,          __unreported_summary_aal ;
        DISABLED,            __disabled_summary_aal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_ai
**********************************************************************
*/
RECORD      __alarm_sum_ai
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_ai ;
        UNACKNOWLEDGED,      __unacked_summary_ai ;
        UNREPORTED,          __unreported_summary_ai ;
        DISABLED,            __disabled_summary_ai ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_dal
**********************************************************************
*/
RECORD      __alarm_sum_dal
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_dal ;
        UNACKNOWLEDGED,      __unacked_summary_dal ;
        UNREPORTED,          __unreported_summary_dal ;
        DISABLED,            __disabled_summary_dal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_di
**********************************************************************
*/
RECORD      __alarm_sum_dc
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_dc ;
        UNACKNOWLEDGED,      __unacked_summary_dc ;
        UNREPORTED,          __unreported_summary_dc ;
        DISABLED,            __disabled_summary_dc ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_di
**********************************************************************
*/
RECORD      __alarm_sum_di
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_di ;
        UNACKNOWLEDGED,      __unacked_summary_di ;
        UNREPORTED,          __unreported_summary_di ;
        DISABLED,            __disabled_summary_di ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_ml
**********************************************************************
*/
RECORD      __alarm_sum_ml
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_ml ;
        UNACKNOWLEDGED,      __unacked_summary_ml ;
        UNREPORTED,          __unreported_summary_ml ;
        DISABLED,            __disabled_summary_ml ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_pd
**********************************************************************
*/
RECORD      __alarm_sum_pd
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_pd ;
        UNACKNOWLEDGED,      __unacked_summary_pd ;
        UNREPORTED,          __unreported_summary_pd ;
        DISABLED,            __disabled_summary_pd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_pi
**********************************************************************
*/
RECORD      __alarm_sum_pi
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_pi ;
        UNACKNOWLEDGED,      __unacked_summary_pi ;
        UNREPORTED,          __unreported_summary_pi ;
        DISABLED,            __disabled_summary_pi ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_pid
**********************************************************************
*/
RECORD      __alarm_sum_pid
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_pid ;
        UNACKNOWLEDGED,      __unacked_summary_pid ;
        UNREPORTED,          __unreported_summary_pid ;
        DISABLED,            __disabled_summary_pid ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_ra
**********************************************************************
*/
RECORD      __alarm_sum_ra
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_ra ;
        UNACKNOWLEDGED,      __unacked_summary_ra ;
        UNREPORTED,          __unreported_summary_ra ;
        DISABLED,            __disabled_summary_ra ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_res
**********************************************************************
*/
RECORD      __alarm_sum_res
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_res ;
        UNACKNOWLEDGED,      __unacked_summary_res ;
        UNREPORTED,          __unreported_summary_res ;
        DISABLED,            __disabled_summary_res ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_res
**********************************************************************
*/
RECORD      __alarm_sum_res2
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_res2 ;
        UNACKNOWLEDGED,      __unacked_summary_res2 ;
        UNREPORTED,          __unreported_summary_res2 ;
        DISABLED,            __disabled_summary_res2 ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_spg
**********************************************************************
*/
RECORD      __alarm_sum_spg
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_spg ;
        UNACKNOWLEDGED,      __unacked_summary_spg ;
        UNREPORTED,          __unreported_summary_spg ;
        DISABLED,            __disabled_summary_spg ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_spid
**********************************************************************
*/
RECORD      __alarm_sum_spid
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_spid ;
        UNACKNOWLEDGED,      __unacked_summary_spid ;
        UNREPORTED,          __unreported_summary_spid ;
        DISABLED,            __disabled_summary_spid ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__alarm_sum_ft
**********************************************************************
*/
RECORD      __alarm_sum_ft
{
    LABEL           [alarm_sum_label] ;
    HELP            [alarm_sum_help] ;
    MEMBERS
    {
        CURRENT,             __current_summary_ft ;
        UNACKNOWLEDGED,      __unacked_summary_ft ;
        UNREPORTED,          __unreported_summary_ft ;
        DISABLED,            __disabled_summary_ft ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
VIEW_*
%SYM%   member      VIEW_1              parameter-list          0xC00101A0
%SYM%   member      VIEW_2              parameter-list          0xC00101A1
%SYM%   member      VIEW_3              parameter-list          0xC00101A2
%SYM%   member      VIEW_3_2            parameter-list      0xC00101A7
%SYM%   member      VIEW_3_3            parameter-list      0xC00101A8
%SYM%   member      VIEW_3_4            parameter-list      0xC00101A9
%SYM%   member      VIEW_3_5            parameter-list      0xC00101AA
%SYM%   member      VIEW_3_6            parameter-list      0xC00101AB
%SYM%   member      VIEW_3_7            parameter-list      0xC00101AC
%SYM%   member      VIEW_3_8            parameter-list      0xC00101AD
%SYM%   member      VIEW_3_9            parameter-list      0xC00101AE
%SYM%   member      VIEW_3_10           parameter-list      0xC00101AF
%SYM%   member      VIEW_3_11           parameter-list      0xC00101A0
%SYM%   member      VIEW_3_12           parameter-list      0xC00101A1
%SYM%   member      VIEW_3_13           parameter-list      0xC00101B2
%SYM%   member      VIEW_3_14           parameter-list      0xC00101B3
%SYM%   member      VIEW_3_15           parameter-list      0xC00101B4
%SYM%   member      VIEW_3_16           parameter-list      0xC00101B5
%SYM%   member      VIEW_3_17           parameter-list      0xC00101B6
%SYM%   member      VIEW_4              parameter-list      0xC00101A3
%SYM%   member      VIEW_4_2            parameter-list      0xC00101B7
%SYM%   member      VIEW_4_3            parameter-list      0xC00101B8
%SYM%   member      VIEW_4_4            parameter-list      0xC00101B9
%SYM%   member      VIEW_4_5            parameter-list      0xC00101BA
%SYM%   member      VIEW_4_6            parameter-list      0xC00101BB
%SYM%   member      VIEW_4_7            parameter-list      0xC00101BC
%SYM%   member      VIEW_4_8            parameter-list      0xC00101BD
%SYM%   member      VIEW_4_9            parameter-list      0xC00101BE
%SYM%   member      VIEW_4_10           parameter-list      0xC00101BF
%SYM%   member      VIEW_4_11           parameter-list      0xC00101C0
%SYM%   member      VIEW_4_12           parameter-list      0xC00101C1
%SYM%   member      VIEW_4_13           parameter-list      0xC00101C2
%SYM%   member      VIEW_4_14           parameter-list      0xC00101C3
%SYM%   member      VIEW_4_15           parameter-list      0xC00101C4
%SYM%   member      VIEW_4_16           parameter-list      0xC00101C5
%SYM%   member      VIEW_4_17           parameter-list      0xC00101C6
**********************************************************************
*/

/*
**********************************************************************
__itk_ver
%SYM%   member      ITK_VER             parameter           0xC0010195
%SYM%   member      VL_ITK_VER          variable-list       0xC0010123
%TXT%   variable    __itk_ver           unsigned            0x800201B0
%IMP%   VARIABLE    __itk_ver
**********************************************************************
*/
VARIABLE    __itk_ver
{
    LABEL           [itk_ver_label] ;
    HELP            [itk_ver_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__algorithm_sel
%SYM%   member      ALGORITHM_SEL	parameter           0xC0010B44
%SYM%   member      VL_ALGORITHM_SEL	variable-list       0xC0010B45
%TXT%   variable    __algorithm_sel	unsigned            0x80020B45
%IMP%   VARIABLE    __algorithm_sel
**********************************************************************
*/
VARIABLE    __algorithm_sel
{
    LABEL           [algorithm_sel_label] ;
    HELP            [algorithm_sel_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__pi_pointer
%SYM%   member      PI_POINTER		parameter           0xC0020840
%SYM%   member      VL_PI_POINTER	variable-list       0xC0010B24
%TXT%   variable    __pi_pointer	unsigned            0x80020840
%IMP%   VARIABLE    __pi_pointer
**********************************************************************
*/
VARIABLE    __pi_pointer
{
    LABEL           [pi_pointer_label] ;
    HELP            [pi_pointer_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__contents_rev
%SYM%   member      CONTENTS_REV	parameter           0xC0020841
%SYM%   member      VL_CONTENTS_REV	variable-list       0xC0010B25
%TXT%   variable    __contents_rev	unsigned            0x80020841
%IMP%   VARIABLE    __contents_rev
**********************************************************************
*/
VARIABLE    __contents_rev
{
    LABEL           [contents_rev_label] ;
    HELP            [contents_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fdd_locator
%SYM%   member      FDD_LOCATOR		parameter           0xC0020843
%SYM%   member      VL_FDD_LOCATOR	variable-list       0xC0010B26
%TXT%   variable    __fdd_locator_elem	unsigned            0x80020844
%TXT%   array       __fdd_locator	            	    0x80020843
%IMP%   ARRAY       __fdd_locator
**********************************************************************
*/
VARIABLE    __fdd_locator_elem
{
    LABEL           [fdd_locator_elem_label] ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CLASS           CONTAINED ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

ARRAY    __fdd_locator
{
    LABEL               [fdd_locator_label] ;
    HELP                [fdd_locator_help] ;
    TYPE                __fdd_locator_elem ;
    NUMBER_OF_ELEMENTS  3 ;
}

/*
**********************************************************************
__fcf_locator
%SYM%   member      FCF_LOCATOR		parameter           0xC0020845
%SYM%   member      VL_FCF_LOCATOR	variable-list       0xC0010B27
%TXT%   variable    __fcf_locator_elem	unsigned            0x80020844
%TXT%   array       __fcf_locator	            	    0x80020843
%IMP%   ARRAY       __fcf_locator
**********************************************************************
*/
VARIABLE    __fcf_locator_elem
{
    LABEL           [fcf_locator_elem_label] ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CLASS           CONTAINED ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

ARRAY    __fcf_locator
{
    LABEL               [fcf_locator_label] ;
    HELP                [fcf_locator_help] ;
    TYPE                __fcf_locator_elem ;
    NUMBER_OF_ELEMENTS  3 ;
}

/*
**********************************************************************
__file_locator
%SYM%   member      FILE_LOCATOR	parameter           0xC0010B46
%SYM%   member      VL_FILE_LOCATOR	variable-list       0xC0010B47
%TXT%   variable    __file_locator_elem	unsigned            0x80020846
%TXT%   array       __file_locator	            	    0x80020847
%IMP%   ARRAY       __file_locator
**********************************************************************
*/
VARIABLE    __file_locator_elem
{
    LABEL           [file_locator_elem_label] ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CLASS           CONTAINED ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

ARRAY    __file_locator
{
    LABEL               [file_locator_label] ;
    HELP                [file_locator_help] ;
    TYPE                __file_locator_elem ;
    NUMBER_OF_ELEMENTS  3 ;
}

/*
**********************************************************************
__file_rev
%SYM%   member      FILE_REV		parameter           0xC0010B48
%SYM%   member      VL_FILE_REV		variable-list       0xC0010B49
%TXT%   variable    __file_rev		unsigned            0x80020848
%IMP%   VARIABLE    __file_rev
**********************************************************************
*/
VARIABLE    __file_rev
{
    LABEL           [file_rev_label] ;
    HELP            [file_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__capability_lev
**********************************************************************
*/
VARIABLE    __capability_lev
{
    LABEL           [capability_level_label] ;
    HELP            [capability_level_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        {0x00,  [capability_level_not_supported], [capability_level_not_supported_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*** Standard Diagnostics FF-912 ***/

VARIABLE    __resource_directory_elem
{
    LABEL           [resource_directory_elem_label] ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CLASS           CONTAINED ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

/*
**********************************************************************
__resource_directory
%SYM%   member      RESOURCE_DIRECTORY      parameter   0xC0010B07
%TXT%   array      __resource_directory                 0x80020B0C
%IMP%   ARRAY      __resource_directory
%IMP%     VARIABLE    __resource_directory_entry
**********************************************************************
*/
ARRAY  __resource_directory
  {
     LABEL    [resource_directory_label] ;
     HELP     [resource_directory_help] ;
     TYPE     __resource_directory_elem;
     NUMBER_OF_ELEMENTS 1;
  }
  
/*
**********************************************************************
__resource_type   FF-912 PS 2.0
%SYM%   member      RESOURCE_TYPE      parameter       0xC0010B08
%SYM%   member      VL_RESOURCE_TYPE   variable-list   0xC0010B0A
%TXT%   variable    __resource_type    enumerated      0x80020B0D
%IMP%   VARIABLE    __resource_type
**********************************************************************
*/
VARIABLE    __resource_type
{
    LABEL           [resource_type_label] ;
    HELP            [resource_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
        { 100,  [field_diagnostics_label],  [field_diagnostics_help]        },
        { 65535,[other],            [other_help]            }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_ver   FF-912 PS 3.0.5
%SYM%   member      SD_VER      parameter       0xC0010B08
%SYM%   member      VL_SD_VER   variable-list   0xC0010B0A
%TXT%   variable    __fd_ver    enumerated      0x80020B0D
%IMP%   VARIABLE    __fd_ver
**********************************************************************
*/
VARIABLE    __fd_ver
{
    LABEL           [fd_ver_label] ;
    HELP            [fd_ver_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_check_active          FF-912 PS1.02
%SYM%   member      CHECK_ACTIVE         record           0x 
%SYM%   member      VL_CHECK_ACTIVE      variable-list       0x
%TXT%   variable    __fd_check_active       bit-enumerated      0x 
%IMP%   VARIABLE    __fd_check_active
**********************************************************************
*/
VARIABLE    __fd_check_active
{
    LABEL           [fd_check_active_label] ;
    HELP            [fd_check_active_help] ;
    CLASS           CONTAINED ;
     TYPE            BIT_ENUMERATED (4)
     {
        __FD_BITENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sub_code_32              FF-912 DPS 3.0.5
%SYM%   member      SUB_CODE_32            record              0xC0010029
%TXT%   variable    __sub_code_32          enumerated          0x80020029
%IMP%   VARIABLE    __sub_code_32
**********************************************************************
*/
VARIABLE    __sub_code_32
{
    LABEL           [sub_code] ;
    HELP            [sub_code_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM ;
    TYPE            UNSIGNED_INTEGER (4);
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__value_16
%SYM%   member      VALUE               record              0xC0010012
%TXT%   variable    __value_16    enumerated          0x8002002C
%IMP%   VARIABLE    __value_16
**********************************************************************
*/
VARIABLE    __value_16
{
    LABEL           [value_16_label] ;
    HELP            [value_16_help] ;
    CLASS           CONTAINED & DYNAMIC & ALARM;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_check_alm        (DS-87)
%SYM%   member      FD_CHECK_ALM            parameter           0xC0010B2A
%SYM%   member      VL_FD_CHECK_ALM         variable-list       0x
%TXT%   record      __fd_check_alm                              0x80020B2A
%IMP%   RECORD      __fd_check_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __fd_check_alm
{
    LABEL           [fd_check_alm_label] ;
    HELP            [fd_check_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code_32 ;
        VALUE,           __alm_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_check_map          FF-912 PS1.02
%SYM%   member      FD_CHECK_MAP         parameter              0x
%SYM%   member      VL_FD_CHECK_MAP      variable-list       0x
%TXT%   variable    __fd_check_enable       bit-enumerated      0x
%IMP%   VARIABLE    __fd_check_enable
**********************************************************************
*/
VARIABLE    __fd_check_map
{
    LABEL           [fd_check_map_label] ;
    HELP            [fd_check_map_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}



/*
**********************************************************************
__fd_check_mask          FF-912 PS1.02
%SYM%   member      FD_CHECK_MASK         parameter           0x
%SYM%   member      VL_FD_CHECK_MASK      variable-list       0x
%TXT%   variable    __fd_check_mask       bit-enumerated      0x
%IMP%   VARIABLE    __fd_check_mask
**********************************************************************
*/
VARIABLE    __fd_check_mask
{
    LABEL           [fd_check_mask_label] ;
    HELP            [fd_check_mask_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_check_pri
%SYM%   member      FD_CHECK_PRI            parameter           0x
%SYM%   member      VL_FD_CHECK_PRI         variable-list       0x
%TXT%   variable    __fd_check_pri          unsigned            0x
%IMP%   VARIABLE    __fd_check_pri
**********************************************************************
*/
VARIABLE    __fd_check_pri
{
    LABEL           [fd_check_pri_label] ;
    HELP            [fd_check_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_fail_active          FF-912-PS2.2
%SYM%   member      FD_FAIL_ACTIVE         parameter           0x
%SYM%   member      VL_FD_FAIL_ACTIVE      variable-list       0x
%TXT%   variable    __fd_fail_diag_active       bit-enumerated     0x
%IMP%   VARIABLE    __fd_fail_diag_active
**********************************************************************
*/
VARIABLE    __fd_fail_active
{
    LABEL           [fd_fail_active_label] ;
    HELP            [fd_fail_active_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_fail_alm        (DS-87)
%SYM%   member      FD_FAIL_ALM            parameter           0x
%SYM%   member      VL_FD_FAIL_ALM         variable-list       0x
%TXT%   record      __fd_fail_alm                              0x
%IMP%   RECORD      __fd_fail_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code_32
%IMP%       VARIABLE    __value_16
**********************************************************************
*/
RECORD      __fd_fail_alm
{
    LABEL           [fd_fail_alm_label] ;
    HELP            [fd_fail_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code_32 ;
        VALUE,           __alm_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_fail_map          FF-912 PS1.02
%SYM%   member      FD_FAIL_MAP         parameter           0x
%SYM%   member      VL_FD_FAIL_MAP      variable-list       0x
%TXT%   variable    __fd_fail_map       bit-enumerated     0x
%IMP%   VARIABLE    __fd_fail_map
**********************************************************************
*/
VARIABLE    __fd_fail_map
{
    LABEL           [fd_fail_map_label] ;
    HELP            [fd_fail_map_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}



/*
**********************************************************************
__fd_fail_mask          FF-912-PS2.2
%SYM%   member      FD_FAIL_MASK         parameter           0x
%SYM%   member      VL_FD_FAIL_MASK      variable-list       0x
%TXT%   variable    __fd_fail_mask      bit-enumerated      0x
%IMP%   VARIABLE    __fd_fail_mask
**********************************************************************
*/
VARIABLE    __fd_fail_mask
{
    LABEL           [fd_fail_mask_label] ;
    HELP            [fd_fail_mask_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_fail_pri
%SYM%   member      FD_FAIL_PRI            parameter           0x
%SYM%   member      VL_FD_FAIL_PRI         variable-list       0x
%TXT%   variable    __fd_fail_pri          unsigned            0x
%IMP%   VARIABLE    __fd_fail_pri
**********************************************************************
*/
VARIABLE    __fd_fail_pri
{
    LABEL           [fd_fail_pri_label] ;
    HELP            [fd_fail_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_maint_active          FF-912-PS2.2
%SYM%   member      FD_MAINT_ACTIVE         parameter           0x
%SYM%   member      VL_FD_MAINT_ACTIVE      variable-list       0x
%TXT%   variable    __fd_maint_active       bit-enumerated      0x
%IMP%   VARIABLE    __fd_maint_active
**********************************************************************
*/
VARIABLE    __fd_maint_active
{
    LABEL           [fd_maint_active_label] ;
    HELP            [fd_maint_active_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_maint_alm        (DS-87)
%SYM%   member      FD_MAINT_ALM            parameter           0x
%SYM%   member      VL_FD_MAINT_ALM         variable-list       0x
%TXT%   record      __fd_maint_alm                              0x
%IMP%   RECORD      __fd_maint_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __fd_maint_alm
{
    LABEL           [fd_maint_alm_label] ;
    HELP            [fd_maint_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code_32 ;
        VALUE,           __alm_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_maint_map           FF-912 PS1.02
%SYM%   member      FD_MAINT_MAP         parameter           0x
%SYM%   member      VL_FD_MAINT_MAP      variable-list       0x
%TXT%   variable    __fd_maint_map       bit-enumerated      0x
%IMP%   VARIABLE    __fd_maint_map
**********************************************************************
*/
VARIABLE    __fd_maint_map
{
    LABEL           [fd_maint_map_label] ;
    HELP            [fd_maint_map_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_maint_mask          FF-912-PS2.2
%SYM%   member      FD_MAINT_MASK         parameter           0x
%SYM%   member      VL_FD_MAINT_MASK      variable-list       0x
%TXT%   variable    __maint_mask       bit-enumerated      0x
%IMP%   VARIABLE    __maint_mask
**********************************************************************
*/
VARIABLE    __fd_maint_mask
{
    LABEL           [fd_maint_mask_label] ;
    HELP            [fd_maint_mask_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_maint_pri
%SYM%   member      FD_MAINT_PRI            parameter           0x
%SYM%   member      VL_FD_MAINT_PRI         variable-list       0x
%TXT%   variable    __fd_maint_pri          unsigned            0x
%IMP%   VARIABLE    __fd_maint_pri
**********************************************************************
*/
VARIABLE    __fd_maint_pri
{
    LABEL           [fd_maint_pri_label] ;
    HELP            [fd_maint_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_offspec_active          FF-912-PS2.2
%SYM%   member      FD_OFFSPEC_ACTIVE         parameter           0x
%SYM%   member      VL_FD_OFFSPEC_ACTIVE      variable-list       0x
%TXT%   variable    __fd_offspec_active       bit-enumerated      0x
%IMP%   VARIABLE    __fd_offspec_active
**********************************************************************
*/
VARIABLE    __fd_offspec_active
{
    LABEL           [fd_offspec_active_label] ;
    HELP            [fd_offspec_active_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_offspec_alm        (DS-87)
%SYM%   member      FD_OFFSPEC_ALM            parameter           0x
%SYM%   member      VL_FD_OFFSPEC_ALM         variable-list       0x
%TXT%   record      __fd_offspec_alm                              0x
%IMP%   RECORD      __fd_offspec_alm
%IMP%       VARIABLE    __unacknowledged
%IMP%       VARIABLE    __alarm_state
%IMP%       VARIABLE    __time_stamp
%IMP%       VARIABLE    __sub_code
%IMP%       VARIABLE    __discrete_value
**********************************************************************
*/
RECORD      __fd_offspec_alm
{
    LABEL           [fd_offspec_alm_label] ;
    HELP            [fd_offspec_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code_32 ;
        VALUE,           __alm_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_offspec_map          FF-912 PS1.02
%SYM%   member      FD_OFFSPEC_MAP         parameter           0x
%SYM%   member      VL_FD_OFFSPEC_MAP      variable-list       0x
%TXT%   variable    __fd_offspec_map       bit-enumerated      0x
%IMP%   VARIABLE    __fd_offspec_map
**********************************************************************
*/
VARIABLE    __fd_offspec_map
{
    LABEL           [fd_offspec_map_label] ;
    HELP            [fd_offspec_map_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}



/*
**********************************************************************
__fd_offspec_mask          FF-912-PS2.2
%SYM%   member      FD_OFFSPEC_MASK         parameter           0x
%SYM%   member      VL_FD_OFFSPEC_MASK      variable-list       0x
%TXT%   variable    __fd_offspec_mask       bit-enumerated      0x
%IMP%   VARIABLE    __fd_offspec_mask
**********************************************************************
*/
VARIABLE    __fd_offspec_mask
{
    LABEL           [fd_offspec_mask_label] ;
    HELP            [fd_offspec_mask_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            BIT_ENUMERATED (4)
    {
        __FD_BITENUMS   
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_offspec_pri
%SYM%   member      FD_OFFSPEC_PRI            parameter           0x
%SYM%   member      VL_FD_OFFSPEC_PRI         variable-list       0x
%TXT%   variable    __fd_offspec_pri          unsigned            0x
%IMP%   VARIABLE    __fd_offspec_pri
**********************************************************************
*/
VARIABLE    __fd_offspec_pri
{
    LABEL           [fd_offspec_pri_label] ;
    HELP            [fd_offspec_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__set_check
%SYM%   member      SET_CHECK              parameter           0xC0010B09
%SYM%   member      VL_SET_CHECK           variable-list       0x
%TXT%   variable    __set_check           enumerated           0x80020B0E
%IMP%   VARIABLE    __set_check
**********************************************************************
*/
/*
VARIABLE    __set_check
{
    LABEL           [set_check_label] ;
    HELP            [set_check_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1) 
    {
        { 1,  [off_label],  [off_help]        },
        { 2,  [set_label],  [set_help]         }
    }
    HANDLING        READ ;
}
*/

/*
**********************************************************************
__clr_check
%SYM%   member      CLR_CHECK              parameter           0xC0010AF6
%SYM%   member      VL_CLR_CHECK           variable-list       0x
%TXT%   variable    __clr_check            enumerated          0x80020AFB
%IMP%   VARIABLE    __clr_check
**********************************************************************
*/
/*
VARIABLE    __clr_check
{
    LABEL           [clr_check_label] ;
    HELP            [clr_check_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1) 
    {
        { 1,  [off_label],  [off_help]        },
        { 2,  [clear_label],  [clear_help]         }
    }
    HANDLING        READ ;
}
*/

/*
**********************************************************************
__check_state
%SYM%   member      CHECK_STATE              parameter           0xC0010AF5
%SYM%   member      VL_CHECK_STATE           variable-list       0x
%TXT%   variable    __check_state            enumerated          0x80020AFA
%IMP%   VARIABLE    __check_state
**********************************************************************
*/
/*
VARIABLE    __check_state
{
    LABEL           [check_state_label] ;
    HELP            [check_state_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1) 
    {
        { 1,  [clear_label],  [clear_help]        },
        { 2,  [active_label],  [active_help]         }
    }
    HANDLING        READ ;
}
*/

/*
**********************************************************************
__fd_recommended_action
%SYM%   member      FD_RECOMMENDED_ACTION              parameter           0x
%SYM%   member      VL_FD_RECOMMENDED_ACTION           variable-list       0x
%TXT%   variable    __fd_recommended_action            enumerated          0x
%IMP%   VARIABLE    __fd_recommended_action
**********************************************************************
*/
VARIABLE    __fd_recommen_act
{
    LABEL           [fd_recommended_action_label] ;
    HELP            [fd_recommended_action_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2) 
    {
        { 0x00000000,  	[no_act_label],  [no_act_help]        },
        { 0x00000001,   [mfg_specific_label],    [mfg_specific_help]    }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__diagnostic_simulate_value
%TXT%   variable    __diagnostic_simulate_value  bitstring               0x
%IMP%   VARIABLE    __diagnostic_simulate_value
**********************************************************************
*/
VARIABLE    __diagnostic_simulate_value
{
    LABEL           [diagnostic_simulate_value_label] ;
    HELP            [diagnostic_simulate_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BIT_ENUMERATED (4) 
    {
        __FD_BITENUMS   
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__diagnostic_value
%TXT%   variable    __diagnostic_value    bitstring               0x
%IMP%   VARIABLE    __diagnostic_value
**********************************************************************
*/
VARIABLE    __diagnostic_value
{
    LABEL           [diagnostic_value_label] ;
    HELP            [diagnostic_value_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BIT_ENUMERATED(4) 
    {
        __FD_BITENUMS   
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_simulate
%TXT%   record      __fd_simulate                        0x
%IMP%   RECORD      __fd_simulate
%IMP%       VARIABLE    __diagnostic_simulate_value
%IMP%       VARIABLE    __diagnostic_value
%IMP%       VARIABLE    __enable_disable
**********************************************************************
*/
RECORD      __fd_simulate
{
    LABEL           [fd_simulate_label] ;
    HELP            [fd_simulate_help] ;
    MEMBERS
    {
        DIAGNOSTIC_SIMULATE_VALUE,    __diagnostic_simulate_value ;
        DIAGNOSTIC_VALUE,     __diagnostic_value ;
        ENABLE_DISABLE,                __enable_disable ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_extended_active_1
%TXT%   variable    __fd_extended_active_1    bitstring               0x
%IMP%   VARIABLE    __fd_extended_active_1
**********************************************************************
*/
VARIABLE    __fd_extended_active_1
{
    LABEL           [fd_extended_active_label] ;
    HELP            [fd_extended_active_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BIT_ENUMERATED(4) 
    {
        __FD_BITENUMS   
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fd_extended_map_1
%TXT%   variable    __fd_extended_map_1    bitstring               0x
%IMP%   VARIABLE    __fd_extended_map_1
**********************************************************************
*/
VARIABLE    __fd_extended_map_1
{
    LABEL           [fd_extended_map_label] ;
    HELP            [fd_extended_map_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED(4) 
    {
        __FD_BITENUMS   
    }
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*** END Field Diagnostics ***/

/*
**********************************************************************
__compatability_rev
%SYM%   member      COMPATABILITY_REV        parameter		0xC0020863
%SYM%   member      VL_COMPATABILITY_REV     variable-list      0xC0020864
%TXT%   variable    __compatability_rev      unsigned           0x80020F18
%IMP%   VARIABLE    __compatability_rev
**********************************************************************
*/
VARIABLE	__compatability_rev
{
	LABEL	[compatability_rev_label];
	HELP	[compatability_rev_help];
	CLASS	CONTAINED;
	TYPE	UNSIGNED_INTEGER (1);
	CONSTANT_UNIT	[blank];
	HANDLING	READ ;
/*  	RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__software_rev
%SYM%   member      SOFTWARE_REV        parameter	0xC0020865
%TXT%   variable    __software_rev      visiblestring	0x80020B57
%IMP%   VARIABLE    __software_rev
**********************************************************************
*/
VARIABLE	__software_rev
{
	LABEL	[software_rev_label];
	HELP	[software_rev_help];
	CLASS	CONTAINED ;
	TYPE	VISIBLE (32) ;
    	CONSTANT_UNIT   [blank] ;
	HANDLING	READ ;
/*  	RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hardware_rev
%SYM%   member      HARDWARE_REV        parameter	0xC0020866
%TXT%   variable    __hardware_rev      visiblestring	0x80020B58
%IMP%   VARIABLE    __hardware_rev
**********************************************************************
*/
VARIABLE	__hardware_rev
{
	LABEL	[hardware_rev_label];
	HELP	[hardware_rev_help];
	CLASS	CONTAINED ;
	TYPE	VISIBLE (32) ;
    	CONSTANT_UNIT   [blank] ;
	HANDLING	READ ;
/*  	RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__block_err_desc_1_tot   
%SYM%   member     BLOCK_ERR_DESC_1       parameter      0xC0011782
%SYM%   member     VL_BLOCK_ERR_DESC_1   variable-list  0xC0011783
%TXT%   variable     __block_err_desc_1_tot   bit-enumerated  0x80020F1A
%IMP%   VARIABLE     __block_err_desc_1_tot
**********************************************************************
*/
VARIABLE    __block_err_desc_1_tot
{
    LABEL           [block_err_desc];
    HELP            [block_err_desc_help];
    CLASS           CONTAINED & DIAGNOSTIC;
    TYPE            BIT_ENUMERATED (4)
    {
        { 0x00000001,"XD_RANGE units not compatible with OUT_RANGE units","Units must be compatible between XD_RANGE and OUT_RANGE." },
	{ 0x00000010,"XD_RANGE units not equal to channel units","Units must match between Totalizer block and Transducer block." }

    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
