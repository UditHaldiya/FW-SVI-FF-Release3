#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mnwrap.h"
#include "advmap.h"
#include "bitutils.h"

static void errexit(const char *a1, const char *a2)
{
	printf("%s%s\n", (a1==NULL)?"":a1, (a2==NULL)?"":a2);
	exit(EXIT_FAILURE);
}
/** \brief Reads a non-negative number converted
\param arg - a pointer to buffer with a number presumed decimal
\return value or negative on error
*/
static long readint(const char *arg)
{
	char *endp;
	long ret = strtol(arg, &endp, 10);
	if(*endp != 0)
	{
		errexit("Invalid param:", arg);
	}
	return ret;
}

#define DEVICE_ID_BYTES 32
u8 *mfgid = NULL;


u32 CalcKeyR2(size_t advkey_sz, const u8 *advkey, const u8 *dev_id)
{
    size_t len = strlen(dev_id);
	if(len > DEVICE_ID_BYTES)
	{
		errexit("Device Id string too large:", dev_id);
	}
	
	u8 id[DEVICE_ID_BYTES] = "0047450008______________________";
	if (mfgid != NULL)
	{
		memcpy(id, mfgid, 6);
	}
	memcpy(id+DEVICE_ID_BYTES-len, dev_id, len);

    return mn_CalcAdvanced(advkey_sz, advkey, DEVICE_ID_BYTES, id);
}

void adv_EmitKeyR2(size_t advkey_sz, const u8 *advkey, const u8 *dev_id)
{
	u32 key = CalcKeyR2(advkey_sz, advkey, dev_id);
	printf("Id %s: %08X\n", dev_id, key);
}

#define PARA_ADV_READ_DWORD          5u
#define PARA_ADV_READ_BYTES          (PARA_ADV_READ_DWORD * sizeof(u32))
#define PARA_ADV_RWF_DWORD           12u
#define PARA_ADV_REDWRT_BYTES        (PARA_ADV_RWF_DWORD *sizeof(u32))

#define MN_DIAG_FUNC_IDX_OF_AD       10u

#define ADV_BITMAP_SIZE_R2 (12*sizeof(u32)) //Number of bytes before key in TB:ADVANCED
#define ADV_R_BITMAP_SIZE_R2 (5*sizeof(u32)) //Number of bytes in Read bitmap
#define ADV_W_BITMAP_SIZE_R2 ADV_R_BITMAP_SIZE_R2 //Number of bytes in Write bitmap
#define ADV_R_BITMAP_START_R2 0
#define ADV_W_BITMAP_START_R2 (ADV_R_BITMAP_START_R2 + ADV_R_BITMAP_SIZE_R2)
#define ADV_D_BITMAP_START_R2 (ADV_W_BITMAP_START_R2 + ADV_W_BITMAP_SIZE_R2)
#define ADV_D_BITMAP_SIZE_R2 (ADV_BITMAP_SIZE_R2 - ADV_D_BITMAP_START_R2)

typedef enum skind_t
{
	s_unknown,
	s_diag,
	s_read,
	s_write
} skind_t;

s32 adv_Index(size_t len, const char * const try[], const char *tomatch)
{
	s32 i;
	for(i=0; i<len; i++)
	{
		if(try[i]!=NULL && strcmp(try[i], tomatch)==0)
		{
			return i;
		}
	}
	return -1;
}

extern const u8 adv_diag_lock[];
extern const u8 nelem_adv_diag_lock;

int adv_CreateBitmap(dict_t *dict, u8 bitmap[ADV_BITMAP_SIZE_R2])
{
	skind_t state = s_unknown;
	for(ulong i=0; i<dict->wcount; i++)
	{
		if(strcmp(dict->w[i].word, "[End]") == 0)
		{
			break;
		}
		else if(strcmp(dict->w[i].word, "[Diagnostics]") == 0)
		{
			state = s_diag;
		}
		else if(strcmp(dict->w[i].word, "[Read]") == 0)
		{
			state = s_read;
		}
		else if(strcmp(dict->w[i].word, "[Write]") == 0)
		{
			state = s_write;
		}
		else if(dict->w[i].word[0]==';' || dict->w[i].word[0]==' ')
		{
			//Nothing: just skip the line
		}
		else
		{
			s32 x;
			size_t start;
			size_t size;
			int ignore;
			ignore=0;
			switch(state)
			{
				case s_diag:
				{
					
					x = adv_Index(diagnames_size, diagnames, dict->w[i].word);
					if(x > nelem_adv_diag_lock)
					{
						x=-1;
					}
					else
					{
						if(x>0)
						{
					        x = adv_diag_lock[x]; //Map to victoria's bits
					        if(x==9+1)
					        {
					        	errexit(dict->w[i].word, " mapped to bit 9 incompatible with previous keys");
							}
					        if(x>0)
					        {
					        	--x;
							}
							else 
							{
								ignore = 1;
							}
						}
						else
						{
							ignore = 1;
						}
					}
					start = ADV_D_BITMAP_START_R2;
					size = ADV_D_BITMAP_SIZE_R2;
					break;
				}
				case s_read:
				{
					
					x = adv_Index(paramnames_size, paramnames, dict->w[i].word);
					start = ADV_R_BITMAP_START_R2;
					size = ADV_R_BITMAP_SIZE_R2;
					break;
				}
				case s_write:
				{
					
					x = adv_Index(paramnames_size, paramnames, dict->w[i].word);
					start = ADV_W_BITMAP_START_R2;
					size = ADV_W_BITMAP_SIZE_R2;
					break;
				}
				default:
					errexit("Unknown context at:", dict->w[i].word);
			}
			
			if(x >= size*CHAR_BIT)
			{
				errexit("Index too large for:", dict->w[i].word);
			}
			else if(x<0)
			{
				errexit("Param not found:", dict->w[i].word);
			}
			else
			{
				if(ignore==0)
				{
					bitmap[start + BYTENUM(x)] |= BYTEBITMASK(x);
				}
			}
		}
	}
	return 0;
}

void adv_EmitBitmap(size_t len, const void *bitmap)
{
	if(len%sizeof(u32)!=0)
	{
		errexit("Bitmap length must be a multiple of 4", NULL);
	}
	len /=4;
	const unsigned *b = bitmap;
	for(u32 i=0; i<len; i++)
	{
		printf("[%u]=0x%08X\n", i, b[i]);
	}
}

int main(int argc, char *argv[])
{
	dict_t *dict;
	u8 bitmap[ADV_BITMAP_SIZE_R2]={0};
	//Not needed but for regeression testing against GenKey2
	bitmap[ADV_D_BITMAP_START_R2+1] |= 0x02;
	//read command line params
	if (0 == strcmp(argv[1], "-M"))
	{
		mfgid = argv[2];
		argv += 2;
		argc -= 2;
	}
	int err = file2dict(&dict, argv[1], 0);
	if(err==MYERR_OK)
	{
		err = adv_CreateBitmap(dict, bitmap);
	}
	if(err==MYERR_OK)
	{
		adv_EmitBitmap(sizeof(bitmap), bitmap);
		for(int i=2; i<argc; i++)
		{
			adv_EmitKeyR2(sizeof(bitmap), bitmap, argv[i]);
		}
	}
	if(err != MYERR_OK)
	{
		errexit("Usage: ", "[-M <mfg-id>] definition-file dev-id1 dev-id2 ...");
	}
	return 0;
}

