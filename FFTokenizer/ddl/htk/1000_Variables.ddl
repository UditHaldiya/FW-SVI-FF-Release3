/*****************************************************************************/
/* 1000_Variables.ddl                                                        */
/*                                                                           */
/*   This DDL file is used for common variable definitions.                  */
/*                                                                           */
/* CRITERIA FOR TEST_CASE_SELECTION                                          */
/*                                                                           */
/*	 None              .                                                     */
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
/* 03-28-07 ! dissabled var defs for vis & oct string240        ! 1.0 ! ms   */
/* 09-24-09 ! ARs 3159, 3570                                    ! 2.0 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Common Variable & Record Definitions
******************************************************************************
*/

/* used for ChannelTB parameter defs */
VARIABLE    analog_function
{
    LABEL   "Function";
    HELP    "This parameter sets the functionality "
            "of the associated block.";
    CLASS   CONTAINED & OPERATE;
    TYPE    ENUMERATED (1)
    {
         {0,     "No Funciton",  "No Funciton Help"},
         {1,     "Ramp",  "Ramp Help"}
    }
    CONSTANT_UNIT   [blank];
    HANDLING        READ & WRITE;
}

VARIABLE    discrete_function
{
    LABEL   "Function";
    HELP    "This parameter sets the functionality "
            "of the associated block.";
    CLASS   CONTAINED & OPERATE;
    TYPE    ENUMERATED (1)
    {
        {0,     "No Funciton",  "No Funciton Help"},
        {1,     "Toggle",  "Toggle Help"},
        {2,     "Ramp",  "Ramp Help"}
    }
    CONSTANT_UNIT   [blank];
    HANDLING        READ & WRITE;
}

/* used for VisuallTB parameter defs */
VARIABLE    test_fl_val
{
    LABEL           "Test Float Value";
    HELP            "A float value used to test EDD visualizations.";
    CLASS           CONTAINED;
    TYPE            FLOAT;
    HANDLING        READ & WRITE;
}

/* LOCAL used for VisuallTB parameter defs */
VARIABLE    test_fl_val_local
{
    LABEL           "Test Float Value Local";
    HELP            "A float value used to test EDD visualizations.";
    CLASS           LOCAL;
    TYPE            FLOAT;
    HANDLING        READ & WRITE;
}

ARRAY       test_array
{
    LABEL   "Test Array";
    HELP    "An array of float values used "
            "to test EDD visualizations.";
    TYPE    test_fl_val;
    NUMBER_OF_ELEMENTS _ARRAY_SIZE;
}

/* used for DataTypesTB data-structure record defs */
VARIABLE    v_vis_string8
{
    LABEL           "Variable Visible String [8]";
    CLASS           CONTAINED;
    TYPE            VISIBLE (8);
    HANDLING        READ & WRITE;
}

VARIABLE    v_vis_string64
{
    LABEL           "Variable Visible String [64]";
    CLASS           CONTAINED;
    TYPE            VISIBLE (64);
    HANDLING        READ & WRITE;
}

VARIABLE    v_vis_string128
{
    LABEL           "Variable Visible String [128]";
    CLASS           CONTAINED;
    TYPE            VISIBLE (128);
    HANDLING        READ & WRITE;
}

/* var def disabled */
#if 0
VARIABLE    v_vis_string240
{
    LABEL           "Variable Visible String [240]";
    CLASS           CONTAINED;
    TYPE            VISIBLE (240);
    HANDLING        READ & WRITE;
}
#endif

VARIABLE    v_oct_string8
{
    LABEL           "Variable Octet String [8]";
    CLASS           CONTAINED;
    TYPE            OCTET (8);
    HANDLING        READ & WRITE;
}

VARIABLE    v_oct_string16
{
    LABEL           "Variable Octet String [16]";
    CLASS           CONTAINED;
    TYPE            OCTET (16);
    HANDLING        READ & WRITE;
}

VARIABLE    v_oct_string24
{
    LABEL           "Variable Octet String [24]";
    CLASS           CONTAINED;
    TYPE            OCTET (24);
    HANDLING        READ & WRITE;
}

VARIABLE    v_oct_string64
{
    LABEL           "Variable Octet String [64]";
    CLASS           CONTAINED;
    TYPE            OCTET (64);
    HANDLING        READ & WRITE;
}

VARIABLE    v_oct_string128
{
    LABEL           "Variable Octet String [128]";
    CLASS           CONTAINED;
    TYPE            OCTET (128);
    HANDLING        READ & WRITE;
}

/* var def disabled */
#if 0
VARIABLE    v_oct_string240
{
    LABEL           "Variable Octet String [240]";
    CLASS           CONTAINED;
    TYPE            OCTET (240);
    HANDLING        READ & WRITE;
}
#endif

VARIABLE    v_bitstring64
{
    LABEL           "Variable Bit String (64)";
    CLASS           CONTAINED;
    TYPE            BITSTRING (64);
    HANDLING        READ & WRITE;
}

VARIABLE    v_float
{
    LABEL           "Variable Floating Point";
    CLASS           CONTAINED;
    TYPE            FLOAT;
    HANDLING        READ & WRITE;
}

/*
******************************************************************************
** Input Construct Definitions for CondTB1/2
******************************************************************************
*/

/* defs & variable re-defs      */
VARIABLE    test_input_var
{
    LABEL           "Test Input Variable";
    CLASS           CONTAINED;
    TYPE            UNSIGNED_INTEGER (1);
    HANDLING        READ & WRITE;
}

/* AR3159 */
VARIABLE     test_input_int
{
    LABEL           "Test Input Integer Variable";
    CLASS           CONTAINED;
    TYPE            INTEGER (1);
    HANDLING        READ & WRITE;
}

test_input_rec LIKE RECORD __final_value
{
    REDEFINE LABEL  "Test Input Record";
    REDEFINE HELP   [blank];
}

ARRAY       test_input_ary_1
{
    LABEL   "Test Input Array 1";
    TYPE    test_input_var;
    NUMBER_OF_ELEMENTS 10;
}

test_input_ary_2 LIKE ARRAY test_input_ary_1
{
    REDEFINE LABEL  "Test Input Array 2";
}

VARIABLE    test_input_enum
{
    LABEL       "Test Input Enumeration";
    HELP        _CONDTB_ENUM_HELP;
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        _CONDTB_TEST_INPUT_ENUM
    }
    HANDLING    READ & WRITE;
}

VARIABLE    test_input_bit_enum
{
    LABEL       "Test Input Bit Enumeration";
    HELP        _CONDTB_ENUM_HELP;
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
        _CONDTB_TEST_INPUT_BIT_ENUM
    }
    HANDLING    READ & WRITE;
}

#if _DD5_PROFILE
LIST    test_input_list
{
    LABEL   "Test Input List";
    HELP    "List used for conditional testing.";
    TYPE    test_input_rec;
}

#if _AR4990 && _DD5_PROFILE
METHOD insert_test_input_list_action
{
    LABEL   "Insert Test Input List Action";
    CLASS   INPUT;
    DEFINITION
    {
        send_on_exit();
        while (test_input_list.COUNT > 0)
        {
            ListDeleteElementAt(ITEM_ID(test_input_list), 1);
        }
        ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
    }
}
#endif
#endif

/* local var definitions */
VARIABLE    local_input_var
{
	LABEL   "Local Input Variable" ;
	CLASS   LOCAL;
	TYPE    UNSIGNED_INTEGER;
}

RECORD      local_input_rec
{
    LABEL   "Local Input Record" ;
    MEMBERS
    {
        INPUT_ELEM_1,   local_input_var;
    }
}

ARRAY   local_input_ary
{
	LABEL 			    "Local Input Array";
	TYPE 			    local_input_var;
	NUMBER_OF_ELEMENTS 	2;
}

/* complex constructs */
COLLECTION  test_input_col
{
    LABEL   "Test Input Collection";
    MEMBERS
    {
        TEST_INPUT_COL_VAR,         test_input_var;
        TEST_INPUT_COL_REC,         test_input_rec;
        TEST_INPUT_COL_ARY_1,       test_input_ary_1;
        TEST_INPUT_COL_ARY_2,       test_input_ary_2;
        TEST_INPUT_COL_ENUM,        test_input_enum;
        TEST_INPUT_COL_BIT_ENUM,    test_input_bit_enum;
    }
}

/* AR3570 - addition of custom-DS parameters to all enhanced I/O FBs */
r_ds256_fb LIKE RECORD r_ds256
{
    REDEFINE LABEL  "DS-256 Label";
    REDEFINE HELP   "DS-256 Help";
}

r_ds257_fb LIKE RECORD r_ds257
{
    REDEFINE LABEL  "DS-257 Label";
    REDEFINE HELP   "DS-257 Help";
}
