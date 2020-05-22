/*
** @(#)rio_parm.ddl    1.0 June 16 2009

**
** FF standard remote I/O parameter definitions
** Filename: rio_parm.ddl
** Spec revision:       FF-900 FS 1.0 DDL spec
**                      FF-633 DPS 2.1 FBAP spec part 6
** Date of last change: 2009-06-16
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
** FD    Revision 1.0  20090616
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
DEVICE_TYPE     __RIO_PARM,
DEVICE_REVISION __RIO_PARM_rel_dev_rev,
DD_REVISION     __RIO_PARM_rel_dd_rev


/*
**********************************************************************
__bkcal_outm_16 (DS-174)
**********************************************************************
*/

VARIABLE    __reserved3_r
{
    LABEL           [reserved3_r_label] ;
    HELP            [reserved3_r_help] ;
    CLASS           OUTPUT & DYNAMIC ;
    TYPE            OCTET (3) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

RECORD      __bkcal_outm_16
{
    LABEL           [bkcal_outm_16_label] ;
    HELP            [bkcal_outm_16_help] ;
    MEMBERS
    {
		RESERVED,  __reserved3_r;
		OVERALL_STATUS, __status_output_r;

        STATUS1,  __status_output_r ;
        STATUS2,  __status_output_r ;
        STATUS3,  __status_output_r ;
        STATUS4,  __status_output_r ;
        STATUS5,  __status_output_r ;
        STATUS6,  __status_output_r ;
        STATUS7,  __status_output_r ;
        STATUS8,  __status_output_r ;
        STATUS9,  __status_output_r ;
        STATUS10,  __status_output_r ;
        STATUS11,  __status_output_r ;
        STATUS12,  __status_output_r ;
        STATUS13,  __status_output_r ;
        STATUS14,  __status_output_r ;
        STATUS15,  __status_output_r ;
        STATUS16,  __status_output_r ;
        VALUE1,   __float_output_r ;
        VALUE2,   __float_output_r ;
        VALUE3,   __float_output_r ;
        VALUE4,   __float_output_r ;
        VALUE5,   __float_output_r ;
        VALUE6,   __float_output_r ;
        VALUE7,   __float_output_r ;
        VALUE8,   __float_output_r ;
        VALUE9,   __float_output_r ;
        VALUE10,   __float_output_r ;
        VALUE11,   __float_output_r ;
        VALUE12,   __float_output_r ;
        VALUE13,   __float_output_r ;
        VALUE14,   __float_output_r ;
        VALUE15,   __float_output_r ;
        VALUE16,   __float_output_r ;
    }
}

/*
**********************************************************************
__bkcal_outm_b64       (based on DS-158)
**********************************************************************
*/
RECORD      __bkcal_outm_b64
{
    LABEL           [bkcal_outm__b64_label] ;
    HELP            [bkcal_outm__b64_help] ;
    MEMBERS
    {
		RESERVED, __reserved3_r ;
        STATUS,  __status_output_r ;
        VALUE,   __bkcal_outm_b64_values ;
    }
}

VARIABLE __bkcal_outm_b64_values
{
    LABEL           [__bkcal_outm_b64_value_label] ;
    HELP            [__bkcal_outm_b64_value_help] ;
    CLASS           OUTPUT & DYNAMIC;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ;
}

/*
**********************************************************************
__cas_inm_16 (DS-174)
**********************************************************************
*/

VARIABLE    __reserved3_r_in
{
    LABEL           [reserved3_r_label] ;
    HELP            [reserved3_r_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            OCTET (3) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}


RECORD      __cas_inm_16
{
    LABEL           [__cas_inm_16_label] ;
    HELP            [__cas_inm_16_help] ;
    MEMBERS
    {
		RESERVED,  __reserved3_r_in;
		OVERALL_STATUS, __status_input;

        STATUS1,  __status_input ;
        STATUS2,  __status_input ;
        STATUS3,  __status_input ;
        STATUS4,  __status_input ;
        STATUS5,  __status_input ;
        STATUS6,  __status_input ;
        STATUS7,  __status_input ;
        STATUS8,  __status_input ;
        STATUS9,  __status_input ;
        STATUS10,  __status_input ;
        STATUS11,  __status_input ;
        STATUS12,  __status_input ;
        STATUS13,  __status_input ;
        STATUS14,  __status_input ;
        STATUS15,  __status_input ;
        STATUS16,  __status_input ;
        VALUE1,   __float_input ;
        VALUE2,   __float_input ;
        VALUE3,   __float_input ;
        VALUE4,   __float_input ;
        VALUE5,   __float_input ;
        VALUE6,   __float_input ;
        VALUE7,   __float_input ;
        VALUE8,   __float_input ;
        VALUE9,   __float_input ;
        VALUE10,   __float_input ;
        VALUE11,   __float_input ;
        VALUE12,   __float_input ;
        VALUE13,   __float_input ;
        VALUE14,   __float_input ;
        VALUE15,   __float_input ;
        VALUE16,   __float_input ;
    }
}


/*
**********************************************************************
__cas_in_b64       (based on DS-158)
**********************************************************************
*/
RECORD      __cas_inm_b64
{
    LABEL           [__cas_inm_b64_label] ;
    HELP            [__cas_inm_b64_help] ;
    MEMBERS
    {
		RESERVED, __reserved3_r_in ;
        STATUS,  __status_input ;
        VALUE,   __cas_inm_b64_values ;
    }
}

VARIABLE __cas_inm_b64_values
{
    LABEL           [__cas_inm_b64_values_label] ;
    HELP            [__cas_inm_b64_values_help] ;
    CLASS           INPUT & DYNAMIC ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE;
}


/*
**********************************************************************
__channel_tag_elem
**********************************************************************
*/
VARIABLE    __channel_tag_elem
{
    LABEL           [channel_tag_elem] ;
    HELP            [channel_tag_elem_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            VISIBLE (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__channel_tag_64a
**********************************************************************
*/
ARRAY __channel_tag_64a
{
    LABEL           [channel_tag_32a_label] ;
    HELP            [channel_tag_32a_help] ;
    TYPE            __channel_tag_elem ;
	NUMBER_OF_ELEMENTS	32 ;
}

/*
**********************************************************************
__channel_tag_32b
**********************************************************************
*/
ARRAY __channel_tag_64b
{
    LABEL           [channel_tag_32b_label] ;
    HELP            [channel_tag_32b_help] ;
    TYPE            __channel_tag_elem ;
	NUMBER_OF_ELEMENTS	32 ;
}
/*
**********************************************************************
__channel_tag_16
**********************************************************************
*/
ARRAY __channel_tag_16
{
    LABEL           [channel_tag_16_label] ;
    HELP            [channel_tag_16_help] ;
    TYPE            __channel_tag_elem ;
	NUMBER_OF_ELEMENTS	16 ;
}

/*
**********************************************************************
__fstate_st_16
**********************************************************************
*/
VARIABLE    __fstate_st_16
{
    LABEL           [fstate_st_16_label] ;
    HELP            [fstate_st_16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

/*
**********************************************************************
__fstate_st_64
**********************************************************************
*/
VARIABLE    __fstate_st_64
{
    LABEL           [fstate_st_64_label] ;
    HELP            [fstate_st_64_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

/*
**********************************************************************
__fstate_val_b64
**********************************************************************
*/
VARIABLE    __fstate_val_b64
{
    LABEL           [fstate_val_b64_label] ;
    HELP            [fstate_val_b64_help] ;
    CLASS           CONTAINED ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__fstate_val_16
**********************************************************************
*/
ARRAY    __fstate_val_16
{
    LABEL           [fstate_val_16_label] ;
    HELP            [fstate_val_16_help] ;
    TYPE            __fstate_val ;
	NUMBER_OF_ELEMENTS	16 ;
}

/*
**********************************************************************
__map_mm_16
**********************************************************************
*/
VARIABLE    __map_mm_16
{
    LABEL           [map_mm_16_label] ;
    HELP            [map_mm_16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

/*
**********************************************************************
__map_mm_64
**********************************************************************
*/
VARIABLE    __map_mm_64
{
    LABEL           [map_mm_64_label] ;
    HELP            [map_mm_64_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

/*
**********************************************************************
__mo_fstate_opts_16
**********************************************************************
*/
VARIABLE    __mo_fstate_opts_16
{
    LABEL           [mo_fstate_opts_16_label] ;
    HELP            [mo_fstate_opts_16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__mo_powerup_opts_16
**********************************************************************
*/
VARIABLE    __mo_powerup_opts_16
{
    LABEL           [mo_powerup_opts_16_label] ;
    HELP            [mo_powerup_opts_16_help] ;
    CLASS           CONTAINED ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__mo_fstate_opts_64
**********************************************************************
*/
VARIABLE    __mo_fstate_opts_64
{
    LABEL           [mo_fstate_opts_64_label] ;
    HELP            [mo_fstate_opts_64_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__mo_powerup_opts_64
**********************************************************************
*/
VARIABLE    __mo_powerup_opts_64
{
    LABEL           [mo_powerup_opts_64_label] ;
    HELP            [mo_powerup_opts_64_help] ;
    CLASS           CONTAINED ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__force_enb_16
**********************************************************************
*/
VARIABLE    __force_enb_16
{
    LABEL           [force_enb_16_label] ;
    HELP            [force_enb_16_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__outm_16 (DS-174)
**********************************************************************
*/

RECORD      __outm_16
{
    LABEL           [__outm_16_label] ;
    HELP            [__outm_16_help] ;
    MEMBERS
    {
		RESERVED,  __reserved3_r;
		OVERALL_STATUS, __status_output_r;

        STATUS1,  __status_output_r ;
        STATUS2,  __status_output_r ;
        STATUS3,  __status_output_r ;
        STATUS4,  __status_output_r ;
        STATUS5,  __status_output_r ;
        STATUS6,  __status_output_r ;
        STATUS7,  __status_output_r ;
        STATUS8,  __status_output_r ;
        STATUS9,  __status_output_r ;
        STATUS10,  __status_output_r ;
        STATUS11,  __status_output_r ;
        STATUS12,  __status_output_r ;
        STATUS13,  __status_output_r ;
        STATUS14,  __status_output_r ;
        STATUS15,  __status_output_r ;
        STATUS16,  __status_output_r ;
        VALUE1,   __float_output_nd ;
        VALUE2,   __float_output_nd ;
        VALUE3,   __float_output_nd ;
        VALUE4,   __float_output_nd ;
        VALUE5,   __float_output_nd ;
        VALUE6,   __float_output_nd ;
        VALUE7,   __float_output_nd ;
        VALUE8,   __float_output_nd ;
        VALUE9,   __float_output_nd ;
        VALUE10,   __float_output_nd ;
        VALUE11,   __float_output_nd ;
        VALUE12,   __float_output_nd ;
        VALUE13,   __float_output_nd ;
        VALUE14,   __float_output_nd ;
        VALUE15,   __float_output_nd ;
        VALUE16,   __float_output_nd ;
    }
}



/*
**********************************************************************
__force_enb_b64
**********************************************************************
*/
VARIABLE    __force_enb_b64
{
    LABEL           [force_enb_b64_label] ;
    HELP            [force_enb_b64_help] ;
    CLASS           CONTAINED;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

/*
**********************************************************************
__outm_b64       (based on DS-158)
**********************************************************************
*/
RECORD      __outm_b64
{
    LABEL           [__outm_b64_label] ;
    HELP            [__outm_b64_help] ;
    MEMBERS
    {
		RESERVED, __reserved3_r ;
        STATUS,  __status_input ;
        VALUE,   __outm_b64_values ;
    }
}

VARIABLE __outm_b64_values
{
    LABEL           [__out_b64_values_label] ;
    HELP            [__out_b64_values_help] ;
    CLASS           OUTPUT & OPERATE ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE;
}

/*
**********************************************************************
__spm_16 (DS-174)
**********************************************************************
*/

VARIABLE    __reserved3_r_con
{
    LABEL           [reserved3_r_label] ;
    HELP            [reserved3_r_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            OCTET (3) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}


RECORD      __spm_16
{
    LABEL           [__spm_16_label] ;
    HELP            [__spm_16_help] ;
    MEMBERS
    {
		RESERVED,  __reserved3_r_con;
		OVERALL_STATUS, __status_contained_r;

        STATUS1,  __status_contained_r ;
        STATUS2,  __status_contained_r ;
        STATUS3,  __status_contained_r ;
        STATUS4,  __status_contained_r ;
        STATUS5,  __status_contained_r ;
        STATUS6,  __status_contained_r ;
        STATUS7,  __status_contained_r ;
        STATUS8,  __status_contained_r ;
        STATUS9,  __status_contained_r ;
        STATUS10,  __status_contained_r ;
        STATUS11,  __status_contained_r ;
        STATUS12,  __status_contained_r ;
        STATUS13,  __status_contained_r ;
        STATUS14,  __status_contained_r ;
        STATUS15,  __status_contained_r ;
        STATUS16,  __status_contained_r ;
        VALUE1,   __float_contained_nd ;
        VALUE2,   __float_contained_nd ;
        VALUE3,   __float_contained_nd ;
        VALUE4,   __float_contained_nd ;
        VALUE5,   __float_contained_nd ;
        VALUE6,   __float_contained_nd ;
        VALUE7,   __float_contained_nd ;
        VALUE8,   __float_contained_nd ;
        VALUE9,   __float_contained_nd ;
        VALUE10,   __float_contained_nd ;
        VALUE11,   __float_contained_nd ;
        VALUE12,   __float_contained_nd ;
        VALUE13,   __float_contained_nd ;
        VALUE14,   __float_contained_nd ;
        VALUE15,   __float_contained_nd ;
        VALUE16,   __float_contained_nd ;
    }
}

/*
**********************************************************************
__spm_b64       (based on DS-158)
**********************************************************************
*/
RECORD      __spm_b64
{
    LABEL           [__spm_b64_label] ;
    HELP            [__spm_b64_help] ;
    MEMBERS
    {
		RESERVED, __reserved3_r_con ;
        STATUS,  __status_input ;
        VALUE,   __spm_b64_values ;
    }
}

VARIABLE __spm_b64_values
{
    LABEL           [__spm_b64_values_label] ;
    HELP            [__spm_b64_values_help] ;
    CLASS           CONTAINED & OPERATE ;
    TYPE            BITSTRING (64) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE;
}


VARIABLE __num_posns
{
    LABEL           [num_posns_label] ;
    HELP            [num_posns_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) 
	{
		MAX_VALUE		2048;
	}
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
}

VARIABLE __max_num_posns
{
    LABEL           [max_num_posns_label] ;
    HELP            [max_num_posns_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2)
	{
		MAX_VALUE		2048;
	}

    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

VARIABLE __elem_mismat_num
{
    LABEL           [elem_mismat_num_label] ;
    HELP            [elem_mismat_num_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (2) 
	{
		MAX_VALUE		2048;
	}

    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

VARIABLE __elem_mismat_bs_1
{
    LABEL           [elem_mismat_bs_1_label] ;
    HELP            [elem_mismat_bs_1_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (32) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
}

