// ===========================================================================
// base/sharedmem.h                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//! @file   base/sharedmem.h
//! @brief Shared memory management
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cOsBase
//        |
//        +-cSharedMem        - Verwaltung von Shared Memory.
//
// ===========================================================================

#ifndef __ecl_sharedmem__
#define __ecl_sharedmem__


// Headerfiles
// ===========================================================================

#include "base/eb_err.hpp"
#include "base/eb_str.hpp"

           
namespace ecl {


// ===========================================================================
// Definition cSharedMem
// ---------------------------------------------------------------------------
//
//! @class cSharedMem sharedmem.h "base/sharedmem.h"
//! @brief Shared memory management
//!
//! Verwaltung von Shared Memory. Kann aus Konsistenzgruenden auch lokalen
//! Speicher mitverwalten (falls kein Name uebergeben wurde).
//!
//! Es werden immer sizeof(int) Bytes mehr allokiert als angefordert. Das
//! zusaetzliche int enthaelt die tatsaechliche Groesse des Speicherbereiches.
//! Beispiel fuer cSharedMem(..., 5):
//!
//!@verbatim
//!   +---+---+---+---+---+---+---+---+---+
//!   | x   x   x   x | A | B | C | D | E |
//!   +---+---+---+---+---+---+---+---+---+
//!     ^               ^
//!     mem             getAdr()
//!@endverbatim
//
// cBase
//  +--cOsBase
//      +--cSharedMem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cSharedMem : public cOsBase {

public:
   enum OPEN_MODE {
      memCreate,        //!< Create new shared memory
      memOpen,          //!< Cpen existing shared memory
      memOpenOrCreate   //!< Cpen existing shared memory or create if not existent
   };

   enum CREATION_MODE {
      cmLocalCreated,   //!< Local memory allocated
      cmSharedCreated,  //!< Shared memory created
      cmSharedOpened,   //!< Shared memory opened
      cmStaticCreated,  //!< Static buffer initialized
      cmStaticOpened    //!< Static buffer opened
   };

   //! Shared Memory oeffnen oder erzeugen (abhaengig von 'mode')
   //! Lokaler Memory wird angefordert, wenn 'name' nicht spezifiziert
   cSharedMem(const cString &name, OPEN_MODE mode, int size);
   //! Shared Memory in vorhandenem, lokalem Speicherbereich verwalten,
   //! der NICHT angefordert wird. Bei mode == memCreate werden die
   //! Verwaltungsdaten initialisiert. mode == memOpenOrCreate ist
   //! nicht erlaubt!
   cSharedMem(OPEN_MODE mode, void *ptr, int size);
   //! Destructor: release resources
   ~cSharedMem();

   //! Get start address of shared memory
   void *getAdr()
      { return (void *)((char *)mem + sizeof(int)); }
   //! Get size of shared memory in bytes.
   int getSize() const
      { return *((int *)mem); }
   //! Query the creation method used during construction
   CREATION_MODE getCreationMode() const
      { return cm; }

   //! Test whether a certain shared memory already exists
   static bool isAllocated(const cString &name);

private:
   void *mem;           // Zugewiesene Startadresse nach Einblendung
   CREATION_MODE cm;    // Beim Konstruktor angewandete Methode

};

}; // namespace ecl


#endif // _ecl_sharedmem__


