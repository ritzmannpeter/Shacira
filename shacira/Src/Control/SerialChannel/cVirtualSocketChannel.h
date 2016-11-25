//## begin module%378B702202CC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%378B702202CC.cm

//## begin module%378B702202CC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%378B702202CC.cp

//## Module: cVirtualSocketChannel%378B702202CC; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cVirtualSocketChannel.h

#ifndef cVirtualSocketChannel_h
#define cVirtualSocketChannel_h 1

//## begin module%378B702202CC.includes preserve=yes
//## end module%378B702202CC.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"

class __DLL_EXPORT__ cError;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cSocketReceiver;
class __DLL_EXPORT__ cCharReceiver;

//## begin module%378B702202CC.additionalDeclarations preserve=yes
//## end module%378B702202CC.additionalDeclarations


//## begin cVirtualSocketChannel%378B702202CC.preface preserve=yes
//## end cVirtualSocketChannel%378B702202CC.preface

//## Class: cVirtualSocketChannel%378B702202CC
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C3443AA0116;cSocketReceiver { -> F}
//## Uses: <unnamed>%3C34AAE90130;cConfigurationObject { -> F}
//## Uses: <unnamed>%3C35646C02E7;cError { -> F}

class __DLL_EXPORT__ cVirtualSocketChannel : public cSerialChannel  //## Inherits: <unnamed>%378B703E0091
{
  //## begin cVirtualSocketChannel%378B702202CC.initialDeclarations preserve=yes
public:
  //## end cVirtualSocketChannel%378B702202CC.initialDeclarations

    //## Constructors (generated)
      cVirtualSocketChannel();

      cVirtualSocketChannel(const cVirtualSocketChannel &right);

    //## Constructors (specified)
      //## Operation: cVirtualSocketChannel%1009995363
      cVirtualSocketChannel (cConfigurationObject *config_obj);

      //## Operation: cVirtualSocketChannel%1010072192
      cVirtualSocketChannel (ULONG_T rx_port, ULONG_T tx_port);

    //## Destructor (generated)
      virtual ~cVirtualSocketChannel();


    //## Other Operations (specified)
      //## Operation: GetBaudRate%1009995364
      virtual ULONG_T GetBaudRate ();

      //## Operation: SetBaudRate%1009995365
      virtual void SetBaudRate (ULONG_T baud_rate);

      //## Operation: GetStopBits%1009995366
      virtual UCHAR_T GetStopBits ();

      //## Operation: SetStopBits%1009995367
      virtual void SetStopBits (UCHAR_T stop_bits);

      //## Operation: GetStartBits%1009995368
      virtual UCHAR_T GetStartBits ();

      //## Operation: SetStartBits%1009995369
      virtual void SetStartBits (UCHAR_T start_bits);

      //## Operation: GetCharLen%1009995370
      virtual UCHAR_T GetCharLen ();

      //## Operation: SetCharLen%1009995371
      virtual void SetCharLen (UCHAR_T data_len);

      //## Operation: GetParity%1009995372
      virtual ParityTypes GetParity ();

      //## Operation: SetParity%1009995373
      virtual void SetParity (ParityTypes parity);

      //## Operation: GetHandshake%1009995374
      virtual HandshakeTypes GetHandshake ();

      //## Operation: SetHandshake%1009995375
      virtual void SetHandshake (HandshakeTypes handshake);

      //## Operation: GetTimeout%1009995376
      virtual ULONG_T GetTimeout ();

      //## Operation: SetTimeout%1009995377
      virtual void SetTimeout (ULONG_T timeout);

      //## Operation: GetState%1014886110
      virtual void GetState (COM_STATE_T *state);

      //## Operation: Open%1009995378
      virtual void Open ();

      //## Operation: Close%1009995379
      virtual void Close ();

      //## Operation: Reset%1014806625
      virtual void Reset (INT_T type);

      //## Operation: Read%1009995380
      virtual LONG_T Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout);

      //## Operation: Write%1009995381
      virtual LONG_T Write (UCHAR_T *buffer, ULONG_T amount);

      //## Operation: FlushInput%1009995382
      virtual void FlushInput ();

      //## Operation: FlushOutput%1009995383
      virtual void FlushOutput ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IPAddress%378B70590112
      STRING_T get_IPAddress () const;
      void set_IPAddress (STRING_T value);

      //## Attribute: RXPort%3C3430360057
      ULONG_T get_RXPort () const;
      void set_RXPort (ULONG_T value);

      //## Attribute: TXPort%3C34306000B2
      ULONG_T get_TXPort () const;
      void set_TXPort (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cVirtualSocketChannel%378B702202CC.public preserve=yes
      //## end cVirtualSocketChannel%378B702202CC.public

  protected:
    // Data Members for Class Attributes

      //## begin cVirtualSocketChannel::IPAddress%378B70590112.attr preserve=no  public: STRING_T {U} "127.0.0.1"
      STRING_T _IPAddress;
      //## end cVirtualSocketChannel::IPAddress%378B70590112.attr

      //## begin cVirtualSocketChannel::RXPort%3C3430360057.attr preserve=no  public: ULONG_T {U} 20000
      ULONG_T _RXPort;
      //## end cVirtualSocketChannel::RXPort%3C3430360057.attr

      //## begin cVirtualSocketChannel::TXPort%3C34306000B2.attr preserve=no  public: ULONG_T {U} 20001
      ULONG_T _TXPort;
      //## end cVirtualSocketChannel::TXPort%3C34306000B2.attr

    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3C3440E6028B
      //## Role: cVirtualSocketChannel::Receiver%3C3440E80003
      //## begin cVirtualSocketChannel::Receiver%3C3440E80003.role preserve=no  public: cCharReceiver { -> 1RFHN}
      cCharReceiver *_Receiver;
      //## end cVirtualSocketChannel::Receiver%3C3440E80003.role

    // Additional Protected Declarations
      //## begin cVirtualSocketChannel%378B702202CC.protected preserve=yes
      //## end cVirtualSocketChannel%378B702202CC.protected

  private:
    // Additional Private Declarations
      //## begin cVirtualSocketChannel%378B702202CC.private preserve=yes
      //## end cVirtualSocketChannel%378B702202CC.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartUp%1010072191
      BOOL_T StartUp ();

      //## Operation: SetSockets%1010072193
      BOOL_T SetSockets ();

    // Data Members for Class Attributes

      //## Attribute: RXSocket%3C347A2E0074
      //## begin cVirtualSocketChannel::RXSocket%3C347A2E0074.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _RXSocket;
      //## end cVirtualSocketChannel::RXSocket%3C347A2E0074.attr

      //## Attribute: TXSocket%3C347A620123
      //## begin cVirtualSocketChannel::TXSocket%3C347A620123.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _TXSocket;
      //## end cVirtualSocketChannel::TXSocket%3C347A620123.attr

    // Additional Implementation Declarations
      //## begin cVirtualSocketChannel%378B702202CC.implementation preserve=yes
      //## end cVirtualSocketChannel%378B702202CC.implementation

};

//## begin cVirtualSocketChannel%378B702202CC.postscript preserve=yes
//## end cVirtualSocketChannel%378B702202CC.postscript

// Class cVirtualSocketChannel 

//## begin module%378B702202CC.epilog preserve=yes
//## end module%378B702202CC.epilog


#endif
