/*****************************************************************************/
/* 1000_Test_Case_Conditional_Menus.ddl                                            */
/*                                                                           */
/*   This file contains DDL for the displayed menus for conditional test cases.                  */
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
/* 06-04-08 ! Initial version                                   ! 1.0 ! dg   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2008                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Menus  for conditional test cases
******************************************************************************
*/

/***********************************************************************************
 *                                                 DISPLAY_FORMAT                                              *
 ***********************************************************************************/

MENU   display_format_test
{
        LABEL "Display Format";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                display_format_test_input_group,
                display_format_test_evaluate_group
        }
}

MENU    display_format_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
        #if _DD5_PROFILE
		LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
		#endif

        /* Methods to assist with entry */
        write_display_format_1_method, write_display_format_2_method          
         }
}    

MENU    display_format_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_display_format_1_method
{
        LABEL "Write DISPLAY_FORMAT_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = 1;   /* Write this value to all interested parties  */
                bit_value = _DISPLAY_FORMAT_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();

                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}

#endif /* DD5_PROFILE */
 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_display_format_2_method
{
        LABEL "Write DISPLAY_FORMAT_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = 2;   /* Write this value to all interested parties  */
                bit_value = _DISPLAY_FORMAT_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif /* DD5_PROFILE */ 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                       EDIT_FORMAT                                                *
 ***********************************************************************************/
 MENU   edit_format_test
{
        LABEL "EditFormat";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                edit_format_test_input_group,
                edit_format_test_evaluate_group
        }
}

MENU    edit_format_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
        #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
		#endif
		        
          /* Methods to assist with entry */
          write_edit_format_1_method, write_edit_format_2_method         
         }
}    

MENU    edit_format_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_edit_format_1_method
{
        LABEL "Write EDIT_FORMAT_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = 3;   /* Write this value to all interested parties  */
                bit_value = _EDIT_FORMAT_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif /* DD5_PROFILE */ 
 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_edit_format_2_method
{
        LABEL "Write EDIT_FORMAT_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = 4;   /* Write this value to all interested parties  */
                bit_value = _EDIT_FORMAT_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                          MIN_VALUE                                                    *
 ***********************************************************************************/
 MENU   min_value_test
{
        LABEL "MinValue";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                min_value_test_input_group,
                min_value_test_evaluate_group
        }
}

MENU    min_value_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
        #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
		#endif
		        
          /* Methods to assist with entry */
          write_min_value_1_method, write_min_value_2_method         
         }
}    

MENU    min_value_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_min_value_1_method
{
        LABEL "Write MIN_VALUE_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _MIN_VALUE_1;   /* Write this value to all interested parties  */
                bit_value = _MIN_VALUE_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_min_value_2_method
{
        LABEL "Write MIN_VALUE_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _MIN_VALUE_2;   /* Write this value to all interested parties  */
                bit_value = _MIN_VALUE_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                          MAX_VALUE                                                    *
 ***********************************************************************************/
 MENU   max_value_test
{
        LABEL "MaxValue";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                max_value_test_input_group,
                max_value_test_evaluate_group
        }
}

MENU    max_value_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif        
          /* Methods to assist with entry */
          write_max_value_1_method, write_max_value_2_method         
         }
}    

MENU    max_value_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_max_value_1_method
{
        LABEL "Write MAX_VALUE_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _MAX_VALUE_1;   /* Write this value to all interested parties  */
                bit_value = _MAX_VALUE_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif
 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_max_value_2_method
{
        LABEL "Write MAX_VALUE_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _MAX_VALUE_2;   /* Write this value to all interested parties  */
                bit_value = _MAX_VALUE_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                                ENUM                                                         *
 ***********************************************************************************/
 MENU  enum_value_test
{
        LABEL "EnumValue";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                enum_value_test_input_group,
                enum_value_test_evaluate_group
        }
}

MENU    enum_value_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif
	        
          /* Methods to assist with entry */
          write_enum_value_1_method, write_enum_value_2_method         
         }
}    

MENU    enum_value_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_enum_var,
        cond0011_enum_var,
        cond0012_enum_var,
        cond0013_enum_var,
        cond0015_enum_var,
        cond0016_enum_var,
        cond0017_enum_var,
        cond0018a_enum_var,
        cond0018b_enum_var,
        cond0019_enum_var,
        cond0020_enum_var,
        cond0021_enum_var,
        cond0024_enum_var,
        cond0026_enum_var,
        cond0027a_enum_var,
        cond0027b_enum_var,
        cond0028a_enum_var,
        cond0028b_enum_var,
        cond0028c_enum_var,
        cond0029a_enum_var,
        cond0029b_enum_var,
        cond0029c_enum_var,
        cond0030a_enum_var,
        cond0030b_enum_var,
        cond0030c_enum_var,
        cond0031_enum_var
         }
}    

METHOD write_enum_value_1_method
{
        LABEL "Write ENUM_VALUE_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _ENUMERATED_1;   /* Write this value to all interested parties  */
                bit_value = _ENUMERATED_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_enum_value_2_method
{
        LABEL "Write ENUM_VALUE_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _ENUMERATED_2;   /* Write this value to all interested parties  */
                bit_value = _ENUMERATED_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                         BIT_ ENUM                                                      *
 ***********************************************************************************/
 MENU  bit_enum_value_test
{
        LABEL "BitEnumValue";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                bit_enum_value_test_input_group,
                bit_enum_value_test_evaluate_group
        }
}

MENU    bit_enum_value_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif
	        
          /* Methods to assist with entry */
          write_bit_enum_value_1_method, write_bit_enum_value_2_method         
         }
}    

MENU    bit_enum_value_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_bit_enum_var,
        cond0011_bit_enum_var,
        cond0012_bit_enum_var,
        cond0013_bit_enum_var,
        cond0015_bit_enum_var,
        cond0016_bit_enum_var,
        cond0017_bit_enum_var,
        cond0018a_bit_enum_var,
        cond0018b_bit_enum_var,
        cond0019_bit_enum_var,
        cond0020_bit_enum_var,
        cond0021_bit_enum_var,
        cond0024_bit_enum_var,
        cond0026_bit_enum_var,
        cond0027a_bit_enum_var,
        cond0027b_bit_enum_var,
        cond0028a_bit_enum_var,
        cond0028b_bit_enum_var,
        cond0028c_bit_enum_var,
        cond0029a_bit_enum_var,
        cond0029b_bit_enum_var,
        cond0029c_bit_enum_var,
        cond0030a_bit_enum_var,
        cond0030b_bit_enum_var,
        cond0030c_bit_enum_var,
		cond0031_bit_enum_var
         }
}    

METHOD write_bit_enum_value_1_method
{
        LABEL "Write BIT_ENUM_VALUE_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _BIT_ENUMERATED_1;   /* Write this value to all interested parties  */
                bit_value = _BIT_ENUMERATED_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_bit_enum_value_2_method
{
        LABEL "Write BIT_ENUM_VALUE_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _BIT_ENUMERATED_2;   /* Write this value to all interested parties  */
                bit_value = _BIT_ENUMERATED_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}


/***********************************************************************************
 *                                                 CONSTANT_UNIT                                                *
 ***********************************************************************************/
 MENU  constant_unit_test
{
        LABEL "ConstantUnit";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                constant_unit_test_input_group,
                constant_unit_test_evaluate_group
        }
}

MENU    constant_unit_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif
	        
          /* Methods to assist with entry */
          write_constant_unit_1_method, write_constant_unit_2_method         
         }
}    

MENU    constant_unit_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_constant_unit_1_method
{
        LABEL "Write CONSTANT_UNIT_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _CONSTANT_UNIT_1;   /* Write this value to all interested parties  */
                bit_value = _CONSTANT_UNIT_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_constant_unit_2_method
{
        LABEL "Write CONSTANT_UNIT_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _CONSTANT_UNIT_2;   /* Write this value to all interested parties  */
                bit_value = _CONSTANT_UNIT_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                       HANDLING                                                         *
 ***********************************************************************************/
 MENU  handling_test
{
        LABEL "Handling";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                handling_test_input_group,
                handling_test_evaluate_group
        }
}

MENU    handling_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif
	        
          /* Methods to assist with entry */
          write_handling_1_method, write_handling_2_method         
         }
}    

MENU    handling_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_handling_1_method
{
        LABEL "Write HANDLING_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _HANDLING_1;   /* Write this value to all interested parties  */
                bit_value = _HANDLING_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_handling_2_method
{
        LABEL "Write HANDLING_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _HANDLING_2;   /* Write this value to all interested parties  */
                bit_value = _HANDLING_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

/***********************************************************************************
 *                                                       VALIDITY                                                         *
 ***********************************************************************************/
MENU  validity_test
{
        LABEL "Validity";
    #if _DD5_PROFILE
        STYLE  PAGE;
    #endif
        ITEMS {
                validity_test_input_group,
                validity_test_evaluate_group
        }
}

MENU    validity_test_input_group
{
    LABEL   "Input";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {   
    
        /* The variables to be entered */
        test_input_var,  test_input_rec.VALUE,  test_input_bit_enum,  test_input_ary_1[1],

        /* These are really the same as above: 
         * PARAM.TEST_INPUT_VAR,  PARAM.TEST_INPUT_REC.VALUE, PARAM.TEST_INPUT_ARY_1[1],  
         */

        /* Local variables to be entered */
    #if _DD5_PROFILE
        LOCAL_PARAM.LOCAL_INPUT_VAR, LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1, LOCAL_PARAM.LOCAL_INPUT_ARY[1],
	#endif
	        
          /* Methods to assist with entry */
          write_validity_1_method, write_validity_2_method         
         }
}    

MENU    validity_test_evaluate_group
{
    LABEL   "Evaluate";
    #if _DD5_PROFILE
    STYLE   GROUP;
    #endif
    ITEMS   {  
        cond0010_float_var,
        cond0011_float_var,
        cond0012_float_var,
        cond0013_float_var,
        cond0015_float_var,
        cond0016_float_var,
        cond0017_float_var,
        cond0018a_float_var,
        cond0018b_float_var,
        cond0019_float_var,
        cond0020_float_var,
        cond0021_float_var,
        cond0024_float_var,
        cond0026_float_var,
        cond0027a_float_var,
        cond0027b_float_var,
        cond0028a_float_var,
        cond0028b_float_var,
        cond0028c_float_var,
        cond0029a_float_var,
        cond0029b_float_var,
        cond0029c_float_var,
        cond0030a_float_var,
        cond0030b_float_var,
        cond0030c_float_var,
        cond0031_float_var
         }
}    

METHOD write_validity_1_method
{
        LABEL "Write VALIDITY_1";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _VALIDITY_1;   /* Write this value to all interested parties  */
                bit_value = _VALIDITY_1_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif 
               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

METHOD write_validity_2_method
{
        LABEL "Write VALIDITY_2";
	CLASS 	INPUT;
        DEFINITION {
                long            status;
		unsigned long	ids[1], members[1];
		unsigned long	value; 
                int errors;
                unsigned long bit_value;

                value = _VALIDITY_2;   /* Write this value to all interested parties  */
                bit_value = _VALIDITY_2_BIT ;        /* This is for the bit enumerated variables */       
                
                errors = 0;
                send_on_exit();
                
                ids[0] = ITEM_ID(test_input_var);
                members[0] = 0;                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_rec);
                members[0] = MEMBER_ID(VALUE);                
                status=put_float_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[i]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_ary_1);
                members[0] = 1;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                ids[0] = ITEM_ID(test_input_bit_enum);
                members[0] = 0;
                status=put_unsigned_value(ids[0], members[0], bit_value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_VAR */
#if _DD5_PROFILE
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_VAR);
                members[0] = 0;  /* Array index */
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }

                /* LOCAL_PARAM.LOCAL_INPUT_REC.INPUT_ELEM_1  */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_REC);
                members[0] = MEMBER_ID(INPUT_ELEM_1);
                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
                
                /* LOCAL_PARAM.LOCAL_INPUT_ARY[1] */
                ids[0] = ITEM_ID(LOCAL_PARAM.LOCAL_INPUT_ARY);
                members[0] = 1; /* Array index */                
                status=put_unsigned_value(ids[0], members[0], value);
                if (status)
                {
                        display_message("Write of %[L]{0}  failed with error %[d]{status}", ids, members, 1); 
                        errors++;
                }
				/* Clear out test_input_list, then insert TEST_INPUT_REC as the first element */
				while (test_input_list.COUNT > 0)
				{
					ListDeleteElementAt(ITEM_ID(test_input_list), 1);
				}
				PARAM.TEST_INPUT_REC.VALUE = value;
				status = ListInsert(ITEM_ID(test_input_list), 1, ITEM_ID(PARAM.TEST_INPUT_REC));
				if (status)
				{
					display_message("ListInsert of test_input_list failed with error %[d]{status}", ids, members, 0);
					errors++;
				}
#endif               
                if  (!errors)
                        display_message("All writes succeeded.", ids, members, 0);
                else
                        display_message("One or more writes failed.", ids, members, 0);
        }
}

