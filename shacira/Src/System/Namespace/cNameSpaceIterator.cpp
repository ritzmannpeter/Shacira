//## begin module%3BB1D19403AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BB1D19403AB.cm

//## begin module%3BB1D19403AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3BB1D19403AB.cp

//## Module: cNameSpaceIterator%3BB1D19403AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNameSpaceIterator.cpp

//## begin module%3BB1D19403AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BB1D19403AB.additionalIncludes

//## begin module%3BB1D19403AB.includes preserve=yes
//## end module%3BB1D19403AB.includes

// cNameSpaceNode
#include "System/Namespace/cNameSpaceNode.h"
// cNameSpaceIterator
#include "System/Namespace/cNameSpaceIterator.h"
// cNameSpace
#include "System/Namespace/cNameSpace.h"
//## begin module%3BB1D19403AB.additionalDeclarations preserve=yes
//## end module%3BB1D19403AB.additionalDeclarations


// Class cNameSpaceIterator 



cNameSpaceIterator::cNameSpaceIterator()
  //## begin cNameSpaceIterator::cNameSpaceIterator%.hasinit preserve=no
      : _Node(NULL), _NameSpace(NULL)
  //## end cNameSpaceIterator::cNameSpaceIterator%.hasinit
  //## begin cNameSpaceIterator::cNameSpaceIterator%.initialization preserve=yes
  //## end cNameSpaceIterator::cNameSpaceIterator%.initialization
{
  //## begin cNameSpaceIterator::cNameSpaceIterator%.body preserve=yes
  //## end cNameSpaceIterator::cNameSpaceIterator%.body
}

cNameSpaceIterator::cNameSpaceIterator(const cNameSpaceIterator &right)
  //## begin cNameSpaceIterator::cNameSpaceIterator%copy.hasinit preserve=no
      : _Node(NULL), _NameSpace(NULL)
  //## end cNameSpaceIterator::cNameSpaceIterator%copy.hasinit
  //## begin cNameSpaceIterator::cNameSpaceIterator%copy.initialization preserve=yes
  //## end cNameSpaceIterator::cNameSpaceIterator%copy.initialization
{
  //## begin cNameSpaceIterator::cNameSpaceIterator%copy.body preserve=yes
   _NameSpace = right._NameSpace;
   _Node = right._Node;
  //## end cNameSpaceIterator::cNameSpaceIterator%copy.body
}

cNameSpaceIterator::cNameSpaceIterator (cNameSpace *name_space, CONST_STRING_T path)
  //## begin cNameSpaceIterator::cNameSpaceIterator%1001511098.hasinit preserve=no
      : _Node(NULL), _NameSpace(NULL)
  //## end cNameSpaceIterator::cNameSpaceIterator%1001511098.hasinit
  //## begin cNameSpaceIterator::cNameSpaceIterator%1001511098.initialization preserve=yes
  //## end cNameSpaceIterator::cNameSpaceIterator%1001511098.initialization
{
  //## begin cNameSpaceIterator::cNameSpaceIterator%1001511098.body preserve=yes
   _NameSpace = name_space;
   Reset();
   if (path != NULL && strlen(path) > 0) {
      SetPath(path);
   }
  //## end cNameSpaceIterator::cNameSpaceIterator%1001511098.body
}


cNameSpaceIterator::~cNameSpaceIterator()
{
  //## begin cNameSpaceIterator::~cNameSpaceIterator%.body preserve=yes
  //## end cNameSpaceIterator::~cNameSpaceIterator%.body
}


ostream & operator<<(ostream &stream,const cNameSpaceIterator &right)
{
  //## begin cNameSpaceIterator::operator<<%.body preserve=yes
   STRING_LIST_T names;
   int name_count = ((cNameSpaceIterator&)right).Names(names);
   stream << "Directory " << ((cNameSpaceIterator&)right).Name().c_str() << " "
          << name_count << " entries" << endl;
   stream << "Path: " << ((cNameSpaceIterator&)right).Path().c_str() << endl;
   STRING_LIST_T::const_iterator n = names.begin();
   while (n != names.end()) {
      cout << "     " << (*n).c_str() << endl;
      n++;
   }
   return stream;
  //## end cNameSpaceIterator::operator<<%.body
}

istream & operator>>(istream &stream,cNameSpaceIterator &object)
{
  //## begin cNameSpaceIterator::operator>>%.body preserve=yes
   return stream;
  //## end cNameSpaceIterator::operator>>%.body
}



//## Other Operations (implementation)
BOOL_T cNameSpaceIterator::Reset ()
{
  //## begin cNameSpaceIterator::Reset%1001511117.body preserve=yes
   return SetNode(_NameSpace->Root());
  //## end cNameSpaceIterator::Reset%1001511117.body
}

BOOL_T cNameSpaceIterator::SetPath (CONST_STRING_T path)
{
  //## begin cNameSpaceIterator::SetPath%1001511100.body preserve=yes
   if (strlen(path) == 0) return true;
cout << "Change Directory to " << path << endl;
#undef EMULATE_DIRECTORY
#ifdef EMULATE_DIRECTORY
   if (strcmp(path, "..") == 0) return Up();
   if (strcmp(path, ".") == 0) return true;
#endif
   STRING_T delimiter = _NameSpace->get_Delimiter();
   STRING_T _path;
   if (strncmp(delimiter.c_str(), path, delimiter.size()) == 0) {
      _path = &path[delimiter.size()];
      Reset();
   } else {
      _path = path;
   }
   STRING_T tail;
   STRING_T name = _NameSpace->Split(_path.c_str(), tail);
   Down(name.c_str());
   return SetPath(tail.c_str());
  //## end cNameSpaceIterator::SetPath%1001511100.body
}

BOOL_T cNameSpaceIterator::Up ()
{
  //## begin cNameSpaceIterator::Up%1001511101.body preserve=yes
cout << "Up" << endl;
   return SetNode(_Node->Parent());
  //## end cNameSpaceIterator::Up%1001511101.body
}

BOOL_T cNameSpaceIterator::Down (CONST_STRING_T name)
{
  //## begin cNameSpaceIterator::Down%1001511102.body preserve=yes
   if (strlen(name) == 0) return true;
   return SetNode(_Node->Child(name));
  //## end cNameSpaceIterator::Down%1001511102.body
}

STRING_T cNameSpaceIterator::Name ()
{
  //## begin cNameSpaceIterator::Name%1001511114.body preserve=yes
   if (_Node != NULL) {
      return _Node->get_Name();
   } else {
      return "INVALID_NODE";
   }
  //## end cNameSpaceIterator::Name%1001511114.body
}

STRING_T cNameSpaceIterator::Path ()
{
  //## begin cNameSpaceIterator::Path%1001528550.body preserve=yes
   return _Node->Path();
  //## end cNameSpaceIterator::Path%1001528550.body
}

INT_T cNameSpaceIterator::Names (STRING_LIST_T &names)
{
  //## begin cNameSpaceIterator::Names%1001511115.body preserve=yes
   if (_Node != NULL) {
      return _Node->Children(names);
   } else {
      return -1;
   }
  //## end cNameSpaceIterator::Names%1001511115.body
}

INT_T cNameSpaceIterator::Leafs (STRING_LIST_T &names)
{
  //## begin cNameSpaceIterator::Leafs%1001584930.body preserve=yes
   if (_Node != NULL) {
      return _Node->Leafs(names);
   } else {
      return -1;
   }
  //## end cNameSpaceIterator::Leafs%1001584930.body
}

INT_T cNameSpaceIterator::Branches (STRING_LIST_T &names)
{
  //## begin cNameSpaceIterator::Branches%1001584931.body preserve=yes
   if (_Node != NULL) {
      return _Node->Branches(names);
   } else {
      return -1;
   }
  //## end cNameSpaceIterator::Branches%1001584931.body
}

INT_T cNameSpaceIterator::FullNames (STRING_LIST_T &names)
{
  //## begin cNameSpaceIterator::FullNames%1001584932.body preserve=yes
   if (_Node != NULL) {
      return _Node->FullNames(names);
   } else {
      return -1;
   }
  //## end cNameSpaceIterator::FullNames%1001584932.body
}

STRING_T cNameSpaceIterator::FullName ()
{
  //## begin cNameSpaceIterator::FullName%1001584934.body preserve=yes
   if (_Node != NULL) {
      return _Node->FullName();
   } else {
      return "INVALID_NODE";
   }
  //## end cNameSpaceIterator::FullName%1001584934.body
}

BOOL_T cNameSpaceIterator::SetNode (cNameSpaceNode *node)
{
  //## begin cNameSpaceIterator::SetNode%1001511109.body preserve=yes
   if (node != NULL) {
      _Node = node;
      return true;
   } else {
      return false;
   }
  //## end cNameSpaceIterator::SetNode%1001511109.body
}

// Additional Declarations
  //## begin cNameSpaceIterator%3BB1D19403AB.declarations preserve=yes
  //## end cNameSpaceIterator%3BB1D19403AB.declarations

//## begin module%3BB1D19403AB.epilog preserve=yes
//## end module%3BB1D19403AB.epilog
