// ===========================================================================
// eb_res.cpp                                    ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cOsBase
//        |
//        +-cModule     - Resourcen-Module
//        |
//        +-cIcon       - Icon-Resourcen
//        |
//        +-cBitmap     - Bitmap-Resourcen
//
//    cResource         - Spezifikation von Resourcen
//
// ===========================================================================

#include "base/eb_res.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"

#endif /*__INTERFACE__*/




// Lokale Variablen
// ===========================================================================

#if defined __ECL_W32__

   // Backdoor-Entry zur Realisierung der Ladefunktionen fuer Bitmaps
   // und Icons. Wird waehrend der Initialisierung von ECL/win gesetzt.
   HINSTANCE __declspec(dllexport) EclDefaultInstance = NULL;

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cModule
// ---------------------------------------------------------------------------
//
// cBase
//  +--cOsBase
//      +--cModule
//
// ===========================================================================

class __ECL_DLLEXPORT__ cModule : public cOsBase {

public:

   // Default-Konstruktor
   inline cModule()
      { }
   // Konstruktor ueber Modulname
   inline cModule(const char *modname)
      { fromName(modname); }
   // Copy-Konstruktor
   inline cModule(const cModule& other)
      { handle = other.handle; }
   // Destruktor
   ~cModule();

   // Zuweisungs-Operator
   cModule& operator=(const cModule& other)
      { handle = other.handle; return *this; }

   // Initialisierung ueber Modulname
   void fromName(const char *modname);

};

#endif /*__INTERFACE__*/


// Implementierung cModule
// ===========================================================================

cModule::~cModule()
{
}

void cModule::fromName(const char * /*modname*/)
{
   #if defined __ECL_W32__
      // TBD: ...
   #else
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cResource
// ---------------------------------------------------------------------------
//
// cBase
//  +--cResource
//
// ===========================================================================

class __ECL_DLLEXPORT__ cResource {

public:
   // Konstruktor (aktuelles Modul)
   inline cResource(int res_id)
      { cResource::res_id = res_id; }
   // Konstruktor (fremdes Modul)
   inline cResource(cModule /*module*/, int res_id)
      { /* TBD: ... */ cResource::res_id = res_id; }
   // Copy-Konstruktor
   inline cResource(const cResource& other)
      { res_id = other.res_id; }

   // Zuweisungs-Operator
   cResource& operator=(const cResource& other)
      { res_id = other.res_id; return *this; }

   // ID der Resource erfragen
   int getID() const
      { return res_id; }

private:
   int res_id;

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cIcon
// ---------------------------------------------------------------------------
//
// cBase
//  +--cOsBase
//      +--cIcon
//
// ===========================================================================

class __ECL_DLLEXPORT__ cIcon : public cOsBase {

public:

   // Default-Konstruktor
   inline cIcon()
      { }
   // Konstruktor aus Resource
   inline cIcon(const cResource& res, bool def_size = false)
      { load(res, def_size); }
   // Copy-Konstruktor
   inline cIcon(const cIcon& other)
      { handle = other.handle; }
   // Destruktor
   ~cIcon();

   // Zuweisungs-Operator
   cIcon& operator=(const cIcon& other)
      { handle = other.handle; return *this; }

   // Icon aus Resource laden (def_size = false: Groesse wie gespeichert)
   void load(const cResource& res, bool def_size = false);
   // Icon aus Resource laden und auf spezifizierte Groesse skalieren
   void load(const cResource& res, int cx, int cy);

};

#endif /*__INTERFACE__*/

// Implementierung cIcon
// ===========================================================================

cIcon::~cIcon()
{
}

void cIcon::load(const cResource& res, bool def_size)
{
   #if defined __ECL_W32__
      UINT fuLoad = LR_SHARED | (def_size ? LR_DEFAULTSIZE : 0);
      handle = ::LoadImage(EclDefaultInstance, MAKEINTRESOURCE(res.getID()),
                           IMAGE_ICON, 0, 0, fuLoad);
   #else
   #endif
}

void cIcon::load(const cResource& res, int cx, int cy)
{
   #if defined __ECL_W32__
      handle = ::LoadImage(EclDefaultInstance, MAKEINTRESOURCE(res.getID()),
                           IMAGE_ICON, cx, cy, LR_SHARED);
   #else
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cBitmap
// ---------------------------------------------------------------------------
//
// cBase
//  +--cOsBase
//      +--cBitmap
//
// ===========================================================================

class __ECL_DLLEXPORT__ cBitmap : public cOsBase {

public:

   // Default-Konstruktor
   inline cBitmap()
      { refc_ptr = 0; }
   // Konstruktor aus Resource
   inline cBitmap(const cResource& res, int cx = 0, int cy = 0)
      { load(res, cx, cy); }
   // Copy-Konstruktor
   inline cBitmap(const cBitmap& other)
      { refc_ptr = 0; copy(other); }
   // Destruktor
   ~cBitmap();

   // Zuweisungs-Operator
   cBitmap& operator=(const cBitmap& other)
      { copy(other); return *this; }

   // Bitmap aus Resource laden
   void load(const cResource& res, int cx = 0, int cy = 0);

private:

   // Referenzzaehler fuer Freigabe
   int *refc_ptr;

   // Intern: Referenz anlegen
   void alloc();
   // Intern: Referenz freigeben
   void dealloc();
   // Intern: Kopie anfertigen
   void copy(const cBitmap& other);

};

#endif /*__INTERFACE__*/


// Implementierung cBitmap
// ===========================================================================

cBitmap::~cBitmap()
{
   dealloc();
}

void cBitmap::load(const cResource& res, int cx, int cy)
{
   alloc();

   #if defined __ECL_W32__
      handle = ::LoadImage(EclDefaultInstance, MAKEINTRESOURCE(res.getID()),
                           IMAGE_BITMAP, cx, cy, 0);
   #else
   #endif
}

void cBitmap::alloc()
{
   refc_ptr = new0 int;
   *refc_ptr = 0;
}

void cBitmap::dealloc()
{
   if ( refc_ptr && *refc_ptr >= 0 && (*refc_ptr)-- == 0 ) {
      delete refc_ptr;
      #if defined __ECL_W32__
         if ( handle.isValid() )
            ::DeleteObject(handle);
      #else
      #endif
   }
   refc_ptr = 0;
}

void cBitmap::copy(const cBitmap& other)
{
   if ( &other != this ) {
      dealloc();
      handle = other.handle;
      refc_ptr = other.refc_ptr;
      if ( refc_ptr ) ++*refc_ptr;
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cRString
// ---------------------------------------------------------------------------
//
// cBase
//  +--cString
//      +--cRString
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRString : public cString {

public:

   // Default-Konstruktor
   inline cRString()
      { }
   // Konstruktor aus Resource (via Resource-Objekt)
   inline cRString(const cResource& res)
      { load(res); }
   // Konstruktor aus Resource (via Resource-ID)
   inline cRString(int id)
      { load(id); }

   // Bitmap aus Resource laden (via Resource-Objekt)
   void load(const cResource& res);
   // Bitmap aus Resource laden (via Resource-ID)
   void load(int res_id);

};

#endif /*__INTERFACE__*/


// Implementierung cRString
// ===========================================================================

void cRString::load(const cResource& res)
{
   load(res.getID());
}

void cRString::load(int res_id)
{
   char buf[1024];
   int len = 0;

   #if defined __ECL_W32__
      len = ::LoadString(EclDefaultInstance, res_id, buf, sizeof buf);
   #else
   #endif


   init(buf, len + 1);
}

