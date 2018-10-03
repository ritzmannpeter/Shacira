
#include "FirstHeader.h"
#include "System/Objects/cStaticObject.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Objects/cProtocol.h"
#include <stdarg.h>

ULONG_T cStaticObject::_ObjectCount = 0;

cStaticObject::cStaticObject()
      : _ConfigurationObject(NULL), _Class("StaticObject"), _Type("StaticObject"), _Ident(0), _HasReferences(false)
{
   Parameter("Verbose") = false;
   Parameter("DebugLevel") = (ULONG_T)0;
   _PrintBuffer = NULL;
}

cStaticObject::cStaticObject(cConfigurationObject * config_object)
      : _ConfigurationObject(config_object), _Class("StaticObject"), _Type("StaticObject"), _Ident(0), _HasReferences(false)
{
   Parameter("Verbose") = config_object->PropertyValue("Verbose", (BOOL_T)false);
   Parameter("DebugLevel") = config_object->PropertyValue("DebugLevel", (ULONG_T)0);
   _PrintBuffer = NULL;
}

cStaticObject::~cStaticObject()
{
   if (_PrintBuffer != NULL) {
      cSystemUtils::Free(_PrintBuffer);
   }
}

void cStaticObject::Event (cTransientObject *object)
{
#ifndef BASE_LIBRARY
   throw cError(STATIC_OBJECT_EVENTFUNC_NOTIMPL, 0, _Name.c_str(), 
                cConvUtils::StringValue(object->get_Type()).c_str());
#endif
}

void cStaticObject::RaiseEvent (cTransientObject *object)
{
_ASSERT_COND(object != NULL)
#ifndef BASE_LIBRARY
   LISTENER_LIST_T::const_iterator i = _Listeners.cbegin();
   while (i != _Listeners.cend()) {
      cStaticObject * target = *i;
      target->Event(object);
      i++;
   }
#endif
}

void cStaticObject::ListenTo (cStaticObject *source)
{
   source->AddListener(this);
}

void cStaticObject::Start ()
{
}

void cStaticObject::Stop ()
{
}

void cStaticObject::Protocol(CONST_STRING_T fmt_str, ...)
{
#ifndef BASE_LIBRARY
   if ((BOOL_T)Parameter("Verbose") == false) {
      return;
   }
   try {
      if (_PrintBuffer == NULL) {
         _PrintBuffer = (char*)cSystemUtils::Alloc(0x8000);
      }
      va_list args;
      va_start(args, fmt_str);
      vsprintf(_PrintBuffer, fmt_str, args);
      DCPrintf("[%s]: %s", _Name.c_str(), _PrintBuffer);
      cProtocol * object = new cProtocol(this, _PrintBuffer);
      RaiseEvent(object);
      object->Release();
   } catch (...) {
   }
#endif
}

void cStaticObject::Protocol2(ULONG_T level, CONST_STRING_T fmt_str, ...)
{
#ifndef BASE_LIBRARY
   if ((BOOL_T)Parameter("Verbose") == false) {
      return;
   }
   ULONG_T dbg_level = (ULONG_T)Parameter("DebugLevel");
   if (level > dbg_level) {
      return;
   }
   try {
      if (_PrintBuffer == NULL) {
         _PrintBuffer = (char*)cSystemUtils::Alloc(0x8000);
      }
      va_list args;
      va_start(args, fmt_str);
      vsprintf(_PrintBuffer, fmt_str, args);
      DCPrintf("[%s]: %s", _Name.c_str(), _PrintBuffer);
      cProtocol * object = new cProtocol(this, _PrintBuffer);
      RaiseEvent(object);
      object->Release();
   } catch (...) {
   }
#endif
}

cValue & cStaticObject::Parameter(CONST_STRING_T name)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      cValue * value = new cValue;
      _Parameters[name] = value;
      return *value;
   } else {
      cValue * value = (*i).second;
      return *value;
   }
}

BOOL_T cStaticObject::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   if (PARAM_NAME_EQUALS(name, "shacira_test")) {
      return true;
   } else {
      return false;
   }
}

BOOL_T cStaticObject::SetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      *v = value;
      return true;
   }
}

BOOL_T cStaticObject::SetParam (CONST_STRING_T name, LONG_T value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      *v = value;
      return true;
   }
}

BOOL_T cStaticObject::SetParam (CONST_STRING_T name, ULONG_T value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      *v = value;
      return true;
   }
}

BOOL_T cStaticObject::SetParam (CONST_STRING_T name, DOUBLE_T value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      *v = value;
      return true;
   }
}

BOOL_T cStaticObject::GetParam (CONST_STRING_T name, STRING_T &value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      value = (CONST_STRING_T)*v;
      return true;
   }
}

BOOL_T cStaticObject::GetParam (CONST_STRING_T name, LONG_T &value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      value = (LONG_T)*v;
      return true;
   }
}

BOOL_T cStaticObject::GetParam (CONST_STRING_T name, ULONG_T &value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      value = (ULONG_T)*v;
      return true;
   }
}

BOOL_T cStaticObject::GetParam (CONST_STRING_T name, DOUBLE_T &value)
{
   PARAMETER_MAP_T::const_iterator i = _Parameters.find(name);
   if (i == _Parameters.cend()) {
      return false;
   } else {
      cValue * v = (*i).second;
      value = *v;
      return true;
   }
}

BOOL_T cStaticObject::HasReferences ()
{
   return _HasReferences;
}

void cStaticObject::HasReferences (BOOL_T state)
{
   _HasReferences = state;
}

void cStaticObject::AddListener (cStaticObject *target)
{
   _Listeners.push_back(target);
}

ULONG_T cStaticObject::get_ObjectCount ()
{
   return _ObjectCount;
}

STRING_T cStaticObject::get_Name () const
{
   return _Name;
}

void cStaticObject::set_Name (STRING_T value)
{
   _Name = value;
}

STRING_T cStaticObject::get_Class () const
{
   return _Class;
}

void cStaticObject::set_Class (STRING_T value)
{
   _Class = value;
}

STRING_T cStaticObject::get_Type () const
{
   return _Type;
}

void cStaticObject::set_Type (STRING_T value)
{
   _Type = value;
}

ULONG_T cStaticObject::get_Ident () const
{
   return _Ident;
}

void cStaticObject::set_Ident (ULONG_T value)
{
   _Ident = value;
}

