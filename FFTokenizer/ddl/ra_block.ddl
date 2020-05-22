/*
** @(#)ra_block.ddl     1.1 1999-03-04
**
** FF standard Ratio block
** Filename: ra_block.ddl
** Spec revision:       FF-900 FS 1.0  DDL spec
**                FF-890 FS 1.0 FBAP spec part 1
**                FF-891 FS 1.0 FBAP spec part 2
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
** JPH   Revision 0.9  19950515
** TAB   Revision 1.0  19961015
** DAD   Revision 1.1  1999-03-04
**       added new number system for dev rev and dd rev
** FI    Revision 1.1  20051109
**       added block specific status options per AR#708
**       added block specific control options per AR#708
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
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
** Ratio block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RA_BLOCK,
DEVICE_REVISION __RA_BLOCK_rel_dev_rev,
DD_REVISION     __RA_BLOCK_rel_dd_rev

/*
**********************************************************************
** Ratio
** Definition of a ratio block
**********************************************************************
*/
BLOCK      __ratio_block
{
        CHARACTERISTICS     __ra_character ;
        LABEL                           [ratio_block] ;
        HELP                            [ratio_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
                PV,                     __pv ;
                SP,                     __sp ;
                OUT,                    __out ;
                PV_SCALE,               __pv_scale ;
                OUT_SCALE,              __out_scale ;
                GRANT_DENY,             __grant_deny ;
                #ifdef LIB2
                CONTROL_OPTS,   	__control_opts ;
                STATUS_OPTS,    	__status_opts ;
                #else
                CONTROL_OPTS,   	__control_opts_ra ;
                STATUS_OPTS,    	__status_opts_ra ;
                #endif
                IN,                     __in ;
                PV_FTIME,               __pv_ftime ;
                IN_1,                   __in_1 ;
                RA_FTIME,               __ra_ftime ;
                CAS_IN,                 __cas_in ;
                SP_RATE_DN,             __sp_rate_dn ;
                SP_RATE_UP,             __sp_rate_up ;
                SP_HI_LIM,              __sp_hi_lim ;
                SP_LO_LIM,              __sp_lo_lim ;
                GAIN,                   __gain ;
                BKCAL_IN,               __bkcal_in ;
                OUT_HI_LIM,             __out_hi_lim ;
                OUT_LO_LIM,             __out_lo_lim ;
                BKCAL_OUT,              __bkcal_out ;
                BAL_TIME,               __bal_time ;
                RCAS_IN,                __rcas_in ;
                SHED_OPT,               __shed_opt ;
                RCAS_OUT,               __rcas_out ;
                TRK_SCALE,              __trk_scale ;
                TRK_IN_D,               __trk_in_d ;
                TRK_VAL,                __trk_val ;
                UPDATE_EVT,             __update_evt ;
                BLOCK_ALM,              __block_alm ;
                #ifdef LIB2
                ALARM_SUM,              __alarm_sum ;
                ACK_OPTION,             __ack_option ;
                #else
                ALARM_SUM,              __alarm_sum_ra ;
                ACK_OPTION,             __ack_option_ra ;
                #endif
                ALARM_HYS,              __alarm_hys ;
                HI_HI_PRI,              __hi_hi_pri ;
                HI_HI_LIM,              __hi_hi_lim ;
                HI_PRI,                 __hi_pri ;
                HI_LIM,                 __hi_lim ;
                LO_PRI,                 __lo_pri ;
                LO_LIM,                 __lo_lim ;
                LO_LO_PRI,              __lo_lo_pri ;
                LO_LO_LIM,              __lo_lo_lim ;
                DV_HI_PRI,              __dv_hi_pri ;
                DV_HI_LIM,              __dv_hi_lim ;
                DV_LO_PRI,              __dv_lo_pri ;
                DV_LO_LIM,              __dv_lo_lim ;
                HI_HI_ALM,              __hi_hi_alm ;
                HI_ALM,                 __hi_alm ;
                LO_ALM,                 __lo_alm ;
                LO_LO_ALM,              __lo_lo_alm ;
                DV_HI_ALM,              __dv_hi_alm ;
                DV_LO_ALM,              __dv_lo_alm ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __ra_view_1 ;
                VIEW_2, __ra_view_2 ;
                VIEW_3, __ra_view_3 ;
                VIEW_4, __ra_view_4 ;
        }
        UNIT_ITEMS
        {
                __unit_ra_pv,
                __unit_ra_out,
                __unit_ra_trk
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_ra
		,upload_wanted_ra
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ra_character
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
VARIABLE_LIST   __ra_view_1
{
        LABEL           [ra_view_1] ;
        HELP            [ra_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,                  PARAM.PV ;
                VL_SP,                  PARAM.SP ;
                VL_OUT,                 PARAM.OUT ;
                VL_CAS_IN,              PARAM.CAS_IN ;
                VL_TRK_IN_D,    PARAM.TRK_IN_D ;
                VL_TRK_VAL,             PARAM.TRK_VAL ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __ra_view_2
{
        LABEL           [ra_view_2] ;
        HELP            [ra_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_PV_SCALE,    PARAM.PV_SCALE ;
                VL_OUT_SCALE,   PARAM.OUT_SCALE ;
                VL_GRANT_DENY,  PARAM.GRANT_DENY ;
                VL_SP_HI_LIM,   PARAM.SP_HI_LIM ;
                VL_SP_LO_LIM,   PARAM.SP_LO_LIM ;
                VL_OUT_HI_LIM,  PARAM.OUT_HI_LIM ;
                VL_OUT_LO_LIM,  PARAM.OUT_LO_LIM ;
        }
}

VARIABLE_LIST   __ra_view_3
{
        LABEL           [ra_view_3] ;
        HELP            [ra_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,              PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,                  PARAM.PV ;
                VL_SP,                  PARAM.SP ;
                VL_OUT,                 PARAM.OUT ;
                VL_IN,                  PARAM.IN ;
                VL_IN_1,                   PARAM.IN_1 ;
                VL_CAS_IN,              PARAM.CAS_IN ;
                VL_BKCAL_IN,    PARAM.BKCAL_IN ;
                VL_BKCAL_OUT,   PARAM.BKCAL_OUT ;
                VL_RCAS_IN,             PARAM.RCAS_IN ;
                VL_RCAS_OUT,    PARAM.RCAS_OUT ;
                VL_TRK_IN_D,    PARAM.TRK_IN_D ;
                VL_TRK_VAL,             PARAM.TRK_VAL ;
                VL_ALARM_SUM,   PARAM.ALARM_SUM ;
        }
}

VARIABLE_LIST   __ra_view_4
{
        LABEL           [ra_view_4] ;
        HELP            [ra_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,                      PARAM.ST_REV ;
                VL_STRATEGY,            PARAM.STRATEGY ;
                VL_ALERT_KEY,           PARAM.ALERT_KEY ;
                VL_CONTROL_OPTS,        PARAM.CONTROL_OPTS ;
                VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
                VL_PV_FTIME,            PARAM.PV_FTIME ;
                VL_RA_FTIME,            PARAM.RA_FTIME ;
                VL_SP_RATE_DN,          PARAM.SP_RATE_DN ;
                VL_SP_RATE_UP,          PARAM.SP_RATE_UP ;
                VL_GAIN,                           PARAM.GAIN ;
                VL_BAL_TIME,            PARAM.BAL_TIME ;
                VL_SHED_OPT,            PARAM.SHED_OPT ;
                VL_TRK_SCALE,           PARAM.TRK_SCALE ;
                VL_ACK_OPTION,          PARAM.ACK_OPTION ;
                VL_ALARM_HYS,           PARAM.ALARM_HYS ;
                VL_HI_HI_PRI,           PARAM.HI_HI_PRI ;
                VL_HI_HI_LIM,           PARAM.HI_HI_LIM ;
                VL_HI_PRI,                      PARAM.HI_PRI ;
                VL_HI_LIM,                      PARAM.HI_LIM ;
                VL_LO_PRI,                      PARAM.LO_PRI ;
                VL_LO_LIM,                      PARAM.LO_LIM ;
                VL_LO_LO_PRI,           PARAM.LO_LO_PRI ;
                VL_LO_LO_LIM,           PARAM.LO_LO_LIM ;
                VL_DV_HI_PRI,           PARAM.DV_HI_PRI ;
                VL_DV_HI_LIM,           PARAM.DV_HI_LIM ;
                VL_DV_LO_PRI,           PARAM.DV_LO_PRI ;
                VL_DV_LO_LIM,           PARAM.DV_LO_LIM ;
        }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT    __unit_ra_pv
{
        PARAM.PV_SCALE.UNITS_INDEX :
                PARAM.PV.VALUE,
                PARAM.SP.VALUE,
                PARAM.PV_SCALE.EU_100,
                PARAM.PV_SCALE.EU_0,
                PARAM.IN.VALUE,
                PARAM.CAS_IN.VALUE,
                PARAM.SP_HI_LIM,
                PARAM.SP_LO_LIM,
                PARAM.BKCAL_OUT.VALUE,
                PARAM.RCAS_IN.VALUE,
                PARAM.RCAS_OUT.VALUE,
                PARAM.HI_HI_LIM,
                PARAM.HI_LIM,
                PARAM.LO_LIM,
                PARAM.LO_LO_LIM,
                PARAM.DV_HI_LIM,
                PARAM.DV_LO_LIM,
                PARAM.HI_HI_ALM.VALUE,
                PARAM.HI_ALM.VALUE,
                PARAM.LO_ALM.VALUE,
                PARAM.LO_LO_ALM.VALUE,
                PARAM.DV_HI_ALM.VALUE,
                PARAM.DV_LO_ALM.VALUE
}

UNIT    __unit_ra_out
{
        PARAM.OUT_SCALE.UNITS_INDEX :
                PARAM.OUT.VALUE,
                PARAM.OUT_SCALE.EU_100,
                PARAM.OUT_SCALE.EU_0,
                PARAM.IN_1.VALUE,
                PARAM.BKCAL_IN.VALUE,
                PARAM.OUT_HI_LIM,
                PARAM.OUT_LO_LIM
}

UNIT    __unit_ra_trk
{
        PARAM.TRK_SCALE.UNITS_INDEX :
                PARAM.TRK_SCALE.EU_100,
                PARAM.TRK_SCALE.EU_0,
                PARAM.TRK_VAL.VALUE
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
COLLECTION no_download_ra
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ra
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
