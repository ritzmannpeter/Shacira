//## begin module%3C3440B80004.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C3440B80004.cm

//## begin module%3C3440B80004.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C3440B80004.cp

//## Module: cCharReceiver%3C3440B80004; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cCharReceiver.cpp

//## begin module%3C3440B80004.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C3440B80004.additionalIncludes

//## begin module%3C3440B80004.includes preserve=yes
//## end module%3C3440B80004.includes

// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
// cCharReceiver
#include "Control/SerialChannel/cCharReceiver.h"
//## begin module%3C3440B80004.additionalDeclarations preserve=yes
//## end module%3C3440B80004.additionalDeclarations


// Class cCharReceiver 




cCharReceiver::cCharReceiver()
  //## begin cCharReceiver::cCharReceiver%.hasinit preserve=no
      : _RingBuffer(NULL)
  //## end cCharReceiver::cCharReceiver%.hasinit
  //## begin cCharReceiver::cCharReceiver%.initialization preserve=yes
  //## end cCharReceiver::cCharReceiver%.initialization
{
  //## begin cCharReceiver::cCharReceiver%.body preserve=yes
   _RingBuffer = new cCharRingBuffer;
  //## end cCharReceiver::cCharReceiver%.body
}

cCharReceiver::cCharReceiver(const cCharReceiver &right)
  //## begin cCharReceiver::cCharReceiver%copy.hasinit preserve=no
      : _RingBuffer(NULL)
  //## end cCharReceiver::cCharReceiver%copy.hasinit
  //## begin cCharReceiver::cCharReceiver%copy.initialization preserve=yes
  //## end cCharReceiver::cCharReceiver%copy.initialization
{
  //## begin cCharReceiver::cCharReceiver%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCharReceiver::cCharReceiver%copy.body
}


cCharReceiver::~cCharReceiver()
{
  //## begin cCharReceiver::~cCharReceiver%.body preserve=yes
   if (_RingBuffer != NULL) delete _RingBuffer;
  //## end cCharReceiver::~cCharReceiver%.body
}


// Additional Declarations
  //## begin cCharReceiver%3C3440B80004.declarations preserve=yes
  //## end cCharReceiver%3C3440B80004.declarations

//## begin module%3C3440B80004.epilog preserve=yes
//## end module%3C3440B80004.epilog
