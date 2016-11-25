//## begin module%3D0D9834032B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D0D9834032B.cm

//## begin module%3D0D9834032B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D0D9834032B.cp

//## Module: cPtrList%3D0D9834032B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cPtrList.h

#ifndef cPtrList_h
#define cPtrList_h 1

//## begin module%3D0D9834032B.includes preserve=yes
//## end module%3D0D9834032B.includes

//## begin module%3D0D9834032B.additionalDeclarations preserve=yes

typedef struct list_entry
{
   void * ptr;
   struct list_entry * next;
}  list_entry_t;
typedef struct list_entry PTR_LIST_ENTRY_T;

//## end module%3D0D9834032B.additionalDeclarations


//## begin cPtrList%3D0D9834032B.preface preserve=yes
//## end cPtrList%3D0D9834032B.preface

//## Class: cPtrList%3D0D9834032B
//	Implements a list of pointers to whatever memory.
//## Category: System::Memory%3DC92B0D00DE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPtrList 
{
  //## begin cPtrList%3D0D9834032B.initialDeclarations preserve=yes
public:
  //## end cPtrList%3D0D9834032B.initialDeclarations

    //## begin cPtrList::cConstIterator%3D0D98B20119.preface preserve=yes
    //## end cPtrList::cConstIterator%3D0D98B20119.preface

    //## Class: cConstIterator%3D0D98B20119
    //## Category: System::Memory%3DC92B0D00DE
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    class __DLL_EXPORT__ cConstIterator 
    {
      //## begin cPtrList::cConstIterator%3D0D98B20119.initialDeclarations preserve=yes
public:
      //## end cPtrList::cConstIterator%3D0D98B20119.initialDeclarations

        //## Constructors (generated)
          cConstIterator();

          cConstIterator(const cConstIterator &right);

        //## Constructors (specified)
          //## Operation: cConstIterator%1024301711
          cConstIterator (cPtrList *ptr_list, PTR_LIST_ENTRY_T *entry);

        //## Destructor (generated)
          virtual ~cConstIterator();


        //## Other Operations (specified)
          //## Operation: First%1024301704
          BOOL_T First ();

          //## Operation: Next%1024301705
          BOOL_T Next ();

          //## Operation: Ptr%1024301706
          void * Ptr ();

      public:
        // Additional Public Declarations
          //## begin cPtrList::cConstIterator%3D0D98B20119.public preserve=yes
          //## end cPtrList::cConstIterator%3D0D98B20119.public

      protected:
        // Additional Protected Declarations
          //## begin cPtrList::cConstIterator%3D0D98B20119.protected preserve=yes
          //## end cPtrList::cConstIterator%3D0D98B20119.protected

      private:
        // Additional Private Declarations
          //## begin cPtrList::cConstIterator%3D0D98B20119.private preserve=yes
          //## end cPtrList::cConstIterator%3D0D98B20119.private

      private: //## implementation
        // Data Members for Class Attributes

          //## Attribute: First%3D0DC11C03D3
          //## begin cPtrList::cConstIterator::First%3D0DC11C03D3.attr preserve=no  implementation: PTR_LIST_ENTRY_T * {U} NULL
          PTR_LIST_ENTRY_T *_First;
          //## end cPtrList::cConstIterator::First%3D0DC11C03D3.attr

          //## Attribute: Entry%3D0D9C300061
          //## begin cPtrList::cConstIterator::Entry%3D0D9C300061.attr preserve=no  implementation: PTR_LIST_ENTRY_T * {U} NULL
          PTR_LIST_ENTRY_T *_Entry;
          //## end cPtrList::cConstIterator::Entry%3D0D9C300061.attr

          //## Attribute: PtrList%46B8847E0361
          //## begin cPtrList::cConstIterator::PtrList%46B8847E0361.attr preserve=no  implementation: cPtrList * {U} NULL
          cPtrList *_PtrList;
          //## end cPtrList::cConstIterator::PtrList%46B8847E0361.attr

        // Additional Implementation Declarations
          //## begin cPtrList::cConstIterator%3D0D98B20119.implementation preserve=yes
          //## end cPtrList::cConstIterator%3D0D98B20119.implementation

    };

    //## begin cPtrList::cConstIterator%3D0D98B20119.postscript preserve=yes
    //## end cPtrList::cConstIterator%3D0D98B20119.postscript

    //## Constructors (generated)
      cPtrList();

      cPtrList(const cPtrList &right);

    //## Destructor (generated)
      virtual ~cPtrList();


    //## Other Operations (specified)
      //## Operation: Add%1024301707
      //	Adds a pointer to the list (oush back operator).
      void Add (void *ptr);

      //## Operation: Remove%1024301708
      //	Removes a pointer from the list.
      void Remove (void *ptr);

      //## Operation: Clear%1073642250
      //	Clears the pointer list.
      void Clear ();

      //## Operation: Size%1024301710
      //	Returns the current size (number of pointers in the
      //	list).
      ULONG_T Size ();

      //## Operation: Begin%1024301709
      //	Returns a const iterator to the list taht begins with
      //	the first element.
      cPtrList::cConstIterator Begin ();

  public:
    // Additional Public Declarations
      //## begin cPtrList%3D0D9834032B.public preserve=yes
      //## end cPtrList%3D0D9834032B.public

  protected:
    // Additional Protected Declarations
      //## begin cPtrList%3D0D9834032B.protected preserve=yes
      //## end cPtrList%3D0D9834032B.protected

  private:
    // Additional Private Declarations
      //## begin cPtrList%3D0D9834032B.private preserve=yes
      //## end cPtrList%3D0D9834032B.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Lock%1186497422
      void Lock ();

      //## Operation: Unlock%1186497423
      void Unlock ();

    // Data Members for Class Attributes

      //## Attribute: First%3D0D9BB00342
      //## begin cPtrList::First%3D0D9BB00342.attr preserve=no  implementation: PTR_LIST_ENTRY_T * {U} NULL
      PTR_LIST_ENTRY_T *_First;
      //## end cPtrList::First%3D0D9BB00342.attr

      //## Attribute: Last%3D0DBCE203AF
      //## begin cPtrList::Last%3D0DBCE203AF.attr preserve=no  implementation: PTR_LIST_ENTRY_T * {U} NULL
      PTR_LIST_ENTRY_T *_Last;
      //## end cPtrList::Last%3D0DBCE203AF.attr

      //## Attribute: Size%3D0DBCA1029D
      //## begin cPtrList::Size%3D0DBCA1029D.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Size;
      //## end cPtrList::Size%3D0DBCA1029D.attr

      //## Attribute: ListMutex%46B882FF027B
      //## begin cPtrList::ListMutex%46B882FF027B.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _ListMutex;
      //## end cPtrList::ListMutex%46B882FF027B.attr

    // Additional Implementation Declarations
      //## begin cPtrList%3D0D9834032B.implementation preserve=yes
      friend class cPtrList::cConstIterator;
      //## end cPtrList%3D0D9834032B.implementation

};

//## begin cPtrList%3D0D9834032B.postscript preserve=yes
//## end cPtrList%3D0D9834032B.postscript

// Class cPtrList::cConstIterator 

// Class cPtrList 

//## begin module%3D0D9834032B.epilog preserve=yes
//## end module%3D0D9834032B.epilog


#endif
