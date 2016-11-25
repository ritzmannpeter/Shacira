//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH

#include "FirstHeader.h"
#include "Control/Device/cDevice.h"
#include "Control/Device/cStringCache.h"

cStringCache::cStringCache (cDevice *device, CONST_STRING_T name)
  : cCache(device, name)
{
}

cStringCache::~cStringCache()
{
}

BOOL_T cStringCache::SetCached (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "BOOL_T cStringCache::SetCached (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)");
}

BOOL_T cStringCache::SetCached (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   if (*name == '\0') {
      return true;
   }
   cStringBuffer * buffer = StringBuffer(name);
   if (buffer == NULL) {
      buffer = new cStringBuffer(refresh_type, refresh_value);
      _StringBuffers[name] = buffer;
   }
   return true;
}

BOOL_T cStringCache::SetBuffered (LONG_T address, ULONG_T size)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "BOOL_T cStringCache::SetBuffered (LONG_T address, ULONG_T size)");
}

BOOL_T cStringCache::SetBuffered (CONST_STRING_T name, ULONG_T size)
{
   cStringBuffer * buffer = StringBuffer(name);
   if (buffer == NULL) {
      buffer = new cStringBuffer;
      _StringBuffers[name] = buffer;
   }
   return true;
}

void cStringCache::Done ()
{
}

void cStringCache::Read (LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cStringCache::Read (LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size)");
}

void cStringCache::Read (CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   STRING_T cached_value;
   cStringBuffer * buffer = StringBuffer(name);
   if (buffer == NULL) {
      return;
   } else {
      cached_value = buffer->String();
   }
   int size = _MIN_(cached_value.size(), buf_size);
   memcpy(buf, cached_value.c_str(), size);
}

void cStringCache::Read (CONST_STRING_T name, STRING_T &value)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cStringCache::Read (CONST_STRING_T name, STRING_T &value)");
}

void cStringCache::Write (LONG_T address, ULONG_T elements, void *buf)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cStringCache::Write (LONG_T address, ULONG_T elements, void *buf)");
}

void cStringCache::Write (CONST_STRING_T name, ULONG_T elements, void *buf)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cStringCache::Write (CONST_STRING_T name, ULONG_T elements, void *buf)");
}

void cStringCache::Write (CONST_STRING_T name, CONST_STRING_T value)
{
   cStringBuffer * buffer = StringBuffer(name);
   if (buffer == NULL) {
      return;
   } else {
      buffer->SetString(value);
   }
}

void cStringCache::Save (ULONG_T elapsed)
{
   STRING_BUFFER_MAP_T::const_iterator i = _StringBuffers.begin();
   while (i != _StringBuffers.end()) {
      STRING_T name = (*i).first;
      cStringBuffer * buffer = (*i).second;
      if (buffer != NULL && buffer->Expired(elapsed)) {
         _Device->Read(_CacheName.c_str(),
                       name.c_str(),
                       _BufSize,
                       _Buf,
                       _BufSize,
                       VF_DEVICE);
         CONST_STRING_T src_buf = (CONST_STRING_T)_Buf;
         if (strcmp(src_buf, buffer->String().c_str()) != 0) {
            buffer->SetString(src_buf);
            _Device->Changed(_CacheName.c_str(), name.c_str());
         }
      }
      i++;
   }
}

void cStringCache::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   STRING_BUFFER_MAP_T::const_iterator i = _StringBuffers.begin();
   while (i != _StringBuffers.end()) {
      STRING_T name = (*i).first;
      cStringBuffer * buffer = (*i).second;
      UCHAR_T buffer_refresh_type = buffer->_RefreshType;
      ULONG_T buffer_refresh_value = buffer->_RefreshValue;
      if (refresh_type == buffer_refresh_type &&
          refresh_value == buffer_refresh_value) {
         try {
            _Device->Read(_CacheName.c_str(),
                          name.c_str(),
                          _BufSize,
                          _Buf,
                          _BufSize,
                          VF_DEVICE);
         } catch (cError & e) {
            int dummy = 0;
         } catch (...) {
            int dummy = 0;
         }
         CONST_STRING_T src_buf = (CONST_STRING_T)_Buf;
         if (strcmp(src_buf, buffer->String().c_str()) != 0) {
            buffer->SetString(src_buf);
            _Device->Changed(_CacheName.c_str(), name.c_str());
         }
      }
      i++;
   }
}

void cStringCache::Load ()
{
   STRING_BUFFER_MAP_T::const_iterator i = _StringBuffers.begin();
   while (i != _StringBuffers.end()) {
      STRING_T name = (*i).first;
      cStringBuffer * buffer = (*i).second;
      if (buffer != NULL && buffer->IsBuffered()) {
         STRING_T value = buffer->String();
         _Device->Write(_CacheName.c_str(),
                        name.c_str(),
                        (ULONG_T)value.size(),
                        (void*)value.c_str(),
                        VF_DEVICE);
      }
      i++;
   }
}

void cStringCache::Upload ()
{
}

void cStringCache::Download ()
{
}

ULONG_T cStringCache::MinIdleTime ()
{
   return 100;
}

cStringBuffer * cStringCache::StringBuffer (CONST_STRING_T name)
{
   STRING_BUFFER_MAP_T::const_iterator i = _StringBuffers.find(name);
   if (i == _StringBuffers.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

