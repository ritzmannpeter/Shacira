
#include "CarItf.h"
#include "Carrier.h"
#include "stdio.h"
#include "stdarg.h"
#include <conio.h>

#define DIRECT_ACCESS   1
#define DRIVER_BASED    2

static int Access = DRIVER_BASED;
#define HW_DIRECT (Access == DIRECT_ACCESS)
static CCB * Ccb = NULL;

// driver configuration
#define SETTING_FILE       "Carrier.set"
#define SETTING_CHAPTER    "Settings"
static unsigned long PortBase = DEF_BASE_PORT;           // direct access only (Win9x and ME)
static unsigned long ForceDirectAccess = 0;              // force direct acces even if system
                                                         // is Win NT, 2000 or XP
static unsigned long SimulateHardware = DEF_SIM_FLAG;    // simulate hardware
static unsigned long Version = DEF_VERSION;
static unsigned long CheckMode = DEF_CHECK_MODE;
static unsigned long Retries = DEF_RETRIES;
static unsigned long Stability = DEF_STABILITY;
static unsigned long DelayTime = DEF_DELAY_TIME;
static unsigned long SimulatedSize = 32;

#define IOCTL_ERROR IoCtlError()

static void LogPrintf(const char * fmt_str, ... )
{
   va_list args;
   char text[1024] = {0};
   FILE * stream = NULL;
   va_start(args, fmt_str);
   vsprintf(text, fmt_str, args);
   va_end(args);
   stream = fopen("Carrier.log", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", text);
      fclose(stream);
   }
}

static long IoCtlError(void)
{
   long err = GetLastError() + 10000;
   return -err;
}

static void ReadULong(const char * file_name, const char * chapter, const char * key,
                      unsigned long * value)
{
   char cur_dir[1024] = {0};
   char file[1024] = {0};
   DWORD len = GetCurrentDirectory(sizeof(cur_dir), cur_dir);
   if (len > 0) {
      unsigned long temp_value = 0;
      char buf[512] = {0};
      sprintf(file, "%s\\%s", cur_dir, file_name);
      len = GetPrivateProfileString(chapter, key, "", buf, sizeof(buf), file);
      if (len == 0) return;
      if (strlen(buf) == 0) return;
      if (sscanf(buf, "0x%x", &temp_value) == 1) {
         *value = temp_value;
      } else if (sscanf(buf, "%d", &temp_value) == 1) {
         *value = temp_value;
      } else {
         int dummy = 0;
      }
   }
}

static void LoadSettings(void)
{
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "PortBase", &PortBase);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "ForceDirectAccess", &ForceDirectAccess);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "SimulateHardware", &SimulateHardware);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "Version", &Version);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "CheckMode", &CheckMode);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "Retries", &Retries);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "Stability", &Stability);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "DelayTime", &DelayTime);
   ReadULong(SETTING_FILE, SETTING_CHAPTER, "SimulatedSize", &SimulatedSize);
   if (ForceDirectAccess > 0) Access = DIRECT_ACCESS;
}

static void SetSettings(HANDLE hnd)
{
   if (hnd != INVALID_HANDLE_VALUE) {
      if (Version <= HW_VERSIONS) {
         CARITF_SetParam(hnd, "VERSION", Version);
      } else {
         LogPrintf("Invalid value %d in parameter Version\n", Version);
      }
      if (CheckMode <= 1) {
         CARITF_SetParam(hnd, "CHECK_MODE", CheckMode);
      } else {
         LogPrintf("Invalid value %d in parameter CheckMode\n", CheckMode);
      }
      CARITF_SetParam(hnd, "RETRIES", Retries);
      CARITF_SetParam(hnd, "STABILITY", Stability);
      CARITF_SetParam(hnd, "DELAY_TIME", DelayTime);
      if (SimulateHardware <= 1) {
         CARITF_SetParam(hnd, "SIMULATE_HARDWARE", SimulateHardware);
      } else {
         LogPrintf("Invalid value %d in parameter SimulateHardware\n", SimulateHardware);
      }
      if (SimulatedSize == 4 ||
		  SimulatedSize == 8 ||
		  SimulatedSize == 32) {
         CARITF_SetParam(hnd, "SIMULATED_SIZE", SimulatedSize);
      } else {
         LogPrintf("Invalid value %d in parameter SimulatedSize\n", SimulatedSize);
      }
   }
}

#define USER_MODE_SYSTEM   1
#define WIN9X_COMPATIBLE   2
static int BaseSystem(void)
{
static int base_system = 0;
   if (base_system == 0) {
      OSVERSIONINFO osvi;
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&osvi);
      if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
         base_system = USER_MODE_SYSTEM;
      } else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
         base_system = WIN9X_COMPATIBLE;
      }
   }
   return base_system;
}

char * CarrierName(void)
{
   if (BaseSystem() == USER_MODE_SYSTEM) {
      return CARRIER_DEVICE;
   } else {
      return CARRIER_VXD;
   }
}

static int HardwareAccess(void)
{
   if (BaseSystem() == USER_MODE_SYSTEM) {
      return DRIVER_BASED;
   } else {
      return DIRECT_ACCESS;
   }
}

static HANDLE CarrierOpen(LPCSTR lpCStrDevice)
{
   HANDLE hnd;
   hnd = CreateFile(
                 lpCStrDevice, 
                 GENERIC_READ|GENERIC_WRITE,
                 FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   return hnd;
}

static void CarrierClose(HANDLE hnd)
{
   if (hnd != INVALID_HANDLE_VALUE) CloseHandle(hnd);
   hnd = INVALID_HANDLE_VALUE;
}

static long CarrierGetLastError(HANDLE hnd, long result, long error)
{
   long _result = 0;
   long _error = 0;
   if (result == 0) {
      CARRIER_CTL_STRUCT carctl = {0};
      if (DeviceIoControl(hnd, IOCTL_CARRIER_GET_LAST_ERROR, 
                        (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                        (LPVOID)&_error, sizeof(_error),
                        &_result, NULL)) {
         return _error;
      } else {
         return IOCTL_ERROR;
      }
   } else {
      return error;
   }
}

static long CarrierCheck(HANDLE hnd)
{
   long result = 0;
   long size = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   if (DeviceIoControl(hnd, IOCTL_CARRIER_CHECK, 
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       (LPVOID)&size, sizeof(size),
                       &result, NULL)) {
      return CarrierGetLastError(hnd, result, size);
   } else {
      return IOCTL_ERROR;
   }
}

static unsigned long CarrierSeek(HANDLE hnd, unsigned long seek_pos)
{
   long result = 0;
   unsigned long returned_pos = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   carctl.Long1 = seek_pos;
   if (DeviceIoControl(hnd, IOCTL_CARRIER_SEEK, 
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       &returned_pos, sizeof(returned_pos),
                       &result, NULL)) {
      return CarrierGetLastError(hnd, result, 0);
   } else {
      return IOCTL_ERROR;
   }
}

static long CarrierRead(HANDLE hnd, unsigned long address,
                        unsigned char * buf, unsigned long bufsize,
                        unsigned long amount)
{
   long result = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   carctl.Long1 = address;
   carctl.Long2 = amount;
   if (DeviceIoControl(hnd, IOCTL_CARRIER_READ, 
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       (LPVOID)buf, bufsize,
                       &result, NULL)) {
      return CarrierGetLastError(hnd, result, result);
   } else {
      return IOCTL_ERROR;
   }
}

static long CarrierWrite(HANDLE hnd, unsigned long address,
                         unsigned char * buf, unsigned long amount)
{
   long result = 0;
   long state = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   carctl.Long1 = address;
   carctl.Long2 = amount;
   carctl.pByte = buf;
   if (DeviceIoControl(hnd, IOCTL_CARRIER_WRITE,
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       &state, sizeof(state),
                       &result, NULL)) {
      return CarrierGetLastError(hnd, result, state);
   } else {
      return IOCTL_ERROR;
   }
}

static long CarrierGetParam(HANDLE hnd, const char * param_name, long * value)
{
   long result = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   carctl.pByte = (char*)param_name;
   if (DeviceIoControl(hnd, IOCTL_CARRIER_GET_PARAM,
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       (LPVOID)value, sizeof(*value),
                       &result, NULL)) {
      long rc = CarrierGetLastError(hnd, result, 0);
      if (rc != 0) LogPrintf("Failed to get parameter %s: %d\n", param_name, rc);
      return rc;
   } else {
      return IOCTL_ERROR;
   }
}

static long CarrierSetParam(HANDLE hnd, const char * param_name, long value)
{
   long result = 0;
   long state = 0;
   CARRIER_CTL_STRUCT carctl = {0};
   carctl.pByte = (char*)param_name;
   carctl.Long1 = value;
   if (DeviceIoControl(hnd, IOCTL_CARRIER_SET_PARAM,
                       (LPVOID)&carctl, sizeof(CARRIER_CTL_STRUCT),
                       &state, sizeof(state),
                       &result, NULL)) {
      long rc = CarrierGetLastError(hnd, result, 0);
      if (rc != 0) LogPrintf("Failed to set parameter %s: %d\n", param_name, rc);
      return rc;
   } else {
      return IOCTL_ERROR;
   }
}

HANDLE CARITF_Open(void)
{
   Access = HardwareAccess();
   LoadSettings();
   if (HW_DIRECT) {
      if (Ccb == NULL) Ccb = CARRIER_Init(NULL, PortBase);
      if (Ccb == NULL) return INVALID_HANDLE_VALUE;
      SetSettings(0);
      return 0;
   } else {
      char * device_name = CarrierName();
      HANDLE hnd = CreateFile(device_name,
                              GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      SetSettings(hnd);
      return hnd;
   }
}

void CARITF_Close(HANDLE hnd)
{
   if (HW_DIRECT) {
      return;
   } else {
      if (hnd != INVALID_HANDLE_VALUE) CloseHandle(hnd);
   }
}

long CARITF_SetParam(HANDLE hnd, const char * param_name, long param_value)
{
   long rc = 0;
   if (HW_DIRECT) {
      if (Ccb == NULL) {
         return CARITF_DEVICE_NOT_INITIALIZED;
      } else {
         rc = CARRIER_SetParam(Ccb, param_name, param_value);
         if (rc == 0) {
            printf("Parameter %s set to %d\n", param_name, param_value);
         } else {
            printf("Failed to set parameter %s to %d: %d\n", param_name, param_value, rc);
         }
         return rc;
      }
   } else {
      if (hnd == INVALID_HANDLE_VALUE) {
         return CARITF_DEVICE_NOT_OPEN;
      } else {
         rc = CarrierSetParam(hnd, param_name, param_value);
         if (rc == 0) {
            printf("Parameter %s set to %d\n", param_name, param_value);
         } else {
            printf("Failed to set parameter %s to %d: %d\n", param_name, param_value, rc);
         }
         return rc;
      }
   }
}

long CARITF_GetParam(HANDLE hnd, const char * param_name, long * param_value)
{
   if (HW_DIRECT) {
      if (Ccb == NULL) {
         return CARITF_DEVICE_NOT_INITIALIZED;
      } else {
         return CARRIER_GetParam(Ccb, param_name, param_value);
      }
   } else {
      if (hnd == INVALID_HANDLE_VALUE) {
         return CARITF_DEVICE_NOT_OPEN;
      } else {
         return CarrierGetParam(hnd, param_name, param_value);
      }
   }
}

long CARITF_Check(HANDLE hnd)
{
   if (HW_DIRECT) {
      if (Ccb == NULL) {
         return CARITF_DEVICE_NOT_INITIALIZED;
      } else {
         return CARRIER_Check(Ccb);
      }
   } else {
      if (hnd == INVALID_HANDLE_VALUE) {
         return CARITF_DEVICE_NOT_OPEN;
      } else {
         return CarrierCheck(hnd);
      }
   }
}

long CARITF_Read(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long bufsize, unsigned long amount)
{
   if (HW_DIRECT) {
      if (Ccb == NULL) {
         return CARITF_DEVICE_NOT_INITIALIZED;
      } else {
		  return CARRIER_Read(Ccb, address, buf, bufsize, amount);
      }
   } else {
      if (hnd == INVALID_HANDLE_VALUE)  {
         return CARITF_DEVICE_NOT_OPEN;
      } else {
         return CarrierRead(hnd, address, buf, bufsize, amount);
      }
   }
}

long CARITF_Write(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long amount)
{
   if (HW_DIRECT) {
      if (Ccb == NULL) {
         return CARITF_DEVICE_NOT_INITIALIZED;
      } else {
         return CARRIER_Write(Ccb, address, buf, amount);
      }
   } else {
      if (hnd == INVALID_HANDLE_VALUE) {
         return CARITF_DEVICE_NOT_OPEN;
      } else {
         return CarrierWrite(hnd, address, buf, amount);
      }
   }
}

// implementation of direct access hardware
// and wait functions

void Wait(unsigned long ms)
{
   Sleep(ms);
}

unsigned char Inport(unsigned short port)
{
   if (BaseSystem() == USER_MODE_SYSTEM) {
      return 0xff;
   } else {
#if defined(__BORLANDC__)
//return 0x77;
      return _inp(port);
#else
      return _inp(port);
#endif
   }
}

void Outport(unsigned short port, unsigned char value)
{
   if (BaseSystem() != USER_MODE_SYSTEM) {
#if defined(__BORLANDC__)
      _outp(port, value);
#else
      _outp(port, value);
#endif
   }
}

