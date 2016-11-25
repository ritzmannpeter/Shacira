// ===========================================================================
// base/collect.h                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMap                    - Map collection class.
//
// ===========================================================================

#ifndef __ecl_collect__
#define __ecl_collect__


// Headerfiles
// ===========================================================================

#if __ECL_VCPP__ >= 1310
   #include <new>
#else
   #include <new.h>
// PR GNUC
   #include <string.h>
#endif

#include "base/base.h"

namespace ecl {


// ===========================================================================
// Typ IPOSITION
// ---------------------------------------------------------------------------
//
// Abstract iterator position.
//
// 25.01.01 -TE- Name geaendert POSITION -> IPOSITION, um Konflikten mit
//    der MFC aus dem Weg zu gehen...
//
//  IPOSITION
//
// ===========================================================================

struct __IPOSITION { };
//! Abstract iterator position.
//! @ingroup collections
typedef __IPOSITION* IPOSITION;

//! Marks the position before the start position.
//! @ingroup collections
#define BEFORE_START_IPOSITION ((IPOSITION)-1L)


// ===========================================================================
// Template-Funktion EclConstructElements
// ---------------------------------------------------------------------------
//
//! Performs any action necessary when an element is constructed.
//! @ingroup collections
//!
//! This function is called when new array, list, and map elements are
//! constructed. The default version initializes all bits of the new elements
//! to 0.
//
// ===========================================================================

template<class TYPE>
   inline void EclConstructElements(TYPE *elements, int count)
      {
         __ECL_ASSERT__(count >= 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
         memset((void*)elements, 0, count * sizeof(TYPE));
         for ( ; count-- ; elements++ )
            ::new((void*)elements) TYPE;
      }


// ===========================================================================
// Template-Funktion EclDestructElements
// ---------------------------------------------------------------------------
//
//! Performs any action necessary when an element is destroyed.
//! @ingroup collections
//!
//! The cArray, cList, and cMap class members call this function when
//! elements are destroyed. The default implementation calls the destructor
//! for each element.
//
// ===========================================================================

template<class TYPE>
   inline void EclDestructElements(TYPE *elements, int count)
      {
         __ECL_ASSERT__(count >= 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
         for (; count--; elements++)
            elements->~TYPE();
      }
   inline void EclDestructElements(char * /*elements*/, int /*count*/)
      { /* no destructor call needed */ }
   inline void EclDestructElements(int * /*elements*/, int /*count*/)
      { /* no destructor call needed */ }
   inline void EclDestructElements(long * /*elements*/, int /*count*/)
      { /* no destructor call needed */ }
   inline void EclDestructElements(void ** /*elements*/, int /*count*/)
      { /* no destructor call needed */ }


// ===========================================================================
// Template-Funktion EclCompareElements
// ---------------------------------------------------------------------------
//
//! Indicates whether elements are the same.
//! @ingroup collections
//!
//! This function is called directly by cList::find() and indirectly by
//! cMap::lookup() and cMap::operator[]. The cMap calls use the cMap
//! template parameters KEY and ARG_KEY.
//!
//! The default implementation returns the result of the comparison of
//! *pElement1 and *pElement2. Override this function so that it compares
//! the elements in a way that is appropriate for your application.
//!
//! The C++ language defines the comparison operator (==) for simple types
//! (char, int, float, and so on) but does not define a comparison operator
//! for classes and structures. If you want to use EclCompareElements or to
//! instantiate one of the collection classes that uses it, you must either
//! define the comparison operator or overload EclCompareElements with a
//! version that returns appropriate values.
//
// ===========================================================================

template<class TYPE>
   inline bool EclCompareElements(const TYPE* pElement1, const TYPE* pElement2)
      {
         return *pElement1 == *pElement2;
      }


// ===========================================================================
// Template-Funktion EclCopyElements
// ---------------------------------------------------------------------------
//
//! Copies elements from one array to another.
//! @ingroup collections
//!
//! This function is called directly by cArray::append() and cArray::copy().
//! The default implementation uses the simple assignment operator ( = )
//! to perform the copy operation. If the type being copied does not have
//! an overloaded operator=, then the default implementation performs a
//! bitwise copy.
//
// ===========================================================================

template<class TYPE>
   inline void EclCopyElements(TYPE* dest, const TYPE* src, int count)
      {
         __ECL_ASSERT__(count >= 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
         while (count--)
            *dest++ = *src++;
      }


// ===========================================================================
// Template-Funktion EclHashKey
// ---------------------------------------------------------------------------
//
//! Calculates a hash key.
//! @ingroup collections
//!
//! Calculates a hash value for the given key. This function is called
//! directly by cMap::removeKey() and indirectly by cMap::lookup()
//! and cMap::operator[]. The default implementation creates a hash value
//! by shifting key rightward by four positions. Override this function so
//! that it returns hash values appropriate for your application.
//
// ===========================================================================

template<class TYPE>
   inline unsigned int EclHashKey(TYPE key)
      {
         // default identity hash - works for most primitive values
         return ((unsigned int)(void*)(unsigned long)key) >> 4;
      }
   inline unsigned int EclHashKey(const char *key)
      {
	      unsigned int hash = 0;
	      while ( *key )
		      hash = (hash<<5) + hash + *key++;
	      return hash;
      }


// ===========================================================================
// Definition cPlex
// ---------------------------------------------------------------------------
//
// Warning: variable length structure
//
//  cPlex
//
// ===========================================================================

class __ECL_DLLEXPORT__ cPlex {

public:
	cPlex* pNext;
// unsigned char data[maxNum*elementSize];

	void* data() { return this+1; }
	static cPlex* Create(cPlex*& head, unsigned int nMax, unsigned int cbElement);
	void FreeDataChain();       // free this one and links
};

}; // namespace ecl


#endif // __ecl_collect__

