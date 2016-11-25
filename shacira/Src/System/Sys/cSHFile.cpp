//## begin module%3E9EF7DD02AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E9EF7DD02AF.cm

//## begin module%3E9EF7DD02AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E9EF7DD02AF.cp

//## Module: cSHFile%3E9EF7DD02AF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSHFile.cpp

//## begin module%3E9EF7DD02AF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E9EF7DD02AF.additionalIncludes

//## begin module%3E9EF7DD02AF.includes preserve=yes
//## end module%3E9EF7DD02AF.includes

// cTimeObject
#include "System/cTimeObject.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3E9EF7DD02AF.additionalDeclarations preserve=yes

/// PR 07.04.09 - added printf statements that are more safe with respect to buffer overflows
/// PR 02.03.11 - made ::ReadLine(STRING_T &) thread safe and unlimited in buffer size
///               made ::Printf(..) thread safe

#define WRITE_BUFFER_SIZE	0x8000

//## end module%3E9EF7DD02AF.additionalDeclarations


// Class cSHFile 




cSHFile::cSHFile()
  //## begin cSHFile::cSHFile%.hasinit preserve=no
      : _Stream(NULL)
  //## end cSHFile::cSHFile%.hasinit
  //## begin cSHFile::cSHFile%.initialization preserve=yes
  //## end cSHFile::cSHFile%.initialization
{
  //## begin cSHFile::cSHFile%.body preserve=yes
_ASSERT_UNCOND
  //## end cSHFile::cSHFile%.body
}

cSHFile::cSHFile(const cSHFile &right)
  //## begin cSHFile::cSHFile%copy.hasinit preserve=no
      : _Stream(NULL)
  //## end cSHFile::cSHFile%copy.hasinit
  //## begin cSHFile::cSHFile%copy.initialization preserve=yes
  //## end cSHFile::cSHFile%copy.initialization
{
  //## begin cSHFile::cSHFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSHFile::cSHFile%copy.body
}

cSHFile::cSHFile (CONST_STRING_T file_name)
  //## begin cSHFile::cSHFile%1050605979.hasinit preserve=no
      : _Stream(NULL)
  //## end cSHFile::cSHFile%1050605979.hasinit
  //## begin cSHFile::cSHFile%1050605979.initialization preserve=yes
  //## end cSHFile::cSHFile%1050605979.initialization
{
  //## begin cSHFile::cSHFile%1050605979.body preserve=yes
	_Path = cFileSystemUtils::FullPath(file_name);
  //## end cSHFile::cSHFile%1050605979.body
}


cSHFile::~cSHFile()
{
  //## begin cSHFile::~cSHFile%.body preserve=yes
	Close();
  //## end cSHFile::~cSHFile%.body
}


const cSHFile & cSHFile::operator=(const cSHFile &right)
{
  //## begin cSHFile::operator=%.body preserve=yes
  return *this;
  //## end cSHFile::operator=%.body
}



//## Other Operations (implementation)
BOOL_T cSHFile::Open (ULONG_T flags)
{
  //## begin cSHFile::Open%1050605980.body preserve=yes
	if (flags & FILE_ACCESS_APPEND) {
		_Stream = fopen(_Path.c_str(), "a");
	} else {
		if (flags & FILE_ACCESS_READ_ONLY) {
			if (flags & FILE_MODE_BINARY) {
				_Stream = fopen(_Path.c_str(), "rb");
			} else {
				_Stream = fopen(_Path.c_str(), "r");
			}
		} else {
			if (flags & FILE_MODE_BINARY) {
            if (flags & FILE_MODE_CREATE) {
               _Stream = fopen(_Path.c_str(), "wb+");
            } else {
               _Stream = fopen(_Path.c_str(), "rb+");
            }
			} else {
            if (flags & FILE_MODE_CREATE) {
   				_Stream = fopen(_Path.c_str(), "w+");
            } else {
   				_Stream = fopen(_Path.c_str(), "r+");
            }
			}
		}
	}
   if (_Stream == NULL) {
      return false;
   } else {
      return true;
   }
  //## end cSHFile::Open%1050605980.body
}

void cSHFile::Close ()
{
  //## begin cSHFile::Close%1050605981.body preserve=yes
	UnLock();
	if (_Stream != NULL) {
		fclose(_Stream);
      _Stream = NULL;
	}
  //## end cSHFile::Close%1050605981.body
}

BOOL_T cSHFile::Seek (ULONG_T pos)
{
  //## begin cSHFile::Seek%1077548355.body preserve=yes
	if (_Stream == NULL) return false;
   ULONG_T new_pos = fseek(_Stream, pos, SEEK_SET);
   new_pos = ftell(_Stream);
	return (pos == new_pos);
  //## end cSHFile::Seek%1077548355.body
}

BOOL_T cSHFile::SeekEnd ()
{
  //## begin cSHFile::SeekEnd%1135258641.body preserve=yes
	if (_Stream == NULL) return false;
   ULONG_T new_pos = fseek(_Stream, 0, SEEK_END);
	return true;
  //## end cSHFile::SeekEnd%1135258641.body
}

BOOL_T cSHFile::Rewind ()
{
  //## begin cSHFile::Rewind%1135258642.body preserve=yes
	if (_Stream == NULL) return false;
   ULONG_T new_pos = fseek(_Stream, 0, SEEK_SET);
   new_pos = ftell(_Stream);
	return (0 == new_pos);
  //## end cSHFile::Rewind%1135258642.body
}

ULONG_T cSHFile::Read (void *buf, ULONG_T buf_size, ULONG_T bytes)
{
  //## begin cSHFile::Read%1050605982.body preserve=yes
	if (_Stream == NULL) return 0;
   ULONG_T nread = fread(buf, 1, bytes, _Stream);
	return nread;
  //## end cSHFile::Read%1050605982.body
}

BOOL_T cSHFile::ReadLine (STRING_BUF_T buf, ULONG_T buf_size)
{
  //## begin cSHFile::ReadLine%1050605983.body preserve=yes
   if (_Stream == NULL) return false;
   ULONG_T nread = 0;
   int c = fgetc(_Stream);
   if (c == EOF) return false;
      while (c != '\n' && c != EOF) {
      if (nread >= buf_size-1) {
         return true;
      }
      buf[nread] = c;
      nread++;
      c = fgetc(_Stream);
   }
   buf[nread] = 0;
   return true;
  //## end cSHFile::ReadLine%1050605983.body
}

STRING_T cSHFile::ToString ()
{
  //## begin cSHFile::ToString%1090486621.body preserve=yes
   STRING_T content;
   ULONG_T file_size = Size();
   char buf[0x20];
   if (Open()) {
      memset(buf, 0, sizeof(buf));
      int nread = Read(buf, sizeof(buf)-1, sizeof(buf)-1);
      while (nread > 0) {
         content += buf;
         memset(buf, 0, sizeof(buf));
         nread = Read(buf, sizeof(buf)-1, sizeof(buf)-1);
      }
      Close();
   }
   return content;
  //## end cSHFile::ToString%1090486621.body
}

ULONG_T cSHFile::Write (void *buf, ULONG_T bytes)
{
  //## begin cSHFile::Write%1053510999.body preserve=yes
   if (_Stream == NULL) return false;
   ULONG_T nwrite = fwrite(buf, 1, bytes, _Stream);
   return nwrite;
  //## end cSHFile::Write%1053510999.body
}

BOOL_T cSHFile::WriteBlock (void *buf, ULONG_T bytes)
{
  //## begin cSHFile::WriteBlock%1108486027.body preserve=yes
   if (_Stream == NULL) return false;
   ULONG_T nwrite = fwrite(buf, 1, bytes, _Stream);
   return (nwrite < bytes) ? false : true;
  //## end cSHFile::WriteBlock%1108486027.body
}

BOOL_T cSHFile::ReadLine (STRING_T &buf)
{
  //## begin cSHFile::ReadLine%1051885629.body preserve=yes
   if (_Stream == NULL) return false;
   buf = "";
   ULONG_T nread = 0;
   int c = fgetc(_Stream);
   if (c == EOF) return false;
   while (c != '\n' && c != EOF) {
      buf += c;
      nread++;
      c = fgetc(_Stream);
   }
   return true;
  //## end cSHFile::ReadLine%1051885629.body
}

void cSHFile::Printf (CONST_STRING_T fmt_str, ... )
{
  //## begin cSHFile::Printf%1050605984.body preserve=yes
   if (_Stream == NULL) return;
   char * text = (char*)cSystemUtils::Alloc(WRITE_BUFFER_SIZE);
   va_list args;
   va_start(args, fmt_str);
   int nprint = _vsnprintf(text, WRITE_BUFFER_SIZE - 1, fmt_str, args);
   va_end(args);
   Write(text, strlen(text));
   cSystemUtils::Free(text);
  //## end cSHFile::Printf%1050605984.body
}

void cSHFile::Lock ()
{
  //## begin cSHFile::Lock%1050605985.body preserve=yes
  //## end cSHFile::Lock%1050605985.body
}

void cSHFile::UnLock ()
{
  //## begin cSHFile::UnLock%1050605986.body preserve=yes
  //## end cSHFile::UnLock%1050605986.body
}

BOOL_T cSHFile::Exists ()
{
  //## begin cSHFile::Exists%1050605987.body preserve=yes
	return cFileSystemUtils::FileExists(_Path.c_str());
  //## end cSHFile::Exists%1050605987.body
}

void cSHFile::Remove ()
{
  //## begin cSHFile::Remove%1050605988.body preserve=yes
	if (Exists()) {
		remove(_Path.c_str());
	}
  //## end cSHFile::Remove%1050605988.body
}

void cSHFile::Move (CONST_STRING_T location)
{
  //## begin cSHFile::Move%1106850060.body preserve=yes
	if (Exists()) {
		rename(_Path.c_str(), location);
	}
  //## end cSHFile::Move%1106850060.body
}

STRING_T cSHFile::Path ()
{
  //## begin cSHFile::Path%1050605989.body preserve=yes
	return _Path;
  //## end cSHFile::Path%1050605989.body
}

ULONG_T cSHFile::Size ()
{
  //## begin cSHFile::Size%1053511000.body preserve=yes
#if defined(_WIN32)
   HANDLE fhnd = CreateFile(
                      _Path.c_str(),                         // file name
                      GENERIC_READ,                      // access mode
                      0,                          // share mode
                      NULL,                              // SD
                      OPEN_EXISTING,                // how to create
                      FILE_ATTRIBUTE_NORMAL,                 // file attributes
                      NULL                       // handle to template file
                           );
   if (fhnd != INVALID_HANDLE_VALUE) {
      DWORD size = GetFileSize(fhnd, NULL);
      CloseHandle(fhnd);
      return size;
   } else {
      return 0;
   }
#elif defined(__linux__)
PORT_LEVEL_5
   return cFileSystemUtils::FileSize(_Path.c_str());
#else
NO_PLATFORM
#endif
  //## end cSHFile::Size%1053511000.body
}

ULONG_T cSHFile::Time (ULONG_T ctrl)
{
  //## begin cSHFile::Time%1102005112.body preserve=yes
#if defined(_WIN32)
   FILETIME file_time;
   file_time.dwLowDateTime = 0;
   file_time.dwHighDateTime = 0;
   HANDLE handle = CreateFile(_Path.c_str(),
                              GENERIC_READ,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      cTimeObject time_object;
      FILETIME created;
      FILETIME accessed;
      if (GetFileTime(handle, &created, &accessed, &file_time)) {
         SYSTEMTIME sys_time = {0};
         FILETIME local_file_time;
         if (FileTimeToLocalFileTime(&file_time, &local_file_time)) {
         } else {
            local_file_time = file_time;
         }
         if (FileTimeToSystemTime(&local_file_time, &sys_time)) {
            time_object.Set(cTimeObject::YEAR, sys_time.wYear);
            time_object.Set(cTimeObject::MONTH, sys_time.wMonth);
            time_object.Set(cTimeObject::DAY, sys_time.wDay);
            time_object.Set(cTimeObject::HOUR, sys_time.wHour);
            time_object.Set(cTimeObject::MINUTE, sys_time.wMinute);
            time_object.Set(cTimeObject::SECOND, sys_time.wSecond);
         }
      }
      CloseHandle(handle);
      return (ULONG_T)time_object;
   } else {
      return 0;
   }
#elif defined(__linux__)
PORT_LEVEL_3
   return 0;
#else
NO_PLATFORM
#endif
  //## end cSHFile::Time%1102005112.body
}

void cSHFile::SetReadOnly (BOOL_T read_only)
{
  //## begin cSHFile::SetReadOnly%1053513442.body preserve=yes
#if defined(_WIN32)
   DWORD attributes = GetFileAttributes(_Path.c_str());
   if (read_only) {
      if (!(attributes & FILE_ATTRIBUTE_READONLY)) {
         attributes |= FILE_ATTRIBUTE_READONLY;
         SetFileAttributes(_Path.c_str(), attributes);
      }
   } else {
      if (attributes & FILE_ATTRIBUTE_READONLY) {
         attributes &= (~FILE_ATTRIBUTE_READONLY);
         SetFileAttributes(_Path.c_str(), attributes);
      }
   }
#elif defined(__linux__)
   PORT_LEVEL_3
#else
NO_PLATFORM
#endif
  //## end cSHFile::SetReadOnly%1053513442.body
}

BOOL_T cSHFile::IsAsciiFile (CONST_STRING_T path)
{
  //## begin cSHFile::IsAsciiFile%1123070425.body preserve=yes
   FILE * stream = fopen(path, "r");
   if (stream != NULL) {
      int c = fgetc(stream);
      fclose(stream);
      if (c == EOF) {
         return true;
      } else if (c == 0) {
         return false;
      } else {
         return true;
      }
   } else {
      return true;
   }
  //## end cSHFile::IsAsciiFile%1123070425.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSHFile::get_Path () const
{
  //## begin cSHFile::get_Path%3E9EF83700CB.get preserve=no
  return _Path;
  //## end cSHFile::get_Path%3E9EF83700CB.get
}

// Additional Declarations
  //## begin cSHFile%3E9EF7DD02AF.declarations preserve=yes
  //## end cSHFile%3E9EF7DD02AF.declarations

//## begin module%3E9EF7DD02AF.epilog preserve=yes
//## end module%3E9EF7DD02AF.epilog
