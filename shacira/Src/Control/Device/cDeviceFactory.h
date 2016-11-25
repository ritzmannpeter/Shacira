//## begin module%3FE6D4CB005D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE6D4CB005D.cm

//## begin module%3FE6D4CB005D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE6D4CB005D.cp

//## Module: cDeviceFactory%3FE6D4CB005D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cDeviceFactory.h

#ifndef cDeviceFactory_h
#define cDeviceFactory_h 1

//## begin module%3FE6D4CB005D.includes preserve=yes
//## end module%3FE6D4CB005D.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"

class __DLL_EXPORT__ cStaticObject;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cSharedLibrary;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cDevice;
class __DLL_EXPORT__ cGrabberDevice;
class __DLL_EXPORT__ cFM2Device;
class __DLL_EXPORT__ cConfigurationDevice;
class __DLL_EXPORT__ cDigIODevice;
class __DLL_EXPORT__ cMemoryAddressedDevice;
class __DLL_EXPORT__ cS7Device;
class __DLL_EXPORT__ cPPCDevice;
class __DLL_EXPORT__ cPerfDevice;

//## begin module%3FE6D4CB005D.additionalDeclarations preserve=yes
//## end module%3FE6D4CB005D.additionalDeclarations


//## begin cDeviceFactory%3FE6D4CB005D.preface preserve=yes
//## end cDeviceFactory%3FE6D4CB005D.preface

//## Class: cDeviceFactory%3FE6D4CB005D
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FE6D5B5007D;cPPCDevice { -> F}
//## Uses: <unnamed>%3FE6D5B9007D;cFM2Device { -> F}
//## Uses: <unnamed>%3FE6D5BC032C;cGrabberDevice { -> F}
//## Uses: <unnamed>%401621750271;cS7Device { -> F}
//## Uses: <unnamed>%401623780119;cConfigurationObject { -> F}
//## Uses: <unnamed>%401623B00280;cDevice { -> F}
//## Uses: <unnamed>%401623D901C5;cStaticObject { -> F}
//## Uses: <unnamed>%401E842E031C;cMemoryAddressedDevice { -> F}
//## Uses: <unnamed>%40472AC003D8;cDigIODevice { -> F}
//## Uses: <unnamed>%40719A410196;cCell { -> F}
//## Uses: <unnamed>%408CFEFD0399;cConfigurationDevice { -> F}
//## Uses: <unnamed>%41E6AB7C0261;cCustomFunctions { -> }
//## Uses: <unnamed>%421B6A51029F;cSharedLibrary { -> F}
//## Uses: <unnamed>%428C88EA008C;cPerfDevice { -> F}

class __DLL_EXPORT__ cDeviceFactory 
{
  //## begin cDeviceFactory%3FE6D4CB005D.initialDeclarations preserve=yes
public:
  //## end cDeviceFactory%3FE6D4CB005D.initialDeclarations

    //## Constructors (generated)
      cDeviceFactory();

      cDeviceFactory(const cDeviceFactory &right);

    //## Destructor (generated)
      virtual ~cDeviceFactory();


    //## Other Operations (specified)
      //## Operation: CreateDevice%1072085855
      static cDevice * CreateDevice (cConfigurationObject *config_obj, cCell *cell);

      //## Operation: CreateExternal%1075189787
      static cDevice * CreateExternal (cConfigurationObject *config_obj, cCell *cell);

      //## Operation: CreateExternal%1105976610
      static cDevice * CreateExternal (CONST_STRING_T type_name, cConfigurationObject *config_obj, cCell *cell);

  public:
    // Additional Public Declarations
      //## begin cDeviceFactory%3FE6D4CB005D.public preserve=yes
      //## end cDeviceFactory%3FE6D4CB005D.public

  protected:
    // Additional Protected Declarations
      //## begin cDeviceFactory%3FE6D4CB005D.protected preserve=yes
      //## end cDeviceFactory%3FE6D4CB005D.protected

  private:
    // Additional Private Declarations
      //## begin cDeviceFactory%3FE6D4CB005D.private preserve=yes
      //## end cDeviceFactory%3FE6D4CB005D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDeviceFactory%3FE6D4CB005D.implementation preserve=yes
      //## end cDeviceFactory%3FE6D4CB005D.implementation

};

//## begin cDeviceFactory%3FE6D4CB005D.postscript preserve=yes
//## end cDeviceFactory%3FE6D4CB005D.postscript

// Class cDeviceFactory 

//## begin module%3FE6D4CB005D.epilog preserve=yes
//## end module%3FE6D4CB005D.epilog


#endif
