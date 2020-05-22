
/*************************************************************************************************************************************************************/
#ifndef DD4
IMAGE pst_graph_image
{
PATH "PST_Graph_display.JPG";
}
#endif


#ifndef DD4
IMAGE pic_dev_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{"greenCheckMark.JPG";}
	ELSE
	{ "cross.JPG"; }
}
#else
#define pic_dev_alert
#endif

#if 0 /*ndef DD4*/
IMAGE img_ok
{
    PATH
        "greenCheckMark.JPG";
}
IMAGE img_oops
{
    PATH
        "cross.JPG";
}

#if !0
IMAGE img_dev_alert
{
    PATH
    IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
        "greenCheckMark.JPG";
    }
    ELSE
	{
        "cross.JPG";
    }
}
#else
MENU mnu_ok_dev_alert
{
	LABEL "|en|Deviation Alert";
    ITEMS
    {
        PARAM.ALERT_STATE.DEVIATION_ALERT_ST
        COLUMNBREAK
        img_ok
		PARAM.ALERT_COUNTERS.DEVIATION_ALERT_CNT
    }
    VALIDITY
    IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
        TRUE;
    }
    ELSE
	{
        FALSE;
    }
}
MENU mnu_oops_dev_alert
{
	LABEL "|en|Deviation Alert";
    ITEMS
    {
        PARAM.ALERT_STATE.DEVIATION_ALERT_ST
        COLUMNBREAK
        img_oops
		PARAM.ALERT_COUNTERS.DEVIATION_ALERT_CNT
    }
    VALIDITY
    IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST != 0)
	{
        TRUE;
    }
    ELSE
	{
        FALSE;
    }
}
#define img_dev_alert mnu_ok_dev_alert mnu_oops_dev_alert COLUMNBREAK
#endif
#else
#define img_dev_alert PARAM.ALERT_STATE.DEVIATION_ALERT_ST 		PARAM.ALERT_COUNTERS.DEVIATION_ALERT_CNT
#endif

#ifndef DD4
IMAGE pic_poshihi_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_poshihi_alert PARAM.ALERT_STATE.POSITION_HIHI_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_poshi_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_poshi_alert PARAM.ALERT_STATE.POSITION_HI_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_poslo_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{"greenCheckMark.JPG";}
	ELSE
	{ "cross.JPG"; }
}
#else
#define pic_poslo_alert PARAM.ALERT_STATE.POSITION_LO_ALERT_ST
#endif

#ifndef DD4
IMAGE pic_poslolo_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_poslolo_alert PARAM.ALERT_STATE.POSITION_LOLO_ALERT_ST
#endif

#ifndef DD4
IMAGE pic_setpoint_alert
{
	PATH
	IF(PARAM.ALERT_STATE.SETPOINT_TIMEOUT_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_setpoint_alert PARAM.ALERT_STATE.SETPOINT_TIMEOUT_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_nearclose_alert
{
	PATH "greenCheckMark.JPG";
	VALIDITY
	IF(PARAM.ALERT_STATE.NEAR_CLOSE_ALERT_ST == 0)
	{
TRUE;
}
ELSE
{ FALSE; }
}
#else
#define pic_nearclose_alert PARAM.ALERT_STATE.NEAR_CLOSE_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_travelA_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_travelA_alert PARAM.ALERT_STATE.TRAVEL_ACCUMULATION_A_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_travelB_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{"greenCheckMark.JPG";}
	ELSE
	{ "cross.JPG"; }
}
#else
#define pic_travelB_alert PARAM.ALERT_STATE.TRAVEL_ACCUMULATION_B_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_cycleA_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_cycleA_alert PARAM.ALERT_STATE.CYCLE_COUNTER_A_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_cycleB_alert
{
	PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_cycleB_alert PARAM.ALERT_STATE.CYCLE_COUNTER_B_ALERT_ST
#endif


#ifndef DD4
IMAGE pic_wroktime_alert
{
PATH
	IF(PARAM.ALERT_STATE.DEVIATION_ALERT_ST == 0)
	{
"greenCheckMark.JPG";
}
ELSE
{ "cross.JPG"; }
}
#else
#define pic_wroktime_alert PARAM.ALERT_STATE.WORKING_TIME_ALERT_ST
#endif

