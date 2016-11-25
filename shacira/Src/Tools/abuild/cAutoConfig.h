
#ifndef cAutoConfig_h
#define cAutoConfig_h

#include "cConfigUtils.h"
#include "cDependentConfig.h"
#include "cPath.h"

class cBuildEntry;
typedef std::map<STRING_T, cBuildEntry *> BUILD_ENTRY_MAP_T;
typedef std::map<STRING_T, cDependentConfig *> DEP_PRJ_MAP_T;

class cAutoConfig
{
public:
   cAutoConfig(const char * build_name, const char * build_config);
   virtual ~cAutoConfig();
   
   void IncludePaths(STRING_LIST_T & header_paths, BOOL_T absolute = false);
   void LibraryPaths(STRING_LIST_T & lib_paths);
   void StaticLibraries(STRING_LIST_T & libraries);
   void GeneratedHeaders(STRING_LIST_T & generated_headers);
   STRING_T A_I_PATHS();
   STRING_T A_GEN_HEADERS();
   STRING_T A_LIBS();
   STRING_T A_L_PATHS();
   STRING_T A_TARGETS();
   void TargetFiles(STRING_LIST_T & object_files);
   STRING_T A_OBJECTS();
   void ObjectFiles(STRING_LIST_T & object_files);
   void DependentObjectFiles(STRING_LIST_T & object_files);
   STRING_T A_INCLUDES();

   STRING_T ToLower(const char * text);
   void SkipDir(const char * dir_name);
   BOOL_T DirExcluded(const char * dir_name);
   void SkipFile(const char * file_name);
   BOOL_T FileExcluded(const char * file_name);
   void AddDependentProject(const char * file);
   void AddRecursivePath(const char * path);
   void AddPath(const char * path);
   void AddLibPath(const char * path);
   void AddLib(const char * lib);
   void AddIncludePath(const char * path);
   void AddBuildEntry(const char * name, cBuildEntry * build_entry);
   cBuildEntry * BuildEntry(const char * name);
   void SearchHeaderFiles(const char * path, const char * pattern, BOOL_T recursive, int level);
   int AddFiles(const char * path, BOOL_T recursive);
   void BuildMakeFile();
   
   void AddFile(const char * file_name, const char * path);
   void AddHeaderFile(CONST_STRING_T header_file, int level);
   void AddGeneratedHeaderFile(CONST_STRING_T header_file);
   void AddSourceFile(CONST_STRING_T source_file);
   cPath * HeaderFile(const char * file_name);
   STRING_T TargetDir();
private:
   void Load();
   void Configure();
   void SetDirective(const char * directive, const char * text, int line_no);
   void PrintDependentProjects(FILE * stream);
   BOOL_T Processed(CONST_STRING_T file);
   STRING_T Dependencies();
   void PrintDependencies();
   void SearchHeaderFiles();

public:
   BOOL_T _Verbose;
   BOOL_T _NoGeneration;
   BOOL_T _RevertObjects;
   BOOL_T _RevertLibPaths;
   BOOL_T _GeneratedHeaderFiles;
   BOOL_T _ConfigurationSkipped;
   STRING_T _ConfigFile;
   STRING_T _ConfigName;
   STRING_T _TargetName;
   STRING_T _TargetType;
   STRING_T _TargetDir;
   STRING_T _DependencyFile;
   STRING_T _System;
   STRING_T _Compiler;
   STRING_MAP_T _SkippedDirs;
   STRING_MAP_T _SkippedFiles;
   cPath * _TargetFile;
   PATH_MAP_T _Paths;
   PATH_MAP_T _RecursivePaths;
   DEP_PRJ_MAP_T _DependentProjects;
   PATH_MAP_T _IncludePaths;
   PATH_MAP_T _GeneratedHeaders;
   PATH_MAP_T _LibPaths;
   PATH_MAP_T _SourceFiles;
   PATH_MAP_T _HeaderFiles;
   PATH_MAP_T _TargetFiles;
   PATH_MAP_T _ObjectFiles;
   STRING_MAP_T _Libraries;
   BUILD_ENTRY_MAP_T _BuildEntries;
   cPath * _MakeFile;
private:
   static STRING_MAP_T _ProcessedFiles;
};

#endif
