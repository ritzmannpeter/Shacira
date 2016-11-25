
#ifndef EM63Program_h
#define EM63Program_h 1

#include "Language\cEM63StyxParser.h"
#include "Control/Cell/cEM63Program.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cEM63Interface;

class __DLL_EXPORT__ EM63Program : public cEM63Program
{
public:
   EM63Program (cConfigurationObject * config_obj, cContext *context);
   virtual ~EM63Program();
protected:
   virtual void ProcessEvent (cTransientObject *object);
   virtual void Initialize();
   virtual STRING_T RootDirectory ();
   virtual STRING_T SessionDirectory ();
   virtual STRING_T LD ();
   virtual STRING_T DatasetId (CONST_STRING_T keyword);
   virtual STRING_T ShotCounterId ();
   virtual LONG_T ShotCounterValue ();
   virtual ULONG_T InjUnitNbrValue ();
   virtual STRING_T MoldNbrValue ();
   virtual STRING_T MachNbrValue ();
   virtual STRING_T MaterialNbrValue ();
   virtual STRING_T MachVendor ();
   virtual STRING_T MachDesc ();
   virtual STRING_T ContrType ();
   virtual STRING_T ContrVersion ();
   virtual ULONG_T MaxJobs ();
   virtual ULONG_T MaxChanges ();
   virtual ULONG_T MaxAlarms ();
   virtual ULONG_T MaxCurrentAlarms ();
   virtual ULONG_T MaxReports ();
   virtual ULONG_T MaxArchives ();
   virtual ULONG_T MaxSessions ();
   virtual STRING_T CharDef ();
   virtual STRING_T Version ();
};

#endif
