//## begin module%3D413C3F0290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D413C3F0290.cm

//## begin module%3D413C3F0290.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D413C3F0290.cp

//## Module: cStandardConsole%3D413C3F0290; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cStandardConsole.cpp

//## begin module%3D413C3F0290.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D413C3F0290.additionalIncludes

//## begin module%3D413C3F0290.includes preserve=yes
//## end module%3D413C3F0290.includes

// cStandardConsole
#include "System/Console/cStandardConsole.h"
//## begin module%3D413C3F0290.additionalDeclarations preserve=yes
//## end module%3D413C3F0290.additionalDeclarations


// Class cStandardConsole 


cStandardConsole::cStandardConsole()
  //## begin cStandardConsole::cStandardConsole%.hasinit preserve=no
      : _Stream(NULL)
  //## end cStandardConsole::cStandardConsole%.hasinit
  //## begin cStandardConsole::cStandardConsole%.initialization preserve=yes
  //## end cStandardConsole::cStandardConsole%.initialization
{
  //## begin cStandardConsole::cStandardConsole%.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardConsole::cStandardConsole%.body
}

cStandardConsole::cStandardConsole(const cStandardConsole &right)
  //## begin cStandardConsole::cStandardConsole%copy.hasinit preserve=no
      : _Stream(NULL)
  //## end cStandardConsole::cStandardConsole%copy.hasinit
  //## begin cStandardConsole::cStandardConsole%copy.initialization preserve=yes
  //## end cStandardConsole::cStandardConsole%copy.initialization
{
  //## begin cStandardConsole::cStandardConsole%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardConsole::cStandardConsole%copy.body
}

cStandardConsole::cStandardConsole (FILE *stream, INT_T direction)
  //## begin cStandardConsole::cStandardConsole%1027676084.hasinit preserve=no
      : _Stream(NULL)
  //## end cStandardConsole::cStandardConsole%1027676084.hasinit
  //## begin cStandardConsole::cStandardConsole%1027676084.initialization preserve=yes
  , cConsole(direction)
  //## end cStandardConsole::cStandardConsole%1027676084.initialization
{
  //## begin cStandardConsole::cStandardConsole%1027676084.body preserve=yes
   _Stream = stream;
  //## end cStandardConsole::cStandardConsole%1027676084.body
}


cStandardConsole::~cStandardConsole()
{
  //## begin cStandardConsole::~cStandardConsole%.body preserve=yes
   if (_Stream != NULL) {
      fclose(_Stream);
   }
  //## end cStandardConsole::~cStandardConsole%.body
}



//## Other Operations (implementation)
void cStandardConsole::Write (CONST_STRING_T text)
{
  //## begin cStandardConsole::Write%1037267664.body preserve=yes
   CHECK_DIRECTION(DIRECTION_OUTPUT)
   if (_Stream == NULL) return;
   fwrite(text, strlen(text), 1, _Stream);
  //## end cStandardConsole::Write%1037267664.body
}

LONG_T cStandardConsole::Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cStandardConsole::Read%1037267665.body preserve=yes
   CHECK_DIRECTION(DIRECTION_INPUT)
   if (_Stream == NULL) return 0;
   long nread = fread((void*)buf, buf_size, 1, _Stream);
   return nread;
  //## end cStandardConsole::Read%1037267665.body
}

void cStandardConsole::FlushInput ()
{
  //## begin cStandardConsole::FlushInput%1037267667.body preserve=yes
   CHECK_DIRECTION(DIRECTION_OUTPUT)
   if (_Stream == NULL) return;
   fflush(_Stream);
  //## end cStandardConsole::FlushInput%1037267667.body
}

void cStandardConsole::FlushOutput ()
{
  //## begin cStandardConsole::FlushOutput%1037267668.body preserve=yes
   CHECK_DIRECTION(DIRECTION_INPUT)
   if (_Stream == NULL) return;
   fflush(_Stream);
  //## end cStandardConsole::FlushOutput%1037267668.body
}

// Additional Declarations
  //## begin cStandardConsole%3D413C3F0290.declarations preserve=yes
  //## end cStandardConsole%3D413C3F0290.declarations

//## begin module%3D413C3F0290.epilog preserve=yes
//## end module%3D413C3F0290.epilog
