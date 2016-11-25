 
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char _Text[0x2000] = {0};

void PluginPrintf(const char * fmt_str, ...)
{
   va_list ap;
   va_start(ap, fmt_str);
   try {
      vsprintf(_Text, fmt_str, ap);
      const char * file_name = getenv("PLUGIN_LOG");
      if (file_name != NULL) {
         if (strlen(file_name) > 0) {
            printf("%s", _Text);
            FILE * stream = fopen(file_name, "a");
            if (stream != NULL) {
               fprintf(stream, "%s", _Text);
               fclose(stream);
            }
         }
      }
   } catch (...) {
   }
   va_end(ap);
}


