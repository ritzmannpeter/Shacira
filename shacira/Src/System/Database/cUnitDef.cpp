//## begin module%4224A214030D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4224A214030D.cm

//## begin module%4224A214030D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4224A214030D.cp

//## Module: cUnitDef%4224A214030D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cUnitDef.cpp

//## begin module%4224A214030D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4224A214030D.additionalIncludes

//## begin module%4224A214030D.includes preserve=yes

/// PR 09.05.05 - added control to GetValue methods via GETVALUE_PROLOG GETVALUE_EPILOG
///               to catch exceptions originating in user functions 
/// PR 13.02.07 - exchanged float and double conversions in ::GetValue(STRING_T &, ...)
/// PR 05.07.07 - added methods and attributes used for input state sensitive handling of datasets
///               TargetDependent
///               ::UnitCode
/// PR 06.07.07 - removed obselete method UnitCode

//## end module%4224A214030D.includes

// cContext
#include "System/Database/cContext.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
//## begin module%4224A214030D.additionalDeclarations preserve=yes

#define GETVALUE_PROLOG try {
#define GETVALUE_EPILOG \
   } catch (cError & e) { \
      STRING_T ref; \
      try { \
         ref = _FuncRef->_Name; \
      } catch (...) { \
      } \
      InfoPrintf("%s in unit function reference %s\n", (const char *)e, ref.c_str()); \
   } catch (...) { \
      STRING_T ref; \
      try { \
         ref = _FuncRef->_Name; \
      } catch (...) { \
      } \
      InfoPrintf("unhandled exception in unit function reference %s\n", ref.c_str()); \
   }

#define SET_FLAGS \
   ULONG_T flags = 0; \
   SET_SOURCE(flags, source) \
   if (destination == -1) { \
      destination = GetCurrentState(); \
   } \
   if (source == destination) { \
      return; \
   } \
   SET_DESTINATION(flags, destination)

//## end module%4224A214030D.additionalDeclarations


// Class cUnitDef 













cUnitDef::cUnitDef()
  //## begin cUnitDef::cUnitDef%.hasinit preserve=no
      : _DataType(UNDEFINED), _DeviceState(0), _DatasetState(0), _TargetDependent(false), _CurrentState(0), _UnitSpecCount(0), _Context(NULL), _FuncRef(NULL), _DevStateFuncRef(NULL)
  //## end cUnitDef::cUnitDef%.hasinit
  //## begin cUnitDef::cUnitDef%.initialization preserve=yes
  //## end cUnitDef::cUnitDef%.initialization
{
  //## begin cUnitDef::cUnitDef%.body preserve=yes
   memset(_CurrentStates, 0, sizeof(_CurrentStates));
   for (int i=0; i<MAX_DIM_DEFINITIONS; i++) {
      _UnitSpecs[i] = NULL;
   }
  //## end cUnitDef::cUnitDef%.body
}

cUnitDef::cUnitDef(const cUnitDef &right)
  //## begin cUnitDef::cUnitDef%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _DeviceState(0), _DatasetState(0), _TargetDependent(false), _CurrentState(0), _UnitSpecCount(0), _Context(NULL), _FuncRef(NULL), _DevStateFuncRef(NULL)
  //## end cUnitDef::cUnitDef%copy.hasinit
  //## begin cUnitDef::cUnitDef%copy.initialization preserve=yes
  //## end cUnitDef::cUnitDef%copy.initialization
{
  //## begin cUnitDef::cUnitDef%copy.body preserve=yes
_ASSERT_UNCOND
   memset(_CurrentStates, 0, sizeof(_CurrentStates));
   for (int i=0; i<MAX_DIM_DEFINITIONS; i++) {
      _UnitSpecs[i] = NULL;
   }
  //## end cUnitDef::cUnitDef%copy.body
}

cUnitDef::cUnitDef (UCHAR_T data_type, cContext *context)
  //## begin cUnitDef::cUnitDef%1111233643.hasinit preserve=no
      : _DataType(UNDEFINED), _DeviceState(0), _DatasetState(0), _TargetDependent(false), _CurrentState(0), _UnitSpecCount(0), _Context(NULL), _FuncRef(NULL), _DevStateFuncRef(NULL)
  //## end cUnitDef::cUnitDef%1111233643.hasinit
  //## begin cUnitDef::cUnitDef%1111233643.initialization preserve=yes
  //## end cUnitDef::cUnitDef%1111233643.initialization
{
  //## begin cUnitDef::cUnitDef%1111233643.body preserve=yes
   memset(_CurrentStates, 0, sizeof(_CurrentStates));
   for (int i=0; i<MAX_DIM_DEFINITIONS; i++) {
      _UnitSpecs[i] = NULL;
   }
   _DataType = data_type;
   _Context = context;
  //## end cUnitDef::cUnitDef%1111233643.body
}


cUnitDef::~cUnitDef()
{
  //## begin cUnitDef::~cUnitDef%.body preserve=yes
   for (int i=0; i<MAX_DIM_DEFINITIONS; i++) {
      cUnitSpec * unit_spec = _UnitSpecs[i];
      if (unit_spec != NULL) {
         delete unit_spec;
      }
   }
  //## end cUnitDef::~cUnitDef%.body
}



//## Other Operations (implementation)
void cUnitDef::SetState (UCHAR_T state)
{
  //## begin cUnitDef::SetState%1109759952.body preserve=yes
   SetCurrentState(state);
  //## end cUnitDef::SetState%1109759952.body
}

UCHAR_T cUnitDef::GetState ()
{
  //## begin cUnitDef::GetState%1111243133.body preserve=yes
   return GetCurrentState();
  //## end cUnitDef::GetState%1111243133.body
}

STRING_T cUnitDef::UnitText (CHAR_T state)
{
  //## begin cUnitDef::UnitText%1109759953.body preserve=yes
   if (state == -1) {
      state = GetCurrentState();
   }
   cUnitSpec * unit_spec = UnitSpec(state);
   if (unit_spec != NULL) {
      return unit_spec->_UnitText;
   } else {
      return "?";
   }
  //## end cUnitDef::UnitText%1109759953.body
}

UCHAR_T cUnitDef::Precision (CHAR_T state)
{
  //## begin cUnitDef::Precision%1109759954.body preserve=yes
   if (state == -1) {
      state = GetCurrentState();
   }
   cUnitSpec * unit_spec = UnitSpec(state);
   if (unit_spec != NULL) {
      return unit_spec->_Precision;
   } else {
      return 0;
   }
  //## end cUnitDef::Precision%1109759954.body
}

void cUnitDef::GetValue (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759955.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (CHAR_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (CHAR_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (CHAR_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759955.body
}

void cUnitDef::GetValue (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759956.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (UCHAR_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (UCHAR_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (UCHAR_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759956.body
}

void cUnitDef::GetValue (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759957.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (SHORT_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (SHORT_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (SHORT_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759957.body
}

void cUnitDef::GetValue (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759958.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (USHORT_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (USHORT_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (USHORT_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759958.body
}

void cUnitDef::GetValue (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759959.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (LONG_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = (FLOAT_T)value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (LONG_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = (DOUBLE_T)value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (LONG_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759959.body
}

void cUnitDef::GetValue (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759960.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (ULONG_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = (FLOAT_T)value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (ULONG_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = (DOUBLE_T)value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (ULONG_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759960.body
}

void cUnitDef::GetValue (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759961.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = (LONG_T)value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (FLOAT_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (FLOAT_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759961.body
}

void cUnitDef::GetValue (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1109759962.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = (LONG_T)value;
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            value = (DOUBLE_T)lvalue;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = (FLOAT_T)value;
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            value = (DOUBLE_T)fvalue;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = value;
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            value = (DOUBLE_T)dvalue;
         }
		   break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1109759962.body
}

void cUnitDef::GetValue (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination)
{
  //## begin cUnitDef::GetValue%1151480220.body preserve=yes
   GETVALUE_PROLOG
   SET_FLAGS
   if (_FuncRef != NULL) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            LONG_T lvalue = atol(value.c_str());
            _FuncRef->CallUnitFunc(lvalue, lvalue, flags, i1, i2, i3, i4);
            cSHVariant::Long2String(value,lvalue);
         }
         break;
      case SH_FLOAT:
         {
            FLOAT_T fvalue = (FLOAT_T)atof(value.c_str());
            _FuncRef->CallUnitFunc(fvalue, fvalue, flags, i1, i2, i3, i4);
            cSHVariant::Float2String(value, fvalue, Precision(destination));
         }
         break;
      case SH_DOUBLE:
         {
            DOUBLE_T dvalue = atof(value.c_str());
            _FuncRef->CallUnitFunc(dvalue, dvalue, flags, i1, i2, i3, i4);
            cSHVariant::Double2String(value, dvalue, Precision(destination));
         }
         break;
      }
   }
   GETVALUE_EPILOG
  //## end cUnitDef::GetValue%1151480220.body
}

void cUnitDef::AddUnitSpec (CONST_STRING_T unit_text, UCHAR_T precision)
{
  //## begin cUnitDef::AddUnitSpec%1111588837.body preserve=yes
   int index = _UnitSpecCount;
   if (index < MAX_DIM_DEFINITIONS) {
      cUnitSpec * unit_spec = new cUnitSpec(unit_text, precision);
      _UnitSpecs[index] = unit_spec;
      _UnitSpecCount++;
   }
  //## end cUnitDef::AddUnitSpec%1111588837.body
}

cUnitSpec * cUnitDef::UnitSpec (UCHAR_T state)
{
  //## begin cUnitDef::UnitSpec%1111588838.body preserve=yes
   if (state >= MAX_DIM_DEFINITIONS) {
      return NULL;
   }
   return _UnitSpecs[state];
  //## end cUnitDef::UnitSpec%1111588838.body
}

void cUnitDef::SetCurrentState (UCHAR_T state)
{
  //## begin cUnitDef::SetCurrentState%1142413728.body preserve=yes
#ifndef BASE_LIBRARY
   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   if (user_info == NULL) {
      _CurrentState = state;
   } else {
      if (cResources::FlagSet(PF_ITF_UNITS)) {
         ULONG_T if_type = user_info->get_IFType();
         if (if_type == 0) {
            _CurrentState = state;
         } else {
            if (if_type < IF_MAX) {
               _CurrentStates[if_type] = state;
            } else {
               _CurrentState = state;
            }
         }
      } else {
         _CurrentState = state;
      }
   }
#endif
   //## end cUnitDef::SetCurrentState%1142413728.body
}

UCHAR_T cUnitDef::GetCurrentState ()
{
  //## begin cUnitDef::GetCurrentState%1142413729.body preserve=yes
#ifndef BASE_LIBRARY
   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   if (user_info == NULL) {
      return _CurrentState;
   } else {
      if (cResources::FlagSet(PF_ITF_UNITS)) {
         ULONG_T if_type = user_info->get_IFType();
         if (if_type == 0) {
            return _CurrentState;
         } else {
            if (if_type < IF_MAX) {
               return _CurrentStates[if_type];
            } else {
               return _CurrentState;
            }
         }
      } else { 
         return _CurrentState;
      }
   }
#else
   return 0;
#endif
   //## end cUnitDef::GetCurrentState%1142413729.body
}

//## Get and Set Operations for Class Attributes (implementation)

UCHAR_T cUnitDef::get_DataType () const
{
  //## begin cUnitDef::get_DataType%4225F1320138.get preserve=no
  return _DataType;
  //## end cUnitDef::get_DataType%4225F1320138.get
}

UCHAR_T cUnitDef::get_DeviceState () const
{
  //## begin cUnitDef::get_DeviceState%4225EBAC0196.get preserve=no
   if (_DevStateFuncRef != NULL) {
      int value = 0;
      int i1 = -1;
      int i2 = -1;
      int i3 = -1;
      int i4 = -1;
      RestoreIndices(i1, i2, i3, i4);
      _DevStateFuncRef->CallDevStateFunc(value, i1, i2, i3, i4);
     return (UCHAR_T)value;
   } else {
      return _DeviceState;
   }
  //## end cUnitDef::get_DeviceState%4225EBAC0196.get
}

void cUnitDef::set_DeviceState (UCHAR_T value)
{
  //## begin cUnitDef::set_DeviceState%4225EBAC0196.set preserve=no
  _DeviceState = value;
  //## end cUnitDef::set_DeviceState%4225EBAC0196.set
}

UCHAR_T cUnitDef::get_DatasetState () const
{
  //## begin cUnitDef::get_DatasetState%423C14400232.get preserve=no
  return _DatasetState;
  //## end cUnitDef::get_DatasetState%423C14400232.get
}

void cUnitDef::set_DatasetState (UCHAR_T value)
{
  //## begin cUnitDef::set_DatasetState%423C14400232.set preserve=no
  _DatasetState = value;
  //## end cUnitDef::set_DatasetState%423C14400232.set
}

BOOL_T cUnitDef::get_TargetDependent () const
{
  //## begin cUnitDef::get_TargetDependent%470A5EB9020B.get preserve=no
  return _TargetDependent;
  //## end cUnitDef::get_TargetDependent%470A5EB9020B.get
}

void cUnitDef::set_TargetDependent (BOOL_T value)
{
  //## begin cUnitDef::set_TargetDependent%470A5EB9020B.set preserve=no
  _TargetDependent = value;
  //## end cUnitDef::set_TargetDependent%470A5EB9020B.set
}

// Additional Declarations
  //## begin cUnitDef%4224A214030D.declarations preserve=yes
  //## end cUnitDef%4224A214030D.declarations

//## begin module%4224A214030D.epilog preserve=yes
//## end module%4224A214030D.epilog

void cUnitDef::set_DevStateFuncRef(cFuncRef* func_ref)
{
   _DevStateFuncRef = func_ref;
}

void cUnitDef::set_FuncRef(cFuncRef* func_ref)
{
   _FuncRef = func_ref;
}

BOOL_T cUnitDef::StoreIndices(int i1, int i2, int i3, int i4)
{
   _CurrentModelIndices.Set(i1, i2, i3, i4);
   return true;
}

BOOL_T cUnitDef::RestoreIndices(int & i1, int & i2, int & i3, int & i4) const
{
   _CurrentModelIndices.Get(i1, i2, i3, i4);
   return true;
}

UCHAR_T cUnitDef::get_DeviceState(int i1, int i2, int i3, int i4)
{
   StoreIndices(i1, i2, i3, i4);
   return get_DeviceState();
}

