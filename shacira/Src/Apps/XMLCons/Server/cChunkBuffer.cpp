
#include <string.h>
#include "cChunkBuffer.h"
#include "cAlloc.h"

cChunkBuffer::cChunkBuffer(int chunk_size)
   : _ChunkSize(chunk_size), _Size(0), _Used(0)
{
   _Buffer = (unsigned char*)cAlloc::Alloc(_ChunkSize);
   _Size = _ChunkSize;
}

cChunkBuffer::~cChunkBuffer()
{
   cAlloc::Free(_Buffer);
}

bool cChunkBuffer::Add(unsigned char * buf, int size)
{
   int free_space = _Size - _Used;
   if (size <= free_space) {
      unsigned char * buf_ptr = &(_Buffer[_Used]);
      memcpy(buf_ptr, buf, size);
      _Used += size;
   } else {
      Expand(free_space, size);
      Add(buf, size);
   }
   return true;
}

void cChunkBuffer::Reset()
{
   memset(_Buffer, 0, _Size);
   _Used = 0;
}

void cChunkBuffer::Expand(int free_space, int required_space)
{
   int total_size = _Used + free_space + required_space + _ChunkSize;
   unsigned char * old_buffer = _Buffer;
   unsigned char * new_buffer = (unsigned char*)cAlloc::Alloc(total_size);
   memcpy(new_buffer, _Buffer, _Used);
   _Buffer = new_buffer;
   _Size = total_size;
   cAlloc::Free(old_buffer);
}


