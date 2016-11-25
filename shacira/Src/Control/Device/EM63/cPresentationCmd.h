//## begin module%43807F7B0079.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43807F7B0079.cm

//## begin module%43807F7B0079.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43807F7B0079.cp

//## Module: cPresentationCmd%43807F7B0079; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cPresentationCmd.h

#ifndef cPresentationCmd_h
#define cPresentationCmd_h 1

//## begin module%43807F7B0079.includes preserve=yes
//## end module%43807F7B0079.includes

// cTimeObject
#include "System/cTimeObject.h"
// cBufferedFile
#include "System/Sys/cBufferedFile.h"
// cCondition
#include "Control/Device/EM63/cCondition.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cEM63Session;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%43807F7B0079.additionalDeclarations preserve=yes

#define EM63_APPEND     0
#define EM63_REWRITE    1

#define EM63_START_IMMEDIATE  0
#define EM63_START_TIME       1

#define EM63_STOP_NEVER       0
#define EM63_STOP_TIME        1

// condition types

#define EM63_CYCLE            0
#define EM63_CYCLE_SHOT       1
#define EM63_PARAM_COND       2
#define EM63_PARAM_CHANGED    3
#define EM63_TIME_INTERFVAL   4
#define EM63_TIME_REL         5

// meta conditions

#define EM63_ID               0
#define EM63_NOT              1

// relative operators

#define EM63_EQ               0
#define EM63_LT               1
#define EM63_GT               2
#define EM63_LE               3
#define EM63_GE               4
#define EM63_NE               5

//## end module%43807F7B0079.additionalDeclarations


//## begin cPresentationCmd%43807F7B0079.preface preserve=yes
//## end cPresentationCmd%43807F7B0079.preface

//## Class: cPresentationCmd%43807F7B0079
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A68C6403B2;cTimeObject { -> }
//## Uses: <unnamed>%43A6A6F80342;cCondition { -> }
//## Uses: <unnamed>%440BE855020C;cBufferedFile { -> }

class __DLL_EXPORT__ cPresentationCmd 
{
  //## begin cPresentationCmd%43807F7B0079.initialDeclarations preserve=yes
public:
  //## end cPresentationCmd%43807F7B0079.initialDeclarations

    //## Constructors (generated)
      cPresentationCmd();

      cPresentationCmd(const cPresentationCmd &right);

    //## Constructors (specified)
      //## Operation: cPresentationCmd%1136548767
      cPresentationCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cPresentationCmd();


    //## Other Operations (specified)
      //## Operation: Job%1134835349
      cEM63Job * Job ();

      //## Operation: Process%1135078972
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1135068543
      virtual BOOL_T Start ();

      //## Operation: Control%1135068544
      virtual void Control ();

      //## Operation: Stop%1135068545
      virtual void Stop ();

      //## Operation: Abort%1136213368
      void Abort (int abort_type, CONST_STRING_T name);

      //## Operation: IsTerminated%1136286711
      BOOL_T IsTerminated ();

      //## Operation: IsActive%1136457201
      BOOL_T IsActive ();

      //## Operation: HasFailed%1136457202
      BOOL_T HasFailed ();

      //## Operation: IsStarted%1136457206
      BOOL_T IsStarted ();

      //## Operation: IsReport%1136286713
      virtual BOOL_T IsReport ();

      //## Operation: IsEvent%1136286714
      virtual BOOL_T IsEvent ();

      //## Operation: IsAbortCmd%1136457212
      virtual BOOL_T IsAbortCmd ();

      //## Operation: Key%1136457214
      STRING_T Key ();

      //## Operation: CommandString%1136541420
      STRING_T CommandString (LONG_T command_type=-1);

      //## Operation: SetOutputFile%1166170824
      void SetOutputFile (const STRING_T &file);

      //## Operation: OutputFile%1166170825
      STRING_T OutputFile ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CommandType%43A93F7700C4
      ULONG_T get_CommandType () const;

      //## Attribute: CommandName%43A7CF3B0369
      STRING_T get_CommandName () const;
      void set_CommandName (STRING_T value);

      //## Attribute: Terminated%43A7CF7301E3
      BOOL_T get_Terminated () const;
      void set_Terminated (BOOL_T value);

      //## Attribute: ErrorCode%43A8111C006E
      ULONG_T get_ErrorCode () const;

      //## Attribute: Param1%43A8113901B6
      STRING_T get_Param1 () const;

      //## Attribute: Param2%43A811480139
      STRING_T get_Param2 () const;

      //## Attribute: ErrorMsg%43B2B076035A
      STRING_T get_ErrorMsg () const;

  public:
    // Additional Public Declarations
      //## begin cPresentationCmd%43807F7B0079.public preserve=yes
      //## end cPresentationCmd%43807F7B0079.public

  protected:

    //## Other Operations (specified)
      //## Operation: Processed%1136457210
      void Processed ();

      //## Operation: Started%1136457198
      void Started ();

      //## Operation: Terminated%1136457199
      void Terminated ();

      //## Operation: Aborted%1136457200
      void Aborted ();

      //## Operation: Failed%1136457203
      void Failed (int err_code, CONST_STRING_T param1 = "", CONST_STRING_T param2 = "");

    // Data Members for Class Attributes

      //## begin cPresentationCmd::CommandType%43A93F7700C4.attr preserve=no  public: ULONG_T {U} EM63_UNDEFINED_COMMAND
      ULONG_T _CommandType;
      //## end cPresentationCmd::CommandType%43A93F7700C4.attr

      //## begin cPresentationCmd::CommandName%43A7CF3B0369.attr preserve=no  public: STRING_T {U} 
      STRING_T _CommandName;
      //## end cPresentationCmd::CommandName%43A7CF3B0369.attr

      //## begin cPresentationCmd::Terminated%43A7CF7301E3.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Terminated;
      //## end cPresentationCmd::Terminated%43A7CF7301E3.attr

      //## begin cPresentationCmd::ErrorCode%43A8111C006E.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ErrorCode;
      //## end cPresentationCmd::ErrorCode%43A8111C006E.attr

      //## begin cPresentationCmd::Param1%43A8113901B6.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param1;
      //## end cPresentationCmd::Param1%43A8113901B6.attr

      //## begin cPresentationCmd::Param2%43A811480139.attr preserve=no  public: STRING_T {U} 
      STRING_T _Param2;
      //## end cPresentationCmd::Param2%43A811480139.attr

      //## begin cPresentationCmd::ErrorMsg%43B2B076035A.attr preserve=no  public: STRING_T {U} 
      STRING_T _ErrorMsg;
      //## end cPresentationCmd::ErrorMsg%43B2B076035A.attr

      //## Attribute: LD%43AAAC5B0118
      //## begin cPresentationCmd::LD%43AAAC5B0118.attr preserve=no  protected: STRING_T {U} ","
      STRING_T _LD;
      //## end cPresentationCmd::LD%43AAAC5B0118.attr

      //## Attribute: OutputFile%43A942BF0055
      //## begin cPresentationCmd::OutputFile%43A942BF0055.attr preserve=no  protected: STRING_T {U} 
      STRING_T _OutputFile;
      //## end cPresentationCmd::OutputFile%43A942BF0055.attr

    // Data Members for Associations

      //## Association: Control::Device::EM63::<unnamed>%43B289CB039B
      //## Role: cPresentationCmd::Job%43B289CC037C
      //## begin cPresentationCmd::Job%43B289CC037C.role preserve=no  public: cEM63Job { -> 1RHN}
      cEM63Job *_Job;
      //## end cPresentationCmd::Job%43B289CC037C.role

      //## Association: Control::Device::EM63::<unnamed>%43B289F70197
      //## Role: cPresentationCmd::Session%43B289F80234
      //## begin cPresentationCmd::Session%43B289F80234.role preserve=no  public: cEM63Session { -> 1RFHN}
      cEM63Session *_Session;
      //## end cPresentationCmd::Session%43B289F80234.role

      //## Association: Control::Device::EM63::<unnamed>%43B28881017A
      //## Role: cPresentationCmd::Interface%43B2888400CE
      //## begin cPresentationCmd::Interface%43B2888400CE.role preserve=no  public: cEM63Interface { -> 1RFHN}
      cEM63Interface *_Interface;
      //## end cPresentationCmd::Interface%43B2888400CE.role

      //## Association: Control::Device::EM63::<unnamed>%43A7FD5503BC
      //## Role: cPresentationCmd::Context%43A7FD5602C2
      //## begin cPresentationCmd::Context%43A7FD5602C2.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cPresentationCmd::Context%43A7FD5602C2.role

    // Additional Protected Declarations
      //## begin cPresentationCmd%43807F7B0079.protected preserve=yes
      //## end cPresentationCmd%43807F7B0079.protected

  private:
    // Additional Private Declarations
      //## begin cPresentationCmd%43807F7B0079.private preserve=yes
      //## end cPresentationCmd%43807F7B0079.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Failed%43A8110E006E
      //## begin cPresentationCmd::Failed%43A8110E006E.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Failed;
      //## end cPresentationCmd::Failed%43A8110E006E.attr

      //## Attribute: Started%43A7CF53035A
      //## begin cPresentationCmd::Started%43A7CF53035A.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Started;
      //## end cPresentationCmd::Started%43A7CF53035A.attr

      //## Attribute: Active%43A7CF6501A5
      //## begin cPresentationCmd::Active%43A7CF6501A5.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Active;
      //## end cPresentationCmd::Active%43A7CF6501A5.attr

      //## Attribute: Aborted%43B940090127
      //## begin cPresentationCmd::Aborted%43B940090127.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Aborted;
      //## end cPresentationCmd::Aborted%43B940090127.attr

    // Additional Implementation Declarations
      //## begin cPresentationCmd%43807F7B0079.implementation preserve=yes
      //## end cPresentationCmd%43807F7B0079.implementation

};

//## begin cPresentationCmd%43807F7B0079.postscript preserve=yes
//## end cPresentationCmd%43807F7B0079.postscript

// Class cPresentationCmd 

//## begin module%43807F7B0079.epilog preserve=yes
//## end module%43807F7B0079.epilog


#endif
