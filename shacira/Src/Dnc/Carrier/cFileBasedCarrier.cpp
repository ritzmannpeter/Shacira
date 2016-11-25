//## begin module%3BA5B72D01AC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA5B72D01AC.cm

//## begin module%3BA5B72D01AC.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA5B72D01AC.cp

//## Module: cFileBasedCarrier%3BA5B72D01AC; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\Carrier\cFileBasedCarrier.cpp

//## begin module%3BA5B72D01AC.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BA5B72D01AC.additionalIncludes

//## begin module%3BA5B72D01AC.includes preserve=yes
//## end module%3BA5B72D01AC.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cFileBasedCarrier
#include "Dnc/Carrier/cFileBasedCarrier.h"
//## begin module%3BA5B72D01AC.additionalDeclarations preserve=yes

#define BLOCK_SIZE      1024

//## end module%3BA5B72D01AC.additionalDeclarations


// Class cFileBasedCarrier 




cFileBasedCarrier::cFileBasedCarrier()
  //## begin cFileBasedCarrier::cFileBasedCarrier%.hasinit preserve=no
      : _Size(-1)
  //## end cFileBasedCarrier::cFileBasedCarrier%.hasinit
  //## begin cFileBasedCarrier::cFileBasedCarrier%.initialization preserve=yes
  //## end cFileBasedCarrier::cFileBasedCarrier%.initialization
{
  //## begin cFileBasedCarrier::cFileBasedCarrier%.body preserve=yes
  //## end cFileBasedCarrier::cFileBasedCarrier%.body
}

cFileBasedCarrier::cFileBasedCarrier(const cFileBasedCarrier &right)
  //## begin cFileBasedCarrier::cFileBasedCarrier%copy.hasinit preserve=no
      : _Size(-1)
  //## end cFileBasedCarrier::cFileBasedCarrier%copy.hasinit
  //## begin cFileBasedCarrier::cFileBasedCarrier%copy.initialization preserve=yes
  //## end cFileBasedCarrier::cFileBasedCarrier%copy.initialization
{
  //## begin cFileBasedCarrier::cFileBasedCarrier%copy.body preserve=yes
  //## end cFileBasedCarrier::cFileBasedCarrier%copy.body
}

cFileBasedCarrier::cFileBasedCarrier (INT_T size)
  //## begin cFileBasedCarrier::cFileBasedCarrier%1000716056.hasinit preserve=no
      : _Size(-1)
  //## end cFileBasedCarrier::cFileBasedCarrier%1000716056.hasinit
  //## begin cFileBasedCarrier::cFileBasedCarrier%1000716056.initialization preserve=yes
  //## end cFileBasedCarrier::cFileBasedCarrier%1000716056.initialization
{
  //## begin cFileBasedCarrier::cFileBasedCarrier%1000716056.body preserve=yes
   if (size == 4 || size == 8 || size == 32 || size == 64) {
      _Size = size;
      char s_size[32] = {0};
      sprintf(s_size, "%d", size);
      _FileName = "Carrier";
      _FileName += s_size;
      _FileName += ".dmp";
      _Path = cFileSystemUtils::FullPath(_FileName.c_str());
      if (!cFileSystemUtils::FileExists(_FileName.c_str())) {
         CreateDump();
      }
   } else {
      throw cError(CARRIER_SIZE_NOT_SUPPORTED, 0);
   }
  //## end cFileBasedCarrier::cFileBasedCarrier%1000716056.body
}


cFileBasedCarrier::~cFileBasedCarrier()
{
  //## begin cFileBasedCarrier::~cFileBasedCarrier%.body preserve=yes
  //## end cFileBasedCarrier::~cFileBasedCarrier%.body
}



//## Other Operations (implementation)
LONG_T cFileBasedCarrier::Read (void *buffer, ULONG_T address, LONG_T amount)
{
  //## begin cFileBasedCarrier::Read%1000716053.body preserve=yes
   HANDLE handle = CreateFile(_Path.c_str(),
                              GENERIC_READ,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      Seek(handle, address);
      unsigned long nread = 0;
      BOOL_T success = ReadFile(handle, buffer, amount, &nread, NULL);
      CloseHandle(handle);
      if (!success) {
         throw cError(CARRIER_READ_ERROR, GetLastError());
      } else {
         return nread;
      }
   } else {
      throw cError(CARRIER_CREATE_ERROR);
   }
  //## end cFileBasedCarrier::Read%1000716053.body
}

LONG_T cFileBasedCarrier::Write (void *buffer, ULONG_T address, LONG_T amount)
{
  //## begin cFileBasedCarrier::Write%1000716054.body preserve=yes
   HANDLE handle = CreateFile(_Path.c_str(),
                              GENERIC_WRITE,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      Seek(handle, address);
      unsigned long nwrite = 0;
      BOOL_T success = WriteFile(handle, buffer, amount, &nwrite, NULL);
      CloseHandle(handle);
      if (success) {
         return nwrite;
      } else {
         throw cError(CARRIER_WRITE_ERROR, GetLastError());
#ifdef __MSCPP__
         return 0;
#endif
      }
   } else {
      throw cError(CARRIER_CREATE_ERROR, 0);
#ifdef __MSCPP__
      return 0;
#endif
   }
  //## end cFileBasedCarrier::Write%1000716054.body
}

LONG_T cFileBasedCarrier::Size ()
{
  //## begin cFileBasedCarrier::Size%1000716055.body preserve=yes
   return _Size;
  //## end cFileBasedCarrier::Size%1000716055.body
}

LONG_T cFileBasedCarrier::Seek (HANDLE handle, ULONG_T address)
{
  //## begin cFileBasedCarrier::Seek%1000716059.body preserve=yes
   unsigned long pos = SetFilePointer(handle, address, 0, FILE_BEGIN);
   return pos;
  //## end cFileBasedCarrier::Seek%1000716059.body
}

void cFileBasedCarrier::CreateDump ()
{
  //## begin cFileBasedCarrier::CreateDump%1000716058.body preserve=yes
   HANDLE handle = CreateFile(_Path.c_str(),
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      char buf[BLOCK_SIZE] = {0};
      unsigned long nwrite = 0;
      for (int i=0; i<_Size; i++) {
//         Seek(handle, (i*BLOCK_SIZE));
         BOOL_T success = WriteFile(handle, buf, BLOCK_SIZE, &nwrite, NULL);
         if (!success) {
            CloseHandle(handle);
            throw cError(CARRIER_WRITE_ERROR, GetLastError());
         }
      }
      CloseHandle(handle);
   } else {
      throw cError(CARRIER_CREATE_ERROR, 0);
   }
  //## end cFileBasedCarrier::CreateDump%1000716058.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cFileBasedCarrier::get_Size () const
{
  //## begin cFileBasedCarrier::get_Size%3BA5BE8400F0.get preserve=no
  return _Size;
  //## end cFileBasedCarrier::get_Size%3BA5BE8400F0.get
}

STRING_T cFileBasedCarrier::get_FileName () const
{
  //## begin cFileBasedCarrier::get_FileName%3BA5BCD20023.get preserve=no
  return _FileName;
  //## end cFileBasedCarrier::get_FileName%3BA5BCD20023.get
}

STRING_T cFileBasedCarrier::get_Path () const
{
  //## begin cFileBasedCarrier::get_Path%3BA5C01F006F.get preserve=no
  return _Path;
  //## end cFileBasedCarrier::get_Path%3BA5C01F006F.get
}

// Additional Declarations
  //## begin cFileBasedCarrier%3BA5B72D01AC.declarations preserve=yes
  //## end cFileBasedCarrier%3BA5B72D01AC.declarations

//## begin module%3BA5B72D01AC.epilog preserve=yes
//## end module%3BA5B72D01AC.epilog
