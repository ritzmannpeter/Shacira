
#ifndef _fsysutils_h_
#define _fsysutils_h_

#include "platform.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN32__
#include <windows.h>
#endif

class cSString {
public:
   cSString();
   cSString(cSString & right);
   cSString(const char * string);
   cSString(const char * string, unsigned long len);
   virtual ~cSString();
   const char * c_str();
   unsigned long size();
   cSString operator +(cSString & right);
   cSString operator +(const char * right);
   cSString operator +=(cSString & right);
   cSString operator +=(const char * right);
   operator =(cSString & right);
   operator =(const char * right);
   char operator [](unsigned long index);
   void clear();
private:
   int _RefCount;
   char * _String;
};

typedef cSString STRING_T;
typedef bool BOOL_T;
typedef char CHAR_T;
typedef int INT_T;
typedef unsigned int UINT_T;
typedef unsigned long ULONG_T;
typedef const char * CONST_STRING_T;

#define SLASH           '/'
#define BACK_SLASH      '\\'
#define PATH_DELIMITERS "/\\"

BOOL_T CreateDir(CONST_STRING_T directory);
BOOL_T RemoveFile(CONST_STRING_T file);
BOOL_T RenameFile(CONST_STRING_T src_path, CONST_STRING_T dst_path);
BOOL_T DirExists(CONST_STRING_T path);
BOOL_T FileExists(CONST_STRING_T path);
ULONG_T FileSize(CONST_STRING_T path);
STRING_T FullPath(CONST_STRING_T path);
void LeftSplit(CONST_STRING_T path, STRING_T &head, STRING_T &tail);
void RightSplit(CONST_STRING_T path, STRING_T &head, STRING_T &tail);
STRING_T AppendPath(CONST_STRING_T head, CONST_STRING_T tail, CONST_STRING_T delimiter = "/");
STRING_T FileName(CONST_STRING_T path);
STRING_T BaseFileName(CONST_STRING_T path);
STRING_T DirName(CONST_STRING_T path);
STRING_T DriveName(CONST_STRING_T path);
STRING_T FileExtension(CONST_STRING_T path);
STRING_T CurrentDir();
STRING_T CurrentDrive();
BOOL_T IsRelativePath(CONST_STRING_T path);
BOOL_T IsAbsolutePath(CONST_STRING_T path);
BOOL_T IsUNCPath(CONST_STRING_T path);
BOOL_T IsPathDelimiter(CHAR_T c);
BOOL_T IsDrive(CONST_STRING_T path);
BOOL_T IsUNCRoot(CONST_STRING_T path);
BOOL_T IsDriveChar(CHAR_T c);
#endif
