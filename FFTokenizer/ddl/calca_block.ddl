/*
** @(#)calca_block.ddl    1.0 Thu May 23 10:21:43 2002

**
** FF standard Calculate Analog block
** Filename: calca_block.ddl
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
** MS	 temporarily commented out unit per AR#1991 until correct def. for OUT_n_UNITS
** MS	 made changes per AR2351 using LIB2 macro def during tok 2007-07-17
** MS   ARs 1992, 2901 -- 2008.10.07
*/
/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Calculate Analog block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __CALCULATE_ANALOG,
DEVICE_REVISION __CALCULATE_ANALOG_beta_dev_rev,
DD_REVISION     __CALCULATE_ANALOG_beta_dd_rev
/*
**********************************************************************
** Calculate Analog
** Definition of Calculate Analog Block
**********************************************************************
*/
BLOCK   __calculate_analog
{
        CHARACTERISTICS __calca_character ;
        LABEL                              [calculate_analog_block] ;
        HELP                               [calculate_analog_block_help] ;
        PARAMETERS
        {
            ST_REV,                     __st_rev ;
            TAG_DESC,                   __tag_desc ;
            STRATEGY,                   __strategy ;
            ALERT_KEY,                  __alert_key ;
            MODE_BLK,                   __mode_blk ;
            BLOCK_ERR,                  __block_err ;
            IN_1,                       __in_1 ;
            IN_2,                       __in_2 ;
            IN_3,                       __in_3 ;
            IN_4,                       __in_4 ;
            PRE_OUT_1,                  __pre_out_1 ;
            PRE_OUT_2,                  __pre_out_2 ;
            TEMP_1,                     __temp_1 ;
            TEMP_2,                     __temp_2 ;
            TEMP_3,                     __temp_3 ;
            TEMP_4,                     __temp_4 ;
            OUT_1,                      __out_1 ;
            OUT_2,                      __out_2 ;
            OUT_1_UNITS,                __out_1_units ;
            OUT_2_UNITS,                __out_2_units ;
            IN_D1,                      __in_d1 ;
            IN_D2,                      __in_d2 ;
            IN_D3,                      __in_d3 ;
            IN_D4,                      __in_d4 ;
            PRE_OUT_D1,                 __pre_out_d1 ;
            PRE_OUT_D2,                 __pre_out_d2 ;
            TEMP_D1,                    __temp_d1 ;
            TEMP_D2,                    __temp_d2 ;
            TEMP_D3,                    __temp_d3 ;
            TEMP_D4,                    __temp_d4 ;
            OUT_D1,                     __out_d1 ;
            OUT_D2,                     __out_d2 ;
            OUT_1_STATE,                __out_1_state ;
            OUT_2_STATE,                __out_2_state ;
            INST_EX_LIM,                __inst_ex_lim ;
            PROP_LIMS,                  __prop_lims ;
            CALC_ERRS,                  __calc_errs ;
            INST_ERR_NO,                __inst_err_no ;
            ERR_LATCH,                  __err_latch ;
            GRANT_DENY,                 __grant_deny ;
            #ifdef LIB2
            STATUS_OPTS,                __status_opts ;
            #else
            STATUS_OPTS,                __status_opts_calca ;
            #endif
            UPDATE_EVT,                 __update_evt ;
            BLOCK_ALM,                  __block_alm ;
            INST_LIST1,                 __inst_list1 ;
        }
        PARAMETER_LISTS
        {
            VIEW_1, __calca_view_1 ;
            VIEW_2, __calca_view_2 ;
            VIEW_3, __calca_view_3 ;
            VIEW_4, __calca_view_4 ;
        }
        UNIT_ITEMS
        {
            __unit_calca_out_1,
            __unit_calca_out_2
        }
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_calca
		,upload_wanted_calca
	}
	#endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __calca_character
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
VARIABLE_LIST   __calca_view_1
{
        LABEL           [calca_view_1] ;
        HELP            [calca_view_1_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_IN_3,                         PARAM.IN_3 ;
            VL_IN_4,                         PARAM.IN_4 ;
            VL_PRE_OUT_1,                    PARAM.PRE_OUT_1 ;
            VL_PRE_OUT_2,                    PARAM.PRE_OUT_2 ;
            VL_OUT_1,                        PARAM.OUT_1 ;
            VL_OUT_2,                        PARAM.OUT_2 ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D1,                   PARAM.PRE_OUT_D1 ;
            VL_PRE_OUT_D2,                   PARAM.PRE_OUT_D2 ;
            VL_OUT_D1,                       PARAM.OUT_D1 ;
            VL_OUT_D2,                       PARAM.OUT_D2 ;
        }
}

VARIABLE_LIST   __calca_view_2
{
        LABEL           [calca_view_2] ;
        HELP            [calca_view_2_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_OUT_1_UNITS,                  PARAM.OUT_1_UNITS ;
            VL_OUT_2_UNITS,                  PARAM.OUT_2_UNITS ;
            VL_OUT_1_STATE,                  PARAM.OUT_1_STATE ;
            VL_OUT_2_STATE,                  PARAM.OUT_2_STATE ;
        }
}

VARIABLE_LIST   __calca_view_3
{
        LABEL           [calca_view_3] ;
        HELP            [calca_view_3_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_MODE_BLK,                     PARAM.MODE_BLK ;
            VL_BLOCK_ERR,                    PARAM.BLOCK_ERR ;
            VL_IN_1,                         PARAM.IN_1 ;
            VL_IN_2,                         PARAM.IN_2 ;
            VL_IN_3,                         PARAM.IN_3 ;
            VL_IN_4,                         PARAM.IN_4 ;
            VL_PRE_OUT_1,                    PARAM.PRE_OUT_1 ;
            VL_PRE_OUT_2,                    PARAM.PRE_OUT_2 ;
            VL_TEMP_1,                       PARAM.TEMP_1 ;
            VL_TEMP_2,                       PARAM.TEMP_2 ;
            VL_TEMP_3,                       PARAM.TEMP_3 ;
            VL_TEMP_4,                       PARAM.TEMP_4 ;
            VL_OUT_1,                        PARAM.OUT_1 ;
            VL_OUT_2,                        PARAM.OUT_2 ;
            VL_IN_D1,                        PARAM.IN_D1 ;
            VL_IN_D2,                        PARAM.IN_D2 ;
            VL_IN_D3,                        PARAM.IN_D3 ;
            VL_IN_D4,                        PARAM.IN_D4 ;
            VL_PRE_OUT_D1,                   PARAM.PRE_OUT_D1 ;
            VL_PRE_OUT_D2,                   PARAM.PRE_OUT_D2 ;
            VL_TEMP_D1,                      PARAM.TEMP_D1 ;
            VL_TEMP_D2,                      PARAM.TEMP_D2 ;
            VL_TEMP_D3,                      PARAM.TEMP_D3 ;
            VL_TEMP_D4,                      PARAM.TEMP_D4 ;
            VL_OUT_D1,                       PARAM.OUT_D1 ;
            VL_OUT_D2,                       PARAM.OUT_D2 ;
            VL_CALC_ERRS,                    PARAM.CALC_ERRS ;
            VL_INST_ERR_NO,                  PARAM.INST_ERR_NO ;
            VL_GRANT_DENY,                   PARAM.GRANT_DENY ;
        }
}

VARIABLE_LIST   __calca_view_4
{
        LABEL           [calca_view_4] ;
        HELP            [calca_view_4_help] ;
        MEMBERS
        {
            VL_ST_REV,                       PARAM.ST_REV ;
            VL_STRATEGY,                     PARAM.STRATEGY ;
            VL_ALERT_KEY,                    PARAM.ALERT_KEY ;
            VL_INST_EX_LIM,                  PARAM.INST_EX_LIM ;
            VL_PROP_LIMS,                    PARAM.PROP_LIMS ;
            VL_ERR_LATCH,                    PARAM.ERR_LATCH ;
            VL_STATUS_OPTS,                  PARAM.STATUS_OPTS ;
        }
}

/*
**********************************************************************
** Unit relations
**********************************************************************
*/
UNIT __unit_calca_out_1 {
    PARAM.OUT_1_UNITS : PARAM.PRE_OUT_1.VALUE,
            PARAM.OUT_1.VALUE
}
UNIT __unit_calca_out_2 {
    PARAM.OUT_2_UNITS : PARAM.PRE_OUT_2.VALUE,
            PARAM.OUT_2.VALUE
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
COLLECTION no_download_calca
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_calca
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
