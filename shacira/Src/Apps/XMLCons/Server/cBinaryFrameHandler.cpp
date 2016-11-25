
#include <string.h>
#include "cBinaryFrameHandler.h"
#include "cAlloc.h"

#define STATE_IDLE               0
#define STATE_ESCAPE             1
#define STATE_DATA               2
#define STATE_BUSY               3
#define STATE_ERROR_OVERFLOW     4
#define STATE_ERROR_TIMEOUT      5

#define FRAME_START     0x10
#define FRAME_ESCAPE    0x11
#define FRAME_END       0x12

cBinaryFrameHandler::cBinaryFrameHandler()
{
   memset(&_Buffer, 0, sizeof(_Buffer));
   _BufferSize = sizeof(_Buffer);
   _State = STATE_IDLE;
}

cBinaryFrameHandler::~cBinaryFrameHandler()
{
}

bool cBinaryFrameHandler::Input(unsigned char * data, int data_len, unsigned char * & raw_data, int & raw_data_len)
{
   unsigned char * chunk = data;
   int total_size = data_len;
   int chunk_size = _ChunkBuffer.ChunkSize();
   while (total_size > 0) {
      bool frame_complete = HandleInput(chunk, chunk_size);
      AddChunk(_Buffer, _BufferIndex);
      if (frame_complete) {
         const char * data = (const char*)_ChunkBuffer.Buffer();
         raw_data_len = _ChunkBuffer.Used();
         raw_data = (unsigned char*)cAlloc::Alloc(raw_data_len+1);
         memcpy(raw_data, data, raw_data_len);
         _State = STATE_IDLE;
         memset(&_Buffer, 0, sizeof(_Buffer));
         _BufferIndex = 0;
         _ChunkBuffer.Reset();
         return true;
      }
      chunk += chunk_size;
      total_size -= chunk_size;
   }
   return false;
}

unsigned char * cBinaryFrameHandler::Output(const unsigned char * data, int data_len, int & frame_len)
{
   unsigned char * buffer = (unsigned char *)cAlloc::Alloc((data_len*2)+3);
   int buffer_index = 0;
   int i = 0;
   buffer[buffer_index++] = FRAME_START;
   for (i=0; i<data_len; i++) {
      unsigned char c = data[i];
      if (c == FRAME_START) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else if (c == FRAME_ESCAPE) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else if (c == FRAME_END) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else {
         buffer[buffer_index++] = c;
      }
   }
   buffer[buffer_index++] = FRAME_END;
   frame_len = buffer_index;
   return buffer;
}

bool cBinaryFrameHandler::HandleInput(const unsigned char * input, unsigned long input_length)
{
   
   memset(&_Buffer, 0, sizeof(_Buffer));
   _BufferIndex = 0;
   unsigned long i = 0;
   for (i=0; i<input_length; i++) {
      unsigned char c = input[i];
      if (_State == STATE_IDLE) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         }
      } else if (_State == STATE_DATA) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            _State = STATE_ESCAPE;
         } else if (c == FRAME_END) {
            _State = STATE_IDLE;
            return true;
         } else {
            _Buffer[_BufferIndex] = c;
            _BufferIndex++;
         }
      } else if (_State == STATE_ESCAPE) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            _State = STATE_DATA;
            /// ignore
         } else if (c == FRAME_END) {
            _State = STATE_IDLE;
         } else {
            _Buffer[_BufferIndex] = c ^ 0x80;
            _BufferIndex++;
            _State = STATE_DATA;
         }
      } else if (_State == STATE_BUSY) {
         _State = STATE_IDLE;
      } else if (_State == STATE_ERROR_OVERFLOW) {
         _State = STATE_IDLE;
      } else if (_State == STATE_ERROR_TIMEOUT) {
         _State = STATE_IDLE;
      }
   }
   return false;
}

#ifdef lassma

int cFrameHandler::SendFrame(const unsigned char * frame, unsigned long frame_length)
{
   unsigned char * buffer = (unsigned char *)ALLOC(frame_length*2);
   int buffer_index = 0;
   unsigned long i = 0;
   buffer[buffer_index++] = FRAME_START;
   for (i=0; i<frame_length; i++) {
      unsigned char c = frame[i];
      if (c == FRAME_START) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else if (c == FRAME_ESCAPE) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else if (c == FRAME_END) {
         buffer[buffer_index++] = FRAME_ESCAPE;
         buffer[buffer_index++] = c ^ 0x80;
      } else {
         buffer[buffer_index++] = c;
      }
   }
   buffer[buffer_index++] = FRAME_END;
   SendBuffer(buffer, buffer_index);
   FREE(buffer);
   return 0;
}

int cFrameHandler::GetFrame(unsigned char * frame, unsigned long buf_size)
{
   unsigned char buffer[0x100] = {0};
   while (true) {
      int nread = _TransportHandler->ReceiveBuffer(buffer, sizeof(buffer), 10);
      if (nread > 0) {
         HandleInput(buffer, nread);
         if (_ActFrameLength > 0) {
            unsigned long frame_length = _ActFrameLength;
            if (buf_size < _ActFrameLength) {
               frame_length = buf_size;
            }
            memcpy(frame, _ActFrame, frame_length);
            FREE(_ActFrame);
            _ActFrameLength = 0;
            return frame_length;
         }
      } else {
         return nread;
      }
   }
}

int cFrameHandler::HandleInput(const unsigned char * input, unsigned long input_length)
{
   unsigned long i = 0;
   for (i=0; i<input_length; i++) {
      unsigned char c = input[i];
      if (_State == STATE_IDLE) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         }
      } else if (_State == STATE_DATA) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            _State = STATE_ESCAPE;
         } else if (c == FRAME_END) {
            _State = STATE_IDLE;
            return true;
//            Received();
         } else {
            _Buffer[_BufferIndex] = c;
            _BufferIndex++;
         }
      } else if (_State == STATE_ESCAPE) {
         if (c == FRAME_START) {
            _State = STATE_DATA;
            _BufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            /// ignore
         } else if (c == FRAME_END) {
            _State = STATE_IDLE;
            return true;
//            Received();
         } else {
            _Buffer[_BufferIndex] = c ^ 0x80;
            _BufferIndex++;
         }
      } else if (_State == STATE_BUSY) {
         _State = STATE_IDLE;
      } else if (_State == STATE_ERROR_OVERFLOW) {
         _State = STATE_IDLE;
      } else if (_State == STATE_ERROR_TIMEOUT) {
         _State = STATE_IDLE;
      }
   }
   return 0;
}

#endif