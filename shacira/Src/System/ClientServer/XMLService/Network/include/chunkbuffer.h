
#ifndef _chunkbuffer_h
#define _chunkbuffer_h

#include "comm.h"

#define DEFAULT_CHUNK_SIZE    0x8000

class COMM_EXPORT cChunkBuffer
{
public:
   cChunkBuffer(int chunkSize = DEFAULT_CHUNK_SIZE);
   virtual ~cChunkBuffer();
   inline unsigned char * buffer() {return _buffer;};
   inline int chunkSize() {return _chunkSize;};
   inline int size() {return _size;};
   inline int used() {return _used;};
   bool add(unsigned char * buf, int size);
   void reset();
private:
   void expand(int free_space, int required_space);
private:
   unsigned char * _buffer;
   int _chunkSize;
   int _size;
   int _used;
};

#endif
