/*
Copyright 2019 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_11_12.c
    \brief Translation between layouts 11 and 12 (expanded data hog trigger)

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFAP_xlate_11_12.h"

//lint -esym(754, *_t11::*) -esym(754, *_t12::*) Types are for sizes here

CONST_ASSERT(FFAP_NVRAM_ENTRIES_VER_11==FFAP_NVRAM_ENTRIES_VER_12);
CONST_ASSERT(FFAP_NVRAMID_DhogTriggerConf_11==FFAP_NVRAMID_DhogTriggerConf_12);

enum
{
    DhogCommDisable_t11,
    DhogCommEnable_t11
} ;

enum
{
    DhogPvDisable_t11,
    DhogPvEnableBelow_t11,
    DhogPvEnableAbove_t11
} ;

enum
{
    DhogDiDisable_t11,
    DhogDiEnableOpen_t11,
    DhogDiEnableClosed_t11
} ;

typedef struct DhogTriggerConf_t11
{
    s8 DhogCommTrigger;
    s8 DhogDiTrigger;
    s8 DhogPvTrigger;
    s16 pvthreshold;
    u16 CheckWord;
} DhogTriggerConf_t11;

enum
{
    trig_sp_deviation_t12,
    trig_pos_deviation_t12,
    trig_pres_deviation_t12,
    trig_total_t12
};

typedef struct FilterConf_t12
{
    u8 Shift; //!< For exponential forgetting with 2**-Shift rate
} FilterConf_t12; //! Filter configuration type

typedef struct DhogTriggerConf_t12
{
    s16 pvthreshold[Xends]; //!< AI (aka PV) threshold
    s16 DeviationThresh[trig_total_t12];
    u16 BinaryOptions; //
    FilterConf_t12 FilterConf; //common for all deviation triggers (for now)
    u16 CheckWord;
} DhogTriggerConf_t12;

//lint -esym(751 641, DhogBinaryOptionsBits_t12) unused typedef, enum on RHS of <<
//NOTE: Commented out entries don't participate in translation
typedef enum DhogBinaryOptionsBits_t12
{
    DhogBO_Extrn_t12 = 0, //!< Enable external trigger (via HART)
    //DhogBO_TBAlerts_t12 = 1, //!< are we honoring DHOG_TB_ALERT_TRIGGER if comes by IPC?
    //DhogBO_PosDeviation_t12 = 4,
    //DhogBO_PresDeviation_t12 = 5,
    //DhogBO_SpDeviation_t12 = 6,
    DhogBO_DiOpen_t12 = 7,
    DhogBO_DiClosed_t12 = 8,
    DhogBO_PvBelow_t12 = 9,
    DhogBO_PvAbove_t12 = 10
    //, DhogBO_PvBetween_t12 = 11
} DhogBinaryOptionsBits_t12;


/** \A trivial contraction translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlatedn_12_11(u8 *dst, const u8 *src, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_11; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_DhogTriggerConf_11:
            {
                DhogTriggerConf_t11 *d = (DhogTriggerConf_t11 *)(void *)(&dst[FFAP_nvram_map_11[id].offset]);
                const DhogTriggerConf_t12 *s = (const DhogTriggerConf_t12 *)(const void *)(&dst[FFAP_nvram_map_12[id].offset]);
                u16 binopt = s->BinaryOptions;
                s8 opt = DhogCommDisable_t11;
                if( (binopt & (1U<<DhogBO_Extrn_t12)) != 0)
                {
                    opt = DhogCommEnable_t11;
                }
                d->DhogCommTrigger = opt;

                opt = DhogDiDisable_t11;
                if( (binopt & (1U<<DhogBO_DiOpen_t12)) != 0)
                {
                    opt = DhogDiEnableOpen_t11;
                }
                if( (binopt & (1U<<DhogBO_DiClosed_t12)) != 0)
                {
                    opt = DhogDiEnableClosed_t11;
                }
                d->DhogDiTrigger = opt;

                opt = DhogPvDisable_t11;
                if( (binopt & (1U<<DhogBO_PvBelow_t12)) != 0)
                {
                    opt = DhogPvEnableBelow_t11;
                }
                if( (binopt & (1U<<DhogBO_PvAbove_t12)) != 0)
                {
                    opt = DhogPvEnableAbove_t11;
                }
                d->DhogDiTrigger = opt;


                d->pvthreshold = s->pvthreshold[Xlow]; //what else can wedo?
                STRUCT_CLOSE(DhogTriggerConf_t11, d);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_11[id].offset, src + FFAP_nvram_map_12[id].offset, FFAP_nvram_map_12[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}

#define STD_FROM_PSI_12(x) ((s16)(((cdouble_t)(12000-0)*(x))/(60.0-0.0)))  //converts psi to counts
//lint -emacro(506, PRE_ROUND_12) const bool
#define PRE_ROUND_12(x) ((x)+(((x)>=0.0)?0.5:-0.5)) //! ubiquitous compile-time conversion
#define STD_FROM_PERCENT_12(x) (\
        (s16)\
        (\
            PRE_ROUND_12((cdouble_t)(16384-0)*(x)\
            /(100.0-0.0)))\
                            )  //converts % to counts

/** \A trivial expansion translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlateup_11_12(const u8 *src, u8 *dst, void (*func)(void))
{
    //Common part of layout
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_11; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_DhogTriggerConf_11:
            {
                DhogTriggerConf_t12 *d = (DhogTriggerConf_t12 *)(void *)(&dst[FFAP_nvram_map_12[id].offset]);
                const DhogTriggerConf_t11 *s = (const DhogTriggerConf_t11 *)(const void *)(&dst[FFAP_nvram_map_11[id].offset]);
                s8 opt = s->DhogCommTrigger;
                u16 binopt = 0U;
                if(opt == DhogCommEnable_t11)
                {
                    binopt |= (1U<<DhogBO_Extrn_t12);
                }

                opt = s->DhogDiTrigger;
                if(opt == DhogDiEnableOpen_t11)
                {
                    binopt |= (1U<<DhogBO_DiOpen_t12);
                }
                if(opt == DhogDiEnableClosed_t11)
                {
                    binopt |= (1U<<DhogBO_DiClosed_t12);
                }

                opt = s->DhogPvTrigger;
                if(opt == DhogPvEnableBelow_t11)
                {
                    binopt |= (1U<<DhogBO_PvBelow_t12);
                }
                if(opt == DhogPvEnableAbove_t11)
                {
                    binopt |= (1U<<DhogBO_PvAbove_t12);
                }


                d->BinaryOptions = binopt;
                d->pvthreshold[Xlow] = s->pvthreshold;
                d->pvthreshold[Xhi] = s->pvthreshold;
                //default init
                d->DeviationThresh[trig_sp_deviation_t12] = STD_FROM_PERCENT_12(0.5);
                d->DeviationThresh[trig_pos_deviation_t12] = STD_FROM_PERCENT_12(0.5);
                d->DeviationThresh[trig_pres_deviation_t12] = STD_FROM_PSI_12(5.0);
                d->FilterConf.Shift = 6;
                STRUCT_CLOSE(DhogTriggerConf_t11, d);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_12[id].offset, src + FFAP_nvram_map_11[id].offset, FFAP_nvram_map_11[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}


/* This line marks the end of the source */
