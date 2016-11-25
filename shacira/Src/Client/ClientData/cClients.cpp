//## begin module%42DD14750128.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DD14750128.cm

//## begin module%42DD14750128.cp preserve=no
//	Copyright © 2002 - 2016 by
//	2i Industrial Informatics GmbH
//## end module%42DD14750128.cp

//## Module: cClients%42DD14750128; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\ClientData\cClients.cpp

//## begin module%42DD14750128.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%42DD14750128.additionalIncludes

//## begin module%42DD14750128.includes preserve=yes
//## end module%42DD14750128.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cClients
#include "Client/ClientData/cClients.h"
// cClientData
#include "Client/ClientData/cClientData.h"
//## begin module%42DD14750128.additionalDeclarations preserve=yes


static BOOL_T _StopIt = false;

INT_T cTimeoutControl::MainFunc(void * extra)
{
MAINFUNC_PROLOG(_Name.c_str())
   while (!(_Terminated || _Terminating)) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      if (_StopIt) {
         InfoPrintf("client timeout control exit\n");
         return 0;
      }
      if (CheckClients() == 0) {
      }
      cSystemUtils::Suspend(_IdleTime);
MAINFUNC_LOOP_EPILOG
   }
   InfoPrintf("client timeout control exit\n");
   return 0;
MAINFUNC_EPILOG
};

INT_T cTimeoutControl::CheckClients()
{
   int active_clients = 0;
   cObjectLock __lock__(&cClients::_ClientAccessMutex);
   for (ULONG_T i=0; i<USER_CLIENTS_ID_MAX; i++) {
      cClientData * client_data = cClients::_ClientData[i];
      if (client_data != NULL) {
         if (client_data->TimedOut()) {
            InfoPrintf("removing client %d at %d\n", client_data->get_Id(), i);
            cClients::RemoveClient(client_data->get_Id());
         } else {
            active_clients++;
         }
      }
   }
   return active_clients;
}

void cTimeoutControl::Launch()
{
   if (!_Started) {
      Start();
      _Started = true;
      InfoPrintf("client timeout control started\n");
   }
}

//## end module%42DD14750128.additionalDeclarations


// Class cClients 

//## begin cClients::CurrentClients%42DF63D303A9.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cClients::_CurrentClients = 0;
//## end cClients::CurrentClients%42DF63D303A9.attr

//## begin cClients::Connected%42DF6295032C.attr preserve=no  implementation: static BOOL_T {U} false
BOOL_T cClients::_Connected = false;
//## end cClients::Connected%42DF6295032C.attr

//## begin cClients::ClientData%42DD14D60157.attr preserve=no  implementation: static CLIENT_VECTOR_T {U} 
CLIENT_VECTOR_T cClients::_ClientData;
//## end cClients::ClientData%42DD14D60157.attr

//## begin cClients::ClientAccessMutex%42DD15C50148.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cClients::_ClientAccessMutex;
//## end cClients::ClientAccessMutex%42DD15C50148.attr

//## begin cClients::TimeoutControl%42DEA5DF004E.attr preserve=no  implementation: static cTimeoutControl {U} 
cTimeoutControl cClients::_TimeoutControl;
//## end cClients::TimeoutControl%42DEA5DF004E.attr

cClients::cClients()
  //## begin cClients::cClients%.hasinit preserve=no
  //## end cClients::cClients%.hasinit
  //## begin cClients::cClients%.initialization preserve=yes
  //## end cClients::cClients%.initialization
{
  //## begin cClients::cClients%.body preserve=yes
  //## end cClients::cClients%.body
}

cClients::cClients(const cClients &right)
  //## begin cClients::cClients%copy.hasinit preserve=no
  //## end cClients::cClients%copy.hasinit
  //## begin cClients::cClients%copy.initialization preserve=yes
  //## end cClients::cClients%copy.initialization
{
  //## begin cClients::cClients%copy.body preserve=yes
  //## end cClients::cClients%copy.body
}


cClients::~cClients()
{
  //## begin cClients::~cClients%.body preserve=yes
  //## end cClients::~cClients%.body
}



//## Other Operations (implementation)
cClientData * cClients::GetClientData (ULONG_T id)
{
  //## begin cClients::GetClientData%1121785240.body preserve=yes
   cObjectLock __lock__(&_ClientAccessMutex);
   cClientData * client_data = _ClientData[id];
   if (client_data == NULL) {
      if (!IS_INTERFACE_ID(id)) {
         throw cError(CLIENT_INTERFACE_NO_MORE_CONNECTIONS_AVAILABLE, 0,
                      cConvUtils::StringValue(USER_CLIENTS_ID_MAX).c_str(),
                      cConvUtils::StringValue(_CurrentClients).c_str());

      }
      client_data = AllocClient(id);
   }
   return client_data;
  //## end cClients::GetClientData%1121785240.body
}

cClientData * cClients::AllocClient (ULONG_T client_id)
{
  //## begin cClients::AllocClient%1141202704.body preserve=yes
   cObjectLock __lock__(&_ClientAccessMutex);
   cClientData * client_data = new cClientData;
   client_data->set_Id(client_id);
   client_data->set_IFType(client_id);
   _ClientData[client_id] = client_data;
   client_data->Resync();
   _CurrentClients++;
   InfoPrintf("new client %d at %d\n", client_data->get_Id(), client_id);
   return client_data;
  //## end cClients::AllocClient%1141202704.body
}

cClientData * cClients::AllocClient (CONST_STRING_T user_name, CONST_STRING_T password)
{
  //## begin cClients::AllocClient%1121785244.body preserve=yes
   cObjectLock __lock__(&_ClientAccessMutex);
   for (ULONG_T i=USER_CLIENTS_ID_START; i<USER_CLIENTS_ID_MAX; i++) {
      if (_ClientData[i] == NULL) {
         cClientData * client_data = new cClientData;
         _ClientData[i] = client_data;
         client_data->set_Id(i);
         client_data->Resync();
         _CurrentClients++;
#ifdef TIMEOUT_CONTROL
         // PR this concept must be verified before it can be used
         _TimeoutControl.Launch();
#endif
         InfoPrintf("new client %d(%s,%s) at %d\n", client_data->get_Id(), user_name, password, i);
         return client_data;
      }
   }
   throw cError(CLIENT_INTERFACE_NO_MORE_CONNECTIONS_AVAILABLE, 0,
                cConvUtils::StringValue(USER_CLIENTS_ID_MAX).c_str(),
                cConvUtils::StringValue(_CurrentClients).c_str());
   return NULL;
  //## end cClients::AllocClient%1121785244.body
}

BOOL_T cClients::RemoveClient (ULONG_T id)
{
  //## begin cClients::RemoveClient%1121785241.body preserve=yes
   cObjectLock __lock__(&_ClientAccessMutex);
   for (ULONG_T i=0; i<USER_CLIENTS_ID_MAX; i++) {
      cClientData * client_data = _ClientData[i];
      if (client_data != NULL) {
         if (client_data->get_Id() == id)  {
            _ClientData[i] = NULL;
            InfoPrintf("client %d at %d logged out\n", client_data->get_Id(), i);
            delete client_data;
            _CurrentClients--;
            return true;
         }
      }
   }
   return false;
  //## end cClients::RemoveClient%1121785241.body
}

void cClients::AddObject (cTransientObject *object)
{
  //## begin cClients::AddObject%1121845388.body preserve=yes
   cObjectLock __lock__(&_ClientAccessMutex);
   for (ULONG_T i=0; i<USER_CLIENTS_ID_MAX; i++) {
      if (_ClientData[i] != NULL) {
         cClientData * client_data = _ClientData[i];
         client_data->AddObject(object);
      }
   }
  //## end cClients::AddObject%1121845388.body
}

void cClients::Exit ()
{
  //## begin cClients::Exit%1121933608.body preserve=yes
   InfoPrintf("exit client interface\n");
   for (ULONG_T i=0; i<USER_CLIENTS_ID_MAX; i++) {
      cClientData * client_data = cClients::_ClientData[i];
      if (client_data != NULL) {
         InfoPrintf("removing client %d at %d\n", client_data->get_Id(), i);
         cClients::RemoveClient(client_data->get_Id());
      }
   }
   _TimeoutControl.Stop();
  //## end cClients::Exit%1121933608.body
}

BOOL_T cClients::GetConnected ()
{
  //## begin cClients::GetConnected%1121933609.body preserve=yes
   return _Connected;
  //## end cClients::GetConnected%1121933609.body
}

void cClients::SetConnected (BOOL_T value)
{
  //## begin cClients::SetConnected%1121933610.body preserve=yes
   _Connected = value;
  //## end cClients::SetConnected%1121933610.body
}

ULONG_T cClients::GetCurrentClients ()
{
  //## begin cClients::GetCurrentClients%1121933611.body preserve=yes
   return _CurrentClients;
  //## end cClients::GetCurrentClients%1121933611.body
}

// Additional Declarations
  //## begin cClients%42DD14750128.declarations preserve=yes
  //## end cClients%42DD14750128.declarations

//## begin module%42DD14750128.epilog preserve=yes
//## end module%42DD14750128.epilog
