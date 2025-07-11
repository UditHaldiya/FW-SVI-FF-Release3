/*
** @(#)sif_doblock.ddl 1.0 2007-09-30
**
** FF SIF Discrete Output block
** Filename: sif_doblock.ddl
** Spec revision: FF-900 FS 1.0 DDL spec
**                FF-807 FS 1.1 FF-SIS Application Model
**                FF-895 PS 1.1 FF-SIS Function Blocks Phase 1
** Date of last change: 2007-09-30
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
**  ED Revision 0.1 2007-09-30
**  ED Revision 1.0 2008-08-17
**     changed name of SIS parameters: __sis_reset_d (__sis_clear_latch_d)
** MS   ARs 2901 -- 2008.10.07
**  ED Revision --- 2008-12-03
**     removed FSTATE_TIME
**  ED Revision --- 2008-12-03 
**     Changed SIS to SIF
**  ED Revision --- 2010-01-12 
**     Added BKCAL_OUT_D to View 3 per AR4581
** MS   ARs 4538, 5248 -- 2010.07.14
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** SIF Discrete Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __SIF_DO_BLOCK,
DEVICE_REVISION __SIF_DO_BLOCK_rel_dev_rev,
DD_REVISION     __SIF_DO_BLOCK_rel_dd_rev

/*
**********************************************************************
** SIF Discrete Output
** Definition of a SIF discrete output block
**********************************************************************
*/
BLOCK   __sif_discrete_output_block
{
    CHARACTERISTICS     __sif_do_character ;
    LABEL               [sif_discrete_output_block] ;
    HELP                [sif_discrete_output_block_help] ;
    PARAMETERS
    {
        ST_REV,           __st_rev ;
        TAG_DESC,         __tag_desc ;
        STRATEGY,         __strategy ;
        ALERT_KEY,        __alert_key ;
        MODE_BLK,         __mode_blk ;
        BLOCK_ERR,        __block_err ;
        PV_D,             __pv_d ;
        SP_D,             __sp_d ;
        SIMULATE_D,       __simulate_discrete ;
        PV_STATE,         __pv_state ;
        XD_STATE,         __xd_state ;
        IO_OPTS,          __io_opts_do ;
        STATUS_OPTS,      __status_opts_do ;   
        CAS_IN_D,         __cas_in_d ;
        CHANNEL,          __channel ;
        STALE_DATA_T,     __stale_data_t ;
        CLEAR_LATCH_D,    __clear_latch_d ;
        OUT_D,            __out_d ;
        FSTATE_VAL_D,     __fstate_val_d ;
        BKCAL_OUT_D,      __bkcal_out_d ;
        READBACK_D,       __readback_d ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __sif_do_view_1 ;
        VIEW_2, __sif_do_view_2 ;
        VIEW_3, __sif_do_view_3 ;
        VIEW_4, __sif_do_view_4 ;
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_sif_do
    	,upload_wanted_sif_do
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __sif_do_character
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
VARIABLE_LIST   __sif_do_view_1
{
    LABEL       [sif_do_view_1] ;
    HELP        [sif_do_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,            PARAM.ST_REV ;
        VL_MODE_BLK,          PARAM.MODE_BLK ;
        VL_BLOCK_ERR,         PARAM.BLOCK_ERR ;
        VL_PV_D,              PARAM.PV_D ;
        VL_SP_D,              PARAM.SP_D ;
        VL_CAS_IN_D,          PARAM.CAS_IN_D ;
        VL_CLEAR_LATCH_D,     PARAM.CLEAR_LATCH_D ;
        VL_OUT_D,             PARAM.OUT_D ;
        VL_READBACK_D,        PARAM.READBACK_D ;

    }
}

VARIABLE_LIST   __sif_do_view_2
{
    LABEL       [sif_do_view_2] ;
    HELP        [sif_do_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,            PARAM.ST_REV ;
        VL_PV_STATE,          PARAM.PV_STATE ;
        VL_XD_STATE,          PARAM.XD_STATE ;
    }
}

VARIABLE_LIST   __sif_do_view_3
{
    LABEL       [sif_do_view_3] ;
    HELP        [sif_do_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,            PARAM.ST_REV ;
        VL_MODE_BLK,          PARAM.MODE_BLK ;
        VL_BLOCK_ERR,         PARAM.BLOCK_ERR ;
        VL_PV_D,              PARAM.PV_D ;
        VL_SP_D,              PARAM.SP_D ;
        VL_CAS_IN_D,          PARAM.CAS_IN_D ;
        VL_CLEAR_LATCH_D,     PARAM.CLEAR_LATCH_D ;
        VL_OUT_D,             PARAM.OUT_D ;
        VL_BKCAL_OUT_D,       PARAM.BKCAL_OUT_D ;
        VL_READBACK_D,        PARAM.READBACK_D ;
    }
}

VARIABLE_LIST   __sif_do_view_4
{
    LABEL       [sif_do_view_4] ;
    HELP        [sif_do_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,            PARAM.ST_REV ;
        VL_STRATEGY,          PARAM.STRATEGY ;
        VL_ALERT_KEY,         PARAM.ALERT_KEY ;
        VL_IO_OPTS,           PARAM.IO_OPTS ;
        VL_STATUS_OPTS,       PARAM.STATUS_OPTS ;
        VL_CHANNEL,           PARAM.CHANNEL ;
        VL_STALE_DATA_T,      PARAM.STALE_DATA_T ;
        VL_FSTATE_VAL_D,      PARAM.FSTATE_VAL_D ;
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
COLLECTION no_download_sif_do
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_sif_do
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif

