//## begin module%3BB1D0ED0224.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D0ED0224.cm

//## begin module%3BB1D0ED0224.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D0ED0224.cp

//## Module: cNameSpace%3BB1D0ED0224; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpace.cpp

//## begin module%3BB1D0ED0224.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BB1D0ED0224.additionalIncludes

//## begin module%3BB1D0ED0224.includes preserve=yes
//## end module%3BB1D0ED0224.includes

// cStringUtils
#include "System/cStringUtils.h"
// cNameSpaceNode
#include "System/Namespace/cNameSpaceNode.h"
// cNameSpace
#include "System/Namespace/cNameSpace.h"
//## begin module%3BB1D0ED0224.additionalDeclarations preserve=yes

static BOOL_T IS_ROOT(CONST_STRING_T path)
{
   if (strcmp(path, "") == 0 ||
       strcmp(path, "/") == 0 ||
       strcmp(path, "\\") == 0) {
      return true;
   } else {
      return false;
   }
}

//## end module%3BB1D0ED0224.additionalDeclarations


// Class cNameSpace 







cNameSpace::cNameSpace()
  //## begin cNameSpace::cNameSpace%.hasinit preserve=no
      : _Delimiter("/"), _OutDelimiter("."), _Root(NULL)
  //## end cNameSpace::cNameSpace%.hasinit
  //## begin cNameSpace::cNameSpace%.initialization preserve=yes
  //## end cNameSpace::cNameSpace%.initialization
{
  //## begin cNameSpace::cNameSpace%.body preserve=yes
   _Root = new cNameSpaceNode("", NULL, this);
  //## end cNameSpace::cNameSpace%.body
}

cNameSpace::cNameSpace(const cNameSpace &right)
  //## begin cNameSpace::cNameSpace%copy.hasinit preserve=no
      : _Delimiter("/"), _OutDelimiter("."), _Root(NULL)
  //## end cNameSpace::cNameSpace%copy.hasinit
  //## begin cNameSpace::cNameSpace%copy.initialization preserve=yes
  //## end cNameSpace::cNameSpace%copy.initialization
{
  //## begin cNameSpace::cNameSpace%copy.body preserve=yes
   _Delimiter = right._Delimiter;
   _Root = right._Root;
  //## end cNameSpace::cNameSpace%copy.body
}


cNameSpace::~cNameSpace()
{
  //## begin cNameSpace::~cNameSpace%.body preserve=yes
   DELETE_OBJECT(cNameSpaceNode, _Root)
  //## end cNameSpace::~cNameSpace%.body
}



//## Other Operations (implementation)
BOOL_T cNameSpace::Add (CONST_STRING_T path)
{
  //## begin cNameSpace::Add%1001511103.body preserve=yes
   if (IS_ROOT(path)) {
      return true;
   }
   return AddNode(path, _Root);
  //## end cNameSpace::Add%1001511103.body
}

BOOL_T cNameSpace::Exists (CONST_STRING_T path)
{
  //## begin cNameSpace::Exists%1125306234.body preserve=yes
   if (IS_ROOT(path)) {
      return true;
   }
   return Exists(path, _Root);
  //## end cNameSpace::Exists%1125306234.body
}

BOOL_T cNameSpace::Remove (CONST_STRING_T path)
{
  //## begin cNameSpace::Remove%1125306227.body preserve=yes
   if (IS_ROOT(path)) {
      return false;
   }
   return RemoveNode(path, _Root);
  //## end cNameSpace::Remove%1125306227.body
}

cNameSpaceIterator cNameSpace::Iterator (CONST_STRING_T name)
{
  //## begin cNameSpace::Iterator%1001511104.body preserve=yes
   return cNameSpaceIterator(this, name);
  //## end cNameSpace::Iterator%1001511104.body
}

cNameSpaceNode * cNameSpace::Root ()
{
  //## begin cNameSpace::Root%1001511110.body preserve=yes
   return _Root;
  //## end cNameSpace::Root%1001511110.body
}

BOOL_T cNameSpace::AddNode (CONST_STRING_T path, cNameSpaceNode *node)
{
  //## begin cNameSpace::AddNode%1001511112.body preserve=yes
   if (node == NULL || strlen(path) == 0) {
      return true;
   }
   STRING_T tail;
   STRING_T name = Split(path, tail);
   cNameSpaceNode * new_node = node->Child(name.c_str());
   if (new_node != NULL) {
      return AddNode(tail.c_str(), new_node);
   } else {
      new_node = node->AddChild(name.c_str(), this);
      return AddNode(tail.c_str(), new_node);
   }
  //## end cNameSpace::AddNode%1001511112.body
}

BOOL_T cNameSpace::Exists (CONST_STRING_T path, cNameSpaceNode *node)
{
  //## begin cNameSpace::Exists%1125306235.body preserve=yes
   if (strlen(path) == 0) {
      return true;
   }
   if (node == NULL) {
      return false;
   }
   STRING_T tail;
   STRING_T name = Split(path, tail);
   cNameSpaceNode * new_node = node->Child(name.c_str());
   if (new_node != NULL) {
      return Exists(tail.c_str(), new_node);
   } else {
      return false;
   }
  //## end cNameSpace::Exists%1125306235.body
}

BOOL_T cNameSpace::RemoveNode (CONST_STRING_T path, cNameSpaceNode *node)
{
  //## begin cNameSpace::RemoveNode%1125306228.body preserve=yes
   if (node == NULL) {
      return true;
   }
   if (strlen(path) == 0) {
      return RemoveRecursive(node);
   }
   STRING_T tail;
   STRING_T name = Split(path, tail);
   cNameSpaceNode * new_node = node->Child(name.c_str());
   if (new_node != NULL) {
      return RemoveNode(tail.c_str(), new_node);
   } else {
      return true;

      new_node = node->AddChild(name.c_str(), this);
      return RemoveNode(tail.c_str(), new_node);
   }
  //## end cNameSpace::RemoveNode%1125306228.body
}

BOOL_T cNameSpace::RemoveRecursive (cNameSpaceNode *node)
{
  //## begin cNameSpace::RemoveRecursive%1125306229.body preserve=yes
   STRING_T name = node->get_Name();
   if (node == _Root) {
      cNameSpaceNode * parent = node->Parent();
      STRING_T parent_name = parent->get_Name();
      parent->RemoveChild(name.c_str(), node);
      delete node;
   }
   return true;
  //## end cNameSpace::RemoveRecursive%1125306229.body
}

STRING_T cNameSpace::Split (CONST_STRING_T path, STRING_T &tail)
{
  //## begin cNameSpace::Split%1001511108.body preserve=yes
   int pos = cStringUtils::Find(path, _Delimiter.c_str());
   if (pos < 0) {
      return path;
   } else {
      STRING_T name = STRING_T(path, pos);
      tail = &(path[pos+1]);
      return name;
   }
  //## end cNameSpace::Split%1001511108.body
}

STRING_T cNameSpace::Concat (CONST_STRING_T path, CONST_STRING_T name)
{
  //## begin cNameSpace::Concat%1001528551.body preserve=yes
   STRING_T new_path = path;
   new_path += _Delimiter.c_str();
   new_path += name;
   return new_path;
  //## end cNameSpace::Concat%1001528551.body
}

STRING_T cNameSpace::OutConcat (CONST_STRING_T path, CONST_STRING_T name)
{
  //## begin cNameSpace::OutConcat%1001584935.body preserve=yes
   STRING_T new_path = path;
   if (strlen(path) > 0) {
      new_path += _OutDelimiter.c_str();
      new_path += name;
   } else {
      new_path = name;
   }
   return new_path;
  //## end cNameSpace::OutConcat%1001584935.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cNameSpace::get_Delimiter () const
{
  //## begin cNameSpace::get_Delimiter%3BB1D8840015.get preserve=no
  return _Delimiter;
  //## end cNameSpace::get_Delimiter%3BB1D8840015.get
}

void cNameSpace::set_Delimiter (STRING_T value)
{
  //## begin cNameSpace::set_Delimiter%3BB1D8840015.set preserve=no
  _Delimiter = value;
  //## end cNameSpace::set_Delimiter%3BB1D8840015.set
}

STRING_T cNameSpace::get_OutDelimiter () const
{
  //## begin cNameSpace::get_OutDelimiter%3BB3206A0054.get preserve=no
  return _OutDelimiter;
  //## end cNameSpace::get_OutDelimiter%3BB3206A0054.get
}

void cNameSpace::set_OutDelimiter (STRING_T value)
{
  //## begin cNameSpace::set_OutDelimiter%3BB3206A0054.set preserve=no
  _OutDelimiter = value;
  //## end cNameSpace::set_OutDelimiter%3BB3206A0054.set
}

// Additional Declarations
  //## begin cNameSpace%3BB1D0ED0224.declarations preserve=yes
  //## end cNameSpace%3BB1D0ED0224.declarations

//## begin module%3BB1D0ED0224.epilog preserve=yes
//## end module%3BB1D0ED0224.epilog
