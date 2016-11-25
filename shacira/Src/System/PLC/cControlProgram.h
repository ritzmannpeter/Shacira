//## begin module%3F38BBF8033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BBF8033C.cm

//## begin module%3F38BBF8033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BBF8033C.cp

//## Module: cControlProgram%3F38BBF8033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlProgram.h

#ifndef cControlProgram_h
#define cControlProgram_h 1

//## begin module%3F38BBF8033C.includes preserve=yes
//## end module%3F38BBF8033C.includes


class __DLL_EXPORT__ cContext;

//## begin module%3F38BBF8033C.additionalDeclarations preserve=yes
//## end module%3F38BBF8033C.additionalDeclarations


//## begin cControlProgram%3F38BBF8033C.preface preserve=yes
//## end cControlProgram%3F38BBF8033C.preface

//## Class: cControlProgram%3F38BBF8033C
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F38BC9F0222;cContext { -> F}

class __DLL_EXPORT__ cControlProgram 
{
  //## begin cControlProgram%3F38BBF8033C.initialDeclarations preserve=yes
public:
  //## end cControlProgram%3F38BBF8033C.initialDeclarations

    //## Constructors (generated)
      cControlProgram();

      cControlProgram(const cControlProgram &right);

    //## Constructors (specified)
      //## Operation: cControlProgram%1060960063
      cControlProgram (CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cControlProgram();


    //## Other Operations (specified)
      //## Operation: Name%1060960061
      STRING_T Name ();

  public:
    // Additional Public Declarations
      //## begin cControlProgram%3F38BBF8033C.public preserve=yes
      //## end cControlProgram%3F38BBF8033C.public

  protected:
    // Additional Protected Declarations
      //## begin cControlProgram%3F38BBF8033C.protected preserve=yes
      //## end cControlProgram%3F38BBF8033C.protected

  private:
    // Additional Private Declarations
      //## begin cControlProgram%3F38BBF8033C.private preserve=yes
      //## end cControlProgram%3F38BBF8033C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Name%3F38C1EA01F4
      //## begin cControlProgram::Name%3F38C1EA01F4.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Name;
      //## end cControlProgram::Name%3F38C1EA01F4.attr

    // Additional Implementation Declarations
      //## begin cControlProgram%3F38BBF8033C.implementation preserve=yes
      //## end cControlProgram%3F38BBF8033C.implementation

};

//## begin cControlProgram%3F38BBF8033C.postscript preserve=yes
//## end cControlProgram%3F38BBF8033C.postscript

// Class cControlProgram 

//## begin module%3F38BBF8033C.epilog preserve=yes
//## end module%3F38BBF8033C.epilog


#endif
