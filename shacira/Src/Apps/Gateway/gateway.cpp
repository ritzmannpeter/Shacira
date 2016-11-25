
#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Process/cSHProcess.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/cError.h"
#include "System/Database/cContext.h"
#include "System/Database/cVarRef.h"
#include "System/Database/cVarDef.h"
#include "System/ClientServer/cServer.h"

typedef std::map<STRING_T,cVarRef*> VAR_REF_MAP_T;

class cContextCache
{
public:
   cContextCache(cContext * context);
   virtual ~cContextCache();
   cContext * Context();
   cVarRef * VarRef(CONST_STRING_T var_spec);
private:
   cContext * _Context;
   VAR_REF_MAP_T _VarRefs;
};

cContextCache::cContextCache(cContext * context)
   : _Context(context)
{
}

cContextCache::~cContextCache()
{
}

cVarRef * cContextCache::VarRef(CONST_STRING_T var_spec)
{
   cVarRef * var_ref = NULL;
   VAR_REF_MAP_T::const_iterator i = _VarRefs.find(var_spec);
   if (i == _VarRefs.end()) {
      try {
         var_ref = _Context->VarRef(var_spec);
         if (var_ref != NULL) {
            _VarRefs[var_spec] = var_ref;
         }
      } catch (cError & e) {
         printf("%s resolving var ref %s on context %s\n", (const char*)e,
                var_spec, _Context->get_Name().c_str());
      } catch (...) {
         printf("unhandled exception resolving var ref %s on context %s\n",
                var_spec, _Context->get_Name().c_str());
      }
   } else {
      var_ref = (*i).second;
   }
   if (var_ref == NULL) {
      printf("failed to create var ref %s on context %s\n", var_spec, _Context->get_Name().c_str());
   }
   return var_ref;
}

typedef std::map<STRING_T,cContextCache*> CONTEXT_CACHE_MAP_T;

class cProcessCache
{
public:
   cProcessCache(cSHProcess * process);
   virtual ~cProcessCache();
   void Refresh();
   void AddContextCache(CONST_STRING_T context_name, cContextCache * context_cache);
   cContextCache * ContextCache(CONST_STRING_T context_name);
   cVarRef * VarRef(CONST_STRING_T context_name, CONST_STRING_T var_spec);
   STRING_T ContextList();
private:
   cSHProcess * _Process;
   CONTEXT_CACHE_MAP_T _ContextCaches;
};

cProcessCache::cProcessCache(cSHProcess * process)
   : _Process(process)
{
}

cProcessCache::~cProcessCache()
{
}

void cProcessCache::Refresh()
{
   STRING_LIST_T context_names;
   _Process->ContextNames(context_names, REMOTE_CONTEXTS);
   if (context_names.size() > 0) {
      STRING_LIST_T::const_iterator i = context_names.begin();
      while (i != context_names.end()) {
         STRING_T context_name = (*i);
         if (ContextCache(context_name.c_str()) == NULL) {
            cContext * context = _Process->Context(context_name.c_str(), REMOTE_CONTEXTS);
            if (context != NULL) {
               try {
                  context->Connect();
                  context->Create();
                  cContextCache * context_cache = new cContextCache(context);
                  AddContextCache(context_name.c_str(), context_cache);
                  printf("\ncontext %s activated\n", (*i).c_str());
               } catch (cError & e) {
                  printf("%s setting context %s\n", (const char*)e, context_name.c_str());
               } catch (...) {
                  printf("unhandled exception setting context %s\n", context_name.c_str());
               }
            }
         }
         i++;
      }
   }
//   printf(".");
}

void cProcessCache::AddContextCache(CONST_STRING_T context_name, cContextCache * context_cache)
{
   _ContextCaches[context_name] = context_cache;   
}

cContextCache * cProcessCache::ContextCache(CONST_STRING_T context_name)
{
   CONTEXT_CACHE_MAP_T::const_iterator i = _ContextCaches.find(context_name);
   if (i == _ContextCaches.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

cVarRef * cProcessCache::VarRef(CONST_STRING_T context_name, CONST_STRING_T var_spec)
{
   cVarRef * var_ref = NULL;
   cContextCache * context_cache = ContextCache(context_name);
   if (context_cache != NULL) {
      var_ref = context_cache->VarRef(var_spec);
   }
   return var_ref;
}

STRING_T cProcessCache::ContextList()
{  
   STRING_T context_list;
   CONTEXT_CACHE_MAP_T::const_iterator i = _ContextCaches.begin();
   while (i != _ContextCaches.end()) {
      if (i != _ContextCaches.begin()) {
         context_list += ",";
      }
      context_list += (*i).first;
      i++;
   }
   return context_list;
}


#ifdef vorersmawech

class cGatewayServer : public cExtendedServer
{
public:
   cGatewayServer(cCSComm * comm, cProcessCache * process_cache);
protected:
   virtual void Request(cCSMsg *msg, cCSAddress *client_address);
private:
   void GetValue(cVarRef * var_ref, STRING_T & value);
   void SetValue(cVarRef * var_ref, CONST_STRING_T value);
   void Add(cCSMsg * msg);
private:
   cProcessCache * _ProcessCache;
};

cGatewayServer::cGatewayServer(cCSComm * comm, cProcessCache * process_cache)
      : cExtendedServer(comm), _ProcessCache(process_cache)
{
}

void cGatewayServer::Request(cCSMsg *msg, cCSAddress *client_address)
{
//   Beep(100, 100);
   PTR_T buf = msg->AppData();
   ULONG_T buf_size = msg->AppDataSize();
   ULONG_T client_id = msg->ClientId();
   ULONG_T request_id = msg->RequestId();
printf("request %d\n", request_id);
   ReplyMsg(buf, buf_size, client_id, request_id, client_address);
}

void cGatewayServer::GetValue(cVarRef * var_ref, STRING_T & value)
{
   if (var_ref == NULL) {
      value = "?4";
      return;
   }
   value = "?5";
   try {
      var_ref->GetValue(value);
   } catch (cError & e) {
      printf("%s getting value of %s\n", (const char*)e, var_ref->_Spec.c_str());
   } catch (...) {
      printf("unhandled exception getting value of %s\n", var_ref->_Spec.c_str());
   }
}

void cGatewayServer::SetValue(cVarRef * var_ref, CONST_STRING_T value)
{
   if (var_ref == NULL) {
      value = "?4";
      return;
   }
   try {
      var_ref->SetValue(value);
   } catch (cError & e) {
      printf("%s setting value of %s to %s\n", (const char*)e, var_ref->_Spec.c_str(), value);
   } catch (...) {
      printf("unhandled exception getting value of %s to %s\n", var_ref->_Spec.c_str(), value);
   }
}

void cGatewayServer::Add(cCSMsg * msg)
{
   ULONG_T client_id = msg->ClientId();
   ULONG_T request_id = msg->RequestId();
   ULONG_T data_size = msg->DataSize();
   ULONG_T block_no = msg->BlockNo();
   ULONG_T block_count = msg->BlockCount();
}

static int Gateway(int argc, char* argv[])
{
MAINFUNC_PROLOG("Gateway")
   USHORT_T send_port = 18001;
   USHORT_T receive_port = 18000;
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
      cConfigurationObject * process_obj = config->Object(root_name.c_str());
      if (process_obj != NULL) {
         char prog_file[512] = {0};
         char control_program[512] = {0};
         char control_procedure[512] = {0};
         cSHProcess process(process_obj);
         process.set_Path(argv[0]);
		   process.Start();
         cProcessCache process_cache(&process);
         cResources::RegisterProcess(&process);
         cUDPComm comm(18000, 18001, "localhost");
         cGatewayServer server(&comm, &process_cache);
         server.Start();
         while (!process.Terminated()) {
            process_cache.Refresh();
            Sleep(1000);
         }
      } else {
         printf("Root object %s not found\n", root_name.c_str());
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

#endif

int main(int argc, char* argv[])
{
//   return Gateway(argc, argv);
   return 0;
}
