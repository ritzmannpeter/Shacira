//## begin module%431339020347.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%431339020347.cm

//## begin module%431339020347.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%431339020347.cp

//## Module: cOPCClientProcess%431339020347; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOPCClientProcess.h

#ifndef cOPCClientProcess_h
#define cOPCClientProcess_h 1

//## begin module%431339020347.includes preserve=yes
//## end module%431339020347.includes

// eb_sema
#include "base/eb_sema.hpp"
// cSHClientProcess
#include "System/Process/cSHClientProcess.h"

class cNameSpaceIterator;
class __DLL_EXPORT__ cContext;

//## begin module%431339020347.additionalDeclarations preserve=yes
//## end module%431339020347.additionalDeclarations


//## begin cOPCClientProcess%431339020347.preface preserve=yes
//## end cOPCClientProcess%431339020347.preface

//## Class: cOPCClientProcess%431339020347
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43133F84024F;cNameSpaceIterator { -> F}
//## Uses: <unnamed>%43183FB902D0;cMutexSem { -> }
//## Uses: <unnamed>%431842CF0001;cContext { -> F}

class __DLL_EXPORT__ cOPCClientProcess : public cSHClientProcess  //## Inherits: <unnamed>%4313394200A7
{
  //## begin cOPCClientProcess%431339020347.initialDeclarations preserve=yes
public:
  //## end cOPCClientProcess%431339020347.initialDeclarations

    //## Constructors (generated)
      cOPCClientProcess();

      cOPCClientProcess(const cOPCClientProcess &right);

    //## Destructor (generated)
      virtual ~cOPCClientProcess();


    //## Other Operations (specified)
      //## Operation: Init%1125333424
      static void Init ();

      //## Operation: OnCycle%1125662156
      virtual void OnCycle ();

      //## Operation: NewContextNames%1125664304
      void NewContextNames (STRING_LIST_T &context_names);

      //## Operation: NewContext%1125664305
      cContext * NewContext (CONST_STRING_T name);

    // Data Members for Class Attributes

      //## Attribute: OPCClientProcess%43133A4F0088
      //## begin cOPCClientProcess::OPCClientProcess%43133A4F0088.attr preserve=no  public: static cOPCClientProcess * {U} NULL
      static cOPCClientProcess *_OPCClientProcess;
      //## end cOPCClientProcess::OPCClientProcess%43133A4F0088.attr

  public:
    // Additional Public Declarations
      //## begin cOPCClientProcess%431339020347.public preserve=yes
      //## end cOPCClientProcess%431339020347.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: NewContexts%431845B7006E
      //## begin cOPCClientProcess::NewContexts%431845B7006E.attr preserve=no  protected: CONTEXT_MAP_T {U} 
      CONTEXT_MAP_T _NewContexts;
      //## end cOPCClientProcess::NewContexts%431845B7006E.attr

    // Additional Protected Declarations
      //## begin cOPCClientProcess%431339020347.protected preserve=yes
      //## end cOPCClientProcess%431339020347.protected

  private:
    // Additional Private Declarations
      //## begin cOPCClientProcess%431339020347.private preserve=yes
      //## end cOPCClientProcess%431339020347.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cOPCClientProcess%431339020347.implementation preserve=yes
      //## end cOPCClientProcess%431339020347.implementation

};

//## begin cOPCClientProcess%431339020347.postscript preserve=yes
//## end cOPCClientProcess%431339020347.postscript

// Class cOPCClientProcess 

//## begin module%431339020347.epilog preserve=yes
//## end module%431339020347.epilog


#endif
