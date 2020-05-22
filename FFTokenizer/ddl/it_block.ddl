/*
** @(#)it_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Integrator block
** Filename: it_block.ddl
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
**       fixed unit relations per AR#1621
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
** Integrator block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __INTEGRATOR,
DEVICE_REVISION __INTEGRATOR_rel_dev_rev,
DD_REVISION     __INTEGRATOR_rel_dd_rev
/*
**********************************************************************
** Integrator
** Definition of Integrator Block
**********************************************************************
*/
BLOCK   __integrator
{
        CHARACTERISTICS __it_character ;
        LABEL                              [integrator_block] ;
        HELP                               [integrator_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            TOTAL_SP,                   __total_sp ;
            OUT,                        __out ;
            OUT_RANGE,                  __out_range ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_it ;
            #endif
            IN_1,                       __in_1 ;
            IN_2,                       __in_2 ;
            OUT_TRIP,                   __out_trip ;
            OUT_PTRIP,                  __out_ptrip ;
            TIME_UNIT1,                 __time_unit1 ;
            TIME_UNIT2,                 __time_unit2 ;
            UNIT_CONV,                  __unit_conv ;
            PULSE_VAL1,                 __pulse_val1 ;
            PULSE_VAL2,                 __pulse_val2 ;
            REV_FLOW1,                  __rev_flow1 ;
            REV_FLOW2,                  __rev_flow2 ;
            RESET_IN,                   __reset_in ;
            STOTAL,                     __stotal ;
            RTOTAL,                     __rtotal ;
            SRTOTAL,                    __srtotal ;
            SSP,                        __ssp ;
            INTEG_TYPE,                 __integ_type ;
            INTEG_OPTS,                 __integ_opts ;
            CLOCK_PER,                  __clock_per ;
            PRE_TRIP,                   __pre_trip ;
            N_RESET,                    __n_reset ;
            PCT_INCL,                   __pct_incl ;
            GOOD_LIM,                   __good_lim ;
            UNCERT_LIM,                 __uncert_lim ;
            OP_CMD_INT,                 __op_cmd_int ;
            OUTAGE_LIM,                 __outage_lim ;
            RESET_CONFIRM,              __reset_confirm ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __it_view_1 ;
            VIEW_2, __it_view_2 ;
            VIEW_3, __it_view_3 ;
            VIEW_4, __it_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_it_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_it
		,upload_wanted_it
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __it_character
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
VARIABLE_LIST   __it_view_1
{
        LABEL           [it_view_1] ;
        HELP            [it_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_TOTAL_SP,                     PARAM.TOTAL_SP ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_OUT_TRIP,                     PARAM.OUT_TRIP ;
            VL_OUT_PTRIP,                    PARAM.OUT_PTRIP ;
            VL_REV_FLOW1,                    PARAM.REV_FLOW1 ;
            VL_REV_FLOW2,                    PARAM.REV_FLOW2 ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
            VL_RTOTAL,                       PARAM.RTOTAL ;
            VL_N_RESET,                      PARAM.N_RESET ;
            VL_PCT_INCL,                     PARAM.PCT_INCL ;
            VL_OP_CMD_INT,                   PARAM.OP_CMD_INT ;
            VL_RESET_CONFIRM,                PARAM.RESET_CONFIRM ;
        }
}

VARIABLE_LIST   __it_view_2
{
        LABEL           [it_view_2] ;
        HELP            [it_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_TIME_UNIT1,                   PARAM.TIME_UNIT1 ;
            VL_TIME_UNIT2,                   PARAM.TIME_UNIT2 ;
        }
}

VARIABLE_LIST   __it_view_3
{
        LABEL           [it_view_3] ;
        HELP            [it_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_TOTAL_SP,                     PARAM.TOTAL_SP ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_OUT_TRIP,                     PARAM.OUT_TRIP ;
            VL_OUT_PTRIP,                    PARAM.OUT_PTRIP ;
            VL_REV_FLOW1,                    PARAM.REV_FLOW1 ;
            VL_REV_FLOW2,                    PARAM.REV_FLOW2 ;
            VL_RESET_IN,                     PARAM.RESET_IN ;
            VL_STOTAL,                       PARAM.STOTAL ;
            VL_RTOTAL,                       PARAM.RTOTAL ;
            VL_SRTOTAL,                      PARAM.SRTOTAL ;
            VL_SSP,                          PARAM.SSP ;
            VL_N_RESET,                      PARAM.N_RESET ;
            VL_PCT_INCL,                     PARAM.PCT_INCL ;
            VL_OP_CMD_INT,                   PARAM.OP_CMD_INT ;
            VL_RESET_CONFIRM,                PARAM.RESET_CONFIRM ;
        }
}

VARIABLE_LIST   __it_view_4
{
        LABEL           [it_view_4] ;
        HELP            [it_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_UNIT_CONV,                    PARAM.UNIT_CONV ;
            VL_PULSE_VAL1,                   PARAM.PULSE_VAL1 ;
            VL_PULSE_VAL2,                   PARAM.PULSE_VAL2 ;
            VL_INTEG_TYPE,                   PARAM.INTEG_TYPE ;
            VL_INTEG_OPTS,                   PARAM.INTEG_OPTS ;
            VL_CLOCK_PER,                    PARAM.CLOCK_PER ;
            VL_PRE_TRIP,                     PARAM.PRE_TRIP ;
            VL_GOOD_LIM,                     PARAM.GOOD_LIM ;
            VL_UNCERT_LIM,                   PARAM.UNCERT_LIM ;
            VL_OUTAGE_LIM,                   PARAM.OUTAGE_LIM ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_it_out {
    PARAM.OUT_RANGE.UNITS_INDEX : PARAM.OUT.VALUE,
            PARAM.TOTAL_SP,
            PARAM.STOTAL,
            PARAM.RTOTAL,
            PARAM.SRTOTAL,
            PARAM.SSP,
            PARAM.PRE_TRIP
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
COLLECTION no_download_it
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_it
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
