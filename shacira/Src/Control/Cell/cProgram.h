//## begin module%3FE745260261.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE745260261.cm

//## begin module%3FE745260261.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE745260261.cp

//## Module: cProgram%3FE745260261; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cProgram.h

#ifndef cProgram_h
#define cProgram_h 1

//## begin module%3FE745260261.includes preserve=yes
#include "Control/Cell/JobQueue.h"
//## end module%3FE745260261.includes

// cProgress
#include "System/Objects/cProgress.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cConnector
#include "System/Channel/cConnector.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cObjectQueue;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3FE745260261.additionalDeclarations preserve=yes
//## end module%3FE745260261.additionalDeclarations


//## begin cProgram%3FE745260261.preface preserve=yes
//## end cProgram%3FE745260261.preface

//## Class: cProgram%3FE745260261
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FE7475B0186;cTransientObject { -> F}
//## Uses: <unnamed>%3FE753F90213;cConfigurationObject { -> F}
//## Uses: <unnamed>%3FE7551B03B9;cVarRef { -> }
//## Uses: <unnamed>%406E87AF0399;cVariable { -> F}
//## Uses: <unnamed>%407D8F7B0128;cFileSystemUtils { -> F}
//## Uses: <unnamed>%42CBED3C000F;cProgress { -> }
//## Uses: <unnamed>%43B1609301E5;cVarDef { -> }
//## Uses: <unnamed>%4610A0C803C8;cObjectQueue { -> F}

class __DLL_EXPORT__ cProgram : public cConnector  //## Inherits: <unnamed>%3FFE78F60186
{
  //## begin cProgram%3FE745260261.initialDeclarations preserve=yes
public:
  //## end cProgram%3FE745260261.initialDeclarations

    //## Constructors (generated)
      cProgram();

      cProgram(const cProgram &right);

    //## Constructors (specified)
      //## Operation: cProgram%1072120959
      cProgram (cConfigurationObject *config_obj, cContext *context);

      //## Operation: cProgram%1122375232
      cProgram (CONST_STRING_T name, cContext *context);

    //## Destructor (generated)
      virtual ~cProgram();


    //## Other Operations (specified)
      //## Operation: ControlFunc%1072120961
      virtual INT_T ControlFunc ();

      //## Operation: Object%1073642243
      //	Method that is called when an incoming object arrives at
      //	the back end of the associated channel.
      virtual void Object (cTransientObject *object);

      //## Operation: ExecuteCommand%1089292609
      virtual void ExecuteCommand (ULONG_T command);

      //## Operation: ExecuteRequest%1133771771
      //	Executes a request on this program.
      virtual void ExecuteRequest (STRING_T &reply, CONST_STRING_T request);

      //## Operation: Stop%1090071073
      void Stop ();

      //## Operation: Restart%1090071074
      void Restart ();

      //## Operation: Set%1078844334
      void Set (cVarRef *var_ref, BOOL_T value);

      //## Operation: Set%1078844335
      void Set (cVarRef *var_ref, CHAR_T value);

      //## Operation: Set%1078844336
      void Set (cVarRef *var_ref, UCHAR_T value);

      //## Operation: Set%1078844337
      void Set (cVarRef *var_ref, SHORT_T value);

      //## Operation: Set%1078844338
      void Set (cVarRef *var_ref, USHORT_T value);

      //## Operation: Set%1078844339
      void Set (cVarRef *var_ref, LONG_T value);

      //## Operation: Set%1078844321
      void Set (cVarRef *var_ref, ULONG_T value);

      //## Operation: Set%1078844340
      void Set (cVarRef *var_ref, FLOAT_T value);

      //## Operation: Set%1078844322
      void Set (cVarRef *var_ref, DOUBLE_T value);

      //## Operation: Set%1078844323
      void Set (cVarRef *var_ref, CONST_STRING_T value);

      //## Operation: Set%1078844324
      void Set (cVarRef *var_ref, BUF_T buf, ULONG_T size);

      //## Operation: Refresh%1078844341
      void Refresh (cVarRef *var_ref);

      //## Operation: SetVar%1080985435
      void SetVar (CONST_STRING_T var_name, BOOL_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985436
      void SetVar (CONST_STRING_T var_name, CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985437
      void SetVar (CONST_STRING_T var_name, UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985438
      void SetVar (CONST_STRING_T var_name, SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985439
      void SetVar (CONST_STRING_T var_name, USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985440
      void SetVar (CONST_STRING_T var_name, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985441
      void SetVar (CONST_STRING_T var_name, ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985442
      void SetVar (CONST_STRING_T var_name, FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985443
      void SetVar (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985444
      void SetVar (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetVar%1080985445
      void SetVar (CONST_STRING_T var_name, BUF_T buf, ULONG_T size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985446
      void GetVar (CONST_STRING_T var_name, BOOL_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985447
      void GetVar (CONST_STRING_T var_name, CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985448
      void GetVar (CONST_STRING_T var_name, UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985449
      void GetVar (CONST_STRING_T var_name, SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985450
      void GetVar (CONST_STRING_T var_name, USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985451
      void GetVar (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985452
      void GetVar (CONST_STRING_T var_name, ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985453
      void GetVar (CONST_STRING_T var_name, FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985454
      void GetVar (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985455
      void GetVar (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985456
      void GetVar (CONST_STRING_T var_name, BUF_T &buf, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetVar%1080985457
      void GetVar (CONST_STRING_T var_name, BUF_T buf, ULONG_T size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: RefreshVar%1092325288
      void RefreshVar (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1117548695
      void Get (CONST_STRING_T var_spec, STRING_T &value);

      //## Operation: Get%1117548696
      void Get (CONST_STRING_T var_spec, LONG_T &value);

      //## Operation: Get%1117548697
      void Get (CONST_STRING_T var_spec, DOUBLE_T &value);

      //## Operation: SetProgress%1120660729
      void SetProgress (ULONG_T indicator, ULONG_T value);

      //## Operation: Save%1236707296
      void Save (UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: ExecuteJob%1244549648
      void ExecuteJob (CONST_STRING_T job, BOOL_T async = false);

      //## Operation: ProcessJob%1244551835
      virtual void ProcessJob (CONST_STRING_T job, BOOL_T async);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Verbose%43B93E400327
      BOOL_T get_Verbose () const;
      void set_Verbose (BOOL_T value);

      //## Attribute: StartDelay%40960061032C
      ULONG_T get_StartDelay () const;
      void set_StartDelay (ULONG_T value);

      //## Attribute: IFType%43B15F190264
      LONG_T get_IFType () const;
      void set_IFType (LONG_T value);

  public:
    // Additional Public Declarations
      //## begin cProgram%3FE745260261.public preserve=yes
      //## end cProgram%3FE745260261.public

  protected:

    //## Other Operations (specified)
      //## Operation: ProcessEvent%1072120962
      virtual void ProcessEvent (cTransientObject *object) = 0;

      //## Operation: Cycle%1072120963
      virtual void Cycle () = 0;

      //## Operation: Initialize%1078844332
      virtual void Initialize () = 0;

      //## Operation: GetInt%1078844325
      ULONG_T GetInt (cVarRef *var_ref);

      //## Operation: GetReal%1078844326
      DOUBLE_T GetReal (cVarRef *var_ref);

      //## Operation: GetString%1078844327
      STRING_T GetString (cVarRef *var_ref);

      //## Operation: GetBuf%1078844328
      BUF_T GetBuf (cVarRef *var_ref);

      //## Operation: ClearAlarm%1081425530
      void ClearAlarm (ULONG_T ident);

      //## Operation: ClearAlarms%1081425632
      void ClearAlarms ();

      //## Operation: DebugPrintf%1081970260
      void DebugPrintf (ULONG_T debug_level, CONST_STRING_T fmt_str, ... );

      //## Operation: UserContext%1090071075
      BOOL_T UserContext ();

      //## Operation: ProgramContext%1090071076
      BOOL_T ProgramContext ();

      //## Operation: AsyncContext%1090071077
      BOOL_T AsyncContext ();

      //## Operation: DispatchEvent%1175495042
      BOOL_T DispatchEvent (cTransientObject *object);

      //## Operation: ProcessEventQueue%1175495043
      void ProcessEventQueue ();

      //## Operation: ProcessJobQueue%1244549649
      virtual void ProcessJobQueue ();

    // Data Members for Class Attributes

      //## begin cProgram::Verbose%43B93E400327.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Verbose;
      //## end cProgram::Verbose%43B93E400327.attr

      //## begin cProgram::StartDelay%40960061032C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _StartDelay;
      //## end cProgram::StartDelay%40960061032C.attr

      //## begin cProgram::IFType%43B15F190264.attr preserve=no  public: LONG_T {U} IF_PROPRIETARY
      LONG_T _IFType;
      //## end cProgram::IFType%43B15F190264.attr

      //## Attribute: Initialized%404DE9D400FA
      //## begin cProgram::Initialized%404DE9D400FA.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Initialized;
      //## end cProgram::Initialized%404DE9D400FA.attr

      //## Attribute: DebugLevel%407D8CD3031C
      //## begin cProgram::DebugLevel%407D8CD3031C.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _DebugLevel;
      //## end cProgram::DebugLevel%407D8CD3031C.attr

      //## Attribute: CycleMutex%416A7DE0032C
      //## begin cProgram::CycleMutex%416A7DE0032C.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _CycleMutex;
      //## end cProgram::CycleMutex%416A7DE0032C.attr

      //## Attribute: ProgramThreadId%40F9297D0399
      //## begin cProgram::ProgramThreadId%40F9297D0399.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _ProgramThreadId;
      //## end cProgram::ProgramThreadId%40F9297D0399.attr

      //## Attribute: AsyncThreadId%40F929B80000
      //## begin cProgram::AsyncThreadId%40F929B80000.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _AsyncThreadId;
      //## end cProgram::AsyncThreadId%40F929B80000.attr

      //## Attribute: UserThreadId%40F929C901C5
      //## begin cProgram::UserThreadId%40F929C901C5.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _UserThreadId;
      //## end cProgram::UserThreadId%40F929C901C5.attr

      //## Attribute: EventQueueMutex%4610A0E6003E
      //## begin cProgram::EventQueueMutex%4610A0E6003E.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _EventQueueMutex;
      //## end cProgram::EventQueueMutex%4610A0E6003E.attr

      //## Attribute: EventQueue%4610A0F9036B
      //## begin cProgram::EventQueue%4610A0F9036B.attr preserve=no  protected: cObjectQueue * {U} NULL
      cObjectQueue *_EventQueue;
      //## end cProgram::EventQueue%4610A0F9036B.attr

      //## Attribute: JobQueue%4A2E534F017A
      //## begin cProgram::JobQueue%4A2E534F017A.attr preserve=no  protected: JobQueue {U} 
      JobQueue _JobQueue;
      //## end cProgram::JobQueue%4A2E534F017A.attr

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%3FE747D90213
      //## Role: cProgram::Context%3FE747DA00CB
      //## begin cProgram::Context%3FE747DA00CB.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cProgram::Context%3FE747DA00CB.role

    // Additional Protected Declarations
      //## begin cProgram%3FE745260261.protected preserve=yes
      //## end cProgram%3FE745260261.protected

  private:
    // Additional Private Declarations
      //## begin cProgram%3FE745260261.private preserve=yes
      //## end cProgram%3FE745260261.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProgram%3FE745260261.implementation preserve=yes
      //## end cProgram%3FE745260261.implementation
      ULONG_T _MaxProcessEventDuration;
};

//## begin cProgram%3FE745260261.postscript preserve=yes
//## end cProgram%3FE745260261.postscript

// Class cProgram 

//## begin module%3FE745260261.epilog preserve=yes
//## end module%3FE745260261.epilog


#endif
