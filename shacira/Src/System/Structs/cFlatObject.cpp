//## begin module%41413E860232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41413E860232.cm

//## begin module%41413E860232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41413E860232.cp

//## Module: cFlatObject%41413E860232; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cFlatObject.cpp

//## begin module%41413E860232.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41413E860232.additionalIncludes

//## begin module%41413E860232.includes preserve=yes
//## end module%41413E860232.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cFlatObject
#include "System/Structs/cFlatObject.h"
//## begin module%41413E860232.additionalDeclarations preserve=yes
//## end module%41413E860232.additionalDeclarations


// Class cFlatObject 




cFlatObject::cFlatObject()
  //## begin cFlatObject::cFlatObject%.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _ObjectValid(false)
  //## end cFlatObject::cFlatObject%.hasinit
  //## begin cFlatObject::cFlatObject%.initialization preserve=yes
  //## end cFlatObject::cFlatObject%.initialization
{
  //## begin cFlatObject::cFlatObject%.body preserve=yes
_ASSERT_UNCOND
  //## end cFlatObject::cFlatObject%.body
}

cFlatObject::cFlatObject(const cFlatObject &right)
  //## begin cFlatObject::cFlatObject%copy.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _ObjectValid(false)
  //## end cFlatObject::cFlatObject%copy.hasinit
  //## begin cFlatObject::cFlatObject%copy.initialization preserve=yes
  //## end cFlatObject::cFlatObject%copy.initialization
{
  //## begin cFlatObject::cFlatObject%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFlatObject::cFlatObject%copy.body
}

cFlatObject::cFlatObject (cVarRef *var_ref)
  //## begin cFlatObject::cFlatObject%1104332377.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _ObjectValid(false)
  //## end cFlatObject::cFlatObject%1104332377.hasinit
  //## begin cFlatObject::cFlatObject%1104332377.initialization preserve=yes
  //## end cFlatObject::cFlatObject%1104332377.initialization
{
  //## begin cFlatObject::cFlatObject%1104332377.body preserve=yes
   BUF_T data = NULL;
   var_ref->GetValue(data);
   ULONG_T data_size = var_ref->ValueSize();
   _Header = data;
   _Data = data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->flat_object_signature = FLAT_OBJECT_SIGNATURE;
   ((FLAT_OBJECT_HEADER_T*)_Header)->header_size = FLAT_OBJECT_HEADER_SIZE;
   ((FLAT_OBJECT_HEADER_T*)_Header)->data = _Data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->data_size = data_size;
   ((FLAT_OBJECT_HEADER_T*)_Header)->object_data = ((CHAR_T*)_Data) + FLAT_OBJECT_HEADER_SIZE;
   if (data_size < FLAT_OBJECT_HEADER_SIZE) {
      throw cError(FLAT_OBJECT_NO_SPACE, 0,
                   cConvUtils::StringValue(data_size).c_str(),
                   cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE).c_str());
   } else {
      ((FLAT_OBJECT_HEADER_T*)_Header)->object_data_size = data_size - FLAT_OBJECT_HEADER_SIZE;
   }
  //## end cFlatObject::cFlatObject%1104332377.body
}

cFlatObject::cFlatObject (PTR_T data, ULONG_T data_size)
  //## begin cFlatObject::cFlatObject%1094795547.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _ObjectValid(false)
  //## end cFlatObject::cFlatObject%1094795547.hasinit
  //## begin cFlatObject::cFlatObject%1094795547.initialization preserve=yes
  //## end cFlatObject::cFlatObject%1094795547.initialization
{
  //## begin cFlatObject::cFlatObject%1094795547.body preserve=yes
   _Header = data;
   _Data = data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->flat_object_signature = FLAT_OBJECT_SIGNATURE;
   ((FLAT_OBJECT_HEADER_T*)_Header)->header_size = FLAT_OBJECT_HEADER_SIZE;
   ((FLAT_OBJECT_HEADER_T*)_Header)->data = _Data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->data_size = data_size;
   ((FLAT_OBJECT_HEADER_T*)_Header)->object_data = ((CHAR_T*)_Data) + FLAT_OBJECT_HEADER_SIZE;
   if (data_size < FLAT_OBJECT_HEADER_SIZE) {
      throw cError(FLAT_OBJECT_NO_SPACE, 0,
                   cConvUtils::StringValue(data_size).c_str(),
                   cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE).c_str());
   } else {
      ((FLAT_OBJECT_HEADER_T*)_Header)->object_data_size = data_size - FLAT_OBJECT_HEADER_SIZE;
   }
  //## end cFlatObject::cFlatObject%1094795547.body
}

cFlatObject::cFlatObject (PTR_T data)
  //## begin cFlatObject::cFlatObject%1095144437.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _ObjectValid(false)
  //## end cFlatObject::cFlatObject%1095144437.hasinit
  //## begin cFlatObject::cFlatObject%1095144437.initialization preserve=yes
  //## end cFlatObject::cFlatObject%1095144437.initialization
{
  //## begin cFlatObject::cFlatObject%1095144437.body preserve=yes
   _Header = data;
   _Data = data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->data = _Data;
   ((FLAT_OBJECT_HEADER_T*)_Header)->object_data = ((CHAR_T*)_Data) + FLAT_OBJECT_HEADER_SIZE;
  //## end cFlatObject::cFlatObject%1095144437.body
}


cFlatObject::~cFlatObject()
{
  //## begin cFlatObject::~cFlatObject%.body preserve=yes
  //## end cFlatObject::~cFlatObject%.body
}



//## Other Operations (implementation)
PTR_T cFlatObject::GetHeader ()
{
  //## begin cFlatObject::GetHeader%1094795548.body preserve=yes
   return _Header;
  //## end cFlatObject::GetHeader%1094795548.body
}

ULONG_T cFlatObject::GetHeaderSize ()
{
  //## begin cFlatObject::GetHeaderSize%1094795549.body preserve=yes
   return FLAT_OBJECT_HEADER_SIZE;
  //## end cFlatObject::GetHeaderSize%1094795549.body
}

PTR_T cFlatObject::GetData ()
{
  //## begin cFlatObject::GetData%1094795550.body preserve=yes
   return _Data;
  //## end cFlatObject::GetData%1094795550.body
}

ULONG_T cFlatObject::GetDataSize ()
{
  //## begin cFlatObject::GetDataSize%1094795551.body preserve=yes
   return ((FLAT_OBJECT_HEADER_T*)_Header)->data_size;
  //## end cFlatObject::GetDataSize%1094795551.body
}

PTR_T cFlatObject::GetObjectData ()
{
  //## begin cFlatObject::GetObjectData%1094795552.body preserve=yes
   return ((FLAT_OBJECT_HEADER_T*)_Header)->object_data;
  //## end cFlatObject::GetObjectData%1094795552.body
}

ULONG_T cFlatObject::GetObjectDataSize ()
{
  //## begin cFlatObject::GetObjectDataSize%1094795553.body preserve=yes
   return ((FLAT_OBJECT_HEADER_T*)_Header)->object_data_size;
  //## end cFlatObject::GetObjectDataSize%1094795553.body
}

void cFlatObject::SetObjectName (CONST_STRING_T object_name)
{
  //## begin cFlatObject::SetObjectName%1110025033.body preserve=yes
   ULONG_T name_len = strlen(object_name);
   ULONG_T buf_size = OBJECT_NAME_LEN;
   int len = _MIN_(name_len, buf_size - 1);
   memcpy(((FLAT_OBJECT_HEADER_T*)_Header)->object_name, object_name, len);
   ((FLAT_OBJECT_HEADER_T*)_Header)->object_name[buf_size - 1] = 0;
  //## end cFlatObject::SetObjectName%1110025033.body
}

CONST_STRING_T cFlatObject::GetObjectName ()
{
  //## begin cFlatObject::GetObjectName%1110025034.body preserve=yes
STRING_T objn = ((FLAT_OBJECT_HEADER_T*)_Header)->object_name;
   return ((FLAT_OBJECT_HEADER_T*)_Header)->object_name;
  //## end cFlatObject::GetObjectName%1110025034.body
}

BOOL_T cFlatObject::IsValid ()
{
  //## begin cFlatObject::IsValid%1151501385.body preserve=yes
   return _ObjectValid;
  //## end cFlatObject::IsValid%1151501385.body
}

// Additional Declarations
  //## begin cFlatObject%41413E860232.declarations preserve=yes
  //## end cFlatObject%41413E860232.declarations

//## begin module%41413E860232.epilog preserve=yes
//## end module%41413E860232.epilog


