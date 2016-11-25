//## begin module%3E0032230357.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0032230357.cm

//## begin module%3E0032230357.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0032230357.cp

//## Module: cVarDef%3E0032230357; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarDef.cpp

//## begin module%3E0032230357.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0032230357.additionalIncludes

//## begin module%3E0032230357.includes preserve=yes

/// PR 05.07.07 - added methods used for input state sensitive handling of datasets
///               ::PrintUnitSensitiveValues
/// PR 06.07.07 - changes due to new GetRaw - method of cLocalVariable
/// PR 08.03.10 - added check for unused indices in ::GetPos(...) (Horst Anselm FM)
/// PR 26.01.16 - added new method void cVarDef::Unparse(cStringBuffer &buf, ULONG_T ctrl)
///               this method unparses a variable definition directly to a cStringBuffer

//## end module%3E0032230357.includes

// cStringUtils
#include "System/cStringUtils.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cVariableValues
#include "System/Database/cVariableValues.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cMapping
#include "System/Database/cMapping.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cArgument
#include "System/Database/cArgument.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
#include "System/Sys/cStringBuffer.h"

//## begin module%3E0032230357.additionalDeclarations preserve=yes

#define RELPOS_1(i1)                            (i1)
#define RELPOS_2(i1,d2,i2)                      ((i1 * d2) + i2)
#define RELPOS_3(i1,d2,i2,d3,i3)                ((i1 * (d2*d3)) + RELPOS_2(i2,d3,i3))
#define RELPOS_4(i1,d2,i2,d3,i3,d4,i4)          ((i1 * (d2*d3*d4)) + RELPOS_3(i2,d3,i3,d4,i4))
#define RELPOS_5(i1,d2,i2,d3,i3,d4,i4,d5,i5)    ((i1 * (d2*d3*d4*d5)) + RELPOS_4(i2,d3,i3,d4,i4,d5,i5))

#define GET_INDICES_1(pos,i1,d1)                          {i1=pos;}
#define GET_INDICES_2(pos,i1,i2,d1,d2)                    {i1=(pos/d2)%d1;i2=pos%d2;}
#define GET_INDICES_3(pos,i1,i2,i3,d1,d2,d3)              {i1=(pos/(d2*d3))%d1;i2=(pos/d3)%d2;i3=pos%d3;}
#define GET_INDICES_4(pos,i1,i2,i3,i4,d1,d2,d3,d4)        {i1=(pos/(d2*d3*d4))%d1;i2=(pos/(d3*d4))%d2;i3=(pos/d4)%d3;i4=pos%d4;}
#define GET_INDICES_5(pos,i1,i2,i3,i4,i5,d1,d2,d3,d4,d5)  {i1=(pos/(d2*d3*d4*d5))%d1;i2=(pos/(d3*d4*d5))%d2;i3=(pos/(d4*d5))%d3;i4=(pos/d5)%d4;i5=pos%d5;}

#define POSITION_1(i1)                                (i1)
#define POSITION_2(i1,d2,i2,el_size)                  (RELPOS_2(i1,d2,i2) * el_size)
#define POSITION_3(i1,d2,i2,d3,i3,el_size)            (RELPOS_3(i1,d2,i2,d3,i3) * el_size)
#define POSITION_4(i1,d2,i2,d3,i3,d4,i4,el_size)      (RELPOS_4(i1,d2,i2,d3,i3,d4,i4) * el_size)
#define POSITION_5(i1,d2,i2,d3,i3,d4,i4,d5,i5el_size) (RELPOS_5(i1,d2,i2,d3,i3,d4,i4,d5,i5) * el_size)

#define CLEAN_UNUSED

//## end module%3E0032230357.additionalDeclarations


// Class cVarDef 



































cVarDef::cVarDef()
  //## begin cVarDef::cVarDef%.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _VarType(SH_VAR_VOLATILE), _PersistenceType(UNDEFINED), _MinSpec(NULL), _MaxSpec(NULL), _RefreshType(UNDEFINED), _RefreshValue(0), _BackgroundVar(false), _Flags(0), _SystemFlags(0), _Dynamic(false), _Variable(NULL), _Context(NULL), _Mapping(NULL), _Filter(NULL), _UnitDef(NULL), _Values(NULL), _Access(NULL), _Option(-1)
  //## end cVarDef::cVarDef%.hasinit
  //## begin cVarDef::cVarDef%.initialization preserve=yes
  //## end cVarDef::cVarDef%.initialization
{
  //## begin cVarDef::cVarDef%.body preserve=yes
  //## end cVarDef::cVarDef%.body
}

cVarDef::cVarDef(const cVarDef &right)
  //## begin cVarDef::cVarDef%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _VarType(SH_VAR_VOLATILE), _PersistenceType(UNDEFINED), _MinSpec(NULL), _MaxSpec(NULL), _RefreshType(UNDEFINED), _RefreshValue(0), _BackgroundVar(false), _Flags(0), _SystemFlags(0), _Dynamic(false), _Variable(NULL), _Context(NULL), _Mapping(NULL), _Filter(NULL), _UnitDef(NULL), _Values(NULL), _Access(NULL), _Option(-1)
  //## end cVarDef::cVarDef%copy.hasinit
  //## begin cVarDef::cVarDef%copy.initialization preserve=yes
  //## end cVarDef::cVarDef%copy.initialization
{
  //## begin cVarDef::cVarDef%copy.body preserve=yes
   _DatabaseName = right._DatabaseName;
   _DeviceName = right._DeviceName;
   _VarName = right._VarName;
   _DataType = right._DataType;
   _Length = right._Length;
   _Precision = right._Precision;
   _VarType = right._VarType;
   _PersistenceType = right._PersistenceType;
   _FileName = right._FileName;
   _Description = right._Description;
   _RefreshType = right._RefreshType;
   _RefreshValue = right._RefreshValue;
   _BackgroundVar = right._BackgroundVar;
   _Text = right._Text;
   _Dim1Text = right._Dim1Text;
   _Dim2Text = right._Dim2Text;
   _Dim3Text = right._Dim3Text;
   _Dim4Text = right._Dim4Text;
   _Flags = right._Flags;
   _UnitText = right._UnitText;
   _SystemFlags = right._SystemFlags;
   _Dims = right._Dims;
   _Dynamic = right._Dynamic;
   _UnitDef = right._UnitDef; // HA 190406
  //## end cVarDef::cVarDef%copy.body
}

cVarDef::cVarDef (CONST_STRING_T var_name, UCHAR_T data_type, ULONG_T length, UCHAR_T precision, BOOL_T dynamic)
  //## begin cVarDef::cVarDef%1040992373.hasinit preserve=no
      : _DataType(UNDEFINED), _Length(1), _Precision(0), _VarType(SH_VAR_VOLATILE), _PersistenceType(UNDEFINED), _MinSpec(NULL), _MaxSpec(NULL), _RefreshType(UNDEFINED), _RefreshValue(0), _BackgroundVar(false), _Flags(0), _SystemFlags(0), _Dynamic(false), _Variable(NULL), _Context(NULL), _Mapping(NULL), _Filter(NULL), _UnitDef(NULL), _Values(NULL), _Access(NULL), _Option(-1)
  //## end cVarDef::cVarDef%1040992373.hasinit
  //## begin cVarDef::cVarDef%1040992373.initialization preserve=yes
  //## end cVarDef::cVarDef%1040992373.initialization
{
  //## begin cVarDef::cVarDef%1040992373.body preserve=yes
   _VarName = var_name;
   _DataType = data_type;
   _Length = length;
   if (_Length == 0) {
      _Length = cSHVariant::TypeSize(_DataType);
   }
   _Precision = precision;
   _Dynamic = dynamic;
  //## end cVarDef::cVarDef%1040992373.body
}


cVarDef::~cVarDef()
{
  //## begin cVarDef::~cVarDef%.body preserve=yes
   DELETE_OBJECT(cVariable, _Variable)
   DELETE_OBJECT(cVariableValues, _Values)
   DELETE_OBJECT(cMapping, _Mapping)
   DELETE_OBJECT(cArgument, _MinSpec)
   DELETE_OBJECT(cArgument, _MaxSpec)
   DELETE_OBJECT(cFuncRef, _Filter)
   DELETE_OBJECT(cFuncRef, _Access)
///   DELETE_OBJECT(cUnitDef, _UnitDef)
  //## end cVarDef::~cVarDef%.body
}



//## Other Operations (implementation)
UCHAR_T cVarDef::DataType ()
{
  //## begin cVarDef::DataType%1061805340.body preserve=yes
   return _DataType;
  //## end cVarDef::DataType%1061805340.body
}

ULONG_T cVarDef::GetPos (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cVarDef::GetPos%1040202763.body preserve=yes
   unsigned element_pos = 0;
   ULONG_T size = _Dims.size();
   switch (size) {
   case 0:
      // check values of unused indices
      if (i1 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(), "0", "-1");
      }
      if (i2 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(), "1", "-1");
      }
      if (i3 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(), "2", "-1");
      }
      if (i4 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(), "3", "-1");
      }
      // end of umused check
      break;
   case 1:
      // check values of unused indices
      if (i2 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(), "1", "-1");
      }
      if (i3 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(), "2", "-1");
      }
      if (i4 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(), "3", "-1");
      }
      // end of umused check
      if (i1 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i1 >= (long)_Dims[0]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      element_pos = RELPOS_1(i1);
      break;
   case 2:
      // check values of unused indices
      if (i3 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(), "2", "-1");
      }
      if (i4 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(), "3", "-1");
      }
      // end of umused check
      if (i1 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      if (i1 >= (long)_Dims[0]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 >= (long)_Dims[1]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      element_pos = RELPOS_2(i1,_Dims[1],i2);
      break;
   case 3:
      // check values of unused indices
      if (i4 != -1) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(), "3", "-1");
      }
      // end of umused check
      if (i1 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      if (i3 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(),
                      "2",
                      cConvUtils::StringValue(_Dims[2]-1).c_str());
      }
      if (i1 >= (long)_Dims[0]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 >= (long)_Dims[1]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      if (i3 >= (long)_Dims[2]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(),
                      "2",
                      cConvUtils::StringValue(_Dims[2]-1).c_str());
      }
      element_pos = RELPOS_3(i1,_Dims[1],i2,_Dims[2],i3);
      break;
   case 4:
      if (i1 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      if (i3 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(),
                      "2",
                      cConvUtils::StringValue(_Dims[2]-1).c_str());
      }
      if (i4 < 0) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(),
                      "3",
                      cConvUtils::StringValue(_Dims[3]-1).c_str());
      }
      if (i1 >= (long)_Dims[0]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i1).c_str(),
                      "0",
                      cConvUtils::StringValue(_Dims[0]-1).c_str());
      }
      if (i2 >= (long)_Dims[1]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i2).c_str(),
                      "1",
                      cConvUtils::StringValue(_Dims[1]-1).c_str());
      }
      if (i3 >= (long)_Dims[2]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i3).c_str(),
                      "2",
                      cConvUtils::StringValue(_Dims[2]-1).c_str());
      }
      if (i4 >= (long)_Dims[3]) {
         throw cError(VARIABLE_INVALID_INDEX, 0, _VarName.c_str(),
                      cConvUtils::StringValue(i4).c_str(),
                      "3",
                      cConvUtils::StringValue(_Dims[3]-1).c_str());
      }
      element_pos = RELPOS_4(i1,_Dims[1],i2,_Dims[2],i3,_Dims[3],i4);
      break;
   default:
      int dummy = 0;
      _ASSERT_UNCOND;
   }
   return element_pos;
  //## end cVarDef::GetPos%1040202763.body
}

void cVarDef::GetIndices (ULONG_T pos, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4)
{
  //## begin cVarDef::GetIndices%1040202764.body preserve=yes
   i1 = i2 = i3 = i4 = -1;
   switch (_Dims.size()) {
   case 0: break;
   case 1:
      GET_INDICES_1(pos,i1,_Dims[0])
      break;
   case 2:
      GET_INDICES_2(pos,i1,i2,_Dims[0],_Dims[1])
      break;
   case 3:
      GET_INDICES_3(pos,i1,i2,i3,_Dims[0],_Dims[1],_Dims[2])
      break;
   case 4:
      GET_INDICES_4(pos,i1,i2,i3,i4,_Dims[0],_Dims[1],_Dims[2],_Dims[3])
      break;
   default:
_ASSERT_UNCOND
   }
  //## end cVarDef::GetIndices%1040202764.body
}

void cVarDef::AddDim (ULONG_T pos, ULONG_T dim_size)
{
  //## begin cVarDef::AddDim%1040209222.body preserve=yes
   ULONG_T size = _Dims.size();
   if (pos >= size) _Dims.resize(pos+1);
   _Dims[pos] = dim_size;
  //## end cVarDef::AddDim%1040209222.body
}

void cVarDef::ClearDims ()
{
  //## begin cVarDef::ClearDims%1130341402.body preserve=yes
   _Dims.clear();
  //## end cVarDef::ClearDims%1130341402.body
}

void cVarDef::SetFilter (cFuncRef *func_ref)
{
  //## begin cVarDef::SetFilter%1040209223.body preserve=yes
   if (_Filter != NULL) {
#ifdef CLEAN_UNUSED
      delete _Filter;
#endif
   }
   _Filter = func_ref;
  //## end cVarDef::SetFilter%1040209223.body
}

void cVarDef::SetAccess (cFuncRef *func_ref)
{
  //## begin cVarDef::SetAccess%1132940253.body preserve=yes
   if (_Access != NULL) {
#ifdef CLEAN_UNUSED
      delete _Access;
#endif
   }
   _Access = func_ref;
  //## end cVarDef::SetAccess%1132940253.body
}

void cVarDef::SetMinSpec (cArgument *min_spec)
{
  //## begin cVarDef::SetMinSpec%1088537822.body preserve=yes
   if (_MinSpec != NULL) {
#ifdef CLEAN_UNUSED
      delete _MinSpec;
#endif
   }
   _MinSpec = min_spec;
  //## end cVarDef::SetMinSpec%1088537822.body
}

void cVarDef::SetMaxSpec (cArgument *max_spec)
{
  //## begin cVarDef::SetMaxSpec%1088537823.body preserve=yes
   if (_MaxSpec != NULL) {
#ifdef CLEAN_UNUSED
      delete _MaxSpec;
#endif
   }
   _MaxSpec = max_spec;
  //## end cVarDef::SetMaxSpec%1088537823.body
}

void cVarDef::SetMapping (cMapping *mapping)
{
  //## begin cVarDef::SetMapping%1040209224.body preserve=yes
   if (_Mapping != NULL) {
#ifdef CLEAN_UNUSED
      delete _Mapping;
#endif
   }
   _Mapping = mapping;
  //## end cVarDef::SetMapping%1040209224.body
}

void cVarDef::SetValues (cVariableValues *values)
{
  //## begin cVarDef::SetValues%1091802232.body preserve=yes
   if (_Values != NULL) {
#ifdef CLEAN_UNUSED
      delete _Values;
#endif
   }
   _Values = values;
  //## end cVarDef::SetValues%1091802232.body
}

ULONG_T cVarDef::Dims ()
{
  //## begin cVarDef::Dims%1040209225.body preserve=yes
   return _Dims.size();
  //## end cVarDef::Dims%1040209225.body
}

ULONG_T cVarDef::DimSize (ULONG_T pos)
{
  //## begin cVarDef::DimSize%1040209226.body preserve=yes
   ULONG_T size = _Dims.size();
   if (pos >= size) {
      throw cError(VARIABLE_INVALID_DIM, 0, _VarName.c_str(),
                   cConvUtils::StringValue(pos).c_str(),
                   cConvUtils::StringValue(size).c_str());
   }
   return _Dims[pos];
  //## end cVarDef::DimSize%1040209226.body
}

void cVarDef::SetDimSize (ULONG_T pos, ULONG_T new_size)
{
  //## begin cVarDef::SetDimSize%1133013902.body preserve=yes
   ULONG_T size = _Dims.size();
   if (pos >= size) {
      throw cError(VARIABLE_INVALID_DIM, 0, _VarName.c_str(),
                   cConvUtils::StringValue(pos).c_str(),
                   cConvUtils::StringValue(size).c_str());
   }
   ULONG_T dim_size = _Dims[pos];
//   if (new_size < dim_size && new_size > 0) {
      _Dims[pos] = new_size;
//   }
  //## end cVarDef::SetDimSize%1133013902.body
}

ULONG_T cVarDef::Elements ()
{
  //## begin cVarDef::Elements%1040209227.body preserve=yes
   ULONG_T elements = 1;
   ULONG_T size = _Dims.size();
   for (ULONG_T i=0; i<size; i++) {
      elements = elements * _Dims[i];
   }
   return elements;
  //## end cVarDef::Elements%1040209227.body
}

ULONG_T cVarDef::ElementSize ()
{
  //## begin cVarDef::ElementSize%1042559818.body preserve=yes
   return _Length * cSHVariant::TypeSize(_DataType);
  //## end cVarDef::ElementSize%1042559818.body
}

STRING_T cVarDef::Serialize_Obsolete ()
{
  //## begin cVarDef::Serialize_Obsolete%1049277232.body preserve=yes
   STRING_T serialized_obj;
   char buf[0x400] = {0};
	ULONG_T dim[4] = {0};
	ULONG_T dims = _Dims.size();
	if (dims > 4) dims = 4;
	for (ULONG_T i=0; i<dims; i++) {
		dim[i] = _Dims[i];
	}
	SafePrintf(buf, sizeof(buf), "VAR(%s,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		        _VarName.c_str(),
		        dim[0],dim[1],dim[2],dim[3],
			     _DataType,
			     _Length,
			     _Precision,
			     _VarType,
              _Flags);
   serialized_obj = buf;
   serialized_obj += ",";
   serialized_obj += _FileName.c_str();
   serialized_obj += ",";
   serialized_obj += _Description.c_str();
   serialized_obj += ",";
   serialized_obj += _Text.c_str();
   serialized_obj += ",";
   serialized_obj += _Dim1Text.c_str();
   serialized_obj += ",";
   serialized_obj += _Dim2Text.c_str();
   serialized_obj += ",";
   serialized_obj += _Dim3Text.c_str();
   serialized_obj += ",";
   serialized_obj += _Dim4Text.c_str();
   serialized_obj += ")";
	return serialized_obj;
  //## end cVarDef::Serialize_Obsolete%1049277232.body
}

void cVarDef::Construct_Obsolete (CONST_STRING_T serialized_obj)
{
  //## begin cVarDef::Construct_Obsolete%1049277233.body preserve=yes
   CONST_STRING_T buf_ptr = serialized_obj;
   char var_name[0x10] = {0};
	STRING_T description;
	STRING_T file_name;
	STRING_T text;
	STRING_T dim1_text;
	STRING_T dim2_text;
	STRING_T dim3_text;
	STRING_T dim4_text;
	ULONG_T dim[4] = {0};
   ULONG_T data_type = UNDEFINED;
   ULONG_T length = 0;
   ULONG_T var_type = UNDEFINED;
   ULONG_T var_flags = 0;
   ULONG_T precision = 0;
   int nchars = 0;
   int params = 0;
	params = sscanf(buf_ptr, "VAR(%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%n",
		     var_name,
		     &dim[0],&dim[1],&dim[2],&dim[3],
			  &data_type,
			  &length,
			  &precision,
			  &var_type,
           &var_flags,
           &nchars);
	if (params == 11) {
		_VarName = var_name;
      _DataType = (UCHAR_T)data_type;
      _Length = length;
      _Precision = (UCHAR_T)precision;
      _VarType = (UCHAR_T)var_type;
      for (ULONG_T i=0; i<4; i++) {
			if (dim[i] == 0) break;
			_Dims.resize(i+1);
			_Dims[i] = dim[i];
		}
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _FileName, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Description, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Text, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Dim1Text, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Dim2Text, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Dim3Text, nchars);
      buf_ptr += nchars;
      cStringUtils::GetStringSequence(buf_ptr, _Dim4Text, nchars);
   } else {
      int dummy = 0;
   }
  //## end cVarDef::Construct_Obsolete%1049277233.body
}

void cVarDef::Unparse(STRING_T &buf, ULONG_T ctrl)
{
   //## begin cVarDef::Unparse%1092077355.body preserve=yes
   buf += _VarName.c_str();
   PrintDims(buf);
   PrintType(buf, ctrl);
   PrintSystemFlags(buf);
   if (!(ctrl & IGN_UNIT_TEXT)) {
      PrintUnitText(buf);
   }
   if (!(ctrl & IGN_DESCRIPTION)) {
      PrintDescription(buf);
   }
   else {
      PrintUnitSensitiveValues(buf, (cLocalVariable*)_Variable);
   }
   if (!(ctrl & IGN_TEXT)) {
      PrintText(buf);
   }
   if (!(ctrl & IGN_DIM1_TEXT)) {
      PrintDim1Text(buf);
   }
   if (!(ctrl & IGN_DIM2_TEXT)) {
      PrintDim2Text(buf);
   }
   if (!(ctrl & IGN_DIM3_TEXT)) {
      PrintDim3Text(buf);
   }
   if (!(ctrl & IGN_DIM4_TEXT)) {
      PrintDim4Text(buf);
   }
   PrintFlags(buf);
   if (!(ctrl & IGN_VALUES)) {
      PrintValues(buf, (cLocalVariable*)_Variable);
   }
   buf += ";\n";
   //## end cVarDef::Unparse%1092077355.body
}

void cVarDef::Unparse(cStringBuffer &buf, ULONG_T ctrl)
{
   //## begin cVarDef::Unparse%1092077355.body preserve=yes
   buf += _VarName.c_str();
   STRING_T text;
   PrintDims(text);
   PrintType(text, ctrl);
   PrintSystemFlags(text);
   if (!(ctrl & IGN_UNIT_TEXT)) {
      PrintUnitText(text);
   }
   if (!(ctrl & IGN_DESCRIPTION)) {
      PrintDescription(text);
   }
   else {
      PrintUnitSensitiveValues(text, (cLocalVariable*)_Variable);
   }
   if (!(ctrl & IGN_TEXT)) {
      PrintText(text);
   }
   if (!(ctrl & IGN_DIM1_TEXT)) {
      PrintDim1Text(text);
   }
   if (!(ctrl & IGN_DIM2_TEXT)) {
      PrintDim2Text(text);
   }
   if (!(ctrl & IGN_DIM3_TEXT)) {
      PrintDim3Text(text);
   }
   if (!(ctrl & IGN_DIM4_TEXT)) {
      PrintDim4Text(text);
   }
   PrintFlags(text);
   buf += text.c_str();
   if (!(ctrl & IGN_VALUES)) {
      PrintValues(buf, (cLocalVariable*)_Variable);
   }
   buf += ";\n";
   //## end cVarDef::Unparse%1092077355.body
}

BOOL_T cVarDef::IsDynamic()
{
  //## begin cVarDef::IsDynamic%1090073692.body preserve=yes
   return _Dynamic;
  //## end cVarDef::IsDynamic%1090073692.body
}

STRING_T cVarDef::TypeSpec (ULONG_T ctrl)
{
  //## begin cVarDef::TypeSpec%1092077359.body preserve=yes
   const char * type_name = "?";
   char type_spec[128] = {0};
   switch (_DataType) {
   case UNDEFINED: return "undefined";
   case SH_VOID: return "void";
   case SH_CHAR:
      type_name = "char";
      break;
   case SH_UCHAR:
      type_name = "uchar";
      break;
   case SH_SHORT:
      type_name = "short";
      break;
   case SH_USHORT:
      type_name = "ushort";
      break;
   case SH_LONG:
      type_name = "long";
      break;
   case SH_ULONG:
      type_name = "ulong";
      break;
   case SH_BIT_8:
      type_name = "bit8";
      break;
   case SH_BIT_16:
      type_name = "bit16";
      break;
   case SH_BIT_32:
      type_name = "bit32";
      break;
   case SH_FLOAT:
      type_name = "float";
      break;
   case SH_DOUBLE:
      type_name = "double";
      break;
   case SH_STRING:
      type_name = "string";
      break;
   case SH_WSTRING:
      type_name = "wstring";
      break;
   case SH_BYTE:
      type_name = "byte";
      break;
   case SH_OBJECT: return "object";
   default: return "?type";
   }
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
   case SH_FLOAT:
   case SH_DOUBLE:
   {
      UCHAR_T precision = _Precision;
      if (_UnitDef && (ctrl & USE_DATASET_PRECISION)) {
          precision = _UnitDef->Precision(_UnitDef->get_DatasetState());
      }

      if (precision > 0) {
         SafePrintf(type_spec, sizeof(type_spec), "%s(%d)", type_name, precision);
      } else {
         SafePrintf(type_spec, sizeof(type_spec), "%s", type_name);
      }
      break;
   }
   case SH_STRING:
   case SH_WSTRING:
   case SH_BYTE:
      SafePrintf(type_spec, sizeof(type_spec), "%s(%d)", type_name, _Length);
      break;
   default:
      SafePrintf(type_spec, sizeof(type_spec), "%s", type_name);
   }
   return type_spec;
  //## end cVarDef::TypeSpec%1092077359.body
}

BOOL_T cVarDef::EnableMapping(BOOL_T state, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   if (_Mapping == NULL) {
      return false;
   }
   ULONG_T pos = GetPos(i1, i2, i3, i4);
   MAP_ITEM_T * map_item = _Mapping->MapItem(pos);
   if (map_item == NULL) {
      return false;
   }
   map_item->enabled = state;
   return true;
}

BOOL_T cVarDef::EnableCompleteMapping(ULONG_T state)
{
   if (_Mapping == NULL) {
      return false;
   }
   int elements = Elements();
   int i = 0;
   for (i=0; i<elements; i++) {
      MAP_ITEM_T * map_item = _Mapping->MapItem(i);
      if (map_item != NULL) {
         map_item->enabled = state;
      }
   }
   return true;
}

BOOL_T cVarDef::MappingEnabled(LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   ULONG_T pos = GetPos(i1, i2, i3, i4);
   if (_Mapping == NULL) {
      return true;
   }
   MAP_ITEM_T * map_item = _Mapping->MapItem(pos);
   if (map_item == NULL) {
      return true;
   }
   return map_item->enabled;
}

ULONG_T cVarDef::PrintDims (STRING_T &buf)
{
  //## begin cVarDef::PrintDims%1092077356.body preserve=yes
   ULONG_T initial_len = buf.size();
   for (ULONG_T i=0; i<Dims(); i++) {
      int dsize = DimSize(i);
      if (dsize > 0) {
         char dim_size[64] = {0};
         SafePrintf(dim_size, sizeof(dim_size), "%d", dsize);
         buf += "[";
         buf += dim_size;
         buf += "]";
      }
   }
   return buf.size() - initial_len;
  //## end cVarDef::PrintDims%1092077356.body
}

ULONG_T cVarDef::PrintType (STRING_T &buf, ULONG_T ctrl)
{
  //## begin cVarDef::PrintType%1092077357.body preserve=yes
   ULONG_T initial_len = buf.size();
   buf += " ";
   buf += TypeSpec(ctrl).c_str();
   if (_VarType == SH_VAR_SET) {
      buf += " vartype=set ";
   }
   if (_VarType == SH_VAR_ACT) {
      buf += " vartype=act ";
   }
   return buf.size() - initial_len;
  //## end cVarDef::PrintType%1092077357.body
}

ULONG_T cVarDef::PrintDescription (STRING_T &buf)
{
  //## begin cVarDef::PrintDescription%1092126572.body preserve=yes
   if (_Description.size() == 0) return 0;
   buf += " description=\"";
   buf += _Description.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintDescription%1092126572.body
}

ULONG_T cVarDef::PrintValues(STRING_T &buf, cLocalVariable *variable)
{
   //## begin cVarDef::PrintValues%1092077358.body preserve=yes
   UCHAR_T data_type = _DataType;
   buf += " values={";
   ULONG_T elements = Elements();
   STRING_T value;
   for (ULONG_T i = 0; i<elements; i++) {
      long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
      GetIndices(i, i1, i2, i3, i4);
      try {
         value = "";
         variable->Get(value, i1, i2, i3, i4, VF_DATASET_REPRESENTATION);
      }
      catch (cError & e) {
         value = DefaultValue(data_type);
      }
      catch (...) {
         value = DefaultValue(data_type);
      }
      if (i > 0) {
         buf += ",";
      }
      if (data_type == SH_STRING) {
         if (cConvUtils::IsPureString(value.c_str())) {
            buf += "\"";
            buf += value.c_str();
            buf += "\"";
         }
         else {
            STRING_T bcd_value;
            cConvUtils::Buf2String(bcd_value, (BUF_T)value.c_str(), value.size());
            buf += bcd_value.c_str();
         }
      }
      else {
         buf += value.c_str();
      }
   }
   buf += "}";
   return 0;
   //## end cVarDef::PrintValues%1092077358.body
}

ULONG_T cVarDef::PrintValues(cStringBuffer &buf, cLocalVariable *variable)
{
   //## begin cVarDef::PrintValues%1092077358.body preserve=yes
   UCHAR_T data_type = _DataType;
   buf += " values={";
   ULONG_T elements = Elements();
   STRING_T value;
   for (ULONG_T i = 0; i<elements; i++) {
      long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
      GetIndices(i, i1, i2, i3, i4);
      try {
         value = "";
         variable->Get(value, i1, i2, i3, i4, VF_DATASET_REPRESENTATION);
      }
      catch (cError & e) {
         value = DefaultValue(data_type);
      }
      catch (...) {
         value = DefaultValue(data_type);
      }
      if (i > 0) {
         buf += ",";
      }
      if (data_type == SH_STRING) {
         if (cConvUtils::IsPureString(value.c_str())) {
            buf += "\"";
            buf += value.c_str();
            buf += "\"";
         }
         else {
            cConvUtils::Buf2String(buf, (BUF_T)value.c_str(), value.size());
         }
      }
      else {
         buf += value.c_str();
      }
   }
   buf += "}";
   return 0;
   //## end cVarDef::PrintValues%1092077358.body
}

ULONG_T cVarDef::PrintUnitSensitiveValues(STRING_T &buf, cLocalVariable *variable)
{
   cUnitDef * unit_def = variable->_VarDef->get_UnitDef();
   if (unit_def != NULL &&
       unit_def->get_TargetDependent()) {
      UCHAR_T data_type = _DataType;
      buf += " description=\" values={";
      ULONG_T elements = Elements();
      STRING_T value;
      STRING_T unit_text;
      UCHAR_T unit_code = 0;
      for (ULONG_T i=0; i<elements; i++) {
         long i1=-1, i2=-1, i3=-1, i4=-1;
         GetIndices(i, i1, i2, i3, i4);
         try {
            value = "";
            variable->GetRaw(unit_code, value, i1, i2, i3, i4);
            unit_text = variable->UnitText((CHAR_T)unit_code);
         } catch (cError & e) {
            value = DefaultValue(data_type); 
         } catch (...) {
            value = DefaultValue(data_type); 
         }
         if (i > 0) {
            buf += ",";
         }
         if (data_type == SH_STRING) {
            if (cConvUtils::IsPureString(value.c_str())) {
               buf += "\"";
               buf += value.c_str();
               buf += "\"";
            } else {
               STRING_T bcd_value;
               cConvUtils::Buf2String(bcd_value, (BUF_T)value.c_str(), value.size());
               buf += bcd_value.c_str();
            }
         } else {
            char _unit_code[0x20] = {0};
            SafePrintf(_unit_code, sizeof(_unit_code), "%d", (ULONG_T)unit_code);
            buf += unit_text;
            buf += "(";
            buf += _unit_code;
            buf += ",";
            buf += value.c_str();
            buf += ")";
         }
      }
      buf += "}\"";
   }
   return 0;
}

ULONG_T cVarDef::PrintText (STRING_T &buf)
{
  //## begin cVarDef::PrintText%1108111655.body preserve=yes
   if (_Text.size() == 0) return 0;
   buf += " text=\"";
   buf += _Text.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintText%1108111655.body
}

ULONG_T cVarDef::PrintDim1Text (STRING_T &buf)
{
  //## begin cVarDef::PrintDim1Text%1108111656.body preserve=yes
   if (_Dim1Text.size() == 0) return 0;
   buf += " dim1text=\"";
   buf += _Dim1Text.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintDim1Text%1108111656.body
}

ULONG_T cVarDef::PrintDim2Text (STRING_T &buf)
{
  //## begin cVarDef::PrintDim2Text%1108111657.body preserve=yes
   if (_Dim2Text.size() == 0) return 0;
   buf += " dim2text=\"";
   buf += _Dim2Text.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintDim2Text%1108111657.body
}

ULONG_T cVarDef::PrintDim3Text (STRING_T &buf)
{
  //## begin cVarDef::PrintDim3Text%1108111658.body preserve=yes
   if (_Dim3Text.size() == 0) return 0;
   buf += " dim3text=\"";
   buf += _Dim3Text.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintDim3Text%1108111658.body
}

ULONG_T cVarDef::PrintDim4Text (STRING_T &buf)
{
  //## begin cVarDef::PrintDim4Text%1108111659.body preserve=yes
   if (_Dim4Text.size() == 0) return 0;
   buf += " dim4text=\"";
   buf += _Dim4Text.c_str();
   buf += "\"";
   return 0;
  //## end cVarDef::PrintDim4Text%1108111659.body
}

ULONG_T cVarDef::PrintSystemFlags (STRING_T &buf)
{
  //## begin cVarDef::PrintSystemFlags%1125676427.body preserve=yes
   if (_SystemFlags == 0) return 0;
   BOOL_T first_added = false;
   buf += " sysflags=";
   if (_SystemFlags & HOST_READ) {
      buf += "hostread";
      first_added = true;
   }
   if (_SystemFlags & HOST_WRITE) {
      if (first_added) {
         buf += ",";
      }
      buf += "hostwrite";
      first_added = true;
   }
   if (_SystemFlags & DIM1_OFFSET) {
      if (first_added) {
         buf += ",";
      }
      buf += "d1offset";
      first_added = true;
   }
   if (_SystemFlags & DIM2_OFFSET) {
      if (first_added) {
         buf += ",";
      }
      buf += "d2offset";
      first_added = true;
   }
   if (_SystemFlags & DIM3_OFFSET) {
      if (first_added) {
         buf += ",";
      }
      buf += "d3offset";
      first_added = true;
   }
   if (_SystemFlags & DIM4_OFFSET) {
      if (first_added) {
         buf += ",";
      }
      buf += "d4offset";
      first_added = true;
   }
   if (_SystemFlags & EM63_VARIABLE) {
      if (first_added) {
         buf += ",";
      }
      buf += "em63";
      first_added = true;
   }
   return 0;
  //## end cVarDef::PrintSystemFlags%1125676427.body
}

ULONG_T cVarDef::PrintFlags (STRING_T &buf)
{
  //## begin cVarDef::PrintFlags%1108111660.body preserve=yes
   if (_Flags == 0) return 0;
   char sval[0x40] = {0};
   SafePrintf(sval, sizeof(sval), "0x%x", _Flags);
   buf += " flags=";
   buf += sval;
   return 0;
  //## end cVarDef::PrintFlags%1108111660.body
}

ULONG_T cVarDef::PrintUnitText (STRING_T &buf)
{
  //## begin cVarDef::PrintUnitText%1145513553.body preserve=yes
   ULONG_T initial_len = buf.size();
   STRING_T unitText = "?";

   if (_UnitDef != NULL) {
      unitText  = "\"";
      unitText += _UnitDef->UnitText();
      unitText += "\"";
   } else {
      unitText = _UnitText;
   }

   if ((unitText != "?") && (unitText != "")){
      buf += " unit=";
      buf += unitText;
   }
   return buf.size() - initial_len;
  //## end cVarDef::PrintUnitText%1145513553.body
}

STRING_T cVarDef::DefaultValue (UCHAR_T data_type)
{
  //## begin cVarDef::DefaultValue%1092122757.body preserve=yes
   switch (data_type) {
   case UNDEFINED: return "undefined";
   case SH_VOID:
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
   case SH_FLOAT:
   case SH_DOUBLE:
      return "0";
   case SH_STRING:
      return "";
   case SH_WSTRING:
      return "bcd('')";
   case SH_BYTE:
      return "bcd('')";
   case SH_OBJECT:
      return "bcd('')";
   default: return "?value";
   }
  //## end cVarDef::DefaultValue%1092122757.body
}

// Additional Declarations
  //## begin cVarDef%3E0032230357.declarations preserve=yes
  //## end cVarDef%3E0032230357.declarations

//## begin module%3E0032230357.epilog preserve=yes

void cVarDef::set_UnitDef(cUnitDef * unit_def)
{
   _UnitDef = unit_def;
}

//## end module%3E0032230357.epilog
