//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "cWinSystem.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

cWinSystem::cWinSystem()
   : _SystemType(UNDEFINED_SYSTEM)
{
   _VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   GetVersionEx(&_VersionInfo);
   if (_VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
      if (_VersionInfo.dwMajorVersion == 4) {
         _SystemType = WIN_NT;
      } else if (_VersionInfo.dwMajorVersion == 5){
         if (_VersionInfo.dwMinorVersion == 0) {
            _SystemType = WIN_2K;
         } else if (_VersionInfo.dwMinorVersion == 1) {
            _SystemType = WIN_XP;
         }
      }
   } else if (_VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
      _SystemType = WIN_95;
   }
   memset(_SystemDirectory, 0, sizeof(_SystemDirectory));
   int rc = GetSystemDirectory(_SystemDirectory, sizeof(_SystemDirectory));
}

cWinSystem::~cWinSystem()
{
}

int cWinSystem::SystemType()
{
   return _SystemType;
}

OSVERSIONINFO * cWinSystem::VersionInfo()
{
   return &_VersionInfo;
}

const char * cWinSystem::SystemDirectory()
{
   return _SystemDirectory;
}


