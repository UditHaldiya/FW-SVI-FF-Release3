/*****************************************************************************/
/* 1000_Test_Case_File_and_List.ddl                                          */
/*                                                                           */
/*   This file contains DDL for File and List test cases.                    */
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

#if _DD5_PROFILE

/*
******************************************************************************
** Common constructs for File and List test cases                                                                
******************************************************************************
*/

/* local parameter item definitions */
VARIABLE    fl_input_var
{
    LABEL   "Local Input Variable";
    CLASS   LOCAL;
    TYPE    FLOAT;
}

VARIABLE    fl_input_enum_var
{
    LABEL   "Local Input Enum Variable";
    CLASS   LOCAL;
    TYPE    ENUMERATED
    {   _DATATYPESTB_ENUM8  }
}

VARIABLE    fl_input_bit_enum_var
{
    LABEL   "Local Input Bit-Enum Variable";
    CLASS   LOCAL;
    TYPE    BIT_ENUMERATED
    {   _DATATYPESTB_BITENUM8   }
}

RECORD      fl_input_rec
{
    LABEL   "Local Input Record";
    MEMBERS
    {
        INPUT_ELEM_1,   fl_input_var ;
        INPUT_ELEM_2,   fl_input_var ;
    }
}

ARRAY       fl_input_arr
{
    LABEL   "Local Input Array";
    TYPE    fl_input_var;
    NUMBER_OF_ELEMENTS  _ARRAY_SIZE;
}        

/* collection of local parameter items */
COLLECTION  fl_input_collection
{
    LABEL   "Local Input Collection";
    MEMBERS
    {
        IN_COL_REC,     fl_input_rec;
        IN_COL_ARR,     fl_input_arr;
    }
}   

/* local parameter item lists */
LIST    fl_input_var_list
{
    LABEL   "Local Input Var List";
    TYPE    fl_input_var;
}

LIST    fl_input_enum_var_list
{
    LABEL   "Local Input Enum Var List";
    TYPE    fl_input_enum_var;
}

LIST    fl_input_bit_enum_var_list
{
    LABEL   "Local Input Bit-Enum Var List";
    TYPE    fl_input_bit_enum_var;
}

LIST    fl_input_rec_list
{
    LABEL   "Local Input Rec List";
    TYPE    fl_input_rec;
}

LIST    fl_input_arr_list
{
    LABEL   "Local Input Arr List";
    TYPE    fl_input_arr;
}

LIST    fl_input_col_list
{
    LABEL   "Local Input Col List";
    TYPE    fl_input_collection;
}

LIST    fl_input_var_list_with_cap
{
    LABEL   "Local Input Var List with Capacity";
    TYPE    fl_input_var;
	CAPACITY 3;
}


/* local parameter item and list file */
FILE    fl_input_file
{
    LABEL   "Local Input File";
    MEMBERS
    {
        FL_INPUT_VAR,				fl_input_var;
		FL_INPUT_ENUM,				fl_input_enum_var;
		FL_INPUT_BIT_ENUM,			fl_input_bit_enum_var;
		FL_INPUT_REC,				fl_input_rec;
		FL_INPUT_ARR,				fl_input_arr;
		FL_INPUT_COL,				fl_input_collection;

        FL_INPUT_VAR_LIST,			fl_input_var_list;
		FL_INPUT_ENUM_LIST,			fl_input_enum_var_list;
		FL_INPUT_BIT_ENUM_LIST,		fl_input_bit_enum_var_list;
		FL_INPUT_REC_LIST,			fl_input_rec_list;
		FL_INPUT_ARR_LIST,			fl_input_arr_list;
		FL_INPUT_COL_LIST,			fl_input_col_list;
    }
}      

/* collection of block parameter items */
COLLECTION  fl_blk_parm_collection
{
    LABEL   "Blk Param Collection";
    MEMBERS
    {
        BLK_COL_REC,    r_ds65;
        BLK_COL_ARR,    a_floating_point;
    }
}   

/* block parameter item lists */
LIST    fl_blk_parm_var_list
{
    LABEL   "Blk Param Var List";
    TYPE    v_floating_point;
}

LIST    fl_blk_parm_enum_var_list
{
    LABEL   "Blk Param Enum Var List";
    TYPE    v_enum8;
}

LIST    fl_blk_parm_bit_enum_var_list
{
    LABEL   "Blk Param Bit-Enum Var List";
    TYPE    v_bit_enum8;
}

LIST    fl_blk_parm_rec_list
{
    LABEL   "Blk Param Rec List";
    TYPE    r_ds65;
}

LIST    fl_blk_parm_arr_list
{
    LABEL   "Blk Param Arr List";
    TYPE    a_floating_point;
}

LIST    fl_blk_parm_col_list
{
    LABEL   "Blk Param Col List";
    TYPE    fl_blk_parm_collection;
}

#if !_AR5274
/* block parameter item and list file */
FILE    fl_blk_param_file
{
    LABEL   "Blk Param File";
    MEMBERS
    {
        FL_BLK_PARM_VAR,			    v_floating_point;
		FL_BLK_PARM_ENUM,				v_enum8;
		FL_BLK_PARM_BIT_ENUM,			v_bit_enum8;
		FL_BLK_PARM_REC,				r_ds65;
		FL_BLK_PARM_ARR,				a_floating_point;
		FL_BLK_PARM_COL,				fl_blk_parm_collection;

        FL_BLK_PARM_VAR_LIST,			fl_blk_parm_var_list;
		FL_BLK_PARM_ENUM_LIST,			fl_blk_parm_enum_var_list;
		FL_BLK_PARM_BIT_ENUM_LIST,		fl_blk_parm_bit_enum_var_list;
		FL_BLK_PARM_REC_LIST,			fl_blk_parm_rec_list;
		FL_BLK_PARM_ARR_LIST,			fl_blk_parm_arr_list;
		FL_BLK_PARM_COL_LIST,			fl_blk_parm_col_list;
    }
}
#endif

#if !_AR5274
/* Unicode string file */
FILE    fl_unicode_string_file
{
    LABEL   "Unicode String File";
    MEMBERS
    {
        FL_UNICODE_STRING,				v_oct_string32 ;
	}
}
#endif

MENU    tc_file_menu
{
    LABEL   "File Test Cases";
    STYLE   MENU;
    ITEMS
    {
        TC_File_001_step_1,
        TC_File_001_step_2,
        TC_File_002_step_1,
        TC_File_002_step_2,
        TC_File_003_step_1,
        TC_File_003_step_2,
        TC_File_004_step_1,
        TC_File_004_step_2,
        TC_File_005_step_1,
        TC_File_005_step_2,
        #if !_AR5572
        TC_File_006_step_1,
        TC_File_006_step_2,
        #endif
        TC_File_012_step_1,
		TC_File_012_step_2
        /* AR3855
        TC_File_013_step_1,
		TC_File_013_step_2,
        TC_File_014_step_1,
		TC_File_014_step_2  */
    }
}

MENU    tc_list_menu
{
    LABEL   "List Test Cases";
    STYLE   MENU;
    ITEMS
    {
        TC_List_001,
        TC_List_002,
        TC_List_003,
        TC_List_004,
        TC_List_005,
        TC_List_006
    }
}      

/*
******************************************************************************
** File test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_001                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that variables can be written and read from a file			     */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_001_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_001 step 1";
	DEFINITION
	{
		long status;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		send_on_exit();

		display_message("Writing variables to file...", ids, dummyIndices, 0);

		display_message("Set float variable = 1", ids, dummyIndices, 0);
		fl_input_file.FL_INPUT_VAR = 1;

		display_message("Set enumerated variable = 2", ids, dummyIndices, 0);
		fl_input_file.FL_INPUT_ENUM = 2;

		display_message("Set bit enumerated variable = 0x0004", ids, dummyIndices, 0);
		fl_input_file.FL_INPUT_BIT_ENUM = 0x0004;

		display_message("Exit the host application, then run TC_FILE_001 step 2.", ids, dummyIndices, 0);
	}
}

METHOD TC_File_001_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_001 step 2";
	DEFINITION
	{
		long status;
		float   flid;
		unsigned long   ulid;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		display_message("Reading variables from file...", ids, dummyIndices, 0);
		
		flid = fl_input_file.FL_INPUT_VAR;
		display_message("Float variable = %[f]{flid}", ids, dummyIndices, 0);

		ulid = fl_input_file.FL_INPUT_ENUM;
		display_message("Enumerated variable = %[d]{ulid}", ids, dummyIndices, 0);

		ulid = fl_input_file.FL_INPUT_BIT_ENUM;
		display_message("Bit enumumerated variable = %[d]{ulid}", ids, dummyIndices, 0);

		if ((fl_input_file.FL_INPUT_VAR == 1) &&
			(fl_input_file.FL_INPUT_ENUM == 2) &&
			(fl_input_file.FL_INPUT_BIT_ENUM == 0x0004))
		{		
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
		}

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_002                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that records can be written and read from a file			     */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_002_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_002 step 1";
	DEFINITION
	{
		long status;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		send_on_exit();

		display_message("Writing record to file...", ids, dummyIndices, 0);

		fl_input_file.FL_INPUT_REC.INPUT_ELEM_1 = 1;
		fl_input_file.FL_INPUT_REC.INPUT_ELEM_2 = 2;

		display_message("Exit the host application, then run TC_FILE_002 step 2.", ids, dummyIndices, 0);
	}
}

METHOD TC_File_002_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_002 step 2";
	DEFINITION
	{
		long status;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		display_message("Reading record from file...", ids, dummyIndices, 0);
		
		if ((fl_input_file.FL_INPUT_REC.INPUT_ELEM_1 == 1) &&
			(fl_input_file.FL_INPUT_REC.INPUT_ELEM_2 == 2))
		{		
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
		}

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_003                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that arrays elements can be written and read from a file		 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_003_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_003 step 1";
	DEFINITION
	{
		long status;
		unsigned long   Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		send_on_exit();

		display_message("Writing to array elements to file...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			fl_input_file.FL_INPUT_ARR[Count] = Count;
		}

		display_message("Exit the host application, then run TC_FILE_003 step 2.", ids, dummyIndices, 0);
	}
}

METHOD TC_File_003_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_003 step 2";
	DEFINITION
	{
		long status;
		unsigned long   Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		display_message("Reading array elements from file...", ids, dummyIndices, 0);
				
		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			if (fl_input_file.FL_INPUT_ARR[Count] != Count)
			{
				get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
                break;
			}
		}

		if (Count == _ARRAY_SIZE+1)
		{
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_004                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that collection entries can be written and read from a file	     */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_004_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_004 step 1";
	DEFINITION
	{
		long status;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		send_on_exit();

		display_message("Writing to file...", ids, dummyIndices, 0);

		fl_input_file.FL_INPUT_COL.IN_COL_REC.INPUT_ELEM_1 = 1;
		fl_input_file.FL_INPUT_COL.IN_COL_REC.INPUT_ELEM_2 = 2;
		
		fl_input_file.FL_INPUT_COL.IN_COL_ARR[1] = 3;
		fl_input_file.FL_INPUT_COL.IN_COL_ARR[2] = 4;

		display_message("Exit the host application, then run TC_FILE_004 step 2.", ids, dummyIndices, 0);
	}
}

METHOD TC_File_004_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_004 step 2";
	DEFINITION
	{
		long status;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];

		display_message("Reading from file...", ids, dummyIndices, 0);
	
		if ((fl_input_file.FL_INPUT_COL.IN_COL_REC.INPUT_ELEM_1 == 1) &&
			(fl_input_file.FL_INPUT_COL.IN_COL_REC.INPUT_ELEM_2 == 2) &&
			(fl_input_file.FL_INPUT_COL.IN_COL_ARR[1] == 3) &&
			(fl_input_file.FL_INPUT_COL.IN_COL_ARR[2] == 4))
		{		
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
		}

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_005                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that list elements can be written and read from a file		     */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_005_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_005 step 1";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		send_on_exit();

		display_message("Writing to file...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_VAR = Count;
			status =  ListInsert(ITEM_ID(fl_input_var_list), Count, ITEM_ID(fl_input_var));
		}

		if (status == 0 && fl_input_file.FL_INPUT_VAR_LIST.COUNT == _ARRAY_SIZE)
		{	
			display_message("Exit the host application, then run TC_FILE_005 step 2.", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Failed:  File access failed due to ListInsert error", ids, dummyIndices, 0);			
		}
	}
}

METHOD TC_File_005_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_005 step 2";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		display_message("Reading from file...", ids, dummyIndices, 0);
		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{			
			if (fl_input_file.FL_INPUT_VAR_LIST[Count] != Count)
			{
				get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
				break;
			}
		}
		if (Count == _ARRAY_SIZE+1)
		{
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}						

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
        
		while (fl_input_var_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);	
		}  
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_006                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that 0x10000 list elements can be written and read from a file	 */
/*                                                                           */
/*****************************************************************************/
#if !_AR5572
METHOD TC_File_006_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_006 step 1";
	DEFINITION
	{
		long status;
		unsigned long Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		send_on_exit();

		display_message("Writing to file...", ids, dummyIndices, 0);

		for (Count = 1; Count <= 0x10000; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_VAR = Count;
			status =  ListInsert(ITEM_ID(fl_input_var_list), Count, ITEM_ID(fl_input_var));
		}

		if (status == 0 && fl_input_file.FL_INPUT_VAR_LIST.COUNT == 0x10000)
		{	
			display_message("Exit the host application, then run TC_FILE_006 step 2.", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Failed:  File access failed due to ListInsert error", ids, dummyIndices, 0);			
		}
	}
}

METHOD TC_File_006_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_006 step 2";
	DEFINITION
	{
		long status;
		unsigned long Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		display_message("Reading from file...", ids, dummyIndices, 0);
		for (Count = 1; Count < 0x10000; Count++)
		{			
			if (fl_input_file.FL_INPUT_VAR_LIST[Count] != Count)
			{
				get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
				break;
			}
		}
		if (Count == 0x10000)
		{
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}						
	
        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
        
		while (fl_input_var_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);	
		}  
    }
}
#endif

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_0012                                                            */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that file exists												 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_012_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_012 step 1";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		send_on_exit();

		display_message("Creating file...", ids, dummyIndices, 0);

        /* put values in items */
		LOCAL_PARAM.LOC_INPUT_VAR = 1;
		LOCAL_PARAM.LOC_INPUT_ENUM = 1;
		LOCAL_PARAM.LOC_INPUT_BIT_ENUM = 0x01;
        #if _AR2557
        LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_1 = 1;
		LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_2 = 1;
        for(Count=1;Count <= _ARRAY_SIZE;Count++)
            LOCAL_PARAM.LOC_INPUT_ARR[Count]=Count;
        #endif

        /* insert one element in each list */
        status=ListInsert(ITEM_ID(fl_input_var_list), 1, ITEM_ID(fl_input_var));
        status=ListInsert(ITEM_ID(fl_input_enum_var_list), 1, ITEM_ID(fl_input_enum_var));
        status=ListInsert(ITEM_ID(fl_input_bit_enum_var_list), 1, ITEM_ID(fl_input_bit_enum_var));
        status=ListInsert(ITEM_ID(fl_input_rec_list), 1, ITEM_ID(fl_input_rec));
        status=ListInsert(ITEM_ID(fl_input_arr_list), 1, ITEM_ID(fl_input_arr));
        status=ListInsert(ITEM_ID(fl_input_col_list), 1, ITEM_ID(fl_input_collection));

		display_message("Now run TC_FILE_012 step 2.", ids, dummyIndices, 0);
    }
}
        
METHOD TC_File_012_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_012 step 2";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;
		unsigned long	failures;

		display_message("Reading from file...\n", ids, dummyIndices, 0);

		failures = 0;
		if (LOCAL_PARAM.LOC_INPUT_VAR != 1)
			failures++;

		if (LOCAL_PARAM.LOC_INPUT_ENUM != 1)
			failures++;

		if (LOCAL_PARAM.LOC_INPUT_BIT_ENUM != 0x01)
			failures++;

        #if _AR2557
        if ((LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_1 != 1) ||
		    (LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_2 != 1))
				failures++
				;
        for(Count=1;Count <= _ARRAY_SIZE;Count++)
            if (LOCAL_PARAM.LOC_INPUT_ARR[Count] != Count)
				failures++;
		#endif


		if (failures != 0)
		{
			get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test Passed !!!!:  File access succeeded", ids, dummyIndices, 0);
		}						

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;

        /* clear values in items */
		LOCAL_PARAM.LOC_INPUT_VAR = 0;
		LOCAL_PARAM.LOC_INPUT_ENUM = 0;
		LOCAL_PARAM.LOC_INPUT_BIT_ENUM = 0x00;
        #if _AR2557
        LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_1 = 0;
		LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_2 = 0;
        for(Count=1;Count <= _ARRAY_SIZE;Count++)
            LOCAL_PARAM.LOC_INPUT_ARR[Count]=0;
        #endif

        /* delete element in each list */
        status=ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);
        status=ListDeleteElementAt(ITEM_ID(fl_input_enum_var_list), 1);
        status=ListDeleteElementAt(ITEM_ID(fl_input_bit_enum_var_list), 1);
        status=ListDeleteElementAt(ITEM_ID(fl_input_rec_list), 1);
        status=ListDeleteElementAt(ITEM_ID(fl_input_arr_list), 1);
        status=ListDeleteElementAt(ITEM_ID(fl_input_col_list), 1);
    }
}


/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_013                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that Unicode strings can be written to and read from a file      */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_013_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_013 step 1";
	DEFINITION
	{
		long status;
		float Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		save_on_exit();

		status = edit_device_value ("Enter a non-ASCII Unicode string for storage into the file", 
				ids, dummyIndices, 0, 
				ITEM_ID(PARAM.V_OCTETSTRING), 0);
		if (status == 0)
		{	
			display_message("Exit the host application, then run TC_FILE_013 step 2.", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test failed:  edit_device_value failed for unknown reason", ids, dummyIndices, 0);			
		}
	}
}

METHOD TC_File_013_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_013 step 2";
	DEFINITION
	{
		long status;
		float Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		display_message("Reading from file...", ids, dummyIndices, 0);
		ids[0] = ITEM_ID(PARAM.V_OCTETSTRING);
		dummyIndices[0] = 0;
		get_acknowledgement("String read from file was: %{0}", ids, dummyIndices, 1);
		get_acknowledgement("If this is not exactly the string that you entered in step 1, then the result is FAIL.  Otherwise, the result is PASS.",
			ids, dummyIndices, 0);
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_File_014                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   File                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that nested LISTs can be written to and read from a file         */
/*                                                                           */
/*****************************************************************************/
METHOD TC_File_014_step_1
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_014 step 1";
	DEFINITION
	{
		long status;
		float Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;
		int failures;

		save_on_exit();
		failures = 0;

		/* Remove all elements in the inner list */
		while ((fl_inner_list.COUNT > 0) && (!failures))
		{
			status = ListDeleteElementAt(ITEM_ID(fl_inner_list), 1);
			if (status != 0)
			{
				display_message("ListDeleteElementAt() call for fl_inner_list failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}
		/* Remove all elements in the outer list */
		while ((fl_inner_list.COUNT > 0) && (!failures))
		{
			status = ListDeleteElementAt(ITEM_ID(fl_outer_list), 1);
			if (status != 0)
			{
				display_message("ListDeleteElementAt() call for fl_outer_list failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}

		if (!failures)
		{
			/* Create two inner list elements : 11  12  */
			LOCAL_PARAM.LOC_INPUT_VAR = 11;
			status = ListInsert(ITEM_ID(fl_inner_list), 1, ITEM_ID(fl_input_var));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_inner_list first element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			LOCAL_PARAM.LOC_INPUT_VAR = 12;
			status = ListInsert(ITEM_ID(fl_inner_list), 2, ITEM_ID(fl_input_var));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_inner_list second element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}

		/* Insert at the head of the outer list : Outer list contains (11 12)  */
		if (!failures)
		{
			status = ListInsert(ITEM_ID(fl_outer_list), 1, ITEM_ID(fl_inner_list));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_outer_list first element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}

		/* Remove all elements in the inner list */
		while ((fl_inner_list.COUNT > 0) && (!failures))
		{
			status = ListDeleteElementAt(ITEM_ID(fl_inner_list), 1);
			if (status != 0)
			{
				display_message("ListDeleteElementAt() call for fl_inner_list failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}

		if (!failures)
		{
			/* Create two inner list elements : 21  22  */
			LOCAL_PARAM.LOC_INPUT_VAR = 21;
			status = ListInsert(ITEM_ID(fl_inner_list), 1, ITEM_ID(fl_input_var));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_inner_list first element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			LOCAL_PARAM.LOC_INPUT_VAR = 22;
			status = ListInsert(ITEM_ID(fl_inner_list), 2, ITEM_ID(fl_input_var));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_inner_list second element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}
		/* Insert at the end of the outer list : Outer list contains (11 12) (21 22)  */
		if (!failures)
		{
			status = ListInsert(ITEM_ID(fl_outer_list), 2, ITEM_ID(fl_inner_list));
			if (status != 0)
			{
				display_message("ListInsert() call for fl_outer_list second element failed with result %[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
		}

		/* If all that worked, this step is a success */
		if (failures == 0)
		{	
			display_message("This step passed.  Exit the host application, then run TC_FILE_014 step 2.", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test failed: The nested lists could not be created.", ids, dummyIndices, 0);			
		}
	}
}

LIST fl_inner_list
{
	LABEL "TC_File_014 inner list";
	HELP "Inner list used in nested list testing";
	TYPE  fl_input_var;  /*	LOCAL_PARAM.LOC_INPUT_VAR in the DataTypeTB block */
}

LIST fl_outer_list
{
	LABEL "TC_File_014 outer list";
	HELP "Outer list used in nested list testing";
	TYPE fl_inner_list; 
}

FILE fl_nested_list_file
{
	LABEL "Nested List File";
	HELP "File used to store a nested list";
	MEMBERS
	{
		OUTER_LIST, fl_outer_list;
	}
}

METHOD TC_File_014_step_2
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_File_014 step 2";
	DEFINITION
	{
		long status;
		float Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;
		int failures;

		failures = 0;

		/* Outer list should contain (11 12) (21 22)  */
		if (fl_outer_list.COUNT != 2)
		{
			display_message("fl_outer_list does not contain 2 elements.", ids, dummyIndices, 0);
			failures++;
		}

		if (!failures)
		{
			/* First element should be (11 12) */
			/* Look for the 11 */
			status = get_signed_lelem2(ITEM_ID(fl_outer_list), 1, ITEM_ID(fl_inner_list), 1, 
									ITEM_ID(fl_input_var), 0);
			if (status != 0)
			{
				display_message("Failed to access first element of first fl_inner_list, status=%[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			if (LOCAL_PARAM.LOC_INPUT_VAR != 11)
			{
				display_message("First element of first fl_inner_list was wrong.", ids, dummyIndices, 0);
				failures++;
			}
		}
		if (!failures)
		{
			/* First element should be (11 12) */
			/* Look for the 12 */
			status = get_signed_lelem2(ITEM_ID(fl_outer_list), 1, ITEM_ID(fl_inner_list), 2, 
									ITEM_ID(fl_input_var), 0);
			if (status != 0)
			{
				display_message("Failed to access second element of first fl_inner_list, status=%[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			if (LOCAL_PARAM.LOC_INPUT_VAR != 12)
			{
				display_message("Second element of first fl_inner_list was wrong.", ids, dummyIndices, 0);
				failures++;
			}
		}
		if (!failures)
		{
			/* First element should be (21 22) */
			/* Look for the 21 */
			status = get_signed_lelem2(ITEM_ID(fl_outer_list), 2, ITEM_ID(fl_inner_list), 1, 
									ITEM_ID(fl_input_var), 0);
			if (status != 0)
			{
				display_message("Failed to access first element of second fl_inner_list, status=%[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			if (LOCAL_PARAM.LOC_INPUT_VAR != 21)
			{
				display_message("First element of second fl_inner_list was wrong.", ids, dummyIndices, 0);
				failures++;
			}
		}
		if (!failures)
		{
			/* First element should be (21 22) */
			/* Look for the 22 */
			status = get_signed_lelem2(ITEM_ID(fl_outer_list), 2, ITEM_ID(fl_inner_list), 2, 
									ITEM_ID(fl_input_var), 0);
			if (status != 0)
			{
				display_message("Failed to access second element of second fl_inner_list, status=%[d]{status}", ids, dummyIndices, 0);
				failures++;
			}
			if (LOCAL_PARAM.LOC_INPUT_VAR != 22)
			{
				display_message("Second element of second fl_inner_list was wrong.", ids, dummyIndices, 0);
				failures++;
			}
		}

		if (!failures)
		{
			get_acknowledgement("Test case PASSED.", ids, dummyIndices, 0);
		}
		else
		{
			get_acknowledgement("Test case FAILED.", ids, dummyIndices, 0);
		}
	}
}


/*
******************************************************************************
** List test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_001                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a variable entry can be inserted into a list,               */
/*   read back from the list, and then deleted from the list.				 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_001 
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_001";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		display_message("Writing to List...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_VAR = Count;
			status=ListInsert(ITEM_ID(fl_input_var_list), Count, ITEM_ID(fl_input_var));
		}

		if (status == 0 && fl_input_var_list.COUNT == _ARRAY_SIZE)
		{	
			display_message("Reading from list...", ids, dummyIndices, 0);
			for (Count = 1; Count <= _ARRAY_SIZE; Count++)
			{			
				if (fl_input_file.FL_INPUT_VAR_LIST[Count] != Count)
				{
					get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
					break;
				}
			}
			if (Count == _ARRAY_SIZE+1)
			{
				get_acknowledgement("Test Passed !!!!:  List access succeeded", ids, dummyIndices, 0);
			}						
		}
		else
		{
			get_acknowledgement("Test Failed:  List access failed due to ListInsert error", ids, dummyIndices, 0);			
		}

		while (fl_input_var_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);	
		} 

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;

	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_002                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a record entry can be inserted into a list,                 */
/*   read back from the list, and then deleted from the list.				 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_002
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_002";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

        #if _AR2557
		display_message("Writing to List...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_REC.INPUT_ELEM_1 = Count;
			status=ListInsert(ITEM_ID(fl_input_rec_list), Count, ITEM_ID(fl_input_rec));
		}

		if (status == 0 && fl_input_rec_list.COUNT == _ARRAY_SIZE)
		{	
			display_message("Reading from list...", ids, dummyIndices, 0);
			for (Count = 1; Count <= _ARRAY_SIZE; Count++)
			{			
				if (fl_input_file.FL_INPUT_REC_LIST[Count].INPUT_ELEM_1 != Count)
				{
					get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
					break;
				}
			}
			if (Count == _ARRAY_SIZE+1)
			{
				get_acknowledgement("Test Passed !!!!:  List access succeeded", ids, dummyIndices, 0);
			}						
		}
		else
		{
			get_acknowledgement("Test Failed:  List access failed due to ListInsert error", ids, dummyIndices, 0);			
		}

		while (fl_input_rec_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_rec_list), 1);	
		} 

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
        #else
        display_message(_TC_NO_SUPORT_MSG, ids, dummyIndices, 0);
        #endif
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_003                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that an array entry can be inserted into a list,                 */
/*   read back from the list, and then deleted from the list.				 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_003
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_003";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		#if _AR2557
		display_message("Writing to List...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_ARR[1] = Count;
			status=ListInsert(ITEM_ID(fl_input_arr_list), Count, ITEM_ID(fl_input_arr));
		}

		if (status == 0 && fl_input_arr_list.COUNT == _ARRAY_SIZE)
		{	
			display_message("Reading from list...", ids, dummyIndices, 0);
			for (Count = 1; Count <= _ARRAY_SIZE; Count++)
			{			
				if (fl_input_file.FL_INPUT_ARR_LIST[Count][1] != Count)
				{
					get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
					break;
				}
			}
			if (Count == _ARRAY_SIZE+1)
			{
				get_acknowledgement("Test Passed !!!!:  List access succeeded", ids, dummyIndices, 0);
			}						
		}
		else
		{
			get_acknowledgement("Test Failed:  List access failed due to ListInsert error", ids, dummyIndices, 0);			
		}

		while (fl_input_arr_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_arr_list), 1);	
		} 

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
        #else
        display_message(_TC_NO_SUPORT_MSG, ids, dummyIndices, 0);
        #endif
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_004                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a collection entry can be inserted into a list,             */
/*   read back from the list, and then deleted from the list.				 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_004
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_004";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		#if _AR2557
		display_message("Writing to List...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_ARR[1] = Count;
			status=ListInsert(ITEM_ID(fl_input_col_list), Count, ITEM_ID(fl_input_collection));
		}

		if (status == 0 && fl_input_col_list.COUNT == _ARRAY_SIZE)
		{	
			display_message("Reading from list...", ids, dummyIndices, 0);
			for (Count = 1; Count <= _ARRAY_SIZE; Count++)
			{			
				if (fl_input_file.FL_INPUT_COL_LIST[Count].IN_COL_ARR[1] != Count)
				{
					get_acknowledgement("Test Failed:  Values read did not match what was written", ids, dummyIndices, 0);
					break;
				}
			}
			if (Count == _ARRAY_SIZE+1)
			{
				get_acknowledgement("Test Passed !!!!:  List access succeeded", ids, dummyIndices, 0);
			}						
		}
		else
		{
			get_acknowledgement("Test Failed:  List access failed due to ListInsert error", ids, dummyIndices, 0);			
		}

		while (fl_input_col_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_col_list), 1);	
		} 

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
        #else
        display_message(_TC_NO_SUPORT_MSG, ids, dummyIndices, 0);
        #endif
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_005                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a list is limited by CAPACITY				                 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_005 
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_005";
	DEFINITION
	{
		long status;
		float   Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;
		int	passed ;

        passed = 1;
		display_message("Writing to List...", ids, dummyIndices, 0);

		/* Inserting these 3 elements should succeed and fill up the list */
		for (Count = 1; Count <= 3; Count++)
		{
			LOCAL_PARAM.LOC_INPUT_VAR = Count;
			status=ListInsert(ITEM_ID(fl_input_var_list_with_cap), 1, ITEM_ID(fl_input_var));
			if (status != 0)
			{
				display_message("Error: Unable to insert a valid element", ids, dummyIndices, 0);
				passed = 0;
				break;
			}
			display_message("Inserted element %d{Count}", ids, dummyIndices, 0);
		}
		if (passed)
		{
			/* Now attempt to insert the 4th element: should fail due to a CAPACITY of 3 on the list */
			LOCAL_PARAM.LOC_INPUT_VAR = Count;
			status=ListInsert(ITEM_ID(fl_input_var_list_with_cap), 1, ITEM_ID(fl_input_var));
			if (status == 0)
			{
				display_message("Error: Test was able to insert beyond list capacity", ids, dummyIndices, 0);
				passed = 0;
			}
		}
		/* Clean up the list */
		while (fl_input_var_list_with_cap.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list_with_cap), 1);	
		}
		if (passed) 
			get_acknowledgement("Test Passed !!!!:  List size was properly limited.", ids, dummyIndices, 0);
		else
			get_acknowledgement("Test failed.", ids, dummyIndices, 0);
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_List_006                                                             */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   List                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a list updates the LIST.COUNT				                 */
/*                                                                           */
/*****************************************************************************/
METHOD TC_List_006 
{
	CLASS 	INPUT & OPERATE;
	LABEL 	"TC_List_006";
	DEFINITION
	{
		long status;
		unsigned int Count;
		unsigned long   id;
		unsigned long	ids[1];
		unsigned long	dummyIndices[1];
		unsigned long 	size;

		display_message("Clearing out any existing list entries...", ids, dummyIndices, 0);

		while (fl_input_var_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);	
		} 

		display_message("Writing to List...", ids, dummyIndices, 0);

		for (Count = 1; Count <= _ARRAY_SIZE; Count++)
		{
			status=ListInsert(ITEM_ID(fl_input_var_list), Count, ITEM_ID(fl_input_var));
		}

		if (status == 0 && fl_input_var_list.COUNT == _ARRAY_SIZE)
		{	
			get_acknowledgement("Test Passed !!!!:  list.COUNT was correct", ids, dummyIndices, 0);	
		}
		else
		{
			get_acknowledgement("Test Failed:  list.COUNT was wrong", ids, dummyIndices, 0);							
		}

		while (fl_input_var_list.COUNT > 0)
		{
			status = ListDeleteElementAt(ITEM_ID(fl_input_var_list), 1);	
		} 

        get_acknowledgement ( "Continue...\n\n", ids, dummyIndices, 0 ) ;
	}
}

/***********************************************************************/

#endif

