
#include "cBuildEntry.h"
#include "cMakeConfig.h"

static char _Buffer[0x1000];

ULONG_T cBuildEntry::_Levels = 0;

cBuildEntry::cBuildEntry(cMakeConfig * make_config, CONST_STRING_T file, ULONG_T base_level, int build_class)
{
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
   _MakeConfig = make_config;
   _File = file;
   Setup();
   _MakeConfig->AddBuildEntry(_FileName.c_str(), this);
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
         STRING_T target_file = target->_File;
         char buf[0x200] = {0};
         sprintf(buf, "\n%s:", target_file.c_str());
         spec += buf;
         spec += " \\\n\t";
         sprintf(buf, "%s", _File.c_str());
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
   SetFile();
   if (_BuildClass == UNKNOWN_CLASS) {
      if (_stricmp(_FileExtension.c_str(), "idl") == 0) {
         _BuildClass = IDL_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "c") == 0) {
         _BuildClass = C_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "cpp") == 0) {
         _BuildClass = CPP_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "h") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "hh") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "hpp") == 0) {
         _BuildClass = H_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "sty") == 0) {
         _BuildClass = STYX_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "ui") == 0) {
         _BuildClass = UI_FILE;
      } else if (_stricmp(_FileExtension.c_str(), "pp") == 0) {
         _BuildClass = PP_FILE;
      }
   }
   RefineClass();
   AddTargets();
   SetBuildCommand();
}

void cBuildEntry::SetFile()
{
   int i = 0;
   const char * buf = _File.c_str();
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
      _FileName = _Buffer;
      if (i > 0) {
         memset(_Buffer, 0, sizeof(_Buffer));
         memcpy(_Buffer, buf, i);
         _Path = _Buffer;
      }
   } else {
      _FileName = buf;
   }

   buf = _FileName.c_str();
   len = strlen(buf);
   for (i=len-1; i>=0; i--) {
      if (buf[i] == '.') {
         break;
      }
   }
   if (i >= 0) {
      memset(_Buffer, 0, sizeof(_Buffer));
      memcpy(_Buffer, &(buf[i+1]), len-(i+1));
      _FileExtension = _Buffer;
      if (i > 0) {
         memset(_Buffer, 0, sizeof(_Buffer));
         memcpy(_Buffer, buf, i);
         _BaseName = _Buffer;
      }
   } else {
      _BaseName = _FileName;
   }
}

void cBuildEntry::RefineClass()
{
   if (_BuildClass == H_FILE) {
      FILE * stream = fopen(_File.c_str(), "r");
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
                  STRING_T header_file = _MakeConfig->HeaderFile(include_file_name.c_str());
                  if (header_file.size() > 0) {
                     AddDependency(include_file_name.c_str(), header_file.c_str());
                  }
               } else if ((params = sscanf(line, "#include%[^<]<%[^>]", white_space, include_file)) == 2) {
                  STRING_T include_file_name = FileName(include_file);
                  STRING_T header_file = _MakeConfig->HeaderFile(include_file_name.c_str());
                  if (header_file.size() > 0) {
                     AddDependency(include_file_name.c_str(), header_file.c_str());
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
      sprintf(file_name, "%s.o", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == STYX_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      /// generate c target files
      sprintf(file_name, "%s_int.c", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_lim.c", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_pim.c", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      /// generate h target files
      sprintf(file_name, "%s_int.h", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_lim.h", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s_pim.h", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == IDL_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%sSK.cpp", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%sDynSK.cpp", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s.hh", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == UI_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%s.cpp", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
      sprintf(file_name, "%s.h", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      entry = new cBuildEntry(_MakeConfig, file, _Level, MOC_FILE);
      AddTarget(file_name, entry);
   } else if (_BuildClass == MOC_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "moc_%s.cpp", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level);
      AddTarget(file_name, entry);
   } else if (_BuildClass == PP_FILE) {
      char file_name[0x100] = {0};
      char file[0x200] = {0};
      sprintf(file_name, "%s.h", _BaseName.c_str());
      sprintf(file, "%s/%s", _MakeConfig->_ConfigName.c_str(), file_name);
      cBuildEntry * entry = new cBuildEntry(_MakeConfig, file, _Level, MOC_FILE);
      AddTarget(file_name, entry);
   }
}

void cBuildEntry::AddTarget(CONST_STRING_T file_name, cBuildEntry * target)
{
   target->_IsTarget = true;
   if (target->_BuildClass == H_FILE ||
       target->_BuildClass == MOC_FILE) {
      _MakeConfig->AddHeaderFile(target->_FileName.c_str(), target->_File.c_str(), true);
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
         STRING_T target_file = target->_File;
         if (_BuildClass == CPP_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cpp)\n");
            _BuildCommand += _Buffer;
         } else if (_BuildClass == C_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(ccc)\n");
            _BuildCommand += _Buffer;
         } else if (_BuildClass == STYX_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) $< .\n");
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(styx) %s -makeC -makeINT -verbose\n", _BaseName.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) *.c %s\n", _MakeConfig->_ConfigName.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(ctoh) -ct -CPATH=./%s -HPATH=./%s -PRJ=./%s\n",
                    _MakeConfig->_ConfigName.c_str(),
                    _MakeConfig->_ConfigName.c_str(),
                    _MakeConfig->_ConfigName.c_str());
            _BuildCommand += _Buffer;
//            sprintf(_Buffer, "\tcp *.h %s\n", _MakeConfig->_ConfigName.c_str());
//            _BuildCommand += _Buffer;
            _BuildCommand += "\t$(rm) *.c\n";
//            _BuildCommand += "\t$(rm) *.h\n";
//            _BuildCommand += "\t$(rm) *.cth\n";
            _BuildCommand += "\t$(rm) *.sty\n";
         } else if (_BuildClass == IDL_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) $< .\n");
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\tomniidl -bcxx -WbBOA -Wba $<\n", _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %s.hh %s\n", _BaseName.c_str(), _MakeConfig->_ConfigName.c_str(), _BaseName.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %sSK.cc %s/%sSK.cpp\n", _BaseName.c_str(), _MakeConfig->_ConfigName.c_str(), _BaseName.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(cp) %sDynSK.cc %s/%sDynSK.cpp\n", _BaseName.c_str(), _MakeConfig->_ConfigName.c_str(), _BaseName.c_str());
            _BuildCommand += _Buffer;
            _BuildCommand += "\t$(rm) *.idl\n";
            _BuildCommand += "\t$(rm) *.hh\n";
            _BuildCommand += "\t$(rm) *.cc\n";
         } else if (_BuildClass == UI_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/uic %s -o %s/%s.h\n", _File.c_str(),
                    _MakeConfig->_ConfigName.c_str(),
                    _BaseName.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/uic %s -i %s/%s.h -o %s/%s.cpp\n",
                    _File.c_str(),
                    _MakeConfig->_ConfigName.c_str(),
                    _BaseName.c_str(),
                    _MakeConfig->_ConfigName.c_str(),
                    _BaseName.c_str());
            _BuildCommand += _Buffer;
         } else if (_BuildClass == MOC_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\t$(QTDIR)/bin/moc %s -o%s\n", _File.c_str(), target_file.c_str());
            _BuildCommand += _Buffer;
         } else if (_BuildClass == PP_FILE) {
            sprintf(_Buffer, "%s: %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
            sprintf(_Buffer, "\tpp -f$(SHBIN)/ppQt.pre -o%s %s\n", target_file.c_str(), _File.c_str());
            _BuildCommand += _Buffer;
         }
      }
      i++;
   }
}

