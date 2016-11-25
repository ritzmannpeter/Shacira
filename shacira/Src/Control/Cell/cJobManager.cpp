//## begin module%41340E1301D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41340E1301D4.cm

//## begin module%41340E1301D4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41340E1301D4.cp

//## Module: cJobManager%41340E1301D4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJobManager.cpp

//## begin module%41340E1301D4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41340E1301D4.additionalIncludes

//## begin module%41340E1301D4.includes preserve=yes
//## end module%41340E1301D4.includes

// cContext
#include "System/Database/cContext.h"
// cJobs
#include "Control/Cell/cJobs.h"
// cJob
#include "Control/Cell/cJob.h"
// cJobManager
#include "Control/Cell/cJobManager.h"
//## begin module%41340E1301D4.additionalDeclarations preserve=yes
//## end module%41340E1301D4.additionalDeclarations


// Class cJobManager 



cJobManager::cJobManager()
  //## begin cJobManager::cJobManager%.hasinit preserve=no
      : _Jobs(NULL)
  //## end cJobManager::cJobManager%.hasinit
  //## begin cJobManager::cJobManager%.initialization preserve=yes
  //## end cJobManager::cJobManager%.initialization
{
  //## begin cJobManager::cJobManager%.body preserve=yes
_ASSERT_UNCOND
  //## end cJobManager::cJobManager%.body
}

cJobManager::cJobManager(const cJobManager &right)
  //## begin cJobManager::cJobManager%copy.hasinit preserve=no
      : _Jobs(NULL)
  //## end cJobManager::cJobManager%copy.hasinit
  //## begin cJobManager::cJobManager%copy.initialization preserve=yes
  //## end cJobManager::cJobManager%copy.initialization
{
  //## begin cJobManager::cJobManager%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cJobManager::cJobManager%copy.body
}

cJobManager::cJobManager (CONST_STRING_T name, cContext *context)
  //## begin cJobManager::cJobManager%1093930649.hasinit preserve=no
      : _Jobs(NULL)
  //## end cJobManager::cJobManager%1093930649.hasinit
  //## begin cJobManager::cJobManager%1093930649.initialization preserve=yes
  , cProgram(name, context)
  //## end cJobManager::cJobManager%1093930649.initialization
{
  //## begin cJobManager::cJobManager%1093930649.body preserve=yes
   _Jobs = new cJobs(this);
   _IdleTime = 100;
  //## end cJobManager::cJobManager%1093930649.body
}

cJobManager::cJobManager (cConfigurationObject *config_obj, cContext *context)
  //## begin cJobManager::cJobManager%1093930655.hasinit preserve=no
      : _Jobs(NULL)
  //## end cJobManager::cJobManager%1093930655.hasinit
  //## begin cJobManager::cJobManager%1093930655.initialization preserve=yes
  , cProgram(config_obj, context)
  //## end cJobManager::cJobManager%1093930655.initialization
{
  //## begin cJobManager::cJobManager%1093930655.body preserve=yes
   _Jobs = new cJobs(this);
   _IdleTime = 100;
  //## end cJobManager::cJobManager%1093930655.body
}


cJobManager::~cJobManager()
{
  //## begin cJobManager::~cJobManager%.body preserve=yes
   DELETE_OBJECT(cJobs, _Jobs)
  //## end cJobManager::~cJobManager%.body
}



//## Other Operations (implementation)
void cJobManager::ProcessEvent (cTransientObject *object)
{
  //## begin cJobManager::ProcessEvent%1093930650.body preserve=yes
  //## end cJobManager::ProcessEvent%1093930650.body
}

void cJobManager::Cycle ()
{
  //## begin cJobManager::Cycle%1093930651.body preserve=yes
   int dummy = 0;
  //## end cJobManager::Cycle%1093930651.body
}

void cJobManager::Initialize ()
{
  //## begin cJobManager::Initialize%1093930652.body preserve=yes
  //## end cJobManager::Initialize%1093930652.body
}

void cJobManager::SetJob (cJobSpec *job_spec)
{
  //## begin cJobManager::SetJob%1093930653.body preserve=yes
   if (_Jobs != NULL) {
      cJob * job = new cJob(job_spec);
      _Jobs->SetJob(job);
   }
  //## end cJobManager::SetJob%1093930653.body
}

cJobSpec * cJobManager::GetJobSpec (CONST_STRING_T job_name)
{
  //## begin cJobManager::GetJobSpec%1093930654.body preserve=yes
   if (_Jobs != NULL) {
      cJob * job = _Jobs->GetJob(job_name);
      if (job != NULL) {
         return job->JobSpec();
      } 
   }
   return NULL;
  //## end cJobManager::GetJobSpec%1093930654.body
}

// Additional Declarations
  //## begin cJobManager%41340E1301D4.declarations preserve=yes
  //## end cJobManager%41340E1301D4.declarations

//## begin module%41340E1301D4.epilog preserve=yes
//## end module%41340E1301D4.epilog
