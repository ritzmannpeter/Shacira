
#include "ctoolfactory.h"

cToolFactory::cToolFactory()
{
   memset(_Tools, 0, sizeof(_Tools));
}

cToolFactory::~cToolFactory()
{
}

cTool * cToolFactory::Tool(const char * file,
                           const char * absolute_path,
                           const char * base_name,
                           const char * file_name,
                           const char * extension)
{
   int type = UNKNOWN_FILE;
   if (stricmp(extension, "idl") == 0) {
      type = CORBA_IDL_FILE;
   } else if (stricmp(extension, "midl") == 0) {
      type = COM_IDL_FILE;
   } else if (stricmp(extension, "c") == 0) {
      type = C_FILE;
   } else if (stricmp(extension, "cpp") == 0 ||
              stricmp(extension, "cc") == 0 ||
              stricmp(extension, "cxx") == 0) {
      type = CPP_FILE;
   } else if (stricmp(extension, "h") == 0) {
      if (CheckForMOCFile(file)) {
         type = MOC_FILE;
      } else {
         type = H_FILE;
      }
   } else if (stricmp(extension, "hh") == 0) {
      if (CheckForMOCFile(file)) {
         type = MOC_FILE;
      } else {
         type = H_FILE;
      }
   } else if (stricmp(extension, "hpp") == 0) {
      if (CheckForMOCFile(file)) {
         type = MOC_FILE;
      } else {
         type = H_FILE;
      }
   } else if (stricmp(extension, "sty") == 0) {
      type = STYX_FILE;
   } else if (stricmp(extension, "ui") == 0) {
      type = UI_FILE;
   } else if (stricmp(extension, "pp") == 0) {
      type = PP_FILE;
   } else if (stricmp(extension, "mdl") == 0 ||
              stricmp(extension, "dec") == 0) {
      type = MDLC_FILE;
   } else if (stricmp(extension, "o") == 0 ||
              stricmp(extension, "obj") == 0) {
      type = OBJECT_FILE;
   } else if (stricmp(extension, "lib") == 0) {
      type = STATIC_LIBRARY_FILE;
   } else if (stricmp(extension, "dll") == 0 ||
              stricmp(extension, "so") == 0) {
      type = SHARED_LIBRARY_FILE;
   } else if (stricmp(extension, "exe") == 0) {
      type = EXECUTABLE_FILE;
   } else {
      type = UNKNOWN_FILE;
   }
   cTool * tool = _Tools[type];
      if (tool == NULL) {
      switch (type) {
      case DETECT:
         break;
      case CORBA_IDL_FILE:
         tool = new cCORBAIdlCompiler(type);
         break;
      case COM_IDL_FILE:
         break;
      case C_FILE:
      case CPP_FILE:
         tool = new cCPPCompiler(type);
         break;
      case H_FILE:
         break;
      case STYX_FILE:
         tool = new cStyxCompiler(type);
         break;
      case UI_FILE:
         tool = new cUserInterfaceCompiler(type);
         break;
      case MOC_FILE:
         tool = new cMetaObjectCompiler(type);
         break;
      case PP_FILE:
         tool = new cPreprocessor(type);
         break;
      case MDLC_FILE:
         tool = new cModelCompiler(type);
         break;
      case STATIC_LIBRARY_FILE:
         tool = new cLibrarian(type);
         break;
      case EXECUTABLE_FILE:
         tool = new cLinker(type);
         break;
      case SHARED_LIBRARY_FILE:
         tool = new cSharedLinker(type);
         break;
      }
      if (tool == NULL) {
         tool = new cTool(type);
      }
   }
   return tool;
}

static char _Buffer[0x8000] = {0};

bool cToolFactory::CheckForMOCFile(const char * file)
{
   FILE * stream = fopen(file, "r");
   if (stream != NULL) {
      int len = 0;
      char * line = fgets(_Buffer, sizeof(_Buffer), stream);
      while (line != NULL) {
         len = strlen(line);
         char * line_ptr = line;
         for (int i=0; i<len-1; i++) {
            if (strncmp(line_ptr, "Q_OBJECT", 8) == 0) {
               fclose(stream);
               return true;
            }
            line_ptr++;
         }
         line = fgets(_Buffer, sizeof(_Buffer), stream);
      }
      fclose(stream);
   }
   return false;
}




