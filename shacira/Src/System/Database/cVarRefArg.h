//## begin module%3E0044830329.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0044830329.cm

//## begin module%3E0044830329.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0044830329.cp

//## Module: cVarRefArg%3E0044830329; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarRefArg.h

#ifndef cVarRefArg_h
#define cVarRefArg_h 1

//## begin module%3E0044830329.includes preserve=yes
//## end module%3E0044830329.includes

// cArgument
#include "System/Database/cArgument.h"

class __DLL_EXPORT__ cVarRef;

//## begin module%3E0044830329.additionalDeclarations preserve=yes
//## end module%3E0044830329.additionalDeclarations


//## begin cVarRefArg%3E0044830329.preface preserve=yes
//## end cVarRefArg%3E0044830329.preface

//## Class: cVarRefArg%3E0044830329
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cVarRefArg : public cArgument  //## Inherits: <unnamed>%3E0044A70227
{
  //## begin cVarRefArg%3E0044830329.initialDeclarations preserve=yes
public:
  //## end cVarRefArg%3E0044830329.initialDeclarations

    //## Constructors (generated)
      cVarRefArg();

      cVarRefArg(const cVarRefArg &right);

    //## Constructors (specified)
      //## Operation: cVarRefArg%1040992369
      cVarRefArg (cVarRef *var_ref);

    //## Destructor (generated)
      virtual ~cVarRefArg();


    //## Other Operations (specified)
      //## Operation: GetValue%1042654024
      virtual void GetValue (LONG_T &value);

      //## Operation: GetValue%1088693708
      virtual void GetValue (ULONG_T &value);

      //## Operation: GetValue%1088693709
      virtual void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1042654025
      virtual void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1042654023
      virtual void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693710
      virtual void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1088693711
      virtual void GetValue (PTR_T &value);

  public:
    // Additional Public Declarations
      //## begin cVarRefArg%3E0044830329.public preserve=yes
      //## end cVarRefArg%3E0044830329.public

  protected:
    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E00454302DF
      //## Role: cVarRefArg::VarRef%3E0045440269
      //## begin cVarRefArg::VarRef%3E0045440269.role preserve=no  public: cVarRef { -> 1RFHN}
      cVarRef *_VarRef;
      //## end cVarRefArg::VarRef%3E0045440269.role

    // Additional Protected Declarations
      //## begin cVarRefArg%3E0044830329.protected preserve=yes
      //## end cVarRefArg%3E0044830329.protected

  private:
    // Additional Private Declarations
      //## begin cVarRefArg%3E0044830329.private preserve=yes
      //## end cVarRefArg%3E0044830329.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cVarRefArg%3E0044830329.implementation preserve=yes
      //## end cVarRefArg%3E0044830329.implementation

};

//## begin cVarRefArg%3E0044830329.postscript preserve=yes
//## end cVarRefArg%3E0044830329.postscript

// Class cVarRefArg 

//## begin module%3E0044830329.epilog preserve=yes
//## end module%3E0044830329.epilog


#endif
