
#include "cFrameHandler.h"
#include <stdio.h>
#include <windows.h>

#define STATE_IDLE               0
#define STATE_ESCAPE             1
#define STATE_DATA               2
#define STATE_BUSY               3
#define STATE_ERROR_OVERFLOW     4
#define STATE_ERROR_TIMEOUT      5

#define FRAME_START     0x10
#define FRAME_ESCAPE    0x11
#define FRAME_END       0x12

#define CHECK_TRANSPORT \
   if (_TransportHandler == NULL) { \
      printf("no transport layer"); \
      Beep(50,50); \
   }

cFrameHandler::cFrameHandler(cTransportHandler * transport_handler)
{
   _TransportHandler = transport_handler;
   _State = STATE_IDLE;
   _BufferIndex = 0;
   _BufferSize = BUFFER_SIZE;
   _Buffer = (unsigned char *)ALLOC(_BufferSize);
   _ActFrame = NULL;
   _ActFrameLength = 0;
}

cFrameHandler::~cFrameHandler()
{
   FREE(_Buffer);
}

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
CHECK_TRANSPORT
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
      } else if (nread < 0) {
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
            Received();
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
            Received();
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

int cFrameHandler::SendBuffer(const unsigned char * buffer, unsigned long buffer_length)
{
CHECK_TRANSPORT
   return _TransportHandler->SendBuffer(buffer, buffer_length);
}

int cFrameHandler::ReceiveBuffer(unsigned char * buffer, unsigned long buffer_size, int timeout)
{
CHECK_TRANSPORT
   return _TransportHandler->ReceiveBuffer(buffer, buffer_size, timeout);
}

void cFrameHandler::SetTransportHandler(cTransportHandler * th)
{
   _TransportHandler = th;
}

void cFrameHandler::Received()
{
   unsigned long frame_length = _BufferIndex;
   unsigned char * buffer = (unsigned char *)ALLOC(frame_length);
   _ActFrame = buffer;
   _ActFrameLength = frame_length;
   memcpy(buffer, _Buffer, _ActFrameLength);
//   FrameReceived(buffer, min);
}


