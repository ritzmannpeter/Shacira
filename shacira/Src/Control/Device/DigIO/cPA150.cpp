//## begin module%404717E301B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%404717E301B5.cm

//## begin module%404717E301B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%404717E301B5.cp

//## Module: cPA150%404717E301B5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cPA150.cpp

//## begin module%404717E301B5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%404717E301B5.additionalIncludes

//## begin module%404717E301B5.includes preserve=yes
//## end module%404717E301B5.includes

// cPA150
#include "Control/Device/DigIO/cPA150.h"
//## begin module%404717E301B5.additionalDeclarations preserve=yes
//## end module%404717E301B5.additionalDeclarations


// Class cPA150 

cPA150::cPA150()
  //## begin cPA150::cPA150%.hasinit preserve=no
  //## end cPA150::cPA150%.hasinit
  //## begin cPA150::cPA150%.initialization preserve=yes
  //## end cPA150::cPA150%.initialization
{
  //## begin cPA150::cPA150%.body preserve=yes
  //## end cPA150::cPA150%.body
}

cPA150::cPA150(const cPA150 &right)
  //## begin cPA150::cPA150%copy.hasinit preserve=no
  //## end cPA150::cPA150%copy.hasinit
  //## begin cPA150::cPA150%copy.initialization preserve=yes
  //## end cPA150::cPA150%copy.initialization
{
  //## begin cPA150::cPA150%copy.body preserve=yes
  //## end cPA150::cPA150%copy.body
}


cPA150::~cPA150()
{
  //## begin cPA150::~cPA150%.body preserve=yes
  //## end cPA150::~cPA150%.body
}



//## Other Operations (implementation)
void cPA150::SetOutput (ULONG_T output_no)
{
  //## begin cPA150::SetOutput%1078400671.body preserve=yes
  //## end cPA150::SetOutput%1078400671.body
}

void cPA150::ResetOutput (ULONG_T output_no)
{
  //## begin cPA150::ResetOutput%1078400672.body preserve=yes
  //## end cPA150::ResetOutput%1078400672.body
}

BOOL_T cPA150::GetInput (ULONG_T input_no)
{
  //## begin cPA150::GetInput%1078400673.body preserve=yes
return false;
  //## end cPA150::GetInput%1078400673.body
}

ULONG_T cPA150::GetInputs (void *inputs, ULONG_T buf_size)
{
  //## begin cPA150::GetInputs%1078400674.body preserve=yes
   return 0;
  //## end cPA150::GetInputs%1078400674.body
}

ULONG_T cPA150::WriteOutputs (void *outputs, ULONG_T len)
{
  //## begin cPA150::WriteOutputs%1078410646.body preserve=yes
return 0;
  //## end cPA150::WriteOutputs%1078410646.body
}

ULONG_T cPA150::ReadOutputs (void *buf, ULONG_T buf_size)
{
  //## begin cPA150::ReadOutputs%1078416423.body preserve=yes
return 0;
  //## end cPA150::ReadOutputs%1078416423.body
}

void cPA150::SetAllOutputs ()
{
  //## begin cPA150::SetAllOutputs%1078416416.body preserve=yes
  //## end cPA150::SetAllOutputs%1078416416.body
}

void cPA150::ResetAllOutputs ()
{
  //## begin cPA150::ResetAllOutputs%1078416417.body preserve=yes
  //## end cPA150::ResetAllOutputs%1078416417.body
}

// Additional Declarations
  //## begin cPA150%404717E301B5.declarations preserve=yes
  //## end cPA150%404717E301B5.declarations

//## begin module%404717E301B5.epilog preserve=yes
//## end module%404717E301B5.epilog
