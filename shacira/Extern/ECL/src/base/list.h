// ===========================================================================
// base/list.h                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cList                   - List collection class.
//
// ===========================================================================

#ifndef __ecl_list__
#define __ecl_list__


// Headerfiles
// ===========================================================================

#include "base/collect.h"


namespace ecl {


// ===========================================================================
// Klasse cList<TYPE,ARG_TYPE>
// ---------------------------------------------------------------------------
//
//! Template class for making lists of arbitrary types.
//! @ingroup collections
//!
//! The cList class supports ordered lists of nonunique objects accessible
//! sequentially or by value. cList lists behave like doubly-linked lists.
//! A variable of type IPOSITION is a key for the list. You can use a
//! IPOSITION variable as an iterator to traverse a list sequentially and as
//! a bookmark to hold a place. A position is not the same as an index,
//! however.
//!
//! Element insertion is very fast at the list head, at the tail, and at a
//! known IPOSITION. A sequential search is necessary to look up an element
//! by value or index. This search can be slow if the list is long.
//!
//! Certain member functions of this class call global helper functions that
//! must be customized for most uses of the cList class.
//!
//! The size of an empty cList object is:
//!
//!   - OS/2 (IBM CSet ++)        = 24 Bytes
//!   - Windows (MS Visual C++)   = 24 Bytes
//
//  cList<TYPE,ARG_TYPE>
//
// ===========================================================================

template<class TYPE, class ARG_TYPE>
   class cList {

   protected:
   	struct cNode
   	{
   		cNode* pNext;
   		cNode* pPrev;
   		TYPE data;
   	};

   public:
   // Construction
   	cList(int nBlockSize = 10);
      ~cList();

   // Attributes (head and tail)
   	// count of elements
   	int getCount() const;
   	bool isEmpty() const;

   	// peek at head or tail
   	TYPE& getHead();
   	TYPE getHead() const;
   	TYPE& getTail();
   	TYPE getTail() const;

   // Operations
   	// get head or tail (and remove it) - don't call on empty list !
   	TYPE removeHead();
   	TYPE removeTail();

   	// add before head or after tail
   	IPOSITION addHead(ARG_TYPE newElement);
   	IPOSITION addTail(ARG_TYPE newElement);

   	// add another list of elements before head or after tail
   	void addHead(cList<TYPE,ARG_TYPE>* pNewList);
   	void addTail(cList<TYPE,ARG_TYPE>* pNewList);

   	// remove all elements
   	void removeAll();

   	// iteration
   	IPOSITION getHeadPosition() const;
   	IPOSITION getTailPosition() const;
   	TYPE& getNext(IPOSITION& rPosition); // return *Position++
   	TYPE getNext(IPOSITION& rPosition) const; // return *Position++
   	TYPE& getPrev(IPOSITION& rPosition); // return *Position--
   	TYPE getPrev(IPOSITION& rPosition) const; // return *Position--

   	// getting/modifying an element at a given position
   	TYPE& getAt(IPOSITION position);
   	TYPE getAt(IPOSITION position) const;
   	void setAt(IPOSITION pos, ARG_TYPE newElement);
   	void removeAt(IPOSITION position);

   	// inserting before or after a given position
   	IPOSITION insertBefore(IPOSITION position, ARG_TYPE newElement);
   	IPOSITION insertAfter(IPOSITION position, ARG_TYPE newElement);

   	// helper functions (note: O(n) speed)
   	IPOSITION find(ARG_TYPE searchValue, IPOSITION startAfter = 0) const;
   		// defaults to starting at the HEAD, return 0 if not found
   	IPOSITION findIndex(int nIndex) const;
   		// get the 'nIndex'th element (may return 0)

   // Implementation
   protected:
   	cNode* m_pNodeHead;
   	cNode* m_pNodeTail;
   	int m_nCount;
   	cNode* m_pNodeFree;
   	cPlex* m_pBlocks;
   	int m_nBlockSize;

   	cNode* NewNode(cNode*, cNode*);
   	void FreeNode(cNode*);

   };

/////////////////////////////////////////////////////////////////////////////
// cList<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
   int cList<TYPE, ARG_TYPE>::getCount() const
   	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
   bool cList<TYPE, ARG_TYPE>::isEmpty() const
   	{ return m_nCount == 0; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getHead()
   	{ __ECL_ASSERT__(m_pNodeHead != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getHead() const
   	{ __ECL_ASSERT__(m_pNodeHead != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getTail()
   	{ __ECL_ASSERT__(m_pNodeTail != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getTail() const
   	{ __ECL_ASSERT__(m_pNodeTail != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::getHeadPosition() const
   	{ return (IPOSITION) m_pNodeHead; }
template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::getTailPosition() const
   	{ return (IPOSITION) m_pNodeTail; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getNext(IPOSITION& rPosition) // return *Position++
   	{ cNode* pNode = (cNode*) rPosition;
   		rPosition = (IPOSITION) pNode->pNext;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getNext(IPOSITION& rPosition) const // return *Position++
   	{ cNode* pNode = (cNode*) rPosition;
   		rPosition = (IPOSITION) pNode->pNext;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getPrev(IPOSITION& rPosition) // return *Position--
   	{ cNode* pNode = (cNode*) rPosition;
   		rPosition = (IPOSITION) pNode->pPrev;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getPrev(IPOSITION& rPosition) const // return *Position--
   	{ cNode* pNode = (cNode*) rPosition;
   		rPosition = (IPOSITION) pNode->pPrev;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getAt(IPOSITION position)
   	{ cNode* pNode = (cNode*) position;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getAt(IPOSITION position) const
   	{ cNode* pNode = (cNode*) position;
   		return pNode->data; }
template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::setAt(IPOSITION pos, ARG_TYPE newElement)
   	{ cNode* pNode = (cNode*) pos;
   		pNode->data = newElement; }

template<class TYPE, class ARG_TYPE>
   cList<TYPE, ARG_TYPE>::cList(int nBlockSize)
   {
   __ECL_ASSERT__(nBlockSize > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	m_nCount = 0;
   	m_pNodeHead = m_pNodeTail = m_pNodeFree = 0;
   	m_pBlocks = 0;
   	m_nBlockSize = nBlockSize;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::removeAll()
   {
   	// destroy elements
   	cNode* pNode;
   	for (pNode = m_pNodeHead; pNode != 0; pNode = pNode->pNext)
   		EclDestructElements(&pNode->data, 1);

   	m_nCount = 0;
   	m_pNodeHead = m_pNodeTail = m_pNodeFree = 0;
   	m_pBlocks->FreeDataChain();
   	m_pBlocks = 0;
   }

template<class TYPE, class ARG_TYPE>
   cList<TYPE, ARG_TYPE>::~cList()
   {
   	removeAll();
   	__ECL_ASSERT__(m_nCount == 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   }

/////////////////////////////////////////////////////////////////////////////
// Node helpers
//
// Implementation note: cNode's are stored in cPlex blocks and
//  chained together. Free blocks are maintained in a singly linked list
//  using the 'pNext' member of cNode with 'm_pNodeFree' as the head.
//  Used blocks are maintained in a doubly linked list using both 'pNext'
//  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
//   as the head/tail.
//
// We never free a cPlex block unless the List is destroyed or RemoveAll()
//  is used - so the total number of cPlex blocks may grow large depending
//  on the maximum past size of the list.
//

template<class TYPE, class ARG_TYPE>
   typename cList<TYPE, ARG_TYPE>::cNode* cList<TYPE, ARG_TYPE>::NewNode(cNode* pPrev, cNode* pNext)
   {
   	if (m_pNodeFree == 0)
   	{
   		// add another block
   		cPlex* pNewBlock = cPlex::Create(m_pBlocks, m_nBlockSize,
   				 sizeof(cNode));

   		// chain them into free list
   		cNode* pNode = (cNode*) pNewBlock->data();
   		// free in reverse order to make it easier to debug
   		pNode += m_nBlockSize - 1;
   		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
   		{
   			pNode->pNext = m_pNodeFree;
   			m_pNodeFree = pNode;
   		}
   	}
   	__ECL_ASSERT__(m_pNodeFree != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // we must have something

// PR GNUC
//   	cList<TYPE,ARG_TYPE>::cNode* pNode = m_pNodeFree;
   	cNode* pNode = m_pNodeFree;
   	m_pNodeFree = m_pNodeFree->pNext;
   	pNode->pPrev = pPrev;
   	pNode->pNext = pNext;
   	m_nCount++;
   	__ECL_ASSERT__(m_nCount > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // make sure we don't overflow

   	EclConstructElements(&pNode->data, 1);
   	return pNode;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::FreeNode(cNode* pNode)
   {
   	EclDestructElements(&pNode->data, 1);
   	pNode->pNext = m_pNodeFree;
   	m_pNodeFree = pNode;
   	m_nCount--;
   	__ECL_ASSERT__(m_nCount >= 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // make sure we don't underflow

   	// if no more elements, cleanup completely
   	if (m_nCount == 0)
   		removeAll();
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::addHead(ARG_TYPE newElement)
   {
   	cNode* pNewNode = NewNode(0, m_pNodeHead);
   	pNewNode->data = newElement;
   	if (m_pNodeHead != 0)
   		m_pNodeHead->pPrev = pNewNode;
   	else
   		m_pNodeTail = pNewNode;
   	m_pNodeHead = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::addTail(ARG_TYPE newElement)
   {
   	cNode* pNewNode = NewNode(m_pNodeTail, 0);
   	pNewNode->data = newElement;
   	if (m_pNodeTail != 0)
   		m_pNodeTail->pNext = pNewNode;
   	else
   		m_pNodeHead = pNewNode;
   	m_pNodeTail = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::addHead(cList<TYPE,ARG_TYPE>* pNewList)
   {
   	__ECL_ASSERT__(pNewList != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	// add a list of same elements to head (maintain order)
   	IPOSITION pos = pNewList->getTailPosition();
   	while (pos != 0)
   		addHead(pNewList->getPrev(pos));
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::addTail(cList<TYPE,ARG_TYPE>* pNewList)
   {
   	__ECL_ASSERT__(pNewList != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);

   	// add a list of same elements
   	IPOSITION pos = pNewList->getHeadPosition();
   	while (pos != 0)
   		addTail(pNewList->getNext(pos));
   }

template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::removeHead()
   {
   	__ECL_ASSERT__(m_pNodeHead != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // don't call on empty list !!!

   	cNode* pOldNode = m_pNodeHead;
   	TYPE returnValue = pOldNode->data;

   	m_pNodeHead = pOldNode->pNext;
   	if (m_pNodeHead != 0)
   		m_pNodeHead->pPrev = 0;
   	else
   		m_pNodeTail = 0;
   	FreeNode(pOldNode);
   	return returnValue;
   }

template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::removeTail()
   {
   	__ECL_ASSERT__(m_pNodeTail != 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);  // don't call on empty list !!!

   	cNode* pOldNode = m_pNodeTail;
   	TYPE returnValue = pOldNode->data;

   	m_pNodeTail = pOldNode->pPrev;
   	if (m_pNodeTail != 0)
   		m_pNodeTail->pNext = 0;
   	else
   		m_pNodeHead = 0;
   	FreeNode(pOldNode);
   	return returnValue;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::insertBefore(IPOSITION position, ARG_TYPE newElement)
   {
   	if (position == 0)
   		return addHead(newElement); // insert before nothing -> head of the list

   	// Insert it before position
   	cNode* pOldNode = (cNode*) position;
   	cNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
   	pNewNode->data = newElement;

   	if (pOldNode->pPrev != 0)
   	{
   		pOldNode->pPrev->pNext = pNewNode;
   	}
   	else
   	{
   		__ECL_ASSERT__(pOldNode == m_pNodeHead, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		m_pNodeHead = pNewNode;
   	}
   	pOldNode->pPrev = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::insertAfter(IPOSITION position, ARG_TYPE newElement)
   {
   	if (position == 0)
   		return addTail(newElement); // insert after nothing -> tail of the list

   	// Insert it before position
   	cNode* pOldNode = (cNode*) position;
   	cNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
   	pNewNode->data = newElement;

   	if (pOldNode->pNext != 0)
   	{
   		pOldNode->pNext->pPrev = pNewNode;
   	}
   	else
   	{
   		__ECL_ASSERT__(pOldNode == m_pNodeTail, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
   		m_pNodeTail = pNewNode;
   	}
   	pOldNode->pNext = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::removeAt(IPOSITION position)
   {
   	cNode* pOldNode = (cNode*) position;

   	// remove pOldNode from list
   	if (pOldNode == m_pNodeHead)
   	{
   		m_pNodeHead = pOldNode->pNext;
   	}
   	else
   	{
   		pOldNode->pPrev->pNext = pOldNode->pNext;
   	}
   	if (pOldNode == m_pNodeTail)
   	{
   		m_pNodeTail = pOldNode->pPrev;
   	}
   	else
   	{
   		pOldNode->pNext->pPrev = pOldNode->pPrev;
   	}
   	FreeNode(pOldNode);
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::findIndex(int nIndex) const
   {
   	if (nIndex >= m_nCount || nIndex < 0)
   		return 0;  // went too far

   	cNode* pNode = m_pNodeHead;
   	while (nIndex--)
   	{
   		pNode = pNode->pNext;
   	}
   	return (IPOSITION) pNode;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::find(ARG_TYPE searchValue, IPOSITION startAfter) const
   {
   	cNode* pNode = (cNode*) startAfter;
   	if (pNode == 0)
   	{
   		pNode = m_pNodeHead;  // start at head
   	}
   	else
   	{
   		pNode = pNode->pNext;  // start after the one specified
   	}

   	for (; pNode != 0; pNode = pNode->pNext)
   		if (EclCompareElements(&pNode->data, &searchValue))
   			return (IPOSITION)pNode;
   	return 0;
   }


}; // namespace ecl


#endif // __ecl_list__

