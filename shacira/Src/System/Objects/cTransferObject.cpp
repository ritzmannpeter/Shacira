//## begin module%3E5A568D005E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E5A568D005E.cm

//## begin module%3E5A568D005E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E5A568D005E.cp

//## Module: cTransferObject%3E5A568D005E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cTransferObject.cpp

//## begin module%3E5A568D005E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E5A568D005E.additionalIncludes

//## begin module%3E5A568D005E.includes preserve=yes

/// PR 14.11.07 - implemented substitution of control characters ,() in string attributes

//## end module%3E5A568D005E.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
//## begin module%3E5A568D005E.additionalDeclarations preserve=yes

#define OPEN_BRACKET    0x1C
#define CLOSE_BRACKET   0x1D
#define COMMA           0x1E

static STRING_T SerializeString(const char * s)
{
   STRING_T result;
   int i = 0;
   int len = strlen(s);
   for (i=0; i<len; i++) {
      char c = s[i];
      if (c == ',') {
         result += COMMA;
      } else if (c == ')') {
         result += CLOSE_BRACKET;
      } else if (c == '(') {
         result += OPEN_BRACKET;
      } else {
         result += c;
      }
   }
   return result;
}

static STRING_T ConstructString(const char * s)
{
   STRING_T result;
   int i = 0;
   int len = strlen(s);
   for (i=0; i<len; i++) {
      char c = s[i];
      if (c == COMMA) {
         result += ',';
      } else if (c == CLOSE_BRACKET) {
         result += ')';
      } else if (c == OPEN_BRACKET) {
         result += '(';
      } else {
         result += c;
      }
   }
   return result;
}

//## end module%3E5A568D005E.additionalDeclarations


// Class cTransferObject 








//## begin cTransferObject::ParseBuf%41657781033C.attr preserve=no  implementation: static cMemoryPtr * {U} NULL
cMemoryPtr *cTransferObject::_ParseBuf = NULL;
//## end cTransferObject::ParseBuf%41657781033C.attr

//## begin cTransferObject::BufMutex%4165875700BB.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cTransferObject::_BufMutex;
//## end cTransferObject::BufMutex%4165875700BB.attr


cTransferObject::cTransferObject()
  //## begin cTransferObject::cTransferObject%.hasinit preserve=no
      : _Type(UNDEFINED), _SubType(UNDEFINED)
  //## end cTransferObject::cTransferObject%.hasinit
  //## begin cTransferObject::cTransferObject%.initialization preserve=yes
  //## end cTransferObject::cTransferObject%.initialization
{
  //## begin cTransferObject::cTransferObject%.body preserve=yes
  //## end cTransferObject::cTransferObject%.body
}

cTransferObject::cTransferObject(const cTransferObject &right)
  //## begin cTransferObject::cTransferObject%copy.hasinit preserve=no
      : _Type(UNDEFINED), _SubType(UNDEFINED)
  //## end cTransferObject::cTransferObject%copy.hasinit
  //## begin cTransferObject::cTransferObject%copy.initialization preserve=yes
  //## end cTransferObject::cTransferObject%copy.initialization
{
  //## begin cTransferObject::cTransferObject%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTransferObject::cTransferObject%copy.body
}

cTransferObject::cTransferObject (CONST_STRING_T serialized_object)
  //## begin cTransferObject::cTransferObject%1047469645.hasinit preserve=no
      : _Type(UNDEFINED), _SubType(UNDEFINED)
  //## end cTransferObject::cTransferObject%1047469645.hasinit
  //## begin cTransferObject::cTransferObject%1047469645.initialization preserve=yes
  //## end cTransferObject::cTransferObject%1047469645.initialization
{
  //## begin cTransferObject::cTransferObject%1047469645.body preserve=yes
	_SerializedObject = serialized_object;
	_Type = Parse(_SerializedObject.c_str());
  //## end cTransferObject::cTransferObject%1047469645.body
}


cTransferObject::~cTransferObject()
{
  //## begin cTransferObject::~cTransferObject%.body preserve=yes
   _Header.clear();
   _Body.clear();
   _Parameters.clear();
  //## end cTransferObject::~cTransferObject%.body
}



//## Other Operations (implementation)
INT_T cTransferObject::Parse (CONST_STRING_T serialized_obj)
{
  //## begin cTransferObject::Parse%1046095020.body preserve=yes
   cObjectLock __lock__(&_BufMutex);
   if (_ParseBuf == NULL) {
      _ParseBuf = new cMemoryPtr(0x2000);
   }
   const char * src_ptr = serialized_obj;
   ULONG_T src_len = strlen(serialized_obj);
   _ParseBuf->AdjustSize(src_len);
   char * buf = (char*)*_ParseBuf;
	ULONG_T buf_size = _ParseBuf->Size();
	ULONG_T nchars = 0;
   int params = sscanf(src_ptr, "H(%[^)])%n,", buf, &nchars);
	if (params == 1) {
		cTokenizer tokenizer(buf, strlen(buf));
		CONST_STRING_T token = NULL;
		int i = 0;
		while ((token = tokenizer.GetToken(",")) != NULL) {
         STRING_T temp_value = ConstructString(token);
         AddAttribute(i, temp_value.c_str(), ObjectHeader);
			if (i == 0) _Type = atol(token);
			i++;
		}
   	src_ptr += nchars;
   } else {
      ErrorPrintf("failed to parse object\n%s\nheader not interpreted\n", serialized_obj);
      return _Type;
   }
   memset(buf, 0, buf_size);
   params = sscanf(src_ptr, "B(%[^)])%n,", buf, &nchars);
   if (params == 1) {
      cTokenizer tokenizer(buf, strlen(buf));
      CONST_STRING_T token = NULL;
      int i = 0;
      while ((token = tokenizer.GetToken(",")) != NULL) {
         STRING_T temp_value = ConstructString(token);
         AddAttribute(i, temp_value.c_str(), ObjectBody);
         i++;
      }
      src_ptr += nchars;
   } else {
      ErrorPrintf("failed to parse object\n%s\nbody not interpreted\n", serialized_obj);
      return _Type;
   }
   if (strnicmp(src_ptr, "bcd", 3) == 0) {
      return _Type;
   }
   // optional parts of a serialized object
   memset(buf, 0, buf_size);
   params = sscanf(src_ptr, "P(%[^)])%n,", buf, &nchars);
	if (params == 1) {
		cTokenizer tokenizer(buf, strlen(buf));
		CONST_STRING_T token = NULL;
		int i = 0;
		while ((token = tokenizer.GetToken(",")) != NULL) {
         STRING_T temp_value = ConstructString(token);
			AddAttribute(i, temp_value.c_str(), ObjectParams);
			i++;
		}
      src_ptr += nchars;
      memset(buf, 0, buf_size);
		params = sscanf(src_ptr, "PV(%[^)])%n,", buf, &nchars);
		if (params == 1) {
			cTokenizer tokenizer(buf, strlen(buf));
			CONST_STRING_T token = NULL;
			int i = 0;
			while ((token = tokenizer.GetToken(",")) != NULL) {
            STRING_T temp_value = ConstructString(token);
				AddAttribute(i, temp_value.c_str(), ObjectParamValues);
				i++;
			}
   		src_ptr += nchars;
		}
      memset(buf, 0, buf_size);
		params = sscanf(src_ptr, "PF(%[^)])%n,", buf, &nchars);
		if (params == 1) {
			cTokenizer tokenizer(buf, strlen(buf));
			CONST_STRING_T token = NULL;
			int i = 0;
			while ((token = tokenizer.GetToken(",")) != NULL) {
            STRING_T temp_value = ConstructString(token);
				AddAttribute(i, temp_value.c_str(), ObjectFlags);
				i++;
			}
		}
   }
   return _Type;
  //## end cTransferObject::Parse%1046095020.body
}

INT_T cTransferObject::ObjectType (CONST_STRING_T serialized_obj)
{
  //## begin cTransferObject::ObjectType%1047543049.body preserve=yes
   INT_T object_type = UNDEFINED;
	sscanf(serialized_obj, "H(%d,,", &object_type);
	return object_type;
  //## end cTransferObject::ObjectType%1047543049.body
}

void cTransferObject::AddAttribute (ULONG_T index, CONST_STRING_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046094996.body preserve=yes
	(*GetVec(area, index))[index] = value;
  //## end cTransferObject::AddAttribute%1046094996.body
}

void cTransferObject::AddAttribute (ULONG_T index, LONG_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095001.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%d", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095001.body
}

void cTransferObject::AddAttribute (ULONG_T index, ULONG_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095006.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%d", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095006.body
}

void cTransferObject::AddAttribute (ULONG_T index, INT_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095016.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%d", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095016.body
}

void cTransferObject::AddAttribute (ULONG_T index, DOUBLE_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095002.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%.3lf", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095002.body
}

void cTransferObject::AddAttribute (ULONG_T index, BOOL_T value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095007.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%d", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095007.body
}

void cTransferObject::AddAttribute (ULONG_T index, cTimeObject &value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1046095013.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%d", (ULONG_T)value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1046095013.body
}

void cTransferObject::AddAttribute (ULONG_T index, void *value, AreaType area)
{
  //## begin cTransferObject::AddAttribute%1051102667.body preserve=yes
	char num_value[64] = {0};
	SafePrintf(num_value, sizeof(num_value), "%p", value);
	(*GetVec(area, index))[index] = num_value;
  //## end cTransferObject::AddAttribute%1051102667.body
}

void cTransferObject::GetAttribute (ULONG_T index, STRING_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095008.body preserve=yes
	value = (*GetVec(area, index))[index].c_str();
  //## end cTransferObject::GetAttribute%1046095008.body
}

void cTransferObject::GetAttribute (ULONG_T index, LONG_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095009.body preserve=yes
	value = atol((*GetVec(area, index))[index].c_str());
  //## end cTransferObject::GetAttribute%1046095009.body
}

void cTransferObject::GetAttribute (ULONG_T index, ULONG_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095010.body preserve=yes
	value = strtoul((*GetVec(area, index))[index].c_str(), NULL, 0);
  //## end cTransferObject::GetAttribute%1046095010.body
}

void cTransferObject::GetAttribute (ULONG_T index, INT_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095017.body preserve=yes
	value = atol((*GetVec(area, index))[index].c_str());
  //## end cTransferObject::GetAttribute%1046095017.body
}

void cTransferObject::GetAttribute (ULONG_T index, DOUBLE_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095011.body preserve=yes
	DOUBLE_T dval = 0;
	sscanf((*GetVec(area, index))[index].c_str(), "%lf", &dval);
	value = dval;
  //## end cTransferObject::GetAttribute%1046095011.body
}

void cTransferObject::GetAttribute (ULONG_T index, BOOL_T &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095012.body preserve=yes
	value = atol((*GetVec(area, index))[index].c_str());
  //## end cTransferObject::GetAttribute%1046095012.body
}

void cTransferObject::GetAttribute (ULONG_T index, cTimeObject &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1046095014.body preserve=yes
	value = atol((*GetVec(area, index))[index].c_str());
  //## end cTransferObject::GetAttribute%1046095014.body
}

void cTransferObject::GetAttribute (ULONG_T index, void * &value, AreaType area)
{
  //## begin cTransferObject::GetAttribute%1051102668.body preserve=yes
	void * ptr = NULL;
	sscanf((*GetVec(area, index))[index].c_str(), "%p", &ptr);
	value = ptr;
  //## end cTransferObject::GetAttribute%1051102668.body
}

ULONG_T cTransferObject::Params ()
{
  //## begin cTransferObject::Params%1047655607.body preserve=yes
	return _Parameters.size();
  //## end cTransferObject::Params%1047655607.body
}

STRING_T cTransferObject::Serialize ()
{
  //## begin cTransferObject::Serialize%1046095005.body preserve=yes
   STRING_T serialized_obj = "H(";
   STRING_VECTOR_T::const_iterator i = _Header.cbegin();
   while (i != _Header.cend()) {
      if (i != _Header.cbegin()) serialized_obj += ",";
      serialized_obj += SerializeString((*i).c_str());
      i++;
   }
   serialized_obj += ")";
   serialized_obj += "B(";
   i = _Body.begin();
   while (i != _Body.cend()) {
      if (i != _Body.cbegin()) serialized_obj += ",";
      serialized_obj += SerializeString((*i).c_str());
      i++;
   }
   serialized_obj += ")";
   if (_Parameters.size() > 0) {
		serialized_obj += "P(";
		i = _Parameters.cbegin();
		while (i != _Parameters.cend()) {
			if (i != _Parameters.cbegin()) serialized_obj += ",";
			serialized_obj += SerializeString((*i).c_str());
			i++;
		}
		serialized_obj += ")";
	   if (_ParameterValues.size() > 0) {
			serialized_obj += "PV(";
			i = _ParameterValues.cbegin();
			while (i != _ParameterValues.cend()) {
				if (i != _ParameterValues.cbegin()) serialized_obj += ",";
				serialized_obj += SerializeString((*i).c_str());
				i++;
			}
			serialized_obj += ")";
		}
	   if (_Flags.size() > 0) {
			serialized_obj += "PF(";
			i = _Flags.begin();
			while (i != _Flags.cend()) {
				if (i != _Flags.cbegin()) serialized_obj += ",";
				serialized_obj += SerializeString((*i).c_str());
				i++;
			}
			serialized_obj += ")";
		}
	}
   return serialized_obj;
  //## end cTransferObject::Serialize%1046095005.body
}

STRING_VECTOR_T * cTransferObject::GetVec (AreaType area, ULONG_T index)
{
  //## begin cTransferObject::GetVec%1047469646.body preserve=yes
	STRING_VECTOR_T * vec;
	if (area == ObjectHeader) {
		vec = &_Header;
	} else if (area == ObjectBody) {
		vec = &_Body;
	} else if (area == ObjectParams) {
		vec = &_Parameters;
	} else if (area == ObjectParamValues) {
		vec = &_ParameterValues;
	} else if (area == ObjectFlags) {
		vec = &_Flags;
	} else {
_ASSERT_UNCOND
	}
	if (index >= vec->size()) {
		vec->resize(index + 1);
	}
	return vec;
  //## end cTransferObject::GetVec%1047469646.body
}

STRING_VECTOR_T * cTransferObject::GetVec (AreaType area)
{
  //## begin cTransferObject::GetVec%1047469647.body preserve=yes
	STRING_VECTOR_T * vec;
	if (area == ObjectHeader) {
		vec = &_Header;
	} else if (area == ObjectBody) {
		vec = &_Body;
	} else if (area == ObjectParams) {
		vec = &_Parameters;
	} else if (area == ObjectParamValues) {
		vec = &_ParameterValues;
	} else if (area == ObjectFlags) {
		vec = &_Flags;
	} else {
_ASSERT_UNCOND
	}
	return vec;
  //## end cTransferObject::GetVec%1047469647.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cTransferObject::get_Type () const
{
  //## begin cTransferObject::get_Type%3E703CFF008C.get preserve=no
  return _Type;
  //## end cTransferObject::get_Type%3E703CFF008C.get
}

void cTransferObject::set_Type (INT_T value)
{
  //## begin cTransferObject::set_Type%3E703CFF008C.set preserve=no
  _Type = value;
  //## end cTransferObject::set_Type%3E703CFF008C.set
}

INT_T cTransferObject::get_SubType () const
{
  //## begin cTransferObject::get_SubType%3FBF5D980177.get preserve=no
  return _SubType;
  //## end cTransferObject::get_SubType%3FBF5D980177.get
}

void cTransferObject::set_SubType (INT_T value)
{
  //## begin cTransferObject::set_SubType%3FBF5D980177.set preserve=no
  _SubType = value;
  //## end cTransferObject::set_SubType%3FBF5D980177.set
}

// Additional Declarations
  //## begin cTransferObject%3E5A568D005E.declarations preserve=yes
  //## end cTransferObject%3E5A568D005E.declarations

//## begin module%3E5A568D005E.epilog preserve=yes
//## end module%3E5A568D005E.epilog
