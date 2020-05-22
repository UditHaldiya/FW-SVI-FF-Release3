/*
** @(#)sif_aiblock.ddl 1.0 2007-09-30
**
** FF SIF Analog Input block
** Filename: sif_aiblock.ddl
** Spec revision: FF-900 FS 1.0 DDL spec
**                FF-807 FS 1.1 FF-SIS Application Model
**                FF-895 PS 1.1 FF-SIS Function Blocks Phase 1
** Date of last change: 2007-09-30
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
** (c) Fieldbus Foundation(TM) (1994-2007)
**
*/

/*
** HISTORY:
**  ED Revision 0.1 20070930
**  MS   ARs 2901 -- 2008.10.07
**  ED Revision 1.2 2008-12-03 Changed SIS to SIF
**  MS   ARs 5282 -- 2010.10.15
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** SIF Analog Input block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __SIF_AI_BLOCK,
DEVICE_REVISION __SIF_AI_BLOCK_rel_dev_rev,
DD_REVISION     __SIF_AI_BLOCK_rel_dd_rev
/*
**********************************************************************
** SIF Analog Input
** Definition of an SIF analog input block
**********************************************************************
*/
BLOCK   __sif_analog_input_block
{
        CHARACTERISTICS                 __sif_ai_character ;
        LABEL                           [sif_analog_input_block] ;
        HELP                            [sif_analog_input_block_help] ;
        PARAMETERS
        {
                ST_REV,                 __st_rev ;
                TAG_DESC,               __tag_desc ;
                STRATEGY,               __strategy ;
                ALERT_KEY,              __alert_key ;
                MODE_BLK,               __mode_blk ;
                BLOCK_ERR,              __block_err ;
                PV,                     __pv ;
                OUT,                    __out ;
                SIMULATE,               __simulate_float ;
                XD_SCALE,               __xd_scale ;
                OUT_SCALE,              __out_scale ;
                IO_OPTS,                __io_opts_ai ;
                STATUS_OPTS,            __status_opts_sai ;
                CHANNEL,                __channel ;
                L_TYPE,                 __l_type ;
                LOW_CUT,                __low_cut ;
                PV_FTIME,               __pv_ftime ;
        }
        PARAMETER_LISTS
        {
                VIEW_1, __sif_ai_view_1 ;
                VIEW_2, __sif_ai_view_2 ;
                VIEW_3, __sif_ai_view_3 ;
                VIEW_4, __sif_ai_view_4 ;
        }
        /*UNIT_ITEMS
        {
                __unit_ai_xd,
                __unit_ai_out
        }*/
        
        #ifdef UD_LISTS
	COLLECTION_ITEMS
	{
		no_download_sif_ai
		,upload_wanted_sif_ai
	}
	#endif
}
/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __sif_ai_character
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
VARIABLE_LIST   __sif_ai_view_1
{
        LABEL           [sif_ai_view_1] ;
        HELP            [sif_ai_view_1_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,          PARAM.PV ;
                VL_OUT,         PARAM.OUT ;
        }
}

VARIABLE_LIST   __sif_ai_view_2
{
        LABEL           [sif_ai_view_2] ;
        HELP            [sif_ai_view_2_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_XD_SCALE,    PARAM.XD_SCALE ;
                VL_OUT_SCALE,   PARAM.OUT_SCALE ;
        }
}

VARIABLE_LIST   __sif_ai_view_3
{
        LABEL           [sif_ai_view_3] ;
        HELP            [sif_ai_view_3_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
                VL_PV,          PARAM.PV ;
                VL_OUT,         PARAM.OUT ;
        }
}

VARIABLE_LIST   __sif_ai_view_4
{
        LABEL           [sif_ai_view_4] ;
        HELP            [sif_ai_view_4_help] ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_STRATEGY,    PARAM.STRATEGY ;
                VL_ALERT_KEY,   PARAM.ALERT_KEY ;
                VL_IO_OPTS,     PARAM.IO_OPTS ;
                VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
                VL_CHANNEL,     PARAM.CHANNEL ;
                VL_L_TYPE,      PARAM.L_TYPE ;
                VL_LOW_CUT,     PARAM.LOW_CUT ;
                VL_PV_FTIME,    PARAM.PV_FTIME ;
        }
}
/*
**********************************************************************
** Unit relations
**********************************************************************
*/
/*
** NOTE:
** In the implementation of the AI Block, PV and OUT always
** have identical scaling.  OUT_SCALE provides scaling for
** PV.
*/

/*

UNIT    __unit_ai_xd
{
        PARAM.XD_SCALE.UNITS_INDEX :
        PARAM.SIMULATE.TRANSDUCER_VALUE,
        PARAM.SIMULATE.SIMULATE_VALUE
        PARAM.XD_SCALE.EU_100,
        PARAM.XD_SCALE.EU_0
}
UNIT    __unit_ai_out
{
        PARAM.OUT_SCALE.UNITS_INDEX :
        PARAM.OUT.VALUE,
        PARAM.OUT_SCALE.EU_100,
        PARAM.OUT_SCALE.EU_0,
        PARAM.LOW_CUT
        PARAM.PV.VALUE,
        PARAM.HI_HI_LIM,
        PARAM.HI_LIM,
        PARAM.LO_LIM,
        PARAM.LO_LO_LIM,
        PARAM.HI_HI_ALM.VALUE,
        PARAM.HI_ALM.VALUE,
        PARAM.LO_ALM.VALUE,
        PARAM.LO_LO_ALM.VALUE
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
COLLECTION no_download_sif_ai
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_sif_ai
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
