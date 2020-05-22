/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_8_9.c
    \brief Trivial translation between layouts 8 (bank 2) and 9 (same but
            in bank 0 or 1 corresponding to the build)

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFAP_xlate_8_9.h"

#if 0
/** \A trivial translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlateup_8_9(const u8 *src, u8 *dst, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_8; id++)
    {
        mn_memcpy(dst + FFAP_nvram_map_9[id].offset, src + FFAP_nvram_map_8[id].offset, FFAP_nvram_map_8[id].length);
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, cant' we?
        {
            func();
        }
    }
    return ERR_OK;
}

ErrorCode_t FFAP_xlatedn_9_8(u8 *dst, const u8 *src, void (*func)(void))
{
    return FFAP_xlateup_8_9(src, dst, func);
}
#endif //0

#define HART_DATE_LENGTH_8_9 3
#define HART_DESCRIPTOR_LENGTH_8_9 16
#define HART_MESSAGE_LENGTH_8_9 32
#define HART_TAG_LENGTH_8_9 8
#define HART_FINAL_LENGTH_8_9 3
#define HART_ID_LENGTH_8_9 3
typedef u8 pascii_t_8_9; //!< HART-packed ascii: 4 characters in 3 bytes
#define HPACKED_8_9(size) ((3*(size))/4) //!< Hart-packed ascii size

typedef struct HartData_t8
{
    u8 hart_version;
    u8 device_id[HART_ID_LENGTH_8_9];		/* device ID number */
	pascii_t_8_9 message[HPACKED_8_9(HART_MESSAGE_LENGTH_8_9)];			/* message 32 characters , 24 packed*/
	pascii_t_8_9 tag[HPACKED_8_9(HART_TAG_LENGTH_8_9)];			/* tag (8 characters, 6 packed) */
	pascii_t_8_9 descriptor[HPACKED_8_9(HART_DESCRIPTOR_LENGTH_8_9)];	/* descriptor (16 characters, 12 packed) */
	u8 date[HART_DATE_LENGTH_8_9];			/* date */
	u8 finalass_nbr[HART_FINAL_LENGTH_8_9];  	        /* final assembly number */
	u8 transmit_address;	        /* transmitter address */
	u8 nbr_resp_pream;		/* number of response preambles */
	u8 burst_mode_cmd;		/* burst mode command number */
	u8 burst_mode_ctrl;	        /* burst mode control */
    u8 Reserved; //used to be optional LoopCurrentMode; //Per cmd6, it could be none NVRAM variable
	u16 CheckWord;
} HartData_t8;

typedef struct HartData_t9
{
    u8 hart_version;
    u8 device_id[HART_ID_LENGTH_8_9];		/* device ID number */
	pascii_t_8_9 message[HPACKED_8_9(HART_MESSAGE_LENGTH_8_9)];			/* message 32 characters , 24 packed*/
	pascii_t_8_9 tag[HPACKED_8_9(HART_TAG_LENGTH_8_9)];			/* tag (8 characters, 6 packed) */
	pascii_t_8_9 descriptor[HPACKED_8_9(HART_DESCRIPTOR_LENGTH_8_9)];	/* descriptor (16 characters, 12 packed) */
	u8 date[HART_DATE_LENGTH_8_9];			/* date */
	u8 finalass_nbr[HART_FINAL_LENGTH_8_9];  	        /* final assembly number */
	u8 transmit_address;	        /* transmitter address */
	u8 nbr_resp_pream;		/* number of response preambles */
	u8 burst_mode_cmd;		/* burst mode command number */
	u8 burst_mode_ctrl;	        /* burst mode control */
	u16 CheckWord;
} HartData_t9;

CONST_ASSERT(FFAP_NVRAM_ENTRIES_VER_8 == FFAP_NVRAM_ENTRIES_VER_9);
//lint -esym(754, HartData_t9::*) -esym(754, HartData_t8::*) not referenced

/* Change in numeric conversions (TFS:26101) between R2 and R3 requires
adaptation due to range checks
NVRAMID
2 digsp_SetConf
    digitalsp_range[] identical
    DigitalSP_ShedTime_range[] identical
3 digsp_SetData
    digitalsp.setpoint is not checked in R2. Should be at least CLAMPed
4 tempr_SetTemperature is not checked in R2.
5 pres_SetPressureCalData STD_FROM_PSI is identical
6 pos_GetPositionConf
    POS_SCALEDMIN, POS_SCALEDMAX, POS_SCALE_DIFF_MIN identical
7-14 tune_SetPIDData - all integers. P+Padj<0 issue addressed elsewhere in translation
!15 pos_SetErrorLimits
    errband_range R2 81, 32604 | R3 errband_range = 82, 32604
    nearpos_range R2 0, 3276 | R3 0, 3277
    errtime_range identical
!16 control_SetLimits
    tso_limits R2 -8192, 3276 | R3 -8192, 3277
    tco_limits identical
    spposlimits_range identical
    spratelim_range R2 81, 16400 | R3 33, 32765
18 posmon_SetContinuousDiagnostics - no checks
22 control_SetBiasExt - identical BIAS_HIGH_LIMIT
--------------
others identical or N/A
*/

//lint -esym(754, ErrorLimits_t8::*, CtlLimits_t9::*) members don't need to be used in translation

typedef struct ErrorLimits_t8
{
    s16 NearPosition;            //!<  Cutoff for "near closed" in % open
    s16 PositionErrorBand;       //!<  position error band
    s16 PositionTime1;           //!<  position error timeout 1 - warning
    u8 bPosErr1Enable;
    u16 CheckWord;
} ErrorLimits_t8;

CONST_ASSERT(FFAP_NVRAMID_ErrorLimits_8 == FFAP_NVRAMID_ErrorLimits_9);
CONST_ASSERT(FFAP_NVRAMID_CtlLimits_8 == FFAP_NVRAMID_CtlLimits_9);

ErrorCode_t FFAP_xlateup_8_9(const u8 *src, u8 *dst, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_8; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_HartData_8:
            {
                CONST_ASSERT(FFAP_NVRAMID_HartData_8 == FFAP_NVRAMID_HartData_9);
                CONST_ASSERT(MN_OFFSETOF(HartData_t8, burst_mode_ctrl) == MN_OFFSETOF(HartData_t9, burst_mode_ctrl));
                const HartData_t8 *s = (const HartData_t8 *)(const void *)(src + FFAP_nvram_map_8[id].offset);
                HartData_t9 *d = (HartData_t9 *)(void *)(dst + FFAP_nvram_map_9[id].offset);
                mn_memcpy(d, s, MN_OFFSETOF(HartData_t8, burst_mode_ctrl) + sizeof(s->burst_mode_ctrl));
                d->hart_version = 0; //the one and the only HART 5
                STRUCT_CLOSE(HartData_t9, d);
                break;
            }
            case FFAP_NVRAMID_ErrorLimits_8:
            {
                const ErrorLimits_t8 *s = (const ErrorLimits_t8 *)(const void *)(src + FFAP_nvram_map_8[id].offset);
                ErrorLimits_t8 *d = (ErrorLimits_t8 *)(void *)(dst + FFAP_nvram_map_9[id].offset);
                *d = *s;
                d->PositionErrorBand = MAX(d->PositionErrorBand, 82);
                STRUCT_CLOSE(ErrorLimits_t8, d);
                break;
            }
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_9[id].offset, src + FFAP_nvram_map_8[id].offset, FFAP_nvram_map_8[id].length);
                break;
            }
        }
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, can't we?
        {
            func();
        }
    }
    return ERR_OK;
}

typedef struct CtlLimits_t9
{
    u8 EnableTightShutoff[Xends]; //!< Tight shutoff enable flags
    s16 TightShutoff[Xends];       //!< Tight shutoff limits in % open
    u8 EnableSetpointLimit[Xends];   //!< Lower and Upper setpoint limits enable flags
    s16 SetpointLimit[Xends];      //!< Lower and Upper setpoint limit in % open
    u8 EnableSetpointRateLimit[Xends];   //!< Lower and Upper setpoint rate limits enable flags
    s16 SetpointRateLimit[Xends];      //!< Lower and Upper setpoint rate limit in % travel
    u8 Protected;           //!< a flag indicating whether temporary changes are enabled
    u16 CheckWord;
} CtlLimits_t9; //same as 8

#define SP_RATE_LIMIT_LOW_8 81 //INT_PERCENT_OF_RANGE(0.5)
#define SP_RATE_LIMIT_HIGH_8 16400 //INT_PERCENT_OF_RANGE(100.1)

ErrorCode_t FFAP_xlatedn_9_8(u8 *dst, const u8 *src, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_8; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_HartData_8:
            {
                CONST_ASSERT(FFAP_NVRAMID_HartData_8 == FFAP_NVRAMID_HartData_9);
                CONST_ASSERT(MN_OFFSETOF(HartData_t8, burst_mode_ctrl) == MN_OFFSETOF(HartData_t9, burst_mode_ctrl));
                const HartData_t9 *s = (const HartData_t9 *)(const void *)(src + FFAP_nvram_map_9[id].offset);
                HartData_t8 *d = (HartData_t8 *)(void *)(dst + FFAP_nvram_map_8[id].offset);
                mn_memcpy(d, s, MN_OFFSETOF(HartData_t8, burst_mode_ctrl) + sizeof(s->burst_mode_ctrl));
                d->hart_version = 1; //HART 5 even if buggy HART 6 dummy is present
                d->Reserved = 1; //Release1 bug 25488 countermeasure
                d->burst_mode_cmd = 3; //R2-compatible
                d->burst_mode_ctrl = 0; //R2-compatible
                STRUCT_CLOSE(HartData_t8, d);

                break;
            }
            case FFAP_NVRAMID_CtlLimits_8:
            {
                CtlLimits_t9 *d = (void *)(dst + FFAP_nvram_map_8[id].offset);
                const CtlLimits_t9 *s = (const void *)(src + FFAP_nvram_map_9[id].offset);
                *d = *s;
                //Clamp to older narrower limits
                d->SetpointRateLimit[Xlow] = CLAMP(d->SetpointRateLimit[Xlow], SP_RATE_LIMIT_LOW_8, SP_RATE_LIMIT_HIGH_8);
                d->SetpointRateLimit[Xhi] = CLAMP(d->SetpointRateLimit[Xhi], SP_RATE_LIMIT_LOW_8, SP_RATE_LIMIT_HIGH_8);
                d->TightShutoff[Xlow] = MIN(d->TightShutoff[Xlow], 3276);
                STRUCT_CLOSE(CtlLimits_t9, d);
            }
            break;
            case FFAP_NVRAMID_ErrorLimits_8:
            {
                const ErrorLimits_t8 *s = (const ErrorLimits_t8 *)(const void *)(src + FFAP_nvram_map_9[id].offset);
                ErrorLimits_t8 *d = (ErrorLimits_t8 *)(void *)(dst + FFAP_nvram_map_8[id].offset);
                *d = *s;
                d->NearPosition = MIN(d->NearPosition, 3276);
                STRUCT_CLOSE(ErrorLimits_t8, d);
                break;
            }
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_8[id].offset, src + FFAP_nvram_map_9[id].offset, FFAP_nvram_map_8[id].length);
                break;
            }
        }
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, can't we?
        {
            func();
        }
    }
    return ERR_OK;
}


/* This line marks the end of the source */
