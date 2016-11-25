//## begin module%408CFEAE0138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%408CFEAE0138.cm

//## begin module%408CFEAE0138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%408CFEAE0138.cp

//## Module: cConfigurationDevice%408CFEAE0138; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cConfigurationDevice.cpp

//## begin module%408CFEAE0138.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%408CFEAE0138.additionalIncludes

//## begin module%408CFEAE0138.includes preserve=yes
//## end module%408CFEAE0138.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cConfigurationDevice
#include "Control/Device/cConfigurationDevice.h"
//## begin module%408CFEAE0138.additionalDeclarations preserve=yes
//## end module%408CFEAE0138.additionalDeclarations


// Class cConfigurationDevice 


cConfigurationDevice::cConfigurationDevice()
  //## begin cConfigurationDevice::cConfigurationDevice%.hasinit preserve=no
      : _Configuration(NULL)
  //## end cConfigurationDevice::cConfigurationDevice%.hasinit
  //## begin cConfigurationDevice::cConfigurationDevice%.initialization preserve=yes
  //## end cConfigurationDevice::cConfigurationDevice%.initialization
{
  //## begin cConfigurationDevice::cConfigurationDevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cConfigurationDevice::cConfigurationDevice%.body
}

cConfigurationDevice::cConfigurationDevice(const cConfigurationDevice &right)
  //## begin cConfigurationDevice::cConfigurationDevice%copy.hasinit preserve=no
      : _Configuration(NULL)
  //## end cConfigurationDevice::cConfigurationDevice%copy.hasinit
  //## begin cConfigurationDevice::cConfigurationDevice%copy.initialization preserve=yes
  //## end cConfigurationDevice::cConfigurationDevice%copy.initialization
{
  //## begin cConfigurationDevice::cConfigurationDevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConfigurationDevice::cConfigurationDevice%copy.body
}

cConfigurationDevice::cConfigurationDevice (cConfigurationObject *config_obj, cCell *cell)
  //## begin cConfigurationDevice::cConfigurationDevice%1082991647.hasinit preserve=no
      : _Configuration(NULL)
  //## end cConfigurationDevice::cConfigurationDevice%1082991647.hasinit
  //## begin cConfigurationDevice::cConfigurationDevice%1082991647.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cConfigurationDevice::cConfigurationDevice%1082991647.initialization
{
  //## begin cConfigurationDevice::cConfigurationDevice%1082991647.body preserve=yes
   STRING_T config_file = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                             cConfiguration::DefaultConfigFile());
   _Configuration = new cConfiguration(config_file.c_str());
  //## end cConfigurationDevice::cConfigurationDevice%1082991647.body
}


cConfigurationDevice::~cConfigurationDevice()
{
  //## begin cConfigurationDevice::~cConfigurationDevice%.body preserve=yes
  //## end cConfigurationDevice::~cConfigurationDevice%.body
}



//## Other Operations (implementation)
void cConfigurationDevice::Start ()
{
  //## begin cConfigurationDevice::Start%1082991648.body preserve=yes
  //## end cConfigurationDevice::Start%1082991648.body
}

void cConfigurationDevice::Stop ()
{
  //## begin cConfigurationDevice::Stop%1082991649.body preserve=yes
  //## end cConfigurationDevice::Stop%1082991649.body
}

void cConfigurationDevice::Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size)
{
  //## begin cConfigurationDevice::Cache%1082991650.body preserve=yes
  //## end cConfigurationDevice::Cache%1082991650.body
}

void cConfigurationDevice::Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements)
{
  //## begin cConfigurationDevice::Buffer%1082991651.body preserve=yes
  //## end cConfigurationDevice::Buffer%1082991651.body
}

void cConfigurationDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Get%1082991653.body preserve=yes
  //## end cConfigurationDevice::Get%1082991653.body
}

void cConfigurationDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Get%1082991654.body preserve=yes
  //## end cConfigurationDevice::Get%1082991654.body
}

void cConfigurationDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Get%1082991655.body preserve=yes
  //## end cConfigurationDevice::Get%1082991655.body
}

void cConfigurationDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Get%1082991656.body preserve=yes
   STRING_T obj_name;
   STRING_T obj_property;
   cStringUtils::LeftSplit(name, obj_name, obj_property, '/');
   cConfigurationObject * config_obj = _Configuration->Object(obj_name.c_str());
   if (config_obj != NULL) {
      cProperty * property = config_obj->Property(obj_property.c_str());
      if (property != NULL) {
         if (property->IsInteger()) {
            LONG_T lvalue = property->Value((LONG_T)0);
            char svalue[128] = {0};
            SafePrintf(svalue, sizeof(svalue), "%d", lvalue);
            value = svalue;
         } else if (property->IsReal()) {
            DOUBLE_T fvalue = property->Value((DOUBLE_T)0);
            char svalue[128] = {0};
            SafePrintf(svalue, sizeof(svalue), "%f", fvalue);
            value = svalue;
         } else if (property->IsString()) {
            value = property->Value("");
         }
      }
   }
  //## end cConfigurationDevice::Get%1082991656.body
}

void cConfigurationDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Set%1082991657.body preserve=yes
  //## end cConfigurationDevice::Set%1082991657.body
}

void cConfigurationDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Set%1082991658.body preserve=yes
  //## end cConfigurationDevice::Set%1082991658.body
}

void cConfigurationDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags)
{
  //## begin cConfigurationDevice::Set%1082991659.body preserve=yes
  //## end cConfigurationDevice::Set%1082991659.body
}

void cConfigurationDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value)
{
  //## begin cConfigurationDevice::Cast%1082991660.body preserve=yes
  //## end cConfigurationDevice::Cast%1082991660.body
}

void cConfigurationDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cConfigurationDevice::Read%1082991661.body preserve=yes
  //## end cConfigurationDevice::Read%1082991661.body
}

// Additional Declarations
  //## begin cConfigurationDevice%408CFEAE0138.declarations preserve=yes
  //## end cConfigurationDevice%408CFEAE0138.declarations

//## begin module%408CFEAE0138.epilog preserve=yes
//## end module%408CFEAE0138.epilog
