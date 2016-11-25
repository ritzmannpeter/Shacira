
#include "cBuildEntry.h"
#include "cAutoConfig.h"

static char _Buffer[0x1000];

ULONG_T cBuildEntry::_Levels = 0;

cBuildEntry::cBuildEntry(cAutoConfig * auto_config, CONST_STRING_T file, ULONG_T base_level, int build_class)
{
   _Path = new cPath(file);
   _IsTarget = false;
   if (base_level > 0) {
      _Generated = true;
   } else {
      _Generated = false;
   }
   _Level = base_level + 1;
   if (_Level > _Levels) {
      _Levels = _Level;
   }
   _BuildClass = build_class;
   _AutoConfig = auto_config;
   Setup();
   _AutoConfig->AddBuildEntry(_Path->FileName().c_str(), this);
}

cBuildEntry::~cBuildEntry()
{
}

STRING_T cBuildEntry::DependencySpecs()
{
   STRING_T spec;
   TARGET_MAP_T::const_iterator i = _Targets.begin();
   while (i != _Targets.end()) {
      cBuildEntry * target = (*i).second;
      if (target != NULL) {
         STRING_T target_file = target->File();
         char buf[0x200] = {0};
         sprintf(buf, "\n%s:", target_file.c_str());
         spec += buf;
         spec += " \\\n\t";
         sprintf(buf, "%s", _Path->File().c_str());
         spec += buf;
         if (_Dependencies.size() > 0) {
            DEPENDENCY_MAP_T::const_iterator j = _Dependencies.begin();
            while (j != _Dependencies.end()) {
               spec += " \\\n\t";
               sprintf(buf, "%s", (*j).second.c_str());
               spec += buf;
               j++;
            }
            spec += "\n";
         }
      }
      i++;
   }
   return spec;
}

void cBuildEntry::Setup()
{
   STRING_T extension = _Path->Extension();
   if (_BuildClass == UNKNOWN_CLASS) {
      if (_stricmp(extension.c_str(), "idl") == 0) {
         _BuildClass = IDL_FILE;
      } else if (_stricmp(extension.c_str(), "c") == 0) {
         _BuildClass = C_FILE;
      } else if (_stricmp(extension.c_str(), "cpp") == 0) {
         _BuildClass = CPP_FILE;
      } else if (_stricmp(extension.c_str(), "h") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(extension.c_str(), "hh") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(extension.c_str(), "hpp") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(extension.c_str(), "sty") == 0) {
         _BuildClass = STYX_FILE;
      } else if (_stricmp(extension.c_str(), "ui") == 0) {
         _BuildClass = UI_FILE;
      } else if (_stricmp(extension.c_str(), "pp") == 0) {
         _BuildClass = PP_FILE;
      } else if (_stricmp(extension.c_str(), "mdl") == 0 ||
                 _stricmp(extension.c_str(), "dec") == 0) {
         _BuildClass = MDLC_FILE;
      }
   }
   RefineClass();
   AddTargets();
   SetBuildCommand();
}

void cBuildEntry::RefineClass()
{
   if (_BuildClass == H_FILE) {
      FILE * stream = fopen(_Path->File().c_str(), "r");
      if (stream != NULL) {
         int len = 0;
         char * line = fgets(_Buffer, sizeof(_Buffer), stream);
         while (line != NULL) {
            len = strlen(line);
            char * line_ptr = line;
            for (int i=0; i<len-1; i++) {
               if (strncmp(line_ptr, "Q_OBJECT", 8) == 0) {
                  _BuildClass = MOC_FILE;
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
}

void cBuildEntry::AddDependencies(CONST_STRING_T file)
{
   if (_BuildClass == CPP_FILE ||
       _BuildClass == C_FILE) {
      FILE * stream = fopen(file, "r");
      if (stream != NULL) {
         int len = 0;
         char * line = fgets(_Buffer, sizeof(_Buffer), stream);
         while (line != NULL) {
            len = strlen(line);
            char * line_ptr = line;
            char white_space[0x100] = {0};
            char include_file[0x100] = {0};
            if (*line_ptr == '#') {
               int params = 0;
               if ((params = sscanf(line, "#include%[^\"]\"%[^\"]", white_space, include_file)) == 2) {
                  STRING_T include_file_name = FileName(include_file);
                  cPath * header_file = _AutoConfig->HeaderFile(include_file_name.c_str());
                  if (header_file != NULL) {
                     STRING_T file = header_file->RelPath();
                     AddDependency(include_file_name.c_str(), file.c_str());
                  }
               } else if ((params = sscanf(line, "#include%[^<]<%[^>]", white_space, include_file)) == 2) {
                  STRING_T include_file_name = FileName(include_file);
                  cPath * header_file = _AutoConfig->HeaderFile(include_file_name.c_str());
                  if (header_file != NULL) {
                     STRING_T file = header_file->RelPath();
                     AddDependency(include_file_name.c_str(), file.c_str());
                  }
               }
            }
            line = fgets(_Buffer, sizeof(_Buffer), stream);
         }
         fclose(stream);
      }
   }
}

void cBuildEntry::AddDependency(CONST_STRING_T file_name, CONST_STRING_T file)
{
   DEPENDENCY_MAP_T::const_iterator i = _Dependencies.find(file_name);
   if (i == _Dependencies.end()) {
      _Dependencies[file_name] = file;
      AddDependencies(file);
   }
}

void cBuildEntry::AddTargets()
{
   if (_BuildClass == CPP_FILE ||
       _BuildClass == C_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%s.o", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == STYX_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      /// generate c target files
      sprintf(file_name, "%s_int.c", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_lim.c", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_pim.c", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      /// generate h target files
      sprintf(file_name, "%s_int.h", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_lim.h", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_pim.h", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == IDL_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%sSK.cpp", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%sDynSK.cpp", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s.hh", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == UI_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%s.cpp", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s.h", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level, MOC_FILE);
      AddTarget(file_name, entry);
   } else if (_BuildClass == MOC_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "moc_%s.cpp", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == PP_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%s.h", _Path->BaseName().c_str());
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level, MOC_FILE);
      AddTarget(file_name, entry);
   } else if (_BuildClass == MDLC_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      char prefix[0x40] = {0};
      if (sscanf(_Path->BaseName().c_str(), "%[^_]_", prefix) != 1) {
        sprintf(prefix, "%s", _Path->BaseName());
      }
      sprintf(file_name, "%s.h", prefix);
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s.tab.cpp", prefix);
      sprintf(file, "%s/%s", _AutoConfig->TargetDir().c_str(), file_name);
      entry = new cBuildEntry(_AutoConfig, file, _Level);
      AddTarget(file_name, entry);
   } else {
      int dummy = 0;
   }
}

void cBuildEntry::AddTarget(CONST_STRING_T file_name, cBuildEntry * target)
{
   target->_IsTarget = true;
   if (target->_BuildClass == H_FILE ||
       target->_BuildClass == MOC_FILE) {
      _AutoConfig->AddGeneratedHeaderFile(target->File().c_str());
   }
   _Targets[file_name] = target;
}

STRING_T cBuildEntry::FileName(CONST_STRING_T file)
{
   STRING_T file_name;
   int i = 0;
   const char * buf = file;
   int len = strlen(buf);
   for (i=len-1; i>=0; i--) {
      if (buf[i] == '/' ||
          buf[i] == '\\') {
         break;
      }
   }
   if (i >= 0) {
      memset(_Buffer, 0, sizeof(_Buffer));
      memcpy(_Buffer, &(buf[i+1]), len-(i+1));
      file_name = _Buffer;
   } else {
      file_name = buf;
   }
   return file_name;
}

void cBuildEntry::SetBuildCommand()
{
   TARGET_MAP_T::const_iterator i = _Targets.begin();
   while (i != _Targets.end()) {
      cBuildEntry * target = (*i).second;
      if (target != NULL) {
         STRING_T target_file = target->File();
         if (_BuildClass == CPP_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cpp)\n");
            _BuildCommand += _Buffer;
         } else if (_BuildClass == C_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(ccc)\n");
            _BuildCommand += _Buffer;
         } else if (_BuildClass == STYX_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) $< .\n");
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(styx) %s -makeC -makeINT -verbose\n", _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) *.c %s\n", _AutoConfig->TargetDir().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(ctoh) -ct -CPATH=./%s -HPATH=./%s -PRJ=./%s\n",
                    _AutoConfig->TargetDir().c_str(),
                    _AutoConfig->TargetDir().c_str(),
                    _AutoConfig->TargetDir().c_str());
            _BuildCommand += _Buffer;
//            sprintf(_Buffer, "\tcp *.h %s\n", _AutoConfig->TargetDir().c_str());
//            _BuildCommand += _Buffer;
            _BuildCommand += "\t$(rm) *.c\n";
//            _BuildCommand += "\t$(rm) *.h\n";
//            _BuildCommand += "\t$(rm) *.cth\n";
            _BuildCommand += "\t$(rm) *.sty\n";
         } else if (_BuildClass == IDL_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) $< .\n");
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\tomniidl -bcxx -WbBOA -Wba $<\n", _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %s.hh %s\n", _Path->BaseName().c_str(), _AutoConfig->TargetDir().c_str(), _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %sSK.cc %s/%sSK.cpp\n", _Path->BaseName().c_str(), _AutoConfig->TargetDir().c_str(), _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %sDynSK.cc %s/%sDynSK.cpp\n", _Path->BaseName().c_str(), _AutoConfig->TargetDir().c_str(), _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
            _BuildCommand += "\t$(rm) *.idl\n";
            _BuildCommand += "\t$(rm) *.hh\n";
            _BuildCommand += "\t$(rm) *.cc\n";
         } else if (_BuildClass == UI_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/uic %s -o %s/%s.h\n", _Path->File().c_str(),
                    _AutoConfig->TargetDir().c_str(),
                    _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/uic %s -i %s/%s.h -o %s/%s.cpp\n",
                    _Path->File().c_str(),
                    _AutoConfig->TargetDir().c_str(),
                    _Path->BaseName().c_str(),
                    _AutoConfig->TargetDir().c_str(),
                    _Path->BaseName().c_str());
            _BuildCommand += _Buffer;
         } else if (_BuildClass == MOC_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/moc %s -o%s\n", _Path->File().c_str(), target_file.c_str());
            _BuildCommand += _Buffer;
         } else if (_BuildClass == PP_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\tpp -f$(SHBIN)/ppQt.pre -o%s %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
         } else if (_BuildClass == MDLC_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _Path->File().c_str());
            _BuildCommand += _Buffer;
            char prefix[0x40] = {0};
            if (sscanf(_Path->BaseName().c_str(), "%[^_]_", prefix) != 1) {
               sprintf(prefix, "%s", _Path->BaseName());
            }
            STRING_T src_dir = cFileSystemUtils::DirName(_Path->File().c_str());
            STRING_T target_dir = _AutoConfig->TargetDir();
            STRING_T extension = _Path->Extension();
            sprintf(_Buffer, "\t$(mdlc) model=%s/%s.%s class=model input=%s header=%s/%s.h table=%s/%s.tab  strings=%s/%s.txt\n",
                    src_dir.c_str(),
                    prefix,
                    extension.c_str(),
                    _Path->File().c_str(),
                    target_dir.c_str(),
                    prefix,
                    target_dir.c_str(),
                    prefix,
                    src_dir.c_str(),
                    prefix);
            _BuildCommand += _Buffer;
         }
      }
      i++;
   }
}

