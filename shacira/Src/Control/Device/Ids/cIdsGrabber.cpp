
#include "Control/Device/Ids/cIdsGrabber.h"

cIdsGrabber::cIdsGrabber(CONST_STRING_T dll_name)
{
   _DLLName = dll_name;
   _GrabberDLL = NULL;
   _InitBoard = NULL;
   _GetBoardInfo = NULL;
   _GetSensorInfo = NULL;
   _SetDisplayMode = NULL;
   _SetImageSize = NULL;
   _SetColorMode = NULL;
   _AllocImageMem = NULL;
   _SetImageMem = NULL;
   _SetCaptureMode = NULL;
   _CaptureVideo = NULL;
   _FreezeVideo = NULL;
   _FreeImageMem = NULL;
   _ExitBoard = NULL;
   _GetError = NULL;
   _SetVideoInput = NULL;
   _CopyImageMem = NULL;
   _SetPixelClock = NULL;
   _SetFrameRate = NULL;
   _SetContrast = NULL;
   _SetBrightness = NULL;
   _LoadParameters = NULL;
   _SaveParameters = NULL;
   _SetVideoMode = NULL;
   _SetHardwareGain = NULL;
   _GetExposureRange = NULL;
   _SetExposureTime = NULL;
   LoadDLL();
}

cIdsGrabber::~cIdsGrabber()
{
   if (_GrabberDLL != NULL) {
      FreeLibrary(_GrabberDLL);
   }
}

IDS_RESULT cIdsGrabber::InitBoard(HIDS* phf, HWND hWnd)
{
   return _InitBoard(phf, hWnd);
}

IDS_RESULT cIdsGrabber::GetBoardInfo(HIDS hf, PBOARDINFO pInfo)
{
   return _GetBoardInfo(hf, pInfo);
}

IDS_RESULT cIdsGrabber::GetSensorInfo(HIDS hf, PSENSORINFO pInfo)
{
   if (_GetSensorInfo == NULL) return IS_SUCCESS;
   return _GetSensorInfo(hf, pInfo);
}

IDS_RESULT cIdsGrabber::SetDisplayMode(HIDS hf, INT Mode)
{
   return _SetDisplayMode(hf, Mode);
}

IDS_RESULT cIdsGrabber::SetImageSize(HIDS hf, INT x, INT y)
{
   return _SetImageSize(hf, x, y);
}

IDS_RESULT cIdsGrabber::SetColorMode(HIDS hf, INT Mode)
{
   return _SetColorMode(hf, Mode);
}

IDS_RESULT cIdsGrabber::AllocImageMem(HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid)
{
   return _AllocImageMem(hf, width, height, bitspixel, ppcImgMem, pid);
}

IDS_RESULT cIdsGrabber::SetImageMem(HIDS hf, char* pcMem, int id)
{
   return _SetImageMem(hf, pcMem, id);
}

IDS_RESULT cIdsGrabber::SetCaptureMode(HIDS hf, INT Mode)
{
   return _SetCaptureMode(hf, Mode);
}

IDS_RESULT cIdsGrabber::CaptureVideo(HIDS hf, INT Wait)
{
   return _CaptureVideo(hf, Wait);
}

IDS_RESULT cIdsGrabber::FreezeVideo(HIDS hf, INT Wait)
{
   return _FreezeVideo(hf, Wait);
}

IDS_RESULT cIdsGrabber::FreeImageMem(HIDS hf, char* pcMem, int id)
{
   return _FreeImageMem(hf, pcMem, id);
}

IDS_RESULT cIdsGrabber::ExitBoard(HIDS hf)
{
   return _ExitBoard(hf);
}

IDS_RESULT cIdsGrabber::GetError(HIDS hf, INT* pErr, char** ppcErr)
{
   return _GetError(hf, pErr, ppcErr);
}

IDS_RESULT cIdsGrabber::SetVideoInput(HIDS hf, INT Source)
{
   return _SetVideoInput(hf, Source);
}

IDS_RESULT cIdsGrabber::CopyImageMem(HIDS hf, char* pcSource, int nID, char* pcDest)
{
   return _CopyImageMem(hf, pcSource, nID, pcDest);
}

IDS_RESULT cIdsGrabber::SetPixelClock(HIDS hf, INT Clock)
{
   if (_SetPixelClock == NULL) return IS_SUCCESS;
   return _SetPixelClock(hf, Clock);
}

IDS_RESULT cIdsGrabber::SetFrameRate(HIDS hf, double FPS, double* newFPS)
{
   if (_SetFrameRate == NULL) return IS_SUCCESS;
   return _SetFrameRate(hf, FPS, newFPS);
}

IDS_RESULT cIdsGrabber::SetContrast(HIDS hf, INT Contrast)
{
   return _SetContrast(hf, Contrast);
}

IDS_RESULT cIdsGrabber::SetBrightness(HIDS hf, INT Brightness)
{
	return _SetBrightness(hf, Brightness);
}

IDS_RESULT cIdsGrabber::LoadParameters(HIDS hf, const TCHAR* pFilename)
{
   if (_LoadParameters == NULL) return IS_SUCCESS;
	return _LoadParameters(hf, pFilename);
}

IDS_RESULT cIdsGrabber::SaveParameters(HIDS hf, const TCHAR* pFilename)
{
   if (_SaveParameters == NULL) return IS_SUCCESS;
	return _SaveParameters(hf, pFilename);
}

IDS_RESULT cIdsGrabber::SetVideoMode(HIDS hf, INT Mode)
{
   return _SetVideoMode(hf, Mode);
}

IDS_RESULT cIdsGrabber::SetHardwareGain(HIDS hf, INT nMaster, INT nRed, INT nGreen, INT nBlue)
{
   if (_SetHardwareGain == NULL) return IS_SUCCESS;
   return _SetHardwareGain(hf, nMaster, nRed, nGreen, nBlue);
}

IDS_RESULT cIdsGrabber::GetExposureRange(HIDS hf, double *min, double *max, double *intervall)
{
   if (_GetExposureRange == NULL) return IS_SUCCESS;
   return _GetExposureRange(hf, min, max, intervall);
}

IDS_RESULT cIdsGrabber::SetExposureTime(HIDS hf, double EXP, double* newEXP)
{
   if (_SetExposureTime == NULL) return IS_SUCCESS;
   return _SetExposureTime(hf, EXP, newEXP);
}


void cIdsGrabber::LoadDLL()
{
   _GrabberDLL = LoadLibrary(_DLLName.c_str());
   if (_GrabberDLL == NULL) {
      int err = GetLastError();
      throw cError(SHARED_LIBRARY_LOAD, err, _DLLName.c_str());
   } else {
      LoadProc((void*&)_InitBoard, "is_InitBoard");
      LoadProc((void*&)_GetBoardInfo, "is_GetBoardInfo");
      LoadProc((void*&)_GetSensorInfo, "is_GetSensorInfo");
      LoadProc((void*&)_SetDisplayMode, "is_SetDisplayMode");
      LoadProc((void*&)_SetImageSize, "is_SetImageSize");
      LoadProc((void*&)_SetColorMode, "is_SetColorMode");
      LoadProc((void*&)_AllocImageMem, "is_AllocImageMem");
      LoadProc((void*&)_SetImageMem, "is_SetImageMem");
      LoadProc((void*&)_SetCaptureMode, "is_SetCaptureMode");
      LoadProc((void*&)_CaptureVideo, "is_CaptureVideo");
      LoadProc((void*&)_FreezeVideo, "is_FreezeVideo");
      LoadProc((void*&)_FreeImageMem, "is_FreeImageMem");
      LoadProc((void*&)_ExitBoard, "is_ExitBoard");
      LoadProc((void*&)_GetError, "is_GetError");
      LoadProc((void*&)_SetVideoInput, "is_SetVideoInput");
      LoadProc((void*&)_CopyImageMem, "is_CopyImageMem");
      LoadProc((void*&)_SetPixelClock, "is_SetPixelClock");
      LoadProc((void*&)_SetFrameRate, "is_SetFrameRate");
      LoadProc((void*&)_SetContrast, "is_SetContrast");
      LoadProc((void*&)_SetBrightness, "is_SetBrightness");
      LoadProc((void*&)_LoadParameters, "is_LoadParameters");
      LoadProc((void*&)_SaveParameters, "is_SaveParameters");
      LoadProc((void*&)_SetVideoMode, "is_SetVideoMode");
      LoadProc((void*&)_SetHardwareGain, "is_SetHardwareGain");
      LoadProc((void*&)_GetExposureRange, "is_GetExposureRange");
      LoadProc((void*&)_SetExposureTime, "is_SetExposureTime");
   }
}

void cIdsGrabber::LoadProc(void * & func_ptr, CONST_STRING_T func_name)
{
   func_ptr = (void*)GetProcAddress(_GrabberDLL, func_name);
   if (func_ptr == NULL) {
      if (strcmp(func_name, "is_GetSensorInfo") == 0) return;
      if (strcmp(func_name, "is_SetPixelClock") == 0) return;
      if (strcmp(func_name, "is_SetFrameRate") == 0) return;
      if (strcmp(func_name, "is_LoadParameters") == 0) return;
      if (strcmp(func_name, "is_SaveParameters") == 0) return;
      int err = GetLastError();
      throw cError(SHARED_FUNCTION_LOAD, err, _DLLName.c_str(), func_name);
   }
}

cFalcon::cFalcon()
{
   for (int i=0; i<MAX_BOARDS; i++) {
      _BoardHandles[i] = NULL;
      _VideoBuffer[i] = NULL;
   }
}

cFalcon::~cFalcon()
{
}

HIDS cFalcon::OpenHandle(cIdsGrabber * grabber, ULONG_T board_id, BOOL_T & new_handle)
{
   new_handle = false;
   if (board_id >= MAX_BOARDS) return NULL;
   if (_BoardHandles[board_id] != NULL) return _BoardHandles[board_id];
   HIDS handle = (void*)board_id;
   int ret = grabber->InitBoard(&handle, NULL);
   if (handle == NULL) {
      ret = grabber->InitBoard(&handle, NULL);
      if (handle == NULL) {
         throw cError(GRABBER_OPEN_DEVICE, 0);
      }
   }
   if (ret != IS_SUCCESS) throw cError(GRABBER_INIT_BOARD, 0);
   _BoardHandles[board_id] = handle;
   new_handle = true;
   return handle;
}

void cFalcon::SetVideoBuffer(char * buffer, ULONG_T board_id)
{
 InfoPrintf("Video Buffer %d set to %p\n", board_id, buffer);						//GH ErrorPrintf in InfoPrintf geaendert
   if (board_id < MAX_BOARDS) {
      _VideoBuffer[board_id] = buffer;
   }
}

char * cFalcon::GetVideoBuffer(ULONG_T board_id)
{
 InfoPrintf("returning Video Buffer %d %p\n", board_id, _VideoBuffer[board_id]);	//GH ErrorPrintf in InfoPrintf geaendert
   if (board_id < MAX_BOARDS) {
      return _VideoBuffer[board_id];
   } else {
      return NULL;
   }
}


cUEye::cUEye()
{
}

cUEye::~cUEye()
{
}

HIDS cUEye::OpenHandle(cIdsGrabber * grabber, ULONG_T board_id)
{
   HIDS handle = (void*)board_id;
   int ret = grabber->InitBoard(&handle, NULL);
   if (handle == NULL) {
      ret = grabber->InitBoard(&handle, NULL);
      if (handle == NULL) {
         throw cError(GRABBER_OPEN_DEVICE, 0);
      }
   }
   if (ret != IS_SUCCESS) throw cError(GRABBER_INIT_BOARD, 0);
   return handle;
}

