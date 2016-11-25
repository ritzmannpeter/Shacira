//## begin module%4113C8220271.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4113C8220271.cm

//## begin module%4113C8220271.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4113C8220271.cp

//## Module: cFileContext%4113C8220271; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFileContext.h

#ifndef cFileContext_h
#define cFileContext_h 1

//## begin module%4113C8220271.includes preserve=yes
//## end module%4113C8220271.includes

// cContext
#include "System/Database/cContext.h"

class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cFileVariable;
class __DLL_EXPORT__ cDevice;

//## begin module%4113C8220271.additionalDeclarations preserve=yes
//## end module%4113C8220271.additionalDeclarations


//## begin cFileContext%4113C8220271.preface preserve=yes
//## end cFileContext%4113C8220271.preface

//## Class: cFileContext%4113C8220271
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4113C9B00251;cFileVariable { -> F}
//## Uses: <unnamed>%4113D1A2009C;cVarDef { -> F}
//## Uses: <unnamed>%4115F3A6006D;cDevice { -> F}

class __DLL_EXPORT__ cFileContext : public cContext  //## Inherits: <unnamed>%4113C83B00DA
{
  //## begin cFileContext%4113C8220271.initialDeclarations preserve=yes
public:
  //## end cFileContext%4113C8220271.initialDeclarations

    //## Constructors (generated)
      cFileContext();

      cFileContext(const cFileContext &right);

    //## Destructor (generated)
      virtual ~cFileContext();


    //## Other Operations (specified)
      //## Operation: IsRemote%1091815615
      //	Is this Context a remote context ?
      virtual BOOL_T IsRemote ();

      //## Operation: Create%1091815619
      //	Creates necessary resources.
      virtual void Create ();

      //## Operation: CreateDynamic%1091815620
      virtual void CreateDynamic ();

      //## Operation: GetVarDefs%1091815621
      //	Gets all variable definitions as a list of serialized
      //	objects.
      ULONG_T GetVarDefs (STRING_T &var_defs, ULONG_T if_type = 0);

  public:
    // Additional Public Declarations
      //## begin cFileContext%4113C8220271.public preserve=yes
      //## end cFileContext%4113C8220271.public

  protected:
    // Additional Protected Declarations
      //## begin cFileContext%4113C8220271.protected preserve=yes
      //## end cFileContext%4113C8220271.protected

  private:
    // Additional Private Declarations
      //## begin cFileContext%4113C8220271.private preserve=yes
      //## end cFileContext%4113C8220271.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFileContext%4113C8220271.implementation preserve=yes
      //## end cFileContext%4113C8220271.implementation

};

//## begin cFileContext%4113C8220271.postscript preserve=yes
//## end cFileContext%4113C8220271.postscript

// Class cFileContext 

//## begin module%4113C8220271.epilog preserve=yes
//## end module%4113C8220271.epilog


#endif
