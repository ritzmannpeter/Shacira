//## begin module%3FE745260261.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE745260261.cm

//## begin module%3FE745260261.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE745260261.cp

//## Module: cProgram%3FE745260261; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cProgram.cpp

//## begin module%3FE745260261.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FE745260261.additionalIncludes

//## begin module%3FE745260261.includes preserve=yes

/// PR 10.01.06 - added error log messages when accessing unknown variables
/// PR 11.01.07 - supplied flags value to local variable in all Get and Set calls
/// PR 22.12.07 - fixed bug that caused indefinite recursion cProgram::Set(..., FLOAT_T value)
/// PR 30.10.12 - minimized blocking duration of _EventQueueMutex in ProcessEventQueue(..)
/// PR 05.11.12 - added process event duration analysis (Gerhard Himmelsbach Nela)

#include "stdarg.h"

//## end module%3FE745260261.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cObjectQueue
#include "System/Objects/cObjectQueue.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cProgram
#include "Control/Cell/cProgram.h"
//## begin module%3FE745260261.additionalDeclarations preserve=yes

#if (_MSC_VER < 1300) 

#include <new>
#include <new.h>

#pragma warning(disable: 4073)
#pragma init_seg(lib)

namespace
{
int NewHandlerFunc(size_t) 
{
//   throw std::bad_alloc();
   throw cError(BAD_NEW, 0);
   return 0;
}
class NewHandler
{
public:
   NewHandler() 
   {
      _OldHandler = _set_new_handler(NewHandlerFunc);
   }
   ~NewHandler() 
   {
      _set_new_handler(_OldHandler);
   }
private:
   _PNH _OldHandler;
}  _NewHandler; 
}

#endif

static char _Text[0x4000] = {0};
#define UNDEF_ERROR(var_name) ErrorPrintf("warning: variable %s undefined in %s\n", var_name, _Name.c_str());

//## end module%3FE745260261.additionalDeclarations


// Class cProgram 














cProgram::cProgram()
  //## begin cProgram::cProgram%.hasinit preserve=no
      : _Verbose(false), _StartDelay(0), _IFType(IF_PROPRIETARY), _Initialized(false), _DebugLevel(0), _ProgramThreadId(0), _AsyncThreadId(0), _UserThreadId(0), _EventQueue(NULL), _Context(NULL)
  //## end cProgram::cProgram%.hasinit
  //## begin cProgram::cProgram%.initialization preserve=yes
  //## end cProgram::cProgram%.initialization
{
  //## begin cProgram::cProgram%.body preserve=yes
_ASSERT_UNCOND
  //## end cProgram::cProgram%.body
}

cProgram::cProgram(const cProgram &right)
  //## begin cProgram::cProgram%copy.hasinit preserve=no
      : _Verbose(false), _StartDelay(0), _IFType(IF_PROPRIETARY), _Initialized(false), _DebugLevel(0), _ProgramThreadId(0), _AsyncThreadId(0), _UserThreadId(0), _EventQueue(NULL), _Context(NULL)
  //## end cProgram::cProgram%copy.hasinit
  //## begin cProgram::cProgram%copy.initialization preserve=yes
  //## end cProgram::cProgram%copy.initialization
{
  //## begin cProgram::cProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProgram::cProgram%copy.body
}

cProgram::cProgram (cConfigurationObject *config_obj, cContext *context)
  //## begin cProgram::cProgram%1072120959.hasinit preserve=no
      : _Verbose(false), _StartDelay(0), _IFType(IF_PROPRIETARY), _Initialized(false), _DebugLevel(0), _ProgramThreadId(0), _AsyncThreadId(0), _UserThreadId(0), _EventQueue(NULL), _Context(NULL), _MaxProcessEventDuration(0)
  //## end cProgram::cProgram%1072120959.hasinit
  //## begin cProgram::cProgram%1072120959.initialization preserve=yes
  //## end cProgram::cProgram%1072120959.initialization
{
  //## begin cProgram::cProgram%1072120959.body preserve=yes
_ASSERT_COND(context != NULL)
   _Name = config_obj->get_Name();
   _Context = context;
   _IdleTime = config_obj->PropertyValue("IdleTime", _IdleTime);
   _TimeControl = config_obj->PropertyValue("TimeControl", _TimeControl);
   _CycleTimeSet = config_obj->PropertyValue("CycleTimeSet", _CycleTimeSet);
   _DebugLevel = config_obj->PropertyValue("DebugLevel", _DebugLevel);
   _StartDelay = config_obj->PropertyValue("StartDelay", _StartDelay);
   _Verbose = config_obj->PropertyValue("Verbose", _Verbose);
   _EventQueue = new cObjectQueue(0x2000);
  //## end cProgram::cProgram%1072120959.body
}

cProgram::cProgram (CONST_STRING_T name, cContext *context)
  //## begin cProgram::cProgram%1122375232.hasinit preserve=no
      : _Verbose(false), _StartDelay(0), _IFType(IF_PROPRIETARY), _Initialized(false), _DebugLevel(0), _ProgramThreadId(0), _AsyncThreadId(0), _UserThreadId(0), _EventQueue(NULL), _Context(NULL)
  //## end cProgram::cProgram%1122375232.hasinit
  //## begin cProgram::cProgram%1122375232.initialization preserve=yes
  //## end cProgram::cProgram%1122375232.initialization
{
  //## begin cProgram::cProgram%1122375232.body preserve=yes
_ASSERT_COND(context != NULL)
   _Name = name;
   _Context = context;
   _EventQueue = new cObjectQueue(0x2000);
  //## end cProgram::cProgram%1122375232.body
}


cProgram::~cProgram()
{
  //## begin cProgram::~cProgram%.body preserve=yes
   if (_EventQueue != NULL) {
      delete _EventQueue;
   }
  //## end cProgram::~cProgram%.body
}

INT_T cProgram::ControlFunc ()
{
  //## begin cProgram::ControlFunc%1072120961.body preserve=yes
   try {
      if (!_Initialized) {
         _ProgramThreadId = cSystemUtils::ThreadId();
         if (_StartDelay > 0) cSystemUtils::Suspend(_StartDelay);
         Initialize();
         _Initialized = true;
         return 0;
      }
      ProcessEventQueue();
      ProcessJobQueue();
      Cycle();
      return 0;
   } catch (cError & e) {
      ErrorPrintf("cycle of program %s: error %s\n", _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception in cycle of program %s\n", _Name.c_str());
   }
   return 0;
  //## end cProgram::ControlFunc%1072120961.body
}

void cProgram::Object (cTransientObject *object)
{
  //## begin cProgram::Object%1073642243.body preserve=yes
   try {
      ULONG_T t_start = cSystemUtils::RealtimeOffset();
      ULONG_T t_end = 0;
      ProcessEvent(object);
      t_end = cSystemUtils::RealtimeOffset();
      ULONG_T duration = t_end - t_start;
      if (duration > _MaxProcessEventDuration) {
         _MaxProcessEventDuration = duration;
         DCPrintf("[%s] New maximum ProcessEvent Handling : %d\n", _Name.c_str(), _MaxProcessEventDuration);
      }
      return;
   } catch (cError & e) {
      ErrorPrintf("event processing of program %s: error %s\n", _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception in event processing of program %s\n", _Name.c_str());
   }
  //## end cProgram::Object%1073642243.body
}

void cProgram::ExecuteCommand (ULONG_T command)
{
  //## begin cProgram::ExecuteCommand%1089292609.body preserve=yes
  //## end cProgram::ExecuteCommand%1089292609.body
}

void cProgram::ExecuteRequest (STRING_T &reply, CONST_STRING_T request)
{
  //## begin cProgram::ExecuteRequest%1133771771.body preserve=yes
  //## end cProgram::ExecuteRequest%1133771771.body
}

void cProgram::Stop ()
{
  //## begin cProgram::Stop%1090071073.body preserve=yes
   cControlThread::Stop();
  //## end cProgram::Stop%1090071073.body
}

void cProgram::Restart ()
{
  //## begin cProgram::Restart%1090071074.body preserve=yes
  //## end cProgram::Restart%1090071074.body
}

void cProgram::Set (cVarRef *var_ref, BOOL_T value)
{
  //## begin cProgram::Set%1078844334.body preserve=yes
   Set(var_ref, value ? (ULONG_T)1 : (ULONG_T)0);
  //## end cProgram::Set%1078844334.body
}

void cProgram::Set (cVarRef *var_ref, CHAR_T value)
{
  //## begin cProgram::Set%1078844335.body preserve=yes
   Set(var_ref, (ULONG_T)value);
  //## end cProgram::Set%1078844335.body
}

void cProgram::Set (cVarRef *var_ref, UCHAR_T value)
{
  //## begin cProgram::Set%1078844336.body preserve=yes
   Set(var_ref, (ULONG_T)value);
  //## end cProgram::Set%1078844336.body
}

void cProgram::Set (cVarRef *var_ref, SHORT_T value)
{
  //## begin cProgram::Set%1078844337.body preserve=yes
   Set(var_ref, (ULONG_T)value);
  //## end cProgram::Set%1078844337.body
}

void cProgram::Set (cVarRef *var_ref, USHORT_T value)
{
  //## begin cProgram::Set%1078844338.body preserve=yes
   Set(var_ref, (ULONG_T)value);
  //## end cProgram::Set%1078844338.body
}

void cProgram::Set (cVarRef *var_ref, LONG_T value)
{
  //## begin cProgram::Set%1078844339.body preserve=yes
   Set(var_ref, (ULONG_T)value);
  //## end cProgram::Set%1078844339.body
}

void cProgram::Set (cVarRef *var_ref, ULONG_T value)
{
  //## begin cProgram::Set%1078844321.body preserve=yes
   try {
      var_ref->SetValue(value);
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
  //## end cProgram::Set%1078844321.body
}

void cProgram::Set (cVarRef *var_ref, FLOAT_T value)
{
  //## begin cProgram::Set%1078844340.body preserve=yes
   DOUBLE_T dval = value;
   Set(var_ref, dval);
  //## end cProgram::Set%1078844340.body
}

void cProgram::Set (cVarRef *var_ref, DOUBLE_T value)
{
  //## begin cProgram::Set%1078844322.body preserve=yes
   try {
      var_ref->SetValue(value);
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
  //## end cProgram::Set%1078844322.body
}

void cProgram::Set (cVarRef *var_ref, CONST_STRING_T value)
{
  //## begin cProgram::Set%1078844323.body preserve=yes
   try {
      var_ref->SetValue(value);
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
  //## end cProgram::Set%1078844323.body
}

void cProgram::Set (cVarRef *var_ref, BUF_T buf, ULONG_T size)
{
  //## begin cProgram::Set%1078844324.body preserve=yes
   try {
      var_ref->SetValue(buf, size);
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
  //## end cProgram::Set%1078844324.body
}

ULONG_T cProgram::GetInt (cVarRef *var_ref)
{
  //## begin cProgram::GetInt%1078844325.body preserve=yes
   try {
      ULONG_T value = 0;
      var_ref->GetValue(value);
      return value;
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
   return 0;
  //## end cProgram::GetInt%1078844325.body
}

DOUBLE_T cProgram::GetReal (cVarRef *var_ref)
{
  //## begin cProgram::GetReal%1078844326.body preserve=yes
   try {
      DOUBLE_T value = 0;
      var_ref->GetValue(value);
      return value;
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
   return 0;
  //## end cProgram::GetReal%1078844326.body
}

STRING_T cProgram::GetString (cVarRef *var_ref)
{
  //## begin cProgram::GetString%1078844327.body preserve=yes
   try {
      STRING_T value;
      var_ref->GetValue(value);
      return value;
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
   return "";
  //## end cProgram::GetString%1078844327.body
}

BUF_T cProgram::GetBuf (cVarRef *var_ref)
{
  //## begin cProgram::GetBuf%1078844328.body preserve=yes
   try {
      BUF_T buf = NULL;
      var_ref->GetValue(buf);
      return buf;
   } catch (cError & e) {
      ErrorPrintf("failed to set var ref %s in program %s: error %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("unhandled exception setting var ref %s in program %s\n",
                  var_ref->_Spec.c_str(), _Name.c_str());
   }
   return NULL;
  //## end cProgram::GetBuf%1078844328.body
}

void cProgram::Refresh (cVarRef *var_ref)
{
  //## begin cProgram::Refresh%1078844341.body preserve=yes
   UCHAR_T data_type = var_ref->DataType();
   if (data_type == SH_BYTE || data_type == SH_OBJECT) {
      BUF_T buf = NULL;
      var_ref->GetValue(buf);
   }
  //## end cProgram::Refresh%1078844341.body
}

void cProgram::SetVar (CONST_STRING_T var_name, BOOL_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985435.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value ? 1L : 0L, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985435.body
}

void cProgram::SetVar (CONST_STRING_T var_name, CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985436.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985436.body
}

void cProgram::SetVar (CONST_STRING_T var_name, UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985437.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985437.body
}

void cProgram::SetVar (CONST_STRING_T var_name, SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985438.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985438.body
}

void cProgram::SetVar (CONST_STRING_T var_name, USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985439.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985439.body
}

void cProgram::SetVar (CONST_STRING_T var_name, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985440.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985440.body
}

void cProgram::SetVar (CONST_STRING_T var_name, ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985441.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985441.body
}

void cProgram::SetVar (CONST_STRING_T var_name, FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985442.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985442.body
}

void cProgram::SetVar (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985443.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985443.body
}

void cProgram::SetVar (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985444.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985444.body
}

void cProgram::SetVar (CONST_STRING_T var_name, BUF_T buf, ULONG_T size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::SetVar%1080985445.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(buf, size, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::SetVar%1080985445.body
}

void cProgram::GetVar (CONST_STRING_T var_name, BOOL_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985446.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      UCHAR_T temp_val = 0;
      variable->Get(temp_val, i1, i2, i3, i4, flags);
      value = (temp_val == 0) ? false : true;
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985446.body
}

void cProgram::GetVar (CONST_STRING_T var_name, CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985447.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985447.body
}

void cProgram::GetVar (CONST_STRING_T var_name, UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985448.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985448.body
}

void cProgram::GetVar (CONST_STRING_T var_name, SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985449.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985449.body
}

void cProgram::GetVar (CONST_STRING_T var_name, USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985450.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985450.body
}

void cProgram::GetVar (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985451.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985451.body
}

void cProgram::GetVar (CONST_STRING_T var_name, ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985452.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985452.body
}

void cProgram::GetVar (CONST_STRING_T var_name, FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985453.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985453.body
}

void cProgram::GetVar (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985454.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985454.body
}

void cProgram::GetVar (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985455.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985455.body
}

void cProgram::GetVar (CONST_STRING_T var_name, BUF_T &buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985456.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(buf, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985456.body
}

void cProgram::GetVar (CONST_STRING_T var_name, BUF_T buf, ULONG_T size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::GetVar%1080985457.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(buf, size, size, i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::GetVar%1080985457.body
}

void cProgram::RefreshVar (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cProgram::RefreshVar%1092325288.body preserve=yes
   cVariable * variable = _Context->Variable(var_name);
   if (variable != NULL) {
      variable->Refresh(i1, i2, i3, i4, flags);
   } else {
      UNDEF_ERROR(var_name)
   }
  //## end cProgram::RefreshVar%1092325288.body
}

void cProgram::ClearAlarm (ULONG_T ident)
{
  //## begin cProgram::ClearAlarm%1081425530.body preserve=yes
   _Context->ClearAlarm(ident);
#ifdef _26_
   if (_Cell != NULL) {
      _Cell->ClearAlarm(ident);
   }
#endif
  //## end cProgram::ClearAlarm%1081425530.body
}

void cProgram::ClearAlarms ()
{
  //## begin cProgram::ClearAlarms%1081425632.body preserve=yes
   _Context->ClearAlarms();
#ifdef _26_
   if (_Cell != NULL) {
      _Cell->ClearAlarms();
   }
#endif
  //## end cProgram::ClearAlarms%1081425632.body
}

void cProgram::DebugPrintf (ULONG_T debug_level, CONST_STRING_T fmt_str, ... )
{
  //## begin cProgram::DebugPrintf%1081970260.body preserve=yes
   if (debug_level > _DebugLevel) return;
   STRING_T file = cResources::LogPath();
   file = cFileSystemUtils::AppendPath(file.c_str(), _Name.c_str());
   file += ".log";
   try {
      va_list args;
      va_start(args, fmt_str);
      _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
      va_end(args);
      FILE * stream = fopen(file.c_str(), "a");
      if (stream != NULL) {
         fprintf(stream, "%s", _Text);
         fclose(stream);
      }
   } catch (...) {
   }
  //## end cProgram::DebugPrintf%1081970260.body
}

BOOL_T cProgram::UserContext ()
{
  //## begin cProgram::UserContext%1090071075.body preserve=yes
   if (cSystemUtils::ThreadId() == _UserThreadId) {
      return true;
   } else {
      return false;
   }
  //## end cProgram::UserContext%1090071075.body
}

BOOL_T cProgram::ProgramContext ()
{
  //## begin cProgram::ProgramContext%1090071076.body preserve=yes
   if (cSystemUtils::ThreadId() == _ProgramThreadId) {
      return true;
   } else {
      return false;
   }
  //## end cProgram::ProgramContext%1090071076.body
}

BOOL_T cProgram::AsyncContext ()
{
  //## begin cProgram::AsyncContext%1090071077.body preserve=yes
   if (cSystemUtils::ThreadId() == _AsyncThreadId) {
      return true;
   } else {
      return false;
   }
  //## end cProgram::AsyncContext%1090071077.body
}

void cProgram::Get (CONST_STRING_T var_spec, STRING_T &value)
{
  //## begin cProgram::Get%1117548695.body preserve=yes
   cVarRef * var_ref = _Context->VarRef(var_spec);
   if (var_ref != NULL) {
      var_ref->GetValue(value);
   }
  //## end cProgram::Get%1117548695.body
}

void cProgram::Get (CONST_STRING_T var_spec, LONG_T &value)
{
  //## begin cProgram::Get%1117548696.body preserve=yes
   cVarRef * var_ref = _Context->VarRef(var_spec);
   if (var_ref != NULL) {
      var_ref->GetValue(value);
   }
  //## end cProgram::Get%1117548696.body
}

void cProgram::Get (CONST_STRING_T var_spec, DOUBLE_T &value)
{
  //## begin cProgram::Get%1117548697.body preserve=yes
   cVarRef * var_ref = _Context->VarRef(var_spec);
   if (var_ref != NULL) {
      var_ref->GetValue(value);
   }
  //## end cProgram::Get%1117548697.body
}

void cProgram::SetProgress (ULONG_T indicator, ULONG_T value)
{
  //## begin cProgram::SetProgress%1120660729.body preserve=yes
   _Context->SetProgress(indicator, value);
#ifdef _26_
   if (_Cell != NULL) {
      _Cell->SetProgress(indicator, value);
   }
#endif
  //## end cProgram::SetProgress%1120660729.body
}

BOOL_T cProgram::DispatchEvent (cTransientObject *object)
{
  //## begin cProgram::DispatchEvent%1175495042.body preserve=yes
   ULONG_T my_thread_id = cSystemUtils::ThreadId();
   if (_ProgramThreadId != my_thread_id &&
       _EventQueue != NULL &&
       !_EventQueue->IsFull()) {
      cObjectLock __obj_lock__(&_EventQueueMutex);
      _EventQueue->Add(object);
      return true;
   } else {
      return false;
   }
  //## end cProgram::DispatchEvent%1175495042.body
}

void cProgram::ProcessEventQueue ()
{
  //## begin cProgram::ProcessEventQueue%1175495043.body preserve=yes
   std::list<cTransientObject*> local_object_list;
   try {
      cObjectLock __obj_lock__(&_EventQueueMutex);
      cTransientObject * object = _EventQueue->GetNext();
      while (object != NULL) {
         local_object_list.push_back(object);
         object = _EventQueue->GetNext();
      }
   } catch(cError & e) {
      ErrorPrintf("%s while preparing event queue in\n", e.ErrMsg().c_str(), get_Name().c_str());
      return;
   } catch (...) {
      ErrorPrintf("unhandled exception while preparing event queue in\n", get_Name().c_str());
      return;
   }
   try {
      std::list<cTransientObject*>::const_iterator i = local_object_list.begin();
      while (i != local_object_list.end()) {
         cTransientObject * object = (*i);
         ProcessEvent(object);
         object->Release();
         i++;
      }
   } catch(cError & e) {
      ErrorPrintf("%s while processing event queue in\n", e.ErrMsg().c_str(), get_Name().c_str());
   } catch (...) {
      ErrorPrintf("unhandled exception while processing event queue in\n", get_Name().c_str());
   }
  //## end cProgram::ProcessEventQueue%1175495043.body
}

void cProgram::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   _Context->Save(refresh_type, refresh_value);
}

void cProgram::ExecuteJob (CONST_STRING_T job, BOOL_T async)
{
  //## begin cProgram::ExecuteJob%1244549648.body preserve=yes
   if (async) {
      _JobQueue.AddJob(job);
   } else {
      ProcessJob(job, false);
   }
  //## end cProgram::ExecuteJob%1244549648.body
}

void cProgram::ProcessJobQueue ()
{
  //## begin cProgram::ProcessJobQueue%1244549649.body preserve=yes
   STRING_T job;
   while (_JobQueue.GetJob(job)) {
      ProcessJob(job.c_str(), true);
   }
  //## end cProgram::ProcessJobQueue%1244549649.body
}

void cProgram::ProcessJob (CONST_STRING_T job, BOOL_T async)
{
  //## begin cProgram::ProcessJob%1244551835.body preserve=yes
  //## end cProgram::ProcessJob%1244551835.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cProgram::get_Verbose () const
{
  //## begin cProgram::get_Verbose%43B93E400327.get preserve=no
  return _Verbose;
  //## end cProgram::get_Verbose%43B93E400327.get
}

void cProgram::set_Verbose (BOOL_T value)
{
  //## begin cProgram::set_Verbose%43B93E400327.set preserve=no
  _Verbose = value;
  //## end cProgram::set_Verbose%43B93E400327.set
}

ULONG_T cProgram::get_StartDelay () const
{
  //## begin cProgram::get_StartDelay%40960061032C.get preserve=no
  return _StartDelay;
  //## end cProgram::get_StartDelay%40960061032C.get
}

void cProgram::set_StartDelay (ULONG_T value)
{
  //## begin cProgram::set_StartDelay%40960061032C.set preserve=no
  _StartDelay = value;
  //## end cProgram::set_StartDelay%40960061032C.set
}

LONG_T cProgram::get_IFType () const
{
  //## begin cProgram::get_IFType%43B15F190264.get preserve=no
  return _IFType;
  //## end cProgram::get_IFType%43B15F190264.get
}

void cProgram::set_IFType (LONG_T value)
{
  //## begin cProgram::set_IFType%43B15F190264.set preserve=no
  _IFType = value;
  //## end cProgram::set_IFType%43B15F190264.set
}

// Additional Declarations
  //## begin cProgram%3FE745260261.declarations preserve=yes
  //## end cProgram%3FE745260261.declarations

//## begin module%3FE745260261.epilog preserve=yes
//## end module%3FE745260261.epilog

