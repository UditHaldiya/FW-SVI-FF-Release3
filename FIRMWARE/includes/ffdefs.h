#ifndef FFDEFS_H_
#define FFDEFS_H_

#include "lcd.h"

#define FF_TAG_MAX_LEN                       (32u)

//lint -emacro(943, FF_TAG_DEF) MISRA3 allows this init
#define FF_TAG_DEF {0}

#define FF_TAG_WR_MAX_BLOCK_NUM              (2u)
#define FF_DEVICE_TAG_LEN                    (32u)
#define FF_DEVICE_TAG_WR_MAX_BLOCK_NUM       (2u)
#define FF_DEVICE_ID_LEN                     (32u)
#define FF_DEVICE_ID_WR_MAX_BLOCK_NUM        (2u)

//---------------------------------------------------
// Fault State
// FAULT_STATE, SET_FSTATE, CLR_FSTATE
//not used #define FF_FAULT_STATE_CLEAR                    (1u)
//not used #define FF_FAULT_STATE_ACTIVE                   (2u)

//not used #define FF_SET_FSTATE_OFF                       (1u)
//not used #define FF_SET_FSTATE_SET                       (2u)
//not used  #define isSetFstate_DEFINED(x)                  ((x == FF_SET_FSTATE_OFF) || (x == FF_SET_FSTATE_SET))

//not used #define FF_CLR_FSTATE_OFF                       (1u)
//not used #define FF_CLR_FSTATE_CLR                       (2u)
//not used #define isClrFstate_DEFINED(x)                  ((x == FF_CLR_FSTATE_OFF) || (x == FF_CLR_FSTATE_CLR))

#define FF_BLK_ERR_NOERR                        0

#define FLOAT_STRING_LEN        NUMBER_OF_DIGITS_PER_LINE

//lint -emacro(943, FLOAT_STRING_INIT) Misra3-compatible init
#define FLOAT_STRING_INIT       {0}

// Definition for Resource Block RESTART value
//not used  #define IPC_RESTART_PROCESSOR       (4u)

//not used #define IPC_RESTART_VALUE_MIN   1
//not used #define IPC_RESTART_VALUE_MAX   12


typedef struct ffDataFloat_t
{
    u8  value[8]; //!< Float value already in string representation, NOT 0-terminated
    u8  status;
    //u16 CheckWord; //!< Probably for the future
} ffDataFloat_t;

typedef struct ffDataDiscrete_t
{
    s16 value;
    u8  status;
    //u16 CheckWord; //!< Probably for the future
} ffDataDiscrete_t;

#endif //FFDEFS_H_

