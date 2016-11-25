//## begin module%4047181A0232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4047181A0232.cm

//## begin module%4047181A0232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4047181A0232.cp

//## Module: cMemIO%4047181A0232; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cMemIO.h

#ifndef cMemIO_h
#define cMemIO_h 1

//## begin module%4047181A0232.includes preserve=yes
//## end module%4047181A0232.includes

// cDigIO
#include "Control/Device/DigIO/cDigIO.h"
//## begin module%4047181A0232.additionalDeclarations preserve=yes
//## end module%4047181A0232.additionalDeclarations


//## begin cMemIO%4047181A0232.preface preserve=yes
//## end cMemIO%4047181A0232.preface

//## Class: cMemIO%4047181A0232
//## Category: Control::Device::DigIO%40471A4D029F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cMemIO : public cDigIO  //## Inherits: <unnamed>%4047183B033C
{
  //## begin cMemIO%4047181A0232.initialDeclarations preserve=yes
public:
  //## end cMemIO%4047181A0232.initialDeclarations

    //## Constructors (generated)
      cMemIO();

      cMemIO(const cMemIO &right);

    //## Destructor (generated)
      virtual ~cMemIO();


    //## Other Operations (specified)
      //## Operation: SetOutput%1078400667
      virtual void SetOutput (ULONG_T output_no);

      //## Operation: ResetOutput%1078400668
      virtual void ResetOutput (ULONG_T output_no);

      //## Operation: GetInput%1078400669
      virtual BOOL_T GetInput (ULONG_T input_no);

      //## Operation: GetInputs%1078400670
      virtual ULONG_T GetInputs (void *inputs, ULONG_T buf_size);

      //## Operation: WriteOutputs%1078410645
      virtual ULONG_T WriteOutputs (void *outputs, ULONG_T len);

      //## Operation: ReadOutputs%1078416422
      virtual ULONG_T ReadOutputs (void *buf, ULONG_T buf_size);

      //## Operation: SetAllOutputs%1078416414
      virtual void SetAllOutputs ();

      //## Operation: ResetAllOutputs%1078416415
      virtual void ResetAllOutputs ();

  public:
    // Additional Public Declarations
      //## begin cMemIO%4047181A0232.public preserve=yes
      //## end cMemIO%4047181A0232.public

  protected:
    // Additional Protected Declarations
      //## begin cMemIO%4047181A0232.protected preserve=yes
      //## end cMemIO%4047181A0232.protected

  private:
    // Additional Private Declarations
      //## begin cMemIO%4047181A0232.private preserve=yes
      //## end cMemIO%4047181A0232.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cMemIO%4047181A0232.implementation preserve=yes
      //## end cMemIO%4047181A0232.implementation

};

//## begin cMemIO%4047181A0232.postscript preserve=yes
//## end cMemIO%4047181A0232.postscript

// Class cMemIO 

//## begin module%4047181A0232.epilog preserve=yes
//## end module%4047181A0232.epilog


#endif
