//## begin module%3AC4C3880219.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC4C3880219.cm

//## begin module%3AC4C3880219.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AC4C3880219.cp

//## Module: cObjectQueue%3AC4C3880219; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectQueue.cpp

//## begin module%3AC4C3880219.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AC4C3880219.additionalIncludes

//## begin module%3AC4C3880219.includes preserve=yes
//## end module%3AC4C3880219.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cObjectQueue
#include "System/Objects/cObjectQueue.h"
//## begin module%3AC4C3880219.additionalDeclarations preserve=yes
//## end module%3AC4C3880219.additionalDeclarations


// Class cObjectQueue 



cObjectQueue::cObjectQueue()
  //## begin cObjectQueue::cObjectQueue%.hasinit preserve=no
  //## end cObjectQueue::cObjectQueue%.hasinit
  //## begin cObjectQueue::cObjectQueue%.initialization preserve=yes
   : cObjectBuffer(10, QOverwrite)
  //## end cObjectQueue::cObjectQueue%.initialization
{
  //## begin cObjectQueue::cObjectQueue%.body preserve=yes
  //## end cObjectQueue::cObjectQueue%.body
}

cObjectQueue::cObjectQueue(const cObjectQueue &right)
  //## begin cObjectQueue::cObjectQueue%copy.hasinit preserve=no
  //## end cObjectQueue::cObjectQueue%copy.hasinit
  //## begin cObjectQueue::cObjectQueue%copy.initialization preserve=yes
  //## end cObjectQueue::cObjectQueue%copy.initialization
{
  //## begin cObjectQueue::cObjectQueue%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cObjectQueue::cObjectQueue%copy.body
}

cObjectQueue::cObjectQueue (ULONG_T size, QMode mode)
  //## begin cObjectQueue::cObjectQueue%985973979.hasinit preserve=no
  //## end cObjectQueue::cObjectQueue%985973979.hasinit
  //## begin cObjectQueue::cObjectQueue%985973979.initialization preserve=yes
   : cObjectBuffer(size, mode)
  //## end cObjectQueue::cObjectQueue%985973979.initialization
{
  //## begin cObjectQueue::cObjectQueue%985973979.body preserve=yes
  //## end cObjectQueue::cObjectQueue%985973979.body
}


cObjectQueue::~cObjectQueue()
{
  //## begin cObjectQueue::~cObjectQueue%.body preserve=yes
  //## end cObjectQueue::~cObjectQueue%.body
}



//## Other Operations (implementation)
BOOL_T cObjectQueue::Add (cTransientObject *object)
{
  //## begin cObjectQueue::Add%985973981.body preserve=yes
   if (IsFull()) {
      return false;
   } else {
      object->AddRef();
      cObjectBuffer::Add(object);
      return true;
   }
  //## end cObjectQueue::Add%985973981.body
}

cTransientObject * cObjectQueue::GetNext (BOOL_T wait)
{
  //## begin cObjectQueue::GetNext%985973980.body preserve=yes
   return cObjectBuffer::GetNext(wait);
  //## end cObjectQueue::GetNext%985973980.body
}

// Additional Declarations
  //## begin cObjectQueue%3AC4C3880219.declarations preserve=yes
  //## end cObjectQueue%3AC4C3880219.declarations

//## begin module%3AC4C3880219.epilog preserve=yes
//## end module%3AC4C3880219.epilog
