
#include "FirstHeader.h"
#include "cDemo2Device.h"
#include "System/ApplicationInterface.h"

REGISTER_DEVICE("Demo2Device", cDemo2Device)

cDemo2Device::cDemo2Device()
{
_ASSERT_UNCOND
}

cDemo2Device::cDemo2Device (cConfigurationObject * config_obj, cCell * cell)
   : cDevice(config_obj, cell)
{
}

cDemo2Device::~cDemo2Device()
{
}

void cDemo2Device::Start ()
{
}

void cDemo2Device::Stop ()
{
}

void cDemo2Device::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cDemo2Device::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T elements)
{
}

void cDemo2Device::UseBuffer (CONST_STRING_T buf_spec)
{
}

void cDemo2Device::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
}

void cDemo2Device::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{

}

void cDemo2Device::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
}

void cDemo2Device::Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags)
{
}

BOOL_T cDemo2Device::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   return false;
}

void cDemo2Device::Download()
{
}

