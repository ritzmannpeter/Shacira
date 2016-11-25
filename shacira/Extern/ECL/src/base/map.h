// ===========================================================================
// base/map.h                                                   ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMap                    - Map collection class.
//
// ===========================================================================

#ifndef __ecl_map__
#define __ecl_map__


// Headerfiles
// ===========================================================================

#include "base/collect.h"
#include <string.h>

    
namespace ecl {


// ===========================================================================
// Klasse cMap<KEY,ARG_KEY,VALUE,ARG_VALUE>
// ---------------------------------------------------------------------------
//
//! Template class for making maps with arbitrary key and value types.
//! @ingroup collections
//!
//! cMap is a dictionary collection class that maps unique keys to values.
//! Once you have inserted a key-value pair (element) into the map, you can
//! efficiently retrieve or delete the pair using the key to access it. You
//! can also iterate over all the elements in the map.
//!
//! A variable of type IPOSITION is used for alternate access to entries.
//! You can use a IPOSITION to “remember” an entry and to iterate through the
//! map. You might think that this iteration is sequential by key value; it
//! is not. The sequence of retrieved elements is indeterminate.
//!
//! Certain member functions of this class call global helper functions that
//! must be customized for most uses of the cMap class.
//!
//! When a CMap object is deleted, or when its elements are removed, the keys
//! and values both are removed.
//!
//! Map class derivation is similar to list derivation.
//!
//! The size of an empty cMap object is:
//!
//!   - OS/2 (IBM CSet ++)        = 24 Bytes
//!   - Windows (MS Visual C++)   = 24 Bytes
//
//  cMap<KEY,ARG_KEY,VALUE,ARG_VALUE>
//
// ===========================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   class cMap {

   protected:
   	// Association
   	struct cAssoc
   	{
   		cAssoc* pNext;
   		unsigned int nHashValue;  // needed for efficient iteration
   		KEY key;
   		VALUE value;
   	};

   public:
   	cMap(int nBlockSize = 10);
   	~cMap();

   // Attributes
   	// number of elements
   	int getCount() const;
   	bool isEmpty() const;

   	//! Lookup. If @a key exists in the map, the value is assigned to @a rValue and
      //! true is returned. Otherwise false is returned and @a rValue is unchanged.
   	bool lookup(ARG_KEY key, VALUE& rValue) const;

   // Operations
   	// Lookup and add if not there
   	VALUE& operator[](ARG_KEY key);

   	// add a new (key, value) pair
   	void setAt(ARG_KEY key, ARG_VALUE newValue);

   	// removing existing (key, ?) pair
   	bool removeKey(ARG_KEY key);
   	void removeAll();

   	// iterating all (key, value) pairs
   	IPOSITION getStartPosition() const;
   	void getNextKey(IPOSITION& rNextPosition, KEY& rKey) const;
   	void getNextAssoc(IPOSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

   	// advanced features for derived classes
   	unsigned int getHashTableSize() const;
   	void initHashTable(unsigned int hashSize, bool bAllocNow = true);

   // Implementation
   protected:
   	cAssoc** m_pHashTable;
   	unsigned int m_nHashTableSize;
   	int m_nCount;
   	cAssoc* m_pFreeList;
   	cPlex* m_pBlocks;
   	int m_nBlockSize;

   	cAssoc* NewAssoc();
   	void FreeAssoc(cAssoc*);
   	cAssoc* GetAssocAt(ARG_KEY, unsigned int&) const;

   };

/////////////////////////////////////////////////////////////////////////////
// cMap<KEY, ARG_KEY, VALUE, ARG_VALUE> inline functions

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   int cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getCount() const
	   { return m_nCount; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   bool cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::isEmpty() const
	   { return m_nCount == 0; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::setAt(ARG_KEY key, ARG_VALUE newValue)
	   { (*this)[key] = newValue; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   IPOSITION cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getStartPosition() const
	   { return (m_nCount == 0) ? 0 : BEFORE_START_IPOSITION; }
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   unsigned int cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getHashTableSize() const
	   { return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////
// cMap<KEY, ARG_KEY, VALUE, ARG_VALUE> out-of-line functions

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::cMap(int nBlockSize)
   {
   	__ECL_ASSERT__(nBlockSize > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	m_pHashTable = 0;
   	m_nHashTableSize = 17;  // default size
   	m_nCount = 0;
   	m_pFreeList = 0;
   	m_pBlocks = 0;
   	m_nBlockSize = nBlockSize;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::initHashTable(unsigned int nHashSize, bool bAllocNow)
   {
      // Used to force allocation of a hash table or to override the default
      //   hash table size of (which is fairly small)

   	__ECL_ASSERT__(m_nCount == 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   	__ECL_ASSERT__(nHashSize > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	if (m_pHashTable != 0)
   	{
   		// free hash table
   		delete[] m_pHashTable;
   		m_pHashTable = 0;
   	}

   	if (bAllocNow)
   	{
   		m_pHashTable = new cAssoc* [nHashSize];
   		memset(m_pHashTable, 0, sizeof(cAssoc*) * nHashSize);
   	}
   	m_nHashTableSize = nHashSize;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeAll()
   {
   	if (m_pHashTable != 0)
   	{
   		// destroy elements (values and keys)
   		for (unsigned int nHash = 0; nHash < m_nHashTableSize; nHash++)
   		{
   			cAssoc* pAssoc;
   			for (pAssoc = m_pHashTable[nHash]; pAssoc != 0;
   			  pAssoc = pAssoc->pNext)
   			{
   				EclDestructElements(&pAssoc->value, 1);
   				EclDestructElements(&pAssoc->key, 1);
   			}
   		}
   	}

   	// free hash table
   	delete[] m_pHashTable;
   	m_pHashTable = 0;

   	m_nCount = 0;
   	m_pFreeList = 0;
   	m_pBlocks->FreeDataChain();
   	m_pBlocks = 0;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::~cMap()
   {
   	removeAll();
   	__ECL_ASSERT__(m_nCount == 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   typename cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::cAssoc* cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::NewAssoc()
   {
   	if (m_pFreeList == 0)
   	{
   		// add another block
   		cPlex* newBlock = cPlex::Create(m_pBlocks, m_nBlockSize, sizeof(cAssoc));
   		// chain them into free list
   		cAssoc* pAssoc = (cAssoc*) newBlock->data();
   		// free in reverse order to make it easier to debug
   		pAssoc += m_nBlockSize - 1;
   		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
   		{
   			pAssoc->pNext = m_pFreeList;
   			m_pFreeList = pAssoc;
   		}
   	}
   	__ECL_ASSERT__(m_pFreeList != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // we must have something

   	cAssoc* pAssoc = m_pFreeList;
   	m_pFreeList = m_pFreeList->pNext;
   	m_nCount++;
   	__ECL_ASSERT__(m_nCount > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // make sure we don't overflow
   	EclConstructElements(&pAssoc->key, 1);
   	EclConstructElements(&pAssoc->value, 1);   // special construct values
   	return pAssoc;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::FreeAssoc(cAssoc* pAssoc)
   {
   	EclDestructElements(&pAssoc->value, 1);
   	EclDestructElements(&pAssoc->key, 1);
   	pAssoc->pNext = m_pFreeList;
   	m_pFreeList = pAssoc;
   	m_nCount--;
   	__ECL_ASSERT__(m_nCount >= 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // make sure we don't underflow

   	// if no more elements, cleanup completely
   	if (m_nCount == 0)
   		removeAll();
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   typename cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::cAssoc* cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetAssocAt(ARG_KEY key, unsigned int& nHash) const
   {
      // find association (or return 0)

   	nHash = EclHashKey(key) % m_nHashTableSize;

   	if (m_pHashTable == 0)
   		return 0;

   	// see if it exists
   	cAssoc* pAssoc;
   	for (pAssoc = m_pHashTable[nHash]; pAssoc != 0; pAssoc = pAssoc->pNext)
   	{
   		if (EclCompareElements(&pAssoc->key, &key))
   			return pAssoc;
   	}
   	return 0;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   bool cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::lookup(ARG_KEY key, VALUE& rValue) const
   {
   	unsigned int nHash;
   	cAssoc* pAssoc = GetAssocAt(key, nHash);
   	if (pAssoc == 0)
   		return false;  // not in map

   	rValue = pAssoc->value;
   	return true;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   VALUE& cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key)
   {
   	unsigned int nHash;
   	cAssoc* pAssoc;
   	if ((pAssoc = GetAssocAt(key, nHash)) == 0)
   	{
   		if (m_pHashTable == 0)
   			initHashTable(m_nHashTableSize);

   		// it doesn't exist, add a new Association
   		pAssoc = NewAssoc();
   		pAssoc->nHashValue = nHash;
   		pAssoc->key = key;
   		// 'pAssoc->value' is a constructed object, nothing more

   		// put into hash table
   		pAssoc->pNext = m_pHashTable[nHash];
   		m_pHashTable[nHash] = pAssoc;
   	}
   	return pAssoc->value;  // return new reference
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   bool cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeKey(ARG_KEY key)
   {
      // remove key - return true if removed

   	if (m_pHashTable == 0)
   		return false;  // nothing in the table

   	cAssoc** ppAssocPrev;
   	ppAssocPrev = &m_pHashTable[EclHashKey(key) % m_nHashTableSize];

   	cAssoc* pAssoc;
   	for (pAssoc = *ppAssocPrev; pAssoc != 0; pAssoc = pAssoc->pNext)
   	{
   		if (EclCompareElements(&pAssoc->key, &key))
   		{
   			// remove it
   			*ppAssocPrev = pAssoc->pNext;  // remove from list
   			FreeAssoc(pAssoc);
   			return true;
   		}
   		ppAssocPrev = &pAssoc->pNext;
   	}
   	return false;  // not found
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getNextAssoc(IPOSITION& rNextPosition, KEY& rKey, VALUE& rValue) const
   {
   	__ECL_ASSERT__(m_pHashTable != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // never call on empty map

   	cAssoc* pAssocRet = (cAssoc*)rNextPosition;
   	__ECL_ASSERT__(pAssocRet != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	if (pAssocRet == (cAssoc*) BEFORE_START_IPOSITION)
   	{
   		// find the first association
   		for (unsigned int nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
   			if ((pAssocRet = m_pHashTable[nBucket]) != 0)
   				break;
   		__ECL_ASSERT__(pAssocRet != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // must find something
   	}

   	// find next association
   	cAssoc* pAssocNext;
   	if ((pAssocNext = pAssocRet->pNext) == 0)
   	{
   		// go to next bucket
   		for (unsigned int nBucket = pAssocRet->nHashValue + 1;
   		  nBucket < m_nHashTableSize; nBucket++)
   			if ((pAssocNext = m_pHashTable[nBucket]) != 0)
   				break;
   	}

   	rNextPosition = (IPOSITION) pAssocNext;

   	// fill in return data
   	rKey = pAssocRet->key;
   	rValue = pAssocRet->value;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
   void cMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getNextKey(IPOSITION& rNextPosition, KEY& rKey) const
   {
   	__ECL_ASSERT__(m_pHashTable != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // never call on empty map

   	cAssoc* pAssocRet = (cAssoc*)rNextPosition;
   	__ECL_ASSERT__(pAssocRet != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	if (pAssocRet == (cAssoc*) BEFORE_START_IPOSITION)
   	{
   		// find the first association
   		for (unsigned int nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
   			if ((pAssocRet = m_pHashTable[nBucket]) != 0)
   				break;
   		__ECL_ASSERT__(pAssocRet != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // must find something
   	}

   	// find next association
   	cAssoc* pAssocNext;
   	if ((pAssocNext = pAssocRet->pNext) == 0)
   	{
   		// go to next bucket
   		for (unsigned int nBucket = pAssocRet->nHashValue + 1;
   		  nBucket < m_nHashTableSize; nBucket++)
   			if ((pAssocNext = m_pHashTable[nBucket]) != 0)
   				break;
   	}

   	rNextPosition = (IPOSITION) pAssocNext;

   	// fill in return data
   	rKey = pAssocRet->key;
   }

}; // namespace ecl


#endif // __ecl_map__


