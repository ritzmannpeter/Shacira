
#ifndef _safefunctions_h_
#define _safefunctions_h_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#if _MSC_VER <= 1200

inline int SafeStrCpy(char * destination, const char * source, size_t count)
{
   if ((destination == NULL) || (source == NULL)) return 0;

   if (strlen(source) >= count) {
      memcpy(destination, source, count - 2);
      destination[count-1] = '\0';
   } else {
      strncpy(destination, source, count);
   }
   return 0;
};

inline int SafePrintf(char * buffer, size_t count, const char * format, ...)
{
   int rc = 0;
   va_list ap;
   va_start(ap, format);
   rc = _vsnprintf(buffer, count - 1, format, ap);
   va_end(ap);
   return rc;
};

#else

inline errno_t SafeStrCpy(char * destination, const char * source, size_t count)
{
   if ((destination == NULL) || (source == NULL)) return 0;

#ifdef _DEBUG
   strncpy_s(destination, count, source, count);
#else
   if (strlen(source) >= count) {
      memcpy(destination, source, count - 2);
      destination[count-1] = '\0';
   } else {
      strncpy_s(destination, count, source, count);
   }
#endif
   return 0;
};

inline errno_t SafePrintf(char * buffer, rsize_t count, const char * format, ...)
{
   int rc = 0;
   va_list ap;
   va_start(ap, format);
   rc = vsprintf_s(buffer, count - 1, format, ap);
   va_end(ap);
   return rc;
};

#endif

#endif
