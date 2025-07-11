#include "std_defs.h"

#if 1
/* ===========================================================================

FILE_NAME          rev_defs.h

  The FF DD Libraries provide a set descriptions for parameters and blocks.

  The macros in this file define the revisions of the FF descriptions that
  are imported when the DDs for the FF-FD-SW 2.40 are built.

  The FF device and DD revision numbers are taken from the FF std_defs.h file
  which was delivered together with the DD Libraries.

  DD Libraries, version 3.60 is used to generate the DDs for the
  FF-FD-SW 2.40.

  The DDs for the FF-FD-SW 2.40 are generated with Tokenizer, version 5.0.6

=========================================================================== */

/* FF device revisions used for DD import */
#define SFT_STD_PARM_dev_rev             __STD_PARM_rel_dev_rev      /*  Standard Parameters       DD-LIB V3.70 */
#define SFT_STD_XDCR_PARM_dev_rev        __STD_XDCR_PARM_rel_dev_rev      /*  Transducer Parameters     DD-LIB V3.70, 013E\01xx not available */
#define SFT_ADV_PARAM_dev_rev            __ADV_PARAM_rel_dev_rev      /*  Advanced Parameters       DD-LIB V3.70 */
#define SFT_MIO_PARM_dev_rev             0x01      /*  Std Parms for MIO blocks  DD-LIB V3.70 */

#define SFT_RES_BLOCK_2_dev_rev          __RES_BLOCK_2_rel_dev_rev      /*  DD-LIB V3.70 */

#define SFT_PID_BLOCK_dev_rev            __PID_BLOCK_rel_dev_rev      /*  DD-LIB V3.70 */
#define SFT_AI_BLOCK_dev_rev             __AI_BLOCK_rel_dev_rev      /*  DD-LIB V3.70 */
#define SFT_DI_BLOCK_dev_rev             __DI_BLOCK_rel_dev_rev      /*  DD-LIB V3.70 */
#define SFT_AO_BLOCK_dev_rev             __AO_BLOCK_rel_dev_rev      /*  DD-LIB V3.70 */
#define SFT_DO_BLOCK_dev_rev             __DO_BLOCK_rel_dev_rev      /*  DD-LIB V3.70 */

#define SFT_SIGNAL_CHARACTERIZER_dev_rev 0x01      /*  Signal Characterizer      DD-LIB V3.70 */
#define SFT_INTEGRATOR_dev_rev           0x01      /*  Integrator                DD-LIB V3.70 */
#define SFT_INPUT_SELECTOR_dev_rev       __INPUT_SELECTOR_rel_dev_rev      /*  Input Selector            DD-LIB V3.70 */
#define SFT_ARITHMETIC_dev_rev           __ARITHMETIC_rel_dev_rev      /*  Arithmetic                DD-LIB V3.70 */
#define SFT_OUTPUT_SPLITTER_dev_rev      __OUTPUT_SPLITTER_rel_dev_rev      /*  Output Splitter           DD-LIB V3.70 */

#define SFT_MDI_dev_rev                  0x01      /*  Multiple Discrete Input   DD-LIB V3.70 */
#define SFT_MDO_dev_rev                  0x01      /*  Multiple Discrete Output  DD-LIB V3.70 */
#define SFT_MAI_dev_rev                  __MAI_rel_dev_rev      /*  Multiple Analog Input     DD-LIB V3.70 */
#define SFT_MAO_dev_rev                  0x01      /*  Multiple Analog Output    DD-LIB V3.70 */


/* FF DD revisions used for DD import */
#define SFT_STD_PARM_dd_rev              __STD_PARM_rel_dd_rev      /*  Standard Parameters       DD-LIB V3.70 */
#define SFT_STD_XDCR_PARM_dd_rev         __STD_XDCR_PARM_rel_dd_rev      /*  Transducer Parameters     DD-LIB V3.70 */
#define SFT_ADV_PARAM_dd_rev             __ADV_PARAM_rel_dd_rev      /*  Advanced Parameters       DD-LIB V3.70 */
#define SFT_MIO_PARM_dd_rev              0x01      /*  Std Parms for MIO blocks  DD-LIB V3.70 */

#define SFT_RES_BLOCK_2_dd_rev           __RES_BLOCK_2_rel_dd_rev      /*  DD-LIB V3.70 */

#define SFT_PID_BLOCK_dd_rev             __PID_BLOCK_rel_dd_rev      /*  DD-LIB V3.70 */
#define SFT_AI_BLOCK_dd_rev              __AI_BLOCK_rel_dd_rev      /*  DD-LIB V3.70 */
#define SFT_DI_BLOCK_dd_rev              __DI_BLOCK_rel_dd_rev      /*  DD-LIB V3.70 */
#define SFT_AO_BLOCK_dd_rev              __AO_BLOCK_rel_dd_rev      /*  DD-LIB V3.70 */
#define SFT_DO_BLOCK_dd_rev              __DO_BLOCK_rel_dd_rev      /*  DD-LIB V3.70 */

#define SFT_SIGNAL_CHARACTERIZER_dd_rev  0x02      /*  Signal Characterizer      DD-LIB V3.70 */
#define SFT_INTEGRATOR_dd_rev            0x04      /*  Integrator                DD-LIB V3.70 */
#define SFT_INPUT_SELECTOR_dd_rev        __INPUT_SELECTOR_rel_dd_rev      /*  Input Selector            DD-LIB V3.70 */
#define SFT_ARITHMETIC_dd_rev            __ARITHMETIC_rel_dd_rev      /*  Arithmetic                DD-LIB V3.70 */
#define SFT_OUTPUT_SPLITTER_dd_rev       __OUTPUT_SPLITTER_rel_dd_rev      /*  Output Splitter           DD-LIB V3.70 */

#define SFT_MDI_dd_rev                   0x02      /*  Multiple Discrete Input   DD-LIB V3.70 */
#define SFT_MDO_dd_rev                   0x02      /*  Multiple Discrete Output  DD-LIB V3.70 */
#define SFT_MAI_dd_rev                   __MAI_rel_dd_rev      /*  Multiple Analog Input     DD-LIB V3.70 */
#define SFT_MAO_dd_rev                   0x02      /*  Multiple Analog Output    DD-LIB V3.70 */

#endif

