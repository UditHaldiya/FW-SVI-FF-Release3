#include "armtypes.h"
#include "mnadvcalc.h"
static const  u16 pFK_1 = 0x5AA5u;
static const  u16 pFK_2 = 0xA55Au;
//static u32 sAdvancedBuffer[PARA_ADV_DWORD];

/* \brief calculate the first 32 bytes of the arrays which is used to calculate
    the userkey.
   \param in:
        no
   \return:
        no
*/
static u16 calcFrst(size_t len, const u8 *buf, u16 FK)
{
    u16 Frst = FK;
    u8  uTempData;
	u8 i;
	u16 xDvcId;
	u16 DvcId;
    for (i = 0; i < len; i++)
    {
        uTempData = buf[i];
        xDvcId = uTempData ^ 0xAAU;
        DvcId = uTempData & 0xFFU;
        if (i % 2 != 0)
        {
            Frst += DvcId;
            DvcId = (u16)(DvcId << 7);
            Frst += DvcId;
            DvcId = (u16)(DvcId << 4);
            Frst += DvcId;
        }
        else
        {
            Frst += xDvcId;
            xDvcId = (u16)(xDvcId << 7);
            Frst += xDvcId;
            xDvcId = (u16)(xDvcId << 4);
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
static u16 calcScnd(size_t len, const u8 *buf, u16 FK)
{
    u16 Scnd = FK;
    u8  uTempData;
	u8_least i;
	u16 xDvcId;
	u16 DvcId;
    //for (u8 i = PARA_ADV_REDWRT_BYTES; i < CAL_TOTAL_DEVICE_ID_BYTES; i++)
    for (i = 0; i < len; i++)
    {
        uTempData = buf[i];
        xDvcId = uTempData ^ 0xAAU;
        DvcId=uTempData & 0xFFU;
        if (i % 2 != 0)
        {
            Scnd += DvcId;
            xDvcId = (u16)(xDvcId << 7);
            Scnd += xDvcId;
            DvcId = (u16)(DvcId << 11);
            Scnd += DvcId;
        } else
        {
            Scnd += xDvcId;
            DvcId = (u16)(DvcId << 7);
            Scnd += DvcId;
            xDvcId = (u16)(xDvcId << 11);
            Scnd += xDvcId;
        }
    }
    return Scnd;
}

/* \brief compare the input FFKey is euqal to the UserKey or not.
    \param in:
        pDeviceId: advanced parameter read/write table and the device id together
        FFKey    £ºadvanced parameter sub-checksum parmater
    \return:
        true or false, if the FFKey is equal to the UserKey which is calculated
        by pDevicedId and algrithom.
*/
u32 mn_CalcAdvanced(size_t advkey_sz, const u8 *advkey, size_t devid_sz, const u8 *dev_id)
{
    u16 ClcltdKeyFrst = calcFrst(advkey_sz, advkey, pFK_1);
    u16 ClcltdKeyScnd = calcScnd(devid_sz, dev_id, pFK_2);
    return ClcltdKeyScnd + (((u32)ClcltdKeyFrst) << 16);
}


