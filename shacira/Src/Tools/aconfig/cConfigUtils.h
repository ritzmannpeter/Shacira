
#ifndef _cConfigUtils_h
#define _cConfigUtils_h 	1

#define __DLL_EXPORT__
#define _ASSERT_UNCOND

#pragma warning(disable:4786) /* identifier was truncated to '255' characters in the debug information */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "iostream.h"
#include "string"
#include "list"
#include "vector"
#include "map"

typedef char CHAR_T;
typedef unsigned short WCHAR_T;
typedef unsigned char UCHAR_T;
typedef short SHORT_T;
typedef unsigned short USHORT_T;
typedef int INT_T;
typedef unsigned int UINT_T;
typedef long LONG_T;
typedef unsigned long ULONG_T;
typedef float FLOAT_T;
typedef double DOUBLE_T;
typedef bool BOOL_T;
typedef std::string STRING_T;
typedef const CHAR_T * CONST_STRING_T;
typedef CHAR_T * STRING_BUF_T;
typedef std::wstring WSTRING_T;
typedef const WCHAR_T * CONST_WSTRING_T;
typedef WCHAR_T * WSTRING_BUF_T;
typedef UCHAR_T * BUF_T;
typedef const UCHAR_T * CONST_BUF_T;
typedef WSTRING_T & WBUF_T;
typedef void * PTR_T;
typedef std::list<STRING_T> STRING_LIST_T;
typedef std::list<LONG_T> LONG_LIST_T;
typedef std::list<WSTRING_T> WSTRING_LIST_T;
typedef std::list<FLOAT_T> FLOAT_LIST_T;
typedef std::list<DOUBLE_T> DOUBLE_LIST_T;
typedef std::list<void *> POINTER_LIST_T;
typedef std::vector<BOOL_T> BOOL_VECTOR_T;
typedef std::vector<STRING_T> STRING_VECTOR_T;
typedef std::vector<WSTRING_T> WSTRING_VECTOR_T;
typedef std::vector<void *> POINTER_VECTOR_T;
typedef std::vector<int> INT_VECTOR_T;
typedef std::vector<SHORT_T> SHORT_VECTOR_T;
typedef std::vector<USHORT_T> USHORT_VECTOR_T;
typedef std::vector<INT_T> INT_VECTOR_T;
typedef std::vector<UINT_T> UINT_VECTOR_T;
typedef std::vector<LONG_T> LONG_VECTOR_T;
typedef std::vector<ULONG_T> ULONG_VECTOR_T;
typedef std::vector<BOOL_T> BOOL_VECTOR_T;
typedef std::map<STRING_T, STRING_T> STRING_MAP_T;
typedef std::map<STRING_T, ULONG_T> ULONG_MAP_T;
typedef std::map<STRING_T, LONG_T> LONG_MAP_T;
typedef std::map<STRING_T, BOOL_T> BOOL_MAP_T;

#include <windows.h>
#include <stdarg.h>
#include "System/Sys/cFileSystemUtils.h"

#define BUFFER_SIZE  0x8000

class cConfigUtils {
public:
   static char * Buffer();
   static ULONG_T BufferSize();
   static STRING_T POSIX_Path(const char * path);
   static STRING_T ResolveSymbols(const char * path, BOOL_T posix = true);
   static STRING_T RelPath(const char * dir, const char * path);
   static BOOL_T CreateDir (CONST_STRING_T directory);
   static BOOL_T RemoveFile (CONST_STRING_T file);
   static BOOL_T RenameFile (CONST_STRING_T src_path, CONST_STRING_T dst_path);
   static BOOL_T DirExists (CONST_STRING_T path);
   static BOOL_T FileExists (CONST_STRING_T path);
   static BOOL_T FileExistence (STRING_VECTOR_T &paths, CONST_STRING_T file_name, STRING_T &file);
   static ULONG_T FileSize (CONST_STRING_T path);
   static BOOL_T FileList (STRING_LIST_T &file_names, CONST_STRING_T path = "", CONST_STRING_T pattern = "*");
   static STRING_T FullPath (CONST_STRING_T path);
   static void LeftSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail);
   static void RightSplit (CONST_STRING_T path, STRING_T &head, STRING_T &tail);
   static STRING_T AppendPath (CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter = SLASH_STRING);
   static STRING_T FileName (CONST_STRING_T path);
   static STRING_T BaseFileName (CONST_STRING_T path);
   static STRING_T DirName (CONST_STRING_T path);
   static STRING_T DriveName (CONST_STRING_T path);
   static STRING_T FileExtension (CONST_STRING_T path);
   static STRING_T CurrentDir ();
   static STRING_T CurrentDrive ();
   static STRING_T StartupDir ();
   static BOOL_T IsRelativePath (CONST_STRING_T path);
   static BOOL_T IsAbsolutePath (CONST_STRING_T path);
   static BOOL_T IsUNCPath (CONST_STRING_T path);
   static BOOL_T IsPathDelimiter (CHAR_T c);
   static BOOL_T IsDrive (CONST_STRING_T path);
   static BOOL_T IsUNCRoot (CONST_STRING_T path);
   static BOOL_T IsDriveChar (CHAR_T c);
   static INT_T WriteProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value, CONST_STRING_T file);
   static STRING_T GetProfileString (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T default_value, CONST_STRING_T file);
private:
   static char * _Buffer;
};

extern STRING_T System();
extern STRING_T Compiler();
extern STRING_T Configuration();
extern STRING_T ConfigFile();
extern void SetSymbol(CONST_STRING_T sym_name, CONST_STRING_T sym_value);
extern STRING_T GetSymbol(CONST_STRING_T sym_name);

#endif

