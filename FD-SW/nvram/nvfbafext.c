#include <softing_base.h>
#include <fbs_api.h>
#include "nvffext.h"
#include "ff2nvram.h"

/** \brief -----------mn wrapper for softing fbs_write_param_loc() --------------
The original has a bug in handling any padding in the object it writes.
This version has a kludgy workaround and a critical section around the call.
NOTE: length in p_write_loc must be >0; this guarantees correct loop termination.
*/
USIGN16 mn_fbs_write_param_loc(T_FBIF_BLOCK_INSTANCE *p_block_instance,
                                      T_FBS_WRITE_PARAM_LOCAL *p_write_loc)
{
    USIGN16 ret;
    do
    {
        osif_disable_all_tasks();
        ret = fbs_write_param_loc(p_block_instance, p_write_loc);
        osif_enable_all_tasks();
        //try removing trail padding length
        if((p_write_loc->length & 3U) == 1U)
        {
            break;
        }
        p_write_loc->length--;
    } while( (ret != E_OK));

    if(ret == E_OK)
    {
        //See if the object has MN storage and commit it if it does
        u8_least rel_idx = p_write_loc->rel_idx;
        if(rel_idx < ff2nvram_map_size)
        {
            nvramId_t nvid = ff2nvram_map[rel_idx].nvramid;
            if(nvid != 0)
            {
                (void)nvmem_RequestWrite(nvid);
            }
        }
    }

    return ret;
}

/** \brief A PTB-specific version of fbs_write_param() which is aware of
non-Softing NVMEM storage and commits (requests commit) in MN NVRAM model
*/
USIGN16 mn_fbs_write_param(T_FBIF_BLOCK_INSTANCE *p_block_instance,
                               T_FBIF_WRITE_DATA *p_write)
{
    USIGN16 ret = fbs_write_param(p_block_instance, p_write);

    if(ret == E_OK)
    {
        //See if the object has MN storage and commit it if it does
        u8_least rel_idx = p_write->rel_idx;
        if(rel_idx < ff2nvram_map_size)
        {
            nvramId_t nvid = ff2nvram_map[rel_idx].nvramid;
            if(nvid != 0)
            {
                (void)nvmem_RequestWrite(nvid);
            }
        }
    }

    return ret;
}

