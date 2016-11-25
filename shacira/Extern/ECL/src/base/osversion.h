// ===========================================================================
// base/osversion.h                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cOsVersion              - Versionsinformationen
//
// ===========================================================================

#ifndef __ecl_osversion__
#define __ecl_osversion__


// Other ECL headers
#include "base/base.h"

             
namespace ecl {


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

   enum OSVERSION {
      W95   = 0x00000100,     // Windows 95
      W98   = 0x00000200,     // Windows 98
      WME   = 0x00000400,     // Windows ME
      WNT3  = 0x00000800,     // Windows NT4
      WNT4  = 0x00001000,     // Windows NT4
      W2K   = 0x00002000,     // Windows 2000
      WXP   = 0x00004000      // Windows XP
   };

   // Liefert true, wenn das aktuelle OS unter den angegebenen ist
   // \par ver_mask Bitmaske, kombiniert die OSVERSION-Tags
   static bool isVersion(int ver_mask);

   // Liefert true, wenn das aktuelle OS mindestens \a ver ist
   static bool isVersionOrNewer(OSVERSION ver);

   // Obsolete: Liefert die Version des Betriebssystems
   // W32: 95 (= Win95), 98 (= Win98/ME), 2000 (= NT4/2000/XP)
   // OS2: 20 (= V2.0), 21 (= V2.1), 23 (= Warp3), 24 (= Warp4)
   static int getVersion();

};


}; // namespace ecl


#endif // __ecl_osversion__

