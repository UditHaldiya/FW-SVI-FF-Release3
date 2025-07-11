/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/
#ifndef SHA256_H_
#define SHA256_H_
/*************************** HEADER FILES ***************************/


/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef u32  DWORD;            // 32-bit word, change to "long" for 16-bit machines

#define BLOCKSZ		    64

#ifdef _MSC_VER
typedef unsigned __int64 u64;
#endif


/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(void);
void sha256_update( const u8 data[], size_t len);
void sha256_final(u8 hash[]);

#endif   // SHA256_H
