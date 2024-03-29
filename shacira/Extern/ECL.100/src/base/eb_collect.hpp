/*.SH.*/

/*
 *  Headerfile for module eb_collect
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_collect.cpp on Saturday March 17 2001  16:09:48
 */

#ifndef __eb_collect__
#define __eb_collect__


// Headerfiles
// ===========================================================================

#include <new.h>
#include "base/eb_base.hpp"


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
typedef __IPOSITION* IPOSITION;

#define BEFORE_START_IPOSITION ((IPOSITION)-1L)


// ===========================================================================
// Template-Funktion EclConstructElements
// ---------------------------------------------------------------------------
//
// ===========================================================================

template<class TYPE>
   inline void EclConstructElements(TYPE *elements, int count)
      {
         __ECL_ASSERT1__(count >= 0);
         memset((void*)elements, 0, count * sizeof(TYPE));
         for ( ; count-- ; elements++ )
            ::new((void*)elements) TYPE;
      }


// ===========================================================================
// Template-Funktion EclDestructElements
// ---------------------------------------------------------------------------
//
// ===========================================================================

template<class TYPE>
   inline void EclDestructElements(TYPE *elements, int count)
      {
         __ECL_ASSERT1__(count >= 0);
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
// ===========================================================================

template<class TYPE>
   inline void EclCopyElements(TYPE* dest, const TYPE* src, int count)
      {
         __ECL_ASSERT1__(count >= 0);
         while (count--)
            *dest++ = *src++;
      }


// ===========================================================================
// Template-Funktion EclHashKey
// ---------------------------------------------------------------------------
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


#endif

/*.EH.*/
