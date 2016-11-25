//## begin module%3C59098602B7.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C59098602B7.cm

//## begin module%3C59098602B7.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C59098602B7.cp

//## Module: cShutDownControl%3C59098602B7; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cShutDownControl.h

#ifndef cShutDownControl_h
#define cShutDownControl_h 1

//## begin module%3C59098602B7.includes preserve=yes
//## end module%3C59098602B7.includes

// cControlThread
#include "System/Threads/cControlThread.h"
//## begin module%3C59098602B7.additionalDeclarations preserve=yes
//## end module%3C59098602B7.additionalDeclarations


//## begin cShutDownControl%3C59098602B7.preface preserve=yes
//## end cShutDownControl%3C59098602B7.preface

//## Class: cShutDownControl%3C59098602B7
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cShutDownControl : public cControlThread  //## Inherits: <unnamed>%3C5909BC00CA
{
  //## begin cShutDownControl%3C59098602B7.initialDeclarations preserve=yes
public:
  //## end cShutDownControl%3C59098602B7.initialDeclarations

    //## Constructors (generated)
      cShutDownControl();

      cShutDownControl(const cShutDownControl &right);

    //## Constructors (specified)
      //## Operation: cShutDownControl%1012464114
      cShutDownControl (ULONG_T control_time);

    //## Destructor (generated)
      virtual ~cShutDownControl();


    //## Other Operations (specified)
      //## Operation: MainFunc%1012464115
      virtual INT_T MainFunc (void *extra);

  public:
    // Additional Public Declarations
      //## begin cShutDownControl%3C59098602B7.public preserve=yes
      //## end cShutDownControl%3C59098602B7.public

  protected:
    // Additional Protected Declarations
      //## begin cShutDownControl%3C59098602B7.protected preserve=yes
      //## end cShutDownControl%3C59098602B7.protected

  private:
    // Additional Private Declarations
      //## begin cShutDownControl%3C59098602B7.private preserve=yes
      //## end cShutDownControl%3C59098602B7.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ShutDownControlTime%3C590AA10079
      //## begin cShutDownControl::ShutDownControlTime%3C590AA10079.attr preserve=no  implementation: ULONG_T {U} 10000
      ULONG_T _ShutDownControlTime;
      //## end cShutDownControl::ShutDownControlTime%3C590AA10079.attr

    // Additional Implementation Declarations
      //## begin cShutDownControl%3C59098602B7.implementation preserve=yes
      //## end cShutDownControl%3C59098602B7.implementation

};

//## begin cShutDownControl%3C59098602B7.postscript preserve=yes
//## end cShutDownControl%3C59098602B7.postscript

// Class cShutDownControl 

//## begin module%3C59098602B7.epilog preserve=yes
//## end module%3C59098602B7.epilog


#endif
