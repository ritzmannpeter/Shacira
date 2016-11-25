//## begin module%3D0D9834032B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D0D9834032B.cm

//## begin module%3D0D9834032B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D0D9834032B.cp

//## Module: cPtrList%3D0D9834032B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cPtrList.cpp

//## begin module%3D0D9834032B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D0D9834032B.additionalIncludes

//## begin module%3D0D9834032B.includes preserve=yes
//## end module%3D0D9834032B.includes

// cPtrList
#include "System/Memory/cPtrList.h"
//## begin module%3D0D9834032B.additionalDeclarations preserve=yes

#define AllocEntry()          ((PTR_LIST_ENTRY_T*)cSystemUtils::Alloc(sizeof(PTR_LIST_ENTRY_T)))
#define DeleteEntry(entry)    (cSystemUtils::Free(entry))

//## end module%3D0D9834032B.additionalDeclarations


// Class cPtrList::cConstIterator 




cPtrList::cConstIterator::cConstIterator()
  //## begin cConstIterator::cConstIterator%.hasinit preserve=no
      : _First(NULL), _Entry(NULL), _PtrList(NULL)
  //## end cConstIterator::cConstIterator%.hasinit
  //## begin cConstIterator::cConstIterator%.initialization preserve=yes
  //## end cConstIterator::cConstIterator%.initialization
{
  //## begin cPtrList::cConstIterator::cConstIterator%.body preserve=yes
_ASSERT_UNCOND
  //## end cPtrList::cConstIterator::cConstIterator%.body
}

cPtrList::cConstIterator::cConstIterator(const cPtrList::cConstIterator &right)
  //## begin cConstIterator::cConstIterator%copy.hasinit preserve=no
      : _First(NULL), _Entry(NULL), _PtrList(NULL)
  //## end cConstIterator::cConstIterator%copy.hasinit
  //## begin cConstIterator::cConstIterator%copy.initialization preserve=yes
  //## end cConstIterator::cConstIterator%copy.initialization
{
  //## begin cPtrList::cConstIterator::cConstIterator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPtrList::cConstIterator::cConstIterator%copy.body
}

cPtrList::cConstIterator::cConstIterator (cPtrList *ptr_list, PTR_LIST_ENTRY_T *entry)
  //## begin cPtrList::cConstIterator::cConstIterator%1024301711.hasinit preserve=no
      : _First(NULL), _Entry(NULL), _PtrList(NULL)
  //## end cPtrList::cConstIterator::cConstIterator%1024301711.hasinit
  //## begin cPtrList::cConstIterator::cConstIterator%1024301711.initialization preserve=yes
  //## end cPtrList::cConstIterator::cConstIterator%1024301711.initialization
{
  //## begin cPtrList::cConstIterator::cConstIterator%1024301711.body preserve=yes
   ptr_list->Lock();
   _PtrList = ptr_list;
   _First = _Entry = entry;
  //## end cPtrList::cConstIterator::cConstIterator%1024301711.body
}


cPtrList::cConstIterator::~cConstIterator()
{
  //## begin cPtrList::cConstIterator::~cConstIterator%.body preserve=yes
   _PtrList->Unlock();
  //## end cPtrList::cConstIterator::~cConstIterator%.body
}



//## Other Operations (implementation)
BOOL_T cPtrList::cConstIterator::First ()
{
  //## begin cPtrList::cConstIterator::First%1024301704.body preserve=yes
   if (_First != NULL) {
      _Entry = _First;
      return true;
   } else {
      return false;
   }
  //## end cPtrList::cConstIterator::First%1024301704.body
}

BOOL_T cPtrList::cConstIterator::Next ()
{
  //## begin cPtrList::cConstIterator::Next%1024301705.body preserve=yes
   if (_Entry != NULL) {
      _Entry = _Entry->next;
      return (_Entry != NULL);
   } else {
      return false;
   }
  //## end cPtrList::cConstIterator::Next%1024301705.body
}

void * cPtrList::cConstIterator::Ptr ()
{
  //## begin cPtrList::cConstIterator::Ptr%1024301706.body preserve=yes
   if (_Entry == NULL) return NULL;
   return _Entry->ptr;
  //## end cPtrList::cConstIterator::Ptr%1024301706.body
}

// Additional Declarations
  //## begin cPtrList::cConstIterator%3D0D98B20119.declarations preserve=yes
  //## end cPtrList::cConstIterator%3D0D98B20119.declarations

// Class cPtrList 





cPtrList::cPtrList()
  //## begin cPtrList::cPtrList%.hasinit preserve=no
      : _First(NULL), _Last(NULL), _Size(0)
  //## end cPtrList::cPtrList%.hasinit
  //## begin cPtrList::cPtrList%.initialization preserve=yes
  //## end cPtrList::cPtrList%.initialization
{
  //## begin cPtrList::cPtrList%.body preserve=yes
  //## end cPtrList::cPtrList%.body
}

cPtrList::cPtrList(const cPtrList &right)
  //## begin cPtrList::cPtrList%copy.hasinit preserve=no
      : _First(NULL), _Last(NULL), _Size(0)
  //## end cPtrList::cPtrList%copy.hasinit
  //## begin cPtrList::cPtrList%copy.initialization preserve=yes
  //## end cPtrList::cPtrList%copy.initialization
{
  //## begin cPtrList::cPtrList%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPtrList::cPtrList%copy.body
}


cPtrList::~cPtrList()
{
  //## begin cPtrList::~cPtrList%.body preserve=yes
   PTR_LIST_ENTRY_T * next = _First;
   PTR_LIST_ENTRY_T * entry = _First;
   if (entry == NULL) return;
   while (entry != NULL) {
      next = entry->next;
      DeleteEntry(entry);
      entry = next;
   }
  //## end cPtrList::~cPtrList%.body
}



//## Other Operations (implementation)
void cPtrList::Add (void *ptr)
{
  //## begin cPtrList::Add%1024301707.body preserve=yes
   cObjectLock __lock__(&_ListMutex);
   PTR_LIST_ENTRY_T * prev = _First;
   PTR_LIST_ENTRY_T * entry = _First;
   if (entry == NULL) {
      entry = AllocEntry();
      entry->ptr = ptr;
      _Last = _First = entry;
      _Size++;
   } else {
      do {
         if (entry->ptr == ptr) {
            return;
         }
         prev = entry;
         entry = entry->next;
      } while (entry != NULL);
      if (prev != NULL) {
         PTR_LIST_ENTRY_T * new_entry = AllocEntry();
         new_entry->ptr = ptr;
         prev->next = new_entry;
         _Last = new_entry;
         _Size++;
      }
   }
  //## end cPtrList::Add%1024301707.body
}

void cPtrList::Remove (void *ptr)
{
  //## begin cPtrList::Remove%1024301708.body preserve=yes
   cObjectLock __lock__(&_ListMutex);
   PTR_LIST_ENTRY_T * prev = NULL;
   PTR_LIST_ENTRY_T * entry = _First;
   if (entry == NULL) {
      return;
   }
   do {
      if (entry->ptr == ptr) {
         if (entry->next == NULL) {
            _Last = prev;
         }
         if (prev == NULL) {
            _First = entry->next;
         } else {
            prev->next = entry->next;
         }
         DeleteEntry(entry);
         _Size--;
         return;
      }
      prev = entry;
      entry = entry->next;
   } while (entry != NULL);
  //## end cPtrList::Remove%1024301708.body
}

void cPtrList::Clear ()
{
  //## begin cPtrList::Clear%1073642250.body preserve=yes
   cObjectLock __lock__(&_ListMutex);
  //## end cPtrList::Clear%1073642250.body
}

ULONG_T cPtrList::Size ()
{
  //## begin cPtrList::Size%1024301710.body preserve=yes
   return _Size;
  //## end cPtrList::Size%1024301710.body
}

cPtrList::cConstIterator cPtrList::Begin ()
{
  //## begin cPtrList::Begin%1024301709.body preserve=yes
   cObjectLock __lock__(&_ListMutex);
   return cConstIterator(this, _First);
  //## end cPtrList::Begin%1024301709.body
}

void cPtrList::Lock ()
{
  //## begin cPtrList::Lock%1186497422.body preserve=yes
   _ListMutex.request();
  //## end cPtrList::Lock%1186497422.body
}

void cPtrList::Unlock ()
{
  //## begin cPtrList::Unlock%1186497423.body preserve=yes
   _ListMutex.release();
  //## end cPtrList::Unlock%1186497423.body
}

// Additional Declarations
  //## begin cPtrList%3D0D9834032B.declarations preserve=yes
  //## end cPtrList%3D0D9834032B.declarations

//## begin module%3D0D9834032B.epilog preserve=yes
//## end module%3D0D9834032B.epilog
