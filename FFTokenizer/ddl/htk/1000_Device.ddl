/*****************************************************************************/
/* 1000_Device.ddl                                                           */
/*                                                                           */
/*   This DDL file is the main project file for this device.  This should    */
/*   be the only file that needs to be referenced by the Tokenizer; all      */
/*   other files will be included or imported into this file.                */
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
/* 03-28-07 ! Redefined enumerations for I/O FBs (in AI block)  ! 1.0 ! ms   */
/* 09-24-09 ! ARs 4048, 3184, 3570, 4041                        ! 1.1 ! ms   */
/* 10-20-09 ! ARs 3184, 3570, 4041, 4048, 4437                  ! 2.0 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/


/*
******************************************************************************
** Includes
******************************************************************************
*/

#include "std_defs.h"
#include "com_tbls.h"
#include "builtins.h"
#include "1000_Definitions.h"

/*
******************************************************************************
** Device Information
******************************************************************************
*/

MANUFACTURER        _FF_MFG_ID,
DEVICE_TYPE         _FF_HTK_DEV_ID,
DEVICE_REVISION     _FF_HTK_DEV_REV,
DD_REVISION         _FF_HTK_DD_REV

/*
******************************************************************************
** Standard Library Parameter Imports
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __STD_PARM,
        DEVICE_REVISION __STD_PARM_rel_dev_rev,
        DD_REVISION     __STD_PARM_rel_dd_rev
{EVERYTHING;

    REDEFINITIONS
    {
        #if !_AR5111
        VARIABLE    __fd_check_active
        {
            TYPE   BIT_ENUMERATED
            {
                DELETE      0x00000000;
                REDEFINE    {0x00000001,[check_label],[check_help]}
                _FD_BITS_REDEFINE  
            }
        }

        VARIABLE    __fd_check_map
        {
            TYPE   BIT_ENUMERATED
            {
                DELETE      0x0000;
                REDEFINE    {0x0001,[check_label],[check_help]}
                REDEFINE    {0x0002,    "Bit 1"}
                ADD {0x00000004,    "Bit 2"} 
                ADD {0x00000008,    "Bit 3"}  
                ADD {0x00000010,    "Bit 4"}  
                ADD {0x00000020,    "Bit 5"}  
                ADD {0x00000040,    "Bit 6"}  
                ADD {0x00000080,    "Bit 7"}  
                ADD {0x00000100,    "Bit 8"}  
                ADD {0x00000200,    "Bit 9"}  
                ADD {0x00000400,    "Bit 10"} 
                ADD {0x00000800,    "Bit 11"} 
                ADD {0x00001000,    "Bit 12"} 
                ADD {0x00002000,    "Bit 13"} 
                ADD {0x00004000,    "Bit 14"} 
                ADD {0x00008000,    "Bit 15"}
            }
        }

        VARIABLE    __fd_check_mask
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_fail_active
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_fail_map
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_fail_mask
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_maint_active
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_maint_map
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_maint_mask
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_offspec_active
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_offspec_map
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __fd_offspec_mask
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __diagnostic_simulate_value
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }

        VARIABLE    __diagnostic_value
        {
            TYPE   BIT_ENUMERATED
            {
                _FD_BITS_ADD  
            }
        }
        #endif

        #if _AR4629
        RECORD      __out
        {
            MEMBERS
            {
                REDEFINE STATUS,  __status_output_nd ;
            }
        }
        #endif
    }
}

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __ADV_PARAM,
        DEVICE_REVISION __ADV_PARAM_rel_dev_rev,
        DD_REVISION     __ADV_PARAM_rel_dd_rev
{EVERYTHING;
    #if _AR4437==0
    REDEFINITIONS
    {
        RECORD      __bkcal_in_d
        {
            MEMBERS
            {
                REDEFINE STATUS,  __status_input_nd ;
                REDEFINE VALUE,   __on_off_input_nd ;
            }
        }
    }
    #endif
}

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __STD_XDCR_PARM,
        DEVICE_REVISION __STD_XDCR_PARM_beta_dev_rev,
        DD_REVISION     __STD_XDCR_PARM_beta_dd_rev
{EVERYTHING;
    #if _AR4990 && _DD5_PROFILE
    REDEFINITIONS
    {
        VARIABLE    __float_contained_srv
        {
            REDEFINE POST_EDIT_ACTIONS {insert_test_input_list_action}
        }
    }
    #endif
}

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __STD_MIO_PARM,
        DEVICE_REVISION __STD_MIO_PARM_rel_dev_rev,
        DD_REVISION     __STD_MIO_PARM_rel_dd_rev
{EVERYTHING;}

/*
******************************************************************************
** Resource Block
** Import
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __RES_BLOCK_2,
        DEVICE_REVISION __RES_BLOCK_2_rel_dev_rev,
        DD_REVISION     __RES_BLOCK_2_rel_dd_rev
{EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __resource_block_2
        {
            #ifndef DEVREV1
            PARAMETERS
            {
                ADD COMPATIBILITY_REV,  __compatability_rev;    /* AR4048 */
                __FD_PARAMS                                     /* AR3184 */
            }
            #endif
        
            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_rb,
                #else
                Menu_Top_rb,
                #endif
                
                device_root_menu_rb

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_rb
                #if !_AR4940
                ,hh_diagnostics_root_menu_rb
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_rb
                #if !_AR4940
                ,hh_process_variables_root_menu_rb
                #endif
                #endif
            }
        }

        #ifndef DEVREV1
        /* AR3184 */
        VARIABLE_LIST   __res_2_view_1
        {
            MEMBERS
            {
                __FD_PARAMS_VIEW1
            }    
        }
        
        VARIABLE_LIST   __res_2_view_3
        {
            MEMBERS
            {
                __FD_PARAMS_VIEW3
            }    
        }
        
        VARIABLE_LIST   __res_2_view_4
        {
            MEMBERS
            {
                #if _AR5111==0
                ADD VL_FD_VER,  PARAM.FD_VER;
                #endif
                __FD_PARAMS_VIEW4
            }    
        }
        #endif
    }
}

/*
******************************************************************************
** Analog Input Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __AI_BLOCK,
        DEVICE_REVISION __AI_BLOCK_rel_dev_rev,
        DD_REVISION     __AI_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        /* channel enumeration redefinition for all I/O FBs */
        VARIABLE    __channel
        {
            TYPE ENUMERATED
            {
                REDEFINE    {0, "None"          }
                REDEFINE    {1, "AI Channel"    }
                REDEFINE    {2, "AO Channel"    }
                ADD         {3, "DI Channel"    }
                ADD         {4, "DO Channel"    }
                ADD         {5, "MAI Channel"   }
                ADD         {6, "MAO Channel"   }
                ADD         {7, "MDI Channel"   }
                ADD         {8, "MDO Channel"   }
            }
        }

        BLOCK   __analog_input_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
                /* AR3570 */
                #ifndef DEVREV1
                ADD R_DS256,    r_ds256_fb;
                ADD R_DS257,    r_ds257_fb;
                #endif
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_ai,
                #else
                Menu_Top_ai,
                #endif
                
                device_root_menu_ai

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_ai
                #if !_AR4940
                ,hh_diagnostics_root_menu_ai
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_ai
                #if !_AR4940
                ,hh_process_variables_root_menu_ai
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Analog Output Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __AO_BLOCK,
        DEVICE_REVISION __AO_BLOCK_rel_dev_rev,
        DD_REVISION     __AO_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __analog_output_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
                /* AR3570 */
                #ifndef DEVREV1
                ADD R_DS256,    r_ds256_fb;
                ADD R_DS257,    r_ds257_fb;
                #endif
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_ao,
                #else
                Menu_Top_ao,
                #endif
                
                device_root_menu_ao

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_ao
                #if !_AR4940
                ,hh_diagnostics_root_menu_ao
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_ao
                #if !_AR4940
                ,hh_process_variables_root_menu_ao
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Discrete Input Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __DI_BLOCK,
        DEVICE_REVISION __DI_BLOCK_rel_dev_rev,
        DD_REVISION     __DI_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __discrete_input_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_di,
                #else
                Menu_Top_di,
                #endif
                
                device_root_menu_di

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_di
                #if !_AR4940
                ,hh_diagnostics_root_menu_di
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_di
                #if !_AR4940
                ,hh_process_variables_root_menu_di
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Discrete Output Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __DO_BLOCK,
        DEVICE_REVISION __DO_BLOCK_rel_dev_rev,
        DD_REVISION     __DO_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __discrete_output_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_do,
                #else
                Menu_Top_do,
                #endif
                
                device_root_menu_do

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_do
                #if !_AR4940
                ,hh_diagnostics_root_menu_do
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_do
                #if !_AR4940
                ,hh_process_variables_root_menu_do
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Multiple Analog Input Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __MAI,
        DEVICE_REVISION __MAI_rel_dev_rev,
        DD_REVISION     __MAI_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __mai_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_mai,
                #else
                Menu_Top_mai,
                #endif
                
                device_root_menu_mai

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_mai
                #if !_AR4940
                ,hh_diagnostics_root_menu_mai
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_mai
                #if !_AR4940
                ,hh_process_variables_root_menu_mai
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Multiple Analog Output Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __MAO,
        DEVICE_REVISION __MAO_rel_dev_rev,
        DD_REVISION     __MAO_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __mao_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_mao,
                #else
                Menu_Top_mao,
                #endif
                
                device_root_menu_mao

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_mao
                #if !_AR4940
                ,hh_diagnostics_root_menu_mao
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_mao
                #if !_AR4940
                ,hh_process_variables_root_menu_mao
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Multiple Discrete Input Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __MDI,
        DEVICE_REVISION __MDI_rel_dev_rev,
        DD_REVISION     __MDI_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __mdi_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_mdi,
                #else
                Menu_Top_mdi,
                #endif
                
                device_root_menu_mdi

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_mdi
                #if !_AR4940
                ,hh_diagnostics_root_menu_mdi
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_mdi
                #if !_AR4940
                ,hh_process_variables_root_menu_mdi
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** Multiple Discrete Output Block
** Import & Redefinitions
******************************************************************************
*/

IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __MDO,
        DEVICE_REVISION __MDO_rel_dev_rev,
        DD_REVISION     __MDO_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __mdo_block
        {
            PARAMETERS
            {
                ADD ENHANCED_BLK_PARAM,     __test_read_write;
            }

            REDEFINE MENU_ITEMS
            {
                #if !_AR4940
                hh_device_root_menu_mdo,
                #else
                Menu_Top_mdo,
                #endif
                
                device_root_menu_mdo

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_mdo
                #if !_AR4940
                ,hh_diagnostics_root_menu_mdo
                #endif
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_mdo
                #if !_AR4940
                ,hh_process_variables_root_menu_mdo
                #endif
                #endif
            }
        }
    }
}

/*
******************************************************************************
** AR4041 - Profiled Custom Function Blocks (available in DDL 3.5)
** Import & Redefinitions
******************************************************************************
*/

#ifndef DEVREV1
/* Custom Calculation Block */
IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __CUSTOM_CALC_BLOCK,
        DEVICE_REVISION __CUSTOM_CALC_BLOCK_rel_dev_rev,
        DD_REVISION     __CUSTOM_CALC_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __custom_calc_block
        {
            PARAMETERS
            {
                ADD OUT,            __out;
                ADD PV,             __pv;
                ADD IN,             __in;
                ADD OUT_D,          __out_d;
                ADD PV_D,           __pv_d;
                ADD IN_D,           __in_d;
                ADD BLOCK_ALM,      __block_alm;
                ADD R_DS256,        r_ds256_fb;
                ADD R_DS257,        r_ds257_fb;
            }
            REDEFINE MENU_ITEMS
            {
                Menu_Top_custom_calc,
                device_root_menu_custom_calc

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_custom_calc
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_custom_calc
                #endif
            }
        }

        VARIABLE_LIST   __custom_calc_view_1
        {
            MEMBERS
            {
                ADD VL_OUT,         PARAM.OUT;
                ADD VL_PV,          PARAM.PV;
                ADD VL_OUT_D,       PARAM.OUT_D;
                ADD VL_PV_D,        PARAM.PV_D;
            }
        }

        VARIABLE_LIST   __custom_calc_view_3
        {
            MEMBERS
            {
                ADD VL_OUT,         PARAM.OUT;
                ADD VL_PV,          PARAM.PV;
                ADD VL_IN,          PARAM.IN;
                ADD VL_OUT_D,       PARAM.OUT_D;
                ADD VL_PV_D,        PARAM.PV_D;
                ADD VL_IN_D,        PARAM.IN_D;
                ADD VL_R_DS256,     PARAM.R_DS256;
                ADD VL_R_DS257,     PARAM.R_DS257;
            }
        }
    }
}

/* Custom Control Block */
IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __CUSTOM_CONTROL_BLOCK,
        DEVICE_REVISION __CUSTOM_CONTROL_BLOCK_rel_dev_rev,
        DD_REVISION     __CUSTOM_CONTROL_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __custom_cntrl_block
        {
            PARAMETERS
            {
                ADD OUT,            __out;
                ADD BKCAL_IN,       __bkcal_in;
                ADD PV,             __pv;
                ADD IN,             __in;
                ADD OUT_D,          __out_d;
                ADD BKCAL_IN_D,     __bkcal_in_d;
                ADD PV_D,           __pv_d;
                ADD IN_D,           __in_d;
                ADD BLOCK_ALM,      __block_alm;
                ADD R_DS256,        r_ds256_fb;
                ADD R_DS257,        r_ds257_fb;
            }
            REDEFINE MENU_ITEMS
            {
                Menu_Top_custom_cntrl,
                device_root_menu_custom_cntrl

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_custom_cntrl
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_custom_cntrl
                #endif
            }
        }

        VARIABLE_LIST   __custom_cntrl_view_1
        {
            MEMBERS
            {
                ADD VL_OUT,         PARAM.OUT;
                ADD VL_PV,          PARAM.PV;
                ADD VL_OUT_D,       PARAM.OUT_D;
                ADD VL_PV_D,        PARAM.PV_D;
            }
        }

        VARIABLE_LIST   __custom_cntrl_view_3
        {
            MEMBERS
            {
                ADD VL_OUT,         PARAM.OUT;
                ADD VL_BKCAL_IN,    PARAM.BKCAL_IN;
                ADD VL_PV,          PARAM.PV;
                ADD VL_IN,          PARAM.IN;
                ADD VL_OUT_D,       PARAM.OUT_D;
                ADD VL_BKCAL_IN_D,  PARAM.BKCAL_IN_D;
                ADD VL_PV_D,        PARAM.PV_D;
                ADD VL_IN_D,        PARAM.IN_D;
                ADD VL_R_DS256,     PARAM.R_DS256;
                ADD VL_R_DS257,     PARAM.R_DS257;
            }
        }
    }
}

/* Custom Input Block */
IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __CUSTOM_INPUT_BLOCK,
        DEVICE_REVISION __CUSTOM_INPUT_BLOCK_rel_dev_rev,
        DD_REVISION     __CUSTOM_INPUT_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __custom_in_block
        {
            PARAMETERS
            {
                ADD PV,                     __pv ;
                ADD OUT,                    __out ;
                ADD SIMULATE,               __simulate_float ;
                ADD XD_SCALE,               __xd_scale ;
                ADD OUT_SCALE,              __out_scale ;
                ADD GRANT_DENY,             __grant_deny ;
                ADD IO_OPTS,                __io_opts_ai ;
                ADD STATUS_OPTS,    	    __status_opts_ai ;
                ADD CHANNEL,                __channel ;
                ADD L_TYPE,                 __l_type ;
                ADD LOW_CUT,                __low_cut ;
                ADD PV_FTIME,               __pv_ftime ;
                ADD FIELD_VAL,              __field_val ;
                ADD UPDATE_EVT,             __update_evt ;
                ADD BLOCK_ALM,              __block_alm ;
                ADD ALARM_SUM,              __alarm_sum_ai ;
                ADD ACK_OPTION,             __ack_option_ai ;
                ADD ALARM_HYS,              __alarm_hys ;
                ADD HI_HI_PRI,              __hi_hi_pri ;
                ADD HI_HI_LIM,              __hi_hi_lim ;
                ADD HI_PRI,                 __hi_pri ;
                ADD HI_LIM,                 __hi_lim ;
                ADD LO_PRI,                 __lo_pri ;
                ADD LO_LIM,                 __lo_lim ;
                ADD LO_LO_PRI,              __lo_lo_pri ;
                ADD LO_LO_LIM,              __lo_lo_lim ;
                ADD HI_HI_ALM,              __hi_hi_alm ;
                ADD HI_ALM,                 __hi_alm ;
                ADD LO_ALM,                 __lo_alm ;
                ADD LO_LO_ALM,              __lo_lo_alm ;
                ADD R_DS256,                r_ds256_fb;
                ADD R_DS257,                r_ds257_fb;
            }
            REDEFINE MENU_ITEMS
            {
                Menu_Top_custom_in,
                device_root_menu_custom_in

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_custom_in
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_custom_in
                #endif
            }
        }

        VARIABLE_LIST   __custom_in_view_1
        {
            MEMBERS
            {
                ADD VL_PV,          PARAM.PV ;
                ADD VL_OUT,         PARAM.OUT ;
                ADD VL_FIELD_VAL,   PARAM.FIELD_VAL ;
                ADD VL_ALARM_SUM,   PARAM.ALARM_SUM ;
            }
        }

        VARIABLE_LIST   __custom_in_view_2
        {
            MEMBERS
            {
                ADD VL_XD_SCALE,    PARAM.XD_SCALE ;
                ADD VL_OUT_SCALE,   PARAM.OUT_SCALE ;
                ADD VL_GRANT_DENY,  PARAM.GRANT_DENY ;
            }
        }

        VARIABLE_LIST   __custom_in_view_3
        {
            MEMBERS
            {
                ADD VL_PV,          PARAM.PV ;
                ADD VL_OUT,         PARAM.OUT ;
                ADD VL_FIELD_VAL,   PARAM.FIELD_VAL ;
                ADD VL_ALARM_SUM,   PARAM.ALARM_SUM ;
                ADD VL_R_DS256,     PARAM.R_DS256;
                ADD VL_R_DS257,     PARAM.R_DS257;
            }
        }

        VARIABLE_LIST   __custom_in_view_4
        {
            MEMBERS
            {
                ADD VL_IO_OPTS,         PARAM.IO_OPTS ;
                ADD VL_STATUS_OPTS,     PARAM.STATUS_OPTS ;
                ADD VL_CHANNEL,         PARAM.CHANNEL ;
                ADD VL_L_TYPE,          PARAM.L_TYPE ;
                ADD VL_LOW_CUT,         PARAM.LOW_CUT ;
                ADD VL_PV_FTIME,        PARAM.PV_FTIME ;
                ADD VL_ACK_OPTION,      PARAM.ACK_OPTION ;
                ADD VL_ALARM_HYS,       PARAM.ALARM_HYS ;
                ADD VL_HI_HI_PRI,       PARAM.HI_HI_PRI ;
                ADD VL_HI_HI_LIM,       PARAM.HI_HI_LIM ;
                ADD VL_HI_PRI,          PARAM.HI_PRI ;
                ADD VL_HI_LIM,          PARAM.HI_LIM ;
                ADD VL_LO_PRI,          PARAM.LO_PRI ;
                ADD VL_LO_LIM,          PARAM.LO_LIM ;
                ADD VL_LO_LO_PRI,       PARAM.LO_LO_PRI ;
                ADD VL_LO_LO_LIM,       PARAM.LO_LO_LIM ;
            }
        }
    }
}

/* Custom Output Block */
IMPORT  MANUFACTURER    __FF,
        DEVICE_TYPE     __CUSTOM_OUTPUT_BLOCK,
        DEVICE_REVISION __CUSTOM_OUTPUT_BLOCK_rel_dev_rev,
        DD_REVISION     __CUSTOM_OUTPUT_BLOCK_rel_dd_rev
{
    EVERYTHING;

    REDEFINITIONS
    {
        BLOCK   __custom_out_block
        {
            PARAMETERS
            {
                ADD PV,             __pv ;
                ADD SP,             __sp ;
                ADD OUT,            __out ;
                ADD SIMULATE,       __simulate_float ;
                ADD PV_SCALE,       __pv_scale ;
                ADD XD_SCALE,       __xd_scale ;
                ADD GRANT_DENY,     __grant_deny ;
                ADD IO_OPTS,        __io_opts_ao ;
		        ADD STATUS_OPTS,    __status_opts_ao ;
                ADD READBACK,       __readback ;
                ADD CAS_IN,         __cas_in ;
                ADD SP_RATE_DN,     __sp_rate_dn ;
                ADD SP_RATE_UP,     __sp_rate_up ;
                ADD SP_HI_LIM,      __sp_hi_lim ;
                ADD SP_LO_LIM,      __sp_lo_lim ;
                ADD CHANNEL,        __channel ;
                ADD FSTATE_TIME,    __fstate_time ;
                ADD FSTATE_VAL,     __fstate_val ;
                ADD BKCAL_OUT,      __bkcal_out ;
                ADD RCAS_IN,        __rcas_in ;
                ADD SHED_OPT,       __shed_opt ;
                ADD RCAS_OUT,       __rcas_out ;
                ADD UPDATE_EVT,     __update_evt ;
                ADD BLOCK_ALM,      __block_alm ;
                ADD R_DS256,    r_ds256_fb;
                ADD R_DS257,    r_ds257_fb;
            }
            REDEFINE MENU_ITEMS
            {
                Menu_Top_custom_out,
                device_root_menu_custom_out

                #if _DIAG_ROOT_MENU 
                ,diagnostic_root_menu_custom_out
                #endif

                #if _PROC_VAR_ROOT_MENU
                ,process_variables_root_menu_custom_out
                #endif
            }
        }

        VARIABLE_LIST   __custom_out_view_1
        {
            MEMBERS
            {
                ADD VL_PV,          PARAM.PV ;
                ADD VL_SP,          PARAM.SP ;
                ADD VL_OUT,         PARAM.OUT ;
                ADD VL_READBACK,    PARAM.READBACK ;
                ADD VL_CAS_IN,      PARAM.CAS_IN ;
            }
        }

        VARIABLE_LIST   __custom_out_view_2
        {
            MEMBERS
            {
                ADD VL_PV_SCALE,    PARAM.PV_SCALE ;
                ADD VL_XD_SCALE,    PARAM.XD_SCALE ;
                ADD VL_GRANT_DENY,  PARAM.GRANT_DENY ;
                ADD VL_SP_HI_LIM,   PARAM.SP_HI_LIM ;
                ADD VL_SP_LO_LIM,   PARAM.SP_LO_LIM ;
            }
        }

        VARIABLE_LIST   __custom_out_view_3
        {
            MEMBERS
            {
                ADD VL_PV,          PARAM.PV ;
                ADD VL_SP,          PARAM.SP ;
                ADD VL_OUT,         PARAM.OUT ;
                ADD VL_READBACK,    PARAM.READBACK ;
                ADD VL_CAS_IN,      PARAM.CAS_IN ;
                ADD VL_BKCAL_OUT,   PARAM.BKCAL_OUT ;
                ADD VL_RCAS_IN,     PARAM.RCAS_IN ;
                ADD VL_RCAS_OUT,    PARAM.RCAS_OUT ;
                ADD VL_R_DS256,     PARAM.R_DS256;
                ADD VL_R_DS257,     PARAM.R_DS257;
            }
        }

        VARIABLE_LIST   __custom_out_view_4
        {
            MEMBERS
            {
                ADD VL_IO_OPTS,     PARAM.IO_OPTS ;
                ADD VL_STATUS_OPTS, PARAM.STATUS_OPTS ;
                ADD VL_SP_RATE_DN,  PARAM.SP_RATE_DN ;
                ADD VL_SP_RATE_UP,  PARAM.SP_RATE_UP ;
                ADD VL_CHANNEL,     PARAM.CHANNEL ;
                ADD VL_FSTATE_TIME, PARAM.FSTATE_TIME ;
                ADD VL_FSTATE_VAL,  PARAM.FSTATE_VAL ;
                ADD VL_SHED_OPT,    PARAM.SHED_OPT ;
            }
        }
    }
}
#endif

/*
******************************************************************************
** Project DDL Includes
******************************************************************************
*/

#include "1000_Variables.ddl"
#include "1000_Visualizations.ddl"
#include "1000_Methods.ddl"
#include "1000_Menus.ddl"
#include "1000_Test_Case_Conditional.ddl"
#include "1000_Test_Case_Graph.ddl"
#include "1000_Test_Case_Chart.ddl"
#include "1000_Test_Case_Image.ddl"
#include "1000_Test_Case_Menu.ddl"
#include "1000_Test_Case_Grid.ddl"
#include "1000_Test_Case_File_and_List.ddl"
#include "1000_Test_Case_Misc.ddl"
#include "1000_CustomFB.ddl"
#include "1000_ChannelTB.ddl"
#include "1000_VisualTB.ddl"
#include "1000_DataTypesTB.ddl"
#include "1000_CondTB1.ddl"
#include "1000_CondTB2.ddl"
