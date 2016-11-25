//## begin module%404717E301B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404717E301B5.cm

//## begin module%404717E301B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404717E301B5.cp

//## Module: cPA150%404717E301B5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cPA150.h

#ifndef cPA150_h
#define cPA150_h 1

//## begin module%404717E301B5.includes preserve=yes
//## end module%404717E301B5.includes

// cDigIO
#include "Control/Device/DigIO/cDigIO.h"
//## begin module%404717E301B5.additionalDeclarations preserve=yes
//## end module%404717E301B5.additionalDeclarations


//## begin cPA150%404717E301B5.preface preserve=yes
//## end cPA150%404717E301B5.preface

//## Class: cPA150%404717E301B5
//## Category: Control::Device::DigIO%40471A4D029F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPA150 : public cDigIO  //## Inherits: <unnamed>%40471835000F
{
  //## begin cPA150%404717E301B5.initialDeclarations preserve=yes
public:
  //## end cPA150%404717E301B5.initialDeclarations

    //## Constructors (generated)
      cPA150();

      cPA150(const cPA150 &right);

    //## Destructor (generated)
      virtual ~cPA150();


    //## Other Operations (specified)
      //## Operation: SetOutput%1078400671
      virtual void SetOutput (ULONG_T output_no);

      //## Operation: ResetOutput%1078400672
      virtual void ResetOutput (ULONG_T output_no);

      //## Operation: GetInput%1078400673
      virtual BOOL_T GetInput (ULONG_T input_no);

      //## Operation: GetInputs%1078400674
      virtual ULONG_T GetInputs (void *inputs, ULONG_T buf_size);

      //## Operation: WriteOutputs%1078410646
      virtual ULONG_T WriteOutputs (void *outputs, ULONG_T len);

      //## Operation: ReadOutputs%1078416423
      virtual ULONG_T ReadOutputs (void *buf, ULONG_T buf_size);

      //## Operation: SetAllOutputs%1078416416
      virtual void SetAllOutputs ();

      //## Operation: ResetAllOutputs%1078416417
      virtual void ResetAllOutputs ();

  public:
    // Additional Public Declarations
      //## begin cPA150%404717E301B5.public preserve=yes
      //## end cPA150%404717E301B5.public

  protected:
    // Additional Protected Declarations
      //## begin cPA150%404717E301B5.protected preserve=yes
      //## end cPA150%404717E301B5.protected

  private:
    // Additional Private Declarations
      //## begin cPA150%404717E301B5.private preserve=yes
      //## end cPA150%404717E301B5.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cPA150%404717E301B5.implementation preserve=yes
      //## end cPA150%404717E301B5.implementation

};

//## begin cPA150%404717E301B5.postscript preserve=yes
//## end cPA150%404717E301B5.postscript

// Class cPA150 

//## begin module%404717E301B5.epilog preserve=yes
//## end module%404717E301B5.epilog


#endif
