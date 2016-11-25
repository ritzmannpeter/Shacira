//## begin module%43141D1003BE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43141D1003BE.cm

//## begin module%43141D1003BE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43141D1003BE.cp

//## Module: cRequestHandler%43141D1003BE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cRequestHandler.h

#ifndef cRequestHandler_h
#define cRequestHandler_h 1

//## begin module%43141D1003BE.includes preserve=yes
//## end module%43141D1003BE.includes


class __DLL_EXPORT__ cSHProcess;

//## begin module%43141D1003BE.additionalDeclarations preserve=yes

#define OPC_HANDLER     1

//## end module%43141D1003BE.additionalDeclarations


//## begin cRequestHandler%43141D1003BE.preface preserve=yes
//## end cRequestHandler%43141D1003BE.preface

//## Class: cRequestHandler%43141D1003BE
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cRequestHandler 
{
  //## begin cRequestHandler%43141D1003BE.initialDeclarations preserve=yes
public:
  //## end cRequestHandler%43141D1003BE.initialDeclarations

    //## Constructors (generated)
      cRequestHandler();

      cRequestHandler(const cRequestHandler &right);

    //## Constructors (specified)
      //## Operation: cRequestHandler%1125391950
      cRequestHandler (cSHProcess *process, CONST_STRING_T handler_name);

    //## Destructor (generated)
      virtual ~cRequestHandler();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%43141EB1032D
      STRING_T get_Name () const;
      void set_Name (STRING_T value);

      //## Attribute: Type%43141ECD030E
      UCHAR_T get_Type () const;
      void set_Type (UCHAR_T value);

  public:
    // Additional Public Declarations
      //## begin cRequestHandler%43141D1003BE.public preserve=yes
      //## end cRequestHandler%43141D1003BE.public

  protected:
    // Data Members for Class Attributes

      //## begin cRequestHandler::Name%43141EB1032D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cRequestHandler::Name%43141EB1032D.attr

      //## begin cRequestHandler::Type%43141ECD030E.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _Type;
      //## end cRequestHandler::Type%43141ECD030E.attr

    // Data Members for Associations

      //## Association: System::Process::<unnamed>%43141D3E0004
      //## Role: cRequestHandler::Process%43141D3F00FF
      //## begin cRequestHandler::Process%43141D3F00FF.role preserve=no  public: cSHProcess {0..n -> 1RFHN}
      cSHProcess *_Process;
      //## end cRequestHandler::Process%43141D3F00FF.role

    // Additional Protected Declarations
      //## begin cRequestHandler%43141D1003BE.protected preserve=yes
      //## end cRequestHandler%43141D1003BE.protected

  private:
    // Additional Private Declarations
      //## begin cRequestHandler%43141D1003BE.private preserve=yes
      //## end cRequestHandler%43141D1003BE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cRequestHandler%43141D1003BE.implementation preserve=yes
      //## end cRequestHandler%43141D1003BE.implementation

};

//## begin cRequestHandler%43141D1003BE.postscript preserve=yes
//## end cRequestHandler%43141D1003BE.postscript

// Class cRequestHandler 

//## begin module%43141D1003BE.epilog preserve=yes
//## end module%43141D1003BE.epilog


#endif
