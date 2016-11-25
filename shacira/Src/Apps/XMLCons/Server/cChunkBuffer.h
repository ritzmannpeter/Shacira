
#ifndef _cChunkBuffer_h
#define _cChunkBuffer_h

class cChunkBuffer
{
public:
   cChunkBuffer(int chunk_size);
   virtual ~cChunkBuffer();
   inline unsigned char * Buffer() {return _Buffer;};
   inline int ChunkSize() {return _ChunkSize;};
   inline int Size() {return _Size;};
   inline int Used() {return _Used;};
   bool Add(unsigned char * buf, int size);
   void Reset();
private:
   void Expand(int free_space, int required_space);
private:
   unsigned char * _Buffer;
   int _ChunkSize;
   int _Size;
   int _Used;
};

#endif
