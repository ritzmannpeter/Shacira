
#include "utils.h"

const char * GetArg(int i, int argc, char*argv[], int opt_len)
{
   const char * arg = &argv[i][opt_len];
   if (*arg != 0) {
      return arg;
   } else {
      if (i + 1 < argc) {
         arg = argv[i + 1];
         if (*arg != '-') {
            return arg;
         } else {
            return 0;
         }
      } else {
         return NULL;
      }
   }
}

bool ReadLine(FILE * file, char * buf, unsigned long buf_size)
{
   memset(buf, 0, buf_size);
   char * _buf = fgets(buf, buf_size, file);
   if (_buf == buf) {
      unsigned long len = strlen(buf);
      if (len > 0 && buf[len - 1] == '\n') {
         buf[len - 1] = 0;
      }
      return true;
   } else {
      return false;
   }
}

unsigned long GetToken(const char * source, char * token_buf, unsigned long token_buf_size, char delimiter)
{
   return 0;
}


