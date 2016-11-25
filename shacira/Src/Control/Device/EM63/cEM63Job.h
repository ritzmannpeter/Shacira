//## begin module%4380835603C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380835603C0.cm

//## begin module%4380835603C0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380835603C0.cp

//## Module: cEM63Job%4380835603C0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Job.h

#ifndef cEM63Job_h
#define cEM63Job_h 1

//## begin module%4380835603C0.includes preserve=yes
//## end module%4380835603C0.includes

// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cPresentationCmd;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%4380835603C0.additionalDeclarations preserve=yes

typedef std::vector<cPresentationCmd*> COMMAND_VECTOR_T;
typedef std::list<cPresentationCmd*> COMMAND_LIST_T;

//## end module%4380835603C0.additionalDeclarations


//## begin cEM63Job%4380835603C0.preface preserve=yes
//## end cEM63Job%4380835603C0.preface

//## Class: cEM63Job%4380835603C0
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A7FBE9036E;cContext { -> F}
//## Uses: <unnamed>%43A809A4037B;cEM63Interface { -> F}
//## Uses: <unnamed>%43B25CE5037B;cPresentationCmd { -> F}

class __DLL_EXPORT__ cEM63Job 
{
  //## begin cEM63Job%4380835603C0.initialDeclarations preserve=yes
public:
  //## end cEM63Job%4380835603C0.initialDeclarations

    //## Constructors (generated)
      cEM63Job();

      cEM63Job(const cEM63Job &right);

    //## Constructors (specified)
      //## Operation: cEM63Job%1134738523
      cEM63Job (cEM63Session *session, CONST_STRING_T request_file);

      //## Operation: cEM63Job%1233306614
      cEM63Job (cEM63Session *session);

    //## Destructor (generated)
      virtual ~cEM63Job();


    //## Other Operations (specified)
      //## Operation: Initialize%1135078974
      void Initialize (CONST_STRING_T job_name, CONST_STRING_T response_file);

      //## Operation: SetSession%1134835346
      void SetSession (cEM63Session *session);

      //## Operation: Session%1134835347
      cEM63Session * Session ();

      //## Operation: AddCommand%1134738524
      void AddCommand (cPresentationCmd *command);

      //## Operation: Commands%1134835350
      void Commands (COMMAND_LIST_T &commands);

      //## Operation: Failed%1135017138
      void Failed (ULONG_T code, CONST_STRING_T param1 = "", CONST_STRING_T param2 = "");

      //## Operation: Process%1135068536
      BOOL_T Process (cContext *context);

      //## Operation: Respond%1135068540
      void Respond ();

      //## Operation: Start%1135068537
      BOOL_T Start ();

      //## Operation: Control%1135068538
      void Control ();

      //## Operation: Stop%1135068539
      void Stop ();

      //## Operation: CleanUp%1136213366
      void CleanUp ();

      //## Operation: Abort%1136213370
      void Abort (int abort_type, CONST_STRING_T name);

      //## Operation: Command%1134835351
      cPresentationCmd * Command (ULONG_T index);

      //## Operation: IsActive%1135162872
      BOOL_T IsActive ();

      //## Operation: IsTerminated%1136286709
      BOOL_T IsTerminated ();

      //## Operation: HasFailed%1136457204
      BOOL_T HasFailed ();

      //## Attribute: ErrorCode
      ULONG_T get_ErrorCode () const;

      //## Attribute: ErrorMsg
      STRING_T get_ErrorMsg () const;

      //## Operation: SetRequestFile%1166170826
      void SetRequestFile (const STRING_T &file);

      //## Operation: RequestFile%1166170827
      STRING_T RequestFile ();

      //## Operation: SetResponseFile%1166170828
      void SetResponseFile (const STRING_T &file);

      //## Operation: ResponseFile%1166170829
      STRING_T ResponseFile ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: JobName%43A2B9720014
      STRING_T get_JobName () const;
      void set_JobName (STRING_T value);

      //## Attribute: CommandIdentifier%43F4D80F0236
      STRING_T get_CommandIdentifier () const;
      void set_CommandIdentifier (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cEM63Job%4380835603C0.public preserve=yes
      //## end cEM63Job%4380835603C0.public

  protected:
    // Data Members for Class Attributes

      //## begin cEM63Job::JobName%43A2B9720014.attr preserve=no  public: STRING_T {U} 
      STRING_T _JobName;
      //## end cEM63Job::JobName%43A2B9720014.attr

      //## begin cEM63Job::CommandIdentifier%43F4D80F0236.attr preserve=no  public: STRING_T {U} 
      STRING_T _CommandIdentifier;
      //## end cEM63Job::CommandIdentifier%43F4D80F0236.attr

      //## Attribute: RequestFile%43A815F8030E
      //## begin cEM63Job::RequestFile%43A815F8030E.attr preserve=no  protected: STRING_T {U} 
      STRING_T _RequestFile;
      //## end cEM63Job::RequestFile%43A815F8030E.attr

      //## Attribute: ResponseFile%43A2B97F0227
      //## begin cEM63Job::ResponseFile%43A2B97F0227.attr preserve=no  protected: STRING_T {U} 
      STRING_T _ResponseFile;
      //## end cEM63Job::ResponseFile%43A2B97F0227.attr

    // Data Members for Associations

      //## Association: Control::Device::EM63::<unnamed>%43A8132B0168
      //## Role: cEM63Job::Session%43A8132D039A
      //## begin cEM63Job::Session%43A8132D039A.role preserve=no  public: cEM63Session { -> 1RHN}
      cEM63Session *_Session;
      //## end cEM63Job::Session%43A8132D039A.role

    // Additional Protected Declarations
      //## begin cEM63Job%4380835603C0.protected preserve=yes
      //## end cEM63Job%4380835603C0.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Job%4380835603C0.private preserve=yes
      //## end cEM63Job%4380835603C0.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Commands%43A2BEAB01AD
      //## begin cEM63Job::Commands%43A2BEAB01AD.attr preserve=no  implementation: COMMAND_VECTOR_T {U} 
      COMMAND_VECTOR_T _Commands;
      //## end cEM63Job::Commands%43A2BEAB01AD.attr

      //## Attribute: Failed%43BCFC610119
      //## begin cEM63Job::Failed%43BCFC610119.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Failed;
      //## end cEM63Job::Failed%43BCFC610119.attr

      //## Attribute: ErrorCode%43A94E2400C2
      //## begin cEM63Job::ErrorCode%43A94E2400C2.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ErrorCode;
      //## end cEM63Job::ErrorCode%43A94E2400C2.attr

      //## Attribute: Param1%43A94E2400C3
      //## begin cEM63Job::Param1%43A94E2400C3.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Param1;
      //## end cEM63Job::Param1%43A94E2400C3.attr

      //## Attribute: Param2%43A94E2400C4
      //## begin cEM63Job::Param2%43A94E2400C4.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Param2;
      //## end cEM63Job::Param2%43A94E2400C4.attr

      //## Attribute: ErrorMsg%43B2B9730071
      //## begin cEM63Job::ErrorMsg%43B2B9730071.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ErrorMsg;
      //## end cEM63Job::ErrorMsg%43B2B9730071.attr

    // Additional Implementation Declarations
      //## begin cEM63Job%4380835603C0.implementation preserve=yes
      //## end cEM63Job%4380835603C0.implementation

};

//## begin cEM63Job%4380835603C0.postscript preserve=yes
//## end cEM63Job%4380835603C0.postscript

// Class cEM63Job 

//## begin module%4380835603C0.epilog preserve=yes
//## end module%4380835603C0.epilog


#endif
