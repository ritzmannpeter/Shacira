// ===========================================================================
// ed_object.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cdObject                   - Basisklasse fuer Anzeigeobjekte
//
// ===========================================================================

#include "draw/ed_object.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "draw/ed_base.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdObject
// ---------------------------------------------------------------------------
//
//  cdObject
//
// ===========================================================================

class cdObject {
   friend class cdSpace;

public:

   // Konstruktor
   cdObject(cdColor _color = cdColor::Undef) :
      color(_color) { }

   // Objekt zeichnen
   inline void draw(cdSpace *space) const
      { onDraw(space); }

protected:

   cdColor color;

   // Wird aufgerufen, um das Objekt zu zeichnen
   virtual void onDraw(cdSpace *space) const = 0;

};

#endif /*__INTERFACE__*/


