
#ifndef _cLiteString_h_
#define _cLiteString_h_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class cLiteString {
public:
   cLiteString();
   cLiteString(const cLiteString & right);
   cLiteString(const char * string);
   cLiteString(const char * string, unsigned long len);
   virtual ~cLiteString();
   const char * c_str() const;
   const unsigned long size() const;
   cLiteString operator +(const cLiteString & right);
   cLiteString operator +(const char * right);
   cLiteString operator +=(const cLiteString & right);
   cLiteString operator +=(const char * right);
   cLiteString operator =(const cLiteString & right);
   cLiteString operator =(const char * right);
   char operator [](unsigned long index);
   void clear();
private:
   int _RefCount;
   char * _String;
};

#endif
