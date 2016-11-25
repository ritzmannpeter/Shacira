
#ifndef __cstatestack_h__
#define __cstatestack_h__

#include "global_defs.h"
#include <string.h>

#define STACK_SIZE 0x1000

class cStateStack
{
public:
   cStateStack()
   {
      int i = 0;
      for (i=0; i<STACK_SIZE; i++) {
         _States[i] = false;
      }
      _States[0] = true;
   };
   virtual ~cStateStack()
   {
   };
   inline void Clear()
   {
      int i = 0;
      for (i=0; i<STACK_SIZE; i++) {
         _States[i] = false;
      }
      _States[0] = true;
   };
   inline bool Get(int level)
   {
      return _States[level];
   }
   inline void Set(int level, bool state)
   {
      _States[level] = state;
   }
protected:
   bool _States[STACK_SIZE];
};

#endif

