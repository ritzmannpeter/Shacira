//## begin module%40054A77001F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40054A77001F.cm

//## begin module%40054A77001F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40054A77001F.cp

//## Module: cUserInterface%40054A77001F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cUserInterface.cpp

//## begin module%40054A77001F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40054A77001F.additionalIncludes

//## begin module%40054A77001F.includes preserve=yes
//## end module%40054A77001F.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cConsole
#include "System/Console/cConsole.h"
// cContext
#include "System/Database/cContext.h"
// cCCSInterface
#include "GUIFramework/Interface/cCCSInterface.h"
// cUserInterface
#include "GUIFramework/cUserInterface.h"
// cNodeList
#include "GUIFramework/cNodeList.h"
// cNode
#include "GUIFramework/cNode.h"
//## begin module%40054A77001F.additionalDeclarations preserve=yes
//## end module%40054A77001F.additionalDeclarations


// Class cUserInterface 









cUserInterface::cUserInterface()
  //## begin cUserInterface::cUserInterface%.hasinit preserve=no
      : _Process(NULL), _Remote(false), _ActContext(NULL), _GUIInitFuncAddress(NULL), _NodeList(NULL), _ContextChooser(NULL), _CCSInterface(NULL), _Console(NULL)
  //## end cUserInterface::cUserInterface%.hasinit
  //## begin cUserInterface::cUserInterface%.initialization preserve=yes
  //## end cUserInterface::cUserInterface%.initialization
{
  //## begin cUserInterface::cUserInterface%.body preserve=yes
_ASSERT_UNCOND
  //## end cUserInterface::cUserInterface%.body
}

cUserInterface::cUserInterface(const cUserInterface &right)
  //## begin cUserInterface::cUserInterface%copy.hasinit preserve=no
      : _Process(NULL), _Remote(false), _ActContext(NULL), _GUIInitFuncAddress(NULL), _NodeList(NULL), _ContextChooser(NULL), _CCSInterface(NULL), _Console(NULL)
  //## end cUserInterface::cUserInterface%copy.hasinit
  //## begin cUserInterface::cUserInterface%copy.initialization preserve=yes
  //## end cUserInterface::cUserInterface%copy.initialization
{
  //## begin cUserInterface::cUserInterface%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cUserInterface::cUserInterface%copy.body
}

cUserInterface::cUserInterface (BOOL_T remote, CONST_STRING_T language, cConsole *console)
  //## begin cUserInterface::cUserInterface%1074088882.hasinit preserve=no
      : _Process(NULL), _Remote(false), _ActContext(NULL), _GUIInitFuncAddress(NULL), _NodeList(NULL), _ContextChooser(NULL), _CCSInterface(NULL), _Console(NULL)
  //## end cUserInterface::cUserInterface%1074088882.hasinit
  //## begin cUserInterface::cUserInterface%1074088882.initialization preserve=yes
  //## end cUserInterface::cUserInterface%1074088882.initialization
{
  //## begin cUserInterface::cUserInterface%1074088882.body preserve=yes
   _Remote = remote;
   _Console = console;
  //## end cUserInterface::cUserInterface%1074088882.body
}


cUserInterface::~cUserInterface()
{
  //## begin cUserInterface::~cUserInterface%.body preserve=yes
  //## end cUserInterface::~cUserInterface%.body
}



//## Other Operations (implementation)
BOOL_T cUserInterface::IsRemote ()
{
  //## begin cUserInterface::IsRemote%1097490347.body preserve=yes
   return _Remote;
  //## end cUserInterface::IsRemote%1097490347.body
}

BOOL_T cUserInterface::GUIInitialize (ULONG_T step, cContext *context)
{
  //## begin cUserInterface::GUIInitialize%1106052709.body preserve=yes
InfoPrintf("gui init call step %d ...\n", step);
   if (_GUIInitFuncAddress == NULL) {
      _GUIInitFuncAddress = cCustomFunctions::GUIInitFuncAddress();
   }
   if (_GUIInitFuncAddress == NULL) {
InfoPrintf("no gui init function\n");
      return true;
   } else {
      BOOL_T success = _GUIInitFuncAddress(step, context);
      if (success) {
InfoPrintf("gui init call step %d done\n", step);
      } else {
InfoPrintf("gui init call step %d failed\n", step);
      }
      return success;
   }
  //## end cUserInterface::GUIInitialize%1106052709.body
}

// Additional Declarations
  //## begin cUserInterface%40054A77001F.declarations preserve=yes
  //## end cUserInterface%40054A77001F.declarations

//## begin module%40054A77001F.epilog preserve=yes
//## end module%40054A77001F.epilog
