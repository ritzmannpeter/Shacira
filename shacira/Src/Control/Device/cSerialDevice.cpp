//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
#include "FirstHeader.h"
#include "Control/Device/cSerialDevice.h"

cSerialDevice::cSerialDevice()
      : _SerialChannel(NULL)
{
   Parameter("BaudRate") = 9600L;
   Parameter("Parity") = (int)Even;
   Parameter("Handshake") = (int)NoHandshake;
   Parameter("CharLen") = 8;
   Parameter("StartBits") = 1;
   Parameter("StopBits") = 1;
   _ActDirection = DIR_OUTPUT;
}

cSerialDevice::cSerialDevice (cConfigurationObject *config_obj, cCell *cell)
      : cDevice(config_obj, cell), _SerialChannel(NULL)
{
_ASSERT_COND(config_obj != NULL)
   STRING_T channel_type = config_obj->PropertyValue("ChannelType", "StandardChannel");
   STRING_T port_name = config_obj->PropertyValue("PortName", "COM1");
   STRING_T parity = config_obj->PropertyValue("Parity", "none");
   STRING_T handshake = config_obj->PropertyValue("Handshake", "none");

   Parameter("ChannelType") = channel_type.c_str();
   Parameter("PortName") = port_name.c_str();
   
   Parameter("BaudRate") = config_obj->PropertyValue("BaudRate", (ULONG_T)9600);
   Parameter("Parity") = cSerialChannel::ParityType(parity.c_str());
   Parameter("Handshake") = cSerialChannel::HandshakeType(handshake.c_str());
   Parameter("CharLen") = config_obj->PropertyValue("CharLen", (ULONG_T)8);
   Parameter("StartBits") = config_obj->PropertyValue("StartBits", (ULONG_T)1);
   Parameter("StopBits") = config_obj->PropertyValue("StopBits", (ULONG_T)1);
   _ActDirection = DIR_OUTPUT;
}


cSerialDevice::~cSerialDevice()
{
}

BOOL_T cSerialDevice::InitializeInterface()
{
   FreeInterface();
   cConfigurationObject * serial_channel_obj = _ConfigurationObject->PropertyValue("SerialChannel", NULL_OBJECT);
   if (serial_channel_obj != NULL) {
      _SerialChannel = cSerialChannelFactory::CreateSerialChannel(serial_channel_obj);
      _SerialChannel->Open();
      ULONG_T baud_rate = Parameter("BaudRate");
      ParityTypes parity = (ParityTypes)(int)Parameter("Parity");
      HandshakeTypes handshake = (HandshakeTypes)(int)Parameter("Handshake");
      UCHAR_T char_len = (UCHAR_T)(int)Parameter("CharLen");
      UCHAR_T start_bits = (UCHAR_T)(int)Parameter("StartBits");
      UCHAR_T stop_bits = (UCHAR_T)(int)Parameter("StopBits");
      _SerialChannel->SetBaudRate(baud_rate);
      _SerialChannel->SetCharLen(char_len);
      _SerialChannel->SetStartBits(start_bits);
      _SerialChannel->SetStopBits(stop_bits);
      _SerialChannel->SetParity(parity);
   }
   return true;
}

BOOL_T cSerialDevice::FreeInterface()
{
   if (_SerialChannel != NULL) {
      cSerialChannel * channel_ptr = _SerialChannel;
      _SerialChannel = NULL;
      channel_ptr->Close();
      delete channel_ptr;
   }
   return true;
}

void cSerialDevice::PrintBuf(CONST_STRING_T buf, ULONG_T len, INT_T direction)
{
   SetDirection(direction);
   STRING_T msg;
   msg = Format(buf, len).c_str();
   Protocol("%s", msg.c_str());
}

void cSerialDevice::SetDirection(INT_T direction)
{
   if (_ActDirection != direction) {
      if (direction == DIR_INPUT) {
         Protocol("\n<<");
      } else if (direction == DIR_OUTPUT) {
         Protocol("\n>>");
      }
      _ActDirection = direction;
   }
}

STRING_T cSerialDevice::Format(CONST_STRING_T buf, ULONG_T len)
{
   STRING_T formatted;
   for (unsigned int i=0; i<len; i++) {
      char temp[0x20] = {0};
      if (isprint(buf[i])) {
         SafePrintf(temp, sizeof(temp), "%c", buf[i]);
      } else {
         SafePrintf(temp, sizeof(temp), "[%d]", buf[i]);
      }
      formatted += temp;
   }
   return formatted;
}


