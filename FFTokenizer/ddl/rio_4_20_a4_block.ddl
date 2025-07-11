/*
** @(#)rio_4_20_a4_block.ddl      0.9   2009-08-07
**
** FF Standard 4-20 4 Analog I/O Card Transducer Block
** Filename: rio_4_20_a4_block.ddl
** Spec revision:   FF-901 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.2  Transducer Block Common Structures
**                  FF-912 FS 1.0  Field Diagnostics Profile
**                  FF-915 DPS 2.2 Transducer Block for HSE RIO Module
**                  
** Date of last change: 2009-11-30
** Description:
**    Standard 4-20 4 Analog I/O Card Transducer Block
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
** TAB   Revision 0.1  20090807
** TAB   Revision 0.2  20091130
**       Updated for FF-915 DPS rev 2.2
** TAB   Revision 0.3  20100618
**       Updated for FF-915 DPS rev 2.3
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Standard 4-20 4 Analog I/O Card Transducer Block
**********************************************************************
*/
MANUFACTURER    0x10FF00,
DEVICE_TYPE     __RIO_BLOCK,
DEVICE_REVISION __RIO_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_BLOCK_rel_dd_rev

IMPORT MANUFACTURER __FF,
DEVICE_TYPE __STD_PARM,
DEVICE_REVISION __STD_PARM_rel_dev_rev,
DD_REVISION __STD_PARM_rel_dd_rev
{EVERYTHING;}

IMPORT MANUFACTURER __FF,
DEVICE_TYPE __STD_XDCR_PARM,
DEVICE_REVISION __STD_XDCR_PARM_beta_dev_rev,
DD_REVISION __STD_XDCR_PARM_beta_dd_rev
{EVERYTHING;}

IMPORT MANUFACTURER __FF,
DEVICE_TYPE __RIO_XDCR_PARM,
DEVICE_REVISION __RIO_XDCR_PARM_rel_dev_rev,
DD_REVISION __RIO_XDCR_PARM_rel_dd_rev
{EVERYTHING;}

/*
**********************************************************************
** Block definition
**********************************************************************
*/
BLOCK    __rio_4_20_a4_xdcr_block
{
         CHARACTERISTICS       __rio_4_20_a4_xdcr_character ;
         LABEL                 "RIO 4-20 A4 Transducer Block" ;
         HELP                  "RIO 4-20 A4 Transducer Block" ;
         PARAMETERS
         {
            ST_REV,                    __st_rev ;
            TAG_DESC,                  __tag_desc ;
            STRATEGY,                  __strategy ;
            ALERT_KEY,                 __alert_key ;
            MODE_BLK,                  __mode_blk ;
            BLOCK_ERR,                 __block_err ;
            UPDATE_EVT,                __update_evt ;
            BLOCK_ALM,                 __block_alm ;
            ACK_OPTION,                __ack_option ;
            TRANSDUCER_DIRECTORY,      __transducer_directory ;
            TRANSDUCER_TYPE,           __transducer_type ;
            TRANSDUCER_TYPE_VER,       __transducer_type_ver ;
            XD_ERROR,                  __xd_error ;
            COLLECTION_DIRECTORY,      __collection_directory ;
            VAR_NAMES4,                __var_names4 ;
            VAR_DIR4,                  __var_dir4 ;
            PROCESS_VALUE_A_1,         __process_value_a_1 ;
            PROCESS_VALUE_A_2,         __process_value_a_2 ;
            PROCESS_VALUE_A_3,         __process_value_a_3 ;
            PROCESS_VALUE_A_4,         __process_value_a_4 ;
            PROCESS_VALUE_RANGE_A_1,   __process_value_range_a_1 ;
            PROCESS_VALUE_RANGE_A_2,   __process_value_range_a_2 ;
            PROCESS_VALUE_RANGE_A_3,   __process_value_range_a_3 ;
            PROCESS_VALUE_RANGE_A_4,   __process_value_range_a_4 ;
            IO_THRESHOLD_A_1,          __io_threshold_a_1 ;
            IO_THRESHOLD_A_2,          __io_threshold_a_2 ;
            IO_THRESHOLD_A_3,          __io_threshold_a_3 ;
            IO_THRESHOLD_A_4,          __io_threshold_a_4 ;
         }
         PARAMETER_LISTS
         {
            VIEW_1, __rio_4_20_a4_xdcr_view_1 ;
            VIEW_2, __rio_4_20_a4_xdcr_view_2 ;
            VIEW_3, __rio_4_20_a4_xdcr_view_3 ;
            VIEW_4, __rio_4_20_a4_xdcr_view_4 ;
         }
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __rio_4_20_a4_xdcr_character
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
VARIABLE_LIST     __rio_4_20_a4_xdcr_view_1
{
      LABEL       "RIO 4-20 A4 Transducer View 1" ;
      HELP        [rio_h1_xdcr_view_1_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
         VL_PROCESS_VALUE_A_1,      PARAM.PROCESS_VALUE_A_1 ;
         VL_PROCESS_VALUE_A_2,      PARAM.PROCESS_VALUE_A_2 ;
         VL_PROCESS_VALUE_A_3,      PARAM.PROCESS_VALUE_A_3 ;
         VL_PROCESS_VALUE_A_4,      PARAM.PROCESS_VALUE_A_4 ;
      }
}

VARIABLE_LIST     __rio_4_20_a4_xdcr_view_2
{
      LABEL       "RIO 4-20 A4 Transducer View 2" ;
      HELP        [rio_h1_xdcr_view_2_help] ;
      MEMBERS
      {
         VL_ST_REV,                    PARAM.ST_REV ;
         VL_TRANSDUCER_TYPE,           PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,       PARAM.TRANSDUCER_TYPE_VER ;
         VL_PROCESS_VALUE_RANGE_A_1,   PARAM.PROCESS_VALUE_RANGE_A_1 ;
         VL_PROCESS_VALUE_RANGE_A_2,   PARAM.PROCESS_VALUE_RANGE_A_2 ;
         VL_PROCESS_VALUE_RANGE_A_3,   PARAM.PROCESS_VALUE_RANGE_A_3 ;
         VL_PROCESS_VALUE_RANGE_A_4,   PARAM.PROCESS_VALUE_RANGE_A_4 ;
         VL_IO_THRESHOLD_A_1,          PARAM.IO_THRESHOLD_A_1 ;
         VL_IO_THRESHOLD_A_2,          PARAM.IO_THRESHOLD_A_2 ;
         VL_IO_THRESHOLD_A_3,          PARAM.IO_THRESHOLD_A_3 ;
         VL_IO_THRESHOLD_A_4,          PARAM.IO_THRESHOLD_A_4 ;
      }
}

VARIABLE_LIST   __rio_4_20_a4_xdcr_view_3
{
      LABEL       "RIO 4-20 A4 Transducer View 3" ;
      HELP        [rio_h1_xdcr_view_3_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
         VL_PROCESS_VALUE_A_1,      PARAM.PROCESS_VALUE_A_1 ;
         VL_PROCESS_VALUE_A_2,      PARAM.PROCESS_VALUE_A_2 ;
         VL_PROCESS_VALUE_A_3,      PARAM.PROCESS_VALUE_A_3 ;
         VL_PROCESS_VALUE_A_4,      PARAM.PROCESS_VALUE_A_4 ;
      }
}

VARIABLE_LIST     __rio_4_20_a4_xdcr_view_4
{
      LABEL       "RIO 4-20 A4 Transducer View 4" ;
      HELP        [rio_h1_xdcr_view_4_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_STRATEGY,               PARAM.STRATEGY ;
         VL_ALERT_KEY,              PARAM.ALERT_KEY ;
         VL_ACK_OPTION,             PARAM.ACK_OPTION ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,    PARAM.TRANSDUCER_TYPE_VER ;
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
