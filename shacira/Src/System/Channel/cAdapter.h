//## begin module%3F82F35E004E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82F35E004E.cm

//## begin module%3F82F35E004E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82F35E004E.cp

//## Module: cAdapter%3F82F35E004E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cAdapter.h

#ifndef cAdapter_h
#define cAdapter_h 1

//## begin module%3F82F35E004E.includes preserve=yes
//## end module%3F82F35E004E.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cTransientObject;

//## begin module%3F82F35E004E.additionalDeclarations preserve=yes
//## end module%3F82F35E004E.additionalDeclarations


//## begin cAdapter%3F82F35E004E.preface preserve=yes
//## end cAdapter%3F82F35E004E.preface

//## Class: cAdapter%3F82F35E004E
//	Base class for channel adapters. Channel adapters listen
//	to the back end of a channel awaiting incoming transient
//	objects,
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F82F5FE0261;cTransientObject { -> F}

class __DLL_EXPORT__ cAdapter : public cControlThread  //## Inherits: <unnamed>%3FFE88BB030D
{
  //## begin cAdapter%3F82F35E004E.initialDeclarations preserve=yes
public:
  //## end cAdapter%3F82F35E004E.initialDeclarations

    //## Constructors (generated)
      cAdapter();

      cAdapter(const cAdapter &right);

    //## Destructor (generated)
      virtual ~cAdapter();

     //## Operation: Object%1065547479
      //	Method that is called when an incoming object arrives at
      //	the back end of the associated channel.
      virtual void Object (cTransientObject *object) = 0;

  public:
    // Additional Public Declarations
      //## begin cAdapter%3F82F35E004E.public preserve=yes
      //## end cAdapter%3F82F35E004E.public

  protected:
    // Additional Protected Declarations
      //## begin cAdapter%3F82F35E004E.protected preserve=yes
      //## end cAdapter%3F82F35E004E.protected

  private:
    // Additional Private Declarations
      //## begin cAdapter%3F82F35E004E.private preserve=yes
      //## end cAdapter%3F82F35E004E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAdapter%3F82F35E004E.implementation preserve=yes
      //## end cAdapter%3F82F35E004E.implementation

};

//## begin cAdapter%3F82F35E004E.postscript preserve=yes
//## end cAdapter%3F82F35E004E.postscript

// Class cAdapter 

//## begin module%3F82F35E004E.epilog preserve=yes
//## end module%3F82F35E004E.epilog


#endif
