
#ifndef _cgraphnode_h
#define _cgraphnode_h 	1

#include "global_defs.h"
#include "cgraph.h"
#include "cnode.h"

class cGraphNode {
public:
   virtual cNode * Node(cGraph * graph) = 0;
};

#endif

