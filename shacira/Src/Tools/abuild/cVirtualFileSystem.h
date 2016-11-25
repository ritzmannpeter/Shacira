
#ifndef cVirtualFileSystem_h
#define cVirtualFileSystem_h

#include "abuild.h"

#define FLAG_DIRECTORY     0x00000001
#define FLAG_ROOT          0x00000002

class cFSNodes;

class cFSNode {
public:
   cFSNode(cFSNodes * parent, const char * name);
   virtual ~cFSNode();
   cFSNodes * Children();
   void Print(int level);
private:
   STRING_T _Name;
   cFSNodes * _Parent;
   unsigned long _Flags;
   cFSNodes * _Children;
};

typedef std::map<STRING_T,cFSNode*> NODE_MAP_T;

class cFSNodes {
public:
   cFSNodes();
   virtual ~cFSNodes();
   cFSNode * Add(const char * name);
   cFSNode * Find(const char * name);
   void Print(int level);
private:
   NODE_MAP_T _Nodes;
};

class cVirtualFileSystem {
public:
   cVirtualFileSystem();
   virtual ~cVirtualFileSystem();
   bool AddPath(const char * path);
   bool FindPath(const char * path);
   void Print(int level);
private:
   cFSNodes * _Nodes;
};

#endif
