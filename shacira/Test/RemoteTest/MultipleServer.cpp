
#include "FirstHeader.h"
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
#include "Control/CellProcess/cCellProcess.h"
#include "System/Database/cVarDef.h"
#include "Control/LocalDatabase/cLocalContext.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#include <vector>
using namespace std;

#if defined(_WIN32)

// Ctrl + x handler
BOOL WINAPI CtrlHandler(DWORD dwCtrlType)
{
   switch (dwCtrlType) {
   case CTRL_C_EVENT:
      InfoPrintf("CTRL+C\n");
      cResources::ShutDown();
      break;
   case CTRL_BREAK_EVENT:
      InfoPrintf("CTRL+BREAK\n");
      break;
   case CTRL_CLOSE_EVENT:
      InfoPrintf("CTRL+CLOSE\n");
      break;
   case CTRL_LOGOFF_EVENT:
      InfoPrintf("CTRL+LOGOFF\n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      InfoPrintf("CTRL+SHUTDOWN\n");
      cResources::ShutDown();
      break;
   }
   return true;
}

#endif

static vector<int> dimensionVector(int size1 = -1, int size2 = -1, int size3 = -1, int size4 = -1)
{
   vector<int> v;
   if (size4 > 0) {
      v.resize(4);
      v[0] = size1;
      v[1] = size2;
      v[2] = size3;
      v[3] = size4;
   } else if (size3 > 0) {
      v.resize(3);
      v[0] = size1;
      v[1] = size2;
      v[2] = size3;
   } else if (size2 > 0) {
      v.resize(2);
      v[0] = size1;
      v[1] = size2;
   } else if (size1 > 0) {
      v.resize(1);
      v[0] = size1;
   }
   return v;
}

static void addStructure(cVarDef * var_def, const vector<int> & dimensions)
{
   int dimCount = dimensions.size();
   int pos = 0;
   for (pos=0; pos<dimCount; pos++) {
      var_def->AddDim(pos, dimensions[pos]);
   }
}

static cVarDef * createVariable(cLocalContext * context, const char * name, int data_type, int length, int precision, unsigned long flags)
{
   cVarDef * var_def = NULL;
   var_def = new cVarDef(name, data_type, length, precision, false);
   var_def->_Context = context;
   var_def->_SystemFlags |= HOST_READ;
   var_def->_SystemFlags |= HOST_WRITE;
   return var_def;
}

static void addVariables(cLocalContext * context)
{
   cVarDef * var_def = NULL;
   var_def = createVariable(context, "testString", SH_STRING, 100, 0, HOST_READ|HOST_WRITE);
   context->AddVarDef(var_def->_VarName.c_str(), var_def);
   var_def = createVariable(context, "testFloat", SH_FLOAT, 0, 3, HOST_READ|HOST_WRITE);
   addStructure(var_def, dimensionVector(2, 2, 2, 2));
   context->AddVarDef(var_def->_VarName.c_str(), var_def);
   var_def = createVariable(context, "ActCntCyc", SH_LONG, 0, 0, HOST_READ|HOST_WRITE);
   context->AddVarDef(var_def->_VarName.c_str(), var_def);
}

static void setVariables(cLocalContext * local_context)
{
}

static void live(cLocalContext * localContext)
{
   static int count = 0;
   count++;
   static bool initialized = false;
   if (initialized) {
//      return;
   }
   initialized = true;
   cVariable * variable = localContext->Variable("testFloat");
   if (variable != NULL) {
      int i1 = 0;
      int i2 = 0;
      int i3 = 0;
      int i4 = 0;
      for (i1=0; i1<2; i1++) {
         for (i2=0; i2<2; i2++) {
            for (i3=0; i3<2; i3++) {
               for (i4=0; i4<2; i4++) {
                  float value = (float)((i1*1000) + (i2*100) + (i3*10) + i4 + count);
                  float v2 = 0;
                  variable->Set(value, i1, i2, i3, i4);
                  variable->Get(v2, i1, i2, i3, i4);
//                  printf("%f = %f\n", value, v2);
                  if (value != v2) {
                     int dummy = 0;
                  }
               }
            }
         }
      }
   }
   variable = localContext->Variable("ActCntCyc");
   LONG_T cycCount = 0;
   variable->Get(cycCount);
   cycCount++;
   variable->Set(cycCount);
   variable->Get(cycCount);
   int dummy = 0;
}

static void live(cCellProcess * process)
{
   ULONG_T filter = LOCAL_CONTEXTS;
   STRING_LIST_T contextNames;
   process->ContextNames(contextNames, filter);
   int contextCount = contextNames.size();
   STRING_LIST_T::const_iterator i = contextNames.begin();
   while (i != contextNames.end()) {
      string contextName = (*i);
      cContext * context = process->Context(contextName.c_str(), filter);
      cLocalContext * localContext = dynamic_cast<cLocalContext*>(context);
      if (localContext != NULL) {
         live(localContext);
      }
      i++;
   }
}

//#define MACHINE_COUNT   360 /// maximum without access violations
#define MACHINE_COUNT   1
   
int MultipleServer(int argc, char* argv[])
{
MAINFUNC_PROLOG("MultipleServer")
   try {
      int terminationCeiling = 0;
      int machineCount = MACHINE_COUNT;
      if (argc == 2) {
         int param = atoi(argv[1]);
         if (param > 0 && param < 360) {
            machineCount = param;
         }
      } else if (argc == 3) {
         int param = atoi(argv[1]);
         if (param > 0 && param < 360) {
            machineCount = param;
         }
         param = atoi(argv[2]);
         if (param > 10) {
            terminationCeiling = param;
         }
      }
      cResources resources(argc, argv);
		cSockets::Initialize();
		cBroker::Initialize();
      cCellProcess process(machineCount, "test_machine", addVariables, setVariables);
      process.set_Path(argv[0]);
      process.Start();
      cResources::RegisterProcess(&process);
#if defined(_WIN32)
      SetConsoleCtrlHandler(CtrlHandler, true);
#endif
      int count = 0;
      while (!process.Terminated()) {
         live(&process);
         cSystemUtils::Suspend(1000);
         if ((terminationCeiling > 0) && (count > terminationCeiling)) {
            exit(0);
         }
         count++;
      }
      return 0;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      ErrorPrintf("unhandled exception in main thread\n");
      return -12;
   }
MAINFUNC_EPILOG
}

int main(int argc, char* argv[])
{
   return MultipleServer(argc, argv);
}
