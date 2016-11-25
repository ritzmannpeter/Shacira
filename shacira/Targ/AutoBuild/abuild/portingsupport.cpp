
#include "portingsupport.h"
#include "cfileenumerator.h"
#include "cdirectoryutils.h"
#include "cvirtualfilesystem.h"
#include "cpath.h"

class cTokenizer {
public:
   cTokenizer(const char * text)
   {
      _TextPtr = _Text = text;
   };
   bool GetToken(STRING_T & token)
   {
      bool tok = false;
      char c = *_TextPtr;
      while (true) {
         if (c == '\0') {
            break;
         } else if (c == ' ') {
            if (tok) {
               break;
            } else {
               _TextPtr++;
            }
         } else {
            tok = true;
            token += c;
            _TextPtr++;
         }
         c = *_TextPtr;
      }
      return tok;
   };
protected:
   const char * _Text;
   const char * _TextPtr;
};

static char _Buffer[0x8000];

class cSubstFile {
public:
   cSubstFile(const char * path)
   {
      _LineNo = 0;
      _InputStream = NULL;
      _OutputStream = NULL;
      _InputFile = path;
      _InputFile += ".v13";
      _OutputFile = path;
      if (!cDirectoryUtils::RenameFile(path, _InputFile.c_str())) {
//         printf("failed to rename %s to %s\n", path, _InputFile.c_str());
      }
      _InputStream = fopen(_InputFile.c_str(), "r");
      _OutputStream = fopen(_OutputFile.c_str(), "w");
   }
   virtual ~cSubstFile()
   {
      if (_InputStream != NULL) {
         fclose(_InputStream);
      }
      if (_OutputStream != NULL) {
         fclose(_OutputStream);
      }
   };
   inline bool IsOpen()
   {
      return (_InputStream != NULL && _OutputStream != NULL);
   };
   inline bool ReadLine(STRING_T & line, int & line_no)
   {
      _LineNo++;
      if (_InputStream != NULL) {
         char * l = fgets(_Buffer, sizeof(_Buffer), _InputStream);
         if (l != NULL) {
            line = l;
            int size = line.size() - 1;
            if (line[size] == '\n') {
               line[size] = '\0';
            }
            return true;
         }
      }
      return false;
   };
   inline bool WriteLine(const char * line)
   {
      if (_OutputStream != NULL) {
         fprintf(_OutputStream, "%s\n", line);
         return true;
      }
      return false;
   };
   inline int LineNo()
   {
      return _LineNo;
   };
private:
   STRING_T _InputFile;
   STRING_T _OutputFile;
   FILE * _InputStream;
   FILE * _OutputStream;
   int _LineNo;
};

class cPortProcessor : public cFileEnumerator
{
public:
   cPortProcessor(const char * path, bool recursive = false)
      : cFileEnumerator(path, recursive)
   {
      _Vfs = NULL;
   };
protected:
   inline bool Substitute(STRING_T & line, const char * string, const char * subst_string, bool word = false)
   {
      bool changed = false;
      int sub_len = strlen(string);
      int rep_len = strlen(subst_string);
      STRING_T new_string = line.c_str();
      int search_pos = 0;
      int pos = new_string.find(string, search_pos);
      while (pos >= 0) {
         if (!word || IsWord(new_string.c_str(), pos, sub_len)) {
            new_string.replace(pos, sub_len, subst_string);
            changed = true;
         }
         search_pos = pos + rep_len;
         pos = new_string.find(string, search_pos);
      }
      line = new_string;
      return changed;
   };
   inline int Search(const STRING_T & text, const char * string, bool word = false)
   {
      int pos = -1;
      int len = strlen(string);
      pos = text.find(string, 0);
      if (pos >= 0) {
         if (!word || IsWord(text.c_str(), pos, len)) {
            pos = pos;
         }
      }
      return pos;
   };
   inline bool Contains(const STRING_T & text, const char * string, bool word = false)
   {
      return Search(text, string, word) >= 0;
   };
   inline bool IsWord(const char * text, int start, int len)
   {
      char begin = start == 0 ? 0 : text[start-1];
      char end = text[start + len];
      if (isalnum(begin)) {
         return false;
      }
      if (isalnum(end)) {
         return false;
      }
      if (begin == '_' || end == '_' ||
          begin == '-' || end == '-') {
         return false;
      }
      return true;
   };
   inline bool Trim(STRING_T & text, char trim_char)
   {
      if (text[0] == trim_char || text[text.size()-1] == trim_char) {
         int len = text.size();
         STRING_T new_text;
         int i = 0;
         while (i < len && text[i] == trim_char) {
            i++;
         }
         new_text = &(text[i]);
         i = new_text.size() - 1;
         while (i >= 0 && new_text[i] == trim_char) {
            new_text[i] = '\0';
         }
         text = new_text;
         return true;
      }
      return false;
   };
protected:
   cVirtualFileSystem * _Vfs;
};

class cPort14Processor : public cPortProcessor
{
public:
   cPort14Processor(const char * path, bool recursive = false)
      : cPortProcessor(path, recursive)
   {
      const char * shacira_dir = getenv("SHACIRADIR");
      if (shacira_dir == NULL) {
         _QT3FrameworkPath = cDirectoryUtils::FullPath("..\\..\\Shacira\\Src\\GUIFramework\\QT3Framework");
      } else {
         _QT3FrameworkPath = shacira_dir;
         _QT3FrameworkPath += "\\Src\\GUIFramework\\QT3Framework";
      }
      _Vfs = new cVirtualFileSystem;
      AddSources(_Vfs, _QT3FrameworkPath.c_str());
   };
   void AddSources(cVirtualFileSystem * vfs, const char * path)
   {
      STRING_LIST_T source_files;
      cDirectoryUtils::FileList(source_files, path, WALK_RECURSIVE);
      STRING_LIST_T::const_iterator i = source_files.begin();
      while (i != source_files.end()) {
         STRING_T file = (*i);
         cPath * _path = new cPath(file.c_str());
         STRING_T rel_path = _path->RelativePath(path);
         vfs->AddPath(rel_path.c_str());
         i++;
      }
   };
   virtual void File(STRING_T file)
   {
      cPath path(file.c_str());
      if (strcmp(path.Extension().c_str(), "dsw") == 0) {
         SubstDSWFile(file.c_str());
      } else if (strcmp(path.Extension().c_str(), "dsp") == 0) {
         SubstDSPFile(file.c_str());
      } else if (strcmp(path.Extension().c_str(), "pp") == 0) {
         SubstSourceFile(file.c_str());
      } else if (strcmp(path.Extension().c_str(), "cpp") == 0) {
         SubstSourceFile(file.c_str());
      } else if (strcmp(path.Extension().c_str(), "h") == 0) {
         SubstSourceFile(file.c_str());
      }
   };
private:
   void SubstDSWFile(const char * file)
   {
      cSubstFile subst_file(file);
      if (subst_file.IsOpen()) {
         int line_no = 0;
         STRING_T line;
         while (subst_file.ReadLine(line, line_no)) {
            if (Substitute(line, "CWidgets", "q3_widget_plugin", true)) {
            }
            if (Substitute(line, "framework", "q3_framework", true)) {
            }
            if (Substitute(line, "QTFramework", "QT3Framework", true)) {
            }
            if (Substitute(line, "cwidget_plugin", "q3_cwidget_plugin", true)) {
            }
            if (Substitute(line, "qt_plugin_keypads", "q3_keypad_plugin", true)) {
            }
            if (Substitute(line, "qt_plugin_kbdlayouts", "q3_kbdlayout_plugin", true)) {
            }
            subst_file.WriteLine(line.c_str());
         }
      }
   };
   void SubstDSPFile(const char * file)
   {
      cSubstFile subst_file(file);
      if (subst_file.IsOpen()) {
         int line_no = 0;
         STRING_T line;
         while (subst_file.ReadLine(line, line_no)) {
            if (Contains(line, "/I", true) ||
                Contains(line, "/D", true)) {
               line = NewDefinitions(line.c_str(), subst_file.LineNo());
            } else if (Contains(line, "SOURCE=")) {
               line = SetQT3Source(line.c_str(), subst_file.LineNo());
            }
            if (Substitute(line, "omnithread2_rt", "omnithread32_rt", true)) {
            }
            if (Substitute(line, "omnithread2_rtd", "omnithread32_rtd", true)) {
            }
            if (Substitute(line, "omniORB304_rt", "omniORB407_rt", true)) {
            }
            if (Substitute(line, "omniORB304_rtd", "omniORB407_rtd", true)) {
            }
            if (Substitute(line, "omniDynamic304_rt", "omniDynamic407_rt", true)) {
            }
            if (Substitute(line, "omniDynamic304_rtd", "omniDynamic407_rtd", true)) {
            }
            if (Substitute(line, "omniORB3", "omniORB4")) {
            }
            subst_file.WriteLine(line.c_str());
         }
      }
   };
   void SubstSourceFile(const char * file)
   {
      cSubstFile subst_file(file);
      if (subst_file.IsOpen()) {
         int line_no = 0;
         STRING_T line;
         while (subst_file.ReadLine(line, line_no)) {
            char path[0x200] = {0};
            int params = sscanf(line.c_str(), "#include \"%[^\"]s\"", path);
            if (params == 1) {
               STRING_T file_name = cDirectoryUtils::FileName(path);
               STRING_T found_file;
               if (_Vfs->FindFile(file_name.c_str(), found_file)) {
                  file_name = cDirectoryUtils::FileName(found_file.c_str());
                  line = "#include \"";
                  line += file_name.c_str();
                  line += "\"";
                  subst_file.WriteLine("/// adjusted by 14 port");
               } else {
                  if (QT3SubstInclude(file_name.c_str(), found_file)) {
                     line = "#include \"";
                     line += found_file.c_str();
                     line += "\"";
                     subst_file.WriteLine("/// adjusted by 14 port");
                  }
               }
            } else {
               params = sscanf(line.c_str(), "#include <%[^\"]>", path);
               if (params == 1) {
                  STRING_T file_name = cDirectoryUtils::FileName(path);
                  STRING_T found_file;
                  if (_Vfs->FindFile(file_name.c_str(), found_file)) {
                     file_name = cDirectoryUtils::FileName(found_file.c_str());
                     line = "#include \"";
                     line += file_name.c_str();
                     line += "\"";
                     subst_file.WriteLine("/// adjusted by 14 port");
                  } else {
                     if (QT3SubstInclude(file_name.c_str(), found_file)) {
                        line = "#include \"";
                        line += found_file.c_str();
                        line += "\"";
                        subst_file.WriteLine("/// adjusted by 14 port");
                     }
                  }
               }
            }
            subst_file.WriteLine(line.c_str());
         }
      }
   };
   STRING_T NewDefinitions(const char * line, int line_no)
   {
      bool qt3_includes = false;
      bool orb4_definitions = false;
      STRING_T include_base;
      STRING_T new_definitions;
      cTokenizer tokenizer(line);
      STRING_T token;
      while (tokenizer.GetToken(token)) {
         if (stricmp(token.c_str(), "/I") == 0) {
            STRING_T path;
            if (tokenizer.GetToken(path)) {
               if (IsQT3Include(include_base, path.c_str())) {
                  /// ignore
                  qt3_includes = true;
               } else {
                  if (new_definitions.size() > 0) {
                     new_definitions += " ";
                  }
                  new_definitions += "/I ";
                  new_definitions += path.c_str();
               }
            }
         } else if (stricmp(token.c_str(), "/D") == 0) {
            STRING_T def;
            if (tokenizer.GetToken(def)) {
               if (IsORB4Definition(def.c_str())) {
                  /// ignore
                  orb4_definitions = true;
               } else {
                  if (new_definitions.size() > 0) {
                     new_definitions += " ";
                  }
                  new_definitions += "/D ";
                  new_definitions += def.c_str();
               }
            }
         } else {
            if (new_definitions.size() > 0) {
               new_definitions += " ";
            }
            new_definitions += token.c_str();
         }
         token = "";
      }
      if (orb4_definitions) {
         new_definitions += ORB4Definitions().c_str();
      }
      if (qt3_includes) {
         new_definitions += QT3Includes(include_base.c_str()).c_str();
      }
      return new_definitions;
   };
   STRING_T QT3Includes(const char * include_base)
   {
      STRING_T qt3_includes;
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\CWidgets\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\Keypads\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\Styles\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\Dialogs\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\Plugins\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\HTML\"";
      qt3_includes += " /I ";
      qt3_includes += include_base;
      qt3_includes += "\\GUIFramework\\QT3Framework\\Generated\"";
      return qt3_includes;
   };
   STRING_T ORB4Definitions()
   {
      STRING_T orb4_definitions;
      orb4_definitions += "/D ";
      orb4_definitions += "\"__x86__\"";
      orb4_definitions += "/D ";
      orb4_definitions += "\"__WIN32__\"";
      orb4_definitions += "/D ";
      orb4_definitions += "\"_COS_LIBRARY\"";
      return orb4_definitions;
   };
   bool IsQT3Include(STRING_T & include_base, const char * path)
   {
      int pos = Search(path, "GUIFramework");
      if (pos >= 0) {
         if (include_base.size() == 0) {
            int i = 0;
            for (i=0; i<pos-1; i++) {
               include_base += path[i];
            }
         }
         return true;
      }
      return false;
   };
   bool IsORB4Definition(const char * def)
   {
      if (stricmp(def, "__x86__") == 0) {
         return true;
      }
      if (stricmp(def, "__WIN32__") == 0) {
         return true;
      }
      if (stricmp(def, "_COS_LIBRARY") == 0) {
         return true;
      }
      return false;
   };
   STRING_T SetQT3Source(const char * line, int line_no)
   {
      STRING_T new_line = line;
      if (Contains(line, "GUIFramework")) {
         STRING_T path = &(line[strlen("SOURCE=")]);
         bool trimmed = Trim(path, '"');
         int pos = Search(path, "GUIFramework");
         STRING_T base_path;
         if (pos >= 0) {
            int i = 0;
            for (i=0; i<pos-1; i++) {
               base_path += path[i];
            }
         }
         STRING_T file_name = cDirectoryUtils::FileName(path.c_str());
         STRING_T found_file = file_name;
         STRING_T found_file_name = file_name;
         if (_Vfs->FindFile(file_name.c_str(), found_file)) {
            found_file_name = cDirectoryUtils::FileName(found_file.c_str());
         }
         new_line = "SOURCE=";
         if (trimmed) {
            new_line += "\"";
         }
         new_line += base_path.c_str();
         new_line += "\\GUIFramework\\QT3Framework\\";
         new_line += found_file.c_str();
         if (trimmed) {
            new_line += "\"";
         }
         int dummy = 0;
      }
      return new_line;
   };
   bool QT3SubstInclude(const char * file_name, STRING_T & subst_file_name)
   {
      if (stricmp(file_name, "touch_style.h") == 0) {
         subst_file_name = "cQtTouchStyle.h";
         return true;
      } else if (stricmp(file_name, "qt_navigation_widget.h") == 0) {
         subst_file_name = "cQtNavigationWidget.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard.h") == 0) {
         subst_file_name = "cQtKeyboard.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard.h") == 0) {
         subst_file_name = "cQtKeyboard.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard_button.h") == 0) {
         subst_file_name = "cQtKeyboardButton.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard_layout_german.h") == 0) {
         subst_file_name = "cQtKeyboardLayoutGerman.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard_layout_standard.h") == 0) {
         subst_file_name = "cQtKeyboardLayoutStandard.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboard_input.h") == 0) {
         subst_file_name = "cQtKeyboardInput.h";
         return true;
      } else if (stricmp(file_name, "qt_keyboardalpha.h") == 0) {
         subst_file_name = "cQtKeyboardAlpha.h";
         return true;
      } else if (stricmp(file_name, "qt_keypadnumeric.h") == 0) {
         subst_file_name = "cQtKeypadNumeric.h";
         return true;
      } else if (stricmp(file_name, "qt_number_validator.h") == 0) {
         subst_file_name = "cQtNumberValidator.h";
         return true;
      } else if (stricmp(file_name, "qt_string_validator.h") == 0) {
         subst_file_name = "cQtStringValidator.h";
         return true;
      } else if (stricmp(file_name, "qt_property_widget.h") == 0) {
         subst_file_name = "cQtPropertyWidget.h";
         return true;
      }
      return false;
   };
private:
   STRING_T _QT3FrameworkPath;
};

int PortToShacira14()
{
   STRING_T current_directory = cDirectoryUtils::CurrentDir();
   cPort14Processor processor(current_directory.c_str(), true);
   processor.Process();
   return 0;
}

int PortToLinux()
{
   return 0;
}

int PortToQT4()
{
   return 0;
}


