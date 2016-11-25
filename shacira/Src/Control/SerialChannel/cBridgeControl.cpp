//## begin module%3FBCC1D6009C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBCC1D6009C.cm

//## begin module%3FBCC1D6009C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBCC1D6009C.cp

//## Module: cBridgeControl%3FBCC1D6009C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cBridgeControl.cpp

//## begin module%3FBCC1D6009C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FBCC1D6009C.additionalIncludes

//## begin module%3FBCC1D6009C.includes preserve=yes
//## end module%3FBCC1D6009C.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cBridgeControl
#include "Control/SerialChannel/cBridgeControl.h"
// cSerialBridge
#include "Control/SerialChannel/cSerialBridge.h"
//## begin module%3FBCC1D6009C.additionalDeclarations preserve=yes
//## end module%3FBCC1D6009C.additionalDeclarations


// Class cBridgeControl 






cBridgeControl::cBridgeControl()
  //## begin cBridgeControl::cBridgeControl%.hasinit preserve=no
      : _Bridge(NULL), _Input(NULL), _Output(NULL)
  //## end cBridgeControl::cBridgeControl%.hasinit
  //## begin cBridgeControl::cBridgeControl%.initialization preserve=yes
  //## end cBridgeControl::cBridgeControl%.initialization
{
  //## begin cBridgeControl::cBridgeControl%.body preserve=yes
_ASSERT_UNCOND
  //## end cBridgeControl::cBridgeControl%.body
}

cBridgeControl::cBridgeControl(const cBridgeControl &right)
  //## begin cBridgeControl::cBridgeControl%copy.hasinit preserve=no
      : _Bridge(NULL), _Input(NULL), _Output(NULL)
  //## end cBridgeControl::cBridgeControl%copy.hasinit
  //## begin cBridgeControl::cBridgeControl%copy.initialization preserve=yes
  //## end cBridgeControl::cBridgeControl%copy.initialization
{
  //## begin cBridgeControl::cBridgeControl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBridgeControl::cBridgeControl%copy.body
}

cBridgeControl::cBridgeControl (cSerialChannel *input, cSerialChannel *output, cSerialBridge *bridge)
  //## begin cBridgeControl::cBridgeControl%1069326617.hasinit preserve=no
      : _Bridge(NULL), _Input(NULL), _Output(NULL)
  //## end cBridgeControl::cBridgeControl%1069326617.hasinit
  //## begin cBridgeControl::cBridgeControl%1069326617.initialization preserve=yes
  //## end cBridgeControl::cBridgeControl%1069326617.initialization
{
  //## begin cBridgeControl::cBridgeControl%1069326617.body preserve=yes
   _Input = input;
   _Output = output;
   _Bridge = bridge;
   cControlThread::Start();
  //## end cBridgeControl::cBridgeControl%1069326617.body
}


cBridgeControl::~cBridgeControl()
{
  //## begin cBridgeControl::~cBridgeControl%.body preserve=yes
  //## end cBridgeControl::~cBridgeControl%.body
}



//## Other Operations (implementation)
INT_T cBridgeControl::MainFunc (void *extra)
{
  //## begin cBridgeControl::MainFunc%1069326618.body preserve=yes
   unsigned char buffer[300] = {0};
   int nread = 0;
MAINFUNC_PROLOG(_Name.c_str())
   while (true) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      _Bridge->_IOMutex.request();
      nread = _Input->Read(buffer, sizeof(buffer), 15);
      for (int i=0; i< nread; i++) {
         if (buffer[i] == ENQ) {
            printf("busy\n");
         }
         if (buffer[i] == EOT) {
            printf("idle\n");
         }
      }
      _Bridge->_IOMutex.release();
      if (nread > 0) {
         _Bridge->_IOMutex.request();
         _Output->Write(buffer, nread);
         _Bridge->_IOMutex.release();
      }
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cBridgeControl::MainFunc%1069326618.body
}

// Additional Declarations
  //## begin cBridgeControl%3FBCC1D6009C.declarations preserve=yes
  //## end cBridgeControl%3FBCC1D6009C.declarations

//## begin module%3FBCC1D6009C.epilog preserve=yes
//## end module%3FBCC1D6009C.epilog
