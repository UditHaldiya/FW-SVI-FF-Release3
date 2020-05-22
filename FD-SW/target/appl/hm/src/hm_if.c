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

FILE_NAME          hm_if.c



FUNCTIONAL_MODULE_DESCRIPTION

=========================================================================== */
  #include "keywords.h"
  #define  MODULE_ID      (COMP_HM + MOD_HM_IF)




INCLUDES

  #include "base.h"
  #include "osif.h"
  #include "except.h"

  #include "hw_cfg.h"
  #include "hm_api.h"
  #include "hm_if.h"
  #include "hm_cfg.h"
  #include "hm.h"
  #include "mnhart2ff.h"
  #include "hartfunc.h"

//lint -estring(457,hm_get_acyc_result)
MN_INLINE u8 hm_get_acyc_result(void)
{
    return HM_acyc_result;
}

/****************************************************************************/
/*lint -esym(457, hm_mutex)
because it is embOS API
*/
static OS_RSEMA hm_mutex;
//lint -sem(hm_AcquireMutex, thread_lock)
//lint -sem(hm_ReleaseMutex, thread_unlock)
/**
  \brief  This function acquires the Masoneilan FRAM guardian mutex.
*/
static void hm_AcquireMutex(void)
{
    if((u8_least)OS_Request(&hm_mutex) == 0) //return value 1: Resource was available, now in use by calling task; 0: Resource was not available.
    {
        //Mutex not available
        (void)OS_Use(&hm_mutex); //wait; returned value larger than 1 means the resource was already locked by the calling task
    }
} //lint !e456 embOS mutex model uses counting resource semaphore; implementation is per manual

static void hm_ReleaseMutex(void)
{
    OS_Unuse(&hm_mutex);
}

/** \brief The function sends an acyclic command to the HART communication. Note,
  that the function blocks until the command is executed by the HART
  slave.
\param cmd - command number
\param send_buff - a pointer to a xmit buffer
\param send_length - xmit length of data payload
\param receive_buff - a pointer to a receive buffer
\return FF error code
*/
fferr_t mn_HART_acyc_cmd(u8 cmd, u8 *send_buff, u8 send_length, u8 *receive_buff)
{
    fferr_t fferr;

#if 0 //seems to matter A LOT in the initialization phase
    if(mn_HART_ResponseTimeOut())
    {
        //APP is out to lunch
        fferr = E_FB_TEMP_ERROR;
    }
    else
#endif
    {
        //Worth sending a command
        hm_AcquireMutex();

        {
            //A countermeasure (not a solution) for bug 11609
            receive_buff[0] = HART_TYPE_MISMATCH; //forbidden response which must be overwritten on success

            OS_TASK **pMe = hm_set_cmd_in_acyc_list(cmd, send_buff, send_length, receive_buff);
            osif_set_event(HM_TASK_ID, OS_IF_EVENT_REQRES);

            /* Wait until request is completed and discard the event*/
            /*---------------------------------*/
            (void)osif_wait_event(osif_get_current_task_id (), HART_ACY_CMD_END_EVENT);
            *pMe = NULL; //clear my traces

            u16 result = (USIGN16) hm_get_acyc_result();

            if(result == 0)
            {
                u8 rsp = receive_buff[0];
                fferr = err_Hart2FF(rsp);
            }
            else
            {
                fferr = E_FB_TEMP_ERROR; //Comm error; TODO
            }
        }
        hm_ReleaseMutex();
    }
    return fferr;
}

/** \brief Intializes the HART interface. The function is called by
  the main function in osif_mn.c.

Note that we only do housekeeping here:
- create a mutex,
- init data structures

"Physical" variables availability is indicated
by their STATUS, as it has always been.
*/
void hm_init(void)
{
    OS_CREATERSEMA(&hm_mutex);
    hmtask_SysStart();
} /* FUNCTION hm_init */




