//## begin module%3C4EE681039C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE681039C.cm

//## begin module%3C4EE681039C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE681039C.cp

//## Module: cCorbaCellProxy%3C4EE681039C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Orb\cCorbaCellProxy.cpp

//## begin module%3C4EE681039C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C4EE681039C.additionalIncludes

//## begin module%3C4EE681039C.includes preserve=yes
//## end module%3C4EE681039C.includes

// cJobSpec
#include "System/Objects/cJobSpec.h"
// cCorbaCellProxy
#include "Orb/cCorbaCellProxy.h"
// cBroker
#include "Orb/cBroker.h"
//## begin module%3C4EE681039C.additionalDeclarations preserve=yes
//## end module%3C4EE681039C.additionalDeclarations


// Class cCorbaCellProxy 

cCorbaCellProxy::cCorbaCellProxy(unsigned long call_timeout)
  //## begin cCorbaCellProxy::cCorbaCellProxy%.hasinit preserve=no
  //## end cCorbaCellProxy::cCorbaCellProxy%.hasinit
  //## begin cCorbaCellProxy::cCorbaCellProxy%.initialization preserve=yes
   : _Itf(NULL), _CorbaObject(NULL), _CallTimeout(call_timeout)
  //## end cCorbaCellProxy::cCorbaCellProxy%.initialization
{
  //## begin cCorbaCellProxy::cCorbaCellProxy%.body preserve=yes
   _Type = OT_CORBA_CELL_PROXY;
  //## end cCorbaCellProxy::cCorbaCellProxy%.body
}

cCorbaCellProxy::cCorbaCellProxy(const cCorbaCellProxy &right)
  //## begin cCorbaCellProxy::cCorbaCellProxy%copy.hasinit preserve=no
  //## end cCorbaCellProxy::cCorbaCellProxy%copy.hasinit
  //## begin cCorbaCellProxy::cCorbaCellProxy%copy.initialization preserve=yes
  //## end cCorbaCellProxy::cCorbaCellProxy%copy.initialization
{
  //## begin cCorbaCellProxy::cCorbaCellProxy%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCorbaCellProxy::cCorbaCellProxy%copy.body
}


cCorbaCellProxy::~cCorbaCellProxy()
{
  //## begin cCorbaCellProxy::~cCorbaCellProxy%.body preserve=yes
   ReleaseItf();
  //## end cCorbaCellProxy::~cCorbaCellProxy%.body
}



//## Other Operations (implementation)
void cCorbaCellProxy::Update (cProxy *proxy)
{
  //## begin cCorbaCellProxy::Update%1054547852.body preserve=yes
   if (_Type != proxy->get_Type()) return; 
   if (_ProxyName != proxy->get_ProxyName()) return; 
   if (_IOR == proxy->get_IOR()) return; 
   _Computer = proxy->get_Computer();
   _IPAddress = proxy->get_IPAddress();
   _Port = proxy->get_Port();
   _CellName = proxy->get_CellName();
   _Object = proxy->get_Object();
   _ProcessId = proxy->get_ProcessId();
   _ProcessName = proxy->get_ProcessName();
   _IOR = proxy->get_IOR();
   _TimeStamp = proxy->get_TimeStamp();
   SetItf();
  //## end cCorbaCellProxy::Update%1054547852.body
}

STRING_T cCorbaCellProxy::Name ()
{
  //## begin cCorbaCellProxy::Name%1036694763.body preserve=yes
CORBA_ITF_PROLOG("iCell::Name", _Itf)
   char * _name = (*_Itf)->Name();
   STRING_T name = (char*)_name;
   FREE_CORBA_STRING(_name);
   _Connected = true;
   return name;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::Name%1036694763.body
}

ULONG_T cCorbaCellProxy::GetVarDefs (STRING_T &var_defs)
{
  //## begin cCorbaCellProxy::GetVarDefs%1049277237.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetVarDefs", _Itf)
   char * defs = (*_Itf)->GetVarDefs(_ClientId, _IFType);
   var_defs = defs;
   FREE_CORBA_STRING(defs);
   _Connected = true;
   _Synchronized = true;
   return var_defs.size();
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetVarDefs%1049277237.body
}

void cCorbaCellProxy::GetValue (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1023444138.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   char * _value = (*_Itf)->GetValue(_ClientId, var_name, i1, i2, i3, i4, flags);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1023444138.body
}

void cCorbaCellProxy::GetValue (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1023444139.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   STRING_T svalue = (*_Itf)->GetValue(_ClientId, var_name, i1, i2, i3, i4, flags);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1023444139.body
}

void cCorbaCellProxy::GetValue (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1023444140.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   STRING_T svalue = (*_Itf)->GetValue(_ClientId, var_name, i1, i2, i3, i4, flags);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1023444140.body
}

void cCorbaCellProxy::RefreshValue (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::RefreshValue%1133172779.body preserve=yes
CORBA_ITF_PROLOG("iCell::RefreshValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   (*_Itf)->Refresh(_ClientId, var_name, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::RefreshValue%1133172779.body
}

void cCorbaCellProxy::SetValue (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1023444141.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   (*_Itf)->SetValue(_ClientId, var_name, value, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1023444141.body
}

void cCorbaCellProxy::SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1023444142.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   char svalue[0x40] = {0};
   SafePrintf(svalue, sizeof(svalue), "%d", value);
   (*_Itf)->SetValue(_ClientId, var_name, svalue, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1023444142.body
}

void cCorbaCellProxy::SetValue (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1023444143.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   VF_SET_IF_TYPE(flags, _IFType)
   char svalue[0x40] = {0};
   SafePrintf(svalue, sizeof(svalue), "%f", value);
   (*_Itf)->SetValue(_ClientId, var_name, svalue, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1023444143.body
}

void cCorbaCellProxy::GetParam (CONST_STRING_T param_name, STRING_T &value)
{
  //## begin cCorbaCellProxy::GetParam%1078912345.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetParam", _Itf)
   char * _value = (*_Itf)->GetParam(_ClientId, param_name);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetParam%1078912345.body
}

void cCorbaCellProxy::GetParam (CONST_STRING_T param_name, LONG_T &value)
{
  //## begin cCorbaCellProxy::GetParam%1078912346.body preserve=yes
   STRING_T sval;
   GetParam(param_name, sval);
   value = atol(sval.c_str());
  //## end cCorbaCellProxy::GetParam%1078912346.body
}

void cCorbaCellProxy::GetParam (CONST_STRING_T param_name, DOUBLE_T &value)
{
  //## begin cCorbaCellProxy::GetParam%1078912347.body preserve=yes
   STRING_T sval;
   GetParam(param_name, sval);
   value = atof(sval.c_str());
  //## end cCorbaCellProxy::GetParam%1078912347.body
}

void cCorbaCellProxy::SetParam (CONST_STRING_T param_name, CONST_STRING_T value)
{
  //## begin cCorbaCellProxy::SetParam%1078912348.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetParam", _Itf)
   (*_Itf)->SetParam(_ClientId, param_name, value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetParam%1078912348.body
}

void cCorbaCellProxy::SetParam (CONST_STRING_T param_name, LONG_T value)
{
  //## begin cCorbaCellProxy::SetParam%1078912349.body preserve=yes
   char sval[64] = {0};
   SafePrintf(sval, sizeof(sval), "%ld", value);
   SetParam(param_name, sval);
  //## end cCorbaCellProxy::SetParam%1078912349.body
}

void cCorbaCellProxy::SetParam (CONST_STRING_T param_name, DOUBLE_T value)
{
  //## begin cCorbaCellProxy::SetParam%1078912350.body preserve=yes
   char sval[64] = {0};
   SafePrintf(sval, sizeof(sval), "%f", value);
   SetParam(param_name, sval);
  //## end cCorbaCellProxy::SetParam%1078912350.body
}

void cCorbaCellProxy::ReadFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf)
{
  //## begin cCorbaCellProxy::ReadFile%1078912360.body preserve=yes
CORBA_ITF_PROLOG("iCell::ReadFile", _Itf)
   char * _buf = (*_Itf)->ReadFile(_ClientId, file_name, sub_files);
   buf = _buf;
   FREE_CORBA_STRING(_buf);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ReadFile%1078912360.body
}

void cCorbaCellProxy::WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf)
{
  //## begin cCorbaCellProxy::WriteFile%1078912361.body preserve=yes
CORBA_ITF_PROLOG("iCell::WriteFile", _Itf)
   (*_Itf)->WriteFile(_ClientId, file_name, sub_files, buf);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::WriteFile%1078912361.body
}

LONG_T cCorbaCellProxy::GetId (CONST_STRING_T var_name)
{
  //## begin cCorbaCellProxy::GetId%1078912362.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetId", _Itf)
   return (*_Itf)->GetId(_ClientId, var_name);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetId%1078912362.body
}

void cCorbaCellProxy::GetValue (LONG_T var_id, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1078912363.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   char * _value = (*_Itf)->GetValueById(_ClientId, var_id, i1, i2, i3, i4, flags);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1078912363.body
}

void cCorbaCellProxy::GetValue (LONG_T var_id, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1078912364.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   STRING_T svalue = (*_Itf)->GetValueById(_ClientId, var_id, i1, i2, i3, i4, flags);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1078912364.body
}

void cCorbaCellProxy::GetValue (LONG_T var_id, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetValue%1078912365.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetValue", _Itf)
   STRING_T svalue = (*_Itf)->GetValueById(_ClientId, var_id, i1, i2, i3, i4, flags);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetValue%1078912365.body
}

void cCorbaCellProxy::SetValue (LONG_T var_id, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1078912366.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   (*_Itf)->SetValueById(_ClientId, var_id, value, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1078912366.body
}

void cCorbaCellProxy::SetValue (LONG_T var_id, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1078912367.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   char svalue[0x40] = {0};
   SafePrintf(svalue, sizeof(svalue), "%d", value);
   (*_Itf)->SetValueById(_ClientId, var_id, svalue, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1078912367.body
}

void cCorbaCellProxy::SetValue (LONG_T var_id, DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetValue%1078912368.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetValue", _Itf)
   char svalue[0x40] = {0};
   SafePrintf(svalue, sizeof(svalue), "%f", value);
   (*_Itf)->SetValueById(_ClientId, var_id, svalue, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetValue%1078912368.body
}

ULONG_T cCorbaCellProxy::Alarms (ULONG_T selection)
{
  //## begin cCorbaCellProxy::Alarms%1089103360.body preserve=yes
CORBA_ITF_PROLOG("iCell::AlarmCount", _Itf)
   ULONG_T alarms = (*_Itf)->AlarmCount(_ClientId, selection);
   _Connected = true;
   return alarms;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::Alarms%1089103360.body
}

ULONG_T cCorbaCellProxy::Alarms (ULONG_T selection, ALARM_MAP_T &alarms)
{
  //## begin cCorbaCellProxy::Alarms%1081425837.body preserve=yes
CORBA_ITF_PROLOG("iCell::Alarms", _Itf)
   ULONG_T alarms = (*_Itf)->AlarmCount(_ClientId, selection);
   _Connected = true;
   return alarms;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::Alarms%1081425837.body
}

void cCorbaCellProxy::ClearAlarm (ULONG_T ident)
{
  //## begin cCorbaCellProxy::ClearAlarm%1081425838.body preserve=yes
CORBA_ITF_PROLOG("iCell::ClearAlarm", _Itf)
   (*_Itf)->ClearAlarm(_ClientId, ident);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ClearAlarm%1081425838.body
}

void cCorbaCellProxy::ClearAlarms ()
{
  //## begin cCorbaCellProxy::ClearAlarms%1081425839.body preserve=yes
CORBA_ITF_PROLOG("iCell::ClearAlarms", _Itf)
   (*_Itf)->ClearAlarms(_ClientId);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ClearAlarms%1081425839.body
}

void cCorbaCellProxy::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value)
{
  //## begin cCorbaCellProxy::GetDeviceValue%1082984458.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetDeviceValue", _Itf)
#ifdef lassma
   char * _value = (*_Itf)->GetDeviceValue(_ClientId, buf_spec, address);
   value = _value;
   FREE_CORBA_STRING(_value);
#else
   value = "no more supported";
#endif
   _Connected = true;
   CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetDeviceValue%1082984458.body
}

void cCorbaCellProxy::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value)
{
  //## begin cCorbaCellProxy::SetDeviceValue%1082984459.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetDeviceValue", _Itf)
#ifdef lassma
   (*_Itf)->SetDeviceValue(_ClientId, buf_spec, address, value);
#endif
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetDeviceValue%1082984459.body
}

void cCorbaCellProxy::GetMinimum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103339.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetMinimum", _Itf)
   char * _value = (*_Itf)->GetMinimum(_ClientId, var_name, i1, i2, i3, i4);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103339.body
}

void cCorbaCellProxy::GetMinimum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103340.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetIntMinimum", _Itf)
   STRING_T svalue = (*_Itf)->GetMinimum(_ClientId, var_name, i1, i2, i3, i4);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103340.body
}

void cCorbaCellProxy::GetMinimum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103341.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetRealMinimum", _Itf)
   STRING_T svalue = (*_Itf)->GetMinimum(_ClientId, var_name, i1, i2, i3, i4);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103341.body
}

void cCorbaCellProxy::GetMinimum (LONG_T var_id, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103342.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetMinimumById", _Itf)
   char * _value = (*_Itf)->GetMinimumById(_ClientId, var_id, i1, i2, i3, i4);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103342.body
}

void cCorbaCellProxy::GetMinimum (LONG_T var_id, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103343.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetIntMinimumById", _Itf)
   STRING_T svalue = (*_Itf)->GetMinimumById(_ClientId, var_id, i1, i2, i3, i4);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103343.body
}

void cCorbaCellProxy::GetMinimum (LONG_T var_id, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMinimum%1089103344.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetRealMinimumById", _Itf)
   STRING_T svalue = (*_Itf)->GetMinimumById(_ClientId, var_id, i1, i2, i3, i4);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMinimum%1089103344.body
}

void cCorbaCellProxy::GetMaximum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103345.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetMaximum", _Itf)
   char * _value = (*_Itf)->GetMaximum(_ClientId, var_name, i1, i2, i3, i4);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103345.body
}

void cCorbaCellProxy::GetMaximum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103346.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetIntMaximum", _Itf)
   STRING_T svalue = (*_Itf)->GetMaximum(_ClientId, var_name, i1, i2, i3, i4);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103346.body
}

void cCorbaCellProxy::GetMaximum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103347.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetRealMaximum", _Itf)
   STRING_T svalue = (*_Itf)->GetMaximum(_ClientId, var_name, i1, i2, i3, i4);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103347.body
}

void cCorbaCellProxy::GetMaximum (LONG_T var_id, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103348.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetMaximumById", _Itf)
   char * _value = (*_Itf)->GetMaximumById(_ClientId, var_id, i1, i2, i3, i4);
   value = _value;
   FREE_CORBA_STRING(_value);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103348.body
}

void cCorbaCellProxy::GetMaximum (LONG_T var_id, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103349.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetIntMaximumById", _Itf)
   STRING_T svalue = (*_Itf)->GetMaximumById(_ClientId, var_id, i1, i2, i3, i4);
   value = atol(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103349.body
}

void cCorbaCellProxy::GetMaximum (LONG_T var_id, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cCorbaCellProxy::GetMaximum%1089103350.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetRealMaximumById", _Itf)
   STRING_T svalue = (*_Itf)->GetMaximumById(_ClientId, var_id, i1, i2, i3, i4);
   value = atof(svalue.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMaximum%1089103350.body
}

void cCorbaCellProxy::ExecuteCommand (CONST_STRING_T program_name, ULONG_T command)
{
  //## begin cCorbaCellProxy::ExecuteCommand%1089292612.body preserve=yes
CORBA_ITF_PROLOG("iCell::ExecuteCommand", _Itf)
   (*_Itf)->ExecuteCommand(_ClientId, program_name, command);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ExecuteCommand%1089292612.body
}

void cCorbaCellProxy::ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request)
{
  //## begin cCorbaCellProxy::ExecuteRequest%1133771773.body preserve=yes
CORBA_ITF_PROLOG("iCell::ExecuteRequest", _Itf)
   char * _reply = (*_Itf)->ExecuteRequest(_ClientId, program_name, request);
   reply = _reply;
   FREE_CORBA_STRING(_reply);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ExecuteRequest%1133771773.body
}

void cCorbaCellProxy::SetJob (cJobSpec *job_spec)
{
  //## begin cCorbaCellProxy::SetJob%1093930667.body preserve=yes
CORBA_ITF_PROLOG("iCell::SetJob", _Itf)
   STRING_T spec_text = job_spec->Serialize();
   (*_Itf)->SetJobX(_ClientId, spec_text.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SetJob%1093930667.body
}

cJobSpec * cCorbaCellProxy::GetJobSpec (CONST_STRING_T job_name)
{
  //## begin cCorbaCellProxy::GetJobSpec%1093930668.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetJobSpec", _Itf)
   char * _spec_text = (*_Itf)->GetJobSpec(_ClientId, job_name);
   STRING_T spec_text = (char*)_spec_text;
   cJobSpec * job_spec = new cJobSpec;
   job_spec->Construct(spec_text.c_str());
   FREE_CORBA_STRING(_spec_text);
   _Connected = true;
   return job_spec;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetJobSpec%1093930668.body
}

ULONG_T cCorbaCellProxy::Login (CONST_STRING_T user_name, CONST_STRING_T password)
{
  //## begin cCorbaCellProxy::Login%1121785251.body preserve=yes
   ULONG_T client_id = (ULONG_T)-1;
CORBA_ITF_PROLOG("iCell::Login", _Itf)
   client_id = (*_Itf)->Login(user_name, password);
   _Connected = true;
   return client_id;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::Login%1121785251.body
}

void cCorbaCellProxy::Logout ()
{
  //## begin cCorbaCellProxy::Logout%1121785252.body preserve=yes
CORBA_ITF_PROLOG("iCell::Logout", _Itf)
   (*_Itf)->Logout(_ClientId);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::Logout%1121785252.body
}

cTransientObject * cCorbaCellProxy::GetEvent ()
{
  //## begin cCorbaCellProxy::GetEvent%1121785253.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetEvent", _Itf)
   char * _ser_obj = (*_Itf)->GetEvent(_ClientId);
   STRING_T serialized_obj = (char*)_ser_obj;
   cTransientObject * obj = NULL;
   if (serialized_obj.size() > 0) {
      obj = cTransientObject::Parse(serialized_obj.c_str());
   } else {
      int dummy = 0;
   }
   FREE_CORBA_STRING(_ser_obj);
   _Connected = true;
   return obj;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetEvent%1121785253.body
}

void cCorbaCellProxy::GetMemory (BUF_T buf, PTR_T address, ULONG_T size)
{
  //## begin cCorbaCellProxy::GetMemory%1122544052.body preserve=yes
CORBA_ITF_PROLOG("iCell::GetMemory", _Itf)
   Control::Memory * buffer = NULL;
ULONG_T t = cSystemUtils::RealtimeOffset();
//InfoPrintf("get memory at %p of size %d\n", address, size);
   buffer = (*_Itf)->GetMemory(_ClientId, (ULONG_T)address, size);
   if (buffer != NULL) {
      ULONG_T len = buffer->length();
      for (ULONG_T i=0; i<_MIN_(len,size); i++) {
         buf[i] = (*buffer)[i];
      }
      delete buffer;
   }
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::GetMemory%1122544052.body
}

void cCorbaCellProxy::SendObject (cTransientObject *object)
{
  //## begin cCorbaCellProxy::SendObject%1121785254.body preserve=yes
CORBA_ITF_PROLOG("iCell::SendObject", _Itf)
   STRING_T serialized_obj = object->Serialize();
   (*_Itf)->SendObject(_ClientId, serialized_obj.c_str());
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::SendObject%1121785254.body
}

ULONG_T cCorbaCellProxy::GetObject (cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetObject%1238436652.body preserve=yes
   ULONG_T object_size = 0;
CORBA_ITF_PROLOG("iCell::GetObject", _Itf)
   Control::Memory * buffer = NULL;
   ULONG_T buffer_size = 0;
   buffer = (*_Itf)->GetObject(_ClientId, var_name, i1, i2, i3, i4, flags);
   if (buffer != NULL) {
      object_size = buffer->length();
      object = cBinaryObject(object_size);
      unsigned char * buf = object.Data();
      for (ULONG_T i=0; i<object_size; i++) {
         buf[i] = (*buffer)[i];
      }
      delete buffer;
   }
   _Connected = true;
CORBA_ITF_EPILOG
   return object_size;
  //## end cCorbaCellProxy::GetObject%1238436652.body
}

void cCorbaCellProxy::SetObject (const cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::SetObject%1238436653.body preserve=yes
  //## end cCorbaCellProxy::SetObject%1238436653.body
}

void cCorbaCellProxy::SetItf ()
{
  //## begin cCorbaCellProxy::SetItf%1054632839.body preserve=yes
   ReleaseItf();
CORBA_BIND_PROLOG("iCell", _IOR.c_str())
   _CorbaObject = cBroker::Orb()->string_to_object(_IOR.c_str());
   if (_CallTimeout != 0) {
      omniORB::setClientCallTimeout(_CorbaObject, _CallTimeout);
   }
   Control::iCell_var * cell_ref = new Control::iCell_var;
   *cell_ref = Control::iCell::_narrow(_CorbaObject);
   _Itf = cell_ref;
   _Synchronized = false;
CORBA_BIND_EPILOG
  //## end cCorbaCellProxy::SetItf%1054632839.body
}

void cCorbaCellProxy::ReleaseItf ()
{
  //## begin cCorbaCellProxy::ReleaseItf%1054632840.body preserve=yes
   if (_Itf != NULL) {
      try {
         CORBA::Object * object = _CorbaObject;
         Control::iCell_var * itf = _Itf;
         _Itf = NULL;
         _CorbaObject = NULL;
         delete itf;
//         delete object;
// CORBA::Object instances may not be explicitly deleted
// see omniObjRef::~omniObjRef() in omniORB\src\lib\omniORB\orbcore\omniObjRef.cc
      } catch (const Control::AppException & e) {
         ErrorPrintf("AppException when releasing cCorbaCellProxy\n", e.ErrCode, e.NativeCode, e.Param1, e.Param2, e.Param3, e.Param4);
      } catch (CORBA::COMM_FAILURE & e) {
         ErrorPrintf("CORBA::COMM_FAILURE when releasing cCorbaCellProxy\n");
      } catch (CORBA::SystemException & e) {
         ErrorPrintf("CORBA::SystemException when releasing cCorbaCellProxy\n");
      } catch(CORBA::Exception & e) {
         ErrorPrintf("CORBA::Exception when releasing cCorbaCellProxy\n");
      } catch (...) {
         ErrorPrintf("unknown exception when releasing cCorbaCellProxy\n");
      }
      _Synchronized = false;
   }
  //## end cCorbaCellProxy::ReleaseItf%1054632840.body
}

BOOL_T cCorbaCellProxy::Ping ()
{
  //## begin cCorbaCellProxy::Ping%1134227774.body preserve=yes
   try {
      STRING_T name = Name();
      if (name == get_ProxyName()) {
         return true;
      } else {
         return false;
      }
   } catch (...) {
      return false;
   }
  //## end cCorbaCellProxy::Ping%1134227774.body
}

STRING_T cCorbaCellProxy::Request (CONST_STRING_T request)
{
  //## begin cCorbaCellProxy::Request%1242995033.body preserve=yes
   return "no implemetation";
  //## end cCorbaCellProxy::Request%1242995033.body
}

STRING_T cCorbaCellProxy::GetRing (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCorbaCellProxy::GetRing%1242995034.body preserve=yes
   STRING_T objects;
CORBA_ITF_PROLOG("iCell::GetObject", _Itf)
   objects = (*_Itf)->GetRing(_ClientId, var_name, i1, i2, i3, i4, flags);
   _Connected = true;
CORBA_ITF_EPILOG
   return objects;
  //## end cCorbaCellProxy::GetRing%1242995034.body
}

void cCorbaCellProxy::ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async)
{
  //## begin cCorbaCellProxy::ExecuteJob%1244547096.body preserve=yes
CORBA_ITF_PROLOG("iCell::ExecuteJob", _Itf)
   (*_Itf)->ExecuteJob(_ClientId, program_name, job, async);
   _Connected = true;
CORBA_ITF_EPILOG
  //## end cCorbaCellProxy::ExecuteJob%1244547096.body
}

// Additional Declarations
  //## begin cCorbaCellProxy%3C4EE681039C.declarations preserve=yes
  //## end cCorbaCellProxy%3C4EE681039C.declarations

//## begin module%3C4EE681039C.epilog preserve=yes
//## end module%3C4EE681039C.epilog
