/*
** @(#)rio_hart_xdcr_parm.ddl     0.93    2009-08-07
**
** FF common definitions
** Filename: rio_hart_xdcr_parm.ddl
** Spec revision:   FF-901 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.2  Transducer Block Common Structures
**                  FF-912 FS 1.0  Field Diagnostics Profile
**                  FF-915 DPS 2.2 Transducer Block for HSE RIO Module
**
** Date of last change: 2009-12-01
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
** TAB   Revision 0.2  20091201
**       Updated for FF-913 DPS rev 2.2
** TAB   Revision 0.3  20100618
**       Updated for FF-913 DPS rev 2.3
*/

#include "com_tbls.h"
/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_HART_XDCR_PARM,
DEVICE_REVISION __RIO_HART_XDCR_PARM_rel_dev_rev,
DD_REVISION     __RIO_HART_XDCR_PARM_rel_dd_rev

 /*
**********************************************************************
** The following variables make up the RIO Transducer Block Parameters 
** as defined by the RIO Transducer Block specifications (FF-913 & FF-915)
**********************************************************************
*/

/*
**********************************************************************
__io_threshold        (DS-179)
**********************************************************************
*/
RECORD      __io_threshold
{
    LABEL           [io_threshold_label] ;
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
__hart_address      
**********************************************************************
*/
VARIABLE    __hart_address
{
    LABEL           [hart_address_label] ;
    HELP            [hart_address_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_medium      
**********************************************************************
*/
VARIABLE    __hart_medium
{
    LABEL           [hart_medium_label] ;
    HELP            [hart_medium_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_version      
**********************************************************************
*/
VARIABLE    __hart_version
{
    LABEL           [hart_version_label] ;
    HELP            [hart_version_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__num_of_process_variables      
**********************************************************************
*/
VARIABLE    __num_of_process_variables
{
    LABEL           [num_of_process_variables_label] ;
    HELP            [num_of_process_variables_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__dd_revision      
**********************************************************************
*/
VARIABLE    __dd_revision
{
    LABEL           [dd_revision_label] ;
    HELP            [dd_revision_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__device_revision      
**********************************************************************
*/
VARIABLE    __device_revision
{
    LABEL           [device_revision_label] ;
    HELP            [device_revision_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_8_DS_175_1      
**********************************************************************
*/
VARIABLE    __reserved_8_DS_175_1
{
    LABEL           [reserved_label] ;
    HELP            [reserved_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_type      
**********************************************************************
*/
VARIABLE    __hart_device_type
{
    LABEL           [hart_device_type_label] ;
    HELP            [hart_device_type_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_manufacturer_id      
**********************************************************************
*/
VARIABLE    __hart_manufacturer_id
{
    LABEL           [hart_manufacturer_id_label] ;
    HELP            [hart_manufacturer_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_distributor_id      
**********************************************************************
*/
VARIABLE    __hart_distributor_id
{
    LABEL           [hart_distributor_id_label] ;
    HELP            [hart_distributor_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_8_DS_175_1 2    
**********************************************************************
*/
VARIABLE    __reserved_8_DS_175_2
{
    LABEL           [reserved_label] ;
    HELP            [reserved_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_profile   
**********************************************************************
*/
VARIABLE    __hart_device_profile
{
    LABEL           [hart_device_profile_label] ;
    HELP            [hart_device_profile_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_id   
**********************************************************************
*/
VARIABLE    __hart_device_id
{
    LABEL           [hart_device_id_label] ;
    HELP            [hart_device_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_address_ro      
**********************************************************************
*/
VARIABLE    __hart_address_ro
{
    LABEL           [hart_address_label] ;
    HELP            [hart_address_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_medium_ro      
**********************************************************************
*/
VARIABLE    __hart_medium_ro
{
    LABEL           [hart_medium_label] ;
    HELP            [hart_medium_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_version_ro      
**********************************************************************
*/
VARIABLE    __hart_version_ro
{
    LABEL           [hart_version_label] ;
    HELP            [hart_version_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__num_of_process_variables_ro      
**********************************************************************
*/
VARIABLE    __num_of_process_variables_ro
{
    LABEL           [num_of_process_variables_label] ;
    HELP            [num_of_process_variables_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__dd_revision_ro      
**********************************************************************
*/
VARIABLE    __dd_revision_ro
{
    LABEL           [dd_revision_label] ;
    HELP            [dd_revision_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__device_revision_ro      
**********************************************************************
*/
VARIABLE    __device_revision_ro
{
    LABEL           [device_revision_label] ;
    HELP            [device_revision_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_8_DS_175_1_ro      
**********************************************************************
*/
VARIABLE    __reserved_8_DS_175_1_ro
{
    LABEL           [reserved_label] ;
    HELP            [reserved_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_type_ro      
**********************************************************************
*/
VARIABLE    __hart_device_type_ro
{
    LABEL           [hart_device_type_label] ;
    HELP            [hart_device_type_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_manufacturer_id_ro      
**********************************************************************
*/
VARIABLE    __hart_manufacturer_id_ro
{
    LABEL           [hart_manufacturer_id_label] ;
    HELP            [hart_manufacturer_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_distributor_id_ro      
**********************************************************************
*/
VARIABLE    __hart_distributor_id_ro
{
    LABEL           [hart_distributor_id_label] ;
    HELP            [hart_distributor_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_8_DS_175_1 2_ro    
**********************************************************************
*/
VARIABLE    __reserved_8_DS_175_2_ro
{
    LABEL           [reserved_label] ;
    HELP            [reserved_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_profile_ro   
**********************************************************************
*/
VARIABLE    __hart_device_profile_ro
{
    LABEL           [hart_device_profile_label] ;
    HELP            [hart_device_profile_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_device_id_ro   
**********************************************************************
*/
VARIABLE    __hart_device_id_ro
{
    LABEL           [hart_device_id_label] ;
    HELP            [hart_device_id_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
dup_var_name_def_9
**********************************************************************
*/
VARIABLE    __dup_var_name_def_9
{
    LABEL          [dup_var_name_def_9_label] ;
    HELP           [dup_var_name_def_9_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BITSTRING (16) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_expd_dev_info        (DS-175)
**********************************************************************
*/
RECORD      __hart_expd_dev_info
{
    LABEL           [hart_expd_dev_info_label] ;
    HELP            [hart_expd_dev_info_help] ;
    MEMBERS
    {
        HART_ADDRESS,               __hart_address ;
        HART_MEDIUM,                __hart_medium ;
        HART_VERSION,               __hart_version ;
        NUM_OF_PROCESS_VARIABLES,   __num_of_process_variables ;
        HART_DD_REVISION,           __dd_revision ;
        HART_DEVICE_REVISION,       __device_revision ;
        RESERVED_8_DS_175_1,        __reserved_8_DS_175_1 ;
        HART_DEVICE_TYPE,           __hart_device_type ;
        HART_MANUFACTURER_ID,       __hart_manufacturer_id ;
        HART_DISTRIBUTOR_ID,        __hart_distributor_id ;
        RESERVED_8_DS_175_2,        __reserved_8_DS_175_2 ;
        HART_DEVICE_PROFILE,        __hart_device_profile ;
        HART_DEVICE_ID,             __hart_device_id ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_actl_dev_info        (DS-175)
**********************************************************************
*/
RECORD      __hart_actl_dev_info
{
    LABEL           [hart_actl_dev_info_label] ;
    HELP            [hart_actl_dev_info_help] ;
    MEMBERS
    {
        HART_ADDRESS,               __hart_address_ro ;
        HART_MEDIUM,                __hart_medium_ro ;
        HART_VERSION,               __hart_version_ro ;
        NUM_OF_PROCESS_VARIABLES,   __num_of_process_variables_ro ;
        HART_DD_REVISION,           __dd_revision_ro ;
        HART_DEVICE_REVISION,       __device_revision_ro ;
        RESERVED_8_DS_175_1,        __reserved_8_DS_175_1_ro ;
        HART_DEVICE_TYPE,           __hart_device_type_ro ;
        HART_MANUFACTURER_ID,       __hart_manufacturer_id_ro ;
        HART_DISTRIBUTOR_ID,        __hart_distributor_id_ro ;
        RESERVED_8_DS_175_2,        __reserved_8_DS_175_2_ro ;
        HART_DEVICE_PROFILE,        __hart_device_profile_ro ;
        HART_DEVICE_ID,             __hart_device_id_ro ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_cmd_entry
**********************************************************************
*/
VARIABLE    __hart_cmd_entry
{
    LABEL           [hart_cmd_entry_label] ;
    HELP            [hart_cmd_entry_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            OCTET (1);
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_resp_entry
**********************************************************************
*/
VARIABLE    __hart_resp_entry
{
    LABEL           [hart_resp_entry_label] ;
    HELP            [hart_resp_entry_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            OCTET (1);
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_cmd
**********************************************************************
*/
ARRAY    __hart_cmd
{
    LABEL           [hart_cmd_label] ;
    HELP            [hart_cmd_help] ;
    TYPE            __hart_cmd_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 234;
#else
    NUMBER_OF_ELEMENTS 256;
#endif
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_resp
**********************************************************************
*/
ARRAY    __hart_resp
{
    LABEL           [hart_resp_label] ;
    HELP            [hart_resp_help] ;
    TYPE            __hart_resp_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 234;
#else
    NUMBER_OF_ELEMENTS 256;
#endif
    
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__ds_184_pad   
**********************************************************************
*/
VARIABLE    __ds_184_pad
{
    LABEL           [reserved_label] ;
    HELP            [reserved_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__response_code   
**********************************************************************
*/
VARIABLE    __response_code
{
    LABEL           [response_code_label] ;
    HELP            [response_code_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__response_message   
**********************************************************************
*/
VARIABLE    __response_message
{
    LABEL           [response_message_label] ;
    HELP            [response_message_help] ;
    CLASS           CONTAINED ;
#ifdef _TOK42
    TYPE            OCTET (100) ;
#else
    TYPE            OCTET (256) ;
#endif
    HANDLING        READ  ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_ind        (DS-184)
**********************************************************************
*/
RECORD      __hart_ind
{
    LABEL           [hart_ind_label] ;
    HELP            [hart_ind_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,    __unacknowledged ;
        ALARM_STATE,       __alarm_state ;
        TIME_STAMP,        __time_stamp ;
        PAD,               __ds_184_pad ;
        RESPONSE_CODE,     __response_code ;
        RESPONSE_MESSAGE,  __response_message ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_com_stat
**********************************************************************
*/
VARIABLE    __hart_com_stat
{
    LABEL           [hart_com_stat_label] ;
    HELP            [hart_com_stat_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [hart_com_stat_failed_label],      [hart_com_stat_failed_help]     },
        { 1,   [hart_com_stat_timedout_label],    [hart_com_stat_timedout_help]   },
        { 2,   [hart_com_stat_online_label],      [hart_com_stat_online_help]     },
        { 3,   [hart_com_stat_reset_label],       [hart_com_stat_reset_help]      }
    }
    HANDLING        READ ;
    CONSTANT_UNIT   [enumerated] ;

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_ind_pri
**********************************************************************
*/
VARIABLE    __hart_ind_pri
{
    LABEL           [hart_ind_pri_label] ;
    HELP            [hart_ind_pri_help] ;
    CLASS           CONTAINED  ;
    TYPE            UNSIGNED_INTEGER (1);
    HANDLING        READ & WRITE ;

/*  RESPONSE_CODES  xxx ; */
}

/* #define    _HART_DIAG_MAP_0  { 0, [hart_diag_map_0_label], [hart_diag_map_0_help] } */
#define    _HART_DIAG_MAP_0  { 0, "hart_diag_map_0_label", "hart_diag_map_0_help" }

#define  __HART_DIAG_MAP \
        _HART_DIAG_MAP_0
        
/*
**********************************************************************
__hart_diag_map_entry
**********************************************************************
*/
VARIABLE    __hart_diag_map_entry
{
    LABEL           [hart_diag_map_entry_label] ;
    HELP            [hart_diag_map_entry_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        __HART_DIAG_MAP
    }
    HANDLING        READ & WRITE ;
    CONSTANT_UNIT   [enumerated] ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_diag_map
**********************************************************************
*/
ARRAY    __hart_diag_map
{
    LABEL           [hart_diag_map_label] ;
    HELP            [hart_diag_map_help] ;
    TYPE            __hart_diag_map_entry ;
    NUMBER_OF_ELEMENTS 32;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_tstamp
**********************************************************************
*/
VARIABLE    __hart_tstamp
{
    LABEL           [hart_tstamp_label] ;
    HELP            [hart_tstamp_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            TIME_VALUE ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_bad_tmout
**********************************************************************
*/
VARIABLE    __hart_bad_tmout
{
    LABEL           [hart_bad_tmout_label] ;
    HELP            [hart_bad_tmout_help] ;
    CLASS           CONTAINED  ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ&WRITE ;
/*  RESPONSE_CODES  xxx ; */
}


/*
**********************************************************************
__hart_unc_tmout
**********************************************************************
*/
VARIABLE    __hart_unc_tmout
{
    LABEL           [hart_unc_tmout_label] ;
    HELP            [hart_unc_tmout_help] ;
    CLASS           CONTAINED  ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ&WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_var_codes8_entry
**********************************************************************
*/
VARIABLE    __hart_var_codes8_entry
{
    LABEL           [hart_var_codes8_entry_label] ;
    HELP            [hart_var_codes8_entry_help] ;
    CLASS           CONTAINED  ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_var_codes8
**********************************************************************
*/
ARRAY    __hart_var_codes8
{
    LABEL           [hart_var_codes8_label] ;
    HELP            [hart_var_codes8_help] ;
    TYPE            __hart_var_codes8_entry ;
    NUMBER_OF_ELEMENTS 9;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_pv
**********************************************************************
*/
RECORD    __hart_pv
{
    LABEL           [hart_pv_label] ;
    HELP            [hart_pv_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_sv
**********************************************************************
*/
RECORD    __hart_sv
{
    LABEL           [hart_sv_label] ;
    HELP            [hart_sv_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_tv
**********************************************************************
*/
RECORD    __hart_tv
{
    LABEL           [hart_tv_label] ;
    HELP            [hart_tv_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_qv
**********************************************************************
*/
RECORD    __hart_qv
{
    LABEL           [hart_qv_label] ;
    HELP            [hart_qv_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_5v
**********************************************************************
*/
RECORD    __hart_5v
{
    LABEL           [hart_5v_label] ;
    HELP            [hart_5v_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_6v
**********************************************************************
*/
RECORD    __hart_6v
{
    LABEL           [hart_6v_label] ;
    HELP            [hart_6v_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_7v
**********************************************************************
*/
RECORD    __hart_7v
{
    LABEL           [hart_7v_label] ;
    HELP            [hart_7v_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_8v
**********************************************************************
*/
RECORD    __hart_8v
{
    LABEL           [hart_8v_label] ;
    HELP            [hart_8v_help] ;
    MEMBERS
    {
        STATUS,     __status_contained_r ;
        VALUE,      __float_contained_r ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_lrl
**********************************************************************
*/
VARIABLE    __hart_lrl
{
    LABEL           [hart_lrl_label] ;
    HELP            [hart_lrl_help] ;
    CLASS           CONTAINED  ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_url
**********************************************************************
*/
VARIABLE    __hart_url
{
    LABEL           [hart_url_label] ;
    HELP            [hart_url_help] ;
    CLASS           CONTAINED  ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_units9_entry
**********************************************************************
*/
VARIABLE    __var_units9_entry
{
    LABEL           [var_units9_entry_label] ;
    HELP            [var_units9_entry_help] ;
    CLASS           CONTAINED  ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_units9
**********************************************************************
*/
ARRAY    __var_units9
{
    LABEL           [var_units9_label] ;
    HELP            [var_units9_help] ;
    TYPE            __var_units9_entry ;
    NUMBER_OF_ELEMENTS 9;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names9_entry
**********************************************************************
*/
VARIABLE    __var_names9_entry
{
    LABEL           [var_names9_entry_label] ;
    HELP            [var_names9_entry_help] ;
    CLASS           CONTAINED  ;
    TYPE            VISIBLE (32) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_names9
**********************************************************************
*/
ARRAY    __var_names9
{
    LABEL           [var_names9_label] ;
    HELP            [var_names9_help] ;
    TYPE            __var_names9_entry ;
#ifdef _TOK42
    NUMBER_OF_ELEMENTS 7;
#else
    NUMBER_OF_ELEMENTS 9;
#endif

/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__var_dir9_entry
**********************************************************************
*/
VARIABLE    __var_dir9_entry
{
    LABEL           [var_dir9_entry_label] ;
    HELP            [var_dir9_Entry_help] ;
    CLASS           CONTAINED ;
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
__var_dir9
**********************************************************************
*/
ARRAY    __var_dir9
{
    LABEL           [var_dir9_label] ;
    HELP            [var_dir9_help] ;
    TYPE            __var_dir9_entry ;
    NUMBER_OF_ELEMENTS 9; 
}

/*
**********************************************************************
__publish_control
**********************************************************************
*/
VARIABLE    __publish_control
{
    LABEL           [publish_control_label] ;
    HELP            [publish_control_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [publish_control_off_label],           [publish_control_off_help]          },
        { 1,   [publish_control_enable_dll_label],    [publish_control_enable_dll_help]   },
        { 2,   [publish_control_enable_tdma_label],   [publish_control_enable_tdma_help]  },
        { 3,   [publish_control_both_label],          [publish_control_both_help]         }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_command_expansion
**********************************************************************
*/
VARIABLE    __hart_command_expansion
{
    LABEL           [hart_command_expansion_label] ;
    HELP            [hart_command_expansion_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__device_variable_code_0
**********************************************************************
*/
VARIABLE    __device_variable_code_0
{
    LABEL           [device_variable_code_0_label] ;
    HELP            [device_variable_code_0_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_1
**********************************************************************
*/
VARIABLE    __device_variable_code_1
{
    LABEL           [device_variable_code_1_label] ;
    HELP            [device_variable_code_1_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_2
**********************************************************************
*/
VARIABLE    __device_variable_code_2
{
    LABEL           [device_variable_code_2_label] ;
    HELP            [device_variable_code_2_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_3
**********************************************************************
*/
VARIABLE    __device_variable_code_3
{
    LABEL           [device_variable_code_3_label] ;
    HELP            [device_variable_code_3_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_4
**********************************************************************
*/
VARIABLE    __device_variable_code_4
{
    LABEL           [device_variable_code_4_label] ;
    HELP            [device_variable_code_4_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_5
**********************************************************************
*/
VARIABLE    __device_variable_code_5
{
    LABEL           [device_variable_code_5_label] ;
    HELP            [device_variable_code_5_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_6
**********************************************************************
*/
VARIABLE    __device_variable_code_6
{
    LABEL           [device_variable_code_6_label] ;
    HELP            [device_variable_code_6_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__device_variable_code_7
**********************************************************************
*/
VARIABLE    __device_variable_code_7
{
    LABEL           [device_variable_code_7_label] ;
    HELP            [device_variable_code_7_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__publish_data_ref
**********************************************************************
*/
VARIABLE    __publish_data_ref
{
    LABEL           [publish_data_ref_label] ;
    HELP            [publish_data_ref_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__max_publish_count
**********************************************************************
*/
VARIABLE    __max_publish_count
{
    LABEL           [max_publish_count_label] ;
    HELP            [max_publish_count_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_command_number
**********************************************************************
*/
VARIABLE    __hart_command_number
{
    LABEL           [hart_command_number_label] ;
    HELP            [hart_command_number_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_ds_183_u16
**********************************************************************
*/
VARIABLE    __reserved_ds_183_u16
{
    LABEL           [reserved_ds_183_u16_label] ;
    HELP            [reserved_ds_183_u16_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__minimum_update_period
**********************************************************************
*/
VARIABLE    __minimum_update_period
{
    LABEL           [minimum_update_period_label] ;
    HELP            [minimum_update_period_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
    CONSTANT_UNIT   [seconds] ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__maximum_update_period
**********************************************************************
*/
VARIABLE    __maximum_update_period
{
    LABEL           [maximum_update_period_label] ;
    HELP            [maximum_update_period_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
    CONSTANT_UNIT   [seconds] ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__trigger_mode
**********************************************************************
*/
VARIABLE    __trigger_mode
{
    LABEL           [trigger_mode_label] ;
    HELP            [trigger_mode_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   [trigger_mode_normal_label],  [trigger_mode_normal_help] },
        { 1,   [trigger_mode_window_label],  [trigger_mode_window_help] },
        { 2,   [trigger_mode_high_label],    [trigger_mode_high_help]   },
        { 3,   [trigger_mode_low_label],     [trigger_mode_low_help]    },
        { 4,   [trigger_mode_change_label],  [trigger_mode_change_help] }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__device_variable_classification
**********************************************************************
*/
VARIABLE    __device_variable_classification
{
    LABEL           [device_variable_classification_label] ;
    HELP            [device_variable_classification_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   "HCF_SPEC-183",  "HCF_SPEC-183" }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_unit
**********************************************************************
*/
VARIABLE    __hart_unit
{
    LABEL           [hart_unit_label] ;
    HELP            [hart_unit_help] ;
    CLASS           CONTAINED ;
    TYPE            ENUMERATED (1)
    {
        { 0,   "HCF_SPEC-183",  "HCF_SPEC-183" }
    }
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__reserved_ds_183_u8
**********************************************************************
*/
VARIABLE    __reserved_ds_183_u8
{
    LABEL           [reserved_ds_183_u8_label] ;
    HELP            [reserved_ds_183_u8_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
 
/*
**********************************************************************
__trigger_level
**********************************************************************
*/
VARIABLE    __trigger_level
{
    LABEL           [trigger_level_label] ;
    HELP            [trigger_level_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}
        
/*
**********************************************************************
__hart_burst_ctrl_1  DS-183
**********************************************************************
*/
RECORD      __hart_burst_ctrl_1
{
    LABEL           [hart_burst_ctrl_1_label] ;
    HELP            [hart_burst_ctrl_1_help] ;
    MEMBERS
    {
        PUBLISH_CONTROL,                  __publish_control ;
        HART_COMMAND_EXPANSION,           __hart_command_expansion ;
        DEVICE_VARIABLE_CODE_0,           __device_variable_code_0 ;
        DEVICE_VARIABLE_CODE_1,           __device_variable_code_1 ;
        DEVICE_VARIABLE_CODE_2,           __device_variable_code_2 ;
        DEVICE_VARIABLE_CODE_3,           __device_variable_code_3 ;
        DEVICE_VARIABLE_CODE_4,           __device_variable_code_4 ;
        DEVICE_VARIABLE_CODE_5,           __device_variable_code_5 ;
        DEVICE_VARIABLE_CODE_6,           __device_variable_code_6 ;
        DEVICE_VARIABLE_CODE_7,           __device_variable_code_7 ;
        PUBLISH_DATA_REF,                 __publish_data_ref ;
        MAX_PUBLISH_COUNT,                __max_publish_count ;
        HART_COMMAND_NUMBER,              __hart_command_number ;
        RESERVED_DS_183_U16,              __reserved_ds_183_u16 ;
        MINIMUM_UPDATE_PERIOD,            __minimum_update_period ;
        MAXIMUM_UPDATE_PERIOD,            __maximum_update_period ;
        TRIGGER_MODE,                     __trigger_mode ;
        DEVICE_VARIABLE_CLASSIFICATION,   __device_variable_classification ;
        HART_UNIT,                        __hart_unit ;
        RESERVED_DS_183_U8,               __reserved_ds_183_u8 ;
        TRIGGER_LEVEL,                    __trigger_level ;
        
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_burst_ctrl_2  DS-183
**********************************************************************
*/
RECORD      __hart_burst_ctrl_2
{
    LABEL           [hart_burst_ctrl_2_label] ;
    HELP            [hart_burst_ctrl_2_help] ;
    MEMBERS
    {
        PUBLISH_CONTROL,                  __publish_control ;
        HART_COMMAND_EXPANSION,           __hart_command_expansion ;
        DEVICE_VARIABLE_CODE_0,           __device_variable_code_0 ;
        DEVICE_VARIABLE_CODE_1,           __device_variable_code_1 ;
        DEVICE_VARIABLE_CODE_2,           __device_variable_code_2 ;
        DEVICE_VARIABLE_CODE_3,           __device_variable_code_3 ;
        DEVICE_VARIABLE_CODE_4,           __device_variable_code_4 ;
        DEVICE_VARIABLE_CODE_5,           __device_variable_code_5 ;
        DEVICE_VARIABLE_CODE_6,           __device_variable_code_6 ;
        DEVICE_VARIABLE_CODE_7,           __device_variable_code_7 ;
        PUBLISH_DATA_REF,                 __publish_data_ref ;
        MAX_PUBLISH_COUNT,                __max_publish_count ;
        HART_COMMAND_NUMBER,              __hart_command_number ;
        RESERVED_DS_183_U16,              __reserved_ds_183_u16 ;
        MINIMUM_UPDATE_PERIOD,            __minimum_update_period ;
        MAXIMUM_UPDATE_PERIOD,            __maximum_update_period ;
        TRIGGER_MODE,                     __trigger_mode ;
        DEVICE_VARIABLE_CLASSIFICATION,   __device_variable_classification ;
        HART_UNIT,                        __hart_unit ;
        RESERVED_DS_183_U8,               __reserved_ds_183_u8 ;
        TRIGGER_LEVEL,                    __trigger_level ;
        
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_burst_ctrl_3  DS-183
**********************************************************************
*/
RECORD      __hart_burst_ctrl_3
{
    LABEL           [hart_burst_ctrl_3_label] ;
    HELP            [hart_burst_ctrl_3_help] ;
    MEMBERS
    {
        PUBLISH_CONTROL,                  __publish_control ;
        HART_COMMAND_EXPANSION,           __hart_command_expansion ;
        DEVICE_VARIABLE_CODE_0,           __device_variable_code_0 ;
        DEVICE_VARIABLE_CODE_1,           __device_variable_code_1 ;
        DEVICE_VARIABLE_CODE_2,           __device_variable_code_2 ;
        DEVICE_VARIABLE_CODE_3,           __device_variable_code_3 ;
        DEVICE_VARIABLE_CODE_4,           __device_variable_code_4 ;
        DEVICE_VARIABLE_CODE_5,           __device_variable_code_5 ;
        DEVICE_VARIABLE_CODE_6,           __device_variable_code_6 ;
        DEVICE_VARIABLE_CODE_7,           __device_variable_code_7 ;
        PUBLISH_DATA_REF,                 __publish_data_ref ;
        MAX_PUBLISH_COUNT,                __max_publish_count ;
        HART_COMMAND_NUMBER,              __hart_command_number ;
        RESERVED_DS_183_U16,              __reserved_ds_183_u16 ;
        MINIMUM_UPDATE_PERIOD,            __minimum_update_period ;
        MAXIMUM_UPDATE_PERIOD,            __maximum_update_period ;
        TRIGGER_MODE,                     __trigger_mode ;
        DEVICE_VARIABLE_CLASSIFICATION,   __device_variable_classification ;
        HART_UNIT,                        __hart_unit ;
        RESERVED_DS_183_U8,               __reserved_ds_183_u8 ;
        TRIGGER_LEVEL,                    __trigger_level ;
        
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__hart_burst_ctrl_4  DS-183
**********************************************************************
*/
RECORD      __hart_burst_ctrl_4
{
    LABEL           [hart_burst_ctrl_4_label] ;
    HELP            [hart_burst_ctrl_4_help] ;
    MEMBERS
    {
        PUBLISH_CONTROL,                  __publish_control ;
        HART_COMMAND_EXPANSION,           __hart_command_expansion ;
        DEVICE_VARIABLE_CODE_0,           __device_variable_code_0 ;
        DEVICE_VARIABLE_CODE_1,           __device_variable_code_1 ;
        DEVICE_VARIABLE_CODE_2,           __device_variable_code_2 ;
        DEVICE_VARIABLE_CODE_3,           __device_variable_code_3 ;
        DEVICE_VARIABLE_CODE_4,           __device_variable_code_4 ;
        DEVICE_VARIABLE_CODE_5,           __device_variable_code_5 ;
        DEVICE_VARIABLE_CODE_6,           __device_variable_code_6 ;
        DEVICE_VARIABLE_CODE_7,           __device_variable_code_7 ;
        PUBLISH_DATA_REF,                 __publish_data_ref ;
        MAX_PUBLISH_COUNT,                __max_publish_count ;
        HART_COMMAND_NUMBER,              __hart_command_number ;
        RESERVED_DS_183_U16,              __reserved_ds_183_u16 ;
        MINIMUM_UPDATE_PERIOD,            __minimum_update_period ;
        MAXIMUM_UPDATE_PERIOD,            __maximum_update_period ;
        TRIGGER_MODE,                     __trigger_mode ;
        DEVICE_VARIABLE_CLASSIFICATION,   __device_variable_classification ;
        HART_UNIT,                        __hart_unit ;
        RESERVED_DS_183_U8,               __reserved_ds_183_u8 ;
        TRIGGER_LEVEL,                    __trigger_level ;
        
    }
/*  RESPONSE_CODES  xxx ; */
}
