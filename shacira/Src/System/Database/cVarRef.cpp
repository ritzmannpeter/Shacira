//## begin module%3C7E422F03C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E422F03C0.cm

//## begin module%3C7E422F03C0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E422F03C0.cp

//## Module: cVarRef%3C7E422F03C0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarRef.cpp

//## begin module%3C7E422F03C0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C7E422F03C0.additionalIncludes

//## begin module%3C7E422F03C0.includes preserve=yes

/// PR 28.01.05 - replaced SetControl(control)
///               by method pair AddControl(control) and RemoveControl(control)
///               since a cVarRef can point to more than one control and this
///               was not reflected by the API
/// PR 24.05.05 - removed calling of NewValue, when registering a variable reference
///             - NewValue is now called AddControl for the specific control only
/// PR 13.10.05 - added late binding for forward declared variables (MACRO CHECK_VAR)
/// PR 07.02.06 - added dataset marking (for foreground / background)
/// PR 30.09.14 - introduced total removal of controls from control lists
///               to avoid dangling link problem see cViewInterfacs.cpp
/// PR 23.03.18   destructor must not throw any exception

//## end module%3C7E422F03C0.includes

// cDataChange
#include "System/Objects/cDataChange.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cDataControl
#include "Client/Adapters/cDataControl.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
//## begin module%3C7E422F03C0.additionalDeclarations preserve=yes

#define CHECK_VARIABLE() \
   if (_Variable == NULL) { \
      _Variable = _VarDef->_Variable; \
      if (_Variable == NULL) { \
         _Variable = _Context->Variable(_Name.c_str()); \
      } \
      if (_Variable == NULL) { \
         throw cError(VARREF_NO_VARIABLE, 0, _Name.c_str()); \
      } \
   }

#define SUPPORT_MULTIPLE_CONTROLS

//## end module%3C7E422F03C0.additionalDeclarations


// Class cVarRef 
















cVarRef::cVarRef()
  //## begin cVarRef::cVarRef%.hasinit preserve=no
      : _VarId(-1), _Cached(false), _Flags(0), _ControlList(NULL), _Variable(NULL), _VarDef(NULL), _Control(NULL), _Context(NULL)
  //## end cVarRef::cVarRef%.hasinit
  //## begin cVarRef::cVarRef%.initialization preserve=yes
  //## end cVarRef::cVarRef%.initialization
{
  //## begin cVarRef::cVarRef%.body preserve=yes
_ASSERT_UNCOND
  //## end cVarRef::cVarRef%.body
}

cVarRef::cVarRef(const cVarRef &right)
  //## begin cVarRef::cVarRef%copy.hasinit preserve=no
      : _VarId(-1), _Cached(false), _Flags(0), _ControlList(NULL), _Variable(NULL), _VarDef(NULL), _Control(NULL), _Context(NULL)
  //## end cVarRef::cVarRef%copy.hasinit
  //## begin cVarRef::cVarRef%copy.initialization preserve=yes
  //## end cVarRef::cVarRef%copy.initialization
{
  //## begin cVarRef::cVarRef%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVarRef::cVarRef%copy.body
}

cVarRef::cVarRef (cVarDef *var_def, cContext *context)
  //## begin cVarRef::cVarRef%1040202775.hasinit preserve=no
      : _VarId(-1), _Cached(false), _Flags(0), _ControlList(NULL), _Variable(NULL), _VarDef(NULL), _Control(NULL), _Context(NULL)
  //## end cVarRef::cVarRef%1040202775.hasinit
  //## begin cVarRef::cVarRef%1040202775.initialization preserve=yes
  //## end cVarRef::cVarRef%1040202775.initialization
{
  //## begin cVarRef::cVarRef%1040202775.body preserve=yes
   _Context = context;
   _VarDef = var_def;
   _Variable = _VarDef->_Variable;
   _Name = _VarDef->_VarName;
#ifdef SUPPORT_MULTIPLE_CONTROLS
   _ControlList = new cPtrList;
#endif
  //## end cVarRef::cVarRef%1040202775.body
}


cVarRef::~cVarRef()
{
  //## begin cVarRef::~cVarRef%.body preserve=yes
   if (_Cached) {
      ErrorPrintf("tried to delete cached variable reference %s\n", _Spec.c_str());
   } else {
      if (_ControlList != NULL) {
         delete _ControlList;
      }
   }
  //## end cVarRef::~cVarRef%.body
}



//## Other Operations (implementation)
cVarDef * cVarRef::VarDef ()
{
  //## begin cVarRef::VarDef%1061797997.body preserve=yes
   return _VarDef;
  //## end cVarRef::VarDef%1061797997.body
}

UCHAR_T cVarRef::DataType ()
{
  //## begin cVarRef::DataType%1061797999.body preserve=yes
   return _VarDef->DataType();
  //## end cVarRef::DataType%1061797999.body
}

ULONG_T cVarRef::ValueSize ()
{
  //## begin cVarRef::ValueSize%1072120985.body preserve=yes
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
// PR 24.09.04 this is not the intended size of a value
//      return var_def->_Length;
      return var_def->ElementSize();
   }
   return 0;
  //## end cVarRef::ValueSize%1072120985.body
}

UCHAR_T cVarRef::Precision ()
{
  //## begin cVarRef::Precision%1089187398.body preserve=yes
   // PR 29.03.05 current precision now is precision of current unit specification
   //             if a unit definition is available
   UCHAR_T precision = 0;
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
      precision = var_def->_Precision;
      cUnitDef * unit_def = var_def->get_UnitDef();
      if (unit_def != NULL) {
         precision = unit_def->Precision();
      }
   }
   return precision;
  //## end cVarRef::Precision%1089187398.body
}

UCHAR_T cVarRef::VarType ()
{
  //## begin cVarRef::VarType%1100622395.body preserve=yes
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
      return var_def->_VarType;
   }
   return 0;
  //## end cVarRef::VarType%1100622395.body
}

ULONG_T cVarRef::SystemFlags ()
{
  //## begin cVarRef::SystemFlags%1141722272.body preserve=yes
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
      return var_def->_SystemFlags;
   }
   return 0;
  //## end cVarRef::SystemFlags%1141722272.body
}

ULONG_T cVarRef::Flags ()
{
  //## begin cVarRef::Flags%1141722273.body preserve=yes
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
      return var_def->_Flags;
   }
   return 0;
  //## end cVarRef::Flags%1141722273.body
}

BOOL_T cVarRef::BackgroundVar ()
{
  //## begin cVarRef::BackgroundVar%1100678879.body preserve=yes
   cVarDef * var_def = _Variable->_VarDef;
   if (var_def != NULL) {
      return var_def->_BackgroundVar;
   }
   return false;
  //## end cVarRef::BackgroundVar%1100678879.body
}

void cVarRef::GetValue (CHAR_T &value)
{
  //## begin cVarRef::GetValue%1072120972.body preserve=yes
   LONG_T temp_val = 0;
   GetValue(temp_val);
   value = (CHAR_T)temp_val;
  //## end cVarRef::GetValue%1072120972.body
}

void cVarRef::GetValue (UCHAR_T &value)
{
  //## begin cVarRef::GetValue%1072120973.body preserve=yes
   LONG_T temp_val = 0;
   GetValue(temp_val);
   value = (UCHAR_T)temp_val;
  //## end cVarRef::GetValue%1072120973.body
}

void cVarRef::GetValue (SHORT_T &value)
{
  //## begin cVarRef::GetValue%1072120974.body preserve=yes
   LONG_T temp_val = 0;
   GetValue(temp_val);
   value = (SHORT_T)temp_val;
  //## end cVarRef::GetValue%1072120974.body
}

void cVarRef::GetValue (USHORT_T &value)
{
  //## begin cVarRef::GetValue%1072120975.body preserve=yes
   LONG_T temp_val = 0;
   GetValue(temp_val);
   value = (USHORT_T)temp_val;
  //## end cVarRef::GetValue%1072120975.body
}

void cVarRef::GetValue (LONG_T &value)
{
  //## begin cVarRef::GetValue%1040202785.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Get(value, i1, i2, i3, i4);
  //## end cVarRef::GetValue%1040202785.body
}

void cVarRef::GetValue (ULONG_T &value)
{
  //## begin cVarRef::GetValue%1072120976.body preserve=yes
   LONG_T temp_val = 0;
   GetValue(temp_val);
   value = (ULONG_T)temp_val;
  //## end cVarRef::GetValue%1072120976.body
}

void cVarRef::GetValue (FLOAT_T &value)
{
  //## begin cVarRef::GetValue%1072120977.body preserve=yes
   DOUBLE_T temp_val = 0;
   GetValue(temp_val);
   value = (FLOAT_T)temp_val;
  //## end cVarRef::GetValue%1072120977.body
}

void cVarRef::GetValue (DOUBLE_T &value)
{
  //## begin cVarRef::GetValue%1040202786.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Get(value, i1, i2, i3, i4);
  //## end cVarRef::GetValue%1040202786.body
}

void cVarRef::GetValue (STRING_T &value)
{
  //## begin cVarRef::GetValue%1040202784.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Get(value, i1, i2, i3, i4);
  //## end cVarRef::GetValue%1040202784.body
}

void cVarRef::GetValue (WSTRING_T &value)
{
  //## begin cVarRef::GetValue%1088693724.body preserve=yes
  //## end cVarRef::GetValue%1088693724.body
}

void cVarRef::GetValue (BUF_T &buf_ptr)
{
  //## begin cVarRef::GetValue%1073740507.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Get(buf_ptr, i1, i2, i3, i4);
  //## end cVarRef::GetValue%1073740507.body
}

void cVarRef::GetValue (BUF_T buf, ULONG_T len, ULONG_T buf_size)
{
  //## begin cVarRef::GetValue%1072120984.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Get(buf, len, buf_size, i1, i2, i3, i4);
  //## end cVarRef::GetValue%1072120984.body
}

void cVarRef::SetValue (CHAR_T value)
{
  //## begin cVarRef::SetValue%1072120978.body preserve=yes
   SetValue((LONG_T)value);
  //## end cVarRef::SetValue%1072120978.body
}

void cVarRef::SetValue (UCHAR_T value)
{
  //## begin cVarRef::SetValue%1072120979.body preserve=yes
   SetValue((LONG_T)value);
  //## end cVarRef::SetValue%1072120979.body
}

void cVarRef::SetValue (SHORT_T value)
{
  //## begin cVarRef::SetValue%1072120980.body preserve=yes
   SetValue((LONG_T)value);
  //## end cVarRef::SetValue%1072120980.body
}

void cVarRef::SetValue (USHORT_T value)
{
  //## begin cVarRef::SetValue%1072120981.body preserve=yes
   SetValue((LONG_T)value);
  //## end cVarRef::SetValue%1072120981.body
}

void cVarRef::SetValue (LONG_T value)
{
  //## begin cVarRef::SetValue%1040202788.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Set(value, i1, i2, i3, i4);
  //## end cVarRef::SetValue%1040202788.body
}

void cVarRef::SetValue (ULONG_T value)
{
  //## begin cVarRef::SetValue%1072120982.body preserve=yes
   SetValue((LONG_T)value);
  //## end cVarRef::SetValue%1072120982.body
}

void cVarRef::SetValue (FLOAT_T value)
{
  //## begin cVarRef::SetValue%1072120983.body preserve=yes
   SetValue((DOUBLE_T)value);
  //## end cVarRef::SetValue%1072120983.body
}

void cVarRef::SetValue (DOUBLE_T value)
{
  //## begin cVarRef::SetValue%1040202789.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Set(value, i1, i2, i3, i4);
  //## end cVarRef::SetValue%1040202789.body
}

void cVarRef::SetValue (CONST_STRING_T value)
{
  //## begin cVarRef::SetValue%1040202787.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Set(value, i1, i2, i3, i4);
  //## end cVarRef::SetValue%1040202787.body
}

void cVarRef::SetValue (CONST_WSTRING_T value)
{
  //## begin cVarRef::SetValue%1088693725.body preserve=yes
  //## end cVarRef::SetValue%1088693725.body
}

void cVarRef::SetValue (BUF_T buf, ULONG_T len)
{
  //## begin cVarRef::SetValue%1073929899.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Set(buf, len, i1, i2, i3, i4);
  //## end cVarRef::SetValue%1073929899.body
}

void cVarRef::SetValue (BUF_T &buf)
{
  //## begin cVarRef::SetValue%1088693726.body preserve=yes
  //## end cVarRef::SetValue%1088693726.body
}

#undef DOCUMENT_CONTROL_LISTS
#ifdef DOCUMENT_CONTROL_LISTS

#define NEW_VALUE       1
#define ADD_CONTROL     2
#define REMOVE_CONTROL  3

inline const char * fName(int function)
{
   switch (function) {
   case NEW_VALUE: return "::NewValue";
   case ADD_CONTROL: return "::AddControl";
   case REMOVE_CONTROL: return "::RemoveControl";
   }
   return "?";

}
inline void printControlList(cVarRef * varRef, cPtrList * controlList, int function, const STRING_T & spec, const STRING_T & value, void * control)
{
   if (spec != "SetCfgCorDescription_Wiz[0]") {
      return;
   }
   FILE * stream = fopen("Log/controllist.txt", "a");
   if (stream != NULL) {
      int size = controlList->Size();
      fprintf(stream, "\n%p: %s%s %d controls %p\n", varRef, spec.c_str(), fName(function), size, control);
      cPtrList::cConstIterator i = controlList->Begin();
      int index = 0;
      if (i.First()) {
         do {
            cDataControl * control = (cDataControl*)i.Ptr();
            if (control != NULL) {
               fprintf(stream, "%d: %p: %p-%s\n", index, control, control->Widget(), control->Name().c_str());
            }
            index++;
         } while (i.Next());
      }
      fclose(stream);
   }
}

#else

#define NEW_VALUE       1
#define ADD_CONTROL     2
#define REMOVE_CONTROL  3

inline void printControlList(cVarRef * varRef, cPtrList * controlList, int function, const STRING_T & spec, const STRING_T & value, void * control)
{
}

#endif

void cVarRef::NewValue (CONST_STRING_T value, ULONG_T time_offset, ULONG_T value_size, ULONG_T data_set)
{
   //## begin cVarRef::NewValue%1041261882.body preserve=yes
   printControlList(this, _ControlList, NEW_VALUE, _Spec, value, NULL);
   if (IsBackgroundSensitive()) {
      data_set |= BACKGROUND_SENSITIVE;
   }
#ifdef SUPPORT_MULTIPLE_CONTROLS
   cPtrList::cConstIterator i = _ControlList->Begin();
   if (i.First()) {
      do {
         cDataControl * control = (cDataControl*)i.Ptr();
         if (control != NULL) {
            control->NewValue(value, time_offset, DataType(), value_size, data_set);
         }
      } while (i.Next());
   }
#else
   if (_Control != NULL) {
      _Control->NewValue(value, time_offset, DataType(), value_size, data_set);
   }
#endif
  //## end cVarRef::NewValue%1041261882.body
}

void cVarRef::NewValue (BUF_T buf, ULONG_T time_offset, ULONG_T value_size, ULONG_T data_set)
{
  //## begin cVarRef::NewValue%1073907455.body preserve=yes
#ifdef SUPPORT_MULTIPLE_CONTROLS
   if (IsBackgroundSensitive()) {
      data_set |= BACKGROUND_SENSITIVE;
   }
   cPtrList::cConstIterator i = _ControlList->Begin();
   if (i.First()) {
      do {
         cDataControl * control = (cDataControl*)i.Ptr();
         if (control != NULL) {
            control->NewValue(buf, time_offset, DataType(), value_size, data_set);
         }
      } while (i.Next());
   }
#else
   if (_Control != NULL) {
      _Control->NewValue(buf, time_offset, DataType(), value_size, data_set);
   }
#endif
  //## end cVarRef::NewValue%1073907455.body
}

void cVarRef::NewValue (ULONG_T dataset)
{
  //## begin cVarRef::NewValue%1140790764.body preserve=yes
   BUF_T buf = NULL;
   STRING_T value;
   UCHAR_T data_type = DataType();
   ULONG_T size = ValueSize();
   if (DataType() == SH_BYTE ||
       DataType() == SH_OBJECT) {
      GetValue(buf);
      NewValue(buf, 0, size, dataset);
   } else {
      GetValue(value);
      NewValue(value.c_str(), 0, size, dataset);
   }
  //## end cVarRef::NewValue%1140790764.body
}

void cVarRef::SetIndex (ULONG_T pos, cArgument *index)
{
  //## begin cVarRef::SetIndex%1040202776.body preserve=yes
   if (pos >= _IndexVec.size()) _IndexVec.resize(pos+1);
   _IndexVec[pos] = index;
  //## end cVarRef::SetIndex%1040202776.body
}

STRING_T cVarRef::VarName ()
{
  //## begin cVarRef::VarName%1135947274.body preserve=yes
   return _VarDef->_VarName;
  //## end cVarRef::VarName%1135947274.body
}

void cVarRef::GetIndices (LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4)
{
  //## begin cVarRef::GetIndices%1041261885.body preserve=yes
   i1 = i2 = i3 = i4 = -1;
   int dims = _IndexVec.size();
   if (dims > 0) _IndexVec[0]->GetValue(i1);
   if (dims > 1) _IndexVec[1]->GetValue(i2);
   if (dims > 2) _IndexVec[2]->GetValue(i3);
   if (dims > 3) _IndexVec[3]->GetValue(i4);
  //## end cVarRef::GetIndices%1041261885.body
}

ULONG_T cVarRef::Indices ()
{
  //## begin cVarRef::Indices%1040202777.body preserve=yes
   return _IndexVec.size();
  //## end cVarRef::Indices%1040202777.body
}

void cVarRef::Register (cDataChangeAdapter *adapter)
{
  //## begin cVarRef::Register%1042646893.body preserve=yes
#ifndef BASE_LIBRARY
   adapter->RegisterVar(this);
#endif
   //## end cVarRef::Register%1042646893.body
}

void cVarRef::UnRegister (cDataChangeAdapter *adapter)
{
  //## begin cVarRef::UnRegister%1042646894.body preserve=yes
#ifndef BASE_LIBRARY
   adapter->UnRegisterVar(this);
#endif
   //## end cVarRef::UnRegister%1042646894.body
}

BOOL_T cVarRef::Matches (cDataChange *change)
{
  //## begin cVarRef::Matches%1042646895.body preserve=yes
#ifndef BASE_LIBRARY
   LONG_T id1 = _VarId, id2 = change->get_VarId();
   if (id1 != -1 && id2 != -1) {
      if (id1 != id2) return false;
   } else {
      const char * name1 = _Name.c_str();
      STRING_T name2 = change->get_VarName();
      const char * _name2 = name2.c_str();
      if (strcmp(name1, _name2) != 0) return false;
   }
   ULONG_T dims = _IndexVec.size();
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   GetIndices(i1, i2, i3, i4);
   if (i1 != change->get_Index1()) return false;
   if (i2 != change->get_Index2()) return false;
   if (i3 != change->get_Index3()) return false;
   if (i4 != change->get_Index4()) return false;
#endif
   return true;
  //## end cVarRef::Matches%1042646895.body
}

void cVarRef::AddControl (cDataControl *control)
{
  //## begin cVarRef::AddControl%1043311227.body preserve=yes
#ifndef BASE_LIBRARY
#ifdef SUPPORT_MULTIPLE_CONTROLS
   if (control != NULL && _ControlList != NULL) {
      _ControlList->Add((void*)control);
      printControlList(this, _ControlList, ADD_CONTROL, _Spec, "", control);
   }
#else
   _Control = control;
#endif
#endif
   //## end cVarRef::AddControl%1043311227.body
}

void cVarRef::RemoveControl (cDataControl *control)
{
  //## begin cVarRef::RemoveControl%1109600057.body preserve=yes
#ifndef BASE_LIBRARY
#ifdef SUPPORT_MULTIPLE_CONTROLS
   if (control != NULL) {
#define COMPLETE_CONTROL_REMOVAL
#ifdef COMPLETE_CONTROL_REMOVAL
      std::list<cDataControl*> remove_list;
      void * widget = control->Widget();
      cPtrList::cConstIterator i = _ControlList->Begin();
      if (i.First()) {
         do {
            cDataControl * control2 = (cDataControl*)i.Ptr();
            if (control2 != NULL) {
               void * widget2 = control2->Widget();
               if (widget2 == widget) {
                  remove_list.push_back(control2);
               }
            }
         } while (i.Next());
      }
      std::list<cDataControl*>::const_iterator c = remove_list.cbegin();
      while (c != remove_list.cend()) {
         cDataControl * control3 = (*c);
         _ControlList->Remove((void*)control3);
         c++;
      }
#endif
      _ControlList->Remove((void*)control);
      printControlList(this, _ControlList, REMOVE_CONTROL, _Spec, "", control);
   }
#else
   _Control = NULL;
#endif
#endif
   //## end cVarRef::RemoveControl%1109600057.body
}

void cVarRef::GetMinimum (LONG_T &minimum)
{
  //## begin cVarRef::GetMinimum%1089103295.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMinimum(minimum, i1, i2, i3, i4);
  //## end cVarRef::GetMinimum%1089103295.body
}

void cVarRef::GetMinimum (ULONG_T &minimum)
{
  //## begin cVarRef::GetMinimum%1089103296.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMinimum(minimum, i1, i2, i3, i4);
  //## end cVarRef::GetMinimum%1089103296.body
}

void cVarRef::GetMinimum (FLOAT_T &minimum)
{
  //## begin cVarRef::GetMinimum%1089103297.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMinimum(minimum, i1, i2, i3, i4);
  //## end cVarRef::GetMinimum%1089103297.body
}

void cVarRef::GetMinimum (DOUBLE_T &minimum)
{
  //## begin cVarRef::GetMinimum%1089103298.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMinimum(minimum, i1, i2, i3, i4);
  //## end cVarRef::GetMinimum%1089103298.body
}

void cVarRef::GetMinimum (STRING_T &minimum)
{
  //## begin cVarRef::GetMinimum%1089203188.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMinimum(minimum, i1, i2, i3, i4);
  //## end cVarRef::GetMinimum%1089203188.body
}

void cVarRef::GetMaximum (LONG_T &maximum)
{
  //## begin cVarRef::GetMaximum%1089103299.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMaximum(maximum, i1, i2, i3, i4);
  //## end cVarRef::GetMaximum%1089103299.body
}

void cVarRef::GetMaximum (ULONG_T &maximum)
{
  //## begin cVarRef::GetMaximum%1089103300.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMaximum(maximum, i1, i2, i3, i4);
  //## end cVarRef::GetMaximum%1089103300.body
}

void cVarRef::GetMaximum (FLOAT_T &maximum)
{
  //## begin cVarRef::GetMaximum%1089103301.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMaximum(maximum, i1, i2, i3, i4);
  //## end cVarRef::GetMaximum%1089103301.body
}

void cVarRef::GetMaximum (DOUBLE_T &maximum)
{
  //## begin cVarRef::GetMaximum%1089103302.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMaximum(maximum, i1, i2, i3, i4);
  //## end cVarRef::GetMaximum%1089103302.body
}

void cVarRef::GetMaximum (STRING_T &maximum)
{
  //## begin cVarRef::GetMaximum%1089203189.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetMaximum(maximum, i1, i2, i3, i4);
  //## end cVarRef::GetMaximum%1089203189.body
}

void cVarRef::Refresh ()
{
  //## begin cVarRef::Refresh%1098867705.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->Refresh(i1, i2, i3, i4);
  //## end cVarRef::Refresh%1098867705.body
}

BOOL_T cVarRef::IsBackgroundSensitive ()
{
  //## begin cVarRef::IsBackgroundSensitive%1138360004.body preserve=yes
   CHECK_VARIABLE()
   return _Variable->IsBackgroundSensitive();
  //## end cVarRef::IsBackgroundSensitive%1138360004.body
}

ULONG_T cVarRef::GetObject (cBinaryObject &object)
{
  //## begin cVarRef::GetObject%1238436636.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->GetObject(object, i1, i2, i3, i4);
   return object.Size();
  //## end cVarRef::GetObject%1238436636.body
}

void cVarRef::SetObject (const cBinaryObject &object)
{
  //## begin cVarRef::SetObject%1238436637.body preserve=yes
   CHECK_VARIABLE()
   LONG_T i1, i2, i3, i4;
   GetIndices(i1, i2, i3, i4);
   _Variable->SetObject(object, i1, i2, i3, i4);
  //## end cVarRef::SetObject%1238436637.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cVarRef::get_Cached () const
{
  //## begin cVarRef::get_Cached%4215C68B001F.get preserve=no
  return _Cached;
  //## end cVarRef::get_Cached%4215C68B001F.get
}

void cVarRef::set_Cached (BOOL_T value)
{
  //## begin cVarRef::set_Cached%4215C68B001F.set preserve=no
  _Cached = value;
  //## end cVarRef::set_Cached%4215C68B001F.set
}

ULONG_T cVarRef::get_Flags () const
{
  //## begin cVarRef::get_Flags%43FDF5BB009D.get preserve=no
  return _Flags;
  //## end cVarRef::get_Flags%43FDF5BB009D.get
}

void cVarRef::set_Flags (ULONG_T value)
{
  //## begin cVarRef::set_Flags%43FDF5BB009D.set preserve=no
  _Flags = value;
  //## end cVarRef::set_Flags%43FDF5BB009D.set
}

// Additional Declarations
  //## begin cVarRef%3C7E422F03C0.declarations preserve=yes
  //## end cVarRef%3C7E422F03C0.declarations

//## begin module%3C7E422F03C0.epilog preserve=yes
//## end module%3C7E422F03C0.epilog
