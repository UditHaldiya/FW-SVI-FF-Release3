/*****************************************************************************/
/* 1000_Test_Case_Menu.ddl                                                   */
/*                                                                           */
/*   This file contains DDL for the menu test cases.                         */
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
** Common constructs for menu test cases                                                                
******************************************************************************
*/

MENU    range_values
{
 	LABEL   "Range Values";
	STYLE   GROUP;
	ITEMS
	{
		upper_range_value,  /* variable */
		lower_range_value   /* variable */
	}
}

MENU    sensor_limits
{
 	LABEL   "Sensor Limits";
	STYLE   GROUP;
	ITEMS
	{
	    upper_sensor_limit, /* variable */
		lower_sensor_limit  /* variable */
	}
}

MENU    sensor_limits_group_not_defined
{
 	LABEL   "Sensor Limits - No Group";
	ITEMS
	{
		upper_sensor_limit, /* variable */
		lower_sensor_limit  /* variable */
	}
}

WAVEFORM    menuTestWaveform1
{
	LABEL	"Menu Tests: Waveform 1";
	HELP	"Waveform Help:";
	TYPE YT
	{
		X_INITIAL 	0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_1  }
	}
}

GRAPH   menuTestGraph1
{
	LABEL	"Menu Tests: Graph 1";
	HELP    "Graph Help:";
	MEMBERS
	{
		MENU_TEST_WAVEFORM_1, menuTestWaveform1;		
	}

}

SOURCE 	menuTestSrc1
{
	MEMBERS
	{
		SSAMPLE, PARAM.TEST_FL_VAL_1;
	}
}

CHART 	menuTestChart1
{
	LABEL	"Menu Tests: Chart 1";
	HELP	"Chart Help: ";
	MEMBERS
	{
		MENU_TEST_SRC, menuTestSrc1;		
	}

}

MENU	menuTestWindow1
{
	LABEL	"Menu Test Window 1";
	STYLE 	WINDOW;
	ITEMS
	{
		"Menu Test Window 1 displayed properly!"
	}
}

MENU	menuTestDialog1
{
	LABEL	"Menu Test Dialog 1";
	STYLE 	DIALOG;
	ITEMS
	{
		"Menu Test Dialog 1 displayed properly!"
	}
}

METHOD menuTestMethod1
{
	CLASS INPUT;
	LABEL "Menu Test Method 1";
	DEFINITION
	{
		float element;
		long i;
		long status;
		unsigned long 	ids[1];
		unsigned long 	indices[1];
		
		send_on_exit();
		display_message("Menu Test Method 1 worked properly.\n",ids, indices,0);
	}
}

GRID	menuTestGrid1
{
	LABEL	"MenuTest Grid 1";
	VECTORS	
	{
		{ "Values", PARAM.TEST_Y_ARRAY_1 }
	}
	HANDLING 	READ & WRITE;
	ORIENTATION	HORIZONTAL;	
}

IMAGE 	menuTestImage1
{
	LABEL	"Menu Test Image 1";
	PATH	"ff_jpg.jpg";
}

#endif /* _DD5_PROFILE */

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_000                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a menu can be displayed.                                   */
/*                                                                           */
/*****************************************************************************/
#ifdef V4
MENU	tc_mn_000_menu
{
	LABEL	"TC_MN_000 Menu";
	ITEMS
	{
		PARAM.ST_REV
    }
}
#endif

#if _DD5_PROFILE
/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_001                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a window can be displayed with multiple pages with          */
/*   constructs.                                                             */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_001_window
{
	LABEL	"TC_MN_001 Window";
    STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_001_page1,
		tc_mn_001_page2,
		tc_mn_001_page3,
		tc_mn_001_page4,
		tc_mn_001_page5
    }
}

MENU tc_mn_001_page1
{
 	LABEL "Page 1 Label";
	STYLE PAGE;
	ITEMS
	{
		__st_rev,           /* variable */
		ROWBREAK,
		range_values,       /* group */
		COLUMNBREAK,
		sensor_limits,      /* group */
		ROWBREAK, 
		__st_rev            /* variable */
	}
}

MENU tc_mn_001_page2
{
 	LABEL "Page 2 Label";
	STYLE PAGE;
	ITEMS
	{
		menuTestGraph1           /* graph */
	}
}

MENU tc_mn_001_page3
{
 	LABEL "Page 3 Label";
	STYLE PAGE;
	ITEMS
	{
		menuTestChart1           /* chart */
	}
}

MENU tc_mn_001_page4
{
 	LABEL "Page 4 Label";
	STYLE PAGE;
	ITEMS
	{
		menuTestWindow1,           /* Window */
		menuTestDialog1,           /* Dialog Box */
		menuTestMethod1,           /* Method */
		menuTestGrid1              /* Grid */
	}
}

MENU tc_mn_001_page5
{
 	LABEL "Page 5 Label";
	STYLE PAGE;
	ITEMS
	{
		"Static Text Displays Properly",
		menuTestImage1             /* Image */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_002                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that row and column breaks are ignored between pages. Also       */
/*   that a menu with no type is displayed as a group.                       */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_002_window
{
	LABEL	"TC_MN_002 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_002_page1,
		ROWBREAK,
		tc_mn_002_page2,
		COLUMNBREAK,
		tc_mn_002_page3
    }
}

MENU tc_mn_002_page1
{
 	LABEL "Page 1 Label";
	STYLE PAGE;
	ITEMS
	{
		"The following should be in a group.",
		sensor_limits_group_not_defined
	}
}

MENU tc_mn_002_page2
{
 	LABEL "Page 2 Label";
	STYLE PAGE;
	ITEMS
	{
		"Page 2",
		menuTestImage1             /* Image */
	}
}

MENU tc_mn_002_page3
{
 	LABEL "Page 3 Label";
	STYLE PAGE;
	ITEMS
	{
		"Page 3",
		menuTestImage1             /* Image */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_003                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a group can be displayed with the different constructs.     */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_003_window
{
	LABEL	"TC_MN_003 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_003_win1,
		tc_mn_003_win2,
		tc_mn_003_win3,
		tc_mn_003_win4,
		tc_mn_003_win5
    }
}

MENU tc_mn_003_win1
{
 	LABEL "Window 1";
	STYLE WINDOW;
	ITEMS
	{
		tc_mn_003_group1     /* group */
	}
}

MENU tc_mn_003_group1
{
 	LABEL "Group 1";
	STYLE GROUP;
	ITEMS
	{
		__st_rev,           /* variable */
		ROWBREAK,
		sensor_limits,      /* group */
		COLUMNBREAK,
		sensor_limits_group_not_defined,       /* group */
		ROWBREAK, 
		__st_rev            /* variable */
	}
}

MENU tc_mn_003_win2
{
 	LABEL "Window 2";
	STYLE WINDOW;
	ITEMS
	{
		tc_mn_003_group2         /* group */
	}
}

MENU tc_mn_003_group2
{
 	LABEL "Group 2";
	STYLE GROUP;
	ITEMS
	{
		"Graph",
		menuTestGraph1           /* graph */
	}
}

MENU tc_mn_003_win3
{
 	LABEL "Window 3";
	STYLE WINDOW;
	ITEMS
	{
		"Chart",
		tc_mn_003_group3           /* group */
	}
}

MENU tc_mn_003_group3
{
 	LABEL "Group 3";
	STYLE GROUP;
	ITEMS
	{
		menuTestChart1           /* chart */
	}
}

MENU tc_mn_003_win4
{
 	LABEL "Window 4";
	STYLE WINDOW;
	ITEMS
	{
		tc_mn_003_group4           /* Group */
	}
}

MENU tc_mn_003_group4
{
 	LABEL "Group 4";
	STYLE GROUP;
	ITEMS
	{
		menuTestWindow1,           /* Window */
		menuTestDialog1,           /* Dialog Box */
		menuTestMethod1,           /* Method */
		menuTestGrid1              /* Grid */
	}
}

MENU tc_mn_003_win5
{
 	LABEL "Window 5";
	STYLE WINDOW;
	ITEMS
	{
		tc_mn_003_group5             /* Group */
	}
}

MENU tc_mn_003_group5
{
 	LABEL "Group 5";
	STYLE GROUP;
	ITEMS
	{
		"Static Text Displays Properly",
		menuTestImage1             /* Image */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_004                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a undefined MENU is displayed as a dialog if the      .     */
/*   grandparent and the parent are both groups.                             */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_004_window
{
	LABEL	"TC_MN_004 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_004_group1
	}
}

MENU tc_mn_004_win1
{
 	LABEL "Window 1";
	STYLE WINDOW;
	ITEMS
	{
		tc_mn_004_group1     /* group */
	}
}

MENU tc_mn_004_group1
{
 	LABEL "Grandparent Group";
	STYLE GROUP;
	ITEMS
	{
		tc_mn_004_group2      /* group */
	}
}

MENU tc_mn_004_group2
{
 	LABEL "Parent Group";
	STYLE GROUP;
	ITEMS
	{
		sensor_limits_group_not_defined      /* should be a dialog */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_005                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a window can be displayed with multiple dialogs with        */
/*   constructs.                                                             */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_005_window
{
	LABEL	"TC_MN_005 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_005_diag1,
		tc_mn_005_diag2,
		tc_mn_005_diag3,
		tc_mn_005_diag4,
		tc_mn_005_diag5
    }
}

MENU tc_mn_005_diag1
{
 	LABEL "Dialog 1";
	STYLE DIALOG;
	ITEMS
	{
		__st_rev,           /* variable */
		ROWBREAK,
		range_values,       /* group */
		COLUMNBREAK,
		sensor_limits,      /* group */
		ROWBREAK, 
		__st_rev            /* variable */
	}
}

MENU tc_mn_005_diag2
{
 	LABEL "Dialog 2";
	STYLE DIALOG;
	ITEMS
	{
		menuTestGraph1           /* graph */
	}
}

MENU tc_mn_005_diag3
{
 	LABEL "Dialog 3";
	STYLE DIALOG;
	ITEMS
	{
		menuTestChart1           /* chart */
	}
}

MENU tc_mn_005_diag4
{
 	LABEL "Dialog 4";
	STYLE DIALOG;
	ITEMS
	{
		menuTestWindow1,           /* Window */
		menuTestDialog1,           /* Dialog Box */
		menuTestMethod1,           /* Method */
		menuTestGrid1              /* Grid */
	}
}

MENU tc_mn_005_diag5
{
 	LABEL "Dialog 5";
	STYLE DIALOG;
	ITEMS
	{
		"Static Text Displays Properly",
		menuTestImage1             /* Image */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_006                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a undefined menu opens as a page on a dialog. Also verify   */
/*   that a dialog opens on top and is modal.                                */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_006_window
{
	LABEL	"TC_MN_006 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_006_diag1
    }
}

MENU tc_mn_006_diag1
{
 	LABEL "Dialog Label 1";
	STYLE DIALOG;
	ITEMS
	{
		sensor_limits_group_not_defined, /* undefined */
		tc_mn_006_diag2        /* dialog */
	}
}

MENU tc_mn_006_diag2
{
 	LABEL "Dialog Label 2";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog 2 should be modal and on top" /* text */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_007                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a window can be displayed with multiple pages with          */
/*   constructs.                                                             */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_007_window
{
	LABEL	"TC_MN_007 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_007_win1,
		tc_mn_007_win2,
		tc_mn_007_win3,
		tc_mn_007_win4,
		tc_mn_007_win5
    }
}

MENU tc_mn_007_win1
{
 	LABEL "Window 1";
	STYLE WINDOW;
	ITEMS
	{
		__st_rev,            /* variable */
		ROWBREAK,
		sensor_limits,       /* group */
		COLUMNBREAK,
		sensor_limits_group_not_defined,      /* undefined menu */
		ROWBREAK, 
		__st_rev             /* variable */
	}
}

MENU tc_mn_007_win2
{
 	LABEL "Window 2";
	STYLE WINDOW;
	ITEMS
	{
		menuTestGraph1           /* graph */
	}
}

MENU tc_mn_007_win3
{
 	LABEL "Window 3";
	STYLE WINDOW;
	ITEMS
	{
		menuTestChart1           /* chart */
	}
}

MENU tc_mn_007_win4
{
 	LABEL "Window 4";
	STYLE WINDOW;
	ITEMS
	{
		menuTestWindow1,           /* Window */
		menuTestDialog1,           /* Dialog Box */
		menuTestMethod1,           /* Method */
		menuTestGrid1              /* Grid */
	}
}

MENU tc_mn_007_win5
{
 	LABEL "Window 5";
	STYLE WINDOW;
	ITEMS
	{
		"Static Text Displays Properly",
		menuTestImage1             /* Image */
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_008                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a undefined menu opens as a menu or a dialog on a menu,     */
/*   depending if there are variables in the menu.                           */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_008_menu
{
	LABEL	"TC_MN_008 Menu";
	STYLE 	MENU;
	ITEMS
	{
		tc_mn_008_menu1,  /* Menu with variables */
		tc_mn_008_menu2   /* Menu with no variables */
	}
}

MENU tc_mn_008_menu1
{
 	LABEL "Dialog - with variables";
	ITEMS
	{
		__st_rev,            /* variable */
		ROWBREAK,
		sensor_limits,       /* group */
		COLUMNBREAK,
		sensor_limits_group_not_defined,      /* undefined menu */
		ROWBREAK, 
		__st_rev             /* variable */
	}
}

MENU tc_mn_008_menu2
{
 	LABEL "Menu - no variables";
	ITEMS
	{
		menuTestWindow1,
		menuTestDialog1
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_009                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that dialogs can be stacked 5 deep.                              */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_009_window
{
	LABEL	"TC_MN_009 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		"Top Level Window",
		tc_mn_009_diag1
    }
}

MENU tc_mn_009_diag1
{
 	LABEL "Dialog 1";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog Level 1",
		tc_mn_009_diag2
	}
}

MENU tc_mn_009_diag2
{
 	LABEL "Dialog 2";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog Level 2",
		tc_mn_009_diag3
	}
}

MENU tc_mn_009_diag3
{
 	LABEL "Dialog 3";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog Level 3",
		tc_mn_009_diag4
	}
}

MENU tc_mn_009_diag4
{
 	LABEL "Dialog 4";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog Level 4",
		tc_mn_009_diag5
	}
}

MENU tc_mn_009_diag5
{
 	LABEL "Dialog 5";
	STYLE DIALOG;
	ITEMS
	{
		"Dialog Level 5. Final dialog."
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_010                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a window can display 5 columns and 7 rows.                  */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_010_window
{
	LABEL	"TC_MN_010 Window";
	STYLE 	WINDOW;
	ITEMS
	{
	    _TC_MN_5_BY_7_ITEMS	
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_011                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a page can display 5 columns and 7 rows.                    */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_011_window
{
	LABEL	"TC_MN_011 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_011_page1
	}
}

MENU tc_mn_011_page1
{
 	LABEL "Page 1";
	STYLE PAGE;
	ITEMS
	{
		_TC_MN_5_BY_7_ITEMS
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_012                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a window can display 10 pages.                              */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_012_window
{
	LABEL	"TC_MN_012 Window";
	STYLE 	WINDOW;
	ITEMS
	{
		tc_mn_012_page1,
		tc_mn_012_page2,
		tc_mn_012_page3,
		tc_mn_012_page4,
		tc_mn_012_page5,
		tc_mn_012_page6,
		tc_mn_012_page7,
		tc_mn_012_page8,
		tc_mn_012_page9,
		tc_mn_012_page10
	}
}


MENU tc_mn_012_page1
{
 	LABEL "P1";
	STYLE PAGE;
	ITEMS
	{
		"Page 1"
	}
}

MENU tc_mn_012_page2
{
 	LABEL "P2";
	STYLE PAGE;
	ITEMS
	{
		"Page 2"
	}
}

MENU tc_mn_012_page3
{
 	LABEL "P3";
	STYLE PAGE;
	ITEMS
	{
		"Page 3"
	}
}

MENU tc_mn_012_page4
{
 	LABEL "P4";
	STYLE PAGE;
	ITEMS
	{
		"Page 4"
	}
}

MENU tc_mn_012_page5
{
 	LABEL "P5";
	STYLE PAGE;
	ITEMS
	{
		"Page 5"
	}
}

MENU tc_mn_012_page6
{
 	LABEL "P6";
	STYLE PAGE;
	ITEMS
	{
		"Page 6"
	}
}

MENU tc_mn_012_page7
{
 	LABEL "P7";
	STYLE PAGE;
	ITEMS
	{
		"Page 7"
	}
}

MENU tc_mn_012_page8
{
 	LABEL "P8";
	STYLE PAGE;
	ITEMS
	{
		"Page 8"
	}
}

MENU tc_mn_012_page9
{
 	LABEL "P9";
	STYLE PAGE;
	ITEMS
	{
		"Page 9"
	}
}

MENU tc_mn_012_page10
{
 	LABEL "P10";
	STYLE PAGE;
	ITEMS
	{
		"Page 10"
	}
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_MN_013                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Menu                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a menu can be stacked 8 deep.                               */
/*                                                                           */
/*****************************************************************************/
MENU	tc_mn_013_menu
{
	LABEL	"TC_MN_013 Menu";
	STYLE 	MENU;
	ITEMS
	{
		tc_mn_013_menu1
    }
}

MENU tc_mn_013_menu1
{
 	LABEL "Level 1";
	ITEMS
	{
		tc_mn_013_menu2
	}
}

MENU tc_mn_013_menu2
{
 	LABEL "Level 2";
	ITEMS
	{
		tc_mn_013_menu3
	}
}

MENU tc_mn_013_menu3
{
 	LABEL "Level 3";
	ITEMS
	{
		tc_mn_013_menu4
	}
}

MENU tc_mn_013_menu4
{
 	LABEL "Level 4";
	ITEMS
	{
		tc_mn_013_menu5
	}
}

MENU tc_mn_013_menu5
{
 	LABEL "Level 5";
	ITEMS
	{
		tc_mn_013_menu6
	}
}

MENU tc_mn_013_menu6
{
 	LABEL "Level 6";
	ITEMS
	{
		tc_mn_013_menu7
	}
}

MENU tc_mn_013_menu7
{
 	LABEL "Level 7";
	ITEMS
	{
		tc_mn_013_menu8
	}
}

MENU tc_mn_013_menu8
{
 	LABEL "Level 8";
	ITEMS
	{
		tc_mn_013_menu9
	}
}

MENU tc_mn_013_menu9
{
 	LABEL "Level 9";
	ITEMS
	{
		tc_mn_013_dialog1
	}
}

MENU tc_mn_013_dialog1
{
 	LABEL "Dialog";
 	STYLE DIALOG;
	ITEMS
	{
		"Dialog Box"
	}
}

MENU    tc_mn_014_dialog  /* This is a device-level menu */
{
    LABEL   "TC_MN_014 Dialog";
    STYLE   DIALOG;
    ITEMS
    {
		VISUALTB[0].MENU.WINDOW_VISUALTB,
		VISUALTB[0].MENU.TC_CH_001_PAGE,
		VISUALTB[0].MENU.TC_CH_001_INPUT_GROUP,
		VISUALTB[0].MENU.MENUTESTDIALOG1,

		VISUALTB[0].METHOD.MENUTESTMETHOD1,
		VISUALTB[0].GRID.MENUTESTGRID1,
		VISUALTB[0].GRAPH.MENUTESTGRAPH1,
		VISUALTB[0].CHART.MENUTESTCHART1
	}
}

MENU    tc_mn_015_window  /* This is a device-level menu */
{
    LABEL   "TC_MN_015 Window";
    STYLE   WINDOW;
    ITEMS
    {
		VISUALTB[0].MENU.WINDOW_VISUALTB,
		VISUALTB[0].MENU.TC_CH_001_INPUT_GROUP,

		VISUALTB[0].METHOD.MENUTESTMETHOD1,
		VISUALTB[0].PARAM.ST_REV,
		VISUALTB[0].PARAM.MODE_BLK.TARGET,
		VISUALTB[0].PARAM.TEST_Y_ARRAY_1[1],
		VISUALTB[0].GRID.MENUTESTGRID1,
		VISUALTB[0].GRAPH.MENUTESTGRAPH1,
		VISUALTB[0].CHART.MENUTESTCHART1
	}
}

MENU    tc_mn_016_page  /* This is a device-level menu */
{
    LABEL   "TC_MN_016 Page";
    STYLE   PAGE;
    ITEMS
    {
		VISUALTB[0].MENU.WINDOW_VISUALTB,
		VISUALTB[0].MENU.TC_CH_001_INPUT_GROUP,
		VISUALTB[0].MENU.MENUTESTDIALOG1,

		VISUALTB[0].METHOD.MENUTESTMETHOD1,
		VISUALTB[0].PARAM.TEST_FL_VAL_1,
		VISUALTB[0].PARAM.MODE_BLK.TARGET,
		VISUALTB[0].PARAM.TEST_Y_ARRAY_1[1],
		VISUALTB[0].GRID.MENUTESTGRID1,
		VISUALTB[0].GRAPH.MENUTESTGRAPH1,
		VISUALTB[0].CHART.MENUTESTCHART1
	}
}

MENU    tc_mn_017_group  /* This is a device-level menu */
{
    LABEL   "TC_MN_017 Group";
    STYLE   GROUP;
    ITEMS
    {
		VISUALTB[0].MENU.WINDOW_VISUALTB,
		VISUALTB[0].MENU.TC_CH_001_INPUT_GROUP,
		VISUALTB[0].MENU.MENUTESTDIALOG1
	}
}

MENU    tc_mn_018_menu  /* This is a device-level menu */
{
    LABEL   "TC_MN_018 Menu";
    STYLE   MENU;
    ITEMS
    {
		VISUALTB[0].PARAM.TEST_FL_VAL_1,
		VISUALTB[0].PARAM.MODE_BLK.TARGET,
		VISUALTB[0].PARAM.TEST_Y_ARRAY_1[1]
	}
}

MENU    tc_mn_019_menu  /* This is a device-level menu */
{
    LABEL   "TC_MN_019 Menu";
    STYLE   MENU;
    ITEMS
	{
        "Not Completed"
    }
}


/***********************************************************************/

#endif

