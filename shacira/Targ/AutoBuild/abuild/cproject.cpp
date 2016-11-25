
#include "abuild.h"
#include "cprojectfile.h"
#include "cproject.h"
#include "cexptokenizer.h"
#include <time.h>

cProject::cProject(cBuildConfiguration * config, const char * build_file)
   : cConfigBase(build_file, build_file)
{
   _Config = config;
   _Config->Clone(this);
   _IntermediateDirectory = _Config->IntermediateDirectory();
   _ProjectFile = new cProjectFile(this, build_file);
   STRING_T file_name = _Config->ConfigName();
   file_name += ".mk";
   _MakeFile = new cProjectFile(this, file_name.c_str());
   file_name = _Config->ConfigName();
   file_name += ".dep";
   _DepFile = new cProjectFile(this, file_name.c_str());
   _ConfigurationSkipped = false;
   _NoGeneration = false;
   _SourceFiles = new cPathGroup;
   _IncludePaths = new cPathGroup;
   _LibraryPaths = new cPathGroup;
   _TargetFile = NULL;
   memset(_ParseBuffer, 0, sizeof(_ParseBuffer));
}

cProject::~cProject()
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
   if (_ProjectFile != NULL) {
      delete _ProjectFile;
   }
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      delete project;
      p++;
   }
}

cNode * cProject::Node(cGraph * graph)
{
   cNode * node = graph->Node(_ProjectName.c_str());
   node->AddProperty("name", _ProjectName.c_str());
   node->AddProperty("target_type", _TargetType.c_str());
   node->AddProperty("project_file", _ProjectFile->Path()->AbsolutePath().c_str());
   node->AddProperty("dependency_file", _DepFile->Path()->AbsolutePath().c_str());
   if (_TargetFile != NULL) {
      node->AddProperty("make_file", _MakeFile->Path()->AbsolutePath().c_str());
      node->AddProperty("target", _TargetFile->Path()->AbsolutePath().c_str());
   }
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      const char * rel_text = r->RelText();
      cNode * target = project->Node(graph);
      cAngle * angle = new cAngle(graph, "depends_on", node, target);
      angle->AddProperty("relation", rel_text);
      node->AddAngle(angle);
      p++;
   }
   PROJECT_FILE_LIST_T::const_iterator i = _ProjectFiles.begin();
   while (i != _ProjectFiles.end()) {
      cProjectFile * project_file = (*i);
      cNode * target = project_file->Node(graph);
      cAngle * angle = new cAngle(graph, "has_file", node, target);
      node->AddAngle(angle);
      i++;
   }
   return node;
}
   
cProject * cProject::DependentProject(const char * file, ProjectRelations relation)
{
   cProject * project = NULL;
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   STRING_T abs_file = cDirectoryUtils::FullPath(file);
   STRING_T project_dir = cDirectoryUtils::DirName(abs_file.c_str());
   STRING_T project_file = cDirectoryUtils::FileName(abs_file.c_str());
   if (cDirectoryUtils::SetCurrentDir(project_dir.c_str())) {
      project = new cProject(_Config, project_file.c_str());
      if (project->Parse()) {
         if (Skipped()) {
            Printf(M_INFO, "project configuration skipped\n");
         } else {
            Printf(M_INFO, "project %s succesfully parsed\n", _ProjectName.c_str());
         }
         if (!project->Skipped()) {
            AddDependency(project, relation);
         }
      } else {
///         Printf(M_ERROR, "failed to parse dependent project %s\n", abs_file.c_str());
         project = NULL;
      }
      if (!cDirectoryUtils::SetCurrentDir(current_dir.c_str())) {
         Printf(M_ERROR, "failed to reset current directory to %s\n", current_dir.c_str());
         project = NULL;
      }
   } else {
      Printf(M_ERROR, "failed to set current directory to %s\n", project_dir.c_str());
      project = NULL;
   }
   return project;
}

void cProject::SourceFiles(PROJECT_FILE_LIST_T & source_files)
{
   PROJECT_FILE_LIST_T::const_iterator i = _ProjectFiles.begin();
   while (i != _ProjectFiles.end()) {
      cProjectFile * project_file = (*i);
      if (project_file->GeneratedFrom() == NULL) {
         int type = project_file->Type();
         if (type != UNKNOWN_FILE &&
             type != DETECT) {
            source_files.push_back(project_file);
         }
      }
      i++;
   }
}

void cProject::TargetFiles(PROJECT_FILE_LIST_T & target_files)
{
   int prio = 0;
   for (prio=0; prio<3; prio++) {
      PROJECT_FILE_LIST_T::const_iterator i = _ProjectFiles.begin();
      while (i != _ProjectFiles.end()) {
         cProjectFile * project_file = (*i);
         if (project_file->GeneratedFrom() != NULL &&
             project_file->Priority() == prio) {
            target_files.push_back(project_file);
         }
         i++;
      }
   }

}

void cProject::ObjectFiles(PROJECT_FILE_LIST_T & object_files)
{
   PROJECT_FILE_LIST_T::const_iterator i = _ProjectFiles.begin();
   while (i != _ProjectFiles.end()) {
      cProjectFile * project_file = (*i);
      if (project_file->Type() == OBJECT_FILE) {
         object_files.push_back(project_file);
      }
      i++;
   }
}

bool cProject::Build()
{
   cProjectMap project_map;
   return Build(project_map);
}

void cProject::IncludeDirectories(STRING_LIST_T & directories, const char * base)
{
   cProjectMap project_map;
   IncludeDirectories(project_map, directories, base);
}
   
void cProject::LibraryDirectories(STRING_LIST_T & directories, const char * base)
{
   cProjectMap project_map;
   LibraryDirectories(project_map, directories, base);
}

void cProject::Libraries(STRING_LIST_T & libraries, const char * base)
{
   cProjectMap project_map;
   Libraries(project_map, libraries, base);
}

void cProject::AddProjectFile(cProjectFile * project_file)
{
   _ProjectFiles.push_back(project_file);
}

STRING_T cProject::Sources(const char * base)
{
   STRING_T sources;
   PROJECT_FILE_LIST_T source_files;
   SourceFiles(source_files);
   List(sources, source_files, base);
   return sources;
}

STRING_T cProject::Targets(const char * base)
{
   STRING_T targets;
   PROJECT_FILE_LIST_T target_files;
   TargetFiles(target_files);
   List(targets, target_files, base);
   return targets;
}

STRING_T cProject::Objects(const char * base)
{
   STRING_T objects;
   PROJECT_FILE_LIST_T object_files;
   ObjectFiles(object_files);
   List(objects, object_files, base);
   return objects;
}

STRING_T cProject::IncludeDirs(const char * base)
{
   bool inclusion = false;
   if (strcmp(_Config->ToolChain(), "vs6") == 0) {
      inclusion = true;
   }
   STRING_T include_dirs;
   cProjectMap project_map;
   STRING_LIST_T include_dir_list;
   IncludeDirectories(project_map, include_dir_list, base);
   STRING_LIST_T::const_iterator l = include_dir_list.begin();
   while (l != include_dir_list.end()) {
      if (include_dirs.size() > 0) {
         include_dirs += " \\\n";
      }
      include_dirs += _Config->IncludePathAddSymbol();
      if (inclusion) {
         include_dirs += "\"";
      }
      include_dirs += (*l);
      if (inclusion) {
         include_dirs += "\"";
      }
      l++;
   }
   return include_dirs;
}

STRING_T cProject::LibraryDirs(const char * base)
{
   bool inclusion = false;
   if (strcmp(_Config->ToolChain(), "vs6") == 0) {
      inclusion = true;
   }
   STRING_T library_dirs;
   cProjectMap project_map;
   STRING_LIST_T library_dir_list;
   LibraryDirectories(project_map, library_dir_list, base);
   STRING_LIST_T::const_iterator l = library_dir_list.begin();
   while (l != library_dir_list.end()) {
      if (library_dirs.size() > 0) {
         library_dirs += " \\\n";
      }
      library_dirs += _Config->LibPathAddSymbol();
      if (inclusion) {
         library_dirs += "\"";
      }
      library_dirs += (*l);
      if (inclusion) {
         library_dirs += "\"";
      }
      l++;
   }
   return library_dirs;
}

STRING_T cProject::Libraries(const char * base)
{
   STRING_T libraries;
   cProjectMap project_map;
   STRING_LIST_T library_list;
   Libraries(project_map, library_list, base);
   STRING_LIST_T::const_iterator l = library_list.begin();
   while (l != library_list.end()) {
      if (libraries.size() > 0) {
         libraries += " \\\n";
      }
      libraries += _Config->LibAddSymbol();
      libraries += (*l);
      libraries += _Config->StaticLibLinkExtension();
      l++;
   }
   return libraries;
}

STRING_T cProject::Definitions(bool global_only)
{
   STRING_T definitions;
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      ProjectRelations relation = r->Relation();
      if (relation == uses) {
         cProject * project = *r;
         if (definitions.size() > 0) {
            definitions += " ";
         }
         definitions += project->Definitions();
      }
      p++;
   }

   STRING_LIST_T::const_iterator i = _Definitions.begin();
   while (i != _Definitions.end()) {
      if (definitions.size() > 0) {
         definitions += " ";
      }
      definitions += _Config->CDefSymbol();
      definitions += (*i);
      i++;
   }
   if (!global_only) {
      i = _ProjectDefinitions.begin();
      while (i != _ProjectDefinitions.end()) {
         if (definitions.size() > 0) {
            definitions += " ";
         }
         definitions += _Config->CDefSymbol();
         definitions += (*i);
         i++;
      }
   }
   return definitions;
}

void cProject::SetDefinitions(cSymbolTable * symbol_table)
{
   STRING_T definitions = Definitions(false);
   SetDefinitions(definitions.c_str(), symbol_table);
}

void cProject::List(STRING_T & file_list, PROJECT_FILE_LIST_T & project_files, const char * base)
{
   PROJECT_FILE_LIST_T::const_iterator i = project_files.begin();
   while (i != project_files.end()) {
      if (i != project_files.begin()) {
         file_list += " \\\n";
      }
      cProjectFile * project_file = (*i);
      if (base == NULL) {
         file_list += project_file->Path()->AbsolutePath();
      } else {
         file_list += project_file->Path()->RelativePath(base);
      }
      i++;
   }
   file_list += "\n";
}

bool cProject::ParseDirective(const char * directive, const char * text, const char * file, int line_no)
{
   if (_ConfigurationSkipped) {
      return true;
   }
   if (stricmp(directive, "name") == 0) {
      _ProjectName = text;
   } else if (stricmp(directive, "target") == 0) {
      _TargetType = text;
      if (_TargetType != "resources") {
         AddIncludePath(IntermediateDirectory());
      }
      char target_file[0x200] = {0};
      if (_TargetType == "resources") {
         _NoGeneration = true;;
      } else if (_TargetType == "static_library") {
         sprintf(target_file, "%s/%s%s%s",
                 IntermediateDirectory(),
                 _Config->StaticLibPrefix(),
                 _ProjectName.c_str(),
                 _Config->StaticLibTargetExtension());
         _TargetFile = new cProjectFile(this, target_file, 2, STATIC_LIBRARY_FILE, _MakeFile);
         _TargetFile->SetIsMainTarget(true);
      } else if (_TargetType == "shared_library") {
         sprintf(target_file, "%s/%s%s%s",
                 IntermediateDirectory(),
                 _Config->SharedLibPrefix(),
                 _ProjectName.c_str(),
                 _Config->SharedLibExtension());
         _TargetFile = new cProjectFile(this, target_file, 2, SHARED_LIBRARY_FILE, _MakeFile);
         _TargetFile->SetIsMainTarget(true);
      } else if (_TargetType == "executable") {
         sprintf(target_file, "%s/%s%s%s",
                 IntermediateDirectory(),
                 _Config->ExecutablePrefix(),
                 _ProjectName.c_str(),
                 _Config->ExecutableExtension());
         _TargetFile = new cProjectFile(this, target_file, 2, EXECUTABLE_FILE, _MakeFile);
         _TargetFile->SetIsMainTarget(true);
      }
   } else if (stricmp(directive, "include") == 0) {
      AddIncludePath(text);
   } else if (stricmp(directive, "path") == 0) {
      AddSources(text, WALK_RECURSIVE);
   } else if (stricmp(directive, "path_nr") == 0) {
      AddSources(text);
   } else if (stricmp(directive, "lib_path") == 0) {
      AddLibraryPath(text);
   } else if (stricmp(directive, "lib") == 0) {
      AddLibrary(text);
   } else if (stricmp(directive, "depends_on") == 0) {
      cProject * project = DependentProject(text, depends);
      if (project == NULL) {
///         Printf(M_ERROR, "failed to get dependent project %s skipped processing\n", text);
         return false;
      }
   } else if (stricmp(directive, "uses") == 0) {
      cProject * project = DependentProject(text, uses);
      if (project == NULL) {
///         Printf(M_ERROR, "failed to get dependent project %s skipped processing\n", text);
         return false;
      }
   } else if (stricmp(directive, "extends") == 0) {
      cProject * project = DependentProject(text, extends);
      if (project == NULL) {
///         Printf(M_ERROR, "failed to get dependent project %s skipped processing\n", text);
         return false;
      }
   } else if (stricmp(directive, "src_file") == 0) {
      cProjectFile * source = new cProjectFile(this, text);
   } else if (stricmp(directive, "skip_dir") == 0) {
      SkipDirectory(text);
   } else if (stricmp(directive, "skip_file") == 0) {
      SkipFile(text);
   } else if (stricmp(directive, "c_option") == 0) {
      _Config->AddCOption(text);
   } else if (stricmp(directive, "cpp_option") == 0) {
      _Config->AddCPPOption(text);
   } else if (stricmp(directive, "lib_option") == 0) {
      AddLibOption(text);
   } else if (stricmp(directive, "link_option") == 0) {
      AddLinkOption(text);
   } else if (stricmp(directive, "asm_option") == 0) {
      AddASMOption(text);
   } else if (stricmp(directive, "def") == 0) {
      AddDefinition(text);
   } else if (stricmp(directive, "project_def") == 0) {
      AddProjectDefinition(text);
   } else if (stricmp(directive, "post_generation") == 0) {
      _PostSteps.push_back(text);
   } else {
      Printf(M_WARNING, "unrecognized directive \"%s %s\"\n",
             directive, text);
   }
   return true;
}

void cProject::AddIncludePath(const char * path)
{
   cPath * _path = new cPath(path);
   _IncludePaths->Add(_path);
}

void cProject::AddDependency(cProject * project, ProjectRelations relation)
{
   STRING_T name = project->ProjectName();
   _Dependencies[name.c_str()] = new cProjectRelation(project, relation);
}

void cProject::AddLibraryPath(const char * path)
{
   cPath * _path = new cPath(path);
   _LibraryPaths->Add(_path);
}

void cProject::AddLibrary(const char * library)
{
   STRING_T _library = cPath::ResolveSymbols(library);
   char library_file[0x100] = {0};
   sprintf(library_file, "%s", _library.c_str());
   _Libraries.push_back(library_file);
}

void cProject::AddSources(const char * path, unsigned long flags)
{
   STRING_LIST_T source_files;
   cDirectoryUtils::FileList(source_files, path, flags);
   STRING_LIST_T::const_iterator i = source_files.begin();
   while (i != source_files.end()) {
      STRING_T file = (*i);
      if (!Skipped(file.c_str())) {
         cProjectFile * source = new cProjectFile(this, file.c_str());
      }
      i++;
   }
}

bool cProject::Skipped(const char * path)
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
               if ((path[pos-1] == '/' || path[pos-1] == '\\') &&
                   (path[pos+dir_len] == '/' || path[pos+dir_len] == '\\')) {
//                  Printf(M_INFO, "skipped %s (directory = %s)\n", path, dir_name.c_str());
                  return true;
               }
            } else {
               if (path[pos+dir_len] == '/' || path[pos+dir_len] == '\\') {
//                  Printf(M_INFO, "skipped %s (directory = %s)\n", path, dir_name.c_str());
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
      if (stricmp(file_name.c_str(), (*i).c_str()) == 0) {
//         Printf(M_INFO, "skipped %s (file = %s)\n", path, file_name.c_str());
         return true;
      }
      i++;
   }
//   Printf(M_INFO, "source: %s (%s)\n", path, _ProjectName.c_str());
   return false;
}

void cProject::SkipDirectory(const char * directory)
{
   _SkippedDirectories.push_back(directory);
}

void cProject::SkipFile(const char * file)
{
   _SkippedFiles.push_back(file);
}

void cProject::AddDefinition(const char * definition)
{
   _Definitions.push_back(definition);
}

void cProject::AddProjectDefinition(const char * definition)
{
   _ProjectDefinitions.push_back(definition);
}

bool cProject::Build(cProjectMap & project_map)
{
   if (project_map.Exists(_ProjectName.c_str())) {
      return true;
   } else {
      project_map.Add(_ProjectName.c_str());
   }
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      project->Build(project_map);
      p++;
   }
   if (_NoGeneration) {
      return true;
   }

   if (_BuildFlags & GENERATE_DEP_FILES) {
      Printf(M_INFO, "dependencies of project %s ...\n", _ProjectName.c_str());
      AddIncludeDependencies();
      Printf(M_INFO, "dependencies of project %s done\n", _ProjectName.c_str());
   }

   Printf(M_INFO, "building project %s ...\n", _ProjectName.c_str());
   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   if (cDirectoryUtils::SetCurrentDir(_ProjectFile->Path()->AbsoluteDirectory().c_str())) {
      if (_BuildFlags & GENERATE_DEP_FILES) {
         FILE * stream = fopen(_DepFile->Path()->Path().c_str(), "w");
         if (stream != NULL) {
            PrintDependencies(stream);
            fclose(stream);
         }
      }
      FILE * stream = fopen(_MakeFile->Path()->Path().c_str(), "w");
      if (stream != NULL) {
         PrintMakefile(stream);
         fclose(stream);
      }
      if (cDirectoryUtils::SetCurrentDir(current_dir.c_str())) {
         Printf(M_INFO, "project %s built\n", _ProjectName.c_str());
         return true;
      } else {
         Printf(M_ERROR, "failed to reset directory to %s\n", current_dir.c_str());
         return false;
      }
   } else {
      Printf(M_ERROR, "failed to set directory to %s\n", _ProjectFile->Path()->AbsoluteDirectory().c_str());
      return false;
   }
}

void cProject::IncludeDirectories(cProjectMap & project_map, STRING_LIST_T & directories, const char * base, int level)
{
   if (project_map.Exists(_ProjectName.c_str())) {
      return;
   } else {
      project_map.Add(_ProjectName.c_str());
   }
   PATH_LIST_T paths;
   _IncludePaths->List(paths);
   PATH_LIST_T::const_iterator i = paths.begin();
   while (i != paths.end()) {
      cPath * p = (*i);
      STRING_T path;
      if (base == NULL) {
         path = (*i)->AbsolutePath();
      } else {
         path = (*i)->RelativePath(base);
      }
      directories.push_back(path.c_str());
      i++;
   }
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      STRING_LIST_T dependent_includes;
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      ProjectRelations relation = r->Relation();
      if (relation == uses) {
         project->IncludeDirectories(project_map, dependent_includes, base);
         STRING_LIST_T::const_iterator ip = dependent_includes.begin();
         while (ip != dependent_includes.end()) {
            directories.push_back((*ip).c_str());
            ip++;
         }
      }
      p++;
   }
}
   
void cProject::LibraryDirectories(cProjectMap & project_map, STRING_LIST_T & directories, const char * base, int level)
{
   if (project_map.Exists(_ProjectName.c_str())) {
      return;
   } else {
      project_map.Add(_ProjectName.c_str());
   }
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
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      STRING_LIST_T dependent_libpaths;
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      ProjectRelations relation = r->Relation();
      if (relation == uses) {
         project->LibraryDirectories(project_map, dependent_libpaths, base);
         STRING_LIST_T::const_iterator ip = dependent_libpaths.begin();
         while (ip != dependent_libpaths.end()) {
            directories.push_back((*ip).c_str());
            ip++;
         }
      }
      p++;
   }
   p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      ProjectRelations relation = r->Relation();
      if (relation == uses) {
         cProjectFile * target_file = project->TargetFile();
         if (target_file != NULL) {
            int type = target_file->Type();
            if (type == STATIC_LIBRARY_FILE ||
                type == SHARED_LIBRARY_FILE) {
               if (base == NULL) {
                  directories.push_back(target_file->Path()->AbsoluteDirectory());
               } else {
                  directories.push_back(target_file->Path()->RelativeDirectory(base));
               }
            }
         }
      }
      p++;
   }
}

void cProject::Libraries(cProjectMap & project_map, STRING_LIST_T & libraries, const char * base, int level)
{
   if (project_map.Exists(_ProjectName.c_str())) {
      return;
   } else {
      project_map.Add(_ProjectName.c_str());
   }
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      ProjectRelations relation = r->Relation();
      if (relation == uses) {
         cProject * project = *r;
         STRING_LIST_T dependent_libs;
         project->Libraries(project_map, dependent_libs, base, level + 1);
         STRING_LIST_T::const_iterator lp = dependent_libs.begin();
         while (lp != dependent_libs.end()) {
            STRING_T name = *(lp);
            project_map.String(name.c_str(), level);
            lp++;
         }
         cProjectFile * target_file = project->TargetFile();
         if (target_file != NULL) {
            int type = target_file->Type();
            if (type == STATIC_LIBRARY_FILE ||
                type == SHARED_LIBRARY_FILE) {
               ProjectRelations relation = r->Relation();
               if (relation == uses) {
                  STRING_T name = project->ProjectName();
                  project_map.String(name.c_str(), level);
               } else {
                  int dummy = 0;
               }
            }
         }
      }
      p++;
   }
   STRING_LIST_T::const_iterator i = _Libraries.begin();
   while (i != _Libraries.end()) {
      STRING_T name = *(i);
      project_map.String(name.c_str(), level);
      i++;
   }
   if (level == 0) {
      project_map.Strings(libraries);
   }
}

void cProject::AddIncludeDependencies()
{
   PROJECT_FILE_LIST_T::const_iterator i = _ProjectFiles.begin();
   while (i != _ProjectFiles.end()) {
      cProjectFile * project_file = (*i);
      if (project_file->GeneratedFrom() == NULL) {
         project_file->AddIncludeDependencies();
      }
      i++;
   }
}

void cProject::PrintMakefile(FILE * stream)
{
   time_t now = time(NULL);
   struct tm * time_struct = localtime(&now);
   char * time_string = asctime(time_struct);

   int type = Type();
   STRING_T text;

   STRING_T current_dir = cDirectoryUtils::CurrentDir();
   fprintf(stream, "\n");
   fprintf(stream, "# makefile generated by abuild\n");
   fprintf(stream, "# on %s", time_string);
   fprintf(stream, "# based on build file %s\n", _ProjectFile->Path()->AbsolutePath().c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# additional configuration dependent make code\n");
   text = _Config->MakeCode();
   fprintf(stream, "%s\n", text.c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# include project dependency file\n");
   fprintf(stream, "-include %s.dep\n", _Config->ConfigName());
   fprintf(stream, "\n");

   fprintf(stream, "# intermediate directory\n");
   fprintf(stream, "# the directory where all targets will be generated\n");
   fprintf(stream, "intermediate_dir = %s\n", IntermediateDirectory());
   fprintf(stream, "\n");
   
   fprintf(stream, "# additional names\n");
   fprintf(stream, "project_name = %s\n", _ProjectName.c_str());
   fprintf(stream, "target_name = %s\n", _ProjectName.c_str());
   fprintf(stream, "\n");
   
   const char * base = NULL;
   base = current_dir.c_str();

   fprintf(stream, "# options passed to toolchain\n");
   text = _COptions;
   fprintf(stream, "c_options = %s\n", text.c_str());
   text = _CPPOptions;
   fprintf(stream, "cpp_options = %s\n", text.c_str());
   text = _LinkOptions;
   fprintf(stream, "link_options = %s\n", text.c_str());
   text = _LibOptions;
   fprintf(stream, "lib_options = %s\n", text.c_str());
   text = _ASMOptions;
   fprintf(stream, "asm_options = %s\n", text.c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# definitions passed to toolchain\n");
   text = Definitions(false);
   fprintf(stream, "definitions = %s\n", text.c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# library list used by the project (recursive)\n");
   text = Libraries(base);
   fprintf(stream, "libraries = \\\n%s\n", text.c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# include search directories used by the project (recursive)\n");
   text = IncludeDirs(base);
   fprintf(stream, "include_dirs = \\\n%s\n", text.c_str());
   fprintf(stream, "\n");

   fprintf(stream, "# library search directories used by the project (recursive)\n");
   text = LibraryDirs(base);
   fprintf(stream, "library_dirs = \\\n%s\n", text.c_str());
   fprintf(stream, "\n");

#ifdef lassma
   text = Sources(base);
   fprintf(stream, "\n");
   fprintf(stream, "sources = \\\n%s\n", text.c_str());
#endif

   fprintf(stream, "# target file list of the project\n");
   text = Targets(base);
   fprintf(stream, "targets = \\\n%s\n", text.c_str());

   fprintf(stream, "# object file list of the project\n");
   text = Objects(base);
   fprintf(stream, "objects = \\\n%s\n", text.c_str());
   
   fprintf(stream, "# build of dependent projects\n");
   fprintf(stream, "dependencies:\n");
   DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      if (project->GenerateIt()) {
         STRING_T project_file = project->ProjectFile()->Path()->AbsolutePath();
         STRING_T project_file_relative = cDirectoryUtils::RelPath(current_dir.c_str(), project_file.c_str());
         STRING_T project_dir = cDirectoryUtils::DirName(project_file_relative.c_str());
         fprintf(stream, "\t$(make) -C %s -f%s.mk all\n", project_dir.c_str(), _Config->ConfigName());
      }
      p++;
   }
   fprintf(stream, "\n");

   fprintf(stream, "# target specifications\n");
   fprintf(stream, "all: %s dependencies $(targets)\n", IntermediateDirectory());
   fprintf(stream, "\n");

   fprintf(stream, "# intermediate directory generation\n");
   fprintf(stream, "%s:\n\t $(mkdir) %s\n", IntermediateDirectory(), IntermediateDirectory());
   fprintf(stream, "\n");

   fprintf(stream, "# clean specification\n");
   fprintf(stream, "clean:\n");
   PROJECT_FILE_LIST_T target_files;
   TargetFiles(target_files);
   PROJECT_FILE_LIST_T::const_iterator pf = target_files.begin();
   while (pf != target_files.end()) {
      cProjectFile * project_file = (*pf);
      fprintf(stream, "\t-$(rm) %s\n", project_file->Path()->Path().c_str());
      pf++;
   }
   fprintf(stream, "\n");
   fprintf(stream, "cleanall:\n");
   fprintf(stream, "#\t$(make) -f%s.mk clean\n", _Config->ConfigName());
   fprintf(stream, "\t-$(rmdir) %s\n", IntermediateDirectory());
   p = _Dependencies.begin();
   while (p != _Dependencies.end()) {
      cProjectRelation * r = (*p).second;
      cProject * project = *r;
      if (project->GenerateIt()) {
         STRING_T project_file = project->ProjectFile()->Path()->AbsolutePath();
         STRING_T project_file_relative = cDirectoryUtils::RelPath(current_dir.c_str(), project_file.c_str());
         STRING_T project_dir = cDirectoryUtils::DirName(project_file_relative.c_str());
         fprintf(stream, "\t$(make) -C %s -f%s.mk cleanall\n", project_dir.c_str(), _Config->ConfigName());
      }
      p++;
   }
   fprintf(stream, "\n");

   fprintf(stream, "# make rules for every target file\n");
   pf = target_files.begin();
   while (pf != target_files.end()) {
      cProjectFile * project_file = (*pf);
      if (!project_file->IsMainTarget()) {
         cPath * p = project_file->Path();
         fprintf(stream, "%s: %s\n", p->Path().c_str(),
                 project_file->GeneratedFrom()->Path()->RelativePath(_ProjectFile->Path()->AbsoluteDirectory().c_str()).c_str());
         cProjectFile * build_file = project_file->GeneratedFrom();
         int type = build_file->Type();
         if (type == UNKNOWN_FILE) {
            build_file = project_file;
            type = project_file->Type();
         }
         fprintf(stream, "\t%s\n", build_file->Tool()->CommandLine(type));
         fprintf(stream, "\n");
      }
      pf++;
   }
   if (_TargetFile != NULL) {
      cProjectFile * build_file = _TargetFile->GeneratedFrom();
      int type = build_file->Type();
      if (type == UNKNOWN_FILE) {
         build_file = _TargetFile;
         type = _TargetFile->Type();
      }
      fprintf(stream, "%s: %s.mk", _TargetFile->Path()->Path().c_str(), _Config->ConfigName());
      if (_Dependencies.size() > 0) {
         DEPENDENCY_MAP_T::const_iterator p = _Dependencies.begin();
         while (p != _Dependencies.end()) {
            cProjectRelation * r = (*p).second;
            ProjectRelations relation = r->Relation();
            if (relation == uses) {
               cProject * project = *r;
               if (project->GenerateIt()) {
                  STRING_T target = project->TargetFile()->Path()->RelativePath(current_dir.c_str());
                  fprintf(stream, " %s", target.c_str());
               }
            }
            p++;
         }
         fprintf(stream, " $(objects)");
      }
      fprintf(stream, "\n\t%s\n", build_file->Tool()->CommandLine(type));
      STRING_LIST_T::const_iterator s = _PostSteps.begin();
      while (s != _PostSteps.end()) {
         fprintf(stream, "\t%s\n", (*s).c_str());
         s++;
      }
   }

#ifdef lassma
   cPath * dst_file = new cPath("e:/usr/prj/Shacira/include/include.mk");
   FILE * imak = fopen(dst_file->AbsolutePath().c_str(), "a");
   if (imak != NULL) {
      fprintf(imak, "\ncp = cp\n");
      fprintf(imak, "\nall: \\\n");
      pf = _ProjectFiles.begin();
      while (pf != _ProjectFiles.end()) {
         cProjectFile * project_file = (*pf);
         if (project_file->Type() == H_FILE) {
            cPath * p = project_file->Path();
            fprintf(imak, "%s \\\n", p->Name().c_str());
         }
         pf++;
      }
      fprintf(imak, "\n\n");
      pf = _ProjectFiles.begin();
      while (pf != _ProjectFiles.end()) {
         cProjectFile * project_file = (*pf);
         if (project_file->Type() == H_FILE) {
            cPath * p = project_file->Path();
            fprintf(imak, "%s: %s\n", p->Name().c_str(),
                                      p->AbsolutePath().c_str());
            fprintf(imak, "\t$(cp) $< %s\n\n", p->Name().c_str(),
                                               p->AbsolutePath().c_str());
         }
         pf++;
      }
      fclose(imak);
   }
#endif
}

void cProject::PrintDependencies(FILE * stream)
{
   PROJECT_FILE_LIST_T source_files;
   SourceFiles(source_files);
   PROJECT_FILE_LIST_T::const_iterator s = source_files.begin();
   while (s != source_files.end()) {
      cProjectFile * source = (*s);
      STRING_T file_name = cDirectoryUtils::FileName(source->Path()->AbsolutePath().c_str());
      PROJECT_FILE_LIST_T target_files;
      source->TargetFiles(target_files);
      PROJECT_FILE_LIST_T::const_iterator t = target_files.begin();
      while (t != target_files.end()) {
         const char * delimiter = "";
         cProjectFile * target = (*t);
         cPath * path = target->Path();
         cReliance * reliance = Reliance(file_name.c_str());
         if (reliance != NULL) {
            STRING_T file = path->RelativePath(cDirectoryUtils::CurrentDir().c_str());
            if (HasBlanks(file.c_str())) {
               delimiter = "\"";
            } else {
               delimiter = "";
            }
            fprintf(stream, "%s%s%s: \\\n", delimiter, file.c_str(), delimiter);
            STRING_LIST_T dependent_files;
            reliance->DependentFiles(dependent_files, cDirectoryUtils::CurrentDir().c_str());
            STRING_LIST_T::const_iterator i = dependent_files.begin();
            while (i != dependent_files.end()) {
               STRING_T depends_on = (*i);
               if (HasBlanks(depends_on.c_str())) {
                  delimiter = "\"";
               } else {
                  delimiter = "";
               }
               if (!HasBlanks(depends_on.c_str())) {
                  fprintf(stream, "\t%s%s%s \\\n", delimiter, depends_on.c_str(), delimiter);
               }
               i++;
            }
            fprintf(stream, "\n");
         }
         t++;
      }
      s++;
   }
}

void cProject::SetDefinitions(const char * text, cSymbolTable * symbol_table)
{
   if (*text != '\0') {
      cExpTokenizer tokenizer("", 0);
      tokenizer.Scan(text);
      const char * token_value = NULL;
      const char * symbol = NULL;
      int state = 0;
      int token = tokenizer.GetNextToken(token_value);
      while (token != EMPTY_TOKEN) {
         if (state == 4) {
            if (token == TOK_CONST_STRING ||
                token == TOK_CONST_WSTRING) {
               symbol_table->Define(symbol, token_value);
            } else if (token == TOK_HEX_NUMBER) {
               long hex_value = 0;
               if (sscanf(token_value, "%x", & hex_value) == 1) {
                  symbol_table->Define(symbol, (double)hex_value);
               }
            } else if (token == TOK_DEC_NUMBER) {
               symbol_table->Define(symbol, (double)atol(token_value));
            } else if (token == TOK_REAL_NUMBER) {
               symbol_table->Define(symbol, (double)((float)atof(token_value)));
            }
            state = 0;
         }
         if (state == 3) {
            if (token == TOK_ASSIGNMENT) {
               state = 4;
            } else {
               state = 0;
            }
         }
         if (state == 2) {
            symbol = token_value;
            if (tokenizer.Lookup() == TOK_ASSIGNMENT) {
               state = 3;
            } else {
               symbol_table->Define(symbol);
               state = 0;
            }
         }
         if (state == 1 && *token_value == 'D') {
            state = 2;
         }
         if (token == TOK_AROP_SUB ||
             token == TOK_AROP_DIV) {
            state = 1;
         }
         token = tokenizer.GetNextToken(token_value);
      }
#ifdef lassma
      if (VALUE_TOKEN(token)) {
         token = tokenizer.GetNextToken(symbol_value);
         double value = 0;
         if (token == TOK_IDENTIFIER) {
            value = symbol_table->SymbolValue(symbol_value);
         } else if (token == TOK_DEC_NUMBER) {
            value = (double)atol(symbol_value);
         } else if (token == TOK_HEX_NUMBER) {
            unsigned long hex_value = 0;
            sscanf(symbol_value, "%x", &hex_value);
            value = hex_value;
         } else if (token == TOK_REAL_NUMBER) {
            sscanf(symbol_value, "%lf", &value);
         } else {
            value = 1;
         }
         symbol_table->Define(symbol, value);
      }
#endif
   }
}

void cProject::SetDefinition(const char * symbol, double value, cSymbolTable * symbol_table)
{
}

cReliance * cProject::Reliance(const char * file)
{
   return _Reliances.Reliance(file);
}

void cProject::AddReliance(const char * file, const char * path)
{
   cReliance * reliance = _Reliances.Reliance(file);
   if (reliance == NULL) {
      reliance = new cReliance(file);
      _Reliances.Add(file, reliance);
   }
   cPath * _path = new cPath(path);
   reliance->Add(_path);
}


