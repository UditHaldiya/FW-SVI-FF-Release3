/*
Copyright 2004 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup Tempcomp Temperature compensation module
\brief API and implementation of temperature compensation for analog I/O
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_TempComp_Module.doc"> Design document </a><br>
<a href="../../../Doc/TestDocs/utplan_tempcomp_070308.doc"> Unit Test Plan </a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/tempcompHTML.html"> Unit Test Report </a><br>
\endhtmlonly
*/
/**

    \file TempComp.c
    \brief API and functions used in temperature compensation

    CPU: Any

    OWNER: LS
    $Archive: /MNCB/Dev/FIRMWARE/sysio/tempcomp.c $
    $Date: 11/14/11 10:49p $
    $Revision: 114 $
    $Author: Arkkhasin $

    \ingroup Tempcomp
*/
/* (Optional) $History: tempcomp.c $
 *
 * *****************  Version 114  *****************
 * User: Arkkhasin    Date: 11/14/11   Time: 10:49p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Unused headers
 *
 * *****************  Version 113  *****************
 * User: Arkkhasin    Date: 1/12/10    Time: 2:54p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Removed remnants of old code
 *
 * *****************  Version 112  *****************
 * User: Arkkhasin    Date: 4/15/09    Time: 2:26p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Header refactoring (for DLT lint)
 *
 * *****************  Version 111  *****************
 * User: Arkkhasin    Date: 3/29/09    Time: 4:12p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * A few items moved from configure.h to pressures.h and errlimits.h
 *
 * *****************  Version 110  *****************
 * User: Arkkhasin    Date: 2/13/09    Time: 11:45a
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Removed older #error statements - no longer applicable: got mileage
 *
 * *****************  Version 109  *****************
 * User: Sergey Kruss Date: 12/14/08   Time: 11:19a
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Cleaned out commented code only.
 *
 * *****************  Version 108  *****************
 * User: Sergey Kruss Date: 11/10/08   Time: 1:31p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Removed checing of ChannnelShift against the low bowndary (used to be
 * 8). Increased upper boundary for ChannelShift from 14 to 31.
 *
 * This change allows greater values for channelShift for better
 * resolution.
 *
 * *****************  Version 107  *****************
 * User: Arkkhasin    Date: 10/15/08   Time: 6:58p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * A quick oops on the previous version
 *
 * *****************  Version 106  *****************
 * User: Arkkhasin    Date: 10/15/08   Time: 6:27p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * (Temporarily) removed cross-item table consistency test
 *
 * *****************  Version 105  *****************
 * User: Arkkhasin    Date: 10/13/08   Time: 12:27a
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Lint (headers)
 *
 * *****************  Version 104  *****************
 * User: Arkkhasin    Date: 9/11/08    Time: 6:42p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Removed proc_SaveAllComp in favor of selection in cmd 130 cmd Commit
 * RAM
 *
 * *****************  Version 103  *****************
 * User: Arkkhasin    Date: 9/09/08    Time: 11:13a
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Corrected CRC calculation in temperature cals
 *
 * *****************  Version 102  *****************
 * User: Arkkhasin    Date: 9/04/08    Time: 1:43a
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * tcomp_CorrectInput() uses intscale32() again
 *
 * *****************  Version 101  *****************
 * User: Arkkhasin    Date: 7/28/08    Time: 2:14p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Light linting
 * Scope bug fix
 *
 * *****************  Version 100  *****************
 * User: Arkkhasin    Date: 7/19/08    Time: 7:58p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * Tempcomp now supports 32-bit compensation. RAM images are always in
 * 32-bit. For the time being, API exists for both 16- and 32-bit external
 * representation
 * tempr_... now takes sensor id as a parameter
 *
 * *****************  Version 99  *****************
 * User: Arkkhasin    Date: 5/19/08    Time: 3:23p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * New interface for ram_Commit() - now takes a selector function as a
 * parameter
 *
 * *****************  Version 98  *****************
 * User: Arkkhasin    Date: 5/14/08    Time: 5:27p
 * Updated in $/MNCB/Dev/FIRMWARE/sysio
 * (Preliminarily) adapted to new tempcomp
*/
#include "mnwrap.h"
#include "errcodes.h"
#include "numutils.h"
#include "nvram.h"

//data definitions
#include "faultpublic.h"
#include "tempcomp.h"
#include "tempr.h"
#include "oswrap.h"

//temperature compensation table defines
#define TABLE_MAX_SHIFT_VALUE 31u
#define TABLE_INTERPOLATION_SHIFT 16u
#define TABLE_INTERPOLATION_SHIFT_MULTIPLIER ((s32)(1U<<TABLE_INTERPOLATION_SHIFT))
#define TABLE_MIN_COLUMNS 2u



#define DEFAULT_TEMP_AD_0 0U
#define DEFAULT_TEMP_AD_1 65535U

#define TCOMP_SHIFT_DEFAULT 14

/** \brief saves temperature calibration points
  \param[in] src - a pointer to new temperature calibration points struct
  \param tab (unused)
  \param dst - destination struct
  \return an error code
*/
ErrorCode_t tcomp_SetTCalPoints(const TemperatureCalibrationPoints_t *src, const TempComp_t *tab, TemperatureCalibrationPoints_t *dst)
{
    UNUSED_OK(tab); //in the past, messed with crc_of_crcs
    const TemperatureCalibrationPoints_t *pts = src;
    TemperatureCalibrationPoints_t default_pts;
    u8_least i;

    if(pts == NULL)
    {
        //Create (a pointer to) a default table
        default_pts.TemperatureAD[0] = DEFAULT_TEMP_AD_0;
        for(i=1; i<NUMBER_OF_CALIB_POINTS; i++)
        {
            default_pts.TemperatureAD[i] = DEFAULT_TEMP_AD_1;
        }
        default_pts.ActualNumberTempPoints = NUMBER_OF_CALIB_POINTS;
        pts = &default_pts;
    }

    //Test the points we've got
    ErrorCode_t err = ERR_OK;
    u8_least numpoints = pts->ActualNumberTempPoints;
    if((numpoints < TABLE_MIN_COLUMNS) || (numpoints > NUMBER_OF_CALIB_POINTS) )
    {
        /* Legitimate early return: Pre-requisites check */
        err = ERR_COMP_INVALID_TABLE;
    }
    else
    {
        //the temperatures must be in ascending order
        for(i=1; i<numpoints; ++i)
        {
            if(pts->TemperatureAD[i-1U] > pts->TemperatureAD[i])
            {
                err = ERR_COMP_INVALID_TABLE;
                break;
            }
        }
    }

    if(err == ERR_OK)
    {
        Struct_Copy(TemperatureCalibrationPoints_t, dst, pts);
    }
    return err;
}

/** \brief A helper to set a row in the temperature compensation table (32-bit tempcomp)
  \param[in] index - the column index
  \param[in] tccol - the column content to set; NULL means default
  \return ERR_OK if no error
*/
ErrorCode_t tcomp_SetTCalRow32(const TemperatureCalibrationRow32_t *tcrow, TemperatureCalibrationRow32_t *dst)
{
    TemperatureCalibrationRow32_t def_tc;
    if(tcrow == NULL)
    {
        u8_least j;
        OffsetSpanS32_t SpanOffset;
        //AK:TODO: These magic values must guarantee enough sensor failures to go to failsafe.
        //the way it's written is very dangerous w.r.t. fault properties and container sizes.
        //It is safer to have span=0 and offset=out-of-range for each index
        //This is a bug waiting to happen
        SpanOffset.span = 16384;
        SpanOffset.offset = 0;

        //construct default column; shorter than to have endless const arrays
        for(j=0; j<NUMBER_OF_CALIB_POINTS; ++j)
        {
            def_tc.TemperatureCalData[j] = SpanOffset;
        }
        def_tc.ChannelShift = TCOMP_SHIFT_DEFAULT;
        tcrow = &def_tc;
    }

    ErrorCode_t err;
    if( tcrow->ChannelShift > TABLE_MAX_SHIFT_VALUE )
    {
        err = ERR_COMP_INVALID_TABLE;
    }
    else
    {
        Struct_Copy(TemperatureCalibrationRow32_t, dst, tcrow);
        err = ERR_OK;
    }
    return err;
}

/** \brief A helper to set a row in the temperature compensation table (16-bit tempcomp)
NOTE: This is a wrapper around a 32-bit tempcomp in RAM
  \param[in] index - the column index
  \param[in] tccol - the column content to set; NULL means default
  \return ERR_OK if no error
*/
ErrorCode_t tcomp_SetTCalRow(const TemperatureCalibrationRow_t *tcrow, TemperatureCalibrationRow32_t *dst)
{
    const TemperatureCalibrationRow32_t *tcrow32;
    TemperatureCalibrationRow32_t t;
    if(tcrow == NULL)
    {
        tcrow32 = NULL;
    }
    else
    {
        for(u8_least i=0; i<NUMBER_OF_CALIB_POINTS; i++)
        {
           t.TemperatureCalData[i].span = tcrow->TemperatureCalData[i].span;
           t.TemperatureCalData[i].offset = tcrow->TemperatureCalData[i].offset;
        }
        t.ChannelShift = tcrow->ChannelShift;
        tcrow32 = &t;
    }
    return tcomp_SetTCalRow32(tcrow32, dst);
}

/** \brief A helper to get a row from the temperature compensation table (16-bit tempcomp)
NOTE: This is a wrapper around a 32-bit tempcomp in RAM
NOTE: A NULL destination will cause an error indicator of a NULL returned
  \param[out] dst - a pointer to the recipient struct (16-bit)
  \param[in] tcrow - a pointer to the source struct (32-bit)
  \return dst
*/
const void *tcomp_GetTCalRow(TemperatureCalibrationRow_t *dst, const TemperatureCalibrationRow32_t *tcrow)
{
    if(dst != NULL)
    {
        mn_memset(dst, 0, sizeof(*dst));
        for(u8_least i=0; i<NUMBER_OF_CALIB_POINTS; i++)
        {
            //casts are OK since *tcrow came via 16-bit API so it is effectively 16-bit
           dst->TemperatureCalData[i].span = (s16)tcrow->TemperatureCalData[i].span;
           dst->TemperatureCalData[i].offset = (s16)tcrow->TemperatureCalData[i].offset;
        }
        dst->ChannelShift = tcrow->ChannelShift;
        STRUCT_CLOSE(TemperatureCalibrationRow_t, dst);
    }
    return dst;
}

/** \brief A helper to get a row from the temperature compensation table (32-bit tempcomp)
  \param[out] dst - a pointer to the recipient struct (32-bit)
  \param[in] tcrow - a pointer to the source struct (32-bit)
  \return tcrow
*/
const void *tcomp_GetTCalRow32(TemperatureCalibrationRow32_t *dst, const TemperatureCalibrationRow32_t *tcrow)
{
    return STRUCT_GET(tcrow, dst);
}

/** \brief Utility to convert A/D reading to a temperature-corrected value in internal units
\param input - raw A/D value
\param rtdata - temperature correction state for the channel
\param tcorr - temperature correction limits for the channel
\return converted value
*/
tcorr_t tcomp_CorrectInput(s32 input, TemprCorrRTData_t *rtdata, const TemprCorrConfData_t *tcorr)
{
    s32 CompensatedValue, newval;
    s32 a, b;
    u8 downshift;
    s8_least ErrCount;

    MN_ENTER_CRITICAL();
        a = rtdata->curveseg.span;
        b = rtdata->curveseg.offset;
        downshift = rtdata->downshift;
        ErrCount = rtdata->ErrCount;
    MN_EXIT_CRITICAL();

    CompensatedValue = intscale32(a, input, b, downshift);

    newval = CLAMP(CompensatedValue, tcorr->AllowedValue[Xlow], tcorr->AllowedValue[Xhi]);
    if(newval != CompensatedValue)
    {
        /* The value was clamped, and so it is invalid. Set a fault and indicate
        the error with the return value
        */
        if(++ErrCount >=tcorr->ErrLimit)
        {
            error_SetFault(tcorr->fcode);
            ErrCount = tcorr->ErrLimit;
        }
    }
    else
    {
        /* Got a good value */
        if(--ErrCount <= 0)
        {
            ErrCount = 0;
        }
    }
    rtdata->ErrCount = (s8)ErrCount; //valid cast - we are in range

    return (tcorr_t)newval; //valid cast - we are in range
}

/** \brief A computation helper worth keeping separate until we bury 16 bits for good
*/
static void recompute(s32 interpol, s32 xo, s32 xs, s32 bo, s32 bs, TemprCorrRTData_t *dst, u8 ChannelShift)
{
    u8 shift = TABLE_INTERPOLATION_SHIFT;
#if 1
    s32 span = intscale32(interpol, xs, bs, shift);
    s32 offset = intscale32(interpol, xo, bo, shift);
    MN_ENTER_CRITICAL();
        dst->curveseg.span = span;
        dst->curveseg.offset = offset;
        dst->downshift = ChannelShift; // init/refresh the cached value
    MN_EXIT_CRITICAL();
#else
    OffsetSpanS32_t curveseg;
    curveseg.span = intscale32(interpol, xs, bs, shift);
    curveseg.offset = intscale32(interpol, xo, bo, shift);
    MN_ENTER_CRITICAL();
        dst->downshift = ChannelShift; // init/refresh the cached value
        dst->curveseg = curveseg;
    MN_EXIT_CRITICAL();
#endif
}

#if 0
/** \brief Utility to perform span/offset interpolation for a channel
\param tindex - temperature interpolation index [of the left end of the segment]
\param[in] interpol - temperature segment interpolation coefficient (slope)
\param trow - channel's temperature calibrations
\param dst - runtime state to update
*/
void tcomp_ComputeOffsetSpan(u8_least tindex, s32 interpol, const TemperatureCalibrationRow_t *trow, TemprCorrRTData_t *dst)
{
    s32 xs, xo, bs, bo;

    //interpolate the span
    bs = trow->TemperatureCalData[tindex].span;
    xs = trow->TemperatureCalData[tindex+1U].span - bs;


    //interpolate the offset
    bo = trow->TemperatureCalData[tindex].offset;
    xo = trow->TemperatureCalData[tindex+1U].offset - bo;

    Struct_Test(TemperatureCalibrationRow_t, trow);
    recompute(interpol, xo, xs, bo, bs, dst, trow->ChannelShift);
}
#endif

void tcomp_ComputeOffsetSpan32(u8_least tindex, s32 interpol, const TemperatureCalibrationRow32_t *trow, TemprCorrRTData_t *dst)
{
    s32 xs, xo, bs, bo;

    //interpolate the span
    bs = trow->TemperatureCalData[tindex].span;
    xs = trow->TemperatureCalData[tindex+1U].span - bs;


    //interpolate the offset
    bo = trow->TemperatureCalData[tindex].offset;
    xo = trow->TemperatureCalData[tindex+1U].offset - bo;

    Struct_Test(TemperatureCalibrationRow32_t, trow);
    recompute(interpol, xo, xs, bo, bs, dst, trow->ChannelShift);
}



/** \brief computes the interpolated span/offsets at a temperature for each channel
  \param[in] Temperature - the new temperature
\param
*/
void tempr_ComputeTemperatureCompensation(void)
{
    s32 interpol;
    u8_least tindex;

    const TempComp_t *const *ppTempComp = TempComp;
    while(*ppTempComp != NULL)
    {
        const TempComp_t *pTempComp = *ppTempComp;
        ADRaw_t t = pTempComp->GetRawTemp();
        const TemperatureCalibrationPoints_t *pts = nvmem_GetItemById(NULL, pTempComp->ptsId);
        Struct_Test(TemperatureCalibrationPoints_t, pts);
        u8_least tindex_lim = pts->ActualNumberTempPoints-2U;
        tindex = *pTempComp->tindex;

        //Compute the segment and the interpolation factor
        if(tindex > tindex_lim)
        {
            tindex = tindex_lim/2U; //repair a potentially wrong base
        }

        if(pts->TemperatureAD[tindex] < t)
        {
            //going forward
            interpol = TABLE_INTERPOLATION_SHIFT_MULTIPLIER;
            while(tindex < tindex_lim)
            {
                if(pts->TemperatureAD[tindex+1U] > t)
                {
                    break;
                }
                else
                {
                    ++tindex;
                }
            }
        }
        else
        {
            //going backward
            interpol = 0;
            while(tindex != 0u)
            {
                if(pts->TemperatureAD[tindex] > t)
                {
                    --tindex;
                }
                else
                {
                    break;
                }
            }
        }
        *pTempComp->tindex = (u8)tindex;

        if((tindex==0U) && (pts->TemperatureAD[tindex] > t))
        {
            //nothing interpol = 0;
        }
        else if((tindex==tindex_lim) && (pts->TemperatureAD[tindex+1U] < t))
        {
            //greater than the largest - set interpolation to 1 to use the last span/offset
            //nothing interpol = TABLE_INTERPOLATION_SHIFT_MULTIPLIER;
        }
        else if(pts->TemperatureAD[tindex]==pts->TemperatureAD[tindex+1U])
        {
            //nothing: don't divide by 0
        }
        else
        {
            //AK:TODO: Make it suitable for 32-bit tempcomp!
            interpol = (TABLE_INTERPOLATION_SHIFT_MULTIPLIER
                * (t - pts->TemperatureAD[tindex]))
                / (pts->TemperatureAD[tindex+1U] - pts->TemperatureAD[tindex]);
        }

        //compute the span and offset for each channel
        u8_least numchannels = pTempComp->numchannels;
        const TCompAccess_t *TAccess = pTempComp->TAccess;
        u8_least Channel;
        for(Channel=0; Channel<numchannels; Channel++)
        {
            TAccess[Channel].TComputePoint(tindex, interpol);
        }
        ppTempComp++;
    }
}

/* end of source file */
//TEMPCOMP_H_ENTRY32(tamr);
//TEMPCOMP_C_ENTRY32(tamr);
