//## begin module%371221790390.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%371221790390.cm

//## begin module%371221790390.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%371221790390.cp

//## Module: cSerialChannel%371221790390; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialChannel.cpp

//## begin module%371221790390.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%371221790390.additionalIncludes

//## begin module%371221790390.includes preserve=yes
//## end module%371221790390.includes

// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
//## begin module%371221790390.additionalDeclarations preserve=yes
//## end module%371221790390.additionalDeclarations


// Class cSerialChannel 


























cSerialChannel::cSerialChannel()
  //## begin cSerialChannel::cSerialChannel%.hasinit preserve=no
      : _Verbose(false), _User("unknown"), _IsBus(false), _IsOpen(false), _BaudRate(0), _Parity(None), _StopBits(0), _StartBits(0), _CharLen(0), _Handshake(NoHandshake), _ErrorState(0), _ActDirection(CHANNEL_INPUT), _Binary(false), _Buffer(NULL)
  //## end cSerialChannel::cSerialChannel%.hasinit
  //## begin cSerialChannel::cSerialChannel%.initialization preserve=yes
  //## end cSerialChannel::cSerialChannel%.initialization
{
  //## begin cSerialChannel::cSerialChannel%.body preserve=yes
  //## end cSerialChannel::cSerialChannel%.body
}

cSerialChannel::cSerialChannel(const cSerialChannel &right)
  //## begin cSerialChannel::cSerialChannel%copy.hasinit preserve=no
      : _Verbose(false), _User("unknown"), _IsBus(false), _IsOpen(false), _BaudRate(0), _Parity(None), _StopBits(0), _StartBits(0), _CharLen(0), _Handshake(NoHandshake), _ErrorState(0), _ActDirection(CHANNEL_INPUT), _Binary(false), _Buffer(NULL)
  //## end cSerialChannel::cSerialChannel%copy.hasinit
  //## begin cSerialChannel::cSerialChannel%copy.initialization preserve=yes
  //## end cSerialChannel::cSerialChannel%copy.initialization
{
  //## begin cSerialChannel::cSerialChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialChannel::cSerialChannel%copy.body
}

cSerialChannel::cSerialChannel (cConfigurationObject *config_obj)
  //## begin cSerialChannel::cSerialChannel%981360504.hasinit preserve=no
      : _Verbose(false), _User("unknown"), _IsBus(false), _IsOpen(false), _BaudRate(0), _Parity(None), _StopBits(0), _StartBits(0), _CharLen(0), _Handshake(NoHandshake), _ErrorState(0), _ActDirection(CHANNEL_INPUT), _Binary(false), _Buffer(NULL)
  //## end cSerialChannel::cSerialChannel%981360504.hasinit
  //## begin cSerialChannel::cSerialChannel%981360504.initialization preserve=yes
  //## end cSerialChannel::cSerialChannel%981360504.initialization
{
  //## begin cSerialChannel::cSerialChannel%981360504.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _Name = config_obj->get_Name();
   _Verbose = config_obj->PropertyValue("Verbose", _Verbose);
   _IsBus = config_obj->PropertyValue("IsBus", _IsBus);
  //## end cSerialChannel::cSerialChannel%981360504.body
}


cSerialChannel::~cSerialChannel()
{
  //## begin cSerialChannel::~cSerialChannel%.body preserve=yes
   DELETE_OBJECT(cCharRingBuffer, _Buffer)
  //## end cSerialChannel::~cSerialChannel%.body
}

BOOL_T cSerialChannel::SendChar (UCHAR_T c)
{
  //## begin cSerialChannel::SendChar%985437687.body preserve=yes
   if (Write(&c, 1) == 1) {
      return true;
   } else {
      return false;
   }
  //## end cSerialChannel::SendChar%985437687.body
}

INT_T cSerialChannel::GetChar (ULONG_T timeout)
{
  //## begin cSerialChannel::GetChar%985437688.body preserve=yes
   unsigned char c = 0x00;
	if (Read(&c, 1, timeout) != 1) {
		return EOF;
   } else {
      return c;
   }
  //## end cSerialChannel::GetChar%985437688.body
}

ParityTypes cSerialChannel::ParityType (CONST_STRING_T type_name)
{
  //## begin cSerialChannel::ParityType%1027605559.body preserve=yes
   TYPE_CODE(type_name,Even)
   TYPE_CODE(type_name,Odd)
   TYPE_CODE(type_name,Mark)
   TYPE_CODE(type_name,Space)
   TYPE_CODE(type_name,None)
   throw cError(INVALID_PARAMETER_VALUE, 0, type_name, "cSerialChannel::ParityType");
  //## end cSerialChannel::ParityType%1027605559.body
}

HandshakeTypes cSerialChannel::HandshakeType (CONST_STRING_T type_name)
{
  //## begin cSerialChannel::HandshakeType%1071171006.body preserve=yes
   if (strnicmp(type_name, "None", strlen("None")) == 0) {
      return NoHandshake;
   } else if (strnicmp(type_name, "ISW_OSW", strlen("ISW_OSW")) == 0) {
      return (HandshakeTypes)(InputSW | OutputSW);
   } else if (strnicmp(type_name, "ISW_OHW", strlen("ISW_OHW")) == 0) {
      return (HandshakeTypes)(InputSW | OutputHW);
   } else if (strnicmp(type_name, "IHW_OSW", strlen("IHW_OSW")) == 0) {
      return (HandshakeTypes)(InputHW | OutputSW);
   } else if (strnicmp(type_name, "IHW_OHW", strlen("IHW_OHW")) == 0) {
      return (HandshakeTypes)(InputHW | OutputHW);
   }
   throw cError(INVALID_PARAMETER_VALUE, 0, type_name, "cSerialChannel::HandshakeType");
  //## end cSerialChannel::HandshakeType%1071171006.body
}

void cSerialChannel::PrintBuf (CONST_STRING_T buf, ULONG_T len, INT_T direction)
{
  //## begin cSerialChannel::PrintBuf%998299190.body preserve=yes
   if (_Verbose) {
      STRING_T msg;
      msg = Format(buf, len).c_str();
///      DebugPrintf("%s", msg.c_str());
   }
  //## end cSerialChannel::PrintBuf%998299190.body
}

void cSerialChannel::SetDirection (INT_T direction)
{
  //## begin cSerialChannel::SetDirection%1043598188.body preserve=yes
   if (_ActDirection != direction) {
      if (direction == CHANNEL_INPUT) {
///         DebugPrintf(_Name.c_str(), "\n<<");
      } else if (direction == CHANNEL_OUTPUT) {
///         DebugPrintf("\n>>");
      }
      _ActDirection = direction;
   }
  //## end cSerialChannel::SetDirection%1043598188.body
}

STRING_T cSerialChannel::Format (CONST_STRING_T buf, ULONG_T len)
{
  //## begin cSerialChannel::Format%1037956858.body preserve=yes
   STRING_T formatted;
   for (unsigned int i=0; i<len; i++) {
      char temp[16] = {0};
      if (buf[i] == 0) _Binary = true;
      if (isprint(buf[i]) && !_Binary) {
         SafePrintf(temp, sizeof(temp), "%c", buf[i]);
      } else {
         SafePrintf(temp, sizeof(temp), "[%d]", buf[i]);
      }
      formatted += temp;
   }
   return formatted;
  //## end cSerialChannel::Format%1037956858.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSerialChannel::get_ChannelType () const
{
  //## begin cSerialChannel::get_ChannelType%3712224F01E0.get preserve=no
  return _ChannelType;
  //## end cSerialChannel::get_ChannelType%3712224F01E0.get
}

BOOL_T cSerialChannel::get_Verbose () const
{
  //## begin cSerialChannel::get_Verbose%3B80D5C903E1.get preserve=no
  return _Verbose;
  //## end cSerialChannel::get_Verbose%3B80D5C903E1.get
}

void cSerialChannel::set_Verbose (BOOL_T value)
{
  //## begin cSerialChannel::set_Verbose%3B80D5C903E1.set preserve=no
  _Verbose = value;
  //## end cSerialChannel::set_Verbose%3B80D5C903E1.set
}

STRING_T cSerialChannel::get_User () const
{
  //## begin cSerialChannel::get_User%3CE0FBD602D0.get preserve=no
  return _User;
  //## end cSerialChannel::get_User%3CE0FBD602D0.get
}

void cSerialChannel::set_User (STRING_T value)
{
  //## begin cSerialChannel::set_User%3CE0FBD602D0.set preserve=no
  _User = value;
  //## end cSerialChannel::set_User%3CE0FBD602D0.set
}

BOOL_T cSerialChannel::get_IsBus () const
{
  //## begin cSerialChannel::get_IsBus%3E2C3E4600FF.get preserve=no
  return _IsBus;
  //## end cSerialChannel::get_IsBus%3E2C3E4600FF.get
}

void cSerialChannel::set_IsBus (BOOL_T value)
{
  //## begin cSerialChannel::set_IsBus%3E2C3E4600FF.set preserve=no
  _IsBus = value;
  //## end cSerialChannel::set_IsBus%3E2C3E4600FF.set
}

BOOL_T cSerialChannel::get_IsOpen () const
{
  //## begin cSerialChannel::get_IsOpen%3E2C47FF018A.get preserve=no
  return _IsOpen;
  //## end cSerialChannel::get_IsOpen%3E2C47FF018A.get
}

void cSerialChannel::set_IsOpen (BOOL_T value)
{
  //## begin cSerialChannel::set_IsOpen%3E2C47FF018A.set preserve=no
  _IsOpen = value;
  //## end cSerialChannel::set_IsOpen%3E2C47FF018A.set
}

// Additional Declarations
  //## begin cSerialChannel%371221790390.declarations preserve=yes
  //## end cSerialChannel%371221790390.declarations

//## begin module%371221790390.epilog preserve=yes
//## end module%371221790390.epilog
