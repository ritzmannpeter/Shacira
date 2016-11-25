#ifndef __FALCAVI_H__
#define __FALCAVI_H__


#ifdef __cplusplus
 extern "C" {
#endif

// error constants --------------------------------------------
#define ISAVIERRBASE    300
#define ISAVIMAKEERR(_x_)               (ISAVIERRBASE + _x_)

#define IS_AVI_NO_ERR                       0
#define IS_AVI_ERR_INVALID_BOARD_HANDLE     ISAVIMAKEERR( 1)
#define IS_AVI_ERR_WRONG_VFW_VERSION        ISAVIMAKEERR( 2)
#define IS_AVI_ERR_INVALID_FILE             ISAVIMAKEERR( 3)
#define IS_AVI_ERR_NEW_FAILED               ISAVIMAKEERR( 4)
#define IS_AVI_ERR_INVALID_COLOR_MODE       ISAVIMAKEERR( 5)
#define IS_AVI_ERR_ALLOC_FAILED             ISAVIMAKEERR( 6)
#define IS_AVI_ERR_AVIFILEOPEN              ISAVIMAKEERR( 7)
#define IS_AVI_ERR_CREATESTREAM             ISAVIMAKEERR( 8)
#define IS_AVI_ERR_ICOPEN                   ISAVIMAKEERR( 9)
#define IS_AVI_ERR_NO_CODEC_SET             ISAVIMAKEERR(10)
#define IS_AVI_ERR_STREAMSETFORMAT          ISAVIMAKEERR(11)
#define IS_AVI_ERR_CREATEEVENT_FAILED       ISAVIMAKEERR(12)
#define IS_AVI_ERR_INITEVENT_FAILED         ISAVIMAKEERR(13)
#define IS_AVI_ERR_THREAD_FAILED            ISAVIMAKEERR(14)
#define IS_AVI_ERR_IMGMEMLOCK               ISAVIMAKEERR(15)
#define IS_AVI_ERR_PARAMETER                ISAVIMAKEERR(16)
#define IS_AVI_ERR_PARAMETER_1              ISAVIMAKEERR(17)
#define IS_AVI_ERR_PARAMETER_2              ISAVIMAKEERR(18)
#define IS_AVI_ERR_PARAMETER_3              ISAVIMAKEERR(19)
#define IS_AVI_ERR_PARAMETER_4              ISAVIMAKEERR(20)
#define IS_AVI_ERR_NO_CODEC_AVAIL           ISAVIMAKEERR(21)
#define IS_AVI_ERR_INVALID_ID               ISAVIMAKEERR(22)
#define IS_AVI_ERR_FILE_OPEN                ISAVIMAKEERR(23)
#define IS_AVI_ERR_INVALID_FILE_FORMAT      ISAVIMAKEERR(24)
#define IS_AVI_ERR_BUFFER_TOO_SMALL         ISAVIMAKEERR(25)
#define IS_AVI_ERR_COMPRESS                 ISAVIMAKEERR(26)
#define IS_AVI_ERR_DECOMPRESS               ISAVIMAKEERR(27)
#define IS_AVI_ERR_CAPTURE_RUNNING          ISAVIMAKEERR(28)
#define IS_AVI_ERR_CAPTURE_NOT_RUNNING      ISAVIMAKEERR(29)
#define IS_AVI_ERR_FIFO_FULL                ISAVIMAKEERR(30)
#define IS_AVI_ERR_FIFO_EMPTY               ISAVIMAKEERR(31)
#define IS_AVI_ERR_PLAY_RUNNING             ISAVIMAKEERR(32)
#define IS_AVI_ERR_PLAY_NOT_RUNNING         ISAVIMAKEERR(33)
#define IS_AVI_ERR_FALCON_DLL_MISSING       ISAVIMAKEERR(34)



// set, get parameters ----------------------------------------
#define IS_AVI_PARAM_BOARD_HANDLE          1 //  - , get
#define IS_AVI_PARAM_QUALITY               2 // set, get compression quality
#define IS_AVI_PARAM_CAPSIZE_X             3 // set, get capture width
#define IS_AVI_PARAM_CAPSIZE_Y             4 // set, get capture height
#define IS_AVI_PARAM_SPEED                 5 // set, get capture speed in ms/frame
#define IS_AVI_PARAM_AVIPOS                6 //  - , get number of frames written
#define IS_AVI_PARAM_AVILEN                7 //  - , get number of frames written
#define IS_AVI_PARAM_DISPLAY               8 // set, get the window handle to which the frames should be drawn
#define IS_AVI_PARAM_CALLBACK              9 // set, get the window that will receive messages
#define IS_AVI_PARAM_MAXTIME              10 // set, get maximum number of seconds for capture
#define IS_AVI_PARAM_VIDEO_IN             11 // set, get current video input
#define IS_AVI_PARAM_DISPSIZE_X           12 // set, get display width
#define IS_AVI_PARAM_DISPSIZE_Y           13 // set, get display height
#define IS_AVI_PARAM_DISPPOS_X            14 // set, get x position of frame in window
#define IS_AVI_PARAM_DISPPOS_Y            15 // set, get y
#define IS_AVI_PARAM_FIFO                 16 // set, get fifo flag
#define IS_AVI_PARAM_EXTERNAL_BUFFERS     17 // set, get
//#define IS_AVI_PARAM_BUFSIZE_4_QUALITY    18 //  - , get
#define IS_AVI_PARAM_FILE                 19 // set, get
#define IS_AVI_PARAM_VIDEO_MODE           20 // set, get

#define IS_AVI_PARAM_START_POS            21 // set, get start frame position in video
#define IS_AVI_PARAM_END_POS              22 // set, get end frame position in video
#define IS_AVI_PARAM_PLAY_BACKWARDS       23 // set, get boolean value for playing direction
#define IS_AVI_PARAM_PLAY_LOOP            24 // set, get boolean value for loop mode

#define IS_AVI_PARAM_CALLBACK_CLASS       25 // set,  -  callback class (pre&post processing), use NULL to disable
#define IS_AVI_PARAM_CALLBACK_PREPROCESS  26 // set,  -  set callback function for preprocessing, use NULL to disable
#define IS_AVI_PARAM_CALLBACK_POSTPROCESS 27 // set,  -  set callback function for postprocessing, use NULL to disable

#define IS_AVI_PARAM_DEINTERLACE_MODE     28 // set, get deinterlace mode ( 0 (default) = deactivated )
#define IS_AVI_PARAM_CAPTURE_STATE        29 // set, get capture state (paused, running, ...)
#define IS_AVI_PARAM_FINDPREVKEY          30 // -  , get find previous keyframe
#define IS_AVI_PARAM_FINDNEXTKEY          31 // -  , get find next keyframe
#define IS_AVI_PARAM_GM_AUDIO_ENABLE      32 // set, get Ligos GoMotion audio enable
#define IS_AVI_PARAM_GM_AUDIO_BITRATE     33 // set, get Ligos GoMotion audio bitrate
#define IS_AVI_PARAM_GM_AUDIO_MODE        34 // set, get Ligos GoMotion audio mode
#define IS_AVI_PARAM_GM_TOTALBYTES        35 //  - , get total amount of written KB
#define IS_AVI_PARAM_GM_MPEG_TYPE         36 // set, get GoMotion MPEG type
#define IS_AVI_PARAM_DOWNSCALE            37 // set, get downscale the image for the codec
#define IS_AVI_PARAM_DOWNSCALE_X          38 //  - , get downscaled width
#define IS_AVI_PARAM_DOWNSCALE_Y          39 //  - , get downscaled height


// same as VIDEOHDR in msvideo.h
typedef struct 
{
  LPBYTE  lpData;
  DWORD   dwBufferLength;
  DWORD   dwBytesUsed;
  DWORD   dwTimeCaptured;
  DWORD   dwUser;
  DWORD   dwFlags;
  DWORD   dwReserved[4];
} IS_VIDEOHDR, *PIS_VIDEOHDR;


// compressor struct ------------------------------------------
typedef struct
{ 
    DWORD fccHandler;
    char  szName[16];
    char  szDescription[128];
    char  szDriver[128];
    BOOL  bSupportsQuality;
    BOOL  bHasConfigureDlg;
    BOOL  bHasAboutDlg;
} IS_CINFO, *PIS_CINFO;


// capture states ---------------------------------------------
#define IS_AVI_CAPTURE_RUNNING      0
#define IS_AVI_CAPTURE_RESUME       0
#define IS_AVI_CAPTURE_STOPPED      1
#define IS_AVI_CAPTURE_PAUSE        1

// deinterlacing methods --------------------------------------
#define IS_AVI_DEINT_NONE           0   // no deinterlacing
#define IS_AVI_DEINT_BOB_SIMPLE     1   // simple bob
#define IS_AVI_DEINT_BOB_INTERP     2   // linear interpolated bob
#define IS_AVI_DEINT_BOB_MOTION     3   // only bob the areas where there was field motion

// open modes -------------------------------------------------
#define IS_AVI_MODE_CAPTURE     1   // capture only
#define IS_AVI_MODE_NOFILE      2   //
#define IS_AVI_MODE_NOHW        8   // no hardware
#define IS_AVI_MODE_PLAY       16   // playback only

// compressor types ------------------------------------------- 
#define IS_AVI_CODEC_NONE       0   // FCC = RAW
#define IS_AVI_CODEC_SYSTEM     1   // FCC = ????
#define IS_AVI_CODEC_INTERNAL   2   // FCC = MJPG
#define IS_AVI_CODEC_GOMOTION   3   // FCC = ????

// message types ----------------------------------------------
#define IS_AVI_MSG_COMPRESSED       (WM_USER + 17160)
#define IS_AVI_MSG_DECOMPRESSED     (WM_USER + 17161)
#define IS_AVI_MSG_FINISHED         (WM_USER + 17162)
#define IS_AVI_MSG_FIFO_EMPTY       (WM_USER + 17163)
#define IS_AVI_MSG_LOST_FRAMES      (WM_USER + 17164)


#if defined (_MSC_VER) || defined (__BORLANDC__)
  #if defined (_PURE_C) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSAVIEXP     extern  __declspec(dllimport) INT __stdcall
  #elif defined (__STDC__) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSAVIEXP   extern  __declspec(dllimport) INT __stdcall
  #elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)   // using the DLL, not creating one
    #define IDSAVIEXP   extern "C" __declspec(dllimport) INT __stdcall
  #else            // for creating cdecl dll
    #define IDSAVIEXP    extern  __declspec(dllexport) INT __stdcall
  #endif
#elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)  // using the DLL, not creating one
  #define IDSAVIEXP    extern  __declspec(dllimport) INT __stdcall
#endif



typedef HANDLE HIDS;


// function prototyes
// Parameters of isavi_OpenAVI
// hBoard             FALCON handle
// hwndDisp           display window handle
// hwndCallback       callabck window handle
// nXSize             width of source image
// nYSize             height of source image
// nSpeed             capture speed in milliseconds between two captured images (min: 40ms)
// pFileName          string with filename or NULL for SaveAs dialogbox
// boWithCompression  flag if compression should be used
//                    0 no compression
//                    1 with compression. a selection of all installed codecs will
//                      show up where you can select one.
IDSAVIEXP isavi_InitAVI             (HIDS hBoard, int nMode, int* pnAviID);
IDSAVIEXP isavi_ExitAVI             (int nAviID);
IDSAVIEXP isavi_OpenAVI             (int nAviID, const char* pFileName);
IDSAVIEXP isavi_CloseAVI            (int nAviID);
IDSAVIEXP isavi_WriteToAVIFile      (int nAviID, PIS_VIDEOHDR pvh);
IDSAVIEXP isavi_ReadFromAVIFile     (int nAviID, PIS_VIDEOHDR pvh);
IDSAVIEXP isavi_StartAVI            (int nAviID);
IDSAVIEXP isavi_StopAVI             (int nAviID);
IDSAVIEXP isavi_RefreshDisplay      (int nAviID);
IDSAVIEXP isavi_RenderFrame         (int nAviID, long lFrame);
IDSAVIEXP isavi_AddBuffer           (int nAviID, PIS_VIDEOHDR pvh);
IDSAVIEXP isavi_SetAVIParam         (int nAviID, int nType, long lValue);
IDSAVIEXP isavi_GetAVIParam         (int nAviID, int nType, long* plValue);
IDSAVIEXP isavi_GetAVIFileName      (int nAviID, char * strName);
IDSAVIEXP isavi_SaveJPG             (int nAviID, const char* pcFile, PIS_VIDEOHDR pvh);
IDSAVIEXP isavi_LoadJPG             (int nAviID, const char* pcFile, PIS_VIDEOHDR pvh);
// Codec functions
IDSAVIEXP isavi_ConfigureCodec      (int nAviID, HWND hParent);
IDSAVIEXP isavi_AboutCodec          (int nAviID, HWND hParent);
IDSAVIEXP isavi_GetNumCodecs        (int nAviID, int* pnNumCodecs);
IDSAVIEXP isavi_GetCodecInfo        (int nAviID, int nNumCodec, PIS_CINFO pcInfo);
IDSAVIEXP isavi_SelectCodec         (int nAviID, PIS_CINFO pcInfo);
// Compress/Decompress using currently selected codec
IDSAVIEXP isavi_GetMaxCompressedSize(int nAviID, BITMAPINFOHEADER* pbmihIn, char* pcIn, long* size, int nQuality);
IDSAVIEXP isavi_Compress            (int nAviID, BITMAPINFOHEADER* pbmihIn, char* pcIn, PIS_VIDEOHDR pvhOut, int nQuality);
IDSAVIEXP isavi_Decompress          (int nAviID, PIS_VIDEOHDR pvhIn, BITMAPINFOHEADER* pbmihOut, char* pcOut);


// For use with IS_AVI_PARAM_CALLBACK_CLASS
#ifdef __cplusplus
class FALCAVI_CALLBACK_CLASS
{
public:
  // preprocessor callback (before compression)
  virtual void OnPreprocessImage(PBYTE pbData, int nRs) = 0;
  // postprocessor callback (after decompression)
  virtual void OnPostprocessImage(PBYTE pbData, int nRs) = 0;
};
#endif

// For use with IS_AVI_PARAM_CALLBACK_PREPROCESS
//              IS_AVI_PARAM_CALLBACK_POSTPROCESS
// native C callback function
typedef void (WINAPI* FALCAVI_CALLBACK_FUNC)(PBYTE pbData, int nRs);


#ifdef __cplusplus
 }
#endif



#endif // __FALCAVI_H__