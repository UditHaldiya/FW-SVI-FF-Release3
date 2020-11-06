// AdvancedDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "V2_Editions.h"

namespace SviFF_Edition
{
	// Returns the custom key
	unsigned int cV2_Editions::Custom(char *FnBtmp, int loFnBtmp, char *DvcId, int loDvcId)
	{
		static const  unsigned short  FK_1 = 0x5AA5u;
		static const  unsigned short  FK_2 = 0xA55Au;

		unsigned char	DeviceIDStrt[32] = { 0x30, 0x30, 0x34, 0x37, 0x34, 0x35,	//	6
			0x30, 0x30, 0x30, 0x38,				//	10	
			0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,		//20
			0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,		//30
			0x5F, 0x5F };
		const int DvcStrtCntr = 24;	// number of chars used in the begining of the Device ID
		int	DvcIDCntr;
		for (DvcIDCntr = 0; DvcIDCntr < loDvcId; DvcIDCntr++)
		{
			DeviceIDStrt[DvcIDCntr + DvcStrtCntr] = DvcId[DvcIDCntr];
		}
		unsigned int hClcRslt = calcFrst(loFnBtmp, (unsigned char *)FnBtmp, FK_1);
		unsigned int lClcRslt = calcScnd(sizeof(DeviceIDStrt), DeviceIDStrt, FK_2);
		unsigned int UserKey = hClcRslt << 16 ;
		UserKey = UserKey + lClcRslt;
		//	UserKey += ((u32)ClcltdKeyFrst) << 16;
		return UserKey;
	}
	// Returns the key for Advanced Edition
	unsigned int cV2_Editions::Advanced(char *DvcId, int loDvcId)
	{
		unsigned int AdvArry[] = { 
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF, 0,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF, 0,
			0x1FFF, 0 };
		unsigned int uiAdvRtrn = Custom((char *)AdvArry, sizeof(AdvArry), DvcId, loDvcId);
		return uiAdvRtrn;
	}
	

	// Returns the key for standard Edition
	unsigned int cV2_Editions::Standard(char *DvcId, int loDvcId)
	{
		unsigned int AdvArry[] = { 
			0x7FFFFFFF, 0x180BFE00,	0xFFFFFFF8,	0xFFFFFF,	0x0,
			0x7FFFFFFF,	0x180BFE00,	0xFFFFFFF8,	0xFFFFFF,	0x0,
			0x1FFF,		0x0 };
		unsigned int uiAdvRtrn = Custom((char *)AdvArry, sizeof(AdvArry), DvcId, loDvcId);
		return uiAdvRtrn;

	}
	unsigned short  cV2_Editions::calcFrst(size_t len, const unsigned char  *buf, unsigned short  FK)
	{
		unsigned short  Frst = FK;
		unsigned char   uTempData;
		unsigned char  i;
		unsigned short  xDvcId;
		unsigned short  DvcId;
		for (i = 0; i < len; i++)
		{
			uTempData = buf[i];
			xDvcId = uTempData ^ 0xAAU;
			DvcId = uTempData & 0xFFU;
			if (i % 2 != 0)
			{
				Frst += DvcId;
				DvcId = (unsigned short)(DvcId << 7);
				Frst += DvcId;
				DvcId = (unsigned short)(DvcId << 4);
				Frst += DvcId;
			}
			else
			{
				Frst += xDvcId;
				xDvcId = (unsigned short)(xDvcId << 7);
				Frst += xDvcId;
				xDvcId = (unsigned short)(xDvcId << 4);
				Frst += xDvcId;
			}

		}
		return Frst;
	}

	/* \brief calculate the last 32 bytes of the arrays which is used to calculate
	the userkey.
	\param in:
	no
	\return:
	no
	*/
	unsigned short  cV2_Editions::calcScnd(size_t len, const unsigned char  *buf, unsigned short  FK)
	{
		unsigned short  Scnd = FK;
		unsigned char   uTempData;
		unsigned char  i;
		unsigned short  xDvcId;
		unsigned short  DvcId;
		//for (unsigned char  i = PARA_ADV_REDWRT_BYTES; i < CAL_TOTAL_DEVICE_ID_BYTES; i++)
		for (i = 0; i < len; i++)
		{
			uTempData = buf[i];
			xDvcId = uTempData ^ 0xAAU;
			DvcId = uTempData & 0xFFU;
			if (i % 2 != 0)
			{
				Scnd += DvcId;
				xDvcId = (unsigned short)(xDvcId << 7);
				Scnd += xDvcId;
				DvcId = (unsigned short)(DvcId << 11);
				Scnd += DvcId;
			}
			else
			{
				Scnd += xDvcId;
				DvcId = (unsigned short)(DvcId << 7);
				Scnd += DvcId;
				xDvcId = (unsigned short)(xDvcId << 11);
				Scnd += xDvcId;
			}
		}
		return Scnd;
	}

}

