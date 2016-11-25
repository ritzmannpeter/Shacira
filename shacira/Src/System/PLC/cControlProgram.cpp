//## begin module%3F38BBF8033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BBF8033C.cm

//## begin module%3F38BBF8033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BBF8033C.cp

//## Module: cControlProgram%3F38BBF8033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlProgram.cpp

//## begin module%3F38BBF8033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F38BBF8033C.additionalIncludes

//## begin module%3F38BBF8033C.includes preserve=yes
//## end module%3F38BBF8033C.includes

// cContext
#include "System/Database/cContext.h"
// cControlProgram
#include "System/PLC/cControlProgram.h"
//## begin module%3F38BBF8033C.additionalDeclarations preserve=yes
//## end module%3F38BBF8033C.additionalDeclarations


// Class cControlProgram 




cControlProgram::cControlProgram()
  //## begin cControlProgram::cControlProgram%.hasinit preserve=no
  //## end cControlProgram::cControlProgram%.hasinit
  //## begin cControlProgram::cControlProgram%.initialization preserve=yes
  //## end cControlProgram::cControlProgram%.initialization
{
  //## begin cControlProgram::cControlProgram%.body preserve=yes
_ASSERT_UNCOND
  //## end cControlProgram::cControlProgram%.body
}

cControlProgram::cControlProgram(const cControlProgram &right)
  //## begin cControlProgram::cControlProgram%copy.hasinit preserve=no
  //## end cControlProgram::cControlProgram%copy.hasinit
  //## begin cControlProgram::cControlProgram%copy.initialization preserve=yes
  //## end cControlProgram::cControlProgram%copy.initialization
{
  //## begin cControlProgram::cControlProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cControlProgram::cControlProgram%copy.body
}

cControlProgram::cControlProgram (CONST_STRING_T name)
  //## begin cControlProgram::cControlProgram%1060960063.hasinit preserve=no
  //## end cControlProgram::cControlProgram%1060960063.hasinit
  //## begin cControlProgram::cControlProgram%1060960063.initialization preserve=yes
  //## end cControlProgram::cControlProgram%1060960063.initialization
{
  //## begin cControlProgram::cControlProgram%1060960063.body preserve=yes
   _Name = name;
  //## end cControlProgram::cControlProgram%1060960063.body
}


cControlProgram::~cControlProgram()
{
  //## begin cControlProgram::~cControlProgram%.body preserve=yes
  //## end cControlProgram::~cControlProgram%.body
}



//## Other Operations (implementation)
STRING_T cControlProgram::Name ()
{
  //## begin cControlProgram::Name%1060960061.body preserve=yes
   return _Name;
  //## end cControlProgram::Name%1060960061.body
}

// Additional Declarations
  //## begin cControlProgram%3F38BBF8033C.declarations preserve=yes
  //## end cControlProgram%3F38BBF8033C.declarations

//## begin module%3F38BBF8033C.epilog preserve=yes
//## end module%3F38BBF8033C.epilog
