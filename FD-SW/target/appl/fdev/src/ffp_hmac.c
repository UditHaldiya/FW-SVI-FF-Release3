/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA-256 hashing algorithm.
              SHA-256 is one of the three algorithms in the SHA2
              specification. The others, SHA-384 and SHA-512, are not
              offered in this implementation.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/


/*************************** HEADER FILES ***************************/
#include <string.h>
#if defined(__ICCARM__)
#include <base.h>
#endif
#include "ffp_hmac.h"

/** \brief create a padded 64-byte iPad or oPad key

	\param key - array of bytes for key
	\param klen - length of key
	\param padv - pad (xor) value (0x36 or 0x5c)
*/
static void HMAC_PadKey(const BYTE key[], DWORD klen, BYTE padv)
{
	DWORD ix = 0;

	while (ix < klen)
	{
		BYTE tc = key[ix++] ^ padv;
		sha256_update(&tc, 1);
	}
	while (ix < BLOCKSZ)
	{
		sha256_update(&padv, 1);
		ix++;
	}
}

/** \brief apply the HMAC algorithm

  	\param key - array of bytes for key
	\param klen - length of key
	\[aram [padv = pad (xor) value (0x36 or 0x5c)

*/
void HMAC_HashKeyText(const BYTE key[], DWORD klen, BYTE exor, const BYTE str[], DWORD len, BYTE rslt[])
{
	sha256_init();
	HMAC_PadKey(key, klen, exor);
	sha256_update(str, len);
	sha256_final(rslt);
}

void HMAC_HashKeyOnly(const BYTE * key, DWORD klen, BYTE exor)
{
	sha256_init();
	HMAC_PadKey(key, klen, exor);
}

// end of source
