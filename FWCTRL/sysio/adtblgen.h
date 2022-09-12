/*
Copyright 2011 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup ADTable  A/D sequence table module
\brief A/D sensor sequence table module
*/
/**
    \file adtblgen.h
    \brief A/D sensor sequence table generator macros

    CPU: Any

    OWNER: AK

    \ingroup ADTable
*/
#ifndef ADTABLGEN_H_
#define ADTABLGEN_H_
/*
    The A/D conversion tables.  Fast channels must occur first
    followed by slow channels, if any.  There must be at least
    one fast channel.  A list may contain only fast channels

    END_SEQ_ONE     Last fast channel in the list
    END_SEQ_TWO     Use for each slow channel.
    END_OF_SEQ      Use for the last channel in the list.  Note that the last
                    channel is implicitly a slow channel.

    N.B. Since table length affects Cycle task execution, care should be taken when
    constructing tables that might affect such things as sample rate.

USAGE:
static? const u8 name?[] =
{
    ADTABLE(FAST_CHANNELS(  comma_separated_list_of_fast_channels),
            NO_ADCYCLES_or_comma_separated_list_of_slow_channels
                )
};


*/
CONST_ASSERT((END_SEQ_TWO & (END_SEQ_TWO - 1U)) == 0U);

#define ARGLIST(...) __VA_ARGS__ //A means to pass a list to a macro as a single parameter

/* We don't yet use it
#define ARGCOUNT(...) sizeof((u8[]){__VA_ARGS__})
*/

#define NO_ADCYCLES (END_SEQ_TWO+END_SEQ_ONE)
/** This macro, identical to ARGLIST, is a means of passing a list of fast channels
to the ADTABLE macro (see below)
*/
#define FAST_CHANNELS(...) __VA_ARGS__ //A means to pass a list to a macro as a single parameter

//lint -esym(750 755,ADCYCLE_*) OK if not referenced
/** THESE HELPER MACROS SHOULD NOT BE USED DIRECTLY
The ADCYCLE_x family of macros create an expanded list of all channels as follows:
all fast channels, first slow channel, marker, all fast channels, second slow channels, marker, etc.
*/
#define ADCYCLE_1(FAST, a, ...) FAST, a, __VA_ARGS__ END_SEQ_TWO
#define ADCYCLE_2(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_1(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_3(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_2(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_4(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_3(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_5(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_4(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_6(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_5(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_7(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_6(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_8(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_7(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_9(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_8(ARGLIST(FAST), __VA_ARGS__)
#define ADCYCLE_10(FAST, a, ...) ADCYCLE_1(ARGLIST(FAST), a), ADCYCLE_9(ARGLIST(FAST), __VA_ARGS__)
/* Continue as needed...
*/

/**  THIS HELPER MACRO SHOULD NOT BE USED DIRECTLY
A common wrapper for ADCYCLE_x macros;
n must be a literal number that matches the actual number of slow channels, except that
if n=0, a single parameter can be anything, like IGNORE_ME.
If n is wrong, compilation error will result
*/
#define ADCYCLE(FAST, n, ...) CAT(ADCYCLE_, n) (ARGLIST(FAST), __VA_ARGS__)

/** Creates an expanded A/D channel list as a byte array with the following format:
- Number of A/D runs to complete the whole sequence
- All fast channels
- First slow channel
- Stop marker
- All fast channels
- Second slow channel
- Stop marker
...
- All fast channels
- Last slow channel
- Stop-and-Reset marker which is greater than stop marker
*/
#define ADTABLE_1(FAST, n, ...) \
        n, \
        ADCYCLE(ARGLIST(FAST), n, __VA_ARGS__) + END_SEQ_ONE,

#define COUNT(...) SELECT_POSITION_N_OF(__VA_ARGS__,LISTN())
#define SELECT_POSITION_N_OF(...) SELECT_POSITION_N(__VA_ARGS__)
#define SELECT_POSITION_N(dummy0,dummy1,dummy2,dummy3,dummy4,dummy5,dummy6,dummy7,dummy8,dummy9,x,...) x
#define LISTN() 10,9,8,7,6,5,4,3,2,1,0



#define ADTABLE(FAST, ...) ADTABLE_1(ARGLIST(FAST), COUNT(__VA_ARGS__), __VA_ARGS__)

#endif //ADTABLGEN_H_
/* This line marks the end of the source */
