// ===========================================================================
// base/object.h                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//
// ===========================================================================

#ifndef __ecl_object__
#define __ecl_object__


// Standard headers
#include <cstring>

// Other ECL headers
#include "base/base.h"




// Runtime-Type-Information (light)
// ===========================================================================

//! \related cEclObject Jede ECL-Klasse muss diese Anweisung enthalten. Die
//! Parameter geben den Klassennamen und den Namen der jeweiligen Basisklasse
//! an.
//
#define ECL_DECLARE(CLASS,BASECLASS) \
protected: \
   const char *__getClassName() const \
      { return #CLASS; } \
   bool __isKindOf(const char *kind) const \
      { if ( strcmp(kind, CLASS::__getClassName()) == 0 ) return true; \
        return BASECLASS::__isKindOf(kind); } \
private:

//! \related cEclObject Mit Hilfe dieser Anweisung kann ein durch einen Zeiger
//! spezifiziertes Objekt in einen gegebenen ECL-Typ CLASS gewandelt werden,
//! wenn das Objekt von dieser Klasse abgeleitet wurde. Andernfalls wird ein
//! 0-Zeiger geliefert.
//
#define ECL_CAST(CLASS,PTREXPR) \
   ((CLASS*)cEclObject::__cast(#CLASS,PTREXPR))

//! \related cEclObject Diese Funktion prueft, ob das durch den Zeiger
//! spezifizierte Objekt vom Typ CLASS ist oder davon abgeleitet wurde.
//! ECL_ISKINDOF kann wie eine Methode des Objektes verwendet werden.
//
#define ECL_ISKINDOF(CLASS) \
   isKindOf(#CLASS)


namespace ecl {


// ===========================================================================
// Definition cEclObject
// ---------------------------------------------------------------------------
//
//! Basisklasse fuer ECL-Objekte. Realisiert folgende Features:
//!
//!    - Runtime-Type-Information
//!    - Serialisierung (noch nicht implementiert)
//
// cEclObject
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEclObject {

public:

   //! Virtueller Destruktor (Wichtig bei Mehrfachvererbung!)
   virtual ~cEclObject();


   // ECL-RTTI
   // ========

   //! Klassenname der aktuellen Instanz ermitteln
   inline const char * getClassName() const
      { return __getClassName(); }
   //! Pruefen, ob die Instanz vom Typ \a kind (oder davon abgeleitet) ist
   inline bool isKindOf(const char *kind) const
      { return __isKindOf(kind); }


protected:

   // ECL-RTTI-Events
   // ===============

   //! Wird aufgerufen, um den Klassennamen zu erfragen
   virtual const char *__getClassName() const
      { return "cEclObject"; }
   //! Wird aufgerufen, um zu pruefen, ob die Klasse von \a kind abstammt
   virtual bool __isKindOf(const char *kind) const
      { return strcmp(kind, "cEclObject") == 0; }

public:

	//! Umwandeln des Objektes \a ptr in \a class_name, falls moeglich
   static cEclObject *__cast(const char *class_name, cEclObject *ptr);
	//! Umwandeln des const-Objektes \a ptr in \a class_name, falls moeglich
   static const cEclObject *__cast(const char *class_name, const cEclObject *ptr);

};


}; // namespace ecl


#endif // __ecl_object__

