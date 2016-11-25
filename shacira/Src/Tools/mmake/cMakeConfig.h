
#ifndef cMakeConfig_h
#define cMakeConfig_h

#include "globaldefs.h"

#define UNIX      0
#define WIN32     1

#define DEBUG     0
#define RELEASE   1

class cBuildEntry;
class cDependentProject;
typedef std::map<STRING_T, cBuildEntry *> BUILD_ENTRY_MAP_T;
typedef std::map<STRING_T, cDependentProject *> DEP_PRJ_MAP_T;
typedef std::map<STRING_T, STRING_T> HEADER_FILE_MAP_T;
typedef std::vector<STRING_T> STRING_VECTOR_T;

class cMakeConfig
{
public:
   cMakeConfig(const char * build_name, const char * build_config);
   virtual ~cMakeConfig();
   STRING_T ToLower(const char * text);
   void SkipDir(const char * dir_name);
   BOOL_T DirExcluded(const char * dir_name);
   void SkipFile(const char * file_name);
   BOOL_T FileExcluded(const char * file_name);
   void AddDependentProject(const char * path);
   void AddPath(const char * path);
   void AddSrcFile(const char * path);
   void AddIncludePath(const char * path);
   void AddBuildEntry(const char * name, cBuildEntry * build_entry);
   cBuildEntry * BuildEntry(const char * name);
   void SearchHeaderFiles(const char * path, const char * pattern, BOOL_T recursive = true);
   void AddHeaderFile(const char * file_name, const char * file, BOOL_T dominant = false);
   STRING_T HeaderFile(const char * file_name);
   void AddFile(const char * file_name, const char * path);
   int Find(const char * path);
   void Analyse();
   void BuildMakeFile();
   void Load();
   void SetDirective(const char * directive, const char * text, int line_no);
   STRING_T ResolvePath(const char * path);
   void PrintDependentObjFiles(FILE * stream);
   void PrintDependentObjList(FILE * stream);
   void PrintDependentProjects(FILE * stream);
public:
   BOOL_T _Verbose;
   STRING_T _ConfigFile;
   STRING_T _ConfigName;
   STRING_T _TargetName;
   STRING_T _TargetType;
   STRING_T _TargetFile;
   STRING_T _System;
   STRING_T _Compiler;
   STRING_VECTOR_T _IncludePaths;
   STRING_VECTOR_T _Paths;
   DEP_PRJ_MAP_T _DependentProjects;
   STRING_MAP_T _SrcFiles;
   STRING_MAP_T _SkippedDirs;
   STRING_MAP_T _SkippedFiles;
   HEADER_FILE_MAP_T _HeaderFiles;
   BUILD_ENTRY_MAP_T _BuildEntries;
   STRING_T _MakeFile;
   STRING_T _DepFile;
   STRING_T _ObjFile;
   STRING_T _ObjList;
   STRING_T _HdrFile;
   STRING_T _IncFile;
   STRING_T _TrgFile;
};

class cDependentProject
{
public:
   cDependentProject(const char * config_path, cMakeConfig * parent);
   virtual ~cDependentProject();
public:
   STRING_T _ConfigPath;
   cMakeConfig * _Parent;
   cMakeConfig * _Config;
};

#endif
