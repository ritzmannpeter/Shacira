
#ifndef _cstringsink_h_
#define _cstringsink_h_

#include "cstringlist.h"
#include <stdio.h>

class cStringSink
{
public:
   cStringSink();
   virtual ~cStringSink();
   void AddString(const char * str);
   void LoadStringFile(const char * file_name);
   void SaveStringFile(const char * file_name, const char * context = "custom");
private:
   bool LoadStrings(const char * text);
   bool LoadQtStrings(const char * text);
private:
   cStringList * _StringList;
};

#endif

