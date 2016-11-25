
#ifndef ObjectTypes_h
#define ObjectTypes_h 1

#define UNDEFINED                   0

// Transient Object Types
#define OT_EVENT                    1
#define OT_ALARM                    2
#define OT_INFO                     3
#define OT_STATE                    4

#define OT_DATA_CHANGE              6
#define OT_REQUEST                  7
#define OT_JOB_SPEC                 8
#define OT_JOB_ENTRY                9

#define OT_LOCAL_CELL_PROXY         11
#define OT_CORBA_CELL_PROXY         12
#define OT_COS_EVENTCHANNEL_PROXY   13
#define OT_USER_INFO                14
#define OT_PROGRESS                 15
#define OT_PROTOCOL                 16
#define USER_DEFINED_OBJECT_TYPES   1000

// Info Types
#define IT_USER_INFO                1
#define IT_ALARM_INFO               2
#define IT_CUSTOM_INFO              3
#define IT_PROGRESS_INFO            4

// Event codes
#define EC_CYCLE                    1
#define EC_DATA_INPUT               2
#define EC_DATA_ENTRY               3
#define EC_DATA_CHANGE              4
#define EC_JOB_COMPLETION           5

// Static object types

#define OT_CHANNEL                  1
#define OT_ADAPTER                  2
#define OT_SERIAL_CHANNEL           3
#define OT_DIGITAL_CHANNEL          4
#define OT_DRIVER                   5
#define OT_CELL                     6

// Serial Channel types
#define CHANNEL_STANDARD            1
#define CHANNEL_SOCKET              2
#define CHANNEL_VSOCKET             3

// Digital Channel types
#define MEMORY_IO                   1
#define ADDI_UNIVERSAL              2
#define ADDI_PA150                  3

// Driver types
#define VIRTUAL                  1
#define FM1                      2
#define FM2                      3
#define FM3                      4
#define DEMAG_NC3                5
#define DEMAG_NC4                6
#define KM_MC2                   7
#define KM_MC3                   8
#define KM_MC4                   9
#define ND221                    10
#define ND920                    11
#define MITUTOYO                 12
#define INTERMEC_4100            13
#define INTERMEC_DIRECT          14
#define ZEBRA                    15
#define OPTISCAN                 16
#define SCANNER                  17
#define MACHINE_SIMULATION       18
#define BRANSON_USS              19
#define IO_DRIVER                20
#define PPCCOM                   21
#define MODBUS_RTU               22
#define PROGRAMMABLE             23
#define GRABBER                  24

// Program types
#define PGM_STD                  1
#define PGM_AIRBAG               2
#define PGM_USS                  3
#define PGM_IMM                  4
#define PGM_SPS                  5
#define PGM_TEST                 6
#define PGM_VCP                  7

// Job types
#define JT_ON_CYCLE              1
#define JT_ON_INTERVAL           2
#define JT_ON_TIME               3
#define JT_ON_NEW_DATA           4

// Channel types
#define LOCAL_CHANNEL            1
#define REMOTE_BRIDGE            2

// Adapter types
#define CONNECTOR                1

// Event channel Types
#define COS_EVENT_COMM_VISIBROKER   1
#define COS_EVENT_COMM_OMNIORB      2
#define UDP_EVENT_COMM              3
#define TCP_EVENT_COMM              4
#define COMM_EVENT_COMM             5

// Receiver and Sender Types
#define UDP_SOCKET		    1
#define EVENT_CHANNEL		    2

// Part quality
#define CELL_SOFTWARE_ERROR      -2
#define NO_QUALITY               -1
#define GOOD_PART                0
#define MACHINE_TOLERANCE        1
#define CELL_STARTUP_PART        10
#define DEVICE_READ_PROBLEM      11
#define MISSING_DEVICE_DATA      12
#define SPLITLINE_LOWER_TOL      20
#define SPLITLINE_UPPER_TOL      21
#define SPLITLINE_READ_PROBLEM   22
#define SPLITLINE_DATA_PROBLEM   23
#define BARCODE_PRINT_PROBLEM    30
#define BARCODE_READ_PROBLEM     31
#define BARCODE_MISMATCH         32
#define DATA_LOG_PROBLEM         40


// General type definitions
// Production states
#define SH_STOPPED		 1
#define SH_SETUP		 2
#define SH_MANUAL		 3
#define SH_SEMI_AUTOMATIC	 4
#define SH_AUTOMATIC		 5
#define SH_OILHEATING		 6
#define SH_TIPPMODE		 7

// Machine states
#define PRODUCTION		   0

// Configuration states
#define SH_CONFIGURED		0
#define SH_NOT_CONFIGURED	0xFF

// Access types
#define SH_NO_ACCESS		      1
#define SH_READ_ACCESS		   2
#define SH_WRITE_ACCESS		   3
#define SH_READ_WRITE_ACCESS	4

// Database type definitions

// variable types

#define SH_VAR_SET		1
#define SH_VAR_ACT		2
#define SH_VAR_VOLATILE		3
#define SH_VAR_VIRTUAL		4

// persistence types

#define SH_RAM			1
#define SH_BBRAM		2
#define SH_FILE		3
#define SH_SETUP_PST 4

// dimension types

#define SH_SEC			1
#define SH_MM			3
#define SH_BAR			4
#define SH_NEWTON		5
#define SH_CELSIUS		6
#define SH_FAHRENHEIT		7

// refresh types

#define SH_REFRESH_EVENT	1
#define SH_REFRESH_INTERVAL	2

// event types

#define SH_EVENT_TIMER		1
#define SH_EVENT_CYCLE		2
#define SH_EVENT_AUTOMATIC	3
#define SH_EVENT_DATA		4

// data types

#define SH_VOID      		1
#define SH_CHAR			2
#define SH_UCHAR		3
#define SH_SHORT		4
#define SH_USHORT		5
#define SH_LONG			6
#define SH_ULONG		7
#define SH_FLOAT		8
#define SH_DOUBLE		9
#define SH_STRING		10
#define SH_WSTRING		11
#define SH_BYTE                 12
#define SH_OBJECT               13
#define SH_BIT_8                14
#define SH_BIT_16               15
#define SH_BIT_32               16


#define IS_INT(type)      (type==SH_CHAR || \
                           type==SH_UCHAR || \
                           type==SH_SHORT || \
                           type==SH_USHORT || \
                           type==SH_LONG || \
                           type==SH_ULONG)
#define IS_REAL(type)         (type==SH_FLOAT || \
                               type==SH_DOUBLE)
#define IS_NUMBER(type)       (IS_INT(type) || IS_REAL(type))
#define IS_STRING(type)       (type==SH_STRING || \
                               type==SH_WSTRING)
#define IS_VOID(type)         (type==SH_VOID)
#define TYPE_UNSPECIFIED(type) (type == UNDEFINED || IS_VOID(type))
#define TYPE_SPECIFIED(type)  (type != UNDEFINED && !IS_VOID(type))

#undef STRICT_COMPATIBILITY
#ifdef STRICT_COMPATIBILITY
#define TYPES_COMPATIBLE(t1,t2) \
  ( \
   ((IS_INT(t1) && IS_INT(t2))) || \
   ((IS_REAL(t1) && IS_REAL(t2))) || \
   ((IS_STRING(t1) && IS_STRING(t2))) || \
   ((IS_VOID(t1) && IS_VOID(t2))) \
  )
#else
#define TYPES_COMPATIBLE(t1,t2) \
  ( \
   (t1 == t2) || \
   ((IS_NUMBER(t1) && IS_NUMBER(t2))) \
  )
#endif

// variable value flags

#define VF_BUFFERED                 0x00000001
#define VF_UNFORMATTED              0x00000002
#define VF_DEVICE                   0x00000004
#define VF_WRITE                    0x00000008
#define VF_FOREGROUND               0x00000010
#define VF_BACKGROUND               0x00000020
#define VF_NATIVE_REPRESENTATION    0x00000040
#define VF_DEVICE_REPRESENTATION    0x00000080
#define VF_DATASET_REPRESENTATION   0x00000100
#define VF_MEMORY_ACCESS            0x00000200
#define VF_SHADOW                   0x00000400
#define VF_FORCE_EVENT              0x00000800
#define VF_FILE_INPUT               0x00001000
#define VF_NO_DATACHANGE            0x00002000

#define VF_GET_IF_TYPE(flags)           (flags >> 24)
#define VF_SET_IF_TYPE(flags,if_type)   flags = (flags & 0x00ffffff) | (((ULONG_T)if_type) << 24);

// function classes

#define SH_FREE                 1
#define SH_EMBED                2
#define SH_FILTER               3
#define SH_CONVERSION           4
#define SH_LIMIT                5
#define SH_VIEW                 6
#define SH_DARK                 7
#define SH_PLAUS                8
#define SH_USER                 9
#define SH_BUTTON               10
#define SH_SIG_FILTER           11
#define SH_SLOT                 12
#define SH_VALUE                13
#define SH_UNIT                 14
#define SH_EVENT_FILTER         15
#define SH_WINIT                16
#define SH_ACCESS               17
#define SH_DEVICE_STATE         18

// io card types

#define IO_ADDI_STANDARD        1
#define IO_ADDI_PA150 	        2
#define IO_MEMORY	        3

// variable system flags

#define HOST_READ       0x00000001
#define HOST_WRITE      0x00000002
#define DIM1_OFFSET     0x00000004
#define DIM2_OFFSET     0x00000008
#define DIM3_OFFSET     0x00000010
#define DIM4_OFFSET     0x00000020
#define EM63_VARIABLE   0x00000040

// host interface types
#define IF_PROPRIETARY	0

#define IF_OPC		10
#define IF_EM63		11
#define IF_MAX		(IF_EM63+1)

#endif

