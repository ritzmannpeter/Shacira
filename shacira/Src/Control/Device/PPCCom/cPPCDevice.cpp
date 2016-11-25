//## begin module%3FCF4E67000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FCF4E67000F.cm

//## begin module%3FCF4E67000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FCF4E67000F.cp

//## Module: cPPCDevice%3FCF4E67000F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCDevice.cpp

//## begin module%3FCF4E67000F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FCF4E67000F.additionalIncludes

//## begin module%3FCF4E67000F.includes preserve=yes

/// PR 13.05.05 - changed caching behaviour in Read and Write due to flag VF_DEVICE
/// PR 02.06.05 - overloaded method Changed(...) of cDevice to enable data change
///               events of bit mapped variables
/// PR 16.06.05 - also read buffered addresses from cache in Read
/// PR 01.07.05 - removed bug handling interface based access in ::Read
///             - started client thread when constructing the device object
///               in case of tcp/ip based communication
///             - retry handling improved
///             - added verify mechanism switchable via property _Verify
/// PR 03.08.05 - moved control of _Connected state to a position when
///               transmission of data is really necessary
///             - removed protection in ReadBit and WriteBit
///               this protection is no more used because accessing real
///               device resources are protected in the device specific
///               access methods
///               this protection slows down reaction time of the user
///               interface, when a device connection has gone away
/// PR 15.08.05 - activated native write bit operation
/// PR 12.09.05 - handled every possible branch of read and write operations
///               resp. buffering and caching
/// PR 28.03.06 - added command retries to device
/// PR 30.03.06 - exception handling added for client communication in SendBlock
/// PR 19.04.06 - added missing cache refresh in WriteBit
/// PR 21.04.06 - changed cache read behaviour when reading bits to avoid
///               reading volatile bits from cache when device is requested
/// PR 12.10.06 - removed bug when checking for device access
///               (flags && VF_DEVICE) (this is always true fo flags != 0) substituted by
///               (flags & VF_DEVICE) in ::Read and ::Write
/// PR 12.01.07 - disabled block debugging in non interface mode
///             - implemeted timing protocol (can be enabled via property TimingProtocol)
/// PR 15.02.07 - implemented virtual method ::MappingValid
/// PR 23.04.07 - bits now are updated in cache blocks when read from device
/// PR 26.11.07 - implemented variable block length up to MAX_BLOCK_LEN
/// PR 09.01.08 - fixed bug in block segmentation of SupplyData
/// PR 31.03.08 - delete "no connection" alarm only from state is disconnected
/// PR 23.06.08 - fixed bug in ::ReadBit (invalid length supplied to cache->Read and cache->Write)
/// PR 17.04.09 - fixed bug in ::WriteBit (avoiding to acces PLC in buffered Writes)
/// PR 18.06.09 - fixed bug in ::RequestData (evaluate data blocks only if nread > 0)
///               suppplied by Horst Anselm FM
/// PR 29.03.11 - integrated mechanism to synchronize PPCCOM requests with PPCCOM replies


//## end module%3FCF4E67000F.includes

// cCSComm
#include "System/ClientServer/cCSComm.h"
// cUDPComm
#include "System/ClientServer/cUDPComm.h"
// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cStringCache
#include "Control/Device/cStringCache.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cBlockCache
#include "Control/Device/cBlockCache.h"
// cCache
#include "Control/Device/cCache.h"
// cMemoryAddressedDevice
#include "Control/Device/cMemoryAddressedDevice.h"
// cPPCSerialComm
#include "Control/Device/PPCCom/cPPCSerialComm.h"
// cPPCServer
#include "Control/Device/PPCCom/cPPCServer.h"
// cPPCClient
#include "Control/Device/PPCCom/cPPCClient.h"
// cPPCOperator
#include "Control/Device/PPCCom/cPPCOperator.h"
// cPPCDevice
#include "Control/Device/PPCCom/cPPCDevice.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3FCF4E67000F.additionalDeclarations preserve=yes

#define CMD_RETRIES  1
#define DATA_SIZE (_BlockLength - 2)

#define WORD_SWAP(w)    (((w&0x00ff)<<8)+((w&0xff00)>>8))
void __memswap(unsigned short * target, unsigned short * source, unsigned long words)
{
   for (unsigned long i=0; i<words; i++) {
      target[i] = WORD_SWAP(source[i]);
   }
}

/// buffer area for register and logic word data
/// does not depend on block size
#define TRANSFER_BUF_SIZE     (0x1000)
#define REG_BUF_SIZE          (TRANSFER_BUF_SIZE/2)

#define DISCONNECT_ERR_COUNT  2

#define REG_BUFFER      0
#define LOG_BUFFER      1

/* ISCOS-Funktionen A-SET */
#define ICMD_MS   0x81     /* display module map/status */
#define ICMD_IB   0x82     /* input buffer */
#define ICMD_OB   0x83     /* output buffer */
#define ICMD_DR   0x84     /* display register */
#define ICMD_ER   0x85     /* enter register */
#define ICMD_DP   0x86     /* dump user module */
#define ICMD_SS   0x87     /* start/stop control action */

/* ISCOS-Funktionen B-SET */
#define ICMD_CM   0x88     /* create user module */
#define ICMD_DU   0x89     /* delete user module */
#define ICMD_LP   0x8a     /* list user module */
#define ICMD_SM   0x8b     /* set mode RAM/PROM */
#define ICMD_OA   0x8c     /* load PROM into RAM */
#define ICMD_AO   0x8d     /* load RAM into EEPROM */
#define ICMD_IS   0x8e     /* insert instruction(s) */
#define ICMD_CH   0x8f     /* change instruction(s) */
#define ICMD_DE   0x90     /* delete instruction(s) */
#define ICMD_SB   0x91     /* set breakpoint */
#define ICMD_NB   0x92     /* next breakpoint */
#define ICMD_RB   0x93     /* reset breakpoint */
#define ICMD_DG   0x94     /* declare "general" module */
#define ICMD_DC   0x95     /* declare "carrier" module */
#define ICMD_SE   0x96     /* search instruction(s) */
#define ICMD_CF   0x97     /* configuration list */

/* ISCOS-Funktionen C-SET */
#define ICMD_GI   0x9a     /* get ident */
#define ICMD_LU   0x9b     /* load user module */
#define ICMD_SU   0x9c     /* save user module */
#define ICMD_LC   0x9d     /* load carrier modules */
#define ICMD_SC   0x9e     /* save carrier modules */
#define ICMD_LL   0x9f     /* load logic buffer(s) */
#define ICMD_SL   0xa0     /* save logic buffer(s) */
#define ICMD_LR   0xa1     /* load register(s) */
#define ICMD_SR   0xa2     /* save register(s) */
#define ICMD_GM   0xa3     /* get message */

/* ISCOS-Funktionen C-SET */
#define ICMD_DM   0xa4     /* display memory */
#define ICMD_WM   0xa5     /* write memory */

#define FUNCTION_NOT_AVAILABLE		7
#define NO_SS0_1_2_3						21
#define ILLEGAL_BITSET_PARAMETER		22
#define ILLEGAL_BIT_ADDRESS			23
#define REG_NO_OUT_OF_RANGE			26
#define ILLEGAL_SAVREG_PARAMETER		10
#define ILLEGAL_SAVLOG_PARAMETER		11
#define ILLEGAL_LODREG_PARAMETER		12
#define ILLEGAL_LODLOG_PARAMETER		13
#define SYSTEM_ERROR          		20
#define BLOCK_PROTOCOL_ERROR        50

#define PROGRAM_RUNNING					0x10
#define PROGRAM_ERROR  					0x20
#define POWER_FAILURE  					0x40
#define FIRMWARE_ERROR 					0x80

#define SET_SPS_STATE(state, block) \
	if (state & POWER_FAILURE) state &= ~POWER_FAILURE; \
	block[1] |= state;

#define BitmapSet(bitmap, first_addr, symbols, op)

// PPCCOM slave thread

class cPPCSlave: public cControlThread
{
public:
   cPPCSlave(cPPCDevice * device) {_Device = device;};
   virtual ~cPPCSlave() {};
   INT_T MainFunc(void *extra);
private:
   cPPCDevice * _Device;
};

INT_T cPPCSlave::MainFunc(void *extra)
{
MAINFUNC_PROLOG(_Name.c_str())
   while (!(_Terminated || _Terminating)) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      _Device->Process();
MAINFUNC_LOOP_EPILOG
 		if (!_Terminated) cSystemUtils::Suspend(10);
   }
   return 0;
MAINFUNC_EPILOG
};

#define PROTO_FILE      "PPCCOM.LOG"
static char _PrintBuf[0x2000] = {0};
static STRING_T _ComProtoFile = "";
void LogPrintf(CONST_STRING_T fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_PrintBuf, sizeof(_PrintBuf)-1, fmt_str, args);
   va_end(args);
   _ComProtoFile = cFileSystemUtils::AppendPath(cResources::LogPath().c_str(), PROTO_FILE);
   FILE * stream = fopen(_ComProtoFile.c_str(), "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _PrintBuf);
      fclose(stream);
   }
   printf("%s", _PrintBuf);
}


#define TIME_PROTO_FILE      "PPCTIM.LOG"
static char _TimePrintBuf[0x2000] = {0};
static STRING_T _TimeProtoFile = "";
void TimePrintf(CONST_STRING_T fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_TimePrintBuf, sizeof(_TimePrintBuf)-1, fmt_str, args);
   va_end(args);
   _TimeProtoFile = cFileSystemUtils::AppendPath(cResources::LogPath().c_str(), TIME_PROTO_FILE);
   FILE * stream = fopen(_TimeProtoFile.c_str(), "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _TimePrintBuf);
      fclose(stream);
   }
}

//## end module%3FCF4E67000F.additionalDeclarations


// Class cPPCDevice 

























cPPCDevice::cPPCDevice()
  //## begin cPPCDevice::cPPCDevice%.hasinit preserve=no
     : _IscosNo(0), _BlockTimeout(3000), _BlockRetries(3), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _ReadPort(19000), _WritePort(19000), _Host("localhost"), _SpsState(0), _SpsVersion(0), _ErrCount(0), _VerifyBufSize(0x20000), _VerifyBuf(NULL), _BlockLength(STANDARD_PPCCOM_BLOCK_LEN), _AdjustBlockLength(false), _Server(NULL), _Client(NULL), _SerialChannel(NULL), _CSComm(NULL), _Simulation(NULL), _RegisterCache(NULL), _LogicCache(NULL), _MasterRequestId(0), _SlaveRequestId(0), _SafeCommunication(true), _SwapRequestId(false), _FuncBlockSize(14)
  //## end cPPCDevice::cPPCDevice%.hasinit
  //## begin cPPCDevice::cPPCDevice%.initialization preserve=yes
  //## end cPPCDevice::cPPCDevice%.initialization
{
  //## begin cPPCDevice::cPPCDevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCDevice::cPPCDevice%.body
}

cPPCDevice::cPPCDevice(const cPPCDevice &right)
  //## begin cPPCDevice::cPPCDevice%copy.hasinit preserve=no
     : _IscosNo(0), _BlockTimeout(3000), _BlockRetries(3), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _ReadPort(19000), _WritePort(19000), _Host("localhost"), _SpsState(0), _SpsVersion(0), _ErrCount(0), _VerifyBufSize(0x20000), _VerifyBuf(NULL), _BlockLength(STANDARD_PPCCOM_BLOCK_LEN), _AdjustBlockLength(false), _Server(NULL), _Client(NULL), _SerialChannel(NULL), _CSComm(NULL), _Simulation(NULL), _RegisterCache(NULL), _LogicCache(NULL), _MasterRequestId(0), _SlaveRequestId(0), _SafeCommunication(true), _SwapRequestId(false), _FuncBlockSize(14)
  //## end cPPCDevice::cPPCDevice%copy.hasinit
  //## begin cPPCDevice::cPPCDevice%copy.initialization preserve=yes
  //## end cPPCDevice::cPPCDevice%copy.initialization
{
  //## begin cPPCDevice::cPPCDevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCDevice::cPPCDevice%copy.body
}

cPPCDevice::cPPCDevice (cConfigurationObject *config_obj, cCell *cell)
  //## begin cPPCDevice::cPPCDevice%1070550133.hasinit preserve=no
     : _IscosNo(0), _BlockTimeout(3000), _BlockRetries(3), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _ReadPort(19000), _WritePort(19000), _Host("localhost"), _SpsState(0), _SpsVersion(0), _ErrCount(0), _VerifyBufSize(0x20000), _VerifyBuf(NULL), _BlockLength(STANDARD_PPCCOM_BLOCK_LEN), _AdjustBlockLength(false), _Server(NULL), _Client(NULL), _SerialChannel(NULL), _CSComm(NULL), _Simulation(NULL), _RegisterCache(NULL), _LogicCache(NULL), _MasterRequestId(0), _SlaveRequestId(0), _SafeCommunication(true), _SwapRequestId(false), _FuncBlockSize(14)
  //## end cPPCDevice::cPPCDevice%1070550133.hasinit
  //## begin cPPCDevice::cPPCDevice%1070550133.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cPPCDevice::cPPCDevice%1070550133.initialization
{
  //## begin cPPCDevice::cPPCDevice%1070550133.body preserve=yes
   DELETE_OBJECT(cBitOperator, _BitOperator)
   _BitOperator = new cPPCOperator;
   _RegisterCache = new cBlockCache(this, "register");
   SetMemoryInfo("register", 2, 'T', 0, _RegisterCache, NULL);
   _LogicCache = new cBlockCache(this, "logic");
   SetMemoryInfo("logic", 2, 'T', 0, _LogicCache, NULL);
   _BaudRate = config_obj->PropertyValue("BaudRate", _BaudRate);
   _Parity = cSerialChannel::ParityType(config_obj->PropertyValue("Parity", "None").c_str());
   _Handshake = cSerialChannel::HandshakeType(config_obj->PropertyValue("Handshake", "None").c_str());
   _CharLen = (UCHAR_T)config_obj->PropertyValue("CharLen", (ULONG_T)_CharLen);
   _StartBits = (UCHAR_T)config_obj->PropertyValue("StartBits", (ULONG_T)_StartBits);
   _StopBits = (UCHAR_T)config_obj->PropertyValue("StopBits", (ULONG_T)_StopBits);
   _ReadPort = config_obj->PropertyValue("ReadPort", _ReadPort);
   _WritePort = config_obj->PropertyValue("WritePort", _WritePort);
   _Host = config_obj->PropertyValue("Host", _Host.c_str());
   _IscosNo = (UCHAR_T)config_obj->PropertyValue("IscosNo", (ULONG_T)_IscosNo);
   _BlockTimeout = config_obj->PropertyValue("BlockTimeout", _BlockTimeout);
   _BlockRetries = config_obj->PropertyValue("BlockRetries", _BlockRetries);
   _BlockLength = config_obj->PropertyValue("BlockLength", _BlockLength);
   if (_BlockLength > MAX_BLOCK_LEN) {
      _BlockLength = MAX_BLOCK_LEN;
   }
   _AdjustBlockLength = config_obj->PropertyValue("AdjustBlockLength", _AdjustBlockLength);
   if (_Simulated) {
      _Simulation = new cMemoryAddressedDevice(config_obj, cell, 2);
      _Simulation->set_Node(_IscosNo);
   } else {
      cConfigurationObject * serial_channel_obj = config_obj->PropertyValue("SerialChannel", NULL_OBJECT);
      if (serial_channel_obj != NULL) {
         _SerialChannel = cSerialChannelFactory::CreateSerialChannel(serial_channel_obj);
         _SerialChannel->Open();
         _SerialChannel->SetBaudRate(_BaudRate);
         _SerialChannel->SetCharLen(_CharLen);
         _SerialChannel->SetStartBits(_StartBits);
         _SerialChannel->SetStopBits(_StopBits);
         _SerialChannel->SetParity(_Parity);
      } else {
         if (!_Simulated) {
// PR 01.07.05
// _Client must be instantiated and started as early as possible
// to avoid startup communication errors that potentially stop the application
            _CSComm = new cUDPComm((USHORT_T)_ReadPort, (USHORT_T)_WritePort, _Host.c_str());
            _Client = new cPPCClient(_CSComm, this);
            _Client->set_Name("PPCClient");
            _Client->Start();
         }
      }
   }
  //## end cPPCDevice::cPPCDevice%1070550133.body
}


cPPCDevice::~cPPCDevice()
{
  //## begin cPPCDevice::~cPPCDevice%.body preserve=yes
   if (_Client != NULL) {
      _Client->Stop();
   }
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
      DELETE_OBJECT(cCacheControl, _CacheControl)
   }
   if (_RegisterCache != NULL) {
      DELETE_OBJECT(cCache, _RegisterCache)
   }
   if (_LogicCache != NULL) {
      DELETE_OBJECT(cCache, _LogicCache)
   }
   if (_Simulated) {
      DELETE_OBJECT(cMemoryAddressedDevice, _Simulation)
   } else {
      if (_SerialChannel != NULL) {
         _SerialChannel->Close();
         DELETE_OBJECT(cSerialChannel, _SerialChannel);
      }
   }
   DELETE_OBJECT(cPPCClient,_Client)
  //## end cPPCDevice::~cPPCDevice%.body
}



//## Other Operations (implementation)
#include "Control/Cell/cCell.h"
#include "Control/LocalDatabase/cLocalContext.h"
BOOL_T cPPCDevice::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   if (PARAM_NAME_EQUALS(name, "ConnectionTest")) {
      BOOL_T  rc = false;
#ifndef UNSAFE_VERSION
      if (_Simulated) {
         return true;
      }
      NextRequestId();
      FUNCBLOCK func = {0};
      func.info = _IscosNo & 0x0f;
      func.function = SAVREG | 0x80;
      func.param[0] = 0;
      func.param[1] = 0;
      memswap(&func, &func, _FuncBlockSize / 2);
      unsigned char temp_buf[0x500];;
      while (true) {
         _SafeCommunication = true;
         FlushInput();
         int nwrite = WriteBlock((BUF_T)&func, _FuncBlockSize);
         if (nwrite >= 0) {
            _SafeCommunication = false;
            int readCount = 20;
            while (readCount--) {
               _Cell->Context()->UpdateUi();
               int block_len = ReadBlock(temp_buf, sizeof(temp_buf), 500);
               if (block_len >= 0) {
                  unsigned char block[10] = {0};
                  for (int i=0; i<10; i++) {
                     block[i] = temp_buf[i];
                  }
                  if (block_len == 4 + REQUEST_ID_SIZE) {
                     REQUEST_ID_TYPE c1 = *(REQUEST_ID_TYPE*)&(temp_buf[block_len - REQUEST_ID_SIZE]);
                     REQUEST_ID_TYPE c2 = c1;
                     memswap(&c2, &c1, 1);
                     REQUEST_ID_TYPE id = _MasterRequestId;
                     if (c2 == id) {
                        _SwapRequestId = true;
                     }
                     _SafeCommunication = true;
                     InfoPrintf("detected slave with safe communication: enabled safecommunication\n");
                     if (_SwapRequestId) {
                        InfoPrintf("enabled swapping of request id\n");
                     } else {
                        InfoPrintf("request id will not be swapped\n");
                     }
                     return true;
                  } else {
                     _SafeCommunication = false;
                     _FuncBlockSize = 6;
                     InfoPrintf("no slave with safe communication detected: disabled safecommunication\n");
                     return true;
                  }
               }
            }
            return false;
         } else {
            return false;
         }
      }
#else
      ULONG_T BlockTimeoutDefault = _BlockTimeout;
      ULONG_T BlockRetriesDefault = _BlockRetries;
      try {
         _BlockTimeout = strtoul(value, NULL, 0);
         _BlockRetries = 1;
         USHORT_T reg_value = 0;
         Read("register", 0, 2, &reg_value, sizeof(reg_value), VF_DEVICE);
         rc = true;
      } catch (cError & e) {
         if (_DebugLevel) ErrorPrintf("error %s while PPCCOM connection test\n", (const char*)e);
      } catch (...) {
         if (_DebugLevel) ErrorPrintf("unhandled exception while PPCCOM connection test\n");
      }
      _BlockTimeout = BlockTimeoutDefault;
      _BlockRetries = BlockRetriesDefault;
#endif
      return rc;
   } else {
      return SET_BASE_PARAM(cStaticObject, name, value);
   }
}

void cPPCDevice::Start ()
{
  //## begin cPPCDevice::Start%1070963654.body preserve=yes
   if (!_Simulated && _SerialChannel == NULL && _InterfaceMode) {
      /// in case of _InterfaceMode client interface must be reconfigured
      if (_CSComm != NULL && _Client != NULL) {
         _Client->Stop();
         DELETE_OBJECT(cPPCClient, _Client);
         DELETE_OBJECT(cCSComm, _CSComm);
      }
      _CSComm = new cUDPComm((USHORT_T)_ReadPort, (USHORT_T)_WritePort, NULL);
      _Client = new cPPCClient(_CSComm, this);
      _Client->Start();
   }
   if (_RegisterCache != NULL) _RegisterCache->Done();
   if (_LogicCache != NULL) _LogicCache->Done();
   if (_InterfaceMode) {
      cPPCSlave * slave = new cPPCSlave(this);
      slave->Start();
   } else {
      _CacheControl = new cCacheControl(this);
      _CacheControl->SetCache(_RegisterCache);
      _CacheControl->SetCache(_LogicCache);
      _CacheControl->Start();
      _CacheControlId = _CacheControl->get_ThreadId();
   }
   _Active = true;
  //## end cPPCDevice::Start%1070963654.body
}

void cPPCDevice::Stop ()
{
  //## begin cPPCDevice::Stop%1070963655.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
   }
   _Active = false;
  //## end cPPCDevice::Stop%1070963655.body
}

void cPPCDevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cPPCDevice::Cache%1070880000.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Cache(address, size, refresh_type, refresh_value);
   } else {
      if (strcmp(buf_spec, "bit") == 0) {
         ULONG_T log_word_address = address / 0x10;
         cache = SelectCache("logic");
         if (cache != NULL) {
            cache->Cache(log_word_address, 2, refresh_type, refresh_value);
         }
      }
   }
  //## end cPPCDevice::Cache%1070880000.body
}

void cPPCDevice::Buffer (MAP_ITEM_T * map_item)
{
   cCache * cache = SelectCache(map_item->buf_spec);
   if (cache != NULL) {
      cache->Buffer(map_item);
   } else {
      if (strcmp(map_item->buf_spec, "bit") == 0) {
         ULONG_T log_word_address = map_item->address / 0x10;
         cache = SelectCache("logic");
         if (cache != NULL) {
            cache->Buffer(log_word_address, 2);
         }
      }
   }
}

void cPPCDevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
  //## begin cPPCDevice::Buffer%1070880001.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Buffer(address, elements);
   } else {
      if (strcmp(buf_spec, "bit") == 0) {
         ULONG_T log_word_address = address / 0x10;
         cache = SelectCache("logic");
         if (cache != NULL) {
            cache->Buffer(log_word_address, 2);
         }
      }
   }
  //## end cPPCDevice::Buffer%1070880001.body
}

void cPPCDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cPPCDevice::Read%1070550134.body preserve=yes
   if (len == 0) return;
   if (strcmp(buf_spec, "bit") == 0) {
      ReadBit(address, len, buf, buf_size, flags);
      return;
   }
   USHORT_T reg_count = (USHORT_T)len / 2;
// PR 01.07.05
// interface access must be handled correctly
   if (_InterfaceMode) {
      if (_Simulated) {
         _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
      } else {
         cCache * cache = SelectCache(buf_spec);
         if (cache != NULL) {
            cache->Read(address, reg_count, buf, buf_size);
         }
      }
      return;
   }
   if (flags & VF_DEVICE) {
      /// force reading from device
   } else {
      if (_Simulated) {
         _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
         return;
      } else {
         cCache * cache = SelectCache(buf_spec);
         if (cache != NULL) {
#ifdef OLD_BITSET_VERSION
            if (cache->Cached(address, reg_count) ||
               cache->Buffered(address, reg_count)) {
               cache->Read(address, reg_count, buf, buf_size);
               return;
            } else {
               /// this address is not cached so read from device
            }
#else
            BOOL_T cached = cache->Cached(address, reg_count);
            if (cached || _Buffered || (_Cached && cached) ||
                (flags & VF_BUFFERED)) { // address buffered or cached, dont read from device
               cache->Read(address, reg_count, buf, buf_size);
               return;
            } else {
               /// this address is not cached
               /// the device is actually neither bufferd nor cached
               /// so read from device
            }
#endif
         } else {
            /// this buffer is not cached so read from device
         }
      }
   }
   if (_Simulated) {
      _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
   } else {
      if (!_Connected) {
         ULONG_T thread_id = cSystemUtils::ThreadId();
         if ((thread_id != _CacheControlId) && !(flags & VF_DEVICE)) {
            cSystemUtils::Suspend(10);
            throw cError(DEVICE_NOT_CONNECTED, 0, _Name.c_str());
         }
      }
      cObjectLock __lock__(&_DeviceMutex);
      UCHAR_T command = Command(buf_spec, true);
      INT_T err = I60Save (_IscosNo, command, buf, buf_size,(USHORT_T)address, (USHORT_T)reg_count, _BlockTimeout);
      if (err != 0) {
         if (err == PPC_TIMEOUT) {
            if (_ErrCount >= DISCONNECT_ERR_COUNT) {
               _Connected = false;
               cAlarm * alarm = new cAlarm(this, 0x00000001, true, NOT_CONNECTED);
               alarm->set_Param1(_Name);
               alarm->set_Severity(SevError);
               RaiseEvent(alarm);
               alarm->Release();
            } else {
               _ErrCount++;
            }
         }
         throw cError(I60_READ, err,
                      cConvUtils::StringValue(_IscosNo).c_str(),
                      cConvUtils::StringValue(command).c_str(),
                      cConvUtils::StringValue(address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }

      if (!_Connected) { // delete alarm "No connection" only after disconnection
         _Connected = true;
         _ErrCount = 0;
         cAlarm * alarm = new cAlarm(this, 0x00000001, false, NOT_CONNECTED);
         alarm->set_Param1(_Name);
         alarm->set_Severity(SevError);
         RaiseEvent(alarm);
         alarm->Release();
      }
   }
  //## end cPPCDevice::Read%1070550134.body
}

void cPPCDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cPPCDevice::Write%1070550135.body preserve=yes
   if (len == 0) return;
   if (strcmp(buf_spec, "bit") == 0) {
      WriteBit(address, len, buf, flags);
      return;
   }
   USHORT_T reg_count = (USHORT_T)len / 2;
// PR 07.12.04
// always update cache if possible
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Write(address, reg_count, buf);
   }
   if (_InterfaceMode) {
      /// handle interface mode
      if (_Simulated) {
         _Simulation->Write(buf_spec, address, len, buf, flags);
      }
      return;
   }
   if (flags & VF_DEVICE) {
      /// force writing to device
   } else {
      if (_Simulated) {
         _Simulation->Write(buf_spec, address, len, buf, flags);
         return;
      } else {
         if (cache != NULL) {
            if (cache->Buffered(address, reg_count)) {
               if (flags & VF_BUFFERED ||
                   _Buffered) {
                  /// address buffered, dont write to device
                  return;
               } else {
                  /// write to device
                  int dummy = 0;
               }
            } else {
               /// address not buffered so write to device
               int dummy = 0;
            }
         } else {
            /// this buffer is not buffered ! so write to device
            int dummy = 0;
         }
      }
   }
   if (_Simulated) {
      _Simulation->Write(buf_spec, address, len, buf, flags);
   } else {
      if (!_Connected) {
         ULONG_T thread_id = cSystemUtils::ThreadId();
         if ((thread_id != _CacheControlId) && !(flags & VF_DEVICE)) {
            cSystemUtils::Suspend(10);
            throw cError(DEVICE_NOT_CONNECTED, 0, _Name.c_str());
         }
      }
      cObjectLock __lock__(&_DeviceMutex);
      USHORT_T reg_count = (USHORT_T)len / 2;
      UCHAR_T command = Command(buf_spec, false);
      INT_T err = I60Load (_IscosNo, command, buf, len, (USHORT_T)address, reg_count, _BlockTimeout);
      if (err != 0) {
         if (err == PPC_TIMEOUT) {
            if (_ErrCount >= DISCONNECT_ERR_COUNT) {
               _Connected = false;
               cAlarm * alarm = new cAlarm(this, 0x00000001, true, NOT_CONNECTED);
               alarm->set_Param1(_Name);
               alarm->set_Severity(SevError);
               RaiseEvent(alarm);
               alarm->Release();
            } else {
               _ErrCount++;
            }
         }
         throw cError(I60_WRITE, err,
                      cConvUtils::StringValue(_IscosNo).c_str(),
                      cConvUtils::StringValue(command).c_str(),
                      cConvUtils::StringValue(address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
      if (_Verify) {
         if (_VerifyBuf == NULL) {
            _VerifyBuf = (USHORT_T*)cSystemUtils::Alloc(_VerifyBufSize);
         }
         UCHAR_T command = Command(buf_spec, true);
         INT_T err = I60Save (_IscosNo, command, _VerifyBuf, _VerifyBufSize, (USHORT_T)address, (USHORT_T)reg_count, _BlockTimeout);
         if (err == 0) {
            if (memcmp(buf, _VerifyBuf, reg_count * sizeof(USHORT_T)) != 0) {
               USHORT_T * sb = (USHORT_T*)buf;
               USHORT_T * cb = _VerifyBuf;
               for (int i=0; i<reg_count; i++) {
                  USHORT_T sv = *sb;
                  USHORT_T cv = *cb;
                  if (sv != cv) {
                     InfoPrintf("failed to verify ppccom write at %04.4x: set %d, verified %d\n", address + i, sv, cv);
                  }
                  sb++;
                  cb++;
               }
#ifdef NOT_YET
               throw cError(I60_READ, VERIFY_FAILED,
                            cConvUtils::StringValue(_IscosNo).c_str(),
                            cConvUtils::StringValue(command).c_str(),
                            cConvUtils::StringValue(address).c_str(),
                            cConvUtils::StringValue(len).c_str());
#endif
            }
         }
      }

      if (!_Connected) { // delete alarm "No connection" only after disconnection 
         _Connected = true;
         _ErrCount = 0;
         cAlarm * alarm = new cAlarm(this, 0x00000001, false, NOT_CONNECTED);
         alarm->set_Param1(_Name);
         alarm->set_Severity(SevError);
         RaiseEvent(alarm);
         alarm->Release();
      }
   }  
  //## end cPPCDevice::Write%1070550135.body
}

void cPPCDevice::Process ()
{
  //## begin cPPCDevice::Process%1084381602.body preserve=yes
#define CHECK_ADDR(addr,regs,elements) ((ULONG_T)(addr + regs) < (ULONG_T)elements)
#undef RB_SIMULATION
#ifdef RB_SIMULATION
   USHORT_T * reg_buf = 0;
   ULONG_T register_count = 0;
   USHORT_T * log_buf = 0;
   ULONG_T logword_count = 0;
#else
   USHORT_T * reg_buf = (USHORT_T*)((cBlockCache*)_RegisterCache)->get_Memory();
   ULONG_T register_count = ((cBlockCache*)_RegisterCache)->get_Elements();
   USHORT_T * log_buf = (USHORT_T*)((cBlockCache*)_LogicCache)->get_Memory();
   ULONG_T logword_count = ((cBlockCache*)_LogicCache)->get_Elements();
   if (reg_buf == NULL) {
      ErrorPrintf("ppccom slave communication error: no register buffer processing aborted\n");
      return;
   }
   if (log_buf == NULL) {
      ErrorPrintf("ppccom slave communication error: no register buffer processing aborted\n");
      return;
   }
#endif
   char data_block[MAX_BLOCK_LEN + REQUEST_ID_SIZE] = {0};
   char read_buffer[(MAX_BLOCK_LEN + REQUEST_ID_SIZE) * 2] = {0};
   unsigned short address, first_reg;
   unsigned short val, bit_index;
   long nread = 0;
   FUNCBLOCK func = {0};
   unsigned char okay_ready_block[2 + REQUEST_ID_SIZE];
   int regs = 0;
   int channel = 1;
   int timeout = 5000;
   BOOL_T verbose = false;

#ifdef RB_SIMULATION
static int initial = 1;
static BOOL_T active = false;
static char cmp_buffer[(MAX_BLOCK_LEN + REQUEST_ID_SIZE) * 2] = {0};
static USHORT_T _Regs[0x10000] = {0};
static USHORT_T _Logs[0x10000] = {0};
#endif

   try {
      nread = I60Com((UCHAR_T)_IscosNo,
                     NULL, 0,
                     read_buffer, sizeof(read_buffer),
                     timeout);
      if (nread <= 0) return;
#ifdef RB_SIMULATION
      if (!active) {
         initial--;
         if (initial > 0) {
            return;
         }
         if (memcmp(cmp_buffer, read_buffer, sizeof(read_buffer)) == 0) {
            active = true;
            Beep(100, 100);
            reg_buf = (USHORT_T*)((cBlockCache*)_RegisterCache)->get_Memory();
            register_count = ((cBlockCache*)_RegisterCache)->get_Elements();
            log_buf = (USHORT_T*)((cBlockCache*)_LogicCache)->get_Memory();
            logword_count = ((cBlockCache*)_LogicCache)->get_Elements();
         } else {
            USHORT_T * reg_buf = _Regs;
            ULONG_T register_count = sizeof(_Regs) / sizeof(USHORT_T);
            USHORT_T * log_buf = _Logs;
            ULONG_T logword_count = sizeof(_Logs) / sizeof(USHORT_T);
            memcpy(cmp_buffer, read_buffer, sizeof(read_buffer));
            return;
         }
      } else {
         reg_buf = (USHORT_T*)((cBlockCache*)_RegisterCache)->get_Memory();
         register_count = ((cBlockCache*)_RegisterCache)->get_Elements();
         log_buf = (USHORT_T*)((cBlockCache*)_LogicCache)->get_Memory();
         logword_count = ((cBlockCache*)_LogicCache)->get_Elements();
      }
#endif
      memcpy(&func, read_buffer, _FuncBlockSize);
      memswap(&func, &func, 1);
      if (ISCOS_NO(func.info) != (UCHAR_T)_IscosNo) return;
      switch ((int)func.function) {
      case SAVREG:
         if (nread > 4) {
            memswap(&func.param, &func.param, 2);
            first_reg = address = func.param[0];
            regs = func.param[1] - func.param[0] + 1;
         } else {
            memswap(&func.param, &func.param, 1);
            first_reg = address = func.param[0];
            regs = 1;
         }
         if (regs <= 0) {
            SendErrorBlock(ILLEGAL_SAVREG_PARAMETER, timeout);
            break;
         }
         if (!CHECK_ADDR(address,regs,register_count)) {
            SendErrorBlock(REG_NO_OUT_OF_RANGE, timeout);
            break;
         }
         okay_ready_block[0] = OKAY_READY_BLOCK;
         okay_ready_block[1] = 0;
         while (okay_ready_block[0] == OKAY_READY_BLOCK &&
                regs > DATA_SIZE / 2) {
            data_block[0] = DATA_BLOCK;
            data_block[1] = 0;
            memswap(&(data_block[2]), &(reg_buf[address]), DATA_SIZE/2);
            SET_SPS_STATE(_SpsState, data_block);
            nread = I60Com((UCHAR_T)_IscosNo,
                           data_block, _BlockLength, 
                           read_buffer, sizeof(read_buffer),
                           timeout);
            if (nread <= 0) {
               ErrorPrintf("ppccom slave communication error: %d\n", nread);
               break;
            }
            memcpy(okay_ready_block, read_buffer, sizeof(okay_ready_block));
            address = address + (DATA_SIZE / 2);
            regs = regs - (DATA_SIZE / 2);
         }
         if (okay_ready_block[0] != OKAY_READY_BLOCK) {
            SendErrorBlock(BLOCK_PROTOCOL_ERROR, timeout);
            break;
         }
         data_block[0] = LAST_DATA_BLOCK;
         data_block[1] = 0;
         memswap(&(data_block[2]), &(reg_buf[address]), regs);
         SET_SPS_STATE(_SpsState, data_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        data_block, (regs * 2) + 2,
                        NULL, 0,
                        timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
         }
         break;
      case LODREG:
         if (nread > 4) {
            memswap(&func.param, &func.param, 2);
            first_reg = address = func.param[0];
            regs = func.param[1] - func.param[0] + 1;
         } else {
            memswap(&func.param, &func.param, 1);
            first_reg = address = func.param[0];
            regs = 1;
         }
         if (regs <= 0) {
            SendErrorBlock(ILLEGAL_LODREG_PARAMETER, timeout);
            break;
         }
         if (!CHECK_ADDR(address,regs,register_count)) {
            SendErrorBlock(REG_NO_OUT_OF_RANGE, timeout);
            break;
         }
         okay_ready_block[0] = OKAY_READY_BLOCK;
         okay_ready_block[1] = 0;
         data_block[0] = DATA_BLOCK;
         while (data_block[0] != LAST_DATA_BLOCK) {
            SET_SPS_STATE(_SpsState, okay_ready_block);
            nread = I60Com((UCHAR_T)_IscosNo,
                           okay_ready_block, sizeof(OKAY_READY_BLOCK)-REQUEST_ID_SIZE,
                           data_block, sizeof(data_block),
                           timeout);
            if (nread <= 0) {
               ErrorPrintf("ppccom slave communication error: %d\n", nread);
               break;
            }
            if (data_block[0] == DATA_BLOCK ||
                data_block[0] == LAST_DATA_BLOCK) {
               memswap(&(reg_buf[address]), &data_block[2], (nread - 2) / 2);
               address = address + ((nread-2)/2);
            } else {
               break;
            }
         }
         SET_SPS_STATE(_SpsState, okay_ready_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        okay_ready_block, sizeof(okay_ready_block)-REQUEST_ID_SIZE,
                        NULL, 0, timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
            break;
         }
         BitmapSet(_RegBitmap, first_reg, regs, ADDR_WRITTEN);
         break;
      case SAVLOG:
         if (nread > 4) {
            memswap(&func.param, &func.param, 2);
            first_reg = address = func.param[0];
            regs = func.param[1] - func.param[0] + 1;
         } else {
            memswap(&func.param, &func.param, 1);
            first_reg = address = func.param[0];
            regs = 1;
         }
         if (regs <= 0) {
            SendErrorBlock(ILLEGAL_SAVLOG_PARAMETER, timeout);
            break;
         }
         if (!CHECK_ADDR(address,regs,logword_count)) {
            SendErrorBlock(ILLEGAL_BIT_ADDRESS, timeout);
            break;
         }
         okay_ready_block[0] = OKAY_READY_BLOCK;
         okay_ready_block[1] = 0;
         while (okay_ready_block[0] == OKAY_READY_BLOCK &&
                regs > DATA_SIZE / 2) {
            data_block[0] = DATA_BLOCK;
            data_block[1] = 0;
            memswap(&(data_block[2]), &(log_buf[address]), DATA_SIZE / 2);
            SET_SPS_STATE(_SpsState, data_block);
            nread = I60Com((UCHAR_T)_IscosNo,
                           data_block, _BlockLength,
                           read_buffer, sizeof(read_buffer), timeout);
            if (nread <= 0) {
               ErrorPrintf("ppccom slave communication error: %d\n", nread);
               break;
            }
            memcpy(okay_ready_block, read_buffer, sizeof(okay_ready_block));
            address = address + (DATA_SIZE / 2);
            regs = regs - (DATA_SIZE / 2);
         }
         if (okay_ready_block[0] != OKAY_READY_BLOCK) {
            SendErrorBlock(BLOCK_PROTOCOL_ERROR, timeout);
            break;
         }
         data_block[0] = LAST_DATA_BLOCK;
         data_block[1] = 0;
         memswap(&(data_block[2]), &(log_buf[address]), regs);
         SET_SPS_STATE(_SpsState, data_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        data_block, (regs * 2) + 2,
                        NULL, 0,
                        timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
         }
         break;
      case LODLOG:
         if (nread > 4) {
            memswap(&func.param, &func.param, 2);
            first_reg = address = func.param[0];
            regs = func.param[1] - func.param[0] + 1;
         } else {
            memswap(&func.param, &func.param, 1);
            first_reg = address = func.param[0];
            regs = 1;
         }
         if (regs <= 0) {
            SendErrorBlock(ILLEGAL_LODLOG_PARAMETER, timeout);
            break;
         }
         if (!CHECK_ADDR(address,regs,logword_count)) {
            SendErrorBlock(ILLEGAL_BIT_ADDRESS, timeout);
            break;
         }
         okay_ready_block[0] = OKAY_READY_BLOCK;
         okay_ready_block[1] = 0;
         data_block[0] = DATA_BLOCK;
         while (data_block[0] != LAST_DATA_BLOCK) {
            SET_SPS_STATE(_SpsState, okay_ready_block);
            nread = I60Com((UCHAR_T)_IscosNo,
                           okay_ready_block, sizeof(okay_ready_block)-REQUEST_ID_SIZE,
                           data_block, sizeof(data_block), 
                           timeout);
            if (nread <= 0) {
               ErrorPrintf("ppccom slave communication error: %d\n", nread);
               break;
            }
            if (data_block[0] == DATA_BLOCK ||
                data_block[0] == LAST_DATA_BLOCK) {
               memswap(&(log_buf[address]), &data_block[2], (nread - 2) / 2);
               address = address + ((nread-2)/2);
            } else {
               break;
            }
         }
         SET_SPS_STATE(_SpsState, okay_ready_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        okay_ready_block, sizeof(okay_ready_block)-REQUEST_ID_SIZE,
                        NULL, 0,
                        timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
            break;
         }
         BitmapSet(_LogBitmap, first_reg, regs, ADDR_WRITTEN);
         break;
      case BITSET:
         memswap(&func.param, &func.param, 2);
         if (!CHECK_ADDR(func.param[1] % 0x10,1,logword_count)) {
            SendErrorBlock(ILLEGAL_BIT_ADDRESS, timeout);
            break;
         }
         address = func.param[1] / 0x10;
         bit_index = func.param[1] % 0x10;
         val = *(USHORT_T*)&(log_buf[address]);
         if (func.param[0] == 0x5420) {
            val = val | (0x8000 >> bit_index);
         } else if (func.param[0] == 0x4620) {
            val = val & ~(0x8000 >> bit_index);
         } else {
            SendErrorBlock(ILLEGAL_BITSET_PARAMETER, timeout);
            break;
         }
         *(USHORT_T*)&(log_buf[address]) = val;
         okay_ready_block[0] = OKAY_READY_BLOCK;
         okay_ready_block[1] = 0;
         SET_SPS_STATE(_SpsState, okay_ready_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        okay_ready_block, sizeof(okay_ready_block)-REQUEST_ID_SIZE,
                        NULL, 0,
                        timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
            break;
         }
         BitmapSet(_LogBitmap, address, 1, ADDR_WRITTEN);
         break;
      case ICMD_GI:
         data_block[0] = LAST_DATA_BLOCK;
         data_block[1] = 0;
         memswap(&(data_block[2]), &_SpsVersion, 1);
         SET_SPS_STATE(_SpsState, data_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        data_block, 4,
                        NULL, 0, timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
         }
         break;
      case ICMD_GM:
         data_block[0] = NO_DATA_BLOCK;
         data_block[1] = 0;
         SET_SPS_STATE(_SpsState, data_block);
         nread = I60Com((UCHAR_T)_IscosNo,
                        data_block, 2,
                        NULL, 0, timeout);
         if (nread < 0) {
            ErrorPrintf("ppccom slave communication error: %d\n", nread);
         }
         break;
      case ICMD_SS:
         memswap(&func.param, &func.param, 2);
         if ((func.param[0]) > 3) {
            SendErrorBlock(NO_SS0_1_2_3, timeout);
         } else {
            switch (func.param[0]) {
            case 0:
               break;
            case 1:
               _SpsState &= ~PROGRAM_RUNNING;
               break;
            case 2:
               _SpsState |= PROGRAM_RUNNING;
               break;
            case 3:
               break;
            }
            okay_ready_block[0] = OKAY_READY_BLOCK;
            okay_ready_block[1] = 0;
            SET_SPS_STATE(_SpsState, okay_ready_block);
            nread = I60Com((UCHAR_T)_IscosNo,
                           okay_ready_block, sizeof(okay_ready_block)-REQUEST_ID_SIZE,
                           NULL, 0, timeout);
            if (nread < 0) {
               ErrorPrintf("ppccom slave communication error: %d\n", nread);
               break;
            }
         }
         break;
      default:
//       SendErrorBlock(FUNCTION_NOT_AVAILABLE, timeout);
         break;
      }
   } catch (cError & e) {
      printf("error %s in sps slave control\n", (const char *)e);
      cSystemUtils::Suspend(10);
   } catch (...) {
      printf("unhandled exception in sps slave control\n");
      cSystemUtils::Suspend(10);
   }
  //## end cPPCDevice::Process%1084381602.body
}

INT_T cPPCDevice::I60Load (UCHAR_T iscos_no, UCHAR_T order, void *outbuf, ULONG_T outbuf_len, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Load%1070550136.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   ULONG_T t0 = 0, t1 = 0;
   if (_TimingProtocol) {
      t0 = cSystemUtils::RealtimeOffset();
   }
   int retries = CMD_RETRIES;
   int err = -1;
   while (retries >= 0 && err != 0) { 
      unsigned char temp_buffer[TRANSFER_BUF_SIZE];
      char * outbuf_ptr = (char *)outbuf;
      FUNCBLOCK func = {0};
#ifndef UNSAFE_VERSION
      if (_SafeCommunication) {
         NextRequestId();
      }
#endif
      unsigned short _noof_regs = noof_regs;
      unsigned short _regs_to_write = 0;
      unsigned short _reg_addr = reg_addr;
      if (_noof_regs > REG_BUF_SIZE) {
         _regs_to_write = _noof_regs - REG_BUF_SIZE;
         _noof_regs = REG_BUF_SIZE;
      }
      while (_noof_regs > 0) {
           func.info = iscos_no & 0x0f;
           func.function = order | 0x80;
           func.param[0] = _reg_addr;
           func.param[1] = _reg_addr + _noof_regs - 1;
           memswap(&func, &func, 3);
           memswap(temp_buffer, outbuf_ptr, _noof_regs);
         FlushInput();
         err = SupplyData(iscos_no,
                          (void *)&func, _FuncBlockSize, (void *)temp_buffer, _noof_regs * 2,
                          timeout);
         retries--;
         if (err == 0) {
            _noof_regs = _regs_to_write;
            if (_noof_regs > REG_BUF_SIZE) {
               _regs_to_write = _noof_regs - REG_BUF_SIZE;
               _noof_regs = REG_BUF_SIZE;
               _reg_addr += REG_BUF_SIZE;
               outbuf_ptr += (REG_BUF_SIZE*2);
            } else if (_noof_regs > 0) {
               _regs_to_write = 0;
               _reg_addr += REG_BUF_SIZE;
               outbuf_ptr += (REG_BUF_SIZE*2);
            } else {
               _regs_to_write = 0;
            }
         } else {
            if (retries < 0) {
               if (_TimingProtocol) {
                  t1 = cSystemUtils::RealtimeOffset();
                  TimePrintf("I60Load(%d,%d,%04.04x,%d): %d msecs , Error %d\n",
                             (int)iscos_no,
                             (int)order,
                             (int)reg_addr,
                             (int)noof_regs,
                             t1 - t0,
                             err);
               }
               return err;
            }
         }
      }
   }
   if (_TimingProtocol) {
      t1 = cSystemUtils::RealtimeOffset();
      TimePrintf("I60Load(%d,%d,%04.04x,%d): %d msecs , Error %d\n",
                 (int)iscos_no,
                 (int)order,
                 (int)reg_addr,
                 (int)noof_regs,
                 t1 - t0,
                 err);
   }
   return err;
  //## end cPPCDevice::I60Load%1070550136.body
}

INT_T cPPCDevice::I60Save (UCHAR_T iscos_no, UCHAR_T order, void *inbuf, ULONG_T inbuf_size, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Save%1070550137.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   ULONG_T t0 = 0, t1 = 0;
   if (_TimingProtocol) {
      t0 = cSystemUtils::RealtimeOffset();
   }
   int retries = CMD_RETRIES;
   int err = -1;
   while (retries-- && (err != 0)) { 
      unsigned char temp_buffer[TRANSFER_BUF_SIZE];
      char * inbuf_ptr = (char *)inbuf;
      FUNCBLOCK func = {0};
#ifndef UNSAFE_VERSION
      if (_SafeCommunication) {
         NextRequestId();
      }
#endif
      unsigned long _bytes_read = 0;
      unsigned short _noof_regs = noof_regs;
      unsigned short _regs_to_read = 0;
      unsigned short _reg_addr = reg_addr;
      if (_noof_regs > REG_BUF_SIZE) {
         _regs_to_read = _noof_regs - REG_BUF_SIZE;
         _noof_regs = REG_BUF_SIZE;
      }
      while (_noof_regs > 0) {
         func.info = iscos_no & 0x0f;
         func.function = order | 0x80;
         func.param[0] = _reg_addr;
         func.param[1] = _reg_addr + _noof_regs - 1;
         memswap(&func, &func, _FuncBlockSize / 2);
         unsigned long response_len = _noof_regs * 2;
         FlushInput();
         err = RequestData(iscos_no,
                           (void *)&func, _FuncBlockSize, temp_buffer, sizeof(temp_buffer),
                           timeout);
         if (err == 0) {
            _bytes_read += response_len;
            if (_bytes_read > inbuf_size) {
               return I60_BUF_TOO_SMALL;
            } else {
               memswap(inbuf_ptr, temp_buffer, (response_len+1)/2);
               inbuf_ptr += response_len;
               _noof_regs = _regs_to_read;
               if (_noof_regs > REG_BUF_SIZE) {
                  _regs_to_read = _noof_regs - REG_BUF_SIZE;
                  _noof_regs = REG_BUF_SIZE;
                  _reg_addr += REG_BUF_SIZE;
               } else if (_noof_regs > 0) {
                  _regs_to_read = 0;
                  _reg_addr += REG_BUF_SIZE;
               } else {
                  _regs_to_read = 0;
               }
            }
         } else {
            if (retries <= 0) {
               if (_TimingProtocol) {
                  t1 = cSystemUtils::RealtimeOffset();
                  TimePrintf("I60Save(%d,%d,%04.04x,%d): %d msecs , Error %d\n",
                             (int)iscos_no,
                             (int)order,
                             (int)reg_addr,
                             (int)noof_regs,
                             t1 - t0,
                             err);
               }
               return err;
            }
         }
      }
   }

   if (_TimingProtocol) {
      t1 = cSystemUtils::RealtimeOffset();
      TimePrintf("I60Save(%d,%d,%04.04x,%d): %d msecs , Error %d\n",
                 (int)iscos_no,
                 (int)order,
                 (int)reg_addr,
                 (int)noof_regs,
                 t1 - t0,
                 err);
   }
   return err;
  //## end cPPCDevice::I60Save%1070550137.body
}

INT_T cPPCDevice::I60Bit (UCHAR_T iscos_no, USHORT_T bit_no, UCHAR_T function, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Bit%1070550138.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   ULONG_T t0 = 0, t1 = 0;
   if (_TimingProtocol) {
      t0 = cSystemUtils::RealtimeOffset();
   }
   int retries = CMD_RETRIES;
   int err = -1;
   while (retries >= 0 && err != 0) { 
      FUNCBLOCK func = {0};
#ifndef UNSAFE_VERSION
      if (_SafeCommunication) {
         NextRequestId();
      }
#endif
      func.info = iscos_no & 0x0f;
      func.function = BITSET | 0x80;
      if (function == 'T') {
         func.param[0] = 0x5420;
      } else if (function == 'F') {
         func.param[0] = 0x4620;
      } else {
         return I60_ILLEGAL_FUNCTION;
      }
      func.param[1] = bit_no;
      memswap(&func, &func, _FuncBlockSize / 2);
      FlushInput();
      err = RequestData(iscos_no, (void *)&func, _FuncBlockSize, NULL, 0, timeout);
      retries--;
   }
   if (_TimingProtocol) {
      t1 = cSystemUtils::RealtimeOffset();
      TimePrintf("I60Bit(%d,%04.04x): %d msecs , Error %d\n",
                 (int)iscos_no,
                 (int)bit_no,
                 t1 - t0,
                 err);
   }
   return err;
  //## end cPPCDevice::I60Bit%1070550138.body
}

LONG_T cPPCDevice::I60Com (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Com%1070550139.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   long nread = PpcCom(iscos_no, outbuf, outbuf_len, inbuf, inbuf_size, timeout);
   if (nread < 0) {
      return nread;
   } else {	
      if (inbuf != NULL) {
         int err_code = PpcError((unsigned char *)inbuf, nread);
         if (err_code != 0) {
            /*	Retries auf Treiberebene wie bei den supply-
             *	und request-Funktionen werden hier nicht unterstuetzt
             *
             */
            return -err_code;
         } else {
            return nread;
         }
      } else {
         return nread;
      }
   }
  //## end cPPCDevice::I60Com%1070550139.body
}

LONG_T cPPCDevice::I60Request (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Request%1070550140.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "I60Request", "cPPCDevice");
  //## end cPPCDevice::I60Request%1070550140.body
}

UCHAR_T cPPCDevice::Command (CONST_STRING_T buf_spec, BOOL_T read)
{
  //## begin cPPCDevice::Command%1075189792.body preserve=yes
   if (_stricmp("register", buf_spec) == 0) {
      return read ? SAVREG : LODREG;
   } else if (_stricmp("logic", buf_spec) == 0) {
      return read ? SAVLOG : LODLOG;
   } else {
      return 0;
   }
  //## end cPPCDevice::Command%1075189792.body
}

LONG_T cPPCDevice::WriteBlock (BUF_T block, ULONG_T block_len)
{
  //## begin cPPCDevice::WriteBlock%1070550141.body preserve=yes
#ifndef UNSAFE_VERSION
   if (_SafeCommunication) {
      *(REQUEST_ID_TYPE*)&(block[block_len]) = _MasterRequestId;
      block_len += REQUEST_ID_SIZE;
   }
#endif

#define ROT_RIGHT(byte)    ((byte>>1) | ((byte&0x01)<<7))
#define LSB(word)          ((unsigned char)(word&0x00ff)) 
#define MSB(word)          ((unsigned char)((word&0xff00)>>8))

#define ST1                0xf1
#define ST2                0x59

   unsigned char * data = block;
   unsigned long data_len = block_len;
   unsigned char out_buffer[(MAX_BLOCK_LEN + REQUEST_ID_SIZE) * 2] = {0};
   unsigned char * out_buf = out_buffer;
   out_buf = (unsigned char *)(&out_buffer);
   BOOL_T stop = false;
   BOOL_T check = false;
   int state = -4;
   unsigned char checksum = 0;
   unsigned long efflength = 0;
   unsigned char out;
   unsigned long out_buf_len = 0;
   while (!stop) {
      out = *data;
      switch (state) {
      case -4:
         out = ST1;
         state = -3;
         break;
      case -3:
         out = ST2;
         state = -2;
         break;
      case -2:
         out = MSB(data_len);
         check = true;
         state = -1;
         break;
      case -1:
         out = LSB(data_len);
         state = 0;
         break;
      case 0:
         efflength++;
         data++;
         if (efflength == data_len) state = 1;
         break;
      case 1:
         out = checksum;
         check = false;
         state = 2;
         break;
      case 2:
         stop = true;
         break;
      }
 
      if (!stop) {
         switch ((int)out) {
         case ST1:
            *out_buf++ = ST1;
            out_buf_len++;
            if (check) { 
               checksum = ROT_RIGHT(checksum) ^ ST1;
            }
            if (state >= 0) {
               *out_buf++ = ST1;
               out_buf_len++;
            }
            break;
         case ST2:
            *out_buf++ = ST2;
            out_buf_len++;
            if (check) { 
               checksum = ROT_RIGHT(checksum) ^ ST2;
            }
            if (state >= 0) {
               *out_buf++ = ST2;
               out_buf_len++;
            }
            break;
         default:
            *out_buf++ = out;
            out_buf_len++;
            break;
         }
      }
      if (check) {
         checksum = ROT_RIGHT(checksum) ^ out;
      }
   }
   long nwrite = SendBlock(out_buffer, out_buf_len);
   if (nwrite == (long)out_buf_len) {
      BlockDebug(block, block_len, false);
      return efflength;
   } else {
      return nwrite;
   }
  //## end cPPCDevice::WriteBlock%1070550141.body
}

LONG_T cPPCDevice::ReadBlock (BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::ReadBlock%1070550142.body preserve=yes
   if (_SerialChannel == NULL) {
      if (_Client != NULL) {
         LONG_T block_len = _Client->GetMessage(buf, buf_size, timeout, _IscosNo);
         if (block_len > 0) {
            BlockDebug(buf, block_len, true);
#ifndef UNSAFE_VERSION
            if (_SafeCommunication) {
               block_len -= REQUEST_ID_SIZE;
               if (_InterfaceMode) {
                  _MasterRequestId = *(REQUEST_ID_TYPE*)&(buf[block_len]);
               } else {
                  _SlaveRequestId = *(REQUEST_ID_TYPE*)&(buf[block_len]);
                  if (_SwapRequestId) {
                     memswap(&_SlaveRequestId, &_SlaveRequestId, 1);
                  }
                  if (_MasterRequestId != _SlaveRequestId) {
                     ErrorPrintf("ReadBlock sync failed masterRequestId = %d slaveRequestId = %d\n", _MasterRequestId, _SlaveRequestId);
                     cSystemUtils::Suspend(3000);
                     FlushInput();
                     return PPC_SYNC_FAILED;
                  }
               }
            }
#endif
            return block_len;
         } else {
            return PPC_TIMEOUT;
         }
      } else {
         return PPC_DEVICE_NOT_INITIALIZED;
      }
   } else {

#define INTER_CHAR_TIMEOUT    100
#define GET_CHAR(value) \
   { \
      if (buf_index == buf_end) { \
         buf_index = -1; \
      } \
      if (buf_index == -1) { \
         nread = _SerialChannel->Read((UCHAR_T*)temp_buf, sizeof(temp_buf), 1); \
         if (nread > 0) { \
            buf_index = 0; \
            buf_end = nread; \
         } \
      } \
      if (buf_index == -1) { \
         value = _SerialChannel->GetChar(read_timeout); \
      } else { \
         value = temp_buf[buf_index]; \
         buf_index++; \
      } \
   }

      BOOL_T check = false;
      int flag = 0;
      int state = -4;
      unsigned char checksum = 0;
      unsigned long efflength = 0;
      unsigned long length = 0;
      unsigned char * bufptr = (unsigned char *)buf;
      int err = 0;
      int c = 0;
      unsigned char in_data;
      unsigned long read_timeout = timeout;
      BOOL_T rcv = false;
      UCHAR_T temp_buf[MAX_BLOCK_LEN + REQUEST_ID_SIZE] = {0};
      int buf_index = -1;
      int buf_end = 0;
      int nread = 0;
   
      while (true) {

#define OPTIMIZED_VERSION
#ifdef OPTIMIZED_VERSION
         GET_CHAR(c)
#else
         c = _SerialChannel->GetChar(read_timeout);
#endif
         if (c == EOF) {
            return PPC_TIMEOUT;
         }
         read_timeout = INTER_CHAR_TIMEOUT;
         in_data = (unsigned char)c;
         switch (flag) {
         case 0:
            if (in_data == ST1) {
               flag = 1;
            } else {
               if (in_data == ST2) {
                  flag = 2;
               }
            }
            break;
         case 1:
            if (in_data == ST1) {
               flag = 3;
            } else {
               if (in_data == ST2) {
                  state = -1;
                  efflength = 0;
                  checksum = 0;
               } else {
                  state = -4;
               }
            }
         break;
         case 2:
            if (in_data == ST2) {
               flag = 0;
            } else {
               if (in_data == ST1) {
                  state = -3;
               } else {
                  state = -4;
               }
            }
            break;
         case 3:
            if (in_data == ST1) {
               flag = 1;
            } else {
               if (in_data == ST2) {
                  flag = 4;
               } else {
                  flag = 0;
               }
            }
            break;
         case 4:
            if (in_data == ST2) {
               flag = 0;
            } else {
               if (in_data == ST1) {
               state = -3;
               } else {
                  if (in_data > ST2) {
                     state = -4;
                  } else {
                     state = -1;
                     efflength = 0;
                     checksum = 0;
                  }
               }
            }
            break;
         default:
            err = PPC_INVALID_FLAG;
            rcv = true;
         }
         switch (state) {
         case -4:
            check = false;
            flag = 0;
            if (in_data == ST1) {
               state = -3;
            }
            break;
         case -3:
            check = false;
            flag = 0;
            if (in_data == ST2) {
               efflength = 0;
               checksum = 0;
               state = -2;
            } else {
               if (in_data != ST1) {
                  state = -4;
               }
            }
            break;
         case -2:
            flag = 0;
            if (in_data == ST1) {
               state = -3;
            } else {
               if (in_data >= ST2) {
                  state = -4;
               } else {
                  length |= ((WORD)in_data)<<8;
                  check = true;
                  state = -1;
               }
            }
            break;
         case -1:
            if (flag == 0 || flag == 3) {
               length |= (WORD)in_data;
               if (length == 0) {
                  err = PPC_SIZE_ZERO;
                  rcv = true;
               } else if (length > _BlockLength + REQUEST_ID_SIZE) {
                  AdjustBlockLength((USHORT_T)length);
                  err = PPC_SIZE_EXCEEDS_MAX_BLOCK_LEN;
                  rcv = true;
               } else {
                  state = 0;
               }
            }
            break;
         case 0:
            if (flag == 0 || flag == 3) {
               *bufptr = in_data;
               efflength++;
               if (efflength > buf_size) {
                  err = PPC_BUF_TOO_SMALL;
                  rcv = true;
               } else {
                  bufptr++;
                  if (efflength == length) state = 1;
               }
            }
            break;
         case 1:
            check = false;
            if (flag == 0 || flag == 3) {
               if (checksum != in_data) {
                  err = PPC_CHECKSUM_ERROR;
               } else {
                  err = 0;
               }
               rcv = true;
            }
            break;
         default:
            err = PPC_INVALID_STATE;
            rcv = true;
         }
         if (check) {
            checksum = ROT_RIGHT(checksum) ^ in_data;
         }
         if (rcv) {
            if (err == 0) {
               BlockDebug(buf, efflength, true);   
            }
            if (err == 0) {
#ifndef UNSAFE_VERSION
               if (_SafeCommunication) {
                  efflength -= REQUEST_ID_SIZE;
                  if (_InterfaceMode) {
                     _MasterRequestId = *(REQUEST_ID_TYPE*)&(buf[efflength]);
                  } else {
                     _SlaveRequestId = *(REQUEST_ID_TYPE*)&(buf[efflength]);
                     if (_SwapRequestId) {
                        memswap(&_SlaveRequestId, &_SlaveRequestId, 1);
                     }
                     if (_MasterRequestId != _SlaveRequestId) {
                        return PPC_SYNC_FAILED;
                     }
                  }
               }
#endif
               return efflength;
            } else {
               return err;
            }
         }
      }
   }   
  //## end cPPCDevice::ReadBlock%1070550142.body
}

LONG_T cPPCDevice::PpcCom (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::PpcCom%1070550143.body preserve=yes
   long size = 0, err = 0;
   if (outbuf_len > 0) size = WriteBlock((BUF_T)outbuf, outbuf_len);
   if (size >= 0) {
      if (inbuf != NULL) {
			return ReadBlock((BUF_T)inbuf, inbuf_size, timeout);
      } else {
			return 0;
      }
   } else {
		return size;
   }
  //## end cPPCDevice::PpcCom%1070550143.body
}

INT_T cPPCDevice::PpcError (UCHAR_T *block, ULONG_T block_len)
{
  //## begin cPPCDevice::PpcError%1070550144.body preserve=yes
   if (!PPC_ERROR(block)) return 0;
   unsigned char error_block[4] = {0};
   memswap(error_block, block, 2);
   return *(unsigned short*)&error_block[2];
  //## end cPPCDevice::PpcError%1070550144.body
}

INT_T cPPCDevice::SupplyData (UCHAR_T iscos_no, void *func, ULONG_T func_len, void *data, ULONG_T data_len, ULONG_T timeout)
{
  //## begin cPPCDevice::SupplyData%1070550145.body preserve=yes
   unsigned char read_buffer[MAX_BLOCK_LEN + REQUEST_ID_SIZE];
   unsigned char data_block[MAX_BLOCK_LEN + REQUEST_ID_SIZE];
   int func_retries = _BlockRetries;
   long nwrite = 0;
   long nread = 0;
   BOOL_T data_transfer_error = true;
   while (func_retries-- && data_transfer_error) {
      data_transfer_error = false;
      if ((nwrite = WriteBlock((BUF_T)func, func_len)) < 0) {
         return nwrite;
      }
      INIT_BUFFER(read_buffer);
      if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) {
         if (func_retries > 0) {
            data_transfer_error = true;
            continue;
         } else {
            return nread;
         }
      }
      if (PPC_OKAY_READY(read_buffer)) {
         unsigned char * buf_ptr = (unsigned char *)data;
         int len = data_len;
         int data_retries = _BlockRetries + 1;
         while (len && !data_transfer_error) {
            if (len <= DATA_SIZE) {
               SET_INFO_BLOCK(data_block, iscos_no, LAST_DATA_BLOCK);
               memcpy(&(data_block[2]), buf_ptr, len);
               INIT_BUFFER(read_buffer);
               while (data_retries-- && !(PPC_OKAY_READY(read_buffer))) {
                  if ((nwrite = WriteBlock((BUF_T)data_block, len + 2)) < 0) {
                     return nwrite;
                  }
                  INIT_BUFFER(read_buffer);
                  if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) {
                     if (data_retries > 0) {
                        continue;
                     } else {
                        return nread;
                     }
                  }
               }
               if (PPC_OKAY_READY(read_buffer)) {
                  return 0;
               } else {
                  data_transfer_error = true;
               }
            } else {
               SET_INFO_BLOCK(data_block, iscos_no, DATA_BLOCK);
               memcpy(&(data_block[2]), buf_ptr, DATA_SIZE);
               INIT_BUFFER(read_buffer);
               while (data_retries-- && !(PPC_OKAY_READY(read_buffer))) {
                  if ((nwrite = WriteBlock(data_block, DATA_SIZE + 2)) < 0) return nwrite;
                  INIT_BUFFER(read_buffer);
                  if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) {
                     if (data_retries > 0) {
                        continue;
                     } else {
                        return nread;
                     }
                  }
               }
               if (PPC_OKAY_READY(read_buffer)) {
                  buf_ptr += DATA_SIZE;
                  len -= DATA_SIZE;
                  data_retries = _BlockRetries + 1;
               } else {
                  data_transfer_error = true;
                  break;
               }
            }
         }
      } else if (PPC_ERROR(read_buffer)) {
         int err_code = PpcError(read_buffer, nread);
         if (err_code == 10 ||
             err_code == 12 ||
             err_code == 37) {
            data_transfer_error = true;
         } else {
            return -err_code;
         }
      }
   }
   if (_TimingProtocol) {
      TimePrintf("Supply failed %s\n", read_buffer);
   }
   return SUPPLY_FAILED;
  //## end cPPCDevice::SupplyData%1070550145.body
}

INT_T cPPCDevice::RequestData (UCHAR_T iscos_no, void *func, ULONG_T func_len, void *databuf, ULONG_T data_buf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::RequestData%1070550146.body preserve=yes
   unsigned char read_buffer[MAX_BLOCK_LEN + REQUEST_ID_SIZE];
   unsigned char okay_ready_block[2 + REQUEST_ID_SIZE];
   unsigned char error_block[2 + REQUEST_ID_SIZE];
   int func_retries = _BlockRetries;
   int nwrite = 0;
   int nread = 0;
   BOOL_T data_transfer_error = true;
   SET_INFO_BLOCK(okay_ready_block, iscos_no, OKAY_READY_BLOCK);
   SET_INFO_BLOCK(error_block, iscos_no, ERROR_BLOCK);
   while (func_retries-- && data_transfer_error) {
      data_transfer_error = false;
      if ((nwrite = WriteBlock((BUF_T)func, func_len)) < 0) {
         return nwrite;
      }
      INIT_BUFFER(read_buffer);
      if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) {
         if (func_retries > 0) {
            data_transfer_error = true;
            continue;
         } else {
            return nread;
         }
      }
      if (PPC_OKAY_READY(read_buffer)) {
         return 0;
      } else if (PPC_NO_DATA(read_buffer)) {
         return NO_DATA_BLOCK_RECEIVED;
      } else if (PPC_ERROR(read_buffer)) {
         int err_code = PpcError(read_buffer, nread);
         if (err_code == 10 ||
             err_code == 12 ||
             err_code == 37) {
            data_transfer_error = true;
         } else {
            return -err_code;
         }
      } else {
         unsigned char * buf_ptr = (unsigned char *)databuf;
         int len = 0;
         int expected_response_len = ExpectedResponseLength((FUNCBLOCK*)func);
         int data_retries = _BlockRetries + 1;
         while (data_retries-- ||
                PPC_DATA(read_buffer) ||
                PPC_LAST_DATA(read_buffer)) {
            if (nread > 0) {
               if (PPC_LAST_DATA(read_buffer)) {
                  if (expected_response_len != (ULONG_T)nread) {
                     return I60_LENGTH_MISMATCH;
                  }
                  if (len + nread - 2 > data_buf_size) {
                     return I60_BUF_TOO_SMALL;
                  }
                  memcpy(buf_ptr, &read_buffer[2], nread - 2);
                  return 0;
               } else if (PPC_DATA(read_buffer)) {
                  if (len + nread - 2 > data_buf_size) {
                     return I60_BUF_TOO_SMALL;
                  }
                  memcpy(buf_ptr, &read_buffer[2], nread - 2);
                  nwrite = WriteBlock(okay_ready_block, 2);
                  len += (nread - 2);
                  buf_ptr += (nread - 2);
                  data_retries = _BlockRetries + 1;
                  expected_response_len -= (nread - 2);
               }
               INIT_BUFFER(read_buffer);
            }
            if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) {
               if (data_retries > 0) {
                  continue;
               } else {
                  return nread;
               }
            }
         }
      }
   }
   return REQUEST_FAILED;
  //## end cPPCDevice::RequestData%1070550146.body
}

LONG_T cPPCDevice::SendErrorBlock (USHORT_T err_code, ULONG_T timeout)
{
  //## begin cPPCDevice::SendErrorBlock%1070550147.body preserve=yes
   unsigned char error_block[4 + REQUEST_ID_SIZE] = {0};
   error_block[0] = ERROR_BLOCK;
   error_block[1] = 0;
   SET_SPS_STATE(_SpsState, error_block);
   memswap((USHORT_T*)(&(error_block[2])), &err_code, 1);
   return I60Com((UCHAR_T)_IscosNo, error_block, 4, NULL, 0, timeout);
  //## end cPPCDevice::SendErrorBlock%1070550147.body
}

void cPPCDevice::ReadBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cPPCDevice::ReadBit%1086172577.body preserve=yes
   if (len != 1) {
      return;
   }
   cPPCOperator op;
   USHORT_T value = 0;
   ULONG_T log_addr = address / 0x10;
   UCHAR_T bit_pos = (UCHAR_T)(address % 0x10);
   ((cDevice *)this)->Get("logic", log_addr,value, flags);
   op.SetValue(SH_BIT_16, value);
   UCHAR_T bit_val = *(UCHAR_T*)buf = op.GetBit(bit_pos);
   /// PR 23.04.07 update bit in cache if cached or buffered
   cCache * cache = SelectCache("logic");
   if (cache != NULL) {
      USHORT_T cache_value = 0;
      cache->Read(log_addr, 1, &cache_value, sizeof(cache_value));
      op.SetValue(SH_BIT_16, cache_value);
      if (bit_val) {
         op.SetBit(bit_pos);
      } else {
         op.ResetBit(bit_pos);
      }
      cache_value = op;
      cache->Write(log_addr, 1, &cache_value);
   }
  //## end cPPCDevice::ReadBit%1086172577.body
}

void cPPCDevice::WriteBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cPPCDevice::WriteBit%1086172578.body preserve=yes
   cPPCOperator op;
   if (len != 1) {
      return;
   }
   UCHAR_T bit_val = *(UCHAR_T*)buf;
   ULONG_T log_addr = address / 0x10;
   UCHAR_T bit_pos = (UCHAR_T)(address % 0x10);
   if (_InterfaceMode) {
      /// handle inteface mode
      USHORT_T value = 0;
      ((cDevice *)this)->Get("logic", log_addr, value, flags);
      op.SetValue(SH_BIT_16, value);
      if (bit_val == 0) {
         op.ResetBit(bit_pos);
      } else {
         op.SetBit(bit_pos);
      }
      value = op;
      ((cDevice *)this)->Set("logic", log_addr, value, flags);
      return;
   }
   if (_Simulated ||
       (_Buffered && !(flags & VF_DEVICE)) ||
       (flags & VF_BUFFERED)) {
      USHORT_T value = 0;
      ((cDevice *)this)->Get("logic", log_addr, value, flags);
      op.SetValue(SH_BIT_16, value);
      if (bit_val == 0) {
         op.ResetBit(bit_pos);
      } else {
         op.SetBit(bit_pos);
      }
      value = op;
      ((cDevice *)this)->Set("logic", log_addr, value, flags);
   } else {
      if (!_Connected) {
         ULONG_T thread_id = cSystemUtils::ThreadId();
         if ((thread_id != _CacheControlId) && !(flags & VF_DEVICE)) {
            cSystemUtils::Suspend(10);
            throw cError(DEVICE_NOT_CONNECTED, 0, _Name.c_str());
         }
      }
      char bit_op = (bit_val == 0) ? 'F' : 'T';
      INT_T err = I60Bit(_IscosNo, (USHORT_T)address, bit_op, _BlockTimeout);
      if (err != 0) {
         throw cError(I60_WRITE, err,
                      cConvUtils::StringValue(_IscosNo).c_str(),
                      cConvUtils::StringValue(bit_op).c_str(),
                      cConvUtils::StringValue(address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
      cCache * cache = SelectCache("logic");
      if (cache != NULL) {
         USHORT_T value = 0;
         cache->Read(log_addr, 1, &value, sizeof(value));
         op.SetValue(SH_BIT_16, value);
         if (bit_val == 0) {
            op.ResetBit(bit_pos);
         } else {
            op.SetBit(bit_pos);
         }
         value = op;
         cache->Write(log_addr, 1, &value);
      }
   }
  //## end cPPCDevice::WriteBit%1086172578.body
}

LONG_T cPPCDevice::SendBlock (BUF_T buf, ULONG_T len)
{
  //## begin cPPCDevice::SendBlock%1091085016.body preserve=yes
   if (_SerialChannel == NULL) {
      if (_Client != NULL) {
         cCSMsg msg(buf, len);
         msg.SetAppDataSize(len);
         try {
            _Client->Send(&msg);
         } catch (cError & e) {
            if (_DebugLevel) ErrorPrintf("error %s while sending PPCCOM block of length %d\n", (const char*)e, len);
            return 0;
         } catch (...) {
            if (_DebugLevel) ErrorPrintf("unhandled exception while sending PPCCOM block of length %d\n", len);
            return 0;
         }
         return len;
      } else {
         return PPC_DEVICE_NOT_INITIALIZED;
      }
   } else {
   	return _SerialChannel->Write(buf, len);
   }
  //## end cPPCDevice::SendBlock%1091085016.body
}

void cPPCDevice::FlushInput ()
{
  //## begin cPPCDevice::FlushInput%1091085017.body preserve=yes
   if (_SerialChannel == NULL) {
      if (_Client != NULL) {
         _Client->FlushInput(_IscosNo);
      }
   } else {
      _SerialChannel->FlushInput();
   }
  //## end cPPCDevice::FlushInput%1091085017.body
}

LONG_T cPPCDevice::CheckBlock (BUF_T block, ULONG_T block_len, BUF_T buf, ULONG_T buf_size, UCHAR_T &iscos_no)
{
  //## begin cPPCDevice::CheckBlock%1091085018.body preserve=yes
   UCHAR_T * block_ptr = (UCHAR_T*)block;
   iscos_no = 0;
   ULONG_T block_pos = 0;
   BOOL_T check = false;
   int flag = 0;
   int state = -4;
   unsigned char checksum = 0;
   unsigned long efflength = 0;
   unsigned long length = 0;
   unsigned char * bufptr = buf;
   int err = 0;
   int c = 0;
   unsigned char in_data;
   BOOL_T rcv = false;
   while (true) {
      if (block_pos < block_len) {
         c = block_ptr[block_pos];
         block_pos++;
      } else {
         return PPC_TIMEOUT;
      }
      in_data = (unsigned char)c;
      switch (flag) {
      case 0:
         if (in_data == ST1) {
            flag = 1;
         } else {
            if (in_data == ST2) {
               flag = 2;
            }
         }
         break;
      case 1:
         if (in_data == ST1) {
            flag = 3;
         } else {
            if (in_data == ST2) {
               state = -1;
               efflength = 0;
               checksum = 0;
            } else {
               state = -4;
            }
         }
      break;
      case 2:
         if (in_data == ST2) {
            flag = 0;
         } else {
            if (in_data == ST1) {
               state = -3;
            } else {
               state = -4;
            }
         }
         break;
      case 3:
         if (in_data == ST1) {
            flag = 1;
         } else {
            if (in_data == ST2) {
               flag = 4;
            } else {
               flag = 0;
            }
         }
         break;
      case 4:
         if (in_data == ST2) {
            flag = 0;
         } else {
            if (in_data == ST1) {
               state = -3;
            } else {
               if (in_data > ST2) {
                  state = -4;
               } else {
                  state = -1;
                  efflength = 0;
                  checksum = 0;
               }
            }
         }
         break;
      default:
         err = PPC_INVALID_FLAG;
         rcv = true;
      }
      switch (state) {
      case -4:
         check = false;
         flag = 0;
         if (in_data == ST1) {
            state = -3;
         }
         break;
      case -3:
         check = false;
         flag = 0;
         if (in_data == ST2) {
            efflength = 0;
            checksum = 0;
            state = -2;
         } else {
            if (in_data != ST1) {
               state = -4;
            }
         }
         break;
      case -2:
         flag = 0;
         if (in_data == ST1) {
            state = -3;
         } else {
            if (in_data >= ST2) {
               state = -4;
            } else {
               length |= ((WORD)in_data)<<8;
               check = true;
               state = -1;
            }
         }
         break;
      case -1:
         if (flag == 0 || flag == 3) {
            length |= (WORD)in_data;
            if (length == 0) {
               err = PPC_SIZE_ZERO;
               rcv = true;
            } else if (length > (_BlockLength + REQUEST_ID_SIZE + 2)) {
               // Carry the length of the Data Frame (+2 for block and Node) (+2 for Request-ID)
               AdjustBlockLength((USHORT_T)length);
               err = PPC_SIZE_EXCEEDS_MAX_BLOCK_LEN;
               rcv = true;
            } else {
               state = 0;
            }
         }
         break;
      case 0:
         if (flag == 0 || flag == 3) {
            *bufptr = in_data;
            efflength++;
            if (efflength > buf_size) {
               err = PPC_BUF_TOO_SMALL;
               rcv = true;
            } else {
               bufptr++;
               if (efflength == length) state = 1;
            }
         }
         break;
      case 1:
         check = false;
         if (flag == 0 || flag == 3) {
            if (checksum != in_data) {
               err = PPC_CHECKSUM_ERROR;
            } else {
               err = 0;
            }
            rcv = true;
         }
         break;
      default:
         err = PPC_INVALID_STATE;
         rcv = true;
      }
      if (check) {
         checksum = ROT_RIGHT(checksum) ^ in_data;
      }
      if (rcv) {
         if (err == 0) {
            return efflength;
         } else {
            return err;
         }
      }
   }   
  //## end cPPCDevice::CheckBlock%1091085018.body
}

void cPPCDevice::BlockDebug (BUF_T block, ULONG_T block_len, BOOL_T read)
{
  //## begin cPPCDevice::BlockDebug%1091085019.body preserve=yes
   if (!_InterfaceMode || !_TimingProtocol) {
      return;
   }
   const char * d = NULL;
   if (read) {
      d = "<--";
   } else {
      d = "-->";
   }
   REQUEST_ID_TYPE request_id = 0;
   if (_SafeCommunication) {
      request_id = *(REQUEST_ID_TYPE*)&block[block_len - REQUEST_ID_SIZE];
   }
   unsigned char * b = (unsigned char *)block;
   unsigned long bl = block_len;
   if (PPC_FUNC_BLOCK(b)) {
      int i, params = 6;
      FUNCBLOCK func = {0};
      memswap(&func, b, bl / 2);
      LogPrintf("%02x(", b[0]);
      for (i=0; i<params-1; i++) {
         LogPrintf("%x,", func.param[i]);
      }
      if (params > 0) {
         LogPrintf("%x", func.param[i]);
         LogPrintf(")");
      }
      LogPrintf(": %d  %s\n", (int)request_id, d);
   } else {
      if (PPC_OKAY_READY(b)) {
         LogPrintf("OK/READY: %d     %s\n", (int)request_id, d);
      } else if (PPC_DATA(b)) {
         LogPrintf("DATA: %d     %s\n", (int)request_id, d);
      } else if (PPC_NO_DATA(b)) {
         LogPrintf("NO DATA: %d     %s\n", (int)request_id, d);
      } else if (PPC_LAST_DATA(b)) {
         LogPrintf("LAST DATA: %d     %s\n", (int)request_id, d);
      } else if (PPC_ERROR(b)) {
         LogPrintf("ERROR: %d %3d    %s\n", (int)request_id, PpcError(b, block_len), d);
      } else if (PPC_IDENT(b)) {
         LogPrintf("IDENT: %d     %s\n", (int)request_id, d);
      } else if (PPC_ABORT_MESSAGE(b)) {
         LogPrintf("ABORT MESSAGE: %d     %s\n", (int)request_id, d);
      } else {
         LogPrintf("SHIT: %d     %s\n", (int)request_id, d);
      }
   }
  //## end cPPCDevice::BlockDebug%1091085019.body
}

void cPPCDevice::Changed (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags)
{
  //## begin cPPCDevice::Changed%1117647788.body preserve=yes
   if (strcmp(buf_spec, "logic") == 0) {
      /// PR 02.06.05 include bit mapped variables into data change
      ///             event mechanism
      ULONG_T bit_addr = address * 0x10;
      for (int i=0; i<0x10; i++) {
         cDevice::Changed("bit", bit_addr + i, flags);
      }
   }
   else {
      cDevice::Changed(buf_spec, address, flags);
   }
  //## end cPPCDevice::Changed%1117647788.body
}

BOOL_T cPPCDevice::MappingValid (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type)
{
  //## begin cPPCDevice::MappingValid%1171550945.body preserve=yes
   if (strcmp(buf_spec, "bit") == 0) {
      return true;
   } else if (strcmp(buf_spec, "register") == 0) {
      if (data_type == SH_SHORT ||
          data_type == SH_USHORT ||
          data_type == SH_LONG ||
          data_type == SH_ULONG ||
          data_type == SH_FLOAT ||
          data_type == SH_DOUBLE ||
          data_type == SH_STRING) {
         return true;
      } else {
         return false;
      }
   } else if (strcmp(buf_spec, "logic") == 0) {
      if (data_type == SH_SHORT ||
          data_type == SH_USHORT) {
         return true;
      } else {
         return false;
      }
   }
   return false;
  //## end cPPCDevice::MappingValid%1171550945.body
}

void cPPCDevice::AdjustBlockLength (USHORT_T block_length)
{
  //## begin cPPCDevice::AdjustBlockLength%1196082901.body preserve=yes
   if (_AdjustBlockLength) {
      if (block_length == 0) {
      } else if (block_length <= MAX_BLOCK_LEN) {
         _BlockLength = block_length;
      }
   }
  //## end cPPCDevice::AdjustBlockLength%1196082901.body
}

REQUEST_ID_TYPE cPPCDevice::NextRequestId ()
{
   _MasterRequestId++;
   return _MasterRequestId;
}

LONG_T cPPCDevice::ExpectedResponseLength (FUNCBLOCK *func_block)
{
   FUNCBLOCK func = {0};
   memswap(&func, func_block, sizeof(func) / 2);
   if (func.function == SAVREG) {
      int noof_regs = func.param[1] - func.param[0] + 1;
      return (noof_regs * 2) + 2;
   } else if (func.function == SAVLOG) {
      int noof_logs = func.param[1] - func.param[0] + 1;
      return (noof_logs * 2) + 2;
   }
   return 0;
}

//## Get and Set Operations for Class Attributes (implementation)

UCHAR_T cPPCDevice::get_IscosNo () const
{
  //## begin cPPCDevice::get_IscosNo%3FD45862038A.get preserve=no
  return _IscosNo;
  //## end cPPCDevice::get_IscosNo%3FD45862038A.get
}

void cPPCDevice::set_IscosNo (UCHAR_T value)
{
  //## begin cPPCDevice::set_IscosNo%3FD45862038A.set preserve=no
  _IscosNo = value;
  //## end cPPCDevice::set_IscosNo%3FD45862038A.set
}

ULONG_T cPPCDevice::get_BlockTimeout () const
{
  //## begin cPPCDevice::get_BlockTimeout%410F55C0000F.get preserve=no
  return _BlockTimeout;
  //## end cPPCDevice::get_BlockTimeout%410F55C0000F.get
}

void cPPCDevice::set_BlockTimeout (ULONG_T value)
{
  //## begin cPPCDevice::set_BlockTimeout%410F55C0000F.set preserve=no
  _BlockTimeout = value;
  //## end cPPCDevice::set_BlockTimeout%410F55C0000F.set
}

ULONG_T cPPCDevice::get_BlockRetries () const
{
  //## begin cPPCDevice::get_BlockRetries%410F55E9004E.get preserve=no
  return _BlockRetries;
  //## end cPPCDevice::get_BlockRetries%410F55E9004E.get
}

void cPPCDevice::set_BlockRetries (ULONG_T value)
{
  //## begin cPPCDevice::set_BlockRetries%410F55E9004E.set preserve=no
  _BlockRetries = value;
  //## end cPPCDevice::set_BlockRetries%410F55E9004E.set
}

ULONG_T cPPCDevice::get_BaudRate () const
{
  //## begin cPPCDevice::get_BaudRate%3FD459580196.get preserve=no
  return _BaudRate;
  //## end cPPCDevice::get_BaudRate%3FD459580196.get
}

void cPPCDevice::set_BaudRate (ULONG_T value)
{
  //## begin cPPCDevice::set_BaudRate%3FD459580196.set preserve=no
  _BaudRate = value;
  //## end cPPCDevice::set_BaudRate%3FD459580196.set
}

ParityTypes cPPCDevice::get_Parity () const
{
  //## begin cPPCDevice::get_Parity%3FD4595801A5.get preserve=no
  return _Parity;
  //## end cPPCDevice::get_Parity%3FD4595801A5.get
}

void cPPCDevice::set_Parity (ParityTypes value)
{
  //## begin cPPCDevice::set_Parity%3FD4595801A5.set preserve=no
  _Parity = value;
  //## end cPPCDevice::set_Parity%3FD4595801A5.set
}

HandshakeTypes cPPCDevice::get_Handshake () const
{
  //## begin cPPCDevice::get_Handshake%3FD4595801A6.get preserve=no
  return _Handshake;
  //## end cPPCDevice::get_Handshake%3FD4595801A6.get
}

void cPPCDevice::set_Handshake (HandshakeTypes value)
{
  //## begin cPPCDevice::set_Handshake%3FD4595801A6.set preserve=no
  _Handshake = value;
  //## end cPPCDevice::set_Handshake%3FD4595801A6.set
}

UCHAR_T cPPCDevice::get_CharLen () const
{
  //## begin cPPCDevice::get_CharLen%3FD4595801A7.get preserve=no
  return _CharLen;
  //## end cPPCDevice::get_CharLen%3FD4595801A7.get
}

void cPPCDevice::set_CharLen (UCHAR_T value)
{
  //## begin cPPCDevice::set_CharLen%3FD4595801A7.set preserve=no
  _CharLen = value;
  //## end cPPCDevice::set_CharLen%3FD4595801A7.set
}

UCHAR_T cPPCDevice::get_StartBits () const
{
  //## begin cPPCDevice::get_StartBits%3FD4595801B5.get preserve=no
  return _StartBits;
  //## end cPPCDevice::get_StartBits%3FD4595801B5.get
}

void cPPCDevice::set_StartBits (UCHAR_T value)
{
  //## begin cPPCDevice::set_StartBits%3FD4595801B5.set preserve=no
  _StartBits = value;
  //## end cPPCDevice::set_StartBits%3FD4595801B5.set
}

UCHAR_T cPPCDevice::get_StopBits () const
{
  //## begin cPPCDevice::get_StopBits%3FD4595801B6.get preserve=no
  return _StopBits;
  //## end cPPCDevice::get_StopBits%3FD4595801B6.get
}

void cPPCDevice::set_StopBits (UCHAR_T value)
{
  //## begin cPPCDevice::set_StopBits%3FD4595801B6.set preserve=no
  _StopBits = value;
  //## end cPPCDevice::set_StopBits%3FD4595801B6.set
}

ULONG_T cPPCDevice::get_ReadPort () const
{
  //## begin cPPCDevice::get_ReadPort%4108A27902EE.get preserve=no
  return _ReadPort;
  //## end cPPCDevice::get_ReadPort%4108A27902EE.get
}

void cPPCDevice::set_ReadPort (ULONG_T value)
{
  //## begin cPPCDevice::set_ReadPort%4108A27902EE.set preserve=no
  _ReadPort = value;
  //## end cPPCDevice::set_ReadPort%4108A27902EE.set
}

ULONG_T cPPCDevice::get_WritePort () const
{
  //## begin cPPCDevice::get_WritePort%4108A2990000.get preserve=no
  return _WritePort;
  //## end cPPCDevice::get_WritePort%4108A2990000.get
}

void cPPCDevice::set_WritePort (ULONG_T value)
{
  //## begin cPPCDevice::set_WritePort%4108A2990000.set preserve=no
  _WritePort = value;
  //## end cPPCDevice::set_WritePort%4108A2990000.set
}

STRING_T cPPCDevice::get_Host () const
{
  //## begin cPPCDevice::get_Host%4108A2AA0157.get preserve=no
  return _Host;
  //## end cPPCDevice::get_Host%4108A2AA0157.get
}

void cPPCDevice::set_Host (STRING_T value)
{
  //## begin cPPCDevice::set_Host%4108A2AA0157.set preserve=no
  _Host = value;
  //## end cPPCDevice::set_Host%4108A2AA0157.set
}

UCHAR_T cPPCDevice::get_SpsState () const
{
  //## begin cPPCDevice::get_SpsState%410F5A5D02EE.get preserve=no
  return _SpsState;
  //## end cPPCDevice::get_SpsState%410F5A5D02EE.get
}

void cPPCDevice::set_SpsState (UCHAR_T value)
{
  //## begin cPPCDevice::set_SpsState%410F5A5D02EE.set preserve=no
  _SpsState = value;
  //## end cPPCDevice::set_SpsState%410F5A5D02EE.set
}

UCHAR_T cPPCDevice::get_SpsVersion () const
{
  //## begin cPPCDevice::get_SpsVersion%410F5A6B02BF.get preserve=no
  return _SpsVersion;
  //## end cPPCDevice::get_SpsVersion%410F5A6B02BF.get
}

void cPPCDevice::set_SpsVersion (UCHAR_T value)
{
  //## begin cPPCDevice::set_SpsVersion%410F5A6B02BF.set preserve=no
  _SpsVersion = value;
  //## end cPPCDevice::set_SpsVersion%410F5A6B02BF.set
}

ULONG_T cPPCDevice::get_VerifyBufSize () const
{
  //## begin cPPCDevice::get_VerifyBufSize%42C56C9A02AF.get preserve=no
  return _VerifyBufSize;
  //## end cPPCDevice::get_VerifyBufSize%42C56C9A02AF.get
}

void cPPCDevice::set_VerifyBufSize (ULONG_T value)
{
  //## begin cPPCDevice::set_VerifyBufSize%42C56C9A02AF.set preserve=no
  _VerifyBufSize = value;
  //## end cPPCDevice::set_VerifyBufSize%42C56C9A02AF.set
}

USHORT_T * cPPCDevice::get_VerifyBuf () const
{
  //## begin cPPCDevice::get_VerifyBuf%42C56CC6002E.get preserve=no
  return _VerifyBuf;
  //## end cPPCDevice::get_VerifyBuf%42C56CC6002E.get
}

void cPPCDevice::set_VerifyBuf (USHORT_T * value)
{
  //## begin cPPCDevice::set_VerifyBuf%42C56CC6002E.set preserve=no
  _VerifyBuf = value;
  //## end cPPCDevice::set_VerifyBuf%42C56CC6002E.set
}

BOOL_T cPPCDevice::is_SerialCommunicationUsed () const
{
    return (_SerialChannel != NULL) ? true : false;
}

BOOL_T cPPCDevice::is_UDPCommunicationUsed () const
{
   return (_CSComm != NULL) ? true : false;
}

// Additional Declarations
  //## begin cPPCDevice%3FCF4E67000F.declarations preserve=yes
  //## end cPPCDevice%3FCF4E67000F.declarations

//## begin module%3FCF4E67000F.epilog preserve=yes
//## end module%3FCF4E67000F.epilog


