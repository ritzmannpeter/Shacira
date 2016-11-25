
#include <string.h>
#include "cFrameHandler.h"
#include "cAlloc.h"

bool cFrameHandler::Input(unsigned char * data, int data_len, unsigned char * & raw_data, int & raw_data_len)
{
return false;
#ifdef lassma
   unsigned char * chunk = data;
   int total_size = data_len;
   int chunk_size = _ChunkBuffer.Size();
   while (total_size > 0) {
      AddChunk(chunk, chunk_size);




      const char * raw_data = (const char*)_ChunkBuffer.Buffer();
      int raw_data_len = strlen(raw_data);
      if (raw_data[raw_data_len-1] == '\n') {
         raw_data_len = data_len - 1;
         raw_data = (unsigned char*)cAlloc::Alloc(raw_data_len+1);
         memcpy(raw_data, data, raw_data_len);
         _ChunkBuffer.Reset();
         return true;
      } else {
         return false;
      }
   }
#endif
}

unsigned char * cFrameHandler::Output(const unsigned char * data, int data_len, int & frame_len)
{
   frame_len = data_len + 2;
   unsigned char * frame = (unsigned char*)cAlloc::Alloc(frame_len);
   memcpy(frame, data, frame_len);
   frame[frame_len-1] = '\n';
   return frame;
}

void cFrameHandler::AddChunk(unsigned char * chunk, int chunk_size)
{
   _ChunkBuffer.Add(chunk, chunk_size);
}


