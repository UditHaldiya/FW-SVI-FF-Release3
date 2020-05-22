/*****************************************************************************/
/* 1000_DataTypesTB.ddl                                                      */
/*                                                                           */
/*   This DDL file defines a custom transducer block that contains           */
/*   parameters of FF defined data-types.                                    */
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
/* 02-23-07 ! replaced all datatypesTB_block_view_ with         ! 1.0 ! awc  */
/*          !  dtatypesTB_view_                                 !     !      */
/*          !                                                   !     !      */
/* 03-28-07 ! dissabled record definitions for DS149 & DS152    ! 1.0 ! ms   */
/* 04-11-07 ! defined unique character record for block		    ! 1.0 ! awc  */
/* 04-11-07 ! dissabled var/arr defs for EUC/ASCII types        ! 1.0 ! ms   */
/* 08-22-08 ! AR2096: changed v_bool from enum to bool          !1.0.1! ms   */
/* 09-24-07 ! AR4388 - changed __event_update to __update_evt	! 1.1 ! ms   */
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

RECORD      datatypestb_character
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

BLOCK   DATATYPESTB
{
	CHARACTERISTICS datatypestb_character;
	LABEL "Data Types Transducer Block";
    HELP  "This custom transducer block contains "
          "parameters of FF defined data-types.";
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

        /* variable parameters */
/*13*/        V_BOOLEAN,                  v_bool;
/*14*/        V_INTEGER8,                 v_int8;
/*15*/        V_INTEGER16,                v_int16;
/*16*/        V_INTEGER32,                v_int32;
/*17*/        V_UNSIGNED8,                v_uint8;
/*18*/        V_UNSIGNED16,               v_uint16;
/*19*/        V_UNSIGNED32,               v_uint32;
/*20*/        V_UNSIGNED8_ENUM,           v_enum8;
/*21*/        V_UNSIGNED16_ENUM,          v_enum16;
/*22*/        V_UNSIGNED32_ENUM,          v_enum32;
/*23*/        V_FLOATING_POINT,          v_floating_point ;
/*24*/        V_VISIBLESTRING,            v_vis_string32;
/*25*/        V_OCTETSTRING,              v_oct_string32;
/*26*/        V_OCTETSTRING_PASSWORD,     v_passwd_string32;
/*27*/        V_BITSTRING8,               v_bitstring8;
/*28*/        V_BITSTRING16,              v_bitstring16;
/*29*/        V_BITSTRING32,              v_bitstring32;
/*30*/        V_BITSTRING8_BITENUM,       v_bit_enum8;
/*31*/        V_BITSTRING16_BITENUM,      v_bit_enum16;
/*32*/        V_BITSTRING32_BITENUM,      v_bit_enum32;
/*33*/        V_DATE,                     v_date;
/*34*/        V_TIMEOFDAY,                v_time;
/*35*/        V_TIMEDIFF,                 v_duration;
/*36*/        V_TIMEVALUE,                v_time_value;

        /* array parameters */
/*37*/        A_BOOLEAN,                  a_bool;
/*38*/        A_INTEGER8,                 a_int8;
/*39*/        A_INTEGER16,                a_int16;
/*40*/        A_INTEGER32,                a_int32;
/*41*/        A_UNSIGNED8,                a_uint8;
/*42*/        A_UNSIGNED16,               a_uint16;
/*43*/        A_UNSIGNED32,               a_uint32;
/*44*/        A_UNSIGNED8_ENUM,           a_enum8;
/*45*/        A_UNSIGNED16_ENUM,          a_enum16;
/*46*/        A_UNSIGNED32_ENUM,          a_enum32;
/*47*/        A_FLOATING_POINT,           a_floating_point;
/*48*/        A_VISIBLESTRING,            a_vis_string32;
/*49*/        A_OCTETSTRING,              a_oct_string32;
/*50*/        A_OCTETSTRING_PASSWORD,     a_passwd_string32;
/*51*/        A_BITSTRING8,               a_bitstring8;
/*52*/        A_BITSTRING16,              a_bitstring16;
/*53*/        A_BITSTRING32,              a_bitstring32;
/*54*/        A_BITSTRING8_BITENUM,       a_bit_enum8;
/*55*/        A_BITSTRING16_BITENUM,      a_bit_enum16;
/*56*/        A_BITSTRING32_BITENUM,      a_bit_enum32;
/*57*/        A_DATE,                     a_date;
/*58*/        A_TIMEOFDAY,                a_time;
/*59*/        A_TIMEDIFF,                 a_duration;
/*60*/        A_TIMEVALUE,                a_time_value;

        /* data-structure parameters */
/*61*/        R_DS65,	                    r_ds65;
/*62*/        R_DS66,	                    r_ds66;
/*63*/        R_DS67,	                    r_ds67;
/*64*/        R_DS141,	                r_ds141;
/*65*/        R_DS142,	                r_ds142;
/*66*/        R_DS143,	                r_ds143;
/*67*/        R_DS144,	                r_ds144;
/*68*/        R_DS145,	                r_ds145;
/*69*/        R_DS146,	                r_ds146;
/*70*/        R_DS147,	                r_ds147;
/*71*/        R_DS150,                  r_ds150;
/*72*/        R_DS153,                  r_ds153;
/*73*/        R_DS154,                  r_ds154;
/*74*/        R_DS155,                  r_ds155;
/*75*/        R_DS156,                  r_ds156;
/*76*/        R_DS157,                  r_ds157;
/*77*/        R_DS159,                  r_ds159;
/*78*/        R_DS160,                  r_ds160;
/*79*/        R_DS161,                  r_ds161;
/*80*/        R_DS162,                  r_ds162;
/*81*/        R_DS163,                  r_ds163;
/*82*/        R_DS164,                  r_ds164;
/*83*/        R_DS256,                  r_ds256;
/*84*/        R_DS257,                  r_ds257;
    }

    PARAMETER_LISTS
	{
		VIEW_1, datatypestb_view_1;
		VIEW_2, datatypestb_view_2;
		VIEW_3, datatypestb_view_3;
		VIEW_4, datatypestb_view_4;
	}

    MENU_ITEMS
    {
                #if !_AR4940
                hh_device_root_menu_datatypestb,
                #else
                Menu_Top_datatypestb,
                #endif
                
                device_root_menu_datatypestb

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_datatypestb
                #if !_AR4940
                ,hh_diagnostics_root_menu_datatypestb
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_datatypestb
                #if !_AR4940
                ,hh_process_variables_root_menu_datatypestb
                #endif
                #endif
    }

    METHOD_ITEMS
    {
        tc_meth_001
        #if _DD5_PROFILE
        ,tc_meth_003
        ,TC_File_001_step_1
        ,TC_File_001_step_2
        ,TC_File_002_step_1
        ,TC_File_002_step_2
        ,TC_File_003_step_1
        ,TC_File_003_step_2
        ,TC_File_004_step_1
        ,TC_File_004_step_2
        ,TC_File_005_step_1
        ,TC_File_005_step_2
        #if !_AR5572
        ,TC_File_006_step_1
        ,TC_File_006_step_2
        #endif
        ,TC_File_012_step_1
        ,TC_File_012_step_2
        /* AR3855
        ,TC_File_013_step_1
        ,TC_File_013_step_2
		,TC_File_014_step_1
		,TC_File_014_step_2 */
        ,TC_List_001
        ,TC_List_002
        ,TC_List_003
        ,TC_List_004
        ,TC_List_005
        ,TC_List_006
        #endif
        ,operate_method
        ,service_method
    }

    #if _DD5_PROFILE
    LOCAL_PARAMETERS
    {
        LOC_INPUT_VAR,			fl_input_var;
		LOC_INPUT_ENUM,			fl_input_enum_var;
		LOC_INPUT_BIT_ENUM,		fl_input_bit_enum_var;
		LOC_INPUT_REC,			fl_input_rec;
		LOC_INPUT_ARR,			fl_input_arr;
    }    

    COLLECTION_ITEMS
    {
        fl_input_collection,
        fl_blk_parm_collection,
        no_download_datatypestb,
        upload_wanted_datatypestb
    }

    FILE_ITEMS
    {
        fl_input_file,
        #if !_AR5274
        fl_blk_param_file,
        #endif
		fl_nested_list_file
    }

    LIST_ITEMS
    {
        fl_input_var_list,
        fl_input_enum_var_list,
        fl_input_bit_enum_var_list,
        fl_input_rec_list,
        fl_input_arr_list,
        fl_input_col_list,
        fl_blk_parm_var_list,
        fl_blk_parm_enum_var_list,
        fl_blk_parm_bit_enum_var_list,
        fl_blk_parm_rec_list,
        fl_blk_parm_arr_list,
        fl_blk_parm_col_list,
        fl_input_var_list_with_cap,
		fl_outer_list,
		fl_inner_list
    }
    #endif
}

/*
******************************************************************************
** View Definitions
******************************************************************************
*/

VARIABLE_LIST   datatypestb_view_1
{
        LABEL           "View 1" ;
        HELP            "View 1 Help" ;
        MEMBERS
        {
            /* standard transducer view members */
/*1*/             VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR ;
/*10*/             VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
/*11*/            VL_XD_ERROR,            PARAM.XD_ERROR;
        }
}

VARIABLE_LIST   datatypestb_view_2
{
        LABEL           "View 2";
        HELP            "View 2 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/             VL_ST_REV,              PARAM.ST_REV;
/*10*/             VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
         }
}

VARIABLE_LIST   datatypestb_view_3
{
        LABEL           "View 3";
        HELP            "View 3 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/             VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
/*10*/             VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
/*11*/            VL_XD_ERROR,            PARAM.XD_ERROR;

            /* custom transducer view members */
/*13*/            VL_V_BOOLEAN,           PARAM.V_BOOLEAN;
/*14*/            VL_V_INTEGER8,          PARAM.V_INTEGER8;
/*15*/            VL_V_INTEGER16,         PARAM.V_INTEGER16;
/*16*/            VL_V_INTEGER32,         PARAM.V_INTEGER32;
/*17*/            VL_V_UNSIGNED8,         PARAM.V_UNSIGNED8;
/*18*/            VL_V_UNSIGNED16,        PARAM.V_UNSIGNED16;
/*19*/            VL_V_UNSIGNED32,        PARAM.V_UNSIGNED32;
/*20*/            VL_V_UNSIGNED8_ENUM,    PARAM.V_UNSIGNED8_ENUM;
/*21*/            VL_V_UNSIGNED16_ENUM,   PARAM.V_UNSIGNED16_ENUM;
/*22*/            VL_V_UNSIGNED32_ENUM,   PARAM.V_UNSIGNED32_ENUM;
/*23*/            VL_V_FLOATING_POINT,    PARAM.V_FLOATING_POINT;
/*24*/            VL_V_VISIBLESTRING,     PARAM.V_VISIBLESTRING;
/*25*/            VL_V_OCTETSTRING,       PARAM.V_OCTETSTRING;

/*1*/            VL_ST_REV_01,           PARAM.ST_REV;
/*26*/            VL_V_OCTETSTRING_PASSWORD, PARAM.V_OCTETSTRING_PASSWORD;
/*27*/            VL_V_BITSTRING8,        PARAM.V_BITSTRING8;
/*28*/            VL_V_BITSTRING16,       PARAM.V_BITSTRING16;

/*1*/            VL_ST_REV_02,           PARAM.ST_REV;
/*29*/            VL_V_BITSTRING32,       PARAM.V_BITSTRING32;
/*30*/            VL_V_BITSTRING8_BITENUM, PARAM.V_BITSTRING8_BITENUM;
/*31*/            VL_V_BITSTRING16_BITENUM, PARAM.V_BITSTRING16_BITENUM;
/*32*/            VL_V_BITSTRING32_BITENUM, PARAM.V_BITSTRING32_BITENUM;
/*33*/            VL_V_DATE,              PARAM.V_DATE;
/*34*/            VL_V_TIMEOFDAY,         PARAM.V_TIMEOFDAY;
/*35*/            VL_V_TIMEDIFF,          PARAM.V_TIMEDIFF;
/*36*/            VL_V_TIMEVALUE,         PARAM.V_TIMEVALUE;
        }
}

VARIABLE_LIST   datatypestb_view_4
{
        LABEL           "View 4";
        HELP            "View 4 Help";
        MEMBERS
        {
            /* standard transducer view members */
/*1*/             VL_ST_REV,              PARAM.ST_REV;
/*5*/            VL_MODE_BLK,            PARAM.MODE_BLK;
/*6*/            VL_BLOCK_ERR,           PARAM.BLOCK_ERR;
/*10*/             VL_TRANSDUCER_TYPE,     PARAM.TRANSDUCER_TYPE;
        }
}

/*
******************************************************************************
** Variable Definitions/Redefinitions
******************************************************************************
*/

/* integer/enumerated variables */
VARIABLE    v_bool
{
    LABEL           "Variable Boolean";
    CLASS           CONTAINED;
    TYPE            BOOLEAN;
    HANDLING        READ & WRITE;
}

VARIABLE    v_int8
{
    LABEL           "Variable Integer8";
    CLASS           CONTAINED & OPERATE;
    TYPE            INTEGER (1);
    HANDLING        READ & WRITE;
}

VARIABLE    v_int16
{
    LABEL           "Variable Integer16";
    CLASS           CONTAINED & SERVICE;
    TYPE            INTEGER (2);
    HANDLING        READ & WRITE;
}

VARIABLE    v_int32
{
    LABEL           "Variable Integer32";
    CLASS           CONTAINED;
    TYPE            INTEGER (4);
    HANDLING        READ & WRITE;
}

VARIABLE    v_uint8
{
    LABEL           "Variable Unsigned Integer8";
    CLASS           CONTAINED & OPERATE;
    TYPE            UNSIGNED_INTEGER (1);
    HANDLING        READ & WRITE;
}

VARIABLE    v_uint16
{
    LABEL           "Variable Unsigned Integer16";
    CLASS           CONTAINED & SERVICE;
    TYPE            UNSIGNED_INTEGER (2);
    HANDLING        READ & WRITE;
}

VARIABLE    v_uint32
{
    LABEL           "Variable Unsigned Integer32";
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (4);
    HANDLING        READ & WRITE;
}

VARIABLE    v_enum8
{
    LABEL           "Variable Unsigned8 Enumerated";
    CLASS           CONTAINED & OPERATE;
    TYPE            ENUMERATED (1)
    {
        _DATATYPESTB_ENUM8
    }
    HANDLING        READ & WRITE;
}

VARIABLE    v_enum16
{
    LABEL           "Variable Unsigned16 Enumerated";
    CLASS           CONTAINED & SERVICE;
    TYPE            ENUMERATED (2)
    {
        _DATATYPESTB_ENUM16
    }
    HANDLING        READ & WRITE;
}

VARIABLE    v_enum32
{
    LABEL           "Variable Unsigned32 Enumerated";
    CLASS           CONTAINED;
    TYPE            ENUMERATED (4)
    {
        _DATATYPESTB_ENUM32
    }
    HANDLING        READ & WRITE;
}

/* double variable */
VARIABLE    v_floating_point
{
    LABEL           "Variable Floating Point ";
    CLASS           CONTAINED;
    TYPE            FLOAT;
    HANDLING        READ & WRITE;
}

/* string variables */
VARIABLE    v_vis_string32
{
    LABEL           "Variable Visible String [32]";
    CLASS           CONTAINED;
    TYPE            VISIBLE (32);
    HANDLING        READ & WRITE;
}

VARIABLE    v_oct_string32
{
    LABEL           "Variable Octet String [32]";
    CLASS           CONTAINED;
    TYPE            OCTET (32);
    HANDLING        READ & WRITE;
}

/* var defs disabled */
#if 0
VARIABLE    v_euc_string32
{
    LABEL           "Variable EUC String [32]";
    CLASS           CONTAINED;
    TYPE            EUC (32);
    HANDLING        READ & WRITE;
}

VARIABLE    v_ascii_string32
{
    LABEL           "Variable ASCII String [32]";
    CLASS           CONTAINED;
    TYPE            ASCII (32);
    HANDLING        READ & WRITE;
}
#endif

VARIABLE    v_passwd_string32
{
    LABEL           "Variable Password String [32]";
    CLASS           CONTAINED;
    TYPE            PASSWORD (32);
    HANDLING        READ & WRITE;
}

/* bit string variables */
VARIABLE    v_bitstring8
{
    LABEL           "Variable Bit String (8)";
    CLASS           CONTAINED;
    TYPE            BITSTRING (8);
    HANDLING        READ & WRITE;
}

VARIABLE    v_bitstring16
{
    LABEL           "Variable Bit String (16)";
    CLASS           CONTAINED;
    TYPE            BITSTRING (16);
    HANDLING        READ & WRITE;
}

VARIABLE    v_bitstring32
{
    LABEL           "Variable Bit String (32)";
    CLASS           CONTAINED;
    TYPE            BITSTRING (32);
    HANDLING        READ & WRITE;
}

/* bit enumerated variables */
VARIABLE    v_bit_enum8
{
    LABEL           "Variable Bit Enumerated (8)";
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (1)
    {
        _DATATYPESTB_BITENUM8
    }
    HANDLING        READ & WRITE;
}

VARIABLE    v_bit_enum16
{
    LABEL           "Variable Bit Enumerated (16)";
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (2)
    {
        _DATATYPESTB_BITENUM16
    }
    HANDLING        READ & WRITE;
}

VARIABLE    v_bit_enum32
{
    LABEL           "Variable Bit Enumerated (32)";
    CLASS           CONTAINED;
    TYPE            BIT_ENUMERATED (4)
    {
        _DATATYPESTB_BITENUM32
    }
    HANDLING        READ & WRITE;
}

/* date & time variables */
v_date LIKE VARIABLE __test_date
{
    REDEFINE LABEL  "Variable Date";
    REDEFINE HELP   "A sequence of seven (7) octets representing "
                    "the calendar date in both time and date.";
}

v_time LIKE VARIABLE __test_time
{
    REDEFINE LABEL  "Variable Time";
    REDEFINE HELP   "A sequence of six (6) octets representing time "
                    "of day in milliseconds and contained in thirty-two "
                    "(32) bits, with the upper four (4) (i.e. 4 most "
                    "significant bits) bits being set to zero.";
}

v_duration LIKE VARIABLE __test_time_diff
{
    REDEFINE LABEL  "Variable Time Difference";
    REDEFINE HELP   "A sequence of six (6) octets "
                    "representing a time difference.";
}

v_time_value LIKE VARIABLE __test_dll_time
{
    REDEFINE LABEL  "Variable Time Value";
    REDEFINE HELP   "A sequence of eight (8) octets "
                    "representing the time in 1/32s of "
                    "a millisecond. It is contained in a "
                    "sixty-four (64) bit unsigned fixed "
                    "number. Only positive time encoded "
                    "values are supported.";
}

/*
******************************************************************************
** Array Definitions/Redefinitions
******************************************************************************
*/

/* integer/enumerated arrays */
ARRAY       a_bool
{
    LABEL   "Boolean Array [5]";
    TYPE    v_bool;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_int8
{
    LABEL   "Integer8 Array [5]";
    TYPE    v_int8;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_int16
{
    LABEL   "Integer16 Array [5]";
    TYPE    v_int16;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_int32
{
    LABEL   "Integer32 Array [5]";
    TYPE    v_int32;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_uint8
{
    LABEL   "Unsigned Integer8 Array [5]";
    TYPE    v_uint8;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_uint16
{
    LABEL   "Unsigned Integer16 Array [5]";
    TYPE    v_uint16;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_uint32
{
    LABEL   "Unsigned Integer32 Array [5]";
    TYPE    v_uint32;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_enum8
{
    LABEL   "Unsigned8 Enumerated Array [5]";
    TYPE    v_enum8;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_enum16
{
    LABEL   "Unsigned16 Enumerated Array [5]";
    TYPE    v_enum16;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_enum32
{
    LABEL   "Unsigned32 Enumerated Array [5]";
    TYPE    v_enum32;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

/* floating point array */
ARRAY       a_floating_point
{
    LABEL   "Floating Point Array [2]";
    TYPE    v_floating_point;
    NUMBER_OF_ELEMENTS 2;
}

/* string arrays */
ARRAY       a_vis_string32
{
    LABEL   "Visible String [32] Array [2]";
    TYPE    v_vis_string32;
    NUMBER_OF_ELEMENTS 2;
}

ARRAY       a_oct_string32
{
    LABEL   "Octet String [32] Array [2]";
    TYPE    v_oct_string32;
    NUMBER_OF_ELEMENTS 2;
}

/* arr defs disabled */
#if 0
ARRAY       a_euc_string32
{
    LABEL   "EUC String [32] Array [2]";
    TYPE    v_euc_string32;
    NUMBER_OF_ELEMENTS 2;
}

ARRAY       a_ascii_string32
{
    LABEL   "ASCII String [32] Array [2]";
    TYPE    v_ascii_string32;
    NUMBER_OF_ELEMENTS 2;
}
#endif

ARRAY       a_passwd_string32
{
    LABEL   "Password String [32] Array [2]";
    TYPE    v_passwd_string32;
    NUMBER_OF_ELEMENTS 2;
}

/* bit string arrays */
ARRAY       a_bitstring8
{
    LABEL   "Bit String (8) Array [5]";
    TYPE    v_bitstring8;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_bitstring16
{
    LABEL   "Bit String (16) Array [5]";
    TYPE    v_bitstring16;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_bitstring32
{
    LABEL   "Bit String (32) Array [5]";
    TYPE    v_bitstring32;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

/* bit enumerated arrays */
ARRAY       a_bit_enum8
{
    LABEL   "Bit Enumerated (8) Array [5]";
    TYPE    v_bit_enum8;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_bit_enum16
{
    LABEL   "Bit Enumerated (16) Array [5]";
    TYPE    v_bit_enum16;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_bit_enum32
{
    LABEL   "Bit Enumerated (32) Array [5]";
    TYPE    v_bit_enum32;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

/* date & time arrays */
ARRAY       a_date
{
    LABEL   "Date Array [5]";
    TYPE    v_date;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_time
{
    LABEL   "Time Array [5]";
    TYPE    v_time;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_duration
{
    LABEL   "Time Difference Array [5]";
    TYPE    v_duration;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

ARRAY       a_time_value
{
    LABEL   "Time Value Array [5]";
    TYPE    v_time_value;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

/*
******************************************************************************
** Data-Structures Definitions/Redefinitions
******************************************************************************
*/

r_ds65 LIKE RECORD __primary_value_1
{
    REDEFINE LABEL  "DS-65: Value & Status - Float";
    REDEFINE HELP   "This data structure consists of "
                    "the value and status of floating "
                    "point parameters.";
}

r_ds66 LIKE RECORD __pv_d
{
    REDEFINE LABEL  "DS-66: Value & Status - Discrete";
    REDEFINE HELP   "This data structure consists of the "
                    "value and status of discrete value parameters.";
    MEMBERS
    {
        REDEFINE STATUS,    __status_contained;
        REDEFINE VALUE,     __discrete_contained;
    }
}

RECORD  r_ds67
{
    LABEL  "DS-67: Value & Status - Bitstring";
    HELP   "This data structure consists of the "
           "value and status of bit string value parameters.";
    MEMBERS
    {
        STATUS,     __status_contained;
        VALUE,      __bitstring_contained_rw;
    }
}

RECORD  r_ds141
{
    LABEL  "DS-141: Value & Status - Boolean";
    HELP   "This data structure consists of the "
           "value and status of boolean value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string16;
        STATUS,     __status_contained;
        VALUE,      v_bool;
    }
}

RECORD  r_ds142
{
    LABEL  "DS-142: Value & Status - Integer8";
    HELP   "This data structure consists of the "
           "value and status of Integer8 value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string16;
        STATUS,     __status_contained;
        VALUE,      v_int8;
    }
}

RECORD  r_ds143
{
    LABEL  "DS-143: Value & Status - Integer16";
    HELP   "This data structure consists of the "
           "value and status of Integer16 value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string8;
        STATUS,     __status_contained;
        VALUE,      v_int16;
    }
}

RECORD  r_ds144
{
    LABEL  "DS-144: Value & Status - Integer32";
    HELP   "This data structure consists of the "
           "value and status of Integer32 value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_int32;
    }
}

RECORD  r_ds145
{
    LABEL  "DS-145: Value & Status - Unsigned16";
    HELP   "This data structure consists of the value "
           "and status of unsigned16 value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string8;
        STATUS,     __status_contained;
        VALUE,      v_uint16;
    }
}

RECORD  r_ds146
{
    LABEL  "DS-146: Value & Status - Unsigned32";
    HELP   "This data structure consists of the value "
           "and status of unsigned32 value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_uint32;
    }
}

RECORD  r_ds147
{
    LABEL  "DS-147: Value & Status - VisibleString(64)";
    HELP   "This data structure consists of the value and "
           "status of visiblesting(64) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_vis_string64;
    }
}

RECORD  r_ds148
{
    LABEL  "DS-148: Value & Status - VisibleString(128)";
    HELP   "This data structure consists of the value and "
           "status of visiblesting(128) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_vis_string128;
    }
}

/* rec def disabled */
#if 0
RECORD  r_ds149
{
    LABEL  "DS-149: Value & Status - VisibleString(240)";
    HELP   "This data structure consists of the value and "
           "status of visiblesting(240) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_vis_string240;
    }
}
#endif

RECORD  r_ds150
{
    LABEL  "DS-150: Value & Status - OctetString(64)";
    HELP   "This data structure consists of the value "
           "and status of octet sting(64) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_oct_string64;
    }
}

RECORD  r_ds151
{
    LABEL  "DS-151: Value & Status - OctetString(128)";
    HELP   "This data structure consists of the value "
           "and status of octet sting(128) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_oct_string128;
    }
}

/* rec def disabled */
#if 0
RECORD  r_ds152
{
    LABEL  "DS-152: Value & Status - OctetString(240)";
    HELP   "This data structure consists of the value "
           "and status of octet sting(240) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_oct_string240;
    }
}
#endif

RECORD  r_ds153
{
    LABEL  "DS-153: Value & Status - Date";
    HELP   "This data structure consists of the "
           "value and status of date value parameters.";
    MEMBERS
    {
        STATUS,     __status_contained;
        VALUE,      v_date;
    }
}

RECORD  r_ds154
{
    LABEL  "DS-154: Value & Status - Time of Day";
    HELP   "This data structure consists of the value "
           "and status of time of day value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string8;
        STATUS,     __status_contained;
        VALUE,      v_time;
    }
}

RECORD  r_ds155
{
    LABEL  "DS-155: Value & Status - Time Difference";
    HELP   "This data structure consists of the value "
           "and status of time difference value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string8;
        STATUS,     __status_contained;
        VALUE,      v_duration;
    }
}

RECORD  r_ds156
{
    LABEL  "DS-156: Value & Status - Time";
    HELP   "This data structure consists of the "
           "value and status of time value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_time_value;
    }
}

RECORD  r_ds157
{
    LABEL  "DS-157: Value & Status - Bitstring(32)";
    HELP   "This data structure consists of the value "
           "and status of bitstring(32) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_bitstring32;
    }
}

RECORD  r_ds158
{
    LABEL  "DS-158: Value & Status - Bitstring(64)";
    HELP   "This data structure consists of the value "
           "and status of bitstring(64) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE,      v_bitstring64;
    }
}

RECORD  r_ds159
{
    LABEL  "DS-159: Value & Status - Unsigned8(8)";
    HELP   "This data structure consists of the value "
           "and status of unsigned8(8) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_uint8;
        VALUE_2,	v_uint8;
        VALUE_3,	v_uint8;
        VALUE_4,	v_uint8;
        VALUE_5,	v_uint8;
        VALUE_6,	v_uint8;
        VALUE_7,	v_uint8;
        VALUE_8,	v_uint8;
    }
}

RECORD  r_ds160
{
    LABEL  "DS-160: Value & Status - Unsigned8(16)";
    HELP   "This data structure consists of the value "
           "and status of unsigned8(16) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_uint8;
        VALUE_2,	v_uint8;
        VALUE_3,	v_uint8;
        VALUE_4,	v_uint8;
        VALUE_5,	v_uint8;
        VALUE_6,	v_uint8;
        VALUE_7,	v_uint8;
        VALUE_8,	v_uint8;
        VALUE_9,	v_uint8;
        VALUE_10,	v_uint8;
        VALUE_11,	v_uint8;
        VALUE_12,	v_uint8;
        VALUE_13,	v_uint8;
        VALUE_14,	v_uint8;
        VALUE_15,	v_uint8;
        VALUE_16,	v_uint8;
    }
}

RECORD  r_ds161
{
    LABEL  "DS-161: Value & Status - Unsigned8(32)";
    HELP   "This data structure consists of the value "
           "and status of unsigned8(32) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_uint8;
        VALUE_2,	v_uint8;
        VALUE_3,	v_uint8;
        VALUE_4,	v_uint8;
        VALUE_5,	v_uint8;
        VALUE_6,	v_uint8;
        VALUE_7,	v_uint8;
        VALUE_8,	v_uint8;
        VALUE_9,	v_uint8;
        VALUE_10,	v_uint8;
        VALUE_11,	v_uint8;
        VALUE_12,	v_uint8;
        VALUE_13,	v_uint8;
        VALUE_14,	v_uint8;
        VALUE_15,	v_uint8;
        VALUE_16,	v_uint8;
        VALUE_17,	v_uint8;
        VALUE_18,	v_uint8;
        VALUE_19,	v_uint8;
        VALUE_20,	v_uint8;
        VALUE_21,	v_uint8;
        VALUE_22,	v_uint8;
        VALUE_23,	v_uint8;
        VALUE_24,	v_uint8;
        VALUE_25,	v_uint8;
        VALUE_26,	v_uint8;
        VALUE_27,	v_uint8;
        VALUE_28,	v_uint8;
        VALUE_29,	v_uint8;
        VALUE_30,	v_uint8;
        VALUE_31,	v_uint8;
        VALUE_32,	v_uint8;
    }
}

RECORD  r_ds162
{
    LABEL  "DS-162: Value & Status - Float(8)";
    HELP   "This data structure consists of the "
           "value and status of float(8) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_floating_point;
        VALUE_2,	v_floating_point;
        VALUE_3,	v_floating_point;
        VALUE_4,	v_floating_point;
        VALUE_5,	v_floating_point;
        VALUE_6,	v_floating_point;
        VALUE_7,	v_floating_point;
        VALUE_8,	v_floating_point;
    }
}

RECORD  r_ds163
{
    LABEL  "DS-163: Value & Status - Float(16)";
    HELP   "This data structure consists of the "
           "value and status of float(16) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_floating_point;
        VALUE_2,	v_floating_point;
        VALUE_3,	v_floating_point;
        VALUE_4,	v_floating_point;
        VALUE_5,	v_floating_point;
        VALUE_6,	v_floating_point;
        VALUE_7,	v_floating_point;
        VALUE_8,	v_floating_point;
        VALUE_9,	v_floating_point;
        VALUE_10,	v_floating_point;
        VALUE_11,	v_floating_point;
        VALUE_12,	v_floating_point;
        VALUE_13,	v_floating_point;
        VALUE_14,	v_floating_point;
        VALUE_15,	v_floating_point;
        VALUE_16,	v_floating_point;
    }
}

RECORD  r_ds164
{
    LABEL  "DS-164: Value & Status - Float(24)";
    HELP   "This data structure consists of the "
           "value and status of float(24) value parameters.";
    MEMBERS
    {
        RESERVED,   v_oct_string24;
        STATUS,     __status_contained;
        VALUE_1,	v_floating_point;
        VALUE_2,	v_floating_point;
        VALUE_3,	v_floating_point;
        VALUE_4,	v_floating_point;
        VALUE_5,	v_floating_point;
        VALUE_6,	v_floating_point;
        VALUE_7,	v_floating_point;
        VALUE_8,	v_floating_point;
        VALUE_9,	v_floating_point;
        VALUE_10,	v_floating_point;
        VALUE_11,	v_floating_point;
        VALUE_12,	v_floating_point;
        VALUE_13,	v_floating_point;
        VALUE_14,	v_floating_point;
        VALUE_15,	v_floating_point;
        VALUE_16,	v_floating_point;
        VALUE_17,	v_floating_point;
        VALUE_18,	v_floating_point;
        VALUE_19,	v_floating_point;
        VALUE_20,	v_floating_point;
        VALUE_21,	v_floating_point;
        VALUE_22,	v_floating_point;
        VALUE_23,	v_floating_point;
        VALUE_24,	v_floating_point;
    }
}

RECORD  r_ds256
{
    #ifdef DD_REV
    #if _DD5_PROFILE==1
    LABEL  "Latest DDv5 Item";
    #else
    LABEL  "Latest DDv4 Item";
    #endif
    HELP   "TC_DDCF_001 - PASS";
    #else
    LABEL  "DS-256 Label";
    HELP   "DS-256 Help";
    #endif
    MEMBERS
    {
        U8,             v_uint8;
        U16,            v_uint16;
        U32,            v_uint32;
        FLT,            v_float;
        VISIBLESTRING8, v_vis_string8;
    }
}

RECORD  r_ds257
{
    #if _AR2574
    LABEL  _UNICODE_LABEL;
    HELP   _UNICODE_HELP;
    #else
    LABEL  "DS-257 Label";
    HELP   "DS-257 Help";
    #endif
    MEMBERS
    {
        U32_1,  v_uint32;
        U32_2,  v_uint32;
        U32_3,  v_uint32;
        U32_4,  v_uint32;
        U32_5,  v_uint32;
    }
}

/*
******************************************************************************
** no_download and upload_wanted collections (FF-901 4.7.1, 4.7.2)
******************************************************************************
*/

COLLECTION  no_download_datatypestb
{
    MEMBERS
    {
        ND_UNSIGNED32,      PARAM.V_UNSIGNED32;
        ND_UNSIGNED32_ENUM, PARAM.V_UNSIGNED32_ENUM;
    }
}

COLLECTION  upload_wanted_datatypestb
{
    MEMBERS
    {
        UW_UNSIGNED32,      PARAM.V_UNSIGNED32;
        UW_UNSIGNED32_ENUM, PARAM.V_UNSIGNED32_ENUM;
    }
}
    
