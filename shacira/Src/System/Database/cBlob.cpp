//## begin module%402C8232033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%402C8232033C.cm

//## begin module%402C8232033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%402C8232033C.cp

//## Module: cBlob%402C8232033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cBlob.cpp

//## begin module%402C8232033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%402C8232033C.additionalIncludes

//## begin module%402C8232033C.includes preserve=yes
//## end module%402C8232033C.includes

// cBlob
#include "System/Database/cBlob.h"
//## begin module%402C8232033C.additionalDeclarations preserve=yes
//## end module%402C8232033C.additionalDeclarations


// Class cBlob 



cBlob::cBlob()
  //## begin cBlob::cBlob%.hasinit preserve=no
      : _Buf(NULL), _BufSize(0)
  //## end cBlob::cBlob%.hasinit
  //## begin cBlob::cBlob%.initialization preserve=yes
  //## end cBlob::cBlob%.initialization
{
  //## begin cBlob::cBlob%.body preserve=yes
  //## end cBlob::cBlob%.body
}

cBlob::cBlob(const cBlob &right)
  //## begin cBlob::cBlob%copy.hasinit preserve=no
      : _Buf(NULL), _BufSize(0)
  //## end cBlob::cBlob%copy.hasinit
  //## begin cBlob::cBlob%copy.initialization preserve=yes
  //## end cBlob::cBlob%copy.initialization
{
  //## begin cBlob::cBlob%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBlob::cBlob%copy.body
}

cBlob::cBlob (BUF_T buf, ULONG_T buf_size)
  //## begin cBlob::cBlob%1076659058.hasinit preserve=no
      : _Buf(NULL), _BufSize(0)
  //## end cBlob::cBlob%1076659058.hasinit
  //## begin cBlob::cBlob%1076659058.initialization preserve=yes
  //## end cBlob::cBlob%1076659058.initialization
{
  //## begin cBlob::cBlob%1076659058.body preserve=yes
   _BufSize = buf_size;
   _Buf = new cMemoryPtr(_BufSize);
  //## end cBlob::cBlob%1076659058.body
}


cBlob::~cBlob()
{
  //## begin cBlob::~cBlob%.body preserve=yes
   DeleteBuf();
  //## end cBlob::~cBlob%.body
}



//## Other Operations (implementation)
STRING_T cBlob::Serialize ()
{
  //## begin cBlob::Serialize%1076659059.body preserve=yes
   STRING_T serialized_obj = "BLOB(";
   char size[64] = {0};
   SafePrintf(size, sizeof(size), "", _BufSize); // ??
   serialized_obj += size;
   serialized_obj += SerializeBuf().c_str();
   serialized_obj += ";";
   serialized_obj += ")";
   return serialized_obj;
  //## end cBlob::Serialize%1076659059.body
}

void cBlob::Construct (CONST_STRING_T serialized_object)
{
  //## begin cBlob::Construct%1076659060.body preserve=yes
   ULONG_T size = 0;
   ULONG_T n = 0;
   int params = sscanf(serialized_object, "BLOB(%d;%n", &size, &n);
   if (params == 1) {
      _BufSize = size;
      _Buf = new cMemoryPtr(_BufSize);
      CONST_STRING_T buf_ptr = serialized_object + n;
      ConstructBuf(buf_ptr);
   }
  //## end cBlob::Construct%1076659060.body
}

STRING_T cBlob::SerializeBuf ()
{
  //## begin cBlob::SerializeBuf%1076659061.body preserve=yes
   return "?";
  //## end cBlob::SerializeBuf%1076659061.body
}

void cBlob::ConstructBuf (CONST_STRING_T buf_ptr)
{
  //## begin cBlob::ConstructBuf%1076659062.body preserve=yes
  //## end cBlob::ConstructBuf%1076659062.body
}

void cBlob::DeleteBuf ()
{
  //## begin cBlob::DeleteBuf%1076659063.body preserve=yes
   DELETE_OBJECT(cMemoryPtr, _Buf)
  //## end cBlob::DeleteBuf%1076659063.body
}

// Additional Declarations
  //## begin cBlob%402C8232033C.declarations preserve=yes
  //## end cBlob%402C8232033C.declarations

//## begin module%402C8232033C.epilog preserve=yes
//## end module%402C8232033C.epilog
