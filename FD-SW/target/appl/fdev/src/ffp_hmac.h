/*********************************************************************
* Filename:   ffp_hmac.h
* Author:     Ernie
AK: For the time being, I preserved Ernie's implementation. It may be
subject to EOL because of a duplicate APP-process-friendly utilities\hmac.c
*********************************************************************/
#ifndef FFP_HMAC_H_
#define FFP_HMAC_H_
#include "sha256.h"

/*************************** HEADER FILES ***************************/


/**************************** DATA TYPES ****************************/
#ifdef _MSC_VER
typedef u8  BYTE;             // 8-bit byte
#endif

#define HASHSZ		    32
#define SIGNATURE_SZ    HASHSZ
#define IPAD		    0x36
#define OPAD		    0x5c

#ifdef _MSC_VER
typedef unsigned __int64 longlong;
#else
typedef u64 longlong;
#endif


/*********************** FUNCTION DECLARATIONS **********************/
extern void HMAC_HashKeyText(const BYTE key[], DWORD klen, BYTE exor, const BYTE str[], DWORD len, BYTE rslt[]);
extern void HMAC_HashKeyOnly(const BYTE key[], DWORD klen, BYTE exor);

#endif   // FFP_HMAC_H_
