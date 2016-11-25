 
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
      char * file_name = getenv("PLUGIN_LOG_FILE");
      if (file_name == NULL) {
         file_name = "c:/temp/q4_cwidget_plugin.log";
      }
      vsprintf_s(_Text, sizeof(_Text) - 1, fmt_str, ap);
      if (file_name != NULL) {
         if (strlen(file_name) > 0) {
            FILE * stream = fopen(file_name, "a");
            if (stream != NULL) {
#ifdef _DEBUG
               fprintf(stream, "%s debug\n", _Text);
#else
               fprintf(stream, "%s\n", _Text);
#endif
               fclose(stream);
            }
         }
      }
   } catch (...) {
   }
   va_end(ap);
}


