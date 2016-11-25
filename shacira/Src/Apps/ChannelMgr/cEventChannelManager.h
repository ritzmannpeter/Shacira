//## begin module%3C502485009A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C502485009A.cm

//## begin module%3C502485009A.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C502485009A.cp

//## Module: cEventChannelManager%3C502485009A; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cEventChannelManager.h

#ifndef cEventChannelManager_h
#define cEventChannelManager_h 1

//## begin module%3C502485009A.includes preserve=yes
//## end module%3C502485009A.includes

// cSHProcess
#include "System/Process/cSHProcess.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cProxySender;
class __DLL_EXPORT__ cChannelProxy;
class __DLL_EXPORT__ cBroker;
class __DLL_EXPORT__ cEventChannelWrapper;
class __DLL_EXPORT__ cWrapperFactory;

//## begin module%3C502485009A.additionalDeclarations preserve=yes
//## end module%3C502485009A.additionalDeclarations


//## begin cEventChannelManager%3C502485009A.preface preserve=yes
//## end cEventChannelManager%3C502485009A.preface

//## Class: cEventChannelManager%3C502485009A
//## Category: Apps::ChannelMgr%3DD8C17600FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C5036400169;cConfigurationObject { -> F}
//## Uses: <unnamed>%3C50460703A2;cBroker { -> F}
//## Uses: <unnamed>%3D04E64F0300;cChannelProxy { -> F}
//## Uses: <unnamed>%3DD8E11F0292;cWrapperFactory { -> F}
//## Uses: <unnamed>%3DDE1468018B;cProxySender { -> F}

class __DLL_EXPORT__ cEventChannelManager : public cSHProcess  //## Inherits: <unnamed>%3C51226101CF
{
  //## begin cEventChannelManager%3C502485009A.initialDeclarations preserve=yes
public:
  //## end cEventChannelManager%3C502485009A.initialDeclarations

    //## Constructors (generated)
      cEventChannelManager();

      cEventChannelManager(const cEventChannelManager &right);

    //## Constructors (specified)
      //## Operation: cEventChannelManager%1011885582
      cEventChannelManager (cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cEventChannelManager();

  public:
    // Additional Public Declarations
      //## begin cEventChannelManager%3C502485009A.public preserve=yes
      //## end cEventChannelManager%3C502485009A.public

  protected:

    //## Other Operations (specified)
      //## Operation: OnStartUp%1037369514
      virtual void OnStartUp ();

      //## Operation: OnShutDown%1037369516
      virtual void OnShutDown ();

    // Data Members for Associations

      //## Association: Apps::ChannelMgr::<unnamed>%3DD8C21E0235
      //## Role: cEventChannelManager::Wrappers%3DD8C21F01D2
      //## Qualifier: name%3DD8C24E014E; STRING_T
      //## begin cEventChannelManager::Wrappers%3DD8C21F01D2.role preserve=no  public: cEventChannelWrapper {1 -> 0..nRFHN}
      std::map<STRING_T, cEventChannelWrapper*> _Wrappers;
      //## end cEventChannelManager::Wrappers%3DD8C21F01D2.role

    // Additional Protected Declarations
      //## begin cEventChannelManager%3C502485009A.protected preserve=yes
      //## end cEventChannelManager%3C502485009A.protected

  private:
    // Additional Private Declarations
      //## begin cEventChannelManager%3C502485009A.private preserve=yes
      //## end cEventChannelManager%3C502485009A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cEventChannelManager%3C502485009A.implementation preserve=yes
      //## end cEventChannelManager%3C502485009A.implementation

};

//## begin cEventChannelManager%3C502485009A.postscript preserve=yes
//## end cEventChannelManager%3C502485009A.postscript

// Class cEventChannelManager 

//## begin module%3C502485009A.epilog preserve=yes
//## end module%3C502485009A.epilog


#endif
