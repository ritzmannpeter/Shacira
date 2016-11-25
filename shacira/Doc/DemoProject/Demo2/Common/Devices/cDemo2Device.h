
#ifndef _cdemo2device_h
#define _cdemo2device_h

#include "Control/Device/cDevice.h"
#include "Control/Cell/cCell.h"
#include "System/Config/cConfigurationObject.h"

class cDemo2Device : public cDevice
{
public:
   cDemo2Device();
   cDemo2Device (cConfigurationObject * config_obj, cCell * cell);
   virtual ~cDemo2Device();
   virtual void Start ();
   virtual void Stop ();
   virtual void Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements = 1);
   virtual void UseBuffer (CONST_STRING_T buf_spec);
   virtual void Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual void Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual BOOL_T ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value);
   virtual void Download ();
};

#endif
