
#ifndef cIdsGrabber_h
#define cIdsGrabber_h 1

#include "FirstHeader.h"
#include "windows.h"
#include "ueye.h"

#define EAGLE_MAX_CHANNELS 4
#define IDS_RESULT INT

typedef IDS_RESULT (*T_InitBoard)(HIDS* phf, HWND hWnd);
typedef IDS_RESULT (*T_GetBoardInfo)(HIDS hf, PBOARDINFO pInfo);
typedef IDS_RESULT (*T_GetSensorInfo)(HIDS hf, PSENSORINFO pInfo);
typedef IDS_RESULT (*T_SetDisplayMode)(HIDS hf, INT Mode);
typedef IDS_RESULT (*T_SetImageSize)(HIDS hf, INT x, INT y);
typedef IDS_RESULT (*T_SetColorMode)(HIDS hf, INT Mode);
typedef IDS_RESULT (*T_AllocImageMem)(HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid);
typedef IDS_RESULT (*T_SetImageMem)(HIDS hf, char* pcMem, int id);
typedef IDS_RESULT (*T_SetCaptureMode)(HIDS hf, INT Mode);
typedef IDS_RESULT (*T_CaptureVideo)(HIDS hf, INT Wait);
typedef IDS_RESULT (*T_FreezeVideo)(HIDS hf, INT Wait);
typedef IDS_RESULT (*T_FreezeVideo)(HIDS hf, INT Mode);
typedef IDS_RESULT (*T_FreeImageMem)(HIDS hf, char* pcMem, int id);
typedef IDS_RESULT (*T_ExitBoard)(HIDS hf);
typedef IDS_RESULT (*T_GetError)(HIDS hf, INT* pErr, char** ppcErr);
typedef IDS_RESULT (*T_SetVideoInput)(HIDS hf, INT Source);
typedef IDS_RESULT (*T_CopyImageMem)(HIDS hf, char* pcSource, int nID, char* pcDest);
typedef IDS_RESULT (*T_SetPixelClock)(HIDS hf, INT Clock);
typedef IDS_RESULT (*T_SetFrameRate)(HIDS hf, double FPS, double* newFPS);
typedef IDS_RESULT (*T_SetContrast)(HIDS hf, INT Contrast);
typedef IDS_RESULT (*T_SetBrightness)(HIDS hf, INT Brightness);
typedef IDS_RESULT (*T_LoadParameters)(HIDS hf, const TCHAR* pFilename);
typedef IDS_RESULT (*T_SaveParameters)(HIDS hf, const TCHAR* pFilename);
typedef IDS_RESULT (*T_SetVideoMode)(HIDS hf, INT Mode);
typedef IDS_RESULT (*T_SetHardwareGain)(HIDS hf, INT nMaster, INT nRed, INT nGreen, INT nBlue);
typedef IDS_RESULT (*T_GetExposureRange)(HIDS hf, double *min, double *max, double *intervall);
typedef IDS_RESULT (*T_SetExposureTime)(HIDS hf, double EXP, double* newEXP);

class cIdsGrabber
{
public:
   cIdsGrabber(CONST_STRING_T dll_name);
   ~cIdsGrabber();
   IDS_RESULT InitBoard(HIDS* phf, HWND hWnd);
   IDS_RESULT GetBoardInfo(HIDS hf, PBOARDINFO pInfo);
   IDS_RESULT GetSensorInfo(HIDS hf, PSENSORINFO pInfo);
   IDS_RESULT SetDisplayMode(HIDS hf, INT Mode);
   IDS_RESULT SetImageSize(HIDS hf, INT x, INT y);
   IDS_RESULT SetColorMode(HIDS hf, INT Mode);
   IDS_RESULT AllocImageMem(HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid);
   IDS_RESULT SetImageMem(HIDS hf, char* pcMem, int id);
   IDS_RESULT SetCaptureMode(HIDS hf, INT Mode);
   IDS_RESULT CaptureVideo(HIDS hf, INT Wait);
   IDS_RESULT FreezeVideo(HIDS hf, INT Wait);
   IDS_RESULT FreeImageMem(HIDS hf, char* pcMem, int id);
   IDS_RESULT ExitBoard(HIDS hf);
   IDS_RESULT GetError(HIDS hf, INT* pErr, char** ppcErr);
   IDS_RESULT SetVideoInput(HIDS hf, INT Source);
   IDS_RESULT CopyImageMem(HIDS hf, char* pcSource, int nID, char* pcDest);
   IDS_RESULT SetPixelClock(HIDS hf, INT Clock);
   IDS_RESULT SetFrameRate(HIDS hf, double FPS, double* newFPS);
   IDS_RESULT SetContrast(HIDS hf, INT Contrast);
   IDS_RESULT SetBrightness(HIDS hf, INT Brightness);
   IDS_RESULT LoadParameters(HIDS hf, const TCHAR* pFilename);
   IDS_RESULT SaveParameters(HIDS hf, const TCHAR* pFilename);
   IDS_RESULT SetVideoMode(HIDS hf, INT Mode);
   IDS_RESULT SetHardwareGain(HIDS hf, INT nMaster, INT nRed, INT nGreen, INT nBlue);
   IDS_RESULT GetExposureRange(HIDS hf, double *min, double *max, double *intervall);
   IDS_RESULT SetExposureTime(HIDS hf, double EXP, double* newEXP);

protected:
   HMODULE _GrabberDLL;
private:
   STRING_T _DLLName;
   T_InitBoard _InitBoard;
   T_GetBoardInfo _GetBoardInfo;
   T_GetSensorInfo _GetSensorInfo;
   T_SetDisplayMode _SetDisplayMode;
   T_SetImageSize _SetImageSize;
   T_SetColorMode _SetColorMode;
   T_AllocImageMem _AllocImageMem;
   T_SetImageMem _SetImageMem;
   T_SetCaptureMode _SetCaptureMode;
   T_CaptureVideo _CaptureVideo;
   T_FreezeVideo _FreezeVideo;
   T_FreeImageMem _FreeImageMem;
   T_ExitBoard _ExitBoard;
   T_GetError _GetError;
   T_SetVideoInput _SetVideoInput;
   T_CopyImageMem _CopyImageMem;
   T_SetPixelClock _SetPixelClock;
   T_SetFrameRate _SetFrameRate;
   T_SetContrast _SetContrast;
   T_SetBrightness _SetBrightness;
   T_LoadParameters _LoadParameters;
   T_SaveParameters _SaveParameters;
   T_SetVideoMode _SetVideoMode;
   T_SetHardwareGain _SetHardwareGain;
   T_GetExposureRange _GetExposureRange;
   T_SetExposureTime _SetExposureTime;

private:
   void LoadDLL();
   void LoadProc(void * & func_ptr, CONST_STRING_T func_name);
};

#define MAX_BOARDS  20

class cFalcon
{
public:
   cFalcon();
   virtual ~cFalcon();
   HIDS OpenHandle(cIdsGrabber * grabber, ULONG_T board_id, BOOL_T & new_handle);
   void SetVideoBuffer(char * buffer, ULONG_T board_id);
   char * GetVideoBuffer(ULONG_T board_id);
private:
   HIDS _BoardHandles[MAX_BOARDS];
   char * _VideoBuffer[MAX_BOARDS];
};

class cUEye
{
public:
   cUEye();
   virtual ~cUEye();
   HIDS OpenHandle(cIdsGrabber * grabber, ULONG_T camera_id);
private:
};

#endif
