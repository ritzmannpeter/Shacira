/*
###############################################################################
#                                                                             #
# File:    uEye.h                                                             #
# Project: Library interface for IDS uEye - Camera family                     #
#             exported API functions                                          #
#                                                                             #
###############################################################################
*/

#ifndef __IDS_HEADER__
#define __IDS_HEADER__

#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// ----------------------------------------Driver name----------------------------------------------
//
#ifndef __LINUX__
  #define DRIVER_DLL_NAME   "ueye_api.dll"
#else
  #define DRIVER_DLL_NAME   "libueye_api.so"
#endif


// ----------------------------------------Color modes----------------------------------------------
//
#define IS_COLORMODE_INVALID        0
#define IS_COLORMODE_MONOCHROME     1
#define IS_COLORMODE_BAYER          2
//
// -------------------------------------------------------------------------------------------------


// ----------------------------------------Sensor Types---------------------------------------------
//
#define IS_SENSOR_INVALID           0x0000

// CMOS Sensors
#define IS_SENSOR_UI141X_M          0x0001      // VGA rolling shutter - VGA monochrome
#define IS_SENSOR_UI141X_C          0x0002      // VGA rolling shutter - VGA color
#define IS_SENSOR_UI144X_M          0x0003      // SXGA rolling shutter - SXGA monochrome
#define IS_SENSOR_UI144X_C          0x0004      // SXGA rolling shutter - SXGA color

#define IS_SENSOR_UI145X_C          0x0008      // UXGA rolling shutter - UXGA color
#define IS_SENSOR_UI146X_C          0x000a      // QXGA rolling shutter - QXGA color
#define IS_SENSOR_UI148X_C          0x000c      //

#define IS_SENSOR_UI121X_M          0x0010      // VGA global shutter - VGA monochrome
#define IS_SENSOR_UI121X_C          0x0011      // VGA global shutter - VGA color
#define IS_SENSOR_UI122X_M          0x0012      // WVGA global shutter - WVGA monochrome
#define IS_SENSOR_UI122X_C          0x0013      // WVGA global shutter - WVGA color
#define IS_SENSOR_UI1223_M          0x0018      // WVGA global shutter - WVGA monochrome
#define IS_SENSOR_UI1223_C          0x0019      // WVGA global shutter - WVGA color
#define IS_SENSOR_UI1225_M          0x0022      // WVGA global shutter - WVGA monochrome
#define IS_SENSOR_UI1225_C          0x0023      // WVGA global shutter - WVGA color

#define IS_SENSOR_UI164X_C          0x0020      // SXGA rolling shutter - SXGA color

#define IS_SENSOR_UI154X_M          0x0030      // SXGA rolling shutter - SXGA monochrome
#define IS_SENSOR_UI154X_C          0x0031      // SXGA rolling shutter - SXGA color
#define IS_SENSOR_UI1543_M          0x0032      // SXGA rolling shutter - SXGA monochrome
#define IS_SENSOR_UI1543_C          0x0033      // SXGA rolling shutter - SXGA color

#define IS_SENSOR_UI1453_C          0x0035      // UXGA rolling shutter - UXGA color
#define IS_SENSOR_UI1463_C          0x0037      // QXGA rolling shutter - QXGA color
#define IS_SENSOR_UI1483_C          0x0039      //


// CCD Sensors
#define IS_SENSOR_UI223X_M          0x0080      // Sony CCD sensor - XGA monochrome
#define IS_SENSOR_UI223X_C          0x0081      // Sony CCD sensor - XGA color

#define IS_SENSOR_UI241X_M          0x0082      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI241X_C          0x0083      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI234X_M          0x0084      // Sony CCD sensor - SXGA monochrome
#define IS_SENSOR_UI234X_C          0x0085      // Sony CCD sensor - SXGA color

#define IS_SENSOR_UI233X_M          0x0086      //
#define IS_SENSOR_UI233X_C          0x0087      //

#define IS_SENSOR_UI221X_M          0x0088      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI221X_C          0x0089      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI231X_M          0x0090      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI231X_C          0x0091      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI222X_M          0x0092      // Sony CCD sensor - CCIR / PAL monochrome
#define IS_SENSOR_UI222X_C          0x0093      // Sony CCD sensor - CCIR / PAL color

#define IS_SENSOR_UI224X_M          0x0096      // Sony CCD sensor - SXGA monochrome
#define IS_SENSOR_UI224X_C          0x0097      // Sony CCD sensor - SXGA color

#define IS_SENSOR_UI225X_M          0x0098      // Sony CCD sensor - UXGA monochrome
#define IS_SENSOR_UI225X_C          0x0099      // Sony CCD sensor - UXGA color
//
// -------------------------------------------------------------------------------------------------


// ----------------------------------------------
// error codes
// ----------------------------------------------
#define IS_NO_SUCCESS                      -1   // function call failed
#define IS_SUCCESS                          0   // function call succeeded
#define IS_INVALID_CAMERA_HANDLE            1   // camera handle is not valid or zero
#define IS_INVALID_HANDLE                   1   // a handle other than the camera handle is invalid

#define IS_IO_REQUEST_FAILED                2   // an io request to the driver failed
#define IS_CANT_OPEN_DEVICE                 3   // returned by is_InitCamera
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

// DirectDraw Mode errors
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
#define IS_INVALID_PARAMETER              125   // a parameter specified was invalid
#define IS_NOT_ALLOWED                    126
#define IS_OUT_OF_MEMORY                  127
#define IS_INVALID_WHILE_LIVE             128
#define IS_ACCESS_VIOLATION               129   // an internal exception occured
#define IS_UNKNOWN_ROP_EFFECT             130
#define IS_INVALID_RENDER_MODE            131
#define IS_INVALID_THREAD_CONTEXT         132
#define IS_NO_HARDWARE_INSTALLED          133
#define IS_INVALID_WATCHDOG_TIME          134
#define IS_INVALID_WATCHDOG_MODE          135
#define IS_INVALID_PASSTHROUGH_IN         136
#define IS_ERROR_SETTING_PASSTHROUGH_IN   137
#define IS_FAILURE_ON_SETTING_WATCHDOG    138
#define IS_NO_USB20                       139   // the usb port doesnt support usb 2.0
#define IS_CAPTURE_RUNNING                140   // there is already a capture running

#define IS_MEMORY_BOARD_ACTIVATED         141   // operation could not execute while mboard is enabled
#define IS_MEMORY_BOARD_DEACTIVATED       142   // operation could not execute while mboard is disabled
#define IS_NO_MEMORY_BOARD_CONNECTED      143   // no memory board connected
#define IS_TOO_LESS_MEMORY                144   // image size is above memory capacity
#define IS_IMAGE_NOT_PRESENT              145   // requested image is no longer present in the camera
#define IS_MEMORY_MODE_RUNNING            146
#define IS_MEMORYBOARD_DISABLED           147

#define IS_TRIGGER_ACTIVATED              148   // operation could not execute while trigger is enabled
#define IS_WRONG_KEY                      150
#define IS_CRC_ERROR                      151
#define IS_NOT_YET_RELEASED               152   // this feature is not available yet
#define IS_NOT_CALIBRATED                 153   // the camera is not calibrated
#define IS_WAITING_FOR_KERNEL             154   // a request to the kernel exceeded
#define IS_NOT_SUPPORTED                  155   // operation mode is not supported
#define IS_TRIGGER_NOT_ACTIVATED          156   // operation could not execute while trigger is disabled
#define IS_OPERATION_ABORTED              157
#define IS_BAD_STRUCTURE_SIZE             158
#define IS_INVALID_BUFFER_SIZE            159
#define IS_INVALID_PIXEL_CLOCK            160
#define IS_INVALID_EXPOSURE_TIME          161
#define IS_AUTO_EXPOSURE_RUNNING          162
#define IS_CANNOT_CREATE_BB_SURF          163   // error creating backbuffer surface  
#define IS_CANNOT_CREATE_BB_MIX           164   // backbuffer mixer surfaces can not be created
#define IS_BB_OVLMEM_NULL                 165   // backbuffer overlay mem could not be locked  
#define IS_CANNOT_CREATE_BB_OVL           166   // backbuffer overlay mem could not be created  
#define IS_NOT_SUPP_IN_OVL_SURF_MODE      167   // function not supported in overlay surface mode  
#define IS_INVALID_SURFACE                168   // surface invalid
#define IS_SURFACE_LOST                   169   // surface hase been lost  
#define IS_RELEASE_BB_OVL_DC              170   // error releasing backbuffer overlay DC  
#define IS_BB_TIMER_NOT_CREATED           171   // backbuffer timer could not be created  
#define IS_BB_OVL_NOT_EN                  172   // backbuffer overlay has not been enabled  
#define IS_ONLY_IN_BB_MODE                173   // only possible in backbuffer mode 
#define IS_INVALID_COLOR_FORMAT			  174   // invalid color format


// ----------------------------------------------
// common definitions
// ----------------------------------------------
#define IS_OFF                      0
#define IS_ON                       1
#define IS_IGNORE_PARAMETER         -1


// ----------------------------------------------
//  device enumeration
// ----------------------------------------------
#define IS_USE_DEVICE_ID            0x8000L


// ----------------------------------------------
// AutoExit enable/disable
// ----------------------------------------------
#define IS_GET_AUTO_EXIT_ENABLED    0x8000
#define IS_DISABLE_AUTO_EXIT        0
#define IS_ENABLE_AUTO_EXIT         1


// ----------------------------------------------
// live/freeze parameters
// ----------------------------------------------
#define IS_GET_LIVE                 0x8000

#define IS_WAIT                     0x0001
#define IS_DONT_WAIT                0x0000
#define IS_FORCE_VIDEO_STOP         0x4000
#define IS_FORCE_VIDEO_START        0x4000
#define IS_USE_NEXT_MEM             0x8000


// ----------------------------------------------
// video finish constants
// ----------------------------------------------
#define IS_VIDEO_NOT_FINISH         0
#define IS_VIDEO_FINISH             1


// ----------------------------------------------
// bitmap render modes
// ----------------------------------------------
#define IS_GET_RENDER_MODE          0x8000

#define IS_RENDER_DISABLED          0
#define IS_RENDER_NORMAL            1
#define IS_RENDER_FIT_TO_WINDOW     2
#define IS_RENDER_DOWNSCALE_1_2     4
#define IS_RENDER_MIRROR_UPDOWN     16
#define IS_RENDER_DOUBLE_HEIGHT     32
#define IS_RENDER_HALF_HEIGHT       64


// ----------------------------------------------
// external trigger modes
// ----------------------------------------------
#define IS_GET_EXTERNALTRIGGER      0x8000
#define IS_GET_TRIGGER_STATUS       0x8001
#define IS_GET_TRIGGER_MASK         0x8002
#define IS_GET_TRIGGER_INPUTS       0x8003
#define IS_GET_TRIGGER_COUNTER      0x8000

#define IS_SET_TRIG_OFF             0x000
#define IS_SET_TRIG_HI_LO           0x001
#define IS_SET_TRIG_LO_HI           0x002
#define IS_SET_TRIG_SOFTWARE        0x008
#define IS_SET_TRIG_MASK            0x100

#define IS_GET_TRIGGER_DELAY                0x8000
#define IS_GET_MIN_TRIGGER_DELAY            0x8001
#define IS_GET_MAX_TRIGGER_DELAY            0x8002
#define IS_GET_TRIGGER_DELAY_GRANULARITY    0x8003


// ----------------------------------------------
// Timing
// ----------------------------------------------
// pixelclock
#define IS_GET_PIXEL_CLOCK          0x8000
#define IS_GET_DEFAULT_PIXEL_CLK    0x8001
// framerate
#define IS_GET_FRAMERATE            0x8000
#define IS_GET_DEFAULT_FRAMERATE    0x8001
// exposure
#define IS_GET_EXPOSURE_TIME        0x8000
#define IS_GET_DEFAULT_EXPOSURE     0x8001


// ----------------------------------------------
// Gain definitions
// ----------------------------------------------
#define IS_GET_MASTER_GAIN          0x8000
#define IS_GET_RED_GAIN             0x8001
#define IS_GET_GREEN_GAIN           0x8002
#define IS_GET_BLUE_GAIN            0x8003
#define IS_GET_DEFAULT_MASTER       0x8004
#define IS_GET_DEFAULT_RED          0x8005
#define IS_GET_DEFAULT_GREEN        0x8006
#define IS_GET_DEFAULT_BLUE         0x8007
#define IS_GET_GAINBOOST            0x8008
#define IS_SET_GAINBOOST_ON         0x0001
#define IS_SET_GAINBOOST_OFF        0x0000
#define IS_GET_SUPPORTED_GAINBOOST  0x0002


// ----------------------------------------------
// Gain factor definitions
// ----------------------------------------------
#define IS_GET_MASTER_GAIN_FACTOR          0x8000
#define IS_GET_RED_GAIN_FACTOR             0x8001
#define IS_GET_GREEN_GAIN_FACTOR           0x8002
#define IS_GET_BLUE_GAIN_FACTOR            0x8003
#define IS_SET_MASTER_GAIN_FACTOR          0x8004
#define IS_SET_RED_GAIN_FACTOR             0x8005
#define IS_SET_GREEN_GAIN_FACTOR           0x8006
#define IS_SET_BLUE_GAIN_FACTOR            0x8007
#define IS_GET_DEFAULT_MASTER_GAIN_FACTOR  0x8008
#define IS_GET_DEFAULT_RED_GAIN_FACTOR     0x8009
#define IS_GET_DEFAULT_GREEN_GAIN_FACTOR   0x800a
#define IS_GET_DEFAULT_BLUE_GAIN_FACTOR    0x800b
#define IS_INQUIRE_MASTER_GAIN_FACTOR      0x800c
#define IS_INQUIRE_RED_GAIN_FACTOR         0x800d
#define IS_INQUIRE_GREEN_GAIN_FACTOR       0x800e
#define IS_INQUIRE_BLUE_GAIN_FACTOR        0x800f


// ----------------------------------------------
// Global Shutter definitions
// ----------------------------------------------
#define IS_SET_GLOBAL_SHUTTER_ON            0x0001
#define IS_SET_GLOBAL_SHUTTER_OFF           0x0000
#define IS_GET_GLOBAL_SHUTTER               0x0010
#define IS_GET_SUPPORTED_GLOBAL_SHUTTER     0x0020


// ----------------------------------------------
// Blacklevel definitions
// ----------------------------------------------
#define IS_GET_BL_COMPENSATION      0x8000
#define IS_GET_BL_OFFSET            0x8001
#define IS_GET_BL_DEFAULT_MODE      0x8002
#define IS_GET_BL_DEFAULT_OFFSET    0x8003
#define IS_GET_BL_SUPPORTED_MODE    0x8004

#define IS_BL_COMPENSATION_DISABLE  0
#define IS_BL_COMPENSATION_ENABLE   1
#define IS_BL_COMPENSATION_OFFSET   32


// ----------------------------------------------
// hardware gamma definitions
// ----------------------------------------------
#define IS_GET_HW_GAMMA             0x8000
#define IS_GET_HW_SUPPORTED_GAMMA   0x8001

#define IS_SET_HW_GAMMA_OFF         0x0000
#define IS_SET_HW_GAMMA_ON          0x0001


// ----------------------------------------------
// image parameters
// ----------------------------------------------
// brightness
#define IS_GET_BRIGHTNESS           0x8000
#define IS_MIN_BRIGHTNESS           0
#define IS_MAX_BRIGHTNESS           255
#define IS_DEFAULT_BRIGHTNESS       -1
// contrast
#define IS_GET_CONTRAST             0x8000
#define IS_MIN_CONTRAST             0
#define IS_MAX_CONTRAST             511
#define IS_DEFAULT_CONTRAST         -1
// gamma
#define IS_GET_GAMMA                0x8000
#define IS_MIN_GAMMA                1
#define IS_MAX_GAMMA                1000
#define IS_DEFAULT_GAMMA            -1
// saturation   (Falcon)
#define IS_GET_SATURATION_U         0x8000
#define IS_MIN_SATURATION_U         0
#define IS_MAX_SATURATION_U         200
#define IS_DEFAULT_SATURATION_U     100
#define IS_GET_SATURATION_V         0x8001
#define IS_MIN_SATURATION_V         0
#define IS_MAX_SATURATION_V         200
#define IS_DEFAULT_SATURATION_V     100
// hue  (Falcon)
#define IS_GET_HUE                  0x8000
#define IS_MIN_HUE                  0
#define IS_MAX_HUE                  255
#define IS_DEFAULT_HUE              128


// ----------------------------------------------
// Image pos and size
// ----------------------------------------------
#define IS_GET_IMAGE_SIZE_X         0x8000
#define IS_GET_IMAGE_SIZE_Y         0x8001
#define IS_GET_IMAGE_SIZE_X_INC     0x8002
#define IS_GET_IMAGE_SIZE_Y_INC     0x8003
#define IS_GET_IMAGE_SIZE_X_MIN     0x8004
#define IS_GET_IMAGE_SIZE_Y_MIN     0x8005
#define IS_GET_IMAGE_SIZE_X_MAX     0x8006
#define IS_GET_IMAGE_SIZE_Y_MAX     0x8007

#define IS_GET_IMAGE_POS_X          0x8001
#define IS_GET_IMAGE_POS_Y          0x8002
#define IS_GET_IMAGE_POS_X_ABS      0xC001
#define IS_GET_IMAGE_POS_Y_ABS      0xC002
#define IS_GET_IMAGE_POS_X_INC      0xC003
#define IS_GET_IMAGE_POS_Y_INC      0xC004
#define IS_GET_IMAGE_POS_X_MIN      0xC005
#define IS_GET_IMAGE_POS_Y_MIN      0xC006
#define IS_GET_IMAGE_POS_X_MAX      0xC007
#define IS_GET_IMAGE_POS_Y_MAX      0xC008

#define IS_SET_IMAGE_POS_X_ABS      0x00010000
#define IS_SET_IMAGE_POS_Y_ABS      0x00010000

// Compatibility
#define IS_SET_IMAGEPOS_X_ABS       0x8000
#define IS_SET_IMAGEPOS_Y_ABS       0x8000


// ----------------------------------------------
// ROP effect constants
// ----------------------------------------------
#define IS_GET_ROP_EFFECT               0x8000

#define IS_SET_ROP_NONE                 0
#define IS_SET_ROP_MIRROR_UPDOWN        8
#define IS_SET_ROP_MIRROR_UPDOWN_ODD    16
#define IS_SET_ROP_MIRROR_UPDOWN_EVEN   32
#define IS_SET_ROP_MIRROR_LEFTRIGHT     64


// ----------------------------------------------
// Subsampling
// ----------------------------------------------
#define IS_GET_SUBSAMPLING              0x8000
#define IS_GET_SUPPORTED_SUBSAMPLING    0x8001
#define IS_GET_SUBSAMPLING_TYPE         0x8002

#define IS_SUBSAMPLING_DISABLE          0x00

#define IS_SUBSAMPLING_2X_VERTICAL      0x01
#define IS_SUBSAMPLING_2X_HORIZONTAL    0x02
#define IS_SUBSAMPLING_4X_VERTICAL      0x04
#define IS_SUBSAMPLING_4X_HORIZONTAL    0x08

#define IS_SUBSAMPLING_COLOR            0x01
#define IS_SUBSAMPLING_MONO             0x02

#define IS_SUBSAMPLING_MASK_VERTICAL    (IS_SUBSAMPLING_2X_VERTICAL | IS_SUBSAMPLING_4X_VERTICAL)
#define IS_SUBSAMPLING_MASK_HORIZONTAL  (IS_SUBSAMPLING_2X_HORIZONTAL | IS_SUBSAMPLING_4X_HORIZONTAL)

// Compatibility
#define IS_SUBSAMPLING_VERT             IS_SUBSAMPLING_2X_VERTICAL
#define IS_SUBSAMPLING_HOR              IS_SUBSAMPLING_2X_HORIZONTAL


// ----------------------------------------------
// Binning
// ----------------------------------------------
#define IS_GET_BINNING                  0x8000
#define IS_GET_SUPPORTED_BINNING        0x8001
#define IS_GET_BINNING_TYPE             0x8002

#define IS_BINNING_DISABLE              0x00

#define IS_BINNING_2X_VERTICAL          0x01
#define IS_BINNING_2X_HORIZONTAL        0x02
#define IS_BINNING_4X_VERTICAL          0x04
#define IS_BINNING_4X_HORIZONTAL        0x08

#define IS_BINNING_COLOR                0x01
#define IS_BINNING_MONO                 0x02

#define IS_BINNING_MASK_VERTICAL        (IS_BINNING_2X_VERTICAL | IS_BINNING_4X_VERTICAL)
#define IS_BINNING_MASK_HORIZONTAL      (IS_BINNING_2X_HORIZONTAL | IS_BINNING_4X_HORIZONTAL)

// Compatibility
#define IS_BINNING_VERT                 IS_BINNING_2X_VERTICAL
#define IS_BINNING_HOR                  IS_BINNING_2X_HORIZONTAL

// ----------------------------------------------
// Auto Control Parameter
// ----------------------------------------------
#define IS_SET_ENABLE_AUTO_GAIN         0x8800
#define IS_GET_ENABLE_AUTO_GAIN         0x8801
#define IS_SET_ENABLE_AUTO_SHUTTER      0x8802
#define IS_GET_ENABLE_AUTO_SHUTTER      0x8803
#define IS_SET_ENABLE_AUTO_WHITEBALANCE 0x8804
#define IS_GET_ENABLE_AUTO_WHITEBALANCE 0x8805
#define IS_SET_ENABLE_AUTO_FRAMERATE    0x8806
#define IS_GET_ENABLE_AUTO_FRAMERATE    0x8807

#define IS_SET_AUTO_REFERENCE           0x8000
#define IS_GET_AUTO_REFERENCE           0x8001
#define IS_SET_AUTO_GAIN_MAX            0x8002
#define IS_GET_AUTO_GAIN_MAX            0x8003
#define IS_SET_AUTO_SHUTTER_MAX         0x8004
#define IS_GET_AUTO_SHUTTER_MAX         0x8005
#define IS_SET_AUTO_SPEED               0x8006
#define IS_GET_AUTO_SPEED               0x8007
#define IS_SET_AUTO_WB_OFFSET           0x8008
#define IS_GET_AUTO_WB_OFFSET           0x8009
#define IS_SET_AUTO_WB_GAIN_RANGE       0x800A
#define IS_GET_AUTO_WB_GAIN_RANGE       0x800B
#define IS_SET_AUTO_WB_SPEED            0x800C
#define IS_GET_AUTO_WB_SPEED            0x800D
#define IS_SET_AUTO_WB_ONCE             0x800E
#define IS_GET_AUTO_WB_ONCE             0x800F
#define IS_SET_AUTO_BRIGHTNESS_ONCE     0x8010
#define IS_GET_AUTO_BRIGHTNESS_ONCE     0x8011

// ----------------------------------------------
// Auto Control definitions
// ----------------------------------------------
#define IS_MIN_AUTO_BRIGHT_REFERENCE          0
#define IS_MAX_AUTO_BRIGHT_REFERENCE        255
#define IS_DEFAULT_AUTO_BRIGHT_REFERENCE    128
#define IS_MIN_AUTO_SPEED                     0
#define IS_MAX_AUTO_SPEED                   100
#define IS_DEFAULT_AUTO_SPEED                50

#define IS_DEFAULT_AUTO_WB_OFFSET             0
#define IS_MIN_AUTO_WB_OFFSET               -50
#define IS_MAX_AUTO_WB_OFFSET                50
#define IS_DEFAULT_AUTO_WB_SPEED             50
#define IS_MIN_AUTO_WB_SPEED                  0
#define IS_MAX_AUTO_WB_SPEED                100
#define IS_MIN_AUTO_WB_REFERENCE              0
#define IS_MAX_AUTO_WB_REFERENCE            255


// ----------------------------------------------
// AOI types to set/get
// ----------------------------------------------
#define IS_SET_AUTO_BRIGHT_AOI      0x8000
#define IS_GET_AUTO_BRIGHT_AOI      0x8001
#define IS_SET_IMAGE_AOI            0x8002
#define IS_GET_IMAGE_AOI            0x8003
#define IS_SET_AUTO_WB_AOI          0x8004
#define IS_GET_AUTO_WB_AOI          0x8005


// ----------------------------------------------
// color modes
// ----------------------------------------------
#define IS_GET_COLOR_MODE           0x8000

#define IS_SET_CM_RGB32             0
#define IS_SET_CM_RGB24             1
#define IS_SET_CM_RGB16             2
#define IS_SET_CM_RGB15             3
#define IS_SET_CM_Y8                6
#define IS_SET_CM_RGB8              7
#define IS_SET_CM_BAYER             11
#define IS_SET_CM_UYVY              12
#define IS_SET_CM_UYVY_MONO         13
#define IS_SET_CM_UYVY_BAYER        14


// ----------------------------------------------
// Hotpixel correction
// ----------------------------------------------
#define IS_GET_BPC_MODE             0x8000
#define IS_GET_BPC_THRESHOLD        0x8001
#define IS_GET_BPC_SUPPORTED_MODE   0x8002

#define IS_BPC_DISABLE              0
#define IS_BPC_ENABLE_LEVEL_1       1
#define IS_BPC_ENABLE_LEVEL_2       2
#define IS_BPC_ENABLE_USER          4
#define IS_BPC_ENABLE_SOFTWARE      IS_BPC_ENABLE_LEVEL_2
#define IS_BPC_ENABLE_HARDWARE      IS_BPC_ENABLE_LEVEL_1

#define IS_SET_BADPIXEL_LIST        0x01
#define IS_GET_BADPIXEL_LIST        0x02
#define IS_GET_LIST_SIZE            0x03


// ----------------------------------------------
// color correction definitions
// ----------------------------------------------
#define IS_GET_CCOR_MODE            0x8000
#define IS_CCOR_DISABLE             0x0000
#define IS_CCOR_ENABLE              0x0001


// ----------------------------------------------
// bayer algorithm modes
// ----------------------------------------------
#define IS_GET_BAYER_CV_MODE        0x8000

#define IS_SET_BAYER_CV_NORMAL      0x0000
#define IS_SET_BAYER_CV_BETTER      0x0001
#define IS_SET_BAYER_CV_BEST        0x0002


// ----------------------------------------------
// Edge enhancement
// ----------------------------------------------
#define IS_GET_EDGE_ENHANCEMENT     0x8000

#define IS_EDGE_EN_DISABLE          0
#define IS_EDGE_EN_STRONG           1
#define IS_EDGE_EN_WEAK             2


// ----------------------------------------------
// white balance modes
// ----------------------------------------------
#define IS_GET_WB_MODE              0x8000

#define IS_SET_WB_DISABLE           0x0000
#define IS_SET_WB_USER              0x0001
#define IS_SET_WB_AUTO_ENABLE       0x0002
#define IS_SET_WB_AUTO_ENABLE_ONCE  0x0004

#define IS_SET_WB_DAYLIGHT_65       0x0101
#define IS_SET_WB_COOL_WHITE        0x0102
#define IS_SET_WB_U30               0x0103
#define IS_SET_WB_ILLUMINANT_A      0x0104
#define IS_SET_WB_HORIZON           0x0105


// ----------------------------------------------
// flash strobe constants
// ----------------------------------------------
#define IS_GET_FLASHSTROBE_MODE     0x8000
#define IS_GET_FLASHSTROBE_LINE     0x8001

#define IS_SET_FLASH_OFF            0
#define IS_SET_FLASH_ON             1
#define IS_SET_FLASH_LO_ACTIVE      IS_SET_FLASH_ON
#define IS_SET_FLASH_HI_ACTIVE      2
#define IS_SET_FLASH_HIGH           3
#define IS_SET_FLASH_LOW            4

#define IS_GET_FLASH_DELAY                  -1
#define IS_GET_FLASH_DURATION               -2
#define IS_GET_MAX_FLASH_DELAY              -3
#define IS_GET_MAX_FLASH_DURATION           -4
#define IS_GET_MIN_FLASH_DELAY              -5
#define IS_GET_MIN_FLASH_DURATION           -6
#define IS_GET_FLASH_DELAY_GRANULARITY      -7
#define IS_GET_FLASH_DURATION_GRANULARITY   -8

// ----------------------------------------------
// Digital IO constants
// ----------------------------------------------
#define IS_GET_IO                   0x8000
#define IS_GET_IO_MASK              0x8000


// ----------------------------------------------
// EEPROM defines
// ----------------------------------------------
#define IS_EEPROM_MIN_USER_ADDRESS      0
#define IS_EEPROM_MAX_USER_ADDRESS      63
#define IS_EEPROM_MAX_USER_SPACE        64


// ----------------------------------------------
// error report modes
// ----------------------------------------------
#define IS_GET_ERR_REP_MODE         0x8000
#define IS_ENABLE_ERR_REP           1
#define IS_DISABLE_ERR_REP          0


// ----------------------------------------------
// display mode selectors
// ----------------------------------------------
#define IS_GET_DISPLAY_MODE         0x8000
#define IS_GET_DISPLAY_SIZE_X       0x8000
#define IS_GET_DISPLAY_SIZE_Y       0x8001
#define IS_GET_DISPLAY_POS_X        0x8000
#define IS_GET_DISPLAY_POS_Y        0x8001

#define IS_SET_DM_DIB               1
#define IS_SET_DM_DIRECTDRAW        2
#define IS_SET_DM_ALLOW_SYSMEM      0x40
#define IS_SET_DM_ALLOW_PRIMARY     0x80



// -- overlay display mode ---
#define IS_GET_DD_OVERLAY_SCALE     0x8000

#define IS_SET_DM_ALLOW_OVERLAY     0x100
#define IS_SET_DM_ALLOW_SCALING     0x200
#define IS_SET_DM_ALLOW_FIELDSKIP   0x400
#define IS_SET_DM_MONO              0x800
#define IS_SET_DM_BAYER             0x1000
// -- backbuffer display mode ---
#define IS_SET_DM_BACKBUFFER        0x2000

// ----------------------------------------------
// DirectDraw keying color constants
// ----------------------------------------------
#define IS_GET_KC_RED               0x8000
#define IS_GET_KC_GREEN             0x8001
#define IS_GET_KC_BLUE              0x8002
#define IS_GET_KC_RGB               0x8003
#define IS_GET_KC_INDEX             0x8004
#define IS_GET_KEYOFFSET_X          0x8000
#define IS_GET_KEYOFFSET_Y          0x8001

// RGB-triple for default key-color in 15,16,24,32 bit mode
#define IS_SET_KC_DEFAULT           0xFF00FF   // 0xbbggrr
// colorindex for default key-color in 8bit palette mode
#define IS_SET_KC_DEFAULT_8         253


// ----------------------------------------------
// Memoryboard
// ----------------------------------------------
#define IS_MEMORY_GET_COUNT         0x8000
#define IS_MEMORY_GET_DELAY         0x8001
#define IS_MEMORY_MODE_DISABLE      0x0000
#define IS_MEMORY_USE_TRIGGER       0xFFFF


// ----------------------------------------------
// Testimage modes
// ----------------------------------------------
#define IS_GET_TEST_IMAGE           0x8000

#define IS_SET_TEST_IMAGE_DISABLED  0x0000
#define IS_SET_TEST_IMAGE_MEMORY_1  0x0001
#define IS_SET_TEST_IMAGE_MEMORY_2  0x0002
#define IS_SET_TEST_IMAGE_MEMORY_3  0x0003


// ------------------------------------------
// Led settings
// ------------------------------------------
#define IS_SET_LED_OFF              0
#define IS_SET_LED_ON               1
#define IS_SET_LED_TOGGLE           2
#define IS_GET_LED                  0x8000


// ----------------------------------------------
// save options
// ----------------------------------------------
#define IS_SAVE_USE_ACTUAL_IMAGE_SIZE    0x00010000


// ----------------------------------------------
// event constants
// ----------------------------------------------
#define IS_SET_EVENT_ODD                    0
#define IS_SET_EVENT_EVEN                   1
#define IS_SET_EVENT_FRAME                  2
#define IS_SET_EVENT_EXTTRIG                3
#define IS_SET_EVENT_VSYNC                  4
#define IS_SET_EVENT_SEQ                    5
#define IS_SET_EVENT_STEAL                  6
#define IS_SET_EVENT_VPRES                  7
#define IS_SET_EVENT_TRANSFER_FAILED        8
#define IS_SET_EVENT_DEVICE_RECONNECTED     9
#define IS_SET_EVENT_MEMORY_MODE_FINISH     10
#define IS_SET_EVENT_FRAME_RECEIVED         11
#define IS_SET_EVENT_WB_FINISHED            12
#define IS_SET_EVENT_AUTOBRIGHTNESS_FINISHED  13

#define IS_SET_EVENT_REMOVE                 128
#define IS_SET_EVENT_REMOVAL                129
#define IS_SET_EVENT_NEW_DEVICE             130


// ----------------------------------------------
// Window message defines
// ----------------------------------------------
#define IS_UEYE_MESSAGE            WM_USER + 0x0100 // 0x7FFF + 0x0100
  #define IS_FRAME                      0x0000
  #define IS_SEQUENCE                   0x0001
  #define IS_TRIGGER                    0x0002
  #define IS_TRANSFER_FAILED            0x0003
  #define IS_DEVICE_RECONNECTED         0x0004
  #define IS_MEMORY_MODE_FINISH         0x0005
  #define IS_FRAME_RECEIVED             0x0006
  #define IS_GENERIC_ERROR              0x0007
  #define IS_STEAL_VIDEO                0x0008
  #define IS_WB_FINISHED                0x0009
  #define IS_AUTOBRIGHTNESS_FINISHED    0x000A

  #define IS_DEVICE_REMOVED             0x1000
  #define IS_DEVICE_REMOVAL             0x1001
  #define IS_NEW_DEVICE                 0x1002


// ----------------------------------------------
// camera id constants
// ----------------------------------------------
#define IS_GET_CAMERA_ID                0x8000


// ----------------------------------------------
// camera info constants
// ----------------------------------------------
#define IS_GET_STATUS                   0x8000

#define IS_EXT_TRIGGER_EVENT_CNT        0
#define IS_FIFO_OVR_CNT                 1
#define IS_SEQUENCE_CNT                 2
#define IS_LAST_FRAME_FIFO_OVR          3
#define IS_SEQUENCE_SIZE                4
#define IS_VIDEO_PRESENT                5
#define IS_STEAL_FINISHED               6
#define IS_STORE_FILE_PATH              7
#define IS_LUMA_BANDWIDTH_FILTER        8
#define IS_BOARD_REVISION               9
#define IS_MIRROR_BITMAP_UPDOWN         10
#define IS_BUS_OVR_CNT                  11
#define IS_STEAL_ERROR_CNT              12
#define IS_LOW_COLOR_REMOVAL            13
#define IS_CHROMA_COMB_FILTER           14
#define IS_CHROMA_AGC                   15
#define IS_WATCHDOG_ON_BOARD            16
#define IS_PASSTHROUGH_ON_BOARD         17
#define IS_EXTERNAL_VREF_MODE           18
#define IS_WAIT_TIMEOUT                 19
#define IS_TRIGGER_MISSED               20

// ----------------------------------------------
// board type defines
// ----------------------------------------------
#define IS_BOARD_TYPE_FALCON            1
#define IS_BOARD_TYPE_EAGLE             2
#define IS_BOARD_TYPE_FALCON2           3
#define IS_BOARD_TYPE_FALCON_PLUS       7
#define IS_BOARD_TYPE_FALCON_QUATTRO    9
#define IS_BOARD_TYPE_FALCON_DUO        10
#define IS_BOARD_TYPE_EAGLE_QUATTRO     11
#define IS_BOARD_TYPE_EAGLE_DUO         12
#define IS_BOARD_TYPE_UEYE_USB          0x40


// ----------------------------------------------
// readable operation system defines
// ----------------------------------------------
#define IS_OS_UNDETERMINED          0
#define IS_OS_WIN95                 1   // VER_PLATFORM_WIN32_WINDOWS
#define IS_OS_WINNT40               2   // VER_PLATFORM_WIN32_NT
#define IS_OS_WIN98                 3
#define IS_OS_WIN2000               4
#define IS_OS_WINXP                 5
#define IS_OS_WINME                 6
#define IS_OS_WINNET                7
#define IS_OS_WINSERVER2003         8


// ----------------------------------------------
// Bus speed
// ----------------------------------------------
#define IS_USB_10                   1
#define IS_USB_20                   4


// ----------------------------------------------
// sequence flags
// ----------------------------------------------
#define IS_LOCK_LAST_BUFFER         0x8002

// ----------------------------------------------
// Image files types
// ----------------------------------------------
#define IS_IMG_BMP         0
#define IS_IMG_JPG         1



// ----------------------------------------------
// DirectDraw steal video constants   (Falcon)
// ----------------------------------------------
#define IS_INIT_STEAL_VIDEO         1
#define IS_EXIT_STEAL_VIDEO         2
#define IS_INIT_STEAL_VIDEO_MANUAL  3
#define IS_INIT_STEAL_VIDEO_AUTO    4
#define IS_SET_STEAL_RATIO          64
#define IS_USE_MEM_IMAGE_SIZE       128
#define IS_STEAL_MODES_MASK         7
#define IS_SET_STEAL_COPY           0x1000
#define IS_SET_STEAL_NORMAL         0x2000

// ----------------------------------------------
// AGC modes   (Falcon)
// ----------------------------------------------
#define IS_GET_AGC_MODE             0x8000
#define IS_SET_AGC_OFF              0
#define IS_SET_AGC_ON               1


// ----------------------------------------------
// Gamma modes   (Falcon)
// ----------------------------------------------
#define IS_GET_GAMMA_MODE           0x8000
#define IS_SET_GAMMA_OFF            0
#define IS_SET_GAMMA_ON             1


// ----------------------------------------------
// sync levels   (Falcon)
// ----------------------------------------------
#define IS_GET_SYNC_LEVEL           0x8000
#define IS_SET_SYNC_75              0
#define IS_SET_SYNC_125             1


// ----------------------------------------------
// color bar modes   (Falcon)
// ----------------------------------------------
#define IS_GET_CBARS_MODE           0x8000
#define IS_SET_CBARS_OFF            0
#define IS_SET_CBARS_ON             1


// ----------------------------------------------
// horizontal filter defines   (Falcon)
// ----------------------------------------------
#define IS_GET_HOR_FILTER_MODE      0x8000
#define IS_GET_HOR_FILTER_STEP      0x8001

#define IS_DISABLE_HOR_FILTER       0
#define IS_ENABLE_HOR_FILTER        1
#define IS_HOR_FILTER_STEP(_s_)     ((_s_ + 1) << 1)
#define IS_HOR_FILTER_STEP1         2
#define IS_HOR_FILTER_STEP2         4
#define IS_HOR_FILTER_STEP3         6


// ----------------------------------------------
// vertical filter defines   (Falcon)
// ----------------------------------------------
#define IS_GET_VERT_FILTER_MODE     0x8000
#define IS_GET_VERT_FILTER_STEP     0x8001

#define IS_DISABLE_VERT_FILTER      0
#define IS_ENABLE_VERT_FILTER       1
#define IS_VERT_FILTER_STEP(_s_)    ((_s_ + 1) << 1)
#define IS_VERT_FILTER_STEP1        2
#define IS_VERT_FILTER_STEP2        4
#define IS_VERT_FILTER_STEP3        6


// ----------------------------------------------
// scaler modes   (Falcon)
// ----------------------------------------------
#define IS_GET_SCALER_MODE  (float) 1000
#define IS_SET_SCALER_OFF   (float) 0
#define IS_SET_SCALER_ON    (float) 1

#define IS_MIN_SCALE_X      (float)   6.25
#define IS_MAX_SCALE_X      (float) 100.00
#define IS_MIN_SCALE_Y      (float)   6.25
#define IS_MAX_SCALE_Y      (float) 100.00


// ----------------------------------------------
// video source selectors   (Falcon)
// ----------------------------------------------
#define IS_GET_VIDEO_IN             0x8000
#define IS_GET_VIDEO_PASSTHROUGH    0x8000
#define IS_GET_VIDEO_IN_TOGGLE      0x8001
#define IS_GET_TOGGLE_INPUT_1       0x8000
#define IS_GET_TOGGLE_INPUT_2       0x8001
#define IS_GET_TOGGLE_INPUT_3       0x8002
#define IS_GET_TOGGLE_INPUT_4       0x8003

#define IS_SET_VIDEO_IN_1           0x00
#define IS_SET_VIDEO_IN_2           0x01
#define IS_SET_VIDEO_IN_S           0x02
#define IS_SET_VIDEO_IN_3           0x03
#define IS_SET_VIDEO_IN_4           0x04
#define IS_SET_VIDEO_IN_1S          0x10
#define IS_SET_VIDEO_IN_2S          0x11
#define IS_SET_VIDEO_IN_3S          0x13
#define IS_SET_VIDEO_IN_4S          0x14
#define IS_SET_VIDEO_IN_EXT         0x40
#define IS_SET_TOGGLE_OFF           0xFF
#define IS_SET_VIDEO_IN_SYNC        0x4000


// ----------------------------------------------
// video crossbar selectors   (Falcon)
// ----------------------------------------------
#define IS_GET_CROSSBAR             0x8000

#define IS_CROSSBAR_1               0
#define IS_CROSSBAR_2               1
#define IS_CROSSBAR_3               2
#define IS_CROSSBAR_4               3
#define IS_CROSSBAR_5               4
#define IS_CROSSBAR_6               5
#define IS_CROSSBAR_7               6
#define IS_CROSSBAR_8               7
#define IS_CROSSBAR_9               8
#define IS_CROSSBAR_10              9
#define IS_CROSSBAR_11              10
#define IS_CROSSBAR_12              11
#define IS_CROSSBAR_13              12
#define IS_CROSSBAR_14              13
#define IS_CROSSBAR_15              14
#define IS_CROSSBAR_16              15
#define IS_SELECT_AS_INPUT          128


// ----------------------------------------------
// video format selectors   (Falcon)
// ----------------------------------------------
#define IS_GET_VIDEO_MODE           0x8000

#define IS_SET_VM_PAL               0
#define IS_SET_VM_NTSC              1
#define IS_SET_VM_SECAM             2
#define IS_SET_VM_AUTO              3


// ----------------------------------------------
// capture modes   (Falcon)
// ----------------------------------------------
#define IS_GET_CAPTURE_MODE         0x8000

#define IS_SET_CM_ODD               0x0001
#define IS_SET_CM_EVEN              0x0002
#define IS_SET_CM_FRAME             0x0004
#define IS_SET_CM_NONINTERLACED     0x0008
#define IS_SET_CM_NEXT_FRAME        0x0010
#define IS_SET_CM_NEXT_FIELD        0x0020
#define IS_SET_CM_BOTHFIELDS        (IS_SET_CM_ODD | IS_SET_CM_EVEN | IS_SET_CM_NONINTERLACED)
#define IS_SET_CM_FRAME_STEREO      0x2004


// ----------------------------------------------
// display update mode constants   (Falcon)
// ----------------------------------------------
#define IS_GET_UPDATE_MODE          0x8000
#define IS_SET_UPDATE_TIMER         1
#define IS_SET_UPDATE_EVENT         2


// ----------------------------------------------
// sync generator mode constants   (Falcon)
// ----------------------------------------------
#define IS_GET_SYNC_GEN             0x8000
#define IS_SET_SYNC_GEN_OFF         0
#define IS_SET_SYNC_GEN_ON          1


// ----------------------------------------------
// decimation modes   (Falcon)
// ----------------------------------------------
#define IS_GET_DECIMATION_MODE          0x8000
#define IS_GET_DECIMATION_NUMBER        0x8001

#define IS_DECIMATION_OFF               0
#define IS_DECIMATION_CONSECUTIVE       1
#define IS_DECIMATION_DISTRIBUTED       2


// ----------------------------------------------
// hardware watchdog defines   (Falcon)
// ----------------------------------------------
#define IS_GET_WATCHDOG_TIME            0x2000
#define IS_GET_WATCHDOG_RESOLUTION      0x4000
#define IS_GET_WATCHDOG_ENABLE          0x8000

#define IS_WATCHDOG_MINUTES             0
#define IS_WATCHDOG_SECONDS             0x8000
#define IS_DISABLE_WATCHDOG             0
#define IS_ENABLE_WATCHDOG              1
#define IS_RETRIGGER_WATCHDOG           2
#define IS_ENABLE_AUTO_DEACTIVATION     4
#define IS_DISABLE_AUTO_DEACTIVATION    8
#define IS_WATCHDOG_RESERVED            0x1000


// ----------------------------------------------
// typedefs
// ----------------------------------------------
#ifdef __LINUX__
        #include <stdint.h>

        // aliases for common Win32 types
        typedef int32_t           BOOLEAN;
        typedef int32_t           BOOL;
        typedef int32_t           INT;
        typedef uint32_t          UINT;
        typedef int32_t           LONG;
        typedef void              VOID;
        typedef void*             LPVOID;
        typedef uint32_t          ULONG;

        typedef uint64_t          UINT64;
        typedef int64_t           __int64;
        typedef int64_t           LONGLONG;
        typedef uint32_t          DWORD;
        typedef uint16_t          WORD;

        typedef unsigned char     BYTE;
        typedef char              CHAR;
        typedef char              TCHAR;
        typedef unsigned char     UCHAR;

        typedef int8_t*           LPTSTR;
        typedef const int8_t*     LPCTSTR;
        typedef const int8_t*     LPCSTR;
        typedef uint32_t          WPARAM;
        typedef uint32_t          LPARAM;
        typedef uint32_t          LRESULT;
        typedef uint32_t          HRESULT;

        typedef void*             HWND;
        typedef void*             HGLOBAL;
        typedef void*             HINSTANCE;
        typedef void*             HDC;
        typedef void*             HMODULE;
        typedef void*             HKEY;
        typedef void*             HANDLE;

        typedef BYTE*             LPBYTE;
        typedef DWORD*            PDWORD;
        typedef VOID*             PVOID;
        typedef CHAR*             PCHAR;


    #ifndef FALSE
        #define FALSE 0
    #endif
    #ifndef TRUE
        #define TRUE 1
    #endif

    #ifndef HIBYTE
        #define HIBYTE(_x_)    ( (_x_)>>8 )
    #endif

    #ifndef LOBYTE
        #define LOBYTE(_x_)    ( (_x_)&0x00ff )
    #endif

    #ifndef HIWORD
        #define HIWORD(_x_)    ( (_x_)>>16 )
    #endif

    #ifndef LOWORD
        #define LOWORD(_x_)    ( (_x_)&0x0000ffff )
    #endif

    #ifndef min
        #define min( _x_, _y_ ) ( (_x_)<(_y_) ? (_x_) : (_y_) )
    #endif

    #ifndef max
        #define max( _x_, _y_ ) ( (_x_)>(_y_) ? (_x_) : (_y_) )
    #endif

    #ifndef WM_USER
        #define WM_USER        0x400
    #endif


        // unknown stuff for Linux
        #define WINAPI
        #define CALLBACK
        #undef  UNICODE
        #define __stdcall

    //#define IDSEXP    EXTERNC __attribute__((cdecl)) INT
    //#define IDSEXPUL  EXTERNC __attribute__((cdecl)) ULONG
        #define IDSEXP    __attribute__((cdecl)) INT
        #define IDSEXPUL  __attribute__((cdecl)) ULONG


        typedef long (*WNDPROC) (HWND, UINT, WPARAM, LPARAM);


        typedef union _LARGE_INTEGER
        {
            struct
            {
                DWORD LowPart;
                LONG HighPart;
            };
            struct
            {
                DWORD LowPart;
                LONG HighPart;
            } u;
            LONGLONG QuadPart;
        } LARGE_INTEGER, *PLARGE_INTEGER;

        //usefull structs that were in windows.h
        typedef struct tagRECT
        {
            long    left;
            long    top;
            long    right;
            long    bottom;
        } RECT, *PRECT, *LPRECT;

        typedef struct tagRGNDATAHEADER
        {
            DWORD   dwSize;
            DWORD   iType;
            DWORD   nCount;
            DWORD   nRgnSize;
            RECT    rcBound;
        } RGNDATAHEADER, *PRGNDATAHEADER;

        typedef struct tagRGNDATA
        {
            RGNDATAHEADER   rdh;
            char            Buffer[1];
        } RGNDATA, *PRGNDATA, *LPRGNDATA;


        typedef struct tagBITMAPINFOHEADER
        {
                DWORD      biSize;
                long       biWidth;
                long       biHeight;
                WORD       biPlanes;
                WORD       biBitCount;
                DWORD      biCompression;
                DWORD      biSizeImage;
                long       biXPelsPerMeter;
                long       biYPelsPerMeter;
                DWORD      biClrUsed;
                DWORD      biClrImportant;
        } BITMAPINFOHEADER, *PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;

        typedef struct tagRGBQUAD
        {
                BYTE    rgbBlue;
                BYTE    rgbGreen;
                BYTE    rgbRed;
                BYTE    rgbReserved;
        } RGBQUAD;

        typedef struct tagBITMAPINFO
        {
            BITMAPINFOHEADER    bmiHeader;
            RGBQUAD             bmiColors[1];
        } BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;

        #define ZeroMemory(a,b)      memset((a), 0, (b))
    #define OutputDebugString(s) fprintf(stderr, s)


    #define INFINITE    -1
#else

#include <windows.h>

#if defined (_MSC_VER) || defined (__BORLANDC__) || defined (_WIN32_WCE)
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

typedef int     INT;

#endif    // Linux

// ----------------------------------------------
// typedefs
// ----------------------------------------------
typedef HANDLE  HIDS;
typedef HIDS    HCAM;
typedef HANDLE  HFALC;

// ----------------------------------------------
// info struct
// ----------------------------------------------
#define FALCINFO   BOARDINFO
#define PFALCINFO  PBOARDINFO
#define CAMINFO    BOARDINFO
#define PCAMINFO   PBOARDINFO

typedef struct
{
  char          SerNo[12];          // e.g. "1234512345"  (11 char)
  char          ID[20];             // e.g. "IDS GmbH"
  char          Version[10];        // e.g. "V2.10"  (9 char)
  char          Date[12];           // e.g. "24.01.2006" (11 char)
  unsigned char Select;             // contains board select number for multi board support
  unsigned char Type;               // e.g. IS_BOARD_TYPE_UEYE_USB
  char          Reserved[8];        // (7 char)
} BOARDINFO, *PBOARDINFO;


typedef struct _SENSORINFO
{
  WORD          SensorID;           // e.g. IS_SENSOR_UI224X_C
  TCHAR         strSensorName[32];  // e.g. "UI-224X-C"
  char          nColorMode;         // e.g. IS_COLORMODE_BAYER
  DWORD         nMaxWidth;          // e.g. 1280
  DWORD         nMaxHeight;         // e.g. 1024
  BOOL          bMasterGain;        // e.g. TRUE
  BOOL          bRGain;             // e.g. TRUE
  BOOL          bGGain;             // e.g. TRUE
  BOOL          bBGain;             // e.g. TRUE
  BOOL          bGlobShutter;       // e.g. TRUE
  char          Reserved[16];       // not used
} SENSORINFO, *PSENSORINFO;


typedef struct _REVISIONINFO
{
    WORD  size;                     // 2
    WORD  Sensor;                   // 2
    WORD  Cypress;                  // 2
    DWORD Blackfin;                 // 4
    WORD  DspFirmware;              // 2
                                    // --12
    WORD  USB_Board;                // 2
    WORD  Sensor_Board;             // 2
    WORD  Processing_Board;         // 2
    WORD  Memory_Board;             // 2
    WORD  Housing;                  // 2
    WORD  Filter;                   // 2
    WORD  Timing_Board;             // 2
    WORD  Product;                  // 2
                                    // --24
    BYTE reserved[100];             // --128
} REVISIONINFO, *PREVISIONINFO;


#ifndef UEYE_CAMERA_INFO_STRUCT
#define UEYE_CAMERA_INFO_STRUCT
typedef struct _UEYE_CAMERA_INFO
{
  DWORD     dwCameraID;   // this is the user defineable camera ID
  DWORD     dwDeviceID;   // this is the systems enumeration ID
  DWORD     dwSensorID;   // this is the sensor ID e.g. IS_SENSOR_UI141X_M
  DWORD     dwInUse;      // flag, whether the camera is in use or not
  TCHAR     SerNo[16];    // serial numer of the camera
  TCHAR     Model[16];    // model name of the camera
  DWORD     dwReserved[16];
}UEYE_CAMERA_INFO, *PUEYE_CAMERA_INFO;
#endif //UEYE_CAMERA_INFO_STRUCT

// usage of the list:
// 1. call the DLL with .dwCount = 0
// 2. DLL returns .dwCount = N  (N = number of available cameras)
// 3. call DLL with .dwCount = N and a pointer to UEYE_CAMERA_LIST with
//    and array of UEYE_CAMERA_INFO[N]
// 4. DLL will fill in the array with the camera infos and
//    will update the .dwCount member with the actual number of cameras
//    because there may be a change in number of cameras between step 2 and 3
// 5. check if there's a difference in actual .dwCount and formerly
//    reported value of N and call DLL again with an updated array size
#ifndef UEYE_CAMERA_LIST_STRUCT
#define UEYE_CAMERA_LIST_STRUCT
typedef struct _UEYE_CAMERA_LIST
{
  ULONG     dwCount;
  UEYE_CAMERA_INFO uci[1];
}UEYE_CAMERA_LIST, *PUEYE_CAMERA_LIST;
#endif //UEYE_CAMERA_LIST_STRUCT


// ----------------------------------------------
// auto feature structs and definitions
// ----------------------------------------------
#define AC_SHUTTER          0x00000001
#define AC_GAIN             0x00000002
#define AC_WHITEBAL         0x00000004
#define AC_WB_RED_CHANNEL   0x00000008
#define AC_WB_GREEN_CHANNEL 0x00000010
#define AC_WB_BLUE_CHANNEL  0x00000020
#define AC_FRAMERATE        0x00000040

#define ACS_ADJUSTING 0x00000001
#define ACS_FINISHED  0x00000002
#define ACS_DISABLED  0x00000004

typedef struct _AUTO_BRIGHT_STATUS
{
    DWORD curValue;             // current average greylevel
    long curError;             // current auto brightness error
    DWORD curController;        // current active brightness controller -> AC_x
    DWORD curCtrlStatus;        // current control status -> ACS_x
} AUTO_BRIGHT_STATUS, *PAUTO_BRIGHT_STATUS;



typedef struct _AUTO_WB_CHANNNEL_STATUS
{
    DWORD curValue;             // current average greylevel
    long curError;             // current auto wb error
    DWORD curCtrlStatus;        // current control status -> ACS_x
} AUTO_WB_CHANNNEL_STATUS, *PAUTO_WB_CHANNNEL_STATUS;

typedef struct _AUTO_WB_STATUS
{
    AUTO_WB_CHANNNEL_STATUS RedChannel;
    AUTO_WB_CHANNNEL_STATUS GreenChannel;
    AUTO_WB_CHANNNEL_STATUS BlueChannel;
    DWORD curController;        // current active wb controller -> AC_x
} AUTO_WB_STATUS, *PAUTO_WB_STATUS;

typedef struct _UEYE_AUTO_INFO
{
    DWORD               AutoAbility;        // autocontrol ability
    AUTO_BRIGHT_STATUS  sBrightCtrlStatus;  // brightness autocontrol status
    AUTO_WB_STATUS      sWBCtrlStatus;      // white balance autocontrol status
    DWORD               reserved[12];
} UEYE_AUTO_INFO, *PUEYE_AUTO_INFO;


// ----------------------------------------------
// function exports
// ----------------------------------------------
#ifdef __LINUX__
    IDSEXP is_WaitEvent             (HIDS hf, INT which, INT nTimeout);
#endif

// ----------------------------------------------
// functions only effective on Falcon boards
// ----------------------------------------------
  IDSEXP   is_SetVideoInput          (HIDS hf, INT Source);
  IDSEXP   is_SetSaturation          (HIDS hf, INT ChromU, INT ChromV);
  IDSEXP   is_SetHue                 (HIDS hf, INT Hue);
  IDSEXP   is_SetVideoMode           (HIDS hf, INT Mode);
  IDSEXP   is_SetAGC                 (HIDS hf, INT Mode);
  IDSEXP   is_SetSyncLevel           (HIDS hf, INT Level);
  IDSEXP   is_ShowColorBars          (HIDS hf, INT Mode);
  IDSEXP   is_SetScaler              (HIDS hf, float Scalex, float Scaley);
  IDSEXP   is_SetCaptureMode         (HIDS hf, INT Mode);
  IDSEXP   is_SetHorFilter           (HIDS hf, INT Mode);
  IDSEXP   is_SetVertFilter          (HIDS hf, INT Mode);
  IDSEXP   is_ScaleDDOverlay         (HIDS hf, BOOL boScale);
  IDSEXP   is_GetCurrentField        (HIDS hf, int* pField);
  IDSEXP   is_SetVideoSize           (HIDS hf, INT xpos, INT ypos, INT xsize, INT ysize);
  IDSEXP   is_SetKeyOffset           (HIDS hf, INT nOffsetX, INT nOffsetY);
  IDSEXP   is_PrepareStealVideo      (HIDS hf, int Mode, ULONG StealColorMode);
  IDSEXP   is_SetParentHwnd          (HIDS hf, HWND hwnd);
  IDSEXP   is_SetUpdateMode          (HIDS hf, INT mode);
  IDSEXP   is_OvlSurfaceOffWhileMove (HIDS hf, BOOL boMode);
  IDSEXP   is_GetPciSlot             (HIDS hf, INT* pnSlot);
  IDSEXP   is_GetIRQ                 (HIDS hf, INT* pnIRQ);
  IDSEXP   is_SetToggleMode          (HIDS hf, int nInput1, int nInput2, int nInput3, int nInput4);
  IDSEXP   is_SetDecimationMode      (HIDS hf, INT nMode, INT nDecimate);
  IDSEXP   is_SetSync                (HIDS hf, INT nSync);
  // only FALCON duo/quattro
  IDSEXP   is_SetVideoCrossbar       (HIDS hf, INT In, INT Out);
  // watchdog functions
  IDSEXP   is_WatchdogTime           (HIDS hf, long lTime);
  IDSEXP   is_Watchdog               (HIDS hf, long lMode);
  // video out functions
  IDSEXP   is_SetPassthrough         (HIDS hf, INT Source);

// ----------------------------------------------
// alias functions for compatibility
// ----------------------------------------------
  IDSEXP   is_InitBoard              (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitBoard              (HIDS hf);
  IDSEXP   is_InitFalcon             (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitFalcon             (HIDS hf);

  IDSEXP   is_GetBoardType           (HIDS hf);
  IDSEXP   is_GetBoardInfo           (HIDS hf, PBOARDINFO pInfo);
  IDSEXPUL is_BoardStatus            (HIDS hf, INT nInfo, ULONG ulValue);
  IDSEXP   is_GetNumberOfDevices     ();
  IDSEXP   is_GetNumberOfBoards      (INT* pnNumBoards);

// ----------------------------------------------
// common function
// ----------------------------------------------
  

  
  
  IDSEXP   is_StopLiveVideo          (HIDS hf, INT Wait);
  IDSEXP   is_FreezeVideo            (HIDS hf, INT Wait);
  IDSEXP   is_CaptureVideo           (HIDS hf, INT Wait);
  IDSEXP   is_IsVideoFinish          (HIDS hf, BOOL* pbo);
  IDSEXP   is_HasVideoStarted        (HIDS hf, BOOL* pbo);

  IDSEXP   is_SetBrightness          (HIDS hf, INT Bright);
  IDSEXP   is_SetContrast            (HIDS hf, INT Cont);
  IDSEXP   is_SetGamma               (HIDS hf, INT nGamma);

  IDSEXP   is_AllocImageMem          (HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid);
  IDSEXP   is_SetImageMem            (HIDS hf, char* pcMem, int id);
  IDSEXP   is_FreeImageMem           (HIDS hf, char* pcMem, int id);
  IDSEXP   is_GetImageMem            (HIDS hf, VOID** pMem);
  IDSEXP   is_GetActiveImageMem      (HIDS hf, char** ppcMem, int* pnID);
  IDSEXP   is_InquireImageMem        (HIDS hf, char* pcMem, int nID, int* pnX, int* pnY, int* pnBits, int* pnPitch);
  IDSEXP   is_GetImageMemPitch       (HIDS hf, INT* pPitch);

  IDSEXP   is_SetAllocatedImageMem   (HIDS hf, INT width, INT height, INT bitspixel, char* pcImgMem, int* pid);
  IDSEXP   is_SaveImageMem           (HIDS hf, const TCHAR* File, char* pcMem, int nID);
  IDSEXP   is_CopyImageMem           (HIDS hf, char* pcSource, int nID, char* pcDest);
  IDSEXP   is_CopyImageMemLines      (HIDS hf, char* pcSource, int nID, int nLines, char* pcDest);

  IDSEXP   is_AddToSequence          (HIDS hf, char* pcMem, INT nID);
  IDSEXP   is_ClearSequence          (HIDS hf);
  IDSEXP   is_GetActSeqBuf           (HIDS hf, INT* pnNum, char** ppcMem, char** ppcMemLast);
  IDSEXP   is_LockSeqBuf             (HIDS hf, INT nNum, char* pcMem);
  IDSEXP   is_UnlockSeqBuf           (HIDS hf, INT nNum, char* pcMem);

  IDSEXP   is_SetImageSize           (HIDS hf, INT x, INT y);
  IDSEXP   is_SetImagePos            (HIDS hf, INT x, INT y);

  IDSEXP   is_GetError               (HIDS hf, INT* pErr, TCHAR** ppcErr);
  IDSEXP   is_SetErrorReport         (HIDS hf, INT Mode);

  IDSEXP   is_ReadEEPROM             (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_WriteEEPROM            (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_SaveImage              (HIDS hf, const TCHAR* File);

  IDSEXP   is_SetColorMode           (HIDS hf, INT Mode);
  IDSEXP   is_GetColorDepth          (HIDS hf, INT* pnCol, INT* pnColMode);
  // bitmap display function
  IDSEXP   is_RenderBitmap           (HIDS hf, INT nMemID, HWND hwnd, INT nMode);

  IDSEXP   is_SetDisplayMode         (HIDS hf, INT Mode);
  IDSEXP   is_GetDC                  (HIDS hf, HDC* phDC);
  IDSEXP   is_ReleaseDC              (HIDS hf, HDC hDC);
  IDSEXP   is_UpdateDisplay          (HIDS hf);
  IDSEXP   is_SetDisplaySize         (HIDS hf, INT x, INT y);
  IDSEXP   is_SetDisplayPos          (HIDS hf, INT x, INT y);

  IDSEXP   is_LockDDOverlayMem       (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDOverlayMem     (HIDS hf);
  IDSEXP   is_LockDDMem              (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDMem            (HIDS hf);
  IDSEXP   is_GetDDOvlSurface        (HIDS hf, void** ppDDSurf);
  IDSEXP   is_SetKeyColor            (HIDS hf, INT r, INT g, INT b);
  IDSEXP   is_StealVideo             (HIDS hf, int Wait);
  IDSEXP   is_SetHwnd                (HIDS hf, HWND hwnd);


  IDSEXP   is_SetDDUpdateTime        (HIDS hf, INT ms);
  IDSEXP   is_EnableDDOverlay        (HIDS hf);
  IDSEXP   is_DisableDDOverlay       (HIDS hf);
  IDSEXP   is_ShowDDOverlay          (HIDS hf);
  IDSEXP   is_HideDDOverlay          (HIDS hf);


  IDSEXP   is_GetVsyncCount          (HIDS hf, long* pIntr, long* pActIntr);
  IDSEXP   is_GetOsVersion           ();
  // version information
  IDSEXP   is_GetDLLVersion          ();

  IDSEXP   is_InitEvent              (HIDS hf, HANDLE hEv, INT which);
  IDSEXP   is_ExitEvent              (HIDS hf, INT which);
  IDSEXP   is_EnableEvent            (HIDS hf, INT which);
  IDSEXP   is_DisableEvent           (HIDS hf, INT which);

  IDSEXP   is_SetIO                  (HIDS hf, INT nIO);
  IDSEXP   is_SetFlashStrobe         (HIDS hf, INT nMode, INT nLine);
  IDSEXP   is_SetExternalTrigger     (HIDS hf, INT nTriggerMode);
  IDSEXP   is_SetTriggerCounter      (HIDS hf, INT nValue);
  IDSEXP   is_SetRopEffect           (HIDS hf, INT effect, INT param, INT reserved);

// ----------------------------------------------
// new functions only valid for uEye USB
// ----------------------------------------------
  // Camera functions
  IDSEXP is_InitCamera                  (HIDS* phf, HWND hWnd);
  IDSEXP is_ExitCamera                  (HIDS hf);
  IDSEXP is_GetCameraInfo               (HIDS hf, PCAMINFO pInfo);
  IDSEXPUL is_CameraStatus              (HIDS hf, INT nInfo, ULONG ulValue);
  IDSEXP is_GetCameraType               (HIDS hf);
  IDSEXP is_GetNumberOfCameras          (INT* pnNumCams);

  // PixelClock
  IDSEXP is_GetPixelClockRange          (HIDS hf, INT *pnMin, INT *pnMax);
  IDSEXP is_SetPixelClock               (HIDS hf, INT Clock);
  IDSEXP is_GetUsedBandwidth            (HIDS hf);
  // Set/Get Framerate
  IDSEXP is_GetFrameTimeRange           (HIDS hf, double *min, double *max, double *intervall);
  IDSEXP is_SetFrameRate                (HIDS hf, double FPS, double* newFPS);
  // Set/Get Exposure
  IDSEXP is_GetExposureRange            (HIDS hf, double *min, double *max, double *intervall);
  IDSEXP is_SetExposureTime             (HIDS hf, double EXP, double* newEXP);
  // get frames per second
  IDSEXP is_GetFramesPerSecond          (HIDS hf, double *dblFPS);

  // is_SetIOMask ( only uEye USB )
  IDSEXP is_SetIOMask                   (HIDS hf, INT nMask);

  // Get Sensorinfo
  IDSEXP is_GetSensorInfo               (HIDS hf, PSENSORINFO pInfo);
  // Get RevisionInfo
  IDSEXP is_GetRevisionInfo             (HIDS hf, PREVISIONINFO prevInfo);

  // enable/disable AutoExit after device remove
  IDSEXP is_EnableAutoExit              (HIDS hf, INT nMode);
  // Message
  IDSEXP is_EnableMessage               (HIDS hf, INT which, HWND hWnd);

  // hardware gain settings
  IDSEXP is_SetHardwareGain             (HIDS hf, INT nMaster, INT nRed, INT nGreen, INT nBlue);

  // set render mode
  IDSEXP is_SetRenderMode               (HIDS hf, INT Mode);

  // enable/disable WhiteBalance
  IDSEXP is_SetWhiteBalance             (HIDS hf, INT nMode);
  IDSEXP is_SetWhiteBalanceMultipliers  (HIDS hf, double dblRed, double dblGreen, double dblBlue);
  IDSEXP is_GetWhiteBalanceMultipliers  (HIDS hf, double *pdblRed, double *pdblGreen, double *pdblBlue);

  // Edge enhancement
  IDSEXP is_SetEdgeEnhancement          (HIDS hf, INT nEnable);

  // Sensor features
  IDSEXP is_SetColorCorrection          (HIDS hf, INT nEnable, double *factors);
  IDSEXP is_SetBlCompensation           (HIDS hf, INT nEnable, INT offset, INT reserved);

  // Hotpixel
  IDSEXP is_SetBadPixelCorrection       (HIDS hf, INT nEnable, INT threshold);
  IDSEXP is_LoadBadPixelCorrectionTable (HIDS hf, const TCHAR *File);
  IDSEXP is_SaveBadPixelCorrectionTable (HIDS hf, const TCHAR *File);
  IDSEXP is_SetBadPixelCorrectionTable  (HIDS hf, INT nMode, WORD *pList);

  // Memoryboard
  IDSEXP is_SetMemoryMode               (HIDS hf, INT nCount, INT nDelay);
  IDSEXP is_TransferImage               (HIDS hf, INT nMemID, INT seqID, INT imageNr, INT reserved);
  IDSEXP is_TransferMemorySequence      (HIDS hf, INT seqID, INT StartNr, INT nCount, INT nSeqPos);
  IDSEXP is_MemoryFreezeVideo           (HIDS hf, INT nMemID, INT Wait);
  IDSEXP is_GetLastMemorySequence       (HIDS hf, INT *pID);
  IDSEXP is_GetNumberOfMemoryImages     (HIDS hf, INT nID, INT *pnCount);
  IDSEXP is_GetMemorySequenceWindow     (HIDS hf, INT nID, INT *left, INT *top, INT *right, INT *bottom);
  IDSEXP is_IsMemoryBoardConnected      (HIDS hf, BOOL *pConnected);
  IDSEXP is_ResetMemory                 (HIDS hf, INT nReserved);

  IDSEXP is_SetSubSampling              (HIDS hf, INT mode);
  IDSEXP is_ForceTrigger                (HIDS hf);

  // new with driver version 1.12.0006
  IDSEXP is_GetBusSpeed                 (HIDS hf);

  // new with driver version 1.12.0015
  IDSEXP is_SetBinning                  (HIDS hf, INT mode);

  // new with driver version 1.12.0017
  IDSEXP is_ResetToDefault              (HIDS hf);
  IDSEXP is_LoadParameters              (HIDS hf, const TCHAR* pFilename);
  IDSEXP is_SaveParameters              (HIDS hf, const TCHAR* pFilename);

  // new with driver version 1.14.0001
  IDSEXP is_GetGlobalFlashDelays        (HIDS hf, ULONG *pulDelay, ULONG *pulDuration);
  IDSEXP is_SetFlashDelay               (HIDS hf, ULONG ulDelay, ULONG ulDuration);
  // new with driver version 1.14.0002
  IDSEXP is_LoadImage                   (HIDS hf, const TCHAR* File);

  // new with driver version 1.14.0008
  IDSEXP is_SetImageAOI                 (HIDS hf, INT xPos, INT yPos, INT width, INT height);
  IDSEXP is_SetCameraID                 (HIDS hf, INT nID);
  IDSEXP is_SetBayerConversion          (HIDS hf, INT nMode);
  IDSEXP is_SetTestImage                (HIDS hf, INT nMode);
  // new with driver version 1.14.0009
  IDSEXP is_SetHardwareGamma            (HIDS hf, INT nMode);

  // new with driver version 2.00.0001
  IDSEXP is_GetCameraList               (PUEYE_CAMERA_LIST pucl);

  // new with driver version 2.00.0011
  IDSEXP is_SetAOI                      (HIDS hf, INT type, INT *pXPos, INT *pYPos, INT *pWidth, INT *pHeight);
  IDSEXP is_SetAutoParameter            (HIDS hf, INT param, double *pval1, double *pval2);
  IDSEXP is_GetAutoInfo                 (HIDS hf, UEYE_AUTO_INFO *pInfo);
  
  // new with driver version 2.20.0001
  IDSEXP is_ConvertImage                (HIDS hf, char* pcSource, int nIDSource, char** pcDest, INT *nIDDest, INT *reserved);
  IDSEXP is_SetConvertParam             (HIDS hf, BOOL ColorCorrection, INT BayerConversionMode, INT ColorMode, INT Gamma, double* WhiteBalanceMultipliers);
  
  IDSEXP is_SaveImageEx                 (HIDS hf, const TCHAR* File, INT fileFormat, INT Param);
  IDSEXP is_SaveImageMemEx              (HIDS hf, const TCHAR* File, char* pcMem, INT nID, INT FileFormat, INT Param);
  IDSEXP is_LoadImageMem                (HIDS hf, const TCHAR* File, char** ppcImgMem, INT* pid);
  
  IDSEXP is_GetImageHistogram           (HIDS hf, int nID, INT ColorMode, DWORD* pHistoMem);
  IDSEXP is_SetTriggerDelay             (HIDS hf, INT nTriggerDelay);

  IDSEXP is_SetGainBoost                (HIDS hf, INT mode);
  IDSEXP is_SetLED                      (HIDS hf, INT nValue);

  IDSEXP is_SetGlobalShutter            (HIDS hf, INT mode );
  IDSEXP is_SetExtendedRegister         ( HIDS hf, INT index,WORD value);

  // new with driver version 2.22.0002
  IDSEXP is_SetHWGainFactor             (HIDS hf, INT nMode, INT nFactor);

#ifdef __cplusplus
};
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  // #ifndef __IDS_HEADER__
