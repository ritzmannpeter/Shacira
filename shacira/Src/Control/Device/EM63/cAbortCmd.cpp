//## begin module%43807E60007A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43807E60007A.cm

//## begin module%43807E60007A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43807E60007A.cp

//## Module: cAbortCmd%43807E60007A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cAbortCmd.cpp

//## begin module%43807E60007A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43807E60007A.additionalIncludes

//## begin module%43807E60007A.includes preserve=yes
//## end module%43807E60007A.includes

// cAbortCmd
#include "Control/Device/EM63/cAbortCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%43807E60007A.additionalDeclarations preserve=yes
//## end module%43807E60007A.additionalDeclarations


// Class cAbortCmd 





cAbortCmd::cAbortCmd()
  //## begin cAbortCmd::cAbortCmd%.hasinit preserve=no
      : _AbortType(0)
  //## end cAbortCmd::cAbortCmd%.hasinit
  //## begin cAbortCmd::cAbortCmd%.initialization preserve=yes
  //## end cAbortCmd::cAbortCmd%.initialization
{
  //## begin cAbortCmd::cAbortCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cAbortCmd::cAbortCmd%.body
}

cAbortCmd::cAbortCmd(const cAbortCmd &right)
  //## begin cAbortCmd::cAbortCmd%copy.hasinit preserve=no
      : _AbortType(0)
  //## end cAbortCmd::cAbortCmd%copy.hasinit
  //## begin cAbortCmd::cAbortCmd%copy.initialization preserve=yes
  //## end cAbortCmd::cAbortCmd%copy.initialization
{
  //## begin cAbortCmd::cAbortCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cAbortCmd::cAbortCmd%copy.body
}

cAbortCmd::cAbortCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cAbortCmd::cAbortCmd%1136548768.hasinit preserve=no
      : _AbortType(0)
  //## end cAbortCmd::cAbortCmd%1136548768.hasinit
  //## begin cAbortCmd::cAbortCmd%1136548768.initialization preserve=yes
  , cPresentationCmd(job, command_name)
  //## end cAbortCmd::cAbortCmd%1136548768.initialization
{
  //## begin cAbortCmd::cAbortCmd%1136548768.body preserve=yes
   _CommandType = EM63_ABORT_COMMAND;
   INCREMENT_OBJECT_COUNT()
//## end cAbortCmd::cAbortCmd%1136548768.body
}


cAbortCmd::~cAbortCmd()
{
  //## begin cAbortCmd::~cAbortCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
  //## end cAbortCmd::~cAbortCmd%.body
}



//## Other Operations (implementation)
BOOL_T cAbortCmd::Start ()
{
  //## begin cAbortCmd::Start%1136457211.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      Started();
      STRING_T name;
      switch (_AbortType) {
      case ABORT_JOB:
         name = _JobName;
         break;
      case ABORT_REPORT:
         name = _ReportName;
         break;
      case ABORT_EVENT:
         name = _EventName;
         break;
      }
      _Interface->Abort(_AbortType, name.c_str());
      Terminated();
      return true;
   } else {
      return false;
   }
  //## end cAbortCmd::Start%1136457211.body
}

BOOL_T cAbortCmd::IsAbortCmd ()
{
  //## begin cAbortCmd::IsAbortCmd%1136457213.body preserve=yes
   return true;
  //## end cAbortCmd::IsAbortCmd%1136457213.body
}

//## Get and Set Operations for Class Attributes (implementation)

int cAbortCmd::get_AbortType () const
{
  //## begin cAbortCmd::get_AbortType%43BA5BD70324.get preserve=no
  return _AbortType;
  //## end cAbortCmd::get_AbortType%43BA5BD70324.get
}

void cAbortCmd::set_AbortType (int value)
{
  //## begin cAbortCmd::set_AbortType%43BA5BD70324.set preserve=no
  _AbortType = value;
  //## end cAbortCmd::set_AbortType%43BA5BD70324.set
}

STRING_T cAbortCmd::get_JobName () const
{
  //## begin cAbortCmd::get_JobName%43BA504600C5.get preserve=no
  return _JobName;
  //## end cAbortCmd::get_JobName%43BA504600C5.get
}

void cAbortCmd::set_JobName (STRING_T value)
{
  //## begin cAbortCmd::set_JobName%43BA504600C5.set preserve=no
  _JobName = value;
  //## end cAbortCmd::set_JobName%43BA504600C5.set
}

STRING_T cAbortCmd::get_ReportName () const
{
  //## begin cAbortCmd::get_ReportName%43BA505101C5.get preserve=no
  return _ReportName;
  //## end cAbortCmd::get_ReportName%43BA505101C5.get
}

void cAbortCmd::set_ReportName (STRING_T value)
{
  //## begin cAbortCmd::set_ReportName%43BA505101C5.set preserve=no
  _ReportName = value;
  //## end cAbortCmd::set_ReportName%43BA505101C5.set
}

STRING_T cAbortCmd::get_EventName () const
{
  //## begin cAbortCmd::get_EventName%43BA505A02B4.get preserve=no
  return _EventName;
  //## end cAbortCmd::get_EventName%43BA505A02B4.get
}

void cAbortCmd::set_EventName (STRING_T value)
{
  //## begin cAbortCmd::set_EventName%43BA505A02B4.set preserve=no
  _EventName = value;
  //## end cAbortCmd::set_EventName%43BA505A02B4.set
}

// Additional Declarations
  //## begin cAbortCmd%43807E60007A.declarations preserve=yes
  //## end cAbortCmd%43807E60007A.declarations

//## begin module%43807E60007A.epilog preserve=yes
//## end module%43807E60007A.epilog
