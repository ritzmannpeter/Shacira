//## begin module%41340E1301D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41340E1301D4.cm

//## begin module%41340E1301D4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41340E1301D4.cp

//## Module: cJobManager%41340E1301D4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJobManager.h

#ifndef cJobManager_h
#define cJobManager_h 1

//## begin module%41340E1301D4.includes preserve=yes
//## end module%41340E1301D4.includes

// cProgram
#include "Control/Cell/cProgram.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cJobs;
class __DLL_EXPORT__ cJob;

//## begin module%41340E1301D4.additionalDeclarations preserve=yes
//## end module%41340E1301D4.additionalDeclarations


//## begin cJobManager%41340E1301D4.preface preserve=yes
//## end cJobManager%41340E1301D4.preface

//## Class: cJobManager%41340E1301D4
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%41340F7E035B;cContext { -> F}
//## Uses: <unnamed>%41341F700222;cJob { -> F}

class __DLL_EXPORT__ cJobManager : public cProgram  //## Inherits: <unnamed>%41340E56029F
{
  //## begin cJobManager%41340E1301D4.initialDeclarations preserve=yes
public:
  //## end cJobManager%41340E1301D4.initialDeclarations

    //## Constructors (generated)
      cJobManager();

      cJobManager(const cJobManager &right);

    //## Constructors (specified)
      //## Operation: cJobManager%1093930649
      cJobManager (CONST_STRING_T name, cContext *context);

      //## Operation: cJobManager%1093930655
      cJobManager (cConfigurationObject *config_obj, cContext *context);

    //## Destructor (generated)
      virtual ~cJobManager();


    //## Other Operations (specified)
      //## Operation: SetJob%1093930653
      void SetJob (cJobSpec *job_spec);

      //## Operation: GetJobSpec%1093930654
      cJobSpec * GetJobSpec (CONST_STRING_T job_name);

  public:
    // Additional Public Declarations
      //## begin cJobManager%41340E1301D4.public preserve=yes
      //## end cJobManager%41340E1301D4.public

  protected:

    //## Other Operations (specified)
      //## Operation: ProcessEvent%1093930650
      virtual void ProcessEvent (cTransientObject *object);

      //## Operation: Cycle%1093930651
      virtual void Cycle ();

      //## Operation: Initialize%1093930652
      virtual void Initialize ();

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%4134126A01F4
      //## Role: cJobManager::Jobs%4134126B0290
      //## begin cJobManager::Jobs%4134126B0290.role preserve=no  public: cJobs {1 -> 1RFHN}
      cJobs *_Jobs;
      //## end cJobManager::Jobs%4134126B0290.role

    // Additional Protected Declarations
      //## begin cJobManager%41340E1301D4.protected preserve=yes
      //## end cJobManager%41340E1301D4.protected

  private:
    // Additional Private Declarations
      //## begin cJobManager%41340E1301D4.private preserve=yes
      //## end cJobManager%41340E1301D4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cJobManager%41340E1301D4.implementation preserve=yes
      //## end cJobManager%41340E1301D4.implementation

};

//## begin cJobManager%41340E1301D4.postscript preserve=yes
//## end cJobManager%41340E1301D4.postscript

// Class cJobManager 

//## begin module%41340E1301D4.epilog preserve=yes
//## end module%41340E1301D4.epilog


#endif
