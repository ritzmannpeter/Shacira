
#include "abuild.h"
#include "cprojectfile.h"
#include "cproject.h"
#include "cexpression.h"
#include "cexptokenizer.h"
#include "cexpparser.h"
#include "cpp.h"

static char _Buffer[0x4000];

cProjectFile::cProjectFile(cProject * project, const char * file, int prio)
{
   _SymbolTable = NULL;
   _IsMainTarget = false;
   _Project = project;
   _Path = new cPath(file);
   AddVFS(_Path->AbsolutePath().c_str());
   _Priority = prio;
   if (!_Path->Exists()) {
      Printf(M_WARNING, "not found: %s\n", _Path->AbsolutePath().c_str());
   }
   _GeneratedFrom = NULL;
   _Tool = _Project->Config()->Tool(_Path->Path().c_str(),
                                    _Path->AbsolutePath().c_str(),
                                    _Path->BaseName().c_str(),
                                    _Path->Name().c_str(),
                                    _Path->Extension().c_str());
   _Type = _Tool->FileType();
   if (_Type != UNKNOWN_FILE) {
      AddTargets();
      _Project->AddProjectFile(this);
   }
}

cProjectFile::cProjectFile(cProject * project, const char * file, int prio, int type, cProjectFile * generated_from)
{
   _SymbolTable = NULL;
   _IsMainTarget = false;
   _Project = project;
   _Path = new cPath(file);
   AddVFS(_Path->AbsolutePath().c_str());
   _Priority = prio;
   if (type == DETECT || type == UNKNOWN_FILE) {
      _Tool = _Project->Config()->Tool(_Path->Path().c_str(),
                                       _Path->AbsolutePath().c_str(),
                                       _Path->BaseName().c_str(),
                                       _Path->Name().c_str(),
                                       _Path->Extension().c_str());
      _Type = _Tool->FileType();
   } else {
      _Type  = type;
      _Tool = _Project->Config()->Tool(_Type);
   }
   _GeneratedFrom = generated_from;
   AddTargets();
   _Project->AddProjectFile(this);
}

cProjectFile::~cProjectFile()
{
}

cNode * cProjectFile::Node(cGraph * graph)
{
   cNode * node = graph->Node(_Path->Name().c_str());
   node->AddProperty("absolute_path", _Path->AbsolutePath().c_str());
///   node->AddProperty("command_line", _Tool->CommandLine(_Type));
   return node;
}
   
cPath * cProjectFile::Path()
{
   return _Path;
}

void cProjectFile::AddIncludeDependencies()
{
   if (_BuildFlags & GENERATE_DEP_FILES) {
      if (_Type == CORBA_IDL_FILE ||
          _Type == COM_IDL_FILE ||
          _Type == C_FILE ||
          _Type == CPP_FILE ||
          _Type == H_FILE ||
          _Type == PP_FILE) {
         AddIncludeDependencies(_Path->Name().c_str(), _Path->AbsolutePath().c_str());
      }
   }
}

int cProjectFile::FileTypeExtension(const char * extension)
{
   if (stricmp(extension, "idl") == 0) {
      return CORBA_IDL_FILE;
   } else if (stricmp(extension, "midl") == 0) {
      return COM_IDL_FILE;
   } else if (stricmp(extension, "c") == 0) {
      return C_FILE;
   } else if (stricmp(extension, "cpp") == 0 ||
              stricmp(extension, "cc") == 0 ||
              stricmp(extension, "cxx") == 0) {
      return CPP_FILE;
   } else if (stricmp(extension, "h") == 0) {
      return H_FILE;
   } else if (stricmp(extension, "hh") == 0) {
      return H_FILE;
   } else if (stricmp(extension, "hpp") == 0) {
      return H_FILE;
   } else if (stricmp(extension, "sty") == 0) {
      return STYX_FILE;
   } else if (stricmp(extension, "ui") == 0) {
      return UI_FILE;
   } else if (stricmp(extension, "pp") == 0) {
      return PP_FILE;
   } else if (stricmp(extension, "mdl") == 0 ||
              stricmp(extension, "dec") == 0) {
      return MDLC_FILE;
   } else if (stricmp(extension, "o") == 0 ||
              stricmp(extension, "obj") == 0) {
      return OBJECT_FILE;
   } else if (stricmp(extension, "lib") == 0) {
      return STATIC_LIBRARY_FILE;
   } else if (stricmp(extension, "dll") == 0 ||
              stricmp(extension, "so") == 0) {
      return SHARED_LIBRARY_FILE;
   } else if (stricmp(extension, "exe") == 0) {
      return EXECUTABLE_FILE;
   } else {
      return UNKNOWN_FILE;
   }
}
int cProjectFile::FileTypeSpec(const char * spec)
{
   if (stricmp(spec, "corba_idl") == 0) {
      return CORBA_IDL_FILE;
   } else if (stricmp(spec, "com_idl") == 0) {
      return COM_IDL_FILE;
   } else if (stricmp(spec, "c") == 0) {
      return C_FILE;
   } else if (stricmp(spec, "cpp") == 0) {
      return CPP_FILE;
   } else if (stricmp(spec, "h") == 0) {
      return H_FILE;
   } else if (stricmp(spec, "styx") == 0) {
      return STYX_FILE;
   } else if (stricmp(spec, "moc") == 0) {
      return MOC_FILE;
   } else if (stricmp(spec, "ui") == 0) {
      return UI_FILE;
   } else if (stricmp(spec, "pp") == 0) {
      return PP_FILE;
   } else if (stricmp(spec, "mdlc") == 0) {
      return MDLC_FILE;
   } else if (stricmp(spec, "object") == 0) {
      return OBJECT_FILE;
   } else if (stricmp(spec, "static_library") == 0) {
      return STATIC_LIBRARY_FILE;
   } else if (stricmp(spec, "shared_library") == 0) {
      return SHARED_LIBRARY_FILE;
   } else if (stricmp(spec, "executable") == 0) {
      return EXECUTABLE_FILE;
   } else {
      return UNKNOWN_FILE;
   }
}


void cProjectFile::AddTargets()
{
   cProjectFile * project_file = NULL;
   char target_file[0x200] = {0};
   STRING_T intermediate_dir = _Project->IntermediateDirectory();
   STRING_T base_name = _Path->BaseName();
   int index = 0;
   while (true) {
      int type = UNKNOWN_FILE;
      STRING_T target;
      if (_Tool->Target(index, base_name.c_str(), target, type)) {
         sprintf(target_file, "%s/%s", _Project->IntermediateDirectory(), target.c_str());
         int prio = type == OBJECT_FILE ? 1 : 0;
         project_file = new cProjectFile(_Project, target_file, prio, type, this);
         AddTargetFile(project_file);
      } else {
         break;
      }
      index++;
   }
   return;
}

cSymbolTable * cProjectFile::SymbolTable()
{
   if (_SymbolTable == NULL) {
      _SymbolTable = _Project->CSymbols();
   }
   return _SymbolTable;
}

void cProjectFile::AddTargetFile(cProjectFile * target_file)
{
   _TargetFiles.push_back(target_file);
}

void cProjectFile::TargetFiles(PROJECT_FILE_LIST_T & target_files)
{
   PROJECT_FILE_LIST_T::const_iterator i = _TargetFiles.begin();
   while (i != _TargetFiles.end()) {
      cProjectFile * project_file = (*i);
      target_files.push_back(project_file);
      i++;
   }
}

static char _WhiteSpace[0x1000] = {0};
void cProjectFile::AddIncludeDependencies(const char * key, const char * file, int level)
{
   cStateStack state_stack;
   if (level == 0) {
      SymbolTable()->Clear();
      _Project->Config()->SetDefinitions(SymbolTable());
      _Project->SetDefinitions(SymbolTable());
   } else if (level > INCLUDE_SEARCH_LEVEL) {
      return;
   }
   STRING_T def;
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   STRING_T file_name = cDirectoryUtils::RelPath(current_dir.c_str(), cDirectoryUtils::FullPath(file).c_str());
   cReliance * reliance = _Project->Reliance(key);   
   STRING_LIST_T include_directories;
   _Project->IncludeDirectories(include_directories, cDirectoryUtils::CurrentDir().c_str());
   FILE * stream = fopen(file, "r");
   if (stream != NULL) {
      int line_no = 0;
      int def_level = 0;
      bool accept = true;
      char * line = fgets(_Buffer, sizeof(_Buffer), stream);
      line_no++;
      POSITION(file,line_no,0)
      while (line != NULL) {
         char * line_ptr = line;
         if (line_ptr[0] == '#') {
            accept = CheckCondition(def_level, file, line_no, line_ptr, accept,
                                    SymbolTable(), &state_stack);
            if (accept) {
               if (strnicmp(line, "#include", 8) == 0) {
                  char include_file[0x200] = {0};
                  int params = 0;
                  if ((params = sscanf(line, "#include%[^\"]\"%[^\"]", _WhiteSpace, include_file)) == 2) {
                     STRING_T header_file = HeaderFile(include_directories, include_file,
                                                       cDirectoryUtils::DirName(file).c_str());
                     if (header_file.size() > 0) {
                        _Project->AddReliance(key, header_file.c_str());
                        AddIncludeDependencies(key, header_file.c_str(), level + 1);
                     }
                  } else if ((params = sscanf(line, "#include%[^<]<%[^>]", _WhiteSpace, include_file)) == 2) {
                     STRING_T header_file = HeaderFile(include_directories, include_file,
                                                       cDirectoryUtils::DirName(file).c_str());
                     if (header_file.size() > 0) {
                        _Project->AddReliance(key, header_file.c_str());
                        AddIncludeDependencies(key, header_file.c_str(), level + 1);
                     }
                  }
               }
            } else {
            }
         }
         line = fgets(_Buffer, sizeof(_Buffer), stream);
         line_no++;
         POSITION(file,line_no,0)
      }
      fclose(stream);
   }
}

STRING_T cProjectFile::HeaderFile(STRING_LIST_T & include_directories, const char * file_spec, const char * base_dir)
{
   STRING_T file_name = cDirectoryUtils::FileName(file_spec);
//Printf(M_INFO, "check for %s %s\n", file_name.c_str(), file_spec);
   STRING_T header_file;
   STRING_T file;
   STRING_LIST_T::const_iterator i = include_directories.begin();
   while (i != include_directories.end()) {
//Printf(M_INFO, "check in %s\n", (*i).c_str());
      STRING_T directory = (*i);
      file = cDirectoryUtils::AppendPath(directory.c_str(), file_spec);
      file = cDirectoryUtils::FullPath(file.c_str());
      if (FindVFS(file.c_str())) {
///Printf(M_INFO, "%s found in (VFS)\n", file_spec);
         return file;
      }
      if (cDirectoryUtils::FileExists(file.c_str())) {
///Printf(M_INFO, "found %s in %s\n", file_spec, directory.c_str());
         AddVFS(file.c_str());
         return file;
      }
      i++;
   }
   file = cDirectoryUtils::AppendPath(base_dir, file_spec);
   file = cDirectoryUtils::FullPath(file.c_str());
//Printf(M_INFO, "check in %s\n", base_dir);
   if (FindVFS(file.c_str())) {
///Printf(M_INFO, "%s found in (VFS)\n", file_spec);
      return file;
   }
   if (cDirectoryUtils::FileExists(file.c_str())) {
///Printf(M_INFO, "found %s in current directory\n", file.c_str());
      AddVFS(file.c_str());
      return file;
   }
   Printf(M_WARNING, "include file %s not found\n", file_spec);
   return "";
}

