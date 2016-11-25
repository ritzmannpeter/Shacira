
#ifndef _global_defs_h
#define _global_defs_h 	1

#if defined(_WIN32)
#pragma warning(disable:4503) /* decorated name length exceeded, name was truncated */
#pragma warning(disable:4067) /* unexpected tokens following preprocessor directive - expected a newline */
#pragma warning(disable:4101) /* Unreferenzierte lokale Variable */
#pragma warning(disable:4786) /* identifier was truncated to '255' characters in the debug information */
#pragma warning(disable:4800) /* Variable wird auf booleschen Wert ('True' oder 'False') gesetzt (Auswirkungen auf Leistungsverhalten moeglich) */
#endif

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "iostream.h"
#include "string"
#include "list"
#include "vector"
#include "map"

#if defined(_WIN32)
#include <windows.h>
#endif
#include <stdarg.h>
#include <malloc.h>

#define __ALLOC__(size) calloc(1,size)
#define __FREE__(mem) free(mem)

typedef std::string STRING_T;
typedef std::map<STRING_T,STRING_T> STRING_MAP_T;
typedef std::vector<STRING_T> STRING_VECTOR_T;
typedef std::list<STRING_T> STRING_LIST_T;
typedef bool BOOL_T;

#define M_INFO      0x00000001
#define M_WARNING   0x00000002
#define M_ERROR     0x00000004
extern STRING_T _File;
extern int _Line;
extern int _Column;
void Printf(unsigned long msg_class, const char * fmt_str, ...);

#endif

