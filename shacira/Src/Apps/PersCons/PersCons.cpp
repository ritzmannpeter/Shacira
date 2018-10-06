
#include "FirstHeader.h"
#include "System/Sys/cFileSystemUtils.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/Console/cStandardConsole.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Console/cSocketConsole.h"
#include "System/Objects/cInfo.h"
#include "System/cError.h"
#include "System/Database/cContext.h"
#include "System/Database/cVarRef.h"
#include "System/Database/cVarDef.h"
#include "Control/LocalDatabase/cFileStorage.h"
#include "Control/LocalDatabase/cPersistentVariable.h"
#include "Language/cStyxParser.h"
#include "System/PLC/cActProcedure.h"

#ifdef _WIN32

// Ctrl + x handler
BOOL WINAPI CtrlHandler(DWORD dwCtrlType)
{
   switch (dwCtrlType) {
   case CTRL_C_EVENT:
      printf("CTRL+C\n");
      cResources::ShutDown();
      break;
   case CTRL_BREAK_EVENT:
      printf("CTRL+BREAK\n");
      break;
   case CTRL_CLOSE_EVENT:
      printf("CTRL+CLOSE\n");
      break;
   case CTRL_LOGOFF_EVENT:
      printf("CTRL+LOGOFF\n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      printf("CTRL+SHUTDOWN\n");
      cResources::ShutDown();
      break;
   }
   return true;
}

#endif

static cContext * _ActiveContext = NULL;
static cFileStorage * _ActiveStorage = NULL;

#define CHECK_CONTEXT \
   if (_ActiveContext == NULL) { \
      printf("no context active\n"); \
      return; \
   }


static void ListVariables()
{
   CHECK_CONTEXT
   STRING_LIST_T var_defs;
   _ActiveContext->VariableNames(var_defs);
   if (var_defs.size() > 0) {
      STRING_LIST_T::const_iterator i = var_defs.cbegin();
      while (i != var_defs.cend()) {
         STRING_T var_name = (*i);
         cVarDef * var_def = _ActiveContext->VarDef(var_name.c_str());
         if (var_def != NULL) {
            STRING_T description;
            if (var_def->_Description.size() > 0) {
               description = var_def->_Description;
            }
            UCHAR_T data_type = var_def->DataType();
            ULONG_T length = var_def->ElementSize();
            ULONG_T dims = 0, dim1 = 0, dim2 = 0, dim3 = 0, dim4 = 0;
            dims = var_def->Dims();
            switch (dims) {
            case 0:
               printf("%s: %s: %s\n", var_name.c_str(), var_def->TypeSpec().c_str(), description.c_str());
               break;
            case 1:
               dim1 = var_def->DimSize(0);
               printf("%s[%d]: %s: %s\n", var_name.c_str(), dim1, var_def->TypeSpec().c_str(), description.c_str());
               break;
            case 2:
               dim1 = var_def->DimSize(0);
               dim2 = var_def->DimSize(1);
               printf("%s[%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, var_def->TypeSpec().c_str(), description.c_str());
               break;
            case 3:
               dim1 = var_def->DimSize(0);
               dim2 = var_def->DimSize(1);
               dim3 = var_def->DimSize(2);
               printf("%s[%d][%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, dim3, var_def->TypeSpec().c_str(), description.c_str());
               break;
            case 4:
               dim1 = var_def->DimSize(0);
               dim2 = var_def->DimSize(1);
               dim3 = var_def->DimSize(2);
               dim4 = var_def->DimSize(3);
               printf("%s[%d][%d][%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, dim3, dim4, var_def->TypeSpec().c_str(), description.c_str());
               break;
            default:
               printf("? %s: %s: %s\n", var_name.c_str(), var_def->TypeSpec().c_str(), description.c_str());
            }
         }  
         i++;
      }
   } else {
      printf("no variables available\n");
   }
}

static void SetContext(const char * file_name)
{
   try {
      STRING_T file = cFileSystemUtils::FullPath(file_name);
      if (cFileSystemUtils::FileExists(file.c_str())) {
         if (_ActiveStorage == NULL) {
            _ActiveStorage = NULL;
         }
         _ActiveStorage = new cFileStorage(file.c_str(), true, 0);
         if (_ActiveStorage == NULL) {
            printf("failed to instantiate context %s\n", file.c_str());
         } else {
            _ActiveStorage->Initialize();
            _ActiveContext = _ActiveStorage->Parse();
            if (_ActiveContext == NULL) {
               printf("failed to parse %s\n", file.c_str());
            }
         }
      } else {
         printf("file %s not found\n", file.c_str());
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception setting context %s\n", file_name);
   }
}

static void SetVar(CONST_STRING_T var_spec, CONST_STRING_T value)
{
   CHECK_CONTEXT
   try {
      cVarRef * var_ref = _ActiveContext->VarRef(var_spec);
      if (var_ref == NULL) {
         printf("failed to resolve %s\n", var_spec);
      } else {
         var_ref->SetValue(value);
         LONG_T i1 = -1;
         LONG_T i2 = -1;
         LONG_T i3 = -1;
         LONG_T i4 = -1;
         var_ref->GetIndices(i1, i2, i3, i4);
         cVarDef * var_def = var_ref->VarDef();
         if (var_def != NULL) {
            STRING_T var_name = var_def->_VarName;
            int pos = var_def->GetPos(i1, i2, i3, i4);
            cVariable * variable = var_def->_Variable;
            cPersistentVariable * persistent_variable = dynamic_cast<cPersistentVariable*>(variable);
            if (persistent_variable != NULL) {
               BUF_T buf = persistent_variable->Buffer();
               int element_size = var_def->ElementSize();
               int offset = (pos * element_size);
               buf += offset;
               _ActiveStorage->Write(var_name.c_str(), pos, buf, element_size, 0);
               _ActiveStorage->Flush();
            }
         }
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception setting %s to %s\n", var_spec, value);
   }
}

static void GetVar(CONST_STRING_T var_spec)
{
   CHECK_CONTEXT
   try {
      cVarRef * var_ref = _ActiveContext->VarRef(var_spec);
      if (var_ref == NULL) {
         printf("failed to resolve %s\n", var_spec);
      } else {
         STRING_T value;
         var_ref->GetValue(value);
         printf("%s\n", value.c_str());
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception getting value %s\n", var_spec);
   }
}

static BOOL_T SetContextCmd(const char * line, char * file_name)
{
   int params = sscanf(line, "set %s", file_name);
   if (params == 1) {
      return true;
   } else {
      return false;
   }
}
   
static BOOL_T SetVarCmd(const char * line, char * var_ref, char * value)
{
   int params = sscanf(line, "%[^=]=%s", var_ref, value);
   if (params == 2) {
      return true;
   } else {
      return false;
   }
}
   
static BOOL_T GetVarCmd(const char * line, char * var_ref)
{
   int params = sscanf(line, "%s", var_ref);
   if (params == 1) {
      return true;
   } else {
      return false;
   }
}

static void ParseFile(cContext * context, CONST_STRING_T file)
{
   try {
      if (context == NULL) {
         printf("no context\n");
      }
      STRING_T path = cFileSystemUtils::FullPath(file);
      if (cFileSystemUtils::FileExists(path.c_str())) {
         cStyxParser parser;
         parser.ParseProgramFromFile(context, path.c_str(), true);
         context->CreateDynamic();
      } else {
         printf("file %s not found\n", path.c_str());
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception in Parse File\n");
   }
}

static int PersCons(int argc, char* argv[])
{
MAINFUNC_PROLOG("SysCons")
   char temp_buf[1024];
   int tests = 1000;
   int delay = 100;
   try {
      cResources resources(argc, argv);
		cSockets::Initialize();
		cBroker::Initialize();
      char path[0x200] = {0};
      char name[0x100] = {0};
      char persistence_file[0x100] = {0};
#ifdef _WIN32
      SetConsoleCtrlHandler(CtrlHandler, true);
#endif
      while (true) {
         memset(temp_buf, 0, sizeof(temp_buf));
         char context_name[128] = {0};
         char var_spec[128] = {0};
         char value[128] = {0};
         int tests = 0;
         const char * line = gets_s(temp_buf);
         if (_stricmp("?", line) == 0) {
            printf("available commands:\n");
            printf("   q: exit console\n");
            printf("   sc <file_name>: set context to file\n");
            printf("   lv list variables\n");
            printf("   <variable_name>: query variable value\n");
         } else if (_stricmp("q", line) == 0) {
            printf("exit console ...\n");
            break;
         } else if (_stricmp(line, "lv") == 0) {
            ListVariables();
         } else if (sscanf(line, "sc %s", context_name) == 1 &&
                    line[2] == ' ') {
            SetContext(context_name);
         } else {
            if (SetVarCmd(line, var_spec, value)) {
               SetVar(var_spec, value);
            } else if (GetVarCmd(line, var_spec)) {
               GetVar(var_spec);
            } else {
               if (line[0] != 0) {
                  printf("syntax error\n");
               }
            }
         }
      }
      return 0;
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      printf("unhandled exception in main thread\n");
      return -12;
   }
MAINFUNC_EPILOG
}

int main(int argc, char* argv[])
{
   return PersCons(argc, argv);
}
