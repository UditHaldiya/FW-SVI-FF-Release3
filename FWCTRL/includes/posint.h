/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file posint.h
    \brief API for System-level data and services related to internal (Hall) position measurement

1. Sensor-specific raw data compensation
2. Sensor-specific linearization

    CPU: Any

    OWNER: AK

    \ingroup sysio
*/

#ifndef POSINT_H_
#define POSINT_H_
#include "tempcomp.h"
#include "position.h"

void posint_Update(ADRaw_t adval);
TEMPCOMP_H_ENTRY32(posint);

LINT_PURE(posint_GetPreLinearized)
extern HardPos_t posint_GetPreLinearized(void);

MN_DECLARE_API_FUNC(posint_GetInstantTempCompParams)
extern void posint_GetInstantTempCompParams(OffsetSpanS32_t *curveseg);

#endif //POSINT_H_
/* This line marks the end of the source */
