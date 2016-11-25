//## begin module%3EDDCAEC005D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDDCAEC005D.cm

//## begin module%3EDDCAEC005D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EDDCAEC005D.cp

//## Module: cLocalContext%3EDDCAEC005D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cLocalContext.h

#ifndef cLocalContext_h
#define cLocalContext_h 1

//## begin module%3EDDCAEC005D.includes preserve=yes

//## end module%3EDDCAEC005D.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"
// cContext
#include "System/Database/cContext.h"
// cMapping
#include "System/Database/cMapping.h"

class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cJobSpec;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cFileContext;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cInternalBridge;
class __DLL_EXPORT__ cLocalChannel;
class __DLL_EXPORT__ cProgramFactory;
class __DLL_EXPORT__ cProgram;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cJobManager;
class __DLL_EXPORT__ cLocalVariable;
class __DLL_EXPORT__ cPersistenceChannel;
class __DLL_EXPORT__ cSubFile;
class __DLL_EXPORT__ cDevice;
class __DLL_EXPORT__ cCorbaCellProxy;
class __DLL_EXPORT__ cBroker;
class __DLL_EXPORT__ cStyxParser;
class __DLL_EXPORT__ cPersistenceManager;
class __DLL_EXPORT__ iCellObject;

//## begin module%3EDDCAEC005D.additionalDeclarations preserve=yes

typedef std::map<ULONG_T,STRING_T> HOSTITF_CACHE_T;

/// run levels and run flags
#define RF_BBRAM_INITIALIZED        0x00000001

/// corba service for delayed activation
class cObjectService;

//## end module%3EDDCAEC005D.additionalDeclarations


//## begin cLocalContext%3EDDCAEC005D.preface preserve=yes
//## end cLocalContext%3EDDCAEC005D.preface

//## Class: cLocalContext%3EDDCAEC005D
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EDDCBF3008C;cLocalVariable { -> F}
//## Uses: <unnamed>%3EDDCC230177;cVarDef { -> F}
//## Uses: <unnamed>%3FE7239601C5;cMapping { -> F}
//## Uses: <unnamed>%40B4904E0109;cDevice { -> F}
//## Uses: <unnamed>%41121296036B;cSubFile { -> F}
//## Uses: <unnamed>%4113C9C40261;cFileContext { -> F}
//## Uses: <unnamed>%4113CC070128;cStyxParser { -> F}
//## Uses: <unnamed>%42E73F47035B;cCustomFunctions { -> }
//## Uses: <unnamed>%42E75D76008C;cFileSystemUtils { -> F}
//## Uses: <unnamed>%42E75E4C0196;cLocalChannel { -> F}
//## Uses: <unnamed>%42E76289034B;cInternalBridge { -> F}
//## Uses: <unnamed>%42E7C29B0148;cInfo { -> F}
//## Uses: <unnamed>%42E7C7D601F4;cCorbaCellProxy { -> F}
//## Uses: <unnamed>%42E7C81F0000;cSHProcess { -> F}
//## Uses: <unnamed>%42E7C900033C;cProgramFactory { -> F}
//## Uses: <unnamed>%42E8721901E4;cJobSpec { -> F}
//## Uses: <unnamed>%4305EC8A000F;cBroker { -> F}
//## Uses: <unnamed>%437A02B002C1;cIniFile { -> F}
//## Uses: <unnamed>%45D1EF9A0148;cMapping { -> }

class __DLL_EXPORT__ cLocalContext : public cContext  //## Inherits: <unnamed>%3EDDCB1F0232
{
  //## begin cLocalContext%3EDDCAEC005D.initialDeclarations preserve=yes
private:
   iCellObject * _CellObject;
public:
  //## end cLocalContext%3EDDCAEC005D.initialDeclarations

    //## Constructors (generated)
      cLocalContext();

      cLocalContext(const cLocalContext &right);

    //## Constructors (specified)
      //## Operation: cLocalContext%1122450441
      cLocalContext (cSHProcess *process, cConfigurationObject *config_obj, BOOL_T client_context = false);
      cLocalContext (cSHProcess *process);

    //## Destructor (generated)
      virtual ~cLocalContext();


    //## Other Operations (specified)
      //## Operation: IsRemote%1054715290
      //	Is this Context a remote context ?
      virtual BOOL_T IsRemote ();

      //## Operation: Start%1122450442
      virtual void Start ();

      //## Operation: Stop%1122450443
      virtual void Stop ();

      //## Operation: ActivateCorbaObject%1163011502
      virtual BOOL_T ActivateCorbaObject ();

      //## Operation: Create%1054715292
      //	Creates necessary resources.
      virtual void Create ();

      //## Operation: CreateDynamic%1090073690
      virtual void CreateDynamic ();

      //## Operation: GetVarDefs%1054726258
      //	Gets all variable definitions as a list of serialized
      //	objects.
      ULONG_T GetVarDefs (STRING_T &var_defs, ULONG_T if_type = 0);

      //## Operation: Cell%1081425823
      virtual cCell * Cell ();

      //## Operation: EventChannel%1073299990
      virtual cChannel * EventChannel ();

      //## Operation: Alarms%1089103362
      virtual ULONG_T Alarms (ULONG_T selection);

      //## Operation: Alarms%1081425828
      virtual ULONG_T Alarms (ULONG_T selection, ALARM_MAP_T &alarms);

      //## Operation: ClearAlarm%1081425829
      virtual void ClearAlarm (ULONG_T ident, BOOL_T propagate = true);

      //## Operation: ClearAlarms%1081425830
      virtual void ClearAlarms (BOOL_T propagate = true);

      //## Operation: GetDeviceValue%1082984460
      //	Retrieves a value of a variable directly from a device.
      virtual void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value);

      //## Operation: SetDeviceValue%1082984461
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value);

      //## Operation: Device%1085574712
      //	Returns a pointer to the device named name if available,
      //	returns NULL if a device with that name is not available.
      virtual cDevice * Device (CONST_STRING_T name);

      //## Operation: ExecuteCommand%1089292613
      //	Executes a command on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteCommand (CONST_STRING_T program_name, ULONG_T command);

      //## Operation: ExecuteRequest%1133771768
      //	Executes a request on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request);

      //## Operation: Save%1092293195
      virtual void Save (UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Download%1091687832
      //	The download method activates a download of all device
      //	data hold in a database.
      virtual void Download (ULONG_T ctrl = 0);

      //## Operation: Upload%1091687833
      //	The upload method activates an upload of all device data
      //	hold in devices.
      virtual void Upload (ULONG_T ctrl = 0);

      //## Operation: ReadFile%1091699605
      virtual void ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, STRING_T &buf);
      // cStringBuffer type of the ReadFile method 
      virtual void ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, cStringBuffer &buf);

      //## Operation: WriteFile%1091699606
      virtual void WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_file, CONST_STRING_T buf);

      //## Operation: Copy%1102418726
      virtual void Copy (cContext *src_context, CONST_STRING_T sub_file, BOOL_T show_errors=true, BOOL_T buffered = true);

      //## Operation: LoadVariables%1084445993
      void LoadVariables ();

      //## Operation: SaveVariables%1091180972
      void SaveVariables ();

      //## Operation: SetJob%1093930661
      virtual void SetJob (cJobSpec *job_spec);

      //## Operation: GetJobSpec%1093930662
      virtual cJobSpec * GetJobSpec (CONST_STRING_T job_name);

      //## Operation: CopyCommand%1100714371
      virtual void CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags = 0);

      //## Operation: Compare%1108566002
      virtual STRING_T Compare (ULONG_T flags = 0);

      //## Operation: SetAlarm%1122475152
      BOOL_T SetAlarm (cAlarm *alarm);

      //## Operation: Alarm%1122475153
      cAlarm * Alarm (ULONG_T ident);

      //## Operation: Send%1122475164
      virtual void Send (cTransientObject *object);

      //## Operation: Program%1122475166
      cProgram * Program (CONST_STRING_T name);

      //## Operation: SetJob%1122529737
      void SetJob (CONST_STRING_T job_spec);

      //## Operation: GetJobSpecText%1122529738
      STRING_T GetJobSpecText (CONST_STRING_T job_name);

      //## Operation: PersistenceChannel%1122619258
      //	Returns the persistence channel object associated with
      //	the context.
      virtual cPersistenceChannel * PersistenceChannel ();

      //## Operation: Initialize%1122450440
      BOOL_T Initialize (ULONG_T step);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CorbaService%42E73CF701E4
      BOOL_T get_CorbaService () const;
      void set_CorbaService (BOOL_T value);

      //## Attribute: ForceCorbaService%4552251A0148
      BOOL_T get_ForceCorbaService () const;
      void set_ForceCorbaService (BOOL_T value);

      //## Attribute: SkipNetworks%4561ECB3030D
      STRING_VECTOR_T get_SkipNetworks () const;
      void set_SkipNetworks (STRING_VECTOR_T value);

      //## Attribute: IsClientContext%42EFABD70109
      BOOL_T get_IsClientContext () const;
      void set_IsClientContext (BOOL_T value);

      //## Attribute: RunLevel%43D9C40502F3
      ULONG_T get_RunLevel () const;

      //## Attribute: RunFlags%43D9C42F0264
      ULONG_T get_RunFlags () const;

    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%3EDDE2760399
      //## Role: cLocalContext::Cell%3EDDE27802CE
      //## begin cLocalContext::Cell%3EDDE27802CE.role preserve=no  public: cCell {1 -> 1RFHN}
      cCell *_Cell;
      //## end cLocalContext::Cell%3EDDE27802CE.role

  public:
    // Additional Public Declarations
      //## begin cLocalContext%3EDDCAEC005D.public preserve=yes
      cPersistenceManager * PersistenceManager() const;
      //## end cLocalContext%3EDDCAEC005D.public

  protected:
    // Data Members for Class Attributes

      //## begin cLocalContext::CorbaService%42E73CF701E4.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _CorbaService;
      //## end cLocalContext::CorbaService%42E73CF701E4.attr

      //## begin cLocalContext::ForceCorbaService%4552251A0148.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ForceCorbaService;
      //## end cLocalContext::ForceCorbaService%4552251A0148.attr

      //## begin cLocalContext::SkipNetworks%4561ECB3030D.attr preserve=no  public: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _SkipNetworks;
      //## end cLocalContext::SkipNetworks%4561ECB3030D.attr

      //## begin cLocalContext::IsClientContext%42EFABD70109.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsClientContext;
      //## end cLocalContext::IsClientContext%42EFABD70109.attr

      //## begin cLocalContext::RunLevel%43D9C40502F3.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RunLevel;
      //## end cLocalContext::RunLevel%43D9C40502F3.attr

      //## begin cLocalContext::RunFlags%43D9C42F0264.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RunFlags;
      //## end cLocalContext::RunFlags%43D9C42F0264.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%42E761F800CB
      //## Role: cLocalContext::JobManager%42E761F803D8
      //## begin cLocalContext::JobManager%42E761F803D8.role preserve=no  public: cJobManager { -> 0..1RFHN}
      cJobManager *_JobManager;
      //## end cLocalContext::JobManager%42E761F803D8.role

      //## Association: Control::Cell::<unnamed>%42E7C13C03C8
      //## Role: cLocalContext::Programs%42E7C13D03A9
      //## Qualifier: name%42E7C1800128; STRING_T
      //## begin cLocalContext::Programs%42E7C13D03A9.role preserve=no  public: cProgram { -> 0..1RFHN}
      std::map<STRING_T, cProgram*> _Programs;
      //## end cLocalContext::Programs%42E7C13D03A9.role

      //## Association: Control::Cell::<unnamed>%42E7C08E037A
      //## Role: cLocalContext::PersistenceChannel%42E7C08F0261
      //## begin cLocalContext::PersistenceChannel%42E7C08F0261.role preserve=no  public: cPersistenceChannel { -> 1RFHN}
      cPersistenceChannel *_PersistenceChannel;
      //## end cLocalContext::PersistenceChannel%42E7C08F0261.role

    // Additional Protected Declarations
      //## begin cLocalContext%3EDDCAEC005D.protected preserve=yes
      //## end cLocalContext%3EDDCAEC005D.protected

  private:
    // Additional Private Declarations
      //## begin cLocalContext%3EDDCAEC005D.private preserve=yes
      //## end cLocalContext%3EDDCAEC005D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartServices%1122475148
      void StartServices ();

      //## Operation: StopServices%1122475149
      void StopServices ();

      //## Operation: StartPrograms%1122475150
      void StartPrograms ();

      //## Operation: StopPrograms%1122475151
      void StopPrograms ();

      //## Operation: CreatePersistenceChannel%1138346769
      void CreatePersistenceChannel ();

      //## Operation: CreatePrograms%1138346770
      void CreatePrograms ();

      //## Operation: SetCellName%1138346771
      void SetCellName ();

      //## Operation: CreateProgram%1122475158
      void CreateProgram (cConfigurationObject *program_obj, cContext *context);

      //## Operation: PrintIOR%1132068351
      void PrintIOR (CONST_STRING_T context_name, CONST_STRING_T ior);

      //## Operation: VarDefFilter%1132999007
      ULONG_T VarDefFilter (cContext *context, ULONG_T if_type, cVarDef *var_def);

      //## Operation: ActiveAlarm%1170178867
      cAlarm * ActiveAlarm (ALARM_MAP_T &alarms);

      //## Operation: CheckMapping%1171386481
      void CheckMapping (STRING_MAP_T &id_map, cDevice *device, cVarDef *var_def, cMapping *mapping, int pos);

    // Data Members for Class Attributes

      //## Attribute: MdlInitFuncAddress%42E73D8C037A
      //## begin cLocalContext::MdlInitFuncAddress%42E73D8C037A.attr preserve=no  implementation: MDL_INIT_FUNC_T {U} NULL
      MDL_INIT_FUNC_T _MdlInitFuncAddress;
      //## end cLocalContext::MdlInitFuncAddress%42E73D8C037A.attr

      //## Attribute: AlarmMap%42E7B5D40000
      //## begin cLocalContext::AlarmMap%42E7B5D40000.attr preserve=no  implementation: ALARM_MAP_T {U} 
      ALARM_MAP_T _AlarmMap;
      //## end cLocalContext::AlarmMap%42E7B5D40000.attr

      //## Attribute: AlarmMutex%42E7B5D4000F
      //## begin cLocalContext::AlarmMutex%42E7B5D4000F.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _AlarmMutex;
      //## end cLocalContext::AlarmMutex%42E7B5D4000F.attr

      //## Attribute: IORDirectory%4379FFB30277
      //## begin cLocalContext::IORDirectory%4379FFB30277.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _IORDirectory;
      //## end cLocalContext::IORDirectory%4379FFB30277.attr

      //## Attribute: IORFile%4379FFC20083
      //## begin cLocalContext::IORFile%4379FFC20083.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _IORFile;
      //## end cLocalContext::IORFile%4379FFC20083.attr

      //## Attribute: PrintIOR%437B213B00C3
      //## begin cLocalContext::PrintIOR%437B213B00C3.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _PrintIOR;
      //## end cLocalContext::PrintIOR%437B213B00C3.attr

      //## Attribute: VarDefFilterFuncAddress%438831300244
      //## begin cLocalContext::VarDefFilterFuncAddress%438831300244.attr preserve=no  implementation: static VARDEF_FILTER_T {U} NULL
      static VARDEF_FILTER_T _VarDefFilterFuncAddress;
      //## end cLocalContext::VarDefFilterFuncAddress%438831300244.attr

      //## Attribute: HostItfCache%438837020108
      //## begin cLocalContext::HostItfCache%438837020108.attr preserve=no  implementation: static HOSTITF_CACHE_T {U} 
      static HOSTITF_CACHE_T _HostItfCache;
      //## end cLocalContext::HostItfCache%438837020108.attr

      //## Attribute: ConfigObject%43D9C671024C
      //## begin cLocalContext::ConfigObject%43D9C671024C.attr preserve=no  implementation: cConfigurationObject * {U} NULL
      cConfigurationObject *_ConfigObject;
      //## end cLocalContext::ConfigObject%43D9C671024C.attr

      //## Attribute: ObjectService%4552253901C5
      //## begin cLocalContext::ObjectService%4552253901C5.attr preserve=no  implementation: cObjectService * {U} NULL
      cObjectService *_ObjectService;
      //## end cLocalContext::ObjectService%4552253901C5.attr

      //## Attribute: CorbaObjectActive%4552255B01F4
      //## begin cLocalContext::CorbaObjectActive%4552255B01F4.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _CorbaObjectActive;
      //## end cLocalContext::CorbaObjectActive%4552255B01F4.attr

      cPersistenceManager *_ShadowManager;

    // Additional Implementation Declarations
      //## begin cLocalContext%3EDDCAEC005D.implementation preserve=yes
      cMutexSem _DataFileMutex;
      //## end cLocalContext%3EDDCAEC005D.implementation

public:
   /// extensions for emitting startup data changes
   void EmitChanges();
   void PersistShadowDataset();
   void CheckShadowDataset();
   virtual void ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async = false);

};

//## begin cLocalContext%3EDDCAEC005D.postscript preserve=yes
//## end cLocalContext%3EDDCAEC005D.postscript

// Class cLocalContext 

//## begin module%3EDDCAEC005D.epilog preserve=yes
//## end module%3EDDCAEC005D.epilog


#endif
