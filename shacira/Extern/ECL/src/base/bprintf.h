// ===========================================================================
// base/bprintf.h                                               ______ /  ECL
// Autor: Norman Bring                                         /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses kleine, aber feine Modul stellt die folgenden FUNKTIONEN
// zur Verfuegung:
//
//    bprintf  - Binary Print Formatted
//    vbprintf - Variable Binary Print Formatted
//
// Diese arbeiten aehnlich wie sprintf und vsprintf aus der Standard-"C"-
// Bibliothek, erzeugen aber aus den angegebenen Argumenten keinen String
// sondern Binaerdaten.
//
// ===========================================================================

#ifndef __ecl_bprintf__
#define __ecl_bprintf__


// Standard headers
#include <cstdarg>

// Other ECL headers
#include "base/base.h"


namespace ecl {


// Forward-Deklarationen
// ==========================================================================

int __ECL_DLLEXPORT__ vbprintf( void *buf, const char *fmt, va_list ap );
int __ECL_DLLEXPORT__ bprintf( void *buf, const char *fmt, ... );


}; // namespace ecl


#endif // __ecl_bprintf__

