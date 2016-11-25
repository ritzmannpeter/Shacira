//## begin module%3FBC9F5C033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBC9F5C033C.cm

//## begin module%3FBC9F5C033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBC9F5C033C.cp

//## Module: cMultiplexer%3FBC9F5C033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cMultiplexer.h

#ifndef cMultiplexer_h
#define cMultiplexer_h 1

//## begin module%3FBC9F5C033C.includes preserve=yes
//## end module%3FBC9F5C033C.includes


class __DLL_EXPORT__ cSerialBridge;

//## begin module%3FBC9F5C033C.additionalDeclarations preserve=yes
//## end module%3FBC9F5C033C.additionalDeclarations


//## begin cMultiplexer%3FBC9F5C033C.preface preserve=yes
//## end cMultiplexer%3FBC9F5C033C.preface

//## Class: cMultiplexer%3FBC9F5C033C
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cMultiplexer 
{
  //## begin cMultiplexer%3FBC9F5C033C.initialDeclarations preserve=yes
public:
  //## end cMultiplexer%3FBC9F5C033C.initialDeclarations

    //## Constructors (generated)
      cMultiplexer();

      cMultiplexer(const cMultiplexer &right);

    //## Destructor (generated)
      virtual ~cMultiplexer();


    //## Other Operations (specified)
      //## Operation: AddBridge%1069326591
      void AddBridge (CONST_STRING_T name, cSerialBridge *bridge);

  public:
    // Additional Public Declarations
      //## begin cMultiplexer%3FBC9F5C033C.public preserve=yes
      //## end cMultiplexer%3FBC9F5C033C.public

  protected:
    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3FBCA00E00CB
      //## Role: cMultiplexer::Bridges%3FBCA00F01F4
      //## Qualifier: name%3FBCA03102AF; STRING_T
      //## begin cMultiplexer::Bridges%3FBCA00F01F4.role preserve=no  public: cSerialBridge { -> 1RFHN}
      std::map<STRING_T, cSerialBridge*> _Bridges;
      //## end cMultiplexer::Bridges%3FBCA00F01F4.role

    // Additional Protected Declarations
      //## begin cMultiplexer%3FBC9F5C033C.protected preserve=yes
      //## end cMultiplexer%3FBC9F5C033C.protected

  private:
    // Additional Private Declarations
      //## begin cMultiplexer%3FBC9F5C033C.private preserve=yes
      //## end cMultiplexer%3FBC9F5C033C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cMultiplexer%3FBC9F5C033C.implementation preserve=yes
      //## end cMultiplexer%3FBC9F5C033C.implementation

};

//## begin cMultiplexer%3FBC9F5C033C.postscript preserve=yes
//## end cMultiplexer%3FBC9F5C033C.postscript

// Class cMultiplexer 

//## begin module%3FBC9F5C033C.epilog preserve=yes
//## end module%3FBC9F5C033C.epilog


#endif
