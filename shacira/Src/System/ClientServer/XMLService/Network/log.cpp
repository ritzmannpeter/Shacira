
#include "log.h"
#include <stdarg.h>
#include <stdio.h>

static char _text[0x2000] = {0};
void Log(const char * fileName, const char * fmtString, ...)
{
   va_list args;
   va_start(args, fmtString);
   vsprintf(_text, fmtString, args);
   FILE * stream = fopen(fileName, "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _text);
      fclose(stream);
   }
   va_end(args);
}
