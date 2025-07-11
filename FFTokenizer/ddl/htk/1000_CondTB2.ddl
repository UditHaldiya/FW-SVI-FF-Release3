/*****************************************************************************/
/* 1000_CondTB2.ddl                                                          */
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
/* 09-24-09 ! ARs 3159                                          ! 2.0 ! ms   */
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

RECORD      cond2tb_character
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

BLOCK   COND2TB
{
	CHARACTERISTICS cond2tb_character;
	LABEL "Conditional Transducer Block2";
    HELP  "This custom transducer block is used to test "
          "the EDD conditionals functionality.";
	PARAMETERS
	{
        /* standard transducer parameters */
/*1*/          ST_REV,                     __st_rev ;
/*2*/          TAG_DESC,                   __tag_desc ;
/*3*/          STRATEGY,                   __strategy ;
/*4*/          ALERT_KEY,                  __alert_key ;
/*5*/          MODE_BLK,                   __mode_blk ;
/*6*/          BLOCK_ERR,                  __block_err ;
/*7*/          UPDATE_EVT,                 __update_evt ;
/*8*/          BLOCK_ALM,                  __block_alm ;
/*9*/          TRANSDUCER_DIRECTORY,       __transducer_directory ;
/*10*/         TRANSDUCER_TYPE,            __transducer_type ;
/*11*/         XD_ERROR,                   __xd_error ;
/*12*/         COLLECTION_DIRECTORY,       __collection_directory ;

        /* custom transducer parameters */
/*13*/        TEST_INPUT_VAR,             test_input_var;
/*14*/        TEST_INPUT_ARY_1,           test_input_ary_1;
/*15*/        TEST_INPUT_ARY_2,           test_input_ary_2;
/*16*/        TEST_INPUT_ENUM,            test_input_enum;

        /* conditional test parameters */
/*17*/        COND0050_VAR,               cond0050_var;
/*18*/        COND0051A_VAR,              cond0051a_var;
/*19*/        COND0051B_VAR,              cond0051b_var;
/*20*/        COND0051C_VAR,              cond0051c_var;
/*21*/        COND0051D_VAR,              cond0051d_var;
/*22*/        COND0052A_VAR,              cond0052a_var;
/*23*/        COND0052B_VAR,              cond0052b_var;
/*24*/        COND0052C_VAR,              cond0052c_var;
/*25*/        COND0052D_VAR,              cond0052d_var;
/*26*/        COND0052E_VAR,              cond0052e_var;
/*27*/        COND0053A_VAR,              cond0053a_var;
/*28*/        COND0053B_VAR,              cond0053b_var;
/*29*/        COND0053C_VAR,              cond0053c_var;
/*30*/        COND0053D_VAR,              cond0053d_var;
/*31*/        COND0054A_VAR,              cond0054a_var;
/*32*/        COND0054B_VAR,              cond0054b_var;
/*33*/        COND0055A_VAR,              cond0055a_var;
/*34*/        COND0055B_VAR,              cond0055b_var;
/*35*/        COND0055C_VAR,              cond0055c_var;
/*36*/        COND0055D_VAR,              cond0055d_var;
/*37*/        COND0055E_VAR,              cond0055e_var;
/*38*/        COND0055F_VAR,              cond0055f_var;
/*39*/        COND0055G_VAR,              cond0055g_var;
/*40*/        COND0055H_VAR,              cond0055h_var;
/*41*/        COND0056A_VAR,              cond0056a_var;
/*42*/        COND0056B_VAR,              cond0056b_var;
/*43*/        COND0057A_VAR,              cond0057a_var;
/*44*/        COND0057B_VAR,              cond0057b_var;
/*45*/        COND0057C_VAR,              cond0057c_var;
/*46*/        COND0058A_VAR,              cond0058a_var;
/*47*/        COND0058B_VAR,              cond0058b_var;
/*48*/        COND0058C_VAR,              cond0058c_var;
/*49*/        COND0059A_VAR,              cond0059a_var;
/*50*/        COND0059B_VAR,              cond0059b_var;
/*51*/        COND0060A_VAR,              cond0060a_var;
/*52*/        COND0060B_VAR,              cond0060b_var;
/*53*/        COND0060C_VAR,              cond0060c_var;
/*54*/        COND0061A_VAR,              cond0061a_var;
/*55*/        COND0061B_VAR,              cond0061b_var;
/*56*/        COND0061C_VAR,              cond0061c_var;
/*57*/        COND0061D_VAR,              cond0061d_var;
/*58*/        COND0061E_VAR,              cond0061e_var;
/*59*/        COND0070_VAR,               cond0070_var;
/*60*/        COND0071_VAR,               cond0071_var;
/*61*/        COND0072_VAR,               cond0072_var;
/*62*/        COND0073_VAR,               cond0073_var;
/*63*/        COND0081_VALIDITY_VAR,      cond0081_validity_var;
              #ifndef DEVREV1
              TEST_INPUT_INT,             test_input_int;   /* AR3159 */
              #endif
    }

    PARAMETER_LISTS
	{
		VIEW_1, cond2tb_view_1;
		VIEW_2, cond2tb_view_2;
		VIEW_3, cond2tb_view_3;
		VIEW_4, cond2tb_view_4;
    }

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_condtb2,
                #else
                Menu_Top_condtb2,
                #endif
                
                device_root_menu_condtb2

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_condtb2
                #if !_AR4940
                ,hh_diagnostics_root_menu_condtb2
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_condtb2
                #if !_AR4940
                ,hh_process_variables_root_menu_condtb2
                #endif
                #endif
    }
    
    METHOD_ITEMS
    {
        cond0080_validity_method,
        clear_test_vals_condtb2
    }
}

/*
******************************************************************************
** View Definitions
******************************************************************************
*/

VARIABLE_LIST   cond2tb_view_1
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

VARIABLE_LIST   cond2tb_view_2
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

VARIABLE_LIST   cond2tb_view_3
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

VARIABLE_LIST   cond2tb_view_4
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
/*13*/            VL_TEST_INPUT_VAR,      PARAM.TEST_INPUT_VAR;
/*14*/            VL_TEST_INPUT_ARY_1,    PARAM.TEST_INPUT_ARY_1;
/*15*/            VL_TEST_INPUT_ARY_2,    PARAM.TEST_INPUT_ARY_2;
/*16*/            VL_TEST_INPUT_ENUM,     PARAM.TEST_INPUT_ENUM;
/*17*/            VL_COND0050_VAR,        PARAM.COND0050_VAR;
/*18*/            VL_COND0051A_VAR,       PARAM.COND0051A_VAR;
/*19*/            VL_COND0051B_VAR,       PARAM.COND0051B_VAR;
/*20*/            VL_COND0051C_VAR,       PARAM.COND0051C_VAR;
/*21*/            VL_COND0051D_VAR,       PARAM.COND0051D_VAR;
/*22*/            VL_COND0052A_VAR,       PARAM.COND0052A_VAR;
/*23*/            VL_COND0052B_VAR,       PARAM.COND0052B_VAR;
/*24*/            VL_COND0052C_VAR,       PARAM.COND0052C_VAR;
/*25*/            VL_COND0052D_VAR,       PARAM.COND0052D_VAR;
/*26*/            VL_COND0052E_VAR,       PARAM.COND0052E_VAR;
/*27*/            VL_COND0053A_VAR,       PARAM.COND0053A_VAR;
/*28*/            VL_COND0053B_VAR,       PARAM.COND0053B_VAR;
/*29*/            VL_COND0053C_VAR,       PARAM.COND0053C_VAR;
/*30*/            VL_COND0053D_VAR,       PARAM.COND0053D_VAR;
/*31*/            VL_COND0054A_VAR,       PARAM.COND0054A_VAR;
/*32*/            VL_COND0054B_VAR,       PARAM.COND0054B_VAR;
/*33*/            VL_COND0055A_VAR,       PARAM.COND0055A_VAR;
/*34*/            VL_COND0055B_VAR,       PARAM.COND0055B_VAR;
/*35*/            VL_COND0055C_VAR,       PARAM.COND0055C_VAR;
/*36*/            VL_COND0055D_VAR,       PARAM.COND0055D_VAR;
/*37*/            VL_COND0055E_VAR,       PARAM.COND0055E_VAR;
/*38*/            VL_COND0055F_VAR,       PARAM.COND0055F_VAR;

/*1*/            VL_ST_REV_01,           PARAM.ST_REV;
/*39*/            VL_COND0055G_VAR,       PARAM.COND0055G_VAR;
/*40*/            VL_COND0055H_VAR,       PARAM.COND0055H_VAR;
/*41*/            VL_COND0056A_VAR,       PARAM.COND0056A_VAR;
/*42*/            VL_COND0056B_VAR,       PARAM.COND0056B_VAR;
/*43*/            VL_COND0057A_VAR,       PARAM.COND0057A_VAR;
/*44*/            VL_COND0057B_VAR,       PARAM.COND0057B_VAR;
/*45*/            VL_COND0057C_VAR,       PARAM.COND0057C_VAR;
/*46*/            VL_COND0058A_VAR,       PARAM.COND0058A_VAR;
/*47*/            VL_COND0058B_VAR,       PARAM.COND0058B_VAR;
/*48*/            VL_COND0058C_VAR,       PARAM.COND0058C_VAR;
/*49*/            VL_COND0059A_VAR,       PARAM.COND0059A_VAR;
/*50*/            VL_COND0059B_VAR,       PARAM.COND0059B_VAR;
/*51*/            VL_COND0060A_VAR,       PARAM.COND0060A_VAR;
/*52*/            VL_COND0060B_VAR,       PARAM.COND0060B_VAR;
/*53*/            VL_COND0060C_VAR,       PARAM.COND0060C_VAR;
/*54*/            VL_COND0061A_VAR,       PARAM.COND0061A_VAR;
/*55*/            VL_COND0061B_VAR,       PARAM.COND0061B_VAR;
/*56*/            VL_COND0061C_VAR,       PARAM.COND0061C_VAR;
/*57*/            VL_COND0061D_VAR,       PARAM.COND0061D_VAR;
/*58*/            VL_COND0061E_VAR,       PARAM.COND0061E_VAR;
/*59*/            VL_COND0070_VAR,        PARAM.COND0070_VAR;
/*60*/            VL_COND0071_VAR,        PARAM.COND0071_VAR;
/*61*/            VL_COND0072_VAR,        PARAM.COND0072_VAR;
/*62*/            VL_COND0073_VAR,        PARAM.COND0073_VAR;
/*63*/            VL_COND0081_VALIDITY_VAR, PARAM.COND0081_VALIDITY_VAR;
                  #ifndef DEVREV1
                  VL_TEST_INPUT_INT,        PARAM.TEST_INPUT_INT;   /* AR3159 */
                  #endif
        }
}