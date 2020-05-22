/*
** @(#)mio_parm.ddl 1.0 2002-06-08
**
** FF common definitions
** Filename: mio_parm.ddl
** Spec revision:   FF-900    FS 1.0  DDL spec
**                  FF-891    FS 1.0  Function Block AP Part 4

** Date of last change: 2002-06-08
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
**  TAB   Revision draft   1998-11-02
**  DAD   Revision 0.9beta 1999-03-04
**  SBM	  Revision 0.91beta 1999-12-01
**     removed __in_1 (duplicated in std_parm), corrected syntax errors.
**	SBM   Revision 1.0    2002-06-08
** MS   ARs 2122 -- 2008.10.07
**
*/

#include "com_tbls.h"
/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __STD_MIO_PARM,
DEVICE_REVISION __STD_MIO_PARM_rel_dev_rev,
DD_REVISION     __STD_MIO_PARM_rel_dd_rev


/*
**********************************************************************
__out_1             (DS-65)
%SYM%   member      OUT_1               parameter
%SYM%   member      VL_OUT_1            variable-list
%TXT%   record      __out_1
%IMP%   RECORD      __out_1
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_1
{
    LABEL           [out_1] ;
    HELP            [out_1_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_2             (DS-65)
%SYM%   member      OUT_2               parameter
%SYM%   member      VL_OUT_2            variable-list
%TXT%   record      __out_2
%IMP%   RECORD      __out_2
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_2
{
    LABEL           [out_2] ;
    HELP            [out_2_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_3             (DS-65)
%SYM%   member      OUT_3               parameter
%SYM%   member      VL_OUT_3            variable-list
%TXT%   record      __out_3
%IMP%   RECORD      __out_3
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_3
{
    LABEL           [out_3] ;
    HELP            [out_3_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_4             (DS-65)
%SYM%   member      OUT_4               parameter
%SYM%   member      VL_OUT_4            variable-list
%TXT%   record      __out_4
%IMP%   RECORD      __out_4
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_4
{
    LABEL           [out_4] ;
    HELP            [out_4_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_5             (DS-65)
%SYM%   member      OUT_5               parameter
%SYM%   member      VL_OUT_5            variable-list
%TXT%   record      __out_5
%IMP%   RECORD      __out_5
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_5
{
    LABEL           [out_5] ;
    HELP            [out_5_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_6             (DS-65)
%SYM%   member      OUT_6               parameter
%SYM%   member      VL_OUT_6            variable-list
%TXT%   record      __out_6
%IMP%   RECORD      __out_6
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_6
{
    LABEL           [out_6] ;
    HELP            [out_6_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_7             (DS-65)
%SYM%   member      OUT_7               parameter
%SYM%   member      VL_OUT_7            variable-list
%TXT%   record      __out_7
%IMP%   RECORD      __out_7
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_7
{
    LABEL           [out_7] ;
    HELP            [out_7_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_8             (DS-65)
%SYM%   member      OUT_8               parameter
%SYM%   member      VL_OUT_8            variable-list
%TXT%   record      __out_8
%IMP%   RECORD      __out_8
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_8
{
    LABEL           [out_8] ;
    HELP            [out_8_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __float_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d1             (DS-66)
%SYM%   member      OUT_D1               parameter
%SYM%   member      VL_OUT_D1            variable-list
%TXT%   record      __out_d1
%IMP%   RECORD      __out_d1
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d1
{
    LABEL           [out_d1] ;
    HELP            [out_d1_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d2             (DS-66)
%SYM%   member      OUT_D2               parameter
%SYM%   member      VL_OUT_D2            variable-list
%TXT%   record      __out_d2
%IMP%   RECORD      __out_d2
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d2
{
    LABEL           [out_d2] ;
    HELP            [out_d2_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d3             (DS-66)
%SYM%   member      OUT_D3               parameter
%SYM%   member      VL_OUT_D3            variable-list
%TXT%   record      __out_d3
%IMP%   RECORD      __out_d3
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d3
{
    LABEL           [out_d3] ;
    HELP            [out_d3_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d4             (DS-66)
%SYM%   member      OUT_D4               parameter
%SYM%   member      VL_OUT_D4            variable-list
%TXT%   record      __out_d4
%IMP%   RECORD      __out_d4
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d4
{
    LABEL           [out_d4] ;
    HELP            [out_d4_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d5             (DS-66)
%SYM%   member      OUT_D5               parameter
%SYM%   member      VL_OUT_D5            variable-list
%TXT%   record      __out_d5
%IMP%   RECORD      __out_d5
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d5
{
    LABEL           [out_d5] ;
    HELP            [out_d5_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d6             (DS-66)
%SYM%   member      OUT_D6               parameter
%SYM%   member      VL_OUT_D6            variable-list
%TXT%   record      __out_D6
%IMP%   RECORD      __out_D6
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d6
{
    LABEL           [out_d6] ;
    HELP            [out_d6_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_d7             (DS-66)
%SYM%   member      OUT_D7               parameter
%SYM%   member      VL_OUT_D7            variable-list
%TXT%   record      __out_d7
%IMP%   RECORD      __out_d7
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d7
{
    LABEL           [out_d7] ;
    HELP            [out_d7_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__out_D8             (DS-66)
%SYM%   member      OUT_D8               parameter
%SYM%   member      VL_OUT_d8            variable-list
%TXT%   record      __out_d8
%IMP%   RECORD      __out_d8
%IMP%       VARIABLE    __status_output_nd
%IMP%       VARIABLE    __float_output_nd
**********************************************************************
*/
RECORD      __out_d8
{
    LABEL           [out_d8] ;
    HELP            [out_d8_help] ;
    MEMBERS
    {
        STATUS,  __status_output_nd ;
        VALUE,   __discrete_output_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}


/*
************************************************************
__in_2            (DS-65)
%SYM%   member      IN_2                parameter
%SYM%   member      VL_IN_2             variable-list
%TXT%   record      __in_2
%IMP%   RECORD      __in_2
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_2
{
    LABEL           [in_2] ;
    HELP            [in_2_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_3            (DS-65)
%SYM%   member      IN_3                parameter
%SYM%   member      VL_IN_3             variable-list
%TXT%   record      __in_3
%IMP%   RECORD      __in_3
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_3
{
    LABEL           [in_3] ;
    HELP            [in_3_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_4            (DS-65)
%SYM%   member      IN_4                parameter
%SYM%   member      VL_IN_4             variable-list
%TXT%   record      __in_4
%IMP%   RECORD      __in_4
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_4
{
    LABEL           [in_4] ;
    HELP            [in_4_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_5            (DS-65)
%SYM%   member      IN_5                parameter
%SYM%   member      VL_IN_5             variable-list
%TXT%   record      __in_5
%IMP%   RECORD      __in_5
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_5
{
    LABEL           [in_5] ;
    HELP            [in_5_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_6            (DS-65)
%SYM%   member      IN_6                parameter
%SYM%   member      VL_IN_6             variable-list
%TXT%   record      __in_6
%IMP%   RECORD      __in_6
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_6
{
    LABEL           [in_6] ;
    HELP            [in_6_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_7            (DS-65)
%SYM%   member      IN_7                parameter
%SYM%   member      VL_IN_7             variable-list
%TXT%   record      __in_7
%IMP%   RECORD      __in_7
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_7
{
    LABEL           [in_7] ;
    HELP            [in_7_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_8            (DS-65)
%SYM%   member      IN_8                parameter
%SYM%   member      VL_IN_8             variable-list
%TXT%   record      __in_8
%IMP%   RECORD      __in_8
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_8
{
    LABEL           [in_8] ;
    HELP            [in_8_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __float_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d1            (DS-66)
%SYM%   member      IN_D1                parameter
%SYM%   member      VL_IN_D1             variable-list
%TXT%   record      __in_d1
%IMP%   RECORD      __in_d1
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d1
{
    LABEL           [in_d1] ;
    HELP            [in_d1_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d2            (DS-66)
%SYM%   member      IN_D2                parameter
%SYM%   member      VL_IN_D2             variable-list
%TXT%   record      __in_d2
%IMP%   RECORD      __in_d2
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d2
{
    LABEL           [in_d2] ;
    HELP            [in_d2_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d3            (DS-66)
%SYM%   member      IN_D3                parameter
%SYM%   member      VL_IN_D3             variable-list
%TXT%   record      __in_d3
%IMP%   RECORD      __in_d3
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d3
{
    LABEL           [in_d3] ;
    HELP            [in_d3_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d4            (DS-66)
%SYM%   member      IN_D4                parameter
%SYM%   member      VL_IN_D4             variable-list
%TXT%   record      __in_d4
%IMP%   RECORD      __in_d4
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d4
{
    LABEL           [in_d4] ;
    HELP            [in_d4_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d5            (DS-66)
%SYM%   member      IN_D5                parameter
%SYM%   member      VL_IN_D5             variable-list
%TXT%   record      __in_d5
%IMP%   RECORD      __in_d5
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d5
{
    LABEL           [in_d5] ;
    HELP            [in_d5_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d6            (DS-66)
%SYM%   member      IN_D6                parameter
%SYM%   member      VL_IN_D6             variable-list
%TXT%   record      __in_d6
%IMP%   RECORD      __in_d6
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d6
{
    LABEL           [in_d6] ;
    HELP            [in_d6_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d7            (DS-66)
%SYM%   member      IN_D7                parameter
%SYM%   member      VL_IN_D7             variable-list
%TXT%   record      __in_d7
%IMP%   RECORD      __in_d7
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d7
{
    LABEL           [in_d7] ;
    HELP            [in_d7_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__in_d8            (DS-66)
%SYM%   member      IN_D8                parameter
%SYM%   member      VL_IN_D8             variable-list
%TXT%   record      __in_d8
%IMP%   RECORD      __in_d8
%IMP%       VARIABLE    __status_input_nd
%IMP%       VARIABLE    __float_input_nd
************************************************************
*/
RECORD      __in_d8
{
    LABEL           [in_d8] ;
    HELP            [in_d8_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
this parameter probably will go away
************************************************************
*/
VARIABLE      __mo_status_opts
{
    LABEL           [mo_status_opts] ;
    HELP            [mo_status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
/*  RESPONSE_CODES  xxx ; */
}

/*
************************************************************
__mo_opts
%SYM%   member      MO_OPTS         parameter
%SYM%   member      VL_MO_OPTS      variable-list
%TXT%   variable    __mo_opts       bit-enumerated
%IMP%   VARIABLE    __mo_opts
************************************************************
*/
VARIABLE    __mo_opts
{
    LABEL           [mo_opts] ;
    HELP            [mo_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,    [fs_to_value_1], [fs_to_value_1_help] },
        { 0x0002,    [fs_to_value_2], [fs_to_value_2_help] },
        { 0x0004,    [fs_to_value_3], [fs_to_value_3_help] },
        { 0x0008,    [fs_to_value_4], [fs_to_value_4_help] },
        { 0x0010,    [fs_to_value_5], [fs_to_value_5_help] },
        { 0x0020,    [fs_to_value_6], [fs_to_value_6_help] },
        { 0x0040,    [fs_to_value_7], [fs_to_value_7_help] },
        { 0x0080,    [fs_to_value_8], [fs_to_value_8_help] },
        { 0x0100,    [use_fs_value_1], [use_fs_value_1_help] },
        { 0x0200,    [use_fs_value_2], [use_fs_value_2_help] },
        { 0x0400,    [use_fs_value_3], [use_fs_value_3_help] },
        { 0x0800,    [use_fs_value_4], [use_fs_value_4_help] },
        { 0x1000,    [use_fs_value_5], [use_fs_value_5_help] },
        { 0x2000,    [use_fs_value_6], [use_fs_value_6_help] },
        { 0x4000,    [use_fs_value_7], [use_fs_value_7_help] },
        { 0x8000,    [use_fs_value_8], [use_fs_value_8_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__fstate_status
**********************************************************************
*/
VARIABLE    __fstate_status
{
    LABEL           [fs_status] ;
    HELP            [fs_status_help] ;
    CLASS           CONTAINED & DYNAMIC;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001, [value_1_in_fs], [value_1_in_fs_help] },
        { 0x0002, [value_2_in_fs], [value_2_in_fs_help] },
        { 0x0004, [value_3_in_fs], [value_3_in_fs_help] },
        { 0x0008, [value_4_in_fs], [value_4_in_fs_help] },
        { 0x0010, [value_5_in_fs], [value_5_in_fs_help] },
        { 0x0020, [value_6_in_fs], [value_6_in_fs_help] },
        { 0x0040, [value_7_in_fs], [value_7_in_fs_help] },
        { 0x0080, [value_8_in_fs], [value_8_in_fs_help] }
    }

    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val1
%SYM%   member      FSTATE_VAL_1        parameter
%SYM%   member      VL_FSTATE_VAL_1     variable-list
%TXT%   variable    __fstate_val_1      float
%IMP%   VARIABLE    __fstate_val_1
***********************************************************
*/
VARIABLE    __fstate_val1
{
    LABEL           [fs_val_1] ;
    HELP            [fs_val_1_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val2
%SYM%   member      FSTATE_VAL_2        parameter
%SYM%   member      VL_FSTATE_VAL_2     variable-list
%TXT%   variable    __fstate_val_2      float
%IMP%   VARIABLE    __fstate_val_2
***********************************************************
*/
VARIABLE    __fstate_val2
{
    LABEL           [fs_val_2] ;
    HELP            [fs_val_2_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val3
%SYM%   member      FSTATE_VAL_3        parameter
%SYM%   member      VL_FSTATE_VAL_3     variable-list
%TXT%   variable    __fstate_val_3     float
%IMP%   VARIABLE    __fstate_val_3
***********************************************************
*/
VARIABLE    __fstate_val3
{
    LABEL           [fs_val_3] ;
    HELP            [fs_val_3_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val4
%SYM%   member      FSTATE_VAL_4        parameter
%SYM%   member      VL_FSTATE_VAL_4     variable-list
%TXT%   variable    __fstate_val_4      float
%IMP%   VARIABLE    __fstate_val_4
***********************************************************
*/
VARIABLE    __fstate_val4
{
    LABEL           [fs_val_4] ;
    HELP            [fs_val_4_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val5
%SYM%   member      FSTATE_VAL_5        parameter
%SYM%   member      VL_FSTATE_VAL_5     variable-list
%TXT%   variable    __fstate_val_5      float
%IMP%   VARIABLE    __fstate_val_5
***********************************************************
*/
VARIABLE    __fstate_val5
{
    LABEL           [fs_val_5] ;
    HELP            [fs_val_5_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val6
%SYM%   member      FSTATE_VAL_6        parameter
%SYM%   member      VL_FSTATE_VAL_6     variable-list
%TXT%   variable    __fstate_val_6      float
%IMP%   VARIABLE    __fstate_val_6
***********************************************************
*/
VARIABLE    __fstate_val6
{
    LABEL           [fs_val_6] ;
    HELP            [fs_val_6_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val7
%SYM%   member      FSTATE_VAL_7        parameter
%SYM%   member      VL_FSTATE_VAL_7     variable-list
%TXT%   variable    __fstate_val_7      float
%IMP%   VARIABLE    __fstate_val_7
***********************************************************
*/
VARIABLE    __fstate_val7
{
    LABEL           [fs_val_7] ;
    HELP            [fs_val_7_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val8
%SYM%   member      FSTATE_VAL_8        parameter
%SYM%   member      VL_FSTATE_VAL_8   variable-list       0
%TXT%   variable    __fstate_val_8      float
%IMP%   VARIABLE    __fstate_val_8
***********************************************************
*/
VARIABLE    __fstate_val8
{
    LABEL           [fs_val_8] ;
    HELP            [fs_val_8_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val_d1
%SYM%   member      FSTATE_VAL_D1         parameter
%SYM%   member      VL_FSTATE_VAL_D1      variable-list
%TXT%   variable    __fstate_val_d1       unsigned
%IMP%   VARIABLE    __fstate_val_d1
***********************************************************
*/
VARIABLE    __fstate_val_d1
{
    LABEL           [fs_val_d1] ;
    HELP            [fs_val_d1_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val_d2
%SYM%   member      FSTATE_VAL_D2         parameter
%SYM%   member      VL_FSTATE_VAL_D2      variable-list
%TXT%   variable    __fstate_val_d2       unsigned
%IMP%   VARIABLE    __fstate_val_d2
***********************************************************
*/
VARIABLE    __fstate_val_d2
{
    LABEL           [fs_val_d2] ;
    HELP            [fs_val_d2_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
***********************************************************
__fstate_val_d3
%SYM%   member      FSTATE_VAL_D3         parameter
%SYM%   member      VL_FSTATE_VAL_D3      variable-list
%TXT%   variable    __fstate_val_d3       unsigned
%IMP%   VARIABLE    __fstate_val_d3
***********************************************************
*/
VARIABLE    __fstate_val_d3
{
    LABEL           [fs_val_d3] ;
    HELP            [fs_val_d3_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
***********************************************************
__fstate_val_d4
%SYM%   member      FSTATE_VAL_D4         parameter
%SYM%   member      VL_FSTATE_VAL_D4      variable-list
%TXT%   variable    __fstate_val_d4       unsigned
%IMP%   VARIABLE    __fstate_val_d4
***********************************************************
*/
VARIABLE    __fstate_val_d4
{
    LABEL           [fs_val_d4] ;
    HELP            [fs_val_d4_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
***********************************************************
__fstate_val_d5
%SYM%   member      FSTATE_VAL_D5         parameter
%SYM%   member      VL_FSTATE_VAL_D5      variable-list
%TXT%   variable    __fstate_val_d5       unsigned
%IMP%   VARIABLE    __fstate_val_d5
***********************************************************
*/
VARIABLE    __fstate_val_d5
{
    LABEL           [fs_val_d5] ;
    HELP            [fs_val_d5_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
***********************************************************
__fstate_val_d6
%SYM%   member      FSTATE_VAL_D6         parameter
%SYM%   member      VL_FSTATE_VAL_D6      variable-list
%TXT%   variable    __fstate_val_d6       unsigned
%IMP%   VARIABLE    __fstate_val_d6
***********************************************************
*/
VARIABLE    __fstate_val_d6
{
    LABEL           [fs_val_d6] ;
    HELP            [fs_val_d6_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
***********************************************************
__fstate_val_d7
%SYM%   member      FSTATE_VAL_D7         parameter
%SYM%   member      VL_FSTATE_VAL_D7      variable-list
%TXT%   variable    __fstate_val_d7       unsigned
%IMP%   VARIABLE    __fstate_val_d7
***********************************************************
*/
VARIABLE    __fstate_val_d7
{
    LABEL           [fs_val_d7] ;
    HELP            [fs_val_d7_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
***********************************************************
__fstate_val_d8
%SYM%   member      FSTATE_VAL_D8         parameter
%SYM%   member      VL_FSTATE_VAL_D8      variable-list
%TXT%   variable    __fstate_val_d8       unsigned
%IMP%   VARIABLE    __fstate_val_d8
***********************************************************
*/
VARIABLE    __fstate_val_d8
{
    LABEL           [fs_val_d8] ;
    HELP            [fs_val_d8_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
