
#include "system.h"
#include <windows.h>
#include <shlobj.h>

int getCurrentThreadId()
{
   return (int)GetCurrentThreadId();
}

unsigned long realtimeOffset()
{
   unsigned long ticks = GetTickCount();
   return ticks;
}

#ifdef doku

static bool unicodeToAnsi(LPWSTR unicodeString, LPSTR buffer, DWORD bufferSize)
{
   int rc = WideCharToMultiByte(CP_ACP, 0, unicodeString, -1, buffer, bufferSize, NULL, NULL);
   return (0 != rc);
}

static bool ansiToUnicode(LPSTR ansiString, LPWSTR buffer, DWORD bufferSize)
{
   int rc = MultiByteToWideChar(CP_ACP, 0, ansiString, -1, buffer, bufferSize);
   return (0 != rc);
}

#endif

static TCHAR * multi(const char * s)
{
   if (sizeof(TCHAR) == sizeof(char)) {
      return (TCHAR*)s;
   } else {
      int bufferSize = (int)strlen(s) + 1;
      wchar_t * wideBuffer = new wchar_t[bufferSize];
      MultiByteToWideChar(CP_ACP, 0, s, -1, wideBuffer, bufferSize);
      LPWSTR wideString = SysAllocString(wideBuffer);
      delete wideBuffer;
      return (TCHAR*)wideString;
   }
}

static string ansi(TCHAR * s)
{
   if (sizeof(TCHAR) == sizeof(char)) {
      return string((char*)s);
   } else {
      string str;
      int bufferSize = (int)wcslen((wchar_t*)s) + 1;
      char * buffer = new char(bufferSize);
      WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)s, -1, buffer, bufferSize, NULL, NULL);
      str = buffer;
      delete buffer;
      return str;
   }
}

#if (_MSC_VER >= 1300)

bool getAppDataDir(string & directory)
{
   TCHAR path[MAX_PATH];
   HRESULT rc = SHGetFolderPath(NULL, 
                                CSIDL_APPDATA|CSIDL_FLAG_CREATE, 
                                NULL, 0, path);
   if (SUCCEEDED(rc)) {
      directory = ansi(path);
      return true;
   } else {
      return false;
   }
}

#endif

bool getCurrentWorkingDirectory(string & directory)
{
   TCHAR path[MAX_PATH];
   DWORD rc = GetCurrentDirectory(MAX_PATH, path);
   if (rc > 0) {
      directory = ansi(path);
      return true;
   } else {
      return false;
   }
}

bool setCurrentWorkingDirectory(string & directory)
{
   if(SetCurrentDirectory(multi(directory.c_str()))) {
      string currentDirectory;
      if (getCurrentWorkingDirectory(currentDirectory)) {
         if (directory == currentDirectory) {
            return true;
         }
      }
      return true;
   }
   return false;
}

