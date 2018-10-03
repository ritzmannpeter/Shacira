//## begin module%3BB1D5320154.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D5320154.cm

//## begin module%3BB1D5320154.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D5320154.cp

//## Module: cNameSpaceNode%3BB1D5320154; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpaceNode.cpp

//## begin module%3BB1D5320154.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BB1D5320154.additionalIncludes

//## begin module%3BB1D5320154.includes preserve=yes
//## end module%3BB1D5320154.includes

// cNameSpaceNode
#include "System/Namespace/cNameSpaceNode.h"
// cNameSpace
#include "System/Namespace/cNameSpace.h"
//## begin module%3BB1D5320154.additionalDeclarations preserve=yes
//## end module%3BB1D5320154.additionalDeclarations


// Class cNameSpaceNode 










cNameSpaceNode::cNameSpaceNode()
  //## begin cNameSpaceNode::cNameSpaceNode%.hasinit preserve=no
      : _Type(Leaf), _Parent(NULL), _NameSpace(NULL)
  //## end cNameSpaceNode::cNameSpaceNode%.hasinit
  //## begin cNameSpaceNode::cNameSpaceNode%.initialization preserve=yes
  //## end cNameSpaceNode::cNameSpaceNode%.initialization
{
  //## begin cNameSpaceNode::cNameSpaceNode%.body preserve=yes
  //## end cNameSpaceNode::cNameSpaceNode%.body
}

cNameSpaceNode::cNameSpaceNode(const cNameSpaceNode &right)
  //## begin cNameSpaceNode::cNameSpaceNode%copy.hasinit preserve=no
      : _Type(Leaf), _Parent(NULL), _NameSpace(NULL)
  //## end cNameSpaceNode::cNameSpaceNode%copy.hasinit
  //## begin cNameSpaceNode::cNameSpaceNode%copy.initialization preserve=yes
  //## end cNameSpaceNode::cNameSpaceNode%copy.initialization
{
  //## begin cNameSpaceNode::cNameSpaceNode%copy.body preserve=yes
   _Name = right._Name;
   _Parent = right._Parent;
   _Type = right._Type;
  //## end cNameSpaceNode::cNameSpaceNode%copy.body
}

cNameSpaceNode::cNameSpaceNode (CONST_STRING_T name, cNameSpaceNode *parent, cNameSpace *name_space)
  //## begin cNameSpaceNode::cNameSpaceNode%1001511095.hasinit preserve=no
      : _Type(Leaf), _Parent(NULL), _NameSpace(NULL)
  //## end cNameSpaceNode::cNameSpaceNode%1001511095.hasinit
  //## begin cNameSpaceNode::cNameSpaceNode%1001511095.initialization preserve=yes
  //## end cNameSpaceNode::cNameSpaceNode%1001511095.initialization
{
  //## begin cNameSpaceNode::cNameSpaceNode%1001511095.body preserve=yes
   _Name = name;
   _Parent = parent;
   _NameSpace = name_space;
  //## end cNameSpaceNode::cNameSpaceNode%1001511095.body
}


cNameSpaceNode::~cNameSpaceNode()
{
  //## begin cNameSpaceNode::~cNameSpaceNode%.body preserve=yes
   std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.cbegin();
   while (node != _Children.cend()) {
      cNameSpaceNode * child = (*node).second;
      delete child;
      node++;
   }
  //## end cNameSpaceNode::~cNameSpaceNode%.body
}



//## Other Operations (implementation)
cNameSpaceNode * cNameSpaceNode::AddChild (CONST_STRING_T name, cNameSpace *name_space)
{
  //## begin cNameSpaceNode::AddChild%1001511097.body preserve=yes
   cNameSpaceNode * child = Child(name);
   if (child == NULL) {
      _Type = Branch;
      child = new cNameSpaceNode(name, this, name_space);
      _Children[name] = child;
   }
   return child;
  //## end cNameSpaceNode::AddChild%1001511097.body
}

BOOL_T cNameSpaceNode::RemoveChild (CONST_STRING_T name, cNameSpaceNode *node)
{
  //## begin cNameSpaceNode::RemoveChild%1125306230.body preserve=yes
   cNameSpaceNode * child = Child(name);
   if (child == node) {
      _Children.erase(name);
      return true;
   } else {
      return false;
   }
  //## end cNameSpaceNode::RemoveChild%1125306230.body
}

cNameSpaceNode * cNameSpaceNode::Child (CONST_STRING_T name)
{
  //## begin cNameSpaceNode::Child%1001511105.body preserve=yes
   std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.find(name);
   if (node == _Children.cend()) {
      return NULL;
   } else {
      return (*node).second;
   }
  //## end cNameSpaceNode::Child%1001511105.body
}

cNameSpaceNode * cNameSpaceNode::Parent ()
{
  //## begin cNameSpaceNode::Parent%1001511111.body preserve=yes
   return _Parent;
  //## end cNameSpaceNode::Parent%1001511111.body
}

STRING_T cNameSpaceNode::Path ()
{
  //## begin cNameSpaceNode::Path%1001528552.body preserve=yes
   STRING_T path;
   if (_Parent != NULL) {
      return _NameSpace->Concat(_Parent->Path().c_str(), _Name.c_str());
   } else {
      return "";
   }
  //## end cNameSpaceNode::Path%1001528552.body
}

INT_T cNameSpaceNode::Children (STRING_LIST_T &names)
{
  //## begin cNameSpaceNode::Children%1001511113.body preserve=yes
#undef EMULATE_DIRECTORY
#ifdef EMULATE_DIRECTORY
   names.push_back(".");
   names.push_back("..");
#endif
   std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.cbegin();
   while (node != _Children.cend()) {
      names.push_back((*node).second->get_Name().c_str());
      node++;
   }
   return names.size();
  //## end cNameSpaceNode::Children%1001511113.body
}

INT_T cNameSpaceNode::Leafs (STRING_LIST_T &names)
{
  //## begin cNameSpaceNode::Leafs%1001584927.body preserve=yes
   std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.cbegin();
   while (node != _Children.cend()) {
      if ((*node).second->get_Type() == Leaf) {
         names.push_back((*node).second->get_Name().c_str());
      }
      node++;
   }
   return names.size();
  //## end cNameSpaceNode::Leafs%1001584927.body
}

INT_T cNameSpaceNode::Branches (STRING_LIST_T &names)
{
  //## begin cNameSpaceNode::Branches%1001584928.body preserve=yes
   std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.cbegin();
   while (node != _Children.cend()) {
      if ((*node).second->get_Type() == Branch) {
         names.push_back((*node).second->get_Name().c_str());
      }
      node++;
   }
   return names.size();
  //## end cNameSpaceNode::Branches%1001584928.body
}

INT_T cNameSpaceNode::FullNames (STRING_LIST_T &names)
{
  //## begin cNameSpaceNode::FullNames%1001584929.body preserve=yes
   if (_Type == Leaf) {
      names.push_back(FullName().c_str());
   } else {
      std::map<STRING_T, cNameSpaceNode*>::const_iterator node = _Children.cbegin();
      while (node != _Children.cend()) {
         (*node).second->FullNames(names);
         node++;
      }
   }
   return names.size();
  //## end cNameSpaceNode::FullNames%1001584929.body
}

STRING_T cNameSpaceNode::FullName ()
{
  //## begin cNameSpaceNode::FullName%1001584933.body preserve=yes
   STRING_T path;
   if (_Parent != NULL) {
      return _NameSpace->OutConcat(_Parent->FullName().c_str(), _Name.c_str());
   } else {
      return "";
   }
  //## end cNameSpaceNode::FullName%1001584933.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cNameSpaceNode::get_Name () const
{
  //## begin cNameSpaceNode::get_Name%3BB1D69C006E.get preserve=no
  return _Name;
  //## end cNameSpaceNode::get_Name%3BB1D69C006E.get
}

NodeTypes cNameSpaceNode::get_Type () const
{
  //## begin cNameSpaceNode::get_Type%3BB2F9B20245.get preserve=no
  return _Type;
  //## end cNameSpaceNode::get_Type%3BB2F9B20245.get
}

// Additional Declarations
  //## begin cNameSpaceNode%3BB1D5320154.declarations preserve=yes
  //## end cNameSpaceNode%3BB1D5320154.declarations

//## begin module%3BB1D5320154.epilog preserve=yes
//## end module%3BB1D5320154.epilog
