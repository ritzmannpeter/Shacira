// ===========================================================================
// base/profile.h                                               ______ /  ECL
// Autor: Thomas Epting, Urautor: Markus Wuertz                /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cProfile - Zugriff auf Profiles.
//
// Zum Zugriff auf Profiles wird ein Applikationspfad (app_path) und ein
// Schluesselname (key) verwendet. Fuer klassischen INI-File-Zugriff degene-
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

#ifndef __ecl_profile__
#define __ecl_profile__


// Base class header
#include "base/base.h"

// Standard headers
#include <cstdlib>

// Other ECL headers
#include "base/string.h"

        
namespace ecl {


// ===========================================================================
// Definition cProfile
// ---------------------------------------------------------------------------
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

class __ECL_DLLEXPORT__ cProfile {

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
   // Zahl schreiben, liefert false bei Misserfolg
   bool write(cString app_path, cString key, long data) const;


   // Loeschen
   // ========

   // Einzelnen Key loeschen
   bool remove(cString app_path, cString key);
   // Gesamte Applikation loeschen
   bool remove(cString app_path);


   // Applikations- und Keyliste
   // ==========================

   class ITERATOR {
      friend class cProfile;
      char *pos;
      char *buf;
      int len;
   public:
      ITERATOR() { buf = pos = 0; len = 0;}
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

   // TBD: EBHDL wurde aus base.h zusammen mit dem alten DebugWindow entfernt.
   //      Diese Platformabhaengigkeit besteht sonst nur noch in profile.h/.cpp!
   typedef unsigned long EBHDL;
   EBHDL anchor_hdl, prf_hdl;
   cString prf_name, def_app_path;

};


}; // namespace ecl


#endif // __ecl_profile__

