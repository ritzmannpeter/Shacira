
#ifndef globaldefs_h
#define globaldefs_h 	1

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

#endif

