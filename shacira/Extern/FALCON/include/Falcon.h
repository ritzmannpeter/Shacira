/*
######################################################################
#                                                                    #
# File:    falcon.h                                                  #
# Project: Library interface for IDS FALCON/EAGLE-Board              #
#                                                                    #
# Revision History:                                                  #
#                                                                    #
# Ed   When   Who   What                                             #
# -- -------- ---- ------------------------------------------------  #
# 01 13.08.97 av   Created for WinNT 4.0                             #
# 02 22.08.97 av   Added memory management  is_AllocImageMem      () #
#                                           is_FreeImageMem       () #
#                                           is_SetImageMem        () #
#                                                                    #
#                  Added new function       is_FreezeVideo        () #
#                                           is_IsVideoFinish      () #
#                                                                    #
# 03 19.09.97 av   Added DirectDraw Overlay functions                #
#                                           is_EnableDDOverlay    () #
#                                           is_DisableDDOverlay   () #
#                                           is_ShowDDOverlay      () #
#                                           is_HideDDOverlay      () #
#                                           is_GetDDOverlayMem    () #
#                                           is_GetDC              () #
#                                           is_ReleaseDC          () #
#                                           is_SetDDUpdateTime    () #
#                                           is_LockDDOverlayMem   () #
#                                           is_UnlockDDOverlayMem () #
#                                           is_LockDDMem          () #
#                                           is_UnlockDDMem        () #
#                                                                    #
# 03 22.10.97 av   Added VSYNC count function                        #
#                                           is_GetVsyncCount      () #
# 03 22.10.97 av   Added Field-Flag function                         #
#                                           is_GetCurrentField    () #
#                                                                    #
# 03 23.10.97 av   Added event handling on VSYNC interrupt           #
#                                           is_InitEvent          () #
#                                           is_ExitEvent          () #
#                                           is_EnableEvent        () #
#                                           is_DisableEvent       () #
#                                                                    #
# 03 28.10.97 av   Added new function       is_GetImageMemPitch   () #
#                                                                    #
# 04 23.11.97 av   Added S3 ColorKey Overlay surface function        #
#                                           IS_SET_DM_ALLOW_OVERLAY  #
#                                           is_SetColorKey        () #
#                                                                    #
# 05 09.12.97 av   Added new function to set image borders           #
#                  (adjustment to diferent cameras)                  #
#                                           is_SetVideoSize       () #
#                                                                    #
# 06 11.12.97 av   Minor bug fixes in new S3 overlay surface mode    #
#                                                                    #
# 07 12.12.97 av   Corrected EEPROM read function for Win95          #
#                  for PPro systems                                  #
#                                                                    #
# 08 18.12.97 av   Minor bug fixes in new S3 overlay surface mode    #
#                  under Win95                                       #
#                                                                    #
# 09 09.01.98 av   Added new function to steal one frame into        #
#                  the system memory out of the video stream under   #
#                  DirectDraw mode                                   #
#                                           is_PrepareStealVideo  () #
#                                           is_StealVideo         () #
#                                                                    #
# 10 18.03.98 av   Added new function to perform double- and         #
#                  ringbuffering                                     #
#                                           is_AddToSequence      () #
#                                           is_ClearSequence      () #
#                                           is_GetActSeqBuf       () #
#                                           is_LockSeqBuf         () #
#                                           is_UnlockSeqBuf       () #
#                                                                    #
# 11 19.03.98 av   Added new function to get current VGA color       #
#                  setting                                           #
#                                           is_GetColorDepth      () #
#                                                                    #
# 12 07.07.98 ab   Added functions for EAGLE                         #
#                                           is_GetBoardType       () #
#                                           is_BoardStatus        () #
#                                           is_SetSync            () #
#                                           is_SetIO              () #
#                                           is_SetFlashStrobe     () #
#                                           is_SetExternalTrigger () #
#                                                                    #
# 13 01.07.01 av   Added FALCON Duo / Quattro support                #
#                                           is_SetVideoCrossbar()    #
#                                                                    #
# 13 05.07.01 av   Added new function                                #
#                                           is_GetIRQ()              #
#                                                                    #
######################################################################
*/

#ifndef __IDS_HEADER__
#define __IDS_HEADER__


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// ------------------------------------------
// error codes
// ------------------------------------------
#define IS_NO_SUCCESS                      -1
#define IS_SUCCESS                          0 
#define IS_INVALID_FALCON_HANDLE            1
#define IS_INVALID_HANDLE                   1
#define IS_IO_REQUEST_FAILED                2
#define IS_CANT_OPEN_DEVICE                 3
#define IS_CANT_CLOSE_DEVICE                4
#define IS_CANT_SETUP_MEMORY                5
#define IS_NO_HWND_FOR_ERROR_REPORT         6
#define IS_ERROR_MESSAGE_NOT_CREATED        7
#define IS_ERROR_STRING_NOT_FOUND           8
#define IS_HOOK_NOT_CREATED                 9
#define IS_TIMER_NOT_CREATED               10
#define IS_CANT_OPEN_REGISTRY              11
#define IS_CANT_READ_REGISTRY              12
#define IS_CANT_VALIDATE_BOARD             13
#define IS_CANT_GIVE_BOARD_ACCESS          14
#define IS_NO_IMAGE_MEM_ALLOCATED          15
#define IS_CANT_CLEANUP_MEMORY             16
#define IS_CANT_COMMUNICATE_WITH_DRIVER    17
#define IS_FUNCTION_NOT_SUPPORTED_YET      18
#define IS_OPERATING_SYSTEM_NOT_SUPPORTED  19

#define IS_INVALID_VIDEO_IN                20
#define IS_INVALID_IMG_SIZE                21
#define IS_INVALID_ADDRESS                 22
#define IS_INVALID_VIDEO_MODE              23
#define IS_INVALID_AGC_MODE                24
#define IS_INVALID_GAMMA_MODE              25
#define IS_INVALID_SYNC_LEVEL              26
#define IS_INVALID_CBARS_MODE              27
#define IS_INVALID_COLOR_MODE              28
#define IS_INVALID_SCALE_FACTOR            29
#define IS_INVALID_IMAGE_SIZE              30
#define IS_INVALID_IMAGE_POS               31
#define IS_INVALID_CAPTURE_MODE            32
#define IS_INVALID_RISC_PROGRAM            33
#define IS_INVALID_BRIGHTNESS              34
#define IS_INVALID_CONTRAST                35
#define IS_INVALID_SATURATION_U            36
#define IS_INVALID_SATURATION_V            37
#define IS_INVALID_HUE                     38
#define IS_INVALID_HOR_FILTER_STEP         39
#define IS_INVALID_VERT_FILTER_STEP        40
#define IS_INVALID_EEPROM_READ_ADDRESS     41
#define IS_INVALID_EEPROM_WRITE_ADDRESS    42
#define IS_INVALID_EEPROM_READ_LENGTH      43
#define IS_INVALID_EEPROM_WRITE_LENGTH     44
#define IS_INVALID_BOARD_INFO_POINTER      45
#define IS_INVALID_DISPLAY_MODE            46
#define IS_INVALID_ERR_REP_MODE            47
#define IS_INVALID_BITS_PIXEL              48
#define IS_INVALID_MEMORY_POINTER          49

#define IS_FILE_WRITE_OPEN_ERROR           50
#define IS_FILE_READ_OPEN_ERROR            51
#define IS_FILE_READ_INVALID_BMP_ID        52
#define IS_FILE_READ_INVALID_BMP_SIZE      53
#define IS_FILE_READ_INVALID_BIT_COUNT     54
#define IS_WRONG_KERNEL_VERSION            55

#define IS_RISC_INVALID_XLENGTH            60
#define IS_RISC_INVALID_YLENGTH            61
#define IS_RISC_EXCEED_IMG_SIZE            62

#define IS_DD_MAIN_FAILED                  70
#define IS_DD_PRIMSURFACE_FAILED           71
#define IS_DD_SCRN_SIZE_NOT_SUPPORTED      72
#define IS_DD_CLIPPER_FAILED               73
#define IS_DD_CLIPPER_HWND_FAILED          74
#define IS_DD_CLIPPER_CONNECT_FAILED       75 
#define IS_DD_BACKSURFACE_FAILED           76
#define IS_DD_BACKSURFACE_IN_SYSMEM        77
#define IS_DD_MDL_MALLOC_ERR               78
#define IS_DD_MDL_SIZE_ERR                 79
#define IS_DD_CLIP_NO_CHANGE               80
#define IS_DD_PRIMMEM_NULL                 81
#define IS_DD_BACKMEM_NULL                 82
#define IS_DD_BACKOVLMEM_NULL              83
#define IS_DD_OVERLAYSURFACE_FAILED        84
#define IS_DD_OVERLAYSURFACE_IN_SYSMEM     85
#define IS_DD_OVERLAY_NOT_ALLOWED          86
#define IS_DD_OVERLAY_COLKEY_ERR           87
#define IS_DD_OVERLAY_NOT_ENABLED          88
#define IS_DD_GET_DC_ERROR                 89
#define IS_DD_DDRAW_DLL_NOT_LOADED         90
#define IS_DD_THREAD_NOT_CREATED           91
#define IS_DD_CANT_GET_CAPS                92
#define IS_DD_NO_OVERLAYSURFACE            93
#define IS_DD_NO_OVERLAYSTRETCH            94
#define IS_DD_CANT_CREATE_OVERLAYSURFACE   95
#define IS_DD_CANT_UPDATE_OVERLAYSURFACE   96
#define IS_DD_INVALID_STRETCH              97

#define IS_EV_INVALID_EVENT_NUMBER        100
#define IS_INVALID_MODE                   101
#define IS_CANT_FIND_FALCHOOK             102
#define IS_CANT_FIND_HOOK                 102
#define IS_CANT_GET_HOOK_PROC_ADDR        103
#define IS_CANT_CHAIN_HOOK_PROC           104
#define IS_CANT_SETUP_WND_PROC            105
#define IS_HWND_NULL                      106
#define IS_INVALID_UPDATE_MODE            107
#define IS_NO_ACTIVE_IMG_MEM              108
#define IS_CANT_INIT_EVENT                109
#define IS_FUNC_NOT_AVAIL_IN_OS           110
#define IS_CAMERA_NOT_CONNECTED           111
#define IS_SEQUENCE_LIST_EMPTY            112
#define IS_CANT_ADD_TO_SEQUENCE           113
#define IS_LOW_OF_SEQUENCE_RISC_MEM       114
#define IS_IMGMEM2FREE_USED_IN_SEQ        115
#define IS_IMGMEM_NOT_IN_SEQUENCE_LIST    116
#define IS_SEQUENCE_BUF_ALREADY_LOCKED    117
#define IS_INVALID_DEVICE_ID              118
#define IS_INVALID_BOARD_ID               119
#define IS_ALL_DEVICES_BUSY               120
#define IS_HOOK_BUSY                      121
#define IS_TIMED_OUT                      122
#define IS_NULL_POINTER                   123
#define IS_WRONG_HOOK_VERSION             124
#define IS_INVALID_PARAMETER              125
#define IS_NOT_ALLOWED                    126
#define IS_OUT_OF_MEMORY                  127
#define IS_INVALID_WHILE_LIVE             128
#define IS_ACCESS_VIOLATION               129
#define IS_UNKNOWN_ROP_EFFECT             130
#define IS_INVALID_RENDER_MODE            131
#define IS_INVALID_THREAD_CONTEXT         132
#define IS_NO_HARDWARE_INSTALLED          133

#define IS_WRONG_KEY                      150

// ------------------------------------------
// common definitions
// ------------------------------------------
#define IS_OFF      0
#define IS_ON       1


// ------------------------------------------
// get/set selector
// ------------------------------------------
#define IS_GET_ERR_REP_MODE      0x8000
#define IS_GET_VIDEO_IN          0x8000
#define IS_GET_VIDEO_IN_TOGGLE   0x8001
#define IS_GET_LIVE              0x8000
#define IS_GET_BRIGHTNESS        0x8000
#define IS_GET_CONTRAST          0x8000
#define IS_GET_SATURATION_U      0x8000
#define IS_GET_SATURATION_V      0x8001
#define IS_GET_HUE               0x8000
#define IS_GET_VIDEO_MODE        0x8000
#define IS_GET_DISPLAY_MODE      0x8000
#define IS_GET_AGC_MODE          0x8000
#define IS_GET_GAMMA_MODE        0x8000
#define IS_GET_SYNC_LEVEL        0x8000
#define IS_GET_CBARS_MODE        0x8000
#define IS_GET_COLOR_MODE        0x8000
#define IS_GET_CAPTURE_MODE      0x8000
#define IS_GET_IMAGE_SIZE_X      0x8000
#define IS_GET_IMAGE_SIZE_Y      0x8001
#define IS_GET_IMAGE_POS_X       0x8000
#define IS_GET_IMAGE_POS_Y       0x8001
#define IS_GET_HOR_FILTER_MODE   0x8000
#define IS_GET_HOR_FILTER_STEP   0x8001
#define IS_GET_VERT_FILTER_MODE  0x8000
#define IS_GET_VERT_FILTER_STEP  0x8001
#define IS_GET_SCALER_MODE       (float) 1000
#define IS_GET_KC_RED            0x8000
#define IS_GET_KC_GREEN          0x8001
#define IS_GET_KC_BLUE           0x8002
#define IS_GET_KC_RGB            0x8003
#define IS_GET_KC_INDEX          0x8004
#define IS_GET_KEYOFFSET_X       0x8000
#define IS_GET_KEYOFFSET_Y       0x8001
#define IS_GET_UPDATE_MODE       0x8000
#define IS_GET_SYNC_GEN          0x8000
#define IS_GET_IO                0x8000
#define IS_GET_FLASHSTROBE_FIELD 0x8000
#define IS_GET_FLASHSTROBE_LINE  0x8001
#define IS_GET_EXTERNALTRIGGER   0x8000
#define IS_GET_TRIGGER_STATUS    0x8001
#define IS_GET_TRIGGER_MASK      0x8002
#define IS_GET_TRIGGER_INPUTS    0x8003
#define IS_GET_STATUS            0x8000
#define IS_GET_TOGGLE_INPUT_1    0x8000
#define IS_GET_TOGGLE_INPUT_2    0x8001
#define IS_GET_TOGGLE_INPUT_3    0x8002
#define IS_GET_TOGGLE_INPUT_4    0x8003
#define IS_GET_CROSSBAR          0x8000
#define IS_GET_DD_OVERLAY_SCALE  0x8000

// ------------------------------------------
// horizontal filter defines
// ------------------------------------------
#define IS_DISABLE_HOR_FILTER    0
#define IS_ENABLE_HOR_FILTER     1
#define IS_HOR_FILTER_STEP(_s_)  ((_s_ + 1) << 1)
#define IS_HOR_FILTER_STEP1      2
#define IS_HOR_FILTER_STEP2      4
#define IS_HOR_FILTER_STEP3      6

// ------------------------------------------
// vertical filter defines
// ------------------------------------------
#define IS_DISABLE_VERT_FILTER    0
#define IS_ENABLE_VERT_FILTER     1
#define IS_VERT_FILTER_STEP(_s_)  ((_s_ + 1) << 1)
#define IS_VERT_FILTER_STEP1      2
#define IS_VERT_FILTER_STEP2      4
#define IS_VERT_FILTER_STEP3      6

// ------------------------------------------
// image parameters
// ------------------------------------------
#define IS_DEFAULT_BRIGHTNESS     100
#define IS_DEFAULT_CONTRAST       216
#define IS_DEFAULT_SATURATION_U   254
#define IS_DEFAULT_SATURATION_V   180
#define IS_DEFAULT_HUE            128
#define IS_MIN_BRIGHTNESS           0
#define IS_MIN_CONTRAST             0
#define IS_MIN_SATURATION_U         0
#define IS_MIN_SATURATION_V         0
#define IS_MIN_HUE                  0
#define IS_MAX_BRIGHTNESS         255
#define IS_MAX_CONTRAST           511
#define IS_MAX_SATURATION_U       511
#define IS_MAX_SATURATION_V       511
#define IS_MAX_HUE                255

// ------------------------------------------
// error report modes
// ------------------------------------------
#define IS_ENABLE_ERR_REP     1
#define IS_DISABLE_ERR_REP    0

// ------------------------------------------
// video source selectors
// ------------------------------------------
#define IS_SET_VIDEO_IN_1       0x00
#define IS_SET_VIDEO_IN_2       0x01
#define IS_SET_VIDEO_IN_S       0x02
#define IS_SET_VIDEO_IN_3       0x03
#define IS_SET_VIDEO_IN_4       0x04
#define IS_SET_VIDEO_IN_1S      0x10
#define IS_SET_VIDEO_IN_2S      0x11
#define IS_SET_VIDEO_IN_3S      0x13
#define IS_SET_VIDEO_IN_4S      0x14
#define IS_SET_TOGGLE_OFF       0xFF
#define IS_SET_VIDEO_IN_SYNC  0x4000

// ------------------------------------------
// video crossbar selectors
// ------------------------------------------
#define IS_CROSSBAR_1            0
#define IS_CROSSBAR_2            1
#define IS_CROSSBAR_3            2
#define IS_CROSSBAR_4            3
#define IS_CROSSBAR_5            4
#define IS_CROSSBAR_6            5
#define IS_CROSSBAR_7            6
#define IS_CROSSBAR_8            7
#define IS_CROSSBAR_9            8
#define IS_CROSSBAR_10           9
#define IS_CROSSBAR_11          10
#define IS_CROSSBAR_12          11
#define IS_CROSSBAR_13          12
#define IS_CROSSBAR_14          13
#define IS_CROSSBAR_15          14
#define IS_CROSSBAR_16          15
#define IS_SELECT_AS_INPUT      128

// ------------------------------------------
// video format selectors
// ------------------------------------------
#define IS_SET_VM_PAL       0
#define IS_SET_VM_NTSC      1
#define IS_SET_VM_SECAM     2
#define IS_SET_VM_AUTO      3

// ------------------------------------------
// display mode selectors
// ------------------------------------------
#define IS_SET_DM_DIB              1
#define IS_SET_DM_DIRECTDRAW       2
#define IS_SET_DM_ALLOW_SYSMEM     0x40
#define IS_SET_DM_ALLOW_PRIMARY    0x80

// -- overlay display mode ---
#define IS_SET_DM_ALLOW_OVERLAY    0x100  
#define IS_SET_DM_ALLOW_SCALING    0x200
#define IS_SET_DM_ALLOW_FIELDSKIP  0x400

// ------------------------------------------
// bitmap render modes
// ------------------------------------------
#define IS_RENDER_NORMAL             0
#define IS_RENDER_FIT_TO_WINDOW      1
#define IS_RENDER_DOWNSCALE_1_2      2
#define IS_RENDER_MIRROR_UPDOWN     16
#define IS_RENDER_HALF_HEIGHT       32
#define IS_RENDER_USE_MEMORY_COLOR  64

// ------------------------------------------
// save options
// ------------------------------------------
#define IS_SAVE_USE_ACTUAL_IMAGE_SIZE    0x00010000

// ------------------------------------------
// AGC modes
// ------------------------------------------
#define IS_SET_AGC_OFF      0
#define IS_SET_AGC_ON       1

// ------------------------------------------
// Gamma modes
// ------------------------------------------
#define IS_SET_GAMMA_OFF    0
#define IS_SET_GAMMA_ON     1

// ------------------------------------------
// sync levels
// ------------------------------------------
#define IS_SET_SYNC_75      0
#define IS_SET_SYNC_125     1

// ------------------------------------------
// color bar modes
// ------------------------------------------
#define IS_SET_CBARS_OFF    0
#define IS_SET_CBARS_ON     1

// ------------------------------------------
// scaler modes
// ------------------------------------------
#define IS_SET_SCALER_OFF   (float) 0
#define IS_SET_SCALER_ON    (float) 1

#define IS_MIN_SCALE_X      (float)   6.25
#define IS_MAX_SCALE_X      (float) 100.00
#define IS_MIN_SCALE_Y      (float)   6.25
#define IS_MAX_SCALE_Y      (float) 100.00

// ------------------------------------------
// color modes
// ------------------------------------------
#define IS_SET_CM_RGB32      0
#define IS_SET_CM_RGB24      1
#define IS_SET_CM_RGB16      2
#define IS_SET_CM_RGB15      3
#define IS_SET_CM_Y8         6
#define IS_SET_CM_RGB8       7

// ------------------------------------------
// capture modes
// ------------------------------------------
#define IS_SET_CM_ODD             0x0001
#define IS_SET_CM_EVEN            0x0002
#define IS_SET_CM_FRAME           0x0004
#define IS_SET_CM_NONINTERLACED   0x0008
#define IS_SET_CM_NEXT_FRAME      0x0010
#define IS_SET_CM_NEXT_FIELD      0x0020
#define IS_SET_CM_BOTHFIELDS      (IS_SET_CM_ODD | IS_SET_CM_EVEN | IS_SET_CM_NONINTERLACED)
#define IS_SET_CM_FRAME_STEREO    0x2004

// ------------------------------------------
// live/freeze parameters
// ------------------------------------------
#define IS_WAIT               0x0001
#define IS_DONT_WAIT          0x0000
#define IS_FORCE_VIDEO_STOP   0x4000
#define IS_FORCE_VIDEO_START  0x4000

// ------------------------------------------
// video finish constants
// ------------------------------------------
#define IS_VIDEO_NOT_FINISH    0
#define IS_VIDEO_FINISH        1

// ------------------------------------------
// event constants
// ------------------------------------------
#define IS_SET_EVENT_ODD      0
#define IS_SET_EVENT_EVEN     1
#define IS_SET_EVENT_FRAME    2
#define IS_SET_EVENT_EXTTRIG  3
#define IS_SET_EVENT_VSYNC    4
#define IS_SET_EVENT_SEQ      5
#define IS_SET_EVENT_STEAL    6
#define IS_SET_EVENT_VPRES    7

// ------------------------------------------
// steal video constants
// ------------------------------------------
#define IS_INIT_STEAL_VIDEO         1
#define IS_EXIT_STEAL_VIDEO         2
#define IS_INIT_STEAL_VIDEO_MANUAL  3
#define IS_INIT_STEAL_VIDEO_AUTO    4
#define IS_SET_STEAL_RATIO         64
#define IS_STEAL_MODES_MASK         7

// ------------------------------------------
// display update mode constants
// ------------------------------------------
#define IS_SET_UPDATE_TIMER    1
#define IS_SET_UPDATE_EVENT    2

// ------------------------------------------
// keying color constants
// ------------------------------------------
// RGB-triple for default key-color in 15,16,24,32 bit mode
#define IS_SET_KC_DEFAULT    0xFF00FF    // 0xbbggrr    
// colorindex for default key-color in 8bit palette mode
#define IS_SET_KC_DEFAULT_8       253

// ------------------------------------------
// sync generator mode constants
// ------------------------------------------
#define IS_SET_SYNC_GEN_OFF      0
#define IS_SET_SYNC_GEN_ON       1

// ------------------------------------------
// flash strobe constants
// ------------------------------------------
#define IS_SET_FLASH_OFF       0x0000
#define IS_SET_FLASH_ODD       0x1000
#define IS_SET_FLASH_EVEN      0x2000
#define IS_SET_FLASH_HI_ACTIVE 0x4000

// ------------------------------------------
// external trigger mode constants
// ------------------------------------------
#define IS_SET_TRIG_OFF          0x000
#define IS_SET_TRIG_HI_LO        0x001
#define IS_SET_TRIG_LO_HI        0x002
#define IS_SET_TRIG_EVENT_ONLY   0x004
#define IS_SET_TRIG_MASK         0x100

// ------------------------------------------
// board info constants
// ------------------------------------------
#define IS_EXT_TRIGGER_EVENT_CNT    0
#define IS_FIFO_OVR_CNT             1
#define IS_SEQUENCE_CNT             2
#define IS_LAST_FRAME_FIFO_OVR      3
#define IS_SEQUENCE_SIZE            4
#define IS_VIDEO_PRESENT            5
#define IS_STEAL_FINISHED           6
#define IS_STORE_FILE_PATH          7
#define IS_LUMA_BANDWIDTH_FILTER    8
#define IS_BOARD_REVISION           9
#define IS_MIRROR_BITMAP_UPDOWN    10
#define IS_BUS_OVR_CNT             11
#define IS_STEAL_ERROR_CNT         12
#define IS_LOW_COLOR_REMOVAL       13

// ------------------------------------------
// rop effect constants
// ------------------------------------------
#define IS_SET_ROP_MIRROR_UPDOWN         8
#define IS_SET_ROP_MIRROR_UPDOWN_ODD    16
#define IS_SET_ROP_MIRROR_UPDOWN_EVEN   32
#define IS_GET_ROP_EFFECT               0x8000

// ------------------------------------------
// board type defines
// ------------------------------------------
#define IS_BOARD_TYPE_FALCON            1
#define IS_BOARD_TYPE_EAGLE             2
#define IS_BOARD_TYPE_FALCON2           3
#define IS_BOARD_TYPE_FALCON_PLUS       7
#define IS_BOARD_TYPE_FALCON_QUATTRO    9
#define IS_BOARD_TYPE_FALCON_DUO       10
#define IS_BOARD_TYPE_EAGLE_QUATTRO    11
#define IS_BOARD_TYPE_EAGLE_DUO        12

// decimation modes
#define IS_DECIMATION_OFF                 0
#define IS_DECIMATION_CONSECUTIVE         1
#define IS_DECIMATION_DISTRIBUTED         2
#define IS_GET_DECIMATION_MODE       0x8000
#define IS_GET_DECIMATION_NUMBER     0x8001

// ------------------------------------------
// readable operation system defines
// ------------------------------------------
#define IS_OS_WIN95    1      // VER_PLATFORM_WIN32_WINDOWS
#define IS_OS_WINNT40  2      // VER_PLATFORM_WIN32_NT
#define IS_OS_WIN98    3
#define IS_OS_WIN2000  4
#define IS_OS_WINXP    5

// ------------------------------------------
// sequence flags
// ------------------------------------------
#define IS_LOCK_LAST_BUFFER         0x8002

// ------------------------------------------
// info struct
// ------------------------------------------
#define FALCINFO   BOARDINFO
#define PFALCINFO  PBOARDINFO

typedef struct
{
  char          SerNo[12];    // e.g. "12345-1234"  (11 char)
  char          ID[20];       // e.g. "IDS GmbH"
  char          Version[10];  // e.g. "V1.00"  (9 char)
  char          Date[12];     // e.g "11.11.1999" (11 char)
  unsigned char Select;       // 0 (contains board select number for multi board support)
  unsigned char Type;         // 1 (contains board type)
  char          Reserved[8];  // (7 char)
} BOARDINFO, *PBOARDINFO;

// ------------------------------------------
// EEPROM defines
// ------------------------------------------
#define IS_EEPROM_MIN_USER_ADDRESS     0
#define IS_EEPROM_MAX_USER_ADDRESS    63
#define IS_EEPROM_MAX_USER_SPACE      64


// ------------------------------------------
// typedefs
// ------------------------------------------

typedef HANDLE HIDS;
typedef HANDLE HFALC;
typedef int    INT;



#if defined (_MSC_VER) || defined (__BORLANDC__)
  #if defined (_PURE_C) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSEXP     extern  __declspec(dllimport) INT __cdecl
    #define IDSEXPUL   extern  __declspec(dllimport) ULONG __cdecl
  #elif defined (__STDC__) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSEXP   extern  __declspec(dllimport) INT __cdecl
    #define IDSEXPUL extern  __declspec(dllimport) ULONG __cdecl
  #elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)   // using the DLL, not creating one
    #define IDSEXP   extern "C" __declspec(dllimport) INT __cdecl
    #define IDSEXPUL extern "C" __declspec(dllimport) ULONG __cdecl
  #elif defined (_IDS_VBSTD) || defined (_FALC_VBSTD)     // for creating stdcall dll
    #define IDSEXP    extern __declspec(dllexport) INT __stdcall
    #define IDSEXPUL  extern __declspec(dllexport) ULONG __stdcall
  #else            // for creating cdecl dll
    #define IDSEXP    extern  __declspec(dllexport) INT __cdecl
    #define IDSEXPUL  extern  __declspec(dllexport) ULONG __cdecl
  #endif
#elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)  // using the DLL, not creating one
  #define IDSEXP    extern  __declspec(dllimport) INT __cdecl
  #define IDSEXPUL  extern  __declspec(dllimport) ULONG __cdecl
#endif


// ------------------------------------------
// exports
// ------------------------------------------

  IDSEXP   is_InitBoard              (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitBoard              (HIDS hf);
  IDSEXP   is_InitFalcon             (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitFalcon             (HIDS hf);
  IDSEXP   is_StopLiveVideo          (HIDS hf, INT Wait);
  IDSEXP   is_FreezeVideo            (HIDS hf, INT Wait);
  IDSEXP   is_CaptureVideo           (HIDS hf, INT Wait);
  IDSEXP   is_SetVideoInput          (HIDS hf, INT Source);
  IDSEXP   is_SetBrightness          (HIDS hf, INT Bright);
  IDSEXP   is_SetContrast            (HIDS hf, INT Cont);
  IDSEXP   is_SetSaturation          (HIDS hf, INT ChromU, INT ChromV);
  IDSEXP   is_SetHue                 (HIDS hf, INT Hue);
  IDSEXP   is_SetVideoMode           (HIDS hf, INT Mode);
  IDSEXP   is_SetDisplayMode         (HIDS hf, INT Mode);
  IDSEXP   is_SetAGC                 (HIDS hf, INT Mode);
  IDSEXP   is_SetGamma               (HIDS hf, INT Mode);
  IDSEXP   is_SetSyncLevel           (HIDS hf, INT Level);
  IDSEXP   is_ShowColorBars          (HIDS hf, INT Mode);
  IDSEXP   is_SetColorMode           (HIDS hf, INT Mode);
  IDSEXP   is_SetScaler              (HIDS hf, float Scalex, float Scaley);
  IDSEXP   is_GetImageMem            (HIDS hf, VOID** pMem);
  IDSEXP   is_GetImageMemPitch       (HIDS hf, INT* pPitch);
  IDSEXP   is_SetImageSize           (HIDS hf, INT x, INT y);
  IDSEXP   is_SetImagePos            (HIDS hf, INT x, INT y);
  IDSEXP   is_GetError               (HIDS hf, INT* pErr, char** ppcErr);
  IDSEXP   is_SetCaptureMode         (HIDS hf, INT Mode);
  IDSEXP   is_SetErrorReport         (HIDS hf, INT Mode);
  IDSEXP   is_SetHorFilter           (HIDS hf, INT Mode);
  IDSEXP   is_SetVertFilter          (HIDS hf, INT Mode);
  IDSEXP   is_GetBoardInfo           (HIDS hf, PBOARDINFO pInfo);
  IDSEXP   is_ReadEEPROM             (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_WriteEEPROM            (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_SaveImage              (HIDS hf, char* File);
  IDSEXP   is_LoadImage              (HIDS hf, char* File);
  IDSEXP   is_UpdateDisplay          (HIDS hf);
  IDSEXP   is_SetDisplaySize         (HIDS hf, INT x, INT y);
  IDSEXP   is_SetDisplayPos          (HIDS hf, INT x, INT y);
  IDSEXP   is_AllocImageMem          (HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid);
  IDSEXP   is_SetImageMem            (HIDS hf, char* pcMem, int id);
  IDSEXP   is_FreeImageMem           (HIDS hf, char* pcMem, int id);
  IDSEXP   is_IsVideoFinish          (HIDS hf, BOOL* pbo);
  IDSEXP   is_HasVideoStarted        (HIDS hf, BOOL* pbo);
  IDSEXP   is_EnableDDOverlay        (HIDS hf);
  IDSEXP   is_DisableDDOverlay       (HIDS hf);
  IDSEXP   is_ShowDDOverlay          (HIDS hf);
  IDSEXP   is_HideDDOverlay          (HIDS hf);
  IDSEXP   is_ScaleDDOverlay         (HIDS hf, BOOL boScale);
  IDSEXP   is_GetDC                  (HIDS hf, HDC* phDC);
  IDSEXP   is_ReleaseDC              (HIDS hf, HDC hDC);
  IDSEXP   is_SetDDUpdateTime        (HIDS hf, INT ms);
  IDSEXP   is_LockDDOverlayMem       (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDOverlayMem     (HIDS hf);
  IDSEXP   is_LockDDMem              (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDMem            (HIDS hf);
  IDSEXP   is_GetDDOvlSurface        (HIDS hf, void** ppDDSurf);
  IDSEXP   is_GetVsyncCount          (HIDS hf, long* pIntr, long* pActIntr);
  IDSEXP   is_GetCurrentField        (HIDS hf, int* pField);
  IDSEXP   is_InitEvent              (HIDS hf, HANDLE hEv, INT which);
  IDSEXP   is_ExitEvent              (HIDS hf, INT which);
  IDSEXP   is_EnableEvent            (HIDS hf, INT which);
  IDSEXP   is_DisableEvent           (HIDS hf, INT which);
  IDSEXP   is_SetVideoSize           (HIDS hf, INT xpos, INT ypos, INT xsize, INT ysize);
  IDSEXP   is_SetKeyColor            (HIDS hf, INT r, INT g, INT b);
  IDSEXP   is_SetKeyOffset           (HIDS hf, INT nOffsetX, INT nOffsetY);
  IDSEXP   is_PrepareStealVideo      (HIDS hf, int Mode, ULONG StealColorMode);
  IDSEXP   is_StealVideo             (HIDS hf, int Wait);
  IDSEXP   is_SetHwnd                (HIDS hf, HWND hwnd);
  IDSEXP   is_SetParentHwnd          (HIDS hf, HWND hwnd);
  IDSEXP   is_SetUpdateMode          (HIDS hf, INT mode);
  IDSEXP   is_GetActiveImageMem      (HIDS hf, char** ppcMem, int* pnID);
  IDSEXP   is_InquireImageMem        (HIDS hf, char* pcMem, int nID, int* pnX, int* pnY, int* pnBits, int* pnPitch);
  IDSEXP   is_OvlSurfaceOffWhileMove (HIDS hf, BOOL boMode);
  IDSEXP   is_AddToSequence          (HIDS hf, char* pcMem, INT nID);
  IDSEXP   is_ClearSequence          (HIDS hf);
  IDSEXP   is_GetActSeqBuf           (HIDS hf, INT* pnNum, char** ppcMem, char** ppcMemLast);
  IDSEXP   is_LockSeqBuf             (HIDS hf, INT nNum, char* pcMem);
  IDSEXP   is_UnlockSeqBuf           (HIDS hf, INT nNum, char* pcMem);
  IDSEXP   is_GetColorDepth          (HIDS hf, INT* pnCol, INT* pnColMode);
  IDSEXP   is_GetNumberOfBoards      (INT* pnNumBoards);
  IDSEXP   is_GetPciSlot             (HIDS hf, INT* pnSlot);
  IDSEXP   is_GetIRQ                 (HIDS hf, INT* pnIRQ);
  IDSEXP   is_SaveImageMem           (HIDS hf, char* File, char* pcMem, int nID);
  IDSEXP   is_GetBoardType           (HIDS hf);
  IDSEXPUL is_BoardStatus            (HIDS hf, INT nInfo, ULONG ulValue);
  IDSEXP   is_CopyImageMem           (HIDS hf, char* pcSource, int nID, char* pcDest);
  IDSEXP   is_CopyImageMemLines      (HIDS hf, char* pcSource, int nID, int nLines, char* pcDest);
  IDSEXP   is_GetNumberOfDevices     ();
  IDSEXP   is_GetOsVersion           ();
  IDSEXP   is_SetAllocatedImageMem   (HIDS hf, INT width, INT height, INT bitspixel, char* pcImgMem, int* pid);
  IDSEXP   is_SetToggleMode          (HIDS hf, int nInput1, int nInput2, int nInput3, int nInput4);
  IDSEXP   is_SetRopEffect           (HIDS hf, INT effect, INT param, INT reserved);
  IDSEXP   is_SetDecimationMode      (HIDS hf, INT nMode, INT nDecimate);

  // only EAGLE:
  IDSEXP   is_SetSync                (HIDS hf, INT nSync);
  IDSEXP   is_SetIO                  (HIDS hf, INT nIO);
  IDSEXP   is_SetFlashStrobe         (HIDS hf, INT nField, INT nLine);
  IDSEXP   is_SetExternalTrigger     (HIDS hf, INT nTriggerMode);

  // only FALCON duo/quattro
  IDSEXP   is_SetVideoCrossbar       (HIDS hf, INT In, INT Out);

  // bitmap display function
  IDSEXP   is_RenderBitmap           (HIDS hf, INT nMemID, HWND hwnd, INT nMode);

  // version information
  IDSEXP   is_GetDLLVersion          ();


#ifdef __cplusplus
};
#endif  /* __cplusplus */

#endif



