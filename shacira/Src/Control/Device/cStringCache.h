//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH

#ifndef cStringCache_h
#define cStringCache_h 1

#include "Control/Device/cCache.h"

class __DLL_EXPORT__ cDevice;

class cStringBuffer
{
public:
   UCHAR_T _RefreshType;
   ULONG_T _RefreshValue;
   STRING_T _String;
   BOOL_T _Buffered;
public:
   cStringBuffer()
   {
      _RefreshType = UNDEFINED;
      _RefreshValue = UNDEFINED;
      _Expired = 0;
      _Buffered = true;
   };
   cStringBuffer(UCHAR_T refresh_type, ULONG_T refresh_value)
   {
      _RefreshType = refresh_type;
      _RefreshValue = refresh_value;
      _Expired = refresh_value;
      _Buffered = false;
   };
   void SetString(CONST_STRING_T value)
   {
      _String = value;
      _Expired = _RefreshValue;
   };
   STRING_T String()
   {
      return _String;
   };
   BOOL_T Expired(ULONG_T elapsed)
   {
      if (_RefreshType == SH_REFRESH_INTERVAL) {
         _Expired -= elapsed;
         if (_Expired <= 0) {
            _Expired = _RefreshValue;
            return true;
         } else {
            return false;
         }
      } else {
         return false;
      }
   };
   BOOL_T IsBuffered()
   {
      return _Buffered;
   };
private:
   LONG_T _Expired;
};
typedef std::map<STRING_T, cStringBuffer*> STRING_BUFFER_MAP_T;

class __DLL_EXPORT__ cStringCache : public cCache
{
public:
   cStringCache (cDevice *device, CONST_STRING_T name);
   virtual ~cStringCache();
   virtual BOOL_T SetCached (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetCached (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetBuffered (LONG_T address, ULONG_T size);
   virtual BOOL_T SetBuffered (CONST_STRING_T name, ULONG_T size);
   virtual void Done ();
   virtual void Read (LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read (CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read (CONST_STRING_T name, STRING_T &value);
   virtual void Write (LONG_T address, ULONG_T elements, void *buf);
   virtual void Write (CONST_STRING_T name, ULONG_T elements, void *buf);
   virtual void Write (CONST_STRING_T name, CONST_STRING_T value);
   virtual void Save (ULONG_T elapsed);
   virtual void Save (UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Load ();
   virtual void Upload ();
   virtual void Download ();
   virtual ULONG_T MinIdleTime ();

protected:
   STRING_BUFFER_MAP_T _StringBuffers;

private:
   cStringBuffer * StringBuffer (CONST_STRING_T name);

};

#endif
