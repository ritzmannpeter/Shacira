//## begin module%3ABF397B02F1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABF397B02F1.cm

//## begin module%3ABF397B02F1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3ABF397B02F1.cp

//## Module: cObjectBuffer%3ABF397B02F1; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectBuffer.cpp

//## begin module%3ABF397B02F1.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3ABF397B02F1.additionalIncludes

//## begin module%3ABF397B02F1.includes preserve=yes
//## end module%3ABF397B02F1.includes

// cObjectBuffer
#include "System/Objects/cObjectBuffer.h"
// cTransientObject
#include "System/Objects/cTransientObject.h"
//## begin module%3ABF397B02F1.additionalDeclarations preserve=yes
//## end module%3ABF397B02F1.additionalDeclarations


// Class cObjectBuffer 



cObjectBuffer::cObjectBuffer()
  //## begin cObjectBuffer::cObjectBuffer%.hasinit preserve=no
  //## end cObjectBuffer::cObjectBuffer%.hasinit
  //## begin cObjectBuffer::cObjectBuffer%.initialization preserve=yes
   : _Queue(1)
  //## end cObjectBuffer::cObjectBuffer%.initialization
{
  //## begin cObjectBuffer::cObjectBuffer%.body preserve=yes
  //## end cObjectBuffer::cObjectBuffer%.body
}

cObjectBuffer::cObjectBuffer(const cObjectBuffer &right)
  //## begin cObjectBuffer::cObjectBuffer%copy.hasinit preserve=no
  //## end cObjectBuffer::cObjectBuffer%copy.hasinit
  //## begin cObjectBuffer::cObjectBuffer%copy.initialization preserve=yes
   : _Queue(right.Size())
  //## end cObjectBuffer::cObjectBuffer%copy.initialization
{
  //## begin cObjectBuffer::cObjectBuffer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cObjectBuffer::cObjectBuffer%copy.body
}

cObjectBuffer::cObjectBuffer (ULONG_T size, QMode mode)
  //## begin cObjectBuffer::cObjectBuffer%985610909.hasinit preserve=no
  //## end cObjectBuffer::cObjectBuffer%985610909.hasinit
  //## begin cObjectBuffer::cObjectBuffer%985610909.initialization preserve=yes
   : _Queue(size, mode)
  //## end cObjectBuffer::cObjectBuffer%985610909.initialization
{
  //## begin cObjectBuffer::cObjectBuffer%985610909.body preserve=yes
  //## end cObjectBuffer::cObjectBuffer%985610909.body
}


cObjectBuffer::~cObjectBuffer()
{
  //## begin cObjectBuffer::~cObjectBuffer%.body preserve=yes
   cTransientObject * object = NULL;
   while ((object = GetNext()) != NULL) {
      RELEASE_OBJECT(object)
   }
  //## end cObjectBuffer::~cObjectBuffer%.body
}



//## Other Operations (implementation)
BOOL_T cObjectBuffer::Add (cTransientObject *object)
{
  //## begin cObjectBuffer::Add%985610910.body preserve=yes
   _Queue.put(object);
   return true;
  //## end cObjectBuffer::Add%985610910.body
}

cTransientObject * cObjectBuffer::GetNext (BOOL_T wait)
{
  //## begin cObjectBuffer::GetNext%985610911.body preserve=yes
   if (IsEmpty() && !wait) {
      return NULL;
   } else {
      return _Queue.get();
   }
  //## end cObjectBuffer::GetNext%985610911.body
}

ULONG_T cObjectBuffer::Size () const
{
  //## begin cObjectBuffer::Size%985610912.body preserve=yes
   return _Queue.getCount();
  //## end cObjectBuffer::Size%985610912.body
}

ULONG_T cObjectBuffer::Elements () const
{
  //## begin cObjectBuffer::Elements%985610923.body preserve=yes
   return _Queue.getUsed();
  //## end cObjectBuffer::Elements%985610923.body
}

BOOL_T cObjectBuffer::IsFull () const
{
  //## begin cObjectBuffer::IsFull%985610913.body preserve=yes
   return _Queue.isFull();
  //## end cObjectBuffer::IsFull%985610913.body
}

BOOL_T cObjectBuffer::IsEmpty () const
{
  //## begin cObjectBuffer::IsEmpty%985610914.body preserve=yes
   return _Queue.isEmpty();
  //## end cObjectBuffer::IsEmpty%985610914.body
}

// Additional Declarations
  //## begin cObjectBuffer%3ABF397B02F1.declarations preserve=yes
  //## end cObjectBuffer%3ABF397B02F1.declarations

//## begin module%3ABF397B02F1.epilog preserve=yes
//## end module%3ABF397B02F1.epilog
