
#ifndef _cPositionedBuffer_h_
#define _cPositionedBuffer_h_

class cPositionedBuffer {
public:
   cPositionedBuffer(ULONG_T size);
   virtual ~cPositionedBuffer();
   void * Buffer();
   ULONG_T Size();
   ULONG_T Pos();
   BOOL_T Set(void * buf, ULONG_T size);
   BOOL_T Get(void * buf, ULONG_T size);
   BOOL_T Seek(ULONG_T pos);
private:
   ULONG_T _BufSize;
   void * _Buf;
   ULONG_T _BufPos;
};

#endif
