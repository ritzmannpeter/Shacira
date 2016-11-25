
#include "cNode.h"
#include "cAngle.h"

cNode::cNode(const char * name)
{
   _Name = name;
}

cNode::~cNode()
{
}

void cNode::AddAngle(cAngle * angle)
{
   int size = _Angles.size();
   _Angles.resize(size+1);
   _Angles[size] = angle;
}

void cNode::AddProperty(const char * name, const char * value)
{
   _Properties[name] = value;
}

void cNode::Print(FILE * stream)
{
   fprintf(stream, "node %s:\n", _Name.c_str());
   STRING_MAP_T::const_iterator p = _Properties.begin();
   while (p != _Properties.end()) {
      STRING_T name = (*p).first;
      STRING_T value = (*p).second;
      fprintf(stream, "  %s = %s:\n", name.c_str(), value.c_str());
      p++;
   }
   ANGLE_VECTOR_T::const_iterator a = _Angles.begin();
   while (a != _Angles.end()) {
      cAngle * angle = (*a);
      if (angle->Target() != this) {
         angle->Print(stream);
      }
      a++;
   }
}

