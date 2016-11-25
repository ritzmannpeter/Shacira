//## begin module%3AB878F3028A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB878F3028A.cm

//## begin module%3AB878F3028A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AB878F3028A.cp

//## Module: cLogFile%3AB878F3028A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cLogFile.cpp

//## begin module%3AB878F3028A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AB878F3028A.additionalIncludes

//## begin module%3AB878F3028A.includes preserve=yes
//## end module%3AB878F3028A.includes

// cTokenizer
#include "System/cTokenizer.h"
// cLogFile
#include "System/cLogFile.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3AB878F3028A.additionalDeclarations preserve=yes

#define VA_BUF_SIZE      0x4000
#ifdef CLOSE_ON_IDLE
#define CHECK_STREAM(stream)
#else
#define CHECK_STREAM(stream) \
if (stream == NULL) { \
   throw cError(LOGFILE_NO_STREAM, 0, _File.c_str()); \
}
#endif

//## end module%3AB878F3028A.additionalDeclarations


// Class cLogFile 









cLogFile::cLogFile()
  //## begin cLogFile::cLogFile%.hasinit preserve=no
      : _Stream(NULL), _IsNewFile(true), _IsNewDir(true), _ReadOnly(false)
  //## end cLogFile::cLogFile%.hasinit
  //## begin cLogFile::cLogFile%.initialization preserve=yes
  //## end cLogFile::cLogFile%.initialization
{
  //## begin cLogFile::cLogFile%.body preserve=yes
   set_Name("UnnamedLogFile");
  //## end cLogFile::cLogFile%.body
}

cLogFile::cLogFile(const cLogFile &right)
  //## begin cLogFile::cLogFile%copy.hasinit preserve=no
      : _Stream(NULL), _IsNewFile(true), _IsNewDir(true), _ReadOnly(false)
  //## end cLogFile::cLogFile%copy.hasinit
  //## begin cLogFile::cLogFile%copy.initialization preserve=yes
  //## end cLogFile::cLogFile%copy.initialization
{
  //## begin cLogFile::cLogFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cLogFile::cLogFile%copy.body
}

cLogFile::cLogFile (CONST_STRING_T file, BOOL_T read_only)
  //## begin cLogFile::cLogFile%985174332.hasinit preserve=no
      : _Stream(NULL), _IsNewFile(true), _IsNewDir(true), _ReadOnly(false)
  //## end cLogFile::cLogFile%985174332.hasinit
  //## begin cLogFile::cLogFile%985174332.initialization preserve=yes
  //## end cLogFile::cLogFile%985174332.initialization
{
  //## begin cLogFile::cLogFile%985174332.body preserve=yes
   set_Name(file);
   _ReadOnly = read_only;
   _File = cFileSystemUtils::FullPath(file);
   cFileSystemUtils::RightSplit(_File.c_str(), _Directory, _FileName);
   if (cFileSystemUtils::DirExists(_Directory.c_str())) {
      _IsNewDir = false;
   } else {
      CreateDir(_Directory.c_str());
      _IsNewDir = true;
   }
   if (cFileSystemUtils::FileExists(_File.c_str())) {
      _IsNewFile = false;
   } else {
      _IsNewFile = true;
   }
   SetReadOnly(false);
#ifdef CLOSE_ON_IDLE
#else
   _Stream = fopen(_File.c_str(), "a");
   if (_Stream == NULL) {
      throw cError(LOGFILE_OPEN, errno, _File.c_str());
   } else {
      setbuf(_Stream, NULL);
   }
#endif
  //## end cLogFile::cLogFile%985174332.body
}


cLogFile::~cLogFile()
{
  //## begin cLogFile::~cLogFile%.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   if (_Stream != NULL) fclose(_Stream);
   SetReadOnly(true);
  //## end cLogFile::~cLogFile%.body
}



//## Other Operations (implementation)
BOOL_T cLogFile::Printf (CONST_STRING_T fmt_str, ... )
{
  //## begin cLogFile::Printf%985174333.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   va_list args;
   static char text[VA_BUF_SIZE] = {0};
   va_start(args, fmt_str);
   _vsnprintf(text, sizeof(text)-1, fmt_str, args);
   va_end(args);
#ifdef CLOSE_ON_IDLE
   BOOL_T success = false;
   FILE * stream = NULL;
   stream = fopen(_File.c_str(), "a");
   if (stream != NULL) {
      if (fprintf(stream, "%s", text) != EOF) {
         success = true;
	  }
      fclose(stream);
      return success;
   } else {
	  return false;
   }
#else
   if (fprintf(_Stream, "%s", text) == EOF) {
      return false;
   } else {
      return true;
   }
#endif
  //## end cLogFile::Printf%985174333.body
}

BOOL_T cLogFile::LogPrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cLogFile::LogPrintf%985174334.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   va_list args;
   static char text[VA_BUF_SIZE] = {0};
   va_start(args, fmt_str);
   _vsnprintf(text, sizeof(text)-1, fmt_str, args);
   va_end(args);
   _Time.Now();
#ifdef CLOSE_ON_IDLE
   BOOL_T success = false;
   FILE * stream = NULL;
   stream = fopen(_File.c_str(), "a");
   if (stream != NULL) {
      if (fprintf(stream, "%02.2d.%02.2d.%04.4d %02.2d:%02.2d:%02.2d %s",
                 (int)_Time.Get(cTimeObject::DAY),
                 (int)_Time.Get(cTimeObject::MONTH),
                 (int)_Time.Get(cTimeObject::YEAR),
                 (int)_Time.Get(cTimeObject::HOUR),
                 (int)_Time.Get(cTimeObject::MINUTE),
                 (int)_Time.Get(cTimeObject::SECOND),
                 text) != EOF) {
         success = true;
	  }
      fclose(stream);
      return success;
   } else {
	  return false;
   }
#else
   if (fprintf(_Stream, "%02.2d.%02.2d.%04.4d %02.2d:%02.2d:%02.2d %s",
               (int)_Time.Get(cTimeObject::DAY),
               (int)_Time.Get(cTimeObject::MONTH),
               (int)_Time.Get(cTimeObject::YEAR),
               (int)_Time.Get(cTimeObject::HOUR),
               (int)_Time.Get(cTimeObject::MINUTE),
               (int)_Time.Get(cTimeObject::SECOND),
               text) == EOF) {
      return false;
   } else {
      return true;
   }
#endif
  //## end cLogFile::LogPrintf%985174334.body
}

BOOL_T cLogFile::IsNewFile ()
{
  //## begin cLogFile::IsNewFile%985174353.body preserve=yes
   return _IsNewFile;
  //## end cLogFile::IsNewFile%985174353.body
}

BOOL_T cLogFile::IsNewDir ()
{
  //## begin cLogFile::IsNewDir%985174336.body preserve=yes
   return _IsNewDir;
  //## end cLogFile::IsNewDir%985174336.body
}

BOOL_T cLogFile::CreateDir (CONST_STRING_T dir)
{
  //## begin cLogFile::CreateDir%985174337.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   BOOL_T success = cFileSystemUtils::CreateDir(dir);
   return success;
  //## end cLogFile::CreateDir%985174337.body
}

BOOL_T cLogFile::SetReadOnly (BOOL_T read_only)
{
  //## begin cLogFile::SetReadOnly%985197430.body preserve=yes
#if defined(_WIN32)
   cObjectLock __lock__(&_LockMutex);
   DWORD attributes = GetFileAttributes(_File.c_str());
   if (read_only) {
      if (!_ReadOnly) return true;
      if (attributes & FILE_ATTRIBUTE_READONLY) {
         return true;
      } else {
         attributes |= FILE_ATTRIBUTE_READONLY;
         return (BOOL_T)SetFileAttributes(_File.c_str(), attributes);
      }
   } else {
      if (attributes & FILE_ATTRIBUTE_READONLY) {
         attributes &= (~FILE_ATTRIBUTE_READONLY);
         return (BOOL_T)SetFileAttributes(_File.c_str(), attributes);
      } else {
         return true;
      }
   }
#elif defined(__linux__)
PORT_LEVEL_3
   return false;
#else
NO_PLATFORM
#endif
  //## end cLogFile::SetReadOnly%985197430.body
}

// Additional Declarations
  //## begin cLogFile%3AB878F3028A.declarations preserve=yes
  //## end cLogFile%3AB878F3028A.declarations

//## begin module%3AB878F3028A.epilog preserve=yes
//## end module%3AB878F3028A.epilog
