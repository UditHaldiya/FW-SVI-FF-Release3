/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup mncbcomp MNCB computer definitions
\brief Basic framework with native types abstraction
*/
/**
    \file mnbasetypes.h
    \brief Wrappers for compiler- and library-dependent facilities

    This header is just a hull. The actual wrapping is done in
    innerwrap.h.

    This header is a wrapper of mnwrap.h because the (Softing version of)
    gcc chokes on mnwrap.h (Not standard-compliant)

    CPU: ARM family (because of armtypes.h); IAR compiler (inarm.h)

    \ingroup mncbcomp
*/

#ifndef MNBASETYPES_H_
#define MNBASETYPES_H_

//Enable all native types for Softing code; rely on Lint to detect using them
#define MN_TYPE_ENABLE_CHAR
#define MN_TYPE_ENABLE_SHORT
#define MN_TYPE_ENABLE_INT
#define MN_TYPE_ENABLE_UNSIGNED
#define MN_TYPE_ENABLE_LONG
#define MN_TYPE_ENABLE_FLOAT
#define MN_TYPE_ENABLE_DOUBLE

#include "mnwrap.h"

#endif //MNBASETYPES_H_
