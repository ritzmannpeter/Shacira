//## begin module%3E9EA7C2029F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E9EA7C2029F.cm

//## begin module%3E9EA7C2029F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E9EA7C2029F.cp

//## Module: cBlockBuffer%3E9EA7C2029F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cBlockBuffer.cpp

//## begin module%3E9EA7C2029F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E9EA7C2029F.additionalIncludes

//## begin module%3E9EA7C2029F.includes preserve=yes
//## end module%3E9EA7C2029F.includes

// cBlockBuffer
#include "System/Memory/cBlockBuffer.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
//## begin module%3E9EA7C2029F.additionalDeclarations preserve=yes
//## end module%3E9EA7C2029F.additionalDeclarations


// Class cBlockBuffer 


cBlockBuffer::cBlockBuffer()
  //## begin cBlockBuffer::cBlockBuffer%.hasinit preserve=no
  //## end cBlockBuffer::cBlockBuffer%.hasinit
  //## begin cBlockBuffer::cBlockBuffer%.initialization preserve=yes
  //## end cBlockBuffer::cBlockBuffer%.initialization
{
  //## begin cBlockBuffer::cBlockBuffer%.body preserve=yes
  //## end cBlockBuffer::cBlockBuffer%.body
}

cBlockBuffer::cBlockBuffer(const cBlockBuffer &right)
  //## begin cBlockBuffer::cBlockBuffer%copy.hasinit preserve=no
  //## end cBlockBuffer::cBlockBuffer%copy.hasinit
  //## begin cBlockBuffer::cBlockBuffer%copy.initialization preserve=yes
  //## end cBlockBuffer::cBlockBuffer%copy.initialization
{
  //## begin cBlockBuffer::cBlockBuffer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBlockBuffer::cBlockBuffer%copy.body
}


cBlockBuffer::~cBlockBuffer()
{
  //## begin cBlockBuffer::~cBlockBuffer%.body preserve=yes
	BUFFER_LIST_T::const_iterator i = _Buffers.cbegin();
	while (i != _Buffers.cend()) {
		void * buf = (*i);
		cSystemUtils::Free(buf);
		i++;
	}
  //## end cBlockBuffer::~cBlockBuffer%.body
}



//## Other Operations (implementation)
void * cBlockBuffer::AllocBlock (ULONG_T size)
{
  //## begin cBlockBuffer::AllocBlock%1050587414.body preserve=yes
	void * buf = cSystemUtils::Alloc(size);
	_Buffers.push_back(buf);
	return buf;
  //## end cBlockBuffer::AllocBlock%1050587414.body
}

CONST_STRING_T cBlockBuffer::AllocString (CONST_STRING_T str)
{
  //## begin cBlockBuffer::AllocString%1050584918.body preserve=yes
   ULONG_T len = cSHVariant::StrLen(str);
	void * buf = cSystemUtils::Alloc((len + 1) * sizeof(CHAR_T));
	memcpy(buf, str, len * sizeof(CHAR_T));
	_Buffers.push_back(buf);
	return (CONST_STRING_T)buf;
  //## end cBlockBuffer::AllocString%1050584918.body
}

CONST_WSTRING_T cBlockBuffer::AllocString (CONST_WSTRING_T str)
{
  //## begin cBlockBuffer::AllocString%1061824379.body preserve=yes
   ULONG_T len = cSHVariant::StrLen(str);
	void * buf = cSystemUtils::Alloc((len + 1) * sizeof(WCHAR_T));
	memcpy(buf, str, len * sizeof(WCHAR_T));
	_Buffers.push_back(buf);
	return (CONST_WSTRING_T)buf;
  //## end cBlockBuffer::AllocString%1061824379.body
}

// Additional Declarations
  //## begin cBlockBuffer%3E9EA7C2029F.declarations preserve=yes
  //## end cBlockBuffer%3E9EA7C2029F.declarations

//## begin module%3E9EA7C2029F.epilog preserve=yes
//## end module%3E9EA7C2029F.epilog
