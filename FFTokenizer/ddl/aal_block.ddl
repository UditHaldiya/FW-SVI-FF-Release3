/*
** @(#)aal_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Analog Alarm block
** Filename: aal_block.ddl
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
**       added block specific alarm summary per AR#697
**       added block specific ack option per AR#1349
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
** Analog Alarm block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __ANALOG_ALARM,
DEVICE_REVISION __ANALOG_ALARM_rel_dev_rev,
DD_REVISION     __ANALOG_ALARM_rel_dd_rev
/*
**********************************************************************
** Analog Alarm
** Definition of Analog Alarm Block
**********************************************************************
*/
BLOCK   __analog_alarm
{
        CHARACTERISTICS __aal_character ;
        LABEL                              [analog_alarm_block] ;
        HELP                               [analog_alarm_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            PV,                         __pv ;
            OUT,                        __out ;
            OUT_RANGE,                  __out_range ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_aal ;
            #endif
            PV_FTIME,                   __pv_ftime ;
            IN,                         __in ;
            PSP,                        __psp ;
            HI_GAIN,                    __hi_gain ;
            LO_GAIN,                    __lo_gain ;
            HI_HI_BIAS,                 __hi_hi_bias ;
            HI_BIAS,                    __hi_bias ;
            LO_BIAS,                    __lo_bias ;
            LO_LO_BIAS,                 __lo_lo_bias ;
            PRE_OUT_ALM,                __pre_out_alm ;
            OUT_ALM,                    __out_alm ;
            OUT_ALM_SUM,                __out_alm_sum ;
            ALM_RATE_UP,                __alm_rate_up ;
            ALM_RATE_DN,                __alm_rate_dn ;
            EXPAND_UP,                  __expand_up ;
            EXPAND_DN,                  __expand_dn ;
            IGNORE_TIME,                __ignore_time ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            #ifdef LIB2
            ALARM_SUM,                  __alarm_sum ;
            ACK_OPTION,                 __ack_option ;
            #else
            ALARM_SUM,                  __alarm_sum_aal ;
            ACK_OPTION,                 __ack_option_aal ;
            #endif
            ALARM_HYS,                  __alarm_hys ;
            HI_HI_PRI,                  __hi_hi_pri ;
            HI_HI_LIM,                  __hi_hi_lim ;
            HI_HI_LIMX,                 __hi_hi_limx ;
            HI_PRI,                     __hi_pri ;
            HI_LIM,                     __hi_lim ;
            HI_LIMX,                    __hi_limx ;
            LO_PRI,                     __lo_pri ;
            LO_LIM,                     __lo_lim ;
            LO_LIMX,                    __lo_limx ;
            LO_LO_PRI,                  __lo_lo_pri ;
            LO_LO_LIM,                  __lo_lo_lim ;
            LO_LO_LIMX,                 __lo_lo_limx ;
            HI_HI_ALM,                  __hi_hi_alm ;
            HI_ALM,                     __hi_alm ;
            LO_ALM,                     __lo_alm ;
            LO_LO_ALM,                  __lo_lo_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __aal_view_1 ;
            VIEW_2, __aal_view_2 ;
            VIEW_3, __aal_view_3 ;
            VIEW_4, __aal_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_aal_out
        }
        
        #ifdef UD_LISTS
        COLLECTION_ITEMS
        {
		no_download_aal
		,upload_wanted_aal
	}
        #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __aal_character
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
VARIABLE_LIST   __aal_view_1
{
        LABEL           [aal_view_1] ;
        HELP            [aal_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_PSP,                          PARAM.PSP ;
            VL_PRE_OUT_ALM,                  PARAM.PRE_OUT_ALM ;
            VL_OUT_ALM,                      PARAM.OUT_ALM ;
            VL_EXPAND_UP,                    PARAM.EXPAND_UP ;
            VL_EXPAND_DN,                    PARAM.EXPAND_DN ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
            VL_HI_HI_LIMX,                   PARAM.HI_HI_LIMX ;
            VL_HI_LIMX,                      PARAM.HI_LIMX ;
            VL_LO_LIMX,                      PARAM.LO_LIMX ;
            VL_LO_LO_LIMX,                   PARAM.LO_LO_LIMX ;
        }
}

VARIABLE_LIST   __aal_view_2
{
        LABEL           [aal_view_2] ;
        HELP            [aal_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
            VL_HI_GAIN,                      PARAM.HI_GAIN ;
            VL_LO_GAIN,                      PARAM.LO_GAIN ;
            VL_HI_HI_BIAS,                   PARAM.HI_HI_BIAS ;
            VL_HI_BIAS,                      PARAM.HI_BIAS ;
            VL_LO_BIAS,                      PARAM.LO_BIAS ;
            VL_LO_LO_BIAS,                   PARAM.LO_LO_BIAS ;
        }
}

VARIABLE_LIST   __aal_view_3
{
        LABEL           [aal_view_3] ;
        HELP            [aal_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_IN,                           PARAM.IN ;
            VL_PSP,                          PARAM.PSP ;
            VL_PRE_OUT_ALM,                  PARAM.PRE_OUT_ALM ;
            VL_OUT_ALM,                      PARAM.OUT_ALM ;
            VL_EXPAND_UP,                    PARAM.EXPAND_UP ;
            VL_EXPAND_DN,                    PARAM.EXPAND_DN ;
            VL_ALARM_SUM,                    PARAM.ALARM_SUM ;
            VL_HI_HI_LIMX,                   PARAM.HI_HI_LIMX ;
            VL_HI_LIMX,                      PARAM.HI_LIMX ;
            VL_LO_LIMX,                      PARAM.LO_LIMX ;
            VL_LO_LO_LIMX,                   PARAM.LO_LO_LIMX ;
        }
}

VARIABLE_LIST   __aal_view_4
{
        LABEL           [aal_view_4] ;
        HELP            [aal_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
            VL_PV_FTIME,                     PARAM.PV_FTIME ;
            VL_OUT_ALM_SUM,                  PARAM.OUT_ALM_SUM ;
            VL_ALM_RATE_UP,                  PARAM.ALM_RATE_UP ;
            VL_ALM_RATE_DN,                  PARAM.ALM_RATE_DN ;
            VL_IGNORE_TIME,                  PARAM.IGNORE_TIME ;
            VL_ACK_OPTION,                   PARAM.ACK_OPTION ;
            VL_ALARM_HYS,                    PARAM.ALARM_HYS ;
            VL_HI_HI_PRI,                    PARAM.HI_HI_PRI ;
            VL_HI_HI_LIM,                    PARAM.HI_HI_LIM ;
            VL_HI_PRI,                       PARAM.HI_PRI ;
            VL_HI_LIM,                       PARAM.HI_LIM ;
            VL_LO_PRI,                       PARAM.LO_PRI ;
            VL_LO_LIM,                       PARAM.LO_LIM ;
            VL_LO_LO_PRI,                    PARAM.LO_LO_PRI ;
            VL_LO_LO_LIM,                    PARAM.LO_LO_LIM ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_aal_out {
    PARAM.OUT_RANGE.UNITS_INDEX : PARAM.OUT.VALUE,
            PARAM.PSP.VALUE,
            PARAM.HI_HI_BIAS,
            PARAM.HI_BIAS,
            PARAM.LO_BIAS,
            PARAM.LO_LO_BIAS,
            PARAM.OUT_ALM.VALUE,
            PARAM.OUT_ALM_SUM,
            PARAM.EXPAND_UP,
            PARAM.EXPAND_DN,
            PARAM.HI_HI_LIMX,
            PARAM.HI_LIMX,
            PARAM.LO_LIMX,
            PARAM.LO_LO_LIMX
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
COLLECTION no_download_aal
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_aal
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
