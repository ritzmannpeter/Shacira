
#include "cGraph.h"

cGraph::cGraph()
{
   _RootNode = NULL;
   _Flags = HIERARCHICAL_XML_OUTPUT;
}

cGraph::~cGraph()
{
}

cNode * cGraph::Node(const char * name)
{
   cNode * node = NULL;
   GRAPH_NODE_MAP_T::const_iterator i = _NodeMap.find(name);
   if (i == _NodeMap.end()) {
      node = new cNode(this, name);
      AddNode(node);
      _NodeMap[name] = node;
   } else {
      node = (*i).second;
   }
   return node;
}

void cGraph::Print(FILE * stream, int level)
{
   NODE_VECTOR_T::const_iterator i = _Nodes.begin();
   while (i != _Nodes.end()) {
      cNode * node = (*i);
      node->Print(stream, level);
      i++;
   }
}

void cGraph::XML(STRING_T & text, int level)
{
   text += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
   text += "<node name = \"graph\">\n";
   if (cGraph::Flags() & HIERARCHICAL_XML_OUTPUT) {
      if (_RootNode != NULL) {
         _RootNode->XML(text, level + 1);
      }
   } else {
      NODE_VECTOR_T::const_iterator i = _Nodes.begin();
      while (i != _Nodes.end()) {
         cNode * node = (*i);
         node->XML(text, level + 1);
         i++;
      }
   }
   text += "</node>\n";
}

void cGraph::AddNode(cNode * node)
{
   int size = _Nodes.size();
   _Nodes.resize(size+1);
   _Nodes[size] = node;
}

void cGraph::AddAngle(cAngle * angle)
{
   int size = _Angles.size();
   _Angles.resize(size+1);
   _Angles[size] = angle;
}

