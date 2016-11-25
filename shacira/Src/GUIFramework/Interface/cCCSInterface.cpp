//## begin module%4005259C0000.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4005259C0000.cm

//## begin module%4005259C0000.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4005259C0000.cp

//## Module: cCCSInterface%4005259C0000; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\Interface\cCCSInterface.cpp

//## begin module%4005259C0000.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4005259C0000.additionalIncludes

//## begin module%4005259C0000.includes preserve=yes
#include "Control/LocalDatabase/cLocalContext.h"
//## end module%4005259C0000.includes

// cResources
#include "System/Process/cResources.h"
// cSHProcess
#include "System/Process/cSHProcess.h"
// cOptions
#include "System/Process/cOptions.h"
// cMemoryConsole
#include "System/Console/cMemoryConsole.h"
// cStandardConsole
#include "System/Console/cStandardConsole.h"
// cFileConsole
#include "System/Console/cFileConsole.h"
// cSocketConsole
#include "System/Console/cSocketConsole.h"
// cConfiguration
#include "System/Config/cConfiguration.h"
// cContext
#include "System/Database/cContext.h"
// cSockets
#include "System/Sys/cSockets.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cLocalChannel
#include "System/Channel/cLocalChannel.h"
// cChannel
#include "System/Channel/cChannel.h"
// cCellProcess
#include "Control/CellProcess/cCellProcess.h"
// cBroker
#include "Orb/cBroker.h"
// cEventAdapter
#include "Client/Adapters/cEventAdapter.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
// cCCSInterface
#include "GUIFramework/Interface/cCCSInterface.h"
// cNodeList
#include "GUIFramework/cNodeList.h"
// cNode
#include "GUIFramework/cNode.h"
//## begin module%4005259C0000.additionalDeclarations preserve=yes

#undef ANALYZE_OBJECTS
#ifdef ANALYZE_OBJECTS
class cAnalyzeAdapter : public cEventAdapter
{
   virtual void Object (cTransientObject *object)
   {
      ULONG_T object_type = object->get_Type();
      if (object_type != OT_INFO) {
         return;
      }
      STRING_T ser_obj = object->Serialize();
      FILE * stream = fopen("objects", "a");
      if (stream != NULL) {
         fprintf(stream, "%s\n", ser_obj.c_str());
         fclose(stream);
      }
   };
};
#endif

//## end module%4005259C0000.additionalDeclarations


// Class cCCSInterface 













cCCSInterface::cCCSInterface()
  //## begin cCCSInterface::cCCSInterface%.hasinit preserve=no
      : _Argc(0), _Argv(NULL), _RootName("CCSApplication"), _Loaded(false), _ProcessObject(NULL), _RootContext(NULL), _NodeList(NULL), _Process(NULL)
  //## end cCCSInterface::cCCSInterface%.hasinit
  //## begin cCCSInterface::cCCSInterface%.initialization preserve=yes
  //## end cCCSInterface::cCCSInterface%.initialization
{
  //## begin cCCSInterface::cCCSInterface%.body preserve=yes
_ASSERT_UNCOND
  //## end cCCSInterface::cCCSInterface%.body
}

cCCSInterface::cCCSInterface(const cCCSInterface &right)
  //## begin cCCSInterface::cCCSInterface%copy.hasinit preserve=no
      : _Argc(0), _Argv(NULL), _RootName("CCSApplication"), _Loaded(false), _ProcessObject(NULL), _RootContext(NULL), _NodeList(NULL), _Process(NULL)
  //## end cCCSInterface::cCCSInterface%copy.hasinit
  //## begin cCCSInterface::cCCSInterface%copy.initialization preserve=yes
  //## end cCCSInterface::cCCSInterface%copy.initialization
{
  //## begin cCCSInterface::cCCSInterface%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCCSInterface::cCCSInterface%copy.body
}

cCCSInterface::cCCSInterface (int argc, char **argv)
  //## begin cCCSInterface::cCCSInterface%1074080278.hasinit preserve=no
      : _Argc(0), _Argv(NULL), _RootName("CCSApplication"), _Loaded(false), _ProcessObject(NULL), _RootContext(NULL), _NodeList(NULL), _Process(NULL)
  //## end cCCSInterface::cCCSInterface%1074080278.hasinit
  //## begin cCCSInterface::cCCSInterface%1074080278.initialization preserve=yes
  //## end cCCSInterface::cCCSInterface%1074080278.initialization
{
  //## begin cCCSInterface::cCCSInterface%1074080278.body preserve=yes
   _Argc = argc;
   _Argv = argv;
  //## end cCCSInterface::cCCSInterface%1074080278.body
}


cCCSInterface::~cCCSInterface()
{
  //## begin cCCSInterface::~cCCSInterface%.body preserve=yes
   if (_Process != NULL) {
      if (!_Process->get_IsClient()) {
         cBroker::Cleanup();
      }
      _Process->Stop();
      DELETE_OBJECT(cSHProcess,_Process)
   }
  //## end cCCSInterface::~cCCSInterface%.body
}

//## Other Operations (implementation)
BOOL_T cCCSInterface::Load ()
{
  //## begin cCCSInterface::Load%1074080279.body preserve=yes
   if (_Loaded) {
      ErrorPrintf("\ntried to load CCS Interface twice\n");
      return false;
   } else {
      _Loaded = true;
   }
   try {
      if (!cResources::FlagSet(PF_DELAYED_ORB_INIT)) {
         cBroker::Initialize(_Argc, _Argv);
      }
      cSockets::Initialize();
      cResources::GetOption("RootName", _RootName);
      _NodeList = new cNodeList;
      cDataChangeAdapter * data_change_adapter = new cDataChangeAdapter;
      _DataChangeAdapters["standard"] = data_change_adapter;
      cEventAdapter * event_adapter = new cEventAdapter;
      _EventAdapters["standard"] = event_adapter;
#ifdef ANALYZE_OBJECTS
      cAnalyzeAdapter * analyze_adapter = new cAnalyzeAdapter;
      _EventAdapters["analyze"] = event_adapter;
#endif
      _ConfigFile = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                 cConfiguration::DefaultConfigFile());
      cConfiguration * config = new cConfiguration(_ConfigFile.c_str());
      _ProcessObject = config->Object(_RootName.c_str());
      if (_ProcessObject == NULL) {
         ErrorPrintf("\nno process object %s\n", _RootName.c_str());
         return false;
      }
      _Process = new cCellProcess(_ProcessObject);
      STRING_LIST_T context_names;
      _Process->ContextNames(context_names, LOCAL_CONTEXTS);
      // search for root context
      STRING_LIST_T::const_iterator i = context_names.begin();
      while (i != context_names.end()) {
         STRING_T context_name = (*i);
         if (context_name.size() > 0) {
            cContext * context = _Process->Context(context_name.c_str(), LOCAL_CONTEXTS);
            if (context != NULL) {
               if (context->get_IsRootContext()) {
                  _RootContext = context;
//                  _Process->SetRootContext(_RootContext);
               }
            }
         }
         i++;
      }
      if (_RootContext != NULL) {
         i = context_names.begin();
         while (i != context_names.end()) {
            STRING_T context_name = (*i);
            if (context_name.size() > 0) {
               cContext * context = _Process->Context(context_name.c_str(), LOCAL_CONTEXTS);
               if (context != NULL) {
                  if (context != _RootContext) {
                     _RootContext->Search(context);
//                     _Process->SetRootContext(_RootContext);
                  }
                  cChannel * event_channel = context->EventChannel();
                  if (event_channel != NULL) {
                     event_channel->Connect(event_adapter);
                     event_channel->Connect(data_change_adapter);
#ifdef ANALYZE_OBJECTS
                     event_channel->Connect(analyze_adapter);
#endif
                  }
               }
            }
            i++;
         }
         cNode * node = new cNode(_RootContext, data_change_adapter, event_adapter);
         _NodeList->AddNode(node);
         return true;
      } else {
         ErrorPrintf("\nno local root context found\n");
         return false;
      }
   } catch(cError & e) {
      ErrorPrintf("\n%s loading CCS\n", e.ErrMsg().c_str());
      return false;
   } catch(...) {
      ErrorPrintf("\nunknown exception loading CCS\n");
      return false;
   }
  //## end cCCSInterface::Load%1074080279.body
}

BOOL_T cCCSInterface::Start ()
{
  //## begin cCCSInterface::Start%1091612889.body preserve=yes
   try {
      if (_Process != NULL &&
          !_Process->Started()) {
         _Process->Start();
         cResources::RegisterProcess(_Process);
      }
   } catch(cError & e) {
      ErrorPrintf("\n%s starting CCS\n", e.ErrMsg().c_str());
      return false;
   } catch(...) {
      ErrorPrintf("\nunknown exception starting CCS\n");
      return false;
   }
   return true;
  //## end cCCSInterface::Start%1091612889.body
}

BOOL_T cCCSInterface::Stop ()
{
  //## begin cCCSInterface::Stop%1120214653.body preserve=yes
   if (_Process != NULL &&
       _Process->Started()) {
      _Process->Stop();
   }
   return true;
  //## end cCCSInterface::Stop%1120214653.body
}

cNodeList * cCCSInterface::NodeList ()
{
  //## begin cCCSInterface::NodeList%1074080280.body preserve=yes
   return _NodeList;
  //## end cCCSInterface::NodeList%1074080280.body
}

void cCCSInterface::Lock ()
{
  //## begin cCCSInterface::Lock%1088517107.body preserve=yes
   std::map<STRING_T,cEventAdapter*>::const_iterator i = _EventAdapters.begin();
   while (i != _EventAdapters.end()) {
      cEventAdapter * adapter = (*i).second;
      adapter->Lock();
      i++;
   }
   std::map<STRING_T,cDataChangeAdapter*>::const_iterator j = _DataChangeAdapters.begin();
   while (j != _DataChangeAdapters.end()) {
      cDataChangeAdapter * adapter = (*j).second;
      adapter->Lock();
      j++;
   }
  //## end cCCSInterface::Lock%1088517107.body
}

void cCCSInterface::Unlock ()
{
  //## begin cCCSInterface::Unlock%1088517108.body preserve=yes
   std::map<STRING_T,cEventAdapter*>::const_iterator i = _EventAdapters.begin();
   while (i != _EventAdapters.end()) {
      cEventAdapter * adapter = (*i).second;
      adapter->Unlock();
      i++;
   }
   std::map<STRING_T,cDataChangeAdapter*>::const_iterator j = _DataChangeAdapters.begin();
   while (j != _DataChangeAdapters.end()) {
      cDataChangeAdapter * adapter = (*j).second;
      adapter->Unlock();
      j++;
   }
  //## end cCCSInterface::Unlock%1088517108.body
}

BOOL_T cCCSInterface::PrepareProcess ()
{
  //## begin cCCSInterface::PrepareProcess%1097343822.body preserve=yes
   try {
      _NodeList = new cNodeList;
//      cResources(_Argc, _Argv);
      cBroker::Initialize(_Argc, _Argv);
      cSockets::Initialize();
      cResources::GetOption("RootName", _RootName);
      _ConfigFile = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                 cConfiguration::DefaultConfigFile());
      cConfiguration * config = new cConfiguration(_ConfigFile.c_str());
      _ProcessObject = config->Object(_RootName.c_str());
      if (_ProcessObject == NULL) {
         ErrorPrintf("\nno process object %s\n", _RootName.c_str());
         return false;
      }
      _Process = new cSHProcess(_ProcessObject);
      _Process->Start();
      return true;
   } catch(cError & e) {
      ErrorPrintf("\n%s\n", e.ErrMsg().c_str());
      return false;
   } catch(...) {
      ErrorPrintf("\nunknown exception preparing process\n");
      return false;
   }
  //## end cCCSInterface::PrepareProcess%1097343822.body
}

BOOL_T cCCSInterface::LoadRemote (cContext *context)
{
  //## begin cCCSInterface::LoadRemote%1097333007.body preserve=yes
   if (_Loaded) {
      ErrorPrintf("\ntried to load CCS Interface twice\n");
      return false;
   } else {
      _Loaded = true;
   }
   try {
      if (context != NULL) {
         context->Connect();
         context->Create();
         _RootContext = context;
//         _Process->SetRootContext(_RootContext);
         cDataChangeAdapter * data_change_adapter = new cDataChangeAdapter;
         _DataChangeAdapters["standard"] = data_change_adapter;
         cEventAdapter * event_adapter = new cEventAdapter;
         _EventAdapters["standard"] = event_adapter;
#ifdef ANALYZE_OBJECTS
         cAnalyzeAdapter * analyze_adapter = new cAnalyzeAdapter;
         _EventAdapters["analyze"] = event_adapter;
#endif
         cChannel * event_channel = context->EventChannel();
         if (event_channel != NULL) {
            event_channel->Connect(event_adapter);
            event_channel->Connect(data_change_adapter);
#ifdef ANALYZE_OBJECTS
            event_channel->Connect(analyze_adapter);
#endif
         }

         STRING_LIST_T context_names;
         _Process->ContextNames(context_names, LOCAL_CONTEXTS);
         if (_RootContext != NULL) {
            STRING_LIST_T::const_iterator i = context_names.begin();
            i = context_names.begin();
            while (i != context_names.end()) {
               STRING_T context_name = (*i);
               if (context_name.size() > 0) {
                  cContext * context = _Process->Context(context_name.c_str(), LOCAL_CONTEXTS);
                  if (context != NULL) {
                     if (context != _RootContext) {
                        _RootContext->Search(context);
                     }
                     event_channel = context->EventChannel();
                     if (event_channel != NULL) {
                        event_channel->Connect(event_adapter);
                        event_channel->Connect(data_change_adapter);
#ifdef ANALYZE_OBJECTS
                        event_channel->Connect(analyze_adapter);
#endif
                     }
                  }
               }
               i++;
            }
            cNode * node = new cNode(_RootContext, data_change_adapter, event_adapter);
            _NodeList->AddNode(node);
            return true;
         } else {
            return false;
         }
      } else {
         ErrorPrintf("\nno remote root context found\n");
         return false;
      }
   } catch(cError & e) {
      ErrorPrintf("\n%s loading CCS\n", e.ErrMsg().c_str());
      return false;
   } catch(...) {
      ErrorPrintf("\nunknown exception loading CCS\n");
      return false;
   }
  //## end cCCSInterface::LoadRemote%1097333007.body
}

cSHProcess * cCCSInterface::Process ()
{
  //## begin cCCSInterface::Process%1097343821.body preserve=yes
   return _Process;
  //## end cCCSInterface::Process%1097343821.body
}

cContext * cCCSInterface::Context (cSHProcess *process, CONST_STRING_T name, ULONG_T timeout)
{
  //## begin cCCSInterface::Context%1074080285.body preserve=yes
   INT_T time_left = timeout;
   cContext * context = NULL;
   while (context == NULL) {
      context = process->Context(name, ALL_CONTEXTS);
      if (context == NULL) {
         if (time_left <= 0) break;
         cSystemUtils::Suspend(1000);
         time_left -= 1000;
      }
   }
   return context;
  //## end cCCSInterface::Context%1074080285.body
}

// Additional Declarations
  //## begin cCCSInterface%4005259C0000.declarations preserve=yes
void cCCSInterface::SetUiUpdateFunction(UI_UPDATE_FUNCTION_T function)
{
   cContext::SetUiUpdateFunction(function);
}
  //## end cCCSInterface%4005259C0000.declarations

//## begin module%4005259C0000.epilog preserve=yes
//## end module%4005259C0000.epilog
