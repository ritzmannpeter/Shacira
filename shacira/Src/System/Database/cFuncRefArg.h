//## begin module%3E0044AA03D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0044AA03D0.cm

//## begin module%3E0044AA03D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0044AA03D0.cp

//## Module: cFuncRefArg%3E0044AA03D0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncRefArg.h

#ifndef cFuncRefArg_h
#define cFuncRefArg_h 1

//## begin module%3E0044AA03D0.includes preserve=yes
//## end module%3E0044AA03D0.includes

// cArgument
#include "System/Database/cArgument.h"

class __DLL_EXPORT__ cFuncRef;

//## begin module%3E0044AA03D0.additionalDeclarations preserve=yes
//## end module%3E0044AA03D0.additionalDeclarations


//## begin cFuncRefArg%3E0044AA03D0.preface preserve=yes
//## end cFuncRefArg%3E0044AA03D0.preface

//## Class: cFuncRefArg%3E0044AA03D0
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cFuncRefArg : public cArgument  //## Inherits: <unnamed>%3E0044BB03B6
{
  //## begin cFuncRefArg%3E0044AA03D0.initialDeclarations preserve=yes
public:
  //## end cFuncRefArg%3E0044AA03D0.initialDeclarations

    //## Constructors (generated)
      cFuncRefArg();

      cFuncRefArg(const cFuncRefArg &right);

    //## Constructors (specified)
      //## Operation: cFuncRefArg%1040992368
      cFuncRefArg (cFuncRef *func_ref);

    //## Destructor (generated)
      virtual ~cFuncRefArg();


    //## Other Operations (specified)
      //## Operation: GetValue%1042654018
      virtual void GetValue (LONG_T &value);

      //## Operation: GetValue%1088693704
      virtual void GetValue (ULONG_T &value);

      //## Operation: GetValue%1088693705
      virtual void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1042654019
      virtual void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1042654017
      virtual void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693706
      virtual void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1088693707
      virtual void GetValue (PTR_T &value);

      //## Operation: GetFuncRef%1089133000
      virtual cFuncRef * GetFuncRef ();

  public:
    // Additional Public Declarations
      //## begin cFuncRefArg%3E0044AA03D0.public preserve=yes
      //## end cFuncRefArg%3E0044AA03D0.public

  protected:
    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E004517020A
      //## Role: cFuncRefArg::FuncRef%3E004518007B
      //## begin cFuncRefArg::FuncRef%3E004518007B.role preserve=no  public: cFuncRef { -> 1RFHN}
      cFuncRef *_FuncRef;
      //## end cFuncRefArg::FuncRef%3E004518007B.role

    // Additional Protected Declarations
      //## begin cFuncRefArg%3E0044AA03D0.protected preserve=yes
      //## end cFuncRefArg%3E0044AA03D0.protected

  private:
    // Additional Private Declarations
      //## begin cFuncRefArg%3E0044AA03D0.private preserve=yes
      //## end cFuncRefArg%3E0044AA03D0.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFuncRefArg%3E0044AA03D0.implementation preserve=yes
      //## end cFuncRefArg%3E0044AA03D0.implementation

};

//## begin cFuncRefArg%3E0044AA03D0.postscript preserve=yes
//## end cFuncRefArg%3E0044AA03D0.postscript

// Class cFuncRefArg 

//## begin module%3E0044AA03D0.epilog preserve=yes
//## end module%3E0044AA03D0.epilog


#endif
