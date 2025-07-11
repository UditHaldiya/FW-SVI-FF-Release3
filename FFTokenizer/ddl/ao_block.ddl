/*
** @(#)ao_block.ddl 1.2 1999-03-04
**
** FF standard Analog Output block
** Filename: ao_block.ddl
** Spec revision:   FF-900 FS 1.0  DDL spec
**                  FF-890 FS 1.0 FBAP spec part 1
**                  FF-891 FS 1.0 FBAP spec part 2
** Date of last change: 2005-11-09
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
** (c) Fieldbus Foundation(TM) (1994-2005)
**
*/

/*
** HISTORY:
**  JPH Revision 0.9  19950515
**  TAB Revision 1.0  19961015
**  QLQ Revision 1.1  19970915 (changed all fail-safe to fault-state)
**  DAD Revision 1.2  1999-03-04
**  FI  Revision 1.3  20051109
**      added block specific status options per AR#708
**      added block specific io options per AR#708
**      fixed unit relations per AR#700
** MS	made changes per AR2351 using LIB2 macro def during tok 2007-07-17
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
** Analog Output block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __AO_BLOCK,
DEVICE_REVISION __AO_BLOCK_rel_dev_rev,
DD_REVISION     __AO_BLOCK_rel_dd_rev

/*
**********************************************************************
** Analog Output
** Definition of an analog output block
**********************************************************************
*/
BLOCK   __analog_output_block
{
    CHARACTERISTICS     __ao_character ;
    LABEL               [analog_output_block] ;
    HELP                [analog_output_block_help] ;
    PARAMETERS
    {
        ST_REV,         __st_rev ;
        TAG_DESC,       __tag_desc ;
        STRATEGY,       __strategy ;
        ALERT_KEY,      __alert_key ;
        MODE_BLK,       __mode_blk ;
        BLOCK_ERR,      __block_err ;
        PV,             __pv ;
        SP,             __sp ;
        OUT,            __out ;
        SIMULATE,       __simulate_float ;
        PV_SCALE,       __pv_scale ;
        XD_SCALE,       __xd_scale ;
        GRANT_DENY,     __grant_deny ;
        #ifdef LIB2
        IO_OPTS,        __io_opts ;
        STATUS_OPTS,    __status_opts ;
        #else
        IO_OPTS,        __io_opts_ao ;
		STATUS_OPTS,    __status_opts_ao ;
        #endif
        READBACK,       __readback ;
        CAS_IN,         __cas_in ;
        SP_RATE_DN,     __sp_rate_dn ;
        SP_RATE_UP,     __sp_rate_up ;
        SP_HI_LIM,      __sp_hi_lim ;
        SP_LO_LIM,      __sp_lo_lim ;
        CHANNEL,        __channel ;
        FSTATE_TIME,    __fstate_time ;
        FSTATE_VAL,     __fstate_val ;
        BKCAL_OUT,      __bkcal_out ;
        RCAS_IN,        __rcas_in ;
        SHED_OPT,       __shed_opt ;
        RCAS_OUT,       __rcas_out ;
        UPDATE_EVT,     __update_evt ;
        BLOCK_ALM,      __block_alm ;
    }
    PARAMETER_LISTS
    {
        VIEW_1, __ao_view_1 ;
        VIEW_2, __ao_view_2 ;
        VIEW_3, __ao_view_3 ;
        VIEW_4, __ao_view_4 ;
    }
    UNIT_ITEMS
    {
        __unit_ao_pv,
        __unit_ao_xd
    }
    
    #ifdef UD_LISTS
    COLLECTION_ITEMS
    {
    	no_download_ao
    	,upload_wanted_ao
    }
    #endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ao_character
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
VARIABLE_LIST   __ao_view_1
{
    LABEL       [ao_view_1] ;
    HELP        [ao_view_1_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_MODE_BLK,    PARAM.MODE_BLK ;
        VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        VL_PV,          PARAM.PV ;
        VL_SP,          PARAM.SP ;
        VL_OUT,         PARAM.OUT ;
        VL_READBACK,    PARAM.READBACK ;
        VL_CAS_IN,      PARAM.CAS_IN ;
    }
}

VARIABLE_LIST   __ao_view_2
{
    LABEL       [ao_view_2] ;
    HELP        [ao_view_2_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_PV_SCALE,    PARAM.PV_SCALE ;
        VL_XD_SCALE,    PARAM.XD_SCALE ;
        VL_GRANT_DENY,  PARAM.GRANT_DENY ;
        VL_SP_HI_LIM,   PARAM.SP_HI_LIM ;
        VL_SP_LO_LIM,   PARAM.SP_LO_LIM ;
    }
}

VARIABLE_LIST   __ao_view_3
{
    LABEL       [ao_view_3] ;
    HELP        [ao_view_3_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_MODE_BLK,    PARAM.MODE_BLK ;
        VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        VL_PV,          PARAM.PV ;
        VL_SP,          PARAM.SP ;
        VL_OUT,         PARAM.OUT ;
        VL_READBACK,    PARAM.READBACK ;
        VL_CAS_IN,      PARAM.CAS_IN ;
        VL_BKCAL_OUT,   PARAM.BKCAL_OUT ;
        VL_RCAS_IN,     PARAM.RCAS_IN ;
        VL_RCAS_OUT,    PARAM.RCAS_OUT ;
    }
}

VARIABLE_LIST   __ao_view_4
{
    LABEL       [ao_view_4] ;
    HELP        [ao_view_4_help] ;
    MEMBERS
    {
        VL_ST_REV,      PARAM.ST_REV ;
        VL_STRATEGY,    PARAM.STRATEGY ;
        VL_ALERT_KEY,   PARAM.ALERT_KEY ;
        VL_IO_OPTS,     PARAM.IO_OPTS ;
        VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
        VL_SP_RATE_DN,  PARAM.SP_RATE_DN ;
        VL_SP_RATE_UP,  PARAM.SP_RATE_UP ;
        VL_CHANNEL,     PARAM.CHANNEL ;
        VL_FSTATE_TIME, PARAM.FSTATE_TIME ;
        VL_FSTATE_VAL,  PARAM.FSTATE_VAL ;
        VL_SHED_OPT,    PARAM.SHED_OPT ;
    }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_ao_pv
{
    PARAM.PV_SCALE.UNITS_INDEX :
        PARAM.PV.VALUE,
        PARAM.SP.VALUE,
        PARAM.PV_SCALE.EU_100,
        PARAM.PV_SCALE.EU_0,
        PARAM.CAS_IN.VALUE,
        PARAM.SP_HI_LIM,
        PARAM.SP_LO_LIM,
        PARAM.BKCAL_OUT.VALUE,
        PARAM.RCAS_IN.VALUE,
        PARAM.RCAS_OUT.VALUE
}

UNIT    __unit_ao_xd
{
    PARAM.XD_SCALE.UNITS_INDEX :
        PARAM.OUT.VALUE,
        PARAM.XD_SCALE.EU_100,
        PARAM.XD_SCALE.EU_0,
        PARAM.READBACK.VALUE,
        PARAM.SIMULATE.TRANSDUCER_VALUE,
        PARAM.SIMULATE.SIMULATE_VALUE,
        PARAM.FSTATE_VAL
}
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
COLLECTION no_download_ao
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ao
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
