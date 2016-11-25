
#include "FirstHeader.h"
#include "Control/Cell/cCell.h"
#include "Control/Device/cCacheControl.h"
#include "Control/Device/cBlockCache.h"
#include "Control/Device/cMemoryAddressedDevice.h"
#include "cDemoDevice.h"

cDemoDevice::cDemoDevice() : _BaseDevice(NULL)
{
_ASSERT_UNCOND
}

cDemoDevice::cDemoDevice(const cDemoDevice &right) : _BaseDevice(NULL)
{
_ASSERT_UNCOND
}

cDemoDevice::cDemoDevice (cConfigurationObject *config_obj, cCell *cell)
      : _BaseDevice(NULL)
  , cDevice(config_obj, cell)
{
}

cDemoDevice::~cDemoDevice()
{
}

void cDemoDevice::Start ()
{
}

void cDemoDevice::Stop ()
{
}

void cDemoDevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cDemoDevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
}

void cDemoDevice::UseBuffer (CONST_STRING_T buf_spec)
{
}

void cDemoDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
}

void cDemoDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{

}

void cDemoDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
}

void cDemoDevice::Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags)
{
   FLOAT_T value = *(FLOAT_T*)buf;

}

BOOL_T cDemoDevice::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   return false;
}

void cDemoDevice::Download()
{
}

void cDemoDevice::Control()
{
}

