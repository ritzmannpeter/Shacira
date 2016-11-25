//## begin module%3E8469320119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E8469320119.cm

//## begin module%3E8469320119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E8469320119.cp

//## Module: cTree%3E8469320119; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cTree.cpp

//## begin module%3E8469320119.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E8469320119.additionalIncludes

//## begin module%3E8469320119.includes preserve=yes
//## end module%3E8469320119.includes

// cNodeObject
#include "System/Namespace/cNodeObject.h"
// cNodeContext
#include "System/Namespace/cNodeContext.h"
// cTree
#include "System/Namespace/cTree.h"
//## begin module%3E8469320119.additionalDeclarations preserve=yes

#define DELIMITER "/"

//## end module%3E8469320119.additionalDeclarations


// Class cTree::TreeIterator 




cTree::TreeIterator::TreeIterator()
  //## begin TreeIterator::TreeIterator%.hasinit preserve=no
      : _Tree(NULL), _NextNode(NULL)
  //## end TreeIterator::TreeIterator%.hasinit
  //## begin TreeIterator::TreeIterator%.initialization preserve=yes
  //## end TreeIterator::TreeIterator%.initialization
{
  //## begin cTree::TreeIterator::TreeIterator%.body preserve=yes
  //## end cTree::TreeIterator::TreeIterator%.body
}

cTree::TreeIterator::TreeIterator(const cTree::TreeIterator &right)
  //## begin TreeIterator::TreeIterator%copy.hasinit preserve=no
      : _Tree(NULL), _NextNode(NULL)
  //## end TreeIterator::TreeIterator%copy.hasinit
  //## begin TreeIterator::TreeIterator%copy.initialization preserve=yes
  //## end TreeIterator::TreeIterator%copy.initialization
{
  //## begin cTree::TreeIterator::TreeIterator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTree::TreeIterator::TreeIterator%copy.body
}

cTree::TreeIterator::TreeIterator (cTree *tree)
  //## begin cTree::TreeIterator::TreeIterator%1049099897.hasinit preserve=no
      : _Tree(NULL), _NextNode(NULL)
  //## end cTree::TreeIterator::TreeIterator%1049099897.hasinit
  //## begin cTree::TreeIterator::TreeIterator%1049099897.initialization preserve=yes
  //## end cTree::TreeIterator::TreeIterator%1049099897.initialization
{
  //## begin cTree::TreeIterator::TreeIterator%1049099897.body preserve=yes
  _Tree = tree;
  //## end cTree::TreeIterator::TreeIterator%1049099897.body
}


cTree::TreeIterator::~TreeIterator()
{
  //## begin cTree::TreeIterator::~TreeIterator%.body preserve=yes
  //## end cTree::TreeIterator::~TreeIterator%.body
}



//## Other Operations (implementation)
cTree * cTree::TreeIterator::First ()
{
  //## begin cTree::TreeIterator::First%1049099898.body preserve=yes
	_TouchedNodes.clear();
   cTree * node = _NextNode = _Tree;
   _NextNode = NextNode(node);
   return node;
  //## end cTree::TreeIterator::First%1049099898.body
}

cTree * cTree::TreeIterator::Last ()
{
  //## begin cTree::TreeIterator::Last%1049099899.body preserve=yes
	return NULL;
  //## end cTree::TreeIterator::Last%1049099899.body
}

cTree * cTree::TreeIterator::Next ()
{
  //## begin cTree::TreeIterator::Next%1049099892.body preserve=yes
   cTree * node = _NextNode;
   if (node != NULL) _NextNode = NextNode(node);
   return node;
  //## end cTree::TreeIterator::Next%1049099892.body
}

cTree * cTree::TreeIterator::Previous ()
{
  //## begin cTree::TreeIterator::Previous%1049099893.body preserve=yes
   return NULL;
  //## end cTree::TreeIterator::Previous%1049099893.body
}

cTree * cTree::TreeIterator::FirstLeaf ()
{
  //## begin cTree::TreeIterator::FirstLeaf%1049099900.body preserve=yes
   return NULL;
  //## end cTree::TreeIterator::FirstLeaf%1049099900.body
}

cTree * cTree::TreeIterator::LastLeaf ()
{
  //## begin cTree::TreeIterator::LastLeaf%1049099901.body preserve=yes
   return NULL;
  //## end cTree::TreeIterator::LastLeaf%1049099901.body
}

cTree * cTree::TreeIterator::NextLeaf ()
{
  //## begin cTree::TreeIterator::NextLeaf%1049099894.body preserve=yes
   return NULL;
  //## end cTree::TreeIterator::NextLeaf%1049099894.body
}

cTree * cTree::TreeIterator::PreviousLeaf ()
{
  //## begin cTree::TreeIterator::PreviousLeaf%1049099895.body preserve=yes
   return NULL;
  //## end cTree::TreeIterator::PreviousLeaf%1049099895.body
}

cTree * cTree::TreeIterator::NextNode (cTree *node)
{
  //## begin cTree::TreeIterator::NextNode%1049099906.body preserve=yes
   cTree * parent = node->_Parent;
   if (!Touched(node)) {
      if (node->_Children.size() > 0) {
         _TouchedNodes[node] = node;
         return node->_Children[0];
      } else {
         return NextRightNode(node);
      }
   } else {
      return NextRightNode(node);
   }
  //## end cTree::TreeIterator::NextNode%1049099906.body
}

cTree * cTree::TreeIterator::NextRightNode (cTree *node)
{
  //## begin cTree::TreeIterator::NextRightNode%1049124942.body preserve=yes
   cTree * act_node = node;
   cTree * new_node = RightNode(act_node);
   while (42) {
      if (act_node == _Tree) return NULL;
      if (new_node != NULL) return new_node;
      act_node = act_node->_Parent;
      new_node = RightNode(act_node);
   }
  //## end cTree::TreeIterator::NextRightNode%1049124942.body
}

cTree * cTree::TreeIterator::RightNode (cTree *node)
{
  //## begin cTree::TreeIterator::RightNode%1049114547.body preserve=yes
   cTree * parent = node->_Parent;
   ULONG_T index = node->_Index;
   index++;
   if (parent == NULL) return NULL;
   if (index < parent->_Children.size()) {
      return parent->_Children[index];
   } else {
      return NULL;
   }
  //## end cTree::TreeIterator::RightNode%1049114547.body
}

BOOL_T cTree::TreeIterator::Touched (cTree *node)
{
  //## begin cTree::TreeIterator::Touched%1049114546.body preserve=yes
   TREE_MAP_T::const_iterator i = _TouchedNodes.find(node);
   if (i == _TouchedNodes.end()) {
      return false;
   } else {
      return true;
   }
  //## end cTree::TreeIterator::Touched%1049114546.body
}

// Additional Declarations
  //## begin cTree::TreeIterator%3E87FE2A009C.declarations preserve=yes
  //## end cTree::TreeIterator%3E87FE2A009C.declarations

// Class cTree 








cTree::cTree()
  //## begin cTree::cTree%.hasinit preserve=no
      : _Level(0), _Index(0), _Parent(NULL), _Object(NULL), _Context(NULL)
  //## end cTree::cTree%.hasinit
  //## begin cTree::cTree%.initialization preserve=yes
  //## end cTree::cTree%.initialization
{
  //## begin cTree::cTree%.body preserve=yes
   _Name = "Root";
  //## end cTree::cTree%.body
}

cTree::cTree(const cTree &right)
  //## begin cTree::cTree%copy.hasinit preserve=no
      : _Level(0), _Index(0), _Parent(NULL), _Object(NULL), _Context(NULL)
  //## end cTree::cTree%copy.hasinit
  //## begin cTree::cTree%copy.initialization preserve=yes
  //## end cTree::cTree%copy.initialization
{
  //## begin cTree::cTree%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTree::cTree%copy.body
}

cTree::cTree (CONST_STRING_T name, cTree *parent)
  //## begin cTree::cTree%1048867681.hasinit preserve=no
      : _Level(0), _Index(0), _Parent(NULL), _Object(NULL), _Context(NULL)
  //## end cTree::cTree%1048867681.hasinit
  //## begin cTree::cTree%1048867681.initialization preserve=yes
  //## end cTree::cTree%1048867681.initialization
{
  //## begin cTree::cTree%1048867681.body preserve=yes
   _Name = name;
   _Parent = parent;
  //## end cTree::cTree%1048867681.body
}


cTree::~cTree()
{
  //## begin cTree::~cTree%.body preserve=yes
  //## end cTree::~cTree%.body
}



//## Other Operations (implementation)
void cTree::Add (CONST_STRING_T path)
{
  //## begin cTree::Add%1048867682.body preserve=yes
//printf("Adding %s ...\n", path);
   STRING_T tail;
   STRING_T name = LeftSplit(path, tail);
   if (name.size() == 0) {
      // Root !!
      if (tail.size() > 0) Root()->Add(tail.c_str());
   } else {
      cTree * tree = Child(name.c_str());
      if (tree == NULL) {
         tree = CreateNode(name.c_str(), this);
         AddChild(tree);
      }
      if (tail.size() > 0) tree->Add(tail.c_str());
   }
  //## end cTree::Add%1048867682.body
}

cTree * cTree::Node (CONST_STRING_T path)
{
  //## begin cTree::Node%1048867683.body preserve=yes
   STRING_T tail;
   STRING_T name = LeftSplit(path, tail);
   if (name.size() == 0) {
      // Root !!
      if (tail.size() > 0) {
         return Root()->Node(tail.c_str());
      } else {
         return Root();
      }
   } else {
      cTree * tree = Child(name.c_str());
      if (tree == NULL) {
         return NULL;
      } else {
         if (tail.size() > 0) {
            return tree->Node(tail.c_str());
         } else {
            return tree;
         }
      }
   }
  //## end cTree::Node%1048867683.body
}

cTree * cTree::Node (ULONG_T index)
{
  //## begin cTree::Node%1049099904.body preserve=yes
   if (index >= _Children.size()) {
      return NULL;
   } else {
      return _Children[index];
   }
  //## end cTree::Node%1049099904.body
}

cTree * cTree::Root ()
{
  //## begin cTree::Root%1048867672.body preserve=yes
   if (_Parent != NULL) {
      return _Parent->Root();
   } else {
      return this;
   }
  //## end cTree::Root%1048867672.body
}

void cTree::SetObject (cNodeObject *object)
{
  //## begin cTree::SetObject%1048867679.body preserve=yes
   _Object = object;
  //## end cTree::SetObject%1048867679.body
}

cNodeObject * cTree::Object ()
{
  //## begin cTree::Object%1048867677.body preserve=yes
   return _Object;
  //## end cTree::Object%1048867677.body
}

void cTree::SetContext (cNodeContext *context)
{
  //## begin cTree::SetContext%1048867680.body preserve=yes
   _Context = context;
  //## end cTree::SetContext%1048867680.body
}

cNodeContext * cTree::Context ()
{
  //## begin cTree::Context%1048867678.body preserve=yes
   return _Context;
  //## end cTree::Context%1048867678.body
}

void cTree::Initialize ()
{
  //## begin cTree::Initialize%1048867684.body preserve=yes
  //## end cTree::Initialize%1048867684.body
}

void cTree::Show ()
{
  //## begin cTree::Show%1048867685.body preserve=yes
   printf("%s Index %d\n", Path().c_str(), _Index);
   ULONG_T children = _Children.size();
   for (ULONG_T i=0; i<children; i++) {
      cTree * tree = _Children[i];
      tree->Show();
   }
  //## end cTree::Show%1048867685.body
}

cTree * cTree::CreateNode (CONST_STRING_T node_name, cTree *parent)
{
  //## begin cTree::CreateNode%1049191555.body preserve=yes
	return new cTree(node_name, parent);
  //## end cTree::CreateNode%1049191555.body
}

STRING_T cTree::Path ()
{
  //## begin cTree::Path%1048867687.body preserve=yes
   STRING_T path;
   if (_Parent != NULL) {
      path += _Parent->Path().c_str();
      path += "::";
   }
   path += _Name;
   return path;
  //## end cTree::Path%1048867687.body
}

cTree::TreeIterator cTree::Iterator ()
{
  //## begin cTree::Iterator%1049099896.body preserve=yes
   return TreeIterator(this);
  //## end cTree::Iterator%1049099896.body
}

ULONG_T cTree::Children ()
{
  //## begin cTree::Children%1049099905.body preserve=yes
   return _Children.size();
  //## end cTree::Children%1049099905.body
}

cTree * cTree::Child (CONST_STRING_T name)
{
  //## begin cTree::Child%1048867690.body preserve=yes
   cTree * child = NULL;
   ULONG_T children = _Children.size();
   for (ULONG_T i=0; i<children; i++) {
      child = _Children[i];
      if (strcmp(child->get_Name().c_str(), name) == 0) return child;
   }
   return NULL;
  //## end cTree::Child%1048867690.body
}

void cTree::AddChild (cTree *child)
{
  //## begin cTree::AddChild%1048867691.body preserve=yes
   if (Child(child->get_Name().c_str()) == NULL) {
      ULONG_T children = _Children.size();
      _Children.resize(children+1);
      child->set_Index(children);
      child->set_Level(_Level + 1);
      _Children[children] = child;
   }
  //## end cTree::AddChild%1048867691.body
}

STRING_T cTree::LeftSplit (CONST_STRING_T path, STRING_T &tail)
{
  //## begin cTree::LeftSplit%1048867688.body preserve=yes
   int path_len = strlen(path);
   int delimiter_len = strlen(DELIMITER);
   path_len -= (delimiter_len - 1);
   int pos;
   for (pos=0; pos<path_len; pos++) {
      if (strncmp(&(path[pos]), DELIMITER, delimiter_len) == 0) break;
   }
   if (pos < path_len) {
      STRING_T name = STRING_T(path, pos);
      tail = &(path[pos+1]);
      return name;
   } else {
      tail = "";
      return path;
   }
  //## end cTree::LeftSplit%1048867688.body
}

STRING_T cTree::RightSplit (CONST_STRING_T path, STRING_T &tail)
{
  //## begin cTree::RightSplit%1048867689.body preserve=yes
   int path_len = strlen(path);
   int delimiter_len = strlen(DELIMITER);
   path_len -= (delimiter_len - 1);
   int pos;
   for (pos=path_len-1; pos>=0; pos--) {
      if (strncmp(&(path[pos]), DELIMITER, delimiter_len) == 0) break;
   }
   if (pos < 0) {
      tail = "";
      return path;
   } else {
      STRING_T name = STRING_T(path, pos);
      tail = &(path[pos+1]);
      return name;
   }
  //## end cTree::RightSplit%1048867689.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cTree::get_Name () const
{
  //## begin cTree::get_Name%3E8486BB02BF.get preserve=no
  return _Name;
  //## end cTree::get_Name%3E8486BB02BF.get
}

ULONG_T cTree::get_Level () const
{
  //## begin cTree::get_Level%3E8889410290.get preserve=no
  return _Level;
  //## end cTree::get_Level%3E8889410290.get
}

void cTree::set_Level (ULONG_T value)
{
  //## begin cTree::set_Level%3E8889410290.set preserve=no
  _Level = value;
  //## end cTree::set_Level%3E8889410290.set
}

ULONG_T cTree::get_Index () const
{
  //## begin cTree::get_Index%3E880E710000.get preserve=no
  return _Index;
  //## end cTree::get_Index%3E880E710000.get
}

void cTree::set_Index (ULONG_T value)
{
  //## begin cTree::set_Index%3E880E710000.set preserve=no
  _Index = value;
  //## end cTree::set_Index%3E880E710000.set
}

// Additional Declarations
  //## begin cTree%3E8469320119.declarations preserve=yes
  //## end cTree%3E8469320119.declarations

//## begin module%3E8469320119.epilog preserve=yes
//## end module%3E8469320119.epilog
