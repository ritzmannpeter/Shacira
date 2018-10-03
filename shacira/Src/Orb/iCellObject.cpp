
#include "FirstHeader.h"
#include "iCellObject.h"
#include "cBroker.h"
#include "Client/ClientData/cClients.h"
#include "Client/ClientData/cClientData.h"
#include "System/Objects/cUserInfo.h"
#include "Control/LocalDatabase/cLocalContext.h"
#include "System/Database/cBinaryObject.h"
#include "System/Structs/cExtendedObjectRing.h"

#define CONTEXT_REF ((cLocalContext*)_Link)

static void _SetUserInfo(ULONG_T client_id, ULONG_T if_type)
{
   cClientData * client_data =  cClients::GetClientData(client_id, if_type);
   if (client_data == NULL) {
      client_data = cClients::AllocClient(client_id, if_type);
   }
   cUserInfo * user_info = client_data->UserInfo();
   if (user_info == NULL) {
      user_info = new cUserInfo;
      user_info->set_UserName(cClients::UserName(if_type));
      user_info->set_ClientId(client_id);
      user_info->set_IFType(if_type);
      client_data->SetUserInfo(user_info);
   }
   cSystemUtils::SetThreadData(user_info);
}

static void _SetUserInfo(ULONG_T client_id)
{
   _SetUserInfo(client_id, 0);
}

#define SET_USER_INFO(client_id) \
   _SetUserInfo(client_id); \


iCellObject::iCellObject(const char *object_name, void * link)
   : _Link(NULL), _Removed(false)
{
   _Link = link;
//   this->_obj_is_ready(cBroker::Boa());
   if (cBroker::GetUseCorbaLoc()) {
      PortableServer::ObjectId * oid = PortableServer::string_to_ObjectId (CELL_OBJECT_KEY);
      cBroker::Poa()->activate_object_with_id(*oid, this);
      char corbaloc[0x200] = {0};
      Control::iCell_var obj_ref = this->_this();
      STRING_T ior = cBroker::Orb()->object_to_string(obj_ref);
      STRING_T ip_address;
      ULONG_T ip_port = 0;
      cBroker::DecodeIOR(ior.c_str(), ip_address, ip_port);
      SafePrintf(corbaloc, sizeof(corbaloc), "corbaloc::%s:%d/%s", ip_address.c_str(), ip_port, CELL_OBJECT_KEY); 
      _IOR = corbaloc;
   } else {
      PortableServer::ObjectId_var myechoid = cBroker::Poa()->activate_object(this);
      Control::iCell_var obj_ref = this->_this();
      _IOR = cBroker::Orb()->object_to_string(obj_ref);
   }
}

iCellObject::~iCellObject()
{
   if (!_Removed) Remove();
}

void iCellObject::Remove()
{
   _Removed = true;	
//   _dispose();
}

STRING_T iCellObject::IOR()
{
	return _IOR;
}

char * iCellObject::Name()
{
CORBA_OBJECT_PROLOG("iCellObject::Name")
   STRING_T name = CONTEXT_REF->get_Name();
   return CORBA_STRING_DUP(name.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::GetVarDefs(long client_id, long if_type)
{
CORBA_OBJECT_PROLOG("iCellObject::GetVarDefs")
	STRING_T var_defs;
    _SetUserInfo(client_id, if_type);
	CONTEXT_REF->GetVarDefs(var_defs, if_type);
	return CORBA_STRING_DUP(var_defs.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

long iCellObject::GetId(long client_id, const char * var_name)
{
CORBA_OBJECT_PROLOG("iCellObject::GetId")
SET_USER_INFO(client_id)
//   return CONTEXT_REF->GetId(var_name);
CORBA_OBJECT_EPILOG
   return 0;
}

char * iCellObject::GetValue(long client_id, const char * var_name, long i1, long i2, long i3, long i4, long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::GetValue")
SET_USER_INFO(client_id)
   STRING_T _var_name = var_name;
   cClientData * client_data =  cClients::GetClientData(client_id);
   CONTEXT_REF->RefFilter(client_data->get_IFType(), _var_name, i1, i2, i3, i4);
   STRING_T value;
   CONTEXT_REF->GetValue(_var_name.c_str(), value, i1, i2, i3, i4, flags|VF_MEMORY_ACCESS);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::GetValueById(long client_id, long var_id, long i1, long i2, long i3, long i4, long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::GetValueById")
SET_USER_INFO(client_id)
   STRING_T value;
//   CONTEXT_REF->GetValueById(id, value, i1, i2, i3, i4, flags|VF_MEMORY_ACCESS);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::Refresh(long client_id, const char * var_name, long i1, long i2, long i3, long i4, long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::Refresh")
SET_USER_INFO(client_id)
   CONTEXT_REF->Refresh(var_name, i1, i2, i3, i4, flags);
CORBA_OBJECT_EPILOG
}

void iCellObject::RefreshById(long client_id, long var_id, long i1, long i2, long i3, long i4, long flags)
{
SET_USER_INFO(client_id)
}

void iCellObject::SetValue(long client_id, const char * var_name, const char * value, long i1, long i2, long i3, long i4, long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::SetValue")
SET_USER_INFO(client_id)
   STRING_T _var_name = var_name;
   cClientData * client_data =  cClients::GetClientData(client_id);
   CONTEXT_REF->RefFilter(client_data->get_IFType(), _var_name, i1, i2, i3, i4);
   CONTEXT_REF->SetValue(_var_name.c_str(), value, i1, i2, i3, i4, flags);
CORBA_OBJECT_EPILOG
}

void iCellObject::SetValueById(long client_id, long var_id, const char * value, long i1, long i2, long i3, long i4, long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::SetValueById")
SET_USER_INFO(client_id)
//   CONTEXT_REF->SetValueById(id, value, i1, i2, i3, i4, flags);
CORBA_OBJECT_EPILOG
}

char * iCellObject::GetMinimum(long client_id, const char * var_name, long i1, long i2, long i3, long i4)
{
CORBA_OBJECT_PROLOG("iCellObject::GetMinimum")
SET_USER_INFO(client_id)
   STRING_T value;
   STRING_T _var_name = var_name;
   cClientData * client_data =  cClients::GetClientData(client_id);
   CONTEXT_REF->RefFilter(client_data->get_IFType(), _var_name, i1, i2, i3, i4);
   CONTEXT_REF->GetMinimum(_var_name.c_str(), value, i1, i2, i3, i4);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::GetMinimumById(long client_id, long var_id, long i1, long i2, long i3, long i4)
{
CORBA_OBJECT_PROLOG("iCellObject::GetMinimum")
SET_USER_INFO(client_id)
   STRING_T value = "not supprted";
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::GetMaximum(long client_id, const char * var_name, long i1, long i2, long i3, long i4)
{
CORBA_OBJECT_PROLOG("iCellObject::GetMaximum")
SET_USER_INFO(client_id)
   STRING_T value;
   STRING_T _var_name = var_name;
   cClientData * client_data =  cClients::GetClientData(client_id);
   CONTEXT_REF->RefFilter(client_data->get_IFType(), _var_name, i1, i2, i3, i4);
   CONTEXT_REF->GetMaximum(_var_name.c_str(), value, i1, i2, i3, i4);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::GetMaximumById(long client_id, long var_id, long i1, long i2, long i3, long i4)
{
CORBA_OBJECT_PROLOG("iCellObject::GetMaximum")
SET_USER_INFO(client_id)
   STRING_T value = "not supprted";
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::ReadFile(long client_id, const char * file_name, const char * sub_files)
{
CORBA_OBJECT_PROLOG("iCellObject::ReadFile")
SET_USER_INFO(client_id)
   STRING_T buf;
   CONTEXT_REF->ReadFile(file_name, sub_files, buf);
   return CORBA_STRING_DUP(buf.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

char * iCellObject::ExportVariables(long client_id, const char * sub_file, const char * separator)
{
CORBA_OBJECT_PROLOG("iCellObject::ExportVariables")
SET_USER_INFO(client_id)
   STRING_T buf;
   CONTEXT_REF->ExportVariables(buf, sub_file, separator);
   return CORBA_STRING_DUP(buf.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::WriteFile(long client_id, const char * file_name, const char * sub_files, const char * buf)
{
CORBA_OBJECT_PROLOG("iCellObject::WriteFile")
SET_USER_INFO(client_id)
   CONTEXT_REF->WriteFile(file_name, sub_files, buf);
CORBA_OBJECT_EPILOG
}

char * iCellObject::GetParam(long client_id, const char* param_name)
{
CORBA_OBJECT_PROLOG("iCellObject::GetParam")
SET_USER_INFO(client_id)
   STRING_T value;
   CONTEXT_REF->GetParam(param_name, value);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::SetParam(long client_id, const char* param_name, const char* value)
{
CORBA_OBJECT_PROLOG("iCellObject::SetParam")
SET_USER_INFO(client_id)
   CONTEXT_REF->SetParam(param_name, value);
CORBA_OBJECT_EPILOG
}

unsigned long iCellObject::AlarmCount(long client_id, unsigned long selection)
{
CORBA_OBJECT_PROLOG("iCellObject::AlarmCount")
SET_USER_INFO(client_id)
	return CONTEXT_REF->Alarms(selection);
CORBA_OBJECT_EPILOG
   return 0;
}

string_list_t iCellObject::Alarms(long client_id, unsigned long selection)
{
CORBA_OBJECT_PROLOG("iCellObject::Alarms")
SET_USER_INFO(client_id)
	return CORBA_STRING_DUP("not implemented");
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::ClearAlarm(long client_id, long ident)
{
CORBA_OBJECT_PROLOG("iCellObject::ClearAlarm")
SET_USER_INFO(client_id)
   CONTEXT_REF->ClearAlarm(ident, true);
CORBA_OBJECT_EPILOG
}

void iCellObject::ClearAlarms(long client_id)
{
CORBA_OBJECT_PROLOG("iCellObject::ClearAlarms")
SET_USER_INFO(client_id)
   CONTEXT_REF->ClearAlarms(true);
CORBA_OBJECT_EPILOG
}

void iCellObject::ExecuteCommand(long client_id, const char * program_name, unsigned long command)
{
CORBA_OBJECT_PROLOG("iCellObject::ExecuteCommand")
SET_USER_INFO(client_id)
   CONTEXT_REF->ExecuteCommand(program_name, command);
CORBA_OBJECT_EPILOG
}

char * iCellObject::ExecuteRequest(long client_id, const char * program_name, const char * request)
{
CORBA_OBJECT_PROLOG("iCellObject::ExecuteRequest")
SET_USER_INFO(client_id)
   STRING_T reply;
   CONTEXT_REF->ExecuteRequest(program_name, reply, request);
   return CORBA_STRING_DUP(reply.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::SetJobX(long client_id, const char * job_spec)
{
CORBA_OBJECT_PROLOG("iCellObject::SetJob")
SET_USER_INFO(client_id)
   CONTEXT_REF->SetJob(job_spec);
CORBA_OBJECT_EPILOG
}

char * iCellObject::GetJobSpec(long client_id, const char * job_name)
{
CORBA_OBJECT_PROLOG("iCellObject::GetJobSpec")
SET_USER_INFO(client_id)
   STRING_T value = CONTEXT_REF->GetJobSpecText(job_name);
   return CORBA_STRING_DUP(value.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

long iCellObject::Login(client_info_t client_info, const char * password)
{
CORBA_OBJECT_PROLOG("iCellObject::Login")
   cClientData * client_data = cClients::AllocClient(client_info, password, 0);
   if (client_data != NULL) {
      return client_data->get_Id();
   }
CORBA_OBJECT_EPILOG
   return 0;
}

long iCellObject::LoginIfType(client_info_t client_info, const char * password, ULONG_T if_type)
{
CORBA_OBJECT_PROLOG("iCellObject::Login")
   cClientData * client_data = cClients::AllocClient(client_info, password, if_type);
   if (client_data != NULL) {
      return client_data->get_Id();
   }
CORBA_OBJECT_EPILOG
   return 0;
}

void iCellObject::Logout(long client_id)
{
CORBA_OBJECT_PROLOG("iCellObject::Logout")
SET_USER_INFO(client_id)
   cClients::RemoveClient(client_id);
CORBA_OBJECT_EPILOG
}

void iCellObject::SetUserInfo(long client_id, user_info_t user_info)
{
CORBA_OBJECT_PROLOG("iCellObject::SetUserInfo")
SET_USER_INFO(client_id)
CORBA_OBJECT_EPILOG
}

char * iCellObject::GetEvent(long client_id)
{
/// PR 18.03.06 there is no need for shelter through _CorbaObjectMutex
///             but shelter will block all other methods
CORBA_OBJECT_PROLOG_NO_LOCK("iCellObject::GetEvent")
SET_USER_INFO(client_id)
   cClientData * client_data = cClients::GetClientData(client_id);
   if (client_data != NULL) {
      STRING_T value = client_data->GetEvent();
      return CORBA_STRING_DUP(value.c_str());
   }
CORBA_OBJECT_EPILOG
   return NULL;
}

Control::Memory * iCellObject::GetMemory(long client_id, unsigned long address, unsigned long size)
{
CORBA_OBJECT_PROLOG("iCellObject::GetMemory")
SET_USER_INFO(client_id)
   Control::Memory * buffer = new Control::Memory(size);
   buffer->length(size);
   int len = buffer->length();
   BUF_T ptr = (BUF_T)address;
   for (int i=0; i<len; i++) {
      CORBA::Octet a = (*buffer)[i];
      (*buffer)[i] = ptr[i];
   }
   return buffer;
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::SendObject(long client_id, const char * serialized_obj)
{
CORBA_OBJECT_PROLOG("iCellObject::SendObject")
SET_USER_INFO(client_id)
   cTransientObject * obj = NULL;
   if (strlen(serialized_obj) > 0) {
      obj = cTransientObject::Parse(serialized_obj);
      if (obj != NULL) {
   	   CONTEXT_REF->Send(obj);
         obj->Release();
      }
   }
CORBA_OBJECT_EPILOG
}


char * iCellObject::Request(long client_id, const char * request)
{
CORBA_OBJECT_PROLOG("iCellObject::Request")
SET_USER_INFO(client_id)
CORBA_OBJECT_EPILOG
   return NULL;
}

char* iCellObject::GetRing(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags)
{
   STRING_T objects;
CORBA_OBJECT_PROLOG("iCellObject::GetRing")
   cBinaryObject ring_object;
   CONTEXT_REF->GetObject(var_name, ring_object, i1, i2, i3, i4, flags|VF_MEMORY_ACCESS);
   BUF_T buf = ring_object.Data();
   ULONG_T bufsize = ring_object.Size();
   cExtendedObjectRing ring(buf, bufsize);
   cObjectLock __lock__(ring.RingMutex());
   ULONG_T used = ring.Used();
   for (int i=used-1; i>=0; i--) {
      cTransientObject * object = ring.GetObject(i);
      if (object != NULL) {
         STRING_T serialized_object = object->Serialize();
         objects += serialized_object;
         objects += "\01";
         object->Release();
      }
   }
   return CORBA_STRING_DUP(objects.c_str());
CORBA_OBJECT_EPILOG
   return NULL;
}

Control::Memory* iCellObject::GetObject(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags)
{
CORBA_OBJECT_PROLOG("iCellObject::GetObject")
SET_USER_INFO(client_id)
   STRING_T _var_name = var_name;
   cClientData * client_data =  cClients::GetClientData(client_id);
   CONTEXT_REF->RefFilter(client_data->get_IFType(), _var_name, i1, i2, i3, i4);
   cBinaryObject object;
   CONTEXT_REF->GetObject(_var_name.c_str(), object, i1, i2, i3, i4, flags|VF_MEMORY_ACCESS);
   ULONG_T size = object.Size();
   unsigned char * data = object.Data();
   Control::Memory * buffer = new Control::Memory(size);
   buffer->length(size);
   ULONG_T i = 0;
   for (i=0; i<size; i++) {
      CORBA::Octet a = (*buffer)[i];
      (*buffer)[i] = data[i];
   }
   return buffer;
CORBA_OBJECT_EPILOG
   return NULL;
}

void iCellObject::SetObject(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags, const Control::Memory& binary_object)
{
CORBA_OBJECT_PROLOG("iCellObject::GetObject")
SET_USER_INFO(client_id)
   ULONG_T size = binary_object.length();
   BUF_T buffer = (BUF_T)calloc(1, size);
   ULONG_T i = 0;
   for (i=0; i<size; i++) {
      buffer[i] = binary_object[i];
   }
   cBinaryObject object(buffer, size);
   CONTEXT_REF->SetObject(var_name, object, i1, i2, i3, i4, flags|VF_MEMORY_ACCESS);
   free(buffer);
CORBA_OBJECT_EPILOG
}

void iCellObject::ExecuteJob(long client_id, const char * program_name, const char * job, CORBA::Long async)
{
CORBA_OBJECT_PROLOG("iCellObject::ExecuteJob")
SET_USER_INFO(client_id)
   CONTEXT_REF->ExecuteJob(program_name, job, async == 0 ? false : true);
CORBA_OBJECT_EPILOG
}

