
#include "cConfigUtils.h"

char * cConfigUtils::_Buffer = NULL;

#define ALLOC_BUFFER() \
   if (_Buffer == NULL) { \
      _Buffer = (char*)calloc(1, BUFFER_SIZE); \
   }

char * cConfigUtils::Buffer()
{
   ALLOC_BUFFER();
   return _Buffer;
}

ULONG_T cConfigUtils::BufferSize()
{
   return BUFFER_SIZE;
}

STRING_T cConfigUtils::POSIX_Path(const char * path)
{
   ALLOC_BUFFER();
   sprintf(_Buffer, "%s", path);
   ULONG_T len = strlen(path);
   for (ULONG_T i=0; i<len; i++) {
      if (_Buffer[i] == '\\') {
         _Buffer[i] = '/';
      }
   }
   return _Buffer;
}

STRING_T cConfigUtils::ResolveSymbols(const char * str, BOOL_T posix)
{
   int len = strlen(str);
   STRING_T new_str = str;
   char head[0x100] = {0};
   char var[0x100] = {0};
   char tail[0x200] = {0};
   if (strncmp(str, "$(", 2) == 0) {
      int params = sscanf(str, "$(%[^)])%s", var, tail);
      if (params == 2) {
         char * content = getenv(var);
         if (content == NULL) {
            printf("environment variable %s not set\n", var);
         } else {
            if (posix) {
               new_str = POSIX_Path(content);
               new_str += POSIX_Path(tail).c_str();
            } else {
               new_str = content;
               new_str += tail;
            }
         }
      }
   } else if (strncmp(str, "%(", 2) == 0) {
      int params = sscanf(str, "$(%[^)])%s", var, tail);
      if (params == 2) {
         STRING_T content = GetSymbol(var);
         if (posix) {
            new_str = POSIX_Path(content.c_str());
            new_str += POSIX_Path(tail).c_str();
         } else {
            new_str = content.c_str();
            new_str += tail;
         }
      }
   } else {
      STRING_T symbol;
      int params = 0;
      if ((params = sscanf(str, "%[^$]$(%[^)])%s", head, var, tail)) > 1) {
         char * content = getenv(var);
         if (content == NULL) {
            symbol = GetSymbol(var);
         } else {
            symbol = content;
         }
         if (posix) {
            new_str = POSIX_Path(head);
            new_str += POSIX_Path(symbol.c_str()).c_str();
            if (params > 2) {
               new_str += POSIX_Path(tail).c_str();
            }
         } else {
            new_str = head;
            new_str += symbol.c_str();
            if (params > 2) {
               new_str += tail;
            }
         }
      }
   }
   return new_str;
}

STRING_T cConfigUtils::RelPath(const char * dir, const char * path)
{
   STRING_T rel_path;
   STRING_T _dir = dir;
   STRING_T _path = path;
   STRING_T left_dir;
   STRING_T left_path;
   _dir = cFileSystemUtils::LeftStrip(_dir.c_str(), left_dir);
   _path = cFileSystemUtils::LeftStrip(_path.c_str(), left_path);
   if (left_path.size() == 0 &&
      cFileSystemUtils::get_Type() == FSYS_UNIX) {
      return path;
   }
   while (_stricmp(left_dir.c_str(), left_path.c_str()) == 0) {
      if (left_dir.size() == 0) {
         return "./";
      }
      _dir = cFileSystemUtils::LeftStrip(_dir.c_str(), left_dir);
      _path = cFileSystemUtils::LeftStrip(_path.c_str(), left_path);
   }
   int levels = 0;
   while (left_dir.size() > 0) {
      levels++;
      _dir = cFileSystemUtils::LeftStrip(_dir.c_str(), left_dir);
   }
   int i = 0;
   for (i=0; i<levels; i++) {
      rel_path = cFileSystemUtils::AppendPath(rel_path.c_str(), "..");
   }
   rel_path = cFileSystemUtils::AppendPath(rel_path.c_str(), left_path.c_str());
   if (_path.size() > 0) {
      rel_path = cFileSystemUtils::AppendPath(rel_path.c_str(), _path.c_str());
   }
   rel_path = cFileSystemUtils::Resolve(rel_path.c_str());
   return rel_path;
}

BOOL_T cConfigUtils::CreateDir (CONST_STRING_T directory)
{
   return cFileSystemUtils::CreateDir(directory);
}

BOOL_T cConfigUtils::RemoveFile (CONST_STRING_T file)
{
   return cFileSystemUtils::RemoveFile(file);
}

BOOL_T cConfigUtils::RenameFile (CONST_STRING_T src_path, CONST_STRING_T dst_path)
{
   return cFileSystemUtils::RenameFile(src_path, dst_path);
}

BOOL_T cConfigUtils::DirExists (CONST_STRING_T path)
{
   return cFileSystemUtils::DirExists(path);
}

BOOL_T cConfigUtils::FileExists (CONST_STRING_T path)
{
   return cFileSystemUtils::FileExists(path);
}

BOOL_T cConfigUtils::FileExistence (STRING_VECTOR_T &paths, CONST_STRING_T file_name, STRING_T &file)
{
   return cFileSystemUtils::FileExistence (paths, file_name, file);
}

ULONG_T cConfigUtils::FileSize (CONST_STRING_T path)
{
   return cFileSystemUtils::FileSize(path);
}

BOOL_T cConfigUtils::FileList (STRING_LIST_T &file_names, CONST_STRING_T path, CONST_STRING_T pattern)
{
   return cFileSystemUtils::FileList(file_names, path, pattern);
}

STRING_T cConfigUtils::FullPath (CONST_STRING_T path)
{
   return cFileSystemUtils::FullPath(path);
}

void cConfigUtils::LeftSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
   cFileSystemUtils::LeftSplit(path, head, tail);
}

void cConfigUtils::RightSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail)
{
   cFileSystemUtils::RightSplit(path, head, tail);
}

STRING_T cConfigUtils::AppendPath (CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter)
{
   return cFileSystemUtils::AppendPath(head, tail, delimiter);
}

STRING_T cConfigUtils::FileName (CONST_STRING_T path)
{
   return cFileSystemUtils::FileName(path);
}

STRING_T cConfigUtils::BaseFileName (CONST_STRING_T path)
{
   return cFileSystemUtils::BaseFileName(path);
}

STRING_T cConfigUtils::DirName (CONST_STRING_T path)
{
   return cFileSystemUtils::DirName(path);
}

STRING_T cConfigUtils::DriveName (CONST_STRING_T path)
{
   return cFileSystemUtils::DriveName(path);
}

STRING_T cConfigUtils::FileExtension (CONST_STRING_T path)
{
   return cFileSystemUtils::FileExtension(path);
}

STRING_T cConfigUtils::CurrentDir ()
{
   return cFileSystemUtils::CurrentDir();
}

STRING_T cConfigUtils::CurrentDrive ()
{
   return cFileSystemUtils::CurrentDrive ();
}

STRING_T cConfigUtils::StartupDir ()
{
   return cFileSystemUtils::StartupDir ();
}

BOOL_T cConfigUtils::IsRelativePath (CONST_STRING_T path)
{
   return cFileSystemUtils::IsRelativePath (path);
}

BOOL_T cConfigUtils::IsAbsolutePath (CONST_STRING_T path)
{
   return cFileSystemUtils::IsAbsolutePath (path);
}

BOOL_T cConfigUtils::IsUNCPath (CONST_STRING_T path)
{
   return cFileSystemUtils::IsUNCPath (path);
}

BOOL_T cConfigUtils::IsPathDelimiter (CHAR_T c)
{
   return cFileSystemUtils::IsPathDelimiter (c);
}

BOOL_T cConfigUtils::IsDrive (CONST_STRING_T path)
{
   return cFileSystemUtils::IsDrive (path);
}

BOOL_T cConfigUtils::IsUNCRoot (CONST_STRING_T path)
{
   return cFileSystemUtils::IsUNCRoot (path);
}

BOOL_T cConfigUtils::IsDriveChar (CHAR_T c)
{
   return cFileSystemUtils::IsDriveChar (c);
}

INT_T cConfigUtils::WriteProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value, CONST_STRING_T file)
{
   return cFileSystemUtils::WriteProfileString(chapter, key, value, file);
}

STRING_T cConfigUtils::GetProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T default_value, CONST_STRING_T file)
{
   return cFileSystemUtils::GetProfileString(chapter, key, default_value, file);
}

