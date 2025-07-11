/*****************************************************************************/
/* 1000_ChannelTB.ddl                                                        */
/*                                                                           */
/*   This DDL file defines a custom transducer block that groups the         */
/*   channels for the enhanced function blocks of this device.               */
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
/* 02-23-07 ! replaced all channel_block_view_ with             ! 1.0 ! awc  */
/*          !  channel_view_                                    !     !      */
/* 04-11-07 ! defined unique character record for block		    ! 1.0 ! awc  */
/* 04-11-07 ! removed function parameters for output blocks	    ! 1.0 ! awc  */
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

RECORD      channeltb_character
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

BLOCK   CHANNELTB
{
	CHARACTERISTICS channeltb_character;
	LABEL "Channel Transducer Block";
    HELP  "This custom transducer block is a grouping "
          "of channels for the enhanced function blocks.";
	PARAMETERS
	{
        /* standard transducer parameters */
/*1*/        ST_REV,                     __st_rev ;
/*2*/        TAG_DESC,                   __tag_desc ;
/*3*/        STRATEGY,                   __strategy ;
/*4*/        ALERT_KEY,                  __alert_key ;
/*5*/        MODE_BLK,                   __mode_blk ;
/*6*/        BLOCK_ERR,                  __block_err ;
/*7*/        UPDATE_EVT,                 __update_evt ;
/*8*/        BLOCK_ALM,                  __block_alm ;
/*9*/        TRANSDUCER_DIRECTORY,       __transducer_directory ;
/*10*/        TRANSDUCER_TYPE,            __transducer_type ;
/*11*/        XD_ERROR,                   __xd_error ;
/*12*/        COLLECTION_DIRECTORY,       __collection_directory ;



        /* custom transducer parameters */
/*13*/        PRIMARY_VALUE_AI,           primary_value_ai;
/*14*/        PRIMARY_VALUE_RANGE_AI,     primary_value_range_ai;
/*15*/        AI_FUNCTION,                ai_function;
/*16*/        PRIMARY_VALUE_AO,           primary_value_ao;
/*17*/        PRIMARY_VALUE_RANGE_AO,     primary_value_range_ao;
/*18*/        PRIMARY_VALUE_DI,           primary_value_di;
/*19*/        DI_FUNCTION,                di_function;
/*20*/        PRIMARY_VALUE_DO,           primary_value_do;
/*21*/        PRIMARY_VALUE_MAI,          primary_value_mai;
/*22*/        PRIMARY_VALUE_RANGE_MAI,    primary_value_range_mai;
/*23*/        MAI_FUNCTION,               mai_function;
/*24*/        PRIMARY_VALUE_MAO,          primary_value_mao;
/*25*/        PRIMARY_VALUE_RANGE_MAO,    primary_value_range_mao;
/*26*/        PRIMARY_VALUE_MDI,          primary_value_mdi;
/*27*/        MDI_FUNCTION,               mdi_function;
/*28*/        PRIMARY_VALUE_MDO,          primary_value_mdo;
/*29*/        FUNCTION_PERIOD,            function_period;
/*30*/        AI_HI_ALARM,                ai_hi_alarm  ;
/*31*/        AI_HI_LIM,                  ai_hi_lim  ;
/*32*/        AI_HI_PRI,                  ai_hi_pri  ;
/*33*/        DI_ALM,                     di_alm;
/*34*/        DI_LIM,                     di_lim;
/*35*/        DI_PRI,                     di_pri;
    }


            /* custom transducer view members */
    PARAMETER_LISTS
	{
		VIEW_1, channeltb_view_1;
		VIEW_2, channeltb_view_2;
		VIEW_3, channeltb_view_3;
		VIEW_4, channeltb_view_4;
	}

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_channeltb,
                #else
                Menu_Top_channeltb,
                #endif
                
                device_root_menu_channeltb

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_channeltb
                #if !_AR4940
                ,hh_diagnostics_root_menu_channeltb
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_channeltb
                #if !_AR4940
                ,hh_process_variables_root_menu_channeltb
                #endif
                #endif
    }
}

/*
******************************************************************************
** View Definitions
******************************************************************************
*/
VARIABLE_LIST   channeltb_view_1
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

            /* custom transducer view members */
/*13*/           VL_PRIMARY_VALUE_AI,    PARAM.PRIMARY_VALUE_AI;
/*16*/            VL_PRIMARY_VALUE_AO,    PARAM.PRIMARY_VALUE_AO;
/*18*/            VL_PRIMARY_VALUE_DI,    PARAM.PRIMARY_VALUE_DI;
/*20*/            VL_PRIMARY_VALUE_DO,    PARAM.PRIMARY_VALUE_DO;
/*21*/            VL_PRIMARY_VALUE_MAI,   PARAM.PRIMARY_VALUE_MAI;
/*24*/             VL_PRIMARY_VALUE_MAO,   PARAM.PRIMARY_VALUE_MAO;
/*26*/            VL_PRIMARY_VALUE_MDI,   PARAM.PRIMARY_VALUE_MDI;
/*30*/            VL_AI_HI_ALARM,         PARAM.AI_HI_ALARM;
/*33*/            VL_DI_ALM,              PARAM.DI_ALM;
        }
}

VARIABLE_LIST   channeltb_view_2
{
        LABEL           "View 2";
        HELP            "View 2 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/            VL_ST_REV,              PARAM.ST_REV;
/*10*/            VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;

            /* custom transducer view members */
/*15*/            VL_AI_FUNCTION,         PARAM.AI_FUNCTION;
/*19*/            VL_DI_FUNCTION,         PARAM.DI_FUNCTION;
/*23*/            VL_MAI_FUNCTION,        PARAM.MAI_FUNCTION;
/*27*/            VL_MDI_FUNCTION,        PARAM.MDI_FUNCTION;
/*29*/            VL_FUNCTION_PERIOD,     PARAM.FUNCTION_PERIOD;
/*31*/            VL_AI_HI_LIM,           PARAM.AI_HI_LIM;
/*32*/            VL_AI_HI_PRI,           PARAM.AI_HI_PRI;
/*34*/            VL_DI_LIM,              PARAM.DI_LIM;
/*35*/            VL_DI_PRI,              PARAM.DI_PRI;
        }
}

VARIABLE_LIST   channeltb_view_3
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

            /* custom transducer view members */
/*13*/           VL_PRIMARY_VALUE_AI,    PARAM.PRIMARY_VALUE_AI;
/*16*/            VL_PRIMARY_VALUE_AO,    PARAM.PRIMARY_VALUE_AO;
/*18*/            VL_PRIMARY_VALUE_DI,    PARAM.PRIMARY_VALUE_DI;
/*20*/            VL_PRIMARY_VALUE_DO,    PARAM.PRIMARY_VALUE_DO;
/*21*/            VL_PRIMARY_VALUE_MAI,   PARAM.PRIMARY_VALUE_MAI;
/*24*/             VL_PRIMARY_VALUE_MAO,   PARAM.PRIMARY_VALUE_MAO;
/*26*/            VL_PRIMARY_VALUE_MDI,   PARAM.PRIMARY_VALUE_MDI;
/*30*/            VL_AI_HI_ALARM,         PARAM.AI_HI_ALARM;
/*33*/            VL_DI_ALM,              PARAM.DI_ALM;
        }
}

VARIABLE_LIST   channeltb_view_4
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
/*15*/            VL_AI_FUNCTION,         PARAM.AI_FUNCTION;
/*19*/            VL_DI_FUNCTION,         PARAM.DI_FUNCTION;
/*23*/            VL_MAI_FUNCTION,        PARAM.MAI_FUNCTION;
/*27*/            VL_MDI_FUNCTION,        PARAM.MDI_FUNCTION;
/*29*/            VL_FUNCTION_PERIOD,     PARAM.FUNCTION_PERIOD;
/*31*/            VL_AI_HI_LIM,           PARAM.AI_HI_LIM;
/*32*/            VL_AI_HI_PRI,           PARAM.AI_HI_PRI;
/*34*/            VL_DI_LIM,              PARAM.DI_LIM;
/*35*/            VL_DI_PRI,              PARAM.DI_PRI;
        }
}

/*
******************************************************************************
** Variable Definitions/Redefinitions
******************************************************************************
*/

/* AI parameters */
primary_value_ai LIKE RECORD __primary_value
{
    REDEFINE LABEL "Primary Value AI";

}

primary_value_range_ai LIKE RECORD __primary_value_range
{
    REDEFINE LABEL "Primary Value Range AI";
}

ai_function LIKE VARIABLE analog_function
{
    REDEFINE LABEL "AI Function";
}

/* AO parameters */
primary_value_ao LIKE RECORD __primary_value
{
    REDEFINE LABEL "Primary Value AO";
}

primary_value_range_ao LIKE RECORD __primary_value_range
{
    REDEFINE LABEL "Primary Value Range AO";
}

/* DI parameters */
primary_value_di LIKE RECORD __primary_value
{
    REDEFINE LABEL  "Primary Value DI";
    REDEFINE HELP   [primary_value_decimal_help];
    MEMBERS
    {
        REDEFINE VALUE, __discrete_contained_r;
    }
}

di_function LIKE VARIABLE discrete_function
{
    REDEFINE LABEL "DI Function";
}

/* DO parameters */
primary_value_do LIKE RECORD __primary_value
{
    REDEFINE LABEL  "Primary Value DO";
    REDEFINE HELP   [primary_value_decimal_help];
    MEMBERS
    {
        REDEFINE VALUE, __discrete_contained_r;
    }
}

/* MAI parameters */
primary_value_mai LIKE RECORD __primary_value
{
    REDEFINE LABEL "Primary Value MAI";
}

primary_value_range_mai LIKE RECORD __primary_value_range
{
    REDEFINE LABEL "Primary Value Range MAI";
}

mai_function LIKE VARIABLE analog_function
{
    REDEFINE LABEL "MAI Function";
}

/* MAO parameters */
primary_value_mao LIKE RECORD __primary_value
{
    REDEFINE LABEL "Primary Value MAO";
}

primary_value_range_mao LIKE RECORD __primary_value_range
{
    REDEFINE LABEL "Primary Value Range MAO";
}

/* MDI parameters */
primary_value_mdi LIKE RECORD __primary_value
{
    REDEFINE LABEL  "Primary Value MDI";
    REDEFINE HELP   [primary_value_decimal_help];
    MEMBERS
    {
        REDEFINE VALUE, __discrete_contained_r;
    }
}

mdi_function LIKE VARIABLE discrete_function
{
    REDEFINE LABEL "MDI Function";
}

/* MDO parameters */
primary_value_mdo LIKE RECORD __primary_value
{
    REDEFINE LABEL  "Primary Value MDO";
    REDEFINE HELP   [primary_value_decimal_help];
    MEMBERS
    {
        REDEFINE VALUE, __discrete_contained_r;
    }
}

/* function period */
VARIABLE    function_period
{
    LABEL   "Function Period";
    HELP    "This enumerated parameter sets the "
            "period of execution for this block's "
            "function parameters in seconds.";
    CLASS   CONTAINED;
    TYPE    ENUMERATED (1)
    {
        _FUNCTION_PERIOD_ENUM
    }    
    CONSTANT_UNIT   [unit_code_1054];
    HANDLING        READ & WRITE;
}


/*
**********************************************************************
ai_hi_alarm      (DS-71)

**********************************************************************
*/
RECORD      ai_hi_alarm
{
    LABEL           [hi_alm_label] ;
    HELP            [hi_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __float_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
ai_hi_lim

**********************************************************************
*/
VARIABLE    ai_hi_lim
{
    LABEL           [hi_lim_label] ;
    HELP            [hi_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            FLOAT ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
ai_hi_pri

**********************************************************************
*/
VARIABLE    ai_hi_pri
{
    LABEL           [hi_pri_label] ;
    HELP            [hi_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}

/*
**********************************************************************
di_alm        (DS-72)

**********************************************************************
*/
RECORD      di_alm
{
    LABEL           [disc_alm_label] ;
    HELP            [disc_alm_help] ;
    MEMBERS
    {
        UNACKNOWLEDGED,  __unacknowledged ;
        ALARM_STATE,     __alarm_state ;
        TIME_STAMP,      __time_stamp ;
        SUB_CODE,        __sub_code ;
        VALUE,           __discrete_value ;
    }
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
di_lim

**********************************************************************
*/
VARIABLE    di_lim
{
    LABEL           [disc_lim_label] ;
    HELP            [disc_lim_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1) ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}
/*
**********************************************************************
di_pri

**********************************************************************
*/
VARIABLE    di_pri
{
    LABEL           [disc_pri_label] ;
    HELP            [disc_pri_help] ;
    CLASS           CONTAINED & ALARM ;
    TYPE            UNSIGNED_INTEGER (1)
    {
        MAX_VALUE   15 ;
    }
    CONSTANT_UNIT   [blank] ;
    HANDLING        READ & WRITE ;
/*  RESPONSE_CODES  xxx ; */
}










