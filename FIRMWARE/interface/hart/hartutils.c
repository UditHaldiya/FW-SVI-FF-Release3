/*
Copyright 2009-2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup mnhartcmd HART Command Module
\brief Generic part of HART layer link to application

*/
/**
    \file hartutils.c
    \brief Misc. HART helpers

    CPU: Any

    OWNER: AK

    \ingroup mnhartcmd
*/
#include "mnwrap.h"
#include "hartfunc.h"
#include "hart.h"
#include "faultpublic.h"
#include "errcodes.h"
#include "nvram.h"
//#include "hart_faultrept.h"
#if defined(HART_REV_7)
#include "hartdef7.h"
#include "bufutils.h"
#endif

#define NO_MASKS

#ifndef NO_MASKS

#if defined(HART_REV_5) || defined(HART_REV_6)
static u8 msa5(HartMaster_t masterFlag)
{
    UNUSED_OK(masterFlag);
    //Check how the faults are doing, the old inline way
    const u8 *enable_masks = error_GetFaultCodeMasks(NULL)->hideInStatusBit;
    u8 rsp2;
    if(error_IsAnyFaultExt(enable_masks))
    {
        rsp2 = HART_ADDL_STATUS;
    }
    else
    {
        rsp2 = 0;
    }
    return rsp2;
}
#endif

#if defined(HART_REV_7)
typedef struct Ack_t
{
    Req7_ReadAdditionalDeviceStatus_t Request;
    u8 rsp2_additional_status_available;
    u16 CheckWord;
} Ack_t;

static Ack_t Ack[2] =
{
    [HartMaster_Secondary] =
    {
        .Request =
        {
            .Cmd48RqstStruct =
            {
                [0] = {0},
            },
            .endmark = 0,
        },
        .rsp2_additional_status_available = 0U,
        .CheckWord = CRC_SEED,
    },
    [HartMaster_Primary] =
    {
        .Request =
        {
            .Cmd48RqstStruct =
            {
                [0] = {0},
            },
            .endmark = 0,
        },
        .rsp2_additional_status_available = 0U,
        .CheckWord = CRC_SEED,
    },
};

static void msa_Compute(u8_least hm, const FaultCodeData_t *pFaultCodeData, const FaultCodeMasks_t *pFaultCodeMasks)
{
    u8 msa = 0;
    const Cmd48RqstStruct_t *p = (const void *)Ack[hm].Request.Cmd48RqstStruct;
    u8_least bytenum;
    MN_ENTER_CRITICAL();
        for(bytenum = 0; bytenum<NELEM(p->DevSpecificStatus); bytenum++)
        {
            if(util_GetU8(p->DevSpecificStatus[bytenum]) != (pFaultCodeData->fcode[bytenum] & pFaultCodeMasks->enabled[bytenum]))
            {
                msa = HART_ADDL_STATUS;
                //? break;
            }
        }
        for(; bytenum<MIN(NELEM(p->DevSpecificStatus)+NELEM(p->DevSpecificStatusExtend), NELEM(pFaultCodeData->fcode)); bytenum++)
        {
            if(util_GetU8(p->DevSpecificStatusExtend[bytenum-NELEM(p->DevSpecificStatus)]) != (pFaultCodeData->fcode[bytenum] & pFaultCodeMasks->enabled[bytenum]))
            {
                msa = HART_ADDL_STATUS;
                //? break;
            }
        }
        storeMemberInt(&Ack[hm], rsp2_additional_status_available, msa);
    MN_EXIT_CRITICAL();
}

/** \brief Periodic service for monitoring "more status available"

Useful in HART 7 only,
    We check whether the following is true
    1. First segment matches current faults, and
    2. Second segemnt matches current faults
    If true, we clear rsp2_additional_status_available, otherwise, set it

For deterministic behavior, it is handy to run this in cycle task or in an
empty-ish slot of control task (DLT). Even at 120 ms it is more than enough for HART
*/
void msa_AckPatrol(void)
{
    const FaultCodeData_t *pFaultCodeData = error_GetFaultCodeData(NULL);
    const FaultCodeMasks_t *pFaultCodeMasks = error_GetFaultCodeMasks(NULL);
    for(u8_least hm=0; hm<NELEM(Ack); hm++) //Once for each of the two possible HART Masters
    {
        msa_Compute(hm, pFaultCodeData, pFaultCodeMasks);
    }
}

/** \brief Implements HART 7 command 48 faults acknowledgement for MSA
(more status available) bit in rsp2
\param s - a pointer to command 48 request
\param hm - HART master index
*/
void msa_Acknowledge(const Req7_ReadAdditionalDeviceStatus_t *s, HartMaster_t hm)
{
    if(s==NULL)
    {
        MN_ENTER_CRITICAL();
            mn_memset(&Ack[hm], 0, MN_OFFSETOF(Ack_t, CheckWord));
            Ack[hm].CheckWord = CRC_SEED;
        MN_EXIT_CRITICAL();
    }
    else
    {
        MN_ENTER_CRITICAL();
            Ack[hm].Request = *s;
            Ack[hm].rsp2_additional_status_available = 0;
            STRUCT_CLOSE(Ack_t, &Ack[hm]);
        MN_EXIT_CRITICAL();
    }
}

static u8 msa7(HartMaster_t masterFlag)
{
    return Ack[masterFlag].rsp2_additional_status_available;
}
#endif

typedef u8 msafunc_t(HartMaster_t masterFlag);
static msafunc_t *const msa_table[] =
{
#ifdef HART_REV_5
    [HART_REV_5] = msa5,
#endif
#ifdef HART_REV_6
    [HART_REV_6] = msa5, //same function
#endif
#ifdef HART_REV_7
    [HART_REV_7] = msa7,
#endif
};

#endif //NO_MASKS

/** \brief Prepares response's status byte 2

    \param[in] masterFlag - true = primary, false = secondary
    \return the status byte
*/
u8 hart_makeResponseFlags(HartMaster_t masterFlag, u8_least hart_version)
{
#ifndef NO_MASKS
    if(hart_version >= NELEM(msa_table))
    {
        //should never ever happen but regularize
        hart_version = HART_REV_OLDEST;
    }

    u8 rsp2 = msa_table[hart_version](masterFlag);
#else
    UNUSED_OK(hart_version);
    u8 rsp2 = 0U;
#endif

    if(nvram_GetConfigurationChangedFlag(masterFlag==HartMaster_Primary))
    {
        rsp2 |= HART_CONFIG_CHANGED;
    }

    if(error_IsAnyFailsafeFault()) // *not* failsafe mode!
    {
        rsp2 |= HART_DEVICE_FAILED;
    }

    return hart_StatusPlugin(rsp2);
}

/** \brief convert error codes to hart codes
*   \param[in]  error code
*   \param[out]
*   \return   hart code
*/
s8_least err2hart(ErrorCode_t err)
{
    s8_least ret;
    switch (err)
    {
    //success
    case ERR_OK:
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
        break;

    case ERR_NOT_SUPPORTED:
    case ERR_INVALID_PARAMETER:
    case ERR_LOGF_OPENMODE://A read operation attempted on a log open for writes or vice versa
	//Those below are mostly out of spec but match existing implementation; subject to improvement
	//Since they belong to device-specific commands, no panic necessary
    case ERR_CHARACT_INVALID_ARG:
    case ERR_CHARACT_ERROR:
    case ERR_CHARACT_CUSTOM_SIZE:
    case ERR_CHARACT_CUSTOM_ORDER:
    case ERR_CAL_SG_OUT_OF_RANGE: //DLT team to review
    case ERR_CAL_VALUE:
    case ERR_DIAG_POSITION_RANGE:
    case ERR_DIAG_LIMITS_ON:
    case ERR_DIAG_LOW_COST_LIM:
    case ERR_DIAG_NO_PRESSURE:
    case ERR_DIAG_TYPE_NOT_AVAILABLE:
    case ERR_COMP_INVALID_TABLE:
        ret = HART_INVALID_SELECTION;
        break;

    case ERR_HART_NO_DATA_AVAILABLE:
		ret = HART_NO_DATA;
		break;
    case ERR_CNFG_PROTECTED_LIMITS:
    case ERR_CAL_INVALID_PROCEDURE_CALL:
		ret = HART_ACCESS_RESTRICTED;
		break;

	case ERR_CAL_NOT_AT_STOPS:
		ret = HART_FIND_STOPS_FAILED;
		break;
    case ERR_CAL_MOUNTING_MISMATCH: //DLT team to review
    case ERR_PROCESS_START:
		ret = HART_CANNOT_START_PROCESS;
		break;

    case ERR_LOGF_INVALID: //wrong log file - a different log is open
    case ERR_LOGF_PREVIOUS_ERROR: //an error existed when an operation was attempted
		ret = HART_LOGF_ERROR;
		break;
	case ERR_DP_DEVICE_BUSY: //Internal only but OK to map to busy
        ret = HART_BUSY;
        break;

#ifdef OLD_DEVMODE
        //mode checks
    case ERR_MODE_ILLEGAL_SUBMODE:
        ret = HART_WRONG_MODE;
        break;
#else
		//used in factory mode or internally; should not be seen in the field
#endif
    case ERR_HART_RV_LOW_TOO_HIGH:
         ret = HART_LOWERRANGE_TOOHIGH;
        break;
    case ERR_HART_RV_LOW_TOO_LOW:
        ret = HART_LOWERRANGE_TOOLOW;
        break;
    case ERR_HART_RV_HIGH_TOO_HIGH:
        ret = HART_UPPERRANGE_TOOHIGH;
        break;
    case ERR_HART_RV_HIGH_TOO_LOW:
        ret = HART_UPPERRANGE_TOOLOW;
        break;
    case ERR_HART_RV_SPAN_LOW:
        ret = HART_INVALID_SPAN;
        break;
    case ERR_CNFG_SIGNAL_RANGE:
    case ERR_CNFG_PRESSURE_RANGE:
    case ERR_CNFG_STOPS_RANGE:
		ret = HART_RV_SPAN_INVALID;
		break;
    case  ERR_HART_RV_BOTH_OOR:
        ret = HART_RV_BOTH_OOR;
        break;
    case ERR_MODE_CANNOT_CHANGE:
        ret = HART_WRONG_MODE;
        break;
    case ERR_BIOS_PARAM:
	case ERR_LOGF_LENGTH:
    case ERR_UPPERLIM:
        ret =  HART_PASSED_PARAMETER_TOO_LARGE;
        break;
    case ERR_LOWERLIM:
        ret = HART_PASSED_PARAMETER_TOO_SMALL;
        break;

    case ERR_CAL_PROCESS_CANCELED: //in projects where used, it must be (and is) purely internal
    default:
        ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR;
        break;
    }
    return ret;
}

#if 0 //Optimization attempt for the future
/** \brief Common routine for getting cmd 0 response by tag (short or long)
\param src - a pointer to request as in command processing function
\param dst - a ponter to response as in command processing function
\param params - a pointer to command parameters as in command processing function
\param tag - a pointer to the tag to compare against
\param taglen - the length of the tag
\param function - a pointer to the appropriate implementation of command 0
\return HART completion code
*/
s8_least hart_ReadUniqIdByTag(const u8 *src, void *dst, HartCmdParams_t *params,
                              const u8 *tag, size_t taglen,
                              s8_least (*func)(const void *src, void *dst, HartCmdParams_t *params))
{
    if(params != NULL)
    {
        //HART 6+
        if (params->req_data_len < taglen)
        {
            Hart_DropFrame();
            return HART_NO_COMMAND_SPECIFIC_ERRORS;
        }
    }

    u8_least i = 0;
    while ((i < taglen) && (tag[i] == src[i]))
    {
        i++;
    }
    s8_least ret;
    if (i == taglen)
    {
      // it is command 0
       ret = func(src, dst, params);
    }
    else
    {
        Hart_DropFrame();
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
}
#endif //Optimization attempt

/* This line marks the end of the source */
