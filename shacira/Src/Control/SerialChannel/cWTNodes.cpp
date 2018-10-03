//## begin module%3CBBD3F60158.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CBBD3F60158.cm

//## begin module%3CBBD3F60158.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CBBD3F60158.cp

//## Module: cWTNodes%3CBBD3F60158; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cWTNodes.cpp

//## begin module%3CBBD3F60158.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3CBBD3F60158.additionalIncludes

//## begin module%3CBBD3F60158.includes preserve=yes
//## end module%3CBBD3F60158.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cWTNodes
#include "Control/SerialChannel/cWTNodes.h"
// cWTNode
#include "Control/SerialChannel/cWTNode.h"
//## begin module%3CBBD3F60158.additionalDeclarations preserve=yes
//## end module%3CBBD3F60158.additionalDeclarations


// Class cWTNodes 



cWTNodes::cWTNodes()
  //## begin cWTNodes::cWTNodes%.hasinit preserve=no
  //## end cWTNodes::cWTNodes%.hasinit
  //## begin cWTNodes::cWTNodes%.initialization preserve=yes
  //## end cWTNodes::cWTNodes%.initialization
{
  //## begin cWTNodes::cWTNodes%.body preserve=yes
   _Name = "W&T Node Control";
	_IdleTime = 2000;
  //## end cWTNodes::cWTNodes%.body
}

cWTNodes::cWTNodes(const cWTNodes &right)
  //## begin cWTNodes::cWTNodes%copy.hasinit preserve=no
  //## end cWTNodes::cWTNodes%copy.hasinit
  //## begin cWTNodes::cWTNodes%copy.initialization preserve=yes
  //## end cWTNodes::cWTNodes%copy.initialization
{
  //## begin cWTNodes::cWTNodes%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cWTNodes::cWTNodes%copy.body
}


cWTNodes::~cWTNodes()
{
  //## begin cWTNodes::~cWTNodes%.body preserve=yes
   NODE_MAP_T::const_iterator i = _NodeMap.cbegin();
   while (i != _NodeMap.cend()) {
      cWTNode * node = (*i).second;
      delete node;
      i++;
   }
  //## end cWTNodes::~cWTNodes%.body
}



//## Other Operations (implementation)
cWTNode * cWTNodes::Node (CONST_STRING_T ip_address)
{
  //## begin cWTNodes::Node%1018942490.body preserve=yes
   NODE_MAP_T::const_iterator i = _NodeMap.find(ip_address);
   if (i == _NodeMap.cend()) {
      cObjectLock _lock_(&_NodeListMutex);
      int size = _NodeMap.size();
      cWTNode * node = new cWTNode(ip_address);
      _NodeMap[ip_address] = node;
      if (size == 0) Start();
      return node;
   } else {
      return (*i).second;
   }
  //## end cWTNodes::Node%1018942490.body
}

INT_T cWTNodes::ControlFunc ()
{
  //## begin cWTNodes::ControlFunc%1018942495.body preserve=yes
   CONTROLFUNC_PROLOG(_Name.c_str())
   cObjectLock _lock_(&_NodeListMutex);
   NODE_MAP_T::const_iterator i = _NodeMap.cbegin();
   while (i != _NodeMap.cend()) {
      cWTNode * node = (*i).second;
      if (Terminated()) return 0;
      node->Refresh();
      if (Terminated()) return 0;
      // 27.05.2002 -PR- mindestens 1 Sekune Wartezeit zwischen jedem Ping
	  // um die Netzwerkbelastung zu verringern.
      sleep(1000);
      i++;
   }
   CONTROLFUNC_EPILOG
   return 0;
  //## end cWTNodes::ControlFunc%1018942495.body
}

// Additional Declarations
  //## begin cWTNodes%3CBBD3F60158.declarations preserve=yes
  //## end cWTNodes%3CBBD3F60158.declarations

//## begin module%3CBBD3F60158.epilog preserve=yes
//## end module%3CBBD3F60158.epilog
