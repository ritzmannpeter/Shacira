
#ifndef cVirtualFileSystem_h
#define cVirtualFileSystem_h

#include "global_defs.h"

#define FLAG_DIRECTORY     0x00000001
#define FLAG_ROOT          0x00000002

class cFSNodes;

class cFSNode {
public:
   cFSNode(cFSNodes * parent, const char * name);
   virtual ~cFSNode();
   inline STRING_T Name()
   {
      return _Name;
   };
   inline cFSNodes * Children()
   {
      return _Children;
   };
   inline cFSNodes * Parent()
   {
      return _Parent;
   };
   inline unsigned long Flags()
   {
      return _Flags;
   };
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
   cFSNode * FindCI(const char * name);
   void Print(int level);
   inline NODE_MAP_T Nodes()
   {
      return _Nodes;
   };
private:
   NODE_MAP_T _Nodes;
};

class cVirtualFileSystem {
public:
   cVirtualFileSystem();
   virtual ~cVirtualFileSystem();
   bool AddPath(const char * path);
   bool FindPath(const char * path);
   bool FindFile(const char * file_name, STRING_T & file);
   void Print(int level);
private:
   cFSNodes * _Nodes;
private:
   bool FindFileRecursive(cFSNode * node, const char * file_name, const char * path, STRING_T & file);
};

#endif
