
#include "cAngle.h"
#include "cNode.h"

cAngle::cAngle(const char * name, cNode * source, cNode * target)
{
   _Source = source;
   _Target = target;
   _Name = name;
   _Source->AddAngle(this);
   _Target->AddAngle(this);
}

cAngle::~cAngle()
{
}

void cAngle::Print(FILE * stream)
{
   fprintf(stream, "  angle %s:\n", _Name.c_str());
   fprintf(stream, "    source: %s\n", _Source->Name().c_str());
   fprintf(stream, "    target: %s\n", _Target->Name().c_str());
}
