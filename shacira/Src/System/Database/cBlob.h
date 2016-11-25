//## begin module%402C8232033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%402C8232033C.cm

//## begin module%402C8232033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%402C8232033C.cp

//## Module: cBlob%402C8232033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cBlob.h

#ifndef cBlob_h
#define cBlob_h 1

//## begin module%402C8232033C.includes preserve=yes
//## end module%402C8232033C.includes

// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
//## begin module%402C8232033C.additionalDeclarations preserve=yes
//## end module%402C8232033C.additionalDeclarations


//## begin cBlob%402C8232033C.preface preserve=yes
//## end cBlob%402C8232033C.preface

//## Class: cBlob%402C8232033C
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%402C82ED0232;cMemoryPtr { -> }

class __DLL_EXPORT__ cBlob 
{
  //## begin cBlob%402C8232033C.initialDeclarations preserve=yes
public:
  //## end cBlob%402C8232033C.initialDeclarations

    //## Constructors (generated)
      cBlob();

      cBlob(const cBlob &right);

    //## Constructors (specified)
      //## Operation: cBlob%1076659058
      cBlob (BUF_T buf, ULONG_T buf_size);

    //## Destructor (generated)
      virtual ~cBlob();


    //## Other Operations (specified)
      //## Operation: Serialize%1076659059
      STRING_T Serialize ();

      //## Operation: Construct%1076659060
      void Construct (CONST_STRING_T serialized_object);

  public:
    // Additional Public Declarations
      //## begin cBlob%402C8232033C.public preserve=yes
      //## end cBlob%402C8232033C.public

  protected:
    // Additional Protected Declarations
      //## begin cBlob%402C8232033C.protected preserve=yes
      //## end cBlob%402C8232033C.protected

  private:
    // Additional Private Declarations
      //## begin cBlob%402C8232033C.private preserve=yes
      //## end cBlob%402C8232033C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SerializeBuf%1076659061
      STRING_T SerializeBuf ();

      //## Operation: ConstructBuf%1076659062
      void ConstructBuf (CONST_STRING_T buf_ptr);

      //## Operation: DeleteBuf%1076659063
      void DeleteBuf ();

    // Data Members for Class Attributes

      //## Attribute: Buf%402C829D03D8
      //## begin cBlob::Buf%402C829D03D8.attr preserve=no  implementation: cMemoryPtr * {U} NULL
      cMemoryPtr *_Buf;
      //## end cBlob::Buf%402C829D03D8.attr

      //## Attribute: BufSize%402C82CE03A9
      //## begin cBlob::BufSize%402C82CE03A9.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _BufSize;
      //## end cBlob::BufSize%402C82CE03A9.attr

    // Additional Implementation Declarations
      //## begin cBlob%402C8232033C.implementation preserve=yes
      //## end cBlob%402C8232033C.implementation

};

//## begin cBlob%402C8232033C.postscript preserve=yes
//## end cBlob%402C8232033C.postscript

// Class cBlob 

//## begin module%402C8232033C.epilog preserve=yes
//## end module%402C8232033C.epilog


#endif
