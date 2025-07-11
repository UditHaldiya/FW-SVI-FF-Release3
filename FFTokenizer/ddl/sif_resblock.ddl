/*
** @(#)sif_resblock.ddl 1.0 2007-09-29
**
** FF SIF Resource block
** Filename: sif_resblock.ddl
** Spec revision: FF-900 FS 1.0 DDL spec
**                FF-807 FS 1.1 FF-SIS Application Model
**                FF-895 PS 1.1 FF-SIS Function Blocks Phase 1
** Date of last change: 2007-09-29
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
** (c) Fieldbus Foundation(TM) (1994-2007)
**
*/

/*
** HISTORY:
**  ED Revision 0.1 2007-09-28
**  ED Revision 1.0 2008-08-17
**     changed name of SIF parameters: __blk_chn_err (sif_err), __sf_sync_drift (sif...) , __sf_sync_jitter (sif...), __sf_sync_drift_act (sif...)
**     added new SIF parameters: __sif_sync_tot_err, __config_sig, __config_sig_calc, __firmware_sig 
** MS   ARs 2901 -- 2008.10.07
**  ED Revision 1.2 2008-12-03 Changed SIS to SIF
** MS   ARs 4006 -- 2009.06.15
** MS   ARs 5044 -- 2010.07.14
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Resource block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __SIF_RES_BLOCK,
DEVICE_REVISION __SIF_RES_BLOCK_rel_dev_rev,
DD_REVISION     __SIF_RES_BLOCK_rel_dd_rev

/*
**********************************************************************
** Resource
** Definition of an SIF resource block
**********************************************************************
*/
BLOCK      __sif_resource_block
{
    CHARACTERISTICS     __sif_res_character ;
    LABEL               [sif_resource_block] ;
    HELP                [sif_resource_block_help] ;
    PARAMETERS
    {
        ST_REV,             __st_rev ;
        TAG_DESC,           __tag_desc ;
        STRATEGY,           __strategy ;
        ALERT_KEY,          __alert_key ;
        MODE_BLK,           __mode_blk ;
        BLOCK_ERR,          __block_err ;
        RS_STATE,           __rs_state ;
        TEST_RW,            __test_read_write ;
        DD_RESOURCE,        __dd_resource ;
        MANUFAC_ID,         __manufac_id ;
        DEV_TYPE,           __dev_type ;
        DEV_REV,            __dev_rev ;
        DD_REV,             __dd_rev ;
        GRANT_DENY,         __grant_deny ;
        HARD_TYPES,         __hard_types ;
        RESTART,            __restart ;
        FEATURES,           __features ;
        FEATURE_SEL,        __feature_sel ;
        CYCLE_TYPE,         __cycle_type ;
        CYCLE_SEL,          __cycle_sel ;
        MIN_CYCLE_T,        __min_cycle_t ;
        MEMORY_SIZE,        __memory_size ;
        NV_CYCLE_T,         __nv_cycle_t ;
        FREE_SPACE,         __free_space ;
        FREE_TIME,          __free_time ;
        SHED_RCAS,          __shed_rcas ;
        SHED_ROUT,          __shed_rout ;
        FAULT_STATE,        __fault_state ;
        SET_FSTATE,         __set_fstate ;
        CLR_FSTATE,         __clr_fstate ;
        MAX_NOTIFY,         __max_notify ;
        LIM_NOTIFY,         __lim_notify ;
        CONFIRM_TIME,       __confirm_time ;
        WRITE_LOCK,         __write_lock ;
        UPDATE_EVT,         __update_evt ;
        BLOCK_ALM,          __block_alm ;
        ALARM_SUM,          __alarm_sum_res ;
        ACK_OPTION,         __ack_option_res ;
        WRITE_PRI,          __write_pri ;
        WRITE_ALM,          __write_alm ;
        ITK_VER,            __itk_ver ;       
        SIF_DET_COMM_ERR,   __sif_det_comm_err ;
        MACRO_CYCLE_T,      __macro_cycle_t ;
        SIF_ERROR,          __sif_error ;
        SIF_SYNC_DRIFT,     __sif_sync_drift ;
        SIF_SYNC_JITTER,    __sif_sync_jitter ;
        SIF_SYNC_TOT_ERR,   __sif_sync_tot_err ;
        CONFIG_SIG,         __config_sig ;
        CONFIG_SIG_CALC,    __config_sig_calc ;
        FIRMWARE_SIG,       __firmware_sig ;
        SIF_ITK_VER,	__sif_itk_ver ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __sif_res_view_1 ;
        VIEW_2, __sif_res_view_2 ;
        VIEW_3, __sif_res_view_3 ;
        VIEW_4, __sif_res_view_4 ;
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_sif_res
    	,upload_wanted_sif_res
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __sif_res_character
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
}
/*
**********************************************************************
** Variable lists
**********************************************************************
*/
VARIABLE_LIST   __sif_res_view_1
{
    LABEL       [sif_res_view_1] ;
    HELP        [sif_res_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_MODE_BLK,    PARAM.MODE_BLK ;
        VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        VL_RS_STATE,    PARAM.RS_STATE ;
        VL_FREE_TIME,   PARAM.FREE_TIME ;
        VL_FAULT_STATE, PARAM.FAULT_STATE ;
        VL_ALARM_SUM,   PARAM.ALARM_SUM ;
    }
}

VARIABLE_LIST   __sif_res_view_2
{
    LABEL       [sif_res_view_2] ;
    HELP        [sif_res_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_GRANT_DENY,      PARAM.GRANT_DENY ;
        VL_FEATURE_SEL,     PARAM.FEATURE_SEL ;
        VL_CYCLE_SEL,       PARAM.CYCLE_SEL ;
        VL_NV_CYCLE_T,      PARAM.NV_CYCLE_T ;
        VL_FREE_SPACE,      PARAM.FREE_SPACE ;
        VL_SHED_RCAS,       PARAM.SHED_RCAS ;
        VL_SHED_ROUT,       PARAM.SHED_ROUT ;
        VL_LIM_NOTIFY,      PARAM.LIM_NOTIFY ;
        VL_CONFIRM_TIME,    PARAM.CONFIRM_TIME ;
        VL_WRITE_LOCK,      PARAM.WRITE_LOCK ;
    }
}

VARIABLE_LIST   __sif_res_view_3
{
    LABEL       [sif_res_view_3] ;
    HELP        [sif_res_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,            PARAM.ST_REV ;
        VL_MODE_BLK,          PARAM.MODE_BLK ;
        VL_BLOCK_ERR,         PARAM.BLOCK_ERR ;
        VL_RS_STATE,          PARAM.RS_STATE ;
        VL_FREE_TIME,         PARAM.FREE_TIME ;
        VL_FAULT_STATE,       PARAM.FAULT_STATE ;
        VL_ALARM_SUM,         PARAM.ALARM_SUM ;
        VL_SIF_DET_COMM_ERR,  PARAM.SIF_DET_COMM_ERR ;
        VL_SIF_ERROR,         PARAM.SIF_ERROR ;
        VL_SIF_SYNC_TOT_ERR,  PARAM.SIF_SYNC_TOT_ERR ;
    }
}

VARIABLE_LIST   __sif_res_view_4
{
    LABEL       [sif_res_view_4] ;
    HELP        [sif_res_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,          PARAM.ST_REV ;
        VL_STRATEGY,        PARAM.STRATEGY ;
        VL_ALERT_KEY,       PARAM.ALERT_KEY ;
        VL_MANUFAC_ID,      PARAM.MANUFAC_ID ;
        VL_DEV_TYPE,        PARAM.DEV_TYPE ;
        VL_DEV_REV,         PARAM.DEV_REV ;
        VL_DD_REV,          PARAM.DD_REV ;
        VL_HARD_TYPES,      PARAM.HARD_TYPES ;
        VL_FEATURES,        PARAM.FEATURES ;
        VL_CYCLE_TYPE,      PARAM.CYCLE_TYPE ;
        VL_MIN_CYCLE_T,     PARAM.MIN_CYCLE_T ;
        VL_MEMORY_SIZE,     PARAM.MEMORY_SIZE ;
        VL_MAX_NOTIFY,      PARAM.MAX_NOTIFY ;
        VL_ACK_OPTION,      PARAM.ACK_OPTION ;
        VL_WRITE_PRI,       PARAM.WRITE_PRI ;
        VL_ITK_VER,         PARAM.ITK_VER ;
        VL_MACRO_CYCLE_T,   PARAM.MACRO_CYCLE_T ;
        VL_SIF_SYNC_DRIFT,  PARAM.SIF_SYNC_DRIFT ;
        VL_SIF_SYNC_JITTER, PARAM.SIF_SYNC_JITTER ;
        VL_CONFIG_SIG,      PARAM.CONFIG_SIG ;
    	VL_CONFIG_SIG_CALC, PARAM.CONFIG_SIG_CALC ;
	    VL_FIRMWARE_SIG,    PARAM.FIRMWARE_SIG ;
	    VL_SIF_ITK_VER,     PARAM.SIF_ITK_VER ;
    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/*
**********************************************************************
** Refresh relations
**********************************************************************
*/
/*
**********************************************************************
** Response codes
**********************************************************************
*/
/*
**********************************************************************
** Write as one relations
**********************************************************************
*/
/*
**********************************************************************
** Edit displays
**********************************************************************
*/

/*
**********************************************************************
** no_download & upload_wanted collections
**********************************************************************
*/
#ifdef UD_LISTS
COLLECTION no_download_sif_res
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_sif_res
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
