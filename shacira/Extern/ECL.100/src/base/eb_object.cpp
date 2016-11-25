// ===========================================================================
// eb_object.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//
// ===========================================================================

#include "base/eb_object.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"


// Runtime-Type-Information (light)
// ===========================================================================

// ECL_DECLARE - Jede ECL-Klasse muss diese Anweisung enthalten. Die Para-
// meter geben den Klassennamen und den Namen der jeweiligen Basisklasse an.
//
#define ECL_DECLARE(CLASS,BASECLASS) \
protected: \
   const char *__getClassName() const \
      { return #CLASS; } \
   bool __isKindOf(const char *kind) const \
      { if ( strcmp(kind, CLASS::__getClassName()) == 0 ) return true; \
        return BASECLASS::__isKindOf(kind); } \
private:

// ECL_CAST - Mit Hilfe dieser Anweisung kann ein durch einen Zeiger spezifi-
// ziertes Objekt in einen gegebenen ECL-Typ CLASS gewandelt werden, wenn das
// Objekt von dieser Klasse abgeleitet wurde. Andernfalls wird ein 0-Zeiger
// geliefert.
//
#define ECL_CAST(CLASS,PTREXPR) \
   ((CLASS*)cEclObject::__cast(#CLASS,PTREXPR))

// ECL_ISKINDOF - Diese Funktion prueft, ob das durch den Zeiger spezifizierte
// Objekt vom Typ CLASS ist oder davon abgeleitet wurde. ECL_ISKINDOF kann wie
// eine Methode des Objektes verwendet werden.
//
#define ECL_ISKINDOF(CLASS) \
   isKindOf(#CLASS)

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEclObject
// ---------------------------------------------------------------------------
//
// Basisklasse fuer ECL-Objekte. Realisiert folgende Features:
//
//    - Runtime-Type-Information
//    - Serialisierung (noch nicht implementiert)
//
// cEclObject
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEclObject {

public:

   // Virtueller Destruktor (Wichtig bei Mehrfachvererbung!)
   virtual ~cEclObject();


   // ECL-RTTI
   // ========

   // Klassenname der aktuellen Instanz ermitteln
   inline const char * getClassName() const
      { return __getClassName(); }
   // Pruefen, ob die Instanz vom Typ 'kind' (oder davon abgeleitet) ist
   inline bool isKindOf(const char *kind) const
      { return __isKindOf(kind); }


protected:

   // ECL-RTTI-Events
   // ===============

   virtual const char *__getClassName() const
      { return "cEclObject"; }
   virtual bool __isKindOf(const char *kind) const
      { return strcmp(kind, "cEclObject") == 0; }

public:

   static cEclObject *__cast(const char *class_name, cEclObject *ptr);

};

#endif /*__INTERFACE__*/


// Implementierung cEclObject
// ===========================================================================

cEclObject::~cEclObject()
{
}

cEclObject * cEclObject::__cast(const char *class_name, cEclObject *ptr)
{
   // 04.12.2001 -TE- Dem Klassennamen darf auch ein optionales "const"
   // vorangestellt werden (vereinfachte Benutzung von ECL_CAST)

   if ( ptr == 0 ) {
      return 0;
   } else if ( ptr->isKindOf(class_name) ) {
      return ptr;
   } else if ( strncmp(class_name, "const ", 6) == 0 && ptr->isKindOf(class_name+6) ) {
      return ptr;
   }

   __ECL_ASSERT2__(0, ("ECL cast to '%s' failed", class_name));
   return 0;
}


