/*
** @(#)do_block.ddl 1.2 1999-03-04
**
** FF standard Discrete Output block
** Filename: do_block.ddl
** Spec revision:   FF-900 FS 5.0  DDL spec
**                  FF-890 FS 1.7 FBAP spec part 1
**                  FF-891 FS 1.7 FBAP spec part 2
** Date of last change: 2006-05-16
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
** (c) Fieldbus Foundation(TM) (1994-2006)
**
*/

/*
** HISTORY:
**  JPH Revision 0.9  19950515
**  TAB Revision 1.0  19961015
**  QLQ Revision 1.1  19970915  (changed all fail-safe to fault-state)
**  DAD Revision 1.2  1999-03-04
**      added new rev numbering system for dev rev and dd rev
**  FI  Revision 1.3  20051109
**      added block specific status options per AR#708
**      added block specific io options per AR#708
**      fixed unit relations per ARs 701 and 1538
**  MS	commented out UNIT_ITEMS ref. & def. per AR#1991
**  MS	made changes per AR2351 using LIB2 macro def during tok 2007-07-17
** MS   ARs 2901 -- 2008.10.07
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Discrete Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __DO_BLOCK,
DEVICE_REVISION __DO_BLOCK_rel_dev_rev,
DD_REVISION     __DO_BLOCK_rel_dd_rev

/*
**********************************************************************
** Discrete Output
** Definition of an discrete output block
**********************************************************************
*/
BLOCK   __discrete_output_block
{
    CHARACTERISTICS     __do_character ;
    LABEL               [discrete_output_block] ;
    HELP                [discrete_output_block_help] ;
    PARAMETERS
    {
        ST_REV,         __st_rev ;
        TAG_DESC,       __tag_desc ;
        STRATEGY,       __strategy ;
        ALERT_KEY,      __alert_key ;
        MODE_BLK,       __mode_blk ;
        BLOCK_ERR,      __block_err ;
        PV_D,           __pv_d ;
        SP_D,           __sp_d ;
        OUT_D,          __out_d ;
        SIMULATE_D,     __simulate_discrete ;
        PV_STATE,       __pv_state ;
        XD_STATE,       __xd_state ;
        GRANT_DENY,     __grant_deny ;
        #ifdef LIB2
        IO_OPTS,        __io_opts ;
        STATUS_OPTS,    __status_opts ;
        #else
        IO_OPTS,        __io_opts_do ;
        STATUS_OPTS,    __status_opts_do ;
        #endif
        READBACK_D,     __readback_d ;
        CAS_IN_D,       __cas_in_d ;
        CHANNEL,        __channel ;
        FSTATE_TIME,    __fstate_time ;
        FSTATE_VAL_D,   __fstate_val_d ;
        BKCAL_OUT_D,    __bkcal_out_d ;
        RCAS_IN_D,      __rcas_in_d ;
        SHED_OPT,       __shed_opt ;
        RCAS_OUT_D,     __rcas_out_d ;
        UPDATE_EVT,     __update_evt ;
        BLOCK_ALM,      __block_alm ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __do_view_1 ;
        VIEW_2, __do_view_2 ;
        VIEW_3, __do_view_3 ;
        VIEW_4, __do_view_4 ;
    }
    /*UNIT_ITEMS
    {
        __unit_do_pv,
        __unit_do_xd
    }*/
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_do
    	,upload_wanted_do
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __do_character
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
VARIABLE_LIST   __do_view_1
{
    LABEL       [do_view_1] ;
    HELP        [do_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_MODE_BLK,    PARAM.MODE_BLK ;
        VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        VL_PV_D,        PARAM.PV_D ;
        VL_SP_D,        PARAM.SP_D ;
        VL_OUT_D,       PARAM.OUT_D ;
        VL_READBACK_D,  PARAM.READBACK_D ;
        VL_CAS_IN_D,    PARAM.CAS_IN_D ;
    }
}

VARIABLE_LIST   __do_view_2
{
    LABEL       [do_view_2] ;
    HELP        [do_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_PV_STATE,    PARAM.PV_STATE ;
        VL_XD_STATE,    PARAM.XD_STATE ;
        VL_GRANT_DENY,  PARAM.GRANT_DENY ;
    }
}

VARIABLE_LIST   __do_view_3
{
    LABEL       [do_view_3] ;
    HELP        [do_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_MODE_BLK,    PARAM.MODE_BLK ;
        VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        VL_PV_D,        PARAM.PV_D ;
        VL_SP_D,        PARAM.SP_D ;
        VL_OUT_D,       PARAM.OUT_D ;
        VL_READBACK_D,  PARAM.READBACK_D ;
        VL_CAS_IN_D,    PARAM.CAS_IN_D ;
        VL_BKCAL_OUT_D, PARAM.BKCAL_OUT_D ;
        VL_RCAS_IN_D,   PARAM.RCAS_IN_D ;
        VL_RCAS_OUT_D,  PARAM.RCAS_OUT_D ;
    }
}

VARIABLE_LIST   __do_view_4
{
    LABEL       [do_view_4] ;
    HELP        [do_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,       PARAM.ST_REV ;
        VL_STRATEGY,     PARAM.STRATEGY ;
        VL_ALERT_KEY,    PARAM.ALERT_KEY ;
        VL_IO_OPTS,      PARAM.IO_OPTS ;
        VL_STATUS_OPTS,  PARAM.STATUS_OPTS ;
        VL_CHANNEL,      PARAM.CHANNEL ;
        VL_FSTATE_TIME,  PARAM.FSTATE_TIME ;
        VL_FSTATE_VAL_D, PARAM.FSTATE_VAL_D ;
        VL_SHED_OPT,     PARAM.SHED_OPT ;
    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/*UNIT    __unit_do_pv
{
    PARAM.PV_STATE :
        PARAM.PV_D.VALUE,
        PARAM.SP_D.VALUE,
        PARAM.CAS_IN_D.VALUE,
        PARAM.BKCAL_OUT_D.VALUE,
        PARAM.RCAS_IN_D.VALUE,
        PARAM.RCAS_OUT_D.VALUE
}

UNIT    __unit_do_xd
{
    PARAM.XD_STATE :
        PARAM.OUT_D.VALUE,
        PARAM.READBACK_D.VALUE,
        PARAM.SIMULATE_D.TRANSDUCER_VALUE,
        PARAM.SIMULATE_D.SIMULATE_VALUE,
        PARAM.FSTATE_VAL_D
}*/
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
COLLECTION no_download_do
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_do
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
