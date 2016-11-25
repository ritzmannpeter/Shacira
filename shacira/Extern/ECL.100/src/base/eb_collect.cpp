// ===========================================================================
// eb_collect.cpp                                ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMap                    - Map collection class.
//
// ===========================================================================

#include "base/eb_collect.hpp"




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cPlex
// ===========================================================================

cPlex* cPlex::Create(cPlex*& pHead, unsigned int nMax, unsigned int cbElement)
{
   // like 'calloc' but no zero fill
   // may throw memory exceptions

	__ECL_ASSERT1__(nMax > 0 && cbElement > 0);
	cPlex* p = (cPlex*) new0 unsigned char[sizeof(cPlex) + nMax * cbElement];
			// may throw exception
	p->pNext = pHead;
	pHead = p;  // change head (adds in reverse order for simplicity)
	return p;
}

void cPlex::FreeDataChain()     // free this one and links
{
	cPlex* p = this;
	while (p != NULL)
	{
		unsigned char* bytes = (unsigned char*) p;
		cPlex* pNext = p->pNext;
		delete[] bytes;
		p = pNext;
	}
}


