
#include "cangle.h"
#include "cgraph.h"

cAngle::cAngle(cGraph * graph, const char * name, cNode * source, cNode * target)
{
   _Graph = graph;
   _Source = source;
   _Target = target;
#ifdef lassma
   _Name = source->Name();
   _Name += ".";
   _Name += name;
   _Name += ".";
   _Name += target->Name();
#else
   _Name = name;
#endif
}

cAngle::~cAngle()
{
}

void cAngle::AddProperty(const char * name, const char * value)
{
   cProperty * property = new cProperty(name, value);
   int size = _Properties.size();
   _Properties.resize(size + 1);
   _Properties[size] = property;
}

void cAngle::Print(FILE * stream, int level)
{
}

void cAngle::XML(STRING_T & text, int level)
{
   cNode::PrintLevel(text, level);
   text += "<angle name = ";
   text += "\"";
   text += Name().c_str();
   text += "\"";
   text += " ";
   text += "source = ";
   text += "\"";
   text += Source()->Name().c_str();
   text += "\"";
   text += " ";
   text += "target = ";
   text += "\"";
   text += Target()->Name().c_str();
   text += "\"";
   text += ">";
   text += "\n";
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
   cNode::PrintLevel(text, level);
   text += "</angle>";
   text += "\n";
   if (_Graph->Flags() & HIERARCHICAL_XML_OUTPUT) {
      Target()->XML(text, level);
   }
}

