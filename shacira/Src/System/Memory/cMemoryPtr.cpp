//## begin module%3A4A1F5D0137.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A4A1F5D0137.cm

//## begin module%3A4A1F5D0137.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A4A1F5D0137.cp

//## Module: cMemoryPtr%3A4A1F5D0137; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Memory\cMemoryPtr.cpp

//## begin module%3A4A1F5D0137.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A4A1F5D0137.additionalIncludes

//## begin module%3A4A1F5D0137.includes preserve=yes
//## end module%3A4A1F5D0137.includes

// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
//## begin module%3A4A1F5D0137.additionalDeclarations preserve=yes
//## end module%3A4A1F5D0137.additionalDeclarations


// Class cMemoryPtr 



cMemoryPtr::cMemoryPtr()
  //## begin cMemoryPtr::cMemoryPtr%.hasinit preserve=no
      : _Buffer(NULL), _Size(0)
  //## end cMemoryPtr::cMemoryPtr%.hasinit
  //## begin cMemoryPtr::cMemoryPtr%.initialization preserve=yes
  //## end cMemoryPtr::cMemoryPtr%.initialization
{
  //## begin cMemoryPtr::cMemoryPtr%.body preserve=yes
  //## end cMemoryPtr::cMemoryPtr%.body
}

cMemoryPtr::cMemoryPtr(const cMemoryPtr &right)
  //## begin cMemoryPtr::cMemoryPtr%copy.hasinit preserve=no
      : _Buffer(NULL), _Size(0)
  //## end cMemoryPtr::cMemoryPtr%copy.hasinit
  //## begin cMemoryPtr::cMemoryPtr%copy.initialization preserve=yes
  //## end cMemoryPtr::cMemoryPtr%copy.initialization
{
  //## begin cMemoryPtr::cMemoryPtr%copy.body preserve=yes
   _Size = right._Size;
   _Buffer = (unsigned char *)cSystemUtils::Alloc(_Size);
   memcpy(_Buffer, (void*)right, _Size);
  //## end cMemoryPtr::cMemoryPtr%copy.body
}

cMemoryPtr::cMemoryPtr (ULONG_T size)
  //## begin cMemoryPtr::cMemoryPtr%977931300.hasinit preserve=no
      : _Buffer(NULL), _Size(0)
  //## end cMemoryPtr::cMemoryPtr%977931300.hasinit
  //## begin cMemoryPtr::cMemoryPtr%977931300.initialization preserve=yes
  //## end cMemoryPtr::cMemoryPtr%977931300.initialization
{
  //## begin cMemoryPtr::cMemoryPtr%977931300.body preserve=yes
   _Buffer = (unsigned char *)cSystemUtils::Alloc(size);
   _Size = size;
  //## end cMemoryPtr::cMemoryPtr%977931300.body
}


cMemoryPtr::~cMemoryPtr()
{
  //## begin cMemoryPtr::~cMemoryPtr%.body preserve=yes
   if (_Buffer != NULL) cSystemUtils::Free(_Buffer);
  //## end cMemoryPtr::~cMemoryPtr%.body
}



//## Other Operations (implementation)
ULONG_T cMemoryPtr::Size () const
{
  //## begin cMemoryPtr::Size%977931299.body preserve=yes
   return _Size;
  //## end cMemoryPtr::Size%977931299.body
}

void cMemoryPtr::Size (ULONG_T size)
{
  //## begin cMemoryPtr::Size%977993518.body preserve=yes
   unsigned char * old_buf = _Buffer;
   _Buffer = (unsigned char *)cSystemUtils::Alloc(size);
   _Size = size;
   if (old_buf != NULL) {
      cSystemUtils::Free(old_buf);
   }
  //## end cMemoryPtr::Size%977993518.body
}

void cMemoryPtr::AdjustSize (ULONG_T size, BOOL_T keep_data)
{
  //## begin cMemoryPtr::AdjustSize%1137931252.body preserve=yes
   if (size > _Size) {
      unsigned char * old_buf = _Buffer;
      ULONG_T old_size = size;
      _Buffer = (unsigned char *)cSystemUtils::Alloc(size);
      _Size = size;
      if (old_buf != NULL) {
         if (keep_data) {
            memcpy(_Buffer, old_buf, old_size);
         }
      }
      cSystemUtils::Free(old_buf);
   }
  //## end cMemoryPtr::AdjustSize%1137931252.body
}

void cMemoryPtr::Clear ()
{
  //## begin cMemoryPtr::Clear%977993522.body preserve=yes
   if (_Buffer != NULL) {
      memset(_Buffer, 0, _Size);
   }
  //## end cMemoryPtr::Clear%977993522.body
}

void * cMemoryPtr::Memory ()
{
  //## begin cMemoryPtr::Memory%1000308658.body preserve=yes
   return (void*)_Buffer;
  //## end cMemoryPtr::Memory%1000308658.body
}

cMemoryPtr::operator CHAR_T * () const
{
  //## begin cMemoryPtr::operator CHAR_T *%978080755.body preserve=yes
   return (char*)_Buffer;
  //## end cMemoryPtr::operator CHAR_T *%978080755.body
}

cMemoryPtr::operator UCHAR_T * () const
{
  //## begin cMemoryPtr::operator UCHAR_T *%978080756.body preserve=yes
   return (unsigned char*)_Buffer;
  //## end cMemoryPtr::operator UCHAR_T *%978080756.body
}

cMemoryPtr::operator void * () const
{
  //## begin cMemoryPtr::operator void *%978080757.body preserve=yes
   return (void*)_Buffer;
  //## end cMemoryPtr::operator void *%978080757.body
}

// Additional Declarations
  //## begin cMemoryPtr%3A4A1F5D0137.declarations preserve=yes
  //## end cMemoryPtr%3A4A1F5D0137.declarations

//## begin module%3A4A1F5D0137.epilog preserve=yes
//## end module%3A4A1F5D0137.epilog
