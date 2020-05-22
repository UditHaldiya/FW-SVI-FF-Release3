/*
** @(#)ar_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Arithmetic block
** Filename: ar_block.ddl
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
**       fixed unit relations per AR#1621
** MS	 modified unit relations to resolve to correct attribute per AR#1991
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
** Arithmetic block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __ARITHMETIC,
DEVICE_REVISION __ARITHMETIC_rel_dev_rev,
DD_REVISION     __ARITHMETIC_rel_dd_rev
/*
**********************************************************************
** Arithmetic
** Definition of Arithmetic Block
**********************************************************************
*/
BLOCK   __arithmetic
{
        CHARACTERISTICS __ar_character ;
        LABEL                              [arithmetic_block] ;
        HELP                               [arithmetic_block_help] ;
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
            PRE_OUT,                    __pre_out ;
            PV_SCALE,                   __pv_scale ;
            OUT_RANGE,                  __out_range ;
            GRANT_DENY,                 __grant_deny ;
            INPUT_OPTS,                 __input_opts ;
            IN,                         __in ;
            IN_LO,                      __in_lo ;
            IN_1,                       __in_1 ;
            IN_2,                       __in_2 ;
            IN_3,                       __in_3 ;
            RANGE_HI,                   __range_hi ;
            RANGE_LO,                   __range_lo ;
            BIAS_IN_1,                  __bias_in_1 ;
            GAIN_IN_1,                  __gain_in_1 ;
            BIAS_IN_2,                  __bias_in_2 ;
            GAIN_IN_2,                  __gain_in_2 ;
            BIAS_IN_3,                  __bias_in_3 ;
            GAIN_IN_3,                  __gain_in_3 ;
            COMP_HI_LIM,                __comp_hi_lim ;
            COMP_LO_LIM,                __comp_lo_lim ;
            ARITH_TYPE,                 __arith_type ;
            BAL_TIME,                   __bal_time ;
            BIAS,                       __bias ;
            GAIN,                       __gain ;
            OUT_HI_LIM,                 __out_hi_lim ;
            OUT_LO_LIM,                 __out_lo_lim ;
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __ar_view_1 ;
            VIEW_2, __ar_view_2 ;
            VIEW_3, __ar_view_3 ;
            VIEW_4, __ar_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_ar_pv,
            __unit_ar_out
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_ar
		,upload_wanted_ar
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __ar_character
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
VARIABLE_LIST   __ar_view_1
{
        LABEL           [ar_view_1] ;
        HELP            [ar_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_PRE_OUT,                      PARAM.PRE_OUT ;
        }
}

VARIABLE_LIST   __ar_view_2
{
        LABEL           [ar_view_2] ;
        HELP            [ar_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_PV_SCALE,                     PARAM.PV_SCALE ;
            VL_OUT_RANGE,                    PARAM.OUT_RANGE ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __ar_view_3
{
        LABEL           [ar_view_3] ;
        HELP            [ar_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_PV,                           PARAM.PV ;
            VL_OUT,                          PARAM.OUT ;
            VL_PRE_OUT,                      PARAM.PRE_OUT ;
            VL_IN,                           PARAM.IN ;
            VL_IN_LO,                        PARAM.IN_LO ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_IN_3,                         PARAM.IN_3 ;
        }
}

VARIABLE_LIST   __ar_view_4
{
        LABEL           [ar_view_4] ;
        HELP            [ar_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_INPUT_OPTS,                   PARAM.INPUT_OPTS ;
            VL_RANGE_HI,                     PARAM.RANGE_HI ;
            VL_RANGE_LO,                     PARAM.RANGE_LO ;
            VL_BIAS_IN_1,                    PARAM.BIAS_IN_1 ;
            VL_GAIN_IN_1,                    PARAM.GAIN_IN_1 ;
            VL_BIAS_IN_2,                    PARAM.BIAS_IN_2 ;
            VL_GAIN_IN_2,                    PARAM.GAIN_IN_2 ;
            VL_BIAS_IN_3,                    PARAM.BIAS_IN_3 ;
            VL_GAIN_IN_3,                    PARAM.GAIN_IN_3 ;
            VL_COMP_HI_LIM,                  PARAM.COMP_HI_LIM ;
            VL_COMP_LO_LIM,                  PARAM.COMP_LO_LIM ;
            VL_ARITH_TYPE,                   PARAM.ARITH_TYPE ;
            VL_BAL_TIME,                     PARAM.BAL_TIME ;
            VL_BIAS,                         PARAM.BIAS ;
            VL_GAIN,                         PARAM.GAIN ;
            VL_OUT_HI_LIM,                   PARAM.OUT_HI_LIM ;
            VL_OUT_LO_LIM,                   PARAM.OUT_LO_LIM ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_ar_pv {
    PARAM.PV_SCALE.UNITS_INDEX : PARAM.PV.VALUE,
            PARAM.IN_LO.VALUE,
            PARAM.RANGE_HI,
            PARAM.RANGE_LO
}
UNIT __unit_ar_out {
    PARAM.OUT_RANGE.UNITS_INDEX : PARAM.OUT.VALUE,
            PARAM.PRE_OUT.VALUE,
            PARAM.OUT_HI_LIM,
            PARAM.OUT_LO_LIM
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
COLLECTION no_download_ar
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_ar
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
