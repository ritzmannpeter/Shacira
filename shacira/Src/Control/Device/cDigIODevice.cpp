//## begin module%404713CF0138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404713CF0138.cm

//## begin module%404713CF0138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404713CF0138.cp

//## Module: cDigIODevice%404713CF0138; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cDigIODevice.cpp

//## begin module%404713CF0138.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%404713CF0138.additionalIncludes

//## begin module%404713CF0138.includes preserve=yes
//## end module%404713CF0138.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cBlockCache
#include "Control/Device/cBlockCache.h"
// cCache
#include "Control/Device/cCache.h"
// cDigIODevice
#include "Control/Device/cDigIODevice.h"
// cMemoryAddressedDevice
#include "Control/Device/cMemoryAddressedDevice.h"
// cMemIO
#include "Control/Device/DigIO/cMemIO.h"
// cPA150
#include "Control/Device/DigIO/cPA150.h"
// cAddiStandard
#include "Control/Device/DigIO/cAddiStandard.h"
// cDigIO
#include "Control/Device/DigIO/cDigIO.h"
//## begin module%404713CF0138.additionalDeclarations preserve=yes
//## end module%404713CF0138.additionalDeclarations


// Class cDigIODevice 








cDigIODevice::cDigIODevice()
  //## begin cDigIODevice::cDigIODevice%.hasinit preserve=no
      : _CardType(UNDEFINED), _Inputs(0), _Outputs(0), _Simulation(NULL), _IoCard(NULL), _InputCache(NULL), _OutputCache(NULL)
  //## end cDigIODevice::cDigIODevice%.hasinit
  //## begin cDigIODevice::cDigIODevice%.initialization preserve=yes
  //## end cDigIODevice::cDigIODevice%.initialization
{
  //## begin cDigIODevice::cDigIODevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cDigIODevice::cDigIODevice%.body
}

cDigIODevice::cDigIODevice(const cDigIODevice &right)
  //## begin cDigIODevice::cDigIODevice%copy.hasinit preserve=no
      : _CardType(UNDEFINED), _Inputs(0), _Outputs(0), _Simulation(NULL), _IoCard(NULL), _InputCache(NULL), _OutputCache(NULL)
  //## end cDigIODevice::cDigIODevice%copy.hasinit
  //## begin cDigIODevice::cDigIODevice%copy.initialization preserve=yes
  //## end cDigIODevice::cDigIODevice%copy.initialization
{
  //## begin cDigIODevice::cDigIODevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDigIODevice::cDigIODevice%copy.body
}

cDigIODevice::cDigIODevice (cConfigurationObject *config_obj, cCell *cell)
  //## begin cDigIODevice::cDigIODevice%1078400651.hasinit preserve=no
      : _CardType(UNDEFINED), _Inputs(0), _Outputs(0), _Simulation(NULL), _IoCard(NULL), _InputCache(NULL), _OutputCache(NULL)
  //## end cDigIODevice::cDigIODevice%1078400651.hasinit
  //## begin cDigIODevice::cDigIODevice%1078400651.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cDigIODevice::cDigIODevice%1078400651.initialization
{
  //## begin cDigIODevice::cDigIODevice%1078400651.body preserve=yes
   _InputCache = new cBlockCache(this, "inputs", 1);
   _OutputCache = new cBlockCache(this, "outputs", 1);
   SetMemoryInfo("inputs", 1, 0, 0, _InputCache, NULL);
   SetMemoryInfo("outputs", 1, 0, 0, _OutputCache, NULL);
   _CardType = config_obj->PropertyValue("CardType", _CardType);
   _Inputs = config_obj->PropertyValue("Inputs", _Inputs);
   _Outputs = config_obj->PropertyValue("Outputs", _Outputs);
   if (_Simulated) {
      _Simulation = new cMemoryAddressedDevice(config_obj, cell);
   } else {
      switch (_CardType) {
      case IO_ADDI_STANDARD:
         _IoCard = new cAddiStandard;
         break;
      case IO_ADDI_PA150:
         _IoCard = new cPA150;
         break;
      case IO_MEMORY:
         _IoCard = new cMemIO;
         break;
      default:
         throw cError(DIGIO_INVALID_CARDTYPE, 0,
                      cConvUtils::StringValue(_CardType).c_str());
      }
      _Inputs = _IoCard->get_Inputs();
      _Outputs = _IoCard->get_Outputs();
   }
  //## end cDigIODevice::cDigIODevice%1078400651.body
}


cDigIODevice::~cDigIODevice()
{
  //## begin cDigIODevice::~cDigIODevice%.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
      DELETE_OBJECT(cCacheControl, _CacheControl)
   }
   if (_InputCache != NULL) DELETE_OBJECT(cCache, _InputCache)
   if (_OutputCache != NULL) DELETE_OBJECT(cCache, _OutputCache)
   if (_Simulated) {
      DELETE_OBJECT(cMemoryAddressedDevice, _Simulation)
   }
   DELETE_OBJECT(cDigIO, _IoCard)
  //## end cDigIODevice::~cDigIODevice%.body
}



//## Other Operations (implementation)
void cDigIODevice::Start ()
{
  //## begin cDigIODevice::Start%1078400652.body preserve=yes
   if (_InputCache != NULL) _InputCache->Done();
   if (_OutputCache != NULL) _OutputCache->Done();
   _CacheControl = new cCacheControl(this);
   _CacheControl->SetCache(_InputCache);
   _CacheControl->SetCache(_OutputCache);
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.begin();
   while (i != _InfoMap.end()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->Done();
         _CacheControl->SetCache(cache);
      }
      i++;
   }
   _CacheControl->Start();
  //## end cDigIODevice::Start%1078400652.body
}

void cDigIODevice::Stop ()
{
  //## begin cDigIODevice::Stop%1078400653.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
   }
// as consequence of problems with addi data kernel drivers on Win NT 4
DELETE_OBJECT(cDigIO, _IoCard)
  //## end cDigIODevice::Stop%1078400653.body
}

void cDigIODevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cDigIODevice::Cache%1078400654.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Cache(address, size, refresh_type, refresh_value);
   } else {
_ASSERT_UNCOND
   }
  //## end cDigIODevice::Cache%1078400654.body
}

void cDigIODevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
  //## begin cDigIODevice::Buffer%1078400655.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Buffer(address, elements);
   } else {
_ASSERT_UNCOND
   }
  //## end cDigIODevice::Buffer%1078400655.body
}

void cDigIODevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cDigIODevice::Read%1078400656.body preserve=yes
   if (len == 0) return;
   MEMORY_INFO * info = MemoryInfo(buf_spec);
   UCHAR_T granularity = info->granularity;
   len = len / granularity;
   if (!(flags & VF_DEVICE)) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         if (cache->Cached(address, len)) {
            cache->Read(address, len, buf, buf_size);
            return;
         }
      }
   }
   cObjectLock __lock__(&_DeviceMutex);
   if (_Simulated) {
      if (_InterfaceMode) {
         if (strcmp(buf_spec, "inputs") == 0) {
            buf_spec = "outputs";
         } else if (strcmp(buf_spec, "outputs") == 0) {
            buf_spec = "inputs";
         }
      }
      _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
   } else {
      if (strcmp(buf_spec, "inputs") == 0) {
         DigIOSaveInputs(info, buf, buf_size, address);
      } else if (strcmp(buf_spec, "outputs") == 0) {
         DigIOSaveOutputs(info, buf, buf_size, address);
      }
   }
  //## end cDigIODevice::Read%1078400656.body
}

void cDigIODevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cDigIODevice::Write%1078400657.body preserve=yes
   if (len == 0) return;
   cObjectLock __lock__(&_DeviceMutex);
   if (_Simulated) {
      MEMORY_INFO * info = MemoryInfo(buf_spec);
      UCHAR_T granularity = info->granularity;
      len = len / granularity;
      if (_InterfaceMode) {
         if (strcmp(buf_spec, "inputs") == 0) {
            buf_spec = "outputs";
         } else if (strcmp(buf_spec, "outputs") == 0) {
            buf_spec = "inputs";
         }
      }
      _Simulation->Write(buf_spec, address, len, buf, flags);
   } else {
      MEMORY_INFO * info = MemoryInfo(buf_spec);
      UCHAR_T granularity = info->granularity;
      len = len / granularity;
      DigIOLoad(info, buf, address, len);
   }
  //## end cDigIODevice::Write%1078400657.body
}

void cDigIODevice::SetOutput (ULONG_T output_no)
{
  //## begin cDigIODevice::SetOutput%1078400659.body preserve=yes
   _IoCard->SetOutput(output_no);
  //## end cDigIODevice::SetOutput%1078400659.body
}

void cDigIODevice::ResetOutput (ULONG_T output_no)
{
  //## begin cDigIODevice::ResetOutput%1078400661.body preserve=yes
   _IoCard->ResetOutput(output_no);
  //## end cDigIODevice::ResetOutput%1078400661.body
}

BOOL_T cDigIODevice::GetInput (ULONG_T input_no)
{
  //## begin cDigIODevice::GetInput%1078400660.body preserve=yes
   return _IoCard->GetInput(input_no);
  //## end cDigIODevice::GetInput%1078400660.body
}

ULONG_T cDigIODevice::GetInputs (void *inputs, ULONG_T buf_size)
{
  //## begin cDigIODevice::GetInputs%1078400662.body preserve=yes
   return _IoCard->GetInputs(inputs, buf_size);
  //## end cDigIODevice::GetInputs%1078400662.body
}

void cDigIODevice::DigIOLoad (MEMORY_INFO *info, void *buf, ULONG_T address, ULONG_T len)
{
  //## begin cDigIODevice::DigIOLoad%1078410639.body preserve=yes
   _IoCard->WriteOutputs(buf, len);
  //## end cDigIODevice::DigIOLoad%1078410639.body
}

void cDigIODevice::DigIOSaveInputs (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address)
{
  //## begin cDigIODevice::DigIOSaveInputs%1078410640.body preserve=yes
   ULONG_T bytes = _IoCard->GetInputs(buf, buf_size);
  //## end cDigIODevice::DigIOSaveInputs%1078410640.body
}

void cDigIODevice::DigIOSaveOutputs (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address)
{
  //## begin cDigIODevice::DigIOSaveOutputs%1078416426.body preserve=yes
   ULONG_T bytes = _IoCard->ReadOutputs(buf, buf_size);
  //## end cDigIODevice::DigIOSaveOutputs%1078416426.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cDigIODevice::get_CardType () const
{
  //## begin cDigIODevice::get_CardType%40472B3F03C8.get preserve=no
  return _CardType;
  //## end cDigIODevice::get_CardType%40472B3F03C8.get
}

void cDigIODevice::set_CardType (ULONG_T value)
{
  //## begin cDigIODevice::set_CardType%40472B3F03C8.set preserve=no
  _CardType = value;
  //## end cDigIODevice::set_CardType%40472B3F03C8.set
}

ULONG_T cDigIODevice::get_Inputs () const
{
  //## begin cDigIODevice::get_Inputs%4047364A038A.get preserve=no
  return _Inputs;
  //## end cDigIODevice::get_Inputs%4047364A038A.get
}

void cDigIODevice::set_Inputs (ULONG_T value)
{
  //## begin cDigIODevice::set_Inputs%4047364A038A.set preserve=no
  _Inputs = value;
  //## end cDigIODevice::set_Inputs%4047364A038A.set
}

ULONG_T cDigIODevice::get_Outputs () const
{
  //## begin cDigIODevice::get_Outputs%4047366102AF.get preserve=no
  return _Outputs;
  //## end cDigIODevice::get_Outputs%4047366102AF.get
}

void cDigIODevice::set_Outputs (ULONG_T value)
{
  //## begin cDigIODevice::set_Outputs%4047366102AF.set preserve=no
  _Outputs = value;
  //## end cDigIODevice::set_Outputs%4047366102AF.set
}

// Additional Declarations
  //## begin cDigIODevice%404713CF0138.declarations preserve=yes
  //## end cDigIODevice%404713CF0138.declarations

//## begin module%404713CF0138.epilog preserve=yes
//## end module%404713CF0138.epilog
