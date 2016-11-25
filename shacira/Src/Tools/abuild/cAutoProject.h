
#ifndef cAutoProject_h
#define cAutoProject_h

#include "abuild.h"
#include "cPathGroup.h"
#include "cSource.h"
#include "cDirectoryUtils.h"
#include "cReliance.h"
#include "Graph/cGraph.h"

#define PARSE_BUFFER_SIZE  0x2000
class cAutoProject;
typedef std::map<STRING_T,cAutoProject*> DEPENDENCY_MAP_T;

class cAutoProject
{
public:
   cAutoProject(const char * build_file);
   virtual ~cAutoProject();
   STRING_T ProjectPath();
   STRING_T ProjectFile();
   bool Parse();
   bool Build();
   void Show(const char * file);
   void Show(FILE * stream, cNode * dependent);
   void IncludeDirectories(STRING_LIST_T & directories, const char * base = NULL);
   void LibraryDirectories(STRING_LIST_T & directories, const char * base = NULL);
   void Libraries(STRING_LIST_T & libraries, const char * base = NULL);
   void GeneratedFiles(STRING_LIST_T & files, const char * base = NULL);
   void ObjectFiles(STRING_LIST_T & files, const char * base = NULL);
   STRING_T TargetFile(const char * base = NULL);
   inline STRING_T TargetType() { return _TargetType;};
   void AddSource(cSource * source);
   void Sources(SOURCE_LIST_T & sources);
   cReliance * Reliance(const char * name);
   void AddReliance(const char * name, const char * path);
private:
   bool ParseSpec(const char * spec_file);
   bool ParseDirective(const char * directive, const char * text, const char * file, int line_no);
   void AddIncludePath(const char * path);
   void AddDependency(cAutoProject * project);
   void AddLibraryPath(const char * path);
   void AddLibrary(const char * library);
   void AddSources(const char * path, unsigned long flags = 0);
   bool Skipped(const char * path);
   void SkipDirectory(const char * directory);
   void SkipFile(const char * file);
   void AddIncludeDependencies();
   void PrintDependencies();
private:
   char _ParseBuffer[PARSE_BUFFER_SIZE];
   STRING_T _ProjectPath;
   STRING_T _TargetName;
   STRING_T _TargetType;
   bool _ConfigurationSkipped;
   bool _NoGeneration;
   DEPENDENCY_MAP_T _Dependencies;
   cPath * _BuildFile;
   cPath * _TargetFile;
   cPathGroup * _SourceFiles;
   cPathGroup * _IncludePaths;
   cPathGroup * _LibraryPaths;
   STRING_LIST_T _Libraries;
   SOURCE_LIST_T _Sources;
   STRING_LIST_T _SkippedDirectories;
   STRING_LIST_T _SkippedFiles;
   static cReliances * _Reliances;
   static cGraph * _Graph;
};

#endif
