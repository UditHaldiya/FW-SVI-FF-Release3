/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
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
    \file mnhartcmd.c
    \brief HART command dispatcher, a glue between data link layer and app layer

    [Originally based on MESCO's COMMAND.C]

    CPU: Any

    OWNER: AK

    \ingroup mnhartcmd
*/

#include "mnwrap.h"
#include "errcodes.h"
#include "hart.h"
#include "hartfunc.h"
#include "ifman.h"
#include "hartdef.h"

#include "wprotect.h" //for write protect input

#include "nvram.h" //for configuration changed flag

#include "devicemode.h"
#include "faultpublic.h"
#include "uipublic.h"
#include "uistartnodes.h"
#include "process.h"
#include "bufutils.h"
#include "fpconvert.h"


static
s8_least hart_CmdExec(const hartDispatch_t *disp, const u8 *src, u8 *dst, const HartCmdParams_t *params)
{
    s8_least ret = -HART_NO_COMMAND_SPECIFIC_ERRORS;
    u8 req_data_len = params->req_data_len;
    if (disp == NULL)                         	  /* command not implementd ? */
    {
        ret = -COMMAND_NOT_IMPLEMENTED;
    }
    else if(req_data_len < disp->req_len)
    {
        /* There are not enough databytes received*/
        ret = -HART_TOO_FEW_DATA_BYTES_RECEIVED;
    }
    else if ( ((disp->flags & HC_WRITE_PROTECT) != 0) && bios_ReadWriteProtectInput()) //lint !e960 Violates MISRA 2004 Required Rule 12.4 AK:TEMPORARY UNTIL LINT 9
    {
        /* write protect violation attempt */
        ret = -HART_WRITE_PROTECT_MODE;
    }
    else if ( ((disp->flags & HC_MODIFY) != 0)
#ifdef HART_REV_5 //Then it it is the oldest
             && (hart_GetHartData()->hart_version != HART_REV_OLDEST) //we are in fallback to old implementation
#endif
         && !ifman_IsAccessEnabled((params->master==HartMaster_Primary)?iflock_owner_hart_primary:iflock_owner_hart_secondary)
        )
    {
        /* lock protect violation attempt */
        ret = -HART_ACCESS_RESTRICTED;
    }
    else if( (disp->flags & ((HC_WRITE_COMMAND | HC_COMMAND_COMMAND) & ~process_GetProcessFlags()))!= 0 )
    {
        ret = -HART_BUSY;
    }
    else
    {
        ret = -hart_CheckMode(disp->flags);
        if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
        {
            //Test engineering units before possible use
            fpconvert_TestData();

            //Inform UI we are changing things (as needed)
            if ( (disp->flags & HC_WRITE_PROTECT) != 0)
            {
#ifdef OLD_DEVMODE
                const ModeData_t *md = mode_GetMode();
                if((md->mode==MODE_OOS) && (md->submode == SUBMODE_OOS_NORMAL))
#else
                if(mode_GetMode() == MODE_SETUP)
#endif
                {
                    ui_setNext(HART_OVERRIDE_INFO_NODE);
                }
            }

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

#ifndef HART_COMMAND_11_ReadUniqueIdentifierByTag //command 11 went xml
#define HART_COMMAND_11_ReadUniqueIdentifierByTag 11u
#endif
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
    HartCmdParams_t params;

    params.rsp_warning = HART_NO_COMMAND_SPECIFIC_ERRORS;
    params.master = hart_MsgFromSecondaryMaster(src);

    //See if the Command has a subcommand
    const SubCommandInfo_t *sub = hart_GetSubCommandInfo(cmd);
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    if(sub == NULL)
    {
        //No subcommand: the easy old way
        disp = HART_cmdlookup(cmd); /* look up the dispatch table entry */
        params.req_data_len = req_data_len;
        params.rsp_data_len = disp->rsp_len; //default length of response
        ret = hart_CmdExec(disp, src, dst, &params);

        /** The exception in HART is that if command 11 is too short, there shall be no response.
        A good architecture would be to drop the frame in the command 11 handler, but it requires
        support of optional parameters in the HART framework.
        Until it is implemented, the wart is reinstated here.
        */
        if((ret == -HART_TOO_FEW_DATA_BYTES_RECEIVED) && (cmd == HART_COMMAND_11_ReadUniqueIdentifierByTag))
        {
            Hart_DropFrame();
        }
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
                ret = -HART_INVALID_SELECTION;
            }
            else
            {
                //Preliminary conditions are met; execute the main command first
                disp = HART_cmdlookup(cmd); /* look up the dispatch table entry */
                params.req_data_len = sub->data_offset;
                params.rsp_data_len = disp->rsp_len; //default length of response
                ret = hart_CmdExec(disp, src, dst, &params);
                s8_least len = ret;
                if(ret >= HART_NO_COMMAND_SPECIFIC_ERRORS)
                {
                    //Now we are in a position to execute the subcommand
                    params.req_data_len = req_data_len - sub->data_offset;
                    params.rsp_data_len = subdisp->rsp_len; //default length of response
                    params.rsp_warning = HART_NO_COMMAND_SPECIFIC_ERRORS;
                    ret = hart_CmdExec(subdisp, &src[sub->data_offset], &dst[len], &params);
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
        u8_least warn = params.rsp_warning;
        warn <<=HART_WARNING_SCALER;
        ret = HART_NUM_STATUS_BYTES + ret + (s8_least)warn;
    }
    return ret;
}

#if HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED
/**
\brief Central dispatcher of HART burst responses

Dispatches processing to the appropriate app-level function

\param cmd - HART command to process
\param dst - response data destination as a byte array
\return the length of the response in dst or if <0 an error code
*/
s8_least hart5_BurstDispatch(u8_least cmd, u8 *dst)
{
    s8_least ret  = 0;
    const hartDispatch_t *disp;

    disp = HART_cmdlookup(cmd); /* look up the dispatch table entry */
    if(disp != NULL)
    {
        if(disp->proc == NULL)
        {
            //The command is listed but not implemented. Mark it as such:
            disp = NULL;
        }
    }

    if (disp == NULL)                         	  /* command not implementd ? */
    {
        ret = -COMMAND_NOT_IMPLEMENTED;
    }
    else
    {
        //Test engineering units before possible use
        fpconvert_TestData();

        /* perform the command; it must be happy to take a NULL request and infer length
        from its burst configuration
        */
        ret = disp->proc(NULL, dst);

        if(ret > HART_NO_COMMAND_SPECIFIC_ERRORS)
        {
            //propagate the error up as a negative
            ret = -ret;
        }
        else
        {
            if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
            {
                ret = (s8_least)disp->rsp_len;
            }
            else
            {
                ret = -ret; //positive length
            }
            ret += HART_NUM_STATUS_BYTES; //length
        }
    }
    return ret;
}
#endif //HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED

/* This line marks the end of the source */
