//## begin module%3DD8DFED0147.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD8DFED0147.cm

//## begin module%3DD8DFED0147.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3DD8DFED0147.cp

//## Module: cWrapperFactory%3DD8DFED0147; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cWrapperFactory.h

#ifndef cWrapperFactory_h
#define cWrapperFactory_h 1

//## begin module%3DD8DFED0147.includes preserve=yes
//## end module%3DD8DFED0147.includes


class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cEventChannelWrapper;
class __DLL_EXPORT__ cEventChannelManager;
class __DLL_EXPORT__ cVbrokerEventChannelWrapper;

//## begin module%3DD8DFED0147.additionalDeclarations preserve=yes
//## end module%3DD8DFED0147.additionalDeclarations


//## begin cWrapperFactory%3DD8DFED0147.preface preserve=yes
//## end cWrapperFactory%3DD8DFED0147.preface

//## Class: cWrapperFactory%3DD8DFED0147
//## Category: Apps::ChannelMgr%3DD8C17600FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD8E1020146;cEventChannelWrapper { -> F}
//## Uses: <unnamed>%3DD8E10C019A;cVbrokerEventChannelWrapper { -> F}
//## Uses: <unnamed>%3DD8E1630087;cConfigurationObject { -> F}
//## Uses: <unnamed>%3E70C3220000;cEventChannelManager { -> F}

class __DLL_EXPORT__ cWrapperFactory 
{
  //## begin cWrapperFactory%3DD8DFED0147.initialDeclarations preserve=yes
public:
  //## end cWrapperFactory%3DD8DFED0147.initialDeclarations

    //## Constructors (generated)
      cWrapperFactory();

      cWrapperFactory(const cWrapperFactory &right);

    //## Destructor (generated)
      virtual ~cWrapperFactory();


    //## Other Operations (specified)
      //## Operation: CreateWrapper%1037621190
      static cEventChannelWrapper * CreateWrapper (cEventChannelManager *process, cConfigurationObject *config_obj);

  public:
    // Additional Public Declarations
      //## begin cWrapperFactory%3DD8DFED0147.public preserve=yes
      //## end cWrapperFactory%3DD8DFED0147.public

  protected:
    // Additional Protected Declarations
      //## begin cWrapperFactory%3DD8DFED0147.protected preserve=yes
      //## end cWrapperFactory%3DD8DFED0147.protected

  private:
    // Additional Private Declarations
      //## begin cWrapperFactory%3DD8DFED0147.private preserve=yes
      //## end cWrapperFactory%3DD8DFED0147.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cWrapperFactory%3DD8DFED0147.implementation preserve=yes
      //## end cWrapperFactory%3DD8DFED0147.implementation

};

//## begin cWrapperFactory%3DD8DFED0147.postscript preserve=yes
//## end cWrapperFactory%3DD8DFED0147.postscript

// Class cWrapperFactory 

//## begin module%3DD8DFED0147.epilog preserve=yes
//## end module%3DD8DFED0147.epilog


#endif
