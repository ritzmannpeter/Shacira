//## begin module%3B8A315401D5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A315401D5.cm

//## begin module%3B8A315401D5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A315401D5.cp

//## Module: cFileSystemUtils%3B8A315401D5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cFileSystemUtils.cpp

//## begin module%3B8A315401D5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B8A315401D5.additionalIncludes

//## begin module%3B8A315401D5.includes preserve=yes

#if defined(__linux__)
#include<sys/stat.h>
#endif

//## end module%3B8A315401D5.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3B8A315401D5.additionalDeclarations preserve=yes
//## end module%3B8A315401D5.additionalDeclarations


// Class cFileSystemUtils 

//## begin cFileSystemUtils::Type%3B8A340400E4.attr preserve=no  public: static FileSystemTypes {U} FSYS_WINDOWS
FileSystemTypes cFileSystemUtils::_Type = FSYS_WINDOWS;
//## end cFileSystemUtils::Type%3B8A340400E4.attr

//## begin cFileSystemUtils::StartupDirectory%3B8A5B5A0292.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cFileSystemUtils::_StartupDirectory;
//## end cFileSystemUtils::StartupDirectory%3B8A5B5A0292.attr

cFileSystemUtils::cFileSystemUtils()
  //## begin cFileSystemUtils::cFileSystemUtils%.hasinit preserve=no
  //## end cFileSystemUtils::cFileSystemUtils%.hasinit
  //## begin cFileSystemUtils::cFileSystemUtils%.initialization preserve=yes
  //## end cFileSystemUtils::cFileSystemUtils%.initialization
{
  //## begin cFileSystemUtils::cFileSystemUtils%.body preserve=yes
_ASSERT_UNCOND
  //## end cFileSystemUtils::cFileSystemUtils%.body
}

cFileSystemUtils::cFileSystemUtils(const cFileSystemUtils &right)
  //## begin cFileSystemUtils::cFileSystemUtils%copy.hasinit preserve=no
  //## end cFileSystemUtils::cFileSystemUtils%copy.hasinit
  //## begin cFileSystemUtils::cFileSystemUtils%copy.initialization preserve=yes
  //## end cFileSystemUtils::cFileSystemUtils%copy.initialization
{
  //## begin cFileSystemUtils::cFileSystemUtils%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFileSystemUtils::cFileSystemUtils%copy.body
}


cFileSystemUtils::~cFileSystemUtils()
{
  //## begin cFileSystemUtils::~cFileSystemUtils%.body preserve=yes
_ASSERT_UNCOND
  //## end cFileSystemUtils::~cFileSystemUtils%.body
}



//## Other Operations (implementation)
BOOL_T cFileSystemUtils::CreateDir (CONST_STRING_T directory)
{
  //## begin cFileSystemUtils::CreateDir%998912344.body preserve=yes
   STRING_T path = FullPath(directory);
   STRING_T temp_path;
   STRING_T head, tail;
   LeftSplit(path.c_str(), head, tail);
   while (head.size() > 0) {
      temp_path = AppendPath(temp_path.c_str(), head.c_str());
      if (!IsDrive(temp_path.c_str()) &&
          !IsUNCRoot(temp_path.c_str())) {
         if (!DirExists(temp_path.c_str())) {
#if defined(_WIN32)
            int success = CreateDirectory(temp_path.c_str(), NULL);
            if (!success) {
               return false;
            }
#elif defined(__linux__)
            int rc = mkdir(temp_path.c_str(), 0777);
#else
NO_PLATFORM
#endif
         }
      }
      LeftSplit(tail.c_str(), head, tail);
   }
   return true;
  //## end cFileSystemUtils::CreateDir%998912344.body
}

BOOL_T cFileSystemUtils::RemoveFile (CONST_STRING_T file)
{
  //## begin cFileSystemUtils::RemoveFile%1037294318.body preserve=yes
   if (remove(file) == 0) {
      return true;
   } else {
      return false;
   }
  //## end cFileSystemUtils::RemoveFile%1037294318.body
}

BOOL_T cFileSystemUtils::RenameFile (CONST_STRING_T src_path, CONST_STRING_T dst_path)
{
  //## begin cFileSystemUtils::RenameFile%1141375555.body preserve=yes
   if (rename(src_path, dst_path) == 0) {
      return true;
   } else {
      return false;
   }
  //## end cFileSystemUtils::RenameFile%1141375555.body
}

BOOL_T cFileSystemUtils::DirExists (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::DirExists%998912345.body preserve=yes
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   STRING_T find_spec = AppendPath(full_path.c_str(), "*");
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   hFind = FindFirstFile(find_spec.c_str(), &find_data);
   if (hFind == INVALID_HANDLE_VALUE) {
      return false;
   } else {
      FindClose(hFind);
      return true;
   }
#elif defined(__linux__)
   int rc = access(path, F_OK);
   if (rc == 0) {
      return true;
   } else {
      return false;
   }
#else
NO_PLATFORM
#endif
   return false;
  //## end cFileSystemUtils::DirExists%998912345.body
}

BOOL_T cFileSystemUtils::FileExists (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::FileExists%998912346.body preserve=yes
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   hFind = FindFirstFile(full_path.c_str(), &find_data);
   if (hFind == INVALID_HANDLE_VALUE) {
      return false;
   } else {
      FindClose(hFind);
      return true;
   }
#elif defined(__linux__)
   int rc = access(path, F_OK);
   if (rc == 0) {
      return true;
   } else {
      return false;
   }
#else
NO_PLATFORM
#endif
   return false;
  //## end cFileSystemUtils::FileExists%998912346.body
}

BOOL_T cFileSystemUtils::FileExistence (STRING_VECTOR_T &paths, CONST_STRING_T file_name, STRING_T &file)
{
  //## begin cFileSystemUtils::FileExistence%1044520499.body preserve=yes
   STRING_VECTOR_T::const_iterator i = paths.cbegin();
   while (i != paths.cend()) {
      STRING_T path = (*i);
      STRING_T test_file = AppendPath(path.c_str(), file_name);
      if (FileExists(test_file.c_str())) {
         file = test_file;
         return true;
      }
      i++;
   }
   return false;
  //## end cFileSystemUtils::FileExistence%1044520499.body
}

ULONG_T cFileSystemUtils::FileSize (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::FileSize%1013674760.body preserve=yes
#if defined(_WIN32)
   HANDLE handle = CreateFile(path,
                              GENERIC_READ,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if (handle != INVALID_HANDLE_VALUE) {
      unsigned long file_size = GetFileSize(handle, NULL);
      if (file_size == 0xFFFFFFFF) {
         file_size = 0;
      }
      CloseHandle(handle);
      return file_size;
   } else {
      return 0;
   }
#elif defined(__linux__)
   ULONG_T file_size = 0;
   FILE * stream = fopen(path, "r");
   if (stream != NULL) {
      fseek(stream, 0, SEEK_END);
      file_size = ftell(stream);
   }
   return file_size;
#else
NO_PLATFORM
#endif
   return 0;
  //## end cFileSystemUtils::FileSize%1013674760.body
}

BOOL_T cFileSystemUtils::FileList (STRING_LIST_T &file_names, CONST_STRING_T path, CONST_STRING_T pattern)
{
  //## begin cFileSystemUtils::FileList%1000386745.body preserve=yes
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   if (!DirExists(full_path.c_str())) {
      return false;
   }
   STRING_T find_spec = AppendPath(full_path.c_str(), pattern);
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   hFind = FindFirstFile(find_spec.c_str(), &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      BOOL_T found = true;
      while (found) {
         STRING_T file_name = find_data.cFileName;
         file_names.push_back(file_name);
         found = FindNextFile(hFind, &find_data) ? true : false;
      }
   }
   DWORD last_error = GetLastError();
   if (hFind != INVALID_HANDLE_VALUE) FindClose(hFind);
   if (last_error == ERROR_NO_MORE_FILES) {
      return true;
   } else {
      return false;
   }
#elif defined(__linux__)
PORT_LEVEL_1
return false;
#else
NO_PLATFORM
#endif
   return false;
  //## end cFileSystemUtils::FileList%1000386745.body
}

STRING_T cFileSystemUtils::FullPath (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::FullPath%998912347.body preserve=yes
   if (IsRelativePath(path)) {
      return AppendPath(CurrentDir().c_str(), path);
   } else if (IsUNCPath(path)) {
      return path;
   } else if (IsAbsolutePath(path)) {
      STRING_T drive_name = DriveName(path);
      if (drive_name.size() == 0) {
         STRING_T full_path = CurrentDrive().c_str();
         full_path += path;
         return full_path;
      } else {
         return path;
      }
   } else {
      STRING_T full_path = "\\\\\\\\\\invalid path specification::";
      full_path += path;
      return full_path;
   }
  //## end cFileSystemUtils::FullPath%998912347.body
}

void cFileSystemUtils::LeftSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
  //## begin cFileSystemUtils::LeftSplit%998912348.body preserve=yes
   int pos = cStringUtils::FindFirstOf(path, PATH_DELIMITERS);
   if (pos < 0) {
      head = path;
      tail = "";
   } else if (pos == 0) {
      if (path[0] == '\\' &&
          path[1] == '\\') {
         /// UNC path
         pos = cStringUtils::FindFirstOf(&path[2], PATH_DELIMITERS);
         if (pos < 0) {
            head = path;
            tail = "";
         } else {
            pos += 2;
            head = cStringUtils::Left(path, pos);
            tail = cStringUtils::Right(path, strlen(path) - (pos + 1));
         }
      }
   } else {
      head = cStringUtils::Left(path, pos);
      tail = cStringUtils::Right(path, strlen(path) - (pos + 1));
   }
  //## end cFileSystemUtils::LeftSplit%998912348.body
}

void cFileSystemUtils::RightSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
  //## begin cFileSystemUtils::RightSplit%998912349.body preserve=yes
   int pos = cStringUtils::FindLastOf(path, PATH_DELIMITERS);
   if (pos < 0) {
      head = path;
      tail = "";
   } else {
      head = cStringUtils::Left(path, pos);
      tail = cStringUtils::Right(path, strlen(path) - (pos + 1));
   }
  //## end cFileSystemUtils::RightSplit%998912349.body
}

STRING_T cFileSystemUtils::AppendPath (CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter)
{
  //## begin cFileSystemUtils::AppendPath%998912355.body preserve=yes
   if (strlen(head) == 0) return tail;
   if (strlen(tail) == 0) return head;
   if (IsAbsolutePath(tail) || IsUNCPath(tail)) return tail;

   if (strncmp(tail, "../", 3) == 0) {
      STRING_T new_head = RightStrip(head);
      STRING_T new_tail = LeftStrip(tail);
      return AppendPath(new_head.c_str(), new_tail.c_str());
   } else if (strncmp(tail, "./", 2) == 0) {
      STRING_T new_tail = LeftStrip(tail);
      return AppendPath(head, new_tail.c_str());
   } else {
      STRING_T new_head = cStringUtils::RTrim(head, SLASH);
      new_head = cStringUtils::RTrim(new_head.c_str(), BACK_SLASH);
      STRING_T new_tail = cStringUtils::LTrim(tail, SLASH);
      new_tail = cStringUtils::LTrim(new_tail.c_str(), BACK_SLASH);
      STRING_T new_path = new_head;
      new_path += delimiter;
      new_path += new_tail.c_str();
      return new_path;
   }
  //## end cFileSystemUtils::AppendPath%998912355.body
}

STRING_T cFileSystemUtils::FileName (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::FileName%998912350.body preserve=yes
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   if (directory.size() > 0 && file_name.size() == 0) file_name = directory;
   return file_name;
  //## end cFileSystemUtils::FileName%998912350.body
}

STRING_T cFileSystemUtils::BaseFileName (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::BaseFileName%1074777877.body preserve=yes
   STRING_T base_file_name = FileName(path);
   int pos = cStringUtils::FindFirstOf(base_file_name.c_str(), ".");
   if (pos < 0) {
      return base_file_name;
   } else {
      return cStringUtils::Left(base_file_name.c_str(), pos);
   }
  //## end cFileSystemUtils::BaseFileName%1074777877.body
}

STRING_T cFileSystemUtils::DirName (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::DirName%998912351.body preserve=yes
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   return directory;
  //## end cFileSystemUtils::DirName%998912351.body
}

STRING_T cFileSystemUtils::DriveName (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::DriveName%998912359.body preserve=yes
   if (IsUNCPath(path)) return "";
   if (IsRelativePath(path)) {
      return DriveName(CurrentDir().c_str());
   }
   STRING_T drive_name = cStringUtils::Left(path, 2);
   if (IsPathDelimiter(drive_name[0])) {
      return "";
   }
   return drive_name;
  //## end cFileSystemUtils::DriveName%998912359.body
}

STRING_T cFileSystemUtils::FileExtension (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::FileExtension%998912352.body preserve=yes
   int pos = cStringUtils::FindLastOf(path, ".");
   STRING_T file_extension = cStringUtils::Right(path, strlen(path) - pos);
   return file_extension;
  //## end cFileSystemUtils::FileExtension%998912352.body
}

STRING_T cFileSystemUtils::CurrentDir ()
{
  //## begin cFileSystemUtils::CurrentDir%998912356.body preserve=yes
   char current_directory[1024] = {0};
#if defined(_WIN32)
   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
   if (len > 0) {
      return current_directory;
   } else {
      return "Current directory unknown";
   }
#elif defined(__linux__)
   ULONG_T len = 0;
   char * current_dir = getcwd(current_directory, sizeof(current_directory));
   if (current_dir != NULL) {
      return current_dir;
   } else {
      return "no cwd"; 
   }
#else
NO_PLATFORM
#endif
  //## end cFileSystemUtils::CurrentDir%998912356.body
}

STRING_T cFileSystemUtils::CurrentDrive ()
{
  //## begin cFileSystemUtils::CurrentDrive%998912363.body preserve=yes
#if defined(_WIN32)
   STRING_T current_directory = CurrentDir();
   STRING_T current_drive = cStringUtils::Left(current_directory, 2);
   return current_drive;
#elif defined(__linux__)
   return "";
#else
NO_PLATFORM
#endif
  //## end cFileSystemUtils::CurrentDrive%998912363.body
}

STRING_T cFileSystemUtils::StartupDir ()
{
  //## begin cFileSystemUtils::StartupDir%998912357.body preserve=yes
   if (_StartupDirectory.size() == 0) {
      _StartupDirectory = CurrentDir();
   }
   return _StartupDirectory.c_str();
  //## end cFileSystemUtils::StartupDir%998912357.body
}

BOOL_T cFileSystemUtils::IsRelativePath (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::IsRelativePath%998912360.body preserve=yes
   int len = strlen(path);
   if (len == 0) return true;
   if (IsPathDelimiter(path[0])) {
      return false;
   } else if (len > 1 && IsDriveChar(path[1])) {
      return false;
   } else {
      return true;
   }
  //## end cFileSystemUtils::IsRelativePath%998912360.body
}

BOOL_T cFileSystemUtils::IsAbsolutePath (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::IsAbsolutePath%998912361.body preserve=yes
   return !IsRelativePath(path);
  //## end cFileSystemUtils::IsAbsolutePath%998912361.body
}

BOOL_T cFileSystemUtils::IsUNCPath (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::IsUNCPath%998912365.body preserve=yes
   if (path[0] == BACK_SLASH && path[1] == BACK_SLASH) {
      return true;
   } else {
      return false;
   }
  //## end cFileSystemUtils::IsUNCPath%998912365.body
}

BOOL_T cFileSystemUtils::IsPathDelimiter (CHAR_T c)
{
  //## begin cFileSystemUtils::IsPathDelimiter%998912362.body preserve=yes
   return (c == BACK_SLASH || c == SLASH);
  //## end cFileSystemUtils::IsPathDelimiter%998912362.body
}

BOOL_T cFileSystemUtils::IsDrive (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::IsDrive%998912364.body preserve=yes
   if (strlen(path) == 2 && IsDriveChar(path[1])) {
      return true;
   } else {
      return false;
   }
  //## end cFileSystemUtils::IsDrive%998912364.body
}

BOOL_T cFileSystemUtils::IsUNCRoot (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::IsUNCRoot%1141396797.body preserve=yes
   if (path[0] != '\\' ||
       path[1] != '\\') {
      return false;
   } else {
      const char * path_ptr = &path[2];
      int pos = cStringUtils::FindFirstOf(path_ptr, PATH_DELIMITERS);
      if (pos < 0) {
         return true;
      } else {
         path_ptr = &path[pos + 2 + 1];
         pos = cStringUtils::FindFirstOf(path_ptr, PATH_DELIMITERS);
         if (pos < 0) {
            return true;
         } else {
            return false;
         }
      }
   }
  //## end cFileSystemUtils::IsUNCRoot%1141396797.body
}

BOOL_T cFileSystemUtils::IsDriveChar (CHAR_T c)
{
  //## begin cFileSystemUtils::IsDriveChar%998912366.body preserve=yes
   return (c == ':');
  //## end cFileSystemUtils::IsDriveChar%998912366.body
}

INT_T cFileSystemUtils::WriteProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value, CONST_STRING_T file)
{
  //## begin cFileSystemUtils::WriteProfileString%1046178221.body preserve=yes
#if defined(_WIN32)
   BOOL success = WritePrivateProfileString(chapter, key, value, file);
   if (!success) {
      return GetLastError();
   }
#elif defined(__linux__)
PORT_LEVEL_3
   return -1;
#else
NO_PLATFORM
#endif
   return 0;
  //## end cFileSystemUtils::WriteProfileString%1046178221.body
}

STRING_T cFileSystemUtils::GetProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T default_value, CONST_STRING_T file)
{
  //## begin cFileSystemUtils::GetProfileString%1053266946.body preserve=yes
#if defined(_WIN32)
   char buffer[1024] = {0};
   DWORD nread = GetPrivateProfileString(chapter, key, default_value, buffer, sizeof(buffer), file);
   return buffer;
#elif defined(__linux__)
PORT_LEVEL_3
   return "";
#else
NO_PLATFORM
#endif
   return "no data";
  //## end cFileSystemUtils::GetProfileString%1053266946.body
}

STRING_T cFileSystemUtils::LeftStrip (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::LeftStrip%1144065933.body preserve=yes
   STRING_T component;
   return LeftStrip(path, component);
  //## end cFileSystemUtils::LeftStrip%1144065933.body
}

STRING_T cFileSystemUtils::LeftStrip (CONST_STRING_T path, STRING_T &component)
{
  //## begin cFileSystemUtils::LeftStrip%1144065935.body preserve=yes
   component = "";
   int len = strlen(path);
   int i = 0;
   for (i=0; i<len; i++) {
      if (path[i] == '/' ||
          path[i] == '\\') {
         break;
      }
   }
   STRING_T new_path;
   if (i != len) {
      new_path = &(path[i+1]);
      component = cStringUtils::Left(path, i);
   } else {
      new_path = "";
      component = path;
   }
   return new_path;
  //## end cFileSystemUtils::LeftStrip%1144065935.body
}

STRING_T cFileSystemUtils::RightStrip (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::RightStrip%1144065934.body preserve=yes
   STRING_T component;
   return RightStrip(path, component);
  //## end cFileSystemUtils::RightStrip%1144065934.body
}

STRING_T cFileSystemUtils::RightStrip (CONST_STRING_T path, STRING_T &component)
{
  //## begin cFileSystemUtils::RightStrip%1144065936.body preserve=yes
   component = "";
   int len = strlen(path);
   int i = 0;
   for (i=len; i>=0; i--) {
      if (path[i] == '/' ||
          path[i] == '\\') {
         break;
      }
   }
   STRING_T new_path;
   if (i > 0) {
      new_path = cStringUtils::Left(path, i);
      component = &(path[i+1]);
   } else {
      new_path = "";
      component = path;
   }
   return new_path;
  //## end cFileSystemUtils::RightStrip%1144065936.body
}

void cFileSystemUtils::NameComponents (CONST_STRING_T file_name, STRING_T &base_name, STRING_T &extension)
{
  //## begin cFileSystemUtils::NameComponents%1144078177.body preserve=yes
   int len = strlen(file_name);
   int i = 0;
   for (i=len; i>=0; i--) {
      if (file_name[i] == '.') {
         break;
      }
   }
   if (i > 0) {
      base_name = cStringUtils::Left(file_name, i);
      extension = &(file_name[i+1]);
   } else {
      base_name = file_name;
      extension = "";
   }
  //## end cFileSystemUtils::NameComponents%1144078177.body
}

STRING_T cFileSystemUtils::Resolve (CONST_STRING_T path)
{
  //## begin cFileSystemUtils::Resolve%1144143457.body preserve=yes
   /// ?????????????
   if (path[0] == '/') {
      return path;
   }
   STRING_T new_path = path;
   STRING_VECTOR_T ppath;
   int len = strlen(path);
   int prev_pos = 0;
   int i = 0;
   for (i=0; i<len; i++) {
      if (path[i] == '/' ||
          path[i] == '\\') {
         int pos = ppath.size();
         ppath.resize(pos+1);
         STRING_T c = cStringUtils::Left(&(path[prev_pos]), i - (prev_pos));
         ppath[pos] = c; 
         prev_pos = i + 1;
      }
   }
   if (path[len-1] != '/' &&
       path[len-1] != '\\') {
      int pos = ppath.size();
      ppath.resize(pos+1);
      STRING_T c = cStringUtils::Left(&(path[prev_pos]), i - (prev_pos));
      ppath[pos] = c; 
   }
   int size = ppath.size();
   for (i=1; i<size; i++) {
      if (ppath[i] == ".." &&
          ppath[i-1] != "..") {
         int j = 0;
         if (i < size - 1) {
            for (j=i; j<size; j++) {
               ppath[j-1] = ppath[j+1];
            }
         }
         ppath.resize(size-2);
      }
   }
   size = ppath.size();
   if (size > 0) {
      new_path = ppath[0];
      for (i=1; i<size; i++) {
         new_path = cFileSystemUtils::AppendPath(new_path.c_str(), ppath[i].c_str());
      }
   } else {
      new_path = "";
   }
   return new_path;
  //## end cFileSystemUtils::Resolve%1144143457.body
}

BOOL_T cFileSystemUtils::GetDiskInfo (CONST_STRING_T path, ULONG_T &free_space, ULONG_T &occupied_space, ULONG_T flags)
{
#ifdef _WIN32
#define SIZE_IN_MEG     0x00000001
#define SIZE_IN_GIG     0x00000002
   free_space = 0;
   occupied_space = 0;
   try {
      if (flags == 0) {
         flags = SIZE_IN_MEG;
      }
      STRING_T drive = DriveName(path);
      if (IsUNCPath(path)) {
         drive = path;
         if (drive[drive.size()] != '\\') {
            drive += "\\";
         }
      } else {
         drive = DriveName(path);
      }
      ULONG_T free_bytes_caller[2] = {0};
      ULONG_T free_bytes[2] = {0};
      ULONG_T bytes[2] = {0};
      PULARGE_INTEGER _free_bytes_caller = (PULARGE_INTEGER)&free_bytes_caller;
      PULARGE_INTEGER _free_bytes = (PULARGE_INTEGER)&free_bytes;
      PULARGE_INTEGER _bytes = (PULARGE_INTEGER)&bytes;
      BOOL success = GetDiskFreeSpaceEx(drive.c_str(),
                                        _free_bytes_caller,
                                        _bytes,
                                        _free_bytes);
      if (success) {
         ULONGLONG quad1 = _free_bytes_caller->QuadPart;
         ULONGLONG quad2 = _bytes->QuadPart;
         ULONGLONG quad3 = _free_bytes->QuadPart;
         if (flags & SIZE_IN_MEG) {
            quad1 = Int64ShraMod32(quad1, 20);
            quad2 = Int64ShraMod32(quad2, 20);
            quad3 = Int64ShraMod32(quad3, 20);
         } else if (flags & SIZE_IN_GIG) {
            quad1 = Int64ShraMod32(quad1, 30);
            quad2 = Int64ShraMod32(quad2, 30);
            quad3 = Int64ShraMod32(quad3, 30);
         }
         _free_bytes->QuadPart = quad3;
         _bytes->QuadPart = quad2;
         free_space = free_bytes[0];
         occupied_space = bytes[0] - free_space;
         return true;
      } else {
         int error = GetLastError();
         return false;
      }
   } catch (...) {
   }
#endif
   return false;
}

void cFileSystemUtils::FlushFile(const char * filename)
{
#ifdef _WIN32
   #define MAXRETRIES 2
   #define RETRY_DELAY 100

   int retries = 0;
   int error = 0;
   HANDLE hnd = INVALID_HANDLE_VALUE;
   BOOL_T success = false;

   do {
      hnd = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      if (hnd == INVALID_HANDLE_VALUE) {
         error = (int)GetLastError();

         if (error == ERROR_SHARING_VIOLATION) {
            retries++;
            Sleep(RETRY_DELAY);
            continue;
         }
         else {
            // An error occurred.
            break;
         }
      }

      success = true;
      break;
   } while (retries < MAXRETRIES);

   if (success) {
      if (FlushFileBuffers(hnd)) {
      } else {
         error = (int)GetLastError();
         ErrorPrintf("failed to flush file buffers of %s: %d\n", filename, error);
      }
      CloseHandle(hnd);
   }
   else {
      error = (int)GetLastError();
      ErrorPrintf("failed to open handle for flush file buffers of %s: %d\n", filename, error);
   }
#endif
}

//## Get and Set Operations for Class Attributes (implementation)

FileSystemTypes cFileSystemUtils::get_Type ()
{
  //## begin cFileSystemUtils::get_Type%3B8A340400E4.get preserve=no
  return _Type;
  //## end cFileSystemUtils::get_Type%3B8A340400E4.get
}

void cFileSystemUtils::set_Type (FileSystemTypes value)
{
  //## begin cFileSystemUtils::set_Type%3B8A340400E4.set preserve=no
  _Type = value;
  //## end cFileSystemUtils::set_Type%3B8A340400E4.set
}

// Additional Declarations
  //## begin cFileSystemUtils%3B8A315401D5.declarations preserve=yes
  //## end cFileSystemUtils%3B8A315401D5.declarations

//## begin module%3B8A315401D5.epilog preserve=yes
//## end module%3B8A315401D5.epilog
