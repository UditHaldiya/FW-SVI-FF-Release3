/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file numutils.h
    \brief numeric utilities (interfaces and inlines)

    This file contains prototypes of numeric utilities which are not
TERRIBLY time-critical.
    Time-critical numeric utilities are implemented here as inline functions.
    There is a possibility of an implementation to migrate between numutils.c
(as a normal function) and numutils.h (as an inline function).

    All functions in this file are pure, i.e., without side effects.
    Therefore, early returns are freely employed here.

     CPU: 32-bit (and perhaps smaller-word) CPUs with 2's complement negatives representation

    OWNER: AK

    \ingroup numutils
*/
#ifndef NUMUTILS_H_
#define NUMUTILS_H_
#include "config.h"

//Public API may or may not be used in a particular project
MN_DECLARE_API_FUNC(SInv, SDivByMul, UInv, UDivByMul, SUInv, SDivByUMul, swapEndian32)
MN_DECLARE_API_MACRO(ROR, ROL8, ROR8)

//lint -strong(AJX, ieee754_t)
typedef u32 ieee754_t;
#ifdef MN_INLINE
MN_INLINE u32 secs2hrs(u32 secs)
{
    return secs/3600u; //3600 sec in an hour; the compiler does it by multiplication, as it should
}
//A shim that the compiler optimizes out
MN_INLINE ieee754_t float2ieee(float32 arg)
{
    const void *p = &arg;
    const ieee754_t *q = p;
    return *q;
}
MN_INLINE float32 ieee2float(ieee754_t arg)
{
    const void *p = &arg;
    const float32 *q = p;
    return *q;
}
#endif //MN_INLINE

//Division by multiplication by reciprocal:
/* The pairs are as follows:
- Inv function compute the "reciprocal" of the divisor
- DivByMul function uses the reciprocal to compute the qoutient
DivByMul functions are going to become MN_INLINE later.
The use is whenever there are more than 2 divisions by the
same number or when division happens in a time-critical path and
the divisor can be pre-computed.
*/
//unsigned by unsigned
//MN_DECLARE_API_FUNC(UDivByMul, UInv)
extern u32 UDivByMul(u32 num, u32 inv);
extern u32 UInv(u32 divisor);

//signed by signed
//MN_DECLARE_API_FUNC(SDivByMul, SInv)
extern s32 SDivByMul(s32 num, u32 inv);
extern u32 SInv(s32 divisor);

//signed by unsigned
//MN_DECLARE_API_FUNC(SDivByUMul, SUInv)
extern s32 SDivByUMul(s32 num, u32 inv);
extern u32 SUInv(u32 divisor);


//Same thing, typeless
#define CLAMP(val, lo, hi) (((val)<(lo))?(lo):(((val)>(hi))?(hi):(val)))

#define PRE_ROUND(x) (x) //! control/autotune bisbehave with rounding (non-monotonic response on P)
//lint -emacro(506, PRE_ROUND) constant value Boolean - of course!
//#define PRE_ROUND(x) ((x)+(((x)>=0.0)?0.5:-0.5)) //! ubiquitous compile-time conversion
/* NOTE: There is no cast INTENTIONALLY so as to ensure (by Lint) that there is
no implicit promotion
*/

//float back to int
extern s32 f2i_ScaledConv(float32 f_, u32 scale, u8 downshift);

/** Compatibilty macro - changing the order of arguments */
#define i2f_Scaled(num, scale, downshift) i2f_Scaled__((num), (downshift), (scale))
extern float32 i2f_Scaled__(s32 num, u8_least downshift, u32 scale);


MN_INLINE s32 f2i_Scaled(float32 f, s32 lolim, s32 hilim, u32 scale)
{
    s32 result = f2i_ScaledConv(f, scale, 16);
    return CLAMP(result, lolim, hilim);
}

#define std2f(pos) i2f_Scaled((pos), 1, STANDARD_NUMBITS) //deprecated

//extern u32 MN_API_FUNC(swapEndian32)(u32 x);
extern u32 swapEndian32(u32 x);


#define ROR(x,n) (((x)>>(n))|((x)<<(32-(n))))
//and handy shortcuts
#define ROL8(x) (((x)<<8)|((x)>>24))
#define ROR8(x) (((x)<<24)|((x)>>8)) /**< a macro for rotating a u32 8 bits to the right */

#define ABS(x) ( ((x)<0)?(-(x)):(x) ) //!< typeless macro for absolute value

//-------------- integer scaling -------------------------

/** \brief Check whether a IEEE754 single-precision value is 0 (positive or negative)
*/
MN_INLINE bool_t ieee754_IsZero(ieee754_t val)
{
    return (val & (ieee754_t)0x7fffffff) == (ieee754_t)0U;
}

/** \brief A simple two-side clamping routine
\param val - the value to limit
\param lolim - lower limit
\param hilim - upper limit
\return val saturated on both sides. If lolim>hilim, return is hilim
*/
MN_INLINE s32 limit(s32 val, s32 lolim, s32 hilim)
{
    if(val < lolim)
    {
        val = lolim; /* Legitimate early return: A pure function */
    }
    if(val > hilim)
    {
        val = hilim; /* Legitimate early return: A pure function */
    }
    return val;
}

/**
    \brief Computes arg/(1<<shift)
    The compiler turns this ugly yet compliant code turns in a fairly good
    inline code. In fact, the compiler should translate this expression
    on its own without calling the division function, but it doesn't have
    enough smarts (yet?).
    \param arg - a number to divide
    \param shift - an exponent of the divisor
    \return quotient
*/
MN_INLINE s32 div_by_pwr2(s32 arg, u8 shift)
{
    s32 val = arg;
    u32 uval;
    if(val < 0)
    {
        val = -val;
        uval = (u32)val;
        uval >>= shift;
        val = (s32)uval;
        val = -val;
    }
    else
    {
        uval = (u32)val;
        uval >>= shift;
        val = (s32)uval;
    }
    return val;
}

/**
    \brief Computes (a*x)/(1<<shift) + b
    The compiler turns this ugly yet compliant code turns in a fairly good
    inline code. In fact, the compiler should translate this expression
    on its own without calling the division function, but it doesn't have
    enough smarts (yet?).
    \param a - slope coef
    \param x - variable to scale
    \param b - offset coef
    \param shift - an exponent of the divisor
    \return computed value
*/
MN_INLINE s32 intscale16(s16 a, s16 x, s16 b, u8 shift)
{
    s32 arg = (s32)a * (s32)x;

    arg += b << shift; //lint !e9027 !e701 !e960 left signed shift (701) of sub-integer (960:12.7)

    arg = div_by_pwr2(arg, shift);

    return arg;
}

/** \brief Divide a 64-bit number by a power of 2.
No error is raised if the result doesn't fit
\param arg - dividend
\param shift - exponent of the divisor (must be >0 and <32)
\return the quotient rounded toward zero (just like C99 integer division)
*/
MN_INLINE s32 div64_by_pwr2(s64 arg, u8_least shift)
{
    u32 hi, lo;
    u64 uarg = (u64)(arg);

    hi = (u32)(uarg>>32);

    u32 correction = hi>>31; //sign bit of uarg
    correction = (correction<<shift) - correction;
    uarg += correction; //compensation for difference between shift and division for negatives
    hi = (u32)(uarg>>32);
    lo = (u32)uarg;
    hi <<= (32U-shift);
    lo >>= shift;
    lo |= hi;
    return (s32)lo; //non-portable cast!
}

/* The difference between intscale32() and intscale32r() below is the treatment
of x.500000000 in the intermediate result (conceptually).
intscale32() rounds it toward 0 (i.e. to x.0 in the example)
intscale32r() rounds it away from 0 (i.e. to (x+1).0 for positive x and (x-1).0
for negative x)
intscale32r() is better suited for presentation layer conversions.
Which function is better for internal calculations is TBD.
*/

/**
    \brief Computes (a*x)/(1<<shift) + b (with rounding = truncation toward zero)
    The compiler turns this ugly yet compliant code turns in a fairly good
    inline code. In fact, the compiler should translate this expression
    on its own without calling the division function, but it doesn't have
    enough smarts (yet?).
    \param a - slope coef
    \param x - variable to scale
    \param b - offset coef
    \param shift - an exponent of the divisor
    WARNING: shift **MUST** be between 1 and 31 (inclusive)
    \return computed value
*/
MN_INLINE s32 intscale32(s32 a, s32 x, s32 b, u8 shift)
{
    s64 arg = (s64)a * (s64)x;
    s32 result = div64_by_pwr2(arg, shift);
    result += b;
    return result;
}

/** \brief Divide a 64-bit number by a power of 2.
No error is raised if the result doesn't fit
\param arg - dividend
\param shift - exponent of the divisor (must be >0 and <32)
\return the quotient properly rounded
*/
MN_INLINE s32 div64_by_pwr2r(s64 arg, u8_least shift)
{
    u32 hi, lo;
    u64 uarg = (u64)(arg);

    hi = (u32)(uarg>>32);

    u32 correction = hi>>(31); //sign bit of the product
    correction = (correction<<shift) - correction; //compensation for shift vs division
    correction ^= (1U<<(shift-1U)); //add (for positive) or subtract (for negative) half of last bit's worth for rounding

    uarg += correction;
    hi = (u32)(uarg>>32);
    lo = (u32)uarg;
    hi <<= (32U-shift);
    lo >>= shift;
    lo |= hi;
    return (s32)lo; //non-portable cast!
}

MN_DECLARE_API_FUNC(lsr64)
extern u32 lsr64(u64 val, u32 shift);

/**
    \brief Computes (a*x)/(1<<shift) + b with rounding
    The compiler turns this ugly yet compliant code turns in a fairly good
    inline code. In fact, the compiler should translate this expression
    on its own without calling the division function, but it doesn't have
    enough smarts (yet?).
    \param a - slope coef
    \param x - variable to scale
    \param b - offset coef
    \param shift - an exponent of the divisor
    WARNING: shift **MUST** be between 1 and 31 (inclusive)
    \return computed value
*/
MN_INLINE s32 intscale32r(s32 a, s32 x, s32 b, u8_least shift)
{
    s64 arg = (s64)a * (s64)x;
    s32 result = div64_by_pwr2r(arg, shift);
    result += b;
    return result;
}

/** \brief A wrapper to test that two consecutive increments of a trajectory are in the same direction.
The direction is considered unchanged if either both increments are positive or both are negative.
In particular, transition to or from 0 in any direction is considered a direction change.
The code is hand-crafted. It is not good for machines where negatives are not in 2's complement. Are there any?
\param a - first increment
\param b - next increment
\return false if direction changed; true otherwise.
*/
MN_INLINE bool_t IsSameDirection(s32 a, s32 b)
{
    return ((a^-b)<0) && ((b^-a)<0); //lint !e9027 !e960 CPU-architecture-dependent code
}

#define BITLEN_S32 32U //!< Bit length of s32 type not to drag limits.h around (verified in numutils.c)
/** \brief A wrapper to test that two numbers have the same sign.
Remarkably, the compiler needs help here for efficiency. So, the code is hand-crafted.
It is not good for machines where negatives are not in 2's complement. Are there any?
\param a - first number
\param b - second number
\return false if one number is negative, another non-negative; true otherwise.
*/

MN_INLINE bool_t IsSameSign(s32 a, s32 b)
{
    u32 ua = (u32)a; //C guarantees bit pattern preservation
    u32 ub = (u32)b;
    return ((ua^ub)>>(BITLEN_S32-1U))==0U; //XOR of sign bits (in LSB) == 0?
}
/** \brief A wrapper for Boolean equivalence
\param a - first boolean
\param b - second boolean
\return true iff a and b are equivalent
*/
MN_INLINE bool_t equiv(bool_t a, bool_t b)
{
    return a==b; //lint !e731 Boolean argument to equal/not equal
}

#define bool2int(b) ((b)?1:0) //!< bool-to-int conversion, to be optimized out
#define int2bool(i) (((i)!=0)?true:false) //!< int-to-bool conversion, what the compiler should do implicitly, anyway.

/** \brief A wrapper for division (by shift) by a power of 2
\param numerator - the number to divide
\param denominator_exponent - log(2) of the divisor
\return the quotient
*/
MN_INLINE s32 div32pwr2(s32 numerator, u8 denominator_exponent)
{
    return numerator>>denominator_exponent; //lint !e9027 !e702 !e960 signed shift right
}

/** \brief A wrapper for multiplication (by shift) by a power of 2
\param multiplier - the number to multiply
\param multiplier_exponent - log(2) of the second multiplier
\return the product
*/
MN_INLINE s32 mul32pwr2(s32 multiplier, u8 multiplier_exponent)
{
    return multiplier<<multiplier_exponent; //lint !e9027 !e701 !e960 signed shift left
}

#if 0
/** \brief A wrapper for division (by shift) by a power of 2
\param numerator - the number to divide
\param denominator_exponent - log(2) of the divisor
\return the quotient
*/
MN_INLINE s16 div16pwr2(s16 numerator, u8 denominator_exponent)
{
    return numerator>>denominator_exponent; //lint !e702 !e960 signed shift right
}

/** \brief A wrapper for multiplication (by shift) by a power of 2
\param multiplier - the number to multiply
\param multiplier_exponent - log(2) of the second multiplier
\return the product
*/
MN_INLINE s16 mul16pwr2(s16 multiplier, u8 multiplier_exponent)
{
    return multiplier<<multiplier_exponent; //lint !e701 !e960 signed shift left
}
#endif

//lint -emacro(572,INTLOG) Excessive shift of small constant quantities
//lint -emacro(506,INTLOG) Constant value boolean (specifically, embedded ABS)
/** number of bits to represent x, so 1<<(INTLOG(x)-1)) <= x < 1<<INTLOG(x), x!=0 */
#define INTLOG(x) INTLOG32((u32)(ABS(x)))
#define INTLOG32(x) (((x)<(1UL<<16))?INTLOG16((x)):(INTLOG16((x)>>16) + 16U))
#define INTLOG16(x) (((x)<(1UL<<8))?INTLOG8((x)):(INTLOG8((x)>>8) + 8U))
#define INTLOG8(x) (((x)<(1UL<<4))?INTLOG4((x)):(INTLOG4((x)>>4) + 4U))
#define INTLOG4(x) (((x)<(1UL<<2))?INTLOG2((x)):(INTLOG2((x)>>2) + 2U))
#define INTLOG2(x) (((x)<(1UL<<1))?INTLOG1((x)):(INTLOG1((x)>>1) + 1U))
#define INTLOG1(x) (((x)<(1UL<<0))?0U:1U)

//A runtime counterpart to INTLOG
extern u8_least intlog(u32 x);


#endif //NUMUTILS_H_
