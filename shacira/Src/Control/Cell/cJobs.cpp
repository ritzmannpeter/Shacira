//## begin module%3E7705210399.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E7705210399.cm

//## begin module%3E7705210399.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E7705210399.cp

//## Module: cJobs%3E7705210399; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJobs.cpp

//## begin module%3E7705210399.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E7705210399.additionalIncludes

//## begin module%3E7705210399.includes preserve=yes
//## end module%3E7705210399.includes

// cJobSpec
#include "System/Objects/cJobSpec.h"
// cJobs
#include "Control/Cell/cJobs.h"
// cJob
#include "Control/Cell/cJob.h"
// cJobManager
#include "Control/Cell/cJobManager.h"
//## begin module%3E7705210399.additionalDeclarations preserve=yes
//## end module%3E7705210399.additionalDeclarations


// Class cJobs 



cJobs::cJobs()
  //## begin cJobs::cJobs%.hasinit preserve=no
      : _JobManager(NULL)
  //## end cJobs::cJobs%.hasinit
  //## begin cJobs::cJobs%.initialization preserve=yes
  //## end cJobs::cJobs%.initialization
{
  //## begin cJobs::cJobs%.body preserve=yes
_ASSERT_UNCOND
  //## end cJobs::cJobs%.body
}

cJobs::cJobs(const cJobs &right)
  //## begin cJobs::cJobs%copy.hasinit preserve=no
      : _JobManager(NULL)
  //## end cJobs::cJobs%copy.hasinit
  //## begin cJobs::cJobs%copy.initialization preserve=yes
  //## end cJobs::cJobs%copy.initialization
{
  //## begin cJobs::cJobs%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cJobs::cJobs%copy.body
}

cJobs::cJobs (cJobManager *job_manager)
  //## begin cJobs::cJobs%1047978429.hasinit preserve=no
      : _JobManager(NULL)
  //## end cJobs::cJobs%1047978429.hasinit
  //## begin cJobs::cJobs%1047978429.initialization preserve=yes
  //## end cJobs::cJobs%1047978429.initialization
{
  //## begin cJobs::cJobs%1047978429.body preserve=yes
	_JobManager = job_manager;
  //## end cJobs::cJobs%1047978429.body
}


cJobs::~cJobs()
{
  //## begin cJobs::~cJobs%.body preserve=yes
  //## end cJobs::~cJobs%.body
}



//## Other Operations (implementation)
void cJobs::LoadJobs ()
{
  //## begin cJobs::LoadJobs%1047978430.body preserve=yes
  //## end cJobs::LoadJobs%1047978430.body
}

void cJobs::SaveJobs ()
{
  //## begin cJobs::SaveJobs%1047978431.body preserve=yes
  //## end cJobs::SaveJobs%1047978431.body
}

cJobSpec * cJobs::LoadJob (CONST_STRING_T job_name)
{
  //## begin cJobs::LoadJob%1047978432.body preserve=yes
	return NULL;
  //## end cJobs::LoadJob%1047978432.body
}

void cJobs::SaveJob (cJob *job_spec)
{
  //## begin cJobs::SaveJob%1047978433.body preserve=yes
  //## end cJobs::SaveJob%1047978433.body
}

void cJobs::SetJob (cJob* job)
{
  //## begin cJobs::SetJob%1047993027.body preserve=yes
   _Jobs[job->Name().c_str()] = job;
  //## end cJobs::SetJob%1047993027.body
}

cJob * cJobs::GetJob (CONST_STRING_T job_name)
{
  //## begin cJobs::GetJob%1047993026.body preserve=yes
   std::map<STRING_T, cJob*>::const_iterator i = _Jobs.find(job_name);
	if (i == _Jobs.cend()) {
		return NULL;
	} else {
		return (*i).second;
	}
  //## end cJobs::GetJob%1047993026.body
}

// Additional Declarations
  //## begin cJobs%3E7705210399.declarations preserve=yes
  //## end cJobs%3E7705210399.declarations

//## begin module%3E7705210399.epilog preserve=yes
//## end module%3E7705210399.epilog
