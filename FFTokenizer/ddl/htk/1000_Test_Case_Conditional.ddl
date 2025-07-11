/*****************************************************************************/
/* 1000_Test_Case_Conditional.ddl                                            */
/*                                                                           */
/*   This file contains DDL for the conditional test cases.                  */
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
/* 06-06-08 ! Restructured condTb1 menus per AR#2626            ! 1.1 ! dbg  */
/* 01-12-09 ! ARs 3159                                          ! 2.0 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Common constructs for conditional test cases
******************************************************************************
*/

#if _DD5_PROFILE
FILE    condtb1_input_file
{
    LABEL   "Local Record Parameter File";
    HELP    "Persistent storage for TEST_INPUT_REC.VALUE and test_input_list";
    MEMBERS
    {
        FILE_INPUT_REC, LOCAL_PARAM.LOCAL_INPUT_REC;
		TEST_INPUT_LIST, test_input_list;
    }
}

MENU    test_graph_window_condtb1
{
    LABEL   "Test Graph Window";
    STYLE   WINDOW;
    ITEMS   {   test_graph_condtb1  }
}

MENU    test_chart_window_condtb1
{
    LABEL   "Test Chart Window";
    STYLE   WINDOW;
    ITEMS   {   test_chart_condtb1  }
}
#endif    

MENU    test_input_var_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {
                test_input_var
                #ifndef DEVREV1 /* AR3159 */
                ,test_input_int
                #endif
            }
}    

MENU    test_input_rec_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   test_input_rec.VALUE    }
}

MENU    test_input_arr1_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   test_input_ary_1[1]     }
}

MENU    test_input_bit_enum_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   test_input_bit_enum     }
}

MENU    test_input_param_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        test_input_var,
        test_input_rec.VALUE,
        test_input_ary_1[1]
    }   
}

/*
******************************************************************************
** Test Cases for CondTB1
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0010                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences variables when evaluating	     */
/*   conditionals.   							                             */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0010_float_var
{
    LABEL       "COND0010 Float Var";
    HELP        "Verify that host properly dereferences items when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (test_input_var) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_input_var) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_input_var == _MIN_VALUE_1)         {2;}
			ELSE
            {   IF (test_input_var == _MIN_VALUE_2)     {1;}
                ELSE                                    {0;}
            }	       

		MAX_VALUE       
			IF (test_input_var == _MAX_VALUE_1)         {5;}
			ELSE
            {   IF (test_input_var == _MAX_VALUE_2)     {10;}
                ELSE                                    {100;}
            }
    }
    HANDLING 
		IF (test_input_var == _HANDLING_1)              {READ;}
		ELSE								            {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_input_var) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_input_var == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_input_var == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}


VARIABLE        cond0010_enum_var
{
    LABEL       "COND0010 Enum Var";
    HELP        "Verify that host properly dereferences items when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (test_input_var == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0010_bit_enum_var
{
    LABEL       "COND0010 Bit Enum Var";
    HELP        "Verify that host properly dereferences items when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
        #if _AR2259
	    IF (test_input_var == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0011                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences record elements when evaluating	 */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0011_float_var
{
    LABEL       "COND0011 Float Var";
    HELP        "Verify that host properly dereferences record elements "
                "when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _AR2582
    {
        DISPLAY_FORMAT
		    SELECT (test_input_rec.VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_input_rec.VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_input_rec.VALUE == _MIN_VALUE_1)             {2;}
			ELSE
            {   IF (test_input_rec.VALUE == _MIN_VALUE_2)   {1;}
                ELSE                                        {0;}
            }	       

		MAX_VALUE       
			IF (test_input_rec.VALUE == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (test_input_rec.VALUE == _MAX_VALUE_2)   {10;}
                ELSE                                        {100;}
            }
    }
    HANDLING 
		IF (test_input_rec.VALUE == _HANDLING_1)    {READ;}
		ELSE								        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_input_rec.VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_input_rec.VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_input_rec.VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0011_enum_var
{
    LABEL       "COND0011 Enum Var";
    HELP        "Verify that host properly dereferences record elements "
                "when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _AR2582
        IF (test_input_rec.VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0011_bit_enum_var
{
    LABEL       "COND0011 Bit Enum Var";
    HELP        "Verify that host properly dereferences record elements "
                "when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259 && _AR2582
	    IF (test_input_rec.VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}



/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0012                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences arrays when evaluating	         */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0012_float_var
{
    LABEL       "COND0012 Float Var";
    HELP        "Verify that host properly dereferences arrays when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (test_input_ary_1[1]) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_input_ary_1[1]) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_input_ary_1[1] == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (test_input_ary_1[1] == _MIN_VALUE_2)    {1;}
                ELSE                                        {0;}
            }	       

		MAX_VALUE       
			IF (test_input_ary_1[1] == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (test_input_ary_1[1] == _MAX_VALUE_2)    {10;}
                ELSE                                        {100;}
            }
    }
    HANDLING 
		IF (test_input_ary_1[1] == _HANDLING_1)     {READ;}
		ELSE								        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_input_ary_1[1]) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_input_ary_1[1] == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_input_ary_1[1] == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}

VARIABLE        cond0012_enum_var
{
    LABEL       "COND0012 Enum Var";
    HELP        "Verify that host properly dereferences arrays when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (test_input_ary_1[1] == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0012_bit_enum_var
{
    LABEL       "COND0012 Bit Enum Var";
    HELP        "Verify that host properly dereferences arrays when "
                "evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (test_input_ary_1[1] == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0013                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences collection members when          */
/*   evaluating conditionals.												 */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0013_float_var
{
    LABEL       "COND0013 Float Var";
    HELP        "Verify that host properly dereferences collection "
                "members when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _AR2273 && _AR2582
    {
        DISPLAY_FORMAT
		    SELECT (test_input_col.TEST_INPUT_COL_REC.VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_input_col.TEST_INPUT_COL_REC.VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _MIN_VALUE_2)    {1;}
                ELSE                                                        {0;}
            }	       

		MAX_VALUE       
			IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _MAX_VALUE_2)    {10;}
                ELSE                                                        {100;}
            }
    }
    HANDLING 
		IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _HANDLING_1)     {READ;}
		ELSE								                        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_input_col.TEST_INPUT_COL_REC.VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0013_enum_var
{
    LABEL       "COND0013 Enum Var";
    HELP        "Verify that host properly dereferences collection "
                "members when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _AR2273 && _AR2582
        IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0013_bit_enum_var
{
    LABEL       "COND0013 Bit Enum Var";
    HELP        "Verify that host properly dereferences collection "
                "members when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259 && _AR2273 && _AR2582
	    IF (test_input_col.TEST_INPUT_COL_REC.VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/****************************************/

VARIABLE        cond0014_float_var
{
    LABEL       "COND0014 Float Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}

VARIABLE        cond0014_enum_var
{
    LABEL       "COND0014 Enum Var";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        _CONDTB_ZERO_ENUM
    }
}

VARIABLE        cond0014_bit_enum_var
{
    LABEL       "COND0014 Bit Enum Var";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    _CONDTB_ZERO_BIT_ENUM
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0015                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences variable lists when evaluating	 */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0015_float_var
{
    LABEL       "COND0015 Float Var";
    HELP        "Verify that host properly dereferences variable "
                "lists when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _AR2316 && _AR2582
    {
        DISPLAY_FORMAT
		    SELECT (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _MIN_VALUE_1)         {2;}
			ELSE
            {   IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _MIN_VALUE_2)     {1;}
                ELSE                                                            {0;}
            }	       

		MAX_VALUE       
			IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _MAX_VALUE_1)         {5;}
			ELSE
            {   IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _MAX_VALUE_2)     {10;}
                ELSE                                                            {100;}
            }
    }
    HANDLING 
		IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _HANDLING_1)      {READ;}
		ELSE								                            {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0015_enum_var
{
    LABEL       "COND0015 Enum Var";
    HELP        "Verify that host properly dereferences variable "
                "lists when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _AR2316 && _AR2582
        IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0015_bit_enum_var
{
    LABEL       "COND0015 Bit Enum Var";
    HELP        "Verify that host properly dereferences variable "
                "lists when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259 && _AR2316 && _AR2582
	    IF (cond1tb_view_4.VL_TEST_INPUT_REC.VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0016                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences file members when evaluating     */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0016_float_var
{
    LABEL       "COND0016 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences file members "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2318
    {
        DISPLAY_FORMAT
		    SELECT (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _MIN_VALUE_2)    {1;}
                ELSE                                                                    {0;}
            }	       

		MAX_VALUE       
			IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _MAX_VALUE_2)    {10;}
                ELSE                                                                    {100;}
            }
    }
    HANDLING 
		IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _HANDLING_1)     {READ;}
		ELSE								                                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0016_enum_var
{
    LABEL       "COND0016 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences file members "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2318
        IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0016_bit_enum_var
{
    LABEL       "COND0016 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences file members "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2318
	    IF (condtb1_input_file.FILE_INPUT_REC.INPUT_ELEM_1 == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0017                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences list elements when evaluating    */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0017_float_var
{
    LABEL       "COND0017 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences list elements "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2319
    {
        DISPLAY_FORMAT
		    SELECT (test_input_list[1].VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_input_list[1].VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_input_list[1].VALUE == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (test_input_list[1].VALUE == _MIN_VALUE_2)   {1;}
                ELSE                                            {0;}
            }	       

		MAX_VALUE       
			IF (test_input_list[1].VALUE == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (test_input_list[1].VALUE == _MAX_VALUE_2)   {10;}
                ELSE                                            {100;}
            }
    }
    HANDLING 
		IF (test_input_list[1].VALUE == _HANDLING_1)        {READ;}
		ELSE								                {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_input_list[1].VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_input_list[1].VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_input_list[1].VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0017_enum_var
{
    LABEL       "COND0017 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences list elements "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2319
        IF (test_input_list[1].VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0017_bit_enum_var
{
    LABEL       "COND0017 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences list elements "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2319
	    IF (test_input_list[1].VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0018A                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences Axis VIEW_MIN when evaluating    */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0018a_float_var
{
    LABEL       "COND0018A Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis VIEW_MIN "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2333
    {
        DISPLAY_FORMAT
		    SELECT (test_x_axis_condtb1.VIEW_MIN) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_x_axis_condtb1.VIEW_MIN) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_x_axis_condtb1.VIEW_MIN == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (test_x_axis_condtb1.VIEW_MIN == _MIN_VALUE_2)   {1;}
                ELSE                                                {0;}
            }	       

		MAX_VALUE       
			IF (test_x_axis_condtb1.VIEW_MIN == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (test_x_axis_condtb1.VIEW_MIN == _MAX_VALUE_2)   {10;}
                ELSE                                                {100;}
            }
    }
    HANDLING 
		IF (test_x_axis_condtb1.VIEW_MIN == _HANDLING_1)        {READ;}
		ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_x_axis_condtb1.VIEW_MIN) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_x_axis_condtb1.VIEW_MIN == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_x_axis_condtb1.VIEW_MIN == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0018a_enum_var
{
    LABEL       "COND0018A Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis reference "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2333
        IF (test_x_axis_condtb1.VIEW_MIN == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0018a_bit_enum_var
{
    LABEL       "COND0018A Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis reference "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2333
	    IF (test_x_axis_condtb1.VIEW_MIN == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0018B                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences Axis VIEW_MAX when evaluating    */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/
 VARIABLE        cond0018b_float_var
{
    LABEL       "COND0018B Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis VIEW_MAX "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2333
    {
        DISPLAY_FORMAT
		    SELECT (test_x_axis_condtb1.VIEW_MAX) 
 		    {
			    CASE _DISPLAY_FORMAT_1+10:  "5.2f";

                CASE _DISPLAY_FORMAT_2+10:  "5.4f";
                    
                DEFAULT:                    "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_x_axis_condtb1.VIEW_MAX) 
 		    {
			    CASE _EDIT_FORMAT_1+10:     "5.2f";

                CASE _EDIT_FORMAT_2+10:     "5.4f";
                    
                DEFAULT:                    "3.3f";
            } 						    

        MIN_VALUE
			IF (test_x_axis_condtb1.VIEW_MAX == _MIN_VALUE_1+10)        {2;}
			ELSE
            {   IF (test_x_axis_condtb1.VIEW_MAX == _MIN_VALUE_2+10)    {1;}
                ELSE                                                    {0;}
            }	       

		MAX_VALUE       
			IF (test_x_axis_condtb1.VIEW_MAX == _MAX_VALUE_1+10)        {5;}
			ELSE
            {   IF (test_x_axis_condtb1.VIEW_MAX == _MAX_VALUE_2+10)    {10;}
                ELSE                                                    {100;}
            }
    }
    HANDLING 
		IF (test_x_axis_condtb1.VIEW_MAX == _HANDLING_1+10)     {READ;}
        ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_x_axis_condtb1.VIEW_MAX) 
 		{
			CASE _CONSTANT_UNIT_1+10:   [unit_code_1056];

            CASE _CONSTANT_UNIT_2+10:   [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_x_axis_condtb1.VIEW_MAX == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_x_axis_condtb1.VIEW_MAX == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0018b_enum_var
{
    LABEL       "COND0018B Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis reference "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2333
        IF (test_x_axis_condtb1.VIEW_MAX == _ENUMERATED_1+10)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0018b_bit_enum_var
{
    LABEL       "COND0018B Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences Axis reference "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2333
	    IF (test_x_axis_condtb1.VIEW_MAX == _BIT_ENUMERATED_1+10)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0019                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences chart member when evaluating     */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0019_float_var
{
    LABEL       "COND0019 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences chart member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2334
    {
        DISPLAY_FORMAT
		    SELECT (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _MIN_VALUE_1)     {2;}
			ELSE
            {   IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _MIN_VALUE_2) {1;}
                ELSE                                                                {0;}
            }	       

		MAX_VALUE       
			IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _MAX_VALUE_1)     {5;}
			ELSE
            {   IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _MAX_VALUE_2) {10;}
                ELSE                                                                {100;}
            }
    }
    HANDLING 
		IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _HANDLING_1)  {READ;}
		ELSE								                                {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0019_enum_var
{
    LABEL       "COND0019 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences chart member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2334
        IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0019_bit_enum_var
{
    LABEL       "COND0019 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences chart member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2334
	    IF (test_chart_condtb1.TEST_SOURCE.TEST_SRC_IN_VAR == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0020                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences graph member when evaluating     */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0020_float_var
{
    LABEL       "COND0020 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences graph member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2339
    {
        DISPLAY_FORMAT
		    SELECT (test_graph_condtb1.TEST_WAVEFORM) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_graph_condtb1.TEST_WAVEFORM) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_graph_condtb1.TEST_WAVEFORM == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (test_graph_condtb1.TEST_WAVEFORM == _MIN_VALUE_2)   {1;}
                ELSE                                                    {0;}
            }	       

		MAX_VALUE       
			IF (test_graph_condtb1.TEST_WAVEFORM == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (test_graph_condtb1.TEST_WAVEFORM == _MAX_VALUE_2)   {10;}
                ELSE                                                    {100;}
            }
    }
    HANDLING 
		IF (test_graph_condtb1.TEST_WAVEFORM == _HANDLING_1)    {READ;}
		ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_graph_condtb1.TEST_WAVEFORM) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_graph_condtb1.TEST_WAVEFORM == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_graph_condtb1.TEST_WAVEFORM == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0020_enum_var
{
    LABEL       "COND0020 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences graph member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2339
        IF (test_graph_condtb1.TEST_WAVEFORM == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0020_bit_enum_var
{
    LABEL       "COND0020 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences graph member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2339
	    IF (test_graph_condtb1.TEST_WAVEFORM == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0021                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences source member when evaluating    */
/*   conditionals.   														 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0021_float_var
{
    LABEL       "COND0021 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2340
    {
        DISPLAY_FORMAT
		    SELECT (test_source_condtb1.TEST_SRC_IN_VAR) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_source_condtb1.TEST_SRC_IN_VAR) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (test_source_condtb1.TEST_SRC_IN_VAR == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (test_source_condtb1.TEST_SRC_IN_VAR == _MIN_VALUE_2)    {1;}
                ELSE                                                        {0;}
            }	       

		MAX_VALUE       
			IF (test_source_condtb1.TEST_SRC_IN_VAR == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (test_source_condtb1.TEST_SRC_IN_VAR == _MAX_VALUE_2)    {10;}
                ELSE                                                        {100;}
            }
    }
    HANDLING 
		IF (test_source_condtb1.TEST_SRC_IN_VAR == _HANDLING_1)     {READ;}
		ELSE								                        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_source_condtb1.TEST_SRC_IN_VAR) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (test_source_condtb1.TEST_SRC_IN_VAR == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (test_source_condtb1.TEST_SRC_IN_VAR == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0021_enum_var
{
    LABEL       "COND0021 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2340
        IF (test_source_condtb1.TEST_SRC_IN_VAR == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0021_bit_enum_var
{
    LABEL       "COND0021 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source member "
                "when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2340
	    IF (test_source_condtb1.TEST_SRC_IN_VAR == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/****************************************/
 
VARIABLE        cond0022_float_var
{
    LABEL       "COND0022 Float Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}

VARIABLE        cond0022_enum_var
{
    LABEL       "COND0022 Enum Var";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        _CONDTB_ZERO_ENUM
    }
}

VARIABLE        cond0022_bit_enum_var
{
    LABEL       "COND0022 Bit Enum Var";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    _CONDTB_ZERO_BIT_ENUM
    }
}

/****************************************/
 
VARIABLE        cond0023_float_var
{
    LABEL       "COND0023 Float Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}

VARIABLE        cond0023_enum_var
{
    LABEL       "COND0023 Enum Var";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        _CONDTB_ZERO_ENUM
    }
}

VARIABLE        cond0023_bit_enum_var
{
    LABEL       "COND0023 Bit Enum Var";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    _CONDTB_ZERO_BIT_ENUM
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0024                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences source line color when           */
/*   evaluating conditionals.        										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0024_float_var
{
    LABEL       "COND0024 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source line "
                "color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2342
    {
        DISPLAY_FORMAT
		    SELECT (test_source_condtb1.LINE_COLOR) 
 		    {
			    CASE _RGB_WHITE:    "5.2f";

                CASE _RGB_GREY:     "5.4f";
                    
                DEFAULT:            "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_source_condtb1.LINE_COLOR) 
 		    {
			    CASE _RGB_BLUE:     "5.2f";

                CASE _RGB_CYAN:     "5.4f";
                    
                DEFAULT:            "3.3f";
            } 						    

        MIN_VALUE
			IF (test_source_condtb1.LINE_COLOR == _RGB_GREEN)       {2;}
			ELSE
            {   IF (test_source_condtb1.LINE_COLOR == _RGB_YELLOW)  {1;}
                ELSE                                                {0;}
            }	       

		MAX_VALUE       
			IF (test_source_condtb1.LINE_COLOR == _RGB_BROWN)       {5;}
			ELSE
            {   IF (test_source_condtb1.LINE_COLOR == _RGB_ORANGE)  {10;}
                ELSE                                                {100;}
            }
    }
    HANDLING 
		IF (test_source_condtb1.LINE_COLOR == _RGB_NAVY)    {READ;}
		ELSE								                {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_source_condtb1.LINE_COLOR) 
 		{
			CASE _RGB_PURPLE:       [unit_code_1056];

            CASE _RGB_AZURE:        [unit_code_1054];
                    
            DEFAULT:                [blank];
        }

	VALIDITY
		IF (test_source_condtb1.LINE_COLOR == _RGB_KHAKI) { TRUE; }
		ELSE
		{
			IF (test_source_condtb1.LINE_COLOR == _RGB_GOLD) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0024_enum_var
{
    LABEL       "COND0024 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source line "
                "color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2342
        IF (test_source_condtb1.LINE_COLOR == _RGB_RED)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0024_bit_enum_var
{
    LABEL       "COND0024 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences source line "
                "color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2342
	    IF (test_source_condtb1.LINE_COLOR == _RGB_MAROON)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/****************************************/
 
VARIABLE        cond0025_float_var
{
    LABEL       "COND0025 Float Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}

VARIABLE        cond0025_enum_var
{
    LABEL       "COND0025 Enum Var";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        _CONDTB_ZERO_ENUM
    }
}

VARIABLE        cond0025_bit_enum_var
{
    LABEL       "COND0025 Bit Enum Var";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    _CONDTB_ZERO_BIT_ENUM
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0026                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences waveform line color when	     */
/*   evaluating conditionals.   											 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0026_float_var
{
    LABEL       "COND0026 Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences waveform "
                "line color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2343
    {
        DISPLAY_FORMAT
		    SELECT (test_waveform_condtb1.LINE_COLOR) 
 		    {
			    CASE _RGB_WHITE:    "5.2f";

                CASE _RGB_GREY:     "5.4f";
                    
                DEFAULT:            "3.3f";
            }

        EDIT_FORMAT  
			SELECT (test_waveform_condtb1.LINE_COLOR) 
 		    {
			    CASE _RGB_BLUE:     "5.2f";

                CASE _RGB_CYAN:     "5.4f";
                    
                DEFAULT:            "3.3f";
            } 						    

        MIN_VALUE
			IF (test_waveform_condtb1.LINE_COLOR == _RGB_GREEN)         {2;}
			ELSE
            {   IF (test_waveform_condtb1.LINE_COLOR == _RGB_YELLOW)    {1;}
                ELSE                                                    {0;}
            }	       

		MAX_VALUE       
			IF (test_waveform_condtb1.LINE_COLOR == _RGB_BROWN)         {5;}
			ELSE
            {   IF (test_waveform_condtb1.LINE_COLOR == _RGB_ORANGE)    {10;}
                ELSE                                                    {100;}
            }
    }
    HANDLING 
		IF (test_waveform_condtb1.LINE_COLOR == _RGB_NAVY)      {READ;}
		ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (test_waveform_condtb1.LINE_COLOR) 
 		{
			CASE _RGB_PURPLE:       [unit_code_1056];

            CASE _RGB_AZURE:        [unit_code_1054];
                    
            DEFAULT:                [blank];
        }

	VALIDITY
		IF (test_waveform_condtb1.LINE_COLOR == _RGB_KHAKI) { TRUE; }
		ELSE
		{
			IF (test_waveform_condtb1.LINE_COLOR == _RGB_GOLD) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0026_enum_var
{
    LABEL       "COND0026 Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences waveform "
                "line color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2343
        IF (test_waveform_condtb1.LINE_COLOR == _RGB_RED)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0026_bit_enum_var
{
    LABEL       "COND0026 Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences waveform "
                "line color when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2343
	    IF (test_waveform_condtb1.LINE_COLOR == _RGB_MAROON)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0027                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences enumerated bits when			 */
/*   evaluating conditionals.   											 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0027a_float_var
{
    LABEL       "COND0027A Float Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE
    {
        DISPLAY_FORMAT
            IF (test_input_bit_enum[_DISPLAY_FORMAT_1_BIT]) {"5.2f";}
		    ELSE								            {"5.4f";}

		EDIT_FORMAT
            IF (test_input_bit_enum[_EDIT_FORMAT_1_BIT])    {"5.2f";}
		    ELSE								            {"5.4f";}  					    

        MIN_VALUE
			IF (test_input_bit_enum[_MIN_VALUE_1_BIT])      {2;}
			ELSE                                            {1;}

        MAX_VALUE       
			IF (test_input_bit_enum[_MAX_VALUE_1_BIT])      {5;}
			ELSE                                            {10;}
    }

    HANDLING 
		IF (test_input_bit_enum[_HANDLING_1_BIT])           {READ;}
		ELSE								                {READ & WRITE;}

    CONSTANT_UNIT
        IF (test_input_bit_enum[_CONSTANT_UNIT_1_BIT])      {[unit_code_1056];}
		ELSE								                {[unit_code_1054];}
        
	VALIDITY
		IF (test_input_bit_enum[_VALIDITY_1_BIT]) { TRUE; }
		ELSE
		{
			IF (test_input_bit_enum[_VALIDITY_2_BIT]) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0027a_enum_var
{
    LABEL       "COND0027A Enum Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE
        IF (test_input_bit_enum[_ENUMERATED_1_BIT])			
		{   _TEST_ENUM1     }
		ELSE
        {   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }        
}

VARIABLE        cond0027a_bit_enum_var
{
    LABEL       "COND0027A Bit Enum Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259 && _DD5_PROFILE
	    IF (test_input_bit_enum[_BIT_ENUMERATED_1_BIT])			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}
/****************************************/
 
VARIABLE        cond0027b_float_var
{
    LABEL       "COND0027B Float Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE
    {
        DISPLAY_FORMAT
            IF (test_input_bit_enum[_DISPLAY_FORMAT_2_BIT]) {"5.4f";}
		    ELSE								            {"5.2f";}

		EDIT_FORMAT
            IF (test_input_bit_enum[_EDIT_FORMAT_2_BIT])    {"5.4f";}
		    ELSE								            {"5.2f";}  					    

        MIN_VALUE
			IF (test_input_bit_enum[_MIN_VALUE_2_BIT])      {1;}
			ELSE                                            {2;}

        MAX_VALUE       
			IF (test_input_bit_enum[_MAX_VALUE_2_BIT])      {10;}
			ELSE                                            {5;}
    }

    HANDLING 
		IF (test_input_bit_enum[_HANDLING_2_BIT])           {READ & WRITE;}
		ELSE
        {
            IF (test_input_bit_enum[_HANDLING_1_BIT])       {READ;}
            ELSE                                            {READ & WRITE;}
        }  

    CONSTANT_UNIT
        IF (test_input_bit_enum[_CONSTANT_UNIT_2_BIT])      {[unit_code_1054];}
		ELSE								                {[unit_code_1056];}
        
	VALIDITY
		IF (test_input_bit_enum[_VALIDITY_1_BIT]) { TRUE; }
		ELSE
		{
			IF (test_input_bit_enum[_VALIDITY_2_BIT]) { FALSE; }
			ELSE { TRUE;  }
		}
        #else
        ;
        #endif
}

VARIABLE        cond0027b_enum_var
{
    LABEL       "COND0027B Enum Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE
        IF (test_input_bit_enum[_ENUMERATED_2_BIT])			
		{   _TEST_ENUM2     }
		ELSE								
		{   _TEST_ENUM1     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}

VARIABLE        cond0027b_bit_enum_var
{
    LABEL       "COND0027B Bit Enum Var";
    HELP        "Verify that host properly dereferences enumerated "
                "bits when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259  && _DD5_PROFILE
	    IF (test_input_bit_enum[_BIT_ENUMERATED_2_BIT])			
		{   _TEST_BIT_ENUM2     }
		ELSE								
		{   _TEST_BIT_ENUM1     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0028A                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameters (variable)      */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0028a_float_var
{
    LABEL       "COND0028A Float Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (PARAM.TEST_INPUT_VAR) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM.TEST_INPUT_VAR) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM.TEST_INPUT_VAR == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (PARAM.TEST_INPUT_VAR == _MIN_VALUE_2)   {1;}
                ELSE                                        {0;}
            }	       

		MAX_VALUE       
			IF (PARAM.TEST_INPUT_VAR == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (PARAM.TEST_INPUT_VAR == _MAX_VALUE_2)   {10;}
                ELSE                                        {100;}
            }
    }
    HANDLING 
		IF (PARAM.TEST_INPUT_VAR == _HANDLING_1)            {READ;}
		ELSE								                {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM.TEST_INPUT_VAR) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM.TEST_INPUT_VAR == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM.TEST_INPUT_VAR == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}

VARIABLE        cond0028a_enum_var
{
    LABEL       "COND0028A Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (PARAM.TEST_INPUT_VAR == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0028a_bit_enum_var
{
    LABEL       "COND0028A Bit Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (PARAM.TEST_INPUT_VAR == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0028B                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameters (record)        */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0028b_float_var
{
    LABEL       "COND0028B Float Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _AR2582
    {
        DISPLAY_FORMAT
		    SELECT (PARAM.TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM.TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM.TEST_INPUT_REC.VALUE == _MIN_VALUE_1)     {2;}
			ELSE
            {   IF (PARAM.TEST_INPUT_REC.VALUE == _MIN_VALUE_2) {1;}
                ELSE                                            {0;}
            }	       

		MAX_VALUE       
			IF (PARAM.TEST_INPUT_REC.VALUE == _MAX_VALUE_1)     {5;}
			ELSE
            {   IF (PARAM.TEST_INPUT_REC.VALUE == _MAX_VALUE_2) {10;}
                ELSE                                            {100;}
            }
    }
    HANDLING 
		IF (PARAM.TEST_INPUT_REC.VALUE == _HANDLING_1)          {READ;}
		ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM.TEST_INPUT_REC.VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM.TEST_INPUT_REC.VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM.TEST_INPUT_REC.VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0028b_enum_var
{
    LABEL       "COND0028B Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _AR2582
        IF (PARAM.TEST_INPUT_REC.VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0028b_bit_enum_var
{
    LABEL       "COND0028B Bit Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259 && _AR2582
	    IF (PARAM.TEST_INPUT_REC.VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0028C                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameters (array)         */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0028c_float_var
{
    LABEL       "COND0028C Float Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (PARAM.TEST_INPUT_ARY_1[1]) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM.TEST_INPUT_ARY_1[1]) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM.TEST_INPUT_ARY_1[1] == _MIN_VALUE_1)      {2;}
			ELSE
            {   IF (PARAM.TEST_INPUT_ARY_1[1] == _MIN_VALUE_2)  {1;}
                ELSE                                            {0;}
            }	       

		MAX_VALUE       
			IF (PARAM.TEST_INPUT_ARY_1[1] == _MAX_VALUE_1)      {5;}
			ELSE
            {   IF (PARAM.TEST_INPUT_ARY_1[1] == _MAX_VALUE_2)  {10;}
                ELSE                                            {100;}
            }
    }
    HANDLING 
		IF (PARAM.TEST_INPUT_ARY_1[1] == _HANDLING_1)           {READ;}
		ELSE								                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM.TEST_INPUT_ARY_1[1]) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM.TEST_INPUT_ARY_1[1] == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM.TEST_INPUT_ARY_1[1] == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}

VARIABLE        cond0028c_enum_var
{
    LABEL       "COND0028C Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (PARAM.TEST_INPUT_ARY_1[1] == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0028c_bit_enum_var
{
    LABEL       "COND0028C Bit Enum Var";
    HELP        "Verify that host properly dereferences block "
                "parameters (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (PARAM.TEST_INPUT_ARY_1[1] == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0029A                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences local block parameters           */
/*   (variable) when evaluating conditionals.   							 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0029a_float_var
{
    LABEL       "COND0029A Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (variable) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2344
    {
        DISPLAY_FORMAT
		    SELECT (LOCAL_PARAM.LOCAL_INPUT_VAR) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (LOCAL_PARAM.LOCAL_INPUT_VAR) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _MIN_VALUE_2)    {1;}
                ELSE                                                {0;}
            }	       

		MAX_VALUE       
			IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _MAX_VALUE_2)    {10;}
                ELSE                                                {100;}
            }
    }
    HANDLING 
		IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _HANDLING_1)             {READ;}
		ELSE								                        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (LOCAL_PARAM.LOCAL_INPUT_VAR) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0029a_enum_var
{
    LABEL       "COND0029A Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (variable) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2344
        IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0029a_bit_enum_var
{
    LABEL       "COND0029A Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (variable) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2344
	    IF (LOCAL_PARAM.LOCAL_INPUT_VAR == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0029B                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences local block parameters           */
/*   (record) when evaluating conditionals.   							     */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0029b_float_var
{
    LABEL       "COND0029B Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (record) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2344
    {
        DISPLAY_FORMAT
		    SELECT (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _MIN_VALUE_2)   {1;}
                ELSE                                                            {0;}
            }	       

		MAX_VALUE       
			IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _MAX_VALUE_2)   {10;}
                ELSE                                                            {100;}
            }
    }
    HANDLING 
		IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _HANDLING_1)            {READ;}
		ELSE								                                    {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0029b_enum_var
{
    LABEL       "COND0029B Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (record) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2344
        IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0029b_bit_enum_var
{
    LABEL       "COND0029B Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (record) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2344
	    IF (LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1 == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0029C                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences local block parameters           */
/*   (array) when evaluating conditionals.   							     */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0029c_float_var
{
    LABEL       "COND0029C Float Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (array) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _DD5_PROFILE && _AR2344
    {
        DISPLAY_FORMAT
		    SELECT (LOCAL_PARAM.LOCAL_INPUT_ARY[1]) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (LOCAL_PARAM.LOCAL_INPUT_ARY[1]) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _MIN_VALUE_1)     {2;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _MIN_VALUE_2) {1;}
                ELSE                                                {0;}
            }	       

		MAX_VALUE       
			IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _MAX_VALUE_1)     {5;}
			ELSE
            {   IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _MAX_VALUE_2) {10;}
                ELSE                                                {100;}
            }
    }
    HANDLING 
		IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _HANDLING_1)          {READ;}
		ELSE								                        {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (LOCAL_PARAM.LOCAL_INPUT_ARY[1]) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0029c_enum_var
{
    LABEL       "COND0029C Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (array) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _DD5_PROFILE && _AR2344
        IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0029c_bit_enum_var
{
    LABEL       "COND0029C Bit Enum Var";
    #if _DD5_PROFILE
    HELP        "Verify that host properly dereferences local block "
                "parameters (array) when evaluating conditionals.";
    #endif
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _DD5_PROFILE && _AR2259 && _AR2344
	    IF (LOCAL_PARAM.LOCAL_INPUT_ARY[1] == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0030A                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameter lists (variable) */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0030a_float_var
{
    LABEL       "COND0030A Float Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _MIN_VALUE_1)        {2;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _MIN_VALUE_2)    {1;}
                ELSE                                                        {0;}
            }	       

		MAX_VALUE       
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _MAX_VALUE_1)        {5;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _MAX_VALUE_2)    {10;}
                ELSE                                                        {100;}
            }
    }
    HANDLING 
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _HANDLING_1)         {READ;}
		ELSE								                            {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}

VARIABLE        cond0030a_enum_var
{
    LABEL       "COND0030A Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0030a_bit_enum_var
{
    LABEL       "COND0030A Bit Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (variable) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_VAR == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0030B                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameter lists (record)   */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0030b_float_var
{
    LABEL       "COND0030B Float Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    #if _AR2582
    {
        DISPLAY_FORMAT
		    SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _MIN_VALUE_1)      {2;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _MIN_VALUE_2)  {1;}
                ELSE                                                            {0;}
            }	       

		MAX_VALUE       
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _MAX_VALUE_1)      {5;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _MAX_VALUE_2)  {10;}
                ELSE                                                            {100;}
            }
    }
    HANDLING 
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _HANDLING_1)       {READ;}
		ELSE								                                {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
    #else
    ;
    #endif
}

VARIABLE        cond0030b_enum_var
{
    LABEL       "COND0030B Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        #if _AR2582
        IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
        #else
            _CONDTB_ZERO_ENUM
        #endif
    }
}

VARIABLE        cond0030b_bit_enum_var
{
    LABEL       "COND0030B Bit Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (record) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_REC.VALUE == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0030C                                                           */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block parameter lists (array)    */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0030c_float_var
{
    LABEL       "COND0030C Float Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1]) 
 		    {
			    CASE _DISPLAY_FORMAT_1: "5.2f";

                CASE _DISPLAY_FORMAT_2: "5.4f";
                    
                DEFAULT:                "3.3f";
            }

        EDIT_FORMAT  
			SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1]) 
 		    {
			    CASE _EDIT_FORMAT_1:    "5.2f";

                CASE _EDIT_FORMAT_2:    "5.4f";
                    
                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _MIN_VALUE_1)       {2;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _MIN_VALUE_2)   {1;}
                ELSE                                                            {0;}
            }	       

		MAX_VALUE       
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _MAX_VALUE_1)       {5;}
			ELSE
            {   IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _MAX_VALUE_2)   {10;}
                ELSE                                                            {100;}
            }
    }
    HANDLING 
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _HANDLING_1)    {READ;}
		ELSE								                            {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1]) 
 		{
			CASE _CONSTANT_UNIT_1:      [unit_code_1056];

            CASE _CONSTANT_UNIT_2:      [unit_code_1054];
                    
            DEFAULT:                    [blank];
        }

	VALIDITY
		IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _VALIDITY_1) { TRUE; }
		ELSE
		{
			IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _VALIDITY_2) { FALSE; }
			ELSE { TRUE;  }
		}
}

VARIABLE        cond0030c_enum_var
{
    LABEL       "COND0030C Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _ENUMERATED_1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0030c_bit_enum_var
{
    LABEL       "COND0030C Bit Enum Var";
    HELP        "Verify that host properly dereferences block parameter "
                "lists (array) when evaluating conditionals.";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
	    #if _AR2259
	    IF (PARAM_LIST.VIEW_4.VL_TEST_INPUT_ARY_1[1] == _BIT_ENUMERATED_1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
        #else
            _CONDTB_ZERO_BIT_ENUM
        #endif
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0031                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Referencing data in conditionals										 */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly dereferences block characteristics            */
/*   when evaluating conditionals.   										 */
/*                                                                           */
/*****************************************************************************/ 
VARIABLE        cond0031_float_var
{
    LABEL       "COND0031 Float Var";
    CLASS       CONTAINED;
    TYPE        FLOAT
    {
        DISPLAY_FORMAT
		    SELECT (BLOCK.NUM_OF_PARAMS) 
 		    {
			    CASE _NUM_OF_PARAMS_CONDTB1: "5.2f";

                DEFAULT:                "3.3f";
            }

        #if !_AR5487
        EDIT_FORMAT  
		    SELECT (BLOCK.NUM_OF_PARAMS) 
 		    {
			    CASE _NUM_OF_PARAMS_CONDTB1: "5.2f";

                DEFAULT:                "3.3f";
            } 						    

        MIN_VALUE
			IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)       {2;}
			ELSE                                                     {0;}

		MAX_VALUE       
			IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)       {5;}
			ELSE
                                                                     {0;}
        #endif
    }
    HANDLING 
			IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)       {READ;}
			ELSE                                                     {READ & WRITE;}

    CONSTANT_UNIT
		SELECT (BLOCK.NUM_OF_PARAMS) 
 		{
			CASE _NUM_OF_PARAMS_CONDTB1:      [unit_code_1056];
                   
            DEFAULT:                    [blank];
        }

	VALIDITY
			IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)       {TRUE;}
			ELSE                                                     {FALSE;}
}

VARIABLE        cond0031_enum_var
{
    LABEL       "COND0031 Enum Var";
    CLASS       CONTAINED;
    TYPE        ENUMERATED (2)
    {
        IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)			
		{   _TEST_ENUM1     }
		ELSE								
		{   _TEST_ENUM2     }
    }
}

VARIABLE        cond0031_bit_enum_var
{
    LABEL       "COND0031 Bit Enum Var";
    CLASS       CONTAINED;
    TYPE        BIT_ENUMERATED (4)
    {
        IF (BLOCK.NUM_OF_PARAMS == _NUM_OF_PARAMS_CONDTB1)			
		{   _TEST_BIT_ENUM1     }
		ELSE								
		{   _TEST_BIT_ENUM2     }
    }
}



/*
******************************************************************************
** Test Cases for CondTB2
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0050                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates constant expressions.               */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0050_var
{
    LABEL       "COND0050 Var";
    HELP        "Verify that host properly evaluates constant expressions.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var)     {READ;}
		ELSE					{READ & WRITE;}    
}

MENU    cond0050_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0050_var    }
}    

MENU    cond0050_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0050_page
{
    LABEL   "COND_0050";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0050_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0050_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0051                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates unary expressions                   */
/*   (~, !, and negative value).                                             */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0051a_var
{
    LABEL       "COND0051A Var";
    HELP        "Verify that host properly evaluates unary expression (!).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (!test_input_var)    {READ;}
		ELSE					{READ & WRITE;}
}
/***********************************/

VARIABLE        cond0051b_var
{
    LABEL       "COND0051B Var";
    HELP        "Verify that host properly evaluates unary expression (~).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        #ifndef DEVREV1
        #if _AR5072
        SELECT (~test_input_int) 
 		{
			CASE -2:    READ;
            DEFAULT:    READ & WRITE;
        }
        #else
        SELECT (~test_input_var) 
 		{
			CASE -1:    READ;
            DEFAULT:    READ & WRITE;
        }
        #endif
        #else
        SELECT (~test_input_var) 
 		{
			CASE -1:    READ;
            DEFAULT:    READ & WRITE;
        }
        #endif
}
/***********************************/

VARIABLE        cond0051c_var
{
    LABEL       "COND0051C Var";
    HELP        "Verify that host properly evaluates unary expression (-).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
	    #ifndef DEVREV1   /* AR3159 */
        SELECT (-test_input_int) 
 		{
			CASE -1:    READ;
            DEFAULT:    READ & WRITE;
        }
        #else
            READ & WRITE;
        #endif
}
/***********************************/

VARIABLE        cond0051d_var
{
    LABEL       "COND0051D Var";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
}

MENU    cond0051_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0051a_var
        ,cond0051b_var
        #ifndef DEVREV1   /* AR3159 */
        ,cond0051c_var
        #endif
    }
}    

MENU    cond0051_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0051_page
{
    LABEL   "COND_0051";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0051_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0051_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0052                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   multiplication operators (*, /, %).                                     */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0052a_var
{
    LABEL       "COND0052A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with multiplication operator (*).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var * 5) 
 		{
			CASE 25:    READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0052b_var
{
    LABEL       "COND0052B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with multiplication operator (*).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var * 4.25) 
 		{
			CASE 21.25: READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0052c_var
{
    LABEL       "COND0052C Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with multiplication operator (/).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (25 / test_input_var) 
 		{
			CASE 5:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0052d_var
{
    LABEL       "COND0052D Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with multiplication operator (/).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (31.25 / test_input_var) 
 		{
			CASE 6.25:  READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0052e_var
{
    LABEL       "COND0052E Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with multiplication operator (%).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (27 % test_input_var) 
 		{
			CASE 2:     READ;
            DEFAULT:    READ & WRITE;
        }
}

MENU    cond0052_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0052a_var,
        cond0052b_var,
        cond0052c_var,
        cond0052d_var
    }
}    

MENU    cond0052_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0052_page
{
    LABEL   "COND_0052";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0052_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0052_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0053                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   additive operators. (-, +).                                             */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0053a_var
{
    LABEL       "COND0053A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with additive operator (+).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var + 1) 
 		{
			CASE 6:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0053b_var
{
    LABEL       "COND0053B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with additive operator (+).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var + 1.25) 
 		{
			CASE 6.25:  READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0053c_var
{
    LABEL       "COND0053C Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with additive operator (-).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var - 1) 
 		{
			CASE 4:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0053d_var
{
    LABEL       "COND0053D Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with additive operator (-).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var - 1.25) 
 		{
			CASE 3.75:  READ;
            DEFAULT:    READ & WRITE;
        }
}

MENU    cond0053_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0053a_var,
        cond0053b_var,
        cond0053c_var,
        cond0053d_var
    }
}    

MENU    cond0053_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0053_page
{
    LABEL   "COND_0053";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0053_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0053_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0054                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   shifts (<<, >>).                                                        */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0054a_var
{
    LABEL       "COND0054A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with shift (<<).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var << 1) 
 		{
			CASE 8:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0054b_var
{
    LABEL       "COND0054B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with shift (>>).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var >> 1) 
 		{
			CASE 2:     READ;
            DEFAULT:    READ & WRITE;
        }
}

MENU    cond0054_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0054a_var,
        cond0054b_var
    }
}    

MENU    cond0054_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0054_page
{
    LABEL   "COND_0054";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0054_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0054_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0055                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   relationship operators (<,<=,>,>=).                                     */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0055a_var
{
    LABEL       "COND0055A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (<).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (3 < test_input_var)     {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055b_var
{
    LABEL       "COND0055B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (<).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (3.25 < test_input_var)  {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055c_var
{
    LABEL       "COND0055C Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (<=).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (4 <= test_input_var)    {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055d_var
{
    LABEL       "COND0055D Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (<=).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (4.00 <= test_input_var) {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055e_var
{
    LABEL       "COND0055E Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (>).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var > 3)     {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055f_var
{
    LABEL       "COND0055F Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (>).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var > 3.25)  {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055g_var
{
    LABEL       "COND0055G Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (>=).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var >= 4)    {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0055h_var
{
    LABEL       "COND0055H Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with relationship operator (>=).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var >= 4.00) {READ;}
		ELSE					    {READ & WRITE;}
}

MENU    cond0055_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0055a_var,
        cond0055b_var,
        cond0055c_var,
        cond0055d_var,
        cond0055e_var,
        cond0055f_var,
        cond0055g_var,
        cond0055h_var
    }
}    

MENU    cond0055_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0055_page
{
    LABEL   "COND_0055";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0055_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0055_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0056                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   equality operators (==, !=).                                            */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0056a_var
{
    LABEL       "COND0056A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with equality operator (==).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var == 5)    {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0056b_var
{
    LABEL       "COND0056B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with equality operator (!=).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var != 2)    {READ;}
		ELSE					    {READ & WRITE;}
}

MENU    cond0056_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0056a_var,
        cond0056b_var
    }
}    

MENU    cond0056_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0056_page
{
    LABEL   "COND_0056";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0056_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0056_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0057                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   bitwise operators (&,^,|).                                              */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0057a_var
{
    LABEL       "COND0057A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with bitwise operator (&).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var & 5) 
 		{
			CASE 5:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0057b_var
{
    LABEL       "COND0057B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with bitwise operator (^).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var ^ 4) 
 		{
			CASE 1:     READ;
            DEFAULT:    READ & WRITE;
        }
}
/***********************************/

VARIABLE        cond0057c_var
{
    LABEL       "COND0057C Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with bitwise operator (vert. bar).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var | 5) 
 		{
			CASE 5:     READ;
            DEFAULT:    READ & WRITE;
        }
}

MENU    cond0057_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0057a_var,
        cond0057b_var,
        cond0057c_var
    }
}    

MENU    cond0057_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0057_page
{
    LABEL   "COND_0057";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0057_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0057_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0058                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   logical operators (&&,||).                                              */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0058a_var
{
    LABEL       "COND0058A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with logical operator (&&).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var && 1)    {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0058b_var
{
    LABEL       "COND0058B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with logical operator (dbl. vert. bar).";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var || 0)    {READ;}
		ELSE					    {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0058c_var
{
    LABEL       "COND0058C Var";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
}

MENU    cond0058_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0058a_var,
        cond0058b_var
    }
}    

MENU    cond0058_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0058_page
{
    LABEL   "COND_0058";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0058_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0058_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0059                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating conditional expressions					                     */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates binary expressions with             */
/*   complex parenthesized expressions.                                      */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0059a_var
{
    LABEL       "COND0059A Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with complex parenthesized expressions.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF ((5 - test_input_var) + 1 == 1)  {READ;}
		ELSE					            {READ & WRITE;}
}
/***********************************/

VARIABLE        cond0059b_var
{
    LABEL       "COND0059B Var";
    HELP        "Verify that host properly evaluates binary expressions "
                "with complex parenthesized expressions.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF ((((((5 * test_input_var) + 5) / 10) - 2) % 2)  == 1)    {READ;}
		ELSE					                                    {READ & WRITE;}
}

MENU    cond0059_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS
    {
        cond0059a_var,
        cond0059b_var
    }
}    

MENU    cond0059_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0059_page
{
    LABEL   "COND_0059";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0059_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0059_methods_group
    }
}        

/***********************************/

VARIABLE        cond0060a_var
{
    LABEL       "COND0060A Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0060b_var
{
    LABEL       "COND0060B Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0060c_var
{
    LABEL       "COND0060C Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0061a_var
{
    LABEL       "COND0061A Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0061b_var
{
    LABEL       "COND0061B Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0061c_var
{
    LABEL       "COND0061C Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0061d_var
{
    LABEL       "COND0061D Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}
/***********************************/

VARIABLE        cond0061e_var
{
    LABEL       "COND0061E Var";
    CLASS       CONTAINED;
    TYPE        FLOAT;
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0070                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating nested conditionals					                         */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates nested conditionals when IF         */
/*   statements are nested up to 5 levels deep.                              */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0070_var
{
    LABEL       "COND0070 Var";
    HELP        "Verify that host properly evaluates nested conditionals "
                "when IF statements are nested up to 5 levels deep.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var == 5)
        {   IF (test_input_var == 5)
            {   IF (test_input_var == 5)
                {   IF (test_input_var == 5)
                    {   IF (test_input_var == 5)    {READ;}}}}}      
}

MENU    cond0070_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0070_var   }   
}    

MENU    cond0070_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0070_page
{
    LABEL   "COND_0070";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0070_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0070_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0071                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating nested conditionals					                         */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates nested conditionals when IF-ELSE    */
/*   statements are nested up to 5 levels deep.                              */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0071_var
{
    LABEL       "COND0071 Var";
    HELP        "Verify that host properly evaluates nested conditionals "
                "when IF-ELSE statements are nested up to 5 levels deep.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var == 5)
        {   IF (test_input_var == 5)
            {   IF (test_input_var == 5)
                {   IF (test_input_var == 5)
                    {   IF (test_input_var == 5)    {READ;}
                        ELSE                        {READ & WRITE;}}
                    ELSE                        {READ & WRITE;}}
                ELSE                        {READ & WRITE;}}
            ELSE                        {READ & WRITE;}}
        ELSE                        {READ & WRITE;}
}

MENU    cond0071_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0071_var   }   
}    

MENU    cond0071_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0071_page
{
    LABEL   "COND_0071";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0071_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0071_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0072                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating nested conditionals					                         */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates nested conditionals when SELECT     */
/*   statements are nested up to 5 levels deep.                              */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0072_var
{
    LABEL       "COND0072 Var";
    HELP        "Verify that host properly evaluates nested conditionals "
                "when SELECT statements are nested up to 5 levels deep.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        SELECT (test_input_var)
        {   CASE 5: SELECT (test_input_var)
                    {   CASE 5: SELECT (test_input_var)
                                {   CASE 5: SELECT (test_input_var)
                                            {   CASE 5: SELECT (test_input_var)
                                                        {   CASE 5:     READ;
                                                            DEFAULT:    READ & WRITE;}
                                                DEFAULT:    READ & WRITE;}
                                    DEFAULT:    READ & WRITE;}
                        DEFAULT:    READ & WRITE;}
            DEFAULT:    READ & WRITE;
        }         
                                               
}

MENU    cond0072_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0072_var   }   
}    

MENU    cond0072_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0072_page
{
    LABEL   "COND_0072";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0072_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0072_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0073                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating nested conditionals					                         */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates nested conditionals when IF,        */
/*   IF-ELSE, & SLEECT statements are nested up to 5 levels deep.            */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0073_var
{
    LABEL       "COND0073 Var";
    HELP        "Verify that host properly evaluates nested conditionals when IF, "
                "IF-ELSE, & SLEECT statements are nested up to 5 levels deep.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    HANDLING
        IF (test_input_var == 5)
        {   SELECT (test_input_var)
            {   CASE 5: IF (test_input_var == 5)
                        {   SELECT (test_input_var)
                            {   CASE 5: IF (test_input_var == 5)    {READ;}
                                        ELSE                        {READ & WRITE;}
                                DEFAULT:    READ & WRITE;}}
                        ELSE    {READ & WRITE;}
                DEFAULT:    READ & WRITE;}}    
}

MENU    cond0073_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0073_var   }   
}    

MENU    cond0073_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0073_page
{
    LABEL   "COND_0073";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0073_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0073_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0080                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating method validity					                             */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates method validity.                    */
/*                                                                           */
/*****************************************************************************/

METHOD  cond0080_validity_method
{
    LABEL   "COND0080 Validity Method";
    HELP    "Verify that host properly evaluates method validity.";
    CLASS   INPUT & OPERATE;
    DEFINITION
    {
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Method is valid.",ids,indices,0);
    }
    VALIDITY
        IF (test_input_var == 1)    {TRUE;}
		ELSE					    {FALSE;}
}

MENU    cond0080_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0080_validity_method    }   
}    

MENU    cond0080_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0080_page
{
    LABEL   "COND_0080";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0080_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0080_methods_group
    }
}        

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_COND_0081                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Evaluating variable validity					                         */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host properly evaluates variable validity.                  */
/*                                                                           */
/*****************************************************************************/
VARIABLE        cond0081_validity_var
{
    LABEL       "COND0081 Validity Var";
    HELP        "Verify that host properly evaluates variable validity.";
    CLASS       CONTAINED;
    TYPE        INTEGER (4);
    VALIDITY
        IF (test_input_var == 1)    {TRUE;}
		ELSE					    {FALSE;}
}

MENU    cond0081_eval_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   cond0081_validity_var   }   
}    

MENU    cond0081_methods_group
{
    LABEL   "Methods";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   clear_test_vals_condtb2     }
}    

MENU    cond0081_page
{
    LABEL   "COND_0081";
    #if _DD5_PROFILE
    STYLE   PAGE;
    #endif
    ITEMS
    {
        test_input_var_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0081_eval_group
        #if _DD5_PROFILE
        ,ROWBREAK
        #endif
        ,cond0081_methods_group
    }
}        

#include "1000_Test_Case_Conditional_Menus.ddl"

