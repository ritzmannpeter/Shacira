
#include "cGraph.h"

cGraph::cGraph()
{
}

cGraph::~cGraph()
{
}

void cGraph::AddNode(cNode * node)
{
   int size = _Nodes.size();
   _Nodes.resize(size+1);
   _Nodes[size] = node;
}

void cGraph::Print(FILE * stream)
{
   NODE_VECTOR_T::const_iterator i = _Nodes.begin();
   while (i != _Nodes.end()) {
      cNode * node = (*i);
      node->Print(stream);
      i++;
   }
}

