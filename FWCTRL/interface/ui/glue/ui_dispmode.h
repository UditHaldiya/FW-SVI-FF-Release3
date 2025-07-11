/**
Copyright 2009 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file ui_dispmode.h
    \brief API to support UI display mode

    CPU: Any

    OWNER: AK

*/
#ifndef UI_DISPMODE_H_
#define UI_DISPMODE_H_

extern void *ui_getDispmode(void); //What to display on line 3 - 0 bar, non-0:
MN_INLINE const void *ui_getCDispmode(void) //Wrapper of What to display on line 3 - 0 bar, non-0
{
    return ui_getDispmode();
}

#endif //UI_DISPMODE_H_
