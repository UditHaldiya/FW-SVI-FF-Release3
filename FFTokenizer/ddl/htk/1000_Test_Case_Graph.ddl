/*****************************************************************************/
/* 1000_Test_Case_Graph.ddl                                                  */
/*                                                                           */
/*   This file contains DDL for the graph test cases.                        */
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
** Graph test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_001                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with one waveform.                    */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_001_waveform
{
    LABEL   "TC_GR_001 Waveform";
	HELP	"tc_gr_001_waveform help";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
}

GRAPH 	    tc_gr_001_graph
{
	LABEL	"TC_GR_001 Graph";
	HELP    "Verify that host displays a graph with one waveform.";
	MEMBERS
	{
	    TC_GR_001_WAVEFORM,     tc_gr_001_waveform;		
	}
}

MENU    tc_gr_001_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5]
    }
}

MENU    tc_gr_001_methnvis_group
{
    LABEL   "Methods & Visualizations";
    STYLE   GROUP;
    ITEMS
    {
        tc_gr_001_graph,
        ROWBREAK,
        tc_gr_001_set_vals_method,
        clear_test_vals_visualtb
    }    
}    

MENU    tc_gr_001_page
{
    LABEL   "TC_GR_001";
    STYLE   PAGE;
    ITEMS
    {
        tc_gr_001_input_group,
        ROWBREAK,
        tc_gr_001_methnvis_group
    }
}

METHOD  tc_gr_001_set_vals_method
{
    LABEL   "TC_GR_001 - Set Values";
    CLASS   INPUT;
    DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,10);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,0);
     }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_002                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with 2 XY, 2 horizontal, 2 vertical.  */
/*                                                                           */
/*****************************************************************************/
WAVEFORM 	tc_gr_002_xy_waveform1
{
    LABEL   "TC_GR_002 XY Waveform1";
    TYPE    XY
	{
		X_VALUES    {   test_x_array_1  }
		Y_VALUES    {   test_y_array_1  }
	}
    LINE_COLOR  _RGB_PINK;
}

WAVEFORM 	tc_gr_002_xy_waveform2
{
	LABEL   "TC_GR_002 XY Waveform2";
    TYPE    XY
	{
		X_VALUES    {   test_x_array_2  }
		Y_VALUES    {   test_y_array_2  }
	}
    LINE_COLOR  _RGB_NAVY;
}

WAVEFORM 	tc_gr_002_hz_waveform1
{
	LABEL   "TC_GR_002 Horizontal Waveform1";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_hi_limit   }
	}
    LINE_TYPE   HIGH_LIMIT;
    LINE_COLOR  _RGB_YELLOW;
}

WAVEFORM 	tc_gr_002_hz_waveform2
{
    LABEL   "TC_GR_002 Horizontal Waveform2";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_lo_limit   }
	}
    LINE_TYPE   LOW_LIMIT;
    LINE_COLOR  _RGB_TURQUOISE;
}

WAVEFORM 	tc_gr_002_vt_waveform1
{
	LABEL   "TC_GR_002 Vertical Waveform1";
    TYPE    VERTICAL
	{
		X_VALUES    {   test_left_limit     }
	}
    LINE_TYPE   LOW_LIMIT;
    LINE_COLOR  _RGB_MAROON;
}

WAVEFORM 	tc_gr_002_vt_waveform2
{
	LABEL   "TC_GR_002 Vertical Waveform2";
    TYPE    VERTICAL
	{
		X_VALUES    {   test_right_limit    }
	}
    LINE_TYPE   HIGH_LIMIT;
    LINE_COLOR  _RGB_RED;
}

GRAPH 	tc_gr_002_graph
{
	LABEL	"TC_GR_002 Graph";
    HELP    "Verify that host displays a graph with 2 XY, "
            "2 horizontal, 2 vertical.";
	MEMBERS
	{
		TC_GR_002_XY_Waveform1,     tc_gr_002_xy_waveform1;		
		TC_GR_002_XY_Waveform2,     tc_gr_002_xy_waveform2;
		TC_GR_002_HZ_WAVEFORM1,     tc_gr_002_hz_waveform1;
		TC_GR_002_HZ_WAVEFORM2,     tc_gr_002_hz_waveform2;
		TC_GR_002_VT_WAVEFORM1,     tc_gr_002_vt_waveform1;
		TC_GR_002_VT_WAVEFORM2,     tc_gr_002_vt_waveform2;
	}
}

MENU    tc_gr_002_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        COLUMNBREAK,
        test_x_array_1[1],
        test_x_array_1[2],
        test_x_array_1[3],
        test_x_array_1[4],
        test_x_array_1[5],
        ROWBREAK,ROWBREAK,
        test_y_array_2[1],
        test_y_array_2[2],
        test_y_array_2[3],
        test_y_array_2[4],
        test_y_array_2[5],
        COLUMNBREAK,
        test_x_array_2[1],
        test_x_array_2[2],
        test_x_array_2[3],
        test_x_array_2[4],
        test_x_array_2[5],
        ROWBREAK,ROWBREAK,
        test_hi_limit,
        test_lo_limit,
        test_left_limit,
        test_right_limit
    }
}

tc_gr_002_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_002_graph,
        ROWBREAK,
        tc_gr_002_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_002_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_002";
    REDEFINE ITEMS
    {
        tc_gr_002_input_group,
        ROWBREAK,
        tc_gr_002_methnvis_group
    }
}

tc_gr_002_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_002 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,10);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,0);

        status=put_float_value(ITEM_ID(test_x_array_1),1,-3);
        status=put_float_value(ITEM_ID(test_x_array_1),2,4);
        status=put_float_value(ITEM_ID(test_x_array_1),3,7);
        status=put_float_value(ITEM_ID(test_x_array_1),4,12);
        status=put_float_value(ITEM_ID(test_x_array_1),5,15);

        status=put_float_value(ITEM_ID(test_y_array_2),1,4);
        status=put_float_value(ITEM_ID(test_y_array_2),2,3);
        status=put_float_value(ITEM_ID(test_y_array_2),3,7);
        status=put_float_value(ITEM_ID(test_y_array_2),4,-1);
        status=put_float_value(ITEM_ID(test_y_array_2),5,-3);

        status=put_float_value(ITEM_ID(test_x_array_2),1,-2);
        status=put_float_value(ITEM_ID(test_x_array_2),2,2);
        status=put_float_value(ITEM_ID(test_x_array_2),3,7);
        status=put_float_value(ITEM_ID(test_x_array_2),4,9.67);
        status=put_float_value(ITEM_ID(test_x_array_2),5,13.35);

        status=put_float_value(ITEM_ID(test_hi_limit),0,9);
        status=put_float_value(ITEM_ID(test_lo_limit),0,2);
        status=put_float_value(ITEM_ID(test_left_limit),0,1);
        status=put_float_value(ITEM_ID(test_right_limit),0,14);
    }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_003                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a XX_SMALL graph with one waveform.           */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_003_waveform
{
    LABEL   "TC_GR_003 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_003_graph
{
	LABEL	"TC_GR_003 Graph";
	HELP    "Verify that host displays a XX_SMALL graph with one waveform.";
	MEMBERS
	{
	    TC_GR_003_WAVEFORM,     tc_gr_003_waveform;		
	}
	HEIGHT  XX_SMALL;
	WIDTH   XX_SMALL;
}

tc_gr_003_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_003_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_003_graph,
        ROWBREAK,
        tc_gr_003_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_003_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_003";
    REDEFINE ITEMS
    {
        tc_gr_003_input_group,
        ROWBREAK,
        tc_gr_003_methnvis_group
    }
}

tc_gr_003_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_003 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_004                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a X_SMALL graph with one waveform.            */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_004_waveform
{
    LABEL   "TC_GR_004 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_004_graph
{
	LABEL	"TC_GR_004 Graph";
	HELP    "Verify that host displays a X_SMALL graph with one waveform.";
	MEMBERS
	{
	    TC_GR_004_WAVEFORM,     tc_gr_004_waveform;		
	}
	HEIGHT  X_SMALL;
	WIDTH   X_SMALL;
}

tc_gr_004_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_004_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_004_graph,
        ROWBREAK,
        tc_gr_004_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_004_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_004";
    REDEFINE ITEMS
    {
        tc_gr_004_input_group,
        ROWBREAK,
        tc_gr_004_methnvis_group
    }
}

tc_gr_004_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_004 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_005                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a SMALL graph with one waveform.              */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_005_waveform
{
    LABEL   "TC_GR_005 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_005_graph
{
	LABEL	"TC_GR_005 Graph";
	HELP    "Verify that host displays a SMALL graph with one waveform.";
	MEMBERS
	{
	    TC_GR_005_WAVEFORM,     tc_gr_005_waveform;		
	}
	HEIGHT  SMALL;
	WIDTH   SMALL;
}

tc_gr_005_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_005_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_005_graph,
        ROWBREAK,
        tc_gr_005_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_005_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_005";
    REDEFINE ITEMS
    {
        tc_gr_005_input_group,
        ROWBREAK,
        tc_gr_005_methnvis_group
    }
}

tc_gr_005_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_005 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_006                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a MEDIUM graph with one waveform.             */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_006_waveform
{
    LABEL   "TC_GR_006 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_006_graph
{
	LABEL	"TC_GR_006 Graph";
	HELP    "Verify that host displays a MEDIUM graph with one waveform.";
	MEMBERS
	{
	    TC_GR_006_WAVEFORM,     tc_gr_006_waveform;		
	}
	HEIGHT  MEDIUM;
	WIDTH   MEDIUM;
}

tc_gr_006_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_006_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_006_graph,
        ROWBREAK,
        tc_gr_006_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_006_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_006";
    REDEFINE ITEMS
    {
        tc_gr_006_input_group,
        ROWBREAK,
        tc_gr_006_methnvis_group
    }
}

tc_gr_006_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_006 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_007                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a LARGE graph with one waveform.              */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_007_waveform
{
    LABEL   "TC_GR_007 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_007_graph
{
	LABEL	"TC_GR_007 Graph";
	HELP    "Verify that host displays a LARGE graph with one waveform.";
	MEMBERS
	{
	    TC_GR_007_WAVEFORM,     tc_gr_007_waveform;		
	}
	HEIGHT  LARGE;
	WIDTH   LARGE;
}

tc_gr_007_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_007_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_007_graph,
        ROWBREAK,
        tc_gr_007_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_007_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_007";
    REDEFINE ITEMS
    {
        tc_gr_007_input_group,
        ROWBREAK,
        tc_gr_007_methnvis_group
    }
}

tc_gr_007_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_007 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_008                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a X_LARGE graph with one waveform.            */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_008_waveform
{
    LABEL   "TC_GR_008 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_008_graph
{
	LABEL	"TC_GR_008 Graph";
	HELP    "Verify that host displays a X_LARGE graph with one waveform.";
	MEMBERS
	{
	    TC_GR_008_WAVEFORM,     tc_gr_008_waveform;		
	}
	HEIGHT  X_LARGE;
	WIDTH   X_LARGE;
}

tc_gr_008_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_008_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_008_graph,
        ROWBREAK,
        tc_gr_008_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_008_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_008";
    REDEFINE ITEMS
    {
        tc_gr_008_input_group,
        ROWBREAK,
        tc_gr_008_methnvis_group
    }
}

tc_gr_008_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_008 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_009                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a XX_LARGE graph with one waveform.           */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_009_waveform
{
    LABEL   "TC_GR_009 Waveform";
    TYPE    YT
	{
	    X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES
		{
			test_y_array_1
		}
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	    tc_gr_009_graph
{
	LABEL	"TC_GR_009 Graph";
	HELP    "Verify that host displays a XX_LARGE graph with one waveform.";
	MEMBERS
	{
	    TC_GR_009_WAVEFORM,     tc_gr_009_waveform;		
	}
	HEIGHT  XX_LARGE;
	WIDTH   XX_LARGE;
}

tc_gr_009_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_009_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_009_graph,
        ROWBREAK,
        tc_gr_009_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_009_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_009";
    REDEFINE ITEMS
    {
        tc_gr_009_input_group,
        ROWBREAK,
        tc_gr_009_methnvis_group
    }
}

tc_gr_009_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_009 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_010                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with 2 YT, 4 vertical with different  */
/*   line types.                                                             */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_010_axis
{
	LABEL   "TC_GR_010 Y axis";
        HELP "Y axis help text";
	MIN_VALUE   -15;
	MAX_VALUE    15;
	SCALING     LINEAR;
	CONSTANT_UNIT   "Constant Unit Text";
}

WAVEFORM 	tc_gr_010_yt_waveform1
{
    LABEL   "TC_GR_010 YT Waveform1";
	TYPE    YT
	{
		X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_1  }
		NUMBER_OF_POINTS    _ARRAY_SIZE/2;
	}
	LINE_TYPE   DATA1;
	LINE_COLOR  _RGB_RED;
	Y_AXIS      tc_gr_010_axis;
}

WAVEFORM 	tc_gr_010_yt_waveform2
{
	LABEL   "TC_GR_010 YT Waveform2";
	TYPE YT
	{
		X_INITIAL 	 0;
		X_INCREMENT 10;
		Y_VALUES    {   test_y_array_2  }
	}
	LINE_TYPE   DATA2;
	EMPHASIS    TRUE;
    LINE_COLOR  _RGB_NAVY;
	Y_AXIS      tc_gr_010_axis;
}

WAVEFORM 	tc_gr_010_hz_waveform1
{
	LABEL   "TC_GR_010 Horizontal Waveform1";
	TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_hi_hi_limit    }
	}
	LINE_TYPE   HIGH_HIGH_LIMIT;
	LINE_COLOR  _RGB_GREEN;
	Y_AXIS      tc_gr_010_axis;
}

WAVEFORM 	tc_gr_010_hz_waveform2
{
	LABEL   "TC_GR_010 Horizontal Waveform2";
	TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_hi_limit   }
	}
	LINE_TYPE   HIGH_LIMIT;
	LINE_COLOR  _RGB_PURPLE;
	Y_AXIS      tc_gr_010_axis;
}

WAVEFORM 	tc_gr_010_hz_waveform3
{
	LABEL   "TC_GR_010 Horizontal Waveform3";
	TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_lo_limit   }
	}
	LINE_TYPE   LOW_LIMIT;
	LINE_COLOR  _RGB_MAROON;
	Y_AXIS      tc_gr_010_axis;
}

WAVEFORM 	tc_gr_010_hz_waveform4
{
	LABEL   "TC_GR_010 Horizontal Waveform4";
	TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_lo_lo_limit    }
	}
	LINE_TYPE   LOW_LOW_LIMIT;
	LINE_COLOR  _RGB_BLUE;
	Y_AXIS      tc_gr_010_axis;
}

GRAPH   tc_gr_010_graph
{
	LABEL	"TC_GR_010 Graph";
	HELP    "Verify that host displays a graph with 2 YT, 4 "
            "horizontal with different line types.";
	MEMBERS
	{
		TC_GR_010_YT_WAVEFORM1,     tc_gr_010_yt_waveform1;		
		TC_GR_010_YT_WAVEFORM2,     tc_gr_010_yt_waveform2;
		TC_GR_010_HZ_WAVEFORM1,     tc_gr_010_hz_waveform1;
		TC_GR_010_HZ_WAVEFORM2,     tc_gr_010_hz_waveform2;
		TC_GR_010_HZ_WAVEFORM3,     tc_gr_010_hz_waveform3;
		TC_GR_010_HZ_WAVEFORM4,     tc_gr_010_hz_waveform4;
	}
}

MENU    tc_gr_010_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        ROWBREAK,
        test_y_array_2[1],
        test_y_array_2[2],
        test_y_array_2[3],
        test_y_array_2[4],
        test_y_array_2[5],
        COLUMNBREAK,
        ROWBREAK
        test_hi_limit,
        test_lo_limit,
        test_hi_hi_limit,
        test_lo_lo_limit
    }
}

tc_gr_010_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_010_graph,
        ROWBREAK,
        tc_gr_010_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_010_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_010";
    REDEFINE ITEMS
    {
        tc_gr_010_input_group,
        ROWBREAK,
        tc_gr_010_methnvis_group
    }
}

tc_gr_010_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_010 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,10);
        status=put_float_value(ITEM_ID(test_y_array_1),3,2);
        status=put_float_value(ITEM_ID(test_y_array_1),4,-3.5);
        status=put_float_value(ITEM_ID(test_y_array_1),5,0);

        status=put_float_value(ITEM_ID(test_y_array_2),1,4);
        status=put_float_value(ITEM_ID(test_y_array_2),2,3);
        status=put_float_value(ITEM_ID(test_y_array_2),3,7);
        status=put_float_value(ITEM_ID(test_y_array_2),4,-1);
        status=put_float_value(ITEM_ID(test_y_array_2),5,-3);

        status=put_float_value(ITEM_ID(test_hi_limit),0,9);
        status=put_float_value(ITEM_ID(test_lo_limit),0,2);
        status=put_float_value(ITEM_ID(test_hi_hi_limit),0,12);
        status=put_float_value(ITEM_ID(test_lo_lo_limit),0,-3);
    }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_011                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with a LOG x axis.                    */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_011_axis
{   
    LABEL   "TC_GR_011 X axis";
	SCALING LOGARITHMIC;
}

WAVEFORM    tc_gr_011_waveform
{
	LABEL   "TC_GR_011 Waveform";
	TYPE    XY
	{
		X_VALUES    {   test_x_array_1  }
        Y_VALUES    {   test_y_array_1  }
	}
    LINE_COLOR  _RGB_NAVY;
}

GRAPH 	tc_gr_011_graph
{
	LABEL	"TC_GR_011 Graph";
	HELP    "Verify that host displays a graph with a LOG x axis.";
    MEMBERS
	{
		TC_GR_011_WAVEFORM, tc_gr_011_waveform;		
    }
    X_AXIS  tc_gr_011_axis;
}

MENU    tc_gr_011_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        COLUMNBREAK,
        test_x_array_1[1],
        test_x_array_1[2],
        test_x_array_1[3],
        test_x_array_1[4],
        test_x_array_1[5]
    }
}

tc_gr_011_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_011_graph,
        ROWBREAK,
        tc_gr_011_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_011_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_011";
    REDEFINE ITEMS
    {
        tc_gr_011_input_group,
        ROWBREAK,
        tc_gr_011_methnvis_group
    }
}

tc_gr_011_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_011 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,1);
        status=put_float_value(ITEM_ID(test_y_array_1),2,3);
        status=put_float_value(ITEM_ID(test_y_array_1),3,7);
        status=put_float_value(ITEM_ID(test_y_array_1),4,10);
        status=put_float_value(ITEM_ID(test_y_array_1),5,15);

        status=put_float_value(ITEM_ID(test_x_array_1),1,0.01);
        status=put_float_value(ITEM_ID(test_x_array_1),2,1);
        status=put_float_value(ITEM_ID(test_x_array_1),3,10);
        status=put_float_value(ITEM_ID(test_x_array_1),4,15);
        status=put_float_value(ITEM_ID(test_x_array_1),5,20);
     }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_012                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with keypoints defined and handling   */
/*   set to read only.                                                       */
/*                                                                           */
/*****************************************************************************/
WAVEFORM    tc_gr_012_waveform
{
	LABEL   "TC_GR_012 Waveform";
	TYPE    XY
	{
		X_VALUES    {   test_x_array_1  }
        Y_VALUES    {   test_y_array_1  }
	}
    KEY_POINTS
    {
        X_VALUES    {   test_fl_val_1, test_fl_val_2    }
        Y_VALUES    {   test_fl_val_3, test_fl_val_4    }
    }
    LINE_COLOR  _RGB_NAVY;
    HANDLING    READ;
}

GRAPH 	tc_gr_012_graph
{
	LABEL	"TC_GR_012 Graph";
	HELP    "Verify that host displays a graph with keypoints "
            "defined and handling set to read only.";
    MEMBERS
	{
		TC_GR_012_WAVEFORM, tc_gr_012_waveform;		
    }
}

MENU    tc_gr_012_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        COLUMNBREAK,
        test_x_array_1[1],
        test_x_array_1[2],
        test_x_array_1[3],
        test_x_array_1[4],
        test_x_array_1[5]
        ROWBREAK,ROWBREAK,
        test_fl_val_1,
        test_fl_val_2,
        test_fl_val_3,
        test_fl_val_4
    }
}

tc_gr_012_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_012_graph,
        ROWBREAK,
        tc_gr_012_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_012_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_012";
    REDEFINE ITEMS
    {
        tc_gr_012_input_group,
        ROWBREAK,
        tc_gr_012_methnvis_group
    }
}

tc_gr_012_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_012 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,12);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,-1.4);

        status=put_float_value(ITEM_ID(test_x_array_1),1,-3);
        status=put_float_value(ITEM_ID(test_x_array_1),2,4);
        status=put_float_value(ITEM_ID(test_x_array_1),3,7);
        status=put_float_value(ITEM_ID(test_x_array_1),4,12);
        status=put_float_value(ITEM_ID(test_x_array_1),5,14.5);

        status=put_float_value(ITEM_ID(test_fl_val_1),0,7);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,14.5);
        status=put_float_value(ITEM_ID(test_fl_val_3),0,12);
        status=put_float_value(ITEM_ID(test_fl_val_4),0,-1.4);
     }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_013                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with XY waveform and action methods.  */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_013_axis
{
	LABEL   "TC_GR_013 Y axis";
    HELP "Y axis help text";
	MIN_VALUE   -10;
	MAX_VALUE   10;
	SCALING     LINEAR;
	CONSTANT_UNIT  "Constant Unit Text";
}

WAVEFORM    tc_gr_013_waveform
{
	LABEL   "TC_GR_013 Waveform";
	TYPE    XY
	{
		X_VALUES    {   test_x_array_1  }
        Y_VALUES    {   test_y_array_1  }
        NUMBER_OF_POINTS    _ARRAY_SIZE-1;    
	}
	Y_AXIS          tc_gr_013_axis;
    LINE_COLOR      _RGB_PINK;
	INIT_ACTIONS    {   tc_gr_013_wvfrm_init_method     }
    REFRESH_ACTIONS {   tc_gr_013_wvfrm_refresh_method  }
	EXIT_ACTIONS    {   tc_gr_013_wvfrm_exit_method     }
}

GRAPH   tc_gr_013_graph
{
	LABEL	"TC_GR_013 Graph";
	HELP    "Verify that host displays a graph with XY waveform and "
            "action methods.";
    MEMBERS
	{
		TC_GR_013_WAVEFORM, tc_gr_013_waveform;		
    }
}

tc_gr_013_input_group LIKE MENU tc_gr_011_input_group { REDEFINE LABEL   "Input"; }

tc_gr_013_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_013_graph,
        ROWBREAK,
        tc_gr_013_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_013_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_013";
    REDEFINE ITEMS
    {
        tc_gr_013_input_group,
        ROWBREAK,
        tc_gr_013_methnvis_group
    }
}

METHOD  tc_gr_013_wvfrm_init_method
{
	LABEL   "TC_GR_013 Waveform Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Waveform Init Method Worked Properly!",ids,indices,0);
    }
}

METHOD  tc_gr_013_wvfrm_refresh_method
{
	LABEL   "TC_GR_013 Waveform Refresh Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Waveform Refresh Method Worked Properly!",ids,indices,0);
    }
}

METHOD  tc_gr_013_wvfrm_exit_method
{
	LABEL   "TC_GR_013 Waveform Exit Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Waveform Exit Method Worked Properly!",ids,indices,0);
    }
}

tc_gr_013_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_013 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,12);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,-1.4);

        status=put_float_value(ITEM_ID(test_x_array_1),1,-3);
        status=put_float_value(ITEM_ID(test_x_array_1),2,4);
        status=put_float_value(ITEM_ID(test_x_array_1),3,7);
        status=put_float_value(ITEM_ID(test_x_array_1),4,12);
        status=put_float_value(ITEM_ID(test_x_array_1),5,14.5);
     }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_014                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graph with 1 YT, 1 XY, 4 horiz, no vert.    */
/*   The YT and XY shall have different axis.                                */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_014_axis1
{
	LABEL           "TC_GR_014 Y axis1";
	HELP			"Y axis help text 1";
    MIN_VALUE       -100;
	MAX_VALUE        100;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text1";
}

AXIS    tc_gr_014_axis2
{
	LABEL           "TC_GR_014 Y axis2";
	HELP			"Y axis help text 2";
    MIN_VALUE       -50;
	MAX_VALUE        50;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text2";
}

WAVEFORM 	tc_gr_014_yt_waveform
{
	LABEL   "TC_GR_014 YT Waveform";
	TYPE    YT
	{
		X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_1  }
	}
	LINE_TYPE   DATA1;
	LINE_COLOR  _RGB_RED;
	Y_AXIS      tc_gr_014_axis1;
}

WAVEFORM 	tc_gr_014_xy_waveform
{
	LABEL   "TC_GR_014 XY Waveform";
	TYPE    XY
	{
		Y_VALUES    {   test_y_array_2      }
		X_VALUES    {   test_x_array_2      }
	}
	LINE_TYPE   DATA2;
    LINE_COLOR  _RGB_NAVY;
	Y_AXIS      tc_gr_014_axis2;
}

WAVEFORM 	tc_gr_014_hz_waveform1
{
	LABEL   "TC_GR_014 Horizontal Waveform1";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_hi_hi_limit    }
	}
	LINE_TYPE   HIGH_HIGH_LIMIT;
	LINE_COLOR  _RGB_MAROON;
	Y_AXIS      tc_gr_014_axis1;
}

WAVEFORM 	tc_gr_014_hz_waveform2
{
	LABEL   "TC_GR_014 Horizontal Waveform2";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_hi_limit   }
	}
	LINE_TYPE   HIGH_LIMIT;
	LINE_COLOR  _RGB_YELLOW;
	Y_AXIS      tc_gr_014_axis1;
}

WAVEFORM 	tc_gr_014_hz_waveform3
{
	LABEL   "TC_GR_014 Horizontal Waveform3";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_lo_limit   }
	}
	LINE_TYPE   LOW_LIMIT;
	LINE_COLOR  _RGB_TURQUOISE;
	Y_AXIS      tc_gr_014_axis1;
}

WAVEFORM 	tc_gr_014_hz_waveform4
{
	LABEL   "TC_GR_014 Horizontal Waveform4";
    TYPE    HORIZONTAL
	{
		Y_VALUES    {   test_lo_lo_limit    }
	}
	LINE_TYPE   LOW_LOW_LIMIT;
	LINE_COLOR  _RGB_PURPLE;
	Y_AXIS      tc_gr_014_axis1;
}

GRAPH 	tc_gr_014_graph
{
	LABEL	"TC_GR_014 Graph";
	HELP    "Verify that host displays a graph with 1 YT, 1 XY, 4 horiz. "
            "The YT and XY shall have different axis.";
    MEMBERS
	{
		TC_GR_014_YT_WAVEFORM,  tc_gr_014_yt_waveform;		
		TC_GR_014_XY_WAVEFORM,  tc_gr_014_xy_waveform;
		TC_GR_014_HZ_WAVEFORM1, tc_gr_014_hz_waveform1;
		TC_GR_014_HZ_WAVEFORM2, tc_gr_014_hz_waveform2;
		TC_GR_014_HZ_WAVEFORM3, tc_gr_014_hz_waveform3;
		TC_GR_014_HZ_WAVEFORM4, tc_gr_014_hz_waveform4;
	}
}

MENU    tc_gr_014_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        ROWBREAK,
        test_y_array_2[1],
        test_y_array_2[2],
        test_y_array_2[3],
        test_y_array_2[4],
        test_y_array_2[5],
        COLUMNBREAK,
        test_x_array_2[1],
        test_x_array_2[2],
        test_x_array_2[3],
        test_x_array_2[4],
        test_x_array_2[5],
        ROWBREAK,ROWBREAK,
        test_hi_limit,
        test_lo_limit,
        test_hi_hi_limit,
        test_lo_lo_limit
    }
}

tc_gr_014_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_014_graph,
        ROWBREAK,
        tc_gr_014_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_014_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_014";
    REDEFINE ITEMS
    {
        tc_gr_014_input_group,
        ROWBREAK,
        tc_gr_014_methnvis_group
    }
}

tc_gr_014_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_014 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,10);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,0);

        status=put_float_value(ITEM_ID(test_y_array_2),1,40);
        status=put_float_value(ITEM_ID(test_y_array_2),2,30);
        status=put_float_value(ITEM_ID(test_y_array_2),3,70);
        status=put_float_value(ITEM_ID(test_y_array_2),4,-10);
        status=put_float_value(ITEM_ID(test_y_array_2),5,-30);

        status=put_float_value(ITEM_ID(test_x_array_2),1,-5);
        status=put_float_value(ITEM_ID(test_x_array_2),2,2);
        status=put_float_value(ITEM_ID(test_x_array_2),3,7);
        status=put_float_value(ITEM_ID(test_x_array_2),4,9.67);
        status=put_float_value(ITEM_ID(test_x_array_2),5,13.35);

        status=put_float_value(ITEM_ID(test_hi_limit),0,35);
        status=put_float_value(ITEM_ID(test_lo_limit),0,-20);
        status=put_float_value(ITEM_ID(test_hi_hi_limit),0,45);
        status=put_float_value(ITEM_ID(test_lo_lo_limit),0,-30);
    }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_015                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays 2 graphs on a window.                         */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_015_y_axis1
{}

AXIS    tc_gr_015_y_axis2
{
	LABEL           "TC_GR_015 Y axis2";
	MIN_VALUE       -100;
	MAX_VALUE       100;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text2";
}

AXIS    tc_gr_015_x_axis1
{
	LABEL           "TC_GR_015 X axis1";
	MIN_VALUE       10;
	MAX_VALUE       20;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit X Text 1";
}

AXIS    tc_gr_015_x_axis2
{
	LABEL           "TC_GR_015 X axis2";
	MIN_VALUE       -100;
	MAX_VALUE       100;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit X Text2";
}

WAVEFORM    tc_gr_015_yt_waveform1
{
	LABEL   "TC_GR_015 YT Waveform1";
    TYPE    YT
	{
		X_INITIAL   0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_1      }
	}
	Y_AXIS      tc_gr_015_y_axis1;
}

WAVEFORM 	tc_gr_015_yt_waveform2
{
	LABEL   "TC_GR_015 YT Waveform2";
    TYPE    YT
	{
		X_INITIAL 	0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_2      }
	}
	Y_AXIS      tc_gr_015_y_axis2;
}

GRAPH   tc_gr_015_graph1
{
	LABEL	"TC_GR_015 Graph1";
	HELP    "Verify that host displays 2 graphs on a window.";
    MEMBERS
	{
		TC_GR_015_YT_WAVEFORM1, tc_gr_015_yt_waveform1;		
	}
	X_AXIS tc_gr_015_x_axis1;
}

GRAPH 	tc_gr_015_graph2
{
	LABEL	"TC_GR_015 Graph2";
	HELP    "Verify that host displays 2 graphs on a window.";
    MEMBERS
	{
		TC_GR_015_YT_WAVEFORM2, tc_gr_015_yt_waveform2;		
	}
	X_AXIS tc_gr_015_x_axis2;
}

MENU    tc_gr_015_window
{
    LABEL   "TC_GR_015 Window";
    STYLE   WINDOW;
    ITEMS
    {
        tc_gr_015_graph1,
        tc_gr_015_graph2
    }
}    

MENU    tc_gr_015_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_y_array_1[1],
        test_y_array_1[2],
        test_y_array_1[3],
        test_y_array_1[4],
        test_y_array_1[5],
        ROWBREAK,
        test_y_array_2[1],
        test_y_array_2[2],
        test_y_array_2[3],
        test_y_array_2[4],
        test_y_array_2[5]
    }
}

tc_gr_015_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_015_window,
        ROWBREAK,
        tc_gr_015_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_015_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_015";
    REDEFINE ITEMS
    {
        tc_gr_015_input_group,
        ROWBREAK,
        tc_gr_015_methnvis_group
    }
}

tc_gr_015_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{
    REDEFINE LABEL  "TC_GR_015 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_y_array_1),1,-5);
        status=put_float_value(ITEM_ID(test_y_array_1),2,2.5);
        status=put_float_value(ITEM_ID(test_y_array_1),3,10);
        status=put_float_value(ITEM_ID(test_y_array_1),4,8);
        status=put_float_value(ITEM_ID(test_y_array_1),5,0);

        status=put_float_value(ITEM_ID(test_y_array_2),1,4);
        status=put_float_value(ITEM_ID(test_y_array_2),2,5);
        status=put_float_value(ITEM_ID(test_y_array_2),3,13);
        status=put_float_value(ITEM_ID(test_y_array_2),4,3);
        status=put_float_value(ITEM_ID(test_y_array_2),5,10);
    }
} 

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GR_016                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Graph                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a graphs with the MIN and MAX value the same. */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_gr_016_y_axis
{
	LABEL       "TC_GR_016 Y axis";
	MIN_VALUE   10.0;
	MAX_VALUE   10.0;
	SCALING     LINEAR;
}

WAVEFORM    tc_gr_016_yt_waveform
{
	LABEL   "TC_GR_016 YT Waveform";
    TYPE    YT
	{
		X_INITIAL 	0;
		X_INCREMENT 5;
		Y_VALUES    {   test_y_array_1      }
	}
	LINE_COLOR  _RGB_NAVY;
	Y_AXIS      tc_gr_016_y_axis;
}

GRAPH 	tc_gr_016_graph
{
	LABEL	"TC_GR_016 Graph";
	HELP    "Verify that host displays a graphs with the "
            "MIN and MAX value the same.";
    MEMBERS
	{
		TC_GR_016_YT_WAVEFORM,  tc_gr_016_yt_waveform;		
	}
}

tc_gr_016_input_group LIKE MENU tc_gr_001_input_group { REDEFINE LABEL   "Input"; }

tc_gr_016_methnvis_group LIKE MENU tc_gr_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_gr_016_graph,
        ROWBREAK,
        tc_gr_016_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_gr_016_page LIKE MENU tc_gr_001_page
{
    REDEFINE LABEL  "TC_GR_016";
    REDEFINE ITEMS
    {
        tc_gr_016_input_group,
        ROWBREAK,
        tc_gr_016_methnvis_group
    }
}

tc_gr_016_set_vals_method LIKE METHOD tc_gr_001_set_vals_method
{    REDEFINE LABEL  "TC_GR_016 - Set Values";      }

/***********************************************************************/

#endif
