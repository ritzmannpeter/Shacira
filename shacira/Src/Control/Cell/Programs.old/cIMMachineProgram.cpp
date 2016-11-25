//## begin module%3C99A64C0341.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C99A64C0341.cm

//## begin module%3C99A64C0341.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C99A64C0341.cp

//## Module: cIMMachineProgram%3C99A64C0341; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cIMMachineProgram.cpp

//## begin module%3C99A64C0341.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C99A64C0341.additionalIncludes

//## begin module%3C99A64C0341.includes preserve=yes
//## end module%3C99A64C0341.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cVariable
#include "System/Database/cVariable.h"
// cCell
#include "Control/Cell/cCell.h"
// cIMMachineProgram
#include "Control/Cell/Programs/cIMMachineProgram.h"
//## begin module%3C99A64C0341.additionalDeclarations preserve=yes
//## end module%3C99A64C0341.additionalDeclarations


// Class cIMMachineProgram 



















cIMMachineProgram::cIMMachineProgram()
  //## begin cIMMachineProgram::cIMMachineProgram%.hasinit preserve=no
      : _CycleTimeSet(10000), _CycleTimeAct(0), _ProductionState(SH_SETUP), _CycleTimeLeft(0), _VCycleTime(NULL), _VStepCounter(NULL), _VGoodCycles(NULL), _VBadCycles(NULL), _VOperationMode(NULL), _VAlarms(NULL), _VProductionSet(NULL), _VCavities(NULL), _VGoodParts(NULL), _VBadParts(NULL), _VShotCounter(NULL), _VAddingShotCounter(NULL), _VSubtractingShotCounter(NULL)
  //## end cIMMachineProgram::cIMMachineProgram%.hasinit
  //## begin cIMMachineProgram::cIMMachineProgram%.initialization preserve=yes
  //## end cIMMachineProgram::cIMMachineProgram%.initialization
{
  //## begin cIMMachineProgram::cIMMachineProgram%.body preserve=yes
  //## end cIMMachineProgram::cIMMachineProgram%.body
}

cIMMachineProgram::cIMMachineProgram(const cIMMachineProgram &right)
  //## begin cIMMachineProgram::cIMMachineProgram%copy.hasinit preserve=no
      : _CycleTimeSet(10000), _CycleTimeAct(0), _ProductionState(SH_SETUP), _CycleTimeLeft(0), _VCycleTime(NULL), _VStepCounter(NULL), _VGoodCycles(NULL), _VBadCycles(NULL), _VOperationMode(NULL), _VAlarms(NULL), _VProductionSet(NULL), _VCavities(NULL), _VGoodParts(NULL), _VBadParts(NULL), _VShotCounter(NULL), _VAddingShotCounter(NULL), _VSubtractingShotCounter(NULL)
  //## end cIMMachineProgram::cIMMachineProgram%copy.hasinit
  //## begin cIMMachineProgram::cIMMachineProgram%copy.initialization preserve=yes
  //## end cIMMachineProgram::cIMMachineProgram%copy.initialization
{
  //## begin cIMMachineProgram::cIMMachineProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cIMMachineProgram::cIMMachineProgram%copy.body
}

cIMMachineProgram::cIMMachineProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cIMMachineProgram::cIMMachineProgram%1016702701.hasinit preserve=no
      : _CycleTimeSet(10000), _CycleTimeAct(0), _ProductionState(SH_SETUP), _CycleTimeLeft(0), _VCycleTime(NULL), _VStepCounter(NULL), _VGoodCycles(NULL), _VBadCycles(NULL), _VOperationMode(NULL), _VAlarms(NULL), _VProductionSet(NULL), _VCavities(NULL), _VGoodParts(NULL), _VBadParts(NULL), _VShotCounter(NULL), _VAddingShotCounter(NULL), _VSubtractingShotCounter(NULL)
  //## end cIMMachineProgram::cIMMachineProgram%1016702701.hasinit
  //## begin cIMMachineProgram::cIMMachineProgram%1016702701.initialization preserve=yes
   , cProgram(cell, config_obj)
  //## end cIMMachineProgram::cIMMachineProgram%1016702701.initialization
{
  //## begin cIMMachineProgram::cIMMachineProgram%1016702701.body preserve=yes
_ASSERT_COND(config_obj != NULL)
_ASSERT_COND(cell != NULL)
  //## end cIMMachineProgram::cIMMachineProgram%1016702701.body
}


cIMMachineProgram::~cIMMachineProgram()
{
  //## begin cIMMachineProgram::~cIMMachineProgram%.body preserve=yes
  //## end cIMMachineProgram::~cIMMachineProgram%.body
}



//## Other Operations (implementation)
BOOL_T cIMMachineProgram::Start ()
{
  //## begin cIMMachineProgram::Start%1047387669.body preserve=yes
	return true;
  //## end cIMMachineProgram::Start%1047387669.body
}

BOOL_T cIMMachineProgram::Stop ()
{
  //## begin cIMMachineProgram::Stop%1047387670.body preserve=yes
	return true;
  //## end cIMMachineProgram::Stop%1047387670.body
}

void cIMMachineProgram::ProcessEvent (cTransientObject *object)
{
  //## begin cIMMachineProgram::ProcessEvent%1047387671.body preserve=yes
  //## end cIMMachineProgram::ProcessEvent%1047387671.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cIMMachineProgram::get_CycleTimeSet () const
{
  //## begin cIMMachineProgram::get_CycleTimeSet%3C99B415013D.get preserve=no
  return _CycleTimeSet;
  //## end cIMMachineProgram::get_CycleTimeSet%3C99B415013D.get
}

void cIMMachineProgram::set_CycleTimeSet (ULONG_T value)
{
  //## begin cIMMachineProgram::set_CycleTimeSet%3C99B415013D.set preserve=no
  _CycleTimeSet = value;
  //## end cIMMachineProgram::set_CycleTimeSet%3C99B415013D.set
}

ULONG_T cIMMachineProgram::get_CycleTimeAct () const
{
  //## begin cIMMachineProgram::get_CycleTimeAct%3C99B44600CF.get preserve=no
  return _CycleTimeAct;
  //## end cIMMachineProgram::get_CycleTimeAct%3C99B44600CF.get
}

void cIMMachineProgram::set_CycleTimeAct (ULONG_T value)
{
  //## begin cIMMachineProgram::set_CycleTimeAct%3C99B44600CF.set preserve=no
  _CycleTimeAct = value;
  //## end cIMMachineProgram::set_CycleTimeAct%3C99B44600CF.set
}

UCHAR_T cIMMachineProgram::get_ProductionState () const
{
  //## begin cIMMachineProgram::get_ProductionState%3C99B4830091.get preserve=no
  return _ProductionState;
  //## end cIMMachineProgram::get_ProductionState%3C99B4830091.get
}

void cIMMachineProgram::set_ProductionState (UCHAR_T value)
{
  //## begin cIMMachineProgram::set_ProductionState%3C99B4830091.set preserve=no
  _ProductionState = value;
  //## end cIMMachineProgram::set_ProductionState%3C99B4830091.set
}

// Additional Declarations
  //## begin cIMMachineProgram%3C99A64C0341.declarations preserve=yes
  //## end cIMMachineProgram%3C99A64C0341.declarations

//## begin module%3C99A64C0341.epilog preserve=yes
//## end module%3C99A64C0341.epilog
