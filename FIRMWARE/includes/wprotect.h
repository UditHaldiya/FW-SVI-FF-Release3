/*
Copyright 2010 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file wprotect.h
    \brief SYSIO level API for write protect

    CPU: Any (with standard C compiler)

    OWNER: AK
    \ingroup sysio
*/

#ifndef WPROTECT_H_
#define WPROTECT_H_

#define bios_ReadWriteProtectInput sysio_ReadWriteProtectInput //for legacy compatibility
extern bool_t sysio_ReadWriteProtectInput(void);

extern void wprotect_SetExtLock(bool_t wlock);

#endif //WPROTECT_H_

/* End of the source */
