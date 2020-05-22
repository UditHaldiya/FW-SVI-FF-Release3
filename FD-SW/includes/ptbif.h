/*
Copyright 2020 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ptbif.h
    \brief Misc. interfaces in a truly public header

    CPU: Any

    OWNER: AK
*/
#ifndef PTBIF_H_
#define PTBIF_H_

#include "mnhart2ff.h" //for fferr_t
#include "process.h" //for procresult_t

extern void nvmem_FFP_RestoreFirmwareDefaults(void);
extern fferr_t nvmem_FFP_PreRestoreFirmwareDefaults(void);
extern procresult_t proc_FFP_RestoreFirmwareDefaults(s16 *procdetails);

#endif //PTBIF_H_

