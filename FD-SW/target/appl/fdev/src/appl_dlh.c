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

FILE_NAME          appl_dlh.c


FUNCTIONAL_MODULE_DESCRIPTION

  This module implements an example of a domain download handler. The download
  handler is the counter part of the download server which is a part of the
  System Management Agent.

  The download server implements the download state machine as specified
  in FF-883. The download handler is responsible for checking and storing
  the downloaded domain. Both, download handler and download server implement
  the software download function of a device.

  This module is intended to be an example for class 1 as well as for class 3
  software download. Its current state implements an example for class 1
  software download only. Future releases of this module will also implement
  an example of class 3 software download.

  This module is intended to be an example for single domain software download
  as well as for multi-domain software download. Its current state implements
  an example for single domain software download only. Future releases of this
  module will also implement an example of multi-domain software download.

=========================================================================== */
  #include <keywords.h>
  #define  MODULE_ID      (COMP_FAPP + MOD_APPL_DLH)

INCLUDES
  #include <base.h>
  #include <hw_if.h>
  #include <except.h>
  #include <osif.h>
  #include <eep_if.h>
  #include "swdl_cfg.h"
  #include "swdl_api.h"
  #include "appl_int.h"

  #include "appl_svi.h"

#if 0 //in support of a failed attempt
#include <fbap.h>
#include "eepshim.h"
#endif


LOCAL_DEFINES


  #define _INIT_PLATFORM_SPECIFIC_DWNLD_FUNC        init_svi_dwnld()

#if 0 //removed in favor of static init: appl_fd_sw_available() just returns TRUE for Class 1
  #define _FD_SW_IS_AVAILABLE                       (appl_fd_sw_available() != FALSE)
#endif

  #define _PREPARE_DWNLD_OF_FD_SW                   start_prepare_swdl()

  #define _FINISH_FD_DWNLD_PREPARATION_PHASE        finish_prepare_swdl()

  #define _FD_SW_DOM_READY_FOR_DWNLD

  #define _CHECK_FD_DOMAIN_HDR(p_dwnld_dom_hdr)                     \
                    appl_check_fd_dom_hdr (p_dwnld_dom_hdr)

  #define _STORE_FD_DOMAIN_HDR(p_dwnld_dom_hdr)                     \
                    appl_store_fd_dom_hdr (p_dwnld_dom_hdr)

  #define _CHECK_FD_DOMAIN_SEGM(segment_id,segment_len,p_segment)   \
                    appl_check_fd_dom_segm (segment_id,segment_len,p_segment)

  #define _STORE_FD_DOMAIN_SEGM(segment_id,segment_len,p_segment)   \
                    dwnld_handle_data(segment_id,segment_len,p_segment)

#if 0 //removed in favor of static init: complete_fd_dom_is_avail() just returns TRUE for the context it was called from
  #define _COMPLETE_FD_DOM_IS_AVAILABLE             (complete_fd_dom_is_avail() != FALSE)
#endif

  #define _RESET_FD_DOMAIN                          fwdl_reset_fddom()

  #define _FINISH_FD_DWNLD_ACTIVATION_PHASE         verify_activation()

  #define _ACTIVATE_FD_FW                           activate_fd_sw()


LOCAL_TYPEDEFS

FUNCTION_DECLARATIONS
  FUNCTION GLOBAL USIGN8 Appl_prepare_download
    (
      IN USIGN8               dom_id
    );

  FUNCTION GLOBAL const T_DOMAIN_HDR_API * Appl_cancel_download
    (
      IN USIGN8               dom_id
    );

  FUNCTION GLOBAL USIGN8 Appl_download_header
    (
      IN USIGN8               dom_id,
      IN T_DOMAIN_HDR_API *   p_dwnld_dom_hdr
    );

  FUNCTION GLOBAL USIGN8 Appl_download_segment
    (
      IN USIGN8               dom_id,
      IN USIGN8               segment_id,
      IN USIGN8               segment_len,
      IN USIGN8 *             p_segment
    );

  FUNCTION GLOBAL VOID Appl_activate_software
    (
      IN USIGN8               dom_id
    );

static const T_DWNLD_PROPERTY_API   appl_dwnld_prop =
{
    .resp_for_prepare                = SEND_WRITE_RESP_FOR_DWNLD_PREPARE, /* Class 1 */
    .max_time_for_preparation        = MAX_TIME_FOR_DWNLD_PREPARE,
    .max_time_for_activation         = MAX_TIME_FOR_SW_ACTIVATE,
};

typedef struct domdesc_t
{
    T_DOMAIN_HDR_API dh1;
    T_DOMAIN_DESCR_API dh2;
} domdesc_t;

const domdesc_t domainHdr =
{
    /*lint -save -e784 "Nul character truncated from string" OK:
    These strings are treated as character arrays of fixed length
    */
    .dh1 =
    {
        .manufacturer_id = FD_DOM_MFG_ID,
        .device_family = FD_DOM_FAMILY,
        .device_type = FD_DOM_DEV_TYPE,
        .device_revision = FD_DOM_DEV_REV,
        .dd_revision = FD_DOM_DD_REV,
        .software_revision = FD_DOM_SW_REV,
        .software_name = FD_DOM_SW_NAME
    },
    .dh2 =
    {
        .dom_name = FD_DOM_DOM_NAME
    }
    /*lint -restore
    */
};

#define appl_fd_dom_hdr domainHdr.dh1

//Bogus: AP definitions not used anywhere
#define appl_ap_dom_descr appl_fd_dom_descr
#define appl_ap_dom_hdr appl_fd_dom_hdr

//Totally bogus to satisfy API (multidomain not supported)
#define appl_ap_multidom_descr appl_fd_multidom_descr

//Totally bogus to satisfy API (multidomain not supported)
static const T_MULTIDOM_DESCR_API   appl_fd_multidom_descr =
{
    /*lint -save -e784 "Nul character truncated from string" OK:
    These strings are treated as character arrays of fixed length
    */
    .multidom_mfg_id = FD_DOM_MFG_ID,        /* As specified in FF-883 */
    .multidom_family = FD_DOM_FAMILY,        /* As specified in FF-883 */
    .instance = "stance",               /* As specified in FF-883 */
    .hardware_revision = 0,          /* As specified in FF-883 */
    .software_revision = SOFTWARE_FF_REVISION >>16,          /* As specified in FF-883 */
    /*lint -restore
    */
};
#define appl_fd_dom_descr domainHdr.dh2

static const  T_DWNLD_CFG_API appl_dwnld_cfg =
{
    .p_property                       = &appl_dwnld_prop,
    .p_fd_multidom_descr              = &appl_fd_multidom_descr,
    .p_ap_multidom_descr              = &appl_ap_multidom_descr,
    .p_fd_dom_descr                   = &appl_fd_dom_descr,
    .p_ap_dom_descr                   = &appl_ap_dom_descr,
    .p_fd_dom_hdr                     = &domainHdr.dh1,
    .p_ap_dom_hdr                     = &appl_ap_dom_hdr,
};


/****************************************************************************/

//MN redirect (must be redirected by linker)
const T_SMDL_CALL_FDEV_FUNCT  mnsmdl_call_fdev_funct =
{
    .a_of_prepare_download  = Appl_prepare_download,
    .a_of_cancel_download   = Appl_cancel_download,
    .a_of_download_header   = Appl_download_header,
    .a_of_download_segment  = Appl_download_segment,
    .a_of_activate_software = Appl_activate_software,
};

FUNCTION PUBLIC VOID appl_dhl_init (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

PARAMETERS
  None

RETURN_VALUES
  None

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
#if LINKER_REDIRECT_KLUDGE
    smdl_call_fdev_funct = mnsmdl_call_fdev_funct; //lint !e111 Don't reconfigure build/lint yet for a temporary workaround
#endif
#if 0
  smdl_call_fdev_funct.a_of_prepare_download  = Appl_prepare_download;
  smdl_call_fdev_funct.a_of_cancel_download   = Appl_cancel_download;
#endif

  _INIT_PLATFORM_SPECIFIC_DWNLD_FUNC;

#if 0
  smdl_call_fdev_funct.a_of_download_header   = Appl_download_header;
  smdl_call_fdev_funct.a_of_download_segment  = Appl_download_segment;
  smdl_call_fdev_funct.a_of_activate_software = Appl_activate_software;
#endif

  return;
}



FUNCTION PUBLIC VOID appl_dlh_start (VOID)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called in the device startup phases when the APPL task
  handles the SYSSTART event.

  With this function the download handler configures the download server.

  If the device has been power-cycled during a software download, the download
  handler has take the software download into a proper state.

  This function performs the following steps:
  a) Ask the download server about the state of the download procedure
  b) Configure the download server in dependence of the current state
  c) Complete the preparation of a download or the activation of the new
     software - if necessary

PARAMETERS
  None

RETURN_VALUES
  None

----------------------------------------------------------------------------*/
/* AK:
This function has been greatly simplified by const-izing the objects which
Softing chose to initialize at runtime for reasons unkown.
Some const objects are generic, some are specific to our Class 1 FW download.
For reference, see appl_dlh.c,C74623 in TFS, or even deeper in history.

Also, handling of state SWDL_DOM_DOWNLOADING has to be done in a loop
(actually 2 iterations), which Softing bug fix was found experimentally.

Since other unusual states are too transient, I can't make test cases for them,
so I left them alone.

Finally, for readability, if-else chain is replaced with a switch statement
*/
{
    T_DWNLD_STATE_API     dwnld_state;
    USIGN16               result;

    u8_least retries = 3U;

    do
    {
        /* Ask the download server about the state of the download procedure ---- */
        result = fdc_get_dwnld_state (&dwnld_state);

        if (result != E_OK)
        {
            _FAPP_FATAL (XCP_FAPP_FDC_ERR,XCP_FAPP_IDENT_LOAD,result);
        }

        /* Initialize the download property structure - AK: Now statically ------ */

        /* Initialize the download descriptor - now, statically ------------------ */

        /* Statically Initialized the download config structure ------------ */


        /* Provide the config data to the download server ----------------------- */
        result = fdc_config_dwnld_server (&appl_dwnld_cfg);

        if (result != E_OK)
        {
            _FAPP_FATAL (XCP_FAPP_FDC_ERR,XCP_FAPP_IDENT_LOAD,result);
        }

        /* Continue in the download procedure - if necessary -------------------- */
        switch(dwnld_state.fd_dwnld_state)
        {
            case SWDL_DOM_PREPARING:
            {
                /* The device was stopped while it was preparing a software download.
                   In case of NO_WRITE_RESP_FOR_DWNLD_PREPARE the reset may be
                   triggered by the download handler itself.                            */

                /* Finish the preparation phase. The possible results of the
                   preparation phase are SWDL_PREPARE_OK and SWDL_PREPARE_FAIL          */

                if (_FINISH_FD_DWNLD_PREPARATION_PHASE == E_OK)
                {
                  fdc_complete_dwnld_action (FD_SW_DOM_ID, SWDL_PREPARE_OK, NULL);
                }
                else /* Download preparation failed */
                {
                    //AK: Now initialized statically, _FD_SW_IS_AVAILABLE always available
                    fdc_complete_dwnld_action (FD_SW_DOM_ID, SWDL_PREPARE_FAIL, &appl_fd_dom_hdr);
                }
                break;
            }
            case SWDL_DOM_READY_FOR_DWNLD:
            {
                /* The device was stopped after the preparation has finished and before
                   the Download is started.                                            */

                _FD_SW_DOM_READY_FOR_DWNLD;
                break;
            }
            case SWDL_DOM_DOWNLOADING:
            {
                /* The device was stopped during a download process. As the download
                   server does not support download recovery, a partially stored domain
                   has to be reset.                                                    */

                _RESET_FD_DOMAIN;

                /* (The host will re-start the download procedure by sending a prepare
                   command)
                */
                break;
            }
            case SWDL_DOM_ACTIVATING:
            {
                /* The device was stopped while it was activating a downloaded software.
                   As the device restart is a mandatory step in the activation procedure
                   the reset was possibly triggered by the download handler itself      */

                /* Finish the activation phase. The possible results of the
                   activation phase are SWDL_ACTIVATE_OK and SWDL_ACTIVATE_FAIL         */

                if (_FINISH_FD_DWNLD_ACTIVATION_PHASE == E_OK)
                {
                    //AK: Now initialized statically, _FD_SW_IS_AVAILABLE always available
                    fdc_complete_dwnld_action (FD_SW_DOM_ID,SWDL_ACTIVATE_OK, &appl_fd_dom_hdr);
                }
                else /* The software activation failed */
                {
                    fdc_complete_dwnld_action (FD_SW_DOM_ID,SWDL_ACTIVATE_FAIL, NULL);
                }
                break;
            }
            default:
                //Unknown state but nothing to do
                break;
        }
        --retries;
    } while((dwnld_state.fd_dwnld_state == SWDL_DOM_DOWNLOADING) && (retries != 0U));

#if 0 //doesn't help
    if(retries == 0U)
    {
        //try to bring dl state to default
        eepshim_Set_nv_swdl_blk_dwnld_cfg(NULL);
        ram2nvramAtomic(NVRAMID_nv_swdl_blk_dwnld_cfg);
        Reset_CPU();
    }
#endif //0
}






FUNCTION GLOBAL USIGN8 Appl_prepare_download
  (
    IN USIGN8   dom_id
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the download server when a prepare download
  command has been received.

  The download handler has to prepare the software download. For a class 3
  device restarting will be  one step of the preparation; a class 1 device
  is not allowed to restart during the preparation phase.

PARAMETERS
  dom_id    FD_SW_DOM_ID

RETURN_VALUES
  E_OK                  The preparation command is accepted
  E_SWDL_TEMP_DENIED    Software download is not possible at the moment
  E_SWDL_NOT_POSSIBLE   Software download is not possible for this device

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  if (dom_id == FD_SW_DOM_ID)
  {
    _PREPARE_DWNLD_OF_FD_SW;
  }
  else
  {
    _ASSERT(TRUE); /* MULTIDOMAIN Not Supported */
  }


  if (appl_dwnld_prop.resp_for_prepare == SEND_WRITE_RESP_FOR_DWNLD_PREPARE)
  {
    fdc_complete_dwnld_action (dom_id, SWDL_PREPARE_OK, NULL);
  }
  else /* appl_dwnld_prop.resp_for_prepare == NO_WRITE_RESP_FOR_DWNLD_PREPARE */
  {
    Reset_CPU ();     /* A class 1 device is not allowed to restart
                         in the preparation phase!                   */
  }

  return E_OK;
}







FUNCTION GLOBAL const T_DOMAIN_HDR_API * Appl_cancel_download
  (
    IN USIGN8   dom_id
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the download server when the download procedure is
  aborted. The abort can be triggered by the host by sending a cancel command;
  the procedure is also aborted when the underlying connection has been closed.

PARAMETERS
  dom_id          FD_SW_DOM_ID

RETURN_VALUES
  If the old software is still executable the download handler shall return
  the domain header of the executable software - otherwise it shall return NULL

----------------------------------------------------------------------------*/
{
    const T_DOMAIN_HDR_API *ret = NULL;
    if (dom_id == FD_SW_DOM_ID)
    {
        _RESET_FD_DOMAIN;

        /* If the old field device software is still executable return its
           domain header - otherwise return NULL                                */

        ret = &appl_fd_dom_hdr;
    }
    else
    {
        _ASSERT(TRUE); /* MULTIDOMAIN Not Supported */

    }
    return ret;
}




FUNCTION GLOBAL USIGN8 Appl_download_header
  (
    IN USIGN8               dom_id,
    IN T_DOMAIN_HDR_API *   p_dwnld_dom_hdr
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the download server when the header of the
  downloaded software has been received.

  The download server cuts the software download domain header from the rest
  of the domain. The first segment provided to the download handler will not
  contain the domain header.

PARAMETERS
  dom_id            FD_SW_DOM_ID

  p_dwnld_dom_hdr   Pointer to the header of the domain to be downloaded

RETURN_VALUES
  E_OK            A domain with this header will be accepted
  E_SWDL_OTHER    A domain with this header will not be accepted

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8 result;

FUNCTION_BODY


  if (dom_id == FD_SW_DOM_ID)
  {
    result = _CHECK_FD_DOMAIN_HDR (p_dwnld_dom_hdr);

    if (result == E_OK)
    {
      result = _STORE_FD_DOMAIN_HDR (p_dwnld_dom_hdr);
    }
  }
  else
  {
    _ASSERT(TRUE); /* MULTIDOMAIN Not Supported */

    result = E_SWDL_OTHER;
  }

  return result;
}




FUNCTION GLOBAL USIGN8 Appl_download_segment
  (
    IN USIGN8           dom_id,
    IN USIGN8           segment_id,
    IN USIGN8           segment_len,
    IN USIGN8 *         p_segment
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the download server when a segment of downloaded
  domain  has been received.

PARAMETERS
  dom_id          FD_SW_DOM_ID

  segment_id      SWDL_LOAD_FIRST_SEGM  The first segment of the domain has
                                        been received. The first segment does
                                        not contain the domain header. The
                                        domain header is indicated by an extra
                                        interface function.

                  SWDL_LOAD_SEGM        The received segment is neither the
                                        first nor the last segment of the
                                        domain.

                  SWDL_LOAD_LAST_SEGM   The last segment has been received.
                                        The download handler has to check
                                        the downloaded domain for consistency.

  segment_len     Length of the segment

  p_segment       Pointer to the segment

RETURN_VALUES
  E_OK                  The segment has been received correctly
  E_SWDL_CHECKSUM_FAIL  The checksum (of the complete domain) is not correct
  E_SWDL_OTHER          The segment or the whole domain is not correct

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8 result;

FUNCTION_BODY

  result = E_OK;

  if (dom_id == FD_SW_DOM_ID)
  {
    result = _CHECK_FD_DOMAIN_SEGM (segment_id,segment_len,p_segment);

    if (result == E_OK)
    {
      result = _STORE_FD_DOMAIN_SEGM (segment_id,segment_len,p_segment);
    }
  }
  else
  {
    _ASSERT(TRUE); /* MULTIDOMAIN Not Supported */

    result = E_SWDL_OTHER;
  }

  return result;
}




FUNCTION GLOBAL VOID Appl_activate_software
  (
    IN USIGN8           dom_id
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
  This function is called by the download server when the host has issued an
  activation command.

PARAMETERS
  dom_id          FD_SW_DOM_ID

RETURN_VALUES
  There is no 'positive' return value: each successful activation will result
  in a device restart.

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
    BOOL  activation_ok;

//We are not using hm mutex here because the common function uses it inside.
FUNCTION_BODY

    if (dom_id == FD_SW_DOM_ID)
    {
        activation_ok = _ACTIVATE_FD_FW;
    }
    else
    {
        //assert is a wrong reaction to external intput! _ASSERT(TRUE); /* MULTIDOMAIN Not Supported */

        activation_ok = FALSE;
    }

    if (activation_ok != FALSE)
    {
        Reset_CPU ();
    }

    return; /* A return indicates a failed activation ! */
}


