
#include "binaryframehandler.h"
#include "alloc.h"
#include <string.h>

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
   memset(&_buffer, 0, sizeof(_buffer));
   _bufferSize = sizeof(_buffer);
   _bufferIndex = 0;
   _state = STATE_IDLE;
}

cBinaryFrameHandler::~cBinaryFrameHandler()
{
}

bool cBinaryFrameHandler::add(const OCTET_T * input, LENGTH_T inputLength, cByteBuffer & frame)
{
   cByteBuffer buffer;
   if (this->input(input, inputLength, buffer)) {
      frame = buffer;
      return true;
   } else {
      return false;
   }
}

bool cBinaryFrameHandler::pack(const OCTET_T * data, LENGTH_T dataLength, cByteBuffer & frame)
{
   cByteBuffer buffer = this->output(data, dataLength);
   frame = buffer;
   return true;
}

bool cBinaryFrameHandler::input(const OCTET_T * data, LENGTH_T dataLen, cByteBuffer & buffer)
{
   bool frameComplete = handleInput(data, dataLen);
   _inputBuffer.add(_buffer, _bufferIndex);
   if (frameComplete) {
      buffer = cByteBuffer((unsigned char*)_inputBuffer.buffer(), _inputBuffer.used());
      _state = STATE_IDLE;
      memset(&_buffer, 0, sizeof(_buffer));
      _bufferIndex = 0;
      _inputBuffer.reset();
      return true;
   } else {
      return false;
   }
}

cByteBuffer cBinaryFrameHandler::output(const OCTET_T * data, LENGTH_T dataLen)
{
   OCTET_T * buffer = (unsigned char *)cAlloc::allocbuffer((dataLen*2)+3);
   int bufferIndex = 0;
   LENGTH_T i = 0;
   buffer[bufferIndex++] = FRAME_START;
   for (i=0; i<dataLen; i++) {
      unsigned char c = data[i];
      if (c == FRAME_START) {
         buffer[bufferIndex++] = FRAME_ESCAPE;
         buffer[bufferIndex++] = c ^ 0x80;
      } else if (c == FRAME_ESCAPE) {
         buffer[bufferIndex++] = FRAME_ESCAPE;
         buffer[bufferIndex++] = c ^ 0x80;
      } else if (c == FRAME_END) {
         buffer[bufferIndex++] = FRAME_ESCAPE;
         buffer[bufferIndex++] = c ^ 0x80;
      } else {
         buffer[bufferIndex++] = c;
      }
   }
   buffer[bufferIndex++] = FRAME_END;
   cByteBuffer byteBuffer(buffer, bufferIndex);
   cAlloc::freebuffer(buffer);
   return byteBuffer;
}

bool cBinaryFrameHandler::handleInput(const OCTET_T * input, LENGTH_T inputLength)
{
   memset(&_buffer, 0, sizeof(_buffer));
   _bufferIndex = 0;
   unsigned long i = 0;
   for (i=0; i<inputLength; i++) {
      unsigned char c = input[i];
      if (_state == STATE_IDLE) {
         if (c == FRAME_START) {
            _state = STATE_DATA;
            _bufferIndex = 0;
         }
      } else if (_state == STATE_DATA) {
         if (c == FRAME_START) {
            _state = STATE_DATA;
            _bufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            _state = STATE_ESCAPE;
         } else if (c == FRAME_END) {
            _state = STATE_IDLE;
            return true;
         } else {
            _buffer[_bufferIndex] = c;
            _bufferIndex++;
         }
      } else if (_state == STATE_ESCAPE) {
         if (c == FRAME_START) {
            _state = STATE_DATA;
            _bufferIndex = 0;
         } else if (c == FRAME_ESCAPE) {
            _state = STATE_DATA;
            /// ignore
         } else if (c == FRAME_END) {
            _state = STATE_IDLE;
         } else {
            _buffer[_bufferIndex] = c ^ 0x80;
            _bufferIndex++;
            _state = STATE_DATA;
         }
      } else if (_state == STATE_BUSY) {
         _state = STATE_IDLE;
      } else if (_state == STATE_ERROR_OVERFLOW) {
         _state = STATE_IDLE;
      } else if (_state == STATE_ERROR_TIMEOUT) {
         _state = STATE_IDLE;
      }
   }
   return false;
}

