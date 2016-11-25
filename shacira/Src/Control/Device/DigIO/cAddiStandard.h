//## begin module%404717710000.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404717710000.cm

//## begin module%404717710000.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404717710000.cp

//## Module: cAddiStandard%404717710000; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cAddiStandard.h

#ifndef cAddiStandard_h
#define cAddiStandard_h 1

//## begin module%404717710000.includes preserve=yes

#ifdef __linux__

#else

#include "DEFINE.H"
#include "DIG_INP.H"
#include "DIG_OUT.H"
#include "ERROR.H"
#include "INIT.H"

#endif

//## end module%404717710000.includes

// cDigIO
#include "Control/Device/DigIO/cDigIO.h"
//## begin module%404717710000.additionalDeclarations preserve=yes

#define INVALID_DRIVER_HANDLE    ((DWORD)-1)

//## end module%404717710000.additionalDeclarations


//## begin cAddiStandard%404717710000.preface preserve=yes
//## end cAddiStandard%404717710000.preface

//## Class: cAddiStandard%404717710000
//## Category: Control::Device::DigIO%40471A4D029F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cAddiStandard : public cDigIO  //## Inherits: <unnamed>%404717B801D4
{
  //## begin cAddiStandard%404717710000.initialDeclarations preserve=yes
public:
  //## end cAddiStandard%404717710000.initialDeclarations

    //## Constructors (generated)
      cAddiStandard();

      cAddiStandard(const cAddiStandard &right);

    //## Destructor (generated)
      virtual ~cAddiStandard();


    //## Other Operations (specified)
      //## Operation: SetOutput%1078400675
      virtual void SetOutput (ULONG_T output_no);

      //## Operation: ResetOutput%1078400676
      virtual void ResetOutput (ULONG_T output_no);

      //## Operation: GetInput%1078400677
      virtual BOOL_T GetInput (ULONG_T input_no);

      //## Operation: GetInputs%1078400678
      virtual ULONG_T GetInputs (void *inputs, ULONG_T buf_size);

      //## Operation: WriteOutputs%1078410644
      virtual ULONG_T WriteOutputs (void *outputs, ULONG_T len);

      //## Operation: ReadOutputs%1078416424
      virtual ULONG_T ReadOutputs (void *buf, ULONG_T buf_size);

      //## Operation: SetAllOutputs%1078416418
      virtual void SetAllOutputs ();

      //## Operation: ResetAllOutputs%1078416419
      virtual void ResetAllOutputs ();

  public:
    // Additional Public Declarations
      //## begin cAddiStandard%404717710000.public preserve=yes
      //## end cAddiStandard%404717710000.public

  protected:
    // Additional Protected Declarations
      //## begin cAddiStandard%404717710000.protected preserve=yes
      //## end cAddiStandard%404717710000.protected

  private:
    // Additional Private Declarations
      //## begin cAddiStandard%404717710000.private preserve=yes
      //## end cAddiStandard%404717710000.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Handle%404718B000CB
      //## begin cAddiStandard::Handle%404718B000CB.attr preserve=no  implementation: DWORD {U} INVALID_DRIVER_HANDLE
      DWORD _Handle;
      //## end cAddiStandard::Handle%404718B000CB.attr

    // Additional Implementation Declarations
      //## begin cAddiStandard%404717710000.implementation preserve=yes
      //## end cAddiStandard%404717710000.implementation

};

//## begin cAddiStandard%404717710000.postscript preserve=yes
//## end cAddiStandard%404717710000.postscript

// Class cAddiStandard 

//## begin module%404717710000.epilog preserve=yes
//## end module%404717710000.epilog


#endif
