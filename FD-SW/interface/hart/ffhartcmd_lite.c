/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup mnhartcmd HART Command Module
\brief Dispatcher of HART commands
*/
/**
    \file ffhartcmd_lite.c
    \brief A light version of HART 5 slave command dispatcher,
    a glue between data link layer and app layer.
    Based on HART 5 mnhartcmd.
    Needed for commands intercepted in FFP

    CPU: Any

    OWNER: AK

    \ingroup mnhartcmd
*/

#include <keywords.h>
#include <base.h>
#include <fbap.h>
#include <ffbl_res.h>
#include <hw_if.h>


#include "mnwrap.h"
#include "errcodes.h"
#include "hartnumtypes.h"
#include "hartfunc.h"
//#include "ifman.h"
//#include "hartdef.h"

#include "wprotect.h" //for write protect input

//#include "nvram.h" //for configuration changed flag

//#include "devicemode.h"
#include "faultpublic.h"
//#include "uipublic.h"
//#include "uistartnodes.h"
//#include "process.h"
#include "bufutils.h"

#include "mnhart2ff.h"
#include <softing_base.h>
#include <fbif_dcl.h>

bool_t sysio_ReadWriteProtectInput(void)
{
    return ((hw_write_protection() != 0) || (p_resource->write_lock == WRITE_LOCKED)); //lint !e506 in case hw_write_protection macro-ized out
}

static s8_least hart_CheckFlags(u8 ModeFlag)
{
    u8 HartError = HART_NO_COMMAND_SPECIFIC_ERRORS;

    //if factory command, only allow if enabled
    if( ((ModeFlag&HC_FACTORY_COMMAND) != 0)
        && !mn_IsAppFault(&ptb_1, FAULT_FACTORYMODE))
    {
        ///not allowed in this mode
        HartError = COMMAND_NOT_IMPLEMENTED;
    }

    return HartError;
}

static
s8_least hart_CmdExec(const hartDispatch_t *disp, const u8 *src, u8 *dst, u8 req_data_len)
{
    s8_least ret;
    if (disp == NULL)                         	  /* command not implementd ? */
    {
        ret = -COMMAND_NOT_IMPLEMENTED;
    }
    else if(req_data_len < disp->req_len)
    {
        /* There are not enough databytes received*/
        ret = -HART_TOO_FEW_DATA_BYTES_RECEIVED;
    }
    else if ( ((disp->flags & HC_WRITE_PROTECT) != 0) && sysio_ReadWriteProtectInput()) //lint !e960 Violates MISRA 2004 Required Rule 12.4 AK:TEMPORARY UNTIL LINT 9
    {
        /* write protect violation attempt */
        ret = -HART_WRITE_PROTECT_MODE;
    }
#if 0 //maybe, future
    else if ( ((disp->flags & HC_MODIFY) != 0)
#ifdef HART_REV_5 //Then it it is the oldest
             && (hart_GetHartData()->hart_version != HART_REV_OLDEST) //we are in fallback to old implementation
#endif
             && !ifman_IsAccessEnabled(hart_MsgFromSecondaryMaster(src)?iflock_owner_hart_primary:iflock_owner_hart_secondary)
            )
    {
        /* lock protect violation attempt */
        ret = -HART_ACCESS_RESTRICTED;
    }
#endif
#if 0 //maybe, future
    else if( (disp->flags & ((HC_WRITE_COMMAND | HC_PROCESS_COMMAND) & ~process_GetProcessFlags()))!= 0 )
    {
        ret = -HART_BUSY;
    }
#endif
    else
    {
        ret = -hart_CheckFlags(disp->flags);
        if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
        {
#if 0 //maybe, future
            //Inform UI we are changing things (as needed)
            if ( (disp->flags & HC_WRITE_PROTECT) != 0)
            {
                if(mode_GetMode() == MODE_SETUP)
                {
                    ui_setNext(HART_OVERRIDE_INFO_NODE);
                }
            }
#endif

            /* Copy request data to the response buffer unconditionally so that if
            a specific command's processor feels like that, it can modify/replace
            the default response as it sees fit.
            If this data is not needed, it will be ignored.
            */
            util_GetU8Array(src, (size_t)(disp->rsp_len), dst);

            //All tests passed: process the command; disp is known to be a non-NULL
            ret = -disp->proc(src, dst); /* perform the command which returns a positive on error */
        }

        //a routine can return the length by setting the return to the negative of it (sign reversed above)
        //      This means HART_NO_COMMAND_SPECIFIC_ERRORS but different length
        if(ret >= HART_NO_COMMAND_SPECIFIC_ERRORS)
        {
            if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
            {
                ret = disp->rsp_len;
            }
            else
            {
                //this was a length - command() wants us to return a positive number
            }
        }
    }
    return ret;
}

/**
\brief Central dispatcher of HART requests

Checks the app-level correctness of the data in the request
and dispatches processing to the appropriate app-level function

\param cmd - HART command to process
\param src - request data source as a byte array
\param dst - response data destination as a byte array
\param req_data_len - length (in bytes) of the src array
\return if negative, -error, otherwise, the length of the response in dst
*/
s8_least hart5_Dispatch(u8_least cmd, const u8 *src, u8 *dst, u8 req_data_len)
{
    const hartDispatch_t *disp;
    const hartDispatch_t *subdisp;

    //See if the Command has a subcommand
    const SubCommandInfo_t *sub = hart_GetSubCommandInfo(cmd);
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    if(sub == NULL)
    {
        //No subcommand: the easy old way; + not supporting cmd 11 etc. drop frame
        disp = HART_cmdlookup(cmd); /* look up the dispatch table entry */
        ret = hart_CmdExec(disp, src, dst, req_data_len);
    }
    else
    {
        //subcommand exists; check its data lengths
        if(req_data_len < sub->data_offset)
        {
            //Not enough bytes even for the top-level command
            ret = -HART_TOO_FEW_DATA_BYTES_RECEIVED;
        }
        else if(req_data_len < sub->type_offset)
        {
            //If we ever get here, the const dispatcher table is misconfigured.
            //AK:FUTURE: probably can assert here
            ret = -HART_TOO_FEW_DATA_BYTES_RECEIVED;
        }
        else
        {
            subdisp = sub->lookup_func(src[sub->type_offset]);
            if(subdisp == NULL)
            {
                ret = -COMMAND_NOT_IMPLEMENTED; //HART_INVALID_SELECTION;
                /* NOTE: This is not HART-compliant but we don't care for our purpose:
                If we don't find a subcommand, we want to pass through to APP,
                which happens on COMMAND_NOT_IMPLEMENTED
                */
            }
            else
            {
                //Preliminary conditions are met; execute the main command first
                disp = HART_cmdlookup(cmd); /* look up the dispatch table entry */
                ret = hart_CmdExec(disp, src, dst, sub->data_offset);
                s8_least len = ret;
                if(ret >= HART_NO_COMMAND_SPECIFIC_ERRORS)
                {
                    //Now we are in a position to execute the subcommand
                    ret = hart_CmdExec(subdisp, src + sub->data_offset, dst + len, req_data_len - sub->data_offset);
                    if(ret >= HART_NO_COMMAND_SPECIFIC_ERRORS)
                    {
                        ret += len; //combined length of responses to command and subcommand
                    }

                }
            }
        }
    }
    //a routine can return the length by setting the return to the negative of it (sign reversed noted)
    //      This means HART_NO_COMMAND_SPECIFIC_ERRORS but different length
    if(ret >= HART_NO_COMMAND_SPECIFIC_ERRORS)
    {
        ret = HART_NUM_STATUS_BYTES + ret;
    }
    return ret;
}

/* This line marks the end of the source */
