// ===========================================================================
// eb_osver.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cOsVersion              - Versionsinformationen
//
// ===========================================================================

#include "base/eb_osver.hpp"

#if defined __ECL_W32__
   #include <windows.h>
#elif defined __ECL_OS2__
   #include <os2.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

#endif /*__INTERFACE__*/




// Lokale Funktionen
// ===========================================================================

#if defined __ECL_W32__

   static int GetWinVer()
   {
      DWORD dwVersion = GetVersion();

      // Get the Windows version.

      DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
      //DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));

      // Get the build number for Windows NT/Windows 2000 or Win32s.

      if (dwVersion < 0x80000000) {                // Windows NT/2000
         //dwBuild = (DWORD)(HIWORD(dwVersion));
         return 2000;
      } else if (dwWindowsMajorVersion < 4) {      // Win32s
         //dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
         return 2000;
      } else {                                     // Windows 95/98 -- No build number
         //dwBuild =  0;
         return 95;
      }
   }

   int WinVer = GetWinVer(); // 95 (= Win95), 98 (= Win98/ME), 2000 (= NT4/2000/XP)

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cOsVersion
// ---------------------------------------------------------------------------
//
//  cOsVersion
//
// ===========================================================================

class __ECL_DLLEXPORT__ cOsVersion {

public:

   // Liefert true unter Win32
   static bool isW32();
   // Liefert true unter OS/2
   static bool isOS2();

   // Liefert die Version des Betriebssystems
   // W32: 95 (= Win95), 98 (= Win98/ME), 2000 (= NT4/2000/XP)
   // OS2: 20 (= V2.0), 21 (= V2.1), 23 (= Warp3), 24 (= Warp4)
   static int getVersion();

};

#endif /*__INTERFACE__*/


// Implementierung cOsVersion
// ===========================================================================

bool cOsVersion::isW32()
{
   #if defined __ECL_W32__
      return true;
   #elif defined __ECL_OS2__
      return false;
   #endif
}

bool cOsVersion::isOS2()
{
   #if defined __ECL_W32__
      return false;
   #elif defined __ECL_OS2__
      return true;
   #endif
}

int cOsVersion::getVersion()
{
   #if defined __ECL_W32__
      return WinVer;
   #elif defined __ECL_OS2__
      return 20; // ??? TBD: 
   #endif
}

