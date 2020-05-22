/*
** @(#)cao_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Complex AO block
** Filename: cao_block.ddl
** Spec revision:       FF-900 FS 5.0 DDL spec
**                      FF-892 FS 1.7 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
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
** DBG   Revision 1.0  20020523
** FI    Revision 1.1  20051109
**       added block specific status options per AR#708
**       added block specific io options per AR#708
** MS	 modified unit relations to resolve to correct attribute per AR#1991
** MS	 made changes per AR2351 using LIB2 macro def during tok 2007-07-17
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
** Complex AO block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __COMPLEX_AO,
DEVICE_REVISION __COMPLEX_AO_beta_dev_rev,
DD_REVISION     __COMPLEX_AO_beta_dd_rev
/*
**********************************************************************
** Complex AO
** Definition of Complex AO Block
**********************************************************************
*/
BLOCK   __complex_ao
{
        CHARACTERISTICS __cao_character ;
        LABEL                              [complex_ao_block] ;
        HELP                               [complex_ao_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV,                         __pv ;
            SP,                         __sp ;
            OUT,                        __out ;
            SIMULATE,                   __simulate_float ;
            PV_SCALE,                   __pv_scale ;
            XD_SCALE,                   __xd_scale ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            IO_OPTS,                    __io_opts ;
            STATUS_OPTS,                __status_opts ;
            #else
            IO_OPTS,                    __io_opts_cao ;
	    	STATUS_OPTS,                __status_opts_cao ;
            #endif
            READBACK,                   __readback ;
            CAS_IN,                     __cas_in ;
            SP_RATE_DN,                 __sp_rate_dn ;
            SP_RATE_UP,                 __sp_rate_up ;
            SP_HI_LIM,                  __sp_hi_lim ;
            SP_LO_LIM,                  __sp_lo_lim ;
            CHANNEL,                    __channel ;
            FSAFE_TIME,                 __fsafe_time ;
            FSAFE_VAL,                  __fsafe_val ;
            BKCAL_OUT,                  __bkcal_out ;
            RCAS_IN,                    __rcas_in ;
            SHED_OPT,                   __shed_opt ;
            RCAS_OUT,                   __rcas_out ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            PV_STATE,                   __pv_state ;
            READBACK_D,                 __readback_d ;
            SAFEGUARD_OP,               __safeguard_op ;
            SAFEGUARD_CL,               __safeguard_cl ;
            BINARY_OP,                  __binary_op ;
            BINARY_CL,                  __binary_cl ;
            OP_CMD_CXO,                 __op_cmd_cxo ;
            EN_OPEN,                    __en_open ;
            EN_CLOSE,                   __en_close ;
            CHECKBACK,                  __checkback ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __cao_view_1 ;
            VIEW_2, __cao_view_2 ;
            VIEW_3, __cao_view_3 ;
            VIEW_4, __cao_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_cao_pv
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_cao
		,upload_wanted_cao
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __cao_character
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
VARIABLE_LIST   __cao_view_1
{
        LABEL           [cao_view_1] ;
        HELP            [cao_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_SP,                           PARAM.SP ;
            VL_OUT,                          PARAM.OUT ;
            VL_READBACK,                     PARAM.READBACK ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
            VL_READBACK_D,                   PARAM.READBACK_D ;
            VL_CHECKBACK,                    PARAM.CHECKBACK ;
        }
}

VARIABLE_LIST   __cao_view_2
{
        LABEL           [cao_view_2] ;
        HELP            [cao_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_PV_SCALE,                     PARAM.PV_SCALE ;
            VL_XD_SCALE,                     PARAM.XD_SCALE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_SP_HI_LIM,                    PARAM.SP_HI_LIM ;
            VL_SP_LO_LIM,                    PARAM.SP_LO_LIM ;
            VL_PV_STATE,                     PARAM.PV_STATE ;
        }
}

VARIABLE_LIST   __cao_view_3
{
        LABEL           [cao_view_3] ;
        HELP            [cao_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_SP,                           PARAM.SP ;
            VL_OUT,                          PARAM.OUT ;
            VL_READBACK,                     PARAM.READBACK ;
            VL_CAS_IN,                       PARAM.CAS_IN ;
            VL_BKCAL_OUT,                    PARAM.BKCAL_OUT ;
            VL_RCAS_IN,                      PARAM.RCAS_IN ;
            VL_RCAS_OUT,                     PARAM.RCAS_OUT ;
            VL_READBACK_D,                   PARAM.READBACK_D ;
            VL_SAFEGUARD_OP,                 PARAM.SAFEGUARD_OP ;
            VL_SAFEGUARD_CL,                 PARAM.SAFEGUARD_CL ;
            VL_BINARY_OP,                    PARAM.BINARY_OP ;
            VL_BINARY_CL,                    PARAM.BINARY_CL ;
            VL_OP_CMD_CXO,                   PARAM.OP_CMD_CXO ;
            VL_EN_OPEN,                      PARAM.EN_OPEN ;
            VL_EN_CLOSE,                     PARAM.EN_CLOSE ;
            VL_CHECKBACK,                    PARAM.CHECKBACK ;
        }
}

VARIABLE_LIST   __cao_view_4
{
        LABEL           [cao_view_4] ;
        HELP            [cao_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_IO_OPTS,                      PARAM.IO_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_SP_RATE_DN,                   PARAM.SP_RATE_DN ;
            VL_SP_RATE_UP,                   PARAM.SP_RATE_UP ;
            VL_CHANNEL,                      PARAM.CHANNEL ;
            VL_FSAFE_TIME,                   PARAM.FSAFE_TIME ;
            VL_FSAFE_VAL,                    PARAM.FSAFE_VAL ;
            VL_SHED_OPT,                     PARAM.SHED_OPT ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_cao_pv {
    PARAM.PV_SCALE.UNITS_INDEX : PARAM.PV.VALUE,
            PARAM.PV_STATE
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
COLLECTION no_download_cao
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_cao
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
