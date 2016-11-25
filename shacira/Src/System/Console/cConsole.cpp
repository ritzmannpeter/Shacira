//## begin module%3D402C9600B0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D402C9600B0.cm

//## begin module%3D402C9600B0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D402C9600B0.cp

//## Module: cConsole%3D402C9600B0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cConsole.cpp

//## begin module%3D402C9600B0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D402C9600B0.additionalIncludes

//## begin module%3D402C9600B0.includes preserve=yes
//## end module%3D402C9600B0.includes

// cConsole
#include "System/Console/cConsole.h"
//## begin module%3D402C9600B0.additionalDeclarations preserve=yes
//## end module%3D402C9600B0.additionalDeclarations


// Class cConsole 



cConsole::cConsole()
  //## begin cConsole::cConsole%.hasinit preserve=no
      : _Direction(0)
  //## end cConsole::cConsole%.hasinit
  //## begin cConsole::cConsole%.initialization preserve=yes
  //## end cConsole::cConsole%.initialization
{
  //## begin cConsole::cConsole%.body preserve=yes
_ASSERT_UNCOND
  //## end cConsole::cConsole%.body
}

cConsole::cConsole(const cConsole &right)
  //## begin cConsole::cConsole%copy.hasinit preserve=no
      : _Direction(0)
  //## end cConsole::cConsole%copy.hasinit
  //## begin cConsole::cConsole%copy.initialization preserve=yes
  //## end cConsole::cConsole%copy.initialization
{
  //## begin cConsole::cConsole%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConsole::cConsole%copy.body
}

cConsole::cConsole (INT_T direction)
  //## begin cConsole::cConsole%1037267669.hasinit preserve=no
      : _Direction(0)
  //## end cConsole::cConsole%1037267669.hasinit
  //## begin cConsole::cConsole%1037267669.initialization preserve=yes
  //## end cConsole::cConsole%1037267669.initialization
{
  //## begin cConsole::cConsole%1037267669.body preserve=yes
   if (direction == DIRECTION_INPUT || direction == DIRECTION_OUTPUT) {
      _Direction = direction;
   } else {
      _Direction = DIRECTION_OUTPUT;
   }
  //## end cConsole::cConsole%1037267669.body
}


cConsole::~cConsole()
{
  //## begin cConsole::~cConsole%.body preserve=yes
  //## end cConsole::~cConsole%.body
}



//## Other Operations (implementation)
void cConsole::Write (CONST_STRING_T text)
{
  //## begin cConsole::Write%1027605558.body preserve=yes
  //## end cConsole::Write%1027605558.body
}

LONG_T cConsole::Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cConsole::Read%1037267666.body preserve=yes
   return 0;
  //## end cConsole::Read%1037267666.body
}

void cConsole::FlushInput ()
{
  //## begin cConsole::FlushInput%1037267670.body preserve=yes
  //## end cConsole::FlushInput%1037267670.body
}

void cConsole::FlushOutput ()
{
  //## begin cConsole::FlushOutput%1037267671.body preserve=yes
  //## end cConsole::FlushOutput%1037267671.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cConsole::get_Direction () const
{
  //## begin cConsole::get_Direction%3DD378E900BB.get preserve=no
  return _Direction;
  //## end cConsole::get_Direction%3DD378E900BB.get
}

// Additional Declarations
  //## begin cConsole%3D402C9600B0.declarations preserve=yes
  //## end cConsole%3D402C9600B0.declarations

//## begin module%3D402C9600B0.epilog preserve=yes
//## end module%3D402C9600B0.epilog
