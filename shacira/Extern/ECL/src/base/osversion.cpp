// ===========================================================================
// base/osversion.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/osversion.h"

// Platform dependant headers
#if defined __ECL_W32__
   #include <windows.h>
#elif defined __ECL_OS2__
   #include <os2.h>
#endif




namespace ecl {




// Lokale Funktionen
// ===========================================================================

#if defined __ECL_W32__

   static DWORD Version = 0;
   static DWORD MajorVersion = 0;
   static DWORD MinorVersion = 0;

   static void GetWinVer()
   {
      if ( Version == 0 && MajorVersion == 0 && MinorVersion == 0 ) {
         Version      = GetVersion();
         MajorVersion = (DWORD)(LOBYTE(LOWORD(Version)));
         MinorVersion = (DWORD)(HIBYTE(LOWORD(Version)));
      }
   }

#endif




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

// Liefert true, wenn das aktuelle OS unter den angegebenen ist
// \par ver_mask Bitmaske, kombiniert die OSVERSION-Tags
bool cOsVersion::isVersion(int ver_mask)
{
   #if defined __ECL_W32__
      GetWinVer();
      if ( Version < 0x80000000 ) {         
         // Current OS is Windows NT3 or higher
         switch ( MajorVersion ) {
         case 3:  return !!(ver_mask & WNT3);
         case 4:  return !!(ver_mask & WNT4);
         case 5:  return !!(ver_mask & (W2K|WXP));
         }
      } else {
         // Current OS is Windows 95/98/ME
         // TODO: Determine OS more exactly!
         return !!(ver_mask & (W95|W98|WME));
      }
   #endif

   return false;
}

// Liefert true, wenn das aktuelle OS mindestens \a ver ist
bool cOsVersion::isVersionOrNewer(OSVERSION ver)
{
   #if defined __ECL_W32__
      GetWinVer();
      if ( Version < 0x80000000 ) {
         switch ( ver ) {
         case WNT3:  return MajorVersion >= 3;
         case WNT4:  return MajorVersion >= 4;
         case W2K:   return MajorVersion >= 5;
         case WXP:   return MajorVersion >= 5;
         }
      } else {
         // Current OS is Windows 95/98/ME
         // TODO: Determine OS more exactly!
         return true;
      }
   #endif

   return false;
}

int cOsVersion::getVersion()
{
   #if defined __ECL_W32__
      GetWinVer();
      // Get the build number for Windows NT/Windows 2000 or Win32s.
      // (for compatibility with previous ECL versions!)
      if (Version < 0x80000000) {         // Windows NT/2000
         return 2000;
      } else if (MajorVersion < 4) {      // Win32s
         return 2000;
      } else {                            // Windows 95/98 -- No build number
         return 95;
      }
   #elif defined __ECL_OS2__
      return 20; // ??? TBD: 
   #endif
}


}; // namespace ecl
