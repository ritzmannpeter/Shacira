
#ifndef _ctoolfactory_h
#define _ctoolfactory_h 	1

#include "global_defs.h"
#include "ctool.h"

class cToolFactory {
public:
   cToolFactory();
   virtual ~cToolFactory();
   virtual cTool * Tool(const char * file,
                        const char * absolute_path,
                        const char * base_name,
                        const char * file_name,
                        const char * extension);
private:
   bool CheckForMOCFile(const char * file);
   cTool * _Tools[0x100];
};

#endif

