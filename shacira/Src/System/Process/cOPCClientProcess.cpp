//## begin module%431339020347.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%431339020347.cm

//## begin module%431339020347.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%431339020347.cp

//## Module: cOPCClientProcess%431339020347; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOPCClientProcess.cpp

//## begin module%431339020347.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%431339020347.additionalIncludes

//## begin module%431339020347.includes preserve=yes

/// PR 19.10.06 - checking for invalid ip addresses (127.0.0.1)
/// PR 20.10.06 - pinging before connecting, removed standard error log entry

#include "System/Objects/cProxy.h"

//## end module%431339020347.includes

// cOPCClientProcess
#include "System/Process/cOPCClientProcess.h"
// cNameSpaceIterator
#include "System/Namespace/cNameSpaceIterator.h"
// cContext
#include "System/Database/cContext.h"
//## begin module%431339020347.additionalDeclarations preserve=yes
//## end module%431339020347.additionalDeclarations


// Class cOPCClientProcess 

//## begin cOPCClientProcess::OPCClientProcess%43133A4F0088.attr preserve=no  public: static cOPCClientProcess * {U} NULL
cOPCClientProcess *cOPCClientProcess::_OPCClientProcess = NULL;
//## end cOPCClientProcess::OPCClientProcess%43133A4F0088.attr


cOPCClientProcess::cOPCClientProcess()
  //## begin cOPCClientProcess::cOPCClientProcess%.hasinit preserve=no
  //## end cOPCClientProcess::cOPCClientProcess%.hasinit
  //## begin cOPCClientProcess::cOPCClientProcess%.initialization preserve=yes
  : cSHClientProcess(IF_OPC)
  //## end cOPCClientProcess::cOPCClientProcess%.initialization
{
  //## begin cOPCClientProcess::cOPCClientProcess%.body preserve=yes
  //## end cOPCClientProcess::cOPCClientProcess%.body
}

cOPCClientProcess::cOPCClientProcess(const cOPCClientProcess &right)
  //## begin cOPCClientProcess::cOPCClientProcess%copy.hasinit preserve=no
  //## end cOPCClientProcess::cOPCClientProcess%copy.hasinit
  //## begin cOPCClientProcess::cOPCClientProcess%copy.initialization preserve=yes
  //## end cOPCClientProcess::cOPCClientProcess%copy.initialization
{
  //## begin cOPCClientProcess::cOPCClientProcess%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cOPCClientProcess::cOPCClientProcess%copy.body
}


cOPCClientProcess::~cOPCClientProcess()
{
  //## begin cOPCClientProcess::~cOPCClientProcess%.body preserve=yes
  //## end cOPCClientProcess::~cOPCClientProcess%.body
}



//## Other Operations (implementation)
void cOPCClientProcess::Init ()
{
  //## begin cOPCClientProcess::Init%1125333424.body preserve=yes
   _OPCClientProcess = new cOPCClientProcess();
   _OPCClientProcess->Start();
   _OPCClientProcess->AddProxyReceiver(21001);
   _OPCClientProcess->AddProxyReceiver(21002);
   _OPCClientProcess->AddProxyReceiver(21003);
  //## end cOPCClientProcess::Init%1125333424.body
}

void cOPCClientProcess::OnCycle ()
{
  //## begin cOPCClientProcess::OnCycle%1125662156.body preserve=yes
static STRING_MAP_T _SkippedContexts;
   cObjectLock __lock__(&_NameSpaceMutex);
   STRING_LIST_T context_names;
   ContextNames(context_names, REMOTE_CONTEXTS);
   STRING_LIST_T::const_iterator i = context_names.cbegin();
   while (i != context_names.cend()) {
      STRING_T context_name = (*i);
      cContext * context = Context(context_name.c_str(), REMOTE_CONTEXTS);
      cProxy * proxy = Proxy(context_name.c_str());
      if (proxy == NULL) {
         InfoPrintf("skipped context %s: proxy is NULL\n", context_name.c_str());
      } else {
         STRING_T ip_addr = proxy->get_IPAddress();
         if (_stricmp(ip_addr.c_str(), "127.0.0.1") == 0) {
            STRING_MAP_T::const_iterator sc = _SkippedContexts.find(context_name.c_str());
            if (sc == _SkippedContexts.cend()) {
               InfoPrintf("skipped context %s: unsupported ip address %s\n", context_name.c_str(), ip_addr.c_str());
               _SkippedContexts[context_name.c_str()] = context_name.c_str();
            }
         } else {
            if (context->Ping()) {
               if (!context->IsActive()) {
                  try {
                     context->Connect(IF_OPC);
                     context->Create();
                     _NewContexts[context_name.c_str()] = context;
                     InfoPrintf("new context %s added in opc client process\n", context_name.c_str());
                  } catch (cError & e) {
//                     ErrorPrintf("%s while connecting to %s\n", (const char *)e, context_name.c_str());
                  } catch (...) {
                     ErrorPrintf("unknown exception while connecting to %s\n", context_name.c_str());
                  }
               }
            }
         }
      }
      i++;
   }
  //## end cOPCClientProcess::OnCycle%1125662156.body
}

void cOPCClientProcess::NewContextNames (STRING_LIST_T &context_names)
{
  //## begin cOPCClientProcess::NewContextNames%1125664304.body preserve=yes
   cObjectLock __lock__(&_NameSpaceMutex);
   CONTEXT_MAP_T::const_iterator i = _NewContexts.cbegin();
   while (i != _NewContexts.cend()) {
      cContext * context = (*i).second;
      if (context != NULL) {
         context_names.push_back(context->get_Name().c_str());
      }
      i++;
   }
  //## end cOPCClientProcess::NewContextNames%1125664304.body
}

cContext * cOPCClientProcess::NewContext (CONST_STRING_T name)
{
  //## begin cOPCClientProcess::NewContext%1125664305.body preserve=yes
   CONTEXT_MAP_T::const_iterator i = _NewContexts.find(name);
   if (i != _NewContexts.cend()) {
      cContext * context = (*i).second;
      _NewContexts.erase(name);
      return context;
   } else {
      return NULL;
   }
  //## end cOPCClientProcess::NewContext%1125664305.body
}

// Additional Declarations
  //## begin cOPCClientProcess%431339020347.declarations preserve=yes
  //## end cOPCClientProcess%431339020347.declarations

//## begin module%431339020347.epilog preserve=yes
//## end module%431339020347.epilog
