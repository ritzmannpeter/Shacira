
#include "cconfigbase.h"
#include "abuild.h"
#include "cpp.h"

cSymbolTable * cConfigBase::_BuildSymbols = NULL;

cConfigBase::cConfigBase(const char * config_file, const char * name)
{
   if (config_file != NULL) {
      _ConfigFile = new cPath(config_file);
      _ConfigName = cDirectoryUtils::BaseFileName(config_file);
   }
   memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
   memset(_CheckBuffer, 0, sizeof(_CheckBuffer));
   _CSymbols = new cSymbolTable(name);
   if (_BuildSymbols == NULL) {
      _BuildSymbols = new cSymbolTable("build_symbols");
   }
}

cConfigBase::~cConfigBase()
{
   delete _CSymbols;
   if (_BuildSymbols != NULL) {
      delete _BuildSymbols;
      _BuildSymbols = NULL;
   }
}

bool cConfigBase::Parse()
{
   Printf(M_INFO, "parse configuration file %s ...\n", _ConfigFile->AbsolutePath().c_str());
   bool success = false;
   if (ParseSpecs(_ConfigFile->AbsolutePath().c_str())) {
      Printf(M_INFO, "configuration file %s succesfully parsed\n", _ConfigFile->AbsolutePath().c_str());
      return true;
   } else {
//      Printf(M_ERROR, "failed to parse configuration %s\n", _ConfigFile->AbsolutePath().c_str());
      return false;
   }
}

bool cConfigBase::ParseSpecs(const char * spec_file)
{
   bool success = true;
   bool accept = true;
   FILE * stream = fopen(spec_file, "r");
   if (stream != NULL) {
      cStateStack state_stack;
      int line_no = 1;
      int def_level = 0;
      memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
      char * line = fgets(_ParseBuffer, sizeof(_ParseBuffer), stream);
      POSITION(spec_file,line_no,0)
      while (success && line != NULL) {
         char * line_ptr = line;
         if (line_ptr[0] == '.') {
            int params = 0;
            char directive[0x100] = {0};
            char text[0x400] = {0};
            if ((params = sscanf(line_ptr+1, "%[^ ] %[^\n]", directive, text)) > 0) {
               if (accept) {
                  if (params == 2) {
                     int len = strlen(text);
                     if (len > 0 && text[len-1] == '\n') {
                        text[len-1] = 0;
                     }
                  } else if (params == 1) {
                     int len = strlen(directive);
                     if (len > 0 && directive[len-1] == '\n') {
                        directive[len-1] = 0;
                     }
                  }
                  if (!ParseDirective(directive, text, spec_file, line_no)) {
                     success = false;
                  }
               }
            }
         } else if (line_ptr[0] == '#') {
//            accept = CheckCondition(def_level, spec_file, line_no, line_ptr, accept,
//                                    BuildSymbols(), BuildStack());
            accept = CheckCondition(def_level, spec_file, line_no, line_ptr, accept,
                                    BuildSymbols(), &state_stack);
         } else if (line_ptr[0] == '/' &&
                    line_ptr[1] == '/') {
         }
         memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
         line = fgets(_ParseBuffer, sizeof(_ParseBuffer), stream);
         line_no++;
         POSITION(spec_file,line_no,0)
      }
      fclose(stream);
      return success;
   } else {
      Printf(M_ERROR, "failed to open build specification %s\n", spec_file);
      return false;
   }
}

bool cConfigBase::ParseDirective(const char * directive, const char * text, const char * file, int line_no)
{
   return true;
}

bool cConfigBase::CheckForMOCFile(const char * file)
{
   FILE * stream = fopen(file, "r");
   if (stream != NULL) {
      int len = 0;
      char * line = fgets(_CheckBuffer, sizeof(_CheckBuffer), stream);
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
         line = fgets(_CheckBuffer, sizeof(_CheckBuffer), stream);
      }
      fclose(stream);
   }
   return false;
}

