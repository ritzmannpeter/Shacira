
#include "chunkbuffer.h"
#include "alloc.h"
#include <string.h>

cChunkBuffer::cChunkBuffer(int chunkSize)
   : _chunkSize(chunkSize), _size(0), _used(0)
{
   _buffer = (unsigned char*)cAlloc::allocbuffer(_chunkSize);
   _size = _chunkSize;
}

cChunkBuffer::~cChunkBuffer()
{
   cAlloc::freebuffer(_buffer);
}

bool cChunkBuffer::add(unsigned char * buf, int size)
{
   int freeSpace = _size - _used;
   if (size <= freeSpace) {
      unsigned char * buf_ptr = &(_buffer[_used]);
      memcpy(buf_ptr, buf, size);
      _used += size;
   } else {
      expand(freeSpace, size);
      add(buf, size);
   }
   return true;
}

void cChunkBuffer::reset()
{
   memset(_buffer, 0, _size);
   _used = 0;
}

void cChunkBuffer::expand(int freeSpace, int requiredSpace)
{
   int total_size = _used + freeSpace + requiredSpace + _chunkSize;
   unsigned char * old_buffer = _buffer;
   unsigned char * new_buffer = (unsigned char*)cAlloc::allocbuffer(total_size);
   memcpy(new_buffer, _buffer, _used);
   _buffer = new_buffer;
   _size = total_size;
   cAlloc::freebuffer(old_buffer);
}


