//## begin module%400525E50157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%400525E50157.cm

//## begin module%400525E50157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%400525E50157.cp

//## Module: cNodeList%400525E50157; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cNodeList.cpp

//## begin module%400525E50157.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%400525E50157.additionalIncludes

//## begin module%400525E50157.includes preserve=yes
//## end module%400525E50157.includes

// cNodeList
#include "GUIFramework/cNodeList.h"
// cNode
#include "GUIFramework/cNode.h"
//## begin module%400525E50157.additionalDeclarations preserve=yes
//## end module%400525E50157.additionalDeclarations


// Class cNodeList 




cNodeList::cNodeList()
  //## begin cNodeList::cNodeList%.hasinit preserve=no
  //## end cNodeList::cNodeList%.hasinit
  //## begin cNodeList::cNodeList%.initialization preserve=yes
  //## end cNodeList::cNodeList%.initialization
{
  //## begin cNodeList::cNodeList%.body preserve=yes
  //## end cNodeList::cNodeList%.body
}

cNodeList::cNodeList(const cNodeList &right)
  //## begin cNodeList::cNodeList%copy.hasinit preserve=no
  //## end cNodeList::cNodeList%copy.hasinit
  //## begin cNodeList::cNodeList%copy.initialization preserve=yes
  //## end cNodeList::cNodeList%copy.initialization
{
  //## begin cNodeList::cNodeList%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cNodeList::cNodeList%copy.body
}


cNodeList::~cNodeList()
{
  //## begin cNodeList::~cNodeList%.body preserve=yes
  //## end cNodeList::~cNodeList%.body
}



//## Other Operations (implementation)
void cNodeList::AddNode (cNode *node)
{
  //## begin cNodeList::AddNode%1074080283.body preserve=yes
   STRING_T name = node->get_Name();
   _Nodes[name.c_str()] = node;
  //## end cNodeList::AddNode%1074080283.body
}

ULONG_T cNodeList::NodeNames (STRING_LIST_T &node_names)
{
  //## begin cNodeList::NodeNames%1074084959.body preserve=yes
   node_names.clear();
   std::map<STRING_T,cNode*>::const_iterator i = _Nodes.cbegin();
   while (i != _Nodes.cend()) {
      node_names.push_back((*i).first.c_str());
      i++;
   }
   return node_names.size();
  //## end cNodeList::NodeNames%1074084959.body
}

cNode * cNodeList::Node (CONST_STRING_T name)
{
  //## begin cNodeList::Node%1074084960.body preserve=yes
   std::map<STRING_T,cNode*>::const_iterator i = _Nodes.find(name);
   if (i == _Nodes.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cNodeList::Node%1074084960.body
}

// Additional Declarations
  //## begin cNodeList%400525E50157.declarations preserve=yes
  //## end cNodeList%400525E50157.declarations

//## begin module%400525E50157.epilog preserve=yes
//## end module%400525E50157.epilog
