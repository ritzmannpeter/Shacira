//## begin module%3A6C140C0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A6C140C0356.cm

//## begin module%3A6C140C0356.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A6C140C0356.cp

//## Module: cSocketChannel%3A6C140C0356; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSocketChannel.h

#ifndef cSocketChannel_h
#define cSocketChannel_h 1

//## begin module%3A6C140C0356.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3A6C140C0356.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cWTNodes
#include "Control/SerialChannel/cWTNodes.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cCharReceiver;
class __DLL_EXPORT__ cStandardChannel;
class __DLL_EXPORT__ cWTNode;
class __DLL_EXPORT__ cTCPReceiver;

//## begin module%3A6C140C0356.additionalDeclarations preserve=yes

typedef struct _com_error
{
	union
	{
		short int error_flags;
		struct
		{
			short int f_data      : 1;    //Set when data available
			short int f_net       : 2;    // 1 when netware error occours
			                              // 2 unresolved command
			                              // 3 Reset Box after overrun or time out
			short int f_com       : 1;    //Set when COM port error detected
			short int f_break     : 1;    //Reflect the break flag
			short int f_cts_time  : 1;    //Time out while waiting on CTS
			short int f_dsr_time  : 1;    //Time out while waiting on DSR
			short int f_rlsd_time : 1;    //Time out while waiting on RLSD (CD)
			short int f_overrun   : 1;    //Overrun error
			short int f_parity    : 1;    //Parity error
			short int f_frame     : 1;    //Framing error
			short int f_status    : 1;    //Port LOCK info available (nur IPX-API)
			short int no_use_1    : 1;    //not used
			short int no_use_2    : 1;    //not used
			short int f_rx_over   : 1;    //Ring buffer overrun after handshake
			short int no_use_3    : 1;    //not used
		} cerr_flags;
	};
} COM_ERROR;

typedef struct _com_stat               //States of com-port read/write
{
	union
	{
		short int com_flags;
		struct
		{
			short int dsr_hold    : 1;    //DSR line - LowByte
			short int cts_hold    : 1;    //CTS line |
			short int ri_hold     : 1;    //RI line | is set with every
			short int rlsd_hold   : 1;    //RLSD line | received packet
			short int dtr_hold    : 1;    //DTR line |
			short int rts_hold    : 1;    //RTS line |
			short int x_receive   : 1;    //XOFF received |
			short int x_send      : 1;    //XOFF was send -int
			short int dummy       : 2;    //space not used - HighByte
			short int send_xoff   : 1;    //Send XOFF asynchron |
			short int flush_rd    : 1;    //Flush seriell input buffer |
			short int flush_wr    : 1;    //Flush seriell output buffer |
			short int set_rts_dtr : 1;    //set RTS to rts_hold and |
			                              // DTR to dtr_hold |
			short int set_break   : 1;    //Independent setting break mode |
			short int clear_break : 1;    //Independent clearing break mode -};
		} ccom_flags;
	};
   short int cbInQue;                  //Receive byte count of COM ring buffer
	short int cbOutQue;                 //Transmit byte count of COM ring buffer
} COM_STAT;


typedef struct _box_cntrl
{
	struct
	{
		unsigned char baud : 5;          // Baud rate for channel
		                                 // Com-Server (max. 1Port) Com-Server mit 1-4 Ports
		                                 // Table 1              Table 2
		                                 // 0 = 57600  6 = 2400  11 = 230,4k   5 = 4800
		                                 // 1 = 38400  7 = 1200  14 = 153,6k   6 = 2400
		                                 // 2 = 19200  8 = 600   15 = 115,2k   7 = 1200
		                                 // 20= 14400  9 = 300    0 = 57600    8 = 600
		                                 // 3 = 9600              1 = 38400    9 = 300
		                                 // 5 = 4800              2 = 19200   10 = 150
		                                 //                       3 = 9600    12 = 75
      		                           //                       4 = 7200    13 = 50
		                                 // (nur COM-Server mit Baud Table 2)
		unsigned char fifo_aktiv : 1;    // FIFO enable
		                                 // 0 = FIFO disabled
		                                 // 1 = FIFO enabled
		unsigned char fifo : 2;          // Send / Receive FIFO Trigger:
		                                 // 0 = 8 / 8
		                                 // 1 = 16 / 16
		                                 // 2 = 32 / 56
	} cbaud_fifo;	                     // 3 = disable
	                                    //
	unsigned char bits;                 // 00xx.xxxx Data-,Stop-Bits, Parity
	                                    //
	                                    // 00 = 5 data bits
	                                    // 01 = 6 data bits
	                                    // 10 = 7 data bits
	                                    // 11 = 8 data bits
	                                    // 0 = 1
	                                    // 1 = 1½, 2 stop bits
	                                    // 1 = parity enable
	                                    // 0 = odd, 1 = even paritiy
	                                    // 1 = stick parity
	short int RLS_time_out;             // Timer before f_rlsd_time will be set
	short int CTS_time_out;             // Timer before f_cts_time will be set
	short int DSR_time_out;             // Timer before f_dsr_time will be set
	char XONChar;                       // Char excepted as XON
	char XOFFChar;                      // Char excepted as XOFF
	short int XONLim;                   // Limit in ring buffer before clearing handshake stop
	short int XOFFLim;                  // Limit in ring buffer before setting handshake stop
	char PEChar;                        // Replace this char if parity error
	struct
	{
		unsigned char save_command : 4;  //Save COM Configuation
		                                 //0 = no save
		                                 //1 = save without EEPROM Update
		                                 //2 = save with EEPROM Update
		unsigned char clear_error : 1;   //1 = clear error in display / lamps
		unsigned char free_cmd : 3;      //not used
	} ccommands;
	short int UserTime;                 //AUTO_LOCK_OUT time defined by user (only IPX-API)
	union
	{
		short int f_flags;
		struct
		{
			short int f_rts_disable : 1;  //RTS will not change at LOCK/UNLOCK
			short int f_dtr_disable : 1;  //DTR will not change at LOCK/UNLOCK
			short int f_outx        : 1;  //Enable software handshake while sending
			short int f_inx         : 1;  //Enable software handshake while receiving
			short int f_outx_cts    : 1;  //Enable hardware handshake on CTS
			short int f_outx_dsr    : 1;  //Enable hardware handshake on DSR
			short int f_inx_dtr     : 1;  //Enable hardware handshake on DTR
			short int f_inx_rts     : 1;  //Enable hardware handshake on RTS
			short int f_parity      : 1;  //Enable parity check & error report
			short int f_pechar      : 1;  //Enable replacement of received char
			short int f_inxfilter   : 1;  //Enable XON/XOFF Filter while receiving
			short int f_outxfilter  : 1;  //Enable XON/XOFF Filter while sending
			short int f_rts_default : 1;  //1 = While RTS is not used, RTS is activ
			short int f_dtr_default : 1;  //1 = While DTR is not used, DTR is activ
			short int f_user_time   : 1;  //Enable user defined time out
			short int no_use_4      : 1;  //not used
		} cf_flags;
	};
} BOX_CNTRL;


#pragma pack(1)
typedef struct _rem_box_cntrl
{
	char zero_1;
	COM_ERROR _ce;
	COM_STAT _cs;
	BOX_CNTRL _bc;
	char zero_2;
} REM_BOX_CNTRL;
#pragma pack()

//## end module%3A6C140C0356.additionalDeclarations


//## begin cSocketChannel%3A6C140C0356.preface preserve=yes
//## end cSocketChannel%3A6C140C0356.preface

//## Class: cSocketChannel%3A6C140C0356
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CABFC2200DF;cStandardChannel { -> F}
//## Uses: <unnamed>%3CAC01B702A6;cConfigurationObject { -> F}
//## Uses: <unnamed>%3CAC8B2B029B;cTCPReceiver { -> F}
//## Uses: <unnamed>%3CBBD65202AB;cWTNodes { -> }

class __DLL_EXPORT__ cSocketChannel : public cSerialChannel  //## Inherits: <unnamed>%3CAAC6C402CE
{
  //## begin cSocketChannel%3A6C140C0356.initialDeclarations preserve=yes
public:
  //## end cSocketChannel%3A6C140C0356.initialDeclarations

    //## Constructors (generated)
      cSocketChannel();

      cSocketChannel(const cSocketChannel &right);

    //## Constructors (specified)
      //## Operation: cSocketChannel%1009995342
      cSocketChannel (cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cSocketChannel();


    //## Other Operations (specified)
      //## Operation: GetBaudRate%1009995343
      virtual ULONG_T GetBaudRate ();

      //## Operation: SetBaudRate%1009995344
      virtual void SetBaudRate (ULONG_T baud_rate);

      //## Operation: GetStopBits%1009995345
      virtual UCHAR_T GetStopBits ();

      //## Operation: SetStopBits%1009995346
      virtual void SetStopBits (UCHAR_T stop_bits);

      //## Operation: GetStartBits%1009995347
      virtual UCHAR_T GetStartBits ();

      //## Operation: SetStartBits%1009995348
      virtual void SetStartBits (UCHAR_T start_bits);

      //## Operation: GetCharLen%1009995349
      virtual UCHAR_T GetCharLen ();

      //## Operation: SetCharLen%1009995350
      virtual void SetCharLen (UCHAR_T data_len);

      //## Operation: GetParity%1009995351
      virtual ParityTypes GetParity ();

      //## Operation: SetParity%1009995352
      virtual void SetParity (ParityTypes parity);

      //## Operation: GetHandshake%1009995353
      virtual HandshakeTypes GetHandshake ();

      //## Operation: SetHandshake%1009995354
      virtual void SetHandshake (HandshakeTypes handshake);

      //## Operation: GetTimeout%1009995355
      virtual ULONG_T GetTimeout ();

      //## Operation: SetTimeout%1009995356
      virtual void SetTimeout (ULONG_T timeout);

      //## Operation: GetState%1014886109
      virtual void GetState (COM_STATE_T *state);

      //## Operation: Open%1009995357
      virtual void Open ();

      //## Operation: Close%1009995358
      virtual void Close ();

      //## Operation: Reset%1014806624
      virtual void Reset (INT_T type);

      //## Operation: Read%1009995359
      virtual LONG_T Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout);

      //## Operation: Write%1009995360
      virtual LONG_T Write (UCHAR_T *buffer, ULONG_T amount);

      //## Operation: FlushInput%1009995361
      virtual void FlushInput ();

      //## Operation: FlushOutput%1009995362
      virtual void FlushOutput ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IPAddress%3CAAC6FA011D
      STRING_T get_IPAddress () const;
      void set_IPAddress (STRING_T value);

      //## Attribute: SerialPort%3CAC89A30323
      STRING_T get_SerialPort () const;
      void set_SerialPort (STRING_T value);

      //## Attribute: Redirected%3CABF7CA0158
      BOOL_T get_Redirected () const;
      void set_Redirected (BOOL_T value);

      //## Attribute: ComPort%3CAAC78D0178
      STRING_T get_ComPort () const;
      void set_ComPort (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cSocketChannel%3A6C140C0356.public preserve=yes
      //## end cSocketChannel%3A6C140C0356.public

  protected:
    // Data Members for Class Attributes

      //## begin cSocketChannel::IPAddress%3CAAC6FA011D.attr preserve=no  public: STRING_T {U} 
      STRING_T _IPAddress;
      //## end cSocketChannel::IPAddress%3CAAC6FA011D.attr

      //## begin cSocketChannel::SerialPort%3CAC89A30323.attr preserve=no  public: STRING_T {U} 
      STRING_T _SerialPort;
      //## end cSocketChannel::SerialPort%3CAC89A30323.attr

      //## begin cSocketChannel::Redirected%3CABF7CA0158.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _Redirected;
      //## end cSocketChannel::Redirected%3CABF7CA0158.attr

      //## begin cSocketChannel::ComPort%3CAAC78D0178.attr preserve=no  public: STRING_T {U} 
      STRING_T _ComPort;
      //## end cSocketChannel::ComPort%3CAAC78D0178.attr

    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3CABF78200BE
      //## Role: cSocketChannel::StandardChannel%3CABF78A00FC
      //## begin cSocketChannel::StandardChannel%3CABF78A00FC.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_StandardChannel;
      //## end cSocketChannel::StandardChannel%3CABF78A00FC.role

      //## Association: Control::SerialChannel::<unnamed>%3CAC8B430032
      //## Role: cSocketChannel::Receiver%3CAC8B4302C7
      //## begin cSocketChannel::Receiver%3CAC8B4302C7.role preserve=no  public: cCharReceiver { -> 1RFHN}
      cCharReceiver *_Receiver;
      //## end cSocketChannel::Receiver%3CAC8B4302C7.role

      //## Association: Control::SerialChannel::<unnamed>%3CBBD4B60168
      //## Role: cSocketChannel::Node%3CBBD4B70264
      //## begin cSocketChannel::Node%3CBBD4B70264.role preserve=no  public: cWTNode { -> 1RFHN}
      cWTNode *_Node;
      //## end cSocketChannel::Node%3CBBD4B70264.role

    // Additional Protected Declarations
      //## begin cSocketChannel%3A6C140C0356.protected preserve=yes
      //## end cSocketChannel%3A6C140C0356.protected

  private:
    // Additional Private Declarations
      //## begin cSocketChannel%3A6C140C0356.private preserve=yes
      //## end cSocketChannel%3A6C140C0356.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Connect%1017903089
      void Connect ();

      //## Operation: StartUp%1017825255
      BOOL_T StartUp ();

      //## Operation: SetSerialParams%1018270344
      BOOL_T SetSerialParams ();

      //## Operation: FlushInputBuffer%1018270345
      BOOL_T FlushInputBuffer ();

      //## Operation: ConnectSocket%1017825256
      BOOL_T ConnectSocket (SOCKET &sock, ULONG_T port, BOOL_T always_new = true);

      //## Operation: DisconnectSocket%1018270346
      BOOL_T DisconnectSocket (SOCKET &sock);

      //## Operation: RestartNode%1018961942
      void RestartNode ();

    // Data Members for Class Attributes

      //## Attribute: PortNum%3CAC89D700A7
      //## begin cSocketChannel::PortNum%3CAC89D700A7.attr preserve=no  implementation: INT_T {U} 0
      INT_T _PortNum;
      //## end cSocketChannel::PortNum%3CAC89D700A7.attr

      //## Attribute: Connected%3CABFBB30234
      //## begin cSocketChannel::Connected%3CABFBB30234.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Connected;
      //## end cSocketChannel::Connected%3CABFBB30234.attr

      //## Attribute: DataPort%3CAAC6FA00FF
      //## begin cSocketChannel::DataPort%3CAAC6FA00FF.attr preserve=no  implementation: USHORT_T {U} 0
      USHORT_T _DataPort;
      //## end cSocketChannel::DataPort%3CAAC6FA00FF.attr

      //## Attribute: ControlPort%3CAAC6FA0109
      //## begin cSocketChannel::ControlPort%3CAAC6FA0109.attr preserve=no  implementation: USHORT_T {U} 0
      USHORT_T _ControlPort;
      //## end cSocketChannel::ControlPort%3CAAC6FA0109.attr

      //## Attribute: AdminPort%3CAC8F4D0260
      //## begin cSocketChannel::AdminPort%3CAC8F4D0260.attr preserve=no  implementation: USHORT_T {U} 8888
      USHORT_T _AdminPort;
      //## end cSocketChannel::AdminPort%3CAC8F4D0260.attr

      //## Attribute: DataSocket%3CAC8F1D02CF
      //## begin cSocketChannel::DataSocket%3CAC8F1D02CF.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _DataSocket;
      //## end cSocketChannel::DataSocket%3CAC8F1D02CF.attr

      //## Attribute: ControlSocket%3CAC8F1D02D9
      //## begin cSocketChannel::ControlSocket%3CAC8F1D02D9.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _ControlSocket;
      //## end cSocketChannel::ControlSocket%3CAC8F1D02D9.attr

      //## Attribute: Control%3CF3A0FD00CE
      //## begin cSocketChannel::Control%3CF3A0FD00CE.attr preserve=no  implementation: REM_BOX_CNTRL {U} 
      REM_BOX_CNTRL _Control;
      //## end cSocketChannel::Control%3CF3A0FD00CE.attr

      //## Attribute: Nodes%3CBBD5EC010A
      //## begin cSocketChannel::Nodes%3CBBD5EC010A.attr preserve=no  implementation: static cWTNodes {U} 
      static cWTNodes _Nodes;
      //## end cSocketChannel::Nodes%3CBBD5EC010A.attr

    // Additional Implementation Declarations
      //## begin cSocketChannel%3A6C140C0356.implementation preserve=yes
      //## end cSocketChannel%3A6C140C0356.implementation

};

//## begin cSocketChannel%3A6C140C0356.postscript preserve=yes
//## end cSocketChannel%3A6C140C0356.postscript

// Class cSocketChannel 

//## begin module%3A6C140C0356.epilog preserve=yes
//## end module%3A6C140C0356.epilog


#endif
