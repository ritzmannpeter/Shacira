
#include "cVirtualFileSystem.h"
#include "cDirectoryUtils.h"

cFSNode::cFSNode(cFSNodes * parent, const char * name)
{
   _Parent = parent;
   _Name = name;
   _Children = new cFSNodes;
}

cFSNode::~cFSNode()
{
}

void cFSNode::Print(int level)
{
   for (int i=0; i<level; i++) {
      Printf("--");
   }
   Printf("%s\n", _Name.c_str());
   _Children->Print(level+1);
}

cFSNodes::cFSNodes()
{
}

cFSNodes * cFSNode::Children()
{
   return _Children;
}

cFSNodes::~cFSNodes()
{
}

cFSNode * cFSNodes::Add(const char * name)
{
   cFSNode * node = Find(name);
   if (node == NULL) {
      node = new cFSNode(this, name);
      _Nodes[name] = node;
   }
   return node;
}

cFSNode * cFSNodes::Find(const char * name)
{
   NODE_MAP_T::const_iterator i = _Nodes.find(name);
   if (i == _Nodes.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cFSNodes::Print(int level)
{
   NODE_MAP_T::const_iterator i = _Nodes.begin();
   while (i != _Nodes.end()) {
      (*i).second->Print(level);
      i++;
   }
}

cVirtualFileSystem::cVirtualFileSystem()
{
   _Nodes = new cFSNodes;
}

cVirtualFileSystem::~cVirtualFileSystem()
{
}

bool cVirtualFileSystem::AddPath(const char * path)
{
   cFSNode * node = NULL;
   cFSNodes * nodes = _Nodes;
   STRING_T head, tail;
   cDirectoryUtils::LeftSplit(path, head, tail);
   node = nodes->Add(head.c_str());
   nodes = node->Children();
   cDirectoryUtils::LeftSplit(tail.c_str(), head, tail);
   while(head.size() > 0 &&
         node != NULL) {
      node = nodes->Add(head.c_str());
      nodes = node->Children();
      cDirectoryUtils::LeftSplit(tail.c_str(), head, tail);
   }
   return false;
}

bool cVirtualFileSystem::FindPath(const char * path)
{
   cFSNode * node = NULL;
   cFSNodes * nodes = _Nodes;
   STRING_T head, tail;
   cDirectoryUtils::LeftSplit(path, head, tail);
   node = nodes->Find(head.c_str());
   if (node == NULL) {
      return false;
   }
   nodes = node->Children();
   cDirectoryUtils::LeftSplit(tail.c_str(), head, tail);
   while(head.size() > 0 &&
         node != NULL) {
      node = nodes->Find(head.c_str());
      if (node == NULL) {
         return false;
      }
      nodes = node->Children();
      cDirectoryUtils::LeftSplit(tail.c_str(), head, tail);
   }
   return true;
}

void cVirtualFileSystem::Print(int level)
{
   _Nodes->Print(level);
}
