//## begin module%4047174B006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4047174B006D.cm

//## begin module%4047174B006D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4047174B006D.cp

//## Module: cDigIO%4047174B006D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\DigIO\cDigIO.cpp

//## begin module%4047174B006D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4047174B006D.additionalIncludes

//## begin module%4047174B006D.includes preserve=yes
//## end module%4047174B006D.includes

// cDigIO
#include "Control/Device/DigIO/cDigIO.h"
//## begin module%4047174B006D.additionalDeclarations preserve=yes
//## end module%4047174B006D.additionalDeclarations


// Class cDigIO 




cDigIO::cDigIO()
  //## begin cDigIO::cDigIO%.hasinit preserve=no
      : _Inputs(0), _Outputs(0)
  //## end cDigIO::cDigIO%.hasinit
  //## begin cDigIO::cDigIO%.initialization preserve=yes
  //## end cDigIO::cDigIO%.initialization
{
  //## begin cDigIO::cDigIO%.body preserve=yes
  //## end cDigIO::cDigIO%.body
}

cDigIO::cDigIO(const cDigIO &right)
  //## begin cDigIO::cDigIO%copy.hasinit preserve=no
      : _Inputs(0), _Outputs(0)
  //## end cDigIO::cDigIO%copy.hasinit
  //## begin cDigIO::cDigIO%copy.initialization preserve=yes
  //## end cDigIO::cDigIO%copy.initialization
{
  //## begin cDigIO::cDigIO%copy.body preserve=yes
  //## end cDigIO::cDigIO%copy.body
}


cDigIO::~cDigIO()
{
  //## begin cDigIO::~cDigIO%.body preserve=yes
  //## end cDigIO::~cDigIO%.body
}


//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cDigIO::get_Inputs () const
{
  //## begin cDigIO::get_Inputs%4047189701C5.get preserve=no
  return _Inputs;
  //## end cDigIO::get_Inputs%4047189701C5.get
}

ULONG_T cDigIO::get_Outputs () const
{
  //## begin cDigIO::get_Outputs%4047189701C6.get preserve=no
  return _Outputs;
  //## end cDigIO::get_Outputs%4047189701C6.get
}

// Additional Declarations
  //## begin cDigIO%4047174B006D.declarations preserve=yes
  //## end cDigIO%4047174B006D.declarations

//## begin module%4047174B006D.epilog preserve=yes
//## end module%4047174B006D.epilog
