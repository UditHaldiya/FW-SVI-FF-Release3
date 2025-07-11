/*
** @(#)rio_xdcr_parm.ddl     0.93    2009-08-07
**
** FF common definitions
** Filename: rio_xdcr_parm.ddl
** Spec revision:   FF-901 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.2  Transducer Block Common Structures
**                  FF-912 FS 1.0  Field Diagnostics Profile
**                  FF-915 DPS 2.2 Transducer Block for HSE RIO Module
**
** Date of last change: 2009-11-30
** Description: This file contains common data variables and records
** used for rio xducer block parameter records
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
** TAB   Revision 0.1  20090807
** TAB   Revision 0.2  20091130
**       Updated for FF-915 DPS rev 2.2
** TAB   Revision 0.3  20100618
**       Updated for FF-915 DPS rev 2.3
*/

#include "com_tbls.h"
/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_XDCR_PARM,
DEVICE_REVISION __RIO_XDCR_PARM_rel_dev_rev,
DD_REVISION     __RIO_XDCR_PARM_rel_dd_rev

 /*
**********************************************************************
** The following variables make up the RIO Transducer Block Parameters 
** as defined by the RIO Transducer Block specifications (FF-913 & FF-915)
**********************************************************************
*/
/*
**********************************************************************
__var_names_entry
**********************************************************************
*/
VARIABLE    __var_names_entry
{
    LABEL           [var_names_entry_label] ;
    HELP            [var_names_entry_help] ;
    CLASS           CONTAINED ;
    TYPE            VISIBLE (32) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__var_names4 
**********************************************************************
*/
ARRAY    __var_names4
{
    LABEL           [var_names4_label] ;
    HELP            [var_names4_help] ;
    TYPE            __var_names_entry ;
    NUMBER_OF_ELEMENTS 4;

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names8 
**********************************************************************
*/
ARRAY    __var_names8
{
    LABEL           [var_names8_label] ;
    HELP            [var_names8_help] ;
    TYPE            __var_names_entry ;
#ifdef _TOK42
     NUMBER_OF_ELEMENTS 7;
#else
   NUMBER_OF_ELEMENTS 8;
#endif

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names16 
**********************************************************************
*/
ARRAY    __var_names16
{
    LABEL           [var_names16_label] ;
    HELP            [var_names16_help] ;
    TYPE            __var_names_entry ;
#ifdef _TOK42
   NUMBER_OF_ELEMENTS 7;
#else
   NUMBER_OF_ELEMENTS 16;
#endif

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names32 
**********************************************************************
*/
ARRAY    __var_names32
{
    LABEL           [var_names32_label] ;
    HELP            [var_names32_help] ;
    TYPE            __var_names_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 7;
#else
    NUMBER_OF_ELEMENTS 32;
#endif

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names64a
**********************************************************************
*/
ARRAY    __var_names64a
{
    LABEL           [var_names64a_label] ;
    HELP            [var_names64a_help] ;
    TYPE            __var_names_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 7;
#else
NUMBER_OF_ELEMENTS 32;
#endif
}

/*
**********************************************************************
__var_names64b 
**********************************************************************
*/
ARRAY    __var_names64b
{
    LABEL           [var_names64b_label] ;
    HELP            [var_names64b_help] ;
    TYPE            __var_names_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 7;
#else
    NUMBER_OF_ELEMENTS 32;
#endif
}

/*
**********************************************************************
var_dir_entry
**********************************************************************
*/
VARIABLE    __var_dir_entry
{
    LABEL          [var_dir_entry_label] ;
    HELP           [var_dir_entry_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [var_dir9_undefined_label],      [var_dir9_undefined_help]  },
        { 1,   [var_dir9_input_label],          [var_dir9_input_help]      },
        { 2,   [var_dir9_output_label],         [var_dir9_output_help]     }
    }
    
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [enumerated] ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir4 
**********************************************************************
*/
ARRAY    __var_dir4
{
    LABEL           [var_dir4_label] ;
    HELP            [var_dir4_help] ;
    TYPE            __var_dir_entry ;
    NUMBER_OF_ELEMENTS 4; 
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir8
**********************************************************************
*/
ARRAY    __var_dir8
{
    LABEL           [var_dir8_label] ;
    HELP            [var_dir8_help] ;
    TYPE            __var_dir_entry ;
    NUMBER_OF_ELEMENTS 8; 
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir16
**********************************************************************
*/
ARRAY    __var_dir16
{
    LABEL           [var_dir16_label] ;
    HELP            [var_dir16_help] ;
    TYPE            __var_dir_entry ;
    NUMBER_OF_ELEMENTS 16; 
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir32
**********************************************************************
*/
ARRAY    __var_dir32
{
    LABEL           [var_dir32_label] ;
    HELP            [var_dir32_help] ;
    TYPE            __var_dir_entry ;
    NUMBER_OF_ELEMENTS 32; 
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir64
**********************************************************************
*/
ARRAY    __var_dir64
{
    LABEL           [var_dir64_label] ;
    HELP            [var_dir64_help] ;
    TYPE            __var_dir_entry ;
    NUMBER_OF_ELEMENTS 64; 
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a
**********************************************************************
*/
RECORD      __process_value_a
{
    LABEL           [process_value_a_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_1
**********************************************************************
*/
RECORD      __process_value_a_1
{
    LABEL           [process_value_a_1_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_2
**********************************************************************
*/
RECORD      __process_value_a_2
{
    LABEL           [process_value_a_2_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_3
**********************************************************************
*/
RECORD      __process_value_a_3
{
    LABEL           [process_value_a_3_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_4
**********************************************************************
*/
RECORD      __process_value_a_4
{
    LABEL           [process_value_a_4_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_5
**********************************************************************
*/
RECORD      __process_value_a_5
{
    LABEL           [process_value_a_5_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_6
**********************************************************************
*/
RECORD      __process_value_a_6
{
    LABEL           [process_value_a_6_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_7
**********************************************************************
*/
RECORD      __process_value_a_7
{
    LABEL           [process_value_a_7_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_8
**********************************************************************
*/
RECORD      __process_value_a_8
{
    LABEL           [process_value_a_8_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_9
**********************************************************************
*/
RECORD      __process_value_a_9
{
    LABEL           [process_value_a_9_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_10
**********************************************************************
*/
RECORD      __process_value_a_10
{
    LABEL           [process_value_a_10_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_11
**********************************************************************
*/
RECORD      __process_value_a_11
{
    LABEL           [process_value_a_11_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_12
**********************************************************************
*/
RECORD      __process_value_a_12
{
    LABEL           [process_value_a_12_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_13
**********************************************************************
*/
RECORD      __process_value_a_13
{
    LABEL           [process_value_a_13_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_14
**********************************************************************
*/
RECORD      __process_value_a_14
{
    LABEL           [process_value_a_14_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_15
**********************************************************************
*/
RECORD      __process_value_a_15
{
    LABEL           [process_value_a_15_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_a_16
**********************************************************************
*/
RECORD      __process_value_a_16
{
    LABEL           [process_value_a_16_label] ;
    HELP            [process_value_a_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b
**********************************************************************
*/
RECORD      __process_value_b
{
    LABEL           [process_value_b_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_1
**********************************************************************
*/
RECORD      __process_value_b_1
{
    LABEL           [process_value_b_1_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_2
**********************************************************************
*/
RECORD      __process_value_b_2
{
    LABEL           [process_value_b_2_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_3
**********************************************************************
*/
RECORD      __process_value_b_3
{
    LABEL           [process_value_b_3_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_4
**********************************************************************
*/
RECORD      __process_value_b_4
{
    LABEL           [process_value_b_4_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_5
**********************************************************************
*/
RECORD      __process_value_b_5
{
    LABEL           [process_value_b_5_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_6
**********************************************************************
*/
RECORD      __process_value_b_6
{
    LABEL           [process_value_b_6_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_7
**********************************************************************
*/
RECORD      __process_value_b_7
{
    LABEL           [process_value_b_7_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_8
**********************************************************************
*/
RECORD      __process_value_b_8
{
    LABEL           [process_value_b_8_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_9
**********************************************************************
*/
RECORD      __process_value_b_9
{
    LABEL           [process_value_b_9_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_10
**********************************************************************
*/
RECORD      __process_value_b_10
{
    LABEL           [process_value_b_10_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_11
**********************************************************************
*/
RECORD      __process_value_b_11
{
    LABEL           [process_value_b_11_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_12
**********************************************************************
*/
RECORD      __process_value_b_12
{
    LABEL           [process_value_b_12_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_13
**********************************************************************
*/
RECORD      __process_value_b_13
{
    LABEL           [process_value_b_13_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_14
**********************************************************************
*/
RECORD      __process_value_b_14
{
    LABEL           [process_value_b_14_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_15
**********************************************************************
*/
RECORD      __process_value_b_15
{
    LABEL           [process_value_b_15_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_16
**********************************************************************
*/
RECORD      __process_value_b_16
{
    LABEL           [process_value_b_16_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_17
**********************************************************************
*/
RECORD      __process_value_b_17
{
    LABEL           [process_value_b_17_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_18
**********************************************************************
*/
RECORD      __process_value_b_18
{
    LABEL           [process_value_b_18_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_19
**********************************************************************
*/
RECORD      __process_value_b_19
{
    LABEL           [process_value_b_19_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_20
**********************************************************************
*/
RECORD      __process_value_b_20
{
    LABEL           [process_value_b_20_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_21
**********************************************************************
*/
RECORD      __process_value_b_21
{
    LABEL           [process_value_b_21_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_22
**********************************************************************
*/
RECORD      __process_value_b_22
{
    LABEL           [process_value_b_22_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_23
**********************************************************************
*/
RECORD      __process_value_b_23
{
    LABEL           [process_value_b_23_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_24
**********************************************************************
*/
RECORD      __process_value_b_24
{
    LABEL           [process_value_b_24_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_25
**********************************************************************
*/
RECORD      __process_value_b_25
{
    LABEL           [process_value_b_25_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_26
**********************************************************************
*/
RECORD      __process_value_b_26
{
    LABEL           [process_value_b_26_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_27
**********************************************************************
*/
RECORD      __process_value_b_27
{
    LABEL           [process_value_b_27_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_28
**********************************************************************
*/
RECORD      __process_value_b_28
{
    LABEL           [process_value_b_28_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_29
**********************************************************************
*/
RECORD      __process_value_b_29
{
    LABEL           [process_value_b_29_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_30
**********************************************************************
*/
RECORD      __process_value_b_30
{
    LABEL           [process_value_b_30_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_31
**********************************************************************
*/
RECORD      __process_value_b_31
{
    LABEL           [process_value_b_31_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_32
**********************************************************************
*/
RECORD      __process_value_b_32
{
    LABEL           [process_value_b_32_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_33
**********************************************************************
*/
RECORD      __process_value_b_33
{
    LABEL           [process_value_b_33_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_34
**********************************************************************
*/
RECORD      __process_value_b_34
{
    LABEL           [process_value_b_34_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_35
**********************************************************************
*/
RECORD      __process_value_b_35
{
    LABEL           [process_value_b_35_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_36
**********************************************************************
*/
RECORD      __process_value_b_36
{
    LABEL           [process_value_b_36_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_37
**********************************************************************
*/
RECORD      __process_value_b_37
{
    LABEL           [process_value_b_37_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_38
**********************************************************************
*/
RECORD      __process_value_b_38
{
    LABEL           [process_value_b_38_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_39
**********************************************************************
*/
RECORD      __process_value_b_39
{
    LABEL           [process_value_b_39_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_40
**********************************************************************
*/
RECORD      __process_value_b_40
{
    LABEL           [process_value_b_40_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_41
**********************************************************************
*/
RECORD      __process_value_b_41
{
    LABEL           [process_value_b_41_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_42
**********************************************************************
*/
RECORD      __process_value_b_42
{
    LABEL           [process_value_b_42_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_43
**********************************************************************
*/
RECORD      __process_value_b_43
{
    LABEL           [process_value_b_43_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_44
**********************************************************************
*/
RECORD      __process_value_b_44
{
    LABEL           [process_value_b_44_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_45
**********************************************************************
*/
RECORD      __process_value_b_45
{
    LABEL           [process_value_b_45_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_46
**********************************************************************
*/
RECORD      __process_value_b_46
{
    LABEL           [process_value_b_46_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_47
**********************************************************************
*/
RECORD      __process_value_b_47
{
    LABEL           [process_value_b_47_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_48
**********************************************************************
*/
RECORD      __process_value_b_48
{
    LABEL           [process_value_b_48_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_49
**********************************************************************
*/
RECORD      __process_value_b_49
{
    LABEL           [process_value_b_49_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_50
**********************************************************************
*/
RECORD      __process_value_b_50
{
    LABEL           [process_value_b_50_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_51
**********************************************************************
*/
RECORD      __process_value_b_51
{
    LABEL           [process_value_b_51_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_52
**********************************************************************
*/
RECORD      __process_value_b_52
{
    LABEL           [process_value_b_52_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_53
**********************************************************************
*/
RECORD      __process_value_b_53
{
    LABEL           [process_value_b_53_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_54
**********************************************************************
*/
RECORD      __process_value_b_54
{
    LABEL           [process_value_b_54_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_55
**********************************************************************
*/
RECORD      __process_value_b_55
{
    LABEL           [process_value_b_55_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_56
**********************************************************************
*/
RECORD      __process_value_b_56
{
    LABEL           [process_value_b_56_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_57
**********************************************************************
*/
RECORD      __process_value_b_57
{
    LABEL           [process_value_b_57_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_58
**********************************************************************
*/
RECORD      __process_value_b_58
{
    LABEL           [process_value_b_58_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_59
**********************************************************************
*/
RECORD      __process_value_b_59
{
    LABEL           [process_value_b_59_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_60
**********************************************************************
*/
RECORD      __process_value_b_60
{
    LABEL           [process_value_b_60_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_61
**********************************************************************
*/
RECORD      __process_value_b_61
{
    LABEL           [process_value_b_61_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_62
**********************************************************************
*/
RECORD      __process_value_b_62
{
    LABEL           [process_value_b_62_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_63
**********************************************************************
*/
RECORD      __process_value_b_63
{
    LABEL           [process_value_b_63_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_b_64
**********************************************************************
*/
RECORD      __process_value_b_64
{
    LABEL           [process_value_b_64_label] ;
    HELP            [process_value_b_help] ;
    MEMBERS
    {
        STATUS,  __status_contained_r ;
        VALUE,   __discrete_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__h1_vfd_id_1
**********************************************************************
*/
VARIABLE    __h1_vfd_id_1
{
    LABEL          [h1_vfd_id_1_label] ;
    HELP           [h1_vfd_id_1_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__h1_vfd_id_2
**********************************************************************
*/
VARIABLE    __h1_vfd_id_2
{
    LABEL          [h1_vfd_id_2_label] ;
    HELP           [h1_vfd_id_2_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__h1_vfd_id_3
**********************************************************************
*/
VARIABLE    __h1_vfd_id_3
{
    LABEL          [h1_vfd_id_3_label] ;
    HELP           [h1_vfd_id_3_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
__h1_vfd_id_4
**********************************************************************
*/
VARIABLE    __h1_vfd_id_4
{
    LABEL          [h1_vfd_id_4_label] ;
    HELP           [h1_vfd_id_4_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_1        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_1
{
    LABEL           [process_value_range_a_1_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_2        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_2
{
    LABEL           [process_value_range_a_2_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_3        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_3
{
    LABEL           [process_value_range_a_3_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_4        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_4
{
    LABEL           [process_value_range_a_4_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_5        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_5
{
    LABEL           [process_value_range_a_5_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_6        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_6
{
    LABEL           [process_value_range_a_6_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_7        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_7
{
    LABEL           [process_value_range_a_7_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_8        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_8
{
    LABEL           [process_value_range_a_8_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_9        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_9
{
    LABEL           [process_value_range_a_9_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_10        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_10
{
    LABEL           [process_value_range_a_10_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_11        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_11
{
    LABEL           [process_value_range_a_11_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_12        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_12
{
    LABEL           [process_value_range_a_12_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_13        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_13
{
    LABEL           [process_value_range_a_13_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_14        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_14
{
    LABEL           [process_value_range_a_14_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_15        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_15
{
    LABEL           [process_value_range_a_15_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__process_value_range_a_16        (DS-68)
**********************************************************************
*/
RECORD      __process_value_range_a_16
{
    LABEL           [process_value_range_a_16_label] ;
    HELP            [process_value_range_a_help] ;
    MEMBERS
    {
        EU_100,      __eu_100 ;
        EU_0,        __eu_0 ;
        UNITS_INDEX, __units_index ;
        DECIMAL,     __decimal ;
    }
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__overrng_bad
**********************************************************************
*/
VARIABLE    __overrng_bad
{
    LABEL           [overrng_bad_label] ;
    HELP            [overrng_bad_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__overrng_unc
**********************************************************************
*/
VARIABLE    __overrng_unc
{
    LABEL           [overrng_unc_label] ;
    HELP            [overrng_unc_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__underrng_unc
**********************************************************************
*/
VARIABLE    __underrng_unc
{
    LABEL           [underrng_unc_label] ;
    HELP            [underrng_unc_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__underrng_bad
**********************************************************************
*/
VARIABLE    __underrng_bad
{
    LABEL           [underrng_bad_label] ;
    HELP            [underrng_bad_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__overrng_lim
**********************************************************************
*/
VARIABLE    __overrng_lim
{
    LABEL           [overrng_lim_label] ;
    HELP            [overrng_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
          
/*
**********************************************************************
__underrng_lim
**********************************************************************
*/
VARIABLE    __underrng_lim
{
    LABEL           [underrng_lim_label] ;
    HELP            [underrng_lim_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_1        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_1
{
    LABEL           [io_threshold_a_1_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_2        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_2
{
    LABEL           [io_threshold_a_2_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_3        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_3
{
    LABEL           [io_threshold_a_3_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_4        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_4
{
    LABEL           [io_threshold_a_4_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_5        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_5
{
    LABEL           [io_threshold_a_5_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_6        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_6
{
    LABEL           [io_threshold_a_6_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_7        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_7
{
    LABEL           [io_threshold_a_7_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_8        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_8
{
    LABEL           [io_threshold_a_8_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_9        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_9
{
    LABEL           [io_threshold_a_9_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_10        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_10
{
    LABEL           [io_threshold_a_10_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_11        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_11
{
    LABEL           [io_threshold_a_11_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_12        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_12
{
    LABEL           [io_threshold_a_12_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_13        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_13
{
    LABEL           [io_threshold_a_13_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_14        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_14
{
    LABEL           [io_threshold_a_14_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_15        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_15
{
    LABEL           [io_threshold_a_15_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__io_threshold_a_16        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold_a_16
{
    LABEL           [io_threshold_a_16_label] ;
    HELP            [io_threshold_help] ;
    MEMBERS
    {
        OVERRNG_BAD,       __overrng_bad ;
        OVERRNG_UNC,       __overrng_unc ;
        UNDERRNG_UNC,      __underrng_unc ;
        UNDERRNG_BAD,      __underrng_bad ;
        OVERRNG_LIM,       __overrng_lim ;
        UNDERRNG_LIM,      __underrng_lim ;
    }
/*  RESPONSE_CODES  xxx ; */
}

VARIABLE    __expd_manufac_id
{
    LABEL           [expd_manufac_id_label] ;
    HELP            [expd_manufac_id_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (4)
    {
            __FF_MFR_INDEX
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

VARIABLE    __expd_dev_type
{
    LABEL           [expd_dev_type_label] ;
    HELP            [expd_dev_type_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (2)
    {
    	{ 0,	[undefined],	[blank] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

VARIABLE    __expd_dev_rev
{
    LABEL           [expd_dev_rev_label] ;
    HELP            [expd_dev_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

VARIABLE    __expd_dd_rev
{
    LABEL           [expd_dd_rev_label] ;
    HELP            [expd_dd_rev_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

VARIABLE    __vfd_ref
{
    LABEL           [vfd_ref_label] ;
    HELP            [vfd_ref_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
