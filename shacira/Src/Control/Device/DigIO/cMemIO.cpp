//## begin module%4047181A0232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4047181A0232.cm

//## begin module%4047181A0232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4047181A0232.cp

//## Module: cMemIO%4047181A0232; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cMemIO.cpp

//## begin module%4047181A0232.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4047181A0232.additionalIncludes

//## begin module%4047181A0232.includes preserve=yes
//## end module%4047181A0232.includes

// cMemIO
#include "Control/Device/DigIO/cMemIO.h"
//## begin module%4047181A0232.additionalDeclarations preserve=yes
//## end module%4047181A0232.additionalDeclarations


// Class cMemIO 

cMemIO::cMemIO()
  //## begin cMemIO::cMemIO%.hasinit preserve=no
  //## end cMemIO::cMemIO%.hasinit
  //## begin cMemIO::cMemIO%.initialization preserve=yes
  //## end cMemIO::cMemIO%.initialization
{
  //## begin cMemIO::cMemIO%.body preserve=yes
  //## end cMemIO::cMemIO%.body
}

cMemIO::cMemIO(const cMemIO &right)
  //## begin cMemIO::cMemIO%copy.hasinit preserve=no
  //## end cMemIO::cMemIO%copy.hasinit
  //## begin cMemIO::cMemIO%copy.initialization preserve=yes
  //## end cMemIO::cMemIO%copy.initialization
{
  //## begin cMemIO::cMemIO%copy.body preserve=yes
  //## end cMemIO::cMemIO%copy.body
}


cMemIO::~cMemIO()
{
  //## begin cMemIO::~cMemIO%.body preserve=yes
  //## end cMemIO::~cMemIO%.body
}



//## Other Operations (implementation)
void cMemIO::SetOutput (ULONG_T output_no)
{
  //## begin cMemIO::SetOutput%1078400667.body preserve=yes
  //## end cMemIO::SetOutput%1078400667.body
}

void cMemIO::ResetOutput (ULONG_T output_no)
{
  //## begin cMemIO::ResetOutput%1078400668.body preserve=yes
  //## end cMemIO::ResetOutput%1078400668.body
}

BOOL_T cMemIO::GetInput (ULONG_T input_no)
{
  //## begin cMemIO::GetInput%1078400669.body preserve=yes
return false;
  //## end cMemIO::GetInput%1078400669.body
}

ULONG_T cMemIO::GetInputs (void *inputs, ULONG_T buf_size)
{
  //## begin cMemIO::GetInputs%1078400670.body preserve=yes
return 0;
  //## end cMemIO::GetInputs%1078400670.body
}

ULONG_T cMemIO::WriteOutputs (void *outputs, ULONG_T len)
{
  //## begin cMemIO::WriteOutputs%1078410645.body preserve=yes
return 0;
  //## end cMemIO::WriteOutputs%1078410645.body
}

ULONG_T cMemIO::ReadOutputs (void *buf, ULONG_T buf_size)
{
  //## begin cMemIO::ReadOutputs%1078416422.body preserve=yes
return 0;
  //## end cMemIO::ReadOutputs%1078416422.body
}

void cMemIO::SetAllOutputs ()
{
  //## begin cMemIO::SetAllOutputs%1078416414.body preserve=yes
  //## end cMemIO::SetAllOutputs%1078416414.body
}

void cMemIO::ResetAllOutputs ()
{
  //## begin cMemIO::ResetAllOutputs%1078416415.body preserve=yes
  //## end cMemIO::ResetAllOutputs%1078416415.body
}

// Additional Declarations
  //## begin cMemIO%4047181A0232.declarations preserve=yes
  //## end cMemIO%4047181A0232.declarations

//## begin module%4047181A0232.epilog preserve=yes
//## end module%4047181A0232.epilog
