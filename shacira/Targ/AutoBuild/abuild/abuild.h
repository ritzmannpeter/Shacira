
#ifndef _abuild_h
#define _abuild_h 	1

#include "global_defs.h"

#define GENERATE_XML_BACKEND  0x00000001
#define GENERATE_DEP_FILES    0x00000002
#define GENERATE_ENVIRONMENT  0x00000004
extern unsigned long _BuildFlags;

#define POSITION(file,line,column) \
   _File = file; \
   _Line = line; \
   _Column = column;

void AddVFS(const char * path);
bool FindVFS(const char * path);

#endif

