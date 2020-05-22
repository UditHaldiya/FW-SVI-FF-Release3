/*
** @(#)rio_wless_hart_block.ddl      0.9   2009-08-07
**
** FF Standard Wireless HART Transducer Block
** Filename: rio_wless_hart_block.ddl
** Spec revision:   FF-901 FS 5.1  DDL spec
**                  FF-890 FS 1.8  FBAP spec part 1
**                  FF-891 FS 1.8  FBAP spec part 2
**                  FF-902 FS 1.2  Transducer Block Common Structures
**                  FF-912 FS 1.0  Field Diagnostics Profile
**                  FF-915 DPS 2.2 Transducer Block for HSE RIO Module
**                  
** Date of last change: 2009-12-01
** Description:
**    Standard Wireless HART Transducer Block
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
** (c) Fieldbus Foundation(TM) (1994-2011)
**
*/

/*
** HISTORY:
** TAB   Revision 0.9  20090807
** TAB   Revision 0.2  20091201
**       Updated for FF-913 DPS rev 2.2
** TAB   Revision 0.3  20100618
**       Updated for FF-913 DPS rev 2.3
** TAB   Revision 0.4  20110304
**       Updated for FF-914 DPS rev 2.4
*/

/*
**********************************************************************
** Includes
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Standard HART Transducer Block
**********************************************************************
*/
MANUFACTURER    __FF,
DEVICE_TYPE     __RIO_WLESS_HART_BLOCK,
DEVICE_REVISION __RIO_WLESS_HART_BLOCK_rel_dev_rev,
DD_REVISION     __RIO_WLESS_HART_BLOCK_rel_dd_rev

/*
**********************************************************************
** Block definition
**********************************************************************
*/
BLOCK    __rio_wless_hart_xdcr_block
{
         CHARACTERISTICS       __rio_wless_hart_xdcr_character ;
         LABEL                 [rio_wless_hart_xdcr_block] ;
         HELP                  [rio_wless_hart_xdcr_block_help] ;
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
            TRANSDUCER_DIRECTORY,      __transducer_directory ;
            TRANSDUCER_TYPE,           __transducer_type ;
            TRANSDUCER_TYPE_VER,       __transducer_type_ver ;
            XD_ERROR,                  __xd_error ;
            COLLECTION_DIRECTORY,      __collection_directory ;
            HART_EXPD_DEV_INFO,        __hart_expd_dev_info ;
            HART_ACTL_DEV_INFO,        __hart_actl_dev_info ;
            HART_CMD,                  __hart_cmd ;
            HART_RESP,                 __hart_resp ;
            HART_IND,                  __hart_ind ;
            HART_COM_STAT,             __hart_com_stat ;
            HART_IND_PRI,              __hart_ind_pri;
            HART_DIAG_MAP,             __hart_diag_map ;
            HART_TSTAMP,               __hart_tstamp ;
            HART_BAD_TMOUT,            __hart_bad_tmout ;
            HART_UNC_TMOUT,            __hart_unc_tmout ;
            HART_VAR_CODES8,           __hart_var_codes8 ;
            HART_PV,                   __hart_pv ;
            HART_SV,                   __hart_sv ;
            HART_TV,                   __hart_tv ;
            HART_QV,                   __hart_qv ;
            HART_5V,                   __hart_5v ;
            HART_6V,                   __hart_6v ;
            HART_7V,                   __hart_7v ;
            HART_8V,                   __hart_8v ;
            PRIMARY_VALUE,             __primary_value ;
            VAR_UNITS9,                __var_units9 ;
            VAR_NAMES9,                __var_names9 ;
            VAR_DIR9,                  __var_dir9 ;
            DUP_VAR_NAME_DEF_9,        __dup_var_name_def_9 ;
            HART_URL,                  __hart_url ;
            HART_LRL,                  __hart_lrl ;
            IO_THRESHOLD,              __io_threshold ;
            ACK_OPTION,                __ack_option ;
            FD_VER,                    __fd_ver ;
            FD_FAIL_ACTIVE,            __fd_fail_active ;
            FD_OFFSPEC_ACTIVE,         __fd_offspec_active ;
            FD_MAINT_ACTIVE,           __fd_maint_active ;
            FD_CHECK_ACTIVE,           __fd_check_active ;
            FD_FAIL_MAP,               __fd_fail_map ;
            FD_OFFSPEC_MAP,            __fd_offspec_map ;
            FD_MAINT_MAP,              __fd_maint_map ;
            FD_CHECK_MAP,              __fd_check_map ;
            FD_FAIL_MASK,              __fd_fail_mask ;
            FD_OFFSPEC_MASK,           __fd_offspec_mask ;
            FD_MAINT_MASK,             __fd_maint_mask ;
            FD_CHECK_MASK,             __fd_check_mask ;
            FD_FAIL_ALM,               __fd_fail_alm ;
            FD_OFFSPEC_ALM,            __fd_offspec_alm ;
            FD_MAINT_ALM,              __fd_maint_alm ;
            FD_CHECK_ALM,              __fd_check_alm ;
            FD_FAIL_PRI,               __fd_fail_pri ;
            FD_OFFSPEC_PRI,            __fd_offspec_pri ;
            FD_MAINT_PRI,              __fd_maint_pri ;
            FD_CHECK_PRI,              __fd_check_pri ;
            FD_SIMULATE,               __fd_simulate ;
            FD_RECOMMEN_ACT,           __fd_recommen_act ;
            HART_BURST_CTRL_1,         __hart_burst_ctrl_1 ;
            HART_BURST_CTRL_2,         __hart_burst_ctrl_2 ;
            HART_BURST_CTRL_3,         __hart_burst_ctrl_3 ;
            HART_BURST_CTRL_4,         __hart_burst_ctrl_4 ;
         }
         PARAMETER_LISTS
         {
            VIEW_1, __rio_wless_hart_xdcr_view_1 ;
            VIEW_2, __rio_wless_hart_xdcr_view_2 ;
            VIEW_3, __rio_wless_hart_xdcr_view_3 ;
            VIEW_4, __rio_wless_hart_xdcr_view_4 ;
         }
         
         #ifdef UD_LISTS
	 COLLECTION_ITEMS
	 {
	 	no_download_rwhx
	 	,upload_wanted_rwhx
	 }
	 #endif
}

/*
**********************************************************************
** Variables
**********************************************************************
*/
RECORD      __rio_wless_hart_xdcr_character
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
VARIABLE_LIST     __rio_wless_hart_xdcr_view_1
{
      LABEL       [rio_wless_hart_xdcr_view_1] ;
      HELP        [rio_wless_hart_xdcr_view_1_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
         VL_HART_TSTAMP,            PARAM.HART_TSTAMP ;
         VL_HART_PV,                PARAM.HART_PV ;
         VL_HART_SV,                PARAM.HART_SV ;
         VL_HART_TV,                PARAM.HART_TV ;
         VL_HART_QV,                PARAM.HART_QV ;
         VL_HART_5V,                PARAM.HART_5V ;
         VL_HART_6V,                PARAM.HART_6V ;
         VL_HART_7V,                PARAM.HART_7V ;
         VL_HART_8V,                PARAM.HART_8V ;
         VL_PRIMARY_VALUE,          PARAM.PRIMARY_VALUE ;  
         VL_FD_FAIL_ACTIVE,         PARAM.FD_FAIL_ACTIVE ;
         VL_FD_OFFSPEC_ACTIVE,      PARAM.FD_OFFSPEC_ACTIVE ;
         VL_FD_MAINT_ACTIVE,        PARAM.FD_MAINT_ACTIVE ;
         VL_FD_CHECK_ACTIVE,        PARAM.FD_CHECK_ACTIVE ;
         VL_FD_RECOMMEN_ACT,        PARAM.FD_RECOMMEN_ACT ;
      }
}

VARIABLE_LIST     __rio_wless_hart_xdcr_view_2
{
      LABEL       [rio_wless_hart_xdcr_view_2] ;
      HELP        [rio_wless_hart_xdcr_view_2_help] ;
      MEMBERS
      {
         VL_ST_REV,                    PARAM.ST_REV ;
         VL_TRANSDUCER_TYPE,           PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,       PARAM.TRANSDUCER_TYPE_VER ;
         VL_HART_EXPD_DEV_INFO,        PARAM.HART_EXPD_DEV_INFO ;
         VL_HART_DIAG_MAP,             PARAM.HART_DIAG_MAP ;
         VL_HART_URL,                  PARAM.HART_URL ;
         VL_HART_LRL,                  PARAM.HART_LRL ;
         VL_IO_THRESHOLD,              PARAM.IO_THRESHOLD ;
      }
}

VARIABLE_LIST   __rio_wless_hart_xdcr_view_3
{
      LABEL           [rio_wless_hart_xdcr_view_3] ;
      HELP            [rio_wless_hart_xdcr_view_3_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_MODE_BLK,               PARAM.MODE_BLK ;
         VL_BLOCK_ERR,              PARAM.BLOCK_ERR ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_XD_ERROR,               PARAM.XD_ERROR ;
         VL_HART_ACTL_DEV_INFO,     PARAM.HART_ACTL_DEV_INFO ;
         VL_FD_FAIL_ACTIVE,         PARAM.FD_FAIL_ACTIVE ;
         VL_FD_OFFSPEC_ACTIVE,      PARAM.FD_OFFSPEC_ACTIVE ;
         VL_FD_MAINT_ACTIVE,        PARAM.FD_MAINT_ACTIVE ;
         VL_FD_CHECK_ACTIVE,        PARAM.FD_CHECK_ACTIVE ;
         VL_FD_SIMULATE,            PARAM.FD_SIMULATE ;
         VL_FD_RECOMMEN_ACT,        PARAM.FD_RECOMMEN_ACT ;
      }
}

VARIABLE_LIST     __rio_wless_hart_xdcr_view_4
{
      LABEL       [rio_wless_hart_xdcr_view_4] ;
      HELP        [rio_wless_hart_xdcr_view_4_help] ;
      MEMBERS
      {
         VL_ST_REV,                 PARAM.ST_REV ;
         VL_STRATEGY,               PARAM.STRATEGY ;
         VL_ALERT_KEY,              PARAM.ALERT_KEY ;
         VL_TRANSDUCER_TYPE,        PARAM.TRANSDUCER_TYPE ;
         VL_TRANSDUCER_TYPE_VER,    PARAM.TRANSDUCER_TYPE_VER ;
         VL_HART_IND_PRI,           PARAM.HART_IND_PRI ;
         VL_HART_BAD_TMOUT,         PARAM.HART_BAD_TMOUT ;
         VL_HART_UNC_TMOUT,         PARAM.HART_UNC_TMOUT ;
         VL_HART_VAR_CODES8,        PARAM.HART_VAR_CODES8 ;
         VL_VAR_UNITS9,             PARAM.VAR_UNITS9 ;
         VL_VAR_DIR9,               PARAM.VAR_DIR9 ;
         VL_ACK_OPTION,             PARAM.ACK_OPTION ;
         VL_FD_VER,                 PARAM.FD_VER ;
         VL_FD_FAIL_MAP,            PARAM.FD_FAIL_MAP ;
         VL_FD_OFFSPEC_MAP,         PARAM.FD_OFFSPEC_MAP ;
         VL_FD_MAINT_MAP,           PARAM.FD_MAINT_MAP ;
         VL_FD_CHECK_MAP,           PARAM.FD_CHECK_MAP ;
         VL_FD_FAIL_MASK,           PARAM.FD_FAIL_MASK ;
         VL_FD_OFFSPEC_MASK,        PARAM.FD_OFFSPEC_MASK ;
         VL_FD_MAINT_MASK,          PARAM.FD_MAINT_MASK ;
         VL_FD_CHECK_MASK,          PARAM.FD_CHECK_MASK ;
         VL_FD_FAIL_PRI,            PARAM.FD_FAIL_PRI ;
         VL_FD_OFFSPEC_PRI,         PARAM.FD_OFFSPEC_PRI ;
         VL_FD_MAINT_PRI,           PARAM.FD_MAINT_PRI ;
         VL_FD_CHECK_PRI,           PARAM.FD_CHECK_PRI ;
         VL_HART_BURST_CTRL_1,      PARAM.HART_BURST_CTRL_1 ;
         VL_HART_BURST_CTRL_2,      PARAM.HART_BURST_CTRL_2 ;
         VL_HART_BURST_CTRL_3,      PARAM.HART_BURST_CTRL_3 ;
         VL_HART_BURST_CTRL_4,      PARAM.HART_BURST_CTRL_4 ;
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
COLLECTION no_download_rwhx
{
	LABEL	[no_download_label] ;
	HELP	[no_download_help] ;
	MEMBERS {}
}

COLLECTION upload_wanted_rwhx
{
	LABEL	[upload_wanted_label] ;
	HELP	[upload_wanted_help] ;
	MEMBERS {}
}
#endif
