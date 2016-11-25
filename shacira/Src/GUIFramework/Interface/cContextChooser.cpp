//## begin module%4167FEE2030D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4167FEE2030D.cm

//## begin module%4167FEE2030D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4167FEE2030D.cp

//## Module: cContextChooser%4167FEE2030D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\Interface\cContextChooser.cpp

//## begin module%4167FEE2030D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4167FEE2030D.additionalIncludes

//## begin module%4167FEE2030D.includes preserve=yes
//## end module%4167FEE2030D.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cContext
#include "System/Database/cContext.h"
// cContextChooser
#include "GUIFramework/Interface/cContextChooser.h"
//## begin module%4167FEE2030D.additionalDeclarations preserve=yes
//## end module%4167FEE2030D.additionalDeclarations


// Class cContextChooser 



cContextChooser::cContextChooser()
  //## begin cContextChooser::cContextChooser%.hasinit preserve=no
      : _Process(NULL)
  //## end cContextChooser::cContextChooser%.hasinit
  //## begin cContextChooser::cContextChooser%.initialization preserve=yes
  //## end cContextChooser::cContextChooser%.initialization
{
  //## begin cContextChooser::cContextChooser%.body preserve=yes
  //## end cContextChooser::cContextChooser%.body
}

cContextChooser::cContextChooser(const cContextChooser &right)
  //## begin cContextChooser::cContextChooser%copy.hasinit preserve=no
      : _Process(NULL)
  //## end cContextChooser::cContextChooser%copy.hasinit
  //## begin cContextChooser::cContextChooser%copy.initialization preserve=yes
  //## end cContextChooser::cContextChooser%copy.initialization
{
  //## begin cContextChooser::cContextChooser%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cContextChooser::cContextChooser%copy.body
}


cContextChooser::~cContextChooser()
{
  //## begin cContextChooser::~cContextChooser%.body preserve=yes
  //## end cContextChooser::~cContextChooser%.body
}



//## Other Operations (implementation)
void cContextChooser::SetProcess (cSHProcess *process)
{
  //## begin cContextChooser::SetProcess%1097333010.body preserve=yes
   _Process = process;
  //## end cContextChooser::SetProcess%1097333010.body
}

cContext * cContextChooser::GetContext ()
{
  //## begin cContextChooser::GetContext%1097333008.body preserve=yes
   return NULL;
  //## end cContextChooser::GetContext%1097333008.body
}

// Additional Declarations
  //## begin cContextChooser%4167FEE2030D.declarations preserve=yes
  //## end cContextChooser%4167FEE2030D.declarations

//## begin module%4167FEE2030D.epilog preserve=yes
//## end module%4167FEE2030D.epilog
