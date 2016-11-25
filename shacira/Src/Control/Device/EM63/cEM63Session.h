//## begin module%4380829603D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380829603D0.cm

//## begin module%4380829603D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380829603D0.cp

//## Module: cEM63Session%4380829603D0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Session.h

#ifndef cEM63Session_h
#define cEM63Session_h 1

//## begin module%4380829603D0.includes preserve=yes
//## end module%4380829603D0.includes

// eb_sema
#include "base/eb_sema.hpp"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cEM63Interface;
class __DLL_EXPORT__ cEM63Job;
class __DLL_EXPORT__ cEM63StyxParser;

//## begin module%4380829603D0.additionalDeclarations preserve=yes

typedef std::vector<cEM63Job*> JOB_VECTOR_T;

//## end module%4380829603D0.additionalDeclarations


//## begin cEM63Session%4380829603D0.preface preserve=yes
//## end cEM63Session%4380829603D0.preface

//## Class: cEM63Session%4380829603D0
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A409D80364;cFileSystemUtils { -> F}
//## Uses: <unnamed>%43A7C8D8007A;cEM63StyxParser { -> F}
//## Uses: <unnamed>%43A7FC60034F;cContext { -> F}
//## Uses: <unnamed>%43A8130701A6;cEM63Job { -> F}
//## Uses: <unnamed>%43BE3F9C014B;cMutexSem { -> }

class __DLL_EXPORT__ cEM63Session 
{
  //## begin cEM63Session%4380829603D0.initialDeclarations preserve=yes
public:
  //## end cEM63Session%4380829603D0.initialDeclarations

    //## Constructors (generated)
      cEM63Session();

      cEM63Session(const cEM63Session &right);

    //## Constructors (specified)
      //## Operation: cEM63Session%1133895373
      cEM63Session (cEM63Interface *itf, CONST_STRING_T request_file);

    //## Destructor (generated)
      virtual ~cEM63Session();


    //## Other Operations (specified)
      //## Operation: SetInterface%1134822065
      void SetInterface (cEM63Interface *itf);

      //## Operation: Interface%1134822067
      cEM63Interface * Interface ();

      //## Operation: AddJob%1133895375
      void AddJob (cEM63Job *job);

      //## Operation: Failed%1135017139
      void Failed (ULONG_T code, CONST_STRING_T param1 = "", CONST_STRING_T param2 = "");

      //## Operation: Process%1135068533
      BOOL_T Process (cContext *context);

      //## Operation: Start%1135068534
      BOOL_T Start ();

      //## Operation: Control%1135068535
      void Control ();

      //## Operation: Stop%1135068541
      void Stop ();

      //## Operation: CleanUp%1136213367
      void CleanUp ();

      //## Operation: Abort%1136213371
      void Abort (int abort_type, CONST_STRING_T name);

      //## Operation: Respond%1135017141
      void Respond ();

      //## Operation: IsActive%1135162873
      BOOL_T IsActive ();

      //## Operation: IsTerminated%1136286710
      BOOL_T IsTerminated ();

      //## Operation: HasFailed%1136457205
      BOOL_T HasFailed ();

      //## Operation: SetErrorInfo%1140161327
      void SetErrorInfo (int error_code, CONST_STRING_T param1, CONST_STRING_T param2);

      //## Operation: SetRequestFile%1166170820
      void SetRequestFile (const STRING_T &file);

      //## Operation: RequestFile%1166170821
      STRING_T RequestFile ();

      //## Operation: SetResponseFile%1166170822
      void SetResponseFile (const STRING_T &file);

      //## Operation: ResponseFile%1166170823
      STRING_T ResponseFile ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SessionId%4395DE920146
      ULONG_T get_SessionId () const;
      void set_SessionId (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cEM63Session%4380829603D0.public preserve=yes
      //## end cEM63Session%4380829603D0.public

  protected:
    // Data Members for Class Attributes

      //## begin cEM63Session::SessionId%4395DE920146.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _SessionId;
      //## end cEM63Session::SessionId%4395DE920146.attr

      //## Attribute: RequestFile%4395DE920147
      //## begin cEM63Session::RequestFile%4395DE920147.attr preserve=no  protected: STRING_T {U} 
      STRING_T _RequestFile;
      //## end cEM63Session::RequestFile%4395DE920147.attr

      //## Attribute: ResponseFile%4395DE920155
      //## begin cEM63Session::ResponseFile%4395DE920155.attr preserve=no  protected: STRING_T {U} 
      STRING_T _ResponseFile;
      //## end cEM63Session::ResponseFile%4395DE920155.attr

    // Data Members for Associations

      //## Association: Control::Device::EM63::<unnamed>%43A2BAF901CC
      //## Role: cEM63Session::Interface%43A2BAFA02F5
      //## begin cEM63Session::Interface%43A2BAFA02F5.role preserve=no  public: cEM63Interface { -> 1RFHN}
      cEM63Interface *_Interface;
      //## end cEM63Session::Interface%43A2BAFA02F5.role

    // Additional Protected Declarations
      //## begin cEM63Session%4380829603D0.protected preserve=yes
      //## end cEM63Session%4380829603D0.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Session%4380829603D0.private preserve=yes
      //## end cEM63Session%4380829603D0.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ParsePresentationRequest%1135068542
      BOOL_T ParsePresentationRequest (cEM63Job *job, CONST_STRING_T file, CONST_STRING_T source_code, STRING_T &err_text);

    // Data Members for Class Attributes

      //## Attribute: Jobs%43A80FAB006E
      //## begin cEM63Session::Jobs%43A80FAB006E.attr preserve=no  implementation: JOB_VECTOR_T {U} 
      JOB_VECTOR_T _Jobs;
      //## end cEM63Session::Jobs%43A80FAB006E.attr

      //## Attribute: Failed%43BCFC0900B8
      //## begin cEM63Session::Failed%43BCFC0900B8.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Failed;
      //## end cEM63Session::Failed%43BCFC0900B8.attr

      //## Attribute: ErrorCode%43A8119F0273
      //## begin cEM63Session::ErrorCode%43A8119F0273.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _ErrorCode;
      //## end cEM63Session::ErrorCode%43A8119F0273.attr

      //## Attribute: Param1%43A8119F0281
      //## begin cEM63Session::Param1%43A8119F0281.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Param1;
      //## end cEM63Session::Param1%43A8119F0281.attr

      //## Attribute: Param2%43A8119F0282
      //## begin cEM63Session::Param2%43A8119F0282.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Param2;
      //## end cEM63Session::Param2%43A8119F0282.attr

      //## Attribute: ErrorMsg%43B2B984017B
      //## begin cEM63Session::ErrorMsg%43B2B984017B.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ErrorMsg;
      //## end cEM63Session::ErrorMsg%43B2B984017B.attr

    // Additional Implementation Declarations
      //## begin cEM63Session%4380829603D0.implementation preserve=yes
      //## end cEM63Session%4380829603D0.implementation

};

//## begin cEM63Session%4380829603D0.postscript preserve=yes
//## end cEM63Session%4380829603D0.postscript

// Class cEM63Session 

//## begin module%4380829603D0.epilog preserve=yes
//## end module%4380829603D0.epilog


#endif
