/*****************************************************************************/
/* 1000_VisualTB.ddl                                                         */
/*                                                                           */
/*   This DDL file defines a custom transducer block that will demonstrate   */
/*   several EDDL visualizations.                                            */
/*                                                                           */
/* CRITERIA FOR TEST_CASE_SELECTION                                          */
/*                                                                           */
/*	 None.                                                                   */
/*                                                                           */
/* REFERENCE                                                                 */
/*                                                                           */
/*   Document:                                                               */
/*   Version:                                                                */
/*   Date:                                                                   */
/*   Section:                                                                */
/*                                                                           */
/* REVISION_HISTORY                                                          */
/*                                                                           */
/*----------+---------------------------------------------------+-----+------*/
/* Date     ! Changes                                           !Vers.! By   */
/*----------+---------------------------------------------------+-----+------*/
/* 02-07-07 ! Initial version                                   ! 1.0 ! ms   */
/* 02-23-07 ! replaced all visualTB_block_view_ with            ! 1.0 ! awc  */
/*          !  visualTB_view_                                   !     !      */
/* 04-11-07 ! defined unique character record for block		    ! 1.0 ! awc  */
/* 09-24-07 ! AR4388 - changed __event_update to __update_evt	! 1.1 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Block Attributes Definition
******************************************************************************
*/

RECORD      visualtb_character
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
        VIEWS_INDEX,        __views_index ;
        NUMBER_VIEW_3,      __number_view_3 ;
        NUMBER_VIEW_4,      __number_view_4 ;
    }
}

/*
******************************************************************************
** Block Definition
******************************************************************************
*/

BLOCK   VISUALTB
{
	CHARACTERISTICS visualtb_character;
	LABEL "Visual Transducer Block";
    HELP  "This custom transducer block demonstrates "
          "several EDD visualizations.";
	PARAMETERS
	{
        /* standard transducer parameters */
        ST_REV,                     __st_rev ;
        TAG_DESC,                   __tag_desc ;
        STRATEGY,                   __strategy ;
        ALERT_KEY,                  __alert_key ;
        MODE_BLK,                   __mode_blk ;
        BLOCK_ERR,                  __block_err ;
        UPDATE_EVT,                 __update_evt ;
        BLOCK_ALM,                  __block_alm ;
        TRANSDUCER_DIRECTORY,       __transducer_directory ;
        TRANSDUCER_TYPE,            __transducer_type ;
        XD_ERROR,                   __xd_error ;
        COLLECTION_DIRECTORY,       __collection_directory ;

        /* custom transducer parameters */
        TEST_FL_VAL_1,              test_fl_val_1;
        TEST_FL_VAL_2,              test_fl_val_2;
        TEST_FL_VAL_3,              test_fl_val_3;
        TEST_FL_VAL_4,              test_fl_val_4;
        TEST_VAL_INT_8,             test_val_int_8;
        TEST_VAL_UINT_8,            test_val_uint_8;
        TEST_VAL_INT_16,            test_val_int_16;
        TEST_VAL_UINT_16,           test_val_uint_16;
        TEST_VAL_INT_32,            test_val_int_32;
        TEST_VAL_UINT_32,           test_val_uint_32;
        TEST_Y_ARRAY_1,             test_y_array_1;
        TEST_X_ARRAY_1,             test_x_array_1;
        TEST_Y_ARRAY_2,             test_y_array_2;
        TEST_X_ARRAY_2,             test_x_array_2;
        TEST_RECORD,                test_record;
        TEST_STRING,                test_string;
        TEST_HI_HI_LIMIT,           test_hi_hi_limit;
        TEST_HI_LIMIT,              test_hi_limit;
        TEST_LO_LIMIT,              test_lo_limit;
        TEST_LO_LO_LIMIT,           test_lo_lo_limit;
        TEST_RIGHT_LIMIT,           test_right_limit;
        TEST_LEFT_LIMIT,            test_left_limit;
        UPPER_RANGE_VALUE,          upper_range_value;
        LOWER_RANGE_VALUE,          lower_range_value;
        UPPER_SENSOR_LIMIT,         upper_sensor_limit;
        LOWER_SENSOR_LIMIT,         lower_sensor_limit;
    }

    PARAMETER_LISTS
	{
		VIEW_1, visualtb_view_1;
		VIEW_2, visualtb_view_2;
		VIEW_3, visualtb_view_3;
		VIEW_4, visualtb_view_4;
	}

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_visualtb,
                #else
                Menu_Top_visualtb,
                #endif
                
                device_root_menu_visualtb

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_visualtb
                #if !_AR4940
                ,hh_diagnostics_root_menu_visualtb
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_visualtb
                #if !_AR4940
                ,hh_process_variables_root_menu_visualtb
                #endif
                #endif
        
            #ifdef V4
	        ,tc_mn_000_menu
            #endif
    }

#if _DD5_PROFILE
	MENUS  /* Menus exported for cross-block purposes */
	{
		WINDOW_VISUALTB, window_visualtb;
		TC_CH_001_PAGE, tc_ch_001_page;
		TC_CH_001_INPUT_GROUP, tc_ch_001_input_group;
		MENUTESTDIALOG1, menuTestDialog1;
	}
	
	METHODS
	{
		MENUTESTMETHOD1, menuTestMethod1;
	}

	GRIDS
	{
		MENUTESTGRID1, menuTestGrid1;
	}

	GRAPHS
	{
		MENUTESTGRAPH1, menuTestGraph1;
	}

	CHARTS
	{
		MENUTESTCHART1, menuTestChart1;
	}
#endif

    METHOD_ITEMS
    {
        #if _DD5_PROFILE
        tc_gr_001_set_vals_method,
        tc_gr_002_set_vals_method,
        tc_gr_003_set_vals_method,
        tc_gr_004_set_vals_method,
        tc_gr_005_set_vals_method,
        tc_gr_006_set_vals_method,
        tc_gr_007_set_vals_method,
        tc_gr_008_set_vals_method,
        tc_gr_009_set_vals_method,
        tc_gr_010_set_vals_method,
        tc_gr_011_set_vals_method,
        tc_gr_012_set_vals_method,
        tc_gr_013_set_vals_method,
        tc_gr_014_set_vals_method,
        tc_gr_015_set_vals_method,
        tc_gr_016_set_vals_method,
        tc_ch_001_set_vals_method,
        tc_ch_002_set_vals_method,
        tc_ch_003_set_vals_method,
        tc_ch_004_set_vals_method,
        tc_ch_005_set_vals_method,
        tc_ch_006_set_vals_method,
        tc_ch_007_set_vals_method,
        tc_ch_008_set_vals_method,
        tc_ch_009_set_vals_method,
        tc_ch_010_set_vals_method,
        tc_ch_011_set_vals_method,
        tc_ch_012_set_vals_method,
        tc_ch_013_set_vals_method,
        tc_ch_014_set_vals_method,
        tc_ch_015_set_vals_method,
        tc_ch_016_set_vals_method,
        tc_ch_017_set_vals_method,
        tc_ch_018_set_vals_method,
        tc_ch_019_set_vals_method,
        tc_ch_020_set_vals_method,
        tc_ch_023_init_vals_method,
		tc_ch_023_set_vals_method,
        tc_img_005_link_method,
        #endif
        #if _AR4904 && _DD5_PROFILE
        menuTestMethod1,
        #endif
        clear_test_vals_visualtb
    }

    #if _DD5_PROFILE
    LOCAL_PARAMETERS
    {
        LOCAL_FL_VAL,   test_fl_val_local;
    }
    #endif
}

/*
******************************************************************************
** View Definitions
******************************************************************************
*/

VARIABLE_LIST   visualtb_view_1
{
        LABEL           "View 1" ;
        HELP            "View 1 Help" ;
        MEMBERS
        {
            /* standard transducer view members */
            VL_ST_REV,              PARAM.ST_REV;
            VL_MODE_BLK,            PARAM.MODE_BLK;
            VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
            VL_XD_ERROR,            PARAM.XD_ERROR;
        }
}

VARIABLE_LIST   visualtb_view_2
{
        LABEL           "View 2";
        HELP            "View 2 Help";
        MEMBERS
        {
            /* standard transducer view members */
            VL_ST_REV,              PARAM.ST_REV;
            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
         }
}

VARIABLE_LIST   visualtb_view_3
{
        LABEL           "View 3";
        HELP            "View 3 Help";
        MEMBERS
        {
            /* standard transducer view members */
            VL_ST_REV,              PARAM.ST_REV;
            VL_MODE_BLK,            PARAM.MODE_BLK;
            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
            VL_XD_ERROR,            PARAM.XD_ERROR;

            /* custom transducer view members */
            VL_TEST_FL_VAL_1,       PARAM.TEST_FL_VAL_1;
            VL_TEST_FL_VAL_2,       PARAM.TEST_FL_VAL_2;
            VL_TEST_FL_VAL_3,       PARAM.TEST_FL_VAL_3;
            VL_TEST_FL_VAL_4,       PARAM.TEST_FL_VAL_4;
            VL_TEST_VAL_INT_8,      PARAM.TEST_VAL_INT_8;
            VL_TEST_VAL_UINT_8,     PARAM.TEST_VAL_UINT_8;
            VL_TEST_VAL_INT_16,     PARAM.TEST_VAL_INT_16;
            VL_TEST_VAL_UINT_16,    PARAM.TEST_VAL_UINT_16;
            VL_TEST_VAL_INT_32,     PARAM.TEST_VAL_INT_32;
            VL_TEST_VAL_UINT_32,    PARAM.TEST_VAL_UINT_32;

            VL_ST_REV_01,           PARAM.ST_REV;
            VL_TEST_Y_ARRAY_1,      PARAM.TEST_Y_ARRAY_1;
            VL_TEST_X_ARRAY_1,      PARAM.TEST_X_ARRAY_1;
            VL_TEST_Y_ARRAY_2,      PARAM.TEST_Y_ARRAY_2;
            VL_TEST_X_ARRAY_2,      PARAM.TEST_X_ARRAY_2;
            VL_TEST_RECORD,         PARAM.TEST_RECORD;
            VL_TEST_STRING,         PARAM.TEST_STRING;
        }
}

VARIABLE_LIST   visualtb_view_4
{
        LABEL           "View 4";
        HELP            "View 4 Help";
        MEMBERS
        {
            /* standard transducer view members */
            VL_ST_REV,              PARAM.ST_REV;
            VL_MODE_BLK,            PARAM.MODE_BLK;
            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;

            /* custom transducer view members */
            VL_TEST_HI_HI_LIMIT,    PARAM.TEST_HI_HI_LIMIT;
            VL_TEST_HI_LIMIT,       PARAM.TEST_HI_LIMIT;
            VL_TEST_LO_LIMIT,       PARAM.TEST_LO_LIMIT;
            VL_TEST_LO_LO_LIMIT,    PARAM.TEST_LO_LO_LIMIT;
            VL_TEST_RIGHT_LIMIT,    PARAM.TEST_RIGHT_LIMIT;
            VL_TEST_LEFT_LIMIT,     PARAM.TEST_LEFT_LIMIT;
            VL_UPPER_RANGE_VALUE,   PARAM.UPPER_RANGE_VALUE;
            VL_LOWER_RANGE_VALUE,   PARAM.LOWER_RANGE_VALUE;
            VL_UPPER_SENSOR_LIMIT,  PARAM.UPPER_SENSOR_LIMIT;
            VL_LOWER_SENSOR_LIMIT,  PARAM.LOWER_SENSOR_LIMIT;
        }
}

/*
******************************************************************************
** Variable Definitions/Redefinitions
******************************************************************************
*/

/* test float variables */
test_fl_val_1 LIKE VARIABLE test_fl_val
{
    REDEFINE LABEL "Test Float Value 1";
}

test_fl_val_2 LIKE VARIABLE test_fl_val
{
    REDEFINE LABEL "Test Float Value 2";
}

test_fl_val_3 LIKE VARIABLE test_fl_val
{
    REDEFINE LABEL "Test Float Value 3";
}

test_fl_val_4 LIKE VARIABLE test_fl_val
{
    REDEFINE LABEL "Test Float Value 4";
}

/* test int/uint variables */
VARIABLE    test_val_int_8
{
    LABEL           "Test Integer8 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            INTEGER (1);
    HANDLING        READ & WRITE;
}

VARIABLE    test_val_uint_8
{
    LABEL           "Test Unsigned Integer8 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            UNSIGNED_INTEGER (1);
    HANDLING        READ & WRITE;
}

VARIABLE    test_val_int_16
{
    LABEL           "Test Integer16 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            INTEGER (2);
    HANDLING        READ & WRITE;
}

VARIABLE    test_val_uint_16
{
    LABEL           "Test Unsigned Integer16 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            UNSIGNED_INTEGER (2);
    HANDLING        READ & WRITE;
}

VARIABLE    test_val_int_32
{
    LABEL           "Test Integer32 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            INTEGER (4);
    HANDLING        READ & WRITE;
}

VARIABLE    test_val_uint_32
{
    LABEL           "Test Unsigned Integer32 Value";
    HELP            "An integer value used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            UNSIGNED_INTEGER (4);
    HANDLING        READ & WRITE;
}

/* test arrays of floats */
test_y_array_1 LIKE ARRAY test_array
{
    REDEFINE LABEL "Test Y-Array 1";
}

test_x_array_1 LIKE ARRAY test_array
{
    REDEFINE LABEL "Test X-Array 1";
}

test_y_array_2 LIKE ARRAY test_array
{
    REDEFINE LABEL "Test Y-Array 2";
}

test_x_array_2 LIKE ARRAY test_array
{
    REDEFINE LABEL "Test X-Array 2";
}

/* test record */
test_record LIKE RECORD __primary_value_1
{
    REDEFINE LABEL "Test Record";
    REDEFINE HELP  "A Value & Status - Float (DS-65) "
                   "used to test EDD visualizations.";
}

/* test string */
VARIABLE    test_string
{
    LABEL           "Test String";
    HELP            "A visible string [32] used to test EDD visualizations.";
    CLASS           CONTAINED & DYNAMIC;
    TYPE            VISIBLE (32);
    HANDLING        READ & WRITE;
}

/* test limits */
test_hi_hi_limit LIKE VARIABLE __hi_hi_lim
{
    REDEFINE LABEL "Test Hi Hi Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

test_hi_limit LIKE VARIABLE __hi_lim
{
    REDEFINE LABEL "Test Hi Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

test_lo_limit LIKE VARIABLE __lo_lim
{
    REDEFINE LABEL "Test Lo Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

test_lo_lo_limit LIKE VARIABLE __lo_lo_lim
{
    REDEFINE LABEL "Test Lo Lo Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

test_right_limit LIKE VARIABLE __hi_lim
{
    REDEFINE LABEL "Right Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

test_left_limit LIKE VARIABLE __lo_lim
{
    REDEFINE LABEL "Left Limit";
    REDEFINE HELP  _VISTB_ALARM_HELP;
}

/* range value */
upper_range_value LIKE VARIABLE __range_hi
{
    REDEFINE LABEL "Upper Range Value";
    REDEFINE HELP  _VISTB_RANGE_HELP;
}

lower_range_value LIKE VARIABLE __range_lo
{
    REDEFINE LABEL "Lower Range Value";
    REDEFINE HELP  _VISTB_RANGE_HELP;
}

/* sensor limits */
upper_sensor_limit LIKE VARIABLE __hi_lim
{
    REDEFINE LABEL "Upper Sensor Limit";
    REDEFINE HELP  _VISTB_LIMIT_HELP;
}

lower_sensor_limit LIKE VARIABLE __lo_lim
{
    REDEFINE LABEL "Lower Sensor Limit";
    REDEFINE HELP  _VISTB_LIMIT_HELP;
}
