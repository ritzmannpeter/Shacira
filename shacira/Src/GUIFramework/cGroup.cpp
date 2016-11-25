//## begin module%4005261001B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4005261001B5.cm

//## begin module%4005261001B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4005261001B5.cp

//## Module: cGroup%4005261001B5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cGroup.cpp

//## begin module%4005261001B5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4005261001B5.additionalIncludes

//## begin module%4005261001B5.includes preserve=yes
//## end module%4005261001B5.includes

// cContext
#include "System/Database/cContext.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
// cEventAdapter
#include "Client/Adapters/cEventAdapter.h"
// cGroup
#include "GUIFramework/cGroup.h"
//## begin module%4005261001B5.additionalDeclarations preserve=yes
//## end module%4005261001B5.additionalDeclarations


// Class cGroup 




cGroup::cGroup()
  //## begin cGroup::cGroup%.hasinit preserve=no
      : _DataChangeAdapter(NULL), _Context(NULL), _EventAdapter(NULL)
  //## end cGroup::cGroup%.hasinit
  //## begin cGroup::cGroup%.initialization preserve=yes
  //## end cGroup::cGroup%.initialization
{
  //## begin cGroup::cGroup%.body preserve=yes
_ASSERT_UNCOND
  //## end cGroup::cGroup%.body
}

cGroup::cGroup(const cGroup &right)
  //## begin cGroup::cGroup%copy.hasinit preserve=no
      : _DataChangeAdapter(NULL), _Context(NULL), _EventAdapter(NULL)
  //## end cGroup::cGroup%copy.hasinit
  //## begin cGroup::cGroup%copy.initialization preserve=yes
  //## end cGroup::cGroup%copy.initialization
{
  //## begin cGroup::cGroup%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGroup::cGroup%copy.body
}

cGroup::cGroup (cContext *context, cDataChangeAdapter *data_change_adapter, cEventAdapter *event_adapter)
  //## begin cGroup::cGroup%1074080281.hasinit preserve=no
      : _DataChangeAdapter(NULL), _Context(NULL), _EventAdapter(NULL)
  //## end cGroup::cGroup%1074080281.hasinit
  //## begin cGroup::cGroup%1074080281.initialization preserve=yes
  //## end cGroup::cGroup%1074080281.initialization
{
  //## begin cGroup::cGroup%1074080281.body preserve=yes
   _Context = context;
   _DataChangeAdapter = data_change_adapter;
   _EventAdapter = event_adapter;
  //## end cGroup::cGroup%1074080281.body
}


cGroup::~cGroup()
{
  //## begin cGroup::~cGroup%.body preserve=yes
  //## end cGroup::~cGroup%.body
}


// Additional Declarations
  //## begin cGroup%4005261001B5.declarations preserve=yes
  //## end cGroup%4005261001B5.declarations

//## begin module%4005261001B5.epilog preserve=yes
//## end module%4005261001B5.epilog
