
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "FileBuffer.h"
#include "HAlloc.h"

#define BUF_SIZE(size)   ((size / BLOCK_SIZE) + 1) * BLOCK_SIZE;

static int Expand(void * fbuf, unsigned_32 size)
{
   unsigned_32 buf_size;
   void * buffer;
   if (size < _file_size) return 0;
   buf_size = BUF_SIZE(size);
   buffer = HAlloc(buf_size);
   if (buffer) {
      memcpy(buffer, _buffer, _file_size);
      HFree(_buffer);
      _buffer = buffer;
      _buf_size = buf_size;
   } else {
      return -203;
   }
   return 0;
}

static int Init(void * fbuf, unsigned_32 size)
{
   if (_buffer != NULL) {
      HFree(_buffer);
   }
   _buffer = NULL;
   _seek_pos = _file_size = 0;
   _buf_size = BUF_SIZE(size);
   _buffer = HAlloc(_buf_size);
   if (_buffer) {
      _file_size = size;
   }
   return 0;
}

static int LoadFile(void * fbuf, const char * path)
{
   char buf[512];
   int nread, nwrite;
   FILE * stream;
   _Init(fbuf, 0);
   if ((stream = fopen(path, "rb")) != NULL) {
      while ((nread = fread(buf, 1, sizeof(buf), stream)) != 0) {
         nwrite = _Write(fbuf, buf, nread);
      }
      fclose(stream);
   } else {
      return -204;
   }
   return 0;
}

static int SaveFile(void * fbuf, const char * path)
{
   char buf[512];
   int nread, nwrite;
   FILE * stream;
   _Seek(fbuf, 0);
   if ((stream = fopen(path, "wb")) != NULL) {
      while ((nread = _Read(fbuf, buf, sizeof(buf))) != 0) {
         nwrite = fwrite(buf, 1, nread, stream);
      }
      fclose(stream);
   } else {
      return -204;
   }
   return 0;
}

static int Seek(void * fbuf, unsigned_32 pos)
{
   if (_buffer == NULL) return -200;
   if (pos > _file_size) return -201;
   _seek_pos = pos;
   return _seek_pos;
}

static int Read(void * fbuf, void * buffer, unsigned_32 size)
{
   signed_32 len;
   unsigned_8 * src;
   if (_buffer == NULL) return -200;
   if (_seek_pos + size >= _file_size) {
      len = _file_size - _seek_pos;
      if (len <= 0) return 0;
   } else {
      len = size;
   }
   src = _buffer;
   src += _seek_pos;
   memcpy(buffer, (void*)src, len);
   _seek_pos += len;
   return len;
}

static int Write(void * fbuf, void * buffer, unsigned_32 size)
{
   unsigned_8 * dst;
   if (_buffer == NULL) return -200;
   if (_seek_pos + size >= _file_size) {
      if (Expand(fbuf, _seek_pos + size) != 0) {
         return -202;
      }
   }
   dst = _buffer;
   dst += _seek_pos;
   memcpy((void*)dst, buffer, size);
   _seek_pos += size;
   if (_seek_pos > _file_size) {
      _file_size = _seek_pos;
   }
   return size;
}

unsigned_32 SeekPos(void * fbuf)
{
   return _seek_pos;
}

unsigned_32 FileSize(void * fbuf)
{
   return _file_size;
}

FILE_BUFFER_T * NewFileBuffer(const char * path)
{
   FILE_BUFFER_T * fbuf = HAlloc(sizeof(*fbuf));
   _Init = Init;
   _LoadFile = LoadFile;
   _SaveFile = SaveFile;
   _Seek = Seek;
   _Read = Read;
   _Write = Write;
   _SeekPos = SeekPos;
   _FileSize = FileSize;
   if (_LoadFile(fbuf, path) == 0) {
      return fbuf;
   } else {
      HFree(fbuf);
      return NULL;
   }
}

int DeleteFileBuffer(FILE_BUFFER_T * fbuf)
{
   if (_buffer != NULL) {
      HFree(_buffer);
   }
   HFree(fbuf);
   return 0;
}

