//## begin module%3C6A7BFD0121.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C6A7BFD0121.cm

//## begin module%3C6A7BFD0121.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C6A7BFD0121.cp

//## Module: cVariable%3C6A7BFD0121; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVariable.cpp

//## begin module%3C6A7BFD0121.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C6A7BFD0121.additionalIncludes

//## begin module%3C6A7BFD0121.includes preserve=yes

/// HA 18.04.05 - method copy: creation of unit_def changed from _VarDef
///               to dst_variable->_VarDef
/// PR 07.12.06 - removed setting of input state o 0 (native) in ::Copy
///               substituted this functionality by suppliying flag VF_DATASET_REPRESENTATION
///               to set operation
/// PR 05.07.07 - added methods used for input state sensitive handling of datasets
///               ::CopyUnitSensitive
///               added static class reference _VariableControl (cVariableControl)
///               to enable application specific control of variable functionality
/// PR 06.07.07 - extended method UniText with argument CHAR_T state to retrieve the unit text
///               of a specific input state (state >= 0) or the current state of the value (state == -1)
///             - counting and checking unit sensitive values in ::CopyUnitSensitive
/// PR 12.10.07 - Exporting system flags through method ::SystemFlags()

//## end module%3C6A7BFD0121.includes

// cDataChange
#include "System/Objects/cDataChange.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cPersistenceChannel
#include "Control/LocalDatabase/cPersistenceChannel.h"
//## begin module%3C6A7BFD0121.additionalDeclarations preserve=yes
#include "Control/LocalDatabase/cLocalVariable.h"
//## end module%3C6A7BFD0121.additionalDeclarations


// Class cVariable 



//## begin cVariable::VariableControl%470A5FBB01BE.attr preserve=no  protected: static cVariableControl * {U} NULL
cVariableControl *cVariable::_VariableControl = NULL;
//## end cVariable::VariableControl%470A5FBB01BE.attr





cVariable::cVariable()
  //## begin cVariable::cVariable%.hasinit preserve=no
      : _VarId(-1), _Flags(0), _VarDef(NULL), _PersistenceChannel(NULL)
  //## end cVariable::cVariable%.hasinit
  //## begin cVariable::cVariable%.initialization preserve=yes
  //## end cVariable::cVariable%.initialization
{
  //## begin cVariable::cVariable%.body preserve=yes
_ASSERT_UNCOND
  //## end cVariable::cVariable%.body
}

cVariable::cVariable(const cVariable &right)
  //## begin cVariable::cVariable%copy.hasinit preserve=no
      : _VarId(-1), _Flags(0), _VarDef(NULL), _PersistenceChannel(NULL)
  //## end cVariable::cVariable%copy.hasinit
  //## begin cVariable::cVariable%copy.initialization preserve=yes
  //## end cVariable::cVariable%copy.initialization
{
  //## begin cVariable::cVariable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVariable::cVariable%copy.body
}

cVariable::cVariable (cVarDef *var_def)
  //## begin cVariable::cVariable%1015079155.hasinit preserve=no
      : _VarId(-1), _Flags(0), _VarDef(NULL), _PersistenceChannel(NULL)
  //## end cVariable::cVariable%1015079155.hasinit
  //## begin cVariable::cVariable%1015079155.initialization preserve=yes
  //## end cVariable::cVariable%1015079155.initialization
{
  //## begin cVariable::cVariable%1015079155.body preserve=yes
_ASSERT_COND(var_def != NULL)
   _VarDef = var_def;
  //## end cVariable::cVariable%1015079155.body
}


cVariable::~cVariable()
{
  //## begin cVariable::~cVariable%.body preserve=yes
  //## end cVariable::~cVariable%.body
}



//## Other Operations (implementation)
STRING_T cVariable::VarName ()
{
  //## begin cVariable::VarName%1077542661.body preserve=yes
   return _VarDef->_VarName;
  //## end cVariable::VarName%1077542661.body
}

UCHAR_T cVariable::DataType ()
{
  //## begin cVariable::DataType%1077542654.body preserve=yes
   return _VarDef->_DataType;
  //## end cVariable::DataType%1077542654.body
}

UCHAR_T cVariable::VarType ()
{
  //## begin cVariable::VarType%1077542656.body preserve=yes
   return _VarDef->_VarType;
  //## end cVariable::VarType%1077542656.body
}

UCHAR_T cVariable::PersistenceType ()
{
  //## begin cVariable::PersistenceType%1077542655.body preserve=yes
   return _VarDef->_PersistenceType;
  //## end cVariable::PersistenceType%1077542655.body
}

UCHAR_T cVariable::Precision ()
{
  //## begin cVariable::Precision%1087412991.body preserve=yes
   return _VarDef->_Precision;
  //## end cVariable::Precision%1087412991.body
}

STRING_T cVariable::FileName ()
{
  //## begin cVariable::FileName%1077542657.body preserve=yes
   return _VarDef->_FileName;
  //## end cVariable::FileName%1077542657.body
}

ULONG_T cVariable::Dims ()
{
  //## begin cVariable::Dims%1077542660.body preserve=yes
   return _VarDef->Dims();
  //## end cVariable::Dims%1077542660.body
}

ULONG_T cVariable::DimSize (ULONG_T dim)
{
  //## begin cVariable::DimSize%1077539621.body preserve=yes
   return _VarDef->DimSize(dim);
  //## end cVariable::DimSize%1077539621.body
}

ULONG_T cVariable::ValueSize ()
{
  //## begin cVariable::ValueSize%1077542658.body preserve=yes
   return _VarDef->ElementSize();
  //## end cVariable::ValueSize%1077542658.body
}

ULONG_T cVariable::Elements ()
{
  //## begin cVariable::Elements%1077542659.body preserve=yes
   return _VarDef->Elements();
  //## end cVariable::Elements%1077542659.body
}

STRING_T cVariable::DeviceName ()
{
  //## begin cVariable::DeviceName%1079186865.body preserve=yes
   if (_VarDef != NULL) {
      return _VarDef->_DeviceName;
   } else {
      return "?";
   }
  //## end cVariable::DeviceName%1079186865.body
}

STRING_T cVariable::DatabaseName ()
{
  //## begin cVariable::DatabaseName%1092050721.body preserve=yes
   if (_VarDef != NULL) {
      return _VarDef->_DatabaseName;
   } else {
      return "?";
   }
  //## end cVariable::DatabaseName%1092050721.body
}

STRING_T cVariable::UnitText (CHAR_T state)
{
  //## begin cVariable::UnitText%1111426861.body preserve=yes
   return "?";
  //## end cVariable::UnitText%1111426861.body
}

void cVariable::Refresh (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cVariable::Refresh%1092218360.body preserve=yes
  //## end cVariable::Refresh%1092218360.body
}

void cVariable::Copy (cVariable *dst_variable, BOOL_T show_errors)
{
  //## begin cVariable::Copy%1091957521.body preserve=yes
   /* this is not used and error prone
      the intended functionality can be obtained by supplying
      the flag VF_DATASET_REPRESENTATION to the set operation
   UCHAR_T current_state = 0;
   cUnitDef * unit_def = dst_variable->_VarDef->get_UnitDef(); // HA180405
   //cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      current_state = unit_def->GetState();
      unit_def->SetState(0); // _CurrentState are set to 0
   }
   */
   STRING_T description = _VarDef->_Description;
   if (description.size() > 0) {
      if (CopyUnitSensitive(description.c_str(), (cLocalVariable*)dst_variable)) {
         return;
      }
   }
   ULONG_T elements = _VarDef->Elements(); 
   LONG_T i1=-1, i2=-1, i3=-1, i4=-1;
   for (ULONG_T i=0; i<elements; i++) {
      try {
         _VarDef->GetIndices(i, i1, i2, i3, i4);
         STRING_T value;
         Get(value, i1, i2, i3, i4);
         dst_variable->Set(value.c_str(), i1, i2, i3, i4, VF_FILE_INPUT | VF_DATASET_REPRESENTATION);
      } catch (cError & e) {
         if (e.get_ErrCode() != VARIABLE_NULL_MAPPING &&
             e.get_ErrCode() != -VARIABLE_NULL_MAPPING && show_errors) {
            ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: %s\n",
                        dst_variable->VarName().c_str(),
                        i1, i2, i3, i4, (const char *)e);
         }
      } catch (...) {
         ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: unhandled exception\n",
                     dst_variable->VarName().c_str(),
                     i1, i2, i3, i4);
      }
   }
   /* this is not used and error prone (see above)
   if (unit_def != NULL) {
      unit_def->SetState(current_state);
   }
   */
  //## end cVariable::Copy%1091957521.body
}

void cVariable::CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange)
{
  //## begin cVariable::CopyCommand%1100714613.body preserve=yes
  //## end cVariable::CopyCommand%1100714613.body
}

void cVariable::SetFlags (ULONG_T flags)
{
  //## begin cVariable::SetFlags%1102166610.body preserve=yes
   _Flags = flags;
  //## end cVariable::SetFlags%1102166610.body
}

ULONG_T cVariable::GetFlags ()
{
  //## begin cVariable::GetFlags%1102166611.body preserve=yes
   return _Flags;
  //## end cVariable::GetFlags%1102166611.body
}

BOOL_T cVariable::SetFlag (ULONG_T flag_pos, BOOL_T state)
{
  //## begin cVariable::SetFlag%1102166612.body preserve=yes
   if (flag_pos > 31) {
      return false;
   } else {
      ULONG_T flags = GetFlags();
      if (state) {
         flags |= (1 << flag_pos);
      } else {
         flags &= (~(1 << flag_pos));
      }
      SetFlags(flags);
      return true;
   }
  //## end cVariable::SetFlag%1102166612.body
}

BOOL_T cVariable::GetFlag (ULONG_T flag_pos)
{
  //## begin cVariable::GetFlag%1102166613.body preserve=yes
   if (flag_pos > 31) {
      return false;
   } else {
      ULONG_T flags = GetFlags();
      if (flags & (1 << flag_pos)) {
         return true;
      } else {
         return false;
      }
   }
  //## end cVariable::GetFlag%1102166613.body
}

BOOL_T cVariable::IsBackgroundSensitive ()
{
  //## begin cVariable::IsBackgroundSensitive%1138360003.body preserve=yes
   return true;
  //## end cVariable::IsBackgroundSensitive%1138360003.body
}

void cVariable::SetVariableControl (cVariableControl *variable_control)
{
  //## begin cVariable::SetVariableControl%1191857021.body preserve=yes
   _VariableControl = variable_control;
  //## end cVariable::SetVariableControl%1191857021.body
}

BOOL_T cVariable::CopyUnitSensitive (CONST_STRING_T spec, cLocalVariable *dst_variable)
{
  //## begin cVariable::CopyUnitSensitive%1191857022.body preserve=yes
   if (_VariableControl == NULL ||
       _VarDef == NULL) {
      return false;
   }
   cContext * file_context = _VarDef->_Context;
   if (file_context == NULL) {
      return false;
   }
   cLocalContext * target_context = (cLocalContext*)dst_variable->_VarDef->_Context;
   if (target_context == NULL) {
      return false;
   }
   cUnitDef * unit_def = dst_variable->_VarDef->get_UnitDef();
   if (unit_def == NULL) {
      return false;
   }
   STRING_T unit_def_name = unit_def->_UnitName;
   STRING_T var_name = _VarDef->_VarName;

#define PROLOG_SIZE     0x20
   const char * values = spec;
   int i = 0;
   for (i=0; i<PROLOG_SIZE; i++) {
      if (strncmp(values, "values={", 8) == 0) {
         values += 8;
         break;
      }
      values++;
   }
   if (i < PROLOG_SIZE) {
      int pos = 0;
      char unit_text[0x60] = {0};
      DOUBLE_T value = 0;
      DOUBLE_T v = 0;
      ULONG_T specified_unit_code = 0;
      ULONG_T value_count = 0;
      int nread = 0;
      int params = sscanf(values, "%[^(](%d,%lf%n)", unit_text, &specified_unit_code, &value, &nread);
      while (params == 3) {
         value_count++;
         LONG_T i1=-1, i2=-1, i3=-1, i4=-1;
         _VarDef->GetIndices(pos, i1, i2, i3, i4);
         if (_VariableControl->TargetParameterChange(file_context, target_context, unit_def_name.c_str(),
                                                     var_name.c_str(), i1, i2, i3, i4)) {
            /// unit conversion target parameters have changed
            /// so convert from the parameter independent representation
            /// (even if there are precision problems)
            try {
               STRING_T svalue;
               Get(svalue, i1, i2, i3, i4);
               dst_variable->Set(svalue.c_str(), i1, i2, i3, i4, VF_FILE_INPUT | VF_DATASET_REPRESENTATION);
            } catch (cError & e) {
               if (e.get_ErrCode() != VARIABLE_NULL_MAPPING &&
                   e.get_ErrCode() != -VARIABLE_NULL_MAPPING) {
                  ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: %s\n",
                              dst_variable->VarName().c_str(),
                              i1, i2, i3, i4, (const char *)e);
               }
            } catch (...) {
               ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: unhandled exception\n",
                           dst_variable->VarName().c_str(),
                           i1, i2, i3, i4);
            }
         } else {
            /// unit conversion target parameters remain the same
            /// so set the unit stamped values and avoid precision problems
            try {
               UCHAR_T unit_code = (UCHAR_T)specified_unit_code;
               dst_variable->SetUnitSensitive(value, i1, i2, i3, i4, VF_FILE_INPUT, (UCHAR_T)unit_code, true);
            } catch (cError & e) {
               if (e.get_ErrCode() != VARIABLE_NULL_MAPPING &&
                   e.get_ErrCode() != -VARIABLE_NULL_MAPPING) {
                  ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: %s\n",
                              dst_variable->VarName().c_str(),
                              i1, i2, i3, i4, (const char *)e);
               }
            } catch (...) {
               ErrorPrintf("variable %s[%d][%d][%d][%d] not wrt set: unhandled exception\n",
                           dst_variable->VarName().c_str(),
                           i1, i2, i3, i4);
            }
         }
         values += nread + 2;
         params = sscanf(values, "%[^(](%d,%lf%n)", unit_text, &specified_unit_code, &value, &nread);
         pos++;
      }
      ULONG_T elements = _VarDef->Elements();
      if (value_count != elements) {
         int dummy = 0;
      }
      return true;
   }
   return false;
  //## end cVariable::CopyUnitSensitive%1191857022.body
}

void cVariable::ResetShadowBuffer ()
{
  //## begin cVariable::ResetShadowBuffer%1191857023.body preserve=yes

  //## end cVariable::ResetShadowBuffer%1191857023.body
}

//## Get and Set Operations for Class Attributes (implementation)

LONG_T cVariable::get_VarId () const
{
  //## begin cVariable::get_VarId%3D085CD7007A.get preserve=no
  return _VarId;
  //## end cVariable::get_VarId%3D085CD7007A.get
}

void cVariable::set_VarId (LONG_T value)
{
  //## begin cVariable::set_VarId%3D085CD7007A.set preserve=no
  _VarId = value;
  //## end cVariable::set_VarId%3D085CD7007A.set
}

// Additional Declarations
  //## begin cVariable%3C6A7BFD0121.declarations preserve=yes
  //## end cVariable%3C6A7BFD0121.declarations

//## begin module%3C6A7BFD0121.epilog preserve=yes
//## end module%3C6A7BFD0121.epilog
