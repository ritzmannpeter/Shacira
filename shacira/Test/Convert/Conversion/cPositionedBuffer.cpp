
#include "FirstHeader.h"
#include "cPositionedBuffer.h"

cPositionedBuffer::cPositionedBuffer(ULONG_T size)
{
   _Buf = cSystemUtils::Alloc(size);
   _BufSize = size;
   _BufPos = 0;
}

cPositionedBuffer::~cPositionedBuffer()
{
   cSystemUtils::Free(_Buf);
}

void * cPositionedBuffer::Buffer()
{
   return _Buf;
}

ULONG_T cPositionedBuffer::Size()
{
   return _BufSize;
}

ULONG_T cPositionedBuffer::Pos()
{
   return _BufPos;
}

BOOL_T cPositionedBuffer::Set(void * buf, ULONG_T size)
{
   if (size > _BufSize) {
      return false;
   } else {
      memcpy(_Buf, buf, size);
      return true;
   }
}

BOOL_T cPositionedBuffer::Get(void * buf, ULONG_T size)
{
   if ((_BufPos + size) <= _BufSize) {
      const void * src_ptr = &(((UCHAR_T*)_Buf)[_BufPos]);
      memcpy(buf, src_ptr, size);
      _BufPos += size;
      return true;
   } else {
      return false;
   }
}

BOOL_T cPositionedBuffer::Seek(ULONG_T pos)
{
   if (pos < _BufSize) {
      _BufPos = pos;
      return true;
   } else {
      return false;
   }
}


