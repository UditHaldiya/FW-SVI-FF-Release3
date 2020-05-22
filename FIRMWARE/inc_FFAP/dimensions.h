/*
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file dimensions.h
    \brief Definitions of fixed-size-like parameters shared between Unimal and C.

    CPU: Any

    OWNER: dimensions.u

    \ingroup proj
*/
#ifndef DIMENSIONS_H_
#define DIMENSIONS_H_
#define NUMBER_OF_CALIB_POINTS 8U //The # of cal points as known to Unimal and C
#define FAULT_CODE_BYTES_STORED 12 //The # of bytes allocated in NVMEM to store a single copy of faults bitmap
#define TEMPR_NUM_SENSORS 1U //! Number of temperature sensors
#define NUM_POSCTL_PARAMSETS 8U //! Number of independent position control parameter sets
#define DO_NUM_CHANNELS 2U //! Number of Discrete Outputs
#define COMM_NUM_CHANNELS 3 //! Number of UART-based comm channels
#define NUM_DIAG_BUFFERS 2U //! number of diagnostic buffers
#define DIAG_BUFFER_LOGSIZE 14 //! diag buffer size is 1<<DIAG_BUFFER_LOGSIZE
#define DIAG_BUFFER_LOGSIZE_AUX 10 //! diag buffer size is 1<<DIAG_BUFFER_LOGSIZE
#endif //DIMENSIONS_H_
/* This line marks the end of the source */
