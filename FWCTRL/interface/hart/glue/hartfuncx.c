/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hartfuncx.c
    \brief new commands for HART revision 6

    CPU: Any

    OWNER: Eric Jiang, Jojo Liu
    $Archive: /MNCB/Dev/AP_Release_3.1.x/FIRMWARE/interface/hart/hartfuncx.c $
    $Date: 7/19/11 1:30p $
    $Revision: 7 $
    $Author: Arkkhasin $

    \ingroup hart
*/

#include "mnwrap.h"
#include "hartdef.h"
#include "bufutils.h"
#include "hart.h"
#include "mncbdefs.h"
//#include "bios.h"
#include "mnassert.h"
#include "errcodes.h"
#include "hartfunc.h"
#include "hartfuncx.h"
#include "nvram.h"
#include "uipublic.h"
#include "uistartnodes.h"
//#include "devicevariables.h"
#include "configure.h"
#include "devicemode.h"
//#include "conversion.h"
#include "ifman.h"
#include "hartdefX.h"

// make sense for LCX with out jumper
// #define WRITEPROTECT_NONE 251


/**
    \brief universal command 0 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadUniqueIdentifier(const void *src, void *dst, HartCmdParams_t *params)
{
    Rsp_ReadUniqueIdentifier_t *d = (void *)dst;
    const HartData_t * tmpptr;
    ConfigurationChanged_t conch;
    stUniqueIdentifier_t *temp = (void *)(d->stUniqueIdentifier);

    util_PutU8(temp->DummyDelimiter[0], (u8)254);
    util_PutU8(temp->MfgID[0], (u8)MNCB_MANUFACTURER_ID);
    util_PutU8(temp->DeviceType[0], VerString[hart_GetHartData()->hart_version].ManufacturerDeviceCode);
    util_PutU8(temp->Preambles[0], (u8)NBR_REQUEST_PREAM);
    util_PutU8(temp->CmdRev[0], (u8)UNIV_CMD_REV6);
    util_PutU8(temp->DevRev[0], (u8)TRANS_SPEC_REV6);
    util_PutU8(temp->SWRev[0], (u8)SOFT_REV6);
    util_PutU8(temp->HWRevandSignalingcode[0], (u8)MNCB_HARDWARE_REVISION);
    util_PutU8(temp->Flags[0], (u8)FLAG_REV6);

    tmpptr = hart_GetHartData();
    util_PutU8Array(temp->DeviceID[0], sizeof(tmpptr->device_id)/sizeof(u8), tmpptr->device_id);

    util_PutU8(temp->nPreambles[0], (u8)NBR_RESPONSE_PREAM);   //default value should be 5, check ANNEX B. Default configuration table
    //util_PutU8(temp->nVariables[0], hart_GetNumberOfDeviceVars());
    util_PutU8(temp->nVariables[0], 42);
    //Return argument ignored because data returned in input parameter conch.
    (void)nvram_GetConfigurationChanged(&conch);
    util_PutU16(temp->Count[0], (u16)conch.ConfigurationChangeCounter);
    //util_PutU8(temp->ExtStatus[0], hart_ExtendedDeviceStatus());
    util_PutU8(temp->ExtStatus[0], 17);

    UNUSED_OK(src);
    UNUSED_OK(params);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ReadUniqueIdentifier() ------

#if 0 //This file is just a prototype for integration of HART revisions
/**
    \brief universal command 6 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_WritePollingAddress(const void *src, void *dst, HartCmdParams_t *params)
{
    const Req_WritePollingAddress_t *s = src;
    Req_WritePollingAddress_t *d = dst;

    const HartData_t * tmpptr;
    HartData_t tmp;
    ErrorCode_t errcode;
    u8 pollingaddress;
    u8 LoopCurrentMode;

    pollingaddress = util_GetU8(s->PollingAddress[0]);

    //Return argument ignored because data returned in input parameter.
    (void)hart_GetAndTestHartData(&tmp);
    tmp.transmit_address = pollingaddress;
    if(params->req_data_len >= MN_OFFSETOF(Req_WritePollingAddress_t, endmark))
    {
        //Assume HART 6 host sent loop current mode
        LoopCurrentMode = util_GetU8(s->LoopCurrentMode[0]);
        if (  ((u8)LoopModeEnabled != LoopCurrentMode)
            &&((u8)LoopModeDisabled != LoopCurrentMode) )
         {
              return err2hart(ERR_MODE_CANNOT_CHANGE);
         }
    }
    else
    {
        //Assume HART 5 host; let the set function figure out what to do
        if (0 == pollingaddress)
        {
            LoopCurrentMode = (u8)LoopModeEnabled;
        }
        else
        {
            LoopCurrentMode = (u8)LoopModeDisabled;
        }
    }

    errcode = hart_SetHartData(&tmp);
    tmpptr = hart_GetHartData();
    if (ERR_OK == errcode)
    {
        errcode = hart_SetDevModeByLoopCurMode(LoopCurrentMode);
    }

    if (ERR_OK == errcode)
    {
        util_PutU8(d->PollingAddress[0], tmpptr->transmit_address); //optional - could not change the preset
        util_PutU8(d->LoopCurrentMode[0], LoopCurrentMode);
    }

    UNUSED_OK(params);
    return err2hart(errcode);
}

/**
*   \brief universal command 7 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadLoopConfiguration(const void *src, void *dst, HartCmdParams_t *params)
{
    const HartData_t *tmpptr;
    Rsp_ReadLoopConfiguration_t* d = (Rsp_ReadLoopConfiguration_t*)dst;
    u8 loopCurrentMode;

    tmpptr = hart_GetHartData();
    loopCurrentMode = hart_GetLoopCurModeByDevMode();

    util_PutU8(d->PollingAddress[0] , tmpptr->transmit_address);
    util_PutU8(d->LoopCurrentMode[0], loopCurrentMode);

    UNUSED_OK(src);
    UNUSED_OK(params);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ReadLoopConfiguration() ------


/**
*   \brief universal command 8 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadVariableClassifications(const void *src, void *dst, HartCmdParams_t *params)
{
    Rsp_ReadVariableClassifications_t *d=(void *)dst;

    util_PutU8(d->ClassificationsforPSQT[0], (u8)VarClass_ValveActuator); //Position
    util_PutU8(d->ClassificationsforPSQT[1], (u8)VarClass_Pressure);
    util_PutU8(d->ClassificationsforPSQT[2], (u8)VarClass_Pressure);
    util_PutU8(d->ClassificationsforPSQT[3], (u8)VarClass_Pressure);

    UNUSED_OK(src);
    UNUSED_OK(params);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}//-----  end of hartcmd_ReadDynamicVariable() ------


/**
*   \brief universal command 9 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadDeviceVariableswithStatus(const void *src, void *dst, HartCmdParams_t *params)
{
    u8_least items, datalen, i;
    s8_least ret = HART_TOO_FEW_DATA_BYTES_RECEIVED;
    VariableSlotsConfig_t slots;
    const VariableCodeEnum_t* xs;
    stVariableCodeSlotX_t* xd;
    const Req_ReadDeviceVariableswithStatus_t *s = (const void *)src;
    Rsp_ReadDeviceVariableswithStatus_t *d = (void *)dst;

    if (NULL == s)
    {
        (void)hconf_GetVariableSlotsConfig(&slots); // unnecessary but lint
        for (i = 0; i < VAR_SLOTS_CONFIG_SIZE; i += 1)
        {
            if (slots.VariableSlotsConfig[i] == VAR_SLOT_EMPTY)
            {
                break;
            }
        }
        items = i;
    }
    else
    {
        datalen = params->req_data_len;
        datalen = MIN(datalen, MN_OFFSETOF(Req_ReadDeviceVariableswithStatus_t, endmark));
        // how many slots requested
        items = (datalen - MN_OFFSETOF(Req_ReadDeviceVariableswithStatus_t, VariableCodeSlotX)) / sizeof(s->VariableCodeSlotX[0]);
    }

    util_PutU8(d->ExtendedDSCodes[0],  hart_ExtendedDeviceStatus());
    for (i = 0; i < items; i += 1)
    {
        if (NULL == s)
        {
            xs = (const void*)&(slots.VariableSlotsConfig[i]);
        }
        else
        {
            xs = (const void *) s->VariableCodeSlotX[i];
        }
        xd = (void *) d->stVariableCodeSlotX[i];
        ret = hart_FillVariableCode(xs, xd);
        if(HART_NO_COMMAND_SPECIFIC_ERRORS != ret)
        {
            break;
        }
    }
    params->rsp_data_len = (u8)(MN_OFFSETOF(Rsp_ReadDeviceVariableswithStatus_t, stVariableCodeSlotX) + items * sizeof(*xd));
    return ret;
} //-----  end of hartcmd_ReadDeviceVariableswithStatus() ------


/**
*   \brief universal command 11 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadUniqueIdentifierByTag(const void *src, void *dst, HartCmdParams_t *params)
{
//copy and paste codes from HART5, but the line commented below
    u32 i;
    s8_least ret;
    const u8* tag;
    const HartData_t * tmpptr;

    if (params->req_data_len < sizeof(tmpptr->tag))
    {
        Hart_DropFrame();
        return HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    tmpptr = hart_GetHartData();
    tag = (const u8*)src;

    i = 0;
    while ((tag[i] == tmpptr->tag[i]) && (i < sizeof(tmpptr->tag)))
    {
        i++;
    }

    if (i == sizeof(tmpptr->tag))
    {
      // it is command 0 of HART6
       ret = HartCmd_ReadUniqueIdentifier(src, dst, params);
    }
    else
    {
        Hart_DropFrame();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
} //-----  end of hartcmd_ReadUniqueIdentifierByTag() ------

/**
*   \brief universal command 14 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadPVTransducerInformation(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    Rsp_ReadPVTransducerInformation_t* d;

    d = (Rsp_ReadPVTransducerInformation_t*)dst;
    ret = hart_Command_14_ReadTransducerInfo((const u8*)src, (u8*)dst);
    util_PutU8(d->TransducerUnitsCode[0], HART_MAMP_CODE); //mA, hart compliance test case requirement test3.pdf, UAL007

    UNUSED_OK(params);
    return ret;
} //-----  end of HartCmd_ReadPVTransducerInformation() ------

/**
*   \brief universal command 15 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadDeviceInformation(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    Rsp_ReadDeviceInformation_t* d;
    PVRangeValues_t* temp;

    d = (Rsp_ReadDeviceInformation_t*)dst;
    temp = (PVRangeValues_t*)(d->PVRangeValues[0]); // lint, by EJ
    ret = hart_Command_15_ReadTransmitterInfo( (const u8*)src, (u8*)dst );
    util_PutU8(temp->PV_Range_Units[0], HART_MAMP_CODE);
    util_PutFloat(temp->PV_URV[0], 20.0F);
    util_PutFloat(temp->PV_LRV[0], 4.0F);
    util_PutU8(d->PrivateLabel[0], MNCB_MANUFACTURER_ID);
    util_PutU8(d->PVChannelFlag[0], ANALOG_CHANNEL_FLAG);

    UNUSED_OK(params);
    return ret;
} //-----  end of hartcmd_ReadDeviceInformation() ------

/**
    \brief universal command 20 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadLongTag(const void *src, void *dst, HartCmdParams_t *params)
{
    Rsp_ReadLongTag_t *d=(void *)dst;
    LongTag_t  LongTag;

    //load the pointer with what is presently in NVRAM
    //Return argument ignored because data returned in input parameter LongTag.
    (void)hconf_GetLongTag(&LongTag);
    util_PutU8Array(d->LongTag[0], sizeof(d->LongTag), LongTag.longTag);

    UNUSED_OK(params);
    UNUSED_OK(src);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ReadLongTag() ------


/**
*   \brief universal command 21 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadUniqueIdentiferassociatedwithLongTag(const void *src, void *dst, HartCmdParams_t *params)
{
    u32 i;
    s8_least ret;
    LongTag_t  LongTag;
    const u8* tag;

    if (params->req_data_len < sizeof(LongTag.longTag))
    {
        Hart_DropFrame();
        return HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    //load the pointer with what is presently in NVRAM
    (void)hconf_GetLongTag(&LongTag); //Return argument ignored because data returned in LongTag
    tag = (const u8*)src;

    i = 0;
    while ((tag[i] == LongTag.longTag[i]) && (i < sizeof(LongTag.longTag)) )
    {
        i++;
    }

    if (i == sizeof(LongTag.longTag))
    {
      // it is command 0 of HART6
       ret = HartCmd_ReadUniqueIdentifier(src, dst, params);
    }
    else
    {
        Hart_DropFrame();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
} //-----  end of hartcmd_ReadUniqueIdentiferassociatedwithLongTag() ------


/**
    \brief universal command 22 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_WriteLongTag(const void *src, void *dst, HartCmdParams_t *params)
{
    const Req_WriteLongTag_t *s = (const void *)src;
    Rsp_WriteLongTag_t *d = (void *)dst;

    ErrorCode_t err;
    LongTag_t  LongTag;

    //load the pointer with what is presently in NVRAM
    //Return argument ignored because data returned in input parameter LongTag.
    (void)hconf_GetLongTag(&LongTag);

    //get Long Tag value from the wire
    util_GetU8Array(s->LongTag[0], sizeof(LongTag.longTag)/sizeof(u8), LongTag.longTag);
    //write it to the FW structure in RAM and NVRAM
    err = hconf_SetLongTag(&LongTag);

    if (err == ERR_OK)
    {
        //return to HART wire what got to NVRAM
        //Return argument ignored because data returned in input parameter LongTag.
        (void)hconf_GetLongTag(&LongTag);
        util_PutU8Array(d->LongTag[0], sizeof(LongTag.longTag)/sizeof(u8), LongTag.longTag);
    }

    UNUSED_OK(params);
    return err2hart(err);
} //-----  end of hartcmd_WriteLongTag() ------

/**
*   \brief common practice command 33 of HART revision 6
           Note:
           This command is allowed in all modes
           comply with ap hart5 and not comply with hcf hart6 in terms of functionalityn
*/
s8_least HartCmd_ReadDeviceVariables(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    Rsp_ReadDeviceVariableswithStatus_t vars;  //response structure for CMD9
    Rsp_ReadDeviceVariables_t *d = (void *)dst;  //response structure for CMD33
    stVariableCodeSlotXwithoutStatus_t *xd; //data slot without status from CMD33
    const stVariableCodeSlotX_t* xds; //data slot with status from CMD9
    u8_least i, items = 0;

    //call command 9 function first
    ret = HartCmd_ReadDeviceVariableswithStatus(src, &vars, params);
    //Get subset value
    if(HART_NO_COMMAND_SPECIFIC_ERRORS == ret)
    {
        items = (params->rsp_data_len - MN_OFFSETOF(Rsp_ReadDeviceVariableswithStatus_t, stVariableCodeSlotX))/sizeof(stVariableCodeSlotX_t);
        for(i = 0; i < items; i += 1)
        {
            xds = (const void *)vars.stVariableCodeSlotX[i];
            xd = (void *)d->stVariableCodeSlotXwithoutStatus[i];
            util_PutU8Array(xd->VariableCode[0], sizeof(xds->VariableCode)/sizeof(u8), xds->VariableCode[0]);
            util_PutU8Array(xd->UnitsCode[0], sizeof(xds->UnitsCode)/sizeof(u8), xds->UnitsCode[0]);
            util_PutU8Array(xd->VariableValue[0], sizeof(xds->VariableValue)/sizeof(u8), xds->VariableValue[0]);
        }
    }
    params->rsp_data_len = (u8)(MN_OFFSETOF(Rsp_ReadDeviceVariables_t, stVariableCodeSlotXwithoutStatus) + items * sizeof(stVariableCodeSlotXwithoutStatus_t));
    return ret;
}

/**
*   \brief common practice command 35 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_WritePVRange(const void *src, void *dst, HartCmdParams_t *params)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    UNUSED_OK(params);
    // don't be supprised, it's an way of bug fixing, by EJ
    return HART_COMMAND_UNDEFINED;
}

/**
*   \brief common practice command 40 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_FixedCurrentMode(const void *src, void *dst, HartCmdParams_t *params)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    UNUSED_OK(params);
    // don't be supprised, it's an way of bug fixing, by EJ
    return HART_COMMAND_UNDEFINED;
}

/**
*   \brief common practice command 45 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_TrimCurrentZero(const void *src, void *dst, HartCmdParams_t *params)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    UNUSED_OK(params);
    // don't be supprised, it's an way of bug fixing, by EJ
    return HART_COMMAND_UNDEFINED;
}

/**
*   \brief common practice command 46 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_TrimcurrentGain(const void *src, void *dst, HartCmdParams_t *params)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    UNUSED_OK(params);
    // don't be supprised, it's an way of bug fixing, by EJ
    return HART_COMMAND_UNDEFINED;
}

/**
*   \brief common practice command 48 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadAdditionalDeviceStatus(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    Rsp_ReadAdditionalDeviceStatus_t* d;

    d = (Rsp_ReadAdditionalDeviceStatus_t*)dst;
    ret = hart_Command_48_ReadAdditionalStatus( (const u8*)src, (u8*)dst );

    util_PutU8(d->ExtendedDSCodes[0],  hart_ExtendedDeviceStatus());

    UNUSED_OK(params);
    return ret;
}

/**
*   \brief common practice command 54 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadDeviceVariableInfo(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    const stRequestCmd54_t* xs;
    stResponseCmd54_t* xd;

    // it will be problem if the number of elements in outer nested stuct more than one, but never happens
    xs = (const stRequestCmd54_t*)src;
    xd = (stResponseCmd54_t*)dst;
    ret = hart_FillVariableInfo(xs, xd);

    UNUSED_OK(params);
    return ret;
}

/**
*   \brief common practice command 71 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_LockDevice(const void *src, void *dst, HartCmdParams_t *params)
{
    ErrorCode_t errcode;
    const Req_LockDevice_t* s = src;
    Rsp_LockDevice_t* d = dst;
    InterfaceAccess_t ia;

    UNUSED_OK(params);
    CONST_ASSERT(sizeof(s->LockCode[0]) == sizeof(ia.iflock));
    (void)TypeUnsafe_ifman_GetLock(&ia); // return value ignored because got by param
    ia.iflock = (iflock_t)*(s->LockCode[0]);
    if(params->master)
    {
        ia.owner = iflock_owner_hart_primary;
    }
    else
    {
        ia.owner = iflock_owner_hart_secondary;
    }
    errcode = ifman_SetLock(&ia);
    if (ERR_OK == errcode)
    {
        (void)TypeUnsafe_ifman_GetLock(&ia); // return value ignored because got by param
        util_PutU8(d->LockCode[0], (u8)ia.iflock);
        return HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    // we need a stronger err2hart() in the future
    else if (ERR_INVALID_PARAMETER == errcode)
    {
        return HART_INVALID_LOCK_CODE;
    }
    else
    {
        return err2hart(errcode);
    }
}

/**
*   \brief common practice command 72 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_Squawk(const void *src, void *dst, HartCmdParams_t *params)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    UNUSED_OK(params);

    ui_setNext(UINODEID_SQUAWKNODE);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
*   \brief common practice command 73 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_FindDevice(const void *src, void *dst, HartCmdParams_t *params)
{
    s8_least ret;
    //physically armed
    if (ui_IsFromStartnode(UINODEID_FINDMENODE))
    {
       ret = HartCmd_ReadUniqueIdentifier(src, dst, params);
       //disarm
       //ui_setNext(UINODEID_INITNODE);
    }
    else
    {
        Hart_DropFrame();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
}

/**
*   \brief common practice command 76 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadLockState(const void *src, void *dst, HartCmdParams_t *params)
{
    InterfaceAccess_t ia;
    u8 lockstate = 0;
    Rsp_ReadLockState_t* d = dst;

//    CONST_ASSERT(sizeof(d->LockState[0]) == sizeof(u8));
    (void)TypeUnsafe_ifman_GetLock(&ia); // return value ignored because got by param

    if (iflock_temp == ia.iflock )
    {
        lockstate = lockstate | (u8)LockStateDeviceLocked;
    }
    if (iflock_perm == ia.iflock )
    {
        lockstate = lockstate | ((u8)LockStateDeviceLocked | (u8)LockStateLockisPermanent);
    }
    if (lockstate != 0)
    {
        if (iflock_owner_hart_primary == ia.owner)
        {
            lockstate = lockstate | (u8)LockStateLockedbyPrimaryMaster;
        }
    }

    util_PutU8(d->LockState[0], lockstate);
    UNUSED_OK(params);
    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
*   \brief common practice command 105 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_ReadburstConfig(const void *src, void *dst, HartCmdParams_t *params)
{
    const HartData_t *tmpptr;
    VariableSlotsConfig_t slots;
    Rsp_ReadburstConfig_t* d = (void*)dst;

    tmpptr = hart_GetHartData();
    util_PutU8(d->BurstControlCode[0], tmpptr->burst_mode_ctrl);
    util_PutU8(d->BurstCommand[0], tmpptr->burst_mode_cmd);

    (void)hconf_GetVariableSlotsConfig(&slots); // unnecessary but lin
    util_PutU8Array((u8*)d->VariableCodeSlotX, 4, (u8*)slots.VariableSlotsConfig);

    UNUSED_OK(src);
    UNUSED_OK(params);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
/**
*   \brief common practice command 107 of HART revision 6
           Note:
           This command is allowed in all modes
*/
s8_least HartCmd_Writeburstdevicevariables(const void *src, void *dst, HartCmdParams_t *params)
{
    ErrorCode_t errcode = ERR_OK;
    u8 items, datalen, i;
    VariableSlotsConfig_t slots;
    const Req_Writeburstdevicevariables_t *s = (const void *)src;
    Rsp_Writeburstdevicevariables_t *d = (void *)dst;

    (void)hconf_GetVariableSlotsConfig(&slots); // unnecessary but lint
    datalen = params->req_data_len;
    datalen = MIN(datalen, MN_OFFSETOF(Req_Writeburstdevicevariables_t, endmark));

    // how many slots requested
    items = (datalen - MN_OFFSETOF(Req_Writeburstdevicevariables_t, VariableCodeSlotX)) / sizeof(s->VariableCodeSlotX[0]);
    for (i = 0; i < items; i += 1)
    {
        if ( *(s->VariableCodeSlotX[i]) > (u8)DevVarMAXVARNUMBER )
        {
            errcode = ERR_INVALID_PARAMETER;
            break;
        }
        else
        {
            *(d->VariableCodeSlotX[i]) = *(s->VariableCodeSlotX[i]);
            slots.VariableSlotsConfig[i] = (u8)*(s->VariableCodeSlotX[i]);
        }
    }

    if (ERR_OK == errcode)
    {
        for (i = items; i < VAR_SLOTS_CONFIG_SIZE; i += 1)
        {
            slots.VariableSlotsConfig[i] = VAR_SLOT_EMPTY;
        }
        params->rsp_data_len = datalen;
        errcode = hconf_SetVariableSlotsConfig(&slots);
    }
    return err2hart(errcode);
}

/**
*   \brief common practice command 108 of HART revision 5!!!
           Note:
           This command is allowed in all modes
*/
s8_least hartcmd_WriteBurstCmd(const u8 *src, u8 *dst)
{
    ErrorCode_t errcode;
    const Req_WriteBurstCmd_t* s = (const void*)src;
    Rsp_WriteBurstCmd_t* d = (void*)dst;

    HartData_t tmp;
    const HartData_t *tmpptr;
    u8 burstcmd;

    burstcmd = util_GetU8(s->BurstCmd[0]);
    (void)hart_GetAndTestHartData(&tmp);//return argument ignored because data returned in tmp
    storeMemberU8(&tmp, burst_mode_cmd, burstcmd);
    errcode = hart_SetHartData(&tmp);

    if(ERR_OK == errcode)
    {
        tmpptr = hart_GetHartData();
        util_PutU8(d->BurstCmd[0], tmpptr->burst_mode_cmd);
    }
    return err2hart(errcode);
}
#endif
/* This line marks the end of the source */


