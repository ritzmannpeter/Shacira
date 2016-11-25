
#ifndef cProjectFile_h
#define cProjectFile_h

#include "cpath.h"
#include "file_types.h"
#include "csymboltable.h"
#include "cstatestack.h"
#include "cgraphnode.h"

class cProjectFile;
class cProject;
class cTool;

typedef std::list<cProjectFile*> PROJECT_FILE_LIST_T;
typedef std::map<STRING_T,cProjectFile*> PROJECT_FILE_MAP_T;

class cProjectFile : public cGraphNode
{
public:
   cProjectFile(cProject * project, const char * file, int prio = 0);
   cProjectFile(cProject * project, const char * file, int prio, int type, cProjectFile * from);
   virtual ~cProjectFile();
   virtual cNode * Node(cGraph * graph);
   cPath * Path();
   inline int Type()
   {
      return _Type;
   };
   inline int Priority()
   {
      return _Priority;
   };
   inline cProjectFile * GeneratedFrom()
   {
      return _GeneratedFrom;
   };
   inline cTool * Tool()
   {
      return _Tool;
   };
   inline bool IsMainTarget()
   {
      return _IsMainTarget;
   };
   inline void SetIsMainTarget(bool state)
   {
      _IsMainTarget = state;
   };
   inline cSymbolTable * SymbolTable();
   void AddTargetFile(cProjectFile * target_file);
   void TargetFiles(PROJECT_FILE_LIST_T & target_files);
   void AddIncludeDependencies();
   static int FileTypeExtension(const char * extension);
   static int FileTypeName(const char * file_name);
   static int FileTypePath(const char * path);
   static int FileTypeSpec(const char * spec);
private:
   void DetectType();
   void CheckForMOCFile();
   void AddIncludeDependencies(const char * key, const char * file, int level = 0);
   STRING_T HeaderFile(STRING_LIST_T & include_directories, const char * file_spec, const char * base_dir);
   void AddTargets();
private:
   cProject * _Project;
   cPath * _Path;
   int _Type;
   cProjectFile * _GeneratedFrom;
   cTool * _Tool;
   PROJECT_FILE_LIST_T _TargetFiles;
   bool _IsMainTarget;
   int _Priority;
   cSymbolTable * _SymbolTable;
};

#endif
