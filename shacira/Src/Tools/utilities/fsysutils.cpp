
#include "fsysutils.h"
#include <malloc.h>

char * StrAlloc(unsigned long size)
{
   return (char*)calloc(1, size);
}

void StrFree(char * string)
{
   free(string);
}

cSString::cSString()
{
   _String = NULL;
   _RefCount = 0;
}

cSString::cSString(cSString & right)
{
   _String = NULL;
   _RefCount = 0;
   const char * string = right.c_str();
   ULONG_T len = strlen(string);
   if (len > 0) {
      _String = StrAlloc(len+1);
      strcpy(_String, string);
   }
}

cSString::cSString(const char * string)
{
   _String = NULL;
   _RefCount = 0;
   int len = strlen(string);
   _String = StrAlloc(len+1);
   strcpy(_String, string);
}

cSString::cSString(const char * string, unsigned long len)
{
   _String = NULL;
   _RefCount = 0;
   _String = StrAlloc(len+1);
   strncpy(_String, string, len);
}

cSString::~cSString()
{
   if (_String != NULL) {
      StrFree(_String);
      _String = NULL;
   }
}

const char * cSString::c_str()
{
   if (_String == NULL) {
      return "";
   } else {
      return _String;
   }
}

unsigned long cSString::size()
{
   if (_String == NULL) {
      return 0;
   } else {
      return strlen(_String);
   }
}

cSString cSString::operator +(cSString & right)
{
   const char * str1 = _String;
   const char * str2 = right.c_str();
   ULONG_T size1 = size();
   ULONG_T size2 = right.size();
   ULONG_T new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cSString new_string = cSString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cSString cSString::operator +(const char * right)
{
   const char * str1 = _String;
   const char * str2 = right;
   ULONG_T size1 = size();
   ULONG_T size2 = strlen(right);
   ULONG_T new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cSString new_string = cSString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cSString cSString::operator +=(cSString & right)
{
   const char * str1 = _String;
   const char * str2 = right.c_str();
   ULONG_T size1 = size();
   ULONG_T size2 = right.size();
   ULONG_T new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cSString cSString::operator +=(const char * right)
{
   const char * str1 = _String;
   const char * str2 = right;
   ULONG_T size1 = size();
   ULONG_T size2 = strlen(right);
   ULONG_T new_size = size1 + size2;
   char * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cSString::operator =(cSString & right)
{
   char * new_buf = NULL;
   const char * string = right.c_str();
   ULONG_T size = right.size();
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      strcpy(new_buf, string);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
}

cSString::operator =(const char * right)
{
   char * new_buf = NULL;
   const char * string = right;
   ULONG_T size = strlen(right);
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      strcpy(new_buf, string);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
}

char cSString::operator [](unsigned long index)
{
   if (_String == NULL) {
      return 0;
   } else {   
      if (index < size()) {
         return _String[index];
      } else {
         return 0;
      }
   }
}

void cSString::clear()
{
}


#ifdef lassma

STRING_T Trim (CONST_STRING_T str, CHAR_T trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = StrAlloc(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   const char * result = Trim(str, buffer_ptr, buffer_size, trim_char);
   if (str_len >= sizeof(buffer) - 1) {
		StrFree(buffer_ptr);
   }
   return result;
}

CONST_STRING_T Trim (CONST_STRING_T str, CHAR_T *buf, ULONG_T buf_size, CHAR_T trim_char)
{
   bool started = false;
   unsigned int str_len = strlen(str);
   if (str_len >= buf_size) return NULL;
   const char * str_ptr = str;
   char * buf_ptr = buf;
   for (unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if (!started) {
         if (c == trim_char) {
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
   for (j=strlen(buf)-1; j>=0; j--) {
      char c = buf[j];
      if (c != trim_char) break;
   }
   j++;
   buf[j] = '\0';
   return buf;
}

STRING_T LTrim (CONST_STRING_T str, CHAR_T trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   unsigned int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = StrAlloc(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   bool started = false;
   const char * str_ptr = str;
   char * buf_ptr = buffer_ptr;
   for (unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if (!started) {
         if (c == trim_char) {
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
   if (str_len >= sizeof(buffer) - 1) {
		StrFree(buffer_ptr);
   }
   return buffer_ptr;
}

STRING_T RTrim (CONST_STRING_T str, CHAR_T trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = StrAlloc(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   memcpy(buffer_ptr, str, str_len);
   int j;
   for (j=buffer_size-1; j>=0; j--) {
      char c = buffer_ptr[j];
      if (c != '\0' && c != trim_char) break;
   }
   if (j < (int)buffer_size) j++;
   buffer_ptr[j] = '\0';
   if (str_len >= sizeof(buffer) - 1) {
		StrFree(buffer_ptr);
   }
   return buffer_ptr;
}

INT_T Find (STRING_T &str, CONST_STRING_T sub_str)
{
   return str.find(sub_str);
}

INT_T Find (CONST_STRING_T str, CONST_STRING_T sub_str)
{
   STRING_T _str = str;
   return Find(_str, sub_str);
}

INT_T FindFirstOf (STRING_T &str, CONST_STRING_T sub_str)
{
   return str.find_first_of(sub_str);
}

INT_T FindFirstOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
   STRING_T _str = str;
   return FindFirstOf(_str, sub_str);
}

INT_T FindLastOf (STRING_T &str, CONST_STRING_T sub_str)
{
   return str.find_last_of(sub_str);
}

INT_T FindLastOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
   STRING_T _str = str;
   return FindLastOf(_str, sub_str);
}

STRING_T Left (STRING_T &str, ULONG_T len)
{
   if (len > str.size()) {
      return str.c_str();
   } else {
      return STRING_T(str.c_str(), len);
   }
}

STRING_T Left (CONST_STRING_T str, ULONG_T len)
{
   STRING_T _str = str;
   return Left(_str, len);
}

STRING_T Right (STRING_T &str, ULONG_T len)
{
   if (len > str.size()) {
      return str.c_str();
   } else {
      int pos = str.size() - len;
      return &str.c_str()[pos];
   }
}

STRING_T Right (CONST_STRING_T str, ULONG_T len)
{
   STRING_T _str = str;
   return Right(_str, len);
}

STRING_T Replace (STRING_T &str, CONST_STRING_T sub_str, CONST_STRING_T rep_str)
{
   int sub_len = strlen(sub_str);
   int rep_len = strlen(rep_str);
   STRING_T new_string = str.c_str();
   int search_pos = 0;
   int pos = new_string.find(sub_str, search_pos);
   while (pos >= 0) {
      new_string.replace(pos, sub_len, rep_str);
      search_pos = pos + rep_len;
      pos = new_string.find(sub_str, search_pos);
   }
   return new_string;
}

void LeftSplit (CONST_STRING_T str, STRING_T &head, STRING_T &tail, CHAR_T separator)
{
   char delimiters[2] = {0};
   delimiters[0] = separator;
   int pos = FindFirstOf(str, delimiters);
   if (pos < 0) {
      head = str;
      tail = "";
   } else {
      head = Left(str, pos);
      tail = Right(str, strlen(str) - (pos + 1));
   }
}

void GetStringSequence (CONST_STRING_T str, STRING_T &sequence, int &nchars, CHAR_T separator)
{
   char buffer[2] = {0};
   int i, len = strlen(str);
   int separator_count = 0;
   nchars = 0;
   for (i=0; i<len; i++) {
      char c = str[i];
      if (c == separator) {
         if (separator_count == 0) {
            separator_count++;
         } else if (separator_count == 1) {
            nchars++;
            return;
         }
      } else {
         if (separator_count == 0) {
            // ignore
         } else if (separator_count == 1) {
            buffer[0] = c;
            sequence += buffer;
         } else {
            return;
         }
      }
      nchars++;
   }
}

#endif


INT_T FindFirstOf (STRING_T &str, CONST_STRING_T sub_str)
{
   int i1 = 0;
   char c1 = sub_str[i1];
   while (c1 != 0) {
      int i2 = 0;
      char c2 = str[i2];
      while (c2 != 0) {
         if (c1 == c2) {
            return i2;
         }
         i2++;
         c2 = str[i2];
      }
      i1++;
      c1 = sub_str[i1];
   }
   return -1;
}

INT_T FindFirstOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
   STRING_T _str = str;
   return FindFirstOf(_str, sub_str);
}

INT_T FindLastOf (STRING_T &str, CONST_STRING_T sub_str)
{

   return 0;
}

INT_T FindLastOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
   STRING_T _str = str;
   return FindLastOf(_str, sub_str);
}

STRING_T Left (STRING_T &str, ULONG_T len)
{
   if (len > str.size()) {
      return str.c_str();
   } else {
      return STRING_T(str.c_str(), len);
   }
}

STRING_T Left (CONST_STRING_T str, ULONG_T len)
{
   STRING_T _str = str;
   return Left(_str, len);
}

STRING_T Right (STRING_T &str, ULONG_T len)
{
   if (len > str.size()) {
      return str.c_str();
   } else {
      int pos = str.size() - len;
      return &str.c_str()[pos];
   }
}

STRING_T Right (CONST_STRING_T str, ULONG_T len)
{
   STRING_T _str = str;
   return Right(_str, len);
}

STRING_T LTrim (CONST_STRING_T str, CHAR_T trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   unsigned int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = StrAlloc(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   bool started = false;
   const char * str_ptr = str;
   char * buf_ptr = buffer_ptr;
   for (unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if (!started) {
         if (c == trim_char) {
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
   if (str_len >= sizeof(buffer) - 1) {
		StrFree(buffer_ptr);
   }
   return buffer_ptr;
}

STRING_T RTrim (CONST_STRING_T str, CHAR_T trim_char)
{
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = StrAlloc(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   memcpy(buffer_ptr, str, str_len);
   int j;
   for (j=buffer_size-1; j>=0; j--) {
      char c = buffer_ptr[j];
      if (c != '\0' && c != trim_char) break;
   }
   if (j < (int)buffer_size) j++;
   buffer_ptr[j] = '\0';
   if (str_len >= sizeof(buffer) - 1) {
		StrFree(buffer_ptr);
   }
   return buffer_ptr;
}











BOOL_T CreateDir (CONST_STRING_T directory)
{
   STRING_T path = FullPath(directory);
   STRING_T temp_path;
   STRING_T head, tail;
   LeftSplit(path.c_str(), head, tail);
   while (head.size() > 0) {
      temp_path = AppendPath(temp_path.c_str(), head.c_str());
      if (!IsDrive(temp_path.c_str()) &&
          !IsUNCRoot(temp_path.c_str())) {
         if (!DirExists(temp_path.c_str())) {
            int success = CreateDirectory(temp_path.c_str(), NULL);
            if (!success) {
               return false;
            }
         }
      }
      LeftSplit(tail.c_str(), head, tail);
   }
   return true;
}

BOOL_T RemoveFile (CONST_STRING_T file)
{
   if (remove(file) == 0) {
      return true;
   } else {
      return false;
   }
}

BOOL_T RenameFile (CONST_STRING_T src_path, CONST_STRING_T dst_path)
{
   if (rename(src_path, dst_path) == 0) {
      return true;
   } else {
      return false;
   }
}

BOOL_T DirExists (CONST_STRING_T path)
{
#ifdef __WIN32__
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
#else
#endif
   return false;
}

BOOL_T FileExists (CONST_STRING_T path)
{
#ifdef __WIN32__
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
#else
#endif
   return false;
}

ULONG_T FileSize (CONST_STRING_T path)
{
#ifdef __WIN32__
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
#else
#endif
   return 0;
}

STRING_T FullPath (CONST_STRING_T path)
{
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
}

void LeftSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
   int pos = FindFirstOf(path, PATH_DELIMITERS);
   if (pos < 0) {
      head = path;
      tail = "";
   } else if (pos == 0) {
      if (path[0] == '\\' &&
          path[1] == '\\') {
         /// UNC path
         pos = FindFirstOf(&path[2], PATH_DELIMITERS);
         if (pos < 0) {
            head = path;
            tail = "";
         } else {
            pos += 2;
            head = Left(path, pos);
            tail = Right(path, strlen(path) - (pos + 1));
         }
      }
   } else {
      head = Left(path, pos);
      tail = Right(path, strlen(path) - (pos + 1));
   }
}

void RightSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
   int pos = FindLastOf(path, PATH_DELIMITERS);
   if (pos < 0) {
      head = path;
      tail = "";
   } else {
      head = Left(path, pos);
      tail = Right(path, strlen(path) - (pos + 1));
   }
}

STRING_T AppendPath (CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter)
{
   if (strlen(head) == 0) return tail;
   if (strlen(tail) == 0) return head;
   if (IsAbsolutePath(tail) || IsUNCPath(tail)) return tail;
   STRING_T new_head = RTrim(head, SLASH);
   new_head = RTrim(new_head.c_str(), BACK_SLASH);
   STRING_T new_tail = LTrim(tail, SLASH);
   new_tail = LTrim(new_tail.c_str(), BACK_SLASH);
   STRING_T new_path = new_head;
   new_path += delimiter;
   new_path += new_tail.c_str();
   return new_path;
}

STRING_T FileName (CONST_STRING_T path)
{
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   if (directory.size() > 0 && file_name.size() == 0) file_name = directory;
   return file_name;
}

STRING_T BaseFileName (CONST_STRING_T path)
{
   STRING_T base_file_name = FileName(path);
   int pos = FindFirstOf(base_file_name.c_str(), ".");
   if (pos < 0) {
      return base_file_name;
   } else {
      return Left(base_file_name.c_str(), pos);
   }
}

STRING_T DirName (CONST_STRING_T path)
{
   STRING_T file_name;
   STRING_T directory;
   RightSplit(path, directory, file_name);
   return directory;
}

STRING_T DriveName (CONST_STRING_T path)
{
   if (IsUNCPath(path)) return "";
   if (IsRelativePath(path)) {
      return DriveName(CurrentDir().c_str());
   }
   STRING_T drive_name = Left(path, 2);
   if (IsPathDelimiter(drive_name[0])) {
      drive_name.clear();
   }
   return drive_name;
}

STRING_T FileExtension (CONST_STRING_T path)
{
   int pos = FindLastOf(path, ".");
   STRING_T file_extension = Right(path, strlen(path) - pos);
   return file_extension;
}

STRING_T CurrentDir ()
{
   char current_directory[1024] = {0};
   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
   if (len > 0) {
      return current_directory;
   } else {
      return "Current directory unknown";
   }
}

STRING_T CurrentDrive ()
{
   STRING_T current_directory = CurrentDir();
   STRING_T current_drive = Left(current_directory, 2);
   return current_drive;
}

BOOL_T IsRelativePath (CONST_STRING_T path)
{
   int len = strlen(path);
   if (len == 0) return true;
   if (IsPathDelimiter(path[0])) {
      return false;
   } else if (len > 1 && IsDriveChar(path[1])) {
      return false;
   } else {
      return true;
   }
}

BOOL_T IsAbsolutePath (CONST_STRING_T path)
{
   return !IsRelativePath(path);
}

BOOL_T IsUNCPath (CONST_STRING_T path)
{
   if (path[0] == BACK_SLASH && path[1] == BACK_SLASH) {
      return true;
   } else {
      return false;
   }
}

BOOL_T IsPathDelimiter (CHAR_T c)
{
   return (c == BACK_SLASH || c == SLASH);
}

BOOL_T IsDrive (CONST_STRING_T path)
{
   if (strlen(path) == 2 && IsDriveChar(path[1])) {
      return true;
   } else {
      return false;
   }
}

BOOL_T IsUNCRoot (CONST_STRING_T path)
{
   if (path[0] != '\\' ||
       path[1] != '\\') {
      return false;
   } else {
      const char * path_ptr = &path[2];
      int pos = FindFirstOf(path_ptr, PATH_DELIMITERS);
      if (pos < 0) {
         return true;
      } else {
         path_ptr = &path[pos + 2 + 1];
         pos = FindFirstOf(path_ptr, PATH_DELIMITERS);
         if (pos < 0) {
            return true;
         } else {
            return false;
         }
      }
   }
}

BOOL_T IsDriveChar (CHAR_T c)
{
   return (c == ':');
}
