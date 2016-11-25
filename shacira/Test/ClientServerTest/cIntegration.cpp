#include "FirstHeader.h"

// cResources
#include "System/Process/cResources.h"
static char _Text[0x8000];

void cResources::EPrintf (CONST_STRING_T fmt_str, ... )
{
   try {
      va_list args;
      va_start(args, fmt_str);
      vsprintf(_Text, fmt_str, args);
      va_end(args);
      printf("%s", _Text);
   } catch (...) {
   }
}

void cResources::IPrintf (CONST_STRING_T fmt_str, ... )
{
   try {
      va_list args;
      va_start(args, fmt_str);
      vsprintf(_Text, fmt_str, args);
      va_end(args);
      printf("%s", _Text);
   } catch (...) {
   }
}

