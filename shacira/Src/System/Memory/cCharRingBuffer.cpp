//## begin module%3C348D8E0012.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C348D8E0012.cm

//## begin module%3C348D8E0012.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C348D8E0012.cp

//## Module: cCharRingBuffer%3C348D8E0012; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cCharRingBuffer.cpp

//## begin module%3C348D8E0012.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C348D8E0012.additionalIncludes

//## begin module%3C348D8E0012.includes preserve=yes
//## end module%3C348D8E0012.includes

// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
//## begin module%3C348D8E0012.additionalDeclarations preserve=yes
//## end module%3C348D8E0012.additionalDeclarations


// Class cCharRingBuffer 








cCharRingBuffer::cCharRingBuffer()
  //## begin cCharRingBuffer::cCharRingBuffer%.hasinit preserve=no
      : _Buffer(NULL), _BufferSize(0x2000), _ReadPtr(0), _WritePtr(0)
  //## end cCharRingBuffer::cCharRingBuffer%.hasinit
  //## begin cCharRingBuffer::cCharRingBuffer%.initialization preserve=yes
  //## end cCharRingBuffer::cCharRingBuffer%.initialization
{
  //## begin cCharRingBuffer::cCharRingBuffer%.body preserve=yes
   CreateBuffer();
  //## end cCharRingBuffer::cCharRingBuffer%.body
}

cCharRingBuffer::cCharRingBuffer(const cCharRingBuffer &right)
  //## begin cCharRingBuffer::cCharRingBuffer%copy.hasinit preserve=no
      : _Buffer(NULL), _BufferSize(0x2000), _ReadPtr(0), _WritePtr(0)
  //## end cCharRingBuffer::cCharRingBuffer%copy.hasinit
  //## begin cCharRingBuffer::cCharRingBuffer%copy.initialization preserve=yes
  //## end cCharRingBuffer::cCharRingBuffer%copy.initialization
{
  //## begin cCharRingBuffer::cCharRingBuffer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCharRingBuffer::cCharRingBuffer%copy.body
}

cCharRingBuffer::cCharRingBuffer (ULONG_T size)
  //## begin cCharRingBuffer::cCharRingBuffer%1010077552.hasinit preserve=no
      : _Buffer(NULL), _BufferSize(0x2000), _ReadPtr(0), _WritePtr(0)
  //## end cCharRingBuffer::cCharRingBuffer%1010077552.hasinit
  //## begin cCharRingBuffer::cCharRingBuffer%1010077552.initialization preserve=yes
  //## end cCharRingBuffer::cCharRingBuffer%1010077552.initialization
{
  //## begin cCharRingBuffer::cCharRingBuffer%1010077552.body preserve=yes
   _BufferSize = size;
   CreateBuffer();
  //## end cCharRingBuffer::cCharRingBuffer%1010077552.body
}


cCharRingBuffer::~cCharRingBuffer()
{
  //## begin cCharRingBuffer::~cCharRingBuffer%.body preserve=yes
   if (_Buffer != NULL) cSystemUtils::Free((void*)_Buffer);;
  //## end cCharRingBuffer::~cCharRingBuffer%.body
}



//## Other Operations (implementation)
ULONG_T cCharRingBuffer::Put (CONST_STRING_T buffer, ULONG_T amount)
{
  //## begin cCharRingBuffer::Put%1010077553.body preserve=yes
   ULONG_T space = Space();
   if (amount > space) {
      amount = space;
      buffer += (amount - space);
   }
   for (ULONG_T i=0; i<amount; i++) {
      _Buffer[_WritePtr] = buffer[i];
      _WritePtr++;
      if (_WritePtr == _BufferSize) {
         _WritePtr = 0;
      }
   }
   return amount;
  //## end cCharRingBuffer::Put%1010077553.body
}

ULONG_T cCharRingBuffer::Get (STRING_BUF_T buffer, ULONG_T amount)
{
  //## begin cCharRingBuffer::Get%1010077554.body preserve=yes
   ULONG_T fill = Fill();
   if (fill < amount) {
      amount = fill;
   }
   for (ULONG_T i=0; i<amount; i++) {
      buffer[i] = _Buffer[_ReadPtr];
      _ReadPtr++;
      if (_ReadPtr == _BufferSize) {
         _ReadPtr = 0;
      }
   }
   return amount;
  //## end cCharRingBuffer::Get%1010077554.body
}

void cCharRingBuffer::Clear ()
{
  //## begin cCharRingBuffer::Clear%1010131285.body preserve=yes
   _ReadPtr = _WritePtr = 0;
  //## end cCharRingBuffer::Clear%1010131285.body
}

BOOL_T cCharRingBuffer::IsEmpty ()
{
  //## begin cCharRingBuffer::IsEmpty%1010077555.body preserve=yes
   return (_ReadPtr == _WritePtr);
  //## end cCharRingBuffer::IsEmpty%1010077555.body
}

void cCharRingBuffer::CreateBuffer ()
{
  //## begin cCharRingBuffer::CreateBuffer%1091549391.body preserve=yes
   _Buffer = (STRING_BUF_T)cSystemUtils::Alloc(_BufferSize+1);
  //## end cCharRingBuffer::CreateBuffer%1091549391.body
}

ULONG_T cCharRingBuffer::Space ()
{
  //## begin cCharRingBuffer::Space%1091549392.body preserve=yes
   if (_ReadPtr == _WritePtr) {
      return _BufferSize;
   } else if (_ReadPtr < _WritePtr) {
      return (_BufferSize - _WritePtr) + _ReadPtr;
   } else {
      return _ReadPtr - _WritePtr;
   }
  //## end cCharRingBuffer::Space%1091549392.body
}

ULONG_T cCharRingBuffer::Fill ()
{
  //## begin cCharRingBuffer::Fill%1091549393.body preserve=yes
   return _BufferSize - Space();
  //## end cCharRingBuffer::Fill%1091549393.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_BUF_T cCharRingBuffer::get_Buffer () const
{
  //## begin cCharRingBuffer::get_Buffer%3C348DD5010E.get preserve=no
  return _Buffer;
  //## end cCharRingBuffer::get_Buffer%3C348DD5010E.get
}

ULONG_T cCharRingBuffer::get_BufferSize () const
{
  //## begin cCharRingBuffer::get_BufferSize%410FB86C0203.get preserve=no
  return _BufferSize;
  //## end cCharRingBuffer::get_BufferSize%410FB86C0203.get
}

// Additional Declarations
  //## begin cCharRingBuffer%3C348D8E0012.declarations preserve=yes
  //## end cCharRingBuffer%3C348D8E0012.declarations

//## begin module%3C348D8E0012.epilog preserve=yes
//## end module%3C348D8E0012.epilog
