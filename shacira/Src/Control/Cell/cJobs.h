//## begin module%3E7705210399.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E7705210399.cm

//## begin module%3E7705210399.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E7705210399.cp

//## Module: cJobs%3E7705210399; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJobs.h

#ifndef cJobs_h
#define cJobs_h 1

//## begin module%3E7705210399.includes preserve=yes
//## end module%3E7705210399.includes


class __DLL_EXPORT__ cJobSpec;
class __DLL_EXPORT__ cJob;
class __DLL_EXPORT__ cJobManager;

//## begin module%3E7705210399.additionalDeclarations preserve=yes
//## end module%3E7705210399.additionalDeclarations


//## begin cJobs%3E7705210399.preface preserve=yes
//## end cJobs%3E7705210399.preface

//## Class: cJobs%3E7705210399
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%413416D8036B;cJobSpec { -> F}

class __DLL_EXPORT__ cJobs 
{
  //## begin cJobs%3E7705210399.initialDeclarations preserve=yes
public:
  //## end cJobs%3E7705210399.initialDeclarations

    //## Constructors (generated)
      cJobs();

      cJobs(const cJobs &right);

    //## Constructors (specified)
      //## Operation: cJobs%1047978429
      cJobs (cJobManager *job_manager);

    //## Destructor (generated)
      virtual ~cJobs();


    //## Other Operations (specified)
      //## Operation: LoadJobs%1047978430
      void LoadJobs ();

      //## Operation: SaveJobs%1047978431
      void SaveJobs ();

      //## Operation: LoadJob%1047978432
      cJobSpec * LoadJob (CONST_STRING_T job_name);

      //## Operation: SaveJob%1047978433
      void SaveJob (cJob *job_spec);

      //## Operation: SetJob%1047993027
      void SetJob (cJob* job);

      //## Operation: GetJob%1047993026
      cJob * GetJob (CONST_STRING_T job_name);

  public:
    // Additional Public Declarations
      //## begin cJobs%3E7705210399.public preserve=yes
      //## end cJobs%3E7705210399.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%3E77055A01F4
      //## Role: cJobs::Jobs%3E77055B00FA
      //## Qualifier: name%3E7726BE0222; STRING_T
      //## begin cJobs::Jobs%3E77055B00FA.role preserve=no  public: cJob { -> 0..nRFHN}
      std::map<STRING_T, cJob*> _Jobs;
      //## end cJobs::Jobs%3E77055B00FA.role

      //## Association: Control::Cell::<unnamed>%4134126A01F4
      //## Role: cJobs::JobManager%4134126B0291
      //## begin cJobs::JobManager%4134126B0291.role preserve=no  public: cJobManager {1 -> 1RFHN}
      cJobManager *_JobManager;
      //## end cJobs::JobManager%4134126B0291.role

    // Additional Protected Declarations
      //## begin cJobs%3E7705210399.protected preserve=yes
      //## end cJobs%3E7705210399.protected

  private:
    // Additional Private Declarations
      //## begin cJobs%3E7705210399.private preserve=yes
      //## end cJobs%3E7705210399.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cJobs%3E7705210399.implementation preserve=yes
      //## end cJobs%3E7705210399.implementation

};

//## begin cJobs%3E7705210399.postscript preserve=yes
//## end cJobs%3E7705210399.postscript

// Class cJobs 

//## begin module%3E7705210399.epilog preserve=yes
//## end module%3E7705210399.epilog


#endif
