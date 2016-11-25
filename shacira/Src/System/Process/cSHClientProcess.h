//## begin module%4312DD580335.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4312DD580335.cm

//## begin module%4312DD580335.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4312DD580335.cp

//## Module: cSHClientProcess%4312DD580335; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cSHClientProcess.h

#ifndef cSHClientProcess_h
#define cSHClientProcess_h 1

//## begin module%4312DD580335.includes preserve=yes
//## end module%4312DD580335.includes

// eb_sema
#include "base/eb_sema.hpp"
// cSHProcess
#include "System/Process/cSHProcess.h"

class __DLL_EXPORT__ cProxyReceiver;
class __DLL_EXPORT__ cNameSpace;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;

//## begin module%4312DD580335.additionalDeclarations preserve=yes
//## end module%4312DD580335.additionalDeclarations


//## begin cSHClientProcess%4312DD580335.preface preserve=yes
//## end cSHClientProcess%4312DD580335.preface

//## Class: cSHClientProcess%4312DD580335
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4312DF290144;cProxyReceiver { -> F}
//## Uses: <unnamed>%4312DFB802CB;cContext { -> F}
//## Uses: <unnamed>%4312E02003A7;cVarDef { -> F}
//## Uses: <unnamed>%4312E02A029D;cVarRef { -> F}
//## Uses: <unnamed>%43183FB50243;cMutexSem { -> }

class __DLL_EXPORT__ cSHClientProcess : public cSHProcess  //## Inherits: <unnamed>%4312DE69022D
{
  //## begin cSHClientProcess%4312DD580335.initialDeclarations preserve=yes
public:
  //## end cSHClientProcess%4312DD580335.initialDeclarations

    //## Constructors (generated)
      cSHClientProcess();

      cSHClientProcess(const cSHClientProcess &right);

    //## Constructors (specified)
      //## Operation: cSHClientProcess%1133172775
      cSHClientProcess (LONG_T if_type, BOOL_T offer_namespace = false);

    //## Destructor (generated)
      virtual ~cSHClientProcess();


    //## Other Operations (specified)
      //## Operation: OnCycle%1125306232
      virtual void OnCycle ();

      //## Operation: NameSpace%1125306233
      cNameSpace * NameSpace ();

  public:
    // Additional Public Declarations
      //## begin cSHClientProcess%4312DD580335.public preserve=yes
      //## end cSHClientProcess%4312DD580335.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: OfferNameSpace%4312E2D9007D
      //## begin cSHClientProcess::OfferNameSpace%4312E2D9007D.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _OfferNameSpace;
      //## end cSHClientProcess::OfferNameSpace%4312E2D9007D.attr

      //## Attribute: NameSpaceMutex%43183F4D005F
      //## begin cSHClientProcess::NameSpaceMutex%43183F4D005F.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _NameSpaceMutex;
      //## end cSHClientProcess::NameSpaceMutex%43183F4D005F.attr

    // Data Members for Associations

      //## Association: System::Process::<unnamed>%4312DE00025B
      //## Role: cSHClientProcess::NameSpace%4312DE0100F4
      //## begin cSHClientProcess::NameSpace%4312DE0100F4.role preserve=no  public: cNameSpace { -> 1RFHN}
      cNameSpace *_NameSpace;
      //## end cSHClientProcess::NameSpace%4312DE0100F4.role

    // Additional Protected Declarations
      //## begin cSHClientProcess%4312DD580335.protected preserve=yes
      //## end cSHClientProcess%4312DD580335.protected

  private:
    // Additional Private Declarations
      //## begin cSHClientProcess%4312DD580335.private preserve=yes
      //## end cSHClientProcess%4312DD580335.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSHClientProcess%4312DD580335.implementation preserve=yes
      //## end cSHClientProcess%4312DD580335.implementation

};

//## begin cSHClientProcess%4312DD580335.postscript preserve=yes
//## end cSHClientProcess%4312DD580335.postscript

// Class cSHClientProcess 

//## begin module%4312DD580335.epilog preserve=yes
//## end module%4312DD580335.epilog


#endif
