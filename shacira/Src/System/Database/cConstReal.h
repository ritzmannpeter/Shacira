//## begin module%3E00444D03D6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00444D03D6.cm

//## begin module%3E00444D03D6.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00444D03D6.cp

//## Module: cConstReal%3E00444D03D6; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstReal.h

#ifndef cConstReal_h
#define cConstReal_h 1

//## begin module%3E00444D03D6.includes preserve=yes
//## end module%3E00444D03D6.includes

// cArgument
#include "System/Database/cArgument.h"
//## begin module%3E00444D03D6.additionalDeclarations preserve=yes
//## end module%3E00444D03D6.additionalDeclarations


//## begin cConstReal%3E00444D03D6.preface preserve=yes
//## end cConstReal%3E00444D03D6.preface

//## Class: cConstReal%3E00444D03D6
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cConstReal : public cArgument  //## Inherits: <unnamed>%3E0044620119
{
  //## begin cConstReal%3E00444D03D6.initialDeclarations preserve=yes
public:
  //## end cConstReal%3E00444D03D6.initialDeclarations

    //## Constructors (generated)
      cConstReal();

      cConstReal(const cConstReal &right);

    //## Constructors (specified)
      //## Operation: cConstReal%1040992361
      cConstReal (DOUBLE_T arg);

    //## Destructor (generated)
      virtual ~cConstReal();


    //## Other Operations (specified)
      //## Operation: GetValue%1042654030
      virtual void GetValue (LONG_T &value);

      //## Operation: GetValue%1088693712
      virtual void GetValue (ULONG_T &value);

      //## Operation: GetValue%1088693713
      virtual void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1042654031
      virtual void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1042654029
      virtual void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693714
      virtual void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1088693715
      virtual void GetValue (PTR_T &value);

  public:
    // Additional Public Declarations
      //## begin cConstReal%3E00444D03D6.public preserve=yes
      //## end cConstReal%3E00444D03D6.public

  protected:
    // Additional Protected Declarations
      //## begin cConstReal%3E00444D03D6.protected preserve=yes
      //## end cConstReal%3E00444D03D6.protected

  private:
    // Additional Private Declarations
      //## begin cConstReal%3E00444D03D6.private preserve=yes
      //## end cConstReal%3E00444D03D6.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Value%3E25A49B0121
      //## begin cConstReal::Value%3E25A49B0121.attr preserve=no  implementation: DOUBLE_T {U} 
      DOUBLE_T _Value;
      //## end cConstReal::Value%3E25A49B0121.attr

    // Additional Implementation Declarations
      //## begin cConstReal%3E00444D03D6.implementation preserve=yes
      //## end cConstReal%3E00444D03D6.implementation

};

//## begin cConstReal%3E00444D03D6.postscript preserve=yes
//## end cConstReal%3E00444D03D6.postscript

// Class cConstReal 

//## begin module%3E00444D03D6.epilog preserve=yes
//## end module%3E00444D03D6.epilog


#endif
