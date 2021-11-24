/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_corefac.c
    \brief Core factory functions common to all projects

    Originally based on extracts from hartfunc_fac.c,79

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/

#include "mnwrap.h"

#include "errcodes.h"
#include "bufutils.h"
#include "oswrap.h"

#include "nvram.h"
#include "fram.h"
#include "devicemode.h"
#include "faultpublic.h"
#include "hartfunc.h"
#include "hart.h"
#include "smoothing.h"
#include "bsp.h" //for mychecksum
#include "watchdog.h"
#include "hartdef.h"

#ifndef OLD_NVRAM
#include "resource.h"
#endif

#include MEMMAP_H_
#include "mncbdefs.h"


#include "param.h"

#if !((NVMEMEND-NVMEMSTART) >=0x1000U)
//For NVMEM parts > 8K do not use volume encoding
#define VOLID_MASK 0x0003U //! A hack mask to extract the NVMEM module from FRAM addr in raw R/W operations
#define VOLID_BITPOS 14 //Where the module is placed
#endif

s8_least hartcmd_ReadFactoryValues(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_ReadRAMarea(const u8 *src, u8 *dst)
{
    s8_least ret;
    const Req_ReadRAMarea_t *s = (const void *)src;
    Rsp_ReadRAMarea_t *d = (void *)dst;
    u32 Address = util_GetU32(s->RamAddress[0]);
    const u8* RamAddress = HARDWARE(const u8 *,RAMSTART) + Address;
    if(Address > (((RAMEND-RAMSTART)+1) - sizeof(d->ReadBlock) ))
    {
       ret = HART_INVALID_DATA;
    }
    else
    {
        util_PutU8Array(d->ReadBlock[0], sizeof(d->ReadBlock), RamAddress);
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    return ret;
}

s8_least hartcmd_ReadNVMEMarea(const u8 *src, u8 *dst)
{
    s8_least ret;
    const Req_ReadNVMEMarea_t *s = (const void *)src;
    Rsp_ReadNVMEMarea_t *d = (void *)dst;
    u16_least Address = util_GetU16(s->MemoryAddress[0]);

    u8_least volid;
#if !((NVMEMEND-NVMEMSTART) >=0x1000U)
    volid = (Address & (VOLID_MASK << VOLID_BITPOS)) >> VOLID_BITPOS;
    Address &= ~(VOLID_MASK << VOLID_BITPOS);
#else
    //NVMEM part > 8K
    volid = 0;
#endif

    MN_FRAM_ACQUIRE();
        if(fram_ReadExt(d->ReadBlock[0], Address, sizeof(d->ReadBlock), volid) == ERR_OK)
        {
            ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
        }
        else
        {
            ret = HART_INVALID_DATA; //ignore disconnected board and read errors for now
        }
    MN_FRAM_RELEASE();
    return ret;
}

s8_least hartcmd_ReadFirmwareVersion(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadFirmwareVersion_t *d = (void *)dst;
    util_PutU16(d->FirmwareCRC[0], mychecksum);
    CONST_ASSERT(sizeof(d->BuildDate)==sizeof(VerString[0].date_str));
    util_PutU8Array(d->BuildDate[0], sizeof(d->BuildDate), (const u8 *)VerString[0].date_str);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}


s8_least hartcmd_WriteFactoryValues(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

//keys to unlock factory commands
#define FACTORY_KEY1 0xfeedf0a1U
#define FACTORY_KEY2 0xdeadbeefU

s8_least hartcmd_EnableFactoryMode(const u8 *src, u8 *dst)
{
    s8_least ret;
    UNUSED_OK(dst);
    const Req_EnableFactoryMode_t *s = (const void *)src;
    if((util_GetU32(s->FactoryKey1[0])==FACTORY_KEY1) && (util_GetU32(s->FactoryKey2[0])==FACTORY_KEY2))
    {
        //Enable factory mode
        error_SetFault(FAULT_FACTORYMODE);
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else if(error_IsFault(FAULT_FACTORYMODE))
    {
        //If factory mode was in effect, cancel it
        error_ClearFault(FAULT_FACTORYMODE);
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else
    {
        ret = COMMAND_NOT_IMPLEMENTED;
    }
    return ret;
}

s8_least hartcmd_WriteRAMarea(const u8 *src, u8 *dst)
{
    s8_least ret;
    const Req_WriteRAMarea_t *s = (const void *)src;
    UNUSED_OK(dst);
    u32 Address = util_GetU16(s->RamAddress[0]);
    u8* RamAddress = HARDWARE(u8 *,RAMSTART) + Address;
    u8_least len = util_GetU8(s->ByteCount[0]);
    if(len > sizeof(s->WriteBlock))
    {
       ret = HART_INVALID_DATA;
    }
    else if(Address > (((RAMEND-RAMSTART)+1) - len ))
    {
       ret = HART_INVALID_DATA;
    }
    else
    {
        MN_ENTER_CRITICAL();
            util_PutU8Array(RamAddress, len, s->WriteBlock[0]);
        MN_EXIT_CRITICAL();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    return ret;
}

s8_least hartcmd_WriteNVMEMarea(const u8 *src, u8 *dst)
{
    /*
    We employ the technique to set FAULT_FACTORYWRITE fault to disable
    background FRAM test and FRAM writes. This is because FRAM write will not write
    large structures atomically.
    */
    /* In case FAULT_FACTORYWRITE is set up as not failsafe, for which
    there may be good internal reasons, we enforce failsafe here
    */
    mode_SetMode(MODE_FAILSAFE);
    error_SetFault(FAULT_FACTORYWRITE);

    s8_least ret;
    const Req_WriteNVMEMarea_t *s = (const void *)src;
    UNUSED_OK(dst);
    u16_least Address = util_GetU16(s->MemoryAddress[0]);

    u8_least volid;
#if !((NVMEMEND-NVMEMSTART) >=0x1000U)
    volid = (Address & (VOLID_MASK << VOLID_BITPOS)) >> VOLID_BITPOS;
    Address &= ~(VOLID_MASK << VOLID_BITPOS);
#else
    //NVMEM part > 8K
    volid = 0;
#endif

    u8 len = util_GetU8(s->ByteCount[0]);
    if(len > sizeof(s->WriteBlock))
    {
       ret = HART_INVALID_DATA;
    }
    else
    {
        MN_FRAM_ACQUIRE();
            if(fram_WriteExt(s->WriteBlock[0], Address, len, volid) == ERR_OK)
            {
                ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
            }
            else
            {
                ret = HART_INVALID_DATA; //ignore disconnected board and read errors for now
            }
        MN_FRAM_RELEASE();
    }
    return ret;
}

/**
\brief sets the HART device ID
*/
s8_least hartcmd_WriteDeviceId(const u8 *src, u8 *dst)
{
    s8_least ret;
    HartData_t HartHeader;

    UNUSED_OK(dst);
    const Req_WriteDeviceId_t *s = (const void *)src;
    CONST_ASSERT(sizeof(HartHeader.device_id) == sizeof(s->DeviceID));

    (void)hart_GetAndTestHartData(&HartHeader);

    util_GetU8Array(s->DeviceID[0], sizeof(s->DeviceID), HartHeader.device_id);

    if(hart_SetHartData(&HartHeader) == ERR_OK)
    {
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else
    {
        ret = HART_INVALID_DATA;
    }
    return ret;
}

s8_least hartcmd_TestWatchdog(const u8 *src, u8 *dst)
{
    //this just waits for the watchdog to time out
    // see watchdog.c for description on testing watchdogs
    UNUSED_OK(dst);
    const Req_TestWatchdog_t *s = (const void *)src;
    u8 wdid = util_GetU8(s->WatchdogId[0]);
    for(;;) //Just make it clear that we aren't going to return
    {
        if (wdid != 0)                   // test the internal watchdog
        {
            mn_disable();
            wdog_WatchdogTrigger();         // feed external and internal

            // wait for timeout - internal should expire first
            for (;;)
            {
            }
        }
        else                                // test the external watchdog
        {
#if USE_INTERNAL_WATCHDOG != 0
            wdog_WaitExternalWatchdog();    // never returns
#endif
        }
    }
}




#ifndef SETPOINT_LOWIP
#define SETPOINT_LOWIP INT_PERCENT_OF_RANGE(50.0) //don't care
#endif
#ifndef SETPOINT_FULLIP
#define SETPOINT_FULLIP INT_PERCENT_OF_RANGE(50.0) //don't care
#endif

/**
\brief sets the I/P low or high even if device is in factory/out-of-service mode
*/
s8_least hartcmd_SaturateMainOutput(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);
    u8 flag;
    const Req_SaturateMainOutput_t *s = (const void *)src;

    flag = util_GetU8(s->OutputFlag[0]);
    if(flag == 0)
    {
        mode_SetControlMode(CONTROL_IPOUT_LOW, SETPOINT_LOWIP);
    }
    else
    {
        mode_SetControlMode(CONTROL_IPOUT_HIGH_FACTORY, SETPOINT_FULLIP);
    }
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}


/** \brief Read expected FRAM signatures
*/
s8_least hartcmd_ReadExpectedNVMEMSignature(const u8 *src, u8 *dst)
{
    const Req_ReadExpectedNVMEMSignature_t *s = (const void *)src;
    Rsp_ReadExpectedNVMEMSignature_t *d = (void *)dst;
    s8_least ret;
    u8_least id = util_GetU8(s->NVMEMVolumeId[0]);
#ifndef OLD_NVRAM
    const StartupVersionNumber_t *p = nvmem_GetVersion(NVRAMID_StartupVersionNumber+id, NULL);
    if(p == NULL)
    {
        ret = HART_INVALID_DATA;
    }
    else
    {
        util_PutU32(d->NVMEMSignature[0], p->VersionNumber);
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
#else
    if(id > NVMEM_MAX_VOLID)
    {
        ret = HART_INVALID_DATA;
    }
    else
    {
        util_PutU32(d->NVMEMSignature[0], MNCB_NVRAM_SIGNATURE);
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
#endif
    return ret;
}


/* This line marks the end of the source */

