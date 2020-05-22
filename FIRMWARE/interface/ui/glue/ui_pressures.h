/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_pressures.h
    \brief UI service functions prototypes for pressures support

     CPU: Any

    OWNER: AK

    \ingroup UI
*/
#ifndef UI_PREESURES_H_
#define UI_PREESURES_H_
#include "uidef.h"
#include "pneumatics.h"

extern uivalvar_t *ui_getMainPressure(void);
extern uivalvar_t *ui_getSupplyPressure(void);
extern const void *ui_getPneuParams(void);

#endif //UI_PREESURES_H_
/* This line marks the end of the source */
