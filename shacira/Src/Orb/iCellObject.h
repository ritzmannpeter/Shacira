//---------------------------------------------------------------------------
#ifndef iCellObjectH
#define iCellObjectH
#include "CorbaDefinitions.h"
//---------------------------------------------------------------------------

#define CELL_OBJECT_KEY    "ShaciraCellObject"

typedef const char * client_info_t;
typedef const char * user_info_t;
typedef char * string_list_t;

class iCellObject: public POA_Control::iCell
{
protected:
public:
   iCellObject(const char *object_name=NULL, void * link=NULL);
   virtual ~iCellObject();
   void Remove();
	STRING_T IOR();
   char * Name();
	char * GetVarDefs(long client_id, long if_type);
   long GetId(long client_id, const char * var_name);

   char * GetValue(long client_id, const char * var_name, long i1, long i2, long i3, long i4, long flags);
   char * GetValueById(long client_id, long var_id, long i1, long i2, long i3, long i4, long flags);
   void Refresh(long client_id, const char * var_name, long i1, long i2, long i3, long i4, long flags);
   void RefreshById(long client_id, long var_id, long i1, long i2, long i3, long i4, long flags);
   void SetValue(long client_id, const char * var_name, const char * value, long i1, long i2, long i3, long i4, long flags);
   void SetValueById(long client_id, long var_id, const char * value, long i1, long i2, long i3, long i4, long flags);

   char * GetMinimum(long client_id, const char * var_name, long i1, long i2, long i3, long i4);
   char * GetMinimumById(long client_id, long var_id, long i1, long i2, long i3, long i4);
   char * GetMaximum(long client_id, const char * var_name, long i1, long i2, long i3, long i4);
   char * GetMaximumById(long client_id, long var_id, long i1, long i2, long i3, long i4);

   char * ReadFile(long client_id, const char* file_name, const char * sub_files);
   void WriteFile(long client_id, const char* file_name, const char * sub_files, const char* buf);

   char * GetParam(long client_id, const char * param_name);
   void SetParam(long client_id, const char * param_name, const char * value);
   unsigned long AlarmCount(long client_id, unsigned long selection);
   string_list_t Alarms(long client_id, unsigned long selection);
   void ClearAlarm(long client_id, long ident);
   void ClearAlarms(long client_id);

   void ExecuteCommand(long client_id, const char * program_name, unsigned long command);
   char * ExecuteRequest(long client_id, const char * program_name, const char * request);
   void SetJobX(long client_id, const char * job_spec);
   char * GetJobSpec(long client_id, const char * job_name);

   long Login(client_info_t client_info, const char * password);
   void Logout(long client_id);
   void SetUserInfo(long client_id, user_info_t user_info);

   char * GetEvent(long client_id);
   Control::Memory * GetMemory(long client_id, unsigned long address, unsigned long size);
   void SendObject(long client_id, const char * serialized_obj);
   char * Request(long client_id, const char * request);
   char* GetRing(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags);
   Control::Memory* GetObject(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags);
   void SetObject(CORBA::Long client_id, const char* var_name, CORBA::Long i1, CORBA::Long i2, CORBA::Long i3, CORBA::Long i4, CORBA::Long flags, const Control::Memory& binary_object);
   void ExecuteJob(long client_id, const char * program_name, const char * job, CORBA::Long async);

private:
	STRING_T _IOR;
   bool _Removed;
   void * _Link;
   CORBA_OBJECT_SEMAPHORE
};
#endif
