//## begin module%3E0038B30046.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0038B30046.cm

//## begin module%3E0038B30046.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0038B30046.cp

//## Module: cLocalVariable%3E0038B30046; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cLocalVariable.cpp

//## begin module%3E0038B30046.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0038B30046.additionalIncludes

//## begin module%3E0038B30046.includes preserve=yes

/// PR 02.03.05 - introduced mapping between float/double and integer types
///               this property can be switched using constant
///               ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
///               introduced alternate units
///               this property can be switched using constant
///               ENABLE_UNITS
/// PR 07.03.05 - added cast functionality for float and double type mapping
/// PR 15.04.05 - added trimming of string based unit texts in method UnitText
/// PR 09.05.05 - considered input state values when copying or exchangig fore-/background
/// PR 10.05.05 - removed bug in exchanging input state values
/// PR 12.05.05 - extended unit switch functionality for name based device mappings
/// PR 18.05.05 - avoid to read previous value when checking write access, check variable type only
///               SetValue on binary data types
/// PR 23.05.05 - added parameter flags to device Set- and Get-Operations
/// PR 17.06.05 - dont get previous valus when setting act and volatile variables
/// PR 07.07.05 - changed unit handling when calling filter functions
///             - forcing data change event and setting input state when unit definitions
///               are used when setting a variable value
/// PR 11.07.05 - implemented Set method for float values directly due to precisiion problems
///               added new FormatIn method for float values (as a consequence of
///               the first modification)
/// PR 19.07.05 - introduced variable mutex for test purposes
/// PR 25.07.05 - added missing unit handling in Load method
///             - raising bufchanged events only in set methods to avoid infinite loops
///               in case of client access
/// PR 03.08.05 - avoid to load unmapped data items in Load method
/// PR 08.08.05 - call BufChanged in case of SH_BYTE and SH_OBJECT datatypes,
///               when DataChanged is called
/// PR 15.08.05 - eliminated setting of _VarDef->_Precision in HandleUnit - methods
/// PR 17.08.05 - removed negative consequences of change from 15.08
/// PR 23.08.05 - added missing LoadVariable calls when copying variables
/// PR 09.09.05 - integrated unit conversion for name based float mappings from FM
///               added conversion for double values
/// PR 12.09.05 - restricted LoadVariable calls to active datasets in method CopyCommand
/// PR 19.09.05 - calling BufChanged instead of Get when refreshing binary variables
///               otherwise ring buffer refresh will not work
/// PR 04.10.05 - controlling beuufer serialization through flag VF_MEMORY_ACCESS
///             - new DataChange method usable by filter functions to avoid
///               indefinite recursions when filter function values are changing fast
///               this method is used by string type filter functions only
///               until general correctness of functionality is verified
/// PR 31.10.05 - handling unit specific flags in ::Set methods
/// PR 03.11.05 - sending data change events in general in case of variables
///               with unit definitions (even when the value not changed)
/// PR 15.11.05 - Integrated rounding fixes from Afton (Rob Montag (RM rounding fix))
///             - Integrated refresh fix from Malterdingen (Horst Anselm (HA refresh fix))
/// PR 28.11.05 - introduced host access interface
///             - supplied parameter flags to filter and conversion methods
/// PR 09.12.05 - Changes to method ::Get(BUF_T &, ..)
///               BufChanged events are generated only, when variable is mapped
///               to a device and when VF_BUFFERED is not set
/// PR 07.01.06 - introduced variable type virtual (such a variable has no resources like memory)
///               values are supplied by computing values either via filter or access functions
///               or devices.
/// PR 09.01.06 - changes for virtual variables
/// PR 23.01.06 - retrieving the persistence channel reference only when its really used
/// PR 13.02.06 - added function Round(..) to correctly round integral device representations
///               of float and double values
/// PR 14.03.06 - removed bug in handling of unit specific presentation flags
///               now also device mapped variables handle the flags correctly
///               and can be used to retrieve presentation dependent values
/// PR 15.03.06 - temporarily all sent datachanges switch to user interface
///               unit representations when a host interface causes a data change
/// PR 22.05.06 - identical acquisition of precision value through all
///               FormatIn and FormatOut methods
/// PR 03.07.06 - fixed bug with invalid buffers in cLocalVariable::Save
/// PR 20.07.06 - extended temporary buffer in Compare(...) and made it static
///               buf was to short for comparison, this must be solved dynamic
///               in future
/// PR 15.08.06 - substituted breaks with returns in
///        ::GetDevice (cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, ULONG_T size, ULONG_T flags)
/// PR 07.12.06 - setting of input states is now done using
///               new method SetInput(pos,flags) rather than SetInputState
///               this new method respects presentation specific flag values
/// PR 23.02.07 - corrected handling of signed integral values in name based ::GetDevice
///               different handling of short and long compared to unsigned short
///               and unsigned long (identical to the handling in address based ::GetDevice)
/// PR 26.04.07 - avoid to call filter function when VF_BUFFERED set in flags
/// PR 04.05.07 - added reading from device for set variables, when flag VF_DEVICE is supplied
///               (not activated define ALLOW_SET_FROM_DEVICE) 
///             - added synchronisation of device parameters persistent values and configuration values
///               now can coexist. in case of general (bbram) init, the configuration values are stored
///               but the values can be altered subsequently
///               (active define SYNC_DEVICE_PARAMETERS)
/// PR 05.07.07 - added methods used for input state sensitive handling of datasets
///               ::Set(DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, UCHAR_T input_state)
///               this setter method is only defined in the class cLocalVariable to overcome
///               the precision problems of switchable units in datasets
///               ::SetUnitCode(ULONG_T pos, CHAR_T value);
///               ::UnitCode(ULONG_T pos)
///               same motivation as above
///               added input state information (active unit when the value was set) to the data change notification events
/// PR 06.07.07 - extended reimplemented method UniText with argument CHAR_T state (see cVariable.cpp)
///             - checked and changed ::DataChange - methods respective persistence behaviour in 
///               foreground and background datasets
///             - changed unit specific Set - method
///             - implemented GetRaw - method for usage in ::DataChange and cVarDef::PrintUnitSensitiveValues
/// PR 09.07.07 - GetRaw should take fixed point decimal data types into account
///               for correct formats of these values
///               Implemented and called A further FormatOut - method where the expected
///               unit code can be supplied as parameter.
/// PR 13.07.07 - added method ::EmitChanges to emit changes caused by persistent variable values
/// PR 14.09.07 - extended virtual variable handling (no more dimension checks no more index chaecks)
/// PR 17.09.07 - extensions to virtual variables: implemented data change mechanisma
/// PR 24.09.07 - removed superfluous BufChanged call in SetMemoryType (hint from Horst Anselm FM)
/// PR 07.10.07 - full implementation of shadow dataset control for local variables
/// PR 12.10.07 - passed flags consequently to DataChanged and BufChanged methods
///             - data change events are merked with cause flag CH_FLAG_FILE_INPUT
/// PR 17.10.07 - no more truncation of values in ::GetRaw for SH_FLOAT and SH_DOUBLE
/// PR 22.10.07 - access function considered again for virtual variables
/// PR 29.10.07 - allocating resources for shadow datasets only if enabled
/// PR 31.10.07 - fixed bug in name based ::GetDevice (value was always 0)
/// PR 19.04.08 - changes in handling of precision 0 (FM Horst Anselm)
/// PR 21.07.08 - passing consequently flags parameter to Device::Read(..) calls (FM Horst Anselm)
/// PR 08.10.08 - checking for null pointers in cLocalVariable::Set
/// PR 14.07.10 - added protection to device->SetPattern(...) via _DeviceMutex
/// PR 21.10.11 - implemented new accu management functionality to avoid invalid values in race conditions
/// PR 27.10.11 - setting the accu correctly in ::Refresh for byte variables
///               PR refresh fix
/// HA 10.06.13 - handling SH_DOUBLE as well as SH_LOAT in ::HandleUnit(...)
/// PR 29.01.14 - added missing flags parameter in Get() of macro CHECK_WRITE_ACCESS
///               that prevented from using the correct dataset with flag VF_BACKGROUND
/// PR 31.07.14 - added method to synchronously persist variable data
///               in addition to the event based (cDataChange) mechanism
///               together with the new buffering mechanism in cFileStorage this possibility
///               enhances performance and control, when reading data sets
/// PR 08.12.15 - added parameter fixed_decimal_representation to methods
///               ::GetMinimum(LONG_T &, ...)
///               ::GetMinimum(ULONG_T &, ...)
///               ::GetMaximum(LONG_T &, ...)
///               and ::GetMaximum(ULONG_T &, ...)
///               fixed_decimal_representation = false supplies a "real" long value for the minimum,
///               no value in fixed decimal representation

//## end module%3E0038B30046.includes

// cIniFile
#include "System/cIniFile.h"
// cUserInfo
#include "System/Objects/cUserInfo.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cBlockBuffer
#include "System/Memory/cBlockBuffer.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cMapping
#include "System/Database/cMapping.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cArgument
#include "System/Database/cArgument.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cValueBuffer
#include "Control/LocalDatabase/cValueBuffer.h"
// cPersistenceChannel
#include "Control/LocalDatabase/cPersistenceChannel.h"
#include "Control/LocalDatabase/cPersistenceManager.h"
// cDevice
#include "Control/Device/cDevice.h"
#include "Control/Cell/cCell.h"

//## begin module%3E0038B30046.additionalDeclarations preserve=yes

#define MAX_PRECISION      10

#if defined(_DEBUG) 
#define BREAK(i1,i2,i3,i4) Break(i1,i2,i3,i4)
#else
#define BREAK(i1,i2,i3,i4)
#endif

#define ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
#define ENABLE_UNITS
#define STATEBUF_SIZE (_VarDef->Elements() * sizeof(CHAR_T))

#define DATASET_SELECTED (VF_FOREGROUND|VF_BACKGROUND|VF_SHADOW)
#ifdef BASE_LIBRARY
#define SELECT_DATASET(f)
#else
#define SELECT_DATASET(f) \
  cObjectLock __lock__(&_VariableMutex); \
  if (f & DATASET_SELECTED) { \
      if (f & VF_FOREGROUND) { \
         _Values = _DataSets[FOREGROUND_DATASET]; \
         _States = _InputStates[FOREGROUND_DATASET]; \
      } if (f & VF_BACKGROUND) { \
         if (_DataSets[BACKGROUND_DATASET] != NULL) { \
            _Values = _DataSets[BACKGROUND_DATASET]; \
            _States = _InputStates[BACKGROUND_DATASET]; \
         } \
      } if (f & VF_SHADOW) { \
         if (_DataSets[SHADOW_DATASET] != NULL) { \
            _Values = _DataSets[SHADOW_DATASET]; \
            _States = _InputStates[SHADOW_DATASET]; \
         } \
      } \
   } else { \
      cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData(); \
      if (user_info == NULL) { \
         _Values = _DataSets[FOREGROUND_DATASET]; \
         _States = _InputStates[FOREGROUND_DATASET]; \
      } else { \
         ULONG_T dataset = user_info->get_DataSet(); \
         if (dataset < MAX_DATASETS && _DataSets[dataset] != NULL) { \
            _Values = _DataSets[dataset]; \
            _States = _InputStates[dataset]; \
         } \
      } \
   }
#endif

#define IS_PERSISTENT(ptype) (ptype != UNDEFINED && ptype != SH_RAM)

static void CopyBuf(BUF_T dst_buf, ULONG_T dst_size, BUF_T src_buf, ULONG_T src_size)
{
   ULONG_T size = _MIN_(dst_size, src_size);
   memcpy(dst_buf, src_buf, size);
}

#define CHECK_WRITE_ACCESS(f) \
   if (_VarDef->_VarType == SH_VAR_ACT) { \
      throw cError(VARIABLE_READ_ONLY, 0, _VarDef->_VarName.c_str()); \
   } \
   if (_VarDef->_VarType == SH_VAR_SET) { \
      try { \
         _Initialized = true; \
         Get(_PreviousValue, i1, i2, i3, i4, f); \
      } catch (cError & e) { \
         ErrorPrintf("%s getting previous value of %s\n", (const char *)e, VarName().c_str()); \
      } catch (...) { \
         ErrorPrintf("unhandled exception getting previous value of %s\n", VarName().c_str()); \
      } \
   }

#define FLOAT_MIN    -99999.9
#define FLOAT_MAX     99999.9
#define DOUBLE_MIN   -9999999999.9
#define DOUBLE_MAX    9999999999.9

static void Min(LONG_T & value, UCHAR_T data_type)
{
   switch  (data_type) {
   case SH_CHAR:
      value = CHAR_MIN;
      break;
   case SH_UCHAR:
      value = 0;
      break;
   case SH_SHORT:
      value = SHRT_MIN;
      break;
   case SH_USHORT:
      value = 0;
      break;
   case SH_LONG:
      value = LONG_MIN;
      break;
   case SH_ULONG:
      value = 0;
      break;
   case SH_BIT_8:
      value = 0;
      break;
   case SH_BIT_16:
      value = 0;
      break;
   case SH_BIT_32:
      value = 0;
      break;
   case SH_FLOAT:
      value = (LONG_T)FLOAT_MIN;
      break;
   case SH_DOUBLE:
      value = (LONG_T)DOUBLE_MIN;
      break;
   default: value = 0;
   }
}

static void Min(ULONG_T & value, UCHAR_T data_type)
{
   switch  (data_type) {
   case SH_CHAR:
      value = CHAR_MIN;
      break;
   case SH_UCHAR:
      value = 0;
      break;
   case SH_SHORT:
      value = SHRT_MIN;
      break;
   case SH_USHORT:
      value = 0;
      break;
   case SH_LONG:
      value = LONG_MIN;
      break;
   case SH_ULONG:
      value = 0;
      break;
   case SH_BIT_8:
      value = 0;
      break;
   case SH_BIT_16:
      value = 0;
      break;
   case SH_BIT_32:
      value = 0;
      break;
   case SH_FLOAT:
      value = (ULONG_T)FLOAT_MIN;
      break;
   case SH_DOUBLE:
      value = (ULONG_T)DOUBLE_MIN;
      break;
   default: value = 0;
   }
}

static void Min(FLOAT_T & value, UCHAR_T data_type)
{
   switch  (data_type) {
   case SH_CHAR:
      value = CHAR_MIN;
      break;
   case SH_UCHAR:
      value = 0;
      break;
   case SH_SHORT:
      value = SHRT_MIN;
      break;
   case SH_USHORT:
      value = 0;
      break;
   case SH_LONG:
      value = LONG_MIN;
      break;
   case SH_ULONG:
      value = 0;
      break;
   case SH_BIT_8:
      value = 0;
      break;
   case SH_BIT_16:
      value = 0;
      break;
   case SH_BIT_32:
      value = 0;
      break;
   case SH_FLOAT:
      value = (FLOAT_T)FLOAT_MIN;
      break;
   case SH_DOUBLE:
      value = (FLOAT_T)DOUBLE_MIN;
      break;
   default: value = 0;
   }
}

static void Min(DOUBLE_T & value, UCHAR_T data_type)
{
   switch  (data_type) {
   case SH_CHAR:
      value = CHAR_MIN;
      break;
   case SH_UCHAR:
      value = 0;
      break;
   case SH_SHORT:
      value = SHRT_MIN;
      break;
   case SH_USHORT:
      value = 0;
      break;
   case SH_LONG:
      value = LONG_MIN;
      break;
   case SH_ULONG:
      value = 0;
      break;
   case SH_BIT_8:
      value = 0;
      break;
   case SH_BIT_16:
      value = 0;
      break;
   case SH_BIT_32:
      value = 0;
      break;
   case SH_FLOAT:
      value = FLOAT_MIN;
      break;
   case SH_DOUBLE:
      value = DOUBLE_MIN;
      break;
   default: value = 0;
   }
}

static void Max(LONG_T & value, UCHAR_T data_type)
{
   switch (data_type) {
   case SH_CHAR:
      value = CHAR_MAX;
      break;
   case SH_UCHAR:
      value = UCHAR_MAX;
      break;
   case SH_SHORT:
      value = SHRT_MAX;
      break;
   case SH_USHORT:
      value = USHRT_MAX;
      break;
   case SH_LONG:
      value = LONG_MAX;
      break;
   case SH_ULONG:
      value = ULONG_MAX;
      break;
   case SH_BIT_8:
      value = UCHAR_MAX;
      break;
   case SH_BIT_16:
      value = USHRT_MAX;
      break;
   case SH_BIT_32:
      value = ULONG_MAX;
      break;
   case SH_FLOAT:
      value = (LONG_T)FLOAT_MAX;
      break;
   case SH_DOUBLE:
      value = (LONG_T)DOUBLE_MAX;
      break;
   default: value = LONG_MAX;
   }
}

static void Max(ULONG_T & value, UCHAR_T data_type)
{
   switch (data_type) {
   case SH_CHAR:
      value = CHAR_MAX;
      break;
   case SH_UCHAR:
      value = UCHAR_MAX;
      break;
   case SH_SHORT:
      value = SHRT_MAX;
      break;
   case SH_USHORT:
      value = USHRT_MAX;
      break;
   case SH_LONG:
      value = LONG_MAX;
      break;
   case SH_ULONG:
      value = ULONG_MAX;
      break;
   case SH_BIT_8:
      value = UCHAR_MAX;
      break;
   case SH_BIT_16:
      value = USHRT_MAX;
      break;
   case SH_BIT_32:
      value = ULONG_MAX;
      break;
   case SH_FLOAT:
      value = (ULONG_T)FLOAT_MAX;
      break;
   case SH_DOUBLE:
      value = (ULONG_T)DOUBLE_MAX;
      break;
   default: value = ULONG_MAX;
   }
}

static void Max(FLOAT_T & value, UCHAR_T data_type)
{
   switch (data_type) {
   case SH_CHAR:
      value = CHAR_MAX;
      break;
   case SH_UCHAR:
      value = UCHAR_MAX;
      break;
   case SH_SHORT:
      value = SHRT_MAX;
      break;
   case SH_USHORT:
      value = USHRT_MAX;
      break;
   case SH_LONG:
      value = (FLOAT_T)LONG_MAX;
      break;
   case SH_ULONG:
      value = (FLOAT_T)ULONG_MAX;
      break;
   case SH_BIT_8:
      value = UCHAR_MAX;
      break;
   case SH_BIT_16:
      value = USHRT_MAX;
      break;
   case SH_BIT_32:
      value = (FLOAT_T)ULONG_MAX;
      break;
   case SH_FLOAT:
      value = (FLOAT_T)FLOAT_MAX;
      break;
   case SH_DOUBLE:
      value = (FLOAT_T)DOUBLE_MAX;
      break;
   default: value = (FLOAT_T)LONG_MAX;
   }
}

static void Max(DOUBLE_T & value, UCHAR_T data_type)
{
   switch (data_type) {
   case SH_CHAR:
      value = CHAR_MAX;
      break;
   case SH_UCHAR:
      value = UCHAR_MAX;
      break;
   case SH_SHORT:
      value = SHRT_MAX;
      break;
   case SH_USHORT:
      value = USHRT_MAX;
      break;
   case SH_LONG:
      value = LONG_MAX;
      break;
   case SH_ULONG:
      value = ULONG_MAX;
      break;
   case SH_BIT_8:
      value = UCHAR_MAX;
      break;
   case SH_BIT_16:
      value = USHRT_MAX;
      break;
   case SH_BIT_32:
      value = ULONG_MAX;
      break;
   case SH_FLOAT:
      value = FLOAT_MAX;
      break;
   case SH_DOUBLE:
      value = DOUBLE_MAX;
      break;
   default: value = LONG_MAX;
   }
}

#include <math.h>
static inline LONG_T Round(DOUBLE_T fval)
{
   DOUBLE_T remainder = fval - (LONG_T)fval;
   if (fval > 0) {
      if (remainder < 0.5) {
         fval = floor(fval);
      } else {
         fval = ceil(fval);
      }
   } else {
      if (remainder < -0.5) {
         fval = floor(fval);
      } else {
         fval = ceil(fval);
      }
   }
   return (LONG_T)fval;
}

// Macros for virtual variable Handling (get methods)
#define GET_VIRTUAL_LONG(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(value); \
      return; \
   }
#define GET_VIRTUAL_FLOAT(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(value); \
      return; \
   }
#define GET_VIRTUAL_DOUBLE(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(value); \
      return; \
   }
#define GET_VIRTUAL_STRING(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(value, _VarDef->_Precision); \
      return; \
   }
#define GET_VIRTUAL_WSTRING(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(value, _VarDef->_Precision); \
      return; \
   }
#define GET_VIRTUAL_BUF(buf) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(buf); \
      return; \
   }
#define GET_VIRTUAL_BYTE(buf,len) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      ReadFilter(i1, i2, i3, i4, flags); \
      Accu()->Get(buf); \
      return; \
   }


// Macros for virtual variable Handling (set methods)
#define SET_VIRTUAL_LONG(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set(value); \
      WriteFilter(i1, i2, i3, i4, flags); \
      STRING_T new_value; \
      Accu()->Get(new_value); \
      DataChanged("", new_value.c_str(), i1, i2, i3, i4, 0); \
      return; \
   }
#define SET_VIRTUAL_FLOAT(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set(value); \
      WriteFilter(i1, i2, i3, i4, flags); \
      STRING_T new_value; \
      Accu()->Get(new_value); \
      DataChanged("", new_value.c_str(), i1, i2, i3, i4, 0); \
      return; \
   }
#define SET_VIRTUAL_DOUBLE(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set(value); \
      WriteFilter(i1, i2, i3, i4, flags); \
      STRING_T new_value; \
      Accu()->Get(new_value); \
      DataChanged("", new_value.c_str(), i1, i2, i3, i4, 0); \
      return; \
   }
#define SET_VIRTUAL_STRING(value)\
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set(value); \
      WriteFilter(i1, i2, i3, i4, flags); \
      STRING_T new_value; \
      Accu()->Get(new_value, _VarDef->_Precision); \
      DataChanged("", new_value.c_str(), i1, i2, i3, i4, 0); \
      return; \
   }
#define SET_VIRTUAL_WSTRING(value) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set(value); \
      WriteFilter(i1, i2, i3, i4, flags); \
      STRING_T new_value; \
      Accu()->Get(new_value, _VarDef->_Precision); \
      DataChanged("", new_value.c_str(), i1, i2, i3, i4, 0); \
      return; \
   }
#define SET_VIRTUAL_BYTE(buf,len) \
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) { \
      Accu()->Set((BUF_T)buf); \
      WriteFilter(i1, i2, i3, i4, flags); \
      BufChanged((BUF_T)NULL, (BUF_T)buf, i1, i2, i3, i4, 0); \
      return; \
   }

//## end module%3E0038B30046.additionalDeclarations


// Class cLocalVariable 


















cLocalVariable::cLocalVariable()
  //## begin cLocalVariable::cLocalVariable%.hasinit preserve=no
      : _Initialized(false), _FilterFuncRef(NULL), _ConvFuncRef(NULL), _AccessFuncRef(NULL), _MinArg(NULL), _MaxArg(NULL), _States(NULL), _ShadowChanges(NULL), _Accu(NULL), _IniFile(NULL), _Context(NULL)
  //## end cLocalVariable::cLocalVariable%.hasinit
  //## begin cLocalVariable::cLocalVariable%.initialization preserve=yes
  //## end cLocalVariable::cLocalVariable%.initialization
{
  //## begin cLocalVariable::cLocalVariable%.body preserve=yes
_ASSERT_UNCOND
  //## end cLocalVariable::cLocalVariable%.body
}

cLocalVariable::cLocalVariable(const cLocalVariable &right)
  //## begin cLocalVariable::cLocalVariable%copy.hasinit preserve=no
      : _Initialized(false), _FilterFuncRef(NULL), _ConvFuncRef(NULL), _AccessFuncRef(NULL), _MinArg(NULL), _MaxArg(NULL), _States(NULL), _ShadowChanges(NULL), _Accu(NULL), _IniFile(NULL), _Context(NULL)
  //## end cLocalVariable::cLocalVariable%copy.hasinit
  //## begin cLocalVariable::cLocalVariable%copy.initialization preserve=yes
  //## end cLocalVariable::cLocalVariable%copy.initialization
{
  //## begin cLocalVariable::cLocalVariable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cLocalVariable::cLocalVariable%copy.body
}

cLocalVariable::cLocalVariable (cVarDef *var_def)
  //## begin cLocalVariable::cLocalVariable%1040202755.hasinit preserve=no
      : _Initialized(false), _FilterFuncRef(NULL), _ConvFuncRef(NULL), _AccessFuncRef(NULL), _MinArg(NULL), _MaxArg(NULL), _States(NULL), _ShadowChanges(NULL), _Accu(NULL), _IniFile(NULL), _Context(NULL)
  //## end cLocalVariable::cLocalVariable%1040202755.hasinit
  //## begin cLocalVariable::cLocalVariable%1040202755.initialization preserve=yes
  , cVariable(var_def)
  //## end cLocalVariable::cLocalVariable%1040202755.initialization
{
  //## begin cLocalVariable::cLocalVariable%1040202755.body preserve=yes
   BOOL_T shadow_data_set_enabled = cResources::FlagSet(PF_ENABLE_SHADOW_DATASET);
   _Flags = var_def->_Flags;
   // determine background
   if (var_def->_VarType == SH_VAR_SET) {
     var_def->_BackgroundVar = true;
   }
   _Context = _VarDef->_Context;
   for (int i=0; i<MAX_DATASETS; i++) {
      _DataSets[i] = NULL;
   }
   BOOL_T bg_var = var_def->_BackgroundVar;
   if (_VarDef->_VarType != SH_VAR_VIRTUAL) {
      for (int i=0; i<MAX_DATASETS; i++) {
         if (i == FOREGROUND_DATASET || bg_var) {
            if (i == SHADOW_DATASET) {
                if (shadow_data_set_enabled) {
                  _DataSets[i] = new cValueBuffer(var_def->_DataType, var_def->Elements(), var_def->ElementSize());
                }
            } else {
               _DataSets[i] = new cValueBuffer(var_def->_DataType, var_def->Elements(), var_def->ElementSize());
            }
         }
      }
   }
   _Values = _DataSets[FOREGROUND_DATASET];
   _Accu = new cSHVariant(var_def->_DataType);
   _FilterFuncRef = var_def->_Filter;
   _AccessFuncRef = var_def->_Access;
   _MinArg = var_def->_MinSpec;
   _MaxArg = var_def->_MaxSpec;
   cMapping * mapping = var_def->_Mapping;
   if (mapping != NULL) {
      _ConvFuncRef = mapping->_ConvFunc;
   }
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      if (bg_var) {
         for (int i=0; i<MAX_DATASETS; i++) {
            _InputStates[i] = (CHAR_T*)cSystemUtils::Alloc(STATEBUF_SIZE);
         }
      } else {
         for (int i=0; i<MAX_DATASETS; i++) {
            if (i == 0) {
               _InputStates[i] = (CHAR_T*)cSystemUtils::Alloc(STATEBUF_SIZE);
            } else {
               _InputStates[i] = NULL;
            }
         }
      }
      _States = _InputStates[FOREGROUND_DATASET];
   } else {
      for (int i=0; i<MAX_DATASETS; i++) {
         _InputStates[i] = NULL;
      }
   }
#endif
   if (shadow_data_set_enabled) {
      _ShadowChanges = (UCHAR_T*)cSystemUtils::Alloc(STATEBUF_SIZE);
   }
  //## end cLocalVariable::cLocalVariable%1040202755.body
}


cLocalVariable::~cLocalVariable()
{
  //## begin cLocalVariable::~cLocalVariable%.body preserve=yes
   DELETE_OBJECT(cSHVariant, Accu())
   int i = 0;
   for (i=0; i<MAX_DATASETS; i++) {
      DELETE_OBJECT(cValueBuffer, _DataSets[i])
   }
   for (i=0; i<MAX_DATASETS; i++) {
      if (_InputStates[i] != NULL) {
         cSystemUtils::Free(_InputStates[i]);
      }
   }
   if (_ShadowChanges != NULL) {
      cSystemUtils::Free(_ShadowChanges);
   }
  //## end cLocalVariable::~cLocalVariable%.body
}



//## Other Operations (implementation)
STRING_T cLocalVariable::UnitText (CHAR_T state)
{
  //## begin cLocalVariable::UnitText%1111426625.body preserve=yes
   STRING_T dimension = "?";
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      dimension = unit_def->UnitText(state);
      return dimension;
   } else {
#define TRIM_UNIT_TEXT
#ifdef TRIM_UNIT_TEXT
      dimension = cStringUtils::Trim(_VarDef->_UnitText.c_str(), '"');
#else
      dimension = _VarDef->_UnitText;
#endif
      return dimension;
   }
  //## end cLocalVariable::UnitText%1111426625.body
}

void cLocalVariable::Get (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244159.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (CHAR_T)lval;
  //## end cLocalVariable::Get%1071244159.body
}

void cLocalVariable::Get (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244160.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (UCHAR_T)lval;
  //## end cLocalVariable::Get%1071244160.body
}

void cLocalVariable::Get (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244161.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (SHORT_T)lval;
  //## end cLocalVariable::Get%1071244161.body
}

void cLocalVariable::Get (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244162.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (USHORT_T)lval;
  //## end cLocalVariable::Get%1071244162.body
}

void cLocalVariable::Get (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244163.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_LONG(value);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
      if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
   Accu()->Get(value);
   FormatOut(value, pos, flags);
  //## end cLocalVariable::Get%1071244163.body
}

void cLocalVariable::Get (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244164.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (ULONG_T)lval;
  //## end cLocalVariable::Get%1071244164.body
}

void cLocalVariable::Get (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244165.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
#ifdef ENABLE_UNITS
   GET_VIRTUAL_FLOAT(value);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
      if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
   Accu()->Get(value);
   HandleUnit(value, pos, flags);
   FormatOut(value, pos, flags);
#else
   DOUBLE_T dval = 0;
   Get(dval, i1, i2, i3, i4, flags);
   value = (FLOAT_T)dval;
#endif
  //## end cLocalVariable::Get%1071244165.body
}

void cLocalVariable::Get (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244166.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_DOUBLE(value);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
      if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
   Accu()->Get(value);
   HandleUnit(value, pos, flags);
   FormatOut(value, pos, flags);
  //## end cLocalVariable::Get%1071244166.body
}

void cLocalVariable::Get (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244167.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_STRING(value);
   SELECT_DATASET(flags)
   if (GetMemoryType(value, i1, i2, i3, i4, flags)) {
      return;
   }
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
      if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
#ifdef ENABLE_UNITS
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = _VarDef->_Precision;
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      precision = unit_def->Precision(GetInputState(pos));
   }

   // PR 15.11.05 read value with max. precision (RM rounding fix)
   Accu()->Get(value, MAX_PRECISION);

   HandleUnit(value, pos, flags);
   if (flags & VF_DATASET_REPRESENTATION) {
       if (data_type == SH_FLOAT || data_type == SH_DOUBLE) {
          /// PR 15.11.05 only restrict precision when value is not stored in a dataset (RM rounding fix)
          ///             or datatype is integral (fixed decimal)
       } else {
         FormatOut(value, pos, flags);
       }
   } else {
      FormatOut(value, pos, flags);
   }
#else
   Accu()->Get(value, _VarDef->_Precision);
   FormatOut(value, pos, flags);
#endif
  //## end cLocalVariable::Get%1071244167.body
}

void cLocalVariable::Get (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244168.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_WSTRING(value);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
      if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
   Accu()->Get(value, _VarDef->_Precision);
   FormatOut(value, pos, flags);
  //## end cLocalVariable::Get%1071244168.body
}

void cLocalVariable::Get (BUF_T &buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1071244169.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_BUF(buf);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   BUF_T src_buf = NULL;
   GetBuffer(pos, src_buf);
   Accu()->Set(src_buf);
   UCHAR_T var_type = _VarDef->_VarType;
   if (var_type != SH_VAR_SET) {
      cMapping * mapping = _VarDef->_Mapping;
      if (mapping != NULL && !(flags & VF_BUFFERED)) {
         GetDevice(pos, flags);
         BufChanged(i1, i2, i3, i4, flags);
      }
   }
   Accu()->Get(buf);
  //## end cLocalVariable::Get%1071244169.body
}

void cLocalVariable::Get (BUF_T &buf, ULONG_T & size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_BUF(buf);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   UCHAR_T data_type = _VarDef->_DataType;
   if (data_type == SH_OBJECT) {
      ULONG_T s = 0;
      if (ReadFilter(pos, flags, &s)) {
         BUF_T buffer = NULL;
         Accu()->Get(buffer);
         buf = buffer;
         size = s;
         return;
      }
      cMapping * mapping = _VarDef->_Mapping;
      if (mapping != NULL && !(flags & VF_BUFFERED)) {
         GetDevice(pos, flags);
         BufChanged(i1, i2, i3, i4, flags);
      }
      Accu()->Get(buf);
   } else {
      return;
   }
}

void cLocalVariable::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Get%1077626056.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   GET_VIRTUAL_BYTE(buf,len);
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   UCHAR_T var_type = _VarDef->_VarType;
#ifdef ALLOW_SET_FROM_DEVICE
   if ((var_type == SH_VAR_SET || flags & VF_BUFFERED) && !(flags & VF_DEVICE)) {
#else
   if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
#endif
      cMapping * mapping = _VarDef->_Mapping;
      if (mapping != NULL) {
         GetDevice(pos, flags);
      }
   }
   GetBuffer(pos, len);
   BUF_T src_buf = NULL;
   Accu()->Get(src_buf);
   CopyBuf(buf, len, src_buf, ValueSize());
  //## end cLocalVariable::Get%1077626056.body
}

void cLocalVariable::Refresh (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Refresh%1092218361.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   LONG_T lval = 0;
   DOUBLE_T dval = 0;
   STRING_T sval;
   WSTRING_T wsval;
   BUF_T buf = NULL;
   UCHAR_T data_type = DataType();
   switch (data_type) {
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
   case SH_UCHAR:
   case SH_BIT_8:
   case SH_USHORT:
   case SH_BIT_16:
   case SH_ULONG:
   case SH_BIT_32:
      Get(lval, i1, i2, i3, i4, flags);
      DataChanged(i1, i2, i3, i4, flags);
      break;
   case SH_FLOAT:
   case SH_DOUBLE:
      Get(dval, i1, i2, i3, i4, flags);
      DataChanged(i1, i2, i3, i4, flags);
      break;
   case SH_STRING:
      Get(sval, i1, i2, i3, i4, flags);
      DataChanged(i1, i2, i3, i4, flags);
      break;
   case SH_WSTRING:
      Get(wsval, i1, i2, i3, i4, flags);
      DataChanged(i1, i2, i3, i4, flags);
      break;
   case SH_BYTE:
      {
         // PR 27.10.11
         // as a consequence of accu management and not eventually noz calling Get
         // in this branch the value of buf on the accu may be NULL
         // if this is the case the buf value on the accu must be set to
         // the buffer of this variable with the correct index
         // PR refresh fix
         ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
         Accu()->Get(buf);
         if (buf == NULL) {
            GetBuffer(pos, buf);
            Accu()->Set(buf);
         }
      }
      // PR 19.09.05
      // Get(buf, i1, i2, i3, i4, flags);
      /// PR 15.11.05 in case of device mapped act values read from device
      ///             in advance to send data change event(HA refresh fix)
      if (_VarDef->_VarType == SH_VAR_VOLATILE ||
          _VarDef->_VarType == SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            Get(buf, i1, i2, i3, i4, flags);
         }
      }
      BufChanged(i1, i2, i3, i4, flags);
      break;
   case SH_OBJECT:
      Get(buf, i1, i2, i3, i4, flags);
      DataChanged(i1, i2, i3, i4, flags);
      break;
   }
  //## end cLocalVariable::Refresh%1092218361.body
}

void cLocalVariable::Set (CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244171.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1071244171.body
}

void cLocalVariable::Set (UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244172.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1071244172.body
}

void cLocalVariable::Set (SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244173.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1071244173.body
}

void cLocalVariable::Set (USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244174.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1071244174.body
}

void cLocalVariable::Set (LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244175.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   SET_VIRTUAL_LONG(value);
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FormatIn(value, pos, flags);
   LONG_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (has_unit_definition) {
      SetInput(pos, flags);
   }
   Accu()->Set(value);
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value);
               if (SetBuffer(pos) ||
                   has_unit_definition) {
                  DataChanged(i1, i2, i3, i4, flags);
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   if (SetBuffer(pos) ||
       has_unit_definition) {
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Set%1071244175.body
}

void cLocalVariable::Set (ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244176.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1071244176.body
}

void cLocalVariable::Set (FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244177.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   SET_VIRTUAL_FLOAT(value);
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FormatIn(value, pos, flags);
   FLOAT_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (has_unit_definition) {
      SetInput(pos, flags);
   }
   Accu()->Set(value);
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value);
               if (SetBuffer(pos) ||
                  has_unit_definition) {
                  DataChanged(i1, i2, i3, i4, flags);
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   if (SetBuffer(pos) ||
       has_unit_definition) {
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Set%1071244177.body
}

void cLocalVariable::Set (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244178.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   SET_VIRTUAL_DOUBLE(value);
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FormatIn(value, pos, flags);
   DOUBLE_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (has_unit_definition) {
      SetInput(pos, flags);
   }
   Accu()->Set(value);
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value);
               if (SetBuffer(pos) ||
                  has_unit_definition) {
                  DataChanged(i1, i2, i3, i4, flags);
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   if (SetBuffer(pos) ||
       has_unit_definition) {
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Set%1071244178.body
}

void cLocalVariable::Set (CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244179.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   if (value == NULL) {
      STRING_T var_ref = _VarDef->_VarName;
      if (i1 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i1);
         var_ref += "]";
      }
      if (i2 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i2);
         var_ref += "]";
      }
      if (i3 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i3);
         var_ref += "]";
      }
      if (i4 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i4);
         var_ref += "]";
      }
      throw cError(VARIABLE_SET_NULL_VALUE, 0, var_ref.c_str());
   }
   SET_VIRTUAL_STRING(value);
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   if (SetMemoryType(value, i1, i2, i3, i4, flags)) {
      return;
   }
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   STRING_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   FormatIn(temp_value, pos, flags);
   Accu()->Set(temp_value.c_str());
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            SetInput(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value.c_str());
               if (SetBuffer(pos) || _VarDef->get_UnitDef() != NULL) {
                  DataChanged(i1, i2, i3, i4, flags);
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (SetBuffer(pos) ||
       has_unit_definition) {
      SetInput(pos, flags);
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Set%1071244179.body
}

void cLocalVariable::Set (CONST_WSTRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1071244180.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   if (value == NULL) {
      STRING_T var_ref = _VarDef->_VarName;
      if (i1 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i1);
         var_ref += "]";
      }
      if (i2 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i2);
         var_ref += "]";
      }
      if (i3 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i3);
         var_ref += "]";
      }
      if (i4 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i4);
         var_ref += "]";
      }
      throw cError(VARIABLE_SET_NULL_VALUE, 0, var_ref.c_str());
   }
   SET_VIRTUAL_WSTRING(value);
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   WSTRING_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   FormatIn(temp_value, pos, flags);
   Accu()->Set(temp_value.c_str());
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            SetInput(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value.c_str());
               if (SetBuffer(pos) || _VarDef->get_UnitDef() != NULL) {
                  DataChanged(i1, i2, i3, i4, flags);
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (SetBuffer(pos) ||
       has_unit_definition) {
      SetInput(pos, flags);
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Set%1071244180.body
}

void cLocalVariable::Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Set%1077626057.body preserve=yes
   StoreIndices(i1, i2, i3, i4);
   if (buf == NULL) {
      STRING_T var_ref = _VarDef->_VarName;
      if (i1 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i1);
         var_ref += "]";
      }
      if (i2 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i2);
         var_ref += "]";
      }
      if (i3 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i3);
         var_ref += "]";
      }
      if (i4 != -1) {
         var_ref += "[";
         var_ref += cConvUtils::StringValue(i4);
         var_ref += "]";
      }
      throw cError(VARIABLE_SET_NULL_VALUE, 0, var_ref.c_str());
   }
   SET_VIRTUAL_BYTE(buf,len);
   SELECT_DATASET(flags)
//   CHECK_WRITE_ACCESS(flags)
// PR 18.05.05 avoid to read previous value when checking write access, check variable type only
   if (_VarDef->_VarType == SH_VAR_ACT) {
      throw cError(VARIABLE_READ_ONLY, 0, _VarDef->_VarName.c_str());
   }
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (_VarDef->DataType() == SH_OBJECT) {
      Accu()->Set((BUF_T)buf);
      if (WriteFilter(pos, flags, &len)) {
         return;
      }
   }
   BUF_T dst_buf = NULL;
   GetBuffer(pos, dst_buf);
   Accu()->Set(dst_buf);
   CopyBuf(dst_buf, ValueSize(), (BUF_T)buf, len);
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            if (SetDevice(pos, flags)) {
               BufChanged(i1, i2, i3, i4, flags);
               return;
            } else {
               throw cError(FAILED_TO_WRITE_DEVICE_BLOB_DATA, 0, _VarDef->_VarName.c_str());
            }
         }
      }
   }
   BufChanged(i1, i2, i3, i4, flags);
  //## end cLocalVariable::Set%1077626057.body
}

MAP_ITEM_T * cLocalVariable::MapItem(LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4) const
{
   if (_VarDef != NULL) {
      ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
      cMapping * mapping = _VarDef->_Mapping;
      if (mapping != NULL) {
         MAP_ITEM_T * map_item = mapping->MapItem(pos);
         return map_item;
      }
   }
   return NULL;
}

BOOL_T cLocalVariable::MappingEnabled(LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   if (_VarDef == NULL) {
      return true;
   }
   return _VarDef->MappingEnabled(i1, i2, i3, i4);
}

BOOL_T cLocalVariable::EnableMapping(ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   if (_VarDef == NULL) {
      return true;
   }
   return _VarDef->EnableMapping(value, i1, i2, i3, i4);
}

BOOL_T cLocalVariable::EnableCompleteMapping(ULONG_T value)
{
   if (_VarDef == NULL) {
      return true;
   }
   return _VarDef->EnableCompleteMapping(value);
}

void cLocalVariable::GetMinimum (ULONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cLocalVariable::GetMinimum%1089103312.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   ULONG_T min = 0;
   Min(min, DataType());
   UCHAR_T precision = Precision();
   if (precision == 0) {
      if (_MinArg != NULL) {
         cFuncRef * func_ref = _MinArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(min, i1, i2, i3, i4, 0);
         } else {
            _MinArg->GetValue(min);
         }
      }
   } else {
      DOUBLE_T temp_min = 0;
      if (_MinArg != NULL) {
         cFuncRef * func_ref = _MinArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(temp_min, i1, i2, i3, i4, 0);
         } else {
            _MinArg->GetValue(temp_min);
         }
         if (fixed_decimal_representation) {
            FormatIn(temp_min, pos);
         }
         min = (ULONG_T)temp_min;
      }
   }
   minimum = min;
  //## end cLocalVariable::GetMinimum%1089103312.body
}

void cLocalVariable::GetMinimum (LONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cLocalVariable::GetMinimum%1089103311.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   LONG_T min = 0;
   Min(min, DataType());
   UCHAR_T precision = Precision();
   if (precision == 0) {
      if (_MinArg != NULL) {
         cFuncRef * func_ref = _MinArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(min, i1, i2, i3, i4, 0);
         } else {
            _MinArg->GetValue(min);
         }
      }
   } else {
      DOUBLE_T temp_min = 0;
      if (_MinArg != NULL) {
         cFuncRef * func_ref = _MinArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(temp_min, i1, i2, i3, i4, 0);
         } else {
            _MinArg->GetValue(temp_min);
         }
         if (fixed_decimal_representation) {
            FormatIn(temp_min, pos);
         }
         min = (LONG_T)temp_min;
      }
   }
   minimum = min;
  //## end cLocalVariable::GetMinimum%1089103311.body
}

void cLocalVariable::GetMinimum (FLOAT_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMinimum%1089103313.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FLOAT_T min = 0;
   Min(min, DataType());
   if (_MinArg != NULL) {
      cFuncRef * func_ref = _MinArg->GetFuncRef();
      if (func_ref != NULL) {
         func_ref->CallMDLFunc(min, i1, i2, i3, i4, 0);
      } else {
         _MinArg->GetValue(min);
      }
   }
   minimum = min;
  //## end cLocalVariable::GetMinimum%1089103313.body
}

void cLocalVariable::GetMinimum (DOUBLE_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMinimum%1089103314.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   DOUBLE_T min = 0;
   Min(min, DataType());
   if (_MinArg != NULL) {
      cFuncRef * func_ref = _MinArg->GetFuncRef();
      if (func_ref != NULL) {
         func_ref->CallMDLFunc(min, i1, i2, i3, i4, 0);
      } else {
         _MinArg->GetValue(min);
      }
   }
   minimum = min;
  //## end cLocalVariable::GetMinimum%1089103314.body
}

void cLocalVariable::GetMinimum (STRING_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMinimum%1089203186.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   char value_buf[128] = {0};
   LONG_T lval = 0;
   ULONG_T ulval = 0;
   FLOAT_T fval = 0;
   DOUBLE_T dval = 0;
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
      GetMinimum(lval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%d", lval);
      break;
   case SH_UCHAR:
   case SH_BIT_8:
   case SH_USHORT:
   case SH_BIT_16:
   case SH_ULONG:
   case SH_BIT_32:
      GetMinimum(ulval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%d", ulval);
      break;
   case SH_FLOAT:
      GetMinimum(fval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%f", fval);
      break;
   case SH_DOUBLE:
      GetMinimum(dval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%f", dval);
      break;
   }
   minimum = value_buf;
   FormatOut(minimum, pos);
  //## end cLocalVariable::GetMinimum%1089203186.body
}

void cLocalVariable::GetMaximum (LONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cLocalVariable::GetMaximum%1089103315.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   LONG_T max = 0;
   Max(max, DataType());
   UCHAR_T precision = Precision();
   if (precision == 0) {
      if (_MaxArg != NULL) {
         cFuncRef * func_ref = _MaxArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(max, i1, i2, i3, i4, 0);
         } else {
            _MaxArg->GetValue(max);
         }
      }
   } else {
      DOUBLE_T temp_max = 0;
      if (_MaxArg != NULL) {
         cFuncRef * func_ref = _MaxArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(temp_max, i1, i2, i3, i4, 0);
         } else {
            _MaxArg->GetValue(temp_max);
         }
         if (fixed_decimal_representation) {
            FormatIn(temp_max, pos);
         }
         max = (LONG_T)temp_max;
      }
   }
   maximum = max;
  //## end cLocalVariable::GetMaximum%1089103315.body
}

void cLocalVariable::GetMaximum (ULONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cLocalVariable::GetMaximum%1089103316.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   ULONG_T max = 0;
   Max(max, DataType());
   UCHAR_T precision = Precision();
   if (precision == 0) {
      if (_MaxArg != NULL) {
         cFuncRef * func_ref = _MaxArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(max, i1, i2, i3, i4, 0);
         } else {
            _MaxArg->GetValue(max);
         }
      }
   } else {
      DOUBLE_T temp_max = 0;
      if (_MaxArg != NULL) {
         cFuncRef * func_ref = _MaxArg->GetFuncRef();
         if (func_ref != NULL) {
            func_ref->CallMDLFunc(temp_max, i1, i2, i3, i4, 0);
         } else {
            _MaxArg->GetValue(temp_max);
         }
         if (fixed_decimal_representation) {
            FormatIn(temp_max, pos);
         }
         max = (ULONG_T)temp_max;
      }
   }
   maximum = max;
//   FormatOut(maximum, pos);
  //## end cLocalVariable::GetMaximum%1089103316.body
}

void cLocalVariable::GetMaximum (FLOAT_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMaximum%1089103317.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FLOAT_T max = 0;
   Max(max, DataType());
   if (_MaxArg != NULL) {
      cFuncRef * func_ref = _MaxArg->GetFuncRef();
      if (func_ref != NULL) {
         func_ref->CallMDLFunc(max, i1, i2, i3, i4, 0);
      } else {
         _MaxArg->GetValue(max);
      }
   }
   maximum = max;
   FormatOut(maximum, pos);
  //## end cLocalVariable::GetMaximum%1089103317.body
}

void cLocalVariable::GetMaximum (DOUBLE_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMaximum%1089103318.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   DOUBLE_T max = 0;
   Max(max, DataType());
   if (_MaxArg != NULL) {
      cFuncRef * func_ref = _MaxArg->GetFuncRef();
      if (func_ref != NULL) {
         func_ref->CallMDLFunc(max, i1, i2, i3, i4, 0);
      } else {
         _MaxArg->GetValue(max);
      }
   }
   maximum = max;
   FormatOut(maximum, pos);
  //## end cLocalVariable::GetMaximum%1089103318.body
}

void cLocalVariable::GetMaximum (STRING_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetMaximum%1089203187.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   char value_buf[128] = {0};
   LONG_T lval = 0;
   ULONG_T ulval = 0;
   FLOAT_T fval = 0;
   DOUBLE_T dval = 0;
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
      GetMaximum(lval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%d", lval);
      break;
   case SH_UCHAR:
   case SH_BIT_8:
   case SH_USHORT:
   case SH_BIT_16:
   case SH_ULONG:
   case SH_BIT_32:
      GetMaximum(ulval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%u", ulval);
      break;
   case SH_FLOAT:
      GetMaximum(fval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%f", fval);
      break;
   case SH_DOUBLE:
      GetMaximum(dval, i1, i2, i3, i4);
      SafePrintf(value_buf, sizeof(value_buf), "%f", dval);
      break;
   }
   maximum = value_buf;
   FormatOut(maximum, pos);
  //## end cLocalVariable::GetMaximum%1089203187.body
}

BOOL_T cLocalVariable::IsBackgroundSensitive ()
{
  //## begin cLocalVariable::IsBackgroundSensitive%1138360005.body preserve=yes
   return _VarDef->_BackgroundVar;
  //## end cLocalVariable::IsBackgroundSensitive%1138360005.body
}

void cLocalVariable::DataChanged (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
#ifndef BASE_LIBRARY
   if (flags & VF_NO_DATACHANGE)
      return;

   ULONG_T data_type = _VarDef->_DataType;
   UCHAR_T var_type = VarType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      BufChanged(i1, i2, i3, i4, flags);
      return;
   }
   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   ULONG_T if_type = 0;
   ULONG_T client_id = 0;
   if (user_info != NULL) {
      if_type = user_info->get_IFType();
      client_id = user_info->get_ClientId();
   }
   STRING_T value;
   if (if_type != 0) {
      /// PR 15.03.06 if i am a host interface please behave
      /// as i where a "normal" client like user interface or a program
      user_info->set_IFType(0);
      user_info->set_ClientId(0);
      Get(value, i1, i2, i3, i4, VF_BUFFERED);
      if (user_info != NULL) {
         user_info->set_IFType(if_type);
         user_info->set_ClientId(client_id);
      }
   } else {
      Get(value, i1, i2, i3, i4, VF_BUFFERED);
   }
   ULONG_T pos = 0;
   if (var_type != SH_VAR_VIRTUAL) {
      pos = _VarDef->GetPos(i1, i2, i3, i4);
   }
   cDataChange * data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                               _VarId,
                                               value.c_str(),
                                               i1, i2, i3, i4);
   ULONG_T dataset = 0;
   if (flags & VF_BACKGROUND)
      dataset = BACKGROUND_DATASET;
   else if (flags & VF_SHADOW)
      dataset = SHADOW_DATASET;

   if (user_info == NULL) {
      data_change->set_DataSet(dataset);
   } else {
      if (dataset == 0)
         dataset = user_info->get_DataSet();
      if (var_type != SH_VAR_VIRTUAL) {
         data_change->set_DataSet(dataset);
      } else {
         if (dataset < MAX_DATASETS && _DataSets[dataset] != NULL) {
            data_change->set_DataSet(dataset);
         } else {
            data_change->set_DataSet(FOREGROUND_DATASET);
         }
      }
      if (dataset == 0) {
         data_change->set_UserName(user_info->get_UserName());
         data_change->set_OldValue(_PreviousValue);
      }
   }
   data_change->set_CellName(_Context->get_Name());
   data_change->set_DataType(DataType());
   data_change->set_PersistenceType(PersistenceType());
   data_change->set_ValueSize(ValueSize());
   data_change->set_Pos(pos);
   data_change->set_Precision(Precision());
   data_change->set_VarType(var_type);
   data_change->set_Value(value);
   if (flags & VF_FILE_INPUT) {
      data_change->set_ChangeFlags(CH_FLAG_FILE_INPUT);
   }
   _Context->Send(data_change);
   RELEASE_OBJECT(data_change)
   if (IS_PERSISTENT(PersistenceType())) {
      if (dataset == 0) {
         if (_PersistenceChannel == NULL) {
            _PersistenceChannel = _Context->PersistenceChannel();
         }
         if (_PersistenceChannel != NULL) {
            STRING_T persistent_value;
            UCHAR_T persistent_state = 0;
            GetRaw(persistent_state, persistent_value, i1, i2, i3, i4); 
            cDataChange * persistent_data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                                                   _VarId,
                                                                   persistent_value.c_str(),
                                                                   i1, i2, i3, i4);
            persistent_data_change->set_DataType(DataType());
            persistent_data_change->set_PersistenceType(PersistenceType());
            persistent_data_change->set_ValueSize(ValueSize());
            persistent_data_change->set_Pos(pos);
            persistent_data_change->set_Precision(Precision());
            persistent_data_change->set_VarType(var_type);
            persistent_data_change->set_Value(persistent_value);
            persistent_data_change->set_UnitCode(persistent_state);
            if (flags & VF_FILE_INPUT) {
               persistent_data_change->set_ChangeFlags(CH_FLAG_FILE_INPUT);
            }
            _PersistenceChannel->Send(persistent_data_change);
            RELEASE_OBJECT(persistent_data_change)
            if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
               CheckShadowDataset(i1, i2, i3, i4);
            }
         }
      } else {
         int dummy = 0;
      }
   }
#endif
}

void cLocalVariable::DataChanged (CONST_STRING_T old_value, CONST_STRING_T new_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
#ifndef BASE_LIBRARY
   if (flags & VF_NO_DATACHANGE)
      return;

   UCHAR_T var_type = VarType();
   cDataChange * data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                               _VarId,
                                               new_value,
                                               i1, i2, i3, i4);
   data_change->set_OldValue(old_value);

   ULONG_T dataset = 0;
   if (flags & VF_BACKGROUND)
      dataset = BACKGROUND_DATASET;
   else if (flags & VF_SHADOW)
      dataset = SHADOW_DATASET;

   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   if (user_info == NULL) {
      data_change->set_DataSet(dataset);
   }
   else {
      if (dataset == 0)
         dataset = user_info->get_DataSet();
      if (var_type == SH_VAR_VIRTUAL) {
         data_change->set_DataSet(dataset);
      } else {
         if (dataset < MAX_DATASETS && _DataSets[dataset] != NULL) {
            data_change->set_DataSet(dataset);
         } else {
            data_change->set_DataSet(FOREGROUND_DATASET);
         }
      }
      if (dataset == 0) {
         data_change->set_UserName(user_info->get_UserName());
      }
   }
   ULONG_T pos = 0;
   if (var_type != SH_VAR_VIRTUAL) {
      pos = _VarDef->GetPos(i1, i2, i3, i4);
   }
   data_change->set_CellName(_Context->get_Name());
   data_change->set_DataType(DataType());
   data_change->set_PersistenceType(PersistenceType());
   data_change->set_ValueSize(ValueSize());
   data_change->set_Pos(pos);
   data_change->set_Precision(Precision());
   data_change->set_VarType(var_type);
   _Context->Send(data_change);
   RELEASE_OBJECT(data_change)
   if (IS_PERSISTENT(PersistenceType())) {
      if (dataset == 0) {
         if (_PersistenceChannel == NULL) {
            _PersistenceChannel = _Context->PersistenceChannel();
         }
         if (_PersistenceChannel != NULL) {
            STRING_T persistent_value;
            UCHAR_T persistent_state = 0;
            GetRaw(persistent_state, persistent_value, i1, i2, i3, i4); 
            cDataChange * persistent_data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                                                   _VarId,
                                                                   persistent_value.c_str(),
                                                                   i1, i2, i3, i4);
            persistent_data_change->set_DataType(DataType());
            persistent_data_change->set_PersistenceType(PersistenceType());
            persistent_data_change->set_ValueSize(ValueSize());
            persistent_data_change->set_Pos(pos);
            persistent_data_change->set_Precision(Precision());
            persistent_data_change->set_VarType(var_type);
            persistent_data_change->set_Value(persistent_value);
            persistent_data_change->set_UnitCode(persistent_state);
            if (flags & VF_FILE_INPUT) {
               persistent_data_change->set_ChangeFlags(CH_FLAG_FILE_INPUT);
            }
            _PersistenceChannel->Send(persistent_data_change);
            RELEASE_OBJECT(persistent_data_change)
         }
      } else {
         int dummy = 0;
      }
   }
#endif
}

void cLocalVariable::BufChanged (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
#ifndef BASE_LIBRARY
   UCHAR_T var_type = VarType();
   BUF_T buf = NULL;
   Accu()->Get(buf);
   if (buf == NULL) {
       ErrorPrintf("buffer is NULL in BufChanged(..) of %s\n", _VarDef->_VarName.c_str());
       return;
   }
   ULONG_T pos = 0;
   if (var_type != SH_VAR_VIRTUAL) {
      pos = _VarDef->GetPos(i1, i2, i3, i4);
   }
   cDataChange * data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                               _VarId,
                                               buf,
                                               i1, i2, i3, i4);

   ULONG_T dataset = 0;
   if (flags & VF_BACKGROUND)
      dataset = BACKGROUND_DATASET;
   else if (flags & VF_SHADOW)
      dataset = SHADOW_DATASET;

   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   if (user_info == NULL) {
      data_change->set_DataSet(dataset);
   } else {
      if (dataset == 0)
         dataset = user_info->get_DataSet();
      if (var_type == SH_VAR_VIRTUAL) {
         data_change->set_DataSet(dataset);
      }
      else {
         if (dataset < MAX_DATASETS && _DataSets[dataset] != NULL) {
            data_change->set_DataSet(dataset);
         }
         else {
            data_change->set_DataSet(FOREGROUND_DATASET);
         }
      }
      if (dataset == 0) {
         data_change->set_UserName(user_info->get_UserName());
      }
   }

   data_change->set_CellName(_Context->get_Name());
   data_change->set_DataType(DataType());
   data_change->set_PersistenceType(PersistenceType());
   data_change->set_ValueSize(ValueSize());
   data_change->set_Pos(pos);
   data_change->set_VarType(var_type);
   if (flags & VF_FILE_INPUT) {
      data_change->set_ChangeFlags(CH_FLAG_FILE_INPUT);
   }
   _Context->Send(data_change);
   if (IS_PERSISTENT(PersistenceType())) {
      /// PR 23.01.06 retrieving the persistence channel reference only when its really used
      if (_PersistenceChannel == NULL) {
         _PersistenceChannel = _Context->PersistenceChannel();
      }
      if (_PersistenceChannel != NULL) {
         _PersistenceChannel->Send(data_change);
      } else {
         ErrorPrintf("persistence channel not ready %s\n", _VarDef->_VarName.c_str());
      }
   }
   RELEASE_OBJECT(data_change)
#endif
}

void cLocalVariable::GetBuffer (ULONG_T pos, ULONG_T len)
{
  //## begin cLocalVariable::GetBuffer%1042559816.body preserve=yes
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      return;
   }
   if (!_Initialized && _VarDef->_PersistenceType != 0) {
#ifndef BASE_LIBRARY
      cLocalContext * context = (cLocalContext*)_Context;
      if (context->get_RunFlags() & RF_BBRAM_INITIALIZED) {
         /// ignore it
      } else {
         ErrorPrintf("warning: reading uninitialized variable %s\n", _VarDef->_VarName.c_str());
         _Initialized = true;
      }
#endif
   }
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_CHAR:
      {
         CHAR_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_SHORT:
      {
         SHORT_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_LONG:
      {
         LONG_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_FLOAT:
      {
         FLOAT_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_DOUBLE:
      {
         DOUBLE_T value;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   case SH_BYTE:
      {
         if (len > 0) {
            int size = _MIN_(len, _VarDef->ElementSize());
            BUF_T src_buf = NULL;
            _Values->Get(pos, src_buf);
            // potentially dereferencing NULL pointer
            if (src_buf != NULL) {
               BUF_T dst_buf = NULL;
               Accu()->Get(dst_buf);
               memcpy((void*)dst_buf, (void*)src_buf, size);
               int fill = len - size;
               if (fill > 0) memset((void*)dst_buf, 0, fill);
            }
         } else {
            BUF_T buf = NULL;
            _Values->Get(pos, buf);
            STRING_T value;
            cConvUtils::Buf2String(value, buf, ValueSize());
            Accu()->Set(value.c_str());
            Accu()->Set(buf);
         }
      }
      return;
   case SH_STRING:
      {
         STRING_T value;
         _Values->Get(pos, value);
         Accu()->Set(value.c_str());
      }
      return;
   case SH_WSTRING:
      {
         WSTRING_T value;
         _Values->Get(pos, value);
         Accu()->Set(value.c_str());
      }
      return;
   case SH_OBJECT:
      {
         BUF_T value = NULL;
         _Values->Get(pos, value);
         Accu()->Set(value);
      }
      return;
   }
_ASSERT_UNCOND
  //## end cLocalVariable::GetBuffer%1042559816.body
}

void cLocalVariable::GetBuffer (ULONG_T pos, BUF_T &buf)
{
  //## begin cLocalVariable::GetBuffer%1136794166.body preserve=yes
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      buf = NULL;
      return;
   }
   if (!_Initialized && _VarDef->_PersistenceType != 0) {
#ifndef BASE_LIBRARY
      cLocalContext * context = (cLocalContext*)_Context;
      if (context->get_RunFlags() & RF_BBRAM_INITIALIZED) {
         /// ignore it
      } else {
         ErrorPrintf("warning: reading uninitialized variable %s\n", _VarDef->_VarName.c_str());
         _Initialized = true;
      }
#endif
   }
   _Values->Get(pos, buf);
  //## end cLocalVariable::GetBuffer%1136794166.body
}

BOOL_T cLocalVariable::SetBuffer (ULONG_T pos, ULONG_T len)
{
  //## begin cLocalVariable::SetBuffer%1042559817.body preserve=yes
   _Initialized = true;
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      return false;
   }
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_CHAR:
      {
         CHAR_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_SHORT:
      {
         SHORT_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_LONG:
      {
         LONG_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_FLOAT:
      {
         FLOAT_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_DOUBLE:
      {
         DOUBLE_T value;
         Accu()->Get(value);
         return _Values->Set(pos, value);
      }
   case SH_BYTE:
      {
         // actually there is no reaction
         // the accu contains a pointer to the internal buffer
         return true;
      }
   case SH_STRING:
      {
         STRING_T value;
         Accu()->Get(value, MAX_PRECISION);
         return _Values->Set(pos, value.c_str());
      }
   case SH_WSTRING:
      {
         WSTRING_T value;
         Accu()->Get(value, MAX_PRECISION);
         return _Values->Set(pos, value.c_str());
      }
   case SH_OBJECT:
      {
         return false;
      }
   }
_ASSERT_UNCOND
   return false;
  //## end cLocalVariable::SetBuffer%1042559817.body
}

void cLocalVariable::FormatOut (DOUBLE_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatOut%1042559822.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = 0;
   if (_VarDef->get_UnitDef() != NULL) {
      precision = _VarDef->get_UnitDef()->Precision(_VarDef->get_UnitDef()->GetState());
   } else {
      precision = _VarDef->_Precision;
   }
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      {
         if (precision > 0) {
            for (ULONG_T i=0; i<precision; i++) {
	   			value /= 10;
		   	}
		   }
      }
		break;
   case SH_FLOAT:
   case SH_DOUBLE:
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatOut%1042559822.body
}

void cLocalVariable::FormatOut (FLOAT_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatOut%1071244306.body preserve=yes
	DOUBLE_T dval = value;
	FormatOut(dval, pos, flags);
	value = (FLOAT_T)dval;
  //## end cLocalVariable::FormatOut%1071244306.body
}

void cLocalVariable::FormatOut (LONG_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatOut%1042559821.body preserve=yes
	DOUBLE_T dval = value;
	FormatOut(dval, pos, flags);
	value = (LONG_T)dval;
  //## end cLocalVariable::FormatOut%1042559821.body
}

void cLocalVariable::FormatOut (STRING_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatOut%1042559820.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = 0;
   if (_VarDef->get_UnitDef() != NULL) {
      precision = _VarDef->get_UnitDef()->Precision(_VarDef->get_UnitDef()->GetState());
   } else {
      precision = _VarDef->_Precision;
   }
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      if (precision > 0) {
         DOUBLE_T lval = atof(value.c_str());
         for (ULONG_T i=0; i<precision; i++) {
				lval /= 10;
         }
         cSHVariant::Double2String(value, lval, precision);
      }
      break;
   case SH_FLOAT:
   case SH_DOUBLE:
   {
      DOUBLE_T fval = atof(value.c_str());
      cSHVariant::Double2String(value, fval, precision);
      break;
   }
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatOut%1042559820.body
}

void cLocalVariable::FormatOut (WSTRING_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatOut%1071244307.body preserve=yes
  //## end cLocalVariable::FormatOut%1071244307.body
}

void cLocalVariable::FormatIn (STRING_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatIn%1042559823.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = 0;
   if (_VarDef->get_UnitDef() != NULL) {
      precision = _VarDef->get_UnitDef()->Precision(_VarDef->get_UnitDef()->GetState());
   } else {
      precision = _VarDef->_Precision;
   }
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      {
         char value_buf[64] = {0};
   		 double lval = atof(value.c_str());
	   	 for (unsigned long i=0; i<precision; i++) {
		    lval *= 10;
         }

         if ((precision >= 0) && (precision <= 6)) {
            SafePrintf(value_buf, sizeof(value_buf), "%.*f", precision, lval);
         }
         else {
            SafePrintf(value_buf, sizeof(value_buf), "%.lf", lval);
         }
		 value = value_buf;
      }
	  break;
   case SH_FLOAT:
   case SH_DOUBLE:
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatIn%1042559823.body
}

void cLocalVariable::FormatIn (LONG_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatIn%1042559824.body preserve=yes
   DOUBLE_T dval = value;
   FormatIn(dval, pos, flags);
   value = (LONG_T)dval;
  //## end cLocalVariable::FormatIn%1042559824.body
}

void cLocalVariable::FormatIn (FLOAT_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatIn%1121085449.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = 0;
   if (_VarDef->get_UnitDef() != NULL) {
      precision = _VarDef->get_UnitDef()->Precision(_VarDef->get_UnitDef()->GetState());
   } else {
      precision = _VarDef->_Precision;
   }
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      {
		   if (precision > 0) {
			   for (ULONG_T i=0; i<precision; i++) {
				   value *= 10;
			   }
		   }
      }
		break;
   case SH_FLOAT:
   case SH_DOUBLE:
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatIn%1121085449.body
}

void cLocalVariable::FormatIn (DOUBLE_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatIn%1042559825.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T precision = 0;
   if (_VarDef->get_UnitDef() != NULL) {
      precision = _VarDef->get_UnitDef()->Precision(_VarDef->get_UnitDef()->GetState());
   } else {
      precision = _VarDef->_Precision;
   }
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      {
		   if (precision > 0) {
			   for (ULONG_T i=0; i<precision; i++) {
				   value *= 10;
			   }
		   }
      }
		break;
   case SH_FLOAT:
   case SH_DOUBLE:
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatIn%1042559825.body
}

void cLocalVariable::FormatIn (WSTRING_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::FormatIn%1071244308.body preserve=yes
  //## end cLocalVariable::FormatIn%1071244308.body
}

void cLocalVariable::ReadConversion (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::ReadConversion%1051713135.body preserve=yes
   if (_ConvFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
         }
		   break;
      case SH_BYTE:
      case SH_STRING:
      case SH_WSTRING:
      case SH_OBJECT:
         break;
      }
   }
  //## end cLocalVariable::ReadConversion%1051713135.body
}

void cLocalVariable::WriteConversion (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::WriteConversion%1071498211.body preserve=yes
   if (_ConvFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _ConvFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
         }
		   break;
      case SH_BYTE:
      case SH_STRING:
      case SH_WSTRING:
      case SH_OBJECT:
         break;
      }
   }
  //## end cLocalVariable::WriteConversion%1071498211.body
}

BOOL_T cLocalVariable::ReadFilter (ULONG_T pos, ULONG_T flags, ULONG_T * size)
{
  //## begin cLocalVariable::ReadFilter%1074783623.body preserve=yes
   if (flags & VF_BUFFERED) {
      return false;
   }
   ULONG_T if_type = VF_GET_IF_TYPE(flags);
   if (if_type != IF_PROPRIETARY) {
      return ReadAccessFilter(pos, flags);
   }
   if (_FilterFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_STRING:
         {
#ifdef old_and_unpreferred_version
            STRING_T value;
            GetBuffer(pos);
            Accu()->Get(value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, 0);
            Accu()->Set(value.c_str());
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
#else
            STRING_T value;
            STRING_T old_value;
            GetBuffer(pos);
            Accu()->Get(old_value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, old_value.c_str(), i1, i2, i3, i4, 0);
            Accu()->Set(value.c_str());
            if (SetBuffer(pos)) {
               DataChanged(old_value.c_str(), value.c_str(), i1, i2, i3, i4, flags);
            }
#endif
            return true;
         }
         break;
      case SH_BYTE:
      case SH_WSTRING:
         break;
      case SH_OBJECT:
         {
            PTR_T value = NULL;
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, size, i1, i2, i3, i4, flags);
            Accu()->Set((BUF_T)value);
            return true;
         }
         break;
      }
   }
   return false;
  //## end cLocalVariable::ReadFilter%1074783623.body
}

BOOL_T cLocalVariable::WriteFilter (ULONG_T pos, ULONG_T flags, ULONG_T * size)
{
  //## begin cLocalVariable::WriteFilter%1074783624.body preserve=yes
   if (flags & VF_BUFFERED) {
      return false;
   }
   ULONG_T if_type = VF_GET_IF_TYPE(flags);
   if (if_type != IF_PROPRIETARY) {
      return WriteAccessFilter(pos, flags);
   }
   if (_FilterFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_STRING:
         {
#ifdef old_and_unpreferred_version
            STRING_T value;
            Accu()->Get(value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value.c_str());
#else
            STRING_T value;
            Accu()->Get(value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value.c_str());
#endif
            return true;
         }
		   break;
      case SH_BYTE:
      case SH_WSTRING:
         break;
      case SH_OBJECT:
         {
            PTR_T value = NULL;
            Accu()->Get((BUF_T&)value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _FilterFuncRef->CallMDLFunc(value, value, size, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
         break;
      }
   }
   return false;
  //## end cLocalVariable::WriteFilter%1074783624.body
}

void cLocalVariable::GetDevice (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::GetDevice%1071317836.body preserve=yes
   StoreIndices(pos);
   cMapping * mapping = _VarDef->_Mapping;
   if (mapping == NULL) throw cError(VARIABLE_NO_MAPPING, 0, _VarDef->_VarName.c_str(),
                                     cConvUtils::StringValue(pos).c_str());
   MAP_ITEM_T * map_item = mapping->MapItem(pos);
   if (map_item == NULL) throw cError(VARIABLE_NO_MAP_ITEM, 0, _VarDef->_VarName.c_str(),
                                      cConvUtils::StringValue(pos).c_str());
   CONST_STRING_T buf_spec = map_item->buf_spec;
   ULONG_T size = map_item->size;
   cDevice * device = map_item->device;
   if (device == NULL) throw cError(VARIABLE_NO_DEVICE, 0, _VarDef->_VarName.c_str(),
                                    cConvUtils::StringValue(pos).c_str());
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T map_data_type = map_item->data_type;
   ULONG_T address = map_item->address;
   CONST_STRING_T name = map_item->name;
   if (address == (ULONG_T)UNDEFINED_SYMBOL_VALUE && name == NULL) {
      throw cError(VARIABLE_NULL_MAPPING, 0, _VarDef->_VarName.c_str(),
                   cConvUtils::StringValue(pos).c_str());
   }
#ifdef SYNC_DEVICE_PARAMETERS
   if (FilterInternalDataGet(device, buf_spec, name)) {
      return;
   }
#endif
   UCHAR_T bit_pos_b = map_item->bit_pos_b;
   UCHAR_T bit_pos_e = map_item->bit_pos_e;
   if (bit_pos_b == UNUSED_BITPOS) {
      if (address == UNUSED_ADDRESS) {
         GetDevice(device, buf_spec, name, map_data_type, size, flags);
      } else {
         GetDevice(device, buf_spec, address, map_data_type, size, flags);
      }
   } else {
      if (address == UNUSED_ADDRESS) {
         CONST_STRING_T name = map_item->name;
         GetDevice(device, buf_spec, name, map_data_type, bit_pos_b, bit_pos_e, flags);
      } else {
         GetDevice(device, buf_spec, address, map_data_type, bit_pos_b, bit_pos_e, flags);
      }
   }
  //## end cLocalVariable::GetDevice%1071317836.body
}

void cLocalVariable::GetDevice (cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, ULONG_T size, ULONG_T flags)
{
  //## begin cLocalVariable::GetDevice%1075382074.body preserve=yes
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         device->Get(buf_spec, address, value, flags);
         device->Cast(buf_spec, data_type, value);
         if (data_type == SH_CHAR) {
            Accu()->Set((CHAR_T)value);
         } else {
            Accu()->Set(value);
         }
      }
      return;
   case SH_SHORT:
      {
         SHORT_T value = 0;
         USHORT_T _value = 0;
         device->Get(buf_spec, address, _value, flags);
         device->Cast(buf_spec, data_type, _value);
         value = _value;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
         device->Get(buf_spec, address, value, flags);
         device->Cast(buf_spec, data_type, value);
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_LONG:
      {
         LONG_T value = 0;
         ULONG_T _value = 0;
         device->Get(buf_spec, address, _value, flags);
         device->Cast(buf_spec, data_type, _value);
         value = _value;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
         device->Get(buf_spec, address, value, flags);
         device->Cast(buf_spec, data_type, value);
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_FLOAT:
      {
         FLOAT_T value = 0;
         device->Get(buf_spec, address, value, flags);
         device->Cast(buf_spec, data_type, value);
         Accu()->Set(value);
      }
      return;
   case SH_DOUBLE:
      {
         DOUBLE_T value = 0;
         device->Get(buf_spec, address, value, flags);
         device->Cast(buf_spec, data_type, value);
         Accu()->Set(value);
      }
      return;
   case SH_BYTE:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         if (buf != NULL) {
            device->Read(buf_spec, address, size, buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
      }
      return;
   case SH_STRING:
      {
         STRING_T value;
// PR 03.07.2004 using read operation instead of get
         cBlockBuffer block_buffer;
         CONST_STRING_T buf = (CONST_STRING_T)block_buffer.AllocBlock(size + sizeof(CHAR_T));
         if (buf != NULL) {
            device->Read(buf_spec, address, size, (BUF_T)buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
         value = buf;
         Accu()->Set(value.c_str());
      }
      return;
   case SH_WSTRING:
      {
         WSTRING_T value;
// PR 03.07.2004 using read operation instead of get
         cBlockBuffer block_buffer;
         CONST_WSTRING_T buf = (CONST_WSTRING_T)block_buffer.AllocBlock(size + sizeof(WCHAR_T));
         if (buf != NULL) {
            device->Read(buf_spec, address, size, (BUF_T)buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
         value = buf;
         Accu()->Set(value.c_str());
      }
      return;
   case SH_OBJECT:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         if (buf != NULL) {
            device->Read(buf_spec, address, size, buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
      }
      return;
   }
_ASSERT_UNCOND
  //## end cLocalVariable::GetDevice%1075382074.body
}

void cLocalVariable::GetDevice (cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, ULONG_T size, ULONG_T flags)
{
  //## begin cLocalVariable::GetDevice%1075382076.body preserve=yes
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         device->Get(buf_spec, name, value, flags);
         device->Cast(buf_spec, data_type, value);
         if (data_type == SH_CHAR) {
            Accu()->Set((CHAR_T)value);
         } else {
            Accu()->Set(value);
         }
      }
      return;
   case SH_SHORT:
      {
         SHORT_T value = 0;
         USHORT_T _value = 0;
         device->Get(buf_spec, name, _value, flags);
         device->Cast(buf_spec, data_type, _value);
         value = _value;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
         device->Get(buf_spec, name, value, flags);
         device->Cast(buf_spec, data_type, value);
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_LONG:
      {
         LONG_T value = 0;
         ULONG_T _value = 0;
         device->Get(buf_spec, name, _value, flags);
         device->Cast(buf_spec, data_type, _value);
         value = _value;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
         device->Get(buf_spec, name, value, flags);
         device->Cast(buf_spec, data_type, value);
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = (FLOAT_T)value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = value;
            for (int i=0; i<dev_precision; i++) {
               fvalue /= 10;
            }
            Accu()->Set(fvalue);
         } else {
            Accu()->Set(value);
         }
#else
         Accu()->Set(value);
#endif
      }
      return;
   case SH_FLOAT:
      {
         FLOAT_T value = 0;
         device->Get(buf_spec, name, value, flags);
         device->Cast(buf_spec, data_type, value);
         Accu()->Set(value);
      }
      return;
   case SH_DOUBLE:
      {
         DOUBLE_T value = 0;
         device->Get(buf_spec, name, value, flags);
         device->Cast(buf_spec, data_type, value);
         Accu()->Set(value);
      }
      return;
   case SH_BYTE:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         if (buf != NULL) {
            device->Read(buf_spec, name, size, buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
      }
      return;
   case SH_STRING:
      {
         STRING_T value;
// PR 01.02.2012 using read operation instead of get
         cBlockBuffer block_buffer;
         CONST_STRING_T buf = (CONST_STRING_T)block_buffer.AllocBlock(size + sizeof(CHAR_T));
         if (buf != NULL) {
            device->Read(buf_spec, name, size, (BUF_T)buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
         value = buf;
         Accu()->Set(value.c_str());
/*
         STRING_T value;
         device->Get(buf_spec, name, value, flags);
         Accu()->Set(value.c_str());
*/
      }
      return;
   case SH_WSTRING:
      {
         WSTRING_T value;
// PR 01.02.2012 using read operation instead of get
         cBlockBuffer block_buffer;
         CONST_WSTRING_T buf = (CONST_WSTRING_T)block_buffer.AllocBlock(size + sizeof(WCHAR_T));
         if (buf != NULL) {
            device->Read(buf_spec, name, size, (BUF_T)buf, size, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
         value = buf;
         Accu()->Set(value.c_str());
/*
         WSTRING_T value;
         device->Get(buf_spec, name, value, flags);
         Accu()->Set(value.c_str());
*/
      }
      return;
   case SH_OBJECT:
      {
      }
      return;
   }
_ASSERT_UNCOND
  //## end cLocalVariable::GetDevice%1075382076.body
}

void cLocalVariable::GetDevice (cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags)
{
  //## begin cLocalVariable::GetDevice%1075382075.body preserve=yes
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         device->Get(buf_spec, address, value, flags);
         value = (UCHAR_T)device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e);
         if (data_type == SH_CHAR) {
            Accu()->Set((CHAR_T)value);
         } else {
            Accu()->Set(value);
         }
      }
      return;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
         device->Get(buf_spec, address, value, flags);
         value = (USHORT_T)device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e, flags);
         Accu()->Set(value);
      }
      return;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
         device->Get(buf_spec, address, value, flags);
         value = (ULONG_T)device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e, flags);
         Accu()->Set(value);
      }
      return;
   }
_ASSERT_UNCOND
  //## end cLocalVariable::GetDevice%1075382075.body
}

void cLocalVariable::GetDevice (cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags)
{
  //## begin cLocalVariable::GetDevice%1075382077.body preserve=yes
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         device->Get(buf_spec, name, value, flags);
         value = (UCHAR_T)device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e, flags);
         if (data_type == SH_CHAR) {
            Accu()->Set((CHAR_T)value);
         } else {
            Accu()->Set(value);
         }
      }
      return;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
         device->Get(buf_spec, name, value, flags);
         value = (USHORT_T)device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e, flags);
         Accu()->Set(value);
      }
      return;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
         device->Get(buf_spec, name, value, flags);
         value = device->GetPattern(buf_spec, data_type, value, bit_pos_b, bit_pos_e, flags);
         Accu()->Set(value);
      }
      return;
   }
_ASSERT_UNCOND
  //## end cLocalVariable::GetDevice%1075382077.body
}

BOOL_T cLocalVariable::SetDevice (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::SetDevice%1071317837.body preserve=yes
#ifndef BASE_LIBRARY
   StoreIndices(pos);

   if ((flags & VF_BACKGROUND) || (flags & VF_SHADOW))
      return true;

   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
   if (user_info != NULL) {
      ULONG_T dataset = user_info->get_DataSet();
      if (dataset < MAX_DATASETS && _DataSets[dataset] != NULL) {
         if (dataset > 0) {
            return true;
         }
      }
   }
   cMapping * mapping = _VarDef->_Mapping;
   if (mapping == NULL) throw cError(VARIABLE_NO_MAPPING, 0, _VarDef->_VarName.c_str(),
                                     cConvUtils::StringValue(pos).c_str());
   MAP_ITEM_T * map_item = mapping->MapItem(pos);
   if (map_item == NULL) throw cError(VARIABLE_NO_MAP_ITEM, 0, _VarDef->_VarName.c_str(),
                                      cConvUtils::StringValue(pos).c_str());
   CONST_STRING_T buf_spec = map_item->buf_spec;
   ULONG_T size = map_item->size;
   cDevice * device = map_item->device;
   if (device == NULL) throw cError(VARIABLE_NO_DEVICE, 0, _VarDef->_VarName.c_str(),
                                    cConvUtils::StringValue(pos).c_str());
   UCHAR_T data_type = _VarDef->_DataType;
   UCHAR_T map_data_type = map_item->data_type;
   ULONG_T address = map_item->address;
   CONST_STRING_T name = map_item->name;
   if (address == (ULONG_T)UNDEFINED_SYMBOL_VALUE && name == NULL) {
      throw cError(VARIABLE_NULL_MAPPING, 0, _VarDef->_VarName.c_str(),
                   cConvUtils::StringValue(pos).c_str());
   }
#ifdef SYNC_DEVICE_PARAMETERS
   if (FilterInternalDataSet(device, buf_spec, name)) {
      return true;
   }
#endif
   UCHAR_T bit_pos_b = map_item->bit_pos_b;
   UCHAR_T bit_pos_e = map_item->bit_pos_e;
   if (bit_pos_b == UNUSED_BITPOS) {
      if (address == UNUSED_ADDRESS) {
         return SetDevice(pos, device, buf_spec, name, map_data_type, size, flags);
      } else {
         return SetDevice(pos, device, buf_spec, address, map_data_type, size, flags);
      }
   } else {
      if (address == UNUSED_ADDRESS) {
         CONST_STRING_T name = map_item->name;
         return SetDevice(pos, device, buf_spec, name, map_data_type, bit_pos_b, bit_pos_e, flags);
      } else {
         return SetDevice(pos, device, buf_spec, address, map_data_type, bit_pos_b, bit_pos_e, flags);
      }
   }
#else
   return true;
#endif
  //## end cLocalVariable::SetDevice%1071317837.body
}

BOOL_T cLocalVariable::SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, ULONG_T size, ULONG_T flags)
{
  //## begin cLocalVariable::SetDevice%1075491276.body preserve=yes
   StoreIndices(pos);
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         Accu()->Get(value);
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, address, value, flags);
      }
      return true;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = 0;
            Accu()->Get(fvalue);
#ifdef ENABLE_UNITS
            cUnitDef * unit_def = _VarDef->get_UnitDef();
            if (unit_def != NULL) {
               UCHAR_T act_state = GetInputState(pos);
               UCHAR_T device_state = unit_def->get_DeviceState();
               if (act_state != device_state) {
                  ConvertToDevice(unit_def, fvalue, act_state, pos);
               }
            }
#endif
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (USHORT_T)Round(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = 0;
            Accu()->Get(fvalue);
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (USHORT_T)Round(fvalue);
         } else {
            Accu()->Get(value);
         }
#else
         Accu()->Get(value);
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, address, value, flags);
      }
      return true;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = 0;
            Accu()->Get(fvalue);
#ifdef ENABLE_UNITS
            cUnitDef * unit_def = _VarDef->get_UnitDef();
            if (unit_def != NULL) {
               UCHAR_T act_state = GetInputState(pos);
               UCHAR_T device_state = unit_def->get_DeviceState();
               if (act_state != device_state) {
                  ConvertToDevice(unit_def, fvalue, act_state, pos);
               }
            }
#endif            
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (ULONG_T)Round(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = 0;
            Accu()->Get(fvalue);
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (ULONG_T)Round(fvalue);
         } else {
            Accu()->Get(value);
         }
#else
         Accu()->Get(value);
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, address, value, flags);
      }
      return true;
   case SH_FLOAT:
      {
         FLOAT_T value = 0;
         Accu()->Get(value);
#ifdef ENABLE_UNITS
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            UCHAR_T act_state = GetInputState(pos);
            UCHAR_T device_state = unit_def->get_DeviceState();
            if (act_state != device_state) {
               ConvertToDevice(unit_def, value, act_state, pos);
            }
		   }
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, address, value, flags);
      }
      return true;
   case SH_DOUBLE:
      {
         DOUBLE_T value = 0;
         Accu()->Get(value);
#ifdef ENABLE_UNITS
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            UCHAR_T act_state = GetInputState(pos);
            UCHAR_T device_state = unit_def->get_DeviceState();
            if (act_state != device_state) {
               ConvertToDevice(unit_def, value, act_state, pos);
            }
		   }
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, address, value, flags);
      }
      return true;
   case SH_BYTE:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         device->Write(buf_spec, address, size, buf, flags);
      }
      return true;
   case SH_STRING:
      {
         STRING_T value;
         Accu()->Get(value, MAX_PRECISION);
// PR 03.07.2004 using write operation instead of set
         cBlockBuffer block_buffer;
         BUF_T buf = (BUF_T)block_buffer.AllocBlock(size + sizeof(CHAR_T));
         if (buf != NULL) {
            ULONG_T nwrite = _MIN_(size, value.size());
            memcpy(buf, value.c_str(), nwrite);
            device->Write(buf_spec, address, size, buf, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
      }
      return true;
   case SH_WSTRING:
      {
         WSTRING_T value;
         Accu()->Get(value, MAX_PRECISION);
// PR 03.07.2004 using write operation instead of set
         cBlockBuffer block_buffer;
         BUF_T buf = (BUF_T)block_buffer.AllocBlock(size + sizeof(WCHAR_T));
         if (buf != NULL) {
            ULONG_T nwrite = _MIN_(size, value.size());
            memcpy(buf, value.c_str(), nwrite);
            device->Write(buf_spec, address, size, buf, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
      }
      return true;
   case SH_OBJECT:
      {
      }
      return false;
   }
_ASSERT_UNCOND
   return false;
  //## end cLocalVariable::SetDevice%1075491276.body
}

BOOL_T cLocalVariable::SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, ULONG_T size, ULONG_T flags)
{
  //## begin cLocalVariable::SetDevice%1075491277.body preserve=yes
   StoreIndices(pos);
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T value = 0;
         Accu()->Get(value);
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, name, value, flags);
      }
      return true;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T value = 0;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = 0;
            Accu()->Get(fvalue);
#ifdef ENABLE_UNITS
            cUnitDef * unit_def = _VarDef->get_UnitDef();
            if (unit_def != NULL) {
               UCHAR_T act_state = GetInputState(pos);
               UCHAR_T device_state = unit_def->get_DeviceState();
               if (act_state != device_state) {
                  ConvertToDevice(unit_def, fvalue, act_state, pos);
               }
            }
#endif
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (USHORT_T)Round(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = 0;
            Accu()->Get(fvalue);
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (USHORT_T)Round(fvalue);
         } else {
            Accu()->Get(value);
         }
#else
         Accu()->Get(value);
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, name, value, flags);
      }
      return true;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T value = 0;
#ifdef ENABLE_REAL_TO_FIXED_DECIMAL_MAPPING
         UCHAR_T var_data_type = _VarDef->_DataType;
         UCHAR_T dev_precision = 0;
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            dev_precision = mapping->_Precision;
         }
         // compatibility mode for earlier versions
         if (_VarDef->get_UnitDef() == NULL &&
             dev_precision == 0) {
            dev_precision = _VarDef->_Precision;
         }
         if (var_data_type == SH_FLOAT) {
            FLOAT_T fvalue = 0;
            Accu()->Get(fvalue);
#ifdef ENABLE_UNITS
            cUnitDef * unit_def = _VarDef->get_UnitDef();
            if (unit_def != NULL) {
               UCHAR_T act_state = GetInputState(pos);
               UCHAR_T device_state = unit_def->get_DeviceState();
               if (act_state != device_state) {
                  ConvertToDevice(unit_def, fvalue, act_state, pos);
               }
            }
#endif
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (ULONG_T)Round(fvalue);
         } else if (var_data_type == SH_DOUBLE) {
            DOUBLE_T fvalue = 0;
            Accu()->Get(fvalue);
            for (int i=0; i<dev_precision; i++) {
               fvalue *= 10;
            }
            value = (ULONG_T)Round(fvalue);
         } else {
            Accu()->Get(value);
         }
#else
         Accu()->Get(value);
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, name, value, flags);
      }
      return true;
   case SH_FLOAT:
      {
         FLOAT_T value = 0;
         Accu()->Get(value);
#ifdef ENABLE_UNITS
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            UCHAR_T act_state = GetInputState(pos);
            UCHAR_T device_state = unit_def->get_DeviceState();
            if (act_state != device_state) {
               ConvertToDevice(unit_def, value, act_state, pos);
            }
		   }
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, name, value, flags);
      }
      return true;
   case SH_DOUBLE:
      {
         DOUBLE_T value = 0;
         Accu()->Get(value);
#ifdef ENABLE_UNITS
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            UCHAR_T act_state = GetInputState(pos);
            UCHAR_T device_state = unit_def->get_DeviceState();
            if (act_state != device_state) {
               ConvertToDevice(unit_def, value, act_state, pos);
            }
		   }
#endif
         device->Cast(buf_spec, data_type, value);
         device->Set(buf_spec, name, value, flags);
      }
      return true;
   case SH_BYTE:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         device->Write(buf_spec, name, size, buf, flags);
      }
      return true;
   case SH_STRING:
      {
         STRING_T value;
         Accu()->Get(value, MAX_PRECISION);
// PR 03.02.2012 using write operation instead of set
         cBlockBuffer block_buffer;
         BUF_T buf = (BUF_T)block_buffer.AllocBlock(size + sizeof(CHAR_T));
         if (buf != NULL) {
            ULONG_T nwrite = _MIN_(size, value.size());
            memcpy(buf, value.c_str(), nwrite);
            device->Write(buf_spec, name, size, buf, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
/*
         STRING_T value;
         Accu()->Get(value, MAX_PRECISION);
         device->Set(buf_spec, name, value.c_str(), flags);
*/
      }
      return true;
   case SH_WSTRING:
      {
         WSTRING_T value;
         Accu()->Get(value, MAX_PRECISION);
// PR 03.02.2012 using write operation instead of set
         cBlockBuffer block_buffer;
         BUF_T buf = (BUF_T)block_buffer.AllocBlock(size + sizeof(WCHAR_T));
         if (buf != NULL) {
            ULONG_T nwrite = _MIN_(size, value.size());
            memcpy(buf, value.c_str(), nwrite);
            device->Write(buf_spec, name, size, buf, flags);
         } else {
            throw cError(NO_BUFFER_FOR_BLOB_DATA, 0, _VarDef->_VarName.c_str());
         }
/*
         WSTRING_T value;
         Accu()->Get(value, MAX_PRECISION);
         device->Set(buf_spec, name, value.c_str(), flags);
*/
      }
      return true;
   case SH_OBJECT:
      {
         BUF_T buf = NULL;
         Accu()->Get(buf);
         device->Write(buf_spec, name, size, buf, flags);
      }
      return true;
   }
_ASSERT_UNCOND
   return false;
  //## end cLocalVariable::SetDevice%1075491277.body
}

BOOL_T cLocalVariable::SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags)
{
  //## begin cLocalVariable::SetDevice%1075491278.body preserve=yes
   StoreIndices(pos);
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         UCHAR_T value = 0;
         UCHAR_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, address, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, address, dev_value, flags);
      }
      return true;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         USHORT_T value = 0;
         USHORT_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, address, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, address, dev_value, flags);
      }
      return true;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         ULONG_T value = 0;
         ULONG_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, address, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, address, dev_value, flags);
      }
      return true;
   case SH_OBJECT:
      {
      }
      return false;
   }
_ASSERT_UNCOND
   return false;
  //## end cLocalVariable::SetDevice%1075491278.body
}

BOOL_T cLocalVariable::SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags)
{
  //## begin cLocalVariable::SetDevice%1075491279.body preserve=yes
   StoreIndices(pos);
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         UCHAR_T value = 0;
         UCHAR_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, name, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, name, dev_value, flags);
      }
      return true;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         USHORT_T value = 0;
         USHORT_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, name, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, name, dev_value, flags);
      }
      return true;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         cObjectLock __lock__(&device->_DeviceMutex);
         ULONG_T value = 0;
         ULONG_T dev_value = 0;
         Accu()->Get(value);
         device->Get(buf_spec, name, dev_value, flags);
         device->SetPattern(buf_spec, data_type, dev_value, bit_pos_b, bit_pos_e, value, flags);
         device->Set(buf_spec, name, dev_value, flags);
      }
      return true;
   case SH_OBJECT:
      {
      }
      return false;
   }
_ASSERT_UNCOND
   return false;
  //## end cLocalVariable::SetDevice%1075491279.body
}

void cLocalVariable::Save (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Save%1071741889.body preserve=yes
   if (_VarDef->_Mapping == NULL) return;
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
/// PR 03.07.06 - at this point the pointer to the buffer inthe Accu()
///               may be invalid (NULL) or may point to an invalid buffer
///               the inserted lines will reset the Accu() to the right buffer
/// >>>
   if (_VarDef->DataType() == SH_BYTE) {
      BUF_T buf = NULL;
      GetBuffer(pos, buf);
      Accu()->Set(buf);
   }
/// <<<
   GetDevice(pos, flags);
   ReadConversion(pos, 0);
#ifdef ENABLE_UNITS   
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      SetInputState(pos, unit_def->get_DeviceState());
   }
#endif
   if (SetBuffer(pos) || flags & VF_FORCE_EVENT) {
      DataChanged(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::Save%1071741889.body
}

void cLocalVariable::SaveVariable (ULONG_T flags)
{
  //## begin cLocalVariable::SaveVariable%1084445991.body preserve=yes
   ULONG_T elements = _VarDef->Elements();
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   for (ULONG_T i=0; i<elements; i++) {
      _VarDef->GetIndices(i, i1, i2, i3, i4);
      Save(i1, i2, i3, i4, flags);
   }
  //## end cLocalVariable::SaveVariable%1084445991.body
}

void cLocalVariable::Load (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::Load%1071741890.body preserve=yes
   cMapping * mapping = _VarDef->_Mapping;
   if (mapping == NULL) {
      /// avoid to load unmapped variables
      return;
   }
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   MAP_ITEM_T * map_item = mapping->MapItem(pos);
   if (map_item == NULL) {
      /// avoid to load unmapped items
      return;
   } else {
      ULONG_T address = map_item->address;
      CONST_STRING_T name = map_item->name;
      if (address == (ULONG_T)UNDEFINED_SYMBOL_VALUE && name == NULL) {
         /// avoid to load unmapped items
         return;
      }
   }
#ifdef SYNC_DEVICE_PARAMETERS
   if (!_Context->IsRemote()) {
      cLocalContext * local_context = (cLocalContext*)_Context;
      if (local_context->get_RunFlags() & RF_BBRAM_INITIALIZED) {
         if (strcmp(map_item->buf_spec, "parameter") == 0) {
            GetDevice(pos);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
               SetDevice(pos, flags);
            }
            return;
         }
      }
   }
#endif
   /// PR 15.11.05 generally switch to foreground to avoid sending background data to the device
   ///             even when user works in background (RM rounding fix, but no rounding problem)
   SELECT_DATASET(VF_FOREGROUND);
   if (_LimitChecker != NULL) {
      _LimitChecker->CheckLimits(this, i1, i2, i3, i4);
   }
   GetBuffer(pos);
   WriteConversion(pos, 0);
   SetDevice(pos);
  //## end cLocalVariable::Load%1071741890.body
}

void cLocalVariable::LoadVariable (ULONG_T flags)
{
  //## begin cLocalVariable::LoadVariable%1084445992.body preserve=yes
   cMapping * mapping = _VarDef->_Mapping;
   if (mapping == NULL) {
      /// avoid to load unmapped variables
      return;
   }
   ULONG_T elements = _VarDef->Elements();
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   for (ULONG_T i=0; i<elements; i++) {
      _VarDef->GetIndices(i, i1, i2, i3, i4);
      Load(i1, i2, i3, i4);
   }
  //## end cLocalVariable::LoadVariable%1084445992.body
}

BUF_T cLocalVariable::GetBuf ()
{
  //## begin cLocalVariable::GetBuf%1077613262.body preserve=yes
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      return NULL;
   } else {
      return _Values->GetBuf();
   }
  //## end cLocalVariable::GetBuf%1077613262.body
}

ULONG_T cLocalVariable::GetBufSize ()
{
  //## begin cLocalVariable::GetBufSize%1077613263.body preserve=yes
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      return 0;
   } else {
      return _Values->GetBufSize();
   }
  //## end cLocalVariable::GetBufSize%1077613263.body
}

BOOL_T cLocalVariable::GetMemoryType (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::GetMemoryType%1092208311.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      if (data_type == SH_OBJECT) {
         BUF_T buffer = NULL;
         ULONG_T size = 0;
         Get(buffer, size, i1, i2, i3, i4, flags);
         cConvUtils::Buf2String(value, buffer, size);
         return true;
      }
      ULONG_T size = ValueSize();
      BUF_T buf = NULL;
      Get(buf, i1, i2, i3, i4, flags);
      if (buf != NULL) {
         if (flags & VF_MEMORY_ACCESS) {
            cConvUtils::Ptr2String(value, buf);
         } else {
            cConvUtils::Buf2String(value, buf, size);
         }
      }
      return true; 
   } else if (data_type == SH_WSTRING) {
      ULONG_T size = ValueSize();
      BUF_T buf = NULL;
      Get(buf, i1, i2, i3, i4, flags);
      if (buf != NULL) {
         cConvUtils::Buf2String(value, buf, size);
      }
      return true; 
   }
   return false;
  //## end cLocalVariable::GetMemoryType%1092208311.body
}

BOOL_T cLocalVariable::SetMemoryType (CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::SetMemoryType%1092208312.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      if (data_type == SH_OBJECT) {
         ULONG_T bufSize = cConvUtils::BCDBufSize(strlen(value));
         BUF_T buffer = (BUF_T)cSystemUtils::Alloc(bufSize);
         cConvUtils::String2Buf(value, buffer, bufSize);
         Set(buffer, bufSize, i1, i2, i3, i4, flags);
         cSystemUtils::Free(buffer);
         return true;
      }
      ULONG_T size = ValueSize();
      BUF_T buf = (BUF_T)cSystemUtils::Alloc(size);
      cConvUtils::String2Buf(value, buf, size);
      Set(buf, size, i1, i2, i3, i4, flags);
      cSystemUtils::Free(buf);
      return true; 
   } else if (data_type == SH_WSTRING ||
              data_type == SH_STRING) {
      ULONG_T size = ValueSize();
      BUF_T buf = (BUF_T)cSystemUtils::Alloc(size+1);
      ULONG_T conv_len = cConvUtils::String2Buf(value, buf, size);
      if (conv_len > 0) {
         Set((const char *)buf, i1, i2, i3, i4, flags);
         cSystemUtils::Free(buf);
         return true;
      } else {
         cSystemUtils::Free(buf);
         return false; 
      }
   }
   return false;
  //## end cLocalVariable::SetMemoryType%1092208312.body
}

void cLocalVariable::CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags)
{
  //## begin cLocalVariable::CopyCommand%1100714614.body preserve=yes

   // if exchanging with foreground, then always make the foreground the destination
   if ((exchange) && (src == FOREGROUND_DATASET)) {
      src = dst;
      dst = FOREGROUND_DATASET;
   }

   void * src_ptr = NULL;
   void * dst_ptr = NULL;
   cValueBuffer * src_buf = NULL;
   cValueBuffer * dst_buf = NULL;
   if ((src < MAX_DATASETS) && (dst < MAX_DATASETS)) {
      src_buf = _DataSets[src];
      dst_buf = _DataSets[dst];
   } else {
      return;
   }

   if (src_buf == NULL || dst_buf == NULL) {
      return;
   }

   if (exchange) {
      ULONG_T size = dst_buf->GetBufSize();
      ULONG_T diff_flag = 0;
      src_ptr = src_buf->GetBuf();
      dst_ptr = dst_buf->GetBuf();
      void * buf = cSystemUtils::Alloc(size);
      void * state_buf = cSystemUtils::Alloc(STATEBUF_SIZE);
      if (src_ptr != NULL && dst_ptr != NULL && buf != NULL && state_buf != NULL) {
         if (memcmp(dst_ptr, src_ptr, size) != 0) {
            memcpy(buf, dst_ptr, size);// copy the destination to a temp buffer
            if (dst != FOREGROUND_DATASET) {
               memcpy(dst_ptr, src_ptr, size);
               memcpy(src_ptr, buf, size);
            }
            else {
               diff_flag = 1;
            }
         }
         // PR 9.5.05 also transfer input states
         if (_InputStates[src] != NULL && _InputStates[dst] != NULL) {
            if (memcmp(_InputStates[dst], _InputStates[src], STATEBUF_SIZE) != 0) {
               memcpy(state_buf, _InputStates[dst], STATEBUF_SIZE);
               if (dst != FOREGROUND_DATASET) {
                  memcpy(_InputStates[dst], _InputStates[src], STATEBUF_SIZE);
                  memcpy(_InputStates[src], state_buf, STATEBUF_SIZE);
               }
               else {
                  diff_flag |= 2;
               }
            }
         }

         if (diff_flag) {
            ULONG_T source_dataset_flag = 0;
            if (src == BACKGROUND_DATASET) {
               source_dataset_flag = VF_BACKGROUND;
            }
            else if (src == SHADOW_DATASET) {
               source_dataset_flag = VF_SHADOW;
            }

            ULONG_T elements = _VarDef->Elements();
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            for (ULONG_T i = 0; i<elements; i++) {
               _VarDef->GetIndices(i, i1, i2, i3, i4);
               STRING_T new_value, current_value;
               Get(new_value, i1, i2, i3, i4, source_dataset_flag);
               Get(current_value, i1, i2, i3, i4);
               if (new_value != current_value) {
                  Set(new_value.c_str(), i1, i2, i3, i4);
               }
            }
            memcpy(dst_ptr, src_ptr, size);
            memcpy(src_ptr, buf, size);
            if (diff_flag & 2) {
               memcpy(_InputStates[dst], _InputStates[src], STATEBUF_SIZE);
               memcpy(_InputStates[src], state_buf, STATEBUF_SIZE);
            }

            LoadVariable();
            Persist();
         }
      }
      if (buf != NULL) {
         cSystemUtils::Free(buf);
      }
      if (state_buf != NULL) {
         cSystemUtils::Free(state_buf);
      }
   } else {
      ULONG_T size = dst_buf->GetBufSize();
      src_ptr = src_buf->GetBuf();
      dst_ptr = dst_buf->GetBuf();
      if (src_ptr != NULL && dst_ptr != NULL) {
         if (dst == FOREGROUND_DATASET) {
            ULONG_T diff_flag = 0;
            if (memcmp(dst_ptr, src_ptr, size) != 0) diff_flag = 1;
            if (_InputStates[src] != NULL && _InputStates[dst] != NULL) {
               if (memcmp(_InputStates[dst], _InputStates[src], STATEBUF_SIZE) != 0) {
                  diff_flag |= 2;
               }
            }
            if (diff_flag) {
               ULONG_T source_dataset_flag = 0;
               if (src == BACKGROUND_DATASET) {
                  source_dataset_flag = VF_BACKGROUND;
               }
               else if (src == SHADOW_DATASET) {
                  source_dataset_flag = VF_SHADOW;
               }

               ULONG_T elements = _VarDef->Elements();
               LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
               for (ULONG_T i = 0; i<elements; i++) {
                  _VarDef->GetIndices(i, i1, i2, i3, i4);
                  STRING_T value;
                  Get(value, i1, i2, i3, i4, source_dataset_flag);
                  Set(value.c_str(), i1, i2, i3, i4);
               }
               LoadVariable();
            }
         }
         else {
            memcpy(dst_ptr, src_ptr, size);
            // PR 9.5.05 also transfer input states
            if (_InputStates[src] != NULL && _InputStates[dst] != NULL) {
               memcpy(_InputStates[dst], _InputStates[src], STATEBUF_SIZE);
            }
         }
         Persist();
      }
   }
  //## end cLocalVariable::CopyCommand%1100714614.body
}

BOOL_T cLocalVariable::Compare (STRING_T &result, ULONG_T flags)
{
  //## begin cLocalVariable::Compare%1108566003.body preserve=yes
   STRING_T var_name = _VarDef->_VarName;
   STRING_T fg_value;
   STRING_T bg_value;
   long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   long i1_max = -1, i2_max = -1, i3_max = -1, i4_max = -1;
   ULONG_T dims = _VarDef->Dims();
   switch (dims) {
   case 1:
      i1_max = _VarDef->DimSize(0);
      break;
   case 2:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      break;
   case 3:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      i3_max = _VarDef->DimSize(2);
      break;
   case 4:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      i3_max = _VarDef->DimSize(2);
      i4_max = _VarDef->DimSize(3);
      break;
   }
   BOOL_T difference = false;
/// PR 20.07.06 temporarily until solved dynamic
///   char buf[0x2000] = {0};
static char buf[0x8000] = {0};
memset(buf, 0, sizeof(buf));
   
   BOOL_T compare_to_shadow = false;
   if (flags & CF_COMPARE_TO_SHADOW) {
      if (!cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
         return false;
      } else {
         if (_VarDef->_FileName == "Ignore") {
            return false;
         }
         compare_to_shadow = true;
      }
   }
   ULONG_T src_flags = VF_FOREGROUND|VF_BUFFERED;
   ULONG_T dst_flags = VF_BACKGROUND|VF_BUFFERED;
   if (compare_to_shadow) {
      dst_flags = VF_SHADOW|VF_BUFFERED;
   }
   if (dims == 0) {
     Get(bg_value, i1, i2, i3, i4, dst_flags);
     Get(fg_value, i1, i2, i3, i4, src_flags);
     if (strcmp(fg_value.c_str(), bg_value.c_str()) != 0) {
        SafePrintf(buf, sizeof(buf), "%s(\"%s\",\"%s\")\n", var_name.c_str(), fg_value.c_str(), bg_value.c_str());
        difference = true;
        result += buf;
     }
   } else if (dims == 1) {
      for (i1=0; i1<i1_max; i1++) {
         Get(bg_value, i1, i2, i3, i4, dst_flags);
         Get(fg_value, i1, i2, i3, i4, src_flags);
         if (strcmp(fg_value.c_str(), bg_value.c_str()) != 0) {
            SafePrintf(buf, sizeof(buf), "%s[%d](\"%s\",\"%s\")\n", var_name.c_str(), i1, fg_value.c_str(), bg_value.c_str());
            difference = true;
            result += buf;
         }
      }
   } else if (dims == 2) {
      for (i1=0; i1<i1_max; i1++) {
         for (i2=0; i2<i2_max; i2++) {
            Get(bg_value, i1, i2, i3, i4, dst_flags);
            Get(fg_value, i1, i2, i3, i4, src_flags);
            if (strcmp(fg_value.c_str(), bg_value.c_str()) != 0) {
               SafePrintf(buf, sizeof(buf), "%s[%d][%d](\"%s\",\"%s\")\n", var_name.c_str(), i1, i2, fg_value.c_str(), bg_value.c_str());
               difference = true;
               result += buf;
            }
         }
      }
   } else if (dims == 3) {
      for (i1=0; i1<i1_max; i1++) {
         for (i2=0; i2<i2_max; i2++) {
            for (i3=0; i3<i3_max; i3++) {
               Get(bg_value, i1, i2, i3, i4, dst_flags);
               Get(fg_value, i1, i2, i3, i4, src_flags);
               if (strcmp(fg_value.c_str(), bg_value.c_str()) != 0) {
                  SafePrintf(buf, sizeof(buf), "%s[%d][%d][%d](\"%s\",\"%s\")\n", var_name.c_str(), i1, i2, i3, fg_value.c_str(), bg_value.c_str());
                  difference = true;
                  result += buf;
               }
            }
         }
      }
   } else if (dims == 4) {
      for (i1=0; i1<i1_max; i1++) {
         for (i2=0; i2<i2_max; i2++) {
            for (i3=0; i3<i3_max; i3++) {
               for (i4=0; i4<i4_max; i4++) {
                  Get(bg_value, i1, i2, i3, i4, dst_flags);
                  Get(fg_value, i1, i2, i3, i4, src_flags);
                  if (strcmp(fg_value.c_str(), bg_value.c_str()) != 0) {
                     SafePrintf(buf, sizeof(buf), "%s[%d][%d][%d][%d](\"%s\",\"%s\")\n", var_name.c_str(), i1, i2, i3, i4, fg_value.c_str(), bg_value.c_str());
                     difference = true;
                     result += buf;
                  }
               }
            }
         }
      }
   }
   return difference;
  //## end cLocalVariable::Compare%1108566003.body
}

void cLocalVariable::SetInput (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::SetInput%1111256533.body preserve=yes
#ifdef ENABLE_UNITS
   if (flags & VF_NATIVE_REPRESENTATION) {
      SetInputState(pos, (CHAR_T)0);
   } else if (flags & VF_DEVICE_REPRESENTATION) {
      cUnitDef * unit_def = _VarDef->get_UnitDef();
      if (unit_def != NULL) {
         SetInputState(pos, (CHAR_T)unit_def->get_DeviceState());
      }
   } else if (flags & VF_DATASET_REPRESENTATION) {
      cUnitDef * unit_def = _VarDef->get_UnitDef();
      if (unit_def != NULL) {
         SetInputState(pos, (CHAR_T)unit_def->get_DatasetState());
      }
   } else {
      cUnitDef * unit_def = _VarDef->get_UnitDef();
      if (unit_def != NULL) {
         UCHAR_T input_state = unit_def->GetState();
         SetInputState(pos, input_state);
      }
   }
#endif
  //## end cLocalVariable::SetInput%1111256533.body
}

void cLocalVariable::SetInputState (ULONG_T pos, CHAR_T value)
{
  //## begin cLocalVariable::SetInputState%1111243134.body preserve=yes
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      if (_States != NULL) {
         if (pos < _VarDef->Elements()) {
            _States[pos] = value;
         }
      }
   }
#endif
  //## end cLocalVariable::SetInputState%1111243134.body
}

UCHAR_T cLocalVariable::GetInputState (ULONG_T pos)
{
  //## begin cLocalVariable::GetInputState%1111243135.body preserve=yes
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      if (_States != NULL) {
         if (pos < _VarDef->Elements()) {
            return _States[pos];
         }
      }
   }
#endif
   return 0;
  //## end cLocalVariable::GetInputState%1111243135.body
}

void cLocalVariable::HandleUnit (STRING_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::HandleUnit%1111243132.body preserve=yes
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def == NULL) {
      return;
   }
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_FLOAT:
      {
         if (unit_def != NULL) {
            FLOAT_T fval = (FLOAT_T)atof(value.c_str());
            if (flags & VF_NATIVE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(0);
               ConvertToNative(unit_def, fval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, fval, precision);
            } else if (flags & VF_DEVICE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DeviceState());
               ConvertToDevice(unit_def, fval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, fval, precision);
            } else if (flags & VF_DATASET_REPRESENTATION) {
               ConvertToDataset(unit_def, fval, GetInputState(pos), pos);
               /// PR 15.11.05 store values in full precision (RM rounding fix)
               ///cSHVariant::Double2String(value, fval, precision);
               char buf[64] = {0};
               SafePrintf(buf, sizeof(buf), "%f", fval);
               value = buf;
            } else {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision();
               ConvertToState(unit_def, fval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, fval, precision);
            }
         }
      }
      break;
   case SH_DOUBLE:
      {
         if (unit_def != NULL) {
            DOUBLE_T dval = atof(value.c_str());
            if (flags & VF_NATIVE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(0);
               ConvertToNative(unit_def, dval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, dval, precision);
            } else if (flags & VF_DEVICE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DeviceState());
               ConvertToDevice(unit_def, dval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, dval, precision);
            } else if (flags & VF_DATASET_REPRESENTATION) {
               ConvertToDataset(unit_def, dval, GetInputState(pos), pos);
               /// PR 15.11.05 store values in full precision (RM rounding fix)
               ///cSHVariant::Double2String(value, dval, precision);
               char buf[64] = {0};
               SafePrintf(buf, sizeof(buf), "%f", dval);
               value = buf;
            } else {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision();
               ConvertToState(unit_def, dval, GetInputState(pos), pos);
               cSHVariant::Double2String(value, dval, precision);
            }
         }
      }
      break;
   }
#endif
  //## end cLocalVariable::HandleUnit%1111243132.body
}

void cLocalVariable::HandleUnit (FLOAT_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::HandleUnit%1111256534.body preserve=yes
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def == NULL) {
      return;
   }
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_FLOAT:
   case SH_DOUBLE:
      {
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            if (flags & VF_NATIVE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(0);
               ConvertToNative(unit_def, value, GetInputState(pos), pos);
            } else if (flags & VF_DEVICE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DeviceState());
               ConvertToDevice(unit_def, value, GetInputState(pos), pos);
            } else if (flags & VF_DATASET_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DatasetState());
               ConvertToDataset(unit_def, value, GetInputState(pos), pos);
            } else {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision();
               ConvertToState(unit_def, value, GetInputState(pos), pos);
            }
         }
      }
      break;
   }
#endif
  //## end cLocalVariable::HandleUnit%1111256534.body
}

void cLocalVariable::HandleUnit (DOUBLE_T &value, ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::HandleUnit%1111388587.body preserve=yes
#ifdef ENABLE_UNITS
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def == NULL) {
      return;
   }
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_FLOAT:
      {
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            FLOAT_T fval = (FLOAT_T)value;
            if (flags & VF_NATIVE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(0);
               ConvertToNative(unit_def, fval, GetInputState(pos), pos);
               value = (DOUBLE_T)fval;
            } else if (flags & VF_DEVICE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DeviceState());
               ConvertToDevice(unit_def, fval, GetInputState(pos), pos);
               value = (DOUBLE_T)fval;
            } else if (flags & VF_DATASET_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DatasetState());
               ConvertToDataset(unit_def, fval, GetInputState(pos), pos);
               value = (DOUBLE_T)fval;
            } else {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision();
               ConvertToState(unit_def, fval, GetInputState(pos), pos);
               value = (DOUBLE_T)fval;
            }
         }
      }
      break;
   case SH_DOUBLE:
      {
         cUnitDef * unit_def = _VarDef->get_UnitDef();
         if (unit_def != NULL) {
            if (flags & VF_NATIVE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(0);
               ConvertToNative(unit_def, value, GetInputState(pos), pos);
            } else if (flags & VF_DEVICE_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DeviceState());
               ConvertToDevice(unit_def, value, GetInputState(pos), pos);
            } else if (flags & VF_DATASET_REPRESENTATION) {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision(unit_def->get_DatasetState());
               ConvertToDataset(unit_def, value, GetInputState(pos), pos);
            } else {
               UCHAR_T precision = _VarDef->_Precision = unit_def->Precision();
               ConvertToState(unit_def, value, GetInputState(pos), pos);
            }
         }
      }
      break;
   }
#endif
  //## end cLocalVariable::HandleUnit%1111388587.body
}

void cLocalVariable::ConvertToNative (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToNative%1111388586.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, 0);
  //## end cLocalVariable::ConvertToNative%1111388586.body
}

void cLocalVariable::ConvertToNative (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToNative%1126246271.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, 0);
  //## end cLocalVariable::ConvertToNative%1126246271.body
}

void cLocalVariable::ConvertToDevice (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToDevice%1111426863.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, unit_def->get_DeviceState());
  //## end cLocalVariable::ConvertToDevice%1111426863.body
}

void cLocalVariable::ConvertToDevice (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToDevice%1126246272.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, unit_def->get_DeviceState());
  //## end cLocalVariable::ConvertToDevice%1126246272.body
}

void cLocalVariable::ConvertToDataset (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToDataset%1111388584.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, unit_def->get_DatasetState());
  //## end cLocalVariable::ConvertToDataset%1111388584.body
}

void cLocalVariable::ConvertToDataset (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToDataset%1126246273.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source, unit_def->get_DatasetState());
  //## end cLocalVariable::ConvertToDataset%1126246273.body
}

void cLocalVariable::ConvertToState (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToState%1111388585.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source);
  //## end cLocalVariable::ConvertToState%1111388585.body
}

void cLocalVariable::ConvertToState (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos)
{
  //## begin cLocalVariable::ConvertToState%1126246274.body preserve=yes
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   _VarDef->GetIndices(pos, i1, i2, i3, i4);
   unit_def->GetValue(value, i1, i2, i3, i4, source);
  //## end cLocalVariable::ConvertToState%1126246274.body
}

BOOL_T cLocalVariable::ReadAccessFilter (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::ReadAccessFilter%1133185466.body preserve=yes
   if (_AccessFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
// PR 24.11.04 first load Accu() from buffer
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
            return true;
         }
		   break;
      case SH_STRING:
         {
#ifdef old_and_unpreferred_version
            STRING_T value;
            GetBuffer(pos);
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, 0);
            Accu()->Set(value.c_str());
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
#else
            STRING_T value;
            STRING_T old_value;
            GetBuffer(pos);
            Accu()->Get(old_value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, old_value.c_str(), i1, i2, i3, i4, 0);
            Accu()->Set(value.c_str());
            if (SetBuffer(pos)) {
               DataChanged(old_value.c_str(), value.c_str(), i1, i2, i3, i4, flags);
            }
#endif
            return true;
         }
         break;
      case SH_BYTE:
      case SH_WSTRING:
      case SH_OBJECT:
         break;
      }
   }
   return false;
  //## end cLocalVariable::ReadAccessFilter%1133185466.body
}

BOOL_T cLocalVariable::WriteAccessFilter (ULONG_T pos, ULONG_T flags)
{
  //## begin cLocalVariable::WriteAccessFilter%1133185467.body preserve=yes
   if (_AccessFuncRef != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            Accu()->Get(value);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value);
/* PR 07.07.05 not necessary and prevents subordinate handling of units
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
*/
            return true;
         }
		   break;
      case SH_STRING:
         {
#ifdef old_and_unpreferred_version
            STRING_T value;
            Accu()->Get(value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value.c_str());
#else
            STRING_T value;
            Accu()->Get(value, MAX_PRECISION);
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            _VarDef->GetIndices(pos, i1, i2, i3, i4);
            _AccessFuncRef->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, VF_WRITE);
            Accu()->Set(value.c_str());
#endif
            return true;
         }
		   break;
      case SH_BYTE:
      case SH_WSTRING:
      case SH_OBJECT:
         break;
      }
   }
   return false;
  //## end cLocalVariable::WriteAccessFilter%1133185467.body
}

void cLocalVariable::SetUnitSensitive (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, UCHAR_T state, BOOL_T suppress_data_change)
{
  //## begin cLocalVariable::Set%1191857007.body preserve=yes
   SELECT_DATASET(flags)
   CHECK_WRITE_ACCESS(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   FormatIn(value, pos, flags);
   DOUBLE_T temp_value = value;
   UCHAR_T temp_state = GetInputState(pos);
   BOOL_T has_unit_definition = (_VarDef->get_UnitDef() != NULL);
   if (has_unit_definition) {
      SetInputState(pos, state);
   }
   Accu()->Set(value);
   if (!WriteFilter(pos, flags)) {
      if (_VarDef->_VarType != SH_VAR_ACT) {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            WriteConversion(pos, flags);
            if (SetDevice(pos, flags)) {
               Accu()->Set(temp_value);
               if (SetBuffer(pos) ||
                   has_unit_definition) {
                  if (!suppress_data_change) {
                     DataChanged(i1, i2, i3, i4, flags);
                  }
               }
            } else {
               SetInputState(pos, temp_state);
            }
            return;
         }
      }
   }
   if (SetBuffer(pos) ||
       has_unit_definition) {
      if (!suppress_data_change) {
         DataChanged(i1, i2, i3, i4, flags);
      }
   }
  //## end cLocalVariable::Set%1191857007.body
}

void cLocalVariable::GetRaw (UCHAR_T &state, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::GetRaw%1191857008.body preserve=yes
   ULONG_T flags = 0;
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   state = GetInputState(pos);
   GetBuffer(pos);
   UCHAR_T data_type = DataType();
   if (data_type == SH_FLOAT ||
       data_type == SH_DOUBLE) {
      Accu()->Get(value, MAX_PRECISION);
   } else {
      UCHAR_T precision = _VarDef->_Precision;
      cUnitDef * unit_def = _VarDef->get_UnitDef();
      if (unit_def != NULL) {
         precision = unit_def->Precision(state);
      }
      Accu()->Get(value, precision);
      FormatOut(value, precision);
   }
  //## end cLocalVariable::GetRaw%1191857008.body
}

void cLocalVariable::SetUnitCode (ULONG_T pos, UCHAR_T value)
{
  //## begin cLocalVariable::SetUnitCode%1191857009.body preserve=yes
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      if (_States != NULL) {
         if (pos < _VarDef->Elements()) {
            _States[pos] = value;
         }
      }
   }
  //## end cLocalVariable::SetUnitCode%1191857009.body
}

UCHAR_T cLocalVariable::UnitCode (ULONG_T pos)
{
  //## begin cLocalVariable::UnitCode%1191857010.body preserve=yes
   UCHAR_T code = 0;
   if (_States != NULL) {
      if (pos < _VarDef->Elements()) {
         code = _States[pos];
      }
   }
   return code;
  //## end cLocalVariable::UnitCode%1191857010.body
}

void cLocalVariable::Test(int param)
{
#define SRC_   0
#define DST_   1
   if (_VarDef->_VarName != "SetStrPlstShotSize") {
      return;
   }
   void * src_ptr = NULL;
   void * dst_ptr = NULL;
   cValueBuffer * src_buf = NULL;
   cValueBuffer * dst_buf = NULL;
   src_buf = _DataSets[SRC_];
   dst_buf = _DataSets[DST_];
   ULONG_T size = dst_buf->GetBufSize();
   src_ptr = src_buf->GetBuf();
   dst_ptr = dst_buf->GetBuf();
   FLOAT_T src_val = *(FLOAT_T*)src_ptr;
   FLOAT_T dst_val = *(FLOAT_T*)dst_ptr;
   CHAR_T src_state = (_InputStates[SRC_])[0];
   CHAR_T dst_state = (_InputStates[DST_])[0];
   FLOAT_T fval = 0;
   this->Get(fval, 0);
   GetBuffer(0);
   return;
}

void cLocalVariable::Break (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::Break%1191857017.body preserve=yes
   // for debugging only
   if (_VarDef->_VarName == "SetStrInj") {
      if (i1 == 0 && i2 == 0) {
         int dummy = 0;
      }
   }
  //## end cLocalVariable::Break%1191857017.body
}

void cLocalVariable::FormatOut (STRING_T &value, UCHAR_T precision)
{
  //## begin cLocalVariable::FormatOut%1191857018.body preserve=yes
   UCHAR_T data_type = _VarDef->_DataType;
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      {
         DOUBLE_T lval = atof(value.c_str());
         for (ULONG_T i=0; i<precision; i++) {
				lval /= 10;
			}
			char value_buf[64] = {0};

            if ((precision >= 0) && (precision <= 6)) {
               SafePrintf(value_buf, sizeof(value_buf), "%.*f", precision, lval);
            }
            else {
               SafePrintf(value_buf, sizeof(value_buf), "%.lf", lval);
            }
			value = value_buf;
		}
		break;
   case SH_FLOAT:
   case SH_DOUBLE:
		if (precision > 0) {
	      char value_buf[64] = {0};
			ULONG_T len = value.size();
			memcpy(value_buf, value.c_str(), _MIN_(len, sizeof(value_buf)));
			ULONG_T i;
         for (i=0; i<len; i++) {
				if (value_buf[i] == '.') break;
			}
			i += precision + 1;
			value_buf[i] = '\0';
			value = value_buf;
      } else if (precision == 0) {
         DOUBLE_T dval = atof(value.c_str());
	      char value_buf[64] = {0};
         /// PR 15.11.05 no cast to long but restriction to 0 precision (RM rounding fix)
         ///SafePrintf(value_buf, sizeof(value_buf), "%d", (long)dval);
         SafePrintf(value_buf, sizeof(value_buf), "%.0f", dval);
         value = value_buf;
      }
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
   case SH_OBJECT:
      break;
   }
  //## end cLocalVariable::FormatOut%1191857018.body
}

void cLocalVariable::EmitChanges ()
{
  //## begin cLocalVariable::EmitChanges%1191857011.body preserve=yes
   ULONG_T data_type = _VarDef->DataType();
   ULONG_T elements = _VarDef->Elements();
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   for (ULONG_T i=0; i<elements; i++) {
      _VarDef->GetIndices(i, i1, i2, i3, i4);
      if (data_type == SH_BYTE) {
         DataChanged(i1, i2, i3, i4);
      } else if (data_type == SH_STRING ||
                 data_type == SH_WSTRING) {
         STRING_T value;
         Get(value, i1, i2, i3, i4, VF_BUFFERED);
         if (value.size() != 0) {
            DataChanged(i1, i2, i3, i4);
         }
      } else {
         DOUBLE_T value;
         Get(value, i1, i2, i3, i4, VF_BUFFERED);
         if (value != 0) {
            DataChanged(i1, i2, i3, i4);
         }
      }
   }
  //## end cLocalVariable::EmitChanges%1191857011.body
}

void cLocalVariable::ResetShadowBuffer ()
{
  //## begin cLocalVariable::ResetShadowBuffer%1191857012.body preserve=yes
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      BOOL_T bg_var = _VarDef->_BackgroundVar;
      if (bg_var) {
         memset(_ShadowChanges, 0, STATEBUF_SIZE);
      }
   }
  //## end cLocalVariable::ResetShadowBuffer%1191857012.body
}

BUF_T cLocalVariable::GetBuf (ULONG_T dataset)
{
  //## begin cLocalVariable::GetBuf%1191857013.body preserve=yes
   if (dataset >= MAX_DATASETS ||
      _VarDef->_VarType == SH_VAR_VIRTUAL) {
      return NULL;
   }
   cValueBuffer * value_buffer = _DataSets[dataset];
   if (value_buffer == NULL) {
      return NULL;
   } else {
      return value_buffer->GetBuf();
   }
  //## end cLocalVariable::GetBuf%1191857013.body
}

void cLocalVariable::SetUnitCode (ULONG_T pos, UCHAR_T value, ULONG_T dataset)
{
  //## begin cLocalVariable::SetUnitCode%1191857014.body preserve=yes
   if (dataset < MAX_DATASETS) {
      CHAR_T * states = _InputStates[dataset];
      cUnitDef * unit_def = _VarDef->get_UnitDef();
      if (unit_def != NULL) {
         if (states != NULL) {
            if (pos < _VarDef->Elements()) {
               states[pos] = value;
            }
         }
      }
   }
  //## end cLocalVariable::SetUnitCode%1191857014.body
}

UCHAR_T cLocalVariable::UnitCode (ULONG_T pos, ULONG_T dataset)
{
  //## begin cLocalVariable::UnitCode%1191857015.body preserve=yes
   UCHAR_T code = 0;
   if (dataset < MAX_DATASETS) {
      CHAR_T * states = _InputStates[dataset];
      if (states != NULL) {
         if (pos < _VarDef->Elements()) {
            code = states[pos];
         }
      }
   }
   return code;
  //## end cLocalVariable::UnitCode%1191857015.body
}

void cLocalVariable::CheckShadowDataset (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cLocalVariable::CheckShadowDataset%1191857016.body preserve=yes
   STRING_T database_name = _VarDef->_DatabaseName;
   if ((_VarDef->_FileName == "Ignore") || (_VarDef->_Text == "NO_LOG_TEXT")) {
      return;
   }
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (_Values == NULL || _VarDef->_VarType == SH_VAR_VIRTUAL) {
      // virtual variable
      return;
   }
   BOOL_T bg_var = _VarDef->_BackgroundVar;
   if (!bg_var) {
      // no set variable
      return;
   }
   if (_Values != _DataSets[FOREGROUND_DATASET]) {
      /// no foreground
      return;
   }
   BOOL_T value_changed = false;
   BOOL_T state_changed = false;
   CHAR_T * shadow_states = _InputStates[SHADOW_DATASET];
   if (shadow_states != NULL) {
      CHAR_T input_state = _States[pos];
      CHAR_T shadow_input_state = shadow_states[pos];
      if (input_state != shadow_input_state) {
         state_changed = true;
      }
   }
   cValueBuffer * shadow_values = _DataSets[SHADOW_DATASET];
   UCHAR_T data_type = _VarDef->_DataType;
   if (!state_changed) {
      switch (data_type) {
      case SH_CHAR:
         {
            CHAR_T value;
            _Values->Get(pos, value);
            CHAR_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_UCHAR:
      case SH_BIT_8:
         {
            UCHAR_T value;
            _Values->Get(pos, value);
            UCHAR_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_SHORT:
         {
            SHORT_T value;
            _Values->Get(pos, value);
            SHORT_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_USHORT:
      case SH_BIT_16:
         {
            USHORT_T value;
            _Values->Get(pos, value);
            USHORT_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_LONG:
         {
            LONG_T value;
            _Values->Get(pos, value);
            LONG_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_ULONG:
      case SH_BIT_32:
         {
            ULONG_T value;
            _Values->Get(pos, value);
            ULONG_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_FLOAT:
         {
            FLOAT_T value;
            _Values->Get(pos, value);
            FLOAT_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_DOUBLE:
         {
            DOUBLE_T value;
            _Values->Get(pos, value);
            DOUBLE_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_BYTE:
         {
         }
         break;
      case SH_STRING:
         {
            STRING_T value;
            _Values->Get(pos, value);
            STRING_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      case SH_WSTRING:
         {
            WSTRING_T value;
            _Values->Get(pos, value);
            WSTRING_T shadow_value;
            shadow_values->Get(pos, shadow_value);
            if (value != shadow_value) {
               value_changed = true;
            }
         }
         break;
      }
   } else {
      STRING_T fg_value;
      STRING_T shadow_value;
      ULONG_T src_flags = VF_FOREGROUND|VF_BUFFERED;
      ULONG_T dst_flags = VF_SHADOW|VF_BUFFERED;
      Get(shadow_value, i1, i2, i3, i4, dst_flags);
      Get(fg_value, i1, i2, i3, i4, src_flags);
      if (strcmp(fg_value.c_str(), shadow_value.c_str()) != 0) {
         value_changed = true;
      }
   }
   if (value_changed) {
      if (_ShadowChanges[pos] == 0) {
         _Context->AlterShadowChanges(+1);
      }
      _ShadowChanges[pos] = 1;
   } else {
      if (_ShadowChanges[pos] == 1) {
         _Context->AlterShadowChanges(-1);
      }
      _ShadowChanges[pos] = 0;
   }
  //## end cLocalVariable::CheckShadowDataset%1191857016.body
}

BOOL_T cLocalVariable::ReadFilter (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, ULONG_T * size)
{
  //## begin cLocalVariable::ReadFilter%1191857019.body preserve=yes
   cFuncRef * func_ref = NULL;
   ULONG_T if_type = VF_GET_IF_TYPE(flags);
   if (if_type == IF_PROPRIETARY) {
      func_ref = _FilterFuncRef;
   } else {
      func_ref = _AccessFuncRef;
   }
   if (func_ref != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            return true;
         }
		   break;
      case SH_STRING:
         {
            STRING_T value;
            func_ref->CallMDLFunc(value, "", i1, i2, i3, i4, 0);
            Accu()->Set(value.c_str());
            return true;
         }
         break;
      case SH_BYTE:
      case SH_WSTRING:
         break;
      case SH_OBJECT:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, 0);
            Accu()->Set(value);
            return true;
         }
      }
   }
   return false;
  //## end cLocalVariable::ReadFilter%1191857019.body
}

BOOL_T cLocalVariable::WriteFilter (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, ULONG_T * size)
{
  //## begin cLocalVariable::WriteFilter%1191857020.body preserve=yes
   cFuncRef * func_ref = NULL;
   ULONG_T if_type = VF_GET_IF_TYPE(flags);
   if (if_type == IF_PROPRIETARY) {
      func_ref = _FilterFuncRef;
   } else {
      func_ref = _AccessFuncRef;
   }
   if (func_ref != NULL) {
      UCHAR_T data_type = _VarDef->_DataType;
      switch (data_type) {
      case SH_CHAR:
      case SH_SHORT:
      case SH_LONG:
         {
            LONG_T value = 0;
            Accu()->Get(value);
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
		   break;
      case SH_UCHAR:
      case SH_USHORT:
      case SH_ULONG:
      case SH_BIT_8:
      case SH_BIT_16:
      case SH_BIT_32:
         {
            ULONG_T value = 0;
            Accu()->Get(value);
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
		   break;
      case SH_FLOAT:
         {
            FLOAT_T value = 0;
            Accu()->Get(value);
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
		   break;
      case SH_DOUBLE:
         {
            DOUBLE_T value = 0;
            Accu()->Get(value);
            func_ref->CallMDLFunc(value, value, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
		   break;
      case SH_STRING:
         {
            STRING_T value;
            Accu()->Get(value, MAX_PRECISION);
            func_ref->CallMDLFunc(value, value.c_str(), i1, i2, i3, i4, VF_WRITE);
            return true;
         }
		   break;
      case SH_BYTE:
      case SH_WSTRING:
         break;
      case SH_OBJECT:
         {
            PTR_T value = 0;
            Accu()->Get((BUF_T&)value);
            func_ref->CallMDLFunc((PTR_T)value, value, size, i1, i2, i3, i4, VF_WRITE);
            return true;
         }
         break;
      }
   }
   return false;
  //## end cLocalVariable::WriteFilter%1191857020.body
}

void cLocalVariable::BufChanged (BUF_T old_buf, BUF_T new_buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
#ifndef BASE_LIBRARY
   UCHAR_T var_type = VarType();
   ULONG_T pos = 0;
   if (var_type != SH_VAR_VIRTUAL) {
      pos = _VarDef->GetPos(i1, i2, i3, i4);
   }
   cDataChange * data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                               _VarId,
                                               new_buf,
                                               i1, i2, i3, i4);
   data_change->set_CellName(_Context->get_Name());
   data_change->set_DataType(DataType());
   data_change->set_PersistenceType(PersistenceType());
   data_change->set_ValueSize(ValueSize());
   data_change->set_Pos(pos);
   data_change->set_VarType(var_type);
   if (flags & VF_FILE_INPUT) {
      data_change->set_ChangeFlags(CH_FLAG_FILE_INPUT);
   }
   _Context->Send(data_change);
   if (IS_PERSISTENT(PersistenceType())) {
      if (_PersistenceChannel == NULL) {
         _PersistenceChannel = _Context->PersistenceChannel();
      }
      if (_PersistenceChannel != NULL) {
         _PersistenceChannel->Send(data_change);
      } else {
         ErrorPrintf("persistence channel not ready %s\n", _VarDef->_VarName.c_str());
      }
   }
   RELEASE_OBJECT(data_change)
#endif
}

ULONG_T cLocalVariable::GetObject (cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::GetObject%1238436644.body preserve=yes
   if (_VarDef->_VarType == SH_VAR_VIRTUAL) {
      Accu()->Set((LONG_T)(&object));
      ReadFilter(i1, i2, i3, i4, flags);
      LONG_T rc = 0;
      Accu()->Get(rc);
      return object.Size();
   }
   SELECT_DATASET(flags)
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   if (!ReadFilter(pos, flags)) {
      UCHAR_T var_type = _VarDef->_VarType;
      if (var_type == SH_VAR_SET || flags & VF_BUFFERED) {
         GetBuffer(pos);
      } else {
         cMapping * mapping = _VarDef->_Mapping;
         if (mapping != NULL) {
            GetDevice(pos, flags);
            ReadConversion(pos, flags);
            if (SetBuffer(pos)) {
               DataChanged(i1, i2, i3, i4, flags);
            }
         } else {
            GetBuffer(pos);
         }
      }
   }
   BUF_T buf = NULL;
   Accu()->Get(buf);
   object = cBinaryObject(buf, ValueSize());
   return object.Size();
  //## end cLocalVariable::GetObject%1238436644.body
}

void cLocalVariable::SetObject (const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cLocalVariable::SetObject%1238436645.body preserve=yes
  //## end cLocalVariable::SetObject%1238436645.body
}

void cLocalVariable::Persist()
{
   cLocalContext * local_context = dynamic_cast<cLocalContext*>(_Context);
   if (local_context == NULL) {
      ErrorPrintf("failed to retrieve local context\n");
      return;
   }
   cPersistenceManager * manager = local_context->PersistenceManager();
   if (manager == NULL) {
      ErrorPrintf("failed to retrieve persistence manager\n");
      return;
   }
   UCHAR_T persistence_type = PersistenceType();
   if (persistence_type == 0) {
      return;
   }
   ULONG_T dataset = 0;
   cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData(); \
   if (user_info == NULL) {
      dataset = 0;
   } else {
      dataset = user_info->get_DataSet();
   }
   long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   long i1_max = -1, i2_max = -1, i3_max = -1, i4_max = -1;
   ULONG_T dims = _VarDef->Dims();
   switch (dims) {
   case 1:
      i1_max = _VarDef->DimSize(0);
      break;
   case 2:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      break;
   case 3:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      i3_max = _VarDef->DimSize(2);
      break;
   case 4:
      i1_max = _VarDef->DimSize(0);
      i2_max = _VarDef->DimSize(1);
      i3_max = _VarDef->DimSize(2);
      i4_max = _VarDef->DimSize(3);
      break;
   }
   if (i4_max > 0) {
      for (i4=0; i4<i4_max; i4++) {
         for (i3=0; i3<i3_max; i3++) {
            for (i2=0; i2<i2_max; i2++) {
               for (i1=0; i1<i1_max; i1++) {
                  Persist(manager, i1, i2, i3, i4, persistence_type, dataset);
               }
            }
         }
      }
   } else if (i3_max > 0) {
      for (i3=0; i3<i3_max; i3++) {
         for (i2=0; i2<i2_max; i2++) {
            for (i1=0; i1<i1_max; i1++) {
               Persist(manager, i1, i2, i3, i4, persistence_type, dataset);
            }
         }
      }
   } else if (i2_max > 0) {
      for (i2=0; i2<i2_max; i2++) {
         for (i1=0; i1<i1_max; i1++) {
            Persist(manager, i1, i2, i3, i4, persistence_type, dataset);
         }
      }
   } else if (i1_max > 0) {
      for (i1=0; i1<i1_max; i1++) {
         Persist(manager, i1, i2, i3, i4, persistence_type, dataset);
      }
   } else {
      Persist(manager, i1, i2, i3, i4, persistence_type, dataset);
   }
}

void cLocalVariable::Persist(cPersistenceManager * manager, int i1, int i2, int i3, int i4, UCHAR_T persistence_type, ULONG_T dataset)
{
   int pos = _VarDef->GetPos(i1, i2, i3, i4);
   STRING_T value;
   UCHAR_T unit_code = 0;
   GetRaw(unit_code, value, i1, i2, i3, i4); 
   cDataChange * data_change = new cDataChange(_VarDef->_VarName.c_str(),
                                               _VarId,
                                               value.c_str(),
                                               i1, i2, i3, i4);
   UCHAR_T precision = _VarDef->_Precision;
   data_change->set_Precision(precision);
   BUF_T buf = NULL;
   Accu()->Get(buf);
   data_change->set_BufPtr(buf);
   data_change->set_CellName(_Context->get_Name());
   data_change->set_DataType(DataType());
   data_change->set_PersistenceType(persistence_type);
   data_change->set_ValueSize(ValueSize());
   data_change->set_Pos(pos);
   data_change->set_VarType(VarType());
//   data_change->set_DataSet(dataset);
   data_change->set_DataSet(0);
   data_change->set_UnitCode(unit_code);
   data_change->set_ValueSize(ValueSize());
//   data_change->set_State(unit_code);   ??
//   data_change->set_UnitText(..);   ??
   manager->Object(data_change);
   delete data_change;
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cLocalVariable::get_Initialized () const
{
  //## begin cLocalVariable::get_Initialized%43D9C4610140.get preserve=no
  return _Initialized;
  //## end cLocalVariable::get_Initialized%43D9C4610140.get
}

void cLocalVariable::set_Initialized (BOOL_T value)
{
  //## begin cLocalVariable::set_Initialized%43D9C4610140.set preserve=no
  _Initialized = value;
  //## end cLocalVariable::set_Initialized%43D9C4610140.set
}

BOOL_T cLocalVariable::StoreIndices(int i1, int i2, int i3, int i4)
{
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      return unit_def->StoreIndices(i1, i2, i3, i4);
   } else {
      return false;
   }
}

BOOL_T cLocalVariable::StoreIndices(int pos)
{
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
      LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
      _VarDef->GetIndices(pos, i1, i2, i3, i4);
      return unit_def->StoreIndices(i1, i2, i3, i4);
   } else {
      return false;
   }
}

void cLocalVariable::SetDeviceStates()
{
   cUnitDef * unit_def = _VarDef->get_UnitDef();
   if (unit_def != NULL) {
   } else {
   }
}

cLocalVariable::LimitChecker * cLocalVariable::_LimitChecker = NULL;

// Additional Declarations
  //## begin cLocalVariable%3E0038B30046.declarations preserve=yes
  //## end cLocalVariable%3E0038B30046.declarations

//## begin module%3E0038B30046.epilog preserve=yes
//## end module%3E0038B30046.epilog
