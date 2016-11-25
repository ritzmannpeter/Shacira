
#ifndef stl_def_h
#define stl_def_h 1

#ifdef __cplusplus
#if defined(__linux__)
#include "iostream.h"
#include "string"
#include "list"
#include "vector"
#include "map"
#elif defined (_WIN32)
#if _MSC_VER >= 1300
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using std::endl;
using std::istream;
using std::ostream;
using std::cout;
///using std::string;
///using std::wstring;
///using std::list;
///using std::map;
///using std::vector;
#else
#include "iostream.h"
#include "string"
#include "list"
#include "vector"
#include "map"
#endif
#endif // __linux__
#endif // __cplusplus

#endif // stl_def_h

