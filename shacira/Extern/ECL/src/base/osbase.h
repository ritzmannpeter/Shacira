// ===========================================================================
// base/osbase.h                                                ______ /  ECL
// Autor: Thomas Epting, Markus Wuertz                         /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cOsBase - Platformspezifische Basisfunktionen
//
//! @file  osbase.h
//! @brief Platform dependant stuff
// ===========================================================================

#ifndef __ecl_osbase__
#define __ecl_osbase__


// Base class header
#include "base/base.h"

// Other ECL headers
#include "base/string.h"

#if defined __ECL_LINUX__
   #include <sys/types.h>
#endif

             
namespace ecl {


// ===========================================================================
// Definition cOsBase
// ---------------------------------------------------------------------------
//
//! Basisklasse zur Realisierung von betriebssystemspezifischen Objekten
//! (OS-Objekt), die typischerweise ueber ein Identifikations-Handle verfuegen.
//! Ueber die spezielle Methode getHandleFrom() kann die Implementierung des
//! OS-Objektes auf normalerweise verdeckte Handles anderer OS-Objekte zu-
//! greifen.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cOsBase {

public:
#if defined __ECL_W32__
   cOsBase() {};
#endif

public:
   class cOsKey;

   class __ECL_DLLEXPORT__ cOsHandle {

   public:
   #if defined __ECL_OS2__

      cOsHandle(unsigned long h = 0)
         { cOsHandle::h = h; }
      unsigned long * operator & ()
         { return &h; }
      operator unsigned long () const
         { return h; }
      void invalidate()
         { h = 0; }
      bool isNull() const
         { return h == 0; }
      bool isValid() const
         { return h != 0; }

   private:
      unsigned long h;

   #elif defined __ECL_W32__

      cOsHandle(void *hnd = 0)
         { h = hnd; }
      void ** operator & ()
         { return &h; }
      operator void * () const
         { return h; }
      void invalidate()
         { h = 0; }
      bool isNull() const
         { return h == 0; }
      bool isValid() const
         { return h != 0; }

   private:
      void *h;

   #endif

   };

protected:
   //! Handle des betriebssystem-spezifischen Objektes
   cOsHandle handle;

   //! Erfragen von Handles anderer betriebssystem-spezifischer Objekte
   static const cOsHandle getHandleFrom(const cOsBase& other)
      { return other.handle; }
   //! Setzen von Handles anderer betriebssystem-spezifischer Objekte (Gefaehrlich!!!)
   static void setHandleOf(cOsBase& other, const cOsHandle& h)
      { other.handle = h; }

};

// ===========================================================================
// Definition cOsBase::cOsKey (nur __ECL_LINUX__)
// ---------------------------------------------------------------------------
//
// Prozessuebergreifenden key_t aus symbolischem Namen gewinnen.
// Die Verbindung wird ueber eine Datei in "/tmp/ecl/" hergestellt.
// Die Art des Zugriffs legt fest, ob die Datei existieren kann oder muss etc.
//
// Einschraenkungen: der symbolische Name muss einem Dateinamen entsprechen
// und darf keine Pfad-Anteil besitzen (Neue Verzeichnisse koennen derzeit
// nicht automatisch angelegt werden).
// ===========================================================================

#if defined __ECL_LINUX__

class __ECL_DLLEXPORT__ cOsBase::cOsKey {
public:
   enum OPEN_MODE {
      keyCreate,        //!< Create new key
      keyOpen,          //!< Open existing key
      keyOpenOrCreate   //!< Cpen existing key or create if not existent
   };

   cOsKey(const cString &name, int mode);
   ~cOsKey();

   key_t getKey() const { return _key; }
   bool isValid() const { return _key != -1; }
   int getFlags() const { return _flags; }
   bool hasCreated() const { return _created; }
   const cString &getName() const { return _name; }

   static cString buildKeyFileSpec(const cString &name) { return "/tmp/ecl/" + name; }


private:
   enum {PROJ_ID = 0xEC }; // common proj_id for EC-L
   key_t _key;
   int _flags;    // -> msgflag, shmflag, semflg
   cString _name;
   bool _created;
};

#endif // __ECL_LINUX__


}; // namespace ecl


#endif // __ecl_osbase__

