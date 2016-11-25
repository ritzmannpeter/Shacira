
#ifndef _cAngle_h
#define _cAngle_h 	1

#include "abuild.h"
class cNode;
class cAngle;
typedef std::vector<cAngle*> ANGLE_VECTOR_T;

class cAngle {
public:
   cAngle(const char * name, cNode * source, cNode * target);
   virtual ~cAngle();
   STRING_T Name() {return _Name;};
   cNode * Source() {return _Source;};
   cNode * Target() {return _Target;};
   void Print(FILE * stream);
protected:
   STRING_T _Name;   
   cNode * _Source;
   cNode * _Target;
};

#endif

