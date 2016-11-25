
#include "cAutoProject.h"
#include "cPath.h"
#include "cSource.h"
#include "Graph/cGraph.h"

cReliances * cAutoProject::_Reliances = NULL;
cGraph * cAutoProject::_Graph = NULL;

cAutoProject::cAutoProject(const char * build_file)
{
   if (_Reliances == NULL) {
      _Reliances = new cReliances;
   }
   if (_Graph == NULL) {
      _Graph = new cGraph;
   }
   _ConfigurationSkipped = false;
   _NoGeneration = false;
   _SourceFiles = new cPathGroup;
   _IncludePaths = new cPathGroup;
   _LibraryPaths = new cPathGroup;
   _BuildFile = new cPath(build_file);
   _TargetFile = NULL;
   _ProjectPath = cDirectoryUtils::DirName(_BuildFile->AbsolutePath().c_str());
}

cAutoProject::~cAutoProject()
{
   if (_SourceFiles != NULL) {
      delete _SourceFiles;
   }
   if (_IncludePaths != NULL) {
      delete _IncludePaths;
   }
   if (_LibraryPaths != NULL) {
      delete _LibraryPaths;
   }
   if (_BuildFile != NULL) {
      delete _BuildFile;
   }
   if (_TargetFile != NULL) {
      delete _TargetFile;
   }
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      cAutoProject * auto_project = (*ap).second;
      delete auto_project;
      ap++;
   }
}

STRING_T cAutoProject::ProjectPath()
{
   return _ProjectPath;
}

STRING_T cAutoProject::ProjectFile()
{
   STRING_T project_file = _BuildFile->AbsolutePath();
   return project_file;
}

bool cAutoProject::Parse()
{
   bool success = false;
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   cDirectoryUtils::SetCurrentDir(_ProjectPath.c_str());
   success = ParseSpec(_BuildFile->AbsolutePath().c_str());
   if (success) {
      success = cDirectoryUtils::SetCurrentDir(current_dir.c_str());
   }
   if (success) {
      AddIncludeDependencies();
   }
   return success;
}

bool cAutoProject::Build()
{
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      (*ap).second->Build();
      ap++;
   }
   bool success = false;
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   success = cDirectoryUtils::SetCurrentDir(_ProjectPath.c_str());
   if (success) {
      success = cDirectoryUtils::SetCurrentDir(current_dir.c_str());
      if (success) {
         PrintDependencies();
      }
   }
   return success;
}

void cAutoProject::Show(const char * file)
{
   if (_ConfigurationSkipped) {
      return;
   }
   cNode * node = new cNode(_TargetName.c_str());
   node->AddProperty("path", _ProjectPath.c_str());
   node->AddProperty("target_type", _TargetType.c_str());
   _Graph->AddNode(node);
   FILE * stream = fopen(file, "w");
   if (stream != NULL) {
      DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
      while (ap != _Dependencies.end()) {
         cAutoProject * depends_on = (*ap).second;
         depends_on->Show(stream, node);
         ap++;
      }
      _Graph->Print(stream);
      fclose(stream);
   }
}

void cAutoProject::Show(FILE * stream, cNode * dependent)
{
   if (_ConfigurationSkipped) {
      return;
   }
   cNode * node = new cNode(_TargetName.c_str());
   node->AddProperty("path", _ProjectPath.c_str());
   node->AddProperty("target_type", _TargetType.c_str());
   _Graph->AddNode(node);
   cAngle * angle = new cAngle("depends_on", dependent, node);
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      cAutoProject * depends_on = (*ap).second;
      depends_on->Show(stream, node);
      ap++;
   }
}

void cAutoProject::IncludeDirectories(STRING_LIST_T & directories, const char * base)
{
   PATH_LIST_T paths;
   _IncludePaths->List(paths);
   PATH_LIST_T::const_iterator i = paths.begin();
   while (i != paths.end()) {
      STRING_T path;
      if (base == NULL) {
         path = (*i)->AbsolutePath();
      } else {
         path = (*i)->RelativePath(base);
      }
      directories.push_back(path.c_str());
      i++;
   }
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      STRING_LIST_T dependent_includes;
      (*ap).second->IncludeDirectories(dependent_includes, base);
      STRING_LIST_T::const_iterator ip = dependent_includes.begin();
      while (ip != dependent_includes.end()) {
         directories.push_back((*ip).c_str());
         ip++;
      }
      ap++;
   }
}
   
void cAutoProject::LibraryDirectories(STRING_LIST_T & directories, const char * base)
{
   PATH_LIST_T paths;
   _LibraryPaths->List(paths);
   PATH_LIST_T::const_iterator i = paths.begin();
   while (i != paths.end()) {
      STRING_T path;
      if (base == NULL) {
         path = (*i)->AbsolutePath();
      } else {
         path = (*i)->RelativePath(base);
      }
      directories.push_back(path.c_str());
      i++;
   }
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      STRING_LIST_T dependent_libpaths;
      (*ap).second->LibraryDirectories(dependent_libpaths, base);
      STRING_LIST_T::const_iterator ip = dependent_libpaths.begin();
      while (ip != dependent_libpaths.end()) {
         directories.push_back((*ip).c_str());
         ip++;
      }
      ap++;
   }
}

void cAutoProject::Libraries(STRING_LIST_T & libraries, const char * base)
{
   STRING_LIST_T::const_iterator i = _Libraries.begin();
   while (i != _Libraries.end()) {
      libraries.push_back((*i).c_str());
      i++;
   }
   DEPENDENCY_MAP_T::const_iterator ap = _Dependencies.begin();
   while (ap != _Dependencies.end()) {
      STRING_LIST_T dependent_libs;
      (*ap).second->Libraries(dependent_libs, base);
      STRING_LIST_T::const_iterator ip = dependent_libs.begin();
      while (ip != dependent_libs.end()) {
         libraries.push_back((*ip).c_str());
         ip++;
      }
      if (strcmp((*ap).second->TargetType().c_str(), "static_library") == 0) {
         libraries.push_back((*ap).second->TargetFile(base));
      }
      ap++;
   }
}

void cAutoProject::GeneratedFiles(STRING_LIST_T & files, const char * base)
{
}

void cAutoProject::ObjectFiles(STRING_LIST_T & files, const char * base)
{
}

STRING_T cAutoProject::TargetFile(const char * base)
{
   if (_TargetFile == NULL) {
      return "?";
   } else {
      return _TargetFile->RelativePath(base);
   }
}

void cAutoProject::AddSource(cSource * source)
{
   _Sources.push_back(source);
}

void cAutoProject::Sources(SOURCE_LIST_T & sources)
{
   sources = _Sources;
}

cReliance * cAutoProject::Reliance(const char * name)
{
   return _Reliances->Reliance(name);
}

void cAutoProject::AddReliance(const char * name, const char * path)
{
   cReliance * reliance = _Reliances->Reliance(name);
   if (reliance == NULL) {
      reliance = new cReliance(name);
      _Reliances->Add(name, reliance);
   }
   cPath * _path = new cPath(path);
   reliance->Add(_path);
}

bool cAutoProject::ParseSpec(const char * spec_file)
{
   bool success = true;
   FILE * stream = fopen(spec_file, "r");
   if (stream != NULL) {
      int line_no = 1;
      memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
      char * line = fgets(_ParseBuffer, sizeof(_ParseBuffer), stream);
      while (line != NULL) {
         char * line_ptr = line;
         while (*line_ptr != '.' &&
                *line_ptr != '\0' &&
                *line_ptr != ';') {
            line_ptr++;
         }
         if (*line_ptr == '.') {
            int params = 0;
            char directive[0x100] = {0};
            char text[0x200] = {0};
            if ((params = sscanf(line_ptr+1, "%[^ ] %[^\n]", directive, text)) == 2) {
               if (!ParseDirective(directive, text, spec_file, line_no)) {
                  success = false;
               }
            }
         }
         memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
         line = fgets(_ParseBuffer, sizeof(_ParseBuffer), stream);
      }
      fclose(stream);
      return success;
   } else {
      ParseError("failed to open build specification %s\n", spec_file);
      return false;
   }
}

bool cAutoProject::ParseDirective(const char * directive, const char * text, const char * file, int line_no)
{
   if (_ConfigurationSkipped) {
      return true;
   }
   if (_stricmp(directive, "name") == 0) {
      _TargetName = text;
   } else if (_stricmp(directive, "target") == 0) {
      _TargetType = text;
      if (_TargetType != "resources") {
         AddIncludePath(IntermediateDirectory());
      }
      if (_TargetType == "resources") {
         _NoGeneration = true;;
      } else if (_TargetType == "static_library") {
         STRING_T target_file;
         if (System() == "win32") {
            target_file = cDirectoryUtils::AppendPath(IntermediateDirectory(), _TargetName.c_str());
            target_file += ".lib";
         } else if (System() == "linux") {
            target_file = cDirectoryUtils::AppendPath(IntermediateDirectory(), "lib");
            target_file += _TargetName.c_str();
            target_file += ".a";
         }
         _TargetFile = new cPath(target_file.c_str());
      } else if (_TargetType == "executable") {
         STRING_T target_file;
         if (System() == "win32") {
            target_file = cDirectoryUtils::AppendPath(IntermediateDirectory(), _TargetName.c_str());
            target_file += ".exe";
         } else if (System() == "linux") {
            target_file = cDirectoryUtils::AppendPath(IntermediateDirectory(), _TargetName.c_str());
         }
         _TargetFile = new cPath(target_file.c_str());
      }
   } else if (_stricmp(directive, "include") == 0) {
      AddIncludePath(text);
   } else if (_stricmp(directive, "path") == 0) {
      AddSources(text, WALK_RECURSIVE);
   } else if (_stricmp(directive, "path_nr") == 0) {
      AddSources(text);
   } else if (_stricmp(directive, "lib_path") == 0) {
      AddLibraryPath(text);
   } else if (_stricmp(directive, "lib") == 0) {
      AddLibrary(text);
   } else if (_stricmp(directive, "depends_on") == 0) {
      cAutoProject * auto_project = new cAutoProject(text);
      auto_project->Parse();
      AddDependency(auto_project);
   } else if (_stricmp(directive, "src_file") == 0) {
      cSource * source = new cSource(this, text);
   } else if (_stricmp(directive, "skip_dir") == 0) {
      SkipDirectory(text);
   } else if (_stricmp(directive, "skip_file") == 0) {
      SkipFile(text);
   } else if (_stricmp(directive, "compiler") == 0) {
      if (_stricmp(text, Compiler().c_str()) != 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else if (_stricmp(directive, "system") == 0) {
      if (_stricmp(text, System().c_str()) != 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else if (_stricmp(directive, "skip_compiler") == 0) {
      if (_stricmp(text, Compiler().c_str()) == 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else if (_stricmp(directive, "skip_system") == 0) {
      if (_stricmp(text, System().c_str()) == 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else {
#ifdef lassma
      ParseError("error in %s/%s (%d): unrecognized directive %s %s\n",
                 cFileSystemUtils::CurrentDir().c_str(), _ConfigFile.c_str(), line_no,
                 directive, text);
      return false;
#endif
   }
   return true;
}

void cAutoProject::AddIncludePath(const char * path)
{
   cPath * _path = new cPath(path);
   _IncludePaths->Add(_path);
}

void cAutoProject::AddDependency(cAutoProject * project)
{
   STRING_T project_file = project->ProjectFile();
   _Dependencies[project_file.c_str()] = project;
}

void cAutoProject::AddLibraryPath(const char * path)
{
   cPath * _path = new cPath(path);
   _LibraryPaths->Add(_path);
}

void cAutoProject::AddLibrary(const char * library)
{
   STRING_T _library = cPath::ResolveSymbols(library);
   char library_file[0x100] = {0};
   if (System() == "win32") {
      sprintf(library_file, "%s.lib", _library.c_str());
   } else if (System() == "linux") {
      sprintf(library_file, "lib%s.a", _library.c_str());
   }
   _Libraries.push_back(library_file);
}

void cAutoProject::AddSources(const char * path, unsigned long flags)
{
   STRING_LIST_T source_files;
   cDirectoryUtils::FileList(source_files, path, flags);
   STRING_LIST_T::const_iterator i = source_files.begin();
   while (i != source_files.end()) {
      STRING_T file = (*i);
      if (!Skipped(file.c_str())) {
         cSource * source = new cSource(this, file.c_str());
      }
      i++;
   }
}

bool cAutoProject::Skipped(const char * path)
{
   long pos = 0;
   long path_len = strlen(path);
   STRING_LIST_T::const_iterator i = _SkippedDirectories.begin();
   while (i != _SkippedDirectories.end()) {
      STRING_T dir_name = (*i);
      long dir_len = dir_name.size();
      for (pos=0; pos<path_len; pos++) {
         if (strnicmp(dir_name.c_str(), &(path[pos]), dir_len) == 0) {
            if (pos > 0) {
               if (path[pos-1] == '/' &&
                   path[pos+dir_len] == '/') {
//                  Printf("skipped %s (directory = %s)\n", path, dir_name.c_str());
                  return true;
               }
            } else {
               if (path[pos+dir_len] == '/') {
//                  Printf("skipped %s (directory = %s)\n", path, dir_name.c_str());
                  return true;
               }
            }
         }
      }
      i++;
   }
   STRING_T file_name = cDirectoryUtils::FileName(path);
   i = _SkippedFiles.begin();
   while (i != _SkippedFiles.end()) {
      if (_stricmp(file_name.c_str(), (*i).c_str()) == 0) {
//         Printf("skipped %s (file = %s)\n", path, file_name.c_str());
         return true;
      }
      i++;
   }
//   Printf("source: %s (%s)\n", path, _TargetName.c_str());
   return false;
}

void cAutoProject::SkipDirectory(const char * directory)
{
   _SkippedDirectories.push_back(directory);
}

void cAutoProject::SkipFile(const char * file)
{
   _SkippedFiles.push_back(file);
}

void cAutoProject::AddIncludeDependencies()
{
   SOURCE_LIST_T::const_iterator i = _Sources.begin();
   while (i != _Sources.end()) {
      cSource * source = (*i);
      source->AddIncludeDependencies();
      i++;
   }
}

void cAutoProject::PrintDependencies()
{
   SOURCE_LIST_T::const_iterator i = _Sources.begin();
   while (i != _Sources.end()) {
      cSource * source = (*i);
      cPath * path = source->Path();
      STRING_T file_name = cDirectoryUtils::FileName(path->AbsolutePath().c_str());
      cReliance * reliance = Reliance(file_name.c_str());
      if (reliance != NULL) {
         Printf("%s: \\\n", path->RelativePath(cDirectoryUtils::CurrentDir().c_str()).c_str());
         STRING_LIST_T dependent_files;
         reliance->DependentFiles(dependent_files, cDirectoryUtils::CurrentDir().c_str());
         STRING_LIST_T::const_iterator i = dependent_files.begin();
         while (i != dependent_files.end()) {
            Printf("\t%s \\\n", (*i).c_str());
            i++;
         }
         Printf("\n");
      }
      i++;
   }
}



