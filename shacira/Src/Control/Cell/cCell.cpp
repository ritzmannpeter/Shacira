//## begin module%3A51D539000C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A51D539000C.cm

//## begin module%3A51D539000C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A51D539000C.cp

//## Module: cCell%3A51D539000C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cCell.cpp

//## begin module%3A51D539000C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A51D539000C.additionalIncludes

//## begin module%3A51D539000C.includes preserve=yes

/// PR 27.07.06 - reporting errors in up- and download

//## end module%3A51D539000C.includes

// eb_sema
#include "base/eb_sema.hpp"
// cTokenizer
#include "System/cTokenizer.h"
// cStringUtils
#include "System/cStringUtils.h"
// cInfo
#include "System/Objects/cInfo.h"
// cProgress
#include "System/Objects/cProgress.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cContext
#include "System/Database/cContext.h"
// cSharedLibrary
#include "System/Sys/cSharedLibrary.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cCell
#include "Control/Cell/cCell.h"
// cLocalContext
#include "Control/LocalDatabase/cLocalContext.h"
// cDevice
#include "Control/Device/cDevice.h"
// cDeviceFactory
#include "Control/Device/cDeviceFactory.h"
//## begin module%3A51D539000C.additionalDeclarations preserve=yes
//## end module%3A51D539000C.additionalDeclarations


// Class cCell 







cCell::cCell()
  //## begin cCell::cCell%.hasinit preserve=no
      : _DevicesBuffered(false), _DevicesCached(false), _LocalContext(NULL)
  //## end cCell::cCell%.hasinit
  //## begin cCell::cCell%.initialization preserve=yes
  //## end cCell::cCell%.initialization
{
  //## begin cCell::cCell%.body preserve=yes
_ASSERT_UNCOND
  //## end cCell::cCell%.body
}

cCell::cCell(const cCell &right)
  //## begin cCell::cCell%copy.hasinit preserve=no
      : _DevicesBuffered(false), _DevicesCached(false), _LocalContext(NULL)
  //## end cCell::cCell%copy.hasinit
  //## begin cCell::cCell%copy.initialization preserve=yes
  //## end cCell::cCell%copy.initialization
{
  //## begin cCell::cCell%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCell::cCell%copy.body
}

cCell::cCell (cLocalContext *context, cConfigurationObject *config_obj)
  //## begin cCell::cCell%978422270.hasinit preserve=no
      : _DevicesBuffered(false), _DevicesCached(false), _LocalContext(NULL)
  //## end cCell::cCell%978422270.hasinit
  //## begin cCell::cCell%978422270.initialization preserve=yes
  //## end cCell::cCell%978422270.initialization
{
  //## begin cCell::cCell%978422270.body preserve=yes
_ASSERT_COND(context != NULL)
_ASSERT_COND(config_obj != NULL)
   InfoPrintf("creating cell %s\n", _Name.c_str());
   _LocalContext = context;
   _Name = config_obj->get_Name();

   // add devices
   CONFOBJ_VECTOR_T obj_vec;
   config_obj->PropertyValue("Devices", obj_vec);
   ULONG_T size = obj_vec.size();
   ULONG_T i = 0;
   InfoPrintf("loading devices ...\n");
   for (i=0; i<size; i++) {
      cConfigurationObject * device_obj = (cConfigurationObject*)obj_vec[i];
      InfoPrintf("device %s ...\n", device_obj->get_Name().c_str());
      cDevice * device = cDeviceFactory::CreateDevice(device_obj, this);
      if (device != NULL) {
         STRING_T device_name = device->get_Name();
         ListenTo(device);
         _Devices[device_name.c_str()] = device;
      } else {
         STRING_T device_name = device_obj->get_Name();
         throw cError(CELL_CREATE_DEVICE, 0, device_name.c_str());
      }
      InfoPrintf("device %s done\n", device_obj->get_Name().c_str());
   }
   InfoPrintf("loading devices done\n");

   // add interfaces
   obj_vec.clear();
   config_obj->PropertyValue("Interfaces", obj_vec);
   size = obj_vec.size();
   InfoPrintf("loading interfaces ...\n");
   for (i=0; i<size; i++) {
      cConfigurationObject * interface_obj = (cConfigurationObject*)obj_vec[i];
      InfoPrintf("interface %s ...\n", interface_obj->get_Name().c_str());
      cDevice * itf = cDeviceFactory::CreateDevice(interface_obj, this);
      if (itf != NULL) {
         STRING_T interface_name = itf->get_Name();
         ListenTo(itf);
         _Devices[interface_name.c_str()] = itf;
         itf->set_InterfaceMode(true);
      } else {
         STRING_T device_name = interface_obj->get_Name();
         throw cError(CELL_CREATE_DEVICE, 0, device_name.c_str());
      }
      InfoPrintf("interface %s done\n", interface_obj->get_Name().c_str());
   }
   InfoPrintf("loading interfaces done\n");

   SetDevicesCached(true);
   SetDevicesBuffered(true);
  //## end cCell::cCell%978422270.body
}

cCell::cCell (cLocalContext *context)
   : _DevicesBuffered(false), _DevicesCached(false), _LocalContext(NULL)
{
_ASSERT_COND(context != NULL)
   _LocalContext = context;
   _Name = context->get_Name();
}

cCell::~cCell()
{
  //## begin cCell::~cCell%.body preserve=yes
   Stop();
   std::list<STRING_T> free_devices;
   std::map<STRING_T,cDevice*>::iterator j = _Devices.begin();
   while (j != _Devices.end()) {
      cDevice * device = (*j).second;
      STRING_T device_name = device->get_Name();
      if (!device->HasReferences()) {
         free_devices.push_back(device_name);
         InfoPrintf("deleting device %s\n", device_name.c_str());
         DELETE_OBJECT(cDevice,device)
      }
      j++;
   }
   std::list<STRING_T>::const_iterator i = free_devices.begin();
   while (i != free_devices.end()) {
      _Devices.erase((*i));
      i++;
   }
   j = _Devices.begin();
   while (j != _Devices.end()) {
      cDevice * device = (*j).second;
      if (device->HasReferences()) {
         InfoPrintf("deleting device %s\n", device->get_Name().c_str());
         DELETE_OBJECT(cDevice,device)
      }
      j++;
   }
   _Devices.clear();
  //## end cCell::~cCell%.body
}



//## Other Operations (implementation)
void cCell::Event (cTransientObject *object)
{
  //## begin cCell::Event%983863599.body preserve=yes
   _LocalContext->Send(object);
  //## end cCell::Event%983863599.body
}

void cCell::Start ()
{
  //## begin cCell::Start%982075365.body preserve=yes
   StartDevices();
  //## end cCell::Start%982075365.body
}

void cCell::Stop ()
{
  //## begin cCell::Stop%983778357.body preserve=yes
	StopDevices();
  //## end cCell::Stop%983778357.body
}

cDevice * cCell::Device (CONST_STRING_T device_name)
{
  //## begin cCell::Device%1047978426.body preserve=yes
   std::map<STRING_T, cDevice*>::const_iterator i = _Devices.find(device_name);
	if (i == _Devices.end()) {
		return NULL;
	} else {
      cDevice * device = (*i).second;
      return device;
	}
  //## end cCell::Device%1047978426.body
}

BOOL_T cCell::ResolveItem (CONST_STRING_T path, STRING_T &device_name, STRING_T &item_name)
{
  //## begin cCell::ResolveItem%1072085848.body preserve=yes
_ASSERT_UNCOND
   return false;
  //## end cCell::ResolveItem%1072085848.body
}

void cCell::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value)
{
  //## begin cCell::SetDeviceValue%1122475165.body preserve=yes
   STRING_T device_name;
   STRING_T new_address;
   SplitAddress(address, device_name, new_address);
   cDevice * device = Device(device_name.c_str());
   if (device != NULL) {
      device->Set(buf_spec, new_address.c_str(), value);
   }
  //## end cCell::SetDeviceValue%1122475165.body
}

void cCell::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value)
{
  //## begin cCell::GetDeviceValue%1078912378.body preserve=yes
   STRING_T device_name;
   STRING_T new_address;
   SplitAddress(address, device_name, new_address);
   cDevice * device = Device(device_name.c_str());
   if (device != NULL) {
      device->Get(buf_spec, new_address.c_str(), value);
   }
  //## end cCell::GetDeviceValue%1078912378.body
}

void cCell::SetDevicesBuffered (BOOL_T state)
{
  //## begin cCell::SetDevicesBuffered%1091556105.body preserve=yes
   _DevicesBuffered = state;
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      device->set_Buffered(state);
      i++;
   }
  //## end cCell::SetDevicesBuffered%1091556105.body
}

BOOL_T cCell::GetDevicesBuffered ()
{
  //## begin cCell::GetDevicesBuffered%1126515329.body preserve=yes
   return _DevicesBuffered;
  //## end cCell::GetDevicesBuffered%1126515329.body
}

void cCell::SetDevicesCached (BOOL_T state)
{
  //## begin cCell::SetDevicesCached%1091556106.body preserve=yes
   _DevicesCached = state;
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      device->set_Cached(state);
      i++;
   }
  //## end cCell::SetDevicesCached%1091556106.body
}

BOOL_T cCell::GetDevicesCached ()
{
  //## begin cCell::GetDevicesCached%1126515330.body preserve=yes
   return _DevicesCached;
  //## end cCell::GetDevicesCached%1126515330.body
}

void cCell::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cCell::Save%1122475167.body preserve=yes
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      try {
         device->Save(refresh_type, refresh_value);
      } catch (cError & e) {
         ErrorPrintf("%s Save Block of %s\n", (CONST_STRING_T)e, device->get_Name().c_str());
      } catch (...) {
         ErrorPrintf("General exception in Save Block of %s\n", device->get_Name().c_str());
      }
      i++;
   }
  //## end cCell::Save%1122475167.body
}

void cCell::Download (ULONG_T ctrl)
{
  //## begin cCell::Download%1122475168.body preserve=yes
   if (_LocalContext == NULL ||
       _Devices.size() == 0) {
      return;
   }
   BOOL_T cached_state = _DevicesCached;
   BOOL_T buffered_state = _DevicesBuffered;
   SetDevicesBuffered(false);
   BOOL_T failed = false;
   cInfo * info = NULL;
   if (_LocalContext != NULL) {
      info = new cInfo(this, IT_USER_INFO, DOWNLOAD_MESSAGE, "");
      _LocalContext->Send(info);
      info->Release();
   }
   _LocalContext->Initialize(SH_PRE_DOWNLOAD);
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      try {
         SetDevicesCached(true);
         device->Download();
         if (_LocalContext != NULL) {
            info = new cInfo(this, IT_USER_INFO, DOWNLOAD_MESSAGE, "");
            _LocalContext->Send(info);
            info->Release();
         }
         i++;
      } catch (cError & e) {
         SetDevicesCached(false);
         cSystemUtils::Suspend(200);
         if (!failed) {
            ErrorPrintf("%s while downloading data to %s\n", (const char *)e, device->get_Name().c_str());
            info = new cInfo(this, IT_USER_INFO, DOWNLOAD_NO_CONNECTION, "");
            _LocalContext->Send(info);
            info->Release();
            cSystemUtils::Suspend(200);
            failed = true;
         }
      } catch (...) {
         if (!failed) {
            ErrorPrintf("unhandled exception while downloading data\n");
            info = new cInfo(this, IT_USER_INFO, DOWNLOAD_UNKNOWN_ERROR, "");
            _LocalContext->Send(info);
            info->Release();
            cSystemUtils::Suspend(200);
            failed = true;
         }
      }
   }
   SetDevicesCached(cached_state);
   SetDevicesBuffered(buffered_state);
   info = new cInfo(this, IT_USER_INFO, 0, "");
   _LocalContext->Send(info);
   info->Release();
   _LocalContext->Initialize(SH_POST_DOWNLOAD);
  //## end cCell::Download%1122475168.body
}

void cCell::Upload (ULONG_T ctrl)
{
  //## begin cCell::Upload%1122475169.body preserve=yes
   if (_LocalContext != NULL) {
      BOOL_T cached_state = _DevicesCached;
      SetDevicesCached(false);
      BOOL_T failed = false;
      cInfo * info = NULL;
      info = new cInfo(this, IT_USER_INFO, UPLOAD_MESSAGE, "");
      _LocalContext->Send(info);
      info->Release();
      _LocalContext->Initialize(SH_PRE_UPLOAD);
      std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
      while (i != _Devices.end()) {
         cDevice * device = (*i).second;
         try {
            device->Upload();
            if (_LocalContext != NULL) {
               info = new cInfo(this, IT_USER_INFO, UPLOAD_MESSAGE, "");
               _LocalContext->Send(info);
               info->Release();
            }
            i++;
         } catch (cError & e) {
            SetDevicesCached(false);
            cSystemUtils::Suspend(200);
            if (!failed) {
               ErrorPrintf("%s while uploading data from %s\n", (const char *)e, device->get_Name().c_str());
               info = new cInfo(this, IT_USER_INFO, UPLOAD_NO_CONNECTION, "");
               _LocalContext->Send(info);
               info->Release();
               cSystemUtils::Suspend(200);
               failed = true;
            }
         } catch (...) {
            if (!failed) {
               ErrorPrintf("unhandled exception while uploading data\n");
               info = new cInfo(this, IT_USER_INFO, UPLOAD_UNKNOWN_ERROR, "");
               _LocalContext->Send(info);
               info->Release();
               cSystemUtils::Suspend(200);
               failed = true;
            }
         }
      }
      SetDevicesCached(cached_state);
      info = new cInfo(this, IT_USER_INFO, 0, "");
      _LocalContext->Send(info);
      info->Release();
      _LocalContext->Initialize(SH_POST_UPLOAD);
   } else {
      ErrorPrintf("local context is null while uploading data\n");
   }
  //## end cCell::Upload%1122475169.body
}

void cCell::SetProgress (ULONG_T indicator, ULONG_T value)
{
  //## begin cCell::SetProgress%1120661021.body preserve=yes
   cProgress * progress = new cProgress(this, indicator, value);
   _LocalContext->Send(progress);
   progress->Release();
  //## end cCell::SetProgress%1120661021.body
}

void cCell::StartDevices ()
{
  //## begin cCell::StartDevices%1072801792.body preserve=yes
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      device->Start();
      i++;
   }
  //## end cCell::StartDevices%1072801792.body
}

void cCell::StopDevices ()
{
  //## begin cCell::StopDevices%1072801793.body preserve=yes
   std::map<STRING_T,cDevice*>::const_iterator i = _Devices.begin();
   while (i != _Devices.end()) {
      cDevice * device = (*i).second;
      device->Stop();
      i++;
   }
  //## end cCell::StopDevices%1072801793.body
}

void cCell::SplitAddress (CONST_STRING_T address, STRING_T &device_name, STRING_T &new_address)
{
  //## begin cCell::SplitAddress%1082991645.body preserve=yes
   cStringUtils::LeftSplit(address, device_name, new_address, '/');
  //## end cCell::SplitAddress%1082991645.body
}

cContext * cCell::Context ()
{
  //## begin cCell::Context%1122641992.body preserve=yes
   return _LocalContext;
  //## end cCell::Context%1122641992.body
}

// Additional Declarations
  //## begin cCell%3A51D539000C.declarations preserve=yes
  //## end cCell%3A51D539000C.declarations

//## begin module%3A51D539000C.epilog preserve=yes
//## end module%3A51D539000C.epilog
