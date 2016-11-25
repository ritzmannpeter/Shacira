// ===========================================================================
// eb_list.cpp                                   ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cList                   - List collection class.
//
// ===========================================================================

#include "base/eb_list.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_collect.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Klasse cList<TYPE,ARG_TYPE>
// ---------------------------------------------------------------------------
//
// Groesse eines leeren cList-Objektes unter:
//
//   - OS/2 (IBM CSet ++)        = 24 Bytes
//   - Windows (MS Visual C++)   = 24 Bytes
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
   	IPOSITION find(ARG_TYPE searchValue, IPOSITION startAfter = NULL) const;
   		// defaults to starting at the HEAD, return NULL if not found
   	IPOSITION findIndex(int nIndex) const;
   		// get the 'nIndex'th element (may return NULL)

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
   	{ __ECL_ASSERT1__(m_pNodeHead != NULL);
   		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getHead() const
   	{ __ECL_ASSERT1__(m_pNodeHead != NULL);
   		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
   TYPE& cList<TYPE, ARG_TYPE>::getTail()
   	{ __ECL_ASSERT1__(m_pNodeTail != NULL);
   		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::getTail() const
   	{ __ECL_ASSERT1__(m_pNodeTail != NULL);
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
   	__ECL_ASSERT1__(nBlockSize > 0);

   	m_nCount = 0;
   	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
   	m_pBlocks = NULL;
   	m_nBlockSize = nBlockSize;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::removeAll()
   {
   	// destroy elements
   	cNode* pNode;
   	for (pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
   		EclDestructElements(&pNode->data, 1);

   	m_nCount = 0;
   	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
   	m_pBlocks->FreeDataChain();
   	m_pBlocks = NULL;
   }

template<class TYPE, class ARG_TYPE>
   cList<TYPE, ARG_TYPE>::~cList()
   {
   	removeAll();
   	__ECL_ASSERT1__(m_nCount == 0);
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
   cList<TYPE, ARG_TYPE>::cNode* cList<TYPE, ARG_TYPE>::NewNode(cNode* pPrev, cNode* pNext)
   {
   	if (m_pNodeFree == NULL)
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
   	__ECL_ASSERT1__(m_pNodeFree != NULL);  // we must have something

   	cList<TYPE,ARG_TYPE>::cNode* pNode = m_pNodeFree;
   	m_pNodeFree = m_pNodeFree->pNext;
   	pNode->pPrev = pPrev;
   	pNode->pNext = pNext;
   	m_nCount++;
   	__ECL_ASSERT1__(m_nCount > 0);  // make sure we don't overflow

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
   	__ECL_ASSERT1__(m_nCount >= 0);  // make sure we don't underflow

   	// if no more elements, cleanup completely
   	if (m_nCount == 0)
   		removeAll();
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::addHead(ARG_TYPE newElement)
   {
   	cNode* pNewNode = NewNode(NULL, m_pNodeHead);
   	pNewNode->data = newElement;
   	if (m_pNodeHead != NULL)
   		m_pNodeHead->pPrev = pNewNode;
   	else
   		m_pNodeTail = pNewNode;
   	m_pNodeHead = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::addTail(ARG_TYPE newElement)
   {
   	cNode* pNewNode = NewNode(m_pNodeTail, NULL);
   	pNewNode->data = newElement;
   	if (m_pNodeTail != NULL)
   		m_pNodeTail->pNext = pNewNode;
   	else
   		m_pNodeHead = pNewNode;
   	m_pNodeTail = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::addHead(cList<TYPE,ARG_TYPE>* pNewList)
   {
   	__ECL_ASSERT1__(pNewList != NULL);

   	// add a list of same elements to head (maintain order)
   	IPOSITION pos = pNewList->getTailPosition();
   	while (pos != NULL)
   		addHead(pNewList->getPrev(pos));
   }

template<class TYPE, class ARG_TYPE>
   void cList<TYPE, ARG_TYPE>::addTail(cList<TYPE,ARG_TYPE>* pNewList)
   {
   	__ECL_ASSERT1__(pNewList != NULL);

   	// add a list of same elements
   	IPOSITION pos = pNewList->getHeadPosition();
   	while (pos != NULL)
   		addTail(pNewList->getNext(pos));
   }

template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::removeHead()
   {
   	__ECL_ASSERT1__(m_pNodeHead != NULL);  // don't call on empty list !!!

   	cNode* pOldNode = m_pNodeHead;
   	TYPE returnValue = pOldNode->data;

   	m_pNodeHead = pOldNode->pNext;
   	if (m_pNodeHead != NULL)
   		m_pNodeHead->pPrev = NULL;
   	else
   		m_pNodeTail = NULL;
   	FreeNode(pOldNode);
   	return returnValue;
   }

template<class TYPE, class ARG_TYPE>
   TYPE cList<TYPE, ARG_TYPE>::removeTail()
   {
   	__ECL_ASSERT1__(m_pNodeTail != NULL);  // don't call on empty list !!!

   	cNode* pOldNode = m_pNodeTail;
   	TYPE returnValue = pOldNode->data;

   	m_pNodeTail = pOldNode->pPrev;
   	if (m_pNodeTail != NULL)
   		m_pNodeTail->pNext = NULL;
   	else
   		m_pNodeHead = NULL;
   	FreeNode(pOldNode);
   	return returnValue;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::insertBefore(IPOSITION position, ARG_TYPE newElement)
   {
   	if (position == NULL)
   		return addHead(newElement); // insert before nothing -> head of the list

   	// Insert it before position
   	cNode* pOldNode = (cNode*) position;
   	cNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
   	pNewNode->data = newElement;

   	if (pOldNode->pPrev != NULL)
   	{
   		pOldNode->pPrev->pNext = pNewNode;
   	}
   	else
   	{
   		__ECL_ASSERT1__(pOldNode == m_pNodeHead);
   		m_pNodeHead = pNewNode;
   	}
   	pOldNode->pPrev = pNewNode;
   	return (IPOSITION) pNewNode;
   }

template<class TYPE, class ARG_TYPE>
   IPOSITION cList<TYPE, ARG_TYPE>::insertAfter(IPOSITION position, ARG_TYPE newElement)
   {
   	if (position == NULL)
   		return addTail(newElement); // insert after nothing -> tail of the list

   	// Insert it before position
   	cNode* pOldNode = (cNode*) position;
   	cNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
   	pNewNode->data = newElement;

   	if (pOldNode->pNext != NULL)
   	{
   		pOldNode->pNext->pPrev = pNewNode;
   	}
   	else
   	{
   		__ECL_ASSERT1__(pOldNode == m_pNodeTail);
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
   		return NULL;  // went too far

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
   	if (pNode == NULL)
   	{
   		pNode = m_pNodeHead;  // start at head
   	}
   	else
   	{
   		pNode = pNode->pNext;  // start after the one specified
   	}

   	for (; pNode != NULL; pNode = pNode->pNext)
   		if (EclCompareElements(&pNode->data, &searchValue))
   			return (IPOSITION)pNode;
   	return NULL;
   }

#endif /*__INTERFACE__*/


#ifdef __TEST_ME__

   #include <iostream.h>

   void main (int argc, char *argv[])
   {
      typedef cList<int,int> MYLIST;

      MYLIST l1, l2;

      l1.addHead(11);
      l1.addHead(12);

      l2.addHead(21);
      l2.addHead(22);
      l2.addHead(23);

      l1.addTail(&l2);

      IPOSITION pos = l1.getHeadPosition();
      while ( pos != NULL ) {
         cout << l1.getNext(pos) << endl;
      }
   }

#endif

