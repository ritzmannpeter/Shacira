
#ifndef _cLiteWString_h_
#define _cLiteWString_h_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class cLiteWString {
public:
   cLiteWString();
   cLiteWString(const cLiteWString & right);
   cLiteWString(const short * string);
   cLiteWString(const short * string, unsigned long len);
   virtual ~cLiteWString();
   const short * c_str() const;
   const unsigned long size() const;
   cLiteWString operator +(const cLiteWString & right);
   cLiteWString operator +(const short * right);
   cLiteWString operator +=(const cLiteWString & right);
   cLiteWString operator +=(const short * right);
   cLiteWString operator =(const cLiteWString & right);
   cLiteWString operator =(const short * right);
   short operator [](unsigned long index);
   bool operator ==(const cLiteWString & right);
   bool operator !=(const cLiteWString & right);
   void clear();
private:
   int _RefCount;
   short * _String;
};

#endif
