/*
Copyright 2019 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnerrorif.h
    \brief MN error processing interface API

    CPU: Any

    OWNER: AK
*/
#ifndef MNERRORIF_H_
#define MNERRORIF_H_

typedef enum xdX_t
{
    xdX_pos,
    xdX_pressure,
    xdX_temperature,
    xdX_total
} xdX_t; //< index type for accumulation of xd_errors

typedef struct MnAlertsEtc_t
{
    u32 block_err_desc_1;
    u32 block_alert_map; //TB alerts bitmap as in Vlad'd TB parameters
    u16 rb_block_err; //copied/apportioned to RB.BLOCK_ERR
    u16 recom_action;
    u8 xd_error[xdX_total];
    u8 priority; //of the most severe diag
} MnAlertsEtc_t;

extern const MnAlertsEtc_t *MnAlert_GetAlertsEtc(MnAlertsEtc_t *dst);

MN_INLINE u16 mnptb_GetTBRecommendedAction(void)
{
    return MnAlert_GetAlertsEtc(NULL)->recom_action;
}

#endif //MNERRORIF_H_
