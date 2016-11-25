//## begin module%3E0043B201E8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0043B201E8.cm

//## begin module%3E0043B201E8.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0043B201E8.cp

//## Module: cConstString%3E0043B201E8; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstString.h

#ifndef cConstString_h
#define cConstString_h 1

//## begin module%3E0043B201E8.includes preserve=yes
//## end module%3E0043B201E8.includes

// cArgument
#include "System/Database/cArgument.h"
//## begin module%3E0043B201E8.additionalDeclarations preserve=yes
//## end module%3E0043B201E8.additionalDeclarations


//## begin cConstString%3E0043B201E8.preface preserve=yes
//## end cConstString%3E0043B201E8.preface

//## Class: cConstString%3E0043B201E8
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cConstString : public cArgument  //## Inherits: <unnamed>%3E00441901A0
{
  //## begin cConstString%3E0043B201E8.initialDeclarations preserve=yes
public:
  //## end cConstString%3E0043B201E8.initialDeclarations

    //## Constructors (generated)
      cConstString();

      cConstString(const cConstString &right);

    //## Constructors (specified)
      //## Operation: cConstString%1040992363
      cConstString (CONST_STRING_T arg);

    //## Destructor (generated)
      virtual ~cConstString();


    //## Other Operations (specified)
      //## Operation: GetValue%1042654042
      virtual void GetValue (LONG_T &value);

      //## Operation: GetValue%1088693720
      virtual void GetValue (ULONG_T &value);

      //## Operation: GetValue%1088693721
      virtual void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1042654043
      virtual void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1042654041
      virtual void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693722
      virtual void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1088693723
      virtual void GetValue (PTR_T &value);

  public:
    // Additional Public Declarations
      //## begin cConstString%3E0043B201E8.public preserve=yes
      //## end cConstString%3E0043B201E8.public

  protected:
    // Additional Protected Declarations
      //## begin cConstString%3E0043B201E8.protected preserve=yes
      //## end cConstString%3E0043B201E8.protected

  private:
    // Additional Private Declarations
      //## begin cConstString%3E0043B201E8.private preserve=yes
      //## end cConstString%3E0043B201E8.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Value%3E25A48D0026
      //## begin cConstString::Value%3E25A48D0026.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Value;
      //## end cConstString::Value%3E25A48D0026.attr

    // Additional Implementation Declarations
      //## begin cConstString%3E0043B201E8.implementation preserve=yes
      //## end cConstString%3E0043B201E8.implementation

};

//## begin cConstString%3E0043B201E8.postscript preserve=yes
//## end cConstString%3E0043B201E8.postscript

// Class cConstString 

//## begin module%3E0043B201E8.epilog preserve=yes
//## end module%3E0043B201E8.epilog


#endif
