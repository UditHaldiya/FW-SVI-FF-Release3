/*****************************************************************************/
/* 1000_Test_Case_Misc.ddl                                                   */
/*                                                                           */
/*   This file contains DDL for miscellaneous test cases.                    */
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
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
**  DD revision and language support test cases                                                                 
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_DDCF_001                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host uses latest version of DD to interface with device.	 */
/*                                                                           */
/*****************************************************************************/
MENU    tc_ddcf_001_window
{
    LABEL   "TC_DDCF_001";
    #if _DD5_PROFILE
    STYLE   WINDOW;
    #endif
    ITEMS   {   r_ds256.FLT }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_ITEM_004                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Item                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that LABEL and HELP strings of supported languages can           */
/*   be displayed.	                                                         */
/*                                                                           */
/*****************************************************************************/
MENU    tc_item_004_window
{
    LABEL   "TC_ITEM_004";
    #if _DD5_PROFILE
    STYLE   WINDOW;
    #endif
    ITEMS   {   r_ds257.U32_1   }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_ITEM_005                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Item                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify host can set default access rights based on DDL classes          */
/*   OPERATE and SERVICE.	                                                 */
/*                                                                           */
/*****************************************************************************/
MENU    tc_item_005_window
{
    LABEL   "TC_ITEM_005";
    #if _DD5_PROFILE
    STYLE   WINDOW;
    #endif
    ITEMS
    {
        v_int8,
        v_uint8,
        v_enum8,
        operate_method,
        v_int16,
        v_uint16,
        v_enum16,
        service_method
    }
}

METHOD  operate_method
{
    LABEL   "Operate Method";
    CLASS   INPUT & OPERATE;
    DEFINITION
    {
       unsigned long ids[1],indices[1];
       display_message("Operate Method executed.",ids,indices,0);
    }
}

METHOD  service_method
{
    LABEL   "Service Method";
    CLASS   INPUT & SERVICE;
    DEFINITION
    {
       unsigned long ids[1],indices[1];
       display_message("Service Method executed.",ids,indices,0);
    }
}
        
/*
******************************************************************************
**  Method test cases                                                                 
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_METH_001                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that the method will execute without error.	                     */
/*                                                                           */
/*****************************************************************************/
METHOD  tc_meth_001
{
    LABEL   "TC_METH_001";
	HELP "This method calls every available builtin.";
    CLASS   INPUT;
    DEFINITION
    {
        long status,failures;
        unsigned long ids[1],indices[1];
		long dummy;
		float floatVal;
		double doubleVal;
		char charArray[99];
		long item_id, member_id;

		ids[0] = ITEM_ID(PARAM.ALERT_KEY);
		indices[0] = 0;
		dummy = 0;

        failures=0;

		/*************************
		 **** Method builtins ****
		 *************************/

        status=add_abort_method(ITEM_ID(abort_meth));
        display_message("add_abort_method() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status=remove_abort_method(ITEM_ID(abort_meth));
        display_message("remove_abort_method() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        remove_all_abort_methods();
        display_message("remove_all_abort_methods() was called and does not return a status",ids,indices,0);
        if(status>0)
            failures++;


		/*********************************
		 **** Variable Table builtins ****
		 *********************************/

        discard_on_exit();
        display_message("discard_on_exit() was called and does not return a status",ids,indices,0);

        send_on_exit();
        display_message("send_on_exit() was called and does not return a status",ids,indices,0);

        save_on_exit();
        display_message("save_on_exit() was called and does not return a status",ids,indices,0);

#if _DD5_PROFILE

        #if _AR4063
        status=get_sel_string(charArray, ITEM_ID(PARAM.ST_REV), 21 /* Label */, 0, &dummy);
        display_message("get_sel_string() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status=get_sel_double(ITEM_ID(fl_input_var_list), 24 /* Count */, 0);  
        display_message("get_sel_double() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;
        #endif

		/*********
		 * Lists *
		 *********/

		/* Insert an item into the list, for testing */
		status = ListInsert(ITEM_ID(fl_input_col_list), 1, ITEM_ID(fl_input_collection));
        display_message("ListInsert() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

		status = ListDeleteElementAt(ITEM_ID(fl_input_col_list), 1);
        display_message("ListDeleteElementAt() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;
#endif

		/*************
		 * Variables *
		 *************/

        status=get_float_value(ITEM_ID(PARAM.V_FLOATING_POINT), 0, &floatVal);
        display_message("get_float_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        floatVal=ret_float_value(ITEM_ID(PARAM.V_FLOATING_POINT), 0);
        display_message("ret_float_value() was called and does not return a status",ids,indices,0);

		floatVal = 0.0;
        status=put_float_value(ITEM_ID(PARAM.V_FLOATING_POINT), 0, floatVal);
        display_message("put_float_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status=get_signed_value(ITEM_ID(PARAM.V_INTEGER32), 0, &dummy);
        display_message("get_signed_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy=ret_signed_value(ITEM_ID(PARAM.V_INTEGER32), 0);
        display_message("ret_signed_value() was called and does not return a status",ids,indices,0);

		dummy = 0;
        status=put_signed_value(ITEM_ID(PARAM.V_INTEGER32), 0, dummy);
        display_message("put_signed_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status=get_unsigned_value(ITEM_ID(PARAM.V_UNSIGNED32), 0, &dummy);
        display_message("get_unsigned_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy=ret_unsigned_value(ITEM_ID(PARAM.V_UNSIGNED32), 0);
        display_message("ret_unsigned_value() was called and does not return a status",ids,indices,0);

        dummy = 0;
        status=put_unsigned_value(ITEM_ID(PARAM.V_UNSIGNED32), 0, dummy);
        display_message("put_unsigned_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = 99;
        status=get_string_value(ITEM_ID(PARAM.V_VISIBLESTRING), 0, charArray, &dummy);
        display_message("get_string_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = 32;
        status=put_string_value(ITEM_ID(PARAM.V_VISIBLESTRING), 0, charArray, dummy);
        display_message("put_string_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = 99;
        status=get_date_value(ITEM_ID(PARAM.V_DATE), 0, charArray, &dummy);
        display_message("get_date_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = 7; /* Size of a date variable */
        status=put_date_value(ITEM_ID(PARAM.V_DATE), 0, charArray, dummy);
        display_message("put_date_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        #if _AR4905
        PARAM.ALERT_KEY=1;
        #endif
        status=assign(ITEM_ID(PARAM.ALERT_KEY),0,ITEM_ID(PARAM.ALERT_KEY),0);
        display_message("assign() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;


        /**************************
         * Communication Builtins *
         **************************/

        status=read_value(ITEM_ID(PARAM.V_INTEGER8), 0);
        display_message("read_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

		PARAM.V_INTEGER8 += 1;  /* Force a change in the cache */
        status=send_value(ITEM_ID(PARAM.V_INTEGER8), 0);
        display_message("send_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status=send_all_values();
        display_message("send_all_values() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        get_response_code(&dummy, &item_id, &member_id);
        display_message("get_response_code() was called and does not return a status",ids,indices,0);

        dummy = get_comm_error();
        display_message("get_comm_error() was called and does not return a status",ids,indices,0);

        abort_on_all_comm_errors();
        display_message("abort_on_all_comm_errors() was called and does not return a status",ids,indices,0);

        abort_on_all_response_codes();
        display_message("abort_on_all_response_codes() was called and does not return a status",ids,indices,0);

        status = abort_on_comm_error(1);
        display_message("abort_on_comm_error() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = abort_on_response_code(1);
        display_message("abort_on_response_code() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        fail_on_all_comm_errors();
        display_message("fail_on_all_comm_errors() was called and does not return a status",ids,indices,0);

        fail_on_all_response_codes();
        display_message("fail_on_all_response_codes() was called and does not return a status",ids,indices,0);

        status = fail_on_comm_error(1);
        display_message("fail_on_comm_error() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = fail_on_response_code(1);
        display_message("fail_on_response_code() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        retry_on_all_comm_errors();
        display_message("retry_on_all_comm_errors() was called and does not return a status",ids,indices,0);

        retry_on_all_response_codes();
        display_message("retry_on_all_response_codes() was called and does not return a status",ids,indices,0);

        status = retry_on_comm_error(1);
        display_message("retry_on_comm_error() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = retry_on_response_code(1);
        display_message("retry_on_response_code() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = get_status_string(ITEM_ID(PARAM.MODE_BLK), MEMBER_ID(TARGET), 1, charArray, 98);
        display_message("get_status_string() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = get_comm_error_string(1, charArray, 98);
        display_message("get_comm_error_string() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = get_response_code_string(ITEM_ID(PARAM.ST_REV), 0, 1, charArray, 98);
        display_message("get_response_code_string() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        /********************
         * Display Builtins *
         ********************/

        display_message("Testing display_builtin_error(): should print an out-of-memory message now...",ids,indices,0);
        status = display_builtin_error(BLTIN_NO_MEMORY);    /*AR4929*/
        display_message("display_builtin_error() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = display_message("display_message test", ids, indices, 0);
        display_message("display_message() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        ids[0] = ITEM_ID(PARAM.MODE_BLK);
        indices[0] = MEMBER_ID(TARGET);
        status = display_dynamics("display_dynamics test MODE_BLK.TARGET=%{0}", ids, indices, 1);
        display_message("display_dynamics() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        display_message("Testing display_comm_error(): should print an error message now...",ids,indices,0);
        status = display_comm_error(1);
        display_message("display_comm_error() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        display_message("Testing display_response_code(): should print an error message now...",ids,indices,0);
        status = display_response_code(ITEM_ID(PARAM.ST_REV), 0, 1);
        display_message("display_response_code() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        ids[0] = ITEM_ID(PARAM.MODE_BLK);
        indices[0] = MEMBER_ID(TARGET);
        status = delayfor(2, "delayfor() test MODE_BLK.TARGET=%{0}", ids, indices, 1);
        display_message("delayfor() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = edit_device_value("edit_device_value() enter value for MODE_BLK.TARGET", ids, indices, 0,
            ITEM_ID(PARAM.MODE_BLK), MEMBER_ID(TARGET));
        display_message("edit_device_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = edit_local_value("edit_local_value() test: enter an integer value", ids, indices, 0, 
            "dummy");
        display_message("edit_local_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = select_from_menu("select_from_menu() test: enter any option", ids, indices, 0, 
            "continue;also continue", &dummy);
        display_message("select_from_menu() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = get_acknowledgement("get_acknowledgement() test", ids, indices, 0);
        display_message("get_acknowledgement() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

#if _DD5_PROFILE

        status = MenuDisplay(ITEM_ID(window_test_datatypestb), "continue;also continue", &dummy);
        display_message("MenuDisplay() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;
#endif

        /**************************
         * Miscellaneous Builtins *
         **************************/

        floatVal = 0.0;
        status = is_NaN(floatVal);
        display_message("is_NaN() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = NaN_value(&doubleVal);
        display_message("NaN_value() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        status = get_stddict_string(0x1900000, charArray, 98);
        display_message("get_stddict_string() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = resolve_block_ref(MEMBER_ID(BLOCK_TAG));
        display_message("resolve_block_ref() was called and does not return a status",ids,indices,0);
        
#if _DD5_PROFILE

        dummy = resolve_list_ref(ITEM_ID(fl_input_var_list));
        display_message("resolve_list_ref() was called and does not return a status",ids,indices,0);

        dummy = resolve_local_ref(MEMBER_ID(LOC_INPUT_VAR));
        display_message("resolve_local_ref() was called and does not return a status",ids,indices,0);
        
#endif
        
        dummy = resolve_param_ref(MEMBER_ID(ST_REV));
        display_message("resolve_param_ref() was called and does not return a status",ids,indices,0);
        
        dummy = resolve_param_list_ref(MEMBER_ID(VIEW_1));
        display_message("resolve_param_list_ref() was called and does not return a status",ids,indices,0);
        
        dummy = resolve_array_ref(ITEM_ID(a_bool), 1);
        display_message("resolve_array_ref() was called and does not return a status",ids,indices,0);
        
        dummy = resolve_record_ref(ITEM_ID(r_ds65), MEMBER_ID(STATUS));
        display_message("resolve_record_ref() was called and does not return a status",ids,indices,0);
        
#if _DD5_PROFILE

        dummy = resolve_selector_ref(ITEM_ID(fl_input_var_list), 0, 24 /* SEL_COUNT */);
        display_message("resolve_selector_ref() was called and does not return a status",ids,indices,0);

#endif
        
        status = get_resolve_status();
        display_message("get_resolve_status() builtin return status: %[d]{status}",ids,indices,0);
        if(status>0)
            failures++;

        dummy = get_dds_error(charArray, 98);
        display_message("get_dds_error() was called and does not return a status",ids,indices,0);

        display_message("Number of builtin failures: %[d]{failures}",ids,indices,0);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_METH_002                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that the cross-block builtins will execute without error.        */
/*                                                                           */
/*****************************************************************************/
#if _DD5_PROFILE
METHOD  tc_meth_002
{
    LABEL   "Test Cross-Block Builtins";
    HELP    "Verify that the cross-block builtins will execute without error.";
    CLASS   INPUT;
    DEFINITION
    {
        long status,failures;
        unsigned long ids[1],indices[1];
		unsigned long blockids[1], blockinstances[1];
		long dummy;
		float floatVal;
		double doubleVal;
		char charArray[99];
		long item_id, member_id;

		/* Initialize to point to the first instance of the DataTypesTB block */
		blockids[0] = ITEM_ID(DATATYPESTB);
		blockinstances[0] = 0;

		ids[0] = ITEM_ID(PARAM.ALERT_KEY);
		indices[0] = 0;
		dummy = 0;

        failures=0;

		/*************
		 * Variables *
		 *************/

        status=get_float_value2(blockids[0], blockinstances[0], ITEM_ID(v_floating_point), 0, &floatVal);
        display_message2("get_float_value2() builtin return status: %[d]{status}",blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        floatVal=ret_float_value2(blockids[0], blockinstances[0], ITEM_ID(v_floating_point), 0);
        display_message2("ret_float_value2() was called and does not return a status", blockids, blockinstances, ids,indices,0);

		floatVal = 0.0;
        status=put_float_value2(blockids[0], blockinstances[0], ITEM_ID(v_floating_point), 0, floatVal);
        display_message2("put_float_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        status=get_signed_value2(blockids[0], blockinstances[0], ITEM_ID(v_int32), 0, &dummy);
        display_message2("get_signed_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy=ret_signed_value2(blockids[0], blockinstances[0], ITEM_ID(v_int32), 0);
        display_message2("ret_signed_value2() was called and does not return a status", blockids, blockinstances, ids,indices,0);

		dummy = 0;
        status=put_signed_value2(blockids[0], blockinstances[0], ITEM_ID(v_int32), 0, dummy);
        display_message2("put_signed_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        status=get_unsigned_value2(blockids[0], blockinstances[0], ITEM_ID(v_uint32), 0, &dummy);
        display_message2("get_unsigned_value3() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy=ret_unsigned_value2(blockids[0], blockinstances[0], ITEM_ID(v_uint32), 0);
        display_message2("ret_unsigned_value2() was called and does not return a status", blockids, blockinstances, ids,indices,0);

        dummy = 0;
        status=put_unsigned_value2(blockids[0], blockinstances[0], ITEM_ID(v_uint32), 0, dummy);
        display_message2("put_unsigned_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy = 99;
        status=get_string_value2(blockids[0], blockinstances[0], ITEM_ID(v_vis_string32), 0, charArray, &dummy);
        display_message2("get_string_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy = 32;
        status=put_string_value2(blockids[0], blockinstances[0], ITEM_ID(v_vis_string32), 0, charArray, dummy);
        display_message2("put_string_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy = 99;
        status=get_date_value2(blockids[0], blockinstances[0], ITEM_ID(v_date), 0, charArray, &dummy);
        display_message2("get_date_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        dummy = 7; /* Size of a date variable */
        status=put_date_value2(blockids[0], blockinstances[0], ITEM_ID(v_date), 0, charArray, dummy);
        display_message2("put_date_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        status=assign2(blockids[0], blockinstances[0], ITEM_ID(__alert_key),0,
					   blockids[0], blockinstances[0], ITEM_ID(__st_rev),0);
        display_message2("assign2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;


        /**************************
         * Communication Builtins *
         **************************/

        status=read_value2(blockids[0], blockinstances[0], ITEM_ID(v_int8), 0);
        display_message2("read_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        status=send_value2(blockids[0], blockinstances[0], ITEM_ID(v_int8), 0);
        display_message2("send_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;


        /********************
         * Display Builtins *
         ********************/

        status = display_message2("display_message2() test", blockids, blockinstances, ids, indices, 0);
        display_message2("display_message2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        ids[0] = ITEM_ID(__mode_blk);
        indices[0] = MEMBER_ID(TARGET);
        status = display_dynamics2("display_dynamics2 test MODE_BLK.TARGET=%{0}", 
			blockids, blockinstances, ids, indices, 1);
        display_message2("display_dynamics2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;


        ids[0] = ITEM_ID(__mode_blk);
        indices[0] = MEMBER_ID(TARGET);
#if _AR3478
        status = delayfor2(2, "delayfor2() test MODE_BLK.TARGET=%{0}", blockids, blockinstances, ids, indices, 1);
        display_message2("delayfor2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;
#endif

        status = edit_device_value2("edit_device_value2() enter value for MODE_BLK.TARGET", blockids, blockinstances, ids, indices, 0,
            blockids[0], blockinstances[0], ITEM_ID(__mode_blk), MEMBER_ID(TARGET));
        display_message2("edit_device_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        status = edit_local_value2("edit_local_value2() test: enter an integer value", blockids, blockinstances, ids, indices, 0, 
            "dummy");
        display_message2("edit_local_value2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

#if _AR3479
        status = select_from_menu2("select_from_menu2() test: enter any option", blockids, blockinstances, ids, indices, 0, 
            "continue;also continue", &dummy);
        display_message2("select_from_menu2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;
#endif
        status = get_acknowledgement2("get_acknowledgement2() test", blockids, blockinstances, ids, indices, 0);
        display_message2("get_acknowledgement2() builtin return status: %[d]{status}", blockids, blockinstances, ids,indices,0);
        if(status>0)
            failures++;

        /**************************
         * Miscellaneous Builtins *
         **************************/
        
        dummy = resolve_local_ref2(blockids[0], blockinstances[0], MEMBER_ID(LOC_INPUT_VAR));
        display_message2("resolve_local_ref2() was called and does not return a status", blockids, blockinstances, ids,indices,0);
       
        
        dummy = resolve_param_ref2(blockids[0], blockinstances[0], MEMBER_ID(ST_REV));
        display_message2("resolve_param_ref() was called and does not return a status", blockids, blockinstances, ids,indices,0);
        
        dummy = resolve_array_ref2(blockids[0], blockinstances[0], ITEM_ID(a_bool), 1);
        display_message2("resolve_array_ref2() was called and does not return a status", blockids, blockinstances, ids,indices,0);
        
        dummy = resolve_record_ref2(blockids[0], blockinstances[0], ITEM_ID(r_ds65), MEMBER_ID(STATUS));
        display_message2("resolve_record_ref2() was called and does not return a status", blockids, blockinstances, ids,indices,0);

        display_message2("Number of builtin failures: %[d]{failures}", blockids, blockinstances, ids,indices,0);
    }
}
#endif /* _DD5_PROFILE */

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_METH_003                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that non-ASCII Unicode prompt strings display correctly.         */
/*                                                                           */
/*****************************************************************************/
#if _DD5_PROFILE
METHOD  tc_meth_003
{
    LABEL   "Test Unicode Prompt Strings";
    HELP    "Verify that non-ASCII Unicode prompt strings display correctly.";
    CLASS   INPUT;
    DEFINITION
    {
        long status,failures;
        unsigned long ids[1],indices[1];
	long dummy;
	float floatVal;
	double doubleVal;
	char charArray[99];
	long item_id, member_id;

	ids[0] = ITEM_ID(PARAM.ALERT_KEY);
	indices[0] = 0;
	dummy = 0;

        get_acknowledgement("All the following strings should display with no question marks or other substitutes.", ids, indices, 0);
        get_acknowledgement("Non-ASCII string 1: これはテストである",ids,indices,0);
        get_acknowledgement("Non-ASCII string 2: Это испытание", ids, indices, 0);
        get_acknowledgement("Non-ASCII string 3: Ciò è una prova", ids, indices, 0);
        get_acknowledgement("All the above strings should have displayed with no question marks or other substitutes.", ids, indices, 0);
    }
}

#endif

MENU    tc_meth_menu
{
    LABEL   "Method Test Cases";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        tc_meth_001
	#if _DD5_PROFILE
	,tc_meth_003
	#endif
    }
}

METHOD abort_meth
{
    LABEL   "Abort-called method";
    CLASS   INPUT;
    DEFINITION
    {
	}
}

