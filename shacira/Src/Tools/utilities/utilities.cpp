
#include "utilities.h"
#include "safefunctions.h"

#if defined(__linux__)
#include <unistd.h>
#endif

void GetWorkingDirectory(char * buf, unsigned long buf_size)
{
#if defined(_WIN32)
   DWORD len = GetCurrentDirectory(buf_size, buf);
#elif defined(__linux__)
   unsigned long len = buf_size - 1;
   char current_directory[0x400] = {0};
   char * current_dir = getcwd(current_directory, sizeof(current_directory));
   if (current_dir != NULL) {
      if (strlen(current_dir) < len) {
         len = strlen(current_dir);
      }
      strncpy(buf, current_dir, len);
   }
#else
NO_PLATFORM
#endif
}

void GetFullPath(const char * path, char * buf, unsigned long buf_size)
{
}

void AppendPath(const char * path, char * buf, unsigned long buf_size)
{
   unsigned long path_len = strlen(buf);
   if (path_len == 0) {
      SafeStrCpy(buf, path, buf_size);
   } else if (buf[path_len - 1] == '\\' ||
              buf[path_len - 1] == '/') {
      SafeStrCpy(&buf[path_len], path, buf_size - path_len);
   } else {
      buf[path_len] = '/';
      SafeStrCpy(&buf[path_len+1], path, buf_size -path_len - 1);
   }
}

void StripFileName(char * path)
{
}

bool IsRelativePath(const char * path)
{
   if (path[0] == '/' || path[0] == '\\') return false;
   if (path[1] == ':') return false;
   return true;
}

unsigned long GetToken(const char * str, const char delimiter,
                       char * buf, unsigned long buf_size)
{
   char c = 0;
   unsigned long pos = 0;
   while (42) {
      c = str[pos];
      if (c == delimiter ||
          c == 0 ||
          pos == buf_size) {
         if (pos < buf_size) {
            buf[pos] = 0;
         } else {
            if (pos > 0) {
               buf[pos - 1] = 0;
            }
         }
         if (c == 0 && pos > 0) {
            return pos -1;
         } else {
            return pos;
         }
      } else {
         buf[pos] = str[pos];
      }
      pos++;
   }
}

bool FileExists(const char * file_name)
{
#if defined(_WIN32)
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   hFind = FindFirstFile(file_name, &find_data);
   if (hFind == INVALID_HANDLE_VALUE) {
      return false;
   } else {
      FindClose(hFind);
      return true;
   }
#elif defined(__linux__)
   int rc = access(file_name, F_OK);
   if (rc == 0) {
      return true;
   } else {
      return false;
   }
#else
NO_PLATFORM
#endif
}

void FileTime(const char * file_name, char * buf, unsigned long buf_size)
{
#if defined(_WIN32)
   HANDLE fhnd = CreateFile(file_name,           // file name
                      GENERIC_READ,              // access mode
                      0,                         // share mode
                      NULL,                      // SD
                      OPEN_EXISTING,             // how to create
                      FILE_ATTRIBUTE_NORMAL,     // file attributes
                      NULL                       // handle to template file
                           );
   if (fhnd != INVALID_HANDLE_VALUE) {
      BY_HANDLE_FILE_INFORMATION info = {0};
      if (GetFileInformationByHandle(fhnd, &info)) {
         SYSTEMTIME system_time = {0};
         if (FileTimeToSystemTime(&info.ftLastWriteTime,
                                  &system_time)) {
            sprintf(buf, "%02d.%02d.%04d %02d:%02d:%02d",
                    system_time.wDay,
                    system_time.wMonth,
                    system_time.wYear,
                    system_time.wHour,
                    system_time.wMinute,
                    system_time.wSecond);
         }
      }
      CloseHandle(fhnd);
   }
#elif defined(__linux__)
#warning "not ported to linux"
#else
NO_PLATFORM
#endif
}

const char * SearchFile(const char * file_name,
                        char * buf, unsigned long buf_size,
                        const char * path_list, const char * rel_path)
{
   char token[512] = {0};
   unsigned long buf_pos = 0;
   const char * buf_ptr = path_list;
   unsigned long token_len = GetToken(buf_ptr, ';', token, sizeof(token));
   while (token_len > 0) {
      if (IsRelativePath(token)) {
         if (rel_path == NULL ||
             strcmp(rel_path, token) != 0) {
            const char * found_path = SearchFile(file_name, buf, buf_size,
                                                 path_list, token);
            if (found_path != NULL) {
               return buf;
            }
         }
      } else {
         char search_path[512] = {0};
         SafeStrCpy(search_path, token, sizeof(search_path));
         if (rel_path != NULL) {
            AppendPath(rel_path, search_path, sizeof(search_path));
         }
         AppendPath(file_name, search_path, sizeof(search_path));
         if (FileExists(search_path)) {
            SafeStrCpy(buf, search_path, buf_size);
            StripFileName(buf);
            return buf;
         }
      }
      buf_pos += token_len + 1;
      buf_ptr = &path_list[buf_pos];
      token_len = GetToken(buf_ptr, ';', token, sizeof(token));
   }
   return NULL;
}

const char * GetArg(int i, int argc, char*argv[], int opt_len)
{
   const char * arg = &argv[i][opt_len];
   if (*arg != NULL) {
      return arg;
   } else {
      if (i + 1 < argc) {
         arg = argv[i + 1];
         if ((arg != NULL) && (*arg != '-')) {
            return arg;
         } else {
            return NULL;
         }
      } else {
         return NULL;
      }
   }
}

bool ReadLine(FILE * file, char * buf, unsigned long buf_size)
{
   memset(buf, 0, buf_size);
   char * _buf = fgets(buf, buf_size, file);
   if (_buf == buf) {
      unsigned long len = strlen(buf);
      if (len > 0 && buf[len - 1] == '\n') {
         buf[len - 1] = 0;
      }
      return true;
   } else {
      return false;
   }
}

void ReplaceChar(char * str, char rep, char subst)
{
   unsigned long len = strlen(str);
   for (unsigned long i=0; i<len; i++) {
      if (str[i] == rep) {
         str[i] = subst;
      }
   }
}
