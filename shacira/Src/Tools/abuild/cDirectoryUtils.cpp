
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sys/stat.h>
#endif
#include "cDirectoryUtils.h"

#include <malloc.h>
#define __ALLOC__(size) calloc(1,size)
#define __FREE__(mem) free(mem)

bool cDirectoryUtils::IsDirectory(const char * path)
{
return DirExists(path);
}

STRING_T cDirectoryUtils::RelPath(const char * dir, const char * path)
{
   STRING_T rel_path;
   STRING_T _dir = dir;
   STRING_T _path = path;
   STRING_T left_dir;
   STRING_T left_path;
   _dir = cDirectoryUtils::LeftStrip(_dir.c_str(), left_dir);
   _path = cDirectoryUtils::LeftStrip(_path.c_str(), left_path);
#ifdef lassma
   if (left_path.size() == 0 ||
       left_path[1] == ':') {
      return path;
   }
#endif
   while (_stricmp(left_dir.c_str(), left_path.c_str()) == 0) {
      if (left_dir.size() == 0) {
         return "./";
      }
      _dir = cDirectoryUtils::LeftStrip(_dir.c_str(), left_dir);
      _path = cDirectoryUtils::LeftStrip(_path.c_str(), left_path);
   }
   int levels = 0;
   while (left_dir.size() > 0) {
      levels++;
      _dir = cDirectoryUtils::LeftStrip(_dir.c_str(), left_dir);
   }
   int i = 0;
   for (i=0; i<levels; i++) {
      rel_path = cDirectoryUtils::AppendPath(rel_path.c_str(), "..");
   }
   rel_path = cDirectoryUtils::AppendPath(rel_path.c_str(), left_path.c_str());
   if (_path.size() > 0) {
      rel_path = cDirectoryUtils::AppendPath(rel_path.c_str(), _path.c_str());
   }
   rel_path = cDirectoryUtils::Resolve(rel_path.c_str());
   return rel_path;
}

bool cDirectoryUtils::CreateDir(const char * directory)
{
   STRING_T path = FullPath(directory);
   STRING_T temp_path;
   STRING_T head, tail;
   LeftSplit(path.c_str(), head, tail);
   while(head.size() > 0) {
      temp_path = AppendPath(temp_path.c_str(), head.c_str());
      if(!IsDrive(temp_path.c_str()) &&
          !IsUNCRoot(temp_path.c_str())) {
         if(!DirExists(temp_path.c_str())) {
#if defined(_WIN32)
            int success = CreateDirectory(temp_path.c_str(), NULL);
            if(!success) {
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
}

bool cDirectoryUtils::RemoveFile(const char * file)
{
   if(remove(file) == 0) {
      return true;
   } else {
      return false;
   }
}

bool cDirectoryUtils::RenameFile(const char * src_path, const char * dst_path)
{
   if(rename(src_path, dst_path) == 0) {
      return true;
   } else {
      return false;
   }
}

bool cDirectoryUtils::DirExists(const char * path)
{
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   STRING_T find_spec = AppendPath(full_path.c_str(), "*");
   WIN32_FIND_DATA find_data;
   HANDLE find_handle;
   find_handle = FindFirstFile(find_spec.c_str(), &find_data);
   if(find_handle == INVALID_HANDLE_VALUE) {
      return false;
   } else {
      FindClose(find_handle);
      return true;
   }
#elif defined(__linux__)
   int rc = access(path, F_OK);
   if(rc == 0) {
      return true;
   } else {
      return false;
   }
#else
NO_PLATFORM
#endif
   return false;
}

bool cDirectoryUtils::FileExists(const char * path)
{
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   WIN32_FIND_DATA find_data;
   HANDLE find_handle;
   find_handle = FindFirstFile(full_path.c_str(), &find_data);
   if(find_handle == INVALID_HANDLE_VALUE) {
      return false;
   } else {
      FindClose(find_handle);
      return true;
   }
#elif defined(__linux__)
   int rc = access(path, F_OK);
   if(rc == 0) {
      return true;
   } else {
      return false;
   }
#else
NO_PLATFORM
#endif
   return false;
}

bool cDirectoryUtils::FileExistence(STRING_VECTOR_T &paths, const char * file_name, STRING_T &file)
{
   STRING_VECTOR_T::const_iterator i = paths.begin();
   while(i != paths.end()) {
      STRING_T path =(*i);
      STRING_T test_file = AppendPath(path.c_str(), file_name);
      if(FileExists(test_file.c_str())) {
         file = test_file;
         return true;
      }
      i++;
   }
   return false;
}

unsigned long cDirectoryUtils::FileSize(const char * path)
{
#if defined(_WIN32)
   HANDLE handle = CreateFile(path,
                              GENERIC_READ,
                              0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
   if(handle != INVALID_HANDLE_VALUE) {
      unsigned long file_size = GetFileSize(handle, NULL);
      if(file_size == 0xFFFFFFFF) {
         file_size = 0;
      }
      CloseHandle(handle);
      return file_size;
   } else {
      return 0;
   }
#elif defined(__linux__)
   unsigned long file_size = 0;
   FILE * stream = fopen(path, "r");
   if(stream != NULL) {
      fseek(stream, 0, SEEK_END);
      file_size = ftell(stream);
   }
   return file_size;
#else
NO_PLATFORM
#endif
   return 0;
}

bool cDirectoryUtils::FileList(STRING_LIST_T &file_names, const char * path, unsigned long flags, const char * pattern)
{
#if defined(_WIN32)
   STRING_T full_path = FullPath(path);
   if(!DirExists(full_path.c_str())) {
      return false;
   }
   STRING_T find_spec = AppendPath(full_path.c_str(), pattern);
   WIN32_FIND_DATA find_data;
   HANDLE find_handle;
   find_handle = FindFirstFile(find_spec.c_str(), &find_data);
   if (find_handle != INVALID_HANDLE_VALUE) {
      bool found = true;
      while(found) {
         STRING_T file_name = find_data.cFileName;
         STRING_T file = AppendPath(path, file_name.c_str());
         if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (flags & WALK_RECURSIVE) {
               if (file_name[0] != '.') {
                  STRING_T new_path = AppendPath(path, file_name.c_str());
                  FileList(file_names, new_path.c_str(), flags);
               }
            }
         } else {
            file_names.push_back(file);
         }
         found = FindNextFile(find_handle, &find_data) ? true : false;
      }
   }
   DWORD last_error = GetLastError();
   if(find_handle != INVALID_HANDLE_VALUE) FindClose(find_handle);
   if(last_error == ERROR_NO_MORE_FILES) {
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
}

STRING_T cDirectoryUtils::FullPath(const char * path)
{
   if(IsRelativePath(path)) {
      return AppendPath(CurrentDir().c_str(), path);
   } else if(IsUNCPath(path)) {
      return path;
   } else if(IsAbsolutePath(path)) {
      STRING_T drive_name = DriveName(path);
      if(drive_name.size() == 0) {
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
}

void cDirectoryUtils::LeftSplit(const char * path, STRING_T &head, STRING_T &tail)
{
   int pos = FindFirstOf(path, PATH_DELIMITERS);
   if(pos < 0) {
      head = path;
      tail = "";
   } else if(pos == 0) {
      if(path[0] == '\\' &&
          path[1] == '\\') {
         /// UNC path
         pos = FindFirstOf(&path[2], PATH_DELIMITERS);
         if(pos < 0) {
            head = path;
            tail = "";
         } else {
            pos += 2;
            head = cDirectoryUtils::Left(path, pos);
            tail = cDirectoryUtils::Right(path, strlen(path) -(pos + 1));
         }
      } else if(path[0] == '/') {
         /// unix absolute path
         tail = cDirectoryUtils::Right(path, strlen(path) -(pos + 1));
      }
   } else {
      head = cDirectoryUtils::Left(path, pos);
      tail = cDirectoryUtils::Right(path, strlen(path) -(pos + 1));
   }
}

void cDirectoryUtils::RightSplit(const char * path, STRING_T &head, STRING_T &tail)
{
   int pos = cDirectoryUtils::FindLastOf(path, PATH_DELIMITERS);
   if(pos < 0) {
      head = path;
      tail = "";
   } else {
      head = cDirectoryUtils::Left(path, pos);
      tail = cDirectoryUtils::Right(path, strlen(path) -(pos + 1));
   }
}

STRING_T cDirectoryUtils::AppendPath(const char * head, const char * tail, const char * delimiter)
{
   if(strlen(head) == 0) return tail;
   if(strlen(tail) == 0) return head;
   if(IsAbsolutePath(tail) || IsUNCPath(tail)) return tail;

   if(strncmp(tail, "../", 3) == 0) {
      STRING_T new_head = RightStrip(head);
      STRING_T new_tail = LeftStrip(tail);
      return AppendPath(new_head.c_str(), new_tail.c_str());
   } else if(strncmp(tail, "./", 2) == 0) {
      STRING_T new_tail = LeftStrip(tail);
      return AppendPath(head, new_tail.c_str());
   } else {
      STRING_T new_head = cDirectoryUtils::RTrim(head, SLASH);
      new_head = cDirectoryUtils::RTrim(new_head.c_str(), BACK_SLASH);
      STRING_T new_tail = cDirectoryUtils::LTrim(tail, SLASH);
      new_tail = cDirectoryUtils::LTrim(new_tail.c_str(), BACK_SLASH);
      STRING_T new_path = new_head;
      new_path += delimiter;
      new_path += new_tail.c_str();
      return new_path;
   }
}

STRING_T cDirectoryUtils::FileName(const char * path)
{
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   if(directory.size() > 0 && file_name.size() == 0) file_name = directory;
   return file_name;
}

STRING_T cDirectoryUtils::BaseFileName(const char * path)
{
   STRING_T base_file_name = FileName(path);
   int pos = cDirectoryUtils::FindFirstOf(base_file_name.c_str(), ".");
   if(pos < 0) {
      return base_file_name;
   } else {
      return cDirectoryUtils::Left(base_file_name.c_str(), pos);
   }
}

STRING_T cDirectoryUtils::DirName(const char * path)
{
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   return directory;
}

STRING_T cDirectoryUtils::DriveName(const char * path)
{
   if(IsUNCPath(path)) return "";
   if(IsRelativePath(path)) {
      return DriveName(CurrentDir().c_str());
   }
   STRING_T drive_name = cDirectoryUtils::Left(path, 2);
   if(IsPathDelimiter(drive_name[0])) {
      return "";
   }
   return drive_name;
}

STRING_T cDirectoryUtils::FileExtension(const char * path)
{
   int pos = cDirectoryUtils::FindLastOf(path, ".");
   STRING_T file_extension = cDirectoryUtils::Right(path, strlen(path) - pos);
   return file_extension;
}

STRING_T cDirectoryUtils::CurrentDir()
{
   char current_directory[1024] = {0};
#if defined(_WIN32)
   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
   if (len > 0) {
      return current_directory;
   } else {
      return "Current directory unknown";
   }
#elif defined(__linux__)
   unsigned long len = 0;
   char * current_dir = getcwd(current_directory, sizeof(current_directory));
   if(current_dir != NULL) {
      return current_dir;
   } else {
      return "no cwd"; 
   }
#else
NO_PLATFORM
#endif
}

bool cDirectoryUtils::SetCurrentDir(const char * directory)
{
#if defined(_WIN32)
   BOOL success = SetCurrentDirectory(directory);
   if (!success) {
      int err = GetLastError();
   }
   return success;
#elif defined(__linux__)
#else
NO_PLATFORM
#endif
}

STRING_T cDirectoryUtils::CurrentDrive()
{
#if defined(_WIN32)
   STRING_T current_directory = CurrentDir();
   STRING_T current_drive = cDirectoryUtils::Left(current_directory, 2);
   return current_drive;
#elif defined(__linux__)
   return "";
#else
NO_PLATFORM
#endif
}

bool cDirectoryUtils::SetCurrentDrive(const char * drive)
{
return true;
}

bool cDirectoryUtils::IsRelativePath(const char * path)
{
   int len = strlen(path);
   if(len == 0) return true;
   if(IsPathDelimiter(path[0])) {
      return false;
   } else if(len > 1 && IsDriveChar(path[1])) {
      return false;
   } else {
      return true;
   }
}

bool cDirectoryUtils::IsAbsolutePath(const char * path)
{
   return !IsRelativePath(path);
}

bool cDirectoryUtils::IsUNCPath(const char * path)
{
   if(path[0] == BACK_SLASH && path[1] == BACK_SLASH) {
      return true;
   } else {
      return false;
   }
}

bool cDirectoryUtils::IsPathDelimiter(char c)
{
   return(c == BACK_SLASH || c == SLASH);
}

bool cDirectoryUtils::IsDrive(const char * path)
{
   if(strlen(path) == 2 && IsDriveChar(path[1])) {
      return true;
   } else {
      return false;
   }
}

bool cDirectoryUtils::IsUNCRoot(const char * path)
{
   if(path[0] != '\\' ||
       path[1] != '\\') {
      return false;
   } else {
      const char * path_ptr = &path[2];
      int pos = cDirectoryUtils::FindFirstOf(path_ptr, PATH_DELIMITERS);
      if(pos < 0) {
         return true;
      } else {
         path_ptr = &path[pos + 2 + 1];
         pos = cDirectoryUtils::FindFirstOf(path_ptr, PATH_DELIMITERS);
         if(pos < 0) {
            return true;
         } else {
            return false;
         }
      }
   }
}

bool cDirectoryUtils::IsDriveChar(char c)
{
   return(c == ':');
}

STRING_T cDirectoryUtils::LeftStrip(const char * path)
{
   STRING_T component;
   return LeftStrip(path, component);
}

STRING_T cDirectoryUtils::LeftStrip(const char * path, STRING_T &component)
{
   component = "";
   int len = strlen(path);
   int i = 0;
   for(i=0; i<len; i++) {
      if(path[i] == '/' ||
          path[i] == '\\') {
         break;
      }
   }
   STRING_T new_path;
   if(i != len) {
      new_path = &(path[i+1]);
      component = cDirectoryUtils::Left(path, i);
   } else {
      new_path = "";
      component = path;
   }
   return new_path;
}

STRING_T cDirectoryUtils::RightStrip(const char * path)
{
   STRING_T component;
   return RightStrip(path, component);
}

STRING_T cDirectoryUtils::RightStrip(const char * path, STRING_T &component)
{
   component = "";
   int len = strlen(path);
   int i = 0;
   for(i=len; i>=0; i--) {
      if(path[i] == '/' ||
          path[i] == '\\') {
         break;
      }
   }
   STRING_T new_path;
   if(i > 0) {
      new_path = cDirectoryUtils::Left(path, i);
      component = &(path[i+1]);
   } else {
      new_path = "";
      component = path;
   }
   return new_path;
}

void cDirectoryUtils::NameComponents(const char * file_name, STRING_T &base_name, STRING_T &extension)
{
   int len = strlen(file_name);
   int i = 0;
   for(i=len; i>=0; i--) {
      if(file_name[i] == '.') {
         break;
      }
   }
   if(i > 0) {
      base_name = cDirectoryUtils::Left(file_name, i);
      extension = &(file_name[i+1]);
   } else {
      base_name = file_name;
      extension = "";
   }
}

STRING_T cDirectoryUtils::Resolve(const char * path)
{
   /// ?????????????
   if(path[0] == '/') {
      return path;
   }
   STRING_T new_path = path;
   STRING_VECTOR_T ppath;
   int len = strlen(path);
   int prev_pos = 0;
   int i = 0;
   for(i=0; i<len; i++) {
      if(path[i] == '/' ||
          path[i] == '\\') {
         int pos = ppath.size();
         ppath.resize(pos+1);
         STRING_T c = cDirectoryUtils::Left(&(path[prev_pos]), i -(prev_pos));
         ppath[pos] = c; 
         prev_pos = i + 1;
      }
   }
   if(path[len-1] != '/' &&
       path[len-1] != '\\') {
      int pos = ppath.size();
      ppath.resize(pos+1);
      STRING_T c = cDirectoryUtils::Left(&(path[prev_pos]), i -(prev_pos));
      ppath[pos] = c; 
   }
   int size = ppath.size();
   for(i=1; i<size; i++) {
      if(ppath[i] == ".." &&
          ppath[i-1] != "..") {
         int j = 0;
         if(i < size - 1) {
            for(j=i; j<size; j++) {
               ppath[j-1] = ppath[j+1];
            }
         }
         ppath.resize(size-2);
      }
   }
   size = ppath.size();
   if(size > 0) {
      new_path = ppath[0];
      for(i=1; i<size; i++) {
         new_path = cDirectoryUtils::AppendPath(new_path.c_str(), ppath[i].c_str());
      }
   } else {
      new_path = "";
   }
   return new_path;
}



/// strings

STRING_T cDirectoryUtils::Trim(const char * str, char trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if(str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size =(str_len + 100);
      buffer_ptr =(char*)__ALLOC__(buffer_size);
      if(buffer_ptr == NULL) return str;
   }
   const char * result = Trim(str, buffer_ptr, buffer_size, trim_char);
   if(str_len >= sizeof(buffer) - 1) {
		__FREE__(buffer_ptr);
   }
   return result;
}

const char * cDirectoryUtils::Trim(const char * str, char *buf, unsigned long buf_size, char trim_char)
{
   bool started = false;
   unsigned int str_len = strlen(str);
   if(str_len >= buf_size) return NULL;
   const char * str_ptr = str;
   char * buf_ptr = buf;
   for(unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if(!started) {
         if(c == trim_char) {
            str_ptr++;
         } else {
            started = true;
            *buf_ptr = c;
            str_ptr++;
            buf_ptr++;
         }
      } else {
         *buf_ptr = c;
         str_ptr++;
         buf_ptr++;
      }
   }
   int j;
   for(j=strlen(buf)-1; j>=0; j--) {
      char c = buf[j];
      if(c != trim_char) break;
   }
   j++;
   buf[j] = '\0';
   return buf;
}

STRING_T cDirectoryUtils::LTrim(const char * str, char trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   unsigned int str_len = strlen(str);
   if(str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size =(str_len + 100);
      buffer_ptr =(char*)__ALLOC__(buffer_size);
      if(buffer_ptr == NULL) return str;
   }
   bool started = false;
   const char * str_ptr = str;
   char * buf_ptr = buffer_ptr;
   for(unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if(!started) {
         if(c == trim_char) {
            str_ptr++;
         } else {
            started = true;
            *buf_ptr = c;
            str_ptr++;
            buf_ptr++;
         }
      } else {
         *buf_ptr = c;
         str_ptr++;
         buf_ptr++;
      }
   }
   if(str_len >= sizeof(buffer) - 1) {
		__FREE__(buffer_ptr);
   }
   return buffer_ptr;
}

STRING_T cDirectoryUtils::RTrim(const char * str, char trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if(str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size =(str_len + 100);
      buffer_ptr =(char*)__ALLOC__(buffer_size);
      if(buffer_ptr == NULL) return str;
   }
   memcpy(buffer_ptr, str, str_len);
   int j;
   for(j=buffer_size-1; j>=0; j--) {
      char c = buffer_ptr[j];
      if(c != '\0' && c != trim_char) break;
   }
   if(j <(int)buffer_size) j++;
   buffer_ptr[j] = '\0';
   if(str_len >= sizeof(buffer) - 1) {
		__FREE__(buffer_ptr);
   }
   return buffer_ptr;
}

long cDirectoryUtils::Find(STRING_T &str, const char * sub_str)
{
   return str.find(sub_str);
}

long cDirectoryUtils::Find(const char * str, const char * sub_str)
{
   STRING_T _str = str;
   return Find(_str, sub_str);
}

long cDirectoryUtils::FindFirstOf(STRING_T &str, const char * sub_str)
{
   return str.find_first_of(sub_str);
}

long cDirectoryUtils::FindFirstOf(const char * str, const char * sub_str)
{
   STRING_T _str = str;
   return FindFirstOf(_str, sub_str);
}

long cDirectoryUtils::FindLastOf(STRING_T &str, const char * sub_str)
{
   return str.find_last_of(sub_str);
}

long cDirectoryUtils::FindLastOf(const char * str, const char * sub_str)
{
   STRING_T _str = str;
   return FindLastOf(_str, sub_str);
}

STRING_T cDirectoryUtils::Left(STRING_T &str, unsigned long len)
{
   if(len > str.size()) {
      return str.c_str();
   } else {
      return STRING_T(str.c_str(), len);
   }
}

STRING_T cDirectoryUtils::Left(const char * str, unsigned long len)
{
   STRING_T _str = str;
   return Left(_str, len);
}

STRING_T cDirectoryUtils::Right(STRING_T &str, unsigned long len)
{
   if(len > str.size()) {
      return str.c_str();
   } else {
      int pos = str.size() - len;
      return &str.c_str()[pos];
   }
}

STRING_T cDirectoryUtils::Right(const char * str, unsigned long len)
{
   STRING_T _str = str;
   return Right(_str, len);
}

