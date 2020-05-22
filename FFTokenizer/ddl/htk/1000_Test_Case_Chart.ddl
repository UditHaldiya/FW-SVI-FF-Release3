/*****************************************************************************/
/* 1000_Test_Case_Chart.ddl                                                  */
/*                                                                           */
/*   This file contains DDL for the chart test cases.                        */
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
** Chart test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_001                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_001_source
{
    LABEL   "TC_CH_001 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
}

CHART 	tc_ch_001_chart
{
	LABEL	"TC_CH_001 Chart";
	HELP	"Chart Help: TC_CH_001";
	MEMBERS
	{
		TC_CH_001_SOURCE,   tc_ch_001_source;		
	}
}

MENU    tc_ch_001_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_fl_val_1
    }
}

MENU    tc_ch_001_methnvis_group
{
    LABEL   "Methods & Visualizations";
    STYLE   GROUP;
    ITEMS
    {
        tc_ch_001_chart,
        ROWBREAK,
        tc_ch_001_set_vals_method,
        clear_test_vals_visualtb
    }    
}    

MENU    tc_ch_001_page
{
    LABEL   "TC_CH_001";
    STYLE   PAGE;
    ITEMS
    {
        tc_ch_001_input_group,
        ROWBREAK,
        tc_ch_001_methnvis_group
    }
}

METHOD  tc_ch_001_set_vals_method
{
    LABEL   "TC_CH_001 - Set Values";
    CLASS   INPUT;
    DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,5);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_002                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source with multiple      */
/*   variables.                                                              */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_002_axis
{
	LABEL           "TC_CH_002 axis";
	HELP			"TC_CH_002 axis help text";
	MIN_VALUE       -6;
	MAX_VALUE        10;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text";
}

SOURCE  tc_ch_002_source
{
	LABEL   "TC_CH_002 Source";
	HELP	"TC_CH_002 Source TC Chart 2 Help Text";
	MEMBERS
	{
		SRC_FL_VAL_1,   test_fl_val_1;
        SRC_FL_VAL_2,   test_fl_val_2;
        SRC_FL_VAL_3,   test_fl_val_3;
        SRC_FL_VAL_4,   test_fl_val_4;
    }
    LINE_COLOR  _RGB_NAVY;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_002_axis;
}

CHART 	tc_ch_002_chart
{
	LABEL	"TC_CH_002 Chart";
	HELP	"Chart Help: TC_CH_002";
	MEMBERS
	{
		TC_CH_002_SOURCE,   tc_ch_002_source;		
	}
    TYPE        STRIP;
    CYCLE_TIME  5000;
    LENGTH      30000;
}

MENU    tc_ch_002_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_fl_val_1,
        test_fl_val_2,
        test_fl_val_3,
        test_fl_val_4
    }
}

tc_ch_002_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_002_chart,
        ROWBREAK,
        tc_ch_002_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_002_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_002";
    REDEFINE ITEMS
    {
        tc_ch_002_input_group,
        ROWBREAK,
        tc_ch_002_methnvis_group
    }
}

tc_ch_002_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_002 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,5);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,3.5);
        status=put_float_value(ITEM_ID(test_fl_val_3),0,-2);
        status=put_float_value(ITEM_ID(test_fl_val_4),0,1);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_003                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with multiple sources.             */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_003_axis
{
	LABEL           "TC_CH_003 axis";
	MIN_VALUE       -100;
	MAX_VALUE        100;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text";
}

SOURCE  tc_ch_003_source1
{
    LABEL   "TC_CH_003 Source1";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_003_axis;
}

SOURCE  tc_ch_003_source2
{
    LABEL   "TC_CH_003 Source2";
    MEMBERS
    {
        SRC_HI_HI_LIMIT,    test_hi_hi_limit;
    }
    LINE_COLOR  _RGB_YELLOW;
    LINE_TYPE   HIGH_HIGH_LIMIT;
    Y_AXIS      tc_ch_003_axis;
}

SOURCE  tc_ch_003_source3
{
    LABEL   "TC_CH_003 Source3";
    MEMBERS
    {
        SRC_HI_LIMIT,   test_hi_limit;
    }
    LINE_COLOR  _RGB_PINK;
    LINE_TYPE   HIGH_LIMIT;
    Y_AXIS      tc_ch_003_axis;
}

SOURCE  tc_ch_003_source4
{
    LABEL   "TC_CH_003 Source4";
    MEMBERS
    {
        SRC_LO_LIMIT,   test_lo_limit;
    }
    LINE_COLOR  _RGB_TURQUOISE;
    LINE_TYPE   LOW_LIMIT;
    Y_AXIS      tc_ch_003_axis;
}

SOURCE  tc_ch_003_source5
{
    LABEL   "TC_CH_003 Source5";
    MEMBERS
    {
        SRC_LO_LO_LIMIT,    test_lo_lo_limit;
    }
    LINE_COLOR  _RGB_GREEN;
    LINE_TYPE   LOW_LOW_LIMIT;
    Y_AXIS      tc_ch_003_axis;
}

CHART 	tc_ch_003_chart
{
	LABEL	"TC_CH_003 Chart";
	HELP	"Chart Help: TC_CH_003";
	MEMBERS
	{
		TC_CH_003_SOURCE1,  tc_ch_003_source1;
        TC_CH_003_SOURCE2,  tc_ch_003_source2;
        TC_CH_003_SOURCE3,  tc_ch_003_source3;
        TC_CH_003_SOURCE4,  tc_ch_003_source4;
        TC_CH_003_SOURCE5,  tc_ch_003_source5;		
	}
    TYPE        SCOPE;
    CYCLE_TIME  1000;
    LENGTH      20000;
}

MENU    tc_ch_003_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_fl_val_1,
        ROWBREAK,
        test_hi_hi_limit,
        test_hi_limit,
        test_lo_limit,
        test_lo_lo_limit
    }
}

tc_ch_003_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_003_chart,
        ROWBREAK,
        tc_ch_003_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_003_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_003";
    REDEFINE ITEMS
    {
        tc_ch_003_input_group,
        ROWBREAK,
        tc_ch_003_methnvis_group
    }
}

tc_ch_003_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_003 - Set Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,50);
        status=put_float_value(ITEM_ID(test_hi_hi_limit),0,70);
        status=put_float_value(ITEM_ID(test_hi_limit),0,35);
        status=put_float_value(ITEM_ID(test_lo_limit),0,10);
        status=put_float_value(ITEM_ID(test_lo_lo_limit),0,-20);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_004                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_004_source
{
    LABEL   "TC_CH_004 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
}

CHART 	tc_ch_004_chart
{
	LABEL	"TC_CH_004 Chart";
	HELP	"Chart Help: TC_CH_004";
	MEMBERS
	{
		TC_CH_004_SOURCE,   tc_ch_004_source;		
	}
    TYPE    GAUGE;
}

tc_ch_004_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_004_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_004_chart,
        ROWBREAK,
        tc_ch_004_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_004_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_004";
    REDEFINE ITEMS
    {
        tc_ch_004_input_group,
        ROWBREAK,
        tc_ch_004_methnvis_group
    }
}

tc_ch_004_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_004 - Set Values";
    REDEFINE DEFINITION
    {
		int status;
        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,33);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_005                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_005_source
{
    LABEL   "TC_CH_005 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_MAROON;
}

CHART 	tc_ch_005_chart
{
	LABEL	"TC_CH_005 Chart";
	HELP	"Chart Help: TC_CH_005";
	MEMBERS
	{
		TC_CH_005_SOURCE,   tc_ch_005_source;		
	}
    TYPE    HORIZONTAL_BAR;
}

tc_ch_005_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_005_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_005_chart,
        ROWBREAK,
        tc_ch_005_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_005_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_005";
    REDEFINE ITEMS
    {
        tc_ch_005_input_group,
        ROWBREAK,
        tc_ch_005_methnvis_group
    }
}

tc_ch_005_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_005 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_006                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_006_source
{
    LABEL   "TC_CH_006 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_006_chart
{
	LABEL	"TC_CH_006 Chart";
	HELP	"Chart Help: TC_CH_006";
	MEMBERS
	{
		TC_CH_006_SOURCE,   tc_ch_006_source;		
	}
    TYPE    SWEEP;
    LENGTH      30000;
    CYCLE_TIME  5000;
}

tc_ch_006_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_006_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_006_chart,
        ROWBREAK,
        tc_ch_006_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_006_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_006";
    REDEFINE ITEMS
    {
        tc_ch_006_input_group,
        ROWBREAK,
        tc_ch_006_methnvis_group
    }
}

tc_ch_006_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_006 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_007                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_007_source
{
    LABEL   "TC_CH_007 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_BLUE;
}

CHART 	tc_ch_007_chart
{
	LABEL	"TC_CH_007 Chart";
	HELP	"Chart Help: TC_CH_007";
	MEMBERS
	{
		TC_CH_007_SOURCE,   tc_ch_007_source;		
	}
    TYPE    VERTICAL_BAR;
}

tc_ch_007_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_007_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_007_chart,
        ROWBREAK,
        tc_ch_007_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_007_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_007";
    REDEFINE ITEMS
    {
        tc_ch_007_input_group,
        ROWBREAK,
        tc_ch_007_methnvis_group
    }
}

tc_ch_007_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_007 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_008                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one source.                   */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_008_axis
{
	LABEL           "TC_CH_008 axis";
	MIN_VALUE       -100;
	MAX_VALUE        100;
	SCALING         LINEAR;
	CONSTANT_UNIT   "Constant Unit Text";
}

SOURCE  tc_ch_008_source
{
    LABEL   "TC_CH_008 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
    Y_AXIS      tc_ch_008_axis;
}

CHART 	tc_ch_008_chart
{
	LABEL	"TC_CH_008 Chart";
	HELP	"Chart Help: TC_CH_008";
	MEMBERS
	{
		TC_CH_008_SOURCE,   tc_ch_008_source;		
	}
    TYPE        STRIP;
    CYCLE_TIME  20;
    LENGTH      1000;
}

tc_ch_008_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_008_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_008_chart,
        ROWBREAK,
        tc_ch_008_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_008_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_008";
    REDEFINE ITEMS
    {
        tc_ch_008_input_group,
        ROWBREAK,
        tc_ch_008_methnvis_group
    }
}

tc_ch_008_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_008 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_009                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with multiple sources.             */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_009_axis1
{
	LABEL           "TC_CH_009 axis1";
	MIN_VALUE       -100;
	MAX_VALUE        100;
}

AXIS    tc_ch_009_axis2
{
	LABEL           "TC_CH_009 axis2";
	MIN_VALUE       0;
	MAX_VALUE       100;
}

AXIS    tc_ch_009_axis3
{
	LABEL           "TC_CH_009 axis3";
	MIN_VALUE       25;
	MAX_VALUE       50;
}

AXIS    tc_ch_009_axis4
{
	LABEL           "TC_CH_009 axis4";
	MIN_VALUE       0.4;
	MAX_VALUE       0.5;
}

SOURCE  tc_ch_009_source1
{
    LABEL   "TC_CH_009 Source1";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_009_axis1;
}

SOURCE  tc_ch_009_source2
{
    LABEL   "TC_CH_009 Source2";
    MEMBERS
    {
        SRC_FL_VAL_2,   test_fl_val_2;
    }
    LINE_COLOR  _RGB_PINK;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_009_axis2;
}

SOURCE  tc_ch_009_source3
{
    LABEL   "TC_CH_009 Source3";
    MEMBERS
    {
        SRC_FL_VAL_3,   test_fl_val_3;
    }
    LINE_COLOR  _RGB_YELLOW;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_009_axis3;
}

SOURCE  tc_ch_009_source4
{
    LABEL   "TC_CH_009 Source4";
    MEMBERS
    {
        SRC_FL_VAL_4,   test_fl_val_4;
    }
    LINE_COLOR  _RGB_TURQUOISE;
    LINE_TYPE   DATA;
    Y_AXIS      tc_ch_009_axis4;
}

CHART 	tc_ch_009_chart
{
	LABEL	"TC_CH_009 Chart";
	HELP	"Chart Help: TC_CH_009";
	MEMBERS
	{
		TC_CH_009_SOURCE1,  tc_ch_009_source1;
        TC_CH_009_SOURCE2,  tc_ch_009_source2;
        TC_CH_009_SOURCE3,  tc_ch_009_source3;
        TC_CH_009_SOURCE4,  tc_ch_009_source4;		
	}
    TYPE        SCOPE;
    CYCLE_TIME  1000;
    LENGTH      20000;
}

tc_ch_009_input_group LIKE MENU tc_ch_002_input_group { REDEFINE LABEL   "Input"; }

tc_ch_009_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_009_chart,
        ROWBREAK,
        tc_ch_009_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_009_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_009";
    REDEFINE ITEMS
    {
        tc_ch_009_input_group,
        ROWBREAK,
        tc_ch_009_methnvis_group
    }
}

tc_ch_009_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_009 - Set Values";
    REDEFINE DEFINITION
    {
        long status;
        float val1, val2, val3, val4;

        send_on_exit();

        status=get_float_value(ITEM_ID(test_fl_val_1),0,&val1);
        status=get_float_value(ITEM_ID(test_fl_val_2),0,&val2);
        status=get_float_value(ITEM_ID(test_fl_val_3),0,&val3);
        status=get_float_value(ITEM_ID(test_fl_val_4),0,&val4);

        if((val1<-25)||(val1>75))
            val1=75;
        else
            val1=val1-25;

        if((val2<20)||(val2>80))
            val2=20;
        else
            val2=val2+10;

        if((val3<30)||(val3>50))
            val3=50;
        else
            val3=val3-5;

        if((val4<0.41)||(val4>0.49))
            val4=0.41;
        else
            val4=val4+0.01;

        status=put_float_value(ITEM_ID(test_fl_val_1),0,val1);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,val2);
        status=put_float_value(ITEM_ID(test_fl_val_3),0,val3);
        status=put_float_value(ITEM_ID(test_fl_val_4),0,val4);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_010                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with a long length.                */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_010_axis
{
	LABEL           "TC_CH_010 axis";
	MIN_VALUE       -100;
	MAX_VALUE        100;
}

SOURCE  tc_ch_010_source
{
    LABEL   "TC_CH_010 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
    Y_AXIS      tc_ch_010_axis;
}

CHART 	tc_ch_010_chart
{
	LABEL	"TC_CH_010 Chart";
	HELP	"Chart Help: TC_CH_010";
	MEMBERS
	{
		TC_CH_010_SOURCE,   tc_ch_010_source;		
	}
    TYPE        STRIP;
    CYCLE_TIME  1000;
    LENGTH      86400000;
}

tc_ch_010_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_010_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_010_chart,
        ROWBREAK,
        tc_ch_010_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_010_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_010";
    REDEFINE ITEMS
    {
        tc_ch_010_input_group,
        ROWBREAK,
        tc_ch_010_methnvis_group
    }
}

tc_ch_010_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_010 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_011                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of XX_SMALL can be displayed.           */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_011_source
{
    LABEL   "TC_CH_011 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_011_chart
{
	LABEL	"TC_CH_011 Chart";
	HELP	"Chart Help: TC_CH_011";
	MEMBERS
	{
		TC_CH_011_SOURCE,   tc_ch_011_source;		
	}
    WIDTH   XX_SMALL;
	HEIGHT  XX_SMALL;
}

tc_ch_011_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_011_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_011_chart,
        ROWBREAK,
        tc_ch_011_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_011_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_011";
    REDEFINE ITEMS
    {
        tc_ch_011_input_group,
        ROWBREAK,
        tc_ch_011_methnvis_group
    }
}

tc_ch_011_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_011 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_012                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of X_SMALL can be displayed.            */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_012_source
{
    LABEL   "TC_CH_012 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_PINK;
}

CHART 	tc_ch_012_chart
{
	LABEL	"TC_CH_012 Chart";
	HELP	"Chart Help: TC_CH_012";
	MEMBERS
	{
		TC_CH_012_SOURCE,   tc_ch_012_source;		
	}
    WIDTH   X_SMALL;
	HEIGHT  X_SMALL;
}

tc_ch_012_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_012_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_012_chart,
        ROWBREAK,
        tc_ch_012_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_012_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_012";
    REDEFINE ITEMS
    {
        tc_ch_012_input_group,
        ROWBREAK,
        tc_ch_012_methnvis_group
    }
}

tc_ch_012_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_012 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_013                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of SMALL can be displayed.              */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_013_source
{
    LABEL   "TC_CH_013 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_PINK;
}

CHART 	tc_ch_013_chart
{
	LABEL	"TC_CH_013 Chart";
	HELP	"Chart Help: TC_CH_013";
	MEMBERS
	{
		TC_CH_013_SOURCE,   tc_ch_013_source;		
	}
    WIDTH   SMALL;
	HEIGHT  SMALL;
}

tc_ch_013_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_013_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_013_chart,
        ROWBREAK,
        tc_ch_013_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_013_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_013";
    REDEFINE ITEMS
    {
        tc_ch_013_input_group,
        ROWBREAK,
        tc_ch_013_methnvis_group
    }
}

tc_ch_013_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_013 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_014                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of MEDIUM can be displayed.             */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_014_source
{
    LABEL   "TC_CH_014 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_014_chart
{
	LABEL	"TC_CH_014 Chart";
	HELP	"Chart Help: TC_CH_014";
	MEMBERS
	{
		TC_CH_014_SOURCE,   tc_ch_014_source;		
	}
    WIDTH   MEDIUM;
	HEIGHT  MEDIUM;
}

tc_ch_014_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_014_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_014_chart,
        ROWBREAK,
        tc_ch_014_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_014_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_014";
    REDEFINE ITEMS
    {
        tc_ch_014_input_group,
        ROWBREAK,
        tc_ch_014_methnvis_group
    }
}

tc_ch_014_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_014 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_015                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of LARGE can be displayed.              */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_015_source
{
    LABEL   "TC_CH_015 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_015_chart
{
	LABEL	"TC_CH_015 Chart";
	HELP	"Chart Help: TC_CH_015";
	MEMBERS
	{
		TC_CH_015_SOURCE,   tc_ch_015_source;		
	}
    WIDTH   LARGE;
	HEIGHT  LARGE;
}

tc_ch_015_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_015_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_015_chart,
        ROWBREAK,
        tc_ch_015_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_015_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_015";
    REDEFINE ITEMS
    {
        tc_ch_015_input_group,
        ROWBREAK,
        tc_ch_015_methnvis_group
    }
}

tc_ch_015_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_015 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_016                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of X_LARGE can be displayed.            */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_016_source
{
    LABEL   "TC_CH_016 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_016_chart
{
	LABEL	"TC_CH_016 Chart";
	HELP	"Chart Help: TC_CH_016";
	MEMBERS
	{
		TC_CH_016_SOURCE,   tc_ch_016_source;		
	}
    WIDTH   X_LARGE;
	HEIGHT  X_LARGE;
}

tc_ch_016_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_016_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_016_chart,
        ROWBREAK,
        tc_ch_016_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_016_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_016";
    REDEFINE ITEMS
    {
        tc_ch_016_input_group,
        ROWBREAK,
        tc_ch_016_methnvis_group
    }
}

tc_ch_016_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_016 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_017                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with a size of XX_LARGE can be displayed.           */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_017_source
{
    LABEL   "TC_CH_017 Source";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    LINE_COLOR  _RGB_NAVY;
}

CHART 	tc_ch_017_chart
{
	LABEL	"TC_CH_017 Chart";
	HELP	"Chart Help: TC_CH_017";
	MEMBERS
	{
		TC_CH_017_SOURCE,   tc_ch_017_source;		
	}
    WIDTH   XX_LARGE;
	HEIGHT  XX_LARGE;
}

tc_ch_017_input_group LIKE MENU tc_ch_001_input_group { REDEFINE LABEL   "Input"; }

tc_ch_017_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_017_chart,
        ROWBREAK,
        tc_ch_017_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_017_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_017";
    REDEFINE ITEMS
    {
        tc_ch_017_input_group,
        ROWBREAK,
        tc_ch_017_methnvis_group
    }
}

tc_ch_017_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{    REDEFINE LABEL  "TC_CH_017 - Set Values";      }

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_018                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart with DATA1 and DATA2 can be displayed.              */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_018_axis
{
	LABEL           "TC_CH_018 axis";
	MIN_VALUE       -25;
	MAX_VALUE        25;
}

SOURCE  tc_ch_018_source1
{
    LABEL   "TC_CH_018 Source1";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
    Y_AXIS      tc_ch_018_axis;
    LINE_COLOR  _RGB_NAVY;
    LINE_TYPE   DATA1;
	INIT_ACTIONS {tc_ch_018_srce_init_method}
	REFRESH_ACTIONS {tc_ch_018_set_vals_method}
}

SOURCE  tc_ch_018_source2
{
    LABEL   "TC_CH_018 Source2";
    MEMBERS
    {
        SRC_FL_VAL_2,   test_fl_val_2;
    }
    Y_AXIS      tc_ch_018_axis;
    LINE_COLOR  _RGB_PINK;
    LINE_TYPE   DATA2;
}

CHART 	tc_ch_018_chart
{
	LABEL	"TC_CH_018 Chart";
	HELP	"Chart Help: TC_CH_018";
	MEMBERS
	{
		TC_CH_018_SOURCE1,  tc_ch_018_source1;
        TC_CH_018_SOURCE2,  tc_ch_018_source2;		
	}
    WIDTH   XX_LARGE;
	HEIGHT  XX_LARGE;
	LENGTH  8000;
	CYCLE_TIME	400;
}

MENU    tc_ch_018_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_fl_val_1,
        test_fl_val_2
    }
}

tc_ch_018_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_018_chart,
        ROWBREAK,
        tc_ch_018_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_018_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_018";
    REDEFINE ITEMS
    {
        tc_ch_018_input_group,
        ROWBREAK,
        tc_ch_018_methnvis_group
    }
}
METHOD  tc_ch_018_srce_init_method
{
	LABEL   "TC_CH_018 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;

        send_on_exit();
        status=put_float_value(ITEM_ID(test_fl_val_1),0, 0.0);
        status=put_float_value(ITEM_ID(test_fl_val_2),0, 0.0);
    }
}

tc_ch_018_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_018 - Set Values";
    REDEFINE DEFINITION
    {
        long status;
        float val1, val2;

        send_on_exit();

        status=get_float_value(ITEM_ID(test_fl_val_1),0,&val1);
        status=get_float_value(ITEM_ID(test_fl_val_2),0,&val2);

        if((val1<-20)||(val1>20))
            val1=-20;
        else
            val1=val1+5;

        if((val2<-20)||(val2>20))
            val2=20;
        else
            val2=val2-2;

        status=put_float_value(ITEM_ID(test_fl_val_1),0,val1);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,val2);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_019                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with one-byte sources.             */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_019_axis
{
	LABEL           "TC_CH_019 axis";
	MIN_VALUE       -25;
	MAX_VALUE        25;
}

SOURCE  tc_ch_019_source1
{
    LABEL   "TC_CH_019 Source1";
    MEMBERS
    {
        SRC_VAL_INT8,   test_val_int_8;
    }
    Y_AXIS      tc_ch_019_axis;
    LINE_COLOR  _RGB_NAVY;
	INIT_ACTIONS {tc_ch_019_srce_init_method}
	REFRESH_ACTIONS {tc_ch_019_set_vals_method}

}

SOURCE  tc_ch_019_source2
{
    LABEL   "TC_CH_019 Source2";
    MEMBERS
    {
        SRC_VAL_UINT8,  test_val_uint_8;
    }
    Y_AXIS      tc_ch_019_axis;
    LINE_COLOR  _RGB_PINK;
}

CHART 	tc_ch_019_chart
{
	LABEL	"TC_CH_019 Chart";
	HELP	"Chart Help: TC_CH_019";
	MEMBERS
	{
		TC_CH_019_SOURCE1,  tc_ch_019_source1;
        TC_CH_019_SOURCE2,  tc_ch_019_source2;		
	}
	LENGTH 10000;
	CYCLE_TIME 500;
}

MENU    tc_ch_019_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_val_int_8,
        test_val_uint_8
    }
}

tc_ch_019_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_019_chart,
        ROWBREAK,
        tc_ch_019_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_019_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_019";
    REDEFINE ITEMS
    {
        tc_ch_019_input_group,
        ROWBREAK,
        tc_ch_019_methnvis_group
    }
}

METHOD  tc_ch_019_srce_init_method
{
	LABEL   "TC_CH_019 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;

        send_on_exit();
        status=put_signed_value(ITEM_ID(test_val_int_8),0, 0);
        status=put_unsigned_value(ITEM_ID(test_val_uint_8),0, 0);
    }
}


tc_ch_019_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_019 - Set Values";
    REDEFINE DEFINITION
    {
        long status, val1;
        unsigned long val2;

        send_on_exit();

        status=get_signed_value(ITEM_ID(test_val_int_8),0,&val1);
        status=get_unsigned_value(ITEM_ID(test_val_uint_8),0,&val2);

        if((val1<-20)||(val1>20))
            val1=-20;
        else
            val1=val1+5;

        if(val2>20)
            val2=20;
        else
            val2=val2-2;

        status=put_signed_value(ITEM_ID(test_val_int_8),0,val1);
        status=put_unsigned_value(ITEM_ID(test_val_uint_8),0,val2);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_020                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with four-byte sources.            */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_020_axis
{
	LABEL           "TC_CH_020 axis";
	MIN_VALUE       -25;
	MAX_VALUE        25;
}

SOURCE  tc_ch_020_source1
{
    LABEL   "TC_CH_020 Source1";
    MEMBERS
    {
        SRC_VAL_INT32,  test_val_int_32;
    }
    Y_AXIS      tc_ch_020_axis;
    LINE_COLOR  _RGB_RED;
    EMPHASIS    TRUE;
	INIT_ACTIONS {tc_ch_020_srce_init_method}
	REFRESH_ACTIONS {tc_ch_020_set_vals_method}
}

SOURCE  tc_ch_020_source2
{
    LABEL   "TC_CH_020 Source2";
    MEMBERS
    {
        SRC_VAL_UINT32, test_val_uint_32;
    }
    Y_AXIS      tc_ch_020_axis;
    LINE_COLOR  _RGB_GREEN;
}

CHART 	tc_ch_020_chart
{
	LABEL	"TC_CH_020 Chart";
	HELP	"Chart Help: TC_CH_020";
	MEMBERS
	{
		TC_CH_020_SOURCE1,  tc_ch_020_source1;
        TC_CH_020_SOURCE2,  tc_ch_020_source2;		
	}
	LENGTH 20000;
	CYCLE_TIME 1000;
}

MENU    tc_ch_020_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_val_int_32,
        test_val_uint_32
    }
}

tc_ch_020_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_020_chart,
        ROWBREAK,
        tc_ch_020_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_020_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_020";
    REDEFINE ITEMS
    {
        tc_ch_020_input_group,
        ROWBREAK,
        tc_ch_020_methnvis_group
    }
}

METHOD  tc_ch_020_srce_init_method
{
	LABEL   "TC_CH_020 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;

        send_on_exit();
        status=put_signed_value(ITEM_ID(test_val_int_32),0, 0);
        status=put_unsigned_value(ITEM_ID(test_val_uint_32),0, 0);
    }
}


tc_ch_020_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_020 - Set Values";
    REDEFINE DEFINITION
    {
        long status, val1;
        unsigned long val2;

        send_on_exit();

        status=get_signed_value(ITEM_ID(test_val_int_32),0,&val1);
        status=get_unsigned_value(ITEM_ID(test_val_uint_32),0,&val2);

        if((val1<-20)||(val1>20))
            val1=-20;
        else
            val1=val1+5;

        if(val2>20)
            val2=20;
        else
            val2=val2-2;

        status=put_signed_value(ITEM_ID(test_val_int_32),0,val1);
        status=put_unsigned_value(ITEM_ID(test_val_uint_32),0,val2);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_021                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with source action methods.        */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_021_axis
{
	LABEL           "TC_CH_021 axis";
	MIN_VALUE       -500;
	MAX_VALUE        500;
}

SOURCE  tc_ch_021_source1
{
    LABEL   "TC_CH_021 Source1";
    MEMBERS
    {
        SRC_VAL_INT8,   test_val_int_8;
    }
    LINE_COLOR  _RGB_NAVY;
    Y_AXIS      tc_ch_021_axis;
    INIT_ACTIONS    {   tc_ch_021_srce_init_method      }
    REFRESH_ACTIONS {   tc_ch_021_srce_refresh_method   }
	EXIT_ACTIONS    {   tc_ch_021_srce_exit_method      }
}

SOURCE  tc_ch_021_source2
{
    LABEL   "TC_CH_021 Source2";
    MEMBERS
    {
        SRC_HI_LIMIT,   test_hi_limit;
    }
    LINE_COLOR  _RGB_YELLOW;
    Y_AXIS      tc_ch_021_axis;
}

SOURCE  tc_ch_021_source3
{
    LABEL   "TC_CH_021 Source3";
    MEMBERS
    {
        SRC_LO_LIMIT,   test_lo_limit;
    }
    LINE_COLOR  _RGB_PINK;
    Y_AXIS      tc_ch_021_axis;
}

CHART 	tc_ch_021_chart
{
	LABEL	"TC_CH_021 Chart";
	HELP	"Chart Help: TC_CH_021";
	MEMBERS
	{
		TC_CH_021_SOURCE1,  tc_ch_021_source1;
        TC_CH_021_SOURCE2,  tc_ch_021_source2;
        TC_CH_021_SOURCE3,  tc_ch_021_source3;		
	}
    CYCLE_TIME  1000;
    LENGTH      60000;
}

MENU    tc_ch_021_input_group
{
    LABEL   "Input";
    STYLE   GROUP;
    ITEMS
    {
        test_val_int_8,
        ROWBREAK,
        test_hi_limit,
        test_lo_limit
    }
}

tc_ch_021_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_021_chart
    }
}

tc_ch_021_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_021";
    REDEFINE ITEMS
    {
        tc_ch_021_input_group,
        ROWBREAK,
        tc_ch_021_methnvis_group
    }
}

METHOD  tc_ch_021_srce_init_method
{
	LABEL   "TC_CH_021 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;

        send_on_exit();

        #if 0

        status=put_float_value(ITEM_ID(test_lo_limit),0,-500);
        status=put_float_value(ITEM_ID(test_hi_limit),0,500);
        status=put_signed_value(ITEM_ID(test_val_int_8),0,-50);

        #else

        PARAM.TEST_LO_LIMIT = -300;
        PARAM.TEST_HI_LIMIT = 300;
        PARAM.TEST_VAL_INT_8 = -50;

        #endif
    }
}

METHOD  tc_ch_021_srce_refresh_method
{
	LABEL   "TC_CH_021 Source Refresh Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status, value;

        send_on_exit();

        #if 0

        status=get_signed_value(ITEM_ID(test_val_int_8),0,&value);

        value=value+5;

        if(value > 50)
            status=put_signed_value(ITEM_ID(test_val_int_8),0,-50);
        else
            status=put_signed_value(ITEM_ID(test_val_int_8),0,value);

        #else

        PARAM.TEST_VAL_INT_8 += 5;

        if(PARAM.TEST_VAL_INT_8 > 50)
            PARAM.TEST_VAL_INT_8 = -50;

        #endif
    }
}

METHOD  tc_ch_021_srce_exit_method
{
	LABEL   "TC_CH_021 Source Exit Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Source Exit Method Worked Properly!",ids,indices,0);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_022                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with source action methods.        */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_022_axis
{
	LABEL           "TC_CH_022 axis";
	MIN_VALUE       -30;
	MAX_VALUE        30;
}

SOURCE  tc_ch_022_source1
{
    LABEL   "TC_CH_022 Source1";
    MEMBERS
    {
        SRC_LOC_FL_VAL, LOCAL_PARAM.LOCAL_FL_VAL;
    }
    LINE_COLOR  _RGB_NAVY;
    Y_AXIS      tc_ch_022_axis;
    INIT_ACTIONS    {   tc_ch_022_srce_init_method      }
    REFRESH_ACTIONS {   tc_ch_022_srce_refresh_method   }
	EXIT_ACTIONS    {   tc_ch_022_srce_exit_method      }
}

CHART 	tc_ch_022_chart
{
	LABEL	"TC_CH_022 Chart";
	HELP	"Chart Help: TC_CH_022";
	MEMBERS
	{
		TC_CH_022_SOURCE1,  tc_ch_022_source1;
    }
    CYCLE_TIME  1000;
    LENGTH      30000;
}

tc_ch_022_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_022_chart
     }
}

tc_ch_022_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_022";
    REDEFINE ITEMS
    {
        tc_ch_022_methnvis_group
    }
}

METHOD  tc_ch_022_srce_init_method
{
	LABEL   "TC_CH_022 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        send_on_exit();

        LOCAL_PARAM.LOCAL_FL_VAL=-50;
    }
}

METHOD  tc_ch_022_srce_refresh_method
{
	LABEL   "TC_CH_022 Source Refresh Method";
	CLASS   INPUT;
	DEFINITION
	{
        send_on_exit();

        LOCAL_PARAM.LOCAL_FL_VAL+=20;

        if(LOCAL_PARAM.LOCAL_FL_VAL > 50)
            LOCAL_PARAM.LOCAL_FL_VAL=-50;    
    }
}

METHOD  tc_ch_022_srce_exit_method
{
	LABEL   "TC_CH_022 Source Exit Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Source Exit Method Worked Properly!",ids,indices,0);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_023                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that two charts can be displayed in a window.                    */
/*                                                                           */
/*****************************************************************************/
SOURCE  tc_ch_023_source1
{
    LABEL   "TC_CH_023 Source1";
    MEMBERS
    {
        SRC_FL_VAL_1,   test_fl_val_1;
    }
	INIT_ACTIONS { tc_ch_023_init_vals_method }
    REFRESH_ACTIONS { tc_ch_023_set_vals_method }
}

SOURCE  tc_ch_023_source2
{
    LABEL   "TC_CH_023 Source2";
    MEMBERS
    {
        SRC_FL_VAL_2,   test_fl_val_2;
    }
}

CHART 	tc_ch_023_chart1
{
	LABEL	"TC_CH_023 Chart1";
	HELP	"Chart Help: TC_CH_023";
	MEMBERS
	{
		TC_CH_023_SOURCE1,  tc_ch_023_source1;
    }
    WIDTH   MEDIUM;
	HEIGHT  MEDIUM;
	CYCLE_TIME 100;
	LENGTH 2000;
}

CHART 	tc_ch_023_chart2
{
	LABEL	"TC_CH_023 Chart2";
	HELP	"Chart Help: TC_CH_023";
	MEMBERS
	{
		TC_CH_023_SOURCE2,  tc_ch_023_source2;
    }
    WIDTH   LARGE;
	HEIGHT  LARGE;
	CYCLE_TIME 100;
	LENGTH 2000;
}

MENU    tc_ch_023_window
{
    LABEL   "TC_CCH_023 Window";
    STYLE   WINDOW;
    ITEMS
    {
        tc_ch_023_chart1,
        tc_ch_023_chart2
    }
}    

tc_ch_023_input_group LIKE MENU tc_ch_018_input_group { REDEFINE LABEL   "Input"; }

tc_ch_023_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_023_window,
        ROWBREAK,
        tc_ch_023_init_vals_method,
        tc_ch_023_set_vals_method,
        clear_test_vals_visualtb
    }
}

tc_ch_023_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_023";
    REDEFINE ITEMS
    {
        tc_ch_023_input_group,
        ROWBREAK,
        tc_ch_023_methnvis_group
    }
}

tc_ch_023_init_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_023 - Init Values";
    REDEFINE DEFINITION
    {
        long status;

        send_on_exit();

        status=put_float_value(ITEM_ID(test_fl_val_1),0,0.0);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,0.0);
    }
}

tc_ch_023_set_vals_method LIKE METHOD tc_ch_001_set_vals_method
{
    REDEFINE LABEL  "TC_CH_023 - Set Values";
    REDEFINE DEFINITION
    {
        long status;
        float val1, val2;

        send_on_exit();

        status=get_float_value(ITEM_ID(test_fl_val_1),0,&val1);
        status=get_float_value(ITEM_ID(test_fl_val_2),0,&val2);

        if((val1<-20)||(val1>20))
            val1=-20;
        else
            val1=val1+5;

        if((val2<-20)||(val2>20))
            val2=20;
        else
            val2=val2-2;

        status=put_float_value(ITEM_ID(test_fl_val_1),0,val1);
        status=put_float_value(ITEM_ID(test_fl_val_2),0,val2);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_CH_024                                                               */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Chart                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a chart can be displayed with a local variable.             */
/*                                                                           */
/*****************************************************************************/
AXIS    tc_ch_024_axis
{
	LABEL           "TC_CH_024 axis";
	MIN_VALUE       1;
	MAX_VALUE       100;
    SCALING         LOGARITHMIC;
}

SOURCE  tc_ch_024_source
{
    LABEL   "TC_CH_024 Source";
    MEMBERS
    {
        SRC_LOC_FL_VAL, LOCAL_PARAM.LOCAL_FL_VAL;
    }
    LINE_COLOR  _RGB_NAVY;
    Y_AXIS      tc_ch_024_axis;
    INIT_ACTIONS    {   tc_ch_024_srce_init_method      }
    REFRESH_ACTIONS {   tc_ch_024_srce_refresh_method   }
	EXIT_ACTIONS    {   tc_ch_024_srce_exit_method      }
}

CHART 	tc_ch_024_chart
{
	LABEL	"TC_CH_024 Chart";
	HELP	"Chart Help: TC_CH_024";
	MEMBERS
	{
		TC_CH_024_SOURCE,   tc_ch_024_source;
    }
    CYCLE_TIME  1000;
    LENGTH      60000;
}

tc_ch_024_methnvis_group LIKE MENU tc_ch_001_methnvis_group
{
    REDEFINE ITEMS
    {
        tc_ch_024_chart
    }
}

tc_ch_024_page LIKE MENU tc_ch_001_page
{
    REDEFINE LABEL  "TC_CH_024";
    REDEFINE ITEMS
    {
        tc_ch_024_methnvis_group
    }
}

METHOD  tc_ch_024_srce_init_method
{
	LABEL   "TC_CH_024 Source Init Method";
	CLASS   INPUT;
	DEFINITION
	{
        send_on_exit();

        LOCAL_PARAM.LOCAL_FL_VAL=1;
    }
}

METHOD  tc_ch_024_srce_refresh_method
{
	LABEL   "TC_CH_024 Source Refresh Method";
	CLASS   INPUT;
	DEFINITION
	{
        send_on_exit();

        LOCAL_PARAM.LOCAL_FL_VAL+=10;

        if(LOCAL_PARAM.LOCAL_FL_VAL > 100)
            LOCAL_PARAM.LOCAL_FL_VAL=1;
    }
}

METHOD  tc_ch_024_srce_exit_method
{
	LABEL   "TC_CH_024 Source Exit Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Source Exit Method Worked Properly!",ids,indices,0);
    }
}

/***********************************************************************/

#endif

