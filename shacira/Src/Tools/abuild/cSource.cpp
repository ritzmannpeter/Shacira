
#include "cSource.h"
#include "cAutoProject.h"

static char _Buffer[0x1000];

cSource::cSource(cAutoProject * project, const char * file, SourceFileTypes type, bool generated)
{
   _Project = project;
   _Path = new cPath(file);
AddVFS(_Path->AbsolutePath().c_str());
   if (!generated &&
      !_Path->Exists()) {
      Printf("not found: %s\n", _Path->AbsolutePath().c_str());
      // abort
   }
   _Type  = type;
   SetType();
   AddTargets();
   _Project->AddSource(this);
}

cSource::~cSource()
{
}

cPath * cSource::Path()
{
   return _Path;
}

SourceFileTypes cSource::Type()
{
   return _Type;
}

STRING_T cSource::TypeName()
{
   switch (_Type) {
   case UNKNOWN_TYPE: return "UNKNOWN_TYPE";
   case IDL_FILE: return "IDL_FILE";
   case C_FILE: return "C_FILE";
   case CPP_FILE: return "CPP_FILE";
   case H_FILE: return "H_FILE";
   case STYX_FILE: return "STYX_FILE";
   case UI_FILE: return "UI_FILE";
   case MOC_FILE: return "MOC_FILE";
   case PP_FILE: return "PP_FILE";
   case MDLC_FILE: return "MDLC_FILE";
   }
   return "?";
}

void cSource::AddIncludeDependencies()
{
   if (
       _Type == C_FILE ||
       _Type == CPP_FILE ||
       _Type == H_FILE ||
       _Type == PP_FILE
       ) {
      AddIncludeDependencies(_Path->AbsolutePath().c_str());
   }
}

void cSource::SetType()
{
   STRING_T extension = _Path->Extension();
   if (_Type == UNKNOWN_TYPE) {
      if (_stricmp(extension.c_str(), "idl") == 0) {
         _Type = IDL_FILE;
      } else if (_stricmp(extension.c_str(), "c") == 0) {
         _Type = C_FILE;
      } else if (_stricmp(extension.c_str(), "cpp") == 0) {
         _Type = CPP_FILE;
      } else if (_stricmp(extension.c_str(), "cc") == 0) {
         _Type = CPP_FILE;
      } else if (_stricmp(extension.c_str(), "h") == 0) {
         _Type = H_FILE;
         CheckForMOCFile();
      } else if (_stricmp(extension.c_str(), "hh") == 0) {
         _Type = H_FILE;
         CheckForMOCFile();
      } else if (_stricmp(extension.c_str(), "hpp") == 0) {
         _Type = H_FILE;
         CheckForMOCFile();
      } else if (_stricmp(extension.c_str(), "sty") == 0) {
         _Type = STYX_FILE;
      } else if (_stricmp(extension.c_str(), "ui") == 0) {
         _Type = UI_FILE;
      } else if (_stricmp(extension.c_str(), "pp") == 0) {
         _Type = PP_FILE;
      } else if (_stricmp(extension.c_str(), "mdl") == 0 ||
                 _stricmp(extension.c_str(), "dec") == 0) {
         _Type = MDLC_FILE;
      }
   }
}

void cSource::CheckForMOCFile()
{
   FILE * stream = fopen(_Path->AbsolutePath().c_str(), "r");
   if (stream != NULL) {
      int len = 0;
      char * line = fgets(_Buffer, sizeof(_Buffer), stream);
      while (line != NULL) {
         len = strlen(line);
         char * line_ptr = line;
         for (int i=0; i<len-1; i++) {
            if (strncmp(line_ptr, "Q_OBJECT", 8) == 0) {
               _Type = MOC_FILE;
               fclose(stream);
               return;
            }
            line_ptr++;
         }
         line = fgets(_Buffer, sizeof(_Buffer), stream);
      }
      fclose(stream);
   }
}

void cSource::AddTargets()
{
   cSource * source = NULL;
   char target_file[0x200] = {0};
   switch (_Type) {
   case UNKNOWN_TYPE:
      break;
   case IDL_FILE:
      break;
   case C_FILE:
      sprintf(target_file, "%s/%s.o", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case CPP_FILE:
      sprintf(target_file, "%s/%s.o", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case H_FILE:
      break;
   case STYX_FILE:
      sprintf(target_file, "%s/%s_lim.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s_pim.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s_int.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s_lim.c", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s_pim.c", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s_int.c", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case UI_FILE:
      sprintf(target_file, "%s/%s.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/%s.cpp", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/moc_%s.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      sprintf(target_file, "%s/moc_%s.cpp", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case MOC_FILE:
      sprintf(target_file, "%s/moc_%s.cpp", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case PP_FILE:
      sprintf(target_file, "%s/%s.h", IntermediateDirectory(), _Path->BaseName().c_str());
      source = new cSource(_Project, target_file);
      break;
   case MDLC_FILE:
      break;
   }
}

static char _WhiteSpace[0x1000] = {0};
void cSource::AddIncludeDependencies(const char * file)
{
   STRING_T file_name = cDirectoryUtils::FileName(file);
   cReliance * reliance = _Project->Reliance(file_name.c_str());   
   if (reliance == NULL) {
      STRING_LIST_T include_directories;
      _Project->IncludeDirectories(include_directories, cDirectoryUtils::CurrentDir().c_str());
      FILE * stream = fopen(file, "r");
      if (stream != NULL) {
         int len = 0;
         char * line = fgets(_Buffer, sizeof(_Buffer), stream);
         while (line != NULL) {
            len = strlen(line);
            char * line_ptr = line;
            if (*line_ptr == '#') {
               int params = 0;
               char include_file[0x200] = {0};
               if ((params = sscanf(line, "#include%[^\"]\"%[^\"]", _WhiteSpace, include_file)) == 2) {
                  STRING_T header_file = HeaderFile(include_directories, include_file,
                                                    cDirectoryUtils::DirName(file).c_str());
                  if (header_file.size() > 0) {
                     _Project->AddReliance(file_name.c_str(), header_file.c_str());
                     AddIncludeDependencies(header_file.c_str());
                  }
               } else if ((params = sscanf(line, "#include%[^<]<%[^>]", _WhiteSpace, include_file)) == 2) {
                  STRING_T header_file = HeaderFile(include_directories, include_file,
                                                    cDirectoryUtils::DirName(file).c_str());
                  if (header_file.size() > 0) {
                     _Project->AddReliance(file_name.c_str(), header_file.c_str());
                     AddIncludeDependencies(header_file.c_str());
                  }
               }
            }
            line = fgets(_Buffer, sizeof(_Buffer), stream);
         }
         fclose(stream);
      }
   }
}

STRING_T cSource::HeaderFile(STRING_LIST_T & include_directories, const char * file_spec, const char * base_dir)
{
   STRING_T file_name = cDirectoryUtils::FileName(file_spec);
//Printf("check for %s %s\n", file_name.c_str(), file_spec);
   STRING_T header_file;
   STRING_T file;
   STRING_LIST_T::const_iterator i = include_directories.begin();
   while (i != include_directories.end()) {
//Printf("check in %s\n", (*i).c_str());
      file = cDirectoryUtils::AppendPath((*i).c_str(), file_spec);
      file = cDirectoryUtils::FullPath(file.c_str());
      if (FindVFS(file.c_str())) {
//Printf("%s okay (VFS)\n", file.c_str());
         return file;
      }
      if (cDirectoryUtils::FileExists(file.c_str())) {
//Printf("%s okay\n", file.c_str());
         AddVFS(file.c_str());
         return file;
      }
      i++;
   }
   file = cDirectoryUtils::AppendPath(base_dir, file_spec);
   file = cDirectoryUtils::FullPath(file.c_str());
//Printf("check in %s\n", base_dir);
   if (FindVFS(file.c_str())) {
//Printf("%s okay (VFS)\n", file.c_str());
      return file;
   }
   if (cDirectoryUtils::FileExists(file.c_str())) {
//Printf("%s okay\n", file.c_str());
      AddVFS(file.c_str());
      return file;
   }
Printf("%s not found\n", file_spec);
   return "";
}

