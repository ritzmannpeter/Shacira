
#ifndef _cproperty_h
#define _cproperty_h 	1

#include "global_defs.h"

class cProperty {
public:
   inline cProperty(const char * name, const char * value)
   {
      _Name = name;
      _Value = value;
   };
   inline const char * Name()
   {
      return _Name.c_str();
   };
   inline const char * Value()
   {
      return _Value.c_str();
   };
protected:
   STRING_T _Name;
   STRING_T _Value;
};

typedef std::vector<cProperty*> PROPERTY_VECTOR_T;

#endif

