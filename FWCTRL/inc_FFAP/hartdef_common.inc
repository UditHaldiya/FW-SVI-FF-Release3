#MP If 0 ;Tombstone header
/**
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file harttdef.inc
    \brief Master definitions of HART services - Old style

    CPU: Any

    OWNER: AK
*/
#MP Endif ;Tombstone header
#MP Include "ustd.inc"
#MP Include "HART_config.inc"
#MP     Expand DefineOb(0, #@ReadUniqueIdentifier#)
#MP strcmp(HART_SELECTION_CMD_1, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(1, #@ReadPrimaryVariable#)
#MP Endif
#MP If FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#MP     Expand DefineOb(2, #@ReadCurrent#)
#MP Endif
#MP strcmp(HART_SELECTION_CMD_3, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(3, #@ReadDynamicVariables#)
#MP Endif
#MP strcmp(HART_SELECTION_CMD_6, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(6, #@WritePollingAddress#)
#MP Endif
#MP strcmp(HART_SELECTION_CMD_11, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(11, #@ReadUniqueIdentifierByTag#)
#MP Endif
#MP strcmp(HART_SELECTION_MESSAGE, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(12, #@ReadMessage#)
#MP     Expand DefineOb(17, #@WriteMessage#)
#MP Endif
#MP strcmp(HART_SELECTION_TAGDESC, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(13, #@ReadTagAndDescriptor#)
#MP     Expand DefineOb(18, #@WriteTagAndDescriptor#)
#MP Endif
#MP     Expand DefineOb(14, #@ReadTransducerInfo#)
#MP     Expand DefineOb(15, #@ReadTransmitterInfo#)
#MP strcmp(HART_SELECTION_ASSYNUM, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(16, #@ReadFinalAssemblyNumber#)
#MP     Expand DefineOb(19, #@WriteFinalAssemblyNumber#)
#MP Endif
#MP     Expand DefineOb(38, #@ResetConfigurationChangedFlag#)
#MP strcmp(HART_SELECTION_BURST_MODE, "SUPPORTED")
#MP If strcmp > 0 ;supported
#MP     Expand DefineOb(108, #@WriteBurstModeCommand#)
#MP     Expand DefineOb(109, #@WriteBurstModeControl#)
#MP Endif
#MP     Expand DefineOb(138, #@ClearFaults#)
#MP     Expand DefineOb(139, #@ReadContinuousDiagnostics#)
#MP     Expand DefineOb(140, #@ResetContinuousDiagnostics#)
#MP     Expand DefineOb(141, #@ReadRawData#)
#MP     Expand DefineOb(174, #@WriteBiasParameters#)
#MP If FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#MP     Expand DefineOb(181, #@WriteInputCurrentRange#)
#MP Endif
#MP     Expand DefineOb(183, #@ResetToFactorCal#)
#MP     Expand DefineOb(200, #@ReadOptionConfiguration#)
#MP     Expand DefineOb(202, #@ActualReadOptionConfiguration#)
#MP If FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#MP     Expand DefineOb(213, #@ReadCurrentLoopValues#)
#MP Endif
#MP     Expand DefineOb(217, #@ReadBiasParameters#)

#MP     Expand DefineOb(248, #@WriteOptionConfig#)
#MP     Expand DefineOb(253, #@HaltProcess#)
#MP
#MP ; This line marks the end of the source
