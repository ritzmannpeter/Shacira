
#ifndef __cparser_h__
#define __cparser_h__

#include "global_defs.h"
#include "cstreamtokenizer.h"

#define SAFETY       100
#define MAX_CHUNKS   1000
#define CHUNK_SIZE   0x4000
class cParser
{
public:
   cParser(cStreamTokenizer * tokenizer) :
      _Tokenizer(tokenizer), _Chunk(0), _WaterMark(0)
   {
      memset(_Chunks, 0, sizeof(_Chunks));
      _Chunks[_Chunk] = (char*)calloc(1, CHUNK_SIZE);
   };
   virtual ~cParser()
   {
      unsigned long i = 0;
      for (i=0; i<=_Chunk; i++) {
         void * chunk = _Chunks[i];
         if (chunk != NULL) {
            delete chunk;
         }
      }
   };
   inline void * Alloc(unsigned long size)
   {
      if (_WaterMark + size > (CHUNK_SIZE - SAFETY)) {
         _Chunk++;
         _Chunks[_Chunk] = (char*)calloc(1, CHUNK_SIZE);
         _WaterMark = 0;
      }
      void * mem = &(_Chunks[_Chunk][_WaterMark]);
      _WaterMark += (size + 1);
      return mem;
   };
protected:
   cStreamTokenizer * _Tokenizer;
   unsigned long _Chunk;
   char * _Chunks[MAX_CHUNKS];
   unsigned long _WaterMark;
};

#endif

