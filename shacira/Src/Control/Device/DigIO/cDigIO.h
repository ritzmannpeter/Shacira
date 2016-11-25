//## begin module%4047174B006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4047174B006D.cm

//## begin module%4047174B006D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4047174B006D.cp

//## Module: cDigIO%4047174B006D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cDigIO.h

#ifndef cDigIO_h
#define cDigIO_h 1

//## begin module%4047174B006D.includes preserve=yes
//## end module%4047174B006D.includes

//## begin module%4047174B006D.additionalDeclarations preserve=yes
//## end module%4047174B006D.additionalDeclarations


//## begin cDigIO%4047174B006D.preface preserve=yes
//## end cDigIO%4047174B006D.preface

//## Class: cDigIO%4047174B006D
//## Category: Control::Device::DigIO%40471A4D029F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cDigIO 
{
  //## begin cDigIO%4047174B006D.initialDeclarations preserve=yes
public:
  //## end cDigIO%4047174B006D.initialDeclarations

    //## Constructors (generated)
      cDigIO();

      cDigIO(const cDigIO &right);

    //## Destructor (generated)
      virtual ~cDigIO();


    //## Other Operations (specified)
      //## Operation: SetOutput%1078400663
      virtual void SetOutput (ULONG_T output_no) = 0;

      //## Operation: ResetOutput%1078400664
      virtual void ResetOutput (ULONG_T output_no) = 0;

      //## Operation: GetInput%1078400665
      virtual BOOL_T GetInput (ULONG_T input_no) = 0;

      //## Operation: GetInputs%1078400666
      virtual ULONG_T GetInputs (void *inputs, ULONG_T buf_size) = 0;

      //## Operation: WriteOutputs%1078410647
      virtual ULONG_T WriteOutputs (void *outputs, ULONG_T len) = 0;

      //## Operation: ReadOutputs%1078416425
      virtual ULONG_T ReadOutputs (void *buf, ULONG_T buf_size) = 0;

      //## Operation: SetAllOutputs%1078416420
      virtual void SetAllOutputs () = 0;

      //## Operation: ResetAllOutputs%1078416421
      virtual void ResetAllOutputs () = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Inputs%4047189701C5
      ULONG_T get_Inputs () const;

      //## Attribute: Outputs%4047189701C6
      ULONG_T get_Outputs () const;

  public:
    // Additional Public Declarations
      //## begin cDigIO%4047174B006D.public preserve=yes
      //## end cDigIO%4047174B006D.public

  protected:
    // Data Members for Class Attributes

      //## begin cDigIO::Inputs%4047189701C5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Inputs;
      //## end cDigIO::Inputs%4047189701C5.attr

      //## begin cDigIO::Outputs%4047189701C6.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Outputs;
      //## end cDigIO::Outputs%4047189701C6.attr

    // Additional Protected Declarations
      //## begin cDigIO%4047174B006D.protected preserve=yes
      //## end cDigIO%4047174B006D.protected

  private:
    // Additional Private Declarations
      //## begin cDigIO%4047174B006D.private preserve=yes
      //## end cDigIO%4047174B006D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDigIO%4047174B006D.implementation preserve=yes
      //## end cDigIO%4047174B006D.implementation

};

//## begin cDigIO%4047174B006D.postscript preserve=yes
//## end cDigIO%4047174B006D.postscript

// Class cDigIO 

//## begin module%4047174B006D.epilog preserve=yes
//## end module%4047174B006D.epilog


#endif
