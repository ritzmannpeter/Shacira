//## begin module%400525C90290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%400525C90290.cm

//## begin module%400525C90290.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%400525C90290.cp

//## Module: cNode%400525C90290; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cNode.cpp

//## begin module%400525C90290.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%400525C90290.additionalIncludes

//## begin module%400525C90290.includes preserve=yes
//## end module%400525C90290.includes

// cContext
#include "System/Database/cContext.h"
// cEventAdapter
#include "Client/Adapters/cEventAdapter.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
// cNode
#include "GUIFramework/cNode.h"
//## begin module%400525C90290.additionalDeclarations preserve=yes
//## end module%400525C90290.additionalDeclarations


// Class cNode 







cNode::cNode()
  //## begin cNode::cNode%.hasinit preserve=no
      : _IsRemote(false), _Context(NULL), _DataChangeAdapter(NULL), _EventAdapter(NULL)
  //## end cNode::cNode%.hasinit
  //## begin cNode::cNode%.initialization preserve=yes
  //## end cNode::cNode%.initialization
{
  //## begin cNode::cNode%.body preserve=yes
_ASSERT_UNCOND
  //## end cNode::cNode%.body
}

cNode::cNode(const cNode &right)
  //## begin cNode::cNode%copy.hasinit preserve=no
      : _IsRemote(false), _Context(NULL), _DataChangeAdapter(NULL), _EventAdapter(NULL)
  //## end cNode::cNode%copy.hasinit
  //## begin cNode::cNode%copy.initialization preserve=yes
  //## end cNode::cNode%copy.initialization
{
  //## begin cNode::cNode%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cNode::cNode%copy.body
}

cNode::cNode (cContext *context, cDataChangeAdapter *data_change_adapter, cEventAdapter *event_adapter)
  //## begin cNode::cNode%1074080284.hasinit preserve=no
      : _IsRemote(false), _Context(NULL), _DataChangeAdapter(NULL), _EventAdapter(NULL)
  //## end cNode::cNode%1074080284.hasinit
  //## begin cNode::cNode%1074080284.initialization preserve=yes
  //## end cNode::cNode%1074080284.initialization
{
  //## begin cNode::cNode%1074080284.body preserve=yes
   _Context = context;
   _Name = _Context->get_Name();
   _DataChangeAdapter = data_change_adapter;
   _EventAdapter = event_adapter;
   if (_Context->IsRemote()) {
      _IsRemote = true;
   } else {
      _IsRemote = false;
   }
  //## end cNode::cNode%1074080284.body
}


cNode::~cNode()
{
  //## begin cNode::~cNode%.body preserve=yes
  //## end cNode::~cNode%.body
}



//## Other Operations (implementation)
cContext * cNode::Context ()
{
  //## begin cNode::Context%1074084964.body preserve=yes
   if (_IsRemote) {
      return _Context;
   } else {
      return _Context;
   }
  //## end cNode::Context%1074084964.body
}

cDataChangeAdapter * cNode::DataChangeAdapter ()
{
  //## begin cNode::DataChangeAdapter%1074084965.body preserve=yes
   if (_IsRemote) {
      return _DataChangeAdapter;
   } else {
      return _DataChangeAdapter;
   }
  //## end cNode::DataChangeAdapter%1074084965.body
}

cEventAdapter * cNode::EventAdapter ()
{
  //## begin cNode::EventAdapter%1074084966.body preserve=yes
   if (_IsRemote) {
      return _EventAdapter;
   } else {
      return _EventAdapter;
   }
  //## end cNode::EventAdapter%1074084966.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cNode::get_Name () const
{
  //## begin cNode::get_Name%40052CE10196.get preserve=no
  return _Name;
  //## end cNode::get_Name%40052CE10196.get
}

void cNode::set_Name (STRING_T value)
{
  //## begin cNode::set_Name%40052CE10196.set preserve=no
  _Name = value;
  //## end cNode::set_Name%40052CE10196.set
}

BOOL_T cNode::get_IsRemote () const
{
  //## begin cNode::get_IsRemote%42DCFE9C02AF.get preserve=no
  return _IsRemote;
  //## end cNode::get_IsRemote%42DCFE9C02AF.get
}

// Additional Declarations
  //## begin cNode%400525C90290.declarations preserve=yes
  //## end cNode%400525C90290.declarations

//## begin module%400525C90290.epilog preserve=yes
//## end module%400525C90290.epilog
