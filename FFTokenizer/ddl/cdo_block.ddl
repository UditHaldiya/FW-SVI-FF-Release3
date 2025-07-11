/*
** @(#)cdo_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Complex DO block
** Filename: cdo_block.ddl
** Spec revision:       FF-900 FS 1.0 DDL spec
**                      FF-892 FS 1.5 FBAP spec part 3 (release)
**                      FF-892 PS 2.0 FBAP spec part 3 (beta)
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
** DBG   Revision 1.0  20020523
** FI    Revision 1.1  20051109
**       added block specific status options per AR#708
**       added block specific io options per AR#708
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
** Complex DO block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __COMPLEX_DO,
DEVICE_REVISION __COMPLEX_DO_beta_dev_rev,
DD_REVISION     __COMPLEX_DO_beta_dd_rev
/*
**********************************************************************
** Complex DO
** Definition of Complex DO Block
**********************************************************************
*/
BLOCK   __complex_do
{
        CHARACTERISTICS __cdo_character ;
        LABEL                              [complex_do_block] ;
        HELP                               [complex_do_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV_D,                       __pv_d ;
            SP_D,                       __sp_d ;
            OUT_D,                      __out_d ;
            SIMULATE_D,                 __simulate_discrete ;
            PV_STATE,                   __pv_state ;
            XD_STATE,                   __xd_state ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            IO_OPTS,                    __io_opts ;
            STATUS_OPTS,                __status_opts ;
            #else
            IO_OPTS,                    __io_opts_cdo ;
	    	STATUS_OPTS,                __status_opts_cdo ;
            #endif
            READBACK_D,                 __readback_d ;
            CAS_IN_D,                   __cas_in_d ;
            CHANNEL,                    __channel ;
            FSAFE_TIME,                 __fsafe_time ;
            FSAFE_VAL_D,                __fsafe_val_d ;
            BKCAL_OUT_D,                __bkcal_out_d ;
            RCAS_IN_D,                  __rcas_in_d ;
            SHED_OPT,                   __shed_opt ;
            RCAS_OUT_D,                 __rcas_out_d ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
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
            VIEW_1, __cdo_view_1 ;
            VIEW_2, __cdo_view_2 ;
            VIEW_3, __cdo_view_3 ;
            VIEW_4, __cdo_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_cdo
		,upload_wanted_cdo
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __cdo_character
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
VARIABLE_LIST   __cdo_view_1
{
        LABEL           [cdo_view_1] ;
        HELP            [cdo_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_SP_D,                         PARAM.SP_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_READBACK_D,                   PARAM.READBACK_D ;
            VL_CAS_IN_D,                     PARAM.CAS_IN_D ;
            VL_CHECKBACK,                    PARAM.CHECKBACK ;
        }
}

VARIABLE_LIST   __cdo_view_2
{
        LABEL           [cdo_view_2] ;
        HELP            [cdo_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_PV_STATE,                     PARAM.PV_STATE ;
            VL_XD_STATE,                     PARAM.XD_STATE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __cdo_view_3
{
        LABEL           [cdo_view_3] ;
        HELP            [cdo_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_SP_D,                         PARAM.SP_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_READBACK_D,                   PARAM.READBACK_D ;
            VL_CAS_IN_D,                     PARAM.CAS_IN_D ;
            VL_BKCAL_OUT_D,                  PARAM.BKCAL_OUT_D ;
            VL_RCAS_IN_D,                    PARAM.RCAS_IN_D ;
            VL_RCAS_OUT_D,                   PARAM.RCAS_OUT_D ;
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

VARIABLE_LIST   __cdo_view_4
{
        LABEL           [cdo_view_4] ;
        HELP            [cdo_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_IO_OPTS,                      PARAM.IO_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_CHANNEL,                      PARAM.CHANNEL ;
            VL_FSAFE_TIME,                   PARAM.FSAFE_TIME ;
            VL_FSAFE_VAL_D,                  PARAM.FSAFE_VAL_D ;
            VL_SHED_OPT,                     PARAM.SHED_OPT ;
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
COLLECTION no_download_cdo
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_cdo
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
