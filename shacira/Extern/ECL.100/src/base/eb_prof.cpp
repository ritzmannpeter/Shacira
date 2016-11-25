// ===========================================================================
// eb_prof.cpp                                  ETCL (ET's Tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cProfile             - Zugriff auf Profiles.
//
// Zum Zugriff auf Profiles wird ein Applikationspfad (app_path) und ein
// Schlüsselname (key) verwendet. Fuer klassischen INI-File-Zugriff degene-
// riert der Applikationspfad zu einem einfachen Bezeichner, fuer moderneren
// Registry-Zugriff kann es ein hierarchischer Name sein, der analog zu den
// Pfadnamen im Dateisystem aufgebaut ist.
//
// Beispiele:
//
//  - Zugriff auf ein "klassisches" INI-File (PRF_PRIVATE):
//
//       cProfile profile("TEST.INI");
//       cString value = profile.read("Application", "Key", "DefaultValue");
//       profile.write("Application", "Key", value);
//
//  - Zugriff auf eine strukturierte Registry (PRF_PUBLIC):
//
//       cProfile profile;
//       cString app_path = "HKEY_LOCAL_MACHINE/SOFTWARE/Microsoft/DrWatson";
//       cString value = profile.read(app_path, "WaveFile", "DefaultValue");
//       profile.write(app_path, "WaveFile", value);
//
//  - Zugriff auf den aktuellen User-Bereich (PRF_CURUSR):
//
//       cProfile profile(":USR:Sirius Corp/Nutrimat");
//       cString app_path = "Drink/Tea";
//       long value = profile.read(app_path, "HotWater", 1);
//       profile.write(app_path, "HotWater", value);
//
//       Besonderheiten:
//        - read() sucht in dieser Reihenfolge unter folgenden Pfaden nach
//          dem Wert "HotWater" (falls in keinem dieser Pfade gefunden, wird
//          der Defaultwert zurueckgegeben):
//           1. HKEY_CURRENT_USER/Software/Sirius Corp/Nutrimat/Drink/Tea
//           2. HKEY_LOCAL_MACHINE/SOFTWARE/Sirius Corp/Nutrimat/Drink/Tea
//        - write() schreibt nur im CURRENT_USER-Zweig
//
// ===========================================================================

#include "base/eb_prof.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stdarg.h>

#if defined(__ECL_OS2__)
   #include <os2.h>
#elif defined(__ECL_W32__) || defined(__ECL_W16__)
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

#if defined __ECL_W32__ || defined __ECL_W16__

   // Uneingeschraenkter Zugriff auf gesamte Registry. Zum Oeffnen des
   // Profiles die zweite open()-Variante (ohne prf_name) verwenden.
   #define PRF_PUBLIC   1

   // Zugriff auf ein privates .INI-File, dessen Name bei Open (prf_name)
   // angegeben wurde. Es stehen keine Applikationspfade zur Verfuegung.
   #define PRF_PRIVATE  2

   // Zugriff auf die Daten des aktuellen Benutzers. Beim Lesen wird, sofern
   // ein gesuchter Applikationspfad und/oder Schlüssel nicht gefunden wurde,
   // zusätzlich automatisch der entsprechende Eintrag im globalen Profile
   // gesucht. Zum Oeffnen in diesem Modus muss der Parameter prf_name den
   // folgenden Aufbau haben: ":USR:<Company>/<Application>"
   #define PRF_CURUSR   3

#endif




// Lokale Funktionen
// ===========================================================================

#if defined __ECL_OS2__

   static bool Reopen(USHORT& err)
   {
      err = ERRORIDERROR(WinGetLastError(hab));
      if (!hini || hini == HINI_PROFILE || err != PMERR_INVALID_INI_FILE_HANDLE)
         return FALSE;

      hini = PrfOpenProfile(hab,name);
      cBase::DbgTrace("cProfile: Reopen of '%s' %s", (const char *)name, (hini ? "successful" : "failed" ));

      return hini != NULLHANDLE;
   }

#elif defined __ECL_W32__

   static void ReplaceSlashes(cString& str, char with)
   {
      int pos;
      while ( (pos = str.getPos("/")) >= 0 )
         str[pos] = with;
   }

   static HKEY AdaptAppPath(cString& app_path, int prf_mode)
   {
      if ( prf_mode == PRF_PRIVATE ) {

         ReplaceSlashes(app_path, '_');
         return 0;

      } else {

         ReplaceSlashes(app_path, '\\');

         if ( app_path.compareNoCase("HKEY_CLASSES_ROOT\\", 18) == 0 ) {
            app_path = app_path.getMid(18);
            return HKEY_CLASSES_ROOT;
         } else if ( app_path.compareNoCase("HKEY_CURRENT_CONFIG\\", 20) == 0 ) {
            app_path = app_path.getMid(20);
            return HKEY_CURRENT_CONFIG;
         } else if ( app_path.compareNoCase("HKEY_CURRENT_USER\\", 18) == 0 ) {
            app_path = app_path.getMid(18);
            return HKEY_CURRENT_USER;
         } else if ( app_path.compareNoCase("HKEY_LOCAL_MACHINE\\", 19) == 0 ) {
            app_path = app_path.getMid(19);
            return HKEY_LOCAL_MACHINE;
         } else if ( app_path.compareNoCase("HKEY_USERS\\", 11) == 0 ) {
            app_path = app_path.getMid(11);
            return HKEY_USERS;
         } else if ( app_path.compareNoCase("HKEY_PERFORMANCE_DATA\\", 22) == 0 ) {
            app_path = app_path.getMid(22);
            return HKEY_PERFORMANCE_DATA;
         } else if ( app_path.compareNoCase("HKEY_DYN_DATA\\", 14) == 0 ) {
            app_path = app_path.getMid(14);
            return HKEY_DYN_DATA;
         }

         return 0;

      }
   }

   static DWORD MyRegOpenKeyEx(EBHDL prf_hdl, cString app_path, cString prf_name, HKEY& hkey)
   {
      cString real_app_path = prf_hdl == PRF_CURUSR ?
         "HKEY_CURRENT_USER/Software/" + prf_name + "/" + app_path
       : app_path;

      HKEY hkey_parent = AdaptAppPath(real_app_path, prf_hdl);

      LONG err = RegOpenKeyEx(
         hkey_parent,                  // hKey
         real_app_path,                // lpSubKey
         0,                            // ulOptions
         KEY_QUERY_VALUE,              // samDesired
         &hkey                         // phkResult
      );

      if ( err != ERROR_SUCCESS && prf_hdl == PRF_CURUSR ) {
         real_app_path = "HKEY_LOCAL_MACHINE/SOFTWARE/" + prf_name + "/" + app_path;
         err = RegOpenKeyEx(hkey_parent, real_app_path, 0, KEY_QUERY_VALUE, &hkey);
      }

      return err;
   }

   static DWORD MyRegCreateKeyEx(EBHDL prf_hdl, cString app_path, cString prf_name, HKEY& hkey)
   {
      cString real_app_path = prf_hdl == PRF_CURUSR ?
         "HKEY_CURRENT_USER/Software/" + prf_name + "/" + app_path
       : app_path;

      HKEY hkey_parent = AdaptAppPath(real_app_path, prf_hdl);

      LONG err = RegCreateKeyEx(
         hkey_parent,                  // hKey
         real_app_path,                // lpSubKey
         0,                            // Reserved
         NULL,                         // lpClass
         REG_OPTION_NON_VOLATILE,      // dwOptions
         KEY_SET_VALUE,                // samDesired
         NULL,                         // lpSecurityAttributes
         &hkey,                        // phkResult
         NULL                          // lpdwDisposition
      );

      return err;
   }

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cProfile
// ---------------------------------------------------------------------------
//
// cBase
//  +--cProfile
//
// Anmerkungen:
//  - Die Funktionen getAppList() und getKeyList() benutzen das Windows-API
//    und arbeiten mit einem zwar grossen, aber begrenzten Puffer. Bei Mehr-
//    bedarf muessen diese Funktionen neu implementiert werden.
//  - Binaerdaten werden unter __ECL_W32__ (bis jetzt) nicht unterstuetzt!
//  - Ab heute (18.08.2001) schon! Aber nur fuer benannte Profiles!
//  - getAppList() und getKeyList() (bis jetzt) nicht unter __ECL_OS2__!
//
// ===========================================================================

class __ECL_DLLEXPORT__ cProfile : public cBase {

public:

   // Konstruktor
   cProfile(cString prf_name = 0, cString def_app_path = 0);
   // Destruktor
   ~cProfile();


   // Oeffnen, Schliessen
   // ===================

   // Profile oeffnen (im Modus PRIVATE oder CURUSR)
   bool open(cString prf_name, cString def_app_path);
   // Profile oeffnen (im Modus PUBLIC)
   bool open(cString def_app_path = 0);
   // Profile schliessen
   void close();


   // Lesen
   // =====

   // Pruefen, ob ein Eintrag in der vorhanden ist
   // - falls key nicht angegeben, pruefen ob Applikation vorhanden ist
   // - falls app_path und key nicht angegeben, pruefen ob INI-Datei vorhanden ist
   bool exist(cString app_path = 0, cString key = 0) const;

   // Binaere Daten einlesen
   size_t read(cString app_path, cString key, void *data, size_t size) const;
   // Zeichenkette einlesen
   cString read(cString app_path, cString key, cString def_val = 0) const;
   // Zahl einlesen
   long read(cString app_path, cString key, long def_val) const;


   // Schreiben
   // =========

   // Binaere Daten schreiben, liefert false bei Misserfolg
   bool write(cString app_path, cString key, void *data, size_t size) const;
   // Zeichenkette schreiben, liefert false bei Misserfolg
   // - falls data nicht angegeben, wird der key geloescht
   // - falls data und key fehlt, wird die gesamte Applikation geloescht
   bool write(cString app_path, cString key = 0, cString data = 0) const;
   // Zahl schreiaben, liefert false bei Misserfolg
   bool write(cString app_path, cString key, long data) const;


   // Applikations- und Keyliste
   // ==========================

   class ITERATOR {
      friend class cProfile;
      char *pos;
      char *buf;
      int len;
   public:
      ITERATOR() { buf = pos = NULL; len = 0;}
      ~ITERATOR() { if (buf) free(buf); }
      void alloc(int s) { if (!buf) buf = (char*)malloc(len=s); }
   };

   // Applikationsliste laden, liefert false falls Funktion nicht verfuegbar
   bool getAppList(ITERATOR &it);
   // Keyliste laden, liefert false falls Funktion nicht verfuegbar
   bool getKeyList(ITERATOR &it, cString app_path);
   // Iteration der Liste wieder auf Startwert
   void resetList(ITERATOR &it) { it.pos = it.buf; }
   // Naechsten Namen holen, leere Zeichenkette beim Ende
   cString getNext(ITERATOR &it);

   // cProfile::ITERATOR it;
   // cString app_path;
   // getAppList(it);
   // while ((app_path=getNext(it)).Length()) { ... }


private:

   enum {
      buf_size = 1024,     // maximale Laenge einer Zeile
      dir_size = 0x7FFF    // Puffergroesse fuer Applikations/Keyliste
   };

   EBHDL anchor_hdl, prf_hdl;
   cString prf_name, def_app_path;

};

#endif /*__INTERFACE__*/


// Implementierung cProfile
// ===========================================================================

cProfile::cProfile(cString prf_name, cString def_app_path)
{
   cProfile::anchor_hdl = 0;
   cProfile::prf_hdl = 0;

   open(prf_name, def_app_path);
}

cProfile::~cProfile()
{
   close();
}


// Oeffnen, Schliessen
// ===================

bool cProfile::open(cString _prf_name, cString _def_app_path)
{
   //if ( __ECL_ASSERT1__(prf_hdl != 0) )
   //   return false;

   if ( !_def_app_path.isEmpty() )
      def_app_path = _def_app_path;

   #if defined(__ECL_OS2__)

      if ( _prf_name.isEmpty() ) {
         prf_hdl = (EBHDL)HINI_PROFILE;
      } else {
         prf_name = _prf_name;
         if ( prf_name.getLocase().getPos(".ini") < 0 )
            prf_name += ".ini";
         prf_hdl = (EBHDL)PrfOpenProfile((HAB)anchor_hdl, prf_name);
      }

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( _prf_name.isEmpty() ) {
         prf_hdl = PRF_PUBLIC;
         prf_name.clear();
      } else if ( _prf_name.compareNoCase(":USR:", 5) == 0 ) {
         prf_hdl = PRF_CURUSR;
         prf_name = _prf_name.getMid(5);
      } else {
         prf_hdl = PRF_PRIVATE;
         prf_name = _prf_name;
         if ( prf_name.getPosNoCase(".INI") < 0 )
            prf_name += ".ini";
      }

   #endif

   return __ECL_ASSERT1__(prf_hdl != 0);
}

bool cProfile::open(cString def_app_path)
{
   return open(0, def_app_path);
}

void cProfile::close()
{
   #if defined(__ECL_OS2__)

      if ( prf_hdl ) {
         if ( (HINI)prf_hdl != HINI_PROFILE )
            PrfCloseProfile((HINI)prf_hdl);
      }

   #endif

   prf_hdl = 0;
}


// Lesen
// =====

bool cProfile::exist(cString app, cString key) const
{
   if ( !prf_hdl ) { return false; }

   char data[10];
   const char *app_ptr = app.isEmpty() ? 0 : (const char *)app;
   const char *key_ptr = key.isEmpty() ? 0 : (const char *)key;

   if ( app.isEmpty() ) { app = def_app_path; }

   size_t len = 0;

   #if defined(__ECL_OS2__)

      len = PrfQueryProfileString((HINI)prf_hdl, app, key, def_val, data, sizeof(data));

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {
         len = GetPrivateProfileString(app_ptr, key_ptr, "", data, sizeof(data), prf_name);
      } else {
         len = GetProfileString(app_ptr, key_ptr, "", data, sizeof(data));
      }

   #endif

   return len > 0;
}


size_t cProfile::read(cString app_path, cString key, void *data, size_t size) const
{
   //## Rueckgabewert bei Fehler stimmt nicht immer !?!

   if ( !prf_hdl )
      return (unsigned)-1;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   #if defined(__ECL_OS2__)

      USHORT err = 0;

      if ( !PrfQueryProfileData((HINI)prf_hdl, app_path, key, data, (PULONG)&size) &&
           (!Reopen(err) ||
            !PrfQueryProfileData(hini, app_path, key, data, (PULONG)&size)) ) {
         if( err && err != PMERR_NOT_IN_IDX)
            DbgError( "cProfile: Read returned error %X", err );
         return -1;
      }

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {

         AdaptAppPath(app_path, PRF_PRIVATE);
         if ( !GetPrivateProfileStruct(app_path, key, data, size, prf_name) )
            size = 0;

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = size;

         if ( (err = MyRegOpenKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegQueryValueEx(hkey, key, NULL, NULL, (LPBYTE)data, &cb_data);
            RegCloseKey(hkey);
         }

         size = err == ERROR_SUCCESS ? cb_data : 0;

      }

   #endif

   return size;
}

cString cProfile::read(cString app_path, cString key, cString def_val) const
{
   if ( !prf_hdl )
      return def_val;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   char data[buf_size];
   size_t len = sizeof data;

   #if defined(__ECL_OS2__)

      len = PrfQueryProfileString((HINI)prf_hdl, app_path, key, def_val, data, sizeof(data));

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {

         AdaptAppPath(app_path, PRF_PRIVATE);
         len = GetPrivateProfileString(app_path, key, def_val, data, sizeof(data), prf_name);

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = len;

         if ( (err = MyRegOpenKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegQueryValueEx(hkey, key, NULL, NULL, (LPBYTE)data, &cb_data);
            RegCloseKey(hkey);
         }

         if ( err != ERROR_SUCCESS )
            return def_val;

         if ( (len = cb_data) > 0 )
            data[len - 1] = '\0';

      }

   #endif

   if ( len <= 0 )
      data[0] = '\0';

   return data;
}

long cProfile::read(cString app_path, cString key, long def_val) const
{
   if ( !prf_hdl )
      return def_val;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   #if defined(__ECL_OS2__)

      return PrfQueryProfileInt((HINI)prf_hdl, app_path, key, def_val);

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      char data[20];
      size_t len = sizeof data;

      if ( prf_hdl == PRF_PRIVATE ) {

         AdaptAppPath(app_path, PRF_PRIVATE);
         len = GetPrivateProfileString(app_path, key, "", data, sizeof data, prf_name);

         if ( len > 0 ) {
            char *end;
            long value = strtol(data, &end, 0);
            if ( end != data )
               return value;
         }

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = len;

         if ( (err = MyRegOpenKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegQueryValueEx(hkey, key, NULL, NULL, (LPBYTE)data, &cb_data);
            RegCloseKey(hkey);
         }

         if ( err == ERROR_SUCCESS || cb_data == sizeof(DWORD) )
            return (long)(*((DWORD*)data));

      }

   #endif

   return def_val;
}


// Schreiben
// =========

bool cProfile::write(cString app_path, cString key, void *data, size_t size) const
{
   if ( !prf_hdl )
      return false;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   #if defined(__ECL_OS2__)

      USHORT err = 0;

      if ( !PrfWriteProfileData((HINI)prf_hdl, app_path, key, data, size) &&
           (!Reopen(err) ||
            !PrfWriteProfileData(hini, app_path, key, data, size)) ) {
         if( err ) DbgError( "cProfile: Write returned error %X", err );
      } else {
         return true;
      }

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {

         AdaptAppPath(app_path, PRF_PRIVATE);
         if ( WritePrivateProfileStruct(app_path, key, data, size, prf_name) )
            return true;

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = size;

         if ( (err = MyRegCreateKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegSetValueEx(hkey, key, NULL, REG_BINARY, (LPBYTE)data, cb_data);
            RegCloseKey(hkey);
         }

         return __ECL_ASSERT1__(err == ERROR_SUCCESS);

      }

   #endif

   return false;
}

bool cProfile::write(cString app_path, cString key, cString data) const
{
   if ( !prf_hdl )
      return false;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   #if defined(__ECL_OS2__)

      return PrfWriteProfileString((HINI)prf_hdl, app_path, key, data);

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {

         const char *key_ptr = key.isEmpty() ? 0 : (const char *)key;
         const char *data_ptr = data.isEmpty() ? 0 : (const char *)data;

         AdaptAppPath(app_path, PRF_PRIVATE);
         WritePrivateProfileString(app_path, key_ptr, data_ptr, prf_name);

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = data.getLength() + 1;
         const char *str = data;

         if ( (err = MyRegCreateKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegSetValueEx(hkey, key, NULL, REG_SZ, (LPBYTE)str, cb_data);
            RegCloseKey(hkey);
         }

         return __ECL_ASSERT1__(err == ERROR_SUCCESS);

      }

   #endif

   return true;
}

bool cProfile::write(cString app_path, cString key, long data) const
{
   if ( !prf_hdl )
      return false;

   if ( app_path.isEmpty() )
      app_path = def_app_path;

   char buf[20];
   sprintf(buf, "%ld", data);

   #if defined(__ECL_OS2__)

      return PrfWriteProfileString((HINI)prf_hdl, app_path, key, buf);

   #elif defined(__ECL_W32__) || defined(__ECL_W16__)

      if ( prf_hdl == PRF_PRIVATE ) {

         AdaptAppPath(app_path, PRF_PRIVATE);
         WritePrivateProfileString(app_path, key, buf, prf_name);

      } else {

         HKEY hkey; LONG err;
         DWORD cb_data = sizeof data;

         if ( (err = MyRegCreateKeyEx(prf_hdl, app_path, prf_name, hkey)) == ERROR_SUCCESS ) {
            err = RegSetValueEx(hkey, key, NULL, REG_DWORD, (LPBYTE)&data, cb_data);
            RegCloseKey(hkey);
         }

         return __ECL_ASSERT1__(err == ERROR_SUCCESS);

      }

   #endif

   return true;
}


// Applikations- und Keyliste
// ==========================

bool cProfile::getAppList(ITERATOR &it)
{
   #if defined(__ECL_W32__)

   it.alloc(dir_size);
   // Es wird z.Zt. nicht geprueft, ob der Puffer zu klein ist !!!
   if ( prf_hdl == PRF_PRIVATE ) {
      GetPrivateProfileString(NULL, "", "", it.buf, it.len, prf_name);
   } else {
      GetProfileString(NULL, "", "", it.buf, it.len);
   }
   it.pos = it.buf;
   return true;

   #else

   return false;

   #endif
}

bool cProfile::getKeyList(ITERATOR &it,cString app)
{
   #if defined(__ECL_W32__)

   it.alloc(dir_size);
   // Es wird z.Zt. nicht geprueft, ob der Puffer zu klein ist !!!
   if ( prf_hdl == PRF_PRIVATE ) {
      GetPrivateProfileString(app, NULL, "", it.buf, it.len, prf_name);
   } else {
      GetProfileString(app, NULL, "", it.buf, it.len);
   }
   it.pos = it.buf;
   return true;

   #else

   return false;

   #endif
}

cString cProfile::getNext(ITERATOR &it)
{
   cString result;

   if (it.pos && *it.pos != '\0') {
      result = it.pos;
      it.pos += strlen(it.pos)+1;
   };

   return result;
}


