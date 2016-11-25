//## begin module%3FCF4E67000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FCF4E67000F.cm

//## begin module%3FCF4E67000F.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3FCF4E67000F.cp

//## Module: cPPCDevice%3FCF4E67000F; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Device\cPPCDevice.cpp

//## begin module%3FCF4E67000F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FCF4E67000F.additionalIncludes

//## begin module%3FCF4E67000F.includes preserve=yes
//## end module%3FCF4E67000F.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cPPCDevice
//#include "Control/Device/cPPCDevice.h"
#include "cPPCDevice.h"
#include "cPPCClient.h"
// cMemoryAddressedDevice
//#include "Control/Device/cMemoryAddressedDevice.h"
// cStringCache
//#include "Control/Device/cStringCache.h"
// cCacheControl
//#include "Control/Device/cCacheControl.h"
// cBlockCache
//#include "Control/Device/cBlockCache.h"
// cCache
//#include "Control/Device/cCache.h"
// cPPCOperator
//#include "Control/Device/cPPCOperator.h"
//## begin module%3FCF4E67000F.additionalDeclarations preserve=yes

#define WORD_SWAP(w)    (((w&0x00ff)<<8)+((w&0xff00)>>8))
void __memswap(unsigned short * target, unsigned short * source, unsigned long words)
{
   for (unsigned long i=0; i<words; i++) {
      target[i] = WORD_SWAP(source[i]);
   }
}
#define TRANSFER_BUF_SIZE  0x400
#define REG_BUF_SIZE       (TRANSFER_BUF_SIZE/2)
#define PPCCOM_TIMEOUT     5000

#define DEBUG
//#undef DEBUG
extern bool _Debug;

#undef SIMULATE

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
#define BLOCK_PROTOCOL_ERROR        50

#define PROGRAM_RUNNING					0x10
#define PROGRAM_ERROR  					0x20
#define POWER_FAILURE  					0x40
#define FIRMWARE_ERROR 					0x80

#define SET_SPS_STATE(state, block) \
	if (state & POWER_FAILURE) state &= ~POWER_FAILURE; \
	block[1] |= state;

static void PrintBuffer(int channel, int * buffer, unsigned short address, int len)
{	int i;
	char file_name[50] = {0};
	FILE * stream;
	len = len / 2;
	sprintf(file_name, "i60_%d.prot", channel);
	stream = fopen(file_name, "a");
	if (stream) {
		fprintf(stream, "\nchannel %d address %04x buffer %p len %d",channel,address,buffer,len);
		for (i=0; i<len; i++) {
			if (i%10 == 0) fprintf(stream,"\n");
			fprintf(stream, "%5d ", buffer[i]);
		}
		fprintf(stream,"\n");
		fclose(stream);
	}
}

#define BitmapSet(bitmap, first_addr, symbols, op)
static unsigned char _SpsState = 0;
static unsigned char _SpsVersion = 0;


#include "Control/SerialChannel/cStandardChannel.h"

// PPCCOM slave thread

class cPPCSlave: public cThread
{
public:
   cPPCSlave(cPPCDevice * device)
   {
      _Terminated = false;
      _Device = device;
   };
   virtual ~cPPCSlave() {};
   virtual int onMain (void *extra);
   void Start()
   {
   if (start(teStart)) {
printf("slave started\n");
   } else {
printf("failed to start slave\n");
   }
   waitFor(teStart);
   };
private:
   cPPCDevice * _Device;
   bool _Terminated;
};

int cPPCSlave::onMain(void *extra)
{
   while (!_Terminated) {
      _Device->Process();
 		if (!_Terminated) Sleep(10);
   }
   return 0;
};

//## end module%3FCF4E67000F.additionalDeclarations


// Class cPPCDevice 












#ifdef lassma
cPPCDevice::cPPCDevice()
  //## begin cPPCDevice::cPPCDevice%.hasinit preserve=no
      : _IscosNo(0), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _RegisterCache(NULL), _LogicCache(NULL), _SerialChannel(NULL), _Simulation(NULL)
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
      : _IscosNo(0), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _RegisterCache(NULL), _LogicCache(NULL), _SerialChannel(NULL), _Simulation(NULL)
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
      : _IscosNo(0), _BaudRate(19200), _Parity(None), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _RegisterCache(NULL), _LogicCache(NULL), _SerialChannel(NULL), _Simulation(NULL)
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
   _IscosNo = (UCHAR_T)config_obj->PropertyValue("IscosNo", (ULONG_T)_IscosNo);
   if (_Simulated) {
      _Simulation = new cMemoryAddressedDevice(config_obj, cell, 2);
      _Simulation->set_Node(_IscosNo);
   } else {
      cConfigurationObject * serial_channel_obj = config_obj->PropertyValue("SerialChannel", NULL_OBJECT, true);
      _SerialChannel = cSerialChannelFactory::CreateSerialChannel(serial_channel_obj);
      _SerialChannel->Open();
      _SerialChannel->SetBaudRate(_BaudRate);
      _SerialChannel->SetCharLen(_CharLen);
      _SerialChannel->SetStartBits(_StartBits);
      _SerialChannel->SetStopBits(_StopBits);
      _SerialChannel->SetParity(_Parity);
   }
   //## end cPPCDevice::cPPCDevice%1070550133.body
}
#endif

cPPCDevice::cPPCDevice (unsigned short read_port, unsigned short write_port,
                        const char * host)
                        : _IscosNo(0)
{
   memset(_RegBuf, 0, sizeof(_RegBuf));
   memset(_LogBuf, 0, sizeof(_LogBuf));
   _Comm = new cUDPComm(read_port, write_port, host);
   _Client = new cPPCClient(this, _Comm);
   _Server = NULL;
   _Slave = NULL;
}

cPPCDevice::cPPCDevice (unsigned short read_port, unsigned short write_port)
                        : _IscosNo(0)
{
   memset(_RegBuf, 0, sizeof(_RegBuf));
   memset(_LogBuf, 0, sizeof(_LogBuf));
   _Comm = new cUDPComm(read_port, write_port);
   _Client = new cPPCClient(this, _Comm);
   _Server = NULL;
   _Slave = new cPPCSlave(this);
}

cPPCDevice::~cPPCDevice()
{
  //## begin cPPCDevice::~cPPCDevice%.body preserve=yes
#ifdef lassma
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
#endif
  //## end cPPCDevice::~cPPCDevice%.body
}



//## Other Operations (implementation)
void cPPCDevice::Start ()
{
  //## begin cPPCDevice::Start%1070963654.body preserve=yes
   if (_Client != NULL) {
      _Client->Start();
   } else if (_Server != NULL) {
      _Server->Start();
   }
   if (_Slave != NULL) {
      _Slave->Start();
   }
#ifdef lassma
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
   }
#endif
  //## end cPPCDevice::Start%1070963654.body
}

void cPPCDevice::Stop ()
{
  //## begin cPPCDevice::Stop%1070963655.body preserve=yes
#ifdef lassma
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
   }
#endif
   //## end cPPCDevice::Stop%1070963655.body
}

void cPPCDevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T cache_value, ULONG_T size)
{
  //## begin cPPCDevice::Cache%1070880000.body preserve=yes
#ifdef lassma
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Cache(address, cache_value, size);
   }
#endif
   //## end cPPCDevice::Cache%1070880000.body
}

void cPPCDevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
  //## begin cPPCDevice::Buffer%1070880001.body preserve=yes
#ifdef lassma
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Buffer(address, elements);
   }
#endif
   //## end cPPCDevice::Buffer%1070880001.body
}

void cPPCDevice::UseBuffer (CONST_STRING_T buf_spec)
{
  //## begin cPPCDevice::UseBuffer%1075647705.body preserve=yes
  //## end cPPCDevice::UseBuffer%1075647705.body
}

void cPPCDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cPPCDevice::Read%1070550134.body preserve=yes
   _LastError = 0;
   USHORT_T reg_count = (USHORT_T)len / 2;
   UCHAR_T command = Command(buf_spec, true);
   INT_T err = I60Save (_IscosNo, command, buf, buf_size,(USHORT_T)address, (USHORT_T)reg_count, PPCCOM_TIMEOUT);
   if (err != 0) {
      printf("I60Save error %d\n", err);
   }
   _LastError = err;
#ifdef lassma
   if (len == 0) return;
   if (strcmp(buf_spec, "bit") == 0) {
      ReadBit(address, len, buf, buf_size, flags);
      return;
   }
   USHORT_T reg_count = (USHORT_T)len / 2;
   if (!(flags && VF_DEVICE)) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         if (cache->Cached(address, reg_count)) {
            cache->Read(address, reg_count, buf, buf_size, flags);
            return;
         }
      }
   }
   // check if interface (slave) mode active
   // if so only read from cache
   if (_InterfaceMode) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         cache->Read(address, reg_count, buf, buf_size, flags);
         return;
      }
      return;
   }
   if (_Simulated) {
      _Simulation->Read(buf_spec, address, len, buf, buf_size, flags);
   } else {
      UCHAR_T command = Command(buf_spec, true);
      INT_T err = I60Save (_IscosNo, command, buf, buf_size,(USHORT_T)address, (USHORT_T)reg_count, PPCCOM_TIMEOUT);
      if (err != 0) {
         throw cError(I60_READ, err,
                      cConvUtils::StringValue(_IscosNo).c_str(),
                      cConvUtils::StringValue(command).c_str(),
                      cConvUtils::StringValue(address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
   }
#endif
  //## end cPPCDevice::Read%1070550134.body
}

void cPPCDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cPPCDevice::Write%1070550135.body preserve=yes
   _LastError = 0;
   USHORT_T reg_count = (USHORT_T)len / 2;
   UCHAR_T command = Command(buf_spec, false);
   INT_T err = I60Load (_IscosNo, command, buf, len, (USHORT_T)address, reg_count, PPCCOM_TIMEOUT);
   if (err != 0) {
      printf("I60load error %d\n", err);
   }
   _LastError = err;
#ifdef lassma
   if (len == 0) return;
   if (strcmp(buf_spec, "bit") == 0) {
      WriteBit(address, len, buf, flags);
      return;
   }
   USHORT_T reg_count = (USHORT_T)len / 2;
   // check if interface (slave) mode active
   // if so only write to cache
   if (_InterfaceMode) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         cache->Write(address, reg_count, buf, flags);
         return;
      }
      return;
   }
   if (_Simulated) {
      _Simulation->Write(buf_spec, address, len, buf, flags);
   } else {
      USHORT_T reg_count = (USHORT_T)len / 2;
      UCHAR_T command = Command(buf_spec, false);
      INT_T err = I60Load (_IscosNo, command, buf, len, (USHORT_T)address, reg_count, PPCCOM_TIMEOUT);
      if (err != 0) {
         throw cError(I60_READ, err,
                      cConvUtils::StringValue(_IscosNo).c_str(),
                      cConvUtils::StringValue(command).c_str(),
                      cConvUtils::StringValue(address).c_str(),
                      cConvUtils::StringValue(len).c_str());
      }
   }
#endif
  //## end cPPCDevice::Write%1070550135.body
}

void cPPCDevice::Process ()
{
  //## begin cPPCDevice::Process%1084381602.body preserve=yes
#define CHECK_ADDR(addr,regs,elements) ((ULONG_T)(addr + regs) < (ULONG_T)elements)

   USHORT_T * reg_buf = (USHORT_T*)&_RegBuf;
   ULONG_T register_count = sizeof(_RegBuf) / 2;
   USHORT_T * log_buf = (USHORT_T*)&_LogBuf;
   ULONG_T logword_count = sizeof(_LogBuf) / 2;
   if (reg_buf == NULL || log_buf == NULL) return;
   char data_block[MAX_BLOCK_LEN] = {0};
   char read_buffer[MAX_BLOCK_LEN*2] = {0};
   unsigned short address, first_reg;
	unsigned short val, bit_index;
	long nread = 0;
	FUNCBLOCK func;
	unsigned char okay_ready_block[2];
	int regs = 0;
	int channel = 1;
	int timeout = 5000;
	BOOL_T verbose = false;
   try {
      nread = I60Com((UCHAR_T)_IscosNo,
                     NULL, 0,
                     read_buffer, sizeof(read_buffer),
                     timeout);
      if (nread <= 0) return;
		memcpy(&func, read_buffer, sizeof(func));
		memswap(&func, &func, 1);
      UCHAR_T no = ISCOS_NO(func.info);
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
                           data_block, MAX_BLOCK_LEN, 
                           read_buffer, sizeof(read_buffer),
                           timeout);
            if (nread <= 0) {
//               throw cError(nread, 0);
               printf("I60Com error %d\n", nread);
               return;
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
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
                           okay_ready_block, sizeof(OKAY_READY_BLOCK),
                           data_block, sizeof(data_block),
                           timeout);
            if (nread <= 0) {
//               throw cError(nread, 0);
               printf("I60Com error %d\n", nread);
               return;
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
                        okay_ready_block, sizeof(okay_ready_block),
                        NULL, 0, timeout);
         if (nread < 0) {
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
                           data_block, MAX_BLOCK_LEN,
                           read_buffer, sizeof(read_buffer), timeout);
            if (nread <= 0) {
//               throw cError(nread, 0);
               printf("I60Com error %d\n", nread);
               return;
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
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
                           okay_ready_block, sizeof(okay_ready_block),
                           data_block, sizeof(data_block), 
	                        timeout);
            if (nread <= 0) {
//               throw cError(nread, 0);
               printf("I60Com error %d\n", nread);
               return;
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
                        okay_ready_block, sizeof(okay_ready_block),
                        NULL, 0,
                        timeout);
         if (nread < 0) {
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
                        okay_ready_block, sizeof(okay_ready_block),
                        NULL, 0,
                        timeout);
         if (nread < 0) {
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
//            throw cError(nread, 0);
            printf("I60Com error %d\n", nread);
            return;
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
                           okay_ready_block, sizeof(okay_ready_block),
                           NULL, 0, timeout);
            if (nread < 0) {
//               throw cError(nread, 0);
               printf("I60Com error %d\n", nread);
               return;
            }
   	   }
		   break;
	   default:
		   SendErrorBlock(FUNCTION_NOT_AVAILABLE, timeout);
	   }
   } catch (cError & e) {
      printf("error %s in sps slave control\n", (const char *)e);
      Sleep(200);
   } catch (...) {
      printf("unhandled exception in sps slave control\n");
      Sleep(200);
   }
   //## end cPPCDevice::Process%1084381602.body
}

INT_T cPPCDevice::I60Load (UCHAR_T iscos_no, UCHAR_T order, void *outbuf, ULONG_T outbuf_len, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Load%1070550136.body preserve=yes
#ifdef lassma
   cObjectLock __lock__(&_DeviceMutex);
   _SerialChannel->FlushInput();
#endif
   _Client->FlushInput(0);
   unsigned char temp_buffer[TRANSFER_BUF_SIZE];
   char * outbuf_ptr = (char *)outbuf;
   FUNCBLOCK func;
   unsigned short _noof_regs = noof_regs;
   unsigned short _regs_to_write = 0;
   unsigned short _reg_addr = reg_addr;
   if (_noof_regs > REG_BUF_SIZE) {
      _regs_to_write = _noof_regs - REG_BUF_SIZE;
      _noof_regs = REG_BUF_SIZE;
   }
   while (_noof_regs > 0) {
   	func.info = iscos_no & 0x0f;
   	func.function = order;
   	func.function |= 0x80;
   	func.param[0] = _reg_addr;
   	func.param[1] = _reg_addr + _noof_regs - 1;
   	memswap(&func, &func, 3);
   	memswap(temp_buffer, outbuf_ptr, _noof_regs);
      int rc = SupplyData(iscos_no,
                          (void *)&func, 6, (void *)temp_buffer, _noof_regs * 2,
                          timeout);
      if (rc == 0) {
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
         return rc;
      }
   }
   return 0;
  //## end cPPCDevice::I60Load%1070550136.body
}

INT_T cPPCDevice::I60Save (UCHAR_T iscos_no, UCHAR_T order, void *inbuf, ULONG_T inbuf_size, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Save%1070550137.body preserve=yes
#ifdef lassma
   cObjectLock __lock__(&_DeviceMutex);
   _SerialChannel->FlushInput();
#endif
   _Client->FlushInput(0);
   unsigned char temp_buffer[TRANSFER_BUF_SIZE];
   char * inbuf_ptr = (char *)inbuf;
   FUNCBLOCK func;
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
   	func.function = order;
   	func.function |= 0x80;
      func.param[0] = _reg_addr;
   	func.param[1] = _reg_addr + _noof_regs - 1;
   	memswap(&func, &func, 3);
      unsigned long requested_len = _noof_regs * 2;
      int rc = RequestData(iscos_no,
                           (void *)&func, 6, temp_buffer, sizeof(temp_buffer),
                           requested_len, timeout);
      if (rc == 0) {
         _bytes_read += requested_len;
         if (_bytes_read > inbuf_size) {
            return I60_BUF_TOO_SMALL;
         } else {
            memswap(inbuf_ptr, temp_buffer, (requested_len+1)/2);
            inbuf_ptr += requested_len;
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
         return rc;
      }
   }
   return 0;
  //## end cPPCDevice::I60Save%1070550137.body
}

INT_T cPPCDevice::I60Bit (UCHAR_T iscos_no, USHORT_T bit_no, UCHAR_T function, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Bit%1070550138.body preserve=yes
#ifdef lassma
   cObjectLock __lock__(&_DeviceMutex);
   _SerialChannel->FlushInput();
#endif
   _Client->FlushInput(0);
   FUNCBLOCK func;
   func.info = iscos_no & 0x0f;
	func.function = BITSET;
	func.function |= 0x80;
   if (function == 'T') {
		func.param[0] = 0x5420;
   } else if (function == 'F') {
		func.param[0] = 0x4620;
   } else {
		return I60_ILLEGAL_FUNCTION;
   }
	func.param[1] = bit_no;
	memswap(&func, &func, 3);
	return RequestData(iscos_no, (void *)&func, 6, NULL, 0, 0, timeout);
  //## end cPPCDevice::I60Bit%1070550138.body
}

LONG_T cPPCDevice::I60Com (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::I60Com%1070550139.body preserve=yes
#ifdef lassma
   cObjectLock __lock__(&_DeviceMutex);
#endif
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
#ifdef lassma
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "I60Request", "cPPCDevice");
#else
   return 0;
#endif
   //## end cPPCDevice::I60Request%1070550140.body
}

UCHAR_T cPPCDevice::Command (CONST_STRING_T buf_spec, BOOL_T read)
{
  //## begin cPPCDevice::Command%1075189792.body preserve=yes
   if (stricmp("register", buf_spec) == 0) {
      return read ? SAVREG : LODREG;
   } else if (stricmp("logic", buf_spec) == 0) {
      return read ? SAVLOG : LODLOG;
   } else {
      return 0;
   }
  //## end cPPCDevice::Command%1075189792.body
}

LONG_T cPPCDevice::WriteBlock (void *block, ULONG_T block_len)
{
  //## begin cPPCDevice::WriteBlock%1070550141.body preserve=yes
#define ROT_RIGHT(byte)		((byte>>1) | ((byte&0x01)<<7))
#define LSB(word)				((unsigned char)(word&0x00ff)) 
#define MSB(word)				((unsigned char)((word&0xff00)>>8))

#define ST1						0xf1
#define ST2						0x59

	unsigned char * data = (unsigned char *)block;
	unsigned long data_len = block_len;
   unsigned char out_buffer[MAX_BLOCK_LEN*2] = {0};
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

if (_Debug)
{
   const char * d = "-->";
   unsigned char * b = (unsigned char *)block;
   unsigned long bl = block_len;
   if (PPC_FUNC_BLOCK(b)) {
      int i, params = (bl - 2) / 2;
		FUNCBLOCK func;
		memswap(&func, b, bl / 2);
      if (params <= 4) {
         printf("%02x(", b[0]);
         for (i=0; i<params-1; i++) {
            printf("%x,", func.param[i]);
         }
			if (params > 0) printf("%x", func.param[i]);
			printf(")  %s\n",d);
      } else {
			printf("%02x invalid param number %d  %s\n", b[0], params, d);
      }
   } else {
      if (PPC_OKAY_READY(b)) {
			printf("OK/READY     %s\n", d);
      } else if (PPC_DATA(b)) {
			printf("DATA         %s\n", d);
      } else if (PPC_NO_DATA(b)) {
			printf("NO DATA      %s\n", d);
      } else if (PPC_LAST_DATA(b)) {
			printf("LAST DATA    %s\n", d);
      } else if (PPC_ERROR(b)) {
			printf("ERROR %3d    %s\n", PpcError(b, out_buf_len), d);
      } else if (PPC_IDENT(b)) {
			printf("IDENT        %s\n", d);
      } else if (PPC_ABORT_MESSAGE(b)) {
			printf("ABORT MESSAGE%s\n", d);
      } else {
			printf("SHIT %02x      %s\n",b[0], d);
      }
   }
}

   cCSMsg msg(out_buffer, out_buf_len);
   msg.SetMsgLen(out_buf_len);
   _Client->Send(&msg);
   return efflength;

#ifdef lassma
   long nwrite = _SerialChannel->Write(out_buffer, out_buf_len);
   if (nwrite == (long)out_buf_len) {

if (_Debug)
{
   const char * d = "-->";
   unsigned char * b = (unsigned char *)block;
   unsigned long bl = block_len;
   if (PPC_FUNC_BLOCK(b)) {
      int i, params = (bl - 2) / 2;
		FUNCBLOCK func;
		memswap(&func, b, bl / 2);
      if (params <= 4) {
         printf("%02x(", b[0]);
         for (i=0; i<params-1; i++) {
            printf("%x,", func.param[i]);
         }
			if (params > 0) printf("%x", func.param[i]);
			printf(")  %s\n",d);
      } else {
			printf("%02x invalid param number %d  %s\n", b[0], params, d);
      }
   } else {
      if (PPC_OKAY_READY(b)) {
			printf("OK/READY     %s\n", d);
      } else if (PPC_DATA(b)) {
			printf("DATA         %s\n", d);
      } else if (PPC_NO_DATA(b)) {
			printf("NO DATA      %s\n", d);
      } else if (PPC_LAST_DATA(b)) {
			printf("LAST DATA    %s\n", d);
      } else if (PPC_ERROR(b)) {
			printf("ERROR %3d    %s\n", PpcError(b, out_buf_len), d);
      } else if (PPC_IDENT(b)) {
			printf("IDENT        %s\n", d);
      } else if (PPC_ABORT_MESSAGE(b)) {
			printf("ABORT MESSAGE%s\n", d);
      } else {
			printf("SHIT %02x      %s\n",b[0], d);
      }
   }
}

      return efflength;
   } else {
		return 0;
	}
#endif
  //## end cPPCDevice::WriteBlock%1070550141.body
}

LONG_T cPPCDevice::ReadBlock (void *blockbuf, ULONG_T blockbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::ReadBlock%1070550142.body preserve=yes
   LONG_T efflength = _Client->GetMessage(blockbuf, blockbuf_size, timeout, _IscosNo);
   if (efflength > 0) {

if (_Debug)
{
   const char * d = "<--";
   unsigned char * b = (unsigned char *)blockbuf;
   unsigned long bl = efflength;
   if (PPC_FUNC_BLOCK(b)) {
      int i, params = (bl - 2) / 2;
		FUNCBLOCK func;
		memswap(&func, b, bl / 2);
      if (params <= 4) {
         printf("%02x(", b[0]);
         for (i=0; i<params-1; i++) {
            printf("%x,", func.param[i]);
         }
			if (params > 0) printf("%x", func.param[i]);
			printf(")  %s\n",d);
      } else {
			printf("%02x invalid param number %d  %s\n", b[0], params, d);
      }
   } else {
      if (PPC_OKAY_READY(b)) {
			printf("OK/READY     %s\n", d);
      } else if (PPC_DATA(b)) {
			printf("DATA         %s\n", d);
      } else if (PPC_NO_DATA(b)) {
			printf("NO DATA      %s\n", d);
      } else if (PPC_LAST_DATA(b)) {
			printf("LAST DATA    %s\n", d);
      } else if (PPC_ERROR(b)) {
			printf("ERROR %3d    %s\n", PpcError(b, efflength), d);
      } else if (PPC_IDENT(b)) {
			printf("IDENT        %s\n", d);
      } else if (PPC_ABORT_MESSAGE(b)) {
			printf("ABORT MESSAGE%s\n", d);
      } else {
			printf("SHIT %02x      %s\n",b[0], d);
      }
   }
}

   }
   if (efflength > 0) {
      return efflength;
   } else {
      return PPC_TIMEOUT;
   }

#ifdef lassma

#define INTER_CHAR_TIMEOUT    100

   BOOL_T check = false;
	int flag = 0;
	int state = -4;
	unsigned char checksum = 0;
	unsigned long efflength = 0;
	unsigned long length = 0;
	unsigned char * bufptr = (unsigned char *)blockbuf;
	int err = 0;
   int c = 0;
   unsigned char in_data;
   unsigned long read_timeout = timeout;
   BOOL_T rcv = false;

   while (true) {
      c = _SerialChannel->GetChar(read_timeout);
      if (c == EOF) return PPC_TIMEOUT;
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
			   } else if (length > MAX_BLOCK_LEN) {
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
            if (efflength > blockbuf_size) {
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

if (_Debug)
{
   const char * d = "<--";
   unsigned char * b = (unsigned char *)blockbuf;
   unsigned long bl = efflength;
   if (PPC_FUNC_BLOCK(b)) {
      int i, params = (bl - 2) / 2;
		FUNCBLOCK func;
		memswap(&func, b, bl / 2);
      if (params <= 4) {
         printf("%02x(", b[0]);
         for (i=0; i<params-1; i++) {
            printf("%x,", func.param[i]);
         }
			if (params > 0) printf("%x", func.param[i]);
			printf(")  %s\n",d);
      } else {
			printf("%02x invalid param number %d  %s\n", b[0], params, d);
      }
   } else {
      if (PPC_OKAY_READY(b)) {
			printf("OK/READY     %s\n", d);
      } else if (PPC_DATA(b)) {
			printf("DATA         %s\n", d);
      } else if (PPC_NO_DATA(b)) {
			printf("NO DATA      %s\n", d);
      } else if (PPC_LAST_DATA(b)) {
			printf("LAST DATA    %s\n", d);
      } else if (PPC_ERROR(b)) {
			printf("ERROR %3d    %s\n", PpcError(b, efflength), d);
      } else if (PPC_IDENT(b)) {
			printf("IDENT        %s\n", d);
      } else if (PPC_ABORT_MESSAGE(b)) {
			printf("ABORT MESSAGE%s\n", d);
      } else {
			printf("SHIT %02x      %s\n",b[0], d);
      }
   }
}
         
         }
         return (err == 0) ? efflength : err;
      }
   }   
#else
   return 0;
#endif
   //## end cPPCDevice::ReadBlock%1070550142.body
}

LONG_T cPPCDevice::CheckBlock (void*block, ULONG_T block_size, void *blockbuf, ULONG_T blockbuf_size, UCHAR_T & iscos_no)
{
  //## begin cPPCDevice::ReadBlock%1070550142.body preserve=yes
   UCHAR_T * block_ptr = (UCHAR_T*)block;
   iscos_no = 0;
   ULONG_T block_pos = 0;
   BOOL_T check = false;
	int flag = 0;
	int state = -4;
	unsigned char checksum = 0;
	unsigned long efflength = 0;
	unsigned long length = 0;
	unsigned char * bufptr = (unsigned char *)blockbuf;
	int err = 0;
   int c = 0;
   unsigned char in_data;
   BOOL_T rcv = false;
   while (true) {
      if (block_pos < block_size) {
         c = block_ptr[block_pos];
         block_pos++;
      } else {
         return err = PPC_TIMEOUT;
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
			   } else if (length > MAX_BLOCK_LEN) {
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
            if (efflength > blockbuf_size) {
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
            return 0;
         }
      }
   }   
   //## end cPPCDevice::ReadBlock%1070550142.body
}

LONG_T cPPCDevice::PpcCom (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout)
{
  //## begin cPPCDevice::PpcCom%1070550143.body preserve=yes
   long size = 0, err = 0;
   if (outbuf_len > 0) size = WriteBlock(outbuf, outbuf_len);
   if (size >= 0) {
      if (inbuf != NULL) {
			return ReadBlock(inbuf, inbuf_size, timeout);
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
   unsigned char read_buffer[MAX_BLOCK_LEN];
   unsigned char data_block[MAX_BLOCK_LEN];
   int func_retries = 2;
	long nwrite = 0;
	long nread = 0;
	BOOL_T data_transfer_error = true;
   while (func_retries-- && data_transfer_error) {
		data_transfer_error = false;
		if ((nwrite = WriteBlock(func, func_len)) < 0) return nwrite;
		INIT_BUFFER(read_buffer);
		if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) return nread;
      if (PPC_OKAY_READY(read_buffer)) {
			unsigned char * buf_ptr = (unsigned char *)data;
			int len = data_len;
			int data_retries = 2;
         while (len && !data_transfer_error) {
            if (len <= DATA_SIZE) {
					SET_INFO_BLOCK(data_block, iscos_no, LAST_DATA_BLOCK);
					memcpy(&(data_block[2]), buf_ptr, len);
					INIT_BUFFER(read_buffer);
               while (data_retries-- && !(PPC_OKAY_READY(read_buffer))) {
						if ((nwrite = WriteBlock(data_block, len + 2)) < 0) return nwrite;
						INIT_BUFFER(read_buffer);
						if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) return nwrite;
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
						if ((nwrite = WriteBlock(data_block, sizeof(data_block))) < 0) return nwrite;
						INIT_BUFFER(read_buffer);
						if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) return nread;
               }
               if (PPC_OKAY_READY(read_buffer)) {
						buf_ptr += DATA_SIZE;
						len -= DATA_SIZE;
						data_retries = 2;
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
//   _SerialChannel->FlushInput();
	return SUPPLY_FAILED;
  //## end cPPCDevice::SupplyData%1070550145.body
}

INT_T cPPCDevice::RequestData (UCHAR_T iscos_no, void *func, ULONG_T func_len, void *databuf, ULONG_T data_buf_size, ULONG_T requested_len, ULONG_T timeout)
{
  //## begin cPPCDevice::RequestData%1070550146.body preserve=yes
   unsigned char read_buffer[MAX_BLOCK_LEN];
	unsigned char okay_ready_block[2];
	unsigned char error_block[2];
	int func_retries = 2;
	int nwrite = 0;
	int nread = 0;
	BOOL_T data_transfer_error = true;
	SET_INFO_BLOCK(okay_ready_block, iscos_no, OKAY_READY_BLOCK);
	SET_INFO_BLOCK(error_block, iscos_no, ERROR_BLOCK);
	while (func_retries-- && data_transfer_error) {
		data_transfer_error = false;
		if ((nwrite = WriteBlock(func, func_len)) < 0) return nwrite;
		INIT_BUFFER(read_buffer);
		if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) return nread;
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
			int data_retries = 2;
			while (PPC_DATA(read_buffer) ||
					PPC_LAST_DATA(read_buffer) ||
					data_retries--) {
				if (PPC_LAST_DATA(read_buffer)) {
               if (requested_len != nread - 2) {
                  return -777;
               }
               if (buf_ptr != NULL) {
                  memcpy(buf_ptr, &read_buffer[2], nread - 2);
					   return 0;
               } else {
					   return -666;
               }
				} else if (PPC_DATA(read_buffer)) {
               if (buf_ptr != NULL) {
                  memcpy(buf_ptr, &read_buffer[2], nread - 2);
               } else {
                  return -555;
               }
					nwrite = WriteBlock(okay_ready_block, 2);
					len += (nread - 2);
					buf_ptr += (nread - 2);
					data_retries = 2;
               requested_len -= (nread - 2);
				}
				INIT_BUFFER(read_buffer);
				if ((nread = ReadBlock(read_buffer, sizeof(read_buffer), timeout)) < 0) return nread;
			}
		}
	}
//   _SerialChannel->FlushInput();
	return REQUEST_FAILED;
  //## end cPPCDevice::RequestData%1070550146.body
}

LONG_T cPPCDevice::SendErrorBlock (USHORT_T err_code, ULONG_T timeout)
{
  //## begin cPPCDevice::SendErrorBlock%1070550147.body preserve=yes
   unsigned char error_block[4] = {0};
	error_block[0] = ERROR_BLOCK;
	error_block[1] = 0;
   SET_SPS_STATE(_SpsState, error_block);
   memswap(&error_block[2], &err_code, 1);
	return I60Com((UCHAR_T)_IscosNo, error_block, sizeof(error_block), NULL, 0, timeout);
  //## end cPPCDevice::SendErrorBlock%1070550147.body
}

void cPPCDevice::ReadBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cPPCDevice::ReadBit%1086172577.body preserve=yes
#ifdef lassma
  if (len != 1) {
      return;
   }
   cPPCOperator op;
   USHORT_T value = 0;
   ULONG_T log_addr = address / 0x10;
   UCHAR_T bit_pos = (UCHAR_T)(address % 0x10);
   ((cDevice *)this)->Get("logic", log_addr,value);
   op.SetValue(SH_USHORT, value);
   *(UCHAR_T*)buf = op.GetBit(bit_pos);
#endif
   //## end cPPCDevice::ReadBit%1086172577.body
}

void cPPCDevice::WriteBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cPPCDevice::WriteBit%1086172578.body preserve=yes
#ifdef lassma
   if (len != 1) {
      return;
   }
   cPPCOperator op;
   UCHAR_T bit_val = *(UCHAR_T*)buf;
   ULONG_T log_addr = address / 0x10;
   UCHAR_T bit_pos = (UCHAR_T)(address % 0x10);
   USHORT_T value = 0;
   ((cDevice *)this)->Get("logic", log_addr, value);
   op.SetValue(SH_BIT_16, value);
   if (bit_val == 0) {
      op.ResetBit(bit_pos);
   } else {
      op.SetBit(bit_pos);
   }
   value = op;
   ((cDevice *)this)->Set("logic", log_addr, value);
#endif
   //## end cPPCDevice::WriteBit%1086172578.body
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

#ifdef lassma

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

#endif

// Additional Declarations
  //## begin cPPCDevice%3FCF4E67000F.declarations preserve=yes
  //## end cPPCDevice%3FCF4E67000F.declarations

//## begin module%3FCF4E67000F.epilog preserve=yes
//## end module%3FCF4E67000F.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cPPCDevice::Get%1088861644.body preserve=no
   value = "sepp";
   int dummy = 0;
//## end cPPCDevice::Get%1088861644.body

//## begin cPPCDevice::Get%1088861645.body preserve=no
   int dummy = 0;
//## end cPPCDevice::Get%1088861645.body

#endif
