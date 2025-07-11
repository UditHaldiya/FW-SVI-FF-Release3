/*****************************************************************************/
/* 1000_CondTB1.ddl                                                          */
/*                                                                           */
/*   This DDL file defines a custom transducer block that is used to test    */
/*   DD conditionals.                                                        */
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
/* 03-27-07 ! Redone all conditional variables to have full     ! 1.0 ! ms   */
/*          !  definitions instead of LIKE re-definitions.      !     !      */
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

RECORD      cond1tb_character
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

BLOCK   COND1TB
{
	CHARACTERISTICS cond1tb_character;
	LABEL "Conditional Transducer Block1";
    HELP  "This custom transducer block is used to test "
          "the EDD conditionals functionality.";
	PARAMETERS
	{
        /* standard transducer parameters */
/*1*/         ST_REV,                     __st_rev ;
/*2*/         TAG_DESC,                   __tag_desc ;
/*3*/         STRATEGY,                   __strategy ;
/*4*/         ALERT_KEY,                  __alert_key ;
/*5*/         MODE_BLK,                   __mode_blk ;
/*6*/         BLOCK_ERR,                  __block_err ;
/*7*/         UPDATE_EVT,                 __update_evt ;
/*8*/         BLOCK_ALM,                  __block_alm ;
/*9*/         TRANSDUCER_DIRECTORY,       __transducer_directory ;
/*10*/        TRANSDUCER_TYPE,            __transducer_type ;
/*11*/        XD_ERROR,                   __xd_error ;
/*12*/        COLLECTION_DIRECTORY,       __collection_directory ;

        /* custom transducer parameters */
/*13*/        TEST_INPUT_VAR,             test_input_var;
/*14*/        TEST_INPUT_REC,             test_input_rec;
/*15*/        TEST_INPUT_ARY_1,           test_input_ary_1;
/*16*/        TEST_INPUT_ARY_2,           test_input_ary_2;
/*17*/        TEST_INPUT_ENUM,            test_input_enum;
/*18*/        TEST_INPUT_BIT_ENUM,        test_input_bit_enum;

        /* conditional test parameters */
/*19*/        COND0010_FLOAT_VAR,         cond0010_float_var;
/*20*/        COND0010_ENUM_VAR,          cond0010_enum_var;
/*21*/        COND0010_BIT_ENUM_VAR,      cond0010_bit_enum_var;
/*22*/        COND0011_FLOAT_VAR,         cond0011_float_var;
/*23*/        COND0011_ENUM_VAR,          cond0011_enum_var;
/*24*/        COND0011_BIT_ENUM_VAR,      cond0011_bit_enum_var;
/*25*/        COND0012_FLOAT_VAR,         cond0012_float_var;
/*26*/        COND0012_ENUM_VAR,          cond0012_enum_var;
/*27*/        COND0012_BIT_ENUM_VAR,      cond0012_bit_enum_var;
/*28*/        COND0013_FLOAT_VAR,         cond0013_float_var;
/*29*/        COND0013_ENUM_VAR,          cond0013_enum_var;
/*30*/        COND0013_BIT_ENUM_VAR,      cond0013_bit_enum_var;
/*31*/        COND0014_FLOAT_VAR,         cond0014_float_var;
/*32*/        COND0014_ENUM_VAR,          cond0014_enum_var;
/*33*/        COND0014_BIT_ENUM_VAR,      cond0014_bit_enum_var;
/*34*/        COND0015_FLOAT_VAR,         cond0015_float_var;
/*35*/        COND0015_ENUM_VAR,          cond0015_enum_var;
/*36*/        COND0015_BIT_ENUM_VAR,      cond0015_bit_enum_var;
/*37*/        COND0016_FLOAT_VAR,         cond0016_float_var;
/*38*/        COND0016_ENUM_VAR,          cond0016_enum_var;
/*39*/        COND0016_BIT_ENUM_VAR,      cond0016_bit_enum_var;
/*40*/        COND0017_FLOAT_VAR,         cond0017_float_var;
/*41*/        COND0017_ENUM_VAR,          cond0017_enum_var;
/*42*/        COND0017_BIT_ENUM_VAR,      cond0017_bit_enum_var;
/*43*/        COND0018A_FLOAT_VAR,        cond0018a_float_var;
/*44*/        COND0018A_ENUM_VAR,         cond0018a_enum_var;
/*45*/        COND0018A_BIT_ENUM_VAR,     cond0018a_bit_enum_var;
/*46*/        COND0018B_FLOAT_VAR,        cond0018b_float_var;
/*47*/        COND0018B_ENUM_VAR,         cond0018b_enum_var;
/*48*/        COND0018B_BIT_ENUM_VAR,     cond0018b_bit_enum_var;
/*49*/        COND0019_FLOAT_VAR,         cond0019_float_var;
/*50*/        COND0019_ENUM_VAR,          cond0019_enum_var;
/*51*/        COND0019_BIT_ENUM_VAR,      cond0019_bit_enum_var;
/*52*/        COND0020_FLOAT_VAR,         cond0020_float_var;
/*53*/        COND0020_ENUM_VAR,          cond0020_enum_var;
/*54*/        COND0020_BIT_ENUM_VAR,      cond0020_bit_enum_var;
/*55*/        COND0021_FLOAT_VAR,         cond0021_float_var;
/*56*/        COND0021_ENUM_VAR,          cond0021_enum_var;
/*57*/        COND0021_BIT_ENUM_VAR,      cond0021_bit_enum_var;
/*58*/        COND0022_FLOAT_VAR,         cond0022_float_var;
/*59*/        COND0022_ENUM_VAR,          cond0022_enum_var;
/*60*/        COND0022_BIT_ENUM_VAR,      cond0022_bit_enum_var;
/*61*/        COND0023_FLOAT_VAR,         cond0023_float_var;
/*62*/        COND0023_ENUM_VAR,          cond0023_enum_var;
/*63*/        COND0023_BIT_ENUM_VAR,      cond0023_bit_enum_var;
/*64*/        COND0024_FLOAT_VAR,         cond0024_float_var;
/*65*/        COND0024_ENUM_VAR,          cond0024_enum_var;
/*66*/        COND0024_BIT_ENUM_VAR,      cond0024_bit_enum_var;
/*67*/        COND0025_FLOAT_VAR,         cond0025_float_var;
/*68*/        COND0025_ENUM_VAR,          cond0025_enum_var;
/*69*/        COND0025_BIT_ENUM_VAR,      cond0025_bit_enum_var;
/*70*/        COND0026_FLOAT_VAR,         cond0026_float_var;
/*71*/        COND0026_ENUM_VAR,          cond0026_enum_var;
/*72*/        COND0026_BIT_ENUM_VAR,      cond0026_bit_enum_var;
/*73*/        COND0027A_FLOAT_VAR,        cond0027a_float_var;
/*74*/        COND0027A_ENUM_VAR,         cond0027a_enum_var;
/*75*/        COND0027A_BIT_ENUM_VAR,     cond0027a_bit_enum_var;
/*76*/        COND0027B_FLOAT_VAR,        cond0027b_float_var;
/*77*/        COND0027B_ENUM_VAR,         cond0027b_enum_var;
/*78*/        COND0027B_BIT_ENUM_VAR,     cond0027b_bit_enum_var;
/*79*/        COND0028A_FLOAT_VAR,        cond0028a_float_var;
/*80*/        COND0028A_ENUM_VAR,         cond0028a_enum_var;
/*81*/        COND0028A_BIT_ENUM_VAR,     cond0028a_bit_enum_var;
/*82*/        COND0028B_FLOAT_VAR,        cond0028b_float_var;
/*83*/        COND0028B_ENUM_VAR,         cond0028b_enum_var;
/*84*/        COND0028B_BIT_ENUM_VAR,     cond0028b_bit_enum_var;
/*85*/        COND0028C_FLOAT_VAR,        cond0028c_float_var;
/*86*/        COND0028C_ENUM_VAR,         cond0028c_enum_var;
/*87*/        COND0028C_BIT_ENUM_VAR,     cond0028c_bit_enum_var;
/*88*/        COND0029A_FLOAT_VAR,        cond0029a_float_var;
/*89*/        COND0029A_ENUM_VAR,         cond0029a_enum_var;
/*90*/        COND0029A_BIT_ENUM_VAR,     cond0029a_bit_enum_var;
/*91*/        COND0029B_FLOAT_VAR,        cond0029b_float_var;
/*92*/        COND0029B_ENUM_VAR,         cond0029b_enum_var;
/*93*/        COND0029B_BIT_ENUM_VAR,     cond0029b_bit_enum_var;
/*94*/        COND0029C_FLOAT_VAR,        cond0029c_float_var;
/*95*/        COND0029C_ENUM_VAR,         cond0029c_enum_var;
/*96*/        COND0029C_BIT_ENUM_VAR,     cond0029c_bit_enum_var;
/*97*/        COND0030A_FLOAT_VAR,        cond0030a_float_var;
/*98*/        COND0030A_ENUM_VAR,         cond0030a_enum_var;
/*99*/        COND0030A_BIT_ENUM_VAR,     cond0030a_bit_enum_var;
/*100*/        COND0030B_FLOAT_VAR,        cond0030b_float_var;
/*101*/        COND0030B_ENUM_VAR,         cond0030b_enum_var;
/*102*/        COND0030B_BIT_ENUM_VAR,     cond0030b_bit_enum_var;
/*103*/        COND0030C_FLOAT_VAR,        cond0030c_float_var;
/*104*/        COND0030C_ENUM_VAR,         cond0030c_enum_var;
/*105*/        COND0030C_BIT_ENUM_VAR,     cond0030c_bit_enum_var;
/*106*/        COND0031_FLOAT_VAR,         cond0031_float_var;
/*107*/        COND0031_ENUM_VAR,          cond0031_enum_var;
/*108*/        COND0031_BIT_ENUM_VAR,      cond0031_bit_enum_var;
    }

    PARAMETER_LISTS
	{
		VIEW_1, cond1tb_view_1;
		VIEW_2, cond1tb_view_2;
		VIEW_3, cond1tb_view_3;
		VIEW_4, cond1tb_view_4;
    }

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_condtb1,
                #else
                Menu_Top_condtb1,
                #endif
                
                device_root_menu_condtb1

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_condtb1
                #if !_AR4940
                ,hh_diagnostics_root_menu_condtb1
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_condtb1
                #if !_AR4940
                ,hh_process_variables_root_menu_condtb1
                #endif
                #endif
    }

    METHOD_ITEMS
    {
		write_display_format_1_method,
		write_display_format_2_method,
		write_edit_format_1_method,
		write_edit_format_2_method,
		write_min_value_1_method,
		write_min_value_2_method,
		write_max_value_1_method,
		write_max_value_2_method,
		write_enum_value_1_method,
		write_enum_value_2_method,
		write_bit_enum_value_1_method,
		write_bit_enum_value_2_method,
		write_constant_unit_1_method,
		write_constant_unit_2_method,
		write_handling_1_method,
		write_handling_2_method,
		write_validity_1_method,
		write_validity_2_method,
        clear_test_vals_condtb1
    }

    COLLECTION_ITEMS
    {
        test_input_col
    }

    #if _DD5_PROFILE
    LOCAL_PARAMETERS
    {
        LOCAL_INPUT_VAR,    local_input_var;
        LOCAL_INPUT_REC,    local_input_rec;
        LOCAL_INPUT_ARY,    local_input_ary;
    }

    LIST_ITEMS
    {
        test_input_list
    }

    FILE_ITEMS
    {
       condtb1_input_file
    }

	FILES
	{
		CONDTB1_INPUT_FILE, condtb1_input_file;
	}

	GRAPHS
	{
		TEST_GRAPH_CONDTB1, test_graph_condtb1;
	}
	CHARTS
	{
		TEST_CHART_CONDTB1, test_chart_condtb1;
	}
    #endif 
}       

/*
******************************************************************************
** View Definitions
******************************************************************************
*/

VARIABLE_LIST   cond1tb_view_1
{
        LABEL           "View 1" ;
        HELP            "View 1 Help" ;
        MEMBERS
        {
            /* standard transducer view members */
/*1*/            VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
/*10*/            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
/*11*/            VL_XD_ERROR,            PARAM.XD_ERROR;
        }
}

VARIABLE_LIST   cond1tb_view_2
{
        LABEL           "View 2";
        HELP            "View 2 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/            VL_ST_REV,              PARAM.ST_REV;
/*10*/            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
        }
}

VARIABLE_LIST   cond1tb_view_3
{
        LABEL           "View 3";
        HELP            "View 3 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/            VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
/*10*/            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
/*11*/            VL_XD_ERROR,            PARAM.XD_ERROR;
        }
}

VARIABLE_LIST   cond1tb_view_4
{
        LABEL           "View 4";
        HELP            "View 4 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/            VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
/*10*/            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;

            /* custom transducer view members */
/*13*/            VL_TEST_INPUT_VAR,          PARAM.TEST_INPUT_VAR;
/*14*/            VL_TEST_INPUT_REC,          PARAM.TEST_INPUT_REC;
/*15*/            VL_TEST_INPUT_ARY_1,        PARAM.TEST_INPUT_ARY_1;
/*16*/            VL_TEST_INPUT_ARY_2,        PARAM.TEST_INPUT_ARY_2;
/*17*/            VL_TEST_INPUT_ENUM,         PARAM.TEST_INPUT_ENUM;
/*18*/            VL_TEST_INPUT_BIT_ENUM,     PARAM.TEST_INPUT_BIT_ENUM;
/*19*/            VL_COND0010_FLOAT_VAR,      PARAM.COND0010_FLOAT_VAR;
/*20*/            VL_COND0010_ENUM_VAR,       PARAM.COND0010_ENUM_VAR;
/*21*/            VL_COND0010_BIT_ENUM_VAR,   PARAM.COND0010_BIT_ENUM_VAR;
/*22*/            VL_COND0011_FLOAT_VAR,      PARAM.COND0011_FLOAT_VAR;
/*23*/            VL_COND0011_ENUM_VAR,       PARAM.COND0011_ENUM_VAR;
/*24*/            VL_COND0011_BIT_ENUM_VAR,   PARAM.COND0011_BIT_ENUM_VAR;
/*25*/            VL_COND0012_FLOAT_VAR,      PARAM.COND0012_FLOAT_VAR;
/*26*/            VL_COND0012_ENUM_VAR,       PARAM.COND0012_ENUM_VAR;
/*27*/            VL_COND0012_BIT_ENUM_VAR,   PARAM.COND0012_BIT_ENUM_VAR;
/*28*/            VL_COND0013_FLOAT_VAR,      PARAM.COND0013_FLOAT_VAR;
/*29*/            VL_COND0013_ENUM_VAR,       PARAM.COND0013_ENUM_VAR;
/*30*/            VL_COND0013_BIT_ENUM_VAR,   PARAM.COND0013_BIT_ENUM_VAR;
/*31*/            VL_COND0014_FLOAT_VAR,      PARAM.COND0014_FLOAT_VAR;
/*32*/            VL_COND0014_ENUM_VAR,       PARAM.COND0014_ENUM_VAR;
/*33*/            VL_COND0014_BIT_ENUM_VAR,   PARAM.COND0014_BIT_ENUM_VAR;
/*34*/            VL_COND0015_FLOAT_VAR,      PARAM.COND0015_FLOAT_VAR;
/*35*/            VL_COND0015_ENUM_VAR,       PARAM.COND0015_ENUM_VAR;
/*36*/            VL_COND0015_BIT_ENUM_VAR,   PARAM.COND0015_BIT_ENUM_VAR;
/*37*/            VL_COND0016_FLOAT_VAR,      PARAM.COND0016_FLOAT_VAR;
/*38*/            VL_COND0016_ENUM_VAR,       PARAM.COND0016_ENUM_VAR;
/*39*/            VL_COND0016_BIT_ENUM_VAR,   PARAM.COND0016_BIT_ENUM_VAR;

/*1*/            VL_ST_REV_01,               PARAM.ST_REV;
/*40*/            VL_COND0017_FLOAT_VAR,      PARAM.COND0017_FLOAT_VAR;
/*41*/            VL_COND0017_ENUM_VAR,       PARAM.COND0017_ENUM_VAR;
/*42*/            VL_COND0017_BIT_ENUM_VAR,   PARAM.COND0017_BIT_ENUM_VAR;
/*43*/            VL_COND0018A_FLOAT_VAR,     PARAM.COND0018A_FLOAT_VAR;
/*44*/            VL_COND0018A_ENUM_VAR,      PARAM.COND0018A_ENUM_VAR;
/*45*/            VL_COND0018A_BIT_ENUM_VAR,  PARAM.COND0018A_BIT_ENUM_VAR;
/*46*/            VL_COND0018B_FLOAT_VAR,     PARAM.COND0018B_FLOAT_VAR;
/*47*/            VL_COND0018B_ENUM_VAR,      PARAM.COND0018B_ENUM_VAR;
/*48*/            VL_COND0018B_BIT_ENUM_VAR,  PARAM.COND0018B_BIT_ENUM_VAR;
/*49*/            VL_COND0019_FLOAT_VAR,      PARAM.COND0019_FLOAT_VAR;
/*50*/            VL_COND0019_ENUM_VAR,       PARAM.COND0019_ENUM_VAR;
/*51*/            VL_COND0019_BIT_ENUM_VAR,   PARAM.COND0019_BIT_ENUM_VAR;
/*52*/            VL_COND0020_FLOAT_VAR,      PARAM.COND0020_FLOAT_VAR;
/*53*/            VL_COND0020_ENUM_VAR,       PARAM.COND0020_ENUM_VAR;
/*54*/            VL_COND0020_BIT_ENUM_VAR,   PARAM.COND0020_BIT_ENUM_VAR;
/*55*/            VL_COND0021_FLOAT_VAR,      PARAM.COND0021_FLOAT_VAR;
/*56*/            VL_COND0021_ENUM_VAR,       PARAM.COND0021_ENUM_VAR;
/*57*/            VL_COND0021_BIT_ENUM_VAR,   PARAM.COND0021_BIT_ENUM_VAR;
/*58*/            VL_COND0022_FLOAT_VAR,      PARAM.COND0022_FLOAT_VAR;
/*59*/            VL_COND0022_ENUM_VAR,       PARAM.COND0022_ENUM_VAR;
/*60*/            VL_COND0022_BIT_ENUM_VAR,   PARAM.COND0022_BIT_ENUM_VAR;
/*61*/            VL_COND0023_FLOAT_VAR,      PARAM.COND0023_FLOAT_VAR;
/*62*/            VL_COND0023_ENUM_VAR,       PARAM.COND0023_ENUM_VAR;
/*63*/            VL_COND0023_BIT_ENUM_VAR,   PARAM.COND0023_BIT_ENUM_VAR;
/*64*/            VL_COND0024_FLOAT_VAR,      PARAM.COND0024_FLOAT_VAR;
/*65*/            VL_COND0024_ENUM_VAR,       PARAM.COND0024_ENUM_VAR;
/*66*/            VL_COND0024_BIT_ENUM_VAR,   PARAM.COND0024_BIT_ENUM_VAR;
/*67*/            VL_COND0025_FLOAT_VAR,      PARAM.COND0025_FLOAT_VAR;
/*68*/            VL_COND0025_ENUM_VAR,       PARAM.COND0025_ENUM_VAR;
/*69*/            VL_COND0025_BIT_ENUM_VAR,   PARAM.COND0025_BIT_ENUM_VAR;

/*1*/            VL_ST_REV_02,               PARAM.ST_REV;
/*70*/            VL_COND0026_FLOAT_VAR,      PARAM.COND0026_FLOAT_VAR;
/*71*/            VL_COND0026_ENUM_VAR,       PARAM.COND0026_ENUM_VAR;
/*72*/            VL_COND0026_BIT_ENUM_VAR,   PARAM.COND0026_BIT_ENUM_VAR;
/*73*/            VL_COND0027A_FLOAT_VAR,     PARAM.COND0027A_FLOAT_VAR;
/*74*/            VL_COND0027A_ENUM_VAR,      PARAM.COND0027A_ENUM_VAR;
/*75*/            VL_COND0027A_BIT_ENUM_VAR,  PARAM.COND0027A_BIT_ENUM_VAR;
/*76*/            VL_COND0027B_FLOAT_VAR,     PARAM.COND0027B_FLOAT_VAR;
/*77*/            VL_COND0027B_ENUM_VAR,      PARAM.COND0027B_ENUM_VAR;
/*78*/            VL_COND0027B_BIT_ENUM_VAR,  PARAM.COND0027B_BIT_ENUM_VAR;
/*79*/             VL_COND0028A_FLOAT_VAR,     PARAM.COND0028A_FLOAT_VAR;
/*80*/             VL_COND0028A_ENUM_VAR,      PARAM.COND0028A_ENUM_VAR;
/*81*/             VL_COND0028A_BIT_ENUM_VAR,  PARAM.COND0028A_BIT_ENUM_VAR;
/*82*/             VL_COND0028B_FLOAT_VAR,     PARAM.COND0028B_FLOAT_VAR;
/*83*/             VL_COND0028B_ENUM_VAR,      PARAM.COND0028B_ENUM_VAR;
/*84*/             VL_COND0028B_BIT_ENUM_VAR,  PARAM.COND0028B_BIT_ENUM_VAR;
/*85*/             VL_COND0028C_FLOAT_VAR,     PARAM.COND0028C_FLOAT_VAR;
/*86*/             VL_COND0028C_ENUM_VAR,      PARAM.COND0028C_ENUM_VAR;
/*87*/             VL_COND0028C_BIT_ENUM_VAR,  PARAM.COND0028C_BIT_ENUM_VAR;
/*88*/             VL_COND0029A_FLOAT_VAR,     PARAM.COND0029A_FLOAT_VAR;
/*89*/             VL_COND0029A_ENUM_VAR,      PARAM.COND0029A_ENUM_VAR;
/*90*/             VL_COND0029A_BIT_ENUM_VAR,  PARAM.COND0029A_BIT_ENUM_VAR;
/*91*/             VL_COND0029B_FLOAT_VAR,     PARAM.COND0029B_FLOAT_VAR;
/*92*/             VL_COND0029B_ENUM_VAR,      PARAM.COND0029B_ENUM_VAR;
/*93*/             VL_COND0029B_BIT_ENUM_VAR,  PARAM.COND0029B_BIT_ENUM_VAR;
/*94*/             VL_COND0029C_FLOAT_VAR,     PARAM.COND0029C_FLOAT_VAR;
/*95*/             VL_COND0029C_ENUM_VAR,      PARAM.COND0029C_ENUM_VAR;
/*96*/             VL_COND0029C_BIT_ENUM_VAR,  PARAM.COND0029C_BIT_ENUM_VAR;
/*97*/             VL_COND0030A_FLOAT_VAR,     PARAM.COND0030A_FLOAT_VAR;
/*98*/             VL_COND0030A_ENUM_VAR,      PARAM.COND0030A_ENUM_VAR;
/*99*/             VL_COND0030A_BIT_ENUM_VAR,  PARAM.COND0030A_BIT_ENUM_VAR;

/*1*/            VL_ST_REV_03,               PARAM.ST_REV;
/*100*/            VL_COND0030B_FLOAT_VAR,     PARAM.COND0030B_FLOAT_VAR;
/*101*/            VL_COND0030B_ENUM_VAR,      PARAM.COND0030B_ENUM_VAR;
/*102*/            VL_COND0030B_BIT_ENUM_VAR,  PARAM.COND0030B_BIT_ENUM_VAR;
/*103*/            VL_COND0030C_FLOAT_VAR,     PARAM.COND0030C_FLOAT_VAR;
/*104*/            VL_COND0030C_ENUM_VAR,      PARAM.COND0030C_ENUM_VAR;
/*105*/            VL_COND0030C_BIT_ENUM_VAR,  PARAM.COND0030C_BIT_ENUM_VAR;
/*106*/            VL_COND0031_FLOAT_VAR,      PARAM.COND0031_FLOAT_VAR;
/*107*/            VL_COND0031_ENUM_VAR,       PARAM.COND0031_ENUM_VAR;
/*108*/            VL_COND0031_BIT_ENUM_VAR,   PARAM.COND0031_BIT_ENUM_VAR;
        }
}
