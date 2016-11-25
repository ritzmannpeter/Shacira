//## begin module%371221790390.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%371221790390.cm

//## begin module%371221790390.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%371221790390.cp

//## Module: cSerialChannel%371221790390; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialChannel.h

#ifndef cSerialChannel_h
#define cSerialChannel_h 1

//## begin module%371221790390.includes preserve=yes
//## end module%371221790390.includes

// cStaticObject
#include "System/Objects/cStaticObject.h"

class __DLL_EXPORT__ cCharRingBuffer;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%371221790390.additionalDeclarations preserve=yes

typedef enum {UndefinedParity=-1,Even, Odd, Mark, Space, None} ParityTypes;
typedef enum {UndefinedHandshake=-1,NoHandshake=0,InputSW=0x01,InputHW=0x02,
              OutputSW=0x04,OutputHW=0x08} HandshakeTypes;

typedef struct {
   unsigned long errors;
   unsigned long act_state;
   unsigned long set_state;
   unsigned long in_queue_size;
   unsigned long out_queue_size;
}  COM_STATE_T;

#define ERROR_RESET           0
#define UNCONDITIONAL_RESET   1
#define TARGET_RESET          2
#define INIT_DEVICE           3

// error states
#define ERROR_BREAK           0x00000001   // The hardware detected a break condition.
#define ERROR_DNS             0x00000002   // Windows 95/98/Me: A parallel device is not selected.
#define ERROR_FRAME           0x00000004   // The hardware detected a framing error.
#define ERROR_IOE             0x00000008   // An I/O error occurred during communications with the device.
#define ERROR_MODE            0x00000010   // The requested mode is not supported, or the hFile parameter is invalid. If this value is specified, it is the only valid error.
#define ERROR_OOP             0x00000020   // Windows 95/98/Me: A parallel device signaled that it is out of paper.
#define ERROR_OVERRUN         0x00000040   // A character-buffer overrun has occurred. The next character is lost.
#define ERROR_PTO             0x00000080   // Windows 95/98/Me: A time-out occurred on a parallel device.
#define ERROR_RXOVER          0x00000100   // An input buffer overflow has occurred. There is either no room in the input buffer, or a character was received after the end-of-file (EOF) character.
#define ERROR_RXPARITY        0x00000200   // The hardware detected a parity error.
#define ERROR_TXFULL          0x00000400   // The application tried to transmit a character, but the output buffer was full.

// communication actual states
#define CTS_HOLD              0x00000001
#define DSR_HOLD              0x00000002
#define RLSD_HOLD             0x00000004
#define XOFF_HOLD             0x00000008
#define XOFF_SENT             0x00000010
#define EOF_REACHED           0x00000020
#define TXIM                  0x00000040

// communication setting states
#define MODE_BINARY              0x00000001  // binary mode, no EOF check
#define MODE_PARITY              0x00000002  // enable parity checking
#define MODE_OUTXCTSFLOW         0x00000004  // CTS output flow control
#define MODE_OUTXDSRFLOW         0x00000008  // DSR output flow control
#define MODE_DTRCONTROL          0x00000030  // DTR flow control type
#define MODE_DSRSENSITIVITY      0x00000040  // DSR sensitivity
#define MODE_TXCONTINUEONXOFF    0x00000080  // XOFF continues Tx
#define MODE_OUTX                0x00000100  // XON/XOFF out flow control
#define MODE_INX                 0x00000200  // XON/XOFF in flow control
#define MODE_ERRORCHAR           0x00000400  // enable error replacement
#define MODE_NULL                0x00000800  // enable null stripping
#define MODE_RTSCONTROL          0x00003000  // RTS flow control
#define MODE_ABORTONERROR        0x00004000  // abort on error

#define CHANNEL_OUTPUT  1
#define CHANNEL_INPUT   2

#ifndef EOF
#define EOF          (-1)
#endif
#define CTRL_B       0x02
#define STX          0x02
#define ETX          0x03
#define ENQ          0x05
#define EOT          0x04
#define ACK          0x06
#define NAK          0x15
#define ETB          0x17
#define CAN          0x18
#define CR           0x0D
#define LF           0x0A
#define SPACE        0x20


//## end module%371221790390.additionalDeclarations


//## begin cSerialChannel%371221790390.preface preserve=yes
//## end cSerialChannel%371221790390.preface

//## Class: cSerialChannel%371221790390
//	cSerialChannel describes all objects that behave like a
//	serial channel with respect to input, output, timeout
//	facilities and buffering mechanisms. The class abstracts
//	from special serial channels like standard PC serial
//	communication lines, tty's and other serial devices.
//	This clas is a base class with abstract methods and
//	cannot be instantiated directly. The concrete serial
//	channel classes must derive from cSerialChannel.
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A6C7BA3011D;cConfigurationObject { -> F}
//## Uses: <unnamed>%3CE1068C02FB;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3DDE07DB00FF;cConvUtils { -> F}

class __DLL_EXPORT__ cSerialChannel : public cStaticObject  //## Inherits: <unnamed>%3DDDE199017E
{
  //## begin cSerialChannel%371221790390.initialDeclarations preserve=yes
public:
  //## end cSerialChannel%371221790390.initialDeclarations

    //## Constructors (generated)
      cSerialChannel();

      cSerialChannel(const cSerialChannel &right);

    //## Constructors (specified)
      //## Operation: cSerialChannel%981360504
      cSerialChannel (cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cSerialChannel();


    //## Other Operations (specified)
      //## Operation: GetBaudRate%980152408
      virtual ULONG_T GetBaudRate () = 0;

      //## Operation: SetBaudRate%980152409
      virtual void SetBaudRate (ULONG_T baud_rate) = 0;

      //## Operation: GetStopBits%980152410
      virtual UCHAR_T GetStopBits () = 0;

      //## Operation: SetStopBits%980152411
      virtual void SetStopBits (UCHAR_T stop_bits) = 0;

      //## Operation: GetStartBits%980152412
      virtual UCHAR_T GetStartBits () = 0;

      //## Operation: SetStartBits%980152413
      virtual void SetStartBits (UCHAR_T start_bits) = 0;

      //## Operation: GetCharLen%980152414
      virtual UCHAR_T GetCharLen () = 0;

      //## Operation: SetCharLen%980152415
      virtual void SetCharLen (UCHAR_T data_len) = 0;

      //## Operation: GetParity%980152416
      virtual ParityTypes GetParity () = 0;

      //## Operation: SetParity%980152417
      virtual void SetParity (ParityTypes parity) = 0;

      //## Operation: GetHandshake%980239686
      virtual HandshakeTypes GetHandshake () = 0;

      //## Operation: SetHandshake%980239687
      virtual void SetHandshake (HandshakeTypes handshake) = 0;

      //## Operation: GetTimeout%980152418
      virtual ULONG_T GetTimeout () = 0;

      //## Operation: SetTimeout%980152419
      virtual void SetTimeout (ULONG_T timeout) = 0;

      //## Operation: GetState%1014806631
      virtual void GetState (COM_STATE_T *state) = 0;

      //## Operation: Open%980168053
      virtual void Open () = 0;

      //## Operation: Close%980168054
      virtual void Close () = 0;

      //## Operation: Reset%1014806627
      virtual void Reset (INT_T type) = 0;

      //## Operation: Read%925470188
      virtual LONG_T Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout) = 0;

      //## Operation: Write%925470189
      virtual LONG_T Write (UCHAR_T *buffer, ULONG_T amount) = 0;

      //## Operation: FlushInput%934299542
      virtual void FlushInput () = 0;

      //## Operation: FlushOutput%934299543
      virtual void FlushOutput () = 0;

      //## Operation: SendChar%985437687
      BOOL_T SendChar (UCHAR_T c);

      //## Operation: GetChar%985437688
      INT_T GetChar (ULONG_T timeout);

      //## Operation: ParityType%1027605559
      static ParityTypes ParityType (CONST_STRING_T type_name);

      //## Operation: HandshakeType%1071171006
      static HandshakeTypes HandshakeType (CONST_STRING_T type_name);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ChannelType%3712224F01E0
      //	Channel type identifies the type of a channel. Channel
      //	types identify the type of device access.
      STRING_T get_ChannelType () const;

      //## Attribute: Verbose%3B80D5C903E1
      BOOL_T get_Verbose () const;
      void set_Verbose (BOOL_T value);

      //## Attribute: User%3CE0FBD602D0
      //	The name of the channel user. In general this is the
      //	name of a driver that uses the channel.
      STRING_T get_User () const;
      void set_User (STRING_T value);

      //## Attribute: IsBus%3E2C3E4600FF
      BOOL_T get_IsBus () const;
      void set_IsBus (BOOL_T value);

      //## Attribute: IsOpen%3E2C47FF018A
      BOOL_T get_IsOpen () const;
      void set_IsOpen (BOOL_T value);

    // Data Members for Class Attributes

      //## Attribute: BusMutex%3E2C3AEE0375
      //## begin cSerialChannel::BusMutex%3E2C3AEE0375.attr preserve=no  public: cMutexSem {U} 
      cMutexSem _BusMutex;
      //## end cSerialChannel::BusMutex%3E2C3AEE0375.attr

  public:
    // Additional Public Declarations
      //## begin cSerialChannel%371221790390.public preserve=yes
      //## end cSerialChannel%371221790390.public

  protected:

    //## Other Operations (specified)
      //## Operation: PrintBuf%998299190
      void PrintBuf (CONST_STRING_T buf, ULONG_T len, INT_T direction);

      //## Operation: SetDirection%1043598188
      void SetDirection (INT_T direction);

    // Data Members for Class Attributes

      //## begin cSerialChannel::ChannelType%3712224F01E0.attr preserve=no  public: STRING_T {U} 
      STRING_T _ChannelType;
      //## end cSerialChannel::ChannelType%3712224F01E0.attr

      //## begin cSerialChannel::Verbose%3B80D5C903E1.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Verbose;
      //## end cSerialChannel::Verbose%3B80D5C903E1.attr

      //## begin cSerialChannel::User%3CE0FBD602D0.attr preserve=no  public: STRING_T {U} "unknown"
      STRING_T _User;
      //## end cSerialChannel::User%3CE0FBD602D0.attr

      //## begin cSerialChannel::IsBus%3E2C3E4600FF.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsBus;
      //## end cSerialChannel::IsBus%3E2C3E4600FF.attr

      //## begin cSerialChannel::IsOpen%3E2C47FF018A.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsOpen;
      //## end cSerialChannel::IsOpen%3E2C47FF018A.attr

      //## Attribute: BaudRate%3C7CBD2603CA
      //## begin cSerialChannel::BaudRate%3C7CBD2603CA.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _BaudRate;
      //## end cSerialChannel::BaudRate%3C7CBD2603CA.attr

      //## Attribute: Parity%3C7CBD45007B
      //## begin cSerialChannel::Parity%3C7CBD45007B.attr preserve=no  protected: ParityTypes {U} None
      ParityTypes _Parity;
      //## end cSerialChannel::Parity%3C7CBD45007B.attr

      //## Attribute: StopBits%3C7CBD86036E
      //## begin cSerialChannel::StopBits%3C7CBD86036E.attr preserve=no  protected: UCHAR_T {U} 0
      UCHAR_T _StopBits;
      //## end cSerialChannel::StopBits%3C7CBD86036E.attr

      //## Attribute: StartBits%3C7CBD9B025F
      //## begin cSerialChannel::StartBits%3C7CBD9B025F.attr preserve=no  protected: UCHAR_T {U} 0
      UCHAR_T _StartBits;
      //## end cSerialChannel::StartBits%3C7CBD9B025F.attr

      //## Attribute: CharLen%3C7CBDAF03E5
      //## begin cSerialChannel::CharLen%3C7CBDAF03E5.attr preserve=no  protected: UCHAR_T {U} 0
      UCHAR_T _CharLen;
      //## end cSerialChannel::CharLen%3C7CBDAF03E5.attr

      //## Attribute: Handshake%3C7CBDBC01C7
      //## begin cSerialChannel::Handshake%3C7CBDBC01C7.attr preserve=no  protected: HandshakeTypes {U} NoHandshake
      HandshakeTypes _Handshake;
      //## end cSerialChannel::Handshake%3C7CBDBC01C7.attr

      //## Attribute: ErrorState%3C7CCCD5030F
      //## begin cSerialChannel::ErrorState%3C7CCCD5030F.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _ErrorState;
      //## end cSerialChannel::ErrorState%3C7CCCD5030F.attr

    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3CEA8D0D0275
      //## Role: cSerialChannel::Buffer%3CEA8D0E029E
      //## begin cSerialChannel::Buffer%3CEA8D0E029E.role preserve=no  public: cCharRingBuffer { -> 0..1RFHN}
      cCharRingBuffer *_Buffer;
      //## end cSerialChannel::Buffer%3CEA8D0E029E.role

    // Additional Protected Declarations
      //## begin cSerialChannel%371221790390.protected preserve=yes
      //## end cSerialChannel%371221790390.protected

  private:
    // Additional Private Declarations
      //## begin cSerialChannel%371221790390.private preserve=yes
      //## end cSerialChannel%371221790390.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Format%1037956858
      STRING_T Format (CONST_STRING_T buf, ULONG_T len);

    // Data Members for Class Attributes

      //## Attribute: ActDirection%3DDE1A67019C
      //## begin cSerialChannel::ActDirection%3DDE1A67019C.attr preserve=no  implementation: INT_T {U} CHANNEL_INPUT
      INT_T _ActDirection;
      //## end cSerialChannel::ActDirection%3DDE1A67019C.attr

      //## Attribute: Binary%3E34038A032D
      //## begin cSerialChannel::Binary%3E34038A032D.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Binary;
      //## end cSerialChannel::Binary%3E34038A032D.attr

    // Additional Implementation Declarations
      //## begin cSerialChannel%371221790390.implementation preserve=yes
      //## end cSerialChannel%371221790390.implementation

};

//## begin cSerialChannel%371221790390.postscript preserve=yes
//## end cSerialChannel%371221790390.postscript

// Class cSerialChannel 

//## begin module%371221790390.epilog preserve=yes
//## end module%371221790390.epilog


#endif
