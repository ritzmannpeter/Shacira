//## begin module%3FBA3D9F03A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBA3D9F03A9.cm

//## begin module%3FBA3D9F03A9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBA3D9F03A9.cp

//## Module: cAdapterFactory%3FBA3D9F03A9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cAdapterFactory.h

#ifndef cAdapterFactory_h
#define cAdapterFactory_h 1

//## begin module%3FBA3D9F03A9.includes preserve=yes
//## end module%3FBA3D9F03A9.includes

// cAdapter
#include "System/Channel/cAdapter.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cChannel;
class __DLL_EXPORT__ cConnector;

//## begin module%3FBA3D9F03A9.additionalDeclarations preserve=yes
//## end module%3FBA3D9F03A9.additionalDeclarations


//## begin cAdapterFactory%3FBA3D9F03A9.preface preserve=yes
//## end cAdapterFactory%3FBA3D9F03A9.preface

//## Class: cAdapterFactory%3FBA3D9F03A9
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FBA3DF0029F;cAdapter { -> }
//## Uses: <unnamed>%3FBA3DF903C8;cConnector { -> F}
//## Uses: <unnamed>%3FBA3E1D0138;cConfigurationObject { -> F}
//## Uses: <unnamed>%3FBA583E0242;cChannel { -> F}

class __DLL_EXPORT__ cAdapterFactory 
{
  //## begin cAdapterFactory%3FBA3D9F03A9.initialDeclarations preserve=yes
public:
  //## end cAdapterFactory%3FBA3D9F03A9.initialDeclarations

    //## Constructors (generated)
      cAdapterFactory();

      cAdapterFactory(const cAdapterFactory &right);

    //## Destructor (generated)
      virtual ~cAdapterFactory();


    //## Other Operations (specified)
      //## Operation: CreateAdapter%1069152410
      static cAdapter * CreateAdapter (cConfigurationObject *config_obj, cChannel *front_end);

      //## Operation: CreateExternal%1074701776
      static cAdapter * CreateExternal (CONST_STRING_T source, cConfigurationObject *config_obj, cStaticObject *related_object);

  public:
    // Additional Public Declarations
      //## begin cAdapterFactory%3FBA3D9F03A9.public preserve=yes
      //## end cAdapterFactory%3FBA3D9F03A9.public

  protected:
    // Additional Protected Declarations
      //## begin cAdapterFactory%3FBA3D9F03A9.protected preserve=yes
      //## end cAdapterFactory%3FBA3D9F03A9.protected

  private:
    // Additional Private Declarations
      //## begin cAdapterFactory%3FBA3D9F03A9.private preserve=yes
      //## end cAdapterFactory%3FBA3D9F03A9.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAdapterFactory%3FBA3D9F03A9.implementation preserve=yes
      //## end cAdapterFactory%3FBA3D9F03A9.implementation

};

//## begin cAdapterFactory%3FBA3D9F03A9.postscript preserve=yes
//## end cAdapterFactory%3FBA3D9F03A9.postscript

// Class cAdapterFactory 

//## begin module%3FBA3D9F03A9.epilog preserve=yes
//## end module%3FBA3D9F03A9.epilog


#endif
