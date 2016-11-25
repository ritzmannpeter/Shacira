//## begin module%3CBBD3F60158.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CBBD3F60158.cm

//## begin module%3CBBD3F60158.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CBBD3F60158.cp

//## Module: cWTNodes%3CBBD3F60158; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cWTNodes.h

#ifndef cWTNodes_h
#define cWTNodes_h 1

//## begin module%3CBBD3F60158.includes preserve=yes
//## end module%3CBBD3F60158.includes

// eb_sema
#include "base/eb_sema.hpp"
// cError
#include "System/cError.h"
// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cWTNode;

//## begin module%3CBBD3F60158.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cWTNode*> NODE_MAP_T;

//## end module%3CBBD3F60158.additionalDeclarations


//## begin cWTNodes%3CBBD3F60158.preface preserve=yes
//## end cWTNodes%3CBBD3F60158.preface

//## Class: cWTNodes%3CBBD3F60158
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CBBD41202FD;cError { -> }
//## Uses: <unnamed>%3CBBD4A7013F;cWTNode { -> F}
//## Uses: <unnamed>%3CBC78C10300;cMutexSem { -> }
//## Uses: <unnamed>%3CBC799C017E;cObjectLock { -> F}

class __DLL_EXPORT__ cWTNodes : public cControlThread  //## Inherits: <unnamed>%3CBBDB3003BB
{
  //## begin cWTNodes%3CBBD3F60158.initialDeclarations preserve=yes
public:
  //## end cWTNodes%3CBBD3F60158.initialDeclarations

    //## Constructors (generated)
      cWTNodes();

      cWTNodes(const cWTNodes &right);

    //## Destructor (generated)
      virtual ~cWTNodes();


    //## Other Operations (specified)
      //## Operation: Node%1018942490
      cWTNode * Node (CONST_STRING_T ip_address);

      //## Operation: ControlFunc%1018942495
      virtual INT_T ControlFunc ();

  public:
    // Additional Public Declarations
      //## begin cWTNodes%3CBBD3F60158.public preserve=yes
      //## end cWTNodes%3CBBD3F60158.public

  protected:
    // Additional Protected Declarations
      //## begin cWTNodes%3CBBD3F60158.protected preserve=yes
      //## end cWTNodes%3CBBD3F60158.protected

  private:
    // Additional Private Declarations
      //## begin cWTNodes%3CBBD3F60158.private preserve=yes
      //## end cWTNodes%3CBBD3F60158.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: NodeMap%3CBBD81F0177
      //## begin cWTNodes::NodeMap%3CBBD81F0177.attr preserve=no  implementation: NODE_MAP_T {U} 
      NODE_MAP_T _NodeMap;
      //## end cWTNodes::NodeMap%3CBBD81F0177.attr

      //## Attribute: NodeListMutex%3CBC789C0126
      //## begin cWTNodes::NodeListMutex%3CBC789C0126.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _NodeListMutex;
      //## end cWTNodes::NodeListMutex%3CBC789C0126.attr

    // Additional Implementation Declarations
      //## begin cWTNodes%3CBBD3F60158.implementation preserve=yes
      //## end cWTNodes%3CBBD3F60158.implementation

};

//## begin cWTNodes%3CBBD3F60158.postscript preserve=yes
//## end cWTNodes%3CBBD3F60158.postscript

// Class cWTNodes 

//## begin module%3CBBD3F60158.epilog preserve=yes
//## end module%3CBBD3F60158.epilog


#endif
