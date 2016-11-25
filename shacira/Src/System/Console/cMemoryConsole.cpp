//## begin module%3DD37DAE031A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD37DAE031A.cm

//## begin module%3DD37DAE031A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD37DAE031A.cp

//## Module: cMemoryConsole%3DD37DAE031A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cMemoryConsole.cpp

//## begin module%3DD37DAE031A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD37DAE031A.additionalIncludes

//## begin module%3DD37DAE031A.includes preserve=yes
//## end module%3DD37DAE031A.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
// cMemoryConsole
#include "System/Console/cMemoryConsole.h"
//## begin module%3DD37DAE031A.additionalDeclarations preserve=yes
//## end module%3DD37DAE031A.additionalDeclarations


// Class cMemoryConsole 


cMemoryConsole::cMemoryConsole()
  //## begin cMemoryConsole::cMemoryConsole%.hasinit preserve=no
      : _Buffer(NULL)
  //## end cMemoryConsole::cMemoryConsole%.hasinit
  //## begin cMemoryConsole::cMemoryConsole%.initialization preserve=yes
  , cConsole(DIRECTION_BOTH)
  //## end cMemoryConsole::cMemoryConsole%.initialization
{
  //## begin cMemoryConsole::cMemoryConsole%.body preserve=yes
   _Buffer = new cCharRingBuffer(2048);
  //## end cMemoryConsole::cMemoryConsole%.body
}

cMemoryConsole::cMemoryConsole(const cMemoryConsole &right)
  //## begin cMemoryConsole::cMemoryConsole%copy.hasinit preserve=no
      : _Buffer(NULL)
  //## end cMemoryConsole::cMemoryConsole%copy.hasinit
  //## begin cMemoryConsole::cMemoryConsole%copy.initialization preserve=yes
  //## end cMemoryConsole::cMemoryConsole%copy.initialization
{
  //## begin cMemoryConsole::cMemoryConsole%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cMemoryConsole::cMemoryConsole%copy.body
}

cMemoryConsole::cMemoryConsole (ULONG_T buf_size)
  //## begin cMemoryConsole::cMemoryConsole%1037267672.hasinit preserve=no
      : _Buffer(NULL)
  //## end cMemoryConsole::cMemoryConsole%1037267672.hasinit
  //## begin cMemoryConsole::cMemoryConsole%1037267672.initialization preserve=yes
  , cConsole(DIRECTION_BOTH)
  //## end cMemoryConsole::cMemoryConsole%1037267672.initialization
{
  //## begin cMemoryConsole::cMemoryConsole%1037267672.body preserve=yes
   _Buffer = new cCharRingBuffer(buf_size);
  //## end cMemoryConsole::cMemoryConsole%1037267672.body
}


cMemoryConsole::~cMemoryConsole()
{
  //## begin cMemoryConsole::~cMemoryConsole%.body preserve=yes
   if (_Buffer != NULL) DELETE_OBJECT(cCharRingBuffer, _Buffer)
  //## end cMemoryConsole::~cMemoryConsole%.body
}



//## Other Operations (implementation)
void cMemoryConsole::Write (CONST_STRING_T text)
{
  //## begin cMemoryConsole::Write%1037267673.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   _Buffer->Put(text, strlen(text));
  //## end cMemoryConsole::Write%1037267673.body
}

LONG_T cMemoryConsole::Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cMemoryConsole::Read%1037267674.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   return _Buffer->Get(buf, buf_size);;
  //## end cMemoryConsole::Read%1037267674.body
}

void cMemoryConsole::FlushInput ()
{
  //## begin cMemoryConsole::FlushInput%1037267675.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   _Buffer->Clear();
  //## end cMemoryConsole::FlushInput%1037267675.body
}

void cMemoryConsole::FlushOutput ()
{
  //## begin cMemoryConsole::FlushOutput%1037267676.body preserve=yes
  //## end cMemoryConsole::FlushOutput%1037267676.body
}

// Additional Declarations
  //## begin cMemoryConsole%3DD37DAE031A.declarations preserve=yes
  //## end cMemoryConsole%3DD37DAE031A.declarations

//## begin module%3DD37DAE031A.epilog preserve=yes
//## end module%3DD37DAE031A.epilog
