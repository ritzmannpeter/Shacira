//## begin module%3A4A1F5D0137.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A4A1F5D0137.cm

//## begin module%3A4A1F5D0137.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A4A1F5D0137.cp

//## Module: cMemoryPtr%3A4A1F5D0137; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cMemoryPtr.h

#ifndef cMemoryPtr_h
#define cMemoryPtr_h 1

//## begin module%3A4A1F5D0137.includes preserve=yes
//## end module%3A4A1F5D0137.includes

//## begin module%3A4A1F5D0137.additionalDeclarations preserve=yes
//## end module%3A4A1F5D0137.additionalDeclarations


//## begin cMemoryPtr%3A4A1F5D0137.preface preserve=yes
//## end cMemoryPtr%3A4A1F5D0137.preface

//## Class: cMemoryPtr%3A4A1F5D0137
//	Implements a resizable block of memory.
//## Category: System::Memory%3DC92B0D00DE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cMemoryPtr 
{
  //## begin cMemoryPtr%3A4A1F5D0137.initialDeclarations preserve=yes
public:
  //## end cMemoryPtr%3A4A1F5D0137.initialDeclarations

    //## Constructors (generated)
      cMemoryPtr();

      cMemoryPtr(const cMemoryPtr &right);

    //## Constructors (specified)
      //## Operation: cMemoryPtr%977931300
      cMemoryPtr (ULONG_T size);

    //## Destructor (generated)
      virtual ~cMemoryPtr();


    //## Other Operations (specified)
      //## Operation: Size%977931299
      ULONG_T Size () const;

      //## Operation: Size%977993518
      void Size (ULONG_T size);

      //## Operation: AdjustSize%1137931252
      void AdjustSize (ULONG_T size, BOOL_T keep_data = false);

      //## Operation: Clear%977993522
      void Clear ();

      //## Operation: Memory%1000308658
      void * Memory ();

      //## Operation: operator CHAR_T *%978080755
      operator CHAR_T * () const;

      //## Operation: operator UCHAR_T *%978080756
      operator UCHAR_T * () const;

      //## Operation: operator void *%978080757
      operator void * () const;

  public:
    // Additional Public Declarations
      //## begin cMemoryPtr%3A4A1F5D0137.public preserve=yes
      //## end cMemoryPtr%3A4A1F5D0137.public

  protected:
    // Additional Protected Declarations
      //## begin cMemoryPtr%3A4A1F5D0137.protected preserve=yes
      //## end cMemoryPtr%3A4A1F5D0137.protected

  private:
    // Additional Private Declarations
      //## begin cMemoryPtr%3A4A1F5D0137.private preserve=yes
      //## end cMemoryPtr%3A4A1F5D0137.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Buffer%3A4A21400041
      //## begin cMemoryPtr::Buffer%3A4A21400041.attr preserve=no  implementation: UCHAR_T * {U} NULL
      UCHAR_T *_Buffer;
      //## end cMemoryPtr::Buffer%3A4A21400041.attr

      //## Attribute: Size%3A4A1F850315
      //## begin cMemoryPtr::Size%3A4A1F850315.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Size;
      //## end cMemoryPtr::Size%3A4A1F850315.attr

    // Additional Implementation Declarations
      //## begin cMemoryPtr%3A4A1F5D0137.implementation preserve=yes
      //## end cMemoryPtr%3A4A1F5D0137.implementation

};

//## begin cMemoryPtr%3A4A1F5D0137.postscript preserve=yes
//## end cMemoryPtr%3A4A1F5D0137.postscript

// Class cMemoryPtr 

//## begin module%3A4A1F5D0137.epilog preserve=yes
//## end module%3A4A1F5D0137.epilog


#endif
