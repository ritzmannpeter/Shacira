
#ifndef Euromap63_h
#define Euromap63_h 1

// general Euromap 63 version
#define EM63_VERSION "1.05a" // HA060206

// supported session layer error codes
#define SESSION_CODE_NO_ERROR       0
#define SESREQ_INVALID_SYNTAX       2
#define CREATE_JOB_RESPONSE_FILE    3
#define INTERFACE_STARTED           4
#define INTERFACE_BUSY              5
#define MACHINE_OFFLINE             6
#define JOBCMD_INVALID_SYNTAX       7


// supported presentation layer error codes
#define PRESENTATION_CODE_NO_ERROR  0
#define TOO_MANY_ACTIVE_JOBS        3
#define CREATE_DESTINATION_FILE     4
#define REPCMD_INVALID_SYNTAX       5
#define UNKNOWN_REPORT_PARAMETER    6
#define TOO_MANY_ACTIVE_REPORTS     7
#define EVTCMD_INVALID_SYNTAX       8
#define UNKNOWN_EVENT_TOKEN         9
#define TOO_MANY_ACTIVE_EVENTS      10
#define ABTCMD_INVALID_SYNTAX       11
#define UPLCMD_INVALID_SYNTAX       12
#define CREATE_UPLOAD_FILE          13
#define DWNCMD_INVALID_SYNTAX       14
#define OPEN_DOWNLOAD_FILE          15
#define DOWNLOAD_DENIED             16
#define INFCMD_INVALID_SYNTAX       17
#define IDSCMD_INVALID_SYNTAX       18
#define SETCMD_INVALID_SYNTAX       19
#define SET_DENIED                  20
#define SET_RANGE_ERROR             21
#define UNKNOWN_SET_PARAMETER       22
#define UNSUPPORTED_COMMAND         24
#define START_INVALID_SYNTAX        24
#define STOP_INVALID_SYNTAX         25
#define PARAMETER_TOO_LONG          26
#define NUMERIC_FORMAT              27
#define INVALID_OPERATOR            28
#define TIME_FORMAT                 29
#define DATE_FORMAT                 30
#define EOC_EXPECTED                31
#define UNKNOWN_ERROR               32
#define REPORT_RUNNING              33
#define EVENT_RUNNING               34
#define DOWNLOAD_RUNNING            35
#define ABTCMD_NOT_ACTIVE           36
#define PROCESSING_ERROR            37

// vendor specific presentation layer error codes 10000 - 99999999
#define UPLOAD_DENIED               10000
#define PROCESS_START_CONDITION     10001
#define PROCESS_STOP_CONDITION      10002
#define PROCESS_CYCLE_CONDITION     10003
#define PROCESS_REPORT_CONDITION    10004
#define PROCESS_REPORT_BUF_TOO_SMALL 10005
#define CREATE_SESSION_RESPONSE_FILE 10006
#define OPEN_JOB_REQUEST_FILE       10007
#define JOB_WITH_THE_SAME_NAME      10008
#define SESSION_NUMBER_TO_LARGE     10009


// presentation command types

#define EM63_UNDEFINED_COMMAND           0
#define EM63_REPORT_COMMAND              1
#define EM63_GETINFO_COMMAND             2
#define EM63_EVENT_COMMAND               3
#define EM63_ABORT_COMMAND               4
#define EM63_UPLOAD_COMMAND              5
#define EM63_DOWNLOAD_COMMAND            6
#define EM63_SET_COMMAND                 7
#define EM63_GETID_COMMAND               8
#define EM63_JOB_COMMAND                 9

// abort type specification

#define ABORT_ALL                        1
#define ABORT_ALL_JOBS                   2
#define ABORT_ALL_REPORTS                3
#define ABORT_ALL_EVENTS                 4
#define ABORT_JOB                        5
#define ABORT_REPORT                     6
#define ABORT_EVENT                      7

#define EM63_READONLY                    0
#define EM63_WRITEABLE                   1

#define PARAM_ID_SIZE      255
#define UNIT_SIZE          255
#define DESCRIPTION_SIZE   255
#define DIMTEXT_SIZE       255

#define EM63_SESSION       0
#define EM63_PRESENTATION  1

#define E63_NO_ERROR          0
#define E63_MINIMUM_ERROR     1
#define E63_MAXIMUM_ERROR     2
#define E63_UNKNOWN_PARAM_ID  3
#define E63_UNKNOWN_VARREF    4
#define E63_UNKNOWN_VARIABLE  5
#define E63_ACCESS_DENIED     6

#endif

