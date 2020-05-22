/*****************************************************************************
*                                                                            *
*                     SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                          *
*                                D-85540 Haar                                *
*                        Phone: ++49-89-4 56 56-0                            *
*                          Fax: ++49-89-4 56 56-3 99                         *
*                                                                            *
*                            SOFTING CONFIDENTIAL                            *
*                                                                            *
*                     Copyright (C) SOFTING IA GmbH 2012                     *
*                             All Rights Reserved                            *
*                                                                            *
* NOTICE: All information contained herein is, and remains the property of   *
*   SOFTING Industrial Automation GmbH and its suppliers, if any. The intel- *
*   lectual and technical concepts contained herein are proprietary to       *
*   SOFTING Industrial Automation GmbH and its suppliers and may be covered  *
*   by German and Foreign Patents, patents in process, and are protected by  *
*   trade secret or copyright law. Dissemination of this information or      *
*   reproduction of this material is strictly forbidden unless prior         *
*   written permission is obtained from SOFTING Industrial Automation GmbH.  *
******************************************************************************
******************************************************************************
*                                                                            *
* PROJECT_NAME             Softing FF/PA FD 2.42                             *
*                                                                            *
* VERSION                  FF - 2.42                                         *
*                          PA - 2.42 (beta)                                  *
*                                                                            *
* DATE                     16. April 2012                                    *
*                                                                            *
*****************************************************************************/

/* ===========================================================================

FILE_NAME          appl_if.c



FUNCTIONAL_MODULE_DESCRIPTION
  This module contains the main routines of the APPL task.

  Due to the OS interface each task has to provide an init routine and a main
  task routine. With appl_init() and appl_task() this module implements both
  routines.

  The application task is active during the device-startup phase only. When
  the APPL task receives its system start event it has to manage the device-
  startup phase. After the device-startup phase the APPL task becomes inactive.

=========================================================================== */
//  #include "keywords.h"
  #include <softing_base.h>
  #include <hm_if.h>
  #define  MODULE_ID      (COMP_FAPP + MOD_APPL_IF)

INCLUDES
  #include <string.h>

  #include "base.h"
  #include "osif.h"
  #include "hw_if.h"
  #include "fdev_cfg.h"
  #include "fdc_api.h"
  #include "fbs_api.h"
  #include "ffbl_api.h"
  #include "appl_int.h"
  #include "version.h"
  #include "appl_alert.h"
  #include "mnassert.h"
  #include "mn_advanced.h"
  #include "faultpublic.h"
  #include "eepshim.h"
  #include "mn_working_times.h"
  #include "nvutils.h"
  #include "watchdog.h"

LOCAL_DEFINES

  #define E_NV_DATA_AVAILABLE       0x0000U
  #define E_APPL_NV_RAM             0x0001U
  #define E_FDC_NV_RAM              0x0002U
  #define E_FBS_NV_RAM              0x0004U
  #define E_EXTRA_NV_RAM            0x0008U
  /* EXAMPLE FOR USE OF EEP BLOCK: define a flag that might be used to indicate a not valid NV-RAM content at start-up */
  //#define E_EXAMPLE_NV_RAM          0x0010U
  //#define E_BLK3_NV_RAM             0x0100U


  /* EXAMPLE FOR USE OF EEP BLOCK: The blocks EEP_APPL_BLK2 and EEP_APPL_BLK3 are not used currently.
                                   Include eep_if.h within the files where you want to access the NV RAM
  #define EXAMPLE_NV_RAM_BLOCK     EEP_APPL_BLK2
  */


LOCAL_TYPEDEFS

#if 0
  /* EXAMPLE FOR USE OF EEP BLOCK: sample data structure */
  typedef struct
  {
    USIGN32 u32val;
    USIGN16 u16val;
  }T_EXAMPLE_STRUCT;
#endif //0

FUNCTION_DECLARATIONS
  FUNCTION LOCAL VOID appl_config (VOID);
  FUNCTION LOCAL VOID appl_start (VOID);
  FUNCTION LOCAL BOOL appl_check_nv_ram (VOID);
  FUNCTION LOCAL USIGN16 appl_apply_for_nv_ram (VOID);
//  FUNCTION LOCAL VOID appl_store_appl_ident (VOID);
  FUNCTION LOCAL USIGN16 appl_calc_extra_nv_ram_size (const T_FBIF_DICTIONARY *p_fbif_dict);
  FUNCTION LOCAL VOID appl_get_serial_number (STRINGV *p_fdc_ser_no, STRINGV *p_fbs_ser_no);
  FUNCTION LOCAL VOID appl_load_new_fdc_config (VOID);
  FUNCTION LOCAL VOID appl_synchronize_fbap_with_device (VOID);
#if 0
  /* EXAMPLE FOR USE OF EEP BLOCK: these functions need not to be located in this module but in any other */
  FUNCTION LOCAL USIGN8 example_check_nv_ram();
  FUNCTION LOCAL USIGN8 example_apply_for_nv_ram();
  FUNCTION LOCAL VOID   example_store_defaults();
#endif

EXPORT_DATA

IMPORT_DATA

LOCAL_DATA

#ifndef _lint //Softing identification, to be in the image but not referenced
#include "cs_fwinf.h"                            /* CONSTANT SEGMENT DEFINITION */
  STATIC FORCE_REF const uint8_t serial_nr[]  = DEV_SERIAL_NR;
  STATIC FORCE_REF const uint8_t version_nr[] = FW_VERSION;
  STATIC FORCE_REF const uint8_t copyright[]  = COPYRIGHT;
#include "cs_def.h"                              /* DEFAULT CONSTANT SEGMENT */
#endif

#if defined (SW_DOWNLOAD) && defined (FBK2_HW)
  #include "cs_foot.h"                            /* CONSTANT SEGMENT DEFINITION */
    STATIC FORCE_REF const uint8_t footprint_string[16] = FOOTPRINT_STRING;
  #include "cs_def.h"                              /* DEFAULT CONSTANT SEGMENT */
#endif

#if 0
  // This is a container for the Device ID from HART command 0
#define DEVICE_ID_INVALID UINT32_MAX //Something that command 0 will never produce
static volatile u32 Appl_DeviceID = DEVICE_ID_INVALID;
#endif

/* Provide const interface functions to the FB shell -------------------------- */
const T_FBS_CALL_FDEV_FUNCT mnfbs_call_fdev_funct =
{
    .a_of_read_hndl_RESB = Appl_read_handler_RESB,
    .a_of_write_hndl_RESB    = Appl_write_handler_RESB,
    .a_of_background_RESB    = Appl_background_RESB,
    .a_of_read_hndl_FCTB     = NULL,
    .a_of_write_hndl_FCTB    = NULL,
    .a_of_get_default_value  = Appl_get_default_value,
    .a_of_blk_state_check    =
#ifdef FBL_BLOCK_INST
        Appl_check_block_state,
#else
        NULL,
#endif
    .a_of_verify_nv_ram      = Appl_verify_nv_ram,
};


/* Provide a const interface function to the function block layer ------------ */
const T_FFBL_CALL_FDEV_FUNCT  ffbl_call_fdev_funct =
{
    .a_of_chan_unit_check   =
#if defined AI_BLOCK_AVAILABLE || defined AO_BLOCK_AVAILABLE
        Appl_check_channel_unit,
#else
        NULL,
#endif
#ifdef USE_FIELD_DIAGNOSTICS /* ------------------------------------------- */
    .a_of_fd_get_recomm_act = Appl_get_recommend_fd_action,
    .a_of_fd_get_diag_value = Appl_get_diagnostic_value,
#endif /* USE_FIELD_DIAGNOSTICS */

};

/****************************************************************************/

FUNCTION GLOBAL VOID appl_init (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called during device startup phase by the OS interface. It
  a) initializes the local variables
  b) creates an application task
  c) provides interface functions that are used by the FB shell and the
     function block layer

  ad b) The creation of an application task is mandatory. The application
        task must at least handle the system-start event

  ad c) The application layer provides interface functions to the FB shell
        layer via the structure 'fbs_call_fdev_funct'.

        The functions 'a_of_read_hndl_<xxx>' and 'a_of_write_hndl_<xxx>' are
        optional. These functions are used to inform the application layer about
        read and write accesses to resource or function block parameters.
        In appl_res.c the two functions 'Appl_read_handler_RESB' and
        'Appl_write_handler_RESB' are implemented as examples.

        The function 'a_of_chan_unit_check' is called by analog input and analog
        output blocks during the device startup phase and each time the CHANNEL
        or the XD_SCALE parameter is written. The 'a_of_chan_unit_check' routine
        has to check whether the channel matches the XD_SCALE. If there is a
        mismatch the checking routine shall return with a negative result. In
        this case the function block will indicate a configuration error and
        stay in out-of-service. If the device has neither an analog input nor
        analog output block the checking routine is not required and
        'a_of_chan_unit_check' can be set to NULL.

        The function 'a_of_get_default_value' is called when the device has to start
        or to restart with default values. It is called for each parameter that
        has got a Y-flag in the GenVFD script. The 'a_of_get_default_value'
        routine can be used to set a default value that is different from the
        default value in the GenVFD script.

        The function 'a_of_verify_nv_ram' is used to check periodically the
        values in the EEP ram-image against the values stored in the non-
        volatile memory. The routine Appl_verify_nv_ram() is implemented as
        an example of such a checking routine.

        If block instantiation is supported the APPL task has to provide a
        function via 'a_of_blk_state_check'. This interface function is called
        each time a block is activated or deleted. The application then can
        accept or reject the activation or deletion of the block.

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  /* Initialize variables ------------------------------------------------- */

  tag_len_16 = FALSE; /* The tags are 32 byte long. To use 16 byte tags
                         set the flag tag_len_16 to TRUE.
                      */
    appl_config ();

#ifdef SW_DOWNLOAD
    /* This used to be after creating the task, for imponderable reasons
    The whole function may go in favor of C-init initialization
    */
    appl_dhl_init ();
#endif /* SW_DONWLOAD */


  /* Create application task ---------------------------------------------- */
  osif_create_task (
    APPL_TASK_ID,
    APPL_TASK_START_PRIO,  /* As the APPL task must be started before the
                              FDC (Field Device Communication) task and as
                              the OS interface starts the tasks in accordance
                              with their priority, during the startup phase
                              the priority must of the APPL task must be higher
                              than the priorty of the FDC task              */
    appl_task,
    0                      /* The application does not wait for events
                              during the startup phase                      */
  );

  /* This is where runtime populating of fbs_call_fdev_funct used to be.
  Do not remove in case we *ever* want to make the table mutable.
  The chances are slim since we can just un-const the init table and
  re-populate as needed
  */

  /* This is where runtime populating of ffbl_call_fdev_funct used to be.
  Do not remove in case we *ever* want to make the table mutable.
  The chances are slim since we can just un-const the init table and
  re-populate as needed
  */

#ifdef SW_DOWNLOAD /* ----------------------------------------------------- */
  //Used to be here; moved up appl_dhl_init ();
#endif /* SW_DONWLOAD */

  /* This is where appl_nrv_init(); used to be.
  Do not remove in case we *ever* want it back. Now its init is at compile time
  */

  /* This is where appl_trn_init(); used to be.
  Do not remove in case we *ever* want it back. Now its init is at compile and
  C-init time
  */

  return;
}






FUNCTION GLOBAL VOID appl_task
  (
    IN T_EVENT  event
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This task function is called by the OS interface.

  The system-start event is the only mandatory event the APPL task must
  handle.

PARAMETERS
  event           OS_IF_EVENT_SYSSTART        system start event

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  if ( (event & OS_IF_EVENT_SYSSTART) != 0 )
  {
    appl_start ();

    /* Now, the startup phase of the APPL task is finished.
       The APPL task is prepared for the operational phase.
       For this reason the task is set to a low priority.
       Actually, this task is not activated anymore.
     */
    osif_create_task (
      APPL_TASK_ID,
      APPL_TASK_PRIO,         /* During the operational phase the APPL task
                                 has a low priority                       */
      NULL,
      0
    );
  }

  if ( (event & ~OS_IF_EVENT_SYSSTART) != 0  )
  {
    _FAPP_FATAL (XCP_FAPP_INVALID_OS_EVENT,XCP_FAPP_BASE_TASK,event);
  }

  return;
}





FUNCTION LOCAL VOID appl_config (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the application task routine when the system-start
  event has been received.

  It checks and possibly loads the configuration data to the communication stack

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN16  nv_data_available;
  USIGN16  extra_nv_ram_size;

FUNCTION_BODY

  /* Load FBIF dictionary to FB shell ------------------------------------- */
  /* ---------------------------------------------------------------------- */
  fbs_load_fbif_dict (&fbif_dictionary);


  /* Check and possibly reconfigure the NV-RAM ---------------------------- */
  /* ---------------------------------------------------------------------- */
  nv_data_available = E_NV_DATA_AVAILABLE;

  /* EXAMPLE FOR USE OF EEP BLOCK: check whether the NV-RAM content is valid or not.
                                   the check should be done here if the data are important for configuration of FF device otherwise
                                   could be done in any other module during start-up/initialization */
#if 0
  if (example_check_nv_ram() != E_OK)
  {
    nv_data_available |= E_EXAMPLE_NV_RAM;
  }
#endif

  if (appl_check_nv_ram () != E_OK)
  {
    nv_data_available |= E_APPL_NV_RAM;
  }

  if (fdc_check_nv_ram () != E_OK)
  {
    nv_data_available |= E_FDC_NV_RAM;
  }

  if (fbs_check_nv_ram () != E_OK)
  {
    nv_data_available |= E_FBS_NV_RAM;
  }

  if ((extra_nv_ram_size = appl_calc_extra_nv_ram_size (&fbif_dictionary)) != 0)
  {
    if (fbs_check_extra_nv_ram (extra_nv_ram_size) != E_OK)
    {
      nv_data_available |= E_EXTRA_NV_RAM;
    }
  }

  if(error_IsFault(FAULT_NVM_WRITE) || (nv_data_available != E_NV_DATA_AVAILABLE))
  {
    /* Check of NV-RAM was not successful / start device with default data */
    /* ------------------------------------------------------------------- */
    if (appl_apply_for_nv_ram () == E_OK)
    {
      nv_data_available &= ~E_APPL_NV_RAM;
    }

    if (fdc_apply_for_nv_ram () == E_OK)
    {
      nv_data_available &= ~E_FDC_NV_RAM;
    }

    if (fbs_apply_for_nv_ram () == E_OK)
    {
      nv_data_available &= ~E_FBS_NV_RAM;
    }

    if (extra_nv_ram_size != 0)
    {
      if (fbs_apply_for_extra_nv_ram (extra_nv_ram_size) == E_OK)
      {
        nv_data_available &= ~E_EXTRA_NV_RAM;
      }
    }

    MN_RT_ASSERT(nv_data_available == E_NV_DATA_AVAILABLE);
    /*EXPLANATION: A failure would indicate that the fixed layout
    of NVRAM doesn meet the expected layout
    */

    error_SetFault(FAULT_NVM_WRITE); //force reinit

  }

}


static bool_t select_GroupRecover(u8 volid, u8 flags)
{
    UNUSED_OK(volid);
    return ((flags & NVMFLAG_GROUP_RECOVER) != 0);
}


/** \brief Fills PTB parameters stored outside PTB STATIC and NV "eep blocks"

Must be called *after* fbs_start(), otherwise it it will be overwritten
*/
static void appl_trn_sync_with_device (void)
{
    /* Enabling HART communication is hoisted to the caller:
    It is responsible for getting device id
    */
    //osif_set_event  (HM_TASK_ID, HART_START_EVENT);

    /* Wait for the HART master to synchronize the local data base
     with the HART device's data base ------------------------------------- */
    //(void)osif_wait_event (APPL_TASK_ID, OS_IF_EVENT_RESUME); //cast OK because no event action
}





FUNCTION LOCAL VOID appl_start (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the application task routine after the
  configuration phase.

  In this function
  - the NV_RAM_CYCLE_TIME and EXTRA_NV_RAM_CYCLE_TIME is set (optional)
  - unnecessary blocks are disabled (for modular devices only / optional)
  - the device serial number is prepared
  - the FB shell is started
  - transducer block parameters are synchronized with application objects (optional)
  - the field device communication stack is started

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
    USIGN16  result;

    //This is  needed no longer - after replacement of eep
#if 0
    /* Set NV_RAM_CYCLE_TIME ------------------------------------------------ */
    /* NOTE: Define is in file fdev_cfg.h. Unit is [s]. --------------------- */
    fbs_set_nv_ram_cycle_time (NV_RAM_CYCLE_TIME);

    /* Set EXTRA_NV_RAM_CYCLE_TIME ------------------------------------------ */
    /* NOTE: Define is in file fdev_cfg.h. Unit is [s]. --------------------- */
    fbs_set_extra_nv_ram_cycle_time (EXTRA_NV_RAM_CYCLE_TIME);
#endif

    /* If block instantiation or capability levels are supported
     fdc_set_block_state() may be used to overwrite the 'BLOCK_INSTANCE' key
     generated by GenVFD.                                                   */

#if (RES_VAL_DEV_TYPE == 0x0100)  /* Softing's Jazz Application */
        /* To show the usage of fdc_set_block_state() in Softing's Jazz
         Application the second integrator block is disabled                    */

        fbs_set_block_state (5,BLK_INACTIVE); /* ITFB_2 */
#endif /* RES_VAL_DEV_TYPE == 0x0100 */

    //MN_ENTER_CRITICAL(); //another piece that has no business running with interrupts enabled

        STRINGV    fbs_device_serial_number[FDC_SER_NO_LEN];
        STRINGV    fdc_device_serial_number[FDC_SER_NO_LEN];

        /*We are boosting HM task priority so that FF stack doesn't run
        until we are ready. This is subtle and fragile but it ain't my design :)
        */
        osif_create_task (HM_TASK_ID,
                  HM_TASK_START_PRIO,   /* Run with higher prio during startup phase */
                  task_hm_base_routine,
                  (HART_START_EVENT  | HART_RECEIVE_END_EVENT | HART_ERROR_EVENT |
                   OS_IF_EVENT_TIMER | OS_IF_EVENT_REQRES | OS_IF_EVENT_EEPROM)
                 );
        /* NOTE: OS_IF_EVENT_EEPROM is otherwise unused and used to retrigger the task
        */
        appl_synchronize_fbap_with_device ();

        /* Prepare device serial number ----------------------------------------- */
        appl_get_serial_number (fdc_device_serial_number,fbs_device_serial_number);

        /*------------------------------------------------------------------------*/
        /* NOTE:                                                                  */
        /* Softing’s FBK and FBK2 have got a PROM holding a unique serial number. */
        /* The communication stack will overwrite the last nine octets of the     */
        /* application’s serial number by the serial number stored in the PROM.   */
        /*------------------------------------------------------------------------*/

        osif_create_task (
          HM_TASK_ID,
          HM_TASK_PRIO,
          NULL,
          0);

        /* Start FB shell ------------------------------------------------------- */
        result = fbs_start (fbs_device_serial_number);
        if(result != E_OK)
        {
            //appl_load_new_fdc_config();
            _FAPP_FATAL (XCP_FAPP_FDC_ERR,XCP_FAPP_IDENT_LOAD,result);
        }
        if(result == E_OK)
        {
            ram_InitBrutal(NVMFLAG_INIT_2);

            /* Synchronize (transducer) block data with sensor/actuator data -------- */
            //appl_synchronize_fbap_with_device ();

#ifdef SW_DOWNLOAD /* ----------------------------------------------------- */
            appl_dlh_start ();
#endif /* SW_DONWLOAD */

            //If FAULT_NVM_WRITE is set, commit all potentally affected data to NVMEM
            if(error_IsFault(FAULT_NVM_WRITE))
            {
                //No longer needed because it duplicated default init of it : appl_store_appl_ident ();
                (void)eepshim_Set_ApplDeviceId(NULL);
                //Make sure it gets to FRAM
                (void)eep_write (APPL_DEVICE_ID,0,0,EEP_WAIT);
                appl_load_new_fdc_config ();
                ErrorCode_t err = ram_CommitRangeExt(select_GroupRecover, wdog_WatchdogTrigger);

                //ErrorCode_t err = nvmem_FixByFlag(NVMFLAG_GROUP_RECOVER, NVMFLAG_GROUP_RECOVER);
                UNUSED_OK(err); //if fails, will retry on the next power-up
            }

#ifdef USE_FIELD_DIAGNOSTICS /* ----------------------------------------- */
            appl_dia_start_field_diagnostics ();
#endif /* USE_FIELD_DIAGNOSTICS */

            InitialWorkingTimes(fbs_get_block_inst(ID_PTB_1));

            /* Start communication stack -------------------------------------------- */
            result = fdc_start ((STRINGV *)fdc_device_serial_number);

            if (result != E_OK)
            {
                _FAPP_FATAL (XCP_FAPP_FDC_ERR,XCP_FAPP_IDENT_LOAD,result);
            }
        }
    //MN_EXIT_CRITICAL();
}







FUNCTION LOCAL USIGN8 appl_check_nv_ram (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  During the startup phase the application has to check if there are appropriate
  configuration data in the non-volatile memory.

  In this example the APPL task stores the manufacturer-id, the device-type,
  the device-revision, the dd-revision and a configuration-revision in an
  application-specific block of the non-volatile memory.

  This subroutine is used to check if the device identification stored in
  non-volatile memory matches the device identification deposited in the
  firmware.

  Additionally, if the (optional / hardware-dependent) NV-Erase jumper is set,
  the stored device identification is treated to be not the expected one,
  what will cause the calling function to skip all non-volatile data and set
  all configuration data to its default values.

PARAMETERS
  None

RETURN_VALUES
  E_OK            The stored device identification is the expected one.

  E_ERROR           The stored device identification is not the expected one.
                  The calling function will load new configuration data and
                  the device will enter the FF network with a default con-
                  figuration.
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  T_APPL_DEVICE_ID *  p_appl_cfg;
  T_EEP_RESULT        eep_result;
  USIGN8              result;

FUNCTION_BODY

  eep_result = eep_provide_block (APPL_DEVICE_ID,sizeof(T_APPL_DEVICE_ID),(VOID * *)&p_appl_cfg);

  if (eep_result != EEP_OK)
  {
    return E_ERROR;
  }

  if (p_appl_cfg->manufacturer_id != RES_VAL_MANUFAC_ID)        /* RES_VAL_MANUFAC_ID from fdev_cfg.h */
  {
    result = E_ERROR;
  }
  else if (p_appl_cfg->device_type != RES_VAL_DEV_TYPE)         /* RES_VAL_DEV_TYPE from fdev_cfg.h */
  {
    result = E_ERROR;
  }
  else if (p_appl_cfg->device_revision != RES_VAL_DEV_REV)      /* RES_VAL_DEV_REV from fdev_cfg.h */
  {
    result = E_ERROR;
  }
  else if (p_appl_cfg->dd_revision != RES_VAL_DD_REV)           /* RES_VAL_DD_REV from fdev_cfg.h */
  {
    result = E_ERROR;
  }
  else if (p_appl_cfg->config_revision != DEV_CONFIG_REVISION)  /* DEV_CONFIG_REVISION from fdev_cfg.h */
  {
    result = E_ERROR;
  }
  else if (hw_get_nvram_erase_jumper() != FALSE)                        /* NVRAM erase jumper is set */
  {
    result = E_ERROR;
  }
  else
  {
    result = E_OK;
  }

  return result;
}






FUNCTION LOCAL USIGN16 appl_apply_for_nv_ram (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function applies for the non-volatile memory used by the application.

PARAMETERS
  None

RETURN_VALUES
  E_OK          The request for non-volatile memory was accepted
 E_ERROR          The request for non-volatile memory was not accepted
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  T_EEP_BLOCK_DSC     eep_block_dsc;
  T_EEP_RESULT        eep_result;

FUNCTION_BODY

  /* Apply for data block in the non-volatile memory ---------------------- */
  eep_block_dsc.block_id           = APPL_DEVICE_ID;
  eep_block_dsc.auto_write_length  = 0;
  eep_block_dsc.block_size         = sizeof(T_APPL_DEVICE_ID);

  eep_result = eep_config_change(1,&eep_block_dsc);

  if (eep_result == EEP_OK)
  {
    return E_OK;
  }
  else
  {
    return E_ERROR;
  }
}







FUNCTION LOCAL USIGN16 appl_calc_extra_nv_ram_size
  (
    IN const T_FBIF_DICTIONARY *      p_fbif_dict
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  During the device startup phase the application has to make sure that all blocks
  are asked for there need of extra non-volatile memory. The application has to
  summarize the need of all FF blocks and then to apply for the total sum by
  calling fbs_apply_for_extra_nv_ram().

  Currently the IT block is the only standard block that needs extra non-volatile
  memory. In dependance on the application there may be transducer blocks with
  a need of extra non-volatile memory

PARAMETERS
  p_fbif_dict         Pointer to the FBIF dictionary (The dictionary is
                      generated by GenVFD)

RETURN_VALUES
  Total size of extra non-volatile memory
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8   i;
  USIGN16  extra_nv_ram_size;

FUNCTION_BODY

  extra_nv_ram_size = 0;

  for (i = 0;i < p_fbif_dict->no_of_blocks; i++)
  {
    if (p_fbif_dict->fbif_block_dir[i].block_type == FUNCT_BLK)
    {
      #ifdef IT_BLOCK_AVAILABLE /* --------------------------------------- */
      F_BLOCK const * p_hdr = &p_fbif_dict->fbif_block_dir[i].p_block_dft->blk_header;

      if (p_hdr->profile == PROFILE_IT_BLK)
      {
        extra_nv_ram_size += ffbl_it_get_extra_nv_ram_size ();
      }

      #endif /* IT_BLOCK_AVAILABLE --------------------------------------- */
    }
#if 0 //AK: empty anti-MISRA block deactivated
    else if (p_fbif_dict->fbif_block_dir[i].block_type == TRANS_BLK)
    {
      /* if extra NV RAM is needed then calculate the size of extra NV RAM */ ;
    }
#endif
  }

  return extra_nv_ram_size;
}


FUNCTION LOCAL VOID appl_load_new_fdc_config (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function will be called if the device starts with default data. It

  - prepares the configuration data of the field device communication stack

  - loads the configuration data to the field device communication stack

  In this example the configuration data are imported from fdev_cfg.h.
  In a real device some of the configuration data may be provided by
  the senser and actuator hardware or by other device-specific interfaces.

  NOTE: If the function call of the function fdc_load_new_config() returns
        an error display it if possible. A restart of the device will not
        change the behavior!

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  T_FDC_DEVICE_START  fdc_device_start;
  T_FDC_BUSPARAM      fdc_buspar;
  USIGN16             result;

FUNCTION_BODY

  /* Prepare the configuration data for the communication stack ----------- */
  memset(fdc_device_start.default_pd_tag, '_',DEFAULT_PD_TAG_SIZE);
    size_t len = strlen(DEV_DEFAULT_PD_TAG);
    memcpy(fdc_device_start.default_pd_tag, DEV_DEFAULT_PD_TAG,        /*  from fdev_cfg.h */
         min(len, DEFAULT_PD_TAG_SIZE));

  fdc_device_start.sm_operational       = DEV_SM_OPERATIONAL;        /*  from fdev_cfg.h */
  fdc_device_start.default_node_address = DEV_DEFAULT_NODE_ADDRESS;  /*  from fdev_cfg.h */
  fdc_device_start.default_dev_type     = DEV_DEFAULT_DEV_TYPE;      /*  from fdev_cfg.h */

  /* Set the 'fastest' busparameters possible for this device ------------- */
  fdc_buspar.slot_time_min           = DEV_ST_MIN;  /* DEV_ST_MIN        from fdev_cfg.h */
  fdc_buspar.min_inter_pdu_delay_min = DEV_MID_MIN; /* DEV_MID_MIN       from fdev_cfg.h */
  fdc_buspar.max_reply_delay_min     = DEV_MRD_MIN; /* DEV_MRD_MIN       from fdev_cfg.h */

    /* Call the communication stack with default configuration data --------- */
    result = fdc_load_new_config (&fdc_device_start, &fdc_buspar);
    /* Display the error condition if possible (display or LED) */
    /* Note, that a restart will not change the behavior!       */

    MN_RT_ASSERT(result == E_OK);         /* Break in debugger       */
}



//-----------------------------------------------------------------------------

#define DEVICE_ID_STRLEN                (8u)
#define ITOA_CONVERSION_MAXINT          (10000000u)
#define ITOA_CONVERSION_MAXMAXINT       (10u * ITOA_CONVERSION_MAXINT)
#define ZERO_CHARACTER_VAL              (0x30U)
#define DIGIT_TO_ASCII(d)               ((STRINGV)((d) + ZERO_CHARACTER_VAL))

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
    Convert UINT32 number to the 8 char string.
    The function verifies whether the number fits in 8 chars, and truncates it from the LEFT.
    Number converts with left 0's: 34 => "00000034"

PARAMETERS
  USIGN32           Uintnum -- number to convert to ASCII 8char string
  STRINGV *pCharStr    ptr to teh 8 chart string

RETURN_VALUES
  None
----------------------------------------------------------------------------*/

FUNCTION LOCAL VOID FF_itoa(USIGN32 Uintnum, STRINGV *pCharStr)
{
    USIGN32 Divider   = ITOA_CONVERSION_MAXINT;
    USIGN32 Number    = Uintnum;
    USIGN32 StrIndex;

    // Clear the string
    for (StrIndex = 0; StrIndex < DEVICE_ID_STRLEN; StrIndex++)
    {
        pCharStr[StrIndex] = 0;                                  // Zero the string
    }

    // If Number too big for 8 char - truncate from above,
    // Thus we do not need to watch for the StrIndex. We make
    // the number to fit into the string.
    if (Number >= ITOA_CONVERSION_MAXMAXINT)
    {
        Number %= ITOA_CONVERSION_MAXMAXINT;
    }

    StrIndex = 0;
    while (Divider > 1u)
    {
        pCharStr[StrIndex] = DIGIT_TO_ASCII(Number / Divider);      // Get a char for the digit
        StrIndex++;                                                 // Next char
        Number   %= Divider;                                        // Get the remainder
        Divider  /= 10u;                                            // Next digit
    }

    // ones are left
    pCharStr[StrIndex] = DIGIT_TO_ASCII(Number);                    // Get a char for the digit
}





/** \brief Computes andreturns the HART device identifier, which
  was some time returned by CMD0.
\return  HART device id as integer
*/
USIGN32 HART_get_dev_id (void)
{
        /* Decode HART device id */
        /*-----------------------*/
    const u8 *h = hm_GetAPPHeader(NULL)->appheader;
    u32 HM_hart_dev_id = h[5];
    HM_hart_dev_id += ((USIGN32) h[4]) * 0x100UL;
    HM_hart_dev_id += ((USIGN32) h[3]) * 0x10000UL;

    return (HM_hart_dev_id);
}



FUNCTION LOCAL VOID appl_get_serial_number
  (
    IN OUT STRINGV *   p_fdc_ser_no,
    IN OUT STRINGV *   p_fbs_ser_no
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function provides the serial number of the device. The calling function
  has to provide a buffer with a minimum length of 22 bytes.

  In this example the serial number is a constant. In a real device the serial
  number may be provided by the sensor and actuator hardware or by a device-
  specific interface.

PARAMETERS
  p_fdc_ser_no      Pointer to a buffer with a minimum length of 22 bytes

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN16 i, loop_count, serial_array_end, ser_len, ser_size;

  STRINGV        slave_dev_id[8];

FUNCTION_BODY

      memset (p_fdc_ser_no,'_',FDC_SER_NO_LEN);
      memset (p_fbs_ser_no,' ',FDC_SER_NO_LEN);

    u32 HM_hart_dev_id = HART_get_dev_id();
    if(HM_hart_dev_id == 0U) //This is solely for user experience upgrading from R2
    {

        osif_set_event  (HM_TASK_ID, HART_START_EVENT);
        /* EXPLANATION:
        On success, this will reset the device transparently to the user, with id repaired.
        On failure, it will stay at 0. Who cares?
        */

        //Wait more than enough for reset to occur
        wdog_WatchdogTrigger();
        OS_Delay(300);
        wdog_WatchdogTrigger();
        OS_Delay(300);

        //If the device still has 0 id, just go on
    }

    FF_itoa(HM_hart_dev_id, slave_dev_id);


    ser_len  = (USIGN16)strlen((void *)slave_dev_id);
    ser_size = sizeof(slave_dev_id);

    if (ser_len > ser_size) /* if serial_nr without terminating zero */
    {
        loop_count       = min(ser_size, (USIGN16) FDC_SER_NO_LEN); /* if serial_nr array longer than p_fdc_ser_no[] */
        serial_array_end = ser_size-1u;  /* the end of the array */
    }
    else /* serial_nr has a terminating zero */
    {
        loop_count       = min(ser_len, (USIGN16) FDC_SER_NO_LEN);  /* if serial_nr string size longer than p_fdc_ser_no[] */
        serial_array_end = ser_len-1u;   /* the end of string */
    }

    for (i = 0;i < loop_count; i++)
    {
        /* Copy backwards, so that the serial number is right-aligned
           and possibly truncated at its left side ---------------------------- */
        p_fdc_ser_no[(FDC_SER_NO_LEN-1)-i] =  slave_dev_id[serial_array_end-i];
        p_fbs_ser_no[(FDC_SER_NO_LEN-1)-i] =  slave_dev_id[serial_array_end-i];
    }

}


FUNCTION LOCAL VOID appl_synchronize_fbap_with_device (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This optional function is used to synchronize resource and transducer block
  parameters with application objects. It is called after fbs_start(), as
  fbs_start() calls the start routines all FF blocks, and before fdc_start(),
  as fdc_start() enters the livelist and starts the function block schedule.

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  /* Perform action that are necessary to synchronize resource and transducer
     block parameters with application objects
  */

  appl_trn_sync_with_device ();

  return;
}





FUNCTION PUBLIC VOID appl_if_modify_config_rev (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function used to implement a non-standard reset of the non-volatile
  memory.

  It increments the Config Revision, which is part of the device identifier,
  and stores the modified value in the non-volatile memory.

PARAMETERS
  None

RETURN_VALUES
  None
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  T_APPL_DEVICE_ID *  p_appl_cfg;
  T_EEP_RESULT        eep_result;

FUNCTION_BODY

    //MN_NVMEM_LOCK();

    /* Set a pointer to the EEPROM block with the application data ----------- */
    eep_result = eep_provide_block (APPL_DEVICE_ID,sizeof(T_APPL_DEVICE_ID),(VOID * *)&p_appl_cfg);

    /* Write an incremented value to the EEPROM ----------------------------- */
    if (eep_result == EEP_OK)
    {
        eep_result = eep_start_write (APPL_DEVICE_ID);
        p_appl_cfg->config_revision++;
    }

    if (eep_result == EEP_OK)
    {
        eep_result = eep_write (APPL_DEVICE_ID,0,sizeof(T_APPL_DEVICE_ID),EEP_WAIT);
    }

    //eep_ReleaseMutex();

    if (eep_result != EEP_OK)
    {
        _FAPP_FATAL (XCP_FAPP_EEP_ERR,XCP_FAPP_CONFIG_WRITE,eep_result);
    }
}




