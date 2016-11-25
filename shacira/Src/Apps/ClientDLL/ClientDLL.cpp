
#include "FirstHeader.h"
#include "ClientDLL.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Process/cSHProcess.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/Console/cStandardConsole.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Console/cSocketConsole.h"
#include "System/Objects/cInfo.h"
#include "System/cError.h"
#include "Control/CellProcess/cCellProcess.h"
#include "System/Database/cContext.h"
#include "System/Database/cVarRef.h"
#include "Client/RemoteDatabase/cRemoteContext.h"
#include "System/Database/FuncSpecs.h"
#include "System/Database/cVarDef.h"
#include "System/Database/cVariable.h"
#include <direct.h>
#include <math.h>
#include "Language/cStyxParser.h"
#include "System/PLC/cActProcedure.h"


static cSHProcess * _Process = NULL;

#define MAX_HANDLES        512
#define ERROR_STRING_LEN   512
#define CONTEXT_NAME_LEN   512
static char _ErrorString[ERROR_STRING_LEN] = {0};

typedef struct client_data 
{
   CLIENT_HANDLE handle;
   cContext * context;
   char context_name[CONTEXT_NAME_LEN];
   char error_string[ERROR_STRING_LEN];
}  CLIENT_DATA_T;

static CLIENT_DATA_T * _ClientData = NULL;

static CLIENT_DATA_T * ClientData(CLIENT_HANDLE hnd)
{
   if (_ClientData == NULL) {
      return NULL;
   }
   if (hnd == INVALID_CLIENT_HANDLE ||
       hnd > MAX_HANDLES) {
      return NULL;
   } else {
      CLIENT_DATA_T * client_data = &(_ClientData[hnd]);
      if (client_data->handle == hnd) {
         return client_data;
      } else {
         return NULL;
      }
   }
}

static void ResetClientData(CLIENT_HANDLE hnd)
{
   CLIENT_DATA_T * client_data = ClientData(hnd);
   if (client_data != NULL) {
      if (client_data->handle == hnd) {
         memset(client_data, 0, sizeof(CLIENT_DATA_T));
      }
   }
}

static CLIENT_HANDLE AllocClientData()
{
   if (_ClientData == NULL) {
      return INVALID_CLIENT_HANDLE;
   } else {
      for (ULONG_T i=INVALID_CLIENT_HANDLE+1; i<= MAX_HANDLES; i++) {
         CLIENT_DATA_T * client_data = &(_ClientData[i]);
         if (client_data->handle == 0) {
            client_data->handle = i;
            return i;
         }
      }
      return INVALID_CLIENT_HANDLE;
   }
}


static void ResetError(CLIENT_HANDLE hnd)
{
   char * str_ptr = NULL;
   if (hnd == INVALID_CLIENT_HANDLE) {
      str_ptr = _ErrorString;
   } else {
      CLIENT_DATA_T * client_data = ClientData(hnd);
      if (client_data != NULL) {
         str_ptr = client_data->error_string;
      }
   }
   if (str_ptr != NULL) {
      memset(str_ptr, 0, ERROR_STRING_LEN);
   }
}

static void SetError(CLIENT_HANDLE hnd, cError & e)
{
   char * str_ptr = NULL;
   if (hnd == INVALID_CLIENT_HANDLE) {
      str_ptr = _ErrorString;
   } else {
      CLIENT_DATA_T * client_data = ClientData(hnd);
      if (client_data != NULL) {
         str_ptr = client_data->error_string;
      }
   }
   if (str_ptr != NULL) {
      STRING_T msg = (const char *)e;
      ULONG_T size = _MIN_(msg.size(), sizeof(_ErrorString) - 1);
      memcpy(str_ptr, msg.c_str(), size);
   }
}

static void SetError(CLIENT_HANDLE hnd, const char * msg)
{
   char * str_ptr = NULL;
   if (hnd == INVALID_CLIENT_HANDLE) {
      str_ptr = _ErrorString;
   } else {
      CLIENT_DATA_T * client_data = ClientData(hnd);
      if (client_data != NULL) {
         str_ptr = client_data->error_string;
      }
   }
   if (str_ptr != NULL) {
      ULONG_T size = _MIN_(strlen(msg), sizeof(_ErrorString) - 1);
      memcpy(str_ptr, msg, size);
   }
}

static void CopyValue(char * dst, ULONG_T dst_size, const char * src, ULONG_T src_size)
{
   ULONG_T size = _MIN_(src_size, dst_size);
   memcpy(dst, src, size);
}


#define DEFAULT_ROOT_NAME     "ClientProcess"

static long Init(const char * root_name)
{
   if (_Process != NULL) {
      SetError(INVALID_CLIENT_HANDLE, "Die Client Infrastruktur ist schon initialisiert");
      return ERR_CCS_CLIENT_INFRASTRUCTURE_ALREADY_INITIALIZED;
   }
   if (root_name == NULL) {
      root_name = DEFAULT_ROOT_NAME;
   }
   try {
      cResources resources(0, NULL);
		cSockets::Initialize();
		cBroker::Initialize();
      cConfiguration * config = NULL;
      try {
         STRING_T config_file = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                             cConfiguration::DefaultConfigFile());
         config = new cConfiguration(config_file.c_str());
      } catch (cError & e) {
         SetError(INVALID_CLIENT_HANDLE, e);
         return ERR_LOADING_CONFIGURATION;
      }
      cConfigurationObject * process_obj = config->Object(root_name);
      if (process_obj != NULL) {
         char prog_file[512] = {0};
         char control_program[512] = {0};
         char control_procedure[512] = {0};
         _Process = new cSHProcess(process_obj);
         _Process->set_Path("");
		   _Process->Start();
         cResources::RegisterProcess(_Process);
      } else {
         char msg[512] = {0};
         SafePrintf(msg, sizeof(msg), "Objekt %s nicht in der Konfiguration gefunden", root_name);
         SetError(INVALID_CLIENT_HANDLE, msg);
         return ERR_ROOT_NAME_NOT_FOUND;
      }
      _ClientData = (CLIENT_DATA_T*)cSystemUtils::Alloc(sizeof(CLIENT_DATA_T) * (MAX_HANDLES+1));
      return 0;
   } catch (cError & e) {
      SetError(INVALID_CLIENT_HANDLE, e);
      return ERR_INITIALIZING_CCS_CLIENT_INFRASTRUCTURE;
   } catch (...) {
      SetError(INVALID_CLIENT_HANDLE, "Unbekannte Ausnahme beim Initialisieren der Client Infrastruktur");
      return ERR_INITIALIZING_CCS_CLIENT_INFRASTRUCTURE;
   }
}

static void Exit()
{
	if (_Process != NULL) {
		_Process->Stop();
	}
	DELETE_OBJECT(cSHProcess, _Process)
}

static CLIENT_HANDLE Connect(const char * name)
{
   CLIENT_HANDLE hnd = AllocClientData();
   if (hnd != INVALID_CLIENT_HANDLE) {
      CLIENT_DATA_T * client_data = ClientData(hnd);
      if (client_data != NULL) {
         cContext * context = NULL;
         try {
            //LONG_T retries = 7;								//Zeit verkürztz bis Vebindungsaufbau abbrechen
            LONG_T retries = 1;
            while (context == NULL && retries-- > 0) {
               context = _Process->Context(name, REMOTE_CONTEXTS);
               //cSystemUtils::Suspend(1000);
               cSystemUtils::Suspend(100);
            }
         } catch (cError & e) {
            ResetClientData(hnd);
            SetError(INVALID_CLIENT_HANDLE, e);
            return INVALID_CLIENT_HANDLE;
         } catch (...) {
            ResetClientData(hnd);
            SetError(INVALID_CLIENT_HANDLE, "Unbekannte Ausnahme beim Suchen des Kontexts");
            return INVALID_CLIENT_HANDLE;
         }
         if (context == NULL) {
            ResetClientData(hnd);
            STRING_LIST_T context_names;
            _Process->ContextNames(context_names, REMOTE_CONTEXTS);
            if (context_names.size() > 0) {
               STRING_LIST_T::const_iterator i = context_names.begin();
               while (i != context_names.end()) {
                  if (i != context_names.begin()) printf(", ");
                  printf("%s", (*i).c_str());
                  i++;
               }
               printf("\n");
            } else {
               printf("no contexts available\n");
            }
            
            char msg[512] = {0};
            SafePrintf(msg, sizeof(msg), "Kontext %s ist nicht vorhanden", name);
            SetError(INVALID_CLIENT_HANDLE, msg);
            return INVALID_CLIENT_HANDLE;
         }
         try {
            context->Connect();
            context->Create();
         } catch (cError & e) {
            ResetClientData(hnd);
            SetError(INVALID_CLIENT_HANDLE, e);
            return INVALID_CLIENT_HANDLE;
         } catch (...) {
            ResetClientData(hnd);
            SetError(INVALID_CLIENT_HANDLE, "Unbekannte Ausnahme beim Verbinden des Kontexts");
            return INVALID_CLIENT_HANDLE;
         }
         client_data->context = context;
         memcpy(client_data->context_name, name, _MIN_(CONTEXT_NAME_LEN, strlen(name)));
         return hnd;
      }
   }
   SetError(INVALID_CLIENT_HANDLE, "Keine weiteren handles verfügbar");
   return INVALID_CLIENT_HANDLE;
}

static long Release(CLIENT_HANDLE hnd)
{
   return 0;
}

static long GetVarRef(CLIENT_HANDLE hnd, const char * var_spec, char * buf, unsigned long buf_size)
{
   return 0;
}

static long SetVarRef(CLIENT_HANDLE hnd, const char * var_spec, const char * buf, unsigned long buf_len)
{
   return 0;
}

static long GetVariable(CLIENT_HANDLE hnd, const char * var_name,
                        unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                        char * buf, unsigned long buf_size)
{
   ResetError(hnd);
   CLIENT_DATA_T * client_data = ClientData(hnd);
   if (client_data == NULL) {
      char msg[512] = {0};
      SafePrintf(msg, sizeof(msg), "Ungültiges Handle %d", hnd);
      return ERR_INVALID_HANDLE;
   } else {
      try {
         STRING_T _value;
         cVariable * variable = client_data->context->Variable(var_name);
         if (variable == NULL) {
            char msg[512] = {0};
            SafePrintf(msg, sizeof(msg), "Variable %s ist unbekannt", var_name);
            SetError(hnd, msg);
         } else {
            variable->Get(_value, i1, i2, i3, i4);
            CopyValue(buf, buf_size, _value.c_str(), _value.size());
            return 0;
         }
      } catch (cError & e) {
         SetError(hnd, e);
      } catch (...) {
         char msg[512] = {0};
         SafePrintf(msg, sizeof(msg), "Unbekannte Ausnahme beim Lesen der Variable %s", var_name);
         SetError(hnd, msg);
      }
   }
   return ERR_GET_VARIABLE;
}

static long SetVariable(CLIENT_HANDLE hnd, const char * var_name,
                        unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                        const char * buf, unsigned long buf_len)
{
   ResetError(hnd);
   CLIENT_DATA_T * client_data = ClientData(hnd);
   if (client_data == NULL) {
      char msg[512] = {0};
      SafePrintf(msg, sizeof(msg), "Ungültiges Handle %d", hnd);
      return ERR_INVALID_HANDLE;
   } else {
      try {
         cVariable * variable = client_data->context->Variable(var_name);
         if (variable == NULL) {
            char msg[512] = {0};
            SafePrintf(msg, sizeof(msg), "Variable %s ist unbekannt", var_name);
            SetError(hnd, msg);
         } else {
            variable->Set(buf, i1, i2, i3, i4);
            return 0;
         }
      } catch (cError & e) {
         SetError(hnd, e);
      } catch (...) {
         char msg[512] = {0};
         SafePrintf(msg, sizeof(msg), "Unbekannte Ausnahme beim Schreiben der Variable %s", var_name);
         SetError(hnd, msg);
      }
   }
   return ERR_SET_VARIABLE;
}

#ifdef __cplusplus
extern "C" {
#endif

long __declspec(dllexport) __stdcall CLIENT_Init(const char * root_name)
{
   return Init(root_name);
}

void __declspec(dllexport) __stdcall CLIENT_Exit()
{
	Exit();
}

CLIENT_HANDLE __declspec(dllexport) __stdcall CLIENT_Connect(const char * name)
{
   return Connect(name);
}

long __declspec(dllexport) __stdcall CLIENT_Release(CLIENT_HANDLE hnd)
{
   return 0;
}

long __declspec(dllexport) __stdcall CLIENT_GetVarRef(CLIENT_HANDLE hnd, const char * var_spec, char * buf, unsigned long buf_size)
{
   return 0;
}

long __declspec(dllexport) __stdcall CLIENT_SetVarRef(CLIENT_HANDLE hnd, const char * var_spec, const char * buf, unsigned long buf_len)
{
   return 0;
}

long __declspec(dllexport) __stdcall CLIENT_GetVariable(CLIENT_HANDLE hnd, const char * var_name,
                                       unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                                       char * buf, unsigned long buf_size)
{
   return GetVariable(hnd, var_name, i1, i2, i3, i4, buf, buf_size);
}

long __declspec(dllexport) __stdcall CLIENT_SetVariable(CLIENT_HANDLE hnd, const char * var_name,
                                       unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                                       const char * buf, unsigned long buf_len)
{
   return SetVariable(hnd, var_name, i1, i2, i3, i4, buf, buf_len);
}

void __declspec(dllexport) __stdcall CLIENT_GetErrorString(CLIENT_HANDLE hnd, char * buf, unsigned long buf_size)
{
   char * str_ptr = NULL;
   if (hnd == INVALID_CLIENT_HANDLE) {
      str_ptr = _ErrorString;
   } else {
      CLIENT_DATA_T * client_data = ClientData(hnd);
      if (client_data != NULL) {
         str_ptr = client_data->error_string;
      }
   }
   if (str_ptr != NULL) {
      ULONG_T size = _MIN_(buf_size, strlen(str_ptr));
      memcpy(buf, str_ptr, size);
   }
}


#ifdef __cplusplus
}
#endif


#ifdef nur_zur_doku

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

cContext * _ClientContext = NULL;
cSHProcess * _Process = NULL;
STRING_T _ContextName;

#define CHECK_CONTEXT \
   if (_ClientContext == NULL) { \
      printf("no context active\n"); \
      return; \
   }


static void ListContexts()
{
   STRING_LIST_T context_names;
   _Process->ContextNames(context_names);
   if (context_names.size() > 0) {
      STRING_LIST_T::const_iterator i = context_names.begin();
      while (i != context_names.end()) {
         if (i != context_names.begin()) printf(", ");
         printf("%s", (*i).c_str());
         i++;
      }
      printf("\n");
   } else {
      printf("no contexts available\n");
   }
}

static void ListVariables()
{
   CHECK_CONTEXT
   STRING_LIST_T var_defs;
   _ClientContext->VariableNames(var_defs);
   if (var_defs.size() > 0) {
      STRING_LIST_T::const_iterator i = var_defs.begin();
      while (i != var_defs.end()) {
         STRING_T var_name = (*i);
         cVarDef * var_def = _ClientContext->VarDef(var_name.c_str());
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
         i++;
      }
   } else {
      printf("no variables available\n");
   }
}

static void ActiveContext()
{
   CHECK_CONTEXT
   printf("%s\n", _ContextName);
}

static void SetContext(const char * context_name)
{
   cContext * client_context = _ClientContext;
   try {
      printf("searching for context %s ..\n", context_name);
      _ClientContext = _Process->Context(context_name);
      if (_ClientContext != NULL) {
         _ClientContext->Connect();
         _ClientContext->Create();
         printf("context %s active\n", context_name);
         _ContextName = context_name;
      } else {
         printf("context %s not available\n", context_name);
         _ClientContext = client_context;
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception setting context %s\n", context_name);
   }
}

static void SetVar(CONST_STRING_T var_spec, CONST_STRING_T value)
{
   CHECK_CONTEXT
   try {
      cVarRef * var_ref = _ClientContext->VarRef(var_spec);
      if (var_ref == NULL) {
         printf("failed to resolve %s\n", var_spec);
      } else {
         var_ref->SetValue(value);
         delete var_ref;
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
      cVarRef * var_ref = _ClientContext->VarRef(var_spec);
      if (var_ref == NULL) {
         printf("failed to resolve %s\n", var_spec);
      } else {
         STRING_T value;
         var_ref->GetValue(value);
         printf("%s\n", value.c_str());
         delete var_ref;
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception getting value %s\n", var_spec);
   }
}

static BOOL_T SetContextCmd(const char * line, char * context_name)
{
   int params = sscanf(line, "set %s", context_name);
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

static void ExecuteProcedure(cContext * context, CONST_STRING_T proc_name)
{
   try {
      if (context == NULL) {
         printf("no context\n");
      }
      cControlProcedure * proc = context->Procedure(proc_name);
      if (proc == NULL) {
         printf("no definition for procedure %s\n", proc_name);
      } else {
         cActProcedure act_proc(context, proc, NULL);
         act_proc.Execute();
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception in Execute Procedure\n");
   }
}

   
static int SysCons(int argc, char* argv[])
{
MAINFUNC_PROLOG("SysCons")
   char temp_buf[1024];
   int tests = 1000;
   int delay = 100;
   try {
      cResources resources(argc, argv);
		cSockets::Initialize();
		cBroker::Initialize();
      cConfiguration * config = NULL;
      try {
         STRING_T config_file = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                            cConfiguration::DefaultConfigFile());
         config = new cConfiguration(config_file.c_str());
      } catch (cError & e) {
         printf("%s\n", (const char *)e);
         return -9;
      }
      STRING_T root_name = "ClientProcess";
//      cResources::GetOption("RootName", root_name);
      cConfigurationObject * process_obj = config->Object(root_name.c_str());
      if (process_obj != NULL) {
         char prog_file[512] = {0};
         char control_program[512] = {0};
         char control_procedure[512] = {0};
         _Process = new cSHProcess(process_obj);
         _Process->set_Path(argv[0]);
		   _Process->Start();
         cResources::RegisterProcess(_Process);
         SetConsoleCtrlHandler(CtrlHandler, true);
         while (!_Process->Terminated()) {
            memset(temp_buf, 0, sizeof(temp_buf));
            char context_name[128] = {0};
            char var_spec[128] = {0};
            char value[128] = {0};
            int tests = 0;
            const char * line = gets(temp_buf);
            if (_stricmp("?", line) == 0) {
               printf("available commands:\n");
               printf("   q: exit console\n");
               printf("   lc: list available contexts\n");
               printf("   ac: query active context name\n");
               printf("   lv: list available variables\n");
               printf("   sc <context_name>: set context\n");
               printf("   <variable_name>: query variable value\n");
               printf("   <variable_name> = <value>: set variable value\n");
               printf("   lp <program_file_name>: load program\n");
               printf("   ep <procedure_name>: execute procedure\n");
            } else if (_stricmp("q", line) == 0) {
               printf("exit console ...\n");
               break;
            } else if (sscanf(line, "lp %s", prog_file) == 1) {
               ParseFile(_ClientContext, prog_file);
            } else if (sscanf(line, "ep %s", control_procedure) == 1) {
               ExecuteProcedure(_ClientContext, control_procedure);
            } else if (_stricmp(line, "lc") == 0) {
               ListContexts();
            } else if (_stricmp(line, "ac") == 0) {
               ActiveContext();
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
                  printf("syntax error\n");
               }
            }
         }
      } else {
         printf("Root object %s not found\n", root_name.c_str());
      }
      DELETE_OBJECT(cSHProcess, _Process)
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
   return SysCons(argc, argv);
}

#endif


