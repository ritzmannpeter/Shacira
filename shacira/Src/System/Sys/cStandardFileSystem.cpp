//## begin module%440802CA0370.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440802CA0370.cm

//## begin module%440802CA0370.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440802CA0370.cp

//## Module: cStandardFileSystem%440802CA0370; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cStandardFileSystem.cpp

//## begin module%440802CA0370.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%440802CA0370.additionalIncludes

//## begin module%440802CA0370.includes preserve=yes
//## end module%440802CA0370.includes

// cStandardFileSystem
#include "System/Sys/cStandardFileSystem.h"
// cSHFile
#include "System/Sys/cSHFile.h"
//## begin module%440802CA0370.additionalDeclarations preserve=yes

inline void GetErrorInfo(int & error, std::string & error_msg)
{
   error = 0;
   error_msg = "no error message";
#if defined(_WIN32)
   //Get the error message, if any.
   error = ::GetLastError();
   if (error == 0) {
      return;
   }
   char buf[0x255] = {0};
   DWORD size = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, sizeof(buf), NULL);
   int text_end = size - 2;
   if (text_end >= 0 &&
       text_end < sizeof(buf)) {
      buf[text_end] = 0;
   }
   error_msg = buf;
#endif
}

//## end module%440802CA0370.additionalDeclarations


// Class cStandardFileSystem 

cStandardFileSystem::cStandardFileSystem()
  //## begin cStandardFileSystem::cStandardFileSystem%.hasinit preserve=no
  //## end cStandardFileSystem::cStandardFileSystem%.hasinit
  //## begin cStandardFileSystem::cStandardFileSystem%.initialization preserve=yes
  //## end cStandardFileSystem::cStandardFileSystem%.initialization
{
  //## begin cStandardFileSystem::cStandardFileSystem%.body preserve=yes
  //## end cStandardFileSystem::cStandardFileSystem%.body
}

cStandardFileSystem::cStandardFileSystem(const cStandardFileSystem &right)
  //## begin cStandardFileSystem::cStandardFileSystem%copy.hasinit preserve=no
  //## end cStandardFileSystem::cStandardFileSystem%copy.hasinit
  //## begin cStandardFileSystem::cStandardFileSystem%copy.initialization preserve=yes
  //## end cStandardFileSystem::cStandardFileSystem%copy.initialization
{
  //## begin cStandardFileSystem::cStandardFileSystem%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardFileSystem::cStandardFileSystem%copy.body
}


cStandardFileSystem::~cStandardFileSystem()
{
  //## begin cStandardFileSystem::~cStandardFileSystem%.body preserve=yes
  //## end cStandardFileSystem::~cStandardFileSystem%.body
}



//## Other Operations (implementation)
ULONG_T cStandardFileSystem::Scan (STRING_LIST_T &file_names, CONST_STRING_T pattern)
{
  //## begin cStandardFileSystem::Scan%1141375549.body preserve=yes
   if (cFileSystemUtils::FileList(file_names, _BasePath.c_str(), pattern)) {
      return file_names.size();
   }
   return 0;
  //## end cStandardFileSystem::Scan%1141375549.body
}

int cStandardFileSystem::Get (CONST_STRING_T path, STRING_T &buffer, ULONG_T flags)
{
  //## begin cStandardFileSystem::Get%1141375550.body preserve=yes
   STRING_T src_file = path;
   if (cFileSystemUtils::IsRelativePath(path)) {
      if (_BasePath.size() != 0) {
         src_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), path);
      }
   }
   cSHFile file(src_file.c_str());
   if (file.Exists()) {
      buffer = file.ToString();
      if (flags & FS_FLAG_REMOVE) {
         if (cFileSystemUtils::RemoveFile(src_file.c_str())) {
            return 0;
         } else {
            int error = 0;
            STRING_T error_msg;
            GetErrorInfo(error, error_msg);
            ErrorPrintf("failed to remove file %s: %s\n", src_file.c_str(), error_msg.c_str());
            return FAILED_TO_REMOVE_FILE;
         }
      }
      return 0;
   } else {
      ErrorPrintf("file %s not found\n", src_file.c_str());
      return FILE_DOES_NOT_EXIST;
   }
  //## end cStandardFileSystem::Get%1141375550.body
}

int cStandardFileSystem::Put (CONST_STRING_T path, CONST_STRING_T text, ULONG_T flags)
{
  //## begin cStandardFileSystem::Put%1141375551.body preserve=yes
   STRING_T dst_file = path;
   if (cFileSystemUtils::IsRelativePath(path)) {
      if (_BasePath.size() != 0) {
         dst_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), path);
      }
   }
   STRING_T data;
   int mode = 0;
   if (flags & FS_FLAG_APPEND) {
      mode = FILE_ACCESS_APPEND;
#define DIRECT_APPEND
#ifdef DIRECT_APPEND
      cSHFile file(dst_file.c_str());
      if (file.Open(mode)) {
         if (strlen(text) != 0) {
            int err = 0;
            if (file.Write((void*)text, strlen(text)) == 0) {
               int error = 0;
               STRING_T error_msg;
               GetErrorInfo(error, error_msg);
               ErrorPrintf("failed to write to temp file %s: %s\n", dst_file.c_str(), error_msg.c_str());
               file.Close();
               return FAILED_TO_WRITE_FILE;
            } else {
               file.Close();
               cFileSystemUtils::FlushFile(dst_file.c_str());
               return 0;
            }
         }
      }
#else
      Get(dst_file.c_str(), data, FS_FLAG_REMOVE);
#endif
   } else {
      mode = FILE_MODE_CREATE;
   }
   STRING_T temp_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), "tempshac"); // HA030506
   cSHFile file(temp_file.c_str());
   if (file.Open(mode)) {
      if (data.size() > 0) {
         int err = 0;
         if (file.Write((void*)data.c_str(), data.size()) == 0) {
            int error = 0;
            STRING_T error_msg;
            GetErrorInfo(error, error_msg);
            ErrorPrintf("failed to write to temp file %s: %s\n", dst_file.c_str(), error_msg.c_str());
            file.Close();
            return FAILED_TO_WRITE_FILE;
         }
      }
      if (strlen(text) != 0) {
         int err = 0;
         if (file.Write((void*)text, strlen(text)) == 0) {
            int error = 0;
            STRING_T error_msg;
            GetErrorInfo(error, error_msg);
            ErrorPrintf("failed to write to temp file %s: %s\n", dst_file.c_str(), error_msg.c_str());
            file.Close();
            return FAILED_TO_WRITE_FILE;
         }
         file.Close();
         cFileSystemUtils::FlushFile(temp_file.c_str());
#define CREATE_MISSING_DIRECTORIES
#ifdef CREATE_MISSING_DIRECTORIES
         STRING_T dst_path = cFileSystemUtils::DirName(dst_file.c_str());
         if (!cFileSystemUtils::CreateDir(dst_path.c_str())) {
            int error = 0;
            STRING_T error_msg;
            GetErrorInfo(error, error_msg);
            ErrorPrintf("failed to create file %s\n", dst_file.c_str(), error_msg.c_str());
            return FAILED_TO_CREATE_DIRECTORY;
         }
#endif
      } else {
         file.Close();
         cFileSystemUtils::FlushFile(temp_file.c_str());
      }
      cFileSystemUtils::RemoveFile(dst_file.c_str());
      if (!Rename(temp_file.c_str(), dst_file.c_str(), 0)) {
         int error = 0;
         STRING_T error_msg;
         GetErrorInfo(error, error_msg);
         ErrorPrintf("failed to rename temp file %s to %s: %s\n", temp_file.c_str(), dst_file.c_str(), error_msg.c_str());
         return FAILED_TO_RENAME_FILE;
      } else {
         return 0;
      }
   } else {
      int error = 0;
      STRING_T error_msg;
      GetErrorInfo(error, error_msg);
      ErrorPrintf("failed to create temp file %s: %s\n", temp_file.c_str(), error_msg.c_str());
      return FAILED_TO_CREATE_FILE;
   }
  //## end cStandardFileSystem::Put%1141375551.body
}

BOOL_T cStandardFileSystem::Rename (CONST_STRING_T path, CONST_STRING_T new_path, ULONG_T flags)
{
  //## begin cStandardFileSystem::Rename%1141375552.body preserve=yes
   STRING_T src_file = path;
   if (cFileSystemUtils::IsRelativePath(path)) {
      if (_BasePath.size() != 0) {
         src_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), path);
      }
   }
   STRING_T dst_file = new_path;
   if (cFileSystemUtils::IsRelativePath(new_path)) {
      if (_BasePath.size() != 0) {
         dst_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), new_path);
      }
   }
   return cFileSystemUtils::RenameFile(src_file.c_str(), dst_file.c_str());
  //## end cStandardFileSystem::Rename%1141375552.body
}

CONST_STRING_T cStandardFileSystem::ErrorText (int error_code)
{
  //## begin cStandardFileSystem::ErrorText%1166170817.body preserve=yes
   return cAbstractFileSystem::ErrorText(error_code);
  //## end cStandardFileSystem::ErrorText%1166170817.body
}

int cStandardFileSystem::RemoveFile (CONST_STRING_T path)
{
  //## begin cStandardFileSystem::RemoveFile
   STRING_T src_file = path;
   if (cFileSystemUtils::IsRelativePath(path)) {
      if (_BasePath.size() != 0) {
         src_file = cFileSystemUtils::AppendPath(_BasePath.c_str(), path);
      }
   }

   cSHFile file(src_file.c_str());
   if (file.Exists()) {
      if (cFileSystemUtils::RemoveFile(src_file.c_str())) {
         return 0;
      } else {
         int error = 0;
         STRING_T error_msg;
         GetErrorInfo(error, error_msg);
         ErrorPrintf("failed to remove file %s: %s\n", src_file.c_str(), error_msg.c_str());
         return FAILED_TO_REMOVE_FILE;
      }
   } else {
      ErrorPrintf("file %s not found\n", src_file.c_str());
      return FILE_DOES_NOT_EXIST;
   }
  //## end cStandardFileSystem::RemoveFile
}

// Additional Declarations
  //## begin cStandardFileSystem%440802CA0370.declarations preserve=yes
  //## end cStandardFileSystem%440802CA0370.declarations

//## begin module%440802CA0370.epilog preserve=yes
//## end module%440802CA0370.epilog
