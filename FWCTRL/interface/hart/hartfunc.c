/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hartfunc.c
    \brief The functions used by each HART command: the HART Functions Module

    CPU: Any

    OWNER: LS

    \ingroup HARTapp
*/


#define NEED_NVMEM_END //expose hidden stuff
#include "mnwrap.h"
#include MEMMAP_H_

#include "projectdef.h"
//#include "pressmon.h"
#include "oswrap.h"
#include "mnassert.h"
#include "nvram.h"
#include "utility.h"
#include "devicemode.h"
#include "faultdef.h"
#include "faultpublic.h"
#include "configure.h"
#include "diagnostics.h"
#include "bufferhandler.h"
#include "selftune.h"
#include "control.h"
#include "tempr.h"
#include "pressures.h"
#include "process.h"
//#include "reset.h"
#include "hartfunc.h"
#include "hartcmd.h"
#include "hart.h"
#include "tempcomp.h"
#include "smoothing.h"
#include "mncbdefs.h"
#include "sysio.h"

#include "hartdef.h"
//#include "hartpriv.h"
#include "wprotect.h"

#include "poscharact.h"
#if FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_ENABLED
#include "bumpless.h"
#endif
#include "ctllimits.h"

#if FEATURE_SIGNAL_SETPOINT == FEATURE_SIGNAL_SETPOINT_SUPPORTED
#include "signalsp.h"
#endif

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE
#include "uihw_test.h"
#endif

#include "dohwif.h" //for CMD 200 rework

#include "fpconvert.h"

#include "ipcurr.h"
#include "hartapputils.h"

#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#include "insignal.h"
#endif

#if FEATURE_AO == FEATURE_AO_SUPPORTED
#include "ao.h"
#endif

#include "datahog.h"
#include "diagrw.h"

//#include "hartapputils.h"
#include "ramdatamap.h"

#define NON_LINEAR_TRANSFER 4u
#define LINEAR_TRANSFER 0

#define NOT_USED 250u

//#define HART_HCF_NONE 251u //defined by HCF
#define HART_HCF_NOTWP 0u //defined by HCF
#define HART_HCF_WP    1u //defined by HCF

//--------------- App layer functions ---------------------
/*lint -esym(613,src,dst) pointers for the app layer come from mnhartcmd.c
                          and are guaranteed non-NULL.
*/

//Configuration commands wrappers
s8_least hartcmd_ReadSettings(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_OK;
}
s8_least hartcmd_WriteSettings(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_OK;
}


/**
\brief Returns basic HART addressing and command information

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_0_ReadUniqueIdentifier(const u8 *src, u8 *dst)
{
//"0:Ask Address,<Dummy,<MfgID,<DeviceType,<Preambles,<CmdRev,<TXRev,<SWRev,<HWRev,<Flags,<DeviceID;"

    const HartData_t * tmpptr;

    dst[HC0_DUMMY] = 254;
    dst[HC0_MFGID] = MNCB_MANUFACTURER_ID;
    dst[HC0_DEVICE_TYPE] = MNCB_MANUFACTURER_DEVICE_CODE;
    dst[HC0_PREAMBLES] = NBR_REQUEST_PREAM;
    dst[HC0_CMDREV] = UNIV_CMD_REV;
    dst[HC0_TXREV] = TXSPEC_REV;

    dst[HC0_SWREV] = SW_REV;
    dst[HC0_HWREV] = MNCB_HARDWARE_REVISION;
    dst[HC0_FLAG] = FLAGS;

    tmpptr = hart_GetHartData();
    util_PutU8Array(&dst[HC0_DEVICE_ID], 3u, tmpptr->device_id);

    UNUSED_OK(src);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

#if HART_SELECTION_CMD_1 == (HART_OPTIONS_CMD_1_OPTION_SUPPORTED)
/**
\brief Returns position

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_1_ReadPrimaryVariable(const u8 *src, u8 *dst)
{
    //"1:Read Primary Var,<PosUnits,<Pos;"
    pos_t Position;
/*
    Convert position to floating point
    Add data to send buffer (see software specifications for details of data to add).
    Hart_send()
*/
    //use smoothed position
    //Position = control_GetPosition();
    //Position = smooth_GetSmoothedData(SELECTION_POSITION);
    Position = (pos_t)vpos_GetSmoothedScaledPosition();

    u8 units = fpconvert_IntToFloatBuffer(Position, UNITSID_POSITION, &dst[HC1_POS]);

    util_PutU8(&dst[HC1_POS_UNITS], units);

    UNUSED_OK(src);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif //HART_SELECTION_CMD_1

#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
//deprecated
/**
\brief Returns the input current

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_2_ReadCurrent(const u8 *src, u8 *dst)
{
    //"2:Read Current,<Sig,<SigPercent;"
    s16 RawSignal;
    percent_least_t ScaledSignal;

/*    Convert signal to floating point
    Add data to send buffer (see software specifications for details of data to add).
*/

    //use smoothed signal
    //get and convert signal
    RawSignal = sig_GetSmoothedSignal();
    (void)fpconvert_IntToFloatBuffer(RawSignal, UNITSID_SIGNAL_ENTRY, &dst[HC2_SIGNAL]);
    //note:  we scale the signal as if it were ATO always - this hart parameter
    //      doesn't depend on ATO or ATC
    ScaledSignal = sig_ConvertSignalToStd(RawSignal);
    (void)fpconvert_IntToFloatBuffer(ScaledSignal, UNITSID_PERCENT_ENTRY, &dst[HC2_SIGNAL_PERCENT]);

    UNUSED_OK(src);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif

#if HART_SELECTION_CMD_6 == (HART_OPTIONS_CMD_6_OPTION_SUPPORTED)
#define MAX_POLLING_ADDRESS 15u

/**
\brief Sets the polling address of the device

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_6_WritePollingAddress(const u8 *src, u8 *dst)
{
//MESCO
    const HartData_t * tmpptr;
    HartData_t tmp;
    ErrorCode_t retval;
    u8_least PollingAddress;
    s8_least ret;

    PollingAddress = src[HC6_POLLING_ADDRESS];
    if ((PollingAddress > MAX_POLLING_ADDRESS))
    {
        ret = HART_INVALID_SELECTION;
    }
    else
    {
        tmpptr = hart_GetHartData();
        tmp = *tmpptr;
        tmp.transmit_address = (u8)PollingAddress;

        retval = hart_SetHartData(&tmp);

        if (ERR_OK == retval)
        {
            //AK: pre LS, it duplicates what will be done later,PUTU8( HC6_POLLING_ADDRESS, tmpptr->transmit_address);
            ret = HART_OK;
        }
        else // FRAM write error
        {
            ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR;
        }
    }

    UNUSED_OK(dst);

    return ret;
}
#endif //HART_SELECTION_CMD_6

#if HART_SELECTION_CMD_11 == (HART_OPTIONS_CMD_11_OPTION_SUPPORTED)
/**
\brief
*/
s8_least hart_Command_11_ReadUniqueIdentifierByTag(const u8 *src, u8 *dst)
{
    u32 i;
    s8_least ret;
    const HartData_t * tmpptr;

    tmpptr = hart_GetHartData();

    i = 0;
    while ((i < HC11_REQ_LENGTH) && (src[i] == tmpptr->tag[i]))
    {
        i++;
    }

    if (i >= HC11_REQ_LENGTH)
    {
       ret = hart_Command_0_ReadUniqueIdentifier(src, dst);
    }
    else
    {
        Hart_DropFrame();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
}
#endif //HART_SELECTION_CMD_11

#if HART_SELECTION_MESSAGE == (HART_OPTIONS_MESSAGE_OPTION_SUPPORTED)
/**
\brief Returns the Message field in the device

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_12_ReadMessage(const u8 *src, u8 *dst)
{
//MESCO
//NOTE:  I have assumed that the ascii data is not translated from 6bit to 8 bit
//      and therefore we should just use get/put Array instead of get/put ascii

    const HartData_t * tmpptr;

    tmpptr = hart_GetHartData();

    util_PutU8Array(&dst[HC12_MESSAGE], HC12_LENGTH, (const u8 *)tmpptr->message);

    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif //HART_SELECTION_MESSAGE


#if HART_SELECTION_TAGDESC == (HART_OPTIONS_TAGDESC_OPTION_SUPPORTED)
/**
\brief Returns the tag, descriptor, and date fields in the device

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_13_ReadTagAndDescriptor(const u8 *src, u8 *dst)
{
//NOTE:  I have assumed that the ascii data is not translated from 6bit to 8 bit
//      and therefore we should just use get/put Array instead of get/put ascii
    const HartData_t * tmpptr;

    tmpptr = hart_GetHartData();

    util_PutU8Array( &dst[HC13_TAG], HC13_TAG_LENGTH, (const u8 *)tmpptr->tag);
    util_PutU8Array( &dst[HC13_DESCRIPTOR], HC13_DESCRIPTOR_LENGTH, (const u8 *)tmpptr->descriptor);
    util_PutU8Array( &dst[HC13_DATE], HC13_DATE_LENGTH, (const u8 *)tmpptr->date);

    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif //HART_SELECTION_TAGDESC

/**
\brief Returns the transducer information in the device.

  This data is not used by the SVI but the command is provided here
  for compatibility with some DCS systems.

Notes:
  This command is allowed in all modes, even when write busy or process busy is set

To be implemented by Mesco
*/
s8_least hart_Command_14_ReadTransducerInfo(const u8 *src, u8 *dst)
{
    //"14:Read Transducer Info,<TSerial,<TUnits,<TULim,<TLLim,<TSpan;"
    //This command reports constants and is only implemented to statisfy some DCS systems

    util_PutU24(&dst[HC14_SERIAL], 0u);
    util_PutU8(&dst[HC14_UNITS], fpconvert_GetUnits(UNITSID_POSITION));
    util_PutFloat(&dst[HC14_ULIM], 180.0F); //AK: Need symbolic names already used internally!
    util_PutFloat(&dst[HC14_LLIM], -5.0F);
    util_PutFloat(&dst[HC14_SPAN], 100.0F);

    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief Returns the transmitter information in the device.

  This data is not used by the SVI but the command is provided here for compatibility with some DCS systems.
To be implemented by Mesco

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_15_ReadTransmitterInfo(const u8 *src, u8 *dst)
{
    //"15:Read PV Output Info, <AlarmCode, <TransferFunc, <Units, <URV, <LRV, <Damping15, <WriteProtect, <PrivLabel;"
    //This command reports constants and is only implemented to statisfy some DCS systems
    util_PutU8(&dst[HC15_ALARM], (u8)NOT_USED);

    if(poscharact_GetCharacterizationSel(NULL)->CharactSel == CHARACT_LINEAR)
    {
        util_PutU8(&dst[HC15_TXFR_FCN], (u8)LINEAR_TRANSFER);
    }
    else
    {
        util_PutU8(&dst[HC15_TXFR_FCN], (u8)NON_LINEAR_TRANSFER);
    }

    util_PutU8(&dst[HC15_UNITS], fpconvert_GetUnits(UNITSID_POSITION));
    util_PutFloat(&dst[HC15_URV], 100.0F); //AK: Symbolics?
    util_PutFloat(&dst[HC15_LRV], 0.0F);
    util_PutFloat(&dst[HC15_DAMPING], 0.0F);

    if (bios_ReadWriteProtectInput())
    {
        util_PutU8(&dst[HC15_WRITE_PROT], HART_HCF_WP);
    }
    else
    {
        util_PutU8(&dst[HC15_WRITE_PROT], HART_HCF_NOTWP);
    }

    util_PutU8(&dst[HC15_PRIVATE_LABEL], MNCB_MANUFACTURER_ID);

    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

#if HART_SELECTION_ASSYNUM == (HART_OPTIONS_ASSYNUM_OPTION_SUPPORTED)
/**
\brief Returns the final assembly number

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_16_ReadFinalAssemblyNumber(const u8 *src, u8 *dst)
{
//MESCO
//NOTE:  Mesco seems to have defined final assy number as a byte array - I leave it like that
    const HartData_t * tmpptr;

    tmpptr = hart_GetHartData();

    util_PutU8Array(&dst[HC16_FINAL_ASSY], HC16_LENGTH, (const u8 *)tmpptr->finalass_nbr);

    UNUSED_OK(src);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif //HART_SELECTION_ASSYNUM

#if (HART_SELECTION_ASSYNUM == HART_OPTIONS_ASSYNUM_OPTION_SUPPORTED) \
    || (HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED) \
    || (HART_SELECTION_MESSAGE == HART_OPTIONS_MESSAGE_OPTION_SUPPORTED) \
    || (HART_SELECTION_TAGDESC == HART_OPTIONS_TAGDESC_OPTION_SUPPORTED)
//AK: A common wrapper for HART data stuff
static s8_least hart_WriteHartData(const HartData_t *hdata)
{
    s8_least ret;
    ErrorCode_t retval;
    retval = hart_SetHartData(hdata);
    if (ERR_OK == retval)
    {
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else
    {
        ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR;
    }

    return ret;
}
#endif

#if HART_SELECTION_MESSAGE == (HART_OPTIONS_MESSAGE_OPTION_SUPPORTED)
/**
\brief Sets the Message field of the device

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_17_WriteMessage(const u8 *src, u8 *dst)
{
//MESCO

    const HartData_t * tmpptr;
    HartData_t tmp;

    tmpptr = hart_GetHartData();
    tmp = *tmpptr;

    util_GetU8Array(&src[HC17_MESSAGE], HC17_LENGTH, tmp.message);
    UNUSED_OK(dst);
    return hart_WriteHartData(&tmp);
}
#endif //HART_SELECTION_MESSAGE

#if HART_SELECTION_TAGDESC == (HART_OPTIONS_TAGDESC_OPTION_SUPPORTED)
/**
\brief Sets the tag, descriptor, and date fields of the device

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_18_WriteTagAndDescriptor(const u8 *src, u8 *dst)
{
//MESCO
    const HartData_t * tmpptr;
    HartData_t tmp;

    tmpptr = hart_GetHartData();
    tmp = *tmpptr;

    util_GetU8Array( &src[HC13_TAG], HC13_TAG_LENGTH, tmp.tag);
    util_GetU8Array( &src[HC13_DESCRIPTOR], HC13_DESCRIPTOR_LENGTH, tmp.descriptor);
    util_GetU8Array( &src[HC13_DATE], HC13_DATE_LENGTH, tmp.date);

    UNUSED_OK(dst);
    return hart_WriteHartData(&tmp);
}
#endif //HART_SELECTION_TAGDESC

#if HART_SELECTION_ASSYNUM == (HART_OPTIONS_ASSYNUM_OPTION_SUPPORTED)
/**
\brief Sets the final assembly number field of the device

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_19_WriteFinalAssemblyNumber(const u8 *src, u8 *dst)
{
//MESCO
    const HartData_t * tmpptr;
    HartData_t tmp;

    tmpptr = hart_GetHartData();
    tmp = *tmpptr;

    util_GetU8Array( &src[HC19_FINAL_ASSY], HC19_LENGTH, tmp.finalass_nbr);

    UNUSED_OK(dst);
    return hart_WriteHartData(&tmp);
}
#endif //HART_SELECTION_ASSYNUM

/**
\brief Clears the configuration changed bit

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_38_ResetConfigurationChangedFlag(const u8 *src, u8 *dst)
{
    //handled by hart_makeResponseFlags() akt_response_code_2 &= ~HART_CONFIG_CHANGED; //AK:TODO
    (void)nvram_ResetConfigurationChangedFlag(hart_MsgFromSecondaryMaster(src)==HartMaster_Primary); //can't do anything useful with return code yet
    UNUSED_OK(dst);
    UNUSED_OK(src);
    return HART_OK;
}


/**
\brief Performs a master reset

Notes:
This command is allowed in all modes
*/
s8_least hartcmd_Reset(const u8 *src, u8 *dst)
{
    //call reset with a delay that will let the hart response happen
    hart_ResetDeviceOnSend();
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

#if HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED
/**
\brief Sets the command to be used by burst mode
To be implemented by Mesco.

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_108_WriteBurstModeCommand(const u8 *src, u8 *dst)
{
    const HartData_t * tmpptr;
    HartData_t tmp;
    u8 burstcmd;
    s8_least ret;

    burstcmd = util_GetU8(&src[HC108_CMD]);

    if ((0 == burstcmd) || (burstcmd > 3))
    {
        ret = HART_INVALID_SELECTION;
    }
    else
    {
        tmpptr = hart_GetHartData();
        tmp = *tmpptr;

        tmp.burst_mode_cmd = burstcmd;

        ret = hart_WriteHartData(&tmp);
    }
    UNUSED_OK(dst);
    return ret;
}
#endif //HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED

#if HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED
#define ON  1
#define OFF 0

/**
\brief Turns burst mode on or off
To be implemented by Mesco.

Notes:
This command is allowed in all modes
*/
s8_least hart_Command_109_WriteBurstModeControl(const u8 *src, u8 *dst)
{
    const HartData_t * tmpptr;
    HartData_t tmp;
    s8_least ret;

    u8 burst_sel;

    burst_sel = util_GetU8(&src[HC109_CTL]);

    if ((ON != burst_sel) && (OFF != burst_sel))
    {
        //HART_ERROR_RETURN__(INVALID_SELECTION);
        ret = HART_INVALID_SELECTION;
    }
    else
    {
        tmpptr = hart_GetHartData();
        tmp = *tmpptr;
        tmp.burst_mode_ctrl = burst_sel;

        ret = hart_WriteHartData(&tmp);
    }

    UNUSED_OK(dst);
    return ret;
}
#endif //HART_SELECTION_BURST_MODE == HART_OPTIONS_BURST_MODE_OPTION_SUPPORTED

//Special indices
#define INDEX_TRAP_AREA 10000

/**
\brief Returns the address of the variable from a table of allowed variables

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadVariableAddress(const u8 *src, u8 *dst)
{
    const Req_ReadVariableAddress_t *s = (const void *)src;
    Rsp_ReadVariableAddress_t *d = (void *)dst;
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    u16 Index;
    u16 offset=0, length=0;

    //get the requested variable number
    Index = util_GetU16(s->VariableNumber[0]);

    if(Index < NVRAM_ENTRIES)
    {
        //this is an FRAM variable
        util_PutU8(d->VariableType[0], HC_VarTypeNVMEM);

        (void)nvmem_GetMapEntry(Index, &offset, &length, NULL); //assuming vol 0 for now
        util_PutU16(d->VariableAddress[0], offset);
        util_PutU16(d->VariableSize[0], length);
    }
    else if(Index >= RAMID_FLAG) //base addr
    {
        bool_t result = ram_GetMapEntry(Index, &offset, &length);
        if(result)
        {
            //this is a RAM variable
            util_PutU8(d->VariableType[0], HC_VarTypeRAM);
        }
        else
        {
            ret = HART_INVALID_SELECTION;
        }
    }
    else
    {
        //Special cases
        switch(Index)
        {
            case INDEX_TRAP_AREA:
                //this is an FRAM variable
                util_PutU8(d->VariableType[0], HC_VarTypeNVMEM);
                offset = ASSERT_DATA;
                length = ASSERT_DATA_STORE_SIZE+ASSERT_POSITION_SIZE;
                break;
            default:
                //nothing else yet
                ret = HART_INVALID_SELECTION;
                break;
        }
    }
    util_PutU16(d->VariableAddress[0], offset);
    util_PutU16(d->VariableSize[0], length);

    return ret;
}

//--------------------------------------------------------------------
static const DeviceModeEnum_t devmode2hart_tab[MODEBIT_TOTAL] =
{
    [MODEBIT_FAILSAFE] = HFailsafe,
    [MODEBIT_SETUP] = HSetup,
    [MODEBIT_MANUAL] = HManual,
    [MODEBIT_OPERATE] = HNormal,
};

static const devmodebit_t hart2devmode_tab[MODEBIT_TOTAL] =
{
    [HFailsafe] = MODEBIT_FAILSAFE,
    [HSetup] = MODEBIT_SETUP,
    [HManual] = MODEBIT_MANUAL,
    [HNormal] = MODEBIT_OPERATE,
};

/** \brief Convert internal device mode representation to HART device mode representation
*/
static DeviceModeEnum_t hart_FormatDevModeToHART(devmode_t mode)
{
    return devmode2hart_tab[intlog(mode)-1];
}

/** \brief Convert HART device mode representation to internal device mode representation
*/
static devmode_t hart_FormatDevModeToInternal(u8 hmode)
{
    if((u32)hmode >= NELEM(hart2devmode_tab))
    {
        return MODE_INVALID;
    }
    return MODEMAP(hart2devmode_tab[hmode]);
}




/**
\brief Changes the mode of the device
*/
s8_least hartcmd_ChangeDeviceMode(const u8 *src, u8 *dst)
{
    //"135:Set Mode,>Mode;"
    u8 Mode;
    ErrorCode_t err;

    const Req_ChangeDeviceMode_t *s = (const void *)src;
    Rsp_ChangeDeviceMode_t *d = (void *)dst;
    UNUSED_OK(d->DeviceMode); //rely on HART framework to fill data

    UNUSED_OK(dst);
    Mode = util_GetU8(s->DeviceMode[0]);
    Mode = hart_FormatDevModeToInternal(Mode);
    {
        switch(Mode)
        {
            case MODE_SETUP:
                err = mode_SetModeInterface(MODE_SETUP);
                break;
            case MODE_MANUAL:
                err = ERR_INVALID_PARAMETER; //we hide Manual mode in APP
                break;
            case MODE_OPERATE:
#if FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_ENABLED
#error "Broken"
                err = mode_SetNormalModeEx();
#endif
#if FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_DISABLED
                err = mode_SetModeInterface(MODE_OPERATE);
#endif 
                break;
            default:
                err = ERR_INVALID_PARAMETER;
                break;
        }
    }

    return err2hart(err);
}


/**
\brief Clears the fault codes

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_138_ClearFaults(const u8 *src, u8 *dst)
{
    bool_t flag;
    u8 Input;

    UNUSED_OK(dst);
    //handle this way so that ANYTHING not 1 is false
    Input = util_GetU8(&src[HC138_FLAG]);
    if(Input == 1)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    //"138:Clear Faults;"
    error_ClearFaults(flag);
    return HART_OK;
}

/**
\brief Returns the strokes, cycles, time open/closed/near

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_139_ReadContinuousDiagnostics(const u8 *src, u8 *dst)
{
    //"139:Read Continuous Diag Data,<Travel,<TimeClosed,<TimeOpen,<TimeNear,<Cycles;"
    const ContinuousDiagnostics_t* pContinuousDiagnostics;
    UNUSED_OK(src);

    //not allowed in low cost mode
    if(cnfg_GetOptionConfigDashVersion()==LOW_COST_VERSION)
    {
        /* Legitimate early return: Pre-requisites check */
        return COMMAND_NOT_IMPLEMENTED;
    }

    pContinuousDiagnostics = control_GetContinuousDiagnostics();

    //put the data into the hart buffer
    util_PutU32(&dst[HC139_TRAVEL], pContinuousDiagnostics->TotalTravelCntr);
    util_PutU32(&dst[HC139_TIME_CLOSED], pContinuousDiagnostics->TimeClosedCntr);
    util_PutU32(&dst[HC139_TIME_OPEN], pContinuousDiagnostics->TimeOpenCntr);
    util_PutU32(&dst[HC139_TIME_NEAR], pContinuousDiagnostics->TimeNearCntr);
    util_PutU32(&dst[HC139_CYCLES], pContinuousDiagnostics->CyclesCntr);

    return HART_OK;
}

/**
\brief Clears the continuous diagnostic data.
*/
s8_least hart_Command_140_ResetContinuousDiagnostics(const u8 *src, u8 *dst)
{
    //not allowed in low cost mode
    if(cnfg_GetOptionConfigDashVersion()==LOW_COST_VERSION)
    {
        /* Legitimate early return: Pre-requisites check */
        return COMMAND_NOT_IMPLEMENTED;
    }

    //"140:Reset Continuous Diag;"
    UNUSED_OK(src);
    UNUSED_OK(dst);
    control_ClearContinuousDiagnostics();
    return HART_OK;
}

/** \brief Stops replacement interface
*/
s8_least hartcmd_WritePositionStops(const u8 *src, u8 *dst)
{
    const Req_WritePositionStops_t *req = (const void *)src;
    Rsp_WritePositionStops_t *rsp = (void *)dst;
    UNUSED_OK(rsp->PositionLOWStop); //rely on the framework to fill in
    UNUSED_OK(rsp->PositionHIGHStop); //rely on the framework to fill in
    PositionConf_t conf;
    (void)pos_GetPositionConf(&conf);
    conf.rangeval[Xlow] = util_GetS16(req->PositionLOWStop[0]);
    conf.rangeval[Xhi] = util_GetS16(req->PositionHIGHStop[0]);
    ErrorCode_t err = pos_SetPositionConf(&conf);
    if(err == ERR_OK)
    {
        error_ClearFault(FAULT_FIND_STOPS_FAILED);
        //this call cleans up a bad bias - mostly needed for 1st time units
        control_ResetBiasChangeFlag();
    }
    return err2hart(err);
}

/**
\brief Returns the raw position, raw signal, etc.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_141_ReadRawData(const u8 *src, u8 *dst)
{
    //"141:Read Raw Data,<RawSignal,<RawPosition,<RawPressure,<PWMout,<LowPosStop,"
    //        "<HighPosStop,<Temp,<LowTemp,<HighTemp,<IPOutput;"

    /** TFS:4185 */
    u16 nPWMout;
    s16 nPosition, nSignal, IPCurrent;
    const PositionConf_t*   pPositionStop;
    const BoardTemperature_t* pTemperatureData;

    UNUSED_OK(src);
    //get the data
#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
    nSignal = sig_GetSignal();
#else
    nSignal = 0; //RED_FLAG fixme
#endif

    nPosition = (s16)vpos_GetRawPosition();

    nPWMout = sysio_GetRealPWM();      /** TFS:4185 */
    pPositionStop = pos_GetPositionConf(NULL);
    pTemperatureData = tempr_GetTemperature(TEMPR_MAINBOARD, NULL);

    IPCurrent = (s16)ipcurr_GetCompensatedIpCurrent();

    //put the data into the hart buffer
    util_PutU16(&dst[HC141_RAW_SIGNAL], (u16)nSignal);
    util_PutU16(&dst[HC141_RAW_POSITION], (u16)nPosition);

    //LS - removed code that set this to 0 - we need to see pressure for testing
    util_PutS16(&dst[HC141_RAW_PRESSURE], pres_GetMainPressure());

    util_PutU16(&dst[HC141_IPOUT], nPWMout);    /** TFS:4185 */
#if 0
    util_PutU16(&dst[HC141_LOW_POS_STOP], (u16)pPositionStop->LowPositionStop);
    util_PutU16(&dst[HC141_HIGH_POS_STOP], (u16)pPositionStop->HighPositionStop);
#else
    util_PutU16(&dst[HC141_LOW_POS_STOP], (u16)pPositionStop->rangeval[Xlow]);
    util_PutU16(&dst[HC141_HIGH_POS_STOP], (u16)pPositionStop->rangeval[Xhi]);
#endif
    util_PutU16(&dst[HC141_TEMP], (u16)(pTemperatureData->nBoardTemperature));
    util_PutU16(&dst[HC141_LOW_TEMP], (u16)(pTemperatureData->nLowestTemperature));
    util_PutU16(&dst[HC141_HIGH_TEMP], (u16)(pTemperatureData->nHighestTemperature));
    util_PutU16(&dst[HC141_IPCURRENT], (u16)IPCurrent);
    return HART_OK;
}

/**
\brief Returns the temperature data

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadTemperatures(const u8 *src, u8 *dst)
{
    BoardTemperature_t TemperatureData;
    UNUSED_OK(src);
    Rsp_ReadTemperatures_t *d = (void *)dst;
    Temperatures_t *t = (void *)d->Temperatures[0];
    (void)tempr_GetTemperature(TEMPR_MAINBOARD, &TemperatureData);

    u8 units = fpconvert_IntToFloatBuffer(TemperatureData.nBoardTemperature, UNITSID_TEMPR, t->CurrentTemperature[0]);
    util_PutU8(d->TemprUnits[0], units);
    (void)fpconvert_IntToFloatBuffer(TemperatureData.nHighestTemperature, UNITSID_TEMPR, t->MaxTemperature[0]);
    (void)fpconvert_IntToFloatBuffer(TemperatureData.nLowestTemperature, UNITSID_TEMPR, t->MinTemperature[0]);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}


/**
\brief Save some startup bias parameters

Notes:
    Only valid in OOS mode - used primarily in the factory
*/
s8_least hart_Command_174_WriteBiasParameters(const u8 *src, u8 *dst)
{
    s8_least ret;
    BiasExt_t BiasExt;
    UNUSED_OK(dst);

    BiasExt.uiBiasShift = util_GetU16(&src[HC174_BIAS_SHIFT]);
    BiasExt.nBiasAddAirLoss = (s16)util_GetU16(&src[HC174_BIAS_ADD_AIRLOSS]);
    BiasExt.nBiasAdd = (s16)util_GetU16(&src[HC174_BAIS_ADD]);
    BiasExt.nBiasTempCoef = (s16)util_GetU16(&src[HC174_BIAS_TEMP_COEF]);
    BiasExt.uiMaxHysteresis = util_GetU16(&src[HC174_HYSTERESIS]);

    if(control_SetBiasExt(&BiasExt) != ERR_OK)
    {
        //HART_ERROR_RETURN__(HART_INVALID_DATA);
        ret = HART_INVALID_DATA;
    }
    else
    {
        ///for write commands, move the input data to the output
        ret = HART_OK;
    }
    return ret;
}



/**
\brief Replaces stop and recalibrates the position

Notes:
The control mode must be in full open or full closed so that the valve is at the stop position
*/
s8_least hartcmd_ManualFindStops(const u8 *src, u8 *dst)
{
    const Req_ManualFindStops_t *s = (const void *)src;
    Rsp_ManualFindStops_t *d = (void *)dst;
    UNUSED_OK(d);

    u8 Step;
    ErrorCode_t err;

    //get the data
    Step = util_GetU8(s->ManualFindStopsStep[0]);

    switch(Step)
    {
        case HFindStopsStart:
        case HFindStopsCancel:
            err = poscal_CommitStops(false);
            break;
        case HFindStopsAccept:
            err = poscal_AcceptStop();
            break;
        case HFindStopsCommit:
            err = poscal_CommitStops(true);
            break;
        default:
            err = ERR_INVALID_PARAMETER;
            break;
    }

    return err2hart(err);
}

/**
\brief This command runs the find stops process
*/
s8_least hartcmd_FindStops(const u8 *src, u8 *dst)
{
    s8_least ret;
    UNUSED_OK(src);
    UNUSED_OK(dst);
    if(hart_SetProcessCommand(PROC_FIND_STOPS))
    {
        ret = HART_BUSY;
    }
    else
    {
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    return ret;
}

#if FEATURE_SIGNAL_SETPOINT == FEATURE_SIGNAL_SETPOINT_SUPPORTED
//deprecated
/**
\brief Saves the low and high signal range

Notes:
    Only valid in OOS mode
*/
s8_least hart_Command_181_WriteInputCurrentRange(const u8 *src, u8 *dst)
{
    //"181:Write Signal Values,>LowSignal,>HighSignal;"
    s8_least ret;
    UNUSED_OK(dst);

    //get the data from the hart buffer
    SignalData_t sd;
    (void)cnfg_GetSignalData(&sd);

    sd.LowSignal = fpconvert_FloatBufferToInt16Clamped(&src[HC181_LOW_SIGNAL], UNITSID_SIGNAL_ENTRY, SignalLimits_range[Xlow]);
    sd.HighSignal = fpconvert_FloatBufferToInt16Clamped(&src[HC181_HIGH_SIGNAL], UNITSID_SIGNAL_ENTRY, SignalLimits_range[Xhi]);

    //save the data
    if(cnfg_SetSignalData(&sd) != ERR_OK)
    {
        //HART_ERROR_RETURN__(HART_INVALID_DATA);
        ret = HART_INVALID_DATA;
    }
    else
    {
        ///for write commands, move the input data to the output
        ret = HART_OK;
    }
    return ret;
}
#endif

/**
\brief Resets the user calibrations back to the factory calibrations

Notes:
    Only valid in OOS mode

*/
s8_least hart_Command_183_ResetToFactorCal(const u8 *src, u8 *dst)
{
/* Set SignalCalData to factory default (4000 = 4ma, 20000=20ma) and save using SetSignalCalData() */
/* set pressure cal zero data to 0 */
    UNUSED_OK(src);
    UNUSED_OK(dst);

    ErrorCode_t ReturnValue;

    //set to defaults

//save the data
#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
    ReturnValue = sig_SetSignalCalData(NULL);
    if(ReturnValue != ERR_OK)
    {
        //should never have a problem with default data
        MN_ASSERT(ReturnValue == ERR_OK);
    }
#endif

    ReturnValue = pres_SetPressureCalData(NULL);
    if(ReturnValue != ERR_OK)
    {
        //should never have a problem with default data
        MN_ASSERT(ReturnValue == ERR_OK);
    }
#if FEATURE_AO == FEATURE_AO_SUPPORTED
    ReturnValue = ao_SetAOCalibration(AO_CHANNEL_POS_RETRANSMIT, NULL);
    if(ReturnValue != ERR_OK)
    {
        //should never have a problem with default data
        MN_ASSERT(ReturnValue == ERR_OK);
    }
#endif
    return HART_OK;
}


/**
\brief A shell for a diagnostic process
*/
s8_least hartcmd_RunaProcess(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE
//Complete this factory subcommand for LCX
s8_least hartcmd_TestLED(const u8 *src, u8 *dst)
{   // This command shall be valid ONLY when the device is in FACTORY mode
    // Now - validate the parameters
    // In this mode:
    // Type         - is the Type.
    // nSpeed       - TimeOut in Seconds, 0 means no T/O, command invalid
    // Parameter 1  - Device Test Mode #
    // Parameter 2  - Optional - for specific mode, LED # to lit

    const Req_TestLED_t *s = (const void *)src;
    Rsp_TestLED_t *d = (void *)dst;
    UNUSED_OK(d);

    ErrorCode_t     err;
    test_TestMode_t TestMode = (test_TestMode_t)util_GetU8(s->LEDTestMode[0]);
    LEDNumber_t     TestLed = (LEDNumber_t)util_GetU8(s->LEDUnderTest[0]);
    u16_least       TestTime = util_GetU16(s->LEDTestTime[0]);

    err = test_SetTestParameters(TestMode, TestTime, TestLed);
    s8_least ret;
    if (err != ERR_OK)
    {   // Parameters are not accepted
        ret = HART_INVALID_SELECTION;
    }
    else
    {   // Parameters are OK
        if(hart_SetProcessCommand((u8)PROC_TEST_PROCESS))
        {   //could not start process
            //HART_ERROR_RETURN__(HART_BUSY);
            ret = HART_BUSY;
        }
        else
        {
            ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
        }
    }
    return ret;
}
#endif //FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE

#define DATAHOG_RUNFLAG 0x80U //for data collection indiaction; do not change!

/**
\brief Reads data from the diagnostic data buffer
*/
s8_least hartcmd_ReadDataBufferRaw(const u8 *src, u8 *dst)
{
    ErrorCode_t err;

    const Req_ReadDataBufferRaw_t *s = (const void *)src;
    Rsp_ReadDataBufferRaw_t *d = (void *)dst;

    u8 BufferId = util_GetU8(s->BufferId[0]);
    u16_least DataOffset = util_GetU16(s->DataOffset[0]);
    u8_least DataSampleSize = util_GetU8(s->DataSampleSize[0]);
    u8 DataSampleSkipCount = util_GetU8(s->DataSampleSkipCount[0]);

    const u8 *p = (const u8 *)buffer_GetXDiagnosticBuffer(BufferId);
    s16_least n = buffer_GetEntriesInXDiagnosticBuffer(BufferId); //in diag_t samples
    u16_least bytes_in_buf = sizeof(diag_t) * (u16_least)n; //in bytes
    u16_least datasz = bytes_in_buf;

    if(p == NULL)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else if((DataOffset > datasz) || (DataSampleSize == 0) || (DataSampleSize > sizeof(d->RawDataSamples)))
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        datasz -= DataOffset;
        datasz = MIN(datasz, sizeof(d->RawDataSamples)); //number of bytes to populate
        u8_least num_samples = 0;
        u8 *rsp = d->RawDataSamples[0];
        while(datasz >= DataSampleSize)
        {
            mn_memcpy(rsp, p + DataOffset, DataSampleSize);
            rsp += DataSampleSize;
            DataOffset += DataSampleSize * (1U + DataSampleSkipCount);
            if((datasz >= DataSampleSize) && (DataOffset < bytes_in_buf))
            {
                datasz -= DataSampleSize;
            }
            else
            {
                datasz = 0;
            }
            num_samples++;
        }
        mn_memset(rsp, 0x80, sizeof(d->RawDataSamples) - (num_samples*DataSampleSize));

        util_PutU16(d->DataOffset[0], (u16)DataOffset);
        util_PutU8(d->DataSampleCount[0], (u8)num_samples);

        //Rely on HART framework to fill the members
        UNUSED_OK(d->BufferId);
        UNUSED_OK(d->DataSampleSize);
        UNUSED_OK(d->DataSampleSkipCount);
        
        /* A kink to let DTM know (in the buffer header) if data collection is running
            (Moved from unconditional run in datahog_Collect to avoid 
            data conflict with autotune)
        */
        if(util_GetU16(s->DataOffset[0]) == 0U) //reading the header 
        {
            const DatahogState_t *pstate = datahog_GetState(NULL);
            u8 runmask = 0U;

            MN_ENTER_CRITICAL();
                if(pstate->status[pstate->DatahogConfId] == DatahogCollecting)
                {
                    runmask = DATAHOG_RUNFLAG;
                }
            MN_EXIT_CRITICAL();
            //We steal MSB of high halfword of sampling interval to indicate running data collection
            u8 *devid_high = d->RawDataSamples[sizeof(diag_t)*(DIAGRW_HEADERSZ - DEVID_SIZE) + 1U]; //+1 byte because buffer is stored little-endian
            u8 upper = *devid_high;
            upper &= ~DATAHOG_RUNFLAG;
            upper |= runmask;
            *devid_high = upper;
        }

        err = ERR_OK;
    }

    return err2hart(err);
}


/**
\brief Returns the option configuration data.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/

#define CMD_200_BYTE_FOR_DO     BYTENUM(DO_OPTION)
#define CMD_200_BIT_FOR_DO      BYTEBITMASK(DO_OPTION)

CONST_ASSERT(OPTION_CONFIG_BYTES == HC200_LENGTH);
CONST_ASSERT(HC200_LENGTH == HC202_LENGTH);

s8_least hart_Command_200_ReadOptionConfiguration(const u8 *src, u8 *dst)
{
    //"200:Read Option Config,<OptionConfig;"
    //{"OptionConfig", (void*)NULL, H_ARRAY+16},

    const   OptionConfig_t* pOptionConfig;

    UNUSED_OK(src);

    // get a pointer to the configuration
    pOptionConfig = cnfg_GetOptionConfig();

    // and fill the response
    util_PutU8Array(&dst[HC200_OPTION_CONFIG], OPTION_CONFIG_BYTES, pOptionConfig->m_OptionConfig);

    // Extract the DO_OPTION
    u8  thebyte = pOptionConfig->m_OptionConfig[CMD_200_BYTE_FOR_DO];
    if (!bios_DOCardPresent())
    {   // Terminal Card is NOT present -- clear the bit
        thebyte &= ~CMD_200_BIT_FOR_DO;
    }

    util_PutU8(&dst[CMD_200_BYTE_FOR_DO], thebyte);
    return HART_OK;
}

/**
\brief Returns the actual option configuration data.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/

s8_least hart_Command_202_ActualReadOptionConfiguration(const u8 *src, u8 *dst)
{
    //"202:Actual Read Option Config,<OptionConfig;"
    //{"OptionConfig", (void*)NULL, H_ARRAY+16},

    const   OptionConfig_t* pOptionConfig;

    UNUSED_OK(src);

    // get a pointer to the configuration
    pOptionConfig = cnfg_GetOptionConfig();

    // and fill the response
    util_PutU8Array(&dst[HC202_OPTION_CONFIG], OPTION_CONFIG_BYTES, pOptionConfig->m_OptionConfig);
    return HART_OK;
}


#if FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
#define NUMBER_PRESSURES_REPORTED 5
/**
\brief Returns pressure data - returns 0 for pressures that are not enabled

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadAllPressures(const u8 *src, u8 *dst)
{
    Rsp_ReadAllPressures_t *d = (void *)dst;
    CONST_ASSERT(NUMBER_PRESSURES_REPORTED == NELEM(d->PressureArray));

    const BoardPressure_t* BoardPressure;
    pres_t Pressure;
    u32 i;
    bool_t bPressure[NUMBER_PRESSURES_REPORTED];
    static const u8 PressureIndex[NUMBER_PRESSURES_REPORTED] =
    {
        PRESSURE_ACT1_INDEX,
        PRESSURE_ACT2_INDEX,
        PRESSURE_SUPPLY_INDEX,
        PRESSURE_PILOT_INDEX,
        PRESSURE_ATM_INDEX
    };
    //static const u8 PressureDataStart[NUMBER_PRESSURES_REPORTED] = {HC201_PRESSURE, HC201_PRESSURE2, HC201_PRESSURE3, HC201_PRESSURE4};
    UNUSED_OK(src);

    //see which pressures are there
    bPressure[PRESSURE_ACT1_INDEX] = cnfg_GetOptionConfigFlag(PRESSURE_SENSOR_1);
    bPressure[PRESSURE_ACT2_INDEX] = cnfg_GetOptionConfigFlag(PRESSURE_SENSOR_2);
    bPressure[PRESSURE_SUPPLY_INDEX] = cnfg_GetOptionConfigFlag(PRESSURE_SUPPLY);
    bPressure[PRESSURE_PILOT_INDEX] = true; //TFS:3995 -- show Pilot Pressure in Cmd-201 for LCX
    bPressure[PRESSURE_ATM_INDEX] = true;
    CONST_ASSERT(NELEM(bPressure)==NUMBER_PRESSURES_REPORTED);

    BoardPressure = pres_GetPressureData();
    u8 PresUnits;

    for(i=0; i<NUMBER_PRESSURES_REPORTED; ++i)
    {
        Pressure = BoardPressure->Pressures[PressureIndex[i]];
        if(!bPressure[i] || (Pressure==PRESSURE_INVALID))
        {
            //Replace with 0; should turn into a NaN soon
            Pressure = 0;
        }
        PresUnits = fpconvert_IntToFloatBuffer(Pressure, UNITSID_PRESSURE_ENTRY, d->PressureArray[i]);
    }

    util_PutU8(d->PresUnits[0], PresUnits);

    return HART_OK;
}
#endif //FEATURE_PRESSURE_INPUTS_INCLUDED



#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
//deprected
/**
\brief Returns the signal values.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_213_ReadCurrentLoopValues(const u8 *src, u8 *dst)
{
    //see command 181 for defines
    //"213:Read Signal Values,<LowSignal,<HighSignal;"}
    const SignalData_t*     pSignalData;
    UNUSED_OK(src);
    pSignalData = cnfg_GetSignalData(NULL);

    (void)fpconvert_IntToFloatBuffer(pSignalData->LowSignal, UNITSID_SIGNAL_ENTRY, &dst[HC181_LOW_SIGNAL]);
    (void)fpconvert_IntToFloatBuffer(pSignalData->HighSignal, UNITSID_SIGNAL_ENTRY, &dst[HC181_HIGH_SIGNAL]);
    return HART_OK;
}
#endif //FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED

/**
\brief Reads the bias startup parameters

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_217_ReadBiasParameters(const u8 *src, u8 *dst)
{
    const BiasExt_t* pBiasExt;
    pBiasExt = control_GetBiasExt();

    UNUSED_OK(src);

    util_PutU16(&dst[HC174_BIAS_SHIFT], pBiasExt->uiBiasShift);
    util_PutU16(&dst[HC174_BIAS_ADD_AIRLOSS], (u16)(pBiasExt->nBiasAddAirLoss));
    util_PutU16(&dst[HC174_BAIS_ADD], (u16)(pBiasExt->nBiasAdd));
    util_PutU16(&dst[HC174_BIAS_TEMP_COEF], (u16)(pBiasExt->nBiasTempCoef));
    util_PutU16(&dst[HC174_HYSTERESIS], pBiasExt->uiMaxHysteresis);
    return HART_OK;
}


/**
\brief Writes the option configuation - factory only

Notes:
This command is allowed in only in oos mode
*/
s8_least hart_Command_248_WriteOptionConfig(const u8 *src, u8 *dst)
{
    u16 Key;
    OptionConfig_t OptionConfig;
    s8_least retCode;

    //make sure it's the factory sending this
    Key = util_GetU16(&src[HC248_KEY]);
    if(Key != HC248_KEY_VALUE)
    {
        /* Legitimate early return: Pre-requisites check */
        return COMMAND_NOT_IMPLEMENTED;
    }

    ///for write commands, move the input data to the output
    UNUSED_OK(dst);

    //save the option config data
    util_GetU8Array(&src[HC248_OPTION_CONFIG], OPTION_CONFIG_BYTES, OptionConfig.m_OptionConfig);
    if(cnfg_SetOptionConfig(&OptionConfig) != ERR_OK)
    {
        retCode = HART_INVALID_DATA;
    }
    else
    {
        retCode = HART_OK;
    }

    return retCode;
}


/**
\brief Returns the mode

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadDeviceMode(const u8 *src, u8 *dst)
{
    //"249:Read Mode,<Mode,<SubMode;"
#ifdef OLD_DEVMODE
    const ModeData_t* pMode;
    u8 submode;

    // get a pointer to the current mode information
    pMode = mode_GetMode();

     // write the mode in to the buffer
    util_PutU8(&dst[HC249_MODE], pMode->mode);
    submode = pMode->submode;
    if(error_IsFault(FAULT_MARGINAL_POWER))
    {
        submode |= SUBMODE_MARGINAL_POWER; //an artificial flag for ValVue
    }
    util_PutU8(&dst[HC249_SUB_MODE], submode);
#else
    Rsp_ReadDeviceMode_t *d1 = (void *)dst;
    FullDeviceMode_t *d = (void *)d1->FullDeviceMode[0];
    devsubmode_t submode = mode_GetSubmode();
    devmode_t mode = mode_GetMode();
    DeviceModeEnum_t dmode = hart_FormatDevModeToHART(mode);
#if 0 //temporary patch
    if(dmode == HFailsafe)
    {
        dmode = HSetup;
        submode |= 0x02U; //old failsafe
    }
#endif
    util_PutU8(d->DeviceMode[0], dmode);
    util_PutU8(d->DeviceSubmode[0], submode);
#endif
    UNUSED_OK(src);
    return HART_OK;
}



/**
\brief Returns the status of long processes.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_CheckProcess(const u8 *src, u8 *dst)
{
    Rsp_CheckProcess_t *d = (void *)dst;
    UNUSED_OK(src);

    util_PutU8(d->ProcessId[0], process_GetProcId());
    util_PutU8(d->PercentComplete[0], process_CheckProcessProgress());

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief Stops any process running by setting a flag.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_253_HaltProcess(const u8 *src, u8 *dst)
{
    // cancel the process, no checking required
    process_CancelProcess();
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_OK;
}

#ifdef OLD_DEVMODE
/** \brief Returns true iff device mode is acceptable for the command
*/
static bool_t hart_TestMode(u8 ModeFlag)
{
    u8 allowed;
    ModeData_t mode = *mode_GetMode();
    if(mode.mode == MODE_OPERATE)
    {
        allowed = HC_ALLOWED_MODE_NORMAL;
    }
    else if(mode.mode == MODE_MANUAL)
    {
        allowed = HC_ALLOWED_MODE_MAN;
    }
    else
    {
        MN_DBG_ASSERT(mode.mode == MODE_OOS);
        if(mode.submode == SUBMODE_OOS_FAILSAFE)
        {
            allowed = HC_ALLOWED_MODE_FS;
        }
        else
        {
            allowed = HC_ALLOWED_MODE_OOS;
        }
    }
    return (ModeFlag & allowed) != 0;
}
#endif

/**
\brief sets an error if wrong mode

ModeAllowed=0 means all modes, ModeAllowed=1 means manual or OOS
*/
//static bool_t hart_CheckMode(devmode_t ModeAllowed)
//{
//    const ModeData_t* pMode;
//
//    pMode = mode_GetMode();
//    if(pMode->mode > ModeAllowed)
//    {
//        ///must be in OOS mode for this command
//        HART_ERROR_RETURN__(HART_WRONG_MODE);
//        return true;
//    }
//    return false;
//}
s8_least hart_CheckMode(u8 ModeFlag)
{
    u8 HartError = HART_NO_COMMAND_SPECIFIC_ERRORS;

#ifdef OLD_DEVMODE
    if(!hart_TestMode(ModeFlag))
#else
    devmode_t mode;
    mode = mode_GetMode();
    mode = mode_GetEffectiveMode(mode);

    if( (HC_MODE_BITMASK(mode) & ModeFlag) == 0U)
#endif
    {
        ///not allowed in this mode
        HartError = HART_WRONG_MODE;
    }

    //if factory command, only allow if enabled
    if( ((ModeFlag&HC_FACTORY_COMMAND) != 0)
        && !error_IsFault(FAULT_FACTORYMODE))
    {
        ///not allowed in this mode
        HartError = COMMAND_NOT_IMPLEMENTED;
    }

    return HartError;
}

//================vv Top-level envelopes for subcommands vv===============
s8_least hartcmd_ResetToFactoryCalibrations(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
s8_least hartcmd_ReadUserTrim(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
//================^^ Top-level envelopes for subcommands ^^===============


//----------------------- Stolen from the trunk -------------------------
typedef struct BufferCache_t
{
    u8 BufferId;
    u8 Tag;
    diag_t cache[NELEMT(Rsp_LosslesslyReadDataBuffer_t, BufferDataLong)];
    u8 length;
    u16 CheckWord;
} BufferCache_t;

static BufferCache_t BufferCache =
{
    .BufferId = 0x80,
    .CheckWord = (u16)(CRC_SEED + 0x80),
};

/**
\brief Reads data from the circular diagnostic data buffer with losless retries
*/
s8_least hartcmd_LosslesslyReadDataBuffer(const u8 *src, u8 *dst)
{
    s8_least ret;
    const Req_LosslesslyReadDataBuffer_t *s = (const void *)src;
    Rsp_LosslesslyReadDataBuffer_t *d = (void *)dst;

    u8 bufid_cmd = util_GetU8(s->BufferId[0]);
    u8 bufid = bufid_cmd & 0x7fU;
    u8 tag = util_GetU8(s->BufferReadTag[0]);

    if(bufid != bufid_cmd)
    {
        //Reset the read session by convention
        storeMemberInt(&BufferCache, BufferId, bufid);
        storeMemberInt(&BufferCache, Tag, tag);
        ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR; //by convention
    }
    else
    {
        Struct_Test(BufferCache_t, &BufferCache);

        if(bufid == BufferCache.BufferId)
        {
            //buffer is correct; new or retry?
            if(tag == (BufferCache.Tag + 1))
            {
                //new request; fill the cache
                BufferCache.Tag = tag;
                BufferCache.length = (u8)buffer_GetDataFromXDiagnosticBuffer(bufid, NELEM(BufferCache.cache), BufferCache.cache);
                STRUCT_CLOSE(BufferCache_t, &BufferCache);
            }
            //Send the data from cache
            if(tag == BufferCache.Tag)
            {
                util_PutU8(d->BufferReadTag[0], tag);
                util_PutU8(d->BufferReadLength[0], BufferCache.length);
                for(u8_least ix=0; ix < NELEM(BufferCache.cache); ix++)
                {
                    util_PutU16(d->BufferDataLong[ix], (u16)BufferCache.cache[ix]);
                }
                ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
            }
            else
            {
                ret = HART_INVALID_DATA;
            }
        }
        else
        {
            //wrong buffer
            ret = HART_INVALID_DATA;
        }
    }

    return ret;
}

//----------------------- End Stolen from the trunk -------------------------

/*lint +esym(613,src,dst) restore pointers checking
*/

/* This line marks the end of the source */
