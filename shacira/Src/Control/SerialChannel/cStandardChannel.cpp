//## begin module%3728746C01CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3728746C01CA.cm

//## begin module%3728746C01CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3728746C01CA.cp

//## Module: cStandardChannel%3728746C01CA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cStandardChannel.cpp

//## begin module%3728746C01CA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3728746C01CA.additionalIncludes

//## begin module%3728746C01CA.includes preserve=yes
//## end module%3728746C01CA.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cStandardChannel
#include "Control/SerialChannel/cStandardChannel.h"
//## begin module%3728746C01CA.additionalDeclarations preserve=yes
//## end module%3728746C01CA.additionalDeclarations


// Class cStandardChannel 


cStandardChannel::cStandardChannel()
  //## begin cStandardChannel::cStandardChannel%.hasinit preserve=no
  //## end cStandardChannel::cStandardChannel%.hasinit
  //## begin cStandardChannel::cStandardChannel%.initialization preserve=yes
  //## end cStandardChannel::cStandardChannel%.initialization
{
  //## begin cStandardChannel::cStandardChannel%.body preserve=yes
   _ChannelType = "StandardChannel";
  //## end cStandardChannel::cStandardChannel%.body
}

cStandardChannel::cStandardChannel(const cStandardChannel &right)
  //## begin cStandardChannel::cStandardChannel%copy.hasinit preserve=no
  //## end cStandardChannel::cStandardChannel%copy.hasinit
  //## begin cStandardChannel::cStandardChannel%copy.initialization preserve=yes
  //## end cStandardChannel::cStandardChannel%copy.initialization
{
  //## begin cStandardChannel::cStandardChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardChannel::cStandardChannel%copy.body
}

cStandardChannel::cStandardChannel (cConfigurationObject *config_obj)
  //## begin cStandardChannel::cStandardChannel%980152396.hasinit preserve=no
  //## end cStandardChannel::cStandardChannel%980152396.hasinit
  //## begin cStandardChannel::cStandardChannel%980152396.initialization preserve=yes
   : cSerialChannel(config_obj)
  //## end cStandardChannel::cStandardChannel%980152396.initialization
{
  //## begin cStandardChannel::cStandardChannel%980152396.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _ChannelType = "StandardChannel";
   _BaseChannel.SetPortName(config_obj->PropertyValue("PortName", "unknown", true).c_str());
  //## end cStandardChannel::cStandardChannel%980152396.body
}

cStandardChannel::cStandardChannel (CONST_STRING_T port_name)
  //## begin cStandardChannel::cStandardChannel%1069326619.hasinit preserve=no
  //## end cStandardChannel::cStandardChannel%1069326619.hasinit
  //## begin cStandardChannel::cStandardChannel%1069326619.initialization preserve=yes
  //## end cStandardChannel::cStandardChannel%1069326619.initialization
{
  //## begin cStandardChannel::cStandardChannel%1069326619.body preserve=yes
   _ChannelType = "StandardChannel";
   _BaseChannel.SetPortName(port_name);
  //## end cStandardChannel::cStandardChannel%1069326619.body
}


cStandardChannel::~cStandardChannel()
{
  //## begin cStandardChannel::~cStandardChannel%.body preserve=yes
  //## end cStandardChannel::~cStandardChannel%.body
}



//## Other Operations (implementation)
ULONG_T cStandardChannel::GetBaudRate ()
{
  //## begin cStandardChannel::GetBaudRate%980176536.body preserve=yes
   return _BaseChannel.GetBaudRate();
  //## end cStandardChannel::GetBaudRate%980176536.body
}

void cStandardChannel::SetBaudRate (ULONG_T baud_rate)
{
  //## begin cStandardChannel::SetBaudRate%980152397.body preserve=yes
   _BaudRate = baud_rate;
   _BaseChannel.SetBaudRate(baud_rate);
  //## end cStandardChannel::SetBaudRate%980152397.body
}

UCHAR_T cStandardChannel::GetStopBits ()
{
  //## begin cStandardChannel::GetStopBits%980152398.body preserve=yes
   return _BaseChannel.GetStopBits();
  //## end cStandardChannel::GetStopBits%980152398.body
}

void cStandardChannel::SetStopBits (UCHAR_T stop_bits)
{
  //## begin cStandardChannel::SetStopBits%980152399.body preserve=yes
   _StopBits = stop_bits;
   _BaseChannel.SetStopBits(stop_bits);
  //## end cStandardChannel::SetStopBits%980152399.body
}

UCHAR_T cStandardChannel::GetStartBits ()
{
  //## begin cStandardChannel::GetStartBits%980152400.body preserve=yes
   return _BaseChannel.GetStartBits();
  //## end cStandardChannel::GetStartBits%980152400.body
}

void cStandardChannel::SetStartBits (UCHAR_T start_bits)
{
  //## begin cStandardChannel::SetStartBits%980152401.body preserve=yes
   _StartBits = start_bits;
   _BaseChannel.SetStartBits(start_bits);
  //## end cStandardChannel::SetStartBits%980152401.body
}

UCHAR_T cStandardChannel::GetCharLen ()
{
  //## begin cStandardChannel::GetCharLen%980152402.body preserve=yes
   return _BaseChannel.GetCharLen();
  //## end cStandardChannel::GetCharLen%980152402.body
}

void cStandardChannel::SetCharLen (UCHAR_T data_len)
{
  //## begin cStandardChannel::SetCharLen%980152403.body preserve=yes
   _CharLen = data_len;
   _BaseChannel.SetCharLen(data_len);
  //## end cStandardChannel::SetCharLen%980152403.body
}

ParityTypes cStandardChannel::GetParity ()
{
  //## begin cStandardChannel::GetParity%980152404.body preserve=yes
   return _BaseChannel.GetParity();
  //## end cStandardChannel::GetParity%980152404.body
}

void cStandardChannel::SetParity (ParityTypes parity)
{
  //## begin cStandardChannel::SetParity%980152405.body preserve=yes
   _Parity = parity;
   _BaseChannel.SetParity(parity);
  //## end cStandardChannel::SetParity%980152405.body
}

HandshakeTypes cStandardChannel::GetHandshake ()
{
  //## begin cStandardChannel::GetHandshake%980239688.body preserve=yes
   return _BaseChannel.GetHandshake();
  //## end cStandardChannel::GetHandshake%980239688.body
}

void cStandardChannel::SetHandshake (HandshakeTypes handshake)
{
  //## begin cStandardChannel::SetHandshake%980239689.body preserve=yes
   _Handshake = handshake;
   _BaseChannel.SetHandshake(handshake);
  //## end cStandardChannel::SetHandshake%980239689.body
}

ULONG_T cStandardChannel::GetTimeout ()
{
  //## begin cStandardChannel::GetTimeout%980152406.body preserve=yes
   return _BaseChannel.GetTimeout();
  //## end cStandardChannel::GetTimeout%980152406.body
}

void cStandardChannel::SetTimeout (ULONG_T timeout)
{
  //## begin cStandardChannel::SetTimeout%980152407.body preserve=yes
   _BaseChannel.SetTimeout(timeout);
  //## end cStandardChannel::SetTimeout%980152407.body
}

void cStandardChannel::GetState (COM_STATE_T *state)
{
  //## begin cStandardChannel::GetState%1014886111.body preserve=yes
   _BaseChannel.GetState(state);
  //## end cStandardChannel::GetState%1014886111.body
}

void cStandardChannel::Open ()
{
  //## begin cStandardChannel::Open%980168055.body preserve=yes
   _BaseChannel.Open();
   if (_IsBus) _IsOpen = true;
  //## end cStandardChannel::Open%980168055.body
}

void cStandardChannel::Close ()
{
  //## begin cStandardChannel::Close%980168056.body preserve=yes
   _BaseChannel.Close();
  //## end cStandardChannel::Close%980168056.body
}

void cStandardChannel::Reset (INT_T type)
{
  //## begin cStandardChannel::Reset%1014806626.body preserve=yes
   BOOL_T reset = false;
   if (type == ERROR_RESET || type == INIT_DEVICE) {
      _BaseChannel.ResetDevice();
   } else {
      reset = true;
   }
   if (reset) {
      _BaseChannel.Close();
      _BaseChannel.Open();
      _BaseChannel.SetBaudRate(_BaudRate);
      _BaseChannel.SetParity(_Parity);
      _BaseChannel.SetCharLen(_CharLen);
      _BaseChannel.SetStartBits(_StartBits);
      _BaseChannel.SetStopBits(_StopBits);
      _BaseChannel.SetHandshake(_Handshake);
   }
  //## end cStandardChannel::Reset%1014806626.body
}

LONG_T cStandardChannel::Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout)
{
  //## begin cStandardChannel::Read%934378728.body preserve=yes
   if (_Verbose) SetDirection(CHANNEL_INPUT);
   long rc = _BaseChannel.Read(buffer, amount, timeout);
   if (_Verbose) PrintBuf((const char *)buffer, rc, CHANNEL_INPUT);
   return rc;
  //## end cStandardChannel::Read%934378728.body
}

LONG_T cStandardChannel::Write (UCHAR_T *buffer, ULONG_T amount)
{
  //## begin cStandardChannel::Write%934378729.body preserve=yes
   if (_Verbose) {
      SetDirection(CHANNEL_OUTPUT);
      PrintBuf((const char *)buffer, amount, CHANNEL_OUTPUT);
   }
   return _BaseChannel.Write(buffer, amount);
  //## end cStandardChannel::Write%934378729.body
}

void cStandardChannel::FlushInput ()
{
  //## begin cStandardChannel::FlushInput%934378732.body preserve=yes
	_BaseChannel.FlushInput();
  //## end cStandardChannel::FlushInput%934378732.body
}

void cStandardChannel::FlushOutput ()
{
  //## begin cStandardChannel::FlushOutput%934378733.body preserve=yes
	_BaseChannel.FlushOutput();
  //## end cStandardChannel::FlushOutput%934378733.body
}

CONST_STRING_T cStandardChannel::GetPortName ()
{
  //## begin cStandardChannel::GetPortName%980168057.body preserve=yes
   return _BaseChannel.GetPortName();
  //## end cStandardChannel::GetPortName%980168057.body
}

void cStandardChannel::SetPortName (CONST_STRING_T name)
{
  //## begin cStandardChannel::SetPortName%980168058.body preserve=yes
   _BaseChannel.SetPortName(name);
  //## end cStandardChannel::SetPortName%980168058.body
}

// Additional Declarations
  //## begin cStandardChannel%3728746C01CA.declarations preserve=yes
  //## end cStandardChannel%3728746C01CA.declarations

//## begin module%3728746C01CA.epilog preserve=yes
//## end module%3728746C01CA.epilog
