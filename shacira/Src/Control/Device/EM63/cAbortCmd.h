//## begin module%43807E60007A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43807E60007A.cm

//## begin module%43807E60007A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43807E60007A.cp

//## Module: cAbortCmd%43807E60007A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cAbortCmd.h

#ifndef cAbortCmd_h
#define cAbortCmd_h 1

//## begin module%43807E60007A.includes preserve=yes
//## end module%43807E60007A.includes

// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cEM63Interface;

//## begin module%43807E60007A.additionalDeclarations preserve=yes
//## end module%43807E60007A.additionalDeclarations


//## begin cAbortCmd%43807E60007A.preface preserve=yes
//## end cAbortCmd%43807E60007A.preface

//## Class: cAbortCmd%43807E60007A
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43BD099A02F9;cEM63Interface { -> F}

class __DLL_EXPORT__ cAbortCmd : public cPresentationCmd  //## Inherits: <unnamed>%43807FE502BB
{
  //## begin cAbortCmd%43807E60007A.initialDeclarations preserve=yes
public:
  //## end cAbortCmd%43807E60007A.initialDeclarations

    //## Constructors (generated)
      cAbortCmd();

      cAbortCmd(const cAbortCmd &right);

    //## Constructors (specified)
      //## Operation: cAbortCmd%1136548768
      cAbortCmd (cEM63Job *job, CONST_STRING_T command_name = "");

    //## Destructor (generated)
      virtual ~cAbortCmd();


    //## Other Operations (specified)
      //## Operation: Start%1136457211
      virtual BOOL_T Start ();

      //## Operation: IsAbortCmd%1136457213
      virtual BOOL_T IsAbortCmd ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: AbortType%43BA5BD70324
      int get_AbortType () const;
      void set_AbortType (int value);

      //## Attribute: JobName%43BA504600C5
      STRING_T get_JobName () const;
      void set_JobName (STRING_T value);

      //## Attribute: ReportName%43BA505101C5
      STRING_T get_ReportName () const;
      void set_ReportName (STRING_T value);

      //## Attribute: EventName%43BA505A02B4
      STRING_T get_EventName () const;
      void set_EventName (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cAbortCmd%43807E60007A.public preserve=yes
      //## end cAbortCmd%43807E60007A.public

  protected:
    // Data Members for Class Attributes

      //## begin cAbortCmd::AbortType%43BA5BD70324.attr preserve=no  public: int {U} 0
      int _AbortType;
      //## end cAbortCmd::AbortType%43BA5BD70324.attr

      //## begin cAbortCmd::JobName%43BA504600C5.attr preserve=no  public: STRING_T {U} 
      STRING_T _JobName;
      //## end cAbortCmd::JobName%43BA504600C5.attr

      //## begin cAbortCmd::ReportName%43BA505101C5.attr preserve=no  public: STRING_T {U} 
      STRING_T _ReportName;
      //## end cAbortCmd::ReportName%43BA505101C5.attr

      //## begin cAbortCmd::EventName%43BA505A02B4.attr preserve=no  public: STRING_T {U} 
      STRING_T _EventName;
      //## end cAbortCmd::EventName%43BA505A02B4.attr

    // Additional Protected Declarations
      //## begin cAbortCmd%43807E60007A.protected preserve=yes
      //## end cAbortCmd%43807E60007A.protected

  private:
    // Additional Private Declarations
      //## begin cAbortCmd%43807E60007A.private preserve=yes
      //## end cAbortCmd%43807E60007A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAbortCmd%43807E60007A.implementation preserve=yes
      //## end cAbortCmd%43807E60007A.implementation

};

//## begin cAbortCmd%43807E60007A.postscript preserve=yes
//## end cAbortCmd%43807E60007A.postscript

// Class cAbortCmd 

//## begin module%43807E60007A.epilog preserve=yes
//## end module%43807E60007A.epilog


#endif
