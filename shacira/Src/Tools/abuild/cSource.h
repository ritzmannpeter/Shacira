
#ifndef cSource_h
#define cSource_h

class cAutoProject;
#include "cPath.h"

class cSource;
typedef std::list<cSource*> SOURCE_LIST_T;
typedef std::map<STRING_T,cSource*> SOURCE_MAP_T;

typedef enum {UNKNOWN_TYPE,
              IDL_FILE,
              C_FILE,
              CPP_FILE,
              H_FILE,
              STYX_FILE,
              UI_FILE,
              MOC_FILE,
              PP_FILE,
              MDLC_FILE} SourceFileTypes;

class cSource {
public:
   cSource(cAutoProject * project, const char * file, SourceFileTypes type = UNKNOWN_TYPE, bool generated = false);
   virtual ~cSource();
   cPath * Path();
   SourceFileTypes Type();
   STRING_T TypeName();
   void AddIncludeDependencies();
private:
   void SetType();
   void CheckForMOCFile();
   void AddIncludeDependencies(const char * file);
   STRING_T HeaderFile(STRING_LIST_T & include_directories, const char * file_spec, const char * base_dir);
   void AddTargets();
private:
   cAutoProject * _Project;
   cPath * _Path;
   SourceFileTypes _Type;
};

#endif
