// ===========================================================================
// base/object.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/object.h"




namespace ecl {




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

   __ECL_DEBUG_PRINTF__(cBase::dbgError|cBase::dbgBase, ("ECL cast to '%s' failed", class_name));
   return 0;
}

const cEclObject * cEclObject::__cast(const char *class_name, const cEclObject *ptr)
{
   if ( ptr == 0 ) {
      return 0;
   } else if ( ptr->isKindOf(class_name) ) {
      return ptr;
   } else if ( strncmp(class_name, "const ", 6) == 0 && ptr->isKindOf(class_name+6) ) {
      return ptr;
   }

   __ECL_DEBUG_PRINTF__(cBase::dbgError|cBase::dbgBase, ("ECL cast to '%s' failed", class_name));
   return 0;
}




}; // namespace ecl

