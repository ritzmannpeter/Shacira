// ===========================================================================
// eb_store.c
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cSafeDynStorage
//
// ===========================================================================

#include "base/eb_store.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include <stdlib.h>
#include "base/eb_base.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cSafeDynStorage
// ---------------------------------------------------------------------------
//
//  cSafeDynStorage
//
// ===========================================================================

class __ECL_DLLEXPORT__ cSafeDynStorage {

public:
   cSafeDynStorage();
   ~cSafeDynStorage();

   // Wurde das Objekt dynamisch allokiert?
   bool isDynamic() const;

   #ifndef __ECL_DEBUG__
      void *operator new(size_t size);
      void operator delete(void *that);
   #else
      #if defined __ECL_VCPP__
         static void *operator new(size_t size, const char *file, size_t line);
         static void operator delete(void *that, const char *file, size_t line);
      #elif defined __ECL_ICC__
         static void *operator new(size_t size, const char *file, size_t line);
         static void operator delete(void *that, const char *file, size_t line);
      #elif defined __ECL_BCPP__
         // ???
      #endif
   #endif

   static void printDiagInfos();

private:
   int sds_mem_type;
   static int sds_alloc_count;

};

#endif /*__INTERFACE__*/


// Implementierung cSafeDynStorage
// ===========================================================================

int cSafeDynStorage::sds_alloc_count = 0;

#define EYE_CATCHER_STATIC    0x73746174  /*stat*/
#define EYE_CATCHER_DYNAMIC   0x44594e41  /*DYNA*/

cSafeDynStorage::cSafeDynStorage()
{
   if ( sds_mem_type != EYE_CATCHER_DYNAMIC )
      sds_mem_type = EYE_CATCHER_STATIC;
}

cSafeDynStorage::~cSafeDynStorage()
{
   sds_mem_type = 0;
}

bool cSafeDynStorage::isDynamic() const
{
   return sds_mem_type == EYE_CATCHER_DYNAMIC;
}

#ifndef __DEBUG_ALLOC__

   void *cSafeDynStorage::operator new(size_t size)
   {
      cSafeDynStorage *that = (cSafeDynStorage *)malloc(size);
      that->sds_mem_type = EYE_CATCHER_DYNAMIC;
      ++sds_alloc_count;
      return (void *)that;
   }

   void cSafeDynStorage::operator delete(void *that/*, size_t size*/)
   {
      if ( that ) {
         if ( ((cSafeDynStorage *)that)->sds_mem_type == EYE_CATCHER_DYNAMIC ) {
            --sds_alloc_count;
            free(that);
         }
         ((cSafeDynStorage *)that)->sds_mem_type = 0;
      }
   }

#else

   void *cSafeDynStorage::operator new(size_t size, const char *file, size_t line)
   {
      cSafeDynStorage *that = (cSafeDynStorage *)_debug_malloc(size,file,line);
      that->dynamic = true;
      ++alloc_count;
      // cBase::DbgTrcBase("AutoFree Alloc %d", size);
      return (void *)that;
   }

   void cSafeDynStorage::operator delete( void *that, const char *file, size_t line)
   {
      if ( that && ((cSafeDynStorage *)that)->dynamic ) {
         --alloc_count;
         //cBase::DbgTrcBase("AutoFree: %d objects remaining", alloc_count );
         _debug_free(that, file, line);
      }
   }

#endif

void cSafeDynStorage::printDiagInfos()
{
   cBase::DbgOut(0, "cSafeDynStorage: %d objects consuming %d bytes", alloc_count, total);
}

