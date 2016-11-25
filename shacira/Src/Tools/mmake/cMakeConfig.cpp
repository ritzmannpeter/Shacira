
#include "cMakeConfig.h"
#include "cBuildEntry.h"

static char _Buffer[0x2000] = {0};
static STRING_T POSIX(const char * path)
{
   sprintf(_Buffer, "%s", path);
   ULONG_T len = strlen(path);
   for (ULONG_T i=0; i<len; i++) {
      if (_Buffer[i] == '\\') {
         _Buffer[i] = '/';
      }
   }
   return _Buffer;
}

cMakeConfig::cMakeConfig(const char * config_name, const char * config_file)
{
//   char current_directory[1024] = {0};
//   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
//   printf("building configuration %s in %s file %s\n", config_name, current_directory, config_file);
   _Verbose = false;
   _System = "win32";
   _Compiler = "vcpp";
   _ConfigName = config_name;
   _ConfigFile = config_file;
   Load();
   printf("\n");
   printf("configuration %s/%s %s system %s compiler %s:\n",
          _ConfigName.c_str(),
          _TargetName.c_str(),
          _TargetType.c_str(),
          _System.c_str(),
          _Compiler.c_str());
   printf("...\n");
}

cMakeConfig::~cMakeConfig()
{
}

STRING_T cMakeConfig::ToLower(const char * text)
{
   STRING_T lower;
   int size = strlen(text);
   for (int i=0; i<size; i++) {
      lower += tolower(text[i]);
   }
   return lower;
}

void cMakeConfig::SkipDir(const char * dir_name)
{
   STRING_T lower = ToLower(dir_name);
   _SkippedDirs[lower.c_str()] = lower;
}

BOOL_T cMakeConfig::DirExcluded(const char * dir_name)
{
   STRING_T lower = ToLower(dir_name);
   STRING_MAP_T::const_iterator it = _SkippedDirs.find(lower.c_str());
   if (it == _SkippedDirs.end()) {
      return false;
   } else {
      return true;
   }
}

void cMakeConfig::SkipFile(const char * file_name)
{
   STRING_T lower = ToLower(file_name);
   _SkippedFiles[lower.c_str()] = lower;
}

BOOL_T cMakeConfig::FileExcluded(const char * file_name)
{
   STRING_T lower = ToLower(file_name);
   STRING_MAP_T::const_iterator it = _SkippedFiles.find(lower.c_str());
   if (it == _SkippedFiles.end()) {
      return false;
   } else {
      return true;
   }
}

void cMakeConfig::AddDependentProject(const char * path)
{
   STRING_T resolved_path = ResolvePath(path);
   int size = _Paths.size();
   cDependentProject * dep_prj = new cDependentProject(resolved_path.c_str(), this);
   _DependentProjects[resolved_path.c_str()] = dep_prj;
}

static void Split(const char * file, STRING_T & path, STRING_T & file_name)
{
   int len = strlen(file);
   int i = 0;
   for (i=len-1; i>=0; i--) {
      if (file[i] == '/' ||
          file[i] == '\\') {
         break;
      }
   }
   if (i >= 0) {
      char buf[0x200] = {0};
      memcpy(buf, &(file[i+1]), len-(i+1));
      file_name = buf;
      if (i > 0) {
         memset(buf, 0, sizeof(buf));
         memcpy(buf, file, i);
         path = buf;
      }
   }
}

void cMakeConfig::AddSrcFile(const char * path)
{
   STRING_T resolved_path = ResolvePath(path);
   STRING_T file_name;
   STRING_T _path;
   Split(resolved_path.c_str(), _path, file_name);
   _SrcFiles[file_name.c_str()] = _path.c_str();
}

void cMakeConfig::AddPath(const char * path)
{
   STRING_T resolved_path = ResolvePath(path);
   int size = _Paths.size();
   _Paths.resize(size+1);
   _Paths[size] = resolved_path;
}

void cMakeConfig::AddIncludePath(const char * path)
{
   STRING_T resolved_path = ResolvePath(path);
   int size = _IncludePaths.size();
   _IncludePaths.resize(size+1);
   _IncludePaths[size] = resolved_path;
}

void cMakeConfig::AddBuildEntry(const char * name, cBuildEntry * build_entry)
{
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.find(name);
   if (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      if (entry != NULL) {
         if (entry->_IsTarget) {
            return;
         }
      }
   }
   _BuildEntries[name] = build_entry;
}

cBuildEntry * cMakeConfig::BuildEntry(const char * name)
{
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.find(name);
   if (i == _BuildEntries.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cMakeConfig::AddFile(const char * file_name, const char * path)
{
   if (!FileExcluded(file_name)) {
      char buf[0x400] = {0};
      sprintf(buf, "%s/%s", path, file_name);
      cBuildEntry * entry = new cBuildEntry(this, buf);
   } else {
      int dummy = 0;
   }
}

void cMakeConfig::SearchHeaderFiles(const char * path, const char * pattern, BOOL_T recursive)
{
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   char * spec = (char*)calloc(1, 0x1000);
   if (strlen(path) > 0) {
      sprintf(spec, "%s/%s", path, pattern);
   } else {
      sprintf(spec, "%s", pattern);
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         STRING_T file_name = find_data.cFileName;
         char file[0x400] = {0};
         sprintf(file, "%s/%s", path, file_name.c_str());
         AddHeaderFile(file_name.c_str(), file);
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   if (!recursive) {
      return;
   }
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (find_data.cFileName[0] != '.') {
               char * new_path = (char*)calloc(1, 0x1000);
               if (strlen(path) > 0) {
                  sprintf(new_path, "%s/%s", path, find_data.cFileName);
               } else {
                  sprintf(new_path, "%s", find_data.cFileName);
               }
               SearchHeaderFiles(new_path, pattern);
               free(new_path);
            }
         }
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   free(spec);
}

void cMakeConfig::AddHeaderFile(const char * file_name, const char * file, BOOL_T dominant)
{
   if (dominant) {
      _HeaderFiles[file_name] = file;
   } else {
      HEADER_FILE_MAP_T::const_iterator i = _HeaderFiles.find(file_name);
      if (i == _HeaderFiles.end()) {
         _HeaderFiles[file_name] = file;
      } else {
         STRING_T _file_name = (*i).first;
         STRING_T _file = (*i).second;
         int dummy = 0;
      }
   }
}

STRING_T cMakeConfig::HeaderFile(const char * file_name)
{
   HEADER_FILE_MAP_T::const_iterator i = _HeaderFiles.find(file_name);
   if (i == _HeaderFiles.end()) {
      return "";
   } else {
      return (*i).second;
   }
}

int cMakeConfig::Find(const char * path)
{
   WIN32_FIND_DATA find_data;
   HANDLE hFind;
   char spec[0x400] = {0};
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            STRING_T file_name = find_data.cFileName;
            AddFile(file_name.c_str(), path);
         }
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   hFind = FindFirstFile(spec, &find_data);
   if (hFind != INVALID_HANDLE_VALUE) {
      int found = 1;
      while (found) {
         if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (find_data.cFileName[0] != '.') {
               if (!DirExcluded(find_data.cFileName)) {
                  if (strlen(path) > 0) {
                     sprintf(spec, "%s/%s", path, (const char*)find_data.cFileName);
                  } else {
                     sprintf(spec, "%s", path, (const char*)find_data.cFileName);
                  }
                  Find(spec);
               }
            }
         }
         found = FindNextFile(hFind, &find_data);
      }
      FindClose(hFind);
   }
   return 0;
}

void cMakeConfig::Analyse()
{
   ULONG_T size = _Paths.size();
   for (ULONG_T i=0; i<size; i++) {
      STRING_T dir = _Paths[i];
      Find(dir.c_str());
   }
   STRING_MAP_T::const_iterator f = _SrcFiles.begin();
   while (f != _SrcFiles.end()) {
      STRING_T file_name = (*f).first;
      STRING_T file = (*f).second;
      AddFile(file_name.c_str(), file.c_str());
      f++;
   }
}

void cMakeConfig::BuildMakeFile()
{
   _MakeFile = _ConfigName.c_str();
   _MakeFile += ".mk";
   _DepFile = _ConfigName.c_str();
   _DepFile += ".dep";
   _ObjFile = _ConfigName.c_str();
   _ObjFile += ".obs";
   _ObjList = _ConfigName.c_str();
   _ObjList += "obs";
   _HdrFile = _ConfigName.c_str();
   _HdrFile += ".hdr";
   _IncFile = _ConfigName.c_str();
   _IncFile += ".inc";
   _TrgFile = _ConfigName.c_str();
   _TrgFile += ".trg";
   remove(_MakeFile.c_str());
   remove(_DepFile.c_str());
   remove(_ObjFile.c_str());
   remove(_ObjList.c_str());
   remove(_HdrFile.c_str());
   remove(_IncFile.c_str());
   remove(_TrgFile.c_str());
   FILE * stream = fopen(_MakeFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building make file %s ... ", _MakeFile.c_str());
      }
      fprintf(stream, "\n");
      fprintf(stream, "\nconfig = %s\n\n", _ConfigName.c_str());
      fprintf(stream, "build_includes = -I. -I%s\n\n", _ConfigName.c_str());
      fprintf(stream, "\n# include general build instructions\n");
      fprintf(stream, "include $(SHACIRADIR)/Targ/platforms/%s_%s.defs\n", _System.c_str(), _Compiler.c_str());
      fprintf(stream, "\n# include additional header file dependencies\n");
      fprintf(stream, "include %s\n", _HdrFile.c_str());
      fprintf(stream, "\n# include object file list\n");
      fprintf(stream, "include %s\n", _ObjFile.c_str());
      fprintf(stream, "\n# include path list\n");
      fprintf(stream, "include %s\n", _IncFile.c_str());
      fprintf(stream, "\n# include general dependencies\n");
      fprintf(stream, "include %s\n", _DepFile.c_str());
      fprintf(stream, "\n# include target file list\n");
      fprintf(stream, "include %s\n", _TrgFile.c_str());
      fprintf(stream, "\n");
      fprintf(stream, ".PHONY: %s all clean\n\n", _ConfigName.c_str());
      PrintDependentProjects(stream);
      fprintf(stream, "clean:\n");
      fprintf(stream, "\t-rm $(trgfiles)\n\n");
      if (_TargetType == "static_library") {
         fprintf(stream, "%s: $(hdrfiles) $(objfiles)\n", _TargetFile.c_str(), _ConfigName.c_str());
         fprintf(stream, "\t$(lib)\n\n");
         fprintf(stream, "all: dependencies %s %s\n\n", _ConfigName.c_str(), _TargetFile.c_str());
      } else if (_TargetType == "shared_library") {
         fprintf(stream, "%s: $(hdrfiles) $(objfiles)\n", _TargetFile.c_str(), _ConfigName.c_str());
         fprintf(stream, "\t$(share)\n\n");
         fprintf(stream, "all: dependencies %s %s\n\n", _ConfigName.c_str(), _TargetFile.c_str());
      } else if (_TargetType == "executable") {
         fprintf(stream, "%s: $(hdrfiles) $(objfiles)\n", _TargetFile.c_str(), _ConfigName.c_str());
         fprintf(stream, "\t$(link)\n\n");
         fprintf(stream, "all: dependencies %s %s\n\n", _ConfigName.c_str(), _TargetFile.c_str());
      } else if (_TargetType == "object_files") {
         fprintf(stream, "all: dependencies %s $(hdrfiles) $(objfiles)\n\n", _ConfigName.c_str());
      } else {
         printf("unknown target type \"%s\"\n", _TargetType.c_str());
      }
      fprintf(stream, "%s: %s\n", _ConfigName.c_str(), _MakeFile.c_str());
      fprintf(stream, "\tshmkdir $@\n\n");
      ULONG_T levels = cBuildEntry::_Levels;
      for (int level=levels; level>=0; level--) {
//      for (int level=0; level<=levels; level++) {
         BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
         while (i != _BuildEntries.end()) {
            cBuildEntry * entry = (*i).second;
            if (entry->_Level == (ULONG_T)level) {
               entry->AddDependencies(entry->_File.c_str());
               STRING_T command = entry->BuildCommand();
               if (command.size() > 0) {
                  fprintf(stream, "%s\n", command.c_str());
               }
            }
            i++;
         }
      }
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
   stream = fopen(_DepFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building dependency file %s ... ", _DepFile.c_str());
      }
      fprintf(stream, "\n");
      BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
      while (i != _BuildEntries.end()) {
         cBuildEntry * entry = (*i).second;
         STRING_T deps = entry->DependencySpecs();
         if (deps.size() > 0) {
            fprintf(stream, "%s\n", deps.c_str());
         }
         i++;
      }
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
   stream = fopen(_ObjFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building object list %s ... ", _ObjFile.c_str());
      }
      fprintf(stream, "\nobjfiles =");
      BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
      while (i != _BuildEntries.end()) {
         cBuildEntry * entry = (*i).second;
         STRING_T extension = entry->_FileExtension;
         if (extension == "o" &&
             entry->_IsTarget) {
            STRING_T file = entry->_File;
            fprintf(stream, " \\\n\t%s", file.c_str());
         }
         i++;
      }
      PrintDependentObjFiles(stream);
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
//   if (_Compiler == "vcpp") {
      stream = fopen(_ObjList.c_str(), "a");
      if (stream != NULL) {
         if (_Verbose) {
            printf("building object list %s ... ", _ObjFile.c_str());
         }
         BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
         while (i != _BuildEntries.end()) {
            cBuildEntry * entry = (*i).second;
            STRING_T extension = entry->_FileExtension;
            if (extension == "o" &&
                entry->_IsTarget) {
               STRING_T file = entry->_File;
               fprintf(stream, " %s", file.c_str());
            }
            i++;
         }
         PrintDependentObjList(stream);
         if (_Verbose) {
            printf("done\n");
         }
      }
      fclose(stream);
//   }
   stream = fopen(_HdrFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building header dependency list %s ... ", _HdrFile.c_str());
      }
      fprintf(stream, "\nhdrfiles =");
      BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
      while (i != _BuildEntries.end()) {
         cBuildEntry * entry = (*i).second;
         STRING_T extension = entry->_FileExtension;
         BOOL_T generated = entry->_Generated;
         if (extension == "h" &&
             entry->_IsTarget) {
            STRING_T file = entry->_File;
            fprintf(stream, " \\\n\t%s", file.c_str());
         }
         i++;
      }
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
   stream = fopen(_IncFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building include path list %s ... ", _IncFile.c_str());
      }
      fprintf(stream, "\nincludes =");
      for (ULONG_T i=0; i<_IncludePaths.size(); i++) {
         STRING_T path = _IncludePaths[i];
         fprintf(stream, " \\\n\t-I%s", path.c_str());
      }
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
   stream = fopen(_TrgFile.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building target list %s ... ", _TrgFile.c_str());
      }
      fprintf(stream, "\ntrgfiles =");
      BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
      while (i != _BuildEntries.end()) {
         cBuildEntry * entry = (*i).second;
         STRING_T extension = entry->_FileExtension;
         if (entry->_IsTarget) {
            STRING_T file = entry->_File;
            fprintf(stream, " \\\n\t%s", file.c_str());
         }
         i++;
      }
      if (_Verbose) {
         printf("done\n");
      }
      fclose(stream);
   }
}

void cMakeConfig::Load()
{
   FILE * stream = fopen(_ConfigFile.c_str(), "r");
   if (stream != NULL) {
      int line_no = 1;
      char * line = fgets(_Buffer, sizeof(_Buffer), stream);
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
            if ((params = sscanf(line_ptr+1, "%[^ ] %s", directive, text)) == 2) {
               SetDirective(directive, text, line_no);
            } else {
            }
         }
         line = fgets(_Buffer, sizeof(_Buffer), stream);
         line_no++;
      }
      fclose(stream);
      ULONG_T path_count = _IncludePaths.size();
      for (ULONG_T i=0; i<path_count; i++) {
         STRING_T path = _IncludePaths[i];
         SearchHeaderFiles(path.c_str(), "*.h");
         SearchHeaderFiles(path.c_str(), "*.hh");
         SearchHeaderFiles(path.c_str(), "*.hpp");
      }
      if (strcmp(_TargetType.c_str(), "static_library") == 0) {
         char target_file[0x200] = {0};
         if (strcmp(_Compiler.c_str(), "vcpp") == 0) {
            sprintf(target_file, "%s/%s.lib", _ConfigName.c_str(), _TargetName.c_str());
         } else {
            sprintf(target_file, "%s/lib%s.a", _ConfigName.c_str(), _TargetName.c_str());
         }
         _TargetFile = target_file;
      } else if (strcmp(_TargetType.c_str(), "executable") == 0) {
         char target_file[0x200] = {0};
         sprintf(target_file, "%s/%s.exe", _ConfigName.c_str(), _TargetName.c_str());
         _TargetFile = target_file;
      }
   } else {
      printf("failed to open configuration file %s\n", _ConfigFile.c_str());
   }
}

void cMakeConfig::SetDirective(const char * directive, const char * text, int line_no)
{
   if (_stricmp(directive, "name") == 0) {
      _TargetName = text;
   } else if (_stricmp(directive, "target") == 0) {
      _TargetType = text;
   } else if (_stricmp(directive, "system") == 0) {
      _System = text;
   } else if (_stricmp(directive, "compiler") == 0) {
      _Compiler = text;
   } else if (_stricmp(directive, "include") == 0) {
      AddIncludePath(text);
   } else if (_stricmp(directive, "path") == 0) {
      AddPath(text);
   } else if (_stricmp(directive, "depends_on") == 0) {
      AddDependentProject(text);
   } else if (_stricmp(directive, "srcfile") == 0) {
      AddSrcFile(text);
   } else if (_stricmp(directive, "skipdir") == 0) {
      SkipDir(text);
   } else if (_stricmp(directive, "skipfile") == 0) {
      SkipFile(text);
   } else {
      printf("unrecognized directive %s %s in line %d\n", directive, text, line_no);
   }
}

STRING_T cMakeConfig::ResolvePath(const char * path)
{
   int len = strlen(path);
   STRING_T new_path = path;
   char head[0x100] = {0};
   char var[0x100] = {0};
   char tail[0x200] = {0};
   if (strncmp(path, "$(", 2) == 0) {
      int params = sscanf(path, "$(%[^)])%s", var, tail);
      if (params == 2) {
         char * content = getenv(var);
         if (content == NULL) {
            printf("environment variable %s not set\n", var);
         } else {
            new_path = POSIX(content);
            new_path += POSIX(tail).c_str();
         }
      }
   } else {
      int params = sscanf(path, "%[^$]$(%[^)])%s", head, var, tail);
      if (params == 3) {
         char * content = getenv(var);
         if (content == NULL) {
            printf("environment variable %s not set\n", var);
         } else {
            new_path = POSIX(head);
            new_path += POSIX(content).c_str();
            new_path += POSIX(tail).c_str();
         }
      }
   }
   return new_path;
}

void cMakeConfig::PrintDependentObjFiles(FILE * stream)
{
   DEP_PRJ_MAP_T::const_iterator i = _DependentProjects.begin();
   while (i != _DependentProjects.end()) {
      cDependentProject * dep_prj = (*i).second;
      if (dep_prj != NULL) {
         if (dep_prj->_Config != NULL) {
            cMakeConfig * config = dep_prj->_Config;
            STRING_T config_path = dep_prj->_ConfigPath;
            if (config->_TargetType == "object_files") {
               BUILD_ENTRY_MAP_T & entries = config->_BuildEntries;
               BUILD_ENTRY_MAP_T::const_iterator i = entries.begin();
               while (i != entries.end()) {
                  cBuildEntry * entry = (*i).second;
                  STRING_T extension = entry->_FileExtension;
                  if (extension == "o" &&
                     entry->_IsTarget) {
                     STRING_T file = entry->_File;
                     fprintf(stream, " \\\n\t%s/%s", config_path.c_str(), file.c_str());
                  }
                  i++;
               }
            }
         }
      }
      i++;
   }
}

void cMakeConfig::PrintDependentObjList(FILE * stream)
{
   DEP_PRJ_MAP_T::const_iterator i = _DependentProjects.begin();
   while (i != _DependentProjects.end()) {
      cDependentProject * dep_prj = (*i).second;
      if (dep_prj != NULL) {
         if (dep_prj->_Config != NULL) {
            cMakeConfig * config = dep_prj->_Config;
            STRING_T config_path = dep_prj->_ConfigPath;
            BUILD_ENTRY_MAP_T & entries = config->_BuildEntries;
            BUILD_ENTRY_MAP_T::const_iterator i = entries.begin();
            while (i != entries.end()) {
               cBuildEntry * entry = (*i).second;
               STRING_T extension = entry->_FileExtension;
               if (extension == "o" &&
                   entry->_IsTarget) {
                  STRING_T file = entry->_File;
                  fprintf(stream, " %s/%s", config_path.c_str(), file.c_str());
               }
               i++;
            }
         }
      }
      i++;
   }
}

void cMakeConfig::PrintDependentProjects(FILE * stream)
{
   fprintf(stream, "\n");
   fprintf(stream, "dependencies:\n");
   DEP_PRJ_MAP_T::const_iterator i = _DependentProjects.begin();
   while (i != _DependentProjects.end()) {
      cDependentProject * dep_prj = (*i).second;
      if (dep_prj != NULL) {
         if (dep_prj->_Config != NULL) {
            STRING_T config_path = dep_prj->_ConfigPath;
            STRING_T config_name = dep_prj->_Config->_MakeFile;
            fprintf(stream, "\tmake -C %s -f%s all\n", config_path.c_str(), config_name.c_str());
         }
      }
      i++;
   }
   fprintf(stream, "\n");
}


cDependentProject::cDependentProject(const char * config_path, cMakeConfig * parent)
{
   _ConfigPath = config_path;
   _Parent = parent;
   char current_directory[1024] = {0};
   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
   if (SetCurrentDirectory(config_path)) {
      _Config = new cMakeConfig(parent->_ConfigName.c_str(), parent->_ConfigFile.c_str());
      _Config->Analyse();
      _Config->BuildMakeFile();
      SetCurrentDirectory(current_directory);
   } else {
      _Config = NULL;
      printf("failed to change to directory %s\n", config_path);
   }
}

cDependentProject::~cDependentProject()
{
}


