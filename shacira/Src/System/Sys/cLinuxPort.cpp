
#include "cLinuxPort.h"

#ifdef __linux__

#include <ctype.h>
#include <stdio.h>
#include <string.h>

extern "C" {

char* ltoa(long value, char * buf, int sys)
{
#warning "straightforward linux implementation"
   if (sys == 8) {
      sprintf(buf, "%o", value);
   } else if (sys == 16) {
      sprintf(buf, "%x", value);
   } else {
      sprintf(buf, "%d", value);
   }
   return buf;
}

char* itoa(int value, char * buf, int sys)
{
#warning "straightforward linux implementation"
   if (sys == 8) {
      sprintf(buf, "%o", value);
   } else if (sys == 16) {
      sprintf(buf, "%x", value);
   } else {
      sprintf(buf, "%d", value);
   }
   return buf;
}

void strupr(char *s)
{
#warning "straightforward linux implementation"
   int len = strlen(s);
   int i = 0;
   for (i=0; i<len; i++) {
      char c = toupper(s[i]);
      s[i] = c;
   }
#ifdef lassma
   while (*s) {
      *s++ = toupper(*s);
   }
#endif
}

}

#endif

