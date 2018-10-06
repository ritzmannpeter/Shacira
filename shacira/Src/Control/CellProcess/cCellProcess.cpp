//## begin module%3A791D8600CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A791D8600CA.cm

//## begin module%3A791D8600CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A791D8600CA.cp

//## Module: cCellProcess%3A791D8600CA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\CellProcess\cCellProcess.cpp

//## begin module%3A791D8600CA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A791D8600CA.additionalIncludes

//## begin module%3A791D8600CA.includes preserve=yes
//## end module%3A791D8600CA.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProxySender
#include "System/Comm/cProxySender.h"
// cSysProcess
#include "System/Sys/cSysProcess.h"
// cCell
#include "Control/Cell/cCell.h"
// cBackupThread
#include "Control/CellProcess/cBackupThread.h"
// cCellProcess
#include "Control/CellProcess/cCellProcess.h"
// cLocalContext
#include "Control/LocalDatabase/cLocalContext.h"
// cRemoteContext
#include "Client/RemoteDatabase/cRemoteContext.h"
//## begin module%3A791D8600CA.additionalDeclarations preserve=yes
//## end module%3A791D8600CA.additionalDeclarations


// Class cCellProcess 



cCellProcess::cCellProcess()
  //## begin cCellProcess::cCellProcess%.hasinit preserve=no
      : _Backup(NULL)
  //## end cCellProcess::cCellProcess%.hasinit
  //## begin cCellProcess::cCellProcess%.initialization preserve=yes
  //## end cCellProcess::cCellProcess%.initialization
{
  //## begin cCellProcess::cCellProcess%.body preserve=yes
//_ASSERT_UNCOND
  //## end cCellProcess::cCellProcess%.body
}

cCellProcess::cCellProcess(const cCellProcess &right)
  //## begin cCellProcess::cCellProcess%copy.hasinit preserve=no
      : _Backup(NULL)
  //## end cCellProcess::cCellProcess%copy.hasinit
  //## begin cCellProcess::cCellProcess%copy.initialization preserve=yes
  //## end cCellProcess::cCellProcess%copy.initialization
{
  //## begin cCellProcess::cCellProcess%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCellProcess::cCellProcess%copy.body
}

cCellProcess::cCellProcess (cConfigurationObject *config_obj)
  //## begin cCellProcess::cCellProcess%981016466.hasinit preserve=no
      : _Backup(NULL)
  //## end cCellProcess::cCellProcess%981016466.hasinit
  //## begin cCellProcess::cCellProcess%981016466.initialization preserve=yes
   , cSHProcess(config_obj, false)
  //## end cCellProcess::cCellProcess%981016466.initialization
{
  //## begin cCellProcess::cCellProcess%981016466.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _BaseDir = config_obj->PropertyValue("BaseDir", "");

   CONFOBJ_VECTOR_T server_context_vec;
   config_obj->PropertyValue("ServerContexts", server_context_vec);
   ULONG_T len = server_context_vec.size();
   ULONG_T i = 0;
   for (i=0; i<len; i++) {
      cConfigurationObject * server_context_object = (cConfigurationObject*)server_context_vec[i];
      STRING_T context_name = server_context_object->get_Name();
      cLocalContext * server_context = new cLocalContext(this, server_context_object);
      context_name = server_context->get_Name();
      server_context->Create();
      AddContext(context_name.c_str(), server_context);
   }
   
   CONFOBJ_VECTOR_T remote_context_vec;
   config_obj->PropertyValue("RemoteContexts", remote_context_vec);
   len = remote_context_vec.size();
   for (i=0; i<len; i++) {
      cConfigurationObject * remote_context_object = (cConfigurationObject*)remote_context_vec[i];
      STRING_T context_name = remote_context_object->get_Name();
      cRemoteContext * remote_context = (cRemoteContext*)Context(context_name.c_str(), REMOTE_CONTEXTS);
      if (remote_context != NULL) {
         AddContext(context_name.c_str(), remote_context);
      } else {
         ErrorPrintf("remote context %s not available\n", context_name.c_str());
      }
   }
   cConfigurationObject * backup_obj =
      (cConfigurationObject*)config_obj->PropertyValue("Backup", (cConfigurationObject*)NULL);
   if (backup_obj != NULL) {
      _Backup = new cBackupThread(this, backup_obj);
   }
  //## end cCellProcess::cCellProcess%981016466.body
}

#include "System/Database/cVariable.h"
cCellProcess::cCellProcess (int context_count, const char * base_context_name, ADD_VARIABLES_CLOSURE_T add_closure, SET_VARIABLES_CLOSURE_T set_closure)
   : _Backup(NULL)
{
  //## begin cCellProcess::cCellProcess%981016466.body preserve=yes
   cProxySender * proxy_sender = new cProxySender("255.255.255.255", 21001);
   STRING_T name = proxy_sender->get_Name();
   AddProxySender(name.c_str(), proxy_sender);
   int i = 0;
   for (i=0; i<context_count; i++) {
      char context_name[0x100] = {0};
      sprintf(context_name, "%s_%04.04d", base_context_name, i);
      cLocalContext * server_context = new cLocalContext(this);
      if (add_closure == NULL) {
         cVarDef * var_def = new cVarDef("test", SH_STRING, 100, 0);
         var_def->_Context = server_context;
         var_def->_SystemFlags |= HOST_READ;
         var_def->_SystemFlags |= HOST_WRITE;
         server_context->AddVarDef("test", var_def);
      } else {
         add_closure(server_context);
      }
      server_context->Create();
      AddContext(context_name, server_context);
   }
}

cCellProcess::~cCellProcess()
{
  //## begin cCellProcess::~cCellProcess%.body preserve=yes
   DELETE_OBJECT(cBackupThread, _Backup);
  //## end cCellProcess::~cCellProcess%.body
}

void cCellProcess::Start ()
{
  //## begin cCellProcess::Start%1072710117.body preserve=yes
   CONTEXT_MAP_T::const_iterator i = _LocalContexts.cbegin();
   while (i != _LocalContexts.cend()) {
      cLocalContext * server_context = (cLocalContext*)(*i).second;
      if (!server_context->get_IsClientContext()) {
         server_context->Start();
      }
      i++;
   }
   if (_Backup != NULL) {
      _Backup->Start();
   }
   cSHProcess::Start();
  //## end cCellProcess::Start%1072710117.body
}

void cCellProcess::Stop ()
{
  //## begin cCellProcess::Stop%1072710118.body preserve=yes
   if (!_Started) return;
   if (_Terminated || _Terminating) return;
   if (_Backup != NULL) {
      _Backup->Stop();
   }
   CONTEXT_MAP_T::const_iterator i = _LocalContexts.cbegin();
   while (i != _LocalContexts.cend()) {
      cLocalContext * server_context = (cLocalContext*)(*i).second;
      if (!server_context->get_IsClientContext()) {
         server_context->Stop();
      }
      i++;
   }
   cSHProcess::Stop();
  //## end cCellProcess::Stop%1072710118.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cCellProcess::get_BaseDir () const
{
  //## begin cCellProcess::get_BaseDir%3AE931C60337.get preserve=no
  return _BaseDir;
  //## end cCellProcess::get_BaseDir%3AE931C60337.get
}

// Additional Declarations
  //## begin cCellProcess%3A791D8600CA.declarations preserve=yes
  //## end cCellProcess%3A791D8600CA.declarations

//## begin module%3A791D8600CA.epilog preserve=yes
//## end module%3A791D8600CA.epilog
