/* This rather complex part is extracted from svi_tb.ddl
to allow for separate development.
This file is now #include'd in svi_tb.ddl.
*/

#define PROMPT_1_MANSTOPS_OPEN "|en|Wait for RAW POSITION to stabilize.\n" \
    "Click Next to accept its last value as the OPEN stop\n" \
    "Click Cancel otherwise.\n\n " \
    "ACTUATOR A PRESSURE = %[7.2f]{4} %{strPress_Unit}\n"
#define PROMPT_1_MANSTOPS_CLOSED "|en|Wait for RAW POSITION to stabilize.\n" \
    "Click Next to accept its last value as the CLOSED stop\n" \
    "Click Cancel otherwise.\n\n " \
    "ACTUATOR A PRESSURE = %[7.2f]{4} %{strPress_Unit}\n"

#define PROMPT_PB_MANSTOPS "ACTUATOR B PRESSURE = %[7.2f]{5} %{strPress_Unit}\n"

#define PROMPT_2_MANSTOPS  "SUPPLY PRESSURE = %[7.2f]{8} %{strPress_Unit}\n" \
                                         "RAW POSITION = %[8i]{6}\n" \
                                         "ACTUAL POSITION = %[7.2f]{7}\n"

#define PROMPT_SA_MANSTOPS_OPEN PROMPT_1_MANSTOPS_OPEN PROMPT_2_MANSTOPS
#define PROMPT_DA_MANSTOPS_OPEN PROMPT_1_MANSTOPS_OPEN PROMPT_PB_MANSTOPS PROMPT_2_MANSTOPS
#define PROMPT_SA_MANSTOPS_CLOSED PROMPT_1_MANSTOPS_CLOSED PROMPT_2_MANSTOPS
#define PROMPT_DA_MANSTOPS_CLOSED PROMPT_1_MANSTOPS_CLOSED PROMPT_PB_MANSTOPS PROMPT_2_MANSTOPS

METHOD  do_manual_hi_low_stops
{
    LABEL "|en|Manual Stops";
    HELP "|en|Manual High/Low Stop Limits adjustment";
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        int           ivalue;
        int           sel;
        int           nextsel;
        float         flt_buf;
        long          chk_cnt;

        unsigned long ulCal_Type;

        unsigned long trl_ids[7],trl_mbs[7];

        char strPress_Unit[5];
        unsigned long press_unit_index;

        unsigned long act_style;

        float fSupply_press_max, fSupply_press_min;
        float fOpenStopAdj;

        char strLocation[33];
        char strWho[33];
        char strCal_Date[33];

        CHECK_DEVICE_IN_MAN;
        CHECK_DEVICE_IN_PROCESS;
        add_abort_method(ITEM_ID(cancel_find_stops));

		get_acknowledgement(TEXT_STROKE_VALVE, ids, dummy, 0);

        /* set the default travel parameters */
        /*     ·   Travel = 100 */
        /*     ·   Travel Units = % */
        /*     ·   Open Stop Adjustment = 100 % */


        ids[0] = ITEM_ID(PARAM.TRAVEL);
        mbs[0] = MEMBER_ID(TRAVELRANGE);

        ids[1] = ids[0];
        mbs[1] = MEMBER_ID(UNITS_INDEX);

        ids[2] = ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT);
        mbs[2] = 0;


        ids[3] = ITEM_ID(PARAM.FIND_STOPS);
        mbs[3] = 0;

        ids[4] = ITEM_ID(PARAM.ACTUATOR_A_PRESSURE);
        mbs[4] = MEMBER_ID(VALUE);

        ids[5] = ITEM_ID(PARAM.ACTUATOR_B_PRESSURE);
        mbs[5] = MEMBER_ID(VALUE);

        ids[6] = ITEM_ID(PARAM.RAW_POSITION);
        mbs[6] = 0;

        ids[7] = ITEM_ID(PARAM.WORKING_POS); /* Not used anyway */
        mbs[7] = MEMBER_ID(VALUE);

        ids[8] = ITEM_ID(PARAM.SUPPLY_PRESSURE);
        mbs[8] = MEMBER_ID(VALUE);

        ids[9] = ITEM_ID(PARAM.PRESSURE_EXTREMES);
        mbs[9] = 0;

        ids[10] = ITEM_ID(PARAM.PRESSURE_RANGE);
        mbs[10] = MEMBER_ID(UNITS_INDEX);

        ids[11] = ITEM_ID(PARAM.ACTUATOR_3);
        mbs[11] = MEMBER_ID(ACT_STYLE);

        status = put_float_value(ids[0], mbs[0], 100.0); /* travel.range */
        status = put_unsigned_value(ids[1], mbs[1],1342); /* travel.unit */

        fOpenStopAdj = 100.0;
        status = put_float_value(ids[2], 0, fOpenStopAdj); /* Open stops adjustment */

        status = get_unsigned_value(ids[10], mbs[10], &press_unit_index);
        GET_ENUM_STRING(ids[10], mbs[10], strPress_Unit, 5);

        act_style = 0;
        status = get_unsigned_value(ids[11], mbs[11], &act_style);

        trl_ids[0]=trl_ids[1]=trl_ids[2]=trl_ids[3]=trl_ids[4]=trl_ids[5]=trl_ids[6]=ITEM_ID(PARAM.TRAVEL_CALIBRATION);
        trl_mbs[0]=MEMBER_ID(CAL_LOCATION);
        trl_mbs[1]=MEMBER_ID(CAL_DATE);
        trl_mbs[2]=MEMBER_ID(CAL_WHO);
        trl_mbs[3]=MEMBER_ID(CAL_STOP_HI_POS);
        trl_mbs[4]=MEMBER_ID(CAL_STOP_LO_POS);
        trl_mbs[5]=MEMBER_ID(CAL_TYPE);
        trl_mbs[6]=MEMBER_ID(LAST_RESULT);

        status = select_from_menu("|en|\n Select Manual Stop(s) to set:\n", \
                                  ids, mbs, 9, \
                                  "HI/LO Limits;HI Limit;LO Limit", &ivalue);
        nextsel = -1;
		switch (ivalue)
        {
        case 1: /*HI/LO Limits*/
            sel = FINDSTOPS_SETOPEN;
            nextsel = FINDSTOPS_SETCLOSED;
            ulCal_Type = CAL_TYPE_BOTH_ENDPOINTS_MANUAL;
            break;
		case 2: /*HI Limit*/
            sel = FINDSTOPS_SETOPEN;
            ulCal_Type = CAL_TYPE_OPEN_ENDPOINT_MANUAL;
			break;
        case 3:/*LO Limit*/
            sel = FINDSTOPS_SETCLOSED;
            ulCal_Type = CAL_TYPE_CLOSED_ENDPOINT_MANUAL;
            break;
        }

        READ_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), "PRESSURE_EXTREMES.SUPPLY_PRESSURE_MAX");
        READ_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), "PRESSURE_EXTREMES.SUPPLY_PRESSURE_MIN");
        status = get_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), &fSupply_press_max);
        status = get_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), &fSupply_press_min);
        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), -9999.99);
        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), 9999.99);
		send_all_values();

        READ_PARAM(ids[6], 0, "RAW_POSITION");
        READ_PARAM(ids[3], 0, "FIND_STOPS");

        /* Prepare the device for manual find stops */
        if(status == BLTIN_SUCCESS) {
            status = put_unsigned_value(ids[3], mbs[3], FINDSTOPS_START_MAN);
        }
        if(status == BLTIN_SUCCESS) {
            status = send_value(ids[3], mbs[3]);
        }

		do {
            /* A little validation paranoia */
            switch (sel) {
                case FINDSTOPS_SETOPEN:
                case FINDSTOPS_SETCLOSED:
                    break;
                default:
                {
                    get_acknowledgement("Unknown failure\n", dummy, dummy, 0);
                    return;
                }
            }

            /* Prepare the device to accept a stop */
            if(status == BLTIN_SUCCESS) {
                status = put_unsigned_value(ids[3], mbs[3], sel);
            }
            if(status == BLTIN_SUCCESS) {
                status = send_value(ids[3], mbs[3]);
            }

            if(status == BLTIN_SUCCESS) {
                if (SVI2_DBL_ACT == act_style ){
                    if(sel==FINDSTOPS_SETOPEN) {
                        status = display_dynamics(PROMPT_DA_MANSTOPS_OPEN, ids, mbs, 9);
                    }
                    else {
                        status = display_dynamics(PROMPT_DA_MANSTOPS_CLOSED, ids, mbs, 9);
                    }
                }
                else {
                    if(sel==FINDSTOPS_SETOPEN) {
                        status = display_dynamics(PROMPT_SA_MANSTOPS_OPEN, ids, mbs, 9);
                    }
                    else {
                        status = display_dynamics(PROMPT_SA_MANSTOPS_CLOSED, ids, mbs, 9);
                    }
                }
            }

            /* Accept the current value */
            if(status == BLTIN_SUCCESS) {
                status = put_unsigned_value(ids[3],mbs[3], FINDSTOPS_ACCEPT);
            }
            if(status == BLTIN_SUCCESS) {
                status = send_value(ids[3],mbs[3]);
            }
            sel = nextsel;
            nextsel = -1;

        } while ((sel>=0) && (status==BLTIN_SUCCESS));

        /* Commit the accepted stops */
        if(status == BLTIN_SUCCESS) {
            status = put_signed_value( ids[3], mbs[3], FINDSTOPS_COMMIT);
        }
        if(status == BLTIN_SUCCESS) {
            status = send_value( ids[3], mbs[3]);
#if 0
            /* This crashes the method in reference environment RRTE */
            if(status == BLTIN_FAIL_RESPONSE_CODE) {
                unsigned long code;
                get_response_code(&code, &ids[3], &mbs[3]);
                display_response_code(code, ids[3], mbs[3]);
            }
#endif
        }

        /* Regardless of status, restore what was saved */
        {
            int status1; /*Not much of a chance to do any corrections on error*/
            status1 = read_value(ids[2], mbs[2]);

            if (ulCal_Type != CAL_TYPE_CLOSED_ENDPOINT_MANUAL)
            {
                status1 = put_float_value( ids[2], mbs[2], fOpenStopAdj);
                status1 = send_value(ids[2], mbs[2]);
            }

            /*restore the saved supply_pressure_extremes*/
            status1 = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), fSupply_press_max);
            status1 = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), fSupply_press_min);
            status1 = send_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX));
            status1 = send_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN));
        }

#if 1
        if(status == BLTIN_SUCCESS) {
            /*Check the result of the Auto Stop Limits procedure,by reading the
              COMPLETE_STATUS.FIND_STOPS_FAILD and present the result to the
              user.*/
            delayfor(3, "|en|Checking find stops status ...\n", dummy, dummy, 0);

            /* report find stops success/faild */
            id = ITEM_ID(PARAM.COMPLETE_STATUS);
            mb = MEMBER_ID(CURRENT_STATUS_1_C);
            READ_PARAM(id, mb, "COMPLETE_STATUS.CURRENT_STATUS_1_C");
            status = get_unsigned_value(id, mb, &us8_buf);
            /* IF_ERROR_ABORT_MACRO_INFO("READ_STATUS:"); */
            if ( 0 != (us8_buf & FBIT1 )) {
                get_acknowledgement("|en|Stop(s) not accepted.\n",dummy,dummy,0);
                status = -1;
            }
        }
#endif

        if(status == BLTIN_SUCCESS) {
            /* At this point, the damage is done already,
            and housekeeping remains. Even if it fails, the method succeds,
            kind of
            */

            status = put_unsigned_value( trl_ids[5], trl_mbs[5], ulCal_Type);
            SEND_PARAM(trl_ids[5], trl_mbs[5], "TRAVEL_CALIBRATION.CAL_TYPE");

            READ_PARAM(trl_ids[0], trl_mbs[0], "TRAVEL_CALIBRATION.CAL_LOCATION");
            READ_PARAM(trl_ids[1], trl_mbs[1], "TRAVEL_CALIBRATION.CAL_DATE");
            READ_PARAM(trl_ids[2], trl_mbs[2], "TRAVEL_CALIBRATION.CAL_WHO");
            READ_PARAM(trl_ids[3], trl_mbs[3], "TRAVEL_CALIBRATION.CAL_STOP_HI_POS");
            READ_PARAM(trl_ids[4], trl_mbs[4], "TRAVEL_CALIBRATION.CAL_STOP_LO_POS");
            READ_PARAM(trl_ids[5], trl_mbs[5], "TRAVEL_CALIBRATION.CAL_TYPE");
            READ_PARAM(trl_ids[6], trl_mbs[6], "TRAVEL_CALIBRATION.LAST_RESULT");

            maxlen = 33;
            status = get_string_value(trl_ids[0], trl_mbs[0], strLocation, &maxlen);
            maxlen = 33;
            status = get_string_value(trl_ids[2], trl_mbs[2], strWho, &maxlen);
            maxlen = 33;
            status = get_date_value(trl_ids[1], trl_mbs[1], strCal_Date, &maxlen);

            /*display the travel calibration result*/
            get_acknowledgement("|en|\nTravel Calibration:\n"  \
                            "(To edit) CAL_LOCATION:%[s]{strLocation}\n"  \
                            "(To edit)  CAL_DATE: %{1}\n"  \
                            "(To edit)  CAL_WHO:%[s]{strWho}\n"  \
                            "  CAL_STOP_HI_POS:%[d]{3}\n"  \
                            "  CAL_STOP_LO_POS:%[d]{4}\n"  \
                            "  CAL_TYPE:%{5}\n"  \
                            "  LAST_RESULT:%{6}\n", trl_ids, trl_mbs, 7);


            edit_device_value("|en|Enter the new value for CAL_LOCATION:\n",
                              trl_ids, trl_mbs, 7, trl_ids[0], trl_mbs[0]);
            edit_device_value("|en|Enter the new value for CAL_DATE:\n",
                              trl_ids, trl_mbs, 7, trl_ids[1], trl_mbs[1]);
            edit_device_value("|en|Enter the new value for CAL_WHO:\n",
                  trl_ids, trl_mbs, 7, trl_ids[2], trl_mbs[2]);

            send_all_values();


            get_acknowledgement("|en|\nManual Travel Claibration finished.", dummy, dummy, 0);

            /* At the end of Manual Low Stop Limit procedure, the software shall */
            /* recommend to the user to run Manual High Stop Limit procedure. */
            /* At the end of Manual High Stop Limit procedure, the software shall */
            /* recommend to the user to run Manual Low Stop Limit procedure. */
            if (ulCal_Type == CAL_TYPE_CLOSED_ENDPOINT_MANUAL)
            {
                get_acknowledgement("|en|\nPlease calibrate High Stop "
                                "if the procedure was not done.", dummy, dummy, 0);
            }
            if (ulCal_Type == CAL_TYPE_OPEN_ENDPOINT_MANUAL)
            {
                get_acknowledgement("|en|\nPlease calibrate Low Stop "
                                "if the procedure was not done.", dummy, dummy, 0);
            }
        }
        else {
            get_acknowledgement("|en|Method failed\n\nPossible causes:\n"
                            "1. Open and closed stops are too close\n"
                            "2. Device is write-locked\n"
                                , dummy, dummy, 0);
        }

        /* Bail out of manual find stops */
        status = put_unsigned_value(ids[3], mbs[3], FINDSTOPS_CANCEL_MAN);
        if(status == BLTIN_SUCCESS) {
            status = send_value(ids[3], mbs[3]);
        }

    }
}

METHOD  do_find_stops
{
    LABEL "|en|Auto Find Stops";
    HELP "|en|Run Find Stops";
    CLASS INPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        int           ivalue;
        int           sel;
        float         flt_buf;
        long          chk_cnt;
        unsigned long func;
        unsigned long ulCal_Type;

        unsigned long trl_ids[7],trl_mbs[7];

        char strPress_Unit[5];
        unsigned long press_unit_index;

        unsigned long act_style;

        float fSupply_press_max, fSupply_press_min;
        float fOpenStopAdj;

        char strLocation[33];
        char strWho[33];
        char strCal_Date[33];

        CHECK_DEVICE_IN_MAN;
        CHECK_DEVICE_IN_PROCESS;

        get_acknowledgement(TEXT_STROKE_VALVE, ids, dummy, 0);


        /* set the default travel parameters */
        /*     ·   Travel = 100 */
        /*     ·   Travel Units = % */
        /*     ·   Open Stop Adjustment = 100 % */


        ids[0] = ITEM_ID(PARAM.TRAVEL);
        mbs[0] = MEMBER_ID(TRAVELRANGE);

        ids[1] = ids[0];
        mbs[1] = MEMBER_ID(UNITS_INDEX);

        ids[2] = ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT);
        mbs[2] = 0;

        ids[3] = ITEM_ID(PARAM.FIND_STOPS);
        mbs[3] = 0;

        ids[4] = ITEM_ID(PARAM.ACTUATOR_A_PRESSURE);
        mbs[4] = MEMBER_ID(VALUE);

        ids[5] = ITEM_ID(PARAM.ACTUATOR_B_PRESSURE);
        mbs[5] = MEMBER_ID(VALUE);

        ids[6] = ITEM_ID(PARAM.RAW_POSITION);
        mbs[6] = 0;

        ids[7] = ITEM_ID(PARAM.WORKING_POS);
        mbs[7] = MEMBER_ID(VALUE);

        ids[8] = ITEM_ID(PARAM.SUPPLY_PRESSURE);
        mbs[8] = MEMBER_ID(VALUE);

        ids[9] = ITEM_ID(PARAM.PRESSURE_EXTREMES);
        mbs[9] = 0;

        ids[10] = ITEM_ID(PARAM.PRESSURE_RANGE);
        mbs[10] = MEMBER_ID(UNITS_INDEX);

        ids[11] = ITEM_ID(PARAM.ACTUATOR_3);
        mbs[11] = MEMBER_ID(ACT_STYLE);

        /* clear status */
        id = ITEM_ID(PARAM.CLEAR_STATUS);
        mb = 0;
        status = put_unsigned_value(id, 0, 1);
        SEND_PARAM(id, 0, "CLEAR_STATUS");

        status = put_float_value(ids[0], mbs[0], 100.0); /* travel.range */
        status = put_unsigned_value(ids[1], mbs[1],1342); /* travel.unit */

        fOpenStopAdj = 100;
        status = put_float_value(ids[2], 0, fOpenStopAdj); /* Open stops adjustment */

        status = get_unsigned_value(ids[10], mbs[10], &press_unit_index);
        GET_ENUM_STRING(ids[10], mbs[10], strPress_Unit, 5);

        status = get_unsigned_value(ids[11], mbs[11], &act_style);
        act_style = 0;

        trl_ids[0]=trl_ids[1]=trl_ids[2]=trl_ids[3]=trl_ids[4]=trl_ids[5]=trl_ids[6]=ITEM_ID(PARAM.TRAVEL_CALIBRATION);
        trl_mbs[0]=MEMBER_ID(CAL_LOCATION);
        trl_mbs[1]=MEMBER_ID(CAL_DATE);
        trl_mbs[2]=MEMBER_ID(CAL_WHO);
        trl_mbs[3]=MEMBER_ID(CAL_STOP_HI_POS);
        trl_mbs[4]=MEMBER_ID(CAL_STOP_LO_POS);
        trl_mbs[5]=MEMBER_ID(CAL_TYPE);
        trl_mbs[6]=MEMBER_ID(LAST_RESULT);

        /* GET_ENUM_STRING(1); */

        /*status = select_from_menu("|en|\nDefault Setting: \n"           \
								  "OPEN_STOP_ADJUSTMENT = %[5.2f]{2}%% \n" \
                                  "  TRAVEL.RANGE = %[5.2f]{0}\n" \
                                  "  TRAVEL.UNITS_INDEX = %{1}\n" \
                                  "Do you want to change the setting?\n",
                                  ids, mbs, 9, "No(skip);Yes", &ivalue);

        if (ivalue == 2)
        {
            status = edit_device_value("|en|\n TRAVEL.RANGE(%[5.2f]{0})\n",
                                       ids, mbs, 9, ids[0], mbs[0]);
            status = edit_device_value("|en|\n TRAVEL.UNIT(%{1})\n",
                                       ids, mbs, 9, ids[1], mbs[1]);
			status = edit_device_value("|en|\n OPEN_STOP_ADJUSTMENT(%[5.2f]{2})\n",
                                       ids, mbs, 9, ids[2], mbs[2]);
            SEND_PARAM(ids[2], mbs[2], "OPEN_STOP_ADJUSTMENT");
            status = get_float_value(ids[2], mbs[2], &fOpenStopAdj);
        }*/


        /* The software shall read parameter PRESSURE_EXTREMES and preserve the */
        /* values for SUPPLY_PRESSURE_MAX and SUPPLY_PRESSURE_MIN. */

        /* The software shall set the PRESSURE_EXTREMES.SUPPLY_PRESSURE_MAX to */
        /* -9999.99 and PRESSURE_EXTREMES.SUPPLY_PRESSURE_MIN to 9999.99. This will */
        /* ensure that the values will be updated with the minimum and maximum */
        /* value measured during the procedure. */

        READ_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), "PRESSURE_EXTREMES.SUPPLY_PRESSURE_MAX");
        READ_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), "PRESSURE_EXTREMES.SUPPLY_PRESSURE_MIN");

        status = get_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), &fSupply_press_max);
        status = get_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), &fSupply_press_min);
        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), -9999.99);
        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), 9999.99);

        sel = func = FINDSTOPS_START;
        ulCal_Type = CAL_TYPE_BOTH_ENDPOINTS_AUTOMATIC;

        /*status = select_from_menu("|en|\nDefault Open Stops Adjustment:\n" \
                                  "OPEN_STOP_ADJUSTMENT = %[5.2f]{2}%%\n\n" \
                                  "Do you want to change the setting?", \
                                  ids, mbs, 9, "No(skip);Yes", &ivalue);
        if (ivalue == 1)
        {
            status = edit_device_value("|en|\n OPEN_STOP_ADJUSTMENT(%[5.2f]{2})\n",
                                       ids, mbs, 9, ids[2], mbs[2]);
            SEND_PARAM(ids[2], mbs[2], "OPEN_STOP_ADJUSTMENT");
            status = get_float_value(ids[2], mbs[2], &fOpenStopAdj);
        }*/

        send_all_values();



        status = put_unsigned_value(ids[3], mbs[3], func);

        GET_ENUM_STRING(ids[3], mbs[3], str_buf, 256);

        SEND_PARAM(ids[3], 0, "FIND_STOPS");
        /* Only now do we add abort method */
        add_abort_method(ITEM_ID(cancel_find_stops));

        do
        {
            /* The software shall detect that the procedure is completed, when
             * the value of FIND_STOPS is switched from 11 (Find stops Running)
             * to 0(Find stops Not Running). */
#if 0
            if (SVI2_DBL_ACT == act_style )
            {
                display_dynamics("|en|\nRun %{str_buf}:\n\n"    \
                                 "  FIND STOPS = %{3}\n" \
                                 "  ACTUATOR A PRESSURE = %[7.2f]{4} %{strPress_Unit}\n" \
                                 "  ACTUATOR B PRESSURE = %[7.2f]{5} %{strPress_Unit}\n" \
                                 "  SUPPLY PRESSURE = %[7.2f]{8} %{strPress_Unit}\n"        \
                                 "  RAW POSITION = %[8i]{6}\n"          \
                                 "  WORKING POSITION = %[7.2f]{7}\n",    \
                                 ids, mbs, 9);
            }
            else if (SVI2_SNGL_ACT == act_style)
            {
                display_dynamics("|en|\nRun %{str_buf}:\n\n"    \
                                 "  FIND STOPS = %{3}\n" \
                                 "  ACTUATOR PRESSURE = %[7.2f]{4} %{strPress_Unit}\n" \
                                 "  SUPPLY PRESSURE = %[7.2f]{8} %{strPress_Unit}\n"        \
                                 "  RAW POSITION = %[8i]{6}\n"          \
                                 "  WORKING POSITION = %[7.2f]{7}\n",    \
                                 ids, mbs, 9);
            }
#endif
            /* delayfor( 3, "|en|Find stops......", dummy, dummy, 0); */
            delayfor(3, "|en|\nRun %{str_buf}:\n\n"       \
                                 "  FIND STOPS = %{3}\n" \
                                 "  ACTUATOR PRESSURE = %[7.2f]{4} %{strPress_Unit}\n" \
                                 "  SUPPLY PRESSURE = %[7.2f]{8} %{strPress_Unit}\n"        \
                                 "  RAW POSITION = %[8i]{6}\n"          \
                                 "  ACTUAL POSITION = %[7.2f]{7}\n",    \
                                 ids, mbs, 9);

            READ_PARAM(ids[3], 0, "FIND_STOPS");
            status = get_unsigned_value(ids[3], 0, &us8_buf);

        } while(us8_buf == FINDSTOPS_START || us8_buf == FINDSTOPS_RUNNING ) /* Continue */;

        delayfor(3, "|en|Checking find stops status ...\n", dummy, dummy, 0);

        /* report find stops success/faild */
        id = ITEM_ID(PARAM.COMPLETE_STATUS);
        mb = MEMBER_ID(CURRENT_STATUS_1_C);
        READ_PARAM(id, mb, "COMPLETE_STATUS.CURRENT_STATUS_1_C");
        status = get_unsigned_value(id, mb, &us8_buf);
        /* IF_ERROR_ABORT_MACRO_INFO("READ_STATUS:"); */
        if ( 0 != (us8_buf & FBIT1 )) {
            get_acknowledgement("|en|Find stops failed.\n",dummy,dummy,0);
            METHOD_ABORT_MACRO;
        }

        {
            status = put_unsigned_value( trl_ids[5], trl_mbs[5], ulCal_Type);
            SEND_PARAM(trl_ids[5], trl_mbs[5], "TRAVEL_CALIBRATION.CAL_TYPE");

            READ_PARAM(trl_ids[0], trl_mbs[0], "TRAVEL_CALIBRATION.CAL_LOCATION");
            READ_PARAM(trl_ids[1], trl_mbs[1], "TRAVEL_CALIBRATION.CAL_DATE");
            READ_PARAM(trl_ids[2], trl_mbs[2], "TRAVEL_CALIBRATION.CAL_WHO");
            READ_PARAM(trl_ids[3], trl_mbs[3], "TRAVEL_CALIBRATION.CAL_STOP_HI_POS");
            READ_PARAM(trl_ids[4], trl_mbs[4], "TRAVEL_CALIBRATION.CAL_STOP_LO_POS");

            READ_PARAM(trl_ids[5], trl_mbs[4], "TRAVEL_CALIBRATION.CAL_TYPE");
            READ_PARAM(trl_ids[6], trl_mbs[6], "TRAVEL_CALIBRATION.LAST_RESULT");

            maxlen = 33;
            status = get_string_value(trl_ids[0], trl_mbs[0], strLocation, &maxlen);
            maxlen = 33;
            status = get_string_value(trl_ids[2], trl_mbs[2], strWho, &maxlen);
            maxlen = 33;
            status = get_date_value(trl_ids[1], trl_mbs[1], strCal_Date, &maxlen);

            /*display the travel calibration restult*/
            get_acknowledgement("|en|\nTravel Calibration:\n"  \
                            "  CAL_LOCATION:%[s]{strLocation}\n"  \
                            "  CAL_DATE: %{1}\n"  \
                            "  CAL_WHO:%[s]{strWho}\n"  \
                            "  CAL_STOP_HI_POS:%[d]{3}\n"  \
                            "  CAL_STOP_LO_POS:%[d]{4}\n"  \
                            "  CAL_TYPE:%{5}\n"  \
                            "  LAST_RESULT:%{6}\n", trl_ids, trl_mbs, 7);

            status = select_from_menu("\nDo you wish to change the values", dummy, dummy, 0, "Yes;Skip", &ivalue);
            if ( ivalue == 1)
            {
                edit_device_value("|en|Enter the new value for CAL_LOCATION:\n",
                                  trl_ids, trl_mbs, 7, trl_ids[0], trl_mbs[0]);
                edit_device_value("|en|Enter the new value for CAL_DATE:\n",
                                  trl_ids, trl_mbs, 7, trl_ids[1], trl_mbs[1]);
                edit_device_value("|en|Enter the new value for CAL_WHO:\n",
                                  trl_ids, trl_mbs, 7, trl_ids[2], trl_mbs[2]);
                /* send_all_values(); */
            }
            send_all_values();

        }


        /* At the end of Manual Low Stop Limit procedure, the software shall */
        /* recommend to the user to run Manual High Stop Limit procedure. */
        /* At the end of Manual High Stop Limit procedure, the software shall */
        /* recommend to the user to run Manual Low Stop Limit procedure. */


        /*restore the saved supply_pressure_extremes*/
        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), fSupply_press_max);
        SEND_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MAX), "SUPPLY_PRESSURE_EXTREMES");

        status = put_float_value(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), fSupply_press_min);
        SEND_PARAM(ids[9], MEMBER_ID(SUPPLY_PRESSURE_MIN), "SUPPLY_PRESSURE_EXTREMES");

        status = put_float_value(ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT), 0, 100.0);
        SEND_PARAM(ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT), MEMBER_ID(SUPPLY_PRESSURE_MIN), "OPEN_STOP_ADJUSTMENT");

        get_acknowledgement("|en|Find stops finished.", dummy, dummy, 0);
        get_acknowledgement("|en|The Auto Stops Adjustment was set to 100%", dummy, dummy, 0);

        return;
    }
}

#define AK 1 /* troubleshooting send_all_values in AMS and RRTE */
METHOD replace_stops
{
 LABEL "|en|Replace Stops";
    HELP "|en|Method runs replacing HI and LO stop values";
    CLASS INPUT;
    DEFINITION
    {
		COMMON_LOCAL_VARS;

		int ivalue;
		char strCal_Date[256];
		char strWho[33];
		char strLocation[33];
		int stopHiPos;
		int stopLoPos;
		unsigned int strCal_type;
		unsigned int strLast_result;
		signed int Raw_Position;
		float openStopAdjust;
		float workingPosValue;
		long len;
        unsigned int step;
		unsigned long ato;
		long status1, status2;

		/*CHECK_DEVICE_IN_OOS;*/
		/*check if device is in out of service mode and if it is not, then quit method*/

        step = 0;
		id = ITEM_ID(PARAM.MODE_BLK);
        mb = MEMBER_ID(TARGET);
        READ_PARAM(id, mb, "MODE_BLK.TARGET");
        if(status == BLTIN_SUCCESS) {
            step=1;
            status = get_unsigned_value(id, mb, &us8_buf);
        }
        if(status == BLTIN_SUCCESS) {
            if ( us8_buf != _OUT_OF_SERVICE) {
                get_acknowledgement("|en|MODE_BLK.TARGET is not OUT_OF_SERVICE. Method can't proceed.\n"
                                    ,dummy,dummy,0);
                METHOD_ABORT_MACRO;
            }
            step=2;
            ids[0] = ITEM_ID(PARAM.TRAVEL_CALIBRATION);
            mbs[0] = MEMBER_ID(CAL_LOCATION);

            ids[1] = ids[0];
            mbs[1] = MEMBER_ID(CAL_DATE);

            ids[2] = ids[0];
            mbs[2] = MEMBER_ID(CAL_WHO);

            ids[3] = ids[0];
            mbs[3] = MEMBER_ID(CAL_STOP_HI_POS);

            ids[4] = ids[0];
            mbs[4] = MEMBER_ID(CAL_STOP_LO_POS);

            ids[5] = ids[0];
            mbs[5] = MEMBER_ID(CAL_TYPE);

            ids[6] = ids[0];
            mbs[6] = MEMBER_ID(LAST_RESULT);

            ids[7] = ITEM_ID(PARAM.WORKING_POS);
            mbs[7] = MEMBER_ID(STATUS);

            ids[8] = ids[7];
            mbs[8] = MEMBER_ID(VALUE);

            ids[9] = ITEM_ID(PARAM.RAW_POSITION);
            mbs[9] = 0;

            ids[10] = ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT);
            mbs[10] = 0;

            /*read TRAVEL CALIBRATION variables and display current values*/
 
        }

        if(status == BLTIN_SUCCESS) {
            step=112;
			status = get_unsigned_value(ITEM_ID(PARAM.ACTUATOR_3), MEMBER_ID(ACT_FAIL_ACTION_1), &ato);
        }

        if(status == BLTIN_SUCCESS) {
            step=15;
            maxlen=33;
            status = get_string_value(ids[0], mbs[0], strLocation, &maxlen);
        }
        if(status == BLTIN_SUCCESS) {
            step=16;
            maxlen=33;
            status = get_string_value(ids[2], mbs[2], strWho, &maxlen);
        }
        if(status == BLTIN_SUCCESS) {
            step=17;
            len=9;
            status = get_date_value(ids[1], mbs[1], strCal_Date, &len);
        }
        if(status == BLTIN_SUCCESS) {
            step=18;
            status = get_unsigned_value(ids[5], mbs[5], &strCal_type);
        }
        if(status == BLTIN_SUCCESS) {
            step=19;
            status = get_unsigned_value(ids[6], mbs[6], &strLast_result);
        }
        if(status == BLTIN_SUCCESS) {
            step=20;
			status = get_signed_value(ids[3], mbs[3], &stopHiPos);
        }
        if(status == BLTIN_SUCCESS) {
            step=21;
			status = get_signed_value(ids[4], mbs[4], &stopLoPos);
        }
        if(status == BLTIN_SUCCESS) {
            step=22;
			status = get_signed_value(ids[9], mbs[9], &Raw_Position);
        }
        if(status == BLTIN_SUCCESS) {
            step=23;
			status = get_float_value(ids[10], mbs[10], &openStopAdjust);
        }
        if(status == BLTIN_SUCCESS) {
            step=24;
			status = get_float_value(ids[8], mbs[8], &workingPosValue);
        }
        if(status == BLTIN_SUCCESS) {
            step=25;
			status = get_acknowledgement("|en|WARNING!\n This method will change the valve's moving range.\n If you click Next, you will be prompted to edit Travel Calibration settings.", dummy, dummy, 0);
        }
        if(status == BLTIN_SUCCESS) {
            step=26;
			status = edit_device_value("|en|CAL_WHO: %{strWho}\n"	\
								"STOP_HI_POS: %{stopHiPos}\n"	\
								"STOP_LO_POS: %{stopLoPos}\n"	\
								"OPEN_STOP_ADJUSTMENT: %{openStopAdjust}\n"	\
								"WORKING_POS: %{workingPosValue}\n"	\
								"\nCAL_LOCATION: ", ids, mbs, 0, ids[0], mbs[0]);
        }
        if(status == BLTIN_SUCCESS) {
            step=27;
			status = edit_device_value("|en|Modified settings: \nCAL_LOCATION: %{strLocation}\n"	\
								"STOP_HI_POS: %{stopHiPos}\n"	\
								"STOP_LO_POS: %{stopLoPos}\n"	\
								"OPEN_STOP_ADJUSTMENT: %{openStopAdjust}\n"	\
								"WORKING_POS: %{workingPosValue}\n"	\
								"\nCAL_WHO: ", ids, mbs, 2, ids[2], mbs[2]);
        }
        if(status == BLTIN_SUCCESS) {
            step=28;
			workingPosValue = (100.0*(Raw_Position-stopLoPos)/(stopHiPos-stopLoPos));
			if(ato == 2) { /*2 is ATC*/
				workingPosValue = 100.0 - workingPosValue;
			}
			workingPosValue = workingPosValue*(100.0/openStopAdjust);
			status = edit_device_value("|en|CAL_LOCATION: %{strLocation}\n"	\
								"CAL_WHO: %{strWho}\n"	\
								"STOP_LO_POS: %{stopLoPos}\n"	\
								"OPEN_STOP_ADJUSTMENT: %{openStopAdjust}\n"	\
								"WORKING_POS: %{workingPosValue}\n"	\
								"\nSTOP_HI_POS: ",ids, mbs, 3, ids[3], mbs[3]);
        }
        if(status == BLTIN_SUCCESS) {
            step=29;
			workingPosValue = (100.0*(Raw_Position-stopLoPos)/(stopHiPos-stopLoPos));
			if(ato == 2) { /*2 is ATC*/
				workingPosValue = 100.0 - workingPosValue;
			}
			workingPosValue = workingPosValue*(100.0/openStopAdjust);
			status = edit_device_value("|en|CAL_LOCATION: %{strLocation}\n"	\
								"CAL_WHO: %{strWho}\n"	\
								"STOP_HI_POS: %{stopHiPos}\n"	\
								"OPEN_STOP_ADJUSTMENT: %{openStopAdjust}\n"	\
								"WORKING_POS: %{workingPosValue}\n"	\
								"\nSTOP_LO_POS: ",ids, mbs, 4, ids[4], mbs[4]);
        }
        if(status == BLTIN_SUCCESS) {
            step=30;
			workingPosValue = (100.0*(Raw_Position-stopLoPos)/(stopHiPos-stopLoPos));
			if(ato == 2) { /*2 is ATC*/
				workingPosValue = 100.0 - workingPosValue;
			}
			workingPosValue = workingPosValue*(100.0/openStopAdjust);
			status = edit_device_value("|en|CAL_LOCATION: %{strLocation}\n"	\
								"CAL_WHO: %{strWho}\n"	\
								"STOP_HI_POS: %{stopHiPos}\n"	\
								"STOP_LO_POS: %{stopLoPos}\n"	\
								"WORKING_POS: %{workingPosValue}\n"	\
								"\nOPEN_STOP_ADJUSTMENT: ",ids, mbs, 10, ids[10], mbs[10]);
        }
        if(status == BLTIN_SUCCESS) {
            step=31;
            do {
				edit_device_value("|en|CAL_DATE: ", ids, mbs, 1, ids[1], mbs[1]);
			} while(status != BLTIN_SUCCESS);
        }
        if(status == BLTIN_SUCCESS) {
            step=32;
            status = get_acknowledgement("|en| \n Click Next to send the modified settings to the device. \n Click Cancel to abort.\n", dummy, dummy, 0);
        }
        if(status == BLTIN_SUCCESS) {
            step=33;
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_LOCATION));
        }
        if(status == BLTIN_SUCCESS) {
            step=34;
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_WHO));
        }
        if(status == BLTIN_SUCCESS) {
            step=35;
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_DATE));
        }


        /*set cal_type to 43.Prepare for cloning*/
        if(status == BLTIN_SUCCESS) {
            step=36;
			put_unsigned_value(ids[5], mbs[5], CAL_TYPE_READY_CLONE);
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_TYPE));
			
        }
        
        if(status != BLTIN_SUCCESS) {
            step=361;
                get_acknowledgement("|en|Change CAL_TYPE failed.\n"
                                    ,dummy,dummy,0);
                METHOD_ABORT_MACRO;
            }

        if(status == BLTIN_SUCCESS) {
            step=37;          
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_STOP_HI_POS));
			if(status != BLTIN_SUCCESS) {
                get_acknowledgement("|en|Change Stop Hi value failed.\n"
                                    ,dummy,dummy,0);
                METHOD_ABORT_MACRO;
            }
        }

        if(status == BLTIN_SUCCESS) {
            step=38;
			status = send_value(ITEM_ID(PARAM.TRAVEL_CALIBRATION), MEMBER_ID(CAL_STOP_LO_POS));
			if(status != BLTIN_SUCCESS) {
                get_acknowledgement("|en|Change Stop LO value failed.\n"
                                    ,dummy,dummy,0);
                METHOD_ABORT_MACRO;
            }						
        }

        if(status != BLTIN_SUCCESS) {
            step=381;
                get_acknowledgement("|en|Method failed: Stop LO value not accepted.\n"
                                    ,dummy,dummy,0);
                METHOD_ABORT_MACRO;
        }

        if(status == BLTIN_SUCCESS) {
            step=39;
			status = send_value(ITEM_ID(PARAM.OPEN_STOP_ADJUSTMENT), 0);
        }

        if(status != BLTIN_SUCCESS) {
            step=391;
                get_acknowledgement("|en|WARNING: Open Stop Adjustment not accepted.\n"
									"It may be displayed erroneously in the summary.\n"
                                    "LOCATION, DATE, WHO will not be written.\n"
                                    "Complete editing manually."
                                    ,dummy,dummy,0);
                read_value(ids[10], mbs[10]);
                METHOD_ABORT_MACRO;
        }

        if(status == BLTIN_SUCCESS) {
            step=40;
            maxlen=33;
            status = get_string_value(ids[0], mbs[0], strLocation, &maxlen);
        }
        if(status == BLTIN_SUCCESS) {
            step=41;
            maxlen=33;
            status = get_string_value(ids[2], mbs[2], strWho, &maxlen);
        }

        if(status == BLTIN_SUCCESS) {
            step=42;
            status = get_unsigned_value(ids[5], mbs[5], &strCal_type);
        }

        if(status == BLTIN_SUCCESS) {
            step=43;
			status = get_signed_value(ids[3], mbs[3], &stopHiPos);
        }
        if(status == BLTIN_SUCCESS) {
            step=44;
			status = get_signed_value(ids[4], mbs[4], &stopLoPos);
        }

        if(status == BLTIN_SUCCESS) {
            step=45;
			status = get_float_value(ids[10], mbs[10], &openStopAdjust);
        }
        if(status == BLTIN_SUCCESS) {
            step=46;
			status = get_float_value(ids[8], mbs[8], &workingPosValue);
        }

        if(status == BLTIN_SUCCESS) {
            step=47;
			get_acknowledgement("|en|The new Travel Calibration settings:\n"
                                "CAL_LOCATION: %{0}\n"
								"CAL_WHO: %{2}\n"
								"CAL_TYPE: %{5}\n"
								"CAL_STOP_HI_POS: %{3}\n"
								"CAL_STOP_LO_POS: %{4}\n"
								"OPEN_STOP_ADJUSTMENT: %{10}\n"
                                    "Info:\nWORKING_POS: %{8}\n"
                                    , ids, mbs, 11);
        }
        else
        {
            if (status == BLTIN_FAIL_COMM_ERROR) {
                display_comm_error(get_comm_error());
            }
            else {
                display_builtin_error(status);
            }

            get_acknowledgement("|en|Method failed in step %{step} with status %{status}.\n", dummy, dummy, 0);
        }

	}
}

METHOD  cancel_find_stops
{
    LABEL "|en|Cancel Findstops";
    HELP HLP5("|en|run in the abort method to cancel findstops process.");
    CLASS OUTPUT;
    DEFINITION
    {
        COMMON_LOCAL_VARS;

        id = ITEM_ID(PARAM.FIND_STOPS);
        mb = 0;

        status = get_unsigned_value(id, mb, &us8_buf);
        if ( us8_buf != FINDSTOPS_NOTRUNNING && us8_buf != FINDSTOPS_CANCEL )
        {
            status = put_unsigned_value(id, mb, FINDSTOPS_CANCEL);
            SEND_PARAM(id, mb, "FIND_STOPS:CANCEL");
            get_acknowledgement("|en|\n The find stops procedure canceled.", dummy,dummy, 0);
        }

    }
}
#if 0
VARIABLE find_stops
{
    LABEL LBL_375_FIND_STOPS;
    HELP  HLP5(HLP_375_FIND_STOPS);
    CLASS CONTAINED & DYNAMIC;
    TYPE ENUMERATED (1)
    {
        ENUM_FIND_STOPS
    }
}
#endif
