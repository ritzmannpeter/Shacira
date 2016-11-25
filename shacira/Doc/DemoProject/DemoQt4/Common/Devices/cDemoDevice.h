
#ifndef cDemoDevice_h
#define cDemoDevice_h 1

#include "Control/Device/cDevice.h"
#include "Control/Device/PPCCOM/cPPCDevice.h"
#include "Control/Device/PPCCOM/cPPCOperator.h"

class __DLL_EXPORT__ cDemoDevice : public cDevice  //## Inherits: <unnamed>%3FD437DD006D
{
public:
   cDemoDevice();
   cDemoDevice(const cDemoDevice &right);
   cDemoDevice (cConfigurationObject *config_obj, cCell *cell);
   virtual ~cDemoDevice();
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
   virtual void * GetObject(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags = 0);
   virtual void * GetObject(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T flags = 0);
   void Control();
protected:
   UCHAR_T _IscosNo;
   cPPCDevice * _BaseDevice;
private:
private:
};

class cDemoControl : public cControlThread
{
public:
   cDemoControl(cDemoDevice * device);
   virtual ~cDemoControl();
   INT_T ControlFunc();
private:
   cDemoDevice * _Device;
};

#endif
