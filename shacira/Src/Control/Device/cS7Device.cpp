//## begin module%401616F601D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%401616F601D4.cm

//## begin module%401616F601D4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%401616F601D4.cp

//## Module: cS7Device%401616F601D4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cS7Device.cpp

//## begin module%401616F601D4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%401616F601D4.additionalIncludes

//## begin module%401616F601D4.includes preserve=yes
#include "pcs7easy.h"
#include "IPS7LNK.h"
/// PR 12.10.06 - removed bug when checking for device access
///               (flags && VF_DEVICE) (this is always true fo flags != 0) substituted by
///               (flags & VF_DEVICE) in ::Read
//## end module%401616F601D4.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cBlockCache
#include "Control/Device/cBlockCache.h"
// cCache
#include "Control/Device/cCache.h"
// cS7Operator
#include "Control/Device/cS7Operator.h"
// cMemoryAddressedDevice
#include "Control/Device/cMemoryAddressedDevice.h"
// cS7Device
#include "Control/Device/cS7Device.h"
//## begin module%401616F601D4.additionalDeclarations preserve=yes

static STRING_T CommandText(int command)
{
   char text[2] = {0};
   text[0] = (CHAR_T)command;
   return text;
}

static STRING_T AddressText(CONST_STRING_T buf_spec, ULONG_T address)
{
   char text[0x100] = {0};
   SafePrintf(text, sizeof(text), "%s:%04.04d", buf_spec, address);
   return text;
}

#define SIMULATION_DELAY      20

//## end module%401616F601D4.additionalDeclarations


// Class cS7Device 























cS7Device::cS7Device()
  //## begin cS7Device::cS7Device%.hasinit preserve=no
      : _SPSAddress(2), _ClientAddress(1), _SPSType(300), _Com(0), _BusBaudRate(1), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _Handle(0), _Simulation(NULL), _TimerCache(NULL), _InputCache(NULL), _MerkerCache(NULL), _CounterCache(NULL), _OutputCache(NULL)
  //## end cS7Device::cS7Device%.hasinit
  //## begin cS7Device::cS7Device%.initialization preserve=yes
  //## end cS7Device::cS7Device%.initialization
{
  //## begin cS7Device::cS7Device%.body preserve=yes
_ASSERT_UNCOND
  //## end cS7Device::cS7Device%.body
}

cS7Device::cS7Device(const cS7Device &right)
  //## begin cS7Device::cS7Device%copy.hasinit preserve=no
      : _SPSAddress(2), _ClientAddress(1), _SPSType(300), _Com(0), _BusBaudRate(1), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _Handle(0), _Simulation(NULL), _TimerCache(NULL), _InputCache(NULL), _MerkerCache(NULL), _CounterCache(NULL), _OutputCache(NULL)
  //## end cS7Device::cS7Device%copy.hasinit
  //## begin cS7Device::cS7Device%copy.initialization preserve=yes
  //## end cS7Device::cS7Device%copy.initialization
{
  //## begin cS7Device::cS7Device%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cS7Device::cS7Device%copy.body
}

cS7Device::cS7Device (cConfigurationObject *config_obj, cCell *cell)
  //## begin cS7Device::cS7Device%1075189779.hasinit preserve=no
      : _SPSAddress(2), _ClientAddress(1), _SPSType(300), _Com(0), _BusBaudRate(1), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _Handle(0), _Simulation(NULL), _TimerCache(NULL), _InputCache(NULL), _MerkerCache(NULL), _CounterCache(NULL), _OutputCache(NULL)
  //## end cS7Device::cS7Device%1075189779.hasinit
  //## begin cS7Device::cS7Device%1075189779.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cS7Device::cS7Device%1075189779.initialization
{
  //## begin cS7Device::cS7Device%1075189779.body preserve=yes
   DELETE_OBJECT(cBitOperator, _BitOperator)
   _BitOperator = new cS7Operator;
   _TimerCache = new cBlockCache(this, "timer", 1);
   SetMemoryInfo("timer", 1, 'T', 0, _TimerCache, NULL);
   _InputCache = new cBlockCache(this, "inputs", 1);
   SetMemoryInfo("inputs", 1, 'E', 0, _InputCache, NULL);
   _OutputCache = new cBlockCache(this, "outputs", 1);
   SetMemoryInfo("outputs", 1, 'A', 0, _OutputCache, NULL);
   _MerkerCache = new cBlockCache(this, "merker", 1);
   SetMemoryInfo("merker", 1, 'M', 0, _MerkerCache, NULL);
   _CounterCache = new cBlockCache(this, "counter", 1);
   SetMemoryInfo("counter", 1, 'Z', 0, _CounterCache, NULL);
   _BaudRate = config_obj->PropertyValue("BaudRate", _BaudRate);
   _Parity = cSerialChannel::ParityType(config_obj->PropertyValue("Parity", "None").c_str());
   _Handshake = cSerialChannel::HandshakeType(config_obj->PropertyValue("Handshake", "None").c_str());
   _CharLen = (UCHAR_T)config_obj->PropertyValue("CharLen", (ULONG_T)_CharLen);
   _StartBits = (UCHAR_T)config_obj->PropertyValue("StartBits", (ULONG_T)_StartBits);
   _StopBits = (UCHAR_T)config_obj->PropertyValue("StopBits", (ULONG_T)_StopBits);
   _SPSAddress = config_obj->PropertyValue("SPSAddress", _SPSAddress);
   _ClientAddress = config_obj->PropertyValue("ClientAddress", _ClientAddress);
   _SPSType = config_obj->PropertyValue("SPSType", _SPSType);
   _Com = (UCHAR_T)config_obj->PropertyValue("Com", (ULONG_T)_Com);
   _BusBaudRate = (ULONG_T)config_obj->PropertyValue("BusBaudRate", (ULONG_T)_BusBaudRate);

//------------ GH Start Changes ------------------     
   _TCPIPAddress = "0.0.0.0";
   _TCPIPCommunication = false;
   _TCPIPAddress = config_obj->PropertyValue("TCPIPAdress", _TCPIPAddress.c_str());
   if (_TCPIPAddress != "0.0.0.0")
      _TCPIPCommunication = true;
//------------ GH End Changes   ------------------     

   if (_Simulated) {
      _Simulation = new cMemoryAddressedDevice(config_obj, cell, 1);
      _Simulation->set_Node(_SPSAddress);
      return;
   } else {

//------------ GH Start Changes ------------------     
	   if (_TCPIPCommunication)
	   {
		   if (_SPSType == 1200 || _SPSType == 1500)
	          _Handle = IPS7Open (_TCPIPAddress.c_str(), 0, 1, 5000, 5000, 5000);
		   else
			_Handle = IPS7Open (_TCPIPAddress.c_str(), 0, 2, 5000, 5000, 5000);
		  _UsedCommChannel = _TCPIPAddress;
	   }
	   else
	   {
          _Handle = ES7OpenEx(_Com, _SPSAddress, _ClientAddress, _BaudRate, _SPSType, _BusBaudRate);
		  _UsedCommChannel = cConvUtils::StringValue(_Com);
	   }

	   if (_Handle < 0) {
          throw cError(TRAEGER_S7_OPEN, _Handle,
                _UsedCommChannel.c_str(),
                cConvUtils::StringValue(_SPSAddress).c_str(),
                cConvUtils::StringValue(_ClientAddress).c_str());
      }
//------------ GH End Changes   ------------------     
   }
  //## end cS7Device::cS7Device%1075189779.body
}


cS7Device::~cS7Device()
{
  //## begin cS7Device::~cS7Device%.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
      DELETE_OBJECT(cCacheControl, _CacheControl)
   }
   if (_InputCache != NULL) DELETE_OBJECT(cCache, _InputCache)
   if (_OutputCache != NULL) DELETE_OBJECT(cCache, _OutputCache)
   if (_TimerCache != NULL) DELETE_OBJECT(cCache, _TimerCache)
   if (_MerkerCache != NULL) DELETE_OBJECT(cCache, _MerkerCache)
   if (_CounterCache != NULL) DELETE_OBJECT(cCache, _CounterCache)
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.begin();
   while (i != _InfoMap.end()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
//         delete cache;
      }
      i++;
   }
   if (_Simulated) {
      DELETE_OBJECT(cMemoryAddressedDevice, _Simulation)
   } else {
      if (_Handle >= 0) {
//------------ GH Start Changes ------------------     
	   if (_TCPIPCommunication)
		 IPS7Close (_Handle);
       else
         ES7Close(_Handle);
//------------ GH End Changes   ------------------     
      }
   }
  //## end cS7Device::~cS7Device%.body
}



//## Other Operations (implementation)
void cS7Device::Start ()
{
  //## begin cS7Device::Start%1075189780.body preserve=yes
   _CacheControl = new cCacheControl(this);
   _CacheControl->SetCache(_TimerCache);
   _CacheControl->SetCache(_InputCache);
   _CacheControl->SetCache(_OutputCache);
   _CacheControl->SetCache(_MerkerCache);
   _CacheControl->SetCache(_CounterCache);
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
  //## end cS7Device::Start%1075189780.body
}

void cS7Device::Stop ()
{
  //## begin cS7Device::Stop%1075189781.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
   }
  //## end cS7Device::Stop%1075189781.body
}

void cS7Device::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cS7Device::Cache%1075189783.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Cache(address, size, refresh_type, refresh_value);
   } else {
      ULONG_T ident = 0;
      int params = sscanf(buf_spec, "db%d", &ident);
      if (params == 1) {
         cCache * cache = new cBlockCache(this, buf_spec, 1);
         SetMemoryInfo(buf_spec, 1, 'D', ident, cache, NULL);
         cache = SelectCache(buf_spec);
         if (cache != NULL) {
            cache->Cache(address, size, refresh_type, refresh_value);
         } else {
_ASSERT_UNCOND
         }
      }
   }
  //## end cS7Device::Cache%1075189783.body
}

void cS7Device::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
  //## begin cS7Device::Buffer%1075189784.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Buffer(address, elements);
   } else {
      ULONG_T ident = 0;
      int params = sscanf(buf_spec, "db%d", &ident);
      if (params == 1) {
         cCache * cache = new cBlockCache(this, buf_spec, 1);
         SetMemoryInfo(buf_spec, 1, 'D', ident, cache, NULL);
         cache = SelectCache(buf_spec);
         if (cache != NULL) {
            cache->Buffer(address, elements);
         } else {
_ASSERT_UNCOND
         }
      }
   }
  //## end cS7Device::Buffer%1075189784.body
}

void cS7Device::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cS7Device::Read%1075189785.body preserve=yes
   if (len == 0) return;
   MEMORY_INFO * info = Info(buf_spec);
   UCHAR_T granularity = info->granularity;
   len = len / granularity;
   if (!(flags & VF_DEVICE) &&
       (_Cached)) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         cache->Read(address, len, buf, buf_size);
      }
      return;
   }
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
      _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
      if (!_Cached && !_InterfaceMode) {
         cSystemUtils::Suspend(SIMULATION_DELAY);
      }
   } else {
      int retries = 2;
      INT_T err = -1;
      while (err == -1 && retries > 0) {
         err = S7Save(info, buf, buf_size, address, len, 1000);
         retries--;
      }
      if (err == 0) {
         if (!_Connected) {
            _Connected = true;
            cAlarm * alarm = new cAlarm(this, 0x00000001, false);
            RaiseEvent(alarm);
            alarm->Release();
            return;
         }
      } else if (err == -1) {
         if (_Connected) {
            _Connected = false;
            cAlarm * alarm = new cAlarm(this, 0x00000001, true, NOT_CONNECTED);
            alarm->set_Param1(_Name);
            RaiseEvent(alarm);
            alarm->Release();
         }
         throw cError(TRAEGER_S7_READ, err,
                      _UsedCommChannel.c_str(),
                      CommandText(info->command).c_str(),
                      AddressText(buf_spec, address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      } else {
         throw cError(TRAEGER_S7_READ, err,
                      _UsedCommChannel.c_str(),
                      CommandText(info->command).c_str(),
                      AddressText(buf_spec, address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
   }
  //## end cS7Device::Read%1075189785.body
}

void cS7Device::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cS7Device::Write%1075189786.body preserve=yes
   if (len == 0) return;
// PR 07.12.04
// always update cache if possible
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Write(address, len, buf);
   }
   if (flags & VF_BUFFERED ||
       _Buffered) {
      return;
   }
   cObjectLock __lock__(&_DeviceMutex);
   if (_Simulated) {
      _Simulation->Write(buf_spec, address, len, buf, flags);
      if (!_Buffered && !_InterfaceMode) {
         cSystemUtils::Suspend(SIMULATION_DELAY);
      }
   } else {
      MEMORY_INFO * info = Info(buf_spec);
      UCHAR_T granularity = info->granularity;
      len = len / granularity;
      INT_T err = S7Load (info, buf, address, len, 1000);
      if (err != 0) {
         throw cError(TRAEGER_S7_WRITE, err,
                      _UsedCommChannel.c_str(),
                      CommandText(info->command).c_str(),
                      AddressText(buf_spec, address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
   }
  //## end cS7Device::Write%1075189786.body
}

void cS7Device::UseBuffer (CONST_STRING_T buf_spec)
{
  //## begin cS7Device::UseBuffer%1075647703.body preserve=yes
//   MEMORY_INFO * info = Info(buf_spec);
  //## end cS7Device::UseBuffer%1075647703.body
}

MEMORY_INFO * cS7Device::Info (CONST_STRING_T buf_spec)
{
  //## begin cS7Device::Info%1075637926.body preserve=yes
   MEMORY_INFO * info = MemoryInfo(buf_spec);
   if (info != NULL) {
      return info;
   } else {
      ULONG_T ident = 0;
      int params = sscanf(buf_spec, "db%d", &ident);
      if (params == 1) {
         SetMemoryInfo(buf_spec, 1, 'D', ident, NULL, NULL);
         info = MemoryInfo(buf_spec);
         if (info != NULL) {
            return info;
         } else {
         }
      }
   }
   throw cError(DEVICE_NO_MEMORY_INFO, 0, buf_spec);
  //## end cS7Device::Info%1075637926.body
}

INT_T cS7Device::S7Load (MEMORY_INFO *info, void *buf, ULONG_T address, ULONG_T no, ULONG_T timeout)
{
  //## begin cS7Device::S7Load%1075189788.body preserve=yes
   ULONG_T command = info->command;
   ULONG_T granularity = info->granularity;
   ULONG_T db = info->ident;
   switch (command) {
   case 'Z':
//------------ GH Start Changes ------------------     
     if (_TCPIPCommunication)
        return IPS7WrW(_Handle, command, 0, address, no, (LPWORD)buf);
     else
        return ES7WrW(_Handle, command, 0, address, no, (LPWORD)buf);
   case 'T':
     if (_TCPIPCommunication)
        return IPS7WrDW(_Handle, command, 0, address, no, (LPDWORD)buf);
     else
        return ES7WrDW(_Handle, command, 0, address, no, (LPDWORD)buf);
   case 'D':
      switch (granularity) {
      case 1:
         //
         // Offensichtlich werden alle Ausgaben nur über Byteoperanden abgewickelt!!
         //
         if ( _DebugLevel )
         {
            char str1[1000];
            char str2[100];

            SafePrintf(str1, sizeof(str1), "[cS7Device] PC ==> PLC   DB:%2d    Addr:%3d   Count:%3d ==> ", db, address, no );
            BYTE *val = (LPBYTE)buf;
      
            for (unsigned int i=0; i<no && i < 10; i++)
            {
               SafePrintf(str2, sizeof(str2), "%02X   ", *val);
               strcat( str1, str2 );
               val++;
            }

            strcat( str1, "\n" );
            DCPrintf( str1 );
         }
        if (_TCPIPCommunication)
           return IPS7WrB(_Handle, command, db, address, no, (LPBYTE)buf);
        else
           return ES7WrB(_Handle, command, db, address, no, (LPBYTE)buf);
      case 2:
        if (_TCPIPCommunication)
           return IPS7WrW(_Handle, command, db, address, no, (LPWORD)buf);
        else
           return ES7WrW(_Handle, command, db, address, no, (LPWORD)buf);
      case 4:
        if (_TCPIPCommunication)
           return IPS7WrDW(_Handle, command, db, address, no, (LPDWORD)buf);
        else
           return ES7WrDW(_Handle, command, db, address, no, (LPDWORD)buf);
      default:
_ASSERT_UNCOND
      }
   case 'E':
      if (_TCPIPCommunication)
         return IPS7WrB(_Handle, command, 0, address, no, (LPBYTE)buf);
      else
         return ES7WrB(_Handle, command, 0, address, no, (LPBYTE)buf);
   case 'A':
      if (_TCPIPCommunication)
         return IPS7WrB(_Handle, command, 0, address, no, (LPBYTE)buf);
      else
         return ES7WrB(_Handle, command, 0, address, no, (LPBYTE)buf);
//------------ GH End Changes   ------------------     
   default:
_ASSERT_UNCOND
   }
   return -99;
  //## end cS7Device::S7Load%1075189788.body
}

INT_T cS7Device::S7Save (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address, ULONG_T no, ULONG_T timeout)
{
  //## begin cS7Device::S7Save%1075189789.body preserve=yes
   ULONG_T command = info->command;
   ULONG_T granularity = info->granularity;
   ULONG_T db = info->ident;
   switch (command) {
   case 'Z':
      if (_TCPIPCommunication)
         return IPS7RdW(_Handle, command, 0, address, no, (LPWORD)buf);
      else
         return ES7RdW(_Handle, command, 0, address, no, (LPWORD)buf);
   case 'T':
      if (_TCPIPCommunication)
         return IPS7RdDW(_Handle, command, 0, address, no, (LPDWORD)buf);
      else
         return ES7RdDW(_Handle, command, 0, address, no, (LPDWORD)buf);
   case 'D':
      switch (granularity) {
      case 1:
		 {
         //
         // Offensichtlich werden alle Ausgaben nur über Byteoperanden abgewickelt!!
         //
         INT_T result= 0;
         if (_TCPIPCommunication)
            result= IPS7RdB(_Handle, command, db, address, no, (LPBYTE)buf);
         else
            result= ES7RdB(_Handle, command, db, address, no, (LPBYTE)buf);
         if ( _DebugLevel )
         {
            char str1[1000];
            char str2[100];

            SafePrintf(str1, sizeof(str1), "[cS7Device] PLC ==> PC   DB:%2d    Addr:%3d   Count:%3d ==> ", db, address, no );
            BYTE *val = (LPBYTE)buf;

            for (unsigned int i=0; i<no; i++)
            {
               SafePrintf(str2, sizeof(str2), "%02X   ", *val);
               strcat( str1, str2 );
               val++;
            }

            strcat( str1, "\n" );
            DCPrintf( str1 );
         }
         return result;
		 }
      case 2:
         if (_TCPIPCommunication)
            return IPS7RdW(_Handle, command, db, address, no, (LPWORD)buf);
         else
            return ES7RdW(_Handle, command, db, address, no, (LPWORD)buf);
      case 4:
         if (_TCPIPCommunication)
            return IPS7RdDW(_Handle, command, db, address, no, (LPDWORD)buf);
         else
            return ES7RdDW(_Handle, command, db, address, no, (LPDWORD)buf);
      default:
_ASSERT_UNCOND
      }
   case 'E':
      if (_TCPIPCommunication)
         return IPS7RdB(_Handle, command, 0, address, no, (LPBYTE)buf);
      else
         return ES7RdB(_Handle, command, 0, address, no, (LPBYTE)buf);
   case 'A':
      if (_TCPIPCommunication)
         return IPS7RdB(_Handle, command, 0, address, no, (LPBYTE)buf);
      else
         return ES7RdB(_Handle, command, 0, address, no, (LPBYTE)buf);
   default:
_ASSERT_UNCOND
   }
   return -99;
  //## end cS7Device::S7Save%1075189789.body
}

INT_T cS7Device::S7SetBit (MEMORY_INFO *info, ULONG_T address, USHORT_T bit_no, ULONG_T timeout)
{
  //## begin cS7Device::S7SetBit%1075637927.body preserve=yes
return 0;
  //## end cS7Device::S7SetBit%1075637927.body
}

INT_T cS7Device::S7ResetBit (MEMORY_INFO *info, ULONG_T address, USHORT_T bit_no, ULONG_T timeout)
{
  //## begin cS7Device::S7ResetBit%1075189791.body preserve=yes
return 0;
  //## end cS7Device::S7ResetBit%1075189791.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cS7Device::get_SPSAddress () const
{
  //## begin cS7Device::get_SPSAddress%401617530119.get preserve=no
  return _SPSAddress;
  //## end cS7Device::get_SPSAddress%401617530119.get
}

void cS7Device::set_SPSAddress (ULONG_T value)
{
  //## begin cS7Device::set_SPSAddress%401617530119.set preserve=no
  _SPSAddress = value;
  //## end cS7Device::set_SPSAddress%401617530119.set
}

ULONG_T cS7Device::get_ClientAddress () const
{
  //## begin cS7Device::get_ClientAddress%401617F20000.get preserve=no
  return _ClientAddress;
  //## end cS7Device::get_ClientAddress%401617F20000.get
}

void cS7Device::set_ClientAddress (ULONG_T value)
{
  //## begin cS7Device::set_ClientAddress%401617F20000.set preserve=no
  _ClientAddress = value;
  //## end cS7Device::set_ClientAddress%401617F20000.set
}

ULONG_T cS7Device::get_SPSType () const
{
  //## begin cS7Device::get_SPSType%40161CF1030D.get preserve=no
  return _SPSType;
  //## end cS7Device::get_SPSType%40161CF1030D.get
}

void cS7Device::set_SPSType (ULONG_T value)
{
  //## begin cS7Device::set_SPSType%40161CF1030D.set preserve=no
  _SPSType = value;
  //## end cS7Device::set_SPSType%40161CF1030D.set
}

UCHAR_T cS7Device::get_Com () const
{
  //## begin cS7Device::get_Com%40161C4F00AB.get preserve=no
  return _Com;
  //## end cS7Device::get_Com%40161C4F00AB.get
}

void cS7Device::set_Com (UCHAR_T value)
{
  //## begin cS7Device::set_Com%40161C4F00AB.set preserve=no
  _Com = value;
  //## end cS7Device::set_Com%40161C4F00AB.set
}

ULONG_T cS7Device::get_BusBaudRate () const
{
  //## begin cS7Device::get_BusBaudRate%402B88F40280.get preserve=no
  return _BusBaudRate;
  //## end cS7Device::get_BusBaudRate%402B88F40280.get
}

void cS7Device::set_BusBaudRate (ULONG_T value)
{
  //## begin cS7Device::set_BusBaudRate%402B88F40280.set preserve=no
  _BusBaudRate = value;
  //## end cS7Device::set_BusBaudRate%402B88F40280.set
}

ULONG_T cS7Device::get_BaudRate () const
{
  //## begin cS7Device::get_BaudRate%401617530128.get preserve=no
  return _BaudRate;
  //## end cS7Device::get_BaudRate%401617530128.get
}

void cS7Device::set_BaudRate (ULONG_T value)
{
  //## begin cS7Device::set_BaudRate%401617530128.set preserve=no
  _BaudRate = value;
  //## end cS7Device::set_BaudRate%401617530128.set
}

ParityTypes cS7Device::get_Parity () const
{
  //## begin cS7Device::get_Parity%401617530129.get preserve=no
  return _Parity;
  //## end cS7Device::get_Parity%401617530129.get
}

void cS7Device::set_Parity (ParityTypes value)
{
  //## begin cS7Device::set_Parity%401617530129.set preserve=no
  _Parity = value;
  //## end cS7Device::set_Parity%401617530129.set
}

HandshakeTypes cS7Device::get_Handshake () const
{
  //## begin cS7Device::get_Handshake%40161753012A.get preserve=no
  return _Handshake;
  //## end cS7Device::get_Handshake%40161753012A.get
}

void cS7Device::set_Handshake (HandshakeTypes value)
{
  //## begin cS7Device::set_Handshake%40161753012A.set preserve=no
  _Handshake = value;
  //## end cS7Device::set_Handshake%40161753012A.set
}

UCHAR_T cS7Device::get_CharLen () const
{
  //## begin cS7Device::get_CharLen%401617530138.get preserve=no
  return _CharLen;
  //## end cS7Device::get_CharLen%401617530138.get
}

void cS7Device::set_CharLen (UCHAR_T value)
{
  //## begin cS7Device::set_CharLen%401617530138.set preserve=no
  _CharLen = value;
  //## end cS7Device::set_CharLen%401617530138.set
}

UCHAR_T cS7Device::get_StartBits () const
{
  //## begin cS7Device::get_StartBits%401617530139.get preserve=no
  return _StartBits;
  //## end cS7Device::get_StartBits%401617530139.get
}

void cS7Device::set_StartBits (UCHAR_T value)
{
  //## begin cS7Device::set_StartBits%401617530139.set preserve=no
  _StartBits = value;
  //## end cS7Device::set_StartBits%401617530139.set
}

UCHAR_T cS7Device::get_StopBits () const
{
  //## begin cS7Device::get_StopBits%40161753013A.get preserve=no
  return _StopBits;
  //## end cS7Device::get_StopBits%40161753013A.get
}

void cS7Device::set_StopBits (UCHAR_T value)
{
  //## begin cS7Device::set_StopBits%40161753013A.set preserve=no
  _StopBits = value;
  //## end cS7Device::set_StopBits%40161753013A.set
}

STRING_T cS7Device::get_TCPIPAddress () const
{
  //## begin cS7Device::get_TCPIPAddress%4B4C2C370275.get preserve=no
  return _TCPIPAddress;
  //## end cS7Device::get_TCPIPAddress%4B4C2C370275.get
}

void cS7Device::set_TCPIPAddress (STRING_T value)
{
  //## begin cS7Device::set_TCPIPAddress%4B4C2C370275.set preserve=no
  _TCPIPAddress = value;
  //## end cS7Device::set_TCPIPAddress%4B4C2C370275.set
}

STRING_T cS7Device::get_UsedCommChannel () const
{
  //## begin cS7Device::get_UsedCommChannel%4B4C2CBB013E.get preserve=no
  return _UsedCommChannel;
  //## end cS7Device::get_UsedCommChannel%4B4C2CBB013E.get
}

void cS7Device::set_UsedCommChannel (STRING_T value)
{
  //## begin cS7Device::set_UsedCommChannel%4B4C2CBB013E.set preserve=no
  _UsedCommChannel = value;
  //## end cS7Device::set_UsedCommChannel%4B4C2CBB013E.set
}

BOOL_T cS7Device::get_TCPIPCommunication () const
{
  //## begin cS7Device::get_TCPIPCommunication%4B4C2CF4025C.get preserve=no
  return _TCPIPCommunication;
  //## end cS7Device::get_TCPIPCommunication%4B4C2CF4025C.get
}

void cS7Device::set_TCPIPCommunication (BOOL_T value)
{
  //## begin cS7Device::set_TCPIPCommunication%4B4C2CF4025C.set preserve=no
  _TCPIPCommunication = value;
  //## end cS7Device::set_TCPIPCommunication%4B4C2CF4025C.set
}

// Additional Declarations
  //## begin cS7Device%401616F601D4.declarations preserve=yes
  //## end cS7Device%401616F601D4.declarations

//## begin module%401616F601D4.epilog preserve=yes
//## end module%401616F601D4.epilog
