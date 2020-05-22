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
//#include <string.h>
#if defined(__ICCARM__)
#include "mnwrap.h"
#endif
#include "sha256.h"

/****************************** MACROS ******************************/
//#define ROTLEFT(a,b)  (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))


#define CH(x,y,z)  (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)  (ROTRIGHT(x,2)  ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x)  (ROTRIGHT(x,6)  ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7)  ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

typedef struct {
	u8 data[BLOCKSZ];
	DWORD datalen;
	u64 bitlen;
	DWORD state[SHA256_BLOCK_SIZE / 4];
} SHA256_CTX;

static SHA256_CTX ctxa;
static SHA256_CTX * const ctx = &ctxa;
static DWORD m[BLOCKSZ];

/**************************** VARIABLES *****************************/
static const DWORD k[BLOCKSZ] =
{
	0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
	0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
	0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
	0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
	0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
	0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
	0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
	0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
};

/*********************** FUNCTION DEFINITIONS ***********************/
static void sha256_transform(const u8 data[])
{
	DWORD a, b, c, d, e, f, g, h, i, j = 0, t1, t2;//, m[64];

	for (i = 0; i < 16; ++i)
	{
		m[i] = ((DWORD)data[j] << 24) | ((DWORD)data[j + 1] << 16) | ((DWORD)data[j + 2] << 8) | ((DWORD)data[j + 3]);
		j += 4;
	}
	for ( ; i < BLOCKSZ; ++i)
	{
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	}
	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < BLOCKSZ; ++i)
	{
		t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

static const DWORD init[] =
{
	0x6a09e667u,
	0xbb67ae85u,
	0x3c6ef372u,
	0xa54ff53au,
	0x510e527fu,
	0x9b05688cu,
	0x1f83d9abu,
	0x5be0cd19u
};

void sha256_init(void)
{
	ctx->datalen  = 0;
	ctx->bitlen   = 0ULL;
#if 0
	ctx->state[0] = 0x6a09e667u;
	ctx->state[1] = 0xbb67ae85u;
	ctx->state[2] = 0x3c6ef372u;
	ctx->state[3] = 0xa54ff53au;
	ctx->state[4] = 0x510e527fu;
	ctx->state[5] = 0x9b05688cu;
	ctx->state[6] = 0x1f83d9abu;
	ctx->state[7] = 0x5be0cd19u;
#else
	mn_memcpy(ctx->state, init, sizeof(init));
#endif
}

void sha256_update(const u8 data[], size_t len)
{
	DWORD i;

	for (i = 0; i < len; ++i)
	{
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == BLOCKSZ)
		{
			sha256_transform(ctx->data);
			ctx->bitlen += 512ULL;
			ctx->datalen = 0;
		}
	}
}

#define ERP 0

/** \brief Finalize the hash by padding the buffer and adding the bitlength of the
	message.  If less than 56 bytes in the buffer, it the padding and bitlength
	can be added and hashed in one operation.  Otherwise the current buffer is padded
	and hashed, then a second buffer is padded with 56 nuls and the bitlength
	added.

	\param hash - an array of HASHSZ bytes where the hash will be placed
*/
void sha256_final(u8 hash[])
{
	DWORD i;
#if ERP
	DWORD j;
	u8 *xx;
#endif

	i = ctx->datalen;

	// Pad whatever data is left in the buffer.
	if (ctx->datalen < 56)
	{
		ctx->data[i++] = 0x80;			// marker
		while (i < 56)
		{
			ctx->data[i++] = 0x00;		// fill with nuls
		}
	}
	else
	{
		ctx->data[i++] = 0x80;			// marker
		while (i < BLOCKSZ)
		{
			ctx->data[i++] = 0x00;		// fill with nuls
		}
		sha256_transform(ctx->data);	// hash 64 bytes
		memset(ctx->data, 0, 56);		// first 56 bytes of buffer == nuls
	}

	// Append to the padding the total message's length in bits and transform.
	ctx->bitlen += (u64)ctx->datalen * 8ULL;
#if !ERP
	ctx->data[63] = (u8)(ctx->bitlen);
	ctx->data[62] = (u8)(ctx->bitlen >> 8);
	ctx->data[61] = (u8)(ctx->bitlen >> 16);
	ctx->data[60] = (u8)(ctx->bitlen >> 24);
	ctx->data[59] = (u8)(ctx->bitlen >> 32);
	ctx->data[58] = (u8)(ctx->bitlen >> 40);
	ctx->data[57] = (u8)(ctx->bitlen >> 48);
	ctx->data[56] = (u8)(ctx->bitlen >> 56);
#else
    xx = (u8*)&ctx->bitlen + 7;

    for (i = 56; i < BLOCKSZ; i++)
    {
        ctx->data[i] = *xx--;
    }
#endif

	sha256_transform(ctx->data);

	// Since this implementation uses little endian byte ordering and SHA uses big endian,
	// reverse all the bytes when copying the final state to the output hash.
#if 1
	for (i = 0; i < 4; ++i)
	{
		hash[i]      = (u8)(ctx->state[0] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 4]  = (u8)(ctx->state[1] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 8]  = (u8)(ctx->state[2] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 12] = (u8)(ctx->state[3] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 16] = (u8)(ctx->state[4] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 20] = (u8)(ctx->state[5] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 24] = (u8)(ctx->state[6] >> (24 - i * 8)) /*& 0x000000ffu*/;
		hash[i + 28] = (u8)(ctx->state[7] >> (24 - i * 8)) /*& 0x000000ffu*/;
	}
#else
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 4; ++i)
		{
			hash[i + (j * 4)]  = (ctx->state[j] >> (24 - i * 8)) & 0x000000ff;
		}
	}
#endif
}

// end of source
