/*****************************************************************************/
/* 1000_Menus.ddl                                                            */
/*                                                                           */
/*   This DDL file contains all the menus and sub-menus for all the blocks   */
/*   and the device (for x-block reference).                                 */
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
/* 02-11-09 ! added hh_device_root_menu_ as per AR3780          ! 1.1 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Resource Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_rb
{
    LABEL   "RB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_rb
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_rb
{
    LABEL   "RB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_rb
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_rb
{
    LABEL   "RB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_rb
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_rb LIKE MENU device_root_menu_rb
{   REDEFINE LABEL   "Handheld RB Root Menu";  }

hh_diagnostic_root_menu_rb LIKE MENU diagnostic_root_menu_rb
{   REDEFINE LABEL   "Handheld RB Diagnostic Menu";    } 

hh_process_variables_root_menu_rb LIKE MENU process_variables_root_menu_rb
{   REDEFINE LABEL   "Handheld RB Process Variables Menu";    } 
#else
Menu_Top_rb LIKE MENU device_root_menu_rb
{   REDEFINE LABEL   "Handheld RB Root Menu"; }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_rb
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** AI Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_ai
{
    LABEL   "AI Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ai
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_ai
{
    LABEL   "AI Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ai
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_ai
{
    LABEL   "AI Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ai
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_ai LIKE MENU device_root_menu_ai
{   REDEFINE LABEL   "Handheld AI Root Menu";  }

hh_diagnostic_root_menu_ai LIKE MENU diagnostic_root_menu_ai
{   REDEFINE LABEL   "Handheld AI Diagnostic Menu";    } 

hh_process_variables_root_menu_ai LIKE MENU process_variables_root_menu_ai
{   REDEFINE LABEL   "Handheld AI Process Variables Menu";    } 
#else
Menu_Top_ai LIKE MENU device_root_menu_ai
{   REDEFINE LABEL   "Handheld AI Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_ai
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** AO Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_ao
{
    LABEL   "AO Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ao
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_ao
{
    LABEL   "AO Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ao
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_ao
{
    LABEL   "AO Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_ao
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_ao LIKE MENU device_root_menu_ao
{   REDEFINE LABEL   "Handheld AO Root Menu";  }

hh_diagnostic_root_menu_ao LIKE MENU diagnostic_root_menu_ao
{   REDEFINE LABEL   "Handheld AO Diagnostic Menu";    } 

hh_process_variables_root_menu_ao LIKE MENU process_variables_root_menu_ao
{   REDEFINE LABEL   "Handheld AO Process Variables Menu";    } 
#else
Menu_Top_ao LIKE MENU device_root_menu_ao
{   REDEFINE LABEL   "Handheld AO Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_ao
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** DI Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_di
{
    LABEL   "DI Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_di
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_di
{
    LABEL   "DI Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_di
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_di
{
    LABEL   "DI Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_di
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_di LIKE MENU device_root_menu_di
{   REDEFINE LABEL   "Handheld DI Root Menu";  }

hh_diagnostic_root_menu_di LIKE MENU diagnostic_root_menu_di
{   REDEFINE LABEL   "Handheld DI Diagnostic Menu";    } 

hh_process_variables_root_menu_di LIKE MENU process_variables_root_menu_di
{   REDEFINE LABEL   "Handheld DI Process Variables Menu";    } 
#else
Menu_Top_di LIKE MENU device_root_menu_di
{   REDEFINE LABEL   "Handheld DI Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_di
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** DO Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_do
{
    LABEL   "DO Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_do
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_do
{
    LABEL   "DO Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_do
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_do
{
    LABEL   "DO Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_do
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_do LIKE MENU device_root_menu_do
{   REDEFINE LABEL   "Handheld DO Root Menu";  }

hh_diagnostic_root_menu_do LIKE MENU diagnostic_root_menu_do
{   REDEFINE LABEL   "Handheld DO Diagnostic Menu";    } 

hh_process_variables_root_menu_do LIKE MENU process_variables_root_menu_do
{   REDEFINE LABEL   "Handheld DO Process Variables Menu";    } 
#else
Menu_Top_do LIKE MENU device_root_menu_do
{   REDEFINE LABEL   "Handheld DO Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_do
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** MAI Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_mai
{
    LABEL   "MAI Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mai
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_mai
{
    LABEL   "MAI Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mai
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_mai
{
    LABEL   "MAI Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mai
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_mai LIKE MENU device_root_menu_mai
{   REDEFINE LABEL   "Handheld MAI Root Menu";  }

hh_diagnostic_root_menu_mai LIKE MENU diagnostic_root_menu_mai
{   REDEFINE LABEL   "Handheld MAI Diagnostic Menu";    } 

hh_process_variables_root_menu_mai LIKE MENU process_variables_root_menu_mai
{   REDEFINE LABEL   "Handheld MAI Process Variables Menu";    } 
#else
Menu_Top_mai  LIKE MENU device_root_menu_mai
{   REDEFINE LABEL   "Handheld MAI Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_mai
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** MAO Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_mao
{
    LABEL   "MAO Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mao
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_mao
{
    LABEL   "MAO Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mao
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_mao
{
    LABEL   "MAO Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mao
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_mao LIKE MENU device_root_menu_mao
{   REDEFINE LABEL   "Handheld MAO Root Menu";  }

hh_diagnostic_root_menu_mao LIKE MENU diagnostic_root_menu_mao
{   REDEFINE LABEL   "Handheld MAO Diagnostic Menu";    } 

hh_process_variables_root_menu_mao LIKE MENU process_variables_root_menu_mao
{   REDEFINE LABEL   "Handheld MAO Process Variables Menu";    } 
#else
Menu_Top_mao  LIKE MENU device_root_menu_mao
{   REDEFINE LABEL   "Handheld MAO Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_mao
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** MDI Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_mdi
{
    LABEL   "MDI Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdi
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_mdi
{
    LABEL   "MDI Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdi
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_mdi
{
    LABEL   "MDI Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdi
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_mdi LIKE MENU device_root_menu_mdi
{   REDEFINE LABEL   "Handheld MDI Root Menu";  }

hh_diagnostic_root_menu_mdi LIKE MENU diagnostic_root_menu_mdi
{   REDEFINE LABEL   "Handheld MDI Diagnostic Menu";    } 

hh_process_variables_root_menu_mdi LIKE MENU process_variables_root_menu_mdi
{   REDEFINE LABEL   "Handheld MDI Process Variables Menu";    } 
#else
Menu_Top_mdi  LIKE MENU device_root_menu_mdi
{   REDEFINE LABEL   "Handheld MDI Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_mdi
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** MDO Block menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_mdo
{
    LABEL   "MDO Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdo
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_mdo
{
    LABEL   "MDO Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdo
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_mdo
{
    LABEL   "MDO Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_mdo
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_mdo LIKE MENU device_root_menu_mdo
{   REDEFINE LABEL   "Handheld MDO Root Menu";  }

hh_diagnostic_root_menu_mdo LIKE MENU diagnostic_root_menu_mdo
{   REDEFINE LABEL   "Handheld MDO Diagnostic Menu";    } 

hh_process_variables_root_menu_mdo LIKE MENU process_variables_root_menu_mdo
{   REDEFINE LABEL   "Handheld MDO Process Variables Menu";    } 
#else
Menu_Top_mdo LIKE MENU device_root_menu_mdo
{   REDEFINE LABEL   "Handheld MDO Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_mdo
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** CustomFB menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_customfb
{
    LABEL   "CustomFB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_customfb
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_customfb
{
    LABEL   "CustomFB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_customfb
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_customfb
{
    LABEL   "CustomFB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_customfb
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_customfb LIKE MENU device_root_menu_customfb
{   REDEFINE LABEL   "Handheld CustomFB Root Menu";  }

hh_diagnostic_root_menu_customfb LIKE MENU diagnostic_root_menu_customfb
{   REDEFINE LABEL   "Handheld CustomFB Diagnostic Menu";    } 

hh_process_variables_root_menu_customfb LIKE MENU process_variables_root_menu_customfb
{   REDEFINE LABEL   "Handheld CustomFB Process Variables Menu";    } 
#else
Menu_Top_customfb LIKE MENU device_root_menu_customfb
{   REDEFINE LABEL   "Handheld CustomFB Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_customfb
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*
******************************************************************************
** ChannelTB menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_channeltb
{
    LABEL   "ChannelTB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_channeltb
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_channeltb
{
    LABEL   "ChannelTB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_channeltb
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_channeltb
{
    LABEL   "ChannelTB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_channeltb
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_channeltb LIKE MENU device_root_menu_channeltb
{   REDEFINE LABEL   "Handheld ChannelTB Root Menu";  }

hh_diagnostic_root_menu_channeltb LIKE MENU diagnostic_root_menu_channeltb
{   REDEFINE LABEL   "Handheld ChannelTB Diagnostic Menu";    } 

hh_process_variables_root_menu_channeltb LIKE MENU process_variables_root_menu_channeltb
{   REDEFINE LABEL   "Handheld ChannelTB Process Variables Menu";    } 
#else
Menu_Top_channeltb LIKE MENU device_root_menu_channeltb
{   REDEFINE LABEL   "Handheld ChannelTB Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_channeltb
{
    LABEL   "Channel Charts Window";
    STYLE   WINDOW;
    ITEMS
    {
        ai_channel_page_channeltb,
        di_channel_page_channeltb,
        mai_channel_page_channeltb,
        mdi_channel_page_channeltb
    }
}

MENU    mode_n_function_group_channeltb
{
    LABEL   "Mode & Function";
    STYLE   GROUP;
    ITEMS
    {
        PARAM.MODE_BLK.TARGET,
        COLUMNBREAK,
        PARAM.MODE_BLK.ACTUAL(READ_ONLY),
        ROWBREAK,ROWBREAK,
        PARAM.FUNCTION_PERIOD
    }
}

MENU    ai_channel_group_channeltb
{
    LABEL   "AI Channel";
    STYLE   GROUP;
    ITEMS
    {
        PARAM.AI_FUNCTION,
        PARAM.PRIMARY_VALUE_RANGE_AI.EU_100,
        PARAM.PRIMARY_VALUE_RANGE_AI.EU_0,
        PARAM.PRIMARY_VALUE_AI.VALUE(READ_ONLY),
        ROWBREAK,ROWBREAK,
        channeltb_ai_pv_chart
    }
}

MENU    di_channel_group_channeltb
{
    LABEL   "DI Channel";
    STYLE   GROUP;
    ITEMS
    {
        PARAM.DI_FUNCTION,
        PARAM.PRIMARY_VALUE_DI.VALUE(READ_ONLY),
        ROWBREAK,ROWBREAK,
        channeltb_di_pv_chart
    }
}

MENU    mai_channel_group_channeltb
{
    LABEL   "MAI Channel";
    STYLE   GROUP;
    ITEMS
    {
        PARAM.MAI_FUNCTION,
        PARAM.PRIMARY_VALUE_RANGE_MAI.EU_100,
        PARAM.PRIMARY_VALUE_RANGE_MAI.EU_0,
        PARAM.PRIMARY_VALUE_MAI.VALUE(READ_ONLY),
        ROWBREAK,ROWBREAK,
        channeltb_mai_pv_chart
    }
}

MENU    mdi_channel_group_channeltb
{
    LABEL   "MDI Channel";
    STYLE   GROUP;
    ITEMS
    {
        PARAM.MDI_FUNCTION,
        PARAM.PRIMARY_VALUE_MDI.VALUE(READ_ONLY),
        ROWBREAK,ROWBREAK,
        channeltb_mdi_pv_chart
    }
}

MENU    ai_channel_page_channeltb
{
    LABEL   "AI Channel Chart";
    STYLE   PAGE;
    ITEMS   {   mode_n_function_group_channeltb, ai_channel_group_channeltb }
}

MENU    di_channel_page_channeltb
{
    LABEL   "DI Channel Chart";
    STYLE   PAGE;
    ITEMS   {   mode_n_function_group_channeltb, di_channel_group_channeltb }
}

MENU    mai_channel_page_channeltb
{
    LABEL   "MAI Channel Chart";
    STYLE   PAGE;
    ITEMS   {   mode_n_function_group_channeltb, mai_channel_group_channeltb }
}

MENU    mdi_channel_page_channeltb
{
    LABEL   "MDI Channel Chart";
    STYLE   PAGE;
    ITEMS   {   mode_n_function_group_channeltb, mdi_channel_group_channeltb }
}
    
#endif

/*
******************************************************************************
** VisualTB menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_visualtb
{
    LABEL   "VisualTB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        tc_gr_window_visualtb,
        tc_ch_window_visualtb,
        tc_img_menu_visualtb,
        tc_mn_menu_visualtb,
        tc_grd_window_visualtb
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_visualtb
{
    LABEL   "VisualTB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_visualtb
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_visualtb
{
    LABEL   "VisualTB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_visualtb
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_visualtb LIKE MENU device_root_menu_visualtb
{   REDEFINE LABEL   "Handheld VisualTB Root Menu";  }

hh_diagnostic_root_menu_visualtb LIKE MENU diagnostic_root_menu_visualtb
{   REDEFINE LABEL   "Handheld VisualTB Diagnostic Menu";    } 

hh_process_variables_root_menu_visualtb LIKE MENU process_variables_root_menu_visualtb
{   REDEFINE LABEL   "Handheld VisualTB Process Variables Menu";    } 
#else
Menu_Top_visualtb LIKE MENU device_root_menu_visualtb
{   REDEFINE LABEL   "Handheld VisualTB Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_visualtb
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*** access sub menus ***/
#if _DD5_PROFILE
MENU    tc_gr_window_visualtb
{
    LABEL   "Graph Test Cases";
    STYLE   WINDOW;
    ITEMS   {   _VISTB_TC_GR_PAGES  }
}

MENU    tc_ch_window_visualtb
{
    LABEL   "Chart Test Cases";
    STYLE   WINDOW;
    ITEMS   {   _VISTB_TC_CH_PAGES  }
}

MENU    tc_img_menu_visualtb
{
    LABEL   "Image Test Cases";
    STYLE   MENU;
    ITEMS   {   _VISTB_TC_IMG_WINDOWS   }
}    

MENU    tc_mn_menu_visualtb
{
    LABEL   "Menu Test Cases";
    STYLE   MENU;
    ITEMS   {   _VISTB_TC_MN_WINDOWS    }
}    

MENU    tc_grd_window_visualtb
{
    LABEL   "Grid Test Cases";
    STYLE   WINDOW;
    ITEMS   {   _VISTB_TC_GRD_PAGES }
}
#endif

/*
******************************************************************************
** DataTypesTB menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_datatypestb
{
    LABEL   "DataTypesTB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        tc_ddcf_001_window
        ,tc_item_004_window
        ,tc_item_005_window
        ,tc_meth_menu
        #if _DD5_PROFILE
        ,tc_file_menu
        ,tc_list_menu
		,window_test_datatypestb
        #endif
    }
}

MENU    diagnostic_root_menu_datatypestb
{
    LABEL   "DataTypesTB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_datatypestb
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_datatypestb
{
    LABEL   "DataTypesTB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_datatypestb
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_datatypestb LIKE MENU device_root_menu_datatypestb
{   REDEFINE LABEL   "Handheld DataTypesTB Root Menu";  }

hh_diagnostic_root_menu_datatypestb LIKE MENU diagnostic_root_menu_datatypestb
{   REDEFINE LABEL   "Handheld DataTypesTB Diagnostic Menu";    } 

hh_process_variables_root_menu_datatypestb LIKE MENU process_variables_root_menu_datatypestb
{   REDEFINE LABEL   "Handheld DataTypesTB Process Variables Menu";    } 
#else
Menu_Top_datatypestb LIKE MENU device_root_menu_datatypestb
{   REDEFINE LABEL   "Handheld DataTypesTB Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_datatypestb
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

#if _DD5_PROFILE
/* Window menu for the test method to display */
/* for root menus in DD5 profile */
MENU    window_test_datatypestb
{
    LABEL   "MenuDisplay test window";
    STYLE   WINDOW;
    ITEMS   {   "MenuDisplay Builtin Test"   }
}
#endif


/*
******************************************************************************
** CondTB1 menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_condtb1
{
    LABEL   "CondTB1 Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS   {   cond_test_condtb1   }
}

MENU    diagnostic_root_menu_condtb1
{
    LABEL   "CondTB1 Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_condtb1
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_condtb1
{
    LABEL   "CondTB1 Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_condtb1
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_condtb1 LIKE MENU device_root_menu_condtb1
{   REDEFINE LABEL   "Handheld CondTB1 Root Menu";  }

hh_diagnostic_root_menu_condtb1 LIKE MENU diagnostic_root_menu_condtb1
{   REDEFINE LABEL   "Handheld CondTB1 Diagnostic Menu";    } 

hh_process_variables_root_menu_condtb1 LIKE MENU process_variables_root_menu_condtb1
{   REDEFINE LABEL   "Handheld CondTB1 Process Variables Menu";    } 
#else
Menu_Top_condtb1 LIKE MENU device_root_menu_condtb1
{   REDEFINE LABEL   "Handheld CondTB1 Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_condtb1
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*** access sub menus ***/
MENU    cond_test_condtb1
{
    LABEL   "Conditional Test Cases";
    #if _DD5_PROFILE
    STYLE   WINDOW;
    #endif
    ITEMS   {   _CONDTB1_TEST_PAGES } 
}    
     
/*
******************************************************************************
** CondTB2 menus/sub-menus                                                                
******************************************************************************
*/

MENU    device_root_menu_condtb2
{
    LABEL   "CondTB2 Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS   {   cond_test_condtb2   }
}

MENU    diagnostic_root_menu_condtb2
{
    LABEL   "CondTB2 Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_condtb2
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_condtb2
{
    LABEL   "CondTB2 Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_condtb2
        #else
        __st_rev
        #endif
    }
}

#if !_AR4940
hh_device_root_menu_condtb2 LIKE MENU device_root_menu_condtb2
{   REDEFINE LABEL   "Handheld CondTB2 Root Menu";  }

hh_diagnostic_root_menu_condtb2 LIKE MENU diagnostic_root_menu_condtb2
{   REDEFINE LABEL   "Handheld CondTB2 Diagnostic Menu";    } 

hh_process_variables_root_menu_condtb2 LIKE MENU process_variables_root_menu_condtb2
{   REDEFINE LABEL   "Handheld CondTB2 Process Variables Menu";    } 
#else
Menu_Top_condtb2 LIKE MENU device_root_menu_condtb2
{   REDEFINE LABEL   "Handheld CondTB2 Root Menu";  }
#endif

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_condtb2
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif

/*** access sub menus ***/
MENU    cond_test_condtb2
{
    LABEL   "Conditional Test Cases";
    #if _DD5_PROFILE
    STYLE   WINDOW;
    #endif
    ITEMS   {   _CONDTB2_TEST_PAGES     }
}    

/*
******************************************************************************
** AR4041 - Profiled Custom Function Blocks
** Custom Calculation Block                                                                
******************************************************************************
*/
#ifndef DEVREV1
MENU    device_root_menu_custom_calc
{
    LABEL   "Custom Calculation FB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_calc
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_custom_calc
{
    LABEL   "Custom Calculation FB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_calc
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_custom_calc
{
    LABEL   "Custom Calculation FB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_calc
        #else
        __st_rev
        #endif
    }
}

Menu_Top_custom_calc LIKE MENU device_root_menu_custom_calc
{   REDEFINE LABEL   "Handheld Custom Calculation FB Root Menu";  }

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_custom_calc
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif
#endif

/*
******************************************************************************
** AR4041 - Profiled Custom Function Blocks
** Custom Control Block                                                                
******************************************************************************
*/

#ifndef DEVREV1
MENU    device_root_menu_custom_cntrl
{
    LABEL   "Custom Control FB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_cntrl
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_custom_cntrl
{
    LABEL   "Custom Control FB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_cntrl
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_custom_cntrl
{
    LABEL   "Custom Control FB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_cntrl
        #else
        __st_rev
        #endif
    }
}

Menu_Top_custom_cntrl LIKE MENU device_root_menu_custom_cntrl
{   REDEFINE LABEL   "Handheld Custom Control FB Root Menu";  }

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_custom_cntrl
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif
#endif

/*
******************************************************************************
** AR4041 - Profiled Custom Function Blocks
** Custom Input Block                                                                
******************************************************************************
*/

#ifndef DEVREV1
MENU    device_root_menu_custom_in
{
    LABEL   "Custom Input FB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_in
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_custom_in
{
    LABEL   "Custom Input FB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_in
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_custom_in
{
    LABEL   "Custom Input FB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_in
        #else
        __st_rev
        #endif
    }
}

Menu_Top_custom_in LIKE MENU device_root_menu_custom_in
{   REDEFINE LABEL   "Handheld Custom Input FB Root Menu";  }

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_custom_in
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif
#endif

/*
******************************************************************************
** AR4041 - Profiled Custom Function Blocks
** Custom Output Block                                                                
******************************************************************************
*/

#ifndef DEVREV1
MENU    device_root_menu_custom_out
{
    LABEL   "Custom Output FB Root Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_out
        #else
        __st_rev
        #endif
    }
}

MENU    diagnostic_root_menu_custom_out
{
    LABEL   "Custom Output FB Diagnostic Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_out
        #else
        __st_rev
        #endif
    }
}

MENU    process_variables_root_menu_custom_out
{
    LABEL   "Custom Output FB Process Variables Menu";
    #if _DD5_PROFILE
    STYLE   MENU;
    #endif
    ITEMS
    {
        #if _DD5_PROFILE
        window_custom_out
        #else
        __st_rev
        #endif
    }
}

Menu_Top_custom_out LIKE MENU device_root_menu_custom_out
{   REDEFINE LABEL   "Handheld Custom Output FB Root Menu";  }

#if _DD5_PROFILE
/* generic placeholder sub-menu item */
/* for root menus in DD5 profile */
MENU    window_custom_out
{
    LABEL   "Sub-Menu Window";
    STYLE   WINDOW;
    ITEMS   {   "String Constant"   }
}
#endif
#endif

/*
******************************************************************************
** Device root menus/sub-menus                                                                
******************************************************************************
*/

#if _DD5_PROFILE
MENU    device_root_menu
{
    LABEL   "Device Root Menu";
    STYLE   MENU;
    ITEMS   {   device_level_window }   
}

MENU    device_level_window
{
    LABEL   "Device Level Window";
    STYLE   WINDOW;
    ITEMS
    {
        tc_mn_014_dialog,
		tc_mn_015_window,
		tc_mn_016_page,
		tc_mn_017_group,
		tc_mn_018_menu,
		tc_mn_019_menu,
		tc_meth_002

    }
}

hh_device_root_menu LIKE MENU device_root_menu
{   REDEFINE LABEL   "Handheld Device Root Menu";  }

#if _DIAG_ROOT_MENU
MENU    diagnostics_root_menu
{
    LABEL   "Device Diagnostic Menu";
    STYLE   MENU;
    ITEMS
    {
        "String Constant"
    }
}

hh_diagnostics_root_menu LIKE MENU diagnostics_root_menu
{   REDEFINE LABEL   "Handheld Device Diagnostic Menu";    } 
#endif

#if _PROC_VAR_ROOT_MENU
MENU    process_variables_root_menu
{
    LABEL   "Device Process Variables Menu";
    STYLE   MENU;
    ITEMS
    {
        "String Constant"
    }
}

hh_process_variables_root_menu LIKE MENU process_variables_root_menu
{   REDEFINE LABEL   "Handheld Device Process Variables Menu";    } 
#endif

#endif
