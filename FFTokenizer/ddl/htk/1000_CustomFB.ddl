/*****************************************************************************/
/* 1000_CustomFB.ddl                                                         */
/*                                                                           */
/*   This DDL file defines a custom function block for this device.          */
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
/* 02-23-07 !replaced all testfb_block_view_ with testfb_view_  ! 1.0 ! awc  */
/* 04-11-07 ! defined unique character record for block		    ! 1.0 ! awc  */
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

RECORD      testfb_character
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

BLOCK   TESTFB
{
	CHARACTERISTICS testfb_character;
	LABEL "Custom Function Block";
    HELP  "This custom function block is modeled after the ITK "
          "Test Functin Block and is functionaly equivalent.";
	PARAMETERS
	{
		ST_REV,                 __st_rev ;
		TAG_DESC,               __tag_desc ;
		STRATEGY,               __strategy ;
		ALERT_KEY,              __alert_key ;
		MODE_BLK,               __mode_blk ;
        BLOCK_ERR,              __block_err ;
        IN_A_1, 				in_a_1;
        IN_A_2, 				in_a_2;
        IN_A_3, 				in_a_3;
        IN_A_4, 				in_a_4;
        IN_A_5, 				in_a_5;
        IN_A_6, 				in_a_6;
        IN_A_7, 				in_a_7;
        IN_A_8, 				in_a_8;
        IN_A_9, 				in_a_9;
        IN_A_10, 				in_a_10;
        IN_A_11, 				in_a_11;
        IN_A_12, 				in_a_12;
        IN_A_13, 				in_a_13;
        IN_A_14, 				in_a_14;
        IN_A_15, 				in_a_15;
        IN_A_16, 				in_a_16;
	    IN_D_1, 				in_d_1;
        IN_D_2, 				in_d_2;
        IN_D_3, 				in_d_3;
        IN_D_4, 				in_d_4;
        IN_D_5, 				in_d_5;
        IN_D_6, 				in_d_6;
        IN_D_7, 				in_d_7;
        IN_D_8, 				in_d_8;
        IN_D_9, 				in_d_9;
        IN_D_10, 				in_d_10;
        IN_D_11, 				in_d_11;
        IN_D_12, 				in_d_12;
        IN_D_13, 				in_d_13;
        IN_D_14, 				in_d_14;
        IN_D_15, 				in_d_15;
        IN_D_16, 				in_d_16;
        OUT_A_1, 				out_a_1;
        OUT_A_2, 				out_a_2;
        OUT_A_3, 				out_a_3;
        OUT_A_4, 				out_a_4;
        OUT_A_5, 				out_a_5;
        OUT_A_6, 				out_a_6;
        OUT_A_7, 				out_a_7;
        OUT_A_8, 				out_a_8;
        OUT_A_9, 				out_a_9;
        OUT_A_10, 			    out_a_10;
        OUT_A_11, 			    out_a_11;
        OUT_A_12, 			    out_a_12;
        OUT_A_13, 			    out_a_13;
        OUT_A_14, 			    out_a_14;
        OUT_A_15, 			    out_a_15;
        OUT_A_16, 			    out_a_16;
	    OUT_D_1, 				out_d_1;
        OUT_D_2, 				out_d_2;
        OUT_D_3, 				out_d_3;
        OUT_D_4, 				out_d_4;
        OUT_D_5, 				out_d_5;
        OUT_D_6, 				out_d_6;
        OUT_D_7, 				out_d_7;
        OUT_D_8, 				out_d_8;
        OUT_D_9, 				out_d_9;
        OUT_D_10, 			    out_d_10;
        OUT_D_11, 			    out_d_11;
        OUT_D_12, 			    out_d_12;
        OUT_D_13, 			    out_d_13;
        OUT_D_14, 			    out_d_14;
        OUT_D_15, 			    out_d_15;
        OUT_D_16, 			    out_d_16;
		EXECUTION_COUNTER,      execution_counter;
		CONTROL_STATUS,         control_status;
		IN_OUT_INDEX,           in_out_index;
		OFFSET,                 offset;
		ANALOG_TEST_VALUE,      analog_test_value;
		DISCRETE_TEST_VALUE,    discrete_test_value;
		DISC_ALM,               __disc_alm;
		SUPPORTED_MODES,        supported_modes;
	}

	PARAMETER_LISTS
	{
		VIEW_1, testfb_view_1;
		VIEW_2, testfb_view_2;
		VIEW_3, testfb_view_3;
		VIEW_4, testfb_view_4;

	}

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_customfb,
                #else
                Menu_Top_customfb,
                #endif
                
                device_root_menu_customfb

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_customfb
                #if !_AR4940
                ,hh_diagnostics_root_menu_customfb
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_customfb
                #if !_AR4940
                ,hh_process_variables_root_menu_customfb
                #endif
                #endif
    }
}

/*
******************************************************************************
** View Definitions
******************************************************************************
*/


VARIABLE_LIST   testfb_view_1
{
        LABEL           "View 1" ;
        HELP            "View 1 Help" ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        }
}

VARIABLE_LIST   testfb_view_2
{
        LABEL           "View 2" ;
        HELP            "View 2 Help" ;
        MEMBERS
        {
                VL_ST_REV,                  PARAM.ST_REV ;
                VL_EXECUTION_COUNTER,       PARAM.EXECUTION_COUNTER ;
                VL_CONTROL_STATUS,          PARAM.CONTROL_STATUS ;
                VL_IN_OUT_INDEX,            PARAM.IN_OUT_INDEX ;
                VL_OFFSET,                  PARAM.OFFSET ;
                VL_ANALOG_TEST_VALUE,       PARAM.ANALOG_TEST_VALUE ;
                VL_DISCRETE_TEST_VALUE,     PARAM.DISCRETE_TEST_VALUE ;
                VL_DISC_ALM,                PARAM.DISC_ALM ;
        }
}
VARIABLE_LIST   testfb_view_3
{
        LABEL           "View 3" ;
        HELP            "View 3 Help" ;
        MEMBERS
        {
                VL_ST_REV,      PARAM.ST_REV ;
                VL_MODE_BLK,    PARAM.MODE_BLK ;
                VL_BLOCK_ERR,   PARAM.BLOCK_ERR ;
        }
}

VARIABLE_LIST   testfb_view_4
{
        LABEL           "View 4" ;
        HELP            "View 4 Help" ;
        MEMBERS
        {
                VL_ST_REV,                  PARAM.ST_REV ;
                VL_EXECUTION_COUNTER,       PARAM.EXECUTION_COUNTER ;
                VL_CONTROL_STATUS,          PARAM.CONTROL_STATUS ;
                VL_IN_OUT_INDEX,            PARAM.IN_OUT_INDEX ;
                VL_OFFSET,                  PARAM.OFFSET ;
                VL_ANALOG_TEST_VALUE,       PARAM.ANALOG_TEST_VALUE ;
                VL_DISCRETE_TEST_VALUE,     PARAM.DISCRETE_TEST_VALUE ;
                VL_DISC_ALM,                PARAM.DISC_ALM ;
        }
}

/*
******************************************************************************
** Variable Definitions
******************************************************************************
*/

VARIABLE supported_modes
{
	CLASS	CONTAINED;
	LABEL	"Supported Modes";
	TYPE BIT_ENUMERATED (1)
	{
        _MODE_REMOTE_OUTPUT,
        _MODE_REMOTE_CASCADE,
        _MODE_CASCADE,
        _MODE_AUTOMATIC,
        _MODE_MANUAL,
        _MODE_LOCKED,
        _MODE_INITIALIZATION,
        _MODE_OUT_OF_SERVICE
        }

}

VARIABLE execution_counter
{
	CLASS	CONTAINED & DYNAMIC;
	HANDLING READ&WRITE;
	LABEL	"execution_counter";
	TYPE UNSIGNED_INTEGER (2);
}

VARIABLE control_status
{
	CLASS	CONTAINED & DYNAMIC;
	HANDLING READ&WRITE;
	LABEL	"control_status";
	TYPE UNSIGNED_INTEGER (2);
}

VARIABLE in_out_index
{
	CLASS	CONTAINED;
	HANDLING READ&WRITE;
	LABEL	"in_out_index";
	TYPE UNSIGNED_INTEGER (2);
}

VARIABLE offset
{
	CLASS	CONTAINED;
	HANDLING READ&WRITE;
	LABEL	"offset";
	TYPE UNSIGNED_INTEGER (2);
}

RECORD      analog_test_value
{
    LABEL           "analog test value" ;
    HELP            "analog test value" ;
    MEMBERS
    {
        STATUS,  status_contained_nd ;
        VALUE,   float_contained_nd ;
    }
}

RECORD      discrete_test_value
{
    LABEL           "discrete test value" ;
    HELP            "discrete test value" ;
    MEMBERS
    {
        STATUS,  status_contained_nd ;
        VALUE,   discrete_contained_nd ;
    }
}


status_contained_nd LIKE VARIABLE __status_contained_nd
{

	REDEFINE HANDLING WRITE;
}

discrete_contained_nd LIKE VARIABLE __discrete_contained_nd
{

	REDEFINE HANDLING WRITE;
}

float_contained_nd LIKE VARIABLE __float_contained_nd
{

	REDEFINE HANDLING WRITE;
}

in_a_1 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_1";

}

in_a_2 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_2";
}

in_a_3 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_3";
}

in_a_4 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_4";
}

in_a_5 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_5";
}

in_a_6 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_6";
}

in_a_7 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_7";
}

in_a_8 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_8";
}

in_a_9 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_9";
}

in_a_10 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_10";
}

in_a_11 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_11";
}

in_a_12 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_12";
}

in_a_13 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_13";
}

in_a_14 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_14";
}

in_a_15 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_15";
}

in_a_16 LIKE RECORD __in
{
	REDEFINE LABEL "IN_A_16";
}


out_a_1 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_1";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_2 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_2";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_3 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_3";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_4 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_4";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_5 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_5";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_6 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_6";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_7 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_7";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_8 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_8";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_9 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_9";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_10 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_10";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_11 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_11";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_12 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_12";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_13 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_13";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_14 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_14";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_15 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_15";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_a_16 LIKE RECORD __out
{
	REDEFINE LABEL "OUT_A_16";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

RECORD      in_d
{

    LABEL   "in_d";
    HELP     "help";
    MEMBERS
    {
        STATUS,  __status_input ;
        VALUE,   __discrete_input ;
    }
}

in_d_1 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_1";
}

in_d_2 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_2";
}

in_d_3 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_3";
}

in_d_4 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_4";
}

in_d_5 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_5";
}

in_d_6 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_6";
}

in_d_7 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_7";
}

in_d_8 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_8";
}

in_d_9 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_9";
}

in_d_10 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_10";
}

in_d_11 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_11";
}

in_d_12 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_12";
}

in_d_13 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_13";
}

in_d_14 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_14";
}

in_d_15 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_15";
}

in_d_16 LIKE RECORD in_d
{
	REDEFINE LABEL "IN_D_16";
}

out_d_1 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_1";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_2 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_2";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_3 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_3";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_4 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_4";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_5 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_5";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_6 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_6";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_7 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_7";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_8 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_8";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_9 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_9";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_10 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_10";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_11 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_11";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_12 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_12";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_13 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_13";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_14 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_14";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_15 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_15";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}

out_d_16 LIKE RECORD __out_d
{
	REDEFINE LABEL "OUT_D_16";
    #if _AR4625
    MEMBERS { REDEFINE STATUS,  __status_output_nd ; }
    #endif
}
