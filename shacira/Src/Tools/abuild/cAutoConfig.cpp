
#include "cAutoConfig.h"
#include "cBuildEntry.h"

#define MAX_FILE_NAME_LENGTH  0x200
#define INVALID_FIND_HANDLE ((void*)NULL)
typedef void * FIND_HANDLE_T;
typedef struct _find_data {
   char file_name[MAX_FILE_NAME_LENGTH];
   ULONG_T file_attributes;
} FIND_DATA_T;
#define FATTR_DIRECTORY 0x00000001

#ifdef _WIN32

static FIND_HANDLE_T FirstFile(CONST_STRING_T spec, FIND_DATA_T * find_data)
{
   memset(find_data, 0, sizeof(*find_data));
   WIN32_FIND_DATA _find_data;
   HANDLE find_handle = FindFirstFile(spec, &_find_data);
   if (find_handle == INVALID_HANDLE_VALUE) {
      return INVALID_FIND_HANDLE;
   } else {
      strcpy(find_data->file_name, _find_data.cFileName);
      if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
         find_data->file_attributes |= FATTR_DIRECTORY;
      }
      return find_handle;
   }
}

static int NextFile(FIND_HANDLE_T find_handle, FIND_DATA_T * find_data)
{
   memset(find_data, 0, sizeof(*find_data));
   WIN32_FIND_DATA _find_data;
   int result = FindNextFile(find_handle, &_find_data);
   if (result == 0) {
      return 0;
   } else {
      strcpy(find_data->file_name, _find_data.cFileName);
      if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
         find_data->file_attributes |= FATTR_DIRECTORY;
      }
      return 1;
   }
}

#else

#endif

STRING_MAP_T cAutoConfig::_ProcessedFiles;

cAutoConfig::cAutoConfig(const char * config_name, const char * config_file)
{
   _TargetFile = NULL;
   _Verbose = false;
   _NoGeneration = false;
   _RevertObjects = false;
   _RevertLibPaths = false;
   _GeneratedHeaderFiles = false;
   _ConfigurationSkipped = false;
   _System = System();
   _Compiler = Compiler();
   _ConfigName = config_name;
   _ConfigFile = config_file;
   char buf[0x100] = {0};
   sprintf(buf, "%s_%s_%s.mk", _System.c_str(), _Compiler.c_str(), _ConfigName.c_str());
   _MakeFile = new cPath(buf);
   sprintf(buf, "%s_%s_%s", _System.c_str(), _Compiler.c_str(), _ConfigName.c_str());
   _TargetDir = buf;
   sprintf(buf, "%s_%s_%s.dep", _System.c_str(), _Compiler.c_str(), _ConfigName.c_str());
   _DependencyFile = buf;
   Load();
   printf("\n");
   printf("configuration %s %s %s\nsystem %s compiler %s:\n",
          _ConfigName.c_str(),
          _TargetType.c_str(),
          _TargetName.c_str(),
          _System.c_str(),
          _Compiler.c_str());
   printf("...\n");
}

cAutoConfig::~cAutoConfig()
{
}

void cAutoConfig::IncludePaths(STRING_LIST_T & include_paths, BOOL_T absolute)
{
   PATH_MAP_T::const_iterator i = _IncludePaths.begin();
   while (i != _IncludePaths.end()) {
      cPath * path = (*i).second;
      if (absolute) {
         include_paths.push_back(path->AbsPathx().c_str());
      } else {
         include_paths.push_back(path->PathSpec().c_str());
      }
      i++;
   }
   DEP_PRJ_MAP_T::const_iterator p = _DependentProjects.begin();
   while (p != _DependentProjects.end()) {
      cDependentConfig * proj = (*p).second;
      cAutoConfig * config = proj->Config();
      config->IncludePaths(include_paths, absolute);
      p++;
   }
}

void cAutoConfig::LibraryPaths(STRING_LIST_T & lib_paths)
{
   PATH_MAP_T::const_iterator i = _LibPaths.begin();
   while (i != _LibPaths.end()) {
      cPath * path = (*i).second;
      lib_paths.push_back(path->PathSpec().c_str());
      i++;
   }
   DEP_PRJ_MAP_T::const_iterator p = _DependentProjects.begin();
   while (p != _DependentProjects.end()) {
      cDependentConfig * proj = (*p).second;
      cAutoConfig * config = proj->Config();
      config->LibraryPaths(lib_paths);
      p++;
   }
}

void cAutoConfig::StaticLibraries(STRING_LIST_T & libraries)
{
   STRING_MAP_T::const_iterator i = _Libraries.begin();
   while (i != _Libraries.end()) {
      STRING_T library = (*i).second;
      libraries.push_back(library.c_str());
      i++;
   }
   DEP_PRJ_MAP_T::const_iterator p = _DependentProjects.begin();
   while (p != _DependentProjects.end()) {
      cDependentConfig * proj = (*p).second;
      cAutoConfig * config = proj->Config();
      config->StaticLibraries(libraries);
      p++;
   }
}

void cAutoConfig::GeneratedHeaders(STRING_LIST_T & generated_headers)
{
   PATH_MAP_T::const_iterator i = _GeneratedHeaders.begin();
   while (i != _GeneratedHeaders.end()) {
      cPath * path = (*i).second;
      generated_headers.push_back(path->PathSpec().c_str());
      i++;
   }
}

STRING_T cAutoConfig::A_I_PATHS()
{
   STRING_T result;
   STRING_LIST_T include_paths;
   IncludePaths(include_paths);
   result += "A_I_PATHS =";
   STRING_LIST_T::const_iterator i = include_paths.begin();
   while (i != include_paths.end()) {
      char include_spec[0x200] = {0};
      if (_Compiler == "gcc") {
         sprintf(include_spec, " \\\n\t-I%s", (const char*)(*i).c_str());
         result += include_spec;
      } else if (_Compiler == "vcpp") {
         sprintf(include_spec, " \\\n\t/I%s", (const char*)(*i).c_str());
         result += include_spec;
      }
      i++;
   }
   return result;
}

STRING_T cAutoConfig::A_GEN_HEADERS()
{
   STRING_T result;
   STRING_LIST_T generated_headers;
   GeneratedHeaders(generated_headers);
   result += "A_GEN_HEADERS =";
   STRING_LIST_T::const_iterator i = generated_headers.begin();
   while (i != generated_headers.end()) {
      char file_spec[0x200] = {0};
      sprintf(file_spec, " \\\n\t%s", (const char*)(*i).c_str());
      result += file_spec;
      i++;
   }
   return result;
}

STRING_T cAutoConfig::A_LIBS()
{
   STRING_T result;
   STRING_LIST_T libraries;
   StaticLibraries(libraries);
   result += "A_LIBS =";
   STRING_LIST_T::const_iterator i = libraries.begin();
   while (i != libraries.end()) {
      char lib_spec[0x200] = {0};
      if (_Compiler == "gcc") {
         sprintf(lib_spec, " \\\n\t-l%s", (const char*)(*i).c_str());
         result += lib_spec;
      } else if (_Compiler == "vcpp") {
         sprintf(lib_spec, " \\\n\t%s.lib", (const char*)(*i).c_str());
         result += lib_spec;
      }
      i++;
   }
   return result;
}

STRING_T cAutoConfig::A_L_PATHS()
{
_RevertLibPaths = true;
   STRING_T result;
   STRING_LIST_T lib_paths;
   LibraryPaths(lib_paths);
   result += "A_L_PATHS =";
   if (!_RevertLibPaths) {
      STRING_LIST_T::const_iterator i = lib_paths.begin();
      while (i != lib_paths.end()) {
         char lib_spec[0x200] = {0};
         if (_Compiler == "gcc") {
            sprintf(lib_spec, " \\\n\t-L\"%s\"", (const char*)(*i).c_str());
            result += lib_spec;
         } else if (_Compiler == "vcpp") {
            sprintf(lib_spec, " \\\n\t/libpath:\"%s\"", (const char*)(*i).c_str());
            result += lib_spec;
         }
         i++;
      }
   } else {
      STRING_LIST_T reverse_list;
      STRING_LIST_T::const_iterator i = lib_paths.begin();
      while (i != lib_paths.end()) {
         reverse_list.push_front((*i));
         i++;
      }
      i = reverse_list.begin();
      while (i != reverse_list.end()) {
         char lib_spec[0x200] = {0};
         if (_Compiler == "gcc") {
            sprintf(lib_spec, " \\\n\t-L\"%s\"", (const char*)(*i).c_str());
            result += lib_spec;
         } else if (_Compiler == "vcpp") {
            sprintf(lib_spec, " \\\n\t/libpath:\"%s\"", (const char*)(*i).c_str());
            result += lib_spec;
         }
         i++;
      }
   }
   return result;
}

STRING_T cAutoConfig::A_TARGETS()
{
   STRING_T result = "A_TARGETS =";
   STRING_LIST_T target_files;
   TargetFiles(target_files);
   STRING_LIST_T::const_iterator i = target_files.begin();
   while (i != target_files.end()) {
      char target_spec[0x200] = {0};
      sprintf(target_spec, " \\\n\t%s", (*i).c_str());
      result += target_spec;
      i++;
   }
   return result;
}

void cAutoConfig::TargetFiles(STRING_LIST_T & target_files)
{
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
   while (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      if (entry->_IsTarget) {
         STRING_T extension = entry->_Path->Extension();
         if (extension[0] == 'h') {
            target_files.push_back(entry->_Path->PathSpec().c_str());
         }
      }
      i++;
   }
   i = _BuildEntries.begin();
   while (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      if (entry->_IsTarget) {
         STRING_T extension = entry->_Path->Extension();
         if (extension[0] == 'c') {
            target_files.push_back(entry->_Path->PathSpec().c_str());
         }
      }
      i++;
   }
   i = _BuildEntries.begin();
   while (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      if (entry->_IsTarget) {
         STRING_T extension = entry->_Path->Extension();
         if (extension[0] != 'h' &&
             extension[0] != 'c') {
            target_files.push_back(entry->_Path->PathSpec().c_str());
         }
      }
      i++;
   }
}

STRING_T cAutoConfig::A_OBJECTS()
{
   _ProcessedFiles.clear();
   if (_Compiler == "gcc") {
      _RevertObjects = false;
   } else {
      _RevertObjects = false;
   }
   STRING_T result = "A_OBJECTS =";
   STRING_LIST_T object_files;
   ObjectFiles(object_files);
   if (!_RevertObjects) {
      STRING_LIST_T::const_iterator i = object_files.begin();
      while (i != object_files.end()) {
         char obj_spec[0x200] = {0};
         sprintf(obj_spec, " \\\n\t%s", (*i).c_str());
         result += obj_spec;
         i++;
      }
   } else {
      STRING_LIST_T reverse_list;
      STRING_LIST_T::const_iterator i = object_files.begin();
      while (i != object_files.end()) {
         reverse_list.push_front((*i));
         i++;
      }
      i = reverse_list.begin();
      while (i != reverse_list.end()) {
         char obj_spec[0x200] = {0};
         sprintf(obj_spec, " \\\n\t%s", (*i).c_str());
         result += obj_spec;
         i++;
      }
   }
   _ProcessedFiles.clear();
   return result;
}

void cAutoConfig::ObjectFiles(STRING_LIST_T & object_files)
{
   STRING_T result = "A_OBJECTS =";
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
   while (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      STRING_T extension = entry->_Path->Extension();
      if (extension == "o" &&
          entry->_IsTarget) {
         if (!Processed(entry->_Path->FileName().c_str())) {
            STRING_T file = entry->_Path->PathSpec();
            object_files.push_back(file.c_str());
         }
      }
      i++;
   }
   DependentObjectFiles(object_files);
}

void cAutoConfig::DependentObjectFiles(STRING_LIST_T & object_files)
{
   DEP_PRJ_MAP_T::const_iterator i = _DependentProjects.begin();
   while (i != _DependentProjects.end()) {
      cDependentConfig * dep_prj = (*i).second;
      if (dep_prj != NULL) {
         if (dep_prj->Config() != NULL) {
            cAutoConfig * config = dep_prj->Config();
            STRING_T config_path = dep_prj->Path();
            if (config->_TargetType == "object_files" ||
                config->_TargetType == "executable") {
               config->ObjectFiles(object_files);
            }
         }
      }
      i++;
   }
}

STRING_T cAutoConfig::A_INCLUDES()
{
   STRING_T result;
   return result;
}

STRING_T cAutoConfig::ToLower(const char * text)
{
   STRING_T lower;
   int size = strlen(text);
   for (int i=0; i<size; i++) {
      lower += tolower(text[i]);
   }
   return lower;
}

void cAutoConfig::SkipDir(const char * dir_name)
{
   STRING_T lower = ToLower(dir_name);
   _SkippedDirs[lower.c_str()] = lower;
}

BOOL_T cAutoConfig::DirExcluded(const char * dir_name)
{
   STRING_T lower = ToLower(dir_name);
   STRING_MAP_T::const_iterator it = _SkippedDirs.find(lower.c_str());
   if (it == _SkippedDirs.end()) {
      return false;
   } else {
      return true;
   }
}

void cAutoConfig::SkipFile(const char * file_name)
{
   STRING_T lower = ToLower(file_name);
   _SkippedFiles[lower.c_str()] = lower;
}

BOOL_T cAutoConfig::FileExcluded(const char * file_name)
{
   STRING_T lower = ToLower(file_name);
   STRING_MAP_T::const_iterator it = _SkippedFiles.find(lower.c_str());
   if (it == _SkippedFiles.end()) {
      return false;
   } else {
      return true;
   }
}

void cAutoConfig::AddDependentProject(const char * path)
{
   STRING_T resolved_path = cConfigUtils::ResolveSymbols(path);
   cDependentConfig * dep_prj = new cDependentConfig(resolved_path.c_str(), this);
   _DependentProjects[resolved_path.c_str()] = dep_prj;
}

void cAutoConfig::AddRecursivePath(const char * path)
{
   cPath * _path = new cPath(path, true);
   _RecursivePaths[_path->Path().c_str()] = _path;
}

void cAutoConfig::AddPath(const char * path)
{
   cPath * _path = new cPath(path, true);
   _Paths[_path->Path().c_str()] = _path;
}

void cAutoConfig::AddLibPath(const char * path)
{
   cPath * _path = new cPath(path, true);
//   _LibPaths[_path->PathSpec().c_str()] = _path;
   _LibPaths[_path->AbsPathx().c_str()] = _path;
}

void cAutoConfig::AddLib(const char * lib)
{
   STRING_T resolved_lib = cConfigUtils::ResolveSymbols(lib);
   _Libraries[lib] = resolved_lib.c_str();
}

void cAutoConfig::AddIncludePath(const char * path)
{
   STRING_T resolved_path = cConfigUtils::ResolveSymbols(path);
   cPath * _path = new cPath(path, true);
   _IncludePaths[_path->AbsPathx().c_str()] = _path;
}

void cAutoConfig::AddBuildEntry(const char * name, cBuildEntry * build_entry)
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

cBuildEntry * cAutoConfig::BuildEntry(const char * name)
{
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.find(name);
   if (i == _BuildEntries.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cAutoConfig::SearchHeaderFiles(const char * path, const char * pattern, BOOL_T recursive, int level)
{
   FIND_DATA_T find_data;
   FIND_HANDLE_T find_handle;
   char * spec = (char*)calloc(1, 0x1000);
   if (strlen(path) > 0) {
      sprintf(spec, "%s/%s", path, pattern);
   } else {
      sprintf(spec, "%s", pattern);
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         STRING_T file_name = find_data.file_name;
         char file[0x400] = {0};
         sprintf(file, "%s/%s", path, file_name.c_str());
         AddHeaderFile(file, level);
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   if (!recursive) {
      return;
   }
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         if (find_data.file_attributes & FATTR_DIRECTORY) {
            if (find_data.file_name[0] != '.') {
               char * new_path = (char*)calloc(1, 0x1000);
               if (strlen(path) > 0) {
                  sprintf(new_path, "%s/%s", path, find_data.file_name);
               } else {
                  sprintf(new_path, "%s", find_data.file_name);
               }
               SearchHeaderFiles(new_path, pattern, recursive, level+1);
               free(new_path);
            }
         }
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   free(spec);
}

int cAutoConfig::AddFiles(const char * path, BOOL_T recursive)
{
   FIND_DATA_T find_data;
   HANDLE find_handle;
   char spec[0x400] = {0};
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         if (!(find_data.file_attributes & FATTR_DIRECTORY)) {
            STRING_T file_name = find_data.file_name;
            AddFile(file_name.c_str(), path);
         }
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   if (!recursive) {
      return 0;
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         if (find_data.file_attributes & FATTR_DIRECTORY) {
            if (find_data.file_name[0] != '.') {
               if (!DirExcluded(find_data.file_name)) {
                  if (strlen(path) > 0) {
                     sprintf(spec, "%s/%s", path, (const char*)find_data.file_name);
                  } else {
                     sprintf(spec, "%s", path, (const char*)find_data.file_name);
                  }
                  AddFiles(spec, recursive);
               }
            }
         }
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   return 0;
}

void cAutoConfig::BuildMakeFile()
{
   if (_NoGeneration || _ConfigurationSkipped) {
      return;
   }
   STRING_T make_file = _MakeFile->File();
   remove(make_file.c_str());
   FILE * stream = fopen(make_file.c_str(), "a");
   if (stream != NULL) {
      if (_Verbose) {
         printf("building make file %s ... ", make_file.c_str());
      }
      fprintf(stream, "\nmake file generated by Autoconfig: dont edit\n");
      fprintf(stream, "\n# build definitions\n");
      fprintf(stream, "config = %s\n", _ConfigName.c_str());
      fprintf(stream, "compiler = %s\n", _Compiler.c_str());
      fprintf(stream, "system = %s\n", _System.c_str());
      fprintf(stream, "target_type = %s\n", _TargetType.c_str());
      fprintf(stream, "\n# include general build instructions\n");
      fprintf(stream, "include $(SHACIRADIR)/Targ/platforms/%s_%s.defs\n", _System.c_str(), _Compiler.c_str());
//      fprintf(stream, "%s\n", Dependencies().c_str());
      fprintf(stream, "\n# include dependencies\n");
      fprintf(stream, "-include %s\n\n", _DependencyFile.c_str());
      fprintf(stream, "%s\n", A_I_PATHS().c_str());
      fprintf(stream, "%s\n", A_GEN_HEADERS().c_str());
      fprintf(stream, "%s\n", A_INCLUDES().c_str());
      fprintf(stream, "%s\n", A_L_PATHS().c_str());
      fprintf(stream, "%s\n", A_LIBS().c_str());
      fprintf(stream, "%s\n", A_OBJECTS().c_str());
      fprintf(stream, "%s\n", A_TARGETS().c_str());
      fprintf(stream, "\n");

      fprintf(stream, ".PHONY: %s all clean\n\n", _TargetDir.c_str());
      PrintDependentProjects(stream);
      fprintf(stream, "clean:\n");
      fprintf(stream, "\t-rm $(A_TARGETS)\n\n");
      if (_TargetType == "static_library") {
         fprintf(stream, "%s: $(A_TARGETS)\n", _TargetFile->File().c_str());
         fprintf(stream, "\t$(lib)\n\n");
         fprintf(stream, "all: dependencies %s $(A_TARGETS) %s\n\n", _TargetDir.c_str(), _TargetFile->File().c_str());
      } else if (_TargetType == "shared_library") {
         fprintf(stream, "%s: $(A_TARGETS)\n", _TargetFile->File().c_str());
         fprintf(stream, "\t$(share)\n\n");
         fprintf(stream, "all: dependencies %s $(A_TARGETS) %s\n\n", _TargetDir.c_str(), _TargetFile->File().c_str());
      } else if (_TargetType == "qt_plugin") {
         fprintf(stream, "%s: $(A_TARGETS)\n", _TargetFile->File().c_str());
         fprintf(stream, "\t$(share)\n");
         fprintf(stream, "\t$(cp) %s $(QTDIR)/plugins/designer/%s\n\n", _TargetFile->File().c_str(), _TargetFile->FileName().c_str());
         fprintf(stream, "all: dependencies %s $(A_TARGETS) %s\n\n", _TargetDir.c_str(), _TargetFile->File().c_str());
      } else if (_TargetType == "executable") {
         fprintf(stream, "%s: $(A_TARGETS)\n", _TargetFile->File().c_str());
         fprintf(stream, "\t$(link)\n\n");
         fprintf(stream, "all: dependencies %s $(A_TARGETS) %s\n\n", _TargetDir.c_str(), _TargetFile->File().c_str());
      } else if (_TargetType == "object_files") {
         fprintf(stream, "all: dependencies %s $(A_TARGETS)\n\n", _TargetDir.c_str());
      } else {
         fprintf(stderr, "unknown target type \"%s\"\n", _TargetType.c_str());
         exit(-1);
      }
      fprintf(stream, "%s: %s\n", _TargetDir.c_str(), make_file.c_str());
      fprintf(stream, "\t$(mkdir) $@\n\n");
      ULONG_T levels = cBuildEntry::_Levels;
      for (int level=levels; level>=0; level--) {
         BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
         while (i != _BuildEntries.end()) {
            cBuildEntry * entry = (*i).second;
            if (entry->_Level == (ULONG_T)level) {
               entry->AddDependencies(entry->File().c_str());
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
   PrintDependencies();
}

void cAutoConfig::Load()
{
   FILE * stream = fopen(_ConfigFile.c_str(), "r");
   if (stream != NULL) {
      int line_no = 1;
      char * line = fgets(cConfigUtils::Buffer(), cConfigUtils::BufferSize(), stream);
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
//            if ((params = sscanf(line_ptr+1, "%[^ ] %s", directive, text)) == 2) {
            if ((params = sscanf(line_ptr+1, "%[^ ] %[^\n]", directive, text)) == 2) {
               SetDirective(directive, text, line_no);
            } else {
               int dummy = 0;
            }
         }
         if (_ConfigurationSkipped) {
            line = NULL;
         } else {
            line = fgets(cConfigUtils::Buffer(), cConfigUtils::BufferSize(), stream);
            line_no++;
         }
      }
      fclose(stream);
      if (!_ConfigurationSkipped) {
         if (strcmp(_TargetType.c_str(), "static_library") == 0) {
            char target_file[0x200] = {0};
            if (strcmp(_Compiler.c_str(), "vcpp") == 0) {
               sprintf(target_file, "%s/%s.lib", _TargetDir.c_str(), _TargetName.c_str());
            } else {
               sprintf(target_file, "%s/lib%s.a", _TargetDir.c_str(), _TargetName.c_str());
            }
            _TargetFile = new cPath(target_file);
            _Libraries[_TargetName.c_str()] = _TargetName.c_str();
            cPath * lib_path = new cPath(_TargetFile->Path().c_str());
            _LibPaths[_TargetFile->FileName().c_str()] = lib_path;
         } else if (strcmp(_TargetType.c_str(), "executable") == 0) {
            char target_file[0x200] = {0};
            if (strcmp(_System.c_str(), "windows") == 0) {
               sprintf(target_file, "%s/%s.exe", _TargetDir.c_str(), _TargetName.c_str());
            } else {
               sprintf(target_file, "%s/%s", _TargetDir.c_str(), _TargetName.c_str());
            }
            _TargetFile = new cPath(target_file);
         } else if (strcmp(_TargetType.c_str(), "shared_library") == 0) {
            char target_file[0x200] = {0};
            if (strcmp(_System.c_str(), "windows") == 0) {
               sprintf(target_file, "%s/%s.dll", _TargetDir.c_str(), _TargetName.c_str());
            } else if (strcmp(_System.c_str(), "linux") == 0) {
               sprintf(target_file, "%s/lib%s.so", _TargetDir.c_str(), _TargetName.c_str());
            }
            _TargetFile = new cPath(target_file);
         } else if (strcmp(_TargetType.c_str(), "qt_plugin") == 0) {
            char target_file[0x200] = {0};
            if (strcmp(_System.c_str(), "windows") == 0) {
               sprintf(target_file, "%s/%s.dll", _TargetDir.c_str(), _TargetName.c_str());
            } else if (strcmp(_System.c_str(), "linux") == 0) {
               sprintf(target_file, "%s/lib%s.so", _TargetDir.c_str(), _TargetName.c_str());
            }
            _TargetFile = new cPath(target_file);
         }
         Configure();
      }
   } else {
      fprintf(stderr, "failed to open configuration file %s/%s\n",
              cFileSystemUtils::CurrentDir().c_str(), _ConfigFile.c_str());
      exit(-1);
   }
}

void cAutoConfig::Configure()
{
   PATH_MAP_T::const_iterator i = _Paths.begin();
   while (i != _Paths.end()) {
      STRING_T dir = (*i).second->Path();
      AddFiles(dir.c_str(), false);
      i++;
   }
   i = _RecursivePaths.begin();
   while (i != _RecursivePaths.end()) {
      STRING_T dir = (*i).second->Path();
      AddFiles(dir.c_str(), true);
      i++;
   }
   PATH_MAP_T::const_iterator f = _SourceFiles.begin();
   while (f != _SourceFiles.end()) {
      cPath * _path = (*f).second;
      STRING_T file_name = _path->FileName();
      STRING_T path = _path->Path();
      AddFile(file_name.c_str(), path.c_str());
      f++;
   }
   if (_GeneratedHeaderFiles) {
      STRING_T path = cFileSystemUtils::FullPath(_TargetDir.c_str());
      AddIncludePath(path.c_str());
   }
   SearchHeaderFiles();
}

void cAutoConfig::SetDirective(const char * directive, const char * text, int line_no)
{
   if (_stricmp(directive, "name") == 0) {
      _TargetName = text;
   } else if (_stricmp(directive, "target") == 0) {
      _TargetType = text;
      if (_TargetType == "resources") {
         _NoGeneration = true;;
      }
   } else if (_stricmp(directive, "system") == 0) {
//      _System = text;
   } else if (_stricmp(directive, "compiler") == 0) {
//      _Compiler = text;
   } else if (_stricmp(directive, "include") == 0) {
      AddIncludePath(text);
   } else if (_stricmp(directive, "path") == 0) {
      AddRecursivePath(text);
   } else if (_stricmp(directive, "path_nr") == 0) {
      AddPath(text);
   } else if (_stricmp(directive, "lib_path") == 0) {
      AddLibPath(text);
   } else if (_stricmp(directive, "lib") == 0) {
      AddLib(text);
   } else if (_stricmp(directive, "depends_on") == 0) {
      AddDependentProject(text);
   } else if (_stricmp(directive, "src_file") == 0) {
      AddSourceFile(text);
   } else if (_stricmp(directive, "skip_dir") == 0) {
      SkipDir(text);
   } else if (_stricmp(directive, "skip_file") == 0) {
      SkipFile(text);
   } else if (_stricmp(directive, "skip_compiler") == 0) {
      if (_stricmp(text, _Compiler.c_str()) == 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else if (_stricmp(directive, "skip_system") == 0) {
      if (_stricmp(text, _System.c_str()) == 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else if (_stricmp(directive, "skip_configuration") == 0) {
      if (_stricmp(text, _ConfigName.c_str()) == 0) {
         _ConfigurationSkipped = true;
         _NoGeneration = true;
      }
   } else {
      fprintf(stderr, "error in %s/%s (%d): unrecognized directive %s %s\n",
              cFileSystemUtils::CurrentDir().c_str(), _ConfigFile.c_str(), line_no,
              directive, text);
      exit(-1);
   }
}

void cAutoConfig::PrintDependentProjects(FILE * stream)
{
   fprintf(stream, "\n");
   fprintf(stream, "dependencies:\n");
   DEP_PRJ_MAP_T::const_iterator i = _DependentProjects.begin();
   while (i != _DependentProjects.end()) {
      cDependentConfig * dep_prj = (*i).second;
      if (dep_prj != NULL) {
         if (dep_prj->Config() != NULL) {
            if (!dep_prj->Config()->_NoGeneration) {
               STRING_T config_path = dep_prj->Path();
               STRING_T config_name = dep_prj->Config()->_MakeFile->File();
               fprintf(stream, "\t$(make) -C %s -f%s all\n", config_path.c_str(), config_name.c_str());
            }
         }
      }
      i++;
   }
   fprintf(stream, "\n");
}

void cAutoConfig::AddFile(const char * file_name, const char * path)
{
   if (!FileExcluded(file_name)) {
      char buf[0x400] = {0};
      sprintf(buf, "%s/%s", path, file_name);
      cBuildEntry * entry = new cBuildEntry(this, buf);
   } else {
      int dummy = 0;
   }
}

void cAutoConfig::AddHeaderFile(const char * file, int level)
{
   cPath * _path = new cPath(file);
   STRING_T file_name = _path->FileName();
   if (level == 0) {
      _HeaderFiles[file_name.c_str()] = _path;
   } else {
      PATH_MAP_T::const_iterator i = _HeaderFiles.find(file_name.c_str());
      if (i == _HeaderFiles.end()) {
         _HeaderFiles[file_name.c_str()] = _path;
      } else {
         STRING_T _file_name = (*i).first;
         cPath * path = (*i).second;
         int dummy = 0;
      }
   }
}

void cAutoConfig::AddGeneratedHeaderFile(const char * file)
{
   AddHeaderFile(file, 0);
   cPath * path = new cPath(file);
   STRING_T file_name = path->FileName();
   _GeneratedHeaders[file_name.c_str()] = path;
   _GeneratedHeaderFiles = true;
}

void cAutoConfig::AddSourceFile(CONST_STRING_T source_file)
{
   cPath * path = new cPath(source_file);
   _SourceFiles[path->FileName().c_str()] = path;
}

cPath * cAutoConfig::HeaderFile(const char * file_name)
{
   PATH_MAP_T::const_iterator i = _HeaderFiles.find(file_name);
   if (i == _HeaderFiles.end()) {
      DEP_PRJ_MAP_T::const_iterator p = _DependentProjects.begin();
      while (p != _DependentProjects.end()) {
         cDependentConfig * proj = (*p).second;
         cAutoConfig * config = proj->Config();
         cPath * path = config->HeaderFile(file_name);
         if (path != NULL) {
            return path;
         }
         p++;
      }
      return NULL;
   } else {
      cPath * path = (*i).second;
      return (*i).second;
   }
}

STRING_T cAutoConfig::TargetDir()
{
   return _TargetDir;
}

BOOL_T cAutoConfig::Processed(CONST_STRING_T file)
{
   STRING_MAP_T::const_iterator i = _ProcessedFiles.find(file);
   if (i == _ProcessedFiles.end()) {
      _ProcessedFiles[file] = file;
      return false;
   } else {
      return true;
   }
}

STRING_T cAutoConfig::Dependencies()
{
   STRING_T result;
   BUILD_ENTRY_MAP_T::const_iterator i = _BuildEntries.begin();
   while (i != _BuildEntries.end()) {
      cBuildEntry * entry = (*i).second;
      STRING_T deps = entry->DependencySpecs();
      if (deps.size() > 0) {
         result += deps.c_str();
      }
      i++;
   }
   return result;
}

void cAutoConfig::PrintDependencies()
{
   remove(_DependencyFile.c_str());
   FILE * stream = fopen(_DependencyFile.c_str(), "a");
   if (stream != NULL) {
      fprintf(stream, "%s\n", Dependencies().c_str());
      fclose(stream);
   }
}

void cAutoConfig::SearchHeaderFiles()
{
   STRING_LIST_T include_paths;
   IncludePaths(include_paths, true);
   STRING_LIST_T::const_iterator i = include_paths.begin();
   while (i != include_paths.end()) {
      STRING_T abs_path = (*i);
      SearchHeaderFiles(abs_path.c_str(), "*.h", true, 0);
      SearchHeaderFiles(abs_path.c_str(), "*.hh", true, 0);
      SearchHeaderFiles(abs_path.c_str(), "*.hpp", true, 0);
      i++;
   }
}

