
#include "cstringsink.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

cStringSink::cStringSink()
{
   _StringList = new cStringList;
}

cStringSink::~cStringSink()
{
   delete _StringList;
}

void cStringSink::AddString(const char * str)
{
   _StringList->AddString(str);
}

void cStringSink::LoadStringFile(const char * file_name)
{
   FILE * stream = fopen(file_name, "r");
   if (stream != NULL) {
      static char line[0x8000] = {0};
      char * line_ptr = fgets(line, sizeof(line), stream);
      while (line_ptr != NULL) {
         if (!LoadQtStrings(line_ptr)) {
            LoadStrings(line_ptr);
         }
         line_ptr = fgets(line, sizeof(line), stream);
      }
      fclose(stream);
   }
}

void cStringSink::SaveStringFile(const char * file_name, const char * context)
{
   FILE * stream = fopen(file_name, "w");
   if (stream != NULL) {
      _StringList->Reset();
      const char * str = _StringList->GetString();
      while (str != NULL) {
         if (*str != 0 ) {
            fprintf(stream, "QT_TRANSLATE_NOOP(\"%s\", \"%s\")\n", context, str);
         }
         str = _StringList->GetString();
      }
      fclose(stream);
   }
}

#define OUT_OF_STRING   0
#define WITHIN_STRING   1
static char NextChar(const char * str, int & pos, int len)
{
   char c = EOF;
   if (pos != len) {
      c = str[pos];
   }
   pos++;
   return c;
}

bool cStringSink::LoadStrings(const char * text)
{
   char str[0x1000] = {0};
   int len = strlen(text);
   int pos = 0;
   unsigned long str_pos = 0;
   int state = OUT_OF_STRING;
   int prev = 0;
   int c = NextChar(text, pos, len);
   while (c != EOF) {
      if (state == OUT_OF_STRING) {
         if (c == '"') {
            if (c != '\\') {
               state = WITHIN_STRING;
               str_pos = 0;
            }
         }
      } else if (state == WITHIN_STRING) {
         if (c == '"') {
            if (c != '\\') {
               state = OUT_OF_STRING;
               str_pos++;
               str[str_pos] = 0;
               _StringList->AddString(str);
               memset(str, 0, sizeof(str));
            }
         } else {
            str[str_pos] = c;
            str_pos++;
         }
      } else {
      }
      prev = c;
      c = NextChar(text, pos, len);
   }
   return true;
}

bool cStringSink::LoadQtStrings(const char * text)
{
   char context[0x1000] = {0};
   char str[0x1000] = {0};
   int params = sscanf(text, "QT_TRANSLATE_NOOP(\"%[^\"]\", \"%[^\"]\")", context, str);
   if (params == 2) {
      _StringList->AddString(str);
      return true;
   } else {
      return false;
   }
}



