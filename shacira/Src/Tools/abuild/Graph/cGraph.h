
#ifndef _cGraph_h
#define _cGraph_h 	1

#include "abuild.h"
#include "cNode.h"
#include "cAngle.h"

class cGraph {
public:
   cGraph();
   virtual ~cGraph();
   void AddNode(cNode * node);
   void Print(FILE * stream);
protected:
   NODE_VECTOR_T _Nodes;
};

#endif

