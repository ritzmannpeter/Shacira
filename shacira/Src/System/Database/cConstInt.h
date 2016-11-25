//## begin module%3E00443301DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00443301DA.cm

//## begin module%3E00443301DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00443301DA.cp

//## Module: cConstInt%3E00443301DA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstInt.h

#ifndef cConstInt_h
#define cConstInt_h 1

//## begin module%3E00443301DA.includes preserve=yes
//## end module%3E00443301DA.includes

// cArgument
#include "System/Database/cArgument.h"
//## begin module%3E00443301DA.additionalDeclarations preserve=yes
//## end module%3E00443301DA.additionalDeclarations


//## begin cConstInt%3E00443301DA.preface preserve=yes
//## end cConstInt%3E00443301DA.preface

//## Class: cConstInt%3E00443301DA
//## Category: System::Database%3E0030DC0267
//## Persistence: Persistent
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cConstInt : public cArgument  //## Inherits: <unnamed>%3E00444802C0
{
  //## begin cConstInt%3E00443301DA.initialDeclarations preserve=yes
public:
  //## end cConstInt%3E00443301DA.initialDeclarations

    //## Constructors (generated)
      cConstInt();

      cConstInt(const cConstInt &right);

    //## Constructors (specified)
      //## Operation: cConstInt%1040992362
      cConstInt (LONG_T arg);

    //## Destructor (generated)
      virtual ~cConstInt();


    //## Other Operations (specified)
      //## Operation: GetValue%1042654036
      virtual void GetValue (LONG_T &value);

      //## Operation: GetValue%1088693716
      virtual void GetValue (ULONG_T &value);

      //## Operation: GetValue%1088693717
      virtual void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1042654037
      virtual void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1042654035
      virtual void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693718
      virtual void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1088693719
      virtual void GetValue (PTR_T &value);

  public:
    // Additional Public Declarations
      //## begin cConstInt%3E00443301DA.public preserve=yes
      //## end cConstInt%3E00443301DA.public

  protected:
    // Additional Protected Declarations
      //## begin cConstInt%3E00443301DA.protected preserve=yes
      //## end cConstInt%3E00443301DA.protected

  private:
    // Additional Private Declarations
      //## begin cConstInt%3E00443301DA.private preserve=yes
      //## end cConstInt%3E00443301DA.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Value%3E25A4660175
      //## begin cConstInt::Value%3E25A4660175.attr preserve=no  implementation: LONG_T {U} 
      LONG_T _Value;
      //## end cConstInt::Value%3E25A4660175.attr

    // Additional Implementation Declarations
      //## begin cConstInt%3E00443301DA.implementation preserve=yes
      //## end cConstInt%3E00443301DA.implementation

};

//## begin cConstInt%3E00443301DA.postscript preserve=yes
//## end cConstInt%3E00443301DA.postscript

// Class cConstInt 

//## begin module%3E00443301DA.epilog preserve=yes
//## end module%3E00443301DA.epilog


#endif
