/*****************************************************************************/
/* 1000_Methods.ddl                                                          */
/*                                                                           */
/*   This DDL file contains methods for all the blocks.                      */
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
/* 01-12-09 ! ARs 3159                                          ! 2.0 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** CondTB1 methods                                                                
******************************************************************************
*/
 
METHOD  clear_test_vals_condtb1
{
    LABEL   "Clear All Test Values";
    CLASS   INPUT;
    DEFINITION
    {
        long status;
        int i;

        send_on_exit();

        status=put_unsigned_value(ITEM_ID(test_input_var),0,0);

        status=put_float_value(ITEM_ID(test_input_rec),MEMBER_ID(VALUE),0);
        status=put_unsigned_value(ITEM_ID(test_input_rec),MEMBER_ID(STATUS),0);

        for(i=1;i<=10;i++)
        {
            status=put_unsigned_value(ITEM_ID(test_input_ary_1),i,0);
            status=put_unsigned_value(ITEM_ID(test_input_ary_2),i,0);
        }

        status=put_unsigned_value(ITEM_ID(test_input_enum),0,0);

        status=put_unsigned_value(ITEM_ID(test_input_bit_enum),0,0);
    }
}

/*
******************************************************************************
** CondTB2 methods                                                                
******************************************************************************
*/
 
METHOD  clear_test_vals_condtb2
{
    LABEL   "Clear All Test Values";
    CLASS   INPUT;
    DEFINITION
    {
        long status;
        int i;

        send_on_exit();

        status=put_unsigned_value(ITEM_ID(test_input_var),0,0);
        #ifndef DEVREV1   /* AR3159 */
        status=put_signed_value(ITEM_ID(test_input_int),0,0);
        #endif
         
        for(i=1;i<=10;i++)
        {
            status=put_unsigned_value(ITEM_ID(test_input_ary_1),i,0);
            status=put_unsigned_value(ITEM_ID(test_input_ary_2),i,0);
        }

        status=put_unsigned_value(ITEM_ID(test_input_enum),0,0);
    }
}

/*          
******************************************************************************
** VisualTB methods                                                                
******************************************************************************
*/
 
METHOD  clear_test_vals_visualtb
{
    LABEL   "Clear All Test Values";
    CLASS   INPUT;
    DEFINITION
    {
        long status;
        int i;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,0);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,0);
        status=put_float_value(ITEM_ID(test_fl_val_3),0,0);
        status=put_float_value(ITEM_ID(test_fl_val_4),0,0);

        status=put_signed_value(ITEM_ID(test_val_int_8),0,0);
        status=put_signed_value(ITEM_ID(test_val_int_16),0,0);
        status=put_signed_value(ITEM_ID(test_val_int_32),0,0);

        status=put_unsigned_value(ITEM_ID(test_val_uint_8),0,0);
        status=put_unsigned_value(ITEM_ID(test_val_uint_16),0,0);
        status=put_unsigned_value(ITEM_ID(test_val_uint_32),0,0);

        for(i=1;i<=_ARRAY_SIZE;i++)
        {
            status=put_float_value(ITEM_ID(test_y_array_1),i,0);
            status=put_float_value(ITEM_ID(test_x_array_1),i,0);
            status=put_float_value(ITEM_ID(test_y_array_2),i,0);
            status=put_float_value(ITEM_ID(test_x_array_2),i,0);
        }

        status=put_float_value(ITEM_ID(test_record),MEMBER_ID(VALUE),0);
        status=put_unsigned_value(ITEM_ID(test_record),MEMBER_ID(STATUS),0);

        status=put_string_value(ITEM_ID(test_string),0,"",32);

        status=put_float_value(ITEM_ID(test_hi_hi_limit),0,0);
        status=put_float_value(ITEM_ID(test_hi_limit),0,0);
        status=put_float_value(ITEM_ID(test_lo_limit),0,0);
        status=put_float_value(ITEM_ID(test_lo_lo_limit),0,0);
        status=put_float_value(ITEM_ID(test_right_limit),0,0);
        status=put_float_value(ITEM_ID(test_left_limit),0,0);    
    }
}