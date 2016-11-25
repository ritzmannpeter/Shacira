
#include "bytebuffer.h"
#include "alloc.h"

#include <windows.h>
#define LOCKED_INCREMENT(count) InterlockedIncrement(count)
#define LOCKED_DECREMENT(count) InterlockedDecrement(count)

unsigned char cByteBuffer::_emptyData = 0;
int cByteBuffer::_allocatedBuffers = 0;
int cByteBuffer::allocatedBuffers()
{
   return _allocatedBuffers;
}
bool cByteBuffer::_verbose = true;

cByteBuffer::cByteBuffer()
   : _size(0), _buffer(NULL)
{
}

cByteBuffer::cByteBuffer(const OCTET_T * data, LENGTH_T size)
   : _size(size)
{
   _buffer = (struct buffer *)cAlloc::allocbuffer(sizeof(struct buffer));
   _buffer->refCount = 1;
   _buffer->data = (OCTET_T *)cAlloc::allocbuffer(size + 1);
   memcpy(_buffer->data, data, size);
   _allocatedBuffers++;
}

cByteBuffer::cByteBuffer(const cByteBuffer & right)
   : _size(0), _buffer(NULL)
{
   _buffer = right._buffer;
   if (_buffer != NULL) {
      long refCount = LOCKED_INCREMENT(&(_buffer->refCount));
   }
   _size = right._size;
}

cByteBuffer::~cByteBuffer()
{
   if (_buffer != NULL) {
      long refCount = LOCKED_DECREMENT(&(_buffer->refCount));
      if (refCount == 0) {
         cAlloc::freebuffer(_buffer->data);
         cAlloc::freebuffer(_buffer);
         _allocatedBuffers--;
      }
   }
}

cByteBuffer & cByteBuffer::operator= (const cByteBuffer & right)
{
   if (_buffer != NULL) {
      if (_buffer != right._buffer) {
         long refCount = LOCKED_DECREMENT(&(_buffer->refCount));
         if (refCount == 0) {
            cAlloc::freebuffer(_buffer->data);
            cAlloc::freebuffer(_buffer);
            _allocatedBuffers--;
         }
      }
   }
   _buffer = right._buffer;
   if (_buffer != NULL) {
      long refCount = LOCKED_INCREMENT(&(_buffer->refCount));
   }
   _size = right._size;
   return *this;
}

void cByteBuffer::append(const OCTET_T * data, LENGTH_T size)
{
   if (_buffer == NULL) {
      _buffer = (struct buffer *)cAlloc::allocbuffer(sizeof(struct buffer));
      _buffer->refCount = 1;
      _buffer->data = (OCTET_T *)cAlloc::allocbuffer(size + 1);
      memcpy(_buffer->data, data, size);
      _size = size;
      _allocatedBuffers++;
   } else {
      LENGTH_T newSize = _size + size;
      OCTET_T * newData = (OCTET_T *)cAlloc::allocbuffer(newSize + 1);
      memcpy(newData, _buffer->data, _size);
      memcpy(&newData[_size], data, size);
      OCTET_T * freeData = _buffer->data;
      _buffer->data = newData;
      _size = newSize;
      cAlloc::freebuffer(freeData);
   }
}

void cByteBuffer::append(const char * data, LENGTH_T size)
{
   append((unsigned char*)data, size);
}

LENGTH_T cByteBuffer::size() const
{
   return _size;
}

const OCTET_T * cByteBuffer::data() const
{
   if (_buffer == NULL) {
      return &_emptyData;
   } else {
      return _buffer->data;
   }
}

void cByteBuffer::show(const char * header) const
{
   show(header, data(), size());
}

void cByteBuffer::show(const char * header, const OCTET_T * data, LENGTH_T size)
{
   if (_verbose) {
      std::cout << header << " ";
      LENGTH_T i = 0;
      for (i=0; i<size; i++) {
         char c = data[i];
         if (true) {
            std::cout << "[" << c << "/" << (int)c << "]";
         } else {
            std::cout << "[" << (int)c << "]";
         }
      }
      std::cout << endl;
   }
}

void cByteBuffer::setVerbose(bool state)
{
   _verbose = state;
}

