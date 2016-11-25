//## begin module%43A2BA9F0287.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A2BA9F0287.cm

//## begin module%43A2BA9F0287.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A2BA9F0287.cp

//## Module: cEM63Interface%43A2BA9F0287; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Interface.h

#ifndef cEM63Interface_h
#define cEM63Interface_h 1

//## begin module%43A2BA9F0287.includes preserve=yes

#undef COUNT_EUROMAP63_OBJECTS
#ifdef COUNT_EUROMAP63_OBJECTS
#define    INCREMENT_OBJECT_COUNT() cEM63Interface::IncrementObjectCount(typeid(*this).name());
#define    DECREMENT_OBJECT_COUNT() cEM63Interface::DecrementObjectCount(typeid(*this).name());
#else
#define    INCREMENT_OBJECT_COUNT()
#define    DECREMENT_OBJECT_COUNT()
#endif

#include "Euromap63.h"

//## end module%43A2BA9F0287.includes

// cVariable
#include "System/Database/cVariable.h"
// cAbstractFileSystem
#include "System/Sys/cAbstractFileSystem.h"
// cBufferedFile
#include "System/Sys/cBufferedFile.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"

class __DLL_EXPORT__ cTimeObject;
class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cInterfaceFilter;
class __DLL_EXPORT__ cEM63Program;
class __DLL_EXPORT__ cEventlogCmd;
class __DLL_EXPORT__ cPresentationCmd;

//## begin module%43A2BA9F0287.additionalDeclarations preserve=yes

typedef std::list<cEM63Job*> JOB_LIST_T;

typedef std::map<STRING_T,cEM63Job*> JOB_MAP_T;
typedef std::map<STRING_T,cPresentationCmd*> CMD_MAP_T;
typedef std::list<cPresentationCmd*> CMD_LIST_T;

typedef std::map<ULONG_T,cEM63Session*> SESSION_MAP_T;
typedef std::list<cEM63Session*> SESSION_LIST_T;

typedef struct _param_spec {
   cVarRef * var_ref;
   char param_id[PARAM_ID_SIZE + 1];
   UCHAR_T data_type;
   ULONG_T length;
   UCHAR_T precision;
   UCHAR_T access_rights;
   char unit[UNIT_SIZE + 1];
   char comment[DESCRIPTION_SIZE + 1];
   char dim1Text[DIMTEXT_SIZE +1];
   char dim2Text[DIMTEXT_SIZE +1];
   char dim3Text[DIMTEXT_SIZE +1];
   char dim4Text[DIMTEXT_SIZE +1];
   char var_name[PARAM_ID_SIZE + 1];
   int dims;
   long i1, i2, i3, i4;
}  PARAM_SPEC_T;
typedef std::map<STRING_T,PARAM_SPEC_T*> PARAM_SPEC_MAP_T;

typedef struct _em63_error_description {
   ULONG_T code;
   const char * description;
}  EM63_ERR_DESCRIPTION_T;

typedef std::map<STRING_T,STRING_T> VAR_SPEC_MAP_T;

#define EM63_LOGGING_INTERFACE

/// log categories
#define CAT_SYNC              0x00000001
#define CAT_ASYNC             0x00000002

/// log operations
#define OP_GENERAL            0
#define OP_SCAN               1
#define OP_PUT                2
#define OP_GET                3
#define OP_RENAME             4
#define OP_PROCESS_CMD        5
#define OP_START_CMD          6
#define OP_STOP_CMD           7
#define OP_TERMINATE_CMD      8
#define OP_ABORT_CMD          9

//## end module%43A2BA9F0287.additionalDeclarations


//## begin cEM63Interface%43A2BA9F0287.preface preserve=yes
//## end cEM63Interface%43A2BA9F0287.preface

//## Class: cEM63Interface%43A2BA9F0287
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A2BDA90120;cEM63Session { -> }
//## Uses: <unnamed>%43A950160237;cStringUtils { -> F}
//## Uses: <unnamed>%43AACD8B0074;cTimeObject { -> F}
//## Uses: <unnamed>%43B2652E00DD;cVarRef { -> F}
//## Uses: <unnamed>%43B5663003C0;cVariable { -> }
//## Uses: <unnamed>%43B566350239;cVariable { -> F}
//## Uses: <unnamed>%43BE5F5B02C0;cPresentationCmd { -> F}
//## Uses: <unnamed>%43BE858203C5;cTransientObject { -> F}
//## Uses: <unnamed>%43BE8AE50023;cEventlogCmd { -> F}
//## Uses: <unnamed>%44081A7703B7;cAbstractFileSystem { -> }
//## Uses: <unnamed>%440884100146;cBufferedFile { -> }
//## Uses: <unnamed>%440C6FBF00B5;cInterfaceFilter { -> F}

class __DLL_EXPORT__ cEM63Interface 
{
  //## begin cEM63Interface%43A2BA9F0287.initialDeclarations preserve=yes
public:
  //## end cEM63Interface%43A2BA9F0287.initialDeclarations

    //## Constructors (generated)
      cEM63Interface();

      cEM63Interface(const cEM63Interface &right);

    //## Constructors (specified)
      //## Operation: cEM63Interface%1136191745
      cEM63Interface (cEM63Program *program);

    //## Destructor (generated)
      virtual ~cEM63Interface();


    //## Other Operations (specified)
      //## Operation: SetEvent%1136559695
      void SetEvent (cTransientObject *object);

      //## Operation: SetContext%1135947275
      void SetContext (cContext *context);

      //## Operation: AddSession%1134738525
      ULONG_T AddSession (cEM63Session *session);

      //## Operation: SessionCount%1135162870
      ULONG_T SessionCount ();

      //## Operation: Start%1135272167
      void Start ();

      //## Operation: Control%1135177952
      void Control ();

      //## Operation: Stop%1135773616
      void Stop ();

      //## Operation: CleanUp%1136213365
      void CleanUp ();

      //## Operation: Abort%1136213369
      void Abort (int abort_type, CONST_STRING_T name);

      //## Operation: Time%1135258643
      static STRING_T Time (ULONG_T time);

      //## Operation: Date%1135258644
      static STRING_T Date (ULONG_T time);

      //## Operation: AddParamSpec%1135761104
      void AddParamSpec (cVarRef *var_ref, CONST_STRING_T param_id, UCHAR_T data_type, ULONG_T length, UCHAR_T precision, UCHAR_T access_rights, CONST_STRING_T unit, CONST_STRING_T comment, CONST_STRING_T dim1_text, CONST_STRING_T dim2_text, CONST_STRING_T dim3_text, CONST_STRING_T dim4_text, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: GetParamSpecs%1135761105
      void GetParamSpecs (PARAM_SPEC_MAP_T &param_specs);

      //## Operation: ParamExists%1135773612
      BOOL_T ParamExists (CONST_STRING_T param_id);

      //## Operation: ParamIsWriteable%1135788723
      BOOL_T ParamIsWriteable (CONST_STRING_T param_id);

      //## Operation: GetParamValue%1135773613
      int GetParamValue (CONST_STRING_T param_id, STRING_T &value);

      //## Operation: SetParamValue%1135773614
      int SetParamValue (CONST_STRING_T param_id, CONST_STRING_T value);

      //## Operation: ErrorText%1135017137
      static STRING_T ErrorText (UCHAR_T layer, ULONG_T code, CONST_STRING_T param1 = NULL, CONST_STRING_T param2 = NULL);

      //## Operation: AddJob%1136548759
      void AddJob (cEM63Job *job);

      //## Operation: RemoveJob%1136548760
      void RemoveJob (cEM63Job *job);

      //## Operation: Job%1136548774
      cEM63Job * Job (CONST_STRING_T name);

      //## Operation: Jobs%1135162871
      void Jobs (JOB_LIST_T &jobs);

      //## Operation: JobCount%1136548779
      ULONG_T JobCount ();

      //## Operation: AddReport%1136548761
      void AddReport (cPresentationCmd *report);

      //## Operation: RemoveReport%1136548762
      void RemoveReport (cPresentationCmd *report);

      //## Operation: Report%1136548775
      cPresentationCmd * Report (CONST_STRING_T name);

      //## Operation: Reports%1136548776
      void Reports (CMD_LIST_T &reports);

      //## Operation: ReportCount%1136548780
      ULONG_T ReportCount ();

      //## Operation: AddEventLog%1136548763
      void AddEventLog (cPresentationCmd *event_log);

      //## Operation: RemoveEventLog%1136548764
      void RemoveEventLog (cPresentationCmd *event_log);

      //## Operation: EventLog%1136548777
      cPresentationCmd * EventLog (CONST_STRING_T name);

      //## Operation: EventLogs%1136548778
      void EventLogs (CMD_LIST_T &event_logs);

      //## Operation: EventLogCount%1136548781
      ULONG_T EventLogCount (CONST_STRING_T event_type);

      //## Operation: RootDirectory%1136631602
      STRING_T RootDirectory ();

      //## Operation: SessionDirectory%1136631603
      STRING_T SessionDirectory ();

      //## Operation: LD%1136631604
      STRING_T LD ();

      //## Operation: DatasetId%1136191747
      STRING_T DatasetId (CONST_STRING_T keyword);

      //## Operation: ShotCounterId%1136631622
      STRING_T ShotCounterId ();

      //## Operation: ShotCounterValue%1136569865
      LONG_T ShotCounterValue ();

      //## Operation: InjUnitNbrValue%1136199175
      LONG_T InjUnitNbrValue ();

      //## Operation: MachNbrValue%1136631618
      STRING_T MachNbrValue ();

      //## Operation: MaterialNbrValue%1136199176
      STRING_T MaterialNbrValue ();

      //## Operation: MoldNbrValue%1136199177
      STRING_T MoldNbrValue ();

      //## Operation: MachVendor%1136631605
      STRING_T MachVendor ();

      //## Operation: MachDesc%1136631606
      STRING_T MachDesc ();

      //## Operation: ContrType%1136631607
      STRING_T ContrType ();

      //## Operation: ContrVersion%1136631608
      STRING_T ContrVersion ();

      //## Operation: MaxJobs%1136631609
      ULONG_T MaxJobs ();

      //## Operation: MaxChanges%1136631610
      ULONG_T MaxChanges ();

      //## Operation: MaxAlarms%1136631611
      ULONG_T MaxAlarms ();

      //## Operation: MaxCurrentAlarms%1136631612
      ULONG_T MaxCurrentAlarms ();

      //## Operation: MaxReports%1136631613
      ULONG_T MaxReports ();

      //## Operation: MaxArchives%1136631614
      ULONG_T MaxArchives ();

      //## Operation: MaxSessions%1136631615
      ULONG_T MaxSessions ();

      //## Operation: CharDef%1136631616
      STRING_T CharDef ();

      //## Operation: Version%1136631620
      STRING_T Version ();

      //## Operation: GetAlarmText%1139403382
      STRING_T GetAlarmText (cAlarm *alarm);
      STRING_T GetCustomAlarmId (cAlarm *alarm);

      //## Operation: SessionMutex%1140161326
      cMutexSem * SessionMutex ();

      //## Operation: FileSystem%1141375556
      cAbstractFileSystem * FileSystem ();

      //## Operation: ParamError%1141641104
      int ParamError (int err);

      //## Operation: ParamId%1141664737
      STRING_T ParamId (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: GetVarCommentType%1151500989
      STRING_T GetVarCommentType ();

      BOOL_T VariableText(STRING_T &ids_text, PARAM_SPEC_T * param_spec);

      //## Operation: Scan%1166083887
      ULONG_T Scan (STRING_LIST_T &file_names, CONST_STRING_T pattern, CONST_STRING_T directory = NULL);

      //## Operation: Get%1166083888
      int Get (ULONG_T category, CONST_STRING_T path, STRING_T &buffer, ULONG_T flags);

      //## Operation: Put%1166083889
      int Put (ULONG_T category, CONST_STRING_T path, CONST_STRING_T text, ULONG_T flags);

      //## Operation: RemoveFile
      int RemoveFile (ULONG_T category, CONST_STRING_T path);

      //## Operation: Log%1166083890
      void Log (ULONG_T category, ULONG_T operation, int error_code, CONST_STRING_T param1 = NULL, CONST_STRING_T param2 = NULL, CONST_STRING_T param3 = NULL);

      //## Operation: AbsPath%1166170819
      STRING_T AbsPath (CONST_STRING_T path);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Verbose%43BF9D810132
      BOOL_T get_Verbose () const;
      void set_Verbose (BOOL_T value);

      //## Attribute: LogFilter%458106A00290
      ULONG_T get_LogFilter () const;
      void set_LogFilter (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cEM63Interface%43A2BA9F0287.public preserve=yes
      //## end cEM63Interface%43A2BA9F0287.public

  protected:
    // Data Members for Class Attributes

      //## begin cEM63Interface::Verbose%43BF9D810132.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Verbose;
      //## end cEM63Interface::Verbose%43BF9D810132.attr

      //## begin cEM63Interface::LogFilter%458106A00290.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _LogFilter;
      //## end cEM63Interface::LogFilter%458106A00290.attr

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%43B1061102AF
      //## Role: cEM63Interface::Program%43B1061202DE
      //## begin cEM63Interface::Program%43B1061202DE.role preserve=no  public: cEM63Program {1 -> 1RFHN}
      cEM63Program *_Program;
      //## end cEM63Interface::Program%43B1061202DE.role

      //## Association: Control::Device::EM63::<unnamed>%43B5655F008E
      //## Role: cEM63Interface::Context%43B5656000DC
      //## begin cEM63Interface::Context%43B5656000DC.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cEM63Interface::Context%43B5656000DC.role

      //## Association: Control::Device::EM63::<unnamed>%4408189B024D
      //## Role: cEM63Interface::FileSystem%4408189C0337
      //## begin cEM63Interface::FileSystem%4408189C0337.role preserve=no  public: cAbstractFileSystem { -> 1RFHN}
      cAbstractFileSystem *_FileSystem;
      //## end cEM63Interface::FileSystem%4408189C0337.role

    // Additional Protected Declarations
      //## begin cEM63Interface%43A2BA9F0287.protected preserve=yes
      //## end cEM63Interface%43A2BA9F0287.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Interface%43A2BA9F0287.private preserve=yes
      //## end cEM63Interface%43A2BA9F0287.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ErrorDescription%1135773617
      static const EM63_ERR_DESCRIPTION_T * ErrorDescription (UCHAR_T layer, ULONG_T code);

      //## Operation: ParamSpec%1135773615
      PARAM_SPEC_T * ParamSpec (CONST_STRING_T param_id);

      //## Operation: CheckRange%1135947265
      int CheckRange (cVarRef *var_ref, CONST_STRING_T value);

    // Data Members for Class Attributes

      //## Attribute: Sessions%43A2BE720055
      //## begin cEM63Interface::Sessions%43A2BE720055.attr preserve=no  implementation: SESSION_MAP_T {U} 
      SESSION_MAP_T _Sessions;
      //## end cEM63Interface::Sessions%43A2BE720055.attr

      //## Attribute: RemovedSessions%43BE745A0089
      //## begin cEM63Interface::RemovedSessions%43BE745A0089.attr preserve=no  implementation: SESSION_LIST_T {U} 
      SESSION_LIST_T _RemovedSessions;
      //## end cEM63Interface::RemovedSessions%43BE745A0089.attr

      //## Attribute: Jobs%43BE674E02CA
      //## begin cEM63Interface::Jobs%43BE674E02CA.attr preserve=no  implementation: JOB_MAP_T {U} 
      JOB_MAP_T _Jobs;
      //## end cEM63Interface::Jobs%43BE674E02CA.attr

      //## Attribute: Reports%43BE676D025D
      //## begin cEM63Interface::Reports%43BE676D025D.attr preserve=no  implementation: CMD_MAP_T {U} 
      CMD_MAP_T _Reports;
      //## end cEM63Interface::Reports%43BE676D025D.attr

      //## Attribute: EventLogs%43BE6782004A
      //## begin cEM63Interface::EventLogs%43BE6782004A.attr preserve=no  implementation: CMD_MAP_T {U} 
      CMD_MAP_T _EventLogs;
      //## end cEM63Interface::EventLogs%43BE6782004A.attr

      //## Attribute: SessionMutex%43F57AD00297
      //## begin cEM63Interface::SessionMutex%43F57AD00297.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _SessionMutex;
      //## end cEM63Interface::SessionMutex%43F57AD00297.attr

      //## Attribute: ParamSpecs%43B263CE02E5
      //## begin cEM63Interface::ParamSpecs%43B263CE02E5.attr preserve=no  implementation: PARAM_SPEC_MAP_T {U} 
      PARAM_SPEC_MAP_T _ParamSpecs;
      //## end cEM63Interface::ParamSpecs%43B263CE02E5.attr

      //## Attribute: VarSpecs%440C7E29025E
      //## begin cEM63Interface::VarSpecs%440C7E29025E.attr preserve=no  implementation: VAR_SPEC_MAP_T {U} 
      VAR_SPEC_MAP_T _VarSpecs;
      //## end cEM63Interface::VarSpecs%440C7E29025E.attr

    // Additional Implementation Declarations
      //## begin cEM63Interface%43A2BA9F0287.implementation preserve=yes
      //## end cEM63Interface%43A2BA9F0287.implementation
public:
    ULONG_T Options ();
// object count control
static std::map<STRING_T,int> _EM63ObjectCount;
static void ControlObjectCount();
static void IncrementObjectCount(const STRING_T & oname);
static void DecrementObjectCount(const STRING_T & oname);
};

//## begin cEM63Interface%43A2BA9F0287.postscript preserve=yes
//## end cEM63Interface%43A2BA9F0287.postscript

// Class cEM63Interface 

//## begin module%43A2BA9F0287.epilog preserve=yes
//## end module%43A2BA9F0287.epilog


#endif
