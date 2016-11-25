//## begin module%41089B84003E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41089B84003E.cm

//## begin module%41089B84003E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41089B84003E.cp

//## Module: cPPCSerialComm%41089B84003E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCSerialComm.cpp

//## begin module%41089B84003E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41089B84003E.additionalIncludes

//## begin module%41089B84003E.includes preserve=yes
//## end module%41089B84003E.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cPPCSerialComm
#include "Control/Device/PPCCom/cPPCSerialComm.h"
//## begin module%41089B84003E.additionalDeclarations preserve=yes
//## end module%41089B84003E.additionalDeclarations


// Class cPPCSerialComm 


cPPCSerialComm::cPPCSerialComm()
  //## begin cPPCSerialComm::cPPCSerialComm%.hasinit preserve=no
      : _SerialCjhannel(NULL)
  //## end cPPCSerialComm::cPPCSerialComm%.hasinit
  //## begin cPPCSerialComm::cPPCSerialComm%.initialization preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%.initialization
{
  //## begin cPPCSerialComm::cPPCSerialComm%.body preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%.body
}

cPPCSerialComm::cPPCSerialComm(const cPPCSerialComm &right)
  //## begin cPPCSerialComm::cPPCSerialComm%copy.hasinit preserve=no
      : _SerialCjhannel(NULL)
  //## end cPPCSerialComm::cPPCSerialComm%copy.hasinit
  //## begin cPPCSerialComm::cPPCSerialComm%copy.initialization preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%copy.initialization
{
  //## begin cPPCSerialComm::cPPCSerialComm%copy.body preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%copy.body
}

cPPCSerialComm::cPPCSerialComm (cSerialChannel *serial_channel)
  //## begin cPPCSerialComm::cPPCSerialComm%1091082169.hasinit preserve=no
      : _SerialCjhannel(NULL)
  //## end cPPCSerialComm::cPPCSerialComm%1091082169.hasinit
  //## begin cPPCSerialComm::cPPCSerialComm%1091082169.initialization preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%1091082169.initialization
{
  //## begin cPPCSerialComm::cPPCSerialComm%1091082169.body preserve=yes
  //## end cPPCSerialComm::cPPCSerialComm%1091082169.body
}


cPPCSerialComm::~cPPCSerialComm()
{
  //## begin cPPCSerialComm::~cPPCSerialComm%.body preserve=yes
  //## end cPPCSerialComm::~cPPCSerialComm%.body
}



//## Other Operations (implementation)
void cPPCSerialComm::Send (cCSMsg *msg, cCSAddress *address)
{
  //## begin cPPCSerialComm::Send%1091082170.body preserve=yes
  //## end cPPCSerialComm::Send%1091082170.body
}

void cPPCSerialComm::Reply (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cPPCSerialComm::Reply%1091082171.body preserve=yes
  //## end cPPCSerialComm::Reply%1091082171.body
}

void cPPCSerialComm::Receive (cCSMsg &msg, cCSAddress *sender_address, ULONG_T tmo)
{
  //## begin cPPCSerialComm::Receive%1091082172.body preserve=yes
  //## end cPPCSerialComm::Receive%1091082172.body
}

cCSAddress * cPPCSerialComm::ReadAddress ()
{
  //## begin cPPCSerialComm::ReadAddress%1091085014.body preserve=yes
   return NULL;
  //## end cPPCSerialComm::ReadAddress%1091085014.body
}

cCSAddress * cPPCSerialComm::WriteAddress ()
{
  //## begin cPPCSerialComm::WriteAddress%1091085015.body preserve=yes
   return NULL;
  //## end cPPCSerialComm::WriteAddress%1091085015.body
}

void cPPCSerialComm::SetReadTimeout (ULONG_T tmo)
{
  //## begin cPPCSerialComm::SetReadTimeout%1091082173.body preserve=yes
  //## end cPPCSerialComm::SetReadTimeout%1091082173.body
}

// Additional Declarations
  //## begin cPPCSerialComm%41089B84003E.declarations preserve=yes
  //## end cPPCSerialComm%41089B84003E.declarations

//## begin module%41089B84003E.epilog preserve=yes
//## end module%41089B84003E.epilog
