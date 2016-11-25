//## begin module%3A6C140C0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A6C140C0356.cm

//## begin module%3A6C140C0356.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A6C140C0356.cp

//## Module: cSocketChannel%3A6C140C0356; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSocketChannel.cpp

//## begin module%3A6C140C0356.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A6C140C0356.additionalIncludes

//## begin module%3A6C140C0356.includes preserve=yes

#include "System/Sys/cSockets.h"

//## end module%3A6C140C0356.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cCharReceiver
#include "Control/SerialChannel/cCharReceiver.h"
// cSocketChannel
#include "Control/SerialChannel/cSocketChannel.h"
// cStandardChannel
#include "Control/SerialChannel/cStandardChannel.h"
// cWTNode
#include "Control/SerialChannel/cWTNode.h"
// cTCPReceiver
#include "Control/SerialChannel/cTCPReceiver.h"
//## begin module%3A6C140C0356.additionalDeclarations preserve=yes

static unsigned long WTBaudRate(int ports, unsigned long baud_rate)
{
   if (ports == 4) {
      switch (baud_rate) {
      case 57600: return 0;
      case 38400: return 1;
      case 19200: return 2;
      case 9600: return 3;
      case 7200: return 4;
      case 4800: return 5;
      case 2400: return 6;
      case 1200: return 7;
      case 600: return 8;
      case 300: return 9;
      case 150: return 10;
      case 230400: return 11;
      case 75: return 12;
      case 50: return 13;
      case 153600: return 14;
      case 115200: return 15;
      default: return 0;
      }
   } else if (ports == 1) {
// mapping for one port nodes
   } else {
   }
   return 0;
}

//## end module%3A6C140C0356.additionalDeclarations


// Class cSocketChannel 













//## begin cSocketChannel::Nodes%3CBBD5EC010A.attr preserve=no  implementation: static cWTNodes {U} 
cWTNodes cSocketChannel::_Nodes;
//## end cSocketChannel::Nodes%3CBBD5EC010A.attr




cSocketChannel::cSocketChannel()
  //## begin cSocketChannel::cSocketChannel%.hasinit preserve=no
      : _Redirected(true), _PortNum(0), _Connected(false), _DataPort(0), _ControlPort(0), _AdminPort(8888), _DataSocket(INVALID_SOCKET), _ControlSocket(INVALID_SOCKET), _StandardChannel(NULL), _Receiver(NULL), _Node(NULL)
  //## end cSocketChannel::cSocketChannel%.hasinit
  //## begin cSocketChannel::cSocketChannel%.initialization preserve=yes
  //## end cSocketChannel::cSocketChannel%.initialization
{
  //## begin cSocketChannel::cSocketChannel%.body preserve=yes
   memset(&_Control, 0, sizeof(_Control));
  //## end cSocketChannel::cSocketChannel%.body
}

cSocketChannel::cSocketChannel(const cSocketChannel &right)
  //## begin cSocketChannel::cSocketChannel%copy.hasinit preserve=no
      : _Redirected(true), _PortNum(0), _Connected(false), _DataPort(0), _ControlPort(0), _AdminPort(8888), _DataSocket(INVALID_SOCKET), _ControlSocket(INVALID_SOCKET), _StandardChannel(NULL), _Receiver(NULL), _Node(NULL)
  //## end cSocketChannel::cSocketChannel%copy.hasinit
  //## begin cSocketChannel::cSocketChannel%copy.initialization preserve=yes
  //## end cSocketChannel::cSocketChannel%copy.initialization
{
  //## begin cSocketChannel::cSocketChannel%copy.body preserve=yes
_ASSERT_UNCOND
   memset(&_Control, 0, sizeof(_Control));
  //## end cSocketChannel::cSocketChannel%copy.body
}

cSocketChannel::cSocketChannel (cConfigurationObject *config_obj)
  //## begin cSocketChannel::cSocketChannel%1009995342.hasinit preserve=no
      : _Redirected(true), _PortNum(0), _Connected(false), _DataPort(0), _ControlPort(0), _AdminPort(8888), _DataSocket(INVALID_SOCKET), _ControlSocket(INVALID_SOCKET), _StandardChannel(NULL), _Receiver(NULL), _Node(NULL)
  //## end cSocketChannel::cSocketChannel%1009995342.hasinit
  //## begin cSocketChannel::cSocketChannel%1009995342.initialization preserve=yes
   , cSerialChannel(config_obj)
  //## end cSocketChannel::cSocketChannel%1009995342.initialization
{
  //## begin cSocketChannel::cSocketChannel%1009995342.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   memset(&_Control, 0, sizeof(_Control));
   _ComPort = config_obj->PropertyValue("PortName", "");
   _SerialPort = config_obj->PropertyValue("SerialPort", "");
   _Redirected = config_obj->PropertyValue("Redirected", _Redirected);
   _IPAddress = config_obj->PropertyValue("IPAddress", _IPAddress.c_str());
   if (_Redirected) {
      if (_ComPort.size() > 0) {
         _StandardChannel = new cStandardChannel(config_obj);
      } else {
         throw cError(SOCKET_CHANNEL_NO_PORT_NAME, 0, _Name.c_str());
      }
   } else {
      memset(&_Control, 0, sizeof(_Control));
	  if (_IPAddress.size() == 0) throw cError(SOCKET_CHANNEL_NO_IP_ADDRESS, 0, _Name.c_str());
      if (_SerialPort.size() > 0) {
         const char * port = _SerialPort.c_str();
         if (_stricmp(port, "A") == 0) {
            _PortNum = 0;
            _DataPort = 8000;
            _ControlPort = 9094;
         } else if (_stricmp(port, "B") == 0) {
            _PortNum = 1;
            _DataPort = 8100;
            _ControlPort = 9194;
         } else if (_stricmp(port, "C") == 0) {
            _PortNum = 2;
            _DataPort = 8200;
            _ControlPort = 9294;
         } else if (_stricmp(port, "D") == 0) {
            _PortNum = 3;
            _DataPort = 8300;
            _ControlPort = 9394;
         } else {
            throw cError(SOCKET_CHANNEL_INVALID_SERIAL_PORT, 0, _Name.c_str(), port);
         }
      } else {
         throw cError(SOCKET_CHANNEL_NO_SERIAL_PORT, 0, _Name.c_str());
      }
   }
   if (StartUp()) {
   }
   _Node = _Nodes.Node(_IPAddress.c_str());
  //## end cSocketChannel::cSocketChannel%1009995342.body
}


cSocketChannel::~cSocketChannel()
{
  //## begin cSocketChannel::~cSocketChannel%.body preserve=yes
   if (_Redirected) {
      DELETE_OBJECT(cSerialChannel, _StandardChannel)
   } else {
      if (_DataSocket != INVALID_SOCKET) closesocket(_DataSocket);
      if (_ControlSocket != INVALID_SOCKET) closesocket(_ControlSocket);
   }
  //## end cSocketChannel::~cSocketChannel%.body
}



//## Other Operations (implementation)
ULONG_T cSocketChannel::GetBaudRate ()
{
  //## begin cSocketChannel::GetBaudRate%1009995343.body preserve=yes
   Connect();
   if (!_Connected) return 0;
   if (_Redirected) {
      return _StandardChannel->GetBaudRate();
   } else {
      return 0;
   }
  //## end cSocketChannel::GetBaudRate%1009995343.body
}

void cSocketChannel::SetBaudRate (ULONG_T baud_rate)
{
  //## begin cSocketChannel::SetBaudRate%1009995344.body preserve=yes
   _BaudRate = baud_rate;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetBaudRate(baud_rate);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetBaudRate%1009995344.body
}

UCHAR_T cSocketChannel::GetStopBits ()
{
  //## begin cSocketChannel::GetStopBits%1009995345.body preserve=yes
   Connect();
   if (!_Connected) return 0;
   if (_Redirected) {
      return _StandardChannel->GetStopBits();
   } else {
      return 0;
   }
  //## end cSocketChannel::GetStopBits%1009995345.body
}

void cSocketChannel::SetStopBits (UCHAR_T stop_bits)
{
  //## begin cSocketChannel::SetStopBits%1009995346.body preserve=yes
   _StopBits = stop_bits;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetStopBits(stop_bits);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetStopBits%1009995346.body
}

UCHAR_T cSocketChannel::GetStartBits ()
{
  //## begin cSocketChannel::GetStartBits%1009995347.body preserve=yes
   Connect();
   if (!_Connected) return 0;
   if (_Redirected) {
      return _StandardChannel->GetStartBits();
   } else {
      return 0;
   }
  //## end cSocketChannel::GetStartBits%1009995347.body
}

void cSocketChannel::SetStartBits (UCHAR_T start_bits)
{
  //## begin cSocketChannel::SetStartBits%1009995348.body preserve=yes
   _StartBits = start_bits;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetStartBits(start_bits);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetStartBits%1009995348.body
}

UCHAR_T cSocketChannel::GetCharLen ()
{
  //## begin cSocketChannel::GetCharLen%1009995349.body preserve=yes
   Connect();
   if (!_Connected) return 0;
   if (_Redirected) {
      return _StandardChannel->GetCharLen();
   } else {
      return 0;
   }
  //## end cSocketChannel::GetCharLen%1009995349.body
}

void cSocketChannel::SetCharLen (UCHAR_T data_len)
{
  //## begin cSocketChannel::SetCharLen%1009995350.body preserve=yes
   _CharLen = data_len;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetCharLen(data_len);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetCharLen%1009995350.body
}

ParityTypes cSocketChannel::GetParity ()
{
  //## begin cSocketChannel::GetParity%1009995351.body preserve=yes
   Connect();
   if (!_Connected) return UndefinedParity;
   if (_Redirected) {
      return _StandardChannel->GetParity();
   } else {
      return UndefinedParity;
   }
  //## end cSocketChannel::GetParity%1009995351.body
}

void cSocketChannel::SetParity (ParityTypes parity)
{
  //## begin cSocketChannel::SetParity%1009995352.body preserve=yes
   _Parity = parity;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetParity(parity);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetParity%1009995352.body
}

HandshakeTypes cSocketChannel::GetHandshake ()
{
  //## begin cSocketChannel::GetHandshake%1009995353.body preserve=yes
   Connect();
   if (!_Connected) return UndefinedHandshake;
   if (_Redirected) {
      return _StandardChannel->GetHandshake();
   } else {
      return UndefinedHandshake;
   }
  //## end cSocketChannel::GetHandshake%1009995353.body
}

void cSocketChannel::SetHandshake (HandshakeTypes handshake)
{
  //## begin cSocketChannel::SetHandshake%1009995354.body preserve=yes
   _Handshake = handshake;
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetHandshake(handshake);
   } else {
      SetSerialParams();
   }
  //## end cSocketChannel::SetHandshake%1009995354.body
}

ULONG_T cSocketChannel::GetTimeout ()
{
  //## begin cSocketChannel::GetTimeout%1009995355.body preserve=yes
   Connect();
   if (!_Connected) return 0;
   if (_Redirected) {
      return _StandardChannel->GetTimeout();
   } else {
      return 0;
   }
  //## end cSocketChannel::GetTimeout%1009995355.body
}

void cSocketChannel::SetTimeout (ULONG_T timeout)
{
  //## begin cSocketChannel::SetTimeout%1009995356.body preserve=yes
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->SetTimeout(timeout);
   } else {
   }
  //## end cSocketChannel::SetTimeout%1009995356.body
}

void cSocketChannel::GetState (COM_STATE_T *state)
{
  //## begin cSocketChannel::GetState%1014886109.body preserve=yes
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->GetState(state);
   } else {
   }
  //## end cSocketChannel::GetState%1014886109.body
}

void cSocketChannel::Open ()
{
  //## begin cSocketChannel::Open%1009995357.body preserve=yes
   if (!_Node->Reachable()) return;
   if (_Redirected) {
      try {
         _StandardChannel->Open();
         _Connected = true;
         _StandardChannel->SetBaudRate(_BaudRate);
         _StandardChannel->SetParity(_Parity);
         _StandardChannel->SetStopBits(_StopBits);
         _StandardChannel->SetStartBits(_StartBits);
         _StandardChannel->SetCharLen(_CharLen);
         _StandardChannel->set_Verbose(_Verbose);
      } catch (cError & e) {
         int err_code = e.get_NativeCode();
         if (err_code == 121) {
            _Connected = false;
         } else {
            throw e;
         }
      }
   } else {
      if (ConnectSocket(_DataSocket, _DataPort)) {
         ConnectSocket(_ControlSocket, _ControlPort);
         SetSerialParams();
         if (_Receiver != NULL) DELETE_OBJECT(cCharReceiver, _Receiver)
         _Receiver = new cTCPReceiver(_DataSocket);
         _Connected = true;
      }
   }
  //## end cSocketChannel::Open%1009995357.body
}

void cSocketChannel::Close ()
{
  //## begin cSocketChannel::Close%1009995358.body preserve=yes
   if (_Redirected) {
      if (_Connected) {
         _StandardChannel->Close();
         _Connected = false;
      }
   } else {
      if (_Connected) {
         DisconnectSocket(_DataSocket);
         DisconnectSocket(_ControlSocket);
         _Connected = false;
      }
   }
  //## end cSocketChannel::Close%1009995358.body
}

void cSocketChannel::Reset (INT_T type)
{
  //## begin cSocketChannel::Reset%1014806624.body preserve=yes
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->Reset(type);
   } else {
   }
  //## end cSocketChannel::Reset%1014806624.body
}

LONG_T cSocketChannel::Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout)
{
  //## begin cSocketChannel::Read%1009995359.body preserve=yes
   Connect();
   if (!_Connected) {
      cSystemUtils::Suspend(timeout);
      return 0;
   }
   if (_Redirected) {
      return _StandardChannel->Read(buffer, amount, timeout);
   } else {
      int len = _Receiver->Get((char*)buffer, amount, timeout);
      if (_Verbose) PrintBuf((const char *)buffer, len, CHANNEL_INPUT);
      return len;
   }
  //## end cSocketChannel::Read%1009995359.body
}

LONG_T cSocketChannel::Write (UCHAR_T *buffer, ULONG_T amount)
{
  //## begin cSocketChannel::Write%1009995360.body preserve=yes
   Connect();
   if (!_Connected) return amount;
   if (_Redirected) {
      return _StandardChannel->Write(buffer, amount);
   } else {
      int rc = send(_DataSocket, (char*)buffer, amount, 0);
      if (rc < 0) {
         _Connected = false;
         return 0;
      } else {
         if (_Verbose) PrintBuf((const char *)buffer, amount, CHANNEL_OUTPUT);
         return amount;
      }
   }
  //## end cSocketChannel::Write%1009995360.body
}

void cSocketChannel::FlushInput ()
{
  //## begin cSocketChannel::FlushInput%1009995361.body preserve=yes
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->FlushInput();
   } else {
    // 28.05.2002 -PR- Flush implementiert.
     _Receiver->Flush();
	 FlushInputBuffer();
   }
  //## end cSocketChannel::FlushInput%1009995361.body
}

void cSocketChannel::FlushOutput ()
{
  //## begin cSocketChannel::FlushOutput%1009995362.body preserve=yes
   Connect();
   if (!_Connected) return;
   if (_Redirected) {
      _StandardChannel->FlushOutput();
   } else {
   }
  //## end cSocketChannel::FlushOutput%1009995362.body
}

void cSocketChannel::Connect ()
{
  //## begin cSocketChannel::Connect%1017903089.body preserve=yes
   if (_Node->Reachable()) {
      if (!_Connected) Open();
   } else {
      if (_Connected) Close();
   }
  //## end cSocketChannel::Connect%1017903089.body
}

BOOL_T cSocketChannel::StartUp ()
{
  //## begin cSocketChannel::StartUp%1017825255.body preserve=yes
   cSockets::Initialize();
   return true;
  //## end cSocketChannel::StartUp%1017825255.body
}

BOOL_T cSocketChannel::SetSerialParams ()
{
  //## begin cSocketChannel::SetSerialParams%1018270344.body preserve=yes
   int rc = 0;
   int baud_rate = WTBaudRate(4, _BaudRate);
   char databits = _CharLen - 5;
   char stopbits = _StopBits - 1;
   char parity = 0;
   if (_Parity == None) {
      parity = 0x00;
   } else if (_Parity == Odd) {
      parity = 0x02;
   } else if (_Parity == Even) {
      parity = 0x03;
   }
   if (ConnectSocket(_ControlSocket, _ControlPort, false)) {
      if ((rc = send (_ControlSocket, (const char *)&_Control, 1, 0)) < 0) {
		 DisconnectSocket(_ControlSocket);
         InfoPrintf("Failed to set serial parameters on node %s/%d: error %d /1\n",
			        _IPAddress.c_str(), _ControlPort, WSAGetLastError());
         return false;
      }
   } else {
      InfoPrintf("Failed to set serial parameters on node %s/%d: unable to connect %d\n",
                 _IPAddress.c_str(), _ControlPort, WSAGetLastError());
      return false;
   }
   if ((rc = recv (_ControlSocket, (char *)&_Control, sizeof(_Control), 0)) < 0) {
      DisconnectSocket(_ControlSocket);
      InfoPrintf("Failed to set serial parameters on node %s/%d: error %d /2\n",
                 _IPAddress.c_str(), _ControlPort, WSAGetLastError());
      return false;
   }
   _Control._bc.cbaud_fifo.baud = baud_rate;
   char bits = databits | (stopbits << 2) | (parity << 3);
   _Control._bc.bits = bits;
   _Control._bc.ccommands.save_command = 1;   // Save without EEPROM Update
   _Control._bc.ccommands.clear_error = 1;    // Clear error in display/lamps
   _Control._bc.f_flags &= 0xff03;            // Soft- und Hardwarehandshake ausschalten
   if ((rc = send (_ControlSocket, (char *)&_Control, sizeof(_Control), 0)) < 0) {
      DisconnectSocket(_ControlSocket);
      InfoPrintf("Failed to set serial parameters on node %s/%d: error %d /3\n",
                 _IPAddress.c_str(), _ControlPort, WSAGetLastError());
      return false;
   }
   return true;
  //## end cSocketChannel::SetSerialParams%1018270344.body
}

BOOL_T cSocketChannel::FlushInputBuffer ()
{
  //## begin cSocketChannel::FlushInputBuffer%1018270345.body preserve=yes
   int rc = 0;
   if (ConnectSocket(_ControlSocket, _ControlPort, false)) {
      _Control._bc.ccommands.clear_error = 1;    // Clear error in display/lamps
      _Control._cs.com_flags &= 0x00ff;
      _Control._cs.com_flags |= 0x1800;          // Flush seriell input and output buffer
      if ((rc = send (_ControlSocket, (char *)&_Control, sizeof(_Control), 0)) < 0) {
         DisconnectSocket(_ControlSocket);
//         InfoPrintf("Failed to flush input buffer on node %s/%d: error %d /1\n",
//                     _IPAddress.c_str(), _ControlPort, WSAGetLastError());
         return false;
	  }
      if ((rc = recv (_ControlSocket, (char *)&_Control, sizeof(_Control), 0)) < 0) {
         DisconnectSocket(_ControlSocket);
//         InfoPrintf("Failed to flush input buffer on node %s/%d: error %d /2\n",
//                    _IPAddress.c_str(), _ControlPort, WSAGetLastError());
         return false;
	  }
      return true;
   } else {
      return false;
   }
  //## end cSocketChannel::FlushInputBuffer%1018270345.body
}

BOOL_T cSocketChannel::ConnectSocket (SOCKET &sock, ULONG_T port, BOOL_T always_new)
{
  //## begin cSocketChannel::ConnectSocket%1017825256.body preserve=yes
   if (always_new) DisconnectSocket(sock);
   if (sock == INVALID_SOCKET) {
      sock = socket(AF_INET, SOCK_STREAM, 0);
      if (sock == INVALID_SOCKET) {
         throw cError(SOCKET_CREATE, WSAGetLastError(), "W&TSocket");
      }
#if defined(_WIN32)
      unsigned long nonblocking = 0;
      ioctlsocket(sock, FIONBIO, &nonblocking);
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
      SOCKADDR_IN address;
      memset(&address, 0, sizeof(address));
      address.sin_family = AF_INET;
      address.sin_port = htons((unsigned int)port);
      address.sin_addr.s_addr = inet_addr(_IPAddress.c_str());
      if (address.sin_addr.s_addr == INADDR_NONE) {
         throw cError(SOCKET_CHANNEL_BAD_IP_ADDRESS, 0, _Name.c_str(), _IPAddress.c_str());
      }
      // 06.05.2002 -TE- Der folgende Workaround versucht das Problem der Dauer-Restarts
      // mancher Knoten anzugehen. Dieses tritt auf, wenn ein Knoten aus irgendeinem Grund
      // rueckgesetzt werden muss: Ein connect() waehrend der Ruecksetzphase liefert ein
      // WSAETIMEDOUT, was zu einem RestartNode() gefuehrt hat, was wiederum zu einem
      // Timeout-Fehler fuehrt, usw. (Unbestaetigte Vermutung: Der Restart eines Knotens
      // loest ein Restart aller anderen Knoten aus, was letztlich zu den minutenlangen
      // chaotischen Verhaeltnissen auf dem Netz gefuehrt hat.)

      // 14.05.2002 -PR- Dieser Workaround scheint technisch die beste Loesung zu sein.
      // Ich habe lediglich die Wartezeit auf 10 Sekunden erhoeht.

      int tmo = 10;
      while (connect(sock, (SOCKADDR*)&address, sizeof(address)) < 0) {
         int err = WSAGetLastError ();
         switch ( err ) {
         case WSAEISCONN:
            // no matter already connected
            return true;
         case WSAECONNREFUSED:
         case WSAENETUNREACH:
         case WSAETIMEDOUT:
            if ( --tmo > 0 ) {
               // 06.05.2002 -TE- Wait some time before connecting again to the socket. Refer to
               // SDK documentation for connect: "If the error code returned indicates the
               // connection attempt failed (that is, WSAECONNREFUSED, WSAENETUNREACH,
               // WSAETIMEDOUT) the application can call connect again for the same socket."
               cSystemUtils::Suspend(1000);
               InfoPrintf("Retrying connect for node %s/%d due to error %d ...\n", _IPAddress.c_str(), port, err);
               break;
			}
            // fall thru...
         default:
            InfoPrintf("Restarting node %s due to error %d ...\n", _IPAddress.c_str(), err);
            RestartNode();
            return false;
		 }
	  }
   }
   return true;
  //## end cSocketChannel::ConnectSocket%1017825256.body
}

BOOL_T cSocketChannel::DisconnectSocket (SOCKET &sock)
{
  //## begin cSocketChannel::DisconnectSocket%1018270346.body preserve=yes
   if (sock != INVALID_SOCKET) {
      closesocket(sock);
      sock = INVALID_SOCKET;
   }
   return true;
  //## end cSocketChannel::DisconnectSocket%1018270346.body
}

void cSocketChannel::RestartNode ()
{
  //## begin cSocketChannel::RestartNode%1018961942.body preserve=yes
   // 27.05.2002 -PR- Zum neu Starten des Knotens werden ab jetzt direkt
   //                 die Socket-Funktionen benutzt. (Gefahr der unendlichen
   //                 Rekursion)
   SOCKET admin_socket;
   admin_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (admin_socket == INVALID_SOCKET) {
      InfoPrintf("Failed to restart node %s failed to create admin socket error %d ...\n", _IPAddress.c_str(), WSAGetLastError());
      return; 
   }
#if defined(_WIN32)
   unsigned long nonblocking = 0;
   ioctlsocket(admin_socket, FIONBIO, &nonblocking);
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
   SOCKADDR_IN address;
   memset(&address, 0, sizeof(address));
   address.sin_family = AF_INET;
   address.sin_port = htons(_AdminPort);
   address.sin_addr.s_addr = inet_addr(_IPAddress.c_str());
   if (address.sin_addr.s_addr == INADDR_NONE) {
      InfoPrintf("Failed to restart node %s/%d no route to address...\n", _IPAddress.c_str(), _AdminPort);
      DisconnectSocket(admin_socket);
	  return;
   }
   if (connect(admin_socket, (SOCKADDR*)&address, sizeof(address)) < 0) {
      InfoPrintf("Failed to restart node %s/%d error %d ...\n", _IPAddress.c_str(), _AdminPort, WSAGetLastError());
   } else {
      InfoPrintf("Node %s restarted ..\n", _IPAddress.c_str());
   }
   DisconnectSocket(admin_socket);
  //## end cSocketChannel::RestartNode%1018961942.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSocketChannel::get_IPAddress () const
{
  //## begin cSocketChannel::get_IPAddress%3CAAC6FA011D.get preserve=no
  return _IPAddress;
  //## end cSocketChannel::get_IPAddress%3CAAC6FA011D.get
}

void cSocketChannel::set_IPAddress (STRING_T value)
{
  //## begin cSocketChannel::set_IPAddress%3CAAC6FA011D.set preserve=no
  _IPAddress = value;
  //## end cSocketChannel::set_IPAddress%3CAAC6FA011D.set
}

STRING_T cSocketChannel::get_SerialPort () const
{
  //## begin cSocketChannel::get_SerialPort%3CAC89A30323.get preserve=no
  return _SerialPort;
  //## end cSocketChannel::get_SerialPort%3CAC89A30323.get
}

void cSocketChannel::set_SerialPort (STRING_T value)
{
  //## begin cSocketChannel::set_SerialPort%3CAC89A30323.set preserve=no
  _SerialPort = value;
  //## end cSocketChannel::set_SerialPort%3CAC89A30323.set
}

BOOL_T cSocketChannel::get_Redirected () const
{
  //## begin cSocketChannel::get_Redirected%3CABF7CA0158.get preserve=no
  return _Redirected;
  //## end cSocketChannel::get_Redirected%3CABF7CA0158.get
}

void cSocketChannel::set_Redirected (BOOL_T value)
{
  //## begin cSocketChannel::set_Redirected%3CABF7CA0158.set preserve=no
  _Redirected = value;
  //## end cSocketChannel::set_Redirected%3CABF7CA0158.set
}

STRING_T cSocketChannel::get_ComPort () const
{
  //## begin cSocketChannel::get_ComPort%3CAAC78D0178.get preserve=no
  return _ComPort;
  //## end cSocketChannel::get_ComPort%3CAAC78D0178.get
}

void cSocketChannel::set_ComPort (STRING_T value)
{
  //## begin cSocketChannel::set_ComPort%3CAAC78D0178.set preserve=no
  _ComPort = value;
  //## end cSocketChannel::set_ComPort%3CAAC78D0178.set
}

// Additional Declarations
  //## begin cSocketChannel%3A6C140C0356.declarations preserve=yes
  //## end cSocketChannel%3A6C140C0356.declarations

//## begin module%3A6C140C0356.epilog preserve=yes
//## end module%3A6C140C0356.epilog
