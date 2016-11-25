
#ifndef _cNode_h
#define _cNode_h 	1

#include "abuild.h"
#include "cAngle.h"

class cNode;
typedef std::vector<cNode*> NODE_VECTOR_T;

class cNode {
public:
   cNode(const char * name);
   virtual ~cNode();
   STRING_T Name() {return _Name;};
   void AddAngle(cAngle * angle);
   void AddProperty(const char * name, const char * value);
   void Print(FILE * stream);
protected:
   STRING_T _Name;
   ANGLE_VECTOR_T _Angles;
   STRING_MAP_T _Properties;
};

#endif

