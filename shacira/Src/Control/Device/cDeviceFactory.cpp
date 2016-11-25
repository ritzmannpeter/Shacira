//## begin module%3FE6D4CB005D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE6D4CB005D.cm

//## begin module%3FE6D4CB005D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE6D4CB005D.cp

//## Module: cDeviceFactory%3FE6D4CB005D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cDeviceFactory.cpp

//## begin module%3FE6D4CB005D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FE6D4CB005D.additionalIncludes

//## begin module%3FE6D4CB005D.includes preserve=yes
//## end module%3FE6D4CB005D.includes

// cStaticObject
#include "System/Objects/cStaticObject.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cSharedLibrary
#include "System/Sys/cSharedLibrary.h"
// cCell
#include "Control/Cell/cCell.h"
// cDevice
#include "Control/Device/cDevice.h"
// cDeviceFactory
#include "Control/Device/cDeviceFactory.h"
// cGrabberDevice
#include "Control/Device/cGrabberDevice.h"
// cFM2Device
#include "Control/Device/cFM2Device.h"
// cConfigurationDevice
#include "Control/Device/cConfigurationDevice.h"
// cDigIODevice
#include "Control/Device/cDigIODevice.h"
// cMemoryAddressedDevice
#include "Control/Device/cMemoryAddressedDevice.h"
// cS7Device
#include "Control/Device/cS7Device.h"
// cPPCDevice
#include "Control/Device/PPCCom/cPPCDevice.h"
// cPerfDevice
#include "Control/Device/Performance/cPerfDevice.h"
//## begin module%3FE6D4CB005D.additionalDeclarations preserve=yes
//## end module%3FE6D4CB005D.additionalDeclarations


// Class cDeviceFactory 

cDeviceFactory::cDeviceFactory()
  //## begin cDeviceFactory::cDeviceFactory%.hasinit preserve=no
  //## end cDeviceFactory::cDeviceFactory%.hasinit
  //## begin cDeviceFactory::cDeviceFactory%.initialization preserve=yes
  //## end cDeviceFactory::cDeviceFactory%.initialization
{
  //## begin cDeviceFactory::cDeviceFactory%.body preserve=yes
_ASSERT_UNCOND
  //## end cDeviceFactory::cDeviceFactory%.body
}

cDeviceFactory::cDeviceFactory(const cDeviceFactory &right)
  //## begin cDeviceFactory::cDeviceFactory%copy.hasinit preserve=no
  //## end cDeviceFactory::cDeviceFactory%copy.hasinit
  //## begin cDeviceFactory::cDeviceFactory%copy.initialization preserve=yes
  //## end cDeviceFactory::cDeviceFactory%copy.initialization
{
  //## begin cDeviceFactory::cDeviceFactory%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDeviceFactory::cDeviceFactory%copy.body
}


cDeviceFactory::~cDeviceFactory()
{
  //## begin cDeviceFactory::~cDeviceFactory%.body preserve=yes
_ASSERT_UNCOND
  //## end cDeviceFactory::~cDeviceFactory%.body
}



//## Other Operations (implementation)
cDevice * cDeviceFactory::CreateDevice (cConfigurationObject *config_obj, cCell *cell)
{
  //## begin cDeviceFactory::CreateDevice%1072085855.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   STRING_T type_name = config_obj->PropertyValue("DeviceType", "", true);
   cDevice * device = NULL;
   if (IDENTIFIER_EQUAL(type_name.c_str(), "PPCDevice")) {
      device = new cPPCDevice(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "FM2Device")) {
      device = new cFM2Device(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "GrabberDevice")) {
      device = new cGrabberDevice(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "DigIODevice")) {
      device = new cDigIODevice(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "MemoryAddressedDevice")) {
      device = new cMemoryAddressedDevice(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "ConfigDevice")) {
      device = new cConfigurationDevice(config_obj, cell);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "PerfDevice")) {
      device = new cPerfDevice(config_obj, cell);
   } else {
      device = CreateExternal(config_obj, cell);
      if (device == NULL) {
         device = CreateExternal(type_name.c_str(), config_obj, cell);
      }
   }
   return device;
  //## end cDeviceFactory::CreateDevice%1072085855.body
}

cDevice * cDeviceFactory::CreateExternal (cConfigurationObject *config_obj, cCell *cell)
{
  //## begin cDeviceFactory::CreateExternal%1075189787.body preserve=yes
   DEV_FACTORY_T factory_func = cCustomFunctions::DeviceCreatorFuncAddress();
   if (factory_func != NULL) {
      cDevice * device = NULL;
      device = (cDevice*)factory_func(config_obj, cell);
      return device;
   } else {
      return NULL;
   }
  //## end cDeviceFactory::CreateExternal%1075189787.body
}

cDevice * cDeviceFactory::CreateExternal (CONST_STRING_T type_name, cConfigurationObject *config_obj, cCell *cell)
{
  //## begin cDeviceFactory::CreateExternal%1105976610.body preserve=yes
   cSharedLibrary * library = cSharedLibrary::Library(type_name);
   if (library != NULL) {
      library->Load();
      DEV_FACTORY_T factory_func= (DEV_FACTORY_T)library->FunctionAddress("CreateDevice");
      if (factory_func != NULL) {
         return (cDevice*)factory_func(config_obj, cell);
      }
   }
   return NULL;
  //## end cDeviceFactory::CreateExternal%1105976610.body
}

// Additional Declarations
  //## begin cDeviceFactory%3FE6D4CB005D.declarations preserve=yes
  //## end cDeviceFactory%3FE6D4CB005D.declarations

//## begin module%3FE6D4CB005D.epilog preserve=yes
//## end module%3FE6D4CB005D.epilog
