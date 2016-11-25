//## begin module%412062FB0280.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412062FB0280.cm

//## begin module%412062FB0280.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412062FB0280.cp

//## Module: cDatasetDirectory%412062FB0280; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cDatasetDirectory.cpp

//## begin module%412062FB0280.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%412062FB0280.additionalIncludes

//## begin module%412062FB0280.includes preserve=yes
//## end module%412062FB0280.includes

// cDatasetDirectory
#include "System/Structs/cDatasetDirectory.h"
// cDataset
#include "System/Structs/cDataset.h"
//## begin module%412062FB0280.additionalDeclarations preserve=yes
//## end module%412062FB0280.additionalDeclarations


// Class cDatasetDirectory 




cDatasetDirectory::cDatasetDirectory()
  //## begin cDatasetDirectory::cDatasetDirectory%.hasinit preserve=no
  //## end cDatasetDirectory::cDatasetDirectory%.hasinit
  //## begin cDatasetDirectory::cDatasetDirectory%.initialization preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%.initialization
{
  //## begin cDatasetDirectory::cDatasetDirectory%.body preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%.body
}

cDatasetDirectory::cDatasetDirectory(const cDatasetDirectory &right)
  //## begin cDatasetDirectory::cDatasetDirectory%copy.hasinit preserve=no
  //## end cDatasetDirectory::cDatasetDirectory%copy.hasinit
  //## begin cDatasetDirectory::cDatasetDirectory%copy.initialization preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%copy.initialization
{
  //## begin cDatasetDirectory::cDatasetDirectory%copy.body preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%copy.body
}

cDatasetDirectory::cDatasetDirectory (CONST_STRING_T path, CONST_STRING_T pattern)
  //## begin cDatasetDirectory::cDatasetDirectory%1092642065.hasinit preserve=no
  //## end cDatasetDirectory::cDatasetDirectory%1092642065.hasinit
  //## begin cDatasetDirectory::cDatasetDirectory%1092642065.initialization preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%1092642065.initialization
{
  //## begin cDatasetDirectory::cDatasetDirectory%1092642065.body preserve=yes
  //## end cDatasetDirectory::cDatasetDirectory%1092642065.body
}


cDatasetDirectory::~cDatasetDirectory()
{
  //## begin cDatasetDirectory::~cDatasetDirectory%.body preserve=yes
  //## end cDatasetDirectory::~cDatasetDirectory%.body
}



//## Other Operations (implementation)
CONST_STRING_T cDatasetDirectory::NewFileName ()
{
  //## begin cDatasetDirectory::NewFileName%1092642066.body preserve=yes
   return "?";
  //## end cDatasetDirectory::NewFileName%1092642066.body
}

// Additional Declarations
  //## begin cDatasetDirectory%412062FB0280.declarations preserve=yes
  //## end cDatasetDirectory%412062FB0280.declarations

//## begin module%412062FB0280.epilog preserve=yes
//## end module%412062FB0280.epilog
