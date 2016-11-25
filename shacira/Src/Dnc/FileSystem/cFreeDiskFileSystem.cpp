//## begin module%3BA0AC11001E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA0AC11001E.cm

//## begin module%3BA0AC11001E.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA0AC11001E.cp

//## Module: cFreeDiskFileSystem%3BA0AC11001E; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFreeDiskFileSystem.cpp

//## begin module%3BA0AC11001E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BA0AC11001E.additionalIncludes

//## begin module%3BA0AC11001E.includes preserve=yes
//## end module%3BA0AC11001E.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cFreeDiskSource
#include "Dnc/FileSystem/cFreeDiskSource.h"
// cFreeDiskFileSystem
#include "Dnc/FileSystem/cFreeDiskFileSystem.h"
//## begin module%3BA0AC11001E.additionalDeclarations preserve=yes
//## end module%3BA0AC11001E.additionalDeclarations


// Class cFreeDiskFileSystem 

cFreeDiskFileSystem::cFreeDiskFileSystem()
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%.hasinit preserve=no
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%.hasinit
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%.initialization preserve=yes
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%.initialization
{
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%.body preserve=yes
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%.body
}

cFreeDiskFileSystem::cFreeDiskFileSystem(const cFreeDiskFileSystem &right)
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%copy.hasinit preserve=no
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%copy.hasinit
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%copy.initialization preserve=yes
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%copy.initialization
{
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%copy.body preserve=yes
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%copy.body
}

cFreeDiskFileSystem::cFreeDiskFileSystem (cFreeDiskSource *file_source, CONST_STRING_T path)
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.hasinit preserve=no
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.hasinit
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.initialization preserve=yes
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.initialization
{
  //## begin cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.body preserve=yes
   _Path = path;
  //## end cFreeDiskFileSystem::cFreeDiskFileSystem%1000369128.body
}


cFreeDiskFileSystem::~cFreeDiskFileSystem()
{
  //## begin cFreeDiskFileSystem::~cFreeDiskFileSystem%.body preserve=yes
  //## end cFreeDiskFileSystem::~cFreeDiskFileSystem%.body
}



//## Other Operations (implementation)
INT_T cFreeDiskFileSystem::Format (INT_T format)
{
  //## begin cFreeDiskFileSystem::Format%1000369129.body preserve=yes
  //## end cFreeDiskFileSystem::Format%1000369129.body
}

INT_T cFreeDiskFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cFreeDiskFileSystem::Directory%1000369130.body preserve=yes
   if (cFileSystemUtils::FileList(_Path.c_str(), file_names)) {
      return 0;
   } else {
      return FSYS_FAILED_TO_CREATE_DIRECTORY;
   }
  //## end cFreeDiskFileSystem::Directory%1000369130.body
}

LONG_T cFreeDiskFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cFreeDiskFileSystem::Load%1000369131.body preserve=yes
   STRING_T path = cFileSystemUtils::AppendPath(_Path.c_str(), file_name);
/*
   HANDLE handle = CreateFile(path.c_str(),
                              GENERIC_READ,
                              0, NULL,
                              0,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
*/
   HANDLE handle = CreateFile(path.c_str(),
                              GENERIC_READ,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      unsigned long file_size = GetFileSize(handle, NULL);
      if (file_size == 0xFFFFFFFF) {
         CloseHandle(handle);
         return FILE_SIZE_ERROR;
      }
      if (file_size > buf_size) {
         CloseHandle(handle);
         return FILE_BUF_TOO_SMALL;
      }
      unsigned long nread = 0;
      BOOL_T success = ReadFile(handle, buf, file_size, &nread, NULL);
      CloseHandle(handle);
      if (success) {
         return nread;
      } else {
         return FILE_READ_ERROR;
      }
   } else {
      return FILE_CREATE_ERROR;
   }
  //## end cFreeDiskFileSystem::Load%1000369131.body
}

LONG_T cFreeDiskFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cFreeDiskFileSystem::Save%1000369132.body preserve=yes
   STRING_T path = cFileSystemUtils::AppendPath(_Path.c_str(), file_name);
   HANDLE handle = CreateFile(path.c_str(),
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      unsigned long nwrite = 0;
      BOOL_T success = WriteFile(handle, buf, size, &nwrite, NULL);
      CloseHandle(handle);
      if (success) {
         return nwrite;
      } else {
         return FILE_WRITE_ERROR;
      }
   } else {
      return FILE_CREATE_ERROR;
   }
  //## end cFreeDiskFileSystem::Save%1000369132.body
}

INT_T cFreeDiskFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cFreeDiskFileSystem::Delete%1000369133.body preserve=yes
  //## end cFreeDiskFileSystem::Delete%1000369133.body
}

LONG_T cFreeDiskFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cFreeDiskFileSystem::FileSize%1000386732.body preserve=yes
   STRING_T path = cFileSystemUtils::AppendPath(_Path.c_str(), file_name);
   HANDLE handle = CreateFile(path.c_str(),
                              0,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      unsigned long file_size = GetFileSize(handle, NULL);
      CloseHandle(handle);
      if (file_size == 0xFFFFFFFF) {
         return FILE_SIZE_ERROR;
      } else {
         return file_size;
      }
   } else {
      return FILE_CREATE_ERROR;
   }
  //## end cFreeDiskFileSystem::FileSize%1000386732.body
}

cFile * cFreeDiskFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cFreeDiskFileSystem::File%1000386733.body preserve=yes
   return new cFreeFile(file_name, this);
  //## end cFreeDiskFileSystem::File%1000386733.body
}

cTimeObject cFreeDiskFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cFreeDiskFileSystem::GetTime%1000456414.body preserve=yes
   cTimeObject time;
   time.Set(cTimeObject::DAY, 0);
   time.Set(cTimeObject::MONTH, 0);
   time.Set(cTimeObject::YEAR, 0);
   time.Set(cTimeObject::MSECOND, 0);
   time.Set(cTimeObject::SECOND, 0);
   time.Set(cTimeObject::MINUTE, 0);
   time.Set(cTimeObject::HOUR, 0);
   STRING_T path = cFileSystemUtils::AppendPath(_Path.c_str(), file_name);
   HANDLE handle = CreateFile(path.c_str(),
                              0,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      FILETIME created = {0};
      FILETIME last_accessed = {0};
      FILETIME last_written = {0};
      BOOL_T success =  GetFileTime(handle, &created, &last_accessed, &last_written);
      if (success) {
         SYSTEMTIME system_time = {0};
         success = FileTimeToSystemTime(&created, &system_time);
         if (success) {
            unsigned int year = system_time.wYear;
            unsigned int month = system_time.wMonth;
            unsigned int day = system_time.wDay;
            unsigned int hour = system_time.wHour;
            unsigned int minute = system_time.wMinute;
            unsigned int second = system_time.wSecond;
            unsigned int msecond = system_time.wMilliseconds;
            time.Set(cTimeObject::DAY, day);
            time.Set(cTimeObject::MONTH, month);
            time.Set(cTimeObject::YEAR, year);
            time.Set(cTimeObject::MSECOND, msecond);
            time.Set(cTimeObject::SECOND, second);
            time.Set(cTimeObject::MINUTE, minute);
            time.Set(cTimeObject::HOUR, hour);
         }
      }
      CloseHandle(handle);
   }
   return time;
  //## end cFreeDiskFileSystem::GetTime%1000456414.body
}

// Additional Declarations
  //## begin cFreeDiskFileSystem%3BA0AC11001E.declarations preserve=yes
  //## end cFreeDiskFileSystem%3BA0AC11001E.declarations

//## begin module%3BA0AC11001E.epilog preserve=yes
//## end module%3BA0AC11001E.epilog
