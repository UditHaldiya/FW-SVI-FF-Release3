/*
Copyright 2012-2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_actuator_3.h
    \brief API for parameter ACTUATOR_3

    CPU: Any

    OWNER: AK
*/
#ifndef MN_ACTUATOR_3_H_
#define MN_ACTUATOR_3_H_

#include <ptb.h>
#include "mnhart2ff.h"

#define SINGLE_ACTING       1u
#define DOUBLE_ACTING       0u

extern fferr_t ReadActuator3(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf);
extern fferr_t WriteActuator3(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA *p_write, void* snd_buf, void* rcv_buf);

typedef struct Act3Min_t
{
    USIGN16 shutoff_dp;
    USIGN8 hand_wheel;
    USIGN8 relay_type;
    FLOAT supply_prs_max;
    FLOAT prs_control_hi;
    FLOAT prs_control_lo;
    u16 CheckWord;
} Act3Min_t; //! Keeps pressure in internal representation (which happens to be psi)

extern ErrorCode_t act3min_Set(const Act3Min_t *src);
extern const Act3Min_t *act3min_Get(Act3Min_t *dst);
UNTYPEACC(act3min_Set, act3min_Get);


#endif // MN_ACTUATOR_3_H_

