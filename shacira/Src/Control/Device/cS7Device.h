//## begin module%401616F601D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%401616F601D4.cm

//## begin module%401616F601D4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%401616F601D4.cp

//## Module: cS7Device%401616F601D4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cS7Device.h

#ifndef cS7Device_h
#define cS7Device_h 1

//## begin module%401616F601D4.includes preserve=yes
//## end module%401616F601D4.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cBlockCache;
class __DLL_EXPORT__ cCache;
class __DLL_EXPORT__ cS7Operator;
class __DLL_EXPORT__ cMemoryAddressedDevice;

//## begin module%401616F601D4.additionalDeclarations preserve=yes
//## end module%401616F601D4.additionalDeclarations


//## begin cS7Device%401616F601D4.preface preserve=yes
//## end cS7Device%401616F601D4.preface

//## Class: cS7Device%401616F601D4
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40161BA5007D;cBlockCache { -> F}
//## Uses: <unnamed>%401635570290;cCacheControl { -> F}
//## Uses: <unnamed>%40167C59003E;cObjectLock { -> F}
//## Uses: <unnamed>%40A20E6701F4;cS7Operator { -> F}

class __DLL_EXPORT__ cS7Device : public cDevice  //## Inherits: <unnamed>%4016170E001F
{
  //## begin cS7Device%401616F601D4.initialDeclarations preserve=yes
public:
  //## end cS7Device%401616F601D4.initialDeclarations

    //## Constructors (generated)
      cS7Device();

      cS7Device(const cS7Device &right);

    //## Constructors (specified)
      //## Operation: cS7Device%1075189779
      cS7Device (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cS7Device();


    //## Other Operations (specified)
      //## Operation: Start%1075189780
      virtual void Start ();

      //## Operation: Stop%1075189781
      virtual void Stop ();

      //## Operation: Cache%1075189783
      virtual void Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Buffer%1075189784
      virtual void Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements = 1);

      //## Operation: Read%1075189785
      virtual void Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Write%1075189786
      virtual void Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);

      //## Operation: UseBuffer%1075647703
      void UseBuffer (CONST_STRING_T buf_spec);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SPSAddress%401617530119
      ULONG_T get_SPSAddress () const;
      void set_SPSAddress (ULONG_T value);

      //## Attribute: ClientAddress%401617F20000
      ULONG_T get_ClientAddress () const;
      void set_ClientAddress (ULONG_T value);

      //## Attribute: SPSType%40161CF1030D
      ULONG_T get_SPSType () const;
      void set_SPSType (ULONG_T value);

      //## Attribute: Com%40161C4F00AB
      UCHAR_T get_Com () const;
      void set_Com (UCHAR_T value);

      //## Attribute: BusBaudRate%402B88F40280
      ULONG_T get_BusBaudRate () const;
      void set_BusBaudRate (ULONG_T value);

      //## Attribute: BaudRate%401617530128
      ULONG_T get_BaudRate () const;
      void set_BaudRate (ULONG_T value);

      //## Attribute: Parity%401617530129
      ParityTypes get_Parity () const;
      void set_Parity (ParityTypes value);

      //## Attribute: Handshake%40161753012A
      HandshakeTypes get_Handshake () const;
      void set_Handshake (HandshakeTypes value);

      //## Attribute: CharLen%401617530138
      UCHAR_T get_CharLen () const;
      void set_CharLen (UCHAR_T value);

      //## Attribute: StartBits%401617530139
      UCHAR_T get_StartBits () const;
      void set_StartBits (UCHAR_T value);

      //## Attribute: StopBits%40161753013A
      UCHAR_T get_StopBits () const;
      void set_StopBits (UCHAR_T value);

      //## Attribute: TCPIPAddress%4B4C2C370275
      STRING_T get_TCPIPAddress () const;
      void set_TCPIPAddress (STRING_T value);

      //## Attribute: UsedCommChannel%4B4C2CBB013E
      STRING_T get_UsedCommChannel () const;
      void set_UsedCommChannel (STRING_T value);

      //## Attribute: TCPIPCommunication%4B4C2CF4025C
      BOOL_T get_TCPIPCommunication () const;
      void set_TCPIPCommunication (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cS7Device%401616F601D4.public preserve=yes
      //## end cS7Device%401616F601D4.public

  protected:
    // Data Members for Class Attributes

      //## begin cS7Device::SPSAddress%401617530119.attr preserve=no  public: ULONG_T {U} 2
      ULONG_T _SPSAddress;
      //## end cS7Device::SPSAddress%401617530119.attr

      //## begin cS7Device::ClientAddress%401617F20000.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _ClientAddress;
      //## end cS7Device::ClientAddress%401617F20000.attr

      //## begin cS7Device::SPSType%40161CF1030D.attr preserve=no  public: ULONG_T {U} 300
      ULONG_T _SPSType;
      //## end cS7Device::SPSType%40161CF1030D.attr

      //## begin cS7Device::Com%40161C4F00AB.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _Com;
      //## end cS7Device::Com%40161C4F00AB.attr

      //## begin cS7Device::BusBaudRate%402B88F40280.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _BusBaudRate;
      //## end cS7Device::BusBaudRate%402B88F40280.attr

      //## begin cS7Device::BaudRate%401617530128.attr preserve=no  public: ULONG_T {U} 19200
      ULONG_T _BaudRate;
      //## end cS7Device::BaudRate%401617530128.attr

      //## begin cS7Device::Parity%401617530129.attr preserve=no  public: ParityTypes {U} None
      ParityTypes _Parity;
      //## end cS7Device::Parity%401617530129.attr

      //## begin cS7Device::Handshake%40161753012A.attr preserve=no  public: HandshakeTypes {U} NoHandshake
      HandshakeTypes _Handshake;
      //## end cS7Device::Handshake%40161753012A.attr

      //## begin cS7Device::CharLen%401617530138.attr preserve=no  public: UCHAR_T {U} 8
      UCHAR_T _CharLen;
      //## end cS7Device::CharLen%401617530138.attr

      //## begin cS7Device::StartBits%401617530139.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StartBits;
      //## end cS7Device::StartBits%401617530139.attr

      //## begin cS7Device::StopBits%40161753013A.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StopBits;
      //## end cS7Device::StopBits%40161753013A.attr

      //## begin cS7Device::TCPIPAddress%4B4C2C370275.attr preserve=no  public: STRING_T {U} 
      STRING_T _TCPIPAddress;
      //## end cS7Device::TCPIPAddress%4B4C2C370275.attr

      //## begin cS7Device::UsedCommChannel%4B4C2CBB013E.attr preserve=no  public: STRING_T {U} 
      STRING_T _UsedCommChannel;
      //## end cS7Device::UsedCommChannel%4B4C2CBB013E.attr

      //## begin cS7Device::TCPIPCommunication%4B4C2CF4025C.attr preserve=no  public: BOOL_T {U} 
      BOOL_T _TCPIPCommunication;
      //## end cS7Device::TCPIPCommunication%4B4C2CF4025C.attr

    // Data Members for Associations

      //## Association: Control::Device::<unnamed>%402B845B0186
      //## Role: cS7Device::Simulation%402B845C02EE
      //## begin cS7Device::Simulation%402B845C02EE.role preserve=no  public: cMemoryAddressedDevice { -> 0..1RFHN}
      cMemoryAddressedDevice *_Simulation;
      //## end cS7Device::Simulation%402B845C02EE.role

      //## Association: Control::Device::<unnamed>%40161B0700DA
      //## Role: cS7Device::TimerCache%40161B08000F
      //## begin cS7Device::TimerCache%40161B08000F.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_TimerCache;
      //## end cS7Device::TimerCache%40161B08000F.role

      //## Association: Control::Device::<unnamed>%40161B46032C
      //## Role: cS7Device::InputCache%40161B480000
      //## begin cS7Device::InputCache%40161B480000.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_InputCache;
      //## end cS7Device::InputCache%40161B480000.role

      //## Association: Control::Device::<unnamed>%401637E2031C
      //## Role: cS7Device::MerkerCache%401637E5006D
      //## begin cS7Device::MerkerCache%401637E5006D.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_MerkerCache;
      //## end cS7Device::MerkerCache%401637E5006D.role

      //## Association: Control::Device::<unnamed>%401687110222
      //## Role: cS7Device::CounterCache%40168712029F
      //## begin cS7Device::CounterCache%40168712029F.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_CounterCache;
      //## end cS7Device::CounterCache%40168712029F.role

      //## Association: Control::Device::<unnamed>%401CFF23002E
      //## Role: cS7Device::DBCaches%401CFF250109
      //## Qualifier: name%401CFF54001F; STRING_T
      //## begin cS7Device::DBCaches%401CFF250109.role preserve=no  public: cCache { -> 0..nRFHN}
      std::map<STRING_T, cCache*> _DBCaches;
      //## end cS7Device::DBCaches%401CFF250109.role

      //## Association: Control::Device::<unnamed>%4120A2880186
      //## Role: cS7Device::OutputCache%4120A2890280
      //## begin cS7Device::OutputCache%4120A2890280.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_OutputCache;
      //## end cS7Device::OutputCache%4120A2890280.role

    // Additional Protected Declarations
      //## begin cS7Device%401616F601D4.protected preserve=yes
      //## end cS7Device%401616F601D4.protected

  private:
    // Additional Private Declarations
      //## begin cS7Device%401616F601D4.private preserve=yes
      //## end cS7Device%401616F601D4.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Info%1075637926
      MEMORY_INFO * Info (CONST_STRING_T buf_spec);

      //## Operation: S7Load%1075189788
      INT_T S7Load (MEMORY_INFO *info, void *buf, ULONG_T address, ULONG_T no, ULONG_T timeout);

      //## Operation: S7Save%1075189789
      INT_T S7Save (MEMORY_INFO *info, void *buf, ULONG_T buf_size, ULONG_T address, ULONG_T no, ULONG_T timeout);

      //## Operation: S7SetBit%1075637927
      INT_T S7SetBit (MEMORY_INFO *info, ULONG_T address, USHORT_T bit_no, ULONG_T timeout);

      //## Operation: S7ResetBit%1075189791
      INT_T S7ResetBit (MEMORY_INFO *info, ULONG_T address, USHORT_T bit_no, ULONG_T timeout);

    // Data Members for Class Attributes

      //## Attribute: Handle%401619F902EE
      //## begin cS7Device::Handle%401619F902EE.attr preserve=no  implementation: long {U} 0
      long _Handle;
      //## end cS7Device::Handle%401619F902EE.attr

    // Additional Implementation Declarations
      //## begin cS7Device%401616F601D4.implementation preserve=yes
      //## end cS7Device%401616F601D4.implementation

};

//## begin cS7Device%401616F601D4.postscript preserve=yes
//## end cS7Device%401616F601D4.postscript

// Class cS7Device 

//## begin module%401616F601D4.epilog preserve=yes
//## end module%401616F601D4.epilog


#endif
