//## begin module%3E9EA7C2029F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E9EA7C2029F.cm

//## begin module%3E9EA7C2029F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E9EA7C2029F.cp

//## Module: cBlockBuffer%3E9EA7C2029F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cBlockBuffer.h

#ifndef cBlockBuffer_h
#define cBlockBuffer_h 1

//## begin module%3E9EA7C2029F.includes preserve=yes
//## end module%3E9EA7C2029F.includes


class __DLL_EXPORT__ cSHVariant;

//## begin module%3E9EA7C2029F.additionalDeclarations preserve=yes

typedef std::list<void*> BUFFER_LIST_T;

//## end module%3E9EA7C2029F.additionalDeclarations


//## begin cBlockBuffer%3E9EA7C2029F.preface preserve=yes
//## end cBlockBuffer%3E9EA7C2029F.preface

//## Class: cBlockBuffer%3E9EA7C2029F
//	Implements a block buffer that returns memory blocks of
//	a certain size. The blocks are allocated in heap space.
//## Category: System::Memory%3DC92B0D00DE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F4A27D5005D;cSHVariant { -> F}

class __DLL_EXPORT__ cBlockBuffer 
{
  //## begin cBlockBuffer%3E9EA7C2029F.initialDeclarations preserve=yes
public:
  //## end cBlockBuffer%3E9EA7C2029F.initialDeclarations

    //## Constructors (generated)
      cBlockBuffer();

      cBlockBuffer(const cBlockBuffer &right);

    //## Destructor (generated)
      virtual ~cBlockBuffer();


    //## Other Operations (specified)
      //## Operation: AllocBlock%1050587414
      void * AllocBlock (ULONG_T size);

      //## Operation: AllocString%1050584918
      CONST_STRING_T AllocString (CONST_STRING_T str);

      //## Operation: AllocString%1061824379
      CONST_WSTRING_T AllocString (CONST_WSTRING_T str);

  public:
    // Additional Public Declarations
      //## begin cBlockBuffer%3E9EA7C2029F.public preserve=yes
      //## end cBlockBuffer%3E9EA7C2029F.public

  protected:
    // Additional Protected Declarations
      //## begin cBlockBuffer%3E9EA7C2029F.protected preserve=yes
      //## end cBlockBuffer%3E9EA7C2029F.protected

  private:
    // Additional Private Declarations
      //## begin cBlockBuffer%3E9EA7C2029F.private preserve=yes
      //## end cBlockBuffer%3E9EA7C2029F.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Buffers%3E9EA8ED0119
      //## begin cBlockBuffer::Buffers%3E9EA8ED0119.attr preserve=no  private: BUFFER_LIST_T {U} 
      BUFFER_LIST_T _Buffers;
      //## end cBlockBuffer::Buffers%3E9EA8ED0119.attr

    // Additional Implementation Declarations
      //## begin cBlockBuffer%3E9EA7C2029F.implementation preserve=yes
      //## end cBlockBuffer%3E9EA7C2029F.implementation

};

//## begin cBlockBuffer%3E9EA7C2029F.postscript preserve=yes
//## end cBlockBuffer%3E9EA7C2029F.postscript

// Class cBlockBuffer 

//## begin module%3E9EA7C2029F.epilog preserve=yes
//## end module%3E9EA7C2029F.epilog


#endif
