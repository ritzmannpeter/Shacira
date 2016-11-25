//## begin module%3C99A64C0341.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C99A64C0341.cm

//## begin module%3C99A64C0341.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C99A64C0341.cp

//## Module: cIMMachineProgram%3C99A64C0341; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cIMMachineProgram.h

#ifndef cIMMachineProgram_h
#define cIMMachineProgram_h 1

//## begin module%3C99A64C0341.includes preserve=yes
//## end module%3C99A64C0341.includes

// cTimeObject
#include "System/cTimeObject.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"

class cConfigurationObject;
class cVariable;
class cCell;

//## begin module%3C99A64C0341.additionalDeclarations preserve=yes
//## end module%3C99A64C0341.additionalDeclarations


//## begin cIMMachineProgram%3C99A64C0341.preface preserve=yes
//## end cIMMachineProgram%3C99A64C0341.preface

//## Class: cIMMachineProgram%3C99A64C0341
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C99B8850141;cConfigurationObject { -> F}
//## Uses: <unnamed>%3C99B93602CC;cCell { -> F}
//## Uses: <unnamed>%3C99C9B20324;cVariable { -> F}
//## Uses: <unnamed>%3C9C833E02DA; { -> F}
//## Uses: <unnamed>%3E15617A02CE;cTimeObject { -> }

class cIMMachineProgram : public cProgram  //## Inherits: <unnamed>%3C99A6A8004B
{
  //## begin cIMMachineProgram%3C99A64C0341.initialDeclarations preserve=yes
  //## end cIMMachineProgram%3C99A64C0341.initialDeclarations

  public:
    //## Constructors (generated)
      cIMMachineProgram();

      cIMMachineProgram(const cIMMachineProgram &right);

    //## Constructors (specified)
      //## Operation: cIMMachineProgram%1016702701
      cIMMachineProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cIMMachineProgram();


    //## Other Operations (specified)
      //## Operation: Start%1047387669
      virtual BOOL_T Start ();

      //## Operation: Stop%1047387670
      virtual BOOL_T Stop ();

      //## Operation: ProcessEvent%1047387671
      virtual void ProcessEvent (cTransientObject *object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CycleTimeSet%3C99B415013D
      ULONG_T get_CycleTimeSet () const;
      void set_CycleTimeSet (ULONG_T value);

      //## Attribute: CycleTimeAct%3C99B44600CF
      ULONG_T get_CycleTimeAct () const;
      void set_CycleTimeAct (ULONG_T value);

      //## Attribute: ProductionState%3C99B4830091
      UCHAR_T get_ProductionState () const;
      void set_ProductionState (UCHAR_T value);

    // Additional Public Declarations
      //## begin cIMMachineProgram%3C99A64C0341.public preserve=yes
      //## end cIMMachineProgram%3C99A64C0341.public

  protected:
    // Data Members for Class Attributes

      //## begin cIMMachineProgram::CycleTimeSet%3C99B415013D.attr preserve=no  public: ULONG_T {U} 10000
      ULONG_T _CycleTimeSet;
      //## end cIMMachineProgram::CycleTimeSet%3C99B415013D.attr

      //## begin cIMMachineProgram::CycleTimeAct%3C99B44600CF.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CycleTimeAct;
      //## end cIMMachineProgram::CycleTimeAct%3C99B44600CF.attr

      //## begin cIMMachineProgram::ProductionState%3C99B4830091.attr preserve=no  public: UCHAR_T {U} SH_SETUP
      UCHAR_T _ProductionState;
      //## end cIMMachineProgram::ProductionState%3C99B4830091.attr

    // Additional Protected Declarations
      //## begin cIMMachineProgram%3C99A64C0341.protected preserve=yes
      //## end cIMMachineProgram%3C99A64C0341.protected

  private:
    // Additional Private Declarations
      //## begin cIMMachineProgram%3C99A64C0341.private preserve=yes
      //## end cIMMachineProgram%3C99A64C0341.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: CycleTimeLeft%3C99B5560379
      //## begin cIMMachineProgram::CycleTimeLeft%3C99B5560379.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _CycleTimeLeft;
      //## end cIMMachineProgram::CycleTimeLeft%3C99B5560379.attr

      //## Attribute: LastCycle%3C9A0E02038E
      //## begin cIMMachineProgram::LastCycle%3C9A0E02038E.attr preserve=no  implementation: cTimeObject {U} 
      cTimeObject _LastCycle;
      //## end cIMMachineProgram::LastCycle%3C9A0E02038E.attr

      //## Attribute: VCycleTime%3C99C9280022
      //## begin cIMMachineProgram::VCycleTime%3C99C9280022.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VCycleTime;
      //## end cIMMachineProgram::VCycleTime%3C99C9280022.attr

      //## Attribute: VStepCounter%3C99C96C03CD
      //## begin cIMMachineProgram::VStepCounter%3C99C96C03CD.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VStepCounter;
      //## end cIMMachineProgram::VStepCounter%3C99C96C03CD.attr

      //## Attribute: VGoodCycles%3C99C97B02F3
      //## begin cIMMachineProgram::VGoodCycles%3C99C97B02F3.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VGoodCycles;
      //## end cIMMachineProgram::VGoodCycles%3C99C97B02F3.attr

      //## Attribute: VBadCycles%3C99C98C00B2
      //## begin cIMMachineProgram::VBadCycles%3C99C98C00B2.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VBadCycles;
      //## end cIMMachineProgram::VBadCycles%3C99C98C00B2.attr

      //## Attribute: VOperationMode%3C99CEA20317
      //## begin cIMMachineProgram::VOperationMode%3C99CEA20317.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VOperationMode;
      //## end cIMMachineProgram::VOperationMode%3C99CEA20317.attr

      //## Attribute: VAlarms%3C99CCDE023B
      //## begin cIMMachineProgram::VAlarms%3C99CCDE023B.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VAlarms;
      //## end cIMMachineProgram::VAlarms%3C99CCDE023B.attr

      //## Attribute: VProductionSet%3CA30D8E0262
      //## begin cIMMachineProgram::VProductionSet%3CA30D8E0262.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VProductionSet;
      //## end cIMMachineProgram::VProductionSet%3CA30D8E0262.attr

      //## Attribute: VCavities%3CA30CBB02B8
      //## begin cIMMachineProgram::VCavities%3CA30CBB02B8.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VCavities;
      //## end cIMMachineProgram::VCavities%3CA30CBB02B8.attr

      //## Attribute: VGoodParts%3CA30D470061
      //## begin cIMMachineProgram::VGoodParts%3CA30D470061.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VGoodParts;
      //## end cIMMachineProgram::VGoodParts%3CA30D470061.attr

      //## Attribute: VBadParts%3CA30D5303A7
      //## begin cIMMachineProgram::VBadParts%3CA30D5303A7.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VBadParts;
      //## end cIMMachineProgram::VBadParts%3CA30D5303A7.attr

      //## Attribute: VShotCounter%3CA30D600175
      //## begin cIMMachineProgram::VShotCounter%3CA30D600175.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VShotCounter;
      //## end cIMMachineProgram::VShotCounter%3CA30D600175.attr

      //## Attribute: VAddingShotCounter%3CA30D6E02FC
      //## begin cIMMachineProgram::VAddingShotCounter%3CA30D6E02FC.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VAddingShotCounter;
      //## end cIMMachineProgram::VAddingShotCounter%3CA30D6E02FC.attr

      //## Attribute: VSubtractingShotCounter%3CA30D7B0264
      //## begin cIMMachineProgram::VSubtractingShotCounter%3CA30D7B0264.attr preserve=no  implementation: cVariable * {U} NULL
      cVariable *_VSubtractingShotCounter;
      //## end cIMMachineProgram::VSubtractingShotCounter%3CA30D7B0264.attr

    // Additional Implementation Declarations
      //## begin cIMMachineProgram%3C99A64C0341.implementation preserve=yes
      //## end cIMMachineProgram%3C99A64C0341.implementation

};

//## begin cIMMachineProgram%3C99A64C0341.postscript preserve=yes
//## end cIMMachineProgram%3C99A64C0341.postscript

// Class cIMMachineProgram 

//## begin module%3C99A64C0341.epilog preserve=yes
//## end module%3C99A64C0341.epilog


#endif
