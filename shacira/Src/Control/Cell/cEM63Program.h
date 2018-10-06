//## begin module%43B103A502AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43B103A502AB.cm

//## begin module%43B103A502AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43B103A502AB.cp

//## Module: cEM63Program%43B103A502AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cEM63Program.h

#ifndef cEM63Program_h
#define cEM63Program_h 1

//## begin module%43B103A502AB.includes preserve=yes

#define EM63_OPT_LOG_UNKNOWN        0x00000001
#define EM63_OPT_LOG_FILE_CHANGES   0x00000002


#define DIM0_DECREMENT        0x80000000
#define DIM1_DECREMENT        0x40000000
#define DIM2_DECREMENT        0x20000000
#define DIM3_DECREMENT        0x10000000

#define DIM_UNUSED            0x00010000
#define DIM_REMOVED           0x00020000
#define DIM_DECREMENTED       0x00040000
#define GET_DIM_POS(dimspec)  (dimspec & DIM_UNUSED ? -1 : (dimspec & 0x00000007))


class cEM63LogInfo;

//## end module%43B103A502AB.includes

// cContext
#include "System/Database/cContext.h"
// cProgram
#include "Control/Cell/cProgram.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"

class __DLL_EXPORT__ cUserInfo;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cEM63Requester;
class __DLL_EXPORT__ cEM63Session;
class __DLL_EXPORT__ cEM63Interface;
class __DLL_EXPORT__ cEM63Job;
class __DLL_EXPORT__ cStyxParser;

//## begin module%43B103A502AB.additionalDeclarations preserve=yes
//## end module%43B103A502AB.additionalDeclarations


//## begin cEM63Program%43B103A502AB.preface preserve=yes
//## end cEM63Program%43B103A502AB.preface

//## Class: cEM63Program%43B103A502AB
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B107E40261;cEM63Job { -> F}
//## Uses: <unnamed>%43B107ED032D;cEM63Session { -> F}
//## Uses: <unnamed>%43B10E7102A8;cFileSystemUtils { -> F}
//## Uses: <unnamed>%43B1664400CA;cContext { -> }
//## Uses: <unnamed>%43B1664A00E9;cContext { -> F}
//## Uses: <unnamed>%43B16AEE01DB;cStyxParser { -> F}
//## Uses: <unnamed>%43E9E6C602CD;cUserInfo { -> F}
//## Uses: <unnamed>%44A2925B031C;cUnitDef { -> F}

class __DLL_EXPORT__ cEM63Program : public cProgram  //## Inherits: <unnamed>%43B103F302B8
{
  //## begin cEM63Program%43B103A502AB.initialDeclarations preserve=yes
public:
  //## end cEM63Program%43B103A502AB.initialDeclarations

    //## Constructors (generated)
      cEM63Program();

      cEM63Program(const cEM63Program &right);

    //## Constructors (specified)
      //## Operation: cEM63Program%1135674623
      cEM63Program (cConfigurationObject *config_obj, cContext *context);

    //## Destructor (generated)
      virtual ~cEM63Program();


    //## Other Operations (specified)
      //## Operation: Start%1135674627
      virtual void Start ();

      //## Operation: Stop%1135674628
      virtual void Stop ();

      //## Operation: RootDirectory%1136631587
      virtual STRING_T RootDirectory ();

      //## Operation: SessionDirectory%1136631588
      virtual STRING_T SessionDirectory ();

      //## Operation: LD%1136631589
      virtual STRING_T LD ();

      //## Operation: DatasetId%1136191744
      virtual STRING_T DatasetId (CONST_STRING_T keyword);

      //## Operation: ShotCounterId%1136631621
      virtual STRING_T ShotCounterId ();

      //## Operation: ShotCounterValue%1136191748
      virtual LONG_T ShotCounterValue ();

      //## Operation: InjUnitNbrValue%1136199172
      virtual ULONG_T InjUnitNbrValue ();

      //## Operation: MoldNbrValue%1136199174
      virtual STRING_T MoldNbrValue ();

      //## Operation: MachNbrValue%1136631617
      virtual STRING_T MachNbrValue ();

      //## Operation: MaterialNbrValue%1136199173
      virtual STRING_T MaterialNbrValue ();

      //## Operation: MachVendor%1136631590
      virtual STRING_T MachVendor ();

      //## Operation: MachDesc%1136631591
      virtual STRING_T MachDesc ();

      //## Operation: ContrType%1136631592
      virtual STRING_T ContrType ();

      //## Operation: ContrVersion%1136631593
      virtual STRING_T ContrVersion ();

      //## Operation: MaxJobs%1136631594
      virtual ULONG_T MaxJobs ();

      //## Operation: MaxChanges%1136631595
      virtual ULONG_T MaxChanges ();

      //## Operation: MaxAlarms%1136631596
      virtual ULONG_T MaxAlarms ();

      //## Operation: MaxCurrentAlarms%1136631597
      virtual ULONG_T MaxCurrentAlarms ();

      //## Operation: MaxReports%1136631598
      virtual ULONG_T MaxReports ();

      //## Operation: MaxArchives%1136631599
      virtual ULONG_T MaxArchives ();

      //## Operation: MaxSessions%1136631600
      virtual ULONG_T MaxSessions ();

      //## Operation: CharDef%1136631601
      virtual STRING_T CharDef ();

      //## Operation: Version%1136631619
      virtual STRING_T Version ();

      //## Operation: GetAlarmText%1139403383
      virtual STRING_T GetAlarmText (cAlarm *alarm);
      virtual STRING_T GetCustomAlarmId (cAlarm *alarm);

      //## Operation: GetVarCommentType%1151500988
      virtual STRING_T GetVarCommentType ();

      virtual BOOL_T VariableText(STRING_T &ids_text, PARAM_SPEC_T * param_spec);

      //## Operation: Log%1166083886
      virtual void Log (cEM63LogInfo *log_info);

      virtual void SessionDirectoryPresentChanged(BOOL_T &state) {};

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Active%43BF9B6601C0
      BOOL_T get_Active () const;
      void set_Active (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cEM63Program%43B103A502AB.public preserve=yes
      //## end cEM63Program%43B103A502AB.public

  protected:

    //## Other Operations (specified)
      //## Operation: ProcessEvent%1135674616
      virtual void ProcessEvent (cTransientObject *object);

      //## Operation: Cycle%1135674617
      virtual void Cycle ();

      //## Operation: Initialize%1135674618
      virtual void Initialize ();

      //## Operation: SetRoot%1135674624
      void SetRoot (CONST_STRING_T root_directory);

    // Data Members for Class Attributes

      //## begin cEM63Program::Active%43BF9B6601C0.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _Active;
      //## end cEM63Program::Active%43BF9B6601C0.attr

      //## Attribute: UserInfo%43E9E6260253
      //## begin cEM63Program::UserInfo%43E9E6260253.attr preserve=no  protected: cUserInfo * {U} NULL
      cUserInfo *_UserInfo;
      //## end cEM63Program::UserInfo%43E9E6260253.attr

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%43B104A800FA
      //## Role: cEM63Program::Requester%43B104AA035B
      //## begin cEM63Program::Requester%43B104AA035B.role preserve=no  public: cEM63Requester {1 -> 1RFHN}
      cEM63Requester *_Requester;
      //## end cEM63Program::Requester%43B104AA035B.role

      //## Association: Control::Cell::<unnamed>%43B1061102AF
      //## Role: cEM63Program::Interface%43B1061202CE
      //## begin cEM63Program::Interface%43B1061202CE.role preserve=no  public: cEM63Interface {1 -> 1RFHN}
      cEM63Interface *_Interface;
      //## end cEM63Program::Interface%43B1061202CE.role

    // Additional Protected Declarations
      //## begin cEM63Program%43B103A502AB.protected preserve=yes
      //## end cEM63Program%43B103A502AB.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Program%43B103A502AB.private preserve=yes
      //## end cEM63Program%43B103A502AB.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CreateInterfaceContext%1135674630
      void CreateInterfaceContext ();

      //## Operation: VarSpec%1135674631
      BOOL_T VarSpec (cVarDef *var_def, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision, UCHAR_T &access_rights, STRING_T &unit, STRING_T &description, STRING_T &text, STRING_T &dim1_text, STRING_T &dim2_text, STRING_T &dim3_text, STRING_T &dim4_text);

      //## Operation: DigitCount%1135674632
      ULONG_T DigitCount (UCHAR_T data_type);

    // Additional Implementation Declarations
      //## begin cEM63Program%43B103A502AB.implementation preserve=yes
      //## end cEM63Program%43B103A502AB.implementation

    friend class __DLL_EXPORT__ cEM63Requester;
private:
   ULONG_T _Options;
public:
   ULONG_T Options ();
   void SetOption (ULONG_T option);
   void ResetOption (ULONG_T option);
};

//## begin cEM63Program%43B103A502AB.postscript preserve=yes
//## end cEM63Program%43B103A502AB.postscript

// Class cEM63Program 

//## begin module%43B103A502AB.epilog preserve=yes
//## end module%43B103A502AB.epilog


#endif
