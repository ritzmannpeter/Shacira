//## begin module%3FBC9F43000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBC9F43000F.cm

//## begin module%3FBC9F43000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBC9F43000F.cp

//## Module: cSerialBridge%3FBC9F43000F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialBridge.cpp

//## begin module%3FBC9F43000F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FBC9F43000F.additionalIncludes

//## begin module%3FBC9F43000F.includes preserve=yes
//## end module%3FBC9F43000F.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cBridgeControl
#include "Control/SerialChannel/cBridgeControl.h"
// cMultiplexer
#include "Control/SerialChannel/cMultiplexer.h"
// cSerialBridge
#include "Control/SerialChannel/cSerialBridge.h"
//## begin module%3FBC9F43000F.additionalDeclarations preserve=yes
//## end module%3FBC9F43000F.additionalDeclarations


// Class cSerialBridge 








cSerialBridge::cSerialBridge()
  //## begin cSerialBridge::cSerialBridge%.hasinit preserve=no
      : _Multiplexer(NULL), _Front(NULL), _Back(NULL), _InputControl(NULL), _OutputControl(NULL)
  //## end cSerialBridge::cSerialBridge%.hasinit
  //## begin cSerialBridge::cSerialBridge%.initialization preserve=yes
  //## end cSerialBridge::cSerialBridge%.initialization
{
  //## begin cSerialBridge::cSerialBridge%.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialBridge::cSerialBridge%.body
}

cSerialBridge::cSerialBridge(const cSerialBridge &right)
  //## begin cSerialBridge::cSerialBridge%copy.hasinit preserve=no
      : _Multiplexer(NULL), _Front(NULL), _Back(NULL), _InputControl(NULL), _OutputControl(NULL)
  //## end cSerialBridge::cSerialBridge%copy.hasinit
  //## begin cSerialBridge::cSerialBridge%copy.initialization preserve=yes
  //## end cSerialBridge::cSerialBridge%copy.initialization
{
  //## begin cSerialBridge::cSerialBridge%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSerialBridge::cSerialBridge%copy.body
}

cSerialBridge::cSerialBridge (cSerialChannel *front, cSerialChannel *back)
  //## begin cSerialBridge::cSerialBridge%1069326590.hasinit preserve=no
      : _Multiplexer(NULL), _Front(NULL), _Back(NULL), _InputControl(NULL), _OutputControl(NULL)
  //## end cSerialBridge::cSerialBridge%1069326590.hasinit
  //## begin cSerialBridge::cSerialBridge%1069326590.initialization preserve=yes
  //## end cSerialBridge::cSerialBridge%1069326590.initialization
{
  //## begin cSerialBridge::cSerialBridge%1069326590.body preserve=yes
   _Front = front;
   _Back = back;
   _InputControl = new cBridgeControl(_Front, _Back, this);
   _OutputControl = new cBridgeControl(_Back, _Front, this);
  //## end cSerialBridge::cSerialBridge%1069326590.body
}


cSerialBridge::~cSerialBridge()
{
  //## begin cSerialBridge::~cSerialBridge%.body preserve=yes
  //## end cSerialBridge::~cSerialBridge%.body
}


// Additional Declarations
  //## begin cSerialBridge%3FBC9F43000F.declarations preserve=yes
  //## end cSerialBridge%3FBC9F43000F.declarations

//## begin module%3FBC9F43000F.epilog preserve=yes
//## end module%3FBC9F43000F.epilog
