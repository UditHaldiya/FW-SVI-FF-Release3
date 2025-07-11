/*
** @(#)sif_parm.ddl 1.0 2007-09-29
**
** FF SIF standard parameters
** Filename: sif_parm.ddl
** Spec revision: FF-900 FS 1.0 DDL spec
**                FF-807 FS 1.1 FF-SIS Application Model
**                FF-895 PS 1.1 FF-SIS Function Blocks Phase 1
** Date of last change: 2007-10-02
** Description:
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
** (c) Fieldbus Foundation(TM) (1994-2007)
**
*/

/*
** HISTORY:
**  ED  Revision 1.9  2007-09-29
**      added new SIS parameters: __sif_det_comm_err, __macro_cycle_t, __blk_chn_err, __sif_sync_drift, __sif_sync_jitter, __sif_sync_drift_act
**      added new SIS parameters: __stale_data_t
**  ED  Revision 1.10  2008-08-17
**      changed name of SIS parameters: __blk_chn_err (sif_error), __sf_sync_drift (sif...) , __sf_sync_jitter (sif...), __sf_sync_drift_act (sif...), __sis_reset_d (__sif_clear_latch_d)
**      added new SIS parameters: __sif_sync_tot_err, __config_sig, __config_sig_calc, __firmware_sig 
** MS   ARs 5044, 5282 -- 2010.06.14
*/

#include "com_tbls.h"

/*
**********************************************************************
** Blocks are built from variables and records that are defined here.
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __SIF_PARM,
DEVICE_REVISION __SIF_PARM_rel_dev_rev,
DD_REVISION     __SIF_PARM_rel_dd_rev

/*
**********************************************************************
** Block Data Structure (DS-64)
** The following variables make up a block record (DS-64) as defined
** by the Function Block specification
**********************************************************************
*/

/*
**********************************************************************
__sif_det_comm_err
**********************************************************************
*/
VARIABLE    __sif_det_comm_err
{
    LABEL           [sif_det_comm_err_label] ;
    HELP            [sif_det_comm_err_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__macro_cycle_t
**********************************************************************
*/
VARIABLE    __macro_cycle_t
{
    LABEL           [macro_cycle_t_label] ;
    HELP            [macro_cycle_t_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sif_error
**********************************************************************
*/
VARIABLE    __sif_error
{
    LABEL           [sif_error_label] ;
    HELP            [sif_error_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            BIT_ENUMERATED (2)
    {
        { 0x0001,  [subcode_undefined],               [subcode_undefined_help] },
        { 0x0002,  [subcode_config_sig_err],          [subcode_config_sig_err_help] },
        { 0x0004,  [subcode_time_sync_err],           [subcode_time_sync_err_help] },
        { 0x0008,  [subcode_wrong_mode_for_lock_err], [subcode_wrong_mode_for_lock_err_help] }
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sif_sync_drift
**********************************************************************
*/
VARIABLE    __sif_sync_drift
{
    LABEL           [sif_sync_drift_label] ;
    HELP            [sif_sync_drift_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4)
    {
        MIN_VALUE   100 ;
        MAX_VALUE   1000 ;
    }
    CONSTANT_UNIT   [one_thirtysecond_ms_per_min] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sif_sync_jitter
**********************************************************************
*/
VARIABLE    __sif_sync_jitter
{
    LABEL           [sif_sync_jitter_label] ;
    HELP            [sif_sync_jitter_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4)
    {
        MIN_VALUE   0 ;
        MAX_VALUE   320 ;
    }
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sif_sync_tot_err
**********************************************************************
*/
VARIABLE    __sif_sync_tot_err
{
    LABEL           [sif_sync_tot_err_label] ;
    HELP            [sif_sync_tot_err_help] ;
    CLASS           CONTAINED & DYNAMIC ;
    TYPE            INTEGER (4) ;
    CONSTANT_UNIT   [one_thirtysecond_ms] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__stale_data_t
**********************************************************************
*/
VARIABLE    __stale_data_t
{
    LABEL           [stale_data_t_label] ;
    HELP            [stale_data_t_help] ;
    CLASS           CONTAINED ;
    TYPE            FLOAT ;
    CONSTANT_UNIT   [sec] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__clear_latch_d (DS-66)
**********************************************************************
*/
RECORD      __clear_latch_d
{
    LABEL          [clear_latch_d_label] ;
    HELP           [clear_latch_d_help] ;
    MEMBERS
    {
        STATUS,  __status_input_nd ;
        VALUE,   __discrete_input_nd ;
    }
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__config_sig
**********************************************************************
*/
VARIABLE    __config_sig
{
    LABEL           [config_sig_label] ;
    HELP            [config_sig_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__config_sig_calc
**********************************************************************
*/
VARIABLE    __config_sig_calc
{
    LABEL           [config_sig_calc_label] ;
    HELP            [config_sig_calc_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__firmware_sig
**********************************************************************
*/
VARIABLE    __firmware_sig
{
    LABEL           [firmware_sig_label] ;
    HELP            [firmware_sig_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (4) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__sif_itk_ver
%SYM%   member      SIF_ITK_VER             parameter      0xC0011D17     
%SYM%   member      VL_SIF_ITK_VER          variable-list  0xC0011D16     
%TXT%   variable    __sif_itk_ver           unsigned       0x80021D0B     
%IMP%   VARIABLE    __sif_itk_ver
**********************************************************************
*/
VARIABLE    __sif_itk_ver
{
    LABEL           [sif_itk_ver_label] ;
    HELP            [sif_itk_ver_help] ;
    CLASS           CONTAINED ;
    TYPE            UNSIGNED_INTEGER (2) ;
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
__status_opts_sai
**********************************************************************
*/
VARIABLE    __status_opts_sai
{
    LABEL           [status_opts_label] ;
    HELP            [status_opts_help] ;
    CLASS           CONTAINED ;
    TYPE            BIT_ENUMERATED (2)
    {
      __FF_STATUS_OPTS_SAI_ENUMS
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
