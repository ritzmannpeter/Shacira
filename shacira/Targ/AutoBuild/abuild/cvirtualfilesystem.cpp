
#include "abuild.h"
#include "cvirtualfilesystem.h"
#include "cdirectoryutils.h"

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
      Printf(M_INFO, "--");
   }
   Printf(M_INFO, "%s\n", _Name.c_str());
   _Children->Print(level+1);
}

cFSNodes::cFSNodes()
{
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

cFSNode * cFSNodes::FindCI(const char * name)
{
   NODE_MAP_T::const_iterator i = _Nodes.begin();
   while (i != _Nodes.end()) {
      STRING_T node_name = (*i).second->Name();
      if (stricmp(node_name.c_str(), name) == 0) {
         return (*i).second;
      }
      i++;
   }
   return NULL;
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

bool cVirtualFileSystem::FindFile(const char * file_name, STRING_T & file)
{
   cFSNodes * nodes = _Nodes;
   if (nodes != NULL) {
      NODE_MAP_T node_map = nodes->Nodes();
      NODE_MAP_T::const_iterator i = node_map.begin();
      while (i != node_map.end()) {
         if (FindFileRecursive((*i).second, file_name, "", file)) {
            return true;
         }
         i++;
      }
   }
   return false;   
}

void cVirtualFileSystem::Print(int level)
{
   _Nodes->Print(level);
}

bool cVirtualFileSystem::FindFileRecursive(cFSNode * node, const char * file_name, const char * path, STRING_T & file)
{
   if (node == NULL) {
      return false;
   } else {
      STRING_T node_name = node->Name();
      STRING_T new_path = path;
      if (new_path.size() > 0) {
         new_path += "\\";
      }
      new_path += node_name.c_str();
      if (stricmp(node_name.c_str(), file_name) == 0) {
         file = new_path;
         return true;
      } else {
         cFSNodes * nodes = node->Children();
         if (nodes != NULL) {
            NODE_MAP_T node_map = nodes->Nodes();
            NODE_MAP_T::const_iterator i = node_map.begin();
            while (i != node_map.end()) {
               if (FindFileRecursive((*i).second, file_name, new_path.c_str(), file)) {
                  return true;
               }
               i++;
            }
         }
         return false;
      }
   }
}

