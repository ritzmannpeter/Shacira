//## begin module%3FCF4E67000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FCF4E67000F.cm

//## begin module%3FCF4E67000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FCF4E67000F.cp

//## Module: cPPCDevice%3FCF4E67000F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCDevice.h

#ifndef cPPCDevice_h
#define cPPCDevice_h 1

//## begin module%3FCF4E67000F.includes preserve=yes
//## end module%3FCF4E67000F.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cCSComm;
class __DLL_EXPORT__ cUDPComm;
class __DLL_EXPORT__ cSerialChannel;
class __DLL_EXPORT__ cStringCache;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cBlockCache;
class __DLL_EXPORT__ cCache;
class __DLL_EXPORT__ cMemoryAddressedDevice;
class __DLL_EXPORT__ cPPCSerialComm;
class __DLL_EXPORT__ cPPCServer;
class __DLL_EXPORT__ cPPCClient;
class __DLL_EXPORT__ cPPCOperator;

//## begin module%3FCF4E67000F.additionalDeclarations preserve=yes

#ifdef __linux__

typedef unsigned short WORD;

#endif


//#define UNSAFE_VERSION
#ifdef UNSAFE_VERSION
typedef unsigned short REQUEST_ID_TYPE;
#define REQUEST_ID_SIZE    0
#else
typedef unsigned short REQUEST_ID_TYPE;
#define REQUEST_ID_SIZE    sizeof(REQUEST_ID_TYPE)
#endif

typedef struct {
   unsigned char info;
   unsigned char type;
}  INFOBLOCK;

typedef struct {
   unsigned char info;
   unsigned char function;
   unsigned short param[6];
   REQUEST_ID_TYPE request_id;
}  FUNCBLOCK;

#define ISCOS_NO(info)        (info & 0xf0)

#define OKAY_READY_BLOCK			0x00
#define ERROR_BLOCK					0x01
#define NO_DATA_BLOCK				0x02
#define LAST_DATA_BLOCK				0x03
#define DATA_BLOCK					0x04
#define IDENT_BLOCK					0x05
#define ABORT_MESSAGE_BLOCK		0x06

#define PPC_FUNC_BLOCK(block)	(block[0] & 0x80)
#define PPC_OKAY_READY(block) (block[0] == OKAY_READY_BLOCK)
#define PPC_ERROR(block) (block[0] == ERROR_BLOCK)
#define PPC_DATA(block) (block[0] == DATA_BLOCK)
#define PPC_LAST_DATA(block) (block[0] == LAST_DATA_BLOCK)
#define PPC_DATA(block) (block[0] == DATA_BLOCK)
#define PPC_NO_DATA(block) (block[0] == NO_DATA_BLOCK)
#define PPC_IDENT(block) (block[0] == IDENT_BLOCK)
#define PPC_ABORT_MESSAGE(block) (block[0] == ABORT_MESSAGE_BLOCK)
#define INIT_BUFFER(block) (block[0] = (unsigned char)0xff)

#define PPC_SET_INFO(n)				(n & 0x0f)
#define PPC_SET_FUNCTION(f)		(f | 0x80)

#define OKAY_READY_BLOCK_RECEIVED						-101
#define NO_DATA_BLOCK_RECEIVED							-102
#define ERROR_BLOCK_RECEIVED								-103
#define SUPPLY_FAILED										-107
#define REQUEST_FAILED										-108
#define VERIFY_FAILED										-109

#define PPC_CHECKSUM_ERROR									-130
#define PPC_SIZE_ZERO										-131
#define PPC_SIZE_EXCEEDS_MAX_BLOCK_LEN					-132
#define PPC_INVALID_FLAG									-133
#define PPC_INVALID_STATE									-134
#define PPC_TIMEOUT     									-135
#define PPC_BUF_TOO_SMALL                          -136
#define PPC_DEVICE_NOT_INITIALIZED                 -137
#define PPC_SYNC_FAILED                            -138

#define I60_ILLEGAL_FUNCTION								-150
#define I60_LENGTH_MISMATCH								-151
#define I60_BUF_TOO_SMALL                          -152
#define I60_NOTHING_READ                           -153

#define I60_TIMEOUT(err)	(err == BLKTRF_TIMEOUT_OCCURED)
#define I60_SPS_ERROR(err)	((err) > -100 && (err) < 0)

#define BITSET (0x80 | 0x03)	/* OB - Output Buffer */
#define DISREG (0x80 | 0x04)	/* DR - Display Register */
#define ENTREG (0x80 | 0x05)	/* ER - Enter Register */
#define LODLOG	(0x80 | 0x1F)	/* LL - Load Logic */
#define SAVLOG	(0x80 | 0x20)	/* SL - Save Logic */
#define LODREG	(0x80 | 0x21)	/* LR - Load Register */
#define SAVREG	(0x80 | 0x22)	/* SR - Save Register */

#define OKAY_READY_BLOCK		0x00
#define ERROR_BLOCK				0x01
#define NO_DATA_BLOCK			0x02
#define LAST_DATA_BLOCK			0x03
#define DATA_BLOCK				0x04
#define IDENT_BLOCK				0x05
#define ABORT_MESSAGE_BLOCK	0x06

#define STANDARD_PPCCOM_BLOCK_LEN   258
#define MAX_BLOCK_LEN		         1536

#define SET_INFO_BLOCK(block, controller, type) \
	block[0] = type; \
	block[1] = controller;

extern void __memswap(unsigned short * source, unsigned short * target, unsigned long words);
#define memswap(a, b, c) __memswap((unsigned short *)a, (unsigned short *)b, c)
#define ISCOS_0   0

#ifdef DOCUMENTATION_ONLY
#define PPC_LOG_WORD_ADDR(symbol)    ((symbol) / 0x10)
#define PPC_BIT_POS(symbol)          ((symbol) % 0x10)
#define PPC_GET_BIT(pos,log_word)    ((pos) > 15 ? 0 : ((log_word) >> (pos)) & 0x0001)
#define PPC_SET_BIT(pos,log_word)    if (pos > 15) log_word = (log_word) | (0x0001 << (pos));
#define PPC_RESET_BIT(pos,log_word)  if (pos > 15) log_word = (log_word) & ~(0x0001 << (pos));
#endif

//## end module%3FCF4E67000F.additionalDeclarations


//## begin cPPCDevice%3FCF4E67000F.preface preserve=yes
//## end cPPCDevice%3FCF4E67000F.preface

//## Class: cPPCDevice%3FCF4E67000F
//## Category: Control::Device::PPCCom%410896E5001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FD4A1DB0261;cBlockCache { -> F}
//## Uses: <unnamed>%3FD491300280;cCache { -> F}
//## Uses: <unnamed>%3FD5D5C5000F;cCacheControl { -> F}
//## Uses: <unnamed>%3FD60D950186;cStringCache { -> F}
//## Uses: <unnamed>%40A20E82031C;cPPCOperator { -> F}
//## Uses: <unnamed>%4108A53C01D4;cUDPComm { -> F}
//## Uses: <unnamed>%4108A54902BF;cPPCSerialComm { -> F}

class __DLL_EXPORT__ cPPCDevice : public cDevice  //## Inherits: <unnamed>%3FD437DD006D
{
  //## begin cPPCDevice%3FCF4E67000F.initialDeclarations preserve=yes
public:
  //## end cPPCDevice%3FCF4E67000F.initialDeclarations

    //## Constructors (generated)
      cPPCDevice();

      cPPCDevice(const cPPCDevice &right);

    //## Constructors (specified)
      //## Operation: cPPCDevice%1070550133
      cPPCDevice (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cPPCDevice();


    //## Other Operations (specified)
      virtual BOOL_T ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value);
      //## Operation: Start%1070963654
      virtual void Start ();

      //## Operation: Stop%1070963655
      virtual void Stop ();

      //## Operation: Cache%1070880000
      virtual void Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Buffer%1070880001
      virtual void Buffer (MAP_ITEM_T * map_item);
      virtual void Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements = 1);

      //## Operation: Read%1070550134
      virtual void Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Write%1070550135
      virtual void Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);

      //## Operation: Process%1084381602
      virtual void Process ();

      //## Operation: I60Load%1070550136
      INT_T I60Load (UCHAR_T iscos_no, UCHAR_T order, void *outbuf, ULONG_T outbuf_len, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout);

      //## Operation: I60Save%1070550137
      INT_T I60Save (UCHAR_T iscos_no, UCHAR_T order, void *inbuf, ULONG_T inbuf_size, USHORT_T reg_addr, USHORT_T noof_regs, ULONG_T timeout);

      //## Operation: I60Bit%1070550138
      INT_T I60Bit (UCHAR_T iscos_no, USHORT_T bit_no, UCHAR_T function, ULONG_T timeout);

      //## Operation: CheckBlock%1091085018
      LONG_T CheckBlock (BUF_T block, ULONG_T block_len, BUF_T buf, ULONG_T buf_size, UCHAR_T &iscos_no);

      //## Operation: Changed%1117647788
      virtual void Changed (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags = 0);

      //## Operation: MappingValid%1171545273
      virtual BOOL_T MappingValid (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IscosNo%3FD45862038A
      UCHAR_T get_IscosNo () const;
      void set_IscosNo (UCHAR_T value);

      //## Attribute: BlockTimeout%410F55C0000F
      ULONG_T get_BlockTimeout () const;
      void set_BlockTimeout (ULONG_T value);

      //## Attribute: BlockRetries%410F55E9004E
      ULONG_T get_BlockRetries () const;
      void set_BlockRetries (ULONG_T value);

      //## Attribute: BaudRate%3FD459580196
      ULONG_T get_BaudRate () const;
      void set_BaudRate (ULONG_T value);

      //## Attribute: Parity%3FD4595801A5
      ParityTypes get_Parity () const;
      void set_Parity (ParityTypes value);

      //## Attribute: Handshake%3FD4595801A6
      HandshakeTypes get_Handshake () const;
      void set_Handshake (HandshakeTypes value);

      //## Attribute: CharLen%3FD4595801A7
      UCHAR_T get_CharLen () const;
      void set_CharLen (UCHAR_T value);

      //## Attribute: StartBits%3FD4595801B5
      UCHAR_T get_StartBits () const;
      void set_StartBits (UCHAR_T value);

      //## Attribute: StopBits%3FD4595801B6
      UCHAR_T get_StopBits () const;
      void set_StopBits (UCHAR_T value);

      //## Attribute: ReadPort%4108A27902EE
      ULONG_T get_ReadPort () const;
      void set_ReadPort (ULONG_T value);

      //## Attribute: WritePort%4108A2990000
      ULONG_T get_WritePort () const;
      void set_WritePort (ULONG_T value);

      //## Attribute: Host%4108A2AA0157
      STRING_T get_Host () const;
      void set_Host (STRING_T value);

      //## Attribute: SpsState%410F5A5D02EE
      UCHAR_T get_SpsState () const;
      void set_SpsState (UCHAR_T value);

      //## Attribute: SpsVersion%410F5A6B02BF
      UCHAR_T get_SpsVersion () const;
      void set_SpsVersion (UCHAR_T value);

      BOOL_T is_SerialCommunicationUsed () const;
      BOOL_T is_UDPCommunicationUsed () const;

  public:
    // Additional Public Declarations
      //## begin cPPCDevice%3FCF4E67000F.public preserve=yes
      //## end cPPCDevice%3FCF4E67000F.public

  protected:
    // Data Members for Class Attributes

      //## begin cPPCDevice::IscosNo%3FD45862038A.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _IscosNo;
      //## end cPPCDevice::IscosNo%3FD45862038A.attr

      //## begin cPPCDevice::BlockTimeout%410F55C0000F.attr preserve=no  public: ULONG_T {U} 1000
      ULONG_T _BlockTimeout;
      //## end cPPCDevice::BlockTimeout%410F55C0000F.attr

      //## begin cPPCDevice::BlockRetries%410F55E9004E.attr preserve=no  public: ULONG_T {U} 2
      ULONG_T _BlockRetries;
      //## end cPPCDevice::BlockRetries%410F55E9004E.attr

      //## begin cPPCDevice::BaudRate%3FD459580196.attr preserve=no  public: ULONG_T {U} 19200
      ULONG_T _BaudRate;
      //## end cPPCDevice::BaudRate%3FD459580196.attr

      //## begin cPPCDevice::Parity%3FD4595801A5.attr preserve=no  public: ParityTypes {U} None
      ParityTypes _Parity;
      //## end cPPCDevice::Parity%3FD4595801A5.attr

      //## begin cPPCDevice::Handshake%3FD4595801A6.attr preserve=no  public: HandshakeTypes {U} NoHandshake
      HandshakeTypes _Handshake;
      //## end cPPCDevice::Handshake%3FD4595801A6.attr

      //## begin cPPCDevice::CharLen%3FD4595801A7.attr preserve=no  public: UCHAR_T {U} 8
      UCHAR_T _CharLen;
      //## end cPPCDevice::CharLen%3FD4595801A7.attr

      //## begin cPPCDevice::StartBits%3FD4595801B5.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StartBits;
      //## end cPPCDevice::StartBits%3FD4595801B5.attr

      //## begin cPPCDevice::StopBits%3FD4595801B6.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StopBits;
      //## end cPPCDevice::StopBits%3FD4595801B6.attr

      //## begin cPPCDevice::ReadPort%4108A27902EE.attr preserve=no  public: ULONG_T {U} 19000
      ULONG_T _ReadPort;
      //## end cPPCDevice::ReadPort%4108A27902EE.attr

      //## begin cPPCDevice::WritePort%4108A2990000.attr preserve=no  public: ULONG_T {U} 19000
      ULONG_T _WritePort;
      //## end cPPCDevice::WritePort%4108A2990000.attr

      //## begin cPPCDevice::Host%4108A2AA0157.attr preserve=no  public: STRING_T {U} "localhost"
      STRING_T _Host;
      //## end cPPCDevice::Host%4108A2AA0157.attr

      //## begin cPPCDevice::SpsState%410F5A5D02EE.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _SpsState;
      //## end cPPCDevice::SpsState%410F5A5D02EE.attr

      //## begin cPPCDevice::SpsVersion%410F5A6B02BF.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _SpsVersion;
      //## end cPPCDevice::SpsVersion%410F5A6B02BF.attr

      //## begin cPPCDevice::VerifyBufSize%42C56C9A02AF.attr preserve=no  implementation: ULONG_T {U} 0x20000
      ULONG_T _VerifyBufSize;
      //## end cPPCDevice::VerifyBufSize%42C56C9A02AF.attr

      //## begin cPPCDevice::VerifyBuf%42C56CC6002E.attr preserve=no  implementation: USHORT_T * {U} NULL
      USHORT_T *_VerifyBuf;
      //## end cPPCDevice::VerifyBuf%42C56CC6002E.attr

      ULONG_T _BlockLength;
      BOOL_T _AdjustBlockLength;
      REQUEST_ID_TYPE _MasterRequestId;
      REQUEST_ID_TYPE _SlaveRequestId;
      bool _SafeCommunication;
      bool _SwapRequestId;
      ULONG_T _FuncBlockSize;

    // Data Members for Associations

      //## Association: Control::Device::PPCCom::<unnamed>%410898D100DA
      //## Role: cPPCDevice::Server%410898D200DA
      //## begin cPPCDevice::Server%410898D200DA.role preserve=no  public: cPPCServer {1 -> 0..1RFHN}
      cPPCServer *_Server;
      //## end cPPCDevice::Server%410898D200DA.role

      //## Association: Control::Device::PPCCom::<unnamed>%4108990700BB
      //## Role: cPPCDevice::Client%41089907034B
      //## begin cPPCDevice::Client%41089907034B.role preserve=no  public: cPPCClient {1 -> 0..1RFHN}
      cPPCClient *_Client;
      //## end cPPCDevice::Client%41089907034B.role

      //## Association: Control::Device::<unnamed>%3FD458DF004E
      //## Role: cPPCDevice::SerialChannel%3FD458DF02AF
      //## begin cPPCDevice::SerialChannel%3FD458DF02AF.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_SerialChannel;
      //## end cPPCDevice::SerialChannel%3FD458DF02AF.role

      //## Association: Control::Device::PPCCom::<unnamed>%4108A50C00BB
      //## Role: cPPCDevice::CSComm%4108A51000AB
      //## begin cPPCDevice::CSComm%4108A51000AB.role preserve=no  public: cCSComm { -> 0..1RFHN}
      cCSComm *_CSComm;
      //## end cPPCDevice::CSComm%4108A51000AB.role

      //## Association: Control::Device::<unnamed>%406101BD0167
      //## Role: cPPCDevice::Simulation%406101BD03C8
      //## begin cPPCDevice::Simulation%406101BD03C8.role preserve=no  public: cMemoryAddressedDevice { -> 0..1RFHN}
      cMemoryAddressedDevice *_Simulation;
      //## end cPPCDevice::Simulation%406101BD03C8.role

      //## Association: Control::Device::<unnamed>%3FD48C780128
      //## Role: cPPCDevice::RegisterCache%3FD48C7802DE
      //## begin cPPCDevice::RegisterCache%3FD48C7802DE.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_RegisterCache;
      //## end cPPCDevice::RegisterCache%3FD48C7802DE.role

      //## Association: Control::Device::<unnamed>%3FD48CA502BF
      //## Role: cPPCDevice::LogicCache%3FD48CA602DE
      //## begin cPPCDevice::LogicCache%3FD48CA602DE.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_LogicCache;
      //## end cPPCDevice::LogicCache%3FD48CA602DE.role

    // Additional Protected Declarations
      //## begin cPPCDevice%3FCF4E67000F.protected preserve=yes
      //## end cPPCDevice%3FCF4E67000F.protected

  private:
    // Additional Private Declarations
      //## begin cPPCDevice%3FCF4E67000F.private preserve=yes
      //## end cPPCDevice%3FCF4E67000F.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: I60Com%1070550139
      LONG_T I60Com (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout);

      //## Operation: I60Request%1070550140
      LONG_T I60Request (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout);

      //## Operation: Command%1075189792
      virtual UCHAR_T Command (CONST_STRING_T buf_spec, BOOL_T read);

      //## Operation: WriteBlock%1070550141
      LONG_T WriteBlock (BUF_T block, ULONG_T block_len);

      //## Operation: ReadBlock%1070550142
      LONG_T ReadBlock (BUF_T buf, ULONG_T buf_size, ULONG_T timeout);

      //## Operation: PpcCom%1070550143
      LONG_T PpcCom (UCHAR_T iscos_no, void *outbuf, ULONG_T outbuf_len, void *inbuf, ULONG_T inbuf_size, ULONG_T timeout);

      //## Operation: PpcError%1070550144
      INT_T PpcError (UCHAR_T *block, ULONG_T block_len);

      //## Operation: SupplyData%1070550145
      INT_T SupplyData (UCHAR_T iscos_no, void *func, ULONG_T func_len, void *data, ULONG_T data_len, ULONG_T timeout);

      //## Operation: RequestData%1070550146
      INT_T RequestData (UCHAR_T iscos_no, void *func, ULONG_T func_len, void *databuf, ULONG_T data_buf_size, ULONG_T timeout);

      //## Operation: SendErrorBlock%1070550147
      LONG_T SendErrorBlock (USHORT_T err_code, ULONG_T timeout);

      //## Operation: ReadBit%1086172577
      void ReadBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: WriteBit%1086172578
      void WriteBit (ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);

      //## Operation: SendBlock%1091085016
      LONG_T SendBlock (BUF_T buf, ULONG_T len);

      //## Operation: FlushInput%1091085017
      void FlushInput ();

      //## Operation: BlockDebug%1091085019
      void BlockDebug (BUF_T block, ULONG_T block_len, BOOL_T read);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: VerifyBufSize%42C56C9A02AF
      ULONG_T get_VerifyBufSize () const;
      void set_VerifyBufSize (ULONG_T value);

      //## Attribute: VerifyBuf%42C56CC6002E
      USHORT_T * get_VerifyBuf () const;
      void set_VerifyBuf (USHORT_T * value);

    // Data Members for Class Attributes

      //## Attribute: ErrCount%411B93670157
      //## begin cPPCDevice::ErrCount%411B93670157.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ErrCount;
      //## end cPPCDevice::ErrCount%411B93670157.attr

    // Additional Implementation Declarations
      //## begin cPPCDevice%3FCF4E67000F.implementation preserve=yes
      //## end cPPCDevice%3FCF4E67000F.implementation
      void AdjustBlockLength (USHORT_T block_length);
      REQUEST_ID_TYPE NextRequestId ();
      LONG_T ExpectedResponseLength (FUNCBLOCK *func_block);
};

//## begin cPPCDevice%3FCF4E67000F.postscript preserve=yes
//## end cPPCDevice%3FCF4E67000F.postscript

// Class cPPCDevice 

//## begin module%3FCF4E67000F.epilog preserve=yes
//## end module%3FCF4E67000F.epilog


#endif
