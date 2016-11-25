// ===========================================================================
// base/driver/mn.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// 
// ===========================================================================


// Interface header
#include "base/driver/mn.h"




namespace ecl {




// Implementierung cMsgNode
// ===========================================================================

cMsgNode::cMsgNode(int send_mode)
{
   _wait = true;
   _send_mode = send_mode;
}

cMsgNode::cMsgNode(const cString &name, int send_mode)
{
   _name = getName(name);
   _address = getAddress(name);
   _wait = true;
   _send_mode = send_mode;
}

cMsgNode::~cMsgNode()
{
}

cString cMsgNode::getProtocol(const cString &name)
{
   int pos = name.getPos(":", 1);
   if ( name.getLeft(1) != ":" ) return "local";
   if ( pos < 1 ) return name.getMid(1);
   return name.getSubstr(1, pos - 1);
}

cString cMsgNode::getAddress(const cString &name)
{
   int pos1 = 0, pos2 = 0;
   if ( name.getLeft(1) == ":" ) {
      pos1 = name.getPos(":", 1) + 1;
      pos2 = name.getPos(":", pos1+1) - 1;
   } else {
      pos2 = name.getPos(":", 1) - 1;
   }
   if ( pos2 > pos1+1 ) return name.getSubstr(pos1, pos2);
   return ".";
}

cString cMsgNode::getName(const cString &name)
{
   int pos = 0, pos1 = 1;
   while ( (pos1 = name.getPos(":", pos)) >= 0 )
      pos = pos1 + 1;
   return name.getMid(pos);
}




}; // namespace __ecl__

