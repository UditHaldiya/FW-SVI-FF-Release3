/*
** @(#)tmr_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Timer block
** Filename: tmr_block.ddl
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
** Timer block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __TIMER,
DEVICE_REVISION __TIMER_rel_dev_rev,
DD_REVISION     __TIMER_rel_dd_rev
/*
**********************************************************************
** Timer
** Definition of Timer Block
**********************************************************************
*/
BLOCK   __timer
{
        CHARACTERISTICS __tmr_character ;
        LABEL                              [timer_block] ;
        HELP                               [timer_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV_D,                       __pv_d ;
            OUT_D,                      __out_d ;
            TIMER_SP,                   __timer_sp ;
            PV_STATE,                   __pv_state ;
            OUT_STATE,                  __out_state ;
            GRANT_DENY,                 __grant_deny ;
            INVERT_OPTS,                __invert_opts ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_tmr ;
            #endif
            IN_D1,                      __in_d1 ;
            IN_D2,                      __in_d2 ;
            IN_D3,                      __in_d3 ;
            IN_D4,                      __in_d4 ;
            COMB_TYPE,                  __comb_type ;
            TIMER_TYPE,                 __timer_type ;
            PRE_OUT_D,                  __pre_out_d ;
            N_START,                    __n_start ;
            OUT_EXP,                    __out_exp ;
            OUT_REM,                    __out_rem ;
            RESET_IN,                   __reset_in ;
            QUIES_OPT,                  __quies_opt ;
            TIME_UNITS,                 __time_units ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __tmr_view_1 ;
            VIEW_2, __tmr_view_2 ;
            VIEW_3, __tmr_view_3 ;
            VIEW_4, __tmr_view_4 ;
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_tmr
		,upload_wanted_tmr
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __tmr_character
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
VARIABLE_LIST   __tmr_view_1
{
        LABEL           [tmr_view_1] ;
        HELP            [tmr_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_TIMER_SP,                     PARAM.TIMER_SP ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D,                    PARAM.PRE_OUT_D ;
            VL_OUT_EXP,                      PARAM.OUT_EXP ;
            VL_OUT_REM,                      PARAM.OUT_REM ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
        }
}

VARIABLE_LIST   __tmr_view_2
{
        LABEL           [tmr_view_2] ;
        HELP            [tmr_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_PV_STATE,                     PARAM.PV_STATE ;
            VL_OUT_STATE,                    PARAM.OUT_STATE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __tmr_view_3
{
        LABEL           [tmr_view_3] ;
        HELP            [tmr_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV_D,                         PARAM.PV_D ;
            VL_OUT_D,                        PARAM.OUT_D ;
            VL_TIMER_SP,                     PARAM.TIMER_SP ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D,                    PARAM.PRE_OUT_D ;
            VL_N_START,                      PARAM.N_START ;
            VL_OUT_EXP,                      PARAM.OUT_EXP ;
            VL_OUT_REM,                      PARAM.OUT_REM ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
        }
}

VARIABLE_LIST   __tmr_view_4
{
        LABEL           [tmr_view_4] ;
        HELP            [tmr_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_INVERT_OPTS,                  PARAM.INVERT_OPTS ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_COMB_TYPE,                    PARAM.COMB_TYPE ;
            VL_TIMER_TYPE,                   PARAM.TIMER_TYPE ;
            VL_QUIES_OPT,                    PARAM.QUIES_OPT ;
            VL_TIME_UNITS,                   PARAM.TIME_UNITS ;
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
COLLECTION no_download_tmr
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_tmr
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
