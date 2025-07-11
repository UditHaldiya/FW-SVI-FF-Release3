/*****************************************************************************/
/* 1000_Visualizations.ddl                                                   */
/*                                                                           */
/*   This DDL file contains all the visualization and supporting constructs  */
/*   for all the blocks.  Visualizations only active for DD5 profile.        */
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
** Visualization constructs for CondTB1                                                                
******************************************************************************
*/

WAVEFORM    test_waveform_condtb1
{
    LABEL   "Test Waveform";
    TYPE    YT
    {
        X_INITIAL   0;
        X_INCREMENT 1;
        Y_VALUES
        {
            test_input_var
        }    
    }
    LINE_COLOR
        SELECT (test_input_var) 
 		{
			CASE _DISPLAY_FORMAT_1:     _RGB_WHITE;
            CASE _DISPLAY_FORMAT_2:     _RGB_GREY;
            CASE _EDIT_FORMAT_1:        _RGB_BLUE;
            CASE _EDIT_FORMAT_2:        _RGB_CYAN;
            CASE _MIN_VALUE_1:          _RGB_GREEN;
            CASE _MIN_VALUE_2:          _RGB_YELLOW;
            CASE _MAX_VALUE_1:          _RGB_BROWN;
            CASE _MAX_VALUE_2:          _RGB_ORANGE;
            CASE _ENUMERATED_1:         _RGB_RED;
            CASE _ENUMERATED_2:         _RGB_PINK;
            CASE _BIT_ENUMERATED_1:     _RGB_MAROON;
            CASE _BIT_ENUMERATED_2:     _RGB_VIOLET;
            CASE _CONSTANT_UNIT_1:      _RGB_PURPLE;
            CASE _CONSTANT_UNIT_2:      _RGB_AZURE;
            CASE _HANDLING_1:           _RGB_NAVY;
            CASE _HANDLING_2:           _RGB_TURQUOISE;
            CASE _VALIDITY_1:           _RGB_KHAKI;
            CASE _VALIDITY_2:           _RGB_GOLD;
            DEFAULT:                    _RGB_BLACK;
        }
    Y_AXIS  y_axis_condtb1;  
}

SOURCE  test_source_condtb1
{
    LABEL   "Test Source";
    MEMBERS
    {
        TEST_SRC_IN_VAR,    test_input_var;
    }
    LINE_COLOR
        SELECT (test_input_var) 
 		{
			CASE _DISPLAY_FORMAT_1:     _RGB_WHITE;
            CASE _DISPLAY_FORMAT_2:     _RGB_GREY;
            CASE _EDIT_FORMAT_1:        _RGB_BLUE;
            CASE _EDIT_FORMAT_2:        _RGB_CYAN;
            CASE _MIN_VALUE_1:          _RGB_GREEN;
            CASE _MIN_VALUE_2:          _RGB_YELLOW;
            CASE _MAX_VALUE_1:          _RGB_BROWN;
            CASE _MAX_VALUE_2:          _RGB_ORANGE;
            CASE _ENUMERATED_1:         _RGB_RED;
            CASE _ENUMERATED_2:         _RGB_PINK;
            CASE _BIT_ENUMERATED_1:     _RGB_MAROON;
            CASE _BIT_ENUMERATED_2:     _RGB_VIOLET;
            CASE _CONSTANT_UNIT_1:      _RGB_PURPLE;
            CASE _CONSTANT_UNIT_2:      _RGB_AZURE;
            CASE _HANDLING_1:           _RGB_NAVY;
            CASE _HANDLING_2:           _RGB_TURQUOISE;
            CASE _VALIDITY_1:           _RGB_KHAKI;
            CASE _VALIDITY_2:           _RGB_GOLD;
            DEFAULT:                    _RGB_BLACK;
        }
    Y_AXIS  y_axis_condtb1;
}     

AXIS    test_x_axis_condtb1
{
    LABEL   "Test Axis";
    HELP    "Axis MIN & MAX values used for conditional testing.";

    MIN_VALUE
        SELECT (test_input_var) 
 		{
			CASE _DISPLAY_FORMAT_1:     _DISPLAY_FORMAT_1;
            CASE _DISPLAY_FORMAT_2:     _DISPLAY_FORMAT_2;
            CASE _EDIT_FORMAT_1:        _EDIT_FORMAT_1;
            CASE _EDIT_FORMAT_2:        _EDIT_FORMAT_2;
            CASE _MIN_VALUE_1:          _MIN_VALUE_1;
            CASE _MIN_VALUE_2:          _MIN_VALUE_2;
            CASE _MAX_VALUE_1:          _MAX_VALUE_1;
            CASE _MAX_VALUE_2:          _MAX_VALUE_2;
            CASE _ENUMERATED_1:         _ENUMERATED_1;
            CASE _ENUMERATED_2:         _ENUMERATED_2;
            CASE _BIT_ENUMERATED_1:     _BIT_ENUMERATED_1;
            CASE _BIT_ENUMERATED_2:     _BIT_ENUMERATED_2;
            CASE _CONSTANT_UNIT_1:      _CONSTANT_UNIT_1;
            CASE _CONSTANT_UNIT_2:      _CONSTANT_UNIT_2;
            CASE _HANDLING_1:           _HANDLING_1;
            CASE _HANDLING_2:           _HANDLING_2;
            CASE _VALIDITY_1:           _VALIDITY_1;
            CASE _VALIDITY_2:           _VALIDITY_2;
            DEFAULT:                    0;
        }
        
    MAX_VALUE
        SELECT (test_input_var) 
 		{
			CASE _DISPLAY_FORMAT_1:     _DISPLAY_FORMAT_1   +10;
            CASE _DISPLAY_FORMAT_2:     _DISPLAY_FORMAT_2   +10;
            CASE _EDIT_FORMAT_1:        _EDIT_FORMAT_1      +10;
            CASE _EDIT_FORMAT_2:        _EDIT_FORMAT_2      +10;
            CASE _MIN_VALUE_1:          _MIN_VALUE_1        +10;
            CASE _MIN_VALUE_2:          _MIN_VALUE_2        +10;
            CASE _MAX_VALUE_1:          _MAX_VALUE_1        +10;
            CASE _MAX_VALUE_2:          _MAX_VALUE_2        +10;
            CASE _ENUMERATED_1:         _ENUMERATED_1       +10;
            CASE _ENUMERATED_2:         _ENUMERATED_2       +10;
            CASE _BIT_ENUMERATED_1:     _BIT_ENUMERATED_1   +10;
            CASE _BIT_ENUMERATED_2:     _BIT_ENUMERATED_2   +10;
            CASE _CONSTANT_UNIT_1:      _CONSTANT_UNIT_1    +10;
            CASE _CONSTANT_UNIT_2:      _CONSTANT_UNIT_2    +10;
            CASE _HANDLING_1:           _HANDLING_1         +10;
            CASE _HANDLING_2:           _HANDLING_2         +10;
            CASE _VALIDITY_1:           _VALIDITY_1         +10;
            CASE _VALIDITY_2:           _VALIDITY_2         +10;
            DEFAULT:                    10;
        }
}

AXIS    y_axis_condtb1
{
    LABEL   "Y-Axis";
    MIN_VALUE   0;
    MAX_VALUE   _NUM_OF_CONDITIONAL_OPTIONS + 1;
}

GRAPH   test_graph_condtb1
{
    LABEL   "Test Graph";
    MEMBERS
    {
        TEST_WAVEFORM,  test_waveform_condtb1;
    }  
    X_AXIS  test_x_axis_condtb1;
}

CHART   test_chart_condtb1
{
    LABEL   "Test Chart";
    MEMBERS
    {
        TEST_SOURCE,    test_source_condtb1;
    }
}  

/*
******************************************************************************
** Visualization constructs for ChannelTB                                                                
******************************************************************************
*/

AXIS    channeltb_ai_pv_y_axis
{
    LABEL       "AI Channel PV Axis";
    HELP        "Axis is dynamically set to +/-1 of PV Range MAX/MIN.";
    MIN_VALUE   PARAM.PRIMARY_VALUE_RANGE_AI.EU_0 - 1.0;
    MAX_VALUE   PARAM.PRIMARY_VALUE_RANGE_AI.EU_100 + 1.0;
}

AXIS    channeltb_di_pv_y_axis
{
    LABEL       "DI Channel PV Axis";
    HELP        "Axis is conditionaly set to +/-1 of value range based on channel function.";
    MIN_VALUE   -1;
    MAX_VALUE
        IF(PARAM.DI_FUNCTION==2)    {256;}
        ELSE                        {2;}
}

AXIS    channeltb_mai_pv_y_axis
{
    LABEL       "MAI Channel PV Axis";
    HELP        "Axis is dynamically set to +/-1 of PV Range MAX/MIN.";
    MIN_VALUE   PARAM.PRIMARY_VALUE_RANGE_MAI.EU_0 - 1.0;
    MAX_VALUE   PARAM.PRIMARY_VALUE_RANGE_MAI.EU_100 + 1.0;
}

AXIS    channeltb_mdi_pv_y_axis
{
    LABEL       "MDI Channel PV Axis";
    HELP        "Axis is conditionaly set to +/-1 of value range based on channel function.";
    MIN_VALUE   -1;
    MAX_VALUE
        IF(PARAM.MDI_FUNCTION==2)   {256;}
        ELSE                        {2;}
}
    
SOURCE  channeltb_ai_pv_source
{
    LABEL   "AI Channel PV Source";
    HELP    "The simulated PV for the AI Channel based on AI_FUNCTION and PV Range.";
    Y_AXIS  channeltb_ai_pv_y_axis;
    MEMBERS {   AI_PV_SRC,  PARAM.PRIMARY_VALUE_AI.VALUE; }
}
    
SOURCE  channeltb_di_pv_source
{
    LABEL   "DI Channel PV Source";
    HELP    "The simulated PV for the DI Channel based on DI_FUNCTION.";
    Y_AXIS  channeltb_di_pv_y_axis;
    MEMBERS {   DI_PV_SRC,  PARAM.PRIMARY_VALUE_DI.VALUE; }
}
    
SOURCE  channeltb_mai_pv_source
{
    LABEL   "MAI Channel PV Source";
    HELP    "The simulated PV for the MAI Channel based on MAI_FUNCTION and PV Range.";
    Y_AXIS  channeltb_mai_pv_y_axis;
    MEMBERS {   MAI_PV_SRC,  PARAM.PRIMARY_VALUE_MAI.VALUE; }
}
    
SOURCE  channeltb_mdi_pv_source
{
    LABEL   "MDI Channel PV Source";
    HELP    "The simulated PV for the MDI Channel based on MDI_FUNCTION.";
    Y_AXIS  channeltb_mdi_pv_y_axis;
    MEMBERS {   MDI_PV_SRC,  PARAM.PRIMARY_VALUE_MDI.VALUE; }
}

CHART   channeltb_ai_pv_chart
{
    LABEL   "AI Channel PV Chart";
    HELP    "This chart shows the simulated AI Channel PV.  "
            "The chart cycle time is conditionaly set based "
            "on the value of FUNCTION_PERIOD.  The chart is "
            "disabled (VALIDITY FALSE) when AI_FUNCTION "
            "is set to \"No Function\".";
    MEMBERS {   CHANNELTB_AI_PV_SOURCE, channeltb_ai_pv_source; }
    CYCLE_TIME
        SELECT(PARAM.FUNCTION_PERIOD)
        {
            CASE    1:  250;
            CASE    2:  500;
            CASE    3:  1000;
            CASE    4:  2000;
        }
    VALIDITY
        IF(PARAM.AI_FUNCTION==0)    {FALSE;}
        ELSE                        {TRUE;}
}

CHART   channeltb_di_pv_chart
{
    LABEL   "DI Channel PV Chart";
    HELP    "This chart shows the simulated DI Channel PV.  "
            "The chart cycle time is conditionaly set based "
            "on the value of FUNCTION_PERIOD.  The chart is "
            "disabled (VALIDITY FALSE) when DI_FUNCTION "
            "is set to \"No Function\".";
    MEMBERS {   CHANNELTB_DI_PV_SOURCE, channeltb_di_pv_source; }
    CYCLE_TIME
        SELECT(PARAM.FUNCTION_PERIOD)
        {
            CASE    1:  250;
            CASE    2:  500;
            CASE    3:  1000;
            CASE    4:  2000;
        }
    VALIDITY
        IF(PARAM.DI_FUNCTION==0)    {FALSE;}
        ELSE                        {TRUE;}
}

CHART   channeltb_mai_pv_chart
{
    LABEL   "MAI Channel PV Chart";
    HELP    "This chart shows the simulated MAI Channel PV.  "
            "The chart cycle time is conditionaly set based "
            "on the value of FUNCTION_PERIOD.  The chart is "
            "disabled (VALIDITY FALSE) when MAI_FUNCTION "
            "is set to \"No Function\".";
    MEMBERS {   CHANNELTB_MAI_PV_SOURCE, channeltb_mai_pv_source; }
    CYCLE_TIME
        SELECT(PARAM.FUNCTION_PERIOD)
        {
            CASE    1:  250;
            CASE    2:  500;
            CASE    3:  1000;
            CASE    4:  2000;
        }
    VALIDITY
        IF(PARAM.MAI_FUNCTION==0)   {FALSE;}
        ELSE                        {TRUE;}
}

CHART   channeltb_mdi_pv_chart
{
    LABEL   "MDI Channel PV Chart";
    HELP    "This chart shows the simulated MDI Channel PV.  "
            "The chart cycle time is conditionaly set based "
            "on the value of FUNCTION_PERIOD.  The chart is "
            "disabled (VALIDITY FALSE) when MDI_FUNCTION "
            "is set to \"No Function\".";
    MEMBERS {   CHANNELTB_MDI_PV_SOURCE, channeltb_mdi_pv_source; }
    CYCLE_TIME
        SELECT(PARAM.FUNCTION_PERIOD)
        {
            CASE    1:  250;
            CASE    2:  500;
            CASE    3:  1000;
            CASE    4:  2000;
        }
    VALIDITY
        IF(PARAM.MDI_FUNCTION==0)   {FALSE;}
        ELSE                        {TRUE;}
}
       
/***********************************************************************/

#endif