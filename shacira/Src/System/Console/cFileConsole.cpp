//## begin module%3DD3D0B601DE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3D0B601DE.cm

//## begin module%3DD3D0B601DE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3D0B601DE.cp

//## Module: cFileConsole%3DD3D0B601DE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cFileConsole.cpp

//## begin module%3DD3D0B601DE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD3D0B601DE.additionalIncludes

//## begin module%3DD3D0B601DE.includes preserve=yes
//## end module%3DD3D0B601DE.includes

// cFileConsole
#include "System/Console/cFileConsole.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3DD3D0B601DE.additionalDeclarations preserve=yes
//## end module%3DD3D0B601DE.additionalDeclarations


// Class cFileConsole 


cFileConsole::cFileConsole()
  //## begin cFileConsole::cFileConsole%.hasinit preserve=no
  //## end cFileConsole::cFileConsole%.hasinit
  //## begin cFileConsole::cFileConsole%.initialization preserve=yes
  //## end cFileConsole::cFileConsole%.initialization
{
  //## begin cFileConsole::cFileConsole%.body preserve=yes
_ASSERT_UNCOND
  //## end cFileConsole::cFileConsole%.body
}

cFileConsole::cFileConsole(const cFileConsole &right)
  //## begin cFileConsole::cFileConsole%copy.hasinit preserve=no
  //## end cFileConsole::cFileConsole%copy.hasinit
  //## begin cFileConsole::cFileConsole%copy.initialization preserve=yes
  //## end cFileConsole::cFileConsole%copy.initialization
{
  //## begin cFileConsole::cFileConsole%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFileConsole::cFileConsole%copy.body
}

cFileConsole::cFileConsole (CONST_STRING_T file_name)
  //## begin cFileConsole::cFileConsole%1037286975.hasinit preserve=no
  //## end cFileConsole::cFileConsole%1037286975.hasinit
  //## begin cFileConsole::cFileConsole%1037286975.initialization preserve=yes
  : cConsole(DIRECTION_OUTPUT)
  //## end cFileConsole::cFileConsole%1037286975.initialization
{
  //## begin cFileConsole::cFileConsole%1037286975.body preserve=yes
   _File = cFileSystemUtils::FullPath(file_name);
   STRING_T dir = cFileSystemUtils::DirName(_File.c_str());
   cFileSystemUtils::CreateDir(dir.c_str());
  //## end cFileConsole::cFileConsole%1037286975.body
}


cFileConsole::~cFileConsole()
{
  //## begin cFileConsole::~cFileConsole%.body preserve=yes
  //## end cFileConsole::~cFileConsole%.body
}



//## Other Operations (implementation)
void cFileConsole::Write (CONST_STRING_T text)
{
  //## begin cFileConsole::Write%1037286976.body preserve=yes
   FILE * stream = fopen(_File.c_str(), "a");
   if (stream != NULL) {
      fwrite(text, strlen(text), 1, stream);
      fclose(stream);
   }
  //## end cFileConsole::Write%1037286976.body
}

LONG_T cFileConsole::Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cFileConsole::Read%1037286977.body preserve=yes
   CHECK_DIRECTION(DIRECTION_INPUT)
   FILE * stream = fopen(_File.c_str(), "r");
   if (stream != NULL) {
      long nread = fread((void*)buf, buf_size, 1, stream);
      return nread;
   } else {
      return 0;
   }
  //## end cFileConsole::Read%1037286977.body
}

void cFileConsole::FlushInput ()
{
  //## begin cFileConsole::FlushInput%1037286978.body preserve=yes
  //## end cFileConsole::FlushInput%1037286978.body
}

void cFileConsole::FlushOutput ()
{
  //## begin cFileConsole::FlushOutput%1037286979.body preserve=yes
  //## end cFileConsole::FlushOutput%1037286979.body
}

// Additional Declarations
  //## begin cFileConsole%3DD3D0B601DE.declarations preserve=yes
  //## end cFileConsole%3DD3D0B601DE.declarations

//## begin module%3DD3D0B601DE.epilog preserve=yes
//## end module%3DD3D0B601DE.epilog
