#include "mnwrap.h"
#include "hartdef7.h"
#include "hartfunc7.h"
#include "hart.h"
#include "mncbdefs.h"
#include "bufutils.h"

/**
    \brief universal command 0 of HART revision 7
           Note:                            VERY WRONG; JUST TO MAKE IT LINK
*/
s8_least Hart7Cmd_ReadUniqueIdentifier(const void *src, void *dst, HartCmdParams_t *params)
{
    Rsp7_ReadUniqueIdentifier_t *d = (void *)dst;
    const HartData_t * tmpptr;
    ConfigurationChanged_t conch;
    stUniqueIdentifier_t *temp = (void *)(d->stUniqueIdentifier);

    util_PutU8(temp->DummyDelimiter[0], (u8)254);
    util_PutU8(temp->MfgID[0], (u8)MNCB_MANUFACTURER_ID);
    util_PutU8(temp->DeviceType[0], VerString[hart_GetHartData()->hart_version].ManufacturerDeviceCode);
    util_PutU8(temp->Preambles[0], (u8)NBR_REQUEST_PREAM);
    util_PutU8(temp->CmdRev[0], (u8)UNIV_CMD_REV7);
    util_PutU8(temp->DevRev[0], (u8)TRANS_SPEC_REV7);
    util_PutU8(temp->SWRev[0], (u8)SOFT_REV7);
    util_PutU8(temp->HWRevandSignalingcode[0], (u8)MNCB_HARDWARE_REVISION);
    util_PutU8(temp->Flags[0], (u8)FLAG_REV7);

    tmpptr = hart_GetHartData();
    util_PutU8Array(temp->DeviceID[0], sizeof(tmpptr->device_id)/sizeof(u8), tmpptr->device_id);

    util_PutU8(temp->nPreambles[0], (u8)NBR_RESPONSE_PREAM7);   //default value should be 5, check ANNEX B. Default configuration table
    //util_PutU8(temp->nVariables[0], hart_GetNumberOfDeviceVars());
    util_PutU8(temp->nVariables[0], 42);
    //Return argument ignored because data returned in input parameter conch.
    (void)nvram_GetConfigurationChanged(&conch);
    util_PutU16(temp->Count[0], (u16)conch.ConfigurationChangeCounter);
    //util_PutU8(temp->ExtStatus[0], hart_ExtendedDeviceStatus());
    util_PutU8(temp->ExtStatus[0], 17);

    UNUSED_OK(src);
    UNUSED_OK(params);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
