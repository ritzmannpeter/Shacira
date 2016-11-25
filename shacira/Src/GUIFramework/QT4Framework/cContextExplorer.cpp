//## begin module%416814BE0186.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%416814BE0186.cm

//## begin module%416814BE0186.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%416814BE0186.cp

//## Module: cContextExplorer%416814BE0186; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\QTFramework\cContextExplorer.cpp

//## begin module%416814BE0186.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%416814BE0186.additionalIncludes

//## begin module%416814BE0186.includes preserve=yes
//## end module%416814BE0186.includes

// cContextExplorer
#include "cContextExplorer.h"
//## begin module%416814BE0186.additionalDeclarations preserve=yes
//## end module%416814BE0186.additionalDeclarations


// Class cContextExplorer 


cContextExplorer::cContextExplorer()
  //## begin cContextExplorer::cContextExplorer%.hasinit preserve=no
      : _Parent(NULL)
  //## end cContextExplorer::cContextExplorer%.hasinit
  //## begin cContextExplorer::cContextExplorer%.initialization preserve=yes
  //## end cContextExplorer::cContextExplorer%.initialization
{
  //## begin cContextExplorer::cContextExplorer%.body preserve=yes
_ASSERT_UNCOND
  //## end cContextExplorer::cContextExplorer%.body
}

cContextExplorer::cContextExplorer(const cContextExplorer &right)
  //## begin cContextExplorer::cContextExplorer%copy.hasinit preserve=no
      : _Parent(NULL)
  //## end cContextExplorer::cContextExplorer%copy.hasinit
  //## begin cContextExplorer::cContextExplorer%copy.initialization preserve=yes
  //## end cContextExplorer::cContextExplorer%copy.initialization
{
  //## begin cContextExplorer::cContextExplorer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cContextExplorer::cContextExplorer%copy.body
}

cContextExplorer::cContextExplorer (QWidget *parent)
  //## begin cContextExplorer::cContextExplorer%1097340230.hasinit preserve=no
      : _Parent(NULL)
  //## end cContextExplorer::cContextExplorer%1097340230.hasinit
  //## begin cContextExplorer::cContextExplorer%1097340230.initialization preserve=yes
  //## end cContextExplorer::cContextExplorer%1097340230.initialization
{
  //## begin cContextExplorer::cContextExplorer%1097340230.body preserve=yes
   _Parent = parent;
  //## end cContextExplorer::cContextExplorer%1097340230.body
}


cContextExplorer::~cContextExplorer()
{
  //## begin cContextExplorer::~cContextExplorer%.body preserve=yes
  //## end cContextExplorer::~cContextExplorer%.body
}



//## Other Operations (implementation)
cContext * cContextExplorer::GetContext ()
{
  //## begin cContextExplorer::GetContext%1097340229.body preserve=yes
   if (_Process != NULL) {
      ContextExplorerDialog dialog(_Parent, "fuzzy", _Parent);
      dialog.SetProcess(_Process);
      if (dialog.Execute()) {
         cContext * context = dialog.GetContext();
         return context;
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cContextExplorer::GetContext%1097340229.body
}

// Additional Declarations
  //## begin cContextExplorer%416814BE0186.declarations preserve=yes
  //## end cContextExplorer%416814BE0186.declarations

//## begin module%416814BE0186.epilog preserve=yes
//## end module%416814BE0186.epilog
