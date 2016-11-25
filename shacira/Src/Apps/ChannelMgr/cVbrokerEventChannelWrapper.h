//## begin module%3DCAB8D30302.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAB8D30302.cm

//## begin module%3DCAB8D30302.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAB8D30302.cp

//## Module: cVbrokerEventChannelWrapper%3DCAB8D30302; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Apps\ChannelMgr\cVbrokerEventChannelWrapper.h

#ifndef cVbrokerEventChannelWrapper_h
#define cVbrokerEventChannelWrapper_h 1

//## begin module%3DCAB8D30302.includes preserve=yes
//## end module%3DCAB8D30302.includes

// cEventChannelWrapper
#include "Apps/ChannelMgr/cEventChannelWrapper.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cCosEventChannelProxy;
class __DLL_EXPORT__ cBroker;
class __DLL_EXPORT__ cEventChannelManager;

//## begin module%3DCAB8D30302.additionalDeclarations preserve=yes
//## end module%3DCAB8D30302.additionalDeclarations


//## begin cVbrokerEventChannelWrapper%3DCAB8D30302.preface preserve=yes
//## end cVbrokerEventChannelWrapper%3DCAB8D30302.preface

//## Class: cVbrokerEventChannelWrapper%3DCAB8D30302
//## Category: Apps::ChannelMgr%3DD8C17600FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DCAB8D30304;cConfigurationObject { -> F}
//## Uses: <unnamed>%3DCAB8D30305;cBroker { -> F}
//## Uses: <unnamed>%3E70BE110242;cCosEventChannelProxy { -> F}
//## Uses: <unnamed>%3E719B650242;cEventChannelManager { -> F}

class __DLL_EXPORT__ cVbrokerEventChannelWrapper : public cEventChannelWrapper  //## Inherits: <unnamed>%3DD8C37D0230
{
  //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.initialDeclarations preserve=yes
public:
  //## end cVbrokerEventChannelWrapper%3DCAB8D30302.initialDeclarations

    //## Constructors (generated)
      cVbrokerEventChannelWrapper();

      cVbrokerEventChannelWrapper(const cVbrokerEventChannelWrapper &right);

    //## Constructors (specified)
      //## Operation: cVbrokerEventChannelWrapper%1036694775
      cVbrokerEventChannelWrapper (cEventChannelManager *process, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cVbrokerEventChannelWrapper();


    //## Other Operations (specified)
      //## Operation: MainFunc%1037640488
      virtual INT_T MainFunc (void *extra);

  public:
    // Additional Public Declarations
      //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.public preserve=yes
      //## end cVbrokerEventChannelWrapper%3DCAB8D30302.public

  protected:

    //## Other Operations (specified)
      //## Operation: AddServices%1047632192
      virtual void AddServices ();

    // Additional Protected Declarations
      //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.protected preserve=yes
      //## end cVbrokerEventChannelWrapper%3DCAB8D30302.protected

  private:
    // Additional Private Declarations
      //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.private preserve=yes
      //## end cVbrokerEventChannelWrapper%3DCAB8D30302.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartChannel%1047632193
      void StartChannel ();

      //## Operation: StopChannel%1047632194
      void StopChannel ();

    // Additional Implementation Declarations
      //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.implementation preserve=yes
      //## end cVbrokerEventChannelWrapper%3DCAB8D30302.implementation

};

//## begin cVbrokerEventChannelWrapper%3DCAB8D30302.postscript preserve=yes
//## end cVbrokerEventChannelWrapper%3DCAB8D30302.postscript

// Class cVbrokerEventChannelWrapper 

//## begin module%3DCAB8D30302.epilog preserve=yes
//## end module%3DCAB8D30302.epilog


#endif
