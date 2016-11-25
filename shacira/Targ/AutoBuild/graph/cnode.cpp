
#include "cgraph.h"
#include "cnode.h"
#include "cangle.h"

cNode::cNode(cGraph * graph, const char * name)
{
   _Graph = graph;
   _Name = name;
}

cNode::~cNode()
{
}

bool cNode::IsRoot()
{
   cNode * root_node = _Graph->RootNode();
   if (root_node == NULL) {
      return false;
   } else {
      return root_node == this;
   }
}

void cNode::AddAngle(cAngle * angle)
{
   int size = _Angles.size();
   _Angles.resize(size+1);
   _Angles[size] = angle;
}

void cNode::AddProperty(const char * name, const char * value)
{
   cProperty * property = new cProperty(name, value);
   int size = _Properties.size();
   _Properties.resize(size + 1);
   _Properties[size] = property;
}

void cNode::Print(FILE * stream, int level)
{
}

void cNode::XML(STRING_T & text, int level)
{
   cNode::PrintLevel(text, level);
   text += "<node name = ";
   text += "\"";
   text += _Name.c_str();
   text += "\"";
   text += ">\n";
   PROPERTY_VECTOR_T::const_iterator p = _Properties.begin();
   while (p != _Properties.end()) {
      STRING_T name = (*p)->Name();
      STRING_T value = (*p)->Value();
      cNode::PrintLevel(text, level + 1);
      text += "<property name=";
      text += "\"";
      text += name.c_str();
      text += "\"";
      text += ">";
      text += "\"";
      text += value.c_str();
      text += "\"";
      text += "</property>\n";
      p++;
   }
   ANGLE_VECTOR_T::const_iterator a = _Angles.begin();
   while (a != _Angles.end()) {
      cAngle * angle = (*a);
      angle->XML(text, level + 1);
      a++;
   }
   cNode::PrintLevel(text, level);
   text += "</node>\n";
}

void cNode::PrintLevel(FILE * stream, int level)
{
}

void cNode::PrintLevel(STRING_T & text, int level)
{
   int i = 0;
   for (i=0; i<level; i++) {
      text += "  ";
   }
}

