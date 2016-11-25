//## begin module%3FBA3CF100DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBA3CF100DA.cm

//## begin module%3FBA3CF100DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBA3CF100DA.cp

//## Module: cChannelFactory%3FBA3CF100DA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannelFactory.h

#ifndef cChannelFactory_h
#define cChannelFactory_h 1

//## begin module%3FBA3CF100DA.includes preserve=yes
//## end module%3FBA3CF100DA.includes


class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cChannel;
class __DLL_EXPORT__ cRemoteBridge;
class __DLL_EXPORT__ cCOSChannel;
class __DLL_EXPORT__ cLocalChannel;

//## begin module%3FBA3CF100DA.additionalDeclarations preserve=yes
//## end module%3FBA3CF100DA.additionalDeclarations


//## begin cChannelFactory%3FBA3CF100DA.preface preserve=yes
//## end cChannelFactory%3FBA3CF100DA.preface

//## Class: cChannelFactory%3FBA3CF100DA
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FBA3D500186;cChannel { -> F}
//## Uses: <unnamed>%3FBA3D5C009C;cLocalChannel { -> F}
//## Uses: <unnamed>%3FBA3D64037A;cRemoteBridge { -> F}
//## Uses: <unnamed>%3FBA3D71002E;cCOSChannel { -> F}
//## Uses: <unnamed>%3FBA3E28006D;cConfigurationObject { -> F}
//## Uses: <unnamed>%3FBB59170177;cSHProcess { -> F}

class __DLL_EXPORT__ cChannelFactory 
{
  //## begin cChannelFactory%3FBA3CF100DA.initialDeclarations preserve=yes
public:
  //## end cChannelFactory%3FBA3CF100DA.initialDeclarations

    //## Constructors (generated)
      cChannelFactory();

      cChannelFactory(const cChannelFactory &right);

    //## Destructor (generated)
      virtual ~cChannelFactory();


    //## Other Operations (specified)
      //## Operation: CreateChannel%1069152411
      static cChannel * CreateChannel (cConfigurationObject *config_obj, cSHProcess *process, CONST_STRING_T channel_name);

      //## Operation: CreateExternal%1074705361
      static cChannel * CreateExternal (CONST_STRING_T source, cConfigurationObject *config_obj, cStaticObject *related_object);

  public:
    // Additional Public Declarations
      //## begin cChannelFactory%3FBA3CF100DA.public preserve=yes
      //## end cChannelFactory%3FBA3CF100DA.public

  protected:
    // Additional Protected Declarations
      //## begin cChannelFactory%3FBA3CF100DA.protected preserve=yes
      //## end cChannelFactory%3FBA3CF100DA.protected

  private:
    // Additional Private Declarations
      //## begin cChannelFactory%3FBA3CF100DA.private preserve=yes
      //## end cChannelFactory%3FBA3CF100DA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cChannelFactory%3FBA3CF100DA.implementation preserve=yes
      //## end cChannelFactory%3FBA3CF100DA.implementation

};

//## begin cChannelFactory%3FBA3CF100DA.postscript preserve=yes
//## end cChannelFactory%3FBA3CF100DA.postscript

// Class cChannelFactory 

//## begin module%3FBA3CF100DA.epilog preserve=yes
//## end module%3FBA3CF100DA.epilog


#endif
