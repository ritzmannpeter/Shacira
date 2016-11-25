//## begin module%3E76F3320222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E76F3320222.cm

//## begin module%3E76F3320222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E76F3320222.cp

//## Module: cJob%3E76F3320222; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJob.cpp

//## begin module%3E76F3320222.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E76F3320222.additionalIncludes

//## begin module%3E76F3320222.includes preserve=yes
//## end module%3E76F3320222.includes

// cJobSpec
#include "System/Objects/cJobSpec.h"
// cJob
#include "Control/Cell/cJob.h"
//## begin module%3E76F3320222.additionalDeclarations preserve=yes
//## end module%3E76F3320222.additionalDeclarations


// Class cJob 



cJob::cJob()
  //## begin cJob::cJob%.hasinit preserve=no
      : _JobSpec(NULL)
  //## end cJob::cJob%.hasinit
  //## begin cJob::cJob%.initialization preserve=yes
  //## end cJob::cJob%.initialization
{
  //## begin cJob::cJob%.body preserve=yes
_ASSERT_UNCOND
  //## end cJob::cJob%.body
}

cJob::cJob(const cJob &right)
  //## begin cJob::cJob%copy.hasinit preserve=no
      : _JobSpec(NULL)
  //## end cJob::cJob%copy.hasinit
  //## begin cJob::cJob%copy.initialization preserve=yes
  //## end cJob::cJob%copy.initialization
{
  //## begin cJob::cJob%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cJob::cJob%copy.body
}

cJob::cJob (cJobSpec *job_spec)
  //## begin cJob::cJob%1047978427.hasinit preserve=no
      : _JobSpec(NULL)
  //## end cJob::cJob%1047978427.hasinit
  //## begin cJob::cJob%1047978427.initialization preserve=yes
  //## end cJob::cJob%1047978427.initialization
{
  //## begin cJob::cJob%1047978427.body preserve=yes
_ASSERT_COND(job_spec != NULL)
   _JobSpec = job_spec;
  //## end cJob::cJob%1047978427.body
}


cJob::~cJob()
{
  //## begin cJob::~cJob%.body preserve=yes
  //## end cJob::~cJob%.body
}



//## Other Operations (implementation)
cJobSpec * cJob::JobSpec ()
{
  //## begin cJob::JobSpec%1093930657.body preserve=yes
   return _JobSpec;
  //## end cJob::JobSpec%1093930657.body
}

STRING_T cJob::Name ()
{
  //## begin cJob::Name%1093930658.body preserve=yes
   if (_JobSpec != NULL) {
      return _JobSpec->get_JobName();
   } else {
      return "?";
   }
  //## end cJob::Name%1093930658.body
}

// Additional Declarations
  //## begin cJob%3E76F3320222.declarations preserve=yes
  //## end cJob%3E76F3320222.declarations

//## begin module%3E76F3320222.epilog preserve=yes
//## end module%3E76F3320222.epilog
