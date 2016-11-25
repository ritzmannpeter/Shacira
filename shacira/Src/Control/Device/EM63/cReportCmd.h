//## begin module%4380801B000C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380801B000C.cm

//## begin module%4380801B000C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380801B000C.cp

//## Module: cReportCmd%4380801B000C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cReportCmd.h

#ifndef cReportCmd_h
#define cReportCmd_h 1

//## begin module%4380801B000C.includes preserve=yes
//## end module%4380801B000C.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cEM63Interface;

//## begin module%4380801B000C.additionalDeclarations preserve=yes

typedef std::vector<STRING_T> PARAM_VECTOR_T;
typedef std::vector<cVarRef*> VARREF_VECTOR_T;

//## end module%4380801B000C.additionalDeclarations


//## begin cReportCmd%4380801B000C.preface preserve=yes
//## end cReportCmd%4380801B000C.preface

//## Class: cReportCmd%4380801B000C
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A7FC130032;cContext { -> F}
//## Uses: <unnamed>%43A801400032;cVarRef { -> F}
//## Uses: <unnamed>%43B260CC038F;cEM63Interface { -> F}

class __DLL_EXPORT__ cReportCmd : public cPresentationCmd  //## Inherits: <unnamed>%438082160028
{
  //## begin cReportCmd%4380801B000C.initialDeclarations preserve=yes
public:
  //## end cReportCmd%4380801B000C.initialDeclarations

    //## Constructors (generated)
      cReportCmd();

      cReportCmd(const cReportCmd &right);

    //## Constructors (specified)
      //## Operation: cReportCmd%1136548765
      cReportCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cReportCmd();


    //## Other Operations (specified)
      //## Operation: AddParameter%1134980234
      void AddParameter (CONST_STRING_T param_id);

      //## Operation: SetStartCondition%1134992979
      void SetStartCondition (cCondition *condition);

      //## Operation: SetStopCondition%1134992980
      void SetStopCondition (cCondition *condition);

      //## Operation: SetCycleCondition%1134992981
      void SetCycleCondition (cCondition *condition);

      //## Operation: SetReportCondition%1134992986
      void SetReportCondition (cCondition *condition);

      //## Operation: Process%1135078971
      virtual BOOL_T Process (cContext *context);

      //## Operation: Start%1135068546
      virtual BOOL_T Start ();

      //## Operation: Control%1135068547
      virtual void Control ();

      //## Operation: Stop%1135068548
      virtual void Stop ();

      //## Operation: IsReport%1136286712
      virtual BOOL_T IsReport ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: PresentationType%43A68A4201FB
      int get_PresentationType () const;
      void set_PresentationType (int value);

      //## Attribute: StartCondition%43A68BD6024B
      cCondition * get_StartCondition () const;
      void set_StartCondition (cCondition * value);

      //## Attribute: StopCondition%43A6A6950006
      cCondition * get_StopCondition () const;
      void set_StopCondition (cCondition * value);

      //## Attribute: CycleCondition%43A6A6A70342
      cCondition * get_CycleCondition () const;
      void set_CycleCondition (cCondition * value);

      //## Attribute: ReportCondition%43A7DCDF02D2
      cCondition * get_ReportCondition () const;
      void set_ReportCondition (cCondition * value);

      //## Attribute: Samples%43A68F6E0345
      ULONG_T get_Samples () const;
      void set_Samples (ULONG_T value);

      //## Attribute: Sessions%43A68F830345
      ULONG_T get_Sessions () const;
      void set_Sessions (ULONG_T value);

      //## Attribute: Count%43AACC0F0101
      ULONG_T get_Count () const;

  public:
    // Additional Public Declarations
      //## begin cReportCmd%4380801B000C.public preserve=yes
      //## end cReportCmd%4380801B000C.public

  protected:
    // Data Members for Class Attributes

      //## begin cReportCmd::PresentationType%43A68A4201FB.attr preserve=no  public: int {U} EM63_APPEND
      int _PresentationType;
      //## end cReportCmd::PresentationType%43A68A4201FB.attr

      //## begin cReportCmd::StartCondition%43A68BD6024B.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StartCondition;
      //## end cReportCmd::StartCondition%43A68BD6024B.attr

      //## begin cReportCmd::StopCondition%43A6A6950006.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_StopCondition;
      //## end cReportCmd::StopCondition%43A6A6950006.attr

      //## begin cReportCmd::CycleCondition%43A6A6A70342.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_CycleCondition;
      //## end cReportCmd::CycleCondition%43A6A6A70342.attr

      //## begin cReportCmd::ReportCondition%43A7DCDF02D2.attr preserve=no  public: cCondition * {U} NULL
      cCondition *_ReportCondition;
      //## end cReportCmd::ReportCondition%43A7DCDF02D2.attr

      //## begin cReportCmd::Samples%43A68F6E0345.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _Samples;
      //## end cReportCmd::Samples%43A68F6E0345.attr

      //## begin cReportCmd::Sessions%43A68F830345.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Sessions;
      //## end cReportCmd::Sessions%43A68F830345.attr

      //## begin cReportCmd::Count%43AACC0F0101.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Count;
      //## end cReportCmd::Count%43AACC0F0101.attr

    // Additional Protected Declarations
      //## begin cReportCmd%4380801B000C.protected preserve=yes
      //## end cReportCmd%4380801B000C.protected

  private:
    // Additional Private Declarations
      //## begin cReportCmd%4380801B000C.private preserve=yes
      //## end cReportCmd%4380801B000C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Cycle%1135179457
      void Cycle ();

      //## Operation: PrintHeader%1135179458
      void PrintHeader (cBufferedFile *file);

      //## Operation: PrintEntry%1135179459
      void PrintEntry (cBufferedFile *file);

    // Data Members for Class Attributes

      //## Attribute: Params%43A67DB2027A
      //## begin cReportCmd::Params%43A67DB2027A.attr preserve=no  implementation: PARAM_VECTOR_T {U} 
      PARAM_VECTOR_T _Params;
      //## end cReportCmd::Params%43A67DB2027A.attr

      //## Attribute: AbsCount%43AAD027022A
      //## begin cReportCmd::AbsCount%43AAD027022A.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _AbsCount;
      //## end cReportCmd::AbsCount%43AAD027022A.attr

      //## Attribute: FirstEntry%440C32FC0222
      //## begin cReportCmd::FirstEntry%440C32FC0222.attr preserve=no  implementation: BOOL_T {U} true
      BOOL_T _FirstEntry;
      //## end cReportCmd::FirstEntry%440C32FC0222.attr

    // Additional Implementation Declarations
      //## begin cReportCmd%4380801B000C.implementation preserve=yes
      //## end cReportCmd%4380801B000C.implementation

};

//## begin cReportCmd%4380801B000C.postscript preserve=yes
//## end cReportCmd%4380801B000C.postscript

// Class cReportCmd 

//## begin module%4380801B000C.epilog preserve=yes
//## end module%4380801B000C.epilog


#endif
