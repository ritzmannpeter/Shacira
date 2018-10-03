
/// PR 12.10.05 - introduced 2 Step parsing in cStyxParser
///               undefined and double defined variables now are reported
///             - switched to english based reporting
/// PR 17.07.06 - adaptions for linux port
/// PR 05.01.08 - added unit definition texts to localization texts (Horst Anselm FM)
/// PR 11.11.10 - general work on different modes, paths, ...

#include "FirstHeader.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/cTokenizer.h"
#include "Language/cStyxParser.h"
#include "System/Database/cFuncDecl.h"
#include "System/Database/cFuncDecl.h"
#include "System/Database/cContext.h"
#include "System/Process/cResources.h"
#include "Tools/utilities/cstringsink.h"
#include "System/Database/cUnitDef.h"
#include "System/cError.h"

static CONST_STRING_T _Version = "1.4.2";
static STRING_T _BaseName;
static STRING_T _InputDir;
static STRING_T _OutputDir;
static STRING_T _InputFile;
static STRING_T _ModelFile;
static STRING_T _HeaderFile;
static STRING_T _TabFile;
static STRING_T _StringFile;
static STRING_T _MetaClass;
static BOOL_T _Verbose = true;
static BOOL_T _StdC = true;
#define CLASSIC         0
#define MULTIPLE_TABS   1
#define AUTO_REGISTER   2
static long _Mode = CLASSIC;

static cStringSink _Sink;

static void AddString(CONST_STRING_T str)
{
   _Sink.AddString(str);
}

static void SaveStrings(const char * output_file_name)
{
   _Sink.LoadStringFile(output_file_name);
   _Sink.SaveStringFile(output_file_name);
}
   
static void PrintType(FILE * stream, int type)
{
   switch (type) {
   case SH_VOID: fprintf(stream, "void"); break;
   case SH_CHAR: fprintf(stream, "LONG_T"); break;
   case SH_UCHAR: fprintf(stream, "ULONG_T"); break;
   case SH_SHORT: fprintf(stream, "LONG_T"); break;
   case SH_USHORT: fprintf(stream, "ULONG_T"); break;
   case SH_LONG: fprintf(stream, "LONG_T"); break;
   case SH_ULONG: fprintf(stream, "ULONG_T"); break;
   case SH_FLOAT: fprintf(stream, "FLOAT_T"); break;
   case SH_DOUBLE: fprintf(stream, "DOUBLE_T"); break;
   case SH_STRING: fprintf(stream, "CONST_STRING_T"); break;
   case SH_WSTRING: fprintf(stream, "CONST_WSTRING_T"); break;
   case SH_BYTE: fprintf(stream, "BUF_T"); break;
   case SH_OBJECT: fprintf(stream, "BUF_T"); break;
   default: fprintf(stream, "unknown_%d", type); break;
   }
}

static void PrintReturnType(FILE * stream, int type)
{
   switch (type) {
   case SH_VOID: fprintf(stream, "void"); break;
   case SH_CHAR: fprintf(stream, "LONG_T"); break;
   case SH_UCHAR: fprintf(stream, "ULONG_T"); break;
   case SH_SHORT: fprintf(stream, "LONG_T"); break;
   case SH_USHORT: fprintf(stream, "ULONG_T"); break;
   case SH_LONG: fprintf(stream, "LONG_T"); break;
   case SH_ULONG: fprintf(stream, "ULONG_T"); break;
   case SH_FLOAT: fprintf(stream, "FLOAT_T"); break;
   case SH_DOUBLE: fprintf(stream, "DOUBLE_T"); break;
   case SH_STRING: fprintf(stream, "CONST_STRING_T"); break;
   case SH_WSTRING: fprintf(stream, "CONST_WSTRING_T"); break;
   case SH_BYTE: fprintf(stream, "BUF_T"); break;
   case SH_OBJECT: fprintf(stream, "BUF_T"); break;
   default: fprintf(stream, "unknown_%d", type); break;
   }
}

static void Usage(FILE * stream)
{
   fprintf(stream, "usage: mdlc <options>\n");
   fprintf(stream, " options:\n");
   fprintf(stream, "  mode=<mode>\n");
   fprintf(stream, "   0:classic mode\n");
   fprintf(stream, "   1:enable multiple function tables\n");
   if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4) {
   } else {
      fprintf(stream, "   2:auto register functions\n");
   }
   fprintf(stream, "  class=<class>\n");
   fprintf(stream, "   gui: gui functions\n");
   fprintf(stream, "   model: model functions\n");
   fprintf(stream, "  input=<input file> file to compile\n");
   fprintf(stream, "  header=<header file> header file to generate (output)\n");
   fprintf(stream, "  table=<table file> table file to generate (output)\n");
   fprintf(stream, "  strings=<string file> string file to generate (output)\n");
   fprintf(stream, "  model=<model file> new model file, includes resolved (output)\n");
   fprintf(stream, "\n");
}

static void PrintCompilerVersion(FILE * stream)
{
   fprintf(stream, "//\n");
   fprintf(stream, "// Shacira %d.%d.%d data model compiler version %s ...\n", (int)SHACIRA_MAJOR, (int)SHACIRA_MINOR, (int)SHACIRA_BUG_FIX, _Version);
   fprintf(stream, "//\n");
}

static void PrintPrototypeProlog(FILE * stream, const char * base_name)
{
   fprintf(stream, "\n#ifndef _%s_h_\n", base_name);
   fprintf(stream, "#define _%s_h_\n\n", base_name);
   PrintCompilerVersion(stream);
   fprintf(stream, "/*\n * generated prototypes for %s\n */\n\n", _InputFile.c_str());
   if (_stricmp(_MetaClass.c_str(), "gui") == 0) {
      if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4) {
         fprintf(stream, "#include \"cwidgethelper.h\"\n\n");
      } else {
         fprintf(stream, "#include \"CWidgetBase.h\"\n\n");
      }
   }
   if (_Mode != AUTO_REGISTER) {
      if (_StdC) {
         fprintf(stream, "extern \"C\" {\n\n");
      }
   }
}

static void PrintPrototypeEpilog(FILE * stream, const char * base_name)
{
   fprintf(stream, "\n");
   if (_Mode != AUTO_REGISTER) {
      if (_StdC) {
         fprintf(stream, "}\n\n");
      }
   }
   fprintf(stream, "#endif // _%s_h_\n\n", base_name);
}

static void PrintFunctionTableProlog(FILE * stream)
{
   PrintCompilerVersion(stream);
   if (_Mode == MULTIPLE_TABS) {
      fprintf(stream, "#include \"FirstHeader.h\"\n");
      fprintf(stream, "#include \"cstfuncs.h\"\n");
      STRING_T header_file_name = cFileSystemUtils::FileName(_HeaderFile.c_str());
      fprintf(stream, "#include \"%s\"\n\n", header_file_name.c_str());
      fprintf(stream, "static FUNC_ENTRY_T %s_tab[] = {\n", _BaseName.c_str());
   } else if (_Mode == AUTO_REGISTER) {
      fprintf(stream, "#include \"FirstHeader.h\"\n");
      fprintf(stream, "#include \"System/Database/cFuncRef.h\"\n");
      fprintf(stream, "#include \"System/ApplicationInterface.h\"\n");
      STRING_T header_file_name = cFileSystemUtils::FileName(_HeaderFile.c_str());
      fprintf(stream, "#include \"%s\"\n\n", header_file_name.c_str());
   }
}

static void PrintFunctionTableEpilog(FILE * stream)
{
   if (_Mode == MULTIPLE_TABS) {
      STRING_T meta_class_code;
      if (_stricmp(_MetaClass.c_str(), "model") == 0) {
         meta_class_code = "MODEL_FUNCTIONS";
      } else if (_stricmp(_MetaClass.c_str(), "gui") == 0) {
         meta_class_code = "GUI_FUNCTIONS";
      }
      fprintf(stream, "   {NULL, NULL, 0}\n");
      fprintf(stream, "};\n\n");
      fprintf(stream, "static cFunctionTable _%s_Table(%s, %s_tab, \"%s_tab\", 0);\n",
              _BaseName.c_str(),
              meta_class_code.c_str(),
              _BaseName.c_str(),
              _BaseName.c_str());
   } else if (_Mode == AUTO_REGISTER) {
   }
}

static void PrintFuncPrototype(FILE * stream, cFuncDecl * func)
{
   UCHAR_T func_class = func->_FuncClass;
   PrintReturnType(stream, func->_DataType);
   if (func_class != SH_FREE) {
      fprintf(stream, " %s", func->_FuncName.c_str());
      fprintf(stream, "(cContext * _context");
   } else {
      fprintf(stream, " %s", func->_FuncName.c_str());
      fprintf(stream, "(");
   }
   switch (func_class) {
   case SH_FREE:
   case SH_EMBED:
      break;
   case SH_FILTER:
      fprintf(stream, ", ");
      PrintType(stream, func->_DataType);
      fprintf(stream, " _value");
      if (func->_DataType == SH_OBJECT) {
         fprintf(stream, ", ULONG_T *_size");
      }
      fprintf(stream, ", ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4");
      break;
   case SH_CONVERSION:
   case SH_UNIT:
   case SH_ACCESS:
      fprintf(stream, ", ");
      PrintType(stream, func->_DataType);
      fprintf(stream, " _value");
      fprintf(stream, ", ULONG_T _flags, LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4");
      break;
   case SH_DEVICE_STATE:
      fprintf(stream, ", LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4");
      break;
   case SH_LIMIT:
      fprintf(stream, ", LONG_T _i1, LONG_T _i2, LONG_T _i3, LONG_T _i4");
      break;
   case SH_VIEW:
   case SH_DARK:
   case SH_BUTTON:
   case SH_WINIT:
      fprintf(stream, ", WIDGET_PTR _widget");
      break;
   case SH_VALUE:
      fprintf(stream, ", WIDGET_PTR _widget, LONG_T _value, ULONG_T flags");
      break;
   case SH_SIG_FILTER:
      fprintf(stream, ", WIDGET_PTR _widget, ULONG_T _signal");
      break;
   case SH_SLOT:
      fprintf(stream, ", WIDGET_PTR _widget, ULONG_T _signal, WIDGET_PTR _sender");
      break;
   case SH_PLAUS:
      fprintf(stream, ", WIDGET_PTR _widget, CONST_STRING_T _input");
      break;
   case SH_USER:
      fprintf(stream, ", WIDGET_PTR _widget, CONST_STRING_T _input");
      break;
   case SH_EVENT_FILTER:
      fprintf(stream, ", WIDGET_PTR _widget, TRANSIENT_OBJECT_PTR _object");
      break;
   }
   for (unsigned long i=0; i<func->Params(); i++) {
      if (i>0 || func_class != SH_FREE) {
         fprintf(stream, ", ");
      }
      if (i==0 && func_class != SH_FREE) {
         fprintf(stream, "\n\t");
      }
      PrintType(stream, func->ParamType(i));
      fprintf(stream, " %s", func->ParamName(i).c_str());
   }
   fprintf(stream, ");\n");
}

static void PrintFuncImpl(FILE * stream, cFuncDecl * func)
{
}

static void PrintTableEntry(FILE * stream, cFuncDecl * func_decl)
{
   STRING_T func_name = func_decl->_FuncName;
   int func_type = func_decl->_FuncClass;
   if (_Mode == CLASSIC) {
      fprintf(stream, "   {\"%s\", (FUNC_T)%s, %d},\n", func_name.c_str(),
	           func_name.c_str(), func_type);
   } else if (_Mode == MULTIPLE_TABS) {
      fprintf(stream, "   {\"%s\", (FUNC_T)%s, %d},\n",
              func_name.c_str(),
              func_name.c_str(),
              func_type);
   } else if (_Mode == AUTO_REGISTER) {
      fprintf(stream, "REGISTER_FUNCTION(%s, %d)\n",
              func_name.c_str(),
              func_type);
   }
}

static void GenerateFunctionCode(cContext * context, FILE * header_file, FILE * tab_file, const char * base_name)
{
   STRING_LIST_T funcs;
   context->FunctionNames(funcs);
   PrintPrototypeProlog(header_file, base_name);
   PrintFunctionTableProlog(tab_file);
   STRING_LIST_T::const_iterator i = funcs.cbegin();
   while (i != funcs.cend()) {
      cFuncDecl * func_decl = context->FuncDecl((*i).c_str());
      if (func_decl != NULL) {
         PrintFuncPrototype(header_file, func_decl);
         PrintTableEntry(tab_file, func_decl);
      }
      i++;
   }
   i = funcs.begin();
   while (i != funcs.end()) {
      cFuncDecl * func_decl = context->FuncDecl((*i).c_str());
      if (func_decl != NULL) {
      }
      i++;
   }
   PrintPrototypeEpilog(header_file, base_name);
   PrintFunctionTableEpilog(tab_file);
}

static void GenerateStringList(cContext * context)
{
   STRING_LIST_T var_names;
   context->VariableNames(var_names);
   STRING_LIST_T::const_iterator i = var_names.cbegin();
   while (i != var_names.cend()) {
      cVarDef * var_def = context->VarDef((*i).c_str());
      if (var_def != NULL) {
//         AddString(var_def->_Description.c_str());
         AddString(var_def->_Text.c_str());
         AddString(var_def->_Dim1Text.c_str());
         AddString(var_def->_Dim2Text.c_str());
         AddString(var_def->_Dim3Text.c_str());
         AddString(var_def->_Dim4Text.c_str());

         // search unit-text at variable definition
         cUnitDef* unit_def = var_def->get_UnitDef();
         if (unit_def != NULL) {
            for (int state=0; state<MAX_DIM_DEFINITIONS; state++) {
               STRING_T unit_text = "";
               unit_text = unit_def->UnitText(state);
               if (strcmp(unit_text.c_str(), "?") != 0) // found unit text
                  AddString(unit_text.c_str());
            }
         } else {
            STRING_T unit_text = "?";
            unit_text = cStringUtils::Trim(var_def->_UnitText.c_str(), '"');
            if (!unit_text.empty()) {
               AddString(unit_text.c_str());
            }
         }
      }
      i++;
   }
}

static STRING_T StrippedPath(CONST_STRING_T _path)
{
#ifdef __linux__
   return _path;
#endif
#define MAX_DIRS  0x10
   STRING_T full_path = cFileSystemUtils::FullPath(_path);
   CONST_STRING_T path = full_path.c_str();
   ULONG_T i = 0;
   char dir_name[0x200] = {0};
   STRING_T dir_names[MAX_DIRS];
   int depth = 0;
   int start_dir_name = 0;
   int end_dir_name = 0;
   int len = strlen(path);
   for (i=0; i<len + 1; i++) {
      char c = path[i];
      if (c == '\\' ||
          c == '/' ||
          c == 0) {
         end_dir_name = i;
         memset(dir_name, 0, sizeof(dir_name));
         memcpy(dir_name, &(path[start_dir_name]), end_dir_name - start_dir_name);
         dir_names[depth] = dir_name;
         depth++;
         start_dir_name = i + 1; 
      }
   }

   for (i=0; i<MAX_DIRS; i++) {
      if (dir_names[i].size() > 0) {
         if (strcmp(dir_names[i].c_str(), "..") == 0) {
            ULONG_T j = i - 1;
            while (j > 0) {
               if (dir_names[j].size() > 0) {
                  dir_names[j] = "";
                  dir_names[i] = "";
                  break;
               }
               j--;
            }
         } else if (strcmp(dir_names[i].c_str(), ".") == 0) {
            dir_names[i] = "";
         } else {
         }
      }
   }
   BOOL_T started = false;
   STRING_T stripped_path;
   for (i=0; i<MAX_DIRS; i++) {
      if (dir_names[i].size() > 0) {
         if (started) {
            stripped_path += "/";
         } else {
            started = true;
         }
         stripped_path += dir_names[i];
      }
   }
   return stripped_path;
}

static char _LineBuffer[0x2000] = {0};
static BOOL_T Generate(CONST_STRING_T base_dir, FILE * input, FILE * output)
{
   char * line_buf = fgets(_LineBuffer, sizeof(_LineBuffer), input);
   while (line_buf) {
      char white_space[0x100] = {0};
      char open_bracket[0x10] = {0};
      char close_bracket[0x10] = {0};
      char include_path_spec[0x500] = {0};
      int params = sscanf(line_buf, "#include%[ \t]%[<\"]%[^>\"]%[>\"]",
                          white_space,
                          open_bracket,
                          include_path_spec,
                          close_bracket);
      if (params == 4) {
         STRING_T include_path = cFileSystemUtils::AppendPath(base_dir, include_path_spec);
         include_path = StrippedPath(include_path.c_str());
         FILE * include_input = fopen(include_path.c_str(), "r");
         if (include_input != NULL) {
            fprintf(output, "// start include \"%s\"\n", include_path.c_str());
            STRING_T new_base_dir = cFileSystemUtils::DirName(include_path.c_str());
            BOOL_T include_generated = Generate(new_base_dir.c_str(), include_input, output);
            if (include_generated) {
               fprintf(output, "\n// end include \"%s\"\n", include_path.c_str());
            } else {
               fprintf(output, "\n// failed to include \"%s\"\n\n", include_path.c_str());
               return false;
            }
         } else {
            fprintf(output, "\n#error failed to open file \"%s\"\n\n", include_path.c_str());
            return false;
         }
      } else {
         fputs(line_buf, output);
      }
      line_buf = fgets(_LineBuffer, sizeof(_LineBuffer), input);
   }
   return true;
}

static BOOL_T GenerateComplete(CONST_STRING_T output_file_name, CONST_STRING_T input_file_name)
{
   STRING_T path = StrippedPath(input_file_name);
   STRING_T base_dir = cFileSystemUtils::DirName(path.c_str());
   base_dir = StrippedPath(base_dir.c_str());
   FILE * input = fopen(input_file_name, "r");
   if (input != NULL) {
      FILE * output = fopen(output_file_name, "w+");
      if (output != NULL) {
         Generate(base_dir.c_str(), input, output);
         fclose(output);
      }
      fclose(input);
   }
   return true;
}

int main(int argc, char* argv[])
{
   BOOL_T model_file_generated = false;
   fprintf(stderr, "\nShacira %d.%d.%d data model compiler version %s ...\n\n", (int)SHACIRA_MAJOR, (int)SHACIRA_MINOR, (int)SHACIRA_BUG_FIX, _Version);
   if (argc == 1) {
      Usage(stderr);
      return -1;
   }
   FILE * header_file = NULL;
   FILE * tab_file = NULL;
   FILE * impl_file = NULL;
   try {
      cResources(argc, argv);
      cResources::GetOption("verbose", _Verbose);
      cResources::GetOption("stdc", _StdC);
      cResources::GetOption("class", _MetaClass);
      if (_Verbose) {
         fprintf(stderr, "meta class %s\n", _MetaClass.c_str());
      }
      if (_MetaClass.empty()) {
         _Mode = CLASSIC;
      } else if (_MetaClass == "gui") {
         if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4) {
            _Mode = MULTIPLE_TABS;
         } else {
            _Mode = AUTO_REGISTER;
         }
      } else if (_MetaClass == "model") {
         if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4) {
            _Mode = MULTIPLE_TABS;
         } else {
            _Mode = AUTO_REGISTER;
         }
      } else {
         fprintf(stderr, "invalid meta class %s valid meta classes are gui or model\n", _MetaClass.c_str());
         return -1;
      }
      cResources::GetOption("mode", _Mode);
      if (_Mode != CLASSIC &&
          _Mode != MULTIPLE_TABS &&
          _Mode != AUTO_REGISTER) {
         fprintf(stderr, "invalid mode %d\n", (int)_Mode);
         return -1;
      } else if (_Mode == CLASSIC) {
         fprintf(stderr, "mode CLASSIC\n");
      } else if (_Mode == MULTIPLE_TABS) {
         fprintf(stderr, "mode MULTIPLE_TABLES\n");
      } else if (_Mode == AUTO_REGISTER) {
         if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4) {
            fprintf(stderr, "mode AUTO_REGISTER not supported by Shacira versions < 1.4\n");
            return -1;
         } else {
            fprintf(stderr, "mode AUTO_REGISTER\n");
         }
      }
      cResources::GetOption("input", _InputFile);
      if (_InputFile.size() == 0) {
         fprintf(stderr, "no input file specified\nusage:\n\tmdlc input = <file_name>\n");
         return -1;
      }
      if (!cFileSystemUtils::FileExists(_InputFile.c_str())) {
         fprintf(stderr, "input file %s not found\n", _InputFile.c_str());
         return -1;
      }
      fprintf(stderr, "\n");
      _OutputDir = _InputDir = cFileSystemUtils::DirName(cFileSystemUtils::FullPath(_InputFile.c_str()).c_str());
      _BaseName = cFileSystemUtils::BaseFileName(_InputFile.c_str());
      if (_Verbose) {
         fprintf(stderr, "input path %s\nbase name %s\n", _InputDir.c_str(), _BaseName.c_str());
      }
      cResources::GetOption("outputdir", _OutputDir);
      _HeaderFile = cFileSystemUtils::AppendPath(_OutputDir.c_str(), _BaseName.c_str());
      _HeaderFile += ".h";
      _TabFile = cFileSystemUtils::AppendPath(_OutputDir.c_str(), _BaseName.c_str());
      _TabFile += ".tab";
      _StringFile = cFileSystemUtils::AppendPath(_OutputDir.c_str(), _BaseName.c_str());
      _StringFile += ".txt";
      cResources::GetOption("header", _HeaderFile);
      cResources::GetOption("table", _TabFile);
      cResources::GetOption("strings", _StringFile);
      if (_Mode == MULTIPLE_TABS ||
          _Mode == AUTO_REGISTER) {
         _TabFile += ".cpp";
      }
      cResources::GetOption("model", _ModelFile);
      if (_ModelFile.size() > 0) {
         if (!GenerateComplete(_ModelFile.c_str(), _InputFile.c_str())) {
            fprintf(stderr, "development side includes failed\n");
            return -1;
         }
         _InputFile = _ModelFile;
         model_file_generated = true;
      } else {
         _ModelFile = _InputFile;
         model_file_generated = false;
      }
      _ModelFile = StrippedPath(_ModelFile.c_str());
      _InputFile = StrippedPath(_InputFile.c_str());
      _HeaderFile = StrippedPath(_HeaderFile.c_str());
      _TabFile = StrippedPath(_TabFile.c_str());
      _StringFile = StrippedPath(_StringFile.c_str());
      if (_Verbose) {
         fprintf(stderr, "input file %s\n", _InputFile.c_str());
         fprintf(stderr, "header file %s\n", _HeaderFile.c_str());
         fprintf(stderr, "table file %s\n", _TabFile.c_str());
         fprintf(stderr, "model file %s\n", _ModelFile.c_str());
         if (_ModelFile != _InputFile) {
	    fprintf(stderr, "string file %s\n\n", _StringFile.c_str());
         }
      }
      header_file = fopen(_HeaderFile.c_str(), "w");
      if (header_file == NULL) {
         fprintf(stderr, "failed to open header file %s\n", _HeaderFile.c_str());
         return -1;
      }
      tab_file = fopen(_TabFile.c_str(), "w");
      if (tab_file == NULL) {
         fprintf(stderr, "failed to open tab file %s\n", _TabFile.c_str());
         fclose(header_file);
         return -1;
      }

      cContext * context = new cContext;
      {
         // Delete model error file
         STRING_T modelFileErrName = _ModelFile + ".err";
         remove(modelFileErrName.c_str()); 

         cStyxParser parser;
         if (_Verbose) {
            fprintf(stderr, "begin model parsing on %s\n", _InputFile.c_str());
         }
         parser.set_IDEActive(true);
         parser.set_Steps(2);
         if (!parser.ParseDatabaseFromFile(context, _InputFile.c_str())) {
            fprintf(stderr, "errors occured parsing aborted on %s\n", _InputFile.c_str());
            fprintf(header_file, "\n\n#error model compilation failed: no code generated\n\n");
            fprintf(tab_file, "\n\n#error model compilation failed: no code generated\n\n");
            fclose(header_file);
            fclose(tab_file);

            if (model_file_generated) {
                rename(_ModelFile.c_str(), modelFileErrName.c_str());
            }
            return -1;
         };
         if (_Verbose) {
            fprintf(stderr, "end model parsing on %s\n", _InputFile.c_str());
         }
         fprintf(stderr, " \n");
         GenerateFunctionCode(context, header_file, tab_file, _BaseName.c_str());
         GenerateStringList(context);
      }
      fclose(header_file);
      fclose(tab_file);
      SaveStrings(_StringFile.c_str());
      if (_Verbose) {
         fprintf(stderr, "successfully generated >>\n%s\n%s\n%s\n",
                 _HeaderFile.c_str(),
                 _TabFile.c_str(),
                 _StringFile.c_str());
      }
      if (model_file_generated) {
         if (_Verbose) {
            fprintf(stderr, "%s\n", _ModelFile.c_str());
         }
      }
   } catch (cError & e) {
      fprintf(stderr, "%s\n", (const char*) e);
      return -1;
   } catch (...) {
      fprintf(stderr, "unhandled exception\n");
      return -1;
   }
   return 0;
}

