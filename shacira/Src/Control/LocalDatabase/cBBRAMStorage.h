//## begin module%403A0EFB0290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%403A0EFB0290.cm

//## begin module%403A0EFB0290.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%403A0EFB0290.cp

//## Module: cBBRAMStorage%403A0EFB0290; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cBBRAMStorage.h

#ifndef cBBRAMStorage_h
#define cBBRAMStorage_h 1

//## begin module%403A0EFB0290.includes preserve=yes
//## end module%403A0EFB0290.includes

// cStorage
#include "Control/LocalDatabase/cStorage.h"
//## begin module%403A0EFB0290.additionalDeclarations preserve=yes
//## end module%403A0EFB0290.additionalDeclarations


//## begin cBBRAMStorage%403A0EFB0290.preface preserve=yes
//## end cBBRAMStorage%403A0EFB0290.preface

//## Class: cBBRAMStorage%403A0EFB0290
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cBBRAMStorage : public cStorage  //## Inherits: <unnamed>%403A0F1902FD
{
  //## begin cBBRAMStorage%403A0EFB0290.initialDeclarations preserve=yes
public:
  //## end cBBRAMStorage%403A0EFB0290.initialDeclarations

    //## Constructors (generated)
      cBBRAMStorage();

      cBBRAMStorage(const cBBRAMStorage &right);

    //## Destructor (generated)
      virtual ~cBBRAMStorage();


    //## Other Operations (specified)
      //## Operation: SetUp%1077542665
      virtual void SetUp ();

      //## Operation: WriteThrough%1077548350
      virtual void WriteThrough (BUF_T buffer, ULONG_T address, ULONG_T size);

  public:
    // Additional Public Declarations
      //## begin cBBRAMStorage%403A0EFB0290.public preserve=yes
      //## end cBBRAMStorage%403A0EFB0290.public

  protected:
    // Additional Protected Declarations
      //## begin cBBRAMStorage%403A0EFB0290.protected preserve=yes
      //## end cBBRAMStorage%403A0EFB0290.protected

  private:
    // Additional Private Declarations
      //## begin cBBRAMStorage%403A0EFB0290.private preserve=yes
      //## end cBBRAMStorage%403A0EFB0290.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cBBRAMStorage%403A0EFB0290.implementation preserve=yes
      //## end cBBRAMStorage%403A0EFB0290.implementation

};

//## begin cBBRAMStorage%403A0EFB0290.postscript preserve=yes
//## end cBBRAMStorage%403A0EFB0290.postscript

// Class cBBRAMStorage 

//## begin module%403A0EFB0290.epilog preserve=yes
//## end module%403A0EFB0290.epilog


#endif
