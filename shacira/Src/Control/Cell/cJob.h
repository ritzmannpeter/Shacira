//## begin module%3E76F3320222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E76F3320222.cm

//## begin module%3E76F3320222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E76F3320222.cp

//## Module: cJob%3E76F3320222; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cJob.h

#ifndef cJob_h
#define cJob_h 1

//## begin module%3E76F3320222.includes preserve=yes
//## end module%3E76F3320222.includes


class __DLL_EXPORT__ cJobSpec;

//## begin module%3E76F3320222.additionalDeclarations preserve=yes
//## end module%3E76F3320222.additionalDeclarations


//## begin cJob%3E76F3320222.preface preserve=yes
//## end cJob%3E76F3320222.preface

//## Class: cJob%3E76F3320222
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cJob 
{
  //## begin cJob%3E76F3320222.initialDeclarations preserve=yes
public:
  //## end cJob%3E76F3320222.initialDeclarations

    //## Constructors (generated)
      cJob();

      cJob(const cJob &right);

    //## Constructors (specified)
      //## Operation: cJob%1047978427
      cJob (cJobSpec *job_spec);

    //## Destructor (generated)
      virtual ~cJob();


    //## Other Operations (specified)
      //## Operation: JobSpec%1093930657
      cJobSpec * JobSpec ();

      //## Operation: Name%1093930658
      STRING_T Name ();

  public:
    // Additional Public Declarations
      //## begin cJob%3E76F3320222.public preserve=yes
      //## end cJob%3E76F3320222.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%413417240203
      //## Role: cJob::JobSpec%413417250109
      //## begin cJob::JobSpec%413417250109.role preserve=no  public: cJobSpec { -> 1RFHN}
      cJobSpec *_JobSpec;
      //## end cJob::JobSpec%413417250109.role

    // Additional Protected Declarations
      //## begin cJob%3E76F3320222.protected preserve=yes
      //## end cJob%3E76F3320222.protected

  private:
    // Additional Private Declarations
      //## begin cJob%3E76F3320222.private preserve=yes
      //## end cJob%3E76F3320222.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cJob%3E76F3320222.implementation preserve=yes
      //## end cJob%3E76F3320222.implementation

};

//## begin cJob%3E76F3320222.postscript preserve=yes
//## end cJob%3E76F3320222.postscript

// Class cJob 

//## begin module%3E76F3320222.epilog preserve=yes
//## end module%3E76F3320222.epilog


#endif
