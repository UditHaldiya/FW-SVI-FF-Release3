#ifndef SVI_TB_H_2012_07_25_09_58_21_GE_300010777
#define SVI_TB_H_2012_07_25_09_58_21_GE_300010777
#define TS_TB_H "Time-stamp: <2013-11-27 13:06:50 GE-300010777>"

/*----------/
** Reference
/----------*/

/*
#+LINK: FFSPEC file:d:/Doc_index/FF_Index/all_FF_New_spec
   Web Document:
   [[http://libraries.ge.com/foldersIndex.do?p_id=0&ohr_id=300010763&entity_id=18935703101&sid=101&SF=1#24543915101]]
   Loc. Document: [[file:c:/GE/SVI%20II%20AP/FF%20DD/docs/FF_Parameter_Mapping_TB.xlsx]]
*/

#if 0
/*------------------------------------------/
** Related with developing test purpose(TMP)
/------------------------------------------*/

#define _CONDTB_TEST_INPUT_BIT_ENUM           \
        {0x00000001,    "DISPLAY_FORMAT_1"  },\
        {0x00000002,    "DISPLAY_FORMAT_2"  },\
        {0x00000004,    "EDIT_FORMAT_1"     },\
        {0x00000008,    "EDIT_FORMAT_2"     },\
        {0x00000010,    "MIN_VALUE_1"       },\
        {0x00000020,    "MIN_VALUE_2"       },\
        {0x00000040,    "MAX_VALUE_1"       },\
        {0x00000080,    "MAX_VALUE_2"       },\
        {0x00000100,    "ENUMERATED_1"      },\
        {0x00000200,    "ENUMERATED_2"      },\
        {0x00000400,    "BIT_ENUMERATED_1"  },\
        {0x00000800,    "BIT_ENUMERATED_2"  },\
        {0x00001000,    "CONSTANT_UNIT_1"   },\
        {0x00002000,    "CONSTANT_UNIT_2"   },\
        {0x00004000,    "HANDLING_1"        },\
        {0x00008000,    "HANDLING_2"        },\
        {0x00010000,    "VALIDITY_1"        },\
        {0x00020000,    "VALIDITY_2"        }
#endif

#define _DISPLAY_FORMAT_1_BIT   0x00000001
#define _DISPLAY_FORMAT_2_BIT   0x00000002
#define _EDIT_FORMAT_1_BIT      0x00000004
#define _EDIT_FORMAT_2_BIT      0x00000008
#define _MIN_VALUE_1_BIT        0x00000010
#define _MIN_VALUE_2_BIT        0x00000020
#define _MAX_VALUE_1_BIT        0x00000040
#define _MAX_VALUE_2_BIT        0x00000080
#define _ENUMERATED_1_BIT       0x00000100
#define _ENUMERATED_2_BIT       0x00000200
#define _BIT_ENUMERATED_1_BIT   0x00000400
#define _BIT_ENUMERATED_2_BIT   0x00000800
#define _CONSTANT_UNIT_1_BIT    0x00001000
#define _CONSTANT_UNIT_2_BIT    0x00002000
#define _HANDLING_1_BIT         0x00004000
#define _HANDLING_2_BIT         0x00008000
#define _VALIDITY_1_BIT         0x00010000
#define _VALIDITY_2_BIT         0x00020000

#define _CONDTB_ENUM_HELP   "These enumerations represent conditional"     \
                            " evaluation values used to test the attributes "\
                            "of variables in this block."

/*----------------------------/
** Common preprocessing macros
/----------------------------*/

/*~~~~~~~~~~~~~~~~~/
*** general macros
/~~~~~~~~~~~~~~~~~*/

#ifdef DDTEST
#define ACCELERATE_FOR_DEV(x) (x)
#define NO_ABORT_FOR_TEST(x)
#define TEST_ID_MID(id, mid)                                           \
{                                                                      \
    tid = id;                                                          \
    tm_id = mid;                                                       \
    display_message("|en|Id:%[d]{tid}, %[d]{tm_id}", dummy, dummy, 0); \
}                                                                      \

#define TEST_VARS  ;  \
unsigned long tid, tm_id \

#else
#define ACCELERATE_FOR_DEV(x)
#define NO_ABORT_FOR_TEST(x) x
#define TEST_ID_MID(id, mid)
#define TEST_VARS
#endif

#ifdef FWTEST

  #define DATA_LIMITS(min, max) ;
  #define DATA_LIMITS_FOR_PRESS_UNITS(min, max) ;
  #define REDEFINE_DATA_LIMITS_FOR_PRESS_UNITS(_type, min, max)
  #define REDEFINE_DATA_LIMITS(_type, min, max)
  #define REDEFINE_DATA_LIMITS_ONLY_MIN(_type, min)
  #define REDEFINE_DATA_LIMITS_ONLY_MAX(_type, max)

#else

    #define DATA_LIMITS(min, max)   \
    {                               \
      MIN_VALUE min;                \
      MAX_VALUE max;                \
    }

    #define REDEFINE_DATA_LIMITS_ONLY_MIN(_type, min) \
    TYPE _type \
    { \
        REDEFINE MIN_VALUE min; \
        DELETE MAX_VALUE; \
    } \

    #define REDEFINE_DATA_LIMITS_ONLY_MAX(_type, max) \
    TYPE _type \
    { \
        REDEFINE MAX_VALUE max; \
        DELETE MIN_VALUE; \
    } \

    #define REDEFINE_DATA_LIMITS(_type, min, max)   \
    TYPE _type \
    {                                        \
      REDEFINE MIN_VALUE min;                \
      REDEFINE MAX_VALUE max;                \
    }

    #define DATA_LIMITS_FOR_PRESS_UNITS(min, max) \
        {                                         \
            MIN_VALUE SELECT (PARAM.PRESSURE_RANGE.UNITS_INDEX) \
            { \
                CASE 1141: min / 6.895; \
                CASE 1133: min; \
                CASE 1137: min * 0.01; \
            }  \
            MAX_VALUE SELECT (PARAM.PRESSURE_RANGE.UNITS_INDEX) \
            { \
                CASE 1141: max / 6.895;    \
                CASE 1133: max ; \
                CASE 1137: max * 0.01; \
            } \
        }                                         \

    #define REDEFINE_DATA_LIMITS_FOR_PRESS_UNITS(_type, min, max)   \
    TYPE _type \
    {                                        \
        REDEFINE MIN_VALUE SELECT (PARAM.PRESSURE_RANGE.UNITS_INDEX)   \
            { \
                CASE 1141: min / 6.895; \
                CASE 1133: min ; \
                CASE 1137: min * 0.01; \
            }  \
        REDEFINE MAX_VALUE SELECT (PARAM.PRESSURE_RANGE.UNITS_INDEX) \
            { \
                CASE 1141: max / 6.895; \
                CASE 1133: max ; \
                CASE 1137: max * 0.01; \
            } \
    }

#endif

#ifdef FWTEST
#else

#endif

#ifndef DD4
#define EDD(x) x
#else
#define EDD(x)
#endif

#ifndef DD4
#define HLP5(x) x
#else
#define HLP5(x) "|en|"
#endif

#define SVI2_MODE_REMOTE_OUTPUT   0x01
#define SVI2_MODE_REMOTE_CASCADE  0x02
#define SVI2_MODE_CASCADE         0x04
#define SVI2_MODE_AUTOMATIC       0x08
#define SVI2_MODE_MANUAL          0x10
#define SVI2_MODE_LOCKED          0x20
#define SVI2_MODE_INITIALIZATION  0x40
#define SVI2_MODE_OUT_OF_SERVICE  0x80

#define _DISABLE                 0x00
#define _ENABLE                  0x01

#define TEXT_STROKE_VALVE                                                               \
    "|en|WARNING. This procedure will MOVE the valve. \n"         \
    "Click \"Next\" to proceed or \"Cancel\" to exit. \n" \

/*~~~~~~~~~/
*** status
/~~~~~~~~~*/

#define STATUS_MENU(x)                              \
MENU device_status_#x_tb                                \
{                                                       \
    LABEL   "|en|status ##x;"                           \
    STYLE   PAGE;                                       \
    ITEMS                                               \
    {                                                   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[0],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[1],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[2],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[3],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[4],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[5],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[6],   \
        PARAM.COMPLETE_STATUS.CURRENT_STATUS_#x_C[7]    \
        EDD(COLUMNBREAK)                                \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[0],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[1],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[2],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[3],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[4],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[5],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[6],   \
        PARAM.COMPLETE_STATUS.HISTORY_STATUS_#x_H[7]    \
                                                        \
    }                                                   \
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~/
*** common macro for methods
/~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define COMMON_LOCAL_VARS												\
    unsigned long dummy[1],ignored;										\
    unsigned long code,id,mb,ids[20],mbs[20],indices[1];				\
    long status,resp_code;												\
	unsigned long us8_buf;												\
	char     str_buf[256];												\
	long     maxlen;													\
	int tries /*This pre-defination must be ended by semo-comma*/		\
    TEST_VARS                                                          \




#define METHOD_FINISHED_MACRO \
    display_message("|en|The method finished.", dummy, dummy, 0); \
    return;

#define METHOD_ABORT_MACRO \
    display_message("|en|Aborted.", dummy, dummy, 0); \
    return;

#define METHOD_EXIT_MACRO \
    display_message("|en|The method exits.", dummy, dummy, 0); \
    return;

#define IF_ERROR_ABORT_MACRO_INFO(prompt)   \
    if ( BLTIN_SUCCESS !=status) { \
        resp_code = status;                                              \
        display_message("|en|" prompt "(%[d]{status})\n", dummy, dummy, 0); \
        if ( BLTIN_FAIL_RESPONSE_CODE == resp_code  ) { \
             get_response_code(&resp_code, &id, &mb);                     \
             display_response_code(id, mb, resp_code); \
        }                                                       \
        else{                                                   \
            display_builtin_error(status);                      \
        }                              \
        METHOD_ABORT_MACRO \
    }

#define IF_ERROR_ABORT_MACRO \
    if ( BLTIN_SUCCESS != status) { \
        display_builtin_error(status); \
        METHOD_ABORT_MACRO \
    }

#define SHOW_ENUM_MACRO(para_name, para_str) \
    id = ITEM_ID(para_name); \
    status = read_value(id, 0); \
    status = get_unsigned_value(id, 0, &us8_buf); \
    status = get_status_string(id, 0, us8_buf, str_buf, maxlen); \
    status = get_acknowledgement("|en| " #para_str " = %{str_buf}.\n", dummy, dummy, 0);

#define EDIT_ENUM_MACRO(para_name, sub_name, para_str)                         \
    id = ITEM_ID(PARAM.para_name);                                             \
    mb = MEMBER_ID(sub_name);                                                  \
    status = read_value(id, mb);                                               \
    status = get_unsigned_value(id, mb, &us8_buf);                             \
    status = get_status_string(id, mb, us8_buf, str_buf, maxlen);              \
    status = select_from_menu("|en|" #para_str " = %{str_buf}.\n"              \
                              "Do you want to change the setting?\n",          \
                              dummy, dummy, 0, "Yes;No(Skip)\n", &ivalue);     \
    display_message("|en|\n", dummy, dummy, 0);                                \
    if ( ivalue == 1 ) {                                                       \
        status = edit_device_value("|en|Change to:", dummy, dummy, 0, id, mb); \
        IF_ERROR_ABORT_MACRO_INFO("Edit" #para_str)                            \
        status = send_value(id, mb);                                           \
        IF_ERROR_ABORT_MACRO_INFO("Sending" #para_str )                        \
        status = read_value(id, mb);                                           \
        IF_ERROR_ABORT_MACRO_INFO("Reading back" #para_str )                   \
        status = get_unsigned_value(id, mb, &us8_buf);                         \
        status = get_status_string(id, mb, us8_buf, str_buf, maxlen);          \
        status = display_message("|en| " #para_str " = %{str_buf}.\n", dummy, dummy, 0); \
    }

#define EDIT_FLOAT_MACRO_SUB(para_name, sub_name, para_str, unit_str)                           \
  id = ITEM_ID(PARAM.para_name); \
  mb = MEMBER_ID(sub_name); \
  flt_buf = 0; \
  ivalue = 0; \
  status = read_value(id, mb); \
  status = get_float_value(id, mb, &flt_buf); \
  status = select_from_menu("|en|" para_str "= %[.3f]{flt_buf}" unit_str "\nDo you want to change the setting?\n",  dummy, dummy, 0, "Yes;No(Skip)", &ivalue); \
  display_message("|en|\n", dummy, dummy, 0); \
 \
  if ( ivalue == 1 ) { \
      status = edit_device_value("|en|Change to:", dummy, dummy, 0, id, mb); \
      IF_ERROR_ABORT_MACRO_INFO("Edit" para_str) \
      status = send_value(id, mb); \
      status = read_value(id, mb); \
      status = get_float_value(id, mb, &flt_buf); \
      status = display_message("|en| " para_str "= %{flt_buf} " unit_str ".\n",  dummy, dummy, 0); \
 } \


/*
#define EDIT_FLOAT_MACRO_SUB(para_name, sub_name, para_str, unit_str)                           \
    id = ITEM_ID(PARAM.para_name);                                                              \
    mb = MEMBER_ID(sub_name);                                                                   \
    flt_buf = 0;                                                                                \
    ivalue = 0;                                                                                 \
    status = read_value(id, mb);                                                                \
    status = get_float_value(id, mb, &flt_buf);                                                 \
    status = select_from_menu("|en| " para_str " = %[f]{flt_buf} " unit_str ".\nDo you want to change the setting?\n", dummy, dummy, 0, "Yes;No(Skip)", &ivalue); \
    display_message("|en|\n", dummy, dummy, 0);                                                 \
    if ( ivalue == 1 ) {                                                                        \
        status = edit_device_value("|en|Change to:", dummy, dummy, 0, id, mb);                  \
        IF_ERROR_ABORT_MACRO_INFO("Edit" para_str)                                             \
        status = send_value(id, mb);                                                            \
        IF_ERROR_ABORT_MACRO_INFO("Sending" para_str )                                         \
        status = read_value(id, mb);                                                            \
        IF_ERROR_ABORT_MACRO_INFO("Reading back" para_str )                                    \
        status = get_float_value(id, mb, &flt_buf);                                             \
        status = display_message("|en| " para_str " = %[f]{flt_buf} " unit_str ".\n", dummy, dummy, 0); \
    }
*/

#define EDIT_ENUM_MACRO_LOC(para_name, para_str, prompt)                                            \
    id = ITEM_ID(PARAM.para_name);                                                              \
    status = read_value(id, 0);                                                                 \
    status = get_unsigned_value(id, 0, &us8_buf);                                               \
    status = get_status_string(id, 0, us8_buf, str_buf, maxlen);                                \
    status = select_from_menu("|en| " #para_str " = %{str_buf}.\n"                              \
                              #prompt "\n",                                                     \
                              dummy, dummy, 0, "Yes;No(Skip)", &ivalue);                        \
    display_message("|en|\n", dummy, dummy, 0);                                                 \
    if ( ivalue == 1 ) { \
        id = ITEM_ID(LOCAL_PARAM.LOCAL_#para_name);                                     \
        status = edit_device_value("|en|Change to:", dummy, dummy, 0, id, 0);                \
        IF_ERROR_ABORT_MACRO                                                                    \
        status = assign(ITEM_ID(PARAM.para_name), 0, ITEM_ID(LOCAL_PARAM.LOCAL_#para_name), 0);\
        id = ITEM_ID(PARAM.para_name);                                  \
        status = send_value(id, 0);                                                             \
        IF_ERROR_ABORT_MACRO                                                                    \
        status = read_value(id, 0);                                                             \
        status = get_unsigned_value(id, 0, &us8_buf);                                           \
        status = get_status_string(id, 0, us8_buf, str_buf, maxlen);                            \
        status = get_acknowledgement("|en| " #para_str " = %{str_buf}.\n", dummy, dummy, 0);    \
    }
#define CHECK_DIAG_BUFFER																			\
		READ_PARAM(ITEM_ID(PARAM.DIAGNOSTIC_DATA), 0, "DIAGNOSTIC_DATA")							\
		status = get_unsigned_value(ITEM_ID(PARAM.DIAGNOSTIC_DATA), 0, &us8_buf);					\
		display_message("|en|Checking diagnostic buffer...", dummy, dummy, 0);						\
		if (us8_buf > 0) {																			\
				display_message("|en|Attetion! There is data in the diagnostic buffer; clicking Next will prompt losing it. Click Cancel abort Auto Tune.", dummy, dummy, 0);                    \
				METHOD_ABORT_MACRO                                                                  \
		}			\
		else{																						\
				display_message("|en|Diagnostic buffer is clear.", dummy, dummy, 0);                    \
		}																							\

#define CHECK_DEVICE_IN_PROCESS                                                                         \
		READ_PARAM(ITEM_ID(PARAM.CHECK_PROCESS), MEMBER_ID(PROCESS_ID), "CHECK_PROCESS")		\
        status = get_unsigned_value(ITEM_ID(PARAM.CHECK_PROCESS), MEMBER_ID(PERCENT_COMPLETE), &us8_buf);     \
        if ( us8_buf > 0 ){                                                                             \
            display_message("|en|The device is runing in a process.\n"                                  \
                            "Please wait for the process to end.", dummy, dummy, 0);                    \
            METHOD_ABORT_MACRO                                                                          \
        }                                                                                               \
/*
#define CHECK_COMPLETE_PROCESS                                                                         \
		READ_PARAM(ITEM_ID(PARAM.CHECK_PROCESS), MEMBER_ID(PROCESS_ID), "CHECK_PROCESS")		\
        status = get_unsigned_value(ITEM_ID(PARAM.CHECK_PROCESS), MEMBER_ID(PROCESS_ID), &us8_buf);     \
        if ( us8_buf == 0 ){                                                                             \
            delayfor(2,"|en|No process is running. \n"                                  \
                            ".", dummy, dummy, 0);										                \
        }  else if (us8_buf > 0){																		\
			display_message("|en| The device is runing in a process.\n", dummy, dummy, 0);							\
		}		*/																						\

#define CHECK_DEVICE_IN_MAN                                                                     \
        READ_PARAM(ITEM_ID(PARAM.MODE_BLK), MEMBER_ID(ACTUAL), "MODE_BLK");                        \
        status = get_unsigned_value(ITEM_ID(PARAM.MODE_BLK), MEMBER_ID(ACTUAL), &us8_buf);      \
                                                                                                \
        if ( us8_buf != _MANUAL ) { /* TB spec. V37 */                                          \
            get_acknowledgement("|en|MODE_BLK(Actual) is not in MAN mode.\n"                    \
                                "Please set to the MAN mode.\n",dummy,dummy,0);                 \
            METHOD_ABORT_MACRO                                                                  \
        }                                                                                       \

#define GET_ENUM_STRING(id, mb, str_buf, len)     \
    status = get_unsigned_value(id, mb, &us8_buf);                  \
    status = get_status_string(id, mb, us8_buf, str_buf, len); \

#define READ_PARAM(param_id, mb_id, error_prompt)										\
        for(tries=0; tries<TRIES_CNT; tries=tries+1)									\
        {																				\
            {																			\
                status=read_value(param_id,mb_id);										\
                get_response_code(&resp_code,&ignored,&ignored);						\
                if(( BLTIN_FAIL_RESPONSE_CODE != status)||(8!=resp_code))break;			\
            }																			\
        }																				\
/*
        if(BLTIN_SUCCESS != status)														\
        {																				\
            get_acknowledgement("|en|Error(%[d]{status}) on reading:" error_prompt, dummy, dummy, 0);	\
            NO_ABORT_FOR_TEST(display_builtin_error(status);) \
            TEST_ID_MID(param_id, mb_id);                               \
            if( BLTIN_FAIL_RESPONSE_CODE ==status )										\
            {																			\
                display_response_code(param_id, mb_id,resp_code);						\
            }																			\
            NO_ABORT_FOR_TEST(method_abort("|en|Aborting due to the error");)								\
        }																				\
*/

#define SEND_PARAM(param_id, mb_id, error_prompt)										\
		status = send_value(param_id, mb_id);											\
/* comment below code to avoid error in NI 4.0.1
        if(BLTIN_SUCCESS != status)														\
        {																				\
            get_acknowledgement("|en|\f Error(%[d]{status}) on sending:" error_prompt, dummy, dummy, 0);	\
            NO_ABORT_FOR_TEST(display_builtin_error(status);)												\
            if( BLTIN_FAIL_RESPONSE_CODE ==status )										\
            {																			\
			    get_response_code(&resp_code, &ignored, &ignored);						\
                display_response_code(param_id, mb_id,resp_code); \
                TEST_ID_MID(param_id, mb_id);                           \
            }                                                           \
            NO_ABORT_FOR_TEST(method_abort("|en|Aborting due to the error");) \
         }                                                       \
*/
/*if you just want to check whether percent complete is = or > 150 then call SEND_COMMAND(0); */
#define SEND_COMMAND(ivalue)							\
		unsigned long  abortme;									\
		ids[0] = ITEM_ID(PARAM.CHECK_PROCESS);					\
		mbs[0] = MEMBER_ID(PERCENT_COMPLETE);					\
		ids[1] = ITEM_ID(PARAM.OFFLINE_DIAGNOSTIC);				\
		mbs[1] = 0;												\
		status = get_unsigned_value(ids[0], mbs[0], &us8_buf);		\
		abortme = 1;											\
	if (ivalue != 0) {												\
		if (mbs[0] >= 150) {										\
			get_acknowledgement("|en| WARNING: This procedure will move the valve.\n"		\
			"Existing data may be lost. Please upload it in DTM. Click Next to proceed or quit now to keep data. \n", dummy, dummy, 0);		\
		}else if (mbs[0] < 150) {										\
			SEND_PARAM(ids[1], mbs[1], ivalue);									\
			status = put_unsigned_value(ids[1], mbs[1], ivalue);				\
			status = send_value(ids[1], mbs[1]);								\
			send_all_values();													\
			display_message("|en|%{1} \n", ids, mbs, 1);			\
			abortme = 0;															\
		}																\
		while (abortme != 0) {											\
				display_message("|en| %L{1} = %{1}", ids, mbs, 1);		\
				/*Cancel process*/												\
				SEND_PARAM(ids[1], mbs[1], 99);									\
				status = put_unsigned_value(ids[1], mbs[1], 99);				\
				status = send_value(ids[1], mbs[1]);							\
				send_all_values();												\
				display_message("|en|%L{1} = %{1}", ids, mbs, 1);				\
				/*write in requested command and display it*/					\
				SEND_PARAM(ids[1], mbs[1], ivalue);								\
				status = put_unsigned_value(ids[1], mbs[1], ivalue);			\
				status = send_value(ids[1], mbs[1]);							\
				send_all_values();												\
				display_message("|en|%L{1} = %{1}", ids, mbs, 1);				\
				abortme = 0;													\
		}																		\
	}																			\
	if(ivalue == 0){															\
		if (mbs[0] >= 150) {													\
			get_acknowledgement("|en| Existing data may be lost. Please upload it in DTM. Click Next to proceed or quit now to keep data. \n", dummy, dummy, 0);		\
		}																		\
		SEND_PARAM(ids[1], mbs[1], ivalue);										\
		status = put_unsigned_value(ids[1], mbs[1], ivalue);			\
		status = send_value(ids[1], mbs[1]);							\
		send_all_values();												\
		display_message("|en|%L{1} = %{1}", ids, mbs, 1);						\
	}
/*~~~~~~~~~~~~~~~~~~~~~~~/
*** Local parameter list
/~~~~~~~~~~~~~~~~~~~~~~~*/

#define LOCAL_PARAMETER_LIST                            \
            LOCAL_POS_HISTGRAM, local_pos_histgram;     \
            LOCAL_APP_MODE,     local_app_mode;         \
            LOCAL_INPUT_VAR,    local_input_var;        \
            LOCAL_INPUT_REC,    local_input_rec;        \
            LOCAL_INPUT_ARY,    local_input_ary;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
*** Common label & help defines
/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define HLP_FLOAT_VALUE \
  "|en| float value" \

#define HLP_POSITION_ALERT \
  "|en| True if ALERT is true"                                                          \
  "\nNot Changed if ALERT is false"

#define HLP_POSITION                                                                \
  "|en| Current valve position. Presented here for convenience"

#define HLP_ALERT_POINT                                                             \
  "|en| POSITION Value, above which the ALERT will be set to True." \

#define HLP_DEADBAND                                                                \
  "|en| POSITION change, required to clear the ALERT, once it was set to True"

#define HLP_HISTORIC_ALERT                                                          \
  "|en| True if ALERT is true"                                                          \
  "\nNot Changed if ALERT is false"

#define HLP_HISTORIC_ALERT_FOR_NEAR_CLOSED_ALERT  \
  "|en| The count for the near closed alterts had happened"                                                          \

#define HLP_ENABLE                                                                  \
  "|en| True - Enables the ALERT to be reported according to the configuration"         \
  "\nFalse - Disables ALERT reporting"

#define LBL_POSITION_ALERT                  "|en|Position Hi/Lo Alert"
#define LBL_POSITION                        "|en|Position"
#define LBL_ALERT_POINT                     "|en|Alert Point"
#define LBL_DEADBAND                        "|en|Deadband"
#define LBL_ALERT                           "|en|Alert"
#define LBL_HISTORIC_ALERT                  "|en|Historic Alert"
#define LBL_ENABLE                          "|en|Enable"

#define HLP_DIRECTION                                                                   \
  "|en|Value:"                                                                          \
  "\n  1 - Normal Open (default)"                                                       \
  "\n  0 - Normal Closed"

#define HLP_FUNCTION                                                                    \
  "|en|Customize the switch configuration by following selection:"        \
  "\n0. Disabled (always inactive; default)"                                            \
  "\n1. DO block"                                                                       \
  "\n2. Fault State"                                                                    \
  "\n3. Not In Normal"                                                                  \
  "\n4. Maintenance Required"                                                           \
  "\n5. Warning Data"                                                                   \
  "\n6. Air Supply Alert"                                                               \
  "\n7. Travel Deviation Alert"                                                         \
  "\n8. Position HI Alert"                                                              \
  "\n9. Position LO Alert"                                                              \
  "\n10. Always Active"                                                                 \
  "\n11. Always Inactive (same as disabled)"                                            \
  "\n12. Reset Occurred"                                                                \
  "\n13. Tight cutoff"

#define HLP_POS_5_PERCENT_CLOSED            "|en|"                                  \

#define HLP_POS_10_PERCENT                  "|en|"                                  \

#define HLP_POS_20_PERCENT                  "|en|"                                  \

#define HLP_POS_30_PERCENT                  "|en|"                                  \

#define HLP_POS_40_PERCENT                  "|en|"                                  \

#define HLP_POS_50_PERCENT                  "|en|"                                  \

#define HLP_POS_60_PERCENT                  "|en|"                                  \

#define HLP_POS_70_PERCENT                  "|en|"                                  \

#define HLP_POS_80_PERCENT                  "|en|"                                  \

#define HLP_POS_90_PERCENT                  "|en|"                                  \

#define HLP_POS_95_PERCENT                  "|en|"                                  \

#define HLP_POS_95_PERCENT_OPEN             "|en|"                                  \

#define LBL_POS_5_PERCENT_CLOSED            "|en|5% Closed"
#define LBL_POS_10_PERCENT                  "|en|10%"
#define LBL_POS_20_PERCENT                  "|en|20%"
#define LBL_POS_30_PERCENT                  "|en|30%"
#define LBL_POS_40_PERCENT                  "|en|40%"
#define LBL_POS_50_PERCENT                  "|en|50%"
#define LBL_POS_60_PERCENT                  "|en|60%"
#define LBL_POS_70_PERCENT                  "|en|70%"
#define LBL_POS_80_PERCENT                  "|en|80%"
#define LBL_POS_90_PERCENT                  "|en|90%"
#define LBL_POS_95_PERCENT                  "|en|95%"
#define LBL_POS_95_PERCENT_OPEN             "|en|95% Open"

#define HLP_P                               "|en|"                                  \

#define HLP_I                               "|en|"                                  \

#define HLP_D                               "|en|"                                  \

#define HLP_PADJ                            "|en|"                                  \

#define HLP_BETA                            "|en|"                                  \

#define HLP_POSCOMP                         "|en|"                                  \

#define HLP_DEADZONE                        "|en|"                                  \

#define HLP_NONLIN                          "|en|"                                  \

#define LBL_P                               "|en|P"
#define LBL_I                               "|en|I"
#define LBL_D                               "|en|D"
#define LBL_PADJ                            "|en|Padj"
#define LBL_BETA                            "|en|Beta"
#define LBL_POSCOMP                         "|en|Poscomp"
#define LBL_DEADZONE                        "|en|Deadzone"
#define LBL_NONLIN                          "|en|Nonlin"

#define LBL_MAPPED_TO_RB                    "|en|Mapped To RB"
#define HLP_MAPPED_TO_RB                                                            \
  "|en| Indicate if alarms will be reported by the RB:"                                 \
  "\n 1 :: Map to RB (Default)"                                                         \
  "\n 2 :: Report in TB"                                                                \

#define LBL_PROPAGATE_MODE  "|en|Propagate Mode"

#define HLP_PROPAGATE_MODE                        \
  "|en|Propagate Fail State to Resource Block"          \
  "\n  Propagate RB OOS mode to TB – Not propagate Failsafe state of AP to RB(but propagate RB OOS mode to TB)"          \
  "\n  Propagate RB OOS mode to TB and TB failed state to RB – Propagate Failsafe state of AP to RB(also propagate RB OOS mode to TB)"             \
  "\n  Do not propagate – Not propagate Failsafe state of AP to RB(also not propagate RB OOS mode to TB)"     \
  "\n  Propagate TB failed state to RB – Propagate Failsafe state of AP to RB(but not propagate RB OOS mode to TB)"          \

#define LBL_ALERT_LOG  "|en|Alert Log"

#define HLP_ALERT_LOG                       \
  "|en|access alert logs from the device"

#define LBL_ALERT_COMMAND  "|en|Alert Log Command"

#define HLP_ALERT_COMMAND																\
  "|en|Command (Write) / Status (Read). The Value written to this field forces the"		\
  " Alert Log API to execute the following functions; note, that for WRITE"				\
  " operations this field is interpreted as a Command."									\
  " \n0x00 – Copy the Alert Log into the READ Buffer and Reset the read index on READ"	\
  " access. When the Read Alert Log parameter is then executed the Alert Log Entry"		\
  " if populated with the first Alert Log array entry. The subsequent READ"				\
  " operations will populate the Alert Log Entry with the next entry, and so"			\
  " forth.The Command / Status field will return the number of entries in teh Alert"	\
  " Log."																				\
  " \n0xFA – Writing this value will clear the AlertLog Table completely, including"	\
  " the NVRAMstorage.On READ operation returns the number ofAlert Log Entries, if"		\
  " the data read is valid; or returns 0 if the data entry is NOT valid."				\
  " \nNote: during READ operation the Command / Status field is Status. It contains"	\
  " the number of the Alert entries in the Alert Log. 0 - indicates No Entries. MAX"	\
  " number of Alert entries in the Alert Log is 32."									\

#define LBL_ALERT_DATA  "|en|Alert Data"

#define HLP_ALERT_DATA                      \
  "|en|Contains current state of all alerts"

#define LBL_DIAGNOSTIC_CONFIGURATION "|en|Diagnostic Configuration"                \

#define HLP_DIAGNOSTIC_CONFIGURATION "|en|"                                        \

#define LBL_DIAGNOSTIC_DATA "|en|Diagnostic Data"                                  \

#define HLP_DIAGNOSTIC_DATA \
  "|en|An array that will contain the data collected during the diagnostic procedure" \
  " execution.\n" \
  "[0] - Contains the offset in bytes of the data to read from the beginning of the" \
  " diagnostic data buffer, This is the only writable value in the array and may be" \
  " used to initiate the read procedure, by writing 0. The value will be" \
  " autoincremented after each read of the array with sub-index 0.\n" \
  "[1] - Skip count - number of points skipped for each point read"  \
  "[2] - Data Sample Count - number of valid points read from the FW" \
  "   [3] - [26] - Diagnostic Data chunk. It will contain data pairs (" \
  "possition/pressure pairs or position/setpoint pairs)as follows e.g.:\n" \
  "   [3]-1st possition integer [4] - 1st Pressure integer\n" \
  "   [5]-2nd possition integer [6] - 2nd Pressure integer ...\n" \
  "Note that the first record of the buffer will have some informatoin about the" \
  " results fo the procedure, including:\n" \
  "    - Procedure being executed\n" \
  "    - Confuguraton used for the procedure\n" \
  "    - number of data points\n" \
  "    - starting and ending position\n" \
  "    - other parameters specific to the test\n" \
  "see the UC25 document for details of the headers for various tests" \

#define LBL_START_POSITION      "|en|Start Position"

#define HLP_START_POSITION \
  "|en|Applicable to: All Start position for the test. May be above or below End" \
  " position Range is -5 to full open +5" \
  "\nStart and End Positions must be more than 20% different" \

#define LBL_END_POSITION        "|en|End Position"

#define HLP_END_POSITION \
  "|en|Applicable to: All Start position for the test. May be above or below" \
  " End position" \

#define LBL_NUMBER_OF_POINTS    "|en|Number Of Points"

#define HLP_NUMBER_OF_POINTS    "|en|"

#define LBL_SPEED               "|en|Speed"

#define HLP_SPEED               "|en|"

#define LBL_DIRECTION           "|en|Direction"

#define HLP_DIAG_DIRECTION  \
  "|en|Applicable to: Diagnostic signature, Ramp test\n" \
  "0. Both ways (from Start position to End position and back)\n" \
  "1. One way (from Start position to End position)" \

#define LBL_DIAG_OPTION         "|en|Diagnostic Option"

#define HLP_DIAG_OPTION \
  "|en|Applicable to: Diagnostic signature\n" \
  "0. Open loop\n" \
  "1. Closed loop"   \

#define LBL_DIAG_TIME         "|en|Time"

#define HLP_DIAG_TIME         "|en|Time(s)"

#define LBL_DISCRETE_INPUT "|en|Discrete Input"

#define HLP_DISCRETE_INPUT                                              \
  "|en|Discrete Input - The state of the external DI switch to FF"      \

#define LBL_MANUAL_SETPOINT "|en|Manual Setpoint"

#define LBL_SET_POINT_RATE "|en|Set Point Rate"

#define HLP_SET_POINT_RATE \
  "|en|Applicable to: Ramp test and Signatures 0.5-100.1 %/s " \

#define LBL_SAMPLING_TIME "|en|Sampling Time"

#define HLP_SAMPLING_TIME \
  "|en|Applicable to: Step test 2 to 60 s." \

#define LBL_AGGRESSIVENESS "|en|Aggressiveness" \

#define HLP_AGGRESSIVENESS                              \
  "|en|Aggressiveness of the Auto Tune Procedure:"      \
  "\n -9 :: Relaxed"                                    \
  "\n 0 :: Normal (Default)"                            \
  "\n +9 :: Aggressive"                                 \

#define LBL_TUNE_FLAGS "|en|Tune Flags"

#define HLP_TUNE_FLAGS                                  \
  "|en|Preserved for future use."                       \

#define LBL_COMPLETION "|en|Completion"

#define HLP_COMPLETION "|en|Completion." \
  "|en|Writing" \
  "\n   1::Starts the autotune process" \
  "\n  99::Cancels the process" \
  "\nReading" \
  "\n 100::Running" \
  "\n   0 :: Not Run or Success" \
  "\nor" \
  "\nCompletion value:" \
  "\n   31 :: Failed actuation" \
  "\n   32 :: Control limits protected" \
  "\n   33 :: Failed open loop tuning" \
  "\n   45 :: P gain below limit" \
  "\n   46 :: P gain adjustment above limit" \
  "\n   55 :: Bias out of range" \
  "\n   66 :: Fill time exceeded" \
  "\n   77 :: Exhaust time exceeded" \

#define LBL_CHARACTER_TYPE                            "|en|Type"

#define HLP_CHARACTER_TYPE                                                                    \
  "|en| Characteristic conversion type:"                                                \
  "\n 0. Linear"                                                                        \
  "\n 1. Equal Percentage (30:1)"                                                       \
  "\n 2. Equal Percentage (50:1)"                                                       \
  "\n 3. Quick Open (reversal from Equal Percentage (50:1))"                            \
  "\n 4. Custom"                                                                        \
  "\n 5. Camflex Percentage"                                                            \
  /* "\n 255. Activate Custom (Defined in CUSTOM_CHAR.CUSTOM_CHAR_POINTS)" */                \

#define LBL_CHAR_SEL_NUMBER_OF_POINTS                "|en|Number Of Points"

#define HLP_CHAR_SEL_NUMBER_OF_POINTS                                                        \
  "|en| Number of valid CURRENT_CHAR_POINTS (depends on the curve selected)"             \

#define LBL_CURRENT_CHAR_POINTS             "|en|Current Char Points"

#define HLP_CURRENT_CHAR_POINTS                                                         \
  "|en|Actual characterization curve setpoint to position, valid up to"                 \
  " CHAR_SELECTION.NUMBER_OF_POINTS."                                                    \
  "\n  Note that 16384 is equivalent to 100% and 0 to 0%, and endpoints (0,0) and"      \
  " (16384,16384) are implied and are not shown in the curve. The DD and"               \
  " configuration tools must do the conversion."                                        \

#define LBL_ACT_STYLE "|en|Actuator Type" \

#define HLP_ACT_STYLE                                                                   \
  "|en| The actuator Style"                                                             \
  "\n0: Double Acting" \
  "\n1: Single Acting" \

#define LBL_POINT_CLOSED "|en|Point Closed" \

#define HLP_POINT_CLOSED  \
  "|en|Define the threshold for the valve position to be closed" \
  "\n the range for this value is from -5 to +20" \

#define LBL_POSITION_HIHI_POINT "|en|POSITION HIHI Point" \

#define HLP_POSITION_HIHI_POINT  \
  "|en|POSITION Value, above which the ALERT will be set to True.  Should be set" \
  " above POSITION_HI_ALERT.ALERT_POINT. The range is [0, 12000]" \

#define LBL_POSITION_HIHI_DEADBAND "|en|Deadband" \

#define HLP_POSITION_HIHI_DEADBAND  \
  "|en|POSITION change, required to clear the ALERT, once it was set to True" \
  " The range is [0.1, 1000]" \

#define LBL_POSITION_HI_POINT   "|en|Alert HI Point" \

#define HLP_POSITION_HI_POINT \
  "|en|POSITION Value, above which the ALERT will be set to True.  Should be set" \
  " above POSITION_LO_ALERT.ALERT_POINT. The range is [0, 12000]" \

#define LBL_POSITION_HI_DEADBAND "|en|Deadband" \

#define HLP_POSITION_HI_DEADBAND  \
  "|en|POSITION change, required to clear the ALERT, once it was set to True" \
  " The range is [0.1, 1000]" \

#define LBL_POSITION_LO_POINT   "|en|Alert LO Point" \

#define HLP_POSITION_LO_POINT \
  "|en|POSITION Value, below which the ALERT will be set to True.  Should be set" \
  " below POSITION_HI_ALERT.ALERT_POINT. The range is [-5000, 10000]" \

#define LBL_POSITION_LO_DEADBAND "|en|Deadband" \

#define HLP_POSITION_LO_DEADBAND  \
  "|en|POSITION change, required to clear the ALERT, once it was set to True" \
  " The range is [0.1, 1000]" \

#define LBL_POSITION_LOLO_POINT   "|en|Alert LOLO Point" \

#define HLP_POSITION_LOLO_POINT \
  "|en|POSITION Value, below which the ALERT will be set to True.  Should be set" \
  " below POSITION_LO_ALERT.ALERT_POINT. The range is [-5000, 10000]" \


#define HLP_FINAL_VALUE                                                                   \
  "|en| The requested valve position, written by the AO FB"                             \

#define LBL_VALUE_D  "|en|Value" \

#define HLP_VALUE_DINT                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Complete close"                                                               \
  "\n 1-100 - Discrete value of the setpoint in increments of %"                        \
  "\nAll other values will be rejected with a status - Out of Range"                    \

#define HLP_VALUE_D                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Close"                                                                        \
  "\n 1 - Open"                                                                         \

#define HLP_ACTIVE_STATE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Inactive"                                                                        \
  "\n 1 - Active"                                                                         \

/*------------------------------------/
** The definitions for label and helps
/------------------------------------*/

#if 0 /*for fine code */
#include "h_ds.h"
#include "r_s.h"
#endif

/*~~~~~~~~~~~~~~~~~~/
*** constant definitions
/~~~~~~~~~~~~~~~~~~*/
#define ENABEL 1
#define DISABLE 0
#define TRIES_CNT 100

#define FINDSTOPS_START                         1
#define FINDSTOPS_CANCEL                        2
#define FINDSTOPS_SETCLOSED                     3
#define FINDSTOPS_SETOPEN                       4
#define FINDSTOPS_ACCEPT                        5
#define FINDSTOPS_COMMIT                        6
#define FINDSTOPS_NOTRUNNING                    0
#define FINDSTOPS_RUNNING                       11

#define FINDSTOPS_MANUL_LO_HI                   43

#define CAL_TYPE_NOT_CALIBRATED                 0
#define CAL_TYPE_CLOSED_ENDPOINT_MANUAL         1
#define CAL_TYPE_OPEN_ENDPOINT_MANUAL           2
#define CAL_TYPE_BOTH_ENDPOINTS_MANUAL          3
#define CAL_TYPE_BOTH_ENDPOINTS_AUTOMATIC       4
#define CAL_TYPE_CLONE							5
#define CAL_TYPE_READY_CLONE					43

#define CAL_RESULT_FAILED_NO                    0
#define CAL_RESULT_SUCCESS                      1

#define DIAG_DIRECTION_ONE                      0x01
#define DIAG_DIRECTION_BOTH                     0x00
#define DIAG_OPTION_OPEN_LOOP                   0x00
#define DIAG_OPTION_CLOSED_LOOP                 0x01
#define SWITCH_OPEN                             0x01
#define SWITCH_CLOSE                            0x00
#define AO_VAL_SP_STATUS                        0xC0
#define AO_VAL_SP_VALUE                         0.0
#define DO_VAL_SP_D_STATUS                      0xC0
#define DO_VAL_SP_D_VALUE                       0
#define PID_VAL_SP_STATUS                       0xC0
#define PID_VAL_SP_VALUE                        0.0
#define _32_SPACES                    "                                "

#define AUTOTUNE_START                         1
#define AUTOTUNE_CANCEL                        99
#define AUTOTUNE_RUNNING                       100
#define AUTOTUNE_NOT_RUN_OR_SUCCESS            0
#define AUTOTUNE_FAILED_ACTUATION              31
#define AUTOTUNE_CONTROL_LIMITS_PROTECTED      32
#define AUTOTUNE_FAILED_OPEN_LOOP_TUNING       33
#define AUTOTUNE_P_GAIN_BELOW_LIMIT            45
#define AUTOTUNE_P_GAIN_ADJUSTMENT_ABOVE_LIMIT 46
#define AUTOTUNE_BIAS_OUT_OF_RANGE             55
#define AUTOTUNE_FILL_TIME_EXCEEDED            66
#define AUTOTUNE_EXHAUST_TIME_EXCEEDED         77
#define AUTOTUNE_OUT_OF_RANGE                  88

#define CHANGE_SETUP     0x00
#define CHANGE_MANUAL    0x01
#define CHANGE_FAILSAFE  0x02
#define CHANGE_NORMAL    0x03

#define SVI2_DBL_ACT             0x00
#define SVI2_SNGL_ACT            0x01

#define NO_PROCESS_RUNING        0x00
#define NBRS_CHAR_ARRAY          38

#define CLEAR_CURRENT_STATUS     1
#define CLEAR_ALL_STATUS         2

/*~~~~~~~~~~~~~~~~~~/
*** re-fined Labels
/~~~~~~~~~~~~~~~~~~*/

#define LBL_ACTION                       "|en|Action"
#define LBL_ACTUATOR_A_MAX               "|en|Actuator A Max"
#define LBL_ACTUATOR_A_MIN               "|en|Actuator A Min"
#define LBL_ACTUATOR_B_MAX               "|en|Actuator B Max"
#define LBL_ACTUATOR_B_MIN               "|en|Actuator B Min"
#define LBL_ACT_EFFECTIVE_AREA           "|en|Act Effective Area"
#define LBL_ACT_FAIL_ACTION              "|en|Act Fail Action"
#define LBL_ACT_MAN_ID                   "|en|Act Man ID"
#define LBL_ACT_MODEL_NUM                "|en|Act Model Num"
#define LBL_ACT_ROTARY_MOMENT_ARM        "|en|Act Rotary Moment Arm"
#define LBL_ACT_SIZE                     "|en|Act Size"
#define LBL_ACT_SN                       "|en|Act SN"
#define LBL_ACT_TYPE                     "|en|Act Type"
#define LBL_AIR_SUPPLY_ALERT             "|en|Air Supply Alert"
#define LBL_ALERT_POINT_CURRENT_LO       "|en|Alert Point"
#define LBL_ALERT_POINT_PRESS_HI         "|en|Alert Point"
#define LBL_ALERT_POINT_PRESS_LO         "|en|Alert Point"
#define LBL_ALERT_POINT_TEMP_HI          "|en|Alert Point"
#define LBL_ALERT_POINT_TEMP_LO          "|en|Alert Point"
#define LBL_ALERT_POINT_TIME             "|en|Alert Point"
#define LBL_APP                          "|en|App"
#define LBL_BODY_SIZE                    "|en|Body Size"
#define LBL_CAL_DATE                     "|en|Cal Date"
#define LBL_CAL_LOCATION                 "|en|Cal Location"
#define LBL_CAL_TYPE                     "|en|Cal Type"
#define LBL_CAL_WHO                      "|en|Cal Who"
#define LBL_CHARACTERISTIC               "|en|Characteristic"
#define LBL_COMMISSIONING_ALERT          "|en|Commissioning Alert"
#define LBL_WORKING_TIME_ALERT           "|en|Control Time Alert"
#define LBL_CURRENT                      "|en|Current"
#define LBL_CYCLE_COUNTER_A_ALERT        "|en|Cycle Counter A Alert"
#define LBL_CYCLE_COUNTER_B_ALERT        "|en|Cycle Counter B Alert"
#define LBL_DATE                         "|en|Date"
#define LBL_DEADBAND_PRESS               "|en|Deadband"
#define LBL_DEADBAND_TEMP                "|en|Deadband"
#define LBL_DECIMAL_2                    "|en|Decimal"
#define LBL_DECIMAL_3                    "|en|Decimal"
#define LBL_DESCRIPTOR                   "|en|Descriptor"
#define LBL_DEVIATION_ALERT              "|en|Deviation Alert"
#define LBL_ENABLE_HI                    "|en|Enable HI"
#define LBL_ENABLE_LO                    "|en|Enable LO"
#define LBL_ENABLE_RATE_HI               "|en|Enable Rate HI"
#define LBL_ENABLE_RATE_LO               "|en|Enable Rate LO"
#define LBL_FF                           "|en|FF"
#define LBL_FINAL_POS_VALUE_MAX          "|en|Final Pos Value Max"
#define LBL_FINAL_POS_VALUE_MIN          "|en|Final Pos Value Min"
#define LBL_FINAL_VALUE_MAX              "|en|Final Value Max"
#define LBL_FINAL_VALUE_MIN              "|en|Final Value Min"
#define LBL_FLOW_ACTION                  "|en|Flow Action"
#define LBL_HAND_WHEEL                   "|en|Hand Wheel"
#define LBL_IP_CURRENT_MAX               "|en|IP Current Max"
#define LBL_IP_CURRENT_MIN               "|en|IP Current Min"
#define LBL_IP_DRIVE_CURRENT_ALERT_HI    "|en|IP Drive Current Alert HI"
#define LBL_IP_DRIVE_CURRENT_ALERT_LO    "|en|IP Drive Current Alert LO"
#define LBL_LAST_RESULT                  "|en|Last Result"
#define LBL_LEAKAGE_CLASS                "|en|Leakage Class"
#define LBL_LIMITS_PROTECTED             "|en|Limits Protected"
#define LBL_LIMIT_HI                     "|en|Limit Value,%"
#define LBL_LIMIT_LO                     "|en|Limit Value,%"
#define LBL_LIMIT_RATE                   "|en|Setpoint Limit Rate"
#define LBL_LOCK_LEVEL                   "|en|Lock Level"
#define LBL_MANUFACTURER                 "|en|Manufacturer"
#define LBL_MESSAGE                      "|en|Message"
#define LBL_MODEL                        "|en|Model"
#define LBL_NEAR_CLOSED                  "|en|Near Closed"
#define LBL_NEAR_CLOSE_ALERT             "|en|Near Close Alert"
#define LBL_NUMBER_OF_POINTS_CUSTOM_CHAR "|en|Number Of Points"
#define LBL_PACKING                      "|en|Packing"
#define LBL_PASSWORD                     "|en|Password"
#define LBL_PASSWORD_ENABLED             "|en|Password Enabled"
#define LBL_PERCENT_COMPLETE             "|en|Percent Complete"
#define LBL_PID_NO                       "|en|Pid No"
#define LBL_PILOT_MAX                    "|en|Pilot Max"
#define LBL_PILOT_MIN                    "|en|Pilot Min"
#define LBL_PLUG_TYPE                    "|en|Plug Type"
#define LBL_POSITION_HIHI_ALERT          "|en|Position Hihi Alert"
#define LBL_POSITION_HI_ALERT            "|en|Position HI Alert"
#define LBL_POSITION_LOLO_ALERT          "|en|Position Lolo Alert"
#define LBL_POSITION_LO_ALERT            "|en|Position LO Alert"
#define LBL_PROCESSOR_ALERT              "|en|Processor Alert"
#define LBL_PROCESS_ID                   "|en|Process ID"
#define LBL_QTY                          "|en|Qty"
#define LBL_RATED_ADJ_CV                 "|en|Rated Adj CV"
#define LBL_RELAY_TYPE                   "|en|Relay Type"
#define LBL_SAME_AS_ACTUATOR             "|en|Same As Actuator"
#define LBL_SEAT_RING_TYPE               "|en|Seat Ring Type"
#define LBL_SELECTOR                     "|en|Selector"
#define LBL_SENSOR_FAILURE_ALERT         "|en|Sensor Failure Alert"
#define LBL_SERVICE                      "|en|Service"
#define LBL_SET_POINT_TIMEOUT_ALERT      "|en|Setpoint Timeout Alert"
#define LBL_SHUTOFF_DP                   "|en|Shutoff DP"
#define LBL_SINCE_POWERUP                "|en|Since Powerup"
#define LBL_SINCE_RESET                  "|en|Since Reset"
#define LBL_SOLENOID                     "|en|Solenoid"
#define LBL_REMOTE_SENSOR                "|en|Remote Sensor"
#define LBL_SPEC_SHEET                   "|en|Spec Sheet"
#define LBL_STOP_HI_POS                  "|en|Stop HI Pos"
#define LBL_STOP_LO_POS                  "|en|Stop LO Pos"
#define LBL_SUPPLY_PRESSURE_HI_ALERT     "|en|Supply Pressure HI Alert"
#define LBL_SUPPLY_PRESSURE_LOLO_ALERT   "|en|Supply Pressure Lolo Alert"
#define LBL_SUPPLY_PRESSURE_LO_ALERT     "|en|Supply Pressure LO Alert"
#define LBL_SUPPLY_PRESSURE_MAX          "|en|Supply Pressure Max"
#define LBL_SUPPLY_PRESSURE_MIN          "|en|Supply Pressure Min"
#define LBL_SUPPORTING_HARDWARE_ALERT    "|en|Supporting Hardware Alert"
#define LBL_TEMPERATURE_HI_ALERT         "|en|Temperature HI Alert"
#define LBL_TEMPERATURE_LO_ALERT         "|en|Temperature LO Alert"
#define LBL_TEMPERATURE_MAX              "|en|Temperature Max"
#define LBL_TEMPERATURE_MIN              "|en|Temperature Min"
#define LBL_TIME                         "|en|Time"
#define LBL_TOTAL_TIME                   "|en|Total Time"
#define LBL_ALERT_TOTAL_TIME             "|en|Alert Total Time"
#define LBL_TRAVEL_ACCUMULATION_A_ALERT  "|en|Travel Accumulation A Alert"
#define LBL_TRAVEL_ACCUMULATION_B_ALERT  "|en|Travel Accumulation B Alert"
#define LBL_UNITS_INDEX_PERCENT          "|en|Units Index"
#define LBL_UNITS_INDEX_PRESS            "|en|Units Index"
#define LBL_UNITS_INDEX_TRAVEL           "|en|Units Index"
#define LBL_VALUE_IP                     "|en|Value"
#define LBL_VALUE_OPEN_CLOSE             "|en|Value"
#define LBL_VALVE_CONTROL_ALERT          "|en|Valve Control Alert"
#define LBL_VALVE_MAN_ID                 "|en|Valve Man ID"
#define LBL_VALVE_MODEL_NUM              "|en|Valve Model Num"
#define LBL_VALVE_SN                     "|en|Valve SN"
#define LBL_VALVE_TYPE                   "|en|Valve Type"
#define LBL_WORKING_POS_MAX              "|en|Working Pos Max"
#define LBL_WORKING_POS_MIN              "|en|Working Pos Min"
#define LBL_WORKING_SP_MAX               "|en|Working SP Max"
#define LBL_WORKING_SP_MIN               "|en|Working SP Min"
#define LBL_RAW_POSITION "|en|Raw Position"
#define LBL_FSTATE_VALUE "|en|FSTATE Value,%"
#define LBL_FSTATE_TIME  "|en|FSTATE Time,s"
#define LBL_ADVANCED     "|en|Advanced"
/*~~~~~~~~~~~~~~~~~/
*** re-fined Helps
/~~~~~~~~~~~~~~~~~*/

#define HLP_ACTION                                                                \
  "|en| Action on Characterization points:"                                       \
  "\n 0. Initialize with Linear"                                                  \
  "\n 1. Initialize with Equal Percentage (30:1)"                                 \
  "\n 2. Initialize with Equal Percentage (50:1)"                                 \
  "\n 3. Initialize with Quick Open (reversal from Equal Percentage (50:1))"      \
  "\n 4. Initialize with Custom"                                                  \
  "\n 5. Initialize with Camflex Percentage"                                      \
  "\n 7. Initialize with Current"                                                 \
  "\n 255. No Action "                                                            \

#define HLP_ACT_EFFECTIVE_AREA                                                    \
  "|en| 60"                                                                       \

#define HLP_ACT_FAIL_ACTION                                                       \
  "|en| Condition of the actuator, when the power is lost:"                       \
  "\n 1. Valve Closed - Self-closing (air to open)"                               \
  "\n 2. Valve Open - Self-opening (air to close)"                                \

#define HLP_ACT_MAN_ID                                                            \
  "|en| The actuator manufacturer identification."                                \

#define HLP_ACT_MODEL_NUM                                                         \
  "|en| The actuator model number."                                               \

#define HLP_ACT_ROTARY_MOMENT_ARM                                                 \
  "|en| n/a"                                                                      \

#define HLP_ACT_SIZE                                                              \
  "|en| 6"                                                                        \

#define HLP_ACT_SN                                                                \
  "|en| The actuator serial number."                                              \

#define HLP_ACT_TYPE                                                              \
  "|en| Actuator Type. Default value shall be Spring-diaphragm"                   \

#define HLP_AIR_SUPPLY_ALERT                                                      \
  "|en| See above for deviation alert"                                            \

#define HLP_ALERT_POINT_CNT                                                       \
  "|en| CYCLE_COUNTER Value, above which the ALERT_POINT will set the ALERT to"   \
  " True"                                                                          \

#define HLP_ALERT_POINT_TIME                                                      \
  "|en| Value in hours, above which will set the ALERT to True"  /*Spec. V15*/    \

#define HLP_ALERT_POINT_PRESS_HI                                                  \
  "|en| SUPPLY_PRESSURE Value, above which the ALERT will be set to True"         \

#define HLP_ALERT_POINT_PRESS_LO                                                  \
  "|en| SUPPLY_PRESSURE Value, below which the ALERT will be set to True"         \

#define HLP_ALERT_POINT_TEMP_HI                                                   \
  "|en| TEMPERATURE Value, above which the ALERT will be set to True"             \

#define HLP_ALERT_POINT_TEMP_LO                                                   \
  "|en| TEMPERATURE Value, below which the ALERT will be set to True"             \

#define HLP_ALERT_POINT_CURRENT_LO                                                \
  "|en| When the CURRENT Value is below ALERT POINT, the ALERT will be set to"    \
  " True"                                                                          \

#define HLP_APP                                                                   \
  "|en| Valve Control related Failed State"                                       \
  "\n 0 - No active Valve Control Failed State condition exists"                  \
  "\n 1 - Failed State Condition is detected in the Valve Control"                \

#define HLP_BODY_SIZE                                                             \
  "|en| Body Size"                                                                \

#define HLP_CAL_DATE                                                              \
  "|en| The date of the last positioner calibration."                             \

#define HLP_CAL_LOCATION                                                          \
  "|en| The location of last positioner calibration. This describes the physical" \
  " location at which the calibration was performed. (ex. “NIST”, “Acme Labs”)."   \

#define HLP_CAL_TYPE                                                              \
  "|en| Last Calibration Type:"                                                   \
  "\n 0. Not Calibrated"                                                          \
  "\n 1. Closed Endpoint(Manual)"                                                 \
  "\n 2. Open Endopoint(Manual)"                                                  \
  "\n 3. Both Endpoints(Manual)"                                                  \
  "\n 4. Both Endpoints(Automatic)"                                               \
  "\n 5. Clone" \
  "\n 43. Ready to Clone" \
  "\nWill be set when the calibration procedure is invoked."                      \

#define HLP_CAL_WHO                                                               \
  "|en| The name of the person responsible for the last positioner calibration."  \

#define HLP_CHARACTERISTIC                  "|en|"                                \

#define HLP_COMMISSIONING_ALERT                                                   \
  "|en| See above for deviation alert"                                            \

#define HLP_WORKING_TIME_ALERT                                                    \
  "|en| See above for deviation alert"                                            \

#define HLP_CURRENT                                                               \
  "|en| Current IP DRIVE CURRENT value"                                           \

#define HLP_CYCLE_COUNTER_A_ALERT                                                 \
  "|en| See above for deviation alert"                                            \

#define HLP_CYCLE_COUNTER_B_ALERT                                                 \
  "|en| See above for deviation alert"                                            \

#define HLP_DATE                            "|en|"                                \

#define HLP_DEADBAND_PRESS                                                        \
  "|en| SUPPLY_PRESSURE change, required to clear the ALERT, once it was set to"  \
  " True"                                                                          \

#define HLP_DEADBAND_TEMP                                                         \
  "|en| TEMPERATURE change, required to clear the ALERT, once it was set to"      \
  " True"                                                                          \

#define HLP_DECIMAL_2                                                             \
  "|en| 2"                                                                        \

#define HLP_DECIMAL_3                                                             \
  "|en| 3"                                                                        \

#define HLP_DESCRIPTOR                      "|en|"                                \

#define HLP_DEVIATION_ALERT                                                       \
  "|en| The user shall be able to select one of the following:"                   \
  "\n 0 :: Not Reported"                                                          \
  "\n 1 :: Warning Data"                                                          \
  "\n 2 :: Maintenance Required"                                                  \
  "\n 3 :: Device Failure"                                                        \

#define HLP_ENABLE_HI                                                             \
  "|en| Position Limit HI enabled"                                                \

#define HLP_ENABLE_LO                                                             \
  "|en| Position Limit LO enabled"                                                \

#define HLP_ENABLE_RATE_HI                                                        \
  "|en| Setpoint Rate Limit enabled, when setpoint is higher"                     \

#define HLP_ENABLE_RATE_LO                                                        \
  "|en| Setpoint Rate Limit enabled, when setpoint is lower"                      \

#define HLP_FF                                                                    \
  "|en| FF related failed State"                                                  \
  "\n 1 - FAILED_STATE is reported to the Resource Block"                         \
  "\n 0 - No FAILED STATE condition exists"                                       \

#define HLP_FLOW_ACTION                     "|en|"                                \

#define HLP_HAND_WHEEL                                                            \
  "|en| -"                                                                        \

#define HLP_IP_DRIVE_CURRENT_ALERT_HI                                             \
  "|en| See above for deviation alert"                                            \

#define HLP_IP_DRIVE_CURRENT_ALERT_LO                                             \
  "|en| See above for deviation alert"                                            \

#define HLP_LAST_RESULT                                                           \
  "|en| Last Calibration Type:"                                                   \
  "\n 0. No or Failed Calibration"                                                \
  "\n 1. Successful Calibration"                                                  \
  "\nWill be set when the calibration procedure is invoked."                      \

#define HLP_LEAKAGE_CLASS                   "|en|"                                \

#define HLP_LIMITS_PROTECTED                                                      \
  "|en| Position Limits change is restricted"                                     \

#define HLP_LIMIT_HI                                                              \
  "|en| Position Limit HI Point"                                                  \

#define HLP_LIMIT_LO                                                              \
  "|en| Position Limit LO Point"                                                  \

#define HLP_LIMIT_RATE                                                            \
  "|en| Setpoint Rate Limit "                                                     \

#define HLP_LOCK_LEVEL                      "|en|"                                \

#define HLP_MANUFACTURER                    "|en|"                                \

#define HLP_MESSAGE                         "|en|"                                \

#define HLP_MESSAGE                         "|en|"                                \

#define HLP_MODEL                           "|en|"                                \

#define HLP_NEAR_CLOSED                                                           \
  "|en| Time in hours, the valve spends in near closed position (5%-CLOSED)"      \
  "under control (in Manual, Auto or LO modes)"     /*Spec. V15*/                 \

#define HLP_NEAR_CLOSE_ALERT                                                      \
  "|en| See above for deviation alert"                                            \

#define HLP_NUMBER_OF_POINTS_CUSTOM_CHAR                                          \
  "|en| Selected number of valid CUSTOM_CHAR_POINTS"                              \

#define HLP_PACKING                                                               \
  "|en| String containng the packing - Braided PTFE/Carbon or aramid core"        \

#define HLP_PASSWORD                        "|en|"                                \

#define HLP_PASSWORD_ENABLED                "|en|"                                \

#define HLP_PERCENT_COMPLETE                "|en|"                                \

#define HLP_PID_NO                          "|en|"                                \

#define HLP_PLUG_TYPE                                                             \
  "|en| Linear Contoured"                                                         \

#define HLP_POSITION_HIHI_ALERT                                                   \
  "|en| See above for deviation alert"                                            \

#define HLP_POSITION_HI_ALERT                                                     \
  "|en| See above for deviation alert"                                            \

#define HLP_POSITION_LOLO_ALERT                                                   \
  "|en| See above for deviation alert"                                            \

#define HLP_POSITION_LO_ALERT                                                     \
  "|en| See above for deviation alert"                                            \

#define HLP_PROCESSOR_ALERT                                                       \
  "|en| See above for deviation alert"                                            \

#define HLP_PROCESS_ID                                                          \
  "|en|Enumerated Process ID of the currently running process. Zero when no"   \
  " process is running.\n"                                                       \
  "0 - No Process\n"                                                            \
  "1 - Find Stops process\n"                                                    \
  "4 - Autotune process\n"                                                      \
  "7 - Diagnostic - signature\n"                                                \
  "8 - Step Test\n"                                                             \
  "15 - Ramp Test Diagnostics\n"                                                \
  "24 - Log file to diag buffer\n"                                              \
  "25 - Diagnostic buffer to log file\n"                                        \
  "26 - \"Standard\" NVMEM objects to log file\n"                               \
  "27 - Log file to \"Standard\" NVMEM objects\n"                               \
  "28 - Cancel a process\n"                                                 \

#define HLP_QTY                             "|en|"                                \

#define HLP_RATED_ADJ_CV                    "|en|"                                \

#define HLP_RELAY_TYPE                                                            \
  "|en| Relay Type:"                                                              \
  "\n 1. Relay A or C - Double or Single Direct"                                  \
  "\n 2=Relay B--Single Reverse"                                                  \
  "\n 5=Relay C-Special App. --Single Direct"                                     \
  "\n 6=Relay B-Special App. --Single Reverse"                                    \
  "\n 9=Lo-Bleed Relay A or C--Double or Single Direct"                           \
  "\n 10=Lo-Bleed Relay B-- Single Reverse"                                       \
  "\n 13=Lo-Bleed Relay C-Special App.--Single Direct"                            \
  "\n 10=Lo-Bleed Relay B-Special App.--Single Reverse"                           \

#define HLP_SAME_AS_ACTUATOR                                                      \
  "|en| True if the valve and Actuator information is the same"                   \

#define HLP_SEAT_RING_TYPE                                                        \
  "|en| String containng the ring type - Quick Change"                            \

#define HLP_SELECTOR                        "|en|"                                \

#define HLP_SENSOR_FAILURE_ALERT                                                  \
  "|en| See above for deviation alert"                                            \

#define HLP_SERVICE                         "|en|"                                \

#define HLP_SET_POINT_TIMEOUT_ALERT                                               \
  "|en| See above for deviation alert"                                            \

#define HLP_SHUTOFF_DP                                                            \
  "|en| 100"                                                                      \

#define HLP_SINCE_POWERUP                                                         \
  "|en| Hours since last power up"                                                \

#define HLP_SINCE_RESET                                                           \
  "|en| Hours since last reset"                                                   \

#define HLP_SOLENOID                        "|en|"                                \

#define HLP_REMOTE_SENSOR               \
  "|en|Indicates/Enables the remote sensor connection. The following enumeration" \
  " is available:" \
  "\n 0 :: Remote sensor is disabled/Not Active (read only - write will do" \
  " nothing)" \
  "\n 1 :: Remote sensor is enabled (read only - write will do nothing)" \
  "\n 2 :: Enable Local HAL Sensor (write only - write will do nothing if it is" \
  " already 0)" \
  "\n 3 :: Enable Remote Sensor (write only - write will do nothing if it is" \
  " already 1)" \
  "\nIf the user changed this configuration, please MUST restart device for the" \
  " change to take effect" \

#define HLP_SPEC_SHEET                      "|en|"                                \

#define HLP_STOP_HI_POS                                                           \
  "|en| Calibration Point HI: Will be set when the calibration procedure is"      \
  " invoked.  Provides the temperature compensated position, as reported by the"   \
  " sensor."                                                                       \
  "\nValue is not valid if TRAVEL_CALIBRATION.LAST_RESULT is not Success"         \

#define HLP_STOP_LO_POS                                                           \
  "|en| Calibration Point LO: Will be set when the calibration procedure is"      \
  " invoked. Provides the temperature compensated posiotion, as reported by the"   \
  " sensor.  Value is not valid if TRAVEL_CALIBRATION.LAST_RESULT is not Success"  \

#define HLP_SUPPLY_PRESSURE_HI_ALERT                                              \
  "|en| See above for deviation alert"                                            \

#define HLP_SUPPLY_PRESSURE_LOLO_ALERT                                            \
  "|en| See above for deviation alert"                                            \

#define HLP_SUPPLY_PRESSURE_LO_ALERT                                              \
  "|en| See above for deviation alert"                                            \

#define HLP_SUPPORTING_HARDWARE_ALERT                                             \
  "|en| See above for deviation alert"                                            \

#define HLP_TEMPERATURE_HI_ALERT                                                  \
  "|en| See above for deviation alert"                                            \

#define HLP_TEMPERATURE_LO_ALERT                                                  \
  "|en| See above for deviation alert"                                            \

#define HLP_TIME                                                                  \
  "|en| The user defined allowable duration in seconds of deviation before"       \
  " alert.. The valid range is from 1s to 7FFFFFFFF."                              \
  "\nWhen presented to the user, the value should be in seconds and limited"      \
  " between 1s to 5 minutes (300s)"                                                \

#define HLP_TOTAL_TIME                                                            \
  "|en| Lifetime Hours or time since reseted"                                     \

#define HLP_ALERT_TOTAL_TIME                                                            \
  "|en| Total Number of hours since manufacturing or since reset"                                     \

#define HLP_TRAVEL_ACCUMULATION_A_ALERT                                           \
  "|en| See above for deviation alert"                                            \

#define HLP_TRAVEL_ACCUMULATION_B_ALERT                                           \
  "|en| See above for deviation alert"                                            \

#define HLP_UNITS_INDEX_PERCENT                                                   \
  "|en| Engineering Units at 100. Should be fixed to %(1342)"                     \

#define HLP_UNITS_INDEX_TRAVEL                                                    \
  "|en| Enumeration of the travel Units. The following units shall be supported:" \
  "\n : Inch"                                                                     \
  "\n : cm"                                                                       \
  "\n : mm"                                                                       \
  "\n : deg"                                                                      \
  "\n : Rad"                                                                      \
  "\n : %"                     /*spec V13*/                                       \
  "\nThe Units will have no effect on the application - it will be used to"       \
  " present the units for the working SP"                                          \

#define HLP_UNITS_INDEX_PRESS                                                     \
  "|en| Engineering Units The following values should be available:"              \
  "\n FF code 1133 shall be mapped to 12 :: Kpa"                                  \
  "\n FF code 1141 shall be mapped to 6 :: psi"                                   \
  "\n FF code 1137 shall be mapped to 7 :: BAR"                                   \

#define HLP_VALUE_OPEN_CLOSE                                                      \
  "|en| Value:"                                                                   \
  "\n 0 - Close"                                                                  \
  "\n 1 - Open"                                                                   \

#define HLP_VALUE_IP                                                              \
  "|en|Value in % of IP Current MAX (1.67mA as specified"                         \

#define HLP_VALVE_CONTROL_ALERT                                                   \
  "|en| See above for deviation alert"                                            \

#define HLP_VALVE_MAN_ID                                                          \
  "|en| The valve manufacturer identification."                                   \

#define HLP_VALVE_MODEL_NUM                                                       \
  "|en| The valve model number."                                                  \

#define HLP_VALVE_SN                                                              \
  "|en| The valve serial number"                                                  \

#define HLP_VALVE_TYPE                                                            \
  "|en| The type of the valve.Globe, Reciprocating"                               \
  "\nValve Type – Description"                                                    \
  "\n 0 Undefined"                                                                \
  "\n 1 Linear"                                                                   \
  "\n 2 Rotary"                                                                   \
  "\n 255 Other"                                                                  \
  "\nFISHER: Supports only:"                                                      \
  "\n 1 Sliding-stem"                                                             \
  "\n 2 Rotary"                                                                   \

#define HLP_VALUE_MAX                                                       \
  "|en|Max value since restart or last user update. If <MIN, value has not been GOOD"

#define HLP_VALUE_MIN                                                       \
  "|en|Min value since restart or last user update. If >MAX, value has not been GOOD"

#define HLP_RAW_POSITION "|en|The Raw position."

#define HLP_ADVANCED     "|en|Advanced/Standard implementation for the device."

/*~~~~~~~~~~~~~~~/
*** Help Defines
/~~~~~~~~~~~~~~~*/

#define HLP_043_POSITION_TRANSDUCER_TYPE                                                \
  "|en| Standard Advanced Positioner Valve"                                             \

#define HLP_044_XD_ERROR_POS                                                            \
  "|en| The Following errors can be reported in XD_ERROR parameter:"                    \
  "\n 0 No Error"                                                                       \
  "\n 16 Unspecified error (to be mapped to Other in Block Error"                       \
  "\n 17 General error"                                                                 \
  "\n 18 Calibration error"                                                             \
  "\n 19 Configuration error"                                                           \
  "\n 20 Electronics Failure"                                                           \
  "\n 21 Mechanical Failure"                                                            \
  "\n 22 I/O Failure"                                                                   \
  "\n 23 Data Integrity Error"                                                          \
  "\n 24 Software Error"                                                                \
  "\n 25 Algorithm Error"                                                               \
  "\nWill map the errors reported in COMPLETE_STATUS parameter to this errors"          \

#define HLP_045_FINAL_VALUE                                                             \
  "|en| The requested valve position and status written by an analog Function"          \
  " Block"                                                                               \
  "\nRQ: 10883"                                                                         \
  "\nTasks: 10884, 10885"                                                               \

#define HLP_046_STATUS                                                                  \
  "|en| The status written by the Analog Output FB. Review the"                         \
  " UC4_SetPointState"                                                                   \

#define HLP_048_FINAL_VALUE_RANGE                                                       \
  "|en| The range of the FINAL_VALUE (setpoint) and the FINAL_VALUE_RANGE"              \
  "(actual position)."                                                                  \
  "\nThis parameter is not changeable, so the scale parameter of the Analog"            \
  " Output block DD has to be limited to provide this values only. "                     \

#define HLP_049_EU_100                                                                  \
  "|en| Max Position value at 100%. Should be fixed to 100."                            \

#define HLP_050_EU_0                                                                    \
  "|en| Min Position value at 100%.Should be fixed to 0."                               \

#define HLP_053_POSITION_LIMITS                                                         \
  "|en| Position Limits" \

#define HLP_062_FINAL_VALUE_CUTOFF_HI                                                   \
  "|en| If the FINAL_VALUE is more positive than this value, the valve is forced"       \
  " to its maximum high value (fully opened)."                                           \
  "\nRange: FINAL_VALUE_RANGE, +INF"                                                    \
  "\nFISHER: -25 to 125, initial 99.5"                                                  \

#define HLP_064_CUTOFF_POINT_HI                                                         \
  "|en| Cut-Off point HI. Valve will be fully open to after this point"                 \

#define HLP_065_FINAL_VALUE_CUTOFF_LO                                                   \
  "|en| If the FINAL_VALUE is more negative than this value, the valve is forced"       \
  " to its maximum low value (fully closed)."                                            \
  "\nRange: FINAL_VALUE_RANGE, +INF"                                                    \
  "\nFISHER: -25 to 125, initial 0.5"                                                   \

#define HLP_067_CUTOFF_POINT_LO                                                         \
  "|en| Cut-Off point HI. Valve will be fully closed to after this point"               \

#define HLP_068_FINAL_POSITION_VALUE                                                    \
  "|en| The actual valve position and status, could be used at the"                     \
  " READBACK_VALUE in an AO block."                                                      \

#define HLP_069_STATUS                                                                  \
  "|en| Bad - Out of service: The block is in the O/S mode."                            \
  "\n Bad - Sensor failure: The position sensor has failed."                            \
  "\n Bad - Device failure: The A/D converter has failed."                              \
  "\n Bad - Non specific: The deviation exceeds the limit."                             \

#define HLP_070_VALUE                           "|en|"                                  \

#define HLP_071_ACTIVATE_CONTROL_SET                                                    \
  "|en| Allows to copy the Working Control Set or the Backup Control Set to the"        \
  " Active control set. The following commands are available:"                           \
  "\n 0 :: Activate Custom Control Set"                                                 \
  "\n 1 :: Activate Control Set 1(Slowest)"                                                      \
  "\n 2 :: Activate Control Set 2"                                                      \
  "\n 3 :: Activate Control Set 3"                                                      \
  "\n 4 :: Activate Control Set 4"                                                      \
  "\n 5 :: Activate Control Set 5(Fastest)"                                                      \
  "\n 6 :: Activate Control Set 6(Double Acting-Slow)"                                                      \
  "\n 7 :: Activate Control Set 7(Double Acting-Fast)"                                                      \
  "\n"                                                                                  \
  "\n 10 :: Restore Control set (make Backup Control Set Active)"                       \
  "\n 11 :: Make active control set as Custom control set"                              \
  "\n 255:: Do Nothing"                                                                 \
  "\n"                                                                                  \

#define HLP_072_ACTIVE_CONTROL_SET                                                      \
  "|en|Coefficients of the valve control algorithm"   \
  "\n SERVO_GAIN"                                                                       \
  "\n SERVO_RESET"                                                                      \
  "\n SERVO_RATE"                                                                       \
  "\nThis parameter contains the control parameters currently used by the"              \
  " positioner."                                                                         \

#define HLP_073_P                               "|en|"                                  \

#define HLP_074_I                               "|en|"                                  \

#define HLP_075_D                               "|en|"                                  \

#define HLP_076_PADJ                            "|en|"                                  \

#define HLP_077_BETA                            "|en|"                                  \

#define HLP_078_POSCOMP                         "|en|"                                  \

#define HLP_079_DEADZONE                        "|en|"                                  \

#define HLP_080_NONLIN                          "|en|"                                  \

#define HLP_081_CUSTOM_CONTROL_SET              "|en|"                                  \

#define HLP_082_P                               "|en|"                                  \

#define HLP_083_I                               "|en|"                                  \

#define HLP_084_D                               "|en|"                                  \

#define HLP_085_PADJ                            "|en|"                                  \

#define HLP_086_BETA                            "|en|"                                  \

#define HLP_087_POSCOMP                         "|en|"                                  \

#define HLP_088_DEADZONE                        "|en|"                                  \

#define HLP_089_NONLIN                          "|en|"                                  \

#define HLP_090_BACKUP_CONTROL_SET              "|en|"                                  \

#define HLP_092_P                               "|en|"                                  \

#define HLP_093_I                               "|en|"                                  \

#define HLP_094_D                               "|en|"                                  \

#define HLP_095_PADJ                            "|en|"                                  \

#define HLP_096_BETA                            "|en|"                                  \

#define HLP_097_POSCOMP                         "|en|"                                  \

#define HLP_098_DEADZONE                        "|en|"                                  \

#define HLP_099_NONLIN                          "|en|"                                  \

#define HLP_100_TRAVEL_CALIBRATION                                                      \
  "|en| The location of last positioner calibration. This describes the physical"       \
  " location at which the calibration was performed. (ex. “NIST”, “Acme Labs”)."         \

#define HLP_108_TRAVEL                          "|en|"                                  \

#define HLP_109_RANGE                                                                   \
  "|en| A numeric value, describing the Range of travel. Will be used to"               \
  " calculate the Working SetPoint value. "                                              \

#define HLP_111_WORKING_SP                                                              \
  "|en| The final command value to the positioning algorithm after"                     \
  " characterization."                                                                   \

#define HLP_112_STATUS                          "|en|"                                  \

#define HLP_113_VALUE                                                                   \
  "|en| The value will be converted to TRAVEL.UNITS_INDEX" \

#define HLP_114_WORKING_POS                                                             \
  "|en| The actual measured feedback position before de-characterization."              \

#define HLP_115_STATUS                          "|en|"                                  \

#define HLP_116_VALUE                                                                   \
  "|en| The value will be converted to TRAVEL.UNITS_INDEX" \

#define HLP_117_DEVIATION_ALERT                 "|en|"                                  \

#define HLP_118_DEVIATION_VALUE                                                         \
  "|en| Difference between working setpoint and working position. The written"          \
  " value will be overwritten by the algorithm"                                          \

#define HLP_119_ALERT_POINT                                                             \
  "|en| If the DEVIATION VALUE is above ALERT_POINT for deviation TIME, it will"        \
  " set the ALERT to true."                                                              \

#define HLP_120_DEADBAND                                                                \
  "|en| The user defined allowable deviation before alert."                             \

#define HLP_125_POSITION_HIHI_ALERT             "|en|"                                  \

#define HLP_126_POSITION                                                                \
  "|en| Current valve position. Presented here for convenience"                         \

#define HLP_127_ALERT_POINT                                                             \
  "|en| POSITION Value, above which the ALERT will be set to True.  Should be"          \
  " set above POSITION_HI_ALERT.ALERT_POINT."                                            \

#define HLP_128_DEADBAND                                                                \
  "|en| POSITION change, required to clear the ALERT, once it was set to True"          \

#define HLP_132_POSITION_HI_ALERT               "|en|"                                  \

#define HLP_133_POSITION                                                                \
  "|en| Current valve position. Presented here for convenience"                         \

#define HLP_134_ALERT_POINT                                                             \
  "|en| POSITION Value, above which the ALERT will be set to True.  Should be"          \
  " set above POSITION_LO_ALERT.ALERT_POINT."                                            \

#define HLP_135_DEADBAND                                                                \
  "|en| POSITION change, required to clear the ALERT, once it was set to True"          \

#define HLP_139_POSITION_LO_ALERT               "|en|"                                  \

#define HLP_140_POSITION                                                                \
  "|en| Current valve position. Presented here for convenience"                         \

#define HLP_141_ALERT_POINT                                                             \
  "|en| POSITION Value, below which the ALERT will be set to True. Should be set"       \
  " below POSITION_HI_ALERT.ALERT_POINT"                                                 \

#define HLP_142_DEADBAND                                                                \
  "|en| POSITION change, required to clear the ALERT, once it was set to True"          \

#define HLP_146_POSITION_LOLO_ALERT             "|en|"                                  \

#define HLP_147_POSITION                                                                \
  "|en| Current valve position. Presented here for convenience"                         \

#define HLP_148_ALERT_POINT                                                             \
  "|en| POSITION Value, below which the ALERT will be set to True. Should be set"       \
  " below POSITION_LO_ALERT.ALERT_POINT"                                                 \

#define HLP_149_DEADBAND                                                                \
  "|en| POSITION change, required to clear the ALERT, once it was set to True"          \

#define HLP_154_TRAVEL_ACCUMULATION                                                     \
  "|en| Totalized change in travel in %, since the TRAVEL_ACCUMULATION was"             \
  " cleared. The value will increment when the magnitude of the change exceeds the"      \
  " DEADBAND."                                                                           \

#define HLP_155_ALERT_POINT                                                             \
  "|en| POSITION Value, below which the ALERT will be set to True"                      \

#define HLP_156_DEADBAND                                                                \
  "|en| POSITION change, required to exceed, before the TRAVEL ACCUMULATION is"         \
  " increased"                                                                           \

#define HLP_160_TRAVEL_ACCUMULATION_B_ALERT     "|en|"                                  \

#define HLP_161_TRAVEL_ACCUMULATION                                                     \
  "|en| Totalized change in travel in %, since the TRAVEL_ACCUMULATION was"             \
  " cleared. The value will increment when the magnitude of the change exceeds the"      \
  " DEADBAND."                                                                           \

#define HLP_162_ALERT_POINT                                                             \
  "|en| POSITION Value, below which the ALERT will be set to True"                      \

#define HLP_163_DEADBAND                                                                \
  "|en| POSITION change, required to exceed, before the TRAVEL ACCUMULATION is"         \
  " increased"                                                                           \

#define HLP_167_TRAVEL_ACCUMULATION_TREND                                               \
  "|en| The total change in travel trend. The value will increment when the"            \
  " magnitude of the change exceeds the TRAVEL_ACCUMULATION_ALERT.DEADBAND."             \

#define HLP_168_TODAY                                                                   \
  "|en| Travel accumulation for the current 24 hours period."                           \

#define HLP_169_LAST_DAY                                                                \
  "|en| Travel accumulation for the last full 24 hours period."                         \

#define HLP_170_PREVIOUS_DAY                                                            \
  "|en| Travel accumulation for the previous full 24 hours period."                     \

#define HLP_171_THREE_DAYS_AGO                                                          \
  "|en| Travel accumulation for the previous full 24 hours period."                     \

#define HLP_172_CURRENT_WEEK                                                            \
  "|en| Travel accumulation for the current week"                                       \

#define HLP_173_LAST_WEEK                                                               \
  "|en| Travel accumulation for the last full week"                                     \

#define HLP_174_PREVIOUS_WEEK                                                           \
  "|en| Travel accumulation for the previous week (2 weeks ago)."                       \

#define HLP_175_THREE_WEEKS_AGO                                                         \
  "|en| Travel accumulation 3 weeks ago."                                               \

#define HLP_176_CURRENT_MONTH                                                           \
  "|en| Travel accumulation for the current month period."                              \

#define HLP_177_LAST_MONTH                                                              \
  "|en| Travel accumulation for the last full month period."                            \

#define HLP_178_PREVIOUS_MONTH                                                          \
  "|en| Travel accumulation for the previous full month period."                        \

#define HLP_179_THREE_MONTHS_AGO                                                        \
  "|en| Travel accumulation 3 months ago"                                               \

#define HLP_180_CURRENT_12_MONTHS                                                       \
  "|en| Travel accumulation for the current 12 month period."                           \

#define HLP_181_LAST_12_MONTHS                                                          \
  "|en| Travel accumulation for the last full 12 months"                                \

#define HLP_182_PREVIOUS_12_MONTHS                                                      \
  "|en| Travel accumulation for the previous full 12 months"                            \

#define HLP_183_THREE_YEARS_AGO                                                         \
  "|en| Travel accumulation 3 years ago"                                                \

#define HLP_184_TOTAL                                                                   \
  "|en| Total"                                                                          \

#define HLP_188_DEADBAND                                                                \
  "|en| POSITION change, required to exceed, before the CYCLE_COUNTER is"               \
  " increased"                                                                           \

#define HLP_195_DEADBAND                                                                \
  "|en| POSITION change, required to exceed, before the CYCLE_COUNTER is"               \
  " increased"                                                                           \

#define HLP_199_CYCLE_COUNTER_TREND                                                     \
  "|en| The number of times the travel changes direction. The value will"               \
  " increment when the magnitude of the change exceeds the"                              \
  " CYCLE_COUNTER_ALERT.DEADBAND."                                                       \

#define HLP_200_TODAY                                                                   \
  "|en| Cycles for the current 24 hours period."                                        \

#define HLP_201_LAST_DAY                                                                \
  "|en| Cycles for the last full 24 hours period."                                      \

#define HLP_202_PREVIOUS_DAY                                                            \
  "|en| Cycles for the previous full 24 hours period."                                  \

#define HLP_203_THREE_DAYS_AGO                                                          \
  "|en| Cycles for the previous full 24 hours period."                                  \

#define HLP_204_CURRENT_WEEK                                                            \
  "|en| Cycles for the current week"                                                    \

#define HLP_205_LAST_WEEK                                                               \
  "|en| Cycles for the last full week"                                                  \

#define HLP_206_PREVIOUS_WEEK                                                           \
  "|en| Cycles for the previous week (2 weeks ago)."                                    \

#define HLP_207_THREE_WEEKS_AGO                                                         \
  "|en| Cycles 3 weeks ago."                                                            \

#define HLP_208_CURRENT_MONTH                                                           \
  "|en| Cycles for the current month period."                                           \

#define HLP_209_LAST_MONTH                                                              \
  "|en| Cycles for the last full month period."                                         \

#define HLP_210_PREVIOUS_MONTH                                                          \
  "|en| Cycles for the previous full month period."                                     \

#define HLP_211_THREE_MONTHS_AGO                                                        \
  "|en| Cycles 3 months ago"                                                            \

#define HLP_212_CURRENT_12_MONTHS                                                       \
  "|en| Cycles for the current 12 month period."                                        \

#define HLP_213_LAST_12_MONTHS                                                          \
  "|en| Cycles for the last full 12 months"                                             \

#define HLP_214_PREVIOUS_12_MONTHS                                                      \
  "|en| Cycles for the previous full 12 months"                                         \

#define HLP_215_THREE_YEARS_AGO                                                         \
  "|en| Cycles 3 years ago"                                                             \

#define HLP_216_TOTAL                                                                   \
  "|en| Total"                                                                          \

#define HLP_217_POSITION_ERROR_TREND                                                    \
  "|en| Trend of the position error. "                                                  \

#define HLP_218_TODAY                                                                   \
  "|en| Position Error for the current 24 hours period."                                \

#define HLP_219_LAST_DAY                                                                \
  "|en| Position Error Error for the last full 24 hours period."                        \

#define HLP_220_PREVIOUS_DAY                                                            \
  "|en| Position Error for the previous full 24 hours period."                          \

#define HLP_221_THREE_DAYS_AGO                                                          \
  "|en| Position Error for the previous full 24 hours period."                          \

#define HLP_222_CURRENT_WEEK                                                            \
  "|en| Position Error for the current week"                                            \

#define HLP_223_LAST_WEEK                                                               \
  "|en| Position Error for the last full week"                                          \

#define HLP_224_PREVIOUS_WEEK                                                           \
  "|en| Position Error for the previous week (2 weeks ago)."                            \

#define HLP_225_THREE_WEEKS_AGO                                                         \
  "|en| Position Error 3 weeks ago."                                                    \

#define HLP_226_CURRENT_MONTH                                                           \
  "|en| Position Error for the current month period."                                   \

#define HLP_227_LAST_MONTH                                                              \
  "|en| Position Error for the last full month period."                                 \

#define HLP_228_PREVIOUS_MONTH                                                          \
  "|en| Position Error for the previous full month period."                             \

#define HLP_229_THREE_MONTHS_AGO                                                        \
  "|en| Position Error 3 months ago"                                                    \

#define HLP_230_CURRENT_12_MONTHS                                                       \
  "|en| Position Error for the current 12 month period."                                \

#define HLP_231_LAST_12_MONTHS                                                          \
  "|en| Position Error for the last full 12 months"                                     \

#define HLP_232_PREVIOUS_12_MONTHS                                                      \
  "|en| Position Error for the previous full 12 months"                                 \

#define HLP_233_THREE_YEARS_AGO                                                         \
  "|en| Position Error 3 years ago"                                                     \

#define HLP_234_TOTAL                                                                   \
  "|en| Total"                                                                          \

#define HLP_235_POSITION_HISTOGRAM                                                      \
  "|en| An array of counters, that will count how many macro cycles the valve"          \
  " was in different position segments. The counters should increase only if the"        \
  " device is under control - the transducer block is in AUTO mode and the quality"      \
  " of the set point is GOOD."                                                           \

#define HLP_236_TOTAL                                                                   \
  "|en| Total Working time in seconds or time since the reset fo the values in the"     \
  " histogram."

#define HLP_249_NEAR_CLOSED_ALERT                                                       \
  "|en| The near closed alert will be reported only if the valve had been"              \
  " working with a valid set point and in auto mode for at least 1000 macro cycles"      \
  "(the sum of all counters in POSITION_HISTOGRAM.TOTAL will be more than 1000). "       \
  "Should be enabled only if the thight shut off is not enabled." /*Spec. V15*/    \

#define HLP_255_POSITION_ERROR_HISTOGRAM                                                \
  "|en| An array of counters, that will count how many macro cycles the valve"          \
  " was in different position segments. The values will be calculated only if the"       \
  " device is under control - the transducer block is in AUTO mode and the quality"      \
  " of the set point is GOOD."                                                           \

#define HLP_268_SETPOINT_TIMEOUT_ALERT                                                  \
  "|en| The setpoint update alert will be reported only if the valve setpoint"          \
  " has not been updated by the AO or DO block for more than ALERT_POINT time. "         \

#define HLP_269_TIME_SINCE_UPDATE                                                       \
  "|en| Time since the last update from the AO or DO block."                            \

#define HLP_270_ALERT_POINT                                                             \
  "|en| Value, above which will set the ALERT to True. Note, that this time must"       \
  " be at least 2 times bigger than the macro cycle."                                    \

#define HLP_271_MAX_TIME                                                                \
  "|en| Maximal Time Detected before the setpoint is updated"                           \

#define HLP_275_XD_FSTATE                       "|en|"                                  \

#define HLP_XD_FS_CONFIGURATION                                        \
  "|en| Defines the source for configuration:"                                          \
  "\n 1 :: Analog output block/Discrete Output block"                                   \
  "\n 2 :: Independent Configuration"                                                   \

#define HLP_XD_FSTATE_OPT                                                           \
  "|en| Defines an action to be taken on a transducer fault state."                     \
  "\n 0: Hold Last Value"                                                               \
  "\n 1: Fail Closed"                                                                   \
  "\n 2: Fail Open"                                                                     \
  "\n 3: XD_FSTATE_VAL"                                                                 \
  "\n 4-7: Reserved"                                                                    \
  "\n 8-255: Mfg. Specific"                                                             \
  "\n0 :: xd_oos_opt holdlast"                                                          \
  "\n1 :: xd_oos_opt close"                                                             \
  "\n2 :: xd_oos_opt open"                                                              \
  "\n3 :: xd_oos_opt xd_fstate_val"                                                     \

#define HLP_278_FSTATE_VALUE                                                            \
  "|en| The preset analog working setpoint value to use when fault occurs. This"        \
  " value will be used if the I/O option Fault State to value is selected."              \

#define HLP_279_FSTATE_TIME                                                             \
  "|en| Time to keep the current position before the FSTATE_VALUE is used as a"         \
  " set point."                                                                          \

#define HLP_280_CHAR_SELECTION                  "|en|"                                  \

#define HLP_284_CUSTOM_CHAR                     "|en|"                                  \

#define HLP_287_CUSTOM_CHAR_POINTS                                                      \
  "|en| Custom characterization points. The array contains x-y pairs in an increasing" \
  " order.  The slope of the curve should be limited between 2.5 and 87.5 " \
  "degrees. (slope between 0.05 and 20) for up to selected" \
  " CUSTOM_CHAR.NUMBER_OF_POINTS. If this condition is not true, the curve can be" \
  " saved but cannot be activated (by writing CHAR_SELECTION.TYPE=255) The initial" \
  " value is expected to be (if Camflex is selected): Setpoint (16 bit) Position " \
  "(16 bit) " \
  "\n 2458               983 " \
  "\n 4915              1966 " \
  "\n 7117              2949 " \
  "\n 8724              3932 " \
  "\n 9981              4915 " \
  "\n 11012            5898 " \
  "\n 11869            6881 " \
  "\n 12593            7864 " \
  "\n 13206            8847 " \
  "\n 13718            9830 " \
  "\n 14156           10813 " \
  "\n 14944           12780 " \
  "\n 15335           13763 " \
  "\n 15729           14746 " \
  "\n 16122           15729 " \
  "\n Note that 16384 is equivalent to 100% and 0 to 0%, and endpoints (0,0) and " \
  "(16384,16384) are implied and must not be entered in the curve. The DD and" \
  " configuration tools must do the conversion." \

#define HLP_288_READBACK_SELECT                                                         \
  "|en| Selects whether working position or final position value is passed back"        \
  " to connected function block."                                                        \
  "\n0: Final Position Value"                                                           \
  "\n1: Working Position Value"                                                         \

#define HLP_289_TRANSDUCER_TYPE                                                         \
  "|en| Standard Pressure"                                                              \

#define HLP_290_XD_ERROR_PRESSURE                                                       \
  "|en| Pressure transducer error"                                                      \

#define HLP_291_SUPPLY_PRESSURE                                                         \
  "|en| The actual valve supply pressure and status. "                                  \

#define HLP_292_STATUS                          "|en|"                                  \

#define HLP_293_VALUE                           "|en|"                                  \

#define HLP_294_PRESSURE_RANGE                                                          \
  "|en| The range of the supply pressure."                                              \
  "\nThis parameter has to be synchronized with the scale parameter of the"             \
  " Analog Output block"                                                                 \

#define HLP_295_EU_100                                                                  \
  "|en| Upper Range for the supply pressure. Note, the value should be"                 \
  " recalculated if the Unit Index is changed."                                          \

#define HLP_296_EU_0                                                                    \
  "|en| Lower Range for the supply pressure. Note, the value should be"                 \
  " recalculated if the Unit Index is changed."                                          \

#define HLP_299_SUPPLY_PRESSURE_HI_ALERT        "|en|"                                  \

#define HLP_300_PRESSURE                                                                \
  "|en| Current SUPPLY_PRESSURE value"                                                  \

#define HLP_306_SUPPLY_PRESSURE_LO_ALERT        "|en|"                                  \

#define HLP_307_PRESSURE                                                                \
  "|en| Current SUPPLY_PRESSURE value"                                                  \

#define HLP_313_SUPPLY_PRESSURE_LOLO_ALERT      "|en|"                                  \

#define HLP_314_PRESSURE                                                                \
  "|en| Current SUPPLY_PRESSURE value"                                                  \

#define HLP_320_ACTUATOR_A_PRESSURE                                                     \
  "|en| The actual control pressure and status."                                        \
  "\nCommand 240, 1 - RD OUT_PRESSURE "                                                 \

#define HLP_321_STATUS                          "|en|"                                  \

#define HLP_322_VALUE                           "|en|"                                  \

#define HLP_323_ACTUATOR_B_PRESSURE                                                     \
  "|en| The actual control pressure and status. "                                       \

#define HLP_324_STATUS                          "|en|"                                  \

#define HLP_325_VALUE                           "|en|"                                  \

#define HLP_326_ATMOSPHERIC_PRESSURE                                                    \
  "|en| The actual Atmospheric pressure and status."                                    \
  "\nCommand 240, 1 - RD OUT_PRESSURE "                                                 \

#define HLP_327_STATUS                          "|en|"                                  \

#define HLP_328_VALUE                           "|en|"                                  \

#define HLP_329_PILOT_PRESSURE                                                          \
  "|en| The actual pilot pressure and status. "                                         \

#define HLP_330_STATUS                          "|en|"                                  \

#define HLP_331_VALUE                           "|en|"                                  \

#define HLP_332_PRESSURE_CALIBRATION                                                    \
  "|en| The information about the last positioner pressure calibration. "               \

#define HLP_338_SET_TO_FACTORY_PR_CALIBRATION                                           \
  "|en| Read will always return a value of 1."                                          \
  "\nWriting of 88 will restore Factory Calibration for pressure sensors"               \
  "\nWriting any other value will be ignored"                                           \

#define HLP_339_TEMP_TRANSDUCER_TYPE                                                    \
  "|en| Standard Temperature"                                                           \

#define HLP_340_XD_ERROR_TEMPERATURE                                                    \
  "|en| Temperature Transducer Error"                                                   \

#define HLP_341_TEMPERATURE                                                             \
  "|en| The actual temperature reported by the processor."                          \
  "\nCommand 240, 0 - RD ELECT_TEMP "                                                   \

#define HLP_342_STATUS                          "|en|"                                  \

#define HLP_343_VALUE                           "|en|"                                  \

#define HLP_344_TEMPERATURE_HI_ALERT            "|en|"                                  \

#define HLP_345_TEMPERATURE                                                             \
  "|en| Current TEMPERATURE value"                                                      \

#define HLP_351_TEMPERATURE_LO_ALERT            "|en|"                                  \

#define HLP_352_TEMPERATURE                                                             \
  "|en| Current TEMPERATURE value"                                                      \

#define HLP_358_IP_DRIVE_CURRENT                                                        \
  "|en| The current to drive IP converter"                                                  \

#define HLP_359_STATUS                          "|en|"                                  \

#define HLP_361_IP_DRIVE_CURRENT_HI_ALERT                                               \
  "|en| Alarm reported, when the Drive Current through the I/P converter is too"        \
  " High"                                                                                \

#define HLP_368_IP_DRIVE_CURRENT_LO_ALERT                                               \
  "|en| Alarm reported, when the Drive Current through the I/P converter is too"        \
  " Low"                                                                                 \

#define HLP_375_FIND_STOPS                                                              \
  "|en|Find Sops - Writing to the FIND_STOPS parameter will trigger execution of the"   \
  " following commands in the valve:"                                                    \
  "\n 1, Find stops Start - starts an automatic full find stops process" \
  "\n 2, Find stops Cancel - cancels a find stops process (full or partial)" \
  "\n 3, Find stops Set Closed - moves the valve to full closed position" \
  "\n 4, Find stops Set Open - moves the valve to full open position" \
  "\n 5, Find stops Accept - accepts the valve position as one of the stops - not finalized until commit" \
  "\n 6, Find stops Commit - saves the stop positions changed and recalculates scaling factors" \
  "\n 11, Find stops Running(un-selectable) - read only" \
  "\n 0, Find stops Notrunning(un-selectable - read only" \
  "\n Note that FIND_STOPS can be started only when the TB is in MAN" \
  " mode. The expectation is that the method or the DTM will not allow to change" \
  " the mode before the operation is completed." \

#define HLP_376_AUTOTUNE                                                                \
  "|en|Writing will set the three parameters: Supply Pressure, Aggressiveness and" \
  " Tune Flags to the processor. The fourth parameter is ignored on" \
  " writing. Reading will return same as written values of the first 3 parameters" \
  " plus the fourth parameter - Completion, specifying the autotune process" \
  " completion code." \

#define HLP_377_SUPPLY_PRESS                    "|en|"                                  \

#define HLP_378_AGGRESSIVENESS                  "|en|"                                  \

#define HLP_379_TUNE_FLAGS                      "|en|"                                  \


#define HLP_384_TRAVEL_CALIBRATION                                                      \
  "|en| Travel Calibration Procedure"                                                   \

#define HLP_385_START                                                                   \
  "|en| Writing to this parameter will start the travel Calibration procedure:"         \
  "\n 1 :: off"                                                                         \
  "\n 2 :: 0%-point calibration (no change to span)"                                    \
  "\n 3 :: 100% (span) calibration (no change to 0% point)"                             \
  "\n 4 :: 50%- point calibration (no change to either span or 0% point)"               \

#define HLP_386_RESULT                                                                  \
  "|en| Result of the Last Travel Calibration Procedure"                                \

#define HLP_387_CHECK_PROCESS                                                           \
  "|en| The current process running"                                                    \

#define HLP_390_UI_CUSTOM_CONFIGURATION                                                 \
  "|en| Configuration of the custom 1 and Custom 2 display values"                      \

#define HLP_CUSTOM_1_CONFIGURATION                                                  \
  "|en| Custom_1_Configuration will allow the user to select the value displayed"       \
  " on the local LCD display. " \
  "\n 1. WORK_SP (Default for the Custom 1)."                                           \
  "\n 2. WORK_POS"                                                                      \
  "\n 3. PID1.SP"                                                                       \
  "\n 4. PID1.PV"                                                                       \
  "\n 5. PID1.OUT"                                                                      \
  "\n 6. PID2.SP"                                                                       \
  "\n 7. PID2.PV"                                                                       \
  "\n 8. PID2.OUT"                                                                      \
  "\n 9. AI1.OUT"                                                                       \
  "\n 10. AI2.OUT"                                                                      \
  "\n 11. AI3.OUT"                                                                      \
  "\n 12. AO.SP"                                                                        \
  "\n 13. DO1.SP"                                                                       \
  "\n 14. DO2.SP"                                                                       \
  "\n 15. IS.IN1"                                                                       \
  "\n 16. IS.IN2"                                                                       \
  "\n 17. IS.IN3"                                                                       \
  "\n 18. IS.IN4"                                                                       \

#define HLP_CUSTOM_2_CONFIGURATION                                                  \
  "|en| Custom_2_Configuration will allow the user to select the value displayed"       \
  " on the local LCD display for the second custom selection. " \
  "\n 1. WORK_SP"                                                                       \
  "\n 2. WORK_POS.  (Default for the Custom 2)."                                        \
  "\n 3. PID1.SP"                                                                       \
  "\n 4. PID1.PV"                                                                       \
  "\n 5. PID1.OUT"                                                                      \
  "\n 6. PID2.SP"                                                                       \
  "\n 7. PID2.PV"                                                                       \
  "\n 8. PID2.OUT"                                                                      \
  "\n 9. AI1.OUT"                                                                       \
  "\n 10. AI2.OUT"                                                                      \
  "\n 11. AI3.OUT"                                                                      \
  "\n 12. AO.SP"                                                                        \
  "\n 13. DO1.SP"                                                                       \
  "\n 14. DO2.SP"                                                                       \
  "\n 15. IS.IN1"                                                                       \
  "\n 16. IS.IN2"                                                                       \
  "\n 17. IS.IN3"                                                                       \
  "\n 18. IS.IN4"                                                                       \

#define HLP_393_FAILED_STATE                                                            \
  "|en| Failed State status"                                                            \

#define HLP_396_FINAL_VALUE_D                                                           \
  "|en| Setpoint Received from DO block as boolean"       \

#define HLP_397_STATUS                                                                  \
  "|en| Status of the set point value"                                                  \

#define HLP_398_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Complete close"                                                               \
  "\n #0 - Complete Open"                                                               \

#define HLP_399_FINAL_POSITION_VALUE_D                                                  \
  "|en| Actual valve position provided to DO block as boolean"          \

#define HLP_400_STATUS                                                                  \
  "|en| Status of the position value"                                                   \

#define HLP_401_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Complete close"                                                               \
  "\n #0 - Partially or fully Open"                                                     \

#define HLP_402_FINAL_VALUE_DINT                                                        \
  "|en| Setpoint from DO block as integer"       \

#define HLP_403_STATUS                                                                  \
  "|en| Status of the setpoint value"                                                  \

#define HLP_404_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Complete close"                                                               \
  "\n 0 -100 - Discrete value of the setpoint in increments of %"                       \

#define HLP_405_FINAL_POSITION_VALUE_DINT                                               \
  "|en| Actual valve position provided to DO block as Integer"          \

#define HLP_406_STATUS                                                                  \
  "|en| Status of the position value"                                                   \

#define HLP_407_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Complete close"                                                               \
  "\n 1-100 - Discrete setpoint in increments of 1%"                        \

#define HLP_408_FSC_SET_D                                                               \
  "|en| Failed State Control Set (Discrete)"                                            \

#define HLP_409_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_410_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Close"                                                                        \
  "\n 1 - Open"                                                                         \

#define HLP_411_FSC_ACTUAL_D                                                            \
  "|en| Failed State Control Actual (Discrete)"                                         \

#define HLP_412_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_413_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Close"                                                                        \
  "\n 1 - Open"                                                                         \

#define HLP_414_DISCRETE_OUTPUT_1                                                       \
  "|en| Discrete Switch Output 1 value and status"                                      \

#define HLP_415_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_416_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Close"                                                                        \
  "\n 1 - Open"                                                                         \

#define HLP_417_DISCRETE_OUTPUT_2                                                       \
  "|en| Discrete Switch Output 2 value and status"                                      \

#define HLP_418_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_419_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Close"                                                                        \
  "\n 1 - Open"                                                                         \

#define HLP_420_DISCRETE_SWITCH_HI                                                      \
  "|en| Software Discrete Limit Switch HI value and status"                             \

#define HLP_421_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_422_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Position below HI Limit"                                                      \
  "\n 1 - Position Above Hi Limit"                                                      \

#define HLP_423_DISCRETE_SWITCH_LO                                                      \
  "|en| Software Discrete Limit Switch LO value and status"                             \

#define HLP_424_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_425_VALUE                                                                   \
  "|en| Value:"                                                                         \
  "\n 0 - Position Above LO Limit"                                                      \
  "\n 1 - Position Below LO Limit"                                                      \

#define HLP_426_DISCRETE_SWITCH_1_CONF                                                  \
  "|en| Discrete switch configuration"                                                  \

#define HLP_427_DIRECTION                                                               \
  "|en| Value:"                                                                         \
  "\n 1 - Normal Open (default)"                                                        \
  "\n 0 - Normal Closed"                                                                \

#define HLP_428_FUNCTION                                                                \
  "|en| Custom_1_Configuration will allow the user to select the value displayed"       \
  " on the local LCD display. " \
  "\n 0. Disabled (always inactive; default)"                                           \
  "\n 1. DO block"                                                                      \
  "\n 2. Fault State"                                                                   \
  "\n 3. Not In Normal"                                                                 \
  "\n 4. Maintenance Required"                                                          \
  "\n 5. Warning Data"                                                                  \
  "\n 6. Air Supply Alert"                                                              \
  "\n 7. Travel Deviation Alert"                                                        \
  "\n 8. Position HI Alert"                                                             \
  "\n 9. Position LO Alert"                                                             \
  "\n 10. Always Active"                                                                \
  "\n 11. Always Inactive (same as disabled)"                                           \
  "\n 12. Reset Occurred"                                                               \
  "\n 13. Tight cutoff"                                                                 \
  "\n"                                                                                  \

#define HLP_429_DISCRETE_SWITCH_2_CONF          "|en|"                                  \

#define HLP_430_DIRECTION                                                               \
  "|en| Value:"                                                                         \
  "\n 1 - Normal Open (default)"                                                        \
  "\n 0 - Normal Closed"                                                                \

#define HLP_431_FUNCTION                                                                \
  "|en|Option for presenting"       \
  " on the local display. " \
  "\n 0. Disabled (always inactive; default)"                                           \
  "\n 1. DO block"                                                                      \
  "\n 2. Fault State"                                                                   \
  "\n 3. Not In Normal"                                                                 \
  "\n 4. Maintenance Required"                                                          \
  "\n 5. Warning Data"                                                                  \
  "\n 6. Air Supply Alert"                                                              \
  "\n 7. Travel Deviation Alert"                                                        \
  "\n 8. Position HI Alert"                                                             \
  "\n 9. Position LO Alert"                                                             \
  "\n 10. Always Active"                                                                \
  "\n 11. Always Inactive (same as disabled)"                                           \
  "\n 12. Reset Occurred"                                                               \
  "\n 13. Tight cutoff"                                                                 \
  "\n"                                                                                  \

#define HLP_432_UI_ACCESS_CONTROL                                                       \
  "|en|"                               \

#define HLP_436_UI_LANGUAGE                                                             \
  "|en| 0 :: English, 1 :: French, 2 :: Spanish, 3 :: Portuguese, 4 :: Japanese, 5 :: Italian, 6 :: German" \

#define HLP_437_APP_MODE                                                                \
  "|en| Application Processor Mode"                                                     \

#define HLP_438_COMPLETE_STATUS                                                         \
  "|en| Full status presentation" \

#define HLP_439_CLEAR_STATUS                                                            \
  "|en| Clear status presentation - ."                                                  \
  "\n0 - No Action"                                                                     \
  "\n1 - Clear Current Status"                                                          \
  "\n2 - Clear Current and Historic Status"                                             \

#define HLP_440_OPEN_STOP_ADJUSTMENT            "|en|"                                  \

#define HLP_441_SETPOINT_SOURCE                                                         \
  "|en| Describes the source of the set point:"                                         \
  "\n 1 - Control is coming from AO-FINAL_VALUE"                                        \
  "\n 2 - Control is coming from DO-FINAL_VALUE_D in Open/Close mode"                   \
  "\n 3 - Control is coming from DO-FINAL_VALUE_D in 1% steps mode"                     \
  "\nRequirement:10861"                                                                 \
  "\nTask: 10862, 10865"                                                                \

#define HLP_442_SETPOINT                                                                \
  "|en| Setpoint" \

#define HLP_443_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_445_ACTUAL_POSITION                                                         \
  "|en| Actual Position" \

#define HLP_446_STATUS                                                                  \
  "|en| Status"                                                                         \

#define HLP_448_WRONG_CONFIGURATION                                                     \
  "|en| A value of 0 indicates that wrong configuration is not detected"                \
  "\nParameter number within the block will indicate the first detected"                \
  " parameter, that has wrong configuration"                                             \

#define HLP_449_INDEX                                                                   \
  "|en| Index of the parameter with problematic configuration"                          \

#define HLP_450_SUB_INDEX                                                               \
  "|en| Sub-Index of the parameter with problematic configuration"                      \

#define HLP_451_DESCRIPTION                                                             \
  "|en| Description of the problem"                                                     \

#define HLP_531_WORKING_TIMES                   "|en|"                                  \

#define HLP_535_WORKING_TIME_ALERT              "|en|"                                  \

#define HLP_536_TOTAL_TIME                                                              \
  "|en| Total Number of hours since manufacturing or since reset"                       \

#define HLP_537_ALERT_POINT                                                             \
  "|en| TOTAL_TIME Value, above which the ALERT will be set to True"                    \

#define HLP_543_ACTUATOR_1                                                              \
  "|en| Information about the Actuator"                                                 \

#define HLP_548_ACTUATOR_2                                                              \
  "|en| Information about the Actuator"                                                 \

#define HLP_553_ACTUATOR_3                                                              \
  "|en| Information about the Actuator"                                                 \

#define HLP_560_SUPPLY_PRS_MAX                                                          \
  "|en| Maximum Supply pressure for the Actuator"                                       \

#define HLP_561_PRS_CONTROL_HI                                                          \
  "|en| Maximum Supply Pressure for the actuator in control - it should be the"         \
  " same as Bench Range?"                                                                \

#define HLP_562_PRS_CONTROL_LO                                                          \
  "|en| Minimum Supply Pressure for the actuator in control - it should be the"         \
  " same as Bench Range?"                                                                \

#define HLP_563_ACTUATOR_INFO                   "|en|"                                  \

#define HLP_568_VALVE_IDENTIFICATION                                                    \
  "|en| Information about the Valve Identification"                                     \

#define HLP_572_VALVE_SERVICE                                                           \
  "|en| Valve Service information"                                                      \

#define HLP_575_VALVE_BODY_1                                                            \
  "|en| Valve Service information"                                                      \

#define HLP_581_VALVE_BODY_2                                                            \
  "|en| Valve Service information"                                                      \

#define HLP_584_VALVE_BODY_3                                                            \
  "|en| Valve Service information"                                                      \

#define HLP_587_VALVE_INFO                      "|en|"                                  \

#define HLP_593_BOOSTER                         "|en|"                                  \

#define HLP_597_ACCESSORY                       "|en|"                                  \

#define HLP_599_POSITION_EXTREMES               "|en|"                                  \

#define HLP_608_PRESSURE_EXTREMES               "|en|"                                  \

#define HLP_617_TEMPERATURE_EXTREMES            "|en|"                                  \

#define HLP_620_IP_CURRENT_EXTREMES             "|en|"                                  \

#define HLP_TB_BLOCK_ERR_DESC_1                                                   \
  "No Error.\n"                               \
  "Mode Switch Error - The PTB Actual mode cannot be set to any non-AUTO" \
  " mode.\n"                                                                       \
  "HART Response Timeout - The response to the FF request times out.\n"   \
  "SP Source conflict - A DO block attempts to become a SP source on the" \
  " channel already taken by the other DO block.\n"                                \
  "FIND_STOPS Failed - Find Stops request made by writing FIND_STOPS"     \
  " parameter failed.\n"                                                           \
/*~~~~~~~~~~~~~~~~~~~~/
*** Label Definitions
/~~~~~~~~~~~~~~~~~~~~*/


#define LBL_XD_FS_CONFIGURATION                   "|en|Configuration"
#define LBL_XD_FSTATE_OPT                   "|en|XD Fstate Opt"

#define LBL_043_POSITION_TRANSDUCER_TYPE        "|en|Position Transducer Type"
#define LBL_044_XD_ERROR_POS                    "|en|XD Error Pos"
#define LBL_045_FINAL_VALUE                     "|en|Final Value"
#define LBL_046_STATUS                          "|en|Status"
#define LBL_047_VALUE                           "|en|Value"
#define LBL_048_FINAL_VALUE_RANGE               "|en|Final Value Range"
#define LBL_049_EU_100                          "|en|EU 100"
#define LBL_050_EU_0                            "|en|EU 0"
#define LBL_053_POSITION_LIMITS                 "|en|Position Limits"
#define LBL_062_FINAL_VALUE_CUTOFF_HI           "|en|Final Value Cutoff HI"
#define LBL_064_CUTOFF_POINT_HI                 "|en|Cutoff Point HI"
#define LBL_065_FINAL_VALUE_CUTOFF_LO           "|en|Final Value Cutoff LO"
#define LBL_067_CUTOFF_POINT_LO                 "|en|Cutoff Point LO"
#define LBL_068_FINAL_POSITION_VALUE            "|en|Final Position Value"
#define LBL_069_STATUS                          "|en|Status"
#define LBL_070_VALUE                           "|en|Value"
#define LBL_071_ACTIVATE_CONTROL_SET            "|en|Activate"
#define LBL_072_ACTIVE_CONTROL_SET              "|en|Active Control Set"
#define LBL_073_P                               "|en|P"
#define LBL_074_I                               "|en|I"
#define LBL_075_D                               "|en|D"
#define LBL_076_PADJ                            "|en|Padj"
#define LBL_077_BETA                            "|en|Beta"
#define LBL_078_POSCOMP                         "|en|Poscomp"
#define LBL_079_DEADZONE                        "|en|Deadzone"
#define LBL_080_NONLIN                          "|en|Nonlin"
#define LBL_081_CUSTOM_CONTROL_SET              "|en|Custom Control Set"
#define LBL_082_P                               "|en|P"
#define LBL_083_I                               "|en|I"
#define LBL_084_D                               "|en|D"
#define LBL_085_PADJ                            "|en|Padj"
#define LBL_086_BETA                            "|en|Beta"
#define LBL_087_POSCOMP                         "|en|Poscomp"
#define LBL_088_DEADZONE                        "|en|Deadzone"
#define LBL_089_NONLIN                          "|en|Nonlin"
#define LBL_090_BACKUP_CONTROL_SET              "|en|Backup Control Set"
#define LBL_092_P                               "|en|P"
#define LBL_093_I                               "|en|I"
#define LBL_094_D                               "|en|D"
#define LBL_095_PADJ                            "|en|Padj"
#define LBL_096_BETA                            "|en|Beta"
#define LBL_097_POSCOMP                         "|en|Poscomp"
#define LBL_098_DEADZONE                        "|en|Deadzone"
#define LBL_099_NONLIN                          "|en|Nonlin"
#define LBL_100_TRAVEL_CALIBRATION              "|en|Travel Calibration"
#define LBL_108_TRAVEL                          "|en|Travel"
#define LBL_109_RANGE                           "|en|Range"
#define LBL_111_WORKING_SP                      "|en|Working SP"
#define LBL_112_STATUS                          "|en|Status"
#define LBL_113_VALUE                           "|en|Value"
#define LBL_114_WORKING_POS                     "|en|Working Pos"
#define LBL_115_STATUS                          "|en|Status"
#define LBL_116_VALUE                           "|en|Value"
#define LBL_117_DEVIATION_ALERT                 "|en|Deviation Alert"
#define LBL_118_DEVIATION_VALUE                 "|en|Deviation Value"
#define LBL_119_ALERT_POINT                     "|en|Alert Point"
#define LBL_120_DEADBAND                        "|en|Deadband"
#define LBL_125_POSITION_HIHI_ALERT             "|en|Position Hihi Alert"
#define LBL_126_POSITION                        "|en|Position"
#define LBL_127_ALERT_POINT                     "|en|Alert Point"
#define LBL_128_DEADBAND                        "|en|Deadband"
#define LBL_132_POSITION_HI_ALERT               "|en|Position HI Alert"
#define LBL_133_POSITION                        "|en|Position"
#define LBL_134_ALERT_POINT                     "|en|Alert Point"
#define LBL_135_DEADBAND                        "|en|Deadband"
#define LBL_139_POSITION_LO_ALERT               "|en|Position LO Alert"
#define LBL_140_POSITION                        "|en|Position"
#define LBL_141_ALERT_POINT                     "|en|Alert Point"
#define LBL_142_DEADBAND                        "|en|Deadband"
#define LBL_146_POSITION_LOLO_ALERT             "|en|Position Lolo Alert"
#define LBL_147_POSITION                        "|en|Position"
#define LBL_148_ALERT_POINT                     "|en|Alert Point"
#define LBL_149_DEADBAND                        "|en|Deadband"
#define LBL_154_TRAVEL_ACCUMULATION             "|en|Travel Accumulation"
#define LBL_155_ALERT_POINT                     "|en|Alert Point"
#define LBL_156_DEADBAND                        "|en|Deadband"
#define LBL_161_TRAVEL_ACCUMULATION             "|en|Travel Accumulation"
#define LBL_162_ALERT_POINT                     "|en|Alert Point"
#define LBL_163_DEADBAND                        "|en|Deadband"
#define LBL_167_TRAVEL_ACCUMULATION_TREND       "|en|Travel Accumulation Trend"
#define LBL_168_TODAY                           "|en|Today"
#define LBL_169_LAST_DAY                        "|en|Last Day"
#define LBL_170_PREVIOUS_DAY                    "|en|Previous Day"
#define LBL_171_THREE_DAYS_AGO                  "|en|Three Days Ago"
#define LBL_172_CURRENT_WEEK                    "|en|Current Week"
#define LBL_173_LAST_WEEK                       "|en|Last Week"
#define LBL_174_PREVIOUS_WEEK                   "|en|Previous Week"
#define LBL_175_THREE_WEEKS_AGO                 "|en|Three Weeks Ago"
#define LBL_176_CURRENT_MONTH                   "|en|Current Month"
#define LBL_177_LAST_MONTH                      "|en|Last Month"
#define LBL_178_PREVIOUS_MONTH                  "|en|Previous Month"
#define LBL_179_THREE_MONTHS_AGO                "|en|Three Months Ago"
#define LBL_180_CURRENT_12_MONTHS               "|en|Current 12 Months"
#define LBL_181_LAST_12_MONTHS                  "|en|Last 12 Months"
#define LBL_182_PREVIOUS_12_MONTHS              "|en|Previous 12 Months"
#define LBL_183_THREE_YEARS_AGO                 "|en|Three Years Ago"
#define LBL_184_TOTAL                           "|en|Total"
#define LBL_188_DEADBAND                        "|en|Deadband"
#define LBL_195_DEADBAND                        "|en|Deadband"
#define LBL_199_CYCLE_COUNTER_TREND             "|en|Cycle Counter Trend"
#define LBL_200_TODAY                           "|en|Today"
#define LBL_201_LAST_DAY                        "|en|Last Day"
#define LBL_202_PREVIOUS_DAY                    "|en|Previous Day"
#define LBL_203_THREE_DAYS_AGO                  "|en|Three Days Ago"
#define LBL_204_CURRENT_WEEK                    "|en|Current Week"
#define LBL_205_LAST_WEEK                       "|en|Last Week"
#define LBL_206_PREVIOUS_WEEK                   "|en|Previous Week"
#define LBL_207_THREE_WEEKS_AGO                 "|en|Three Weeks Ago"
#define LBL_208_CURRENT_MONTH                   "|en|Current Month"
#define LBL_209_LAST_MONTH                      "|en|Last Month"
#define LBL_210_PREVIOUS_MONTH                  "|en|Previous Month"
#define LBL_211_THREE_MONTHS_AGO                "|en|Three Months Ago"
#define LBL_212_CURRENT_12_MONTHS               "|en|Current 12 Months"
#define LBL_213_LAST_12_MONTHS                  "|en|Last 12 Months"
#define LBL_214_PREVIOUS_12_MONTHS              "|en|Previous 12 Months"
#define LBL_215_THREE_YEARS_AGO                 "|en|Three Years Ago"
#define LBL_216_TOTAL                           "|en|Total"
#define LBL_217_POSITION_ERROR_TREND            "|en|Position Error Trend"
#define LBL_218_TODAY                           "|en|Today"
#define LBL_219_LAST_DAY                        "|en|Last Day"
#define LBL_220_PREVIOUS_DAY                    "|en|Previous Day"
#define LBL_221_THREE_DAYS_AGO                  "|en|Three Days Ago"
#define LBL_222_CURRENT_WEEK                    "|en|Current Week"
#define LBL_223_LAST_WEEK                       "|en|Last Week"
#define LBL_224_PREVIOUS_WEEK                   "|en|Previous Week"
#define LBL_225_THREE_WEEKS_AGO                 "|en|Three Weeks Ago"
#define LBL_226_CURRENT_MONTH                   "|en|Current Month"
#define LBL_227_LAST_MONTH                      "|en|Last Month"
#define LBL_228_PREVIOUS_MONTH                  "|en|Previous Month"
#define LBL_229_THREE_MONTHS_AGO                "|en|Three Months Ago"
#define LBL_230_CURRENT_12_MONTHS               "|en|Current 12 Months"
#define LBL_231_LAST_12_MONTHS                  "|en|Last 12 Months"
#define LBL_232_PREVIOUS_12_MONTHS              "|en|Previous 12 Months"
#define LBL_233_THREE_YEARS_AGO                 "|en|Three Years Ago"
#define LBL_234_TOTAL                           "|en|Total"
#define LBL_235_POSITION_HISTOGRAM              "|en|Position Histogram"
#define LBL_236_TOTAL                           "|en|Total Time"
#define LBL_249_NEAR_CLOSED_ALERT               "|en|Near Closed Alert"
#define LBL_255_POSITION_ERROR_HISTOGRAM        "|en|Position Error Histogram"
#define LBL_269_TIME_SINCE_UPDATE               "|en|Time Since Update"
#define LBL_270_ALERT_POINT                     "|en|Alert Point"
#define LBL_271_MAX_TIME                        "|en|Max Time"
#define LBL_275_XD_FSTATE                       "|en|XD Fstate"
#define LBL_278_FSTATE_VALUE                    "|en|Fstate Value"
#define LBL_279_FSTATE_TIME                     "|en|Fstate Time"
#define LBL_280_CHAR_SELECTION                  "|en|Char Selection"
#define LBL_281_TYPE                            "|en|Type"
#define LBL_284_CUSTOM_CHAR                     "|en|Custom Char"
#define LBL_287_CUSTOM_CHAR_POINTS              "|en|Custom Char Points"
#define LBL_288_READBACK_SELECT                 "|en|Readback Select"
#define LBL_289_TRANSDUCER_TYPE                 "|en|Transducer Type"
#define LBL_290_XD_ERROR_PRESSURE               "|en|XD Error Pressure"
#define LBL_291_SUPPLY_PRESSURE                 "|en|Supply Pressure"
#define LBL_292_STATUS                          "|en|Status"
#define LBL_293_VALUE                           "|en|Value"
#define LBL_294_PRESSURE_RANGE                  "|en|Pressure Range"
#define LBL_295_EU_100                          "|en|EU 100"
#define LBL_296_EU_0                            "|en|EU 0"
#define LBL_299_SUPPLY_PRESSURE_HI_ALERT        "|en|Supply Pressure HI Alert"
#define LBL_300_PRESSURE                        "|en|Pressure"
#define LBL_306_SUPPLY_PRESSURE_LO_ALERT        "|en|Supply Pressure LO Alert"
#define LBL_307_PRESSURE                        "|en|Pressure"
#define LBL_313_SUPPLY_PRESSURE_LOLO_ALERT      "|en|Supply Pressure Lolo Alert"
#define LBL_314_PRESSURE                        "|en|Pressure"
#define LBL_320_ACTUATOR_A_PRESSURE             "|en|Actuator A Pressure"
#define LBL_321_STATUS                          "|en|Status"
#define LBL_322_VALUE                           "|en|Value"
#define LBL_323_ACTUATOR_B_PRESSURE             "|en|Actuator B Pressure"
#define LBL_324_STATUS                          "|en|Status"
#define LBL_325_VALUE                           "|en|Value"
#define LBL_326_ATMOSPHERIC_PRESSURE            "|en|Atmospheric Pressure"
#define LBL_327_STATUS                          "|en|Status"
#define LBL_328_VALUE                           "|en|Value"
#define LBL_329_PILOT_PRESSURE                  "|en|Pilot Pressure"
#define LBL_330_STATUS                          "|en|Status"
#define LBL_331_VALUE                           "|en|Value"
#define LBL_332_PRESSURE_CALIBRATION            "|en|Pressure Calibration"
#define LBL_338_SET_TO_FACTORY_PR_CALIBRATION   "|en|Set To Factory PR Calibration"
#define LBL_339_TEMP_TRANSDUCER_TYPE            "|en|Temp Transducer Type"
#define LBL_340_XD_ERROR_TEMPERATURE            "|en|XD Error Temperature"
#define LBL_341_TEMPERATURE                     "|en|Temperature"
#define LBL_342_STATUS                          "|en|Status"
#define LBL_343_VALUE                           "|en|Value"
#define LBL_344_TEMPERATURE_HI_ALERT            "|en|Temperature HI Alert"
#define LBL_345_TEMPERATURE                     "|en|Temperature"
#define LBL_351_TEMPERATURE_LO_ALERT            "|en|Temperature LO Alert"
#define LBL_352_TEMPERATURE                     "|en|Temperature"
#define LBL_358_IP_DRIVE_CURRENT                "|en|IP Drive Current"
#define LBL_359_STATUS                          "|en|Status"
#define LBL_361_IP_DRIVE_CURRENT_HI_ALERT       "|en|IP Drive Current HI Alert"
#define LBL_368_IP_DRIVE_CURRENT_LO_ALERT       "|en|IP Drive Current LO Alert"
#define LBL_375_FIND_STOPS                      "|en|Find Stops"
#define LBL_376_AUTOTUNE                        "|en|Autotune"
#define LBL_377_SUPPLY_PRESS                    "|en|Supply Press"
#define LBL_378_AGGRESSIVENESS                  "|en|Aggressiveness"
#define LBL_379_TUNE_FLAGS                      "|en|Tune Flags"
#define LBL_384_TRAVEL_CALIBRATION              "|en|Travel Calibration"
#define LBL_385_START                           "|en|Start"
#define LBL_386_RESULT                          "|en|Result"
#define LBL_387_CHECK_PROCESS                   "|en|Check Process"
#define LBL_390_UI_CUSTOM_CONFIGURATION         "|en|UI Custom Configuration"
#define LBL_CUSTOM_1_CONFIGURATION          "|en|Custom 1 Configuration"
#define LBL_CUSTOM_2_CONFIGURATION          "|en|Custom 2 Configuration"
#define LBL_393_FAILED_STATE                    "|en|Failed State"
#define LBL_396_FINAL_VALUE_D                   "|en|Final Value D"
#define LBL_397_STATUS                          "|en|Status"
#define LBL_398_VALUE                           "|en|Value"
#define LBL_399_FINAL_POSITION_VALUE_D          "|en|Final Position Value D"
#define LBL_400_STATUS                          "|en|Status"
#define LBL_401_VALUE                           "|en|Value"
#define LBL_402_FINAL_VALUE_DINT                "|en|Final Value Dint"
#define LBL_403_STATUS                          "|en|Status"
#define LBL_404_VALUE                           "|en|Value"
#define LBL_405_FINAL_POSITION_VALUE_DINT       "|en|Final Position Value Dint"
#define LBL_406_STATUS                          "|en|Status"
#define LBL_407_VALUE                           "|en|Value"
#define LBL_408_FSC_SET_D                       "|en|Fsc Set D"
#define LBL_409_STATUS                          "|en|Status"
#define LBL_410_VALUE                           "|en|Value"
#define LBL_411_FSC_ACTUAL_D                    "|en|Fsc Actual D"
#define LBL_412_STATUS                          "|en|Status"
#define LBL_413_VALUE                           "|en|Value"
#define LBL_414_DISCRETE_OUTPUT_1               "|en|Discrete Output 1"
#define LBL_415_STATUS                          "|en|Status"
#define LBL_416_VALUE                           "|en|Value"
#define LBL_417_DISCRETE_OUTPUT_2               "|en|Discrete Output 2"
#define LBL_418_STATUS                          "|en|Status"
#define LBL_419_VALUE                           "|en|Value"
#define LBL_420_DISCRETE_SWITCH_HI              "|en|Discrete Switch HI"
#define LBL_421_STATUS                          "|en|Status"
#define LBL_422_VALUE                           "|en|Value"
#define LBL_423_DISCRETE_SWITCH_LO              "|en|Discrete Switch LO"
#define LBL_424_STATUS                          "|en|Status"
#define LBL_425_VALUE                           "|en|Value"
#define LBL_426_DISCRETE_SWITCH_1_CONF          "|en|Discrete Switch 1 Conf"
#define LBL_427_DIRECTION                       "|en|Direction"
#define LBL_428_FUNCTION                        "|en|Function"
#define LBL_429_DISCRETE_SWITCH_2_CONF          "|en|Discrete Switch 2 Conf"
#define LBL_430_DIRECTION                       "|en|Direction"
#define LBL_431_FUNCTION                        "|en|Function"
#define LBL_432_UI_ACCESS_CONTROL               "|en|UI Access Control"
#define LBL_436_UI_LANGUAGE                     "|en|UI Language"
#define LBL_437_APP_MODE                        "|en|App Mode"
#define LBL_438_COMPLETE_STATUS                 "|en|Complete Status"
#define LBL_439_CLEAR_STATUS                    "|en|Clear Status"
#define LBL_440_OPEN_STOP_ADJUSTMENT            "|en|Open Stop Adjustment"
#define LBL_441_SETPOINT_SOURCE                 "|en|Setpoint Source"
#define LBL_442_SETPOINT                        "|en|Setpoint"
#define LBL_443_STATUS                          "|en|Status"
#define LBL_445_ACTUAL_POSITION                 "|en|Actual Position"
#define LBL_446_STATUS                          "|en|Status"
#define LBL_448_WRONG_CONFIGURATION             "|en|Wrong Configuration"
#define LBL_449_INDEX                           "|en|Index"
#define LBL_450_SUB_INDEX                       "|en|Sub Index"
#define LBL_451_DESCRIPTION                     "|en|Description"
#define LBL_452_ALERT_ACTION                    "|en|Alert Action"
#define LBL_455_POSITION_HIHI_ALERT             "|en|Position Hihi Alert"
#define LBL_456_POSITION_HI_ALERT               "|en|Position HI Alert"
#define LBL_457_POSITION_LO_ALERT               "|en|Position LO Alert"
#define LBL_458_POSITION_LOLO_ALERT             "|en|Position Lolo Alert"
#define LBL_459_SET_POINT_TIMEOUT_ALERT         "|en|Setpoint Timeout Alert"
#define LBL_460_NEAR_CLOSE_ALERT                "|en|Near Close Alert"
#define LBL_461_TRAVEL_ACCUMULATION_A_ALERT     "|en|Travel Accumulation A Alert"
#define LBL_462_TRAVEL_ACCUMULATION_B_ALERT     "|en|Travel Accumulation B Alert"
#define LBL_463_CYCLE_COUNTER_A_ALERT           "|en|Cycle Counter A Alert"
#define LBL_464_CYCLE_COUNTER_B_ALERT           "|en|Cycle Counter B Alert"
#define LBL_465_WORKING_TIME_ALERT              "|en|Control Time Alert"
#define LBL_466_SUPPLY_PRESSURE_HI_ALERT        "|en|Supply Pressure HI Alert"
#define LBL_467_SUPPLY_PRESSURE_LO_ALERT        "|en|Supply Pressure LO Alert"
#define LBL_468_SUPPLY_PRESSURE_LOLO_ALERT      "|en|Supply Pressure Lolo Alert"
#define LBL_469_TEMPERATURE_HI_ALERT            "|en|Temperature HI Alert"
#define LBL_470_TEMPERATURE_LO_ALERT            "|en|Temperature LO Alert"
#define LBL_471_IP_DRIVE_CURRENT_ALERT_HI       "|en|IP Drive Current Alert HI"
#define LBL_472_IP_DRIVE_CURRENT_ALERT_LO       "|en|IP Drive Current Alert LO"
#define LBL_473_SENSOR_FAILURE_ALERT            "|en|Sensor Failure Alert"
#define LBL_474_PROCESSOR_ALERT                 "|en|Processor Alert"
#define LBL_475_VALVE_CONTROL_ALERT             "|en|Valve Control Alert"
#define LBL_476_COMMISSIONING_ALERT             "|en|Commissioning Alert"
#define LBL_477_AIR_SUPPLY_ALERT                "|en|Air Supply Alert"
#define LBL_478_SUPPORTING_HARDWARE_ALERT       "|en|Supporting Hardware Alert"
#define LBL_479_ALERT_STATE                     "|en|Alert State"
#define LBL_505_ALERT_COUNTERS                  "|en|Alert Counters"
#define LBL_531_WORKING_TIMES                   "|en|Working Times"
#define LBL_535_WORKING_TIME_ALERT              "|en|Working Time Alert"
#define LBL_536_TOTAL_TIME                      "|en|Total Time"
#define LBL_537_ALERT_POINT                     "|en|Alert Point"
#define LBL_543_ACTUATOR_1                      "|en|Actuator 1"
#define LBL_548_ACTUATOR_2                      "|en|Actuator 2"
#define LBL_553_ACTUATOR_3                      "|en|Actuator 3"
#define LBL_556_STYLE                           "|en|Style"
#define LBL_560_SUPPLY_PRS_MAX                  "|en|Supply Prs Max"
#define LBL_561_PRS_CONTROL_HI                  "|en|Prs Control HI"
#define LBL_562_PRS_CONTROL_LO                  "|en|Prs Control LO"
#define LBL_563_ACTUATOR_INFO                   "|en|Actuator Info"
#define LBL_568_VALVE_IDENTIFICATION            "|en|Valve Identification"
#define LBL_572_VALVE_SERVICE                   "|en|Valve Service"
#define LBL_575_VALVE_BODY_1                    "|en|Valve Body 1"
#define LBL_581_VALVE_BODY_2                    "|en|Valve Body 2"
#define LBL_584_VALVE_BODY_3                    "|en|Valve Body 3"
#define LBL_587_VALVE_INFO                      "|en|Valve Info"
#define LBL_593_BOOSTER                         "|en|Booster"
#define LBL_597_ACCESSORY                       "|en|Accessory"
#define LBL_599_POSITION_EXTREMES               "|en|Position Extremes"
#define LBL_608_PRESSURE_EXTREMES               "|en|Pressure Extremes"
#define LBL_617_TEMPERATURE_EXTREMES            "|en|Temperature Extremes"
#define LBL_620_IP_CURRENT_EXTREMES             "|en|IP Current Extremes"

/*----------------------------------/
** TB block members for SVI2 special
/----------------------------------*/
#include "svi_custom.h"

/*--------------------------------------/
** TB block members from standard libary
/--------------------------------------*/

#define TB_BLOCK_MEMBERS_STD                                \
    ST_REV,                 __st_rev ;                      \
    TAG_DESC,               __tag_desc ;                    \
    STRATEGY,               __strategy ;                    \
    ALERT_KEY,              __alert_key ;                   \
    MODE_BLK,               __mode_blk ;              \
    BLOCK_ERR,              __block_err ;                   \
    UPDATE_EVT,             __update_evt ;                  \
    BLOCK_ALM,              __block_alm ;                   \
    TRANSDUCER_DIRECTORY,   __transducer_directory

/*------------------------------/
** TB block views object defines - see svi_positioner.ddl
/------------------------------*/

/*--------------------/
** TB block MENUS list
/--------------------*/

#define TB_MENU_LIST                \
   device_root_menu_ptb,            \
   diagnostic_root_menu_ptb,        \
   process_variables_root_menu_ptb, \
   Menu_Top_ptb


/*---------------------/
** TB block METHOD LIST
/---------------------*/

#define TB_METHOD_LIST       \
  /* update_custom_char_points, */ \
  /* do_setup_wizard, */           \
  /* do_configure_wizard, */       \
  /*do_enable_position_limits, */  \
  do_find_stops,             \
  /* do_open_stop_adjustment, */   \
  do_autotune,               \
  do_manual_hi_low_stops,    \
  /*do_full_close, */        \
  /*do_full_open,  */        \
  /* do_set_position, */           \
  change_app_mode            \
  /* do_factory_configure, */

/* autotune,                               \ */
/* travel_calibration,                     \ */
/* find_stops,                             \ */

/*----------------------------/
** Enumerated Data Definitions
/----------------------------*/

#define TB_BLOCK_ERR_DESC_1_ENUM   /* The order of bits reversed by #18079*/ \
    { 0x80000000,  "|en|No Error" }, \
    { 0x40000000,  "|en|Mode Switch Error" }, \
    { 0x20000000,  "|en|HART Response Time out" }, \
    { 0x10000000,  "|en|Channel Configuration Conflict" }, \
    { 0x08000000,  "|en|Find Stops Failed" } \

#define ENUM_PROPAGATE_MODE                       \
  {0, "|en|Propagate RB OOS mode to TB" },                         \
  {1, "|en|Propagate TB failed state to RB and RB OOS mode to TB " }      \
  {2, "|en|Do not propagate" }      \
  {3, "|en|Propagate TB failed state to RB" }      \

#define ENUM_MAPPED_TO_RB               \
  {1, "|en|Map to RB (Default)" },      \
  {2, "|en|Report in TB" }              \

#define ENUM_SETPOINT_SOURCE                            \
  { 1,"|en|AO-Final Value"},                            \
  { 2,"|en|DO-Final Value D in Open/Close mode"},       \
  { 3,"|en|DO-Final Value D in 1% steps mode"}          \

#define ENUM_CLEAR_STATUS                       \
{0, "|en|No Action"},                           \
{1, "|en|Clear Current Status"},                \
{2, "|en|Clear Current and Historic Status"}    \

#define ENUM_DIRECTION                                          \
  {1, "|en|Normal Open (default)"                       },      \
  {0, "|en|Normal Closed"                               }

#define ENUM_FUNCTION                                           \
  {0,   "|en|Disabled (always inactive; default)"       },      \
  {1,   "|en|DO block"                                  },      \
  {2,   "|en|Fault State"                               },      \
  {3,   "|en|Not In Normal"                             },      \
  {4,   "|en|Maintenance Required"                      },      \
  {5,   "|en|Warning Data"                              },      \
  {6,   "|en|Air Supply Alert"                          },      \
  {7,   "|en|Travel Deviation Alert"                    },      \
  {8,   "|en|Position HI Alert"                         },      \
  {9,   "|en|Position LO Alert"                         },      \
  {10,  "|en|Always Active"                             },      \
  {11,  "|en|Always Inactive (same as disabled)"        },      \
  {12,  "|en|Reset Occurred"                            },      \
  {13,  "|en|Tight cutoff"                              }

#define ENUM_APP_MODE_NO_FAIL_SAFE              \
   {0x00 , "|en|Setup"},           \
   {0x03 , "|en|Normal"}

#define ENUM_APP_MODE                           \
   {CHANGE_SETUP, "|en|Setup"},           \
   {CHANGE_FAILSAFE, "|en|Failsafe"},     \
   {CHANGE_NORMAL, "|en|Normal"}

#define ENUM_CUSTOM_CHAR_ACTION   \
   {0,  "|en|0. Initialize with Linear"}, \
   {1,  "|en|1. Initialize with Equal Percentage (30:1)"}, \
   {2,  "|en|2. Initialize with Equal Percentage (50:1)"}, \
   {3,  "|en|3. Initialize with Quick Open (reversal from Equal Percentage (50:1))"}, \
   {4,  "|en|4. Initialize with Custom"}, \
   {5,  "|en|5. Initialize with Camflex Percentage"}, \
   {7,  "|en|7. Initialize with Current"}, \
   {255,"|en|255. No Action "}

#define ENUM_CHAR_TYPE                                                                     \
   { 1,"|en|1. Linear"},                                                               \
   { 2,"|en|2. Equal Percentage (30:1)"},                                              \
   { 3,"|en|3. Equal Percentage (50:1)"},                                              \
   { 4,"|en|4. Quick Open (reversal from Equal Percentage (50:1))"},                   \
   { 5,"|en|5. Camflex Percentage"},                                                   \
   { 255,"|en|255. Custom (Defined in CUSTOM_CHAR_POINTS)"}

#define ENUM_BLOCK_ERR                                      \
    { 0x0001, "|en|Other" },                         \
    { 0x0002, "|en|Block Configuration Error" },     \
    { 0x0004, "|en|Link Configuration Error" },      \
    { 0x0008, "|en|Simulation Active" },             \
    { 0x0010, "|en|Local Override" },                \
    { 0x0020, "|en|Device Fault State Set" },        \
    { 0x0040, "|en|Device Needs Maintenance Soon" }, \
    { 0x0080, "|en|Sensor Failure Detected" },       \
    { 0x0100, "|en|Output Failure Detected" },       \
    { 0x0200, "|en|Memory Failure" },                \
    { 0x0400, "|en|Lost Static Data" },              \
    { 0x0800, "|en|Lost NV Data" },                  \
    { 0x1000, "|en|Readback Check Failed" },         \
    { 0x2000, "|en|Device Needs Maintenance Now" },  \
    { 0x4000, "|en|Reserved" },                      \
    { 0x8000, "|en|Out-of-Service" }

#define ENUM_UNACKNOWLEDGED                                                           \
   {0, "|en|0 = Undefined"},                                                          \
   {1, "|en|1 = Acknowledged"},                                                       \
   {2, "|en|2 = Unacknowledged"}

#define ENUM_UPDATE_STATE                                                             \
   {0, "|en|0 = Undefined"},                                                          \
   {1, "|en|1 = Update reported"},                                                    \
   {2, "|en|2 = Update not reported"}

#define ENUM_ALARM_STATE                                                              \
   {0, "|en|0 = Undefined"},                                                          \
   {1, "|en|1 = Clear - reported"},                                                   \
   {2, "|en|2 = Clear - not reported"},                                               \
   {3, "|en|3 = Active - reported"},                                                  \
   {4, "|en|4 = Active - not reported"}

#define ENUM_SUB_CODE \
   { 0x0000,  [subcode_other],           [subcode_other_help] },         \
   { 0x0001,  [subcode_block_config],    [subcode_block_config_help] },  \
   { 0x0002,  [subcode_link_config],     [subcode_link_config_help] },   \
   { 0x0003,  [subcode_simulation],      [subcode_simulation_help] },    \
   { 0x0004,  [subcode_override],        [subcode_override_help] },      \
   { 0x0005,  [subcode_fault_state],     [subcode_fault_state_help] },   \
   { 0x0006,  [subcode_maint_soon],      [subcode_maint_soon_help] },    \
   { 0x0007,  [subcode_input_fail],      [subcode_input_fail_help] },    \
   { 0x0008,  [subcode_output_fail],     [subcode_output_fail_help] },   \
   { 0x0009,  [subcode_mem_fail],        [subcode_mem_fail_help] },      \
   { 0x000A,  [subcode_lost_static],     [subcode_lost_static_help] },   \
   { 0x000B,  [subcode_lost_nv],         [subcode_lost_nv_help] },       \
   { 0x000C,  [subcode_readback_fail],   [subcode_readback_fail_help] }, \
   { 0x000D,  [subcode_maint_now],       [subcode_maint_now_help] },     \
   { 0x000E,  [subcode_power_up],        [subcode_power_up_help] },      \
   { 0x000F,  [subcode_out_of_service],  [subcode_out_of_service_help] }

#define ENUM_XD_ERROR_POS                                                             \
   {0, "|en|0 No Error"},                                                             \
   {16, "|en|16 Unspecified error"},            \
   {17, "|en|17 General error"},                                                      \
   {18, "|en|18 Calibration error"},                                                  \
   {19, "|en|19 Configuration error"},                                                \
   {20, "|en|20 Electronics Failure"},                                                \
   {21, "|en|21 Mechanical Failure"},                                                 \
   {22, "|en|22 I/O Failure"},                                                        \
   {23, "|en|23 Data Integrity Error"},                                               \
   {24, "|en|24 Software Error"},                                                     \
   {25, "|en|25 Algorithm Error"}

#define ENUM_CAL_TYPE																							\
  {CAL_TYPE_NOT_CALIBRATED,				 "|en|Not Calibrated"},							\
  {CAL_TYPE_CLOSED_ENDPOINT_MANUAL,		 "|en|Closed Endpoint(Manual)"},			\
  {CAL_TYPE_OPEN_ENDPOINT_MANUAL,		 "|en|Open Endpoint(Manual)"},				\
  {CAL_TYPE_BOTH_ENDPOINTS_MANUAL,		 "|en|Both Endpoints(Manual)"},			\
  {CAL_TYPE_BOTH_ENDPOINTS_AUTOMATIC,	 "|en|Both Endpoints(Automatic)"}, \
  {CAL_TYPE_CLONE,						 "|en|Cloned", "|en|Cloned(read-only)"} \
  /* {CAL_TYPE_READY_CLONE,				 "|en|Ready to Clone", "|en|Ready to Clone"}							\ */

#define ENUM_TYPE                                                                                                                            \
  {0,   "|en|Linear", "|en|Linear"},                                                                                                         \
  {1,   "|en|Equal Percentage (30:1)"},                                                                       \
  {2,   "|en|Equal Percentage (50:1)"},                                                                       \
  {3,   "|en|Quick Open", "|en|Reversal from Equal Percentage (50:1)"},                                                         \
  {4,   "|en|Custom"},                                                                                                         \
  {5,   "|en|Camflex Percentage"}
      /* \
  , Can't edit custom characterization in DD, so can't activate the edit \
  {255, "|en|Activate Custom (Defined in CUSTOM_CHAR.CUSTOM_CHAR_POINTS)", "|en|Activate Custom (Defined in CUSTOM_CHAR.CUSTOM_CHAR_POINTS)"}\
      */

#define ENUM_RELAY_TYPE                                                                                                                      \
  {1,   "|en|Standard Flow"},                                                                   \
  {2,   "|en|High Capacity"}

#define ENUM_VALVE_TYPE                                                                                                                      \
  {0,   "|en|Undefined"},                                                                                                   \
  {1,   "|en|Linear"},                                                                                                         \
  {2,   "|en|Rotary"},                                                                                                         \
  {255, "|en|Other"}                                                                                                            \

#define ENUM_UNITS_INDEX_PRESS                                                              \
       _UNIT_CODE_1133,\
       _UNIT_CODE_1141,\
       _UNIT_CODE_1137

#define ENUM_UNITS_INDEX_1342                                                              \
       _UNIT_CODE_1342

#ifndef DD4
#define ENUM_ALERT_LOG_COMMAND                                                          \
  {0x00, "|en|Copy & Reset", "|en|Copy the alert log and Reset the read index"},       \
  {0xFA, "|en|Clear", "|en|Clear the Alert log table"}
#else
#define ENUM_ALERT_LOG_COMMAND                                                          \
  {0x00, "|en|Copy & Reset"},       \
  {0xFA, "|en|Clear"}
#endif

/*
#define ENUM_ALERT_ACTION                                                           \
  {0, "|en|Not Reported"},                                                               \
  {1, "|en|Warning Data"},                                                               \
  {2, "|en|Maintenance Required"},                                                       \
  {3, "|en|Device Failure"}                                                             \
#endif
*/
#define ENUM_ACTIVATE_CONTROL_SET                                                     \
  { 0, "|en|0 :: Activate Custom Control Set" }, \
  { 1, "|en|1 :: Activate Control Set 1(Slowest)" }, \
  { 2, "|en|2 :: Activate Control Set 2" }, \
  { 3, "|en|3 :: Activate Control Set 3" }, \
  { 4, "|en|4 :: Activate Control Set 4" }, \
  { 5, "|en|5 :: Activate Control Set 5(Fastest)" }, \
  { 6, "|en|6 :: Activate Control Set 6(Double Acting-Slow)" }, \
  { 7, "|en|7 :: Activate Control Set 7(Double Acting-Fast)" }, \
  { 10, "|en|10 :: Restore Control set (make Backup Control Set Active)" }, \
  { 11, "|en|11 :: Make active control set as Custom control set" } \
  { 255, "|en|255:: Do Nothing" } \

#define ENUM_FIND_STOPS                                         \
  {FINDSTOPS_START,             "|en|Find stops Start"          },  \
  {FINDSTOPS_CANCEL,            "|en|Find stops Cancel"         },  \
  {FINDSTOPS_SETCLOSED,         "|en|Find stops LO"     }, \
  {FINDSTOPS_SETOPEN,           "|en|Find stops HI"       }, \
  {FINDSTOPS_ACCEPT,            "|en|Find stops Accept"         },  \
  {FINDSTOPS_COMMIT,            "|en|Find stops Commit"         },  \
  {FINDSTOPS_RUNNING,           "|en|Find stops Running"        },  \
  {FINDSTOPS_NOTRUNNING,        "|en|Find stops Not running"    }

#define ENUM_LAST_RESULT                \
  {0, "|en|No or failed calibration"},  \
  {1, "|en|Successful calibration"}     \

#define ENUM_DISCRETE_STATE             \
   {0, "|en|0 - Close"},                \
   {1, "|en|1 - Open"}

#define ENUM_DIAG_DIRECTION             \
  {0, "|en|0 - Both direction(default)" }, \
  {1, "|en|1 - One direction" }              \

#define ENUM_DIAG_OPTION                \
  {0, "|en|0 - Open Loop(default)" },   \
  {1, "|en|1 - Closed Loop" }           \

#define ENUM_ACTUATOR_TYPE \
  {SVI2_DBL_ACT, "|en|0 - Double Acting" },    \
  {SVI2_SNGL_ACT, "|en|1 - Single Acting" }         \

#define ENUM_UI_CUSTOM_CONFIGURATION    \
  {1, "|en|1 - WORK_SP" }               \
  {2, "|en|2 - WORK_POS"}               \
  {3, "|en|3 - PID1.SP" }               \
  {4, "|en|4 - PID1.PV" }               \
  {5, "|en|5 - PID1.OUT" }              \
  {6, "|en|6 - PID2.SP" }               \
  {7, "|en|7 - PID2.PV" }               \
  {8, "|en|8 - PID2.OUT" }              \
  {9, "|en|9 - AI1.OUT" }               \
  {10, "|en|10 - AI2.OUT" }             \
  {11, "|en|11 - AI3.OUT" }             \
  {12, "|en|12 - AO.SP" }               \
  {13, "|en|13 - DO1.SP_D" }              \
  {14, "|en|14 - DO2.SP_D" }              \
  {15, "|en|15 - IS.IN1" }              \
  {16, "|en|16 - IS.IN2" }              \
  {17, "|en|17 - IS.IN3" }              \
  {18, "|en|18 - IS.IN4" }              \

#define ENUM_UI_LANGUAGE     \
  { 0, "|en|0 - English"} \
  { 1, "|en|1 - French"} \
  { 2, "|en|2 - Spanish"} \
  { 3, "|en|3 - Portuguese"} \
  { 4, "|en|4 - Japanese"} \
  { 5, "|en|5 - Italian"} \
  { 6, "|en|6 - German"} \

#define ENUM_XD_FS_CONFIGURATION  \
  { 1, "1 - Copy once from AO/DO block" }                                   \
  { 2, "2 - Independent Configuration"} \

#define ENUM_ENABLE_DISABLE  \
  { _DISABLE, "Disable"} \
  { _ENABLE, "Enable" }                                   \


#define ENUM_COMPLETION \
  {AUTOTUNE_START,                              "|en|Starts the autotune process" } \
  {AUTOTUNE_CANCEL,                             "|en|Cancels the process" } \
  {AUTOTUNE_RUNNING,                            "|en|Running" } \
  {AUTOTUNE_NOT_RUN_OR_SUCCESS,                 "|en|0 - Not Run or Success"                    } \
  {AUTOTUNE_FAILED_ACTUATION,                   "|en|31 - Failed actuation"                     } \
  {AUTOTUNE_CONTROL_LIMITS_PROTECTED,           "|en|32 - Control limits protected"             } \
  {AUTOTUNE_FAILED_OPEN_LOOP_TUNING,            "|en|33 - Failed open loop tuning"              } \
  {AUTOTUNE_P_GAIN_BELOW_LIMIT,                 "|en|45 - P gain below limit"                   } \
  {AUTOTUNE_P_GAIN_ADJUSTMENT_ABOVE_LIMIT,      "|en|46 - P gain adjustment above limit"        } \
  {AUTOTUNE_BIAS_OUT_OF_RANGE,                  "|en|55 - Bias out of range"                    } \
  {AUTOTUNE_FILL_TIME_EXCEEDED,                 "|en|66 - Fill time exceeded"                   } \
  {AUTOTUNE_EXHAUST_TIME_EXCEEDED,              "|en|77 - Exhaust time exceeded"                } \
  {AUTOTUNE_OUT_OF_RANGE,                       "|en|88 - Parameter out of range"               } \

#define ENUM_REMOTE_SENSOR \
  { 0, "0 - Remote sensor is disabled/Not Active(Read Only)"} \
  { 1, "1 - Remote sensor is enabled(Read Only)"} \
  { 2, "2 - Enable Local HAL Sensor"} \
  { 3, "3 - Enable Remote Sensor"} \

#define ENUM_READBACK_SELECT                                                         \
{ 0, "0 - Final Position Value" }                                                           \
{ 1, "1 - Working Position Value" }                                                         \

#define ENUM_ACTIVE_STATE  \
  {0,  "|en|0 - Inactive" }                               \
  {1,  "|en|1 - Active"   }                             \

#define ENUM_IO_FAILURE  \
  {0,  "|en|No Error" }                               \
  {22,  "|en|22 I/O Failure" }                               \

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
*** Following will be removed
/~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*=================/
* Revision History
/=================*/

#endif
