
#include "FirstHeader.h"
#include "cProcessWrapper.h"

#include "System/Process/cResources.h"
#include "System/Process/cSHClientProcess.h"
#include "System/Sys/cSockets.h"
#include "Orb/cBroker.h"
#include "System/Database/cContext.h"
#include "System/Database/cVarDef.h"
#include "System/Database/cVarRef.h"
#include "System/Database/cImage.h"
#include "Client/RemoteDatabase/cRemoteContext.h"
#include "Orb/cCorbaCellProxy.h"
#include "cAlloc.h"
#include "cImageConverter.h"
 
#define CHECK_CONTEXT \
   if (ContextIsNull()) { \
      return "no context active\n"; \
   }

int cProcessWrapper::_Argc = 0;
char ** cProcessWrapper::_Argv = NULL;
cProcessWrapper * cProcessWrapper::_ProcessWrapper = NULL;

cProcessWrapper::cProcessWrapper()
{
   _ActiveContext = NULL;
   try {
      cResources resources(_Argc, _Argv);
		cSockets::Initialize();
		cBroker::Initialize();
      int n = 0;
      char path[0x200] = {0};
      char name[0x100] = {0};
      char host[0x100] = {0};
      char prog_file[0x100] = {0};
      char control_program[0x100] = {0};
      char control_procedure[0x100] = {0};
      _Process = new cSHClientProcess;
      _Process->AddProxyReceiver(21001);
      _Process->AddProxyReceiver(21002);
      _Process->AddProxyReceiver(21003);
      _Process->AddProxyReceiver(21004);
      _Process->set_Path(_Argv[0]);
      _Process->Start();
      cResources::RegisterProcess(_Process);
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception in main thread\n");
   }
}

cProcessWrapper::~cProcessWrapper()
{
}

void cProcessWrapper::Start()
{
   if (_ProcessWrapper == NULL) {
      _ProcessWrapper = new cProcessWrapper;
      _ProcessWrapper->Start();
   }
}

void cProcessWrapper::Stop()
{
   if (_ProcessWrapper == NULL) {
      _ProcessWrapper->Start();
      delete _ProcessWrapper;
   }
}

bool cProcessWrapper::Eval(const char * text, STRING_T & value)
{
   char context_name[0x50] = {0};
   STRING_T var_spec;
   STRING_T var_value;
   value = "";
   if (_stricmp("help", text) == 0) {
      value += "available commands:\n";
      value += "   lc: list available contexts\n";
      value += "   ac: query active context name\n";
      value += "   lv: list available variables\n";
      value += "   sc <context_name>: set context\n";
      value += "   <variable_name>: query variable value\n";
      value += "   <variable_name> = <value>: set variable value\n";
      return true;
   }
   if (_stricmp("lc", text) == 0) {
      STRING_LIST_T context_names;
      _Process->ContextNames(context_names, REMOTE_CONTEXTS);
      if (context_names.size() > 0) {
         STRING_LIST_T::const_iterator i = context_names.begin();
         while (i != context_names.end()) {
            if (i != context_names.begin()) {
               value += ",";
            }
            value += (*i);
            i++;
         }
      } else {
         value += "no contexts available";
      }
      return true;
   }
   if (_stricmp(text, "ac") == 0) {
      STRING_T active_context = ActiveContext();
      value = active_context;
      return true;
   }
   if (_stricmp(text, "lv") == 0) {
      STRING_T var_list = ListVariables();
      value = var_list;
      return true;
   }
   if (sscanf(text, "sc %s", context_name) == 1 &&
              text[2] == ' ') {
      STRING_T result = SetContext(context_name);
      value = result;
      return true;
   }
   if (SetVarCmd(text, var_spec, var_value)) {
      STRING_T result = SetVar(var_spec.c_str(), var_value.c_str());
      value = result;
      return true;
   } else if (GetVarCmd(text, var_spec)) {
      STRING_T result = GetVar(var_spec.c_str());
      value = result;
      unsigned long memory_address = 0;
      int params = sscanf(value.c_str(), "memory'%x'", &memory_address);
      if (params == 1) {
         cVarRef * var_ref = _ActiveContext->VarRef(var_spec.c_str());
         if (var_ref != NULL) {
            int size = var_ref->ValueSize();
            char print_buf[0x50] = {0};
            SafePrintf(print_buf, sizeof(print_buf), "memory:%p:%d", memory_address, size); 
            value = print_buf;
         }
      }
      return true;
   } else {
      if (IsEmpty(text)) {
         return true;
      }
   }
   value += "failed to interprete ";
   value += text;
   return false;
}

bool cProcessWrapper::GetImage(const char * text, unsigned char * & buf, int & buf_size)
{
   CHECK_CONTEXT
   unsigned long memory_address = 0;
   int size = 0;
   int params = sscanf(text, "memory:%x:%d'", &memory_address, &size);
   if (params == 2) {
      cRemoteContext * remote_context = (cRemoteContext*)_ActiveContext;
      cCorbaCellProxy * proxy = (cCorbaCellProxy*)remote_context->Proxy();
      unsigned char * var_buf = (unsigned char *)cAlloc::Alloc(size);
      proxy->GetMemory(var_buf, (PTR_T)memory_address, size);
      cImage image(var_buf);
      int image_size = image.GetImageSize();
      BUF_T image_data = image.GetImageData();
      int width = image.GetXSize();
      int height = image.GetYSize();
      int pixel_size = 8;
      cImageConverter::ConvertToJpeg(pixel_size, width, height, image_data, buf, buf_size);
      cAlloc::Free(var_buf);
      Beep(50,50);
      return true;
   } else {
      cVarRef * var_ref = _ActiveContext->VarRef(text);
      if (var_ref != NULL) {
         if (var_ref->DataType() == SH_OBJECT) {
            cBinaryObject object;         
            var_ref->GetObject(object);
            unsigned char * buffer = object.Data();
            ULONG_T object_size = object.Size();
            buf = (unsigned char *)cAlloc::Alloc(object_size);
            memcpy(buf, buffer, object_size);
            buf_size = object_size;
            Beep(100,100);
            return true;
         } else {
            cBinaryObject object;         
            var_ref->GetObject(object);
            BUF_T buffer = object.Data();
            ULONG_T object_size = object.Size();
            if (object_size > 0) {
               cImage image(buffer);
               int image_size = image.GetImageSize();
               BUF_T image_data = image.GetImageData();
               int width = image.GetXSize();
               int height = image.GetYSize();
               int pixel_size = 8;
               cImageConverter::ConvertToJpeg(pixel_size, width, height, image_data, buf, buf_size);
               Beep(50,50);
               return true;
            } else {
               return false;
            }
         }
      } else {
         return false;
      }
   }
}

STRING_T cProcessWrapper::SetContext(const char * context_name)
{
   char buffer[0x100] = {0};
   STRING_T result;
   cContext * client_context = _ActiveContext;
   try {
      _ActiveContext = _Process->Context(context_name, REMOTE_CONTEXTS);
      if (_ActiveContext != NULL) {
         _ActiveContext->Connect();
         _ActiveContext->Create();
         _ActiveContextName = context_name;
         SafePrintf(buffer, sizeof(buffer), "context %s active\n", context_name);
         result = buffer;
      } else {
         SafePrintf(buffer, sizeof(buffer), "context %s not available\n", context_name);
         result = buffer;
         _ActiveContext = client_context;
      }
   } catch (cError & e) {
      result = (const char*)e;
   } catch (...) {
      SafePrintf(buffer, sizeof(buffer), "unhandled exception setting context %s\n", context_name);
      result = buffer;
   }
   return result;
}

STRING_T cProcessWrapper::ActiveContext()
{
   CHECK_CONTEXT
   return _ActiveContextName;
}

STRING_T cProcessWrapper::ListVariables()
{
   char buffer[0x500] = {0};
   STRING_T var_list;
   CHECK_CONTEXT
   STRING_LIST_T var_defs;
   _ActiveContext->VariableNames(var_defs);
   if (var_defs.size() > 0) {
      STRING_LIST_T::const_iterator i = var_defs.begin();
      while (i != var_defs.end()) {
         STRING_T var_name = (*i);
         cVarDef * var_def = _ActiveContext->VarDef(var_name.c_str());
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
            SafePrintf(buffer, sizeof(buffer), "%s: %s: %s\n", var_name.c_str(), var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         case 1:
            dim1 = var_def->DimSize(0);
            SafePrintf(buffer, sizeof(buffer), "%s[%d]: %s: %s\n", var_name.c_str(), dim1, var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         case 2:
            dim1 = var_def->DimSize(0);
            dim2 = var_def->DimSize(1);
            SafePrintf(buffer, sizeof(buffer), "%s[%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         case 3:
            dim1 = var_def->DimSize(0);
            dim2 = var_def->DimSize(1);
            dim3 = var_def->DimSize(2);
            SafePrintf(buffer, sizeof(buffer), "%s[%d][%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, dim3, var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         case 4:
            dim1 = var_def->DimSize(0);
            dim2 = var_def->DimSize(1);
            dim3 = var_def->DimSize(2);
            dim4 = var_def->DimSize(3);
            SafePrintf(buffer, sizeof(buffer), "%s[%d][%d][%d][%d]: %s: %s\n", var_name.c_str(), dim1, dim2, dim3, dim4, var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         default:
            SafePrintf(buffer, sizeof(buffer), "? %s: %s: %s\n", var_name.c_str(), var_def->TypeSpec().c_str(), description.c_str());
            var_list += buffer;
            break;
         }
         i++;
      }
   } else {
      var_list =  "no variables available\n";
   }
   return var_list;
}

BOOL_T cProcessWrapper::SetVarCmd(const char * line, STRING_T & var_spec, STRING_T & var_value)
{
   char var_ref[0x100] = {0};
   char value[0x200] = {0};
   if (line[strlen(line)-1] == '=') {
      int params = sscanf(line, "%[^=]=", var_ref);
      if (params == 1) {
         var_spec = var_ref;
         return true;
      } else {
         return false;
      }
   } else {
      int params = sscanf(line, "%[^=]=%[^'\n']", var_ref, value);
      if (params == 2) {
         var_spec = var_ref;
         var_value = value;
         return true;
      } else {
         return false;
      }
   }
}
   
BOOL_T cProcessWrapper::GetVarCmd(const char * line, STRING_T & var_spec)
{
   char var_ref[0x100] = {0};
   int params = sscanf(line, "%s", var_ref);
   if (params == 1) {
      var_spec = var_ref;
      return true;
   } else {
      return false;
   }
}

STRING_T cProcessWrapper::SetVar(const char * var_spec, const char * value)
{
   char buffer[0x200] = {0};
   STRING_T result;
   CHECK_CONTEXT
   try {
      cVarRef * var_ref = _ActiveContext->VarRef(var_spec);
      if (var_ref == NULL) {
         printf("failed to resolve %s\n", var_spec);
      } else {
         var_ref->SetValue(value);
      }
   } catch (cError & e) {
      result = (const char*)e;
   } catch (...) {
      SafePrintf(buffer, sizeof(buffer), "unhandled exception setting %s to %s\n", var_spec, value);
      result = buffer;
   }
   return result;
}

STRING_T cProcessWrapper::GetVar(const char * var_spec)
{
   char buffer[0x200] = {0};
   STRING_T result;
   CHECK_CONTEXT
   try {
      cVarRef * var_ref = _ActiveContext->VarRef(var_spec);
      if (var_ref == NULL) {
         SafePrintf(buffer, sizeof(buffer), "failed to resolve %s\n", var_spec);
         result = buffer;
      } else {
         STRING_T value;
         var_ref->GetValue(value);
         result = value.c_str();
      }
   } catch (cError & e) {
      result = (const char*)e;
   } catch (...) {
      SafePrintf(buffer, sizeof(buffer), "unhandled exception getting value %s\n", var_spec);
      result = buffer;
   }
   return result;
}

BOOL_T cProcessWrapper::IsEmpty(const char * text)
{
   int len = strlen(text);
   int i = 0;
   for (i=0; i<len; i++) {
      char c = text[i];
      if (c == ' ' ||
          c == 0x0d ||
          c == 0x0a ||
          c == 0) {
      } else {
         return false;
      }
   }
   return true;
}

BOOL_T cProcessWrapper::ContextIsNull()
{
   if (_ActiveContext == NULL) {
      return true;
   } else {
      return false;
   }
}


#ifdef lassma

#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Process/cSHClientProcess.h"
#include "System/Comm/cProxyReceiver.h"
#include "System/Comm/cProxyService.h"
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
#include "System/NameSpace/cNameSpace.h"
#include "System/NameSpace/cNameSpaceNode.h"
#include "System/NameSpace/cNameSpaceIterator.h"
#include <direct.h>
#include <math.h>
#include "Language/cStyxParser.h"
#include "System/PLC/cActProcedure.h"

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

#define WAIT_FOR_OBJECT    5000
static cContext * _ActiveContext = NULL;
static cSHClientProcess * _Process = NULL;
static STRING_T _ContextName;
static cNameSpaceIterator _NameSpaceIterator;

#define CHECK_CONTEXT \
   if (_ActiveContext == NULL) { \
      printf("no context active\n"); \
      return; \
   }

static bool IsEmpty(const char * text)
{
   int len = strlen(text);
   int i = 0;
   for (i=0; i<len; i++) {
      char c = text[i];
      if (c == ' ' ||
          c == 0x0d ||
          c == 0x0a ||
          c == 0) {
      } else {
         return false;
      }
   }
   return true;
}

static void ListContexts()
{
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
}

static void ListVariables()
{
   CHECK_CONTEXT
   STRING_LIST_T var_defs;
   _ActiveContext->VariableNames(var_defs);
   if (var_defs.size() > 0) {
      STRING_LIST_T::const_iterator i = var_defs.begin();
      while (i != var_defs.end()) {
         STRING_T var_name = (*i);
         cVarDef * var_def = _ActiveContext->VarDef(var_name.c_str());
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

static void PrintNameSpace()
{
   cNameSpace * name_space = _Process->NameSpace();
   if (name_space != NULL) {
      STRING_LIST_T names;
      _NameSpaceIterator.Names(names);
      STRING_LIST_T::const_iterator i = names.begin();
      while (i != names.end()) {
         STRING_T name = (*i);
         printf("%s\n", name.c_str());
         i++;
      }
   } else {
      printf("process has no name space\n");
   }
}

static void ChangeDirectory(CONST_STRING_T path)
{
   cNameSpace * name_space = _Process->NameSpace();
   if (name_space != NULL) {
      _NameSpaceIterator = cNameSpaceIterator(name_space, path);
      if (_NameSpaceIterator.SetPath(path)) {
         printf("okay\n");
      } else {
         printf("failed\n");
      }
      printf("%s>", _NameSpaceIterator.Path().c_str());
   }
}

static void Down(CONST_STRING_T name)
{
   cNameSpace * name_space = _Process->NameSpace();
   if (name_space != NULL) {
      if (_NameSpaceIterator.Down(name)) {
         _NameSpaceIterator.Path() = _NameSpaceIterator.Path();
         printf("okay\n");
      } else {
         printf("failed\n");
      }
      printf("%s>", _NameSpaceIterator.Path().c_str());
   }
}

static void Up()
{
   cNameSpace * name_space = _Process->NameSpace();
   if (name_space != NULL) {
      if (_NameSpaceIterator.Up()) {
         _NameSpaceIterator.Path() = _NameSpaceIterator.Path();
         printf("okay\n");
      } else {
         printf("failed\n");
      }
      printf("%s>", _NameSpaceIterator.Path().c_str());
   }
}

static void ActiveContext()
{
   CHECK_CONTEXT
   printf("%s\n", _ContextName);
}

static void SetContext(const char * context_name)
{
   cContext * client_context = _ActiveContext;
   try {
      printf("searching for context %s ..\n", context_name);
      _ActiveContext = _Process->Context(context_name, REMOTE_CONTEXTS);
      if (_ActiveContext != NULL) {
         _ActiveContext->Connect();
         _ActiveContext->Create();
         printf("context %s active\n", context_name);
         _ContextName = context_name;
      } else {
         printf("context %s not available\n", context_name);
         _ActiveContext = client_context;
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception setting context %s\n", context_name);
   }
}

static void ConnectToHost(const char * host)
{
   cProxyService service(_Process);
   int error = 0;
   SERVICE_COMMAND_T response = {0};
   BOOL_T success = service.Request(host, SI_PROXY, error,
                                    &response, sizeof(response));
   if (error == 0) {
      printf("service: %s\n", response.service_name);
      printf("version: %d.%d.%d\n", response.sh_major, response.sh_minor, response.sh_bug_fix);
      printf("proxy: %s\n", response.service);
      cProxy * proxy = service.CreateProxy(response.service);
      if (proxy != NULL) {
         _Process->NewProxy(proxy);
      } else {
         printf("failed to create proxy\n");
      }
   } else {
      printf("failed to contact service: %d\n", error);
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
   if (line[strlen(line)-1] == '=') {
      int params = sscanf(line, "%[^=]=", var_ref);
      if (params == 1) {
         return true;
      } else {
         return false;
      }
   } else {
      int params = sscanf(line, "%[^=]=%[^'\n']", var_ref, value);
      if (params == 2) {
         return true;
      } else {
         return false;
      }
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
      int n = 0;
      char path[0x200] = {0};
      char name[0x100] = {0};
      char host[0x100] = {0};
      char prog_file[0x100] = {0};
      char control_program[0x100] = {0};
      char control_procedure[0x100] = {0};
      _Process = new cSHClientProcess;
      _Process->AddProxyReceiver(21001);
      _Process->AddProxyReceiver(21002);
      _Process->AddProxyReceiver(21003);
      _Process->AddProxyReceiver(21004);
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
            ParseFile(_ActiveContext, prog_file);
         } else if (sscanf(line, "ep %s", control_procedure) == 1) {
            ExecuteProcedure(_ActiveContext, control_procedure);
         } else if (_stricmp(line, "lc") == 0) {
            ListContexts();
         } else if (_stricmp(line, "ac") == 0) {
            ActiveContext();
         } else if (_stricmp(line, "lv") == 0) {
            ListVariables();
         } else if (_stricmp(line, "ns") == 0) {
            PrintNameSpace();
         } else if (sscanf(line, "sc %s", context_name) == 1 &&
                    line[2] == ' ') {
            SetContext(context_name);
         } else if (sscanf(line, "cd %s", path) == 1 &&
                    line[2] == ' ') {
            ChangeDirectory(path);
         } else if (_stricmp(line, "up") == 0) {
            Up();
         } else if (sscanf(line, "down %s", name) == 1 &&
                    line[4] == ' ') {
            Down(name);
         } else if (sscanf(line, "ah %s %d", host, &n) == 2) {
            int i = 0;
            for (i=0; i<n; i++) {
               ConnectToHost(host);
            }
         } else if (sscanf(line, "ah %s", host) == 1) {
            ConnectToHost(host);
         } else {
            if (SetVarCmd(line, var_spec, value)) {
               SetVar(var_spec, value);
            } else if (GetVarCmd(line, var_spec)) {
               GetVar(var_spec);
            } else {
               if (!IsEmpty(line)) {
                  printf("syntax error\n");
               }
            }
         }
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
