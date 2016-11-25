// ===========================================================================
// mfc_d.cpp                                     ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    ccdFont                    - Kompagnon-Klasse zu "cdFont"
//
//    ccdContext                 - Kompagnon-Klasse zu "cdContext"
//
// ===========================================================================

#include "win/system/mfc/mfc_d.hpp"
#include "win/system/mfc/mfc.hpp"

#include "draw/ed_font.hpp"
#include "draw/ed_context.hpp"

#include "stdafx.h"




#ifdef __INTERFACE__

// Forward-Deklarationen
// ===========================================================================

// von ECL/draw:
class cdFont;
class cdContext;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// ccdFont
// ---------------------------------------------------------------------------
//
// ccdFont
//
// ===========================================================================

class ccdFont {

public:

   // Zeiger auf Font-Objekt ermitteln
   static void *getFont(const cdFont& fnt);

};

#endif /*__INTERFACE__*/


// Implementierung ccdFont
// ===========================================================================

void * ccdFont::getFont(const cdFont& fnt)
   { return fnt.font; }




#ifdef __INTERFACE__

// ===========================================================================
// ccdContext
// ---------------------------------------------------------------------------
//
// ccdContext
//
// ===========================================================================

class ccdContext {

public:

   // Zeiger auf Kontext-Objekt ermitteln
   static void *getContext(const cdContext *ctxt);

};

#endif /*__INTERFACE__*/


// Implementierung ccdContext
// ===========================================================================

void * ccdContext::getContext(const cdContext *ctxt)
   { return ctxt->getContext(); }

