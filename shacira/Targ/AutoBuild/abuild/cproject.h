
#ifndef cProject_h
#define cProject_h

#include "global_defs.h"
#include "cconfigbase.h"
#include "cprojectfile.h"
#include "cbuildconfiguration.h"
#include "cpathgroup.h"
#include "cdirectoryutils.h"
#include "creliance.h"
#include "cgraph.h"

#define PARSE_BUFFER_SIZE  0x2000
#define INCLUDE_SEARCH_LEVEL  5

class cProject;

class cProjectMap
{
public:
typedef std::map<STRING_T,int> CLASS_STRING_MAP_T;
   cProjectMap() {_Ceiling = 0;};
   virtual ~cProjectMap() {};
   inline bool Exists(const char * project_name)
   {
      STRING_MAP_T::const_iterator i = _ProjectNames.find(project_name);
      if (i == _ProjectNames.end()) {
         return false;
      } else {
         return true;
      }
   };
   inline void Add(const char * project_name)
   {
      _ProjectNames[project_name] = project_name;
   };
   inline void String(const char * s, int level)
   {
      CLASS_STRING_MAP_T::const_iterator i = _Strings.find(s);
      if (i == _Strings.end()) {
         _Strings[s] = level;
      } else {
         if (level > (*i).second) {
            _Strings[s] = level;
         }
      }
      if (level > _Ceiling) {
         _Ceiling = level;
      }
   };
   inline void Strings(STRING_LIST_T & slist, bool reverse = false)
   {
      int level = 0;
      for (level=0; level<=_Ceiling; level++) {
         CLASS_STRING_MAP_T::const_iterator i = _Strings.begin();
         while (i != _Strings.end()) {
            if ((*i).second == level) {
               if (reverse) {
                  slist.push_front((*i).first);
               } else {
                  slist.push_back((*i).first);
               }
            }
            i++;
         }
      }
   };
private:
   STRING_MAP_T _ProjectNames;
   CLASS_STRING_MAP_T _Strings;
   int _Ceiling;
};


typedef enum {uses, depends, extends} ProjectRelations;
class cProjectRelation
{
public:
   cProjectRelation(cProject * project, ProjectRelations relation)
   {
      _Project = project;
      _Relation = relation;
   };
   inline cProject * Project()
   {
      return _Project;
   };
   inline ProjectRelations Relation()
   {
      return _Relation;
   };
   inline operator cProject*()
   {
      return _Project;
   };
   inline const char * RelText()
   {
      const char * rel_text = "?";
      switch (_Relation) {
      case uses: return "uses";
      case depends: return "depends";
      case extends: return "extends";
      }
      return rel_text;
   };
private:
   cProject * _Project;
   ProjectRelations _Relation;
};

typedef std::map<STRING_T,cProjectRelation*> DEPENDENCY_MAP_T;

class cProject : public cConfigBase
{
public:
   friend class cBuildConfiguration;
   cProject(cBuildConfiguration * config, const char * build_file);
   virtual ~cProject();
   virtual cNode * Node(cGraph * graph);
   inline cProjectFile * cProject::ProjectFile()
   {
      return _ProjectFile;
   };
   inline const char * cProject::IntermediateDirectory()
   {
      return _IntermediateDirectory;
   };
   inline cProjectFile * TargetFile()
   {
      return _TargetFile;
   };
   inline cBuildConfiguration * Config()
   {
      return _Config;
   }
   inline STRING_T ProjectName()
   {
      return _ProjectName;
   }
   inline bool Skipped()
   {
      return _ConfigurationSkipped;
   }
   inline bool GenerateIt()
   {
      return !_NoGeneration;
   }
   inline int Type()
   {
      if (_TargetFile == NULL) {
         return UNKNOWN_FILE;
      } else {
         return _TargetFile->Type();
      }
   }
   inline void AddCOption(const char * text)
   {
      if (_COptions.size() > 0) {
         _COptions += " ";
      }
      _COptions += text;
   };
   inline void AddCPPOption(const char * text)
   {
      if (_CPPOptions.size() > 0) {
         _CPPOptions += " ";
      }
      _CPPOptions += text;
   };
   inline void AddLibOption(const char * text)
   {
      if (_LibOptions.size() > 0) {
         _LibOptions += " ";
      }
      _LibOptions += text;
   };
   inline void AddLinkOption(const char * text)
   {
      if (_LinkOptions.size() > 0) {
         _LinkOptions += " ";
      }
      _LinkOptions += text;
   };
   inline void AddASMOption(const char * text)
   {
      if (_ASMOptions.size() > 0) {
         _ASMOptions += " ";
      }
      _ASMOptions += text;
   };
   cProject * DependentProject(const char * file, ProjectRelations relation);
   void SourceFiles(PROJECT_FILE_LIST_T & source_files);
   void TargetFiles(PROJECT_FILE_LIST_T & target_files);
   void ObjectFiles(PROJECT_FILE_LIST_T & object_files);

   bool Build();
   void IncludeDirectories(STRING_LIST_T & directories, const char * base = NULL);
   void LibraryDirectories(STRING_LIST_T & directories, const char * base = NULL);
   void Libraries(STRING_LIST_T & libraries, const char * base = NULL);

   void AddProjectFile(cProjectFile * project_file);
   STRING_T Sources(const char * base = NULL);
   STRING_T Targets(const char * base = NULL);
   STRING_T Objects(const char * base = NULL);

   STRING_T IncludeDirs(const char * base = NULL);
   STRING_T LibraryDirs(const char * base = NULL);
   STRING_T Libraries(const char * base = NULL);

   STRING_T Definitions(bool global_only = true);
   void SetDefinitions(cSymbolTable * symbol_table);

protected:
   virtual bool ParseDirective(const char * directive, const char * text, const char * file, int line_no);
private:
   void List(STRING_T & file_list, PROJECT_FILE_LIST_T & project_files, const char * base);
   void AddIncludePath(const char * path);
   void AddDependency(cProject * project, ProjectRelations relation);
   void AddLibraryPath(const char * path);
   void AddLibrary(const char * library);
   void AddSources(const char * path, unsigned long flags = 0);
   bool Skipped(const char * path);
   void SkipDirectory(const char * directory);
   void SkipFile(const char * file);
   void AddDefinition(const char * definition);
   void AddProjectDefinition(const char * definition);
   
   bool Build(cProjectMap & project_map);
   void IncludeDirectories(cProjectMap & project_map, STRING_LIST_T & directories, const char * base = NULL, int level = 0);
   void LibraryDirectories(cProjectMap & project_map, STRING_LIST_T & directories, const char * base = NULL, int level = 0);
   void Libraries(cProjectMap & project_map, STRING_LIST_T & libraries, const char * base = NULL, int level = 0);

private:
   void AddIncludeDependencies();
   void PrintMakefile(FILE * stream);
   void PrintDependencies(FILE * stream);
   inline bool HasBlanks(const char * text)
   {
      int len = strlen(text);
      int i = 0;
      for (i=0; i<len; i++) {
         if (text[i] == ' ') {
            return true;
         }
      }
      return false;
   };
   void SetDefinitions(const char * text, cSymbolTable * symbol_table);
   void SetDefinition(const char * symbol, double value, cSymbolTable * symbol_table);
private:
   cBuildConfiguration * _Config;
   char _ParseBuffer[PARSE_BUFFER_SIZE];
   cProjectFile * _ProjectFile;
   cProjectFile * _MakeFile;
   cProjectFile * _DepFile;
   cProjectFile * _TargetFile;
   PROJECT_FILE_LIST_T _ProjectFiles;

   const char * _IntermediateDirectory;
   bool _ConfigurationSkipped;
   bool _NoGeneration;

   cPathGroup * _SourceFiles;
   cPathGroup * _IncludePaths;
   cPathGroup * _LibraryPaths;

   STRING_LIST_T _Libraries;
   STRING_LIST_T _SkippedDirectories;
   STRING_LIST_T _SkippedFiles;

   STRING_LIST_T _Definitions;
   STRING_LIST_T _ProjectDefinitions;
   STRING_LIST_T _PostSteps;

   STRING_T _ProjectName;
   STRING_T _TargetType;

   DEPENDENCY_MAP_T _Dependencies;
public:
   cReliance * Reliance(const char * file);
   void AddReliance(const char * file, const char * path);
private:
   cReliances _Reliances;
   STRING_T _COptions;
   STRING_T _CPPOptions;
   STRING_T _LibOptions;
   STRING_T _LinkOptions;
   STRING_T _ASMOptions;
};

#endif
