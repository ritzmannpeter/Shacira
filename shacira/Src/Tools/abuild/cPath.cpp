
#include "cPath.h"

cPath::cPath(const char * path_spec)
{
   _Path = Normalize(path_spec);
   _AbsolutePath = cDirectoryUtils::FullPath(_Path.c_str());
//AddVFS(_AbsolutePath.c_str());
   _Name = cDirectoryUtils::FileName(_AbsolutePath.c_str());
   cDirectoryUtils::NameComponents(_Name.c_str(), _BaseName, _Extension);
   _IsDirectory = cDirectoryUtils::IsDirectory(_AbsolutePath.c_str());
}

cPath::~cPath()
{
}

bool cPath::Exists()
{
   bool exists = false;
   if (_IsDirectory) {
      exists = cDirectoryUtils::DirExists(_AbsolutePath.c_str());
   } else {
      exists = cDirectoryUtils::FileExists(_AbsolutePath.c_str());
   }
   if (!exists) {
      exists = FindVFS(_AbsolutePath.c_str());
   }
   return exists;
}

STRING_T cPath::RelativePath(const char * directory)
{
   return cDirectoryUtils::RelPath(directory, _AbsolutePath.c_str());
}

STRING_T cPath::Normalize(const char * path)
{
   unsigned long size = strlen(path);
   char * temp_path = (char*)__ALLOC__(size+1);
   memcpy(temp_path, path, size);
   unsigned long i = 0;
   for (i=0; i<size; i++) {
      if (path[i] == '\\') {
         temp_path[i] = '/';
      }
   }
   STRING_T normalized_path = temp_path;
   __FREE__(temp_path);
   normalized_path = ResolveSymbols(normalized_path.c_str());
   return normalized_path;
}

STRING_T cPath::ResolveSymbols(const char * str)
{
   int len = strlen(str);
   const char * str_ptr = 0;
   STRING_T new_str;
   int i = 0;
   for (i=0; i<len; i++) {
      str_ptr = &(str[i]);
      char var[0x100] = {0};
      if (strncmp(str_ptr, "$(", 2) == 0) {
         int n = 0;
         int params = sscanf(str_ptr, "$(%[^)])%n", var, &n);
         if (params == 1) {
            char * content = getenv(var);
            if (content == NULL) {
               Printf("environment variable %s not set\n", var);
            } else {
               new_str += content;
            }
            i += (n - 1);
         }
      } else {
         new_str += *str_ptr;
      }
   }
   return new_str;
}
