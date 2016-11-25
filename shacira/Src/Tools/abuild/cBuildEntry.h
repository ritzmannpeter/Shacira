
#ifndef cBuildEntry_h
#define cBuildEntry_h

#include "cConfigUtils.h"
#include "cPath.h"

class cAutoConfig;

#define UNKNOWN_CLASS   0
#define IDL_FILE        1
#define C_FILE          2
#define CPP_FILE        3
#define H_FILE          4
#define STYX_FILE       5
#define UI_FILE         6
#define MOC_FILE        7
#define PP_FILE         8
#define MDLC_FILE       9

class cBuildEntry;
typedef std::map<STRING_T,STRING_T> DEPENDENCY_MAP_T;
typedef std::map<STRING_T,cBuildEntry*> TARGET_MAP_T;

class cBuildEntry {
public:
   cBuildEntry(cAutoConfig * auto_config, CONST_STRING_T file, ULONG_T base_level = 0, int build_class = UNKNOWN_CLASS);
   virtual ~cBuildEntry();
   STRING_T File() {return _Path->File();};
   STRING_T FileName() {return _Path->FileName();};
   STRING_T FileExtension() {return _Path->Extension();};
   int BuildClass() {return _BuildClass;};
   STRING_T BuildCommand() {return _BuildCommand;};
   STRING_T DependencySpecs();
   void AddDependencies(CONST_STRING_T file);
private:
   void Setup();
   void RefineClass();
   void AddDependency(CONST_STRING_T file_name, CONST_STRING_T file);
   void AddTargets();
   void AddTarget(CONST_STRING_T file_name, cBuildEntry * target);
   STRING_T FileName(CONST_STRING_T file);
   void SetBuildCommand();
public:
   BOOL_T _IsTarget;
   BOOL_T _Generated;
   ULONG_T _Level;
   static ULONG_T _Levels;
   cAutoConfig * _AutoConfig;
   cPath * _Path;
   int _BuildClass;
   STRING_T _BuildCommand;
   DEPENDENCY_MAP_T _Dependencies;
   TARGET_MAP_T _Targets;
};

#endif
