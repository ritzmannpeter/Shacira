
#ifndef _cdirectoryutils_h
#define _cdirectoryutils_h 1

#include "global_defs.h"

#define PATH_DELIMITERS    "/\\"
#define BACK_SLASH_STRING  "\\"
#define SLASH_STRING       "/"
#define SLASH              '/'
#define BACK_SLASH         '\\'

/// file search flags
#define WALK_RECURSIVE     0x00000001


class cDirectoryUtils 
{
public:
   static const char * _PathDelimiter;
   static bool IsDirectory(const char * path);
   static STRING_T RelPath(const char * dir, const char * path);
   static bool CreateDir(const char * directory);
   static bool RemoveFile(const char * file);
   static bool CopyFile(const char * src_path, const char * dst_path);
   static bool RenameFile(const char * src_path, const char * dst_path);
   static bool DirExists(const char * path);
   static bool FileExists(const char * path);
   static bool FileExistence(STRING_VECTOR_T &paths, const char * file_name, STRING_T &file);
   static unsigned long FileSize(const char * path);
   static bool FileList(STRING_LIST_T &file_names, const char * path = "", unsigned long flags = 0, const char * pattern = "*");
   static STRING_T FullPath(const char * path);
   static void LeftSplit(const char * path, STRING_T &head, STRING_T &tail);
   static void RightSplit(const char * path, STRING_T &head, STRING_T &tail);
//   static STRING_T AppendPath(const char * head, const char * tail, const char * delimiter = SLASH_STRING);
   static STRING_T AppendPath(const char * head, const char * tail, const char * delimiter = _PathDelimiter);
   static STRING_T FileName(const char * path);
   static STRING_T BaseFileName(const char * path);
   static STRING_T DirName(const char * path);
   static STRING_T DriveName(const char * path);
   static STRING_T FileExtension(const char * path);
   static STRING_T CurrentDir();
   static bool SetCurrentDir(const char * directory);
   static STRING_T CurrentDrive();
   static bool SetCurrentDrive(const char * drive);
   static STRING_T StartupDir();
   static bool IsRelativePath(const char * path);
   static bool IsAbsolutePath(const char * path);
   static bool IsUNCPath(const char * path);
   static bool IsPathDelimiter(char c);
   static bool IsDrive(const char * path);
   static bool IsUNCRoot(const char * path);
   static bool IsDriveChar(char c);
   static STRING_T LeftStrip(const char * path);
   static STRING_T LeftStrip(const char * path, STRING_T &component);
   static STRING_T RightStrip(const char * path);
   static STRING_T RightStrip(const char * path, STRING_T &component);
   static void NameComponents(const char * file_name, STRING_T &base_name, STRING_T &extension);
   static STRING_T Resolve(const char * path);


   /// strings
   static STRING_T Trim(const char * str, char trim_char);
   static const char * Trim(const char * str, char *buf, unsigned long buf_size, char trim_char);
   static STRING_T LTrim(const char * str, char trim_char);
   static STRING_T RTrim(const char * str, char trim_char);
   static long Find(STRING_T &str, const char * sub_str);
   static long Find(const char * str, const char * sub_str);
   static long FindFirstOf(STRING_T &str, const char * sub_str);
   static long FindFirstOf(const char * str, const char * sub_str);
   static long FindLastOf(STRING_T &str, const char * sub_str);
   static long FindLastOf(const char * str, const char * sub_str);
   static STRING_T Left(STRING_T &str, unsigned long len);
   static STRING_T Left(const char * str, unsigned long len);
   static STRING_T Right(STRING_T &str, unsigned long len);
   static STRING_T Right(const char * str, unsigned long len);
};

#endif
